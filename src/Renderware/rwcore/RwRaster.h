// RwRaster.h - RenderWare 3.7 rasters and images (core/src/baraster.c, baimage.c, baimras.c) with the PS3 PSGL driver's
// raster code under them (RwPSGL_* in the library range 0x738000-0x76f000), ported from the PS3 library code.
//
// The driver keeps its state in a raster plugin (RwPSGLRasterExt): the GL texture name, the texture parameters, the
// locked mip level, the formats, a camera texture's frame buffer. Its GL calls land on platform/gfx: the texture name
// is a platform/gfx RasterTexture (platform/gfx/raster.h) and a camera texture's frame buffer object a platform/gfx
// render target (RwDevice.cpp). Where the platform does something else than the PSGL call, the comment at the call
// says so.
//
// The driver's format table (library TOC -0x35a4 -> 0xc45994, 12 bytes per rwRASTERFORMAT >> 8: depth, bytes per pixel,
// GL format) and its GL internal formats (0xc45a18; 0xc45a44 with texture compression, [0xcefb4c], which the game
// leaves off: the lock refuses the compressed formats 0x84ed / 0x84ee, so no font could load otherwise).
#pragma once
#include "Renderware/rwcore/RwTypes.h"

namespace dotd::gfx {
struct RasterTexture;
}
struct RwStream;

// rwRASTERTYPE* (RwRasterCreate flags & 7) and rwRASTERFORMAT* (flags & 0xff00).
enum : RwInt32 { rwRASTERTYPENORMAL = 0, rwRASTERTYPEZBUFFER = 1, rwRASTERTYPECAMERA = 2, rwRASTERTYPETEXTURE = 4,
                 rwRASTERTYPECAMERATEXTURE = 5 };
enum : RwInt32 {
    rwRASTERFORMAT1555 = 0x100, rwRASTERFORMAT565 = 0x200, rwRASTERFORMAT4444 = 0x300, rwRASTERFORMATLUM8 = 0x400,
    rwRASTERFORMAT8888 = 0x500, rwRASTERFORMAT888 = 0x600, rwRASTERFORMAT16 = 0x700, rwRASTERFORMAT24 = 0x800,
    rwRASTERFORMAT32 = 0x900, rwRASTERFORMAT555 = 0xa00, rwRASTERFORMATAUTOMIPMAP = 0x1000, rwRASTERFORMATPAL8 = 0x2000,
    rwRASTERFORMATPAL4 = 0x4000, rwRASTERFORMATMIPMAP = 0x8000,
};
// RwRasterLock modes and the raster's privateFlags.
enum : RwInt32 { rwRASTERLOCKWRITE = 1, rwRASTERLOCKREAD = 2, rwRASTERLOCKNOFETCH = 4 };
enum : RwUInt8 { rwRASTERGAMMACORRECTED = 1, rwRASTERPIXELLOCKEDREAD = 2, rwRASTERPIXELLOCKEDWRITE = 4 };

// The PSGL driver's raster plugin (0x70 bytes: RwPSGL_RasterPluginAttach_maybe 0x739680 registers it with
// RwRasterRegisterPlugin(0x70, 0x40c, no constructor); its offset [0xcfbb70] is 0x34 as the only raster plugin _maybe).
// RwPSGL_RasterCreate_maybe 0x73b898 sets every field but +0x14 / +0x18 (never read).
struct RwPSGLRasterExt {
    dotd::gfx::RasterTexture* texture;  // +0x00 glGenTextures' name (RwPSGL_RasterGetGLTexture_maybe 0x738158)
    RwUInt32 wrapS;                     // +0x04 the GL texture parameters set at creation (a camera texture: GL_CLAMP,
    RwUInt32 wrapT;                     // +0x08 GL_CLAMP, GL_LINEAR); 0 for the others
    RwUInt32 magFilter;                 // +0x0c
    RwUInt8 lockedLevel;                // +0x10 the mip level RwRasterLock locked (0xff: none)
    RwUInt8 pad11[3];
    RwUInt32 unk14;                     // +0x14
    RwUInt32 unk18;                     // +0x18
    RwInt32 levelDefined[13];           // +0x1c 1 once a level was given to GL (unlock; a camera texture's level 0)
    RwUInt32 internalFormat;            // +0x50 the GL internal format (a DDS file's: its S3TC format, 0 uncompressed)
    RwInt32 dxtKind;                    // +0x54 a DDS file's DXT 1 / 3 / 5 (such a raster cannot be locked); 0
    RwInt32 autoMipmap;                 // +0x58 GL_GENERATE_MIPMAP while a level is uploaded (MIPMAP | AUTOMIPMAP)
    RwInt32 cubeMap;                    // +0x5c bound as GL_TEXTURE_CUBE_MAP
    RwUInt32 frameBuffer;               // +0x60 a camera texture's frame buffer object (here the device keeps the
                                        //       platform/gfx render target, made on first use: RwDevice_RasterTarget)
    RwUInt32 allocHint;                 // +0x64 0x6030, 0x6031 with cFlags 0x20 (an SCE allocation hint)
    RwInt32 depthBufferIndex;           // +0x68 the shared depth render buffer of a camera texture (4: none)
    RwUInt32 pixelBuffer;               // +0x6c a DDS file's pixel buffer (glGenBuffers; here the platform texture
                                        //       keeps the data, so this stays 0)
};
DOTD_ASSERT_SIZE(RwPSGLRasterExt, 0x70);
DOTD_ASSERT_OFFSET(RwPSGLRasterExt, lockedLevel, 0x10);
DOTD_ASSERT_OFFSET(RwPSGLRasterExt, levelDefined, 0x1c);
DOTD_ASSERT_OFFSET(RwPSGLRasterExt, internalFormat, 0x50);
DOTD_ASSERT_OFFSET(RwPSGLRasterExt, frameBuffer, 0x60);
DOTD_ASSERT_OFFSET(RwPSGLRasterExt, pixelBuffer, 0x6c);

// RwRaster (RW 3.7 0x34) with the driver's plugin.
struct RwRaster {
    RwRaster* parent;          // +0x00 the top raster (itself unless a sub raster)
    RwUInt8* cpPixels;         // +0x04 the pixels while locked
    RwUInt8* palette;          // +0x08
    RwInt32 width;             // +0x0c
    RwInt32 height;            // +0x10
    RwInt32 depth;             // +0x14
    RwInt32 stride;            // +0x18
    RwInt16 nOffsetX;          // +0x1c
    RwInt16 nOffsetY;          // +0x1e
    RwUInt8 cType;             // +0x20
    RwUInt8 cFlags;            // +0x21
    RwUInt8 privateFlags;      // +0x22
    RwUInt8 cFormat;           // +0x23 rwRASTERFORMAT* >> 8 (0x80 MIPMAP, 0x10 AUTOMIPMAP)
    RwUInt8* originalPixels;   // +0x24
    RwInt32 originalWidth;     // +0x28 the size the lock of a mip level saved
    RwInt32 originalHeight;    // +0x2c
    RwInt32 originalStride;    // +0x30
    RwPSGLRasterExt psgl;      // +0x34 the PSGL driver's plugin
};
DOTD_ASSERT_SIZE(RwRaster, 0xa4);
DOTD_ASSERT_OFFSET(RwRaster, width, 0xc);
DOTD_ASSERT_OFFSET(RwRaster, height, 0x10);
DOTD_ASSERT_OFFSET(RwRaster, cType, 0x20);
DOTD_ASSERT_OFFSET(RwRaster, cFormat, 0x23);
DOTD_ASSERT_OFFSET(RwRaster, originalStride, 0x30);
DOTD_ASSERT_OFFSET(RwRaster, psgl, 0x34);

// RwImage (RW 3.7 baimage.h, 0x1c).
struct RwImage {
    RwInt32 flags;      // +0x00 rwIMAGEALLOCATED 1, rwIMAGEGAMMACORRECTED 2
    RwInt32 width;      // +0x04
    RwInt32 height;     // +0x08
    RwInt32 depth;      // +0x0c 4, 8 (palettised: one index per byte) or 32 (R G B A)
    RwInt32 stride;     // +0x10
    RwUInt8* cpPixels;  // +0x14
    RwRGBA* palette;    // +0x18 1 << depth entries after the pixels (4 and 8 only)
};
DOTD_ASSERT_SIZE(RwImage, 0x1c);
DOTD_ASSERT_OFFSET(RwImage, cpPixels, 0x14);

// 0x00750d40 RwRasterCreate (with RwPSGL_RasterCreate_maybe 0x73b898 and RwPSGL_RasterCreateDispatchByType_maybe
// 0x739ca8): null when the driver refuses the size or the format.
RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);
// 0x00750fc0 RwRasterDestroy (with RwPSGL_DestroyNativeRaster_maybe 0x73b3c8).
RwBool RwRasterDestroy(RwRaster* raster);
// 0x00750a70 RwRasterLock (RwPSGL_RasterLock_maybe 0x73a410): the pixels of a mip level; null when it cannot.
RwUInt8* RwRasterLock(RwRaster* raster, RwUInt8 level, RwInt32 lockMode);
// 0x00750560 RwRasterUnlock (RwPSGL_RasterUnlock_maybe 0x73bdc0): written pixels go to the level.
RwRaster* RwRasterUnlock(RwRaster* raster);
// 0x00750050 RwRasterSetFromImage (RwPSGL_RasterSetFromImage_maybe 0x76c230).
RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image);
// 0x007500f8 RwImageFindRasterFormat (RwPSGL_ImageFindRasterFormat_maybe 0x76c650): the raster size and the format
// ((cFormat << 8) | type) an image of this content becomes for a raster of `type`.
RwImage* RwImageFindRasterFormat(RwImage* image, RwInt32 type, RwInt32* width, RwInt32* height, RwInt32* depth,
                                 RwInt32* format);
// 0x0073a860 RwPSGL_GetRasterMipLevelCount_maybe through RwRasterGetNumLevels 0x750930.
RwInt32 RwRasterGetNumLevels(RwRaster* raster);
// 0x0073a8d8 RwStreamReadDDSRaster_maybe: a DDS file ("DDS ", the 0x7c-byte header, the mip chain of each face) as a
// texture raster; null when the file is not a 2D texture or cube map the driver takes, or is short.
RwRaster* RwStreamReadDDSRaster(RwStream* stream);

// 0x0074e768 RwImageCreate / 0x0074edb0 RwImageDestroy / 0x0074d320 RwImageAllocatePixels / 0x0074f268 RwImageStreamRead
RwImage* RwImageCreate(RwInt32 width, RwInt32 height, RwInt32 depth);
RwBool RwImageDestroy(RwImage* image);
RwImage* RwImageAllocatePixels(RwImage* image);
RwImage* RwImageStreamRead(RwStream* stream);

// RwPSGL_RasterGetGLTexture_maybe 0x738158: the raster's GL texture (null for a null raster).
dotd::gfx::RasterTexture* RwPSGLRasterGetTexture(const RwRaster* raster);
