// Reconstructed original translation unit: 0x326498-0x32bb30 (GAME_TOC1, main_toc1), 73 functions, 63 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: CopyHeroDerivedVelocity (1), CopyHeroAdjustedPosition (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x326498  CKHkS08Hero_ActState4_Ability_Condition
//   [x] 0x3267e8  CKHkS08Hero_ActState1_FuryCoop_maybe_Condition
//   [x] 0x326830  CKHkS08Hero_CanStartFury_maybe
//   [x] 0x326950  CKHkS08Hero_ActState1_FuryCoop_maybe
//   [x] 0x326ee0  CKHkS08Hero_CancelAbilityA
//   [x] 0x3272d8  CKHkS08Hero_CancelAbilityB
//   [x] 0x3276d0  CKHkS08Hero_ActState4_AbilityHandler
//   [x] 0x328e40  CKHkS08Hero_SetFuryMode_maybe
//   [x] 0x329d88  CKHkS08Hero_SetExternalDisplacementFlag_maybe
//   [x] 0x329d90  CKHkS08Hero_GetCurrentSpeed_maybe  (CKHkS08Hero.h)
//   [x] 0x329d98  CKHkS08Hero_IsComboKind1Active  (read inline by its caller: CKHkS08Enemy_12.cpp ApplyPendingDamage)
//   [x] 0x329da0  CKHkS08Hero_IsComboKind5Active  (read inline by its caller: CKHkS08Enemy_12.cpp ApplyPendingDamage)
//   [ ] 0x329da8  FUN_00329da8  [dead]
//   [x] 0x329de0  CKHkS08Hero_GetActiveHitSpheres  (read inline by its callers: CKHkS08Enemy.cpp ProcessContacts, CKHkS08Enemy_11.cpp State01)
//   [x] 0x329df8  CKHkS08Hero_GetGrabTarget  (CKHkS08Hero.h)
//   [x] 0x329e00  CKHkS08Hero_EnableSubNode_maybe
//   [x] 0x329e80  CKHkS08Hero_GetSubNode_maybe
//   [x] 0x329eb8  CKHkS08Hero_GetSubNodeB_maybe
//   [ ] 0x329ef0  CKHkS08Hero_IsHitConfirmed_maybe  [dead]
//   [x] 0x329f00  CKHkS08Hero_SetHitConfirmed  (CKHkS08Hero.h)
//   [x] 0x329f20  CKHkS08Hero_GetCurrentBlowFlag61
//   [x] 0x32a000  CKHkS08Hero_GetCarrier  (CKHkS08Hero.h)
//   [x] 0x32a008  CKHkS08Hero_GetHeightAboveGround_maybe
//   [x] 0x32a010  CKHkS08Hero_IsAttachedToContextualMeca
//   [x] 0x32a090  CKHkS08Hero_IsCarryingTransportableKey_maybe
//   [x] 0x32a148  CKHkS08Hero_IsCarryingTransportableWeight_maybe
//   [x] 0x32a200  CKHkS08Hero_IsCarryingPowerBucket_maybe
//   [x] 0x32a2b8  CKHkS08Hero_IsCarryingFilledPowerBucket_maybe
//   [ ] 0x32a390  CKHkS08Hero_SetFlagECCBit5_maybe  [dead]
//   [x] 0x32a3b0  CKHkS08Hero_GetComboTimerMultiplier_maybe  (read inline by its caller: k2000/misc/OnNewHit.cpp)
//   [x] 0x32a3d0  CKHkS08Hero_GetStatusDecayRate_maybe  (CKHkS08Enemy::HeroStatusDecayRate)
//   [ ] 0x32a3f0  CKHkS08Hero_IsInFuryMode_maybe  [dead]
//   [ ] 0x32a400  CKHkS08Hero_GetFlagECCBit5_maybe  [dead]
//   [x] 0x32a410  CKHkS08Hero_SetNearCrumblyZoneFlags_maybe  (written inline by its caller: CKHkS08CrumblyZoneMultiState_2.cpp Update)
//   [x] 0x32a420  CKHkS08Hero_GetNearCrumblyZoneFlag1DD1_maybe  (read inline by its caller: CKHkS08Enemy_7.cpp UpdateMoveDestination)
//   [x] 0x32a428  CKHkS08Hero_GetFlagED4Bit3_maybe  (read inline by its callers: CKHkS08Hero.cpp CanAttachTo, CKHkS08Hero_17.cpp)
//   [x] 0x32a438  CKHkS08Hero_SetCarryingObject_maybe  (CKHkS08Hero.h)
//   [x] 0x32a458  StaticInitAndDestruction_32a458  (the two file statics at the end)
//   [ ] 0x32a488  _GLOBAL__I_32a488
//   [ ] 0x32a498  _GLOBAL__D_32a498
//   [ ] 0x32a4a8  CKHkS08Hero_IsMovementMode0_Thunk  [dead: no pointer to its descriptor 0xb9d658, no call]
//   [ ] 0x32a4d0  CKHkS08Hero_IsFlying_Thunk  [dead: no pointer to its descriptor 0xb9d660, no call]
//   [ ] 0x32a4f8  CKHkS08Hero_ShouldStayClimbing_Thunk  [dead: no pointer to its descriptor 0xb9d668, no call]
//   [x] 0x32a520  CKHkS08Hero_ShouldJoinPartnerFlight_Thunk
//   [x] 0x32a548  CKHkS08Hero_SetMoveDestination
//   [x] 0x32a580  CKHkS08Hero_ValidateOrAcquireTargetThunk_maybe  (thunk: the callers call ValidateOrAcquireTarget 0x2ff978)
//   [ ] 0x32a5a8  CKHkS08Hero_PlaySoundIfIdleDefaultArgs_maybe  [dead]
//   [ ] 0x32a5e0  CKHkS08Hero_StopSound_Thunk_maybe  [dead]
//   [ ] 0x32a608  CKHkS08Hero_PlaySoundDefault  [dead: no pointer to its descriptor 0xb9d698, no call]
//   [x] 0x32a638  CKHkS08Hero_SetExternallyPositionedAndPhysics_maybe
//   [x] 0x32a698  CKHkS08Hero_IsInCombo  (CKHkS08Hero.h)
//   [x] 0x32a6c0  CKHkS08Hero_GetMovementMode_Thunk  (thunk: target called directly)
//   [x] 0x32a6e8  CKHkS08Hero_SetExternalDisplacement_maybe
//   [x] 0x32a708  CKHkS08Hero_CopyAimDirection_maybe  (CKHkS08Hero.h)
//   [x] 0x32a730  CKHkS08Hero_GetPredictedVelocity_maybe
//   [x] 0x32a758  CopyHeroAdjustedPosition
//   [x] 0x32a7a8  CKHkS08Hero_IsUsingWindBeam
//   [x] 0x32a840  CKHkS08Hero_GetEarthBoulderFlag2CC_maybe
//   [x] 0x32a8d0  CKHkS08Hero_GetAbilityElementLevel
//   [x] 0x32a938  CKHkS08Hero_SetAttackSphere0
//   [x] 0x32aa28  CKHkS08Hero_SetAttackSphere2
//   [x] 0x32ab18  CKHkS08Hero_SetAttackSphere1
//   [x] 0x32ac08  CKHkS08Hero_GetElementColor_maybe
//   [x] 0x32ac88  CKHkS08Hero_CrossfadeAnimResource_maybe
//   [x] 0x32ad80  CKHkS08Hero_PlayAnimResource_maybe
//   [x] 0x32aec8  CKHkS08Hero_SetAnimPairAndWeight_maybe
//   [x] 0x32afc8  CKHkS08Hero_ShareCollectedBonusWithPartner_maybe
//   [x] 0x32b138  CKHkS08Hero_GetHotspot4AimDir_maybe
//   [ ] 0x32b240  CKHkS08Hero_GetFlagECCBit5_2_maybe  [dead]
//   [ ] 0x32b250  FUN_0032b250  [dead]
//   [x] 0x32b500  CKHkS08Hero_UpdateMoveTo_maybe
//   [ ] 0x32b9c8  FUN_0032b9c8  [dead]
//   [x] 0x32ba68  CKHkS08Hero_GetHotspot4FlatDir_maybe
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/services/ICollisionMesh.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include <cstring>
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/components/CKMoveCpntUpdater.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "Spyro2008/logic/CKS08HeroBlow.h"
#include "Spyro2008/logic/CKS08HeroCombo.h"
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/misc/CKS08HeroAbilityHost.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKAbilityElement.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "Spyro2008/ui/CKHkS08Bonus.h"
#include "k2000/memory/CKGrpBonusPool.h"
#include "k2000/ui/CKGrpBonus.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/logic/CKEarthBoulder.h"

// 0x003267e8 CKHkS08Hero_ActState1_FuryCoop_maybe_Condition: the fury flag (+0xed4 bit 6) or a running fury timer
// (+0x1b00; the same test as the animation machine's Fury condition).
uint8_t CKHkS08Hero::ActFuryCoopCondition(IKTime*, uint8_t) {
    if ((m_unked4 & 0x40u) != 0) return 1;
    return !(m_unk1b00 <= 0.0f) ? 1 : 0;  // ble: a NaN timer counts as running
}

// 0x00326950 CKHkS08Hero_ActState1_FuryCoop_maybe: the fury's charge. Enter: the combo off, +0x354 bit 11, +0xec4 bits
// 9 / 8 / 11, a flying hero put on the ground, the facing (+0x11cc) the camera's real z axis reversed, the move speed
// +0x1d14 1 and +0x1d10 on, +0xec8 bits 7 / 9 set and 3 / 4 cleared, +0xecc bit 27, +0x35c bit 7, the charge effects
// (SpawnFuryChargeFx), the finisher camera blend +0x1108.. (300, 300, 100, the camera's real field of view, 0, the
// group's curve +0x360 at 0, 0), the release not done (+0x1dc0). Tick: while the fury timer +0x1b00 runs (above 0) the
// release effects once; else, with t = 1 - the group's +0x2d4 / +0x18c, the fury node (+0x1de0) faded by its curve
// (+0x1dec) at t and moved by its movement (+0x1de8) from the identity, the finisher camera blend of a hero its player
// does not control (the curve +0x360 at t, the camera's field of view), and the hero raised by 2 dt / +0x18c. Then
// +0x1511 set. Leave: the release effects unless done, the flags back.
uint8_t CKHkS08Hero::ActFuryCoop(IKTime* clock, int32_t phase, uint8_t other) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);  // TOC +0x261c -> +0x70
    if (phase == 1) {
        SetComboActive(0, 0xff);  // 0x0032d9b0
        m_unk354 = (m_unk354 & ~0x800u) | 0x800u;
        m_unkec4 = (m_unkec4 & ~0x200u) | 0x200u;
        if (static_cast<int8_t>(GetMovementMode()) == 1) SetMovementMode(0);  // 0x003401b8 / 0x00340c18
        m_unkec4 = (m_unkec4 & ~0x100u) | 0x100u;
        m_unkec4 = (m_unkec4 & ~0x800u) | 0x800u;
        m_unk11cc = -camera->m_v3RealAxisZ.x;  // +0x5c8
        m_unk11d0 = -camera->m_v3RealAxisZ.y;
        m_unk11d4 = -camera->m_v3RealAxisZ.z;
        m_unk1d14 = 1.0f;  // TOC +0x2628
        m_unk1d10 = 1;
        m_unkec8 = (m_unkec8 & ~0x80u) | 0x80u;
        m_unkec8 = (m_unkec8 & ~0x200u) | 0x200u;
        m_unkecc = (m_unkecc & ~0x8000000u) | 0x8000000u;
        m_unkec8 &= ~0x18u;
        m_unk35c = (m_unk35c & ~0x80u) | 0x80u;
        SpawnFuryChargeFx();  // 0x0033bf58
        m_unk110c = 300.0f;  // TOC +0x2634
        m_unk1110 = 100.0f;  // TOC +0x2630
        m_unk1118 = 0.0f;    // TOC +0x2624
        m_unk1120 = 0.0f;
        m_unk1108 = 300.0f;
        m_unk1114 = camera->m_fRealFov;  // +0x5d4
        m_unk111c = static_cast<CKCurve2DCpnt*>(group->m_pUnk360)->Evaluate(0.0f);  // 0x00249ea8
        m_unk1dc0 = 0;
        return other;
    }
    if (phase != 0) {
        if (m_unk1dc0 == 0) SpawnFuryReleaseFx();  // 0x0033bbe0
        m_unk354 &= ~0x800u;
        m_unkec4 &= ~0xb00u;
        m_unkec8 &= ~0x80u;
        m_unk1d10 = 0;
        m_unkec8 &= ~0x200u;
        m_unkecc &= ~0x8000000u;
        m_unkec8 = (m_unkec8 & ~0x8u) | 0x8u;
        m_unkec8 = (m_unkec8 & ~0x10u) | 0x10u;
        m_unk35c &= ~0x80u;
        return other;
    }
    if (m_unk1b00 > 0.0f) {  // TOC +0x2624
        if (m_unk1dc0 == 0) {
            m_unk1dc0 = 1;
            SpawnFuryReleaseFx();
        }
    } else {
        const float dt = clock->m_afDeltaTime[0];
        float charge;
        std::memcpy(&charge, &group->m_unk2d4[0], sizeof(charge));  // +0x2d4 (a float)
        const float t = 1.0f - charge / group->m_unk18c;  // TOC +0x2628
        CNode* node = static_cast<CNode*>(m_unk1de0);
        if (node != nullptr) {
            SetNodeAlphaFromCurve(node, m_unk1dec, t);
            node->SetIdentity();  // 0x000d08f0
            float sample[10];
            CKMoveCpntUpdater* updater = static_cast<CKMoveCpntUpdater*>(m_unk1de8);
            updater->Evaluate(dt, sample);           // 0x0024db60
            updater->ApplyToNode(sample, node);  // 0x0024d9c0
        }
        if (m_ui8Hero != m_ui8TrackedLeader) {
            m_unk1118 = 0.0f;
            m_unk111c = static_cast<CKCurve2DCpnt*>(group->m_pUnk360)->Evaluate(t);
            Math_ApproachWithAccelDecel(dt, &m_unk1108);  // 0x00243a10
            camera->m_pCurrentCamera->SetFov(m_unk1114);  // +0x474, vt+0x68
        }
        m_unk550 = (dt + dt) / group->m_unk18c + m_unk550;
    }
    m_unk1511 = 1;
    return other;
}

// The fury node's geometry walk (inlined in ActFuryCoop and SpawnFuryChargeFx).
void CKHkS08Hero::SetNodeAlphaFromCurve(IKSerializable* node, IKSerializable* curve, float x) {
    for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        const float value = static_cast<CKCurve2DCpnt*>(curve)->Evaluate(x);  // 0x00249ea8
        uint8_t alpha = 0;
        if (value <= 0.0f) {
            alpha = 0;
        } else if (value >= 255.0f) {  // TOC +0x262c
            alpha = 0xff;
        } else {
            alpha = static_cast<uint8_t>(ppc::fctiwz(value));  // the low byte (stfiwx, lbz +3)
        }
        if (alpha != 0xff && (geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (mode != 0 && mode <= 6) alpha = 0xff;
        }
        const uint32_t translucent = alpha != 0xff ? 1u : 0u;
        geometry->m_cGeometryColor[3] = alpha;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != translucent) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (translucent << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// 0x00326830 CKHkS08Hero_CanStartFury_maybe: never with +0x358 bit 0; always for a hero its player does not control;
// else not while its dragon's game manager byte +0xe10 is set; with neither hero's +0xecc bit 5 the hero needs +0x1afc
// above 0 and no combo kind active, else no combo kind flag; then not with +0xec8 bit 22, and only without bit 23.
uint8_t CKHkS08Hero::CanStartFury() {
    if ((m_unk358 & 1u) != 0) return 0;
    if (m_ui8TrackedLeader != m_ui8Hero) return 1;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x261c
    const uint8_t* record =
        reinterpret_cast<const uint8_t*>(&manager->m_unkDF4[1]) + static_cast<uint32_t>(m_ui8TrackedLeader) * 0x20u;
    if (record[0x18] != 0) return 0;  // +0xe10 + 0x20 x dragon (read as ActAbility reads it)
    if ((m_unkecc & 0x20u) == 0 && (GetPartnerHero()->m_unkecc & 0x20u) == 0) {  // 0x002f85f8
        if (!(m_unk1afc > 0.0f)) return 0;           // TOC +0x2624; bgt
        if (IsAnyComboKindActive() != 0) return 0;  // 0x002fd030
    } else if (IsComboKindFlagSet() != 0) {         // 0x002fc1b0
        return 0;
    }
    if ((m_unkec8 & 0x00400000u) != 0) return 0;
    return static_cast<uint8_t>(((m_unkec8 >> 23) & 1u) ^ 1u);
}

// 0x00328e40 CKHkS08Hero_SetFuryMode_maybe: +0xed0 bit 4 = `on`. On: the element kept in +0x1cc8 and 4 (the fury
// element) selected, the running abilities cancelled (A then B, the fury element's end filter started in place of a
// running filter), the element HUD, and (heroes 0 / 1, without an aura yet) the point light +0x1dc8 attached to hot
// spot 5 and taken from the FX pool into +0x1dcc. Off: the abilities cancelled (B with the end filter started, A with it
// started: 0x9bdc18, Ghidra CKSrvFx_AcquireFx, reserves nothing: StartEffect), the kept element back, the element
// HUD, and the aura released (vt+0x58).
void CKHkS08Hero::SetFuryMode(int32_t on) {
    m_unked0 = (m_unked0 & ~0x10u) | ((static_cast<uint32_t>(on) << 4) & 0xfffffff0u);
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x261c
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKSerializable* const* endFilters = &m_unk1ce0;  // +0x1ce0[5]
    if (on != 0) {
        m_unk1cc8 = m_unk1cc4;
        m_unk1cc4 = 4;
        if (m_unk1ac5 != 0) CancelAbilityA(0);  // inlined (the end filter of the fury element)
        if (m_unk1ac6 != 0) CancelAbilityB(0);
        if (m_ui8Hero == 0) {
            manager->ShowSpyroSelectedElementHud(static_cast<uint8_t>(m_unk1cc4));  // 0x5039e8 (the byte +0x1cc7)
        } else if (m_ui8Hero == 1) {
            manager->ShowCynderSelectedElementHud(static_cast<uint8_t>(m_unk1cc4));  // 0x5024d8
        } else {
            // BUG(original): another hero reads a stale register as its hot spot; LVL010 has heroes 0 and 1 only.
            return;
        }
        IKSerializable* spot = m_apHotSpots[5];  // +0x14
        CVector3 position;
        static_cast<CSGHotSpot*>(spot)->GetWorldPosition(&position);  // 0x000ce790 (the result is not used)
        if (m_unk1dcc != nullptr) return;
        CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_unk1dc8);
        light->m_pAttachHotSpot = spot;
        light->m_pAttachNode = nullptr;
        m_unk1dcc = fx->AcquireFx(reinterpret_cast<IKFxData*>(light), this);  // inlined
        return;
    }
    if (m_unk1ac6 != 0) CancelAbilityB(0);  // inlined (StartEffect)
    if (m_unk1ac5 != 0) {
        m_unk1ac5 = 0;
        CKAbilityElement* ability = static_cast<CKAbilityElement*>(m_unk1cc0);
        if (ability != nullptr) ability->Stop(0);  // vt+0x5c
        if (m_unk1cf4 != nullptr) {
            static_cast<IKFx*>(m_unk1cf4)->StopAndRelease(this);  // vt+0x58
            m_unk1cf4 = nullptr;
            fx->StartEffect(reinterpret_cast<IKFxData*>(endFilters[m_unk1cc4]), this);  // 0x009bdc18 (no reservation)
        }
    }
    m_unk1cc4 = m_unk1cc8;
    if (m_ui8Hero == 0) {
        manager->ShowSpyroSelectedElementHud(static_cast<uint8_t>(m_unk1cc4));
    } else if (m_ui8Hero == 1) {
        manager->ShowCynderSelectedElementHud(static_cast<uint8_t>(m_unk1cc4));
    }
    if (m_unk1dcc == nullptr) return;
    static_cast<IKFx*>(m_unk1dcc)->StopAndRelease(this);  // vt+0x58
    m_unk1dcc = nullptr;
}

// 0x00329d88 CKHkS08Hero_SetExternalDisplacementFlag_maybe: +0x1674 (the hero group's tether pull is on).
void CKHkS08Hero::SetExternalDisplacementFlag(uint8_t on) { m_unk1674 = on; }

// ---- pre-C2.7 gamemgr: the hero death state's calls ----
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/services/CKSrvDynamic.h"

namespace {
// 0x00a70728: the sub-node count of each hero (the byte at +0x08 of the TOC table 0x00a70720).
const uint8_t kNbSubNodesB[8] = {0x0e, 0x0e, 0, 0, 0, 0, 0, 0};
}  // namespace

// 0x00329eb8 CKHkS08Hero_GetSubNodeB_maybe
IKSerializable* CKHkS08Hero::GetSubNodeB(uint32_t index) {
    // BUG(original): a hero index above 7 reads past the table (DotD has two heroes).
    if (!(index < kNbSubNodesB[m_ui8Hero])) return nullptr;  // cmplw; ble
    return m_apObjects[index];
}

namespace {
// 0x00a70720: the particle node count per hero (17 for both dragons).
const uint8_t kNbParticleNodes[8] = {0x11, 0x11, 0, 0, 0, 0, 0, 0};
}  // namespace

// 0x00329e00 CKHkS08Hero_EnableSubNode_maybe: particle node `index` (+0x50, below the hero's count) emits: its properties
// bits 0x200 / 0x400 set and 0x80000 cleared, its emission speed adjustment 0, its emitter's flags 0x2 | 0x8 set.
void CKHkS08Hero::EnableSubNode(uint32_t index) {
    // BUG(original): a hero index above 7 reads past the table (DotD has two heroes).
    if (!(index < kNbParticleNodes[m_ui8Hero])) return;  // cmplw; blelr
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_apParticles[index]);
    if (node == nullptr) return;
    node->m_sgProperties = ((node->m_sgProperties | 0x200u) | 0x400u) & ~0x80000u;
    node->m_fEmissionSpeedAdjustment = 0.0f;
    node->m_pRpPrtStdEmitter->flag |= 0xau;
}

// 0x00329e80 CKHkS08Hero_GetSubNode_maybe: particle node `index` (+0x50) below the hero's count, else null.
IKSerializable* CKHkS08Hero::GetSubNode(uint32_t index) {
    if (!(index < kNbParticleNodes[m_ui8Hero])) return nullptr;
    return m_apParticles[index];
}

// 0x0032a200 CKHkS08Hero_IsCarryingPowerBucket_maybe: the carrier's (+0xfb8) carried object (vt+0x80) has class id 0xc3.
uint8_t CKHkS08Hero::IsCarryingPowerBucket() {
    if (m_unkfb8 == nullptr) return 0;
    IKSerializable* carried = static_cast<CKS08CarrierHero*>(m_unkfb8)->GetCarriedObject();
    if (carried == nullptr) return 0;
    return carried->GetClassID() == 0xc3 ? 1 : 0;  // vt+0x18
}

// 0x0032a2b8 CKHkS08Hero_IsCarryingFilledPowerBucket_maybe: a carried power bucket whose vt+0x104 is above 0.
uint8_t CKHkS08Hero::IsCarryingFilledPowerBucket() {
    if (m_unkfb8 == nullptr) return 0;
    IKSerializable* carried = static_cast<CKS08CarrierHero*>(m_unkfb8)->GetCarriedObject();
    if (carried == nullptr || carried->GetClassID() != 0xc3) return 0;
    return static_cast<CKHkS08TransportableBase*>(carried)->Vf104() > 0.0f ? 1 : 0;  // vt+0x104; TOC +0x2684
}

// 0x0032ba68 CKHkS08Hero_GetHotspot4FlatDir_maybe: hot spot 4's world forward (at) flattened (y 0) and normalised (kept
// as is at length 0).
CVector3 CKHkS08Hero::GetHotspot4FlatDir() {
    CMatrix34 world;
    static_cast<CSGHotSpot*>(m_apHotSpots[4])->GetWorldMatrix(&world);  // 0x000ce970
    CVector3 out;
    out.y = 0.0f;  // TOC +0x2684
    const float x = world.m_at.x;
    const float sq = ppc::fmadds(x, x, 0.0f);
    out.z = world.m_at.z;
    out.x = x;
    const float length = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(out.z, out.z, sq))));  // 0x00010690
    if (length != 0.0f) {
        const float k = 1.0f / length;  // TOC +0x2688
        out.z = k * out.z;
        out.x = k * out.x;
        out.y = k * out.y;
    }
    return out;
}

// 0x0032a638 CKHkS08Hero_SetExternallyPositionedAndPhysics_maybe
void CKHkS08Hero::SetExternallyPositionedAndPhysics(uint8_t locked, const float* position, const float* direction) {
    SetLockedToObject(locked, position, direction);  // 0x3622a8
    static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic)->SetEntryFlag(this, static_cast<uint8_t>(locked ^ 1));  // 0x23aff8
}

// 0x0032ad80 CKHkS08Hero_PlayAnimResource_maybe (vt+0xc0)
void CKHkS08Hero::PlayAnimResource(float start, uint32_t animation) {
    if ((m_unk358 & 2u) == 0) return;
    m_animBlendSlot10f0.StartCrossfade(0.0, 1);  // 0x7a848; TOC +0x2684
    m_unk360 = (m_unk360 & ~0x800u) | 0x800u;
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    slot->m_unk14 = 0;
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    if (blender != nullptr) blender->m_unk58 = slot->m_unk10 != 0 ? 1.0f : 0.0f;  // the words 0x3f800000 (TOC +0x2688) / 0
    // BUG(original): without a blender the controller is read from address +0x50.
    static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])->SetAnim(start, animation, false);  // 0x7ab20
}

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

// 0x0032a010 CKHkS08Hero_IsAttachedToContextualMeca
uint8_t CKHkS08Hero::IsAttachedToContextualMeca() {
    if ((m_unk358 & 1u) == 0 || m_unk90 == nullptr) return 0;
    return m_unk90->IsKindOfClass(0x2a82) != 0 ? 1 : 0;  // vt+0x08
}

// 0x0032a090 CKHkS08Hero_IsCarryingTransportableKey_maybe
uint8_t CKHkS08Hero::IsCarryingTransportableKey() {
    if (m_unkfb8 == nullptr) return 0;
    IKSerializable* carried = static_cast<CKS08CarrierHero*>(m_unkfb8)->m_pCarriedObject;  // vt+0x80 0x9c54c8
    if (carried == nullptr) return 0;
    return carried->GetClassID() == 0xc2 ? 1 : 0;  // vt+0x18
}

// 0x0032a148 CKHkS08Hero_IsCarryingTransportableWeight_maybe: the carried object is of class id 0xc5 (vt+0x18).
uint8_t CKHkS08Hero::IsCarryingTransportableWeight() {
    if (m_unkfb8 == nullptr) return 0;
    IKSerializable* carried = static_cast<CKS08CarrierHero*>(m_unkfb8)->m_pCarriedObject;  // vt+0x80 0x9c54c8
    if (carried == nullptr) return 0;
    return carried->GetClassID() == 0xc5 ? 1 : 0;
}

namespace {
// The ability slot (+0x1bf8 index) of each element (+0x1cc4) per hero: 0x00c40978 / 0x00c40980 (through TOC +0x2620)
// for the second button (+0xf54), 0x00c40988 / 0x00c40990 (TOC +0x2618) for the first (+0xf40).
constexpr int8_t kAbilitySlotSecond[2][5] = {{1, 3, 4, 7, 9}, {1, 2, 4, 7, 5}};
constexpr int8_t kAbilitySlotFirst[2][5] = {{0, 2, 5, 6, 9}, {0, 3, 9, 6, 5}};
}  // namespace

// 0x00326498 CKHkS08Hero_ActState4_Ability_Condition: the ten ability cooldowns count down (those above 0, by the clock's
// dt). Then, unless +0xec8 bit 23 or +0x1507: an active ability holds the state; else not from the state `row` itself
// (+0xcc), and only on the ground with +0x354 bit 0 clear, or higher than +0x8c8 (flying) / +0x8c4 (on the ground) above
// the ground (+0x550 - +0x574), and not while +0x1acc: the first button (+0xf44 in state 1 / 3) with its element's
// ability ready (cooldown 0 or less) and a level in the element (or element 4) starts it; else the second button
// (+0xf58) with its element's ability ready.
uint8_t CKHkS08Hero::ActAbilityCondition(IKTime* clock, uint8_t row) {
    const float dt = clock->m_afDeltaTime[0];
    for (float& cooldown : m_afAbilityCooldown) {
        if (cooldown > 0.0f) cooldown = cooldown - dt;  // TOC +0x2624 (0)
    }
    if ((m_unkec8 & 0x00800000u) != 0 || m_unk1507 != 0) return 0;
    if (IsAbilityActive() != 0) return 1;  // 0x002fc228
    if (row == m_unkCC) return 0;
    bool allowed = false;
    if (static_cast<int8_t>(GetMovementMode()) == 0 && (m_unk354 & 1u) == 0) {
        allowed = true;
    } else {
        if (static_cast<int8_t>(GetMovementMode()) == 1 && m_unk550 - m_unk574 > m_unk8c8) {
            allowed = true;
        } else if (static_cast<int8_t>(GetMovementMode()) == 0 && m_unk550 - m_unk574 > m_unk8c4) {
            allowed = true;
        }
    }
    if (!allowed || m_unk1acc != 0) return 0;
    const uint8_t hero = m_ui8Hero;
    const uint32_t element = m_unk1cc4;
    if (m_unkf44 == 3u || m_unkf44 == 1u) {
        const int8_t slot = kAbilitySlotFirst[hero][element];
        if (m_afAbilityCooldown[slot] <= 0.0f) {
            CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x261c -> +0x8c
            if (manager->GetElementLevel(hero, static_cast<uint8_t>(element)) != 0) return 1;  // 0x004f9558
            if (element == 4u) return 1;
            if (m_unk1acc != 0) return 0;
        }
    }
    if (m_unkf58 != 3u && m_unkf58 != 1u) return 0;
    const int8_t slot = kAbilitySlotSecond[hero][element];
    return m_afAbilityCooldown[slot] <= 0.0f ? 1 : 0;
}

// 0x0032a7a8 CKHkS08Hero_IsUsingWindBeam: hero 1 (+0x24) whose +0x1cc0 is an object of class 0xa50c (vt+0x08).
uint8_t CKHkS08Hero::IsUsingWindBeam() {
    if (m_ui8Hero != 1) return 0;
    IKSerializable* beam = m_unk1cc0;
    if (beam == nullptr) return 0;
    return beam->IsKindOfClass(0xa50c) != 0 ? 1 : 0;
}

namespace {
// 0x00b01038 (TOC +0x26a4): per dragon (0x00c40998 / 0x00c409b0), the element of each ability id (0xff: none); the
// same values as CKS08HeroAbilityHost's 0x00b01048.
constexpr uint8_t kAbilityElementOfIdHero[2][21] = {
    {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
    {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 1, 1, 2, 4, 3, 3, 4, 2},
};
}  // namespace

// 0x0032a8d0 CKHkS08Hero_GetAbilityElementLevel: the level of the element of ability `id` for this hero's dragon
// (+0x24; GetElementLevel), 0 when the ability has no element for it. The original indexes the table unchecked (the
// callers pass ability ids 0..0x12).
uint8_t CKHkS08Hero::GetAbilityElementLevel(uint8_t id) {
    const uint8_t dragon = m_ui8Hero;
    const uint8_t element = kAbilityElementOfIdHero[dragon][id];
    if (element == 0xff) return 0;
    return static_cast<uint8_t>(
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->GetElementLevel(dragon, element));  // 0x004f9558
}

// 0x0032a938 CKHkS08Hero_SetAttackSphere0 / 0x0032ab18 CKHkS08Hero_SetAttackSphere1 / 0x0032aa28
// CKHkS08Hero_SetAttackSphere2 (three copies, one per sphere +0x1b8c / +0x1b90 / +0x1b94). The enabled test is the
// volume's info bit 0 (+0x18).
void CKHkS08Hero::SetAttackSphere(uint32_t index, uint8_t on, float radius, int8_t hotspot, IKSerializable* damage) {
    IKSerializable* const spheres[3] = {m_unk1b8c, m_unk1b90, m_unk1b94};
    m_unk1bac = 0;
    IKBoundingVolume* sphere = static_cast<IKBoundingVolume*>(spheres[index]);
    if (on == 0) {
        if ((sphere->m_ba8Infos & 1u) == 0) return;
        m_unk1bac = 0xffffffffu;
        SetCollisionVolumeEnabled(sphere, 0);  // 0x00352f10
        return;
    }
    if ((sphere->m_ba8Infos & 1u) != 0) return;
    AttachVolumeToHotspot(sphere, hotspot, radius);  // 0x00352f78
    static_cast<IKBoundingVolume*>(spheres[index])->m_unk1c = damage;
    ActivateAttackSphere(spheres[index], 1);  // 0x0030cad0
}

// 0x00329f20 CKHkS08Hero_GetCurrentBlowFlag61
uint8_t CKHkS08Hero::GetCurrentBlowFlag61() {
    CKS08HeroCombo* combo = static_cast<CKS08HeroCombo*>(m_unk1a88);
    if (combo == nullptr) return 0;
    if (combo->GetBlow() == nullptr) return 0;  // vt+0x54
    return combo->GetBlow()->VfAC();            // vt+0xac
}

// 0x0032ac08 CKHkS08Hero_GetElementColor_maybe
uint32_t CKHkS08Hero::GetElementColor(uint32_t which) const {
    if (which == 0) return (&m_unk1c20)[m_unk1cc4];
    if (which == 1) return (&m_unk1c34)[m_unk1cc4];
    return 0xffffffffu;  // 0x00c50dfc (white)
}

// 0x0032afc8 CKHkS08Hero_ShareCollectedBonusWithPartner_maybe (bonus-crumbly, C2.8)
void CKHkS08Hero::ShareCollectedBonusWithPartner(IKSerializable* bonusObject) {
    CKHkS08Bonus* bonus = static_cast<CKHkS08Bonus*>(bonusObject);
    const uint32_t type = static_cast<CKGrpBonusPool*>(bonus->m_pUnk28)->m_ui32BonusType;
    if (type - 1u > 1u) return;
    if (bonus->m_unk34 != 0) return;
    if ((m_unked0 & 0x10000u) == 0) return;
    CKGrpBonus* group = static_cast<CKGrpBonus*>(g_pEngine->m_gameManager->m_unk04[3]);  // the game manager's +0x10
    if (group == nullptr) return;
    CVector3 at;
    static_cast<CSGHotSpot*>(GetHotSpot(5))->GetWorldPosition(&at);  // 0x00361b70, 0x000ce790
    IKSerializable* partner = static_cast<IKGrpHero*>(m_pGrpHero)->m_apHeros[m_ui8Hero == 0 ? 1 : 0];
    IKSerializable* shared = group->SpawnBonusObject(type, &at, 1);  // 0x005b0df8
    if (shared == nullptr) return;
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    static_cast<CKHkS08Bonus*>(shared)->VfE4(&kAxisY, partner);  // vt+0xe4
}

// 0x0032a840 CKHkS08Hero_GetEarthBoulderFlag2CC_maybe (bonus-crumbly, C2.8)
uint8_t CKHkS08Hero::GetEarthBoulderFlag2CC() {
    if (m_ui8Hero != 0) return 0;
    IKSerializable* ability = m_apUnk1bd0[4];  // +0x1be0
    if (ability->IsKindOfClass(0x95cc) == 0) return 0;  // vt+0x08 CKEarthBoulder
    return static_cast<CKEarthBoulder*>(ability)->m_unk2cc;
}

// 0x0032b138 CKHkS08Hero_GetHotspot4AimDir_maybe
CVector3 CKHkS08Hero::GetHotspot4AimDir(int32_t raw) {
    CMatrix34 world;
    static_cast<CSGHotSpot*>(m_apHotSpots[4])->GetWorldMatrix(&world);  // 0x000ce970 (+0x4c's +0x10)
    CVector3 out = world.m_at;
    if (raw != 0) return out;
    out.y = m_unk12a4;
    const float length =
        static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(out.z, out.z, ppc::fmadds(out.x, out.x, out.y * out.y)))));
    if (length == 0.0f) return out;  // TOC +0x2684
    const float inverse = 1.0f / length;  // TOC +0x2688
    out.z = inverse * out.z;
    out.x = inverse * out.x;
    out.y = inverse * out.y;
    return out;
}

namespace {
// The hero's ability filters: +0x1ccc[5] the element's screen filter while a level 3 ability runs, +0x1ce0[5] the one
// played when it ends (CKFilterFxData).
IKFxData* AbilityFilter(IKSerializable* const* filters, uint32_t element) {
    return reinterpret_cast<IKFxData*>(filters[element]);
}
}  // namespace

// The body CancelAbilityA and CancelAbilityB share (the two differ only in the flag they clear): the running ability
// (+0x1cc0) stopped (vt+0x5c with `forced`); a running filter (+0x1cf4) let go (vt+0x58) and the element's end filter
// (+0x1ce0[element]) started in its place (the inlined effect search: CKSrvFx's StartEffect).
void CKHkS08Hero::CancelAbility(uint8_t forced) {
    CKAbilityElement* ability = static_cast<CKAbilityElement*>(m_unk1cc0);
    if (ability != nullptr) ability->Stop(forced);  // vt+0x5c
    IKSerializable* filter = m_unk1cf4;
    if (filter == nullptr) return;
    static_cast<IKFx*>(filter)->StopAndRelease(this);  // vt+0x58
    m_unk1cf4 = nullptr;
    IKSerializable* const* endFilters = &m_unk1ce0;  // +0x1ce0[5]
    static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->StartEffect(AbilityFilter(endFilters, m_unk1cc4), this);  // TOC +0x261c
}

// 0x00326ee0 CKHkS08Hero_CancelAbilityA: the first button's ability (+0x1ac5 cleared) cancelled.
void CKHkS08Hero::CancelAbilityA(uint8_t forced) {
    m_unk1ac5 = 0;
    CancelAbility(forced);
}

// 0x003272d8 CKHkS08Hero_CancelAbilityB: the second button's ability (+0x1ac6 cleared) cancelled.
void CKHkS08Hero::CancelAbilityB(uint8_t forced) {
    m_unk1ac6 = 0;
    CancelAbility(forced);
}

// 0x003276d0 CKHkS08Hero_ActState4_AbilityHandler. Enter: the host built once (+0x1df8), +0xed0 bit 1, the fury timer
// +0x1d24 at 0.3; the second button (+0xf58 in state 1 / 3) with its element's ability ready (cooldown not above 0) takes
// it (+0x1ac6), else the first button (+0xf44) (+0x1ac5); the ability (+0x1cc0) starts with the host. Tick: for the
// player's dragon the fury timer: at 0 the combo's hits (game manager +0xc34) go to the fury (unless the group's +0x2c8 bit
// 8) and it restarts; the running ability's step (vt+0x60): over, the flag and +0x1a84 cleared and the element's end
// filter played in place of its running filter; still running at element level 3, the quake every +0x1d00 seconds and
// the element's filter taken. An earth boulder (0x95cc) or a poison spin (0xa2cc) on a ground of +0xec4 bit 18, or with
// the game manager's dragon byte +0xe10 set, is cancelled (Stop(1)). Leave: +0x1a84 cleared (unless 4 or 9), the state
// bits, the targets unless +0x1ac4, a running ability stopped (Stop(0)) with its filter swapped for the end one, the move
// speed +0x1d14 back to 1, +0x1d10 and +0x1cc0 cleared, +0x364 bit 24 cleared. The inlined effect searches are
// CKSrvFx's StartEffect; the two direct calls of 0x9bdc18 (Ghidra CKSrvFx_AcquireFx: the unique effects, else
// a pooled one without the reservation bit) are StartEffect too.
uint8_t CKHkS08Hero::ActAbility(IKTime* clock, int32_t phase, uint8_t other) {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKSerializable* const* filters = &m_unk1ccc;      // +0x1ccc[5]
    IKSerializable* const* endFilters = &m_unk1ce0;   // +0x1ce0[5]
    // The running filter (+0x1cf4) let go (vt+0x58) for the element's end filter.
    auto swapFilter = [&](bool acquire) {
        IKSerializable* filter = m_unk1cf4;
        if (filter == nullptr) return;
        static_cast<IKFx*>(filter)->StopAndRelease(this);  // vt+0x58
        m_unk1cf4 = nullptr;
        if (acquire) {
            fx->StartEffect(reinterpret_cast<IKFxData*>(endFilters[m_unk1cc4]), this);  // 0x009bdc18 (no reservation)
        } else {
            fx->StartEffect(AbilityFilter(endFilters, m_unk1cc4), this);  // inlined
        }
    };
    auto ability = [this]() { return static_cast<CKAbilityElement*>(m_unk1cc0); };
    if (phase == 1) {
        if (m_unk1df8 == nullptr) m_unk1df8 = new CKS08HeroAbilityHost(this);  // 0x003f0ec8
        m_unked0 = (m_unked0 & ~2u) | 2u;
        m_unk1d24 = 0.3f;  // TOC +0x267c
        m_unk1cc0 = nullptr;
        const uint8_t hero = m_ui8Hero;
        const uint32_t element = m_unk1cc4;
        bool started = false;
        if (m_unkf58 == 3u || m_unkf58 == 1u) {
            const int8_t slot = kAbilitySlotSecond[hero][element];  // TOC +0x2620
            if (!(0.0f < m_afAbilityCooldown[slot])) {              // TOC +0x2624
                m_unk1cc0 = m_apUnk1bd0[slot];
                if (m_unk1cc0 == nullptr) goto entered;
                m_unk1ac6 = 1;
                started = true;
            }
        }
        if (!started) {
            if (m_unkf44 != 3u && m_unkf44 != 1u) goto entered;
            const int8_t slot = kAbilitySlotFirst[hero][element];  // TOC +0x2618
            if (0.0f < m_afAbilityCooldown[slot]) goto entered;
            m_unk1cc0 = m_apUnk1bd0[slot];
            if (m_unk1cc0 == nullptr) goto entered;
            m_unk1ac5 = 1;
        }
        ability()->Start(m_unk1df8);  // vt+0x58
    entered:
        m_unk1a84 = 0;
        m_unk1cfc = 0.0f;
        return other;
    }
    if (phase != 0) {
        if (m_unk1a84 != 4 && m_unk1a84 != 9) m_unk1a84 = 0;
        m_unked0 &= 0xfffffffdu;
        m_unk354 &= 0xfffff7ffu;
        m_unkec4 &= 0xffdfc1ffu;
        m_unkec8 &= 0xffffff7fu;
        if (m_unk1ac4 == 0) {
            m_unk12c = nullptr;
            m_unk124 = nullptr;
        }
        if (m_unk1ac5 != 0) {
            m_unk1ac5 = 0;
            if (ability() != nullptr) ability()->Stop(0);  // vt+0x5c
            swapFilter(true);
        }
        if (m_unk1ac6 != 0) {
            m_unk1ac6 = 0;
            if (ability() != nullptr) ability()->Stop(0);
            swapFilter(false);
        }
        m_unk1d14 = 1.0f;  // TOC +0x2628
        m_unk1d10 = 0;
        m_unk1cc0 = nullptr;
        m_unk364 &= 0xfeffffffu;
        return other;
    }

    // The tick.
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const float dt = clock->m_afDeltaTime[0];
    const uint32_t level = manager->GetElementLevel(m_ui8Hero, static_cast<uint8_t>(m_unk1cc4));  // 0x004f9558 (twice)
    const uint8_t leader = m_ui8TrackedLeader;
    if (leader == m_ui8Hero) {
        const float left = m_unk1d24;
        if (left < 0.0f) {
            const uint32_t hits = leader == 0 ? manager->m_unkC34 : manager->m_unkC38;  // +0xc34 + 4 x dragon
            if (hits != 0 && (static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_unk2c8 & 0x100u) == 0) {
                manager->AddDragonFuryFromAttack(leader, hits);  // 0x004fe1a0
            }
            m_unk1d24 = 0.3f;
        } else {
            m_unk1d24 = left - dt;
        }
    }
    auto runningStep = [&](uint8_t& flag) {
        if (ability()->Update(dt) == 0) {  // vt+0x60
            flag = 0;
            m_unk1a84 = 0;
            swapFilter(false);
            return;
        }
        if (level != 3) return;
        const float left = m_unk1cfc - dt;
        m_unk1cfc = left;
        if (left <= 0.0f) {
            CKQuakeCameraLauncher* quake = static_cast<CKQuakeCameraLauncher*>(m_unk1cf8);
            quake->m_unk24 = 1;
            quake->Trigger();  // 0x001533c0
            m_unk1cfc = m_unk1d00;
        }
        if (m_unk1cf4 != nullptr) return;
        m_unk1cf4 = fx->AcquireFx(AbilityFilter(filters, m_unk1cc4), this);  // inlined
    };
    if (m_unk1ac5 != 0) {
        runningStep(m_unk1ac5);
    } else if (m_unk1ac6 != 0) {
        runningStep(m_unk1ac6);
    }
    // BUG(original): the kind tests read +0x1cc0 without a null test (an empty ability slot would fault); DOTD returns.
    if (ability() == nullptr) return other;
    const uint8_t* record = reinterpret_cast<const uint8_t*>(&manager->m_unkDF4[1]) + static_cast<uint32_t>(m_ui8Hero) * 0x20u;
    const bool cancel = (m_unkec4 & 0x40000u) != 0 || record[0x18] != 0;  // +0xe10 + 0x20 x dragon
    if (ability()->IsKindOfClass(0x95cc) != 0 && cancel) {  // CKEarthBoulder
        m_unk1ac6 = 0;
        ability()->Stop(1);
        swapFilter(false);
    } else if (ability()->IsKindOfClass(0xa2cc) != 0 && cancel) {  // CKPoisonSpin
        m_unk1ac5 = 0;
        ability()->Stop(1);
        swapFilter(true);
    }
    return other;
}

// ---- C2.8 meca-hero: the moves and animations an object drives ----

// 0x0032ac88 CKHkS08Hero_CrossfadeAnimResource_maybe (vt+0xc4)
uint32_t CKHkS08Hero::CrossfadeAnimResource(float blend, float start, uint32_t word, uint32_t mode) {
    if ((m_unk358 & 2u) == 0) return 0;
    m_animBlendSlot10f0.StartCrossfade(blend, 1);  // 0x0007a848 (f1 still `blend`)
    m_unk360 = (m_unk360 & 0xfffff7ffu) | 0x800u;
    return GetAnimBlendSlot()->CrossfadeToAnim(blend, start, word, mode);  // vt+0x194, 0x00079ea0
}

// 0x0032a548 CKHkS08Hero_SetMoveDestination (vt+0xcc)
void CKHkS08Hero::SetMoveDestination(float timeout, const CVector3* position, const CVector3* direction,
                                     uint32_t /*unused*/, uint32_t flag4, uint32_t flag31) {
    m_unk354 &= 0x7fffffffu;
    SetMoveDestinationBase(timeout, position, direction, flag4, flag31);  // 0x00364470
}

// 0x0032b500 CKHkS08Hero_UpdateMoveTo_maybe (vt+0xd0)
uint8_t CKHkS08Hero::UpdateMoveTo(IKTime* clock, uint8_t* out) {
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    uint8_t flies = 0;
    if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) {
        flies = 1;
        SetMovementMode(1);  // 0x00340c18
        m_unk13d3 = 1;
        m_unk13a4 = 0;
    }
    SetPathCharacterType(IsFlyingMovementMode1() != 0 ? 4u : 2u);  // 0x0033cac0 / 0x0033cb08
    m_unk358 &= 0xffefffffu;
    m_unk360 = (m_unk360 & 0xffffffbfu) | 0x40u;
    if (IsFlyingMovementMode1() != 0 && flies == 0) {
        const float dx = m_unk398 - m_unk54c;
        const float dz = m_unk3a0 - m_unk554;
        const float distance = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(dx, dx, dz * dz))));  // 0x00010690
        if (!(distance >= 2.0f)) SetMovementModeUnlessLocked(0);  // TOC +0x26b8; bge: a NaN keeps the mode
    }
    if (IsClimbingMovementMode2() != 0) SetMovementModeUnlessLocked(0);  // 0x003401a0, 0x00342ef8
    const uint8_t arrived = UpdateMoveToBase(clock, out);  // 0x00363900
    // The steering's move vector +0x3b8 against the zero vector 0x00c50d64 (TOC +0x26bc).
    const bool still = m_unk3b8 == 0.0f && m_unk3bc == 0.0f && m_unk3c0 == 0.0f;
    float ratio = 0.0f;  // TOC +0x2684
    uint8_t stick;
    bool handleStill = still;
    if (!still) {
        ratio = m_unk3dc / m_unkaf4;
        if (ratio > 1.0f) {
            stick = 0xff;
        } else if (ratio == 0.0f) {
            handleStill = true;
        } else {
            stick = static_cast<uint8_t>(ppc::fctiwz(ratio * 255.0f));  // TOC +0x26c0
        }
    }
    if (handleStill) {
        if ((m_unk3b0 & 0x80u) != 0) {
            if (arrived != 0) {
                m_unkec8 &= 0xffffff7fu;
                return 1;
            }
            // Arrived without a move: the player-input copy cleared, the direction kept as the facing to compare with.
            m_unk394 = arrived;
            m_unk1378 = 0.0f;
            m_unk37c = 0.0f;
            m_unk380 = 0.0f;
            m_unk384 = 0.0f;
            m_unkec8 = (m_unkec8 & 0xffffff7fu) | 0x80u;
            m_unk11cc = m_unk3a4;
            m_unk11d0 = m_unk3a8;
            m_unk11d4 = m_unk3ac;
            m_unk127c = 0.0f;
            m_unk1268 = 0.0f;
            m_unk126c = 0.0f;
            m_unk1270 = 0.0f;
            m_unk1284 = 0.0f;
            CVector3 direction = {m_unk3a4, m_unk3a8, m_unk3ac};
            CVector3 facing = {m_unk540, m_unk544, m_unk548};
            Vec3_AngleBetween(&direction, &facing);  // 0x002fbbf8: the angle is not used
            m_unkec8 &= 0xffffff7fu;
            return 1;
        }
        stick = static_cast<uint8_t>(ppc::fctiwz(ratio * 255.0f));
    }
    m_unk394 = stick;
    m_unk37c = m_unk3b8;
    m_unk380 = m_unk3bc;
    m_unk384 = m_unk3c0;
    m_unkec8 &= 0xffffff7fu;
    const float dx = m_unk54c - m_unk398;
    const float dz = m_unk554 - m_unk3a0;
    const float distance = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(dx, dx, dz * dz))));
    if (!(distance < 1.0f)) return arrived;  // TOC +0x2688
    // Within 1 unit: arrived, as above without the facing comparison.
    m_unk1378 = 0.0f;
    m_unk394 = 0;
    m_unk37c = 0.0f;
    m_unk380 = 0.0f;
    m_unk384 = 0.0f;
    m_unkec8 = (m_unkec8 & 0xffffff7fu) | 0x80u;
    m_unk11cc = m_unk3a4;
    m_unk127c = 0.0f;
    m_unk11d4 = m_unk3ac;
    m_unk11d0 = m_unk3a8;
    m_unk1284 = 0.0f;
    m_unk1268 = 0.0f;
    m_unk126c = 0.0f;
    m_unk1270 = 0.0f;
    m_unkec8 &= 0xffffff7fu;
    return 1;
}

// 0x0032a458 StaticInitAndDestruction_32a458: two file statics (0x00ceae4c, 0x00ceae50) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae4c = -1.0f;
[[maybe_unused]] float s_unkceae50 = -1.0f;
}  // namespace
