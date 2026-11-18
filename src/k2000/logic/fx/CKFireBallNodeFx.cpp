// CKFireBallNodeFx.cpp - reconstructed original translation unit: 0x1ba218-0x1bb408 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKFireBallNodeFx  key 0x33cc  category Logic  size 0x38  vtable 0xb1cc58
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1ba218  CKFireBallNodeFx_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x1ba268  RegisterCKFireBallNodeFxClass
//   [ ] 0x1ba2e0  _GLOBAL__I_1ba2e0
//   [x] 0x1ba2f0  CKFireBallNodeFx_PostLoad
//   [x] 0x1ba348  CKFireBallNodeFx_RecursiveRegistration
//   [x] 0x1ba408  CKFireBallNodeFx_Destroy  (CKFireBallNodeFx.h)
//   [x] 0x1ba430  CKFireBallNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1ba4d8  CKFireBallNodeFx_Create  (DOTD_DECLARE_FACTORIES; the constructor in CKFireBallNodeFx.h)
//   [x] 0x1ba530  CKFireBallNodeFx_RequestStopForOwner_maybe  (called by CKProjectileTypeBallisticPFX::OnDeath)
//   [ ] 0x1ba568  FUN_001ba568  [dead]
//   [x] 0x1ba5a8  CKFireBallNodeFx_SetFollowNode  (called by StartFireBall, CKProjectileTypeBallisticPFX.cpp)
//   [x] 0x1ba5e0  CKFireBallNodeFx_SetDirection  (StartFireBall, CKProjectileTypeBallisticPFX::UpdateOrientation)
//   [x] 0x1ba628  CKFireBallNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x1ba6e0  CKFireBallNodeFx_Save
//   [x] 0x1ba828  CKFireBallNodeFx_Stop
//   [x] 0x1ba958  CKFireBallNodeFx_Start
//   [x] 0x1baa80  CKFireBallNodeFx_Load
//   [x] 0x1babb8  CKFireBallNodeFx_Update
//   [ ] 0x1bb338  CKFireBallNodeFx_SetDirectionForOwner_maybe  [dead]
//
//   [x] 0x9ac0d8  CKFireBallNodeFx_IsKindOfClass  [inline]  (CKFireBallNodeFx.h)
//   [x] 0x9ac110  CKFireBallNodeFx_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac118  CKFireBallNodeFx_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac120  CKFireBallNodeFx_GetFxData  [inline]
//   [x] 0x9ac128  CKFireBallNodeFx_SetFxData  [inline]
//   [x] 0x9ac130  CKFireBallNodeFx_Destruct  [inline]  (CKFireBallNodeFx.h)
//   [x] 0x9ac150  CKFireBallNodeFx_DeletingDestruct  [inline]  (CKFireBallNodeFx.h)
#include "k2000/logic/fx/CKFireBallNodeFx.h"

#include <cmath>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKFireBallFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/IKTime.h"

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64

// A frame's modelling position set, the identity flag cleared, the frame marked dirty (inlined throughout).
void SetFramePosition(RwFrame* frame, float x, float y, float z) {
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags &= ~0x20000u;  // rwMATRIXINTERNALIDENTITY
    RwFrame_MarkDirty(frame);
}

// The trail particles stop emitting: properties 0x80000 and 0x400 cleared, the emitter's EMIT flag cleared.
void StopParticleEmission(CParticlesNodeFx* fx) {
    fx->m_sgProperties &= 0xfff7fbffu;
    fx->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
}
}  // namespace

// 0x001baa80 CKFireBallNodeFx_Load: IKNodeFx's; level files then read the trail particles reference, a byte-swapped
// word and one byte straight into the effect's flags.
int32_t CKFireBallNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pParticles);
        ReadU32LE(file, &m_unk2c);
        ReadU8(file, &m_baFxData);
    }
    return 1;
}

// 0x001ba2f0 CKFireBallNodeFx_PostLoad: the node's first geometry gets blend mode 2; no follow node.
int32_t CKFireBallNodeFx::PostLoad(int32_t /*type*/) {
    if (m_pNode != nullptr) static_cast<CGeometry*>(m_pNode->m_lGeometryList)->SetBlendMode(2);
    m_pFollowNode = nullptr;
    return 1;
}

// 0x001ba348 CKFireBallNodeFx_RecursiveRegistration
void CKFireBallNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKNodeFx::RecursiveRegistration(type);
    if (m_pParticles != nullptr) m_pParticles->RecursiveRegistration(type);
}

IKFxData* CKFireBallNodeFx::GetFxData() { return m_pData; }  // 0x009ac120
void CKFireBallNodeFx::SetFxData(IKFxData* data) { m_pData = static_cast<CKFireBallFxData*>(data); }  // 0x009ac128

// 0x001ba530 CKFireBallNodeFx_RequestStopForOwner_maybe
void CKFireBallNodeFx::RequestStopForOwner(const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0) return;
    if (m_pOwner != owner) return;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xf0) | (m_baFxData & 7) | 8);
}

// 0x001ba5a8 CKFireBallNodeFx_SetFollowNode
void CKFireBallNodeFx::SetFollowNode(CSGMovable* node, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0) return;
    if (m_pOwner != owner) return;
    m_pFollowNode = node;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xe0) | (m_baFxData & 0xf));
}

// 0x001ba5e0 CKFireBallNodeFx_SetDirection
void CKFireBallNodeFx::SetDirection(const CVector3* dir, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0) return;
    if (m_pOwner != owner) return;
    const float z = dir->z;
    const float y = dir->y;
    m_vDirection.x = -dir->x;
    m_vDirection.z = -z;
    m_vDirection.y = -y;
}

// 0x001ba828 CKFireBallNodeFx_Stop: stopped; unless bit 5, the trail particles stop emitting and are hidden; bits 3 and 6
// cleared, the node hidden (vt+0x60), no follow node, no direction, no hot spot, bit 4 cleared.
void CKFireBallNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    if ((m_baFxData & 0x20) == 0) {
        CParticlesNodeFx* fx = m_pParticles;
        if (fx != nullptr) {
            StopParticleEmission(fx);
            m_pParticles->m_sgProperties = (m_pParticles->m_sgProperties & ~0x4u) | 0x4u;
        }
    }
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xb7);
    Vf60();
    m_pFollowNode = nullptr;
    m_vDirection = kNullVector;
    m_pHotSpot = nullptr;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xe0) | (m_baFxData & 0xf));
}

// 0x001ba958 CKFireBallNodeFx_Start: with a node: running, alpha 0, fading in (bit 2 set, bit 3 cleared), the node shown
// (vt+0x5c); no direction, no follow node (bit 4 cleared), no hot spot; the node's frame at the origin.
void CKFireBallNodeFx::Vf64() {
    if (m_pNode == nullptr) return;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    m_ui8Alpha = 0;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xf0) | (m_baFxData & 3) | 4);
    Vf5C();
    m_vDirection = kNullVector;
    m_pFollowNode = nullptr;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xe0) | (m_baFxData & 0xf));
    m_pHotSpot = nullptr;
    SetFramePosition(m_pNode->m_pRwFrame, kNullVector.x, kNullVector.y, kNullVector.z);
}

// 0x001babb8 CKFireBallNodeFx_Update. Without a node: Stop (vt+0x6c). The node's UV scrolls (dt times the data's U / V
// speeds, fused, wrapped to 0 past 1; ble: NaN kept). Orientation: with no direction (all three components == 0) the node
// takes the follow node's modelling matrix, or the hot spot's world matrix; with one, the node's right axis
// (normalised unless its length is 0) against the direction: |dot| >= 0.01 (bge: NaN too) rebuilds the basis from the
// direction as up and the node's `at` (normalised unless 0) as forward, else from the direction as up and the right axis
// as `at`. Position: the hot spot's world position (bit 4 and a hot spot), else the follow node's; the trail particles
// (bit 6, not bit 5) are moved with it. Scale (data +0x10, +0x14, +0x10). Fades: out (bit 3) alpha - dt * data +0x1c
// (bit 5 also stops the particles' emission), below 0 (blt) alpha 0 and Stop; in (bit 2) alpha + dt * data +0x18
// (fused), past 255 (ble: NaN not) alpha 0xff and the particles shown and emitting (bit 6 set). The first geometry gets the
// alpha (blending unless 0xff, or flagged 0x1000 with material mode 1..6).
void CKFireBallNodeFx::Update(IKTime* frameClock) {
    if (m_pNode == nullptr) {
        Stop();  // vt+0x6c
        return;
    }
    const float dt = frameClock->m_afDeltaTime[0];
    CGeometry* geometry = static_cast<CGeometry*>(m_pNode->m_lGeometryList);
    CMatrix34* uv = static_cast<CMaterial*>(geometry->m_pMaterial)->GetUVTransformMatrix();
    const float one = 1.0f;  // TOC -0x205c
    float u = ppc::fmadds(dt, m_pData->m_unk0c, uv->m_pos.x);
    const float v0 = uv->m_pos.y;
    const float w = uv->m_pos.z;
    if (u > one) u = 0.0f;
    float v = ppc::fmadds(dt, m_pData->m_unk08, v0);
    if (v > one) v = 0.0f;
    uv->m_pos.x = u;
    uv->m_pos.y = v;
    uv->m_pos.z = w;
    uv->m_ui32Flags &= ~0x20000u;

    if (m_vDirection.x == kNullVector.x && m_vDirection.y == kNullVector.y && m_vDirection.z == kNullVector.z) {
        if (m_pFollowNode != nullptr) {
            m_pNode->SetLocalMatrix(&m_pFollowNode->m_pRwFrame->modelling);
        } else if (m_pHotSpot != nullptr) {
            alignas(16) CMatrix34 matrix;
            m_pHotSpot->GetWorldMatrix(&matrix);
            m_pNode->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));
        }
    } else {
        const RwMatrix& modelling = m_pNode->m_pRwFrame->modelling;
        CVector3 right = {modelling.right.x, modelling.right.y, modelling.right.z};
        const float len = std::sqrt(ppc::fmadds(right.z, right.z, ppc::fmadds(right.x, right.x, right.y * right.y)));
        if (len != 0.0f) {
            const float inv = one / len;
            right.z = right.z * inv;
            right.x = right.x * inv;
            right.y = right.y * inv;
        }
        const float dot =
            ppc::fmadds(m_vDirection.z, right.z, ppc::fmadds(m_vDirection.x, right.x, m_vDirection.y * right.y));
        if (!(std::fabs(dot) < 0.01f)) {  // bge
            const RwMatrix& m = m_pNode->m_pRwFrame->modelling;
            CVector3 at = {m.at.x, m.at.y, m.at.z};
            const float atLen = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
            if (atLen != 0.0f) {
                const float inv = one / atLen;
                at.z = at.z * inv;
                at.x = at.x * inv;
                at.y = at.y * inv;
            }
            m_pNode->SetBasisFromUpAndForward(&m_vDirection, &at);
        } else {
            m_pNode->SetOrientationFromUpAt(&m_vDirection, &right);
        }
    }

    if ((m_baFxData & 0x10) != 0 && m_pHotSpot != nullptr) {
        CVector3 pos;
        m_pHotSpot->GetWorldPosition(&pos);
        SetFramePosition(m_pNode->m_pRwFrame, pos.x, pos.y, pos.z);
        if (((m_baFxData >> 6) & 1) != 0 && (m_baFxData & 0x20) == 0) {
            SetFramePosition(m_pParticles->m_pRwFrame, pos.x, pos.y, pos.z);
        }
    } else if (m_pFollowNode != nullptr) {
        const RwV3d& p = m_pFollowNode->m_pRwFrame->modelling.pos;
        SetFramePosition(m_pNode->m_pRwFrame, p.x, p.y, p.z);
        if (((m_baFxData >> 6) & 1) != 0 && ((m_baFxData >> 5) & 1) == 0) {
            const RwV3d& q = m_pFollowNode->m_pRwFrame->modelling.pos;
            SetFramePosition(m_pParticles->m_pRwFrame, q.x, q.y, q.z);
        }
    }
    m_pNode->ScaleXYZ(m_pData->m_unk10, m_pData->m_unk14, m_pData->m_unk10);

    const uint8_t bits = m_baFxData;
    if (((bits >> 3) & 1) != 0) {
        const float a = static_cast<float>(m_ui8Alpha) - dt * m_pData->m_unk1c;
        if (((bits >> 5) & 1) != 0 && m_pParticles != nullptr) StopParticleEmission(m_pParticles);
        m_baFxData = static_cast<uint8_t>(m_baFxData & ~0x40);
        if (a < 0.0f) {
            m_ui8Alpha = 0;
            m_baFxData = static_cast<uint8_t>(m_baFxData & ~0x08);
            Stop();  // vt+0x6c
        } else {
            m_ui8Alpha = static_cast<uint8_t>(ppc::fctiwz(a));
        }
    } else if (((bits >> 2) & 1) != 0) {
        const float a = ppc::fmadds(dt, m_pData->m_unk18, static_cast<float>(m_ui8Alpha));
        if (!(a > 255.0f)) {
            m_ui8Alpha = static_cast<uint8_t>(ppc::fctiwz(a));
        } else {
            m_ui8Alpha = 0xff;
            m_baFxData = static_cast<uint8_t>(m_baFxData & ~0x04);
            if ((m_baFxData & 0x20) == 0 && m_pParticles != nullptr) {
                m_pParticles->m_sgProperties &= ~0x4u;
                CParticlesNodeFx* fx = m_pParticles;
                fx->m_sgProperties = (fx->m_sgProperties | 0x400u) & ~0x80000u;
                fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
                fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
            }
            m_baFxData = static_cast<uint8_t>((m_baFxData & ~0x40) | 0x40);
        }
    }

    CGeometry* first = static_cast<CGeometry*>(m_pNode->m_lGeometryList);
    uint8_t alpha = m_ui8Alpha;
    uint32_t blend = 0;
    if (alpha != 0xff) {
        blend = 1;
        if ((first->m_BitProperties & 0x1000u) != 0) {
            const int32_t mode = static_cast<int32_t>((static_cast<CMaterial*>(first->m_pMaterial)->m_baProperties >> 3) & 0xfu);
            if (mode > 0 && mode <= 6) {
                alpha = 0xff;
                blend = 0;
            }
        }
    }
    first->m_cGeometryColor[3] = alpha;
    const uint32_t properties = first->m_BitProperties;
    if (((properties >> 11) & 1u) == blend) return;
    first->m_BitProperties = (properties & 0xfffff7ffu) | (blend << 11);
    first->UpdateProperties();  // vt+0x60
}
