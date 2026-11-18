// RpSkin.h - RenderWare 3.7 RpSkin (skinned geometry), ported from the PS3 library code (TOC 0xc25974). RW 3.7 ships
// only the header (misc/inc/rpskin.h): the names and the API are its, the code and the layouts are the PS3 build's.
// Animation checkpoint, step 1: the atomic's hierarchy accessors; step 5: the skin data, its stream reader, the pipelines by type and
// the bone matrix palette the uber-shader skins with.
//
// The plugin (RpSkinPluginAttach_maybe 0x773620): engine plugin 0x116 (the globals block at [0xcf0754]: +0 the engine
// offset, +4 the atomic offset 0xcf0758, +8 the geometry offset 0xcf075c, +0x24 / +0x28 the two pipelines); the atomic
// plugin (constructor, destructor, copy; the legacy stream reader 0x773e40, the always callback 0x773b98 and the rights
// callback 0x773ae0); the geometry plugin (the stream reader 0x774280 and the destructor 0x773d38).
//
// What the level files hold (every KP3 of USRDIR, work/scratch-c25/step5/skinall.py): 358 skins, all of them on
// geometries with PS3 native data (flag 0x1000000), none split (bone limit 0); every skinned atomic's right-to-render
// chunk is {0x116, 1}; no atomic carries the legacy 0x116 chunk. The native vertex data already holds the weights and
// the indices (four floats each, RpNativeMesh words 26 / 27, flag word 29), so the PSGL instance callback
// (RpSkinPSGL_AtomicInstanceCallback_maybe 0x774a38, the generic geometry's interleaved layout) has nothing to do.
// The generic path is ported all the same (port-final F06): the legacy atomic chunk 0x773e40, the weight sort 0x774488,
// the instance callback's layout and vertices (inside RpAtomicPSGL.cpp's InstanceGeneric) and the reinstance callback
// 0x7758c0, which runs for every skinned atomic (all are on the generic skin pipeline).
#pragma once
#include "Renderware/rwcore/RwTypes.h"

struct RpAtomic;
struct RpGeometry;
struct RpHAnimHierarchy;
struct RwStream;

// RwMatrixWeights (rpskin.h): up to four bone weights per vertex.
struct RwMatrixWeights {
    RwReal w0;
    RwReal w1;
    RwReal w2;
    RwReal w3;
};

// RpSkin (PS3 0x40 bytes, from the plugin's free list; RW keeps the struct private). The arrays live in one block
// (+0x3c): the used bone ids, then (16-byte aligned) the skin-to-bone matrices, the vertex bone indices and weights.
struct RpSkin {
    RwUInt32 numBones;                 // +0x00
    RwUInt32 numBoneIds;               // +0x04 the bones some vertex uses
    RwUInt8* boneIds;                  // +0x08 numBoneIds bytes
    RwMatrix* skinToBoneMatrices;      // +0x0c numBones inverse bind matrices, 16-byte aligned
    RwUInt32 maxNumWeightsForVertex;   // +0x10
    RwUInt32* vertexBoneIndices;       // +0x14 per vertex: index k in bits 8k..8k+7
    RwMatrixWeights* vertexBoneWeights;  // +0x18
    RwUInt32 sortedWeights;            // +0x1c _rpSkinSortVertexWeights_maybe: the weights per vertex it found (1..4)
    RwUInt32 nativeGeometry;           // +0x20 1 when the geometry is native (RpSkinGeometryStreamRead)
    // The split data (SkinSplitData): RpSkinIsSplit = numMeshes != 0.
    RwUInt32 boneLimit;                // +0x24
    RwUInt32 numMeshes;                // +0x28
    RwUInt32 numRLE;                   // +0x2c
    RwUInt8* meshBoneRemapIndices;     // +0x30 numBones bytes, then the RLE counts and the RLE (one block)
    RwUInt8* meshBoneRLECount;         // +0x34 2 bytes per mesh
    RwUInt8* meshBoneRLE;              // +0x38 2 bytes per RLE entry
    void* unaligned;                   // +0x3c the arrays' block
};
DOTD_ASSERT_SIZE(RpSkin, 0x40);
DOTD_ASSERT_OFFSET(RpSkin, vertexBoneWeights, 0x18);
DOTD_ASSERT_OFFSET(RpSkin, meshBoneRemapIndices, 0x30);

// RpSkinType (rpskin.h).
enum RpSkinType : RwUInt32 {
    rpNASKINTYPE = 0,
    rpSKINTYPEGENERIC = 1,
    rpSKINTYPEMATFX = 2,
    rpSKINTYPETOON = 3,
};

// 0x00773088 _rpSkinCreateInternal_maybe(numVertices, numBones, numBoneIds, maxWeights, weights, indices, matrices):
// a skin with its block. maxWeights 0 counts the weights the vertices use; numBoneIds 0 collects the used bone ids from
// the indices; null arrays stay zero. Null when an allocation fails.
RpSkin* _rpSkinCreateInternal(RwUInt32 numVertices, RwUInt32 numBones, RwUInt32 numBoneIds, RwUInt32 maxWeights,
                              const RwMatrixWeights* weights, const RwUInt32* indices, const RwMatrix* matrices);
// 0x00774280 RpSkinGeometryStreamRead_maybe: the geometry plugin chunk 0x116 (the caller has read its header). Returns
// the stream, null on failure.
RwStream* RpSkinGeometryStreamRead(RwStream* stream, RwInt32 length, RpGeometry* geometry);
// 0x00772e48 RpSkinGeometryConstructor_maybe: the geometry's skin pointer cleared (the plugin's constructor,
// RpGeometryCreate's plugin registry).
RpGeometry* RpSkinGeometryConstructor(RpGeometry* geometry);
// 0x00773d38 RpSkinGeometryDestructor_maybe: the geometry's skin freed (RpGeometryDestroy).
RpGeometry* RpSkinGeometryDestructor(RpGeometry* geometry);

// 0x00772f30 RpSkinGeometryGetSkin (geometry + [0xcf075c]).
RpSkin* RpSkinGeometryGetSkin(const RpGeometry* geometry);
// RpSkinGetNumBones (+0x00), RpSkin_GetMaxWeightsPerVertex_maybe (+0x10), RpSkinGetVertexBoneIndices (+0x14),
// RpSkinGetVertexBoneWeights (+0x18), 0x00772f68 RpSkinGetSkinToBoneMatrices (+0x0c).
inline RwUInt32 RpSkinGetNumBones(const RpSkin* skin) { return skin->numBones; }
inline RwUInt32 RpSkinGetMaxWeightsPerVertex(const RpSkin* skin) { return skin->maxNumWeightsForVertex; }
inline const RwUInt32* RpSkinGetVertexBoneIndices(const RpSkin* skin) { return skin->vertexBoneIndices; }
inline const RwMatrixWeights* RpSkinGetVertexBoneWeights(const RpSkin* skin) { return skin->vertexBoneWeights; }
inline const RwMatrix* RpSkinGetSkinToBoneMatrices(const RpSkin* skin) { return skin->skinToBoneMatrices; }
// 0x00772f70 RpSkinIsSplit_maybe: numMeshes != 0.
inline RwBool RpSkinIsSplit(const RpSkin* skin) { return skin->numMeshes != 0 ? 1 : 0; }
// 0x00775bb0 _rpSkinGetMeshBoneRemapIndices_maybe / 0x00775bb8 _rpSkinGetMeshBoneRLECount_maybe / _rpSkinGetMeshBoneRLE.
inline RwUInt8* _rpSkinGetMeshBoneRemapIndices(const RpSkin* skin) { return skin->meshBoneRemapIndices; }
inline RwUInt8* _rpSkinGetMeshBoneRLECount(const RpSkin* skin) { return skin->meshBoneRLECount; }
inline RwUInt8* _rpSkinGetMeshBoneRLE(const RpSkin* skin) { return skin->meshBoneRLE; }

// 0x00772ef8 RpSkinAtomicSetHAnimHierarchy_maybe: the atomic's skin plugin data (atomic + [0xcf0758]) keeps the
// hierarchy whose matrices skin it. Returns the atomic.
RpAtomic* RpSkinAtomicSetHAnimHierarchy(RpAtomic* atomic, RpHAnimHierarchy* hierarchy);
// RpSkinAtomicGetHAnimHierarchy (the same slot read back).
RpHAnimHierarchy* RpSkinAtomicGetHAnimHierarchy(const RpAtomic* atomic);

// 0x00773c88 RpSkinAtomicSetType: the MatFX and toon types fall back to the generic one when their plugin is not
// attached, then _rpSkinAtomicSetPipelineByType.
RpAtomic* RpSkinAtomicSetType(RpAtomic* atomic, RpSkinType type);
// 0x00775a48 _rpSkinAtomicSetPipelineByType_maybe: the atomic's pipeline (+0x6c) becomes the skin plugin's generic
// pipeline (globals +0x24) or its MatFX one (+0x28: type 2, or another type when the atomic has MatFX effects).
RpAtomic* _rpSkinAtomicSetPipelineByType(RpAtomic* atomic, RwUInt32 type);
// 0x00773b98 (Ghidra RpSkinAtomicStreamAlwaysCallBack_maybe; it is the atomic plugin's stream always callback, registered by
// RpAtomicSetStreamAlwaysCallBack): a skinned atomic takes the MatFX pipeline when it has MatFX effects, else the
// generic one.
RwBool RpSkinAtomicAlwaysCallBack(RpAtomic* atomic);
// 0x00773ae0 (Ghidra RpSkinAtomicRightsCallBack_maybe; it is the rights callback, RpAtomicSetStreamRightsCallBack): a
// skinned atomic takes the pipeline of the right-to-render chunk's extra data (the type).
RwBool RpSkinAtomicRightsCallBack(RpAtomic* atomic, RwUInt32 extraData);

// 0x00773e40 RpSkinAtomicStreamRead_maybe: the atomic plugin's legacy chunk 0x116 (a skin stored with the atomic, older
// files; none in the level files). A geometry that already has a skin skips `sizeInObject` bytes (the PS3 passes the
// plugin's size, 4, not the chunk's length: BUG(original), kept). Else: the bone count, 4 bytes skipped, the vertices'
// bone indices and weights, per bone 12 bytes skipped and the skin-to-bone matrix; the weights in use and the used
// bone ids counted; the skin set on the geometry (a generic geometry's weights sorted). Returns the stream, null on a
// read failure.
RwStream* RpSkinAtomicStreamRead(RwStream* stream, RwInt32 length, RpAtomic* atomic, RwInt32 sizeInObject);
// 0x00774488 _rpSkinSortVertexWeights_maybe: each vertex whose first weight is below 1.0 has its four weights sorted
// largest first with their bone indices (signed word compares of the float bits); the skin's +0x1c becomes the most
// weights a vertex uses (1..4). Returns the geometry.
RpGeometry* _rpSkinSortVertexWeights(RpGeometry* geometry);

struct RpNativeMesh;
// 0x00774a38 RpSkinPSGL_AtomicInstanceCallback_maybe, the part a host instancer keeps (the GL buffer mapping is the
// device's: RpAtomicPSGL.cpp's InstanceGeneric builds device meshes from the vertex arrays). The layout: the geometry
// and the record take the format bit 0x400; after the interleaved attributes (`stride` bytes) the four weights (word 26)
// and the four bone indices (word 27, +0x10), word 29 = 1. Returns the new stride (+0x20).
RwUInt32 RpSkinPSGL_InstanceLayout(RpGeometry* geometry, RpNativeMesh* layout, RwUInt32 stride);
// The vertices: per vertex the skin's four weights (the words as they are) and its four index bytes as floats (index k
// = bits 8k..8k+7), at the layout's words 26 / 27, `layout->stride` bytes apart.
void RpSkinPSGL_InstanceSkinVertices(const RpGeometry* geometry, const RpNativeMesh* layout, RwUInt8* vertices);
// 0x007758c0 RpSkinPSGL_AtomicReinstanceCallback_maybe after its first call (the pipeline's own reinstance callback,
// kept at the plugin globals +0x44 by _rpSkinCreatePlatformPipeline_maybe 0x774830; RpAtomicPSGL_Render runs it inline
// first): for a skinned atomic with a hierarchy, unless the cache (hierarchy, render frame, atomic frame) matches,
// RpSkinPrepareAtomicMatrices_maybe 0x776990 into the plugin's matrix buffer, their fourth column words cleared, and the
// cache set (the render frame as it is: BuildPSGLSkinBoneMatrixPalette stores its complement in the same word). 1.
RwBool RpSkinPSGL_AtomicReinstanceCallback(RpAtomic* atomic);

// 0x00775478 BuildPSGLSkinBoneMatrixPalette(palette, atomic, skin): per hierarchy node, the skin-to-bone matrix times
// the node's matrix (times the inverse of the atomic's LTM unless the hierarchy's matrices are in local space; the
// nodes' frames' LTMs for a hierarchy without matrices), stored as the 3x4 transpose (three float4 rows: the
// uber-shader's float3x4 u_f34BoneMatrix[70]). Nothing is written when the atomic has no hierarchy.
void BuildPSGLSkinBoneMatrixPalette(RwReal* palette, const RpAtomic* atomic, const RpSkin* skin);
