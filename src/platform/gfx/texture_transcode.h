// texture_transcode.h - the DXT (S3TC) textures for a GPU without S3TC (new platform code).
//
// The game's textures are DXT1 / DXT3 / DXT5, which a desktop GPU samples as they are. A phone's GPU has no S3TC: the
// web build used to decode them to RGBA8 (4 to 8 times the memory and the bandwidth of DXT, gfx::CreateTexture) and
// still does when nothing better is there. Where the browser has ASTC (WEBGL_compressed_texture_astc: most phones of
// recent years), each 4x4 DXT block is rewritten as one ASTC 4x4 block instead, directly, without a search:
//   - a DXT1 block of four colours, and a DXT3 / DXT5 block whose 16 alphas are equal: one plane, the two colours as
//     8-bit endpoints, 2-bit weights at 0, 21, 43, 64 / 64 (DXT's thirds within rounding): practically the same pixels;
//   - a DXT1 block of three colours: 3-level weights (0, 32, 64: DXT1's half way exactly); with transparent texels a
//     second weight plane for the alpha (0 or 255), the colour endpoints at 7 bits;
//   - a DXT3 / DXT5 block with varying alpha: a second weight plane for the alpha with 4 levels (DXT5 has 8) between
//     endpoints fitted to the block's alphas; the colour endpoints at ASTC's 48 levels. The only real loss.
// The block layout is ARM's astc-encoder's (thirdparty/astc-encoder, symbolic_to_physical): the web build links it;
// without the clone, or natively, only the decoder below is there. tests/astc_transcode_test.cpp checks every block
// of the game's textures against astc-encoder's decoder.
#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

#include "platform/gfx/device.h"

namespace dotd::gfx {

// DXT1 / DXT3 / DXT5 (kBC1..kBC3) of width x height to RGBA8 (the fallback, and the reference of the test).
std::vector<uint8_t> DecodeS3tc(TextureFormat format, int width, int height, const uint8_t* data);

struct AstcStats {
    uint64_t blocks[5] = {};  // per block kind: DXT1 four colours, DXT1 three colours, DXT1 with transparent texels,
                              // DXT3/5 with one alpha, DXT3/5 with varying alpha
    double ms = 0.0;
};

// Whether this build can transcode (astc-encoder linked) and its tables are ready; the first call sets them up.
bool AstcTranscodeReady();
// The test: every block packed by astc-encoder's symbolic_to_physical instead of the fast path (the same bytes).
void SetAstcReferencePacking(bool on);
// The DXT level of width x height to ASTC 4x4 blocks (16 bytes per 4x4 texels, partial blocks included).
std::vector<uint8_t> TranscodeS3tcToAstc4x4(TextureFormat format, int width, int height, const uint8_t* data,
                                            AstcStats* stats);

}  // namespace dotd::gfx
