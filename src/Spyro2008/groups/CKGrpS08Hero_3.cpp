// Reconstructed original translation unit: 0x2d4d48-0x2d8d98 (GAME_TOC1, main_toc1), 31 functions, 23 live.
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/misc/Engine.h"
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
//   [ ] 0x2d51e0  CKGrpS08Hero_ClearFollowTrail_maybe
//   [ ] 0x2d51f0  CKGrpS08Hero_SetFocusedHeroByIndex_maybe  [dead]
//   [x] 0x2d52d8  CKGrpS08Hero_vf184
//   [ ] 0x2d53b0  StaticInitAndDestruction_2d53b0
//   [ ] 0x2d53e0  _GLOBAL__D_2d53e0
//   [ ] 0x2d53f0  _GLOBAL__I_2d53f0
//   [ ] 0x2d5400  FUN_002d5400  [dead]
//   [ ] 0x2d5430  CKGrpS08Hero_AllowFinisherCamera_maybe
//   [x] 0x2d57a8  CKGrpS08Hero_UpdateSinglePlayerPartnerFlags_maybe
//   [ ] 0x2d5968  CKGrpS08Hero_IsPointFarFromLeadHero_maybe
//   [ ] 0x2d5a00  CKGrpS08Hero_ShouldRecordTrailPoint_maybe
//   [ ] 0x2d5be0  CKGrpS08Hero_RecordLeaderTrail_maybe
//   [ ] 0x2d5fb0  CKGrpS08Hero_ShouldAdvanceCompanionPathPoint_maybe
//   [ ] 0x2d61b8  CKGrpS08Hero_UpdateTimers364_maybe
//   [x] 0x2d63f8  SynchronizeHeroPlayerAssignments
//   [ ] 0x2d66d0  CKGrpS08Hero_AdvanceCompanionFollowPath_maybe
//   [ ] 0x2d6c60  CKGrpS08Hero_UpdateCoopFocusedDragon_maybe
//   [ ] 0x2d6f90  CKGrpS08Hero_ProcessDragonSwitchRequest
//   [ ] 0x2d71f0  CKGrpS08Hero_UpdateFury_maybe
//   [ ] 0x2d8c08  CKHkS08Hero_Delete
//   [ ] 0x2d8c58  CKHkS08Hero_vfD4
//   [ ] 0x2d8c78  CKHkS08Hero_vf150
//   [ ] 0x2d8c80  CKHkS08Hero_vf154
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

// 0x002d61b8 CKGrpS08Hero_UpdateTimers364_maybe. STUB(C2.7: combat): the combo announcer's approach (+0x364), its
// time (+0x374) and pool (+0x370), from the players' combos and grabs. Not used before the first fight.
void CKGrpS08Hero::UpdateTimers364(IKTime*) { DOTD_STUB_ONCE("CKGrpS08Hero_UpdateTimers364_maybe 0x2d61b8 (C2.7)"); }

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

// 0x002d6c60 CKGrpS08Hero_UpdateCoopFocusedDragon_maybe: clears +0xf8 bit 17; with two players, the focus moves to the
// partner whose place (flying, climbing, inside the camera's constraint) ranks above the focused one's. STUB(C2.7, moved from C2.6: co-op /
// two players): the ranking (the camera's constraint test CKSrvCamera_IsPointInActiveConstraint_maybe) is not ported;
// one player returns before it.
void CKGrpS08Hero::UpdateCoopFocusedDragon(IKTime*) {
    m_unkf8 &= 0xfffdffffu;
    if (m_ui8ControlledHeroCount < 2) return;
    if (m_unk66 > 2) return;
    DOTD_STUB_ONCE("CKGrpS08Hero_UpdateCoopFocusedDragon_maybe 0x2d6c60: two players (C2.7, moved from C2.6)");
}

// 0x002d6f90 CKGrpS08Hero_ProcessDragonSwitchRequest (vt+0x180). STUB(C2.7, moved from C2.6: see RequestDragonSelection): with
// +0x2c8 bit 9 clear, two players or a pending player change (game manager +0xe14 / +0xe34) refocus the requested
// dragon (SetFocusedDragon, +0x364 bit 29, +0x6c the time); one player swaps the control
// (ApplyRequestedDragonSelection 0x2cc7c0), the companion's player index, the HUD feedback (C2.7) and +0x2d0; else the
// request is dropped (+0x65 = +0x64, +0xf8 bit 5 cleared). Reached only through the Select button (RequestDragonSelection).
void CKGrpS08Hero::ProcessDragonSwitchRequest(uint8_t) {
    DOTD_STUB_ONCE("CKGrpS08Hero_ProcessDragonSwitchRequest 0x2d6f90 (C2.7, moved from C2.6: dragon switch)");
}

// 0x002d71f0 CKGrpS08Hero_UpdateFury_maybe. STUB(C2.7: fury): the fury gauge (AddDragonFury, the fury mode, the HDR
// blend, the explosion FX and the mana restore).
void CKGrpS08Hero::UpdateFury(IKTime*) { DOTD_STUB_ONCE("CKGrpS08Hero_UpdateFury_maybe 0x2d71f0 (C2.7)"); }
