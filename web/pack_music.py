#!/usr/bin/env python3
"""pack_music.py - re-encodes one of the game's music files for the web pack (README.md, "Music"); used by pack.py.

    python pack_music.py SOURCE.RWS OUT.RWS [--quality 5] [--ffmpeg PATH]

The disc's music (MUSIC/nn/STRAnnn.RWS) is a RenderWare Audio stream of 16-bit PCM, 48 kHz stereo: 1.5 Mbit/s
for as long as it plays. This writes:

  OUT.RWS       the source's first bytes up to its sample data (the RWS header: the game reads the stream's
                items and their lengths from it, so its timing does not change). The pack lists the file with
                the source's size; nothing reads past the header in the web build.
  OUT.RWS.OGV   the samples of the first layer, each item (RWS segment) re-encoded as Vorbis (lossy, quality
                --quality): 'DVOR', version, item count; per item 32 bytes (sample rate, channels, frames (u64),
                bytes of decoder setup, packet count, offset (u64) of the item's data); an item's data is the
                setup (FFmpeg's "extradata": 2, the first two headers' sizes Xiph-laced, the three headers), the
                packets' sizes (u16 each), then the packets. The web build's music player decodes it
                (platform/audio/rwa_stream.cpp).
  OUT.RWS.json  what it was made from, so a later run can skip it.

The encoder is an ffmpeg with libvorbis from the PATH (or --ffmpeg); it gets the samples on its standard input.
Vorbis has no encoder delay: the first sample decoded is the item's first, and the player stops after the
item's frame count, so an item that loops still meets its own start.
"""
import argparse
import json
import os
import shutil
import struct
import subprocess
import sys

VERSION = 1


def find_ffmpeg(explicit=None):
    path = explicit or shutil.which('ffmpeg')
    if not path:
        return None
    try:
        out = subprocess.run([path, '-hide_banner', '-encoders'], capture_output=True, text=True, timeout=60).stdout
    except (OSError, subprocess.SubprocessError):
        return None
    return path if 'libvorbis' in out else None


PCM_GUID = bytes([0xd0, 0x1b, 0xd2, 0x17, 0x35, 0x87, 0x4e, 0xed, 0xb9, 0xd9, 0xb8, 0xe8, 0x6e, 0xa9, 0xb9, 0x95])


def read_rws(f):
    """The header of an RWS file (platform/audio/rws.cpp, RwsFile::Open): its data offset, segments and layers."""
    top = f.read(0x18)
    if len(top) != 0x18 or struct.unpack_from('<I', top, 0)[0] != 0x80d or struct.unpack_from('<I', top, 0xc)[0] != 0x80e:
        raise ValueError('not an RWS file')
    header_size, = struct.unpack_from('<I', top, 0x10)
    b = f.read(header_size)
    chunk = f.read(12)
    if len(b) != header_size or len(chunk) != 12 or struct.unpack_from('<I', chunk, 0)[0] != 0x80f:
        raise ValueError('malformed RWS header')
    nseg, = struct.unpack_from('>I', b, 0x20)
    nlay, = struct.unpack_from('>I', b, 0x28)

    def name_at(at):
        end = b.index(b'\0', at)
        return at + (((end + 1 - at) + 15) & ~15)

    at = name_at(0x50)
    segments = []
    for s in range(nseg):
        segments.append({'bytes': struct.unpack_from('>I', b, at + 0x18)[0], 'offset': struct.unpack_from('>I', b, at + 0x1c)[0],
                         'usable': []})
        at += 0x20
    for s in range(nseg):
        for l in range(nlay):
            segments[s]['usable'].append(struct.unpack_from('>I', b, at)[0])
            at += 4
    at += 0x10 * nseg
    for s in range(nseg):
        at = name_at(at)
    layers = []
    for l in range(nlay):
        layers.append({'block': struct.unpack_from('>I', b, at + 0x10)[0], 'usable': struct.unpack_from('>I', b, at + 0x20)[0],
                       'start': struct.unpack_from('>I', b, at + 0x24)[0]})
        at += 0x28
    for l in range(nlay):
        layers[l].update({'rate': struct.unpack_from('>I', b, at)[0], 'bits': b[at + 0xc], 'channels': b[at + 0xd],
                          'codec': b[at + 0x1c:at + 0x2c]})
        at += 0x30
    return {'data': 0x24 + header_size, 'segments': segments, 'layers': layers}


def is_pcm_music(path):
    try:
        with open(path, 'rb') as f:
            rws = read_rws(f)
    except (OSError, ValueError, struct.error):
        return False
    y = rws['layers'][0]
    return y['codec'] == PCM_GUID and y['bits'] == 16 and y['channels'] in (1, 2) and y['usable'] >= 2 * y['channels']


def segment_pcm(f, rws, s):
    """The first layer's samples of segment s, as stored (16-bit big-endian, interleaved)."""
    y = rws['layers'][0]
    seg = rws['segments'][s]
    stride = sum(l['block'] for l in rws['layers'])
    frame = 2 * y['channels']
    total = seg['usable'][0] - seg['usable'][0] % frame
    out = bytearray()
    block = 0
    while len(out) < total:
        n = min(y['usable'], total - len(out))
        f.seek(rws['data'] + seg['offset'] + y['start'] + block * stride)
        part = f.read(n)
        if len(part) != n:
            raise ValueError('the file ends inside segment %d' % s)
        out += part
        block += 1
    return bytes(out)


def ogg_packets(data):
    """The packets of an Ogg stream with one logical stream."""
    packets = []
    current = bytearray()
    at = 0
    while at + 27 <= len(data):
        if data[at:at + 4] != b'OggS':
            raise ValueError('not an Ogg page')
        nsegs = data[at + 26]
        lacing = data[at + 27:at + 27 + nsegs]
        at += 27 + nsegs
        for size in lacing:
            current += data[at:at + size]
            at += size
            if size < 255:
                packets.append(bytes(current))
                current = bytearray()
    return packets


def xiph_lace(n):
    return b'\xff' * (n // 255) + bytes([n % 255])


def up_to_date(source, out_main, quality):
    try:
        with open(out_main + '.json', encoding='utf-8') as f:
            meta = json.load(f)
    except (OSError, ValueError):
        return None
    st = os.stat(source)
    if (meta.get('version') != VERSION or meta.get('quality') != quality or meta.get('source_size') != st.st_size or
            meta.get('source_mtime') != int(st.st_mtime)):
        return None
    for name, size in meta['files'].items():
        path = os.path.join(os.path.dirname(out_main), name)
        if not os.path.isfile(path) or os.path.getsize(path) != size:
            return None
    return meta


def encode(source, out_main, quality, ffmpeg):
    os.makedirs(os.path.dirname(out_main), exist_ok=True)
    with open(source, 'rb') as f:
        rws = read_rws(f)
        y = rws['layers'][0]
        if y['codec'] != PCM_GUID or y['bits'] != 16:
            raise ValueError('%s: not 16-bit PCM' % source)
        f.seek(0)
        head = f.read(rws['data'])
        items = []
        for s in range(len(rws['segments'])):
            pcm = segment_pcm(f, rws, s)
            frames = len(pcm) // (2 * y['channels'])
            if frames == 0:
                items.append((0, b'', []))
                continue
            done = subprocess.run([ffmpeg, '-hide_banner', '-loglevel', 'error', '-f', 's16be', '-ar', str(y['rate']),
                                   '-ac', str(y['channels']), '-i', 'pipe:0', '-c:a', 'libvorbis', '-q:a', str(quality),
                                   '-map_metadata', '-1', '-fflags', '+bitexact', '-f', 'ogg', 'pipe:1'],
                                  input=pcm, capture_output=True)
            if done.returncode != 0:
                raise RuntimeError('ffmpeg failed on %s: %s' % (source, done.stderr.decode('utf-8', 'replace')[-400:]))
            packets = ogg_packets(done.stdout)
            if len(packets) < 4 or packets[0][:7] != b'\x01vorbis' or packets[2][:7] != b'\x05vorbis':
                raise RuntimeError('%s: unexpected encoder output' % source)
            setup = b'\x02' + xiph_lace(len(packets[0])) + xiph_lace(len(packets[1])) + packets[0] + packets[1] + packets[2]
            audio = packets[3:]
            if max(len(p) for p in audio) > 65535:
                raise RuntimeError('%s: a packet over 64 KB' % source)
            items.append((frames, setup, audio))

    table = 12 + 32 * len(items)
    body = bytearray()
    entries = []
    for frames, setup, audio in items:
        entries.append(struct.pack('<IIQIIQ', y['rate'], y['channels'], frames, len(setup), len(audio), table + len(body)))
        body += setup
        body += struct.pack('<%dH' % len(audio), *[len(p) for p in audio])
        for p in audio:
            body += p
    with open(out_main + '.tmp', 'wb') as f:
        f.write(head)
    os.replace(out_main + '.tmp', out_main)
    side = out_main + '.OGV'
    with open(side + '.tmp', 'wb') as f:
        f.write(struct.pack('<4sII', b'DVOR', VERSION, len(items)) + b''.join(entries) + body)
    os.replace(side + '.tmp', side)
    st = os.stat(source)
    seconds = sum(frames for frames, _, _ in items) / y['rate']
    meta = {'version': VERSION, 'quality': quality, 'source_size': st.st_size, 'source_mtime': int(st.st_mtime),
            'items': len(items), 'seconds': seconds,
            'files': {os.path.basename(out_main): len(head), os.path.basename(side): os.path.getsize(side)}}
    with open(out_main + '.json', 'w', encoding='utf-8') as f:
        json.dump(meta, f, indent=1)
    return meta


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('source')
    ap.add_argument('out')
    ap.add_argument('--quality', type=float, default=5)
    ap.add_argument('--ffmpeg')
    args = ap.parse_args()
    ffmpeg = find_ffmpeg(args.ffmpeg)
    if not ffmpeg:
        raise SystemExit('pack_music.py: no ffmpeg with libvorbis found (PATH or --ffmpeg)')
    print(json.dumps(encode(os.path.abspath(args.source), os.path.abspath(args.out), args.quality, ffmpeg), indent=1))
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
