// CKParticlesEffectNodeFx.cpp - reconstructed original translation unit 0x1cd4a0-0x1cf310 (GAME_TOC1, main_toc1), 23 functions, 17 live.
// Primary class: CKParticlesEffectNodeFx  key 0x1fcc  category Logic  size 0x30  vtable 0xb1d4d8
// Other owners: SetOwnedParticleEffectTransform (2), SetOwnedParticleEffectPosition (1), StopOwnedParticleEffect (1), UpdateParticleEffectLifetime (1), StartParticleEffect (1), StopParticleEffect (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1cd4a0  FUN_001cd4a0  [dead]
//   [ ] 0x1cd598  FUN_001cd598  [dead]
//   [ ] 0x1cd5b8  RegisterCKParticlesEffectNodeFxClass
//   [ ] 0x1cd630  _GLOBAL__I_1cd630
//   [x] 0x1cd640  CKParticlesEffectNodeFx_AttachNodesToHotSpot_maybe
//   [x] 0x1cd718  CKParticlesEffectNodeFx_PostLoad
//   [x] 0x1cd758  CKParticlesEffectNodeFx_Load
//   [ ] 0x1cd910  CKParticlesEffectNodeFx_Save
//   [x] 0x1cd938  CKParticlesEffectNodeFx_DeleteArray
//   [x] 0x1cd9e0  CKParticlesEffectNodeFx_Create
//   [x] 0x1cda50  CKParticlesEffectNodeFx_RecursiveRegistration
//   [ ] 0x1cdb30  SetOwnedParticleEffectTransform_2  [dead]
//   [x] 0x1cdc08  SetOwnedParticleEffectTransform
//   [x] 0x1cdce0  SetOwnedParticleEffectPosition
//   [x] 0x1cdde8  StopOwnedParticleEffect
//   [ ] 0x1cde58  FUN_001cde58  [dead]
//   [ ] 0x1cdf58  FUN_001cdf58  [dead]
//   [ ] 0x1ce000  FUN_001ce000  [dead]
//   [x] 0x1ce0a8  UpdateParticleEffectLifetime
//   [x] 0x1ce1e8  CKParticlesEffectNodeFx_StopIfLinkedTo
//   [x] 0x1ce2b8  CKParticlesEffectNodeFx_CreateArray
//   [x] 0x1ce3a0  StartParticleEffect
//   [x] 0x1cf0d0  StopParticleEffect
//
//   [ ] 0x9acce0  CKParticlesEffectNodeFx_IsKindOfClass  [inline]
//   [x] 0x9acd18  CKParticlesEffectNodeFx_GetClassType  [inline]
//   [x] 0x9acd20  CKParticlesEffectNodeFx_GetClassID  [inline]
//   [x] 0x9acd28  CKParticlesEffectNodeFx_GetFxData  [inline]
//   [x] 0x9acd30  CKParticlesEffectNodeFx_SetFxData  [inline]
//   [ ] 0x9acd38  CKParticlesEffectNodeFx_Destruct  [inline]
//   [ ] 0x9acdb8  CKParticlesEffectNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"

#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {
// The emitter's standard property (index 1 of its class's property table).
RpPrtStdEmitterStandard* EmitterStandard(RpPrtStdEmitter* emitter) {
    return reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) +
                                                       emitter->emtClass->propTab->propOffset[1]);
}
// A parameter block word stored as is into a float field (lwz/stw or lfs/stfs pairs).
void StoreWord(float* dst, uint32_t word) { std::memcpy(dst, &word, 4); }
void StoreVector(RwV3d* dst, const CVector3& src) {
    dst->x = src.x;
    dst->y = src.y;
    dst->z = src.z;
}
// The node taken off its parent (the parent branch's vt+0x78), when it has one.
void DetachFromParent(CSGLeaf* node) {
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);
}
}  // namespace

// 0x001cdce0 SetOwnedParticleEffectPosition
void SetOwnedParticleEffectPosition(CKParticlesEffectNodeFx* effect, const CVector3* position, const IKSerializable* owner) {
    if ((effect->m_baFxData & 2u) == 0 || effect->m_pOwner != owner) return;
    for (uint32_t i = 0; i < effect->m_ui32NodeCount; ++i) {
        CParticlesNodeFx* node = effect->m_ppParticleNodes[i];
        if (node == nullptr) continue;
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos = {position->x, position->y, position->z};
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
    }
}

// Inlined in 0x001cd9e0 CKParticlesEffectNodeFx_Create.
CKParticlesEffectNodeFx::CKParticlesEffectNodeFx() {
    m_ppParticleNodes = nullptr;
    m_ui32NodeCapacity = 1;
    m_ui32NodeCount = 0;
}

// 0x001cd758 CKParticlesEffectNodeFx_Load: the particle-node references only in level files.
int32_t CKParticlesEffectNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_ui32NodeCapacity = 1;
        m_ppParticleNodes =
            static_cast<CParticlesNodeFx**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CParticlesNodeFx*))));
    } else {
        m_ui32NodeCapacity = count;
        m_ppParticleNodes = static_cast<CParticlesNodeFx**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CParticlesNodeFx*))));
    }
    if (m_ui32NodeCapacity < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_ppParticleNodes = static_cast<CParticlesNodeFx**>(
            Mem_ReallocAligned16(m_ppParticleNodes, capacity * static_cast<uint32_t>(sizeof(CParticlesNodeFx*))));
        m_ui32NodeCapacity = capacity;
    }
    m_ui32NodeCount = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_ppParticleNodes[i]);  // one reference at a time
    return 1;
}

// 0x001ce1e8 CKParticlesEffectNodeFx_StopIfLinkedTo
void CKParticlesEffectNodeFx::StopIfLinkedTo(int32_t sector) {
    if ((m_baFxData & 1) != 0 || sector == 0) return;
    if ((m_pEffectData->m_unk08 & 0x10) == 0) return;
    CSGLeaf* owner = m_pEffectData->m_pAttachOwner;
    if (owner == nullptr) return;
    if (sector == static_cast<int32_t>(owner->GetSectorIndex())) Stop();
}

// 0x001cd718 CKParticlesEffectNodeFx_PostLoad
int32_t CKParticlesEffectNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    m_bRefreshOrientation = 0;
    return 1;
}

// 0x001cd640 CKParticlesEffectNodeFx_AttachNodesToHotSpot_maybe
void CKParticlesEffectNodeFx::AttachNodesToHotSpot(CSGHotSpot* hotSpot) {
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
        if (m_ppParticleNodes[i] == nullptr) continue;
        DetachFromParent(m_ppParticleNodes[i]);
        hotSpot->AttachVolume(m_ppParticleNodes[i]);  // 0x000ce2b8
    }
}

// 0x001cdc08 SetOwnedParticleEffectTransform
void SetOwnedParticleEffectTransform(CKParticlesEffectNodeFx* effect, const CVector3* at, const CVector3* up,
                                     const IKSerializable* owner) {
    if ((effect->m_baFxData & 2u) == 0 || effect->m_pOwner != owner) return;
    for (uint32_t i = 0; i < effect->m_ui32NodeCount; ++i) {
        CParticlesNodeFx* node = effect->m_ppParticleNodes[i];
        if (node != nullptr) node->SetOrientationFromAtUp(at, up);  // 0x000d0918
    }
}

// 0x001ce3a0 StartParticleEffect
void CKParticlesEffectNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    CKParticlesEffectFxData* data = m_pEffectData;
    m_pAttachOwner = nullptr;
    // Screen effects (data +0x38) hang under the secondary scene root and draw with the 0x11 render mode.
    const uint32_t screen = (data != nullptr && data->m_unk38 != 0) ? 1u : 0u;
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
        CParticlesNodeFx* node = m_ppParticleNodes[i];
        if (node == nullptr) continue;
        node->m_sgProperties &= 0xfffeffffu;
        node->m_sgProperties = (node->m_sgProperties & 0xfffdffffu) | 0x20000u;
        // 0x000a71d0 CGeometry_SetField8_maybe: the first geometry's +0x08 (the sorting priority) = 100 per node.
        static_cast<CGeometry*>(node->m_lGeometryList)->m_pPriorityParent = (i * 100u) & 0xfffffffcu;
    }
    data = m_pEffectData;
    if (data == nullptr) {
        Stop();  // vt+0x6c
        return;
    }
    if ((data->m_unk08 & 0x10u) == 0) {
        // Not attached: every node in place with the data's matrix.
        for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
            CParticlesNodeFx* node = m_ppParticleNodes[i];
            if (node != nullptr) node->SetLocalMatrix(m_pEffectData->m_unk24);  // 0x000d0be8
        }
    } else if (data->m_pAttachOwner == nullptr) {
        // Attached to the data's hot spot (when there is one).
        CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(data->m_pAttachHotSpot);
        if (hotSpot != nullptr) {
            for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
                if (m_ppParticleNodes[i] == nullptr) continue;
                DetachFromParent(m_ppParticleNodes[i]);
                hotSpot->AttachVolume(m_ppParticleNodes[i]);  // 0x000ce2b8
            }
        }
    } else {
        // Attached to the data's node: every node becomes its child (vt+0x70); under an animated node (key 0x54b) the
        // nodes' bits 16 / 17 follow the data's flags 1 / 2. Then the data's matrix.
        m_pAttachOwner = static_cast<CSGBranch*>(data->m_pAttachOwner);
        for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
            if (m_ppParticleNodes[i] == nullptr) continue;
            DetachFromParent(m_ppParticleNodes[i]);
            m_pAttachOwner->AddChild(m_ppParticleNodes[i]);
        }
        CSGBranch* owner = m_pAttachOwner;
        const uint32_t key = (static_cast<uint32_t>(owner->GetClassID()) << 6) + static_cast<uint32_t>(owner->GetClassType());
        if (key == 0x54b) {
            for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
                CParticlesNodeFx* node = m_ppParticleNodes[i];
                if (node == nullptr) continue;
                node->m_sgProperties = (node->m_sgProperties & 0xfffeffffu) | ((m_pEffectData->m_unk08 & 1u) << 16);
                node->m_sgProperties = (node->m_sgProperties & 0xfffdffffu) | (((m_pEffectData->m_unk08 >> 1) & 1u) << 17);
            }
        }
        for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
            CParticlesNodeFx* node = m_ppParticleNodes[i];
            if (node != nullptr) node->SetLocalMatrix(m_pEffectData->m_unk24);  // 0x000d0be8
        }
    }
    // Every geometry's render mode: bit 17 = screen (UpdateProperties, vt+0x60, when it changes), the mode bits 0..4
    // 0x11 for screen effects else 0xf, bit 5 set; then the node's bit 5 (0x000cc808).
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
        CParticlesNodeFx* node = m_ppParticleNodes[i];
        if (node == nullptr) continue;
        for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
             geometry = geometry->m_pNext) {
            uint32_t flags = geometry->m_BitProperties;
            if (((flags >> 17) & 1u) != screen) {
                geometry->m_BitProperties = (flags & 0xfffdffffu) | (screen << 17);
                geometry->UpdateProperties();  // vt+0x60
                flags = geometry->m_BitProperties;
            }
            flags = (flags & 0xffffffe0u) | (screen != 0 ? 0x11u : 0xfu);
            geometry->m_BitProperties = (flags & 0xffffffdfu) | 0x20u;
        }
        node->SetFlag10Bit5ResetField20To1(screen & 0xffu);
    }
    if (screen != 0) {
        // The nodes go under the secondary scene root (+0x10, vt+0x70) and are stretched by the aspect (height / width,
        // CameraContext +0x48) along x (TOC -0x1b98 1.0 for y and z).
        for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
            if (m_ppParticleNodes[i] == nullptr) continue;
            DetachFromParent(m_ppParticleNodes[i]);
            static_cast<CSGBranch*>(g_pEngine->m_secondarySceneRoot)->AddChild(m_ppParticleNodes[i]);
        }
        const float aspect = static_cast<const CameraContext*>(g_pEngine->m_cameraContext)->m_fHeightOverWidth;
        for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
            CParticlesNodeFx* node = m_ppParticleNodes[i];
            if (node != nullptr) node->ScaleXYZ(aspect, 1.0f, 1.0f);  // 0x000d0d28
        }
    }
    // Each node's emitter takes its parameter block (the standard property, the particle size property when there is
    // one, each size word followed by the bounding radius update 0x000e5c80).
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
        CParticlesNodeFx* node = m_ppParticleNodes[i];
        if (node == nullptr) continue;
        const CKParticlesEffectFxData::ParameterBlock* block = m_pEffectData->m_parameterBlocks.m_pBlock[i];
        RpPrtStdEmitterStandard* standard = EmitterStandard(node->m_pRpPrtStdEmitter);
        standard->emtPrtEmit = static_cast<int32_t>(block->m_unk00);
        node->m_ui8NbEmitParticlesPerPoint = static_cast<uint8_t>(block->m_unk00);  // stb of the same word
        standard->emtPrtEmitBias = static_cast<int32_t>(block->m_unk04);
        StoreVector(&standard->emtSize, block->m_unk08);
        StoreVector(&standard->force, block->m_unk14);
        StoreVector(&standard->prtInitDir, block->m_unk20);
        StoreVector(&standard->prtInitDirBias, block->m_unk2c);
        StoreWord(&standard->prtInitVel, block->m_unk38);
        StoreWord(&standard->prtInitVelBias, block->m_unk3c);
        if (RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE) != -1) {
            const uint32_t sizes[8] = {block->m_unk40, block->m_unk44, block->m_unk48, block->m_unk4c,
                                       block->m_unk50, block->m_unk54, block->m_unk58, block->m_unk5c};
            for (uint32_t k = 0; k < 8; ++k) {
                const int32_t offset = RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab,
                                                                    rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
                if (offset != -1) {
                    std::memcpy(reinterpret_cast<uint8_t*>(node->m_pRpPrtStdEmitter) + offset + k * 4u, &sizes[k], 4);
                }
                UpdateParticleNodeSizeBoundingRadius(node);
            }
        }
        standard = EmitterStandard(node->m_pRpPrtStdEmitter);
        StoreWord(&standard->emtEmitGap, block->m_unk60);
        StoreWord(&standard->emtEmitGapBias, block->m_unk64);
        StoreWord(&standard->unk1c, block->m_unk68);
    }
    // The emitters start (active + emit, the speed adjustment 0, node bit 10 on, bit 19 off, shown). The lifetime: with
    // data flag 8 the longest particle life (prtLife + prtLifeBias) of the nodes, also node bit 9; with flag 4 the data's
    // +0x0c; else 0.
    m_fRemainingSeconds = 0.0f;
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
        CParticlesNodeFx* node = m_ppParticleNodes[i];
        if (node == nullptr) continue;
        if ((m_pEffectData->m_unk08 & 8u) != 0) {
            node->m_sgProperties = (node->m_sgProperties | 0x600u) & 0xfff7ffffu;
            node->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
            node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
            const RpPrtStdEmitterStandard* standard = EmitterStandard(node->m_pRpPrtStdEmitter);
            const float life = standard->prtLife + standard->prtLifeBias;
            if (!(m_fRemainingSeconds >= life)) m_fRemainingSeconds = life;  // fcmpu + bge
        } else {
            node->m_sgProperties = (node->m_sgProperties | 0x400u) & 0xfff7ffffu;
            node->m_fEmissionSpeedAdjustment = 0.0f;
            node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
            if ((m_pEffectData->m_unk08 & 4u) != 0) std::memcpy(&m_fRemainingSeconds, &m_pEffectData->m_unk0c, 4);
        }
        node->m_sgProperties &= 0xfffffffbu;
    }
}

// 0x001ce0a8 UpdateParticleEffectLifetime (vt+0x78)
void CKParticlesEffectNodeFx::Update(IKTime* frameClock) {
    m_fRemainingSeconds = m_fRemainingSeconds - frameClock->m_afDeltaTime[0];
    if (m_bRefreshOrientation != 0) {
        for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
            CParticlesNodeFx* node = m_ppParticleNodes[i];
            if (node != nullptr) node->SetLocalMatrix(m_pEffectData->m_unk24);  // 0x000d0be8
        }
    }
    const uint8_t flags = m_pEffectData->m_unk08;
    const float zero = 0.0f;  // TOC -0x1ba4
    if (((flags & 8u) != 0 && m_fRemainingSeconds < zero) || ((flags & 4u) != 0 && m_fRemainingSeconds < zero)) {
        Stop();  // vt+0x6c
    }
}

// 0x001cf0d0 StopParticleEffect (vt+0x6c)
void CKParticlesEffectNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
        if (m_ppParticleNodes[i] == nullptr) continue;
        DetachFromParent(m_ppParticleNodes[i]);
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(m_ppParticleNodes[i]);  // vt+0x70
    }
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    m_bRefreshOrientation = 0;
    m_pEffectData = nullptr;
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) {
        CParticlesNodeFx* node = m_ppParticleNodes[i];
        if (node == nullptr) continue;
        node->m_sgProperties &= 0xfff7fbffu;  // bits 10 and 19
        node->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
        node->m_sgProperties &= 0xfffeffffu;
        node->SetIdentity();  // 0x000d08f0
        if (node->m_pRpPrtStdEmitter->prtActive == 0) node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    }
}

// 0x009acd28 / 0x009acd30 CKParticlesEffectNodeFx_GetFxData / SetFxData
IKFxData* CKParticlesEffectNodeFx::GetFxData() { return m_pEffectData; }
void CKParticlesEffectNodeFx::SetFxData(IKFxData* data) { m_pEffectData = static_cast<CKParticlesEffectFxData*>(data); }

// 0x001cda50 CKParticlesEffectNodeFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner), then
// every particle node's registration (its vt+0x24; the count read each step).
void CKParticlesEffectNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    for (uint32_t i = 0; i < m_ui32NodeCount; ++i) m_ppParticleNodes[i]->RecursiveRegistration(type);
}
