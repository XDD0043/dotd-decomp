// CKShadowSurprise.cpp - reconstructed original translation unit 0x3d7500-0x3dc3d8 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKShadowSurprise  key 0xa4cc  category Logic  size 0x274  vtable 0xb247f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3d7500  CKShadowSurprise_Delete
//   [x] 0x3d7550  CKShadowSurprise_GetAbilityId
//   [x] 0x3d7558  CKShadowSurprise_GetFamilyId
//   [x] 0x3d7560  CKShadowSurprise_IsGroundTrailActive_maybe
//   [x] 0x3d75c0  CKShadowSurprise_GetFxSound_maybe
//   [x] 0x3d7798  CKShadowSurprise_ApplyHeroControl
//   [x] 0x3d7948  CKShadowSurprise_End
//   [x] 0x3d7ac0  CKShadowSurprise_StopFx
//   [x] 0x3d7d00  CKShadowSurprise_Start
//   [x] 0x3d7d70  CKShadowSurprise_ResetRuntime
//   [x] 0x3d7e40  CKShadowSurprise_PostLoad
//   [x] 0x3d7e90  CKShadowSurprise_RecursiveRegistration  (inherited: CKTransformElement_RecursiveRegistration)
//   [x] 0x3d7eb8  CKShadowSurprise_Destroy  (inherited: CKTransformElement_Destroy)
//   [x] 0x3d7ee0  CKShadowSurprise_Construct
//   [x] 0x3d7f18  CKShadowSurprise_DeleteArray
//   [x] 0x3d7fb8  CKShadowSurprise_DeletingDestructor  (the destructor; delete)
//   [x] 0x3d8000  CKShadowSurprise_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3d8030  CKShadowSurprise_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x3d8060  RegisterCKShadowSurpriseClass
//   [ ] 0x3d80e8  _GLOBAL__D_3d80e8
//   [ ] 0x3d80f8  _GLOBAL__I_3d80f8
//   [x] 0x3d8108  CKShadowSurprise_Construct_2  (the same as CKShadowSurprise_Construct)
//   [x] 0x3d8140  CKShadowSurprise_CreateArray
//   [x] 0x3d81f0  CKShadowSurprise_Create
//   [x] 0x3d8248  CKShadowSurprise_UpdateEffect_maybe
//   [x] 0x3d8ef8  CKShadowSurprise_Load
//   [ ] 0x3d9e48  CKShadowSurprise_Save
//   [x] 0x3dae90  CKShadowSurprise_SetFxActive
//   [x] 0x3dbfd0  CKShadowSurprise_UpdateAttack_maybe
//
//   [ ] 0x9c0848  CKShadowSurprise_IsKindOfClass  [inline]
//   [x] 0x9c0898  CKShadowSurprise_GetClassType  [inline]
//   [x] 0x9c08a0  CKShadowSurprise_GetClassID  [inline]
//   [x] 0x9c08a8  CKShadowSurprise_StartEmitterFx  [inline]
#include "k2000/logic/render/CKShadowSurprise.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGSectorRoot.h"

namespace {
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// (float) of a word read with lwz then extsw (signed) / clrldi (unsigned): fcfid, frsp.
float SignedToFloat(int32_t word) { return static_cast<float>(static_cast<double>(word)); }
float UnsignedToFloat(uint32_t word) { return static_cast<float>(static_cast<double>(word)); }
// The alpha byte of a float (fctiwz, the low byte through stfiwx / lbz).
uint8_t AlphaByte(float value) { return static_cast<uint8_t>(ppc::fctiwz(value)); }
// A spin angle brought into [-360, 360) by steps of 720 (TOC +0x4160 / +0x4164 / +0x4168).
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
// A pooled explosion at the user's hot spot +0x13c (host vt+0xd0), turned to the user's up (host vt+0x2c,
// CKExplosionNodeFx_SetDirection 0x1b5e20); with `damage`, it hurts what it touches (the user's collision group / mask).
void ExplodeAtHotSpot(IKSerializable* data, const IKSerializable* owner, CKS08AbilityHostBase* host, uint8_t hotSpot,
                      IKSerializable* damage) {
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(TransformFx::Acquire(data, owner));
    if (fx == nullptr) return;
    if (damage != nullptr) {
        fx->SetDamageOwner(host->GetOwner(), owner);              // vt+0x08; 0x001b6340
        fx->SetDamageCategory(host->GetCollisionGroup(), owner);  // vt+0xb0; 0x001b6318
        fx->SetDamageFlags(host->GetCollisionMask(), owner);      // vt+0xb4; 0x001b62f0
        fx->SetDamage(damage, owner);                             // 0x001b62c8
    }
    const CVector3 position = host->GetHotspotPosition(hotSpot);
    fx->SetTranslation(&position, owner);  // 0x001b66e8
    const CVector3 up = host->GetOwnerUp();
    fx->SetDirection(&up, owner);  // 0x001b5e20
    fx->Trigger(owner, 0);         // 0x001b82a8
    fx->ReleaseReservation(owner);  // vt+0x54
}
void PlayAttached(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(TransformFx::OwnerNode(host));  // vt+0x08, +0x1c; 0x00111350
    sound->Play(0.0f);                                     // 0x00111230; TOC +0x411c
}
// One Rand_Int draw, its low 16 bits as a float (clrldi 48, fcfid, frsp).
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
constexpr float kRandMax = 65535.0f;          // TOC +0x4174
constexpr float kRandScale = -0x1.0001p-15f;  // TOC +0x4170 (0xb8000080)
}  // namespace

// 0x003d75c0 CKShadowSurprise_GetFxSound_maybe
CKSound* CKShadowSurprise::GetFxSound(uint32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    auto usable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00111000
    };
    // Level 2: `two` when usable, then (levels 1 and 2) `one` when usable, else `base`.
    auto byLevel = [&](CKSound* base, uint32_t one, uint32_t two) -> CKSound* {
        if (m_levelIndex == 2 && usable(two)) return sounds->GetSound(two);
        if ((m_levelIndex == 1 || m_levelIndex == 2) && usable(one)) return sounds->GetSound(one);
        return base;
    };
    if (which == 1) return byLevel(sounds->GetSound(0), 1, 2);  // the loop
    if (which == 3) return byLevel(nullptr, 3, 4);              // the dash (level 0: none)
    return nullptr;
}

// 0x003d7560 CKShadowSurprise_IsGroundTrailActive_maybe
uint8_t CKShadowSurprise::IsGroundTrailActive() {
    if (m_levelIndex == 0) return 0;
    return m_pHost->IsOnGround();  // vt+0x30
}

// 0x003d7798 CKShadowSurprise_ApplyHeroControl
void CKShadowSurprise::ApplyHeroControl(uint8_t on) {
    CKTransformElement::ApplyHeroControl(on);
    const uint8_t allow = on != 0 ? 1 : 0;
    m_pHost->SetHeroActionPermission(7, allow, allow, allow);  // vt+0x44
    m_pHost->SetHeroActionPermission(0xb, allow, allow, allow);
    m_pHost->SetHeroActionPermission(0xc, allow, allow, allow);
}

// 0x003d7948 CKShadowSurprise_End
void CKShadowSurprise::End(int32_t forced) {
    if (m_pLoopSound != nullptr) {
        m_pLoopSound->Stop(0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    if (m_pDashSound != nullptr) {
        m_pDashSound->Stop(0);
        m_pDashSound = nullptr;
    }
    m_pHost->SetHero1d20(1.0f);                                                // vt+0x84; TOC +0x4118
    m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc
    TransformFx::ShowNode(TransformFx::OwnerNode(m_pHost));
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pShadowMesh), 1, 0, 0);  // 0x005832a8
    CKTransformElement::End(forced);
}

// 0x003d7ac0 CKShadowSurprise_StopFx
void CKShadowSurprise::StopFx() {
    CKTransformElement::StopFx();
    ApplyDamageParams(0);  // vt+0x88
    m_pHost->SetAbilityAttackSpheres(this, 1, m_afHitSphereRadius[m_levelIndex], m_elementDamage, 1.0f, nullptr);  // vt+0xfc
    m_pHost->SetHero1d20(1.0f);                       // vt+0x84
    m_pHost->SetHeroActionPermission(0, 1, 1, 1);  // vt+0x44
    m_pHost->SetHeroActionPermission(1, 1, 1, 1);
    m_pHost->SetHeroActionPermission(3, 1, 1, 1);
    if (m_pShadowMesh != nullptr) {
        // The fade-out starts from the first geometry's alpha (none: the level's rolling alpha).
        CGeometry* first = static_cast<CGeometry*>(static_cast<CNode*>(m_pShadowMesh)->m_lGeometryList);
        m_ui32FadeOutStartAlpha = first != nullptr ? first->m_cGeometryColor[3] : static_cast<uint32_t>(m_ai32MeshFullAlpha[m_levelIndex]);
        if (m_fFadeOutTime == 0.0f) {
            SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pShadowMesh), 1, 0, 0);  // 0x005832a8
        } else {
            m_bMeshFadedIn = 1;
        }
    }
    m_fFadeOutStartTime = m_fScaledTimer;
}

// 0x003d7d00 CKShadowSurprise_Start
void CKShadowSurprise::Start(CKS08AbilityHostBase* host) {
    m_pLoopSound = nullptr;
    m_pDashSound = nullptr;
    CKTransformElement::Start(host);
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    dash->m_fImpulseTimer = 0.0f;
    dash->m_fValue = 0.0f;
    dash->m_fSpeed = 0.0f;
    m_bMeshFadedIn = 0;
    m_fNextShotTimer = m_afProjectileParams[2];
    m_fDashTimeScale = 1.0f;  // TOC +0x4118
    m_fScaledTimer = 0.0f;
}

// 0x003d7d70 CKShadowSurprise_ResetRuntime: the base's reset (0x3dcea0), then the element's own words, and the
// damage object learns the ability id (the damage's vt+0x68 0x9c0b00 CKS08ElementDamage_SetAbilityId_maybe
// stores it at +0x38).
void CKShadowSurprise::ResetRuntime() {
    m_pLoopSound = nullptr;
    m_pDashSound = nullptr;
    CKTransformElement::ResetRuntime();
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_pLevel2ProjectileDamage);
    m_fDashTimeScale = 1.0f;  // TOC +0x4118
    m_pActivePointLight = nullptr;
    m_ui8HotSpot = 0;
    m_pActiveParticles = nullptr;
    m_bMeshFadedIn = 0;
    m_pActiveAnimFx = nullptr;
    m_fFadeOutStartTime = 0.0f;
    m_ui8Button = 1;
    m_fNextShotTimer = 0.0f;
    m_fScaledTimer = 0.0f;
    damage->m_i32AbilityId = GetAbilityId();
}

void CKShadowSurprise::SetShadowAlpha(uint8_t alpha) { TransformFx::SetGeometriesAlpha(m_pShadowMesh, alpha); }

// 0x003dae90 CKShadowSurprise_SetFxActive
void CKShadowSurprise::SetFxActive(int32_t on) {
    const CVector3 position = m_pHost->GetOwnerPosition();  // vt+0x10
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    if ((on & 0xff) == 0) {
        TransformFx::ReleaseParticles(&m_pActiveParticles, this);
        if (m_pActiveAnimFx != nullptr) {
            static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Stop();  // 0x005cc990
            m_pActiveAnimFx = nullptr;
        }
        ExplodeAtHotSpot(m_apEndExplosions[level], this, m_pHost, m_ui8HotSpot, m_apEndExplosionDamages[level]);
        TransformFx::ShowNode(TransformFx::OwnerNode(m_pHost));
        if (m_pActivePointLight != nullptr) {
            static_cast<IKFx*>(m_pActivePointLight)->StopAndRelease(this);  // vt+0x58
            m_pActivePointLight = nullptr;
        }
        if (m_pLoopSound != nullptr) {
            m_pLoopSound->Stop(0);  // 0x001111b0
            m_pLoopSound = nullptr;
        }
        if (m_pDashSound != nullptr) {
            m_pDashSound->Stop(0);
            m_pDashSound = nullptr;
        }
        return;
    }
    if (m_pShadowMesh != nullptr) {
        // The shadow node at the user, scaled, shown, its geometries in render stage 0xc with bit 5 (0x2c) at the
        // start alpha (the low byte of +0x16c[level]).
        CSGMovable* node = static_cast<CSGMovable*>(m_pShadowMesh);
        node->SetIdentity();                                                     // 0x000d08f0
        node->Scale(reinterpret_cast<const float*>(&m_avMeshScale[level]));           // 0x000d0d88
        TransformFx::SetNodePosition(m_pShadowMesh, position);
        TransformFx::ShowNode(m_pShadowMesh);
        CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pShadowMesh)->m_lGeometryList);
        const uint8_t alpha = static_cast<uint8_t>(static_cast<uint32_t>(m_ai32MeshStartAlpha[level]) & 0xffu);
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_BitProperties = (geometry->m_BitProperties & ~0x3fu) | 0x2cu;
            TransformFx::SetGeometryAlpha(geometry, alpha);
        }
    }
    CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(m_apParticlesFxData[level]);
    particles->m_ui8Flags = static_cast<uint8_t>(particles->m_ui8Flags & 0xefu);
    m_pActiveParticles = TransformFx::Acquire(m_apParticlesFxData[level], this);
    if (m_pActiveParticles != nullptr) {
        SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_pActiveParticles), &position, this);  // 0x001cdce0
        const CVector3 forward = m_pHost->GetHeroForward();  // vt+0x18
        const CVector3 up = m_pHost->GetOwnerUp();           // vt+0x2c
        SetOwnedParticleEffectTransform(static_cast<CKParticlesEffectNodeFx*>(m_pActiveParticles), &forward, &up, this);  // 0x001cdc08
    }
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_apAnimFx[level]);
    m_pActiveAnimFx = collection;
    collection->Play(static_cast<CSGLeaf*>(g_pEngine->m_dynamicSceneRoot), TransformFx::AttachmentSets(m_pHost),
                     nullptr);  // 0x005cc528
    collection->SetPosition(&position);  // 0x005cc8c8
    {
        const CVector3 forward = m_pHost->GetHeroForward();
        const CVector3 up = m_pHost->GetOwnerUp();
        collection->SetOrientation(&forward, &up);  // 0x005cc7f0
    }
    ExplodeAtHotSpot(m_pStartExplosion, this, m_pHost, m_ui8HotSpot, nullptr);
    TransformFx::HideNode(TransformFx::OwnerNode(m_pHost));
    CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_apPointLightFxData[level]);
    light->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpot);  // vt+0xcc
    light->m_pAttachNode = nullptr;
    m_pActivePointLight = TransformFx::Acquire(m_apPointLightFxData[level], this);
    m_pLoopSound = GetFxSound(1);
    if (m_pLoopSound != nullptr) PlayAttached(m_pLoopSound, m_pHost);
    m_pDashSound = GetFxSound(3);
    if (m_pDashSound != nullptr) {
        m_pDashSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));
        m_pDashSound->SetPitch(1.0f);  // 0x00110ea0; TOC +0x4118
        m_pDashSound->Play(0.0f);
    }
}

// 0x003d8248 CKShadowSurprise_UpdateEffect_maybe
void CKShadowSurprise::UpdateEffect(float dt) {
    const float scaled = dt * m_fDashTimeScale;
    const CVector3 position = m_pHost->GetOwnerPosition();  // vt+0x10
    m_fScaledTimer = scaled + m_fScaledTimer;
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    if (m_pDashSound != nullptr) {
        // The dash sound's pitch with the dash's value between its bottom and its top.
        const float bottom = dash->m_unk04[1];
        float t = (m_fDashTimeScale - bottom) / (dash->m_unk04[0] - bottom);
        if (t <= 0.0f) {
            t = 0.0f;
        } else if (t >= 1.0f) {
            t = 1.0f;
        }
        m_pDashSound->SetPitch(ppc::fmadds(t, m_fDashSoundTopPitch - 1.0f, 1.0f));  // 0x00110ea0
    }
    if (m_pShadowMesh != nullptr) {
        // The fades: in (+0x16c -> +0x160 over +0x1cc), then out once the loop is over (+0x268 -> +0x178 over +0x1d0).
        const float timer = m_fScaledTimer;
        if (timer < m_fFadeInTime) {
            const float rest = (m_fFadeInTime - timer) / m_fFadeInTime;
            const float done = timer / m_fFadeInTime;
            SetShadowAlpha(AlphaByte(ppc::fmadds(SignedToFloat(m_ai32MeshStartAlpha[level]), rest, SignedToFloat(m_ai32MeshFullAlpha[level]) * done)));
        } else if (m_bMeshFadedIn == 0) {
            SetShadowAlpha(AlphaByte(SignedToFloat(m_ai32MeshFullAlpha[level])));
            m_bMeshFadedIn = 1;
        }
        if (m_bLoop == 0 && m_bMeshFadedIn != 0) {
            const float now = m_fScaledTimer;
            if (now - m_fFadeOutStartTime >= m_fFadeOutTime) {
                m_bMeshFadedIn = 0;
                SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pShadowMesh), 1, 1, 0);  // 0x005832a8
            } else {
                // BUG(original): the alpha runs on the whole timer, not on the time since the fade-out started.
                const float rest = (m_fFadeOutTime - now) / m_fFadeOutTime;
                const float done = now / m_fFadeOutTime;
                SetShadowAlpha(AlphaByte(ppc::fmadds(UnsignedToFloat(m_ui32FadeOutStartAlpha), rest, SignedToFloat(m_ai32MeshEndAlpha[level]) * done)));
            }
        }
        // The spin: an identity (the frame's pads kept) turned about z, y and x by the timer times the level's speeds,
        // placed at the user, scaled by +0x1a8[level].
        CMatrix34 matrix;
        std::memcpy(&matrix, &static_cast<CSGMovable*>(m_pShadowMesh)->m_pRwFrame->modelling, sizeof(matrix));
        matrix.m_right = CVector3{1.0f, 0.0f, 0.0f};
        matrix.m_ui32Flags = 0x20003u;
        matrix.m_up = CVector3{0.0f, 1.0f, 0.0f};
        matrix.m_at = CVector3{0.0f, 0.0f, 1.0f};
        matrix.m_pos = CVector3{0.0f, 0.0f, 0.0f};
        const float spinTime = m_fScaledTimer;
        const float spinX = WrapDegrees(spinTime * m_afSpinXDegPerSec[level]);
        const float spinY = WrapDegrees(spinTime * m_afSpinYDegPerSec[level]);
        const float spinZ = WrapDegrees(spinTime * m_afSpinZDegPerSec[level]);
        Mat4_RotateLocalZDeg(spinZ, &matrix);  // 0x002419c0
        Mat4_RotateLocalYDeg(spinY, &matrix);  // 0x002413d0
        Mat4_RotateLocalXDeg(spinX, &matrix);  // 0x00241118
        matrix.m_pos = position;
        matrix.m_ui32Flags &= ~0x20000u;
        RwMatrixScalePreConcat_Thunk(&matrix, &m_avMeshScale[level]);  // 0x0023f670
        static_cast<CSGMovable*>(m_pShadowMesh)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    }
    if (m_pActiveParticles != nullptr) {
        SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_pActiveParticles), &position, this);  // 0x001cdce0
        const CVector3 forward = m_pHost->GetHeroForward();  // vt+0x18
        const CVector3 up = m_pHost->GetOwnerUp();           // vt+0x2c
        SetOwnedParticleEffectTransform(static_cast<CKParticlesEffectNodeFx*>(m_pActiveParticles), &forward, &up, this);  // 0x001cdc08
    }
    if (m_pActiveAnimFx != nullptr) {
        CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx);
        collection->Update(scaled);          // 0x005cccb0
        collection->SetPosition(&position);  // 0x005cc8c8
        const CVector3 forward = m_pHost->GetHeroForward();
        const CVector3 up = m_pHost->GetOwnerUp();
        collection->SetOrientation(&forward, &up);  // 0x005cc7f0
    }
    if (m_levelIndex == 0) return;
    m_pHost->SetAbilityParam11f8(m_fDashTimeScale * m_groundMode1P11f8[0], m_fDashTimeScale * m_groundMode1P11f8[1], m_fDashTimeScale * m_airP11f8,
                                 1, 1, 1);  // vt+0x68
    if (m_levelIndex != 2) return;
    if (!(m_fNextShotTimer < 0.0f)) {
        m_fNextShotTimer = m_fNextShotTimer - scaled;
        return;
    }
    // Level 2: a projectile from the hot spot, in a random horizontal direction raised by +0x248, its speed between
    // +0x234 (the dash at its bottom) and +0x238 (at its top); the next one in +0x23c (+- +0x240) scaled seconds.
    const float speedAtBottom = m_afProjectileParams[0];
    const float scale = m_fDashTimeScale;
    const float speedAtTop = m_afProjectileParams[1];
    const float bottom = dash->m_unk04[1];
    const float top = dash->m_unk04[0];
    CVector3 direction{0.0f, 0.0f, 0.0f};  // 0x00c50d64
    direction.x = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);  // 0x00011500
    const float y2 = direction.y * direction.y;
    direction.z = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
    const float length = Sqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, y2)));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    }
    direction.y = m_afProjectileParams[5];
    const CVector3 spot = m_pHost->GetHotspotPosition(m_ui8HotSpot);  // vt+0xd0
    const CVector3 at{spot.x, spot.y + m_afProjectileParams[4], spot.z};
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_pLevel2Projectile);
    if (accessor->m_pProjectileType != nullptr) {
        const float range = top - bottom;
        IKSerializable* owner = m_pHost->GetOwner();  // vt+0x08
        const float speed = ppc::fmadds(speedAtBottom, (top - scale) / range, speedAtTop * ((scale - bottom) / range));
        accessor->LaunchEx(&at, &direction, speed, m_pLevel2ProjectileDamage, owner, nullptr);  // 0x001f2988
    }
    const float base = m_afProjectileParams[2];
    const float spread = m_afProjectileParams[3] + 0.0f;  // TOC +0x411c
    const float t = RandUnit16() / kRandMax * -2.0f;  // 0x00011500; TOC +0x4178
    m_fNextShotTimer = (base + ppc::fmadds(t, m_afProjectileParams[3], spread)) / m_fDashTimeScale;
}

// 0x003dbfd0 CKShadowSurprise_UpdateAttack_maybe
void CKShadowSurprise::UpdateAttack(float dt) {
    if (m_levelIndex == 0) return;
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    if (m_pHost->IsAbilityButtonDown(3) != 0) {  // vt+0x8c
        dash->Impulse(1.0f);                       // 0x0024bce0; TOC +0x4118
        ExplodeAtHotSpot(m_pDashExplosion, this, m_pHost, m_ui8HotSpot, nullptr);
    }
    dash->Update(dt);  // 0x0024bd40
    m_fDashTimeScale = dash->m_fValue;
    m_pHost->SetHero1d20(m_fDashTimeScale);  // vt+0x84
}

// 0x003d7e40 CKShadowSurprise_PostLoad: the base's (0x3de488: ResetRuntime), then SceneNode_SetVisibleInLayer_maybe
// 0x5832a8 (node +0x1d4, visible 1, layer 0, sector 0).
int32_t CKShadowSurprise::PostLoad(int32_t type) {
    CKTransformElement::PostLoad(type);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pShadowMesh), 1, 0, 0);  // 0x005832a8
    return 1;
}

// 0x003d8ef8 CKShadowSurprise_Load
int32_t CKShadowSurprise::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_apParticlesFxData[0]);
    IKFile_ReadRef(file, &m_apParticlesFxData[1]);
    IKFile_ReadRef(file, &m_apParticlesFxData[2]);
    IKFile_ReadRef(file, &m_pDashImpulsion);
    IKFile_ReadRef(file, &m_pLevel2Projectile);
    IKFile_ReadRef(file, &m_apAnimFx[0]);
    IKFile_ReadRef(file, &m_apAnimFx[1]);
    IKFile_ReadRef(file, &m_apAnimFx[2]);
    IKFile_ReadRef(file, &m_pShadowMesh);
    for (uint32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_afHitSphereRadius[i]);
        ReadS32LE(file, &m_ai32MeshFullAlpha[i]);
        ReadS32LE(file, &m_ai32MeshStartAlpha[i]);
        ReadS32LE(file, &m_ai32MeshEndAlpha[i]);
        ReadF32LE(file, &m_afSpinXDegPerSec[i]);
        ReadF32LE(file, &m_afSpinYDegPerSec[i]);
        ReadF32LE(file, &m_afSpinZDegPerSec[i]);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_avMeshScale[i]), 3);  // one 12-byte read
    }
    ReadF32LE(file, &m_fFadeInTime);
    ReadF32LE(file, &m_fFadeOutTime);
    for (uint32_t i = 0; i < 6; ++i) ReadF32LE(file, &m_afProjectileParams[i]);
    IKFile_ReadRef(file, &m_pStartExplosion);
    IKFile_ReadRef(file, &m_apEndExplosions[0]);
    IKFile_ReadRef(file, &m_apEndExplosions[1]);
    IKFile_ReadRef(file, &m_apEndExplosions[2]);
    IKFile_ReadRef(file, &m_pSoundDico);
    ReadF32LE(file, &m_fDashSoundTopPitch);
    IKFile_ReadRef(file, &m_apEndExplosionDamages[0]);
    IKFile_ReadRef(file, &m_apEndExplosionDamages[1]);
    IKFile_ReadRef(file, &m_apEndExplosionDamages[2]);
    IKFile_ReadRef(file, &m_pDashExplosion);
    IKFile_ReadRef(file, &m_apPointLightFxData[0]);
    IKFile_ReadRef(file, &m_apPointLightFxData[1]);
    IKFile_ReadRef(file, &m_apPointLightFxData[2]);
    IKFile_ReadRef(file, &m_pLevel2ProjectileDamage);
    return 1;
}
