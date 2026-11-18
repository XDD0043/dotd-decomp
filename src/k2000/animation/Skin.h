// Skin.h - the software skinning of the unit Skin.cpp (0xc1b50-0xc2848): dead in the original (only the unreferenced
// Atomic_RenderIm3DSoftwareSkinned_maybe 0xc2848, k2000/render/Atomic.cpp, calls it; the game skins on the GPU).
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwTypes.h"

struct RpSkin;
struct RpHAnimHierarchy;

// 0x00c5d290: the bone matrix palette Skin_ComputeBoneMatrixPalette fills and Skin_BlendVerticesSoftware reads.
extern RwMatrix g_skinBoneMatrixPalette[256];

// 0x000c1b50 Skin_BlendVerticesSoftware_maybe: `count` vertices blended by up to four palette bones each (weights: four
// floats per vertex; indices: one word per vertex, bone k in byte k); positions out at `outStride` bytes, normals (when
// `inNormals` is given) into `outNormals` (which never advances: BUG(original)).
void Skin_BlendVerticesSoftware(int32_t count, const float* weights, const uint32_t* indices, float* outPositions,
                                const RwV3d* inPositions, float* outNormals, const RwV3d* inNormals,
                                int32_t outStride);
// 0x000c2278 Skin_ComputeBoneMatrixPalette_maybe: the palette from the skin's inverse bind matrices and the hierarchy
// (its node frames' LTMs, its matrices, or its local-space matrices then `ltm`).
void Skin_ComputeBoneMatrixPalette(const RwMatrix* ltm, const RpSkin* skin, const RpHAnimHierarchy* hierarchy);
