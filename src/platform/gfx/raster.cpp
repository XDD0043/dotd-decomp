// raster.cpp - see raster.h. New platform code.
#include "platform/gfx/raster.h"

#include <utility>
#ifdef __EMSCRIPTEN__
#include <chrono>
#include <mutex>
#include <set>
#endif

#include "platform/gfx/device.h"
#include "platform/gfx/perf.h"
#include "platform/log.h"

namespace dotd::gfx {

struct RasterTexture {
    // glTextureReferenceSCE: a DDS face's mip chain (the first face referenced) and its GL format.
    bool referenced = false;
    uint32_t referenceFormat = 0;
    int referenceLevels = 0;
    int referenceWidth = 0;
    int referenceHeight = 0;
    std::vector<uint8_t> referenceData;
    // glTexImage2D: the levels given so far, as RGBA8 (an R G B level gets alpha 255, what GL samples from GL_RGB).
    struct Level {
        int width = 0;
        int height = 0;
        std::vector<uint8_t> rgba;
    };
    std::vector<Level> levels;
    bool hasMaxLod = false;
    float maxLod = 0.0f;
    uint32_t device = 0;  // the device texture, once made
    bool deviceTried = false;
};

namespace {

void DropDevice(RasterTexture* texture) {
    if (texture->device != 0) DestroyTexture(texture->device);
    texture->device = 0;
    texture->deviceTried = false;
}

uint32_t MakeReferencedTexture(const RasterTexture& t) {
    TextureFormat format;
    uint32_t blockBytes = 16;
    switch (t.referenceFormat) {
        case 0x83f1:  // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
            format = TextureFormat::kBC1;
            blockBytes = 8;
            break;
        case 0x83f2:  // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
            format = TextureFormat::kBC2;
            break;
        case 0x83f3:  // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
            format = TextureFormat::kBC3;
            break;
        default:
            DOTD_LOG("gfx: raster texture format %04x not supported", t.referenceFormat);
            return 0;
    }
    std::vector<TextureLevel> levels;
    uint32_t w = static_cast<uint32_t>(t.referenceWidth), h = static_cast<uint32_t>(t.referenceHeight);
    size_t offset = 0;
    const size_t available = t.referenceData.size();
    for (int m = 0; m < t.referenceLevels; ++m) {
        const size_t size = static_cast<size_t>((w + 3) / 4) * ((h + 3) / 4) * blockBytes;
        if (offset + size > available) break;
        levels.push_back(TextureLevel{t.referenceData.data() + offset, size});
        offset += size;
        w = w > 1 ? w >> 1 : 1;
        h = h > 1 ? h >> 1 : 1;
    }
    if (levels.empty()) return 0;
    return CreateTexture(format, t.referenceWidth, t.referenceHeight, static_cast<int>(levels.size()), levels.data());
}

uint32_t MakeImageTexture(const RasterTexture& t) {
    std::vector<TextureLevel> levels;
    for (const RasterTexture::Level& level : t.levels) {
        if (level.rgba.empty()) break;  // the levels from 0 up to the first one not given
        levels.push_back(TextureLevel{level.rgba.data(), level.rgba.size()});
    }
    if (levels.empty()) return 0;
    return CreateTexture(TextureFormat::kRGBA8, t.levels[0].width, t.levels[0].height, static_cast<int>(levels.size()),
                         levels.data());
}

}  // namespace

#ifdef __EMSCRIPTEN__
namespace {
// The web build's list of the textures that exist (MakeRasterTexturesAhead); the loader thread makes textures too.
std::mutex g_allMutex;
std::set<RasterTexture*> g_all;
}  // namespace
#endif

RasterTexture* GenRasterTexture() {
    RasterTexture* texture = new RasterTexture();
#ifdef __EMSCRIPTEN__
    std::lock_guard<std::mutex> lock(g_allMutex);
    g_all.insert(texture);
#endif
    return texture;
}

void DeleteRasterTexture(RasterTexture* texture) {
    if (texture == nullptr) return;
#ifdef __EMSCRIPTEN__
    {
        std::lock_guard<std::mutex> lock(g_allMutex);
        g_all.erase(texture);
    }
#endif
    DropDevice(texture);
    delete texture;
}

void RasterTextureReferenceDds(RasterTexture* texture, uint32_t format, int levels, int width, int height,
                               std::vector<uint8_t> data) {
    if (texture->referenced) return;  // a cube map's later faces: the 2D device texture shows the first
    texture->referenced = true;
    texture->referenceFormat = format;
    texture->referenceLevels = levels;
    texture->referenceWidth = width;
    texture->referenceHeight = height;
    texture->referenceData = std::move(data);
    DropDevice(texture);
}

void RasterTextureImage(RasterTexture* texture, int level, int width, int height, int bytesPerPixel,
                        const uint8_t* pixels, int stride) {
    if (level < 0 || width <= 0 || height <= 0) return;
    if (static_cast<size_t>(level) >= texture->levels.size()) texture->levels.resize(static_cast<size_t>(level) + 1);
    RasterTexture::Level& out = texture->levels[static_cast<size_t>(level)];
    out.width = width;
    out.height = height;
    out.rgba.resize(static_cast<size_t>(width) * height * 4);
    for (int y = 0; y < height; ++y) {
        const uint8_t* src = pixels + static_cast<size_t>(y) * stride;
        uint8_t* dst = out.rgba.data() + static_cast<size_t>(y) * width * 4;
        for (int x = 0; x < width; ++x) {
            dst[x * 4 + 0] = src[x * bytesPerPixel + 0];
            dst[x * 4 + 1] = src[x * bytesPerPixel + 1];
            dst[x * 4 + 2] = src[x * bytesPerPixel + 2];
            dst[x * 4 + 3] = bytesPerPixel == 4 ? src[x * 4 + 3] : 0xff;
        }
    }
    DropDevice(texture);
}

namespace {
int Exp5To8R(uint32_t c) { return ((c >> 8) & 0xf8) | ((c >> 13) & 0x7); }
int Exp6To8G(uint32_t c) { return ((c >> 3) & 0xfc) | ((c >> 9) & 0x3); }
int Exp5To8B(uint32_t c) { return ((c << 3) & 0xf8) | ((c >> 2) & 0x7); }

// dxt135_decode_imageblock: texel (i, j) of an 8-byte colour block; type 0 RGB DXT1, 1 RGBA DXT1, 2 DXT3 / DXT5 (always
// the four-colour interpolation).
void DecodeColorBlock(const uint8_t* b, int i, int j, int type, uint8_t* rgba) {
    const uint32_t color0 = b[0] | (b[1] << 8);
    const uint32_t color1 = b[2] | (b[3] << 8);
    const uint32_t bits = b[4] | (b[5] << 8) | (b[6] << 16) | (static_cast<uint32_t>(b[7]) << 24);
    const uint32_t code = (bits >> (2 * (j * 4 + i))) & 3;
    const bool four = type > 1 || color0 > color1;
    rgba[3] = 255;
    switch (code) {
        case 0:
            rgba[0] = static_cast<uint8_t>(Exp5To8R(color0));
            rgba[1] = static_cast<uint8_t>(Exp6To8G(color0));
            rgba[2] = static_cast<uint8_t>(Exp5To8B(color0));
            break;
        case 1:
            rgba[0] = static_cast<uint8_t>(Exp5To8R(color1));
            rgba[1] = static_cast<uint8_t>(Exp6To8G(color1));
            rgba[2] = static_cast<uint8_t>(Exp5To8B(color1));
            break;
        case 2:
            if (four) {
                rgba[0] = static_cast<uint8_t>((Exp5To8R(color0) * 2 + Exp5To8R(color1)) / 3);
                rgba[1] = static_cast<uint8_t>((Exp6To8G(color0) * 2 + Exp6To8G(color1)) / 3);
                rgba[2] = static_cast<uint8_t>((Exp5To8B(color0) * 2 + Exp5To8B(color1)) / 3);
            } else {
                rgba[0] = static_cast<uint8_t>((Exp5To8R(color0) + Exp5To8R(color1)) / 2);
                rgba[1] = static_cast<uint8_t>((Exp6To8G(color0) + Exp6To8G(color1)) / 2);
                rgba[2] = static_cast<uint8_t>((Exp5To8B(color0) + Exp5To8B(color1)) / 2);
            }
            break;
        default:
            if (four) {
                rgba[0] = static_cast<uint8_t>((Exp5To8R(color0) + Exp5To8R(color1) * 2) / 3);
                rgba[1] = static_cast<uint8_t>((Exp6To8G(color0) + Exp6To8G(color1) * 2) / 3);
                rgba[2] = static_cast<uint8_t>((Exp5To8B(color0) + Exp5To8B(color1) * 2) / 3);
            } else {
                rgba[0] = rgba[1] = rgba[2] = 0;
                if (type == 1) rgba[3] = 0;
            }
            break;
    }
}

// fetch_2d_texel_rgba_dxt5's alpha.
uint8_t DecodeDxt5Alpha(const uint8_t* b, int i, int j) {
    const int alpha0 = b[0], alpha1 = b[1];
    const int bitPos = (j * 4 + i) * 3;
    const int low = b[2 + bitPos / 8];
    const int high = b[3 + bitPos / 8];
    const int code = ((low >> (bitPos & 7)) | (high << (8 - (bitPos & 7)))) & 7;
    if (code == 0) return static_cast<uint8_t>(alpha0);
    if (code == 1) return static_cast<uint8_t>(alpha1);
    if (alpha0 > alpha1) return static_cast<uint8_t>((alpha0 * (8 - code) + alpha1 * (code - 1)) / 7);
    if (code < 6) return static_cast<uint8_t>((alpha0 * (6 - code) + alpha1 * (code - 1)) / 5);
    return code == 6 ? 0 : 255;
}
}  // namespace

void RasterTextureCompressedImage(RasterTexture* texture, int level, uint32_t format, int width, int height,
                                  const uint8_t* blocks) {
    if (level < 0 || width <= 0 || height <= 0) return;
    const int blockBytes = (format == 0x83f0 || format == 0x83f1) ? 8 : 16;
    const int type = format == 0x83f0 ? 0 : (format == 0x83f1 ? 1 : 2);
    const int blocksPerRow = (width + 3) / 4;
    std::vector<uint8_t> rgba(static_cast<size_t>(width) * height * 4);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const uint8_t* block = blocks + (static_cast<size_t>(y / 4) * blocksPerRow + x / 4) * blockBytes;
            uint8_t* texel = rgba.data() + (static_cast<size_t>(y) * width + x) * 4;
            const uint8_t* colour = blockBytes == 16 ? block + 8 : block;
            DecodeColorBlock(colour, x & 3, y & 3, type, texel);
            if (format == 0x83f2) {
                const int nibble = (block[((y & 3) * 4 + (x & 3)) / 2] >> (4 * (x & 1))) & 0xf;
                texel[3] = static_cast<uint8_t>(nibble | (nibble << 4));
            } else if (format == 0x83f3) {
                texel[3] = DecodeDxt5Alpha(block, x & 3, y & 3);
            }
        }
    }
    RasterTextureImage(texture, level, width, height, 4, rgba.data(), width * 4);
}

void RasterTextureSetMaxLod(RasterTexture* texture, float lod) {
    texture->hasMaxLod = true;
    texture->maxLod = lod;
    if (texture->device != 0) SetTextureMaxLod(texture->device, lod);
}

int MakeRasterTexturesAhead() {
#ifdef __EMSCRIPTEN__
    if (!IsReady()) return 0;
    const auto start = std::chrono::steady_clock::now();
    std::lock_guard<std::mutex> lock(g_allMutex);
    int made = 0;
    for (RasterTexture* texture : g_all) {
        if (texture->deviceTried) continue;
        if (RasterTextureDevice(texture) != 0) ++made;
    }
    if (made != 0) {
        const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
        DOTD_LOG("gfx: %d texture(s) made ahead in %.0f ms", made, ms);
    }
    return made;
#else
    return 0;
#endif
}

uint32_t RasterTextureDevice(RasterTexture* texture) {
    if (texture == nullptr || !IsReady()) return 0;
    if (!texture->deviceTried) {
        const perf::Scope scope(perf::kWorkTexture);
        texture->deviceTried = true;
        texture->device = texture->referenced ? MakeReferencedTexture(*texture) : MakeImageTexture(*texture);
        if (texture->device != 0 && texture->hasMaxLod) SetTextureMaxLod(texture->device, texture->maxLod);
    }
    return texture->device;
}

}  // namespace dotd::gfx
