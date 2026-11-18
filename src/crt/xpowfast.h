// xpowfast.h - the library's fast power (library TOC 0xc25974): 2^(y * log2 x) by two short polynomials, as the PS3
// build computes it (the fog boxes' fades above the seventh power, the lightning strip's joints).
#pragma once

namespace crt {

// 0x007814c8 Math_Log2Fast_maybe: the exponent of x plus a polynomial of its mantissa - 1 (x > 0).
float Log2Fast(float x);
// 0x00781558 Math_Exp2Fast_maybe: 2^x as the exponent ceil(x) (x + 0.99999994 truncated, for x >= 0) times a polynomial
// of (ceil(x) - x) ln 2; an exponent outside 0..255 gives 0 (below) or infinity (above).
float Exp2Fast(float x);
// 0x00780c50 Math_PowFast_maybe (through TocBridge_Math_PowFast_maybe 0x98ec60): Exp2Fast(Log2Fast(x) * y).
float PowFast(float x, float y);

}  // namespace crt
