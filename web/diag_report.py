#!/usr/bin/env python3
"""diag_report.py - reads the performance reports of the page's ?diag (serve.py writes them to dotd/build/diag) and
says where the time goes, comparing the slow stretches with the fast ones (README.md "Diagnostics").

    python diag_report.py [SESSION.jsonl ...] [--slow FPS] [--top N]

Without a file: the newest session in dotd/build/diag. A window is one 5 s report; windows with the page hidden or
with fewer than 3 game frames (loading screens, a paused tab) are left out of the comparison.

  timeline    per window: level, fps, the main thread's ms per game frame (avg / p90), how often the GPU had not
              finished the previous frame when the next began ("gpu late"), how busy the main thread was (profiler
              samples with a stack), draws per frame (the game's gfxstats line), the three functions with the most
              self samples
  GPU test    (the page's "GPU test" button) the frame time each switch saves: a lower resolution, each render stage
              off; and the measured frames' segments (gpuprof lines: a glFinish at each stage's ends)
  slow / fast the windows under / at or over --slow fps (default 30) side by side: frame time, GPU lateness,
              draws, and per function the share of the main thread's samples, self (the function itself) and total
              (it or what it calls), sorted by how much more of the slow windows' time it takes
"""
import argparse
import glob
import json
import os
import re
import sys
from collections import Counter

HERE = os.path.dirname(os.path.abspath(__file__))
DIAG_DIR = os.path.join(HERE, '..', 'build', 'diag')
GFX = re.compile(r'gfxstats @\d+: (\d+) frames, wall ([\d.]+) ms.*?gpu ([\d.]+) ms, swap ([\d.]+) ms \| per frame: '
                 r'draws ([\d.]+).*?programs ([\d.]+), uniforms ([\d.]+).*?texbinds ([\d.]+).*?buffers ([\d.]+) \(([\d.]+) KB\)')


SEG = re.compile(r'gpuprof seg (.+?): ([\d.]+) ms \(gpu wait ([\d.]+)\), draws ([\d.]+)(?: \| (.*))?$')
HEAD = re.compile(r'gpuprof: (\d+) measured frames.*?frame ([\d.]+) ms.*?drain ([\d.]+) ms, finish cost ([\d.]+) ms')


def gpu_sections(windows, tests):
    """The GPU test reports and the measured frames' segments (gpuprof lines)."""
    for test in tests:
        print('\nGPU test (%d switches; frame time saved against the baselines next to each):' % (
            len([r for r in test['results'] if r['name'] != 'baseline'])))
        print('   ms saved    fps  baseline  gpu late  switch')
        rows = sorted((r for r in test['results'] if r['name'] != 'baseline'), key=lambda r: r.get('msSaved') or 0,
                      reverse=True)
        for r in rows:
            print('  %8.2f  %5.1f  %8.1f  %8s  %s' % (r.get('msSaved') or 0, r['fps'], r.get('baselineFps') or 0,
                                                    '%d%%' % r['gpuLate'] if r.get('gpuLate') is not None else '-',
                                                    r['name']))
        base = [r['fps'] for r in test['results'] if r['name'] == 'baseline']
        print('  baselines: %s fps' % ', '.join('%.1f' % b for b in base))
    heads, segs = [], {}
    for w in windows:
        for line in w.get('logs') or []:
            m = HEAD.search(line)
            if m:
                heads.append([float(x) for x in m.groups()])
            m = SEG.search(line)
            if m:
                s = segs.setdefault(m.group(1), {'ms': [], 'wait': [], 'draws': [], 'items': m.group(5) or ''})
                s['ms'].append(float(m.group(2)))
                s['wait'].append(float(m.group(3)))
                s['draws'].append(float(m.group(4)))
    if not heads:
        return
    avg = lambda v: sum(v) / len(v)
    print('\nmeasured frames (gpuprof, %d reports): frame %.2f ms, previous frame drain %.2f ms, finish cost %.3f ms' % (
        len(heads), avg([h[1] for h in heads]), avg([h[2] for h in heads]), avg([h[3] for h in heads])))
    print('  (a segment absent from a report counts 0 there)')
    print('       ms  gpu wait   draws  segment | items per frame')
    n = len(heads)
    for name, s in sorted(segs.items(), key=lambda kv: sum(kv[1]['ms']), reverse=True):
        print('  %7.2f  %8.2f  %6.1f  %s%s' % (sum(s['ms']) / n, sum(s['wait']) / n, sum(s['draws']) / n, name,
                                             ' | ' + s['items'][:110] if s['items'] else ''))


def load(paths):
    device, windows, tests = None, [], []
    for path in paths:
        with open(path, encoding='utf-8') as f:
            for line in f:
                try:
                    r = json.loads(line)
                except ValueError:
                    continue
                if r.get('type') == 'device':
                    device = r
                elif r.get('type') == 'window':
                    windows.append(r)
                elif r.get('type') == 'gputest':
                    tests.append(r)
    return device, windows, tests


def gfx_of(window):
    """The game's gfxstats averages in this window's log lines (frames-weighted), or None."""
    rows = []
    for line in window.get('logs') or []:
        m = GFX.search(line)
        if m:
            rows.append([float(x) for x in m.groups()])
    if not rows:
        return None
    n = sum(r[0] for r in rows)
    keys = ['frames', 'wall', 'gpu', 'swap', 'draws', 'programs', 'uniforms', 'texbinds', 'buffers', 'bufferKB']
    out = {k: sum(r[i] * r[0] for r in rows) / n for i, k in enumerate(keys) if i}
    out['frames'] = n
    return out


def busy(window):
    p = window.get('profile')
    return 1 - p['idle'] / p['samples'] if p and p.get('samples') else None


def pct(x):
    return '-' if x is None else '%3.0f%%' % (100 * x)


def group(windows):
    """Totals of a set of windows: frame time, GPU lateness, gfx, and function samples."""
    frames = sum((w['frames']['cpu'] or {}).get('n', 0) for w in windows if w['frames'].get('cpu'))
    cpu_ms = sum((w['frames']['cpu'] or {}).get('avg', 0) * (w['frames']['cpu'] or {}).get('n', 0)
                 for w in windows if w['frames'].get('cpu'))
    span = sum(w['spanMs'] for w in windows) / 1000.0
    late = sum(w.get('gpuBehind', 0) for w in windows)
    known = sum(w.get('gpuKnown', 0) for w in windows)
    self_c, total_c = Counter(), Counter()
    samples = idle = 0
    for w in windows:
        p = w.get('profile')
        if not p:
            continue
        samples += p['samples']
        idle += p['idle']
        self_c.update(dict(p['self']))
        total_c.update(dict(p['total']))
    gfx = [g for g in (gfx_of(w) for w in windows) if g]
    gn = sum(g['frames'] for g in gfx)
    gfx_avg = {k: sum(g[k] * g['frames'] for g in gfx) / gn for k in gfx[0]} if gn else None
    return {'windows': len(windows), 'seconds': span, 'fps': frames / span if span else 0,
            'cpu': cpu_ms / frames if frames else None, 'gpuLate': late / known if known else None,
            'busy': 1 - idle / samples if samples else None, 'samples': samples, 'self': self_c, 'total': total_c,
            'gfx': gfx_avg}


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('files', nargs='*')
    ap.add_argument('--slow', type=float, default=30.0, help='a window under this many fps is slow (default 30)')
    ap.add_argument('--top', type=int, default=30, help='functions listed per table (default 30)')
    args = ap.parse_args()
    paths = args.files
    if not paths:
        found = sorted(glob.glob(os.path.join(DIAG_DIR, '*.jsonl')), key=os.path.getmtime)
        if not found:
            sys.exit('diag_report.py: no reports in %s (open the page with ?diag)' % os.path.abspath(DIAG_DIR))
        paths = [found[-1]]
    device, windows, tests = load(paths)
    print('sessions: %s' % ', '.join(os.path.basename(p) for p in paths))
    if device:
        ua = device.get('uaData') or {}
        print('device: %s (%s), %s cores, %s GB, dpr %s, screen %s, canvas %s shown at %s CSS px' % (
            ua.get('model') or '?', device.get('userAgent', '')[:90], device.get('cores'), device.get('memoryGB'),
            device.get('dpr'), device.get('screen'), device.get('canvas'), device.get('canvasCss')))
        print('GPU: %s / %s; timer queries %s; profiler %s; vsync %s, fps cap %s' % (
            device.get('glVendor'), device.get('glRenderer'), device.get('timerQuery'), device.get('profiler'),
            device.get('vsync'), device.get('fpsCap')))

    print('\ntimeline (one 5 s window a line):')
    print('   t(s) level   fps  cpu ms avg/p90  gpu late  main busy  draws  top self functions')
    t0 = windows[0]['t'] if windows else 0
    used = []
    for w in windows:
        cpu = w['frames'].get('cpu') or {}
        g = gfx_of(w)
        known = w.get('gpuKnown', 0)
        p = w.get('profile')
        top = ''
        if p and p.get('samples'):
            top = ', '.join('%s %d%%' % (name[:34], round(100 * c / p['samples'])) for name, c in p['self'][:3])
        flag = '' if w.get('visible', True) else ' (hidden)'
        print('%7.0f %-6s %5.1f  %6s / %-6s  %8s  %9s  %5s  %s%s' % (
            (w['t'] - t0) / 1000, w.get('level') or '-', w.get('fps', 0), cpu.get('avg', '-'), cpu.get('p90', '-'),
            pct(w.get('gpuBehind', 0) / known) if known else '-', pct(busy(w)), '%.0f' % g['draws'] if g else '-',
            top, flag))
        if w.get('visible', True) and cpu.get('n', 0) >= 3:
            used.append(w)

    slow = [w for w in used if w.get('fps', 0) < args.slow]
    fast = [w for w in used if w.get('fps', 0) >= args.slow]
    print('\nslow (< %g fps): %d windows; fast: %d windows' % (args.slow, len(slow), len(fast)))
    gs, gf = group(slow), group(fast)
    for label, g in (('slow', gs), ('fast', gf)):
        if not g['windows']:
            continue
        x = g['gfx']
        print('  %-4s %5.1f fps, main thread %s ms per frame, busy %s, gpu late %s%s' % (
            label, g['fps'], '%.2f' % g['cpu'] if g['cpu'] is not None else '-', pct(g['busy']), pct(g['gpuLate']),
            '; per frame: draws %.0f, programs %.0f, uniforms %.0f, texbinds %.0f, buffers %.0f (%.0f KB), '
            'gpu %.2f ms' % (x['draws'], x['programs'], x['uniforms'], x['texbinds'], x['buffers'], x['bufferKB'],
                             x['gpu']) if x else ''))

    for kind in ('self', 'total'):
        print('\n%s: share of all main-thread samples (slow vs fast), sorted by slow minus fast' % kind)
        ns, nf = gs['samples'] or 1, gf['samples'] or 1
        names = set(n for n, _ in gs[kind].most_common(200)) | set(n for n, _ in gf[kind].most_common(200))
        rows = sorted(((gs[kind][n] / ns, gf[kind][n] / nf, n) for n in names), key=lambda r: r[0] - r[1], reverse=True)
        print('   slow   fast   function')
        for s, f, n in rows[:args.top]:
            print('  %5.1f%% %5.1f%%  %s' % (100 * s, 100 * f, n[:120]))
    gpu_sections(windows, tests)


if __name__ == '__main__':
    main()
