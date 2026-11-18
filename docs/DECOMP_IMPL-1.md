# DECOMP_IMPL-1: boot to the front end

The first implementation phase of the remake. **Goal: the native build boots, loads GAME.KP3 and the front-end level LVL000 exactly like the PS3 build, and shows the working front end (videos, press start, main menu, options, language) on SDL3 + OpenGL.** No gameplay yet.

Read first:
- [BLUEPRINT.md](BLUEPRINT.md): plan, workflow, agent model.
- [STYLE.md](STYLE.md): code rules.
- The three research reports this phase is built on, in `outputs/remake/research/`:
  - `boot-and-platform.md`: boot sequence, main loop, threads, the PS3 API surface, platform shims.
  - `kp3-loading.md`: loader, object database, references, the per-class Load contract, the 160 classes with tiers.
  - `frontend-rendering.md`: Rt2d/Maestro menus, video, fonts, textures, the 2D draw path.

---

## 1. What we are building, and what we are not

**Ported from the EBOOT** (behaviour-exact; one `.cpp` per original unit, address comments, the STYLE rules):
- **Boot and frame sequencing.** `main`'s loop, `Main_InitGame`, `InitializeCKGameLoopSubsystems`, the CKGameLoop mode state machine (modes 0 boot, 1 init, 4, 5 front end and gameplay, 8 pause), and the frame order:
  1. timer;
  2. input;
  3. sound;
  4. update;
  5. render;
  6. sysutil.
- **The KP3 loader.** `CKLoadingManager`, `ClassManager`, the `CKCoreManager` UUID registry, `DecodeObjectId`, the Global providers, and the GAME → GLC → boot request → LVL000 → LLC sequencing. Then the **Load / constructors / PostLoad of the 160 serialized classes** in GAME, 00GLC, LVL000 and 00LLC000.
- **The front-end game logic:**
  - CKS08GameManager front-end states and the CKS08Menu* classes;
  - CKFlashManager / CKFlashUI message handling;
  - CManager2d / CText2d / CBillboard2d;
  - CVideoManager (video segments, fades);
  - CLocManager (text by id, pad glyph tokens);
  - CKInput (the "Flash Manager" mapping set).
- **RenderWare Rt2d / Rt2dAnim / Maestro**, the Flash-like 2D runtime, ported from the EBOOT's RenderWare range (`0x6f5f80`–`0x7216c8`).
  - librw has no Rt2d, and the menus are built entirely on it.
  - This is library code, but it decides what every menu shows and when, so it is ported, not reimplemented.

**Replaced** (platform layer, not ported):
- PSGL / GCM / RESC / Cg → `platform/gfx`: an OpenGL 3.3 core backend that stays inside GLES 3.0, so WebGL2 works later.
- cellFs / sysutil / pad / sysmodule / l10n / lwmutex / threads / time → `platform/cell` shims with the PS3 signatures.
- Bink → an open Bink 1 decoder (FFmpeg's libavcodec `bink`/`binkaudio`, built from source). Never port RAD's code.
- RWA / MultiStream audio → a null output in this phase; real audio comes later.

**Not this phase:**
- 3D rendering. LVL000 has no meshes and the opaque video covers the world stages.
- Sectors, gameplay, sound effects.
- Determinism hooks and replays.
- WASM.

**About "translating PS3 commands":** we do **not** emulate the RSX GPU or translate GCM command buffers. That is what RPCS3 and ps3recomp do. Instead the game's draw calls are caught where they enter RenderWare's immediate-mode API, and the platform layer draws them with OpenGL. PSGL, the API under RenderWare, is OpenGL ES-shaped anyway. ps3recomp is not used; it remains a reference for HLE semantics only.

---

## 2. Third-party pieces for this phase

| Need | Choice | Licence | Notes |
|---|---|---|---|
| Window, input, audio device, threads | **SDL3** | zlib | git submodule, built from source |
| GL loader | **glad** (GL 3.3 core) | MIT/public | generated source |
| Bink 1 video + audio | **FFmpeg libavcodec/libavutil**, only `bink`, `binkaudio_rdft`/`dct` decoders | LGPL-2.1 | build from source with everything else disabled; link dynamically (or keep the LGPL obligations in mind) |
| DXT1/DXT5 | GL `EXT_texture_compression_s3tc` on desktop; **bcdec** (single header) as the CPU fallback for GLES/WASM | MIT/Unlicense | |
| Tests | the existing minimal CHECK harness | — | |

The project rule "never run third-party binaries" applies: everything is built from source in `dotd/thirdparty/`.

---

## 3. Checkpoints

Each checkpoint has an **exit test that a machine can check** where possible. Do them in order; within a checkpoint, the listed parts can be worked on in parallel.

### C1.0: Platform shell
Goal: a window, a frame loop at 60 Hz, files and input, nothing from the game yet.

**Status: done (2026-10-15).**
- MSVC x64 builds clean, with SDL 3.4.18 built from source as a submodule.
- `ctest`: `ppc_ops`, `kclock`, `platform`, `fs_selftest` pass.
- The selftest reads the real GAME.KP3 (810,868 bytes; the first word is 2668, the object count) and lists USRDIR (31 entries).
- `dotd --frames 420` measures 60.000 fps with frame starts 16.36–16.97 ms apart on a 165 Hz display.

Parts:
- **`platform/sdl`:**
  - SDL3 init and a 1280×720 window (resizable; the internal target stays 1280×720 and is letterboxed into the window);
  - a GL 3.3 core context;
  - an event pump;
  - the **frame pacer** (see "Frame rate" in §7). It holds `frame_rate` (default 60). It paces by vsync when the display refresh is a whole multiple of 60 Hz, and checks over 120 frames that the driver really blocks. Otherwise it uses a timer on a fixed slot grid with swap interval 0.
- **`platform/gfx`:** GL backend v0. Clear, one textured-quad pipeline, present. A `gfx::Device` interface so a later Vulkan, Metal or WebGPU backend fits.
- **`platform/cell/fs`:**
  - `cellFsOpen/Read/Seek/Close/Stat/Fstat/Opendir/Readdir`;
  - `/dev_bdvd/PS3_GAME/USRDIR` and `/app_home` map to the user's USRDIR, read-only (path from a config file or the command line, never inside the repo);
  - lazy handles (the boot pre-opens about 550 RWS files).
- **`platform/cell/pad`:**
  - `cellPadInit/GetData/GetInfo2/SetActDirect/...` filled from SDL gamepad and keyboard into `CellPadData`;
  - this is also where input recording will hook in later.
- **`platform/cell/sysutil`, `sys_sync`, `sys_thread`, `sys_time`, `l10n`:**
  - SDL quit maps to the EXITGAME callback;
  - system parameters (language, button assignment) come from the config;
  - `sys_lwmutex_t` keeps its 24-byte PS3 layout and holds a handle id;
  - semaphores and threads map to SDL;
  - `sys_time_get_system_time` exists already.
- **Stubs:** sysmodule, BGM, save data (reports "no data"; check the exact contract against `SaveData_ListAutoLoad_maybe` 0x2d010), message dialog (auto-confirm), gamma (stored).

Exit: `dotd` opens a window, presents at 60 Hz, logs pad input, and a test reads `GAME.KP3` through `cellFsOpen("/dev_bdvd/PS3_GAME/USRDIR/GAME.KP3")`.

### C1.1: Boot skeleton and frame loop
Goal: the real boot order and frame loop, with not-yet-ported systems as stubs.

**Status: done (2026-10-15).** `boot_test` passes (x64 and x86 parity); `dotd --frames 330` boots in a window at 60.000 fps and leaves through the game's own exit path.
- **Ported from the assembly:**
  - `main` (as `GameMain`) and `CellSysutilCallback`;
  - `CoreSingletons.cpp`: `RegisterClass`, `CoreSingletons_Create/Destroy`, `Main_InitGame`, `Run`, `Cleanup`, `HandleParameters(Internal)`, the AppConfig;
  - `ClassManager` and the `ClassRegistry_*` wrappers;
  - `GameEngineContext` with its 48 setters;
  - `CKGameLoop`: `GameLoop`, modes 0/1/2/4/5/8/10, `UpdateGame`, `InitializeCKGameLoopSubsystems`, Pause/Resume/ResetRuntime, `SetAppActive`, `ShutdownAndExit`;
  - `CTimeManager` (FPS average, debug random frame time);
  - `KRequest` state handling;
  - the load requests' `Post`/`CheckDone`;
  - `Pad_Init`;
  - the game manager's level bookkeeping;
  - the game's `rand()` (`crt/rand.cpp`: an LCG with a 32-entry shuffle table and per-thread state).
- **The object model:** `IKSerializable` (root, key 0xc), `IKUpdatable` (key 0x3fe) and `IKModule` (0x33e), with virtuals in vtable slot order.
- **Class registration:** all 570 registered classes come from `work/gen_class_table.py` → `ClassTable.inc`. Classes that are not ported get factories that log.
- **Stand-ins:** everything else on the boot path is in `src/k2000/stubs/BootStubs.cpp`, marked `STUB(<checkpoint>)`; `work/count_stubs.py` lists them. The loader pool runs requests synchronously (C1.2 replaces it). The GAME.KP3 stand-in creates the game manager with level 0.
- **The boot trace** (`k2000/core/Stub.h`) records creation and mode changes; `boot_test` checks it against section 1.5 of `boot-and-platform.md`.
- **Findings:**
  - Key 0xcd is `CCloneManager`. The shader manager is 0x124d, created in `CKGraphic_InitRenderWare` (the research doc is corrected).
  - Five `*_ConstructBase_maybe` names at 0x24db0–0x24ea0 were engine setters; they are renamed in Ghidra (`outputs/ability-analysis/corrections-engine-setters.json`).
  - The frame clock is stopped until mode 4 restarts it, so dt is 0 through boot and level load.
  - `sys_timer_usleep` now uses `SDL_DelayNS`: `sleep_for` made the 5 ms loading-frame sleep about 15 ms on Windows.

Port:
- `main` (0x253870, minus the PS3-specific parameter and sysmodule parts);
- `Main_InitGame_maybe` (0x252c28);
- `InitializeCKGameLoopSubsystems` (0x1eae8): creation order and object ownership, with each subsystem a stub class first;
- `GameLoop` (0x21848), one frame per call;
- the 11-entry mode table (0xc4b070) with modes 0/1/4/5/8;
- `CTimeManager` around the ported `IKTime`;
- the static-constructor class registration (`RegisterClass` → `ClassManager`), as a static table generated from `class-tree.json` + `class-sizes.json`.

Exit: the loop runs, `IKTime` produces dt from `sys_time_get_system_time`, the mode machine walks 0 → 1 → 4 → 5 with stub loads, and the order of subsystem creation matches `boot-and-platform.md` (logged).

### C1.2: KP3 loader core
Goal: the object database, exactly.

**Status: done (2026-10-15), except the RenderWare shim, which moves to C1.3** (no class Load reads RW data yet).

`boot_test` (x64 and x86 parity, with the game data) checks the four files against the `kp3_parse.py` counts:

| File | Objects |
|---|---|
| GAME | 2668 |
| 00GLC | 5 |
| LVL000 | 5923 (4964 objects + 959 per-level glob loads of GAME objects) |
| 00LLC000 | 6 |

In all four files there are zero class or category end-offset mismatches, zero global-provider failures and zero UUID misses.

- **Ported from the assembly:**
  - `CKLoadingManager`: LoadGameFile, LoadLevel, LoadKp3Stream, ReadLevelClassTable, LoadLocFile, DecodeObjectId, ReadObjectRef(Array), ReadTextureRef;
  - `Kp3_LoadCategoryObjects/LoadClassObjects/PostLoadCategory/PostLoadClassObjects`;
  - the `IKFile` helpers and `Uuid_Read/Equals/Copy`;
  - `KFileSystem` OpenFile/CloseFile/BuildFullPath;
  - the `CKCoreManager` UUID hash and provider;
  - `Engine_GetGlobalInstances` and the CKGraphic, CKSrvCollision and game-manager providers;
  - `CKServiceManager_CreateServices/GetServiceByClassId`;
  - the request executors;
  - `keCThreadPool`: a request stack, newest first. The real worker threads are "CKLoadRequestQueue 0" and "CKMemcardRequestQueue::keCThreadPool 0";
  - the game manager's InitImpl and the mode-1 head of LoadImpl (requested level, a UUID ref, 7 player refs).
- **Platform equivalents:** `KFileStream` (a 1 MB block reader on `cellFs`). The pool's mutex and condition variables are host primitives.
- **Placeholders:** `work/gen_kp3_stubs.py` generates 149 classes (`k2000/stubs/Kp3Stubs.h`): every class in the four files, all 20 services, and the renderer's managers. Their Load reads nothing. The loader's development end-offset check (marked `DEV`, not in the original) skips each object's data and lists it per class. Porting a class means writing its header; the generator then leaves it out.
- **Findings:**
  - 20 classes are registered from library-TOC code and were missing from `class-tree.json`, including CKSrvBonus (1:7). They are now in `work/class-registry-extra.json`, for 590 registered classes in all.
  - The game manager's 7 player references in GAME.KP3 point at players 6, 4, 3, 2, 1, 0, 5.
  - `Sysutil_PollDuringLoad_maybe` only yields; it is renamed `Thread_YieldDuringLoad` in Ghidra.
  - The slots +0x24..+0x4c (Load, PostLoad(mode), GetGuid +0x44, SetGuid +0x48, ...) are common to every serialised class, including those that derive straight from the root. `IKSerializable` declares them.
  - `CKSrvCollision_Init` steps through its 50 projectiles with the PS3 sizeof (0x50), not the returned stride.

Port, from `kp3-loading.md` §5.2, the 43 root functions (about 83 with their helpers):
- **The `IKFile` interface:** Read/Seek/Tell/GetSize, a buffered file stream on `cellFs`, and an `ELB:` RW-stream bridge on the same stream position.
- **`CKLoadingManager`:**
  - `LoadGameFile`, `LoadLevel`, `LoadKp3Stream`, `ReadLevelClassTable`, `LoadLocFile`;
  - the category order `9,0,1,…,8,10,…,14`;
  - glob handling;
  - "Load all, then PostLoad all".
- **`ClassManager_CreateObject/CreateObjectArray`:** contiguous `new T[n]` plus stride.
- **`CKCoreManager` UUID registry:** 97 buckets, XOR hash, head insertion.
- **`DecodeObjectId`** exactly as in §2.5 of the report; object-ref and texture-ref reading.
- **The Global providers:** `Engine_GetGlobalInstances` and the four `vt+0x20` providers. This includes CKSrvCollision's "exactly 50" rule and the count == 1 versus pointer-array convention.
- **The RW shim:**
  - `RwStreamFindChunk` (skip until found);
  - per-reader blob capture `{type, size, version, bytes}`;
  - the DDS size walk, ported from `work/scratch-impl1-loading/dds_walk.py`;
  - a native texture registry (`name → texture record`, case-insensitive, 31-character cap) that texture refs resolve against.

During development, **every class Load is a generated "skip to end offset" stub that logs what it skipped.**

Exit:
- GAME, 00GLC, LVL000 and 00LLC000 open, and every object is created with the right count and stride;
- every reference decodes (no UUID misses, no provider failures);
- the class/category end offsets are hit.

### C1.3: The 160 Loads
Goal: every serialized object holds the same field values as in the original.

**Status (2026-10-17): done.** Every class Load is ported (11 family/class agents plus the main session; reports in `work/c13-report-*.json`). Gate 1: the four files load with 0 skipped objects and 0 end-offset mismatches, and `kLoadPendingKeys` is empty. Gate 2: `objects_diff.py` prints OK against the main-menu dump; every allowed difference is in `objects_diff_runtime.json` with the function that writes it. RenderWare data goes through the shim in `dotd/src/Renderware/` (STUB(C1.4) for rendering). Carried over: see HANDOFF.md.

Groundwork notes (kept for reference):
- **Original names from the XXL2 debug symbols** (`outputs/remake/research/xxl2-symbols.md`):
  - The root is IKBaseClass (slots 0–8), then IKSerializable (key 0xc, slots 9–19), IKUpdatable (0x3fe), IKService (0x1) and IKModule (0x33e).
  - KStream is IKFile, KClock is IKTime, KTimeManager is CTimeManager, and CKReferenceResolver is IKLoadingInterfaces (ReadHandle / ReadContiguousHandles / ReadTexture).
  - The loader's records are CKIDBundleLoad and CKTypeBundleLoad; the load mode is `ESerializationType`.
  - 5,513 Ghidra renames, applied to the remake as well; the registry factories are Create/Delete/CreateArray/DeleteArray.
- **Ported-class registration:** a class with `DOTD_CLASS_KEY` + `DOTD_DECLARE_FACTORIES` in a header is registered by `work/gen_kp3_stubs.py` (`k2000/stubs/Kp3Ported.h/.inc`). A hand-written class the files need without either is a generator error.
- **Gate 1 (end offsets):** the loader counts objects that are skipped although their class's Load is ported (`portedMismatches`), and `boot_test` requires 0. The boot classes whose Loads are still to do are listed in `ClassTable.cpp` (`kLoadPendingKeys`).
- **Gate 2 (field values):** `DOTD_DUMP_OBJECTS=path` makes `boot_test` dump the loaded objects of the ported classes (x86 parity build: PS3 layout). `work/objects_diff.py` compares that dump with `live_objects.py`'s dump of RPCS3. It accepts u32/u16/raw-byte matches, compares pointers by target class and index, and takes runtime fields from `work/objects_diff_runtime.json`. The reference dump of the main menu is `outputs/remake/census/objects-frontend_lvl000-20261017-144833.json.gz` (local, ignored by git).
- **Reads:** `IKFile_ReadObjectRef` / `IKFile_ReadObjectRefArray` / `IKFile_ReadRef<T>` (through `m_pLoadingInterfaces`, or the raw id), and `ReadS32LE` / `ReadF32LE` / `ReadRaw` (unswapped bytes).
- objects_diff rules added during the merges: "unset" bytes (0xcd native, 0 live), `{"count": reason}` for objects created at run time, `{"_skip_live": {addr: reason}}` (top level) for live objects with no file object, `{"unset_any": reason}` for stale heap bytes, and masks (bytes compared) matched per 16-bit half.

- **Order of work:** the tiers in `kp3-loading.md` §4.
  - Tier 0/A (77 classes) and B (62) are mechanical and **agent work** (§5).
  - Tier C (11) and D (10) are strong-model work.
  - Port the shared base loaders first (`CKMenuBase_114c`, `IKGameObject` with mode 8, `CElement2d`, `IKRenderable`, the scene-node bases, the FxData and Flash bases): many classes collapse onto them.
- **Constructors** come with each class (field defaults).
- **PostLoad** stays stubbed until the class needs it in C1.5 or C1.6.
- **Tier-D classes keep their RW payload as blobs** (the shim) until their real reader lands: DDS in C1.4, Rt2d brush and font in C1.4, Maestro in C1.5, Rwa in a later phase.

Exit, automatic:
1. **End offsets:** for every object, `Tell()` after `Load` equals the skipped end offset.
2. **Field values:** a **native census** (the remake dumps its objects in `live_census.py`'s JSON format) diffs clean against a census of the original taken at the main menu.
   - That census is still to be taken; see §6.
   - Pointer values are compared by target class and index, not by address.

### C1.4: Pictures: textures, 2D renderer, video
Goal: the boot video sequence and static 2D on screen, faithful to the original.

**Status (2026-10-18): done.** The boot plays loading video → copyrights (text over PS3_065, 299 frames) → logos PS3_071/072/073 → press start (Flash logo and text over PS3_003) → main menu after START (59 frames, as RPCS3), drawn by the GL backend with textures, Rt2d movies, widgets, text and Bink video (FFmpeg Bink-only build). Not yet compared pixel-wise with RPCS3 captures. Details: HANDOFF.md, `work/c14-report-*.json`.

- **Textures.** DDS (DXT1/DXT5, mips) → GL textures; CPU decode on GLES.
- **The immediate-mode path the UI uses.**
  - The calls: RW transform 0x761400, indexed draw 0x761220, plain draw 0x761028 → the backend.
  - The 0x24-byte vertex: position, colour, UV.
  - One "vertex colour × texture" shader with an orthographic UI camera and the 2D matrix stack.
  - UI render states: no depth, no culling, vertex alpha on.
  - The **4 blend modes** from the table at 0xc297ec/0xc297fc: opaque, alpha, additive, and darken `dst*(1-srcColor)`.
  - UI space: x from 0 to the aspect ratio, y from 0 to 1; 800×600 Flash stages fitted to the height and centred.
- **Video.**
  - The **render-stage order** of the 2D group (0xa0ac8): stage 17 screen FX, then the video (`CVideoManager_Draw` 0xa98b0), then stage 18 UI, then stages 19–22.
  - **Bink playback** through FFmpeg into three R8 planes (Y, Cr, Cb, plus alpha) with the BT.601 conversion shader. Use the constants from `frontend-rendering.md`; the original compiles them at run time.
  - The letterbox/pillarbox/stretch rule (0xa9d38).
  - The loading-video fallback frame path (0xa11b0).
- **Rt2d brush and font readers** (CBillboard2d, CText2d, CManager2d fonts from the LLC file: three bitmap fonts on 512×512 atlases) and text drawing, including the private-use pad-glyph characters.

Exit, comparison against RPCS3 reference captures of the same moments (§6), aiming for pixel-close rather than pixel-exact:
- the boot sequence plays in the original order and timing (loading video `PS3_005` → copyrights `PS3_065`, 4 s with fades → logos `PS3_071/072/073`, skippable → press start `PS3_003`, looped);
- static billboards and text render.

### C1.5: The Flash menus (Rt2d Maestro)
Goal: the menus animate and react like the original.

**Status (2026-10-18): done, headless** (drawing is C1.4). Rt2d, Rt2dAnim/Maestro, the RW core maths and the K-side Flash classes are ported (reports `work/c15-report-*.json`, brief `outputs/remake/C15-BRIEF.md`). Exit evidence: `tests/c15/flash_exit_test.cpp` fires the press-start and main-menu labels in the movies' order (main menu: `onMenu_OpeningAnimEnd` 61 frames after the open) and ends bit-equal to RPCS3; `work/maestro_diff.py` finds 26 of 29 movies equal to the live main menu, the other three being shown by the C1.6 flow. RPCS3 (`work/flash_labels_live.py`, 2026-10-18) fires the main menu's `onMenu_OpeningAnimEnd` on the same 61st frame after the open, with the same end state. Details and carried stubs: HANDOFF.md.

- **Port Rt2d / Rt2dAnim / Maestro from the EBOOT:**
  - scene graph, brushes and paths (vector shapes, tessellated by Rt2d itself);
  - animations and keyframes;
  - button and message handling (the message handler 0x6d180; message type 7 is probably getURL).
- **Then the K-side wrappers:**
  - CKFlashUI / CKFlashManager (movie selection: #3 press start, #0 main menu, #16 copyrights, #27 chapter, #28 options);
  - CFlashHotSpot (native widgets pinned to Flash anchors);
  - the localised Flash text.
- **PostLoad of the 2D classes.**

Exit:
- the press-start and main-menu movies play their opening animations and loops in sync with the main-menu video segments (`PS3_004`: frames 1–80/81–1581, 1582–1687/1688–3188, 3189–3268/3269–4768);
- frame labels such as `onMenu_OpeningAnimEnd` fire at the same frame numbers as in the original (logged on both sides: the mod's event logger can hook the message handler).

### C1.6: Front-end logic
Goal: a playable front end.

**Status (2026-10-18): done, except the pixel comparison** (it needs RPCS3 screenshots). The front end runs press start → main menu → game → options (sound, video) → language change with the GLC/LLC reload → back on the pad shim (`tests/c15/menus_c16_test.cpp`), with menu frame counts matching the RPCS3 labels capture; load game ("no save data" system dialog), new game up to "level load requested", the demo video after 30 s, and sound (menu waves, Bink audio) work. Details and open items: HANDOFF.md, `work/c16-report-*.json`.

- **Menu classes.** CKS08MenuMain/PressStart/Copyrights/Language/OptionPS3/OptionVideoPS3/Chapter/ChapterMode/Bonus/StartPlayer/Game, the CKInterfaceButton family, CKMenuManager.
- **Input.** The "Flash Manager" input mapping set (actions 0–3 and 6–9 are directions, 4 validate, 5 back, 0xE start; player 2 is offset by 0x14). Confirm the physical buttons in RPCS3.
- **Game manager.** The front-end state machine of CKS08GameManager. Selecting "new game" may stop at "level load requested".
- **Language switching.** It reloads GLC and LLC, as you did in the capture (`mode3` bursts).
- **Timing.** The press-start idle timer (30 s → demo video `PS3_001`), and the fades.
- **Audio** (moved from C1.4/later): Bink audio tracks of the videos (`binkaudio_dct`/`rdft`, already built in `ffmpeg-bink`), the RWA/MultiStream music and menu sounds through an SDL3 audio output, with the music/speech volumes (`Video_GetMusicVolume_maybe` and the options).
- **Carried from C1.4:**
  - Compare positions and colours pixel for pixel with RPCS3 captures of the same moments (loading video, copyrights, each logo, press start, main menu).
  - The logos' per-frame clear colour: `KBase3B0C_State3` (0x4f4b08) sets the camera context +0x44 every logo frame; not ported yet.

Exit:
- press start → main menu → options → language change → back, all driven by the gamepad;
- the same screens appear in the same order with the same timing as an RPCS3 run.

---

## 4. How to work (per unit)

The BLUEPRINT §4 loop, specialised for this phase:

1. **Pick the next unit** by checkpoint, then by first-run order (`outputs/remake/runtime-stages-newgame-lvl010.md`, stages `boot` → `game_load` → `front_end`). The runtime JSON gives, per function, the time and phase it first ran.
2. **Make sure the unit's classes have named fields** (struct packs, BLUEPRINT §5). A missing name blocks nothing: use the placeholder and come back.
3. **Read the function.**
   - Ghidra C for structure (TOC bridges are inline now; resolve leftover `ppuVarN[-0x...]` reads with `work/toc_lookup.py`).
   - **The assembly whenever there is float maths, bit manipulation or a TOC constant.**
4. **Write it** to STYLE.md:
   - address comment;
   - `ppc_ops.h`;
   - hex-float constants;
   - `BUG(original)` markers;
   - virtuals in vtable slot order.
5. **Build both presets** (`windows-msvc`, `windows-msvc-x86-parity`) and run `ctest`.
6. **Run the checkpoint's automatic checks** (end offsets, census diff, logs).
7. **Tick the unit's checklist** and commit, one unit or one class family per commit.

**Load functions specifically:**
- Read sizes and order must match **exactly**, including the deliberately unswapped colour fields (keep them as raw bytes).
- Branch on `mode` like the original, mode 8 included.
- Return 1 like the original; never add error handling that changes what is consumed.

**Library code (Rt2d):** same rules. It is the original's behaviour that matters, and Rt2d decides tessellation and animation timing.

---

## 5. Agent work in this phase

| Work | Tier | Input | Gate |
|---|---|---|---|
| Struct field naming for the 160 classes | B | `outputs/remake/struct-packs/lvl010-*.json` (restricted to the 160) + STRUCT-BRIEF | `apply_field_names.py --dry` clean |
| Tier 0/A/B Load + constructor ports (139 classes) | B | per-class pack: the decompiled Load, base Loads, the constructor, the assembly of float paths, the class header, the file layout from `kp3_parse.py` | **end offsets hit for every object of the class** + census diff clean + both presets build |
| Generated pieces: class registration table, struct headers from Ghidra, native census dumper | A (one-off scripts) | Ghidra, `class-tree.json` | builds; dumper output parses with the census tools |
| Tier C/D Loads, Rt2d/Maestro, the loader core, the renderer | A | research reports | the checkpoint exits |

A **LOAD-BRIEF.md** (for the Load-port agents) and a **`load_packs.py`** generator are the first two things to write when C1.3 starts. Model them on STRUCT-BRIEF.md and `struct_packs.py`; the per-class data is already in `work/scratch-impl1-loading/`. Only the 3 GB memory cap applies; run as many agents as RAM allows.

---

## 6. What we need from the original (user runs in RPCS3)

Ask for these when each checkpoint needs them; each takes a few minutes:

1. **Census at the title screen and at the main menu** (`python live_census.py --tag frontend_title` / `--tag frontend_menu`). This is the reference for the C1.3 field diff of LVL000 objects. **Needed before C1.3 can pass.**
2. **A recorded boot-to-main-menu run** (RPCS3 video recording or OBS at 60 fps) with the timeline running (`tracer_timeline.py`). Also an RPCS3 screenshot of each screen: the loading video, copyrights, each logo, press start, the main menu's three segments, options, language. This is the reference for C1.4–C1.6.
3. **The pad mapping check:** which physical buttons trigger the "Flash Manager" actions (a short logger session; the event logger can hook `CKInput_GetActionEntry`).
4. Later, when determinism matters: the hook build (dt / rand / pad) and replays.

---

## 7. Known facts and traps for this phase

- **Load order:**
  - GAME.KP3, 00GLC and the boot request load in the **boot** stage (mode 0).
  - LVL000 and 00LLC000 load in mode 1.
  - The level is chosen by GAME.KP3's game-manager data (`+0x280` = 0).
  - Loads run on one worker thread (`CKLoadRequestQueue`). **Checkpoint 1 may load synchronously, but `rand()` state is per thread** (TLS, seed 1). Give the loader its own RNG context from day one.
- **Engine slots:** `engine+0x00` and `+0x4c` are the same CKLoadingManager.
- **Mode 8** exists (the IKGameObject game-structure block); the old docs list 0–7.
- **CKSrvBonus** is key 0x1c1, shown as `?` by `kp3_parse.py`.
- **Uninitialised fields:** constructors that leave fields uninitialised must stay that way (see `CKTime`).
- **Mode names in Ghidra are wrong:** the CKGameLoop mode handler names don't match runtime meaning. The front end and gameplay both run in mode 5, pause in mode 8. Check the mode table, not the names.
- **The frame waits in `PresentPSGLDeviceBuffers`** (0x666d48): a flip semaphore with at most 2 frames in flight, 60 Hz. The platform equivalent is the frame pacer in `platform/sdl/app.cpp`.
- **Frame rate.** The game must run at exactly 60 frames per second, and swap interval 1 alone does not do that: it gives the monitor's rate.
  - Gameplay uses the measured dt (`KClock_Update` clamps it to 0.1 s), so speed holds at any frame rate.
  - Menu animations (Rt2d Maestro) step once per frame. The user saw them run much faster when RPCS3 was uncapped (>120 fps) and slower at 30 fps.
  - The pacer:
    - Starts each frame on a fixed 1/60 s grid. A late frame waits for the next slot, as a missed vblank does.
    - Waits after the swap, not before it. The game reads its clock at the start of the frame, and a steady dt matters more than steady presentation.
    - Does not keep vsync on when pacing by timer. Measured on a 165 Hz display, vsync on with the timer spread frame starts over 8.8–24.5 ms; vsync off gave 16.66–16.67 ms.
  - `frame_rate 0` is uncapped, for experiments only.
  - **`--fps N` (2026-11-17, `platform/fps.h`, default off):** the game runs at N fps (0 = no cap) with the measured dt, and the systems that count frames advance by the 60 Hz frames each displayed frame stands for (a phase accumulator on the real delta, `Ticks()` 0..6, `Scale()` = real delta x 60):
    - fixed steps per update: CKSrvPhysics (1/60 per 60 Hz frame), fixed-step Flash interfaces (0.02 x Scale), the interface video fade, the clamp's pull;
    - per-update trunc(rate x dt) that drops the fraction (0 above the rate): the cinematic scene fade (the scene would never end), the ledge fade-in (invisible above 100 fps), fall damage, fury mana, crumbly-zone and golem per-second damage, the electric arc / target cursor / filter / partner-link / model-flicker fades (`TruncSteps`, `Dt60`);
    - counters and rolls per update: the music stall counter, the stream-file latency, the golem random condition, held-damage hit sounds, the wind beam's 10% roll, the combos' compounding fade-outs;
    - chains of states one update per link run whole 60 Hz updates (`k2000/system/Fps60Hz.h`): the CKSrvCinematic and CKSrvSekensor services, the sound streams' state machines and the RWA stream players. Without this the LVL010 opening scene ran 0.15 s (144 fps) to 0.22 s (uncapped) short.
    - Measured with `fps_timing` (tests/c15, not a ctest; `DOTD_TEST_FPS=N`, `DOTD_TEST_FPS_RAW=1` without the calculation): menu openings within 0.013 s of 60 fps; the scene's control 9.28 s at 60, 9.24 s at 144, 240 and uncapped (9.08 s without the calculation). The Flash menus of LVL000 and LVL010 advance by the clock's dt (none has the fixed-step flag 0x80), so they kept their timing even without it.
    - Not identical: variable-dt integration (the hero's CKSrvDynamic remainder step, cameras, animation) differs slightly from 60 Hz steps; rand draws per update are more frequent (the RNG sequence differs, replays stay at 60); per-update links outside the gated services (AI states, triggers) come up to 16 ms sooner each; particle emitters with a gap below the frame time emit per frame; render-side flicker (glow) changes every frame.
- **Front end as seen in RPCS3** (user, 2026-10-15):
  - The title screen shows "Press the START button". Idling there plays a video.
  - After START there is no way back to the title screen.
  - The main menu has New game / Load game, with an "Accept" (✕) prompt.
- **Memory:** no allocator replication is needed for the front end. `KMemoryManager` is never constructed: do not port it.
- **Bink reads `.VID` through libc `open`**, not cellFs. The platform video layer opens files itself.
- **Open questions to settle during the work:**
  - the save-data "no data" contract;
  - which screens wait for a video to end;
  - the meaning of the u32 after each DDS name;
  - which textures the LLC TextureBank replaces;
  - the CKGameState vt+0x80…0xbc helpers.

---

## 8. Size of this phase (estimates)

| Part | Game functions | Library functions |
|---|---:|---:|
| Boot and loop skeleton | ~150 (most stubbed at first) | — |
| Loader core | ~83 | RW stream/chunk helpers (~10) |
| 160 Loads + constructors (+ PostLoads as needed) | ~560 → ~740 | 106 RW functions reached; most covered by the shim, then by real readers |
| Front-end logic | ~400 (the `front_end` stage traced 415 first-run functions) | — |
| Rt2d / Maestro | — | a few hundred (to be counted when C1.5 starts) |
| Platform layer (new code, not ported) | — | SDL3/GL/FFmpeg glue, roughly 5–8k lines |

Total: roughly 1,500–1,800 ported functions plus the platform layer. Most of the Load ports are mechanical and suited to agents. The parts on the critical path are the loader core, Rt2d/Maestro and the 2D renderer.
