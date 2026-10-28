# Decompilation style guide

The remake must behave exactly like the PS3 build (same results frame by frame, bugs included) and stay readable and traceable to the original addresses. These rules exist for the first goal; follow them even where they look pedantic.

## 1. Traceability
- **Every function carries its original address and Ghidra name** on the line above it:
  ```cpp
  // 0x002c8fb0 KBase1544_Load
  int32_t CKS08GameManager::Load(IKFile* file, int32_t type) { ... }
  ```
  The progress tool reads these comments; a function without one does not count as done.
- **One `.cpp` per reconstructed original translation unit** (`src/k2000/...`, `src/Spyro2008/...`), as generated from `work/tu_map.json`.
  - Delete the `@generated` line when real code goes in; the generator then never touches the file again.
  - Keep the checklist comment until the file is complete; tick items (`[x]`) as you go.
- Class declarations go in a header with the same name next to the `.cpp` (`CKLevel.h`).
- Out-of-line copies of inline methods (marked `[inline]` in the checklists) belong in that header, written once.

## 2. Names
- **Classes keep their K-engine names** (`CKHkS08Hero`, `CKSrvCollision`, `CKLevel`). Unregistered bases use their curated name (`CKHkS08HeroBase` for key 0x3642), never `KBase3642` in new code.
- **Methods:** UpperCamelCase, as the K engine names its virtuals (`Load`, `Save`, `LevelReset`, `Update`). A Ghidra name `CKLevel_GetActiveSector` becomes `CKLevel::GetActiveSector`.
- **Members:** `m_` + lowerCamelCase of the field's base name in Ghidra (`nCurrentSector` / `CurrentSector` → `m_currentSector`). A placeholder `pUnk1c` stays `m_unk1c` until it is named.
- **Free functions:** UpperCamelCase. **Constants:** `k` + UpperCamelCase. **Macros:** `DOTD_...`.
- A name that is still an inference keeps the inference visible: `// _maybe: ...` comment next to it.

## 3. Struct layout
- Keep field order and offsets: every class has its exact PS3 size. Check them in the 32-bit builds (`windows-msvc-x86-parity`, wasm32), where pointers are 4 bytes like on the PS3:
  ```cpp
  DOTD_ASSERT_SIZE(CKLevel, 0x48);
  DOTD_ASSERT_OFFSET(CKLevel, m_currentSector, 0x18);
  ```
  (`src/k2000/core/Layout.h`; both are no-ops when `DOTD_PS3_LAYOUT` is 0.)
- **Never index into a multi-byte field by byte offset.**
  - The PS3 is big-endian. The original's byte read at `+0x354` is bit 24 of the 32-bit word at `+0x354` (`CKHkS08Hero` flags).
  - Write `(m_flags354 >> 24) & 1`, never `((uint8_t*)this)[0x354]`.
- Data from KP3 files is little-endian on disc and already native on little-endian hosts. The `IKFile` readers do the conversion; game code never byte-swaps.

## 4. Arithmetic that must match bit for bit
- **Fused multiply-add:** every original `fmadds`/`fmsubs`/`fnmadds`/`fnmsubs` (and the double forms) is written with `ppc::fmadds(a, b, c)` etc. (`src/crt/ppc_ops.h`).
  - The Ghidra export marks those sites.
  - A plain `a * b + c` is only correct where the original used separate `fmuls` + `fadds`.
- **Float vs double exactly as in the assembly.**
  - `fmuls`/`fadds` are float operations. `fmul`/`fadd` are double operations, followed by `frsp` where the result is stored as float.
  - **Float literals need the `f` suffix.** `x * 0.5` promotes to double, which is a different result from the original `fmuls` with `0.5f`.
  - Take constants from the TOC value, exactly: `0x3dcccccd` is `0.1f`. Write `1.0e-1f` or a hex-float when in doubt.
- **float→int:** `ppc::fctiwz(x)` (it saturates; a C cast is undefined out of range and gives a different value on x86).
- **Integer division:** `ppc::divw` / `ppc::divwu` wherever the divisor can be 0 or the dividend `INT32_MIN`.
- **Variable shifts:** `ppc::slw` / `ppc::srw` / `ppc::sraw` (shifting by 32 to 63 gives 0 on PPC; it is undefined behaviour in C).
- **Bit fields from `rlwinm`/`rlwimi`:** `ppc::rlwinm(x, sh, mb, me)` or the equivalent shift and mask, written out clearly.
- **Math functions:** never the host libm in simulation code. Use the ports of the game's own Dinkumware routines in `src/crt/` (`crt::sinf`, `crt::atan2f`, ...).
- **Random numbers:** only `crt::rand` (the game's `rand()` LCG); never `std::` random.
- **Time:** only through the engine clock (`CTimeManager`/`IKTime`), which the platform layer feeds. Never read the host clock in game code.

## 5. Bugs and glitches
- **Keep every original bug.** Mark it where it is understood:
  ```cpp
  // BUG(original): the timer is a float and stops advancing above 2^19 seconds (adding dt rounds back).
  m_timer += dt;
  #if DOTD_FIX_BUGS
  ...
  #endif
  ```
  `DOTD_FIX_BUGS` defaults to 0 and is never set in parity builds.
- **Uninitialised reads, out-of-bounds reads and use-after-free in the original are bugs too.**
  - Reproduce them through the original allocator and layout, never with "safe" replacements.
  - Comment them with `BUG(original)`.

## 6. C++ usage
- **C++17.** No exceptions or RTTI in game code (the original had neither). No `std::` containers in simulation code unless their iteration order and allocation behaviour match the original's K containers; port those containers instead.
- **Virtual methods are declared in original vtable slot order** with the slot in a comment (`// vt+0x2c`). The root slots are in `src/k2000/core/IKBaseClass.h` and `IKSerializable.h`, IKUpdatable's in `IKUpdatable.h`.
- **No undefined behaviour the compilers could exploit.**
  - Signed overflow wraps, as on PPC: build with `-fwrapv`; MSVC does not exploit it.
  - Type punning goes through `memcpy` or `std::bit_cast`.
  - `-fno-strict-aliasing` is set for decompiled code.
- Use fixed-width integer types (`int32_t`, `uint8_t`) wherever the width matters, which is almost everywhere.

## 7. Floating-point build settings (do not change)
MSVC `/fp:precise` without `/fp:contract`. GCC/Clang `-ffp-contract=off -fno-fast-math`. No `/arch:` or `-march` flags that enable automatic contraction. `CMakeLists.txt` sets these; per-file overrides are not allowed.

## Names from the XXL2 debug symbols

The XXL2 Mac build (same engine, same class keys) gives the original names. Use them, with the evidence in a comment, when the structure matches:
- **Classes:** IKSerializable, IKUpdatable, IKService, IKModule, IKGameObject, ...
- **Virtual methods:** take the name of their slot.
- **Members:** use XXL2's Hungarian names (`m_ui32NbKSound`, `m_pRwStream`, `m_afDeltaTime[3]`) when the load order or the use matches. Keep the PS3 types and offsets, and say so where they differ from XXL2.
- **Enums:** `ESerializationType` `K_LEVEL_PLATEFORMS`, ..., `IKTime::ECurrentState`.

Look things up with `work/xxl2_syms.py` (`vtable CLASS`, `dis LINKAGE --class CLASS`) and in `work/xxl2-dwarf/classes.jsonl`. Background and tables: `outputs/remake/research/xxl2-symbols.md`. DotD is a later branch: check every name against the PS3 code.
