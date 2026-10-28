// Reconstructed original translation unit: 0x2fc530-0x301408 (GAME_TOC1, main_toc1), 47 functions, 39 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: DirectionController (2), ComputeHeroDamageAfterReduction (1), ApplyTimedHeroDamage (1), UpdateHeroStatusAndTimedDamage (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2fc530  FUN_002fc530  [dead]
//   [ ] 0x2fc5a0  FUN_002fc5a0  [dead]
//   [ ] 0x2fc600  CKHkS08Hero_DropGrabbedEnemy
//   [ ] 0x2fc6e0  CKHkS08Hero_IsTargetEnemyOnGround_maybe
//   [ ] 0x2fc720  CKHkS08Hero_ReleaseGrabbedEnemyWithDamage
//   [ ] 0x2fc808  CKHkS08Hero_ReattachGrabbedEnemy
//   [ ] 0x2fc8e8  StaticInitAndDestruction_2fc8e8
//   [ ] 0x2fc918  _GLOBAL__D_2fc918
//   [ ] 0x2fc928  _GLOBAL__I_2fc928
//   [x] 0x2fc938  CKHkS08Hero_ResetCombatState_maybe
//   [ ] 0x2fcce0  CKHkS08Hero_GetVectorToPartner_maybe
//   [ ] 0x2fcd80  CKHkS08Hero_DetachGrabbedEnemyNode_maybe  [dead]
//   [ ] 0x2fce90  CKHkS08Hero_BreakGrabAndRecoil_maybe
//   [x] 0x2fd030  CKHkS08Hero_IsAnyComboKindActive
//   [ ] 0x2fd0b8  DirectionController_Update_maybe
//   [ ] 0x2fd5b0  CKHkS08Hero_IsGrabTargetInRange
//   [ ] 0x2fd7c0  CKHkS08Hero_GetAimPointOnHook
//   [ ] 0x2fdb40  CKHkS08Hero_FindBestHookInAimCone_maybe  [dead]
//   [ ] 0x2fde70  FUN_002fde70  [dead]
//   [ ] 0x2fdec8  CKHkS08Hero_GetAimPointOnEnemy
//   [ ] 0x2fe200  CKHkS08Hero_ComputeLungeScale_maybe
//   [x] 0x2fe3a8  CKHkS08Hero_ComputeLungeOffset_maybe
//   [ ] 0x2fe5b8  CKHkS08Hero_FindBestEnemyInAimCone_maybe
//   [ ] 0x2fe7f0  CKHkS08Hero_AcquireTargetInAimCone
//   [ ] 0x2fea88  CKHkS08Hero_TryAcquireTarget
//   [ ] 0x2fead8  ComputeHeroDamageAfterReduction
//   [ ] 0x2febb8  CKHkS08Hero_AcquireAbilityTargetVariant_maybe  [dead]
//   [ ] 0x2fed80  ApplyTimedHeroDamage_maybe
//   [ ] 0x2fef58  UpdateHeroStatusAndTimedDamage_maybe
//   [ ] 0x2fefb8  CKHkS08Hero_FindAbilityMecaTarget_maybe
//   [ ] 0x2ff670  CKHkS08Hero_TryFindAbilityMecaTarget_maybe  [dead]
//   [ ] 0x2ff6c8  CKHkS08Hero_AcquireAbilityTarget_maybe
//   [ ] 0x2ff890  CKHkS08Hero_ReleaseGrabbedEnemy_maybe
//   [ ] 0x2ff978  CKHkS08Hero_ValidateOrAcquireTarget_maybe
//   [ ] 0x2ffc80  CKHkS08Hero_StartGrab
//   [ ] 0x2fff48  CKHkS08Hero_TryGrabTarget
//   [ ] 0x300010  CKHkS08Hero_ThrowGrabbedEnemy
//   [ ] 0x300120  DirectionController_SetDirectionAndUpdate_maybe
//   [ ] 0x300318  CKHkS08Hero_ComputeThrowToPartner_maybe
//   [ ] 0x300568  CKHkS08Hero_ThrowGrabbedEnemyAtPartner
//   [ ] 0x3006f0  CKHkS08Hero_ComputeFinisherCameraVector_maybe
//   [x] 0x3008d8  CKHkS08Hero_StartLungeFromMark_maybe
//   [x] 0x3011c8  CKHkS08Hero_ComputeExternalPushForce_maybe
//   [ ] 0x301348  CKHkS08Hero_IsInSpecialAnim_maybe
//   [ ] 0x3013a0  CKHkS08Hero_IsAnimFinishedOrOther
//   [ ] 0x3013c8  CKHkS08Hero_IsAnimFinished
//   [ ] 0x3013f0  FUN_003013f0  [dead]
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Stub.h"

#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "crt/ppc_ops.h"

#include <cstring>

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
        m_unk124 = 0;
        m_unk1d28 = 0;
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
        m_unk1d24 = 0;
        m_unk1cc4 = 0;
        m_unk1cc8 = 0;
        m_unk1ab2 = 0;
        m_unk1d20 = 1.0f;
        m_unk1cc0 = 0;
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
        m_unk1bac = 0;
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
        m_unk1b68 = 0;
        CSGLeaf* glow = static_cast<CSGLeaf*>(m_unk1dc4);
        glow->m_sgProperties = (glow->m_sgProperties & 0xfffffffbu) | 4u;
        m_unk1cf4 = nullptr;
        m_unk1dc0 = 0;
        m_unk1dcc = nullptr;
        m_unk1df4 = 0;
    }
    m_unk1aec = -1.0f;  // TOC1 +0x1ffc (0xbf800000)
    m_unk1c1c = 0;
    m_unk1bf8 = 0;
    m_unk1bfc = 0;
    m_unk1c00 = 0;
    m_unk1c04 = 0;
    m_unk1c08 = 0;
    m_unk1c0c = 0;
    m_unk1c10 = 0;
    m_unk1c14 = 0;
    m_unk1c18 = 0;
    ResetComboAndAttackCredits();  // 0x0033f9d0
}

// 0x002fef58 UpdateHeroStatusAndTimedDamage_maybe: the equipped armour and the regeneration (0x30c700, step 4
// ANIM), then STUB(C2.7: combat): the timed damage (0x2fed80 with +0x88c), the grabbed enemy's mark damage (0x32edd0),
// the flight block +0x1d9c and the approach of +0x1108 with the camera notification.
void CKHkS08Hero::UpdateHeroStatusAndTimedDamage() {
    ApplyEquippedArmor();  // 0x0030c700
    DOTD_STUB_ONCE("UpdateHeroStatusAndTimedDamage_maybe 0x2fef58: after the armour (C2.7)");
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

// 0x002fe3a8 CKHkS08Hero_ComputeLungeOffset_maybe: the lunge direction +0x11cc toward the grabbed / targeted enemy
// (+0x124: its aim point from the hero's hot spot 5) or the hook (+0x12c: its aim point from the position), else (no
// target, no hook, neither +0x1ac5 nor +0x1ac6) +0x1b0c..+0x1b14 cleared.
void CKHkS08Hero::ComputeLungeOffset() {
    if (m_unk124 != 0) {
        // STUB(C2.7: targets): CSGHotSpot_GetWorldPosition of hot spot 5, CKHkS08Hero_GetAimPointOnEnemy 0x2fdec8 (no
        // enemy is targeted while walking); +0x11cc takes aim - hot spot, or +0x12a0 when the aim is 0x00c50da0.
        DOTD_STUB_ONCE("CKHkS08Hero_ComputeLungeOffset_maybe 0x2fe3a8: the enemy aim (C2.7)");
        return;
    }
    if (m_unk12c != 0) {
        // STUB(C2.7: hooks): CKHkS08Hero_GetAimPointOnHook 0x2fd7c0; +0x11cc takes aim - position, or +0x12a0.
        DOTD_STUB_ONCE("CKHkS08Hero_ComputeLungeOffset_maybe 0x2fe3a8: the hook aim (C2.7)");
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
        if (m_unk160 == 0xb9) return out;
        // STUB(C2.7: combat): the combo tree's (+0x1a88) current blow (vt+0x54); without a lunge running (+0x1ac7) and
        // with the mark flag +0xedc bit 7 it starts the lunge: the flag cleared, +0x1ac7 set, +0x1aa8 / +0x1d60 = blow
        // vt+0x70, +0x1d5c = vt+0x74, the target (ValidateOrAcquireTarget 0x2ff978, the grab checks), the direction to
        // the enemy / hook aim point (or +0x12a0), ComputeLungeScale 0x2fe200, ComputeFinisherCameraVector 0x3006f0 into
        // +0x1d68, +0x1d64 = 1, +0x1d74 = +0x1d60, TryStartFinisherCamera 0x32d6b0. No combo runs while walking.
        DOTD_STUB_ONCE("CKHkS08Hero_StartLungeFromMark_maybe 0x3008d8: the lunge start (C2.7)");
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

// 0x003011c8 CKHkS08Hero_ComputeExternalPushForce_maybe: the timed push of the record +0x1d3c (scale +0x1d3c, vector
// +0x1d48, time left +0x1d54); while it is active the hero's direction is locked (the airborne bit, as a jump).
CVector3 CKHkS08Hero::ComputeExternalPushForce(float dt) {
    CVector3 out = kHeroZeroVector;  // TOC1 +0x1ff4
    if (m_unk1d44 == 0) return out;
    out = StepTimedImpulse(dt, m_unk1d3c, m_unk1d44, m_unk1d48, m_unk1d4c, m_unk1d50, m_unk1d54, m_unk1d58);
    SetDirectionLock(1);  // 0x00354cf0 and the +0x354 bits
    return out;
}
