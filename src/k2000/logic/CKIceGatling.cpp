// CKIceGatling.cpp - reconstructed original translation unit 0x3a9c50-0x3abec0 (GAME_TOC1, main_toc1), 25 functions, 25 live.
// Primary class: CKIceGatling  key 0x940c  category Logic  size 0x264  vtable 0xb23b80
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3a9c50  CKIceGatling_Delete
//   [x] 0x3a9ca0  CKIceGatling_GetAbilityId
//   [x] 0x3a9ca8  CKIceGatling_IsChargeDisabled_maybe
//   [x] 0x3a9cb0  CKIceGatling_ApplyDamageParams
//   [x] 0x3aa170  CKIceGatling_ResetRuntime
//   [x] 0x3aa1c0  CKIceGatling_Update
//   [x] 0x3aa3c0  CKIceGatling_Start
//   [x] 0x3aa498  CKIceGatling_PostLoad
//   [x] 0x3aa4c0  CKIceGatling_RecursiveRegistration  (inherited: CKProjectileElement_RecursiveRegistration)
//   [x] 0x3aa4e8  CKIceGatling_Destroy  (inherited: CKProjectileElement_Destroy)
//   [x] 0x3aa510  CKIceGatling_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3aa558  CKIceGatling_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3aa588  CKIceGatling_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3aa5b8  CKIceGatling_Construct
//   [x] 0x3aa5f0  CKIceGatling_Construct_2  (the same as 0x3aa5b8 CKIceGatling_Construct)
//   [x] 0x3aa628  CKIceGatling_DeleteArray
//   [ ] 0x3aa6c8  RegisterCKIceGatlingClass
//   [ ] 0x3aa750  _GLOBAL__D_3aa750
//   [ ] 0x3aa760  _GLOBAL__I_3aa760
//   [x] 0x3aa770  CKIceGatling_End
//   [x] 0x3aa800  CKIceGatling_CreateArray
//   [x] 0x3aa8b0  CKIceGatling_Create
//   [x] 0x3aa908  CKIceGatling_Fire
//   [x] 0x3ab230  CKIceGatling_Load
//   [ ] 0x3ab820  CKIceGatling_Save
//
//   [ ] 0x9bff38  CKIceGatling_IsKindOfClass  [inline]
//   [ ] 0x9bff88  CKIceGatling_GetClassType  [inline]
//   [ ] 0x9bff90  CKIceGatling_GetClassID  [inline]
//   [x] 0x9bff98  CKIceGatling_StartEmitterFx  [inline]
#include "k2000/logic/CKIceGatling.h"

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
// 0x00a709f0 (TOC +0x3914): this unit's copy of the ability ids' damage types (the same 26 words as 0x00a70a58).
const uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};

float WordF32(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}

}  // namespace

// A Rand_Int draw (0x00011500) as the float of its low 16 bits (rldicl 48, fcfid, frsp: exact). A macro, so that the
// rand log (DOTD_REPLAY_RANDLOG) names the function that draws.
#define IG_RAND_U16() static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)

// 0x003aa3c0 CKIceGatling_Start. The draw is made even when the base did not start (already running / no host): the
// original stores the flags and draws unconditionally after the host test.
void CKIceGatling::Start(CKS08AbilityHostBase* host) {
    CKProjectileElement::Start(host);
    if (m_pHost != nullptr) m_pHost->SetHero1d20(m_afHeroAnimSpeedScale[m_ui32LevelIndex]);  // vt+0x84
    m_bFirstShotSkipped = 0;
    m_bHoldBackFirstShot = 1;
    m_bReleasedPastTap = 0;
    // fdivs by 65535 (TOC +0x3924), then fcmpu with 0.5 (TOC +0x3928), bgt: an ordered greater-than.
    m_bNextSide = static_cast<uint8_t>(IG_RAND_U16() / 65535.0f > 0.5f ? 1 : 0);
}

// 0x003aa1c0 CKIceGatling_Update. +0x260: neither the button down (host vt+0x8c) nor held (vt+0x94) and the press
// time past the tap window (+0x1fc > +0x74; ble: a NaN keeps 0).
uint8_t CKIceGatling::Update(float dt) {
    float held;
    if (m_pHost->IsAbilityButtonDown(m_ui8ButtonIndex) != 0 || m_pHost->GetAbilityButtonHoldTime(m_ui8ButtonIndex, &held) != 0 ||
        !(m_fTimeSinceRelease > m_fTapWindow)) {
        m_bReleasedPastTap = 0;
    } else {
        m_bReleasedPastTap = 1;
    }
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
    if (collection->m_bPlaying != 0) collection->Update(dt);  // TocBridge 0x0098f4b0 -> 0x005cccb0
    if (CKProjectileElement::Update(dt) == 0) return 0;
    if (m_bFirstShotSkipped != 0) m_fTimeSinceRelease = 0.0f;  // stw 0
    if (m_pHost->IsAbilityButtonDown(m_ui8ButtonIndex) != 0) m_pHost->PlayAbilityAnim(this, 1);  // vt+0x8c, vt+0x7c
    return 1;
}

// 0x003aa770 CKIceGatling_End
void CKIceGatling::End(int32_t forced) {
    m_pHost->SetHero1d20(1.0f);  // vt+0x84; TOC +0x3954
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection);
    if (collection->m_bPlaying != 0) collection->Stop();  // TocBridge 0x0098f4c0 -> 0x005cc990
    CKProjectileElement::End(static_cast<uint8_t>(forced));
}

// 0x003aa170 CKIceGatling_ResetRuntime
void CKIceGatling::ResetRuntime(int32_t type) {
    CKProjectileElement::ResetRuntime(type);
    m_bFirstShotSkipped = 0;
    m_ui8HotSpotIndex = 2;
    m_ui8ButtonIndex = 1;
    m_bReleasedPastTap = 0;
    m_bHoldBackFirstShot = 0;
}

// 0x003a9cb0 CKIceGatling_ApplyDamageParams: the level's normal values (the base's first set), in the base's order.
void CKIceGatling::ApplyDamageParams(uint8_t continuous) {
    const float damageScale = m_pHost->GetDamageScale();  // vt+0xc0
    const float effectScale = m_pHost->GetEffectScale();  // vt+0xc4
    const uint32_t level = m_ui32LevelIndex;
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_pElementDamage);
    damage->SetAmount(damageScale * static_cast<float>(static_cast<double>(m_ai32DamageNormal[level])));  // vt+0x50 (fcfid, frsp)
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
    damage->m_unk26 = 1;
}

// 0x003aa908 CKIceGatling_Fire. The first call after Start only marks the shot skipped (+0x262) and answers launched;
// released past the tap window (+0x260): not launched (the base ends). Otherwise: the launch point (GetLaunchPosDir)
// offset sideways by -/+ the level's +0x22c (alternating), then jittered by (1 - r / 32767.5) x +0x220 on each axis
// (three draws, x, y, z); the aim (host vt+0x58, the result unused); the direction to the locked target's aim point
// (vt+0xdc from the hot spot) or the aim direction (vt+0x24), normalised. With a projectile type: the damage
// parameters (vt+0x74), the shot (CKProjectileAccessor_Launch 0x001f2988 with the damage object, the owner, no
// matrix) at the level's speed plus the hero's (vt+0x48), and above level index 0 the animated collection on the
// owner's node (its rigs vt+0x104, the hot spot 4). Then the level's muzzle explosion (the inlined CKSrvFx::AcquireFx,
// owned by the user) at the hot spot +0x208, turned along the shot, triggered and released. Returns 1.
uint8_t CKIceGatling::Fire() {
    if (m_bHoldBackFirstShot != 0) {
        m_bFirstShotSkipped = 1;
        m_bHoldBackFirstShot = 0;
        return 1;
    }
    if (m_bReleasedPastTap != 0) return 0;
    m_bFirstShotSkipped = 0;
    IKSerializable* owner = m_pHost->GetOwner();  // vt+0x08
    const uint8_t side = m_bNextSide;
    CVector3 offset;
    offset.x = side != 0 ? m_afSideOffset[m_ui32LevelIndex] : -m_afSideOffset[m_ui32LevelIndex];
    offset.y = 0.0f;  // TOC +0x396c
    offset.z = 0.0f;
    m_bNextSide = static_cast<uint8_t>(side ^ 1);
    CVector3 pos = GetLaunchPosDir(&offset);
    // The jitter: three draws first, then x, y, z (each fmadds(r, -1/32767.5, 1), TOC +0x3960 / +0x3954).
    constexpr float kJitterStep = -0x1.0001p-15f;  // 0xb8000080
    const float rx = IG_RAND_U16();
    const float jx = ppc::fmadds(rx, kJitterStep, 1.0f);
    const float ry = IG_RAND_U16();
    const float jy = ppc::fmadds(ry, kJitterStep, 1.0f);
    const float rz = IG_RAND_U16();
    const float jitter = m_afLaunchJitter[m_ui32LevelIndex];
    pos.x = ppc::fmadds(jx, jitter, pos.x);
    pos.y = ppc::fmadds(jy, jitter, pos.y);
    const float jz = ppc::fmadds(rz, kJitterStep, 1.0f);
    pos.z = ppc::fmadds(jz, jitter, pos.z);
    m_pHost->ComputeAimDirection(0x1.921fb6p+1f, this, m_pAimCone);  // vt+0x58; pi (TOC +0x3964); the result unused
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
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        dir.z = dir.z * inv;
        dir.x = dir.x * inv;
        dir.y = dir.y * inv;
    }
    if (static_cast<CKProjectileAccessor*>(m_apProjectiles[m_ui32LevelIndex])->m_pProjectileType != nullptr) {
        ApplyDamageParams(0);  // vt+0x74
        const float speed = m_afLaunchSpeed[m_ui32LevelIndex];
        CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_apProjectiles[m_ui32LevelIndex]);
        const float heroSpeed = m_pHost->GetHeroSpeedForAbility();  // vt+0x48
        accessor->LaunchEx(&pos, &dir, speed + heroSpeed, m_pElementDamage, owner, nullptr);  // 0x001f2988
        if (m_ui32LevelIndex != 0) {
            // vt+0x104 (the hero host's GetHeroAttachmentSets 0x3ee6a0: the hero's +0x1070; the slot is hero-only).
            CSGLeaf* node = static_cast<CSGLeaf*>(static_cast<IKHook*>(owner)->m_pKGLObject);  // the owner's +0x1c
            CKHkS08Hero* hero = static_cast<CKS08HeroAbilityHost*>(m_pHost)->GetHero();
            SAnimatedFxRig* rigs = reinterpret_cast<SAnimatedFxRig*>(&hero->m_apUnk1070[0][0]);
            CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(4));  // vt+0xcc
            static_cast<CKAnimatedFxCollection*>(m_pAnimFxCollection)->Play(node, rigs, spot);  // TocBridge 0x0098f4d0
        }
    }
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x3968 -> +0x60
    CKExplosionNodeFx* fx =
        static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(reinterpret_cast<IKFxData*>(m_apMuzzleExplosions[m_ui32LevelIndex]), owner));
    if (fx == nullptr) return 1;
    const CVector3 position = m_pHost->GetHotspotPosition(m_ui8HotSpotIndex);  // vt+0xd0
    fx->SetTranslation(&position, owner);  // 0x001b66e8
    fx->SetDirection(&dir, owner);         // 0x001b5e20
    fx->Trigger(owner, 0);                 // 0x001b82a8
    fx->ReleaseReservation(owner);         // vt+0x54
    return 1;
}

// 0x003ab230 CKIceGatling_Load: CKProjectileElement's data, then (level data only) 76 bytes: floats and
// seven object references (the original's reads are unrolled; the loops keep its order).
int32_t CKIceGatling::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_afHeroAnimSpeedScale[i]);
        ReadF32LE(file, &m_afLaunchJitter[i]);
    }
    IKFile_ReadRef(file, &m_apProjectiles[0]);
    IKFile_ReadRef(file, &m_apProjectiles[1]);
    IKFile_ReadRef(file, &m_apProjectiles[2]);
    IKFile_ReadRef(file, &m_pAnimFxCollection);
    ReadF32LE(file, &m_afLaunchSpeed[0]);
    ReadF32LE(file, &m_afLaunchSpeed[1]);
    ReadF32LE(file, &m_afLaunchSpeed[2]);
    IKFile_ReadRef(file, &m_apMuzzleExplosions[0]);
    IKFile_ReadRef(file, &m_apMuzzleExplosions[1]);
    IKFile_ReadRef(file, &m_apMuzzleExplosions[2]);
    ReadF32LE(file, &m_afSideOffset[0]);
    ReadF32LE(file, &m_afSideOffset[1]);
    ReadF32LE(file, &m_afSideOffset[2]);
    return 1;
}
