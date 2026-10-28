// xatanf.h - the game's float arc tangent (Ghidra Math_Atanf_maybe 0x00780e58 / _FAtan_maybe 0x0077fe18, library TOC).
#pragma once
#include <cstdint>

namespace crt {

// Math_Atanf_maybe: atan of x in radians, single precision (the argument range-reduced to [0, 1], then
// _FAtan's rational approximation and the octant constant added).
float Atanf(float x);

}  // namespace crt
