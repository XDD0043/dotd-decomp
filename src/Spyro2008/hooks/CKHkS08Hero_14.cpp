// Reconstructed original translation unit: 0x32d578-0x333618 (GAME_TOC1, main_toc1), 33 functions, 32 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x32d578  StaticInitAndDestruction_32d578
//   [ ] 0x32d5a8  _GLOBAL__I_32d5a8
//   [ ] 0x32d5b8  _GLOBAL__D_32d5b8
//   [ ] 0x32d5c8  FUN_0032d5c8  [dead]
//   [ ] 0x32d6b0  CKHkS08Hero_TryStartFinisherCamera_maybe
//   [ ] 0x32d890  CKHkS08Hero_AdvanceCombo
//   [ ] 0x32d9b0  CKHkS08Hero_SetComboActive
//   [ ] 0x32df80  CKHkS08Hero_UpdateGrabReleaseTimer
//   [ ] 0x32e028  CKHkS08Hero_ApproachField1108AndNotifyCamera_maybe
//   [ ] 0x32e0f0  CKHkS08Hero_GrantKillUpgradeBonus_maybe
//   [ ] 0x32e158  CKHkS08Hero_ActState11_GroundComboKind0_Condition
//   [ ] 0x32e378  CKHkS08Hero_ActState5_GrabSlamSeq_maybe_Condition
//   [ ] 0x32e3d0  CKHkS08Hero_ActState9_ClimbComboKind4_maybe_Condition
//   [ ] 0x32e488  CKHkS08Hero_ActState8_FlyingComboKind3_Condition
//   [ ] 0x32e668  CKHkS08Hero_ActState10_GroundAltComboKind2_Condition
//   [ ] 0x32e820  CKHkS08Hero_ActState9_ClimbComboKind4_maybe
//   [ ] 0x32eb80  CKHkS08Hero_ActState6_GrabDashComboKind5_Condition
//   [ ] 0x32ecc0  CKHkS08Hero_ActState7_GroundGrabComboKind1_Condition
//   [ ] 0x32edd0  CKHkS08Hero_ApplyGrabbedEnemyMarkDamage
//   [ ] 0x32f048  CKHkS08Hero_InitFlightField1D9CBlock_maybe
//   [ ] 0x32f170  CKHkS08Hero_ActState0_Dead_Condition
//   [ ] 0x32f268  CKHkS08Hero_ActState3_Recovery_maybe
//   [ ] 0x32f470  CKHkS08Hero_ActState8_FlyingComboKind3
//   [ ] 0x32fce0  CKHkS08Hero_ActState10_GroundAltComboKind2
//   [ ] 0x330528  CKHkS08Hero_ActState11_GroundComboKind0
//   [x] 0x330ab8  CKHkS08Hero_QueueAttackInputAndSelectElement
//   [ ] 0x330fe8  CKHkS08Hero_ActState2_HurtReaction
//   [ ] 0x331540  CKHkS08Hero_ActState6_GrabDashComboKind5
//   [ ] 0x332078  CKHkS08Hero_ActState7_GroundGrabComboKind1
//   [ ] 0x332a70  CKHkS08Hero_ActState5_GrabSlamSeq_maybe
//   [ ] 0x3332c0  CKHkS08Hero_ActState0_Dead
//   [ ] 0x333608  CKHkS08Hero_vfE8
//   [ ] 0x333610  CKHkS08Hero_vf114
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Stub.h"

namespace {
// 0x002fc1b0 CKHkS08Hero_IsComboKindFlagSet (local copy; CKHkS08Hero_3.cpp): one of the combo kind bytes +0x1abc /
// +0x1abd / +0x1ac3 / +0x1ac0 / +0x1ac1 / +0x1ac2.
uint8_t IsComboKindFlagSet(const CKHkS08Hero* hero) {
    if (hero->m_unk1abc != 0 || hero->m_unk1abd != 0 || hero->m_unk1ac3 != 0 || hero->m_unk1ac0 != 0 ||
        hero->m_unk1ac1 != 0) {
        return 1;
    }
    return hero->m_unk1ac2;
}

// The combo input window (inlined after each queued code): during a combo a press made before the combo animation's
// last +0xd84 seconds (CKHkS08Hero_GetCurrentAnimTime 0x303368 against Anim_GetDuration 0x7ab60 of the inner blend
// slot's animation over CKHkS08Hero_GetComboAnimSpeed 0x32bee8) is consumed instead. STUB(C2.7: combos): kept queued.
// Only a running combo (a combo kind byte) asks.
bool ComboWindowConsumes(const CKHkS08Hero* hero) {
    if (IsComboKindFlagSet(hero) == 0) return false;
    DOTD_STUB_ONCE("CKHkS08Hero_QueueAttackInputAndSelectElement 0x330ab8: the combo input window (C2.7)");
    return false;
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
        // STUB(C2.7: HUD): ShowSpyroSelectedElementHud 0x5039e8 / ShowCynderSelectedElementHud 0x5024d8 of the game
        // manager with the element.
        DOTD_STUB_ONCE("Show{Spyro,Cynder}SelectedElementHud 0x5039e8 / 0x5024d8 (C2.7)");
    }
}
