// xfsin.h - the library's float _FSin (Dinkumware xfsin.c) and sqrtf (xfsqrt.c), as the PS3 build computes them
// (library TOC 0xc25974). Game code reaches them through TOC bridges (TocBridge__FSin_maybe 0x98f2a0; the sqrtf of
// Math_Acosf_2_maybe 0x77e720). port-final F06 (CKHkS08ClampGun).
#pragma once
#include <cstdint>

namespace crt {

// 0x00780470 _FSin_maybe (_FSin(float x, unsigned int qoff)): qoff 0 = sine, 1 = cosine. _FDtest first: infinity gives
// the NaN 0xc4adc0 (_Feraise EDOM), a NaN itself, zero itself (the sine) or 1 (the cosine); outside +-40.7 the argument
// is reduced by fmodf(x, 2 pi) (0x781278, exact); then the quadrant (x * 2/pi rounded half away from zero by fctiwz),
// the two-part pi/2 reduction (fmadds) and the polynomials, or x / 1 below _FRteps (2^-12).
float FSinf(float x, uint32_t qoff);

// 0x0077f6b8 sqrtf_maybe (Dinkumware sqrtf, no fsqrts): _FDunscale (x = m * 2^e, m in [0.5, 1)), an odd exponent
// moved into m (m + m), a quadratic seed, two Newton steps (y + m / y, then 0.25 y + m / y), _FDscale by e / 2.
// A negative argument (or -infinity) gives the NaN 0xc4adc0; zero, +infinity and NaN return themselves.
float Sqrtf(float x);

}  // namespace crt
