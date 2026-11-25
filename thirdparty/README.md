# dotd/thirdparty/

Third-party source built with the remake. Everything is compiled from source; no third-party binaries are
used or run.

**Nothing has to be fetched by hand.** When `SDL/` or `ffmpeg/` is missing, configuring (`cmake --preset ...`, or
`setup.cmd`) downloads the release *source* archive into `.fetched/` (git-ignored), checks its SHA-256 and builds from
there (`../cmake/FetchDeps.cmake`):

| Library | Archive | SHA-256 |
|---|---|---|
| SDL3 | `https://github.com/libsdl-org/SDL/releases/download/release-3.4.18/SDL3-3.4.18.tar.gz` (the submodule's commit 829a65d) | `9c75cf16330322c217dedd2e0609f1124f1b54b8633e763467b4684d0f4334a3` |
| FFmpeg | `https://ffmpeg.org/releases/ffmpeg-7.1.2.tar.xz` (the same files as tag n7.1.2) | `089bc60fb59d6aecc5d994ff530fd0dcb3ee39aa55867849a2bbc4e555f9c304` |

`-DDOTD_FETCH_DEPS=OFF` turns the downloads off (offline: put the sources in place as below). A build without FFmpeg
stops at configure time unless `-DDOTD_NO_VIDEO=ON` asks for one (no videos, no speech).

| Folder | What | Licence | How it gets here |
|---|---|---|---|
| `SDL/` | SDL3 (window, input, audio device, threads) | zlib | git submodule, or the release archive fetched at configure time. A git worktree has no submodule checkout: CMake's `DOTD_SDL_DIR` points at the main checkout's copy (`work/wt_build.cmd` does this). |
| `ffmpeg/` | FFmpeg **n7.1.2** source (only the Bink video, Bink audio, ATRAC3, VP9 and Vorbis decoders are built) | LGPL-2.1-or-later | a shallow clone or the release archive fetched at configure time, **not committed** (`dotd/.gitignore`). |
| `astc-encoder/` | ARM's astc-encoder **5.5.0** source (only its block packing, `symbolic_to_physical` / `encode_ise`, and its decoder for `tests/astc_transcode_test.cpp`; library `astcenc_pack`, scalar build) | Apache-2.0 | a shallow clone, **not committed** (`dotd/.gitignore`): `git clone --depth 1 --branch 5.5.0 -c core.autocrlf=false https://github.com/ARM-software/astc-encoder.git astc-encoder`. Without it a phone without S3TC gets RGBA8 textures as before (`platform/gfx/texture_transcode.h`). |
| `zstd/` | zstd **v1.5.7** source (only the decoder, for the web build's download worker: `web/zstddec/`) | BSD-3-Clause | a shallow clone, **not committed** (`dotd/.gitignore`): `git clone --depth 1 --branch v1.5.7 -c core.autocrlf=false https://github.com/facebook/zstd.git zstd`. Without it the web build has no download mode. |
| `ffmpeg-bink/` | ours: the CMake target `ffbink` and the handwritten configuration headers (`include/config.h`, `config_components.h`, `libavutil/avconfig.h`, `libavutil/ffversion.h`, `libavcodec/codec_list.c`, `libavcodec/bsf_list.c`) | — | committed |

## FFmpeg (Bink)

Fetch the source once (from `dotd/thirdparty/`):

```
git clone --depth 1 --branch n7.1.2 -c core.autocrlf=false https://github.com/FFmpeg/FFmpeg.git ffmpeg
```

`dotd/CMakeLists.txt` builds `ffmpeg-bink` from `DOTD_FFMPEG_DIR` (default `thirdparty/ffmpeg`) when it holds the
clone, else from the fetched archive (above); with neither, configuring stops unless `DOTD_NO_VIDEO=ON`.
A git worktree can pass `-DDOTD_FFMPEG_DIR=<main checkout>/dotd/thirdparty/ffmpeg` instead of cloning again.

What is built: `libavcodec` `bink.c`, `binkdsp.c`, `binkaudio.c` (DCT and RDFT), `atrac3.c` / `atrac.c` (the levels' speech, with `libavutil/float_dsp.c`), the VP9 decoder (`vp9*.c`, `videodsp.c`, the `vp9_superframe_split` bitstream filter: the web pack's re-encoded videos, `dotd/web/README.md`), the Vorbis decoder (`vorbisdec.c`, `vorbis.c`, `vorbisdsp.c`, `vorbis_data.c`, `xiph.c`: the web pack's re-encoded music) and the core they need
(`avcodec`, `decode`, the null bitstream filter, options, packets, buffers, `vlc`, `blockdsp`, `hpeldsp`),
and the part of `libavutil` that core uses (frames, buffers, options, pixel formats, `tx` for the audio
transform, ...). No configure script, no assembly, no threads (`HAVE_THREADS 0`), C only; MSVC builds it
with `/O2` in every configuration because FFmpeg relies on dead-code elimination of `if (CONFIG_X)` branches.

LGPL: the remake links this library statically for local builds. A binary that is distributed must either
link FFmpeg as a shared library or ship what LGPL-2.1 section 6 requires (the FFmpeg source used, these build
files, and the program's object files so that it can be relinked with a modified FFmpeg), plus the licence
text and a notice.
