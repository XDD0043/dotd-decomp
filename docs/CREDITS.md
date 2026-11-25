# Credits and acknowledgements

This reconstruction builds on the work of the original developers, middleware authors,
reverse engineers, and open-source tool communities below. The descriptions record how
each resource helped the project, including the separate RPCS3 research/mod workspace.

## Original game, engine, and research material

| Credit | Contribution to this project |
|---|---|
| **Étranges Libellules** and **Sierra Entertainment** | The original *The Legend of Spyro: Dawn of the Dragon*: development and publishing respectively. Étranges Libellules' **K/Kal engine** is the engine being reconstructed. |
| **AdrienTD** — [XXL-Editor](https://github.com/AdrienTD/XXL-Editor) and [elbtools](https://github.com/AdrienTD/elbtools) | K/Kal-engine research, class categories, serialization/deserializer references, and file-format documentation, including Spyro support. |
| **Criterion Software** — **RenderWare Graphics 3.7.0.2** | Original middleware source used to check function names, structures, mathematics, and stream/geometry readers against the PS3 executable. Credit also to the maintainers of the [SIGMA source archive](https://github.com/sigmaco/rwsrc-v3.7.0.2) used for this research. |
| **aap and contributors** — [librw](https://github.com/aap/librw) | RenderWare reimplementation and design/file-format reference. The native build uses this project's `src/Renderware/` implementation. |
| **OSome Studio**, **Microids**, and the original **Étranges Libellules** developers — [*Asterix & Obelix XXL 2* remaster](https://store.steampowered.com/app/887060/Asterix__Obelix_XXL_2/) | The Mac executable's symbols and DWARF/dSYM information supplied original K-engine class, member, method, enum, and source-file names. These were checked against DotD's PS3 code because the engine branches differ. The remaster is credited by [OSome Studio](https://www.osome-studio.com/en/studio). |
| **NVIDIA** — [Cg Toolkit](https://developer.nvidia.com/cg-toolkit) | Reference headers and shader/binary-format definitions used while studying the original Cg/PSGL shader path and translating its behavior to GLSL. |
| **Sony Computer Entertainment**, **Dinkumware**, and **RAD Game Tools** | The original PS3 platform/SDK interfaces, runtime/math routines, and Bink video technology studied during reconstruction. Native platform shims and FFmpeg provide the corresponding host-side functionality. |

## Native runtime dependencies

| Project | Use |
|---|---|
| **Sam Lantinga and the SDL contributors** — [SDL3](https://github.com/libsdl-org/SDL) | Windows, events, controllers, audio devices, threads, and platform integration. Pinned as a source submodule; zlib license. |
| **FFmpeg developers and codec contributors** — [FFmpeg n7.1.2](https://github.com/FFmpeg/FFmpeg/tree/n7.1.2) | Bink video/audio and ATRAC3 speech decoding through the project's `ffmpeg-bink` build. This selected configuration identifies itself as LGPL-2.1-or-later. See [the dependency notes](../thirdparty/README.md). |
| **Khronos and the OpenGL community** — [OpenGL](https://registry.khronos.org/OpenGL/) | The native graphics backend's API and shader-language specifications. |

## Reverse engineering, PS3 scripts, and SDK references

| Project / authors | Use |
|---|---|
| **NSA and Ghidra contributors** — [Ghidra](https://github.com/NationalSecurityAgency/ghidra) | PPC decompilation/disassembly, cross-references, symbols, data types, and static analysis. |
| **clienthax and contributors** — [Ps3GhidraScripts](https://github.com/clienthax/Ps3GhidraScripts) | The installed PS3 analysis extension: `AnalyzePs3Binary.java` and `DefinePs3Syscalls.java`, covering PS3 imports/exports, NIDs, TOC setup, and syscall definitions. |
| **bethington and contributors** — [ghidra-mcp](https://github.com/bethington/ghidra-mcp); **LaurieWired** — [GhidraMCP](https://github.com/LaurieWired/GhidraMCP) | The installed Ghidra MCP/HTTP bridge used to inspect and annotate the executable, with acknowledgement to LaurieWired's upstream project from which the bridge originated. |
| **RPCS3 developers** — [RPCS3](https://github.com/RPCS3/rpcs3) | Running the original game for tracing, memory observations, camera/animation captures, and behavior comparisons; its PPU interpreter was also consulted for instruction semantics. Its SELF decrypter (`rpcs3/Crypto/unself.cpp`) was the reference for the disc executable's layout and its key vault (`key_vault.cpp`) the source of the application key the port uses to read `EBOOT.BIN` (`src/platform/self_decrypt.cpp` is a separate implementation, checked byte for byte against RPCS3's output). |
| **KN4CK3R and ReClass.NET contributors** — [ReClass.NET](https://github.com/ReClassNET/ReClass.NET); **NateWeav and contributors** — [ReClass.NET-MCP](https://github.com/NateWeav/ReClass.NET-MCP) | Live process-memory inspection and structure views, with MCP access for the research workflow. |
| **PSL1GHT / ps3dev contributors** — [PSL1GHT](https://github.com/ps3dev/PSL1GHT) and [ps3dev](https://github.com/ps3dev/ps3dev) | Open PS3 SDK/header references for PPU types, controller data, RSX/GCM register definitions, and FSELF/SPRX packaging tools such as `fself` and `sprxlinker`. |
| **Ned Heller / sp00nznet and contributors** — [ps3recomp](https://github.com/sp00nznet/ps3recomp) | Source reference for PS3 high-level platform semantics. |
| **Capstone contributors** — [Capstone](https://www.capstone-engine.org/); **Keystone contributors** — [Keystone](https://www.keystone-engine.org/) | PPC and x86 disassembly, PPC assembly, and analysis/patch verification helpers. |
| **Eli Bendersky and contributors** — [pyelftools](https://github.com/eliben/pyelftools) | ELF and DWARF parsing, including extracting information from the XXL2 debug symbols. |
| **NumPy**, **Pillow**, and **PyYAML** contributors — [NumPy](https://numpy.org/), [Pillow](https://python-pillow.org/), [PyYAML](https://pyyaml.org/) | Image/numerical comparison tools and RPCS3 patch-file handling in the research scripts. |

## RPCS3 overlay and earlier mod experiments

These credits cover the research tools that helped establish and test the native port.

| Project / authors | Use |
|---|---|
| **Omar Cornut and Dear ImGui contributors** — [Dear ImGui](https://github.com/ocornut/imgui) | The in-game research overlay, event logger, and coverage-tracer UI. |
| **TheRouletteBoi** — [imgui_playstation3](https://github.com/TheRouletteBoi/imgui_playstation3) | PS3 ImGui integration/backend reference during overlay development. |
| **tge-was-taken and contributors** — [ps3-ckit](https://github.com/tge-was-taken/ps3-ckit) | Earlier PS3 C-code injection experiments and loader/hook workflow references. |
| **Zig contributors** — [Zig](https://ziglang.org/) and **LLVM contributors** — [LLVM](https://llvm.org/) | PPU cross-compilation and linking for the research module and related tools. |

## Build and scripting tools

Thanks also to the [Python](https://www.python.org/), [CMake / Kitware](https://cmake.org/),
[Ninja](https://ninja-build.org/), [Microsoft Visual C++](https://visualstudio.microsoft.com/vs/features/cplusplus/),
and Windows SDK teams for the native build and analysis tooling.

Third-party copyright and license notices remain with their respective authors.
These acknowledgements do not replace those notices or grant a new license to the
original game, middleware, debug symbols, or SDK material.
