// CKAnimatedFx.cpp - reconstructed original translation unit 0x5ca148-0x5cc298 (GAME_TOC2, main_toc2), 27 functions, 23 live.
// Primary class: CKAnimatedFx  key 0xa04c  category Logic  size ?  vtable 0xb300c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5ca148  CKAnimatedFx_Delete
//   [ ] 0x5ca198  CKAnimatedFx_Construct  [dead]
//   [ ] 0x5ca1a8  CKAnimatedFx_Construct_2  [dead]
//   [x] 0x5ca1b8  CKAnimatedFx_ResetState_maybe
//   [ ] 0x5ca1e8  RegisterCKAnimatedFxClass
//   [ ] 0x5ca260  _GLOBAL__I_5ca260
//   [ ] 0x5ca270  CKAnimatedFx_SetBasisFromRightUp_maybe  [dead]
//   [x] 0x5ca2d8  CKAnimatedFx_SetOrientation_maybe
//   [x] 0x5ca340  CKAnimatedFx_SetPosition
//   [x] 0x5ca3c8  CKAnimatedFx_UpdateSegmentVolumes_maybe
//   [x] 0x5ca4d8  CKAnimatedFx_ResetRigTransform_maybe
//   [x] 0x5ca828  CKAnimatedFx_Play
//   [x] 0x5ca908  CKAnimatedFx_PlayAnim_maybe
//   [x] 0x5ca980  CKAnimatedFx_DeleteArray
//   [x] 0x5caa28  CKAnimatedFx_CreateArray
//   [x] 0x5caac0  CKAnimatedFx_Create
//   [ ] 0x5caaf8  CKAnimatedFx_Save
//   [x] 0x5cab00  CKAnimatedFx_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0x5cab08  CKAnimatedFx_PostLoad
//   [x] 0x5cab50  CKAnimatedFx_Destroy  (empty: the default slot)
//   [x] 0x5cab58  CKAnimatedFx_Load
//   [x] 0x5cb010  CKAnimatedFx_DeletingDestructor  (the destructor; delete)
//   [x] 0x5cb050  CKAnimatedFx_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x5cb068  CKAnimatedFx_Destructor_2  [dead]
//   [x] 0x5cb080  CKAnimatedFx_SetFxActive
//   [x] 0x5cbf48  CKAnimatedFx_Stop_maybe
//   [x] 0x5cbfb8  CKAnimatedFx_Update
//
//   [x] 0x9cd610  CKAnimatedFx_GetClassType  [inline]
//   [x] 0x9cd618  CKAnimatedFx_GetClassID  [inline]
//   [ ] 0x9cd620  CKAnimatedFx_IsKindOfClass  [inline]
#include "k2000/logic/fx/CKAnimatedFx.h"

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"

// 0x005cab08 CKAnimatedFx_PostLoad
int32_t CKAnimatedFx::PostLoad(int32_t /*type*/) {
    ResetState();  // vt+0x50
    return 1;
}

// 0x005ca1b8 CKAnimatedFx_ResetState_maybe
void CKAnimatedFx::ResetState() {
    m_fDelay = -1.0f;  // 0xbf800000
    m_pAttach = nullptr;
    m_bActivatePending = 0;
    m_bPlaying = 0;
    m_unk40 = 0;
    m_unk48 = 0;
    m_pOwner = nullptr;
}

// 0x005ca908 CKAnimatedFx_PlayAnim_maybe (CAnimatedNode_PlayAnim_maybe with no restart: its byte argument is r6 = 0)
void CKAnimatedFx::PlayAnim(float start, int32_t index) {
    const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_unk04);
    m_pRig->m_pNode->PlayAnim(static_cast<double>(start), static_cast<uint32_t>(dictionary->m_apAnimations[index]), 0);
    m_pRig->m_pNode->m_sgProperties &= 0xfffffffbu;  // shown
}

// 0x005ca828 CKAnimatedFx_Play
int32_t CKAnimatedFx::Play(CSGLeaf* owner, SAnimatedFxRig* rig, CSGHotSpot* attach) {
    if (owner == nullptr) return 0;
    m_pOwner = owner;
    m_pAttach = attach;
    if (rig == nullptr || rig->m_pNode == nullptr || m_bPlaying != 0) return 0;
    m_pRig = rig;
    ResetRigTransform();
    PlayAnim(0.0f, 0);  // vt+0x54 (TOC2 -0x5ecc)
    m_bPlaying = 1;
    m_fDelay = 0.0f;
    m_bActivatePending = 1;
    return 1;
}

// 0x005ca4d8 CKAnimatedFx_ResetRigTransform_maybe
void CKAnimatedFx::ResetRigTransform() {
    CAnimatedNode* node = m_pRig->m_pNode;
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    if (m_pAttach != nullptr && static_cast<CSGLeaf*>(m_pAttach->m_pParent) == m_pOwner) {
        m_pAttach->AttachVolume(m_pRig->m_pNode);
    } else {
        static_cast<CSGBranch*>(m_pOwner)->AddChild(m_pRig->m_pNode);  // vt+0x70
        m_pRig->m_pNode->SetIdentity();
    }
    // The node's modelling axes and position before the turns.
    const RwMatrix& m = m_pRig->m_pNode->m_pRwFrame->modelling;
    const CVector3 at = {m.at.x, m.at.y, m.at.z};
    const CVector3 up = {m.up.x, m.up.y, m.up.z};
    const CVector3 right = {m.right.x, m.right.y, m.right.z};
    const CVector3 position = {m.pos.x, m.pos.y, m.pos.z};
    CAnimatedNode* turned = m_pRig->m_pNode;
    float angle = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f * m_unk28;  // TOC2 -0x5ed4
    turned->RotateAboutPoint(angle, &position, &at);
    turned = m_pRig->m_pNode;
    angle = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f * m_unk2c;
    turned->RotateAboutPoint(angle, &position, &up);
    turned = m_pRig->m_pNode;
    angle = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f * m_unk30;
    turned->RotateAboutPoint(angle, &position, &right);
    m_pRig->m_pNode->Scale(&m_unk10.x);
    if (m_unk34 != 0) {
        m_pRig->m_pNode->ForceWorldMatrixUpdate();  // vt+0x50
        CAnimatedNode* moved = m_pRig->m_pNode;
        moved->m_pParent->RemoveChild(moved);  // vt+0x78
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChildKeepWorldTransform(m_pRig->m_pNode);  // vt+0x74
    }
}

// 0x005cb080 CKAnimatedFx_SetFxActive. On: with +0x35 the spark of +0x3c's data under the rig's hot spot (+0x04) is
// taken from the FX pool into +0x40, with +0x36 the particle effect of +0x44's data at that hot spot into +0x48 (null
// when none is free; the inline CKSrvFx_AcquireFx), with +0x37 and the rig's segment hot spots (+0x08 / +0x0c) the
// trail (+0x4c) moves under the rig's node (its old parent's vt+0x78, the node's vt+0x70) and each of its ribbons
// takes the hot spots as its anchors and is switched on (CTrailNodeFx_SetRibbonActive_maybe, inlined). Off: the spark
// stops bursting and the particles stop (each let go, vt+0x54), and every ribbon is switched off with its points
// reset to its anchors (SetRibbonActive inlined with the geometry reset). No rand draw.
void CKAnimatedFx::SetFxActive(int32_t active) {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC2 -0x5ed0 -> engine +0x60
    if (active == 0) {
        if (m_unk40 != nullptr) {
            StopOwnedSparkEffect(static_cast<CKSparkNodeFx*>(m_unk40), this);  // 0x001d4698
            static_cast<IKFx*>(m_unk40)->ReleaseReservation(this);           // vt+0x54
            m_unk40 = nullptr;
        }
        if (m_unk48 != nullptr) {
            StopOwnedParticleEffect(static_cast<IKFx*>(m_unk48), this);  // 0x001cdde8
            static_cast<IKFx*>(m_unk48)->ReleaseReservation(this);       // vt+0x54
            m_unk48 = nullptr;
        }
        if (m_unk4c == nullptr) return;
        const uint32_t count = static_cast<CTrailNodeFx*>(m_unk4c)->m_ui32NbTrail;
        for (uint32_t i = 0; i < count; i = (i + 1) & 0xffu) {
            static_cast<CTrailNodeFx*>(m_unk4c)->SetRibbonActive(i, 0, 1);  // 0x009bdfb8 (inlined)
        }
        return;
    }
    IKSerializable* hotSpot = m_pRig->m_unk04;
    if (m_unk35 != 0 && hotSpot != nullptr && m_unk3c != nullptr) {
        CKSparkFxData* data = static_cast<CKSparkFxData*>(m_unk3c);
        data->m_unk10 = hotSpot;
        data->m_unk0c = nullptr;
        m_unk40 = fx->AcquireFx(data, this);  // the inline pool lookup
    }
    hotSpot = m_pRig->m_unk04;
    if (m_unk36 != 0 && hotSpot != nullptr && m_unk44 != nullptr) {
        CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk44);
        data->m_pAttachHotSpot = hotSpot;
        data->m_pAttachOwner = nullptr;
        m_unk48 = fx->AcquireFx(data, this);
    }
    SAnimatedFxRig* rig = m_pRig;
    if (m_unk37 == 0 || rig->m_unk04 == nullptr || m_unk4c == nullptr || rig->m_pHotSpotA == nullptr ||
        rig->m_pHotSpotB == nullptr) {
        return;
    }
    CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_unk4c);
    if (trail->m_pParent != nullptr) trail->m_pParent->RemoveChild(trail);  // vt+0x78
    if (m_pRig->m_pNode != nullptr) static_cast<CSGBranch*>(m_pRig->m_pNode)->AddChild(static_cast<CTrailNodeFx*>(m_unk4c));  // vt+0x70
    const uint32_t count = static_cast<CTrailNodeFx*>(m_unk4c)->m_ui32NbTrail;
    for (uint32_t i = 0; i < count; i = (i + 1) & 0xffu) {
        CVector3 a;
        CVector3 b;
        m_pRig->m_pHotSpotA->GetWorldPosition(&a);  // 0x000ce790 (through its TocBridge)
        m_pRig->m_pHotSpotB->GetWorldPosition(&b);
        STrailNodeData* ribbon = static_cast<CTrailNodeFx*>(m_unk4c)->m_apTrailData[i];
        ribbon->m_v3Extrem1 = a;
        ribbon->m_v3Extrem2 = b;
        static_cast<CTrailNodeFx*>(m_unk4c)->SetRibbonActive(i, 1, 0);  // 0x009bdfb8 (inlined; on resets the points)
    }
}

// 0x005ca3c8 CKAnimatedFx_UpdateSegmentVolumes_maybe
void CKAnimatedFx::UpdateSegmentVolumes() {
    if (m_unk4c == nullptr) return;
    const uint32_t count = static_cast<CTrailNodeFx*>(m_unk4c)->m_ui32NbTrail;
    if (count == 0) return;
    uint32_t i = 0;
    do {
        CVector3 a;
        CVector3 b;
        m_pRig->m_pHotSpotA->GetWorldPosition(&a);  // 0x000ce790 (through its TocBridge)
        m_pRig->m_pHotSpotB->GetWorldPosition(&b);
        STrailNodeData* ribbon = static_cast<CTrailNodeFx*>(m_unk4c)->m_apTrailData[i];
        ribbon->m_v3Extrem1 = a;
        ribbon->m_v3Extrem2 = b;
        i = (i + 1) & 0xffu;
    } while (count > i);
}

// 0x005ca2d8 CKAnimatedFx_SetOrientation_maybe
void CKAnimatedFx::SetOrientation(const CVector3* at, const CVector3* up) {
    if (m_bPlaying == 0 || m_pRig->m_pNode == nullptr || m_unk34 != 0) return;
    m_pRig->m_pNode->SetOrientationFromAtUp(at, up);  // 0x000d0918
}

// 0x005ca340 CKAnimatedFx_SetPosition (unlike SetOrientation, +0x34 is not read)
void CKAnimatedFx::SetPosition(const CVector3* position) {
    if (m_bPlaying == 0 || m_pRig->m_pNode == nullptr) return;
    RwFrame* frame = m_pRig->m_pNode->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= ~0x20000u;
    RwFrame_MarkDirty(frame);  // TocBridge -> 0x00010698
}

// 0x005cbf48 CKAnimatedFx_Stop_maybe
void CKAnimatedFx::Stop() {
    if (m_bPlaying == 0) return;
    SetFxActive(0);
    m_pRig->m_pNode->m_sgProperties = (m_pRig->m_pNode->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
    m_bActivatePending = 0;
    m_bPlaying = 0;
}

// 0x005cbfb8 CKAnimatedFx_Update
int32_t CKAnimatedFx::Update(float dt) {
    if (m_bPlaying == 0) return 0;
    if (!(m_fDelay <= 0.0f)) {
        m_fDelay = m_fDelay - dt;
        return 1;
    }
    if (m_bActivatePending != 0) {
        SetFxActive(1);
        m_bActivatePending = 0;
    } else {
        UpdateSegmentVolumes();  // 0x005ca3c8's loop, inlined: the trail's ribbons follow the rig's hot spots
    }
    CAnimatedNode* node = m_pRig->m_pNode;
    node->AddAnimTime(static_cast<double>(dt * m_unk0c));
    const float now = m_pRig->m_pNode->GetAnimTimeNow();
    const float duration = m_pRig->m_pNode->GetCurrentAnimDuration();
    if (now <= duration) return 1;
    if (m_bPlaying != 0) {
        SetFxActive(0);
        m_pRig->m_pNode->m_sgProperties = (m_pRig->m_pNode->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
        m_bActivatePending = 0;
        m_bPlaying = 0;
    }
    if (m_unk1c == 0) return 0;
    // Looping: the rig reset, the animation from 0, a random delay base + range * (u / 65535 * -2) (1 rand draw).
    ResetRigTransform();
    PlayAnim(0.0f, 0);  // vt+0x54
    m_bPlaying = 1;
    const float base = m_unk20 + m_unk24;
    m_bActivatePending = 1;
    const float u = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f;
    m_fDelay = ppc::fmadds(u * -2.0f, m_unk24, base);  // TOC2 -0x5ec0
    return 1;
}

// 0x005cab58 CKAnimatedFx_Load
int32_t CKAnimatedFx::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk35);
    ReadU8(file, &m_unk36);
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk3c);
    IKFile_ReadRef(file, &m_unk44);
    ReadF32LE(file, &m_unk0c);
    ReadU8(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk30);
    ReadU8(file, &m_unk34);
    ReadU8(file, &m_unk37);
    IKFile_ReadRef(file, &m_unk4c);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk10), 3);  // one 12-byte read
    return 1;
}
