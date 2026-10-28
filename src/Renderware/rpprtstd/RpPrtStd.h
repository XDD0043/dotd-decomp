// RpPrtStd.h - the RenderWare 3.7 standard particle plugin (RpPrtStd) and the advanced emitter properties
// (RpPrtAdv: point list, multi colour/texcoords/size, ...), as far as loading and the front end need them:
// the plugin stream of a particle atomic (chunk 0x130 in the atomic's extension), the property tables,
// the emitter and particle classes, the emitters with their property data, and their clones.
//
// No C source of these plugins ships with the RW 3.7 sources (only misc/inc/rpprtstd.h and rpprtadv.h), so
// this is ported from the PS3 library code (TOC 0xc25974): RpPrtStd 0x729798-0x735xxx, RpPrtAdv
// 0x6ef3b0-0x6f5df0. Field names after rpprtstd.h / rpprtadv.h where the PS3 layout matches them; DotD's
// property table puts its fields in another order than the header.
//
// Native layout: the emitter is one block (its emitter class's object size) holding every property at the
// offset its property table gives, the PS3 byte layout inside each property (words as native values).
// Properties with pointers: the emitter header (property 0) and the point list (0x1000006) are native
// structs, their table sizes grown by the native pointer size (the growth is 0 in 32-bit builds, where the
// offsets are the PS3's); the other properties' self pointers (multi colour etc.: their keyframes follow
// them) are only stored in 32-bit builds, the readers use the fixed positions instead.
//
// The running side (emitting, updating, rendering, the PTank property) is in RpPrtStdRuntime.h/.cpp and the
// files it names. STUB(C2): stream writing, destruction.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwTypes.h"

struct RpAtomic;
struct RpPrtStdEmitter;
struct RpPrtStdParticleCallBackArray;

// Property codes (rpprtstd.h, rpprtadv.h).
enum : int32_t {
    rpPRTSTDPROPERTYCODEEMITTER = 0,
    rpPRTSTDPROPERTYCODEEMITTERSTANDARD = 1,
    rpPRTSTDPROPERTYCODEEMITTERPRTCOLOR = 2,
    rpPRTSTDPROPERTYCODEEMITTERPRTTEXCOORDS = 3,
    rpPRTSTDPROPERTYCODEEMITTERPRT2DROTATE = 4,
    rpPRTSTDPROPERTYCODEEMITTERPRTSIZE = 5,
    rpPRTSTDPROPERTYCODEEMITTERPTANK = 6,
    rpPRTSTDPROPERTYCODEEMITTERPRTMATRIX = 8,
    rpPRTADVPROPERTYCODEEMITTERPRTEMITTER = 0x1000001,
    rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR = 0x1000002,
    rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS = 0x1000003,
    rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP = 0x1000004,
    rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE = 0x1000005,
    rpPRTADVPROPERTYCODEEMITTERPOINTLIST = 0x1000006,
    rpPRTADVPROPERTYCODEEMITTERCIRCLE = 0x1000007,
    rpPRTADVPROPERTYCODEEMITTERSPHERE = 0x1000008,
};

// rpPRTSTDEMITTERFLAG* (rpprtstd.h).
enum : uint32_t {
    rpPRTSTDEMITTERFLAGALIVE = 0x1,
    rpPRTSTDEMITTERFLAGACTIVE = 0x2,
    rpPRTSTDEMITTERFLAGPTANK = 0x4,
    rpPRTSTDEMITTERFLAGEMIT = 0x8,
    rpPRTSTDEMITTERFLAGSTREAMREAD = 0x200,
};

// A property table (PS3 order; 0x28 bytes, the arrays follow it in the same allocation).
struct RpPrtStdPropertyTable {
    int32_t* propPtr;               // +0x00 the allocation (the table is 16-byte aligned inside it)
    RpPrtStdPropertyTable* next;    // +0x04 circular list of every table (0x00cfbadc)
    int32_t id;                     // +0x08 the stream's id (a hash of the ids until then)
    int32_t refCount;               // +0x0c
    int32_t numProp;                // +0x10
    int32_t maxProp;                // +0x14 never written
    int32_t* propID;                // +0x18
    int32_t* propOffset;            // +0x1c numProp + 1 entries: the last is the object size
    int32_t* propSize;              // +0x20 the sizes rounded up to 16 (natively: plus the pointer growth)
    int32_t* propSizeUA;            // +0x24 the stream's sizes
};

// RpPrtStdEmitterCallBack: (atomic, emitter, data). The PS3 arrays hold 11 slots (0x2c bytes); the slots
// as the builder (0x6ef7c8) fills them: 0 emit, 1 update time, 2 schedule emit, 3 render (PTank), 5 create
// (init), 6 destroy, 7 stream read, 8 stream write, 9 stream size, 10 clone (copy into `data`).
typedef RpPrtStdEmitter* (*RpPrtStdEmitterCallBack)(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data);
enum : int32_t {
    rpPRTSTDEMITTERCALLBACKEMIT = 0,
    rpPRTSTDEMITTERCALLBACKCREATE = 5,
    rpPRTSTDEMITTERCALLBACKDESTROY = 6,
    rpPRTSTDEMITTERCALLBACKSTREAMREAD = 7,
    rpPRTSTDEMITTERCALLBACKCLONE = 10,
    rpPRTSTDEMITTERCALLBACKMAX = 11,
};
struct RpPrtStdEmitterCallBackArray {
    RpPrtStdEmitterCallBack callback[rpPRTSTDEMITTERCALLBACKMAX];
};

struct RpPrtStdEmitterClass {
    RpPrtStdEmitterClass* next;              // +0x00 circular list (0x00cfbad4)
    int32_t id;                              // +0x04 the data flags (rpPRTSTDEMITTERDATAFLAG*, adv bits)
    int32_t refCount;                        // +0x08
    int32_t objSize;                         // +0x0c the sum of the table's (rounded) sizes
    RpPrtStdPropertyTable* propTab;          // +0x10
    int32_t numCallback;                     // +0x14
    RpPrtStdEmitterCallBackArray* callback;  // +0x18
};

struct RpPrtStdParticleClass {
    RpPrtStdParticleClass* next;     // +0x00 circular list (0x00cfbad8)
    int32_t id;                      // +0x04
    int32_t refCount;                // +0x08
    int32_t objSize;                 // +0x0c
    RpPrtStdPropertyTable* propTab;  // +0x10
    int32_t numCallback;             // +0x14
    RpPrtStdParticleCallBackArray* callback;  // +0x18 (RpPrtStdRuntime.h)
};

// Property 0: the emitter (rpprtstd.h order and PS3 offsets).
struct RpPrtStdEmitter {
    RpPrtStdEmitter* next;            // +0x00 circular list of the atomic's emitters
    uint32_t flag;                    // +0x04 rpPRTSTDEMITTERFLAG*
    RpAtomic* atomic;                 // +0x08
    RpPrtStdEmitterClass* emtClass;   // +0x0c
    int32_t prtActive;                // +0x10
    int32_t prtBatchMaxPrt;           // +0x14
    RpPrtStdParticleClass* prtClass;  // +0x18
    void* inactiveBatch;              // +0x1c
    void* activeBatch;                // +0x20
    RwReal boundingSphere;            // +0x24
};
DOTD_ASSERT_SIZE(RpPrtStdEmitter, 0x28);

// 0x1000006 (rpprtadv.h RpPrtAdvEmtPointList), followed in the property by the points and the directions
// (the property's size gives their capacity: 64 in DotD's data).
struct RpPrtAdvEmtPointList {
    RwUInt32 numPoint;      // +0x00
    RwUInt32 lastPoint;     // +0x04
    RwBool useDirection;    // +0x08
    RwBool random;          // +0x0c
    RwV3d* pointList;       // +0x10
    RwV3d* directionList;   // +0x14
};
DOTD_ASSERT_SIZE(RpPrtAdvEmtPointList, 0x18);

// 0x0072ee88 RW_GetParticlePropertyOffset (RpPrtStdPropTabGetPropOffset): -1 when absent.
int32_t RpPrtStdPropTabGetPropOffset(const RpPrtStdPropertyTable* table, int32_t propID);
// 0x0072ee20 RpPrtStdPropTabGetPropIndex: -1 when absent.
int32_t RpPrtStdPropTabGetPropIndex(const RpPrtStdPropertyTable* table, int32_t propID);
// The property `propID` of an emitter (emitter + its class's offset), or null.
void* RpPrtStdEmitterGetProperty(RpPrtStdEmitter* emitter, int32_t propID);

// 0x0072fca8 RpPrtStdAtomicGetEmitter_maybe: the atomic's emitter list (the last emitter added), or null.
RpPrtStdEmitter* RpPrtStdAtomicGetEmitter(RpAtomic* atomic);
// 0x007301e0 RpPrtStdAtomicStreamRead_maybe on the plugin chunk's payload (`data`, `length` bytes; the
// game's readers may read past the chunk, the caller passes what follows it too). The bytes used.
uint32_t RpPrtStdAtomicStreamRead(RpAtomic* atomic, const uint8_t* data, uint32_t length);
// 0x00730298 RpPrtStdAtomicPlugin_Copy_maybe (RpAtomicClone's plugin copy): every emitter cloned onto `dst`.
void RpPrtStdAtomicCopy(RpAtomic* dst, const RpAtomic* src);

// 0x00730cb8 RW_UpdateParticleAtomic / 0x00730990 RW_EmitParticleAtomic (RpPrtStdRuntime.cpp): every emitter
// updated / emitting with `deltaTime`; null when one fails or the atomic has no emitters.
RpAtomic* RpPrtStdAtomicUpdate(RpAtomic* atomic, float* deltaTime);
RpAtomic* RpPrtStdAtomicEmit(RpAtomic* atomic, float* deltaTime);
// 0x00730e10 RW_UpdateParticleAtomic_2: update and emit in one pass per emitter (the first frame a particle
// node is drawn, with the emit gap as the time).
RpAtomic* RpPrtStdAtomicUpdateAndEmit(RpAtomic* atomic, float* deltaTime);
// 0x00730ba8 RW_RenderParticleAtomic: the render callback of atomics with emitters.
RpAtomic* RpPrtStdAtomicRender(RpAtomic* atomic);

// DEV (tests): what the loads made of the plugin data. Emitters read from atomic streams (bad: without
// STREAMREAD, atomic or classes); particle nodes bound by CParticlesNodeFx_PostLoad (bad: a point list
// outside its emitter or its points not right after it).
struct RpPrtStdShimStats {
    uint32_t emittersRead;
    uint32_t badEmitters;
    uint32_t nodesBound;
    uint32_t nodesWithPointList;
    uint32_t badNodes;
    uint32_t streamsRead;           // plugin chunks read
    uint32_t streamLengthMismatches;  // reads that did not end 8 bytes past the chunk (see RpAtomic.cpp)
};
RpPrtStdShimStats RpPrtStdShim_Stats();
void RpPrtStdShim_NoteStreamRead(uint32_t bytesRead, uint32_t chunkLength);
void RpPrtStdShim_NoteBoundNode(const RpPrtStdEmitter* emitter, const RpPrtAdvEmtPointList* pointList);
