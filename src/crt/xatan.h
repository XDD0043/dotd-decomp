// xatan.h - the game's float arc cosine (Dinkumware acosf over _FAtan), as the PS3 build computes it
// (library TOC 0xc25974).
#pragma once
#include <cstdint>

namespace crt {

// 0x00780c90 Math_Acosf (called through TocBridge_Math_Acosf 0x98e1a0): the arc cosine of x. NaN above 1.
float Acosf(float x);
// 0x00780d70 Math_Asinf (TocBridge_Math_Asinf_maybe): the arc sine of x (step 5, the shared helpers).
float Asinf(float x);

}  // namespace crt
