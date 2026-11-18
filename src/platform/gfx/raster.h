// raster.h - the textures of the PS3's PSGL driver as RenderWare's rasters use them (new platform code, not a port).
//
// The PS3 driver keeps a GL texture name in each raster's extension (RwPSGLRasterExt +0x00, Renderware/rwcore/
// RwRaster.h) and fills it with glTexImage2D / glCompressedTexImage2D (RwPSGL_RasterUnlock_maybe 0x73bdc0) or binds it
// to a pixel buffer holding a DDS file's mip chain (glTextureReferenceSCE, RwStreamReadDDSRaster_maybe 0x73a8d8). Here
// those calls land on a RasterTexture: it keeps the level data the driver gave GL and makes the device texture from
// it the first time the texture is sampled (the game loads before the window exists in the tests, and headless runs
// never make one).
#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

namespace dotd::gfx {

struct RasterTexture;

// glGenTextures(1, &name) / glDeleteTextures(1, &name) (with the device texture, when one was made).
RasterTexture* GenRasterTexture();
void DeleteRasterTexture(RasterTexture* texture);

// glTextureReferenceSCE(GL_TEXTURE_2D, levels, width, height, 1, format, 0, 0) on a pixel buffer filled with a DDS
// file's data: `format` the GL compressed format the driver chose (GL_COMPRESSED_RGBA_S3TC_DXT1/3/5_EXT 0x83f1 /
// 0x83f2 / 0x83f3; 0 for an uncompressed file, which the device cannot show), `data` the face's mip chain as stored.
// A cube map references one buffer per face; the device texture is a 2D texture made from the first face.
void RasterTextureReferenceDds(RasterTexture* texture, uint32_t format, int levels, int width, int height,
                               std::vector<uint8_t> data);
// glTexImage2D(GL_TEXTURE_2D, level, ...) from `height` rows `stride` bytes apart of `bytesPerPixel` bytes each:
// 4 = R G B A (GL_RGBA), 3 = R G B (GL_RGB). The level replaces the one stored before; the device texture is made
// again at its next use.
void RasterTextureImage(RasterTexture* texture, int level, int width, int height, int bytesPerPixel,
                        const uint8_t* pixels, int stride);
// glCompressedTexImage2D(GL_TEXTURE_2D, level, format, ...) of S3TC blocks (format GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83f0,
// RGBA DXT1 0x83f1, DXT3 0x83f2, DXT5 0x83f3; ((width + 3) / 4) x ((height + 3) / 4) blocks). The level is kept as the
// texels the blocks decode to (the S3TC decoding of libtxc_dxtn's fetch functions: 565 expanded by bit replication,
// the interpolated colours and alphas by integer division, which is what a GPU's BC1-3 sampling gives within its
// rounding), so the device texture is made as for RasterTextureImage.
void RasterTextureCompressedImage(RasterTexture* texture, int level, uint32_t format, int width, int height,
                                  const uint8_t* blocks);
// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, lod) on the texture.
void RasterTextureSetMaxLod(RasterTexture* texture, float lod);

// The device texture (made on the first call); 0 without a device, without data or for a format the device has not.
uint32_t RasterTextureDevice(RasterTexture* texture);

// The web build only (0 and nothing done natively): the device texture of every texture that has none yet, made
// now. WebGL takes far longer than a desktop driver to take a texture's data, and a level's first drawn frame
// samples a hundred textures for the first time; the game calls this when a level has loaded, its loading screen
// still up (with the shader programs, CShaderManagerPSGL.h). Main thread, while no load is running. Returns how many.
int MakeRasterTexturesAhead();

}  // namespace dotd::gfx
