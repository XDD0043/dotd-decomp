// CKCometDash.cpp - reconstructed original translation unit 0x385a78-0x389ec8 (GAME_TOC1, main_toc1), 30 functions, 30 live.
// Primary class: CKCometDash  key 0x9a4c  category Logic  size 0x264  vtable 0xb23620
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x385a78  CKCometDash_Delete
//   [x] 0x385ac8  CKCometDash_GetAbilityId
//   [x] 0x385ad0  CKCometDash_GetFamilyId
//   [x] 0x385ad8  CKCometDash_SetAttackActive_maybe
//   [x] 0x385b88  CKCometDash_IsGroundTrailActive_maybe
//   [x] 0x385be8  CKCometDash_End
//   [x] 0x385c78  CKCometDash_StopFxAndAttack
//   [x] 0x385d60  CKCometDash_Update  (the base's only: CKAttackMoveElement_Update)
//   [x] 0x385d88  CKCometDash_Start
//   [x] 0x385df8  CKCometDash_ResetRuntime
//   [x] 0x385e50  CKCometDash_RecursiveRegistration  (the base's only: returns 1)
//   [x] 0x385e78  CKCometDash_Destroy  (inherited: CKAttackMoveElement_Destroy)
//   [x] 0x385ea0  CKCometDash_Construct
//   [x] 0x385ed8  CKCometDash_Construct_2  (the constructor)
//   [x] 0x385f10  CKCometDash_DeleteArray
//   [x] 0x385fb0  CKCometDash_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x385ff8  CKCometDash_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x386028  CKCometDash_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x386058  RegisterCKCometDashClass
//   [ ] 0x3860e0  _GLOBAL__D_3860e0
//   [ ] 0x3860f0  _GLOBAL__I_3860f0
//   [x] 0x386100  CKCometDash_PostLoad
//   [x] 0x386220  CKCometDash_SteerTowardsTarget_maybe
//   [x] 0x386350  CKCometDash_CreateArray
//   [x] 0x386400  CKCometDash_Create
//   [x] 0x386458  CKCometDash_UpdateAttack_maybe
//   [x] 0x386be0  CKCometDash_Load
//   [ ] 0x387730  CKCometDash_Save
//   [x] 0x3882d0  CKCometDash_UpdateMovement_maybe
//   [x] 0x388a58  CKCometDash_SetFxActive
//
//   [ ] 0x9bfa68  CKCometDash_IsKindOfClass  [inline]
//   [ ] 0x9bfab8  CKCometDash_GetClassType  [inline]
//   [ ] 0x9bfac0  CKCometDash_GetClassID  [inline]
//   [ ] 0x9bfac8  CKCometDash_StartEmitterFx  [inline]
#include "k2000/logic/CKCometDash.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/logic/fx/CKTimeScalingFxData.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "platform/fps.h"

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x3408)
constexpr float kOne = 1.0f;                      // TOC +0x33c4
constexpr float kDegToRad = 0.0174532905f;        // TOC +0x340c (0x3c8efa34)
constexpr float kAngleLow = -360.0f;              // TOC +0x3420
constexpr float kAngleTurn = 720.0f;              // TOC +0x3424
constexpr float kAngleHigh = 360.0f;              // TOC +0x3428

// The per-level particle data (+0x230, +0x234, +0x238: three references read one after the other).
IKSerializable* LevelParticles(const CKCometDash* d, uint32_t level) {
    return level == 0 ? d->m_unk230 : level == 1 ? d->m_unk234 : d->m_unk238;
}

// A pooled explosion of `data` (the inlined CKSrvFx::AcquireFx) put at the host's hot spot `hotSpot`, turned to the
// hero's forward (host vt+0x18), triggered and released; the explosion (or null).
CKExplosionNodeFx* FireExplosion(CKCometDash* d, IKSerializable* data, uint32_t hotSpot) {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    CKExplosionNodeFx* burst = static_cast<CKExplosionNodeFx*>(fx->AcquireFx(static_cast<IKFxData*>(data), d));
    if (burst == nullptr) return nullptr;
    const CVector3 position = d->m_pHost->GetHotspotPosition(hotSpot);  // vt+0xd0
    burst->SetTranslation(&position, d);                                 // 0x001b66e8
    const CVector3 forward = d->m_pHost->GetHeroForward();               // vt+0x18
    burst->SetDirection(&forward, d);                                    // 0x001b5e20
    burst->Trigger(d, nullptr);                                          // 0x001b82a8
    burst->ReleaseReservation(d);                                        // vt+0x54
    return burst;
}

// The mesh's geometries take `alpha` (the inlined walk: CKTransformElement.h's TransformFx::SetGeometriesAlpha), when
// the mesh has any.
void SetMeshAlpha(IKSerializable* mesh, float value) {
    if (static_cast<CNode*>(mesh)->m_lGeometryList == nullptr) return;
    TransformFx::SetGeometriesAlpha(mesh, static_cast<uint8_t>(ppc::fctiwz(value)));
}
}  // namespace

// 0x00385ad8 CKCometDash_SetAttackActive_maybe: the damage parameters (vt+0x88, one rand draw), then the host's attack
// sphere `on` with the level's radius (+0x1a8) and the damage (+0x19c).
void CKCometDash::SetAttackActive(uint8_t on) {
    ApplyDamageParams(0);  // vt+0x88
    m_pHost->SetAbilityAttackSpheres(this, on, m_afHitSphereRadius[m_ui32LevelIndex], m_pElementDamage, kOne, nullptr);  // vt+0xfc
}

// 0x00385b88 CKCometDash_IsGroundTrailActive_maybe: above level index 1, while airborne (host vt+0x30).
uint8_t CKCometDash::IsGroundTrailActive() {
    if (m_ui32LevelIndex > 1) return m_pHost->IsOnGround();
    return 0;
}

// 0x00385be8 CKCometDash_End: the host's +0x1d20 back to 1 (vt+0x84), the base's End, the mesh shown under sector 0.
void CKCometDash::End(int32_t forced) {
    m_pHost->SetHero1d20(kOne);  // vt+0x84
    CKAttackMoveElement::End(forced);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pDashMesh), 1, 0, 0);  // 0x0098f340
}

// 0x00385c78 CKCometDash_StopFxAndAttack: the base's, the mesh hidden (not faded in), the attack sphere off, the host's
// +0x1d20 back to 1.
void CKCometDash::StopFxAndAttack() {
    CKAttackMoveElement::StopFxAndAttack();  // 0x00374e60
    CSGLeaf* mesh = static_cast<CSGLeaf*>(m_pDashMesh);
    if (mesh != nullptr) {
        m_bMeshFadedIn = 0;
        mesh->m_sgProperties = (mesh->m_sgProperties & 0xfffffffbu) | 4u;
    }
    m_pHost->SetAbilityAttackSpheres(this, 0, kOne, nullptr, kOne, nullptr);  // vt+0xfc
    m_pHost->SetHero1d20(kOne);                                               // vt+0x84
}

// 0x00385d88 CKCometDash_Start: the base's, the hot spot asked (the result unused), the runtime cleared.
void CKCometDash::Start(CKS08AbilityHostBase* host) {
    CKAttackMoveElement::Start(host);  // 0x003760b0
    m_pHost->GetHotspot(m_ui8HotSpotIndex);    // vt+0xcc (unused)
    m_bHitHeld = 0;
    m_fHitSlowdownTimer = 0.0f;  // (a word store of 0)
    m_bMeshFadedIn = 0;
}

// 0x00385df8 CKCometDash_ResetRuntime: the base's, the hot spot 4, the runtime and the running effects cleared.
void CKCometDash::ResetRuntime(int32_t type) {
    CKAttackMoveElement::ResetRuntime(type);  // 0x003756d0
    m_ui8HotSpotIndex = 4;
    m_fHitSlowdownTimer = 0.0f;  // (a word store of 0)
    m_bHitHeld = 0;
    m_pActiveParticles = nullptr;
    m_pActiveSparks = nullptr;
    m_bMeshFadedIn = 0;
}

// 0x00386100 CKCometDash_PostLoad: the base's (ResetRuntime), the mesh shown under sector 0; the trail taken off its
// parent and hung under the mesh (or, without one, the dynamic scene root).
int32_t CKCometDash::PostLoad(int32_t type) {
    CKAttackMoveElement::PostLoad(type);  // 0x00376e60
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pDashMesh), 1, 0, 0);
    CSGLeaf* trail = static_cast<CSGLeaf*>(m_pTrailNode);
    if (trail == nullptr) return 1;
    if (trail->m_pParent != nullptr) trail->m_pParent->RemoveChild(trail);  // vt+0x78
    CSGBranch* parent = m_pDashMesh != nullptr ? static_cast<CSGBranch*>(m_pDashMesh)
                                            : static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
    parent->AddChild(static_cast<CSGLeaf*>(m_pTrailNode));  // vt+0x70
    return 1;
}

// 0x00386220 CKCometDash_SteerTowardsTarget_maybe: for the null direction the host aims (vt+0x58: the level's cone
// +0x210 in degrees, the aim cone +0x21c) and action 1 is forbidden (vt+0x44); then the base's along the result.
void CKCometDash::SteerTowardsTarget(const CVector3* direction) {
    CVector3 at = *direction;
    if (kNullVector.x == at.x && kNullVector.y == at.y && kNullVector.z == at.z) {
        at = m_pHost->ComputeAimDirection(m_afSteerConeDeg[m_ui32LevelIndex] * kDegToRad, this, m_pAimCamembert);  // vt+0x58
        m_pHost->SetHeroActionPermission(1, 0, 0, 0);                                       // vt+0x44
    }
    CKAttackMoveElement::SteerTowardsTarget(&at);  // 0x00376eb0
}

// 0x00386458 CKCometDash_UpdateAttack_maybe. The mesh (+0x24c) fades in over +0x208 s from the level's alpha +0x1c0 to
// +0x1b4 (then marked faded in, +0x258), out over the last +0x20c s of the attack (+0x44[level]) from its current alpha
// (kept in +0x254) to +0x1cc, and spins about its local z at +0x1d8[level] degrees a second (the angle wrapped by 720
// into [-360, 360)) at the level's scale (+0x1e4), its position kept. The animated collection (+0x240) runs while it
// plays. The float tests keep the original's senses (bge: a NaN time counts as faded in; cror for the fade-out).
void CKCometDash::UpdateAttack(float dt) {
    CNode* mesh = static_cast<CNode*>(m_pDashMesh);
    if (mesh != nullptr) {
        const float fadeIn = m_fFadeInTime;
        if (m_fElapsedTime < fadeIn) {
            const float t = m_fElapsedTime;
            const uint32_t level = m_ui32LevelIndex;
            SetMeshAlpha(mesh, ppc::fmadds(static_cast<float>(m_ai32MeshStartAlpha[level]), (fadeIn - t) / fadeIn,
                                           static_cast<float>(m_ai32MeshHoldAlpha[level]) * (t / fadeIn)));
        } else if (m_bMeshFadedIn == 0) {
            SetMeshAlpha(mesh, static_cast<float>(m_ai32MeshHoldAlpha[m_ui32LevelIndex]));
            m_bMeshFadedIn = 1;
        }
        const float t = m_fElapsedTime;
        const float fadeOut = m_fFadeOutTime;
        const float duration = m_afAttackDuration[m_ui32LevelIndex];
        mesh = static_cast<CNode*>(m_pDashMesh);
        if ((t > duration - fadeOut || t == duration - fadeOut) && m_bMeshFadedIn != 0 && mesh->m_lGeometryList != nullptr &&
            // --fps N (not in the original): the fade-out re-reads the alpha it wrote, so it compounds per update: step
            // it once per 60 Hz frame only, as at 60 fps.
            (!dotd::fps::Unlocked() || dotd::fps::Ticks() > 0) && true) {
            const float left = duration - t;
            const uint8_t current = static_cast<CGeometry*>(mesh->m_lGeometryList)->m_cGeometryColor[3];
            m_ui32FadeOutStartAlpha = current;
            const float value = ppc::fmadds(static_cast<float>(current), left / fadeOut,
                                            static_cast<float>(m_ai32MeshEndAlpha[m_ui32LevelIndex]) * ((fadeOut - left) / fadeOut));
            TransformFx::SetGeometriesAlpha(mesh, static_cast<uint8_t>(ppc::fctiwz(value)));
        }
        // The spin: the identity turned about z, the position and the pads of the local matrix kept, then scaled.
        RwMatrix local = static_cast<CNode*>(m_pDashMesh)->m_pRwFrame->modelling;
        float angle = m_afMeshSpinDegPerSec[m_ui32LevelIndex] * m_fElapsedTime;
        while (angle < kAngleLow) angle = angle + kAngleTurn;
        while (angle > kAngleHigh || angle == kAngleHigh) angle = angle - kAngleTurn;
        const RwV3d position = local.pos;
        local.right = {1.0f, 0.0f, 0.0f};
        local.up = {0.0f, 1.0f, 0.0f};
        local.at = {0.0f, 0.0f, 1.0f};
        local.pos = {0.0f, 0.0f, 0.0f};
        local.flags = 0x20003u;
        Mat4_RotateLocalZDeg(angle, reinterpret_cast<CMatrix34*>(&local));  // 0x002419c0
        local.pos = position;
        local.flags &= ~0x20000u;
        RwMatrixScalePreConcat_Thunk(reinterpret_cast<CMatrix34*>(&local),
                                     reinterpret_cast<const CVector3*>(&m_avMeshScale[m_ui32LevelIndex]));  // 0x0023f670
        static_cast<CNode*>(m_pDashMesh)->SetLocalMatrix(&local);                                  // 0x000d0be8
    }
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
    if (collection->m_bPlaying != 0) collection->Update(dt);  // 0x0098f4b0 (TocBridge)
}

// 0x003882d0 CKCometDash_UpdateMovement_maybe. Below level index 2: on a confirmed hit (host vt+0xf0) the explosion
// +0x22c at the hot spot. At level index 2: a confirmed hit allows action 1 (vt+0x44), fires the explosion +0x228 and
// holds for its time-scaling sub-effect's time (type 6, +0x0c); when that time has run out (cror lt|eq) the host aims
// again (vt+0x58, the result unused) and action 1 is forbidden.
void CKCometDash::UpdateMovement(float dt) {
    if (m_ui32LevelIndex != 2) {
        if (m_pHost->VfF0() == 0) return;  // vt+0xf0
        FireExplosion(this, m_pHitExplosionLow, m_ui8HotSpotIndex);
        return;
    }
    const uint8_t hit = m_pHost->VfF0();  // vt+0xf0
    if (hit == 0) {
        if (m_bHitHeld == 0) return;
        const float left = m_fHitSlowdownTimer - dt;
        m_fHitSlowdownTimer = left;
        if (!(left < 0.0f || left == 0.0f)) return;
        m_pHost->ComputeAimDirection(m_afSteerConeDeg[m_ui32LevelIndex] * kDegToRad, this, m_pAimCamembert);  // vt+0x58 (unused)
        m_pHost->SetHeroActionPermission(1, 0, 0, 0);                                 // vt+0x44
        m_bHitHeld = hit;
        return;
    }
    m_bHitHeld = 1;
    m_pHost->SetHeroActionPermission(1, 1, 1, 1);  // vt+0x44
    m_fHitSlowdownTimer = 0.0f;  // (a word store of 0)
    CKExplosionNodeFx* burst = FireExplosion(this, m_pHitExplosionMax, m_ui8HotSpotIndex);
    if (burst == nullptr) return;
    CKTimeScalingFxData* slow = static_cast<CKTimeScalingFxData*>(burst->GetNthSubEffectOfType(6, this, 0));  // 0x001b6530
    if (slow != nullptr) m_fHitSlowdownTimer = slow->m_fDuration;
}

// 0x00388a58 CKCometDash_SetFxActive. On: the attack (vt+0x74), the level's particles (+0x230[level]) under the hot spot
// (+0x23c), above level index 0 the sparks (+0x244 -> +0x248), the explosion (+0x220, above level index 1 +0x224) at hot
// spot 1 turned to the hero's forward, above level index 1 the animated collection (+0x240) on the user's node; the mesh
// (+0x24c) under the hot spot at the level's scale, shown, its geometries' render bits 0x2c and the level's start alpha
// (+0x1c0); above level index 0 the trail's ribbons on (the mesh's world matrix brought up to date first). Off: the
// particles and the sparks stopped and released, the collection stopped, the trail's ribbons off (laid out again).
void CKCometDash::SetFxActive(uint8_t on) {
    if (on == 0) {
        TransformFx::ReleaseParticles(&m_pActiveParticles, this);
        TransformFx::ReleaseSpark(&m_pActiveSparks, this);
        if (m_pAnimFxCollection != nullptr) static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection)->Stop();  // 0x005cc990 (TocBridge)
        CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pTrailNode);
        if (trail == nullptr) return;
        // Every ribbon off, its points laid out again (CTrailNodeFx_SetRibbonActive_maybe 0x009bdfb8, inlined).
        const uint32_t count = trail->m_ui32NbTrail;
        for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 0, 1);
        return;
    }
    SetAttackActive(1);  // vt+0x74
    CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(LevelParticles(this, m_ui32LevelIndex));
    particles->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpotIndex);  // vt+0xcc
    particles->m_pAttachOwner = nullptr;
    m_pActiveParticles = TransformFx::Acquire(LevelParticles(this, m_ui32LevelIndex), this);
    if (m_ui32LevelIndex != 0) {
        CKSparkFxData* sparks = static_cast<CKSparkFxData*>(m_pSparkFxData);
        sparks->m_unk10 = m_pHost->GetHotspot(m_ui8HotSpotIndex);  // the hot spot to hang the node under
        sparks->m_unk0c = nullptr;
        m_pActiveSparks = TransformFx::Acquire(m_pSparkFxData, this);
    }
    FireExplosion(this, m_ui32LevelIndex > 1 ? m_pStartExplosionMax : m_pStartExplosionLow, 1);
    if (m_ui32LevelIndex > 1) {
        CSGLeaf* owner = TransformFx::OwnerNode(m_pHost);                 // vt+0x08, +0x1c
        SAnimatedFxRig* rigs = TransformFx::AttachmentSets(m_pHost);      // vt+0x104
        static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection)->Play(
            owner, rigs, static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpotIndex)));  // 0x0098f4d0 (TocBridge)
    }
    CNode* mesh = static_cast<CNode*>(m_pDashMesh);
    if (mesh != nullptr) {
        if (mesh->m_pParent != nullptr) mesh->m_pParent->RemoveChild(mesh);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpotIndex))->AttachVolume(static_cast<CNode*>(m_pDashMesh));
        static_cast<CNode*>(m_pDashMesh)->Scale(&m_avMeshScale[m_ui32LevelIndex].m_unk0);  // 0x000d0d88
        mesh = static_cast<CNode*>(m_pDashMesh);
        mesh->m_sgProperties &= 0xfffffffbu;
        for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pDashMesh)->m_lGeometryList);
             geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2cu;
            TransformFx::SetGeometryAlpha(geometry, static_cast<uint8_t>(m_ai32MeshStartAlpha[m_ui32LevelIndex]));
        }
    }
    if (m_ui32LevelIndex == 0 || m_pTrailNode == nullptr) return;
    if (m_pDashMesh != nullptr) static_cast<CSGLeaf*>(m_pDashMesh)->ForceWorldMatrixUpdate();  // vt+0x50
    // Every ribbon on (CTrailNodeFx_SetRibbonActive_maybe, inlined).
    const uint32_t count = static_cast<CTrailNodeFx*>(m_pTrailNode)->m_ui32NbTrail;
    for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 1, 1);
}

// 0x00386be0 CKCometDash_Load: CKAttackMoveElement's data, then (type 0 only) 164 bytes, interleaving
// references and floats (the first per-index pass is unrolled in the original; same order as this loop).
int32_t CKCometDash::Load(IKFile* file, int32_t type) {
    CKAttackMoveElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_pStartExplosionLow);
        IKFile_ReadRef(file, &m_pDashMesh);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_afHitSphereRadius[i]);
            ReadS32LE(file, &m_ai32MeshHoldAlpha[i]);
            ReadS32LE(file, &m_ai32MeshStartAlpha[i]);
            ReadS32LE(file, &m_ai32MeshEndAlpha[i]);
        }
        ReadF32LE(file, &m_fFadeInTime);
        ReadF32LE(file, &m_fFadeOutTime);
        IKFile_ReadRef(file, &m_pTrailNode);
        ReadF32LE(file, &m_afMeshSpinDegPerSec[0]);
        ReadF32LE(file, &m_afMeshSpinDegPerSec[1]);
        ReadF32LE(file, &m_afMeshSpinDegPerSec[2]);
        IKFile_ReadRef(file, &m_pAimCamembert);
        ReadF32LE(file, &m_afSteerConeDeg[0]);
        ReadF32LE(file, &m_afSteerConeDeg[1]);
        ReadF32LE(file, &m_afSteerConeDeg[2]);
        IKFile_ReadRef(file, &m_unk230);
        IKFile_ReadRef(file, &m_unk234);
        IKFile_ReadRef(file, &m_unk238);
        IKFile_ReadRef(file, &m_pStartExplosionMax);
        IKFile_ReadRef(file, &m_pAnimFxCollection);
        for (int32_t i = 0; i < 3; ++i) {
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_avMeshScale[i]), 3);
        }
        IKFile_ReadRef(file, &m_pHitExplosionMax);
        IKFile_ReadRef(file, &m_pHitExplosionLow);
        IKFile_ReadRef(file, &m_pSparkFxData);
    }
    return 1;
}
