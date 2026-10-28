// xsinf.h - the game's float sine and cosine polynomials, as the PS3 build computes them.
//
// Two forms exist. Game code inlines the octant polynomials for a non-negative argument, with the
// reduction x * 4/pi done in single precision (fmuls); the library's cosf 0x009a11d8 / sinf 0x009a1390
// (library TOC 0xc25974) handle any sign and multiply in double precision before the same polynomials.
// Both forms agree except where the single and double product round differently.
#pragma once
#include <cstdint>

namespace crt {

// The game's inlined cosf / sinf: x must have its sign bit clear (the caller tests the bits, as the
// original does) and the product x * 4/pi is a float multiplication.
float InlineCosf(float x);
float InlineSinf(float x);

// 0x009a11d8 cosf and 0x009a1390 sinf: the library functions. A negative argument is handled as the
// original does (cosine of -x; the sine's sign flipped); the product x * 4/pi is a double multiplication.
float LibCosf(float x);
float LibSinf(float x);

}  // namespace crt
