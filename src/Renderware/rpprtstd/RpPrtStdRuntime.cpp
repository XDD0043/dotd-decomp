// RpPrtStdRuntime.cpp - the RpPrtStd plugin's running side: the atomic and emitter loops (update, emit,
// render), the property offset cache, particle batches, the PTank property (creating, binding and locking
// the emitter's PTank atomic) and the standard emitter's small callbacks. Ported from the PS3 library code
// (TOC 0xc25974). See RpPrtStdRuntime.h.
//
//   [x] 0x72a538  RW_CacheParticlePropertyOffsets
//   [x] 0x72a7d8  RW_RenderParticleEmitter
//   [x] 0x72ae28  RW_EmitParticleEmitter
//   [x] 0x72b3a0  RpPrtStdEmitterUpdate_maybe
//   [x] 0x72ba60  RW_UpdateParticleEmitter
//   [x] 0x72c3e0  RpPrtStdEmitterNewParticleBatch_maybe
//   [x] 0x72d508  RpPrtStdPClassSetCallBackArray_maybe
//   [x] 0x72e0d8  RW_LockParticleTankProperties_maybe
//   [x] 0x72e3b0  RpPrtStdEmitter_SetPTankAtomic_maybe
//   [x] 0x72e5a8  RpPrtStdEmitter_CreatePTank_maybe
//   [x] 0x730990  RW_EmitParticleAtomic
//   [x] 0x730ba8  RW_RenderParticleAtomic
//   [x] 0x730cb8  RW_UpdateParticleAtomic
//   [x] 0x730e10  RW_UpdateParticleAtomic_2
//   [x] 0x7310e0  _rpPrtStdEmitterStdUpdateTimeCB_maybe
//   [x] 0x7311b8  _rpPrtStdEmitterStdScheduleEmitCB_maybe
//   [x] 0x731360  RW_RenderEmitterParticleTank
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"

#include <cstdlib>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStdInternal.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

namespace rpprtstd {

CachedOffsets g_offsets = {};

// 0x0072a538 RW_CacheParticlePropertyOffsets: the offsets are looked up again only when the emitter's or
// the particle's property table differs from the last one.
RpPrtStdEmitter* CacheParticlePropertyOffsets(RpPrtStdEmitter* emitter) {
    const RpPrtStdPropertyTable* eTable = emitter->emtClass->propTab;
    if (g_offsets.emitterTable != eTable) {
        g_offsets.emitterTable = eTable;
        g_offsets.emtStd = RpPrtStdPropTabGetPropOffset(eTable, 1);
        g_offsets.emtPrtColor = RpPrtStdPropTabGetPropOffset(eTable, 2);
        g_offsets.emtPrtTexCoords = RpPrtStdPropTabGetPropOffset(eTable, 3);
        g_offsets.emtPrtSize = RpPrtStdPropTabGetPropOffset(eTable, 5);
        g_offsets.emtPTank = RpPrtStdPropTabGetPropOffset(eTable, 6);
        g_offsets.emtPrtMatrix = RpPrtStdPropTabGetPropOffset(eTable, 8);
        g_offsets.emtPrt2DRotate = RpPrtStdPropTabGetPropOffset(eTable, 4);
    }
    const RpPrtStdPropertyTable* pTable = emitter->prtClass->propTab;
    if (g_offsets.particleTable != pTable) {
        g_offsets.particleTable = pTable;
        g_offsets.prtStd = RpPrtStdPropTabGetPropOffset(pTable, 0);
        g_offsets.prtColor = RpPrtStdPropTabGetPropOffset(pTable, 2);
        g_offsets.prtTexCoords = RpPrtStdPropTabGetPropOffset(pTable, 3);
        g_offsets.prtSize = RpPrtStdPropTabGetPropOffset(pTable, 5);
        g_offsets.prtPosition = RpPrtStdPropTabGetPropOffset(pTable, 1);
        g_offsets.prtVelocity = RpPrtStdPropTabGetPropOffset(pTable, 6);
        g_offsets.prtMatrix = RpPrtStdPropTabGetPropOffset(pTable, 7);
        g_offsets.prt2DRotate = RpPrtStdPropTabGetPropOffset(pTable, 4);
        g_offsets.prtStdIndex = RpPrtStdPropTabGetPropIndex(pTable, 0);
        g_offsets.prtColorIndex = RpPrtStdPropTabGetPropIndex(pTable, 2);
        g_offsets.prtTexCoordsIndex = RpPrtStdPropTabGetPropIndex(pTable, 3);
        g_offsets.prtSizeIndex = RpPrtStdPropTabGetPropIndex(pTable, 5);
        g_offsets.prtPositionIndex = RpPrtStdPropTabGetPropIndex(pTable, 1);
        g_offsets.prtVelocityIndex = RpPrtStdPropTabGetPropIndex(pTable, 6);
        g_offsets.prtMatrixIndex = RpPrtStdPropTabGetPropIndex(pTable, 7);
        g_offsets.prt2DRotateIndex = RpPrtStdPropTabGetPropIndex(pTable, 4);
    }
    return emitter;
}

namespace {

// The batch create callbacks (particle slot 2) with (null, batch, null), stopping at the first that does
// not return the batch (RpPrtStdParticleBatchInit_maybe 0x72a108 and the two inlined copies).
void RunBatchCreateCallBacks(RpPrtStdParticleClass* pClass, RpPrtStdParticleBatch* batch) {
    for (int32_t i = 0; i < pClass->numCallback; ++i) {
        RpPrtStdParticleCallBack create = pClass->callback[i].callback[rpPRTSTDPARTICLECALLBACKCREATE];
        if (create != nullptr && create(nullptr, batch, nullptr) != batch) break;
    }
}

}  // namespace

// 0x0072c3e0 RpPrtStdEmitterNewParticleBatch_maybe. A new batch is one RW allocation (Engine +0x108,
// memory hint 0x30130) of maxPrt * the particle size + 0x20, not cleared.
RpPrtStdParticleBatch* EmitterNewParticleBatch(RpPrtStdEmitter* emitter) {
    RpPrtStdParticleBatch* inactive = static_cast<RpPrtStdParticleBatch*>(emitter->inactiveBatch);
    RpPrtStdParticleBatch* batch;
    if (inactive == nullptr) {
        RpPrtStdParticleClass* pClass = emitter->prtClass;
        const int32_t maxPrt = emitter->prtBatchMaxPrt;
        batch = static_cast<RpPrtStdParticleBatch*>(std::malloc(static_cast<size_t>(maxPrt * pClass->objSize + 0x20)));
        if (batch == nullptr) return nullptr;
        batch->maxPrt = maxPrt;
        batch->prtClass = pClass;
        batch->offset = 0x20;
        batch->newPrt = 0;
        batch->next = batch;
        batch->numPrt = 0;
        RunBatchCreateCallBacks(pClass, batch);
    } else {
        batch = inactive->next;
        if (inactive == batch) {
            emitter->inactiveBatch = nullptr;
        } else {
            inactive->next = batch->next;
        }
        batch->next = batch;
        batch->newPrt = 0;
        batch->numPrt = 0;
        RunBatchCreateCallBacks(batch->prtClass, batch);
    }
    RpPrtStdParticleBatch* active = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
    if (active == nullptr) {
        batch->next = batch;
    } else {
        batch->next = active->next;
        active->next = batch;
    }
    emitter->activeBatch = batch;
    return batch;
}

// 0x0072e0d8 RW_LockParticleTankProperties_maybe: every array of the PTank (as many as its property table
// counts, in data-flag order), locked with rpPTANKLFLAGWRITE (0x40000000).
RpPrtStdEmitterPTank* LockParticleTankProperties(RpPrtStdEmitterPTank* ptank) {
    const RpPTankPropertyTable* table = RpPTankAtomicGetPropertyTable(ptank->pTank);
    ptank->dataFlags = 0;
    int32_t locked = 0;
    uint32_t flag = 1;
    while (locked < table->numProp) {
        RpPTankLockStruct lock;
        if (RpPTankAtomicLock(ptank->pTank, &lock, flag, 0x40000000u) != 0) {
            ptank->dataInPtrs[locked] = lock.data;
            ptank->dataOutPtrs[locked] = lock.data;
            ptank->dataStride[locked] = lock.stride;
            ++locked;
            ptank->dataFlags |= flag;
        }
        flag <<= 1;
    }
    return ptank;
}

namespace {

// The PTank property's pointer arrays (in, out, stride; one entry per PTank property), one RW allocation
// (Engine +0x108 / +0x10c), the previous one freed (RpPrtStdEmitter_AllocPTankBuffers_maybe 0x72de50 and
// its inlined copies).
void AllocPTankBuffers(RpPrtStdEmitterPTank* ptank) {
    if (ptank->dataInPtrs != nullptr) {
        std::free(ptank->dataInPtrs);
        std::free(ptank->dataOutPtrs);
        std::free(ptank->dataStride);
    }
    ptank->dataStride = nullptr;
    ptank->dataInPtrs = nullptr;
    ptank->dataOutPtrs = nullptr;
    if (ptank->pTank == nullptr) return;
    const int32_t count = RpPTankAtomicGetPropertyTable(ptank->pTank)->numProp;
    // Natively three blocks (the PS3: one of count * 12 bytes, split in three).
    ptank->dataInPtrs = static_cast<uint8_t**>(std::calloc(static_cast<size_t>(count) + 1, sizeof(uint8_t*)));
    ptank->dataOutPtrs = static_cast<uint8_t**>(std::calloc(static_cast<size_t>(count) + 1, sizeof(uint8_t*)));
    ptank->dataStride = static_cast<int32_t*>(std::calloc(static_cast<size_t>(count) + 1, sizeof(int32_t)));
}

// 0x0072e3b0 RpPrtStdEmitter_SetPTankAtomic_maybe: only when the property has no PTank yet: the PTank's
// capacity and data flags, its count changed (flag 0x800000) and cleared, the pointer arrays.
RpPrtStdEmitter* SetPTankAtomic(RpPrtStdEmitter* emitter, RpAtomic* pTank) {
    RpPrtStdEmitterPTank* ptank =
        reinterpret_cast<RpPrtStdEmitterPTank*>(PropertyAt(emitter, EmitterPropOffset(emitter, 6)));
    if (ptank->pTank != nullptr) return nullptr;
    RpPTankData* data = pTank->ptank;
    ptank->pTank = pTank;
    ptank->maxPrt = static_cast<int32_t>(data->maxParticles);
    ptank->dataFlags = RpPTankAtomicGetPropertyTable(pTank)->dataFlags;
    ptank->platFlags = 0;
    ptank->numPrt = 0;
    data->flags40 |= 0x800000u;
    data->numPrt = 0;
    AllocPTankBuffers(ptank);
    return ptank->dataInPtrs != nullptr ? emitter : nullptr;
}

// 0x0072e5a8 RpPrtStdEmitter_CreatePTank_maybe: with a PTank already bound only the pointer arrays are
// made again. Otherwise the PTank's data flags from the emitter's properties (a matrix or a position, colour,
// tex coords per particle or constant, size, 2D rotation per particle or a constant rotation when the
// standard rotation speed is beyond +/-1e-5), the PTank (RpPTankAtomicCreate with the standard property's
// maxPrt) on an identity frame, its constants from the standard property (colour, size, tex coords,
// texture), bound, with the property's blend modes and vertex alpha.
RpPrtStdEmitter* CreatePTank(RpPrtStdEmitter* emitter) {
    RpPrtStdEmitterPTank* ptank =
        reinterpret_cast<RpPrtStdEmitterPTank*>(PropertyAt(emitter, EmitterPropOffset(emitter, 6)));
    if (ptank->pTank != nullptr) {
        if (ptank->dataInPtrs == nullptr) return emitter;
        AllocPTankBuffers(ptank);
        return emitter;
    }
    RpPrtStdEmitterStandard* std = nullptr;
    const int32_t stdOffset = EmitterPropOffset(emitter, 1);
    if (stdOffset >= 0) std = reinterpret_cast<RpPrtStdEmitterStandard*>(PropertyAt(emitter, stdOffset));
    const int32_t matrixOffset = EmitterPropOffset(emitter, 8);
    const int32_t colorOffset = EmitterPropOffset(emitter, 2);
    uint32_t flags = matrixOffset < 0 ? 0x1u : 0x8u;  // ((offset >> 31) & 0xfffffff9) + 8
    if (colorOffset >= 0) flags |= 0x2;
    // BUG(original): without a standard property `std` is null and read anyway (every DotD class has one).
    if (std->texture != nullptr) {
        flags |= EmitterPropOffset(emitter, 3) < 0 ? 0x80000u : 0x80u;
    }
    if (EmitterPropOffset(emitter, 5) >= 0) {
        if ((flags & 1) == 0) {
            ptank->updateFlags &= 0xfffdffffu;
            goto create;
        }
        flags |= 0x4;
    }
    ptank->updateFlags &= 0xfffdffffu;
    if ((flags & 1) != 0) {
        if (EmitterPropOffset(emitter, 4) < 0) {
            if (1.0e-5f < std->prtDelta2DRotate || std->prtDelta2DRotate < -1.0e-5f) {
                flags |= 0x20000;
                ptank->updateFlags |= 0x20000;
            }
        } else {
            flags |= 0x20;
        }
    }
create:
    RpAtomic* pTank = RpPTankAtomicCreate(static_cast<uint32_t>(std->maxPrt), flags, ptank->platFlags);
    if (pTank == nullptr) return nullptr;
    // RwFrameCreate, its modelling matrix set to the identity inline (type flags 0x20003), RpAtomicSetFrame.
    RwFrame* frame = RwFrameCreate();
    RwMatrixSetIdentity(&frame->modelling);
    frame->modelling.flags |= 0x20003;
    pTank->frame = frame;
    RpPTankData* data = pTank->ptank;
    const uint32_t minusZero = 0x80000000u;  // TOC -0x3728
    std::memcpy(&data->wordB8, &minusZero, 4);
    std::memcpy(&data->wordBC, &minusZero, 4);
    data->flags40 |= 0x1000000u;
    if ((flags & 2) == 0) {
        data->colorCC[0] = std->prtColor.red;
        data->colorCC[1] = std->prtColor.green;
        data->colorCC[2] = std->prtColor.blue;
        data->colorCC[3] = std->prtColor.alpha;
        // The PTank material's colour (RpMaterial +4) follows.
        std::memcpy(data->materialColor, data->colorCC, 4);
        data->flags40 |= 0x2000u;
    }
    if ((flags & 0x80000) != 0) {
        std::memcpy(data->texCoordsE0, std->prtUV, 16);
        data->flags40 |= 0x80000u;
    }
    if ((flags & 4) == 0) {
        std::memcpy(data->renderC0, &std->prtSize, 8);
        data->flags40 |= 0x4000u;
    }
    if (std->texture != nullptr) pTank->texture = std->texture;  // RpMaterialSetTexture (the PTank's material)
    const uint32_t platFlags = ptank->platFlags;
    if (SetPTankAtomic(emitter, pTank) == nullptr) return nullptr;
    ptank->platFlags = platFlags;
    data->renderAC = ptank->strSrcBlend;
    data->renderB0 = ptank->strDstBlend;
    data->flags40 |= 0x10000000u;
    data->renderB4 = static_cast<uint32_t>(ptank->strVtxABlend);
    return emitter;
}

// The emitter class callbacks of one slot, in array order, with (atomic, emitter, data); false when one
// does not return the emitter. `stopAtNull`: the loops that end at the first empty slot (the packed arrays
// keep a slot's callbacks first, so both forms run the same callbacks).
bool RunEmitterCallBacks(RpPrtStdEmitterClass* eClass, int32_t slot, RpAtomic* atomic, RpPrtStdEmitter* emitter,
                         void* data, bool stopAtNull = false) {
    for (int32_t i = 0; i < eClass->numCallback; ++i) {
        RpPrtStdEmitterCallBack callback = eClass->callback[i].callback[slot];
        if (callback == nullptr) {
            if (stopAtNull) break;
            continue;
        }
        if (callback(atomic, emitter, data) != emitter) return false;
    }
    return true;
}

// The particle class callbacks of one slot on a batch; false when one does not return the batch.
bool RunParticleCallBacks(RpPrtStdParticleClass* pClass, int32_t slot, RpPrtStdEmitter* emitter,
                          RpPrtStdParticleBatch* batch, void* data, bool stopAtNull) {
    for (int32_t i = 0; i < pClass->numCallback; ++i) {
        RpPrtStdParticleCallBack callback = pClass->callback[i].callback[slot];
        if (callback == nullptr) {
            if (stopAtNull) break;
            continue;
        }
        if (callback(emitter, batch, data) != batch) return false;
    }
    return true;
}

// The PTank property when the emitter has the PTank flag (4): created on first use; null without the flag,
// and `failed` set when the creation fails.
RpPrtStdEmitterPTank* EmitterPTank(RpPrtStdEmitter* emitter, bool* failed) {
    *failed = false;
    if ((emitter->flag & rpPRTSTDEMITTERFLAGPTANK) == 0) return nullptr;
    RpPrtStdEmitterPTank* ptank = reinterpret_cast<RpPrtStdEmitterPTank*>(PropertyAt(emitter, g_offsets.emtPTank));
    if (ptank->pTank == nullptr) {
        CreatePTank(emitter);
        if (ptank->pTank == nullptr) *failed = true;
    }
    return ptank;
}

// The bounding radius: the callbacks leave its square; RW's _rwSqrt (0x75e738) when positive.
void FinishBoundingRadius(RpPrtStdEmitter* emitter) {
    if (0.0f < emitter->boundingSphere) emitter->boundingSphere = rwSqrt(emitter->boundingSphere);
}

// 0x0069bbe0 RW_UpdateAtomicMorphBoundingSphere (RpAtomic's interpolated bounding sphere): it returns at
// once without a geometry, which the shim's streamed particle atomics never have.
void UpdateAtomicMorphBoundingSphere(RpAtomic* atomic) {
    if (atomic->geometry == nullptr) return;
    // STUB(C2): the morph target spheres of geometry atomics (none carries particles in the front end).
}

// 0x0072ba60 RW_UpdateParticleEmitter: the emitter's update callbacks (slot 1), then every active batch's
// particle update callbacks (slot 0) with the PTank arrays locked; emptied batches go to the inactive ring
// (their slot 3 callbacks run). The particle count is the live particles left; with a PTank bound before
// the update (no particles to update) only the arrays are locked and the out pointers moved past them.
RpPrtStdEmitter* UpdateParticleEmitter(RpAtomic* atomic, RpPrtStdEmitter* emitter, float* deltaTime) {
    RpPrtStdEmitterClass* eClass = emitter->emtClass;
    RpPrtStdParticleClass* pClass = emitter->prtClass;
    RwReal* atomicRadius = nullptr;
    if ((emitter->flag & rpPRTSTDEMITTERFLAGACTIVE) != 0) {
        CacheParticlePropertyOffsets(emitter);
        bool failed = false;
        RpPrtStdEmitterPTank* ptank = EmitterPTank(emitter, &failed);
        if (failed) return nullptr;
        if ((emitter->flag & rpPRTSTDEMITTERFLAGUPDATE) != 0 &&
            !RunEmitterCallBacks(eClass, rpPRTSTDEMITTERCALLBACKUPDATE, atomic, emitter, deltaTime))
            return nullptr;
        bool locked = false;
        if ((atomic->flags & 2) != 0) UpdateAtomicMorphBoundingSphere(atomic);
        atomicRadius = &atomic->boundingSphere[3];
        emitter->boundingSphere = 0.0f;
        RpPrtStdParticleBatch* ring = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
        int32_t live;
        if (ring != nullptr && (emitter->flag & rpPRTSTDEMITTERFLAGUPDATEPARTICLE) != 0) {
            locked = ptank != nullptr;
            if (locked) {
                LockParticleTankProperties(ptank);
                ptank->numPrt = 0;
                ring = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
            }
            live = 0;
            RpPrtStdParticleBatch* first = ring->next;
            emitter->activeBatch = nullptr;
            RpPrtStdParticleBatch* batch = first;
            RpPrtStdParticleBatch* next = first->next;
            first->newPrt = -1;
            for (;;) {
                if (batch->numPrt > 0) {
                    if (!RunParticleCallBacks(pClass, rpPRTSTDPARTICLECALLBACKUPDATE, emitter, batch, deltaTime, true))
                        return nullptr;
                    RpPrtStdParticleBatch* active = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
                    if (active == nullptr) {
                        batch->next = batch;
                    } else {
                        batch->next = active->next;
                        active->next = batch;
                    }
                    emitter->activeBatch = batch;
                    live += batch->numPrt;
                } else {
                    if (!RunParticleCallBacks(pClass, rpPRTSTDPARTICLECALLBACKDESTROY, emitter, batch, deltaTime, false))
                        return nullptr;
                    RpPrtStdParticleBatch* inactive = static_cast<RpPrtStdParticleBatch*>(emitter->inactiveBatch);
                    if (inactive == nullptr) {
                        batch->next = batch;
                    } else {
                        batch->next = inactive->next;
                        inactive->next = batch;
                    }
                    emitter->inactiveBatch = batch;
                }
                if (first == next) break;
                batch = next;
                next = batch->next;
                batch->newPrt = -1;
            }
        } else {
            live = emitter->prtActive;
        }
        emitter->prtActive = live;
        if (ptank != nullptr && !locked) {
            LockParticleTankProperties(ptank);
            const int32_t count = RpPTankAtomicGetPropertyTable(ptank->pTank)->numProp;
            for (int32_t i = 0; i < count; ++i) {
                ptank->dataInPtrs[i] += ptank->numPrt * ptank->dataStride[i];
                ptank->dataOutPtrs[i] += ptank->numPrt * ptank->dataStride[i];
            }
        }
    }
    FinishBoundingRadius(emitter);
    if (atomicRadius != nullptr && *atomicRadius < emitter->boundingSphere) *atomicRadius = emitter->boundingSphere;
    return emitter;
}

// 0x0072ae28 RW_EmitParticleEmitter: with the emit flag (8) the emit callbacks (slot 0); then the PTank's
// count (its +4) becomes the property's, the count-changed flag (0x800000) set and the PTank unlocked; then
// the post-emit callbacks (slot 2) with the update flag (0x10).
RpPrtStdEmitter* EmitParticleEmitter(RpAtomic* atomic, RpPrtStdEmitter* emitter, float* deltaTime) {
    RpPrtStdEmitterClass* eClass = emitter->emtClass;
    if ((emitter->flag & rpPRTSTDEMITTERFLAGACTIVE) == 0) return emitter;
    CacheParticlePropertyOffsets(emitter);
    bool failed = false;
    RpPrtStdEmitterPTank* ptank = EmitterPTank(emitter, &failed);
    if (failed) return nullptr;
    if ((atomic->flags & 2) != 0) UpdateAtomicMorphBoundingSphere(atomic);
    if ((emitter->flag & rpPRTSTDEMITTERFLAGEMIT) != 0 &&
        !RunEmitterCallBacks(emitter->emtClass, rpPRTSTDEMITTERCALLBACKEMIT, atomic, emitter, deltaTime, true))
        return nullptr;
    if (ptank != nullptr) {
        RpPTankData* data = ptank->pTank->ptank;
        data->flags40 |= 0x800000u;
        data->numPrt = static_cast<uint32_t>(ptank->numPrt);
        RpPTankAtomicUnlock(ptank->pTank);
    }
    if ((emitter->flag & rpPRTSTDEMITTERFLAGUPDATE) != 0 &&
        !RunEmitterCallBacks(eClass, rpPRTSTDEMITTERCALLBACKPOSTEMIT, atomic, emitter, deltaTime))
        return nullptr;
    FinishBoundingRadius(emitter);
    if (atomic->boundingSphere[3] < emitter->boundingSphere) atomic->boundingSphere[3] = emitter->boundingSphere;
    return emitter;
}

// 0x0072a7d8 RW_RenderParticleEmitter: with the render flag (0x40) the pre-render callbacks (slot 3, the
// standard one draws the PTank), with the particle render flag (0x80) every active batch's particle render
// callbacks (slot 1; DotD's classes have none), then the post-render callbacks (slot 4).
RpPrtStdEmitter* RenderParticleEmitter(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitterClass* eClass = emitter->emtClass;
    RpPrtStdParticleClass* pClass = emitter->prtClass;
    if ((emitter->flag & rpPRTSTDEMITTERFLAGACTIVE) == 0) return emitter;
    CacheParticlePropertyOffsets(emitter);
    if ((emitter->flag & rpPRTSTDEMITTERFLAGRENDER) != 0 &&
        !RunEmitterCallBacks(eClass, rpPRTSTDEMITTERCALLBACKPRERENDER, atomic, emitter, data))
        return nullptr;
    RpPrtStdParticleBatch* ring = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
    if (ring != nullptr && (emitter->flag & rpPRTSTDEMITTERFLAGRENDERPARTICLE) != 0) {
        RpPrtStdParticleBatch* first = ring->next;
        RpPrtStdParticleBatch* batch = first;
        do {
            // BUG(original): the loop counts the emitter class's callback arrays, not the particle class's.
            for (int32_t i = 0; i < eClass->numCallback; ++i) {
                RpPrtStdParticleCallBack render = pClass->callback[i].callback[rpPRTSTDPARTICLECALLBACKRENDER];
                if (render == nullptr) break;
                if (render(emitter, batch, data) != batch) return nullptr;
            }
            batch = batch->next;
        } while (first != batch);
    }
    if ((emitter->flag & rpPRTSTDEMITTERFLAGRENDER) != 0 &&
        !RunEmitterCallBacks(eClass, rpPRTSTDEMITTERCALLBACKPOSTRENDER, atomic, emitter, data))
        return nullptr;
    return emitter;
}

// 0x0072b3a0 RpPrtStdEmitterUpdate_maybe: RW_UpdateParticleEmitter and RW_EmitParticleEmitter in one: the
// update callbacks, the particles' update (the batch loops ending at the first empty slot), the PTank arrays
// locked once, then the emit callbacks (emit flag) and, when the arrays were locked, the PTank's count and
// unlock, then the post-emit callbacks.
RpPrtStdEmitter* EmitterUpdate(RpAtomic* atomic, RpPrtStdEmitter* emitter, float* deltaTime) {
    RpPrtStdEmitterClass* eClass = emitter->emtClass;
    RpPrtStdParticleClass* pClass = emitter->prtClass;
    if ((emitter->flag & rpPRTSTDEMITTERFLAGACTIVE) == 0) return emitter;
    CacheParticlePropertyOffsets(emitter);
    bool failed = false;
    RpPrtStdEmitterPTank* ptank = EmitterPTank(emitter, &failed);
    if (failed) return nullptr;
    if ((emitter->flag & rpPRTSTDEMITTERFLAGUPDATE) != 0 &&
        !RunEmitterCallBacks(eClass, rpPRTSTDEMITTERCALLBACKUPDATE, atomic, emitter, deltaTime))
        return nullptr;
    bool locked = false;
    if ((atomic->flags & 2) != 0) UpdateAtomicMorphBoundingSphere(atomic);
    RpPrtStdParticleBatch* ring = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
    emitter->boundingSphere = 0.0f;  // TOC -0x374c
    int32_t live;
    if (ring != nullptr && (emitter->flag & rpPRTSTDEMITTERFLAGUPDATEPARTICLE) != 0) {
        locked = ptank != nullptr;
        if (locked) {
            LockParticleTankProperties(ptank);
            ptank->numPrt = 0;
            ring = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
        }
        live = 0;
        RpPrtStdParticleBatch* first = ring->next;
        emitter->activeBatch = nullptr;
        first->newPrt = -1;
        RpPrtStdParticleBatch* batch = first;
        RpPrtStdParticleBatch* next = first->next;
        for (;;) {
            if (batch->numPrt > 0) {
                if (!RunParticleCallBacks(pClass, rpPRTSTDPARTICLECALLBACKUPDATE, emitter, batch, deltaTime, true))
                    return nullptr;
                RpPrtStdParticleBatch* active = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
                if (active == nullptr) {
                    batch->next = batch;
                } else {
                    batch->next = active->next;
                    active->next = batch;
                }
                emitter->activeBatch = batch;
                live += batch->numPrt;
            } else {
                if (!RunParticleCallBacks(pClass, rpPRTSTDPARTICLECALLBACKDESTROY, emitter, batch, deltaTime, true))
                    return nullptr;
                RpPrtStdParticleBatch* inactive = static_cast<RpPrtStdParticleBatch*>(emitter->inactiveBatch);
                if (inactive == nullptr) {
                    batch->next = batch;
                } else {
                    batch->next = inactive->next;
                    inactive->next = batch;
                }
                emitter->inactiveBatch = batch;
            }
            if (first == next) break;
            batch = next;
            next = batch->next;
            batch->newPrt = -1;
        }
    } else {
        live = emitter->prtActive;
    }
    emitter->prtActive = live;
    if (ptank != nullptr && !locked) {
        LockParticleTankProperties(ptank);
        const int32_t count = RpPTankAtomicGetPropertyTable(ptank->pTank)->numProp;
        for (int32_t i = 0; i < count; ++i) {
            ptank->dataInPtrs[i] += ptank->numPrt * ptank->dataStride[i];
            ptank->dataOutPtrs[i] += ptank->numPrt * ptank->dataStride[i];
        }
        locked = true;
    }
    if ((emitter->flag & rpPRTSTDEMITTERFLAGEMIT) != 0 &&
        !RunEmitterCallBacks(emitter->emtClass, rpPRTSTDEMITTERCALLBACKEMIT, atomic, emitter, deltaTime, true))
        return nullptr;
    if (ptank != nullptr && locked) {
        RpPTankData* data = ptank->pTank->ptank;
        data->flags40 |= 0x800000u;
        data->numPrt = static_cast<uint32_t>(ptank->numPrt);
        RpPTankAtomicUnlock(ptank->pTank);
    }
    if ((emitter->flag & rpPRTSTDEMITTERFLAGUPDATE) != 0 &&
        !RunEmitterCallBacks(emitter->emtClass, rpPRTSTDEMITTERCALLBACKPOSTEMIT, atomic, emitter, deltaTime, true))
        return nullptr;
    FinishBoundingRadius(emitter);
    if (atomic->boundingSphere[3] < emitter->boundingSphere) atomic->boundingSphere[3] = emitter->boundingSphere;
    return emitter;
}

}  // namespace

// 0x007310e0 _rpPrtStdEmitterStdUpdateTimeCB_maybe (slot 1): the standard property's LTM pointer (the
// atomic's frame LTM), its time advanced; with a PTank whose constant 2D rotation is animated (update flag
// 0x20000) the rotation advances by the rotation speed, wrapped into [-pi, pi], and the PTank is told
// (flag 0x20000).
RpPrtStdEmitter* StdUpdateTime(RpAtomic* atomic, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitterStandard* std = reinterpret_cast<RpPrtStdEmitterStandard*>(PropertyAt(emitter, g_offsets.emtStd));
    std->ltm = RwFrameGetLTM(atomic->frame);
    const float dt = *static_cast<const float*>(data);
    std->currTime = dt + std->currTime;
    if (g_offsets.emtPTank >= 0) {
        RpPrtStdEmitterPTank* ptank =
            reinterpret_cast<RpPrtStdEmitterPTank*>(PropertyAt(emitter, g_offsets.emtPTank));
        if ((ptank->updateFlags & 0x20000) != 0 && ptank->pTank != nullptr) {
            RpPTankData* tank = ptank->pTank->ptank;
            float rotation;
            std::memcpy(&rotation, &tank->renderC8, 4);
            rotation = ppc::fmadds(dt, std->prtDelta2DRotate, rotation);
            if (rotation > 3.14159274f) {  // TOC -0x36d8 (0x40490fdb)
                rotation = rotation - 6.28318548f;  // -0x36d4 (0x40c90fdb)
            } else if (!(rotation >= -3.14159274f)) {
                rotation = rotation + 6.28318548f;
            }
            std::memcpy(&tank->renderC8, &rotation, 4);
            tank->flags40 |= 0x20000u;
        }
    }
    return emitter;
}

// 0x007311b8 _rpPrtStdEmitterStdScheduleEmitCB_maybe (slot 2): once the emission time is reached, the next
// one is the time + the gap + (2r - 1) * the gap bias, r the emitter's next random number in [0, 1).
RpPrtStdEmitter* StdScheduleEmit(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    RpPrtStdEmitterStandard* std = reinterpret_cast<RpPrtStdEmitterStandard*>(PropertyAt(emitter, g_offsets.emtStd));
    const float now = std->currTime;
    if (!(std->emtEmitTime <= now)) return emitter;
    const float next = now + std->emtEmitGap;
    std->emtPrevEmitTime = now;
    const uint32_t seed = NextSeed(&std->seed);
    float r = static_cast<float>(static_cast<double>(seed));  // fcfid + frsp
    r = r * 2.32830644e-10f;                                  // TOC -0x36cc (0x2f800000)
    r = r + r;
    r = r - 1.0f;
    std->emtEmitTime = ppc::fmadds(r, std->emtEmitGapBias, next);
    return emitter;
}

// 0x00731360 RW_RenderEmitterParticleTank (slot 3): with live particles, the PTank atomic's render callback
// when it holds any; null without a PTank property or when the render fails.
RpPrtStdEmitter* StdRenderPTank(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    if (emitter->prtActive <= 0) return emitter;
    const int32_t offset = EmitterPropOffset(emitter, 6);
    if (offset < 0) return nullptr;
    RpPrtStdEmitterPTank* ptank = reinterpret_cast<RpPrtStdEmitterPTank*>(PropertyAt(emitter, offset));
    if (ptank->numPrt == 0) return emitter;
    RpAtomic* pTank = ptank->pTank;
    if (pTank->renderCallBack(pTank) == nullptr) return nullptr;
    return emitter;
}

// 0x0072d508 RpPrtStdPClassSetCallBackArray_maybe: `count` arrays copied into a new block.
void PClassSetCallBackArray(RpPrtStdParticleClass* pClass, int32_t count, const RpPrtStdParticleCallBackArray* arrays) {
    RpPrtStdParticleCallBackArray* copy = new RpPrtStdParticleCallBackArray[count > 0 ? count : 1];
    for (int32_t i = 0; i < count; ++i) copy[i] = arrays[i];
    delete[] pClass->callback;
    pClass->callback = copy;
    pClass->numCallback = count;
}

}  // namespace rpprtstd

// 0x00730cb8 RW_UpdateParticleAtomic: the atomic's radius from 0, every emitter updated (from the list
// head's next, as the list keeps its last emitter); null when one fails. The atomic's sphere then goes to
// its geometry's morph target and the atomic's frame is marked (private flag 1): nothing natively (the
// shim's streamed atomics have no geometry or object header).
RpAtomic* RpPrtStdAtomicUpdate(RpAtomic* atomic, float* deltaTime) {
    if (atomic->prtStdEmitters == nullptr) return nullptr;
    if ((atomic->flags & 2) != 0) rpprtstd::UpdateAtomicMorphBoundingSphere(atomic);
    atomic->boundingSphere[3] = 0.0f;
    RpAtomic* result = atomic;
    RpPrtStdEmitter* first = atomic->prtStdEmitters;
    RpPrtStdEmitter* emitter = first;
    do {
        RpPrtStdEmitter* next = emitter->next;
        if (rpprtstd::UpdateParticleEmitter(atomic, emitter, deltaTime) != emitter) {
            result = nullptr;
            break;
        }
        emitter = next;
    } while (first != emitter);
    return result;
}

// 0x00730e10 RW_UpdateParticleAtomic_2: RW_UpdateParticleAtomic with the combined update and emit
// (0x72b3a0) per emitter.
RpAtomic* RpPrtStdAtomicUpdateAndEmit(RpAtomic* atomic, float* deltaTime) {
    if (atomic->prtStdEmitters == nullptr) return nullptr;
    if ((atomic->flags & 2) != 0) rpprtstd::UpdateAtomicMorphBoundingSphere(atomic);
    atomic->boundingSphere[3] = 0.0f;
    RpAtomic* result = atomic;
    RpPrtStdEmitter* first = atomic->prtStdEmitters;
    RpPrtStdEmitter* emitter = first;
    do {
        RpPrtStdEmitter* next = emitter->next;
        if (rpprtstd::EmitterUpdate(atomic, emitter, deltaTime) != emitter) {
            result = nullptr;
            break;
        }
        emitter = next;
    } while (first != emitter);
    return result;
}

// 0x00730990 RW_EmitParticleAtomic
RpAtomic* RpPrtStdAtomicEmit(RpAtomic* atomic, float* deltaTime) {
    if (atomic->prtStdEmitters == nullptr) return nullptr;
    RpAtomic* result = atomic;
    RpPrtStdEmitter* first = atomic->prtStdEmitters;
    RpPrtStdEmitter* emitter = first;
    do {
        RpPrtStdEmitter* next = emitter->next;
        if (rpprtstd::EmitParticleEmitter(atomic, emitter, deltaTime) != emitter) {
            result = nullptr;
            break;
        }
        emitter = next;
    } while (first != emitter);
    if ((atomic->flags & 2) != 0) rpprtstd::UpdateAtomicMorphBoundingSphere(atomic);
    return result;
}

// 0x00730ba8 RW_RenderParticleAtomic (the atomic's render callback, +0x48, once it has emitters): the
// list's last emitter first, then from its next on; null when one fails.
RpAtomic* RpPrtStdAtomicRender(RpAtomic* atomic) {
    RpPrtStdEmitter* first = atomic->prtStdEmitters;
    if (first == nullptr) return atomic;
    RpPrtStdEmitter* emitter = first->next;
    if (rpprtstd::RenderParticleEmitter(atomic, first, nullptr) != first) return nullptr;
    while (first != emitter) {
        RpPrtStdEmitter* next = emitter->next;
        if (rpprtstd::RenderParticleEmitter(atomic, emitter, nullptr) != emitter) return nullptr;
        emitter = next;
    }
    return atomic;
}
