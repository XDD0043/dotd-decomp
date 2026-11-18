// RwRaster.cpp - RW 3.7 rasters and images with the PS3 PSGL driver's raster code. See RwRaster.h.
#include "Renderware/rwcore/RwRaster.h"
#include "Renderware/rwcore/RwPSGLDxtn.h"

#include <cstring>
#include <utility>
#include <vector>

#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "crt/ppc_ops.h"
#include "platform/gfx/raster.h"

namespace gfx = dotd::gfx;

namespace {

// 0x00c45994: per rwRASTERFORMAT >> 8 (0..10) the depth, the bytes per pixel and the GL format (GL_RGB 0x1907,
// GL_RGBA 0x1908).
struct PSGLFormat {
    RwInt32 depth;
    RwInt32 bytesPerPixel;
    RwUInt32 glFormat;
};
constexpr PSGLFormat kFormats[11] = {
    {0, 0, 0},         {0x10, 4, 0x1908}, {0x10, 3, 0x1907}, {0x10, 4, 0x1908}, {0, 0, 0},         {0x20, 4, 0x1908},
    {0x18, 3, 0x1907}, {0x10, 3, 0x1907}, {0x18, 3, 0x1907}, {0x20, 4, 0x1908}, {0x10, 3, 0x1907},
};
// 0x00c45a18: the GL internal formats (GL_RGBA8 0x8058, GL_RGB8 0x8051, ...); 0x00c45a44 the compressed ones
// (GL_COMPRESSED_RGB 0x84ed / RGBA 0x84ee) used with the texture compression flag [0xcefb4c], which stays 0.
constexpr RwUInt32 kInternalFormats[11] = {0, 0x8057, 0x8050, 0x8056, 0, 0x8058, 0x8051, 0x8050, 0x8051, 0x8058, 0x8050};
constexpr RwUInt32 kGlRgb = 0x1907;
constexpr RwUInt32 kGlRgba = 0x1908;

// _rwPSGLGetCurrentVideoModeDepth_maybe: the game's video mode is 1280x720 in 32 bits.
constexpr RwInt32 kVideoModeDepth = 0x20;
// KStub_Return24_738ff0: the depth buffer's depth.
constexpr RwInt32 kZBufferDepth = 0x18;
// The driver's maximum texture size (0x740ac0 and [0xcefb90]: GL_MAX_TEXTURE_SIZE of the RSX, 4096 _maybe).
constexpr RwInt32 kMaxTextureSize = 4096;
// The driver caps' GL_GENERATE_MIPMAP support (library TOC -0x35bc -> +0x90; _maybe 1 on the RSX). Read only for a
// raster created with both rwRASTERFORMATMIPMAP and AUTOMIPMAP, which nothing in the game asks for.
constexpr RwInt32 kHasGenerateMipmap = 1;

RwRaster* TopRaster(RwRaster* raster) {
    RwRaster* top = raster;
    while (top->parent != top) top = top->parent;
    return top;
}

// The raster's depth and stride from the format table, the driver's internal format.
void SetFormatFields(RwRaster* raster, RwInt32 index, RwUInt32 internalFormat) {
    raster->depth = kFormats[index].depth;
    raster->stride = raster->width * kFormats[index].bytesPerPixel;
    raster->psgl.internalFormat = internalFormat;
}

bool IsListedFormat(RwUInt32 format) {
    switch (format) {
        case 0x100: case 0x200: case 0x300: case 0x500: case 0x600: case 0x700: case 0x800: case 0x900: case 0xa00:
            return true;
        default:
            return false;
    }
}

// 0x00739ca8 RwPSGL_RasterCreateDispatchByType_maybe: the type and flags, then per type the format (the video mode's
// when the flags name none), its depth, stride and GL internal format. 0 for a palettised format or one the type does
// not take.
bool RasterCreateDispatchByType(RwRaster* raster, RwUInt32 flags) {
    raster->cFlags = static_cast<RwUInt8>(flags & 0xf8);
    raster->cType = static_cast<RwUInt8>(flags & 7);
    if ((flags & 0x6000) != 0) return false;  // rwRASTERFORMATPAL8 / PAL4
    const RwUInt32 format = flags & 0xf00;
    RwUInt8 cFormat = static_cast<RwUInt8>((flags & 0xff00) >> 8);
    RwInt32 index = 0;
    switch (flags & 7) {
        case rwRASTERTYPENORMAL:
        case rwRASTERTYPECAMERATEXTURE:
        case rwRASTERTYPECAMERA:
            if (format == 0) {
                const RwInt32 depth = kVideoModeDepth;
                if (depth == 0x18) {
                    index = 6;
                } else if (depth == 0x20) {
                    index = 5;
                } else if (depth == 0x10) {
                    index = (flags & 7) == rwRASTERTYPECAMERATEXTURE || (flags & 7) == rwRASTERTYPECAMERA ? 2 : 3;
                } else {
                    return false;
                }
                // A normal or camera texture raster keeps its other format bits (MIPMAP, AUTOMIPMAP); a camera's
                // cFormat is the index alone.
                cFormat = (flags & 7) == rwRASTERTYPECAMERA ? static_cast<RwUInt8>(index)
                                                             : static_cast<RwUInt8>(index | cFormat);
                SetFormatFields(raster, index, kInternalFormats[index]);
                break;
            }
            if ((flags & 7) == rwRASTERTYPECAMERA && format != 0x500 && format != 0x600 && format != 0x200) return false;
            if (!IsListedFormat(format)) return false;
            index = static_cast<RwInt32>(format >> 8);
            SetFormatFields(raster, index, kInternalFormats[index]);
            break;
        case rwRASTERTYPEZBUFFER: {
            const RwInt32 zDepth = kZBufferDepth;
            const RwUInt32 zFormat = flags & 0xff00;  // compared with the MIPMAP / AUTOMIPMAP bits
            if (format != 0) {
                if (zFormat == 0x700 && zDepth == 0x10) {
                    index = 7;
                } else if (zFormat == 0x800 && zDepth == 0x18) {
                    index = 8;
                } else if (zFormat == 0x900 && zDepth == 0x20) {
                    index = 9;
                } else {
                    return false;
                }
            } else if (zDepth == 0x18) {
                index = 8;
            } else if (zDepth == 0x20) {
                index = 9;
            } else if (zDepth == 0x10) {
                index = 7;
            } else {
                return false;
            }
            cFormat = static_cast<RwUInt8>(index);
            SetFormatFields(raster, index, kInternalFormats[index]);
            break;
        }
        case rwRASTERTYPETEXTURE: {
            // [0xcefb4c] (texture compression) is 0: the uncompressed internal formats.
            if (format == 0) {
                const RwInt32 depth = kVideoModeDepth;
                if (depth == 0x18) {
                    index = 6;
                } else if (depth == 0x20) {
                    index = 5;
                } else if (depth == 0x10) {
                    index = 3;
                } else {
                    return false;
                }
                cFormat = static_cast<RwUInt8>(index | cFormat);
            } else {
                if (!IsListedFormat(format)) return false;
                index = static_cast<RwInt32>(format >> 8);
            }
            SetFormatFields(raster, index, kInternalFormats[index]);
            break;
        }
        default:
            return false;
    }
    raster->cFormat = cFormat;
    return true;
}

// 0x0073b898 RwPSGL_RasterCreate_maybe (the device's rwSTANDARDRASTERCREATE).
bool PSGLRasterCreate(RwRaster* raster, RwUInt32 flags) {
    RwPSGLRasterExt& ext = raster->psgl;
    ext.lockedLevel = 0xff;
    ext.cubeMap = 0;
    ext.texture = nullptr;
    ext.pixelBuffer = 0;
    ext.wrapS = 0;
    ext.wrapT = 0;
    ext.magFilter = 0;
    for (RwInt32& defined : ext.levelDefined) defined = 0;
    ext.internalFormat = 0;
    ext.dxtKind = 0;
    ext.autoMipmap = 0;
    if (raster->width > kMaxTextureSize || raster->height > kMaxTextureSize) return false;
    if (!RasterCreateDispatchByType(raster, flags)) return false;
    ext.allocHint = (raster->cFlags & 0x20) != 0 ? 0x6031u : 0x6030u;
    ext.frameBuffer = 0;
    ext.depthBufferIndex = 4;
    if (raster->width == 0 || raster->height == 0) {
        raster->cFlags = 0x80;  // rwRASTERDONTALLOCATE
        return true;
    }
    switch (raster->cType) {
        case rwRASTERTYPENORMAL:
            if ((flags & 0x9000) == 0x9000) return false;
            ext.texture = gfx::GenRasterTexture();
            return true;
        case rwRASTERTYPEZBUFFER:
        case rwRASTERTYPECAMERA:
            return true;  // the display's buffers
        case rwRASTERTYPETEXTURE:
            ext.texture = gfx::GenRasterTexture();
            if ((flags & 0x9000) == 0x9000 && kHasGenerateMipmap != 0) ext.autoMipmap = 1;
            return true;
        case rwRASTERTYPECAMERATEXTURE:
            // The texture with GL_CLAMP / GL_LINEAR, its storage of the raster's size (glTexImage2D with no pixels),
            // a frame buffer object with the texture as colour 0 and the shared depth render buffer. Here the device
            // makes the frame buffer (a platform/gfx render target with its colour texture) when the raster is first
            // drawn into or sampled (RwDevice_RasterTarget), and the texture name stays unused.
            ext.texture = gfx::GenRasterTexture();
            ext.wrapT = 0x2900;
            ext.magFilter = 0x2601;
            ext.wrapS = 0x2900;
            ext.levelDefined[0] = 1;
            return true;
        default:
            return false;  // rwRASTERTYPE 3: error 0x8000000d
    }
}

// 0x0073b3c8 RwPSGL_DestroyNativeRaster_maybe. RwPSGL_UnbindTextureIfCurrent_maybe first forgets the raster as the
// driver's bound texture (the device binds per draw here). A top raster's texture, pixels, palette, pixel buffer,
// formats and frame buffer go.
void PSGLRasterDestroy(RwRaster* raster) {
    if (raster->parent != raster) return;
    RwPSGLRasterExt& ext = raster->psgl;
    if (ext.texture != nullptr) {
        gfx::DeleteRasterTexture(ext.texture);
        ext.texture = nullptr;
    }
    if (raster->cpPixels != nullptr) {
        RwFree(raster->cpPixels);
        raster->cpPixels = nullptr;
    }
    if (raster->palette != nullptr) {
        RwFree(raster->palette);
        raster->palette = nullptr;
    }
    ext.pixelBuffer = 0;
    ext.internalFormat = 0;
    ext.dxtKind = 0;
    ext.autoMipmap = 0;
    ext.cubeMap = 0;
    RwDevice_ReleaseRaster(raster);  // glDeleteFramebuffersOES (the device's render target of a camera texture)
    ext.frameBuffer = 0;
    // The shared depth render buffer's reference (depthBufferIndex != 4): a camera texture's, made with its frame
    // buffer; the platform target shares the internal depth buffer, so there is nothing to release.
}

}  // namespace

// 0x00750d40 RwRasterCreate
RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags) {
    RwRaster* raster = static_cast<RwRaster*>(RwMalloc(sizeof(RwRaster), 0x30407));  // the raster free list
    if (raster == nullptr) return nullptr;
    raster->cFlags = 0;
    raster->width = width;
    raster->height = height;
    raster->nOffsetY = 0;
    raster->depth = depth;
    raster->parent = raster;
    raster->palette = nullptr;
    raster->privateFlags = 0;
    raster->nOffsetX = 0;
    raster->cpPixels = nullptr;
    if (!PSGLRasterCreate(raster, static_cast<RwUInt32>(flags))) {
        RwFree(raster);
        return nullptr;
    }
    return raster;  // _rwPluginRegistryInitObject: the driver's plugin has no constructor
}

// 0x00750fc0 RwRasterDestroy
RwBool RwRasterDestroy(RwRaster* raster) {
    PSGLRasterDestroy(raster);
    RwFree(raster);
    return 1;
}

// 0x00750a70 RwRasterLock with 0x0073a410 RwPSGL_RasterLock_maybe. The mip level's size (at least 1 x 1) replaces the
// top raster's while locked (the original size kept at +0x28..+0x30), and fresh memory holds its pixels.
RwUInt8* RwRasterLock(RwRaster* raster, RwUInt8 level, RwInt32 lockMode) {
    const RwUInt32 mode = static_cast<RwUInt32>(level) * 0x100 + static_cast<RwUInt32>(lockMode);
    RwRaster* top = TopRaster(raster);
    RwPSGLRasterExt& ext = top->psgl;
    if (ext.dxtKind != 0) return nullptr;
    if (ext.internalFormat == 0x84ed || ext.internalFormat == 0x84ee) return nullptr;
    const RwUInt32 shift = (mode >> 8) & 0x3f;
    if ((mode & 0xff00) != 0 && ext.autoMipmap != 0) return nullptr;
    switch (raster->cType & 7) {
        case rwRASTERTYPENORMAL:
        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE: {
            const RwInt32 bytesPerPixel = kFormats[top->cFormat & 0xf].bytesPerPixel;
            top->originalWidth = top->width;
            top->originalHeight = top->height;
            top->originalStride = top->stride;
            const RwInt32 h = top->height >> shift;
            const RwInt32 w = top->width >> shift;
            if (w == 0 && h == 0) return nullptr;  // error 0x8000000f
            top->width = w != 0 ? w : 1;
            top->height = h != 0 ? h : 1;
            top->stride = bytesPerPixel * top->width;
            top->cpPixels = static_cast<RwUInt8*>(RwMalloc(static_cast<RwUInt32>(top->stride * top->height), 0x30411));
            if (top->cpPixels == nullptr) {
                top->height = top->originalHeight;
                top->stride = top->originalStride;
                top->width = top->originalWidth;
                return nullptr;  // error 0x80000013
            }
            break;
        }
        case rwRASTERTYPECAMERA: {
            // The display read back (glReadPixels of each row, bottom row first, in the format's GL format): level 0
            // of a raster not locked already.
            if (raster->cpPixels != nullptr || (mode & 0xff00) != 0) return nullptr;
            top->cpPixels = static_cast<RwUInt8*>(RwMalloc(static_cast<RwUInt32>(top->stride * top->height), 0x30411));
            if (top->cpPixels == nullptr) return nullptr;
            const RwInt32 bytesPerPixel = kFormats[top->cFormat & 0xf].bytesPerPixel;
            std::vector<uint8_t> rgba(static_cast<size_t>(gfx::InternalWidth()) * gfx::InternalHeight() * 4);
            const bool read = !rgba.empty() && gfx::ReadTarget(rgba.data());
            for (RwInt32 row = 0; row < top->height; ++row) {
                RwUInt8* dst = top->cpPixels + static_cast<size_t>(row) * top->stride;
                for (RwInt32 x = 0; x < top->width; ++x) {
                    const bool inside = read && x < gfx::InternalWidth() && row < gfx::InternalHeight();
                    for (RwInt32 c = 0; c < bytesPerPixel; ++c) {
                        dst[x * bytesPerPixel + c] =
                            inside ? rgba[(static_cast<size_t>(row) * gfx::InternalWidth() + x) * 4 + c] : 0;
                    }
                }
            }
            break;
        }
        default:
            return nullptr;  // the depth buffer: error 0x8000000e; others 0x8000000d
    }
    if ((mode & rwRASTERLOCKREAD) != 0) raster->privateFlags |= rwRASTERPIXELLOCKEDREAD;
    if ((mode & rwRASTERLOCKWRITE) != 0) raster->privateFlags |= rwRASTERPIXELLOCKEDWRITE;
    ext.lockedLevel = static_cast<RwUInt8>(mode >> 8);
    raster->cpPixels = top->cpPixels + (raster->depth >> 3) * raster->nOffsetX + raster->nOffsetY * raster->stride;
    return raster->cpPixels;
}

// 0x00750560 RwRasterUnlock with 0x0073bdc0 RwPSGL_RasterUnlock_maybe. Written pixels of a texture go to the locked
// level compressed (tx_compress_dxtn 0x743020, RwPSGLDxtn.cpp: DXT5 from 4 bytes per pixel for a GL_RGBA format, DXT1
// from 3 for any other, rows `width` pixels apart, into a malloc'd block) through glCompressedTexImage2D (the platform
// texture keeps the texels the blocks decode to), with GL_GENERATE_MIPMAP around it for an auto-mipmapped raster, and
// the bytes counted in the driver's texture statistics (nothing reads them).
RwRaster* RwRasterUnlock(RwRaster* raster) {
    RwRaster* top = TopRaster(raster);
    RwPSGLRasterExt& ext = top->psgl;
    switch (raster->cType & 7) {
        case rwRASTERTYPENORMAL:
        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            if ((raster->privateFlags & rwRASTERPIXELLOCKEDWRITE) != 0) {
                const PSGLFormat& format = kFormats[top->cFormat & 0xf];
                const bool rgba = format.glFormat == kGlRgba;  // cmpwi 0x1908
                const uint32_t blocks = static_cast<uint32_t>((top->width + 3) / 4) * static_cast<uint32_t>((top->height + 3) / 4);
                std::vector<uint8_t> compressed(static_cast<size_t>(blocks) * (rgba ? 16 : 8));
                tx_compress_dxtn(rgba ? 4 : 3, top->width, top->height, top->cpPixels,
                                 rgba ? kGlCompressedRgbaS3tcDxt5 : kGlCompressedRgbS3tcDxt1, compressed.data());
                gfx::RasterTextureCompressedImage(ext.texture, ext.lockedLevel,
                                                  rgba ? kGlCompressedRgbaS3tcDxt5 : kGlCompressedRgbS3tcDxt1,
                                                  top->width, top->height, compressed.data());
                ext.levelDefined[ext.lockedLevel] = 1;
            }
            top->width = top->originalWidth;
            top->height = top->originalHeight;
            top->stride = top->originalStride;
            break;
        case rwRASTERTYPECAMERA:
            // Written: the viewport and an orthographic projection of the raster's size are set (no pixels go back
            // to the display; the device sets its own per draw here).
            if ((raster->privateFlags & rwRASTERPIXELLOCKEDWRITE) != 0 &&
                (top->cpPixels == nullptr || raster->cpPixels == nullptr)) {
                return raster;
            }
            break;
        default:
            return raster;  // errors 0x8000000e / 0x8000000d
    }
    ext.lockedLevel = 0xff;
    RwFree(top->cpPixels);
    const RwUInt8 flags = raster->privateFlags;
    top->cpPixels = nullptr;
    raster->cpPixels = nullptr;
    if ((flags & rwRASTERPIXELLOCKEDWRITE) == 0) {
        raster->privateFlags = static_cast<RwUInt8>((flags & 0xf8) | (flags & 1));
        return raster;
    }
    raster->privateFlags = static_cast<RwUInt8>(flags & 0xf9);
    // An AUTOMIPMAP raster the driver does not mipmap itself gets its levels from the texture module's mipmap callback.
    if ((raster->cFormat & 0x10) != 0 && ext.autoMipmap == 0) RwTextureRasterGenerateMipmaps(raster, nullptr);
    return raster;
}

// 0x00750050 RwRasterSetFromImage with 0x0076c230 RwPSGL_RasterSetFromImage_maybe: the image's pixels (palette indices
// expanded) into the raster's level, locked here (write, no fetch) unless the caller has locked it for writing.
RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image) {
    const bool callerLocked = (raster->privateFlags & rwRASTERPIXELLOCKEDWRITE) != 0;
    if (!callerLocked && RwRasterLock(raster, 0, rwRASTERLOCKWRITE | rwRASTERLOCKNOFETCH) == nullptr) return nullptr;
    RwRaster* top = TopRaster(raster);
    const RwUInt32 glFormat = kFormats[top->cFormat & 0xf].glFormat;
    if (glFormat != kGlRgb && glFormat != kGlRgba) return nullptr;  // error 0x8000000d (the raster stays locked)
    const RwInt32 out = glFormat == kGlRgba ? 4 : 3;
    const bool palettised = image->depth == 4 || image->depth == 8;
    const RwUInt8* srcRow = image->cpPixels;
    RwUInt8* dstRow = raster->cpPixels;
    for (RwInt32 y = 0; y < image->height; ++y) {
        for (RwInt32 x = 0; x < image->width; ++x) {
            const RwUInt8* src = palettised ? reinterpret_cast<const RwUInt8*>(&image->palette[srcRow[x]]) : srcRow + x * 4;
            for (RwInt32 c = 0; c < out; ++c) dstRow[x * out + c] = src[c];
        }
        srcRow += image->stride;
        dstRow += raster->stride;
    }
    if (!callerLocked) RwRasterUnlock(raster);
    if ((image->flags & 2) != 0) raster->privateFlags |= rwRASTERGAMMACORRECTED;
    return raster;
}

// 0x007500f8 RwImageFindRasterFormat with 0x0076c650 RwPSGL_ImageFindRasterFormat_maybe. The format from the alpha the
// image uses: none (every alpha 0xff) -> rwRASTERFORMAT888, any other -> 8888 (in a 32-bit video mode; 565 / 1555 /
// 4444 / 555 in a 16-bit one). A texture or camera texture is clamped to the maximum texture size and rounded down to
// a power of two, and keeps the MIPMAP / AUTOMIPMAP bits; a normal raster with them is refused.
RwImage* RwImageFindRasterFormat(RwImage* image, RwInt32 type, RwInt32* width, RwInt32* height, RwInt32* depth,
                                 RwInt32* format) {
    RwRaster r;
    std::memset(&r, 0, sizeof(r));
    r.width = image->width;
    r.height = image->height;
    r.depth = 0;
    const RwUInt32 flags = static_cast<RwUInt32>(type);
    const RwInt32 videoDepth = kVideoModeDepth;
    RwUInt32 rasterFormat = 0;
    bool usesAlpha = false;  // LAB_0076c71c: an alpha other than 0xff (above 0xf for a 32-bit image)
    bool smallAlpha = false;
    if (image->depth == 4 || image->depth == 8) {
        const RwRGBA* palette = image->palette;
        bool paletteOpaque = true;
        const RwInt32 entries = image->depth == 4 ? 16 : 256;
        for (RwInt32 i = 0; i < entries; ++i) {
            if (palette[i].alpha != 0xff) {
                paletteOpaque = false;
                break;
            }
        }
        if (!paletteOpaque) {
            const RwUInt8* row = image->cpPixels;
            for (RwInt32 y = 0; y < image->height && !usesAlpha; ++y) {
                for (RwInt32 x = 0; x < image->width; ++x) {
                    if (palette[row[x]].alpha != 0xff) {
                        usesAlpha = true;
                        break;
                    }
                }
                row += image->stride;
            }
        }
        if (!usesAlpha) rasterFormat = videoDepth > 0x10 ? 0x600 : 0xa00;
    } else {
        const RwUInt8* row = image->cpPixels;
        RwUInt32 small = 0;
        for (RwInt32 y = 0; y < image->height && !usesAlpha; ++y) {
            for (RwInt32 x = 0; x < image->width; ++x) {
                const RwUInt8 alpha = row[x * 4 + 3];
                if (alpha == 0xff) continue;
                if (alpha > 0xf) {
                    usesAlpha = true;
                    break;
                }
                small = 1;
            }
            if (small > 7) usesAlpha = true;  // never: small is 0 or 1
            row += image->stride;
        }
        if (!usesAlpha) {
            if (small != 0) {
                smallAlpha = true;
            } else {
                rasterFormat = videoDepth > 0x10 ? 0x600 : 0x200;
            }
        }
    }
    if (usesAlpha) rasterFormat = videoDepth < 0x11 ? 0x300 : 0x500;
    if (smallAlpha) rasterFormat = videoDepth > 0x10 ? 0x500 : 0x100;
    if (r.width != 0 && r.height != 0) {
        const RwInt32 kind = static_cast<RwInt32>(flags & 7);
        if (kind > 5 || kind == 3) return nullptr;  // error 0x8000000d
        if (kind == rwRASTERTYPENORMAL || kind == rwRASTERTYPETEXTURE || kind == rwRASTERTYPECAMERATEXTURE) {
            // 0x76ca1c / 0x76cabc: the maximum texture size, then down to a power of two.
            const RwInt32 maxSize = kMaxTextureSize;
            if (r.width > maxSize) r.width = maxSize;
            if (r.height > maxSize) r.height = maxSize;
            RwInt32 bits = -1;
            for (RwInt32 v = r.width; v != 0; v >>= 1) ++bits;
            r.width = static_cast<RwInt32>(ppc::slw(1u, static_cast<uint32_t>(bits)));
            bits = -1;
            for (RwInt32 v = r.height; v != 0; v >>= 1) ++bits;
            r.height = static_cast<RwInt32>(ppc::slw(1u, static_cast<uint32_t>(bits)));
            if (kind == rwRASTERTYPENORMAL) {
                if ((flags & 0x9000) != 0) return nullptr;
            } else {
                rasterFormat |= flags & 0x9000;
            }
        }
    }
    // 0x76c7b8: the type, flags, format and the format's depth.
    r.cType = static_cast<RwUInt8>(flags & 7);
    r.cFlags = static_cast<RwUInt8>(flags & 0xf8);
    r.cFormat = static_cast<RwUInt8>(rasterFormat >> 8);
    r.depth = kFormats[(rasterFormat >> 8) & 0xf].depth;
    *format = static_cast<RwInt32>((static_cast<RwUInt32>(r.cFormat) << 8) | r.cType);
    *width = r.width;
    *height = r.height;
    *depth = r.depth;
    return image;
}

// 0x00750930 RwRasterGetNumLevels with 0x0073a860 RwPSGL_GetRasterMipLevelCount_maybe: 1 without MIPMAP; a mipmapped
// texture the driver does not auto-mipmap has one level per halving of its larger side.
RwInt32 RwRasterGetNumLevels(RwRaster* raster) {
    if ((raster->cFormat & 0x80) == 0) return 1;
    if ((raster->cType & 7) == rwRASTERTYPETEXTURE && raster->psgl.autoMipmap == 0) {
        RwUInt32 count = 0;
        if (raster->width != 0 || raster->height != 0) {
            do {
                ++count;
            } while ((static_cast<RwInt32>(static_cast<RwUInt32>(raster->height) | static_cast<RwUInt32>(raster->width)) >>
                      (count & 0x3f)) != 0);
        }
        return static_cast<RwInt32>(count);
    }
    return 1;
}

// 0x0073a8d8 RwStreamReadDDSRaster_maybe
RwRaster* RwStreamReadDDSRaster(RwStream* stream) {
    uint8_t magic[4];
    if (RwStreamRead(stream, magic, 4) != 4 || std::memcmp(magic, "DDS ", 4) != 0) return nullptr;
    uint8_t header[0x7c];
    if (RwStreamRead(stream, header, 0x7c) != 0x7c) return nullptr;
    // DDS_HEADER (RwMemNative32 of each word read): height +0x08, width +0x0c, mip count +0x18, pixel format flags
    // +0x4c and fourCC +0x50, caps +0x68, caps2 +0x6c.
    auto word = [&header](int offset) {
        uint32_t v;
        std::memcpy(&v, header + offset, 4);
        return v;
    };
    const uint32_t height = word(0x08);
    const uint32_t width = word(0x0c);
    const uint32_t mipCount = word(0x18);
    const uint32_t pfFlags = word(0x4c);
    const uint32_t fourCC = word(0x50);
    const uint32_t caps = word(0x68);
    uint32_t caps2 = word(0x6c);
    if ((caps & 0x1000) == 0 || (caps2 & 0x200000) != 0) return nullptr;  // DDSCAPS_TEXTURE, not a volume
    RwInt32 cube = 0;
    if ((caps2 & 0x200) != 0) {
        // A cube map needs the driver's cube support (caps +0x48, +0x70, +0x88, the size limit +0x4c) and all six
        // faces. None of the game's DDS files is a cube map (every one is a 2D DXT1 or DXT5 texture).
        if (width > static_cast<uint32_t>(kMaxTextureSize) || height > static_cast<uint32_t>(kMaxTextureSize)) {
            return nullptr;
        }
        if ((caps2 & 0xfffffdffu) != 0xfc00) return nullptr;
        cube = 1;
        caps2 = 0xfc00;
    }
    RwInt32 mipFlag = 0;
    RwInt32 levels = 1;
    if ((caps & 0x400000) != 0) {  // DDSCAPS_MIPMAP
        mipFlag = rwRASTERFORMATMIPMAP;
        levels = static_cast<RwInt32>(mipCount);
    }
    RwUInt32 glFormat = 0;
    RwInt32 kind = 0;
    if ((pfFlags & 4) != 0) {  // DDPF_FOURCC
        if (fourCC == 0x33545844u) {  // DXT3
            kind = 3;
            glFormat = 0x83f2;
        } else if (fourCC == 0x35545844u) {  // DXT5
            kind = 5;
            glFormat = 0x83f3;
        } else if (fourCC == 0x31545844u) {  // DXT1
            kind = 1;
            glFormat = 0x83f1;
        } else {
            return nullptr;
        }
    }
    RwRaster* raster = RwRasterCreate(static_cast<RwInt32>(width), static_cast<RwInt32>(height), 0, mipFlag | 4);
    if (raster == nullptr) return nullptr;
    RwPSGLRasterExt& ext = raster->psgl;
    ext.internalFormat = glFormat;
    ext.dxtKind = kind;
    ext.cubeMap = cube;
    for (;;) {
        if (cube != 0) {
            // A cube map: the next face (DDSCAPS2_CUBEMAP_POSITIVEX 0x400 .. NEGATIVEZ 0x8000) leaves caps2.
            for (uint32_t bit = 0x400; bit <= 0x8000; bit <<= 1) {
                if ((caps2 & bit) != 0) {
                    caps2 &= ~bit;
                    break;
                }
            }
        }
        // The face's size: per level the 4x4 blocks of the level's size (8 bytes for DXT1, 16 otherwise: also for an
        // uncompressed file, which the game has none of), the halvings arithmetic (a side of 0 counts one block).
        // Running out of size before the levels: the raster is destroyed.
        uint32_t size = 0;
        if (levels != 0) {
            if (height == 0 && width == 0) break;
            const uint32_t blockBytes = kind == 1 ? 8u : 16u;
            uint32_t w = width, h = height;
            bool tooMany = false;
            for (RwInt32 m = 1;; ++m) {
                const uint32_t blocksW = w != 0 ? (w + 3) >> 2 : 1;
                const uint32_t blocksH = h != 0 ? (h + 3) >> 2 : 1;
                size += blocksH * blockBytes * blocksW;
                w = static_cast<uint32_t>(static_cast<int32_t>(width) >> (m & 0x3f));
                h = static_cast<uint32_t>(static_cast<int32_t>(height) >> (m & 0x3f));
                if (m == levels) break;
                if (w == 0 && h == 0) {
                    tooMany = true;
                    break;
                }
            }
            if (tooMany) break;
        }
        // The pixel buffer (glGenBuffers, glBufferData(size), glMapBuffer), the texture's GL_TEXTURE_MAX_LOD: 1 plus
        // the halvings of the smaller side down to 16 texels (1.0, library TOC -0x3594, at 16 or less), so the mip
        // levels below about 8 texels are not sampled; glTextureReferenceSCE(levels, width, height, format) on the
        // buffer; then the face's data read into it.
        std::vector<uint8_t> data(size);
        RwInt32 side = raster->height < raster->width ? raster->height : raster->width;
        float maxLod = 1.0f;
        if (side >= 0x11) {
            RwInt32 count = 1;
            do {
                side >>= 1;
                ++count;
            } while (side > 0x10);
            maxLod = static_cast<float>(static_cast<double>(count));
        }
        gfx::RasterTextureSetMaxLod(ext.texture, maxLod);
        if (RwStreamRead(stream, data.data(), size) != size) break;
        gfx::RasterTextureReferenceDds(ext.texture, glFormat, levels, raster->width, raster->height, std::move(data));
        if (cube == 0 || caps2 == 0) return raster;
    }
    RwRasterDestroy(raster);
    return nullptr;
}

// 0x0074e768 RwImageCreate
RwImage* RwImageCreate(RwInt32 width, RwInt32 height, RwInt32 depth) {
    RwImage* image = static_cast<RwImage*>(RwMalloc(sizeof(RwImage), 0x30018));  // the image free list
    if (image == nullptr) return nullptr;
    image->width = width;
    image->height = height;
    image->depth = depth;
    image->flags = 0;
    image->cpPixels = nullptr;
    image->palette = nullptr;
    return image;  // _rwPluginRegistryInitObject: no image plugin
}

// 0x0074edb0 RwImageDestroy (RwImageFreePixels 0x74cca0 inlined)
RwBool RwImageDestroy(RwImage* image) {
    if ((image->flags & 1) != 0) {
        RwFree(image->cpPixels);
        image->palette = nullptr;
        image->flags &= ~1;
        image->cpPixels = nullptr;
    }
    RwFree(image);
    return 1;
}

// 0x0074d320 RwImageAllocatePixels: rows of ((depth + 7) >> 3) * width bytes rounded to 4, then a 1 << depth palette
// for 4 and 8 bits.
RwImage* RwImageAllocatePixels(RwImage* image) {
    const RwInt32 depth = image->depth;
    RwInt32 paletteBytes = 0;
    const bool palettised = depth == 4 || depth == 8;
    if (palettised) paletteBytes = static_cast<RwInt32>(ppc::slw(4u, static_cast<uint32_t>(depth)));
    image->stride = static_cast<RwInt32>((static_cast<RwUInt32>(((depth + 7) >> 3) * image->width) + 3) & 0xfffffffcu);
    const RwInt32 pixelBytes = image->stride * image->height;
    const RwInt32 total = paletteBytes + pixelBytes;
    image->cpPixels = static_cast<RwUInt8*>(RwMalloc(static_cast<RwUInt32>(total), 0x230018));
    if (image->cpPixels == nullptr) return nullptr;  // error 0x80000013
    image->palette = palettised ? reinterpret_cast<RwRGBA*>(image->cpPixels + pixelBytes) : nullptr;
    image->flags |= 1;
    return image;
}

// 0x0074f268 RwImageStreamRead: the struct chunk {width, height, depth, stride}, the image with its pixels, the rows
// (each the stored stride; a different own stride reads row by row), then the palette for 4 and 8 bits.
RwImage* RwImageStreamRead(RwStream* stream) {
    if (RwStreamFindChunk(stream, 1, nullptr, nullptr) == 0) return nullptr;
    RwInt32 header[4];  // RwMemNative32
    RwStreamRead(stream, header, sizeof(header));
    RwImage* image = RwImageCreate(header[0], header[1], header[2]);
    // BUG(original): a failed RwImageCreate is not checked; the free list does not fail here.
    RwImageAllocatePixels(image);
    const RwInt32 stride = image->stride;
    if (header[3] == stride) {
        RwStreamRead(stream, image->cpPixels, static_cast<RwUInt32>(stride * image->height));
    } else if (header[1] > 0) {
        RwInt32 offset = 0;
        for (RwInt32 row = 0;;) {
            if (header[3] < stride) {
                RwStreamRead(stream, image->cpPixels + offset, static_cast<RwUInt32>(header[3]));
            } else {
                RwStreamRead(stream, image->cpPixels + offset, static_cast<RwUInt32>(stride));
                RwStreamSkip(stream, static_cast<RwUInt32>(header[3] - stride));
            }
            if (header[1] <= row + 1) break;
            ++row;
            offset += stride;
        }
    }
    if (image->depth > 8) return image;
    RwStreamRead(stream, image->palette, ppc::slw(4u, static_cast<uint32_t>(image->depth)));
    return image;
}

dotd::gfx::RasterTexture* RwPSGLRasterGetTexture(const RwRaster* raster) {
    return raster != nullptr ? raster->psgl.texture : nullptr;
}
