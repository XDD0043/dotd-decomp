// Reconstructed original translation unit: 0x2fc530-0x301408 (GAME_TOC1, main_toc1), 47 functions, 39 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: DirectionController (2), ComputeHeroDamageAfterReduction (1), ApplyTimedHeroDamage (1), UpdateHeroStatusAndTimedDamage (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2fc530  FUN_002fc530  [dead]
//   [ ] 0x2fc5a0  FUN_002fc5a0  [dead]
//   [x] 0x2fc600  CKHkS08Hero_DropGrabbedEnemy
//   [x] 0x2fc6e0  CKHkS08Hero_IsTargetEnemyOnGround_maybe  (CKHkS08Hero_14.cpp)
//   [x] 0x2fc720  CKHkS08Hero_ReleaseGrabbedEnemyWithDamage  (CKHkS08Hero_14.cpp)
//   [ ] 0x2fc808  CKHkS08Hero_ReattachGrabbedEnemy  [dead: no pointer to its descriptor 0xb998a8, no call]
//   [x] 0x2fc8e8  StaticInitAndDestruction_2fc8e8  (the two file statics at the end)
//   [ ] 0x2fc918  _GLOBAL__D_2fc918
//   [ ] 0x2fc928  _GLOBAL__I_2fc928
//   [x] 0x2fc938  CKHkS08Hero_ResetCombatState_maybe
//   [ ] 0x2fcce0  CKHkS08Hero_GetVectorToPartner_maybe  [dead: no pointer to its descriptor 0xb99918, no call]
//   [ ] 0x2fcd80  CKHkS08Hero_DetachGrabbedEnemyNode_maybe  [dead]
//   [x] 0x2fce90  CKHkS08Hero_BreakGrabAndRecoil_maybe
//   [x] 0x2fd030  CKHkS08Hero_IsAnyComboKindActive
//   [x] 0x2fd0b8  DirectionController_Update_maybe  (C2.8 port-final F07; DirectionController.h)
//   [x] 0x2fd5b0  CKHkS08Hero_IsGrabTargetInRange
//   [x] 0x2fd7c0  CKHkS08Hero_GetAimPointOnHook
//   [ ] 0x2fdb40  CKHkS08Hero_FindBestHookInAimCone_maybe  [dead]
//   [ ] 0x2fde70  FUN_002fde70  [dead]
//   [x] 0x2fdec8  CKHkS08Hero_GetAimPointOnEnemy
//   [x] 0x2fe200  CKHkS08Hero_ComputeLungeScale_maybe
//   [x] 0x2fe3a8  CKHkS08Hero_ComputeLungeOffset_maybe
//   [x] 0x2fe5b8  CKHkS08Hero_FindBestEnemyInAimCone_maybe
//   [x] 0x2fe7f0  CKHkS08Hero_AcquireTargetInAimCone
//   [x] 0x2fea88  CKHkS08Hero_TryAcquireTarget
//   [x] 0x2fead8  ComputeHeroDamageAfterReduction
//   [ ] 0x2febb8  CKHkS08Hero_AcquireAbilityTargetVariant_maybe  [dead]
//   [x] 0x2fed80  ApplyTimedHeroDamage_maybe
//   [x] 0x2fef58  UpdateHeroStatusAndTimedDamage_maybe
//   [x] 0x2fefb8  CKHkS08Hero_FindAbilityMecaTarget_maybe
//   [ ] 0x2ff670  CKHkS08Hero_TryFindAbilityMecaTarget_maybe  [dead]
//   [x] 0x2ff6c8  CKHkS08Hero_AcquireAbilityTarget_maybe
//   [ ] 0x2ff890  CKHkS08Hero_ReleaseGrabbedEnemy_maybe  [dead: no pointer to its descriptor 0xb99a30, no call]
//   [x] 0x2ff978  CKHkS08Hero_ValidateOrAcquireTarget_maybe
//   [x] 0x2ffc80  CKHkS08Hero_StartGrab
//   [x] 0x2fff48  CKHkS08Hero_TryGrabTarget
//   [x] 0x300010  CKHkS08Hero_ThrowGrabbedEnemy
//   [x] 0x300120  DirectionController_SetDirectionAndUpdate_maybe  (C2.8 port-final F07)
//   [ ] 0x300318  CKHkS08Hero_ComputeThrowToPartner_maybe  [dead: no pointer to its descriptor 0xb99a90; its only call is from the dead 0x300568]
//   [ ] 0x300568  CKHkS08Hero_ThrowGrabbedEnemyAtPartner  [dead: no pointer to its descriptor 0xb99a98, no call]
//   [x] 0x3006f0  CKHkS08Hero_ComputeFinisherCameraVector_maybe
//   [x] 0x3008d8  CKHkS08Hero_StartLungeFromMark_maybe
//   [x] 0x3011c8  CKHkS08Hero_ComputeExternalPushForce_maybe
//   [x] 0x301348  CKHkS08Hero_IsInSpecialAnim_maybe  (the local copies in CKHkS08Hero_8.cpp / _15.cpp / _17.cpp)
//   [x] 0x3013a0  CKHkS08Hero_IsAnimFinishedOrOther  (inline in its caller: Spyro2008/misc/CKS08HeroAbilityHost.cpp)
//   [x] 0x3013c8  CKHkS08Hero_IsAnimFinished
//   [ ] 0x3013f0  FUN_003013f0  [dead]
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/DirectionController.h"
#include "k2000/math/Math.h"
#include "crt/xatan.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/logic/animation/CKAnimatedCamera.h"
#include "k2000/logic/animation/CKAnimatedCameraData.h"
#include "k2000/core/Stub.h"

#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/misc/Engine.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08DragonCityGolem.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/cameras/CKAimCamembert.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/hooks/CKHkCrumblyZoneMultiState.h"
#include "Spyro2008/hooks/CKHkS08ElectricGauge.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/CKGrpMeca.h"
#include "Spyro2008/logic/CKS08HeroCombo.h"
#include "Spyro2008/logic/CKS08HeroBlow.h"
#include <cmath>

#include <cstring>
#include "platform/fps.h"

// 0x002fc938 CKHkS08Hero_ResetCombatState_maybe: `flag` 0 only resets the re-attack cooldown and the credits;
// otherwise the whole combat state goes back to the defaults.
void CKHkS08Hero::ResetCombatState(int32_t flag) {
    if (flag != 0) {
        m_unk1a84 = 0;
        if (m_ui8Hero == 0 || m_ui8Hero == 1) {
            // the four melee spheres: the bounding volumes 4..7
            m_unk1b8c = m_apBoundings[4];
            m_unk1b90 = m_apBoundings[5];
            m_unk1b94 = m_apBoundings[6];
            m_unk1b98 = m_apBoundings[7];
        }
        SetCollisionVolumeEnabled(static_cast<IKBoundingVolume*>(m_apBoundings[0]), 1);  // 0x00352f10
        m_unk1ab6 = 1;
        m_unk1a14 = 0;
        m_unk1bb0 = 0;
        m_unk1abc = 0;
        m_unk1abd = 0;
        m_unk1abe = 0;
        m_unk1ac0 = 0;
        m_unk1ac4 = 0;
        m_unk1ac7 = 0;
        m_unk1ac8 = 0;
        m_unk1ac9 = 0;
        m_unk1aca = 0;
        m_unk1acb = 0;
        m_unk1acc = 0;
        m_unk1ab4 = 0;
        m_unk1acd = 0;
        m_unk1ace = 0;
        m_unk1ad0 = 0;
        m_unk1ac1 = 0;
        m_unk1ac2 = 0;
        m_unk1ac3 = 0;
        m_unk1abf = 0;
        m_unk1acf = 0;
        m_unk1ac5 = 0;
        m_unk1ac6 = 0;
        m_unk1ab5 = 0;
        m_unk1ad1 = 0;
        m_pTargetedEnemy = 0;
        m_pFlightAimEnemy = 0;
        // the zero vector 0x00c50d64 (TOC1 +0x1ff4)
        m_unk1d2c = 0.0f;
        m_unk1d30 = 0.0f;
        m_unk1d34 = 0.0f;
        m_unk1b0c = 0.0f;
        m_unk1b14 = 0.0f;
        m_unk1b10 = 0.0f;
        m_unk1bb4 = 0;
        m_unk1bb8 = 0;
        m_unk1bbc = 0;
        m_unk1bc0 = 0;
        m_unk1bc4 = 0;
        m_unk1bc8 = 0;
        m_unk1bcc = 0;
        m_unk1b30 = 0;
        m_unk1b34 = 0;
        m_unk1b40 = 0;
        m_unk1b18 = m_unk8a4;
        m_unk1b38 = 60.0f;  // TOC1 +0x2004
        m_unk1b3c = 1.0f;   // TOC1 +0x2008
        m_unk1b44 = 0.0f;
        m_unk1b4c = 0.0f;
        m_unk1b48 = 0.0f;
        m_unk1ad4 = 0xffffffffu;
        m_unk1ad2 = 0;
        m_unk1ad3 = 0;
        m_unk1ad8 = 0xffffffffu;
        m_unk1adc = 0xffffffffu;
        m_fAbilityFuryTimer = 0;
        m_unk1cc4 = 0;
        m_unk1cc8 = 0;
        m_unk1ab2 = 0;
        m_fAbilityAnimSpeedScale = 1.0f;
        m_pActiveAbility = 0;
        m_unk1d40 = 0;
        m_unk1d3c = 1.0f;
        m_unk1d48 = 0.0f;
        m_unk1d50 = 0.0f;
        m_unk1d4c = 0.0f;
        m_unk1d58 = 0;
        m_unk1d54 = 0;
        m_unk1d44 = 0;
        m_unk1d60 = 0;
        m_unk1d5c = 1.0f;
        m_unk1d68 = 0.0f;
        m_unk1d70 = 0.0f;
        m_unk1d6c = 0.0f;
        m_unk1d78 = 0;
        m_unk1d74 = 0;
        m_unk1d64 = 0;
        m_unk1d80 = 0;
        m_unk1d7c = 1.0f;
        m_unk1d88 = 0.0f;
        m_unk1d90 = 0.0f;
        m_unk1d8c = 0.0f;
        m_unk1d98 = 0;
        m_unk1d94 = 0;
        m_unk1d84 = 0;
        m_unk1da0 = 0;
        m_unk1d9c = 1.0f;
        m_unk1da8 = 0.0f;
        m_unk1db0 = 0.0f;
        m_unk1dac = 0.0f;
        m_unk1db8 = 0;
        m_unk1db4 = 0;
        m_unk1da4 = 0;
        m_unk1ab8 = 0;
        m_unk1cfc = 0;
        m_unk1af8 = 0;
        m_unk1d04 = 4.0f;  // TOC1 +0x200c
        m_unk1d1c = 1.0f;
        m_unk1d08 = 1.0f;
        m_ui32ActiveHitSphereCount = 0;
        m_unkeec = -1.0f;  // TOC1 +0x1ffc
        m_unk1d10 = 0;
        m_unk1d14 = 1.0f;
        m_unk1d11 = 0;
        m_unk1dd0 = 0;
        m_unk1dd1 = 0;
        m_unk1d18 = 0;
        m_unk1ae8 = 0;
        m_unk1b88 = 0;
        m_unk1b08 = 0;
        m_unk1b78 = 0;
        m_unk1b7c = 0;
        m_unk1b80 = 0;
        m_unk1b84 = 0;
        m_unk1b68 = nullptr;
        CSGLeaf* glow = static_cast<CSGLeaf*>(m_unk1dc4);
        glow->m_sgProperties = (glow->m_sgProperties & 0xfffffffbu) | 4u;
        m_unk1cf4 = nullptr;
        m_unk1dc0 = 0;
        m_unk1dcc = nullptr;
        m_unk1df4 = nullptr;
    }
    m_unk1aec = -1.0f;  // TOC1 +0x1ffc (0xbf800000)
    m_afAbilityCooldown[9] = 0.0f;
    for (int i = 0; i < 9; ++i) m_afAbilityCooldown[i] = 0.0f;
    ResetComboAndAttackCredits();  // 0x0033f9d0
}

// 0x002fef58 UpdateHeroStatusAndTimedDamage_maybe: the equipped armour and the regeneration, the timed damage with the
// frame dt (+0x88c), the grabbed enemy's mark damage, the flight block +0x1d9c and the approach of +0x1108.
void CKHkS08Hero::UpdateHeroStatusAndTimedDamage() {
    ApplyEquippedArmor();                   // 0x0030c700
    ApplyTimedHeroDamage(m_unk88c);         // 0x002fed80
    ApplyGrabbedEnemyMarkDamage();          // 0x0032edd0
    InitFlightField1D9CBlock();             // 0x0032f048
    ApproachField1108AndNotifyCamera();     // 0x0032e028
}

// 0x002fed80 ApplyTimedHeroDamage_maybe: the fall damage. Only the controlled hero (+0x24 = +0x25) counts, while the
// game manager's +0x64 bit 8 is clear and +0xecc bit 27 is not set. +0xecc bit 29 is cleared every frame. In the air
// (bit 28) more than +0xdd8 above the ground the time +0x1b08 grows by dt; past +0xdc8 bits 29 and 30 are set (bit 29
// only when 30 was not). Otherwise bit 30 and the time are cleared. While bit 30 is set the dragon loses, each frame,
// dt times the time past +0xdc8 remapped from [0, +0xdd4] to [+0xdcc, +0xdd0] (0 at or before +0xdc8).
void CKHkS08Hero::ApplyTimedHeroDamage(float dt) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x2010 -> +0x8c
    uint8_t counts = 0;
    if ((m_unkecc & 0x08000000u) == 0) counts = static_cast<uint8_t>(((manager->m_flags64 >> 8) & 1u) ^ 1u);
    if (m_ui8Hero != m_ui8TrackedLeader) counts = 0;
    uint32_t flags = m_unkecc & ~0x20000000u;
    m_unkecc = flags;
    bool above = false;
    if ((m_unkecc & 0x10000000u) != 0) {
        const float height = GetHeightAboveGround();  // 0x0032a008
        if (m_unkdd8 > height && counts != 0) {
            above = true;
            m_unk1b08 = dt + m_unk1b08;
            if (m_unkdc8 < m_unk1b08) {  // bge: an unordered compare keeps the bits
                flags = m_unkecc;
                if ((flags & 0x40000000u) == 0) {
                    flags |= 0x20000000u;
                    m_unkecc = flags;
                }
                m_unkecc = flags | 0x40000000u;
            }
        } else {
            flags = m_unkecc;
        }
    }
    if (!above) {
        m_unkecc = flags & ~0x40000000u;
        m_unk1b08 = 0.0f;
    }
    if ((m_unkecc & 0x40000000u) == 0) return;
    const float past = m_unk1b08 - m_unkdc8;
    float rate = 0.0f;  // TOC +0x1fe0
    if (past > 0.0f) rate = Math_RemapClamped(0.0f, m_unkdd4, past, m_unkdcc, m_unkdd0);  // 0x00333618
    int64_t damage = static_cast<int64_t>(rate * dt);  // fctidz
    // --fps N (not in the original): the whole damage of this frame's 60 Hz frames (trunc(rate x dt) per update
    // drops the fraction, so a higher frame rate would deal less fall damage, or none).
    if (dotd::fps::Unlocked()) damage = dotd::fps::TruncSteps(rate, dt);
    manager->DamageDragon(m_ui8Hero, static_cast<uint32_t>(damage));  // 0x004fda08
}

// 0x002fd030 CKHkS08Hero_IsAnyComboKindActive: any of the combo kind bytes +0x1abc / +0x1abd / +0x1ac3 / +0x1ac0 /
// +0x1ac1 / +0x1ac2 / +0x1ac5 / +0x1ac6 / +0x1ac4, else the recovery request +0x1acb.
uint8_t CKHkS08Hero::IsAnyComboKindActive() const {
    if (m_unk1abc != 0 || m_unk1abd != 0 || m_unk1ac3 != 0 || m_unk1ac0 != 0 || m_unk1ac1 != 0 || m_unk1ac2 != 0 ||
        m_unk1ac5 != 0 || m_unk1ac6 != 0 || m_unk1ac4 != 0) {
        return 1;
    }
    return m_unk1acb;
}

namespace {
// The timed records' times (+0x18 / +0x1c) are floats the header still types as words (ResetCombatState stores 0).
template <class T>
float LoadF32(const T& word) {
    static_assert(sizeof(T) == 4, "a 32-bit member");
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}
template <class T>
void StoreF32(T& word, float value) {
    static_assert(sizeof(T) == 4, "a 32-bit member");
    std::memcpy(&word, &value, 4);
}

// The timed impulse step the lunge and push functions inline for each of their 0x20-byte records (+0x00 the scale,
// +0x08 the active byte, +0x0c the vector, +0x18 the time left, +0x1c the last step; the caller has checked the byte):
// a record whose time ran out (below 0) is cleared, else it takes the step; an active record with a non-zero last step
// gives scale * vector (scaled by (last + left) / last on its final, overshooting step), added to the zero vector
// 0x00c50d64 with fmadds.
template <class TLeft, class TLast>
CVector3 StepTimedImpulse(float dt, float scale, uint8_t& active, float& vx, float& vy, float& vz, TLeft& leftWord,
                          TLast& lastWord) {
    const CVector3& zero = kHeroZeroVector;
    uint8_t on = active;
    const float left = LoadF32(leftWord);
    if (left < 0.0f) {  // TOC1 +0x1fe0
        vx = zero.x;
        vz = zero.z;
        vy = zero.y;
        StoreF32(lastWord, 0.0f);
        StoreF32(leftWord, 0.0f);
        active = 0;
        on = 0;
    } else {
        StoreF32(lastWord, dt);
        StoreF32(leftWord, left - dt);
    }
    CVector3 out = zero;
    if (on == 0) return out;
    const float last = LoadF32(lastWord);
    if (last == 0.0f) return out;
    const float remaining = LoadF32(leftWord);
    float factor = scale;
    if (!(remaining >= 0.0f)) factor = ((last + remaining) / last) * scale;
    out.x = ppc::fmadds(factor, vx, zero.x);
    out.y = ppc::fmadds(factor, vy, zero.y);
    out.z = ppc::fmadds(factor, vz, zero.z);
    return out;
}
}  // namespace

namespace {
// 0x00c50da0 (TOC +0x2020): the "no point" vector, FLT_MAX in each part (StaticInitAndDestruction_11578).
constexpr CVector3 kNoAimPoint{3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f};
}  // namespace

// 0x002fe3a8 CKHkS08Hero_ComputeLungeOffset_maybe: the lunge direction +0x11cc toward the grabbed / targeted enemy
// (+0x124: its aim point from the hero's hot spot 5) or the hook (+0x12c: its aim point from the position), else (no
// target, no hook, neither +0x1ac5 nor +0x1ac6) +0x1b0c..+0x1b14 cleared.
void CKHkS08Hero::ComputeLungeOffset() {
    if (m_pTargetedEnemy != nullptr) {
        CVector3 from;
        static_cast<CSGHotSpot*>(m_apHotSpots[5])->GetWorldPosition(&from);  // 0x000ce790
        const CVector3 aim = GetAimPointOnEnemy(m_pTargetedEnemy, &from, 0, 0);       // 0x002fdec8
        if (aim.x == kNoAimPoint.x && aim.y == kNoAimPoint.y && aim.z == kNoAimPoint.z) {  // TOC +0x2020
            m_unk11cc = m_unk12a0;
            m_unk11d4 = m_unk12a8;
            m_unk11d0 = m_unk12a4;
        } else {
            m_unk11cc = aim.x - from.x;
            m_unk11d4 = aim.z - from.z;
            m_unk11d0 = aim.y - from.y;
        }
        return;
    }
    if (m_pTargetedMecaHook != nullptr) {
        // The position is read before the call; the hook's aim point (no height clamp) less it, or +0x12a0 when the
        // hook gives the "no point".
        const float px = m_unk54c;
        const float pz = m_unk554;
        const float py = m_unk550;
        const CVector3 aim = GetAimPointOnHook(m_pTargetedMecaHook, 0);  // 0x002fd7c0
        if (aim.x == kNoAimPoint.x && aim.y == kNoAimPoint.y && aim.z == kNoAimPoint.z) {  // TOC +0x2020
            m_unk11cc = m_unk12a0;
            m_unk11d4 = m_unk12a8;
            m_unk11d0 = m_unk12a4;
        } else {
            m_unk11cc = aim.x - px;
            m_unk11d4 = aim.z - pz;
            m_unk11d0 = aim.y - py;
        }
        return;
    }
    if (m_unk1ac5 != 0 || m_unk1ac6 != 0) return;
    const CVector3& zero = kHeroZeroVector;  // TOC1 +0x1ff4
    m_unk1b0c = zero.x;
    m_unk1b14 = zero.z;
    m_unk1b10 = zero.y;
}

// 0x003008d8 CKHkS08Hero_StartLungeFromMark_maybe: the displacement of the attack moves this step. A combo move starts
// a lunge (record +0x1d5c) at its blow's mark (C2.7); a running lunge locks the direction (airborne bit) and replaces the
// result, else the record +0x1d9c does (outside the grab / dash moves); the record +0x1d7c is added.
CVector3 CKHkS08Hero::StartLungeFromMark(float dt) {
    CVector3 out = kHeroZeroVector;  // TOC1 +0x1ff4
    if (m_unk1abc != 0 || m_unk1abd != 0 || m_unk1ac3 != 0 || m_unk1ac0 != 0 || m_unk1ac1 != 0 || m_unk1ac2 != 0) {
        if (m_i16CurAnimIndex == 0xb9) return out;
        CKS08HeroBlow* blow = static_cast<CKS08HeroCombo*>(m_pCurrentComboNode)->GetBlow();  // vt+0x54
        if (m_unk1ac7 == 0 && (m_unkedc & 0x80u) != 0 && blow != nullptr) StartLunge(blow);
    }
    if (m_unk1d64 != 0) {
        SetDirectionLock(1);  // 0x00354cf0 and the +0x354 bits
        if (m_unk1acc == 0) ComputeLungeOffset();  // 0x002fe3a8
        out = kHeroZeroVector;
        if (m_unk1d64 != 0) {
            out = StepTimedImpulse(dt, m_unk1d5c, m_unk1d64, m_unk1d68, m_unk1d6c, m_unk1d70, m_unk1d74, m_unk1d78);
        }
        if (m_unk1d64 == 0) m_unk1ac7 = 0;
    } else if (m_unk1ac8 == 0 && m_unk1ac1 == 0 && m_unk1ac0 == 0) {
        if (m_unk1da4 != 0) {
            out = StepTimedImpulse(dt, m_unk1d9c, m_unk1da4, m_unk1da8, m_unk1dac, m_unk1db0, m_unk1db4, m_unk1db8);
        }
    } else if (m_unk1acc == 0) {
        ComputeLungeOffset();  // 0x002fe3a8
    }
    if (m_unk1d84 != 0) {
        const CVector3 add =
            StepTimedImpulse(dt, m_unk1d7c, m_unk1d84, m_unk1d88, m_unk1d8c, m_unk1d90, m_unk1d94, m_unk1d98);
        out.z = out.z + add.z;
        out.x = out.x + add.x;
        out.y = out.y + add.y;
    }
    return out;
}

// DOTD: StartLungeFromMark's lunge start (0x00300b00): the mark flag (+0xedc bit 7) cleared, +0x1ac7 set; the record
// +0x1d5c gets the blow's scale (vt+0x74) and duration (vt+0x70, also +0x1aa8), a zero vector, its byte and times
// cleared. Without +0x1ac9 the target is validated (ValidateOrAcquireTarget; the grab checks with +0x1ac8). The direction:
// to the target's aim point from the position (+0x54c; normalised), or (no target point, or +0x1ac9) to the hook's
// (flattened on the ground, normalised), else +0x12a0. Turned by the lunge pitch (ComputeLungeScale in degrees, 0 with
// +0x1acc) plus the blow's vt+0x78 into the record's vector; the record armed for its duration and the finisher camera
// tried.
void CKHkS08Hero::StartLunge(CKS08HeroBlow* blow) {
    const uint8_t running = m_unk1ac7;
    m_unkedc &= ~0x80u;
    m_unk1ac7 = 1;
    const float duration = blow->Vf70();  // vt+0x70
    m_unk1aa8 = duration;
    const float scale = blow->Vf74();     // vt+0x74
    const CVector3& zero = kHeroZeroVector;  // TOC1 +0x1ff4
    StoreF32(m_unk1d60, duration);
    m_unk1d5c = scale;
    m_unk1d68 = zero.x;
    m_unk1d6c = zero.y;
    m_unk1d70 = zero.z;
    m_unk1d64 = running;
    m_unk1d78 = 0;
    m_unk1d74 = 0;
    if (m_unk1ac9 == 0) {
        ValidateOrAcquireTarget();  // 0x002ff978
        if (m_pTargetedEnemy != nullptr && m_unk1ac8 != 0) {
            // A grab lunge: an enemy that can be grabbed and held there has its volume group 1 off.
            CKHkS08Enemy* target = static_cast<CKHkS08Enemy*>(m_pTargetedEnemy);
            if (target->CanBeGrabbed(0) != 0 && target->CanBeHeldAtPosition() != 0) {  // 0x002898b0, 0x00289b38
                target->DisableVolumeGroup(1);  // vt+0xfc
            }
        }
    }
    const CVector3* position = reinterpret_cast<const CVector3*>(&m_unk54c);
    CVector3 direction{m_unk12a0, m_unk12a4, m_unk12a8};
    const CVector3 aim = GetAimPointOnEnemy(m_pTargetedEnemy, position, 1, 1);  // 0x002fdec8
    const bool none = aim.x == kNoAimPoint.x && aim.y == kNoAimPoint.y && aim.z == kNoAimPoint.z;  // TOC +0x2020
    float length = 0.0f;
    bool normalise = false;
    if (!none && m_unk1ac9 == 0) {
        direction.y = aim.y - position->y;
        direction.x = aim.x - position->x;
        direction.z = aim.z - position->z;
        length = std::sqrt(ppc::fmadds(direction.z, direction.z,
                                       ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));  // 0x00010690
        normalise = length != 0.0f;
    } else {
        const CVector3 hook = GetAimPointOnHook(m_pTargetedMecaHook, 1);  // 0x002fd7c0
        if (hook.x == kNoAimPoint.x && hook.y == kNoAimPoint.y && hook.z == kNoAimPoint.z) {
            direction = CVector3{m_unk12a0, m_unk12a4, m_unk12a8};
        } else {
            direction.z = hook.z - position->z;
            direction.x = hook.x - position->x;
            direction.y = hook.y - position->y;
            if (static_cast<int8_t>(GetMovementMode()) == 0) direction.y = 0.0f;  // 0x003401b8
            length = std::sqrt(ppc::fmadds(direction.z, direction.z,
                                           ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
            normalise = length != 0.0f;
        }
    }
    if (normalise) {
        const float inverse = 1.0f / length;  // TOC +0x2008
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    }
    const float pitch = blow->Vf78();  // vt+0x78
    float lunge = 0.0f;  // TOC +0x1fe0
    if (m_unk1acc == 0) lunge = ComputeLungeScale() * 57.2957802f;  // 0x002fe200, TOC +0x2078
    const CVector3 turned = ComputeFinisherCameraVector(0.0f, 0.0f, lunge + pitch, &direction, 0);  // 0x003006f0
    m_unk1d68 = turned.x;
    m_unk1d6c = turned.y;
    m_unk1d70 = turned.z;
    m_unk1d64 = 1;
    StoreF32(m_unk1d74, LoadF32(m_unk1d60));
    StoreF32(m_unk1d78, 0.0f);
    TryStartFinisherCamera();  // 0x0032d6b0
}

// 0x002fd7c0 CKHkS08Hero_GetAimPointOnHook: Malefor's hot spot 6 (vt+0xf8), the golem's nearest aim volume from the
// hero's hot spot 5, the electric gauge's hot spot (vt+0x104); any other hook is asked with message 0x400 (seeded with
// its node's LTM position): an answer other than 0 means that position, else the hot spot it names or the point it
// left. With `clampHeight` a point (not the "no point") is lowered as GetAimPointOnEnemy's.
CVector3 CKHkS08Hero::GetAimPointOnHook(IKSerializable* hook, uint8_t clampHeight) {
    CVector3 out = kNoAimPoint;  // TOC +0x2020
    if (hook != nullptr) {
        if (hook->IsKindOfClass(0x3502) != 0) {
            // STUB(C2.9: Malefor): its hot spot 6 (vt+0xf8) world position.
            DOTD_STUB_ONCE("CKHkS08Hero_GetAimPointOnHook 0x2fd7c0: Malefor (C2.9)");
        } else if (hook->IsKindOfClass(0x31c2) != 0) {
            CVector3 from;
            static_cast<CSGHotSpot*>(m_apHotSpots[5])->GetWorldPosition(&from);  // +0x4c -> +0x14, 0x000ce790
            static_cast<CKHkS08DragonCityGolem*>(hook)->GetNearestAimVolume(&out, &from);  // 0x004d6020
        } else if (hook->IsKindOfClass(0x2e42) != 0) {
            // The gauge's hot spot (vt+0x104 0x492660, the reference +0x30) world position (0x000ce790; no null test).
            static_cast<CSGHotSpot*>(static_cast<CKHkS08ElectricGauge*>(hook)->GetGrabHotSpot())->GetWorldPosition(&out);
        } else {
            const RwFrame* frame = static_cast<CSGMovable*>(static_cast<IKHook*>(hook)->m_pKGLObject)->m_pRwFrame;
            SAimPointQuery query;
            query.m_point = CVector3{frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
            query.m_ui8Index = 0;
            query.m_pHotSpot = nullptr;
            query.m_pHero = this;
            if (hook->MessageProc(0x400, &query) != 0) {  // vt+0x1c
                const RwFrame* again = static_cast<CSGMovable*>(static_cast<IKHook*>(hook)->m_pKGLObject)->m_pRwFrame;
                out = CVector3{again->ltm.pos.x, again->ltm.pos.y, again->ltm.pos.z};
            } else if (query.m_pHotSpot != nullptr) {
                static_cast<CSGHotSpot*>(query.m_pHotSpot)->GetWorldPosition(&out);  // 0x000ce790
            } else {
                out = query.m_point;
            }
        }
    }
    if (clampHeight != 0 && !(out.x == kNoAimPoint.x && out.y == kNoAimPoint.y && out.z == kNoAimPoint.z)) {
        const float dx = out.x - m_unk54c;
        const float dz = out.z - m_unk554;
        const float dy = out.y - m_unk550;
        const float horizontal = std::sqrt(ppc::fmadds(dx, dx, dz * dz));
        const float limit = horizontal * FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->at.y;  // +0x74
        if (dy > limit) out.y = out.y - (dy - limit);
    }
    return out;
}

namespace {
// FindAbilityMecaTarget's mask bits and the class each selects (the first set bit whose class matches admits the actor).
constexpr uint32_t kMecaTargetClasses[8] = {
    0x2ec2,  // bit 0: CKHkS08CrumblyZone
    0x3582,  // bit 1: CKHkS08CrumblyZoneMultiState
    0x2e42,  // bit 2: CKHkS08ElectricGauge
    0x2f02,  // bit 3: CKHkS08FogHorn
    0x2e82,  // bit 4: CKHkS08FlamingTorch
    0x2d42,  // bit 5: CKHkS08TuningFork
    0x3502,  // bit 6: CKHkS08Malefor
    0x31c2,  // bit 7: CKHkS08DragonCityGolem
};
}  // namespace

// 0x002ff6c8 CKHkS08Hero_AcquireAbilityTarget_maybe: an enemy in the aim cone (AcquireTargetInAimCone, into +0x124) and
// a meca actor of the classes `mask` selects (FindAbilityMecaTarget, into +0x12c) along a copy of `direction` each;
// with both, the one of the larger weighted score is kept (the meca's when meca weight x its score is above enemy weight
// x the enemy's) and the other dropped. 1 with a target.
uint8_t CKHkS08Hero::AcquireAbilityTarget(float enemyWeight, float mecaWeight, IKSerializable* aim, const CVector3* direction,
                                          uint32_t mask) {
    CVector3 coneDirection = *direction;
    float enemyScore = 0.0f;
    if (AcquireTargetInAimCone(aim, &coneDirection, &enemyScore) == 0) {  // 0x002fe7f0
        CVector3 mecaDirection = *direction;
        float mecaScore = 0.0f;
        return FindAbilityMecaTarget(aim, &mecaDirection, &mecaScore, mask);  // 0x002fefb8
    }
    CVector3 mecaDirection = *direction;
    float mecaScore = 0.0f;
    if (FindAbilityMecaTarget(aim, &mecaDirection, &mecaScore, mask) != 0) {
        if (mecaWeight * mecaScore > enemyWeight * enemyScore) {
            m_pTargetedEnemy = nullptr;
            return 1;
        }
        m_pTargetedMecaHook = nullptr;
    }
    return 1;
}

// 0x002fefb8 CKHkS08Hero_FindAbilityMecaTarget_maybe: over the game manager's meca group (+0xc) active actors (+0x2c,
// count +0x30): +0x12c and +0xec8 bit 7 cleared, the cone set at hot spot 4 along `direction` (vt+0x5c). An actor the
// mask admits: an electric gauge base must accept the hero (vt+0xf0); a multi-state zone needs pieces in its state
// (vt+0x108); multi-state and plain zones must answer message 0x402 (or say they can be hit); then its aim point
// (GetAimPointOnHook) scored (vt+0x50): the highest score wins into +0x12c and *score (1). Without a winner +0x1b0c is
// cleared (0); without the group 0 at once.
uint8_t CKHkS08Hero::FindAbilityMecaTarget(IKSerializable* aimObject, const CVector3* direction, float* score,
                                           uint32_t mask) {
    CKGrpMeca* group = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);  // TOC +0x2010 -> +0x8c -> +0xc
    if (group == nullptr) return 0;
    m_pTargetedMecaHook = nullptr;
    m_unkec8 &= ~0x80u;
    const uint32_t count = group->m_unk30;
    IKHook** actors = group->m_pUnk2c;
    CVector3 origin;
    static_cast<CSGHotSpot*>(m_apHotSpots[4])->GetWorldPosition(&origin);  // 0x000ce790
    CKAimCamembert* aim = static_cast<CKAimCamembert*>(aimObject);
    const CVector3 at = origin;
    const CVector3 along = *direction;
    aim->SetOriginAndDirection(&at, &along);  // vt+0x5c
    float best = 0.0f;
    bool found = false;
    for (uint32_t i = 0; i < count; ++i) {
        IKHook* actor = actors[i];
        if (mask != 0) {
            bool admitted = false;
            for (uint32_t bit = 0; bit < 8 && !admitted; ++bit) {
                if ((mask & (1u << bit)) != 0 && actor->IsKindOfClass(kMecaTargetClasses[bit]) != 0) admitted = true;
            }
            if (!admitted) continue;
        }
        uint8_t hittable = 0;
        // vt+0xf0 with the hero: the only 0x3542 class is CKHkS08ElectricGauge (0x492650, always 1; the base's slot is pure).
        if (actor->IsKindOfClass(0x3542) != 0 &&
            static_cast<CKHkS08ElectricGauge*>(actor)->AcceptsAbilityTarget(this) == 0) {
            continue;
        }
        if (actor->IsKindOfClass(0x34c2) != 0) {
            if (static_cast<CKHkCrumblyZoneMultiState*>(actor)->CurrentStateHasPieces() == 0) continue;  // vt+0x108
            if (actor->MessageProc(0x402, &hittable) == 0 && hittable == 0) continue;
        }
        if (actor->IsKindOfClass(0x1982) != 0) {
            if (actor->MessageProc(0x402, &hittable) == 0 && hittable == 0) continue;
        }
        const CVector3 point = GetAimPointOnHook(actor, 0);  // 0x002fd7c0
        float value;
        if (aim->ScoreTarget(&point, &value) == 0) continue;  // vt+0x50
        if (!found) {
            found = true;
            best = value;
            m_pTargetedMecaHook = actor;
        } else if (!(value <= best)) {
            best = value;
            m_pTargetedMecaHook = actor;
        }
    }
    if (m_pTargetedMecaHook != nullptr) {
        *score = best;
        return 1;
    }
    const CVector3& zero = kHeroZeroVector;  // TOC +0x1ff4
    m_unk1b0c = zero.x;
    m_unk1b14 = zero.z;
    m_unk1b10 = zero.y;
    return 0;
}

// 0x002ff978 CKHkS08Hero_ValidateOrAcquireTarget_maybe: unless the aim (+0x135c) turned away from +0x37c by more than
// +0xd80 while +0x1378 is above 0.5 (and not in a grab combo, +0x1ac8: then the search runs along +0x37c, +0xec8 bit 7
// cleared), a target (+0x124) or hook (+0x12c) is kept (1). Else both are dropped and searched along +0x12a0 (or
// +0x37c) with the aim cone (+0x1a7c flying or in a grab kind, else +0x1a78): an enemy (AcquireTargetInAimCone) and an
// actor of the crumbly zone / Malefor classes (FindAbilityMecaTarget, mask 0x43); with both the actor wins only when it
// scores more than twice the enemy. A target sets +0xec8 bit 7 (1); none clears +0x1b0c (0).
uint8_t CKHkS08Hero::ValidateOrAcquireTarget() {
    CVector3 aimDirection{m_unk135c, m_unk1360, m_unk1364};
    CVector3 facing{m_unk37c, m_unk380, m_unk384};
    const float angle = Vec3_AngleBetween(&aimDirection, &facing);  // 0x002fbbf8
    CVector3 along{m_unk12a0, m_unk12a4, m_unk12a8};
    bool keep = true;
    if (!(m_unkd80 >= angle) && m_unk1378 > 0.5f && m_unk1ac8 == 0) {  // TOC +0x2034
        along = CVector3{m_unk37c, m_unk380, m_unk384};
        keep = false;
        m_unkec8 &= ~0x80u;
    }
    if (keep && (m_pTargetedEnemy != nullptr || m_pTargetedMecaHook != nullptr)) return 1;
    m_pTargetedMecaHook = nullptr;
    m_pTargetedEnemy = nullptr;
    IKSerializable* aim =
        (static_cast<int8_t>(GetMovementMode()) == 1 || m_unk1ac3 != 0) ? m_unk1a7c : m_unk1a78;  // 0x003401b8
    float enemyScore = 0.0f;
    CVector3 first = along;
    if (AcquireTargetInAimCone(aim, &first, &enemyScore) != 0) {  // 0x002fe7f0
        float mecaScore = 0.0f;
        CVector3 second = along;
        if (FindAbilityMecaTarget(aim, &second, &mecaScore, 0x43) != 0) {  // 0x002fefb8
            if (enemyScore + enemyScore >= mecaScore) {
                m_pTargetedMecaHook = nullptr;
            } else {
                m_pTargetedEnemy = nullptr;
            }
        }
    } else {
        float mecaScore = 0.0f;
        CVector3 second = along;
        if (FindAbilityMecaTarget(aim, &second, &mecaScore, 0x43) == 0) {
            const CVector3& zero = kHeroZeroVector;  // TOC +0x1ff4
            m_unk1b0c = zero.x;
            m_unk1b14 = zero.z;
            m_unk1b10 = zero.y;
            return 0;
        }
    }
    m_unkec8 = (m_unkec8 & ~0x80u) | 0x80u;
    return 1;
}

// 0x002fe200 CKHkS08Hero_ComputeLungeScale_maybe: 0 without a target (+0x124) unless flying or in a grab kind; else the
// angle between the direction to the target's aim point from hot spot 5 (or +0x12a0) and its flattened copy, negative
// when the point is below the hot spot.
float CKHkS08Hero::ComputeLungeScale() {
    if (m_pTargetedEnemy == nullptr) return 0.0f;
    if (static_cast<int8_t>(GetMovementMode()) != 1 && m_unk1ac3 == 0) return 0.0f;  // 0x003401b8
    CVector3 from;
    static_cast<CSGHotSpot*>(m_apHotSpots[5])->GetWorldPosition(&from);  // 0x000ce790
    const CVector3 aim = GetAimPointOnEnemy(m_pTargetedEnemy, &from, 0, 0);    // 0x002fdec8
    CVector3 toward{m_unk12a0, m_unk12a4, m_unk12a8};
    if (!(aim.x == kNoAimPoint.x && aim.y == kNoAimPoint.y && aim.z == kNoAimPoint.z)) {
        toward.x = aim.x - from.x;
        toward.z = aim.z - from.z;
        toward.y = aim.y - from.y;
    }
    CVector3 flat{toward.x, 0.0f, toward.z};
    const float angle = Vec3_AngleBetween(&toward, &flat);  // 0x002fbbf8
    const float sign = aim.y - from.y < 0.0f ? -1.0f : 1.0f;  // TOC +0x1ffc / +0x2008
    return sign * angle;
}

// 0x003006f0 CKHkS08Hero_ComputeFinisherCameraVector_maybe: `direction` (flattened with `flat`, normalised) as the at
// of a basis (up Y, else X); turned about its local x by 360 - `xDegrees`, then y and z; the at row. Without a basis the
// negated +0x12a0.
CVector3 CKHkS08Hero::ComputeFinisherCameraVector(float zDegrees, float yDegrees, float xDegrees,
                                                  const CVector3* direction, uint8_t flat) {
    CVector3 at = *direction;
    if (flat != 0) at.y = 0.0f;
    const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC +0x2008
        at.z = at.z * inverse;
        at.x = at.x * inverse;
        at.y = at.y * inverse;
    }
    CVector3 out{-m_unk12a0, -m_unk12a4, -m_unk12a8};
    alignas(16) CMatrix34 basis{};
    const CVector3 axisY{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x204c)
    const CVector3 axisX{1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC +0x2054)
    if ((Mat4_SetBasisFromAtUp(&basis, &at, &axisY) & 0xff) == 0 &&
        (Mat4_SetBasisFromAtUp(&basis, &at, &axisX) & 0xff) == 0) {  // 0x0023fd30
        return out;
    }
    Mat4_RotateLocalXDeg(360.0f - xDegrees, &basis);  // 0x00241118, TOC +0x2050
    Mat4_RotateLocalYDeg(yDegrees, &basis);           // 0x002413d0
    Mat4_RotateLocalZDeg(zDegrees, &basis);           // 0x002419c0
    out = basis.m_at;
    return out;
}

// 0x003011c8 CKHkS08Hero_ComputeExternalPushForce_maybe: the timed push of the record +0x1d3c (scale +0x1d3c, vector
// +0x1d48, time left +0x1d54); while it is active the hero's direction is locked (the airborne bit, as a jump).
CVector3 CKHkS08Hero::ComputeExternalPushForce(float dt) {
    CVector3 out = kHeroZeroVector;  // TOC1 +0x1ff4
    if (m_unk1d44 == 0) return out;
    out = StepTimedImpulse(dt, m_unk1d3c, m_unk1d44, m_unk1d48, m_unk1d4c, m_unk1d50, m_unk1d54, m_unk1d58);
    SetDirectionLock(1);  // 0x00354cf0 and the +0x354 bits
    return out;
}

// 0x002fdec8 CKHkS08Hero_GetAimPointOnEnemy: for a valid target, with +0x1ac5 / +0x1ac6 its hot spot 1; flying its sector
// hot spot; else the nearer of the sector hot spot and hot spot 1 from `from` (when hot spot 1 is nearer and not
// `hotSpotOnly`, the enemy's position +0x134 when that is nearer still). With `clampHeight` a point (not the "no
// point") more than the horizontal distance x the hero frame's LTM at.y above `from` comes down to that height.
CVector3 CKHkS08Hero::GetAimPointOnEnemy(IKSerializable* target, const CVector3* from, uint8_t hotSpotOnly,
                                         uint8_t clampHeight) {
    CVector3 out = kNoAimPoint;
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(target);
    if (enemy != nullptr && enemy->IsValidCombatTarget() != 0) {  // 0x00289278
        CVector3 sector;
        enemy->GetSectorHotSpotPosition(&sector);  // 0x0028a268
        if (m_unk1ac5 != 0 || m_unk1ac6 != 0) {
            enemy->GetHotSpot(1)->GetWorldPosition(&out);  // 0x002892e8, 0x000ce790
        } else if (static_cast<int8_t>(GetMovementMode()) == 1) {
            out = sector;
        } else {
            CVector3 spot;
            enemy->GetHotSpot(1)->GetWorldPosition(&spot);
            const float sx = sector.x - from->x, sy = sector.y - from->y, sz = sector.z - from->z;
            const float toSector = std::sqrt(ppc::fmadds(sz, sz, ppc::fmadds(sx, sx, sy * sy)));  // Math_Sqrtf
            const float hx = spot.x - from->x, hy = spot.y - from->y, hz = spot.z - from->z;
            const float toSpot = std::sqrt(ppc::fmadds(hz, hz, ppc::fmadds(hx, hx, hy * hy)));
            if (toSector <= toSpot) {
                out = sector;
            } else if (hotSpotOnly != 0) {
                out = spot;
            } else {
                const CVector3 position = enemy->m_v3Position;  // +0x134
                const float px = position.x - from->x, py = position.y - from->y, pz = position.z - from->z;
                const float toPosition = std::sqrt(ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py)));
                out = toSpot <= toPosition ? spot : position;
            }
        }
    }
    if (clampHeight != 0 && !(out.x == kNoAimPoint.x && out.y == kNoAimPoint.y && out.z == kNoAimPoint.z)) {
        const float dz = out.z - from->z;
        const float dx = out.x - from->x;
        const float dy = out.y - from->y;
        const float horizontal = std::sqrt(ppc::fmadds(dx, dx, dz * dz));
        const float limit = horizontal * FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->at.y;  // +0x1c, +4, +0x74
        if (dy > limit) out.y = out.y - (dy - limit);
    }
    return out;
}

// 0x002fe5b8 CKHkS08Hero_FindBestEnemyInAimCone_maybe: the cone (vt+0x5c) set at hot spot 4 along `direction`, then the
// enemy group's active enemies that are valid targets scored at their aim points (vt+0x50): the highest score wins.
IKSerializable* CKHkS08Hero::FindBestEnemyInAimCone(IKSerializable* aimObject, const CVector3* direction) {
    IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // TOC +0x2010 -> +0x8c -> +4
    if (group == nullptr) return nullptr;
    const uint32_t count = group->m_ui32NbActiveEnemies;  // +0x120
    CVector3 origin;
    static_cast<CSGHotSpot*>(m_apHotSpots[4])->GetWorldPosition(&origin);  // 0x000ce790
    CKAimCamembert* aim = static_cast<CKAimCamembert*>(aimObject);
    const CVector3 at = origin;
    const CVector3 along = *direction;
    aim->SetOriginAndDirection(&at, &along);  // vt+0x5c
    IKSerializable* best = nullptr;
    float bestScore = 0.0f;
    bool found = false;
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* enemy = group->m_apActiveEnemies[i];  // +0x58
        if (static_cast<CKHkS08Enemy*>(enemy)->IsValidCombatTarget() == 0) continue;  // 0x00289278
        const CVector3 point = GetAimPointOnEnemy(enemy, &origin, 0, 0);  // 0x002fdec8
        float score;
        if (aim->ScoreTarget(&point, &score) == 0) continue;  // vt+0x50
        if (!found) {
            found = true;
            bestScore = score;
            best = enemy;
        } else if (score > bestScore) {
            bestScore = score;
            best = enemy;
        }
    }
    return best;
}

// 0x002fe7f0 CKHkS08Hero_AcquireTargetInAimCone: FindBestEnemyInAimCone's search into +0x124 (cleared first, as +0xec8
// bit 7); the best score into *score and 1, else +0x1b0c..+0x1b14 the null vector and 0.
uint8_t CKHkS08Hero::AcquireTargetInAimCone(IKSerializable* aimObject, const CVector3* direction, float* score) {
    IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // TOC +0x2010 -> +0x8c -> +4
    if (group == nullptr) return 0;
    m_pTargetedEnemy = nullptr;
    m_unkec8 &= ~0x80u;
    const uint32_t count = group->m_ui32NbActiveEnemies;
    CVector3 origin;
    static_cast<CSGHotSpot*>(m_apHotSpots[4])->GetWorldPosition(&origin);
    CKAimCamembert* aim = static_cast<CKAimCamembert*>(aimObject);
    const CVector3 at = origin;
    const CVector3 along = *direction;
    aim->SetOriginAndDirection(&at, &along);  // vt+0x5c
    float bestScore = 0.0f;
    bool found = false;
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* enemy = group->m_apActiveEnemies[i];
        if (static_cast<CKHkS08Enemy*>(enemy)->IsValidCombatTarget() == 0) continue;
        const CVector3 point = GetAimPointOnEnemy(enemy, &origin, 0, 0);
        float candidate;
        if (aim->ScoreTarget(&point, &candidate) == 0) continue;
        if (!found) {
            found = true;
            bestScore = candidate;
            m_pTargetedEnemy = enemy;
        } else if (candidate > bestScore) {
            bestScore = candidate;
            m_pTargetedEnemy = enemy;
        }
    }
    if (m_pTargetedEnemy != nullptr) {
        *score = bestScore;
        return 1;
    }
    const CVector3& zero = kHeroZeroVector;  // TOC +0x1ff4
    m_unk1b0c = zero.x;
    m_unk1b14 = zero.z;
    m_unk1b10 = zero.y;
    return 0;
}

// 0x002fea88 CKHkS08Hero_TryAcquireTarget: AcquireTargetInAimCone with a copy of `direction`, the score dropped.
uint8_t CKHkS08Hero::TryAcquireTarget(IKSerializable* aim, const CVector3* direction) {
    const CVector3 along = *direction;
    float score = 0.0f;
    return AcquireTargetInAimCone(aim, &along, &score);  // 0x002fe7f0
}

// 0x003013c8 CKHkS08Hero_IsAnimFinished: the playing animation (+0x160) is `anim` and its end flag (+0x354 bit 15) is set.
uint8_t CKHkS08Hero::IsAnimFinished(int32_t anim) const {
    if (static_cast<int16_t>(m_i16CurAnimIndex) != anim) return 0;
    return static_cast<uint8_t>((m_ui32HeroFlags354 >> 15) & 1u);
}

// 0x002fead8 ComputeHeroDamageAfterReduction: the damage less the hero's reduction. The reduction share: none without
// +0xec8 bit 2; with +0xed0 bit 14 +0xe94 (a hit of kind 0 or 2, +0x1ae8) or +0xe98; else +0xdb8 for kinds 0 / 2 and
// none for the others. A single hit (`once`) is reduced by at least the whole amount +0xdbc. Never below 0.
float CKHkS08Hero::ComputeHeroDamageAfterReduction(float damage, uint8_t once) {
    float share = 0.0f;  // TOC +0x1fe0
    if ((m_unkec8 & 4u) != 0) {
        const bool plain = m_unk1ae8 == 0 || m_unk1ae8 == 2;
        if ((m_ui32StatusFlagsED0 & 0x4000u) != 0) {
            share = plain ? m_unke94 : m_unke98;
        } else if (plain) {
            share = m_unkdb8;
        }
    }
    float reduction = share * damage;
    if (once != 0 && !(reduction <= 0.0f)) {
        const float least = static_cast<float>(static_cast<double>(static_cast<uint32_t>(m_unkdbc)));  // fcfid
        if (!(reduction > least)) reduction = least;
    }
    const float result = damage - reduction;
    return result > 0.0f ? result : 0.0f;  // bgtlr
}

namespace {
// The enemy let go by a hero: not held, its grabber cleared, released with the fall flag (a grab of kind 5, +0x1ac3, never
// falls; else it falls unless +0x1abf).
void LetGoOfEnemy(CKHkS08Hero* hero, CKHkS08Enemy* enemy) {
    enemy->SetHeldFlag(0);       // 0x00289f08
    enemy->ClearGrabber(hero);   // 0x00288c98
    const uint8_t falls = hero->m_unk1ac3 != 0 ? 0 : (hero->m_unk1abf == 0 ? 1 : 0);
    enemy->EnterReleasedState(falls);  // 0x0028ab48
}
}  // namespace

// 0x002fc600 CKHkS08Hero_DropGrabbedEnemy: a held grab target (+0x1acc, +0x124) let go, no target, +0x1b0c cleared.
void CKHkS08Hero::DropGrabbedEnemy() {
    if (m_unk1acc == 0 || m_pTargetedEnemy == nullptr) return;
    LetGoOfEnemy(this, static_cast<CKHkS08Enemy*>(m_pTargetedEnemy));
    const CVector3& zero = kHeroZeroVector;  // TOC +0x1ff4 -> 0x00c50d64
    m_pTargetedEnemy = nullptr;
    m_unk1b0c = zero.x;
    m_unk1b14 = zero.z;
    m_unk1b10 = zero.y;
    m_unk1acc = 0;
}

// 0x002fce90 CKHkS08Hero_BreakGrabAndRecoil_maybe: the grab target let go (held or not); the hero knocked back along the
// back of its facing (+0x1d7c 40, +0x1d80 0.1 over the knock data), facing +0x12a0, the hit origin the enemy's position,
// +0x1ac4 set, no target.
void CKHkS08Hero::BreakGrabAndRecoil() {
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pTargetedEnemy);
    if (enemy == nullptr) return;
    LetGoOfEnemy(this, enemy);
    const CVector3& zero = kHeroZeroVector;
    SetF32(m_unk1d80, 0.1f);  // TOC +0x2014
    m_unk1d7c = 40.0f;        // TOC +0x2018
    m_unk1d88 = zero.x;
    m_unk1d8c = zero.y;
    m_unk1d90 = zero.z;
    m_unk1d84 = 0;
    m_unk1d94 = 0;
    m_unk1d98 = 0;
    m_unk1d88 = -m_unk12a0;
    m_unk1d8c = -m_unk12a4;
    m_unk1d90 = -m_unk12a8;
    m_unk1d98 = 0;
    m_unk1d94 = m_unk1d80;
    m_unk1d84 = 1;
    m_unk11cc = m_unk12a0;
    m_unk11d0 = m_unk12a4;
    m_unk11d4 = m_unk12a8;
    m_unkf8 = enemy->m_v3Position.x;
    m_unkfc = enemy->m_v3Position.y;
    m_unk100 = enemy->m_v3Position.z;
    m_unk1ac4 = 1;
    m_pTargetedEnemy = nullptr;
    m_unk1b0c = zero.x;
    m_unk1b14 = zero.z;
    m_unk1b10 = zero.y;
    m_unk1acc = 0;
}

// 0x002fd5b0 CKHkS08Hero_IsGrabTargetInRange: with a target and a blow, the target within the grab range (+0xd88, a
// kind 5 grab +0xd90) of hot spot 18 on x / z and within the grab half angle (+0xd8c / +0xd94) of the facing (+0x12a0).
uint8_t CKHkS08Hero::IsGrabTargetInRange() {
    if (m_pTargetedEnemy == nullptr) return 0;
    if (static_cast<CKS08HeroCombo*>(m_pCurrentComboNode)->GetBlow() == nullptr) return 0;  // vt+0x54
    const float angle = m_unk1ac3 != 0 ? m_unkd94 : m_unkd8c;
    const float range = m_unk1ac3 != 0 ? m_unkd90 : m_unkd88;
    const RwV3d& hero = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->ltm.pos;
    const RwV3d& target = static_cast<CSGMovable*>(static_cast<IKHook*>(m_pTargetedEnemy)->m_pKGLObject)->m_pRwFrame->ltm.pos;
    const float hx = hero.x, hz = hero.z, tx = target.x, tz = target.z;
    CVector3 hand;
    static_cast<CSGHotSpot*>(m_apHotSpots[18])->GetWorldPosition(&hand);  // 0x000ce790
    const float dz = hand.z - tz;
    const float dx = hand.x - tx;
    const float reach = std::sqrt(ppc::fmadds(dx, dx, dz * dz));  // Math_Sqrtf
    const float along = ppc::fmadds(tz - hz, m_unk12a8, ppc::fmadds(tx - hx, m_unk12a0, 0.0f));
    const float bz = hz - tz;
    const float bx = hx - tx;
    float cosine = along / std::sqrt(ppc::fmadds(bx, bx, bz * bz));
    if (cosine <= -1.0f) {
        cosine = -1.0f;  // TOC +0x1ffc
    } else if (cosine >= 1.0f) {
        cosine = 1.0f;   // TOC +0x2008
    }
    const float turn = crt::Acosf(cosine);  // 0x00780c90
    return range >= reach && angle >= turn ? 1 : 0;
}

// 0x002ffc80 CKHkS08Hero_StartGrab: a target not held yet taken from the partner (its combo ended, +0x1aec 0.3, its
// wind beam cancelled) and grabbed: held, hung under the blow's hot spot, +0x1ac9, +0xec4 bit 12, +0xecc bit 4; the
// grab camera started (+0x1b28 with the data +0x1ae0) unless +0xecc bit 5 (started: +0xecc bit 5, +0xed0 bit 6); the
// grab timer +0x1b30 from +0xdc4, +0x1ab4 set, +0x1ab0 -1, holding (+0x1acc).
void CKHkS08Hero::StartGrab() {
    if (m_unk1acc != 0 || m_pTargetedEnemy == nullptr) return;
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pTargetedEnemy);
    if (enemy->GetGrabbingHero() == GetPartnerHero()) {  // 0x00288fd0, 0x002f85f8
        CKHkS08Hero* partner = GetPartnerHero();
        partner->SetComboActive(0, 0xff);  // 0x0032d9b0
        GetPartnerHero()->m_unk1aec = 0.3f;  // TOC +0x2038
        if (GetPartnerHero()->IsUsingWindBeam() != 0) {  // 0x0032a7a8
            GetPartnerHero()->CancelAbilityB(0);  // 0x003272d8
        }
    }
    enemy->SetGrabbedBy(this);  // 0x00288c58
    if (enemy->GetGrabbingHero() != this) return;
    enemy->SetHeldFlag(1);
    CSGLeaf* node = static_cast<CSGLeaf*>(static_cast<CKHkS08Enemy*>(m_pTargetedEnemy)->m_pKGLObject);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    const uint8_t hotspot = static_cast<uint8_t>(static_cast<CKS08HeroCombo*>(m_pCurrentComboNode)->GetBlow()->GetHotspotIndex());
    static_cast<CSGHotSpot*>(m_apHotSpots[hotspot])->AttachVolume(node);  // 0x000ce2b8
    m_unk1ac9 = 1;
    m_unkec4 = (m_unkec4 & ~0x1000u) | 0x1000u;
    m_unkecc = (m_unkecc & ~0x10u) | 0x10u;
    if ((m_unkecc & 0x20u) == 0 &&
        static_cast<CKAnimatedCamera*>(m_unk1b28)->Start(0.0f, static_cast<CKAnimatedCameraData*>(m_unk1ae0),
                                                         static_cast<CSGBranch*>(m_pKGLObject)) != 0) {  // vt+0x50
        m_unkecc = (m_unkecc & ~0x20u) | 0x20u;
        m_ui32StatusFlagsED0 = (m_ui32StatusFlagsED0 & ~0x40u) | 0x40u;
    }
    m_unk1b30 = m_unkdc4;
    m_unk1ab4 = 1;
    m_unk1ab0 = -1;
    m_unk1acc = 1;
}

// 0x002fff48 CKHkS08Hero_TryGrabTarget: without a target one is looked for (and must be in range); a target that can be
// grabbed (by the grab's kind) and held where it is gets grabbed.
void CKHkS08Hero::TryGrabTarget() {
    if (m_pTargetedEnemy == nullptr) {
        ValidateOrAcquireTarget();  // 0x002ff978
        if (IsGrabTargetInRange() == 0) return;
    }
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pTargetedEnemy);
    if (enemy->CanBeGrabbed(m_unk1ac3) == 0) return;  // 0x002898b0
    if (enemy->CanBeHeldAtPosition() == 0) return;    // 0x00289b38
    StartGrab();
}

// 0x00300010 CKHkS08Hero_ThrowGrabbedEnemy: the target let go of and hit by the blow's throw damage (vt+0xb0) along the
// facing (+0x12a0); no target, not holding, +0x1b0c cleared.
void CKHkS08Hero::ThrowGrabbedEnemy(IKSerializable* blow) {
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pTargetedEnemy);
    if (enemy == nullptr) return;
    enemy->SetHeldFlag(0);
    enemy->ClearGrabber(this);
    const CVector3 along{m_unk12a0, m_unk12a4, m_unk12a8};
    enemy->ApplyThrowImpactDamage(static_cast<CKS08HeroBlow*>(blow)->GetDamage(), &along);  // vt+0xb0, 0x0028ac90
    const CVector3& zero = kHeroZeroVector;
    m_pTargetedEnemy = nullptr;
    m_unk1acc = 0;
    m_unk1b0c = zero.x;
    m_unk1b14 = zero.z;
    m_unk1b10 = zero.y;
}

// 0x002fc8e8 StaticInitAndDestruction_2fc8e8: two file statics (0x00ceadfc, 0x00ceae00) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceadfc = -1.0f;
[[maybe_unused]] float s_unkceae00 = -1.0f;
}  // namespace

// ---- C2.8 port-final F07: the hero element beam's segment chain (DirectionController.h) ----
namespace {
constexpr CVector3 kDirectionNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x1ff4)
float DirectionSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }  // 0x00010690
}  // namespace

// 0x002fd0b8 DirectionController_Update_maybe. The labels follow the original's blocks; the float tests are its own
// (bne / beq on fcmpu: NaN unequal; cror eq|lt / eq|gt: ordered).
void DirectionController_Update(float dt, float speed, float followSpeed, DirectionController* node,
                                const CVector3* direction, uint8_t flag) {
    DirectionController* parent = node->m_pParent;
    if (parent == nullptr) node->m_bTurning = flag;
    if (node->m_pNext != nullptr) {
        const CVector3 copy = *direction;
        DirectionController_Update(dt, speed, followSpeed, node->m_pNext, &copy, flag);
        parent = node->m_pParent;
    }
    if (parent == nullptr) return;
    CVector3* target = &node->m_v3Target;
    const uint8_t turning = node->m_bTurning;
    float tx = 0.0f;
    float ty = 0.0f;
    float tz = 0.0f;
    float ax;
    float ay;
    float az;
    float step = speed;
    float angle;
    float cosine;
    float timer;
    if (turning != 0) goto L3e0;
L174:
    if (parent->m_bTurning != 0) goto L528;
L184:
    tx = target->x;
    if (kDirectionNull.x != tx) {
        ty = target->y;
        tz = target->z;
        goto L1b8;
    }
    ty = target->y;
    if (ty != kDirectionNull.y) {
        tz = target->z;
        goto L1b8;
    }
    tz = target->z;
    if (tz == kDirectionNull.z) goto L4d8;
L1b8:
    if (parent->m_pParent == nullptr) goto L4f8;
L1d0: {
    const CVector3& p = parent->m_v3Vector;
    const CVector3& n = node->m_v3Vector;
    az = ppc::fmsubs(p.y, n.x, n.y * p.x);
    ax = ppc::fmsubs(n.y, p.z, n.z * p.y);
    ay = ppc::fmsubs(n.z, p.x, p.z * n.x);
    goto L200;
}
L4d8:
    tz = direction->z;
    tx = direction->x;
    ty = direction->y;
    if (parent->m_pParent != nullptr) goto L1d0;
L4f8: {
    const CVector3& n = node->m_v3Vector;
    az = ppc::fmsubs(ty, n.x, tx * n.y);
    ax = ppc::fmsubs(tz, n.y, ty * n.z);
    ay = ppc::fmsubs(tx, n.z, tz * n.x);
}
L200:
    if (!(DirectionSqrtf(ppc::fmadds(az, az, ppc::fmadds(ax, ax, ay * ay))) > 0.25f)) {  // bgt; TOC +0x201c
        if (node->m_bTurning == 0) return;
    }
    timer = node->m_fTimer;
    if (!(timer <= 0.0f)) {
        if (node->m_bTurning == 0) goto L388;
    }
    {
        DirectionController* p = node->m_pParent;
        node->m_fSpeed = speed;
        step = dt * speed;
        if (p->m_pParent == nullptr) {
            // L554: against the target direction, over the segment's length.
            const CVector3& n = node->m_v3Vector;
            cosine = ppc::fmadds(tz, n.z, ppc::fmadds(tx, n.x, ty * n.y)) / node->m_fLength;
        } else {
            const CVector3& n = node->m_v3Vector;
            cosine = ppc::fmadds(n.z, p->m_v3Vector.z, ppc::fmadds(n.x, p->m_v3Vector.x, n.y * p->m_v3Vector.y)) /
                     (node->m_fLength * p->m_fLength);
        }
        if (cosine <= -1.0f) {
            cosine = -1.0f;
        } else if (cosine >= 1.0f) {
            cosine = 1.0f;
        }
        angle = crt::Acosf(cosine);  // 0x0098e1a0
        if (!(angle <= step)) {
            node->m_bTurning = 1;
        } else {
            step = angle;
        }
        CVector3 out;
        CVector3 v = node->m_v3Vector;
        CVector3 axis = {ax, ay, az};
        Vec3_RotateTowardByAngle(&out, &v, &axis, step);  // 0x0098f300 -> 0x005841a8
        node->m_v3Vector = out;
        const float length = node->m_fLength;
        node->m_v3Vector.z = length * node->m_v3Vector.z;
        node->m_v3Vector.x = length * node->m_v3Vector.x;
        node->m_v3Vector.y = length * node->m_v3Vector.y;
        if (step >= angle) {
            node->m_bTurning = 0;
            *target = kDirectionNull;
        }
        timer = node->m_fTimer;
    }
L388:
    if (!(timer <= 0.0f)) node->m_fTimer = timer - dt;  // ble
    return;
L3e0:
    if (parent->m_bTurning != 0) goto L498;
    if (target->x != kDirectionNull.x || target->y != kDirectionNull.y || target->z != kDirectionNull.z) goto L184;
    if (parent->m_pParent == nullptr) {
        *target = *direction;
    } else {
        *target = parent->m_v3Vector;
    }
    parent = node->m_pParent;
    node->m_fTimer = -1.0f;  // TOC +0x1ffc
    goto L174;
L498:
    if (node->m_fTimer != -1.0f) goto L184;
    node->m_fTimer = node->m_fSegment / followSpeed;
    if (parent->m_bTurning == 0) goto L184;
    if (turning != 0) goto L184;
    goto L538;
L528:
    if (node->m_bTurning != 0) goto L498;
L538:
    if (node->m_fTimer != -1.0f) goto L184;
    node->m_fTimer = node->m_fSegment / followSpeed;
    goto L184;
}

// 0x00300120 DirectionController_SetDirectionAndUpdate_maybe
void DirectionController_SetDirectionAndUpdate(float dt, float speed, float followSpeed, DirectionChain* chain,
                                               CVector3* direction) {
    uint8_t flag;
    float length;
    float dot;
    if (kDirectionNull.x == direction->x && direction->y == kDirectionNull.y) {
        flag = 0;
        if (direction->z == kDirectionNull.z) goto Store;
        length = DirectionSqrtf(
            ppc::fmadds(direction->z, direction->z, ppc::fmadds(direction->x, direction->x, direction->y * direction->y)));
        flag = 1;
        if (length == 0.0f) goto Unscaled;
        goto Scaled;
    }
    length = DirectionSqrtf(
        ppc::fmadds(direction->z, direction->z, ppc::fmadds(direction->x, direction->x, direction->y * direction->y)));
    flag = 1;
    if (length != 0.0f) goto Scaled;
Unscaled:
    dot = ppc::fmadds(direction->z, chain->m_v3Direction.z,
                      ppc::fmadds(direction->x, chain->m_v3Direction.x, direction->y * chain->m_v3Direction.y));
    if (dot >= 0.75f) flag = 0;  // TOC +0x2044; bge
    goto Keep;
Scaled: {
    const float inverse = 1.0f / length;  // TOC +0x2008
    direction->z = inverse * direction->z;
    direction->x = inverse * direction->x;
    direction->y = inverse * direction->y;
    dot = ppc::fmadds(direction->z, chain->m_v3Direction.z,
                      ppc::fmadds(direction->x, chain->m_v3Direction.x, direction->y * chain->m_v3Direction.y));
    if (!(dot < 0.75f)) flag = 0;  // blt keeps 1
}
Keep:
    chain->m_v3Direction = *direction;
Store:
    chain->m_f0c = speed;
    chain->m_f10 = followSpeed;
    const CVector3 copy = chain->m_v3Direction;
    DirectionController_Update(dt, speed, followSpeed, chain->m_pFirst, &copy, static_cast<uint8_t>(flag & 1));  // 0x002fd0b8
}
