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
//   [ ] 0x32bc10  CKHkS08Hero_UpdateComboTimeScale
//   [x] 0x32bed8  CKHkS08Hero_AnimState0_Dead_Condition
//   [ ] 0x32bee8  CKHkS08Hero_GetComboAnimSpeed
//   [ ] 0x32c038  CKHkS08Hero_AdvanceGrabbedEnemyAnimTime_maybe  [dead]
//   [ ] 0x32c078  CKHkS08Hero_SyncGrabbedEnemyAnim_maybe
//   [x] 0x32c130  CKHkS08Hero_AnimState6_Ability_Condition
//   [ ] 0x32c170  CKHkS08Hero_AnimState5_Recovery
//   [ ] 0x32c268  CKHkS08Hero_AnimState1_Fury
//   [ ] 0x32c330  StaticInitAndDestruction_32c330
//   [ ] 0x32c360  _GLOBAL__D_32c360
//   [ ] 0x32c370  _GLOBAL__I_32c370
//   [ ] 0x32c380  CKHkS08Hero_AnimState0_Dead
//   [ ] 0x32c520  CKHkS08Hero_AnimState6_Ability
//   [x] 0x32c5e0  CKHkS08Hero_AnimState3_GuardedHurt_Condition
//   [ ] 0x32c628  CKHkS08Hero_AnimState4_Hurt
//   [ ] 0x32c780  CKHkS08Hero_AnimState3_GuardedHurt
//   [ ] 0x32c950  CKHkS08Hero_AnimState2_HurtType1
//   [ ] 0x32cb98  CKHkS08Hero_AnimState7_ComboAnim
//   [x] 0x32d4b0  CKHkS08Hero_vf100
//   [x] 0x32d4b8  CKHkS08Hero_vfEC
//   [x] 0x32d4c0  CKHkS08Hero_vfF0
//   [x] 0x32d4c8  CKHkS08Hero_ActState2_HurtReaction_Condition
//   [x] 0x32d4d0  CKHkS08Hero_ActState3_Recovery_maybe_Condition
//   [ ] 0x32d4d8  CKHkS08Hero_SetComboKindFlag
#include "Spyro2008/hooks/CKHkS08Hero.h"

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
