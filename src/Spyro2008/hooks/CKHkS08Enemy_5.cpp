// Reconstructed original translation unit: 0x288b18-0x28b4b0 (GAME_TOC1, main_toc1), 60 functions, 38 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x288b18  CKHkS08Enemy_ApplyElementResistance  (CKHkS08Enemy_12.cpp)
//   [x] 0x288c58  CKHkS08Enemy_SetGrabbedBy
//   [x] 0x288c98  CKHkS08Enemy_ClearGrabber
//   [ ] 0x288cd0  CKHkS08Enemy_GetHeldFlag_maybe  [dead]
//   [ ] 0x288ce0  CKHkS08Enemy_GetAnimLayerTime_2_maybe  [dead]
//   [ ] 0x288d28  CKHkS08Enemy_GetAnimLayerTrackField5C_maybe  [dead]
//   [ ] 0x288d70  CKHkS08Enemy_GetAnimLayerTrackField58_maybe  [dead]
//   [ ] 0x288db8  KStub_ReturnFloat1_288db8  [dead]
//   [ ] 0x288dc0  KStub_Nop_288dc0  [dead]
//   [x] 0x288dc8  CKHkS08Enemy_GetPairedGrabAnim
//   [x] 0x288e08  CKHkS08Enemy_SetAttackSpheresActive
//   [x] 0x288fc8  CKHkS08Enemy_GetAbilityInputFlags_maybe
//   [x] 0x288fd0  CKHkS08Enemy_GetGrabbingHero
//   [x] 0x289060  CKHkS08Enemy_GetTargetHero
//   [x] 0x2890f0  CKHkS08Enemy_GetTargetRaw
//   [x] 0x2890f8  CKHkS08Enemy_AddPoisonGauge_2
//   [x] 0x289120  CKHkS08Enemy_ClearAttackSlotReservation_maybe
//   [ ] 0x289138  CKHkS08Enemy_ForceState7_maybe  [dead]
//   [x] 0x289278  CKHkS08Enemy_IsValidCombatTarget_maybe
//   [x] 0x2892e8  CKHkS08Enemy_GetHotSpot
//   [ ] 0x289348  FUN_00289348  [dead]
//   [x] 0x289370  CKHkS08Enemy_GetAttackSlotCategoryThunk_maybe
//   [ ] 0x289398  CKHkS08Enemy_GetLayerSlotAnimDuration_Thunk  [dead: no pointer to its descriptor 0xb8d0c8, no call]
//   [ ] 0x2893c0  CKHkS08Enemy_GetAnimLayerTime_Thunk  [dead]
//   [x] 0x2893e8  CKHkS08Enemy_IsAnimEndReached_Thunk  (thunk: target called directly)
//   [ ] 0x289410  CKHkS08Enemy_SetBlendSlotAnimPairIfHeld_maybe  [dead]
//   [ ] 0x289490  CKHkS08Enemy_CrossfadeBlendSlotAnimIfHeld_maybe  [dead]
//   [ ] 0x289520  CKHkS08Enemy_SetLayerSlotAnimIfHeld_maybe  [dead]
//   [ ] 0x2895d8  CKHkS08Enemy_StopSoundIfGrabbed_maybe  [dead]
//   [ ] 0x289610  CKHkS08Enemy_PlaySoundIfGrabbed_maybe  [dead]
//   [ ] 0x289658  CKHkS08Enemy_RequestAnimIfGrabbed_maybe  [dead]
//   [ ] 0x2896a0  CKHkS08Enemy_IsState4_maybe  [dead]
//   [x] 0x2896b8  CKHkS08Enemy_IsGrabbedState_maybe
//   [ ] 0x2896d0  FUN_002896d0  [dead]
//   [x] 0x289718  CKHkS08Enemy_SetPosition
//   [x] 0x289750  CKHkS08Enemy_TeleportTo_maybe
//   [x] 0x289828  StaticInitAndDestruction_289828  (the two file statics at the end)
//   [ ] 0x289858  _GLOBAL__D_289858
//   [ ] 0x289868  _GLOBAL__I_289868
//   [ ] 0x289878  CKHkS08Enemy_GetWorldForward_maybe  [dead]
//   [x] 0x2898b0  CKHkS08Enemy_CanBeGrabbed_maybe
//   [x] 0x289a98  CKHkS08Enemy_IsOnGround_maybe
//   [x] 0x289b38  CKHkS08Enemy_CanBeHeldAtPosition_maybe
//   [ ] 0x289d98  CKHkS08Enemy_SetGrabbedAnimTime_maybe  [dead]
//   [x] 0x289df8  CKHkS08Enemy_AdvanceGrabbedAnimTime_maybe
//   [x] 0x289e60  CKHkS08Enemy_ComputeGroundPoint_maybe
//   [x] 0x289f08  CKHkS08Enemy_SetHeldFlag
//   [ ] 0x289f38  CKHkS08Enemy_SetGrabbedByAttachToHotSpot_maybe  [dead]
//   [ ] 0x28a038  CKHkS08Enemy_SetGrabbedByAttachToOwner_maybe  [dead]
//   [x] 0x28a160  CKHkS08Enemy_GetSectorHotSpot
//   [x] 0x28a1c8  CKHkS08Enemy_GetGrabHotSpot_maybe
//   [x] 0x28a268  CKHkS08Enemy_GetSectorHotSpotPosition
//   [x] 0x28a2e0  CKHkS08Enemy_CrossfadeAnimFromDictionary_maybe
//   [ ] 0x28a430  CKHkS08Enemy_SetBlendSlotAnimPair_maybe  [dead: no pointer to its descriptor 0xb8d268, no call]
//   [ ] 0x28a598  CKHkS08Enemy_SetBlendSlotAnim_maybe  [dead: no pointer to its descriptor 0xb8d270, no call]
//   [x] 0x28a6e0  CKHkS08Enemy_ReceiveDamage (in CKHkS08Enemy.cpp, beside the armour helpers)
//   [x] 0x28aa70  CKHkS08Enemy_ResetMainStateMachine_maybe
//   [x] 0x28ab48  CKHkS08Enemy_EnterReleasedState_maybe
//   [x] 0x28ac90  CKHkS08Enemy_ApplyThrowImpactDamage
//   [ ] 0x28b4a8  KStub_Nop_28b4a8  [dead]
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include <cstring>
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/logic/CKS08StunDamage.h"
#include "k2000/misc/Mat4.h"
#include "crt/xatan.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "Spyro2008/logic/memory/CKS08EnemyElementPool.h"
#include "Spyro2008/logic/CKS08EnemyElement.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/ai/CKHkDetectorGroup.h"

#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "crt/ppc_ops.h"

using namespace enemy;

namespace {
// 0x00a700f8 (TOC1 +0xda0 points at it): the number of paired grab animations per enemy kind.
const uint32_t kPairedGrabAnimCount[9] = {19, 19, 19, 19, 19, 0, 0, 19, 0};
// The arrays 0x00b00f80 (TOC1 +0xda4) points at, per kind (0x00c40720 ...; the kinds without any: null).
const int32_t kPairedGrabAnims0[19] = {66, 67, 69, 70, 71, 72, 73, 74, 75, 76, 78, 79, 81, 84, 85, 80, 82, 0, 83};
const int32_t kPairedGrabAnims1[19] = {65, 66, 68, 69, 70, 71, 72, 73, 74, 75, 77, 78, 80, 83, 84, 79, 81, 0, 82};
const int32_t kPairedGrabAnims2[19] = {0, 0, 0, 0, 0, 0, 0, 0, 68, 69, 71, 73, 74, 77, 78, 72, 75, 0, 76};
const int32_t kPairedGrabAnims3[19] = {0, 0, 0, 0, 0, 0, 0, 0, 66, 67, 69, 71, 72, 75, 76, 70, 73, 0, 74};
const int32_t kPairedGrabAnims4[19] = {0, 0, 0, 0, 0, 0, 0, 0, 66, 67, 69, 71, 72, 75, 76, 70, 73, 0, 74};
const int32_t kPairedGrabAnims7[19] = {65, 66, 68, 69, 70, 71, 72, 73, 74, 75, 77, 78, 80, 83, 84, 79, 81, 0, 82};
const int32_t* const kPairedGrabAnims[9] = {kPairedGrabAnims0, kPairedGrabAnims1, kPairedGrabAnims2,
                                            kPairedGrabAnims3, kPairedGrabAnims4, nullptr,
                                            nullptr, kPairedGrabAnims7, nullptr};
}  // namespace

// 0x00288c58 CKHkS08Enemy_SetGrabbedBy: a hero takes the enemy when none holds it (+0x298 / +0x294, +0x290 set, the
// position kept at +0x7ec).
void CKHkS08Enemy::SetGrabbedBy(IKSerializable* hero) {
    if (m_pGrabbingHero != nullptr) return;
    m_pLastGrabbingHero = hero;
    m_unk290 = 1;
    m_pGrabbingHero = hero;
    m_unk7ec = m_v3Position.x;
    m_unk7f4 = m_v3Position.z;
    m_unk7f0 = m_v3Position.y;
}

// 0x00288c98 CKHkS08Enemy_ClearGrabber: the holding hero lets go (the life flag 0x200 cleared).
void CKHkS08Enemy::ClearGrabber(IKSerializable* hero) {
    if (m_pGrabbingHero != hero) return;
    m_pGrabbingHero = nullptr;
    m_unk290 = 0;
    m_bitArray = m_bitArray & 0xfffffdffu;  // rlwinm 22 / 10
}

// 0x00288dc8 CKHkS08Enemy_GetPairedGrabAnim: the kind's paired grab animation `index`, -1 past the kind's count.
int32_t CKHkS08Enemy::GetPairedGrabAnim(uint32_t index) const {
    const uint8_t kind = m_ui8EnemyClassType;
    if (kPairedGrabAnimCount[kind] <= index) return -1;
    return kPairedGrabAnims[kind][index];
}

// 0x00288fc8 CKHkS08Enemy_GetAbilityInputFlags_maybe
uint32_t CKHkS08Enemy::GetAbilityInputFlags() const {
    return m_unk77c;
}

// 0x00288fd0 CKHkS08Enemy_GetGrabbingHero: the holding hero when it is a hero (key 0x25c2), else null.
IKSerializable* CKHkS08Enemy::GetGrabbingHero() const {
    if (m_pGrabbingHero == nullptr || m_pGrabbingHero->IsKindOfClass(0x25c2) == 0) return nullptr;  // vt+0x08
    return m_pGrabbingHero;
}

// 0x00289060 CKHkS08Enemy_GetTargetHero: the target when it is a hero (key 0x25c2), else null.
IKSerializable* CKHkS08Enemy::GetTargetHero() const {
    if (m_pTarget == nullptr || m_pTarget->IsKindOfClass(0x25c2) == 0) return nullptr;  // vt+0x08
    return m_pTarget;
}

// 0x002890f0 CKHkS08Enemy_GetTargetRaw
IKSerializable* CKHkS08Enemy::GetTargetRaw() const {
    return m_pTarget;
}

// 0x002890f8 CKHkS08Enemy_AddPoisonGauge_2: AddPoisonGauge's code again.
void CKHkS08Enemy::AddPoisonGauge2(float amount) {
    const float value = ppc::fmadds(amount, m_pActiveEnemyCpnt->m_unk290, m_fPoisonGauge);
    m_fPoisonGauge = value;
    if (!(value <= m_pActiveEnemyCpnt->m_unk24c)) m_fPoisonGauge = m_pActiveEnemyCpnt->m_unk24c;
}

// 0x00289120 CKHkS08Enemy_ClearAttackSlotReservation_maybe
void CKHkS08Enemy::ClearAttackSlotReservation() {
    m_unk891 = 0;
    m_unk7d8 = -1;
}

// 0x00289278 CKHkS08Enemy_IsValidCombatTarget_maybe: not in main states 0, 8, 9, 11, 12, 0x11, 0x16, 0x17, 0x18, and the
// life flag 0x10 clear.
uint8_t CKHkS08Enemy::IsValidCombatTarget() const {
    const uint8_t state = m_mainState;
    if (static_cast<uint8_t>(state - 0xb) <= 1) return 0;
    if (state == 9 || state == 0x11 || state == 0 || state == 8 || state == 0x17 || state == 0x18 || state == 0x16) return 0;
    return static_cast<uint8_t>(((m_bitArray >> 4) & 1u) ^ 1u);
}

// 0x002892e8 CKHkS08Enemy_GetHotSpot: hot spot `index` of the sector component.
CSGHotSpot* CKHkS08Enemy::GetHotSpot(int32_t index) {
    return static_cast<CSGHotSpot*>(m_apEnemySectorCpnt[GetSectorIndex()]->GetHotSpot(static_cast<uint32_t>(index)));  // 0x002771c0, 0x002b31e0
}

// 0x00289370 CKHkS08Enemy_GetAttackSlotCategoryThunk_maybe
int32_t CKHkS08Enemy::GetAttackSlotCategoryThunk(int32_t kind) {
    return GetAttackSlotCategory(kind);  // 0x0027d100
}

// 0x002896b8 CKHkS08Enemy_IsGrabbedState_maybe: main state 7.
uint8_t CKHkS08Enemy::IsGrabbedState() const {
    return m_mainState == 7 ? 1 : 0;
}

// 0x00289718 CKHkS08Enemy_SetPosition: the previous position kept (+0x140), the new one set.
void CKHkS08Enemy::SetPosition(const CVector3* position) {
    m_unk140 = m_v3Position.x;
    m_unk148 = m_v3Position.z;
    m_unk144 = m_v3Position.y;
    m_v3Position.z = position->z;
    m_v3Position.x = position->x;
    m_v3Position.y = position->y;
}

// 0x00289750 CKHkS08Enemy_TeleportTo_maybe: SetPosition, the ground resolved (vt+0x13c; its argument is the position
// pointer still in r4, which it does not read), and the node placed at the position.
void CKHkS08Enemy::TeleportToPosition(const CVector3* position) {
    m_unk140 = m_v3Position.x;
    m_unk148 = m_v3Position.z;
    m_unk144 = m_v3Position.y;
    m_v3Position.x = position->x;
    m_v3Position.y = position->y;
    m_v3Position.z = position->z;
    ResolveGroundAndApplyTransform(nullptr);  // vt+0x13c
    RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    frame->modelling.pos.z = m_v3Position.z;
    frame->modelling.pos.x = m_v3Position.x;
    frame->modelling.pos.y = m_v3Position.y;
    frame->modelling.flags = frame->modelling.flags & 0xfffdffffu;
    RwFrame_MarkDirty(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);  // 0x00010698
}

// 0x00289a98 CKHkS08Enemy_IsOnGround_maybe: the ground probed under the enemy; on it (status 0) when the height above it
// is below 0.01, and for statuses 1 and 2.
uint8_t CKHkS08Enemy::IsOnGround() {
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
        ->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    if (status == 0) return (m_GrdContDatasInOut.m_fdH >= 0.01f) ? 0 : 1;  // TOC1 +0xdc8 0x3c23d70a
    return (status >= 0 && status <= 2) ? 1 : 0;
}

// 0x00289e60 CKHkS08Enemy_ComputeGroundPoint_maybe: the position, lowered by the height above the ground when the probe
// finds it (status 0).
CVector3 CKHkS08Enemy::ComputeGroundPoint() {
    CVector3 point = m_v3Position;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
        ->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    if (m_GrdContDatasInOut.m_eContactStatus == 0) point.y = point.y - m_GrdContDatasInOut.m_fdH;
    return point;
}

// 0x00289f08 CKHkS08Enemy_SetHeldFlag: while held, the life flag 0x200 (and the bits above it: the value's byte << 9)
// set from `value`.
void CKHkS08Enemy::SetHeldFlag(uint32_t value) {
    if (m_pGrabbingHero == nullptr) return;
    m_bitArray = (m_bitArray & 0xfffffdffu) | ((value << 9) & 0x1fe00u);
}

// 0x0028a160 CKHkS08Enemy_GetSectorHotSpot: GetHotSpot's code again.
IKSerializable* CKHkS08Enemy::GetSectorHotSpot(uint32_t index) {
    return m_apEnemySectorCpnt[GetSectorIndex()]->GetHotSpot(index);
}

// 0x0028a1c8 CKHkS08Enemy_GetGrabHotSpot_maybe: hot spot 4 (both branches of the kind test, 5 or not, take 4).
IKSerializable* CKHkS08Enemy::GetGrabHotSpot() {
    CKEnemySectorCpnt* sector = m_apEnemySectorCpnt[GetSectorIndex()];
    if (m_ui8EnemyClassType != 5) return sector->GetHotSpot(4);
    return sector->GetHotSpot(4);
}

// 0x0028a268 CKHkS08Enemy_GetSectorHotSpotPosition: hot spot 0 in the world.
void CKHkS08Enemy::GetSectorHotSpotPosition(CVector3* out) {
    static_cast<CSGHotSpot*>(m_apEnemySectorCpnt[GetSectorIndex()]->GetHotSpot(0))->GetWorldPosition(out);  // 0x000ce790
}


// 0x0028aa70 CKHkS08Enemy_ResetMainStateMachine_maybe: the life flags 0x10 and 8 set (the update skipped), the main state
// left (clock null, to 0xff) and none.
void CKHkS08Enemy::ResetMainStateMachine() {
    m_bitArray = (((m_bitArray & 0xffffffefu) | 0x10u) & 0xfffffff7u) | 8u;
    if (m_mainState != 0xff) CallMainState(m_mainState, nullptr, 2, 0xff);
    m_mainState = 0xff;
}

// 0x0028ab48 CKHkS08Enemy_EnterReleasedState_maybe: +0x7d4 kept, the main machine to state 10 (clock null).
void CKHkS08Enemy::EnterReleasedState(uint8_t value) {
    m_unk7d4 = value;
    const uint8_t old = m_mainState;
    if (old != 0xff) CallMainState(old, nullptr, 2, 10);
    m_mainState = 10;
    CallMainState(10, nullptr, 1, old);
}

namespace {
// The squad's fight zone (CKGrpSquad_GetFightZone 0x25ab50: the parent group, +0x1c) and its detector group (+0x30).
CKGrpFightZone* GrabZone(IKSerializable* squad) {
    return squad == nullptr ? nullptr : static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(squad)->m_pParent);
}
}  // namespace

// 0x00289b38 CKHkS08Enemy_CanBeHeldAtPosition_maybe: an enemy of a fight zone with a detector group and flag 0x40 (+0x0c),
// not off (+0x0c bit 3), inside the zone's detectors and in a state: 1 (the node's matrices brought up to date first);
// while grabbed (state 7) the move since the grab point (+0x7ec) is swept against the walls (the kind's radius, the
// component's height): a wall stops it (0, back at the grab point), a slide moves it on x / z (0, the height kept), a
// free move is kept (1); the grab point follows.
uint8_t CKHkS08Enemy::CanBeHeldAtPosition() {
    CKGrpFightZone* zone = GrabZone(m_pGroupSquad);
    if (zone == nullptr || zone->m_pUnk30 == nullptr) return 0;
    if ((zone->m_bitArray & 0x40u) == 0) return 0;
    if ((m_bitArray & 8u) != 0) return 0;
    if (static_cast<const CKHkDetectorGroup*>(zone->m_pUnk30)->IsTriggered(&m_v3Position.x) == 0) return 0;  // vt+0xc4
    if (m_mainState == 0xff) return 0;
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    node->ForceWorldMatrixUpdate();  // vt+0x50
    const RwV3d& at = node->m_pRwFrame->ltm.pos;
    if (m_mainState != 7) return 1;
    CLine line;
    line.m_start = CVector3{m_unk7ec, m_unk7f0, m_unk7f4};
    line.m_VectDir = CVector3{at.x - m_unk7ec, at.y - m_unk7f0, at.z - m_unk7f4};
    CSlideGroundEdgeDatasOut slide;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    const uint8_t result = collision->ResolveSweptCylinderWalls(&line, m_pActiveEnemyCpnt->m_MoveCpnt.m_afParams[0], ComponentHeight(),
                                                                &slide, nullptr, nullptr, 1);  // 0x0019aa68
    uint8_t held;
    if (result == 1) {
        held = 0;
        m_v3Position.y = m_unk7f0;
        m_v3Position.x = m_unk7ec;
        m_v3Position.z = m_unk7f4;
    } else if (result < 1 || result > 3) {
        held = 1;
    } else {
        held = 0;
        m_v3Position.y = slide.m_v3BouncingVector.y + m_v3Position.y;
        const float x = slide.m_v3BouncingVector.x + m_v3Position.x;
        const float z = slide.m_v3BouncingVector.z + m_v3Position.z;
        m_v3Position.y = m_unk7f0;
        m_v3Position.x = x;
        m_v3Position.z = z;
    }
    m_unk7f4 = m_v3Position.z;
    m_unk7ec = m_v3Position.x;
    m_unk7f0 = m_v3Position.y;
    return held;
}

// 0x002898b0 CKHkS08Enemy_CanBeGrabbed_maybe: never with an elemental armour part (+0x898 with a part of type 0..7);
// kinds 0, 1 and 7 unless dying, spawning, grabbed or in the states 0x15..0x18, 0x19, 0x1e, 0x25, 0xff, inside the
// zone's detectors; kinds 2..4 only launched (reaction 8) or wind-caught (state 0x1d), inside the detectors and by the
// wind beam (`windBeam`); kinds 5 and 6 never.
uint8_t CKHkS08Enemy::CanBeGrabbed(uint8_t windBeam) {
    if (m_unk898 != 0 && m_unk514.m_ui32NbUsedElt != 0) {
        auto* parts = reinterpret_cast<CKS08EnemyElement**>(m_unk514.m_pBlock);
        for (uint32_t i = 0; i < m_unk514.m_ui32NbUsedElt; ++i) {
            const CKS08EnemyElement* part = parts[i];
            if (part == nullptr || part->m_pPool58 == nullptr) continue;
            const int32_t type = static_cast<const CKS08EnemyElementPool*>(part->m_pPool58)->m_unk14;
            if (!(type < 0) && type != 8) return 0;
        }
    }
    const uint32_t kind = m_ui8EnemyClassType;
    if (kind > 7) return 0;
    const uint32_t bit = 1u << kind;
    const CKHkDetectorGroup* detectors = static_cast<const CKHkDetectorGroup*>(GrabZone(m_pGroupSquad)->m_pUnk30);
    if ((bit & 0x83u) != 0) {
        switch (m_mainState) {
            case 0x15: case 0x16: case 0x25: case 0x17: case 0x18: case 0: case 8: case 0x19: case 0x1e: case 0xff:
                return 0;
            default:
                return detectors->IsTriggered(&m_v3Position.x) != 0 ? 1 : 0;  // vt+0xc4
        }
    }
    if ((bit & 0x1cu) == 0) return 0;
    if (m_reactState != 8 && m_mainState != 0x1d) return 0;
    if (detectors->IsTriggered(&m_v3Position.x) == 0) return 0;
    return windBeam != 0 ? 1 : 0;
}

namespace {
// The yaw that faces a direction of x `x` and z `z` (inlined twice in ApplyThrowImpactDamage): acos(-z), mirrored to
// 2 pi - it for a positive x; -z outside [-1, 1] gives pi below and 0 above (TOC +0xdb8, +0xe0c, +0xe10).
float YawFacing(float x, float z) {
    const float c = -z;
    const bool outside = c < 0.0f ? c < -1.0f : c > 1.0f;
    if (outside) return c < 0.0f ? 3.14159274f : 0.0f;
    float yaw = crt::Acosf(c);  // 0x0098e1a0
    if (x > 0.0f) yaw = 6.28318548f - yaw;
    return yaw;
}
}  // namespace

// 0x0028ac90 CKHkS08Enemy_ApplyThrowImpactDamage: a thrown enemy hit by `damage` (+0x27c): the health loses its amount
// (not below 0), a hero damage (0x998c) fills the stun and disarm gauges; the knockback direction (+0x248) is `along`,
// or away from the target (+0x330) when `along` is zero (flattened, normalised); the enemy faces it, the direction is
// turned by the damage's yaw (+0x1c) and pitch (+0x18) in degrees x -57.3 and normalised; the speed and lift from the
// damage, the velocity cleared, the moving spheres on with the kind's damage, reaction 8, main state 2; a damage with
// +0x20 clear sets +0x834; the gauge +0x6d0 cleared.
void CKHkS08Enemy::ApplyThrowImpactDamage(IKSerializable* damage, const CVector3* along) {
    m_pPendingDamage = static_cast<CKS08Damage*>(damage);
    const float amount = m_pPendingDamage->m_fAmount;
    if (m_fHealth >= amount) {
        m_fHealth = m_fHealth - amount;
    } else {
        m_fHealth = 0.0f;
    }
    if (m_pPendingDamage->IsKindOfClass(0x998c) != 0) {  // vt+0x08 CKS08HeroDamage
        const CKS08StunDamage* stun = static_cast<const CKS08StunDamage*>(static_cast<CKDamage*>(m_pPendingDamage));
        float stunAmount;
        std::memcpy(&stunAmount, &stun->m_fStunAmount, sizeof stunAmount);
        m_fStunGauge = m_fStunGauge + stunAmount;
        m_fDisarmGauge = m_fDisarmGauge + stun->m_fDisarmAmount;
    }
    float yaw;
    if (along->x != 0.0f || along->y != 0.0f || along->z != 0.0f) {  // g_nullVector (TOC +0xe08)
        float x = along->x;
        float z = along->z;
        m_unk248 = along->x;
        m_unk24c = along->y;
        m_unk250 = along->z;
        const float length = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f))));  // 0x00010690
        if (length != 0.0f) {
            const float inverse = 1.0f / length;  // TOC +0xd9c
            z = z * inverse;
            x = x * inverse;
        }
        yaw = YawFacing(x, z);
    } else {
        const RwV3d& at = static_cast<CSGMovable*>(m_pTarget->m_pKGLObject)->m_pRwFrame->ltm.pos;
        m_unk248 = m_v3Position.x - at.x;
        m_unk24c = m_v3Position.y - at.y;
        m_unk250 = m_v3Position.z - at.z;
        m_unk24c = 0.0f;
        const float length = static_cast<float>(
            enemy::MathSqrtf(ppc::fmadds(m_unk250, m_unk250, ppc::fmadds(m_unk248, m_unk248, m_unk24c * m_unk24c))));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_unk250 = inverse * m_unk250;
            m_unk248 = inverse * m_unk248;
            m_unk24c = inverse * m_unk24c;
        }
        yaw = YawFacing(m_unk248, m_unk250);
    }
    m_fYaw = yaw;
    alignas(16) CMatrix34 basis{};
    basis.m_right = CVector3{-m_unk250, 0.0f, m_unk248};
    basis.m_ui32Flags &= 0xfffdfffcu;
    basis.m_up = CVector3{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0xe14)
    basis.m_at = CVector3{m_unk248, m_unk24c, m_unk250};
    float pitch;
    std::memcpy(&pitch, &m_pPendingDamage->m_unk18, sizeof pitch);
    Mat4_RotateLocalYDeg(m_pPendingDamage->m_unk1c * -57.2957802f, &basis);  // 0x002413d0, TOC +0xe18
    Mat4_RotateLocalXDeg(pitch * -57.2957802f, &basis);              // 0x00241118
    m_unk248 = basis.m_at.x;
    m_unk24c = basis.m_at.y;
    m_unk250 = basis.m_at.z;
    const float length = static_cast<float>(
        enemy::MathSqrtf(ppc::fmadds(m_unk250, m_unk250, ppc::fmadds(m_unk248, m_unk248, m_unk24c * m_unk24c))));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        m_unk250 = inverse * m_unk250;
        m_unk248 = inverse * m_unk248;
        m_unk24c = inverse * m_unk24c;
    }
    m_fKnockbackForce = m_pPendingDamage->m_fKnockbackForce;
    m_fKnockbackTime = m_pPendingDamage->m_fKnockbackTime;
    m_v3Speed.x = 0.0f;
    m_v3Speed.z = 0.0f;
    m_v3Speed.y = 0.0f;
    SetAttackSpheresActive(1, nullptr);  // inlined: the kind's spheres with its +0x224 damage
    SwitchReactState(8, nullptr);        // the original passes no clock
    SwitchMainState(2, nullptr);
    if (m_pPendingDamage != nullptr && m_pPendingDamage->m_ui32DamageType == 0) m_unk834 = 1;
    m_fWindGauge = 0.0f;
}

namespace {
// 0x00a70120: per enemy kind, the number of moving (projectile) spheres SetAttackSpheresActive switches.
constexpr uint8_t kAttackSphereCount[9] = {2, 3, 3, 2, 3, 3, 3, 3, 2};
}  // namespace

// 0x00288e08 CKHkS08Enemy_SetAttackSpheresActive: the kind's moving spheres switched on (vt+0x108) with `damage` (the
// kind's +0x224 when null) as their damage (+0x1c), or released (vt+0x10c).
void CKHkS08Enemy::SetAttackSpheresActive(uint8_t on, IKSerializable* damage) {
    const uint8_t count = kAttackSphereCount[m_ui8EnemyClassType];
    if (on == 0) {
        for (uint32_t i = 0; i < count; ++i) ReleaseDynSphere(static_cast<uint8_t>(i));  // vt+0x10c
        return;
    }
    IKSerializable* given = damage != nullptr ? damage : m_pActiveEnemyCpnt->m_pUnk224;
    for (uint32_t i = 0; i < count; ++i) {
        EnableCollisionSphere(i);  // vt+0x108
        static_cast<IKBoundingVolume*>(m_apBVProj[i])->m_unk1c = given;
    }
}

// 0x0028a2e0 CKHkS08Enemy_CrossfadeAnimFromDictionary_maybe: while held (+0x294) with flag 0x200 (+0x0c), layer
// `layer` / slot `slot` crossfades to row `anim` of the variant's dictionary `layer` (AnimBlendSlot_CrossfadeToAnim
// 0x79ea0); 0 otherwise.
uint32_t CKHkS08Enemy::CrossfadeAnimFromDictionary(uint32_t anim, uint32_t mode, float blend, float start, uint32_t layer,
                                                   uint32_t slot) {
    const CAnimationDictionary* dictionary = AnimDictionary(static_cast<uint32_t>(GetSectorIndex()), layer);  // 0x002b3128
    const uint32_t word = static_cast<uint32_t>(dictionary->m_apAnimations[anim]);
    if (m_pGrabbingHero == nullptr) return 0;
    if ((m_bitArray & 0x200u) == 0) return 0;
    return m_apAnimLayerSlots[layer][slot].m_blendSlot.CrossfadeToAnim(static_cast<double>(blend), static_cast<double>(start), word, mode);
}

// 0x00289df8 CKHkS08Enemy_AdvanceGrabbedAnimTime_maybe: while held (+0x294) with flag 0x200 (+0x0c), the active track
// of layer `layer` / slot `slot` moves on by `dt`.
void CKHkS08Enemy::AdvanceGrabbedAnimTime(float dt, uint32_t layer, uint32_t slot) {
    if (m_pGrabbingHero == nullptr) return;
    if ((m_bitArray & 0x200u) == 0) return;
    CKAnmKeyFrameController* track = ActiveTrack(m_apAnimLayerSlots[layer][slot]);
    track->m_unk50 = dt + track->m_unk50;
}

// 0x00289828 StaticInitAndDestruction_289828: two file statics (0x00ceacd0, 0x00ceacd4) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceacd0 = -1.0f;
[[maybe_unused]] float s_unkceacd4 = -1.0f;
}  // namespace
