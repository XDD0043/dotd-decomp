// pack-worker.js - the download worker of the web build's download mode (README.md, "Download mode").
// It fetches the game's files as the compressed blobs pack.py made, decodes them (zstddec.wasm) and stores the
// content in the browser's private file system (OPFS folder "dotd-blob", one file per blob, named by its hash,
// with an empty "<hash>.ok" beside it once it is whole). sw.js answers the game's reads from those files.
// Where a file's bytes are in the site folder is its "loc" in pack/manifest.json ([stream, offset, length]: see
// make_site.py); a stream's parts (pack/s/<stream>.<n>) are only ever fetched whole.
//
// What it downloads, in this order of urgency:
//   0  a file the game is waiting for right now (sw.js says so on the "dotd-pack" channel)
//   1  the boot set, which the page waits for before it starts the game; then (1.5) the front end's videos
//      in the order they play (the loading strip, the logos, the title and menu backgrounds) and the other
//      short strips, which the page does not wait for
//   2  the rest of the level being played (its sectors)
//   3  the next level, while this one is played
//   4  the story video after the furthest one the game has opened (the first one before any), with the voice
//      track of the language in use (re-encoded videos only: stored as they are, no zstd; a video that is not
//      stored when it starts is streamed, never waited for)
// A blob that exists as a difference against a blob already stored is fetched in that form (smaller).
// Two downloads run at a time at most; the first lane is kept for urgency 0 and 1. On a connection measured
// below 8 Mbit/s, everything above urgency 1 stands still while the game streams a video, so that the video
// gets it.
'use strict';
importScripts('zstddec.js');

const FOLDER = 'dotd-blob';
const channel = new BroadcastChannel('dotd-pack');
let base = '';              // the pack folder's URL
let manifest = null;        // pack/manifest.json
const lowerPaths = new Map();  // lower-case path -> path as in the manifest
let folder = null;          // the OPFS directory
const have = new Set();     // blobs stored whole
const queue = [];           // {path, blob, priority, order, tries}
const active = new Map();   // blob -> {path, got, total, priority}
const lanes = [{busy: false, module: null, maxPriority: 1}, {busy: false, module: null, maxPriority: 9}];
let order = 0;
let lang = null;            // "00".."09": the language prefix of the localisation files the game opens
let level = null;           // "010": the level whose main file the game opened last
let bootPaths = null;       // the boot set while the page waits for it
let storyPaths = [];        // the re-encoded videos with voice tracks (the story's scenes), in order
let furthest = -1;          // the furthest of them the game has opened (index in storyPaths)
let voice = null;           // ".A01": the suffix of the voice track file the game opened last
let videoStreamedAt = -1e9; // when sw.js last passed a video's range request on to the network
let rate = 0;               // bytes per second the downloads got lately (0 = not measured yet)
let rateBytes = 0, rateSince = 0;
const SLOW = 1000000;       // bytes per second: below this the downloads give way to a streamed video
// The videos the game plays from its start to the main menu, in that order: the loading strip, the four logos,
// the title background, the menu background (watched on a start; they are in GAME.KP3's list, not in a level).
const FRONT_END = ['MOVIE/00/PS3_005.VID', 'MOVIE/06/PS3_065.VID', 'MOVIE/07/PS3_071.VID', 'MOVIE/07/PS3_072.VID',
                   'MOVIE/07/PS3_073.VID', 'MOVIE/00/PS3_003.VID', 'MOVIE/00/PS3_004.VID'];
let lastReport = 0;

function log(text) { self.postMessage({type: 'log', text: 'pack: ' + text}); }

function entryOf(path) {
  const real = lowerPaths.get(path.toLowerCase());
  return real ? [real, manifest.files[real]] : [null, null];
}

function report(force) {
  const now = performance.now();
  if (!force && now - lastReport < 200) return;
  lastReport = now;
  const items = [];
  for (const info of active.values()) items.push({path: info.path, got: info.got, total: info.total, priority: info.priority});
  let queuedBytes = 0;
  for (const item of queue) {
    const entry = manifest.files[item.path];
    queuedBytes += entry.store ? entry.size : entry.delta && have.has(entry.delta.base) ? entry.delta.zsize : entry.zsize;
  }
  self.postMessage({type: 'progress', items, queued: queue.length, queuedBytes});
}

function enqueue(path, priority) {
  const [real, entry] = entryOf(path);
  const id = entry && (entry.blob || entry.store);  // a blob, or a re-encoded video the store may keep
  if (!id || have.has(id)) return;
  const running = active.get(id);
  if (running) {
    running.priority = Math.min(running.priority, priority);
    return;
  }
  const queued = queue.find((item) => item.blob === id);
  if (queued) queued.priority = Math.min(queued.priority, priority);
  else queue.push({path: real, blob: id, priority, order: order++, tries: 0});
}

// The downloads' speed (all lanes together), over half a second at a time; `end`: the lanes went idle, and what
// was counted since the last time is used if it is enough to tell.
function measure(bytes, end) {
  const now = performance.now();
  if (rateSince === 0) rateSince = now;
  rateBytes += bytes;
  if (now - rateSince >= 500 || (end && rateBytes >= 262144 && now > rateSince)) {
    rate = rateBytes * 1000 / (now - rateSince);
    rateBytes = 0;
    rateSince = now;
  }
  if (end) {  // (idle time is not part of the next measurement)
    rateBytes = 0;
    rateSince = 0;
  }
}

// On a slow connection the downloads that fetch ahead stand still while the game streams a video (sw.js says
// so with every range it passes on): the connection is the video's.
async function giveWay(info) {
  let waited = false;
  while (info.priority > 1 && rate > 0 && rate < SLOW && performance.now() - videoStreamedAt < 10000) {
    waited = true;
    await new Promise((resolve) => setTimeout(resolve, 250));
  }
  if (waited) {  // (the wait is not part of the next measurement)
    rateBytes = 0;
    rateSince = 0;
  }
}

function pump() {
  for (const lane of lanes) {
    if (lane.busy) continue;
    let best = -1;
    for (let i = 0; i < queue.length; ++i) {
      const item = queue[i];
      if (item.priority > lane.maxPriority) continue;
      if (best < 0 || item.priority < queue[best].priority ||
          (item.priority === queue[best].priority && item.order < queue[best].order)) best = i;
    }
    if (best < 0) continue;
    const item = queue.splice(best, 1)[0];
    lane.busy = true;
    download(lane, item).catch((error) => {
      log('download of ' + item.path + ' failed: ' + (error && error.message ? error.message : error));
      item.tries += 1;
      setTimeout(() => {  // tried again: at once a few times, then every 5 s
        if (!have.has(item.blob) && !queue.some((q) => q.blob === item.blob)) queue.push(item);
        pump();
      }, item.tries < 3 ? 500 : 5000);
    }).finally(() => {
      lane.busy = false;
      if (lanes.every((l) => !l.busy)) measure(0, true);
      report(true);
      checkBoot();
      pump();
    });
  }
}

// One part of a stream, whole and kept for a while: for the small files that share a stream (the next one wanted
// is mostly in the same part).
const keptParts = new Map();  // "stream.n" -> Promise<Uint8Array>
function keptPart(stream, n) {
  const key = stream + '.' + n;
  let part = keptParts.get(key);
  if (!part) {
    part = fetch(base + 's/' + key, {cache: 'no-store'}).then(async (response) => {
      if (!response.ok) throw new Error('HTTP ' + response.status + ' for ' + key);
      return new Uint8Array(await response.arrayBuffer());
    });
    part.catch(() => keptParts.delete(key));
    while (keptParts.size >= 4) keptParts.delete(keptParts.keys().next().value);
    keptParts.set(key, part);
  }
  return part;
}

// The bytes at a place in the pack ([stream, offset, length]), piece by piece as they arrive. The parts are
// fetched whole, one after the other; `info` is the download's progress record (for giveWay).
async function* chunksOf(loc, info) {
  const [stream, offset, length] = loc;
  const [total, size, first] = manifest.streams[stream];
  const end = offset + length;
  let at = offset;
  while (at < end) {
    const n = first ? (at < first ? 0 : 1 + Math.floor((at - first) / size)) : Math.floor(at / size);
    const start = first ? (n === 0 ? 0 : first + (n - 1) * size) : n * size;
    const partEnd = Math.min(total, start + (first && n === 0 ? first : size));
    const stop = Math.min(end, partEnd);
    await giveWay(info);
    if (length < size / 2) {  // a small file in a shared stream
      const part = await keptPart(stream, n);
      if (part.length < stop - start) throw new Error('a part of ' + stream + ' is short');
      yield part.subarray(at - start, stop - start);
    } else {
      const response = await fetch(base + 's/' + stream + '.' + n, {cache: 'no-store'});
      if (!response.ok) throw new Error('HTTP ' + response.status + ' for ' + stream + '.' + n);
      const reader = response.body.getReader();
      let pos = start;
      for (;;) {
        await giveWay(info);
        const {value, done} = await reader.read();
        if (done) break;
        const from = Math.max(at, pos), to = Math.min(stop, pos + value.length);
        if (to > from) yield value.subarray(from - pos, to - pos);
        pos += value.length;
        if (pos >= stop) {
          if (pos < partEnd) reader.cancel().catch(() => {});
          break;
        }
      }
      if (pos < stop) throw new Error('a part of ' + stream + ' ended early');
    }
    at = stop;
  }
}

// A re-encoded video: fetched as it is from the pack into the store.
async function downloadVideo(item) {
  const entry = manifest.files[item.path];
  const id = entry.store;
  const info = {path: item.path, got: 0, total: entry.size, priority: item.priority};
  active.set(id, info);
  report(true);
  const started = performance.now();
  let handle = null;
  try {
    handle = await (await folder.getFileHandle(id, {create: true})).createSyncAccessHandle();
    handle.truncate(0);
    for await (const value of chunksOf(entry.loc, info)) {
      if (handle.write(value, {at: info.got}) !== value.length) throw new Error('the store is full');
      info.got += value.length;
      measure(value.length);
      report(false);
    }
    if (info.got !== entry.size) throw new Error('the file ended early');
    handle.flush();
    handle.close();
    handle = null;
    await folder.getFileHandle(id + '.ok', {create: true});
    have.add(id);
    log(item.path + ': ' + (entry.size / 1048576).toFixed(1) + ' MB (video, fetched ahead) in ' +
        ((performance.now() - started) / 1000).toFixed(1) + ' s');
    channel.postMessage({type: 'stored', blob: id});
  } finally {
    if (handle) handle.close();
    active.delete(id);
  }
}

async function download(lane, item) {
  const entry = manifest.files[item.path];
  if (entry.store) return downloadVideo(item);
  const blob = entry.blob;
  const delta = entry.delta && have.has(entry.delta.base) ? entry.delta : null;
  const loc = delta ? delta.loc : entry.loc;
  const info = {path: item.path, got: 0, total: delta ? delta.zsize : entry.zsize, priority: item.priority};
  active.set(blob, info);
  report(true);
  const started = performance.now();
  const M = lane.module || (lane.module = await DotdZstd());
  let out = 0, prefix = 0, prefixSize = 0, input = 0, inputSize = 0;
  try {
    out = M._malloc(Math.max(entry.size, 1));
    if (!out) throw new Error('no memory for ' + entry.size + ' bytes');
    if (delta) {  // the base's content, from the store, as the decoder's prefix
      const file = await (await folder.getFileHandle(delta.base)).getFile();
      prefixSize = file.size;
      prefix = M._malloc(Math.max(prefixSize, 1));
      if (!prefix) throw new Error('no memory for the base');
      const reader = file.stream().getReader();
      for (let at = 0;;) {
        const {value, done} = await reader.read();
        if (done) break;
        M.HEAPU8.set(value, prefix + at);
        at += value.length;
      }
    }
    if (M._dotd_zstd_begin(out, entry.size, prefix, prefixSize) !== 0) throw new Error(M.UTF8ToString(M._dotd_zstd_error()));
    let state = 1;
    for await (const value of chunksOf(loc, info)) {
      if (value.length > inputSize) {
        if (input) M._free(input);
        inputSize = Math.max(value.length, 1 << 20);
        input = M._malloc(inputSize);
        if (!input) throw new Error('no memory for the input');
      }
      M.HEAPU8.set(value, input);
      state = M._dotd_zstd_feed(input, value.length);
      if (state < 0) throw new Error('zstd: ' + M.UTF8ToString(M._dotd_zstd_error()));
      info.got += value.length;
      measure(value.length);
      report(false);
    }
    if (state !== 0 || M._dotd_zstd_written() !== entry.size) throw new Error('the blob ended early');
    // Into the store, then the marker that says it is whole.
    const handle = await (await folder.getFileHandle(blob, {create: true})).createSyncAccessHandle();
    try {
      handle.truncate(0);
      const step = 32 << 20;
      for (let at = 0; at < entry.size; at += step) {
        const n = Math.min(step, entry.size - at);
        if (handle.write(M.HEAPU8.subarray(out + at, out + at + n), {at}) !== n) throw new Error('the store is full');
      }
      handle.flush();
    } finally {
      handle.close();
    }
    await folder.getFileHandle(blob + '.ok', {create: true});
    have.add(blob);
    const seconds = (performance.now() - started) / 1000;
    log(item.path + ': ' + (info.total / 1048576).toFixed(1) + ' MB' + (delta ? ' (difference)' : '') + ' -> ' +
        (entry.size / 1048576).toFixed(1) + ' MB in ' + seconds.toFixed(1) + ' s');
    channel.postMessage({type: 'stored', blob});
  } finally {
    if (out) M._free(out);
    if (prefix) M._free(prefix);
    if (input) M._free(input);
    active.delete(blob);
  }
}

// ---- what to fetch ahead -------------------------------------------------------------------------------------
// A level's files for the language in use: the small ones first (they are opened from the game's main thread
// once the level starts), then the main file, then the sectors in order.
function levelPaths(l) {
  const prefix = 'lvl' + l + '/';
  const small = [], main = [], sectors = [];
  for (const path of Object.keys(manifest.files)) {
    if (!path.toLowerCase().startsWith(prefix) || manifest.files[path].raw) continue;
    const rest = path.slice(prefix.length);
    if (/^LVL\d+\.KP3$/i.test(rest)) main.push(path);
    else if (/^STR\d+\.KP3$/i.test(rest)) sectors.push(path);
    else if (/^\d\dLLC\d+\.KP3$/i.test(rest)) { if (lang !== null && rest.slice(0, 2) === lang) small.push(path); }
    else if (/^SPEECH\//i.test(rest)) { if (lang !== null && rest.slice(7).startsWith(parseInt(lang, 10) + '_')) small.push(path); }
    else small.push(path);
  }
  sectors.sort();
  return small.concat(main, sectors);
}

// The video to fetch ahead: the story scene after the furthest one opened so far (they play in the files' order;
// before any was opened, the first), with the voice track of the language in use (until the game has opened
// one: the track of the text language, which is the usual one).
function videosAhead() {
  const list = [];
  const path = storyPaths[furthest + 1];
  if (path) {
    list.push(path);
    const guess = lang !== null ? '.A' + String(parseInt(lang, 10) + 1).padStart(2, '0') : null;
    const side = voice !== null ? voice : guess;
    if (side !== null && manifest.files[path + side]) list.push(path + side);
  }
  return list;
}

function schedule() {
  for (let i = queue.length - 1; i >= 0; --i) {  // the earlier plan's items give way
    if (queue[i].priority >= 2) queue.splice(i, 1);
  }
  if (level !== null) {
    for (const path of levelPaths(level)) enqueue(path, 2);
    const i = manifest.levels.indexOf(level);
    if (i >= 0 && i + 1 < manifest.levels.length) {
      for (const path of levelPaths(manifest.levels[i + 1])) enqueue(path, 3);
    }
  }
  for (const path of videosAhead()) enqueue(path, 4);
  pump();
  report(true);
}

// A path the game asked sw.js for: the language and the level are read off the names.
function seen(path) {
  let m = /^(\d\d)GLC\.KP3$/i.exec(path) || /^LVL\d+\/(\d\d)LLC\d+\.KP3$/i.exec(path);
  if (m && lang !== m[1]) {
    lang = m[1];
    schedule();
  }
  m = /^LVL(\d+)\/LVL\1\.KP3$/i.exec(path);
  if (m && level !== m[1]) {
    level = m[1];
    log('level ' + level + ': fetching its sectors, then the next level');
    schedule();
  }
  m = /\.VID(\.A\d\d)?$/i.exec(path);
  if (m && manifest.files[path] && manifest.files[path].video) {
    for (let i = queue.length - 1; i >= 0; --i) {  // not fetched in time: it is streamed, not downloaded as well
      if (queue[i].path === path) queue.splice(i, 1);
    }
    if (m[1]) {
      if (voice !== m[1]) {
        voice = m[1];
        log('voice track ' + path + (have.has(manifest.files[path].store) ? ' plays from the store' : ' is streamed'));
        schedule();
      }
    } else {
      log('video ' + path + (have.has(manifest.files[path].store) ? ' plays from the store' : ' is streamed'));
      if (storyPaths.indexOf(path) > furthest) {
        furthest = storyPaths.indexOf(path);
        schedule();
      }
    }
  }
}

function checkBoot() {
  if (bootPaths === null) return;
  if (bootPaths.every((path) => { const [, entry] = entryOf(path); return !entry || have.has(entry.blob); })) {
    bootPaths = null;
    self.postMessage({type: 'boot-done'});
  }
}

channel.onmessage = (event) => {
  const message = event.data;
  if (!manifest || !message) return;
  if (message.type === 'need') {
    seen(message.path);
    enqueue(message.path, 0);
    pump();
  } else if (message.type === 'seen') {
    seen(message.path);
  } else if (message.type === 'streaming') {
    videoStreamedAt = performance.now();
  }
};

self.onmessage = async (event) => {
  const message = event.data;
  try {
    if (message.type === 'init') {
      base = message.base;
      manifest = await (await fetch(base + 'manifest.json', {cache: 'no-store'})).json();
      for (const path of Object.keys(manifest.files)) lowerPaths.set(path.toLowerCase(), path);
      storyPaths = Object.keys(manifest.files).filter(
          (path) => manifest.files[path].store && /\.VID$/i.test(path) && manifest.files[path + '.A01']).sort();
      folder = await (await navigator.storage.getDirectory()).getDirectoryHandle(FOLDER, {create: true});
      for await (const name of folder.keys()) {
        if (name.endsWith('.ok')) have.add(name.slice(0, -3));
      }
      let stored = 0;
      const blobs = new Set();
      for (const entry of Object.values(manifest.files)) {
        const id = entry.blob || entry.store;
        if (id && have.has(id) && !blobs.has(id)) {
          blobs.add(id);
          stored += entry.size;
        }
      }
      log('the store has ' + blobs.size + ' file(s), ' + (stored / 1048576).toFixed(0) + ' MB, from earlier visits');
      // The boot set: what the game reads before its first loading screen can show a wait.
      bootPaths = ['GAME.KP3', 'EBOOT.elf'];
      if (manifest.levels.length) bootPaths.push('LVL' + manifest.levels[0] + '/LVL' + manifest.levels[0] + '.KP3');
      for (const path of bootPaths) enqueue(path, 1);
      for (const path of FRONT_END) {
        if (manifest.files[path] && manifest.files[path].store) enqueue(path, 1.5);  // (after the boot set)
      }
      for (const path of Object.keys(manifest.files).sort()) {  // the short strips (a second each): all at once
        const entry = manifest.files[path];
        if (entry.store && /\.VID$/i.test(path) && entry.size < 262144) enqueue(path, 1.5);
      }
      pump();
      report(true);
      checkBoot();
    } else if (message.type === 'clear') {  // the page's "delete downloaded data"
      for await (const name of folder.keys()) await folder.removeEntry(name);
      have.clear();
      channel.postMessage({type: 'cleared'});
      log('the store was emptied');
    }
  } catch (error) {
    self.postMessage({type: 'fatal', text: String(error && error.message ? error.message : error)});
  }
};
