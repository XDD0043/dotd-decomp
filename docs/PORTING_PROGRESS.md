# Porting progress

Measured **2026-11-13** against the open Ghidra EBOOT inventory.

**About 41% of live engine/game functions are marked ported.** This measures source-checklist coverage. It is not a percentage of fully verified behavior, playable content, code size, development time, or remaining effort.

| Area | Live original functions | Marked ported | Explicitly partial | No checklist entry | Coverage |
|---|---:|---:|---:|---:|---:|
| K engine (k2000) | 16,395 | 6,457 | 6 | 71 | 39.4% |
| Game (Spyro2008) | 5,508 | 2,605 | 1 | 0 | 47.3% |
| Engine + game | 21,903 | 9,062 | 7 | 71 | 41.4% |

## Why the denominator is smaller than the EBOOT

Ghidra currently reports **36,930 functions**. Of these, 24,730 are classified as game/K-engine code; 2,827 of those are classified as unreferenced duplicates and excluded from the live porting target. The remaining 12,200 binary functions belong to middleware, runtimes, bridges, and thunks. Much of that code is replaced or dropped by the native port. RenderWare and CRT ports are outside the percentage above.

## Method and limits

- The Ghidra inventory and `work/library_map.json` have identical function-address sets.
- Live targets are GAME_TOC1/GAME_TOC2 entries minus `work/dead-all.json`.
- `work/tu_map.json` assigns each live target to `k2000` or `Spyro2008`, including inline/COMDAT entries.
- A unique original address counts as marked ported when a source `.cpp` checklist contains `[x]`. Repeated checklist entries count once. `[~]` entries are reported separately and excluded from the numerator.
- This is a status-marker census, not an audit of every implementation. Some `[x]` entries retain deferred branches: for example `UpdateCKSrvPhysics` lacks fixed-step body simulation, and `CPostRenderingFx_Draw` still has a deferred blur branch.
- Conversely, implementations without updated checklist ticks are not credited. The estimate can therefore overstate completeness for partial functions and undercount other work.
- 71 live target addresses have no checklist entry. They remain in the denominator and receive no credit in this metric, even where an implementation exists.
- Original compiler duplicates, constructors, destructors, and inline copies do not map one-to-one to source functions or effort. Checkpoint tests remain the evidence for verified behavior.

## Earlier documentation

`DECOMP_IMPL-1.md` section 8 contains a phase-1 planning estimate of 1,500–1,800 ports. `DECOMP_IMPL-2.md` section 1.4 records about 2,800 ports as of 2026-10-18. Those figures describe earlier scope/snapshots; neither is a current overall percentage. The checkpoint status sections describe functional progress in more detail.

## Reproduce

From the workspace root:

```sh
python work/porting_progress.py --inventory work/progress-ghidra-functions-20261028.json --as-of 2026-11-13 --write-report
```

Add `--refresh-ghidra` to replace the cached inventory using one `/list_functions?limit=0` request. The script refuses to report if the Ghidra and classification address sets differ or ownership is ambiguous. Targets without a checklist are reported separately.
