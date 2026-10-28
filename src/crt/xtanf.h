// xtanf.h - the game's float tangent (Dinkumware tanf, library TOC 0xc25974), as the PS3 build computes it.
#pragma once

namespace crt {

// 0x00780a90 tanf: the tangent of x (the argument reduced by _Fmodf_RangeReduce_maybe outside +-2^k, then the
// quadrant polynomial). step 5, the shared helpers.
float Tanf(float x);
// 0x00780bf0 _Fmodf_RangeReduce_maybe: |y| * (q - trunc(q)) with q = x / |y| in single precision (fabs, fdivs, the
// truncation by the exponent mask, fsubs, fmuls).
float FmodfRangeReduce(float x, float y);

}  // namespace crt
