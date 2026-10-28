// xlround.h - the game's Dinkumware lroundf, as the PS3 build computes it (library TOC 0xc25974;
// reached from game code through the bridge 0x98d3a0).
#pragma once
#include <cstdint>

namespace crt {

// 0x0077ed68 lroundf_maybe. _FDtest: zero -> 0, infinity or NaN -> 0 (with _Feraise(FE_INVALID), no other
// effect); otherwise +-0.5 as a float add (so 0.49999997f rounds to 1, as on the PS3), _FDint(x, 0) clears
// the fraction bits, and fctiwz converts (out of [-2^31, 2^31] it raises FE_INVALID and saturates).
int32_t lroundf(float x);

}  // namespace crt
