#!/usr/bin/env python3
"""serve.py - local server for the web build of dotd (dotd.js / dotd.wasm / index.html).

    python serve.py [--usrdir PATH] [--port 8080] [--dir FOLDER]
    python serve.py --site FOLDER [--port 8081] [--rate MBIT] [--no-range] [--lan]

It serves two things on 127.0.0.1 only:
  /                  the page and the wasm build (the folder this script is in, or --dir)
  /usrdir/...        the game's own PS3_GAME/USRDIR folder, read straight from disk, unchanged and read-only
                     (GET / HEAD with byte ranges; nothing is copied, converted or written)
  /usrdir.manifest   a listing of that folder (one line per directory or file: size, time, path), which the
                     page fetches once so the game can stat and list files without a request each
  /shader-variants.txt  the native build's shader variant list when this machine has one (its cache folder,
                     %LOCALAPPDATA%/dotd/cache or ~/.cache/dotd; read-only): the page adds its lines to the web
                     build's own list, so the levels played natively get their shaders built on the loading screen

--site FOLDER serves a site folder (make_site.py) the way a static web host would: the folder's files and nothing
else, no game folder. --rate sends the folder's pack over one connection of that many megabits per second (all
responses share it); --no-range answers a range request with the whole file, as a host that does not know them.

--usrdir defaults to DOTD_USRDIR, then to the "usrdir = ..." line of a dotd.ini (current folder, this folder,
the native build folders next to it).

Every response carries the cross-origin isolation headers the wasm build needs for its threads
(SharedArrayBuffer): Cross-Origin-Opener-Policy / Cross-Origin-Embedder-Policy.

POST /diag takes the performance reports of the page's ?diag (index.html, README.md "Diagnostics"): appended to
--diag-dir/<session>.jsonl (default dotd/build/diag), one console line each.
"""
import argparse
import os
import json
import posixpath
import re
import sys
import threading
import time
import urllib.parse
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

HERE = os.path.dirname(os.path.abspath(__file__))

# The repository's per-process memory cap for helper scripts (work/memguard.py), when this runs from a checkout.
_up = HERE
for _ in range(5):
    if os.path.isfile(os.path.join(_up, 'work', 'memguard.py')):
        sys.path.insert(0, os.path.join(_up, 'work'))
        import memguard  # noqa: F401
        break
    _up = os.path.dirname(_up)

CHUNK = 1 << 20
MIME = {
    '.html': 'text/html; charset=utf-8',
    '.js': 'text/javascript; charset=utf-8',
    '.mjs': 'text/javascript; charset=utf-8',
    '.wasm': 'application/wasm',
    '.json': 'application/json',
    '.css': 'text/css; charset=utf-8',
    '.map': 'application/json',
    '.png': 'image/png',
    '.ico': 'image/x-icon',
    '.txt': 'text/plain; charset=utf-8',
    '.svg': 'image/svg+xml',
    '.webmanifest': 'application/manifest+json',
}


def find_usrdir(explicit):
    if explicit:
        return explicit
    if os.environ.get('DOTD_USRDIR'):
        return os.environ['DOTD_USRDIR']
    folders = [os.getcwd(), HERE]
    builds = os.path.dirname(HERE)  # dotd/build when this is dotd/build/wasm/serve.py; dotd when it is dotd/web
    for preset in ('windows-msvc', 'windows-msvc-x86-parity'):
        for config in ('Release', 'RelWithDebInfo', 'Debug'):
            folders.append(os.path.join(builds, preset, config))
            folders.append(os.path.join(builds, 'build', preset, config))
    for folder in folders:
        ini = os.path.join(folder, 'dotd.ini')
        if not os.path.isfile(ini):
            continue
        with open(ini, encoding='utf-8', errors='replace') as f:
            for line in f:
                key, _, value = line.partition('=')
                if key.strip() == 'usrdir' and value.strip():
                    return value.strip()
    return None


def native_variant_list():
    """The native build's shader variant list file, or None."""
    folders = []
    if os.environ.get('LOCALAPPDATA'):
        folders.append(os.path.join(os.environ['LOCALAPPDATA'], 'dotd', 'cache'))
    folders.append(os.path.join(os.path.expanduser('~'), '.cache', 'dotd'))
    for folder in folders:
        path = os.path.join(folder, 'shader-variants.txt')
        if os.path.isfile(path):
            return path
    return None


def build_manifest(root):
    """D<tab>path / F<tab>size<tab>mtime<tab>path, parents before children, forward slashes."""
    lines = []
    for folder, dirs, files in os.walk(root):
        dirs.sort()
        rel = os.path.relpath(folder, root).replace(os.sep, '/')
        prefix = '' if rel == '.' else rel + '/'
        for name in dirs:
            lines.append('D\t%s%s' % (prefix, name))
        for name in sorted(files):
            try:
                st = os.stat(os.path.join(folder, name))
            except OSError:
                continue
            lines.append('F\t%d\t%d\t%s%s' % (st.st_size, int(st.st_mtime), prefix, name))
    return ('\n'.join(lines) + '\n').encode('utf-8')


DIAG_MAX_BYTES = 4 << 20
# dotd/build/diag, from dotd/web (the source) or dotd/build/wasm (the copy the build makes)
DEFAULT_DIAG_DIR = os.path.join(HERE, '..', 'build', 'diag') if os.path.basename(HERE) == 'web' else os.path.join(HERE, '..', 'diag')


def diag_summary(report):
    """One console line for a /diag report."""
    if report.get('type') == 'device':
        ua = report.get('uaData') or {}
        return 'device %s, %s cores, %s GB, GPU %s, canvas %s, profiler %s, timer queries %s' % (
            ua.get('model') or report.get('userAgent', '?')[:60], report.get('cores'), report.get('memoryGB'),
            report.get('glRenderer'), report.get('canvas'), report.get('profiler'), report.get('timerQuery'))
    if report.get('type') == 'gputest':
        rows = sorted((r for r in report.get('results', []) if r.get('name') != 'baseline'),
                      key=lambda r: r.get('msSaved') or 0, reverse=True)
        return 'GPU test, frame time saved: ' + '; '.join(
            '%s %.1f ms (%s fps)' % (r['name'], r.get('msSaved') or 0, r.get('fps')) for r in rows[:8])
    if report.get('type') != 'window':
        return report.get('type', '?')
    cpu = (report.get('frames') or {}).get('cpu') or {}
    line = '%s %5.1f fps, cpu %s ms/frame (p90 %s), cpu %s%%' % (
        report.get('level') or '-', report.get('fps', 0), cpu.get('avg', '-'), cpu.get('p90', '-'), report.get('cpuPct'))
    if report.get('gpuKnown'):
        line += ', gpu late %d%%' % round(100 * report['gpuBehind'] / report['gpuKnown'])
    profile = report.get('profile')
    if profile and profile.get('samples'):
        n = profile['samples']
        line += ', main busy %d%%; top: %s' % (round(100 * (1 - profile['idle'] / n)), ', '.join(
            '%s %d%%' % (name[:40], round(100 * count / n)) for name, count in profile['self'][:3]))
    if not report.get('visible', True):
        line += ' (page hidden)'
    return line


class Handler(BaseHTTPRequestHandler):
    protocol_version = 'HTTP/1.1'  # keep-alive: the game makes many range requests
    web_root = HERE
    usrdir = None
    site = False       # --site: web_root is a site folder, served as a static host would
    no_range = False   # --no-range: range requests get the whole file
    pack_rate = 0      # --rate: bytes per second for the site's pack (0 = as fast as it goes)
    rate_lock = threading.Lock()
    rate_free = 0.0    # --rate: when the connection is free again (one budget for all responses)
    manifest = b''
    quiet = True
    diag_dir = ''      # where /diag reports go (--diag-dir)
    diag_lock = threading.Lock()

    def log_message(self, fmt, *args):
        if not self.quiet:
            sys.stderr.write('%s %s\n' % (self.address_string(), fmt % args))

    def end_headers(self):
        self.send_header('Cross-Origin-Opener-Policy', 'same-origin')
        self.send_header('Cross-Origin-Embedder-Policy', 'require-corp')
        self.send_header('Cross-Origin-Resource-Policy', 'same-origin')
        self.send_header('Document-Policy', 'js-profiling')  # the page's ?diag may run the browser's sampling profiler
        super().end_headers()

    def do_POST(self):
        """/diag: a performance report of the page's ?diag (index.html), appended to <diag dir>/<session>.jsonl."""
        if urllib.parse.urlsplit(self.path).path != '/diag':
            return self.fail(HTTPStatus.NOT_FOUND)
        try:
            length = int(self.headers.get('Content-Length', '0'))
        except ValueError:
            length = -1
        if not 0 < length <= DIAG_MAX_BYTES:
            return self.fail(HTTPStatus.BAD_REQUEST)
        body = self.rfile.read(length)
        try:
            report = json.loads(body)
        except ValueError:
            return self.fail(HTTPStatus.BAD_REQUEST)
        session = re.sub(r'[^0-9A-Za-z-]', '', str(report.get('session', '')))[:40] or 'unknown'
        os.makedirs(self.diag_dir, exist_ok=True)
        with Handler.diag_lock:
            with open(os.path.join(self.diag_dir, session + '.jsonl'), 'ab') as f:
                f.write(json.dumps(report, separators=(',', ':')).encode('utf-8') + b'\n')
        print('diag %s %s: %s' % (session, self.client_address[0], diag_summary(report)), flush=True)
        self.send_response(HTTPStatus.NO_CONTENT)
        self.send_header('Content-Length', '0')
        self.end_headers()

    def fail(self, status):
        body = ('%d %s\n' % (status.value, status.phrase)).encode()
        self.send_response(status)
        self.send_header('Content-Type', 'text/plain; charset=utf-8')
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        if self.command != 'HEAD':
            self.wfile.write(body)

    def resolve(self, root, rel):
        """The file for a URL path below root, or None: no '..', no drive or absolute parts, inside root."""
        parts = [p for p in posixpath.normpath('/' + rel).split('/') if p]
        if any(p in ('.', '..') or ':' in p or '\\' in p for p in parts):
            return None
        full = os.path.realpath(os.path.join(root, *parts))
        base = os.path.realpath(root)
        if full != base and not full.startswith(base + os.sep):
            return None
        return full

    def do_HEAD(self):
        self.do_GET()

    def do_GET(self):
        path = urllib.parse.unquote(urllib.parse.urlsplit(self.path).path)
        if path == '/usrdir.manifest' and not self.site:
            self.send_response(HTTPStatus.OK)
            self.send_header('Content-Type', 'text/plain; charset=utf-8')
            self.send_header('Content-Length', str(len(self.manifest)))
            self.send_header('Cache-Control', 'no-store')
            self.end_headers()
            if self.command != 'HEAD':
                self.wfile.write(self.manifest)
            return
        if self.site:  # a static host: the folder's files, and its _headers rule for the pack's parts
            full = self.resolve(self.web_root, 'index.html' if path == '/' else path[1:])
            cache = 'public, max-age=31536000, immutable' if path.startswith('/pack/s/') else 'no-cache'
        elif path.startswith('/usrdir/'):
            if not self.usrdir:
                return self.fail(HTTPStatus.NOT_FOUND)
            full = self.resolve(self.usrdir, path[len('/usrdir/'):])
            cache = 'no-store'  # the game's files never go into the browser's disk cache
        elif path == '/shader-variants.txt':
            full = native_variant_list()
            cache = 'no-store'
        else:
            if path == '/':
                path = '/index.html'
            full = self.resolve(self.web_root, path[1:])
            cache = 'no-cache'  # a rebuilt dotd.wasm is picked up on reload
        if not full or not os.path.isfile(full):
            return self.fail(HTTPStatus.NOT_FOUND)
        size = os.path.getsize(full)
        start, end = 0, size - 1
        status = HTTPStatus.OK
        spec = None if self.no_range else self.headers.get('Range')
        if spec and spec.startswith('bytes=') and ',' not in spec:
            first, _, last = spec[6:].partition('-')
            try:
                if first:
                    start = int(first)
                    end = min(int(last), size - 1) if last else size - 1
                else:  # the last N bytes
                    start = max(0, size - int(last))
            except ValueError:
                return self.fail(HTTPStatus.BAD_REQUEST)
            if start > end or start >= size:
                self.send_response(HTTPStatus.REQUESTED_RANGE_NOT_SATISFIABLE)
                self.send_header('Content-Range', 'bytes */%d' % size)
                self.send_header('Content-Length', '0')
                self.end_headers()
                return
            status = HTTPStatus.PARTIAL_CONTENT
        length = end - start + 1
        self.send_response(status)
        self.send_header('Content-Type', MIME.get(os.path.splitext(full)[1].lower(), 'application/octet-stream'))
        self.send_header('Content-Length', str(length))
        self.send_header('Accept-Ranges', 'bytes')
        self.send_header('Cache-Control', cache)
        if status == HTTPStatus.PARTIAL_CONTENT:
            self.send_header('Content-Range', 'bytes %d-%d/%d' % (start, end, size))
        self.end_headers()
        if self.command == 'HEAD':
            return
        try:
            # --rate: the site's pack shares one connection of that speed.
            rate = self.pack_rate if self.site and path.startswith('/pack/') else 0
            step = max(4096, rate // 40) if rate else CHUNK
            with open(full, 'rb') as f:
                f.seek(start)
                left = length
                while left > 0:
                    data = f.read(min(step, left))
                    if not data:
                        break
                    if rate:
                        with Handler.rate_lock:
                            begin = max(time.monotonic(), Handler.rate_free)
                            Handler.rate_free = begin + len(data) / rate
                            wait = Handler.rate_free - time.monotonic()
                        if wait > 0:
                            time.sleep(wait)
                    self.wfile.write(data)
                    left -= len(data)
        except (BrokenPipeError, ConnectionResetError, ConnectionAbortedError):
            pass


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--usrdir', help="the game's PS3_GAME/USRDIR folder (read-only)")
    ap.add_argument('--port', type=int, default=8080)
    ap.add_argument('--dir', default=HERE, help='folder with index.html, dotd.js, dotd.wasm')
    ap.add_argument('--site', help='serve this site folder (make_site.py) as a static web host would')
    ap.add_argument('--rate', '--pack-rate', dest='rate', type=float, default=0, metavar='MBIT',
                    help="--site: send the site's pack over one connection of this many megabits per second")
    ap.add_argument('--no-range', action='store_true', help='--site: answer range requests with the whole file')
    ap.add_argument('--lan', action='store_true',
                    help='--site: answer every device on this network (a phone), not only this computer')
    ap.add_argument('--verbose', action='store_true', help='log every request')
    ap.add_argument('--diag-dir', default=DEFAULT_DIAG_DIR, help="where the page's ?diag reports go (POST /diag)")
    args = ap.parse_args()
    Handler.diag_dir = os.path.abspath(args.diag_dir)

    if args.site:
        Handler.site = True
        Handler.web_root = os.path.abspath(args.site)
        Handler.no_range = args.no_range
        Handler.pack_rate = int(args.rate * 1000000 / 8)
        Handler.quiet = not args.verbose
        if not os.path.isfile(os.path.join(Handler.web_root, 'pack', 'manifest.json')):
            print('serve.py: %s is not a site folder (make_site.py writes one)' % Handler.web_root, file=sys.stderr)
            return 1
        server = ThreadingHTTPServer(('0.0.0.0' if args.lan else '127.0.0.1', args.port), Handler)
        server.daemon_threads = True
        print('serve.py: site   %s%s%s' % (Handler.web_root, ', %g Mbit/s' % args.rate if args.rate else '',
                                          ', no range requests' if args.no_range else ''))
        print('serve.py: open http://localhost:%d/ in Chrome (Ctrl+C stops)' % args.port, flush=True)
        if args.lan:
            # --lan: the folder is served to the whole local network while this runs. A browser only gives a page
            # threads and a service worker on a "secure" address: https, or localhost. The address below is
            # neither, so the phone's browser has to be told to trust it (README.md "Trying it on a phone").
            import socket
            try:
                addresses = sorted(set(a for a in socket.gethostbyname_ex(socket.gethostname())[2]
                                       if not a.startswith('127.')))
            except OSError:
                addresses = []
            for address in addresses:
                print('serve.py: on this network: http://%s:%d/' % (address, args.port))
            if not addresses:
                print('serve.py: on this network: http://<this computer\'s address>:%d/' % args.port)
            print('serve.py: a phone needs that address marked as secure first (dotd/web/README.md, '
                  '"Trying it on a phone")', flush=True)
        try:
            server.serve_forever()
        except KeyboardInterrupt:
            pass
        return 0
    usrdir = find_usrdir(args.usrdir)
    if not usrdir or not os.path.isdir(usrdir):
        print('serve.py: no game folder (%r). Give --usrdir PATH (your PS3_GAME/USRDIR).' % usrdir, file=sys.stderr)
        return 1
    Handler.web_root = os.path.abspath(args.dir)
    Handler.usrdir = os.path.abspath(usrdir)
    Handler.manifest = build_manifest(Handler.usrdir)
    Handler.quiet = not args.verbose
    server = ThreadingHTTPServer(('127.0.0.1', args.port), Handler)
    server.daemon_threads = True
    print('serve.py: page   %s' % Handler.web_root)
    print('serve.py: usrdir %s (%d entries, read-only)' % (Handler.usrdir, Handler.manifest.count(b'\n')))
    print('serve.py: open http://localhost:%d/ in Chrome (Ctrl+C stops)' % args.port, flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    return 0


if __name__ == '__main__':
    sys.exit(main())
