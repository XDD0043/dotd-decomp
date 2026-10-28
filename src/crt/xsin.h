// xsin.h - the game's Dinkumware _Sin (libm xsin.c), ported from the PS3 code (library TOC 0xc25974).
// sin(x) = Sin(x, 0), cos(x) = Sin(x, 1). Double precision, as the PS3 computes it (fmadd/fmsub chains).
#pragma once
#include <cstdint>

namespace crt {

// 0x00780880 _Sin_maybe (Dinkumware _Sin(double x, unsigned int qoff)): qoff 0 = sine, 1 = cosine.
double Sin(double x, uint32_t qoff);

}  // namespace crt
