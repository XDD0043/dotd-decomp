// vmx_ops.h - the PPU's AltiVec (VMX) float operations, one lane at a time, as the replays' reference runs them: RPCS3's
// PPU LLVM recompiler (rpcs3/Emu/Cell/PPUTranslator.cpp, master 2026-11):
//   - every float result goes through VecHandleResult: with VSCR[NJ] set (the PS3 runs in non-Java mode: jm_mask
//     0x7f800000) a result whose exponent field is 0 (a denormal or a zero) becomes a zero of its sign; the inputs are
//     used as they are (no denormals-are-zero on the inputs: "Set DAZ and FTZ" is off by default);
//   - vmaddfp is a fused multiply-add (fmuladd on an FMA host), vnmsubfp -(a * c - b) fused;
//   - vrefp is 1.0f / b and vrsqrtefp 1.0f / sqrt(b), correctly rounded (the estimate tables are only used with the
//     non-default "PPU Set VEST" option), each flushed as above;
//   - the compares are ordered (a NaN compares false).
//
// PERF: the fused multiply-adds go through ppc::detail::FusedMulAdd (crt/ppc_ops.h): the FMA3 instruction when the CPU
// has it instead of the out-of-line std::fmaf of ucrtbase, the same bits (a NaN result is computed by the library).
#pragma once
#include <cmath>
#include <cstdint>
#include <cstring>

#include "crt/ppc_ops.h"

namespace vmx {

// The NJ-mode result: an exponent field of 0 keeps only the sign.
inline float Nj(float r) {
    uint32_t w;
    std::memcpy(&w, &r, 4);
    if ((w & 0x7f800000u) == 0) w &= 0x80000000u;
    std::memcpy(&r, &w, 4);
    return r;
}

// vaddfp / vsubfp
inline float Add(float a, float b) { return Nj(a + b); }
inline float Sub(float a, float b) { return Nj(a - b); }
// vmaddfp vD, vA, vC, vB: vA * vC + vB, one rounding.
inline float Madd(float a, float c, float b) { return Nj(ppc::detail::FusedMulAdd(a, c, b)); }
// vnmsubfp vD, vA, vC, vB: -(vA * vC - vB), one rounding.
inline float Nmsub(float a, float c, float b) { return Nj(-ppc::detail::FusedMulAdd(a, c, -b)); }
// vrefp / vrsqrtefp
inline float Refp(float b) { return Nj(1.0f / b); }
inline float Rsqrtefp(float b) { return Nj(1.0f / std::sqrt(b)); }
// vcmpgefp / vcmpgtfp lanes (true: all ones).
inline bool CmpGe(float a, float b) { return a >= b; }
inline bool CmpGt(float a, float b) { return a > b; }

}  // namespace vmx
