// Reconstructed original translation unit: 0x32bb30-0x32d578 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x32bb30  CKHkS08Hero_IsComboActive
//   [x] 0x32bb58  CKHkS08Hero_AnimState4_Hurt_Condition
//   [x] 0x32bb60  CKHkS08Hero_AnimState2_HurtType1_Condition
//   [x] 0x32bbc0  CKHkS08Hero_AnimState1_Fury_Condition
//   [x] 0x32bc08  CKHkS08Hero_AnimState5_Recovery_Condition
//   [x] 0x32bc10  CKHkS08Hero_UpdateComboTimeScale
//   [x] 0x32bed8  CKHkS08Hero_AnimState0_Dead_Condition
//   [x] 0x32bee8  CKHkS08Hero_GetComboAnimSpeed
//   [ ] 0x32c038  CKHkS08Hero_AdvanceGrabbedEnemyAnimTime_maybe  [dead]
//   [ ] 0x32c078  CKHkS08Hero_SyncGrabbedEnemyAnim_maybe  [dead: no pointer to its descriptor 0xb9dcb0, no call]
//   [x] 0x32c130  CKHkS08Hero_AnimState6_Ability_Condition
//   [x] 0x32c170  CKHkS08Hero_AnimState5_Recovery
//   [x] 0x32c268  CKHkS08Hero_AnimState1_Fury
//   [x] 0x32c330  StaticInitAndDestruction_32c330  (the two file statics at the end)
//   [ ] 0x32c360  _GLOBAL__D_32c360
//   [ ] 0x32c370  _GLOBAL__I_32c370
//   [x] 0x32c380  CKHkS08Hero_AnimState0_Dead
//   [x] 0x32c520  CKHkS08Hero_AnimState6_Ability
//   [x] 0x32c5e0  CKHkS08Hero_AnimState3_GuardedHurt_Condition
//   [x] 0x32c628  CKHkS08Hero_AnimState4_Hurt
//   [x] 0x32c780  CKHkS08Hero_AnimState3_GuardedHurt
//   [x] 0x32c950  CKHkS08Hero_AnimState2_HurtType1
//   [x] 0x32cb98  CKHkS08Hero_AnimState7_ComboAnim
//   [x] 0x32d4b0  CKHkS08Hero_vf100
//   [x] 0x32d4b8  CKHkS08Hero_vfEC
//   [x] 0x32d4c0  CKHkS08Hero_vfF0
//   [x] 0x32d4c8  CKHkS08Hero_ActState2_HurtReaction_Condition
//   [x] 0x32d4d0  CKHkS08Hero_ActState3_Recovery_maybe_Condition
//   [ ] 0x32d4d8  CKHkS08Hero_SetComboKindFlag  [dead: no pointer to its descriptor 0xb9e268, no call]
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "k2000/core/Stub.h"
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "Spyro2008/logic/CKS08HeroCombo.h"
#include "Spyro2008/logic/CKS08HeroBlow.h"

// 0x0032bb30 CKHkS08Hero_IsComboActive (the animation machine's ComboAnim condition): the current combo node
// (+0x1a88) is not the combo tree's root (+0x1a8c).
uint8_t CKHkS08Hero::IsComboActive(IKTime*, uint8_t) { return m_unk1a88 != m_unk1a8c ? 1 : 0; }

// 0x0032bb58 CKHkS08Hero_AnimState4_Hurt_Condition: a hurt reaction is pending (+0x1ac4).
uint8_t CKHkS08Hero::AnimHurtCondition(IKTime*, uint8_t) { return m_unk1ac4; }

// 0x0032bb60 CKHkS08Hero_AnimState2_HurtType1_Condition: a pending hurt of type 1 (+0x1ae8), unless guarded (+0xec8
// bit 2 with +0xed0 bit 15).
uint8_t CKHkS08Hero::AnimHurtType1Condition(IKTime*, uint8_t) {
    if ((m_unkec8 & 4u) != 0 && (m_unked0 & 0x8000u) != 0) return 0;
    if (m_unk1ac4 == 0) return 0;
    return m_unk1ae8 == 1u ? 1 : 0;
}

// 0x0032bbc0 CKHkS08Hero_AnimState1_Fury_Condition: the fury flag (+0xed4 bit 6) or a running fury timer (+0x1b00).
uint8_t CKHkS08Hero::AnimFuryCondition(IKTime*, uint8_t) {
    if ((m_unked4 & 0x40u) != 0) return 1;
    return !(m_unk1b00 <= 0.0f) ? 1 : 0;  // ble: a NaN timer counts as running
}

// 0x0032bc08 CKHkS08Hero_AnimState5_Recovery_Condition: a recovery is requested (+0x1acb).
uint8_t CKHkS08Hero::AnimRecoveryCondition(IKTime*, uint8_t) { return m_unk1acb; }

// 0x0032bed8 CKHkS08Hero_AnimState0_Dead_Condition: bit 27 of +0xec8.
uint8_t CKHkS08Hero::AnimDeadCondition(IKTime*, uint8_t) { return static_cast<uint8_t>((m_unkec8 >> 27) & 1u); }

// 0x0032c130 CKHkS08Hero_AnimState6_Ability_Condition: an active ability, unless +0x1d11 holds the animation.
uint8_t CKHkS08Hero::AnimAbilityCondition(IKTime*, uint8_t) {
    if (m_unk1d11 != 0) return 0;
    return IsAbilityActive();  // 0x002fc228
}

// 0x0032c5e0 CKHkS08Hero_AnimState3_GuardedHurt_Condition: a pending hurt while guarded (+0xec8 bit 2), or while
// animation 0xcf plays.
uint8_t CKHkS08Hero::AnimGuardedHurtCondition(IKTime*, uint8_t) {
    if (m_unk1ac4 == 0) return 0;
    if ((m_unkec8 & 4u) != 0) return 1;
    return m_unk160 == 0xcf ? 1 : 0;
}

// 0x0032d4b0 CKHkS08Hero_vf100 (vt+0x100): empty.
void CKHkS08Hero::Vf100(IKTime*) {}

// 0x0032d4c8 CKHkS08Hero_ActState2_HurtReaction_Condition: a hurt reaction is pending (+0x1ac4).
uint8_t CKHkS08Hero::ActHurtReactionCondition(IKTime*, uint8_t) { return m_unk1ac4; }

// 0x0032d4d0 CKHkS08Hero_ActState3_Recovery_maybe_Condition: a recovery is requested (+0x1acb).
uint8_t CKHkS08Hero::ActRecoveryCondition(IKTime*, uint8_t) { return m_unk1acb; }

// 0x0032d4c0 CKHkS08Hero_vfF0 (vt+0xf0): 0.
uint8_t CKHkS08Hero::VfF0() { return 0; }

// 0x0032d4b8 CKHkS08Hero_vfEC (vt+0xec): 0.
uint8_t CKHkS08Hero::VfEC() { return 0; }

// 0x0032bee8 CKHkS08Hero_GetComboAnimSpeed: the current blow's animation speed (vt+0x90); outside a grab combo scaled by
// +0xe80 (+0xed0 bit 0x800) and +0xeb4 (bit 0x10), 0 when not positive, at most +0xe74.
float CKHkS08Hero::GetComboAnimSpeed() {
    float speed = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimSpeed();
    if (IsGrabComboKind() != 0) return speed;  // 0x002fc208
    const uint32_t bits = m_unked0;
    if ((bits & 0x800u) != 0) speed = speed * m_unke80;
    if ((bits & 0x10u) != 0) speed = speed * m_unkeb4;
    if (speed <= 0.0f) return 0.0f;
    const float limit = m_unke74;
    if (speed >= limit) return limit;
    return speed;
}

namespace {
// The active key-frame controller of the hero's blend slot (vt+0x194; the blender's controller +0x50 array at the
// slot's +0x10).
CKAnmKeyFrameController* ComboActiveController(CKHkS08Hero* hero) {
    AnimBlendSlot* slot = hero->GetAnimBlendSlot();
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    return static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
}
}  // namespace

// 0x0032bc10 CKHkS08Hero_UpdateComboTimeScale: on the launch animations 0xb3 / 0xbb with a queued code, the time scale
// back to 1 and the hero removed from the camera service's owners (+0xe14, count +0xe24; the last one moved into its
// place); else, while the hero owns the time scale (+0x1ace), the scale from the blow's curve (vt+0xc0) at the
// animation's wrapped time over its length (1 without an animation).
void CKHkS08Hero::UpdateComboTimeScale() {
    const int32_t anim = static_cast<int16_t>(m_unk160);
    CTimeManager* time = g_pEngine->m_timeManager;  // TOC +0x26f4 -> +0x48
    if ((anim == 0xb3 || anim == 0xbb) && m_unk1a84 != 0) {
        if (time->m_fTimeScale != 1.0f) time->m_fTimeScale = 1.0f;
        CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
        if (camera->m_unke24 == 0) return;
        const uint32_t count = camera->m_unke24;
        for (uint32_t i = 0; i < count; ++i) {
            if (camera->m_apCinematicOwner[i] != this) continue;
            const uint32_t last = count - 1;
            camera->m_unke24 = last;
            if (i != last) camera->m_apCinematicOwner[i] = camera->m_apCinematicOwner[last];
            return;
        }
        return;
    }
    if (m_unk1ace == 0) return;
    const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_pAnimDico);
    const RtAnimAnimation* animation =
        CAnimationManager_GetAnimation(static_cast<uint32_t>(dictionary->m_apAnimations[anim]));
    if (animation == nullptr) {
        if (time->m_fTimeScale != 1.0f) time->m_fTimeScale = 1.0f;
        return;
    }
    const float length = animation->duration;
    float t = ComboActiveController(this)->m_unk54;
    if (length < t) {
        if (!(t >= 0.0f)) {
            do {
                t = t + length;
            } while (t < 0.0f);
        }
        while (length <= t) t = t - length;
    }
    const float scale = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->EvalTimeScale(t / length);  // vt+0xc0
    if (time->m_fTimeScale != scale) time->m_fTimeScale = scale;
}

// 0x0032cb98 CKHkS08Hero_AnimState7_ComboAnim: the blow's animation. Enter: it plays (crossfade 0.12), the grabbed
// enemy's paired animation, +0xec8 bits 0x18 set, +0x1a14 (skip the first advance). Leave: the speed back to 1, +0xec8
// bits 0x18 cleared. Tick: the time scale; the animation to show (the launch / grab sequences' +0x1ab2, else the
// blow's) started when another plays; else advanced at the combo speed (to its end once finished), the speed set, the
// grabbed enemy's animation kept in step.
uint8_t CKHkS08Hero::AnimComboAnim(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        if (static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow() == nullptr) SetComboActive(0, 0xff);
        const int32_t anim = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId();
        PlayAnimation(0.0f, 0.12f, static_cast<uint16_t>(anim));  // vt+0x184, TOC +0x26fc / +0x2710
        if (m_unk1acc != 0 && m_unk124 != nullptr) PairGrabbedEnemyAnim(anim, 0.12f, 0.0f);
        m_unkec8 |= 0x18u;
        m_unk1a14 = 1;
        return other;
    }
    if (phase != 0) {
        SetUnk890(1.0f);  // vt+0x19c, TOC +0x26f8
        m_unkec8 &= ~0x18u;
        return other;
    }
    if (static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow() == nullptr) {
        SetComboActive(0, 0xff);
        return other;
    }
    UpdateComboTimeScale();  // 0x0032bc10
    int32_t anim = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId();
    if (m_unk1abf != 0 || m_unk1ad1 != 0) anim = static_cast<int16_t>(m_unk1ab2);
    if (static_cast<int16_t>(m_unk160) != anim) {
        PlayAnimation(0.0f, 0.12f, static_cast<uint16_t>(anim));  // vt+0x184
        if (m_unk1acc != 0 && m_unk124 != nullptr) PairGrabbedEnemyAnim(anim, 0.12f, 0.0f);
        SetUnk890(1.0f);  // vt+0x19c
        return other;
    }
    float speed = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimSpeed();  // vt+0x90
    if (IsGrabComboKind() == 0) {  // 0x002fc208 (GetComboAnimSpeed's scaling, inlined)
        const uint32_t bits = m_unked0;
        if ((bits & 0x800u) != 0) speed = speed * m_unke80;
        if ((bits & 0x10u) != 0) speed = speed * m_unkeb4;
        if (speed <= 0.0f) {
            speed = 0.0f;
        } else if (speed >= m_unke74) {
            speed = m_unke74;
        }
    }
    if (m_unk1a14 != 0) {
        m_unk1a14 = 0;
    } else {
        // (the original also reads the active animation's duration here and drops it)
        const uint32_t toEnd = IsAnimFinished(static_cast<int16_t>(m_unk160)) != 0 ? 0u : 1u;  // 0x003013c8
        AdvanceAnimScaled(clock->m_afDeltaTime[0], 1.0f, speed, toEnd);  // 0x00301e70
    }
    SetUnk890(speed);  // vt+0x19c
    if (m_unk1acc != 0) {
        // The grabbed enemy kept in step: a pending re-pair (+0x1ab5) crossfades it at 0.2 to the hero's evaluated
        // time; a re-pair request (+0x1ab4) is taken a frame later; else it moves by the hero's wrapped time step.
        auto heroTrack = [this]() {
            AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
            return static_cast<CKAnmKeyFrameController*>(
                static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10]);
        };
        if (m_unk1ab5 != 0) {
            const int32_t anim = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId();  // vt+0x54, vt+0x8c
            const float evaluated = heroTrack()->m_unk54;
            if (m_unk124 != nullptr) PairGrabbedEnemyAnim(anim, 0.2f, evaluated);  // TOC +0x2720
            m_unk1ab5 = 0;
        } else if (m_unk1ab4 != 0) {
            m_unk1ab4 = 0;
            m_unk1ab5 = 1;
        } else {
            CKAnmKeyFrameController* track = heroTrack();
            const float length = track->GetDuration();  // 0x0007ab60
            float t = track->m_unk50;
            if (!(length >= t)) {
                const float turns = static_cast<float>(static_cast<double>(ppc::fctiwz(t / length)));
                t = t - length * turns;
            }
            const float evaluated = heroTrack()->m_unk54;
            if (m_unk124 != nullptr) static_cast<CKHkS08Enemy*>(m_unk124)->AdvanceGrabbedAnimTime(t - evaluated, 0, 0);  // 0x00289df8
        }
    }
    return other;
}

// DOTD: AnimState7_ComboAnim's inlined pairing: GetPairedGrabAnim 0x288dc8 (anim - 0xb2), the crossfade
// (CrossfadeAnimFromDictionary 0x28a2e0, mode 1, layer 0, slot 0) when another pair plays, the pair in +0x1ab0.
void CKHkS08Hero::PairGrabbedEnemyAnim(int32_t anim, float blend, float start) {
    CKHkS08Enemy* held = static_cast<CKHkS08Enemy*>(m_unk124);
    const int32_t paired = held->GetPairedGrabAnim(static_cast<uint32_t>(anim - 0xb2));
    if (paired == -1) return;
    if (m_unk1ab0 != paired) held->CrossfadeAnimFromDictionary(static_cast<uint32_t>(paired), 1, blend, start, 0, 0);
    m_unk1ab0 = static_cast<int16_t>(paired);
}

// 0x0032c780 CKHkS08Hero_AnimState3_GuardedHurt: the guarded hurt animation 0xcf (crossfade 0.12). Enter: +0xec4 bits
// 0x200000, 0x2000, 0x800 and 0x400 set, +0xed8 bit 0x4000000, and while +0xed0 bit 15 is set +0xec8 bits 0x10 and 8.
// Tick: the animation advanced by the frame time; once finished the pending hurt (+0x1ac4) cleared. Leave: +0xec8 bits
// 0x800000 / 0x400000 and the four +0xec4 bits cleared.
uint8_t CKHkS08Hero::AnimGuardedHurt(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        if (IsAnimFinished(0xcf) != 0) {  // 0x003013c8
            m_unk1ac4 = 0;
        } else {
            AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        }
        return other;
    }
    if (phase == 1) {
        PlayAnimation(0.0f, 0.12f, 0xcf);  // vt+0x184, TOC +0x26fc / +0x2710
        m_unkec4 = (m_unkec4 & ~0x200000u) | 0x200000u;
        m_unkec4 = (m_unkec4 & ~0x800u) | 0x800u;
        m_unkec4 = (m_unkec4 & ~0x400u) | 0x400u;
        m_unkec4 = (m_unkec4 & ~0x2000u) | 0x2000u;
        m_unked8 = (m_unked8 & ~0x4000000u) | 0x4000000u;
        if ((m_unked0 & 0x8000u) != 0) {
            m_unkec8 = (m_unkec8 & ~0x10u) | 0x10u;
            m_unkec8 = (m_unkec8 & ~8u) | 8u;
        }
        return other;
    }
    m_unkec8 &= ~0xc00000u;
    m_unkec4 &= 0xffdfd3ffu;
    return other;
}

// 0x0032c170 CKHkS08Hero_AnimState5_Recovery: enter plays the recovery of the animation shown (0xba: 0xcb, 0xb2: 0xca,
// else 0; crossfade 0.12); the tick advances it by the frame time.
uint8_t CKHkS08Hero::AnimRecovery(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return other;
    }
    if (phase != 1) return other;
    const int16_t shown = static_cast<int16_t>(m_unk160);
    uint32_t anim = shown == 0xba ? 0xcbu : 0u;
    if (shown == 0xb2) anim = 0xca;
    PlayAnimation(0.0f, 0.12f, static_cast<uint16_t>(anim));  // vt+0x184, TOC +0x26fc / +0x2710
    return other;
}

// 0x0032c268 CKHkS08Hero_AnimState1_Fury: enter plays animation 0x116 (start 0, the group's +0x18c crossfade); the tick
// advances it by the frame time.
uint8_t CKHkS08Hero::AnimFury(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return other;
    }
    if (phase == 1) PlayAnimation(0.0f, static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_unk18c, 0x116);  // vt+0x184, TOC +0x26fc
    return other;
}

// 0x0032c520 CKHkS08Hero_AnimState6_Ability: enter sets +0xec8 bits 3 and 4; the tick advances the animation by the frame
// time times the ability's speed +0x1d20 (unless an animation mark holds it, 0x301408); leave puts +0x1d20 back to 1 and
// clears the two bits.
uint8_t CKHkS08Hero::AnimAbility(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        AdvanceAnimTimeUnlessMarkOverride(m_unk1d20 * clock->m_afDeltaTime[0]);  // 0x00301408
    } else if (phase == 1) {
        m_unkec8 = (m_unkec8 & ~0x10u) | 0x10u;
        m_unkec8 = (m_unkec8 & ~0x8u) | 0x8u;
    } else {
        m_unk1d20 = 1.0f;  // TOC +0x26f8
        m_unkec8 &= ~0x18u;
    }
    return other;
}

// 0x0032c380 CKHkS08Hero_AnimState0_Dead: enter plays the death animation 0xcc (0xcd with +0x354 bit 0) with a 0.2
// crossfade; the tick goes on to 0xce from 0xcd once on the ground (not +0x354 bit 0, not +0xec4 bit 18), then advances
// the animation unless 0xcc or 0xce is over.
uint8_t CKHkS08Hero::AnimDead(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        if (m_unk160 == 0xcd && (m_unk354 & 1u) == 0 && (m_unkec4 & 0x40000u) == 0) {
            PlayAnimation(0.0f, 0.2f, 0xce);  // vt+0x184, TOC +0x26fc / +0x2720
        }
        if (IsAnimFinished(0xcc) != 0) return other;  // 0x003013c8
        if (IsAnimFinished(0xce) != 0) return other;
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return other;
    }
    if (phase != 1) return other;
    PlayAnimation(0.0f, 0.2f, (m_unk354 & 1u) != 0 ? 0xcd : 0xcc);  // vt+0x184
    return other;
}

// 0x0032c950 CKHkS08Hero_AnimState2_HurtType1: the hurt animation 0xc8 (0xc9 airborne: +0x354 bit 0) with a 0.12
// crossfade and +0xec4 bits 10, 11, 13 and 21 while it lasts; the tick adds the frame time to +0x1af8 and advances the
// animation scaled toward its reference duration (+0xdb0 for 0xc8, +0xdb4 for 0xc9, else 0) at the speed +0x12d0.
uint8_t CKHkS08Hero::AnimHurtType1(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        const float dt = clock->m_afDeltaTime[0];
        SetF32(m_unk1af8, AsF32(m_unk1af8) + dt);
        const uint16_t wanted = (m_unk354 & 1u) != 0 ? 0xc9 : 0xc8;
        if (m_unk160 != wanted) PlayAnimation(0.0f, 0.12f, wanted);  // vt+0x184, TOC +0x26fc / +0x2710
        const int16_t shown = static_cast<int16_t>(m_unk160);
        float reference = 0.0f;
        if (shown == 0xc8) reference = m_unkdb0;
        else if (shown == 0xc9) reference = m_unkdb4;
        AdvanceAnimScaled(dt, reference, m_unk12d0, 0);  // 0x00301e70
        return other;
    }
    if (phase == 1) {
        SetF32(m_unk1af8, 0.0f);
        const uint16_t wanted = (m_unk354 & 1u) != 0 ? 0xc9 : 0xc8;
        if (m_unk160 != wanted) PlayAnimation(0.0f, 0.12f, wanted);  // vt+0x184
        m_unkec4 |= 0x200000u;
        m_unkec4 |= 0x800u;
        m_unkec4 |= 0x400u;
        m_unkec4 |= 0x2000u;
        return other;
    }
    SetF32(m_unk1af8, 0.0f);
    m_unkec4 &= 0xffdfd3ffu;
    return other;
}

// 0x0032c628 CKHkS08Hero_AnimState4_Hurt: the hurt animation of the movement mode (ground 0xc5, flying 0xc6, climbing
// 0xc7, else none) with a 0.12 crossfade and +0x354 bit 4 while it lasts; the tick advances it by the frame time.
uint8_t CKHkS08Hero::AnimHurt(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return other;
    }
    if (phase != 1) {
        m_unk354 &= ~0x10u;
        return other;
    }
    const int8_t mode = static_cast<int8_t>(GetMovementMode());  // 0x003401b8
    uint32_t anim = 0;
    if (mode == 1) {
        anim = 0xc6;
    } else if (mode == 2) {
        anim = 0xc7;
    } else if (mode == 0) {
        anim = 0xc5;
    }
    PlayAnimation(0.0f, 0.12f, static_cast<uint16_t>(anim & 0xc7u));  // vt+0x184, TOC +0x26fc / +0x2710
    m_unk354 = (m_unk354 & ~0x10u) | 0x10u;
    return other;
}

// 0x0032c330 StaticInitAndDestruction_32c330: two file statics (0x00ceae54, 0x00ceae58) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae54 = -1.0f;
[[maybe_unused]] float s_unkceae58 = -1.0f;
}  // namespace
