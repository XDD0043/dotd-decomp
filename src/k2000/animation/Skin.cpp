// Reconstructed original translation unit: 0xc1b50-0xc2848 (GAME_TOC1, main_toc1), 5 functions, 2 live.
// Primary owner: Skin (not a registered class)
// Other owners: RpMeshHeader (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc1b50  Skin_BlendVerticesSoftware_maybe  [dead: only caller 0xc2848]  (Skin_BlendVerticesSoftware, Skin.h; R08's Atomic_RenderIm3DSoftwareSkinned calls it)
//   [ ] 0xc2160  RpMeshHeader_BuildFromTriangles_maybe  [dead]
//   [x] 0xc2278  Skin_ComputeBoneMatrixPalette_maybe  [dead: only caller 0xc2848]  (Skin_ComputeBoneMatrixPalette, Skin.h; same caller)
//
// Animation checkpoint, step 5: both "live" functions are called only by Atomic_RenderIm3DSoftwareSkinned_maybe 0xc2848
// (k2000/render/Atomic.cpp), whose function descriptor 0xb4d418 nothing references (no TOC slot, vtable or data word
// in 0xb00000..0xc40000 holds it; Ghidra lists no reference to it). The game skins on the GPU only
// (BuildPSGLSkinBoneMatrixPalette 0x775478 through the bone palette uniform, Renderware/rpskin/RpSkin.cpp).
//   [ ] 0xc2488  FUN_000c2488  [dead]
//   [ ] 0xc2628  FUN_000c2628  [dead]
#include "k2000/animation/Skin.h"

#include <cstring>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rpskin/RpSkin.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

// 0x00c5d290: the bone matrix palette of the software skinning (256 matrices: the indices are bytes).
RwMatrix g_skinBoneMatrixPalette[256];

namespace {
// A weight is tested by its bits as a signed word (lwz / cmpwi / ble): only a positive, non-zero float counts.
bool WeightCounts(const float* weight) {
    int32_t bits;
    std::memcpy(&bits, weight, 4);
    return bits > 0;
}

// One bone's share of a position: (right x + up y + at z + pos) * w, stored (first) or added by fmadds (the rest).
// The loads and stores follow the original (the input re-read after each store, the old sums read first).
void BlendPosition(const RwMatrix* m, const RwV3d* in, float* out, const float* weight, bool first) {
    const float vy = in->y;
    const float vx = in->x;
    const float vz = in->z;
    if (first) {
        const float upY = m->up.y * vy;
        out[0] = (ppc::fmadds(m->at.x, vz, ppc::fmadds(m->right.x, vx, m->up.x * vy)) + m->pos.x) * *weight;
        const float vx2 = in->x;
        out[1] = (ppc::fmadds(m->at.y, vz, ppc::fmadds(m->right.y, vx2, upY)) + m->pos.y) * *weight;
        const float vy2 = in->y;
        out[2] = (ppc::fmadds(m->at.z, vz, ppc::fmadds(m->right.z, vx2, m->up.z * vy2)) + m->pos.z) * *weight;
        return;
    }
    const float w = *weight;
    const float oldX = out[0];
    const float oldY = out[1];
    const float oldZ = out[2];
    const float upX = m->up.x * vy;
    const float upY = m->up.y * vy;
    out[0] = ppc::fmadds(ppc::fmadds(m->at.x, vz, ppc::fmadds(m->right.x, vx, upX)) + m->pos.x, w, oldX);
    const float vx2 = in->x;
    out[1] = ppc::fmadds(ppc::fmadds(m->at.y, vz, ppc::fmadds(m->right.y, vx2, upY)) + m->pos.y, *weight, oldY);
    const float vy2 = in->y;
    out[2] = ppc::fmadds(ppc::fmadds(m->at.z, vz, ppc::fmadds(m->right.z, vx2, m->up.z * vy2)) + m->pos.z, *weight,
                         oldZ);
}

// One bone's share of a normal: the same without the translation.
void BlendNormal(const RwMatrix* m, const RwV3d* in, float* out, const float* weight, bool first) {
    const float ny = in->y;
    const float nx = in->x;
    const float nz = in->z;
    if (first) {
        const float upY = m->up.y * ny;
        out[0] = ppc::fmadds(m->at.x, nz, ppc::fmadds(m->right.x, nx, m->up.x * ny)) * *weight;
        const float nx2 = in->x;
        out[1] = ppc::fmadds(m->at.y, nz, ppc::fmadds(m->right.y, nx2, upY)) * *weight;
        const float ny2 = in->y;
        out[2] = ppc::fmadds(m->at.z, nz, ppc::fmadds(m->right.z, nx2, m->up.z * ny2)) * *weight;
        return;
    }
    const float w = *weight;
    const float oldX = out[0];
    const float oldY = out[1];
    const float oldZ = out[2];
    const float upX = m->up.x * ny;
    const float upY = m->up.y * ny;
    out[0] = ppc::fmadds(ppc::fmadds(m->at.x, nz, ppc::fmadds(m->right.x, nx, upX)), w, oldX);
    const float nx2 = in->x;
    out[1] = ppc::fmadds(ppc::fmadds(m->at.y, nz, ppc::fmadds(m->right.y, nx2, upY)), *weight, oldY);
    const float ny2 = in->y;
    out[2] = ppc::fmadds(ppc::fmadds(m->at.z, nz, ppc::fmadds(m->right.z, nx2, m->up.z * ny2)), *weight, oldZ);
}
}  // namespace

// 0x000c1b50 Skin_BlendVerticesSoftware_maybe: for each of `count` vertices, the position (and with `inNormals` the
// normal) blended by up to four bones of the palette: bone k = byte k of the vertex's index word, used while weight k
// is positive (tested by its bits; the first zero weight ends the vertex). The positions go out at `outStride` bytes;
// BUG(original): the normal output pointer never advances (every vertex writes the first normal). Dead in the original
// (only Atomic_RenderIm3DSoftwareSkinned_maybe 0xc2848 calls it, R08's k2000/render/Atomic.cpp, itself unreferenced).
void Skin_BlendVerticesSoftware(int32_t count, const float* weights, const uint32_t* indices, float* outPositions,
                                const RwV3d* inPositions, float* outNormals, const RwV3d* inNormals,
                                int32_t outStride) {
    if (count <= 0) return;
    uint8_t* out = reinterpret_cast<uint8_t*>(outPositions);
    for (int32_t i = 0; i < count; ++i) {
        if (i != 0) out += outStride;
        const float* w = weights + i * 4;
        const uint32_t bones = indices[i];
        float* position = reinterpret_cast<float*>(out);
        for (int32_t k = 0; k < 4; ++k) {
            if (!WeightCounts(&w[k])) break;
            const RwMatrix* m = &g_skinBoneMatrixPalette[(bones >> (8 * k)) & 0xffu];
            BlendPosition(m, &inPositions[i], position, &w[k], k == 0);
            if (inNormals != nullptr) BlendNormal(m, &inNormals[i], outNormals, &w[k], k == 0);
        }
    }
}

// 0x000c2278 Skin_ComputeBoneMatrixPalette_maybe: the palette from the skin's inverse bind matrices
// (RpSkinGetSkinToBoneMatrices) and the hierarchy: with rpHANIMHIERARCHYNOMATRICES (flag 2) each node frame's LTM
// (RwFrameGetLTM); with rpHANIMHIERARCHYLOCALSPACEMATRICES (0x4000) the hierarchy's matrix then `ltm`; else the hierarchy's
// matrix (RwMatrixMultiply(palette, skinToBone, ...)). A null hierarchy does nothing. Dead in the original (same caller).
void Skin_ComputeBoneMatrixPalette(const RwMatrix* ltm, const RpSkin* skin, const RpHAnimHierarchy* hierarchy) {
    if (hierarchy == nullptr) return;
    const RwMatrix* skinToBone = RpSkinGetSkinToBoneMatrices(skin);
    const uint32_t flags = static_cast<uint32_t>(hierarchy->flags);
    if ((flags & 2u) != 0) {
        for (int32_t i = 0; i < hierarchy->numNodes; ++i) {
            RwMatrix* frameLtm = RwFrameGetLTM(hierarchy->pNodeInfo[i].pFrame);  // BridgeRwGetFrameLocalToWorldMatrix
            RwMatrixMultiply(&g_skinBoneMatrixPalette[i], skinToBone, frameLtm);
            ++skinToBone;
        }
        return;
    }
    if ((flags & 0x4000u) == 0) {
        for (int32_t i = 0; i < hierarchy->numNodes; ++i) {
            RwMatrixMultiply(&g_skinBoneMatrixPalette[i], skinToBone, &hierarchy->pMatrixArray[i]);
            ++skinToBone;
        }
        return;
    }
    for (int32_t i = 0; i < hierarchy->numNodes; ++i) {
        RwMatrix local;
        RwMatrixMultiply(&local, skinToBone, &hierarchy->pMatrixArray[i]);
        RwMatrixMultiply(&g_skinBoneMatrixPalette[i], &local, ltm);
        ++skinToBone;
    }
}
