// CKPoisonSpin.cpp - reconstructed original translation unit 0x3b8bd8-0x3bc818 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKPoisonSpin  key 0xa2cc  category Logic  size 0x260  vtable 0xb23d38
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3b8bd8  CKPoisonSpin_Delete
//   [x] 0x3b8c28  CKPoisonSpin_GetAbilityId
//   [x] 0x3b8c30  CKPoisonSpin_GetFamilyId
//   [x] 0x3b8c38  CKPoisonSpin_SetAttackActive_maybe
//   [x] 0x3b8ce8  CKPoisonSpin_IsGroundTrailActive_maybe
//   [x] 0x3b8d48  CKPoisonSpin_ApplyHeroControl
//   [x] 0x3b8e08  CKPoisonSpin_End
//   [x] 0x3b8e98  CKPoisonSpin_StopFxAndAttack
//   [x] 0x3b8f80  CKPoisonSpin_Update  (inherited: CKAttackMoveElement_Update)
//   [x] 0x3b8fa8  CKPoisonSpin_Start
//   [x] 0x3b9018  CKPoisonSpin_ResetRuntime
//   [x] 0x3b9070  CKPoisonSpin_RecursiveRegistration  (inherited: CKAttackMoveElement_RecursiveRegistration)
//   [x] 0x3b9098  CKPoisonSpin_Destroy  (inherited: CKAttackMoveElement_Destroy)
//   [x] 0x3b90c0  CKPoisonSpin_Construct
//   [x] 0x3b90f8  CKPoisonSpin_Construct_2  (the same as 0x3b90c0 CKPoisonSpin_Construct)
//   [x] 0x3b9130  CKPoisonSpin_DeleteArray
//   [x] 0x3b91d0  CKPoisonSpin_DeletingDestructor  (C++ destructor chain: vtable stores, CKAttackMoveElement_DestructBody)
//   [x] 0x3b9218  CKPoisonSpin_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3b9248  CKPoisonSpin_DestructBody  (C++ destructor chain: vtable stores, CKAttackMoveElement_DestructBody)
//   [ ] 0x3b9278  RegisterCKPoisonSpinClass
//   [ ] 0x3b9300  _GLOBAL__D_3b9300
//   [ ] 0x3b9310  _GLOBAL__I_3b9310
//   [x] 0x3b9320  CKPoisonSpin_PostLoad
//   [x] 0x3b9440  CKPoisonSpin_SteerTowardsTarget_maybe
//   [x] 0x3b95a8  CKPoisonSpin_CreateArray
//   [x] 0x3b9658  CKPoisonSpin_Create
//   [x] 0x3b96b0  CKPoisonSpin_UpdateAttack_maybe  (CKBlackCombo's code)
//   [x] 0x3b9e38  CKPoisonSpin_Load
//   [ ] 0x3ba670  CKPoisonSpin_Save
//   [x] 0x3baf48  CKPoisonSpin_UpdateMovement_maybe  (CKBlackCombo's code)
//   [x] 0x3bb3d8  CKPoisonSpin_SetFxActive  (CKBlackCombo's code)
//
//   [ ] 0x9c00d0  CKPoisonSpin_IsKindOfClass  [inline]
//   [ ] 0x9c0120  CKPoisonSpin_GetClassType  [inline]
//   [ ] 0x9c0128  CKPoisonSpin_GetClassID  [inline]
//   [ ] 0x9c0130  CKPoisonSpin_StartEmitterFx  [inline]
#include "k2000/logic/CKPoisonSpin.h"

#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKTimeScalingFxData.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "platform/fps.h"

// 0x003b9e38 CKPoisonSpin_Load: CKAttackMoveElement's data, then (type 0 only) 160 bytes: eight references,
// three passes over seven per-index fields, two floats and three references (as CKBlackCombo_Load).
int32_t CKPoisonSpin::Load(IKFile* file, int32_t type) {
    CKAttackMoveElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk220);
        IKFile_ReadRef(file, &m_unk248);
        IKFile_ReadRef(file, &m_unk24c);
        IKFile_ReadRef(file, &m_unk21c);
        IKFile_ReadRef(file, &m_unk234);
        IKFile_ReadRef(file, &m_unk23c);
        IKFile_ReadRef(file, &m_unk224);
        IKFile_ReadRef(file, &m_unk244);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_unk1a8[i]);
            ReadS32LE(file, &m_unk1b4[i]);
            ReadS32LE(file, &m_unk1c0[i]);
            ReadS32LE(file, &m_unk1cc[i]);
            ReadF32LE(file, &m_unk1d8[i]);
            ReadF32LE(file, &m_unk210[i]);
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk1e4[i]), 3);
        }
        ReadF32LE(file, &m_unk208);
        ReadF32LE(file, &m_unk20c);
        IKFile_ReadRef(file, &m_unk228);
        IKFile_ReadRef(file, &m_unk22c);
        IKFile_ReadRef(file, &m_unk230);
    }
    return 1;
}

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x3b3c)
constexpr float kOne = 1.0f;                      // TOC +0x3af8
constexpr float kDegToRad = 0.0174532905f;        // TOC +0x3b40 (0x3c8efa34)
}  // namespace

// 0x003b9320 CKPoisonSpin_PostLoad
int32_t CKPoisonSpin::PostLoad(int32_t type) {
    CKAttackMoveElement::PostLoad(type);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk248), 1, 0, 0);  // 0x005832a8 (TOC bridge)
    CSGLeaf* trail = static_cast<CSGLeaf*>(m_unk24c);
    if (trail == nullptr) return 1;
    if (trail->m_pParent != nullptr) trail->m_pParent->RemoveChild(trail);  // vt+0x78
    CSGBranch* parent = m_unk248 != nullptr ? static_cast<CSGBranch*>(m_unk248)
                                            : static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
    parent->AddChild(static_cast<CSGLeaf*>(m_unk24c));  // vt+0x70
    return 1;
}

// 0x003b8fa8 CKPoisonSpin_Start
void CKPoisonSpin::Start(CKS08AbilityHostBase* host) {
    CKAttackMoveElement::Start(host);
    m_pHost->GetHotspot(m_unk186);  // vt+0xcc (the result unused)
    m_unk25c = 0;
    m_unk258 = 0;
    m_unk254 = 0;
}

// 0x003b8e08 CKPoisonSpin_End
void CKPoisonSpin::End(int32_t forced) {
    m_pHost->SetHero1d20(kOne);  // vt+0x84 (the ability handed in r4 too)
    CKAttackMoveElement::End(forced);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk248), 1, 0, 0);
}

// 0x003b8d48 CKPoisonSpin_ApplyHeroControl
void CKPoisonSpin::ApplyHeroControl(uint8_t on) {
    const uint8_t allowed = m_pHost->Vf40(this, 9);  // vt+0x40
    CKAttackMoveElement::ApplyHeroControl(on);
    m_pHost->SetHeroActionPermission(9, allowed, allowed, allowed);  // vt+0x44
}

// 0x003b9018 CKPoisonSpin_ResetRuntime
void CKPoisonSpin::ResetRuntime(int32_t type) {
    CKAttackMoveElement::ResetRuntime(type);
    m_unk186 = 5;
    m_unk258 = 0;
    m_unk25c = 0;
    m_unk238 = 0;
    m_unk240 = 0;
    m_unk254 = 0;
}

// 0x003b8c38 CKPoisonSpin_SetAttackActive_maybe
void CKPoisonSpin::SetAttackActive(uint8_t on) {
    ApplyDamageParams(0);  // vt+0x88
    m_pHost->SetAbilityAttackSpheres(this, on, m_unk1a8[m_unk04], m_unk19c, kOne, nullptr);  // vt+0xfc
}

// 0x003b8e98 CKPoisonSpin_StopFxAndAttack
void CKPoisonSpin::StopFxAndAttack() {
    CKAttackMoveElement::StopFxAndAttack();
    CNode* cloud = static_cast<CNode*>(m_unk248);
    if (cloud != nullptr) {
        m_unk254 = 0;
        cloud->m_sgProperties = (cloud->m_sgProperties & 0xfffffffbu) | 4u;
    }
    m_pHost->SetAbilityAttackSpheres(this, 0, kOne, nullptr, kOne, nullptr);  // vt+0xfc
    m_pHost->SetHero1d20(kOne);                                              // vt+0x84
}

// 0x003b8ce8 CKPoisonSpin_IsGroundTrailActive_maybe
uint8_t CKPoisonSpin::IsGroundTrailActive() {
    if (m_unk04 <= 1) return 0;
    return m_pHost->IsAirborne();  // vt+0x30
}

// 0x003b9440 CKPoisonSpin_SteerTowardsTarget_maybe (the null test with fcmpu bne: a NaN component is not null)
void CKPoisonSpin::SteerTowardsTarget(const CVector3* direction) {
    CVector3 dir = *direction;
    if (kNullVector.x == dir.x && kNullVector.y == dir.y && kNullVector.z == dir.z) {
        dir = m_pHost->ComputeAimDirection(m_unk210[m_unk04] * kDegToRad, this, m_unk21c);  // vt+0x58
        m_pHost->SetHeroActionPermission(1, 0, 0, 0);                                     // vt+0x44
    }
    m_pHost->SetHeroActionPermission(9, 1, 1, 1);
    CKAttackMoveElement::SteerTowardsTarget(&dir);  // 0x00376eb0
}

// C2.8 port-rest R06: the three runtime slots below are CKBlackCombo's instruction for instruction (work/scratch-c28-R06
// cmpfn.py: 481 / 292 / 1295 instructions, no difference but the TOC offsets, whose words are the same), so they are
// its port (CKBlackCombo.cpp) at this class's identical offsets.
namespace {
constexpr float kAngleLow = -360.0f;          // TOC (CKBlackCombo's +0x32c8)
constexpr float kAngleTurn = 720.0f;          // TOC (+0x32cc)
constexpr float kAngleHigh = 360.0f;          // TOC (+0x32d0)
constexpr float kHitMargin = 0x1.333334p-2f;  // TOC (+0x32f4: 0x3e99999a, 0.3)

// The hit explosion of the level (+0x228 + 4 x level: +0x22c at level index 1, +0x230 at 2).
IKSerializable* LevelHitExplosion(const CKPoisonSpin* d, uint32_t level) {
    return level == 0 ? d->m_unk228 : level == 1 ? d->m_unk22c : d->m_unk230;
}

// A pooled explosion of `data` (the inlined CKSrvFx::AcquireFx) put at the host's hot spot `hotSpot`, turned to the
// hero's forward (host vt+0x18), triggered and released; the explosion (or null).
CKExplosionNodeFx* FireExplosion(CKPoisonSpin* d, IKSerializable* data, uint32_t hotSpot) {
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
IKSerializable* StartParticles(CKPoisonSpin* d, IKSerializable* data) {
    CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(data);
    particles->m_pAttachHotSpot = d->m_pHost->GetHotspot(d->m_unk186);  // vt+0xcc
    particles->m_pAttachOwner = nullptr;
    return TransformFx::Acquire(data, d);
}
}  // namespace

// 0x003b96b0 CKPoisonSpin_UpdateAttack_maybe: CKBlackCombo_UpdateAttack_maybe 0x37dd68 (the mesh +0x248 fades in over
// +0x208 from the level's +0x1c0 to +0x1b4 (fused), out over the last +0x20c to +0x1cc; it spins about z at the level's
// +0x1d8 degrees per second, scaled by +0x1e4); the collection +0x244 updated while it plays.
void CKPoisonSpin::UpdateAttack(float dt) {
    CNode* mesh = static_cast<CNode*>(m_unk248);
    if (mesh != nullptr) {
        const float fadeIn = m_unk208;
        if (m_unk18c < fadeIn) {
            const float t = m_unk18c;
            const uint32_t level = m_unk04;
            SetMeshAlpha(mesh, ppc::fmadds(static_cast<float>(m_unk1c0[level]), (fadeIn - t) / fadeIn,
                                           static_cast<float>(m_unk1b4[level]) * (t / fadeIn)));
        } else if (m_unk254 == 0) {
            SetMeshAlpha(mesh, static_cast<float>(m_unk1b4[m_unk04]));
            m_unk254 = 1;
        }
        const float t = m_unk18c;
        const float fadeOut = m_unk20c;
        const float duration = m_unk44[m_unk04];
        mesh = static_cast<CNode*>(m_unk248);
        if ((t > duration - fadeOut || t == duration - fadeOut) && m_unk254 != 0 && mesh->m_lGeometryList != nullptr &&
            // --fps N (not in the original): the fade-out re-reads the alpha it wrote, so it compounds per update: step
            // it once per 60 Hz frame only, as at 60 fps.
            (!dotd::fps::Unlocked() || dotd::fps::Ticks() > 0) && true) {
            const float left = duration - t;
            const uint8_t current = static_cast<CGeometry*>(mesh->m_lGeometryList)->m_cGeometryColor[3];
            m_unk250 = current;
            const float value = ppc::fmadds(static_cast<float>(current), left / fadeOut,
                                            static_cast<float>(m_unk1cc[m_unk04]) * ((fadeOut - left) / fadeOut));
            TransformFx::SetGeometriesAlpha(mesh, static_cast<uint8_t>(ppc::fctiwz(value)));
        }
        // The spin: the identity turned about z, the position and the pads of the local matrix kept, then scaled.
        RwMatrix local = static_cast<CNode*>(m_unk248)->m_pRwFrame->modelling;
        float angle = m_unk1d8[m_unk04] * m_unk18c;
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
                                     reinterpret_cast<const CVector3*>(&m_unk1e4[m_unk04]));  // 0x0023f670
        static_cast<CNode*>(m_unk248)->SetLocalMatrix(&local);                                  // 0x000d0be8
    }
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_unk244);
    if (collection->m_bPlaying != 0) collection->Update(dt);  // 0x0098f4b0 (TocBridge)
}

// 0x003baf48 CKPoisonSpin_UpdateMovement_maybe: CKBlackCombo_UpdateMovement_maybe 0x37f600. Above level index 0, in the
// loop (+0x184) while airborne (host vt+0x30) and more than 0.3 s before the attack's end (bge: a NaN time does not hit):
// action 1 allowed (vt+0x44), the level's hit explosion (+0x228 + 4 x level) at the hot spot and a hold for its
// time-scaling sub-effect's time (type 6, +0x0c). Else, once a hold's time has run out (cror lt|eq), the steer again
// along the null direction (vt+0x90).
void CKPoisonSpin::UpdateMovement(float dt) {
    if (m_unk04 == 0) return;
    if (m_unk184 != 0 && m_pHost->IsAirborne() != 0 && m_unk18c < m_unk44[m_unk04] - kHitMargin) {
        m_unk25c = 1;
        m_pHost->SetHeroActionPermission(1, 1, 1, 1);  // vt+0x44
        m_unk258 = 0.0f;  // (a word store of 0)
        CKExplosionNodeFx* burst = FireExplosion(this, LevelHitExplosion(this, m_unk04), m_unk186);
        if (burst == nullptr) return;
        CKTimeScalingFxData* slow = static_cast<CKTimeScalingFxData*>(burst->GetNthSubEffectOfType(6, this, 0));  // 0x001b6530
        if (slow != nullptr) m_unk258 = slow->m_unk0c;
        return;
    }
    if (m_unk25c == 0) return;
    const float left = m_unk258 - dt;
    m_unk258 = left;
    if (!(left < 0.0f || left == 0.0f)) return;
    const CVector3 at = kNullVector;
    SteerTowardsTarget(&at);  // vt+0x90
    m_unk25c = 0;
}

// 0x003bb3d8 CKPoisonSpin_SetFxActive: CKBlackCombo_SetFxActive 0x37fa90. On: the attack (vt+0x74), the particles
// (+0x234 -> +0x238) under the hot spot, above level index 0 the second particles (+0x23c -> +0x240), the explosion
// (+0x220, above level index 1 +0x224) at hot spot 1 turned to the hero's forward, above level index 1 the animated
// collection (+0x244) on the user's node; the mesh (+0x248) under the hot spot at the level's scale, shown, its
// geometries' render bits 0x2c and the level's start alpha (+0x1c0); above level index 0 the trail's (+0x24c) ribbons on.
// Off: both particles stopped and released, the collection stopped, the trail's ribbons off (laid out again).
void CKPoisonSpin::SetFxActive(uint8_t on) {
    if (on == 0) {
        TransformFx::ReleaseParticles(&m_unk238, this);
        TransformFx::ReleaseParticles(&m_unk240, this);
        if (m_unk244 != nullptr) static_cast<CKAnimatedFxCollection*>(m_unk244)->Stop();  // 0x005cc990 (TocBridge)
        CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_unk24c);
        if (trail == nullptr) return;
        // Every ribbon off, its points laid out again (CTrailNodeFx_SetRibbonActive_maybe 0x009bdfb8, inlined).
        const uint32_t count = trail->m_ui32NbTrail;
        for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_unk24c)->SetRibbonActive(i, 0, 1);
        return;
    }
    SetAttackActive(1);  // vt+0x74
    m_unk238 = StartParticles(this, m_unk234);
    if (m_unk04 != 0) m_unk240 = StartParticles(this, m_unk23c);
    FireExplosion(this, m_unk04 > 1 ? m_unk224 : m_unk220, 1);
    if (m_unk04 > 1) {
        CSGLeaf* owner = TransformFx::OwnerNode(m_pHost);             // vt+0x08, +0x1c
        SAnimatedFxRig* rigs = TransformFx::AttachmentSets(m_pHost);  // vt+0x104
        static_cast<CKAnimatedFxCollection*>(m_unk244)->Play(
            owner, rigs, static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk186)));  // 0x0098f4d0 (TocBridge)
    }
    CNode* mesh = static_cast<CNode*>(m_unk248);
    if (mesh != nullptr) {
        if (mesh->m_pParent != nullptr) mesh->m_pParent->RemoveChild(mesh);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk186))->AttachVolume(static_cast<CNode*>(m_unk248));
        static_cast<CNode*>(m_unk248)->Scale(&m_unk1e4[m_unk04].m_unk0);  // 0x000d0d88
        mesh = static_cast<CNode*>(m_unk248);
        mesh->m_sgProperties &= 0xfffffffbu;
        for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_unk248)->m_lGeometryList);
             geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2cu;
            TransformFx::SetGeometryAlpha(geometry, static_cast<uint8_t>(m_unk1c0[m_unk04]));
        }
    }
    if (m_unk04 == 0 || m_unk24c == nullptr) return;
    if (m_unk248 != nullptr) static_cast<CSGLeaf*>(m_unk248)->ForceWorldMatrixUpdate();  // vt+0x50
    // Every ribbon on (CTrailNodeFx_SetRibbonActive_maybe, inlined).
    const uint32_t count = static_cast<CTrailNodeFx*>(m_unk24c)->m_ui32NbTrail;
    for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_unk24c)->SetRibbonActive(i, 1, 1);
}
