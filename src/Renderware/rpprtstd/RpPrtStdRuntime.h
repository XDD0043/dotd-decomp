// RpPrtStdRuntime.h - the running side of the RpPrtStd / RpPrtAdv plugins (emitting, updating and rendering
// particles), shared by RpPrtStdRuntime.cpp (the atomic and emitter loops, batches, the PTank property),
// RpPrtStdEmit.cpp (the standard emit callback), RpPrtStdUpdate.cpp (the standard particle update) and
// RpPrtAdv.cpp (the advanced emit / update callbacks).
//
// Native layout (see RpPrtStd.h): the standard property (1) and the PTank property (6) hold pointers; they
// are native structs below, their table sizes grown by the pointer growth (0 in 32-bit builds, where the
// offsets are the PS3's). Particle batches: the header, then the particles from `offset` (0x20, the PS3
// value, in every build), each the particle class's object size.
#pragma once
#include <atomic>
#include <cstdint>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwTypes.h"

struct RwTexture;
struct RwMatrix;

// rpprtstd.h RpPrtStdParticleBatch (PS3 header 0x18, the particles at +0x20).
struct RpPrtStdParticleBatch {
    RpPrtStdParticleBatch* next;      // +0x00 circular list (the emitter's active or inactive ring)
    RpPrtStdParticleClass* prtClass;  // +0x04
    int32_t numPrt;                   // +0x08 live particles (packed at the head)
    int32_t maxPrt;                   // +0x0c
    int32_t newPrt;                   // +0x10 first particle emitted this frame (-1 after an update)
    int32_t offset;                   // +0x14 0x20: the first particle, from the batch
};
inline uint8_t* RpPrtStdBatchParticles(RpPrtStdParticleBatch* batch) {
    return reinterpret_cast<uint8_t*>(batch) + batch->offset;
}

// The particle class callbacks: (emitter, batch, data) -> batch, 7 slots (PS3 0x1c bytes). Slots as the
// RW loops call them: 0 update (RW_UpdateParticleEmitter, data = the delta time), 1 render
// (RW_RenderParticleEmitter), 2 batch create (RpPrtStdParticleBatchInit / NewParticleBatch), 3 batch emptied
// (moved to the inactive ring).
typedef RpPrtStdParticleBatch* (*RpPrtStdParticleCallBack)(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch,
                                                           void* data);
enum : int32_t {
    rpPRTSTDPARTICLECALLBACKUPDATE = 0,
    rpPRTSTDPARTICLECALLBACKRENDER = 1,
    rpPRTSTDPARTICLECALLBACKCREATE = 2,
    rpPRTSTDPARTICLECALLBACKDESTROY = 3,
    rpPRTSTDPARTICLECALLBACKMAX = 7,
};
struct RpPrtStdParticleCallBackArray {
    RpPrtStdParticleCallBack callback[rpPRTSTDPARTICLECALLBACKMAX];
};

// The emitter callback slots the RW loops call (RpPrtStd.h has create/destroy/stream/clone): 0 emit and
// 2 after the emit (RW_EmitParticleEmitter), 1 before the particles' update (RW_UpdateParticleEmitter),
// 3 before and 4 after the particles' render (RW_RenderParticleEmitter).
enum : int32_t {
    rpPRTSTDEMITTERCALLBACKUPDATE = 1,
    rpPRTSTDEMITTERCALLBACKPOSTEMIT = 2,
    rpPRTSTDEMITTERCALLBACKPRERENDER = 3,
    rpPRTSTDEMITTERCALLBACKPOSTRENDER = 4,
};

// Emitter flags beyond RpPrtStd.h's (rpprtstd.h).
enum : uint32_t {
    rpPRTSTDEMITTERFLAGUPDATE = 0x10,
    rpPRTSTDEMITTERFLAGUPDATEPARTICLE = 0x20,
    rpPRTSTDEMITTERFLAGRENDER = 0x40,
    rpPRTSTDEMITTERFLAGRENDERPARTICLE = 0x80,
};

// Particle property codes (rpprtstd.h) and the advanced ones (rpprtadv.h, the same codes as the emitter's).
enum : int32_t {
    rpPRTSTDPROPERTYCODEPARTICLESTANDARD = 0,
    rpPRTSTDPROPERTYCODEPARTICLEPOSITION = 1,
    rpPRTSTDPROPERTYCODEPARTICLECOLOR = 2,
    rpPRTSTDPROPERTYCODEPARTICLETEXCOORDS = 3,
    rpPRTSTDPROPERTYCODEPARTICLE2DROTATE = 4,
    rpPRTSTDPROPERTYCODEPARTICLESIZE = 5,
    rpPRTSTDPROPERTYCODEPARTICLEVELOCITY = 6,
    rpPRTSTDPROPERTYCODEPARTICLEMATRIX = 7,
};

// Property 1, the standard emitter property (rpprtstd.h RpPrtStdEmitterStandard in DotD's order; PS3 size
// 0xb4, the two pointers at +0xa8 / +0xac).
struct RpPrtStdEmitterStandard {
    int32_t seed;              // +0x00 the emitter's random state (the LCG seed * 0xbb38435 + 0x3619636b)
    int32_t maxPrt;            // +0x04
    RwReal currTime;           // +0x08
    RwReal prevTime;           // +0x0c
    RwV3d force;               // +0x10
    RwReal unk1c;              // +0x1c read after the force
    RwV3d emtPos;              // +0x20
    RwV3d emtSize;             // +0x2c
    RwReal emtEmitGap;         // +0x38
    RwReal emtEmitGapBias;     // +0x3c
    RwReal emtPrevEmitTime;    // +0x40
    RwReal emtEmitTime;        // +0x44
    int32_t emtPrtEmit;        // +0x48
    int32_t emtPrtEmitBias;    // +0x4c
    RwReal prtInitVel;         // +0x50
    RwReal prtInitVelBias;     // +0x54
    RwReal prtLife;            // +0x58
    RwReal prtLifeBias;        // +0x5c
    RwV3d prtInitDir;          // +0x60
    RwV3d prtInitDirBias;      // +0x6c
    RwV2d prtSize;             // +0x78
    RwRGBA prtColor;           // +0x80
    RwReal prtDelta2DRotate;   // +0x84
    RwReal prtUV[8];           // +0x88 four (u, v) pairs
    RwTexture* texture;        // +0xa8
    RwMatrix* ltm;             // +0xac the atomic's frame LTM (the update-time callback sets it)
    int32_t unkB0;             // +0xb0 read from the stream
};
DOTD_ASSERT_SIZE(RpPrtStdEmitterStandard, 0xb4);
DOTD_ASSERT_OFFSET(RpPrtStdEmitterStandard, prtColor, 0x80);
DOTD_ASSERT_OFFSET(RpPrtStdEmitterStandard, texture, 0xa8);

// Property 6, the PTank property (rpprtstd.h RpPrtStdEmitterPTank; PS3 size 0x34, pointers at +0x18..+0x24).
// The data pointer arrays hold one entry per PTank array the lock got, in data-flag order (position 0x1,
// colour 0x2, size 0x4, matrix 0x8, normal 0x10, 2D rotation 0x20, vertex colours 0x40, 2 / 4 tex coords).
struct RpPrtStdEmitterPTank {
    uint32_t dataFlags;     // +0x00 the arrays locked (RW_LockParticleTankProperties_maybe)
    uint32_t platFlags;     // +0x04
    int32_t numPrt;         // +0x08 particles written this frame
    int32_t maxPrt;         // +0x0c the PTank's capacity
    uint32_t updateFlags;   // +0x10 rpPTANKDFLAG* the update writes (stream: the raw bytes, see PTankStreamRead)
    uint32_t emitFlags;     // +0x14 rpPTANKDFLAG* the emit writes
    RpAtomic* pTank;        // +0x18
    uint8_t** dataInPtrs;   // +0x1c
    uint8_t** dataOutPtrs;  // +0x20
    int32_t* dataStride;    // +0x24
    uint32_t strSrcBlend;   // +0x28
    uint32_t strDstBlend;   // +0x2c
    int32_t strVtxABlend;   // +0x30
};
DOTD_ASSERT_SIZE(RpPrtStdEmitterPTank, 0x34);
DOTD_ASSERT_OFFSET(RpPrtStdEmitterPTank, pTank, 0x18);
DOTD_ASSERT_OFFSET(RpPrtStdEmitterPTank, strSrcBlend, 0x28);

namespace rpprtstd {

// RW_CacheParticlePropertyOffsets (0x72a538): the property offsets of the last emitter / particle class
// seen, -1 when absent (RpPrtStd globals 0x00cfbb04..0x00cfbb64).
struct CachedOffsets {
    const RpPrtStdPropertyTable* emitterTable;   // 0x00cfbb04
    const RpPrtStdPropertyTable* particleTable;  // 0x00cfbb08
    int32_t emtStd;        // 0x00cfbb0c emitter property 1
    int32_t emtPrtColor;   // 0x00cfbb10 2
    int32_t emtPrtTexCoords;  // 0x00cfbb14 3
    int32_t emtPrtSize;    // 0x00cfbb18 5
    int32_t emtPTank;      // 0x00cfbb1c 6
    int32_t emtPrtMatrix;  // 0x00cfbb20 8
    int32_t emtPrt2DRotate;   // 0x00cfbb24 4
    int32_t prtPosition;   // 0x00cfbb28 particle property 1
    int32_t prtStd;        // 0x00cfbb2c 0
    int32_t prtColor;      // 0x00cfbb30 2
    int32_t prtTexCoords;  // 0x00cfbb34 3
    int32_t prtSize;       // 0x00cfbb38 5
    int32_t prtVelocity;   // 0x00cfbb3c 6
    int32_t prtMatrix;     // 0x00cfbb40 7
    int32_t prt2DRotate;   // 0x00cfbb44 4
    int32_t prtPositionIndex;   // 0x00cfbb48 the property indices (RpPrtStdPropTabGetPropIndex)
    int32_t prtStdIndex;        // 0x00cfbb4c
    int32_t prtColorIndex;      // 0x00cfbb50
    int32_t prtTexCoordsIndex;  // 0x00cfbb54
    int32_t prtSizeIndex;       // 0x00cfbb58
    int32_t prtVelocityIndex;   // 0x00cfbb5c
    int32_t prtMatrixIndex;     // 0x00cfbb60
    int32_t prt2DRotateIndex;   // 0x00cfbb64
};
// DEV (thread safety, not in the original): the PS3 keeps one cache, which the sector load worker (its FX PostLoads
// update emitters) and the main thread's particle update share; natively the threads race on it (the main thread read
// the worker's offsets: a crash in StdParticleUpdate while G streams sector 2 in). Each thread keeps its own copy. A
// property table's destroy clears it in every thread: PropTabDestroy bumps g_propTabDestroyGeneration and each copy
// forgets its tables when it sees a new generation (the offsets are looked up again: the same values).
extern thread_local CachedOffsets g_offsets;
extern std::atomic<uint32_t> g_propTabDestroyGeneration;
// 0x0072a538 RW_CacheParticlePropertyOffsets
RpPrtStdEmitter* CacheParticlePropertyOffsets(RpPrtStdEmitter* emitter);

// RW_CacheParticlePropertyOffsets2_maybe (0x6f00d8, RpPrtAdv's copy): RpPrtAdv globals 0x00cf9e10..0x00cf9ebc.
struct AdvCachedOffsets {
    const RpPrtStdPropertyTable* emitterTable;   // 0x00cf9e10
    const RpPrtStdPropertyTable* particleTable;  // 0x00cf9e14
    int32_t emtStd;            // 0x00cf9e1c 1
    int32_t emtPrtColor;       // 0x00cf9e20 2
    int32_t emtPrtTexCoords;   // 0x00cf9e24 3
    int32_t emtPrtSize;        // 0x00cf9e28 5
    int32_t emtPTank;          // 0x00cf9e2c 6
    int32_t emtAdv0;           // 0x00cf9e34 0x1000000
    int32_t emtPrtEmitter;     // 0x00cf9e38 0x1000001
    int32_t emtMultiColor;     // 0x00cf9e40 0x1000002
    int32_t emtMultiTexCoords; // 0x00cf9e44 0x1000003
    int32_t emtMultiTexCoordsStep;  // 0x00cf9e48 0x1000004
    int32_t emtMultiSize;      // 0x00cf9e4c 0x1000005
    int32_t emtPointList;      // 0x00cf9e84 0x1000006
    int32_t emtCircle;         // 0x00cf9e88 0x1000007
    int32_t emtSphere;         // 0x00cf9e8c 0x1000008
    int32_t prtPosition;       // 0x00cf9e50 particle 1
    int32_t prtStd;            // 0x00cf9e54 0
    int32_t prtColor;          // 0x00cf9e58 2
    int32_t prtTexCoords;      // 0x00cf9e5c 3
    int32_t prtSize;           // 0x00cf9e60 5
    int32_t prtVelocity;       // 0x00cf9e64 6
    int32_t prtAdv0;           // 0x00cf9e6c 0x1000000
    int32_t prtPrtEmitter;     // 0x00cf9e70 0x1000001
    int32_t prtMultiColor;     // 0x00cf9e74 0x1000002
    int32_t prtMultiTexCoords; // 0x00cf9e78 0x1000003
    int32_t prtMultiTexCoordsStep;  // 0x00cf9e7c 0x1000004
    int32_t prtMultiSize;      // 0x00cf9e80 0x1000005
    int32_t prtPositionIndex;  // 0x00cf9e90
    int32_t prtStdIndex;       // 0x00cf9e94
    int32_t prtColorIndex;     // 0x00cf9e98
    int32_t prtTexCoordsIndex; // 0x00cf9e9c
    int32_t prtSizeIndex;      // 0x00cf9ea0
    int32_t prtVelocityIndex;  // 0x00cf9ea4
    int32_t prtAdv0Index;      // 0x00cf9eac
    int32_t prtPrtEmitterIndex;  // 0x00cf9eb0
    int32_t prtMultiColorIndex;  // 0x00cf9eb4
    int32_t prtMultiTexCoordsIndex;  // 0x00cf9eb8
    int32_t prtMultiSizeIndex;   // 0x00cf9ebc
    // The 0x1000001 update's own cache (0x6f3348): its sub-emitter's property table and that table's
    // standard property (1) offset. The destroy hook (0x6ef3b0) does not clear them.
    const RpPrtStdPropertyTable* subEmitterTable;  // 0x00cf9e18
    int32_t subEmtStd;                             // 0x00cf9e3c
};
extern thread_local AdvCachedOffsets g_advOffsets;  // per thread, as g_offsets
// 0x006f00d8 RW_CacheParticlePropertyOffsets2_maybe
RpPrtStdEmitter* CacheAdvPropertyOffsets(RpPrtStdEmitter* emitter);

// The emitter's random numbers (inlined everywhere): seed = seed * 0xbb38435 + 0x3619636b, the result the
// new seed as an unsigned float times 2^-32 (TOC 2.3283064e-10).
inline uint32_t NextSeed(int32_t* seed) {
    const uint32_t next = static_cast<uint32_t>(*seed) * 0xbb38435u + 0x3619636bu;
    *seed = static_cast<int32_t>(next);
    return next;
}

// 0x0072c3e0 RpPrtStdEmitterNewParticleBatch_maybe: a batch from the inactive ring (or a new one), put on
// the active ring; its create callbacks run. Null when the allocation fails.
RpPrtStdParticleBatch* EmitterNewParticleBatch(RpPrtStdEmitter* emitter);
// 0x0072e0d8 RW_LockParticleTankProperties_maybe: every array of the PTank locked into the in/out pointers
// and strides; dataFlags = the arrays locked.
RpPrtStdEmitterPTank* LockParticleTankProperties(RpPrtStdEmitterPTank* ptank);
// 0x0072b3a0 RpPrtStdEmitterUpdate_maybe: one emitter updated and emitting in one pass (RpPrtStdRuntime.cpp).
RpPrtStdEmitter* EmitterUpdate(RpAtomic* atomic, RpPrtStdEmitter* emitter, float* deltaTime);

// The emitter class callbacks ported in the other files.
RpPrtStdEmitter* StdEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);            // 0x732c58 RpPrtStdEmit.cpp
RpPrtStdEmitter* StdUpdateTime(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);      // 0x7310e0
RpPrtStdEmitter* StdScheduleEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);    // 0x7311b8
RpPrtStdEmitter* StdRenderPTank(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);     // 0x731360
RpPrtStdEmitter* PointListEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);      // 0x6f26c8 RpPrtAdv.cpp
RpPrtStdEmitter* MultiEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);          // 0x6f41b0 RpPrtAdv.cpp
RpPrtStdEmitter* SphereEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);         // 0x6f1110 RpPrtAdvRuntime.cpp
RpPrtStdEmitter* CircleEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);         // 0x6f1a00
RpPrtStdEmitter* PrtEmitterEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);     // 0x6f31b8
RpPrtStdEmitter* TexCoordsStepEmit(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);  // 0x6f5898
// The particle class callbacks.
RpPrtStdParticleBatch* StdParticleUpdate(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch, void* data);   // 0x734188 RpPrtStdUpdate.cpp
RpPrtStdParticleBatch* KeyFramesUpdate(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch, void* data);     // 0x6f50e0 RpPrtAdv.cpp
RpPrtStdParticleBatch* TexCoordStepUpdate(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch, void* data);  // 0x6f5df0
RpPrtStdParticleBatch* PrtEmitterUpdate(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch, void* data);    // 0x6f3348 RpPrtAdvRuntime.cpp

// 0x006ef410 RpPrtStdPClass_BuildStdCallBackArray_maybe (RpPrtAdv.cpp): the particle class setup callback.
RpPrtStdParticleClass* PClassBuildCallBackArray(RpPrtStdParticleClass* pClass);
// 0x0072d508 RpPrtStdPClassSetCallBackArray_maybe (RpPrtStd.cpp)
void PClassSetCallBackArray(RpPrtStdParticleClass* pClass, int32_t count, const RpPrtStdParticleCallBackArray* arrays);

}  // namespace rpprtstd
