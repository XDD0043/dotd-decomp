// CKPurpleCombo.cpp - reconstructed original translation unit 0x3c1f38-0x3c5af0 (GAME_TOC1, main_toc1), 30 functions, 30 live.
// Primary class: CKPurpleCombo  key 0xa48c  category Logic  size 0x25c  vtable 0xb23e68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3c1f38  CKPurpleCombo_Delete
//   [x] 0x3c1f88  CKPurpleCombo_GetAbilityId  (header)
//   [x] 0x3c1f90  CKPurpleCombo_GetFamilyId  (header)
//   [x] 0x3c1f98  CKPurpleCombo_SetAttackActive_maybe
//   [x] 0x3c2048  CKPurpleCombo_IsGroundTrailActive_maybe
//   [x] 0x3c20a8  CKPurpleCombo_End
//   [x] 0x3c2138  CKPurpleCombo_Update  (header)
//   [x] 0x3c2160  CKPurpleCombo_Start
//   [x] 0x3c21d0  CKPurpleCombo_ResetRuntime
//   [x] 0x3c2220  CKPurpleCombo_RecursiveRegistration  (header)
//   [x] 0x3c2248  CKPurpleCombo_Destroy  (inherited: CKAttackMoveElement_Destroy)
//   [x] 0x3c2270  CKPurpleCombo_Construct
//   [x] 0x3c22a8  CKPurpleCombo_Construct_2  (the constructor's second C++ variant)
//   [x] 0x3c22e0  CKPurpleCombo_DeleteArray
//   [x] 0x3c2380  CKPurpleCombo_DeletingDestructor  (the destructor; delete)
//   [x] 0x3c23c8  CKPurpleCombo_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3c23f8  CKPurpleCombo_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x3c2428  RegisterCKPurpleComboClass
//   [ ] 0x3c24b0  _GLOBAL__D_3c24b0
//   [ ] 0x3c24c0  _GLOBAL__I_3c24c0
//   [x] 0x3c24d0  CKPurpleCombo_PostLoad
//   [x] 0x3c25a0  CKPurpleCombo_SteerTowardsTarget_maybe
//   [x] 0x3c26d0  CKPurpleCombo_StopFxAndAttack
//   [x] 0x3c27b8  CKPurpleCombo_CreateArray
//   [x] 0x3c2868  CKPurpleCombo_Create
//   [x] 0x3c28c0  CKPurpleCombo_UpdateAttack_maybe
//   [x] 0x3c3048  CKPurpleCombo_Load
//   [ ] 0x3c3880  CKPurpleCombo_Save
//   [x] 0x3c4158  CKPurpleCombo_UpdateMovement_maybe
//   [x] 0x3c48e0  CKPurpleCombo_SetFxActive
//
//   [ ] 0x9c01b0  CKPurpleCombo_IsKindOfClass  [inline]
//   [ ] 0x9c0200  CKPurpleCombo_GetClassType  [inline]
//   [ ] 0x9c0208  CKPurpleCombo_GetClassID  [inline]
//   [ ] 0x9c0210  CKPurpleCombo_StartEmitterFx  [inline]
#include "k2000/logic/CKPurpleCombo.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKExplosionFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKTimeScalingFxData.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "platform/fps.h"

// 0x003c3048 CKPurpleCombo_Load: CKAttackMoveElement's data, then (type 0 only) 160 bytes: six references,
// three passes over seven per-index fields, two floats and five references.
int32_t CKPurpleCombo::Load(IKFile* file, int32_t type) {
    CKAttackMoveElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_pStartExplosionLow);
        IKFile_ReadRef(file, &m_pDashMesh);
        IKFile_ReadRef(file, &m_pTrailNode);
        IKFile_ReadRef(file, &m_pAimCamembert);
        IKFile_ReadRef(file, &m_pStartExplosionMax);
        IKFile_ReadRef(file, &m_pAnimFxCollection);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_afHitSphereRadius[i]);
            ReadS32LE(file, &m_ai32MeshHoldAlpha[i]);
            ReadS32LE(file, &m_ai32MeshStartAlpha[i]);
            ReadS32LE(file, &m_ai32MeshEndAlpha[i]);
            ReadF32LE(file, &m_afMeshSpinDegPerSec[i]);
            ReadF32LE(file, &m_afSteerConeDeg[i]);
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_avMeshScale[i]), 3);
        }
        ReadF32LE(file, &m_fFadeInTime);
        ReadF32LE(file, &m_fFadeOutTime);
        IKFile_ReadRef(file, &m_pHitExplosionLevel3);
        IKFile_ReadRef(file, &m_pHitExplosion);
        IKFile_ReadRef(file, &m_unk230);
        IKFile_ReadRef(file, &m_unk234);
        IKFile_ReadRef(file, &m_unk238);
    }
    return 1;
}

// C2.8 port-all P03: the purple combo's own methods.

namespace {
constexpr float kDegToRad = 0x1.1df468p-6f;  // TOC +0x3c60 0x3c8efa34

// The inlined pooled explosion of the purple combo: `data`'s effect reserved for the combo (CKSrvFx::AcquireFx), put at
// the host's hot spot `spot` (vt+0xd0), turned along the user's forward (vt+0x18), triggered and released (vt+0x54).
CKExplosionNodeFx* FireExplosion(CKPurpleCombo* combo, IKSerializable* data, uint32_t spot) {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(reinterpret_cast<IKFxData*>(data), combo));
    if (fx == nullptr) return nullptr;
    const CVector3 position = combo->m_pHost->GetHotspotPosition(spot);  // vt+0xd0
    fx->SetTranslation(&position, combo);                                 // 0x001b66e8
    const CVector3 forward = combo->m_pHost->GetHeroForward();            // vt+0x18
    fx->SetDirection(&forward, combo);                                    // 0x001b5e20
    fx->Trigger(combo, nullptr);                                          // 0x001b82a8
    fx->ReleaseReservation(combo);                                        // vt+0x54
    return fx;
}
}  // namespace

// 0x003c24d0 CKPurpleCombo_PostLoad
int32_t CKPurpleCombo::PostLoad(int32_t type) {
    CKAttackMoveElement::PostLoad(type);  // 0x00376e60
    if (m_pDashMesh == nullptr) return 1;
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pDashMesh), 1, 0, 0);  // 0x005832a8 (TocBridge)
    CSGLeaf* trail = static_cast<CSGLeaf*>(m_pTrailNode);
    if (trail == nullptr) return 1;
    if (trail->m_pParent != nullptr) trail->m_pParent->RemoveChild(trail);  // vt+0x78
    static_cast<CSGBranch*>(m_pDashMesh)->AddChild(static_cast<CSGLeaf*>(m_pTrailNode));  // vt+0x70
    return 1;
}

// 0x003c21d0 CKPurpleCombo_ResetRuntime
void CKPurpleCombo::ResetRuntime(int32_t type) {
    CKAttackMoveElement::ResetRuntime(type);  // 0x003756d0
    m_ui8HotSpotIndex = 4;
    m_fLevel3ReaimDelay = 0.0f;  // stw 0
    m_bLevel3ReaimPending = 0;
    m_pActiveParticles = nullptr;
    m_bMeshFadedIn = 0;
}

// 0x003c2160 CKPurpleCombo_Start
void CKPurpleCombo::Start(CKS08AbilityHostBase* host) {
    CKAttackMoveElement::Start(host);  // 0x003760b0
    m_pHost->GetHotspot(m_ui8HotSpotIndex);     // vt+0xcc, the answer unused
    m_bLevel3ReaimPending = 0;
    m_fLevel3ReaimDelay = 0.0f;  // stw 0
    m_bMeshFadedIn = 0;
}

// 0x003c20a8 CKPurpleCombo_End
void CKPurpleCombo::End(int32_t forced) {
    m_pHost->SetHero1d20(1.0f);  // vt+0x84 (r4 = this); TOC +0x3c1c
    CKAttackMoveElement::End(forced);  // 0x00374ee0
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pDashMesh), 1, 0, 0);  // 0x005832a8 (TocBridge)
}

// 0x003c1f98 CKPurpleCombo_SetAttackActive_maybe
void CKPurpleCombo::SetAttackActive(uint8_t on) {
    ApplyDamageParams(0);  // vt+0x88 (one Rand_Int)
    m_pHost->SetAbilityAttackSpheres(this, on, m_afHitSphereRadius[m_ui32LevelIndex], m_pElementDamage, 1.0f, nullptr);  // vt+0xfc
}

// 0x003c2048 CKPurpleCombo_IsGroundTrailActive_maybe
uint8_t CKPurpleCombo::IsGroundTrailActive() {
    if (m_ui32LevelIndex <= 1) return 0;
    return m_pHost->IsOnGround();  // vt+0x30
}

// 0x003c25a0 CKPurpleCombo_SteerTowardsTarget_maybe. The null vector is the constant at 0xc50d64 (fcmpu: a NaN
// component differs).
void CKPurpleCombo::SteerTowardsTarget(const CVector3* direction) {
    CVector3 dir = *direction;
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f) {
        dir = m_pHost->ComputeAimDirection(m_afSteerConeDeg[m_ui32LevelIndex] * kDegToRad, this, m_pAimCamembert);  // vt+0x58
        m_pHost->SetHeroActionPermission(1, 0, 0, 0);                                     // vt+0x44
    }
    CKAttackMoveElement::SteerTowardsTarget(&dir);  // 0x00376eb0
}

// 0x003c26d0 CKPurpleCombo_StopFxAndAttack
void CKPurpleCombo::StopFxAndAttack() {
    CKAttackMoveElement::StopFxAndAttack();  // 0x00374e60
    CSGLeaf* mesh = static_cast<CSGLeaf*>(m_pDashMesh);
    if (mesh != nullptr) {
        m_bMeshFadedIn = 0;
        mesh->m_sgProperties = (mesh->m_sgProperties & ~7u) | 4u;  // rlwinm 29,1,31 / rlwinm 3,0,31, ori 4
    }
    m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc (r7 = r9 = 0)
    m_pHost->SetHero1d20(1.0f);                                                // vt+0x84
}

// 0x003c48e0 CKPurpleCombo_SetFxActive
void CKPurpleCombo::SetFxActive(uint8_t on) {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (on == 0) {
        TransformFx::ReleaseParticles(&m_pActiveParticles, this);  // StopOwnedParticleEffect 0x1cdde8, vt+0x54
        if (m_pAnimFxCollection != nullptr) static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection)->Stop();  // 0x005cc990 (TocBridge)
        CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pTrailNode);
        if (trail == nullptr) return;
        // Every ribbon of the trail off, its points laid out again (CTrailNodeFx_SetRibbonActive_maybe, inlined).
        const uint32_t count = trail->m_ui32NbTrail;
        for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 0, 1);
        return;
    }
    SetAttackActive(1);  // vt+0x74
    const uint32_t level = m_ui32LevelIndex;
    IKSerializable* const particles[3] = {m_unk230, m_unk234, m_unk238};
    CKParticlesEffectFxData* loop = static_cast<CKParticlesEffectFxData*>(particles[level]);
    loop->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpotIndex);  // vt+0xcc
    loop->m_pAttachOwner = nullptr;
    m_pActiveParticles = fxService->AcquireFx(reinterpret_cast<IKFxData*>(particles[m_ui32LevelIndex]), this);
    FireExplosion(this, m_ui32LevelIndex < 2 ? m_pStartExplosionLow : m_pStartExplosionMax, 1);
    if (m_ui32LevelIndex > 1) {
        CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
        CSGLeaf* owner = TransformFx::OwnerNode(m_pHost);              // vt+0x08, +0x1c
        SAnimatedFxRig* rigs = TransformFx::AttachmentSets(m_pHost);  // vt+0x104
        collection->Play(owner, rigs, static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpotIndex)));  // 0x005cc528 (TocBridge)
    }
    if (m_pDashMesh != nullptr) {
        CSGLeaf* mesh = static_cast<CSGLeaf*>(m_pDashMesh);
        if (mesh->m_pParent != nullptr) mesh->m_pParent->RemoveChild(mesh);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpotIndex))->AttachVolume(static_cast<CSGLeaf*>(m_pDashMesh));  // 0x000ce2b8
        static_cast<CSGMovable*>(m_pDashMesh)->Scale(reinterpret_cast<const float*>(&m_avMeshScale[m_ui32LevelIndex]));  // 0x000d0d88
        static_cast<CSGLeaf*>(m_pDashMesh)->m_sgProperties &= ~4u;
        CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pDashMesh)->m_lGeometryList);
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_BitProperties = (geometry->m_BitProperties & ~0x3fu) | 0x2cu;
            TransformFx::SetGeometryAlpha(geometry, static_cast<uint8_t>(m_ai32MeshStartAlpha[m_ui32LevelIndex]));
        }
    }
    CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pTrailNode);
    if (trail == nullptr) return;
    if (m_pDashMesh != nullptr) static_cast<CSGLeaf*>(m_pDashMesh)->ForceWorldMatrixUpdate();  // vt+0x50
    // Every ribbon of the trail on (CTrailNodeFx_SetRibbonActive_maybe 0x009bdfb8, inlined).
    const uint32_t count = static_cast<CTrailNodeFx*>(m_pTrailNode)->m_ui32NbTrail;
    for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 1, 1);
}

// 0x003c28c0 CKPurpleCombo_UpdateAttack_maybe
void CKPurpleCombo::UpdateAttack(float dt) {
    if (m_pDashMesh != nullptr) {
        CNode* mesh = static_cast<CNode*>(m_pDashMesh);
        const float t = m_fElapsedTime;
        const float fadeIn = m_fFadeInTime;
        if (t < fadeIn) {
            // Fading in: the alpha from +0x1c0[level] to +0x1b4[level].
            if (mesh->m_lGeometryList != nullptr) {
                const float k = (fadeIn - t) / fadeIn;
                const float to = static_cast<float>(m_ai32MeshHoldAlpha[m_ui32LevelIndex]) * (t / fadeIn);
                const float a = ppc::fmadds(static_cast<float>(m_ai32MeshStartAlpha[m_ui32LevelIndex]), k, to);
                TransformFx::SetGeometriesAlpha(mesh, static_cast<uint8_t>(ppc::fctiwz(a)));
            }
        } else if (m_bMeshFadedIn == 0) {
            // bge: the fade-in over (or a NaN): the full alpha +0x1b4[level], once.
            if (mesh->m_lGeometryList != nullptr) {
                TransformFx::SetGeometriesAlpha(mesh, static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(m_ai32MeshHoldAlpha[m_ui32LevelIndex]))));
            }
            m_bMeshFadedIn = 1;
        }
        const float t2 = m_fElapsedTime;
        const float fadeOut = m_fFadeOutTime;
        const float duration = m_afAttackDuration[m_ui32LevelIndex];
        mesh = static_cast<CNode*>(m_pDashMesh);
        if (t2 >= duration - fadeOut && m_bMeshFadedIn != 0 && mesh->m_lGeometryList != nullptr &&
            // --fps N (not in the original): the fade-out re-reads the alpha it wrote, so it compounds per update: step
            // it once per 60 Hz frame only, as at 60 fps.
            (!dotd::fps::Unlocked() || dotd::fps::Ticks() > 0) && true) {
            // Fading out: from the first geometry's alpha (kept in +0x24c) to +0x1cc[level].
            const float left = duration - t2;
            const uint8_t current = static_cast<CGeometry*>(mesh->m_lGeometryList)->m_cGeometryColor[3];
            const float k = (fadeOut - left) / fadeOut;
            m_ui32LastFadeOutAlpha = current;
            const float from = left / fadeOut;
            const float to = static_cast<float>(m_ai32MeshEndAlpha[m_ui32LevelIndex]) * k;
            const float a = ppc::fmadds(static_cast<float>(current), from, to);
            TransformFx::SetGeometriesAlpha(mesh, static_cast<uint8_t>(ppc::fctiwz(a)));
        }
        // The spin: the frame's modelling matrix with its rotation replaced by +0x1d8[level] * t degrees about Z (the
        // angle brought into [-360, 360)), the position kept, then scaled by +0x1e4[level].
        RwFrame* frame = static_cast<CSGMovable*>(m_pDashMesh)->m_pRwFrame;
        CMatrix34 matrix;
        std::memcpy(&matrix, &frame->modelling, sizeof(matrix));
        float angle = m_afMeshSpinDegPerSec[m_ui32LevelIndex] * m_fElapsedTime;
        while (angle < -360.0f) angle = angle + 720.0f;   // TOC +0x3c74 / +0x3c78
        while (angle >= 360.0f) angle = angle - 720.0f;   // TOC +0x3c7c
        const CVector3 position = matrix.m_pos;
        matrix.m_right = CVector3{1.0f, 0.0f, 0.0f};
        matrix.m_ui32Flags = 0x20003;
        matrix.m_up = CVector3{0.0f, 1.0f, 0.0f};
        matrix.m_at = CVector3{0.0f, 0.0f, 1.0f};
        matrix.m_pos = CVector3{0.0f, 0.0f, 0.0f};
        Mat4_RotateLocalZDeg(angle, &matrix);  // 0x002419c0
        matrix.m_pos = position;
        matrix.m_ui32Flags &= ~0x20000u;
        RwMatrixScalePreConcat_Thunk(&matrix, reinterpret_cast<const CVector3*>(&m_avMeshScale[m_ui32LevelIndex]));  // 0x0023f670
        static_cast<CSGMovable*>(m_pDashMesh)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    }
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
    if (collection->m_bPlaying != 0) collection->Update(dt);  // 0x005cccb0 (TocBridge)
}

// 0x003c4158 CKPurpleCombo_UpdateMovement_maybe. The host's vt+0xf0 gets this in r4 (dotd's slot takes no argument).
void CKPurpleCombo::UpdateMovement(float dt) {
    if (m_ui32LevelIndex == 3) {
        const uint8_t hit = m_pHost->VfF0();  // vt+0xf0
        if (hit == 0) {
            if (m_bLevel3ReaimPending == 0) return;
            m_fLevel3ReaimDelay = m_fLevel3ReaimDelay - dt;
            if (!(m_fLevel3ReaimDelay <= 0.0f)) return;  // cror eq,lt: NaN returns
            m_pHost->ComputeAimDirection(m_afSteerConeDeg[m_ui32LevelIndex] * kDegToRad, this, m_pAimCamembert);  // vt+0x58, the answer unused
            m_pHost->SetHeroActionPermission(1, 0, 0, 0);                              // vt+0x44
            m_bLevel3ReaimPending = 0;
            return;
        }
        m_bLevel3ReaimPending = 1;
        m_pHost->SetHeroActionPermission(1, 1, 1, 1);  // vt+0x44
        m_fLevel3ReaimDelay = 0.0f;  // stw 0
        CKExplosionNodeFx* fx = FireExplosion(this, m_pHitExplosionLevel3, m_ui8HotSpotIndex);
        if (fx == nullptr) return;
        // The delay: the time scaling (sub-effect type 6) of the explosion, its +0x0c. BUG(original): asked after the
        // reservation was released (vt+0x54 in FireExplosion), so the lookup's owner test fails and the delay stays 0.
        IKSerializable* scaling = fx->GetNthSubEffectOfType(6, this, 0);  // 0x001b6530
        if (scaling == nullptr) return;
        m_fLevel3ReaimDelay = static_cast<CKTimeScalingFxData*>(scaling)->m_fDuration;
        return;
    }
    if (m_pHost->VfF0() == 0) return;  // vt+0xf0
    FireExplosion(this, m_pHitExplosion, m_ui8HotSpotIndex);
}
