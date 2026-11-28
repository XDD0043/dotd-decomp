// Reconstructed original translation unit: 0x33ca98-0x33fa28 (GAME_TOC1, main_toc1), 34 functions, 31 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x33ca98  CKHkS08Hero_vfFC
//   [x] 0x33caa0  CKHkS08Hero_CtlState0_AIWarpToCatchUpPoint_Condition
//   [x] 0x33cab0  CKHkS08Hero_CtlState1_AIPickCatchUpPoint_Condition
//   [x] 0x33cac0  CKHkS08Hero_CopyPointRecordWithType4_maybe
//   [x] 0x33cb08  CKHkS08Hero_CopyPointRecordWithType2_maybe
//   [x] 0x33cb50  CKHkS08Hero_AIWriteStickFromDesiredMove_maybe
//   [x] 0x33cc28  StaticInitAndDestruction_33cc28  (the two file statics at the end)
//   [ ] 0x33cc58  _GLOBAL__I_33cc58
//   [ ] 0x33cc68  _GLOBAL__D_33cc68
//   [x] 0x33cc78  CKHkS08Hero_AIGetFollowFlyingTarget_maybe
//   [ ] 0x33ce70  FUN_0033ce70  [dead]
//   [x] 0x33d000  CKHkS08Hero_CtlState3_AICombat
//   [ ] 0x33d178  FUN_0033d178  [dead]
//   [x] 0x33d250  CKHkS08Hero_CtlState3_AICombat_Condition
//   [x] 0x33d330  CKHkS08Hero_CtlState5_AIClimbing_maybe_Condition
//   [x] 0x33d428  CKHkS08Hero_CtlState7_AIFollowGround_Condition
//   [x] 0x33d570  CKHkS08Hero_CtlState6_AIFollowFlying_Condition
//   [ ] 0x33d708  FUN_0033d708  [dead]
//   [x] 0x33d7d8  CKHkS08Hero_IsPointWalkableInCurrentSector_maybe
//   [x] 0x33d8f0  CKHkS08Hero_UpdateField1348Timers_maybe
//   [x] 0x33da70  CKHkS08Hero_CtlState4_ControlLocked
//   [x] 0x33db90  CKHkS08Hero_AIComputeFollowFlyingThrottle_maybe
//   [x] 0x33de60  CKHkS08Hero_AISteerFollowFlying_maybe
//   [x] 0x33e108  CKHkS08Hero_CtlState1_AIPickCatchUpPoint
//   [x] 0x33e378  CKHkS08Hero_CtlState2_ScriptedMoveTo
//   [x] 0x33e600  CKHkS08Hero_CtlState7_AIFollowGround
//   [x] 0x33ecf0  CKHkS08Hero_AIGetFollowFlyingDirection_maybe
//   [x] 0x33f080  CKHkS08Hero_CtlState5_AIClimbing_maybe
//   [x] 0x33f150  CKHkS08Hero_CtlState0_AIWarpToCatchUpPoint
//   [x] 0x33f4d0  CKHkS08Hero_CtlState6_AIFollowFlying
//   [x] 0x33f9c0  KStub_Nop_33f9c0  (skipped by its caller: CKHkS08Hero_16.cpp CtlAICombat)
//   [x] 0x33f9c8  KStub_Return1_33f9c8  (inline in its caller: CKHkS08Hero_16.cpp CtlAICombat)
//   [x] 0x33f9d0  CKHkS08Hero_ResetComboAndAttackCredits
//   [x] 0x33f9e8  CKHkS08Hero_ConsumeAttackCredits
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "Renderware/rwcore/RwCamera.h"
#include <cmath>
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/math/Vec3.h"
#include "k2000/system/IKTime.h"

// 0x0033f9d0 CKHkS08Hero_ResetComboAndAttackCredits
void CKHkS08Hero::ResetComboAndAttackCredits() {
    m_unk1a20 = 0;
    m_unk1a1c = 0;
    m_unk1a18 = 0;
}

// 0x0033ca98 CKHkS08Hero_vfFC (vt+0xfc): empty.
void CKHkS08Hero::VfFC(IKTime*) {}

// 0x0033caa0 CKHkS08Hero_CtlState0_AIWarpToCatchUpPoint_Condition: +0xed0 bit 3.
uint8_t CKHkS08Hero::CtlAIWarpToCatchUpPointCondition(IKTime*, uint8_t) {
    return static_cast<uint8_t>((m_ui32StatusFlagsED0 >> 3) & 1u);
}

// 0x0033cab0 CKHkS08Hero_CtlState1_AIPickCatchUpPoint_Condition: +0xed0 bit 2.
uint8_t CKHkS08Hero::CtlAIPickCatchUpPointCondition(IKTime*, uint8_t) {
    return static_cast<uint8_t>((m_ui32StatusFlagsED0 >> 2) & 1u);
}

// 0x0033d250 CKHkS08Hero_CtlState3_AICombat_Condition: the AI partner on foot, not on a ground with property 0x200
// and with its leader not flying, fights when the group says so (+0xf8 bit 10).
uint8_t CKHkS08Hero::CtlAICombatCondition(IKTime*, uint8_t) {
    const CGround* ground = static_cast<const CGround*>(GetGroundInfo());  // 0x00361b68
    uint32_t groundFlag = 0;
    if (ground != nullptr) groundFlag = (ground->m_ui16PropertiesFlags >> 9) & 1u;
    if (m_ui8Hero == m_ui8TrackedLeader) return 0;
    if (static_cast<int8_t>(GetMovementMode()) != 0) return 0;
    if (groundFlag != 0) return 0;
    if (GetPartnerHero()->IsFlyingMovementMode1() != 0) return 0;  // 0x002f85f8, 0x00340188
    return static_cast<uint8_t>((static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_baWorkFlags >> 10) & 1u);
}

// 0x0033d330 CKHkS08Hero_CtlState5_AIClimbing_maybe_Condition: the AI partner climbs with its leader (or stays on a
// climb it is on); a partner on the ground below a climbing leader that holds +0x1676 with +0xec8 bit 30 clears
// +0x167d and sets +0x1677 instead.
uint8_t CKHkS08Hero::CtlAIClimbingCondition(IKTime*, uint8_t) {
    if (m_ui8Hero == m_ui8TrackedLeader) return 0;
    const uint8_t leaderMode = GetControllingHero()->GetMovementMode();
    const uint8_t mode = GetMovementMode();
    if (leaderMode == 1 || leaderMode < 1) return mode == 2 ? 1 : 0;
    if (leaderMode != 2) return 0;
    if (mode != 0) return mode == 2 ? 1 : 0;
    if (m_unk1676 == 0) return 0;
    if ((m_unkec8 & 0x40000000u) == 0) return 0;
    m_unk167d = mode;  // 0
    m_unk1677 = 1;
    return 0;
}

// 0x0033f080 CKHkS08Hero_CtlState5_AIClimbing_maybe: the AI partner climbing with its leader: entering clears +0x358 bit 20
// (the jump press), puts it in the climbing mode and sets +0x354 bit 31; leaving clears that bit. The climb itself is
// the locomotion's.
uint8_t CKHkS08Hero::CtlAIClimbing(IKTime*, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_ui32HeroFlags358 &= 0xffefffffu;
        SetMovementMode(2);  // 0x00340c18
        m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0x7fffffffu) | 0x80000000u;
        return other;
    }
    if (phase != 2) return other;
    m_ui32HeroFlags354 &= 0x7fffffffu;
    return other;
}

// 0x0033d570 CKHkS08Hero_CtlState6_AIFollowFlying_Condition: the AI partner flies after a flying leader (taking off
// itself unless +0xec8 bit 10 holds it), or stays in the air (+0xec4 bit 18) behind a walking one.
uint8_t CKHkS08Hero::CtlAIFollowFlyingCondition(IKTime*, uint8_t) {
    if (m_ui8Hero == m_ui8TrackedLeader) return 0;
    const uint8_t leaderMode = GetControllingHero()->GetMovementMode();
    const uint8_t mode = GetMovementMode();
    if (leaderMode == 1) {
        if (mode == 1) return 1;
        if (mode >= 1) return mode == 2 ? static_cast<uint8_t>(GetByte1679() ^ 1u) : 0;  // 0x002f85f0
        if ((m_unkec8 & 0x400u) == 0) SetMovementMode(1);  // 0x00340c18
        return IsFlyingMovementMode1();
    }
    if (leaderMode >= 1) {
        if (leaderMode != 2) return 0;
        return mode <= 1 ? 1 : 0;
    }
    if (mode == 0) return static_cast<uint8_t>((m_unkec4 >> 18) & 1u);
    if (mode != 1) return 0;
    GetGroundInfo();  // 0x00361b68 (the result is not used)
    return static_cast<uint8_t>((m_unkec4 >> 18) & 1u);
}

// 0x0033d428 CKHkS08Hero_CtlState7_AIFollowGround_Condition: the AI partner walks after a walking leader unless it
// is held in the air (+0xec4 bit 18), climbs down from a climb it may leave, or stands below a climbing leader that
// does not keep climbing.
uint8_t CKHkS08Hero::CtlAIFollowGroundCondition(IKTime*, uint8_t) {
    if (m_ui8Hero == m_ui8TrackedLeader) return 0;
    const uint8_t leaderMode = GetControllingHero()->GetMovementMode();
    const uint8_t mode = GetMovementMode();
    if (leaderMode == 0) {
        if (mode == 1 || mode < 1) return static_cast<uint8_t>(((m_unkec4 >> 18) & 1u) ^ 1u);
        if (mode != 2) return 0;
        return static_cast<uint8_t>(ShouldStayClimbing() ^ 1u);  // 0x00342fa8
    }
    if (leaderMode != 2) return 0;
    if (mode != 0) return 0;
    if ((m_unkec4 & 0x40000u) != 0) return 0;
    return static_cast<uint8_t>(PartnerShouldStayClimbing() ^ 1u);  // 0x002f8628
}

// 0x0033e600 CKHkS08Hero_CtlState7_AIFollowGround: the AI partner on foot. Entering puts it in the ground mode.
// Each frame: the sprint / catch-up flags (+0x368 bit 12, +0x35c bit 17), the follow AI, then the move request
// +0x37c..+0x384 / +0x394 from the AI's vector (+0x3b8, scaled by +0x3dc / +0xaf4), cleared while an input-blocking
// cinematic plays.
uint8_t CKHkS08Hero::CtlAIFollowGround(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase != 0) {
        if (phase == 1) {
            SetMovementMode(0);  // 0x00340c18
            m_ui32HeroFlags354 &= 0x7fffffffu;
        }
        return other;
    }
    CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
    const CVector3& zero = kHeroZeroVector;  // TOC +0x28e0 -> 0x00c50d64
    if (IsPartnerClimbFlagSet() != 0) {      // 0x002f87e8
        // A leader climbing a wall (+0x1744 0) is followed to the point one up-axis out from it, kept on the navigation;
        // within 1 (flat) of it, or on a ceiling / frame, the AI stands.
        if (partner->m_unk1744 == 0) {
            const RwFrame* frame = static_cast<const CSGMovable*>(partner->m_pKGLObject)->m_pRwFrame;
            CPFPoint point;
            point.m_position = {partner->m_unk54c + frame->modelling.up.x, partner->m_unk550 + frame->modelling.up.y,
                                partner->m_unk554 + frame->modelling.up.z};
            point.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;  // +0x43c
            CGroundContactDatasInOut contact;  // ground 0, face -1, status 3, sector 0
            if (ValidateNavPosition(&contact, &point, &m_PFCharacter, 0, nullptr) != 0) {  // 0x0036a2f8
                const float dx = m_unk54c - point.m_position.x;
                const float dz = m_unk554 - point.m_position.z;
                const float flat = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, 0.0f)));  // TOC +0x2900
                if (flat > 1.0f) {  // TOC +0x28e4
                    AIMoveToTarget(clock, &point.m_position, reinterpret_cast<const CVector3*>(&m_unk135c), 0, 0, 1);  // 0x0036dd08
                    if (!(m_unk3b8 == zero.x && m_unk3bc == zero.y && m_unk3c0 == zero.z)) {
                        const float ratio = m_unk3dc / m_unkaf4;
                        uint8_t level = 0xff;
                        bool stand = false;
                        if (!(ratio > 1.0f)) {  // ble 0x0033ec90: a NaN ratio takes the fctiwz (0x80000000, byte 0)
                            if (ratio == 0.0f) {
                                stand = true;
                            } else {
                                level = static_cast<uint8_t>(ppc::fctiwz(ratio * 255.0f));  // TOC +0x28e8; the low byte
                            }
                        }
                        if (!stand) {
                            m_unk394 = level;
                            m_unk37c = m_unk3b8;
                            m_unk384 = m_unk3c0;
                            m_unk380 = m_unk3bc;
                            return other;
                        }
                    }
                    m_unk37c = zero.x;
                    m_unk384 = zero.z;
                    m_unk380 = zero.y;
                    m_unk394 = 0;
                    return other;
                }
            }
        }
        m_unk394 = 0;
        m_unk37c = zero.x;
        m_unk384 = zero.z;
        m_unk380 = zero.y;
        return other;
    }
    m_unk368 = (m_unk368 & 0xffffefffu) | 0x1000u;
    bool sprint = false;
    if (partner->m_unk118d == 0 && (partner->m_unkec4 & 0x400000u) != 0) {
        const bool partnerStill = m_unk1258 >= 0.1f && partner->m_unk1258 == 0.0f;  // bge; TOC +0x291c, +0x2900
        if (!partnerStill && (m_unkec8 & 0x400u) == 0 && (m_unkec8 & 0x2000u) == 0 && (m_unkec8 & 0x40000u) == 0) {
            m_unk368 &= 0xffffefffu;
            sprint = true;
        }
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if ((group->m_ui32PairStateFlags & 0x1000u) != 0) {
        m_unk368 = (m_unk368 & 0xffffefffu) | 0x1000u;
        sprint = false;
    }
    const float dx = m_unk54c - partner->m_unk54c;
    const float dy = m_unk550 - partner->m_unk550;
    const float dz = m_unk554 - partner->m_unk554;
    const float distance = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));  // 0x00010690
    if ((group->m_ui32PairStateFlags & 0x80u) != 0 && sprint && distance > 30.0f) {  // TOC +0x2930
        m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xfffdffffu) | 0x20000u;
    } else {
        m_ui32HeroFlags35C &= 0xfffdffffu;
    }
    if ((m_unkec8 & 0x400u) == 0) m_ui32HeroFlags354 &= 0x7fffffffu;
    m_ui32HeroFlags358 &= 0xffefffffu;
    HandleAIFollowGroundPhase(clock, 0, 3);  // 0x00368248
    bool clear = m_unk3b8 == zero.x && m_unk3bc == zero.y && m_unk3c0 == zero.z;
    if (!clear) {
        const float ratio = m_unk3dc / m_unkaf4;
        uint8_t level = 0xff;
        if (!(ratio > 1.0f)) {  // TOC +0x28e4; ble 0x0033e894: a NaN ratio (the leader's 0 / 0 speed of a frozen frame)
            // takes the fctiwz (0x80000000): no move (byte 0), not the full stick
            if (ratio == 0.0f) {
                clear = true;
            } else {
                level = static_cast<uint8_t>(ppc::fctiwz(ratio * 255.0f));  // TOC +0x28e8; the low byte
            }
        }
        if (!clear) {
            m_unk394 = level;
            if ((m_unkec8 & 0x400u) == 0) {
                m_unk37c = m_unk3b8;
                m_unk380 = m_unk3bc;
                m_unk384 = m_unk3c0;
            } else {
                m_unk37c = m_unk11dc;
                m_unk380 = m_unk11e0;
                m_unk384 = m_unk11e4;
            }
        }
    }
    if (clear) {
        m_unk394 = 0;
        m_unk37c = zero.x;
        m_unk380 = zero.y;
        m_unk384 = zero.z;
    }
    uint32_t sceneCount = 0;
    IKSerializable** scenes = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic)->GetScenes(&sceneCount);  // 0x001665e8
    for (uint32_t i = 0; i < sceneCount; ++i) {
        if ((static_cast<CKCinematicScene*>(scenes[i])->m_baData & 1u) == 0) continue;
        if (static_cast<CDefaultGameManager*>(g_pEngine->m_gameManager)->IsInputBlocked() != 0) {  // vt+0x1ec
            m_unk394 = 0;
            m_unk37c = zero.x;
            m_unk380 = zero.y;
            m_unk384 = zero.z;
        }
        break;
    }
    return other;
}

// 0x0033d8f0 CKHkS08Hero_UpdateField1348Timers_maybe: the AI partner's "lost" timers: 5 s without a ground contact
// (+0x1348) or flying in a tether (+0x1350, 3 s) ask for the catch-up warp (+0x35c bit 17) when they run out. The
// player's hero keeps them at 0.
void CKHkS08Hero::UpdateField1348Timers() {
    if (m_ui8Hero == m_ui8TrackedLeader) {
        m_unk1350 = 0.0f;  // TOC +0x2900
        m_unk1348 = 0.0f;
        m_unk134c = 0;
        m_unk1354 = 0;
        return;
    }
    if (m_unk134c != 0 || m_unk1354 != 0) {
        m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xfffdffffu) | 0x20000u;
        m_unk1348 = 0.0f;
        m_unk134c = 0;
        m_unk1350 = 0.0f;
        m_unk1354 = 0;
        return;
    }
    if (m_gcOldDatasInOut.m_eContactStatus == 3) {  // +0x4f8
        if (!(m_unk1348 > 0.0f)) {
            m_unk134c = 0;
            m_unk1348 = 5.0f;  // TOC +0x2910
        }
    } else {
        m_unk134c = 0;
        m_unk1348 = 0.0f;
    }
    if ((m_ui32HeroFlags354 & 0x40000u) == 0 || IsFlyingMovementMode1() == 0) {  // 0x00340188
        m_unk1350 = 0.0f;
        m_unk1354 = 0;
        return;
    }
    if (!(m_unk1350 > 0.0f)) {
        m_unk1350 = 5.0f;  // TOC +0x2910
        m_unk1354 = 0;
    }
}

// ---- step 6 AI: the partner following a flying leader. ----

namespace {

// 0x00c50d34 / 0x00c50d4c / 0x00c50d70 / 0x00c50d88 (StaticInitAndDestruction_11578): +x, +z, -x, -z.
constexpr CVector3 kAxisPosX{1.0f, 0.0f, 0.0f};
constexpr CVector3 kAxisPosZ{0.0f, 0.0f, 1.0f};
constexpr CVector3 kAxisNegX{-1.0f, 0.0f, 0.0f};
constexpr CVector3 kAxisNegZ{0.0f, 0.0f, -1.0f};

// The position the AI uses on a climb zone: the modelling position of its scene node's frame (zone +0x1c
// m_pKGLObject, +4 its RwFrame, +0x40 modelling.pos).
// +0x1694 is the zone (CKHkClimbZone*), +0x16a0 the zone's +0x4c (a hook: its scene node is read the same way).
RwV3d* ClimbZoneAnchor(IKSerializable* zoneObject) {
    IKHook* hook = static_cast<IKHook*>(zoneObject);
    return &static_cast<CSGMovable*>(hook->m_pKGLObject)->m_pRwFrame->modelling.pos;
}

}  // namespace

// 0x0033f4d0 CKHkS08Hero_CtlState6_AIFollowFlying (control state 9): the AI partner flies after a flying leader.
// Entering puts it in the flying mode, +0x354 bit 31 and the path-finding character mode 4 (+0x3e0 bits 0-2, copied
// to the component's +0x3f8); leaving clears +0x13d3, bit 31 and sets mode 2. Each frame: the follow destination, then
// the target and direction (the leader itself, flat, when the group's +0x378 byte is 0 or the partner keeps
// climbing; else the follow target and direction), the move request from the normalised direction, the throttle and
// the steering with the stop distance 8; the "fly higher" request +0x13d3 / +0x358 bit 20 when the leader is above
// (or faster at +0x12d0) and flying (+0x13d1), or from the group's +0x2c8 bit 5 in a tether; a catch-up point request
// (+0xed0 bit 2) when the leader walks and the partner carries no more than 0.1.
uint8_t CKHkS08Hero::CtlAIFollowFlying(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_ui32HeroFlags358 &= 0xffefffffu;
        SetMovementMode(1);  // 0x00340c18
        m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0x7fffffffu) | 0x80000000u;
        m_PFCharacter.m_bits = (m_PFCharacter.m_bits & 0xfffffff8u) | 4u;  // +0x3e0
        m_PFCpnt.m_CharacterType = m_PFCharacter;                           // +0x3f8
        return other;
    }
    if (phase == 2) {
        m_unk13d3 = 0;
        m_ui32HeroFlags354 &= 0x7fffffffu;
        m_PFCharacter.m_bits = (m_PFCharacter.m_bits & 0xfffffff8u) | 2u;
        m_PFCpnt.m_CharacterType = m_PFCharacter;
        return other;
    }
    if (phase != 0) return other;
    AIUpdateFollowDestination(clock);  // 0x0036df50
    CKHkS08Hero* leader = GetControllingHero();  // 0x00344e68
    CVector3 target;
    CVector3 direction;
    const uint32_t followByte = (static_cast<CKGrpS08Hero*>(leader->m_pGrpHero)->m_unk378 >> 24) & 0xffu;  // +0x378
    if (followByte == 0 || PartnerShouldStayClimbing() != 0) {  // 0x002f8628
        target.x = leader->m_unk54c;
        target.z = leader->m_unk554;
        direction.x = leader->m_unk54c - m_unk54c;
        direction.z = leader->m_unk554 - m_unk554;
        target.y = leader->m_unk550;
        direction.y = 0.0f;  // stw 0
    } else {
        target = AIGetFollowFlyingTarget(clock);  // 0x0033cc78
        direction = AIGetFollowDirection();       // 0x0033ecf0
    }
    const float length = static_cast<float>(c22spyro::MathSqrtf(
        ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, direction.y * direction.y))));
    if (length != 0.0f) {  // TOC +0x2900
        const float inverse = 1.0f / length;  // TOC +0x28e4
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    }
    m_unk37c = direction.x;
    m_unk384 = direction.z;
    m_unk380 = direction.y;
    AIComputeFollowFlyingThrottle(8.0f, &target);       // TOC +0x294c
    AISteerFollowFlying(8.0f, &target, &direction);
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (PartnerShouldStayClimbing() == 0) {
        CKHkS08Hero* lead = GetControllingHero();
        bool higher = false;
        if ((m_unkec4 & 0x100000u) == 0) {
            higher = (lead->m_unk550 > m_unk550 + 1.0f || !(lead->m_unk12d0 <= m_unk12d0 + 0.0f)) &&  // bgt; ble
                     lead->m_unk13d1 != 0 && m_unk13d8 == 0;
        } else if ((group->m_ui32PairStateFlags & 0x20u) != 0) {
            higher = true;
            group->m_ui32PairStateFlags &= 0xffffffdfu;  // stored after the two below in the original
        }
        if (higher) {
            m_unk13d3 = 1;
            m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xffefffffu) | 0x100000u;
        } else {
            m_unk13d3 = 0;
            m_ui32HeroFlags358 &= 0xffefffffu;
        }
    }
    if (static_cast<int8_t>(leader->GetMovementMode()) == 0 && m_unk1258 <= 0.1f &&  // cror lt|eq; TOC +0x291c
        (group->m_ui32PairStateFlags & 0x1000u) == 0) {
        m_ui32StatusFlagsED0 = (m_ui32StatusFlagsED0 & 0xfffffffbu) | 4u;
    }
    return other;
}

// 0x0033cc78 CKHkS08Hero_AIGetFollowFlyingTarget_maybe.
CVector3 CKHkS08Hero::AIGetFollowFlyingTarget(IKTime* clock) {
    CVector3 result = kHeroZeroVector;  // TOC +0x28e0
    if ((m_unkec4 & 0x100000u) == 0) {
        result.x = m_unk3c4;
        result.y = m_unk3c8;
        result.z = m_unk3cc;
        return result;
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (GetPartnerHero()->m_unk16a0 == nullptr) {  // 0x002f85f8
        const CKGrpS08Hero::SFollowWaypoint waypoint = group->GetFollowWaypoint();  // 0x002d4fd8
        result.y = waypoint.m_vPosition.y;
        result.x = waypoint.m_vPosition.x;
        result.z = waypoint.m_vPosition.z;
        return result;
    }
    if (IsClimbingMovementMode2() == 0 || (group->m_ui32PairStateFlags & 8u) == 0) {  // 0x003401a0
        GetPartnerHero();  // the result is not used
        CKHkS08Hero* partner = GetPartnerHero();
        AIUpdatePathToTarget(clock, reinterpret_cast<CVector3*>(ClimbZoneAnchor(partner->m_unk16a0)),  // 0x0036d210
                             reinterpret_cast<CVector3*>(&m_unk3c4), reinterpret_cast<CVector3*>(&m_unk3d0));
        result.z = m_unk3cc;
        result.x = m_unk3c4;
        result.y = m_unk3c8;
        return result;
    }
    result.y = m_unk550;
    result.x = m_unk54c;
    result.z = m_unk554;
    result.y = group->GetFollowWaypoint().m_vPosition.y;
    return result;
}

// 0x0033ecf0 CKHkS08Hero_AIGetFollowFlyingDirection_maybe.
CVector3 CKHkS08Hero::AIGetFollowDirection() {
    CVector3 result = kHeroZeroVector;  // TOC +0x28e0
    m_ui32HeroFlags358 &= 0xffefffffu;
    if ((m_unkec4 & 0x100000u) == 0) {
        result.x = m_unk3b8;
        result.y = m_unk3bc;
        result.z = m_unk3c0;
        return result;
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    float tx;
    float tz;
    if (GetPartnerHero()->m_unk16a0 == nullptr) {
        if ((m_ui32HeroFlags354 & 1u) != 0 && (group->m_ui32PairStateFlags & 0x40u) != 0) return group->m_vFollowTargetOverride;  // +0xa94
        const CKGrpS08Hero::SFollowWaypoint waypoint = group->GetFollowWaypoint();
        tx = waypoint.m_vPosition.x;
        tz = waypoint.m_vPosition.z;
    } else {
        const IKSerializable* ownZone = m_pCurrentClimbZone;
        if (GetPartnerHero()->m_unk16a0 != ownZone && IsClimbingMovementMode2() != 0) {
            if (m_pCurrentClimbZone == nullptr) return result;
            const float own = ClimbZoneAnchor(m_pCurrentClimbZone)->x;
            const float gap = own - ClimbZoneAnchor(GetPartnerHero()->m_unk16a0)->x;
            result = gap <= 0.0f ? kAxisPosX : kAxisNegX;  // TOC +0x2938 / +0x2934
            if (m_unk1626 != 0) {
                m_ui32HeroFlags358 &= 0xffefffffu;
            } else {
                m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xffefffffu) | 0x100000u;
            }
            return result;
        }
        if (IsClimbingMovementMode2() != 0 && (group->m_ui32PairStateFlags & 8u) != 0) {
            const float dy = group->GetFollowWaypoint().m_vPosition.y - m_unk550;
            if (!(dy <= 0.0f)) return kAxisPosZ;  // TOC +0x293c
            if (dy >= 0.0f) return result;
            return kAxisNegZ;  // TOC +0x2940
        }
        if (IsClimbingMovementMode2() != 0) return kHeroZeroVector;
        tx = m_unk3c4;
        tz = m_unk3cc;
    }
    const float zero = 0.0f;  // TOC +0x2900
    const float dx = tx - m_unk54c;
    const float dz = tz - m_unk554;
    result.x = dx;
    result.y = zero;
    result.z = dz;
    const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zero))));
    if (length == zero) return result;
    const float inverse = 1.0f / length;  // TOC +0x28e4
    result.z = inverse * result.z;
    result.x = inverse * result.x;
    result.y = inverse * result.y;
    return result;
}

// 0x0033db90 CKHkS08Hero_AIComputeFollowFlyingThrottle_maybe. The distance to `target` (flat while the partner keeps
// climbing). The level stores before the last are overwritten in every path (the original's): only the trail call
// and the final store matter.
void CKHkS08Hero::AIComputeFollowFlyingThrottle(float stopDistance, const CVector3* target) {
    CKHkS08Hero* leader = GetControllingHero();
    const float tz = target->z;
    const float tx = target->x;
    const float x = m_unk54c;
    const float z = m_unk554;
    const float ty = target->y;
    const float y = m_unk550;
    float dy2 = 0.0f;  // TOC +0x2900
    if (PartnerShouldStayClimbing() == 0) {
        const float dy = ty - y;
        dy2 = dy * dy;
    }
    const float dx = tx - x;
    const float dz = tz - z;
    const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy2));
    const float distance = static_cast<float>(c22spyro::MathSqrtf(squared));
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const float range = AsF32(group->m_unka8c[0]);  // +0xa8c
    bool full = true;
    if (distance < range) {  // bge (unordered too) gives full
        const float level = (distance / range) * 255.0f;  // TOC +0x28e8
        if (level <= 255.0f) {
            full = false;
            m_unk394 = static_cast<uint8_t>(ppc::fctiwz(level));
            if (m_unk394 <= 0x31) m_unk394 = 0;
        }
    }
    if (full) m_unk394 = 0xff;
    if (!(distance >= stopDistance) && (m_unkec4 & 0x100000u) == 0) m_unk394 = 0;  // bge skips
    if (leader->m_unk394 > 200) m_unk394 = 0xff;
    bool callTrail = true;
    if ((group->m_ui32PairStateFlags & 8u) == 0 && (m_unkec4 & 0x100000u) != 0) m_unk394 = 0;
    if ((m_ui32HeroFlags354 & 1u) != 0) callTrail = false;
    if (callTrail) {
        if (group->GetFollowWaypoint().m_unk1c == 1) m_unk394 = 0xff;  // 0x002d4fd8
    } else {
        m_unk394 = 0xff;
    }
    m_unk394 = 0xff;
    if ((m_ui32HeroFlags354 & 4u) != 0) m_unk394 = 0;
    if (AsF32(group->m_unkaac) > 0.0f) {  // +0xaac
        const float again = static_cast<float>(c22spyro::MathSqrtf(squared));
        if (!(group->m_unk1e8 <= again)) {  // ble gives full
            m_unk394 = static_cast<uint8_t>(ppc::fctiwz(AsF32(group->m_unkaac) * 255.0f));
            return;
        }
    }
    m_unk394 = 0xff;
}

// 0x0033de60 CKHkS08Hero_AISteerFollowFlying_maybe.
void CKHkS08Hero::AISteerFollowFlying(float stopDistance, const CVector3* target, const CVector3* direction) {
    CKHkS08Hero* leader = GetControllingHero();
    float wz = direction->z;
    const float tz = target->z;
    float wx = direction->x;
    const float x = m_unk54c;
    float wy = direction->y;
    const float tx = target->x;
    const float ty = target->y;
    const float y = m_unk550;
    const float z = m_unk554;
    float dy2 = 0.0f;  // TOC +0x2900
    if (PartnerShouldStayClimbing() == 0) {
        const float dy = ty - y;
        dy2 = dy * dy;
    }
    const float dx = tx - x;
    const float dz = tz - z;
    const float distance = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy2))));
    const CVector3& zero = kHeroZeroVector;  // TOC +0x28e0
    if (m_unk394 <= 0x31) {
        wx = zero.x;
        wy = zero.y;
        wz = zero.z;
    }
    if (!(distance >= stopDistance) && (m_unkec4 & 0x100000u) == 0) {  // bge skips
        wx = zero.x;
        wy = zero.y;
        wz = zero.z;
    }
    const float lx = m_unk54c - leader->m_unk54c;
    const float ly = m_unk550 - leader->m_unk550;
    const float lz = m_unk554 - leader->m_unk554;
    const float toLeader = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(lz, lz, ppc::fmadds(lx, lx, ly * ly))));
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (!(group->m_unk1e8 <= toLeader) && (m_ui32HeroFlags354 & 1u) == 0) {  // ble skips
        wx = zero.x;
        wy = zero.y;
        wz = zero.z;
    }
    if ((group->m_ui32PairStateFlags & 8u) == 0 && (m_unkec4 & 0x100000u) != 0) {
        wx = zero.x;
        wy = zero.y;
        wz = zero.z;
    }
    if (IsClimbingMovementMode2() != 0) {  // 0x003401a0
        m_unk370 = wx;
        m_unk378 = wz;
        m_unk374 = wy;
    } else {
        m_unk37c = wx;
        m_unk380 = wy;
        m_unk384 = wz;
    }
    if (m_unk37c == zero.x && m_unk380 == zero.y && m_unk384 == zero.z) m_unk394 = 0;
}

// ---- step 4 AI: the catch-up states and the AI stick. ----

// 0x0033cb50 CKHkS08Hero_AIWriteStickFromDesiredMove_maybe (the AI combat movement's, C2.7): the move request
// (+0x37c..+0x384, +0x394) from the AI's move vector +0x3b8 and speed +0x3dc / +0xaf4 (full above 1, none at 0).
void CKHkS08Hero::AIWriteStickFromDesiredMove() {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x28e0 -> 0x00c50d64
    bool none = m_unk3b8 == zero.x && m_unk3bc == zero.y && m_unk3c0 == zero.z;
    uint8_t level = 0xff;
    if (!none) {
        const float ratio = m_unk3dc / m_unkaf4;
        if (!(ratio > 1.0f)) {  // TOC +0x28e4; ble 0x0033cb94 (a NaN ratio: byte 0)
            if (ratio == 0.0f) {
                none = true;
            } else {
                level = static_cast<uint8_t>(ppc::fctiwz(ratio * 255.0f));  // TOC +0x28e8; the low byte
            }
        }
    }
    if (none) {
        m_unk37c = zero.x;
        m_unk384 = zero.z;
        m_unk380 = zero.y;
        m_unk394 = 0;
        return;
    }
    m_unk394 = level;
    m_unk37c = m_unk3b8;
    m_unk384 = m_unk3c0;
    m_unk380 = m_unk3bc;
}

// 0x0033e108 CKHkS08Hero_CtlState1_AIPickCatchUpPoint: the AI partner asked to catch up (+0xed0 bit 2) takes the
// catch-up point the group found for it (FindCatchUpPoint with its leader; the group's +0x2c8 bit 7 and +0x378, the
// hero not carrying more than 0.1): the warp's end +0x1124, start +0x1130, duration +0x1140 (the distance / 10) and
// point index +0x1144, then asks for the warp (+0xed0 bit 3). Otherwise (or for the player) bit 2 clears. Entering
// clears the move request, +0x1124 and +0x358 bit 20 (+0x354 bit 31 when it stays climbing); leaving clears bit 2.
uint8_t CKHkS08Hero::CtlAIPickCatchUpPoint(IKTime*, int32_t phase, uint8_t other) {
    if (phase == 1) {
        const CVector3& zero = kHeroZeroVector;  // TOC +0x28e0
        m_unk1378 = 0.0f;  // stw 0
        m_unk37c = zero.x;
        m_unk384 = zero.z;
        m_unk380 = zero.y;
        m_unk394 = 0;
        m_unk1124 = zero.x;
        m_unk112c = zero.z;
        m_unk1128 = zero.y;
        m_ui32HeroFlags358 &= 0xffefffffu;
        if (ShouldStayClimbing() != 0) m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0x7fffffffu) | 0x80000000u;  // 0x00342fa8
        return other;
    }
    if (phase == 2) {
        m_ui32StatusFlagsED0 &= 0xfffffffbu;
        return other;
    }
    if (phase != 0) return other;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (m_ui8Hero == m_ui8TrackedLeader || (group->m_ui32PairStateFlags & 0x80u) == 0 || m_unk1258 > 0.1f) {  // TOC +0x291c
        m_ui32StatusFlagsED0 &= 0xfffffffbu;
        return other;
    }
    if (((group->m_unk378 >> 24) & 0xffu) == 0) return other;  // the byte at +0x378
    const CKGrpS08Hero::SCatchUpPoint* point = group->FindCatchUpPoint(GetPartnerHero());  // 0x002f85f8, 0x002caf58
    if (point == nullptr) return other;
    if (static_cast<uint8_t>(point->m_i8Index) == 0xff) return other;
    const float zero = 0.0f;  // TOC +0x2900
    m_unk1124 = point->m_vPosition.x;
    m_unk1130 = m_unk54c;
    const float dx = m_unk1124 - m_unk1130;
    m_unk112c = point->m_vPosition.z;
    m_unk1138 = m_unk554;
    const float dz = m_unk112c - m_unk1138;
    m_unk1128 = point->m_vPosition.y;
    m_unk1134 = m_unk550;
    const float distance = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zero))));  // 0x00010690
    m_unk1140 = distance;
    if (distance == zero) {
        m_ui32StatusFlagsED0 &= 0xfffffffbu;
        return other;
    }
    m_unk1140 = distance / 10.0f;  // TOC +0x2920
    m_ui32StatusFlagsED0 = (m_ui32StatusFlagsED0 & 0xfffffff7u) | 8u;
    m_unk1144 = static_cast<uint8_t>(point->m_i8Index);
    return other;
}

// 0x0033f150 CKHkS08Hero_CtlState0_AIWarpToCatchUpPoint: the AI partner flies (in the ground mode, +0x368 bit 12 held,
// no velocity) along a cubic curve from +0x1130 to +0x1124, 4 above the higher of the two, over +0x1140 seconds
// (+0x113c the time); it faces its way (+0x11cc). At the end +0xed0 bits 2 and 3 clear. Entering puts it on the
// ground mode, +0x354 bits 6 / 31, +0xec8 bit 7, and takes it off a climb zone; leaving clears them.
uint8_t CKHkS08Hero::CtlAIWarpToCatchUpPoint(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        SetMovementMode(0);  // 0x00340c18
        m_ui32HeroFlags354 = (((m_ui32HeroFlags354 & 0xffffffbfu) | 0x40u) & 0x7fffffffu) | 0x80000000u;
        m_unk113c = 0.0f;  // TOC +0x2900
        m_unkec8 = (m_unkec8 & 0xffffff7fu) | 0x80u;
        if (m_pCurrentClimbZone != nullptr) m_pCurrentClimbZone->RemoveClimber(CKHkClimbZone::ClimberKey(this));  // 0x00457180
        return other;
    }
    if (phase == 2) {
        m_ui32HeroFlags354 &= 0x7fffffbfu;
        m_unkec8 &= 0xffffff7fu;
        return other;
    }
    if (phase != 0) return other;
    m_unk368 = (m_unk368 & 0xffffefffu) | 0x1000u;
    SetMovementMode(0);  // 0x00340c18
    m_unkec8 = (m_unkec8 & 0xffffff7fu) | 0x80u;
    const CVector3& zero = kHeroZeroVector;  // TOC +0x28e0
    m_unk127c = zero.x;
    m_unk1284 = zero.z;
    m_unk1280 = zero.y;
    if (m_unk113c >= m_unk1140) {  // cror gt|eq
        m_ui32StatusFlagsED0 &= 0xfffffff3u;
        m_unk113c = m_unk1140;
    }
    const float t = Math_RemapClamped(0.0f, m_unk1140, m_unk113c, 0.0f, 1.0f);  // 0x00333618; TOC +0x2900, +0x28e4
    CVector3 start{m_unk1130, m_unk1134, m_unk1138};
    CVector3 end{m_unk1124, m_unk1128, m_unk112c};
    float top;
    if (!(m_unk1128 <= m_unk1134)) {  // ble
        top = m_unk1128;
    } else {
        top = m_unk1134;
    }
    start.y = top + 4.0f;  // TOC +0x2944
    end.y = top + 4.0f;
    Vec3_CubicBezier(t, reinterpret_cast<CVector3*>(&m_unk54c), reinterpret_cast<const CVector3*>(&m_unk1130), &start,
                     &end, reinterpret_cast<const CVector3*>(&m_unk1124));  // 0x00010fc0
    m_unk1148 = t;
    m_unk144c.y = 1000.0f;  // +0x1450; TOC +0x2948
    m_unk1511 = 1;
    const float zeroF = 0.0f;  // TOC +0x2900
    const float dx = m_unk1124 - m_unk54c;
    const float dz = m_unk112c - m_unk554;
    const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zeroF))));
    if (length != zeroF && length > zeroF) {
        const float inverse = 1.0f / length;  // TOC +0x28e4
        m_unk11cc = dx * inverse;
        m_unk11d4 = dz * inverse;
        m_unk11d0 = inverse * zeroF;
    }
    m_unk113c = m_unk113c + clock->m_afDeltaTime[0];
    return other;
}

// 0x0033d7d8 CKHkS08Hero_IsPointWalkableInCurrentSector_maybe: `position` with the hero's current graph node (the path
// component's position hint, +0x43c) inside that node's box (an unordered compare fails) and walkable there for the
// hero's character type (+0x3e0; NavSectors_IsPointWalkable_maybe 0x001e42d0).
uint8_t CKHkS08Hero::IsPointWalkableInCurrentSector(const CVector3* position) {
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint point;
    point.m_position = *position;
    point.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    const int32_t node = static_cast<int16_t>(point.m_i16GraphNodeIndex);
    if (node < 0 || static_cast<uint32_t>(node) >= pathFinding->m_Graph.m_ui32GraphNodesSize) return 0;
    const CBBox& box = static_cast<CKPFGraphNode*>(pathFinding->m_Graph.m_apGraphNodes[node])->m_Sector.m_box;
    const CVector3& p = point.m_position;
    if (!(box.m_inf.x <= p.x && box.m_sup.x >= p.x && box.m_inf.z <= p.z && box.m_sup.z >= p.z && box.m_inf.y <= p.y &&
          box.m_sup.y >= p.y)) {
        return 0;
    }
    return static_cast<uint8_t>(pathFinding->IsPointWalkable(&point, &m_PFCharacter));  // 0x001e42d0
}

// 0x0033da70 CKHkS08Hero_CtlState4_ControlLocked: the control locked by a script. Enter: +0xb0 = 5, 0. Run: +0x354 bit 31
// = the speed +0x5a8 is not the zero vector (an unordered compare counts as moving), bit 6 set; +0xec4 bits 0x200000,
// 0x800, 0x400, 0x2000 set; returns `other`. Leave (any other phase): +0x354 bits 31 and 6, +0x35c bit 6 and +0xec4 bits
// 0x200000 / 0x2000 / 0x800 / 0x400 cleared, 0.
uint8_t CKHkS08Hero::CtlControlLocked(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 0) {
        const bool still = m_unk5a8 == 0.0f && m_unk5ac == 0.0f && m_unk5b0 == 0.0f;  // TOC +0x28e0 (0x00c50d64)
        m_ui32HeroFlags354 = ((m_ui32HeroFlags354 & 0x7fffffffu) | (still ? 0u : 0x80000000u)) | 0x40u;
        m_unkec4 = m_unkec4 | 0x200000u | 0x800u | 0x400u | 0x2000u;
        return other;
    }
    if (phase == 1) {
        m_unkb0 = 5;
        return 0;
    }
    m_ui32HeroFlags354 &= 0x7fffffbfu;
    m_ui32HeroFlags35C &= ~0x40u;
    m_unkec4 &= 0xffdfd3ffu;
    return 0;
}

// 0x0033d000 CKHkS08Hero_CtlState3_AICombat: the partner fights. Entering: the combo credits reset (0x33f9d0), +0x1378,
// the move direction +0x37c and +0x394 cleared. Each frame: the attack buttons released; outside a grab combo a target
// sought (KStub_Return1_33f9c8 always allows it) and, outside any combo kind, the combat movement; then the attack queued.
uint8_t CKHkS08Hero::CtlAICombat(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        ResetComboAndAttackCredits();  // 0x0033f9d0
        m_unk1378 = 0.0f;
        const CVector3& zero = kHeroZeroVector;  // TOC +0x28e0
        m_unk37c = zero.x;
        m_unk384 = zero.z;
        m_unk380 = zero.y;
        m_unk394 = 0;
        return other;
    }
    if (phase != 0) return other;
    AIClearAttackButtons();  // 0x0033fdb8
    if (IsGrabComboKind() == 0) {  // 0x002fc208
        // KStub_Nop_33f9c0, then KStub_Return1_33f9c8.
        AIAcquireTargetIfCredits();  // 0x0033fae0
        if (IsComboKindFlagSet() == 0) AIUpdateCombatMovement(clock);  // 0x002fc1b0, 0x0033fb80
    }
    AIQueueAttack();  // 0x0033fdc8
    return other;
}

// 0x0033f9e8 CKHkS08Hero_ConsumeAttackCredits: the blows of the combo (+0x1a18) taken from the credits (+0x1a20); 0 and
// no credits left when they do not cover them.
uint8_t CKHkS08Hero::ConsumeAttackCredits() {
    const int32_t used = static_cast<int32_t>(m_unk1a18);
    const int32_t credits = static_cast<int32_t>(m_unk1a20);
    if (used > credits) {
        m_unk1a20 = 0;
        return 0;
    }
    m_unk1a20 = static_cast<uint32_t>(credits - used);
    return 1;
}

// 0x0033fa78 CKHkS08Hero_GrantPartnerAttackCredits_maybe: with at most one controlled hero, the first companion hero
// gets the combo's blows as credits.
void CKHkS08Hero::GrantPartnerAttackCredits() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    if (group->m_ui8ControlledHeroCount > 1) return;  // 0x002ca288 GetControlledHeroCount
    CKHkS08Hero* partner = static_cast<CKHkS08Hero*>(group->m_apCompanionHeroes[0]);
    partner->m_unk1a20 = partner->m_unk1a20 + m_unk1a18;
}

// 0x0033cac0 CKHkS08Hero_CopyPointRecordWithType4_maybe (type 4) / 0x0033cb08 _CopyPointRecordWithType2_maybe (type 2): the
// path character's walk type and its copy into the path-finding component (+0x3f8; CtlAIFollowFlying inlines them).
void CKHkS08Hero::SetPathCharacterType(uint32_t type) {
    m_PFCharacter.m_bits = (m_PFCharacter.m_bits & 0xfffffff8u) | type;  // +0x3e0
    m_PFCpnt.m_CharacterType = m_PFCharacter;                            // +0x3f8
}

// 0x0033e378 CKHkS08Hero_CtlState2_ScriptedMoveTo: the scripted move to +0x398 (CKControlableHero's move-to). A flying
// hero within 2 (TOC +0x292c; the flat distance, z first then fused) of the target lands (+0x358 bit 20 cleared, ground
// mode unless locked) and walks as type 4, else type 2 (SetPathCharacterType inlined: +0x3e0 copied to +0x3f8); a
// climbing hero is put on the ground; then the move itself (CtlMoveToTargetBody). The stick follows the move vector
// +0x3b8: none for the null vector (+0x37c.. = 0, +0x394 = 0), else +0x37c.. = the move and +0x394 = 255 x the speed
// ratio +0x3dc / +0xaf4 (0xff above 1, TOC +0x28e4; none at exactly 0, TOC +0x2900; x 255, TOC +0x28e8, fctiwz byte).
uint8_t CKHkS08Hero::CtlScriptedMoveTo(IKTime* clock, int32_t phase, uint8_t other) {
    if (IsFlyingMovementMode1() == 0) {  // 0x00340188
        SetPathCharacterType(2);
    } else {
        const float dz = m_unk3a0 - m_unk554;
        const float dx = m_unk398 - m_unk54c;
        const float flat = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dx, dx, dz * dz)));  // 0x00010690
        if (flat < 2.0f) {  // blt
            m_ui32HeroFlags358 &= 0xffefffffu;
            SetMovementModeUnlessLocked(0);  // 0x00342ef8
        }
        SetPathCharacterType(4);
    }
    if (IsClimbingMovementMode2() != 0) SetMovementModeUnlessLocked(0);  // 0x003401a0
    const uint8_t result = CtlMoveToTargetBody(clock, phase, other);  // 0x00368618
    const CVector3& zero = kHeroZeroVector;  // TOC +0x28e0 (g_nullVector)
    if (!(m_unk3b8 == zero.x && m_unk3bc == zero.y && m_unk3c0 == zero.z)) {
        const float ratio = m_unk3dc / m_unkaf4;
        uint8_t stick = 0xff;
        bool none = false;
        if (!(ratio > 1.0f)) {  // ble
            if (ratio == 0.0f) {
                none = true;
            } else {
                stick = static_cast<uint8_t>(ppc::fctiwz(ratio * 255.0f));
            }
        }
        if (!none) {
            m_unk394 = stick;
            m_unk37c = m_unk3b8;
            m_unk384 = m_unk3c0;
            m_unk380 = m_unk3bc;
            return result;
        }
    }
    m_unk37c = zero.x;
    m_unk384 = zero.z;
    m_unk380 = zero.y;
    m_unk394 = 0;
    return result;
}

// 0x0033cc28 StaticInitAndDestruction_33cc28: two file statics (0x00ceae6c, 0x00ceae70) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae6c = -1.0f;
[[maybe_unused]] float s_unkceae70 = -1.0f;
}  // namespace
