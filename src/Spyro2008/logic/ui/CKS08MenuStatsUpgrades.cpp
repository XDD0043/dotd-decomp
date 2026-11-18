// CKS08MenuStatsUpgrades.cpp - reconstructed original translation unit 0x56aee8-0x56cd80 (GAME_TOC2, main_toc2), 23 functions, 21 live.
// Primary class: CKS08MenuStatsUpgrades  key 0xad0c  category Logic  size ?  vtable 0xb2d7e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x56aee8  CKS08MenuStatsUpgrades_Delete
//   [x] 0x56af38  CKS08MenuStatsUpgrades_vf8C
//   [x] 0x56af50  CKS08MenuStatsUpgrades_vf90
//   [x] 0x56af68  CKS08MenuStatsUpgrades_RefreshUpgradeRowGroup_maybe  (RefreshUpgradeRowGroup)
//   [x] 0x56b328  CKS08MenuStatsUpgrades_HandlePageInput_maybe  (HandlePageInput)
//   [x] 0x56b570  CKS08MenuStatsUpgrades_OnItemEvent  (OnItemState, vt+0xe8)
//   [x] 0x56b5b8  CKS08MenuStatsUpgrades_RecursiveRegistration  (RecursiveRegistration, vt+0x24)
//   [x] 0x56b628  CKS08MenuStatsUpgrades_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x56b650  CKS08MenuStatsUpgrades_DeleteArray
//   [ ] 0x56b6f0  RegisterCKS08MenuStatsUpgradesClass
//   [ ] 0x56b778  _GLOBAL__D_56b778
//   [ ] 0x56b788  _GLOBAL__I_56b788
//   [ ] 0x56b798  CKS08MenuStatsUpgrades_Construct  [dead]
//   [ ] 0x56b840  CKS08MenuStatsUpgrades_Save
//   [ ] 0x56b988  CKS08MenuStatsUpgrades_Construct_2  [dead]
//   [x] 0x56ba30  CKS08MenuStatsUpgrades_Load
//   [x] 0x56bc60  CKS08MenuStatsUpgrades_Create
//   [x] 0x56bd48  CKS08MenuStatsUpgrades_CreateArray
//   [x] 0x56be88  CKS08MenuStatsUpgrades_Destructor_2  (the same as 0x56c0f8 CKS08MenuStatsUpgrades_Destructor)
//   [x] 0x56bfc0  CKS08MenuStatsUpgrades_DeletingDestructor  (the deleting form of 0x56c0f8 CKS08MenuStatsUpgrades_Destructor)
//   [x] 0x56c0f8  CKS08MenuStatsUpgrades_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x56c230  CKS08MenuStatsUpgrades_RefreshUpgradeTexts_maybe  (RefreshUpgradeTexts (the counters 0x5112e0 / 0x511458 / 0x511850 / 0x511980 as local copies))
//   [x] 0x56cb20  CKS08MenuStatsUpgrades_OnMenuState_maybe  (OnMenuState, vt+0xdc)
//
//   [x] 0x9ca6a8  CKS08MenuStatsUpgrades_IsKindOfClass  [inline]
//   [x] 0x9ca6e8  CKS08MenuStatsUpgrades_GetClassType  [inline]
//   [x] 0x9ca6f0  CKS08MenuStatsUpgrades_GetClassID  [inline]
//   [x] 0x9ca6f8  CKS08MenuStatsUpgrades_vfB8  [inline]
//   [x] 0x9ca700  CKS08MenuStatsUpgrades_vfE0  [inline]
//   [x] 0x9ca708  CKS08MenuStatsUpgrades_vfC4  [inline]
//   [x] 0x9ca710  CKS08MenuStatsUpgrades_vfC8  [inline]
//   [x] 0x9ca720  CKS08MenuStatsUpgrades_vfCC  [inline]
//   [x] 0x9ca730  CKS08MenuStatsUpgrades_vfBC  [inline]
//   [x] 0x9ca738  CKS08MenuStatsUpgrades_vfC0  [inline]
//   [x] 0x9ca748  CKS08MenuStatsUpgrades_GetWidgetSlotCount  [inline]
//   [x] 0x9ca750  CKS08MenuStatsUpgrades_GetWidgetSlots  [inline]
//   [x] 0x9ca760  CKS08MenuStatsUpgrades_vfF0  [inline]
//   [x] 0x9ca768  CKS08MenuStatsUpgrades_vfF4  [inline]
//   [x] 0x9ca770  CKS08MenuStatsUpgrades_vfE4  [inline]
//   [x] 0x9ca778  CKS08MenuStatsUpgrades_vf84  [inline]
//   [x] 0x9ca780  CKS08MenuStatsUpgrades_vf88  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsUpgrades.h"

#include <cstring>

#include "k2000/io/IKFile.h"

// 0x0056ba30 CKS08MenuStatsUpgrades_Load: no type test of its own.
int32_t CKS08MenuStatsUpgrades::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    // Clear the group's dynamic references [m_unk04, m_unk08) and its first m_unk08 states (signed test).
    RefGroup* group = Vf88();
    GroupState* states = Vf90(0);
    const int32_t dynamic = static_cast<int32_t>(group->m_unk08 - group->m_unk04);
    if (dynamic > 0) {
        std::memset(Vf8C(0) + group->m_unk04, 0, static_cast<uint32_t>(dynamic) * sizeof(IKSerializable*));
    }
    if (states != nullptr) std::memset(states, 0, group->m_unk08 * sizeof(GroupState));
    Vf88()->m_unk0c = 0;
    ReadRaw(file, &m_unk178, 4);
    ReadRaw(file, &m_unk17c, 4);
    IKFile_ReadRef(file, &m_pUnk268);
    return 1;
}

// ==== P14: the inputs, the upgrade rows and the menu state =========================================================
#include <cstring>

#include "Spyro2008/logic/CKS08GameLevel.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/ui/CKS08MenuObjectives.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

namespace {
CKS08GameManager* Gm(const CKS08MenuStatsUpgrades* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
// The "Flash Manager" input project's second configuration (null: the original reads through address 0x10).
CKInputDico* FlashManagerDico() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;  // 0x00106978
    if (project == 0xff) return nullptr;
    return &input->m_aaInputDico[project][1];
}
// Local copies of four counters of CKS08GameStructure.cpp's unit (P12's rows; replace with theirs after the merge). The
// health (category 1, caches +0xcc / +0xd4) or mana (category 2, +0xdc / +0xe4) items of every stage, last first (only
// the flagged ones with `flagged`), cached in the structure's run-time bytes (flag, then the count 4 bytes on).
uint32_t UpgradeItems(CKS08GameStructure* s, uint8_t flagged, uint8_t category, uint32_t base) {
    const uint32_t flagOffset = flagged != 0 ? base + 8 : base;
    if (s->RtByte(flagOffset) != 0) return s->RtWord(flagOffset + 4);
    uint32_t total = 0;
    for (uint32_t i = s->m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        total += CountStatEntriesByCategory(static_cast<CKS08GameLevel*>(s->m_vpStages.m_pBlock[i - 1]), category, flagged);  // 0x507178
    }
    s->SetRtWord(flagOffset + 4, total);
    s->RtByte(flagOffset) = 1;
    return total;
}
// 0x00511458 CountHealthUpgradesEarned_maybe: the items divided (divwu) by the dragon's divisor (+0x45 / +0x46).
uint32_t HealthUpgradesEarned(CKS08GameStructure* s, int32_t dragon, uint8_t flagged) {
    return ppc::divwu(UpgradeItems(s, flagged, 1, 0xcc), dragon != 0 ? s->HealthDivisor1() : s->HealthDivisor0());
}
// 0x005112e0 CountManaUpgradesEarned_maybe: the same for mana (+0x5c / +0x5d).
uint32_t ManaUpgradesEarned(CKS08GameStructure* s, int32_t dragon, uint8_t flagged) {
    return ppc::divwu(UpgradeItems(s, flagged, 2, 0xdc), dragon != 0 ? s->m_bManaDivisor1 : s->m_bManaDivisor0);
}
// 0x00511980 GetHealthItemsTowardNextUpgrade_maybe: the flagged health items modulo the divisor (u - (u / d) * d, divwu).
uint32_t HealthItemsTowardNextUpgrade(CKS08GameStructure* s, int32_t dragon) {
    const uint32_t total = UpgradeItems(s, 1, 1, 0xcc);
    const uint32_t divisor = dragon == 0 ? s->HealthDivisor0() : s->HealthDivisor1();
    return total - ppc::divwu(total, divisor) * divisor;
}
// 0x00511850 GetManaItemsTowardNextUpgrade_maybe: the same for mana.
uint32_t ManaItemsTowardNextUpgrade(CKS08GameStructure* s, int32_t dragon) {
    const uint32_t total = UpgradeItems(s, 1, 2, 0xdc);
    const uint32_t divisor = dragon == 0 ? s->m_bManaDivisor0 : s->m_bManaDivisor1;
    return total - ppc::divwu(total, divisor) * divisor;
}
}  // namespace

// 0x0056b570 CKS08MenuStatsUpgrades_OnItemEvent (vt+0xe8): item 0 validated: back in game (game state 7).
void CKS08MenuStatsUpgrades::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (item == 0 && state == 4 && arg == 1) Gm(this)->RequestState(7);  // 0x004ec420
}

// 0x0056b328 CKS08MenuStatsUpgrades_HandlePageInput_maybe
void CKS08MenuStatsUpgrades::HandlePageInput() {
    CKInputDico* dico = FlashManagerDico();
    CKS08GameManager* gm = Gm(this);
    if (gm->GetPlayerCount() == 0) return;  // vt+0x154
    for (uint8_t player = 0; player < gm->GetPlayerCount(); ++player) {
        if (gm->IsPlayerActive(player) == 0) continue;  // vt+0x180
        const uint8_t base = static_cast<uint8_t>(player * 0x14);
        if (dico->GetButtonState(static_cast<uint8_t>((base + 10) & 0xfe)) == 0xff) {  // rlwinm 0,24,30
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));  // vt+0x344, 0x005587c0
            StartTransitionToMenu(10);  // 0x005148c0
        } else if (dico->GetButtonState(static_cast<uint8_t>(base + 11)) == 0xff) {
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));
            StartTransitionToMenu(0x15);
        }
    }
}

// 0x0056af68 CKS08MenuStatsUpgrades_RefreshUpgradeRowGroup_maybe
void CKS08MenuStatsUpgrades::RefreshUpgradeRowGroup(uint32_t first, uint32_t lit, uint32_t count) {
    uint32_t message = 0;  // BUG(original): r20 is only set for the rows 0, 4, 9 and 14 (the only ones passed)
    for (uint32_t i = 0; i < count; i = (i + 1) & 0xff) {
        const uint32_t slot = first + i;
        IKSerializable* element = m_aWidgetSlots[slot].m_pElement;
        if (element == nullptr) continue;
        // The text part's vt+0x28 with a colour (white below `lit`, else +0x178): on a CText2d that slot is
        // CText2d_GetClassType_Thunk (0x9981c0), which ignores it (as in CKS08MenuStatsGame's counters).
        if (lit <= i) continue;
        switch (first) {
            case 0: message = 1; break;
            case 4: message = 2; break;
            case 9: message = 3; break;
            case 0xe: message = 4; break;
            default: break;
        }
        const float x = GetElementX(slot);  // vt+0x70
        const float y = GetElementY(slot);  // vt+0x74
        IKSerializable* out = VfC0()[message & 0xff];
        RefGroup* groups = Vf88();
        IKSerializable** references = Vf8C(0);
        GroupState* states = Vf90(0);
        if (out == nullptr) continue;
        for (uint32_t j = groups->m_unk04; j < groups->m_unk08; ++j) {
            if (references[j] != out && references[j] != nullptr) continue;
            references[j] = out;
            if (states != nullptr) {
                std::memcpy(&states[j].m_unk04, &y, 4);  // stfs f31, +4 first
                std::memcpy(&states[j].m_unk00, &x, 4);
            }
            break;
        }
    }
}

// 0x0056c230 CKS08MenuStatsUpgrades_RefreshUpgradeTexts_maybe
void CKS08MenuStatsUpgrades::RefreshUpgradeTexts() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    RefreshUpgradeRowGroup(0, HealthItemsTowardNextUpgrade(structure, 0), structure->HealthDivisor0());
    RefreshUpgradeRowGroup(4, ManaItemsTowardNextUpgrade(structure, 0), structure->m_bManaDivisor0);
    RefreshUpgradeRowGroup(9, HealthItemsTowardNextUpgrade(structure, 1), structure->HealthDivisor1());
    RefreshUpgradeRowGroup(0xe, ManaItemsTowardNextUpgrade(structure, 1), structure->m_bManaDivisor1);
    auto setVariable = [&](uint32_t slot, int32_t value) {
        if (value != g_pEngine->m_locManager->GetTextVariableValue(manager->GetCounterTextVarTable()[slot])) {  // 0x000376f8
            g_pEngine->m_locManager->SetTextVariableValue(manager->GetCounterTextVarTable()[slot], value);       // 0x00037730
        }
    };
    // Per dragon and kind: the upgrades earned (flagged items) and possible (all items) into the variables 40..47; the
    // count (slots 18..21) in +0x17c when every possible upgrade is earned, else white.
    for (uint32_t row = 0; row < 4; ++row) {
        const int32_t dragon = static_cast<int32_t>(row >> 1);
        const bool mana = (row & 1) != 0;
        auto earned = [&](uint8_t flagged) {
            return mana ? ManaUpgradesEarned(structure, dragon, flagged) : HealthUpgradesEarned(structure, dragon, flagged);
        };
        setVariable(40 + row * 2, static_cast<int32_t>(earned(1)));
        setVariable(41 + row * 2, static_cast<int32_t>(earned(0)));
        const uint32_t done = earned(1);
        const uint32_t colour = done == earned(0) ? m_unk17c : 0xffffffffu;
        if (IKSerializable* element = m_aWidgetSlots[18 + row].m_pElement) {
            IKText2d* text = static_cast<IKText2d*>(static_cast<CText2d*>(element));
            text->SetColor(reinterpret_cast<const uint8_t*>(&colour));  // vt+0x44 0x0006a1f0
            text->m_VarColor = colour;                                   // +0x6fc
        }
    }
}

// 0x0056cb20 CKS08MenuStatsUpgrades_OnMenuState_maybe (vt+0xdc). Enter (1) and leave (2): the group's dynamic references
// [m_unk04, m_unk08) and its first m_unk08 states cleared (enter then refreshes the rows and the counters); update (0):
// the page inputs.
uint8_t CKS08MenuStatsUpgrades::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 1 || phase == 2) {
        RefGroup* groups = Vf88();
        GroupState* states = Vf90(0);
        const int32_t refs = static_cast<int32_t>(groups->m_unk08 - groups->m_unk04);
        if (0 < refs) {
            std::memset(&Vf8C(0)[groups->m_unk04], 0, static_cast<size_t>(refs) * sizeof(IKSerializable*));  // block-shrink: sizeof(pointer)
        }
        if (states != nullptr) std::memset(states, 0, groups->m_unk08 * sizeof(GroupState));
        if (phase == 1) RefreshUpgradeTexts();
    } else if (phase == 0) {
        HandlePageInput();
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}
