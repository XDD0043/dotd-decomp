// RwTexture.h - the RenderWare texture dictionary as the loader fills it (C1.3 shim).
//
// STUB(C1.4): the rasters. CTextureDictionary_LoadPITextures reads every PS3 texture as a raw DDS file
// (RwStreamReadDDSRaster_maybe 0x73a8d8) into an RwRaster; here the DDS bytes are kept as they are, so
// the textures exist by name with their filter/address flags, and C1.4 turns the bytes into GL textures.
#pragma once
#include <cstdint>
#include <vector>

struct RwStream;

// A raw DDS file as stored after a PS3 texture record ("DDS " + 0x7c-byte header + the mip data).
struct RwShim_DdsRaster {
    uint32_t width;
    uint32_t height;
    uint32_t mipCount;
    // rwRASTERFORMATMIPMAP (the PS3 raster's cFormat byte +0x23, bit 7): RwStreamReadDDSRaster_maybe 0x73a8d8 sets it
    // when the DDS has DDSCAPS_MIPMAP (then mipCount is the file's count). C2.4 exit.
    bool mipmapFormat = false;
    uint32_t faceCount;     // 6 for a cube map
    uint32_t fourCC;        // 0 for an uncompressed format
    uint32_t bitsPerPixel;  // uncompressed formats
    std::vector<uint8_t> bytes;  // the whole file (an RW Image raster: the image's pixels, RGBA bytes)
    // C1.4 (no PS3 counterpart: the PS3 raster is the GPU texture): the device texture made from the bytes
    // on first use (RwDevice_GetRasterTexture), and whether that was tried.
    uint32_t deviceTexture = 0;
    bool deviceTried = false;
};

// RwTexture (RW 3.7: raster, dict, name[32] at +0x10, mask, filterAddressing at +0x50, refCount).
struct RwTexture {
    RwShim_DdsRaster* raster;
    char name[32];
    char mask[32];
    uint32_t filterAddressing;  // bits 0-7 filter mode, 8-11 U addressing, 12-15 V addressing (RW)
    int32_t refCount;
};

struct RwTexDictionary {
    std::vector<RwTexture*> textures;  // in the order they were added
};

RwTexDictionary* RwTexDictionaryCreate();                         // 0x0098xxxx TocBridge (library)
RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture);
RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict);
RwTexDictionary* RwTexDictionaryGetCurrent();
// Case-insensitive, as RW compares texture names (rwstrcmp on the PS3 build compares case-blind).
RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, const char* name);
RwTexture* RwTextureCreate(RwShim_DdsRaster* raster);
// Every dictionary created so far (the shim's search space for texture references; see FindTextureByName).
const std::vector<RwTexDictionary*>& RwShim_AllTexDictionaries();

// 0x0073a8d8 RwStreamReadDDSRaster_maybe, as far as the stream goes: reads "DDS " and the 0x7c-byte header,
// then exactly the mip chain the header describes (all faces of a cube map), and returns the raster, or
// null when the magic is wrong (the original then also returns 0 after the 4 bytes). DXT1/3/5 and the
// uncompressed formats, like the original's size walk (work/scratch-impl1-loading/dds_walk.py reproduces
// LVL000's 147 textures to the object's end offset).
RwShim_DdsRaster* RwShim_StreamReadDDSRaster(RwStream* stream);

struct RwShim_Blob;
// An RwImage chunk (0x18, read whole) as a raster: the struct chunk's width, height and depth, the pixels
// kept as they are (RGBA bytes for depth 32). Stands in for Raster_CreateFromImage_maybe (the texture
// bank's raster from an RwImage). An empty raster (size 0) when the chunk is missing or short.
RwShim_DdsRaster* RwShim_RasterFromImageBlob(const RwShim_Blob* image);
