// ppc_ops.h - PowerPC (Cell PPU) arithmetic, exactly as the PS3 build computes it.
//
// Decompiled code must call these wherever the original used the instruction, because the plain C
// expression gives a different result on x64/WASM for some inputs:
//
//   original instruction            plain C (wrong)          use
//   fmadds/fmsubs/fnmadds/fnmsubs   a*b+c (two roundings)    ppc::fmadds(a,b,c) ...   (11,395 sites)
//   fmadd/fmsub/fnmadd/fnmsub       a*b+c                    ppc::fmadd(a,b,c) ...
//   fctiwz / fctidz                 (int)x (UB / x86 value)  ppc::fctiwz(x), ppc::fctidz(x)
//   fctiw                           lrint                    ppc::fctiw(x)
//   divw / divwu                    a/b (traps on x86)       ppc::divw(a,b), ppc::divwu(a,b)
//   slw / srw / sraw (+ 64-bit)     a<<n (UB for n >= 32)    ppc::slw(a,n), ...
//   rlwinm                          shifts + masks           ppc::rlwinm(x, sh, mb, me)
//
// Edge-case values follow RPCS3's PPU interpreter (the oracle we compare against; reference only,
// no code copied): divw/divwu return 0 on a zero divisor or INT32_MIN / -1; fctiwz saturates and
// returns INT32_MIN for NaN. Hardware results for those undefined cases are still to be confirmed.
// fres / frsqrte (10 sites) need the measured estimate tables and are not provided yet.
//
// Compile with floating-point contraction OFF (MSVC /fp:precise without /fp:contract; GCC/Clang
// -ffp-contract=off), or the compiler may fuse expressions the original did not.
#pragma once
#include <cmath>
#include <cstdint>
#include <limits>

// PERF (MSVC x86/x64): std::fmaf / std::fma are out-of-line calls into ucrtbase (about 4 ns each on x64, 6 ns on x86,
// against under 1 ns for the instruction); the trails' Bezier sampling alone spent 4% of a frame's CPU in them. On a CPU
// with FMA3 (and the OS saving the AVX state) the VFMADD instruction is used instead. Both are IEEE 754 fusedMultiplyAdd
// (one rounding, in the current MXCSR mode), so every non-NaN result is the same bits (signed zeros and infinities
// included). A NaN result's payload is not: with two NaN operands it depends on the operand order of the VFMADD form
// the compiler picks (and the x86 library prefers `a`), so a NaN result is computed again by the library call, giving
// exactly its bits. Without FMA3 the library call stays.
#if defined(_MSC_VER) && !defined(__clang__) && (defined(_M_X64) || defined(_M_IX86))
#include <immintrin.h>
#include <intrin.h>
#define DOTD_PPC_HW_FMA 1
namespace ppc::detail {
inline bool DetectHardwareFma() {
    int regs[4];
    __cpuid(regs, 1);
    const int ecx = regs[2];
    const bool fma = (ecx & (1 << 12)) != 0, osxsave = (ecx & (1 << 27)) != 0, avx = (ecx & (1 << 28)) != 0;
    return fma && osxsave && avx && (_xgetbv(0) & 6u) == 6u;  // XMM and YMM state enabled by the OS
}
// Set during static initialisation; a call before that takes the library path (the same result).
inline const bool g_hardwareFma = DetectHardwareFma();
}  // namespace ppc::detail
#else
#define DOTD_PPC_HW_FMA 0
#endif

namespace ppc {

namespace detail {
inline float FusedMulAdd(float a, float b, float c) {
#if DOTD_PPC_HW_FMA
    if (g_hardwareFma) {
        const float r = _mm_cvtss_f32(_mm_fmadd_ss(_mm_set_ss(a), _mm_set_ss(b), _mm_set_ss(c)));
        if (r == r) return r;  // not NaN (/fp:precise keeps this test)
    }
#endif
    return std::fmaf(a, b, c);
}
inline double FusedMulAdd(double a, double b, double c) {
#if DOTD_PPC_HW_FMA
    if (g_hardwareFma) {
        const double r = _mm_cvtsd_f64(_mm_fmadd_sd(_mm_set_sd(a), _mm_set_sd(b), _mm_set_sd(c)));
        if (r == r) return r;
    }
#endif
    return std::fma(a, b, c);
}
}  // namespace detail

// ---- fused multiply-add: one rounding, like the FPU -------------------------------------------
// The single-precision forms operate on values that are already exact floats (loaded with lfs or
// produced by single ops), so fmaf equals the hardware's round-to-single of the exact a*b+c.
inline float fmadds(float a, float b, float c) { return detail::FusedMulAdd(a, b, c); }
inline float fmsubs(float a, float b, float c) { return detail::FusedMulAdd(a, b, -c); }
inline float fnmadds(float a, float b, float c) { return -detail::FusedMulAdd(a, b, c); }
inline float fnmsubs(float a, float b, float c) { return -detail::FusedMulAdd(a, b, -c); }
inline double fmadd(double a, double b, double c) { return detail::FusedMulAdd(a, b, c); }
inline double fmsub(double a, double b, double c) { return detail::FusedMulAdd(a, b, -c); }
inline double fnmadd(double a, double b, double c) { return -detail::FusedMulAdd(a, b, c); }
inline double fnmsub(double a, double b, double c) { return -detail::FusedMulAdd(a, b, -c); }

// frsp: round a double to single precision (round to nearest even, the PS3's default mode)
inline float frsp(double x) { return static_cast<float>(x); }

// ---- float -> integer -------------------------------------------------------------------------
// fctiwz: truncate toward zero, saturate; NaN -> INT32_MIN (0x80000000).
inline int32_t fctiwz(double x) {
    if (std::isnan(x)) return std::numeric_limits<int32_t>::min();
    if (x >= 2147483648.0) return std::numeric_limits<int32_t>::max();
    if (x <= -2147483649.0) return std::numeric_limits<int32_t>::min();
    return static_cast<int32_t>(x);  // in range: C truncation is exact
}
// fctidz: 64-bit variant.
inline int64_t fctidz(double x) {
    if (std::isnan(x)) return std::numeric_limits<int64_t>::min();
    if (x >= 9223372036854775808.0) return std::numeric_limits<int64_t>::max();
    if (x < -9223372036854775808.0) return std::numeric_limits<int64_t>::min();
    return static_cast<int64_t>(x);
}
// fctiw: round to nearest even (the default FPSCR rounding mode), saturate; NaN -> INT32_MIN.
inline int32_t fctiw(double x) {
    if (std::isnan(x)) return std::numeric_limits<int32_t>::min();
    const double r = std::nearbyint(x);  // assumes the host is in round-to-nearest (the C default)
    if (r >= 2147483648.0) return std::numeric_limits<int32_t>::max();
    if (r < -2147483648.0) return std::numeric_limits<int32_t>::min();
    return static_cast<int32_t>(r);
}

// ---- integer division (no traps) ---------------------------------------------------------------
inline int32_t divw(int32_t a, int32_t b) {
    if (b == 0 || (a == std::numeric_limits<int32_t>::min() && b == -1)) return 0;
    return a / b;
}
inline uint32_t divwu(uint32_t a, uint32_t b) { return b == 0 ? 0u : a / b; }
inline int64_t divd(int64_t a, int64_t b) {
    if (b == 0 || (a == std::numeric_limits<int64_t>::min() && b == -1)) return 0;
    return a / b;
}
inline uint64_t divdu(uint64_t a, uint64_t b) { return b == 0 ? 0u : a / b; }

// ---- shifts: the amount is the low 6 bits of rB; 32..63 shifts everything out ----------------
inline uint32_t slw(uint32_t a, uint32_t n) { n &= 63; return n >= 32 ? 0u : a << n; }
inline uint32_t srw(uint32_t a, uint32_t n) { n &= 63; return n >= 32 ? 0u : a >> n; }
inline int32_t sraw(int32_t a, uint32_t n) {
    n &= 63;
    if (n >= 32) return a < 0 ? -1 : 0;
    return a >> n;  // arithmetic shift on every supported compiler (C++20 guarantees it)
}
inline uint64_t sld(uint64_t a, uint32_t n) { n &= 127; return n >= 64 ? 0u : a << n; }
inline uint64_t srd(uint64_t a, uint32_t n) { n &= 127; return n >= 64 ? 0u : a >> n; }
inline int64_t srad(int64_t a, uint32_t n) {
    n &= 127;
    if (n >= 64) return a < 0 ? -1 : 0;
    return a >> n;
}

// ---- rotate-and-mask (rlwinm / rlwnm / rlwimi) -------------------------------------------------
// Bit numbering is IBM's: bit 0 is the most significant bit of the 32-bit word.
inline uint32_t rotl32(uint32_t x, uint32_t n) { n &= 31; return n ? (x << n) | (x >> (32 - n)) : x; }
inline uint32_t mask32(uint32_t mb, uint32_t me) {
    mb &= 31; me &= 31;
    const uint32_t a = 0xffffffffu >> mb;
    const uint32_t b = 0xffffffffu << (31 - me);
    return mb <= me ? (a & b) : (a | b);
}
inline uint32_t rlwinm(uint32_t x, uint32_t sh, uint32_t mb, uint32_t me) { return rotl32(x, sh) & mask32(mb, me); }
inline uint32_t rlwnm(uint32_t x, uint32_t n, uint32_t mb, uint32_t me) { return rotl32(x, n & 31) & mask32(mb, me); }
inline uint32_t rlwimi(uint32_t dst, uint32_t x, uint32_t sh, uint32_t mb, uint32_t me) {
    const uint32_t m = mask32(mb, me);
    return (rotl32(x, sh) & m) | (dst & ~m);
}

// ---- count leading zeros ------------------------------------------------------------------------
inline uint32_t cntlzw(uint32_t x) {
    uint32_t n = 0;
    if (x == 0) return 32;
    while (!(x & 0x80000000u)) { x <<= 1; ++n; }
    return n;
}

}  // namespace ppc
