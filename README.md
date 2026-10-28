**Approximately 29% ported** — based on tracked engine/game functions; some implementations still contain stubs (2026-10-28).

# Dawn of the Dragon remake (work in progress)

![Dawn of the Dragon remake gameplay demo](docs/media/demo.mp4)

A behaviour-exact reimplementation of *The Legend of Spyro: Dawn of the Dragon*
(PS3, BLUS30205). This repository contains the `dotd` source, tests, build
configuration and documentation.

## Build on Windows

Requires Git, CMake 3.25 or newer, Ninja, and Visual Studio with the C++ tools.
Run these commands from an x64 Visual Studio developer command prompt:

```sh
git submodule update --init --recursive
cmake --preset windows-msvc
cmake --build --preset windows-msvc-release
```

The executable is `build/windows-msvc/Release/dotd.exe`.
Use `launch.cmd` to start it with a fixed console title that hides the executable's local path. The launcher can also sit next to `dotd.exe`.
For a debug build and tests:

```sh
cmake --build --preset windows-msvc-debug
ctest --preset windows-msvc-debug
```

SDL3 is pinned as a submodule. Optional FFmpeg source provides Bink video/audio
and ATRAC3 decoding; fetch it **before configuring** for video and speech support:

```sh
git clone --depth 1 --branch n7.1.2 -c core.autocrlf=false https://github.com/FFmpeg/FFmpeg.git thirdparty/ffmpeg
```

See [thirdparty/README.md](thirdparty/README.md) for dependency details.

## Game data

Supply your own copy of the game. Copy `dotd.ini.example` to `dotd.ini` in the
working directory or next to the executable, and set `usrdir` to your local
`PS3_GAME/USRDIR` directory. Game data is read only. Tests requiring it skip when
it is not configured.

Game data, binaries, screenshots, build output and local settings are excluded
from this repository. The reverse-engineering workspace and its Git history
are kept separately.

## Source layout

- `src/k2000/` and `src/Spyro2008/`: reconstructed engine and game code.
- `src/Renderware/`: the RenderWare portions used by the remake.
- `src/crt/`: math, random-number and PPC instruction helpers.
- `src/platform/`: platform replacements for the PS3 imports.
- `tests/`: native tests; `docs/`: implementation plans and coding rules.
