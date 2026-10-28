// CKS08GameManager_5.cpp - reconstructed original translation unit 0x4fe5a8-0x504358 (GAME_TOC1, main_toc1), 64 functions, 62 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: ResetDragonStatHud (2), OnNewHitW (1), RefreshFuryGaugeHud (1), NotifySpyroMovementModeChanged (1), UpdateDragonUpgradeText (1), NotifyCynderMovementModeChanged (1), UpdateDragonManaCapacityMarker (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4fe5a8  StaticInitAndDestruction_4fe5a8
//   [ ] 0x4fe5d8  _GLOBAL__D_4fe5d8
//   [ ] 0x4fe5e8  _GLOBAL__I_4fe5e8
//   [ ] 0x4fe5f8  OnNewHitW_2
//   [x] 0x4fe638  CKS08GameManager_DestroyTextures
//   [ ] 0x4fe7e0  CKS08GameManager_SetFightZoneGaugeMax2_maybe
//   [ ] 0x4fe880  CKS08GameManager_SetFightZoneGaugeMax_maybe
//   [ ] 0x4fe920  CKS08GameManager_SetFightZoneGaugeValue_maybe
//   [ ] 0x4fe9c0  CKS08GameManager_SetEnemyGaugeMaxHealth_2_maybe
//   [ ] 0x4fea60  CKS08GameManager_SetEnemyGaugeMaxHealth_maybe
//   [ ] 0x4feb00  CKS08GameManager_SetBossGaugeHealth_maybe
//   [ ] 0x4feba0  CKS08GameManager_RegisterSecondBossGaugeZone_maybe
//   [ ] 0x4fec98  RefreshFuryGaugeHud_maybe
//   [x] 0x4fed80  CKS08GameManager_SetCenterTwinGauges_maybe
//   [ ] 0x4feef0  CKS08GameManager_HideFuryGaugeIfShown_maybe
//   [ ] 0x4fefd8  CKS08GameManager_QueueHudMessage_maybe
//   [ ] 0x4ff080  CKS08GameManager_ShowCenterHudMessagePairSecondFromTable_maybe
//   [ ] 0x4ff150  CKS08GameManager_ShowCenterHudMessage_maybe
//   [x] 0x4ff220  CKS08GameManager_SelectSpyroHudPanelElement_maybe
//   [x] 0x4ff2d8  NotifySpyroMovementModeChanged_Stub
//   [x] 0x4ff318  CKS08GameManager_UpdateBossGaugeTotals_maybe
//   [x] 0x4ff540  CKS08GameManager_UpdateSecondBossGaugeTotals_maybe
//   [x] 0x4ff768  CKS08GameManager_LoadHudResources_maybe
//   [ ] 0x4ffaf0  CKS08GameManager_QueueUpgradeAvailableInfo_maybe
//   [ ] 0x4ffdd0  CKS08GameManager_QueueFirstCollectibleInfo_maybe
//   [ ] 0x4fffe0  CKS08GameManager_EndComboDisplay_maybe
//   [x] 0x500140  UpdateDragonUpgradeText_maybe
//   [ ] 0x5003c0  CKS08GameManager_SetDragonUpgradePoints_maybe  [dead]
//   [ ] 0x500418  CKS08GameManager_AddDragonUpgradePoints_maybe
//   [x] 0x500628  CKS08GameManager_UpdateComboTimers_maybe
//   [ ] 0x500880  CKS08GameManager_CheatMaxUpgradePoints_maybe
//   [ ] 0x5008c8  CKS08GameManager_AddDragonUpgradePoints_2_maybe
//   [x] 0x5008d0  CKS08GameManager_HidePlayerHudPanel_maybe
//   [x] 0x500a88  CKS08GameManager_SelectCynderHudPanelElement_maybe
//   [x] 0x500b38  NotifyCynderMovementModeChanged_Stub
//   [ ] 0x500b78  CKS08GameManager_UpdateCenterTwinGauges_maybe
//   [x] 0x500cc8  UpdateDragonManaCapacityMarker_maybe
//   [x] 0x500ee8  UpdateDragonManaGauge
//   [x] 0x501188  UpdateDragonHealthCapacityMarker_maybe
//   [x] 0x5013a8  UpdateDragonHealthGauge
//   [x] 0x501648  UpdateDragonHealthAndManaGauges
//   [ ] 0x501700  CKS08GameManager_CloseDragonHudTimedPanel_maybe
//   [ ] 0x501860  CKS08GameManager_ShowCenterMessage_maybe
//   [ ] 0x501938  CKS08GameManager_QueueCollectibleMessage_maybe
//   [ ] 0x501a08  CKS08GameManager_ShowCollectedItemMessage_maybe
//   [x] 0x501b00  CKS08GameManager_UpdateInGameHud_maybe
//   [ ] 0x501c90  CKS08GameManager_SendFightZoneHudMessageAndClearTimer_maybe
//   [ ] 0x501da8  FUN_00501da8  [dead]
//   [ ] 0x501ea0  CKS08GameManager_RefreshBossGauge_maybe
//   [ ] 0x501fb8  ShowDragonStatChangeFeedback_maybe
//   [x] 0x5022b0  RefreshDragonStatDisplays_maybe
//   [ ] 0x502340  ResetDragonStatHud_2
//   [x] 0x502410  ResetDragonStatHud
//   [ ] 0x5024d8  ShowCynderSelectedElementHud
//   [x] 0x502688  CKS08GameManager_ShowPlayerHudPanel_maybe
//   [ ] 0x502a80  CKS08GameManager_UpdateCounterTextVariables_maybe
//   [ ] 0x502ca0  CKS08GameManager_RefreshManaShardHud_maybe
//   [ ] 0x5032d0  CKS08GameManager_RefreshHealthShardHud_maybe
//   [ ] 0x503900  CKS08GameManager_RefreshComboCountText_maybe
//   [ ] 0x5039e8  ShowSpyroSelectedElementHud
//   [ ] 0x503ba0  OnNewHit_continuecombo
//   [ ] 0x503df0  OnComboHit_comboStart
//   [x] 0x504040  CKS08GameManager_State6_maybe
//   [x] 0x504248  CKS08GameManager_State2_maybe
#include "Spyro2008/logic/CKS08GameManager.h"

#include <cstdio>
#include <cstring>

#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/IKHkHero.h"
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/CKS08InGameInterfaceCenter.h"
#include "Spyro2008/logic/CKS08InGameInterfaceLeft.h"
#include "Spyro2008/logic/CKS08InGameInterfaceRight.h"
#include "Spyro2008/logic/HudGaugeOps.h"
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
// set to +0xbfc[element] (CKS08InGameInterfaceLeft_SetPanelElementObject_maybe). STUB(C2): the in-game HUD.
void CKS08GameManager::SelectSpyroHudPanelElement(uint8_t element) {
    (void)element;
    if (GetHudInterfaces()[0] != nullptr) DOTD_STUB_ONCE("CKS08GameManager_SelectSpyroHudPanelElement_maybe (C2)");
}

// 0x00500a88 CKS08GameManager_SelectCynderHudPanelElement_maybe: the same for Cynder's panel and
// +0xc10[element] (CKS08InGameInterfaceRight_SetPanelElementObject_maybe). STUB(C2): the in-game HUD.
void CKS08GameManager::SelectCynderHudPanelElement(uint8_t element) {
    (void)element;
    if (GetHudInterfaces()[2] != nullptr) DOTD_STUB_ONCE("CKS08GameManager_SelectCynderHudPanelElement_maybe (C2)");
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
// boss's +0xbc0 / +0xbc4) and written to the boss gauge screen's +0xf4, +0xf8 and +0xfc (the maximum twice).
// STUB(C2.7, moved from C2.6: boss fights): the zones' health totals (CKHkS08CrumblyZoneMultiState_GetTotalHealth / GetTotalMaxHealth are in
// the hooks); no zone is registered at the level start, so the loop does not run.
void CKS08GameManager::UpdateBossGaugeTotals() {
    if (m_unkBB4.m_ui32NbUsedElt == 0) return;
    m_afUnkBAC[1] = 0.0f;
    m_afUnkBAC[0] = 0.0f;
    for (uint32_t i = 0; i < m_unkBB4.m_ui32NbUsedElt; ++i) {
        DOTD_STUB_ONCE("CKS08GameManager_UpdateBossGaugeTotals_maybe: the zones' health totals (C2.7, moved from C2.6)");
    }
    // The boss gauge screen (hud[3]) takes the totals: +0xf4 health, +0xf8 and +0xfc the maximum.
    DOTD_STUB_ONCE("CKS08GameManager_UpdateBossGaugeTotals_maybe: the boss gauge screen's fields (C2.7, moved from C2.6)");
}

void CKS08GameManager::UpdateSecondBossGaugeTotals() {
    if (m_unkBC8.m_ui32NbUsedElt == 0) return;
    m_afUnkBC0[1] = 0.0f;
    m_afUnkBC0[0] = 0.0f;
    for (uint32_t i = 0; i < m_unkBC8.m_ui32NbUsedElt; ++i) {
        DOTD_STUB_ONCE("CKS08GameManager_UpdateSecondBossGaugeTotals_maybe: the zones' health totals (C2.7, moved from C2.6)");
    }
    DOTD_STUB_ONCE("CKS08GameManager_UpdateSecondBossGaugeTotals_maybe: the boss gauge screen's fields (C2.7, moved from C2.6)");
}

// 0x00500628 CKS08GameManager_UpdateComboTimers_maybe: each dragon's combo (Cynder's +0xc24..+0xc38 block
// first: timer +0xc30, elapsed +0xc28; then Spyro's +0xc2c / +0xc24): while the timer runs, the elapsed time
// grows and the timer falls by (elapsed * +0xc40 + 1) * dt; at zero the best combo is recorded, the combo
// converted to upgrade points (unless +0xafc bit 5), the count reset and the combo display ended.
// STUB(C2.7, moved from C2.6: combat): the points' curve (CKCurve_Evaluate_maybe 0x249ea8, CKCurve2DCpnt), AddDragonUpgradePoints and the
// panels' EndComboDisplay run only after a combo, which needs the hero.
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
            if (VfC4() == 0) DOTD_STUB_ONCE("CKS08GameManager_UpdateComboTimers_maybe: CKCurve_Evaluate_maybe + AddDragonUpgradePoints (C2.7, moved from C2.6)");
            m_unkC38 = 0;
            DOTD_STUB_ONCE("CKS08GameManager_UpdateComboTimers_maybe: EndComboDisplay (C2.7, moved from C2.6)");
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
            if (VfC4() == 0) DOTD_STUB_ONCE("CKS08GameManager_UpdateComboTimers_maybe: CKCurve_Evaluate_maybe + AddDragonUpgradePoints (C2.7, moved from C2.6)");
            m_unkC34 = 0;
            DOTD_STUB_ONCE("CKS08GameManager_UpdateComboTimers_maybe: EndComboDisplay (C2.7, moved from C2.6)");
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
    // STUB(C2.7: HUD): ShowDragonStatChangeFeedback_maybe 0x501fb8 (the panel's upgrade text, flash message and flags).
    DOTD_STUB_ONCE("ShowDragonStatChangeFeedback_maybe 0x501fb8 (C2.7)");
}
