#!/usr/bin/env python3
"""pack.py - packs the game's files for the web build's download mode (README.md, "Download mode").

    python pack.py --out FOLDER [--usrdir PATH] [--only LVL000,LVL010] [--level 19] [--jobs 3]
                   [--video-crf 34] [--video-jobs 4] [--music-quality 5] [--ffmpeg PATH]

Reads the game's PS3_GAME/USRDIR (only ever reads it) and writes into FOLDER:
  manifest.json      every file the game can ask for: its size and time, and either "raw" (videos and music:
                     streamed by ranges while they play) or a blob to download
  usrdir.manifest    the same listing in the form the game's file layer reads (as serve.py's)
  blob/<hash>.zst    a file's content, zstd-compressed (one frame, with a checksum). Files with the same content
                     share one blob (the localisation file is the same in every level folder).
  blob/<hash>.from.<base>.zst
                     the same content compressed as a difference against another blob the browser already has
                     at that point (a level's main file against the previous level's, a sector against the one
                     before it): kept when it is at least 10% smaller. The browser takes it when it has the base.
  video/<path>       the videos, re-encoded for slower connections (pack_video.py: the picture as VP9 at a constant
                     quality, --video-crf; the audio tracks as they are, each voice language in a file of its own).
                     Needs an ffmpeg with libvpx-vp9 on the PATH (or --ffmpeg); without one, or with --video-crf 0,
                     the videos are streamed as they are on the disc.
  music/<path>       the music, re-encoded (pack_music.py: Vorbis at --music-quality; "<file>.RWS" is only the
                     source's header, "<file>.RWS.OGV" the samples). Needs an ffmpeg with libvorbis; without one,
                     or with --music-quality 0, the music is streamed as the PCM it is on the disc.
                     The videos' picture and the music are the two lossy steps of the pack.

The pack is what make_site.py turns into a folder a static web host can serve.

What is left out: EBOOT.BIN and Shader/ (the port does not read them), anything that is not a game file, and
the executable: EBOOT.elf is replaced by a file of the same size that is zero everywhere except the two Cg shader
source texts the renderer reads from it.

--only limits the level folders packed (a quick test pack); the blobs already in FOLDER are kept, so a later
full run only adds the missing ones.
"""
import argparse
import concurrent.futures
import hashlib
import json
import math
import os
import re
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
_up = HERE
for _ in range(5):  # the repository's per-process memory cap for helper scripts (work/memguard.py)
    if os.path.isfile(os.path.join(_up, 'work', 'memguard.py')):
        sys.path.insert(0, os.path.join(_up, 'work'))
        import memguard  # noqa: F401
        break
    _up = os.path.dirname(_up)

import zstandard as zstd

import pack_music
import pack_video

MB = 1048576
# The Cg sources in EBOOT.elf (platform/gfx/cg_to_glsl.cpp, LoadGameSources): file offset and first line.
CG_BLOCKS = [(0xc26750, b'#pragma pack_matrix (row_major)'), (0xc19848, b'#ifndef externBasicShader')]


def is_raw(path):
    """Streamed while it plays, not downloaded: the videos (Bink, incompressible) and the music (PCM)."""
    return path.upper().endswith('.VID') or path.upper().startswith('MUSIC/')


def is_wanted(path):
    top = path.split('/')[0].upper()
    name = path.split('/')[-1].upper()
    if top == 'SHADER' or name == 'EBOOT.BIN':
        return False
    return name.endswith(('.KP3', '.RWS', '.KCS', '.VID')) or name == 'EBOOT.ELF'


def read_file(path):
    with open(path, 'rb') as f:
        return f.read()


def file_id(path):
    """The name a re-encoded video has in the browser's store: a hash of its content, like a blob's."""
    h = hashlib.sha1()
    with open(path, 'rb') as f:
        for part in iter(lambda: f.read(MB), b''):
            h.update(part)
    return h.hexdigest()[:20]


def eboot_stand_in(data):
    """Zeros of the same size, with the two Cg source texts (up to their terminating zero) in place."""
    out = bytearray(len(data))
    for offset, first_line in CG_BLOCKS:
        if data[offset:offset + len(first_line)] != first_line:
            raise SystemExit('pack.py: EBOOT.elf does not have the expected Cg source at 0x%x' % offset)
        end = data.index(b'\0', offset)
        out[offset:end] = data[offset:end]
    return bytes(out)


def content_of(usrdir, path):
    data = read_file(os.path.join(usrdir, path))
    return eboot_stand_in(data) if path.upper() == 'EBOOT.ELF' else data


def window_log(total):
    return max(20, min(30, math.ceil(math.log2(max(total, 2)))))


def compress_full(job):
    usrdir, path, out_file, level = job
    data = content_of(usrdir, path)
    params = zstd.ZstdCompressionParameters.from_level(level, window_log=min(27, window_log(len(data))), enable_ldm=True,
                                                       threads=4, write_checksum=True, write_content_size=True)
    packed = zstd.ZstdCompressor(compression_params=params).compress(data)
    with open(out_file + '.tmp', 'wb') as f:
        f.write(packed)
    os.replace(out_file + '.tmp', out_file)
    return len(packed)


def compress_delta(job):
    usrdir, path, base_path, out_file, levels = job
    data = content_of(usrdir, path)
    base = content_of(usrdir, base_path)
    prefix = zstd.ZstdCompressionDict(base, dict_type=zstd.DICT_TYPE_RAWCONTENT)
    packed = None
    for level in levels:  # the smallest of the levels tried (15 finds more of a far base than 19 does: measured)
        # One thread: with several, zstd only uses the prefix for the first part of the input.
        params = zstd.ZstdCompressionParameters.from_level(level, window_log=window_log(len(data) + len(base)),
                                                           enable_ldm=True, threads=0, write_checksum=True,
                                                           write_content_size=True)
        attempt = zstd.ZstdCompressor(compression_params=params, dict_data=prefix).compress(data)
        if packed is None or len(attempt) < len(packed):
            packed = attempt
    with open(out_file + '.tmp', 'wb') as f:
        f.write(packed)
    os.replace(out_file + '.tmp', out_file)
    return len(packed)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--usrdir', help="the game's PS3_GAME/USRDIR (read-only; default: as serve.py finds it)")
    ap.add_argument('--out', required=True, help='the pack folder to write')
    ap.add_argument('--only', help='level folders to pack, e.g. LVL000,LVL010 (default: all)')
    ap.add_argument('--level', type=int, default=19, help='zstd level of a whole file (default 19)')
    ap.add_argument('--delta-levels', default='15,19', help='zstd levels tried for a difference; the smallest is kept')
    ap.add_argument('--jobs', type=int, default=3, help='compressions at a time (each may take about 1 GB)')
    ap.add_argument('--video-crf', type=int, default=34,
                    help='VP9 quality of the re-encoded videos, lower = better and larger (default 34; 0 = leave the '
                         'videos as they are)')
    ap.add_argument('--video-jobs', type=int, default=4, help='videos encoded at a time (4 threads each)')
    ap.add_argument('--music-quality', type=float, default=5,
                    help='Vorbis quality of the re-encoded music, 0 to 10 (default 5, about 150 kbit/s; 0 = leave the '
                         'music as it is)')
    ap.add_argument('--ffmpeg', help='the ffmpeg to encode the videos and the music with (default: the one on the PATH)')
    args = ap.parse_args()

    if not args.usrdir:  # DOTD_USRDIR, then a dotd.ini (serve.py's search)
        sys.path.insert(0, HERE)
        import serve
        args.usrdir = serve.find_usrdir(None)
    if not args.usrdir or not os.path.isdir(args.usrdir):
        raise SystemExit('pack.py: no game folder: give --usrdir PATH (your PS3_GAME/USRDIR)')
    usrdir = os.path.abspath(args.usrdir)
    out = os.path.abspath(args.out)
    if os.path.commonpath([usrdir, out]) == usrdir:
        raise SystemExit('pack.py: --out must not be inside the game folder')
    os.makedirs(os.path.join(out, 'blob'), exist_ok=True)
    only = set(x.strip().upper() for x in args.only.split(',')) if args.only else None

    # ---- the files ---------------------------------------------------------------------------------------------
    paths = []
    for folder, dirs, files in os.walk(usrdir):
        dirs.sort()
        rel = os.path.relpath(folder, usrdir).replace(os.sep, '/')
        prefix = '' if rel == '.' else rel + '/'
        for name in sorted(files):
            path = prefix + name
            top = path.split('/')[0].upper()
            if not is_wanted(path):
                continue
            if only is not None and re.fullmatch(r'LVL\d+', top) and top not in only:
                continue
            paths.append(path)
    levels = sorted(set(p.split('/')[0][3:] for p in paths if re.fullmatch(r'LVL\d+', p.split('/')[0], re.I)))

    files = {}
    by_hash = {}  # blob hash -> a path with that content
    start = time.time()
    for path in paths:
        st = os.stat(os.path.join(usrdir, path))
        entry = {'size': st.st_size, 'mtime': int(st.st_mtime)}
        if is_raw(path):
            entry['raw'] = True
        else:
            entry['blob'] = hashlib.sha1(content_of(usrdir, path)).hexdigest()[:20]
            by_hash.setdefault(entry['blob'], path)
        files[path] = entry
    packed = [p for p in paths if 'blob' in files[p]]
    print('pack.py: %d files (%d to download in %d blobs, %d streamed), hashed in %.0f s' %
          (len(paths), len(packed), len(by_hash), len(paths) - len(packed), time.time() - start), flush=True)

    # ---- what a blob may be a difference against ---------------------------------------------------------------------
    def base_of(path):
        m = re.fullmatch(r'LVL(\d+)/LVL\1\.KP3', path, re.I)
        if m:
            i = levels.index(m.group(1))
            return 'LVL%s/LVL%s.KP3' % (levels[i - 1], levels[i - 1]) if i > 0 else None
        m = re.fullmatch(r'LVL(\d+)/STR(\d+)(\d\d)\.KP3', path, re.I)
        if m:
            sector = int(m.group(3))
            if sector == 0:
                return 'LVL%s/LVL%s.KP3' % (m.group(1), m.group(1))
            return 'LVL%s/STR%s%02d.KP3' % (m.group(1), m.group(2), sector - 1)
        return None

    full_jobs, delta_jobs = [], []
    for blob, path in by_hash.items():
        target = os.path.join(out, 'blob', blob + '.zst')
        if not os.path.isfile(target):
            full_jobs.append((usrdir, path, target, args.level))
        base_path = base_of(path)
        if base_path in files and files[base_path]['blob'] != blob:
            base = files[base_path]['blob']
            target = os.path.join(out, 'blob', '%s.from.%s.zst' % (blob, base))
            if not os.path.isfile(target) and not os.path.isfile(target + '.no'):
                delta_jobs.append((usrdir, path, base_path, target, [int(x) for x in args.delta_levels.split(',')]))

    # ---- compress --------------------------------------------------------------------------------------------------------
    done = 0
    total = len(full_jobs) + len(delta_jobs)
    start = time.time()
    with concurrent.futures.ProcessPoolExecutor(max_workers=max(1, args.jobs)) as pool:
        pending = {pool.submit(compress_full, job): ('full', job[1]) for job in full_jobs}
        pending.update({pool.submit(compress_delta, job): ('delta', job[1]) for job in delta_jobs})
        for future in concurrent.futures.as_completed(pending):
            kind, path = pending[future]
            size = future.result()
            done += 1
            print('pack.py: [%d/%d] %-5s %-28s %7.1f MB -> %7.1f MB  (%.0f s)' %
                  (done, total, kind, path, files[path]['size'] / MB, size / MB, time.time() - start), flush=True)

    # ---- the videos ------------------------------------------------------------------------------------------------------
    videos = [p for p in paths if p.upper().endswith('.VID')]
    ffmpeg = pack_video.find_ffmpeg(args.ffmpeg) if args.video_crf > 0 else None
    if args.video_crf > 0 and not ffmpeg:
        print('pack.py: no ffmpeg with libvpx-vp9 found (PATH or --ffmpeg): the videos stay as they are', flush=True)
    video_disc = video_sent = 0
    if ffmpeg:
        def one_video(path):
            source = os.path.join(usrdir, path)
            target = os.path.join(out, 'video', *path.split('/'))
            meta = pack_video.up_to_date(source, target, args.video_crf)
            if meta is not None:
                return path, meta, False
            return path, pack_video.encode(source, target, args.video_crf, ffmpeg), True

        start = time.time()
        done = 0
        metas = {}
        with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, args.video_jobs)) as pool:
            jobs = [pool.submit(one_video, p) for p in sorted(videos, key=lambda p: -files[p]['size'])]
            for future in concurrent.futures.as_completed(jobs):
                path, meta, fresh = future.result()
                metas[path] = meta
                done += 1
                if fresh:
                    name = path.split('/')[-1]
                    print('pack.py: [%d/%d] video %-24s %7.1f MB -> %6.1f MB picture and music, %d voice files  (%.0f s)' %
                          (done, len(videos), path, files[path]['size'] / MB, meta['files'][name] / MB,
                           len(meta['files']) - 1, time.time() - start), flush=True)
        with_sides = []
        for path in paths:
            with_sides.append(path)
            if path not in metas:
                continue
            folder, _, name = path.rpartition('/')
            entry = files[path]
            video_disc += entry['size']
            entry['size'] = metas[path]['files'][name]
            entry['video'] = True
            entry['store'] = file_id(os.path.join(out, 'video', *path.split('/')))
            video_sent += entry['size']
            sides = sorted(n for n in metas[path]['files'] if n != name)
            for side in sides:  # the voice tracks: files of their own next to the video
                side_path = (folder + '/' if folder else '') + side
                files[side_path] = {'size': metas[path]['files'][side], 'mtime': entry['mtime'], 'raw': True,
                                    'video': True, 'store': file_id(os.path.join(out, 'video', *side_path.split('/')))}
                with_sides.append(side_path)
            if sides:
                video_sent += max(metas[path]['files'][n] for n in sides)  # one voice language is played
        paths = with_sides

    # ---- the music -------------------------------------------------------------------------------------------------------
    music_disc = music_sent = 0
    music_ffmpeg = pack_music.find_ffmpeg(args.ffmpeg) if args.music_quality > 0 else None
    if args.music_quality > 0 and not music_ffmpeg:
        print('pack.py: no ffmpeg with libvorbis found (PATH or --ffmpeg): the music stays as it is', flush=True)
    if music_ffmpeg:
        tracks = [p for p in paths if p.upper().startswith('MUSIC/') and 'video' not in files[p] and
                  pack_music.is_pcm_music(os.path.join(usrdir, p))]

        def one_track(path):
            source = os.path.join(usrdir, path)
            target = os.path.join(out, 'music', *path.split('/'))
            meta = pack_music.up_to_date(source, target, args.music_quality)
            return path, meta if meta is not None else pack_music.encode(source, target, args.music_quality, music_ffmpeg)

        start = time.time()
        metas = {}
        with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, args.video_jobs)) as pool:
            for path, meta in pool.map(one_track, tracks):
                metas[path] = meta
        with_samples = []
        for path in paths:
            with_samples.append(path)
            if path not in metas:
                continue
            folder, _, name = path.rpartition('/')
            entry = files[path]
            music_disc += entry['size']
            entry['music'] = True
            entry['head'] = metas[path]['files'][name]  # the bytes the pack has of it (the RWS header)
            side_path = path + '.OGV'
            files[side_path] = {'size': metas[path]['files'][name + '.OGV'], 'mtime': entry['mtime'], 'raw': True,
                                'music': True}
            music_sent += entry['head'] + files[side_path]['size']
            with_samples.append(side_path)
        paths = with_samples
        print('pack.py: music: %d files, %.0f MB on the disc -> %.0f MB (Vorbis, quality %g; %.0f s)' %
              (len(metas), music_disc / MB, music_sent / MB, args.music_quality, time.time() - start), flush=True)

    # ---- the manifest ----------------------------------------------------------------------------------------------------
    raw_total = packed_total = best_total = 0
    for path in packed:
        entry = files[path]
        blob = entry['blob']
        entry['zsize'] = os.path.getsize(os.path.join(out, 'blob', blob + '.zst'))
        base_path = base_of(path)
        if base_path in files and files[base_path]['blob'] != blob:
            base = files[base_path]['blob']
            target = os.path.join(out, 'blob', '%s.from.%s.zst' % (blob, base))
            if os.path.isfile(target):
                size = os.path.getsize(target)
                if size < entry['zsize'] * 0.9:
                    entry['delta'] = {'base': base, 'zsize': size}
                else:  # not worth a second file: remembered so a later run does not compress it again
                    os.remove(target)
                    open(target + '.no', 'w').close()
        if by_hash[blob] == path:
            raw_total += entry['size']
            packed_total += entry['zsize']
            best_total += entry['delta']['zsize'] if 'delta' in entry else entry['zsize']
    manifest = {'version': 1, 'levels': levels, 'files': files}
    with open(os.path.join(out, 'manifest.json'), 'w', encoding='utf-8') as f:
        json.dump(manifest, f, separators=(',', ':'))

    lines = []
    dirs = set()
    for path in paths:
        parts = path.split('/')
        for depth in range(1, len(parts)):
            d = '/'.join(parts[:depth])
            if d not in dirs:
                dirs.add(d)
                lines.append('D\t' + d)
        lines.append('F\t%d\t%d\t%s' % (files[path]['size'], files[path]['mtime'], path))
    with open(os.path.join(out, 'usrdir.manifest'), 'w', encoding='utf-8', newline='\n') as f:
        f.write('\n'.join(lines) + '\n')

    print('pack.py: to download: %.0f MB as on the disc -> %.0f MB compressed, %.0f MB with the differences' %
          (raw_total / MB, packed_total / MB, best_total / MB))
    if ffmpeg:
        print('pack.py: videos: %.0f MB on the disc -> %.0f MB streamed with one voice language (VP9, crf %d)' %
              (video_disc / MB, video_sent / MB, args.video_crf))
    as_is = sum(files[p]['size'] for p in paths if 'raw' in files[p] and 'video' not in files[p] and 'music' not in files[p])
    print('pack.py: streamed as on the disc: %.0f MB. Levels: %s' % (as_is / MB, ' '.join(levels)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
