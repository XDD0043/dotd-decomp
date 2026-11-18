// Reconstructed original translation unit: 0x32d578-0x333618 (GAME_TOC1, main_toc1), 33 functions, 32 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x32d578  StaticInitAndDestruction_32d578  (the two file statics at the end)
//   [ ] 0x32d5a8  _GLOBAL__I_32d5a8
//   [ ] 0x32d5b8  _GLOBAL__D_32d5b8
//   [ ] 0x32d5c8  FUN_0032d5c8  [dead]
//   [x] 0x32d6b0  CKHkS08Hero_TryStartFinisherCamera_maybe
//   [x] 0x32d890  CKHkS08Hero_AdvanceCombo
//   [x] 0x32d9b0  CKHkS08Hero_SetComboActive
//   [ ] 0x32df80  CKHkS08Hero_UpdateGrabReleaseTimer  [dead: no pointer to its descriptor 0xb9e308, no call]
//   [x] 0x32e028  CKHkS08Hero_ApproachField1108AndNotifyCamera_maybe
//   [x] 0x32e0f0  CKHkS08Hero_GrantKillUpgradeBonus_maybe
//   [x] 0x32e158  CKHkS08Hero_ActState11_GroundComboKind0_Condition
//   [x] 0x32e378  CKHkS08Hero_ActState5_GrabSlamSeq_maybe_Condition
//   [x] 0x32e3d0  CKHkS08Hero_ActState9_ClimbComboKind4_maybe_Condition
//   [x] 0x32e488  CKHkS08Hero_ActState8_FlyingComboKind3_Condition
//   [x] 0x32e668  CKHkS08Hero_ActState10_GroundAltComboKind2_Condition
//   [x] 0x32e820  CKHkS08Hero_ActState9_ClimbComboKind4_maybe
//   [x] 0x32eb80  CKHkS08Hero_ActState6_GrabDashComboKind5_Condition
//   [x] 0x32ecc0  CKHkS08Hero_ActState7_GroundGrabComboKind1_Condition
//   [x] 0x32edd0  CKHkS08Hero_ApplyGrabbedEnemyMarkDamage
//   [x] 0x32f048  CKHkS08Hero_InitFlightField1D9CBlock_maybe
//   [x] 0x32f170  CKHkS08Hero_ActState0_Dead_Condition
//   [x] 0x32f268  CKHkS08Hero_ActState3_Recovery_maybe
//   [x] 0x32f470  CKHkS08Hero_ActState8_FlyingComboKind3
//   [x] 0x32fce0  CKHkS08Hero_ActState10_GroundAltComboKind2
//   [x] 0x330528  CKHkS08Hero_ActState11_GroundComboKind0
//   [x] 0x330ab8  CKHkS08Hero_QueueAttackInputAndSelectElement
//   [x] 0x330fe8  CKHkS08Hero_ActState2_HurtReaction
//   [x] 0x331540  CKHkS08Hero_ActState6_GrabDashComboKind5
//   [x] 0x332078  CKHkS08Hero_ActState7_GroundGrabComboKind1
//   [x] 0x332a70  CKHkS08Hero_ActState5_GrabSlamSeq_maybe
//   [x] 0x3332c0  CKHkS08Hero_ActState0_Dead
//   [x] 0x333608  CKHkS08Hero_vfE8  (inline in its caller: CKHkS08Hero_19.cpp UpdateHero)
//   [x] 0x333610  CKHkS08Hero_vf114  (empty: skipped by its caller, CKHkS08Hero_19.cpp)
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include <cmath>
#include "k2000/math/Math.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/logic/animation/CKAnimatedCamera.h"
#include "k2000/logic/animation/CKAnimatedCameraData.h"
#include "k2000/scenegraph/CSGBranch.h"
#include <cstring>

#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/logic/CKS08HeroBlow.h"
#include "Spyro2008/logic/CKS08HeroCombo.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/misc/FloatApproach.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

namespace {
// The combo input window (inlined after each queued code): during a combo (a combo kind byte) a press made before the
// combo animation's last +0xd84 seconds (CKHkS08Hero_GetCurrentAnimTime 0x303368 against Anim_GetDuration 0x7ab60 of the
// inner blend slot's animation over CKHkS08Hero_GetComboAnimSpeed 0x32bee8) is consumed instead.
bool ComboWindowConsumes(CKHkS08Hero* hero) {
    if (hero->IsComboKindFlagSet() == 0) return false;  // 0x002fc1b0
    AnimBlendSlot* slot = hero->GetAnimBlendSlot();       // vt+0x194
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
    const float time = controller->m_unk50;
    const float duration = controller->GetDuration();  // 0x0007ab60
    const float last = duration / hero->GetComboAnimSpeed() - hero->m_unkd84;
    return last > time;  // ble: kept
}
}  // namespace

// 0x00330ab8 CKHkS08Hero_QueueAttackInputAndSelectElement: the attack code +0x1a84 from the button records (record 2
// alone: 1, record 3 alone: 2, record 1: 3, record 0: 0xc; a record consumed by the combo window is not taken again);
// none while locked to an object (+0x358 bit 0). Then, unless an ability runs or +0xed0 bit 4, the element +0x1cc4 from
// the d-pad input bytes 0x12..0x15 (0x13: 1, 0x12: 3, 0x14: 0, 0x15: 2; the same again with +0xed0 bit 27 selects 4 and
// keeps the previous in +0x1cc8); a change goes to the HUD.
void CKHkS08Hero::QueueAttackInputAndSelectElement() {
    if ((m_unk358 & 1u) != 0) {
        m_unk1a84 = 0;
        return;
    }
    const bool record2 = m_unkf28 == 0 && m_unkf1c == 1;
    const bool record3 = m_unkf3c == 0 && m_unkf30 == 1;
    if (record2 && !record3) {
        m_unk1a84 = 1;
        if (ComboWindowConsumes(this)) {
            m_unkf28 = 1;
            m_unk1a84 = 0;
        }
    }
    if (m_unkf3c == 0 && m_unkf30 == 1 && !(m_unkf28 == 0 && m_unkf1c == 1)) {
        m_unk1a84 = 2;
        if (ComboWindowConsumes(this)) {
            m_unk1a84 = 0;
            m_unkf3c = 1;
        }
    }
    if (m_unkf14 == 0 && m_unkf08 == 1) {
        m_unk1a84 = 3;
        if (ComboWindowConsumes(this)) {
            m_unk1a84 = 0;
            m_unkf14 = 1;
        }
    }
    if (m_unkf00 == 0 && m_unkef4 == 1) {
        m_unk1a84 = 0xc;
        if (ComboWindowConsumes(this)) {
            m_unk1a84 = 0;
            m_unkf00 = 1;
        }
    }
    const uint32_t previous = m_unk1cc4;
    if (IsAbilityActive() == 0 && (m_unked0 & 0x10u) == 0) {  // 0x002fc228
        const uint32_t flags = m_unked0;
        const uint8_t* inputs = m_unk36c;
        bool selected = true;
        if (inputs[0x13] != 0) {
            m_unk1cc4 = inputs[0x14] == 0 ? 1u : 0u;
        } else if (inputs[0x12] != 0) {
            m_unk1cc4 = inputs[0x15] != 0 ? 2u : 3u;
        } else if (inputs[0x14] != 0) {
            m_unk1cc4 = 0;
        } else if (inputs[0x15] != 0) {
            m_unk1cc4 = 2;
        } else {
            selected = false;
        }
        if (selected && m_unk1cc4 == previous && (flags & 0x8000000u) != 0) {
            if (previous == 4) return;
            m_unk1cc8 = previous;
            m_unk1cc4 = 4;
        }
    }
    const uint32_t element = m_unk1cc4;
    if (element == previous) return;
    if (m_ui8Hero == 0 || m_ui8Hero == 1) {
        CKS08GameManager* hudManager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        const uint8_t shown = static_cast<uint8_t>(m_unk1cc4);  // the byte +0x1cc7
        if (m_ui8Hero == 0) hudManager->ShowSpyroSelectedElementHud(shown);    // 0x5039e8
        else hudManager->ShowCynderSelectedElementHud(shown);                 // 0x5024d8
    }
}

// ---- The action machine's combo and death conditions (0x32e158..0x32f170) ----

namespace {
// A button record's "pressed this frame": its state word (+0x04) is 1 and it is not consumed (+0x10).
uint8_t ButtonPressed(uint32_t state, uint8_t consumed) { return consumed == 0 && state == 1u ? 1 : 0; }

// The kind 0 / 2 / 3 combos' button test (inlined in each): the presses of the second (+0xf18) and third (+0xf2c)
// records xored, compared with the first's (+0xf04); equal means no combo.
bool ComboButtonsCancel(const CKHkS08Hero* hero) {
    const uint8_t b18 = ButtonPressed(hero->m_unkf1c, hero->m_unkf28);
    const uint8_t b2c = ButtonPressed(hero->m_unkf30, hero->m_unkf3c);
    const uint8_t b04 = ButtonPressed(hero->m_unkf08, hero->m_unkf14);
    return static_cast<uint8_t>(b2c ^ b18) == b04;
}
}  // namespace

// 0x0032e158 CKHkS08Hero_ActState11_GroundComboKind0_Condition: on the ground with the combo timer below 0 (+0x1aec),
// the kind 0 byte (+0x1abc) or the buttons, no other kind active; with the timer at 0 or more and +0x354 bit 0 clear it
// counts down instead (clock +0x1c).
uint8_t CKHkS08Hero::ActGroundComboCondition(IKTime* clock, uint8_t) {
    if ((m_unkec8 & 0x400000u) != 0) return 0;
    uint32_t flags = m_unk354;
    if ((flags & 1u) != 0 && m_unk1abc == 0) return 0;
    if (m_unk1aec < 0.0f) {
        if (static_cast<int8_t>(GetMovementMode()) == 0) {  // 0x003401b8
            if (m_unk1abc == 0) {
                if (m_unk1a84 == 3u) {
                    m_unk1a84 = 0;  // the original stores the byte +0x1abc (0)
                    return 0;
                }
                if (ComboButtonsCancel(this)) return 0;
            }
            if (m_unk1ac4 != 0 || m_unk1abd != 0 || m_unk1ac0 != 0 || m_unk1ac1 != 0 || m_unk1ac3 != 0) return 0;
            return static_cast<uint8_t>(m_unk1abf ^ 1);
        }
        flags = m_unk354;
    }
    if ((flags & 1u) != 0) return 0;
    if (!(m_unk1aec >= 0.0f)) return 0;  // TOC +0x279c (0)
    m_unk1aec = m_unk1aec - clock->m_afDeltaTime[0];
    return 0;
}

// 0x0032e378 CKHkS08Hero_ActState5_GrabSlamSeq_maybe_Condition: +0x1abf, or the animation +0x1ab2 is 0xbd / 0xbe.
uint8_t CKHkS08Hero::ActGrabSlamSeqCondition(IKTime*, uint8_t) {
    if ((m_unkec8 & 0x400000u) != 0) return 0;
    if (m_unk1abf != 0) return 1;
    return m_unk1ab2 == 0xbd || m_unk1ab2 == 0xbe ? 1 : 0;
}

// 0x0032e3d0 CKHkS08Hero_ActState9_ClimbComboKind4_maybe_Condition: climbing (mode 2) with the combo timer below 0,
// inside a combo (+0x1a88 not the root +0x1a8c) or at a combo step other than 0 / 12 (+0x1a84), not while hurt.
uint8_t CKHkS08Hero::ActClimbComboCondition(IKTime*, uint8_t) {
    if ((m_unkec8 & 0x400000u) != 0) return 0;
    if (static_cast<int8_t>(GetMovementMode()) != 2) return 0;
    if (!(m_unk1aec < 0.0f)) return 0;
    if (m_unk1a88 == m_unk1a8c && (m_unk1a84 == 0 || m_unk1a84 == 0xcu)) return 0;
    return static_cast<uint8_t>(m_unk1ac4 ^ 1);
}

// 0x0032e488 CKHkS08Hero_ActState8_FlyingComboKind3_Condition: flying (mode 1) with the combo timer below 0, the kind 3
// byte (+0x1ac1) or the buttons; else the timer counts down while +0x354 bit 0 is set.
uint8_t CKHkS08Hero::ActFlyingComboCondition(IKTime* clock, uint8_t) {
    if ((m_unkec8 & 0x400000u) != 0) return 0;
    if (static_cast<int8_t>(GetMovementMode()) == 1 && m_unk1aec < 0.0f) {
        if (m_unk1ac1 == 0) {
            if (m_unk1a84 == 3u) {
                m_unk1a84 = 0;  // the original stores the byte +0x1ac1 (0)
                return 0;
            }
            if (ComboButtonsCancel(this)) return 0;
        }
        if (m_unk1ac4 != 0 || m_unk1abc != 0 || m_unk1ac0 != 0 || m_unk1abd != 0 || m_unk1ac3 != 0) return 0;
        return static_cast<uint8_t>(m_unk1abf ^ 1);
    }
    if ((m_unk354 & 1u) == 0) return 0;
    if (!(m_unk1aec >= 0.0f)) return 0;
    m_unk1aec = m_unk1aec - clock->m_afDeltaTime[0];
    return 0;
}

// 0x0032e668 CKHkS08Hero_ActState10_GroundAltComboKind2_Condition: on the ground with the combo timer below 0 (with
// +0x354 bit 0 clear only for the kind 2 byte +0x1ac0), the kind 2 byte or the buttons.
uint8_t CKHkS08Hero::ActGroundAltComboCondition(IKTime*, uint8_t) {
    if ((m_unkec8 & 0x400000u) != 0) return 0;
    if ((m_unk354 & 1u) == 0 && m_unk1ac0 == 0) return 0;
    if (!(m_unk1aec < 0.0f)) return 0;
    if (static_cast<int8_t>(GetMovementMode()) != 0) return 0;
    if (m_unk1ac0 == 0) {
        if (m_unk1a84 == 3u) {
            m_unk1a84 = 0;  // the original stores the byte +0x1ac0 (0)
            return 0;
        }
        if (ComboButtonsCancel(this)) return 0;
    }
    if (m_unk1ac4 != 0 || m_unk1abc != 0 || m_unk1abd != 0 || m_unk1ac1 != 0 || m_unk1ac3 != 0) return 0;
    return static_cast<uint8_t>(m_unk1abf ^ 1);
}

// 0x0032eb80 CKHkS08Hero_ActState6_GrabDashComboKind5_Condition: the kind 5 byte (+0x1ac3), or with the combo timer
// below 0 a dash (flying with +0x13d1, or on the ground with +0x1511) and the attack button (+0xef0) pressed.
uint8_t CKHkS08Hero::ActGrabDashComboCondition(IKTime*, uint8_t) {
    if (m_unk13d8 != 0) return 0;
    if ((m_unkec8 & 0x400000u) != 0) return 0;
    if (m_unk1ac3 == 0) {
        if (!(m_unk1aec < 0.0f)) return 0;
        if (!(static_cast<int8_t>(GetMovementMode()) == 1 && m_unk13d1 != 0)) {
            if (static_cast<int8_t>(GetMovementMode()) != 0) return 0;  // asked again, as the original
            if (m_unk1511 == 0) return 0;
        }
        if (m_unk1ac3 == 0 && ButtonPressed(m_unkef4, m_unkf00) == 0) return 0;
    }
    if (m_unk1ac4 != 0 || m_unk1abc != 0 || m_unk1ac0 != 0 || m_unk1ac1 != 0 || m_unk1abd != 0) return 0;
    return static_cast<uint8_t>(m_unk1abf ^ 1);
}

// 0x0032ecc0 CKHkS08Hero_ActState7_GroundGrabComboKind1_Condition: on the ground with the combo timer below 0 (with
// +0x354 bit 0 only for the kind 1 byte +0x1abd), the kind 1 byte or the attack button (+0xef0) pressed.
uint8_t CKHkS08Hero::ActGroundGrabComboCondition(IKTime*, uint8_t) {
    if ((m_unkec8 & 0x400000u) != 0) return 0;
    if ((m_unk354 & 1u) != 0 && m_unk1abd == 0) return 0;
    if (!(m_unk1aec < 0.0f)) return 0;
    if (static_cast<int8_t>(GetMovementMode()) != 0) return 0;
    if (m_unk1abd == 0 && ButtonPressed(m_unkef4, m_unkf00) == 0) return 0;
    if (m_unk1ac4 != 0 || m_unk1abc != 0 || m_unk1ac0 != 0 || m_unk1ac1 != 0 || m_unk1ac3 != 0) return 0;
    return static_cast<uint8_t>(m_unk1abf ^ 1);
}

// 0x0032f170 CKHkS08Hero_ActState0_Dead_Condition: not while the partner holds +0xec8 bit 27; the other dragon (the
// group's +0x66, signed) must be alive when it is not this one; then 1 at no health, else this hero's +0xec8 bit 27.
uint8_t CKHkS08Hero::ActDeadCondition(IKTime*, uint8_t) {
    if ((GetPartnerHero()->m_unkec8 & 0x08000000u) != 0) return 0;  // 0x002f85f8
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x277c -> +0x8c
    const int32_t other = static_cast<int8_t>(static_cast<IKGrpHero*>(m_pGrpHero)->m_unk66);
    if (static_cast<int32_t>(m_ui8Hero) != other && manager->GetDragonHealth(other) == 0) return 0;  // 0x004fd9c8
    if (manager->GetDragonHealth(m_ui8Hero) == 0) return 1;
    return static_cast<uint8_t>((m_unkec8 >> 27) & 1u);
}

// 0x0032e028 CKHkS08Hero_ApproachField1108AndNotifyCamera_maybe: for the controlled hero (+0x24 = +0x25) while the
// hero group's game manager test passes: the approach's current value (+0x1114) goes to +0x1b38 and to the current
// camera's field of view (vt+0x68), then the approach (+0x1108, 7 floats) steps with the frame dt (+0x88c).
void CKHkS08Hero::ApproachField1108AndNotifyCamera() {
    if (m_ui8Hero != m_ui8TrackedLeader) return;
    if (static_cast<CKGrpS08Hero*>(m_pGrpHero)->IsSinglePlayerAndTimer36cSet() == 0) return;  // 0x002d4d48
    const float value = m_unk1114;
    m_unk1b38 = value;
    static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_pCurrentCamera->SetFov(value);  // TOC +0x277c -> +0x70 -> +0x474, vt+0x68
    Math_ApproachWithAccelDecel(m_unk88c, &m_unk1108);  // 0x00243a10
}

// 0x0032edd0 CKHkS08Hero_ApplyGrabbedEnemyMarkDamage: +0x1b30 counts down by the frame dt. While a grabbed enemy (+0x124)
// is held (+0x1ac9) in a combo node with a blow and +0xedc bit 8 is set: the blow's damage when the enemy can be held
// there; then the grab animation's shockwave: 0xc4 at the hero's position (kind 1), or for 0xb4 (+0x160) alternately
// (+0x1ab6) at the position + 0.3 x (+0x12a0) + 2 x the frame's right axis, or with -2 x the right axis (kind 0).
void CKHkS08Hero::ApplyGrabbedEnemyMarkDamage() {
    m_unk1b30 = m_unk1b30 - m_unk88c;
    if (m_unk1ac9 == 0 || m_unk124 == nullptr) return;
    CKS08HeroCombo* combo = static_cast<CKS08HeroCombo*>(m_unk1a88);
    if (combo->m_pBlow == nullptr) return;  // vt+0x54 CKS08HeroCombo_GetBlow
    if ((m_unkedc & 0x100u) == 0) return;
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_unk124);
    if (enemy->CanBeHeldAtPosition() != 0) {  // 0x00289b38
        enemy->ReceiveDamage(reinterpret_cast<IKSerializable*>(combo->m_pBlow->m_pDamage), this);  // vt+0xb0 GetDamage, 0x0028a6e0
    }
    const CVector3 position{m_unk570, m_unk574, m_unk578};
    if (m_unk1ab2 == 0xc4) {
        SpawnShockwave(1, &position);  // 0x0033c688
        return;
    }
    if (m_unk160 != 0xb4) return;
    const RwV3d& right = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.right;  // +0x1c -> +0x04 -> +0x10
    const float k = 0.3f;  // TOC +0x27a0
    CVector3 at;
    if (m_unk1ab6 != 0) {
        const float ax = ppc::fmadds(m_unk12a0, k, position.x);
        const float ay = ppc::fmadds(m_unk12a4, k, position.y);
        const float az = ppc::fmadds(m_unk12a8, k, position.z);
        at.x = ax + (right.x + right.x);
        at.y = ay + (right.y + right.y);
        at.z = az + (right.z + right.z);
        m_unk1ab6 = 0;
    } else {
        const float ax = ppc::fmadds(m_unk12a0, k, position.x);
        const float az = ppc::fmadds(m_unk12a8, k, position.z);
        const float ay = ppc::fmadds(m_unk12a4, k, position.y);
        const float back = -2.0f;  // TOC +0x27a4
        at.z = ppc::fmadds(right.z, back, az);
        at.x = ppc::fmadds(right.x, back, ax);
        at.y = ppc::fmadds(right.y, back, ay);
        m_unk1ab6 = 1;
    }
    SpawnShockwave(0, &at);
}

// 0x0032f048 CKHkS08Hero_InitFlightField1D9CBlock_maybe: when flying with +0x354 bit 25 the flight impulse block
// +0x1d9c starts (scale +0x8d0 x 100, time 0.01, active, the direction the null vector, then the Y axis); then with both
// buttons +0xf18 / +0xf2c in state 1 or 3, +0x1afc = 0.22.
void CKHkS08Hero::InitFlightField1D9CBlock() {
    if ((m_unk354 & 0x02000000u) != 0) {
        const int8_t mode = static_cast<int8_t>(GetMovementMode());
        if (mode == 1) {
            const CVector3 zero = kHeroZeroVector;   // TOC +0x27a8: 0x00c50d64, the null vector
            const CVector3 axisY{0.0f, 1.0f, 0.0f};  // TOC +0x27b0: 0x00c50d40, the Y axis (a static initialiser's)
            m_unk1da0 = 0.01f;                       // TOC +0x27ac
            m_unk1d9c = m_unk8d0 * 100.0f;           // TOC +0x2780
            m_unk1da8 = zero.x;
            m_unk1dac = zero.y;
            m_unk1db0 = zero.z;
            m_unk1da4 = 0;
            m_unk1db4 = 0;
            m_unk1db8 = 0;
            m_unk1da8 = axisY.x;
            m_unk1db0 = axisY.z;
            m_unk1dac = axisY.y;
            m_unk1db8 = 0;
            std::memcpy(&m_unk1db4, &m_unk1da0, 4);
            m_unk1da4 = static_cast<uint8_t>(mode);
        }
    }
    if (m_unkf1c != 3u && m_unkf1c != 1u) return;
    if (m_unkf30 != 3u && m_unkf30 != 1u) return;
    m_unk1afc = 0.22f;  // TOC +0x27b4
}

namespace {
// 0x00a70730 (TOC +0x278c - 0x244): the blow sounds by animation, from 0x91 (-1: none). Constant data.
const int32_t kBlowSounds[52] = {39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
                                 57, 58, 59, 60, 61, 62, 63, -1, -1, -1, -1, -1, -1, -1, -1, 76, 77, 78,
                                 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94};
}  // namespace

// 0x0032d6b0 CKHkS08Hero_TryStartFinisherCamera_maybe: a player-controlled hero (+0x24 == +0x25) holding a target in a
// blow that may show it (vt+0x84) asks the hero group (lethal when the target's health +0x258 is at most what the combo
// still deals); allowed, the camera target's blend runs: +0x1108 / +0x110c 300, +0x1110 100, +0x1114 the camera's real
// field of view (+0x5d4), +0x111c the group's +0x1c0 (blow kind 2) or +0x1bc, +0x1b3c the blow's vt+0x88 and +0x1b34 the
// field of view's change.
void CKHkS08Hero::TryStartFinisherCamera() {
    if (m_unk124 == nullptr || m_ui8Hero != m_ui8TrackedLeader) return;
    CKS08HeroCombo* combo = static_cast<CKS08HeroCombo*>(m_unk1a88);
    CKS08HeroBlow* blow = combo->GetBlow();  // vt+0x54
    if (blow == nullptr || blow->Vf84() == 0) return;
    const uint32_t remaining = static_cast<uint32_t>(combo->GetMinRemainingDamage());  // 0x0036f610
    const float health = static_cast<CKHkS08Enemy*>(m_unk124)->m_unk258;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (group->AllowFinisherCamera(blow, health <= static_cast<float>(static_cast<double>(remaining)) ? 1 : 0) == 0) return;  // 0x002d5430
    m_unk1120 = 0.0f;
    m_unk1110 = 100.0f;  // TOC +0x2780
    m_unk110c = 300.0f;  // TOC +0x2784
    m_unk1118 = 0.0f;
    m_unk1108 = 300.0f;
    m_unk1114 = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_fRealFov;  // +0x5d4
    m_unk111c = blow->GetLinkCode() == 2 ? group->m_unk1c0 : group->m_unk1bc;  // vt+0x58
    m_unk1b3c = blow->Vf88();                                               // vt+0x88
    m_unk1b34 = m_unk1114 - m_unk111c;
}

// 0x0032d890 CKHkS08Hero_AdvanceCombo: the player's combo hits (game manager +0xc34 / +0xc38) give fury
// (AddDragonFuryFromAttack, unless the hero group's +0x2c8 bit 0x100), the blow's recovery delay into +0x1aec, +0x1ac7
// cleared, the next node by the queued link code (+0x1a84's low byte), the code cleared.
void CKHkS08Hero::AdvanceCombo() {
    const uint8_t dragon = m_ui8TrackedLeader;
    if (dragon == m_ui8Hero) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x277c -> +0x8c
        const uint32_t hits = (&manager->m_unkC34)[dragon];
        if (hits != 0 && (static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_unk2c8 & 0x100u) == 0) {
            manager->AddDragonFuryFromAttack(dragon, hits);  // 0x004fe1a0
        }
    }
    CKS08HeroCombo* current = static_cast<CKS08HeroCombo*>(m_unk1a88);
    m_unk1aec = current->GetBlow()->GetRecoveryDelay();  // vt+0x54, vt+0x7c
    m_unk1ac7 = 0;
    m_unk1a88 = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetNext(m_unk1a84 & 0xffu);  // vt+0x68
    m_unk1a84 = 0;
}

// 0x0032d9b0 CKHkS08Hero_SetComboActive (combat.md 2.1). Active: the current blow armed (grab flag +0x1ac8, +0x1aa8 = -1,
// +0x1aac = vt+0x70, its timer reset), the hit sphere cleared, the blow's sound at the combo speed's pitch, the blow's
// camera started once (+0xecc bit 0x20), the grab delays or a random voice (one draw, below +0xd9c percent: a second
// draw picks sound 0x44..0x46), the finisher camera of a grab combo, +0x1a18 counted, the attack credits (granted to
// the partner by the player, consumed by the partner). Inactive: grab and chain state cleared, a held enemy dropped,
// the node back to the idle root +0x1a8c, the targets cleared (not while hurt), the hit sphere cleared, the time scale
// restored when owned, the counters cleared. Then the combo kind's byte (kind 0xff: all cleared) and the active flags
// in +0x354 bit 11, +0xec4 bits 9 / 8 / 11 and +0xec8 bit 28.
void CKHkS08Hero::SetComboActive(uint8_t active, uint8_t kind) {
    if (active == 0) {
        m_unk1ac7 = 0;
        m_unkec8 &= ~0x80u;
        m_unk1ac8 = 0;
        if (m_unk1acc != 0 && m_unk124 != nullptr) DropGrabbedEnemy();  // 0x002fc600
        m_unk1aca = 0;
        m_unk1a88 = m_unk1a8c;
        m_unk1ac9 = 0;
        m_unk1ab2 = 0;
        m_unk1ad1 = 0;
        if (m_unk1ac4 == 0) {
            m_unk12c = nullptr;
            m_unk124 = nullptr;
        }
        SetupHitSphere(1.0f, 0, -1, nullptr);  // 0x0030cc40, TOC +0x2788
        if (m_unk1acd != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;
            m_unk1acd = 0;
        }
        m_unk1ad0 = 0;
        m_unk1a18 = 0;
        m_unk1b30 = 0.0f;
    } else {
        CKS08HeroBlow* blow = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow();  // vt+0x54
        m_unk1aa8 = -1.0f;  // TOC +0x276c
        m_unk1ac8 = blow->IsGrabBlow();  // vt+0x9c
        m_unk1aac = blow->Vf70();
        m_unk1ab8 = 0;
        blow->ResetTimer();  // vt+0xbc
        SetupHitSphere(1.0f, 0, -1, nullptr);
        const int32_t sound = kBlowSounds[blow->GetAnimId() - 0x91];  // vt+0x8c
        const float pitch = ComputeSoundPitchFromAnimSpeed(GetComboAnimSpeed());  // 0x00333688, 0x0032bee8
        PlaySound(1.0f, pitch, static_cast<uint32_t>(sound), 0);  // 0x00334188
        if ((m_unkecc & 0x20u) == 0) {
            CKAnimatedCamera* camera = static_cast<CKAnimatedCamera*>(m_unk1b28);
            if (camera->Start(0.0f, static_cast<CKAnimatedCameraData*>(blow->GetCameraData()),
                              static_cast<CSGBranch*>(m_pKGLObject)) != 0) {  // vt+0x50
                m_unkecc = (m_unkecc & ~0x20u) | 0x20u;
                m_unked0 = (m_unked0 & ~0x40u) | 0x40u;
            }
        }
        if (m_unk1ac8 != 0) {
            m_unk1af0 = blow->GetThrowDelay();    // vt+0xa4
            m_unk1af4 = blow->GetReleaseDelay();  // vt+0xa8
        } else {
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
            if (((r * 100u) >> 16) < static_cast<uint32_t>(m_unkd9c)) {
                const uint32_t voice = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
                PlaySound(1.0f, 1.0f, ((voice * 3u) >> 16) + 0x44u, 0);
            }
        }
        if (IsGrabComboKind() != 0) TryStartFinisherCamera();  // 0x002fc208, 0x0032d6b0
        m_unk1a18 = m_unk1a18 + 1;
        if (m_ui8Hero == m_ui8TrackedLeader) {
            GrantPartnerAttackCredits();  // 0x0033fa78
        } else {
            ConsumeAttackCredits();  // 0x0033f9e8
        }
    }
    switch (kind) {
        case 0:
            m_unk1abc = active;
            break;
        case 1:
            m_unk1abd = active;
            break;
        case 2:
            m_unk1ac0 = active;
            break;
        case 3:
            m_unk1ac1 = active;
            break;
        case 4:
            m_unk1ac2 = active;
            break;
        case 5:
            m_unk1ac3 = active;
            if (active == 0) m_unk1abf = 0;
            break;
        case 0xff:
            m_unk1abf = 0;
            m_unk1abc = 0;
            m_unk1abd = 0;
            m_unk1abe = 0;
            m_unk1ac0 = 0;
            m_unk1ac1 = 0;
            m_unk1ac2 = 0;
            m_unk1ac3 = 0;
            break;
        default:
            break;
    }
    const uint32_t on = active;
    m_unk354 = (m_unk354 & ~0x800u) | (on << 11);
    m_unkec4 = (m_unkec4 & ~0x200u) | (on << 9);
    m_unkec8 = (m_unkec8 & ~0x10000000u) | (on << 28);
    m_unkec4 = (m_unkec4 & ~0x100u) | (on << 8);
    m_unkec4 = (m_unkec4 & ~0x800u) | (on << 11);
}

// 0x00330528 CKHkS08Hero_ActState11_GroundComboKind0: the ground combo (kind 0). Enter: a queued launch (code 2) starts
// the launch sequence (+0x1ad1, animation 0x10f in +0x1ab2); the node from the kind 0 root by the queued code
// (+0x1a84), combo on (owning the time scale) or all kinds off; the code cleared. Leave: the time scale restored when
// owned, the grab target dropped unless a grab blow, the combo off unless idle, +0x1ab2 and +0x364 bit 0x1000000
// cleared. Tick (while a combo kind is on): the launch sequence (at the end of 0x10f, or once its length at the combo
// speed reaches +0xf34, the slam blow +0x1a30[0] in the scratch combo +0x1aa4 with its sound, animation 0x99); then the
// blow: its timer and hit spheres while its animation plays, at its end the next node (AdvanceCombo) or the combo off.
uint8_t CKHkS08Hero::ActGroundCombo(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        if (m_unk1a84 == 2) {
            m_unk1ad1 = 1;
            m_unk1ab2 = 0x10f;
        }
        CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a8c)->GetNext(m_unk1a84 & 0xffu);  // vt+0x68
        m_unk1a88 = next;
        if (next == nullptr || next->GetBlow() == nullptr) {
            SetComboActive(0, 0xff);  // 0x0032d9b0
        } else {
            SetComboActive(1, 0);
            if (m_unk1acd == 0) {
                m_unk1ace = 1;
                m_unk1acd = 1;
            }
        }
        m_unk1a84 = 0;
        return other;
    }
    if (phase != 0) {
        if (m_unk1ace != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;
            m_unk1ace = 0;
            m_unk1acd = 0;
        }
        if (m_unk1ac8 == 0) m_unk124 = nullptr;
        if (m_unk1a88 != m_unk1a8c) SetComboActive(0, 0xff);
        m_unk1ab2 = 0;
        m_unk364 &= ~0x1000000u;
        return other;
    }
    if (IsAnyComboKindActive() == 0) return other;  // 0x002fd030
    if (m_unk1ad1 != 0) {
        // The launch sequence.
        bool slam = false;
        if (IsAnimFinished(static_cast<int16_t>(m_unk1ab2)) != 0 && m_unk1ab2 == 0x10f) {  // 0x003013c8
            bool early = false;
            if (m_unkf3c == 0) {
                const float limit = m_unkf34;
                AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
                CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
                const float length = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])
                                         ->GetDuration();  // 0x0007ab60
                early = length / GetComboAnimSpeed() <= limit;
            }
            if (early || (m_unked4 & 4u) != 0) {
                slam = true;
            } else {
                m_unk1ad1 = 0;
                m_unk1a84 = 0;
            }
        }
        if (slam) {
            m_unked4 &= ~4u;
            m_unkf3c = 1;
            CKS08HeroCombo* scratch = static_cast<CKS08HeroCombo*>(m_unk1aa4);
            scratch->SetBlow(static_cast<CKS08HeroBlow*>(m_apUnk1a30[0]));  // vt+0x58
            m_unk1a88 = m_unk1aa4;
            CKS08HeroCombo* current = static_cast<CKS08HeroCombo*>(m_unk1a88);
            if (current != nullptr && current->GetBlow() != nullptr) {
                const int32_t sound = kBlowSounds[current->GetBlow()->GetAnimId() - 0x91];
                const float pitch = ComputeSoundPitchFromAnimSpeed(GetComboAnimSpeed());
                PlaySound(1.0f, pitch, static_cast<uint32_t>(sound), 0);  // 0x00334188
            }
            m_unk1ab2 = 0x99;
        } else if (m_unk1ab2 == 0x10f) {
            return other;
        }
    }
    CKS08HeroCombo* current = static_cast<CKS08HeroCombo*>(m_unk1a88);
    if (current->GetBlow() == nullptr) SetComboActive(0, 0);
    CKS08HeroBlow* blow = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow();
    const int32_t anim = blow->GetAnimId();  // vt+0x8c
    if (IsAnimFinished(anim) == 0) {
        static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->TickTimer(clock->m_afDeltaTime[0]);  // vt+0xb4
        UpdateComboHitSpheres();  // 0x0030f220
        return other;
    }
    AdvanceCombo();  // 0x0032d890
    CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a88);
    if (next == nullptr || next->GetBlow() == nullptr) {
        SetComboActive(0, 0);
    } else {
        SetComboActive(1, 0);
        m_unk1aec = -1.0f;  // TOC +0x276c
    }
    return other;
}

namespace {
float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}
uint32_t FloatAsWord(float value) {
    uint32_t word;
    std::memcpy(&word, &value, sizeof(word));
    return word;
}
}  // namespace

// The launch sequences of the air combos (kinds 2 and 3): at the end of the launch animation, the slam when it was short
// at the combo speed (its length / the speed not above +0xf34, on the first launch only: +0xf3c) or when +0xed4 bit 2 asks
// for it (the PPC tests are the ordered ones).
bool CKHkS08Hero::ComboLaunchEndsInSlam() {
    if (m_unkf3c == 0) {
        const float limit = m_unkf34;
        AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
        CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
        const float length =
            static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])->GetDuration();  // 0x0007ab60
        if (length / GetComboAnimSpeed() <= limit) return true;
    }
    return (m_unked4 & 4u) != 0;
}

// The air combos' test while the slam animation plays: the slam ends early (the combo off, the blow's recovery delay
// +0x7c as the re-attack cooldown) once the partners are near enough (the group's partner distance over its +0x10c,
// times half its +0x154, not above the dragon's limit +0x314 / +0x318; 0 for another dragon) unless +0xec4 bit 22, or
// whenever +0xec4 bit 18 is set; returns whether it ended.
bool CKHkS08Hero::ComboSlamEndsEarly(uint8_t kind) {
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    const float distance = group->m_unk108;  // 0x002ce518 CKGrpS08Hero_GetMaxPartnerDistance_maybe
    float limit = 0.0f;  // TOC +0x279c
    if (m_ui8Hero == 0) {
        limit = WordAsFloat(group->m_unk2d4[16]);  // +0x314
    } else if (m_ui8Hero == 1) {
        limit = WordAsFloat(group->m_unk318);
    }
    const float ratio = distance / group->m_unk10c * (group->m_unk154 * 0.5f);  // TOC +0x27bc
    const bool near = ratio <= limit;
    if (near && (m_unkec4 & 0x400000u) == 0) {
        // ends
    } else if ((m_unkec4 & 0x40000u) == 0) {
        return false;
    }
    m_unkec4 &= ~0x8000000u;
    m_unk1aec = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetRecoveryDelay();  // vt+0x54, vt+0x7c
    m_unk1ac7 = 0;
    SetComboActive(0, kind);  // 0x0032d9b0
    return true;
}

// The air combos' end of the slam's fall on the ground: a shock wave at the hero's +0x570 unless the ground is of the kind
// flagged 0x200 (+0x38).
void CKHkS08Hero::ComboSlamShockwave() {
    IKSerializable* ground = GetGroundInfo();  // 0x00361b68 (twice)
    if (ground == nullptr || (static_cast<ICollisionMesh*>(GetGroundInfo())->m_ui16PropertiesFlags & 0x200u) == 0) {
        const CVector3 position = {m_unk570, m_unk574, m_unk578};
        SpawnShockwave(1, &position);  // 0x0033c688
    }
}

// The combo rows' blow step: the blow's timer and hit spheres while its animation plays; at its end the next node
// (AdvanceCombo): on with the re-attack cooldown at -1, or the combo off. Kind 2 also ends the combo (and the queued code)
// when the hero left the ground (+0x1511).
uint8_t CKHkS08Hero::ComboBlowStep(IKTime* clock, uint8_t kind, uint8_t other) {
    if (static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow() == nullptr) SetComboActive(0, kind);  // vt+0x54
    const int32_t anim = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId();  // vt+0x8c
    if (IsAnimFinished(anim) == 0) {  // 0x003013c8
        static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->TickTimer(clock->m_afDeltaTime[0]);  // vt+0xb4
        UpdateComboHitSpheres();  // 0x0030f220
        return other;
    }
    AdvanceCombo();  // 0x0032d890
    if (kind == 2 && m_unk1511 == 0) {
        SetComboActive(0, kind);
        m_unk1a84 = 0;
        return other;
    }
    CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a88);
    if (next == nullptr || next->GetBlow() == nullptr) {
        SetComboActive(0, kind);
    } else {
        SetComboActive(1, kind);
        m_unk1aec = -1.0f;  // TOC +0x276c
    }
    return other;
}

// 0x0032fce0 CKHkS08Hero_ActState10_GroundAltComboKind2: the ground combo of kind 2 (root +0x1a94). Enter: a queued launch
// (code 2) starts the launch sequence (+0x1ad1, animation 0x110); the node by the queued code: the combo on (owning the
// time scale), +0x1444 from +0x8a8, +0x11d8 from +0x8a0, +0xec8 bits 17 and 8; else every kind off; the code cleared.
// Leave: the combo off unless idle, the time scale restored when owned, the grab target dropped, +0xec4 bit 27, +0xec8
// bits 17 / 8, +0x1ab2 and +0x364 bit 24 cleared. Tick: the launch (0x110: the slam blow +0x1a30[1] in the scratch combo,
// +0x1b18 100, +0xec4 bit 27, its sound, then 0xa2; the slam ends early near the partner; off the ground 0x114 with the
// shock wave, at its end the next node and the combo off), then the blow step.
uint8_t CKHkS08Hero::ActGroundAltCombo(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        if (m_unk1a84 == 2) {
            m_unk1ad1 = 1;
            m_unk1ab2 = 0x110;
        }
        CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a94)->GetNext(m_unk1a84 & 0xffu);  // vt+0x68
        m_unk1a88 = next;
        if (next == nullptr || next->GetBlow() == nullptr) {
            SetComboActive(0, 0xff);
        } else {
            SetComboActive(1, 2);
            if (m_unk1acd == 0) {
                m_unk1ace = 1;
                m_unk1acd = 1;
            }
            m_unk1444 = FloatAsWord(m_unk8a8);
            m_unkec8 = (m_unkec8 & 0xfffdffffu) | 0x20000u;
            m_unk11d8 = FloatAsWord(m_unk8a0);
            m_unkec8 = (m_unkec8 & 0xfffffeffu) | 0x100u;
        }
        m_unk1a84 = 0;
        return other;
    }
    if (phase != 0) {
        if (m_unk1a88 != m_unk1a8c) SetComboActive(0, 0xff);
        if (m_unk1ace != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x2788
            m_unk1ace = 0;
            m_unk1acd = 0;
        }
        m_unk124 = nullptr;
        m_unkec4 &= ~0x8000000u;
        m_unkec8 &= 0xfffdfeffu;
        m_unk1ab2 = 0;
        m_unk364 &= ~0x1000000u;
        return other;
    }
    if (IsAnyComboKindActive() == 0) return other;  // 0x002fd030
    if (m_unk1ad1 != 0) {
        const int16_t anim = static_cast<int16_t>(m_unk1ab2);
        if (IsAnimFinished(anim) != 0) {
            if (anim == 0x110) {
                if (!ComboLaunchEndsInSlam()) {
                    m_unk1ad1 = 0;
                    m_unk1a84 = 0;
                } else {
                    m_unked4 &= ~4u;
                    m_unkf3c = 1;
                    CKS08HeroCombo* scratch = static_cast<CKS08HeroCombo*>(m_unk1aa4);
                    scratch->SetBlow(static_cast<CKS08HeroBlow*>(m_apUnk1a30[1]));  // vt+0x58
                    m_unk1a88 = m_unk1aa4;
                    m_unk1b18 = 100.0f;  // TOC +0x2780
                    m_unkec4 = (m_unkec4 & ~0x8000000u) | 0x8000000u;
                    m_unkec8 &= ~0x20000u;
                    CKS08HeroCombo* current = static_cast<CKS08HeroCombo*>(m_unk1a88);
                    if (current != nullptr && current->GetBlow() != nullptr) {
                        const int32_t sound = kBlowSounds[current->GetBlow()->GetAnimId() - 0x91];  // TOC +0x278c
                        const float pitch = ComputeSoundPitchFromAnimSpeed(GetComboAnimSpeed());  // 0x00333688
                        PlaySound(1.0f, pitch, static_cast<uint32_t>(sound), 0);  // 0x00334188
                    }
                    m_unk1ab2 = 0xa2;
                    return ComboBlowStep(clock, 2, other);
                }
            } else if (anim == 0x114) {
                m_unkec4 &= ~0x8000000u;
                AdvanceCombo();
                SetComboActive(0, 2);
                return other;
            } else if (anim == 0xa2) {
                m_unk1ab2 = 0xa2;
                return other;
            }
        } else if (anim == 0xa2) {
            if (m_unk1511 == 0) {
                m_unk1ab2 = 0x114;
                ComboSlamShockwave();
            } else {
                if (ComboSlamEndsEarly(2)) return other;
                return ComboBlowStep(clock, 2, other);
            }
        }
        if (static_cast<int16_t>(m_unk1ab2) == 0x110) return other;
    }
    return ComboBlowStep(clock, 2, other);
}

// 0x0032e820 CKHkS08Hero_ActState9_ClimbComboKind4_maybe: the combo of kind 4 (root +0x1a9c, climbing). Enter: the node
// by the queued code: the combo on (owning the time scale) or every kind off; the code cleared. Leave: the combo off
// unless idle, the time scale restored when owned, the grab target dropped, +0x364 bit 24 cleared. Tick: the blow step.
uint8_t CKHkS08Hero::ActClimbCombo(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a9c)->GetNext(m_unk1a84 & 0xffu);  // vt+0x68
        m_unk1a88 = next;
        if (next == nullptr || next->GetBlow() == nullptr) {
            SetComboActive(0, 0xff);
        } else {
            SetComboActive(1, 4);
            if (m_unk1acd == 0) {
                m_unk1ace = 1;
                m_unk1acd = 1;
            }
        }
        m_unk1a84 = 0;
        return other;
    }
    if (phase != 0) {
        if (m_unk1a88 != m_unk1a8c) SetComboActive(0, 0xff);
        if (m_unk1ace != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x2788
            m_unk1ace = 0;
            m_unk1acd = 0;
        }
        m_unk124 = nullptr;
        m_unk364 &= ~0x1000000u;
        return other;
    }
    if (IsAnyComboKindActive() == 0) return other;
    return ComboBlowStep(clock, 4, other);
}

// 0x0032f470 CKHkS08Hero_ActState8_FlyingComboKind3: the combo of kind 3 (root +0x1a98, in the air). Enter: on the ground
// (+0x354 bit 0 clear) only a queued code 3 goes on, else the movement mode 0; in the air a queued launch (code 2) starts
// the launch sequence (0x111); the node by the queued code: the combo on (owning the time scale), +0x1444 from +0x8ac,
// +0x11d8 from +0x8a4, +0xec8 bits 17 and 8; else every kind off; the code cleared. Leave: the time scale restored when
// owned, the grab target dropped unless +0x1ac8, the combo off unless idle, +0xec8 bits 17 / 8, +0xec4 bit 27, +0x1ab2
// and +0x364 bit 24 cleared. Tick: the launch (0x111: the slam blow +0x1a30[2], its sound, 0x113; at its end +0x1b18 100,
// +0xec4 bit 27, 0xa9; the fall ends early near the partner; landed (+0x13d1 clear) 0x115 with the shock wave, at its
// end the next node and the combo off), then the blow step.
uint8_t CKHkS08Hero::ActFlyingCombo(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        if ((m_unk354 & 1u) == 0) {
            if (m_unk1a84 != 3) {
                SetMovementMode(0);  // 0x00340c18
                return other;
            }
        } else if (m_unk1a84 == 2) {
            m_unk1ad1 = 1;
            m_unk1ab2 = 0x111;
        }
        CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a98)->GetNext(m_unk1a84 & 0xffu);  // vt+0x68
        m_unk1a88 = next;
        if (next == nullptr || next->GetBlow() == nullptr) {
            SetComboActive(0, 0xff);
        } else {
            SetComboActive(1, 3);
            if (m_unk1acd == 0) {
                m_unk1ace = 1;
                m_unk1acd = 1;
            }
            m_unk1444 = FloatAsWord(m_unk8ac);
            m_unkec8 = (m_unkec8 & 0xfffdffffu) | 0x20000u;
            m_unk11d8 = FloatAsWord(m_unk8a4);
            m_unkec8 = (m_unkec8 & 0xfffffeffu) | 0x100u;
        }
        m_unk1a84 = 0;
        return other;
    }
    if (phase != 0) {
        if (m_unk1ace != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x2788
            m_unk1ace = 0;
            m_unk1acd = 0;
        }
        if (m_unk1ac8 == 0) m_unk124 = nullptr;
        if (m_unk1a88 != m_unk1a8c) SetComboActive(0, 0xff);
        m_unkec8 &= ~0x20000u;
        m_unkec4 &= ~0x8000000u;
        m_unkec8 &= ~0x100u;
        m_unk1ab2 = 0;
        m_unk364 &= ~0x1000000u;
        return other;
    }
    if (IsAnyComboKindActive() == 0) return other;
    if (m_unk1ad1 != 0) {
        const int16_t anim = static_cast<int16_t>(m_unk1ab2);
        if (IsAnimFinished(anim) != 0) {
            if (anim == 0x111) {
                if (!ComboLaunchEndsInSlam()) {
                    m_unk1ad1 = 0;
                    m_unk1a84 = 0;
                } else {
                    m_unked4 &= ~4u;
                    m_unkf3c = 1;
                    CKS08HeroCombo* scratch = static_cast<CKS08HeroCombo*>(m_unk1aa4);
                    scratch->SetBlow(static_cast<CKS08HeroBlow*>(m_apUnk1a30[2]));  // vt+0x58
                    m_unk1a88 = m_unk1aa4;
                    CKS08HeroCombo* current = static_cast<CKS08HeroCombo*>(m_unk1a88);
                    if (current != nullptr && current->GetBlow() != nullptr) {
                        const int32_t sound = kBlowSounds[current->GetBlow()->GetAnimId() - 0x91];  // TOC +0x278c
                        const float pitch = ComputeSoundPitchFromAnimSpeed(GetComboAnimSpeed());
                        PlaySound(1.0f, pitch, static_cast<uint32_t>(sound), 0);
                    }
                    m_unk1ab2 = 0x113;
                    return ComboBlowStep(clock, 3, other);
                }
            } else if (anim == 0x113) {
                m_unk1b18 = 100.0f;  // TOC +0x2780
                m_unk1ab2 = 0xa9;
                m_unkec4 = (m_unkec4 & ~0x8000000u) | 0x8000000u;
                m_unkec8 &= 0xfffdfeffu;
                return other;
            } else if (anim == 0x115) {
                m_unkec4 &= ~0x8000000u;
                AdvanceCombo();
                SetComboActive(0, 3);
                return other;
            } else if (anim == 0xa9) {
                m_unk1ab2 = 0xa9;
                return other;
            }
        } else if (anim == 0xa9) {
            if (m_unk13d1 == 0) {
                m_unk1ab2 = 0x115;
                ComboSlamShockwave();
            } else {
                if (ComboSlamEndsEarly(3)) return other;
                return ComboBlowStep(clock, 3, other);
            }
        }
        if (static_cast<int16_t>(m_unk1ab2) == 0x111) return other;
    }
    return ComboBlowStep(clock, 3, other);
}

namespace {
// The hero's move vector in its game manager record (+0xe04 + hero * 0x20), as GetGameManagerExternalForce reads it.
CVector3 HurtRecordVector(uint8_t hero) {
    const CKS08GameManager* manager = static_cast<const CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x277c
    const uint32_t* record = &manager->m_unkDF4[1 + hero * 8u + 3];
    CVector3 v;
    std::memcpy(&v.x, &record[0], 4);
    std::memcpy(&v.y, &record[1], 4);
    std::memcpy(&v.z, &record[2], 4);
    return v;
}
float HurtSpeed(const CVector3& v) { return std::sqrt(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, v.y * v.y))); }
}  // namespace

// 0x00330fe8 CKHkS08Hero_ActState2_HurtReaction: the hurt reaction. Enter: the combo ended, +0xec8 bit 7, +0x354 bit 11,
// +0xec4 bits 8, 9 and 11 set, +0xec8 bits 3 / 4 cleared, +0x1acb at 0; with a chance of +0xda0 percent a hurt voice
// (0x47..0x49). Tick: the facing (+0x11cc, +0xec8 bit 7) away from the hit: a golem's hit (+0x1ae8 1) while the knock
// timer +0x1af8 is within +0xda4, or within +0xda8 at a speed +0x12d0 of +0xdac or more (else +0x1ac4 cleared), along
// the move (+0x12a0) or the back of the facing (+0x127c) flattened on Y; another hit along the move when the hero
// moves, else from the hit origin (+0xf8; the back of the facing at the zero vector); the end of any hurt animation
// (0xc5..0xc7) clears +0x1ac4. Leave: the targets and the hit origin cleared, +0x1a84 at 0, the flags back.
uint8_t CKHkS08Hero::ActHurtReaction(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x27a8 -> 0x00c50d64
    if (phase == 1) {
        SetComboActive(0, 0xff);  // 0x0032d9b0
        m_unkec8 = (m_unkec8 & ~0x80u) | 0x80u;
        m_unk354 = (m_unk354 & ~0x800u) | 0x800u;
        m_unkec4 |= 0xb00u;
        m_unkec8 &= ~0x18u;
        m_unk1acb = 0;
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        if ((r * 100u) >> 16 < static_cast<uint32_t>(m_unkda0)) {        // cmplw
            const uint32_t s = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            PlaySoundIfIdle(1.0f, 1.0f, static_cast<uint8_t>(((s * 3u) >> 16) + 0x47), 0, 0);  // 0x00333fc8, TOC +0x2788
        }
        return other;
    }
    if (phase != 0) {
        m_unk124 = nullptr;
        m_unk12c = nullptr;
        m_unkf8 = zero.x;
        m_unk100 = zero.z;
        m_unkfc = zero.y;
        m_unk1a84 = 0;
        m_unk354 &= ~0x800u;
        m_unkec4 &= ~0xb00u;
        m_unkec8 = (m_unkec8 & ~0x188u) | 0x18u;
        return other;
    }
    const float limit = 0.01f;  // TOC +0x27ac
    if (m_unk1ae8 == 1) {
        const float timer = AsF32(m_unk1af8);
        if (!(m_unkda4 >= timer) && (m_unkda8 < timer || m_unk12d0 < m_unkdac)) {
            m_unk1ac4 = 0;
            return other;
        }
        CVector3 away;
        if (HurtSpeed(HurtRecordVector(m_ui8Hero)) > limit) {
            away = CVector3{m_unk12a0, m_unk12a4, m_unk12a8};
        } else {
            away = CVector3{-m_unk127c, -m_unk1280, -m_unk1284};
        }
        static const CVector3 kUp{0.0f, 1.0f, 0.0f};  // TOC +0x27b0 -> 0x00c50d40
        CVector3 flat = Vec3_ProjectOnPlane(&kUp, &away);  // 0x005840d0
        const float length = std::sqrt(ppc::fmadds(flat.z, flat.z, ppc::fmadds(flat.x, flat.x, flat.y * flat.y)));
        if (length == 0.0f) return other;
        const float k = 1.0f / length;
        flat.z = flat.z * k;
        flat.x = flat.x * k;
        flat.y = flat.y * k;
        if (length <= 0.0f) return other;
        m_unkec8 = (m_unkec8 & ~0x80u) | 0x80u;
        m_unk11cc = flat.x;
        m_unk11d4 = flat.z;
        m_unk11d0 = flat.y;
        return other;
    }
    float dx, dy, dz;
    if (HurtSpeed(HurtRecordVector(m_ui8Hero)) <= limit) {
        if (zero.x == m_unkf8 && m_unkfc == zero.y && m_unk100 == zero.z) {
            dx = -m_unk127c;
            dz = -m_unk1284;
            dy = -m_unk1280;
        } else {
            dx = m_unkf8 - m_unk54c;
            dz = m_unk100 - m_unk554;
            dy = m_unkfc - m_unk550;
        }
    } else {
        dx = m_unk12a0;
        dz = m_unk12a8;
        dy = m_unk12a4;
    }
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
    if (length != 0.0f && !(length <= 0.0f)) {
        const float k = 1.0f / length;
        m_unkec8 = (m_unkec8 & ~0x80u) | 0x80u;
        m_unk11cc = dx * k;
        m_unk11d4 = dz * k;
        m_unk11d0 = dy * k;
    }
    if (IsAnimFinished(0xc5) != 0 || IsAnimFinished(0xc6) != 0 || IsAnimFinished(0xc7) != 0) m_unk1ac4 = 0;  // 0x003013c8
    return other;
}

// 0x0032e0f0 CKHkS08Hero_GrantKillUpgradeBonus_maybe: Cynder (hero 1) with +0xed0 bit 18 earns +0xe9c upgrade points
// per kill (CKS08GameManager_AddDragonUpgradePoints_2_maybe 0x5008c8, a tail call of AddDragonUpgradePoints).
void CKHkS08Hero::GrantKillUpgradeBonus(IKSerializable* /*enemy*/) {
    if (m_ui8Hero != 1 || (m_unked0 & 0x40000u) == 0) return;
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->AddDragonUpgradePoints(1, static_cast<uint32_t>(m_unke9c));
}

// 0x002d4cb8 CKGrpS08Hero_OnEnemyKilled_maybe
void CKGrpS08Hero::OnEnemyKilled(IKSerializable* enemy) {
    CKHkS08Hero* second = static_cast<CKHkS08Hero*>(m_apHeros[1]);
    static_cast<CKHkS08Hero*>(m_apHeros[0])->GrantKillUpgradeBonus(enemy);
    second->GrantKillUpgradeBonus(enemy);
}

// 0x00332078 CKHkS08Hero_ActState7_GroundGrabComboKind1: the grab combo (kind 1). Enter: the time scale owned (1), +0x1ac8
// set, the node from the kind 1 root (+0x1a90) by code 7: combo on, or every kind off; the code cleared. Leave: the combo
// off unless idle or a launch (+0x1abe), the time scale restored when owned, +0x364 bit 24 and +0xec4 bits 12 / 27
// cleared, +0x1ab6 set. Tick (while a combo kind is on, the held target held where it is): the release timer +0x1af4
// (the target's attack spheres on once it runs out while connected, +0x1ad0). Not connected (+0x1ac9) or already on
// (+0x1ac8): the grab animation 0xb2 tries the grab while it plays; at its end the recovery delay, then a miss ends the
// combo (the target's volume group 1 back, +0x1acb), a grab goes on with the blow's link (its sound). Connected: at the
// blow's end (0xb6: the queued code 2) the next node; link 3 starts the throw combo of kind 5 (+0x1aa0, code 7 twice);
// no next node breaks or throws the grab; while the blow plays a throw blow throws once the throw timer +0x1af0 runs
// out or the target's animation ends (0xb5: sound 0x60).
uint8_t CKHkS08Hero::ActGroundGrabCombo(IKTime* clock, int32_t phase, uint8_t other) {
    auto playBlowSound = [this]() {
        const int32_t sound = kBlowSounds[static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId() - 0x91];
        const float pitch = ComputeSoundPitchFromAnimSpeed(GetComboAnimSpeed());  // 0x00333688, 0x0032bee8
        PlaySound(1.0f, pitch, static_cast<uint32_t>(sound), 0);                 // 0x00334188, TOC +0x2788
    };
    if (phase == 1) {
        if (m_unk1acd == 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x277c -> +0x48 -> +0x10
            m_unk1acd = 1;
            m_unk1ace = 1;
        }
        m_unk1ac8 = 1;
        CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a90)->GetNext(7);  // vt+0x68
        m_unk1a88 = next;
        if (next != nullptr && next->GetBlow() != nullptr) {
            SetComboActive(1, 1);  // 0x0032d9b0
        } else {
            SetComboActive(0, 0xff);
        }
        m_unk1a84 = 0;
        return other;
    }
    if (phase != 0) {
        if (m_unk1a88 != m_unk1a8c && m_unk1abe == 0) SetComboActive(0, 0xff);
        if (m_unk1ace != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;
            m_unk1ace = 0;
            m_unk1acd = 0;
        }
        m_unk364 &= ~0x01000000u;
        m_unkec4 &= 0xf7ffefffu;
        m_unk1ab6 = 1;
        return other;
    }
    if (IsAnyComboKindActive() == 0) return other;  // 0x002fd030
    if (m_unk1acc != 0 && m_unk124 != nullptr) {
        CKHkS08Enemy* held = static_cast<CKHkS08Enemy*>(m_unk124);
        if (held->CanBeHeldAtPosition() == 0 || held->GetGrabbingHero() != this) {  // 0x00289b38
            SetComboActive(0, 1);
            return other;
        }
    }
    const float release = m_unk1af4;
    if (release != -10.0f) {  // TOC +0x2790
        if (m_unk1ac9 != 0 && m_unk1ad0 == 0 && release <= 0.0f) {  // cror lt / eq
            m_unk1ad0 = 1;
            if (m_unk124 != nullptr) static_cast<CKHkS08Enemy*>(m_unk124)->SetAttackSpheresActive(1, nullptr);  // 0x00288e08
        } else if (release > 0.0f) {
            m_unk1af4 = release - clock->m_afDeltaTime[0];
        }
    }
    const uint8_t connected = m_unk1ac9;
    const uint8_t on = m_unk1ac8;
    if (connected == 0 || on != 0) {
        if (IsAnimFinished(0xb2) == 0) {  // 0x003013c8
            if (m_unk1ac9 != 0) return other;
            if (IsGrabTargetInRange() != 0) TryGrabTarget();  // 0x002fd5b0, 0x002fff48
            return other;
        }
        CKS08HeroBlow* blow = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow();
        m_unk1aec = blow->GetRecoveryDelay();  // vt+0x7c
        m_unk1a84 = 0;
        m_unk1ac7 = 0;
        if (m_unk1ac9 == 0) {
            m_unk1acb = 1;
            if (m_unk124 != nullptr) static_cast<CKHkS08Enemy*>(m_unk124)->EnableVolumeGroup(1);  // vt+0xf8
            SetComboActive(0, 1);
            return other;
        }
        m_unk1ac8 = 0;
        const uint8_t link = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetLinkCode();  // vt+0x58
        CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetNext(link);          // vt+0x68
        m_unk1a88 = next;
        if (next == nullptr || next->GetBlow() == nullptr) {
            SetComboActive(0, 1);
            return other;
        }
        playBlowSound();
        m_unk1aec = -1.0f;  // TOC +0x276c
        return other;
    }
    const uint16_t anim =
        static_cast<uint16_t>(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId());  // vt+0x8c
    if (IsAnimFinished(anim) == 0) {
        if (m_unk1acc != 0) {
            CKHkS08Enemy* held = static_cast<CKHkS08Enemy*>(m_unk124);
            CKS08HeroBlow* blow = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow();
            if (blow->ShouldThrowOnTimeout() != 0) {  // vt+0xa0
                if (m_unk1af0 < 0.0f) {
                    ThrowGrabbedEnemy(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow());  // 0x00300010
                } else if (held->IsAnimEndReached(clock->m_afDeltaTime[0], 0, 0)) {  // 0x002893e8 -> 0x00285558
                    ThrowGrabbedEnemy(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow());
                    if (static_cast<uint16_t>(m_unk160) == 0xb5) PlaySound(1.0f, 1.0f, 0x60, 0);
                }
            }
        }
        m_unk1af0 = m_unk1af0 - clock->m_afDeltaTime[0];
        return other;
    }
    if (static_cast<uint16_t>(m_unk160) == 0xb6) m_unk1a84 = 2;
    CKS08HeroBlow* finished = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow();
    AdvanceCombo();  // 0x0032d890
    if (finished->GetLinkCode() == 3) {
        m_unk1abd = on;
        m_unk1abe = 1;
        m_unk1ac3 = 1;
        CKS08HeroCombo* throwRoot = static_cast<CKS08HeroCombo*>(m_unk1aa0)->GetNext(7);
        m_unk1a88 = throwRoot;
        if (throwRoot == nullptr) return other;
        CKS08HeroCombo* next = throwRoot->GetNext(7);
        m_unk1ac8 = on;
        m_unk1a88 = next;
        if (next == nullptr || next->GetBlow() == nullptr) {
            SetComboActive(0, 0xff);
            return other;
        }
        m_unk1aec = -1.0f;
        playBlowSound();
        return other;
    }
    CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a88);
    if (next != nullptr && next->GetBlow() != nullptr) {
        SetComboActive(1, 1);
        m_unk1aec = -1.0f;
        m_unk1aca = 1;
        m_unk1ac8 = on;
        return other;
    }
    if (m_unk1aca == 0) {
        if (m_unk124 == nullptr) {
            SetComboActive(0, 1);
            return other;
        }
        BreakGrabAndRecoil();  // 0x002fce90
        if (m_unk1aca == 0) {
            SetComboActive(0, 1);
            return other;
        }
    }
    if (m_unk1acc != 0) ThrowGrabbedEnemy(finished);  // 0x00300010
    SetComboActive(0, 1);
    return other;
}

// 0x00331540 CKHkS08Hero_ActState6_GrabDashComboKind5: the grab dash combo (kind 5). Enter: the time scale owned (1) when
// not yet; a pending launch (+0x1abe) arms the air hold (+0xec4 bit 0x1000, +0x1444 / +0x11d8 from +0x8a8 / +0x8a0 with
// +0xec8 bits 0x20000 / 0x100) and clears +0x1abe; else +0x1ac8 set and the node from the kind 5 root (+0x1aa0) by code
// 7: combo on (kind 5, the air hold armed, a flying hero to the ground), or every kind off (kind 3); the code cleared.
// Leave: the combo reset to the kind 0 root (+0x1a8c) unless the override animation (+0x1ab2) is 0xbd / 0xbe, the time
// scale restored when owned, +0x364 bit 24, +0xec4 bit 12 and +0xec8 bits 0x20000 / 0x100 cleared, the impulse record
// (+0x1d5c) reset. Tick (while a combo kind is on and a held target is still held there): the release timer +0x1af4;
// not connected (+0x1ac9) or a grab blow (+0x1ac8): while the blow plays the grab is tried, at its end the recovery
// delay, then a miss ends the combo (the target's volume group 1 back, +0x1acb), a grab goes on with the blow's link
// (the impulse record up 300 / height above the ground, at most 200, for 0.1 s; its sound). Connected: while the blow
// plays a throw blow throws once the throw timer +0x1af0 runs out or the target's animation ends; at its end the
// queued code's node (combo on, +0x1aca, on the ground, its animation as the override) or the grab broken / thrown.
uint8_t CKHkS08Hero::ActGrabDashCombo(IKTime* clock, int32_t phase, uint8_t other) {
    const CVector3& zero = kHeroZeroVector;              // TOC +0x27a8 -> 0x00c50d64
    static const CVector3 kAxisYShared = {0.0f, 1.0f, 0.0f};  // TOC +0x27b0 -> 0x00c50d40 (filled at start-up)
    if (phase == 1) {
        bool launch;
        if (m_unk1acd == 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x277c -> +0x48 -> +0x10
            launch = m_unk1abe != 0;
            m_unk1acd = 1;
            m_unk1ace = 1;
        } else {
            launch = m_unk1abe != 0;
        }
        if (launch) {
            m_unkec4 = (m_unkec4 & ~0x1000u) | 0x1000u;
            std::memcpy(&m_unk1444, &m_unk8a8, sizeof m_unk1444);
            m_unkec8 = (m_unkec8 & ~0x20000u) | 0x20000u;
            std::memcpy(&m_unk11d8, &m_unk8a0, sizeof m_unk11d8);
            m_unkec8 = (m_unkec8 & ~0x100u) | 0x100u;
            m_unk1abe = 0;
        } else {
            m_unk1ac8 = 1;
            CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1aa0)->GetNext(7);  // vt+0x68
            m_unk1a88 = next;
            if (next == nullptr || next->GetBlow() == nullptr) {
                SetComboActive(0, 3);  // 0x0032d9b0
            } else {
                SetComboActive(1, 5);
                std::memcpy(&m_unk1444, &m_unk8a8, sizeof m_unk1444);
                m_unkec8 = (m_unkec8 & ~0x20000u) | 0x20000u;
                std::memcpy(&m_unk11d8, &m_unk8a0, sizeof m_unk11d8);
                m_unkec8 = (m_unkec8 & ~0x100u) | 0x100u;
                if (GetMovementMode() == 1) SetMovementMode(0);  // 0x003401b8, 0x00340c18
            }
        }
        m_unk1a84 = 0;
        return other;
    }
    if (phase != 0) {
        if (static_cast<uint16_t>(m_unk1ab2 - 0xbd) > 1u) {
            IKSerializable* root = m_unk1a8c;
            if (m_unk1a88 != root) {
                SetComboActive(0, 0xff);
                root = m_unk1a8c;
            }
            m_unk1a88 = root;
        }
        if (m_unk1ace != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x2788
            m_unk1ace = 0;
            m_unk1acd = 0;
        }
        m_unk364 &= ~0x01000000u;
        m_unkec4 &= ~0x1000u;
        m_unkec8 &= 0xfffdfeffu;
        m_unk1d5c = 1.0f;
        m_unk1d60 = 0;
        m_unk1d68 = zero.x;
        m_unk1d70 = zero.z;
        m_unk1d6c = zero.y;
        m_unk1d78 = 0;
        m_unk1d64 = 0;
        m_unk1d74 = 0;
        return other;
    }
    if (IsAnyComboKindActive() == 0) return other;  // 0x002fd030
    if (m_unk1acc != 0 && m_unk124 != nullptr) {
        CKHkS08Enemy* held = static_cast<CKHkS08Enemy*>(m_unk124);
        if (held->CanBeHeldAtPosition() == 0 || held->GetGrabbingHero() != this) {  // 0x00289b38
            SetComboActive(0, 5);
            return other;
        }
    }
    const float dt = clock->m_afDeltaTime[0];
    const float release = m_unk1af4;
    if (release != -10.0f) {  // TOC +0x2790
        if (m_unk1ac9 != 0 && m_unk1ad0 == 0 && !(0.0f < release)) {
            m_unk1ad0 = 1;
            if (m_unk124 != nullptr) static_cast<CKHkS08Enemy*>(m_unk124)->SetAttackSpheresActive(1, nullptr);  // 0x00288e08
        } else if (0.0f < release) {
            m_unk1af4 = release - dt;
        }
    }
    if (static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow() == nullptr) SetComboActive(0, 5);  // vt+0x54
    if (m_unk1ac9 == 0 || m_unk1ac8 != 0) {
        const uint16_t anim = static_cast<uint16_t>(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId());  // vt+0x8c
        if (IsAnimFinished(anim) == 0) {  // 0x003013c8
            if (m_unk1ac9 == 0 && IsGrabTargetInRange() != 0) TryGrabTarget();  // 0x002fd5b0, 0x002fff48
            return other;
        }
        m_unk1aec = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetRecoveryDelay();  // vt+0x7c
        m_unk1a84 = 0;
        m_unk1ac7 = 0;
        if (m_unk1ac9 == 0) {
            m_unk1acb = 1;
            if (m_unk124 != nullptr) static_cast<CKHkS08Enemy*>(m_unk124)->EnableVolumeGroup(1);  // vt+0xf8
        } else {
            m_unk1ac8 = 0;
            const uint8_t link = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetLinkCode();  // vt+0x58
            CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetNext(link);          // vt+0x68
            m_unk1a88 = next;
            if (next != nullptr && next->GetBlow() != nullptr) {
                // The lift: an impulse record up (the shared y axis) of 300 / the height above the ground (TOC +0x2784),
                // at most 200 (+0x27d0), for 0.1 s (+0x27b8).
                const float ratio = 300.0f / GetHeightAboveGround();  // 0x0032a008
                float lift = 0.0f;                                    // TOC +0x279c
                if (0.0f < ratio) lift = 200.0f <= ratio ? 200.0f : ratio;
                m_unk1d68 = zero.x;
                m_unk1d5c = lift;
                const float hold = 0.1f;  // TOC +0x27b8
                std::memcpy(&m_unk1d60, &hold, 4);
                m_unk1d70 = zero.z;
                m_unk1d6c = zero.y;
                m_unk1d74 = 0;
                m_unk1d78 = 0;
                m_unk1d64 = 0;
                m_unk1d68 = kAxisYShared.x;
                m_unk1d6c = kAxisYShared.y;
                m_unk1d70 = kAxisYShared.z;
                m_unk1d78 = 0;
                m_unk1d74 = m_unk1d60;
                m_unk1d64 = 1;
                std::memcpy(&m_unk1444, &m_unk8a8, sizeof m_unk1444);
                m_unkec8 = (m_unkec8 & ~0x20000u) | 0x20000u;
                const int32_t sound = kBlowSounds[next->GetBlow()->GetAnimId() - 0x91];  // TOC +0x278c
                const float pitch = ComputeSoundPitchFromAnimSpeed(GetComboAnimSpeed());  // 0x00333688, 0x0032bee8
                PlaySound(1.0f, pitch, static_cast<uint32_t>(sound), 0);                 // 0x00334188, TOC +0x2788
                m_unk1aec = -1.0f;  // TOC +0x276c
                return other;
            }
        }
        SetComboActive(0, 5);
        return other;
    }
    const uint16_t anim = static_cast<uint16_t>(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId());
    if (IsAnimFinished(anim) == 0) {
        if (m_unk1acc != 0 && static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->ShouldThrowOnTimeout() != 0) {  // vt+0xa0
            // The original passes the anim-end test (0x002893e8 -> 0x00285558) a layer left over in r4 from the call
            // before; 0 as in ActGroundGrabCombo.
            if (m_unk1af0 < 0.0f || static_cast<CKHkS08Enemy*>(m_unk124)->IsAnimEndReached(dt, 0, 0)) {
                ThrowGrabbedEnemy(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow());  // 0x00300010
            }
        }
        m_unk1af0 = m_unk1af0 - dt;
        return other;
    }
    m_unk1aec = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetRecoveryDelay();
    m_unk1ac7 = 0;
    CKS08HeroBlow* finished = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow();
    CKS08HeroCombo* next = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetNext(static_cast<uint8_t>(m_unk1a84));
    m_unk1a84 = 0;
    m_unk1a88 = next;
    if (next != nullptr && next->GetBlow() != nullptr) {
        SetComboActive(1, 5);
        m_unk1aca = 1;
        SetMovementMode(0);
        m_unk1ab2 = static_cast<uint16_t>(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetAnimId());
        m_unk1aec = -1.0f;
        m_unk1ac8 = 0;
        m_unkec8 &= 0xffffffe7u;
        return other;
    }
    if (m_unk1aca != 0 || (m_unk124 != nullptr && (BreakGrabAndRecoil(), m_unk1aca != 0))) {  // 0x002fce90
        if (m_unk1acc != 0) ThrowGrabbedEnemy(finished);
    }
    SetComboActive(0, 5);
    return other;
}

// 0x002fc6e0 CKHkS08Hero_IsTargetEnemyOnGround_maybe: no grab target counts as on the ground.
uint8_t CKHkS08Hero::IsTargetEnemyOnGround() {
    if (m_unk124 == nullptr) return 1;
    return static_cast<CKHkS08Enemy*>(m_unk124)->IsOnGround();  // 0x00289a98
}

// 0x002fc720 CKHkS08Hero_ReleaseGrabbedEnemyWithDamage: the grab target let go (not held, no grabber) and hurt by the
// blow's damage (vt+0xb0) along the hero's facing (+0x12a0); no longer holding.
void CKHkS08Hero::ReleaseGrabbedEnemyWithDamage(CKS08HeroBlow* blow) {
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_unk124);
    if (enemy == nullptr) return;
    enemy->SetHeldFlag(0);       // 0x00289f08
    enemy->ClearGrabber(this);   // 0x00288c98
    IKSerializable* damage = reinterpret_cast<IKSerializable*>(blow->GetDamage());  // vt+0xb0
    const CVector3 along = {m_unk12a0, m_unk12a4, m_unk12a8};
    enemy->ApplyThrowImpactDamage(damage, &along);  // 0x0028ac90
    m_unk1acc = 0;
}

// 0x00332a70 CKHkS08Hero_ActState5_GrabSlamSeq_maybe: the grab slam, a sequence of override animations (+0x1ab2).
// Enter: the time scale owned (1), the vertical speed +0x1b18 from +0x8a4, the air hold armed (+0xec4 bit 0x1000,
// +0x1444 / +0x11d8 from +0x8a8 / +0x8a0 with +0xec8 bits 0x20000 / 0x100), +0x1abf set. Leave: the combo reset unless
// at the kind 0 root, the vertical speed back to +0x8a4, the time scale restored when owned, the override animation
// cleared, the flags cleared. Tick (while a combo kind is on and a held target still held there): the release timer
// +0x1af4; an animation at its end steps the sequence (0xbd -> 0xc1 with sound 0x5b, the vertical speed 0, +0xec4 bit
// 27, +0x1b04 1 and a held target released with the blow's damage; 0xbe -> 0xc2 with 0x5c and bit 27; 0xc1 / 0xc2 play
// again; 0xc3 / 0xc4 end the combo). Else 0xc1 / 0xc2 rise (the vertical speed grows by +0x8b0 per second) until the
// hero is too far from its partner for the group (+0x108 / +0x10c x +0x154 / 2, its +0x314 / +0x318 distance; or +0xec4
// bit 22 without being too far, or bit 18), which drops the target and ends the combo; on the ground (+0x1511 clear)
// they land into 0xc3 (sound 0x5d, a shockwave at +0x570) / 0xc4 (sound 0x5e); 0xc1 waits for a target on the ground
// or +0x1b04 to run out. 0xbd releases the held target at its animation's end, 0xc4 throws it.
uint8_t CKHkS08Hero::ActGrabSlamSeq(IKTime* clock, int32_t phase, uint8_t other) {
    auto playSound = [this](uint32_t sound) {
        const float pitch = ComputeSoundPitchFromAnimSpeed(GetComboAnimSpeed());  // 0x00333688, 0x0032bee8
        PlaySound(1.0f, pitch, sound, 0);                                         // 0x00334188, TOC +0x2788
    };
    if (phase == 1) {
        if (m_unk1acd == 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x277c -> +0x48 -> +0x10
            m_unk1acd = 1;
            m_unk1ace = 1;
        }
        m_unk1b18 = m_unk8a4;
        m_unkec4 = (m_unkec4 & ~0x1000u) | 0x1000u;
        std::memcpy(&m_unk1444, &m_unk8a8, sizeof m_unk1444);
        m_unkec8 = (m_unkec8 & ~0x20000u) | 0x20000u;
        std::memcpy(&m_unk11d8, &m_unk8a0, sizeof m_unk11d8);
        m_unkec8 = m_unkec8 | 0x100u;
        m_unk1abf = 1;
        return other;
    }
    if (phase != 0) {
        if (m_unk1a88 != m_unk1a8c) SetComboActive(0, 0xff);  // 0x0032d9b0
        float vertical = m_unk8a4;
        m_unk1b18 = vertical;
        if (m_unk1ace != 0) {
            g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x2788
            vertical = m_unk8a4;
            m_unk1ace = 0;
            m_unk1acd = 0;
        }
        m_unk1b18 = vertical;
        m_unk1ab2 = 0;
        m_unkec4 &= 0xf7ffffffu;
        m_unkec8 &= 0xfffdffffu;
        m_unkec4 &= 0xffffefffu;
        m_unk364 &= 0xfeffffffu;
        m_unkec8 &= 0xfffffeffu;
        return other;
    }
    if (IsAnyComboKindActive() == 0) return other;  // 0x002fd030
    if (m_unk1acc != 0 && m_unk124 != nullptr) {
        CKHkS08Enemy* held = static_cast<CKHkS08Enemy*>(m_unk124);
        if (held->CanBeHeldAtPosition() == 0 || held->GetGrabbingHero() != this) {  // 0x00289b38
            SetComboActive(0, 5);
            return other;
        }
    }
    const float dt = clock->m_afDeltaTime[0];
    const float release = m_unk1af4;
    if (release != -10.0f) {  // TOC +0x2790
        if (m_unk1ac9 != 0 && m_unk1ad0 == 0 && !(0.0f < release)) {
            m_unk1ad0 = 1;
            if (m_unk124 != nullptr) static_cast<CKHkS08Enemy*>(m_unk124)->SetAttackSpheresActive(1, nullptr);  // 0x00288e08
        } else if (0.0f < release) {
            m_unk1af4 = release - dt;
        }
    }
    const uint16_t anim = m_unk1ab2;
    if (IsAnimFinished(anim) != 0) {  // 0x003013c8; the jump table at TOC +0x27d4 (0xbd..0xc4)
        switch (anim) {
            case 0xbd:
                m_unk1ab2 = 0xc1;
                playSound(0x5b);
                m_unk1b18 = 0.0f;
                m_unkec4 = (m_unkec4 & ~0x08000000u) | 0x08000000u;
                m_unk1b04 = 1.0f;
                if (m_unk1acc != 0) ReleaseGrabbedEnemyWithDamage(static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow());  // 0x002fc720
                return other;
            case 0xbe:
                m_unk1ab2 = 0xc2;
                playSound(0x5c);
                m_unkec4 = (m_unkec4 & ~0x08000000u) | 0x08000000u;
                return other;
            case 0xc1:
                m_unk1ab2 = 0xc1;
                playSound(0x5b);
                return other;
            case 0xc2:
                m_unk1ab2 = 0xc2;
                playSound(0x5c);
                return other;
            case 0xc3:
            case 0xc4:
                AdvanceCombo();  // 0x0032d890
                SetComboActive(0, 5);
                return other;
            default:
                return other;
        }
    }
    if (anim == 0xbd || anim == 0xc4) {
        if (m_unk1acc != 0 && static_cast<CKHkS08Enemy*>(m_unk124)->IsAnimEndReached(dt, 0, 0)) {  // 0x002893e8 -> 0x00285558
            CKS08HeroBlow* blow = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow();
            if (anim == 0xbd) {
                ReleaseGrabbedEnemyWithDamage(blow);
            } else {
                ThrowGrabbedEnemy(blow);  // 0x00300010
            }
        }
        return other;
    }
    if (anim != 0xc1 && anim != 0xc2) return other;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const float distance = group->m_unk108;  // 0x002ce518 GetMaxPartnerDistance
    if (m_unk1511 == 0) {
        if (anim == 0xc1) {
            m_unk1ab2 = 0xc3;
            playSound(0x5d);
            const CVector3 at = {m_unk570, m_unk574, m_unk578};
            SpawnShockwave(1, &at);  // 0x0033c688
        } else {
            m_unk1ab2 = 0xc4;
            playSound(0x5e);
        }
        return other;
    }
    float partner = 0.0f;  // TOC +0x279c
    if (m_ui8Hero == 0) {
        std::memcpy(&partner, &group->m_unk2d4[16], 4);  // +0x314
    } else if (m_ui8Hero == 1) {
        std::memcpy(&partner, &group->m_unk318, 4);      // +0x318
    }
    const float limit = (distance / group->m_unk10c) * (group->m_unk154 * 0.5f);  // TOC +0x27bc
    bool drop;
    if (partner < limit) {
        drop = (m_unkec4 & 0x40000u) != 0;
    } else {
        drop = (m_unkec4 & 0x400000u) == 0 || (m_unkec4 & 0x40000u) != 0;
    }
    if (drop) {
        m_unk1aec = static_cast<CKS08HeroCombo*>(m_unk1a88)->GetBlow()->GetRecoveryDelay();  // vt+0x7c
        DropGrabbedEnemy();  // 0x002fc600
        SetComboActive(0, 5);
        return other;
    }
    if (anim == 0xc1 && IsTargetEnemyOnGround() == 0 && 0.0f < m_unk1b04) return other;  // 0x002fc6e0
    m_unk1b18 = ppc::fmadds(dt, m_unk8b0, m_unk1b18);
    return other;
}

// 0x0032f268 CKHkS08Hero_ActState3_Recovery_maybe: the recovery after a hurt. Enter: no combo (SetComboActive(0, 0xff)),
// +0x354 bit 0x800, +0xec4 bits 0x1000 / 0x200 / 0x100 / 0x800, +0xec8 bits 0x400000 / 0x800000; higher than 0.1 above
// the ground also +0x1444 = +0x8a8 with +0xec8 bit 0x20000 and +0x11d8 = +0x8a0 with bit 0x100. Tick: either recovery
// animation (0xca, 0xcb) finished clears +0x1acb. Leave: the grab target, +0x12c and +0x1a84 cleared, the flags cleared.
uint8_t CKHkS08Hero::ActRecovery(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 0) {
        if (IsAnimFinished(0xca) != 0 || IsAnimFinished(0xcb) != 0) m_unk1acb = 0;  // 0x003013c8
        return other;
    }
    if (phase == 1) {
        SetComboActive(0, 0xff);  // 0x0032d9b0
        m_unk354 = (m_unk354 & ~0x800u) | 0x800u;
        m_unkec4 = (m_unkec4 & ~0x1000u) | 0x1000u;
        m_unkec4 = (m_unkec4 & ~0x200u) | 0x200u;
        m_unkec4 = (m_unkec4 & ~0x100u) | 0x100u;
        m_unkec4 = (m_unkec4 & ~0x800u) | 0x800u;
        m_unkec8 = (m_unkec8 & ~0x400000u) | 0x400000u;
        m_unkec8 = (m_unkec8 & ~0x800000u) | 0x800000u;
        if (GetHeightAboveGround() > 0.1f) {  // 0x0032a008, TOC +0x27b8
            std::memcpy(&m_unk1444, &m_unk8a8, sizeof m_unk1444);
            m_unkec8 = (m_unkec8 & ~0x20000u) | 0x20000u;
            std::memcpy(&m_unk11d8, &m_unk8a0, sizeof m_unk11d8);
            m_unkec8 = (m_unkec8 & ~0x100u) | 0x100u;
        }
        return other;
    }
    m_unk124 = nullptr;
    m_unk12c = nullptr;
    m_unk1a84 = 0;
    m_unk354 &= ~0x800u;
    m_unkec4 &= 0xffffe4ffu;
    m_unkec8 &= 0xff3cfeffu;
    m_unk1acb = 0;
    return other;
}

// 0x003332c0 CKHkS08Hero_ActState0_Dead: enter sets +0xec8 bit 27 and the death timer +0x1160 to 1.5 (enter and leave
// answer 0). The tick (+0x1629 set while climbing): on a ground of property 0x200, more than 10 above the ground or with
// the timer run out, the game manager's death sequence of mode 2 (the hero sinks), else on the ground (not +0x354 bit 0)
// mode 1; either only when the game is not in the hero death state already (vt+0x26c), after the group's requested
// dragon is put back to the selected one, its +0xf8 bit 1 set and bit 5 cleared and the attached object left. Every tick
// sets +0xec4 bits 10..13, 21 and 22, +0x354 bit 11 and +0xec8 bits 22, 23 and 29.
uint8_t CKHkS08Hero::ActDead(IKTime*, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_unkec8 = (m_unkec8 & ~0x08000000u) | 0x08000000u;
        m_unk1160 = 1.5f;  // TOC +0x27e8
        return 0;
    }
    if (phase != 0) return 0;
    if (IsClimbingMovementMode2() != 0) m_unk1629 = 1;  // 0x003401a0
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    uint8_t mode = 0;
    if ((ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) || GetHeightAboveGround() > 10.0f ||
        !(m_unk1160 > 0.0f)) {  // TOC +0x27e4 / +0x279c; bgt / ble
        mode = 2;
    } else if ((m_unk354 & 1u) == 0) {
        mode = 1;
    }
    if (mode != 0) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x277c
        if (manager->m_gameState.m_ui8Current != 9) {  // vt+0x26c
            CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
            group->m_unk65 = group->m_unk64;
            group->m_unkf8 = (group->m_unkf8 & 0xffffffddu) | 2u;
            LeaveAttachedObject();                        // 0x00344e88
            manager->StartDeathSequence(mode, m_ui8Hero);  // vt+0x25c 0x004f8750
        }
    }
    m_unkec4 |= 0x400000u;
    m_unkec4 |= 0x200000u;
    m_unkec4 |= 0x800u;
    m_unkec4 |= 0x400u;
    m_unkec4 |= 0x2000u;
    m_unkec4 |= 0x1000u;
    m_unk354 |= 0x800u;
    m_unkec8 |= 0x400000u;
    m_unkec8 |= 0x800000u;
    m_unkec8 |= 0x20000000u;
    return other;
}

// 0x0032d578 StaticInitAndDestruction_32d578: two file statics (0x00ceae5c, 0x00ceae60) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae5c = -1.0f;
[[maybe_unused]] float s_unkceae60 = -1.0f;
}  // namespace
