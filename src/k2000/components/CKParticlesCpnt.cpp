// CKParticlesCpnt.cpp - reconstructed original translation unit 0x1d9080-0x1dab88 (GAME_TOC1, main_toc1), 25 functions, 22 live.
// Primary class: CKParticlesCpnt  key 0x646  category Component  size 0x6c  vtable 0xb1df00
// Other owners: ApplyParticleComponentParameters (2), QueueParticleComponentEmission (2), TriggerParticleNodeEmission (1), ApplyParticleComponentOverrides (1), ProcessParticleComponentEmissionQueue (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d9080  CKParticlesCpnt_Delete
//   [ ] 0x1d90d0  CKParticlesCpnt_Construct  [dead]
//   [x] 0x1d90e8  CKParticlesCpnt_FlushEmissionRequests
//   [ ] 0x1d9128  RegisterCKParticlesCpntClass
//   [ ] 0x1d91a0  _GLOBAL__I_1d91a0
//   [x] 0x1d91b0  TriggerParticleNodeEmission
//   [x] 0x1d9340  CKParticlesCpnt_DeleteArray
//   [x] 0x1d93e0  CKParticlesCpnt_Destructor_2  (~CKParticlesCpnt)
//   [ ] 0x1d9458  CKParticlesCpnt_Construct_2  [dead]
//   [x] 0x1d9470  CKParticlesCpnt_DeletingDestructor  (~CKParticlesCpnt + delete)
//   [x] 0x1d94f8  CKParticlesCpnt_Destructor  (~CKParticlesCpnt)
//   [x] 0x1d9570  CKParticlesCpnt_CreateArray
//   [x] 0x1d9610  CKParticlesCpnt_Create
//   [ ] 0x1d9650  CKParticlesCpnt_Save
//   [x] 0x1d9658  CKParticlesCpnt_Load
//   [x] 0x1d96e8  CKParticlesCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x1d96f0  CKParticlesCpnt_Destroy  (empty: the default)
//   [x] 0x1d96f8  CKParticlesCpnt_CachePropertyValuesFromEmitter_maybe
//   [x] 0x1d9b78  CKParticlesCpnt_CachePropertyValuesFromEmitter_Thunk_maybe
//   [x] 0x1d9b80  ApplyParticleComponentOverrides
//   [x] 0x1da1a8  ProcessParticleComponentEmissionQueue
//   [x] 0x1da328  ApplyParticleComponentParameters
//   [x] 0x1da838  ApplyParticleComponentParameters
//   [x] 0x1da840  QueueParticleComponentEmission
//   [ ] 0x1dab78  QueueParticleComponentEmission_NoDirection  [dead]
//
//   [ ] 0x9adb30  CKParticlesCpnt_IsKindOfClass  [inline]
//   [x] 0x9adb58  CKParticlesCpnt_GetClassType  [inline]
//   [x] 0x9adb60  CKParticlesCpnt_GetClassID  [inline]
#include "k2000/components/CKParticlesCpnt.h"

#include <cstring>

#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"

// 0x001d9610 CKParticlesCpnt_Create, the inlined constructor (0x1d90d0 CKParticlesCpnt_Construct is a
// dead copy): +0x08 only.
CKParticlesCpnt::CKParticlesCpnt() { m_pEmissionQueueHead = nullptr; }

// 0x001d9658 CKParticlesCpnt_Load
int32_t CKParticlesCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pParticleNode);
    return 1;
}

// 0x001d96f8 CKParticlesCpnt_CachePropertyValuesFromEmitter_maybe. Every value is read through the emitter class's
// property table again (the original reloads the emitter each time); property 5 is looked up before each size.
void CKParticlesCpnt::CachePropertyValuesFromEmitter() {
    if (m_pParticleNode == nullptr) return;
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
    auto standard = [node]() {
        RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
        return reinterpret_cast<const RpPrtStdEmitterStandard*>(reinterpret_cast<const uint8_t*>(emitter) +
                                                                emitter->emtClass->propTab->propOffset[1]);
    };
    m_unk0c = static_cast<uint32_t>(standard()->emtPrtEmit);
    m_unk10 = static_cast<uint32_t>(standard()->emtPrtEmitBias);
    m_unk14[0] = standard()->emtSize.x;
    m_unk14[1] = standard()->emtSize.y;
    m_unk14[2] = standard()->emtSize.z;
    m_unk2c[0] = standard()->prtInitDir.x;
    m_unk2c[1] = standard()->prtInitDir.y;
    m_unk2c[2] = standard()->prtInitDir.z;
    m_unk38[0] = standard()->prtInitDirBias.x;
    m_unk38[1] = standard()->prtInitDirBias.y;
    m_unk38[2] = standard()->prtInitDirBias.z;
    m_unk44 = standard()->prtInitVel;
    m_unk48 = standard()->prtInitVelBias;
    auto sizeOffset = [node]() {
        return RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab,
                                            rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);  // TocBridge 0x72ee88
    };
    if (sizeOffset() == -1) {
        m_unk4c[0] = standard()->prtSize.x;
        m_unk4c[1] = standard()->prtSize.y;
    } else {
        // The property's eight floats in the order (0, 1, 4, 5, 2, 3, 6, 7); one that is gone reads 1.0 (TOC1 -0x17d8).
        static const int32_t kOrder[8] = {0, 1, 4, 5, 2, 3, 6, 7};
        for (int32_t i = 0; i < 8; ++i) {
            const int32_t offset = sizeOffset();
            if (offset == -1) {
                m_unk4c[i] = 1.0f;
            } else {
                const uint8_t* size = reinterpret_cast<const uint8_t*>(node->m_pRpPrtStdEmitter) + offset;
                m_unk4c[i] = reinterpret_cast<const float*>(size)[kOrder[i]];
            }
        }
    }
    m_unk20[0] = standard()->force.x;
    m_unk20[1] = standard()->force.y;
    m_unk20[2] = standard()->force.z;
}

namespace {

// 0x00c50d34 / 0x00c50d40 / 0x00c50d64 (TOC1 -0x17e0 / -0x17e4 / -0x17e8): the shared X and Y axes and the null
// vector (zero in the EBOOT's BSS; static initialisers fill them).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// The emitter's standard property (property 1), through the class's property table as the original reads it.
RpPrtStdEmitterStandard* Standard(CParticlesNodeFx* node) {
    RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
    return reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) +
                                                      emitter->emtClass->propTab->propOffset[1]);
}

// RW_GetParticlePropertyOffset (TocBridge 0x98e120 -> 0x72ee88) of the node's emitter.
int32_t PropOffset(CParticlesNodeFx* node, int32_t propID) {
    return RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, propID);
}

// One float of the size property (5), when the emitter has it, then the node's bounding radius (each store of the
// original is followed by UpdateParticleNodeSizeBoundingRadius 0xe5c80).
void SetSizeValue(CParticlesNodeFx* node, int32_t index, float value) {
    const int32_t offset = PropOffset(node, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
    if (offset != -1) reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(node->m_pRpPrtStdEmitter) + offset)[index] = value;
    UpdateParticleNodeSizeBoundingRadius(node);
}

// The sizes without a size property: the standard size and, with a PTank property (6) whose PTank exists, the PTank's
// constant size (+0xc0) with its changed flag 0x4000; then the node's bounding radius.
void SetStandardSize(CParticlesNodeFx* node, float x, float y) {
    Standard(node)->prtSize.x = x;
    Standard(node)->prtSize.y = y;
    const int32_t offset = PropOffset(node, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (offset != -1) {
        const RpPrtStdEmitterPTank* ptank = reinterpret_cast<const RpPrtStdEmitterPTank*>(
            reinterpret_cast<const uint8_t*>(node->m_pRpPrtStdEmitter) + offset);
        if (ptank->pTank != nullptr) {
            RpPTankData* data = ptank->pTank->ptank;  // atomic + the PTank plugin offset (0x00cf079c)
            std::memcpy(&data->renderC0[0], &x, sizeof x);
            std::memcpy(&data->renderC0[1], &y, sizeof y);
            data->flags40 |= 0x4000u;
        }
    }
    UpdateParticleNodeSizeBoundingRadius(node);
}

}  // namespace

// 0x001d9b80 ApplyParticleComponentOverrides
void CKParticlesCpnt::ApplyOverrides(const ParticleEmitOverrides* overrides) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
    if (node == nullptr || overrides == nullptr) return;
    const uint32_t mask = overrides->m_overrideMask;
    if ((mask & 0x1) != 0) {
        Standard(node)->emtPrtEmit = static_cast<int32_t>(overrides->m_emtPrtEmit);
        node->m_ui8NbEmitParticlesPerPoint = static_cast<uint8_t>(overrides->m_emtPrtEmit);
    }
    if ((overrides->m_overrideMask & 0x2) != 0) Standard(node)->emtPrtEmitBias = static_cast<int32_t>(overrides->m_emtPrtEmitBias);
    if ((overrides->m_overrideMask & 0x4) != 0) {
        RpPrtStdEmitterStandard* standard = Standard(node);
        standard->emtSize.x = overrides->m_emtSize.x;
        standard->emtSize.y = overrides->m_emtSize.y;
        standard->emtSize.z = overrides->m_emtSize.z;
    }
    if ((overrides->m_overrideMask & 0x8) != 0) {
        RpPrtStdEmitterStandard* standard = Standard(node);
        standard->prtInitDir.x = overrides->m_prtInitDir.x;
        standard->prtInitDir.y = overrides->m_prtInitDir.y;
        standard->prtInitDir.z = overrides->m_prtInitDir.z;
    }
    if ((overrides->m_overrideMask & 0x10) != 0) {
        RpPrtStdEmitterStandard* standard = Standard(node);
        standard->prtInitDirBias.x = overrides->m_prtInitDirBias.x;
        standard->prtInitDirBias.y = overrides->m_prtInitDirBias.y;
        standard->prtInitDirBias.z = overrides->m_prtInitDirBias.z;
    }
    if ((overrides->m_overrideMask & 0x20) != 0) Standard(node)->prtInitVel = overrides->m_prtInitVel;
    if ((overrides->m_overrideMask & 0x40) != 0) Standard(node)->prtInitVelBias = overrides->m_prtInitVelBias;
    if ((overrides->m_overrideMask & 0x80) != 0) {
        if (PropOffset(node, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE) == -1) {
            SetStandardSize(node, overrides->m_prtSize[0], overrides->m_prtSize[1]);
        } else {
            // The property's start size, end size, start bias, end bias (x then y).
            static const int32_t kOrder[8] = {0, 1, 4, 5, 2, 3, 6, 7};
            for (int32_t i = 0; i < 8; ++i) SetSizeValue(node, kOrder[i], overrides->m_prtSize[kOrder[i]]);
        }
    }
    if ((overrides->m_overrideMask & 0x100) != 0) {
        RpPrtStdEmitterStandard* standard = Standard(node);
        standard->force.x = overrides->m_force.x;
        standard->force.y = overrides->m_force.y;
        standard->force.z = overrides->m_force.z;
    }
}

// 0x001da328 ApplyParticleComponentParameters (0x001da838 ApplyParticleComponentParameters, the second entry, is a
// branch to it)
void CKParticlesCpnt::ApplyParameters() {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
    if (node == nullptr) return;
    Standard(node)->emtPrtEmit = static_cast<int32_t>(m_unk0c);
    node->m_ui8NbEmitParticlesPerPoint = static_cast<uint8_t>(m_unk0c);
    Standard(node)->emtPrtEmitBias = static_cast<int32_t>(m_unk10);
    {
        RpPrtStdEmitterStandard* standard = Standard(node);
        standard->emtSize.x = m_unk14[0];
        standard->emtSize.y = m_unk14[1];
        standard->emtSize.z = m_unk14[2];
    }
    {
        RpPrtStdEmitterStandard* standard = Standard(node);
        standard->prtInitDir.x = m_unk2c[0];
        standard->prtInitDir.y = m_unk2c[1];
        standard->prtInitDir.z = m_unk2c[2];
    }
    {
        RpPrtStdEmitterStandard* standard = Standard(node);
        standard->prtInitDirBias.x = m_unk38[0];
        standard->prtInitDirBias.y = m_unk38[1];
        standard->prtInitDirBias.z = m_unk38[2];
    }
    Standard(node)->prtInitVel = m_unk44;
    Standard(node)->prtInitVelBias = m_unk48;
    if (PropOffset(node, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE) == -1) {
        SetStandardSize(node, m_unk4c[0], m_unk4c[1]);
    } else {
        // +0x4c.. are in CachePropertyValuesFromEmitter's order: start, end, start bias, end bias.
        static const int32_t kOrder[8] = {0, 1, 4, 5, 2, 3, 6, 7};
        for (int32_t i = 0; i < 8; ++i) SetSizeValue(node, kOrder[i], m_unk4c[i]);
    }
    RpPrtStdEmitterStandard* standard = Standard(node);
    standard->force.x = m_unk20[0];
    standard->force.y = m_unk20[1];
    standard->force.z = m_unk20[2];
}

// 0x001d91b0 TriggerParticleNodeEmission
void CKParticlesCpnt::TriggerNodeEmission(CParticlesNodeFx* node, const CVector3* position, const CVector3* direction) {
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    if (direction != nullptr &&
        !(direction->x == kNullVector.x && direction->y == kNullVector.y && direction->z == kNullVector.z)) {
        if (static_cast<uint8_t>(node->SetOrientationFromAtUp(direction, &kAxisY)) == 0)  // 0x000d0918
            node->SetOrientationFromAtUp(direction, &kAxisX);
    }
    node->m_sgProperties = (node->m_sgProperties | 0x200u | 0x400u) & ~0x80000u;
    node->m_fEmissionSpeedAdjustment = 0.0f;
    node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
}

// 0x001da1a8 ProcessParticleComponentEmissionQueue
void CKParticlesCpnt::ProcessEmissionQueue() {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
    if (node == nullptr) return;
    if (node->m_pAdvEmtPointList != nullptr) {
        // The point list is refilled by the next queued emissions (flag 0x8000: the node's update clears its count).
        node->m_sgProperties = (node->m_sgProperties & ~0x8000u) | 0x8000u;
        node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
    }
    ParticleEmitRequest* request = m_pEmissionQueueHead;
    if (node->m_pAdvEmtPointList == nullptr) {
        // Hidden (flag 4) while no particle is alive and nothing is queued.
        const uint32_t hidden = (node->m_pRpPrtStdEmitter->prtActive == 0 && request == nullptr) ? 4u : 0u;
        node->m_sgProperties = (node->m_sgProperties & ~4u) | hidden;
    } else {
        node->m_sgProperties &= ~4u;
    }
    if (request == nullptr) return;
    ApplyOverrides(request->m_pOverrides);
    TriggerNodeEmission(static_cast<CParticlesNodeFx*>(m_pParticleNode), &request->m_position, &request->m_direction);
    request = m_pEmissionQueueHead;
    m_pEmissionQueueHead = request->m_pNext;
    delete request;  // back to the FreeListPool 0x00ceaa94 in the original
}

// 0x001da840 QueueParticleComponentEmission
void CKParticlesCpnt::QueueEmission(const CVector3* position, const CVector3* direction,
                                    const ParticleEmitOverrides* overrides) {
    if (m_pParticleNode == nullptr) return;
    ApplyParameters();
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
    if (node->m_pAdvEmtPointList != nullptr) {
        if (overrides != nullptr) {
            ApplyOverrides(overrides);
            node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
        }
        if ((node->m_sgProperties & 0x400u) == 0) {
            // Not emitting yet: shown, emitting (0x400, 0x80000 off), the speed adjustment 0, the emitter active and
            // emitting.
            node->m_sgProperties &= ~4u;
            node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
            node->m_sgProperties = (node->m_sgProperties | 0x400u) & ~0x80000u;
            node->m_fEmissionSpeedAdjustment = 0.0f;
            node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
            node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
        }
        const uint32_t count = node->m_ui8NbActivePoints;
        if (count < 0x40) {
            RwV3d* point = &node->m_pAdvEmtPointList->pointList[count];
            point->z = position->z;
            point->x = position->x;
            point->y = position->y;
            if (direction != nullptr) {
                RwV3d* along = &node->m_pAdvEmtPointList->directionList[node->m_ui8NbActivePoints];
                along->z = direction->z;
                along->x = direction->x;
                along->y = direction->y;
            }
            node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
            node->m_ui8NbActivePoints = static_cast<uint8_t>(node->m_ui8NbActivePoints + 1);
            node = static_cast<CParticlesNodeFx*>(m_pParticleNode);
        }
        // The points are absolute: the node's frame at the origin.
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.z = kNullVector.z;
        frame->modelling.pos.x = kNullVector.x;
        frame->modelling.pos.y = kNullVector.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(node->m_pRwFrame);  // 0x00010698
        return;
    }
    ParticleEmitRequest* request = new ParticleEmitRequest;  // FreeListPool 0x00ceaa94 (FreeListPool_Grow when empty)
    request->m_pNext = m_pEmissionQueueHead;
    m_pEmissionQueueHead = request;
    request->m_position.x = position->x;
    request->m_position.y = position->y;
    request->m_position.z = position->z;
    request->m_pOverrides = overrides;
    if (direction == nullptr) {
        request->m_direction = kNullVector;
    } else {
        request->m_direction.x = direction->x;
        request->m_direction.y = direction->y;
        request->m_direction.z = direction->z;
    }
}

// 0x001d94f8 CKParticlesCpnt_Destructor (0x1d93e0 / 0x1d9470 the same: FlushEmissionRequests' loop inlined)
CKParticlesCpnt::~CKParticlesCpnt() { FlushEmissionRequests(); }

// 0x001d90e8 CKParticlesCpnt_FlushEmissionRequests
void CKParticlesCpnt::FlushEmissionRequests() {
    ParticleEmitRequest* request = m_pEmissionQueueHead;
    while (request != nullptr) {
        ParticleEmitRequest* next = request->m_pNext;
        delete request;  // back to the FreeListPool 0x00ceaa94 in the original
        request = next;
    }
    m_pEmissionQueueHead = nullptr;
}
