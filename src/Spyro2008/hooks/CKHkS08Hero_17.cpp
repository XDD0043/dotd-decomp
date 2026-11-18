// Reconstructed original translation unit: 0x33fa78-0x344758 (GAME_TOC1, main_toc1), 37 functions, 30 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: TransferHeroManaToOtherDragon (1), TransferHeroHealthToOtherDragon (1), UpdateHeroHealthAndManaSharing (1), UpdateHeroActionInput (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x33fa78  CKHkS08Hero_GrantPartnerAttackCredits_maybe
//   [x] 0x33fae0  CKHkS08Hero_AIAcquireTargetIfCredits
//   [x] 0x33fb80  CKHkS08Hero_AIUpdateCombatMovement_maybe
//   [x] 0x33fdb8  CKHkS08Hero_AIClearAttackButtons
//   [x] 0x33fdc8  CKHkS08Hero_AIQueueAttack
//   [ ] 0x340050  FUN_00340050  [dead]
//   [x] 0x340178  CKHkS08Hero_IsMovementMode0
//   [x] 0x340188  CKHkS08Hero_IsFlying_MovementMode1
//   [x] 0x3401a0  CKHkS08Hero_IsClimbing_MovementMode2
//   [x] 0x3401b8  CKHkS08Hero_GetMovementMode
//   [ ] 0x3401c8  CKHkS08Hero_OnMovementModeChanged_maybe  [dead]
//   [x] 0x3401f0  CKHkS08Hero_GetCarriedPowerBucket_maybe
//   [x] 0x3402a0  CKHkS08Hero_UpdateFlightFlapImpulse_maybe
//   [x] 0x3403f8  TransferHeroManaToOtherDragon
//   [x] 0x3405f0  TransferHeroHealthToOtherDragon
//   [ ] 0x3407e8  CKHkS08Hero_UpdateDragonSwitchInput_maybe  [dead: no pointer to its descriptor 0xb9faf8, no call]
//   [x] 0x3408f8  UpdateHeroHealthAndManaSharing
//   [x] 0x340a20  CKHkS08Hero_UpdateCarriedPowerBucketGroundTrigger_maybe
//   [x] 0x340c18  CKHkS08Hero_SetMovementMode
//   [x] 0x340cd8  StaticInitAndDestruction_340cd8  (the two file statics at the end)
//   [ ] 0x340d08  _GLOBAL__D_340d08
//   [ ] 0x340d18  _GLOBAL__I_340d18
//   [x] 0x340d28  CKHkS08Hero_InitInputActionTable_maybe
//   [ ] 0x340e50  FUN_00340e50  [dead]
//   [ ] 0x340e80  FUN_00340e80  [dead]
//   [ ] 0x340eb0  FUN_00340eb0  [dead]
//   [ ] 0x340ee0  FUN_00340ee0  [dead]
//   [ ] 0x340f10  FUN_00340f10  [dead]
//   [x] 0x340f40  CKHkS08Hero_TryUseInteractable_maybe
//   [x] 0x3411d8  CKHkS08Hero_UpdateButtonRecords
//   [x] 0x341fa0  CKHkS08Hero_ShouldJoinPartnerFlight_maybe
//   [x] 0x342808  CKHkS08Hero_UpdateGuardAndDodgeInput
//   [x] 0x342ef8  CKHkS08Hero_SetMovementModeUnlessLocked
//   [x] 0x342fa8  CKHkS08Hero_ShouldStayClimbing  (CKHkS08HeroCameraTarget.cpp)
//   [x] 0x3430a8  CKHkS08Hero_UpdateAirWallAction_maybe
//   [x] 0x3438b0  CKHkS08Hero_UpdateMovementModeFromInput
//   [x] 0x3445d8  CKHkS08Hero_UpdateActionInput
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/services/CTriggerStarter.h"
#include "Spyro2008/hooks/CKHkS08PowerBucket.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/input/PS3PadDevice.h"
#include "k2000/managers/CKInput.h"
#include "k2000/math/Math.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include <cmath>
#include <cstring>

// 0x00340d28 CKHkS08Hero_InitInputActionTable_maybe
void CKHkS08Hero::InitInputActionTable() {
    m_unkf04 = 0x2;
    m_unkf18 = 3;
    m_unkf2c = 4;
    m_unkef4 = 0x0;
    m_unkf00 = 0;
    m_unkef8 = 0;
    m_unkefc = 0;
    m_unkf08 = 0x0;
    m_unkf10 = 0x0;
    m_unkf14 = 0;
    m_unkf0c = 0x0;
    m_unkf1c = 0;
    m_unkf24 = 0;
    m_unkf28 = 0;
    m_unkf20 = 0;
    m_unkf40 = 8;
    m_unkf54 = 9;
    m_unkf68 = 6;
    m_unkef0 = 0x5;
    m_unkf30 = 0;
    m_unkf38 = 0;
    m_unkf3c = 0;
    m_unkf34 = 0;
    m_unkf44 = 0;
    m_unkf4c = 0;
    m_unkf50 = 0;
    m_unkf48 = 0;
    m_unkf58 = 0;
    m_unkf60 = 0;
    m_unkf6c = 0;
    m_unkf64 = 0;
    m_unkf5c = 0;
    m_unkf78 = 0;
    m_unkfa4 = 23;
    m_unkf7c = 0x00000007;
    m_unkf90 = 0x16;
    m_unkf70 = 0;
    m_unkf74 = 0x0;
    m_unkf80 = 0;
    m_unkf88 = 0;
    m_unkf8c = 0;
    m_unkf84 = 0;
    m_unkf9c = 0;  // the bytes at +0xac, +0xad and the halfword +0xae of the table entry: the whole word
    m_unkf94 = 0;
    m_unkfa0 = 0;
    m_unkf98 = 0;
    m_unkfb0 = 0;
    m_unkfb4 = 0;
    m_unkfa8 = 0;
    m_unkfac = 0;
}

// 0x00340178 CKHkS08Hero_IsMovementMode0: on the ground (+0x1808 0).
uint8_t CKHkS08Hero::IsMovementMode0() { return m_unk1808 == 0 ? 1 : 0; }

// 0x00340188 CKHkS08Hero_IsFlying_MovementMode1: flying (+0x1808 1).
uint8_t CKHkS08Hero::IsFlyingMovementMode1() { return m_unk1808 == 1 ? 1 : 0; }

// 0x003401a0 CKHkS08Hero_IsClimbing_MovementMode2: climbing (+0x1808 2).
uint8_t CKHkS08Hero::IsClimbingMovementMode2() { return m_unk1808 == 2 ? 1 : 0; }

// 0x003401b8 CKHkS08Hero_GetMovementMode: +0x1808 (0 ground, 1 flying, 2 climbing).
uint8_t CKHkS08Hero::GetMovementMode() { return m_unk1808; }

// 0x00340c18 CKHkS08Hero_SetMovementMode: a new mode marks the change (+0x180a; +0x1809 when taking off from the
// ground) and tells the game manager which dragon changed (its notifications only read the HUD list).
void CKHkS08Hero::SetMovementMode(uint8_t mode) {
    const uint8_t previous = m_unk1808;
    if (static_cast<int8_t>(previous) == static_cast<int8_t>(mode)) return;
    m_unk1808 = mode;
    m_unk180a = 1;
    if (previous == 0 && static_cast<int8_t>(mode) == 1) m_unk1809 = mode;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (m_ui8Hero == 0) {
        manager->NotifySpyroMovementModeChanged(m_unk1808);  // 0x004ff2d8
    } else if (m_ui8Hero == 1) {
        manager->NotifyCynderMovementModeChanged(m_unk1808);  // 0x00500b38
    }
}

// 0x00341fa0 CKHkS08Hero_ShouldJoinPartnerFlight_maybe (step 6 FLY): whether the hero takes off to join its
// climbing partner (+0x1615). The partner's ground is probed (the answer is not used); the hero is far when its
// horizontal distance to the partner passes the group's maximum (+0x108) less a slack (1; flying: +0x108 - +0x200, at
// least 0.5); a hero not yet joining that is steeply above it (over 60 degrees), far, with +0x358 bit 20 and the move
// pointing back to it is blocked by a wall or mesh along +0x15d4 times 10. Only a hero not climbing with a climbing
// partner joins: not dodging (+0xec8 bits 2 / 10), not low on a ground without engine flag 8, the partner's climb zone
// allowing it (CLIMB), not blocked; a joining hero keeps joining during an ability or holding record 1 on the ground;
// otherwise it starts with +0xed0 bit 28 when far (back on the ground first), on the ground when +0xec4 bit 24 is set
// (cleared), or in the air after record 1 was held past +0x978 (landing first): +0xed4 bit 5, the push record +0x156c
// along the gap projected on +0x15e0, +0x1618 = 0.5.
uint8_t CKHkS08Hero::ShouldJoinPartnerFlight() {
    auto wordAsFloat = [](uint32_t word) {
        float value;
        std::memcpy(&value, &word, 4);
        return value;
    };
    CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    const float gap314 = wordAsFloat(group->m_unk2d4[16]);  // +0x314
    const float gap318 = wordAsFloat(group->m_unk318);
    float slack = 1.0f;  // TOC +0x29e8
    if (m_unk1808 == 1) {
        slack = group->m_unk108 - group->m_unk200;  // 0x002ce518 CKGrpS08Hero_GetMaxPartnerDistance_maybe
        if (!(slack >= 0.5f)) slack = 0.5f;           // TOC +0x2a50
    }
    {
        CVector3 point{partner->m_unk54c, partner->m_unk550, partner->m_unk554};
        CGroundContactDatasInOut contact;
        GroundContact_ProbeGroundPoint(&contact, &point, nullptr);  // 0x00583ef8 (TocBridge; the answer is not used)
    }
    float dx = m_unk54c - partner->m_unk54c;
    float dy = m_unk550 - partner->m_unk550;
    float dz = m_unk554 - partner->m_unk554;
    float dx2 = dx * dx;
    float dz2 = dz * dz;
    {
        const float length = std::sqrt(ppc::fmadds(dy, dy, dx2) + dz2);  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            dz = dz * inv;
            dx = dx * inv;
            dy = dy * inv;
            dz2 = dz * dz;
            dx2 = dx * dx;
        }
    }
    const CVector3 kDown{0.0f, -1.0f, 0.0f};  // 0x00c50d7c (TOC +0x2a54)
    float c = ppc::fmadds(dz, kDown.z, ppc::fmadds(dx, kDown.x, dy * kDown.y));
    if (c <= -1.0f) {  // TOC +0x29fc
        c = -1.0f;
    } else if (c >= 1.0f) {
        c = 1.0f;
    }
    const float angle = crt::Acosf(c);  // TocBridge_Math_Acosf
    float hx = dx;
    float hz = dz;
    float hy = 0.0f;  // TOC +0x29f4
    {
        const float length = std::sqrt((dx2 + 0.0f) + dz2);
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            hz = dz * inv;
            hx = dx * inv;
            hy = inv * 0.0f;
        }
    }
    uint8_t far = 1;
    {
        const float ex = m_unk54c - partner->m_unk54c;
        const float ez = m_unk554 - partner->m_unk554;
        const float distance = std::sqrt(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, 0.0f)));
        if (!(distance > group->m_unk108 - slack)) far = 0;
    }
    uint8_t blocked = 0;
    if (m_unk1615 == 0 && angle * 57.2957801818847656f > 60.0f && far != 0 && (m_unk358 & 0x100000u) != 0 &&
        !(ppc::fmadds(m_unk384, hz, ppc::fmadds(m_unk37c, hx, m_unk380 * hy)) >= 0.0f)) {  // TOC +0x2a58 / +0x2a5c
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        CLine line;
        line.m_start = CVector3{m_unk54c, m_unk550, m_unk554};
        line.m_VectDir = CVector3{m_unk15d4 * 10.0f, m_unk15d8 * 10.0f, m_unk15dc * 10.0f};  // TOC +0x2a60
        CLineCollisionDatas hit;
        hit.m_ftOnLine = 0x1.fffffep+127f;  // the word at 0x00c4acb8 + 0x28 (FLT_MAX)
        hit.m_pCollisionMesh = nullptr;
        hit.m_i32FaceIndex = -1;
        hit.m_ui8SectorNumber = 0;
        blocked = collision->RaycastMeshes(&line, &hit, 1, 1, nullptr);  // 0x00197af8
        CGroundEdgeDatasOut edge;
        if (collision->RaycastWalls(&line, 0.0f, &edge, 0, nullptr, 1) != 0) blocked = 1;  // 0x00198438
    }
    auto refuse = [this]() -> uint8_t {
        m_unk1615 = 0;
        return 0;
    };
    if (m_unk1808 == 2 || partner->m_unk1808 != 2) return refuse();
    if ((m_unkec8 & 4u) != 0 || (m_unkec8 & 0x400u) != 0) return refuse();
    {
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_gcCurDatasInOut.m_pGround);  // +0x4b8
        if (!(GetHeightAboveGround() >= 1.0f) && ground != nullptr && ((ground->m_ba16EngineFlags >> 3) & 1u) == 0) {
            return refuse();
        }
    }
    // The partner's climb zone refuses the take-off when its body flag (CKHkClimbZone_GetLinkedObjectFlagC23_maybe
    // 0x456bc8) or its flag 0x800 (+0x0c) is set.
    if (partner->m_unk1694 != nullptr &&
        (partner->m_unk1694->GetLinkedObjectFlagC23() != 0 || (partner->m_unk1694->m_bitArray & 0x800u) != 0)) {
        return refuse();
    }
    if (blocked != 0) return refuse();
    if (m_unk1615 != 0) {
        if (IsAbilityActive() != 0) return m_unk1615;  // 0x002fc228
        if ((m_unkf08 == 3 || m_unkf08 == 1) && m_unk1808 == 0) return m_unk1615;
        m_unk1615 = 0;
        return 0;
    }
    bool join = false;
    // A running earth boulder (the ability +0x1cc0 of class 0x95cc, vt+0x08) joins at once (0x3426c4 -> 0x3424ec).
    if (IsAbilityActive() != 0 && m_unk1cc0->IsKindOfClass(0x95cc) != 0) {  // 0x002fc228
        join = true;
    } else if ((m_unked0 & 0x10000000u) != 0 && far != 0) {
        if (m_unk1808 != 0) SetMovementMode(0);  // inlined (1808, 180a, the game manager's notification)
        join = true;
    } else {
        const int8_t mode = static_cast<int8_t>(m_unk1808);
        if (mode == 0) {
            if (gap318 + gap314 > group->m_unk108 - slack) m_unk1615 = 0;  // 0x002ce518
            if ((m_unkec4 & 0x1000000u) != 0) {
                m_unkec4 &= ~0x1000000u;
                m_unk1615 = 1;
            }
        } else if (mode == 1) {
            if (m_unkf0c > m_unk978) {
                SetMovementMode(0);             // inlined (1808, 180a, the game manager's notification)
                UpdateGroundLocomotionState();  // 0x0031a040
                join = true;
            }
        }
        if (!join && m_unk1615 == 0) return 0;
    }
    if (join) m_unk1615 = 1;
    m_unked4 = (m_unked4 & ~0x20u) | 0x20u;
    {
        float gx = m_unk54c - partner->m_unk54c;
        float gy = m_unk550 - partner->m_unk550;
        float gz = m_unk554 - partner->m_unk554;
        const float length = std::sqrt(ppc::fmadds(gz, gz, ppc::fmadds(gx, gx, gy * gy)));
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            gz = gz * inv;
            gx = gx * inv;
            gy = gy * inv;
        }
        const CVector3 gap{gx, gy, gz};
        CVector3 dir = Vec3_ProjectOnPlane(reinterpret_cast<const CVector3*>(&m_unk15e0), &gap);  // 0x005840d0 (TocBridge)
        const float projected = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));
        if (projected != 0.0f) {
            const float inv = 1.0f / projected;
            dir.z = dir.z * inv;
            dir.x = dir.x * inv;
            dir.y = dir.y * inv;
        }
        // The push record +0x156c starts along it (the time left = its duration +0x1570, the last step 0).
        m_unk1578 = dir.x;
        m_unk1580 = dir.z;
        m_unk157c = dir.y;
        SetF32(m_unk1584, m_unk1570);
        SetF32(m_unk1588, 0.0f);
        m_unk1574 = 1;
    }
    m_unk1618 = 0.5f;  // TOC +0x2a50
    return m_unk1615;
}

// 0x00340f40 CKHkS08Hero_TryUseInteractable_maybe (vt+0x16c). A player's hero, not attached (+0x358 bit 0), takes its
// player's interaction target (the game manager's +0x2c8 slot, SetHeroInteractionTarget; a 0x1544 target stops it) into
// +0x98 / +0x9c unless +0x358 bit 14 holds the one it has, and uses it (vt+0xe0 CanAttachTo, then message 0x93f with the
// hero) on the action button (+0xef4 == 1), or a 0x2e02 target with +0x358 bit 21, or always with bit 14: +0x35c bit 30
// set and +0x364 bit 20 cleared / +0xf00 = 1 (the button) or +0x358 bit 21 cleared / +0xf28 = 1.
void CKHkS08Hero::TryUseInteractable() {
    if ((m_unk358 & 1u) != 0) return;
    if (m_ui8Hero != m_ui8TrackedLeader) return;
    CKS08GameManager::PlayerHudSlot& slot =
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->PlayerHudSlots()[m_ui8Leader];
    if (slot.m_pHero != nullptr) {
        if (slot.m_pHero->IsKindOfClass(0x1544) != 0) return;
        if (slot.m_pHero != nullptr && (m_unk358 & 0x4000u) == 0) {
            m_unk98 = slot.m_pHero;
            m_unk9c = slot.m_ui8Flag;
        }
    }
    uint8_t button = 0;  // r8
    uint32_t auto21 = 0;  // r10
    if (m_unk98 != nullptr && m_unk98->IsKindOfClass(0x2e02) != 0) {
        auto21 = 1;
    } else if (m_unkef4 == 1 && m_unk98 != nullptr) {
        button = 1;
    }
    auto21 &= (m_unk358 >> 21) & 1u;
    if ((m_unk358 & 0x4000u) == 0) {
        if (m_ui8TrackedLeader != m_ui8Hero) return;
        if (button == 0 && auto21 == 0) return;
    }
    if (CanAttachTo(m_unk98, static_cast<int32_t>(m_unk9c)) == 0) return;  // vt+0xe0
    m_unk98->MessageProc(0x93f, this);  // vt+0x1c
    if (auto21 != 0) {
        m_unk358 &= 0xffdfffffu;
        m_unk35c = (m_unk35c & 0xbfffffffu) | 0x40000000u;
        m_unkf28 = 1;
    } else {
        m_unk364 &= 0xffefffffu;
        m_unk35c = (m_unk35c & 0xbfffffffu) | 0x40000000u;
        m_unkf00 = 1;
    }
}

// 0x00342ef8 CKHkS08Hero_SetMovementModeUnlessLocked: SetMovementMode (0x340c18, inlined: the same stores and game
// manager notifications) unless the mode is locked (+0xec4 bit 8).
void CKHkS08Hero::SetMovementModeUnlessLocked(uint8_t mode) {
    if ((m_unkec4 & 0x100u) != 0) return;
    SetMovementMode(mode);
}

// ---- step 4 INPUT: the action input (vt+0xe4) and what it calls. ----
namespace {
// A float member the original reads through a word typed uint32_t here (the group's +0x2d4.. block).
float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}

// One button record of CKHkS08Hero_UpdateButtonRecords 0x3411d8 (inlined ten times): the previous held time, the
// game manager's held time of the record's action (vt+0x164), the consumed byte cleared, then the state from the
// pressed byte (vt+0x160): 1 pressed, 3 held (a time above 0), 2 released (was 1 or 3), else 0.
void UpdateButtonRecord(CKS08GameManager* manager, uint8_t player, uint32_t word, uint32_t& state, float& value,
                        float& previous, uint8_t& consumed) {
    previous = value;
    const uint8_t action = static_cast<uint8_t>(word);  // lbz +0x3: the word's low byte
    value = manager->GetActionValue(action, player);
    consumed = 0;
    if (manager->IsActionPressed(action, player) != 0) {
        state = 1;
    } else if (value <= 0.0f) {  // TOC +0x29f4; ble: a NaN time is held
        state = (state == 1 || state == 3) ? 2u : 0u;
    } else {
        state = 3;
    }
}

// The arc cosine of a dot product clamped to [-1, 1] (inlined four times in UpdateGuardAndDodgeInput).
float ClampedAcos(float dot) {
    if (dot <= -1.0f) {  // TOC +0x29fc; cror lt|eq
        dot = -1.0f;
    } else if (dot >= 1.0f) {  // TOC +0x29e8; cror gt|eq
        dot = 1.0f;
    }
    return crt::Acosf(dot);  // TocBridge_Math_Acosf 0x98e1a0
}

// 0x00301348 CKHkS08Hero_IsInSpecialAnim_maybe (local copy; CKHkS08Hero_3.cpp): the animation (+0x160) is one of
// 0x33, 0x36, 0x3a, 0x3d, 0x41, 0x43, 0x44.
uint8_t IsInSpecialAnim(const CKHkS08Hero* hero) {
    const int16_t animation = static_cast<int16_t>(hero->m_unk160);
    switch (animation) {
    case 0x33: case 0x36: case 0x3a: case 0x3d: case 0x41: case 0x43: case 0x44: return 1;
    default: return 0;
    }
}

}  // namespace

// 0x003445d8 CKHkS08Hero_UpdateActionInput (vt+0xe4): the button records, the movement mode, guard / dodge, the health and
// mana sharing, the input 7 hold (+0x180c, +0x1810: released within the group's +0x174, one controlled hero only), the
// carried power bucket, the attack queue and element, the input 4 hold (+0x1304 / +0x1305, its time +0x1308), the air
// action and the flight flap.
void CKHkS08Hero::UpdateHeroActionInput() {
    UpdateButtonRecords();                     // 0x003411d8
    UpdateMovementModeFromInput();             // 0x003438b0
    UpdateGuardAndDodgeInput();                // 0x00342808
    UpdateHeroHealthAndManaSharing(m_unk88c);  // 0x003408f8
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const float held7 = manager->GetActionValue(7, m_ui8Leader);  // vt+0x164
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (group->m_ui8ControlledHeroCount == 1) {  // 0x002ca288 GetControlledHeroCount
        if (m_unk36c[7] != 0 || held7 > 0.0f) {  // TOC +0x29f4
            m_unk180c = held7;
            m_unk1810 = 0;
        } else {
            if (m_unk180c != 0.0f) m_unk1810 = group->m_unk174 >= m_unk180c ? 1 : 0;
            m_unk180c = 0.0f;
        }
    }
    UpdateCarriedPowerBucketGroundTrigger();  // 0x00340a20
    QueueAttackInputAndSelectElement();       // 0x00330ab8
    const float held4 = m_unk388;
    m_unk1305 = m_unk1304;
    m_unk1304 = held4 > 0.0f ? 1 : 0;
    if (m_unk1304 != 0 || m_unk1305 == 0) m_unk1308 = held4;
    HandleAirborneActionCInput();  // 0x003430a8
    UpdateFlightFlapImpulse();     // 0x003402a0 (a tail call)
}

// 0x003411d8 CKHkS08Hero_UpdateButtonRecords: the ten button records (+0xef0, 0x14 each) from the game manager's
// actions of the player (+0x26); all cleared while the group blocks input (+0xf8 bit 3) unless the ground animation
// sub-state (+0x1960) is 10. A hero that is not its own tracked leader loses +0x358 bit 20 first.
void CKHkS08Hero::UpdateButtonRecords() {
    if (m_ui8Hero != m_ui8TrackedLeader) m_unk358 &= 0xffefffffu;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    if (((group->m_unkf8 >> 3) & 1u) != 0 && m_unk1960 != 10) {  // 0x002ca258 CKGrpS08Hero_IsInputBlocked_maybe
        m_unkef4 = 0;
        m_unkefc = 0.0f;
        m_unkf00 = 0;
        m_unkef8 = 0.0f;
        m_unkf08 = 0;
        m_unkf10 = 0.0f;
        m_unkf14 = 0;
        m_unkf0c = 0.0f;
        m_unkf1c = 0;
        m_unkf24 = 0.0f;
        m_unkf28 = 0;
        m_unkf20 = 0.0f;
        m_unkf30 = 0;
        m_unkf38 = 0.0f;
        m_unkf3c = 0;
        m_unkf34 = 0.0f;
        m_unkf44 = 0;
        m_unkf4c = 0.0f;
        m_unkf50 = 0;
        m_unkf48 = 0.0f;
        m_unkf58 = 0;
        m_unkf60 = 0.0f;
        m_unkf64 = 0;
        m_unkf5c = 0.0f;
        m_unkf6c = 0;
        m_unkf74 = 0.0f;
        m_unkf78 = 0;
        m_unkf70 = 0.0f;
        m_unkf80 = 0;
        m_unkf88 = 0.0f;
        m_unkf8c = 0;
        m_unkf84 = 0.0f;
        m_unkf94 = 0;
        m_unkfa0 = 0;
        m_unkf9c = 0.0f;
        m_unkf98 = 0.0f;
        m_unkfb0 = 0.0f;
        m_unkfb4 = 0;
        m_unkfa8 = 0;
        m_unkfac = 0.0f;
        return;
    }
    const uint8_t player = m_ui8Leader;
    UpdateButtonRecord(manager, player, m_unkef0, m_unkef4, m_unkef8, m_unkefc, m_unkf00);
    UpdateButtonRecord(manager, player, m_unkf04, m_unkf08, m_unkf0c, m_unkf10, m_unkf14);
    UpdateButtonRecord(manager, player, m_unkf18, m_unkf1c, m_unkf20, m_unkf24, m_unkf28);
    UpdateButtonRecord(manager, player, m_unkf2c, m_unkf30, m_unkf34, m_unkf38, m_unkf3c);
    UpdateButtonRecord(manager, player, m_unkf40, m_unkf44, m_unkf48, m_unkf4c, m_unkf50);
    UpdateButtonRecord(manager, player, m_unkf54, m_unkf58, m_unkf5c, m_unkf60, m_unkf64);
    UpdateButtonRecord(manager, player, m_unkf68, m_unkf6c, m_unkf70, m_unkf74, m_unkf78);
    UpdateButtonRecord(manager, player, m_unkf7c, m_unkf80, m_unkf84, m_unkf88, m_unkf8c);
    UpdateButtonRecord(manager, player, m_unkf90, m_unkf94, m_unkf98, m_unkf9c, m_unkfa0);
    UpdateButtonRecord(manager, player, m_unkfa4, m_unkfa8, m_unkfac, m_unkfb0, m_unkfb4);
    if (m_unk1808 == 1) {
        // With the pad's motion sensor on (the player's pad record, IKGameManager_IsMotionSensorEnabled 0x13530; off in
        // the default options) the flight steers from the pad's tilt: the input bytes of the logical inputs 2 / 3 / 0 /
        // 1 (the group's vt+0x118) become Math_RemapClamped of 4 times the sensor bytes +0x2a / +0x2b / +0x28 / +0x29 of
        // the pad's state (vt+0x30) plus the input byte, over 30..180 / 30..180 / 0..40 / 40..128 into 0..255 (the low
        // 16 bits of the integer part; above 0xfe: 0xff).
        PS3PadDevice* pad = g_pEngine->m_input->GetPad(m_ui8Leader);  // 0x001052d8
        if (pad != nullptr && manager->IsMotionSensorEnabled(m_ui8Leader) != 0) {  // 0x00013530
            const uint8_t* state = pad->GetCurrentState();  // vt+0x30
            IKGrpHero* heroGroup = static_cast<IKGrpHero*>(m_pGrpHero);
            struct Axis {
                uint8_t input;
                uint8_t sensor;
                float lo;
                float hi;
            };
            const Axis axes[4] = {{2, 0x2a, 30.0f, 180.0f}, {3, 0x2b, 30.0f, 180.0f}, {0, 0x28, 0.0f, 40.0f},
                                  {1, 0x29, 40.0f, 128.0f}};  // TOC +0x2a3c / +0x2a40 / +0x29f4 / +0x2a48 / +0x2a4c
            for (const Axis& axis : axes) {
                const int32_t raw = static_cast<int32_t>(state[axis.sensor]) * 4 +
                                    m_unk36c[heroGroup->GetInputAction(axis.input)];  // vt+0x118
                const float mapped = Math_RemapClamped(axis.lo, axis.hi, static_cast<float>(static_cast<double>(raw)), 0.0f,
                                                       255.0f);  // 0x00333618; TOC +0x2a44
                const uint16_t low = static_cast<uint16_t>(ppc::fctiwz(mapped));
                const uint8_t byte = static_cast<int16_t>(low) > 0xfe ? 0xff : static_cast<uint8_t>(low);
                m_unk36c[heroGroup->GetInputAction(axis.input)] = byte;  // vt+0x118
            }
        }
    }
}

// The climbing part of 0x003438b0 CKHkS08Hero_UpdateMovementModeFromInput (inline there; step 6 CLIMB): a press in
// reach of a zone (+0x1676) attaches the hero to it (AttachClimberIfValid 0x4591e0 into the attach target +0x16d8, the
// node's matrix kept in +0x16d4) or lets it go (RemoveClimber 0x457180). A hero below a ledge top (the target upright,
// unchanged, the zone flagged +0xc bit 18 with a ground) gets +0xec8 bit 31. Not climbing yet: the climbing mode and the
// mount start (+0x1677, +0x1750 = -1, +0x174c); climbing: a leap (+0x1628) restarts the mount, else the hero drops to the
// ground mode (+0xed8 bit 19, +0xed0 bit 28).
void CKHkS08Hero::StartClimbFromInput() {
    const CMatrix34* target = m_unk16d8;
    const float sx = target->m_pos.x;
    const float sy = target->m_pos.y;
    const float sz = target->m_pos.z;
    if (m_unk1694 == nullptr) return;
    const int32_t key = CKHkClimbZone::ClimberKey(this);
    if (m_unk1694->AttachClimberIfValid(m_unkd18 + m_unkd18, reinterpret_cast<const CVector3*>(&m_unk54c), m_unk16d8, key) == 0) {
        if (m_unk1694 != nullptr) m_unk1694->RemoveClimber(key);
        return;
    }
    *m_unk16d4 = *reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling);
    m_unk1748 = 0.0f;
    const auto climbHeld = [this]() {
        return (m_unk1677 != 0 || m_unk1676 != 0 || m_unk1679 != 0 || m_unk1678 != 0 || (m_unkec8 & 1u) != 0) && m_unk1629 == 0;
    };
    bool topCheck = true;
    if (m_unk1808 == 2) {
        if (!climbHeld()) {
            SetMovementMode(0);  // inlined (from 2)
        } else {
            topCheck = false;
            m_unkec8 &= 0x7fffffffu;
        }
    }
    if (topCheck) {
        const CMatrix34& t = *m_unk16d8;
        const CVector3& axis = kHeroAxisY;  // TOC +0x2a70
        const bool top = !(t.m_pos.y >= m_unk550) && t.m_at.x == axis.x && t.m_at.y == axis.y && t.m_at.z == axis.z &&
                         t.m_pos.x == sx && t.m_pos.y == sy && t.m_pos.z == sz && (m_unk1694->m_bitArray & 0x40000u) != 0 &&
                         m_unk1694->m_pUnk50 != nullptr && (m_unk354 & 1u) == 0;
        m_unkec8 = top ? ((m_unkec8 & 0x7fffffffu) | 0x80000000u) : (m_unkec8 & 0x7fffffffu);
    }
    if (m_unk1808 == 2) {
        if (climbHeld()) {
            if (m_unk1628 != 0) {
                m_unk167d = 1;
                m_unk1750 = -1.0f;  // TOC +0x29fc
                m_unk174c = m_unkd0c;
                m_unk1677 = 1;
                return;
            }
            SetMovementMode(0);  // inlined
        } else {
            SetMovementMode(0);  // inlined
        }
        m_unked8 = (m_unked8 & 0xfff7ffffu) | 0x80000u;
        m_unked0 = (m_unked0 & 0xefffffffu) | 0x10000000u;
        return;
    }
    SetMovementMode(2);  // inlined
    m_unk1677 = 1;
    m_unk167d = 0;
    m_unk1750 = -1.0f;  // TOC +0x29fc
    m_unk174c = m_unkd0c;
}

// 0x003438b0 CKHkS08Hero_UpdateMovementModeFromInput: the movement mode from the ground and the buttons. On a ground of
// property 0x200 within +0x8e8 (+0xec4 bit 18) the hero flies (from climbing only when no climb holds it); the jump
// press timers +0x1748 / +0x174c run up to +0xd08 / +0xd0c; a press of record 0 (or within +0xd0c of it, or held with
// +0x1628) restarts +0x174c (climbing starts here when +0x1676: step 6); +0xecc bit 20 lands a hero off such a ground;
// +0xf00 / +0xf14 consume records 0 / 1 for the climb (record 1 leaps off a wall into flight); +0xecc bit 15 drops a
// climb; the game manager's flight request (+0xe10 of the hero's record) flies; an airborne hero on foot whose partner
// climbs and that the tether can no longer hold (the group's +0x314 + +0x318 above its +0x108 less 3) joins it in the air.
void CKHkS08Hero::UpdateMovementModeFromInput() {
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    m_unkec4 &= 0xfffbffffu;
    if (ground != nullptr && (m_unkec8 & 0x400u) == 0 && (ground->m_ui16PropertiesFlags & 0x200u) != 0 &&
        !(m_gcCurDatasInOut.m_fdH >= m_unk8e8)) {  // +0x4dc; bge
        m_unkec4 |= 0x40000u;
        bool fly = true;
        if ((ground->m_ba16EngineFlags & 2u) != 0 && m_unk1808 == 2) {
            const bool climbHeld = m_unk1677 != 0 || m_unk1676 != 0 || m_unk1679 != 0 || m_unk1678 != 0 ||
                                   (m_unkec8 & 1u) != 0;
            if (climbHeld && m_unk1629 == 0) {
                fly = false;
            } else {
                SetMovementMode(0);  // inlined: from climbing (2) to the ground, then on to flying below
            }
        }
        if (fly) SetMovementMode(1);  // inlined (+0x1809 from the ground)
    }
    const float jumpWindow = m_unkd08;
    const float pressWindow = m_unkd0c;
    if (jumpWindow >= m_unk1748) m_unk1748 = m_unk1748 + m_unk88c;  // cror gt|eq
    if (pressWindow >= m_unk174c) m_unk174c = m_unk174c + m_unk88c;
    const bool press = m_unkef4 == 1 || !(m_unk174c >= pressWindow) ||
                       (m_unkef4 == 3 && m_unk1628 != 0 && m_unk1678 == 0);
    if (press && m_unk1748 > jumpWindow && static_cast<int32_t>(m_unkec8) >= 0 && (m_unkec8 & 1u) == 0 &&
        m_unk1678 == 0 && m_unk1ac4 == 0) {
        bool proceed = true;
        if (m_unk1694 != nullptr && m_unk1694->m_unk34 == 1) {
            // On a climb zone of kind 1 a flying hero in a special animation (IsInSpecialAnim 0x301348) or with +0xec8
            // bit 1 stops here.
            if (m_unk1808 == 1 && (IsInSpecialAnim(this) != 0 || (m_unkec8 & 2u) != 0)) proceed = false;
        }
        if (proceed) {
            const uint8_t locked = static_cast<uint8_t>((m_unked4 >> 3) & 1u);  // 0x0032a428 GetFlagED4Bit3
            if (m_unk1676 != 0 && locked == 0) {
                StartClimbFromInput();  // step 6 CLIMB: the zone in reach (+0x1676) takes the hero
            } else if (m_unkef4 == 1 && ((m_unked4 >> 3) & 1u) == 0) {
                m_unk174c = 0.0f;
            }
        }
    }
    if ((m_unkecc & 0x100000u) != 0) {
        m_unkecc &= 0xffefffffu;
        if ((m_unkec4 & 0x40000u) == 0) SetMovementMode(0);  // inlined (only from another mode)
    }
    if (m_unk1677 != 0) {
        // The climb starts: +0x1744 from the zone's kind (1 -> 1, 0 -> 2, 2 -> 0, else 3) and the approach +0x1740
        // (ClassifyClimbZoneApproach 0x321080 with the attach target's at and right rows).
        if (m_unk1694 != nullptr) {
            const uint8_t kind = m_unk1694->m_unk34;
            m_unk1744 = kind == 1 ? 1u : kind == 0 ? 2u : kind == 2 ? 0u : 3u;
        }
        m_unk1740 = ClassifyClimbZoneApproach(&m_unk16d8->m_at, &m_unk16d8->m_right);  // 0x00321080
    }
    uint8_t mode = m_unk1808;
    m_unkf00 = (m_unkef4 == 1 && (mode == 2 || m_unk1676 != 0)) ? 1 : 0;
    if (static_cast<int8_t>(mode) == 2 && m_unk1628 != 0 && m_unkf08 == 1 && m_unk1694 == 0) {
        SetMovementMode(1);  // inlined (from climbing: no +0x1809)
        mode = m_unk1808;
        m_unkf14 = 1;
    } else {
        m_unkf14 = 0;
    }
    if (static_cast<int8_t>(mode) == 2 && (m_unkecc & 0x8000u) != 0) {
        SetMovementMode(0);  // inlined
        m_unkecc &= 0xffff7fffu;
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    // The game manager's record of this hero (+0xdf8 + hero * 0x20; CKHkS08Hero_2.cpp's layout): its byte +0xe10.
    const uint32_t* record = &manager->m_unkDF4[1 + m_ui8Hero * 8];
    const uint8_t flightRequest = reinterpret_cast<const uint8_t*>(&record[6])[0];
    uint8_t partnerClimbs;
    if (flightRequest != 0 && (m_unkec8 & 0x400u) == 0) {
        SetMovementMode(1);  // inlined
        m_unk1440 = 0;
        partnerClimbs = PartnerShouldStayClimbing();  // 0x002f8628
    } else {
        partnerClimbs = PartnerShouldStayClimbing();
    }
    if (partnerClimbs != 0) {
        CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
        if (partner->m_unk1744 != 0 && partner->m_unk1744 == 2 && m_unk1808 != 2 && GetPartnerHero()->m_unk1694 != nullptr) {
            (void)GetPartnerHero()->m_unk1694->GetLinkedObjectFlagC23();  // 0x00456bc8 (its answer is not used)
        }
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const float distance318 = WordAsFloat(group->m_unk318);
    const float distance314 = WordAsFloat(group->m_unk2d4[16]);  // +0x314
    if (m_unk1615 != 0 || (m_unkec8 & 0x400u) != 0 || (m_unk354 & 1u) == 0 || m_unk1808 != 0) return;
    if (PartnerShouldStayClimbing() == 0) return;
    if ((m_unkec8 & 4u) != 0 || (m_unkec4 & 0x1000000u) != 0) return;
    const float reach = group->m_unk108 - 3.0f;  // 0x002ce518 CKGrpS08Hero_GetMaxPartnerDistance_maybe; TOC +0x2a78
    if (distance318 + distance314 <= reach) return;
    SetMovementMode(1);  // inlined
    UpdateFlyingLocomotion(m_unk88c);  // 0x003167e0 (reached only while the partner climbs)
}

// 0x00342808 CKHkS08Hero_UpdateGuardAndDodgeInput: record 6 (+0xf6c, pressed or held) with +0xec8 bit 4 arms the dodge
// (+0xec8 bits 2 / 21, and 22 / 23 on foot); a dodge armed on foot picks its direction from the move direction against
// the facing (+0x1228: 0 ahead, 1 behind within +0xe6c degrees, 2 / 3 to a side within 180 - +0xe6c, else 4) when the
// stick is pushed past +0xe70, sets +0xec8 bit 1 and the dodge vector +0x11cc (the move direction turned to the kind);
// in the air the ahead / behind kinds request a landing (+0xecc bit 19) or end the flight. +0xec8 bit 21 is the dodge
// held; +0xecc bit 19 is also set when record 1 is pressed during an armed dodge.
void CKHkS08Hero::UpdateGuardAndDodgeInput() {
    if (ShouldJoinPartnerFlight() != 0) return;  // 0x00341fa0
    const uint32_t cleared = m_unkec8 & 0xffdfffffu;
    m_unkec8 = cleared;
    uint32_t flags;
    if ((m_unkf6c == 3 || m_unkf6c == 1) && (m_unkec8 & 0x10u) != 0) {
        flags = cleared | 0x200000u | 4u;
        m_unkec8 = flags;
        if (m_unk1808 != 1) m_unkec8 = flags | 0x400000u | 0x800000u;
        flags = m_unkec8;
    } else {
        flags = m_unkec8;
        if ((flags & 2u) == 0) {
            m_unkec8 = cleared & 0xfffffffbu;
            flags = m_unkec8;
        }
    }
    if ((flags & 2u) != 0) {
        if ((flags & 0x100000u) != 0 && (flags & 0x200000u) == 0) {
            m_unkec4 &= 0xffdfd3ffu;
            m_unk354 &= 0xfffff7ffu;
            flags = m_unkec8;
        }
        if ((flags & 0x100000u) != 0 && (flags & 0x200000u) != 0) {
            m_unkec8 = (m_unkec8 & 0xfffffff7u) | 8u;
            flags = m_unkec8;
        }
    }
    bool dodge = false;
    if ((flags & 4u) != 0 && (flags & 8u) != 0) {
        if ((flags & 2u) != 0 && (flags & 0x100000u) == 0) {
            dodge = false;  // straight to the request test below
        } else if ((flags & 0x200000u) == 0) {
            if ((flags & 2u) == 0) m_unk1228 = 4;
        } else {
            dodge = true;
        }
    } else if ((flags & 2u) == 0) {
        m_unk1228 = 4;
    }
    if (dodge) {
        if (m_unk1808 == 0) {
            m_unkec4 |= 0x200000u | 0x800u | 0x400u | 0x2000u;
            m_unk354 |= 0x800u;
        }
        if (!(m_unk1378 < m_unke70)) {
            constexpr float kHalf = 0.5f;                       // TOC +0x2a50
            constexpr float kDegToRad = 0.017453290522098541f;  // TOC +0x2a68 (0x3c8efa34)
            const float ahead = ClampedAcos(ppc::fmadds(m_unk384, m_unk1364, ppc::fmadds(m_unk37c, m_unk135c, m_unk380 * m_unk1360)));
            const float aheadLimit = m_unke6c * kHalf * kDegToRad;
            int32_t kind = -1;  // -1: not chosen here
            bool done = false;
            if (!(aheadLimit <= ahead)) {
                if (static_cast<int8_t>(m_unk1808) == 0) {
                    kind = 0;
                } else {
                    done = true;
                    if ((m_unkec4 & 0x40000u) == 0) {
                        m_unk1228 = 0;
                        m_unkec8 = (m_unkec8 & 0xfffffffdu) | 2u;
                        m_unk122c = 0.0f;
                        SetMovementMode(0);  // inlined
                        m_unk354 = (m_unk354 & 0xfffff7ffu) | 0x800u;
                    }
                }
            } else {
                const float behind = ClampedAcos(ppc::fmadds(-m_unk1364, m_unk384, ppc::fmsubs(-m_unk1360, m_unk380, m_unk135c * m_unk37c)));
                const float behindLimit = m_unke6c * kHalf * kDegToRad;
                if (!(behindLimit <= behind)) {
                    if (static_cast<int8_t>(m_unk1808) == 0) {
                        kind = 1;
                    } else {
                        done = true;
                        if (static_cast<int8_t>(m_unk1808) == 1 && (m_unkec4 & 0x40000u) == 0) {
                            m_unkecc = (m_unkecc & 0xfff7ffffu) | 0x80000u;
                        } else {
                            m_unk1228 = 4;
                        }
                    }
                } else {
                    const float right = ClampedAcos(ppc::fmadds(m_unk384, m_unk1370, ppc::fmadds(m_unk37c, m_unk1368, m_unk380 * m_unk136c)));
                    const float sideLimit = (180.0f - m_unke6c) * kHalf * kDegToRad;  // TOC +0x2a40
                    if (sideLimit > right) {
                        kind = 2;
                    } else {
                        const float left = ClampedAcos(ppc::fmadds(-m_unk1370, m_unk384, ppc::fmsubs(-m_unk136c, m_unk380, m_unk1368 * m_unk37c)));
                        const float sideLimit2 = (180.0f - m_unke6c) * kHalf * kDegToRad;
                        if (sideLimit2 > left) {
                            kind = 3;
                        } else {
                            done = true;
                            m_unk1228 = 4;
                        }
                    }
                }
            }
            if (!done && kind >= 0) {
                m_unk1228 = static_cast<uint8_t>(kind);
                m_unkec8 = (m_unkec8 & 0xfffffffdu) | 2u;
                m_unk122c = 0.0f;
            }
        }
        flags = m_unkec8;
        if ((flags & 2u) != 0) {
            const float x = m_unk37c;
            const float y = m_unk380;
            const float z = m_unk384;
            m_unk1248 = x;
            m_unk1250 = z;
            m_unk124c = y;
            float ox, oy, oz;
            switch (m_unk1228) {
            case 0: ox = x; oy = y; oz = z; break;
            case 1: ox = -x; oy = -y; oz = -z; break;
            case 2: ox = -z; oy = 0.0f; oz = x; break;  // TOC +0x29f4
            case 3: ox = z; oy = 0.0f; oz = -x; break;
            default: ox = m_unk135c; oy = m_unk1360; oz = m_unk1364; break;
            }
            m_unk11cc = ox;
            m_unk11d4 = oz;
            m_unk11d0 = oy;
            m_unkec8 = (m_unkec8 & 0xff3fffffu) | 0xc00000u;
            flags = m_unkec8;
        }
    }
    if ((flags & 4u) == 0 || (flags & 8u) == 0) return;
    if ((flags & 2u) != 0) {
        if ((flags & 0x100000u) == 0 || (flags & 0x200000u) == 0) return;
    } else if ((flags & 0x200000u) == 0) {
        return;
    }
    if ((m_unkec4 & 0x40000u) != 0 || m_unkf08 != 1) return;
    m_unkecc = (m_unkecc & 0xfff7ffffu) | 0x80000u;
}

// 0x003430a8 CKHkS08Hero_UpdateAirWallAction_maybe: the air action of record 0. Its cooldown +0x143c runs down;
// a running action (+0x13d8) ends on a new press after the cooldown or near the ground (below +0x9e0). A press high
// enough above a ground, not aiming at an enemy (group flag 0x400) and without +0xed0 bit 28, restarts the cooldown
// (+0x9dc) and probes +0x9cc to the right then the left (or along -up for the climb kinds 6 / 7) against the walls: a
// wall of property 0x100 that the probe slid along starts the action (+0x13d8, +0x13d9 the left side, the wall's normal
// +0x13dc and its tangent +0x13e8, the speeds +0x1414 / +0x1418, +0x141c / +0x1420 / +0x142c) and the flight.
void CKHkS08Hero::HandleAirborneActionCInput() {
    bool aimed = false;
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    if ((group->m_unkf8 & 0x400u) != 0) {
        const float length =
            std::sqrt(ppc::fmadds(m_unk1364, m_unk1364, ppc::fmadds(m_unk135c, m_unk135c, m_unk1360 * m_unk1360)));
        if (!(length <= 0.1f)) {  // TOC +0x2a6c; ble
            const CVector3 facing{m_unk135c, m_unk1360, m_unk1364};
            aimed = FindBestEnemyInAimCone(m_unk1d38, &facing) != nullptr;  // 0x002fe5b8
        }
    }
    if (m_unk143c > 0.0f) m_unk143c = m_unk143c - m_unk88c;  // TOC +0x29f4; ble
    if (m_unk13d8 != 0) {
        bool end;
        if (m_unkef4 == 1 && m_unk143c <= 0.0f) {
            end = true;
        } else {
            end = !(m_unk9e0 <= GetHeightAboveGround());  // 0x0032a008; ble
        }
        if (end) {
            m_unk143c = m_unk9dc;
            m_unk13d9 = 0;
            m_unk13d8 = 0;
            return;
        }
    }
    if (m_unkef4 != 1 || m_unk13d8 != 0) return;
    if (!(m_unk143c <= 0.0f)) return;
    if (m_unk1677 != 0) return;
    if (m_unk9e0 >= GetHeightAboveGround()) return;
    if (aimed) return;
    if ((m_unked0 & 0x10000000u) != 0) return;
    m_unk143c = m_unk9dc;
    if (GetGroundInfo() == nullptr) return;  // 0x00361b68
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2a38
    float d1x = zero.x, d1y = zero.y, d1z = zero.z;  // f30, f11, f29
    float d2x, d2y, d2z;                              // f28, f27, f26
    bool alongRight = true;
    if (m_unk1808 == 2) {
        const bool climbHeld = m_unk1677 != 0 || m_unk1676 != 0 || m_unk1679 != 0 || m_unk1678 != 0 || (m_unkec8 & 1u) != 0;
        if (climbHeld && m_unk1629 == 0) {
            alongRight = false;
            d2x = d1x;
            d2y = d1y;
            d2z = d1z;
            const RwV3d& up = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.up;
            if (m_unk1664 == 6) {
                d1z = -up.z;
                d1x = -up.x;
                d1y = -up.y;
            } else if (m_unk1664 == 7) {
                d2z = -up.z;
                d2x = -up.x;
                d2y = -up.y;
            }
        } else {
            SetMovementMode(0);  // inlined
        }
    }
    if (alongRight) {
        const RwV3d& right = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.right;
        d1x = right.x;
        d1z = right.z;
        const float length = std::sqrt(ppc::fmadds(d1z, d1z, ppc::fmadds(d1x, d1x, 0.0f)));  // Math_Sqrtf 0x10690
        if (length != 0.0f) {
            const float inverse = 1.0f / length;  // TOC +0x29e8
            d1y = inverse * 0.0f;
            d1z = d1z * inverse;
            d1x = d1x * inverse;
            d2y = -d1y;
        } else {
            d1y = 0.0f;
            d2y = -0.0f;  // TOC +0x2a74
        }
        d2x = -d1x;
        d2z = -d1z;
    }
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CGroundContactDatasInOut contact;  // ground 0, face -1, status 3, sector 0 (the stack copy, reused by both probes)
    // BUG(original): the slide result is a stack copy that ResolveWallSegmentMovement leaves unwritten when it finds
    // no wall (0), and the probe point then adds that garbage; such a probe cannot succeed (it needs 2), but its ground
    // can stay in the shared contact. Zero here (the PS3 stack content is not reproducible).
    CSlideGroundEdgeDatasOut slide{};
    const auto probe = [&](float dx, float dy, float dz) -> bool {
        const float reach = m_unk9cc;
        const float mz = reach * dz;
        const float mx = reach * dx;
        const float my = reach * dy;
        CLine line;
        line.m_start = {m_unk54c, m_unk550, m_unk554};
        line.m_VectDir = {mx, my, mz};
        const uint8_t result = collision->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr, nullptr, 1);  // 0x001996b0
        CVector3 point;
        point.x = (m_unk54c + mx) + slide.m_v3BouncingVector.x;
        point.y = (m_unk550 + my) + slide.m_v3BouncingVector.y;
        point.z = (m_unk554 + mz) + slide.m_v3BouncingVector.z;
        GroundContact_ProbeGroundPoint(&contact, &point, nullptr);  // 0x00583ef8
        const ICollisionMesh* wall = static_cast<const ICollisionMesh*>(contact.m_pGround);
        return wall != nullptr && (wall->m_ui16PropertiesFlags & 0x100u) != 0 && result == 2;
    };
    uint8_t leftSide;
    if (probe(d1x, d1y, d1z)) {
        leftSide = 0;
        const CVector3 n = slide.m_v3Normal;
        m_unk13d9 = 0;
        m_unk13d8 = 1;
        m_unk13dc = n.x;
        m_unk13e0 = n.y;
        m_unk13e4 = n.z;
        m_unk13e8 = n.z;  // the store of -nz is overwritten
        m_unk13ec = -0.0f;
        m_unk13f0 = -m_unk13dc;
    } else if (probe(d2x, d2y, d2z)) {
        leftSide = 1;
        const CVector3 n = slide.m_v3Normal;
        m_unk13d8 = 1;
        m_unk13d9 = 1;
        m_unk13dc = n.x;
        m_unk13e0 = n.y;
        m_unk13e4 = n.z;
        m_unk13e8 = -n.z;
        m_unk13ec = 0.0f;
        m_unk13f0 = m_unk13dc;
    } else {
        return;
    }
    (void)leftSide;
    m_unk1418 = m_unk9d8;
    m_unk1414 = m_unk9d4;
    m_unk1420 = kHeroAxisY.x;  // TOC +0x2a70
    m_unk1428 = kHeroAxisY.z;
    m_unk1424 = kHeroAxisY.y;
    m_unk141c = 0;
    m_unk142c = 0.0f;
    m_unk1430 = 0.0f;
    m_unk1420 = kHeroAxisY.x;
    m_unk1428 = kHeroAxisY.z;
    m_unk1424 = kHeroAxisY.y;
    m_unk142c = m_unk1418;
    m_unk1430 = 0.0f;
    m_unk141c = 1;
    SetMovementMode(1);  // inlined (+0x1809 from the ground)
}

// 0x00340a20 CKHkS08Hero_UpdateCarriedPowerBucketGroundTrigger_maybe: +0xecc bit 21 cleared, set while flying over a
// ground of property 0x200 with engine flag 2 carrying an empty power bucket (its vt+0x190, 0x004d33a8: the byte +0x1f0);
// the action button (record 2, +0xf1c) then fires the group's +0xab0 signals and puts the hero's index into +0xab8.
// +0xec8 bit 16 is set while +0x1258 (the carried object's weight) is not 0.
void CKHkS08Hero::UpdateCarriedPowerBucketGroundTrigger() {
    m_unkecc &= 0xffdfffffu;
    CKS08CarrierHero* carrier = static_cast<CKS08CarrierHero*>(m_unkfb8);
    if (carrier != nullptr) {
        IKSerializable* carried = carrier->GetCarriedObject();  // vt+0x80
        if (carried != nullptr && carried->IsKindOfClass(0x30c2) != 0) {  // vt+0x8
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
            if ((static_cast<CKHkS08PowerBucket*>(carried)->m_unk1f0 >> 24) == 0 && ground != nullptr &&  // vt+0x190
                (ground->m_ui16PropertiesFlags & 0x200u) != 0 && (ground->m_ba16EngineFlags & 2u) != 0 &&
                m_unk1808 == 1) {
                m_unkecc = (m_unkecc & 0xffdfffffu) | 0x200000u;
                if (m_unkf1c == 1) {
                    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
                    QueueTriggerSignals(&group->m_tsUnkab0);  // 0x00236338
                    group->m_unkab8 = m_ui8Hero;
                }
            }
        }
    }
    if (m_unk1258 == 0.0f) {  // TOC +0x29f4
        m_unkec8 &= 0xfffeffffu;
    } else {
        m_unkec8 = (m_unkec8 & 0xfffeffffu) | 0x10000u;
    }
}

// 0x003402a0 CKHkS08Hero_UpdateFlightFlapImpulse_maybe: +0x13cc cleared; the impulsion component (+0x1190) works only
// while flying (no +0x13cd, +0x354 bit 11, +0x35c bit 1), else its state (+0x24..+0x2c) is cleared.
void CKHkS08Hero::UpdateFlightFlapImpulse() {
    m_unk13cc = 0;
    if (m_unk1808 == 1 && m_unk13cd == 0 && (m_unk354 & 0x800u) == 0 && (m_unk35c & 2u) == 0) {
        // The flap: the component runs with the frame's dt, record 1 pressed gives an impulse (1.0); +0xecc bit 11 while
        // its value is above +0xa70; above +0xa74 its state is cleared, +0x13cc set (the flight's push), +0xecc bit 11
        // and +0xec4 bit 19 cleared.
        CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(m_unk1190);
        impulsion->Update(m_unk88c);  // 0x0024bd40
        if (m_unkf08 == 1) static_cast<CKImpulsionCpnt*>(m_unk1190)->Impulse(1.0f);  // 0x0024bce0; TOC +0x29e8
        impulsion = static_cast<CKImpulsionCpnt*>(m_unk1190);
        if (impulsion->m_unk24 > m_unka70) {
            m_unkecc = (m_unkecc & ~0x800u) | 0x800u;
        } else {
            m_unkecc &= ~0x800u;
        }
        impulsion = static_cast<CKImpulsionCpnt*>(m_unk1190);
        if (impulsion->m_unk24 > m_unka74) {
            impulsion->m_unk2c = 0;
            impulsion->m_unk24 = 0;
            impulsion->m_unk28 = 0;
            m_unk13cc = 1;
            m_unkecc &= ~0x800u;
            m_unkec4 &= ~0x80000u;
        }
        return;
    }
    CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(m_unk1190);
    impulsion->m_unk2c = 0;
    impulsion->m_unk24 = 0;
    impulsion->m_unk28 = 0;
}

// 0x003408f8 UpdateHeroHealthAndManaSharing: with two controlled heroes and record 7 held, record 8 held shares health
// and record 9 held shares mana with the other dragon (+0x1a0c / +0x1a10 the times); else both times are cleared. A
// press of record 8 shows the stat change feedback.
void CKHkS08Hero::UpdateHeroHealthAndManaSharing(float dt) {
    const uint8_t controlled = static_cast<IKGrpHero*>(m_pGrpHero)->m_ui8ControlledHeroCount;  // 0x002ca288
    if (controlled <= 1 || (m_unkf80 != 3 && m_unkf80 != 1)) {
        m_unk1a10 = 0.0f;
        m_unk1a0c = 0.0f;
    } else {
        if (m_unkf94 == 3 || m_unkf94 == 1) {
            m_unk1a0c = dt + m_unk1a0c;
            TransferHeroHealthToOtherDragon(&m_unk1a0c);  // 0x003405f0
        } else {
            m_unk1a0c = 0.0f;
        }
        if (m_unkfa8 == 3 || m_unkfa8 == 1) {
            m_unk1a10 = m_unk1a10 + dt;
            TransferHeroManaToOtherDragon(&m_unk1a10);  // 0x003403f8
        } else {
            m_unk1a10 = 0.0f;
        }
    }
    if (m_unkf94 == 1) {
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->ShowDragonStatChangeFeedback(m_ui8Hero);  // 0x501fb8
    }
}

namespace {
// The body TransferHeroManaToOtherDragon and TransferHeroHealthToOtherDragon share (the stat's capacity, value, restore
// and take-away functions and the group's two fields differ): above the donor's share (`ratio` % of its capacity: the
// fctidz of the float product, compared as a word) the stat flows to the other dragon at `rate` per second of `elapsed`
// (fctidz of the float product), at most up to the other's capacity (words); the time it took (the amount over the rate,
// single) comes off `elapsed`; restored to the other dragon (quiet 0), then taken from the donor.
template <typename Capacity, typename Get, typename Restore, typename Take>
void TransferStatToOtherDragon(uint8_t hero, float* elapsed, float ratio, uint32_t rate, Capacity capacity, Get get,
                               Restore restore, Take take) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x29ec -> +0x8c
    const int32_t donor = hero != 0 ? 1 : 0;
    const int32_t other = donor ^ 1;
    const uint32_t donorCapacity = static_cast<uint32_t>(capacity(manager, donor));
    const uint32_t otherCapacity = static_cast<uint32_t>(capacity(manager, other));
    const uint32_t donorValue = get(manager, donor);
    const uint32_t otherValue = get(manager, other);
    const float share = (ratio / 100.0f) * static_cast<float>(static_cast<double>(donorCapacity));  // TOC +0x29f0
    if (!(static_cast<uint32_t>(ppc::fctidz(share)) < donorValue)) return;  // cmplw; bge
    const float perSecond = static_cast<float>(static_cast<double>(rate));
    const float time = *elapsed;
    uint32_t amount = static_cast<uint32_t>(ppc::fctidz(time * perSecond));
    if (otherValue + amount > otherCapacity) amount = otherCapacity - otherValue;
    *elapsed = time - static_cast<float>(static_cast<double>(amount)) / perSecond;
    restore(manager, other, amount);
    take(manager, donor, amount);
}
}  // namespace

// 0x003401f0 CKHkS08Hero_GetCarriedPowerBucket_maybe: the carrier's (+0xfb8) carried object (vt+0x80) when it is a power
// bucket (0x30c2), else null.
IKSerializable* CKHkS08Hero::GetCarriedPowerBucket() {
    if (m_unkfb8 == nullptr) return nullptr;
    IKSerializable* carried = static_cast<CKS08CarrierHero*>(m_unkfb8)->GetCarriedObject();  // vt+0x80 0x9c54c8
    if (carried == nullptr) return nullptr;
    return carried->IsKindOfClass(0x30c2) != 0 ? carried : nullptr;  // vt+0x08
}

// 0x003403f8 TransferHeroManaToOtherDragon: the co-op mana sharing (the group's +0x274 % share, +0x26c per second;
// ComputeSpyro/CynderManaCapacity 0x511710 / 0x5115d0 with include 0, GetDragonMana 0x4fd7c8, RestoreDragonMana 0x4fdca8,
// ConsumeDragonMana 0x4fd808).
void CKHkS08Hero::TransferHeroManaToOtherDragon(float* elapsed) {
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    TransferStatToOtherDragon(
        m_ui8Hero, elapsed, group->m_unk274, static_cast<uint32_t>(group->m_unk26c),
        [](CKS08GameManager* m, int32_t d) {
            CKS08GameStructure* s = static_cast<CKS08GameStructure*>(m->m_gameStructure);  // +0x6c
            return d == 0 ? ComputeSpyroManaCapacity(s, 0) : ComputeCynderManaCapacity(s, 0);
        },
        [](CKS08GameManager* m, int32_t d) { return m->GetDragonMana(d); },
        [](CKS08GameManager* m, int32_t d, uint32_t a) { m->RestoreDragonMana(d, static_cast<int32_t>(a), 0); },
        [](CKS08GameManager* m, int32_t d, uint32_t a) { m->ConsumeDragonMana(d, a); });
}

// 0x003405f0 TransferHeroHealthToOtherDragon: the same with health (the group's +0x270 % share, +0x268 per second;
// ComputeSpyro/CynderHealthCapacity 0x5111a0 / 0x511060, GetDragonHealth 0x4fd9c8, RestoreDragonHealth 0x4fdef8,
// DamageDragon 0x4fda08).
void CKHkS08Hero::TransferHeroHealthToOtherDragon(float* elapsed) {
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    TransferStatToOtherDragon(
        m_ui8Hero, elapsed, group->m_unk270, static_cast<uint32_t>(group->m_unk268),
        [](CKS08GameManager* m, int32_t d) {
            CKS08GameStructure* s = static_cast<CKS08GameStructure*>(m->m_gameStructure);  // +0x6c
            return d == 0 ? ComputeSpyroHealthCapacity(s, 0) : ComputeCynderHealthCapacity(s, 0);
        },
        [](CKS08GameManager* m, int32_t d) { return m->GetDragonHealth(d); },
        [](CKS08GameManager* m, int32_t d, uint32_t a) { m->RestoreDragonHealth(d, static_cast<int32_t>(a), 0); },
        [](CKS08GameManager* m, int32_t d, uint32_t a) { m->DamageDragon(d, a); });
}

// 0x0033fae0 CKHkS08Hero_AIAcquireTargetIfCredits: with attack credits (+0x1a20 > 0) a target in the aim sector of the
// movement (+0x1a7c flying, else +0x1a78) along the aim direction (+0x135c).
void CKHkS08Hero::AIAcquireTargetIfCredits() {
    if (!(static_cast<int32_t>(m_unk1a20) > 0)) return;
    IKSerializable* aim = static_cast<int8_t>(GetMovementMode()) == 1 ? m_unk1a7c : m_unk1a78;  // 0x003401b8
    const CVector3 direction = GetAimDirection();
    TryAcquireTarget(aim, &direction);  // 0x002fea88
}

// 0x0033fb80 CKHkS08Hero_AIUpdateCombatMovement_maybe: with credits, to the partner's attack target when it is a crumbly
// zone that wants hitting (+0x9c): it becomes +0x12c (no enemy), the partner's position and aim; else to a living
// targeted enemy (+0x124, health +0x258 above 0): no hook, the enemy's position, facing it (its frame's at, negated);
// else the ground follow (CtlState7).
void CKHkS08Hero::AIUpdateCombatMovement(IKTime* clock) {
    CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
    IKSerializable* target = partner->GetAITarget(1);  // 0x00364ab0
    const bool credits = static_cast<int32_t>(m_unk1a20) > 0;
    if (credits && target != nullptr && target->IsKindOfClass(CKHkS08CrumblyZoneMultiState::kClassKey) != 0 &&  // 0x3582
        static_cast<CKHkS08CrumblyZoneMultiState*>(target)->m_unk9C != 0) {
        m_unk12c = target;
        m_unk124 = nullptr;
        CVector3 position = GetPartnerHero()->GetAdjustedPosition();  // 0x0032a758
        const CVector3 facing = GetPartnerHero()->GetAimDirection();  // 0x0032a708
        AIMoveToTarget(clock, &position, &facing, 0, 0, 1);  // 0x0036dd08
        AIWriteStickFromDesiredMove();                        // 0x0033cb50
        return;
    }
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_unk124);
    if (enemy != nullptr && enemy->m_unk258 > 0.0f && static_cast<int32_t>(m_unk1a20) > 0) {  // TOC +0x298c
        m_unk12c = nullptr;
        CVector3 position = enemy->m_v3Position;  // +0x134
        const RwV3d& at = static_cast<CSGMovable*>(enemy->m_pKGLObject)->m_pRwFrame->modelling.at;  // +0x1c, +4, +0x30
        const CVector3 facing{-at.x, -at.y, -at.z};
        AIMoveToTarget(clock, &position, &facing, 0, 0, 1);
        AIWriteStickFromDesiredMove();
        return;
    }
    CtlAIFollowGround(clock, 0, 0);  // 0x0033e600
}

// 0x0033fdc8 CKHkS08Hero_AIQueueAttack: close enough to strike (the partner's crumbly zone in a combo within 3, or a living
// enemy within 2 of the position +0x54c): the move direction +0x37c points at it (normalised when farther than 0.1, else
// +0x3a4), +0x1378 and +0x394 cleared, and with credits the combo step 1 with the second button pressed (+0xf1c).
void CKHkS08Hero::AIQueueAttack() {
    float dx = 0.0f, dy = 0.0f, dz = 0.0f, distance = 0.0f;
    bool strike = false;
    bool decided = false;
    if (m_unk12c != nullptr && static_cast<int32_t>(m_unk1a20) > 0 && GetPartnerHero()->IsInCombo() != 0 &&  // 0x0032a698
        m_unk12c == GetPartnerHero()->GetAITarget(1)) {
        const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(m_unk12c)->m_pKGLObject)->m_pRwFrame)->pos;
        dy = m_unk550 - at.y;
        dx = m_unk54c - at.x;
        dz = m_unk554 - at.z;
        distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
        if (distance < 3.0f) strike = true;  // TOC +0x2990 (bge: unordered leaves too)
        decided = true;
    }
    if (!decided) {
        CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_unk124);
        if (enemy == nullptr || !(enemy->m_unk258 > 0.0f) || !(static_cast<int32_t>(m_unk1a20) > 0)) return;
        dy = m_unk550 - enemy->m_v3Position.y;
        dx = m_unk54c - enemy->m_v3Position.x;
        dz = m_unk554 - enemy->m_v3Position.z;
        distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (distance < 2.0f) strike = true;  // TOC +0x299c
    }
    if (!strike) return;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // computed again
    if (length != 0.0f && length > 0.1f) {  // TOC +0x298c / +0x2994
        const float inverse = 1.0f / length;  // TOC +0x2998
        m_unk37c = dx * inverse;
        m_unk384 = dz * inverse;
        m_unk380 = dy * inverse;
    } else {
        m_unk37c = m_unk3a4;
        m_unk384 = m_unk3ac;
        m_unk380 = m_unk3a8;
    }
    m_unk1378 = 0.0f;
    m_unk394 = 0;
    if (!(static_cast<int32_t>(m_unk1a20) > 0)) return;
    m_unk1a84 = 1;
    m_unkf1c = 1;
}

// 0x00340cd8 StaticInitAndDestruction_340cd8: two file statics (0x00ceae7c, 0x00ceae80) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae7c = -1.0f;
[[maybe_unused]] float s_unkceae80 = -1.0f;
}  // namespace
