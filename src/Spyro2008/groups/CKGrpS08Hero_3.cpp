// Reconstructed original translation unit: 0x2d4d48-0x2d8d98 (GAME_TOC1, main_toc1), 31 functions, 23 live.
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Stub.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"
#include <cstring>
#include "k2000/fx/IKFx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKHDRNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CTriggerStarter.h"
#include "platform/fps.h"
// Primary class: CKGrpS08Hero  key 0x984  category Group  size 0xafc  vtable 0xb22b00
// Other owners: CKHkS08Hero (5), SynchronizeHeroPlayerAssignments (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2d4d48  CKGrpS08Hero_IsGameManagerVf154Le1AndField36CNonNegative_maybe
//   [ ] 0x2d4df8  FUN_002d4df8  [dead]
//   [ ] 0x2d4e60  FUN_002d4e60  [dead]
//   [x] 0x2d4fd8  CKGrpS08Hero_GetFollowTrailPoint_maybe
//   [ ] 0x2d5148  CKGrpS08Hero_PopFollowTrailUntilKey_maybe  [dead]
//   [ ] 0x2d51c0  FUN_002d51c0  [dead]
//   [x] 0x2d51e0  CKGrpS08Hero_ClearFollowTrail_maybe  (ClearFollowTrail, CKGrpS08Hero.h)
//   [ ] 0x2d51f0  CKGrpS08Hero_SetFocusedHeroByIndex_maybe  [dead]
//   [x] 0x2d52d8  CKGrpS08Hero_vf184
//   [x] 0x2d53b0  StaticInitAndDestruction_2d53b0  (the two file statics at the end)
//   [ ] 0x2d53e0  _GLOBAL__D_2d53e0
//   [ ] 0x2d53f0  _GLOBAL__I_2d53f0
//   [ ] 0x2d5400  FUN_002d5400  [dead]
//   [x] 0x2d5430  CKGrpS08Hero_AllowFinisherCamera_maybe
//   [x] 0x2d57a8  CKGrpS08Hero_UpdateSinglePlayerPartnerFlags_maybe
//   [ ] 0x2d5968  CKGrpS08Hero_IsPointFarFromLeadHero_maybe  [dead: no pointer to its descriptor 0xb98600]
//   [ ] 0x2d5a00  CKGrpS08Hero_ShouldRecordTrailPoint_maybe  [dead: no pointer to its descriptor 0xb98608; its only bl is in the dead 0x2d5be0]
//   [ ] 0x2d5be0  CKGrpS08Hero_RecordLeaderTrail_maybe  [dead: no pointer to its descriptor 0xb98610]
//   [ ] 0x2d5fb0  CKGrpS08Hero_ShouldAdvanceCompanionPathPoint_maybe  [dead: no pointer to its descriptor 0xb98618; its only bl is in the dead 0x2d66d0]
//   [x] 0x2d61b8  CKGrpS08Hero_UpdateTimers364_maybe
//   [x] 0x2d63f8  SynchronizeHeroPlayerAssignments
//   [ ] 0x2d66d0  CKGrpS08Hero_AdvanceCompanionFollowPath_maybe  [dead: no pointer to its descriptor 0xb98688]
//   [x] 0x2d6c60  CKGrpS08Hero_UpdateCoopFocusedDragon_maybe
//   [x] 0x2d6f90  CKGrpS08Hero_ProcessDragonSwitchRequest
//   [x] 0x2d71f0  CKGrpS08Hero_UpdateFury_maybe
//   [x] 0x2d8c08  CKHkS08Hero_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKHkS08Hero))
//   [x] 0x2d8c58  CKHkS08Hero_vfD4  (CKHkS08Hero::VfD4, CKHkS08Hero.cpp)
//   [x] 0x2d8c78  CKHkS08Hero_vf150  (CKHkS08Hero.h)
//   [x] 0x2d8c80  CKHkS08Hero_vf154  (empty: inline at its call in IKHkHero.cpp)
//   [ ] 0x2d8c88  CKHkS08Hero_ClearTransientFlags_maybe  [dead]
//   [ ] 0x2d8d28  FUN_002d8d28  [dead]

// 0x002d4d48 CKGrpS08Hero_IsGameManagerVf154Le1AndField36CNonNegative_maybe: at most one player (the game manager's
// vt+0x154) and +0x36c at or above 0 (cror gt|eq: a NaN is false).
uint8_t CKGrpS08Hero::IsSinglePlayerAndTimer36cSet() {
    if (g_pEngine->m_gameManager->GetPlayerCount() > 1) return 0;
    return m_unk36c >= 0.0f ? 1 : 0;
}

// 0x002d57a8 CKGrpS08Hero_UpdateSinglePlayerPartnerFlags_maybe: the free AI slots (+0x378: the entries of +0x74
// without their flag +0x11), the companion held in the air above a ground of property 0x200 (+0xec4 bit 18, while its
// ground distance +0x4dc is below its +0x8e8), and the "partner in another navigation sector" flag (+0x2c8 bit 7).
void CKGrpS08Hero::UpdateSinglePlayerPartnerFlags() {
    uint8_t freeSlots = 0;
    for (uint32_t i = 0; i < m_sProperties.m_ui8Value; ++i) {
        const uint8_t* entry = static_cast<const uint8_t*>(m_pUnk74) + i * 0x18u;
        if (entry[0x11] == 0) ++freeSlots;
    }
    m_unk378 = (m_unk378 & 0x00ffffffu) | (static_cast<uint32_t>(freeSlots) << 24);  // the byte at +0x378
    CKHkS08Hero* companion = static_cast<CKHkS08Hero*>(m_apCompanionHeroes[0]);
    CKHkS08Hero* controlled = static_cast<CKHkS08Hero*>(m_apControlledHeroes[0]);
    const CGround* ground = static_cast<const CGround*>(companion->GetGroundInfo());  // 0x00361b68
    const uint32_t flags = companion->m_unkec4;
    companion->m_unkec4 = flags & 0xfffbffffu;
    if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0 &&
        !(companion->m_gcCurDatasInOut.m_fdH >= companion->m_unk8e8)) {  // +0x4dc; bge
        companion->m_unkec4 = (flags & 0xfffbffffu) | 0x40000u;
    }
    controlled->GetPartnerHero();  // 0x002f85f8 (the result is not used)
    const CKHkS08Hero* partner = controlled->GetPartnerHero();
    if (static_cast<int16_t>(partner->m_PFCpnt.m_Destination.m_unk0c) ==
        static_cast<int16_t>(controlled->m_PFCpnt.m_Destination.m_unk0c)) {  // +0x43c
        m_unk2c8 &= 0xffffff7fu;
        return;
    }
    m_unk2c8 = (m_unk2c8 & 0xffffff7fu) | 0x80u;
}

// 0x002d4fd8 CKGrpS08Hero_GetFollowTrailPoint_maybe (step 6 AI): the follow trail's record (TOC +0x1d20: the zero
// vector for an empty result).
CKGrpS08Hero::SFollowWaypoint CKGrpS08Hero::GetFollowWaypoint() const {
    static_assert(sizeof(SFollowWaypoint) == 0x24, "SFollowWaypoint is 0x24 bytes");
    SFollowWaypoint result;
    result.m_vPosition = kHeroZeroVector;
    result.m_vUnk0c = kHeroZeroVector;
    result.m_unk18 = 0.0f;  // stw 0
    result.m_unk1c = 0;
    result.m_unk20 = 0xffff;
    result.m_pad22 = 0;
    const SFollowWaypoint* trail = reinterpret_cast<const SFollowWaypoint*>(m_unk380);  // +0x380
    const int32_t count = static_cast<int32_t>(m_unka88);
    const uint32_t back = m_unkaa0[2];  // +0xaa8
    const SFollowWaypoint* record = nullptr;
    if (back != 0) {
        const int32_t index = (count - static_cast<int32_t>(back)) - 1;
        if (index > 0) record = &trail[index];
    }
    if (record == nullptr) {
        if (count == 0) return result;
        record = &trail[count - 1];
    }
    result.m_vPosition = record->m_vPosition;
    result.m_vUnk0c = record->m_vUnk0c;
    result.m_unk18 = record->m_unk18;
    result.m_unk1c = record->m_unk1c;
    result.m_unk20 = record->m_unk20;
    return result;
}

// 0x002d61b8 CKGrpS08Hero_UpdateTimers364_maybe: the combo announcer. Its approach (+0x364: target, speed, current)
// steps with the frame dt and its time (+0x374) grows. A player-controlled hero that is not grabbing in a combo arms it
// (hero 0 first; hero 1 when hero 0 is not player-controlled or grabs). The approach restarts (current -0.001, target
// -1, speed 1 / +0x1cc) when its current value is 0, or when it is positive with at most one player and armed. Then the
// list +0x370 goes back to its pool once the time reaches +0x1d0.
void CKGrpS08Hero::UpdateTimers364(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];
    FloatApproach_Step(dt, &m_unk364);  // 0x002436e8
    m_unk374 = dt + m_unk374;
    CKHkS08Hero* first = static_cast<CKHkS08Hero*>(m_apHeros[0]);
    CKHkS08Hero* second = static_cast<CKHkS08Hero*>(m_apHeros[1]);
    // A player-controlled hero arms the announcer unless it grabs during a combo.
    auto arms = [](const CKHkS08Hero* hero) { return hero->IsInCombo() == 0 || hero->GetGrabTarget() == nullptr; };
    bool armed;
    if (first->IsPlayerControlled() != 0 && arms(first)) {  // 0x00362af0, 0x0032a698, 0x00329df8
        armed = true;
    } else {
        armed = second->IsPlayerControlled() != 0 && arms(second);
    }
    bool restart = m_unk36c == 0.0f;  // TOC +0x1d54
    if (!restart) {
        const uint8_t players = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->GetPlayerCount();  // vt+0x154
        restart = players <= 1 && m_unk36c >= 0.0f && armed;
    }
    if (restart) {
        m_unk36c = -0.001f;           // TOC +0x1d60
        m_unk364 = -1.0f;             // TOC +0x1d38
        m_unk368 = 1.0f / m_unk1cc;   // TOC +0x1d4c
    }
    // The announced blows are forgotten together once the announcer's time reaches +0x1d0.
    if (m_pAnnounced == nullptr || !(m_unk1d0 <= m_unk374)) return;
    for (AnnouncedBlow* node = m_pAnnounced; node != nullptr;) {
        AnnouncedBlow* next = node->m_pNext;
        delete node;  // back to FreeListPool 0x00ceaa20 in the original
        node = next;
    }
    m_pAnnounced = nullptr;
}

// 0x002d63f8 SynchronizeHeroPlayerAssignments: when the game manager's player count (vt+0x154) differs from the
// controlled heroes', the heroes are assigned again: one player plays hero 0 (both followers of it, +0xec4 bit 22 on,
// +0x2c8 bit 1), two players one hero each; a hero whose control changes is reassigned, hero 0 is focused and the
// controlled and companion lists are rebuilt.
void CKGrpS08Hero::SynchronizeHeroPlayerAssignments() {
    const uint8_t players = g_pEngine->m_gameManager->GetPlayerCount();  // vt+0x154
    if (m_ui8ControlledHeroCount == players) return;
    CKHkS08Hero* first = static_cast<CKHkS08Hero*>(m_apHeros[0]);
    uint8_t firstHero;
    uint8_t firstLeader;
    if (players < 2) {
        m_unk37c = 0;
        m_unk2c8 = (m_unk2c8 & 0xfffffffdu) | 2u;
        m_unka88 = 0;
        for (uint32_t i = GetHeroCount(); i != 0; --i) {  // vt+0xf4
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_apHeros[i - 1]);
            hero->m_unkec4 = (hero->m_unkec4 & 0xffbfffffu) | 0x400000u;
        }
        first = static_cast<CKHkS08Hero*>(m_apHeros[0]);
        first->m_ui8Leader = 0;
        firstHero = first->m_ui8Hero;
        firstLeader = first->m_ui8TrackedLeader;
    } else {
        m_unk2c8 &= 0xfffffffdu;
        for (uint32_t i = GetHeroCount(); i != 0; --i) {
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_apHeros[i - 1]);
            hero->m_unkec4 &= 0xffbfffffu;
        }
        first = static_cast<CKHkS08Hero*>(m_apHeros[0]);
        firstHero = first->m_ui8Hero;
        firstLeader = first->m_ui8TrackedLeader;
        first->m_ui8Leader = 0;
    }
    first->m_ui8TrackedLeader = 0;
    if ((firstHero == firstLeader) != (first->m_ui8Hero == first->m_ui8TrackedLeader)) {
        first->ApplyControlAssignment(0, 0);  // 0x00348010
    }
    CKHkS08Hero* second = static_cast<CKHkS08Hero*>(m_apHeros[1]);
    second->m_ui8Leader = 1;
    const uint8_t secondLeader = second->m_ui8TrackedLeader;
    second->m_ui8TrackedLeader = players > 1 ? 1 : 0;
    if ((second->m_ui8Hero == secondLeader) != (second->m_ui8Hero == second->m_ui8TrackedLeader)) {
        second->ApplyControlAssignment(0, 0);
    }
    SetFocusedDragon(m_apHeros[0], 1);           // 0x002cc3f0
    RebuildControlledAndCompanionHeroArrays();   // 0x002cb528
}

// 0x002d6c60 CKGrpS08Hero_UpdateCoopFocusedDragon_maybe: clears +0xf8 bit 17; with two players, the place of each
// dragon is ranked (3: the camera's constraint zone wants it (its word +0x20 bit 20) for the focused one, inside the
// zone for the partner; 2 flying with the partner; 1 climbing; 0 none): a partner ranked above the focused dragon takes
// the focus (+0xf8 bit 17, the dragon's +0x364 bit 29); one ranked below only sets bit 17.
void CKGrpS08Hero::UpdateCoopFocusedDragon(IKTime*) {
    m_unkf8 &= 0xfffdffffu;
    if (m_ui8ControlledHeroCount < 2) return;
    if (m_unk66 > 2) return;
    const int32_t index = static_cast<int8_t>(m_unk66);
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    CKHkS08Hero* focused = static_cast<CKHkS08Hero*>(m_apHeros[index]);
    CKHkS08Hero* partner = static_cast<CKHkS08Hero*>(m_apHeros[(index + 1) % 2]);
    uint32_t focusedRank = 3;
    uint32_t zoneFlags = 0;
    const CKCameraConstraint* zone = camera->m_pActiveConstraint;
    if (zone != nullptr) std::memcpy(&zoneFlags, &zone->m_unk20, sizeof(zoneFlags));  // a word here
    if (zone == nullptr || (zoneFlags & 0x100000u) == 0) {
        focusedRank = 2;
        if (focused->ShouldJoinPartnerFlight() == 0) focusedRank = focused->ShouldStayClimbing() != 0 ? 1 : 0;  // 0x00341fa0 / 0x00342fa8
    }
    const float* partnerPosition = &partner->m_unk54c;
    bool inside;
    if (partner->ShouldStayClimbing() != 0) {
        inside = camera->IsPointInActiveConstraint(partnerPosition, 1);  // 0x0012b558
    } else {
        inside = camera->IsPointInActiveConstraint(partnerPosition, partner->ShouldJoinPartnerFlight() != 0 ? 2 : 0);
    }
    uint32_t partnerRank = 3;
    if (!inside) {
        if (partner->ShouldJoinPartnerFlight() != 0) {
            partnerRank = 2;
        } else if (partner->ShouldStayClimbing() != 0) {
            partnerRank = 1;
        } else {
            partnerRank = 0;
        }
    }
    if (focusedRank < partnerRank) {
        m_unkf8 = (m_unkf8 & 0xfffdffffu) | 0x20000u;
        IKSerializable** heroes = m_apHeros;
        CKHkS08Hero* next = static_cast<CKHkS08Hero*>(heroes[0]);
        if (partner->m_ui8Hero <= 1 && focused->m_ui8Hero <= 1) next = static_cast<CKHkS08Hero*>(heroes[partner->m_ui8Hero]);
        // KStub_Nop_2ca970 (the two positions, the new one's +0x1818, +0xf8 bits 7 / 8): empty.
        SetFocusedDragon(next, 1);  // 0x002cc3f0
        next->m_unk364 = (next->m_unk364 & 0xdfffffffu) | 0x20000000u;
        return;
    }
    if (focusedRank > partnerRank) m_unkf8 = (m_unkf8 & 0xfffdffffu) | 0x20000u;
}

// 0x002d6f90 CKGrpS08Hero_ProcessDragonSwitchRequest (vt+0x180): with +0x2c8 bit 9 the request is dropped. Two
// players, or a pending player change (the game manager's +0xe14 set and unlike +0xe34), only move the focus to the
// requested dragon (+0x364 bit 29, the time +0x6c). One player: ApplyRequestedDragonSelection, the companion's player the
// other one, the new dragon's panel feedback, the companion's timed panel closed, +0x2d0 = 2.
void CKGrpS08Hero::ProcessDragonSwitchRequest(uint8_t applyArg) {
    if ((m_unk2c8 & 0x200u) != 0) {
        m_unk65 = m_unk64;
        m_unkf8 &= ~0x20u;
        return;
    }
    CKS08GameManager* gm = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const uint32_t change = gm->m_unkDF4[8];  // +0xe14
    const bool pendingChange = change != 0 && (change ^ gm->m_unkDF4[16]) != 0;  // +0xe34
    if (m_ui8ControlledHeroCount > 1 || pendingChange) {  // 0x002ca288
        IKSerializable* hero = m_apHeros[0];
        if (m_unk65 <= 1 && m_unk64 <= 1) hero = m_apHeros[m_unk65];
        // KStub_Nop_2ca970 (the other hero's and this one's positions +0x54c, its +0x1818, +0xf8 bits 7 / 8) is empty.
        SetFocusedDragon(hero, 1);  // 0x002cc3f0
        CKHkS08Hero* focused = static_cast<CKHkS08Hero*>(hero);
        focused->m_unk364 = (focused->m_unk364 & ~0x20000000u) | 0x20000000u;
        m_unk6c = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0];
        m_unk65 = m_unk64;
        m_unkf8 &= ~0x20u;
        return;
    }
    ApplyRequestedDragonSelection(applyArg);  // 0x002cc7c0
    IKHkHero* companion = static_cast<IKHkHero*>(m_apCompanionHeroes[0]);
    const IKHkHero* controlled = static_cast<const IKHkHero*>(m_apControlledHeroes[0]);
    companion->m_ui8Leader = static_cast<uint8_t>((controlled->m_ui8Leader + 1) % 2);
    gm->ShowDragonStatChangeFeedback(controlled->m_ui8Hero);  // 0x00501fb8
    gm->CloseDragonHudTimedPanel(companion->m_ui8Hero);       // 0x00501700
    m_unk2d0 = 2.0f;  // TOC1 +0x1d74
}

namespace {
float FuryWordF32(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}
void SetFuryWordF32(uint32_t& word, float value) { std::memcpy(&word, &value, sizeof(value)); }
}  // namespace

// 0x002d71f0 CKGrpS08Hero_UpdateFury_maybe: the fury (+0x2c8 bit 8 running, bit 9 charging). The fury accumulators
// +0x32c / +0x330 and the timer +0x2d4 are floats kept in words.
// - Running, not charging: both dragons get +0x188 mana per second, the shared fury drains +0x324 per second (an even
//   amount through +0x32c); at no fury left the flash +0x348 plays and the fury ends: its filter (+0x350) and HDR blend
//   (+0x35c back from +0x358) let go, both heroes leave the fury mode, the trigger +0x340.
// - Neither: a full gauge (+0x334) with both heroes able: with neither hero's +0xecc bit 5 the charge starts (trigger
//   +0x338, the heroes' +0xed4 bit 6, the gauge drained, +0x328 = +0x17c, the timer +0x2d4 = +0x18c), else the fury
//   starts at once (the effects, the explosion between the heroes, +0x324 = the fury over +0x180, the fury mode).
// - Charging: the timer runs down; the gauge fills back (+0x17c / +0x180 / +0x18c per second times +0x334; action 3
//   pressed adds +0x184 per player) until the timer is over, then running is set; charging and running: the effects and
//   the explosion, charging cleared, +0x324 = the fury over min(+0x328, +0x180), +0xed4 bit 6 cleared, the heroes' fury
//   timers +0x1b00 = +0x190 and the fury mode.
void CKGrpS08Hero::UpdateFury(IKTime* clock) {
    const uint32_t flags = m_unk2c8;
    float dt = clock->m_afDeltaTime[0];  // +0x1c
    CKHkS08Hero* hero1 = static_cast<CKHkS08Hero*>(m_apHeros[1]);
    CKHkS08Hero* hero0 = static_cast<CKHkS08Hero*>(m_apHeros[0]);
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x1d1c
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    // The fury's effects: the filter (+0x34c, reserved, into +0x350), the explosion (+0x354, reserved), the HDR blend
    // (+0x358 into +0x35c), then the explosion at the middle of the heroes (0.5 of each position over the zero vector).
    auto startEffects = [&]() {
        m_unk350 = fx->AcquireFx(reinterpret_cast<IKFxData*>(m_pUnk34c), this);  // inlined
        IKFx* explosion = fx->AcquireFx(reinterpret_cast<IKFxData*>(m_pUnk354), this);
        m_unk35c = fx->StartEffect(reinterpret_cast<IKFxData*>(m_pUnk358), this);
        if (explosion != nullptr) {
            const CVector3& zero = kHeroZeroVector;  // TOC +0x1d20 -> 0x00c50d64
            const float half = 0.5f;                 // TOC +0x1d9c
            const float* a = &hero0->m_unk54c;       // 0x00361968 CKHkS08Hero_GetPositionPtr
            CVector3 at = {ppc::fmadds(a[0], half, zero.x), ppc::fmadds(a[1], half, zero.y), ppc::fmadds(a[2], half, zero.z)};
            const float* b = &hero1->m_unk54c;
            at.z = ppc::fmadds(b[2], half, at.z);
            at.x = ppc::fmadds(b[0], half, at.x);
            at.y = ppc::fmadds(b[1], half, at.y);
            CKExplosionNodeFx* node = static_cast<CKExplosionNodeFx*>(explosion);
            node->SetTranslation(&at, this);  // 0x001b66e8
            node->Trigger(this, 0);           // 0x001b8770 (-> 0x1b82a8)
        }
    };
    if ((flags & 0x200u) == 0) {
        if ((flags & 0x100u) != 0) {
            int64_t mana = ppc::fctidz(dt * m_unk188);
            // --fps N (not in the original): the whole mana of this frame's 60 Hz frames (the per-update trunc
            // drops the fraction: less mana per second at a higher frame rate).
            if (dotd::fps::Unlocked()) mana = dotd::fps::TruncSteps(m_unk188, dt);
            manager->RestoreDragonMana(0, static_cast<int32_t>(static_cast<uint32_t>(mana)), 1);  // 0x4fdca8
            manager->RestoreDragonMana(1, static_cast<int32_t>(static_cast<uint32_t>(mana)), 1);
            const float pending = ppc::fmadds(dt, m_unk324, FuryWordF32(m_unk32c));
            const int64_t half = ppc::fctidz(pending * 0.5f);  // TOC +0x1d9c
            const uint32_t drained = (static_cast<uint32_t>(half) << 1) & 0xfffffffeu;  // slwi: the low word, zero-extended
            // The carry keeps what was not drained: the drained (even) amount through fcfid (0x002d7a78..0x002d7a8c).
            SetFuryWordF32(m_unk32c, pending - static_cast<float>(static_cast<double>(drained)));
            manager->DrainDragonFury(0, drained, 1);  // 0x004fdb28
            if (manager->GetDragonFury(0) != 0) return;  // 0x004fd680
            fx->StartEffect(reinterpret_cast<IKFxData*>(m_pUnk348), this);  // inlined (the result is not kept)
            if (m_unk350 != nullptr) {
                static_cast<IKFx*>(m_unk350)->StopAndRelease(this);  // vt+0x58
                m_unk350 = nullptr;
            }
            if (m_unk35c != nullptr) {
                static_cast<CKHDRNodeFx*>(m_unk35c)->StartBlendToSetting(m_pUnk358, this);  // 0x001c0200
                m_unk35c = nullptr;
            }
            m_unk2c8 &= ~0x100u;
            hero0->SetFuryMode(0);  // 0x00328e40
            hero1->SetFuryMode(0);
            QueueTriggerSignals(&m_tsUnk340);  // 0x00236338 (the group as the second argument)
            return;
        }
        if (manager->IsFuryGaugeFull(&m_unk334) == 0) return;  // 0x004fe148
        if (hero0->CanStartFury() == 0) return;             // 0x00326830
        if (hero1->CanStartFury() == 0) return;
        if ((hero0->m_unkecc & 0x20u) == 0 && (hero1->m_unkecc & 0x20u) == 0) {
            QueueTriggerSignals(&m_tsUnk338);  // 0x00236338
            hero0->m_unked4 = (hero0->m_unked4 & ~0x40u) | 0x40u;
            hero1->m_unked4 = (hero1->m_unked4 & ~0x40u) | 0x40u;
            m_unk2c8 = (m_unk2c8 & ~0x200u) | 0x200u;
            manager->DrainDragonFury(0, m_unk334, 1);
            m_unk328 = m_unk17c;
            SetFuryWordF32(m_unk2d4[0], m_unk18c);
            m_unk32c = 0;
            return;
        }
        startEffects();
        const uint32_t total = manager->GetTotalFury();  // 0x004fd420
        m_unk32c = 0;
        m_unk324 = static_cast<float>(static_cast<double>(total)) / m_unk180;
        hero0->SetFuryMode(1);
        hero1->SetFuryMode(1);
        m_unk2c8 = (m_unk2c8 & ~0x100u) | 0x100u;
        return;
    }
    if ((flags & 0x100u) == 0) {
        float timer = FuryWordF32(m_unk2d4[0]);
        if (timer > 0.0f) SetFuryWordF32(m_unk2d4[0], timer - dt);  // TOC +0x1d54; bgt
        const uint8_t players = manager->GetPlayerCount();  // vt+0x154
        float rate = ((dt * m_unk17c) / m_unk180) / m_unk18c;
        if (players == 1) {
            if (manager->IsActionPressed(3, 0) != 0) {  // vt+0x160
                const float bonus = m_unk184 / m_unk180;
                m_unk328 = m_unk184 + m_unk328;
                rate = rate + bonus;
            }
            const float amount = ppc::fmadds(rate, static_cast<float>(static_cast<double>(m_unk334)), FuryWordF32(m_unk32c));
            SetFuryWordF32(m_unk32c, amount);
            const uint32_t add = static_cast<uint32_t>(ppc::fctidz(amount * 0.5f));
            manager->AddDragonFury(0, add);  // 0x004fd528
            manager->AddDragonFury(1, add);
            SetFuryWordF32(m_unk32c, FuryWordF32(m_unk32c) - static_cast<float>(static_cast<double>(add)));
        } else {
            float rate0 = rate;
            float rate1 = rate;
            const float perPlayer = m_unk184 / static_cast<float>(static_cast<double>(static_cast<int32_t>(players)));
            if (manager->IsActionPressed(3, 0) != 0) {
                m_unk328 = perPlayer + m_unk328;
                rate0 = rate + perPlayer / m_unk180;
            }
            if (manager->IsActionPressed(3, 1) != 0) {
                m_unk328 = perPlayer + m_unk328;
                rate1 = rate + perPlayer / m_unk180;
            }
            const float capacity = static_cast<float>(static_cast<double>(m_unk334));
            const float second = ppc::fmadds(rate1, capacity, FuryWordF32(m_unk330));
            const float first = ppc::fmadds(rate0, capacity, FuryWordF32(m_unk32c));
            SetFuryWordF32(m_unk330, second);
            SetFuryWordF32(m_unk32c, first);
            const uint32_t add = static_cast<uint32_t>(ppc::fctidz(second + first));
            manager->AddDragonFury(0, add);
            manager->AddDragonFury(1, add);
            const float rest = (FuryWordF32(m_unk32c) + FuryWordF32(m_unk330)) - static_cast<float>(static_cast<double>(add));
            SetFuryWordF32(m_unk330, rest);
            SetFuryWordF32(m_unk32c, rest);
        }
        if (FuryWordF32(m_unk2d4[0]) > 0.0f) return;  // bgt
        m_unk2c8 = (m_unk2c8 & ~0x100u) | 0x100u;
        return;
    }
    startEffects();
    m_unk2c8 &= ~0x200u;
    const uint32_t total = manager->GetTotalFury();
    float span = m_unk180;
    if (!(m_unk328 > m_unk180)) span = m_unk328;  // bgt
    m_unk32c = 0;
    m_unk324 = static_cast<float>(static_cast<double>(total)) / span;
    hero0->m_unked4 &= ~0x40u;
    hero1->m_unked4 &= ~0x40u;
    hero0->m_unk1b00 = m_unk190;
    hero1->m_unk1b00 = m_unk190;
    hero0->SetFuryMode(1);
    hero1->SetFuryMode(1);
}

// 0x002d5430 CKGrpS08Hero_AllowFinisherCamera_maybe (see the header).
uint8_t CKGrpS08Hero::AllowFinisherCamera(const void* blow, int32_t lethal) {
    const uint8_t players = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->GetPlayerCount();  // vt+0x154
    if (players > 1 || m_unk36c != -1.0f) return 0;
    if (lethal == 0) {
        for (const AnnouncedBlow* node = m_pAnnounced; node != nullptr; node = node->m_pNext) {
            if (node->m_pBlow == blow) return 0;
        }
    } else {
        for (AnnouncedBlow** link = &m_pAnnounced; *link != nullptr;) {
            if ((*link)->m_pBlow == blow) {
                AnnouncedBlow* gone = *link;
                *link = gone->m_pNext;
                delete gone;  // back to FreeListPool 0x00ceaa20 in the original
            } else {
                link = &(*link)->m_pNext;
            }
        }
    }
    uint32_t count = 0;
    AnnouncedBlow* last = nullptr;
    AnnouncedBlow* beforeLast = nullptr;
    for (AnnouncedBlow* node = m_pAnnounced; node != nullptr; node = node->m_pNext) {
        ++count;
        beforeLast = last;
        last = node;
    }
    const float base = m_unk1c4 + m_unk1c8;
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    m_unk364 = 0.0f;
    m_unk368 = 1.0f;  // TOC +0x1d4c
    m_unk36c = ppc::fmadds((static_cast<float>(static_cast<double>(r)) / 65535.0f) * -2.0f, m_unk1c8, base);  // +0x1d44 / +0x1d48
    m_unk374 = 0.0f;
    if (m_unk1d4 == 0) return 1;
    if (count >= static_cast<uint32_t>(m_unk1d4) && last != nullptr) {
        if (beforeLast == nullptr) {
            m_pAnnounced = last->m_pNext;
        } else {
            beforeLast->m_pNext = last->m_pNext;
        }
        delete last;
    }
    AnnouncedBlow* node = new AnnouncedBlow();  // FreeListPool 0x00ceaa20 (grown by 0x00244908 when empty)
    node->m_pBlow = blow;
    node->m_pNext = m_pAnnounced;
    m_pAnnounced = node;
    return 1;
}

// 0x002d53b0 StaticInitAndDestruction_2d53b0 (_GLOBAL__I_2d53f0): two file statics (0x00ceade0, 0x00ceade4) set to
// -1.0f. Nothing in the game reads them.
namespace {
[[maybe_unused]] float s_unkceade0 = -1.0f;
[[maybe_unused]] float s_unkceade4 = -1.0f;
}  // namespace
