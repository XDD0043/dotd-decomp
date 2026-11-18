// RwPSGLDxtn.h - the S3TC encoder the PS3's RenderWare PSGL driver links (libtxc_dxtn 1.0 by Roland Scheidegger, MIT
// licence; the 1.0.0 interface without a destination row stride): RwPSGL_RasterUnlock_maybe 0x73bdc0 compresses every
// texture level written through a lock with it before glCompressedTexImage2D (DXT1 from GL_RGB pixels, DXT5 from
// GL_RGBA ones). Library code 0x741b98-0x744a00.
//
//   [x] 0x00741b98  libdxtn_encodeColorBlock_maybe (encodedxtcolorblockfaster with fancybasecolorsearch and
//                   storedxtencodedblock inlined)
//   [x] 0x00743020  tx_compress_dxtn (extractsrccolors, encodedxt5alpha and writedxt5encodedalphablock inlined)
#pragma once
#include <cstdint>

// GL_COMPRESSED_*_S3TC_*_EXT
enum : uint32_t {
    kGlCompressedRgbS3tcDxt1 = 0x83f0,
    kGlCompressedRgbaS3tcDxt1 = 0x83f1,
    kGlCompressedRgbaS3tcDxt3 = 0x83f2,
    kGlCompressedRgbaS3tcDxt5 = 0x83f3,
};

// 0x00743020 tx_compress_dxtn(srccomps, width, height, srcPixData, destFormat, dest): `width` x `height` pixels of
// `srccomps` bytes each (rows `width` pixels apart) into 4x4 blocks of 8 (DXT1) or 16 (DXT3 / DXT5) bytes, the blocks
// of a row of blocks one after the other. Another format prints an error (fprintf) and writes nothing.
void tx_compress_dxtn(int32_t srccomps, int32_t width, int32_t height, const uint8_t* srcPixData, uint32_t destFormat,
                      uint8_t* dest);
