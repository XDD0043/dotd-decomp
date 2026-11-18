// CKS08GameManager_5.cpp - reconstructed original translation unit 0x4fe5a8-0x504358 (GAME_TOC1, main_toc1), 64 functions, 62 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: ResetDragonStatHud (2), OnNewHitW (1), RefreshFuryGaugeHud (1), NotifySpyroMovementModeChanged (1), UpdateDragonUpgradeText (1), NotifyCynderMovementModeChanged (1), UpdateDragonManaCapacityMarker (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4fe5a8  StaticInitAndDestruction_4fe5a8  (two statics (-1.0f) nothing reads (0x00ceb268 / 0x00ceb26c: no other reference): nothing to port)
//   [ ] 0x4fe5d8  _GLOBAL__D_4fe5d8
//   [ ] 0x4fe5e8  _GLOBAL__I_4fe5e8
//   [x] 0x4fe5f8  OnNewHitW_2  (= 0x4fe568 OnNewHitW, k2000/misc/OnNewHit.cpp)
//   [x] 0x4fe638  CKS08GameManager_DestroyTextures
//   [x] 0x4fe7e0  CKS08GameManager_SetFightZoneGaugeMax2_maybe
//   [x] 0x4fe880  CKS08GameManager_SetFightZoneGaugeMax_maybe
//   [x] 0x4fe920  CKS08GameManager_SetFightZoneGaugeValue_maybe
//   [x] 0x4fe9c0  CKS08GameManager_SetEnemyGaugeMaxHealth_2_maybe
//   [x] 0x4fea60  CKS08GameManager_SetEnemyGaugeMaxHealth_maybe
//   [x] 0x4feb00  CKS08GameManager_SetBossGaugeHealth_maybe
//   [x] 0x4feba0  CKS08GameManager_RegisterSecondBossGaugeZone_maybe
//   [x] 0x4fec98  RefreshFuryGaugeHud_maybe  (CKS08GameManager_4.cpp)
//   [x] 0x4fed80  CKS08GameManager_SetCenterTwinGauges_maybe
//   [x] 0x4feef0  CKS08GameManager_HideFuryGaugeIfShown_maybe
//   [x] 0x4fefd8  CKS08GameManager_QueueHudMessage_maybe  (CKS08GameManager::QueueHudMessage, CKS08GameManager_3.cpp)
//   [x] 0x4ff080  CKS08GameManager_ShowCenterHudMessagePairSecondFromTable_maybe  (CKS08GameManager::ShowCenterHudMessagePairSecond, CKS08GameManager_3.cpp)
//   [x] 0x4ff150  CKS08GameManager_ShowCenterHudMessage_maybe  (in CKS08GameManager_3.cpp)
//   [x] 0x4ff220  CKS08GameManager_SelectSpyroHudPanelElement_maybe
//   [x] 0x4ff2d8  NotifySpyroMovementModeChanged_Stub
//   [x] 0x4ff318  CKS08GameManager_UpdateBossGaugeTotals_maybe
//   [x] 0x4ff540  CKS08GameManager_UpdateSecondBossGaugeTotals_maybe
//   [x] 0x4ff768  CKS08GameManager_LoadHudResources_maybe
//   [x] 0x4ffaf0  CKS08GameManager_QueueUpgradeAvailableInfo_maybe
//   [x] 0x4ffdd0  CKS08GameManager_QueueFirstCollectibleInfo_maybe
//   [x] 0x4fffe0  CKS08GameManager_EndComboDisplay_maybe
//   [x] 0x500140  UpdateDragonUpgradeText_maybe
//   [ ] 0x5003c0  CKS08GameManager_SetDragonUpgradePoints_maybe  [dead]
//   [x] 0x500418  CKS08GameManager_AddDragonUpgradePoints_maybe
//   [x] 0x500628  CKS08GameManager_UpdateComboTimers_maybe
//   [x] 0x500880  CKS08GameManager_CheatMaxUpgradePoints_maybe
//   [x] 0x5008c8  CKS08GameManager_AddDragonUpgradePoints_2_maybe  (= a tail call of 0x500418 AddDragonUpgradePoints (CKS08GameManager::AddDragonUpgradePoints))
//   [x] 0x5008d0  CKS08GameManager_HidePlayerHudPanel_maybe
//   [x] 0x500a88  CKS08GameManager_SelectCynderHudPanelElement_maybe
//   [x] 0x500b38  NotifyCynderMovementModeChanged_Stub
//   [x] 0x500b78  CKS08GameManager_UpdateCenterTwinGauges_maybe
//   [x] 0x500cc8  UpdateDragonManaCapacityMarker_maybe
//   [x] 0x500ee8  UpdateDragonManaGauge
//   [x] 0x501188  UpdateDragonHealthCapacityMarker_maybe
//   [x] 0x5013a8  UpdateDragonHealthGauge
//   [x] 0x501648  UpdateDragonHealthAndManaGauges
//   [x] 0x501700  CKS08GameManager_CloseDragonHudTimedPanel_maybe
//   [x] 0x501860  CKS08GameManager_ShowCenterMessage_maybe
//   [x] 0x501938  CKS08GameManager_QueueCollectibleMessage_maybe
//   [x] 0x501a08  CKS08GameManager_ShowCollectedItemMessage_maybe
//   [x] 0x501b00  CKS08GameManager_UpdateInGameHud_maybe
//   [x] 0x501c90  CKS08GameManager_SendFightZoneHudMessageAndClearTimer_maybe
//   [ ] 0x501da8  FUN_00501da8  [dead]
//   [x] 0x501ea0  CKS08GameManager_RefreshBossGauge_maybe
//   [x] 0x501fb8  ShowDragonStatChangeFeedback_maybe
//   [x] 0x5022b0  RefreshDragonStatDisplays_maybe
//   [x] 0x502340  ResetDragonStatHud_2
//   [x] 0x502410  ResetDragonStatHud
//   [x] 0x5024d8  ShowCynderSelectedElementHud
//   [x] 0x502688  CKS08GameManager_ShowPlayerHudPanel_maybe
//   [x] 0x502a80  CKS08GameManager_UpdateCounterTextVariables_maybe
//   [x] 0x502ca0  CKS08GameManager_RefreshManaShardHud_maybe
//   [x] 0x5032d0  CKS08GameManager_RefreshHealthShardHud_maybe
//   [x] 0x503900  CKS08GameManager_RefreshComboCountText_maybe
//   [x] 0x5039e8  ShowSpyroSelectedElementHud
//   [x] 0x503ba0  OnNewHit_continuecombo
//   [x] 0x503df0  OnComboHit_comboStart
//   [x] 0x504040  CKS08GameManager_State6_maybe
//   [x] 0x504248  CKS08GameManager_State2_maybe
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/memory/Mem.h"

#include <cstdio>
#include <cstring>

#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "Spyro2008/hooks/IKHkHero.h"
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/CKS08InGameInterfaceBoss.h"
#include "Spyro2008/logic/CKS08InGameInterfaceCenter.h"
#include "Spyro2008/logic/CKS08InGameInterfaceLeft.h"
#include "Spyro2008/logic/CKS08InGameInterfaceRight.h"
#include "Spyro2008/logic/HudGaugeOps.h"
#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/logic/sound/CKSound.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/io/IKFile.h"

// 0x004fe638 CKS08GameManager_DestroyTextures: the sixteen HUD textures released (RwTextureDestroy: the
// reference LoadHudResources kept), in the original's order; the pointers stay.
void CKS08GameManager::DestroyTextures() {
    static const uint8_t kOrder[16] = {2, 1, 0, 5, 4, 3, 10, 9, 8, 7, 6, 15, 14, 13, 12, 11};  // +0xbec, +0xbe8, ...
    for (uint8_t index : kOrder) {
        if (m_apHudTextures[index] != nullptr) TextureRef_Release(m_apHudTextures[index]);
    }
}

// 0x004ff768 CKS08GameManager_LoadHudResources_maybe: a level's HUD words, a reference and sixteen
// textures (resolved), in the original's order.
void CKS08GameManager::LoadHudResources(IKFile* stream, int32_t mode) {
    if (mode != 0) return;
    ReadU32LE(stream, &m_unkBD8);
    ReadU32LE(stream, &m_unkBE0);
    ReadU32LE(stream, &m_unkC3C);
    ReadF32LE(stream, &m_fUnkC40);
    IKFile_ReadRef(stream, &m_unkC44);
    // +0xbec, +0xbe8, +0xbe4, +0xbf8, +0xbf4, +0xbf0, +0xc0c, +0xc08, +0xc04, +0xc00, +0xbfc, +0xc20,
    // +0xc1c, +0xc18, +0xc14, +0xc10
    static const uint8_t kOrder[16] = {2, 1, 0, 5, 4, 3, 10, 9, 8, 7, 6, 15, 14, 13, 12, 11};
    for (uint8_t index : kOrder) IKFile_ReadTextureRef(stream, &m_apHudTextures[index], 1);
}

// 0x00504040 CKS08GameManager_State6_maybe: the main menu. Enter: flag bit 1 cleared; the menu by +0x2fc
// (1: the main menu, vt+0x2f8; 2: vt+0xc4 ? 3 : 6). Leave: sound 0 of +0xbdc stopped (STUB(sound)), no menu.
uint8_t CKS08GameManager::State6(int32_t phase, uint8_t other) {
    const uint8_t state = State6Common(phase, other);
    if (state != 6) return state;
    if (phase == 1) {
        m_unkAFC &= ~2u;
        if (m_unk2FC == 1) {
            m_aMenuStack[0] = MainMenuId();
            m_ui32MenuStackDepth = 1;
            return 6;
        }
        if (m_unk2FC == 2) {
            m_aMenuStack[0] = VfC4() == 0 ? 6 : 3;
            m_ui32MenuStackDepth = 1;
            return 6;
        }
    } else if (phase == 2) {
        // CKSoundDictionaryID_GetSound_2(+0xbdc, 0), CKSound_IsPlaying_maybe, Sound_Stop: STUB(sound).
        m_aMenuStack[0] = NoMenuId();
        m_ui32MenuStackDepth = 1;
        return 6;
    }
    return 6;
}

// 0x00504248 CKS08GameManager_State2_maybe. Enter: flag bit 0 cleared, menu 8. Update: once the flag is set
// (by the menu), no menu and state 0.
uint8_t CKS08GameManager::State2(int32_t phase, uint8_t other) {
    const uint8_t state = State2Common(phase, other);
    if (state != 2) return state;
    if (phase == 0) {
        if ((m_unkAFC & 1) != 0) {
            m_aMenuStack[0] = 0x24;
            m_ui32MenuStackDepth = 1;
            return 0;
        }
    } else if (phase == 1) {
        m_unkAFC &= ~1u;
        m_aMenuStack[0] = 8;
        m_ui32MenuStackDepth = static_cast<uint32_t>(phase);
        return 2;
    }
    return 2;
}

// ---- C1.6 gm: the dragon stat HUD ----
// The HUD interfaces (vt+0x34c): [0] Spyro's CKS08InGameInterfaceLeft, [2] Cynder's
// CKS08InGameInterfaceRight. LVL000 (the front end) has neither, so every refresh below returns at once.

// 0x004ff220 CKS08GameManager_SelectSpyroHudPanelElement_maybe: with Spyro's panel, its element object
// set to +0xbfc[element] (CKS08InGameInterfaceLeft_SetPanelElementObject_maybe).
void CKS08GameManager::SelectSpyroHudPanelElement(uint8_t element) {
    if (GetHudInterfaces()[0] == nullptr) return;
    static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])
        ->SetPanelElementObject(static_cast<RwTexture*>(m_apHudTextures[6 + element]));
}

// 0x00500a88 CKS08GameManager_SelectCynderHudPanelElement_maybe: the same for Cynder's panel and
// +0xc10[element] (CKS08InGameInterfaceRight_SetPanelElementObject_maybe).
void CKS08GameManager::SelectCynderHudPanelElement(uint8_t element) {
    if (GetHudInterfaces()[2] == nullptr) return;
    static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])
        ->SetPanelElementObject(static_cast<RwTexture*>(m_apHudTextures[11 + element]));
}

// 0x00502410 ResetDragonStatHud: +0xc2c, +0xbd4, +0xc28, +0xc30, +0xc24, +0xc34, +0xc38 = 0, then for
// Cynder (1) and Spyro (0) the upgrade text (UpdateDragonUpgradeText_maybe 0x500140, both first) and the
// health gauge (0x5013a8), health capacity marker (0x501188), mana gauge (0x500ee8) and mana capacity
// marker (0x500cc8). Each refresh returns at once without its panel.
void CKS08GameManager::ResetDragonStatHud() {
    m_fUnkC2C = 0.0f;
    m_unkBD4 = 0.0f;
    m_fUnkC28 = 0.0f;
    m_fUnkC30 = 0.0f;
    m_fUnkC24 = 0.0f;
    m_unkC34 = 0;
    m_unkC38 = 0;
    UpdateDragonUpgradeText(1, 0);
    UpdateDragonUpgradeText(0, 0);
    UpdateDragonHealthGauge(1);
    UpdateDragonHealthCapacityMarker(1);
    UpdateDragonManaGauge(1);
    UpdateDragonManaCapacityMarker(1);
    UpdateDragonHealthGauge(0);
    UpdateDragonHealthCapacityMarker(0);
    UpdateDragonManaGauge(0);
    UpdateDragonManaCapacityMarker(0);
}

// 0x00502340 ResetDragonStatHud_2
void CKS08GameManager::ResetDragonStatHud2() {
    m_unkBD4 = 0.0f;
    UpdateDragonHealthGauge(1);
    UpdateDragonHealthCapacityMarker(1);
    UpdateDragonManaGauge(1);
    UpdateDragonManaCapacityMarker(1);
    UpdateDragonUpgradeText(1, 0);
    UpdateDragonHealthGauge(0);
    UpdateDragonHealthCapacityMarker(0);
    UpdateDragonManaGauge(0);
    UpdateDragonManaCapacityMarker(0);
    UpdateDragonUpgradeText(0, 0);
    m_fUnkC2C = 0.0f;
    m_unkC34 = 0;
    m_fUnkC28 = 0.0f;
    m_fUnkC30 = 0.0f;
    m_unkC38 = 0;
    m_fUnkC24 = 0.0f;
}

// ---- C2.2 gm: the dragon stat HUD and the in-game HUD update ----
// The HUD interfaces (GetHudInterfaces): [0] Spyro's CKS08InGameInterfaceLeft, [1] the centre screen,
// [2] Cynder's CKS08InGameInterfaceRight, [3] / [4] the two boss gauges.
namespace {
CKS08InGameInterfaceLeft* LeftHud(CKS08GameManager* manager) {
    return static_cast<CKS08InGameInterfaceLeft*>(manager->GetHudInterfaces()[0]);
}
CKS08InGameInterfaceCenter* CenterHud(CKS08GameManager* manager) {
    return static_cast<CKS08InGameInterfaceCenter*>(manager->GetHudInterfaces()[1]);
}
CKS08InGameInterfaceRight* RightHud(CKS08GameManager* manager) {
    return static_cast<CKS08InGameInterfaceRight*>(manager->GetHudInterfaces()[2]);
}
CKS08GameStructure* StatsOf(CKS08GameManager* manager) { return static_cast<CKS08GameStructure*>(manager->m_gameStructure); }
}  // namespace

// 0x00500140 UpdateDragonUpgradeText_maybe: the dragon's panel shows the free upgrade points (+0x84 / +0x88
// of the game structure), or "MAX" once every upgrade level is bought.
void CKS08GameManager::UpdateDragonUpgradeText(uint8_t dragon, uint8_t shake) {
    CKS08GameStructure* stats = StatsOf(this);
    char text[16];
    if (dragon == 0) {
        CKS08InGameInterfaceLeft* hud = LeftHud(this);
        if (hud == nullptr) return;
        const uint32_t costs = m_aUnkC48[3].m_unk8 + m_aUnkC48[2].m_unk8 + m_aUnkC48[1].m_unk8 + m_aUnkC48[0].m_unk8;
        if (GetDragonTotalUpgradePoints(stats, 0) < costs) {
            std::snprintf(text, sizeof(text), "%d", static_cast<int32_t>(stats->RtWord(0x84)));
        } else {
            std::strcpy(text, "MAX");
        }
        hud->ShowUpgradeText(text, shake);
    } else if (dragon == 1) {
        CKS08InGameInterfaceRight* hud = RightHud(this);
        if (hud == nullptr) return;
        const uint32_t costs = m_aUnkC84[3].m_unk8 + m_aUnkC84[2].m_unk8 + m_aUnkC84[1].m_unk8 + m_aUnkC84[0].m_unk8;
        if (GetDragonTotalUpgradePoints(stats, 1) < costs) {
            std::snprintf(text, sizeof(text), "%d", static_cast<int32_t>(stats->RtWord(0x88)));
        } else {
            std::strcpy(text, "MAX");
        }
        hud->ShowUpgradeText(text, shake);
    }
}

// 0x005013a8 UpdateDragonHealthGauge: the gauge to health / (capacity with every health item), and its
// "full" flag to health >= the capacity of the collected ones.
void CKS08GameManager::UpdateDragonHealthGauge(uint8_t dragon) {
    CKS08GameStructure* stats = StatsOf(this);
    if (dragon == 0) {
        CKS08InGameInterfaceLeft* hud = LeftHud(this);
        if (hud == nullptr) return;
        const float health = static_cast<float>(stats->m_unk4c);
        SetSpyroHealthGaugeValue(health / static_cast<float>(static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 1))), hud);
        const uint32_t current = stats->m_unk4c;
        const uint32_t capacity = static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 0));
        hudgauge::SuperGaugeSetFullFlag(static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater224), current >= capacity ? 1 : 0);
    } else if (dragon == 1) {
        CKS08InGameInterfaceRight* hud = RightHud(this);
        if (hud == nullptr) return;
        const float health = static_cast<float>(stats->m_unk54);
        SetCynderHealthGaugeValue(health / static_cast<float>(static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 1))), hud);
        const uint32_t current = stats->m_unk54;
        const uint32_t capacity = static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 0));
        hudgauge::SuperGaugeSetFullFlag(static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater21c), current >= capacity ? 1 : 0);
    }
}

// 0x00501188 UpdateDragonHealthCapacityMarker_maybe: the gauge's marker to capacity(collected) / capacity(all).
void CKS08GameManager::UpdateDragonHealthCapacityMarker(uint8_t dragon) {
    CKS08GameStructure* stats = StatsOf(this);
    if (dragon == 0) {
        CKS08InGameInterfaceLeft* hud = LeftHud(this);
        if (hud == nullptr) return;
        const uint32_t collected = static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 0));
        const uint32_t all = static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 1));
        hudgauge::SuperGaugeSetMarker(static_cast<float>(collected) / static_cast<float>(all),
                                      static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater224));
    } else if (dragon == 1) {
        CKS08InGameInterfaceRight* hud = RightHud(this);
        if (hud == nullptr) return;
        const uint32_t collected = static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 0));
        const uint32_t all = static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 1));
        hudgauge::SuperGaugeSetMarker(static_cast<float>(collected) / static_cast<float>(all),
                                      static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater21c));
    }
}

// 0x00500ee8 UpdateDragonManaGauge: as the health gauge, with the mana (+0x64 / +0x6c).
void CKS08GameManager::UpdateDragonManaGauge(uint8_t dragon) {
    CKS08GameStructure* stats = StatsOf(this);
    if (dragon == 0) {
        CKS08InGameInterfaceLeft* hud = LeftHud(this);
        if (hud == nullptr) return;
        const float mana = static_cast<float>(stats->m_unk64);
        SetSpyroManaGaugeValue(mana / static_cast<float>(static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 1))), hud);
        const uint32_t current = stats->m_unk64;
        const uint32_t capacity = static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 0));
        hudgauge::SuperGaugeSetFullFlag(static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater22c), current >= capacity ? 1 : 0);
    } else if (dragon == 1) {
        CKS08InGameInterfaceRight* hud = RightHud(this);
        if (hud == nullptr) return;
        const float mana = static_cast<float>(stats->m_unk6c);
        SetCynderManaGaugeValue(mana / static_cast<float>(static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 1))), hud);
        const uint32_t current = stats->m_unk6c;
        const uint32_t capacity = static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 0));
        hudgauge::SuperGaugeSetFullFlag(static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater224), current >= capacity ? 1 : 0);
    }
}

// 0x00500cc8 UpdateDragonManaCapacityMarker_maybe
void CKS08GameManager::UpdateDragonManaCapacityMarker(uint8_t dragon) {
    CKS08GameStructure* stats = StatsOf(this);
    if (dragon == 0) {
        CKS08InGameInterfaceLeft* hud = LeftHud(this);
        if (hud == nullptr) return;
        const uint32_t collected = static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 0));
        const uint32_t all = static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 1));
        hudgauge::SuperGaugeSetMarker(static_cast<float>(collected) / static_cast<float>(all),
                                      static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater22c));
    } else if (dragon == 1) {
        CKS08InGameInterfaceRight* hud = RightHud(this);
        if (hud == nullptr) return;
        const uint32_t collected = static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 0));
        const uint32_t all = static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 1));
        hudgauge::SuperGaugeSetMarker(static_cast<float>(collected) / static_cast<float>(all),
                                      static_cast<CKSuperGaugeCpntUpdater*>(hud->m_pGaugeUpdater224));
    }
}

// 0x00501648 UpdateDragonHealthAndManaGauges
void CKS08GameManager::UpdateDragonHealthAndManaGauges(uint8_t dragon, int32_t health, int32_t mana) {
    if (health != 0) {
        UpdateDragonHealthGauge(dragon);
        UpdateDragonHealthCapacityMarker(dragon);
    }
    if (mana == 0) return;
    UpdateDragonManaGauge(dragon);
    UpdateDragonManaCapacityMarker(dragon);
}

// 0x00500880 CKS08GameManager_CheatMaxUpgradePoints_maybe
void CKS08GameManager::CheatMaxUpgradePoints() {
    AddDragonUpgradePoints(0, 1000000);  // 0x500418
    AddDragonUpgradePoints(1, 1000000);
}

// 0x005008d0 CKS08GameManager_HidePlayerHudPanel_maybe (vt+0x2dc): the panel of the controlled hero `player`
// hidden: Spyro's panel when the hero is Spyro (dragon 0) or the only one, Cynder's when it is Cynder or the
// only one.
void CKS08GameManager::HidePlayerHudPanel(uint8_t player) {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_unk04[1]);
    const IKHkHero* hero = static_cast<const IKHkHero*>(group->m_apControlledHeroes[player]);
    const uint8_t count = GetControlledHeroCount();
    if (hero->m_ui8Hero == 0 || count == 1) {
        if (LeftHud(this) != nullptr) LeftHud(this)->HidePanel();
    }
    if (hero->m_ui8Hero == 1 || count == 1) {
        if (RightHud(this) != nullptr) RightHud(this)->HidePanel();
    }
}

// 0x00502688 CKS08GameManager_ShowPlayerHudPanel_maybe (vt+0x2d8): with a text, the panel of the controlled hero
// `player` shown (type 0 the normal panel, 1 the type-1 one), the first counter text variable set to `value`,
// and the other dragon's panel hidden when this hero is alone.
void CKS08GameManager::ShowPlayerHudPanel(IKSerializable* text, int32_t value, int32_t type, uint8_t player) {
    if (text == nullptr) return;
    IKGrpHero* group = static_cast<IKGrpHero*>(m_unk04[1]);
    const IKHkHero* hero = static_cast<const IKHkHero*>(group->m_apControlledHeroes[player]);
    const uint8_t count = GetControlledHeroCount();
    if (hero->m_ui8Hero == 0) {
        CKS08InGameInterfaceLeft* left = LeftHud(this);
        if (left != nullptr) {
            if (type == 0) left->ShowPanel(text);
            else if (type == 1) left->ShowPanelType1(text);
        }
        g_pEngine->m_locManager->SetTextVariableValue(GetCounterTextVarTable()[0], value);  // vt+0x354
        if (count == 1 && RightHud(this) != nullptr) RightHud(this)->HidePanel();
    } else if (hero->m_ui8Hero == 1) {
        CKS08InGameInterfaceRight* right = RightHud(this);
        if (right != nullptr) {
            if (type == 0) right->ShowPanel(text);
            else if (type == 1) right->ShowPanelType1(text);
        }
        g_pEngine->m_locManager->SetTextVariableValue(GetCounterTextVarTable()[0], value);
        if (GetControlledHeroCount() == 1 && LeftHud(this) != nullptr) LeftHud(this)->HidePanel();
    }
}

// 0x004ff318 CKS08GameManager_UpdateBossGaugeTotals_maybe / 0x004ff540 ..UpdateSecondBossGaugeTotals_maybe: the
// boss zones' (CKHkS08CrumblyZoneMultiState) health and maximum health summed (+0xbac / +0xbb0, the second
// boss's +0xbc0 / +0xbc4; fadds) and written to the boss gauge screen's (hud [3] / [4]) +0xf4, +0xf8 and +0xfc (the
// maximum twice), each when the screen exists.
namespace {
void SumBossZones(const TVector<IKSerializable*, 5>& zones, float* totals) {
    totals[1] = 0.0f;
    totals[0] = 0.0f;
    for (uint32_t i = 0; i < zones.m_ui32NbUsedElt; ++i) {
        const CKHkS08CrumblyZoneMultiState* zone = static_cast<const CKHkS08CrumblyZoneMultiState*>(zones.m_pBlock[i]);
        totals[0] = totals[0] + zone->GetTotalHealth();     // 0x00413fe8
        totals[1] = totals[1] + zone->GetTotalMaxHealth();  // 0x00414098
    }
}
void SetBossScreen(CKS08GameManager* manager, uint32_t hud, const float* totals) {
    CKS08InGameInterfaceBoss* screen = static_cast<CKS08InGameInterfaceBoss*>(manager->GetHudInterfaces()[hud]);
    if (screen != nullptr) screen->m_fUnkf4 = totals[0];
    screen = static_cast<CKS08InGameInterfaceBoss*>(manager->GetHudInterfaces()[hud]);
    if (screen != nullptr) screen->m_fUnkf8 = totals[1];
    screen = static_cast<CKS08InGameInterfaceBoss*>(manager->GetHudInterfaces()[hud]);
    if (screen != nullptr) screen->m_fUnkfc = totals[1];
}
}  // namespace

void CKS08GameManager::UpdateBossGaugeTotals() {
    if (m_unkBB4.m_ui32NbUsedElt == 0) return;
    SumBossZones(m_unkBB4, m_afUnkBAC);
    SetBossScreen(this, 3, m_afUnkBAC);
}

void CKS08GameManager::UpdateSecondBossGaugeTotals() {
    if (m_unkBC8.m_ui32NbUsedElt == 0) return;
    SumBossZones(m_unkBC8, m_afUnkBC0);
    SetBossScreen(this, 4, m_afUnkBC0);
}

// 0x004feb00 / 0x004fea60 / 0x004fe9c0 (C2.8 golem): the boss gauge screen's (hud [3]) +0xf4 / +0xf8 / +0xfc.
void CKS08GameManager::SetBossGaugeHealth(float value) {
    if (GetHudInterfaces()[3] == nullptr) return;  // vt+0x34c
    static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[3])->m_fUnkf4 = value;
}
void CKS08GameManager::SetEnemyGaugeMaxHealth(float value) {
    if (GetHudInterfaces()[3] == nullptr) return;
    static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[3])->m_fUnkf8 = value;
}
void CKS08GameManager::SetEnemyGaugeMaxHealth2(float value) {
    if (GetHudInterfaces()[3] == nullptr) return;
    static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[3])->m_fUnkfc = value;
}

// 0x00501ea0 CKS08GameManager_RefreshBossGauge_maybe (C2.8 golem): the boss screen's message out 1 (vt+0xc0) posted,
// +0xe0 bit 0 set, its timer cleared.
void CKS08GameManager::RefreshBossGauge() {
    if (GetHudInterfaces()[3] == nullptr) return;
    CKS08InGameInterfaceBoss* boss = static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[3]);
    IKSerializable* out = boss->VfC0()[1];
    if (out != nullptr) static_cast<CKFlashMessageOut*>(out)->PostFlashMessage();
    boss->m_baFlagsE0 = static_cast<uint8_t>((boss->m_baFlagsE0 & 0xfeu) | 1u);
    boss->m_fTime = 0.0f;
}

// 0x00500628 CKS08GameManager_UpdateComboTimers_maybe: each dragon's combo (Cynder's +0xc24..+0xc38 block
// first: timer +0xc30, elapsed +0xc28; then Spyro's +0xc2c / +0xc24): while the timer runs, the elapsed time
// grows and the timer falls by (elapsed * +0xc40 + 1) * dt; at zero the best combo is recorded, the combo
// converted to upgrade points (unless +0xafc bit 5), the count reset and the combo display ended.
// The points: the curve +0xaf0 at the hit count (fcfid / frsp), truncated to a 64-bit integer (fctidz), its low word.
static uint32_t ComboPoints(CKS08GameManager* manager, uint32_t hits) {
    const float x = static_cast<float>(static_cast<double>(static_cast<uint64_t>(hits)));
    const float y = static_cast<CKCurve2DCpnt*>(manager->m_unkAF0)->Evaluate(x);  // 0x249ea8 CKCurve_Evaluate_maybe
    return static_cast<uint32_t>(ppc::fctidz(y));
}

void CKS08GameManager::UpdateComboTimers(IKTime* frameClock) {
    CKS08GameStructure* stats = StatsOf(this);
    float timer = m_fUnkC30;
    if (timer > 0.0f) {
        const float elapsed = m_fUnkC28 + frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
        float step = ppc::fmadds(elapsed, m_fUnkC40, 1.0f);
        m_fUnkC28 = elapsed;
        step = step * frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
        timer = timer - step;
        m_fUnkC30 = timer;
        if (timer <= 0.0f) {
            stats->RecordBestCombo(1, m_unkC38);
            m_fUnkC30 = 0.0f;
            m_fUnkC28 = 0.0f;
            if (VfC4() == 0) AddDragonUpgradePoints(1, ComboPoints(this, m_unkC38));
            m_unkC38 = 0;
            EndComboDisplay(1);  // vt+0x364
        }
    }
    timer = m_fUnkC2C;
    if (timer > 0.0f) {
        const float elapsed = m_fUnkC24 + frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
        float step = ppc::fmadds(elapsed, m_fUnkC40, 1.0f);
        m_fUnkC24 = elapsed;
        step = step * frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
        timer = timer - step;
        m_fUnkC2C = timer;
        if (timer <= 0.0f) {
            stats->RecordBestCombo(0, m_unkC34);
            m_fUnkC2C = 0.0f;
            m_fUnkC24 = 0.0f;
            if (VfC4() == 0) AddDragonUpgradePoints(0, ComboPoints(this, m_unkC34));
            m_unkC34 = 0;
            EndComboDisplay(0);  // vt+0x364
        }
    }
}

// 0x004fed80 CKS08GameManager_SetCenterTwinGauges_maybe: the centre screen's twin gauges to the two values,
// their markers full.
void CKS08GameManager::SetCenterTwinGauges(float first, float second) {
    CKS08InGameInterfaceCenter* center = CenterHud(this);
    if (center == nullptr) return;
    center->SetGaugeValue(first, 0);
    center->SetGaugeMarker(1.0f, 0);
    center->SetGaugeValue(second, 1);
    center->SetGaugeMarker(1.0f, 1);
}

// 0x00501b00 CKS08GameManager_UpdateInGameHud_maybe: the combo timers, the countdown at +0xbd4, the centre
// twin gauges from the game structure's +0x74 / +0x78 over +0x7c (the fury gauge hidden when both are
// empty and it is shown), and the boss gauge totals.
void CKS08GameManager::UpdateInGameHud(IKTime* frameClock) {
    UpdateComboTimers(frameClock);
    if (m_unkBD4 <= 0.0f) m_unkBD4 = 0.0f;
    else m_unkBD4 = m_unkBD4 - frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    CKS08GameStructure* stats = StatsOf(this);
    const float total = static_cast<float>(stats->m_unk7c);
    const float first = static_cast<float>(stats->m_unk74) / total;
    const float second = static_cast<float>(stats->m_unk78) / total;
    if (first > 0.0f || second > 0.0f) {
        SetCenterTwinGauges(first, second);
    } else if (CenterHud(this) != nullptr && CenterHud(this)->IsFuryGaugeShown()) {
        CenterHud(this)->HideFuryGauge();
    }
    UpdateBossGaugeTotals();
    UpdateSecondBossGaugeTotals();
}

// 0x004ff2d8 NotifySpyroMovementModeChanged_Stub: only vt+0x34c (the HUD list), whose result is dropped.
void CKS08GameManager::NotifySpyroMovementModeChanged(uint8_t) { (void)GetHudInterfaces(); }

// 0x00500b38 NotifyCynderMovementModeChanged_Stub: the same for Cynder.
void CKS08GameManager::NotifyCynderMovementModeChanged(uint8_t) { (void)GetHudInterfaces(); }

// 0x005022b0 RefreshDragonStatDisplays_maybe
void CKS08GameManager::RefreshDragonStatDisplays(uint8_t dragon, int32_t health, int32_t mana) {
    if (health != 0) {
        UpdateDragonHealthGauge(dragon);           // 0x005013a8
        UpdateDragonHealthCapacityMarker(dragon);  // 0x00501188
    }
    if (mana != 0) {
        UpdateDragonManaGauge(dragon);           // 0x00500ee8
        UpdateDragonManaCapacityMarker(dragon);  // 0x00500cc8
    }
    ShowDragonStatChangeFeedback(dragon);  // 0x501fb8
}

// ---- C2.7 step 7: the HUD pieces ----

// 0x00502a80 CKS08GameManager_UpdateCounterTextVariables_maybe
void CKS08GameManager::UpdateCounterTextVariables() {
    CKS08GameStructure* stats = StatsOf(this);
    for (uint32_t i = 0; i < 6; ++i) {
        const uint8_t value = stats->RtByte(0x1e4 + i);
        CLocManager* loc = g_pEngine->m_locManager;
        loc->SetTextVariableValue(GetCounterTextVarTable()[5 + i], value);  // vt+0x354, entries +0x14..+0x28
    }
}

// ---- pre-C2.7 gamemgr: a collectible picked up (CKS08GameLevelCollectible_ApplyCollect_maybe) ----
#include "Spyro2008/logic/ui/CKS08MenuPauseInfo.h"
#include "k2000/memory/Mem.h"

namespace {
// Text `index` of a text accessor (its list, else its single text).
IKSerializable* AccessorTextAt(IKSerializable* accessor, uint32_t index) {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(accessor);
    return texts->m_texts.m_pBlock != nullptr ? texts->m_texts.m_pBlock[index] : texts->m_pText;
}

// The info pages menu (menu 0x10, vt+0x344) gets a page text (its vector grows by 3), inlined in the callers.
void AddInfoPage(CKS08MenuPauseInfo* info, IKSerializable* text) {
    TVector<IKSerializable*, 3>& pages = info->m_aPageTextIds;
    if (pages.m_ui32NbUsedElt == pages.m_ui32NbElt) {
        uint32_t capacity = pages.m_ui32NbElt + 3;
        if (capacity == 0) capacity = 3;
        pages.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(pages.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        pages.m_ui32NbElt = capacity;
    }
    pages.m_pBlock[pages.m_ui32NbUsedElt] = text;
    ++pages.m_ui32NbUsedElt;
}

// The shard HUD of a category (1 health, 2 mana) the two refresh functions share: the shards left to the next upgrade
// per dragon (divisor - collected % divisor) into the text variables `variable0` / `variable1` of the counter table,
// the dragon's panel gauge; with the info popups on and `show`, the info page: the dragon's title, then "a shard",
// "an upgrade" or "all" (texts of the accessor +0xf0c, `texts` = {title0, partial0, upgrade0, all0, title1, ...}).
struct ShardHudTexts {
    uint32_t m_title[2];
    uint32_t m_partial[2];
    uint32_t m_upgrade[2];
    uint32_t m_all[2];
};
void RefreshShardHud(CKS08GameManager* manager, uint8_t category, uint8_t divisor0, uint8_t divisor1, uint32_t variable0,
                     uint32_t variable1, bool mana, const ShardHudTexts& texts, uint8_t dragon, uint32_t show) {
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    const uint32_t collected = structure->CountItemsByCategory(category, 1);  // 0x50f730
    CLocManager* loc = g_pEngine->m_locManager;
    const uint32_t left0 = divisor0 - (collected - ppc::divwu(collected, divisor0) * divisor0);
    loc->SetTextVariableValue(manager->GetCounterTextVarTable()[variable0], static_cast<int32_t>(left0));  // vt+0x354, 0x37730
    const uint32_t left1 = divisor1 - (collected - ppc::divwu(collected, divisor1) * divisor1);
    loc->SetTextVariableValue(manager->GetCounterTextVarTable()[variable1], static_cast<int32_t>(left1));
    IKSerializable** huds = manager->GetHudInterfaces();  // vt+0x34c
    if (dragon == 0) {
        CKS08InGameInterfaceLeft* left = static_cast<CKS08InGameInterfaceLeft*>(huds[0]);
        if (mana) left->SetManaShardGauge(static_cast<uint8_t>(left0), static_cast<uint8_t>(show));
        else left->SetHealthShardGauge(static_cast<uint8_t>(left0), static_cast<uint8_t>(show));
    } else {
        CKS08InGameInterfaceRight* right = static_cast<CKS08InGameInterfaceRight*>(huds[2]);
        if (mana) right->SetManaShardGauge(static_cast<uint8_t>(left1), static_cast<uint8_t>(show));
        else right->SetHealthShardGauge(static_cast<uint8_t>(left1), static_cast<uint8_t>(show));
    }
    if (structure->AreInfoPopupsEnabled() == 0 || show == 0) return;  // 0x5102e0
    const uint32_t side = dragon == 0 ? 0 : 1;
    const uint32_t left = side == 0 ? left0 : left1;
    const uint8_t divisor = side == 0 ? divisor0 : divisor1;
    CKS08MenuPauseInfo* info = static_cast<CKS08MenuPauseInfo*>(manager->Vf344()[0x10]);  // vt+0x344
    info->SetTitleText(AccessorTextAt(manager->m_unkF00[3], texts.m_title[side]));  // +0xf0c; 0x55fbf8
    uint32_t page;
    if (left == 0 || divisor == left) {
        page = collected == structure->CountItemsByCategory(category, 0) ? texts.m_all[side] : texts.m_upgrade[side];
    } else {
        page = texts.m_partial[side];
    }
    AddInfoPage(static_cast<CKS08MenuPauseInfo*>(manager->Vf344()[0x10]), AccessorTextAt(manager->m_unkF00[3], page));
    static_cast<CKS08MenuPauseInfo*>(manager->Vf344()[0x10])->m_bTimeScaling = 1;
    manager->m_unkAFC = (manager->m_unkAFC & ~0x80u) | 0x80u;
}
}  // namespace

// 0x005032d0 CKS08GameManager_RefreshHealthShardHud_maybe: category 1, the divisors +0x45 / +0x46, the text variables 1
// and 3, the texts 12 / 14 (titles), 0 / 6, 1 / 7, 2 / 8.
void CKS08GameManager::RefreshHealthShardHud(uint8_t dragon, uint32_t show) {
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(m_gameStructure);
    const ShardHudTexts texts = {{12, 14}, {0, 6}, {1, 7}, {2, 8}};
    RefreshShardHud(this, 1, structure->HealthDivisor0(), structure->HealthDivisor1(), 1, 3, false, texts, dragon, show);
}

// 0x00502ca0 CKS08GameManager_RefreshManaShardHud_maybe: category 2, the divisors +0x5c / +0x5d, the text variables 2
// and 4, the texts 13 / 15 (titles), 3 / 9, 4 / 10, 5 / 11.
void CKS08GameManager::RefreshManaShardHud(uint8_t dragon, uint32_t show) {
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(m_gameStructure);
    const ShardHudTexts texts = {{13, 15}, {3, 9}, {4, 10}, {5, 11}};
    RefreshShardHud(this, 2, structure->m_bManaDivisor0, structure->m_bManaDivisor1, 2, 4, true, texts, dragon, show);
}

// 0x004ffdd0 CKS08GameManager_QueueFirstCollectibleInfo_maybe: with the info popups on, the info page of the first
// collectible (the accessor +0xf08's texts 18, the title, and 19), the slow motion and the info flag (+0xafc bit 7).
void CKS08GameManager::QueueFirstCollectibleInfo() {
    if (static_cast<CKS08GameStructure*>(m_gameStructure)->AreInfoPopupsEnabled() == 0) return;
    static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10])->SetTitleText(AccessorTextAt(m_unkF00[2], 18));  // +0xf08
    AddInfoPage(static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10]), AccessorTextAt(m_unkF00[2], 19));
    static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10])->m_bTimeScaling = 1;
    m_unkAFC = (m_unkAFC & ~0x80u) | 0x80u;
}

// 0x00501938 CKS08GameManager_QueueCollectibleMessage_maybe: the accessor +0xf10's first text on the centre HUD.
void CKS08GameManager::QueueCollectibleMessage() {
    IKSerializable* text = AccessorTextAt(m_unkF00[4], 0);
    if (GetHudInterfaces()[1] != nullptr) static_cast<CKS08InGameInterfaceCenter*>(GetHudInterfaces()[1])->QueueMessage(text);  // 0x536310
}

// 0x00501a08 CKS08GameManager_ShowCollectedItemMessage_maybe: text 9 a + 3 b + c of the accessor +0xf08 on the centre HUD.
void CKS08GameManager::ShowCollectedItemMessage(uint8_t a, uint8_t b, uint8_t c) {
    IKSerializable* text = AccessorTextAt(m_unkF00[2], static_cast<uint32_t>(a) * 9 + static_cast<uint32_t>(b) * 3 + c);
    if (GetHudInterfaces()[1] != nullptr) static_cast<CKS08InGameInterfaceCenter*>(GetHudInterfaces()[1])->QueueMessage(text);
}

// 0x00501860 CKS08GameManager_ShowCenterMessage_maybe
void CKS08GameManager::ShowCenterMessage(uint8_t index) {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(m_unkF00[5]);  // +0xf14
    IKSerializable* text = texts->m_texts.m_pBlock != nullptr ? texts->m_texts.m_pBlock[index] : texts->m_pText;
    if (GetHudInterfaces()[1] != nullptr) static_cast<CKS08InGameInterfaceCenter*>(GetHudInterfaces()[1])->QueueMessage(text);
}

namespace {
// The selection sound of ShowSpyro/CynderSelectedElementHud: entry `index` of the dictionary +0xbdc, not looping, from 0.0.
void PlaySelectedElementSound(CKS08GameManager* manager, uint32_t index) {
    CKSound* sound = static_cast<CKSoundDictionaryID*>(manager->m_unkBDC)->GetSound2(index);  // 0x112bd8
    if (sound == nullptr) return;
    sound->SetLoop(0);
    sound->Play(0.0f);  // lfs TOC1+0x7338
}
}  // namespace

// 0x005039e8 ShowSpyroSelectedElementHud
void CKS08GameManager::ShowSpyroSelectedElementHud(uint8_t element) {
    if (GetHudInterfaces()[0] == nullptr) return;
    if (element <= 4) PlaySelectedElementSound(this, 1u + element);  // the jump table 0x503adc
    static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])
        ->SelectElement(static_cast<RwTexture*>(m_apHudTextures[6 + element]));  // +0xbfc
    ShowDragonStatChangeFeedback(0);
}

// 0x005024d8 ShowCynderSelectedElementHud
void CKS08GameManager::ShowCynderSelectedElementHud(uint8_t element) {
    if (GetHudInterfaces()[2] == nullptr) return;
    if (element <= 4) PlaySelectedElementSound(this, 6u + element);  // the jump table 0x5025c4
    static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])
        ->SelectElement(static_cast<RwTexture*>(m_apHudTextures[11 + element]));  // +0xc10
    ShowDragonStatChangeFeedback(1);
}

// 0x00501fb8 ShowDragonStatChangeFeedback_maybe
void CKS08GameManager::ShowDragonStatChangeFeedback(int32_t dragon) {
    if (dragon == 0) {
        CKS08InGameInterfaceLeft* hud = static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0]);
        if (hud == nullptr) return;
        UpdateDragonUpgradeText(0, static_cast<uint8_t>(hud->m_ui8Active215 ^ 1));
        hud = static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0]);
        if (hud->VfC0()[1] != nullptr) static_cast<CKFlashMessageOut*>(hud->VfC0()[1])->PostFlashMessage();
        hud->m_ui8Flags214 = static_cast<uint8_t>((hud->m_ui8Flags214 & ~1u) | 1u);
        hud->m_ui8Active215 = 1;
        hud->m_fUnk21c = 0.0f;
    } else if (dragon == 1) {
        CKS08InGameInterfaceRight* hud = static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2]);
        if (hud == nullptr) return;
        UpdateDragonUpgradeText(1, static_cast<uint8_t>(hud->m_ui8Active215 ^ 1));
        hud = static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2]);
        if (hud->VfC0()[1] != nullptr) static_cast<CKFlashMessageOut*>(hud->VfC0()[1])->PostFlashMessage();
        hud->m_ui8Flags214 = static_cast<uint8_t>((hud->m_ui8Flags214 & ~1u) | 1u);
        hud->m_ui8Active215 = 1;
        hud->m_fUnk22c = 0.0f;
    }
}

// 0x00500418 CKS08GameManager_AddDragonUpgradePoints_maybe
void CKS08GameManager::AddDragonUpgradePoints(uint8_t dragon, uint32_t points) {
    CKS08GameStructure* stats = StatsOf(this);
    const uint32_t total = GetDragonTotalUpgradePoints(stats, dragon);  // 0x50f050
    const SRecord* costs = dragon == 0 ? m_aUnkC48 : m_aUnkC84;
    const uint32_t cap = costs[3].m_unk8 + costs[2].m_unk8 + costs[1].m_unk8 + costs[0].m_unk8;
    if (cap < total + points) points = cap - total;
    if (dragon == 0) stats->SetRtWord(0x84, points + stats->RtWord(0x84));
    else if (dragon == 1) stats->SetRtWord(0x88, points + stats->RtWord(0x88));
    if (total < 5000) {
        const uint32_t now = dragon == 0 ? stats->RtWord(0x84) : stats->RtWord(0x88);
        bool none = now > 4999;
        for (uint32_t offset = 0x8c; none && offset <= 0xb0; offset += 4) none = stats->RtWord(offset) == 0;
        if (none) {
            QueueUpgradeAvailableInfo();  // 0x004ffaf0
        }
    }
    UpdateDragonUpgradeText(dragon, 1);
}

namespace {
// One text of the accessor +0xf04 for the "upgrade available" pages: its text block's entry `index`, else its own text.
IKSerializable* UpgradeInfoText(IKSerializable* object, uint32_t index) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(object);
    if (accessor->m_texts.m_pBlock == nullptr) return accessor->m_pText;
    return accessor->m_texts.m_pBlock[index];
}
// The info menu's page list grows by 3 (as the game manager's message 0x26ca does).
void PushInfoPage(CKS08MenuPauseInfo* info, IKSerializable* text) {
    TVector<IKSerializable*, 3>& pages = info->m_aPageTextIds;
    if (pages.m_ui32NbUsedElt == pages.m_ui32NbElt) {
        uint32_t capacity = pages.m_ui32NbElt + 3;
        if (capacity == 0) capacity = 3;
        pages.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(pages.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        pages.m_ui32NbElt = capacity;
    }
    pages.m_pBlock[pages.m_ui32NbUsedElt++] = text;
}
}  // namespace

// 0x004ffaf0 CKS08GameManager_QueueUpgradeAvailableInfo_maybe: with the info pages enabled, the info menu (vt+0x344's
// [0x10]) gets the "upgrade available" title (the accessor +0xf04's text 10) and two pages (11, 12; the accessor's own
// text for all three without a text block), the slow motion (+0xe8) and the pages pending (+0xafc bit 7).
void CKS08GameManager::QueueUpgradeAvailableInfo() {
    if (static_cast<CKS08GameStructure*>(m_gameStructure)->AreInfoPopupsEnabled() == 0) return;
    IKSerializable* accessor = m_unkF00[1];  // +0xf04
    static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10])->SetTitleText(UpgradeInfoText(accessor, 10));  // vt+0x344
    PushInfoPage(static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10]), UpgradeInfoText(accessor, 11));
    PushInfoPage(static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10]), UpgradeInfoText(accessor, 12));
    static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10])->m_bTimeScaling = 1;
    m_unkAFC = (m_unkAFC & ~0x80u) | 0x80u;
}

namespace {
// The combo counters as text variables 0x30 / 0x31 (vt+0x354 entries +0xc0 / +0xc4).
void SetComboTextVariables(CKS08GameManager* manager) {
    CLocManager* loc = g_pEngine->m_locManager;
    loc->SetTextVariableValue(manager->GetCounterTextVarTable()[0x30], static_cast<int32_t>(manager->m_unkC34));
    loc = g_pEngine->m_locManager;
    loc->SetTextVariableValue(manager->GetCounterTextVarTable()[0x31], static_cast<int32_t>(manager->m_unkC38));
}
}  // namespace

// 0x00503df0 OnComboHit_comboStart (vt+0x360)
void CKS08GameManager::OnComboHitComboStart(uint8_t dragon, float value) {
    SetComboTextVariables(this);
    if (dragon == 0) {
        if (GetHudInterfaces()[0] != nullptr) static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])->OnComboHit(value);
    } else if (dragon == 1) {
        if (GetHudInterfaces()[2] != nullptr) static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])->OnComboHit(value);
    }
}

// 0x00503ba0 OnNewHit_continuecombo (vt+0x368)
void CKS08GameManager::OnNewHitContinueCombo(uint8_t dragon, float value) {
    SetComboTextVariables(this);
    if (dragon == 0) {
        if (GetHudInterfaces()[0] != nullptr) static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])->OnNewComboHit(value);
    } else if (dragon == 1) {
        if (GetHudInterfaces()[2] != nullptr) static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])->OnNewComboHit(value);
    }
}

// 0x004fffe0 CKS08GameManager_EndComboDisplay_maybe (vt+0x364)
void CKS08GameManager::EndComboDisplay(int32_t dragon) {
    if (dragon == 0) {
        if (GetHudInterfaces()[0] != nullptr) static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])->EndComboDisplay();
    } else if (dragon == 1) {
        if (GetHudInterfaces()[2] != nullptr) static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])->EndComboDisplay();
    }
}

// 0x00501700 CKS08GameManager_CloseDragonHudTimedPanel_maybe
void CKS08GameManager::CloseDragonHudTimedPanel(int32_t dragon) {
    if (dragon == 0) {
        if (GetHudInterfaces()[0] == nullptr) return;  // vt+0x34c
        static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])->CloseTimedPanel();  // 0x0053a738
    } else if (dragon == 1) {
        if (GetHudInterfaces()[2] == nullptr) return;
        static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])->CloseTimedPanel();  // 0x00540100
    }
}

// 0x004feba0 CKS08GameManager_RegisterSecondBossGaugeZone_maybe
void CKS08GameManager::RegisterSecondBossGaugeZone(IKSerializable* zone) {
    TVector<IKSerializable*, 5>& zones = m_unkBC8;
    for (uint32_t i = 0; i < zones.m_ui32NbUsedElt; ++i) {
        if (zones.m_pBlock[i] == zone) return;
    }
    if (zones.m_ui32NbElt == zones.m_ui32NbUsedElt) {
        uint32_t capacity = zones.m_ui32NbElt + 5;
        if (capacity == 0) capacity = 5;
        zones.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(zones.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        zones.m_ui32NbElt = capacity;
    }
    zones.m_pBlock[zones.m_ui32NbUsedElt] = zone;
    ++zones.m_ui32NbUsedElt;
}

// 0x004fe920 CKS08GameManager_SetFightZoneGaugeValue_maybe (fight-zones package: CKS08FightZoneCpnt mode 5)
void CKS08GameManager::SetFightZoneGaugeValue(float value) {
    if (GetHudInterfaces()[4] == nullptr) return;  // vt+0x34c
    static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[4])->m_fUnkf4 = value;
}

// 0x004fe880 CKS08GameManager_SetFightZoneGaugeMax_maybe
void CKS08GameManager::SetFightZoneGaugeMax(float value) {
    if (GetHudInterfaces()[4] == nullptr) return;
    static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[4])->m_fUnkf8 = value;
}

// 0x004fe7e0 CKS08GameManager_SetFightZoneGaugeMax2_maybe
void CKS08GameManager::SetFightZoneGaugeMax2(float value) {
    if (GetHudInterfaces()[4] == nullptr) return;
    static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[4])->m_fUnkfc = value;
}

// 0x00501c90 CKS08GameManager_SendFightZoneHudMessageAndClearTimer_maybe
void CKS08GameManager::SendFightZoneHudMessageAndClearTimer() {
    if (GetHudInterfaces()[4] == nullptr) return;  // vt+0x34c
    CKS08InGameInterfaceBoss* hud = static_cast<CKS08InGameInterfaceBoss*>(GetHudInterfaces()[4]);
    if (hud->VfC0()[1] != nullptr) static_cast<CKFlashMessageOut*>(hud->VfC0()[1])->PostFlashMessage();  // vt+0xc0, 0x75610
    hud->m_baFlagsE0 = static_cast<uint8_t>((hud->m_baFlagsE0 & 0xfe) | 1);
    hud->m_fTime = 0.0f;
}

// 0x004feef0 CKS08GameManager_HideFuryGaugeIfShown_maybe: the centre HUD (vt+0x34c [1]) hides its fury gauge when it shows
// it (+0x201; CKS08InGameInterfaceCenter_HideFuryGauge_maybe 0x535238). No caller in the original besides its OPD.
void CKS08GameManager::HideFuryGaugeIfShown() {
    if (GetHudInterfaces()[1] == nullptr) return;
    CKS08InGameInterfaceCenter* center = static_cast<CKS08InGameInterfaceCenter*>(GetHudInterfaces()[1]);
    if (center->m_ui8FuryShown201 == 0) return;
    static_cast<CKS08InGameInterfaceCenter*>(GetHudInterfaces()[1])->HideFuryGauge();
}

// 0x00503900 CKS08GameManager_RefreshComboCountText_maybe: the loc text variables of the counter table (vt+0x354) entries
// +0xc0 / +0xc4 (words 0x30 / 0x31) take Spyro's and Cynder's combo hits (+0xc34 / +0xc38). No caller in the original
// besides its OPD.
void CKS08GameManager::RefreshComboCountText() {
    const int32_t spyro = static_cast<int32_t>(m_unkC34);
    g_pEngine->m_locManager->SetTextVariableValue(GetCounterTextVarTable()[0x30], spyro);
    const int32_t cynder = static_cast<int32_t>(m_unkC38);
    g_pEngine->m_locManager->SetTextVariableValue(GetCounterTextVarTable()[0x31], cynder);
}

// 0x00500b78 CKS08GameManager_UpdateCenterTwinGauges_maybe: the game structure's two charges (+0x74, +0x78) over their
// maximum (+0x7c) (fdivs of the words as floats); with one of them above 0 (fcmpu ble / bgt: a NaN first one goes on to
// the second) the centre twin gauges show them (a tail call of 0x4fed80), else the centre HUD hides its fury gauge when it
// shows it. No caller in the original besides its OPD.
void CKS08GameManager::UpdateCenterTwinGauges() {
    const CKS08GameStructure* structure = static_cast<const CKS08GameStructure*>(m_gameStructure);
    const float maximum = static_cast<float>(static_cast<double>(structure->m_unk7c));
    const float first = static_cast<float>(static_cast<double>(structure->m_unk74)) / maximum;
    const float second = static_cast<float>(static_cast<double>(structure->m_unk78)) / maximum;
    if (first > 0.0f || second > 0.0f) {
        SetCenterTwinGauges(first, second);
        return;
    }
    HideFuryGaugeIfShown();  // the same three reads of vt+0x34c [1] as 0x4feef0
}
