// Reconstructed original translation unit: 0x326498-0x32bb30 (GAME_TOC1, main_toc1), 73 functions, 63 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: CopyHeroDerivedVelocity (1), CopyHeroAdjustedPosition (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x326498  CKHkS08Hero_ActState4_Ability_Condition
//   [x] 0x3267e8  CKHkS08Hero_ActState1_FuryCoop_maybe_Condition
//   [ ] 0x326830  CKHkS08Hero_CanStartFury_maybe
//   [ ] 0x326950  CKHkS08Hero_ActState1_FuryCoop_maybe
//   [ ] 0x326ee0  CKHkS08Hero_CancelAbilityA
//   [ ] 0x3272d8  CKHkS08Hero_CancelAbilityB
//   [ ] 0x3276d0  CKHkS08Hero_ActState4_AbilityHandler
//   [ ] 0x328e40  CKHkS08Hero_SetFuryMode_maybe
//   [x] 0x329d88  CKHkS08Hero_SetExternalDisplacementFlag_maybe
//   [ ] 0x329d90  CKHkS08Hero_GetCurrentSpeed_maybe
//   [ ] 0x329d98  CKHkS08Hero_IsComboKind1Active
//   [ ] 0x329da0  CKHkS08Hero_IsComboKind5Active
//   [ ] 0x329da8  FUN_00329da8  [dead]
//   [ ] 0x329de0  CKHkS08Hero_GetActiveHitSpheres
//   [ ] 0x329df8  CKHkS08Hero_GetGrabTarget
//   [ ] 0x329e00  CKHkS08Hero_EnableSubNode_maybe
//   [ ] 0x329e80  CKHkS08Hero_GetSubNode_maybe
//   [ ] 0x329eb8  CKHkS08Hero_GetSubNodeB_maybe
//   [ ] 0x329ef0  CKHkS08Hero_IsHitConfirmed_maybe  [dead]
//   [ ] 0x329f00  CKHkS08Hero_SetHitConfirmed
//   [ ] 0x329f20  CKHkS08Hero_GetCurrentBlowFlag61
//   [ ] 0x32a000  CKHkS08Hero_GetCarrier
//   [x] 0x32a008  CKHkS08Hero_GetHeightAboveGround_maybe
//   [ ] 0x32a010  CKHkS08Hero_IsAttachedToContextualMeca
//   [ ] 0x32a090  CKHkS08Hero_IsCarryingTransportableKey_maybe
//   [ ] 0x32a148  CKHkS08Hero_IsCarryingTransportableWeight_maybe
//   [ ] 0x32a200  CKHkS08Hero_IsCarryingPowerBucket_maybe
//   [ ] 0x32a2b8  CKHkS08Hero_IsCarryingFilledPowerBucket_maybe
//   [ ] 0x32a390  CKHkS08Hero_SetFlagECCBit5_maybe  [dead]
//   [ ] 0x32a3b0  CKHkS08Hero_GetComboTimerMultiplier_maybe
//   [ ] 0x32a3d0  CKHkS08Hero_GetStatusDecayRate_maybe
//   [ ] 0x32a3f0  CKHkS08Hero_IsInFuryMode_maybe  [dead]
//   [ ] 0x32a400  CKHkS08Hero_GetFlagECCBit5_maybe  [dead]
//   [ ] 0x32a410  CKHkS08Hero_SetNearCrumblyZoneFlags_maybe
//   [ ] 0x32a420  CKHkS08Hero_GetNearCrumblyZoneFlag1DD1_maybe
//   [ ] 0x32a428  CKHkS08Hero_GetFlagED4Bit3_maybe
//   [ ] 0x32a438  CKHkS08Hero_SetCarryingObject_maybe
//   [ ] 0x32a458  StaticInitAndDestruction_32a458
//   [ ] 0x32a488  _GLOBAL__I_32a488
//   [ ] 0x32a498  _GLOBAL__D_32a498
//   [ ] 0x32a4a8  CKHkS08Hero_IsMovementMode0_Thunk
//   [ ] 0x32a4d0  CKHkS08Hero_IsFlying_Thunk
//   [ ] 0x32a4f8  CKHkS08Hero_ShouldStayClimbing_Thunk
//   [ ] 0x32a520  CKHkS08Hero_ShouldJoinPartnerFlight_Thunk
//   [ ] 0x32a548  CKHkS08Hero_SetMoveDestination
//   [ ] 0x32a580  CKHkS08Hero_ValidateOrAcquireTargetThunk_maybe
//   [ ] 0x32a5a8  CKHkS08Hero_PlaySoundIfIdleDefaultArgs_maybe  [dead]
//   [ ] 0x32a5e0  CKHkS08Hero_StopSound_Thunk_maybe  [dead]
//   [ ] 0x32a608  CKHkS08Hero_PlaySoundDefault
//   [ ] 0x32a638  CKHkS08Hero_SetExternallyPositionedAndPhysics_maybe
//   [ ] 0x32a698  CKHkS08Hero_IsInCombo
//   [ ] 0x32a6c0  CKHkS08Hero_GetMovementMode_Thunk
//   [x] 0x32a6e8  CKHkS08Hero_SetExternalDisplacement_maybe
//   [ ] 0x32a708  CKHkS08Hero_CopyAimDirection_maybe
//   [x] 0x32a730  CKHkS08Hero_GetPredictedVelocity_maybe
//   [x] 0x32a758  CopyHeroAdjustedPosition
//   [ ] 0x32a7a8  CKHkS08Hero_IsUsingWindBeam
//   [ ] 0x32a840  CKHkS08Hero_GetEarthBoulderFlag2CC_maybe
//   [ ] 0x32a8d0  CKHkS08Hero_GetAbilityElementLevel
//   [ ] 0x32a938  CKHkS08Hero_SetAttackSphere0
//   [ ] 0x32aa28  CKHkS08Hero_SetAttackSphere2
//   [ ] 0x32ab18  CKHkS08Hero_SetAttackSphere1
//   [ ] 0x32ac08  CKHkS08Hero_GetElementColor_maybe
//   [ ] 0x32ac88  CKHkS08Hero_CrossfadeAnimResource_maybe
//   [ ] 0x32ad80  CKHkS08Hero_PlayAnimResource_maybe
//   [x] 0x32aec8  CKHkS08Hero_SetAnimPairAndWeight_maybe
//   [ ] 0x32afc8  CKHkS08Hero_ShareCollectedBonusWithPartner_maybe
//   [ ] 0x32b138  CKHkS08Hero_GetHotspot4AimDir_maybe
//   [ ] 0x32b240  CKHkS08Hero_GetFlagECCBit5_2_maybe  [dead]
//   [ ] 0x32b250  FUN_0032b250  [dead]
//   [ ] 0x32b500  CKHkS08Hero_UpdateMoveTo_maybe
//   [ ] 0x32b9c8  FUN_0032b9c8  [dead]
//   [ ] 0x32ba68  CKHkS08Hero_GetHotspot4FlatDir_maybe
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Stub.h"

// 0x003267e8 CKHkS08Hero_ActState1_FuryCoop_maybe_Condition: the fury flag (+0xed4 bit 6) or a running fury timer
// (+0x1b00; the same test as the animation machine's Fury condition).
uint8_t CKHkS08Hero::ActFuryCoopCondition(IKTime*, uint8_t) {
    if ((m_unked4 & 0x40u) != 0) return 1;
    return !(m_unk1b00 <= 0.0f) ? 1 : 0;  // ble: a NaN timer counts as running
}

// 0x00329d88 CKHkS08Hero_SetExternalDisplacementFlag_maybe: +0x1674 (the hero group's tether pull is on).
void CKHkS08Hero::SetExternalDisplacementFlag(uint8_t on) { m_unk1674 = on; }

// 0x0032a008 CKHkS08Hero_GetHeightAboveGround_maybe: the current ground contact's height (+0x4dc, its m_fdH).
float CKHkS08Hero::GetHeightAboveGround() { return m_gcCurDatasInOut.m_fdH; }

// 0x0032aec8 CKHkS08Hero_SetAnimPairAndWeight_maybe: with +0x358 bit 1, the root slot (+0x10f0) cut to its other side
// (StartCrossfade 0 s, mode 1), +0x360 bit 11, and the pair set on the active slot (vt+0x194).
void CKHkS08Hero::SetAnimPairAndWeight(float start1, float start2, float weight, uint32_t word1, uint32_t word2) {
    if ((m_unk358 & 2u) == 0) return;
    m_animBlendSlot10f0.StartCrossfade(0.0f, 1);  // 0x0007a848; TOC +0x2684
    m_unk360 |= 0x800u;
    GetAnimBlendSlot()->SetAnimPairAndWeight(word1, word2, start1, start2, weight);  // 0x00079e10
}

// 0x0032a6e8 CKHkS08Hero_SetExternalDisplacement_maybe: +0x1668 (GetExternalDisplacement reads it).
void CKHkS08Hero::SetExternalDisplacement(const CVector3* displacement) {
    m_unk1668 = displacement->x;
    m_unk1670 = displacement->z;
    m_unk166c = displacement->y;
}

// 0x0032a730 CKHkS08Hero_GetPredictedVelocity_maybe: +0x127c.
CVector3 CKHkS08Hero::GetDerivedVelocity() const { return CVector3{m_unk127c, m_unk1280, m_unk1284}; }

// 0x0032a758 CopyHeroAdjustedPosition: the position (+0x54c) plus +0x1268.
CVector3 CKHkS08Hero::GetAdjustedPosition() const {
    return CVector3{m_unk54c + m_unk1268, m_unk550 + m_unk126c, m_unk554 + m_unk1270};
}
