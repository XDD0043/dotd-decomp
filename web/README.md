# dotd on the web (WebAssembly + WebGL2)

The same game code as the native build, compiled with Emscripten to wasm32 and drawn with WebGL2. The page holds
only the game code: the game's files are read from your own `PS3_GAME/USRDIR` on disk, as they are, through the
small local server here. Nothing is converted, packed or copied.

## Build and run

```
tools\build_wasm.bat     ->  build\wasm\{dotd.js, dotd.wasm, index.html, serve.py}
tools\run_wasm.bat       ->  serves it on http://localhost:8080/ and opens the browser
```

- **Toolchain:** the Emscripten SDK in `toolchain\emsdk` (git-ignored), or wherever `EMSDK` points. To fetch it again:
  `git clone https://github.com/emscripten-core/emsdk toolchain\emsdk`, then in that folder `emsdk install latest`
  and `emsdk activate latest`. Built and tested with Emscripten 7.0.0. `tools\build_wasm.bat` sets the environment
  itself (`EMSDK`, which the `wasm` CMake preset's toolchain file path uses); nothing is added to the system PATH.
- **Game files:** `serve.py --usrdir PATH`; without it `DOTD_USRDIR`, then the `usrdir` of a `dotd.ini` (current
  folder, the build folder, the native build folders). `EBOOT.elf` must be in that folder, as for the native build
  (the Cg shader sources are read from it).
- **Options:** URL parameters become command-line options: `http://localhost:8080/?fps=0&lang=3` is
  `dotd --fps 0 --lang 3`. `fps=0` runs one game frame per browser animation frame (the display's refresh, with the
  60 Hz timing calculation of `platform/fps.h`); the default is 60 like the native build.
- **Frame rate counter:** the presented frame rate is drawn in the top right corner of the picture, in the game's
  own font through its own text drawing (`DrawFpsCounter`, CManager2d.cpp). On by default here, `?show-fps=0`
  turns it off; the native build has it too (`--show-fps`, `show_fps = 1` in dotd.ini; off by default).
- **Runs in a hidden window:** `?DOTD_WEB_TICKER=1` takes the animation frames from a worker's timer (a browser
  runs a hidden page's frames and timers once a second), for automated tests.
- **Debug aids:** a URL parameter named `DOTD_...` is an environment variable, as for the native build:
  `?DOTD_GFX_STATS=600` logs frame statistics and every long frame with what it spent ("gfxstats hitch", and
  "web: the game frame took ... of which ... waiting for file reads"); `?DOTD_SHADER_LIST=off` runs without the
  shader variant list; `?DOTD_SHADER_SALT=word` makes every shader new to the browser's shader cache (the timings
  of a first visit). The log is under the picture ("Show log") and in the browser's console.
- **Input:** the same as the native build (SDL: keyboard in RPCS3's default layout, gamepads through the browser's
  Gamepad API). Click the page once so the browser lets the sound start.
- **A first full build** compiles about 1000 files (a few minutes); the link takes under a minute.
  `-DDOTD_WEB_LINK_OPT=-O1` (through `DOTD_WASM_CMAKE_ARGS` before the first configure) links faster.

## Download mode (2026-11-18): the game's files sent by the site

The mode above reads your own USRDIR. A web site's players have no files, so in download mode the level data is
downloaded, kept in the browser and fetched ahead level by level; nobody waits for more than one level's worth.

```
tools\pack_wasm.bat       ->  build\web-data\       the pack (pack.py: about 12 minutes for the level data, 55 for
                              the videos, 1 for the music), then
                              build\site\           the folder a static host serves (make_site.py): 828 files, 3.2 GB
tools\run_wasm_download.bat ->  http://localhost:8081/  serves that folder as a host would (add --rate 50 to send the
                              data over one 50 Mbit/s line, --no-range to answer like a host without range requests)
```

**What is sent how** (`pack.py`; measured on the whole disc):

| Files | On the disc | Sent |
|---|---|---|
| Level data, localisation, speech, cinematic streams (`.KP3`, `SPEECH/*.RWS`, `.KCS`) | 3130 MB | downloaded as zstd blobs: 1634 MB, 1496 MB with the differences; about 1370 MB over a whole playthrough in one language |
| Videos (`.VID`: Bink, 8 to 10 Mbit/s) | 3966 MB | re-encoded (the one lossy step, see "Videos"): 672 MB with one voice language, 1.5 Mbit/s on average; streamed by ranges or fetched ahead into the store |
| Music (`MUSIC/*.RWS`: PCM, 1.5 Mbit/s) | 1547 MB | re-encoded (the other lossy step, see "Music"): 140 MB, 0.15 Mbit/s; streamed while it plays |
| `EBOOT.BIN`, `Shader/` | 86 MB | left out (the port does not read them) |
| `EBOOT.elf` | 12 MB | replaced by zeros of the same size holding only the two Cg shader source texts the renderer reads (40 KB sent): the site ships no executable |

- A file is one zstd frame (level 19, with a checksum). Files with the same content are one blob (each level folder
  holds the same localisation files).
- **Differences:** a level's main file is also compressed against the previous level's, a sector against the
  sector before it (the first against the level's main file); kept when at least 10% smaller. The browser takes
  the difference when it has the base. LVL020: 60 MB alone, 41 MB as a difference; zstd level 15 finds more of a
  far base than 19 does, so both are tried.
- **Before a level can be played** (main file, first sector, its small files): the menu 26 MB; then 126, 74, 95,
  120, 125, 114, 117, 103, 147, 98 and 56 MB for LVL010 .. LVL120. The later sectors (up to 34 MB) follow.

**Videos** (`pack_video.py`, called by `pack.py`; needs an `ffmpeg` with libvpx-vp9 on the PATH or `--ffmpeg`,
else, or with `--video-crf 0`, the videos stay as they are and are streamed at their 8 Mbit/s):

- The disc's 50 videos are 61 minutes of Bink 1 at 8 Mbit/s; the 23 story scenes (1280x544) also carry eleven
  audio tracks in every frame (music and effects, then a voice track per language: 0.12 to 0.25 Mbit/s each), of
  which the game plays two.
- **The picture** is re-encoded as VP9 at a constant quality (`--video-crf`, default 34; two passes; 55 minutes on
  16 threads). On a 20 s action sample of PS3_026: crf 30 gives 2.35 Mbit/s (VMAF 95.9 against the Bink
  picture), 36 gives 1.33 (92.6), 42 gives 0.76 (87.3); 36 and the source were compared by eye. The source's
  keyframes stay keyframes (the menu background loops by jumping to them).
- **The audio** is the disc's own Bink audio, copied packet for packet. The first track stays in the video's
  frames; every other track is a file of its own next to it (`PS3_019.VID.A01` ..), so only the voice language in
  use is fetched.
- **The file** ("DVP9", described in `pack_video.py`) keeps Bink's layout, so the game's player
  (`platform/video/bink.cpp`) reads both; the picture goes to FFmpeg's VP9 decoder (`thirdparty/ffmpeg-bink`).
- **Decoding is on a thread of its own**, up to 12 frames ahead, with the file reads: the game's frame only copies
  a finished picture. When a frame is not there in time (a slow device or connection), the game keeps the last
  one and the video's clock starts again from the late frame, so picture and sound stay together. Before a
  video's first picture is there (one to five frames at every start, more on a slow connection) the game already
  draws the video: its planes start as a black picture (`PS3Video_CreateFrameBuffers`), else that was a green
  screen (planes of zeros). One 1280x720
  frame takes 2.5 ms here in Chromium (2.9 ms without wasm SIMD, which the decoders are built with); that is a
  desktop: **not measured on a phone**, where the two 50 fps backgrounds of the front end are the tight ones.
- **The front end's music is video sound:** the game starts no music stream before a level; what plays on the
  logos and the title screen is those videos' own audio track. It was silent on most starts for a few hours
  (2026-11-18): the game rewinds a video it has just opened, the thread had usually decoded frame 1 by then, and
  a jump to the frame the decoder already holds decoded nothing, so no frame's sound was ever read again. A jump
  now decodes its target again. Checked by measuring the page's audio output: 0.000 on the logos and the title
  before, 0.05 to 0.3 after, on two starts; about 0.03 on the main menu (not listened to).
- **Sound and the browser's autoplay rule:** a page that has had no click or key press may not make a sound (a
  gamepad button does not count), and what the game plays until then is lost. The page says so under the picture
  while it lasts and starts the sound with the first click or key.
- **In the browser** a video is never waited for: it plays from the store when `pack-worker.js` fetched it ahead,
  and is streamed by ranges from `pack/video/<path>` otherwise. Fetched ahead: right after the boot set, the
  front end's videos in the order they play (loading strip, four logos, title and menu backgrounds: 26 MB) and
  the one-second strips; then always the story scene after the furthest one played (the first one before any),
  with its voice track. The 73 names are all in GAME.KP3, not in the levels, so "next" is the files' order.
  On a connection measured below 8 Mbit/s the downloads that fetch ahead stand still while a video is streamed.

**Music** (`pack_music.py`, called by `pack.py`; needs an `ffmpeg` with libvorbis, else, or with
`--music-quality 0`, the music stays the PCM it is):

- The 143 music files are RenderWare Audio streams of 16-bit PCM, 48 kHz stereo: 2.2 hours, 1547 MB, 1.5 Mbit/s
  for as long as music plays. Re-encoded as Vorbis at quality 5 (about 150 kbit/s) they are 140 MB: 11 times
  smaller. Lossless compression would only have saved about a quarter.
- The pack keeps each `.RWS` file's header (2 KB: the game reads the stream's items and their lengths from it, so
  nothing about its timing changes; the file still has its size in the listing and reads as zeros past the
  header) and puts the samples next to it as `<file>.RWS.OGV` (our container: per item the Vorbis setup and
  packets). The web build's music player (`rwa_stream.cpp`, `OgvFile` in `rws.cpp`) decodes that on the thread
  that already fed the music, with FFmpeg's Vorbis decoder (`thirdparty/ffmpeg-bink`); the native build is
  untouched.
- Vorbis has no encoder delay (checked on a track: the decode lines up with the source at lag 0 and has the same
  number of frames), and the player stops at the item's frame count, so a looping item still meets its own start.
- Checked: LVL010's two tracks start "re-encoded" in the first scene and fight, output level 0.11 to 0.19, 60 fps.
  Not listened to.

**The site folder** (`make_site.py` -> `build/site`): what is uploaded to a static host, as it is.

- **What the hosts ask for** (looked up 2026-11-18): Cloudflare Pages takes no file over 25 MiB and at most
  20,000 files (1,000 by drag and drop); Netlify has no hard limits but serves large files badly and its free
  plan now meters bandwidth in credits (check its pricing page: a whole playthrough is about 2.2 GB). Whether
  Pages answers range requests on static files could not be confirmed. So the folder has no file over 16 MiB,
  828 files, and the page only ever fetches whole files.
- **Streams:** the data is in `pack/s/<stream>.<n>`: a stream is a run of bytes cut into parts (16 MiB for a blob,
  4 MiB for a video with a first part of 256 KiB so that opening one does not cost a whole part, 2 MiB for the
  music). Each blob and each video is a stream; things that are small and go together share one (the voice tracks
  of one language in the videos' order, the music's samples, the music files' headers, the one-second video
  strips). A stream is named by the hash of its bytes, so the host may cache its parts for ever
  (`_headers` says so). `pack/manifest.json` (version 2) gives each file its place: `"loc": [stream, offset, length]`.
- `_headers` (read by both hosts) sets the cross-origin isolation headers the game's threads need; `404.html`
  keeps Cloudflare Pages from answering a missing file with the page.
- **Trying it here:** `run_wasm_download.bat` (`serve.py --site`) serves the folder and nothing else. Checked with
  `--no-range --rate 100`: the game starts, LVL010's 105 MB arrive from seven parts in 9.5 s, the differences
  apply, the videos and their voice track play from the store, the music plays.
- **To put it online:** upload the folder `dotd\build\site` itself (Netlify: "Deploy manually", drag the folder;
  Cloudflare Pages: "Upload assets", or `wrangler pages deploy build/site`). Nothing else is needed: no
  server code, no build step on the host. Not done from here: no deploy was made, so the two hosts' own
  behaviour (upload of 3.2 GB, their caches, their headers) is untested.

**In the browser:**

- `pack-worker.js` (a worker) downloads blobs, decodes them with `zstddec.wasm` (zstd's decoder as a 74 KB module of
  its own, `web/zstddec/`) and stores the content in the browser's private file system (OPFS). Order: what the
  game is waiting for; the boot set (GAME.KP3, the EBOOT stand-in, the menu level: the page starts the game when
  it is stored); the front end's videos; the rest of the level being played; the next level; the next story
  video. Two downloads at a time.
- `sw.js` (a service worker) answers the game's reads of `usrdir/<path>`: from the store for a packed file, from the
  store or the pack's `video/` folder for a re-encoded video, from the network for the music. A packed file that
  is not stored yet gets 503 and is fetched at once; the
  game's file layer asks again until it is there (`hostfs_web.cpp`), which blocks only the thread that reads:
  the level loader waits while the loading screen keeps running. The game code does not know about any of this.
- Which level and language to fetch ahead is read off the paths the game asks for (`LVL010/LVL010.KP3`,
  `00GLC.KP3`): opening a level's main file queues its sectors and then the next level in the pack's order.
- The line under the picture shows what is downloading: yellow when the game waits for it, grey when it is
  fetched ahead. "Delete downloaded data" empties the store.
- The music is played as it is read (a mixer stream fed by a thread, `rwa_stream.cpp`) instead of after the whole
  track has arrived.

**Checked** (the app's browser pane; `--pack-rate` is one budget for everything the site sends: before the
videos' work it was per download, so two downloads got twice the rate, and the numbers this section had then
were that much too good):

- **The store empty, 50 Mbit/s:** the game starts 5 s after the page opens (26 MB); the front end's videos are
  stored at 9 s; LVL010 can be played at 32 s; the intro video and its voice track are stored at 39 s. "New
  game" pressed at 56 s: the intro plays at once, from the store, with the English voice track, 60 fps; LVL020
  (41 MB as a difference) is nearly there at 64 s.
- **6 Mbit/s, the level data already stored:** each logo is stored before it plays (1 to 3 s each), the intro
  (18.5 MB) in 26 s and its voice track (3.2 MB) in 5 s during the title screen, the next story video during the
  intro. A logo that was streamed next to a download (before the order above) waited 2.4 s for data once; the
  game kept 60 fps while its video stood still.
- A second visit downloads nothing and loads LVL010 from the store in 0.7 s (1.1 s over HTTP).

**Not done / to know:**

- The site folder was only served locally (`serve.py --site`), not deployed to a host.
- The music is streamed each visit (the browser's own cache may keep its parts; it is not put in the store).
- **Phones** were not tried. Known gaps besides the decoding speed above: the input is keyboard and gamepad only;
  most phone GPUs lack S3TC, so the textures would take the CPU-decoded path; the page asks for 1 GB of wasm
  memory at the start.
- Only the videos up to the intro and the next one were played re-encoded (front end, PS3_019; PS3_020 was
  fetched, not watched); the sound was not checked by ear.
- A download that is interrupted (the tab closed) starts again from zero. Nothing is ever removed from the store
  by itself (the whole game in one language is about 2.2 GB there).
- A player who enters a level without the previous one stored (from a save) gets the whole blob, not the
  difference. Only LVL000 -> LVL010 -> LVL020 was run; the other levels' packs were made but not played.
- The game's data is copyrighted: putting a pack on a public site distributes the game.

## How it differs from the native build

| Part | Native | Web |
|---|---|---|
| Compiler | MSVC, x64 | Emscripten (clang), wasm32; `-pthread`; the PS3-layout static asserts stay off (as on x64) |
| Graphics | OpenGL 3.3 core | WebGL2 = OpenGL ES 3.0. The backend only ever used entry points both have (`platform/gfx/gl.h`); the shaders get `#version 300 es` and `precision highp` instead of `#version 330 core` (`gl::ShaderSourceForContext`), the game's Cg uber-shader translation included. DXT textures go to the GPU compressed (`WEBGL_compressed_texture_s3tc`) |
| Window, input, sound | SDL3 | SDL3's Emscripten backends (canvas `#canvas`) |
| Main loop | `for (;;) Run();` in the game's main | one `Run()` per `requestAnimationFrame` (`platform/frame_loop.cpp`): a browser must get control back every frame. Frames are held to 60 per second on a fixed time grid whatever the display's refresh |
| Threads | `std::thread` | the same (pthreads on web workers, a pool of 12 created before `main`), so the level loader still runs beside the frames. This needs a cross-origin isolated page: `serve.py` sends the COOP / COEP headers |
| Game files | read from disk (`platform/hostfs.cpp`) | read from disk by `serve.py`, fetched with HTTP range requests (`platform/web/hostfs_web.cpp`): a listing fetched once answers stat / directory listing; reads are synchronous, from a worker (the main thread hands its reads to an I/O thread); a 64 MB cache of 1 MB blocks with read-ahead for the small sequential reads (videos, sound streams) |
| Videos, speech | FFmpeg's Bink / ATRAC3 decoders | the same, compiled to wasm; in download mode the videos are VP9 re-encodes decoded on a thread of their own ("Videos") |
| Shader programs | built at the first draw that needs them (7 ms each), or on the loading screen from the variant list | built by the browser in the background (`KHR_parallel_shader_compile`, `cg_program.h`): a first draw never waits, what uses a program still building is not drawn for those few frames; on the loading screen from the variant list as natively, all started at once and then waited for |
| Textures | the device texture made at a texture's first use | all of a level's made on its loading screen (`MakeRasterTexturesAhead`, raster.h) |
| Music, speech streams | an item read and decoded when its voice starts | the music is played as it is read, on a thread (`rwa_stream.cpp`; in download mode from its Vorbis re-encode, "Music"); a speech item is decoded on a thread and its voice starts when the samples are there |
| Saves, shader variant list | `%LOCALAPPDATA%\dotd` | the home folder `/home/web_user` (`.local/share/dotd/savedata`, `.cache/dotd/shader-variants.txt`), kept in the browser's IndexedDB by the page (IDBFS: restored before `main`, written back every 5 s and when the tab is hidden) |

`serve.py` listens on 127.0.0.1 only and only reads: `/` is the build folder, `/usrdir/...` the game folder
(GET / HEAD with ranges, `Cache-Control: no-store` so the browser does not copy 8.7 GB into its cache),
`/usrdir.manifest` the listing, `/shader-variants.txt` the native build's shader variant list when this machine
has one (the page adds its lines to the web build's own list before the game starts, so the levels already played
natively get their programs built on the loading screen at the first web visit too).

## Long frames (2026-11-18)

Measured with `?DOTD_GFX_STATS=...` on the new-game flow (LVL010: loading, opening video, in-engine scene, first
fight). What a long frame was, before and after:

| Where | Before | Cause | Now |
|---|---|---|---|
| The opening video cuts to the in-engine scene | 1207 ms + 260 ms | 24 shader programs built at their first draw (55 ms each the first time the browser sees them, 5 ms from its cache) and 95 textures uploaded | 42 ms (the list known: programs and textures made on the loading screen, one 250 ms frame there); 40-50 ms for three frames on a first visit with nothing known (background builds) |
| 5 s into the scene, the music starts | 570-640 ms | the whole music track (45.6 MB, 46 requests) read on the main thread when its voice starts | none: read and decoded on a thread |
| New effects in the fight | 170 + 87 + 40 ms | programs built at their first draw | under 30 ms |

Nothing else in that flow is over 30 ms. The native build does not have these because a desktop driver builds a
program in 7 ms and takes a texture in microseconds, and a 45 MB read from disk takes 20 ms.

## Checked (2026-11-17 / 18, Chromium, the app's browser pane)

Boot, the copyright / logo videos, press start, the main and game menus, a new game: LVL010 loads (34272 objects,
about 1 s), the opening video and its skip dialog, the in-engine scene, the first fight with the tutorial, moving,
jumping and attacking. 60 fps, about 1.9 ms of CPU per game frame in the fight, no shader or GL error in the log;
the fight's picture matches the native build's by eye (`work/scratch-c27/capD/control+300.png`).

## Not done yet

- **Only LVL010's flow was measured for long frames.** Other levels may have other first-use work (a streamed
  sector's textures are still made at their first use, a level's meshes too: 158 meshes took 1-5 ms).
- On a first visit an object whose shader program is still being built is missing for a few frames (never seen
  to matter at the cut to LVL010's scene; not looked at elsewhere).
- Music and speech start when their samples have arrived (a music track about half a second after the native
  build would start it; the game's own notion of the stream position does not wait).
- **Saves** are kept the same way but saving and loading a game was not tried in the browser.
- Not compared frame by frame with the native build (the replay harness and `newgame_test` are native only), and
  only LVL000 / LVL010 were run. Sound was only checked as "the device runs", not by ear.
- The canvas is 1280x720, scaled down by the page when the window is narrower; no fullscreen button.
- Sound goes through SDL's ScriptProcessorNode path (Chrome logs a deprecation warning).
- The native build's debug aids that write files (`DOTD_SCREENSHOT`, `DOTD_DUMP_GLSL`, ...) write into the
  in-memory file system, where nothing reads them.
