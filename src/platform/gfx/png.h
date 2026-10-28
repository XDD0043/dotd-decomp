// png.h - a minimal PNG writer for screenshots (8-bit RGB, zlib "stored" blocks: no compression, no
// third-party code). New platform code.
#pragma once
#include <cstdint>

namespace dotd::gfx {

// Writes width x height RGB pixels (top row first, 3 bytes each) to path. False on an I/O error.
bool WritePngRgb(const char* path, int width, int height, const uint8_t* rgb);

}  // namespace dotd::gfx
