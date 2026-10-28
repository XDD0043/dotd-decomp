# Dawn of the Dragon remake: blueprint

The master plan. It ties the strategy ([decompilation-plan.md](../../outputs/decompilation-plan.md)), the groundwork log ([remake-groundwork.md](../../outputs/remake-groundwork.md)), the style rules ([STYLE.md](STYLE.md)) and the agent brief ([STRUCT-BRIEF.md](../../outputs/remake/STRUCT-BRIEF.md)) into one working procedure. Status as of 2026-10-14.

---

## 1. Goal and definition of done

A native rebuild of the PS3 game (BLUS30205) that **behaves exactly like the original**: same results frame by frame, every bug and glitch intact, so speedruns feel the same. MSVC/Windows first, other platforms and WASM later.

**Exact** means: with the same inputs, the same frame-time (`dt`) sequence and the same RNG seed, the remake produces the same per-frame game-state hash as the original running in RPCS3. Everything below serves that test.

**Where the truth comes from:**

| Question | Source |
|---|---|
| What the game does (logic, physics, collision, AI, state machines, bugs) | the EBOOT: Ghidra for structure, **the PPC assembly for float-heavy code** |
| Exact arithmetic of instructions the architecture leaves undefined (divide by zero, float→int overflow, estimate instructions) | RPCS3's interpreter source, reference only (`thirdparty/rpcs3-ref`, GPL-2: never copied) |
| Timing (frame pacing, lag, load durations) | measured from the running game: the `IKTime` dt sequence, replays |
| Data (levels, classes, text) | the KP3 files through the ported `Load` functions |

---

## 2. Architecture

```
dotd/
  src/k2000/       engine (one .cpp per original translation unit, 878 units in total with Spyro2008/)
  src/Spyro2008/   game
  src/Renderware/  exact ports of the RW code gameplay reads (math, frames, animation, streams)
  src/crt/         ppc_ops.h (exact PPC arithmetic), later the ported libm / rand / qsort
  src/platform/    replaces the 110 PS3 imports: cell/ (sys_time, pad, fs, savedata...), sdl/, gfx/, audio/, video/, timing/, web/
  tests/           unit tests, capture-replay tests, replay metadata
  docs/            this blueprint, STYLE.md, source index
```
- Game code calls the PS3 API names it called originally (`sys_time_get_system_time`, `cellPadGetData`, ...). The platform layer implements them, so the call sites stay recognisable.
- Rendering: K-engine renderer decompiled, RenderWare through a librw fork, a small PSGL-subset device on GL 3.3/GLES 3.0 (decompilation-plan.md §6).
- Build: CMake presets (`windows-msvc` default, `windows-msvc-x86-parity` for the PS3-layout checks, `windows-vs2022`, `linux-clang`, `wasm`).

---

## 3. The data pipeline: one source of truth per kind of fact

| Fact | Lives in | Tools |
|---|---|---|
| Function names (36k, 97.8%) | Ghidra `/EBOOT.elf.N` | naming workflow (AGENTS.md) |
| Original source files (878 game/engine units) | `work/tu_map.json` → `dotd/src/**` checklists | `tu_split.py`, `gen_skeleton.py` |
| Class sizes, hierarchy, vtables | `work/class-sizes.json`, `class-tree.json`, `class-tree-extra.json` | `class_sizes.py`, `class_tree_extra.py` |
| Struct layouts (field names and types) | **Ghidra** (curated + imported drafts) | `live_census.py` → `struct_drafts.py` → `ghidra_import_drafts.py`; naming via packs → `apply_field_names.py` |
| `this` types and prototypes | Ghidra | `ghidra_type_this.py` (tiers 1–3) |
| What runs when | `outputs/remake/timeline/*.json` → `runtime-stages*.md` | `tracer_timeline.py`, `timeline_report.py` |
| Remake code | `dotd/src` | written per unit, following STYLE.md |

**Direction of flow:** live data and code reading → Ghidra (types, names) → generated packs and headers → `dotd`. Names are fixed in Ghidra first, then used in code. A header generator from Ghidra layouts is still to be written (§9).

**Ghidra readability fixes applied:** r2 per TOC domain, TOC block read-only, TocBridge stubs inline, engine and time-manager globals typed. Remaining: TOC slots read through a saved register show as `ppuVarN[-0x...]`; resolve them with `python work/toc_lookup.py <N>`.

---

## 4. Workflow for one source file

1. **Pick** the next file in runtime order (`outputs/remake/runtime-stages-newgame-lvl010.md`, earliest stage first).
2. **Types first.** Its classes must have named fields (packs, §5). Unnamed fields block nothing, but they make code unreadable.
3. **Read each function.** Ghidra C for structure, then **check against the assembly** whenever it does float arithmetic, bit manipulation or touches TOC constants. The decompiler shows double math where the code is single precision, hides fused multiply-adds (11,395 sites) and rounds constants (the clock's "0.01" is `0x3c23d70b`, not `0.01f`).
4. **Write C++** following STYLE.md:
   - an address comment on every function;
   - `ppc_ops.h` for FMA, float→int, division and shifts;
   - hex-float constants from the TOC bits;
   - original bugs kept and marked `BUG(original)`.
5. **Build both presets** (x64 and the x86 parity build, which checks the PS3 layout with `DOTD_ASSERT_*`).
6. **Test.** Unit tests for the quirks the assembly shows (like `tests/kclock_test.cpp`). Capture-replay tests and lockstep replays once the harness exists (§7).
7. **Tick the checklist** in the file's header and remove the `@generated` line (the generator then never touches the file again).

Reference implementation of the whole loop: `IKTime` / `CKTime` (`dotd/src/k2000/system/`).

---

## 5. Agent operating model

| Tier | Who | Work | Gate |
|---|---|---|---|
| A | user + strongest model | architecture, core types, briefs, float-critical and state-machine code, verifying "wrong name" claims, the harness | review |
| B | mid models | struct field naming from packs; prototypes; porting ordinary functions once types exist | schema + build + tests |
| C | cheap models | bookkeeping, unit tests from captured traces, doc tables | schema + build |

**Struct naming rounds** (ready to start):
- Packs: `outputs/remake/struct-packs/lvl010-NN.json` (60 packs, 272 classes, 32,627 placeholder fields, in the runtime order of a new game: boot, front end, LVL010). Rebuild with `python work/struct_packs.py --timeline <capture>`.
- Brief: `outputs/remake/STRUCT-BRIEF.md`. Output: `outputs/remake/fields-<pack>.json`. Apply with `python work/apply_field_names.py <file> --dry`, then for real. It renames placeholders only and lists corrections for manual checking.
- **Before agents:** the handful of giant classes (CShaderManagerPSGL 8,564 slots, CManager2d 673, CText2d 465, CKSrvPathFinding, CKSrvCollision) need array and stride detection by a strong model or a script first. Their "fields" are mostly arrays.

**Rules that still apply:**
- the 3 GB memguard cap per process (no limit on the number of agents);
- agents never write to Ghidra, game files or game memory;
- proposals are applied by the main session;
- a ~10% spot check by a strong model per round.

---

## 6. Milestones (measured from a new-game capture: boot → front end → LVL010)

LVL000 is the **front-end level** (press start, main menu, options, language, chapter select, bonus menus; no sectors). It loads together with GAME.KP3. **LVL010 is the first gameplay level.**

| # | Milestone | Scope (measured) | Exit criterion |
|---|---|---|---|
| M0 | Foundations | done: repo, skeleton, Ghidra types, tools, first code | `dotd` builds on both presets; tests pass |
| M1 | Boot | 404 functions in 139 files (KHostFS, PS3_CKVideo, CRenderer, CVideoManager, CManager2d...) | engine context and managers constructed; window open via SDL3 |
| M2 | GAME.KP3 + LVL000 load | +413 functions, 271 files total; 22 + 150 serialized classes | GAME.KP3 and the front-end level load; field values equal a census of the original |
| M3 | Front end | +415 functions, 281 files | title → level select navigable (input, 2D, Flash UI, localisation) |
| M4 | LVL010 load | +1,201 functions, 559 files; **374 serialized classes** (with GAME.KP3) | LVL010 loads; object census equals the original's (`live_census.py` on both) |
| M5 | LVL010 playable | +1,616 functions (start + gameplay), 607 files | hero moves, fights, camera; the first replay runs |
| M6 | LVL010 parity | | replays hash-identical to RPCS3 for 600+ frames; the known LVL010 tricks reproduce |
| M7 | Full game | 422 serialized classes, all levels | every level completable; speedrun regression suite green |
| M8 | Platforms | | Linux, macOS, WASM/WebGL2 |

Functions untraced so far (small leaves, never-run code) are pulled in through the call graph when their callers are ported.

---

## 7. Verification (to build next)

1. **Determinism hooks in the mod** (one boot-patch rebuild, one restart):
   - `KSystemClock_GetElapsedSeconds_maybe` (0x54250) or `sys_time_get_system_time` → scripted time;
   - `rand` → seed control and a call log;
   - `cellPadGetData` → recorded input.

   Plus a per-frame state hash: hero position and velocity, movement mode `+0x1808`, flags `+0x358`, GameManager state `+0x2f5`, active sector, RNG state.
2. **Replay files** recorded in RPCS3 and replayed by the remake; on divergence the first differing field is reported.
3. **Capture-replay unit tests:** the tracer stubs extended (or a separate hook set) to record arguments and the memory read by selected functions, replayed against the ported function.
4. **Timing mode "Console"**: the platform feeds `sys_time_get_system_time` so the clock sees the PS3's frame intervals.
   - The clock's own rules (0.1 s clamp, `0x3c23d70b` for a zero delta, paused and suspended behaviour) are already ported and tested.
   - RPCS3 runs LVL010 at about 59.3 fps (16.8 ms frames).
5. **Known oracle limits:**
   - RPCS3 fuses multiply-adds like the PS3 ("Use Accurate DFMA: true" in the user's config).
   - It does not reproduce the VMX denormal flush ("PPU Accurate Non-Java Mode: false"), which affects 214 vector instructions.
   - The game's debug random-frame-duration mode (CTimeManager flags +0x0a) must be off in replays; it calls `rand()` every frame.

---

## 8. Pitfalls checklist (each one has already happened)

- The decompiler's `(double)` casts are artefacts: check the assembly (`fadds`/`fmuls` vs `fadd`/`fmul`, `frsp` points).
- Constants: take them from TOC bits (`toc_lookup.py`), write hex floats.
- Fused multiply-add sites look like `a*b+c` in Ghidra.
- Big-endian byte reads of words (`+0x354` byte = bit 24 of the word).
- Constructors that leave fields uninitialised (`CKTime` timing fields, `IKTime +0x2c`): do not "fix" them.
- `class-tree.json` misses classes (use `class-tree-extra.json` too); census values 0x2xxxxxxx–0x3fxxxxxx can be floats.
- A tracer build that hooks a function changes its first instruction: never use code bytes as a signature for live tools (`gmem.py` uses the `sys_io` string).
- Bash heredocs in this environment eat backslashes: write files with the editor tools.

---

## 9. Next: implementation phase 1

**[DECOMP_IMPL-1.md](DECOMP_IMPL-1.md)**: boot → GAME.KP3 + LVL000 → working front end, in checkpoints C1.0–C1.6, built on the research in `outputs/remake/research/` (boot-and-platform, kp3-loading, frontend-rendering).

## 10. Open items, in order

1. Finish `this` typing (`ghidra_type_this.py --tier 2`, then `--tier 3`).
2. Vtable structs per class, so virtual calls show method names (generator from `vtable-runs.json` + names).
3. Array and stride detection for the giant classes, then the first struct naming round (packs `lvl010-01..`).
4. Header generator: Ghidra layouts → `dotd` class headers (with `DOTD_ASSERT_OFFSET`), regenerated as fields get names.
5. Determinism hooks + replay recorder in the mod (§7). Bundle with the next tracer rebuild to share the restart.
6. Platform skeleton: SDL3 window, GL clear, `cellPad`/`cellFs` shims.
7. M1: boot path decompiled in runtime order.
