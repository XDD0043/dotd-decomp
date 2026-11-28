// CKWindTwister.cpp - reconstructed original translation unit 0x3e6f80-0x3ee198 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKWindTwister  key 0x98cc  category Logic  size 0x344  vtable 0xb249c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3e6f80  CKWindTwister_Delete
//   [x] 0x3e6fd0  CKWindTwister_GetAbilityId
//   [x] 0x3e6fd8  CKWindTwister_GetFamilyId
//   [x] 0x3e6fe0  CKWindTwister_IsGroundTrailActive_maybe
//   [x] 0x3e7040  CKWindTwister_GetFxSound_maybe
//   [x] 0x3e7248  CKWindTwister_ApplyHeroControl
//   [x] 0x3e7318  CKWindTwister_End
//   [x] 0x3e7480  CKWindTwister_ResetRuntime
//   [x] 0x3e7648  CKWindTwister_RecursiveRegistration  (CKTransformElement's 0x3de480: returns 1; the default slot)
//   [x] 0x3e7670  CKWindTwister_Destroy  (inherited: CKTransformElement_Destroy)
//   [x] 0x3e7698  CKWindTwister_DeletingDestructor  (the destructor; delete)
//   [x] 0x3e76e0  CKWindTwister_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3e7710  CKWindTwister_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3e7740  CKWindTwister_Construct
//   [x] 0x3e7778  CKWindTwister_Construct_2  (the constructor, CKWindTwister.h)
//   [x] 0x3e77b0  CKWindTwister_DeleteArray
//   [x] 0x3e7850  CKWindTwister_PostLoad
//   [ ] 0x3e79a0  RegisterCKWindTwisterClass
//   [ ] 0x3e7a28  _GLOBAL__D_3e7a28
//   [ ] 0x3e7a38  _GLOBAL__I_3e7a38
//   [x] 0x3e7a48  CKWindTwister_StopFx
//   [x] 0x3e7c98  CKWindTwister_CreateArray
//   [x] 0x3e7d48  CKWindTwister_Create
//   [x] 0x3e7da0  CKWindTwister_Start
//   [x] 0x3e8260  CKWindTwister_Load
//   [ ] 0x3e9870  CKWindTwister_Save
//   [x] 0x3ead10  CKWindTwister_UpdateEffect_maybe
//   [x] 0x3ec8d8  CKWindTwister_UpdateAttack_maybe
//   [x] 0x3ed2c0  CKWindTwister_SetFxActive
//
//   [ ] 0x9c09c0  CKWindTwister_IsKindOfClass  [inline]
//   [ ] 0x9c0a10  CKWindTwister_GetClassType  [inline]
//   [ ] 0x9c0a18  CKWindTwister_GetClassID  [inline]
//   [x] 0x9c0a20  CKWindTwister_StartEmitterFx  [inline: CKTransformElement_StartEmitterFx 0x3dd068 called as is; the
//                 base's vt+0x78 serves]
#include "k2000/logic/CKWindTwister.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/render/CKMeshPopFxData.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Math.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CTrailNodeFx.h"

namespace {
// 0x00a70be4 (TOC +0x4304): this unit's copy of the ability ids' damage types.
const uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};
// 0x00c50d40 (TOC +0x438c): the shared Y axis (filled by a static initialiser in the original).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
// 0x00c50d64 (TOC +0x4374): the null vector.
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};
constexpr float kRandMax = 65535.0f;          // TOC +0x4378 (0x477fff00)
constexpr float kRandScale = -0x1.0001p-15f;  // TOC +0x4390 (0xb8000080)
constexpr float kNearTop = 0.05f;             // TOC +0x4394 (0x3d4ccccd)

float SignedToFloat(int32_t word) { return static_cast<float>(static_cast<double>(word)); }
float UnsignedToFloat(uint32_t word) { return static_cast<float>(static_cast<double>(word)); }
// The alpha byte of a float (fctiwz, the low byte through stfiwx / lbz).
uint8_t AlphaByte(float value) { return static_cast<uint8_t>(ppc::fctiwz(value)); }
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// A spin angle brought into [-360, 360) by steps of 720 (TOC +0x4380 / +0x4384 / +0x4388; bge without cror: a NaN
// stays).
float WrapDegrees(float angle) {
    if (angle < -360.0f) {
        do {
            angle = angle + 720.0f;
        } while (angle < -360.0f);
    }
    if (angle >= 360.0f) {
        do {
            angle = angle - 720.0f;
        } while (angle >= 360.0f);
    }
    return angle;
}

// The node's first geometry's alpha byte compared with `alpha`; every geometry takes it when it differs (the inlined
// alpha walk). BUG(original): the byte is read before the geometry list is tested (a node without geometry reads
// address 0x23); dotd tests first.
void SetAlphaIfChanged(IKSerializable* node, uint8_t alpha) {
    CGeometry* first = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList);
    if (first == nullptr || alpha == first->m_cGeometryColor[3]) return;
    TransformFx::SetGeometriesAlpha(node, alpha);
}

// The cone's matrix (the inlined code after each node's alpha): the frame's modelling copied (its flags and pads), an
// identity written over it, then the parent's modelling inverted into it, rebuilt about the world up keeping its at
// row, placed at the node's own position (`height`: its y replaced by -height, the outer cones'), the three rows scaled
// by `scale` (flags bit 17 then bits 17 and 0 cleared), turned by -`spin` degrees about its y and set as the node's
// local matrix (CSGMovable_SetLocalMatrix_maybe 0x0d0be8).
void SpinNode(IKSerializable* object, float spin, float scale, const float* height) {
    CSGLeaf* node = static_cast<CSGLeaf*>(object);
    CMatrix34 m;
    std::memcpy(&m, &static_cast<CSGMovable*>(node)->m_pRwFrame->modelling, sizeof(m));
    const CVector3 position = m.m_pos;
    m.m_up.y = 1.0f;
    m.m_right.z = 0.0f;
    m.m_right.y = 0.0f;
    m.m_at.y = 0.0f;
    m.m_up.z = 0.0f;
    m.m_pos.z = 0.0f;
    m.m_pos.y = 0.0f;
    m.m_pos.x = 0.0f;
    m.m_ui32Flags = 0x20003u;
    m.m_up.x = 0.0f;
    m.m_at.x = 0.0f;
    m.m_at.z = 1.0f;
    m.m_right.x = 1.0f;
    CSGMovable* parent = static_cast<CSGMovable*>(static_cast<CSGLeaf*>(node->m_pParent));
    Mat4_Invert(&m, reinterpret_cast<const CMatrix34*>(&parent->m_pRwFrame->modelling));  // 0x0023f878
    Mat4_BuildFromUpAndForward(&m, &kAxisY, &m.m_at);                                       // 0x0023ff80
    m.m_pos.z = position.z;
    m.m_pos.x = position.x;
    m.m_pos.y = height != nullptr ? -*height : position.y;
    m.m_ui32Flags &= ~0x20000u;
    m.m_right.x = scale * m.m_right.x;
    m.m_right.y = scale * m.m_right.y;
    m.m_right.z = scale * m.m_right.z;
    m.m_up.x = scale * m.m_up.x;
    m.m_up.y = scale * m.m_up.y;
    m.m_up.z = scale * m.m_up.z;
    m.m_at.x = scale * m.m_at.x;
    m.m_at.y = scale * m.m_at.y;
    m.m_at.z = scale * m.m_at.z;
    m.m_ui32Flags &= 0xfffdfffeu;
    Mat4_RotateLocalYDeg(-spin, &m);                                                     // 0x002413d0
    static_cast<CSGMovable*>(node)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));  // 0x000d0be8
}

// The visible test of the three cones: there, under a parent, not hidden (scene property bit 2).
bool IsShown(IKSerializable* node) {
    if (node == nullptr) return false;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    return leaf->m_pParent != nullptr && (leaf->m_sgProperties & 4u) == 0;
}
}  // namespace

// A Rand_Int draw (0x00011500) as the float of its low 16 bits (rldicl 48, fcfid, frsp: exact). A macro, so that the
// rand log (DOTD_REPLAY_RANDLOG) names the function that draws.
#define WT_RAND_U16() static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)

// 0x003e6fe0 CKWindTwister_IsGroundTrailActive_maybe
uint8_t CKWindTwister::IsGroundTrailActive() {
    if (m_levelIndex == 0) return 0;
    return m_pHost->IsOnGround();  // vt+0x30
}

// 0x003e7040 CKWindTwister_GetFxSound_maybe
CKSound* CKWindTwister::GetFxSound(uint32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    auto usable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00111000
    };
    if (which == 3) {
        if (m_levelIndex != 1) {
            if (m_levelIndex != 2) return nullptr;
            if (usable(5)) return sounds->GetSound(5);
        }
        if (usable(4)) return sounds->GetSound(4);
        return nullptr;
    }
    if (which == 4) return sounds->GetSound(3);
    if (which != 1) return nullptr;
    if (m_levelIndex == 1) {
        if (usable(1)) return sounds->GetSound(1);
    } else if (m_levelIndex == 2) {
        if (usable(2)) return sounds->GetSound(2);
        if (usable(1)) return sounds->GetSound(1);
    }
    return sounds->GetSound(0);
}

// 0x003e7248 CKWindTwister_ApplyHeroControl
void CKWindTwister::ApplyHeroControl(uint8_t on) {
    CKTransformElement::ApplyHeroControl(on);
    const uint8_t allow = on != 0 ? 1 : 0;
    m_pHost->SetHeroActionPermission(7, allow, allow, allow);  // vt+0x44
}

// 0x003e7318 CKWindTwister_End
void CKWindTwister::End(int32_t forced) {
    m_pHost->SetHero1d20(1.0f);  // vt+0x84; TOC +0x4300
    if (m_pLoopSound != nullptr) {
        m_pLoopSound->Stop(0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    if (m_pDashSound != nullptr) {
        m_pDashSound->Stop(0);
        m_pDashSound = nullptr;
    }
    CKTransformElement::End(forced);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pConeMesh0), 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pConeMesh1), 1, 0, 0);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pConeMesh2), 1, 0, 0);
    TransformFx::ReleaseMeshPop(&m_pActiveMeshPop, this);
}

// 0x003e7480 CKWindTwister_ResetRuntime
void CKWindTwister::ResetRuntime() {
    CKTransformElement::ResetRuntime();
    m_fDashTimeScale = 1.0f;  // TOC +0x4300
    m_pActiveAnimFx = nullptr;
    m_ui8HotSpot = 0;
    m_unk338 = 0;
    m_pActiveDashSparks = nullptr;
    m_pActiveLoopParticles = nullptr;
    m_pActiveDashParticles = nullptr;
    m_pActiveMeshPop = nullptr;
    m_fEffectTimer = 0.0f;
    m_fStopFxTime = 0.0f;
    m_fUnusedTimer2 = 0.0f;
    m_fNextProjTimer = 0.0f;
    m_abConeFadeState[0] = 0;
    m_abConeFadeState[1] = 0;
    m_abConeFadeState[2] = 0;
    m_pLoopSound = nullptr;
    m_pDashSound = nullptr;
    static_cast<CKS08ElementDamage*>(m_pProjectileDamage)->SetAbilityId(GetAbilityId());  // vt+0x68
    CKS08ElementDamage* second = static_cast<CKS08ElementDamage*>(m_pSecondaryDamage);
    second->SetAbilityId(GetAbilityId());
    second->SetDamageType(kAbilityDamageTypes[GetAbilityId() & 0xffu]);  // vt+0x64
    second->SetContinuous(1);                                             // vt+0x54
    second->m_unk1c = 0x1.921fb6p+1f;                                     // TOC +0x4308 (0x40490fdb, pi)
}

// 0x003e7a48 CKWindTwister_StopFx
void CKWindTwister::StopFx() {
    CKTransformElement::StopFx();
    m_fStopFxTime = m_fEffectTimer;
    // Each node's alpha now (its first geometry's, else the level's full alpha) is where its fade-out starts; without a
    // fade-out time it is hidden at once.
    IKSerializable* nodes[3] = {m_pConeMesh0, m_pConeMesh1, m_pConeMesh2};
    const int32_t* full[3] = {m_ai32Cone0FullAlpha, m_ai32Cone1FullAlpha, m_ai32Cone2FullAlpha};
    for (uint32_t n = 0; n < 3; ++n) {
        IKSerializable* node = nodes[n];
        if (node == nullptr) continue;
        CGeometry* first = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList);
        if (first != nullptr) {
            m_aui32FadeOutStartAlpha[n] = first->m_cGeometryColor[3];
        } else {
            m_aui32FadeOutStartAlpha[n] = static_cast<uint32_t>(full[n][m_levelIndex]);
        }
        const float time = n == 0 ? m_fCone0FadeOutTime : (n == 1 ? m_fCone1FadeOutTime : m_fCone2FadeOutTime);
        if (time == 0.0f) {  // TOC +0x4338
            TransformFx::HideNode(node);
        } else {
            m_abConeFadeState[n] = 1;
        }
    }
    m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc
    m_pHost->SetHero1d20(1.0f);                                                // vt+0x84
}

// 0x003e7da0 CKWindTwister_Start
void CKWindTwister::Start(CKS08AbilityHostBase* host) {
    m_pDashSound = nullptr;
    m_pLoopSound = nullptr;
    CKTransformElement::Start(host);
    // Each node shown at its start alpha and moved under the user's hot spot (the third at level 2 only).
    for (uint32_t n = 0; n < 3; ++n) {
        IKSerializable* node = n == 0 ? m_pConeMesh0 : (n == 1 ? m_pConeMesh1 : m_pConeMesh2);
        if (node == nullptr) continue;
        if (n == 2 && m_levelIndex != 2) continue;
        TransformFx::ShowNode(node);
        // Node 0: the low byte of +0x16c[level] (lbz +0x16f + 4 x level); the others 0.
        const uint8_t alpha = n == 0 ? static_cast<uint8_t>(m_ai32Cone0StartAlpha[m_levelIndex] & 0xff) : 0;
        TransformFx::SetGeometriesAlpha(node, alpha);
        CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
        if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);                // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot))->AttachVolume(leaf);  // vt+0xcc; 0x000ce2b8
    }
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    dash->m_fImpulseTimer = 0.0f;
    dash->m_fValue = 0.0f;
    dash->m_fSpeed = 0.0f;
    m_abConeFadeState[2] = 0;
    m_unk338 = 0;
    m_fNextProjTimer = m_fProjInterval;
    m_fDashTimeScale = 1.0f;  // TOC +0x4300
    m_fEffectTimer = 0.0f;
    m_fUnusedTimer2 = 0.0f;
    m_abConeFadeState[0] = 0;
    m_abConeFadeState[1] = 0;
}

// 0x003ec8d8 CKWindTwister_UpdateAttack_maybe
void CKWindTwister::UpdateAttack(float dt) {
    if (m_levelIndex == 0) return;
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    if (m_pHost->IsAbilityButtonDown(3) != 0) {  // vt+0x8c
        dash->Impulse(1.0f);                       // 0x0024bce0; TOC +0x4300
        // The kick's spark on the hot spot (the inlined CKSrvFx::StartEffect: not kept).
        CKSparkFxData* kick = static_cast<CKSparkFxData*>(m_pDashKickSparkFxData);
        kick->m_unk10 = m_pHost->GetHotspot(m_ui8HotSpot);  // vt+0xcc
        kick->m_unk0c = nullptr;
        TransformFx::Start(m_pDashKickSparkFxData, this);
    }
    dash->Update(dt);  // 0x0024bd40
    m_fDashTimeScale = dash->m_fValue;
    m_pHost->SetHero1d20(m_fDashTimeScale);  // vt+0x84
    // Near the dash's top value (cror: >=) the dash particles and spark are taken; below (bge without cror: a NaN
    // keeps them) they are let go.
    if (m_fDashTimeScale >= dash->m_unk04[0] - kNearTop) {
        if (m_pActiveDashParticles == nullptr) {
            IKSerializable* spot = m_pHost->GetHotspot(m_ui8HotSpot);
            CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(m_pDashParticlesData);
            particles->m_pAttachOwner = nullptr;
            particles->m_pAttachHotSpot = spot;
            m_pActiveDashParticles = TransformFx::Acquire(m_pDashParticlesData, this);
        }
        if (m_pActiveDashSparks == nullptr) {
            IKSerializable* spot = m_pHost->GetHotspot(m_ui8HotSpot);
            CKSparkFxData* spark = static_cast<CKSparkFxData*>(m_pDashSparkFxData);
            spark->m_unk0c = nullptr;
            spark->m_unk10 = spot;
            m_pActiveDashSparks = TransformFx::Acquire(m_pDashSparkFxData, this);
        }
    }
    if (m_fDashTimeScale < dash->m_unk04[0] - kNearTop) {
        TransformFx::ReleaseParticles(&m_pActiveDashParticles, this);
        TransformFx::ReleaseSpark(&m_pActiveDashSparks, this);
    }
}

// 0x003ead10 CKWindTwister_UpdateEffect_maybe
void CKWindTwister::UpdateEffect(float dt) {
    const float scaled = dt * m_fDashTimeScale;
    m_fEffectTimer = scaled + m_fEffectTimer;
    m_fUnusedTimer2 = scaled + m_fUnusedTimer2;
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    float timeScale = m_fDashTimeScale;
    if (m_pDashSound != nullptr) {
        // The dash sound's pitch: 1 at the dash's low value up to +0x310 at its top (cror: <= 0 gives 0, >= 1 gives 1).
        const float low = dash->m_unk04[1];
        float t = (timeScale - low) / (dash->m_unk04[0] - low);
        if (t <= 0.0f) {
            t = 0.0f;
        } else if (t >= 1.0f) {
            t = 1.0f;
        }
        m_pDashSound->SetPitch(ppc::fmadds(t, m_fDashSoundTopPitch - 1.0f, 1.0f));  // 0x00110ea0
        timeScale = m_fDashTimeScale;
    }
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    static_cast<CKS08ElementDamage*>(m_pSecondaryDamage)->m_fKnockbackForce = timeScale * m_afSecondaryKnockbackSpeed[level];

    // Node 0: fades in from +0x16c to +0x160 over +0x194 while the loop runs, then at +0x160 (once); after the stop it
    // fades from its stop alpha to +0x178 and is hidden +0x198 after the stop. Not tied to the height.
    if (IsShown(m_pConeMesh0)) {
        IKSerializable* node = m_pConeMesh0;
        const float t = m_fEffectTimer;
        const float in = m_fCone0FadeInTime;
        if (t < in && m_bLoop != 0) {
            if (static_cast<CNode*>(node)->m_lGeometryList != nullptr) {
                const float rest = (in - t) / in;
                const float done = t / in;
                TransformFx::SetGeometriesAlpha(
                    node, AlphaByte(ppc::fmadds(SignedToFloat(m_ai32Cone0StartAlpha[level]), rest, SignedToFloat(m_ai32Cone0FullAlpha[level]) * done)));
            }
        } else if (m_abConeFadeState[0] == 0 && m_bLoop != 0) {
            if (static_cast<CNode*>(node)->m_lGeometryList != nullptr) {
                TransformFx::SetGeometriesAlpha(node, AlphaByte(SignedToFloat(m_ai32Cone0FullAlpha[level])));
            }
            m_abConeFadeState[0] = 1;
        }
        if (m_bLoop == 0 && m_abConeFadeState[0] != 0) {
            const float now = m_fEffectTimer;
            const float out = m_fCone0FadeOutTime;
            if (now - m_fStopFxTime >= out) {
                m_abConeFadeState[0] = 0;
                TransformFx::HideNode(node);
            } else if (static_cast<CNode*>(node)->m_lGeometryList != nullptr) {
                // BUG(original): the alpha runs on the whole timer, not on the time since the stop.
                const float rest = (out - now) / out;
                const float done = now / out;
                TransformFx::SetGeometriesAlpha(
                    node, AlphaByte(ppc::fmadds(UnsignedToFloat(m_aui32FadeOutStartAlpha[0]), rest, SignedToFloat(m_ai32Cone0EndAlpha[level]) * done)));
            }
        }
        const float wobble = m_fCone0ScaleWobble;
        const float u = WT_RAND_U16();
        const float spin = WrapDegrees(m_afCone0SpinDegPerSec[level] * m_fEffectTimer);
        const float scale = ppc::fmadds(u / kRandMax * -2.0f, m_fCone0ScaleWobble, wobble + 1.0f) * m_afCone0Scale[level];
        SpinNode(node, spin, scale, nullptr);
    }

    // Nodes 1 and 2: the alpha (fading in from the start alpha, the full alpha, after the stop from the stop alpha to the
    // end alpha; hidden when the timer passes the fade-out time) scaled down by the user's height above the ground
    // between the two heights (0 above the second), set when it differs from the first geometry's.
    for (uint32_t n = 1; n < 3; ++n) {
        IKSerializable* node = n == 1 ? m_pConeMesh1 : m_pConeMesh2;
        if (n == 2 && m_levelIndex != 2) break;
        if (!IsShown(node)) continue;
        const uint32_t lv = static_cast<uint32_t>(m_levelIndex);
        const float t = m_fEffectTimer;
        // Node 2's full and start alphas are read at index 2 (+0x210 / +0x21c), its level being 2.
        const float in = n == 1 ? m_fCone1FadeInTime : m_fCone2FadeInTime;
        float alpha = SignedToFloat(n == 1 ? m_ai32Cone1FullAlpha[lv] : m_ai32Cone2FullAlpha[2]);
        if (t < in && m_bLoop != 0) {
            const float done = t / in;
            const float rest = (in - t) / in;
            alpha = ppc::fmadds(SignedToFloat(n == 1 ? m_ai32Cone1StartAlpha[lv] : m_ai32Cone2StartAlpha[2]), rest, alpha * done);
        } else {
            const uint8_t loop = m_bLoop;
            bool fading = true;
            if (m_abConeFadeState[n] == 0) {
                if (loop == 0) {
                    fading = false;
                } else {
                    m_abConeFadeState[n] = 1;
                }
            }
            if (fading && loop == 0 && m_abConeFadeState[n] != 0) {
                const float out = n == 1 ? m_fCone1FadeOutTime : m_fCone2FadeOutTime;
                if (t >= out) {
                    m_abConeFadeState[n] = 0;
                    TransformFx::HideNode(node);
                }
                // BUG(original): the fade-out runs on the whole timer (and hides on it), not on the time since the stop.
                const uint32_t lv2 = static_cast<uint32_t>(m_levelIndex);
                const float now = m_fEffectTimer;
                const float out2 = n == 1 ? m_fCone1FadeOutTime : m_fCone2FadeOutTime;
                const float rest = (out2 - now) / out2;
                const float done = now / out2;
                alpha = ppc::fmadds(UnsignedToFloat(m_aui32FadeOutStartAlpha[n]), rest,
                                    SignedToFloat(n == 1 ? m_ai32Cone1EndAlpha[lv2] : m_ai32Cone2EndAlpha[lv2]) * done);
            }
        }
        const CVector3 position = m_pHost->GetOwnerPosition();  // vt+0x10
        const CVector3 ground = m_pHost->GetOwnerGroundPoint();  // vt+0x14
        const float height = position.y - ground.y;
        const uint32_t lv3 = static_cast<uint32_t>(m_levelIndex);
        const float gone = n == 1 ? m_afCone1FadeHeightEnd[lv3] : m_afCone2FadeHeightEnd[lv3];
        const float start = n == 1 ? m_afCone1FadeHeightStart[lv3] : m_afCone2FadeHeightStart[lv3];
        uint8_t byte = 0;
        if (height > gone) {
            byte = 0;
        } else if (height >= start) {
            byte = AlphaByte(alpha * ((gone - height) / (gone - start)));
        } else {
            byte = AlphaByte(alpha);
        }
        SetAlphaIfChanged(node, byte);
        const float wobble = n == 1 ? m_fCone1ScaleWobble : m_fCone2ScaleWobble;
        const float u = WT_RAND_U16();
        const uint32_t lv4 = static_cast<uint32_t>(m_levelIndex);
        const float spin = WrapDegrees((n == 1 ? m_afCone1SpinDegPerSec[lv4] : m_afCone2SpinDegPerSec[lv4]) * m_fEffectTimer);
        const float scale = ppc::fmadds(u / kRandMax * -2.0f, n == 1 ? m_fCone1ScaleWobble : m_fCone2ScaleWobble, wobble + 1.0f) *
                            (n == 1 ? m_afCone1Scale[lv4] : m_afCone2Scale[lv4]);
        SpinNode(node, spin, scale, &height);
    }

    if (m_pActiveAnimFx != nullptr) static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Update(scaled);  // TocBridge 0x0098f4b0

    // The ground mesh pop under the user while it is in the air (above level 0), at hot spot 0.
    if (IsGroundTrailActive() != 0) {  // vt+0x8c
        if (m_pActiveMeshPop == nullptr) {
            IKSerializable* spot = m_pHost->GetHotspot(0);  // vt+0xcc
            CKMeshPopFxData* data = static_cast<CKMeshPopFxData*>(m_pGroundMeshPopFxData);
            data->m_unk08 = nullptr;
            data->m_unk0c = static_cast<CSGHotSpot*>(spot);
            IKFx* fx = TransformFx::Acquire(m_pGroundMeshPopFxData, this);
            m_pActiveMeshPop = fx;
            if (fx != nullptr) static_cast<CKMeshPopNodeFx*>(static_cast<IKSerializable*>(fx))->SetActive(this, 1);  // 0x001cb568
        }
    } else {
        TransformFx::ReleaseMeshPop(&m_pActiveMeshPop, this);
    }

    // Level 2: while dashing (the time scale above the dash's low value: ble, a NaN does not), a projectile every
    // +0x2fc (+- +0x300) seconds of scaled time.
    if (m_levelIndex != 2) return;
    const float value = m_fDashTimeScale;
    const float low = dash->m_unk04[1];
    if (!(value > low)) return;
    if (!(m_fNextProjTimer < 0.0f)) {  // blt
        m_fNextProjTimer = m_fNextProjTimer - scaled;
        return;
    }
    const float high = dash->m_unk04[0];
    const float range = high - low;
    const float speed = ppc::fmadds((high - value) / range, m_fProjSpeedMin, (value - low) / range * m_fProjSpeedMax);
    // A random horizontal direction (two draws), normalised, then its y set to +0x308.
    CVector3 dir = kNullVector;
    dir.x = ppc::fmadds(WT_RAND_U16(), kRandScale, 1.0f);
    dir.z = ppc::fmadds(WT_RAND_U16(), kRandScale, 1.0f);
    const float length = Sqrtf(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dir.z = dir.z * inverse;
        dir.x = dir.x * inverse;
        dir.y = dir.y * inverse;
    }
    dir.y = m_fProjDirY;
    const CVector3 spot = m_pHost->GetHotspotPosition(m_ui8HotSpot);  // vt+0xd0
    CVector3 pos;
    pos.x = spot.x;
    pos.z = spot.z;
    pos.y = spot.y + m_fProjHeightOffset;
    // A third draw picks the projectile: below 0 the second one (+0x2ec), else the first (+0x2e8).
    const bool second = ppc::fmadds(WT_RAND_U16(), kRandScale, 1.0f) < 0.0f;
    CKProjectileAccessor* first = static_cast<CKProjectileAccessor*>(m_pProjectileAccessorA);
    if (first->m_pProjectileType != nullptr && !second) {
        first->LaunchEx(&pos, &dir, speed, m_pProjectileDamage, m_pHost->GetOwner(), nullptr);  // vt+0x08; 0x001f2988
    }
    CKProjectileAccessor* other = static_cast<CKProjectileAccessor*>(m_pProjectileAccessorB);
    if (other->m_pProjectileType != nullptr && second) {
        other->LaunchEx(&pos, &dir, speed, m_pProjectileDamage, m_pHost->GetOwner(), nullptr);
    }
    // The next one: (+0x2fc + +0x300 + +0x300 x a draw in [-1, 1]) / the time scale.
    const float spread = m_fProjIntervalSpread + 0.0f;  // TOC +0x4338
    const float base = m_fProjInterval;
    const float t = WT_RAND_U16() / kRandMax * -2.0f;  // TOC +0x4378 / +0x437c
    m_fNextProjTimer = (base + ppc::fmadds(t, m_fProjIntervalSpread, spread)) / m_fDashTimeScale;
}

// 0x003ed2c0 CKWindTwister_SetFxActive
void CKWindTwister::SetFxActive(int32_t on) {
    if (on == 0) {
        TransformFx::ReleaseParticles(&m_pActiveLoopParticles, this);
        TransformFx::ReleaseParticles(&m_pActiveDashParticles, this);
        TransformFx::ReleaseSpark(&m_pActiveDashSparks, this);
        if (m_pActiveAnimFx != nullptr) {
            static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Stop();  // TocBridge 0x0098f4c0 -> 0x005cc990
            m_pActiveAnimFx = nullptr;
        }
        if (m_pLoopSound != nullptr) {
            // The end sound (dictionary 3) on the user, then the loop sound stopped.
            CKSound* endSound = GetFxSound(4);
            if (endSound != nullptr) {
                endSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));  // 0x00111350
                endSound->Play(0.0f);                                       // 0x00111230; TOC +0x4338
            }
            m_pLoopSound->Stop(0);  // 0x001111b0
            m_pLoopSound = nullptr;
        }
        if (m_pDashSound != nullptr) {
            m_pDashSound->Stop(0);
            m_pDashSound = nullptr;
        }
        // The trail's ribbons off, their points laid out between the anchors (CTrailNodeFx_SetRibbonActive_maybe
        // 0x9bdfb8, inlined; the count read once, a byte counter).
        CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pTrailNode);
        if (trail == nullptr) return;
        const uint32_t count = trail->m_ui32NbTrail;
        for (uint8_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 0, 1);
        return;
    }
    CKParticlesEffectFxData* loop = static_cast<CKParticlesEffectFxData*>(m_pLoopParticlesData);
    loop->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpot);  // vt+0xcc
    loop->m_pAttachOwner = nullptr;
    m_pActiveLoopParticles = TransformFx::Acquire(m_pLoopParticlesData, this);
    if (m_levelIndex == 1 || static_cast<uint32_t>(m_levelIndex) > 1) {
        IKSerializable* collection = m_levelIndex == 1 ? m_pAnimFxLevel1 : m_pAnimFxLevel2;
        m_pActiveAnimFx = collection;
        CSGLeaf* node = TransformFx::OwnerNode(m_pHost);
        SAnimatedFxRig* rigs = TransformFx::AttachmentSets(m_pHost);
        static_cast<CKAnimatedFxCollection*>(collection)->Play(
            node, rigs, static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot)));  // TocBridge 0x0098f4d0 -> 0x005cc528
    }
    CKSound* loopSound = GetFxSound(1);
    m_pLoopSound = loopSound;
    if (loopSound != nullptr) {
        loopSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));  // 0x00111350
        m_pLoopSound->Play(0.0f);                                        // 0x00111230
    }
    CKSound* dashSound = GetFxSound(3);
    m_pDashSound = dashSound;
    if (dashSound != nullptr) {
        dashSound->SetPitch(1.0f);  // 0x00110ea0; TOC +0x4300
        m_pDashSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));
        m_pDashSound->Play(0.0f);
    }
    ApplyDamageParams(0);  // vt+0x88 (one Rand_Int: the knock angle)
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    static_cast<CKS08ElementDamage*>(m_pSecondaryDamage)->m_fKnockbackForce = m_afSecondaryKnockbackSpeed[level];
    m_pHost->SetAbilityAttackSpheres(this, 1, m_afPrimarySphereRadius[level], m_elementDamage, m_afSecondarySphereRadius[level], m_pSecondaryDamage);  // vt+0xfc
    // The trail: node 0's world matrix brought up to date (vt+0x50), its ribbons on (their points laid out between the
    // anchors).
    CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pTrailNode);
    if (trail == nullptr) return;
    if (m_pConeMesh0 != nullptr) static_cast<CSGLeaf*>(m_pConeMesh0)->ForceWorldMatrixUpdate();
    const uint32_t count = static_cast<CTrailNodeFx*>(m_pTrailNode)->m_ui32NbTrail;
    for (uint8_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 1, 1);
}

// 0x003e7850 CKWindTwister_PostLoad
int32_t CKWindTwister::PostLoad(int32_t type) {
    CKTransformElement::PostLoad(type);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pConeMesh0), 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pConeMesh1), 1, 0, 0);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pConeMesh2), 1, 0, 0);
    CSGLeaf* trail = static_cast<CSGLeaf*>(m_pTrailNode);
    if (trail == nullptr) return 1;
    if (trail->m_pParent != nullptr) trail->m_pParent->RemoveChild(trail);  // vt+0x78
    CSGBranch* parent = m_pConeMesh0 != nullptr ? static_cast<CSGBranch*>(m_pConeMesh0)
                                            : static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
    parent->AddChild(static_cast<CSGLeaf*>(m_pTrailNode));  // vt+0x70
    return 1;
}

// 0x003e8260 CKWindTwister_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 428
// bytes of references and words (714 bytes in all).
int32_t CKWindTwister::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_pDashSparkFxData);
        IKFile_ReadRef(file, &m_pDashKickSparkFxData);
        IKFile_ReadRef(file, &m_pGroundMeshPopFxData);
        IKFile_ReadRef(file, &m_pLoopParticlesData);
        IKFile_ReadRef(file, &m_pDashParticlesData);
        IKFile_ReadRef(file, &m_pConeMesh0);
        IKFile_ReadRef(file, &m_pConeMesh1);
        IKFile_ReadRef(file, &m_pConeMesh2);
        IKFile_ReadRef(file, &m_pDashImpulsion);
        IKFile_ReadRef(file, &m_pProjectileAccessorA);
        IKFile_ReadRef(file, &m_pProjectileAccessorB);
        IKFile_ReadRef(file, &m_pAnimFxLevel1);
        IKFile_ReadRef(file, &m_pAnimFxLevel2);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_afPrimarySphereRadius[i]);
            ReadS32LE(file, &m_ai32Cone0FullAlpha[i]);
            ReadS32LE(file, &m_ai32Cone0StartAlpha[i]);
            ReadS32LE(file, &m_ai32Cone0EndAlpha[i]);
            ReadF32LE(file, &m_afCone0Scale[i]);
            ReadF32LE(file, &m_afCone0SpinDegPerSec[i]);
            ReadS32LE(file, &m_ai32Cone1FullAlpha[i]);
            ReadS32LE(file, &m_ai32Cone1StartAlpha[i]);
            ReadS32LE(file, &m_ai32Cone1EndAlpha[i]);
            ReadF32LE(file, &m_afCone1Scale[i]);
            ReadF32LE(file, &m_afCone1SpinDegPerSec[i]);
            ReadF32LE(file, &m_afCone1FadeHeightStart[i]);
            ReadF32LE(file, &m_afCone1FadeHeightEnd[i]);
            ReadS32LE(file, &m_ai32Cone2FullAlpha[i]);
            ReadS32LE(file, &m_ai32Cone2StartAlpha[i]);
            ReadS32LE(file, &m_ai32Cone2EndAlpha[i]);
            ReadF32LE(file, &m_afCone2Scale[i]);
            ReadF32LE(file, &m_afCone2SpinDegPerSec[i]);
            ReadF32LE(file, &m_afCone2FadeHeightStart[i]);
            ReadF32LE(file, &m_afCone2FadeHeightEnd[i]);
        }
        ReadF32LE(file, &m_fCone0ScaleWobble);
        ReadF32LE(file, &m_fCone0FadeInTime);
        ReadF32LE(file, &m_fCone0FadeOutTime);
        ReadF32LE(file, &m_fProjSpeedMin);
        ReadF32LE(file, &m_fProjSpeedMax);
        ReadF32LE(file, &m_fProjInterval);
        ReadF32LE(file, &m_fProjIntervalSpread);
        ReadF32LE(file, &m_fProjHeightOffset);
        ReadF32LE(file, &m_fProjDirY);
        ReadF32LE(file, &m_fCone1ScaleWobble);
        ReadF32LE(file, &m_fCone1FadeInTime);
        ReadF32LE(file, &m_fCone1FadeOutTime);
        ReadF32LE(file, &m_unk290);
        ReadF32LE(file, &m_unk294);
        ReadF32LE(file, &m_unk298);
        ReadF32LE(file, &m_unk29c);
        ReadF32LE(file, &m_unk2a0);
        ReadF32LE(file, &m_unk2a4);
        ReadS32LE(file, &m_unk2a8);
        ReadU32LE(file, &m_unk2ac);
        ReadF32LE(file, &m_fCone2ScaleWobble);
        ReadF32LE(file, &m_fCone2FadeInTime);
        ReadF32LE(file, &m_fCone2FadeOutTime);
        IKFile_ReadRef(file, &m_pSoundDico);
        ReadF32LE(file, &m_fDashSoundTopPitch);
        IKFile_ReadRef(file, &m_pProjectileDamage);
        IKFile_ReadRef(file, &m_pSecondaryDamage);
        ReadF32LE(file, &m_afSecondarySphereRadius[0]);
        ReadF32LE(file, &m_afSecondaryKnockbackSpeed[0]);
        ReadF32LE(file, &m_afSecondarySphereRadius[1]);
        ReadF32LE(file, &m_afSecondaryKnockbackSpeed[1]);
        ReadF32LE(file, &m_afSecondarySphereRadius[2]);
        ReadF32LE(file, &m_afSecondaryKnockbackSpeed[2]);
        IKFile_ReadRef(file, &m_pTrailNode);
    }
    return 1;
}
