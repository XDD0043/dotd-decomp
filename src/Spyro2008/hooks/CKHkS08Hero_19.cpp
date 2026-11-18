// Reconstructed original translation unit: 0x364ab0-0x36e2d0 (GAME_TOC1, main_toc1), 61 functions, 43 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: IKHkHero (7), UpdateHeroControlStateMachine (1), UpdateHeroInputDerivedState (1), ReadHeroPlayerInput (1), ProbeGroundWorldPointBelow (1), NavSectors (1), CKS08HeroBlow (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x364ab0  CKHkS08Hero_GetAITarget_maybe  (CKHkS08Hero.h)
//   [ ] 0x364af0  CKHkS08Hero_GetTargetSlotPosition_maybe  [dead]
//   [ ] 0x364d50  IKHkHero_GetByte354Bit0_2_maybe  [dead]
//   [ ] 0x364d60  FUN_00364d60  [dead]
//   [ ] 0x364ed8  FUN_00364ed8  [dead]
//   [ ] 0x364fd8  FUN_00364fd8  [dead]
//   [ ] 0x365048  FUN_00365048  [dead]
//   [ ] 0x365310  FUN_00365310  [dead]
//   [x] 0x3656b0  CKHkS08Hero_UpdateActionStateMachine_maybe
//   [ ] 0x365bf0  KStub_Nop_365bf0  [dead]
//   [ ] 0x365bf8  KStub_Nop_365bf8  [dead]
//   [x] 0x365c00  CKHkS08Hero_UpdateShadowGroundPoint_maybe
//   [x] 0x365e78  CKHkS08Hero_SetMainShadowActive
//   [x] 0x365f30  CKHkS08Hero_DetachWaterWaveFx_maybe
//   [ ] 0x366020  CKHkS08Hero_SetFxRecordPlayerIndex_maybe  [dead]
//   [x] 0x366098  CKHkS08Hero_PlayMovementEventSounds_maybe
//   [x] 0x366ba8  CKHkS08Hero_UpdateFootstepFx_maybe
//   [x] 0x3670f8  CKHkS08Hero_UpdateMainShadowAndSurfaceFx_maybe
//   [x] 0x3678f8  CKHkS08Hero_UpdateFootsteps_maybe
//   [x] 0x367f50  CKHkS08Hero_CtlState10_Inactive_Condition
//   [x] 0x367f58  CKHkS08Hero_CtlState2_ScriptedMoveTo_Condition
//   [x] 0x367f98  CKHkS08Hero_CtlState4_ControlLocked_Condition
//   [x] 0x367fc0  CKHkS08Hero_CtlState10_Inactive
//   [x] 0x367ff8  CKHkS08Hero_CtlState9_Player
//   [ ] 0x368130  CKHkS08Hero_IsAIControlled_maybe  [dead]
//   [x] 0x368158  CKHkS08Hero_CtlState9_Player_Condition
//   [x] 0x368178  CKHkS08Hero_CtlState8_PlayerFollowsFocus_Condition
//   [x] 0x368248  CKHkS08Hero_HandleAIFollowGroundPhase_maybe
//   [ ] 0x368390  FUN_00368390  [dead]
//   [x] 0x368478  CKHkS08Hero_CtlState8_PlayerFollowsFocus
//   [x] 0x368618  CKHkS08Hero_CtlState2_MoveToTargetBody_maybe
//   [x] 0x3688a8  UpdateHeroControlStateMachine
//   [x] 0x368de0  CKHkS08Hero_ResetMoveInput
//   [x] 0x368f18  UpdateHeroInputDerivedState
//   [x] 0x369670  ReadHeroPlayerInput
//   [x] 0x369ac8  IKHkHero_SelectMoveEntryIndexForSpeed_maybe
//   [ ] 0x369c40  IKHkHero_SetMoveEntryFlag26ExceptTwo_maybe  [dead]
//   [ ] 0x369d10  IKHkHero_ClearMoveEntryFlag26_maybe  [dead]
//   [x] 0x369da0  IKHkHero_HasNonZeroSpeed530Or534_maybe
//   [ ] 0x369dd8  ProbeGroundWorldPointBelow_maybe  [dead]
//   [x] 0x369f40  IKHkHero_GetNavTransitionFlag2_IfAllowed_maybe
//   [ ] 0x36a000  NavSectors_IsNavPointValidAndWalkable_maybe  [dead]
//   [ ] 0x36a1a8  CKHkS08Hero_ReparentNodeToSceneRoot_maybe  [dead]
//   [x] 0x36a260  CKHkS08Hero_RequestOwnDragonSelectionIfMultiHero_maybe
//   [x] 0x36a2f8  CKHkS08Hero_ValidateNavPosition_maybe
//   [x] 0x36a578  CKHkS08Hero_TeleportTo_maybe
//   [x] 0x36ac88  CKHkS08Hero_TeleportToSavedPosition_maybe
//   [x] 0x36ad50  CKHkS08Hero_ProcessPendingTeleport_maybe
//   [x] 0x36aec0  CKHkS08Hero_ComputeCarriedSidePush_maybe
//   [x] 0x36b1a0  CKHkS08Hero_ConstrainMovementToNavigation_maybe
//   [x] 0x36bbf8  IKHkHero_InitMoveRequestFromSourcePoint_maybe
//   [x] 0x36bf20  CKHkS08Hero_MoveTowardDrivenTarget_maybe
//   [x] 0x36c160  CKHkS08Hero_AISteerToWaypoint_maybe
//   [x] 0x36c6a0  CKHkS08Hero_AIComputeFollowSteeringAndSpeed_maybe
//   [x] 0x36cc88  CKHkS08Hero_AIWarpToWaypointOnPathFailure_maybe
//   [x] 0x36d210  CKHkS08Hero_AIUpdatePathToTarget_maybe
//   [x] 0x36dd08  CKHkS08Hero_AIMoveToTarget_maybe
//   [x] 0x36de10  CKHkS08Hero_AIUpdateFollowPathAndArrival_maybe
//   [x] 0x36df50  CKHkS08Hero_AIUpdateFollowDestination_maybe
//   [x] 0x36e278  CKS08HeroBlow_Delete  (DOTD_DECLARE_FACTORIES, Spyro2008/logic/CKS08HeroBlow.h)
//   [ ] 0x36e2c8  KStub_Nop_36e2c8  [dead]
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/Math.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include <cmath>
#include <cstring>
#include "k2000/core/Stub.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/system/IKTime.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvShadow.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/logic/ai/CKDetectedMovable.h"
#include "k2000/math/CBBox.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/NavGrid.h"
#include "k2000/logic/fx/CKTargetCursorFxData.h"
#include "k2000/logic/fx/CKWaterSplashNodeFx.h"
#include "k2000/logic/fx/CKWaterWaveNodeFx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvDetect.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/logic/fx/CKTargetCursorNodeFx.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSparkNodeFx.h"

// 0x00365e78 CKHkS08Hero_SetMainShadowActive: the hero's shadow caster (the record at +0x64, whose byte +0x1d is
// m_unk81) joins or leaves the shadow service.
void CKHkS08Hero::SetMainShadowActive(int32_t active) {
    CKSrvShadow* service = static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow);
    CKShadowGround* ground = reinterpret_cast<CKShadowGround*>(&m_unk64);
    if (active == 0) {
        if (m_unk81 != 0) service->UnregisterCaster(ground, m_pShadowCpnt);  // 0x001fd6f0
    } else if (m_unk81 == 0) {
        service->RegisterCaster(m_pShadowCpnt, m_pKGLObject, ground, 0, nullptr, 0);  // 0x001fb6f8
    }
}

// 0x003656b0 CKHkS08Hero_UpdateActionStateMachine_maybe: the action machine (rows +0xc0, handlers +0xc8, current
// row +0xcc, 0xff none). A hero locked to an object (+0x358 bit 0) leaves it unless +0x364 bit 26 keeps it running.
void CKHkS08Hero::UpdateActionStateMachine(IKTime* clock) {
    const uint32_t* handlers = reinterpret_cast<const uint32_t*>(m_unkc8);
    if ((m_unk358 & 1u) != 0 && (m_unk364 & 0x4000000u) == 0) {
        if (m_unkCC == 0xff) return;
        SwitchState(handlers, m_unkCC, 0xff, clock);
        m_unkd0 = 0;
        return;
    }
    Vf100(clock);  // vt+0x100
    const uint8_t count = static_cast<IKGrpHero*>(m_pGrpHero)->GetNbHeroStatesB();  // vt+0x150
    uint8_t found = count;  // no condition true: the row count (one past the table)
    for (uint32_t row = 0; row < count; ++row) {
        if (CallStateCondition(m_unkc0[row].m_aPtmf1, clock, static_cast<uint8_t>(row)) != 0) {
            found = static_cast<uint8_t>(row);
            break;
        }
    }
    if (found != m_unkCC) {
        SwitchState(handlers, m_unkCC, found, clock);
        m_unk364 = (m_unk364 & 0xefffffffu) | 0x10000000u;
    }
    RunState(handlers, m_unkCC, clock);
}

// 0x00367f50 CKHkS08Hero_CtlState10_Inactive_Condition: always (the last row).
uint8_t CKHkS08Hero::CtlInactiveCondition(IKTime*, uint8_t) { return 1; }

// 0x00367f58 CKHkS08Hero_CtlState2_ScriptedMoveTo_Condition: a scripted move is asked (+0x35c bit 5, +0x360 bit 30,
// or +0x35c bit 29).
uint8_t CKHkS08Hero::CtlScriptedMoveToCondition(IKTime*, uint8_t) {
    if ((m_unk35c & 0x20u) != 0 || (m_unk360 & 0x40000000u) != 0) return 1;
    return static_cast<uint8_t>((m_unk35c >> 29) & 1u);
}

// 0x00367f98 CKHkS08Hero_CtlState4_ControlLocked_Condition: +0x35c bit 6 while the path component's flag 0x40 (+0x3b0)
// is clear.
uint8_t CKHkS08Hero::CtlControlLockedCondition(IKTime*, uint8_t) {
    if ((m_unk35c & 0x40u) == 0) return 0;
    return static_cast<uint8_t>(((m_unk3b0 ^ 0x40u) >> 6) & 1u);
}

// 0x00367fc0 CKHkS08Hero_CtlState10_Inactive: entering clears +0xb0.
uint8_t CKHkS08Hero::CtlInactive(IKTime*, int32_t phase, uint8_t other) {
    if (phase == 0) return other;
    if (phase == 1) m_unkb0 = 0;
    return 0;
}

// 0x00367ff8 CKHkS08Hero_CtlState9_Player: the player's input each frame; on the ground (+0x354 bit 0) with +0x358
// bit 20, or with +0x358 bit 5, or airborne with +0x354 bit 23 and one of them, vt+0x178 with 1.
uint8_t CKHkS08Hero::CtlPlayer(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase != 0) {
        if (phase == 1) m_unkb0 = 1;
        return 0;
    }
    ReadHeroPlayerInput();  // 0x00369670
    bool call;
    if ((m_unk354 & 1u) == 0 && (m_unk354 & 0x800000u) != 0) {
        call = (m_unk358 & 0x20u) != 0;
    } else {
        call = (m_unk358 & 0x100000u) != 0 || (m_unk358 & 0x20u) != 0;
    }
    if (call) Vf178(clock, 1);  // vt+0x178
    return other;
}

// 0x00368158 CKHkS08Hero_CtlState9_Player_Condition: the hero is its own tracked leader (the player's hero).
uint8_t CKHkS08Hero::CtlPlayerCondition(IKTime*, uint8_t) { return m_ui8Hero == m_ui8TrackedLeader ? 1 : 0; }

// 0x00368178 CKHkS08Hero_CtlState8_PlayerFollowsFocus_Condition: the player's hero while the group's focused dragon
// is another one (and none of the group's flags 0x1000 / 0x2000 / 0x4000). Staying in the state needs the hero drawn
// this frame and less than +0x324 seconds since +0xb8; entering it, +0x364 bit 30.
uint8_t CKHkS08Hero::CtlPlayerFollowsFocusCondition(IKTime* clock, uint8_t row) {
    if (m_ui8TrackedLeader != m_ui8Hero) return 0;
    if ((m_unk368 & 4u) != 0) return 0;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (static_cast<int32_t>(static_cast<int8_t>(group->m_unk66)) == static_cast<int32_t>(m_ui8TrackedLeader)) return 0;
    const uint32_t flags = group->m_unkf8;
    if ((flags & 0x4000u) != 0 || (flags & 0x1000u) != 0 || (flags & 0x2000u) != 0) return 0;
    if (row != m_unkAC) return static_cast<uint8_t>((m_unk364 >> 30) & 1u);
    if (static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) return 1;
    const float elapsed = clock->m_afCurrentTime[0] - m_unkb8;
    return elapsed <= m_unk324 ? 1 : 0;  // cror lt|eq: a NaN is false
}

// 0x00368248 CKHkS08Hero_HandleAIFollowGroundPhase_maybe (the AI follow handler's update part): +0x3b4 from vt+0xf0,
// vt+0x178 with 1 under +0x358 bit 5, then the follow destination. Entering sets +0xb0 to 3.
uint8_t CKHkS08Hero::HandleAIFollowGroundPhase(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        m_unk3b4 = VfF0();  // vt+0xf0
        if ((m_unk358 & 0x20u) != 0) Vf178(clock, 1);  // vt+0x178
        AIUpdateFollowDestination(clock);  // 0x0036df50
        return other;
    }
    if (phase != 1) return 0;
    m_unkb0 = 3;
    return 0;
}

// 0x003688a8 UpdateHeroControlStateMachine: the control machine (rows +0xa0, handlers +0xa8, current row +0xac). With
// +0x358 bit 3 (control suspended) the hero leaves its state and, if it is the player's, only reads the input.
void CKHkS08Hero::UpdateControlStateMachine(IKTime* clock) {
    const uint32_t* handlers = reinterpret_cast<const uint32_t*>(m_unka8);
    if ((m_unk358 & 8u) != 0) {
        if (m_unkAC != 0xff) {
            SwitchState(handlers, m_unkAC, 0xff, clock);
            m_unkb0 = 0;
        }
        if (m_ui8Hero == m_ui8TrackedLeader) ReadHeroPlayerInput();  // 0x00369670
        return;
    }
    VfFC(clock);  // vt+0xfc
    const uint8_t count = static_cast<IKGrpHero*>(m_pGrpHero)->GetNbHeroStatesA();  // vt+0x148
    uint8_t found = count;  // no condition true: the row count
    for (uint32_t row = 0; row < count; ++row) {
        if (CallStateCondition(m_unka0[row].m_aPtmf1, clock, static_cast<uint8_t>(row)) != 0) {
            found = static_cast<uint8_t>(row);
            break;
        }
    }
    if (found != m_unkAC) SwitchState(handlers, m_unkAC, found, clock);
    RunState(handlers, m_unkAC, clock);
}

namespace {
// 0x00c50d4c: the shared Z axis (zero in the EBOOT's BSS, filled by a static initialiser; TOC +0x2e4c).
constexpr CVector3 kHeroAxisZ{0.0f, 0.0f, 1.0f};

// 0x002ca0f8 CKGrpS08Hero_GetFocusedHero (local copy; CKGrpS08Hero.cpp): the focused dragon (+0x66, -1 none) among the
// group's heroes (+0x30).
IKSerializable* GetFocusedHeroOf(const IKGrpHero* group) {
    const int8_t index = static_cast<int8_t>(group->m_unk66);
    if (index == -1) return nullptr;
    return group->m_apHeros[index];
}

// ---- step 4 AI: helpers the original inlines. ----
// Whether the graph node `hint` names exists and its box holds `p` (the original tests x, z, then y; inf <= v <= sup).
bool PointInNodeBox(const CKSrvPathFinding* service, const CVector3& p, uint16_t hint) {
    const int32_t node = static_cast<int16_t>(hint);
    if (node < 0) return false;
    if (static_cast<uint32_t>(node) >= service->m_Graph.m_ui32GraphNodesSize) return false;
    const CBBox& box = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[hint])->m_Sector.m_box;
    if (!(box.m_inf.x <= p.x) || !(box.m_sup.x >= p.x)) return false;
    if (!(box.m_inf.z <= p.z) || !(box.m_sup.z >= p.z)) return false;
    if (!(box.m_inf.y <= p.y) || !(box.m_sup.y >= p.y)) return false;
    return true;
}

// The ground under a navigation point (x, z), probed from the top of its node's box (masks 1 / 8, no delta or
// height) starting from the hero's current contact (+0x4b8); the probe point itself without a ground.
void ProbeNavPointGround(const CKHkS08Hero* hero, const CKSrvPathFinding* service, float x, float z, uint16_t hint,
                         CVector3* out) {
    CGroundContactDatasIn in;  // masks {1, 8}
    in.m_fDeltaMax = 0.0f;
    in.m_fObjectHeight = 0.0f;
    CGroundContactDatasInOut contact;
    CopyGroundContact(contact, hero->m_gcCurDatasInOut);
    CVector3 probe;
    probe.x = x;
    probe.z = z;
    probe.y = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[hint])->m_Sector.m_box.m_sup.y;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &contact, &probe.x, 1);  // 0x00196540
    GroundContact_GetWorldPointOr(&contact, &probe, out);  // 0x00582e08
}

// `a` within `e` of `d` on each axis (the original's chain of cror tests; the last one is d.z <= a.z + e).
uint8_t WithinBox(const CVector3& a, const CVector3& d, float e) {
    if (!(a.x - e <= d.x) || !(a.x + e >= d.x)) return 0;
    if (!(a.y - e <= d.y) || !(a.y + e >= d.y)) return 0;
    if (!(a.z - e <= d.z)) return 0;
    return d.z <= a.z + e ? 1 : 0;
}
}  // namespace

// 0x00368de0 CKHkS08Hero_ResetMoveInput: the input bytes (+0x36c, the group's vt+0x10c of them), the stick and move
// vectors, the held times, the magnitude and speed band cleared; +0x360 bit 29, +0x358 bits 20 / 21, +0x364 bits 20 / 21
// and, unless `keepBit17`, +0x360 bit 17.
void CKHkS08Hero::ResetMoveInput(int32_t keepBit17) {
    uint8_t* inputs = m_unk36c;
    const uint8_t size = static_cast<IKGrpHero*>(m_pGrpHero)->GetHeroRuntimeBlockSize();  // vt+0x10c
    std::memset(inputs, 0, size);  // TocBridge_memset
    m_unk390 = 0;
    m_unk392 = 0;
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2e3c
    m_unk370 = zero.x;
    m_unk378 = zero.z;
    m_unk374 = zero.y;
    m_unk37c = zero.x;
    m_unk384 = zero.z;
    m_unk380 = zero.y;
    m_unk38c = 0.0f;  // stw 0
    m_unk395 = 0;
    m_unk394 = 0;
    m_unk388 = 0.0f;
    m_unk360 &= 0xdfffffffu;
    m_unk358 &= 0xffcfffffu;
    m_unk364 &= 0xffcfffffu;
    if (keepBit17 == 0) m_unk360 &= 0xfffdffffu;
}

// 0x00368f18 UpdateHeroInputDerivedState: the action input first (vt+0xe4), then from the input bytes the stick
// (+0x390 / +0x392 the differences of inputs 2 - 3 and 0 - 1, +0x370 / +0x378 the unit vector, +0x394 its length up to
// 255), the speed band (+0x395: the last enabled, unlocked speed mode whose threshold the length reaches; none: the stick
// is dropped unless +0x368 bit 5), the follow speed (+0x3dc, scaled by +0x350 % for the hero not focused), the move
// direction (+0x37c: the camera's view direction turned by the stick's yaw from +z, flat) and the move target +0x3b8
// (the move direction; without one, the facing +0x540 when the target was cleared), and the flags of inputs 4 / 5 / 7 /
// 6 / 8 (+0x358 bits 20 / 21, +0x364 bits 21 / 20, +0x360 bit 17). With +0x358 bit 3 the speed and target stay.
void CKHkS08Hero::UpdateHeroInputDerivedState() {
    UpdateHeroActionInput();  // vt+0xe4 0x003445d8
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    const uint8_t input2 = m_unk36c[group->GetInputAction(2)];  // vt+0x118
    const uint8_t input3 = m_unk36c[group->GetInputAction(3)];
    m_unk390 = static_cast<uint16_t>(input2 - input3);
    const uint8_t input0 = m_unk36c[group->GetInputAction(0)];
    const uint8_t input1 = m_unk36c[group->GetInputAction(1)];
    m_unk392 = static_cast<uint16_t>(input0 - input1);
    const float x = static_cast<float>(static_cast<int16_t>(m_unk390));  // extsh, fcfid, frsp
    const float z = static_cast<float>(static_cast<int16_t>(m_unk392));
    m_unk370 = x;
    m_unk374 = 0.0f;  // TOC +0x2e50
    m_unk378 = z;
    if (m_unk370 == 0.0f && m_unk378 == 0.0f) {
        m_unk394 = 0;
    } else {
        const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));  // Math_Sqrtf 0x10690
        uint8_t magnitude = 0;
        if (length != 0.0f) {
            const float inverse = 1.0f / length;  // TOC +0x2e44
            m_unk378 = inverse * m_unk378;
            m_unk370 = inverse * m_unk370;
            m_unk374 = inverse * m_unk374;
            // fctiwz, stfiwx, lhz: the low half-word of the truncated length, 0xff above 0xfe.
            const uint16_t whole = static_cast<uint16_t>(ppc::fctiwz(length));
            magnitude = whole > 0xfe ? 0xff : static_cast<uint8_t>(whole);
        }
        m_unk394 = magnitude;
    }
    const uint8_t count = CKGrpS08Hero::GetNbSpeedModesOf(m_ui8Hero);  // vt+0x11c
    m_unk395 = 0;
    for (uint32_t i = 0; i < count; ++i) {
        const SHeroSpeedMode& mode = m_asSpeedModes[i];
        if (mode.m_bEnable != 0 && mode.m_bLocked == 0 && m_unk394 >= mode.m_ui8Threshold) {
            m_unk395 = static_cast<uint8_t>(i);
        }
    }
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2e3c
    if (m_unk395 == 0 && (m_unk368 & 0x20u) == 0) {
        m_unk370 = zero.x;
        m_unk374 = zero.y;
        m_unk378 = zero.z;
    }
    if ((m_unk358 & 8u) == 0) {
        m_unk3dc = m_asSpeedModes[m_unk395].m_afHSpeeds[static_cast<int32_t>(m_unk58c)];
        if (GetFocusedHeroOf(group) != this) {  // 0x002ca0f8
            const float scale = ppc::fmadds(static_cast<float>(m_unk350), 0.01f, 1.0f);  // TOC +0x2e48, +0x2e44
            m_unk3dc = m_unk3dc * scale;
        }
    }
    if (m_unk370 == 0.0f && m_unk378 == 0.0f) {
        m_unk37c = zero.x;
        m_unk380 = zero.y;
        m_unk384 = zero.z;
    } else {
        CVector3* move = reinterpret_cast<CVector3*>(&m_unk37c);
        CKSrvCamera_GetViewDirection(move);  // 0x00582f28
        m_unk380 = 0.0f;
        const float length =
            std::sqrt(ppc::fmadds(m_unk384, m_unk384, ppc::fmadds(m_unk37c, m_unk37c, m_unk380 * m_unk380)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_unk384 = inverse * m_unk384;
            m_unk37c = inverse * m_unk37c;
            m_unk380 = inverse * m_unk380;
        }
        const float angle = Vec3_YawDifferenceWrapped(&kHeroAxisZ, reinterpret_cast<const CVector3*>(&m_unk370));
        Vec3_RotateYawFlatNormalized(angle, move);  // 0x00584e40
    }
    if ((m_unk358 & 8u) == 0) {
        if (m_unk37c == zero.x && m_unk380 == zero.y && m_unk384 == zero.z) {
            if (m_unk3b8 == zero.x && m_unk3bc == zero.y && m_unk3c0 == zero.z) {
                m_unk3b8 = m_unk540;
                m_unk3c0 = m_unk548;
                m_unk3bc = m_unk544;
            }
        } else {
            m_unk3b8 = m_unk37c;
            m_unk3c0 = m_unk384;
            m_unk3bc = m_unk380;
        }
    }
    const uint8_t input4 = m_unk36c[group->GetInputAction(4)];
    m_unk358 = (m_unk358 & 0xffefffffu) | (input4 != 0 ? 0x100000u : 0u);
    const uint8_t input5 = m_unk36c[group->GetInputAction(5)];
    uint32_t bit21 = 0;
    if (input5 != 0) bit21 = (((m_unk360 >> 19) & 1u) ^ 1u) << 21;
    m_unk358 = (m_unk358 & 0xffdfffffu) | bit21;
    const uint8_t input7 = m_unk36c[group->GetInputAction(7)];
    m_unk364 = (m_unk364 & 0xffdfffffu) | (input7 != 0 ? 0x200000u : 0u);
    const uint8_t input6 = Vf144();  // vt+0x144
    m_unk364 = (m_unk364 & 0xffefffffu) | ((static_cast<uint32_t>(input6) << 20) & 0x0ff00000u);
    const uint8_t input8 = m_unk36c[group->GetInputAction(8)];
    uint32_t bit17 = 0;
    if (input8 != 0) bit17 = (((m_unk358 >> 16) & 1u) ^ 1u) << 17;  // lhz +0x358: its bit 0 is the word's bit 16
    m_unk360 = (m_unk360 & 0xfffdffffu) | bit17;
}

// 0x00369670 ReadHeroPlayerInput: once per frame (+0x360 bit 6, the read mark): the game manager's pressed bytes of the
// player's (+0x26) actions 0..49 and 50..51 into +0x36c, the held times of inputs 4 and 5 into +0x388 / +0x38c (input 5's
// release sets +0x360 bit 29, its hold keeps +0x35c bit 30; with +0x360 bit 19 a press or hold sets +0x35c bit 30), then
// UpdateHeroInputDerivedState. A group with input blocked (+0xf8 bit 3) gives the hero no input.
void CKHkS08Hero::ReadHeroPlayerInput() {
    if ((m_unk360 & 0x40u) != 0) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const uint8_t before = group->GetNbInputActions();      // vt+0x110
    const uint8_t after = group->GetNbExtraInputActions();  // vt+0x114
    if ((group->m_unkf8 & 8u) != 0) {
        ResetMoveInput(0);              // 0x00368de0
        UpdateHeroInputDerivedState();  // 0x00368f18
        m_unk360 = (m_unk360 & ~0x40u) | 0x40u;
        return;
    }
    uint8_t* inputs = m_unk36c;
    for (uint32_t i = 0; i != before; ++i) inputs[i] = manager->IsActionPressed(i & 0xffu, m_ui8Leader);  // vt+0x160
    m_unk388 = manager->GetActionValue(group->GetInputAction(4), m_ui8Leader);  // vt+0x164
    const float held5 = manager->GetActionValue(group->GetInputAction(5), m_ui8Leader);
    if ((m_unk360 & 0x80000u) != 0) {
        const uint8_t pressed5 = m_unk36c[group->GetInputAction(5)];
        const uint32_t holding = (held5 != 0.0f || pressed5 != 0) ? 0x40000000u : 0u;
        m_unk35c = (m_unk35c & 0xbfffffffu) | holding;
        m_unk360 &= 0xdfffffffu;
    } else {
        uint32_t released = 0;
        if ((m_unk35c & 0x40000000u) == 0 && m_unk38c != 0.0f && held5 == 0.0f) released = 0x20000000u;
        m_unk360 = (m_unk360 & 0xdfffffffu) | released;
        uint32_t holding = 0;
        if ((m_unk35c & 0x40000000u) != 0 && held5 != 0.0f) holding = 0x40000000u;
        m_unk35c = (m_unk35c & 0xbfffffffu) | holding;
    }
    m_unk38c = held5;
    if (after != 0) {
        uint8_t* extra = m_unk36c + before;
        for (uint32_t i = 0; i != after; ++i) {
            extra[i] = manager->IsActionPressed((before + i) & 0xffu, m_ui8Leader);
        }
    }
    UpdateHeroInputDerivedState();  // 0x00368f18
    m_unk360 = (m_unk360 & ~0x40u) | 0x40u;
}

// 0x0036df50 CKHkS08Hero_AIUpdateFollowDestination_maybe: the AI partner's destination (+0x398) and facing (+0x3a4).
// It stays where it is (+0x3b0 cleared) while it may (+0x358 bit 16 when bit 17 is set), is not held (+0x354 bit 21,
// +0x364 bit 5), stands still (+0x530 0) and is within +0x238 of its leader, and either farther than +0x23c or inside
// the cone of half the group's angle (+0xf2, degrees) behind the leader's yaw (+0x538). Otherwise it takes a follow
// slot of the leader (AssignFollowSlot) and walks there at the leader's speed, or (no slot) keeps its position at speed 0.
void CKHkS08Hero::AIUpdateFollowDestination(IKTime* clock) {
    const float zero = 0.0f;  // TOC +0x2e88
    CKHkS08Hero* leader = GetControllingHero();  // 0x00344e68
    CVector3 away;
    away.x = m_unk54c - leader->m_unk54c;
    away.y = zero;
    away.z = m_unk554 - leader->m_unk554;
    float distance = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(away.z, away.z, ppc::fmadds(away.x, away.x, zero))));  // 0x00010690
    if (distance != zero) {
        const float inverse = 1.0f / distance;  // TOC +0x2ecc
        away.z = away.z * inverse;
        away.x = away.x * inverse;
        away.y = away.y * inverse;
    } else {
        distance = zero;
    }
    const uint32_t mayStay = (m_unk358 & 0x20000u) != 0 ? ((m_unk358 >> 16) & 1u) : 1u;
    const float leaderYaw = leader->m_unk538;
    const float stayRadius = m_unk238;
    const float coneRadius = m_unk23c;
    const float speed = m_unk530;
    float angle = Math_WrapAngleToPi(leaderYaw - Vec3_GetYawAngleFromX(&away));  // 0x00244638, 0x00582c18
    angle = std::fabs(angle);  // the sign bit cleared in memory
    const uint16_t coneDegrees = static_cast<const IKGrpHero*>(m_pGrpHero)->m_sProperties.m_aui16Values[1];  // +0xf2
    bool stay = false;
    if (mayStay != 0 && (m_unk354 & 0x200000u) == 0 && (m_unk364 & 0x20u) == 0 && speed == zero &&
        distance < stayRadius) {  // bge: a NaN follows
        if (distance > coneRadius) {
            stay = true;
        } else {
            const float halfCone = static_cast<float>(coneDegrees) * 0.5f * 1.74532905e-2f;  // TOC +0x2f2c, +0x2f38
            stay = halfCone < angle;  // bge: a NaN follows
        }
    }
    if (stay) {
        m_unk398 = m_unk54c;
        m_unk3a0 = m_unk554;
        m_unk39c = m_unk550;
        m_unk3a4 = m_unk540;
        m_unk3ac = m_unk548;
        m_unk3a8 = m_unk544;
        m_unk3b0 = 0;
        return;
    }
    const CVector3* slot = static_cast<CKGrpS08Hero*>(m_pGrpHero)->AssignFollowSlot(this);  // 0x002cb6f0
    float followSpeed = zero;
    if (slot != nullptr) {
        m_unk398 = slot->x;
        m_unk39c = slot->y;
        m_unk3a0 = slot->z;
        followSpeed = leader->m_unk530;
    } else {
        m_unk398 = m_unk54c;
        m_unk39c = m_unk550;
        m_unk3a0 = m_unk554;
    }
    m_unk3a4 = m_unk540;
    m_unk3a8 = m_unk544;
    m_unk3ac = m_unk548;
    AIUpdateFollowPathAndArrival(followSpeed, clock, reinterpret_cast<CVector3*>(&m_unk398),
                                 reinterpret_cast<const CVector3*>(&m_unk3a4),
                                 reinterpret_cast<const CVector3*>(&leader->m_unk540), 0);  // 0x0036de10
}

// 0x00369ac8 IKHkHero_SelectMoveEntryIndexForSpeed_maybe: the last enabled, unlocked speed mode whose speed of the
// current class (+0x58c) is at most `speed` (when moving, the first such mode counts even above it).
uint8_t CKHkS08Hero::SelectMoveEntryIndexForSpeed(float speed) {
    const uint8_t count = CKGrpS08Hero::GetNbSpeedModesOf(m_ui8Hero);  // vt+0x11c
    uint8_t selected = 0;
    if (count == 0) return 0;
    const bool still = speed == 0.0f;  // TOC +0x2e88
    for (uint32_t i = 0; i < count; ++i) {
        const SHeroSpeedMode& mode = m_asSpeedModes[i];
        if (mode.m_bEnable == 0 || mode.m_bLocked != 0) continue;
        const bool reached = mode.m_afHSpeeds[m_unk58c] <= speed;  // cror lt|eq
        if (still) {
            if (reached) selected = static_cast<uint8_t>(i);
        } else if (reached || selected == 0) {
            selected = static_cast<uint8_t>(i);
        }
    }
    return selected;
}

// 0x0036ad50 CKHkS08Hero_ProcessPendingTeleport_maybe: a lost AI partner (+0x35c bit 18, in the follow state 3, not
// locked) asks for a catch-up warp (+0x35c bit 17); the warp happens while its node is not drawn: to the camera's
// position less its offset (CKSrvCamera +0x598 - +0x5c8), facing +0x540. Answers 1 when the warp was done.
uint8_t CKHkS08Hero::ProcessPendingTeleport(uint8_t flag1, uint8_t flag2) {
    uint32_t flags = m_unk35c;
    if ((flags & 0x40000u) != 0 && m_ui8Hero != m_ui8TrackedLeader && (m_unk358 & 1u) == 0 && m_unkb0 == 3) {
        m_unk35c = (m_unk35c & 0xfffdffffu) | 0x20000u;
        flags = m_unk35c;
    }
    if ((flags & 0x20000u) == 0) return 0;
    if (static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter) return 0;
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    CVector3 position;
    position.x = camera->m_v3RealPos.x - camera->m_v3RealAxisZ.x;
    position.y = camera->m_v3RealPos.y - camera->m_v3RealAxisZ.y;
    position.z = camera->m_v3RealPos.z - camera->m_v3RealAxisZ.z;
    const uint32_t done = TeleportTo(&position, reinterpret_cast<const CVector3*>(&m_unk540), flag1, 1, 0xffff, flag2);  // 0x0036a578
    m_unk35c = (m_unk35c & 0xfffdffffu) | (((done ^ 1u) & 0xffu) << 17);
    return static_cast<uint8_t>(((m_unk35c >> 17) & 1u) ^ 1u);
}

namespace {
// The active animation's time in percent of its duration now and one frame (+0x154, the last time step) before (at
// least 0), as UpdateFootsteps computes them twice (the time wrapped into the duration when past it: fdivs, fctiwz,
// fcfid, fmuls, fsubs; `wrapOnNaN` takes the second block's bge, where an unordered compare wraps too).
void AnimPercents(CKHkS08Hero* hero, bool wrapOnNaN, float* before, float* now) {
    AnimBlendSlot* slot = hero->GetAnimBlendSlot();  // vt+0x194
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    const float total = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])->GetDuration();
    slot = hero->GetAnimBlendSlot();
    blender = static_cast<CKBlenderController*>(slot->m_pController);
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
    const float duration = controller->GetDuration();  // 0x0007ab60
    float t = controller->m_unk50;
    const bool wrap = wrapOnNaN ? !(duration >= t) : duration < t;
    if (wrap) {
        const int32_t loops = ppc::fctiwz(t / duration);
        t = t - duration * static_cast<float>(static_cast<double>(loops));
    }
    float previous = t - hero->m_unk154;
    *now = (t / total) * 100.0f;  // TOC +0x2dc8
    if (previous < 0.0f) previous = 0.0f;  // TOC +0x2dbc
    *before = (previous / total) * 100.0f;
}

// A percent mark (a byte of the hero) passed in this frame's step: at or after it before, past it now.
bool PercentPassed(float before, float now, uint8_t mark) {
    const float at = static_cast<float>(static_cast<double>(mark));
    return before <= at && now > at;
}
}  // namespace

// 0x003678f8 CKHkS08Hero_UpdateFootsteps_maybe: the water flags (+0x358 bit 8: in the water of a ground of engine flag 2
// whose level +0x40 is not below the hero; bit 9 entered this frame, +0x35c bit 13 left), the footstep marks of the
// animation in percent (+0x354 bits 27 / 28 at +0x34a / +0x34b with +0x354 bit 29; +0x360 bits 22 / 23 at +0x34c /
// +0x34d with +0x35c bit 22 and +0x850 3), then the footstep FX, the trail FX, the swing trails, the movement and
// footstep sounds, the main shadow and the surface FX, the shadows and flight FX.
void CKHkS08Hero::UpdateFootsteps(IKTime* clock) {
    const uint32_t old = m_unk358;
    uint32_t flags = old & 0xfffffeffu;
    m_unk358 = flags;
    const CGround* ground = static_cast<const CGround*>(m_gcCurDatasInOut.m_pGround);
    if (ground != nullptr && (ground->m_ba16EngineFlags & 2u) != 0 && ground->m_fPropertieValue - m_unk550 >= 0.0f) {
        flags |= 0x100u;  // TOC +0x2dbc; cror gt|eq
        m_unk358 = flags;
    }
    uint32_t left = 0;
    if ((old & 0x100u) == 0) {
        m_unk358 = (flags & 0xfffffdffu) | (((m_unk358 >> 8) & 1u) << 9);
    } else {
        m_unk358 = flags & 0xfffffdffu;
        if ((m_unk358 & 0x100u) == 0) left = 0x2000u;
    }
    m_unk35c = (m_unk35c & 0xffffdfffu) | left;
    m_unk354 &= 0xe7ffffffu;
    if ((m_unk354 & 0x20000000u) != 0) {
        float before;
        float now;
        AnimPercents(this, false, &before, &now);
        const uint32_t first = PercentPassed(before, now, m_unk34a) ? 0x8000000u : 0u;
        m_unk354 = (m_unk354 & 0xf7ffffffu) | first;
        const bool second = PercentPassed(before, now, m_unk34b) || (m_unk358 & 0x2000u) != 0;
        m_unk354 = (m_unk354 & 0xefffffffu) | (second ? 0x10000000u : 0u);
    }
    m_unk360 &= 0xff3fffffu;
    if ((m_unk35c & 0x400000u) != 0 && m_unk850 == 3) {
        float before;
        float now;
        AnimPercents(this, true, &before, &now);
        const uint32_t first = PercentPassed(before, now, m_unk34c) ? 0x400000u : 0u;
        m_unk360 = (m_unk360 & 0xffbfffffu) | first;
        const uint32_t second = PercentPassed(before, now, m_unk34d) ? 0x800000u : 0u;
        m_unk360 = (m_unk360 & 0xff7fffffu) | second;
    }
    m_unk16c = 0;  // vt+0xe8 0x00333608 CKHkS08Hero_vfE8: 0
    UpdateFootstepFx(clock);  // 0x00366ba8
    UpdateTrailAndFootstepFx();  // vt+0x10c 0x00336598
    UpdateSwingTrails();  // vt+0x110 0x00335158 (vt+0x114 0x333610 is empty)
    PlayMovementEventSounds(clock);       // 0x00366098
    PlayFootstepSounds(clock);            // vt+0x118 0x00334110
    UpdateMainShadowAndSurfaceFx(clock);  // 0x003670f8
    UpdateShadowsAndFlightFx();           // vt+0x11c 0x0033a050
}

// 0x00365c00 CKHkS08Hero_UpdateShadowGroundPoint_maybe: the main shadow's ground point (+0x64), normal (+0x70), height
// (+0x7c) and water flag (+0x80 bit 4): probed under the hero's hot spot 0 (+0x174) when vt+0x12c (0 here) or +0x360
// bit 7 asks for it and the group has that hot spot, else the current ground contact's (when its status is 0 or 1).
void CKHkS08Hero::UpdateShadowGroundPoint() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    // vt+0x12c 0x009bd600 CKHkS08Hero_vf12C: 0.
    if ((m_unk360 & 0x80u) != 0 && static_cast<int8_t>(group->GetHotSpotIndex(m_ui8Hero, 0)) != -1) {  // vt+0x16c
        const int8_t index = static_cast<int8_t>(group->GetHotSpotIndex(m_ui8Hero, 0));
        CVector3 point;
        static_cast<CSGHotSpot*>(m_apHotSpots[index])->GetWorldPosition(&point);  // 0x000ce790
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_gcDatasIn, &m_unk174, &point.x, 1);  // 0x00196540
        if (m_unk174.m_eContactStatus == 3) return;
        CVector3 world;
        GroundContact_GetWorldPoint(&m_unk174, &world);  // 0x001a70e0
        m_unk64 = world.x;
        m_unk68 = world.y;
        m_unk6c = world.z;
        CVector3 normal;
        GroundContact_GetWorldNormal(&m_unk174, &normal);  // 0x001a71d8
        m_unk70 = normal.x;
        m_unk74 = normal.y;
        m_unk78 = normal.z;
        SetF32(m_unk7c, m_unk174.m_fdH);
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_unk174.m_pGround);
        if (((ground->m_ba16EngineFlags >> 6) & 1u) != 0) {
            m_unk80 |= 0x10u;
        } else if ((m_unk80 & 0x10u) != 0) {
            m_unk80 ^= 0x10u;
        }
        return;
    }
    if (static_cast<int32_t>(m_gcCurDatasInOut.m_eContactStatus) > 1) return;
    m_unk64 = m_unk570;
    m_unk6c = m_unk578;
    m_unk68 = m_unk574;
    m_unk70 = m_unk564;
    m_unk78 = m_unk56c;
    m_unk74 = m_unk568;
    SetF32(m_unk7c, m_gcCurDatasInOut.m_fdH);
}

// 0x00366098 CKHkS08Hero_PlayMovementEventSounds_maybe: the group's movement event sounds (vt+0x158: none in DotD,
// every event gives -1) on the hero's event flags, at the leader's or the partner's volume (+0x298 / +0x29c); the only
// lasting effect is the Rand_Int of the landing (+0x354 bit 13 with the sound offset +0x118): the chance +0x34f in 100 of
// event 0xc, then a draw for the variant.
void CKHkS08Hero::PlayMovementEventSounds(IKTime* clock) {
    CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    const float volume = m_ui8Hero == m_ui8TrackedLeader ? m_unk298 : m_unk29c;
    // An event's sound: none for -1, else entry `sound + offset` of the dictionary played (its volume set first with
    // `setVolume`, its flag 0x40 with `once`).
    auto play = [&](int32_t sound, int32_t offset, bool setVolume, bool once) {
        CKSound* entry = dictionary->GetSound(static_cast<uint32_t>(sound + offset));  // 0x00112bc0
        if (once) entry->m_SoundFlags = (entry->m_SoundFlags & 0xffffffbfu) | 0x40u;
        if (setVolume) entry->SetBaseVolume(volume);  // 0x00110ee8
        entry->Play(0.0f);  // 0x00111230; TOC +0x2dbc
    };
    const uint8_t* surface = CKGrpS08Hero::GetSurfaceEntry(m_unk16c);  // vt+0x160
    bool second = true;  // the second footstep check (+0x354 bit 2) and the water entry (+0x358 bit 9)
    if (surface[1] != 0) {
        if ((m_unk354 & 0x8000000u) != 0 || (m_unk354 & 0x10000000u) != 0) {
            const int8_t sound = CKGrpS08Hero::GetMovementEventSound(0);  // vt+0x158
            if (sound != -1) play(sound, m_unk16c, true, true);
        }
        int8_t sound = -1;
        if ((m_unk354 & 4u) != 0 && (m_unk358 & 0x100u) == 0) {
            sound = CKGrpS08Hero::GetMovementEventSound(1);
        } else if ((m_unk358 & 0x200u) != 0) {
            sound = CKGrpS08Hero::GetMovementEventSound(1);
        }
        if (sound != -1) play(sound, m_unk16c, true, false);
    }
    (void)second;
    if ((m_unk354 & 2u) != 0 && (m_unk35c & 0x400000u) == 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(2);
        if (sound != -1) play(sound, static_cast<int8_t>(m_unk590), true, false);
    }
    if ((m_unk354 & 0x40000000u) != 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(3);
        if (sound != -1) play(sound, 0, false, false);
    }
    if ((m_unk35c & 0x100u) != 0 && ((m_unk354 & 0x2000u) != 0 || (m_unk354 & 0x8000u) != 0) &&
        CKGrpS08Hero::GetHeroSoundByte(m_ui8Hero) != static_cast<int32_t>(m_unk588)) {  // vt+0x168
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(4);
        if (sound != -1) play(sound, 0, false, false);
    }
    if ((m_unk358 & 0x200u) != 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(5);
        if (sound != -1) play(sound, 0, false, false);
    }
    bool event6 = (m_unk364 & 0x20000000u) != 0;
    if ((m_unk358 & 0x10000u) != 0 && m_ui8Hero == m_ui8TrackedLeader && (m_unk354 & 0x1000u) == 0 &&
        (m_unk364 & 0x40u) == 0) {
        event6 = true;
    }
    if (event6) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(6);
        if (sound != -1) play(sound, 0, false, false);
    }
    if ((m_unk360 & 2u) != 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(7);
        if (sound != -1) play(sound, 0, false, false);
    }
    if ((m_unk360 & 0x1000000u) != 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(8);
        if (sound != -1) play(sound, 0, false, false);
    }
    if ((m_unk35c & 0x400000u) != 0) {
        const SHeroStateRow* row = &m_unk140[m_unk14c];
        const int32_t relative = static_cast<int32_t>(static_cast<int16_t>(m_unk160)) -
                                 static_cast<int32_t>(static_cast<int16_t>(row->m_key >> 16));
        if (static_cast<uint32_t>(relative - 2) <= 1u) {
            AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
            CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
            CKAnmKeyFrameController* controller =
                static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
            const float duration = controller->GetDuration();  // 0x0007ab60
            float t = controller->m_unk50;
            if (duration < t) {
                const int32_t loops = ppc::fctiwz(t / duration);
                t = t - duration * static_cast<float>(static_cast<double>(loops));
            }
            if ((m_unk354 & 0x2000u) == 0 && t - clock->m_afDeltaTime[0] <= 0.0f) {
                const int8_t sound = CKGrpS08Hero::GetMovementEventSound(9);
                if (sound != -1) play(sound, 0, false, true);
            }
        }
        if ((m_unk354 & 0x2000u) != 0 && static_cast<uint32_t>(relative - 6) <= 1u) {
            const int8_t sound = CKGrpS08Hero::GetMovementEventSound(0xa);
            if (sound != -1) play(sound, 0, false, true);
        }
    }
    if ((m_unk354 & 0x2000u) != 0 && m_unk118 != 0xff) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(0xb);
        if (sound != -1) play(sound, static_cast<int8_t>(m_unk118), false, false);
        const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        if (((draw * 100u) >> 16) < m_unk34f) {
            const int8_t variant = CKGrpS08Hero::GetMovementEventSound(0xc);
            if (variant != -1) play(variant, static_cast<int32_t>((static_cast<uint32_t>(Rand_Int()) >> 15) & 1u), false, false);
        }
    }
    if ((m_unk364 & 0x2000000u) != 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(0xd);
        if (sound != -1) play(sound, static_cast<int32_t>((static_cast<uint32_t>(Rand_Int()) >> 15) & 1u), false, false);
    }
    if ((m_unk364 & 0x80000u) != 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(0xe);
        if (sound != -1) play(sound, 0, false, false);
    }
    if (m_unkd0 == 2 && (m_unk354 & 4u) != 0 && (m_unk360 & 0x2000u) == 0) {
        const int8_t sound = CKGrpS08Hero::GetMovementEventSound(0xf);
        if (sound != -1) play(sound, 0, false, false);
    }
}

namespace {
// The footstep particle index of `kind` for `hero` (CKGrpS08Hero vt+0x154 0x2ce428: the signed byte [hero][kind] of the
// two 8-byte tables the pointers at 0x00b01020 name, 0x00ceadc8 / 0x00ceadd0: zero-filled data that nothing writes, so
// every kind gives particle 0; -1 would be none).
int8_t FootstepParticleIndex(uint8_t /*hero*/, uint8_t /*kind*/) { return 0; }

// A footstep particle node put at `at` (its frame's modelling position, the frame dirtied) and started: shown (bit 9),
// emitting (bit 10), not pending (bit 19), the emission speed adjustment 0, its emitter's flags 0xa set.
void PlaceAndStartParticleNode(IKSerializable* object, const CVector3& at) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = at.z;
    frame->modelling.pos.x = at.x;
    frame->modelling.pos.y = at.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    node->m_sgProperties = (node->m_sgProperties | 0x600u) & 0xfff7ffffu;
    node->m_fEmissionSpeedAdjustment = 0.0f;
    node->m_pRpPrtStdEmitter->flag |= 0xau;
}
}  // namespace

// 0x00366ba8 CKHkS08Hero_UpdateFootstepFx_maybe: with the surface +0x16c's footstep FX on (the group's vt+0x160 entry),
// a foot down (+0x354 bit 27: hot spot +0x16f, else bit 28: +0x170) starts the kind 0 particles (+0x50, index + +0x16c)
// at that foot; +0x360 bit 22 / 23 (hot spots +0x171 / +0x172, the second when bit 23 with +0x35c bit 26 or bit 22
// without it) the kind 1 particles; +0x360 bit 24 the kind 2 particles at the point +0x858. No rand.
void CKHkS08Hero::UpdateFootstepFx(IKTime*) {
    IKSerializable** particles = m_apParticles;  // +0x50
    if (*CKGrpS08Hero::GetSurfaceEntry(m_unk16c) != 0) {  // vt+0x160 0x002ce468
        const uint8_t left = m_unk16f;
        const uint8_t right = m_unk170;
        if (((m_unk354 & 0x08000000u) != 0 && left != 0xff) || ((m_unk354 & 0x10000000u) != 0 && right != 0xff)) {
            const int8_t index = FootstepParticleIndex(m_ui8Hero, 0);  // vt+0x154
            if (index != -1) {
                const int8_t foot = static_cast<int8_t>((m_unk354 & 0x08000000u) != 0 ? left : right);
                CVector3 at;
                static_cast<CSGHotSpot*>(m_apHotSpots[foot])->GetWorldPosition(&at);  // 0x000ce790
                IKSerializable* node = particles[static_cast<int8_t>(index + m_unk16c)];
                if (node != nullptr) PlaceAndStartParticleNode(node, at);
            }
        }
    }
    const uint8_t first = m_unk171;
    const uint8_t second = m_unk172;
    if (((m_unk360 & 0x00400000u) != 0 && first != 0xff) || ((m_unk360 & 0x00800000u) != 0 && second != 0xff)) {
        const int8_t index = FootstepParticleIndex(m_ui8Hero, 1);  // vt+0x154
        if (index != -1) {
            const bool flag26 = (m_unk35c & 0x04000000u) != 0;
            const bool useSecond = ((m_unk360 & 0x00800000u) != 0 && flag26) || ((m_unk360 & 0x00400000u) != 0 && !flag26);
            CVector3 at;
            static_cast<CSGHotSpot*>(m_apHotSpots[static_cast<int8_t>(useSecond ? second : first)])->GetWorldPosition(&at);
            IKSerializable* node = particles[index];
            if (node != nullptr) PlaceAndStartParticleNode(node, at);
        }
    }
    if ((m_unk360 & 0x01000000u) == 0) return;
    const int8_t index = FootstepParticleIndex(m_ui8Hero, 2);  // vt+0x154
    if (index == -1) return;
    IKSerializable* node = particles[index];
    if (node == nullptr) return;
    const CVector3 at = {m_unk858, m_unk85c, m_unk860};
    PlaceAndStartParticleNode(node, at);
}

// 0x003670f8 CKHkS08Hero_UpdateMainShadowAndSurfaceFx_maybe: the main shadow caster registered (and its ground point
// updated) unless +0x358 bit 23, +0x364 bit 2 or +0x35c bit 3 (then unregistered); the water splash and wave FX; the
// timer +0x880 against the limit +0x884 (+0x364 bits 0 / 1, the rate +0x2e8; -1000 off) with its HUD gauge.
void CKHkS08Hero::UpdateMainShadowAndSurfaceFx(IKTime* clock) {
    CKSrvShadow* shadows = static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow);
    CKShadowGround* caster = reinterpret_cast<CKShadowGround*>(&m_unk64);
    uint32_t flags = m_unk358;
    if ((flags & 0x800000u) != 0 || (m_unk364 & 4u) != 0 || (m_unk35c & 8u) != 0) {
        if (m_unk81 != 0) shadows->UnregisterCaster(caster, m_pShadowCpnt);  // 0x001fd6f0
    } else {
        if (m_unk81 == 0) shadows->RegisterCaster(m_pShadowCpnt, m_pKGLObject, caster, 0, nullptr, 0);  // 0x001fb6f8
        UpdateShadowGroundPoint();  // 0x00365c00
    }
    flags = m_unk358;
    // The water surface point: the hero's position, at the water level (+0x40) of a ground of engine flag 1.
    CVector3 surface = {m_unk54c, m_unk550, m_unk554};
    const CGround* ground = static_cast<const CGround*>(m_gcCurDatasInOut.m_pGround);  // +0x4b8
    if (ground != nullptr && (ground->m_ba16EngineFlags & 2u) != 0) surface.y = ground->m_fPropertieValue;
    // A splash on +0x358 bit 9, or on +0x35c bit 13 with +0x354 bit 0.
    const bool splash = (flags & 0x200u) != 0 || ((m_unk35c & 0x2000u) != 0 && (m_unk354 & 1u) != 0);
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (splash) {
        // A CKWaterSplashNodeFx of the data +0x8c (the reserving pool lookup inlined: CKSrvFx::AcquireFx; none when the
        // level has no free one) triggered at `surface` (0x56f7a0), then its reservation released (vt+0x54).
        IKFx* fx = fxService->AcquireFx(static_cast<IKFxData*>(m_pWaterSplashFxData), this);
        if (fx != nullptr) {
            static_cast<CKWaterSplashNodeFx*>(fx)->TriggerAt(&surface, this);  // 0x0056f7a0
            fx->ReleaseReservation(this);  // vt+0x54
        }
    }
    // The wave while +0x35c bit 9 (when +0x35c bit 8 decides) or +0x358 bit 8.
    const bool wave = (m_unk35c & 0x100u) != 0 ? (m_unk35c & 0x200u) != 0 : (m_unk358 & 0x100u) != 0;
    if (wave) {
        // The CKWaterWaveNodeFx +0x88, taken from the pool of the data +0x84 (reserved) when there is none, placed at
        // `surface` (0x570068); +0x88 stays null when no effect is free.
        if (m_unk88 == nullptr) m_unk88 = fxService->AcquireFx(static_cast<IKFxData*>(m_pWaterWaveFxData), this);
        if (m_unk88 != nullptr) static_cast<CKWaterWaveNodeFx*>(m_unk88)->SetPositionIfOwner(&surface, this);
    } else if (m_unk88 != nullptr) {
        static_cast<CKWaterWaveNodeFx*>(m_unk88)->StopIfOwnedBy(this);  // 0x00570498
        m_unk88->ReleaseReservation(this);  // vt+0x54
        m_unk88 = nullptr;
    }
    const float limit = m_unk884;
    if (limit == 0.0f) return;  // TOC +0x2dbc
    if (m_unk880 == -1000.0f) return;  // TOC +0x2db4
    const float time = clock->m_afCurrentTime[0];  // +0x04
    const float dt = clock->m_afDeltaTime[0];
    if ((m_unk354 & 1u) == 0 && (m_unk358 & 1u) == 0) m_unk364 |= 1u;
    const uint32_t state = m_unk364;
    if ((state & 2u) != 0) m_unk880 = dt + m_unk880;
    float left = (m_unk884 - time) + m_unk880;
    if (left < 0.0f) left = 0.0f;
    if ((state & 1u) != 0) {
        const float full = m_unk884;
        if (m_unk2e8 == 0.0f) {
            left = full;
        } else {
            left = ppc::fmadds(dt, full / m_unk2e8, left + dt);
            if (!(full >= left)) left = full;  // bge
        }
        m_unk880 = (left + time) - full;
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (left == m_unk884 && (state & 1u) != 0) {
        manager->Vf2C4(0, m_ui8Hero);  // vt+0x2c4 (empty in CKS08GameManager)
        m_unk880 = -1000.0f;
        m_unk364 &= 0xfffffffeu;
    } else {
        manager->Vf2C0(0, m_ui8Hero);        // vt+0x2c0 (empty)
        manager->Vf2C8(left, 0, m_ui8Hero);  // vt+0x2c8 (empty)
    }
}

// 0x0036b1a0 CKHkS08Hero_ConstrainMovementToNavigation_maybe: the target kept on the walkable navigation. +0x358 bit 7
// clears. A hero free of the navigation (the player's, unless +0x364 bit 23 or +0x358 bit 29; an AI under +0x35c bit 15 or
// +0x364 bit 14; +0x354 bit 31, +0x364 bit 10, +0x35c bit 22) only gets its path destination (unless +0x368 bit 13) and
// +0x358 bit 17; an AI with the path flag 0x40 (+0x3b0) clears bit 17. Otherwise (the AI on its path) the target is
// put in a navigation sector (the nearest one without a sector, the path destination's node unless a transition to
// the point's node lets it through), clamped into its node box and, when not walkable, into the nearest open cell
// with the character's clearance; a changed target is put on the ground (+0x358 bit 7) and `move` recomputed. A
// destination that left the navigation (bit 17 from the last frame) asks for a warp to the waypoint (+0x3c4).
void CKHkS08Hero::ConstrainMovementToNavigation(IKTime* clock, CVector3* move, CVector3* target) {
    const uint32_t flags = m_unk358 & 0xffffff7fu;
    m_unk358 = flags;
    bool free = false;
    bool held = false;
    if (m_ui8Hero == m_ui8TrackedLeader) {
        if ((m_unk364 & 0x800000u) == 0) free = ((m_unk358 >> 29) & 1u) == 0;
    } else if ((m_unk35c & 0x8000u) != 0 || (m_unk364 & 0x4000u) != 0) {
        held = true;
    }
    if (static_cast<int32_t>(m_unk354) < 0 || (m_unk364 & 0x400u) != 0 || free || held || (m_unk35c & 0x400000u) != 0) {
        if ((m_unk368 & 0x2000u) == 0) m_PFCpnt.SetDestination(target);  // 0x001e3a40
        m_unk358 = (m_unk358 & 0xfffdffffu) | 0x20000u;
        return;
    }
    if ((m_unk3b0 & 0x40u) != 0) {
        m_unk358 = flags & 0xfffdffffu;
        return;
    }
    CKSrvPathFinding* const service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint& destination = m_PFCpnt.m_Destination;  // +0x430
    bool checkWarp = true;
    if ((m_unk358 & 0x20000u) != 0 && PointInNodeBox(service, destination.m_position, destination.m_unk0c) &&
        static_cast<uint8_t>(service->IsPointWalkable(&destination, &m_PFCharacter)) != 0) {  // 0x001e42d0
        checkWarp = false;
    }
    if ((m_unk358 & 0x20000u) == 0) checkWarp = false;
    if (checkWarp) {
        bool warp = false;
        if ((m_unk354 & 0x40000u) == 0) {
            if ((m_unk354 & 0x10u) != 0 || (m_unk35c & 1u) != 0 || (m_unk360 & 0x4000000u) != 0) {
                warp = true;
            } else {
                if (static_cast<int16_t>(destination.m_unk0c) != -1) return;
                if (m_unk3c8 > m_unk550) return;
                warp = true;
            }
        } else if ((m_unk354 & 0x10u) != 0 || (m_unk35c & 1u) != 0 || (m_unk360 & 0x4000000u) != 0) {
            warp = true;
        } else if (m_aui8Unk1a4[0x1a6 - 0x1a4] != 0) {
            // The way back swept against the walls from the position (raised by +0x288) along the last move (+0x5d8).
            CLine line;
            line.m_start.x = m_unk54c;
            line.m_start.y = m_unk550 + m_unk288;
            line.m_start.z = m_unk554;
            line.m_VectDir.x = m_unk5d8;
            line.m_VectDir.y = m_unk5dc;
            line.m_VectDir.z = m_unk5e0;
            CSlideGroundEdgeDatasOut slide;
            CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
            if (collision->ResolveSweptCylinderWalls(&line, m_unk218, m_unk510, &slide, nullptr, nullptr, 1) == 0) {  // 0x0019aa68
                if ((m_unk354 & 1u) == 0) Vf178(clock, 1);  // vt+0x178
                return;
            }
            const float zero = 0.0f;  // TOC +0x2e88
            float x = slide.m_v3BouncingVector.x;
            float z = slide.m_v3BouncingVector.z;
            float y = zero;
            const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, zero))));
            if (length != zero) {
                const float inverse = 1.0f / length;  // TOC +0x2ecc
                z = z * inverse;
                x = x * inverse;
                y = inverse * zero;
            }
            // The original takes cosf(-3 pi / 4) when the TOC word +0x2f18 (0x4016cbe4) is negative; it is not.
            const float dot = ppc::fmadds(z, m_unk3c0, ppc::fmadds(x, m_unk3b8, y * m_unk3bc));
            if (dot <= -7.07106709e-1f && (m_unk358 & 0x10000u) == 0) {  // TOC +0x2f1c; cror lt|eq
                warp = true;
            } else if ((m_unk354 & 0x200000u) != 0) {
                warp = true;
            } else {
                return;
            }
        }
        if (warp && (m_unk3b0 & 2u) != 0) {
            TeleportTo(reinterpret_cast<const CVector3*>(&m_unk3c4), reinterpret_cast<const CVector3*>(&m_unk540),
                       static_cast<uint8_t>(((m_unk358 ^ 8u) >> 3) & 1u), 1, 0xffff, 0);  // 0x0036a578
        }
    }
    // The target on the navigation.
    CPFPoint point;
    point.m_position = *target;
    point.m_unk0c = destination.m_unk0c;
    uint8_t changed = 0;
    if (static_cast<int16_t>(point.m_unk0c) == -1) {
        point = service->ClampToNearestSector(&point);  // 0x001e5680
        changed = 1;
    }
    service->FindSectorForPoint(&point);  // 0x001e5ca0
    const uint16_t destinationNode = destination.m_unk0c;
    if (static_cast<int16_t>(destinationNode) != -1) {
        const uint16_t pointNode = point.m_unk0c;
        bool keep = false;
        if (static_cast<int16_t>(pointNode) != -1 && static_cast<int16_t>(destinationNode) != static_cast<int16_t>(pointNode)) {
            const CKPFGraphTransition* transition = service->GetTransitionBetween(pointNode, destinationNode);  // 0x001e3e28
            if (transition != nullptr && (transition->m_baFlags & 1u) == 0 &&
                transition->AllowsCharacter(&m_PFCharacter) != 0 && (transition->m_baFlags & 4u) != 0) {  // 0x001f0648
                keep = true;
            }
        }
        if (!keep) point.m_unk0c = destinationNode;
    }
    if (service->ClampPointToSector(&point) == 0) changed = 1;  // 0x001e4f70
    if (static_cast<uint8_t>(service->IsPointWalkable(&point, &m_PFCharacter)) == 0) {  // 0x001e42d0
        CKPFGraphNode* node = static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[point.m_unk0c]);
        PathFinding_SetWalkabilityMode(m_PFCharacter.m_bits & 7u);  // 0x001f1158
        node->m_Sector.m_grid.m_ui8DynamicMask = (m_PFCharacter.m_bits & 0x800u) != 0 ? 0xff : 0xf7;
        CVector3 open;
        if (node->m_Sector.ClampPointWithClearance(m_PFCharacter.m_unk04, &point.m_position, &open) != 0) {  // 0x001ee190
            point.m_position = open;
        }
    } else if (changed == 0) {
        m_unk358 &= 0xfffdffffu;
        return;
    }
    m_unk358 = (m_unk358 & 0xffffff7fu) | 0x80u;
    CVector3 ground;
    ProbeNavPointGround(this, service, point.m_position.x, point.m_position.z, point.m_unk0c, &ground);
    ground.y = ground.y - 0.01f;  // TOC +0x2e9c
    if ((m_unk354 & 1u) == 0 && (m_unk35c & 0x100u) == 0) {
        *target = ground;
    } else {
        // Airborne (or +0x35c bit 8): the target keeps its height when that is still a walkable point of the node.
        const CVector3 kept{ground.x, target->y, ground.z};
        point.m_position = kept;
        if (PointInNodeBox(service, kept, point.m_unk0c) &&
            static_cast<uint8_t>(service->IsPointWalkable(&point, &m_PFCharacter)) != 0) {
            *target = kept;
        } else {
            *target = ground;
        }
    }
    move->x = target->x - m_unk54c;
    move->z = target->z - m_unk554;
    move->y = target->y - m_unk550;
    m_unk358 &= 0xfffdffffu;
}

// 0x00369da0 IKHkHero_HasNonZeroSpeed530Or534_maybe: a horizontal or vertical speed that is not 0.
uint8_t CKHkS08Hero::HasNonZeroSpeed530Or534() {
    if (m_unk530 == 0.0f) return m_unk534 != 0.0f ? 1 : 0;
    return 1;
}

// 0x0036bbf8 IKHkHero_InitMoveRequestFromSourcePoint_maybe: a push away from `source` with the speeds `speeds` (0
// horizontal, 1 vertical, 2 the duration factor): none when both speeds are 0. +0x354 bit 24; the flat direction from
// the source (+0x660, y 0, normalised when not 0) into +0x66c, the speeds into +0x530 / +0x534, +0x678 the factor times
// +0x318, +0x67c the word +0x33c; the push's facing +0x66c turned back (mode 1 always, mode 0 when the direction points
// against the facing +0x540), +0x680 and +0x358 bit 28 cleared; with a vertical speed the camera direction locked
// (0x354cf0), +0x354 bit 0 set and bit 2 cleared (then, bit 0 being set, bit 9), and with `savePosition` the position kept
// in +0x474 and +0x368 bit 1 = the model drawn this frame.
void CKHkS08Hero::InitMoveRequestFromSourcePoint(const float* speeds, const CVector3* source, int32_t mode,
                                                 int32_t savePosition) {
    const float zero = 0.0f;  // TOC +0x2e88
    if (speeds[0] == zero && speeds[1] == zero) return;
    m_unk354 = (m_unk354 & ~0x01000000u) | 0x01000000u;
    const float dx = m_unk54c - source->x;
    const float dy = m_unk550 - source->y;
    const float dz = m_unk554 - source->z;
    m_unk660 = dx;
    m_unk664 = dy;
    m_unk664 = zero;
    const float yy = m_unk664 * m_unk664;
    m_unk668 = dz;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, yy)));  // 0x00010690
    if (length != zero) {
        const float inv = 1.0f / length;  // TOC +0x2ecc
        const float x = m_unk660;
        const float y = m_unk664;
        const float z = m_unk668;
        m_unk668 = inv * z;
        m_unk660 = inv * x;
        m_unk664 = inv * y;
    }
    m_unk530 = speeds[0];
    m_unk534 = speeds[1];
    m_unk678 = speeds[2] * m_unk318;
    m_unk67c = static_cast<float>(static_cast<double>(m_unk33c));
    const float fx = m_unk660;
    const float fy = m_unk664;
    const float fz = m_unk668;
    m_unk66c = fx;
    m_unk670 = fy;
    m_unk674 = fz;
    bool turn = mode == 1;
    if (!turn && mode == 0) {
        const float dot = ppc::fmadds(fz, m_unk548, ppc::fmadds(fx, m_unk540, fy * m_unk544));
        turn = dot < zero;  // bge: a NaN keeps the direction
    }
    if (turn) {
        m_unk66c = -fx;
        m_unk670 = -fy;
        m_unk674 = -fz;
    }
    m_unk680 = 0;
    m_unk358 &= ~0x10000000u;
    if (m_unk534 == zero) return;
    SetCameraDirectionLock(1);  // 0x00354cf0
    m_unk354 = ((m_unk354 & ~1u) | 1u) & ~4u;
    if ((m_unk354 & 1u) != 0) m_unk354 = (m_unk354 & ~0x200u) | 0x200u;
    if (savePosition == 0) return;
    m_unk474 = m_unk54c;
    m_unk47c = m_unk554;
    m_unk478 = m_unk550;
    const CSGLeaf* node = static_cast<const CSGLeaf*>(m_pKGLObject);
    // ((stamp ^ frame) - 1) >> 30 & 2: bit 1 set when the model was drawn this frame (TOC +0x2ec0: 0x00c29694).
    const uint32_t drawn = ((static_cast<uint32_t>(node->m_ui16LastRenderedFrame ^ g_ui16RenderFrameCounter) - 1u) >> 30) & 2u;
    m_unk368 = (m_unk368 & ~2u) | drawn;
}

// 0x0036ac88 CKHkS08Hero_TeleportToSavedPosition_maybe: with more than one controlled hero (GetControlledHeroCount
// 0x2ca288: the group's +0x50), a hero its own player controls (+0x25 == +0x24) and without +0x368 bit 1 goes back to its
// saved position +0x474 facing +0x540 (keeping its ground, no navigation check, no sector): 1; else 0.
uint8_t CKHkS08Hero::TeleportToSavedPosition() {
    const uint8_t controlled = static_cast<IKGrpHero*>(m_pGrpHero)->m_ui8ControlledHeroCount;  // 0x002ca288
    if (controlled <= 1 || m_ui8Hero != m_ui8TrackedLeader) return 0;
    if ((m_unk368 & 2u) != 0) return 0;
    TeleportTo(reinterpret_cast<const CVector3*>(&m_unk474), reinterpret_cast<const CVector3*>(&m_unk540), 1, 0, 0xffff,
               0);  // 0x0036a578
    return 1;
}

// 0x0036a260 CKHkS08Hero_RequestOwnDragonSelectionIfMultiHero_maybe: with more than one controlled hero, a hero its own
// player controls (+0x25 == +0x24) asks the group for itself (RequestDragonSelection 0x2cbb08 from the group's +0x66,
// immediate, applied) unless the group's +0x66 is that player already.
void CKHkS08Hero::RequestOwnDragonSelectionIfMultiHero() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const uint8_t controlled = group->m_ui8ControlledHeroCount;  // 0x002ca288
    const uint8_t current = group->m_unk66;
    if (controlled <= 1) return;
    if (m_ui8TrackedLeader != m_ui8Hero || current == m_ui8TrackedLeader) return;
    group->RequestDragonSelection(current, m_ui8Hero, 0, 0, 1, 1, 0);  // 0x002cbb08
}

// 0x00369f40 IKHkHero_GetNavTransitionFlag2_IfAllowed_maybe: for two different valid graph nodes, bit 2 of the flags
// of the transition from `from` to `to` when it exists, is enabled (bit 0 clear) and lets the hero's character
// (+0x3e0) through; else 0.
uint32_t CKHkS08Hero::GetNavTransitionFlag2IfAllowed(int16_t from, int16_t to) {
    if (from == -1 || to == -1 || from == to) return 0;
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    const CKPFGraphTransition* transition =
        service->GetTransitionBetween(static_cast<uint16_t>(from), static_cast<uint16_t>(to));  // 0x001e3e28
    if (transition == nullptr) return 0;
    if ((transition->m_baFlags & 1u) != 0) return 0;
    if (transition->AllowsCharacter(&m_PFCharacter) == 0) return 0;  // 0x001f0648
    return (transition->m_baFlags >> 2) & 1u;
}

// 0x0036a2f8 CKHkS08Hero_ValidateNavPosition_maybe: whether the hero may stand at the nav point: its sector found
// (and, with `sameSector`, unchanged), inside that graph node's box, walkable for `character`, put on the ground
// (GroundContact_SnapNavPoint into `contact`), and that ground not of a property the group forbids (properties
// +0xf4); on a ground of engine flag 1 (bit 0x2) below its height (CGround +0x40) the point is raised to it.
// `raised` (when given) tells whether it was.
uint8_t CKHkS08Hero::ValidateNavPosition(CGroundContactDatasInOut* contact, CPFPoint* point,
                                         const CPFCharacter* character, int32_t sameSector, uint8_t* raised) {
    const uint16_t before = point->m_unk0c;
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    if (static_cast<uint8_t>(service->FindSectorForPoint(point)) == 0) return 0;  // 0x001e5ca0
    if (sameSector != 0 && static_cast<int32_t>(before) != static_cast<int32_t>(static_cast<int16_t>(point->m_unk0c))) {
        return 0;
    }
    const int32_t sector = static_cast<int16_t>(point->m_unk0c);
    if (sector < 0) return 0;
    if (static_cast<uint32_t>(sector) >= service->m_Graph.m_ui32GraphNodesSize) return 0;
    const CBBox& box =
        static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[point->m_unk0c])->m_Sector.m_box;
    const float x = point->m_position.x;
    if (!(box.m_inf.x <= x) || !(box.m_sup.x >= x)) return 0;
    const float z = point->m_position.z;
    if (!(box.m_inf.z <= z) || !(box.m_sup.z >= z)) return 0;
    const float y = point->m_position.y;
    if (!(box.m_inf.y <= y) || !(box.m_sup.y >= y)) return 0;
    if (static_cast<uint8_t>(service->IsPointWalkable(point, character)) == 0) return 0;  // 0x001e42d0
    // The original also passes &m_PFCharacter and +0x358 bit 2, which GroundContact_SnapNavPoint does not read.
    if (static_cast<uint8_t>(GroundContact_SnapNavPoint(contact, point)) == 0) return 0;  // 0x005843f0
    const CGround* ground = static_cast<const CGround*>(contact->m_pGround);
    const IKGrpHero* group = static_cast<const IKGrpHero*>(m_pGrpHero);
    // +0xf4: m_sProperties' third half-word (IKGrpHero +0xc0 + 0x34).
    if ((ground->m_ui16PropertiesFlags & group->m_sProperties.m_aui16Values[2]) != 0) return 0;
    if ((ground->m_ba16EngineFlags & 2u) != 0 && !(point->m_position.y >= ground->m_fPropertieValue)) {
        point->m_position.y = ground->m_fPropertieValue;
        if (raised != nullptr) *raised = 1;
        return 1;
    }
    if (raised != nullptr) *raised = 0;
    return 1;
}

// ---- step 4 AI: the partner's follow and catch-up helpers. ----

// The speed mode the AI steering reads (inlined three times in 0x0036c160 and 0x0036c6a0): the last enabled, unlocked
// mode whose speed of the current class (+0x58c) is at most 1000, or the first enabled one (TOC +0x2f24).
const SHeroSpeedMode* CKHkS08Hero::AISelectSpeedModeUpTo1000() {
    const uint8_t count = CKGrpS08Hero::GetNbSpeedModesOf(m_ui8Hero);  // vt+0x11c
    uint32_t selected = 0;
    for (uint32_t i = 0; i < count; ++i) {
        const SHeroSpeedMode& mode = m_asSpeedModes[i];
        if (mode.m_bEnable == 0 || mode.m_bLocked != 0) continue;
        if (mode.m_afHSpeeds[m_unk58c] <= 1000.0f || (selected & 0xffu) == 0) selected = i;  // cror lt|eq
    }
    return &m_asSpeedModes[selected & 0xffu];
}

// 0x0036a578 CKHkS08Hero_TeleportTo_maybe: the hero put at `position` facing `facing`. Not while held (+0x368 bit 12).
// A hero the camera sees (its sphere of radius 1.4 in the frustum) asks for a catch-up point instead (vt+0x168) unless
// +0x35c bit 17 forces the warp. With `checkNav` the point must be a valid navigation position (its contact taken);
// else the contacts are reset. `leaveAttached` leaves the object the hero holds. The position, facing (+0x540) and
// yaw (+0x538), the speeds, the saved position (+0x474), the drawn flag (+0x368 bit 1), the bounding spheres, the
// detectors' old positions and (for the AI) the path destination follow; the moves and the move flags are cleared,
// and without `keepLocomotion` the locomotion machine (+0x528 / +0x52c) leaves its state. +0x358 bit 15 marks it.
uint8_t CKHkS08Hero::TeleportTo(const CVector3* position, const CVector3* facing, uint8_t leaveAttached,
                                uint8_t checkNav, uint16_t sector, uint8_t keepLocomotion) {
    if ((m_unk368 & 0x1000u) != 0) return 0;
    const float sphere[5] = {position->x, position->y, position->z, 1.39999998f, 1.95999992f};  // TOC +0x2eb8, +0x2ebc
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (camera->TestSphereAgainstFrustum(sphere, 5) != 0 && (m_unk35c & 0x20000u) == 0) {  // 0x0012c830
        Vf168();  // vt+0x168
        return 1;
    }
    CGroundContactDatasInOut contact;  // ground 0, face -1, status 3, sector 0
    CPFPoint point;
    point.m_unk0c = 0xffff;
    if (checkNav != 0) {
        CopyGroundContact(contact, m_gcCurDatasInOut);
        point.m_position = *position;
        point.m_unk0c = sector;
        if (ValidateNavPosition(&contact, &point, &m_PFCharacter, 0, nullptr) == 0) return 0;  // 0x0036a2f8
    }
    if (leaveAttached != 0) LeaveAttachedObject();  // 0x00344e88
    CVector3 delta;
    if (checkNav != 0) {
        delta.x = point.m_position.x - m_unk54c;
        delta.y = point.m_position.y - m_unk550;
        delta.z = point.m_position.z - m_unk554;
        m_unk54c = point.m_position.x;
        m_unk550 = point.m_position.y;
        m_unk554 = point.m_position.z;
        CopyGroundContact(m_gcCurDatasInOut, contact);
        CopyGroundContact(m_gcOldDatasInOut, contact);
    } else {
        delta.x = position->x - m_unk54c;
        delta.y = position->y - m_unk550;
        delta.z = position->z - m_unk554;
        m_unk54c = position->x;
        m_unk550 = position->y;
        m_unk554 = position->z;
        m_gcCurDatasInOut.m_pGround = nullptr;
        m_gcOldDatasInOut.m_pGround = nullptr;
        m_gcCurDatasInOut.m_ui8SectorNumber = 0;
        m_gcCurDatasInOut.m_i32FaceIndex = -1;
        m_gcCurDatasInOut.m_eContactStatus = 3;
        m_gcOldDatasInOut.m_ui8SectorNumber = 0;
        m_gcOldDatasInOut.m_i32FaceIndex = -1;
        m_gcOldDatasInOut.m_eContactStatus = 3;
    }
    m_unk540 = facing->x;
    m_unk544 = facing->y;
    m_unk548 = facing->z;
    m_unk538 = Vec3_GetYawAngleFromX(reinterpret_cast<const CVector3*>(&m_unk540));  // 0x00244638
    m_unk534 = 0.0f;  // stw 0
    m_unk530 = 0.0f;
    m_unk474 = m_unk54c;
    m_unk478 = m_unk550;
    m_unk47c = m_unk554;
    const uint32_t drawn = static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter ? 2u : 0u;
    m_unk368 = (m_unk368 & 0xfffffffcu) | drawn;
    ResetBoundingSpheresAtDeltaPos(&delta);  // 0x00352c38
    CKSrvDetect* detect = static_cast<CKSrvDetect*>(g_pEngine->m_srvDetect);
    const IKGrpHero* group = static_cast<const IKGrpHero*>(m_pGrpHero);
    IKSerializable** const lists[3] = {group->m_apUnk44, group->m_apUnk48, group->m_apUnk4c};
    for (IKSerializable** list : lists) {
        const uint32_t count = detect->m_ui32NbDetectedMovable;
        if (count == 0) break;
        const IKSerializable* movable = list[m_ui8Hero];
        for (uint32_t i = 0; i < count; ++i) {
            static_cast<CKDetectedMovable*>(detect->m_apDetectedMovable[i])->SetDetectablePosition(movable, &m_unk54c);  // 0x001ab008
        }
    }
    if (m_ui8Hero != m_ui8TrackedLeader) m_PFCpnt.SetDestination(reinterpret_cast<const CVector3*>(&m_unk54c));  // 0x001e3a40
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2ec4 -> 0x00c50d64
    m_unk5e4 = zero.x;
    m_unk5ec = zero.z;
    m_unk5e8 = zero.y;
    m_unk5f0 = zero.x;
    m_unk5f8 = zero.z;
    m_unk5f4 = zero.y;
    m_unk5fc = zero.x;
    m_unk604 = zero.z;
    m_unk600 = zero.y;
    m_unk354 &= 0xfffbffffu;
    m_unk358 &= 0xffffff7fu;
    m_unk354 &= 0xffdfffffu;
    m_unk358 &= 0xfffbffffu;
    m_unk6d1 = 0;
    if (keepLocomotion == 0) {
        if (m_unk52c != 0xff) {
            CallStateHandler(m_unk528[m_unk52c].m_aPtmf, g_pEngine->m_timeManager->m_pTime, 2, 0xff);  // the state's exit
        }
        m_unk52c = 0xff;
    }
    m_unk358 = (m_unk358 & 0xffff7fffu) | 0x8000u;
    return 1;
}

// 0x0036aec0 CKHkS08Hero_ComputeCarriedSidePush_maybe: on a carrying hero (+0x354 bit 21, the contact owner +0x108 a
// hero), the side push +0x5f0: the carrier's move (+0x5b4; when it has none, this hero's move under +0x354 bit 18 or
// +0x358 bit 7, else its facing) turned a quarter turn and pointed away from the carrier, at most +0x28c x dt long.
void CKHkS08Hero::AIComputeFollowVec5F0(IKTime* clock) {
    if ((m_unk354 & 0x200000u) == 0) return;
    if (static_cast<uint8_t>(m_unk108->IsKindOfClass(0x3642)) == 0) return;  // vt+0x08
    const CKHkS08Hero* carrier = static_cast<const CKHkS08Hero*>(m_unk108);
    const float zero = 0.0f;  // TOC +0x2e88
    float ax = m_unk54c - carrier->m_unk54c;
    float az = m_unk554 - carrier->m_unk554;
    float ay = zero;
    const float distance = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(az, az, ppc::fmadds(ax, ax, zero))));
    if (distance != zero) {
        const float inverse = 1.0f / distance;  // TOC +0x2ecc
        az = az * inverse;
        ax = ax * inverse;
        ay = inverse * zero;
    }
    const CVector3& none = kHeroZeroVector;  // TOC +0x2ec4
    CVector3 side;
    float length;
    if (carrier->m_unk5b4 != none.x || carrier->m_unk5b8 != none.y || carrier->m_unk5bc != none.z) {
        side = {carrier->m_unk5b4, carrier->m_unk5b8, carrier->m_unk5bc};
        length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(side.z, side.z, ppc::fmadds(side.x, side.x, side.y * side.y))));
    } else {
        if ((m_unk354 & 0x40000u) != 0 || (m_unk358 & 0x80u) != 0) {
            side = {m_unk5b4, m_unk5b8, m_unk5bc};
        } else {
            side = {m_unk540, m_unk544, m_unk548};
        }
        length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(m_unk5bc, m_unk5bc, ppc::fmadds(m_unk5b4, m_unk5b4, m_unk5b8 * m_unk5b8))));
    }
    float maximum = m_unk28c * clock->m_afDeltaTime[0];
    if (!(length > maximum)) maximum = length;
    Vec3_RotateYawFlatNormalized(1.57079637f, &side);  // TOC +0x2f14; 0x00584e40
    const float dot = ppc::fmadds(az, side.z, ppc::fmadds(side.x, ax, ay * side.y));
    if (dot <= zero) {
        const float scale = -maximum;
        m_unk5f0 = side.x * scale;
        m_unk5f8 = scale * side.z;
        m_unk5f4 = scale * side.y;
        return;
    }
    m_unk5f0 = maximum * side.x;
    m_unk5f8 = maximum * side.z;
    m_unk5f4 = maximum * side.y;
}

// 0x0036c160 CKHkS08Hero_AISteerToWaypoint_maybe: within +0x258 of the end (and with a path), the AI stops (+0x3dc 0)
// with the rest of the way as the side move +0x5f0 and its facing (or `facing` when it stands) as the move vector;
// else it heads for the waypoint at +0x264 when the waypoint is the end within +0x25c, else at the speed mode's
// first speed (`useWalkSpeed`, or drawn without the path flag 0x40 / `useMaxSpeed`) or its maximum. Answers 1 when it
// stopped standing (+0x530 0) and faces `facing` within 0.02.
uint8_t CKHkS08Hero::AISteerToWaypoint(IKTime* clock, const CVector3* waypoint, const CVector3* end,
                                       const CVector3* facing, uint8_t noPath, uint8_t useWalkSpeed,
                                       uint8_t useMaxSpeed) {
    const float zero = 0.0f;  // TOC +0x2e88
    const float ex = m_unk54c - end->x;
    const float ez = m_unk554 - end->z;
    const float toEnd = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, zero))));
    float tx = waypoint->x - m_unk54c;
    float tz = waypoint->z - m_unk554;
    float ty = zero;
    const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, zero))));
    if (length != zero) {
        const float inverse = 1.0f / length;  // TOC +0x2ecc
        tz = tz * inverse;
        tx = tx * inverse;
        ty = inverse * zero;
    }
    uint8_t stopped = 0;
    if (!(m_unk258 <= toEnd) && noPath == 0) {  // ble
        m_unk3dc = zero;
        m_unk5f0 = end->x - m_unk54c;
        m_unk5f8 = end->z - m_unk554;
        m_unk5f4 = zero;
        if (m_unk530 == zero) {
            m_unk3b8 = facing->x;
            m_unk3c0 = facing->z;
            m_unk3bc = facing->y;
        } else {
            m_unk3b8 = m_unk540;
            m_unk3bc = m_unk544;
            m_unk3c0 = m_unk548;
        }
        stopped = 1;
    } else {
        if (m_unk25c > toEnd && waypoint->x == end->x && waypoint->y == end->y && waypoint->z == end->z) {
            m_unk3dc = m_unk264;
        } else {
            bool maxSpeed;
            if (useWalkSpeed != 0) {
                maxSpeed = false;
            } else if ((m_unk3b0 & 0x61u) == 0x40u || useMaxSpeed != 0) {
                maxSpeed = true;
            } else {
                maxSpeed = static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter;
            }
            const SHeroSpeedMode* mode = AISelectSpeedModeUpTo1000();
            m_unk3dc = maxSpeed ? mode->m_fMaxHSpeed : mode->m_afHSpeeds[0];
        }
        m_unk3b8 = tx;
        m_unk3c0 = tz;
        m_unk3bc = ty;
    }
    AIComputeFollowVec5F0(clock);  // 0x0036aec0
    float fx = m_unk540;
    float fz = m_unk548;
    float fy = zero;
    const float facingLength = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(fz, fz, ppc::fmadds(fx, fx, zero))));
    if (facingLength != zero) {
        const float inverse = 1.0f / facingLength;
        fz = fz * inverse;
        fx = fx * inverse;
        fy = inverse * zero;
    }
    if (stopped == 0) return 0;
    if (m_unk530 != zero) return 0;
    return WithinBox(CVector3{fx, fy, fz}, *facing, 1.99999996e-2f);  // TOC +0x2f28
}

// 0x0036c6a0 CKHkS08Hero_AIComputeFollowSteeringAndSpeed_maybe: the follow move vector (+0x3b8) and speed (+0x3dc).
// The speed asked is `speed`, or the speed mode's (first speed while drawn without the path flag 0x40 / with flag 1,
// else its maximum) with `useModeSpeed` or in the air. Near the end (+0x254) a standing hero turns to its facing
// (stopped: 1 when it faces `facing` within 0.02); a moving one slows (+0x260 / +0x264) or follows its facing. Far
// from it the speed ramps from the asked one to the mode's over +0x268 / (speed + 1) of distance.
uint8_t CKHkS08Hero::AIComputeFollowSteeringAndSpeed(float speed, IKTime* clock, const CVector3* waypoint,
                                                     const CVector3* end, const CVector3* facing, uint8_t useModeSpeed) {
    const float zero = 0.0f;  // TOC +0x2e88
    const float ex = m_unk54c - end->x;
    const float ez = m_unk554 - end->z;
    const float toEnd = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, zero))));
    float tx = waypoint->x - m_unk54c;
    float tz = waypoint->z - m_unk554;
    float ty = zero;
    const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, zero))));
    if (length != zero) {
        const float inverse = 1.0f / length;  // TOC +0x2ecc
        tz = tz * inverse;
        tx = tx * inverse;
        ty = inverse * zero;
    }
    bool maxSpeed = static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter;
    if (!maxSpeed && (m_unk3b0 & 0x40u) != 0 && (m_unk3b0 & 1u) == 0) maxSpeed = true;
    const SHeroSpeedMode* mode = AISelectSpeedModeUpTo1000();
    const float modeSpeed = maxSpeed ? mode->m_fMaxHSpeed : mode->m_afHSpeeds[0];
    const float nearRadius = m_unk254;
    float asked;
    bool far;
    if (useModeSpeed != 0 || (m_unk354 & 1u) != 0) {
        asked = modeSpeed;
        far = toEnd >= nearRadius;  // bge
    } else {
        asked = speed;
        far = !(toEnd < nearRadius);  // blt
    }
    if (!far) {
        bool turn = asked == zero || m_unk530 == zero;
        if (turn && (m_unk354 & 1u) != 0) turn = false;
        if (turn) {
            m_unk3dc = zero;
            if (m_unk530 == zero) {
                m_unk3b8 = facing->x;
                m_unk3c0 = facing->z;
                m_unk3bc = facing->y;
            } else {
                m_unk3b8 = m_unk540;
                m_unk3bc = m_unk544;
                m_unk3c0 = m_unk548;
            }
            AIComputeFollowVec5F0(clock);  // 0x0036aec0
            if (m_unk530 != zero) return 0;
            return WithinBox(*reinterpret_cast<const CVector3*>(&m_unk540), *facing, 1.99999996e-2f);  // TOC +0x2f28
        }
        const float dot = ppc::fmadds(tz, m_unk548, ppc::fmadds(tx, m_unk540, ty * m_unk544));
        if (dot < zero) {
            const float slowed = asked - toEnd / clock->m_afDeltaTime[0];
            m_unk3dc = m_unk264 > slowed ? m_unk264 : slowed;
        } else if (nearRadius * 0.5f > toEnd) {  // TOC +0x2f2c
            const float slowed = asked - m_unk260;
            m_unk3dc = !(m_unk264 > slowed) ? slowed : m_unk264;  // ble 0x0036cbf4: a NaN keeps it
        } else {
            m_unk3dc = asked;
            m_unk3b8 = tx;
            m_unk3c0 = tz;
            m_unk3bc = ty;
            AIComputeFollowVec5F0(clock);
            return 0;
        }
        m_unk3b8 = m_unk540;
        m_unk3c0 = m_unk548;
        m_unk3bc = m_unk544;
        AIComputeFollowVec5F0(clock);
        return 0;
    }
    float range = modeSpeed - asked;
    const bool negative = range < zero;
    const float rampDistance = m_unk268 / (asked + 1.0f);  // TOC +0x2ecc
    if (negative) range = zero;
    float result;
    if (negative ? (toEnd < rampDistance) : !(toEnd >= rampDistance)) {
        result = ppc::fmadds(range, toEnd / rampDistance, asked);
        if (modeSpeed < result) result = modeSpeed;
    } else {
        const float one = rampDistance / rampDistance;
        result = ppc::fmadds(range, one, asked);
        if (!(modeSpeed >= result)) result = modeSpeed;
    }
    m_unk3dc = result;
    m_unk3b8 = tx;
    m_unk3c0 = tz;
    m_unk3bc = ty;
    AIComputeFollowVec5F0(clock);
    return 0;
}

// 0x0036cc88 CKHkS08Hero_AIWarpToWaypointOnPathFailure_maybe. With `onPathFailure` (the path query failed while the path flag 0x40
// held): the waypoint (+0x3c4) in its node's box, walkable, is put on the ground and the hero warped there facing
// it; a hero not held by +0x358 bit 30 then keeps its node's offset (+0x468, +0x358 bit 19) and runs vt+0x178 when
// that is beyond +0x308. Without it the original only computes values it does not use (a facing / move cone test
// under +0x354 bits 20 / 21 and the path flag 2): nothing to do.
void CKHkS08Hero::AITeleportIfLost(IKTime* clock, int32_t onPathFailure) {
    if (onPathFailure == 0) return;
    CKSrvPathFinding* const service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint point;
    point.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
    point.m_position = {m_unk3c4, m_unk3c8, m_unk3cc};
    if (static_cast<uint8_t>(service->FindSectorForPoint(&point)) == 0) return;  // 0x001e5ca0
    if (!PointInNodeBox(service, point.m_position, point.m_unk0c)) return;
    if (static_cast<uint8_t>(service->IsPointWalkable(&point, &m_PFCharacter)) == 0) return;  // 0x001e42d0
    CVector3 ground;
    ProbeNavPointGround(this, service, point.m_position.x, point.m_position.z, point.m_unk0c, &ground);
    const float zero = 0.0f;  // TOC +0x2e88
    CVector3 facing;
    facing.x = ground.x - m_unk54c;
    facing.y = zero;
    facing.z = ground.z - m_unk554;
    ground.y = ground.y - 0.01f;  // TOC +0x2e9c
    const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(facing.z, facing.z, ppc::fmadds(facing.x, facing.x, zero))));
    if (length != zero) {
        const float inverse = 1.0f / length;  // TOC +0x2ecc
        facing.z = facing.z * inverse;
        facing.x = facing.x * inverse;
        facing.y = facing.y * inverse;
    }
    const CVector3& none = kHeroZeroVector;  // TOC +0x2ec4
    if (facing.x == none.x && facing.y == none.y && facing.z == none.z) return;
    TeleportTo(&ground, &facing, 0, 0, 0xffff, 0);  // 0x0036a578 (the result is not used)
    if ((m_unk358 & 0x40000000u) != 0) return;
    const RwV3d& node = FrameLtm(static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;  // RwFrame +0x80
    m_unk468 = node.x - m_unk54c;
    m_unk470 = node.z - m_unk554;
    m_unk46c = node.y - m_unk550;
    m_unk358 = (m_unk358 & 0xfff7ffffu) | 0x80000u;
    const float offset = ppc::fmadds(m_unk470, m_unk470, ppc::fmadds(m_unk468, m_unk468, m_unk46c * m_unk46c));
    if (!(m_unk308 * m_unk308 >= offset)) Vf178(clock, 1);  // vt+0x178
}

// 0x0036d210 CKHkS08Hero_AIUpdatePathToTarget_maybe: the path to `target`. In the air the walkability bits of the
// instantaneous character drop with the jumps the hero has left (FindNextEnabledJump); on the ground it is the base
// character. The component's request and update give the result flags (+0x3b0): 2 a waypoint (into `waypoint`; the
// target's ground point or the target itself into `end`; 0x80: the waypoint is the end), 0x40 the path failed (its
// time +0x488; the reachability class decides the AI's jump vt+0x178, the point +0x49c and a warp to the waypoint
// after +0x294 seconds or a blocked climb), 8 a query result. A waypoint inside another hero's end or bounding (the
// group's companions +0x38 and controlled heroes +0x34) or no waypoint: the hero stays (both points its position,
// 1). Else 1 when the path reached its end (flags 0x82).
uint8_t CKHkS08Hero::AIUpdatePathToTarget(IKTime* clock, CVector3* target, CVector3* waypoint, CVector3* end) {
    CPFCharacter& current = m_PFCpnt.m_InstantaneousCharacterType;  // +0x408
    if ((m_unk354 & 1u) == 0) {
        const CPFCharacter& base = m_PFCpnt.m_CharacterType;  // +0x3f8
        if (&current != &base) current.m_bits = base.m_bits;
        current.m_unk0c = base.m_unk0c;
        current.m_unk04 = base.m_unk04;
        current.m_unk08 = base.m_unk08;
    } else {
        int32_t jumps = -1;
        if (m_unk590 != 0xff) {
            int8_t jump = static_cast<int8_t>(m_unk590);
            do {
                ++jumps;
                jump = FindNextEnabledJump(jump);  // 0x00354990
            } while (jump != -1);
            jumps = static_cast<int8_t>(jumps);
        }
        if (jumps <= 2) {
            // rlwinm 21 / rotlwi 11 keep the bits outside 3..10 (mask 0xfffff807), the and keeps the field's others:
            // bits 6, then 5, then 4 cleared.
            uint32_t bits = current.m_bits;
            bits = (bits & 0xfffff807u) | (bits & 0x7b8u);
            if (jumps <= 1) {
                bits = (bits & 0xfffff807u) | (bits & 0x7d8u);
                if (jumps <= 0) bits = (bits & 0xfffff807u) | (bits & 0x7e8u);
            }
            current.m_bits = bits;
        }
    }
    const CVector3* position = reinterpret_cast<const CVector3*>(&m_unk54c);
    m_PFCpnt.RequestPathTo(target, -1);  // 0x001e1520
    const uint32_t result = m_PFCpnt.Update(position);  // 0x001e2b28
    const uint32_t previous = m_unk3b0;
    if ((previous & 0x40u) == 0 && (result & 0x40u) != 0) m_unk488 = clock->m_afCurrentTime[0];
    if ((result & 8u) != 0 && (previous & 0x40u) != 0) AITeleportIfLost(clock, 1);  // 0x0036cc88
    m_unk3b0 = result;
    const CVector3& none = kHeroZeroVector;  // TOC +0x2ec4
    bool stay = true;
    if ((result & 2u) != 0) {
        *waypoint = m_PFCpnt.m_vCurrentTarget;  // +0x418
        const CVector3& goal = m_PFCpnt.m_ptTargetPosition.m_position;  // +0x450
        if (goal.x == target->x && goal.y == target->y && goal.z == target->z) {
            *end = *target;
        } else {
            CKSrvPathFinding* const service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
            ProbeNavPointGround(this, service, goal.x, goal.z, m_PFCpnt.m_ptTargetPosition.m_unk0c, end);
            end->y = end->y - 0.01f;  // TOC +0x2e9c
        }
        if ((m_unk3b0 & 0x80u) != 0) *waypoint = *end;
        stay = false;
        if ((m_unk3b0 & 0x40u) == 0) {
            m_unk49c = none.x;
            m_unk4a4 = none.z;
            m_unk4a0 = none.y;
        } else {
            const uint32_t reach = m_PFCpnt.ClassifyReachability(&m_gcDatasIn);  // 0x001e1be8
            if (reach <= 0x20u) {
                const uint64_t bit = static_cast<uint64_t>(1) << reach;
                bool snap = false;
                if ((bit & 0x114u) != 0) {
                    if ((m_unk354 & 1u) == 0 || (reach != 2 && m_unk534 <= 0.0f)) Vf178(clock, 1);  // vt+0x178
                    snap = true;
                } else if ((bit & 0x100010000ull) != 0) {  // TOC +0x2f30
                    snap = true;
                } else if ((bit & 2u) != 0) {
                    if (m_unk49c == none.x && m_unk4a0 == none.y && m_unk4a4 == none.z) {
                        m_unk49c = m_unk54c;
                        m_unk4a4 = m_unk554;
                        m_unk4a0 = m_unk550;
                    }
                }
                if (snap && m_unk49c == none.x && m_unk4a0 == none.y && m_unk4a4 == none.z) {
                    // The point the hero heads for, put on the ground (the original also passes &m_PFCharacter and
                    // +0x358 bit 2, which GroundContact_SnapNavPoint does not read).
                    CGroundContactDatasInOut contact;
                    CopyGroundContact(contact, m_gcCurDatasInOut);
                    CPFPoint point;
                    point.m_position = *waypoint;
                    point.m_unk0c = m_PFCpnt.m_unk74;
                    if (static_cast<uint8_t>(GroundContact_SnapNavPoint(&contact, &point)) == 0) {  // 0x005843f0
                        m_unk49c = point.m_position.x;
                        m_unk4a4 = point.m_position.z;
                        m_unk4a0 = point.m_position.y;
                    } else {
                        m_unk4a0 = point.m_position.y;
                        m_unk49c = point.m_position.x;
                        m_unk4a4 = point.m_position.z;
                        // ICollisionMesh +0x28: the ground's box (m_AABB[4]).
                        m_unk4a0 = static_cast<const ICollisionMesh*>(contact.m_pGround)->m_AABB[4];
                    }
                }
            }
            if ((m_unk3b0 & 0x80u) == 0) {
                bool late = !(clock->m_afCurrentTime[0] - m_unk488 <= m_unk294);  // ble
                if (reach == 1 || reach == 0x20) {
                    if ((m_unk354 & 1u) != 0) {
                        if (m_unk4a0 - m_unk550 > m_unk250) late = true;
                    } else if ((m_unk35c & 0x10000u) != 0) {
                        // The way to the point +0x49c lines up with the facing.
                        const float zero = 0.0f;  // TOC +0x2e88
                        float dx = m_unk49c - m_unk54c;
                        float dz = m_unk4a4 - m_unk554;
                        float dy = zero;
                        const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zero))));
                        if (length != zero) {
                            const float inverse = 1.0f / length;  // TOC +0x2ecc
                            dz = dz * inverse;
                            dx = dx * inverse;
                            dy = inverse * zero;
                        }
                        late = WithinBox(CVector3{dx, dy, dz}, *reinterpret_cast<const CVector3*>(&m_unk540),
                                         1.99999996e-2f) != 0;  // TOC +0x2f28
                    }
                }
                if (late &&
                    TeleportTo(waypoint, reinterpret_cast<const CVector3*>(&m_unk540), 0, 1, 0xffff, 0) == 0) {  // 0x0036a578
                    m_unk488 = clock->m_afCurrentTime[0];
                }
            }
        }
    }
    bool found = stay;
    if ((m_unk358 & 8u) == 0 && (m_unk3b0 & 0x40u) == 0) {
        const IKGrpHero* group = static_cast<const IKGrpHero*>(m_pGrpHero);
        IKSerializable* const* companions = group->m_apCompanionHeroes;
        const float wx = waypoint->x;
        const float wz = waypoint->z;
        for (; *companions != nullptr && !found; ++companions) {
            const CKHkS08Hero* other = static_cast<const CKHkS08Hero*>(*companions);
            if (other->m_ui8Hero == m_ui8Hero) continue;
            const float r = m_unk27c;
            const float zero = 0.0f;  // TOC +0x2e88
            if (other->m_unk3d0 - r <= wx && other->m_unk3d0 + r >= wx && zero - r <= zero && r + zero >= zero &&
                other->m_unk3d8 - r <= wz) {
                found = wz <= other->m_unk3d8 + r;
            }
        }
    }
    if (!found && (m_unk358 & 8u) == 0 && (m_unk3b0 & 0x40u) == 0) {
        const IKGrpHero* group = static_cast<const IKGrpHero*>(m_pGrpHero);
        IKSerializable* const* controlled = group->m_apControlledHeroes;
        const float wx = waypoint->x;
        const float wz = waypoint->z;
        for (; *controlled != nullptr && !found; ++controlled) {
            const CKHkS08Hero* other = static_cast<const CKHkS08Hero*>(*controlled);
            if (other->m_ui8Hero == m_ui8Hero) continue;
            const float ox = other->m_unk54c;
            const float oz = other->m_unk554;
            const float r = other->GetFloat218() + m_unk218;  // 0x00361c98
            const float zero = 0.0f;  // TOC +0x2e88
            if (ox - r <= wx && ox + r >= wx && zero - r <= zero && r + zero >= zero && oz - r <= wz && oz + r >= wz) {
                found = true;
            }
        }
    }
    if (found) {
        *waypoint = *position;
        *end = *position;
        return 1;
    }
    return (m_unk3b0 & 0x82u) == 0x82u ? 1 : 0;
}

// 0x0036dd08 CKHkS08Hero_AIMoveToTarget_maybe: the path to `target`, the lost check under `lostCheck`, then the steering
// to the waypoint; 1 when the path ended and the hero stopped facing `facing`.
uint8_t CKHkS08Hero::AIMoveToTarget(IKTime* clock, CVector3* target, const CVector3* facing, uint8_t useWalkSpeed,
                                    uint8_t useMaxSpeed, uint8_t lostCheck) {
    const uint8_t arrived = AIUpdatePathToTarget(clock, target, reinterpret_cast<CVector3*>(&m_unk3c4),
                                                 reinterpret_cast<CVector3*>(&m_unk3d0));  // 0x0036d210
    if (lostCheck != 0) AITeleportIfLost(clock, 0);  // 0x0036cc88
    const uint8_t stopped = AISteerToWaypoint(clock, reinterpret_cast<const CVector3*>(&m_unk3c4),
                                              reinterpret_cast<const CVector3*>(&m_unk3d0), facing,
                                              static_cast<uint8_t>(arrived ^ 1u), useWalkSpeed, useMaxSpeed);  // 0x0036c160
    if (arrived == 0) return 0;
    return stopped != 0 ? 1 : 0;
}

// 0x0036de10 CKHkS08Hero_AIUpdateFollowPathAndArrival_maybe: the path to `target`, the lost check, then the follow
// steering (at `speed` toward `facing` while the path has a waypoint, else at 0 toward the hero's own facing); 1 when
// the path ended and the hero stopped facing its way. (`leaderFacing` reaches the steering's unused 7th argument.)
uint8_t CKHkS08Hero::AIUpdateFollowPathAndArrival(float speed, IKTime* clock, CVector3* target, const CVector3* facing,
                                                  const CVector3* leaderFacing, uint8_t useModeSpeed) {
    (void)leaderFacing;
    const uint8_t arrived = AIUpdatePathToTarget(clock, target, reinterpret_cast<CVector3*>(&m_unk3c4),
                                                 reinterpret_cast<CVector3*>(&m_unk3d0));  // 0x0036d210
    AITeleportIfLost(clock, 0);  // 0x0036cc88
    const bool hasWaypoint = (m_unk3b0 & 2u) != 0;
    const uint8_t stopped = AIComputeFollowSteeringAndSpeed(
        hasWaypoint ? speed : 0.0f, clock, reinterpret_cast<const CVector3*>(&m_unk3c4),
        reinterpret_cast<const CVector3*>(&m_unk3d0),
        hasWaypoint ? facing : reinterpret_cast<const CVector3*>(&m_unk540), useModeSpeed);  // 0x0036c6a0
    if (arrived == 0) return 0;
    return stopped != 0 ? 1 : 0;
}

// 0x00368478 CKHkS08Hero_CtlState8_PlayerFollowsFocus: the player's hero while another dragon is focused: the pad is
// read but its move cleared, and the hero walks to the focused dragon (AIMoveToTarget); a failed path asks for the
// pending warp. Entering sets +0x364 bit 23 and +0xb0 2; leaving clears the bit.
uint8_t CKHkS08Hero::CtlPlayerFollowsFocus(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase != 0) {
        if (phase == 1) {
            m_unk364 = (m_unk364 & 0xff7fffffu) | 0x800000u;
            m_unkb0 = 2;
            return 0;
        }
        m_unk364 &= 0xff7fffffu;
        return 0;
    }
    ReadHeroPlayerInput();          // 0x00369670
    ResetMoveInput(1);              // 0x00368de0
    UpdateHeroInputDerivedState();  // 0x00368f18
    const IKGrpHero* group = static_cast<const IKGrpHero*>(m_pGrpHero);
    const uint8_t focused = static_cast<uint8_t>(group->m_unk66);
    if (focused != 0xff) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[focused]);
        AIMoveToTarget(clock, reinterpret_cast<CVector3*>(&hero->m_unk54c), reinterpret_cast<const CVector3*>(&m_unk540),
                       0, 1, 1);  // 0x0036dd08
    }
    if ((m_unk3b0 & 1u) != 0) ProcessPendingTeleport(1, 1);  // 0x0036ad50
    return other;
}

// ---- The lock and unlock (the cinematic actors' SetObjectLocked) ----

namespace {

// 0x001d4698 StopOwnedSparkEffect_maybe: a spark effect reserved by `owner` stops bursting (its spark node's +0x41).
void StopOwnedSparkEffect(IKSerializable* effect, const IKSerializable* owner) {
    CKSparkNodeFx* spark = reinterpret_cast<CKSparkNodeFx*>(effect);
    if ((spark->m_baFxData & 2u) == 0 || spark->m_pOwner != owner) return;
    reinterpret_cast<CSparkNodeFx*>(spark->m_pSparkNode)->m_unk41 = 1;
}

// 0x001d5988 CKTargetCursorNodeFx_StopForOwner_maybe with `immediate` 1 (the only use here): the fade time (+0x20)
// from the data's +0x0c, then stopped (vt+0x6c).
void StopTargetCursorNow(IKSerializable* effect, const IKSerializable* owner) {
    CKTargetCursorNodeFx* cursor = reinterpret_cast<CKTargetCursorNodeFx*>(effect);
    if ((cursor->m_baFxData & 2u) == 0 || cursor->m_pOwner != owner) return;
    cursor->m_fPhaseTime = static_cast<const CKTargetCursorFxData*>(cursor->m_pFxData)->m_unk0c;
    cursor->Stop();
}

// A particle node of the hero's list stops emitting: its scene flag 0x400 (and 0x80000) cleared, its emitter's
// rpPRTSTDEMITTERFLAGEMIT.
void StopParticleNodeEmission(IKSerializable* object) {
    if (object == nullptr) return;
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    if ((node->m_sgProperties & 0x400u) == 0) return;
    node->m_sgProperties &= 0xfff7fbffu;
    node->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
}

}  // namespace

// 0x00348f00 CKHkS08Hero_ExitAllStateMachines_maybe: a carried object told 0x940; the control, action, animation and
// locomotion machines' current states left (phase 2, next 0xff) and cleared; the move input reset, the position put on
// the frame; without a current animation the group's state row D's animation played; the inactive blend layers reset;
// the water wave and the owned effects released.
void CKHkS08Hero::ExitAllStateMachines() {
    if ((m_unk358 & 1u) != 0) GetAttachedObject()->MessageProc(0x940, this);  // vt+0x1c
    IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    if (m_unkAC != 0xff) CallStateHandler(m_unka8[m_unkAC].m_aPtmf, clock, 2, 0xff);
    m_unkAC = 0xff;
    if (m_unkCC != 0xff) CallStateHandler(m_unkc8[m_unkCC].m_aPtmf, clock, 2, 0xff);
    m_unkCC = 0xff;
    if (m_unk14c != 0xff) CallStateHandler(m_unk148[m_unk14c].m_aPtmf, clock, 2, 0xff);
    m_unk14c = 0xff;
    if (m_unk52c != 0xff) CallStateHandler(m_unk528[m_unk52c].m_aPtmf, clock, 2, 0xff);
    m_unk52c = 0xff;
    ResetMoveInput(0);      // 0x00368de0
    ApplyPositionToFrame();  // 0x00355c00
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    const CKBlenderController* blender = static_cast<const CKBlenderController*>(slot->m_pController);
    const CKAnmKeyFrameController* track = static_cast<const CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
    if (track->m_unk5c == 0) {
        const SHeroStateRow* row = static_cast<IKGrpHero*>(m_pGrpHero)->GetHeroStatesD();  // vt+0x13c
        PlayAnimation(0.0f, 0.0f, static_cast<uint16_t>(row->m_key >> 16));  // vt+0x184, TOC1 +0x2acc; the row's +0x10 halfword
    }
    ResetInactiveBlendLayers();  // 0x00351908
    DetachWaterWaveFx();         // 0x00365f30
}

// 0x00365f30 CKHkS08Hero_DetachWaterWaveFx_maybe: the water wave (+0x88) released; the game manager's vt+0x2c4 (empty)
// when +0x880 is set; then ReleaseOwnedFx (vt+0x134).
void CKHkS08Hero::DetachWaterWaveFx() {
    if (m_unk88 != nullptr) {
        static_cast<CKWaterWaveNodeFx*>(m_unk88)->StopIfOwnedBy(this);  // 0x00570498
        m_unk88->ReleaseReservation(this);  // vt+0x54
        m_unk88 = nullptr;
    }
    // m_unk880 != -1000 (TOC1 +0x2db4): CKS08GameManager_vf2C4 0x9c69d8 (0, the dragon) is empty.
    ReleaseOwnedFx();  // vt+0x134
}

// 0x003349a8 CKHkS08Hero_ReleaseOwnedFx (vt+0x134): the hero's effects let go: the sparks (+0x19e0, +0x19e8, +0x19d8)
// stopped bursting and released, the particle nodes 16 / 12 / 13 of its list stop emitting, the objects 0 and 1
// hidden, the effects +0x19b8 / +0x19c0 and the link bolts (+0x19c8 / +0x19d0) stopped and released (vt+0x58), the dust
// (+0x19f4) stopped and released, the target cursor (+0x1a08) stopped at once and released; the group's +0x2d0 cleared.
void CKHkS08Hero::ReleaseOwnedFx() {
    auto releaseSpark = [this](IKSerializable*& slot) {
        if (slot == nullptr) return;
        IKFx* effect = static_cast<IKFx*>(slot);
        StopOwnedSparkEffect(effect, this);  // 0x001d4698
        effect->ReleaseReservation(this);    // vt+0x54
        slot = nullptr;
    };
    auto stopAndRelease = [this](IKSerializable*& slot) {
        if (slot == nullptr) return;
        static_cast<IKFx*>(slot)->StopAndRelease(this);  // vt+0x58
        slot = nullptr;
    };
    releaseSpark(m_unk19e0);
    releaseSpark(m_unk19e8);
    StopParticleNodeEmission(m_apParticles[0x10]);
    StopParticleNodeEmission(m_apParticles[0x0c]);
    StopParticleNodeEmission(m_apParticles[0x0d]);
    // BUG(original): a dragon index above 1 uses a stale register for the node; the heroes are 0 and 1.
    if (m_ui8Hero <= 1) {
        CSGLeaf* object = static_cast<CSGLeaf*>(m_apObjects[0]);
        if (object != nullptr) object->m_sgProperties = (object->m_sgProperties & 0xfffffffbu) | 4u;
    }
    stopAndRelease(m_unk19b8);
    stopAndRelease(m_unk19c0);
    releaseSpark(m_unk19d8);
    stopAndRelease(m_unk19c8);
    stopAndRelease(m_unk19d0);
    if (m_ui8Hero <= 1) {
        CSGLeaf* object = static_cast<CSGLeaf*>(m_apObjects[1]);
        object->m_sgProperties = (object->m_sgProperties & 0xfffffffbu) | 4u;
    }
    if (m_unk19f4 != nullptr) {
        StopOwnedParticleEffect(static_cast<IKFx*>(m_unk19f4), this);  // 0x001cdde8
        static_cast<IKFx*>(m_unk19f4)->ReleaseReservation(this);
        m_unk19f4 = nullptr;
    }
    if (m_unk1a08 != nullptr) {
        IKFx* cursor = m_unk1a08;
        StopTargetCursorNow(cursor, this);  // 0x001d5988 (immediate)
        cursor->StopAndRelease(this);       // vt+0x58
        m_unk1a08 = nullptr;
    }
    static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_unk2d0 = 0;
}

// 0x00345e50 IKHkHero_AttachNodeToHotspot_maybe: `node` taken from its parent and hung under the hero's body hot spot
// (the group's vt+0x16c, part 0) when that has a node, else under the hero's node (vt+0x70).
void CKHkS08Hero::AttachNodeToHotspot(CSGLeaf* node) {
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    const int8_t index = static_cast<int8_t>(static_cast<IKGrpHero*>(m_pGrpHero)->GetHotSpotIndex(m_ui8Hero, 0));
    if (index != -1) {
        CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_apHotSpots[index]);
        if (spot->m_pParent != nullptr) {
            spot->AttachVolume(node);  // 0x000ce2b8
            return;
        }
    }
    static_cast<CSGBranch*>(m_pKGLObject)->AddChild(node);  // vt+0x70
}

// 0x002dbb88 CKHkS08Hero_OnLock (vt+0xa8): every state machine left, the root blend slot's crossfade finished (one step
// of its remaining time), the camera target leaf (+0x1818) back on the body at identity, the landing / approach
// records cleared, the group's dragon request dropped.
void CKHkS08Hero::OnLock() {
    ExitAllStateMachines();  // 0x00348f00
    m_animBlendSlot10f0.UpdateCrossfade(m_animBlendSlot10f0.m_unk0c);  // 0x0007a9d0
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_unk1818);
    AttachNodeToHotspot(leaf);  // 0x00345e50
    leaf->SetIdentity();        // 0x000d08f0
    const float zero = 0.0f;    // TOC1 +0x1da4
    m_unk1174 = 0;
    m_unk1175 = 0;
    m_unk1178 = zero;
    m_unk117c = zero;
    m_unk1180 = 0;
    m_unk1181 = 0;
    m_unk1184 = zero;
    m_unk1188 = zero;
    m_unk118c = 0;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    group->m_unk65 = group->m_unk64;
    group->m_unkf8 &= ~0x20u;
}

// 0x002dafa8 CKHkS08Hero_OnUnlock (vt+0xac): the runtime state reset (IKHkHero_OnDisable_maybe 0x347528), the camera
// target leaf shown in sector 0, the motion reset, the game manager's record of the dragon (+0xdf8 + 0x20 x dragon)
// cleared: both vectors to the null vector, the two bytes and the word 0.
void CKHkS08Hero::OnUnlock() {
    ResetRuntimeState(0);  // IKHkHero_OnDisable_maybe 0x00347528 = ResetRuntimeState(0) 0x00346480
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk1818), 0, 0, 0);  // 0x005832a8
    ResetMotionState(0);   // 0x002d9410
    // TOC1 +0x1dc0: the zero vector 0xc50d64.
    uint8_t* record = reinterpret_cast<uint8_t*>(&static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_unkDF4[1]) +
                      static_cast<uint32_t>(m_ui8Hero) * 0x20u;
    std::memcpy(record + 0x00, &kHeroZeroVector, 12);
    std::memcpy(record + 0x0c, &kHeroZeroVector, 12);
    record[0x18] = 0;
    record[0x19] = 0;
    std::memset(record + 0x1c, 0, 4);
}

// 0x00368618 CKHkS08Hero_CtlState2_MoveToTargetBody_maybe: entering (1) sets +0xb0 = 4 and answers 0; leaving (any other
// phase) clears +0x360 bit 30 and +0x35c bits 5 / 29 and answers 0. Running (0): the facing +0x3a4 is +0x540.. with
// +0x360 bit 30, else with +0x35c bit 29 the flat direction to the controlling hero (y 0.0, TOC +0x2e08; normalised
// unless of length 0: 1.0 / length, TOC +0x2e04), else kept; then AIMoveToTarget to +0x398 (walk speed for the player
// itself, the lost check on); arrived with +0x3b0 bit 1, +0x360 bit 30 clears and +0x35c bits 5 / 29 clear, bit 6 sets.
uint8_t CKHkS08Hero::CtlMoveToTargetBody(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_unkb0 = 4;
        return 0;
    }
    if (phase != 0) {
        m_unk360 &= 0xbfffffffu;
        m_unk35c &= 0xdfffffdfu;
        return 0;
    }
    if ((m_unk360 & 0x40000000u) != 0) {
        m_unk3a4 = m_unk540;
        m_unk3a8 = m_unk544;
        m_unk3ac = m_unk548;
    } else if ((m_unk35c & 0x20000000u) != 0) {
        const CKHkS08Hero* leader = GetControllingHero();  // 0x00344e68
        const float zero = 0.0f;
        const float x = leader->m_unk54c - m_unk54c;
        const float y = leader->m_unk550 - m_unk550;
        const float z = leader->m_unk554 - m_unk554;
        m_unk3a4 = x;
        m_unk3a8 = y;
        m_unk3a8 = zero;
        m_unk3ac = z;
        const float length = static_cast<float>(
            c22spyro::MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, m_unk3a8 * m_unk3a8))));  // 0x00010690
        if (length != zero) {
            const float scale = 1.0f / length;
            m_unk3ac = scale * m_unk3ac;
            m_unk3a4 = scale * m_unk3a4;
            m_unk3a8 = scale * m_unk3a8;
        }
    }
    const uint8_t player = m_ui8Hero == m_ui8TrackedLeader ? 1 : 0;
    if (AIMoveToTarget(clock, reinterpret_cast<CVector3*>(&m_unk398), reinterpret_cast<const CVector3*>(&m_unk3a4), player, 0,
                       1) != 0 &&  // 0x0036dd08
        (m_unk3b0 & 2u) != 0) {
        m_unk360 &= 0xbfffffffu;
        m_unk35c = (m_unk35c & 0xdfffff9fu) | 0x40u;
    }
    return other;
}

// 0x0036bf20 CKHkS08Hero_MoveTowardDrivenTarget_maybe (CKHkS08Hero_UpdateObjectDrivenMove_maybe 0x363090 passes +0x3dc and
// +0x398): +0x530 and +0x3dc = `speed`; with a speed, the flat direction to `target` (normalised unless 0) becomes the
// move and facing directions (+0x540, +0x3b8) and the yaw (+0x538); within this frame's step (+0x3dc x dt) of the target
// (+0x398) the hero is put there (TeleportTo, facing the direction; +0x3dc = 0) and 1 is returned; else, with +0x35c bit
// 7, the vertical speed +0x5f4 = the 3D direction's y x the step, and 0. Without a speed 1.
uint8_t CKHkS08Hero::MoveTowardDrivenTarget(float speed, const IKTime* clock, const CVector3* target) {
    m_unk530 = speed;
    m_unk3dc = speed;
    if (speed == 0.0f) return 1;  // TOC +0x2e88
    const float dx = target->x - m_unk54c;
    const float dz = target->z - m_unk554;
    const float y = m_unk550;
    float ty = target->y;
    CVector3 dir{dx, 0.0f, dz};
    const float xx = dx * dx;
    const float zz = dz * dz;
    const float flat = static_cast<float>(std::sqrt(static_cast<double>((xx + 0.0f) + zz)));  // 0x00010690
    if (flat != 0.0f) {
        const float k = 1.0f / flat;  // TOC +0x2ecc
        dir.z = dir.z * k;
        dir.x = dir.x * k;
        dir.y = dir.y * k;
    }
    m_unk540 = dir.x;
    m_unk548 = dir.z;
    m_unk544 = dir.y;
    m_unk3b8 = dir.x;
    m_unk3c0 = dir.z;
    m_unk3bc = dir.y;
    m_unk538 = Vec3_GetYawAngleFromX(&dir);  // 0x00244638
    const float ox = m_unk54c - m_unk398;
    const float oz = m_unk554 - m_unk3a0;
    const float step = m_unk3dc * clock->m_afDeltaTime[0];
    if (ppc::fmadds(ox, ox, oz * oz) <= step * step) {  // cror lt / eq
        TeleportTo(target, &dir, 0, 1, 0xffff, 0);  // 0x0036a578
        m_unk3dc = 0.0f;
        return 1;
    }
    if ((m_unk35c & 0x80u) == 0) return 0;
    ty = ty - y;
    const float length = static_cast<float>(std::sqrt(static_cast<double>(zz + ppc::fmadds(ty, ty, xx))));  // 0x00010690
    if (length != 0.0f) ty = ty * (1.0f / length);
    m_unk5f4 = ty * step;
    return 0;
}
