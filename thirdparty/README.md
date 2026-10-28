# dotd/thirdparty/

Third-party source built with the remake. Everything is compiled from source; no third-party binaries are
used or run.

| Folder | What | Licence | How it gets here |
|---|---|---|---|
| `SDL/` | SDL3 (window, input, audio device, threads) | zlib | git submodule. A git worktree has no submodule checkout: CMake's `DOTD_SDL_DIR` points at the main checkout's copy (`work/wt_build.cmd` does this). |
| `ffmpeg/` | FFmpeg **n7.1.2** source (only the Bink video, Bink audio and ATRAC3 decoders are built) | LGPL-2.1-or-later | a shallow clone, **not committed** (`dotd/.gitignore`). |
| `ffmpeg-bink/` | ours: the CMake target `ffbink` and the handwritten configuration headers (`include/config.h`, `config_components.h`, `libavutil/avconfig.h`, `libavutil/ffversion.h`, `libavcodec/codec_list.c`, `libavcodec/bsf_list.c`) | — | committed |

## FFmpeg (Bink)

Fetch the source once (from `dotd/thirdparty/`):

```
git clone --depth 1 --branch n7.1.2 -c core.autocrlf=false https://github.com/FFmpeg/FFmpeg.git ffmpeg
```

`dotd/CMakeLists.txt` builds `ffmpeg-bink` when `DOTD_FFMPEG_DIR` (default `thirdparty/ffmpeg`) holds the
clone; without it the build still works and `platform/video/bink.cpp` reports that videos cannot be played.
A git worktree can pass `-DDOTD_FFMPEG_DIR=<main checkout>/dotd/thirdparty/ffmpeg` instead of cloning again.

What is built: `libavcodec` `bink.c`, `binkdsp.c`, `binkaudio.c` (DCT and RDFT), `atrac3.c` / `atrac.c` (the levels' speech, with `libavutil/float_dsp.c`) and the core they need
(`avcodec`, `decode`, the null bitstream filter, options, packets, buffers, `vlc`, `blockdsp`, `hpeldsp`),
and the part of `libavutil` that core uses (frames, buffers, options, pixel formats, `tx` for the audio
transform, ...). No configure script, no assembly, no threads (`HAVE_THREADS 0`), C only; MSVC builds it
with `/O2` in every configuration because FFmpeg relies on dead-code elimination of `if (CONFIG_X)` branches.

LGPL: the remake links this library statically for local builds. A binary that is distributed must either
link FFmpeg as a shared library or ship what LGPL-2.1 section 6 requires (the FFmpeg source used, these build
files, and the program's object files so that it can be relinked with a modified FFmpeg), plus the licence
text and a notice.
