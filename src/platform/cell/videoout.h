// videoout.h - cellVideoOut as the game uses it (only gamma, from the brightness option).
// The value is applied by the final blit in platform/gfx.
#pragma once
#include <cstdint>

int32_t cellVideoOutSetGamma(uint32_t videoOut, float gamma);

namespace dotd::platform {
float GetVideoOutGamma();  // 1.0 = neutral
}
