// RpAtomic.h - RenderWare atomics as the loader creates them: streamed atomics (chunk 0x14, RpAtomicStreamRead
// in RpGeometryStream.cpp: the real geometry with its materials and mesh data since C2.4 step 1), PTank
// atomics (RpPTankAtomicCreate) hold the particle arrays the Loads read.
// STUB(C1.4): the pipelines and rendering behind them.
#pragma once
#include <cstdint>
#include <vector>

struct RwStream;
struct RwTexture;
struct RpPrtStdEmitter;

// The PTank plugin data (RpPTank, atomic + 0x00cf079c on the PS3; 0x140 bytes): what CParticleGeometry_Load
// and the RpPrtStd emitters fill, and the renderer reads. The PS3 offsets in the comments.
struct RpPTankData {
    uint32_t maxParticles;   // +0x00 RpPTankAtomicCreate's count: the capacity of every per-particle array
    uint32_t numPrt;         // +0x04 particles to draw (the loader's second header word; the emitters' count)
    uint32_t dataFlags;      // (+0xa8) the creation flags as RpPTankAtomicCreate normalised them
    uint32_t lockFlags;      // +0x3c the arrays locked for writing since the last unlock (with 0x40000000)
    uint32_t flags40;        // +0x40 the changed flags (0x800000 count, 0x10000000 render states, ...)
    uint32_t renderC0[2];    // +0xc0 rpPTANKDFLAGCNSSIZE 0x200: the constant size (8 bytes)
    uint32_t renderC8;       // +0xc8 0x1000: the constant 2D rotation (a float)
    uint8_t colorCC[4];      // +0xcc 0x400: the constant colour (RwRGBA)
    uint8_t vtxColorD0[16];  // +0xd0 0x2000: the constant vertex colours
    uint32_t texCoordsE0[8]; // +0xe0 0x4000: 2 / 0x8000: 4 constant tex coords
    uint32_t matrix100[16];  // +0x100 0x800: a CMatrix34 (CMatrix34_LoadMatrix)
    uint32_t renderAC;       // +0xac source blend (RwRenderStateGet(10) at creation)
    uint32_t renderB0;       // +0xb0 destination blend (11)
    uint32_t renderB4;       // +0xb4 vertex alpha (12)
    uint32_t wordB8;         // +0xb8 RpPrtStd's PTanks: -0.0f (TOC 0x80000000)
    uint32_t wordBC;         // +0xbc
    uint8_t materialColor[4];  // the PTank material's colour (RpMaterial +4)
    int32_t numProp;         // +0xa0 the property table: the number of per-particle arrays
    int32_t strideOverride;  // +0xa4 interleaved storage's common stride (0 here: separate arrays)
    // Per-particle arrays (rpPTANKDFLAG* 0x1 .. 0x100), PS3 strides: position 16 (12 used), colour 4 (raw),
    // size 8, matrix 64, normal 12, 2D rotation 4, vertex colours 16 (raw), 2 tex coords 16, 4 tex coords 32;
    // maxParticles + 4 entries each, 16-byte aligned (`data`, inside `storage`).
    std::vector<uint8_t> storage[9];
    uint8_t* data[9];
    int32_t stride[9];
};
typedef RpPTankData RwShim_PTank;

// rpptank.h RpPTankLockStruct.
struct RpPTankLockStruct {
    uint8_t* data;
    int32_t stride;
};
// The property table (+0xa0): count, interleaved stride, data flags.
struct RpPTankPropertyTable {
    int32_t numProp;
    int32_t stride;
    uint32_t dataFlags;
};

struct RpGeometry;
struct RwFrame;
struct RpAtomic;
typedef RpAtomic* (*RpAtomicCallBackRender)(RpAtomic* atomic);

struct RpAtomic {
    // C1.5 (Rt2d shapes, rpworld/RpGeometry.h): the atomics RpAtomicCreate makes for an Rt2d shape:
    // object.parent (RpAtomicSetFrame), the geometry (RpAtomicSetGeometry) and the render callback
    // (PS3 +0x48, called by the shape renderer). Null for streamed and PTank atomics.
    RwFrame* frame = nullptr;
    RpGeometry* geometry = nullptr;
    RpAtomicCallBackRender renderCallBack = nullptr;
    RpAtomic* clonedFrom;      // RpAtomicClone's source
    RpPTankData* ptank;        // RpPTankAtomicCreate, or null
    float boundingSphere[4];   // RpAtomic boundingSphere (center, radius)
    float worldSphere[4];      // RpAtomic worldBoundingSphere
    uint32_t flags;            // RpAtomic flags (bit 1 cleared for PTank atomics: rpATOMICCOLLISIONTEST?)
    uint8_t objectFlags;       // RwObject flags (bit 0 cleared for PTank atomics)
    RwTexture* texture;        // RpMaterialSetTexture on its first material
    // The RpPrtStd plugin data (atomic + 0x00cfba78): the emitter list (its last emitter added), or null.
    RpPrtStdEmitter* prtStdEmitters;
    // The right-to-render chunk (0x1f) of the atomic's extension: the plugin id (0x116 skin ...) whose
    // pipeline draws it, and its extra data (_rwPluginRegistryInvokeRights); 0 when the file has none.
    uint32_t rightsPluginId;
    uint32_t rightsExtraData;
    // The RpSkin plugin data of the atomic (atomic + 0x00cf0758): the HAnim hierarchy whose matrices skin it,
    // RpSkinAtomicSetHAnimHierarchy_maybe 0x772ef8 (Renderware/rpskin/RpSkin.h).
    struct RpHAnimHierarchy* skinHierarchy = nullptr;
    // The atomic's pipeline (+0x6c) when it is one of the skin plugin's (_rpSkinAtomicSetPipelineByType_maybe
    // 0x775a48): rpSKINTYPEGENERIC 1 or rpSKINTYPEMATFX 2; 0 for the shader manager's atomic pipeline or the default.
    uint32_t skinPipeline = 0;
};

// 0x0069ff28 RpAtomicStreamRead after RwStreamFindChunk(0x14): see rpworld/RpGeometry.h.
RpAtomic* RpAtomicClone(RpAtomic* atomic);                                           // null in, null out
// 0x0077ab00 RpPTankAtomicCreate (and RpPTankAtomicCreateCustom_maybe 0x779ee0 with the default storage):
// the flags normalised, the arrays allocated, the constants defaulted, the render callback the PTank's.
RpAtomic* RpPTankAtomicCreate(uint32_t maxParticles, uint32_t dataFlags, uint32_t platFlags);
int32_t RpAtomicIsPTank(RpAtomic* atomic);
// RpPTankAtomicLock(atomic, &array, flag, rpPTANKLFLAGALL...): the storage of one per-particle array.
uint8_t* RwShim_PTankArray(RpAtomic* atomic, uint32_t flag);
// 0x00779b00 RpPTankAtomicGetPropertyTable_maybe
const RpPTankPropertyTable* RpPTankAtomicGetPropertyTable(RpAtomic* atomic);
// 0x00779b20 RpPTankAtomicLock: one array's storage and stride; 0 (both null) when the PTank has no such
// array. With rpPTANKLFLAGWRITE (0x40000000) the lock flags remember it.
int32_t RpPTankAtomicLock(RpAtomic* atomic, RpPTankLockStruct* lock, uint32_t flag, uint32_t lockFlags);
// 0x00779ce8 RpPTankAtomicUnlock: the locked flags become changed flags.
RpAtomic* RpPTankAtomicUnlock(RpAtomic* atomic);
// 0x007799a0 RW_RenderParticleTankAtomic (the PTank atomic's render callback; Renderware/rpptank).
RpAtomic* RpPTankAtomicRender(RpAtomic* atomic);
