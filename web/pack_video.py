#!/usr/bin/env python3
"""pack_video.py - re-encodes one of the game's videos for the web pack (README.md, "Videos"); used by pack.py.

    python pack_video.py SOURCE.VID OUT.VID [--crf 34] [--ffmpeg PATH]

The disc's videos are Bink 1 at 8 Mbit/s with, for the story scenes, eleven audio tracks in every frame (the
music and effects, then one voice track per language). That is 10 Mbit/s read while a scene plays. This writes:

  OUT.VID        a "DVP9" file: the Bink container's layout (header, track table, frame index; a frame = its
                 audio packets, each a size and the data, then its picture), the picture re-encoded as VP9
                 (lossy, constant quality) and only the first audio track in the frames. Unlike Bink's, the
                 picture has its size in front too: a frame is padded to an even offset, and VP9 reads a
                 packet's last bytes.
  OUT.VID.Ann    one file per other audio track nn (a voice language): 'DVPA', the frame count, an index and the
                 track's packets. The player opens only the one it plays.
  OUT.VID.json   what it was made from (the source's size and time, the quality), so a later run can skip it.

The audio packets are the disc's own (Bink audio, copied byte for byte); only the picture is re-encoded. The
encoder is an ffmpeg with libvpx-vp9 found on the PATH (or --ffmpeg); it reads the source where it is.
The source's keyframes stay keyframes: the game jumps to them (the menu background loops between marked frames),
and a jump to any other frame decodes everything since the keyframe before it.

DVP9 header (little-endian, the fields at Bink's offsets where they have one):
  +0 'DVP9'   +4 file size - 8   +8 frames   +12 the audio tracks kept in the frames (the first N)
  +16 the source's Bink signature (the audio decoders' extradata)   +20 width   +24 height
  +28 frame rate   +32 frame rate divisor   +36 0   +40 audio tracks (as in the source)
  then the source's track table (12 bytes per track) and frames + 1 offsets (bit 0: a keyframe).
"""
import argparse
import json
import os
import shutil
import struct
import subprocess
import sys

VERSION = 2  # of what this writes: a change makes pack.py encode again


def find_ffmpeg(explicit=None):
    path = explicit or shutil.which('ffmpeg')
    if not path:
        return None
    try:
        out = subprocess.run([path, '-hide_banner', '-encoders'], capture_output=True, text=True, timeout=60).stdout
    except (OSError, subprocess.SubprocessError):
        return None
    return path if 'libvpx-vp9' in out else None


def read_bink_header(f):
    head = f.read(44)
    if len(head) != 44 or head[:3] != b'BIK':
        raise ValueError('not a Bink 1 file')
    frames, = struct.unpack_from('<I', head, 8)
    width, height, rate, div, flags, tracks = struct.unpack_from('<6I', head, 20)
    if flags & 0x00100000:
        raise ValueError('a Bink video with an alpha plane is not handled')
    table = f.read(12 * tracks)
    index = struct.unpack('<%dI' % (frames + 1), f.read(4 * (frames + 1)))
    return {'signature': head[:4], 'frames': frames, 'width': width, 'height': height, 'rate': rate, 'div': div,
            'tracks': tracks, 'table': table, 'index': index}


def source_keys(bink):
    """The source's keyframes after the first frame (0-based)."""
    return [n for n in range(1, bink['frames']) if bink['index'][n] & 1]


def up_to_date(source, out_main, crf):
    try:
        with open(out_main + '.json', encoding='utf-8') as f:
            meta = json.load(f)
        with open(source, 'rb') as f:
            keys = source_keys(read_bink_header(f))
    except (OSError, ValueError):
        return None
    st = os.stat(source)
    if (meta.get('version') != VERSION or meta.get('crf') != crf or meta.get('source_size') != st.st_size or
            meta.get('source_mtime') != int(st.st_mtime) or meta.get('forced_keys', []) != keys):
        return None
    for name, size in meta['files'].items():
        path = os.path.join(os.path.dirname(out_main), name)
        if not os.path.isfile(path) or os.path.getsize(path) != size:
            return None
    return meta


def encode(source, out_main, crf, ffmpeg, threads=4, speed=2):
    """Writes out_main and its side files; returns the .json's content."""
    os.makedirs(os.path.dirname(out_main), exist_ok=True)
    ivf = out_main + '.tmp.ivf'
    passlog = out_main + '.tmp.pass'
    common = [ffmpeg, '-hide_banner', '-loglevel', 'error', '-y', '-i', source, '-an', '-c:v', 'libvpx-vp9',
              '-b:v', '0', '-crf', str(crf), '-g', '250', '-deadline', 'good', '-cpu-used', str(speed),
              '-row-mt', '1', '-tile-columns', '1', '-auto-alt-ref', '1', '-lag-in-frames', '25',
              '-pix_fmt', 'yuv420p', '-fps_mode', 'passthrough', '-threads', str(threads), '-passlogfile', passlog]
    with open(source, 'rb') as src:
        forced = source_keys(read_bink_header(src))
    if forced:
        common += ['-force_key_frames', 'expr:' + '+'.join('eq(n,%d)' % n for n in forced)]
    try:
        for args in (['-pass', '1', '-f', 'null', os.devnull], ['-pass', '2', '-f', 'ivf', ivf]):
            done = subprocess.run(common + args, capture_output=True, text=True, stdin=subprocess.DEVNULL)
            if done.returncode != 0:
                raise RuntimeError('ffmpeg failed on %s: %s' % (source, done.stderr.strip()[-600:]))

        with open(source, 'rb') as src, open(ivf, 'rb') as pic:
            bink = read_bink_header(src)
            source_size = os.fstat(src.fileno()).st_size
            frames, tracks = bink['frames'], bink['tracks']
            head = pic.read(32)
            if head[:4] != b'DKIF' or head[8:12] != b'VP90':
                raise RuntimeError('unexpected encoder output for %s' % source)
            pic.seek(struct.unpack_from('<H', head, 6)[0])
            inline = 1 if tracks > 0 else 0
            header = struct.pack('<4s10I', b'DVP9', 0, frames, inline, struct.unpack('<I', bink['signature'])[0],
                                 bink['width'], bink['height'], bink['rate'], bink['div'], 0, tracks)
            data_start = len(header) + len(bink['table']) + 4 * (frames + 1)
            side_names = {t: '%s.A%02d' % (out_main, t) for t in range(inline, tracks)}
            sides = {t: open(name + '.tmp', 'wb') for t, name in side_names.items()}
            side_index = {t: [] for t in sides}
            side_start = 8 + 4 * (frames + 1)
            index = []
            keys = 0
            forced_set = set(forced)
            try:
                for f in sides.values():
                    f.write(b'\0' * side_start)
                with open(out_main + '.tmp', 'wb') as out:
                    out.write(b'\0' * data_start)
                    for n in range(frames):
                        begin, end = bink['index'][n] & ~1, bink['index'][n + 1] & ~1
                        if n == frames - 1 and (end <= begin or end > source_size):
                            end = source_size
                        src.seek(begin)
                        frame = src.read(end - begin)
                        packets = []
                        pos = 0
                        for t in range(tracks):
                            size, = struct.unpack_from('<I', frame, pos)
                            packets.append(frame[pos + 4:pos + 4 + size])
                            pos += 4 + size
                        fh = pic.read(12)
                        if len(fh) != 12:
                            raise RuntimeError('%s: the encoder wrote %d frames, the source has %d' % (source, n, frames))
                        picture = pic.read(struct.unpack_from('<I', fh, 0)[0])
                        # VP9's first byte: marker (2 bits), profile (2), show_existing_frame, frame_type (0 = key)
                        key = (picture[0] & 0xc0) == 0x80 and (picture[0] & 0x0c) == 0
                        if n == 0 and not key:
                            raise RuntimeError('%s: the first frame is not a keyframe' % source)
                        keys += key
                        if n in forced_set and not key:
                            raise RuntimeError('%s: frame %d is a keyframe of the source but not of the encode' %
                                               (source, n))
                        if out.tell() & 1:
                            out.write(b'\0')
                        index.append(out.tell() | (1 if key else 0))
                        for t in range(inline):
                            out.write(struct.pack('<I', len(packets[t])) + packets[t])
                        out.write(struct.pack('<I', len(picture)) + picture)
                        for t, f in sides.items():
                            side_index[t].append(f.tell())
                            f.write(packets[t])
                    if pic.read(1):
                        raise RuntimeError('%s: the encoder wrote more frames than the source has' % source)
                    if out.tell() & 1:
                        out.write(b'\0')
                    total = out.tell()
                    index.append(total)
                    out.seek(0)
                    out.write(header[:4] + struct.pack('<I', total - 8) + header[8:])
                    out.write(bink['table'])
                    out.write(struct.pack('<%dI' % (frames + 1), *index))
                for t, f in sides.items():
                    side_index[t].append(f.tell())
                    f.seek(0)
                    f.write(struct.pack('<4sI', b'DVPA', frames))
                    f.write(struct.pack('<%dI' % (frames + 1), *side_index[t]))
            finally:
                for f in sides.values():
                    f.close()
        os.replace(out_main + '.tmp', out_main)
        for name in side_names.values():
            os.replace(name + '.tmp', name)
    finally:
        for leftover in [ivf, passlog + '-0.log', out_main + '.tmp'] + \
                [name + '.tmp' for name in (side_names.values() if 'side_names' in locals() else [])]:
            if os.path.isfile(leftover):
                os.remove(leftover)

    st = os.stat(source)
    meta = {'version': VERSION, 'crf': crf, 'source_size': st.st_size, 'source_mtime': int(st.st_mtime),
            'frames': frames, 'keyframes': keys, 'forced_keys': forced, 'seconds': frames * bink['div'] / bink['rate'],
            'files': {os.path.basename(p): os.path.getsize(p) for p in [out_main] + list(side_names.values())}}
    with open(out_main + '.json', 'w', encoding='utf-8') as f:
        json.dump(meta, f, indent=1)
    return meta


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('source')
    ap.add_argument('out')
    ap.add_argument('--crf', type=int, default=34)
    ap.add_argument('--ffmpeg')
    args = ap.parse_args()
    ffmpeg = find_ffmpeg(args.ffmpeg)
    if not ffmpeg:
        raise SystemExit('pack_video.py: no ffmpeg with libvpx-vp9 found (PATH or --ffmpeg)')
    meta = encode(os.path.abspath(args.source), os.path.abspath(args.out), args.crf, ffmpeg)
    print(json.dumps(meta, indent=1))
    return 0


if __name__ == '__main__':
    _up = os.path.dirname(os.path.abspath(__file__))
    for _ in range(5):  # the repository's per-process memory cap for helper scripts (work/memguard.py)
        if os.path.isfile(os.path.join(_up, 'work', 'memguard.py')):
            sys.path.insert(0, os.path.join(_up, 'work'))
            import memguard  # noqa: F401
            break
        _up = os.path.dirname(_up)
    sys.exit(main())
