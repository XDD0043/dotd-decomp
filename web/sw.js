// sw.js - the service worker of the web build's download mode (README.md, "Download mode", "The site folder").
// The game reads its files with range requests to usrdir/<path> (platform/web/hostfs_web.cpp). This worker answers
// them from the site's pack (pack/manifest.json, version 2, written by make_site.py):
//   - a file the pack lists as a blob comes from the browser's private file system, where pack-worker.js stored
//     its content; while it is not stored the answer is 503 and the download worker is told to fetch it now (the
//     game's file layer asks again until it is there);
//   - a video or the music is never waited for: it comes from the store when the download worker fetched it
//     ahead, and otherwise from the pack's parts (pack/s/<stream>.<n>), which are only ever fetched whole: a static
//     host need not answer range requests. A few parts are kept in memory, so a file read piece by piece costs one
//     fetch per part. Of a music file the pack holds only the header ("head"): the rest reads as zeros (its
//     samples are the re-encoded "<file>.OGV" next to it).
// Without a pack (pack/manifest.json missing) everything goes to the network: the page then reads a USRDIR that
// serve.py serves.
'use strict';

const FOLDER = 'dotd-blob';
const KEPT_PARTS = 8;
const channel = new BroadcastChannel('dotd-pack');
let manifestPromise = null;   // {files, streams, lower: Map} or null without a pack
let folderPromise = null;
const stored = new Map();     // store name -> File (a stored file is never changed once it is whole)
const told = new Set();       // paths already announced as "seen"
const parts = new Map();      // "stream.n" -> Promise<Uint8Array>, the most recently used last
let streamNoted = 0;          // when the download worker was last told that a video is being streamed

self.addEventListener('install', () => self.skipWaiting());
self.addEventListener('activate', (event) => event.waitUntil(self.clients.claim()));

channel.onmessage = (event) => {
  const type = event.data && event.data.type;
  if (type === 'cleared') stored.clear();
  if (type === 'reset') {  // a page started: the pack may have been made again since this worker read it
    manifestPromise = null;
    stored.clear();
    told.clear();
    parts.clear();
  }
};

function scopePath() { return new URL(self.registration.scope).pathname; }

function getManifest() {
  if (!manifestPromise) {
    manifestPromise = fetch(scopePath() + 'pack/manifest.json', {cache: 'no-store'}).then(async (response) => {
      if (!response.ok) return null;
      const manifest = await response.json();
      if (manifest.version !== 2) return null;
      const lower = new Map();
      for (const path of Object.keys(manifest.files)) lower.set(path.toLowerCase(), path);
      return {files: manifest.files, streams: manifest.streams, lower};
    }).catch(() => null);
  }
  return manifestPromise;
}

async function storedFile(name) {
  const known = stored.get(name);
  if (known) return known;
  if (!folderPromise) {
    folderPromise = navigator.storage.getDirectory().then((root) => root.getDirectoryHandle(FOLDER, {create: true}));
  }
  const folder = await folderPromise;
  try {
    await folder.getFileHandle(name + '.ok');  // the marker: the content is whole
    const file = await (await folder.getFileHandle(name)).getFile();
    stored.set(name, file);
    return file;
  } catch (error) {
    return null;
  }
}

// One part of a stream, whole.
function getPart(stream, n) {
  const key = stream + '.' + n;
  let part = parts.get(key);
  if (part) {
    parts.delete(key);  // (the most recently used last)
  } else {
    part = fetch(scopePath() + 'pack/s/' + key).then(async (response) => {
      if (!response.ok) throw new Error('HTTP ' + response.status + ' for ' + key);
      return new Uint8Array(await response.arrayBuffer());
    });
    part.catch(() => { if (parts.get(key) === part) parts.delete(key); });
    while (parts.size >= KEPT_PARTS) parts.delete(parts.keys().next().value);
  }
  parts.set(key, part);
  return part;
}

// Bytes [from, to) of a stream into `into` at `at`.
async function readStream(manifest, stream, from, to, into, at) {
  const size = manifest.streams[stream][1], first = manifest.streams[stream][2];
  while (from < to) {
    const n = first ? (from < first ? 0 : 1 + Math.floor((from - first) / size)) : Math.floor(from / size);
    const start = first ? (n === 0 ? 0 : first + (n - 1) * size) : n * size;
    const part = await getPart(stream, n);
    const count = Math.min(to - from, part.length - (from - start));
    if (count <= 0) throw new Error('stream ' + stream + ' is shorter than the manifest says');
    into.set(part.subarray(from - start, from - start + count), at);
    from += count;
    at += count;
  }
}

// The part of the file the request asks for: {start, end, status} or a 416 response.
function rangeOf(request, size) {
  let start = 0, end = size - 1, status = 200;
  const range = /^bytes=(\d*)-(\d*)$/.exec(request.headers.get('Range') || '');
  if (range && (range[1] !== '' || range[2] !== '')) {
    if (range[1] === '') {
      start = Math.max(0, size - parseInt(range[2], 10));
    } else {
      start = parseInt(range[1], 10);
      if (range[2] !== '') end = Math.min(end, parseInt(range[2], 10));
    }
    if (start > end || start >= size) {
      return {refused: new Response('', {status: 416, headers: {'Content-Range': 'bytes */' + size}})};
    }
    status = 206;
  }
  return {start, end, status};
}

function answer(request, size, range, body) {
  const headers = {
    'Content-Type': 'application/octet-stream',
    'Content-Length': String(range.end - range.start + 1),
    'Accept-Ranges': 'bytes',
    'Cache-Control': 'no-store',
  };
  if (range.status === 206) headers['Content-Range'] = 'bytes ' + range.start + '-' + range.end + '/' + size;
  return new Response(request.method === 'HEAD' ? null : body, {status: range.status, headers});
}

function fromFile(request, file) {
  const range = rangeOf(request, file.size);
  return range.refused || answer(request, file.size, range, file.slice(range.start, range.end + 1));
}

async function serve(request, path) {
  const manifest = await getManifest();
  if (!manifest) return fetch(request);
  const real = manifest.lower.get(path.toLowerCase());
  if (!real) return new Response('', {status: 404});
  const entry = manifest.files[real];
  if (!told.has(real)) {
    told.add(real);
    channel.postMessage({type: 'seen', path: real});
  }
  if (entry.blob) {
    const file = await storedFile(entry.blob);
    if (!file) {
      channel.postMessage({type: 'need', path: real});
      return new Response('', {status: 503, headers: {'Retry-After': '1', 'Cache-Control': 'no-store'}});
    }
    return fromFile(request, file);
  }
  // A video or the music: from the store when it was fetched ahead, else from the pack's parts.
  const file = entry.store ? await storedFile(entry.store) : null;
  if (file) return fromFile(request, file);
  if (entry.video && Date.now() - streamNoted > 1000) {  // (the download worker gives way while a video streams)
    streamNoted = Date.now();
    channel.postMessage({type: 'streaming', path: real});
  }
  const range = rangeOf(request, entry.size);
  if (range.refused) return range.refused;
  const body = new Uint8Array(range.end - range.start + 1);  // (zeros where the pack has nothing: past a "head")
  const have = Math.min(entry.loc[2], entry.size);
  if (request.method !== 'HEAD' && range.start < have) {
    try {
      await readStream(manifest, entry.loc[0], entry.loc[1] + range.start, entry.loc[1] + Math.min(range.end + 1, have), body, 0);
    } catch (error) {
      return new Response('', {status: 502, headers: {'Cache-Control': 'no-store'}});
    }
  }
  return answer(request, entry.size, range, body);
}

self.addEventListener('fetch', (event) => {
  const url = new URL(event.request.url);
  const prefix = scopePath() + 'usrdir/';
  if (url.origin !== self.location.origin || !url.pathname.startsWith(prefix)) return;  // not a game file: the network
  event.respondWith(serve(event.request, decodeURIComponent(url.pathname.slice(prefix.length))));
});
