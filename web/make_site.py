#!/usr/bin/env python3
"""make_site.py - turns the pack (pack.py) and the web build into a folder a static web host can serve as it is
(Netlify, Cloudflare Pages, ...): README.md, "The site folder".

    python make_site.py [--pack FOLDER] [--web FOLDER] [--out FOLDER] [--usrdir PATH]

What a static host asks for, and how the folder meets it:
  - no file over 25 MiB (Cloudflare Pages), and large files served badly: nothing in the folder is over 16 MiB;
  - at most 1,000 files in a drag-and-drop upload (Cloudflare Pages): small things that go together are stored
    one after the other in a shared stream;
  - no reliance on HTTP range requests (not every static host answers them): the page only ever fetches whole
    files of the folder;
  - the cross-origin isolation the game's threads need: the `_headers` file both hosts read.

The folder:
  index.html dotd.js dotd.wasm sw.js pack-worker.js zstddec.js zstddec.wasm   the page (from --web)
  _headers 404.html                                                            for the host
  pack/manifest.json     every file the game can ask for and where its bytes are (below)
  pack/usrdir.manifest   the listing the game's file layer reads
  pack/s/<stream>.<n>    the data: a stream is a run of bytes cut into parts of a fixed size (the first part may
                         be shorter, so that a video's header does not cost a whole part). A stream's name is a
                         hash of its bytes, so a part never changes and the host may cache it for ever.

manifest.json (version 2): "streams": {name: [bytes, part size, first part's size]}; a file's "loc": [stream, offset,
length] says where its bytes are: a blob's compressed bytes (and "delta"."loc" its difference form), a video's or the
music's own bytes. Streams: one per blob and per video; the voice tracks of one language together, in the videos'
order; the music's samples together; the music files' headers together; the one-second video strips together.

Nothing of the game's own folder is changed; the pack folder is only read. A run after a change of the pack
writes only the streams that changed (the record of what was written is <out>.state.json, next to the folder).
"""
import argparse
import hashlib
import json
import os
import re
import shutil
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
_up = HERE
for _ in range(5):  # the repository's per-process memory cap for helper scripts (work/memguard.py)
    if os.path.isfile(os.path.join(_up, 'work', 'memguard.py')):
        sys.path.insert(0, os.path.join(_up, 'work'))
        import memguard  # noqa: F401
        break
    _up = os.path.dirname(_up)

MB = 1048576
BLOB_PART = 16 * MB      # a blob is downloaded whole: parts as large as a host takes without trouble
VIDEO_PART = 4 * MB      # a video may be streamed: a part is what a read waits for
VIDEO_FIRST = 256 * 1024  # its header and first second: what opening it waits for
MUSIC_PART = 2 * MB
WEB_FILES = ['index.html', 'dotd.js', 'dotd.wasm', 'sw.js', 'pack-worker.js', 'zstddec.js', 'zstddec.wasm']
PAGE_FILES = ['index.html', 'sw.js', 'pack-worker.js']  # not built: taken from this folder, where they are edited

HEADERS = '''# The game runs on threads (SharedArrayBuffer): the page must be cross-origin isolated.
/*
  Cross-Origin-Opener-Policy: same-origin
  Cross-Origin-Embedder-Policy: require-corp
  Cross-Origin-Resource-Policy: same-origin

# A stream's name is a hash of its bytes: a part never changes.
/pack/s/*
  Cache-Control: public, max-age=31536000, immutable
'''

NOT_FOUND = '''<!doctype html>
<meta charset="utf-8">
<title>Not found</title>
<p>Not found.</p>
'''


class Stream:
    """A run of bytes made of source files (or pieces of them), written as parts."""

    def __init__(self, key, part, first=0):
        self.key = key
        self.part = part
        self.first = first
        self.sources = []  # (path, bytes to take from its start)
        self.size = 0

    def add(self, path, length=None):
        length = os.path.getsize(path) if length is None else length
        offset = self.size
        self.sources.append((path, length))
        self.size += length
        return offset, length

    def identity(self):
        return json.dumps([self.key, self.part, self.first,
                           [(p, n, os.stat(p).st_mtime_ns, os.path.getsize(p)) for p, n in self.sources]])

    def part_sizes(self):
        sizes = []
        left = self.size
        if self.first and left > 0:
            sizes.append(min(self.first, left))
            left -= sizes[-1]
        while left > 0:
            sizes.append(min(self.part, left))
            left -= sizes[-1]
        return sizes

    def write(self, folder):
        """Writes the parts under temporary names, then names them after the hash of the whole. Returns the name."""
        digest = hashlib.sha1()
        sizes = self.part_sizes()
        temp = os.path.join(folder, 'tmp-%s' % hashlib.sha1(self.identity().encode()).hexdigest()[:16])
        source = iter(self.sources)
        current = None
        left_in_source = 0
        for k, size in enumerate(sizes):
            with open('%s.%d' % (temp, k), 'wb') as out:
                need = size
                while need > 0:
                    if left_in_source == 0:
                        if current is not None:
                            current.close()
                        path, left_in_source = next(source)
                        current = open(path, 'rb')
                        if left_in_source == 0:
                            continue
                    data = current.read(min(need, left_in_source, 4 * MB))
                    if not data:
                        raise RuntimeError('%s is shorter than the pack says' % path)
                    out.write(data)
                    digest.update(data)
                    need -= len(data)
                    left_in_source -= len(data)
        if current is not None:
            current.close()
        name = digest.hexdigest()[:20]
        for k in range(len(sizes)):
            os.replace('%s.%d' % (temp, k), os.path.join(folder, '%s.%d' % (name, k)))
        return name


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    builds = os.path.join(os.path.dirname(HERE), 'build')
    ap.add_argument('--pack', default=os.path.join(builds, 'web-data'), help='the pack folder (pack.py --out)')
    ap.add_argument('--web', default=os.path.join(builds, 'wasm'), help='the built page (dotd.js, dotd.wasm, ...)')
    ap.add_argument('--out', default=os.path.join(builds, 'site'), help='the folder to write')
    ap.add_argument('--usrdir', help="the game's USRDIR, only for videos or music the pack did not re-encode")
    args = ap.parse_args()
    pack, web, out = (os.path.abspath(p) for p in (args.pack, args.web, args.out))
    with open(os.path.join(pack, 'manifest.json'), encoding='utf-8') as f:
        manifest = json.load(f)
    files = manifest['files']
    for name in WEB_FILES:
        if name not in PAGE_FILES and not os.path.isfile(os.path.join(web, name)):
            raise SystemExit('make_site.py: %s is missing in %s: build the web version first (build_wasm.bat)' % (name, web))
    usrdir = args.usrdir
    if not usrdir and any(e.get('raw') and not e.get('video') and not e.get('music') for e in files.values()):
        sys.path.insert(0, HERE)
        import serve
        usrdir = serve.find_usrdir(None)

    # ---- the streams ---------------------------------------------------------------------------------------------
    streams = {}   # key -> Stream
    places = []    # (set: a function taking [stream name, offset, length]), stream key, offset, length

    def stream(key, part, first=0):
        if key not in streams:
            streams[key] = Stream(key, part, first)
        return streams[key]

    def place(setter, key, offset, length):
        places.append((setter, key, offset, length))

    placed = {}  # (stream key, source path) -> (offset, length): the same bytes are stored once per stream
    for path in sorted(files):
        entry = files[path]
        if 'blob' in entry:
            key = ('blob', entry['blob'])
            if key not in streams:
                stream(key, BLOB_PART).add(os.path.join(pack, 'blob', entry['blob'] + '.zst'))
            place(lambda loc, e=entry: e.__setitem__('loc', loc), key, 0, streams[key].size)
            if 'delta' in entry:
                key = ('delta', entry['blob'], entry['delta']['base'])
                if key not in streams:
                    stream(key, BLOB_PART).add(os.path.join(pack, 'blob', '%s.from.%s.zst' % (entry['blob'], entry['delta']['base'])))
                place(lambda loc, e=entry: e['delta'].__setitem__('loc', loc), key, 0, streams[key].size)
            continue
        length = None
        if entry.get('video'):
            source = os.path.join(pack, 'video', *path.split('/'))
            side = re.search(r'\.VID\.(A\d\d)$', path, re.I)
            if side:
                s = stream(('voice', side.group(1).upper()), VIDEO_PART)
            elif entry['size'] < VIDEO_FIRST:
                s = stream(('strips',), VIDEO_PART)
            else:
                s = stream(('video', path), VIDEO_PART, VIDEO_FIRST)
        elif entry.get('music'):
            source = os.path.join(pack, 'music', *path.split('/'))
            if 'head' in entry:
                s = stream(('heads',), MUSIC_PART)
                length = entry['head']
            else:
                s = stream(('music',), MUSIC_PART)
        else:  # streamed as it is on the disc (the pack was made without re-encoding it)
            if not usrdir:
                raise SystemExit('make_site.py: %s is not in the pack: give --usrdir PATH' % path)
            source = os.path.join(usrdir, *path.split('/'))
            s = stream(('raw', path), VIDEO_PART, VIDEO_FIRST)
        same = (s.key, entry.get('store') or path)
        if same not in placed:
            placed[same] = s.add(source, length)
        place(lambda loc, e=entry: e.__setitem__('loc', loc), s.key, *placed[same])

    # ---- write what changed ------------------------------------------------------------------------------------------
    folder = os.path.join(out, 'pack', 's')
    os.makedirs(folder, exist_ok=True)
    state_path = out.rstrip('/\\') + '.state.json'
    try:
        with open(state_path, encoding='utf-8') as f:
            state = json.load(f)
    except (OSError, ValueError):
        state = {}
    names = {}
    new_state = {}
    written = 0
    for n, (key, s) in enumerate(sorted(streams.items(), key=lambda item: str(item[0]))):
        identity = s.identity()
        name = state.get(identity)
        sizes = s.part_sizes()
        if name is None or any(not os.path.isfile(os.path.join(folder, '%s.%d' % (name, k))) or
                               os.path.getsize(os.path.join(folder, '%s.%d' % (name, k))) != size
                               for k, size in enumerate(sizes)):
            name = s.write(folder)
            written += s.size
        names[key] = name
        new_state[identity] = name
    wanted = set()
    stream_table = {}
    for key, s in streams.items():
        stream_table[names[key]] = [s.size, s.part, s.first]
        for k in range(len(s.part_sizes())):
            wanted.add('%s.%d' % (names[key], k))
    for name in os.listdir(folder):
        if name not in wanted:
            os.remove(os.path.join(folder, name))
    with open(state_path, 'w', encoding='utf-8') as f:
        json.dump(new_state, f)
    for setter, key, offset, length in places:
        setter([names[key], offset, length])

    # ---- the manifest, the page, the host's files ------------------------------------------------------------------
    with open(os.path.join(out, 'pack', 'manifest.json'), 'w', encoding='utf-8') as f:
        json.dump({'version': 2, 'levels': manifest['levels'], 'streams': stream_table, 'files': files}, f,
                  separators=(',', ':'))
    shutil.copyfile(os.path.join(pack, 'usrdir.manifest'), os.path.join(out, 'pack', 'usrdir.manifest'))
    for name in WEB_FILES:
        shutil.copyfile(os.path.join(HERE if name in PAGE_FILES else web, name), os.path.join(out, name))
    with open(os.path.join(out, '_headers'), 'w', encoding='utf-8', newline='\n') as f:
        f.write(HEADERS)
    with open(os.path.join(out, '404.html'), 'w', encoding='utf-8', newline='\n') as f:
        f.write(NOT_FOUND)

    count = total = largest = 0
    for folder_path, _, names_here in os.walk(out):
        for name in names_here:
            size = os.path.getsize(os.path.join(folder_path, name))
            count += 1
            total += size
            largest = max(largest, size)
    print('make_site.py: %s' % out)
    print('make_site.py: %d files, %.0f MB, the largest %.1f MB; %d streams, %.0f MB written this run' %
          (count, total / MB, largest / MB, len(streams), written / MB))
    if count > 1000:
        print('make_site.py: NOTE: over 1,000 files: Cloudflare Pages takes this folder with Wrangler, not by drag and drop')
    if largest > 25 * MB:
        print('make_site.py: NOTE: a file over 25 MiB: Cloudflare Pages will refuse it')
    return 0


if __name__ == '__main__':
    sys.exit(main())
