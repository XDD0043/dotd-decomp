// png.cpp - see png.h.
#include "platform/gfx/png.h"

#include <cstdio>
#include <vector>

namespace dotd::gfx {

namespace {

uint32_t g_crcTable[256];
bool g_crcReady = false;

uint32_t Crc(const uint8_t* data, size_t size, uint32_t crc = 0xffffffffu) {
    if (!g_crcReady) {
        for (uint32_t n = 0; n < 256; ++n) {
            uint32_t c = n;
            for (int k = 0; k < 8; ++k) c = (c & 1) != 0 ? 0xedb88320u ^ (c >> 1) : c >> 1;
            g_crcTable[n] = c;
        }
        g_crcReady = true;
    }
    for (size_t i = 0; i < size; ++i) crc = g_crcTable[(crc ^ data[i]) & 0xff] ^ (crc >> 8);
    return crc;
}

void PutBE32(std::vector<uint8_t>& out, uint32_t v) {
    out.push_back(static_cast<uint8_t>(v >> 24));
    out.push_back(static_cast<uint8_t>(v >> 16));
    out.push_back(static_cast<uint8_t>(v >> 8));
    out.push_back(static_cast<uint8_t>(v));
}

void Chunk(std::vector<uint8_t>& out, const char* type, const std::vector<uint8_t>& data) {
    PutBE32(out, static_cast<uint32_t>(data.size()));
    const size_t start = out.size();
    out.insert(out.end(), type, type + 4);
    out.insert(out.end(), data.begin(), data.end());
    PutBE32(out, Crc(out.data() + start, out.size() - start) ^ 0xffffffffu);
}

}  // namespace

bool WritePngRgb(const char* path, int width, int height, const uint8_t* rgb) {
    // The filtered image: each row starts with filter byte 0.
    const size_t rowBytes = static_cast<size_t>(width) * 3;
    std::vector<uint8_t> raw;
    raw.reserve((rowBytes + 1) * height);
    for (int y = 0; y < height; ++y) {
        raw.push_back(0);
        raw.insert(raw.end(), rgb + y * rowBytes, rgb + (y + 1) * rowBytes);
    }
    // zlib stream of stored deflate blocks (at most 65535 bytes each), then the Adler-32.
    std::vector<uint8_t> z;
    z.push_back(0x78);
    z.push_back(0x01);
    size_t pos = 0;
    do {
        const size_t n = raw.size() - pos > 65535 ? 65535 : raw.size() - pos;
        z.push_back(pos + n == raw.size() ? 1 : 0);
        z.push_back(static_cast<uint8_t>(n));
        z.push_back(static_cast<uint8_t>(n >> 8));
        z.push_back(static_cast<uint8_t>(~n));
        z.push_back(static_cast<uint8_t>(~n >> 8));
        z.insert(z.end(), raw.begin() + static_cast<std::ptrdiff_t>(pos), raw.begin() + static_cast<std::ptrdiff_t>(pos + n));
        pos += n;
    } while (pos < raw.size());
    uint32_t a = 1, b = 0;
    for (uint8_t byte : raw) {
        a = (a + byte) % 65521u;
        b = (b + a) % 65521u;
    }
    PutBE32(z, (b << 16) | a);

    std::vector<uint8_t> out = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n'};
    std::vector<uint8_t> ihdr;
    PutBE32(ihdr, static_cast<uint32_t>(width));
    PutBE32(ihdr, static_cast<uint32_t>(height));
    ihdr.push_back(8);  // bit depth
    ihdr.push_back(2);  // colour type: RGB
    ihdr.push_back(0);
    ihdr.push_back(0);
    ihdr.push_back(0);
    Chunk(out, "IHDR", ihdr);
    Chunk(out, "IDAT", z);
    Chunk(out, "IEND", {});
    std::FILE* f = std::fopen(path, "wb");
    if (f == nullptr) return false;
    const bool ok = std::fwrite(out.data(), 1, out.size(), f) == out.size();
    return std::fclose(f) == 0 && ok;
}

}  // namespace dotd::gfx
