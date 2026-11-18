// Reconstructed original translation unit: 0x301408-0x30aa78 (GAME_TOC1, main_toc1), 77 functions, 73 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x301408  CKHkS08Hero_AdvanceAnimTimeUnlessMarkOverride_maybe
//   [x] 0x301458  CKHkS08Hero_GetCurrentAnimResource_maybe  (inline in its callers: CKHkS08Hero_11.cpp ActiveController / WrappedAnimTime)
//   [x] 0x3014b8  CKHkS08Hero_PlayAnimationFromHost  (inline in its caller: Spyro2008/misc/CKS08HeroAbilityHost.cpp PlayAbilityAnim)
//   [x] 0x301508  CKHkS08Hero_GetAnimBlendSlot
//   [x] 0x301528  CKHkS08Hero_GetInactiveAnimBlendSlot
//   [x] 0x301550  CKHkS08Hero_SkipAnimToEnd_maybe
//   [x] 0x301578  CKHkS08Hero_AdvanceAnimTime
//   [ ] 0x3015a0  CKHkS08Hero_UpdateSecondBlendSlotCrossfade_maybe  [dead: no pointer to its descriptor 0xb99f78, no call]
//   [x] 0x3015d0  CKHkS08Hero_PlayAnimation
//   [x] 0x301640  CKHkS08Hero_UpdateAnimationMarkFlags
//   [x] 0x301e70  CKHkS08Hero_AdvanceAnimScaled
//   [x] 0x301fe0  CKHkS08Hero_ComputeLocomotionBlendWeight_maybe
//   [x] 0x302218  CKHkS08Hero_UpdateIdleVariationAnim_maybe
//   [ ] 0x302378  FUN_00302378  [dead]
//   [x] 0x3024a8  CKHkS08Hero_AnimState9_LocomotionClimb_Condition
//   [x] 0x3024d0  CKHkS08Hero_AnimState10_LocomotionGround_Condition
//   [x] 0x3024f8  CKHkS08Hero_AnimState8_LocomotionFlying_Condition
//   [x] 0x302520  CKHkS08Hero_GroundAnimState09_Anim1D
//   [x] 0x3025f8  CKHkS08Hero_FlyAnimState11_Anim49
//   [x] 0x3026f8  CKHkS08Hero_FlyAnimState10_Anim48
//   [x] 0x302808  CKHkS08Hero_FlyAnimState05_Anim43
//   [x] 0x3029f8  CKHkS08Hero_GroundAnimState08_NoAnim
//   [x] 0x302bb0  CKHkS08Hero_FlyAnimState14_Anim52
//   [x] 0x302c98  CKHkS08Hero_FlyAnimState12_Anim4A
//   [x] 0x302de0  CKHkS08Hero_FlyAnimState09_Grounded_maybe
//   [x] 0x302f90  StaticInitAndDestruction_302f90  (the two file statics at the end)
//   [ ] 0x302fc0  _GLOBAL__D_302fc0
//   [ ] 0x302fd0  _GLOBAL__I_302fd0
//   [x] 0x302fe0  CKHkS08Hero_FlyAnimState07_Anim40
//   [x] 0x303168  CKHkS08Hero_GroundAnimState03_JumpTakeOff_maybe
//   [x] 0x303368  CKHkS08Hero_GetCurrentAnimTime  (inline in its callers: CKHkS08Hero_11.cpp WrappedAnimTime, CKHkS08Hero_14.cpp, _15.cpp)
//   [ ] 0x3033c8  FUN_003033c8  [dead]
//   [x] 0x303448  CKHkS08Hero_GroundAnimState04_Anim10_11
//   [x] 0x303698  CKHkS08Hero_ClimbAnimState06_NoAnim
//   [x] 0x303878  CKHkS08Hero_ClimbAnimState00_NoAnim
//   [x] 0x303a78  CKHkS08Hero_GetAnimParams13to18
//   [x] 0x303d48  CKHkS08Hero_FlyAnimState06_Anim3E_3F
//   [x] 0x304090  CKHkS08Hero_FlyAnimState13_NoAnim
//   [ ] 0x3043d0  CKHkS08Hero_GetAnimParam8  [dead: no pointer to its descriptor 0xb9a0c8, no call]
//   [ ] 0x304488  FUN_00304488  [dead]
//   [x] 0x3045e8  CKHkS08Hero_GetCinematicAnimSlots
//   [x] 0x3046a8  CKHkS08Hero_DynamicStageTail_maybe
//   [x] 0x3047a8  CKHkS08Hero_ClimbAnimState04_NoAnim
//   [x] 0x304a30  CKHkS08Hero_GroundAnimState00_Anim01
//   [x] 0x304d00  CKHkS08Hero_FlyAnimState16_NoAnim
//   [x] 0x304dc8  CKHkS08Hero_GroundAnimState07_Landing_maybe
//   [x] 0x3050d0  CKHkS08Hero_GroundAnimState10_HardLanding_maybe
//   [ ] 0x305370  FUN_00305370  [dead]
//   [x] 0x3054e0  CKHkS08Hero_ClimbAnimState01_Anim5F_65_67_63
//   [x] 0x3059d0  CKHkS08Hero_FlyAnimState00_Glide_maybe
//   [x] 0x305cf0  CKHkS08Hero_UpdateSecondaryAnimCrossfade_maybe
//   [x] 0x305d20  CKHkS08Hero_FlyAnimState01_Anim33_36
//   [x] 0x306028  CKHkS08Hero_FlyAnimState02_Anim3A_3D
//   [x] 0x306368  CKHkS08Hero_GroundAnimState02_Anim0C
//   [x] 0x306538  CKHkS08Hero_GroundAnimState01_Anim09
//   [x] 0x306708  CKHkS08Hero_ClimbAnimState03_NoAnim
//   [x] 0x3068e0  CKHkS08Hero_ClimbAnimState02_Anim8B
//   [x] 0x306cf0  CKHkS08Hero_ClimbAnimState07_Anim8C
//   [x] 0x306e50  CKHkS08Hero_GroundAnimState16_Anim90
//   [x] 0x306fc0  CKHkS08Hero_GroundAnimState15_Anim8F
//   [x] 0x307110  CKHkS08Hero_GroundAnimState14_Anim30
//   [x] 0x3072b8  CKHkS08Hero_GroundAnimState06_AirborneHigh_maybe
//   [x] 0x3076c0  CKHkS08Hero_GroundAnimState05_Airborne_maybe
//   [x] 0x307ac8  CKHkS08Hero_FlyAnimState04_Anim44
//   [x] 0x307cf8  CKHkS08Hero_FlyAnimState03_LandingApproach_maybe
//   [x] 0x308028  CKHkS08Hero_FlyAnimState08_Anim5B
//   [x] 0x3081a0  CKHkS08Hero_FlyAnimState17_Anim55
//   [x] 0x3083d0  CKHkS08Hero_FlyAnimState15_NoAnim
//   [x] 0x308778  CKHkS08Hero_GroundAnimState13_AnimD1
//   [x] 0x3089f8  CKHkS08Hero_GroundAnimState12_NoAnim
//   [x] 0x308f48  CKHkS08Hero_GroundAnimState11_Anim26_27_2A
//   [x] 0x309418  CKHkS08Hero_UpdateLocomotionAnimationBlend_maybe
//   [x] 0x3096f8  CKHkS08Hero_UpdateSideBlendAnims_maybe
//   [x] 0x309d58  CKHkS08Hero_UpdateAnimation_maybe
//   [x] 0x309e68  CKHkS08Hero_ClimbAnimState05_ClimbEnd_maybe
//   [x] 0x30a0d8  CKHkS08Hero_AnimState9_LocomotionClimb
//   [x] 0x30a518  CKHkS08Hero_AnimState8_LocomotionFlying
//
//   [ ] 0x9bd5f8  CKHkS08Hero_vf128  [inline]
//   [ ] 0x9bd600  CKHkS08Hero_vf12C  [inline]
//   [ ] 0x9bd608  CKHkS08Hero_vf13C  [inline]
//   [ ] 0x9bd610  CKHkS08Hero_vf140  [inline]
//   [ ] 0x9bd618  CKHkS08Hero_vf148  [inline]
//   [ ] 0x9bd628  CKHkS08Hero_IsKindOfClass  [inline]
//   [ ] 0x9bd680  CKHkS08Hero_GetClassType  [inline]
//   [ ] 0x9bd688  CKHkS08Hero_GetClassID  [inline]
//   [ ] 0x9bd690  CKHkS08Hero_vf160  [inline]
//   [ ] 0x9bd698  CKHkS08Hero_vf198  [inline]
//   [ ] 0x9bd6a0  CKHkS08Hero_vf158  [inline]
//   [ ] 0x9bd6a8  CKHkS08Hero_SetAnimSpeed  [inline]
//   [ ] 0x9bd6d0  CKHkS08Hero_vfF8  [inline]
//   [ ] 0x9bd6d8  CKHkS08Hero_vf15C  [inline]
//   [ ] 0x9bd6e0  CKHkS08Hero_IsAirborneActionActive_maybe  [inline]
//   [ ] 0x9bd6e8  CKHkS08Hero_RequestCatchUpPoint_maybe  [inline]
//   [ ] 0x9bd700  CKHkS08Hero_vf164  [inline]
//   [ ] 0x9bd710  CKHkS08Hero_IsClimbingForTrigger_maybe  [inline]
//   [ ] 0x9bd760  CKHkS08Hero_IsFlying_Thunk2  [inline]
//   [ ] 0x9bd788  CKHkS08Hero_IsHoldingEnemyInGrabCombo  [inline]
//   [ ] 0x9bd7d8  CKHkS08Hero_IsCarryingFilledPowerBucket_Thunk_maybe  [inline]
//   [ ] 0x9bd800  CKHkS08Hero_IsCarryingPowerBucket_Thunk_maybe  [inline]
//   [ ] 0x9bd828  CKHkS08Hero_IsCarryingTransportableWeight_Thunk_maybe  [inline]
//   [ ] 0x9bd850  CKHkS08Hero_IsCarryingTransportableKey_Thunk_maybe  [inline]
//   [ ] 0x9bd878  CKHkS08Hero_DeletingDestructor  [inline]
//   [ ] 0x9bd9e8  CKHkS08Hero_Destructor  [inline]
//   [x] 0x9bdb48  CKHkS08Hero_SetAirborne_maybe  [inline]
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/system/IKTime.h"
#include <cstring>
#include "Renderware/rtanim/RtAnim.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKVibrationData.h"
#include "k2000/misc/Engine.h"
#include <cmath>

// 0x00301508 CKHkS08Hero_GetAnimBlendSlot (vt+0x194): the slot the animation plays on.
AnimBlendSlot* CKHkS08Hero::GetAnimBlendSlot() { return m_unk138 + m_animBlendSlot10f0.m_unk10; }

// 0x00301528 CKHkS08Hero_GetInactiveAnimBlendSlot: the other one.
AnimBlendSlot* CKHkS08Hero::GetInactiveAnimBlendSlot() { return m_unk138 + (m_animBlendSlot10f0.m_unk10 ^ 1u); }

// 0x003045e8 CKHkS08Hero_GetCinematicAnimSlots (vt+0xbc): the cinematic blocs reach the hero's animation through its own
// blend slots, not its node's (the hero node's blend mode is 3, so CAnimatedNode_Load never loads the node's slot): the
// group's slot count for this hero (vt+0x134, 2 in DotD) and the playing slot, then the other one.
void CKHkS08Hero::GetBlendSlot(AnimBlendSlot** slots, int32_t* count) {
    *count = static_cast<IKGrpHero*>(m_pGrpHero)->GetNbAnimBlendSlots(m_ui8Hero);
    slots[0] = m_unk138 + m_animBlendSlot10f0.m_unk10;
    slots[1] = m_unk138 + (m_animBlendSlot10f0.m_unk10 ^ 1u);
}

// 0x00301578 CKHkS08Hero_AdvanceAnimTime (vt+0x188): the base's.
void CKHkS08Hero::AdvanceAnimTime(float dt) { AdvanceAnimTimeBase(dt); }  // 0x0034f970

// 0x003015d0 CKHkS08Hero_PlayAnimation (vt+0x184): the root slot (+0x10f0) crossfades to the other inner blender over
// `blend` seconds, then the base PlayAnim cuts that blender to the animation.
void CKHkS08Hero::PlayAnimation(float start, float blend, uint16_t animation) {
    m_animBlendSlot10f0.StartCrossfade(blend, 1);  // 0x0007a848
    PlayAnimBase(start, 0.0f, animation);           // 0x00351570; TOC +0x208c
}

namespace {
// The active slot's active keyframe controller (the slot's blender +0x04, its controller [+0x10] at +0x50).
CKAnmKeyFrameController* ActiveController(AnimBlendSlot* slot) {
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    return static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
}

// A time wrapped into [0, duration) as UpdateAnimationMarkFlags inlines it: the duration added while below 0 (TOC
// +0x208c), then taken off while the time is not below the duration + 0.
float WrapAnimTime(float t, float duration) {
    if (!(t >= 0.0f)) {
        do {
            t = t + duration;
        } while (t < 0.0f);
    }
    const float end = duration + 0.0f;
    while (t >= end) t = t - duration;  // cror gt|eq
    return t;
}

// `value` clamped into [low, high] as the hero code inlines it: low when low is at or above it, else high when high is
// at or below it (a NaN stays).
float ClampToRange(float value, float low, float high) {
    if (low >= value) return low;
    if (high <= value) return high;
    return value;
}

// The word of the hero's animation dictionary (+0x13c) entry `index`.
uint32_t DictionaryWord(const IKSerializable* dictionary, int32_t index) {
    return static_cast<uint32_t>(static_cast<const CAnimationDictionary*>(dictionary)->m_apAnimations[index]);
}
}  // namespace

// 0x00301640 CKHkS08Hero_UpdateAnimationMarkFlags: the marks of the active animation (its controller's +0x58) between
// the last evaluated time (+0x54) and the time now (+0x50, wrapped; with a locomotion pair running (+0x1838): between the
// pair's previous and current shared times +0x1834 / +0x1830, both wrapped) into +0xedc: the crossed marks (vt+0x1c) of
// channels 1..4 (bits 0..3: the feet), 5 (bit 7) and 6 (bit 8); the windows (vt+0x10 at the time now) of channels 7
// (bit 4), 10 (bit 5), 11 (bit 6) and 12 (bit 9). Nothing when the time did not move; from 0 when it wrapped.
void CKHkS08Hero::UpdateAnimationMarkFlags(float) {
    m_unkedc = 0;
    RtAnimAnimation* animation = ActiveController(GetAnimBlendSlot())->m_unk58;  // vt+0x194
    if (animation == nullptr) return;
    float now;
    float before;
    if (m_unk1838 == 0) {
        now = ActiveController(GetAnimBlendSlot())->m_unk50;
        now = WrapAnimTime(now, ActiveController(GetAnimBlendSlot())->GetDuration());  // 0x0007ab60
        before = ActiveController(GetAnimBlendSlot())->m_unk54;
    } else {
        before = WrapAnimTime(m_unk1834, ActiveController(GetAnimBlendSlot())->GetDuration());
        now = WrapAnimTime(m_unk1830, ActiveController(GetAnimBlendSlot())->GetDuration());
    }
    if (now == before) return;
    if (!(now >= before)) before = 0.0f;  // TOC +0x208c
    for (uint32_t i = 0; i < 4; ++i) {
        AnimMark* mark = Anim_GetMarkById(animation, i + 1);  // 0x00078830
        if (mark != nullptr && AnimMark_CrossedValueR3(mark, before, now) != 0) m_unkedc |= 1u << i;  // vt+0x1c
    }
    static const uint32_t kWindows[3][2] = {{7, 0x10u}, {10, 0x20u}, {11, 0x40u}};
    for (const auto& window : kWindows) {
        AnimMark* mark = Anim_GetMarkById(animation, window[0]);
        if (mark != nullptr && AnimMark_ValueAtR3(mark, ActiveController(GetAnimBlendSlot())->m_unk50) != 0) {
            m_unkedc |= window[1];  // vt+0x10
        }
    }
    AnimMark* mark = Anim_GetMarkById(animation, 5);
    if (mark != nullptr && AnimMark_CrossedValueR3(mark, before, now) != 0) m_unkedc |= 0x80u;
    mark = Anim_GetMarkById(animation, 6);
    if (mark != nullptr && AnimMark_CrossedValueR3(mark, before, now) != 0) m_unkedc |= 0x100u;
    mark = Anim_GetMarkById(animation, 0xc);
    if (mark != nullptr && AnimMark_ValueAtR3(mark, ActiveController(GetAnimBlendSlot())->m_unk50) != 0) {
        m_unkedc |= 0x200u;
    }
}

// 0x00301e70 CKHkS08Hero_AdvanceAnimScaled
void CKHkS08Hero::AdvanceAnimScaled(float dt, float reference, float speed, uint32_t toEnd) {
    const float scale = speed / reference;
    if (toEnd == 0) {
        AdvanceAnimTime(scale * dt);  // vt+0x188
        return;
    }
    const float step = scale * dt;
    const float next = step + ActiveController(GetAnimBlendSlot())->m_unk54;
    const float duration = ActiveController(GetAnimBlendSlot())->GetDuration();  // 0x0007ab60
    if (duration <= next) {  // cror gt|eq
        SkipAnimToEnd();  // vt+0x18c (the step is passed and not used)
    } else {
        AdvanceAnimTime(step);  // vt+0x188
    }
}

// 0x00301550 CKHkS08Hero_SkipAnimToEnd_maybe (vt+0x18c): the base's.
void CKHkS08Hero::SkipAnimToEnd() { SkipAnimToEndBase(); }  // 0x00351450

// 0x00301fe0 CKHkS08Hero_ComputeLocomotionBlendWeight_maybe: the weight between the paired locomotion animations of the
// current one. Flight cruise (0x44 / 0x45): the speed +0x12c4 over [+0x964, +0xa00] into [0, 1]. In the air (0x18): the
// speed over [+0xbd8, +0xbdc] into [0, 1], times the normalised velocity's y clamped to [-1, 1] (rising / falling); with
// +0xed0 bit 3, +0x1148 over [0, 1] into [1, -1]. Else 0.
float CKHkS08Hero::ComputeLocomotionBlendWeight() {
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (animation == 0x44 || animation == 0x45) {
        const float value = ClampToRange(m_unk12c4, m_unk964, m_unka00);
        return Math_RemapClamped(m_unk964, m_unka00, value, 0.0f, 1.0f);  // 0x00333618; TOC +0x208c / +0x2090
    }
    if (animation != 0x18) return 0.0f;  // TOC +0x208c
    if ((m_unked0 & 8u) != 0) return Math_RemapClamped(0.0f, 1.0f, AsF32(m_unk1148), 1.0f, -1.0f);  // TOC +0x2094
    const float low = m_unkbd8;
    const float high = m_unkbdc;
    const float speed =
        std::sqrt(ppc::fmadds(m_unk1284, m_unk1284, ppc::fmadds(m_unk127c, m_unk127c, m_unk1280 * m_unk1280)));  // 0x00010690
    const float weight = Math_RemapClamped(low, high, ClampToRange(speed, low, high), 0.0f, 1.0f);
    float y = m_unk1280;
    float x = m_unk127c;
    float z = m_unk1284;
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z = z * inverse;
        x = x * inverse;
        y = y * inverse;
    }
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x2098): the shared Y axis
    float slope = ppc::fmadds(z, kAxisY.z, ppc::fmadds(x, kAxisY.x, y * kAxisY.y));
    if (slope <= -1.0f) {  // cror lt|eq
        slope = -1.0f;
    } else if (slope >= 1.0f) {
        slope = 1.0f;
    }
    return slope * weight;
}

// 0x00302218 CKHkS08Hero_UpdateIdleVariationAnim_maybe: standing in the idle animation (0) for longer than +0xb64
// seconds (+0x19ac) plays one of five idle variations (rand, the table 0x00a705f0, index kept in +0x19b0); when the
// variation is the current animation again the idle comes back, and any other animation resets the timer.
void CKHkS08Hero::UpdateIdleVariationAnim(float dt) {
    // 0x00a705f0 (TOC +0x209c): the dictionary entries of the variations; the word before it (0) is read for index -1.
    static const uint32_t kIdleVariations[9] = {0, 2, 3, 4, 5, 6, 0x89, 0x8a, 0x77};
    const uint32_t* const table = &kIdleVariations[1];
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (animation == 0) {
        float timer = m_unk19ac;
        if (timer > m_unkb64 && (m_unk354 & 0x8000u) != 0) {
            const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
            const uint32_t index = ((draw * 5u) >> 16) & 0xffffu;
            m_unk19b0 = static_cast<uint16_t>(index);
            PlayAnimation(0.0f, 0.0f, static_cast<uint16_t>(table[index & 7u]));  // vt+0x184
            timer = m_unk19ac;
        }
        m_unk19ac = timer + dt;
        return;
    }
    // BUG(original): +0x19b0 is 0xffff (-1) unless a variation was chosen: the word before the table is read (0).
    const int32_t variation = static_cast<int16_t>(m_unk19b0);
    if (static_cast<int32_t>(animation) == static_cast<int32_t>(table[variation] & 0xffffu) && (m_unk354 & 0x8000u) != 0) {
        PlayAnimation(0.0f, 0.0f, 0);  // vt+0x184
    }
    m_unk19ac = 0.0f;
}

// 0x003024a8 CKHkS08Hero_AnimState9_LocomotionClimb_Condition: climbing.
uint8_t CKHkS08Hero::AnimLocomotionClimbCondition(IKTime*, uint8_t) { return IsClimbingMovementMode2(); }

// 0x003024d0 CKHkS08Hero_AnimState10_LocomotionGround_Condition: on the ground.
uint8_t CKHkS08Hero::AnimLocomotionGroundCondition(IKTime*, uint8_t) { return IsMovementMode0(); }

// 0x003024f8 CKHkS08Hero_AnimState8_LocomotionFlying_Condition: flying.
uint8_t CKHkS08Hero::AnimLocomotionFlyingCondition(IKTime*, uint8_t) { return IsFlyingMovementMode1(); }


// 0x00303a78 CKHkS08Hero_GetAnimParams13to18: the values at time 0 of the marks 13..18 of the animation `animation`
// (-1: the current one, +0x160) into out[0..5] (0 for a missing mark); nothing for an animation above 0x116 or not in
// the hero's dictionary.
void CKHkS08Hero::GetAnimParams13to18(float* out, int32_t animation) {
    if (animation == -1) animation = static_cast<int16_t>(m_unk160);
    if (animation > 0x116) return;
    const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_pAnimDico);
    RtAnimAnimation* anim = CAnimationManager_GetAnimation(static_cast<uint32_t>(dictionary->m_apAnimations[animation]));
    if (anim == nullptr) return;
    for (uint32_t i = 0; i < 6; ++i) {
        AnimMark* mark = Anim_GetMarkById(anim, 0xd + i);  // 0x00078830
        out[i] = mark == nullptr ? 0.0f : AnimMark_ValueAtF1(mark, 0.0f);  // vt+0x10 at TOC1 +0x208c (0.0)
    }
}

// 0x003046a8 CKHkS08Hero_DynamicStageTail_maybe: the end of each dynamic stage clears +0xee0. The rest has no effect:
// the dynamic service's elapsed step time (stage 1, `fixedStep` 0) or its sub-step count and fixed step (stage 3) are
// read and dropped, and the blend slot (vt+0x194) is fetched again when its current controller has +0x58 set.
void CKHkS08Hero::DynamicStageTail(float /*dt*/, int32_t /*fixedStep*/) { m_unkee0 = 0; }

// 0x00304a30 CKHkS08Hero_GroundAnimState00_Anim01: standing. Entering plays the idle (0, or 1 while the group's flag
// 0x400 or an ability is on) with a 0.2 s blend and resets the idle variation; each frame the ground locomotion flags
// pick the next state (11 / 12 / 3 / 13 / 5 / 15 / 8 / 1 / 2), else the idle variation and the animation time run on.
uint8_t CKHkS08Hero::GroundAnimState00(IKTime* clock, int32_t phase, uint8_t) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (phase == 1) {
        uint16_t animation = 1;
        if ((group->m_unkf8 & 0x400u) == 0 && IsAbilityActive() == 0) animation = 0;  // 0x002fc228
        PlayAnimation(0.0f, 0.2f, animation);  // vt+0x184; TOC +0x208c / +0x20a0
        m_unk19ac = 0.0f;
        m_unk19b0 = 0xffff;
        m_unkec8 = ((m_unkec8 & 0xffffffefu) | 0x10u) & 0xfffffff7u;
        m_unkec8 |= 8u;
        return 0;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        m_unk19ac = 0.0f;
        m_unk19b0 = 0xffff;
        return 0;
    }
    if (phase != 0) return 0;
    if ((m_unkec8 & 0x400u) != 0) return 0xb;
    bool idleOne = false;
    if ((group->m_unkf8 & 0x400u) != 0) {
        if (m_unk160 != 1) idleOne = true;
    }
    if (!idleOne && IsAbilityActive() != 0 && m_unk160 != 1) idleOne = true;
    if (idleOne) PlayAnimation(0.0f, 0.2f, 1);  // vt+0x184
    if ((m_unkec8 & 2u) != 0) return 0xc;
    if (m_unk1512 != 0) return 3;
    if ((m_unkec8 & 4u) != 0) return 0xd;
    if (m_unk1511 != 0) return 5;
    if (m_unk1615 != 0) return 0xf;
    if (m_unk1507 != 0) return 8;
    if (m_unk150c != 0) return 1;
    if (m_unk150d != 0) return 2;
    UpdateIdleVariationAnim(clock->m_afDeltaTime[0]);  // 0x00302218
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 0;
}

// The ground animation states' enter / exit blocks set and clear +0xec8 bits 3 and 4 (the original clears each bit and
// sets it again: rlwinm + ori).
//
// The states' shared answers: +0xec8 bit 1 (state 12), bit 2 (state 13), bit 10 (state 11); the locomotion bytes
// UpdateGroundLocomotionState 0x31a040 sets: +0x1512 (3), +0x1511 (5), +0x1615 (15), +0x1507 (8), +0x1517 / +0x1508 (4),
// +0x150b (0), +0x150c (1), +0x150d (2).

// 0x00306538 CKHkS08Hero_GroundAnimState01_Anim09: walking (0x09), its time scaled by the speed +0x12d0 over 2.
uint8_t CKHkS08Hero::GroundAnimState01(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 9);  // vt+0x184; TOC +0x208c / +0x20a0
        m_unk1838 = 0;
        m_unkec8 |= 0x18u;
        return 1;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 1;
    }
    if (phase != 0) return 1;
    if ((m_unkec8 & 2u) != 0) return 0xc;
    if ((m_unkec8 & 4u) != 0) return 0xd;
    if (m_unk1615 != 0) return 0xf;
    if (m_unk1512 != 0) return 3;
    if (m_unk1511 != 0) return 5;
    if (m_unk1507 != 0) return 8;
    if (m_unk1517 != 0) return 4;
    if (m_unk150b != 0) return 0;
    if (m_unk150d != 0) return 2;
    if (m_unk1838 == 0) AdvanceAnimScaled(clock->m_afDeltaTime[0], 2.0f, m_unk12d0, 0);  // 0x00301e70; TOC +0x20b0
    return 1;
}

// 0x00306368 CKHkS08Hero_GroundAnimState02_Anim0C: the other walk (0x0c), its time scaled by +0x12d0 over 7.
uint8_t CKHkS08Hero::GroundAnimState02(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0xc);  // vt+0x184
        m_unk1838 = 0;
        m_unkec8 |= 0x18u;
        return 2;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 2;
    }
    if (phase != 0) return 2;
    if ((m_unkec8 & 2u) != 0) return 0xc;
    if ((m_unkec8 & 4u) != 0) return 0xd;
    if (m_unk1512 != 0) return 3;
    if (m_unk1511 != 0) return 5;
    if (m_unk1615 != 0) return 0xf;
    if (m_unk1507 != 0) return 8;
    if (m_unk1508 != 0) return 4;
    if (m_unk150b != 0) return 0;
    if (m_unk150c != 0) return 1;
    if (m_unk1838 == 0) AdvanceAnimScaled(clock->m_afDeltaTime[0], 7.0f, m_unk12d0, 0);  // TOC +0x20d4
    return 2;
}

// 0x00303168 CKHkS08Hero_GroundAnimState03_JumpTakeOff_maybe: the jump's take-off. Entering by the jump kind +0x1539: 1 / 3 (0x12 /
// 0x14, blend +0xb34, +0xed8 bit 10), 2 (0x13, blend +0xb38, +0xed8 bit 11); another kind plays nothing (the enter's
// answer 5 is not used). Each frame: a new jump (+0x1512) plays 0x13 again; the take-off's end (0x12..0x14 ending) goes
// to the airborne state 5; on the ground again (+0x1511 clear): the landing, state 7.
uint8_t CKHkS08Hero::GroundAnimState03(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (ShouldJoinPartnerFlight() != 0) return 0xf;  // 0x00341fa0
        if ((m_unkec8 & 0x400u) != 0) return 0xb;
        if (m_unk1511 == 0) return 7;
        if (m_unk1512 != 0) {
            PlayAnimation(0.0f, m_unkb38, 0x13);  // vt+0x184; TOC +0x208c
            m_unked8 |= 0x800u;
            return 3;
        }
        const int16_t animation = static_cast<int16_t>(m_unk160);
        if ((animation == 0x12 || animation == 0x13 || animation == 0x14) && (m_unk354 & 0x8000u) != 0) return 5;
        if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 3;
    }
    if (phase != 1) return 3;
    const uint8_t kind = m_unk1539;
    if (kind == 3) {
        PlayAnimation(0.0f, m_unkb34, 0x14);
        m_unked8 |= 0x400u;
    } else if (kind == 1) {
        PlayAnimation(0.0f, m_unkb34, 0x12);
        m_unked8 |= 0x400u;
    } else if (kind == 2) {
        PlayAnimation(0.0f, m_unkb38, 0x13);
        m_unked8 |= 0x800u;
    } else {
        return 5;
    }
    return 3;
}

// 0x00303448 CKHkS08Hero_GroundAnimState04_Anim10_11: turning on the spot (0x10, then 0x11 once +0x1508 / +0x1517 are
// both clear); leaves for walking (state 2 with +0x150d, else the byte +0x150c: 0 or 1) when 0x11 ends or the turn
// amount +0x1378 is not 0.
uint8_t CKHkS08Hero::GroundAnimState04(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x10);
        m_unkec8 |= 0x18u;
        return 4;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 4;
    }
    if (phase != 0) return 4;
    if ((m_unkec8 & 2u) != 0) return 0xc;
    if ((m_unkec8 & 4u) != 0) return 0xd;
    if (m_unk1512 != 0) return 3;
    if (m_unk1507 != 0) return 8;
    if (m_unk1508 == 0 && m_unk1517 == 0 && m_unk160 != 0x11) PlayAnimation(0.0f, 0.2f, 0x11);
    const bool turnEnded = m_unk160 == 0x11 && (m_unk354 & 0x8000u) != 0;
    if (turnEnded || m_unk1378 != 0.0f) {  // TOC +0x208c
        if (m_unk150d != 0) return 2;
        return m_unk150c;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 4;
}

namespace {
// The enter block GroundAnimState05 0x3076c0 and GroundAnimState06 0x3072b8 share: the airborne pose (0x18) at its
// start; the rise / fall pair weight's approach speed +0x1450 = +0xbe8 and its start +0x1454 from the vertical speed
// +0x1280: rising over [+0xbd8, +0xbdc] into [0, 1], falling (negated) over [+0xbe0, +0xbe4] into [0, -1]; +0xecc bit 16
// starts it at +0x1828 instead (and is cleared).
void EnterAirborne(CKHkS08Hero* hero) {
    hero->m_unk182c = 0.2f;  // TOC +0x20a0
    hero->PlayAnimation(0.0f, 0.2f, 0x18);  // vt+0x184 (f2 still 0.2)
    hero->m_unk1838 = 0;
    hero->m_unk182c = 0.0f;  // TOC +0x208c
    hero->m_unk144c.y = hero->m_unkbe8;
    const float vertical = hero->m_unk1280;
    float start;
    if (vertical > 0.0f) {
        const float value = ClampToRange(vertical, hero->m_unkbd8, hero->m_unkbdc);
        start = Math_RemapClamped(hero->m_unkbd8, hero->m_unkbdc, value, 0.0f, 1.0f);  // 0x00333618
    } else {
        const float value = ClampToRange(-vertical, hero->m_unkbe0, hero->m_unkbe4);
        start = Math_RemapClamped(hero->m_unkbe0, hero->m_unkbe4, value, 0.0f, -1.0f);  // TOC +0x2094
    }
    if ((hero->m_unkecc & 0x10000u) != 0) {
        start = hero->m_unk1828;
        hero->m_unkecc &= 0xfffeffffu;
    }
    hero->m_unk144c.z = start;
    hero->m_unkec8 |= 0x18u;
}

// The part of GroundAnimState05 / 06's update before their height test: the answers, then 0x23 with +0xec4 bit 24
// (blended over 0.2 s) or back to 0x18 without it (over `backBlend`). 0xff: no answer yet.
uint8_t UpdateAirborneCommon(CKHkS08Hero* hero, float backBlend) {
    if (hero->ShouldJoinPartnerFlight() != 0) return 0xf;  // 0x00341fa0
    const uint32_t flags = hero->m_unkec8;
    if ((flags & 0x400u) != 0) return 0xb;
    if ((flags & 2u) != 0) return 0xc;
    if ((flags & 4u) != 0) return 0xd;
    if (hero->m_unk1512 != 0) return 3;
    if (hero->m_unk1511 == 0) {
        if (hero->m_unk1544 > hero->m_unkb6c) return 10;
        if (hero->m_unk388 != 0.0f && (hero->m_unkec4 & 0x8000u) != 0) return 9;  // TOC +0x208c
        return 7;
    }
    if ((hero->m_unkec4 & 0x1000000u) != 0 && hero->m_unk160 != 0x23) hero->PlayAnimation(0.0f, 0.2f, 0x23);
    if ((hero->m_unkec4 & 0x1000000u) == 0 && hero->m_unk160 == 0x23) hero->PlayAnimation(0.0f, backBlend, 0x18);
    return 0xff;
}
}  // namespace

// 0x003076c0 CKHkS08Hero_GroundAnimState05_Airborne_maybe: in the air (0x18 with the rise / fall pair of
// UpdateLocomotionAnimationBlend; 0x23 with +0xec4 bit 24); more than 16 above the ground or over a ground of property
// 0x200: state 6. Landed (+0x1511 clear): after a fall from higher than +0xb6c (+0x1544) the hard landing, state 10;
// input 4 held with +0xec4 bit 15: state 9; else the landing, state 7.
uint8_t CKHkS08Hero::GroundAnimState05(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        EnterAirborne(this);
        return 5;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 5;
    }
    if (phase != 0) return 5;
    const uint8_t answer = UpdateAirborneCommon(this, 0.0f);
    if (answer != 0xff) return answer;
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    const float height = GetHeightAboveGround();  // 0x0032a008
    if (height > 16.0f || (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0)) return 6;  // TOC +0x20e0
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 5;
}

// 0x003072b8 CKHkS08Hero_GroundAnimState06_AirborneHigh_maybe: the same in the air high above the ground (or over a ground of
// property 0x200); back within 16 of a plain ground: state 5. The end of +0xec4 bit 24 blends back over 0.2 s here.
uint8_t CKHkS08Hero::GroundAnimState06(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        EnterAirborne(this);
        return 6;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 6;
    }
    if (phase != 0) return 6;
    const uint8_t answer = UpdateAirborneCommon(this, 0.2f);
    if (answer != 0xff) return answer;
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    const float height = GetHeightAboveGround();  // 0x0032a008
    if (height <= 16.0f && (ground == nullptr || (ground->m_ui16PropertiesFlags & 0x200u) == 0)) return 5;
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 6;
}

// 0x00304dc8 CKHkS08Hero_GroundAnimState07_Landing_maybe: the landing (0x19, or 0x1a moving on (+0x150d); blends +0xb3c /
// +0xb40). Sets +0xec4 bits 9 and 28 and +0xed8 bit 12, clears +0x354 bit 9 and +0xecc bit 22; leaves for walking or
// standing when the landing ends.
uint8_t CKHkS08Hero::GroundAnimState07(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if (m_unk150d == 0) {
            PlayAnimation(0.0f, m_unkb3c, 0x19);
        } else {
            PlayAnimation(0.0f, m_unkb40, 0x1a);
        }
        m_unked8 |= 0x1000u;
        m_unkec4 |= 0x10000200u;
        m_unk354 &= 0xfffffdffu;
        m_unkecc &= 0xffbfffffu;
        m_unkec8 |= 0x18u;
        return 7;
    }
    if (phase == 2) {
        m_unkec4 &= 0xfffffdffu;
        m_unkec8 &= 0xffffffe7u;
        return 7;
    }
    if (phase != 0) return 7;
    if (ShouldJoinPartnerFlight() != 0) return 0xf;  // 0x00341fa0
    if ((m_unkec8 & 2u) != 0) return 0xc;
    if ((m_unkec8 & 4u) != 0) return 0xd;
    if (m_unk1512 != 0) return 3;
    if (m_unk150d == 0) {
        if (m_unk160 == 0x1a) {
            PlayAnimation(0.0f, 0.25f, 0x19);  // TOC +0x20bc
            return 7;
        }
    } else if (m_unk160 == 0x19) {
        return 2;
    }
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (m_unk150c != 0 && animation == 0x19) return 1;
    if ((animation != 0x1a && animation != 0x19) || (m_unk354 & 0x8000u) != 0) {
        if (m_unk150d != 0) return 2;
        if (m_unk150c != 0) return 1;
        if (m_unk150b != 0) return 0;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 7;
}

// 0x003029f8 CKHkS08Hero_GroundAnimState08_NoAnim: a short move on the spot: 0x08 with +0x1505 (0.04 s blend), 0x07
// with +0x1506 (0.2 s), else no animation; +0xecc bit 3. Back to standing when 0x07 / 0x08 ends.
uint8_t CKHkS08Hero::GroundAnimState08(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        m_unk1507 = 0;
        if (m_unk1505 != 0) {
            PlayAnimation(0.0f, 0.04f, 8);  // TOC +0x20a4
        } else if (m_unk1506 != 0) {
            PlayAnimation(0.0f, 0.2f, 7);
        }
        m_unkecc |= 8u;
        return 8;
    }
    if (phase == 2) {
        m_unk1506 = 0;
        m_unk1505 = 0;
        return 8;
    }
    if (phase != 0) return 8;
    if (m_unk1512 != 0) return 3;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if ((animation == 8 || animation == 7) && (m_unk354 & 0x8000u) != 0) return 0;
    AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 8;
}

// 0x00302520 CKHkS08Hero_GroundAnimState09_Anim1D: 0x1d until a jump (state 3).
uint8_t CKHkS08Hero::GroundAnimState09(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (m_unk1512 != 0) return 3;
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 9;
    }
    if (phase == 1) PlayAnimation(0.0f, 0.2f, 0x1d);
    return 9;
}

// 0x003050d0 CKHkS08Hero_GroundAnimState10_HardLanding_maybe: the landing after a high fall: 0x1b, then 0x1c from +0x1540 = the
// fall height past +0xb6c over the range [+0xb6c, +0xb70] times 1.5, in [0, 1.5]; +0xec4 bits 11 / 12, +0x354 bit 11;
// the player's hero vibrates the pad (+0x116c, value 3). Standing again when 0x1c ends.
uint8_t CKHkS08Hero::GroundAnimState10(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        const float start = ppc::fmadds(m_unkb70 - m_unk1544, 1.5f, 0.0f);  // TOC +0x20c0 / +0x208c
        m_unk1540 = start;
        float scaled = start / (m_unkb70 - m_unkb6c);
        if (scaled <= 0.0f) {  // cror lt|eq
            scaled = 0.0f;
        } else if (scaled >= 1.5f) {
            scaled = 1.5f;
        }
        m_unk1540 = scaled;
        PlayAnimation(0.0f, 0.2f, 0x1b);
        m_unkec4 |= 0x1800u;
        m_unk354 |= 0x800u;
        CKVibrationData* vibration = static_cast<CKVibrationData*>(m_unk116c);
        if (vibration != nullptr && m_ui8Hero == m_ui8TrackedLeader) {
            vibration->m_pOwner = this;
            vibration->m_ui8NumPad = m_ui8Leader;
            vibration->m_ui8OwnerIndex = 3;
            g_pEngine->m_input->PlayVibration(vibration);  // 0x00107d38
        }
        return 10;
    }
    if (phase == 2) {
        m_unkec4 &= 0xffffe7ffu;
        m_unk1544 = 0.0f;
        m_unk354 &= 0xfffff7ffu;
        return 10;
    }
    if (phase != 0) return 10;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (animation == 0x1b) {
        if ((m_unk354 & 0x8000u) != 0) {
            PlayAnimation(m_unk1540, 0.2f, 0x1c);
            return 10;
        }
    } else if (animation == 0x1c && (m_unk354 & 0x8000u) != 0) {
        return 0;
    }
    AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 10;
}

// 0x00308f48 CKHkS08Hero_GroundAnimState11_Anim26_27_2A: the carried / grabbed sequence of +0xec8 bit 10 (0x2a, or 0x27
// with +0xec8 bit 18; then 0x29 / 0x28 / 0x26 / 0x27 from +0xec8 bits 13 / 14) and its flags (+0xec8 bits 22 / 23,
// +0x35c bit 3, +0x354 bit 31, +0x368 bit 13 for the partner, +0xec4 bit 8). State 5 with +0xec8 bit 12; standing when
// bit 10 goes or 0x26 / 0x27 ends.
uint8_t CKHkS08Hero::GroundAnimState11(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if ((m_unkec8 & 0x40000u) == 0) {
            PlayAnimation(0.0f, 0.08f, 0x2a);  // TOC +0x20f4
        } else {
            PlayAnimation(0.0f, 0.04f, 0x27);
            m_unkec8 &= 0xffffbfffu;
            m_unked8 |= 0x8000u;
        }
        m_unkec8 |= 0xc00000u;
        m_unk35c |= 8u;
        m_unk354 |= 0x80000000u;
        if (m_ui8Hero != m_ui8TrackedLeader) m_unk368 |= 0x2000u;
        m_unkec4 |= 0x100u;
        return 0xb;
    }
    if (phase == 2) {
        m_unkec8 &= 0xfffbc1ffu;
        m_unk354 &= 0xfffff7ffu;
        m_unkec4 &= 0xffdfd3ffu;
        m_unkec8 &= 0xfd3fff7fu;
        m_unk35c &= 0xfffffff7u;
        m_unk354 &= 0x7fffffffu;
        m_unk368 &= 0xffffdfffu;
        m_unkec4 &= 0xfffffeffu;
        return 0xb;
    }
    if (phase != 0) return 0xb;
    m_unkec4 |= 0x100u;
    uint32_t flags = m_unkec8;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if ((flags & 0x2000u) == 0) {
        if (animation == 0x2a && (m_unk354 & 0x8000u) != 0) {
            m_unkecc |= 0x2000000u;
            PlayAnimation(0.0f, 0.2f, 0x29);
            return 0xb;
        }
    } else if (animation != 0x28 && animation != 0x26) {
        PlayAnimation(0.0f, 0.2f, 0x28);
        return 0xb;
    }
    if ((flags & 0x4000u) != 0) {
        m_unkec8 &= 0xffffbfffu;
        if ((m_unkec8 & 0x40000u) == 0) {
            m_unked8 |= 0x4000u;
            PlayAnimation(0.0f, 0.0f, 0x26);
        } else {
            PlayAnimation(0.0f, 0.0f, 0x27);
            m_unked8 |= 0x8000u;
        }
        flags = m_unkec8;
    }
    if ((flags & 0x1000u) != 0) return 5;
    const int16_t now = static_cast<int16_t>(m_unk160);
    if ((flags & 0x400u) == 0 || ((now == 0x26 || now == 0x27) && (m_unk354 & 0x8000u) != 0)) return 0;
    AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 0xb;
}

// 0x003089f8 CKHkS08Hero_GroundAnimState12_NoAnim: the push / pull of +0xec8 bit 1 in the direction +0x1228 (0..3:
// 0x2b..0x2e; 4 none) with its flags and the camera service's temporary flag 27 (+0x46c). The time of the animation is
// kept in +0x122c; past +0xdc0, +0xecc bit 27 goes. Leaves for walking (+0xec8 bit 20 with +0x1378 above 0.5), standing
// or state 13 (+0xec8 bit 21) when the animation ends; state 11 with +0xec8 bit 10.
uint8_t CKHkS08Hero::GroundAnimState12(IKTime* clock, int32_t phase, uint8_t) {
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x20ec)
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (phase == 1) {
        const uint8_t direction = m_unk1228;
        if (direction == 1) {
            PlayAnimation(0.0f, 0.2f, 0x2c);
        } else if (direction == 0) {
            PlayAnimation(0.0f, 0.2f, 0x2b);
        } else if (direction == 2) {
            PlayAnimation(0.0f, 0.2f, 0x2d);
        } else if (direction == 3) {
            PlayAnimation(0.0f, 0.2f, 0x2e);
        }
        m_unk122c = 0.0f;
        m_unk1230 = kNullVector.x;
        m_unk1238 = kNullVector.z;
        m_unk1234 = kNullVector.y;
        m_unk123c = kNullVector.x;
        m_unk1244 = kNullVector.z;
        m_unk1240 = kNullVector.y;
        m_unkec4 |= 0x202c00u;
        m_unk354 |= 0x800u;
        if (m_unk1511 == 0) {
            m_unked8 |= 0x2000u;
        } else {
            m_unked8 |= 0x80u;
        }
        camera->m_baTemporaryFlags |= 0x8000000u;
        m_unkec8 |= 0xc00080u;
        m_unkecc |= 0x8000000u;
        return 0xc;
    }
    if (phase == 2) {
        m_unkec8 &= 0xfffffffdu;
        m_unk122c = 0.0f;
        m_unk1228 = 4;
        m_unkec4 &= 0xffdfd3ffu;
        m_unk354 &= 0xfffff7ffu;
        m_unkec8 &= 0xff3fffffu;
        camera->m_baTemporaryFlags &= 0xf7ffffffu;
        m_unk1248 = kNullVector.x;
        m_unk1250 = kNullVector.z;
        m_unk124c = kNullVector.y;
        m_unkec8 &= 0xffffff7fu;
        m_unkecc &= 0xf7ffffffu;
        return 0xc;
    }
    if (phase != 0) return 0xc;
    const uint32_t flags = m_unkec8;
    if ((flags & 0x400u) != 0) return 0xb;
    bool ended = false;
    switch (m_unk1228) {
        case 0:
            if (m_unk160 != 0x2b) {
                PlayAnimation(0.0f, 0.2f, 0x2b);
                return 0xc;
            }
            ended = true;
            break;
        case 1:
            if (m_unk160 != 0x2c) {
                PlayAnimation(0.0f, 0.2f, 0x2c);
                return 0xc;
            }
            ended = true;
            break;
        case 2:
            if (m_unk160 != 0x2d) {
                PlayAnimation(0.0f, 0.2f, 0x2d);
                return 0xc;
            }
            ended = true;
            break;
        case 3:
            if (m_unk160 != 0x2e) {
                PlayAnimation(0.0f, 0.2f, 0x2e);
                return 0xc;
            }
            ended = true;
            break;
        case 4:
            return 0xd;
        default:
            break;
    }
    if (ended) {
        if ((flags & 0x100000u) != 0 && m_unk1378 > 0.5f && (flags & 0x200000u) == 0) return 2;  // TOC +0x20b8
        if ((m_unk354 & 0x8000u) != 0) {
            if ((flags & 0x200000u) == 0) return 0;
            return 0xd;
        }
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    const float time = ActiveController(GetAnimBlendSlot())->m_unk50;  // vt+0x194
    m_unk122c = time;
    if (m_unkdc0 >= time) return 0xc;
    m_unkecc &= 0xf7ffffffu;
    return 0xc;
}

// 0x00308778 CKHkS08Hero_GroundAnimState13_AnimD1: the push's end (0xd0 after 0xcf, else 0xd1; 0.04 s blends) with
// +0xec8 bits 3 / 4, +0xec4 bits 10, 11, 12, 13 and 21, +0x354 bit 11, +0xed8 bit 25. State 12 with +0xec8 bit 1,
// standing without bit 2.
uint8_t CKHkS08Hero::GroundAnimState13(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.04f, m_unk160 == 0xcf ? 0xd0 : 0xd1);
        m_unkec8 |= 0x18u;
        m_unkec4 |= 0x203c00u;
        m_unk354 |= 0x800u;
        m_unked8 |= 0x2000000u;
        return 0xd;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        m_unkec4 &= 0xffdfc3ffu;
        m_unk354 &= 0xfffff7ffu;
        m_unkec8 &= 0xff3fffffu;
        return 0xd;
    }
    if (phase != 0) return 0xd;
    if ((m_unkec8 & 2u) != 0) return 0xc;
    if ((m_unkec8 & 4u) == 0) return 0;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if ((animation == 0xcf || animation == 0xd0) && (m_unk354 & 0x8000u) != 0) {
        PlayAnimation(0.0f, 0.04f, 0xd1);
    } else if (m_unk1838 == 0) {
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    }
    return 0xd;
}

// 0x00307110 CKHkS08Hero_GroundAnimState14_Anim30: joining the partner's flight (0x30, 0.4 s blend). Standing again when
// that stops; state 16 with +0x15fc; state 15 once the partner is farther than +0xd68 (+0x15f0 vector) and the angle
// +0x1600 is above +0xd78 degrees.
uint8_t CKHkS08Hero::GroundAnimState14(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (ShouldJoinPartnerFlight() == 0) return 0;  // 0x00341fa0
        if (m_unk15fc != 0) return 0x10;
        const float limit = m_unkd68;
        const float distance = std::sqrt(ppc::fmadds(m_unk15f8, m_unk15f8, ppc::fmadds(m_unk15f0, m_unk15f0, m_unk15f4 * m_unk15f4)));
        if (limit < distance && !(AsF32(m_unk1600) <= m_unkd78 * 1.74532905e-2f)) return 0xf;  // TOC +0x20dc; ble
        if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0xe;
    }
    if (phase == 1) PlayAnimation(0.0f, 0.4f, 0x30);  // TOC +0x20d8
    return 0xe;
}

// 0x00306fc0 CKHkS08Hero_GroundAnimState15_Anim8F: 0x8f while joining the partner's flight; state 16 with +0x15fc.
uint8_t CKHkS08Hero::GroundAnimState15(IKTime* clock, int32_t phase, uint8_t) {
    GetPartnerHero();  // 0x002f85f8 (the result is not used)
    if (phase == 0) {
        if (ShouldJoinPartnerFlight() == 0) return 0;  // 0x00341fa0
        if (m_unk15fc != 0) return 0x10;
        if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0xf;
    }
    if (phase == 1) PlayAnimation(0.0f, 0.2f, 0x8f);
    return 0xf;
}

// 0x00306e50 CKHkS08Hero_GroundAnimState16_Anim90: 0x90 (clears +0x15fc, +0xed8 bit 24); back to state 15 when it ends.
uint8_t CKHkS08Hero::GroundAnimState16(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (ShouldJoinPartnerFlight() == 0) return 0;  // 0x00341fa0
        if (m_unk160 == 0x90 && (m_unk354 & 0x8000u) != 0) return 0xf;
        if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0x10;
    }
    if (phase == 1) {
        m_unk15fc = 0;
        PlayAnimation(0.0f, 0.04f, 0x90);
        m_unked8 |= 0x1000000u;
    }
    return 0x10;
}

// 0x00305cf0 CKHkS08Hero_UpdateSecondaryAnimCrossfade_maybe (vt+0x108): the root slot's crossfade one step.
void CKHkS08Hero::UpdateSecondaryAnimCrossfade(IKTime* clock) {
    m_animBlendSlot10f0.UpdateCrossfade(clock->m_afDeltaTime[0]);  // 0x0007a9d0
}

// 0x00309418 CKHkS08Hero_UpdateLocomotionAnimationBlend_maybe: the paired locomotion animations' weight (+0x144c) and,
// for the airborne pose (0x18) and the flight cruise (0x44 / 0x45) on a slot without a crossfade, the pair blended by it
// (+0x1838 / +0x1839 say it runs). Any other animation clears the two flags.
void CKHkS08Hero::UpdateLocomotionAnimationBlend(float dt, uint8_t enabled) {
    m_unk144c.x = ComputeLocomotionBlendWeight();  // 0x00301fe0
    if (enabled != 0) {
        const int16_t animation = static_cast<int16_t>(m_unk160);
        if (animation == 0x44 || animation == 0x45 || animation == 0x18) {
            // The dictionary entries: the centre (0x18 in the air, 0x41 / 0x42 flying) and the pair's two sides (rising
            // 0x15, falling 0x16, or 0x17 high in the air: the ground sub-state 6; flying: the cruise itself).
            int32_t negative = 0x16;
            int32_t centre = 0x18;
            int32_t positive = 0x15;
            if (animation == 0x44) {
                negative = 0x44;
                centre = 0x41;
                positive = 0x44;
            } else if (animation == 0x45) {
                negative = 0x45;
                centre = 0x42;
                positive = 0x45;
            } else if (m_unk1960 == 6) {
                negative = 0x17;
            }
            if (GetAnimBlendSlot()->m_unk14 == 0) {  // vt+0x194: no crossfade on the slot
                m_unk1839 = 1;
                if (m_unk1838 == 0) {
                    m_unk1838 = 1;
                    m_unk1830 = ActiveController(GetAnimBlendSlot())->m_unk50;
                }
                const float weight = m_unk144c.z;
                const float time = m_unk1830;
                const uint32_t positiveWord = DictionaryWord(m_pAnimDico, positive);
                const uint32_t centreWord = DictionaryWord(m_pAnimDico, centre);
                const uint32_t negativeWord = DictionaryWord(m_pAnimDico, negative);
                if (weight <= 0.0f) {  // TOC +0x208c
                    // The absolute value through the stack: the sign bit cleared (rlwinm 0,1,31).
                    GetAnimBlendSlot()->SetAnimPairAndWeight(centreWord, negativeWord, time, time, std::fabs(weight));
                } else {
                    GetAnimBlendSlot()->SetAnimPairAndWeight(centreWord, positiveWord, time, time, weight);  // 0x00079e10
                }
                const float shared = m_unk1830;
                m_unk1834 = shared;
                m_unk1830 = shared + m_unk88c;
                FloatApproach_Step(dt, &m_unk144c.x);  // 0x002436e8
                return;
            }
        }
    }
    m_unk1839 = 0;
    m_unk1838 = 0;
}

// 0x003096f8 CKHkS08Hero_UpdateSideBlendAnims_maybe: the lean approach (+0x13b4) one step, its default limits
// (+0x12f4..+0x1300), and for the walk, turn and flight animations with a left / right pair the three-way blend on the
// slot (+0x1838 says it runs). Any other animation clears +0x1838.
void CKHkS08Hero::UpdateSideBlendAnims(float dt, uint8_t enabled) {
    FloatApproach_Step(dt, &m_unk13b4.x);  // 0x002436e8
    m_unk12f4 = 4.0f;  // TOC +0x20f8
    m_unk12fc = 1.5f;  // TOC +0x20c0
    m_unk1300 = 0.0f;
    m_unk12f8 = 1.0f;  // TOC +0x2090
    if (enabled != 0) {
        // The dictionary entries of the pair (the centre, its two sides), the time scale of the shared time and the
        // approach's limits (+0x12f4 / +0x12f8; +0x12fc / +0x1300) per animation.
        int32_t first = 0;
        int32_t centre = 0;
        int32_t second = 0;
        float timeScale = 1.0f;  // TOC +0x2090
        bool found = true;
        switch (static_cast<int16_t>(m_unk160)) {
            case 0x09:
                first = 0xa; centre = 0x9; second = 0xb;
                timeScale = m_unk12d0 * 0.5f;  // TOC +0x20b8
                m_unk12f4 = m_unkb44; m_unk12f8 = m_unkb48; m_unk12fc = m_unkb54; m_unk1300 = m_unkb5c;
                break;
            case 0x0c:
                first = 0xd; centre = 0xc; second = 0xe;
                m_unk12f4 = m_unkb4c; m_unk12f8 = m_unkb50; m_unk12fc = m_unkb58; m_unk1300 = m_unkb60;
                break;
            case 0x23:
                first = 0x24; centre = 0x23; second = 0x25;
                m_unk12f4 = m_unka24; m_unk12f8 = m_unka28; m_unk12fc = m_unka34; m_unk1300 = m_unka3c;
                break;
            case 0x30:
                first = 0x31; centre = 0x30; second = 0x32;
                m_unk12f4 = m_unka24; m_unk12f8 = m_unka28; m_unk12fc = m_unka34; m_unk1300 = m_unka3c;
                break;
            case 0x33: first = 0x34; centre = 0x33; second = 0x35; break;
            case 0x37:
                first = 0x38; centre = 0x37; second = 0x39;
                m_unk12f4 = m_unka2c; m_unk12f8 = m_unka30; m_unk12fc = m_unka38; m_unk1300 = m_unka40;
                break;
            case 0x3a: first = 0x3b; centre = 0x3a; second = 0x3c; break;
            case 0xda:
                first = 0xfd; centre = 0xda; second = 0xfe;
                timeScale = m_unk12d0 * 0.25f;  // TOC +0x20bc
                m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08;
                break;
            case 0xde: first = 0x103; centre = 0xde; second = 0x104; m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08; break;
            case 0xe1:
                first = 0x109; centre = 0xe1; second = 0x10a;
                timeScale = m_unk1d20;
                m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08;
                break;
            case 0xed: first = 0xff; centre = 0xed; second = 0x100; m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08; break;
            case 0xee: first = 0xff; centre = 0xee; second = 0x100; m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08; break;
            case 0xf1: first = 0x105; centre = 0xf1; second = 0x106; m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08; break;
            case 0xf4:
                first = 0x10b; centre = 0xf4; second = 0x10c;
                timeScale = m_unk1d20;
                m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08;
                break;
            case 0xf6: first = 0x101; centre = 0xf6; second = 0x102; m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08; break;
            case 0xf9: first = 0x107; centre = 0xf9; second = 0x108; m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08; break;
            case 0xfc:
                first = 0x10d; centre = 0xfc; second = 0x10e;
                timeScale = m_unk1d20;
                m_unk12f4 = m_unk1d04; m_unk12f8 = m_unk1d08;
                break;
            default:
                found = false;
                break;
        }
        if (found && GetAnimBlendSlot()->m_unk14 == 0) {  // vt+0x194: no crossfade on the slot
            if (m_unk1838 == 0) {
                m_unk1838 = 1;
                m_unk1830 = ActiveController(GetAnimBlendSlot())->m_unk50;
            }
            const float weight = m_unk13b4.z;  // +0x13bc
            const float time = m_unk1830;
            const uint32_t firstWord = DictionaryWord(m_pAnimDico, first);
            const uint32_t centreWord = DictionaryWord(m_pAnimDico, centre);
            const uint32_t secondWord = DictionaryWord(m_pAnimDico, second);
            if (weight <= 0.0f) {  // TOC +0x208c
                GetAnimBlendSlot()->SetAnimPairAndWeight(centreWord, secondWord, time, time, std::fabs(weight));
            } else {
                GetAnimBlendSlot()->SetAnimPairAndWeight(centreWord, firstWord, time, time, weight);  // 0x00079e10
            }
            const float shared = m_unk1830;
            m_unk1834 = shared;
            m_unk1830 = ppc::fmadds(timeScale, m_unk88c, shared);
            // The turn (+0x1368) against the move direction (+0x37c), absolute: below +0x1300 the target +0x13b8 is
            // +0x12fc, else +0x12f4.
            const float turn = std::fabs(ppc::fmadds(m_unk1370, m_unk384, ppc::fmadds(m_unk1368, m_unk37c, m_unk136c * m_unk380)));
            m_unk13b4.y = !(m_unk1300 <= turn) ? m_unk12fc : m_unk12f4;  // ble (a NaN takes +0x12fc)
            FloatApproach_Step(m_unk88c, &m_unk13b4.x);  // 0x002436e8
            return;
        }
    }
    m_unk1838 = 0;
}

// 0x00309d58 CKHkS08Hero_UpdateAnimation_maybe (vt+0x104): the animation marks, the root slot's crossfade, the side
// blends (unless a locomotion pair holds the slot) and the locomotion pair blend.
void CKHkS08Hero::UpdateAnimation(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];
    UpdateAnimationMarkFlags(dt);                   // 0x00301640
    m_animBlendSlot10f0.UpdateCrossfade(clock->m_afDeltaTime[0]);  // 0x0007a9d0
    if (m_unk1839 == 0) {
        const float frameDt = clock->m_afDeltaTime[0];
        if (ShouldStayClimbing() == 0) {            // 0x00342fa8
            UpdateSideBlendAnims(frameDt, 1);       // 0x003096f8
        } else {
            UpdateSideBlendAnims(frameDt, m_unk1dfc);
        }
    }
    if (m_unk1838 != 0 && m_unk1839 == 0) return;
    UpdateLocomotionAnimationBlend(clock->m_afDeltaTime[0], 1);  // 0x00309418
}

// ---- step 6 ANIM: the flying animation sub-machine (+0x183c, current state +0x18d0) ----
//
// The states' shared answers (the flight locomotion of CKHkS08Hero_8 / _10 sets the bytes): +0xec8 bit 10 (state 16:
// carried / grabbed), bit 1 (15), +0xecc bit 19 (17), +0x13d8 (13), +0x1438 (14), +0x13cc (7), +0xecc bit 23 (8), +0x13ce
// (1 slower than the cruise speed +0x964, else 2), +0x13a4 (3), +0x13cf (5); +0x13d1 clear (on the ground in the flight mode): the
// states 9..11 (0x47 / 0x48 / 0x49 by the speed +0x12d0 against +0x990..+0x99c).
// +0x13c0 counts the time spent in the state.

namespace {
// The animation id `animation` as the original compares it: the half word sign-extended against itself zero-extended
// (lhz, extsh, cmpw): false only for an id with bit 15 set.
bool AnimIdIsShort(uint16_t animation) {
    return static_cast<int32_t>(static_cast<int16_t>(animation)) == static_cast<int32_t>(animation);
}

// The flight cruise animations FlyAnimState00 / 04 let run (0x3a, 0x33, 0x41, 0x43, 0x36, 0x3d, and 0x44 for state 00).
bool IsFlyCruiseAnim(int16_t animation) {
    return animation == 0x3a || animation == 0x33 || animation == 0x41 || animation == 0x43 || animation == 0x36 ||
           animation == 0x3d;
}
}  // namespace

// 0x003059d0 CKHkS08Hero_FlyAnimState00_Glide_maybe: gliding: 0x37 at or above the cruise speed +0x964 (0.2 s blend), else
// 0x30 (0.5 s); each frame 0x37 / 0x30 follow +0x12d0 against +0x964 (unless a cruise animation runs). Without +0x13d1
// (on the ground): state 11.
uint8_t CKHkS08Hero::FlyAnimState00(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if (!(m_unk12c4 < m_unk964)) {  // bge
            PlayAnimation(0.0f, 0.2f, 0x37);  // vt+0x184; TOC +0x208c / +0x20a0
        } else {
            PlayAnimation(0.0f, 0.5f, 0x30);  // TOC +0x20b8
        }
        m_unkec8 |= 0x18u;
        return 0;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 0;
    }
    if (phase != 0) return 0;
    const uint32_t flags = m_unkec8;
    if ((flags & 0x400u) != 0) return 0x10;
    if ((flags & 2u) != 0) return 0xf;
    const uint32_t flagsEcc = m_unkecc;
    if ((flagsEcc & 0x80000u) != 0) return 0x11;
    if (m_unk13d8 != 0) return 0xd;
    if (m_unk1438 != 0) return 0xe;
    if (m_unk13cc != 0) return 7;
    if ((flagsEcc & 0x800000u) != 0) return 8;
    if (m_unk13ce != 0) return !(m_unk12c4 < m_unk964) ? 2 : 1;  // crnor eq, lt, lt
    if (m_unk13a4 != 0) return 3;
    int16_t animation = static_cast<int16_t>(m_unk160);
    if (!IsFlyCruiseAnim(animation) && animation != 0x44) {
        bool skip = false;
        if (animation == 0x37) {
            if (!(m_unk12d0 < m_unk964)) {  // bge
                skip = true;
            } else {
                PlayAnimation(0.0f, 0.5f, 0x30);
                animation = static_cast<int16_t>(m_unk160);
            }
        }
        if (!skip && animation == 0x30 && m_unk12d0 >= m_unk964) PlayAnimation(0.0f, 0.2f, 0x37);  // cror gt|eq
    }
    if (m_unk13d1 == 0) return 0xb;
    if (m_unk1838 != 0) return 0;
    AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 0;
}

// 0x00305d20 CKHkS08Hero_FlyAnimState01_Anim33_36: flying slower than the cruise speed: 0x33 (+0xed8 bit 0), or 0x36
// once after a take-off (+0x1809, cleared; +0xed8 bit 5). Back to gliding (0) when the animation ends; +0x13ce at or
// above the cruise speed: state 2.
uint8_t CKHkS08Hero::FlyAnimState01(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if (m_unk1809 == 0) {
            PlayAnimation(0.0f, 0.2f, 0x33);  // vt+0x184
            m_unk1838 = 0;
            m_unked8 |= 1u;
        } else {
            m_unk1809 = 0;
            PlayAnimation(0.0f, 0.2f, 0x36);
            m_unked8 |= 0x20u;
        }
        m_unk13c0 = 0.0f;
        m_unkec8 |= 0x18u;
        return 1;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 1;
    }
    if (phase != 0) return 1;
    const uint32_t flags = m_unkec8;
    if ((flags & 0x400u) != 0) return 0x10;
    if ((flags & 2u) != 0) return 0xf;
    if (m_unk13d8 != 0) return 0xd;
    const uint32_t flagsEcc = m_unkecc;
    if ((flagsEcc & 0x80000u) != 0) return 0x11;
    if (m_unk13a4 != 0) return 3;
    if (m_unk13cc != 0) return 7;
    if (!AnimIdIsShort(m_unk160) || (m_unk354 & 0x8000u) != 0) return 0;
    if ((flagsEcc & 0x800000u) != 0) return 8;
    if (m_unk13ce != 0) {
        if (!(m_unk12c4 < m_unk964)) return 2;  // bge
        PlayAnimation(0.0f, 0.2f, 0x33);
        m_unk13c0 = 0.0f;
        m_unk1838 = 0;
        return 1;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    m_unk13c0 = m_unk13c0 + clock->m_afDeltaTime[0];
    return 1;
}

// 0x00306028 CKHkS08Hero_FlyAnimState02_Anim3A_3D: flying at the cruise speed: 0x3a (+0xed8 bit 0), or 0x3d once after
// a take-off (+0x1809). Gliding (0) when 0x02 / 0x3a / 0x3d ends; +0x13ce below the cruise speed: state 1.
uint8_t CKHkS08Hero::FlyAnimState02(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if (m_unk1809 == 0) {
            PlayAnimation(0.0f, 0.2f, 0x3a);  // vt+0x184
            m_unk1838 = 0;
            m_unked8 |= 1u;
        } else {
            m_unk1809 = 0;
            PlayAnimation(0.0f, 0.2f, 0x3d);
            m_unked8 |= 0x20u;
        }
        m_unk13c0 = 0.0f;
        m_unkec8 |= 0x18u;
        return 2;
    }
    if (phase == 2) {
        m_unkec8 &= 0xffffffe7u;
        return 2;
    }
    if (phase != 0) return 2;
    const uint32_t flags = m_unkec8;
    if ((flags & 0x400u) != 0) return 0x10;
    if ((flags & 2u) != 0) return 0xf;
    if (m_unk13d8 != 0) return 0xd;
    if (m_unk1438 != 0) return 0xe;
    const uint32_t flagsEcc = m_unkecc;
    if ((flagsEcc & 0x80000u) != 0) return 0x11;
    if (m_unk13a4 != 0) return 3;
    if (m_unk13cc != 0) return 7;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (animation == 2 && (m_unk354 & 0x8000u) != 0) return 0;
    if ((flagsEcc & 0x800000u) != 0) return 8;
    if (m_unk13ce != 0) {
        if (m_unk12c4 < m_unk964) return 1;  // blt
        PlayAnimation(0.0f, 0.2f, 0x3a);
        m_unk13c0 = 0.0f;
        m_unk1838 = 0;
        return 2;
    }
    if ((animation == 0x3a || animation == 0x3d) && (m_unk354 & 0x8000u) != 0) return 0;
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    m_unk13c0 = m_unk13c0 + clock->m_afDeltaTime[0];
    return 2;
}

// 0x00307cf8 CKHkS08Hero_FlyAnimState03_LandingApproach_maybe: the landing approach (+0x13a4): 0x45, then 0x46 with +0xec4 bits 11,
// 12 and 25; the pair weight's approach (+0x1450 = +0xa04, +0x1454 = 1). Past +0xa08 seconds (+0x1448) with the pair at
// 0 the hero is put on the ground (SetMovementMode(0), +0x182c = 0.2); 0x46 ending: state 9. With +0x13d1 (still in
// the air): gliding (0) without +0x13a4, state 4 with +0x13ce.
uint8_t CKHkS08Hero::FlyAnimState03(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x45);  // vt+0x184
        m_unk1838 = 0;
        m_unkec8 |= 0x8018u;
        m_unk144c.y = m_unka04;
        m_unk144c.z = 1.0f;  // TOC +0x2090
        m_unk1448 = 0.0f;
        return 3;
    }
    if (phase == 2) {
        m_unkec4 &= 0xfdffe7ffu;
        m_unkec8 &= 0xffff7fe7u;
        return 3;
    }
    if (phase != 0) return 3;
    if ((m_unkec8 & 2u) != 0) return 0xf;
    if ((m_unkecc & 0x80000u) != 0) return 0x11;
    m_unked8 |= 4u;
    if (m_unk13cf != 0) return 5;
    if (m_unk13d1 == 0) {
        if (m_unk160 == 0x46 && (m_unk354 & 0x8000u) != 0) {
            m_unkec4 &= 0xfdffe7ffu;
            return 9;
        }
        m_unkec4 |= 0x2001800u;
        if (m_unk160 != 0x46) PlayAnimation(0.0f, 0.2f, 0x46);
    } else {
        if (m_unk13a4 == 0) return 0;
        if (m_unk13ce != 0) return 4;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    const float time = m_unk1448 + clock->m_afDeltaTime[0];
    m_unk1448 = time;
    if (m_unka08 < time && m_unk144c.z == 0.0f) {  // bge / bne; TOC +0x208c
        SetMovementMode(0);  // 0x00340c18
        m_unk182c = 0.2f;    // TOC +0x20a0
    }
    return 3;
}

// 0x00307ac8 CKHkS08Hero_FlyAnimState04_Anim44: the landing approach at speed (0x44, the cruise pair of
// UpdateLocomotionAnimationBlend); +0xec8 bit 15 stays set when it leaves. State 3 when 0x44 ends or another animation
// (not a cruise one) runs with +0x13a4, gliding (0) without it.
uint8_t CKHkS08Hero::FlyAnimState04(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x44);  // vt+0x184
        m_unk13c0 = 0.0f;
        m_unk1838 = 0;
        m_unkec8 |= 0x8018u;
        return 4;
    }
    if (phase == 2) {
        m_unkec8 = (m_unkec8 & 0xffff7fe7u) | 0x8000u;
        return 4;
    }
    if (phase != 0) return 4;
    if ((m_unkec8 & 2u) != 0) return 0xf;
    if (m_unk13cf != 0) return 5;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (!IsFlyCruiseAnim(animation)) {
        if (animation != 0x44) return m_unk13a4 == 0 ? 0 : 3;
        if ((m_unk354 & 0x8000u) != 0) return 3;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    m_unk13c0 = m_unk13c0 + clock->m_afDeltaTime[0];
    return 4;
}

// 0x00302808 CKHkS08Hero_FlyAnimState05_Anim43: 0x43 once (no blend; +0xed8 bit 6), +0x13d0 set on entering and cleared
// each frame; gliding (0) when it ends.
uint8_t CKHkS08Hero::FlyAnimState05(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.0f, 0x43);  // vt+0x184
        m_unk13d0 = 1;
        m_unk13c0 = 0.0f;
        m_unked8 |= 0x40u;
        return 5;
    }
    if (phase == 2) {
        m_unk13d0 = 0;
        return 5;
    }
    if (phase != 0) return 5;
    m_unk13d0 = 0;
    if (m_unk160 != 0x43 || (m_unk354 & 0x8000u) != 0) return 0;
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    m_unk13c0 = m_unk13c0 + clock->m_afDeltaTime[0];
    return 5;
}

// 0x00303d48 CKHkS08Hero_FlyAnimState06_Anim3E_3F: the boost (+0x1380 in (0, +0x94c]): 0x3e, then 0x3f (2 s blend,
// +0xec4 bit 19) when it ends. Its time runs at the rate that ends 0x3e's duration when +0x948 seconds (less the
// state's time +0x13c0) are over (rate 1 once 0x3f plays); past the end, or at a negative rate, it skips to the end.
uint8_t CKHkS08Hero::FlyAnimState06(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x3e);  // vt+0x184
        return 6;
    }
    if (phase == 2) {
        m_unkec4 &= 0xfff7ffffu;
        return 6;
    }
    if (phase != 0) return 6;
    if (m_unk13cc != 0) return 7;
    if ((m_unkecc & 0x800000u) != 0) return 8;
    if (m_unk13ce != 0) return !(m_unk12c4 < m_unk964) ? 2 : 1;  // crnor eq, lt, lt
    const float boost = AsF32(m_unk1380);
    if (boost <= 0.0f || m_unk94c < boost) return 0;  // cror lt|eq; blt
    // The dictionary's 0x3e entry (+0x13c +4, word 0x3e): its duration (+0x10), 1 when missing or 0.
    RtAnimAnimation* boostAnim = CAnimationManager_GetAnimation(DictionaryWord(m_pAnimDico, 0x3e));
    float duration;
    if (boostAnim == nullptr || boostAnim->duration == 0.0f) {
        duration = 1.0f;  // TOC +0x2090
    } else {
        duration = boostAnim->duration;
    }
    float rate = (m_unk948 - m_unk13c0) / duration;
    if (m_unk160 == 0x3e && (m_unk354 & 0x8000u) != 0) {
        PlayAnimation(0.0f, 2.0f, 0x3f);  // TOC +0x20b0
        rate = 1.0f;
        m_unkec4 |= 0x80000u;
    }
    if ((m_unkec8 & 0x400u) != 0) return 0xb;
    if (m_unk1838 != 0) return 6;
    if (!(rate < 0.0f)) {  // bge
        const float step = clock->m_afDeltaTime[0] / rate;
        if (!(step + ActiveController(GetAnimBlendSlot())->m_unk50 > duration)) {  // vt+0x194; bgt
            AdvanceAnimTime(step);  // vt+0x188
            return 6;
        }
    }
    SkipAnimToEnd();  // vt+0x18c
    return 6;
}

// 0x00302fe0 CKHkS08Hero_FlyAnimState07_Anim40: 0x40 (+0xed8 bit 1), +0x13cd while in the state; state 14 with +0x1438,
// gliding (0) when 0x40 ends, state 11 with +0xec8 bit 10.
uint8_t CKHkS08Hero::FlyAnimState07(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x40);  // vt+0x184
        m_unked8 |= 2u;
        m_unk13cd = 1;
        return 7;
    }
    if (phase == 2) {
        m_unk13cd = 0;
        return 7;
    }
    if (phase != 0) return 7;
    if (m_unk1438 != 0) return 0xe;
    if (m_unk160 != 0x40 || (m_unk354 & 0x8000u) != 0) return 0;
    if ((m_unkec8 & 0x400u) != 0) return 0xb;
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 7;
}

// 0x00308028 CKHkS08Hero_FlyAnimState08_Anim5B: 0x5b with +0xecc bit 24 (+0xed8 bit 5); gliding (0) when it ends.
uint8_t CKHkS08Hero::FlyAnimState08(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x5b);  // vt+0x184
        m_unkecc |= 0x1000000u;
        m_unked8 |= 0x20u;
        return 8;
    }
    if (phase == 2) {
        m_unkecc &= 0xfeffffffu;
        return 8;
    }
    if (phase != 0) return 8;
    if (m_unk160 == 0x5b && (m_unk354 & 0x8000u) != 0) return 0;
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 8;
}

// 0x00302de0 CKHkS08Hero_FlyAnimState09_Grounded_maybe: on the ground after the landing (0x47, or 0x4b once after a take-off
// (+0x1809); 0x47 again when 0x4b ends). +0x1384: state 12; +0x13d1 (in the air again): gliding (0); faster than
// +0x990 (+0x12d0): state 10.
uint8_t CKHkS08Hero::FlyAnimState09(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (m_unk160 == 0x4b && (m_unk354 & 0x8000u) != 0) PlayAnimation(0.0f, 0.2f, 0x47);  // vt+0x184
        if (m_unk1384 != 0) return 0xc;
        if (m_unk13d1 != 0) return 0;
        if (m_unk12d0 > m_unk990) return 0xa;  // bgt
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 9;
    }
    if (phase == 1) {
        if (m_unk1809 == 0) {
            PlayAnimation(0.0f, 0.2f, 0x47);
        } else {
            m_unk1809 = 0;
            PlayAnimation(0.0f, 0.2f, 0x4b);
        }
    }
    return 9;
}

// 0x003026f8 CKHkS08Hero_FlyAnimState10_Anim48: 0x48 while +0x12d0 is within [+0x994, +0x998] (above: state 11, below:
// state 9); +0x1384: state 12; +0x13d1: gliding (0).
uint8_t CKHkS08Hero::FlyAnimState10(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (m_unk1384 != 0) return 0xc;
        if (m_unk13d1 != 0) return 0;
        if (m_unk998 < m_unk12d0) return 0xb;  // blt
        if (m_unk994 > m_unk12d0) return 9;    // bgt
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0xa;
    }
    if (phase == 1) PlayAnimation(0.0f, 0.2f, 0x48);  // vt+0x184
    return 0xa;
}

// 0x003025f8 CKHkS08Hero_FlyAnimState11_Anim49: 0x49 while +0x12d0 is at least +0x99c (below: state 10); +0x1384:
// state 12; +0x13d1: gliding (0).
uint8_t CKHkS08Hero::FlyAnimState11(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (m_unk1384 != 0) return 0xc;
        if (m_unk13d1 != 0) return 0;
        if (m_unk12d0 < m_unk99c) return 0xa;  // blt
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0xb;
    }
    if (phase == 1) PlayAnimation(0.0f, 0.2f, 0x49);  // vt+0x184
    return 0xb;
}

// 0x00302c98 CKHkS08Hero_FlyAnimState12_Anim4A: 0x4a (+0x13a7 set) until it ends; with +0x13d1 its end goes to state 9.
uint8_t CKHkS08Hero::FlyAnimState12(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        const bool running = m_unk160 == 0x4a && (m_unk354 & 0x8000u) == 0;
        if (m_unk13d1 != 0 && !running) return 9;
        if (running) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0xc;
    }
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x4a);  // vt+0x184
        m_unk13a7 = 1;
    }
    return 0xc;
}

// 0x00304090 CKHkS08Hero_FlyAnimState13_NoAnim: the flying push (+0x13d8): 0x4c / 0x4d (0x4e / 0x4f with +0xec8 bit 16;
// the second with +0x13d9), +0xec8 bits 22 / 23; with +0x1384 the end pose 0x50 / 0x51. Gliding (0) when +0x13d8 is
// clear and 0x50 / 0x51 is not running; state 11 with +0xec8 bit 10.
uint8_t CKHkS08Hero::FlyAnimState13(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        uint16_t animation;
        if ((m_unkec8 & 0x10000u) == 0) {
            animation = m_unk13d9 == 0 ? 0x4c : 0x4d;
        } else {
            animation = m_unk13d9 == 0 ? 0x4e : 0x4f;
        }
        PlayAnimation(0.0f, 0.2f, animation);  // vt+0x184
        m_unkec8 |= 0xc00000u;
        return 0xd;
    }
    if (phase == 2) {
        m_unkec8 &= 0xff3fffffu;
        return 0xd;
    }
    if (phase != 0) return 0xd;
    int16_t first = 0x4c;
    int16_t second = 0x4d;
    if ((m_unkec8 & 0x10000u) != 0) {
        first = 0x4e;
        second = 0x4f;
    }
    const int16_t current = static_cast<int16_t>(m_unk160);
    if (first != current && second != current && m_unk13d8 != 0) {
        PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(m_unk13d9 == 0 ? first : second));
    }
    if (m_unk1384 != 0) {
        PlayAnimation(0.0f, 0.2f, m_unk13d9 == 0 ? 0x50 : 0x51);
        return 0xd;
    }
    if (m_unk13d8 == 0) {
        const int16_t animation = static_cast<int16_t>(m_unk160);
        if (animation != 0x50 && animation != 0x51) return 0;
        if ((m_unk354 & 0x8000u) != 0) return 0;
    }
    if ((m_unkec8 & 0x400u) != 0) return 0xb;
    AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 0xd;
}

// 0x00302bb0 CKHkS08Hero_FlyAnimState14_Anim52: 0x52 until it ends, then gliding (0).
uint8_t CKHkS08Hero::FlyAnimState14(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if (m_unk160 != 0x52 || (m_unk354 & 0x8000u) != 0) return 0;
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0xe;
    }
    if (phase == 1) PlayAnimation(0.0f, 0.2f, 0x52);  // vt+0x184
    return 0xe;
}

// 0x003083d0 CKHkS08Hero_FlyAnimState15_NoAnim: the push / pull in the air (+0xec8 bit 1) in the direction +0x1228 (2:
// 0x53, 3: 0x54; 4: none, gliding again) with its flags and the camera service's temporary flag 27 (+0x46c) as
// GroundAnimState12; the animation's time is kept in +0x122c. Gliding (0) when it ends.
uint8_t CKHkS08Hero::FlyAnimState15(IKTime* clock, int32_t phase, uint8_t) {
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x20ec)
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (phase == 1) {
        if (m_unk1228 == 2) {
            PlayAnimation(0.0f, 0.2f, 0x53);  // vt+0x184
        } else if (m_unk1228 == 3) {
            PlayAnimation(0.0f, 0.2f, 0x54);
        }
        m_unk354 |= 0x800u;
        m_unked8 |= 0x80u;
        camera->m_baTemporaryFlags |= 0x8000000u;
        m_unkec8 |= 0xc00080u;
        return 0xf;
    }
    if (phase == 2) {
        m_unkec8 &= 0xfffffffdu;
        m_unk122c = 0.0f;
        m_unk1228 = 4;
        m_unkec4 &= 0xffdfd3ffu;
        m_unk354 &= 0xfffff7ffu;
        m_unkec8 &= 0xff3fffffu;
        camera->m_baTemporaryFlags &= 0xf7ffffffu;
        m_unk1248 = kNullVector.x;
        m_unk1250 = kNullVector.z;
        m_unk124c = kNullVector.y;
        m_unkec8 &= 0xffffff7fu;
        return 0xf;
    }
    if (phase != 0) return 0xf;
    if ((m_unkecc & 0x800000u) != 0) return 8;
    if (m_unk13ce != 0) return !(m_unk12c4 < m_unk964) ? 2 : 1;  // crnor eq, lt, lt
    const uint8_t direction = m_unk1228;
    if (direction == 3 || direction == 2) {
        const uint16_t animation = direction == 3 ? 0x54 : 0x53;
        if (m_unk160 != animation) {
            PlayAnimation(0.0f, 0.2f, animation);
            return 0xf;
        }
        if ((m_unk354 & 0x8000u) != 0) return 0;
    } else if (direction == 4) {
        return 0;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    m_unk122c = ActiveController(GetAnimBlendSlot())->m_unk50;  // vt+0x194
    return 0xf;
}

// 0x00304d00 CKHkS08Hero_FlyAnimState16_NoAnim: the carried / grabbed state of +0xec8 bit 10 has no animation here: its
// update and enter answer gliding (0) at once; leaving clears the carried flags as GroundAnimState11's exit (with +0xec8
// bit 18, bit 19 is set).
uint8_t CKHkS08Hero::FlyAnimState16(IKTime*, int32_t phase, uint8_t) {
    if (phase < 0) return 0x10;
    if (phase <= 1) return 0;
    if (phase != 2) return 0x10;
    if ((m_unkec8 & 0x40000u) != 0) m_unkec8 |= 0x80000u;
    m_unkec8 &= 0xfffbc1ffu;
    m_unk354 &= 0xfffff7ffu;
    m_unkec4 &= 0xffdfd3ffu;
    m_unkec8 &= 0xcd3fff7fu;
    return 0x10;
}

// 0x003081a0 CKHkS08Hero_FlyAnimState17_Anim55: 0x55 (+0xecc bit 19) with +0xec4 bits 10, 11, 13, 21, +0x354 bit 11,
// +0xec8 bit 8, +0xed8 bit 7; the gravity +0x11d8 = +0xa0c each frame. When it ends the hero is put on the ground
// (SetMovementMode(0)) unless +0xec4 bit 18, and the state answers gliding (0).
uint8_t CKHkS08Hero::FlyAnimState17(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x55);  // vt+0x184
        m_unkec4 |= 0x202c00u;
        m_unk354 |= 0x800u;
        m_unkec8 |= 0x100u;
        m_unked8 |= 0x80u;
        return 0x11;
    }
    if (phase == 2) {
        m_unkec8 &= 0xff3fffffu;
        m_unkec4 &= 0xffdfd3ffu;
        m_unk354 &= 0xfffff7ffu;
        m_unkec8 &= 0xfffffeffu;
        return 0x11;
    }
    if (phase != 0) return 0x11;
    if (m_unk160 == 0x55 && (m_unk354 & 0x8000u) != 0) {
        if ((m_unkec4 & 0x40000u) == 0) SetMovementMode(0);  // 0x00340c18
        return 0;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    std::memcpy(&m_unk11d8, &m_unka0c, 4);  // lfs / stfs: a float in the word +0x11d8
    return 0x11;
}

// ---- step 6 ANIM: the climbing animation sub-machine (+0x1964, current state +0x19a8) ----
//
// The states' shared answers (the climbing locomotion of CKHkS08Hero_11 sets them): +0xecc bit 17 (state 7), +0xec8
// bit 0 (5: the climb's end), +0xec8 bit 31 (6), +0x1626 (2), +0xec4 bits 29 / 30 (4), +0x1678 with +0x167d clear (3),
// +0x161f (1: moving).

namespace {
// 0x00a705f0 (TOC +0x209c): the hero's animation table the idle variations share (UpdateIdleVariationAnim), read here
// from +0x14 (by +0x1740) and +0x40 / +0x64 / +0x88 / +0xac (four rows by the climb kind +0x1664; the low half of each
// word is the animation). Copied from the EBOOT image.
const uint32_t kHeroAnimTable[52] = {
    0x02, 0x03, 0x04, 0x05, 0x06, 0x89, 0x8a, 0x77, 0x81, 0x78, 0x7c, 0x79, 0x7d,  // +0x00
    0x8d, 0x81, 0x81, 0x68, 0x6a, 0x69, 0x6b, 0x6c, 0x68, 0x6a, 0x69, 0x6c, 0x6d,  // +0x34
    0x6f, 0x6e, 0x70, 0x71, 0x6d, 0x6f, 0x6e, 0x71, 0x72, 0x74, 0x73, 0x75, 0x76,  // +0x68
    0x72, 0x74, 0x73, 0x76, 0x77, 0x79, 0x78, 0x7a, 0x7b, 0x77, 0x79, 0x78, 0x7b,  // +0x9c
};
// The word at byte offset `offset` + 4 x `index` of the table.
uint32_t HeroAnimTableWord(uint32_t offset, int32_t index) {
    return kHeroAnimTable[static_cast<int32_t>(offset / 4u) + index];
}
}  // namespace

// 0x00303878 CKHkS08Hero_ClimbAnimState00_NoAnim: hanging still: 0x5c (0x5d with +0xec8 bit 16), cut in with +0xecc
// bit 0 (cleared) or blended over 0.2 s; its time runs while no answer comes.
uint8_t CKHkS08Hero::ClimbAnimState00(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 0) {
        if ((m_unkecc & 0x20000u) != 0) return 7;
        const uint32_t flags = m_unkec8;
        if ((flags & 1u) != 0) return 5;
        if (m_unk1626 != 0) return 2;
        const uint32_t flagsEc4 = m_unkec4;
        if ((flagsEc4 & 0x20000000u) != 0 || (flagsEc4 & 0x40000000u) != 0) return 4;
        if (static_cast<int32_t>(flags) < 0) return 6;
        if (m_unk1678 != 0 && m_unk167d == 0) return 3;
        if (m_unk161f != 0) return 1;
        if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
        return 0;
    }
    if (phase != 1) return 0;
    const uint16_t animation = (m_unkec8 & 0x10000u) == 0 ? 0x5c : 0x5d;
    if ((m_unkecc & 1u) != 0) {
        PlayAnimation(0.0f, 0.0f, animation);  // vt+0x184
        m_unkecc &= 0xfffffffeu;
        return 0;
    }
    PlayAnimation(0.0f, 0.2f, animation);
    return 0;
}

// 0x003054e0 CKHkS08Hero_ClimbAnimState01_Anim5F_65_67_63: climbing along: by the move bytes +0x168c / +0x168d /
// +0x168e the animations 0x5f / 0x62 / 0x63 (0x65 / 0x66 / 0x67 with +0xec8 bit 16; +0x168e sets +0xed8 bit 20), their
// time scaled by the speed (+0x12d0, or the velocity's length while ShouldStayClimbing) over 2, or plain with +0x168e.
// Hanging still (0) with +0x161c.
uint8_t CKHkS08Hero::ClimbAnimState01(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if (ShouldStayClimbing() == 0) {  // 0x00342fa8
            PlayAnimation(0.0f, 0.2f, 0x5f);  // vt+0x184
            return 1;
        }
        if ((m_unkec8 & 0x10000u) != 0) {
            if (m_unk168d != 0) {
                PlayAnimation(0.0f, 0.2f, 0x67);
            } else if (m_unk168c != 0) {
                PlayAnimation(0.0f, 0.2f, 0x65);
            }
        } else if (m_unk168e != 0) {
            PlayAnimation(0.0f, 0.2f, 0x63);
        } else if (m_unk168d != 0) {
            PlayAnimation(0.0f, 0.2f, 0x62);
        } else if (m_unk168c != 0) {
            PlayAnimation(0.0f, 0.2f, 0x5f);
        }
        return 1;
    }
    if (phase != 0) return 1;
    if ((m_unkecc & 0x20000u) != 0) return 7;
    if (m_unk168e != 0) m_unked8 |= 0x100000u;
    const uint32_t flags = m_unkec8;
    if ((flags & 1u) != 0) return 5;
    if (static_cast<int32_t>(flags) < 0) return 6;
    if (m_unk1678 != 0 && m_unk167d == 0) return 3;
    if (m_unk1626 != 0) return 2;
    if ((m_unkec4 & 0x20000000u) != 0 || (m_unkec4 & 0x40000000u) != 0) return 4;
    // The four animations of the side (+0xec8 bit 16): sideways (+0x168e), along (+0x168c), the turn (+0x168d) and
    // the one +0x168c leads to.
    int16_t sideways = 0x63;
    int16_t along = 0x5f;
    int16_t turn = 0x62;
    if ((flags & 0x10000u) != 0) {
        sideways = 0x67;
        along = 0x65;
        turn = 0x66;
    }
    int16_t animation = static_cast<int16_t>(m_unk160);
    bool playTurn = true;
    bool checkAlong = true;
    if (animation != sideways) {
        if (m_unk168e != 0) {
            PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(sideways));
            animation = static_cast<int16_t>(m_unk160);
        }
        if (animation == along) checkAlong = false;
    }
    if (checkAlong) {
        if (m_unk168c != 0) {
            PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(along));
            animation = static_cast<int16_t>(m_unk160);
        }
        if (animation == turn) playTurn = false;
    }
    if (playTurn && m_unk168d != 0 && m_unk168e == 0) PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(turn));
    if (m_unk1678 != 0 && m_unk167d == 0) return 3;
    if (m_unk161c != 0) return 0;
    if (m_unk1838 != 0) return 1;
    float speed = m_unk12d0;
    if (ShouldStayClimbing() != 0) {  // 0x00342fa8
        speed = std::sqrt(ppc::fmadds(m_unk1284, m_unk1284, ppc::fmadds(m_unk127c, m_unk127c, m_unk1280 * m_unk1280)));  // 0x00010690
    }
    if (m_unk168e == 0) {
        AdvanceAnimScaled(clock->m_afDeltaTime[0], 2.0f, speed, 0);  // 0x00301e70; TOC +0x20b0
        return 1;
    }
    AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 1;
}

// 0x003068e0 CKHkS08Hero_ClimbAnimState02_Anim8B: the climb kind's (+0x1664) animations of the table rows: the entry
// (+0x40, 0.04 s blend), up / down by the vertical speed (+0x64 rising, +0x88 falling), the grab of +0x1623 (+0x64,
// +0xed8 bit 16; kind 8: 0x8b), the hold of +0x1627 (+0xac); 0x8b ending sets +0xecc bit 15. Without the climb flags
// (GetClimbFlag1627Or1626And1628): state 3 while ShouldStayClimbing, else 0.
uint8_t CKHkS08Hero::ClimbAnimState02(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.04f, static_cast<uint16_t>(HeroAnimTableWord(0x40, m_unk1664)));  // vt+0x184; TOC +0x20a4
        return 2;
    }
    if (phase != 0) return 2;
    const uint8_t kind = m_unk1664;
    const int16_t current = static_cast<int16_t>(m_unk160);
    const uint32_t rising = HeroAnimTableWord(0x64, kind);
    if (current == static_cast<int16_t>(rising)) {
        if (m_unk1280 < 0.0f) {  // bge
            PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(HeroAnimTableWord(0x88, kind)));
            return 2;
        }
    } else if (current == static_cast<int16_t>(HeroAnimTableWord(0x88, kind))) {
        if (m_unk1280 > 0.0f) {  // ble
            PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(rising));
            return 2;
        }
    }
    if (m_unk1623 != 0) {
        if (kind != 8) {
            PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(rising));
            m_unked8 |= 0x10000u;
            return 2;
        }
        m_unked8 |= 0x10000u;
        PlayAnimation(0.0f, 0.04f, 0x8b);
    }
    if (m_unk1627 != 0) {
        const uint32_t hold = HeroAnimTableWord(0xac, m_unk1664);
        if (static_cast<int16_t>(m_unk160) != static_cast<int16_t>(hold)) {
            PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(hold));
            return 2;
        }
    }
    if (GetClimbFlag1627Or1626And1628() == 0) return ShouldStayClimbing() != 0 ? 3 : 0;  // 0x0031d880, 0x00342fa8
    const int32_t index = m_unk1664;
    const int32_t now = static_cast<int16_t>(m_unk160);
    const bool ended = (m_unk354 & 0x8000u) != 0;
    // The entry (+0x40) or the hold (+0xac) still running, or the up / down animation: the time runs (0x8b ending
    // instead sets +0xecc bit 15); any other animation but 0x8b: nothing.
    bool runs = (static_cast<int32_t>(HeroAnimTableWord(0x40, index) & 0xffffu) == now && !ended) ||
                (static_cast<int32_t>(HeroAnimTableWord(0xac, index) & 0xffffu) == now && !ended) ||
                now == static_cast<int16_t>(HeroAnimTableWord(0x88, index)) ||
                now == static_cast<int16_t>(HeroAnimTableWord(0x64, index));
    if (now == 0x8b || !runs) {
        if (now != 0x8b) return 2;
        if (ended) {
            m_unkecc |= 0x8000u;
            return 2;
        }
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 2;
}

// 0x00306708 CKHkS08Hero_ClimbAnimState03_NoAnim: the animation of +0x1740 (table +0x14) with +0xed8 bit 18 and +0xecc
// bit 27 (cleared on leaving, +0x16f9 set). Hanging still (0) without +0x1678 or when it ends; moving (1) with +0xedc
// bit 9 and the turn amount +0x1378 above 0.5.
uint8_t CKHkS08Hero::ClimbAnimState03(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, static_cast<uint16_t>(HeroAnimTableWord(0x14, static_cast<int32_t>(m_unk1740))));
        m_unked8 |= 0x40000u;
        m_unkecc |= 0x8000000u;
        return 3;
    }
    if (phase == 2) {
        m_unk16f9 = 1;
        m_unkecc &= 0xf7ffffffu;
        return 3;
    }
    if (phase != 0) return 3;
    if (m_unk1678 == 0) return 0;
    const uint32_t animation = HeroAnimTableWord(0x14, static_cast<int32_t>(m_unk1740)) & 0xffffu;
    if (static_cast<int32_t>(static_cast<int16_t>(m_unk160)) == static_cast<int32_t>(animation) &&
        (m_unk354 & 0x8000u) != 0) {
        return 0;
    }
    if ((m_unkedc & 0x200u) != 0 && !(m_unk1378 <= 0.5f)) return 1;  // ble; TOC +0x20b8
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 3;
}

// 0x003047a8 CKHkS08Hero_ClimbAnimState04_NoAnim: the climb's turn (+0xec4 bit 29: 0x85, bit 30: 0x86; +0xed8 bit 22).
// When it ends: hanging still (0) with the stick's x (+0x378) within 0.5, else moving (1) to the side it points
// (+0x168c / +0x168d). Leaving clears the two bits and takes the hero off its climb zones (+0x16a4 / +0x16a8).
uint8_t CKHkS08Hero::ClimbAnimState04(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if ((m_unkec4 & 0x20000000u) != 0) {
            PlayAnimation(0.0f, 0.2f, 0x85);  // vt+0x184
        } else if ((m_unkec4 & 0x40000000u) != 0) {
            PlayAnimation(0.0f, 0.2f, 0x86);
        }
        m_unked8 |= 0x400000u;
        return 4;
    }
    if (phase == 2) {
        m_unkec4 &= 0x9fffffffu;
        if (m_unk16a4 != nullptr) m_unk16a4->RemoveClimber(CKHkClimbZone::ClimberKey(this));  // 0x00457180
        if (m_unk16a8 != nullptr) m_unk16a8->RemoveClimber(CKHkClimbZone::ClimberKey(this));
        m_unk16c4 = 0;
        m_unk16b8 = 0;
        return 4;
    }
    if (phase != 0) return 4;
    if (m_unk1626 != 0) return 2;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if ((animation == 0x85 || animation == 0x86) && (m_unk354 & 0x8000u) != 0) {
        if (!(std::fabs(m_unk378) > 0.5f)) return 0;  // the sign bit cleared through the stack; bgt; TOC +0x20b8
        if (!(m_unk378 <= 0.0f)) {  // ble
            m_unk168d = 0;
            m_unk168c = 1;
        } else {
            m_unk168d = 1;
            m_unk168c = 0;
        }
        return 1;
    }
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 4;
}

// 0x00309e68 CKHkS08Hero_ClimbAnimState05_ClimbEnd_maybe: the climb's end (0x88, 0.15 s blend; 0x87 cut in with +0xec4 bit
// 31, cleared): when 0x87 ends the hero is put on the ground (SetMovementMode(0)); each frame the hero lands
// (SetDirectionLock(0)). Leaving clears +0xec8 bit 0 and, with fewer than two controlled heroes and the group's +0x2c8
// bit 12 clear, sets +0xed0 bit 2 of the group's first companion hero.
uint8_t CKHkS08Hero::ClimbAnimState05(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.15f, 0x88);  // vt+0x184; TOC +0x20fc
        return 5;
    }
    if (phase == 2) {
        m_unkec8 &= 0xfffffffeu;
        SetDirectionLock(0);  // 0x009bdb48 inlined: 0x00354cf0 and the +0x354 / +0x364 / +0x590 stores
        CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
        if (group->m_ui8ControlledHeroCount <= 1 && (group->m_unk2c8 & 0x1000u) == 0) {  // 0x002ca288
            static_cast<CKHkS08Hero*>(group->m_apCompanionHeroes[0])->m_unked0 |= 4u;
        }
        return 5;
    }
    if (phase != 0) return 5;
    if (static_cast<int32_t>(m_unkec4) < 0) {
        PlayAnimation(0.0f, 0.0f, 0x87);
        m_unkec4 &= 0x7fffffffu;
    }
    if (m_unk160 == 0x87 && (m_unk354 & 0x8000u) != 0) {
        SetMovementMode(0);  // 0x00340c18
    } else {
        AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    }
    SetDirectionLock(0);  // 0x009bdb48 inlined
    return 5;
}

// 0x00303698 CKHkS08Hero_ClimbAnimState06_NoAnim: 0x89 / 0x8a by +0x1740 (0 / 1; else none) with +0xed8 bit 21 and
// +0xecc bit 27; hanging still (0) when it ends. Leaving clears +0xec8 bit 31 and +0xecc bit 27.
uint8_t CKHkS08Hero::ClimbAnimState06(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        if (m_unk1740 == 0) {
            PlayAnimation(0.0f, 0.2f, 0x89);  // vt+0x184
        } else if (m_unk1740 == 1) {
            PlayAnimation(0.0f, 0.2f, 0x8a);
        }
        m_unked8 |= 0x200000u;
        m_unkecc |= 0x8000000u;
        return 6;
    }
    if (phase == 2) {
        m_unkec8 &= 0x7fffffffu;
        m_unkecc &= 0xf7ffffffu;
        return 6;
    }
    if (phase != 0) return 6;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if ((animation == 0x89 || animation == 0x8a) && (m_unk354 & 0x8000u) != 0) return 0;
    AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 6;
}

// 0x00306cf0 CKHkS08Hero_ClimbAnimState07_Anim8C: 0x8c (+0xed8 bit 23) until it ends, then moving (1); leaving clears
// +0xecc bit 17.
uint8_t CKHkS08Hero::ClimbAnimState07(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayAnimation(0.0f, 0.2f, 0x8c);  // vt+0x184
        m_unked8 |= 0x800000u;
        return 7;
    }
    if (phase == 2) {
        m_unkecc &= 0xfffdffffu;
        return 7;
    }
    if (phase != 0) return 7;
    if (m_unk160 == 0x8c && (m_unk354 & 0x8000u) != 0) return 1;
    if (m_unk1838 == 0) AdvanceAnimTime(clock->m_afDeltaTime[0]);  // vt+0x188
    return 7;
}

// 0x0030a0d8 CKHkS08Hero_AnimState9_LocomotionClimb: the animation state while climbing runs the climbing animation
// sub-machine (handlers +0x1964 through +0x19a4, current state +0x19a8): entering restarts it in state 0, leaving exits
// it.
uint8_t CKHkS08Hero::AnimLocomotionClimb(IKTime* clock, int32_t phase, uint8_t other) {
    const uint32_t* handlers = static_cast<const uint32_t*>(m_unk19a4);
    if (phase == 1) {
        const uint8_t previous = m_unk19a8;
        if (previous != 0xff) CallStateHandler(&handlers[previous * 2u], clock, 2, 0);
        m_unk19a8 = 0;
        CallStateHandler(&handlers[0], clock, 1, previous);
        return other;
    }
    if (phase == 2) {
        if (m_unk19a8 != 0xff) CallStateHandler(&handlers[m_unk19a8 * 2u], clock, 2, 0xff);
        m_unk19a8 = 0xff;
        return other;
    }
    if (phase == 0) RunState(handlers, m_unk19a8, clock);
    return other;
}

// 0x0030a518 CKHkS08Hero_AnimState8_LocomotionFlying: the animation state while flying runs the flying animation
// sub-machine (handlers +0x183c through +0x18cc, current state +0x18d0). Entering clears +0x13c0..+0x13c8, plays the
// cruise 0x3a (0.2 s blend), clears +0x13a6 / +0x13a7 and restarts the sub-machine in state 9 (on the ground, 0x47)
// without +0x13d1, else gliding (0); leaving exits it and clears +0x1838, +0xec4 bit 19 and +0xecc bits 11 / 12.
uint8_t CKHkS08Hero::AnimLocomotionFlying(IKTime* clock, int32_t phase, uint8_t other) {
    const uint32_t* handlers = static_cast<const uint32_t*>(m_unk18cc);
    if (phase == 0) {
        RunState(handlers, m_unk18d0, clock);
        return other;
    }
    if (phase == 1) {
        m_unk13c4 = 0.0f;  // TOC +0x208c
        m_unk13c8 = 0.0f;
        m_unk13c0 = 0.0f;
        PlayAnimation(0.0f, 0.2f, 0x3a);  // vt+0x184; TOC +0x20a0
        m_unk13a7 = 0;
        m_unk13a6 = 0;
        const uint8_t previous = m_unk18d0;
        const uint8_t first = m_unk13d1 == 0 ? 9 : 0;
        if (previous != 0xff) CallStateHandler(&handlers[previous * 2u], clock, 2, first);
        m_unk18d0 = first;
        CallStateHandler(&handlers[first * 2u], clock, 1, previous);
        return 0;
    }
    m_unk13c8 = 0.0f;
    m_unk13c4 = 0.0f;
    if (m_unk18d0 != 0xff) CallStateHandler(&handlers[m_unk18d0 * 2u], clock, 2, 0xff);
    m_unk18d0 = 0xff;
    m_unk1838 = 0;
    m_unkec4 &= 0xfff7ffffu;
    m_unkecc &= 0xffffe7ffu;
    return 0;
}

// 0x00301408 CKHkS08Hero_AdvanceAnimTimeUnlessMarkOverride_maybe: the animation time advanced (vt+0x188) unless +0x1838.
void CKHkS08Hero::AdvanceAnimTimeUnlessMarkOverride(float dt) {
    if (m_unk1838 != 0) return;
    AdvanceAnimTime(dt);  // vt+0x188
}

// 0x00302f90 StaticInitAndDestruction_302f90: two file statics (0x00ceae04, 0x00ceae08) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae04 = -1.0f;
[[maybe_unused]] float s_unkceae08 = -1.0f;
}  // namespace
