// CKShadowArms.cpp - reconstructed original translation unit 0x3d1c38-0x3d3fe8 (GAME_TOC1, main_toc1), 26 functions, 26 live.
// Primary class: CKShadowArms  key 0x928c  category Logic  size 0x264  vtable 0xb246c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3d1c38  CKShadowArms_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x3d1c88  CKShadowArms_GetAbilityId  (header)
//   [x] 0x3d1c90  CKShadowArms_IsChargeDisabled_maybe  (header)
//   [x] 0x3d1c98  CKShadowArms_ApplyDamageParams
//   [x] 0x3d2150  CKShadowArms_ResetRuntime
//   [x] 0x3d21a8  CKShadowArms_ApplyHeroControl
//   [x] 0x3d21e0  CKShadowArms_Update
//   [x] 0x3d22d8  CKShadowArms_Start
//   [x] 0x3d2370  CKShadowArms_PostLoad  (inherited: CKProjectileElement_PostLoad)
//   [x] 0x3d2398  CKShadowArms_RecursiveRegistration  (inherited: CKProjectileElement_RecursiveRegistration)
//   [x] 0x3d23c0  CKShadowArms_Destroy  (inherited: CKProjectileElement_Destroy)
//   [x] 0x3d23e8  CKShadowArms_DeletingDestructor  (the destructor; delete)
//   [x] 0x3d2430  CKShadowArms_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3d2460  CKShadowArms_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3d2490  CKShadowArms_Construct  (header)
//   [x] 0x3d24c8  CKShadowArms_Construct_2  (the same as 0x3d2490 CKShadowArms_Construct)
//   [x] 0x3d2500  CKShadowArms_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x3d25a0  RegisterCKShadowArmsClass
//   [ ] 0x3d2628  _GLOBAL__D_3d2628
//   [ ] 0x3d2638  _GLOBAL__I_3d2638
//   [x] 0x3d2648  CKShadowArms_End
//   [x] 0x3d26d8  CKShadowArms_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x3d2788  CKShadowArms_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x3d27e0  CKShadowArms_Fire
//   [x] 0x3d3098  CKShadowArms_Load
//   [ ] 0x3d3858  CKShadowArms_Save
//
//   [x] 0x9c0738  CKShadowArms_IsKindOfClass  [inline]  (header)
//   [ ] 0x9c0788  CKShadowArms_GetClassType  [inline]
//   [ ] 0x9c0790  CKShadowArms_GetClassID  [inline]
//   [x] 0x9c0798  CKShadowArms_StartEmitterFx  [inline]  (the base's (not overridden))
#include "k2000/logic/render/CKShadowArms.h"

#include <cmath>
#include <cstring>

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08HeroAbilityHost.h"
#include "crt/ppc_ops.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKAnimatedFx.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"

namespace {
// 0x00a70ac0: this unit's copy of the ability ids' damage types (the same 26 words as 0x00a70a58).
const uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};

float WordF32(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}

const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // TOC +0x3ffc -> 0x00c50d64

}  // namespace

// A Rand_Int draw (0x00011500) as the float of its low 16 bits (rldicl 48, fcfid, frsp: exact). A macro, so that the
// rand log (DOTD_REPLAY_RANDLOG) names the function that draws.
#define SA_RAND_U16() static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)

// 0x003d22d8 CKShadowArms_Start
void CKShadowArms::Start(CKS08AbilityHostBase* host) {
    CKProjectileElement::Start(host);
    if (m_pHost != nullptr) m_pHost->SetHero1d20(m_afHeroAnimSpeed[m_ui32LevelIndex]);  // vt+0x84
    m_ui8HotSpotIndex = m_ui8FirstHandHotSpot;
    m_bReleased = 0;
}

// 0x003d21e0 CKShadowArms_Update
uint8_t CKShadowArms::Update(float dt) {
    float held;
    if (m_pHost->IsAbilityButtonDown(m_ui8ButtonIndex) == 0 && m_pHost->GetAbilityButtonHoldTime(m_ui8ButtonIndex, &held) == 0) {
        m_bReleased = 1;  // vt+0x8c, vt+0x94
    }
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
    if (collection->m_bPlaying != 0) collection->Update(dt);  // TocBridge 0x0098f4b0 -> 0x005cccb0
    return CKProjectileElement::Update(dt);                    // 0x003be178
}

// 0x003d2648 CKShadowArms_End
void CKShadowArms::End(int32_t forced) {
    m_pHost->SetHero1d20(1.0f);  // vt+0x84; TOC +0x3ff0
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
    if (collection->m_bPlaying != 0) collection->Stop();  // TocBridge 0x0098f4c0 -> 0x005cc990
    CKProjectileElement::End(static_cast<uint8_t>(forced));
}

// 0x003d21a8 CKShadowArms_ApplyHeroControl
void CKShadowArms::ApplyHeroControl(uint8_t on) {
    CKProjectileElement::ApplyHeroControl(on);  // 0x003bcb48
    m_ui8HotSpotIndex = m_ui8FirstHandHotSpot;
}

// 0x003d2150 CKShadowArms_ResetRuntime
void CKShadowArms::ResetRuntime(int32_t type) {
    CKProjectileElement::ResetRuntime(type);  // 0x003bd1b0
    m_ui8SecondHandHotSpot = 8;
    m_ui8HotSpotIndex = 7;
    m_ui8ButtonIndex = 1;
    m_bReleased = 0;
    m_ui8FirstHandHotSpot = 7;
}

// 0x003d1c98 CKShadowArms_ApplyDamageParams: the level's normal values (the base's first set), in the base's order.
void CKShadowArms::ApplyDamageParams(uint8_t continuous) {
    const float damageScale = m_pHost->GetDamageScale();  // vt+0xc0
    const float effectScale = m_pHost->GetEffectScale();  // vt+0xc4
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_pElementDamage);
    damage->SetAmount(damageScale * static_cast<float>(static_cast<double>(m_ai32DamageNormal[m_ui32LevelIndex])));  // vt+0x50 (fcfid, frsp)
    damage->SetStun(m_afStunAmountNormal[m_ui32LevelIndex]);                                     // vt+0x5c
    damage->SetDisarmAmount(m_afDisarmAmountNormal[m_ui32LevelIndex]);                             // vt+0x60
    damage->SetElementValue(effectScale * WordF32(m_afElem0Normal[m_ui32LevelIndex]), 0);  // vt+0x58
    damage->SetElementValue(effectScale * m_afElem1Normal[m_ui32LevelIndex], 1);
    damage->SetElementValue(effectScale * WordF32(m_afElem2Normal[m_ui32LevelIndex]), 2);
    damage->SetElementValue(effectScale * m_afElem6Normal[m_ui32LevelIndex], 6);
    damage->SetElementValue(effectScale * WordF32(m_afElem4Normal[m_ui32LevelIndex]), 4);
    damage->SetElementValue(effectScale * WordF32(m_afElem7Normal[m_ui32LevelIndex]), 7);
    const uint32_t value3[3] = {m_unk160, m_unk164, m_unk168};
    damage->SetElementValue(effectScale * WordF32(value3[m_ui32LevelIndex]), 3);
    damage->SetUnk34(m_abDmgFlag34Normal[m_ui32LevelIndex]);  // vt+0x6c
    damage->SetUnk35(m_abDmgFlag35Normal[m_ui32LevelIndex]);  // vt+0x70
    damage->SetDamageType(kAbilityDamageTypes[GetAbilityId() & 0xffu]);  // vt+0x64
    damage->SetAbilityId(GetAbilityId());                                 // vt+0x68
    damage->SetContinuous(continuous);                                    // vt+0x54
}

// 0x003d27e0 CKShadowArms_Fire. Released (+0x260) with the press past the tap window (+0x1fc > +0x74; bgt: a NaN goes
// on): not launched (the base ends). Otherwise +0x260 cleared; the launch point (GetLaunchPosDir, no offset) jittered by
// (1 - r / 32767.5) x +0x220 on each axis (three draws, x, y, z); the hands swap: from the first hand (+0x208 was
// +0x261) the hot spot becomes +0x262 and the shot takes +0x238's accessor, else +0x261 and +0x244's; the aim (host
// vt+0x58, the result unused); the direction to the locked target's aim point (vt+0xdc from the hot spot) or the aim
// direction (vt+0x24), normalised. With a projectile type: the damage parameters (vt+0x74), the shot (LaunchEx
// 0x001f2988 with the damage object, the owner, no matrix) at the level's speed plus the hero's (vt+0x48), and above
// level index 0 the animated collection on the owner's node (its rigs vt+0x104, the hot spot the shot left). Then the
// level's muzzle explosion (the inlined reserving CKSrvFx::AcquireFx, owned by the user) at that hot spot, turned along
// the shot, triggered and released. Returns !+0x260 (read again: 1).
uint8_t CKShadowArms::Fire() {
    if (m_bReleased != 0 && m_fTimeSinceRelease > m_fTapWindow) return 0;
    m_bReleased = 0;
    IKSerializable* owner = m_pHost->GetOwner();  // vt+0x08
    CVector3 pos = GetLaunchPosDir(&kNullVector);  // 0x003bdff8
    // The jitter: three draws first, then x, y, z (each fmadds(r, -1/32767.5, 1), TOC +0x4000 / +0x3ff0).
    constexpr float kJitterStep = -0x1.0001p-15f;  // 0xb8000080
    const float rx = SA_RAND_U16();
    const float ry = SA_RAND_U16();
    const float jx = ppc::fmadds(rx, kJitterStep, 1.0f);
    const float rz = SA_RAND_U16();
    const uint8_t spot = m_ui8HotSpotIndex;
    const float jy = ppc::fmadds(ry, kJitterStep, 1.0f);
    const float jitter = m_afLaunchJitter[m_ui32LevelIndex];
    pos.x = ppc::fmadds(jx, jitter, pos.x);
    pos.y = ppc::fmadds(jy, jitter, pos.y);
    const float jz = ppc::fmadds(rz, kJitterStep, 1.0f);
    pos.z = ppc::fmadds(jz, jitter, pos.z);
    CKProjectileAccessor* accessor;
    if (m_ui8FirstHandHotSpot == spot) {
        m_ui8HotSpotIndex = m_ui8SecondHandHotSpot;
        accessor = static_cast<CKProjectileAccessor*>(m_apFirstHandProjectiles[m_ui32LevelIndex]);
    } else {
        m_ui8HotSpotIndex = m_ui8FirstHandHotSpot;
        accessor = static_cast<CKProjectileAccessor*>(m_apSecondHandProjectiles[m_ui32LevelIndex]);
    }
    m_pHost->ComputeAimDirection(0x1.921fb6p+1f, this, m_pAimCone);  // vt+0x58; pi (TOC +0x4004); the result unused
    CVector3 dir;
    if (m_pHost->GetLockedTarget() != nullptr) {  // vt+0xd4
        const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
        dir.y = target.y - pos.y;
        dir.x = target.x - pos.x;
        dir.z = target.z - pos.z;
    } else {
        dir = m_pHost->GetAimDirection(0);  // vt+0x24
    }
    const float length = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));  // 0x00010690
    if (length != 0.0f) {  // TOC +0x400c
        const float inv = 1.0f / length;
        dir.z = dir.z * inv;
        dir.x = dir.x * inv;
        dir.y = dir.y * inv;
    }
    if (accessor->m_pProjectileType != nullptr) {
        ApplyDamageParams(0);  // vt+0x74
        const float speed = m_afLaunchSpeed[m_ui32LevelIndex];
        const float heroSpeed = m_pHost->GetHeroSpeedForAbility();  // vt+0x48
        accessor->LaunchEx(&pos, &dir, speed + heroSpeed, m_pElementDamage, owner, nullptr);  // 0x001f2988
        if (m_ui32LevelIndex != 0) {
            // vt+0x104 (the hero host's GetHeroAttachmentSets 0x3ee6a0: the hero's +0x1070; the slot is hero-only).
            CSGLeaf* node = static_cast<CSGLeaf*>(static_cast<IKHook*>(owner)->m_pKGLObject);  // the owner's +0x1c
            CKHkS08Hero* hero = static_cast<CKS08HeroAbilityHost*>(m_pHost)->GetHero();
            SAnimatedFxRig* rigs = reinterpret_cast<SAnimatedFxRig*>(&hero->m_apUnk1070[0][0]);
            CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(spot));  // vt+0xcc
            static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection)->Play(node, rigs, hotSpot);  // TocBridge 0x0098f4d0
        }
    }
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x4008 -> +0x60
    CKExplosionNodeFx* fx =
        static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(reinterpret_cast<IKFxData*>(m_apMuzzleExplosions[m_ui32LevelIndex]), owner));
    if (fx != nullptr) {
        const CVector3 position = m_pHost->GetHotspotPosition(spot);  // vt+0xd0
        fx->SetTranslation(&position, owner);  // 0x001b66e8
        fx->SetDirection(&dir, owner);         // 0x001b5e20
        fx->Trigger(owner, 0);                 // 0x001b82a8 (r6 0 too)
        fx->ReleaseReservation(owner);         // vt+0x54
    }
    return static_cast<uint8_t>(m_bReleased ^ 1);
}

// 0x003d3098 CKShadowArms_Load: CKProjectileElement's data, then (level data only) the two accessors per level
// interleaved, the explosions, the collection, then the three float arrays interleaved per level.
int32_t CKShadowArms::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);  // 0x003bf360
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        IKFile_ReadRef(file, &m_apFirstHandProjectiles[i]);
        IKFile_ReadRef(file, &m_apSecondHandProjectiles[i]);
    }
    IKFile_ReadRef(file, &m_apMuzzleExplosions[0]);
    IKFile_ReadRef(file, &m_apMuzzleExplosions[1]);
    IKFile_ReadRef(file, &m_apMuzzleExplosions[2]);
    IKFile_ReadRef(file, &m_pAnimFxCollection);
    for (int32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_afHeroAnimSpeed[i]);
        ReadF32LE(file, &m_afLaunchJitter[i]);
        ReadF32LE(file, &m_afLaunchSpeed[i]);
    }
    return 1;
}
