// CKBlackCombo.cpp - reconstructed original translation unit 0x37d2e0-0x380ed0 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKBlackCombo  key 0xa44c  category Logic  size 0x260  vtable 0xb234e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x37d2e0  CKBlackCombo_Delete
//   [x] 0x37d330  CKBlackCombo_GetAbilityId
//   [x] 0x37d338  CKBlackCombo_GetFamilyId
//   [x] 0x37d340  CKBlackCombo_SetAttackActive_maybe
//   [x] 0x37d3f0  CKBlackCombo_IsGroundTrailActive_maybe
//   [x] 0x37d450  CKBlackCombo_ApplyHeroControl
//   [x] 0x37d510  CKBlackCombo_End
//   [x] 0x37d5a0  CKBlackCombo_StopFxAndAttack
//   [x] 0x37d688  CKBlackCombo_Update  (the base's only: CKAttackMoveElement_Update)
//   [x] 0x37d6b0  CKBlackCombo_Start
//   [x] 0x37d720  CKBlackCombo_ResetRuntime
//   [x] 0x37d778  CKBlackCombo_RecursiveRegistration  (the base's only: returns 1)
//   [x] 0x37d7a0  CKBlackCombo_Destroy  (inherited: CKAttackMoveElement_Destroy)
//   [x] 0x37d7c8  CKBlackCombo_Construct
//   [x] 0x37d800  CKBlackCombo_Construct_2  (the constructor)
//   [x] 0x37d838  CKBlackCombo_DeleteArray
//   [x] 0x37d8d8  CKBlackCombo_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x37d920  CKBlackCombo_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x37d950  CKBlackCombo_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x37d980  RegisterCKBlackComboClass
//   [ ] 0x37da08  _GLOBAL__D_37da08
//   [ ] 0x37da18  _GLOBAL__I_37da18
//   [x] 0x37da28  CKBlackCombo_PostLoad
//   [x] 0x37daf8  CKBlackCombo_SteerTowardsTarget_maybe
//   [x] 0x37dc60  CKBlackCombo_CreateArray
//   [x] 0x37dd10  CKBlackCombo_Create
//   [x] 0x37dd68  CKBlackCombo_UpdateAttack_maybe
//   [x] 0x37e4f0  CKBlackCombo_Load
//   [ ] 0x37ed28  CKBlackCombo_Save
//   [x] 0x37f600  CKBlackCombo_UpdateMovement_maybe
//   [x] 0x37fa90  CKBlackCombo_SetFxActive
//
//   [ ] 0x9bf988  CKBlackCombo_IsKindOfClass  [inline]
//   [ ] 0x9bf9d8  CKBlackCombo_GetClassType  [inline]
//   [ ] 0x9bf9e0  CKBlackCombo_GetClassID  [inline]
//   [ ] 0x9bf9e8  CKBlackCombo_StartEmitterFx  [inline]
#include "k2000/logic/CKBlackCombo.h"

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

// The black combo's code is the comet dash's (CKCometDash.cpp) at its own offsets, with these differences: hot spot 5,
// action 9 (ApplyHeroControl's own and the steer's), one particle effect plus a second above level index 0 (no sparks),
// the hits only while airborne in the loop (UpdateMovement), and the trail only under the mesh.

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x32b0)
constexpr float kOne = 1.0f;                      // TOC +0x3270
constexpr float kDegToRad = 0.0174532905f;        // TOC +0x32b4 (0x3c8efa34)
constexpr float kAngleLow = -360.0f;              // TOC +0x32c8
constexpr float kAngleTurn = 720.0f;              // TOC +0x32cc
constexpr float kAngleHigh = 360.0f;              // TOC +0x32d0
constexpr float kHitMargin = 0x1.333334p-2f;      // TOC +0x32f4 (0x3e99999a, 0.3)

// The hit explosion of the level (+0x228 + 4 x level: +0x22c at level index 1, +0x230 at 2).
IKSerializable* LevelHitExplosion(const CKBlackCombo* d, uint32_t level) {
    return level == 0 ? d->m_pHitExplosionLevel0 : level == 1 ? d->m_pHitExplosionLevel1 : d->m_pHitExplosionLevel2;
}

// A pooled explosion of `data` (the inlined CKSrvFx::AcquireFx) put at the host's hot spot `hotSpot`, turned to the
// hero's forward (host vt+0x18), triggered and released; the explosion (or null).
CKExplosionNodeFx* FireExplosion(CKBlackCombo* d, IKSerializable* data, uint32_t hotSpot) {
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

// The mesh's geometries take `alpha` (TransformFx::SetGeometriesAlpha, the inlined walk), when the mesh has any.
void SetMeshAlpha(IKSerializable* mesh, float value) {
    if (static_cast<CNode*>(mesh)->m_lGeometryList == nullptr) return;
    TransformFx::SetGeometriesAlpha(mesh, static_cast<uint8_t>(ppc::fctiwz(value)));
}

// The particle data hung under the host's hot spot (+0x14; +0x10 cleared), then a pooled effect of it reserved.
IKSerializable* StartParticles(CKBlackCombo* d, IKSerializable* data) {
    CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(data);
    particles->m_pAttachHotSpot = d->m_pHost->GetHotspot(d->m_ui8HotSpotIndex);  // vt+0xcc
    particles->m_pAttachOwner = nullptr;
    return TransformFx::Acquire(data, d);
}
}  // namespace

// 0x0037d340 CKBlackCombo_SetAttackActive_maybe: the damage parameters (vt+0x88, one rand draw), then the host's attack
// sphere `on` with the level's radius (+0x1a8) and the damage (+0x19c).
void CKBlackCombo::SetAttackActive(uint8_t on) {
    ApplyDamageParams(0);  // vt+0x88
    m_pHost->SetAbilityAttackSpheres(this, on, m_afHitSphereRadius[m_ui32LevelIndex], m_pElementDamage, kOne, nullptr);  // vt+0xfc
}

// 0x0037d3f0 CKBlackCombo_IsGroundTrailActive_maybe: above level index 1, while airborne (host vt+0x30).
uint8_t CKBlackCombo::IsGroundTrailActive() {
    if (m_ui32LevelIndex > 1) return m_pHost->IsOnGround();
    return 0;
}

// 0x0037d450 CKBlackCombo_ApplyHeroControl: the owner's state test 9 (host vt+0x40) read first, the base's, then action
// 9 allowed in every context by that answer (vt+0x44).
void CKBlackCombo::ApplyHeroControl(uint8_t on) {
    const uint8_t allowed = m_pHost->Vf40(this, 9);  // vt+0x40
    CKAttackMoveElement::ApplyHeroControl(on);       // 0x00374ff8
    m_pHost->SetHeroActionPermission(9, allowed, allowed, allowed);
}

// 0x0037d510 CKBlackCombo_End: the host's +0x1d20 back to 1 (vt+0x84), the base's End, the mesh shown under sector 0.
void CKBlackCombo::End(int32_t forced) {
    m_pHost->SetHero1d20(kOne);  // vt+0x84
    CKAttackMoveElement::End(forced);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pSpinMesh), 1, 0, 0);  // 0x0098f340
}

// 0x0037d5a0 CKBlackCombo_StopFxAndAttack: the base's, the mesh hidden (not faded in), the attack sphere off, the host's
// +0x1d20 back to 1.
void CKBlackCombo::StopFxAndAttack() {
    CKAttackMoveElement::StopFxAndAttack();  // 0x00374e60
    CSGLeaf* mesh = static_cast<CSGLeaf*>(m_pSpinMesh);
    if (mesh != nullptr) {
        m_bMeshFadedIn = 0;
        mesh->m_sgProperties = (mesh->m_sgProperties & 0xfffffffbu) | 4u;
    }
    m_pHost->SetAbilityAttackSpheres(this, 0, kOne, nullptr, kOne, nullptr);  // vt+0xfc
    m_pHost->SetHero1d20(kOne);                                               // vt+0x84
}

// 0x0037d6b0 CKBlackCombo_Start: the base's, the hot spot asked (the result unused), the runtime cleared.
void CKBlackCombo::Start(CKS08AbilityHostBase* host) {
    CKAttackMoveElement::Start(host);  // 0x003760b0
    m_pHost->GetHotspot(m_ui8HotSpotIndex);    // vt+0xcc (unused)
    m_bHitHeld = 0;
    m_fHitSlowdownTimer = 0.0f;  // (a word store of 0)
    m_bMeshFadedIn = 0;
}

// 0x0037d720 CKBlackCombo_ResetRuntime: the base's, the hot spot 5, the runtime and the running effects cleared.
void CKBlackCombo::ResetRuntime(int32_t type) {
    CKAttackMoveElement::ResetRuntime(type);  // 0x003756d0
    m_ui8HotSpotIndex = 5;
    m_fHitSlowdownTimer = 0.0f;  // (a word store of 0)
    m_bHitHeld = 0;
    m_pActiveParticlesA = nullptr;
    m_pActiveParticlesB = nullptr;
    m_bMeshFadedIn = 0;
}

// 0x0037da28 CKBlackCombo_PostLoad: the base's (ResetRuntime); with a mesh, the mesh shown under sector 0 and the trail
// taken off its parent and hung under it.
int32_t CKBlackCombo::PostLoad(int32_t type) {
    CKAttackMoveElement::PostLoad(type);  // 0x00376e60
    if (m_pSpinMesh == nullptr) return 1;
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pSpinMesh), 1, 0, 0);
    CSGLeaf* trail = static_cast<CSGLeaf*>(m_pTrailNode);
    if (trail == nullptr) return 1;
    if (trail->m_pParent != nullptr) trail->m_pParent->RemoveChild(trail);  // vt+0x78
    static_cast<CSGBranch*>(m_pSpinMesh)->AddChild(static_cast<CSGLeaf*>(m_pTrailNode));  // vt+0x70
    return 1;
}

// 0x0037daf8 CKBlackCombo_SteerTowardsTarget_maybe: for the null direction the host aims (vt+0x58: the level's cone
// +0x210 in degrees, the aim cone +0x21c) and action 1 is forbidden; action 9 allowed (vt+0x44, always); then the base's
// along the result.
void CKBlackCombo::SteerTowardsTarget(const CVector3* direction) {
    CVector3 at = *direction;
    if (kNullVector.x == at.x && kNullVector.y == at.y && kNullVector.z == at.z) {
        at = m_pHost->ComputeAimDirection(m_afSteerConeDeg[m_ui32LevelIndex] * kDegToRad, this, m_pAimCamembert);  // vt+0x58
        m_pHost->SetHeroActionPermission(1, 0, 0, 0);                                       // vt+0x44
    }
    m_pHost->SetHeroActionPermission(9, 1, 1, 1);
    CKAttackMoveElement::SteerTowardsTarget(&at);  // 0x00376eb0
}

// 0x0037dd68 CKBlackCombo_UpdateAttack_maybe: CKCometDash_UpdateAttack_maybe's code at this class's offsets (the mesh
// +0x248, the kept alpha +0x250, faded in +0x254, the collection +0x244).
void CKBlackCombo::UpdateAttack(float dt) {
    CNode* mesh = static_cast<CNode*>(m_pSpinMesh);
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
        mesh = static_cast<CNode*>(m_pSpinMesh);
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
        RwMatrix local = static_cast<CNode*>(m_pSpinMesh)->m_pRwFrame->modelling;
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
        static_cast<CNode*>(m_pSpinMesh)->SetLocalMatrix(&local);                                  // 0x000d0be8
    }
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
    if (collection->m_bPlaying != 0) collection->Update(dt);  // 0x0098f4b0 (TocBridge)
}

// 0x0037f600 CKBlackCombo_UpdateMovement_maybe. Above level index 0, in the loop (+0x184) while airborne (host vt+0x30)
// and more than 0.3 s before the attack's end (bge: a NaN time does not hit): action 1 allowed (vt+0x44), the level's
// hit explosion (+0x228 + 4 x level) at the hot spot and a hold for its time-scaling sub-effect's time (type 6, +0x0c).
// Else, once a hold's time has run out (cror lt|eq), the steer again along the null direction (vt+0x90).
void CKBlackCombo::UpdateMovement(float dt) {
    if (m_ui32LevelIndex == 0) return;
    if (m_bInAir != 0 && m_pHost->IsOnGround() != 0 && m_fElapsedTime < m_afAttackDuration[m_ui32LevelIndex] - kHitMargin) {
        m_bHitHeld = 1;
        m_pHost->SetHeroActionPermission(1, 1, 1, 1);  // vt+0x44
        m_fHitSlowdownTimer = 0.0f;  // (a word store of 0)
        CKExplosionNodeFx* burst = FireExplosion(this, LevelHitExplosion(this, m_ui32LevelIndex), m_ui8HotSpotIndex);
        if (burst == nullptr) return;
        CKTimeScalingFxData* slow = static_cast<CKTimeScalingFxData*>(burst->GetNthSubEffectOfType(6, this, 0));  // 0x001b6530
        if (slow != nullptr) m_fHitSlowdownTimer = slow->m_fDuration;
        return;
    }
    if (m_bHitHeld == 0) return;
    const float left = m_fHitSlowdownTimer - dt;
    m_fHitSlowdownTimer = left;
    if (!(left < 0.0f || left == 0.0f)) return;
    const CVector3 at = kNullVector;
    SteerTowardsTarget(&at);  // vt+0x90
    m_bHitHeld = 0;
}

// 0x0037fa90 CKBlackCombo_SetFxActive. On: the attack (vt+0x74), the particles (+0x234 -> +0x238) under the hot spot,
// above level index 0 the second particles (+0x23c -> +0x240), the explosion (+0x220, above level index 1 +0x224) at hot
// spot 1 turned to the hero's forward, above level index 1 the animated collection (+0x244) on the user's node; the mesh
// (+0x248) under the hot spot at the level's scale, shown, its geometries' render bits 0x2c and the level's start alpha
// (+0x1c0); above level index 0 the trail's (+0x24c) ribbons on. Off: both particles stopped and released, the
// collection stopped, the trail's ribbons off (laid out again).
void CKBlackCombo::SetFxActive(uint8_t on) {
    if (on == 0) {
        TransformFx::ReleaseParticles(&m_pActiveParticlesA, this);
        TransformFx::ReleaseParticles(&m_pActiveParticlesB, this);
        if (m_pAnimFxCollection != nullptr) static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection)->Stop();  // 0x005cc990 (TocBridge)
        CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pTrailNode);
        if (trail == nullptr) return;
        // Every ribbon off, its points laid out again (CTrailNodeFx_SetRibbonActive_maybe 0x009bdfb8, inlined).
        const uint32_t count = trail->m_ui32NbTrail;
        for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 0, 1);
        return;
    }
    SetAttackActive(1);  // vt+0x74
    m_pActiveParticlesA = StartParticles(this, m_pParticlesDataA);
    if (m_ui32LevelIndex != 0) m_pActiveParticlesB = StartParticles(this, m_pParticlesDataB);
    FireExplosion(this, m_ui32LevelIndex > 1 ? m_pStartExplosionMax : m_pStartExplosionLow, 1);
    if (m_ui32LevelIndex > 1) {
        CSGLeaf* owner = TransformFx::OwnerNode(m_pHost);             // vt+0x08, +0x1c
        SAnimatedFxRig* rigs = TransformFx::AttachmentSets(m_pHost);  // vt+0x104
        static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection)->Play(
            owner, rigs, static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpotIndex)));  // 0x0098f4d0 (TocBridge)
    }
    CNode* mesh = static_cast<CNode*>(m_pSpinMesh);
    if (mesh != nullptr) {
        if (mesh->m_pParent != nullptr) mesh->m_pParent->RemoveChild(mesh);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpotIndex))->AttachVolume(static_cast<CNode*>(m_pSpinMesh));
        static_cast<CNode*>(m_pSpinMesh)->Scale(&m_avMeshScale[m_ui32LevelIndex].m_unk0);  // 0x000d0d88
        mesh = static_cast<CNode*>(m_pSpinMesh);
        mesh->m_sgProperties &= 0xfffffffbu;
        for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pSpinMesh)->m_lGeometryList);
             geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2cu;
            TransformFx::SetGeometryAlpha(geometry, static_cast<uint8_t>(m_ai32MeshStartAlpha[m_ui32LevelIndex]));
        }
    }
    if (m_ui32LevelIndex == 0 || m_pTrailNode == nullptr) return;
    if (m_pSpinMesh != nullptr) static_cast<CSGLeaf*>(m_pSpinMesh)->ForceWorldMatrixUpdate();  // vt+0x50
    // Every ribbon on (CTrailNodeFx_SetRibbonActive_maybe, inlined).
    const uint32_t count = static_cast<CTrailNodeFx*>(m_pTrailNode)->m_ui32NbTrail;
    for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 1, 1);
}

// 0x0037e4f0 CKBlackCombo_Load: CKAttackMoveElement's data, then (type 0 only) 160 bytes: eight references,
// three passes over seven per-index fields, two floats and three references.
int32_t CKBlackCombo::Load(IKFile* file, int32_t type) {
    CKAttackMoveElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_pStartExplosionLow);
        IKFile_ReadRef(file, &m_pSpinMesh);
        IKFile_ReadRef(file, &m_pTrailNode);
        IKFile_ReadRef(file, &m_pAimCamembert);
        IKFile_ReadRef(file, &m_pParticlesDataA);
        IKFile_ReadRef(file, &m_pParticlesDataB);
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
        IKFile_ReadRef(file, &m_pHitExplosionLevel0);
        IKFile_ReadRef(file, &m_pHitExplosionLevel1);
        IKFile_ReadRef(file, &m_pHitExplosionLevel2);
    }
    return 1;
}
