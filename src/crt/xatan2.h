// xatan2.h - the game's two-argument arc tangents (Dinkumware atan2f / atan2) and the float logarithm (_FLog), as
// the PS3 build computes them (library TOC 0xc25974). C2.8 port-rest R01 (the quaternion helpers of Quat.cpp).
#pragma once
#include <cstdint>

namespace crt {

// 0x0077e9f0 atan2f (TocBridge_atan2f 0x98f2c0): the angle of (x, y) in radians, single precision: _FDtest of both
// arguments (NaN, infinity, zero, finite), then _FAtan_maybe 0x0077fe18 of the reduced ratio and the octant flags.
float Atan2f(float y, float x);
// 0x0077e868 atan2 (double): the same with _Dtest 0x0077fbe8 and _Atan_maybe 0x0077f990 (the double rational
// approximation, the octant table 0x00a727e0).
double Atan2(double y, double x);
// 0x00780270 _FLog_maybe (TocBridge__FLog_maybe 0x98f2d0): the logarithm of x; base 0 the natural one, base > 0
// log10, base < 0 log2 (_FDunscale_maybe 0x00960a78 / _FDnorm_maybe 0x0096ae60 split x into [1/2, 1) and its exponent).
// The error raising (_Feraise 0x00780048: errno) is the platform's; the results are the original's (zero: -infinity,
// a negative argument or -infinity: NaN).
float FLog(float x, int32_t base);

}  // namespace crt
