//
// Reconstructed original translation unit: 0x3ee198-0x3f2ff0 (GAME_TOC1, main_toc1), 72 functions, 71 live.
// Primary owner: CKS08HeroAbilityHost (not a registered class)
// Other owners: HeroAbilityOwner (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3ee198  HeroAbilityOwner_Construct2  (the constructor twice (one body))
//   [x] 0x3ee210  CKS08HeroAbilityHost_maybe_GetHero
//   [x] 0x3ee218  CKS08HeroAbilityHost_maybe_SetHeroPosition
//   [x] 0x3ee240  CKS08HeroAbilityHost_maybe_GetHeroPosition
//   [x] 0x3ee270  CKS08HeroAbilityHost_maybe_Slot40Switch_maybe
//   [x] 0x3ee3e0  CKS08HeroAbilityHost_maybe_SetAbilityMoveSpeedEnabled
//   [x] 0x3ee3f0  CKS08HeroAbilityHost_maybe_ClearAbilityImpulse_maybe
//   [x] 0x3ee438  CKS08HeroAbilityHost_maybe_SetHeroEc4Bit27
//   [x] 0x3ee460  CKS08HeroAbilityHost_maybe_SetHeroEd4Bit0_maybe
//   [x] 0x3ee488  CKS08HeroAbilityHost_maybe_SetHero1d20
//   [x] 0x3ee498  CKS08HeroAbilityHost_maybe_SetHero1d11
//   [x] 0x3ee4a8  CKS08HeroAbilityHost_maybe_vfA0
//   [x] 0x3ee4b0  CKS08HeroAbilityHost_maybe_vfA4
//   [x] 0x3ee4b8  CKS08HeroAbilityHost_maybe_vfA8
//   [x] 0x3ee4c0  CKS08HeroAbilityHost_maybe_vfAC
//   [x] 0x3ee4c8  CKS08HeroAbilityHost_maybe_GetCollisionGroup
//   [x] 0x3ee4d0  CKS08HeroAbilityHost_maybe_GetCollisionMask
//   [x] 0x3ee4d8  CKS08HeroAbilityHost_maybe_GetLockedTarget
//   [x] 0x3ee500  CKS08HeroAbilityHost_maybe_GetGrabPullRatio_maybe
//   [x] 0x3ee600  CKS08HeroAbilityHost_maybe_GetHeroEccBit1
//   [x] 0x3ee610  CKS08HeroAbilityHost_maybe_vfF8
//   [x] 0x3ee618  CKS08HeroAbilityHost_maybe_IsProjectileChargeHeld_maybe
//   [x] 0x3ee6a0  CKS08HeroAbilityHost_maybe_GetHeroAttachmentSets
//   [x] 0x3ee6b0  CKS08HeroAbilityHost_maybe_Destructor  (the implicit destructor (the base vtable))
//   [x] 0x3ee6c0  CKS08HeroAbilityHost_maybe_GetGrabState_maybe
//   [x] 0x3ee890  CKS08HeroAbilityHost_maybe_CanGrabTarget_maybe
//   [x] 0x3ee9f0  CKS08HeroAbilityHost_maybe_GetManaCostScale
//   [x] 0x3eea18  CKS08HeroAbilityHost_maybe_GetEffectScale
//   [x] 0x3eea68  CKS08HeroAbilityHost_maybe_GetDamageScale
//   [x] 0x3eea90  CKS08HeroAbilityHost_maybe_GetHeroA78_maybe
//   [x] 0x3eeaf8  CKS08HeroAbilityHost_maybe_SetAbilityTurnParams_maybe
//   [x] 0x3eed48  CKS08HeroAbilityHost_maybe_SetAbilityMoveSpeed
//   [x] 0x3eee50  CKS08HeroAbilityHost_maybe_SelectByMovementContext
//   [x] 0x3eef28  CKS08HeroAbilityHost_maybe_CanUseAltLoopAnim_maybe
//   [x] 0x3eeff0  CKS08HeroAbilityHost_maybe_GetHero4dc_maybe
//   [x] 0x3ef018  CKS08HeroAbilityHost_maybe_Slot24_maybe
//   [x] 0x3ef058  CKS08HeroAbilityHost_maybe_Slot20_maybe
//   [x] 0x3ef098  CKS08HeroAbilityHost_maybe_SetAbilityCooldown
//   [x] 0x3ef1d8  CKS08HeroAbilityHost_maybe_PlayAbilityAnim
//   [x] 0x3ef560  CKS08HeroAbilityHost_maybe_GetHeroTargetPoint_maybe
//   [x] 0x3ef5a0  CKS08HeroAbilityHost_maybe_GetHeroVelocity_maybe
//   [x] 0x3ef5d0  CKS08HeroAbilityHost_maybe_SetAbilityImpulse_maybe
//   [x] 0x3ef660  CKS08HeroAbilityHost_maybe_GetHeroVec135c_maybe
//   [x] 0x3ef690  CKS08HeroAbilityHost_maybe_GetHeroForward_maybe
//   [x] 0x3ef6c8  CKS08HeroAbilityHost_maybe_GetHeroVec570_maybe
//   [x] 0x3ef6f8  CKS08HeroAbilityHost_maybe_GetHotspot
//   [x] 0x3ef830  StaticInitAndDestruction_3ef830  (the two file statics at the end)
//   [ ] 0x3ef860  _GLOBAL__D_3ef860
//   [ ] 0x3ef870  _GLOBAL__I_3ef870
//   [x] 0x3ef880  CKS08HeroAbilityHost_maybe_GetHeroUp_maybe
//   [x] 0x3ef8b8  CKS08HeroAbilityHost_maybe_GetHeroRight_maybe
//   [x] 0x3ef8f0  CKS08HeroAbilityHost_maybe_GetAbilityLevelIndex
//   [x] 0x3ef9b8  CKS08HeroAbilityHost_maybe_ConsumeAbilityMana
//   [x] 0x3efac0  CKS08HeroAbilityHost_maybe_IsAbilityButtonDown_maybe
//   [x] 0x3efb48  CKS08HeroAbilityHost_maybe_GetTargetAimPoint_maybe
//   [x] 0x3efcb0  CKS08HeroAbilityHost_maybe_GetHeroSpeedForAbility_maybe
//   [x] 0x3efd80  CKS08HeroAbilityHost_maybe_GetAbilityButtonHoldTime_maybe
//   [x] 0x3efe70  CKS08HeroAbilityHost_maybe_IsAbilityButtonReleased_maybe
//   [x] 0x3efef8  CKS08HeroAbilityHost_maybe_SetAbilityParam11f8_maybe
//   [x] 0x3f00c8  CKS08HeroAbilityHost_maybe_GrabEnemy_maybe
//   [x] 0x3f0808  CKS08HeroAbilityHost_maybe_AimAtTarget_maybe
//   [x] 0x3f0a80  CKS08HeroAbilityHost_maybe_GetHotspotPosition
//   [x] 0x3f0b48  CKS08HeroAbilityHost_maybe_IsAbilityAnimPhaseDone_maybe
//   [x] 0x3f0ec8  CKS08HeroAbilityHost_maybe_Construct
//   [x] 0x3f0f40  CKS08HeroAbilityHost_maybe_GetAbilityMana
//   [x] 0x3f0fa0  CKS08HeroAbilityHost_maybe_IsOnGround_maybe
//   [x] 0x3f1040  CKS08HeroAbilityHost_maybe_SetAbilityHeroMode
//   [ ] 0x3f13d0  CKS08HeroAbilityHost_maybe_Destructor_2  [dead]
//   [x] 0x3f13e0  CKS08HeroAbilityHost_maybe_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x3f1410  CKS08HeroAbilityHost_maybe_SetAbilityAttackSpheres
//   [x] 0x3f18f8  CKS08HeroAbilityHost_maybe_SetHeroActionPermission
//   [x] 0x3f1ea8  CKS08HeroAbilityHost_maybe_ComputeAimDirection_maybe
#include "Spyro2008/misc/CKS08HeroAbilityHost.h"

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameState.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/logic/CKAbilityElement.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include <cmath>
#include <cstring>
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/Math.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Vec3.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/hooks/CKHkS08ElectricGauge.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/logic/CKGrabElement.h"
#include "k2000/logic/cameras/CKAimCamembert.h"

// 0x003f0ec8 CKS08HeroAbilityHost_maybe_Construct
CKS08HeroAbilityHost::CKS08HeroAbilityHost(IKSerializable* hero) {
    if (hero->IsKindOfClass(0x25c2) != 0) m_pHero = static_cast<CKHkS08Hero*>(hero);  // vt+0x08
}

// 0x003ee210 CKS08HeroAbilityHost_maybe_GetHero (the base's vt+0x08)
IKSerializable* CKS08HeroAbilityHost::GetOwner() { return m_pHero; }

namespace {
// 0x00b01050 (TOC +0x43c0): per dragon (0x00c40a08 / 0x00c40a20), the hero slot of each ability id (0xff: not the dragon's).
constexpr uint8_t kAbilitySlotOfId[2][21] = {
    {0, 1, 3, 2, 5, 4, 6, 7, 8, 9, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
    {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 1, 255, 3, 2, 4, 5, 6, 7, 8, 9},
};
// 0x00b01048: per dragon (0x00c409d8 / 0x00c409f0), the element of each ability id.
constexpr uint8_t kAbilityElementOfId[2][21] = {
    {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
    {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 1, 1, 2, 4, 3, 3, 4, 2},
};
// The ability animations [context][dragon][slot][phase 0..4] (0xffff: none): TOC +0x43c8 flying, +0x43d0 on the
// ground (vt+0x30 set), +0x43d8 in the air.
constexpr uint16_t kAbilityAnims[3][2][10][5] = {
    // flying (0x00b01058)
    {
        {{0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xec, 0xed, 0xee, 0xffff, 0xef}, {0xffff, 0xe5, 0xffff, 0xffff, 0xffff}, {0xf0, 0xf4, 0xffff, 0xf2, 0xf3}, {0xffff, 0xe2, 0xffff, 0xffff, 0xe3}, {0xf0, 0xf1, 0xffff, 0xf2, 0xf3}, {0xffff, 0xe4, 0xffff, 0xffff, 0xffff}, {0xec, 0xed, 0xee, 0xffff, 0xef}, {0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xec, 0xed, 0xee, 0xffff, 0xef}},
        {{0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xf0, 0xf1, 0xffff, 0xf2, 0xf3}, {0xe2, 0xe3, 0xffff, 0xffff, 0xe4}, {0xec, 0xed, 0xffff, 0xffff, 0xef}, {0xf0, 0xf1, 0xffff, 0xf2, 0xf3}, {0xec, 0xed, 0xffff, 0xffff, 0xef}, {0xffff, 0xe5, 0xffff, 0xffff, 0xffff}, {0xec, 0xed, 0xffff, 0xffff, 0xef}, {0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xf0, 0xf1, 0xffff, 0xf2, 0xf3}},
    },
    // on the ground (0x00b01060)
    {
        {{0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xd9, 0xda, 0xdb, 0xffff, 0xdc}, {0xffff, 0xe5, 0xffff, 0xffff, 0xffff}, {0xdd, 0xe1, 0xffff, 0xdf, 0xe0}, {0xffff, 0xe2, 0xffff, 0xffff, 0xe3}, {0xdd, 0xde, 0xffff, 0xdf, 0xe0}, {0xffff, 0xe4, 0xffff, 0xffff, 0xffff}, {0xd9, 0xda, 0xea, 0xffff, 0xdc}, {0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xd9, 0xda, 0xdb, 0xffff, 0xdc}},
        {{0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xdd, 0xde, 0xffff, 0xdf, 0xe0}, {0xe2, 0xe3, 0xffff, 0xffff, 0xe4}, {0xd9, 0xda, 0xdb, 0xffff, 0xdc}, {0xdd, 0xde, 0xffff, 0xdf, 0xe0}, {0xd9, 0xda, 0xdb, 0xffff, 0xdc}, {0xffff, 0xe5, 0xffff, 0xffff, 0xffff}, {0xd9, 0xda, 0xdb, 0xffff, 0xdc}, {0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xdd, 0xde, 0xffff, 0xdf, 0xe0}},
    },
    // in the air (0x00b01068)
    {
        {{0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xf5, 0xf6, 0xffff, 0xffff, 0xf7}, {0xffff, 0xe5, 0xffff, 0xffff, 0xffff}, {0xf8, 0xfc, 0xffff, 0xfa, 0xfb}, {0xffff, 0xe2, 0xffff, 0xffff, 0xe3}, {0xf8, 0xf9, 0xffff, 0xfa, 0xfb}, {0xffff, 0xe4, 0xffff, 0xffff, 0xffff}, {0xf5, 0xf6, 0xffff, 0xffff, 0xf7}, {0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xf5, 0xf6, 0xffff, 0xffff, 0xf7}},
        {{0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xf8, 0xf9, 0xffff, 0xfa, 0xfb}, {0xe2, 0xe3, 0xffff, 0xffff, 0xe4}, {0xf5, 0xf6, 0xffff, 0xffff, 0xf7}, {0xf8, 0xf9, 0xffff, 0xfa, 0xfb}, {0xf5, 0xf6, 0xffff, 0xffff, 0xf7}, {0xffff, 0xe5, 0xffff, 0xffff, 0xffff}, {0xf5, 0xf6, 0xffff, 0xffff, 0xf7}, {0xffff, 0xe7, 0xffff, 0xffff, 0xffff}, {0xf8, 0xf9, 0xffff, 0xfa, 0xfb}},
    },
};

// The ability's animation of `phase` in the hero's movement context; 0xffff without one.
uint16_t AbilityAnim(CKS08HeroAbilityHost* host, CKAbilityElement* ability, uint32_t phase, bool* hasSlot) {
    CKHkS08Hero* hero = host->m_pHero;
    const uint8_t id = ability->GetAbilityId();  // vt+0x50
    const uint8_t slot = id < 21 ? kAbilitySlotOfId[hero->m_ui8Hero][id] : 0xff;
    *hasSlot = slot != 0xff;
    if (!*hasSlot || phase > 4) return 0xffff;
    uint32_t context;
    if (static_cast<int8_t>(hero->GetMovementMode()) == 1) {  // 0x003401b8
        context = 0;
    } else {
        context = host->IsOnGround() != 0 ? 1 : 2;  // vt+0x30
    }
    return kAbilityAnims[context][hero->m_ui8Hero][slot][phase];
}

// The hero has the animation: its dictionary's entry (+0x04 list) is not null. The original's entries are the animations
// (CAnimationDictionary_PostLoad 0x0007a288 resolved the words, -1 to null); DOTD: the dictionary keeps the words, resolved
// here the same way.
bool HeroHasAnim(const CKHkS08Hero* hero, uint16_t anim) {
    const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(hero->m_pAnimDico);
    return CAnimationManager_GetAnimation(static_cast<uint32_t>(dictionary->m_apAnimations[anim])) != nullptr;
}
}  // namespace

// 0x003f0fa0 CKS08HeroAbilityHost_maybe_IsOnGround_maybe (the height above the ground it asks first is unused)
uint8_t CKS08HeroAbilityHost::IsOnGround() {
    const uint8_t contact = static_cast<int8_t>(m_pHero->GetMovementMode()) == 1 ? m_pHero->m_unk13d1 : m_pHero->m_unk1511;
    if (contact != 0) return 0;
    return static_cast<uint8_t>(((m_pHero->m_unkec4 >> 18) & 1u) ^ 1u);
}

// 0x003ee240 CKS08HeroAbilityHost_maybe_GetHeroPosition
CVector3 CKS08HeroAbilityHost::GetHeroPosition() {
    return CVector3{m_pHero->m_unk54c, m_pHero->m_unk550, m_pHero->m_unk554};
}

// 0x003ee218 CKS08HeroAbilityHost_maybe_SetHeroPosition
void CKS08HeroAbilityHost::SetOwnerPosition(const CVector3* position) {
    const float z = position->z;
    const float x = position->x;
    const float y = position->y;
    m_pHero->m_unk554 = z;
    m_pHero->m_unk54c = x;
    m_pHero->m_unk550 = y;
}

// 0x003ef6c8 CKS08HeroAbilityHost_maybe_GetHeroVec570_maybe
CVector3 CKS08HeroAbilityHost::GetOwnerGroundPoint() {
    return CVector3{m_pHero->m_unk570, m_pHero->m_unk574, m_pHero->m_unk578};
}

// 0x003ef560 CKS08HeroAbilityHost_maybe_GetHeroTargetPoint_maybe
CVector3 CKS08HeroAbilityHost::GetTargetPoint(float* weight) {
    *weight = m_pHero->m_unk1378;
    return CVector3{m_pHero->m_unk37c, m_pHero->m_unk380, m_pHero->m_unk384};
}

// 0x003ef018 CKS08HeroAbilityHost_maybe_Slot24_maybe
CVector3 CKS08HeroAbilityHost::GetAimDirection(int32_t raw) {
    return m_pHero->GetHotspot4AimDir(raw);  // 0x0032b138
}

// 0x003eef28 CKS08HeroAbilityHost_maybe_CanUseAltLoopAnim_maybe
uint8_t CKS08HeroAbilityHost::CanUseAltLoopAnim() {
    if (static_cast<int8_t>(m_pHero->GetMovementMode()) == 1) {
        return m_pHero->m_fCurrentHorizSpeed < m_pHero->m_unk964 ? 1 : 0;
    }
    if (m_pHero->m_unk150c != 0) return 0;
    return m_pHero->m_unk150d == 0 ? 1 : 0;
}

// 0x003efac0 CKS08HeroAbilityHost_maybe_IsAbilityButtonDown_maybe
uint8_t CKS08HeroAbilityHost::IsAbilityButtonDown(int32_t button) {
    uint32_t state;
    if (button == 1) {
        state = m_pHero->m_unkf58;
    } else if (button == 0) {
        state = m_pHero->m_unkf44;
    } else if (button == 2) {
        if (m_pHero->m_unkf44 == 1) return 1;
        state = m_pHero->m_unkf58;
    } else if (button == 3) {
        state = m_pHero->m_unkf1c;
    } else {
        return 0;
    }
    return state == 1u ? 1 : 0;
}

// 0x003eee50 CKS08HeroAbilityHost_maybe_SelectByMovementContext
uint8_t CKS08HeroAbilityHost::SelectByMovementContext(uint8_t ground, uint8_t air, uint8_t flying) {
    if (static_cast<int8_t>(m_pHero->GetMovementMode()) == 1) return flying;
    return IsOnGround() != 0 ? ground : air;  // vt+0x30
}

// 0x003ee270 CKS08HeroAbilityHost_maybe_Slot40Switch_maybe (the jump table 0x003ee2a4, TOC +0x43a0)
uint8_t CKS08HeroAbilityHost::Vf40(CKAbilityElement* ability, uint32_t index) {
    const CKHkS08Hero* hero = m_pHero;
    switch (index) {
    case 0: return static_cast<uint8_t>((hero->m_unkec4 >> 21) & 1u);
    case 1: return static_cast<uint8_t>((hero->m_unkec4 >> 12) & 1u);
    case 2: return static_cast<uint8_t>((hero->m_unkec4 >> 11) & 1u);
    case 3:
        if ((hero->m_ui32HeroFlags354 & 0x800u) != 0) return 1;
        return static_cast<uint8_t>((hero->m_ui32HeroFlags35C >> 1) & 1u);
    case 4: return static_cast<uint8_t>((hero->m_unkec4 >> 9) & 1u);
    case 5: return hero->m_unk1d11;
    case 6: return static_cast<uint8_t>((hero->m_unkec8 >> 28) & 1u);
    case 7: return static_cast<uint8_t>((hero->m_ui32HeroFlags354 >> 6) & 1u);
    case 8: return static_cast<uint8_t>(hero->m_unkecc >> 31);
    case 9: return static_cast<uint8_t>((hero->m_unkec4 >> 13) & 1u);
    case 10: return ability->GetAbilityId() == 0xf ? 1 : 0;  // vt+0x50
    case 11: return static_cast<uint8_t>((hero->m_unkecc >> 27) & 1u);
    default: return 0;
    }
}

// 0x003ef1d8 CKS08HeroAbilityHost_maybe_PlayAbilityAnim
uint8_t CKS08HeroAbilityHost::PlayAbilityAnim(CKAbilityElement* ability, uint32_t phase) {
    bool hasSlot = false;
    const uint16_t anim = AbilityAnim(this, ability, phase, &hasSlot);
    if (anim == 0xffff || !HeroHasAnim(m_pHero, anim)) return 0;
    // 0x003014b8 CKHkS08Hero_PlayAnimationFromHost: vt+0x184 (start 0, blend 0.12: TOC +0x43a8 / +0x43dc), +0x1838 cleared.
    m_pHero->PlayAnimation(0.0f, 0.12f, anim);
    m_pHero->m_unk1838 = 0;
    return 1;
}

// 0x003f0b48 CKS08HeroAbilityHost_maybe_IsAbilityAnimPhaseDone_maybe
uint8_t CKS08HeroAbilityHost::IsAbilityAnimPhaseDone(CKAbilityElement* ability, uint32_t phase) {
    bool hasSlot = false;
    const uint16_t anim = AbilityAnim(this, ability, phase, &hasSlot);
    if (anim == 0xffff || !HeroHasAnim(m_pHero, anim)) return 1;
    // 0x003013a0 CKHkS08Hero_IsAnimFinishedOrOther: another current animation, or +0x354 bit 15.
    if (m_pHero->m_i16CurAnimIndex != anim) return 1;
    return static_cast<uint8_t>((m_pHero->m_ui32HeroFlags354 >> 15) & 1u);
}

// 0x003efe70 CKS08HeroAbilityHost_maybe_IsAbilityButtonReleased_maybe
uint8_t CKS08HeroAbilityHost::IsAbilityButtonReleased(int32_t button) {
    uint32_t state;
    if (button == 1) {
        state = m_pHero->m_unkf58;
    } else if (button == 0) {
        state = m_pHero->m_unkf44;
    } else if (button == 2) {
        if (m_pHero->m_unkf44 == 2) return 1;
        state = m_pHero->m_unkf58;
    } else if (button == 3) {
        state = m_pHero->m_unkf1c;
    } else {
        return 0;
    }
    return state == 2 ? 1 : 0;
}

// 0x003efd80 CKS08HeroAbilityHost_maybe_GetAbilityButtonHoldTime_maybe
uint8_t CKS08HeroAbilityHost::GetAbilityButtonHoldTime(int32_t button, float* held) {
    CKHkS08Hero* hero = m_pHero;
    if (button == 2) {
        uint8_t down = 1;
        float other = 0.0f;
        if (hero->m_unkf44 != 3) {
            other = hero->m_unkf5c;
            down = hero->m_unkf58 == 3 ? 1 : 0;
        }
        *held = hero->m_unkf48 <= other ? other : hero->m_unkf48;
        return down;
    }
    if (button == 1) {
        *held = hero->m_unkf5c;
        return hero->m_unkf58 == 3 ? 1 : 0;
    }
    if (button == 0) {
        *held = hero->m_unkf48;
        return hero->m_unkf44 == 3 ? 1 : 0;
    }
    if (button == 3) {
        *held = hero->m_unkf20;
        return hero->m_unkf1c == 3 ? 1 : 0;
    }
    *held = 0.0f;
    return 0;
}

// 0x003ef098 CKS08HeroAbilityHost_maybe_SetAbilityCooldown
void CKS08HeroAbilityHost::SetAbilityCooldown(float cooldown, CKAbilityElement* ability, uint8_t perSlot) {
    const uint8_t id = ability->GetAbilityId();  // vt+0x50
    const bool shared = id <= 0x14 && ((0x180300u >> id) & 1u) != 0;  // 8, 9, 19, 20
    if (!shared && perSlot != 0) {
        // BUG(original): an id above 20 or not the dragon's (slot 0xff) indexes past the tables; DOTD sets them all.
        const uint8_t slot = id <= 0x14 ? kAbilitySlotOfId[m_pHero->m_ui8Hero][id] : 0xff;
        if (slot < 10) {
            m_pHero->m_afAbilityCooldown[slot] = cooldown;
            return;
        }
    }
    for (float& value : m_pHero->m_afAbilityCooldown) value = cooldown;
}

// 0x003f0f40 CKS08HeroAbilityHost_maybe_GetAbilityMana
int32_t CKS08HeroAbilityHost::GetAbilityMana() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if ((manager->m_flags64 & 0x800000u) != 0) return -1;
    return static_cast<int32_t>(manager->GetDragonMana(m_pHero->m_ui8Hero));  // 0x004fd7c8
}

// 0x003ef9b8 CKS08HeroAbilityHost_maybe_ConsumeAbilityMana
uint32_t CKS08HeroAbilityHost::ConsumeAbilityMana(CKAbilityElement* ability, uint32_t amount) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if ((manager->m_flags64 & 0x800000u) != 0) return 1;
    const uint8_t id = ability->GetAbilityId();  // vt+0x50
    const uint8_t dragon = m_pHero->m_ui8Hero;
    const uint8_t element = id < 21 ? kAbilityElementOfId[dragon][id] : 0xff;  // 0xb01048
    manager->ConsumeDragonMana(dragon, amount);                                  // 0x004fd808
    AddElementManaSpent(manager->m_gameStructure, m_pHero->m_ui8Hero, element, amount);  // 0x0050f238
    return manager->GetDragonMana(m_pHero->m_ui8Hero) != 0 ? 1u : 0u;  // 0x004fd7c8
}

// 0x003ee9f0 CKS08HeroAbilityHost_maybe_GetManaCostScale (0x0030b110 CKHkS08Hero_GetAbilityManaCostScale: +0xe84 with
// +0xed0 bit 8, else 1)
float CKS08HeroAbilityHost::GetManaCostScale() {
    return (m_pHero->m_ui32StatusFlagsED0 & 0x100u) != 0 ? m_pHero->m_unke84 : 1.0f;
}

// 0x003ef8f0 CKS08HeroAbilityHost_maybe_GetAbilityLevelIndex
uint8_t CKS08HeroAbilityHost::GetAbilityLevelIndex(CKAbilityElement* ability) {
    const uint8_t id = ability->GetAbilityId();  // vt+0x50
    const uint8_t dragon = m_pHero->m_ui8Hero;
    const uint8_t element = id < 21 ? kAbilityElementOfId[dragon][id] : 0xff;
    if (element == 0xff) return 0;
    const uint8_t level = static_cast<uint8_t>(
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->GetElementLevel(dragon, element));  // 0x004f9558
    if (level == 2) return 1;
    if (level <= 1) return 0;
    return level == 3 ? 2 : level;
}

// 0x003ee618 CKS08HeroAbilityHost_maybe_IsProjectileChargeHeld_maybe
uint8_t CKS08HeroAbilityHost::IsProjectileChargeHeld(CKAbilityElement* ability) {
    if (ability->GetFamilyId() != 0x16) return 0;  // vt+0x54
    return static_cast<uint8_t>((m_pHero->m_unkedc >> 8) & 1u);
}

// 0x003ef690 CKS08HeroAbilityHost_maybe_GetHeroForward
CVector3 CKS08HeroAbilityHost::GetHeroForward() {
    const RwV3d& at = static_cast<CSGMovable*>(m_pHero->m_pKGLObject)->m_pRwFrame->modelling.at;
    return CVector3{at.x, at.y, at.z};
}

// 0x003ef660 CKS08HeroAbilityHost_maybe_GetHeroVec135c_maybe
CVector3 CKS08HeroAbilityHost::GetHeroVec135c() {
    return CVector3{m_pHero->m_unk135c, m_pHero->m_unk1360, m_pHero->m_unk1364};
}

// 0x003ef8b8 CKS08HeroAbilityHost_maybe_GetHeroRight_maybe
CVector3 CKS08HeroAbilityHost::GetHeroRight() {
    const RwV3d& right = static_cast<CSGMovable*>(m_pHero->m_pKGLObject)->m_pRwFrame->modelling.right;
    return CVector3{right.x, right.y, right.z};
}

namespace {
// 0x00c50da0 (TOC +0x43fc): the "no point" vector, FLT_MAX in each part; 0x00c50d64 (TOC +0x43a4) the null vector.
constexpr CVector3 kNoAimPoint{3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f};
constexpr CVector3 kNullVector{0.0f, 0.0f, 0.0f};
constexpr float kPi = 0x1.921fb6p+1f;     // TOC +0x444c (0x40490fdb)
constexpr float kTwoPi = 0x1.921fb6p+2f;  // TOC +0x4454 (0x40c90fdb); -2 pi TOC +0x4450
bool IsNull(const CVector3& v) { return v.x == kNullVector.x && v.y == kNullVector.y && kNullVector.z == v.z; }
float Length(const CVector3& v) {  // 0x00010690 Math_Sqrtf of the fused sum
    return static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, v.y * v.y)))));
}
}  // namespace

// 0x003efb48 CKS08HeroAbilityHost_maybe_GetTargetAimPoint_maybe
CVector3 CKS08HeroAbilityHost::GetTargetAimPoint(int32_t fromHotSpot, uint8_t clampHeight) {
    CKHkS08Hero* hero = m_pHero;
    if (hero->m_pTargetedEnemy == nullptr) {
        if (hero->m_pTargetedMecaHook != nullptr) return hero->GetAimPointOnHook(hero->m_pTargetedMecaHook, clampHeight);  // 0x002fd7c0
        return kNoAimPoint;
    }
    if (fromHotSpot != 0) {
        CVector3 from;
        static_cast<CSGHotSpot*>(GetHotspot(1))->GetWorldPosition(&from);  // vt+0xcc, 0x000ce790
        return hero->GetAimPointOnEnemy(hero->m_pTargetedEnemy, &from, 1, clampHeight);  // 0x002fdec8
    }
    // The enemy node's world position (its frame's LTM, +0x1c -> +0x04 -> +0x80).
    const CSGMovable* node = static_cast<const CSGMovable*>(static_cast<IKHook*>(hero->m_pTargetedEnemy)->m_pKGLObject);
    const RwV3d& pos = FrameLtm(node->m_pRwFrame)->pos;
    return CVector3{pos.x, pos.y, pos.z};
}

// 0x003f1ea8 CKS08HeroAbilityHost_maybe_ComputeAimDirection_maybe. The direction the hero wants (+0x37c, else +0x135c)
// turned from its aim direction (+0x135c) by at most `maxTurn` about the y axis (Vec3_RotateTowardByAngle); then by the
// ability (its id, vt+0x50):
//   - the dashes (0, 8, 10, 19): while the partner's flight takes the hero along, its forward row; else, with `aim`, a
//     target (AcquireAbilityTarget 2 / 1, mask 0xc3) gives the direction to it from the hero (GetTargetAimPoint(1, 1));
//     the hero's facing +0x11cc and +0x11ec take it, +0xec8 bit 7, +0x127c the null vector, the speed +0x1d14 1000 with
//     +0x1d10;
//   - the grapple (7, weights 1 / 2, mask 0xc4) and the others (2 / 1, mask 0xd3 for 1 and 2, 0xe3 for 15 and 20, else
//     0xc3): only with `aim` and a target (else the "no point" vector): the direction to the target point
//     (GetTargetAimPoint(1, 0)) into the facing (bit 7), and +0x13b4 the cosine of its flat part with the hero's right row
//     (clamped to -1..1);
//   - the wind beam (18): the same with the target the hero holds already (or one taken, weights 1 / 2, mask 8), +0x11ec
//     too; without `aim` bit 7 cleared and the "no point" vector.
CVector3 CKS08HeroAbilityHost::ComputeAimDirection(float maxTurn, CKAbilityElement* ability, IKSerializable* aim) {
    CKHkS08Hero* hero = m_pHero;
    const uint8_t id = ability->GetAbilityId();  // vt+0x50
    enum { kDefault, kDash, kGrapple, kBeam } kind = kDefault;
    if (id <= 0x13) {
        const uint64_t bit = 1ull << static_cast<int8_t>(id);
        if ((bit & 0x80501ull) != 0) {
            kind = kDash;
        } else if ((bit & 0x80ull) != 0) {
            kind = kGrapple;
        } else if ((bit & 0x40000ull) != 0) {
            kind = kBeam;
        }
    }
    if (kind == kDash && hero->ShouldJoinPartnerFlight() != 0) return GetHeroForward();  // 0x00341fa0, vt+0x18

    // The wanted direction, turned by at most maxTurn.
    CVector3 direction{hero->m_unk37c, hero->m_unk380, hero->m_unk384};
    if (IsNull(direction)) direction = GetHeroVec135c();  // vt+0x1c
    const CVector3 aimDirection = GetHeroVec135c();
    float angle = Vec3_GetYawAngleFromZ(&direction) - Vec3_GetYawAngleFromZ(&aimDirection);  // 0x00244528
    if (!(std::fabs(angle) <= kPi)) angle = angle - (angle < 0.0f ? -kTwoPi : kTwoPi);
    if (!(std::fabs(angle) <= maxTurn)) {
        CVector3 from = aimDirection;
        CVector3 axis{0.0f, 1.0f, 0.0f};  // TOC +0x4458 -> 0x00c50d40
        CVector3 turned;
        Vec3_RotateTowardByAngle(&turned, &from, &axis, (angle < 0.0f ? -1.0f : 1.0f) * maxTurn);  // TocBridge 0x0098f300
        direction = turned;
    }

    // The direction from the hero to the target point, into the facing (+0xec8 bit 7).
    auto towardTarget = [&](int32_t fromHotSpot, uint8_t clamp) {
        const CVector3 target = GetTargetAimPoint(fromHotSpot, clamp);  // vt+0xdc
        const CVector3 position = GetHeroPosition();                    // vt+0x10
        CVector3 d{target.x - position.x, target.y - position.y, target.z - position.z};
        const float length = Length(d);
        if (length != 0.0f) {
            const float k = 1.0f / length;
            d.z = d.z * k;
            d.x = d.x * k;
            d.y = d.y * k;
        }
        hero->m_unk11cc = d.x;
        hero->m_unk11d4 = d.z;
        hero->m_unk11d0 = d.y;
        hero->m_unkec8 = (hero->m_unkec8 & ~0x80u) | 0x80u;
        return d;
    };
    // +0x13b4: the cosine of the direction's flat part with the hero's right row, clamped to -1..1.
    auto storeSideCosine = [&](const CVector3& d) {
        float x = d.x;
        float z = d.z;
        float y = 0.0f;
        const float length = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)))));
        if (length != 0.0f) {
            const float k = 1.0f / length;
            z = z * k;
            x = x * k;
            y = k * 0.0f;
        }
        const CVector3 right = GetHeroRight();  // vt+0x28
        float cosine = ppc::fmadds(z, right.z, ppc::fmadds(x, right.x, y * right.y));
        if (cosine <= -1.0f) {
            cosine = -1.0f;
        } else if (cosine >= 1.0f) {
            cosine = 1.0f;
        }
        hero->m_unk13b4.x = cosine;
    };

    switch (kind) {
        case kDash: {
            if (aim != nullptr) {
                const CVector3 wanted = direction;
                if (hero->AcquireAbilityTarget(2.0f, 1.0f, aim, &wanted, 0xc3) != 0) direction = towardTarget(1, 1);  // 0x002ff6c8
            }
            hero->m_unk11d4 = direction.z;
            hero->m_unk11d0 = direction.y;
            hero->m_unk11cc = direction.x;
            hero->m_unkec8 = (hero->m_unkec8 & ~0x80u) | 0x80u;
            hero->m_unk11f4 = direction.z;
            hero->m_unk11ec = direction.x;
            hero->m_unk11f0 = direction.y;
            hero->m_unk1284 = kNullVector.z;
            hero->m_unk127c = kNullVector.x;
            hero->m_unk1280 = kNullVector.y;
            hero->m_unk1d14 = 1000.0f;  // TOC +0x445c
            hero->m_unk1d10 = 1;
            return direction;
        }
        case kGrapple: {
            if (aim == nullptr) return kNoAimPoint;
            const CVector3 wanted = direction;
            if (hero->AcquireAbilityTarget(1.0f, 2.0f, aim, &wanted, 0xc4) == 0) return kNoAimPoint;
            direction = towardTarget(1, 0);
            storeSideCosine(direction);
            return direction;
        }
        case kBeam: {
            if (aim == nullptr) {
                hero->m_unkec8 &= ~0x80u;
                return kNoAimPoint;
            }
            const CVector3 held = GetTargetAimPoint(1, 0);
            if (held.x == kNoAimPoint.x && held.y == kNoAimPoint.y && held.z == kNoAimPoint.z) {
                const CVector3 wanted = direction;
                if (hero->AcquireAbilityTarget(1.0f, 2.0f, aim, &wanted, 8) == 0) return kNoAimPoint;
            }
            direction = towardTarget(1, 0);
            hero->m_unk11ec = direction.x;
            hero->m_unk11f4 = direction.z;
            hero->m_unk11f0 = direction.y;
            storeSideCosine(direction);
            return direction;
        }
        default: {
            if (aim == nullptr) return kNoAimPoint;
            uint32_t mask = 0xd3;
            if (static_cast<uint8_t>(id - 1) > 1) mask = (id == 0x0f || id == 0x14) ? 0xe3 : 0xc3;
            const CVector3 wanted = direction;
            if (hero->AcquireAbilityTarget(2.0f, 1.0f, aim, &wanted, mask & 0xf3) == 0) return kNoAimPoint;
            direction = towardTarget(1, 0);
            storeSideCosine(direction);
            return direction;
        }
    }
}

// 0x003f18f8 CKS08HeroAbilityHost_maybe_SetHeroActionPermission (three jump tables of 13: TOC +0x4428 flying, +0x4430
// on the ground, +0x4434 in the air)
void CKS08HeroAbilityHost::SetHeroActionPermission(uint32_t index, uint8_t ground, uint8_t flying, uint8_t air) {
    CKHkS08Hero* hero = m_pHero;
    if (static_cast<int8_t>(hero->GetMovementMode()) == 1 && IsOnGround() != 0) hero->SetMovementMode(0);  // 0x00340c18
    uint8_t value;
    uint8_t value7;  // the case 7 test: the flying table's entry is the on-ground one's (it reads `ground`)
    if (static_cast<int8_t>(hero->GetMovementMode()) == 1) {
        value = flying;
        value7 = ground;
    } else if (IsOnGround() != 0) {  // vt+0x30
        value = ground;
        value7 = ground;
    } else {
        value = air;
        value7 = air;
    }
    if (index > 12) return;
    const uint32_t v = value;
    // The bit cleared, then the context's byte shifted in (or-ed whole, as the original's slwi / rlwinm).
    auto setBit = [v](uint32_t& word, uint32_t bit) { word = (word & ~(1u << bit)) | (v << bit); };
    switch (index) {
    case 0:
        setBit(hero->m_unkec4, 21);
        setBit(hero->m_unkec4, 11);
        setBit(hero->m_unkec4, 10);
        setBit(hero->m_unkec4, 13);
        break;
    case 1:
        setBit(hero->m_unkec4, 12);
        break;
    case 2:
        setBit(hero->m_unkec4, 11);
        break;
    case 3:
        setBit(hero->m_ui32HeroFlags354, 11);
        break;
    case 4:
        setBit(hero->m_unkec4, 9);
        break;
    case 5:
        hero->m_unk1d11 = value;
        break;
    case 6:
        setBit(hero->m_unkec8, 28);
        break;
    case 7: {
        // The hero's second bounding volume (+0x54[1]) answers hits or not (its flag 0x10), +0x354 bit 6.
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(hero->m_apBoundings[1]);
        if (value7 == 0) {
            hero->m_ui32HeroFlags354 &= ~0x40u;
            volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags | 0x10u);
        } else {
            hero->m_ui32HeroFlags354 |= 0x40u;
            volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags & ~0x10u);
        }
        break;
    }
    case 8:
        setBit(hero->m_unkecc, 31);
        break;
    case 9:
        setBit(hero->m_unkec4, 13);
        break;
    case 11:
        setBit(hero->m_unkecc, 27);
        break;
    case 12:
        hero->SetUnk894(value == 0 ? 1.0f : 0.2f);  // vt+0x198; TOC +0x4398 / +0x442c
        break;
    default:
        break;
    }
}

// 0x003efcb0 CKS08HeroAbilityHost_maybe_GetHeroSpeedForAbility_maybe
float CKS08HeroAbilityHost::GetHeroSpeedForAbility() {
    const CVector3 at = GetHeroForward();  // vt+0x18
    const float along = m_pHero->m_unk1284 * at.z + (m_pHero->m_unk127c * at.x + m_pHero->m_unk1280 * at.y);
    return 0.0f <= along ? m_pHero->m_fCurrentHorizSpeed * 1.0f : m_pHero->m_fCurrentHorizSpeed * -1.0f;  // TOC +0x43a8 / +0x4398 / +0x43ec
}

// 0x003eed48 CKS08HeroAbilityHost_maybe_SetAbilityMoveSpeed
void CKS08HeroAbilityHost::SetAbilityMoveSpeed(float ground, float flying, float air) {
    if (static_cast<int8_t>(m_pHero->GetMovementMode()) == 1) {
        m_pHero->m_unk1d14 = flying;
    } else if (IsOnGround() != 0) {
        m_pHero->m_unk1d14 = ground;
    } else {
        m_pHero->m_unk1d14 = air;
    }
}

// 0x003ee3e0 CKS08HeroAbilityHost_maybe_SetAbilityMoveSpeedEnabled
void CKS08HeroAbilityHost::SetAbilityMoveSpeedEnabled(uint8_t on) { m_pHero->m_unk1d10 = on; }

// 0x003eeaf8 CKS08HeroAbilityHost_maybe_SetAbilityTurnParams_maybe
void CKS08HeroAbilityHost::SetAbilityTurnParams(float groundA, float groundB, float flyA, float flyB, float airA, float airB,
                                                uint8_t gateGround, uint8_t gateFly, uint8_t gateAir) {
    CKHkS08Hero* hero = m_pHero;
    auto set = [hero](float a, float b) {
        hero->m_unk1d04 = a;
        hero->m_unk1d08 = b;
        hero->m_unk1d0c = hero->m_unk1d04;
        hero->m_unk1dfc = 1;
    };
    if (static_cast<int8_t>(hero->GetMovementMode()) == 1 && gateFly != 0) {
        set(flyA, flyB);
        return;
    }
    if (static_cast<int8_t>(hero->GetMovementMode()) == 0 && gateGround != 0 && IsOnGround() != 0) {
        set(groundA, groundB);
        return;
    }
    if (static_cast<int8_t>(hero->GetMovementMode()) == 0 && gateAir != 0 && IsOnGround() == 0) {
        set(airA, airB);
        return;
    }
    hero->m_unk1d0c = hero->m_unkaf8;
    hero->m_unk1dfc = 0;
}

// 0x003efef8 CKS08HeroAbilityHost_maybe_SetAbilityParam11f8_maybe
void CKS08HeroAbilityHost::SetAbilityParam11f8(float ground, float flying, float air, uint8_t gateGround, uint8_t gateFly,
                                               uint8_t gateAir) {
    CKHkS08Hero* hero = m_pHero;
    float value;
    if (static_cast<int8_t>(hero->GetMovementMode()) == 1 && gateFly != 0) {
        value = flying;
    } else if (static_cast<int8_t>(hero->GetMovementMode()) == 0 && gateGround != 0 && IsOnGround() != 0) {
        value = ground;
    } else if (static_cast<int8_t>(hero->GetMovementMode()) == 0 && gateAir != 0 && IsOnGround() == 0) {
        value = air;
    } else {
        hero->m_unkec8 &= 0xfbffffffu;
        return;
    }
    hero->m_unk11f8 = value;
    hero->m_unkec8 = (hero->m_unkec8 & 0xfbffffffu) | 0x4000000u;
}

// 0x003ef5a0 CKS08HeroAbilityHost_maybe_GetHeroVelocity_maybe
CVector3 CKS08HeroAbilityHost::GetOwnerVelocity() {
    return CVector3{m_pHero->m_unk127c, m_pHero->m_unk1280, m_pHero->m_unk1284};
}

// 0x003ee460 CKS08HeroAbilityHost_maybe_SetHeroEd4Bit0_maybe (the earth boulder's ApplyHeroControl)
void CKS08HeroAbilityHost::SetHeroEd4Bit0(CKAbilityElement* /*ability*/, uint8_t on, float value) {
    m_pHero->m_ui32StatusFlagsED4 = (m_pHero->m_ui32StatusFlagsED4 & 0xfffffffeu) | on;
    m_pHero->m_fExtraMass = value;
}

// 0x003ee438 CKS08HeroAbilityHost_maybe_SetHeroEc4Bit27
void CKS08HeroAbilityHost::SetHeroEc4Bit27(uint32_t value) {
    m_pHero->m_unkec4 = (m_pHero->m_unkec4 & 0xf7ffffffu) | (value << 27);
}

// 0x003f1040 CKS08HeroAbilityHost_maybe_SetAbilityHeroMode
void CKS08HeroAbilityHost::SetAbilityHeroMode(CKAbilityElement* ability, uint8_t on) {
    CKHkS08Hero* hero = m_pHero;
    if (on == 0) {
        hero->m_unkec8 &= 0xfffdffffu;
        SetHeroEc4Bit27(0);  // vt+0x6c
        hero->m_unkec8 &= 0xfffffeffu;
        hero->m_ui32StatusFlagsED0 &= 0xbfffffffu;
        hero->m_unkec4 &= 0xfffffeffu;
        if (ability->GetAbilityId() == 6) {  // vt+0x50: CKElectricSphere
            SetAbilityParam11f8(0.1f, 0.1f, 0.1f, 0, 0, 0);  // vt+0x68
            hero->m_unkec8 &= 0xfffffdffu;
        }
        return;
    }
    const uint8_t id = ability->GetAbilityId();
    if (id == 6) {
        if (static_cast<int8_t>(hero->GetMovementMode()) == 1) hero->SetMovementMode(0);
        hero->m_unkec4 = (hero->m_unkec4 & 0xfffffeffu) | 0x100u;
        hero->m_unkec8 = (hero->m_unkec8 & 0xfffffdffu) | 0x200u;
        hero->m_unkec4 &= 0xffdfd3ffu;
        hero->m_unkec4 = (hero->m_unkec4 & 0xfffff7ffu) | 0x800u;
        return;
    }
    if (id == 10 || id == 5) {  // CKPoisonSpin, CKEarthBoulder
        if (static_cast<int8_t>(hero->GetMovementMode()) == 1) hero->SetMovementMode(0);
        hero->m_unkec4 = (hero->m_unkec4 & 0xfffffeffu) | 0x100u;
        return;
    }
    const uint8_t family = ability->GetFamilyId();  // vt+0x54
    if ((family == 0x15 || family == 0x16) && static_cast<int8_t>(hero->GetMovementMode()) == 1) {
        hero->m_ui32StatusFlagsED0 = (hero->m_ui32StatusFlagsED0 & 0xbfffffffu) | 0x40000000u;
        hero->m_unk11e8 = hero->m_unk8cc;
    }
}

// 0x003ee488 CKS08HeroAbilityHost_maybe_SetHero1d20
void CKS08HeroAbilityHost::SetHero1d20(float value) { m_pHero->m_fAbilityAnimSpeedScale = value; }

// 0x003ee498 CKS08HeroAbilityHost_maybe_SetHero1d11
void CKS08HeroAbilityHost::SetHero1d11(uint8_t value) { m_pHero->m_unk1d11 = value; }

// 0x003eea68 CKS08HeroAbilityHost_maybe_GetDamageScale
float CKS08HeroAbilityHost::GetDamageScale() {
    return (m_pHero->m_ui32StatusFlagsED0 & 0x1000u) != 0 ? m_pHero->m_unke80 : 1.0f;  // 0x0030b0d0
}

// 0x003eea18 CKS08HeroAbilityHost_maybe_GetEffectScale
float CKS08HeroAbilityHost::GetEffectScale() {
    if ((m_pHero->m_ui32StatusFlagsED0 & 0x10u) == 0) return 1.0f;
    return (m_pHero->m_ui32StatusFlagsED0 & 0x80u) != 0 ? m_pHero->m_unke78 : 1.0f;  // 0x0030b0f0
}

// 0x003ef6f8 CKS08HeroAbilityHost_maybe_GetHotspot
IKSerializable* CKS08HeroAbilityHost::GetHotspot(uint32_t index) {
    static const int8_t kSpyro[10] = {0, 5, 18, 26, 28, 1, -1, 3, 2, 32};
    static const int8_t kCynder[10] = {0, 5, 18, 0, -1, 1, 20, 3, 2, 28};
    if (index > 9) return nullptr;
    const int8_t spot = m_pHero->m_ui8Hero == 0 ? kSpyro[index] : kCynder[index];
    if (spot < 0) return nullptr;
    return m_pHero->m_apHotSpots[spot];
}

// 0x003f0a80 CKS08HeroAbilityHost_maybe_GetHotspotPosition
CVector3 CKS08HeroAbilityHost::GetHotspotPosition(uint32_t index) {
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(GetHotspot(index));  // vt+0xcc
    if (spot == nullptr) return CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d64
    CVector3 out;
    spot->GetWorldPosition(&out);  // 0x000ce790
    return out;
}

// 0x003ee4d8 CKS08HeroAbilityHost_maybe_GetLockedTarget
IKSerializable* CKS08HeroAbilityHost::GetLockedTarget() {
    return m_pHero->m_pTargetedEnemy != nullptr ? m_pHero->m_pTargetedEnemy : m_pHero->m_pTargetedMecaHook;
}

// 0x003ef880 CKS08HeroAbilityHost_maybe_GetHeroUp_maybe
CVector3 CKS08HeroAbilityHost::GetOwnerUp() {
    const RwV3d& up = static_cast<CSGMovable*>(m_pHero->m_pKGLObject)->m_pRwFrame->modelling.up;
    return CVector3{up.x, up.y, up.z};
}

// 0x003eeff0 CKS08HeroAbilityHost_maybe_GetHero4dc_maybe
float CKS08HeroAbilityHost::Vf34() {
    return m_pHero->GetHeightAboveGround();  // 0x0032a008
}

// 0x003ef5d0 CKS08HeroAbilityHost_maybe_SetAbilityImpulse_maybe: the impulse cleared, then set (stores in the original's
// order; +0x1d40 / +0x1d54 / +0x1d58 are float words).
void CKS08HeroAbilityHost::SetAbilityImpulse(CKAbilityElement* /*ability*/, float strength, float duration,
                                             const CVector3* direction) {
    CKHkS08Hero* hero = m_pHero;
    std::memcpy(&hero->m_unk1d40, &duration, sizeof(duration));
    hero->m_unk1d3c = strength;
    hero->m_unk1d50 = 0.0f;  // the null vector 0x00c50d64 (TOC +0x43a4)
    hero->m_unk1d48 = 0.0f;
    hero->m_unk1d4c = 0.0f;
    hero->m_unk1d44 = 0;
    hero->m_unk1d58 = 0;
    hero->m_unk1d54 = 0;
    hero->m_unk1d50 = direction->z;
    hero->m_unk1d48 = direction->x;
    hero->m_unk1d4c = direction->y;
    hero->m_unk1d58 = 0;
    hero->m_unk1d54 = hero->m_unk1d40;  // the time left: the duration
    hero->m_unk1d44 = 1;
}

// 0x003ee3f0 CKS08HeroAbilityHost_maybe_ClearAbilityImpulse_maybe
void CKS08HeroAbilityHost::ClearAbilityImpulse(CKAbilityElement* /*ability*/) {
    CKHkS08Hero* hero = m_pHero;
    hero->m_unk1d50 = 0.0f;  // the null vector 0x00c50d64 (TOC +0x43a4)
    hero->m_unk1d48 = 0.0f;
    hero->m_unk1d4c = 0.0f;
    hero->m_unk1d58 = 0;
    hero->m_unk1d44 = 0;
    hero->m_unk1d54 = 0;
}

namespace {
// The ice spin's spheres moved along their own z by `dz`: the modelling position, the matrix no longer the identity
// (flags bit 17 cleared), the frame marked dirty (RwFrame_MarkDirty 0x00010698).
void ShiftSphereZ(IKSerializable* sphere, float dz, bool add) {
    RwFrame* frame = static_cast<CSGMovable*>(sphere)->m_pRwFrame;
    frame->modelling.pos.z = add ? dz + frame->modelling.pos.z : frame->modelling.pos.z - dz;
    frame->modelling.flags &= ~0x20000u;
    RwFrame_MarkDirty(frame);
}
}  // namespace

// 0x003f1410 CKS08HeroAbilityHost_maybe_SetAbilityAttackSpheres: a jump table on the ability id (0x3f14ac, ids 0..19).
void CKS08HeroAbilityHost::SetAbilityAttackSpheres(CKAbilityElement* ability, uint8_t on, float radius0,
                                                   IKSerializable* damage0, float radius1, IKSerializable* damage1) {
    const uint32_t id = ability->GetAbilityId() & 0xffu;  // vt+0x50
    if (id > 0x13) return;
    CKHkS08Hero* hero = m_pHero;
    switch (id) {
    case 0:   // the comet dash
    case 8:   // the purple combo
        hero->SetAttackSphere(0, on, radius0, 4, damage0);  // 0x0032a938
        return;
    case 5:   // the earth boulder
    case 6:   // the electric sphere
    case 14:  // the shadow surprise
        hero->SetAttackSphere(0, on, radius0, 5, damage0);
        return;
    case 3:  // the ice spin: both spheres, then (on) moved apart along their z
        hero->SetAttackSphere(0, on, radius0, 8, damage0);
        hero->SetAttackSphere(1, on, radius0, 4, damage0);  // 0x0032ab18
        if (on == 0) return;
        ShiftSphereZ(hero->m_unk1b8c, radius0, true);
        ShiftSphereZ(hero->m_unk1b90, radius0, false);
        return;
    case 10:  // the poison spin
    case 19:  // the black combo
        hero->SetAttackSphere(0, on, radius0, 1, damage0);
        hero->SetAttackSphere(1, on, radius0, 8, damage0);
        return;
    case 17:  // the wind twister
        hero->SetAttackSphere(0, on, radius0, 0, damage0);
        hero->SetAttackSphere(2, on, radius0, 5, damage0);  // 0x0032aa28
        hero->SetAttackSphere(1, on, radius1, 0, damage1);
        return;
    case 18: {
        // The wind beam (0x3f14fc..0x3f1660, 0x3f1884..0x3f18f4; C2.7, LVL010's breath2 recording): off, both hero
        // spheres off (hot spot -2). Then the locked target (vt+0xd4): an enemy that can fight (0x289278), when on, gets
        // the throw spheres with `damage1` (0x288e08) or, without, the hit `damage0` from the hero (0x28a6e0); a fog
        // horn (0x2f02) gets sphere 0 at its node's position.
        if (on == 0) {
            hero->SetAttackSphere(0, 0, radius0, -2, damage0);  // 0x0032a938
            hero->SetAttackSphere(1, 0, radius1, -2, damage1);  // 0x0032ab18
        }
        IKSerializable* target = GetLockedTarget();  // vt+0xd4
        if (target == nullptr) return;
        if (target->IsKindOfClass(0x26c2) != 0 && on != 0) {  // vt+0x08: CKHkS08Enemy
            CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(target);
            if (enemy->IsValidCombatTarget() == 0) return;
            if (damage1 != nullptr) {
                enemy->SetAttackSpheresActive(1, damage1);
            } else {
                enemy->ReceiveDamage(damage0, GetOwner());  // vt+0x08
            }
        }
        if (target->IsKindOfClass(0x2f02) == 0) return;  // CKHkS08FogHorn
        hero->SetAttackSphere(0, on, radius0, -2, damage0);
        RwFrame* frame = static_cast<CSGMovable*>(hero->m_unk1b8c)->m_pRwFrame;
        const RwV3d& pos = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(target)->m_pKGLObject)->m_pRwFrame)->pos;
        frame->modelling.pos.z = pos.z;
        frame->modelling.pos.x = pos.x;
        frame->modelling.pos.y = pos.y;
        frame->modelling.flags &= ~0x20000u;
        RwFrame_MarkDirty(frame);  // 0x00010698
        return;
    }
    default:
        return;
    }
}

// 0x003ee600 CKS08HeroAbilityHost_maybe_GetHeroEccBit1
uint8_t CKS08HeroAbilityHost::VfF0() {
    return static_cast<uint8_t>((m_pHero->m_unkecc >> 1) & 1u);
}

namespace {
constexpr uint8_t kAbilityElectricGrab = 7;  // the ability id the hero host treats as the electric grab (enemies' shields
                                             // and weapons, electric gauges, Malefor, the dragon city golem)
constexpr uint8_t kAbilityWindBeam = 0x12;   // the wind beam (Cynder's slot 7)

// 0x0025ab50 CKGrpSquad_GetFightZone (inlined): the enemy's squad's parent group, its detector group (+0x30).
const CKHkDetectorGroup* EnemyZoneDetectors(CKHkS08Enemy* enemy) {
    const CKGrpFightZone* zone = static_cast<const CKGrpFightZone*>(static_cast<CKGrpSquad*>(enemy->m_pGroupSquad)->m_pParent);
    return static_cast<const CKHkDetectorGroup*>(zone->m_pUnk30);
}
}  // namespace

// 0x003ee890 CKS08HeroAbilityHost_maybe_CanGrabTarget_maybe
uint8_t CKS08HeroAbilityHost::CanGrabTarget(CKAbilityElement* ability, IKSerializable* target, const CVector3* position) {
    if (target == nullptr) return 0;
    if (ability->GetAbilityId() != kAbilityWindBeam || target->IsKindOfClass(0x26c2) == 0) return 1;  // vt+0x50, vt+0x08
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(target);
    if (enemy->CanBeHeldAtPosition() == 0) return 0;  // 0x00289b38
    if (EnemyZoneDetectors(enemy)->IsTriggered(&position->x) == 0) return 0;  // vt+0xc4
    enemy->TeleportToPosition(position);  // 0x00289750
    return 1;
}

// 0x003ee6c0 CKS08HeroAbilityHost_maybe_GetGrabState_maybe (vt+0xe4). The held target (+0x124) is taken as an enemy.
IKSerializable* CKS08HeroAbilityHost::GetGrabHotspot(CKAbilityElement* ability) {
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pHero->m_pTargetedEnemy);
    if (enemy != nullptr) {
        if (ability->GetAbilityId() == kAbilityElectricGrab) {  // vt+0x50
            if (enemy->m_pHeldShield != nullptr) return enemy->GetGrabHotSpot();  // 0x0028a1c8
            if (enemy->m_pHeldWeapon != nullptr) return enemy->GetHotSpot(2);     // 0x002892e8
        }
        return enemy->GetSectorHotSpot(1);  // 0x0028a160
    }
    IKSerializable* hook = m_pHero->m_pTargetedMecaHook;
    if (hook == nullptr) return nullptr;
    if (hook->IsKindOfClass(0x2e42) != 0) {  // vt+0x08
        return static_cast<CKHkS08ElectricGauge*>(hook)->GetGrabHotSpot();  // vt+0x104 0x00492660
    }
    if (hook->IsKindOfClass(0x3502) != 0) {
        return static_cast<CKHkGolem*>(hook)->GetReference(6);  // vt+0xf8 0x009c5790
    }
    return nullptr;
}

// 0x003ee500 CKS08HeroAbilityHost_maybe_GetGrabPullRatio_maybe (vt+0xe8)
float CKS08HeroAbilityHost::GetGrabPullRatio(CKAbilityElement* ability) {
    IKSerializable* target = GetLockedTarget();  // vt+0xd4
    if (target == nullptr || target->IsKindOfClass(0x26c2) == 0) return 0.0f;  // TOC +0x43a8
    if (ability->GetAbilityId() != kAbilityWindBeam) return 0.0f;
    const CKHkS08Enemy* enemy = static_cast<const CKHkS08Enemy*>(target);
    return enemy->m_fWindGauge / enemy->m_pEnemyCpnt->m_unk25c;
}

// 0x003f00c8 CKS08HeroAbilityHost_maybe_GrabEnemy_maybe (vt+0xec). `target` null: the locked target (vt+0xd4).
// The electric grab (ability 7): an enemy: grab: whether it is a valid combat target; release while this hero holds it:
// the grabber cleared, the enemy released (EnterReleasedState 1), 1. An electric gauge: release: its +0x78 = 0 (vt+0xfc)
// and the hero leaves it (vt+0xf8), 1; grab with `mode`: +0x78 = 1, 1; grab: the hero enters it (vt+0xf4). Malefor and
// the dragon city golem: 1. Anything else (or an enemy the hero does not hold, released) goes on as below.
// The wind beam (0x12) on an enemy (else: whether the target is a fog horn, 0x2f02): release while this hero holds it:
// the grabber cleared; an enemy that cannot be held: 1; with `mode` and a `direction` other than the null vector the
// throw impact (`damage` along `direction`), else released (1); the hero does not hold it: the fog horn test. Grab with
// `mode`: held by this hero: whether it is a valid combat target, else whether the target aim point (vt+0xdc, 1, 0) is
// flat within 1.5 x the aim cone's +0x0c (the ability's +0xd0) of the hero (vt+0x10). Grab: the kinds 5 / 6 and an
// enemy with +0x898: 1; a partner holding it stops its combo (kind 0xff) and gets +0x1aec = 0.3; then the hero grabs it
// (SetGrabbedBy) and the answer is whether it holds it. Any other ability: 0.
uint8_t CKS08HeroAbilityHost::GrabEnemy(CKAbilityElement* ability, uint8_t grab, uint8_t mode, const CVector3* direction,
                                        IKSerializable* damage, IKSerializable* target) {
    if (target == nullptr) target = GetLockedTarget();  // vt+0xd4
    if (ability->GetAbilityId() == kAbilityElectricGrab && target != nullptr) {  // vt+0x50
        if (target->IsKindOfClass(0x26c2) != 0) {  // vt+0x08
            CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(target);
            if (grab != 0) return static_cast<uint8_t>(enemy->IsValidCombatTarget());  // 0x00289278
            if (enemy->GetGrabbingHero() == GetOwner()) {  // 0x00288fd0, vt+0x08
                enemy->ClearGrabber(GetOwner());  // 0x00288c98
                enemy->EnterReleasedState(1);     // 0x0028ab48
                return 1;
            }
        }
        if (target->IsKindOfClass(0x2e42) != 0) {
            CKHkS08ElectricGauge* gauge = static_cast<CKHkS08ElectricGauge*>(target);
            if (grab == 0) {
                gauge->SetGrabWeight(0.0f, m_pHero);  // vt+0xfc 0x00492658; TOC +0x43a8
                gauge->OnHeroLeave(m_pHero);          // vt+0xf8 0x004936b0
                return 1;
            }
            if (mode != 0) {
                gauge->SetGrabWeight(1.0f, m_pHero);  // TOC +0x4398
                return 1;
            }
            return static_cast<uint8_t>(gauge->OnHeroEnter(m_pHero));  // vt+0xf4 0x00493868
        }
        if (target->IsKindOfClass(0x3502) != 0) return 1;
        if (target->IsKindOfClass(0x31c2) != 0) return 1;
    }
    // 0x003f0164
    if (ability->GetAbilityId() != kAbilityWindBeam || target == nullptr) return 0;
    auto fogHornTest = [&]() { return static_cast<uint8_t>(target->IsKindOfClass(0x2f02) != 0 ? 1 : 0); };
    if (target->IsKindOfClass(0x26c2) == 0) return fogHornTest();
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(target);
    if (grab == 0) {  // 0x003f05d4
        if (enemy->GetGrabbingHero() != GetOwner()) return fogHornTest();
        enemy->ClearGrabber(GetOwner());
        if (enemy->CanBeHeldAtPosition() == 0) return 1;  // 0x00289b38
        const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x43a4)
        if (mode != 0 && !(kNull.x == direction->x && direction->y == kNull.y && direction->z == kNull.z)) {
            const CVector3 along = *direction;
            enemy->ApplyThrowImpactDamage(damage, &along);  // 0x0028ac90
            return 1;
        }
        enemy->EnterReleasedState(1);
        return 1;
    }
    if (mode != 0) {  // 0x003f06b8
        if (enemy->GetGrabbingHero() == GetOwner()) return static_cast<uint8_t>(enemy->IsValidCombatTarget());
        const CKAimCamembert* cone = static_cast<const CKAimCamembert*>(static_cast<CKGrabElement*>(ability)->m_pAimCone);
        const CVector3 aim = GetTargetAimPoint(1, 0);  // vt+0xdc
        const CVector3 at = GetOwnerPosition();        // vt+0x10
        const float dz = aim.z - at.z;
        const float dx = aim.x - at.x;
        const float distance = std::sqrt(ppc::fmadds(dx, dx, dz * dz));  // 0x00010690
        return distance < cone->m_afUnk04[2] * 1.5f ? 1 : 0;  // +0x0c, TOC +0x4400
    }
    const uint8_t kind = enemy->m_ui8EnemyClassType;
    if (kind == 6 || kind == 5 || enemy->m_unk898 != 0) return 1;
    if (enemy->GetGrabbingHero() == m_pHero->GetPartnerHero()) {  // 0x002f85f8
        m_pHero->GetPartnerHero()->SetComboActive(0, 0xff);  // 0x0032d9b0
        m_pHero->GetPartnerHero()->m_unk1aec = 0.3f;         // TOC +0x4404
    }
    enemy->SetGrabbedBy(GetOwner());  // 0x00288c58
    // The original's branch-free (|a ^ b| - 1) sign test: equal.
    return enemy->GetGrabbingHero() == GetOwner() ? 1 : 0;
}

// 0x003ef058 CKS08HeroAbilityHost_maybe_Slot20_maybe
CVector3 CKS08HeroAbilityHost::Vf20() { return m_pHero->GetHotspot4FlatDir(); }  // 0x0032ba68

// 0x003eea90 CKS08HeroAbilityHost_maybe_GetHeroA78_maybe
float CKS08HeroAbilityHost::GetOwnerConfig74() {
    if (m_pHero->GetMovementMode() != 1) return m_pHero->m_unka78;  // 0x003401b8
    return m_pHero->m_unk8a4;
}

// 0x003ee6a0 CKS08HeroAbilityHost_maybe_GetHeroAttachmentSets
IKSerializable* CKS08HeroAbilityHost::GetAttachmentSets() {
    return reinterpret_cast<IKSerializable*>(&m_pHero->m_apUnk1070[0][0]);
}

// 0x003f0808 CKS08HeroAbilityHost_maybe_AimAtTarget_maybe
IKSerializable* CKS08HeroAbilityHost::AimAtTarget(CKAbilityElement* ability, IKSerializable* aim) {
    const uint8_t id = ability->GetAbilityId();  // vt+0x50
    if (id == 9 || id == 0x10) {
        // Hot spot 2 (ability 9) or 6 (0x10): its world matrix's at row. DOTD: a missing hot spot (Spyro has no logical
        // hot spot 6) leaves the zeroed matrix; the original calls CSGHotSpot_GetWorldMatrix on null.
        CMatrix34 world{};
        CSGHotSpot* spot = static_cast<CSGHotSpot*>(GetHotspot(id == 9 ? 2 : 6));  // vt+0xcc
        if (spot != nullptr) spot->GetWorldMatrix(&world);  // 0x000ce970
        if (aim != nullptr) {
            const CVector3 direction = world.m_at;
            m_pHero->AcquireAbilityTarget(2.0f, 1.0f, aim, &direction, 3);  // 0x002ff6c8 (TOC +0x4408 / +0x4398)
        }
    } else {
        CVector3 direction{m_pHero->m_unk37c, m_pHero->m_unk380, m_pHero->m_unk384};
        // The null vector (0x00c50d64), compared word by word with fcmpu.
        if (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f) direction = Vf20();  // vt+0x20
        if (aim != nullptr) m_pHero->AcquireAbilityTarget(2.0f, 1.0f, aim, &direction, 3);  // 0x002ff6c8
    }
    return GetLockedTarget();  // vt+0xd4
}

// 0x003ef830 StaticInitAndDestruction_3ef830 (_GLOBAL__I_3ef870): two file statics (0x00ceb0b0, 0x00ceb0b4) set to
// -1.0f. Nothing in the game reads them.
namespace {
[[maybe_unused]] float s_unkceb0b0 = -1.0f;
[[maybe_unused]] float s_unkceb0b4 = -1.0f;
}  // namespace
