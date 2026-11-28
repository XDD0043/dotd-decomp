// CKEarthBoulder.cpp - reconstructed original translation unit 0x389ec8-0x3928a0 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKEarthBoulder  key 0x95cc  category Logic  size 0x2d0  vtable 0xb236c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x389ec8  CKEarthBoulder_Delete
//   [x] 0x389f18  CKEarthBoulder_GetAbilityId
//   [x] 0x389f20  CKEarthBoulder_GetFamilyId
//   [x] 0x389f28  CKEarthBoulder_IsGroundTrailActive_maybe
//   [x] 0x389f88  CKEarthBoulder_PlaySoundByIndex_maybe
//   [x] 0x38a270  CKEarthBoulder_ApplyHeroControl
//   [x] 0x38a3c8  CKEarthBoulder_End
//   [x] 0x38a600  CKEarthBoulder_ResetRuntime
//   [x] 0x38a700  CKEarthBoulder_PostLoad
//   [x] 0x38a798  CKEarthBoulder_RecursiveRegistration  (inherited: CKTransformElement_RecursiveRegistration)
//   [x] 0x38a7c0  CKEarthBoulder_Destroy  (inherited: CKTransformElement_Destroy)
//   [x] 0x38a7e8  CKEarthBoulder_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x38a830  CKEarthBoulder_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x38a860  CKEarthBoulder_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x38a890  CKEarthBoulder_Construct
//   [x] 0x38a8c8  CKEarthBoulder_Construct_2  (the same as 0x38a890 CKEarthBoulder_Construct)
//   [x] 0x38a900  CKEarthBoulder_DeleteArray
//   [ ] 0x38a9a0  RegisterCKEarthBoulderClass
//   [ ] 0x38aa28  _GLOBAL__D_38aa28
//   [ ] 0x38aa38  _GLOBAL__I_38aa38
//   [x] 0x38aa48  CKEarthBoulder_StopFx
//   [x] 0x38ab80  CKEarthBoulder_Update
//   [x] 0x38ace0  CKEarthBoulder_Create
//   [x] 0x38ad38  CKEarthBoulder_CreateArray
//   [x] 0x38ade8  CKEarthBoulder_Start
//   [x] 0x38b200  CKEarthBoulder_Load
//   [ ] 0x38cbd8  CKEarthBoulder_Save
//   [x] 0x38e4a8  CKEarthBoulder_UpdateEffect_maybe
//   [x] 0x38fac8  CKEarthBoulder_SetFxActive
//   [x] 0x390e00  CKEarthBoulder_SwitchLoopAnim_maybe
//   [x] 0x391588  CKEarthBoulder_UpdateAttack_maybe
//
//   [ ] 0x9bfaf0  CKEarthBoulder_IsKindOfClass  [inline]
//   [ ] 0x9bfb40  CKEarthBoulder_GetClassType  [inline]
//   [ ] 0x9bfb48  CKEarthBoulder_GetClassID  [inline]
//   [x] 0x9bfb50  CKEarthBoulder_StartEmitterFx  [inline]
#include "k2000/logic/CKEarthBoulder.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CKMeshPopFxData.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// |x| (the sign bit cleared through memory: clrlwi 1).
float AbsF(float x) { return std::fabs(x); }
// (float) of a word read with lwz (zero-extended, fcfid, frsp).
float WordToFloat(uint32_t word) { return static_cast<float>(static_cast<double>(word)); }
// The alpha byte of a float (fctiwz, the low byte through stfiwx / lbz).
uint8_t AlphaByte(float value) { return static_cast<uint8_t>(ppc::fctiwz(value)); }
// Within `eps` of `b` on all three axes (each bound computed in single precision; a NaN is never near).
bool Near(const CVector3& a, const CVector3& b, float eps) {
    return a.x >= b.x - eps && b.x + eps >= a.x && b.y - eps <= a.y && b.y + eps >= a.y && b.z - eps <= a.z &&
           b.z + eps >= a.z;
}
// A pooled explosion at the user's position (host vt+0x10, read once the effect is found).
void ExplodeAtOwner(IKSerializable* data, const IKSerializable* owner, CKS08AbilityHostBase* host) {
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(TransformFx::Acquire(data, owner));
    if (fx == nullptr) return;
    const CVector3 position = host->GetOwnerPosition();
    fx->SetTranslation(&position, owner);  // 0x001b66e8
    fx->Trigger(owner, 0);                 // 0x001b82a8
    fx->ReleaseReservation(owner);         // vt+0x54
}
void PlayAttached(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(TransformFx::OwnerNode(host));  // vt+0x08, +0x1c; 0x00111350
    sound->Play(0.0f);                                     // 0x00111230; TOC +0x3460
}
constexpr float kNearEpsilon = 0x1.0624dep-10f;  // TOC +0x34d8 (0x3a83126f, 0.001)
constexpr float kTwoPi = 0x1.921fb6p+2f;         // TOC +0x34e0 (0x40c90fdb)
constexpr float kMinScale = 0x1.99999ap-4f;      // TOC +0x34e4 (0x3dcccccd, 0.1)
}  // namespace

// 0x00389f88 CKEarthBoulder_PlaySoundByIndex_maybe
CKSound* CKEarthBoulder::GetSoundByIndex(uint32_t which) {
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
    switch (which) {
    case 1: return byLevel(sounds->GetSound(1), 2, 3);  // the roll
    case 2: return sounds->GetSound(0);                 // the start
    case 3: return sounds->GetSound(4);                 // the charge
    case 6: return byLevel(nullptr, 5, 6);              // the launch (level 0: none)
    case 7: return byLevel(sounds->GetSound(7), 8, 9);  // the jump
    default: return nullptr;
    }
}

// 0x00389f28 CKEarthBoulder_IsGroundTrailActive_maybe
uint8_t CKEarthBoulder::IsGroundTrailActive() {
    if (m_levelIndex == 0) return 0;
    return m_pHost->IsOnGround();  // vt+0x30
}

// 0x0038a270 CKEarthBoulder_ApplyHeroControl
void CKEarthBoulder::ApplyHeroControl(uint8_t on) {
    CKTransformElement::ApplyHeroControl(on);
    if (on != 0) {
        m_pHost->SetHeroActionPermission(0xb, 1, 1, 1);         // vt+0x44
        m_pHost->SetHeroEd4Bit0(this, 1, m_afExtraHeroMass[m_levelIndex]);  // vt+0x78
        return;
    }
    m_pHost->SetHeroActionPermission(0xb, 0, 0, 0);
    m_pHost->SetHeroEd4Bit0(this, 0, 0.0f);  // TOC +0x3460
}

// 0x0038a3c8 CKEarthBoulder_End
void CKEarthBoulder::End(int32_t forced) {
    if (GetSoundByIndex(2) != nullptr) GetSoundByIndex(2)->Stop(0);  // 0x001111b0
    if (m_pRollSound != nullptr) {
        m_pRollSound->Stop(0);
        m_pRollSound = nullptr;
    }
    if (m_pChargeSound != nullptr) {
        m_pChargeSound->Stop(0);
        m_pChargeSound = nullptr;
    }
    CKTransformElement::End(forced);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pActiveBoulderMesh), 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pLevel2ExtraNode), 1, 0, 0);
    m_pActiveBoulderMesh = nullptr;
    TransformFx::ReleaseSpark(&m_pActiveChargeSparks, this);
    TransformFx::ReleaseParticles(&m_pActiveFullChargeParticles, this);
    TransformFx::ReleaseMeshPop(&m_pActiveChargePop, this);
    TransformFx::ReleaseMeshPop(&m_pActiveRollPop, this);
    m_bJustLanded = 0;
}

// 0x0038a600 CKEarthBoulder_ResetRuntime: the base's, the element's own words, and the landing damage (+0x224) learns
// the ability id (vt+0x68 0x9c0b00 CKS08ElementDamage_SetAbilityId_maybe). Not written: +0x2ac, +0x2b4, +0x2b8 (Start /
// the charge / the launch / the landing write them before they are read).
void CKEarthBoulder::ResetRuntime() {
    CKTransformElement::ResetRuntime();
    m_fFadeOutStartTime = 0.0f;
    m_fFadeTimer = 0.0f;
    m_ui32FadeOutStartAlpha = static_cast<uint32_t>(m_i32RollAlpha);
    m_ui8HotSpot = 3;
    m_bJustLanded = 0;
    m_pActiveStartSparks = nullptr;
    m_pActiveChargeSparks = nullptr;
    m_pActiveRollPop = nullptr;
    m_pActiveChargePop = nullptr;
    m_pActiveStartParticles = nullptr;
    m_pActiveFullChargeParticles = nullptr;
    m_bFadingOut = 0;
    m_bFadedIn = 0;
    m_bCharging = 0;
    m_bLaunched = 0;
    m_pRollSound = nullptr;
    m_pChargeSound = nullptr;
    m_pActiveBoulderMesh = nullptr;
    m_bFullChargeFired = 0;
    m_pActiveAnimFx = nullptr;
    m_pActivePointLight = nullptr;
    static_cast<CKS08ElementDamage*>(m_pLandingDamage)->SetAbilityId(GetAbilityId());
    m_ui8Button = 1;
}

// 0x0038a700 CKEarthBoulder_PostLoad
int32_t CKEarthBoulder::PostLoad(int32_t type) {
    CKTransformElement::PostLoad(type);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_apBoulderMeshes[0]), 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_apBoulderMeshes[1]), 1, 0, 0);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_apBoulderMeshes[2]), 1, 0, 0);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pLevel2ExtraNode), 1, 0, 0);
    return 1;
}

// 0x0038aa48 CKEarthBoulder_StopFx
void CKEarthBoulder::StopFx() {
    CKTransformElement::StopFx();
    if (m_pActiveBoulderMesh != nullptr) {
        // The fade-out starts from the first geometry's alpha (none: the rolling alpha).
        CGeometry* first = static_cast<CGeometry*>(static_cast<CNode*>(m_pActiveBoulderMesh)->m_lGeometryList);
        m_ui32FadeOutStartAlpha = first != nullptr ? first->m_cGeometryColor[3] : static_cast<uint32_t>(m_i32RollAlpha);
    }
    m_fFadeOutStartTime = m_fFadeTimer;
    m_bFadedIn = 0;
    if (m_fFadeOutTime == 0.0f) {
        m_bFadingOut = 0;
        if (m_pActiveBoulderMesh != nullptr) TransformFx::HideNode(m_pActiveBoulderMesh);
        if (m_pLevel2ExtraNode != nullptr) TransformFx::HideNode(m_pLevel2ExtraNode);
    } else {
        m_bFadingOut = 1;
    }
    m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc; TOC +0x3494
}

// 0x0038ab80 CKEarthBoulder_Update
uint8_t CKEarthBoulder::Update(float dt) {
    m_bJustLanded = 0;
    const CVector3 velocity = m_pHost->GetOwnerVelocity();  // vt+0x4c
    const float speed = Sqrtf(ppc::fmadds(velocity.z, velocity.z, ppc::fmadds(velocity.x, velocity.x, velocity.y * velocity.y)));
    const float ratio = speed / m_groundMode1P11f8[0];
    const float squared = ratio * ratio;
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    const float knockMax = m_damageParam10[level] * 1.5f;  // TOC +0x3498
    float knock = m_damageParam10[level] * squared;
    if (!(knockMax > knock)) knock = knockMax;
    const float damage = static_cast<float>(static_cast<double>(m_damage[level]));
    float amount = squared * damage;
    const float amountMax = damage * 1.5f;
    if (!(amountMax > amount)) amount = amountMax;  // ble
    CKS08ElementDamage* element = static_cast<CKS08ElementDamage*>(m_elementDamage);
    element->m_fKnockbackForce = knock / 0.2f;  // TOC +0x349c
    element->m_fKnockbackTime = 0.2f;
    element->SetAmount(amount);  // vt+0x50
    return CKTransformElement::Update(dt);
}

// 0x0038ade8 CKEarthBoulder_Start
void CKEarthBoulder::Start(CKS08AbilityHostBase* host) {
    m_pChargeSound = nullptr;
    m_pRollSound = nullptr;
    CKTransformElement::Start(host);
    m_ui32FadeOutStartAlpha = static_cast<uint32_t>(m_i32RollAlpha);
    IKSerializable* boulder = m_apBoulderMeshes[m_levelIndex];
    m_pActiveBoulderMesh = boulder;
    if (boulder != nullptr) {
        // Shown at the start alpha (the low byte of +0x188), at the hot spot one frame of velocity ahead, raised.
        TransformFx::ShowNode(boulder);
        TransformFx::SetGeometriesAlpha(boulder, static_cast<uint8_t>(m_ui32StartAlpha & 0xffu));
        const RwV3d& owner = TransformFx::OwnerNode(m_pHost)->m_pRwFrame->modelling.pos;  // vt+0x08, +0x1c, frame +0x40
        float x = owner.x;
        float y = owner.y;
        float z = owner.z;
        const CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot));  // vt+0xcc
        z = z + spot->m_v3RelativePosition.z;
        x = x + spot->m_v3RelativePosition.x;
        y = y + spot->m_v3RelativePosition.y;
        const CVector3 velocity = m_pHost->GetOwnerVelocity();  // vt+0x4c
        const float frame = TransformFx::FrameDelta();
        CVector3 at;
        at.y = ppc::fmadds(frame, velocity.y, y) + m_afBoulderHeightOffset[m_levelIndex];
        at.z = ppc::fmadds(frame, velocity.z, z);
        at.x = ppc::fmadds(frame, velocity.x, x);
        TransformFx::SetNodePosition(boulder, at);
        if (m_levelIndex == 2 && m_pLevel2ExtraNode != nullptr) {
            TransformFx::ShowNode(m_pLevel2ExtraNode);
            TransformFx::SetGeometriesAlpha(m_pLevel2ExtraNode, static_cast<uint8_t>(m_ui32StartAlpha & 0xffu));
            TransformFx::SetNodePosition(m_pLevel2ExtraNode, at);
        }
    }
    m_bFullChargeFired = 0;
    m_fLandingHoldTimeLeft = 0.0f;
    m_fFadeTimer = 0.0f;
    m_bFadingOut = 0;
    m_bFadedIn = 0;
    m_bCharging = 0;
    m_bLaunched = 0;
    m_bJustLanded = 0;
}

// The roll sound's volume and pitch from the user's speed (host vt+0x48) over +0x108 (SetFxActive and UpdateEffect inline
// the same code).
void CKEarthBoulder::UpdateRollSound() {
    const float ratio = AbsF(m_pHost->GetHeroSpeedForAbility()) / m_groundMode1P11f8[0];
    const float volumeMin = m_fRollSoundMinVolume;
    const float full = m_fRollSoundFullVolSpeedRatio;
    const float range = 1.0f - volumeMin;
    float volume;
    float pitchT;
    float pitchRange;
    if (ratio <= 0.0f) {
        pitchRange = m_fRollSoundMaxPitch - 1.0f;
        volume = ppc::fmadds(0.0f / full, range, volumeMin);
        pitchT = 0.0f;
    } else {
        float clamped = ratio >= full ? full : ratio;
        clamped = clamped / full;
        pitchRange = m_fRollSoundMaxPitch - 1.0f;
        volume = ppc::fmadds(range, clamped, volumeMin);
        if (ratio <= 0.0f) {
            pitchT = 0.0f;
        } else {
            pitchT = ratio >= 1.0f ? 1.0f : ratio;
        }
    }
    m_pRollSound->SetVolume(volume);                                // 0x00110f10
    m_pRollSound->SetPitch(ppc::fmadds(pitchT, pitchRange, 1.0f));  // 0x00110ea0
}

// 0x0038fac8 CKEarthBoulder_SetFxActive
void CKEarthBoulder::SetFxActive(int32_t on) {
    if (on != 0) {
        CKParticlesEffectFxData* start = static_cast<CKParticlesEffectFxData*>(m_pStartParticlesData);
        start->m_pAttachHotSpot = m_pHost->GetHotspot(1);  // vt+0xcc
        start->m_pAttachOwner = nullptr;
        m_pActiveStartParticles = TransformFx::Acquire(m_pStartParticlesData, this);
        ExplodeAtOwner(m_pStartExplosion, this, m_pHost);
        IKSerializable* spot = m_pHost->GetHotspot(m_ui8HotSpot);
        CKSparkFxData* spark = static_cast<CKSparkFxData*>(m_pStartSparkFxData);
        spark->m_unk10 = spot;
        spark->m_unk0c = nullptr;
        m_pActiveStartSparks = TransformFx::Acquire(m_pStartSparkFxData, this);
        if (m_levelIndex == 1 || m_levelIndex == 2) {
            IKSerializable* collection = m_levelIndex == 1 ? m_pAnimFxLevel1 : m_pAnimFxLevel2;
            m_pActiveAnimFx = collection;
            CSGLeaf* node = TransformFx::OwnerNode(m_pHost);
            static_cast<CKAnimatedFxCollection*>(collection)->Play(node, TransformFx::AttachmentSets(m_pHost),
                                                                   static_cast<CSGHotSpot*>(spot));  // 0x005cc528
        }
        CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_apPointLightFxData[m_levelIndex]);
        light->m_pAttachNode = nullptr;
        light->m_pAttachHotSpot = spot;
        m_pActivePointLight = TransformFx::Acquire(m_apPointLightFxData[m_levelIndex], this);
        CKSound* sound = GetSoundByIndex(2);
        if (sound != nullptr) PlayAttached(sound, m_pHost);
        m_pRollSound = GetSoundByIndex(1);
        if (m_pRollSound == nullptr) return;
        UpdateRollSound();
        PlayAttached(m_pRollSound, m_pHost);
        return;
    }
    if (m_pActiveStartParticles != nullptr) {
        // The start particles ran: the stop particles and the stop explosion.
        TransformFx::ReleaseParticles(&m_pActiveStartParticles, this);
        CKParticlesEffectFxData* stop = static_cast<CKParticlesEffectFxData*>(m_pStopParticlesData);
        IKSerializable* spot = m_pHost->GetHotspot(1);
        stop->m_pAttachOwner = nullptr;
        stop->m_pAttachHotSpot = spot;
        TransformFx::Start(m_pStopParticlesData, this);
        ExplodeAtOwner(m_pStopExplosion, this, m_pHost);
    }
    TransformFx::ReleaseSpark(&m_pActiveStartSparks, this);
    if (m_pActiveAnimFx != nullptr) {
        static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Stop();  // 0x005cc990
        m_pActiveAnimFx = nullptr;
    }
    if (m_pActivePointLight != nullptr) {
        static_cast<IKFx*>(m_pActivePointLight)->StopAndRelease(this);  // vt+0x58
        m_pActivePointLight = nullptr;
    }
    if (GetSoundByIndex(2) != nullptr) GetSoundByIndex(2)->Stop(0);
    if (m_pRollSound != nullptr) {
        m_pRollSound->Stop(0);
        m_pRollSound = nullptr;
    }
    if (m_pChargeSound != nullptr) {
        m_pChargeSound->Stop(0);
        m_pChargeSound = nullptr;
    }
    TransformFx::ReleaseMeshPop(&m_pActiveRollPop, this);
}

// 0x0038e4a8 CKEarthBoulder_UpdateEffect_maybe
void CKEarthBoulder::UpdateEffect(float dt) {
    if (m_pActiveBoulderMesh == nullptr) return;
    if (m_pActiveAnimFx != nullptr) static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Update(dt);  // 0x005cccb0
    if (m_pRollSound != nullptr) UpdateRollSound();
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    if (m_bCharging != 0 && m_pChargeSound != nullptr) {
        // The charge sound's pitch rises with the charge.
        float t = m_fChargeTime / (m_afFullChargeTime[level] * m_fChargeSoundPitchTimeScale);
        if (t <= 0.0f) {
            t = 0.0f;
        } else if (t >= 1.0f) {
            t = 1.0f;
        }
        m_pChargeSound->SetPitch(ppc::fmadds(t, m_fChargeSoundMaxPitch - 1.0f, 1.0f));
    }
    // The boulder rolls: its modelling matrix, rotated by the distance rolled this frame (degrees: 360 x roll speed /
    // (2 pi x radius) x dt) about the axis across the velocity and the user's up, placed at the hot spot moved along
    // the velocity and raised along the up.
    CMatrix34 matrix;
    std::memcpy(&matrix, &static_cast<CSGMovable*>(m_pActiveBoulderMesh)->m_pRwFrame->modelling, sizeof(matrix));
    float roll;
    if (m_bCharging != 0) {
        if (m_fChargeTime >= m_afFullChargeTime[level]) {
            roll = m_afChargeRollSpeedMax[level];
        } else {
            roll = ppc::fmadds(m_fChargeTime / m_afFullChargeTime[level], m_afChargeRollSpeedMax[level] - m_afChargeRollSpeedMin[level], m_afChargeRollSpeedMin[level]);
        }
    } else {
        roll = m_pHost->GetHeroSpeedForAbility();  // vt+0x48
    }
    const float radius = m_afBoulderRadius[level];
    CVector3 direction = m_pHost->GetOwnerVelocity();  // vt+0x4c
    float distance =
        Sqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
    if (distance != 0.0f) {
        const float inverse = 1.0f / distance;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    } else {
        distance = 0.0f;
    }
    const CVector3 up = m_pHost->GetOwnerUp();  // vt+0x2c
    CVector3 axis;
    const CVector3 backward{-direction.x, -direction.y, -direction.z};
    if (Near(direction, up, kNearEpsilon) || Near(backward, up, kNearEpsilon)) {
        axis = m_pHost->GetOwnerRight();  // vt+0x28
    } else {
        axis.y = ppc::fmsubs(direction.x, up.z, direction.z * up.x);
        axis.x = ppc::fmsubs(direction.z, up.y, up.z * direction.y);
        axis.z = ppc::fmsubs(direction.y, up.x, direction.x * up.y);
        const float length = Sqrtf(ppc::fmadds(axis.z, axis.z, ppc::fmadds(axis.x, axis.x, axis.y * axis.y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            axis.z = axis.z * inverse;
            axis.x = axis.x * inverse;
            axis.y = axis.y * inverse;
        }
    }
    const float moved = distance * dt;
    const CVector3 spot = m_pHost->GetHotspotPosition(m_ui8HotSpot);  // vt+0xd0
    const float pz = ppc::fmadds(direction.z, moved, spot.z);
    const float px = ppc::fmadds(direction.x, moved, spot.x);
    const float py = ppc::fmadds(moved, direction.y, spot.y);
    const CVector3 up2 = m_pHost->GetOwnerUp();
    const float height = m_afBoulderHeightOffset[level];
    float angle = roll * 360.0f;                   // TOC +0x34dc
    const float circumference = radius * kTwoPi;
    matrix.m_pos.x = ppc::fmadds(height, up2.x, px);
    matrix.m_pos.y = ppc::fmadds(height, up2.y, py);
    angle = angle / circumference;
    matrix.m_pos.z = ppc::fmadds(height, up2.z, pz);
    angle = angle * dt;
    matrix.m_ui32Flags &= ~0x20000u;
    Mat4_RotateInPlace(&matrix, &axis, AbsF(angle));  // 0x00240498
    static_cast<CSGMovable*>(m_pActiveBoulderMesh)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    if (m_pLevel2ExtraNode != nullptr && TransformFx::IsNodeHidden(m_pLevel2ExtraNode) == 0) {
        // The level 2 extra node: the same matrix, scaled with the speed.
        static_cast<CSGMovable*>(m_pLevel2ExtraNode)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));
        const float base = m_fExtraNodeScaleMin;
        const float span = m_fExtraNodeScaleMax - m_fExtraNodeScaleMin;
        const float ratio = m_pHost->GetHeroSpeedForAbility() / m_fExtraNodeMaxScaleSpeed;
        float scale = ppc::fmadds(span, ratio, base);
        if (scale <= kMinScale) {
            scale = kMinScale;
        } else if (scale >= m_fExtraNodeScaleMax) {
            scale = m_fExtraNodeScaleMax;
        }
        static_cast<CSGMovable*>(m_pLevel2ExtraNode)->ScaleXYZ(scale, scale, scale);  // 0x000d0d28
    }
    // The fades.
    if (m_bLoop != 0) {
        if (m_fFadeTimer < m_fFadeInTime) {
            // Fading in: +0x188 -> +0x184.
            const float rest = (m_fFadeInTime - m_fFadeTimer) / m_fFadeInTime;
            const float done = m_fFadeTimer / m_fFadeInTime;
            const float alpha = ppc::fmadds(WordToFloat(static_cast<uint32_t>(m_i32RollAlpha)), done, WordToFloat(m_ui32StartAlpha) * rest);
            SetBouldersAlpha(AlphaByte(alpha));
            m_fFadeTimer = dt + m_fFadeTimer;
        } else if (m_bFadedIn == 0) {
            // Faded in: the attack's damage set up.
            SetBouldersAlpha(AlphaByte(WordToFloat(static_cast<uint32_t>(m_i32RollAlpha))));
            ApplyDamageParams(0);  // vt+0x88
            m_bFadedIn = 1;
        }
    } else if (m_bFadingOut != 0) {
        // Fading out: +0x2a0 -> +0x18c. BUG(original): the alpha runs on the whole timer, not on the time since the
        // fade-out started (+0x2a8, which only ends it).
        const float timer = dt + m_fFadeTimer;
        m_fFadeTimer = timer;
        if (timer - m_fFadeOutStartTime >= m_fFadeOutTime) {
            m_bFadingOut = 0;
            TransformFx::HideNode(m_pActiveBoulderMesh);
            if (m_pLevel2ExtraNode != nullptr) TransformFx::HideNode(m_pLevel2ExtraNode);
            return;
        }
        const float rest = (m_fFadeOutTime - timer) / m_fFadeOutTime;
        const float done = timer / m_fFadeOutTime;
        const float alpha = ppc::fmadds(WordToFloat(m_ui32EndAlpha), done, WordToFloat(m_ui32FadeOutStartAlpha) * rest);
        SetBouldersAlpha(AlphaByte(alpha));
    }
    // The ground mesh pop while in the air (the host's vt+0x30, level 1 and up) above half the top speed.
    bool pop = false;
    if (m_bFadedIn != 0 && IsGroundTrailActive() != 0) {  // vt+0x8c
        const float speed = AbsF(m_pHost->GetHeroSpeedForAbility());
        pop = m_groundMode1P11f8[0] * 0.5f < speed;  // TOC +0x34e8 (bge: a NaN does not pop)
    }
    if (pop) {
        if (m_pActiveRollPop == nullptr) {
            CKMeshPopFxData* data = static_cast<CKMeshPopFxData*>(m_pRollPopFxData);
            data->m_unk08 = nullptr;
            data->m_unk0c = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(0));
            m_pActiveRollPop = TransformFx::Acquire(m_pRollPopFxData, this);
            if (m_pActiveRollPop != nullptr) static_cast<CKMeshPopNodeFx*>(m_pActiveRollPop)->SetActive(this, 1);  // 0x001cb568
        }
    } else {
        TransformFx::ReleaseMeshPop(&m_pActiveRollPop, this);
    }
    // The attack sphere above the level's speed.
    bool sphere = false;
    if (m_bFadedIn != 0) sphere = m_afMinDamageSpeed[level] < AbsF(m_pHost->GetHeroSpeedForAbility());
    if (sphere) {
        m_pHost->SetAbilityAttackSpheres(this, 1, m_afBoulderRadius[level], m_elementDamage, 1.0f, nullptr);  // vt+0xfc
    } else {
        m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);
    }
    // A landing's held actions come back.
    if (!(m_fLandingHoldTimeLeft > 0.0f)) return;  // ble
    m_fLandingHoldTimeLeft = m_fLandingHoldTimeLeft - dt;
    if (m_fLandingHoldTimeLeft <= 0.0f) {
        m_pHost->SetHeroActionPermission(3, 0, 1, 1);  // vt+0x44
        m_pHost->SetHeroActionPermission(0, m_groundPerm1Perm0TurnEnable[1], m_mode1Perm1Perm0TurnEnable[1],
                                         m_airPerm1Perm0TurnEnable[1]);
        m_pHost->SetHeroActionPermission(1, m_groundPerm1Perm0TurnEnable[0], m_mode1Perm1Perm0TurnEnable[0],
                                         m_airPerm1Perm0TurnEnable[0]);
        m_pHost->SetAbilityTurnParams(m_groundTurnAB[0], m_groundTurnAB[1], m_mode1TurnAB[0], m_mode1TurnAB[1],
                                      m_airTurnAB[0], m_airTurnAB[1], m_groundPerm1Perm0TurnEnable[2],
                                      m_mode1Perm1Perm0TurnEnable[2], m_airPerm1Perm0TurnEnable[2]);  // vt+0x64
    }
}

// The fades' alpha on the level's boulder and, while it is shown, the extra node (the walks inlined twice).
void CKEarthBoulder::SetBouldersAlpha(uint8_t alpha) {
    TransformFx::SetGeometriesAlpha(m_pActiveBoulderMesh, alpha);
    if (m_pLevel2ExtraNode != nullptr && TransformFx::IsNodeHidden(m_pLevel2ExtraNode) == 0) TransformFx::SetGeometriesAlpha(m_pLevel2ExtraNode, alpha);
}

// 0x00391588 CKEarthBoulder_UpdateAttack_maybe
void CKEarthBoulder::UpdateAttack(float dt) {
    // The charge's ground mesh pop while in the air.
    if (IsGroundTrailActive() != 0 && m_bCharging != 0) {  // vt+0x8c
        if (m_pActiveChargePop == nullptr) {
            CKMeshPopFxData* data = static_cast<CKMeshPopFxData*>(m_pChargePopFxData);
            data->m_unk08 = nullptr;
            data->m_unk0c = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(0));  // vt+0xcc
            m_pActiveChargePop = TransformFx::Acquire(m_pChargePopFxData, this);
            if (m_pActiveChargePop != nullptr) static_cast<CKMeshPopNodeFx*>(m_pActiveChargePop)->SetActive(this, 1);  // 0x001cb568
        }
    } else {
        TransformFx::ReleaseMeshPop(&m_pActiveChargePop, this);
    }
    if (m_levelIndex == 0) return;
    if (m_fLandingHoldTimeLeft > 0.0f) return;  // ble: a landing holds the charge
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    if (m_bCharging == 0) {
        if (m_pHost->IsAbilityButtonDown(3) != 0 && m_bLaunched == 0) {  // vt+0x8c
            // The charge starts.
            m_bFullChargeFired = 0;
            m_bCharging = 1;
            m_pHost->SetHeroActionPermission(0, 1, 1, 1);  // vt+0x44
            CKSparkFxData* spark = static_cast<CKSparkFxData*>(m_pChargeSparkFxData);
            IKSerializable* spot = m_pHost->GetHotspot(m_ui8HotSpot);
            spark->m_unk0c = nullptr;
            spark->m_unk10 = spot;
            m_pActiveChargeSparks = TransformFx::Acquire(m_pChargeSparkFxData, this);
            m_pChargeSound = GetSoundByIndex(3);
            if (m_pChargeSound != nullptr) {
                m_pChargeSound->SetPitch(1.0f);  // TOC +0x3494
                PlayAttached(m_pChargeSound, m_pHost);
            }
            m_fChargeTime = 0.0f;
            return;
        }
    } else {
        float held;
        if (m_pHost->GetAbilityButtonHoldTime(3, &held) == 0) {  // vt+0x94
            // Let go: the launch along the user's forward, stronger and longer with the charge.
            float strength;
            float duration;
            if (m_fChargeTime >= m_afFullChargeTime[level]) {
                duration = m_afLaunchDurationMax[level];
                strength = m_afLaunchStrengthMax[level];
            } else {
                const float t = m_fChargeTime / m_afFullChargeTime[level];
                strength = ppc::fmadds(t, m_afLaunchStrengthMax[level] - m_afLaunchStrengthMin[level], m_afLaunchStrengthMin[level]);
                duration = ppc::fmadds(t, m_afLaunchDurationMax[level] - m_afLaunchDurationMin[level], m_afLaunchDurationMin[level]);
            }
            m_pHost->SetHeroActionPermission(0, 0, 0, 0);
            m_pHost->SetHeroActionPermission(1, 1, 1, 1);
            m_pHost->SetHeroActionPermission(2, 1, 1, 1);
            const CVector3 forward = m_pHost->GetHeroForward();               // vt+0x18
            m_pHost->SetAbilityImpulse(this, strength, duration, &forward);  // vt+0x5c
            m_fLaunchTimeLeft = duration;
            m_bCharging = 0;
            m_bLaunched = 1;
            TransformFx::ReleaseSpark(&m_pActiveChargeSparks, this);
            TransformFx::ReleaseParticles(&m_pActiveFullChargeParticles, this);
            CKSound* sound = GetSoundByIndex(6);
            if (sound != nullptr) PlayAttached(sound, m_pHost);
            if (m_pChargeSound != nullptr) {
                m_pChargeSound->Stop(0);
                m_pChargeSound = nullptr;
            }
            if (!(m_fChargeTime >= m_afFullChargeTime[level] * 0.5f)) return;  // TOC +0x34e8
            ExplodeAtOwner(m_levelIndex == 2 ? m_pLaunchExplosionLevel2 : m_pLaunchExplosion, this, m_pHost);
            return;
        }
        // Charging: at the full charge, its explosion and particles (once).
        m_fChargeTime = dt + m_fChargeTime;
        if (m_afFullChargeTime[level] <= m_fChargeTime && m_bFullChargeFired == 0) {
            m_bFullChargeFired = 1;
            ExplodeAtOwner(m_pFullChargeExplosion, this, m_pHost);
            CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(m_pFullChargeParticlesData);
            particles->m_pAttachHotSpot = m_pHost->GetHotspot(0);
            particles->m_pAttachOwner = nullptr;
            m_pActiveFullChargeParticles = TransformFx::Acquire(m_pFullChargeParticlesData, this);
        }
    }
    // The launch's time: its held actions come back at the end.
    if (m_bLaunched == 0) return;
    m_fLaunchTimeLeft = m_fLaunchTimeLeft - dt;
    if (!(m_fLaunchTimeLeft < 0.0f)) return;  // bge
    m_bLaunched = 0;
    m_pHost->SetHeroActionPermission(1, 0, 0, 0);
    m_pHost->SetHeroActionPermission(2, 0, 0, 0);
}

// 0x00390e00 CKEarthBoulder_SwitchLoopAnim_maybe
void CKEarthBoulder::SwitchLoopAnim(uint8_t vf30) {
    CKTransformElement::SwitchLoopAnim(vf30);
    if (vf30 == 0) {
        // Off the ground: the jump sound.
        CKSound* sound = GetSoundByIndex(7);
        if (sound != nullptr) PlayAttached(sound, m_pHost);
        return;
    }
    const CVector3 velocity = m_pHost->GetOwnerVelocity();  // vt+0x4c
    if (-velocity.y >= m_fLandingMinFallSpeed) {
        // A hard landing: the level's explosion with the landing damage, the landing pop, actions held.
        CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(TransformFx::Acquire(m_apLandingExplosions[m_levelIndex], this));
        if (fx != nullptr) {
            fx->SetDamageOwner(m_pHost->GetOwner(), this);         // vt+0x08; 0x001b6340
            fx->SetDamageCategory(m_pHost->GetCollisionGroup(), this);  // vt+0xb0; 0x001b6318
            fx->SetDamageFlags(m_pHost->GetCollisionMask(), this);      // vt+0xb4; 0x001b62f0
            fx->SetDamage(m_pLandingDamage, this);                              // 0x001b62c8
            const CVector3 position = m_pHost->GetOwnerPosition();      // vt+0x10
            fx->SetTranslation(&position, this);
            fx->Trigger(this, 0);
            fx->ReleaseReservation(this);
        }
        CKMeshPopFxData* data = static_cast<CKMeshPopFxData*>(m_pLandingPopFxData);
        data->m_unk0c = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(0));
        data->m_unk08 = nullptr;
        IKFx* landing = TransformFx::Acquire(m_pLandingPopFxData, this);
        if (landing != nullptr) static_cast<CKMeshPopNodeFx*>(landing)->TriggerPop(this, 1);  // 0x001caf50
        m_fLandingHoldTimeLeft = m_fLandingActionHoldTime;
        m_pHost->SetHeroActionPermission(3, 1, 1, 1);
        m_pHost->SetHeroActionPermission(0, 1, 1, 1);
        m_pHost->SetHeroActionPermission(1, 1, 1, 1);
    }
    m_bJustLanded = 1;
}

// 0x0038b200 CKEarthBoulder_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 300
// bytes of references and words (586 bytes in all).
int32_t CKEarthBoulder::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_pStartExplosion);
        IKFile_ReadRef(file, &m_apLandingExplosions[0]);
        IKFile_ReadRef(file, &m_apLandingExplosions[1]);
        IKFile_ReadRef(file, &m_apLandingExplosions[2]);
        IKFile_ReadRef(file, &m_pStopExplosion);
        IKFile_ReadRef(file, &m_pStartSparkFxData);
        IKFile_ReadRef(file, &m_pStartParticlesData);
        IKFile_ReadRef(file, &m_pStopParticlesData);
        ReadF32LE(file, &m_afBoulderRadius[0]);
        ReadF32LE(file, &m_afBoulderRadius[1]);
        ReadF32LE(file, &m_afBoulderRadius[2]);
        ReadS32LE(file, &m_i32RollAlpha);
        ReadU32LE(file, &m_ui32StartAlpha);
        ReadU32LE(file, &m_ui32EndAlpha);
        ReadF32LE(file, &m_fFadeInTime);
        ReadF32LE(file, &m_fFadeOutTime);
        ReadF32LE(file, &m_afFullChargeTime[0]);
        ReadF32LE(file, &m_afLaunchStrengthMin[0]);
        ReadF32LE(file, &m_afLaunchStrengthMax[0]);
        ReadF32LE(file, &m_afLaunchDurationMin[0]);
        ReadF32LE(file, &m_afLaunchDurationMax[0]);
        ReadF32LE(file, &m_afChargeRollSpeedMin[0]);
        ReadF32LE(file, &m_afChargeRollSpeedMax[0]);
        ReadF32LE(file, &m_afFullChargeTime[1]);
        ReadF32LE(file, &m_afLaunchStrengthMin[1]);
        ReadF32LE(file, &m_afLaunchStrengthMax[1]);
        ReadF32LE(file, &m_afLaunchDurationMin[1]);
        ReadF32LE(file, &m_afLaunchDurationMax[1]);
        ReadF32LE(file, &m_afChargeRollSpeedMin[1]);
        ReadF32LE(file, &m_afChargeRollSpeedMax[1]);
        ReadF32LE(file, &m_afFullChargeTime[2]);
        ReadF32LE(file, &m_afLaunchStrengthMin[2]);
        ReadF32LE(file, &m_afLaunchStrengthMax[2]);
        ReadF32LE(file, &m_afLaunchDurationMin[2]);
        ReadF32LE(file, &m_afLaunchDurationMax[2]);
        ReadF32LE(file, &m_afChargeRollSpeedMin[2]);
        ReadF32LE(file, &m_afChargeRollSpeedMax[2]);
        IKFile_ReadRef(file, &m_apBoulderMeshes[0]);
        IKFile_ReadRef(file, &m_apBoulderMeshes[1]);
        IKFile_ReadRef(file, &m_apBoulderMeshes[2]);
        ReadF32LE(file, &m_fLandingActionHoldTime);
        IKFile_ReadRef(file, &m_pChargeSparkFxData);
        IKFile_ReadRef(file, &m_pFullChargeExplosion);
        IKFile_ReadRef(file, &m_pAnimFxLevel1);
        IKFile_ReadRef(file, &m_pAnimFxLevel2);
        IKFile_ReadRef(file, &m_pSoundDico);
        ReadF32LE(file, &m_fChargeSoundMaxPitch);
        ReadF32LE(file, &m_fRollSoundMinVolume);
        ReadF32LE(file, &m_fRollSoundMaxPitch);
        ReadF32LE(file, &m_fRollSoundFullVolSpeedRatio);
        IKFile_ReadRef(file, &m_pLandingDamage);
        IKFile_ReadRef(file, &m_pRollPopFxData);
        IKFile_ReadRef(file, &m_pChargePopFxData);
        IKFile_ReadRef(file, &m_pLandingPopFxData);
        IKFile_ReadRef(file, &m_pLaunchExplosion);
        IKFile_ReadRef(file, &m_pLaunchExplosionLevel2);
        IKFile_ReadRef(file, &m_pFullChargeParticlesData);
        ReadF32LE(file, &m_afBoulderHeightOffset[0]);
        ReadF32LE(file, &m_afExtraHeroMass[0]);
        ReadF32LE(file, &m_afBoulderHeightOffset[1]);
        ReadF32LE(file, &m_afExtraHeroMass[1]);
        ReadF32LE(file, &m_afBoulderHeightOffset[2]);
        ReadF32LE(file, &m_afExtraHeroMass[2]);
        ReadF32LE(file, &m_fLandingMinFallSpeed);
        ReadF32LE(file, &m_afMinDamageSpeed[0]);
        ReadF32LE(file, &m_afMinDamageSpeed[1]);
        ReadF32LE(file, &m_afMinDamageSpeed[2]);
        IKFile_ReadRef(file, &m_apPointLightFxData[0]);
        IKFile_ReadRef(file, &m_apPointLightFxData[1]);
        IKFile_ReadRef(file, &m_apPointLightFxData[2]);
        ReadF32LE(file, &m_fChargeSoundPitchTimeScale);
        IKFile_ReadRef(file, &m_pLevel2ExtraNode);
        ReadF32LE(file, &m_fExtraNodeScaleMin);
        ReadF32LE(file, &m_fExtraNodeScaleMax);
        ReadF32LE(file, &m_fExtraNodeMaxScaleSpeed);
    }
    return 1;
}
