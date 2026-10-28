// RwTexture.cpp - the C1.3 texture dictionary shim (see RwTexture.h).
#include "Renderware/rwcore/RwTexture.h"

#include <cctype>
#include <cstring>

#include "Renderware/rwcore/RwStream.h"

namespace {
RwTexDictionary* g_current = nullptr;
std::vector<RwTexDictionary*> g_dictionaries;

uint32_t LoadLE32(const uint8_t* b) {
    return static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) | (static_cast<uint32_t>(b[2]) << 16) |
           (static_cast<uint32_t>(b[3]) << 24);
}

bool NamesEqual(const char* a, const char* b) {
    for (int i = 0; i < 32; ++i) {
        const int ca = std::tolower(static_cast<unsigned char>(a[i]));
        const int cb = std::tolower(static_cast<unsigned char>(b[i]));
        if (ca != cb) return false;
        if (ca == 0) return true;
    }
    return true;
}
}  // namespace

RwTexDictionary* RwTexDictionaryCreate() {
    RwTexDictionary* dict = new RwTexDictionary();
    g_dictionaries.push_back(dict);
    return dict;
}

RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture) {
    dict->textures.push_back(texture);
    return texture;
}

RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict) {
    g_current = dict;
    return dict;
}

RwTexDictionary* RwTexDictionaryGetCurrent() { return g_current; }

RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, const char* name) {
    for (RwTexture* texture : dict->textures) {
        if (NamesEqual(texture->name, name)) return texture;
    }
    return nullptr;
}

RwTexture* RwTextureCreate(RwShim_DdsRaster* raster) {
    RwTexture* texture = new RwTexture();
    texture->raster = raster;
    std::memset(texture->name, 0, sizeof(texture->name));
    std::memset(texture->mask, 0, sizeof(texture->mask));
    // 0x007549d0 RwTextureCreate: wrap / wrap addressing and rwFILTERNEAREST (0x1101), as RW 3.7's (C2.4 exit).
    texture->filterAddressing = 0x1101;
    texture->refCount = 1;
    return texture;
}

const std::vector<RwTexDictionary*>& RwShim_AllTexDictionaries() { return g_dictionaries; }

RwShim_DdsRaster* RwShim_StreamReadDDSRaster(RwStream* stream) {
    uint8_t magic[4];
    if (RwStreamRead(stream, magic, 4) != 4 || std::memcmp(magic, "DDS ", 4) != 0) return nullptr;
    uint8_t header[0x7c];
    if (RwStreamRead(stream, header, 0x7c) != 0x7c) return nullptr;
    // DDS_HEADER: size, flags, height, width, pitch, depth, mipMapCount, reserved1[11], pixel format
    // (size, flags, fourCC, rgbBitCount, masks[4]), caps, caps2, caps3, caps4, reserved2.
    const uint32_t height = LoadLE32(header + 0x08);
    const uint32_t width = LoadLE32(header + 0x0c);
    const uint32_t mips = LoadLE32(header + 0x18);
    const uint32_t pfFlags = LoadLE32(header + 0x48 + 0x04);
    const uint32_t fourCC = LoadLE32(header + 0x48 + 0x08);
    const uint32_t rgbBits = LoadLE32(header + 0x48 + 0x0c);
    const uint32_t caps = LoadLE32(header + 0x68);
    const uint32_t caps2 = LoadLE32(header + 0x6c);
    const uint32_t mipCount = (caps & 0x400000u) != 0 ? (mips != 0 ? mips : 1) : 1;  // DDSCAPS_MIPMAP
    const uint32_t faces = (caps2 & 0x200u) != 0 ? 6 : 1;                           // DDSCAPS2_CUBEMAP
    const bool compressed = (pfFlags & 4u) != 0;                                     // DDPF_FOURCC
    uint32_t dataSize = 0;
    for (uint32_t f = 0; f < faces; ++f) {
        uint32_t w = width, h = height;
        for (uint32_t m = 0; m < mipCount; ++m) {
            if (compressed) {
                const uint32_t blockBytes = fourCC == 0x31545844u ? 8u : 16u;  // DXT1 : DXT3/DXT5
                dataSize += ((w + 3) / 4 > 0 ? (w + 3) / 4 : 1) * ((h + 3) / 4 > 0 ? (h + 3) / 4 : 1) * blockBytes;
            } else {
                dataSize += (w > 0 ? w : 1) * (h > 0 ? h : 1) * rgbBits / 8;
            }
            w = w > 1 ? w >> 1 : 1;
            h = h > 1 ? h >> 1 : 1;
        }
    }
    RwShim_DdsRaster* raster = new RwShim_DdsRaster();
    raster->width = width;
    raster->height = height;
    raster->mipCount = mipCount;
    raster->mipmapFormat = (caps & 0x400000u) != 0;
    raster->faceCount = faces;
    raster->fourCC = compressed ? fourCC : 0;
    raster->bitsPerPixel = compressed ? 0 : rgbBits;
    raster->bytes.resize(4 + 0x7c + dataSize);
    std::memcpy(raster->bytes.data(), magic, 4);
    std::memcpy(raster->bytes.data() + 4, header, 0x7c);
    RwStreamRead(stream, raster->bytes.data() + 4 + 0x7c, dataSize);
    return raster;
}

RwShim_DdsRaster* RwShim_RasterFromImageBlob(const RwShim_Blob* image) {
    RwShim_DdsRaster* raster = new RwShim_DdsRaster();
    raster->mipCount = 1;
    raster->faceCount = 1;
    raster->fourCC = 0;
    raster->width = raster->height = raster->bitsPerPixel = 0;
    if (image != nullptr && image->length >= 12 + 16) {
        uint32_t words[4];
        std::memcpy(words, image->data + 12, sizeof(words));  // struct chunk: width, height, depth, stride
        raster->width = words[0];
        raster->height = words[1];
        raster->bitsPerPixel = words[2];
        const uint8_t* pixels = image->data + 12 + 16;
        const uint8_t* end = image->data + image->length;
        const uint32_t depth = words[2];
        const uint32_t stride = words[3];
        if ((depth == 4 || depth == 8) && pixels + static_cast<size_t>(stride) * words[1] + (4u << depth) <= end) {
            // RwImageStreamRead (image.c): the rows (stride bytes each), then the 1 << depth RwRGBA palette.
            // Expanded to RGBA here, the format the device draws (the PS3 raster keeps the palette).
            const uint8_t* palette = pixels + static_cast<size_t>(stride) * words[1];
            raster->bitsPerPixel = 32;
            raster->bytes.resize(static_cast<size_t>(words[0]) * words[1] * 4);
            for (uint32_t y = 0; y < words[1]; ++y) {
                for (uint32_t x = 0; x < words[0]; ++x) {
                    uint32_t index = pixels[static_cast<size_t>(y) * stride + (depth == 8 ? x : x / 2)];
                    if (depth == 4) index = (x & 1) != 0 ? (index >> 4) : (index & 0xf);
                    std::memcpy(&raster->bytes[(static_cast<size_t>(y) * words[0] + x) * 4], palette + index * 4, 4);
                }
            }
        } else {
            raster->bytes.assign(pixels, end);
        }
    }
    return raster;
}
