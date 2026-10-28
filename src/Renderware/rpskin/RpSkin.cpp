// RpSkin.cpp - see RpSkin.h.
//
//   [x] 0x00773088  _rpSkinCreateInternal_maybe
//   [x] 0x00772f30  RpSkinGeometryGetSkin            (and the inline accessors in RpSkin.h)
//   [x] 0x00772ef8  RpSkinAtomicSetHAnimHierarchy_maybe
//   [x] 0x00773ae0  RpSkinAtomicRightsCallBack_maybe         (= the atomic stream rights callback)
//   [x] 0x00773b98  RpSkinAtomicStreamAlwaysCallBack_maybe    (= the atomic stream always callback)
//   [x] 0x00773c88  RpSkinAtomicSetType
//   [x] 0x00773d38  RpSkinGeometryDestructor_maybe
//   [ ] 0x00773e40  RpSkinAtomicStreamRead_maybe     STUB(C2.9): the legacy atomic skin chunk; no level file has one
//   [x] 0x00774280  RpSkinGeometryStreamRead_maybe
//   [ ] 0x00774488  _rpSkinSortVertexWeights_maybe   STUB(C2.9): generic skinned geometry only; no level file has one
//   [ ] 0x00774a38  RpSkinPSGL_AtomicInstanceCallback_maybe   (generic geometry only; the native data is instanced)
//   [x] 0x00775478  BuildPSGLSkinBoneMatrixPalette
//   [ ] 0x007758c0  RpSkinPSGL_AtomicReinstanceCallback_maybe (RpSkinPrepareAtomicMatrices into the plugin's matrix
//                   buffer [0xcf0760], which only the software skinning path reads; the GPU path skins from the palette)
//   [x] 0x00775a48  _rpSkinAtomicSetPipelineByType_maybe
//   [x] 0x00775bc8  _rpSkinSplitDataDestroy_maybe
//   [x] 0x00775f18  _rpSkinSplitDataStreamRead_maybe
#include "Renderware/rpskin/RpSkin.h"

#include <cstdint>
#include <cstring>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/core/Stub.h"

namespace {

uint32_t Bits(RwReal x) {
    uint32_t b;
    std::memcpy(&b, &x, sizeof b);
    return b;
}

// The weight k of a vertex as the PS3 tests it (a 32-bit load compared with 0: -0.0 counts as a weight).
uint32_t WeightBits(const RwMatrixWeights* weights, uint32_t vertex, uint32_t k) {
    const RwReal* w = &weights[vertex].w0;
    return Bits(w[k]);
}

bool ReadExact(RwStream* stream, void* data, uint32_t length) { return RwStreamRead(stream, data, length) == length; }

// 0x00775f18 _rpSkinSplitDataStreamRead_maybe: the bone limit, the mesh count and the RLE count (three Int32s), then,
// for a split skin (meshes > 0), the remap indices (numBones bytes), the RLE counts (2 bytes per mesh) and the RLE
// (2 bytes per entry) into one block.
RwStream* SplitDataStreamRead(RwStream* stream, RpSkin* skin) {
    int32_t boneLimit = 0, numMeshes = 0, numRLE = 0;
    if (!ReadExact(stream, &boneLimit, 4) || !ReadExact(stream, &numMeshes, 4) || !ReadExact(stream, &numRLE, 4)) {
        return nullptr;
    }
    if (numMeshes < 1) return stream;
    if (skin->meshBoneRemapIndices != nullptr) RwFree(skin->meshBoneRemapIndices);
    skin->meshBoneRLE = nullptr;
    skin->boneLimit = 0;
    skin->numMeshes = 0;
    skin->numRLE = 0;
    skin->meshBoneRemapIndices = nullptr;
    skin->meshBoneRLECount = nullptr;
    const uint32_t rleBytes = static_cast<uint32_t>(numMeshes + numRLE) * 2;
    const uint32_t size = skin->numBones + rleBytes;
    RwUInt8* block = static_cast<RwUInt8*>(RwMalloc(size, 0x30116));
    skin->meshBoneRemapIndices = block;
    if (block == nullptr) return nullptr;
    std::memset(block, 0, size);
    skin->boneLimit = static_cast<RwUInt32>(boneLimit);
    skin->numRLE = static_cast<RwUInt32>(numRLE);
    skin->meshBoneRLECount = block + skin->numBones;
    skin->meshBoneRLE = skin->meshBoneRLECount + numMeshes * 2;
    skin->numMeshes = static_cast<RwUInt32>(numMeshes);
    if (RwStreamRead(stream, block, rleBytes + skin->numBones) != 0) return stream;
    // BUG(original): the failure path frees &skin->boneLimit (skin + 0x24), not the block; not reproduced (a host
    // free of an interior pointer). Nothing in the level files fails here.
    return nullptr;
}

}  // namespace

// 0x00773088 _rpSkinCreateInternal_maybe
RpSkin* _rpSkinCreateInternal(RwUInt32 numVertices, RwUInt32 numBones, RwUInt32 numBoneIds, RwUInt32 maxWeights,
                              const RwMatrixWeights* weights, const RwUInt32* indices, const RwMatrix* matrices) {
    RpSkin* skin = static_cast<RpSkin*>(RwMalloc(sizeof(RpSkin), 0x30116));  // the plugin's free list [0xcf076c]
    std::memset(skin, 0, sizeof *skin);
    if (maxWeights == 0) {
        // The weights in use: the first slot always, then each further slot some vertex fills (up to 4).
        skin->maxNumWeightsForVertex = 1;
        for (RwUInt32 v = 0; v < numVertices && skin->maxNumWeightsForVertex < 4; ++v) {
            while (skin->maxNumWeightsForVertex < 4 && WeightBits(weights, v, skin->maxNumWeightsForVertex) != 0) {
                ++skin->maxNumWeightsForVertex;
            }
        }
    }
    RwUInt8 boneIds[256];
    if (numBoneIds == 0) {
        // The bones the weighted slots name, in first-use order.
        for (RwUInt32 v = 0; v < numVertices; ++v) {
            for (RwUInt32 k = 0; k < skin->maxNumWeightsForVertex; ++k) {
                if (WeightBits(weights, v, k) == 0) continue;
                const RwUInt8 id = static_cast<RwUInt8>(indices[v] >> ((k & 7) << 3));
                RwUInt32 j = 0;
                while (j < numBoneIds && boneIds[j] != id) ++j;
                if (j == numBoneIds) boneIds[numBoneIds++] = id;
            }
        }
    }
    const RwUInt32 size = numVertices * 0x14 + numBones * 0x40 + 0xf + numBoneIds;
    RwUInt8* block = static_cast<RwUInt8*>(RwMalloc(size, 0x230116));
    skin->unaligned = block;
    if (block == nullptr) {
        RwFree(skin);
        return nullptr;
    }
    std::memset(block, 0, size);
    skin->numBones = numBones;
    skin->numBoneIds = numBoneIds;
    const uintptr_t aligned = (reinterpret_cast<uintptr_t>(block) + numBoneIds + 0xf) & ~static_cast<uintptr_t>(0xf);
    skin->boneIds = block;
    skin->skinToBoneMatrices = reinterpret_cast<RwMatrix*>(aligned);
    skin->vertexBoneIndices = reinterpret_cast<RwUInt32*>(aligned + numBones * 0x40);
    skin->vertexBoneWeights = reinterpret_cast<RwMatrixWeights*>(aligned + numBones * 0x40 + numVertices * 4);
    if (numBoneIds != 0) std::memcpy(skin->boneIds, boneIds, numBoneIds);
    // The matrices are copied 16 bytes at a time from the last one down (the source 16-byte aligned).
    if (matrices != nullptr && numBones != 0) std::memcpy(skin->skinToBoneMatrices, matrices, numBones * 0x40);
    if (indices != nullptr) std::memcpy(skin->vertexBoneIndices, indices, numVertices * 4);
    if (weights != nullptr) std::memcpy(skin->vertexBoneWeights, weights, numVertices * 0x10);
    return skin;
}

// 0x00774280 RpSkinGeometryStreamRead_maybe: the header word (numBones, numBoneIds, maxWeights in its low three
// bytes), the bone ids, the vertices' bone indices (Int32) and weights (Real), the skin-to-bone matrices (64 bytes each,
// Real), the split data. A native geometry's skin is flagged (+0x20); a generic one gets its weights sorted.
RwStream* RpSkinGeometryStreamRead(RwStream* stream, RwInt32 /*length*/, RpGeometry* geometry) {
    RwUInt32 header = 0;
    if (!ReadExact(stream, &header, 4)) return nullptr;  // RwStreamReadInt32
    const RwUInt32 numBones = header & 0xff;
    const RwUInt32 numBoneIds = (header >> 8) & 0xff;
    const RwUInt32 maxWeights = (header >> 16) & 0xff;
    const RwUInt32 numVertices = static_cast<RwUInt32>(geometry->numVertices);
    RpSkin* skin = _rpSkinCreateInternal(numVertices, numBones, numBoneIds, maxWeights, nullptr, nullptr, nullptr);
    if (skin == nullptr) return nullptr;
    if (RwStreamRead(stream, skin->boneIds, numBoneIds) != numBoneIds) return nullptr;
    if (!ReadExact(stream, skin->vertexBoneIndices, numVertices * 4)) return nullptr;   // RwStreamReadInt32
    if (!ReadExact(stream, skin->vertexBoneWeights, numVertices * 0x10)) return nullptr;  // RwStreamReadReal
    skin->maxNumWeightsForVertex = maxWeights;
    if (!ReadExact(stream, skin->skinToBoneMatrices, skin->numBones * 0x40)) return nullptr;  // RwStreamReadReal
    if (SplitDataStreamRead(stream, skin) == nullptr) return nullptr;
    if (skin != geometry->skin) {
        // The previous skin goes through KStub_Nop_7746f0 (nothing) and is overwritten.
        geometry->skin = skin;
        if ((geometry->flags & 0x1000000) == 0) {
            // STUB(C2.9): _rpSkinSortVertexWeights_maybe 0x774488 (each generic vertex's weights sorted largest
            // first with their indices, +0x1c the weights in use). Every skinned geometry of the level files is native.
            DOTD_STUB_ONCE("_rpSkinSortVertexWeights 0x774488: a generic skinned geometry (C2.9)");
            return stream;
        }
    } else if ((geometry->flags & 0x1000000) == 0) {
        return stream;
    }
    skin->nativeGeometry = 1;
    return stream;
}

// 0x00773d38 RpSkinGeometryDestructor_maybe
RpGeometry* RpSkinGeometryDestructor(RpGeometry* geometry) {
    RpSkin* skin = geometry->skin;
    if (skin != nullptr) {
        if (skin->unaligned != nullptr) RwFree(skin->unaligned);
        // 0x00775bc8 _rpSkinSplitDataDestroy_maybe
        if (skin->meshBoneRemapIndices != nullptr) RwFree(skin->meshBoneRemapIndices);
        skin->meshBoneRLE = nullptr;
        skin->boneLimit = 0;
        skin->numMeshes = 0;
        skin->numRLE = 0;
        skin->meshBoneRemapIndices = nullptr;
        skin->meshBoneRLECount = nullptr;
        RwFree(skin);
        geometry->skin = nullptr;
    }
    return geometry;
}

// 0x00772f30 RpSkinGeometryGetSkin
RpSkin* RpSkinGeometryGetSkin(const RpGeometry* geometry) { return geometry->skin; }

// 0x00772ef8 RpSkinAtomicSetHAnimHierarchy_maybe
RpAtomic* RpSkinAtomicSetHAnimHierarchy(RpAtomic* atomic, RpHAnimHierarchy* hierarchy) {
    atomic->skinHierarchy = hierarchy;
    return atomic;
}

RpHAnimHierarchy* RpSkinAtomicGetHAnimHierarchy(const RpAtomic* atomic) { return atomic->skinHierarchy; }

namespace {
// RwEngineGetPluginOffset(0x120) != -1: CKGraphic_AttachRwPlugins_maybe 0x59b28 attaches RpMatFX; RpToon (0x12e) is
// not attached.
constexpr bool kMatFXAttached = true;
constexpr bool kToonAttached = false;
// The atomic's MatFX plugin data (atomic + RpAtomicGetPluginOffset(0x120), RpMatFXAtomicQueryEffects_maybe): set by
// RpMatFXAtomicEnableEffects (CGeometry_SetupMaterialShader_maybe, which a skinned atomic never reaches with the
// shader pipeline: ShaderManagerPSGL_TryAssignOverride_maybe 0xf8168 answers 1 for it) or an atomic MatFX chunk.
RwUInt32 AtomicMatFXEffects(const RpAtomic* /*atomic*/) { return 0; }
}  // namespace

// 0x00775a48 _rpSkinAtomicSetPipelineByType_maybe
RpAtomic* _rpSkinAtomicSetPipelineByType(RpAtomic* atomic, RwUInt32 type) {
    if (type != rpSKINTYPEGENERIC && (type == rpSKINTYPEMATFX || (kMatFXAttached && AtomicMatFXEffects(atomic) != 0))) {
        atomic->skinPipeline = rpSKINTYPEMATFX;  // the plugin globals +0x28 (_rpSkinPipelinesCreate_maybe 0x775b28)
        return atomic;
    }
    atomic->skinPipeline = rpSKINTYPEGENERIC;  // +0x24
    return atomic;
}

// 0x00773c88 RpSkinAtomicSetType
RpAtomic* RpSkinAtomicSetType(RpAtomic* atomic, RpSkinType type) {
    if ((kMatFXAttached || type != rpSKINTYPEMATFX) && (kToonAttached || type != rpSKINTYPETOON)) {
        return _rpSkinAtomicSetPipelineByType(atomic, type);
    }
    return _rpSkinAtomicSetPipelineByType(atomic, rpSKINTYPEGENERIC);
}

// 0x00773b98 (the always callback)
RwBool RpSkinAtomicAlwaysCallBack(RpAtomic* atomic) {
    RwUInt32 type = rpSKINTYPEGENERIC;
    if (kMatFXAttached && AtomicMatFXEffects(atomic) != 0) type = rpSKINTYPEMATFX;
    if (atomic->geometry != nullptr && atomic->geometry->skin != nullptr) {
        if ((!kMatFXAttached && type == rpSKINTYPEMATFX) || (!kToonAttached && type == rpSKINTYPETOON)) {
            type = rpSKINTYPEGENERIC;
        }
        _rpSkinAtomicSetPipelineByType(atomic, type);
    }
    return 1;
}

// 0x00773ae0 (the rights callback; its fourth argument is the right-to-render chunk's extra data)
RwBool RpSkinAtomicRightsCallBack(RpAtomic* atomic, RwUInt32 extraData) {
    if (atomic->geometry == nullptr || atomic->geometry->skin == nullptr) return 1;
    RwUInt32 type = extraData;
    if ((!kMatFXAttached && type == rpSKINTYPEMATFX) || (!kToonAttached && type == rpSKINTYPETOON)) {
        type = rpSKINTYPEGENERIC;
    }
    _rpSkinAtomicSetPipelineByType(atomic, type);
    return 1;
}

namespace {
// The palette cache (0xcf0788 hierarchy, 0xcf078c the complement of the engine's render frame, 0xcf0790 the atomic's
// frame): a second atomic on the same hierarchy and frame within one camera update keeps the palette already in the
// uniform record (whatever its skin's matrices). RpSkinPSGL_AtomicReinstanceCallback_maybe shares the words (it stores
// the frame count itself, which never equals its complement); it is not ported, so it never invalidates the cache.
const RpHAnimHierarchy* g_paletteHierarchy = nullptr;
RwUInt32 g_paletteRenderFrame = 0;
const RwFrame* g_paletteFrame = nullptr;

// The 3x4 transpose of a matrix: the rows (right.x, up.x, at.x, pos.x), (.y ...), (.z ...).
void StoreTransposed3x4(RwReal* out, const RwMatrix& m) {
    out[0] = m.right.x;
    out[1] = m.up.x;
    out[2] = m.at.x;
    out[3] = m.pos.x;
    out[4] = m.right.y;
    out[5] = m.up.y;
    out[6] = m.at.y;
    out[7] = m.pos.y;
    out[8] = m.right.z;
    out[9] = m.up.z;
    out[10] = m.at.z;
    out[11] = m.pos.z;
}
}  // namespace

// 0x00775478 BuildPSGLSkinBoneMatrixPalette
void BuildPSGLSkinBoneMatrixPalette(RwReal* palette, const RpAtomic* atomic, const RpSkin* skin) {
    const RpHAnimHierarchy* hierarchy = atomic->skinHierarchy;
    if (hierarchy == nullptr) return;
    const RwUInt32 renderFrame = ~static_cast<RwUInt32>(RwEngineRenderFrame());
    if (g_paletteHierarchy == hierarchy && g_paletteRenderFrame == renderFrame && g_paletteFrame == atomic->frame) return;
    g_paletteRenderFrame = renderFrame;
    g_paletteFrame = atomic->frame;
    g_paletteHierarchy = hierarchy;
    const RwMatrix* skinToBone = RpSkinGetSkinToBoneMatrices(skin);
    RwMatrix product;
    RwMatrix temp;
    RwMatrix inverse;
    if ((hierarchy->flags & 2) == 0) {  // rpHANIMHIERARCHYNOMATRICES clear: the matrix array
        const RwMatrix* matrices = hierarchy->pMatrixArray;
        if ((hierarchy->flags & 0x4000) == 0) {  // rpHANIMHIERARCHYLOCALSPACEMATRICES clear: world space
            RwMatrixInvert(&inverse, RwFrameGetLTM(atomic->frame));
            for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
                RwMatrixMultiply(&temp, &skinToBone[i], &matrices[i]);
                RwMatrixMultiply(&product, &temp, &inverse);
                StoreTransposed3x4(palette, product);
                palette += 12;
            }
            return;
        }
        for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
            RwMatrixMultiply(&product, &skinToBone[i], &matrices[i]);
            StoreTransposed3x4(palette, product);
            palette += 12;
        }
        return;
    }
    RwMatrixInvert(&inverse, RwFrameGetLTM(atomic->frame));
    for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
        RwMatrixMultiply(&temp, &skinToBone[i], RwFrameGetLTM(hierarchy->pNodeInfo[i].pFrame));
        RwMatrixMultiply(&product, &temp, &inverse);
        StoreTransposed3x4(palette, product);
        palette += 12;
    }
}
