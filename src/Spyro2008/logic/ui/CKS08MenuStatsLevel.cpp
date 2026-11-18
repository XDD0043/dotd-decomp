// CKS08MenuStatsLevel.cpp - reconstructed original translation unit 0x568f08-0x56aee8 (GAME_TOC2, main_toc2), 22 functions, 19 live.
// Primary class: CKS08MenuStatsLevel  key 0xa9cc  category Logic  size ?  vtable 0xb2d6d8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x568f08  CKS08MenuStatsLevel_Delete
//   [ ] 0x568f58  CKS08MenuStatsLevel_SetTitleTextByIndex_maybe  [dead]
//   [x] 0x568fd8  CKS08MenuStatsLevel_PollBackButton_maybe
//   [x] 0x569138  CKS08MenuStatsLevel_HandleInput_maybe
//   [x] 0x5693c0  CKS08MenuStatsLevel_RecursiveRegistration  (RecursiveRegistration, vt+0x24)
//   [x] 0x569430  CKS08MenuStatsLevel_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x569458  CKS08MenuStatsLevel_DeleteArray
//   [ ] 0x5694f8  RegisterCKS08MenuStatsLevelClass
//   [ ] 0x569580  _GLOBAL__D_569580
//   [ ] 0x569590  _GLOBAL__I_569590
//   [x] 0x5695a0  CKS08MenuStatsLevel_OnItemEvent
//   [ ] 0x5695e8  CKS08MenuStatsLevel_Construct  [dead]
//   [ ] 0x569690  CKS08MenuStatsLevel_Construct_2  [dead]
//   [x] 0x569738  CKS08MenuStatsLevel_CreateArray
//   [x] 0x569878  CKS08MenuStatsLevel_Create
//   [x] 0x569960  CKS08MenuStatsLevel_Load
//   [ ] 0x569aa0  CKS08MenuStatsLevel_Save
//   [x] 0x569be8  CKS08MenuStatsLevel_DeletingDestructor  (the deleting form of 0x569d20 CKS08MenuStatsLevel_Destructor)
//   [x] 0x569d20  CKS08MenuStatsLevel_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x569e58  CKS08MenuStatsLevel_Destructor_2  (the same as 0x569d20 CKS08MenuStatsLevel_Destructor)
//   [x] 0x569f90  CKS08MenuStatsLevel_RefreshStatTexts_maybe
//   [x] 0x56ab38  CKS08MenuStatsLevel_OnMenuState_maybe
//
//   [x] 0x9ca5e8  CKS08MenuStatsLevel_IsKindOfClass  [inline]
//   [x] 0x9ca628  CKS08MenuStatsLevel_GetClassType  [inline]
//   [x] 0x9ca630  CKS08MenuStatsLevel_GetClassID  [inline]
//   [x] 0x9ca638  CKS08MenuStatsLevel_vfB8  [inline]
//   [x] 0x9ca640  CKS08MenuStatsLevel_vfE0  [inline]
//   [x] 0x9ca648  CKS08MenuStatsLevel_vfC4  [inline]
//   [x] 0x9ca650  CKS08MenuStatsLevel_vfC8  [inline]
//   [x] 0x9ca660  CKS08MenuStatsLevel_vfCC  [inline]
//   [x] 0x9ca670  CKS08MenuStatsLevel_vfBC  [inline]
//   [x] 0x9ca678  CKS08MenuStatsLevel_vfC0  [inline]
//   [x] 0x9ca688  CKS08MenuStatsLevel_GetWidgetSlotCount  [inline]
//   [x] 0x9ca690  CKS08MenuStatsLevel_GetWidgetSlots  [inline]
//   [x] 0x9ca6a0  CKS08MenuStatsLevel_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsLevel.h"

#include "k2000/io/IKFile.h"

// 0x00569960 CKS08MenuStatsLevel_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuStatsLevel::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadRaw(file, &m_unk120, 4);
    ReadRaw(file, &m_unk124, 4);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}

// ==== C2.8 menus-load: the level's statistics screen (interface menu 0x15) ==========================================
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/ui/CKS08MenuObjectives.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

namespace {
CKS08GameManager* Gm(const CKS08MenuStatsLevel* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
// The "Flash Manager" input project's second configuration (null: the original reads through address 0x10).
CKInputDico* FlashManagerDico() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;  // 0x00106978
    if (project == 0xff) return nullptr;
    return &input->m_aaInputDico[project][1];
}
// 0x004f6de0 CKS08GameManager_GetCurrentMainLevelIndex_maybe (CKS08GameManager_3.cpp; a local copy): the current level's
// main level index (the original reads a null current level through address 0x1c).
uint32_t CurrentMainLevelIndex(CKS08GameManager* manager) {
    return static_cast<uint32_t>(
        Level_GetMainLevelIndex(static_cast<IKGameStructure*>(manager->m_gameStructure)->GetCurrentLevel()));  // 0x00040be8
}
// The text of a CKLocTextAccessor: its table's entry `index`, or its default (+0x10) without a table.
IKSerializable* AccessorText(IKSerializable* object, uint32_t index) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(object);
    return accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[index] : accessor->m_pText;
}
// The first text of a button state's accessor replaced (its table's first entry, or its default).
void SetStateAccessorText(IKSerializable* object, IKSerializable* text) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(object);
    if (accessor->m_texts.m_pBlock == nullptr) accessor->m_pText = text;
    else accessor->m_texts.m_pBlock[0] = text;
}
}  // namespace

// 0x005695a0 CKS08MenuStatsLevel_OnItemEvent (vt+0xe8): item 0 validated: back in game (game state 7).
void CKS08MenuStatsLevel::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (item == 0 && state == 4 && arg == 1) Gm(this)->RequestState(7);  // 0x004ec420
}

// 0x00568fd8 CKS08MenuStatsLevel_PollBackButton_maybe: an active player's action 4 (player 2: + 0x14) validates item 0
// with its delay.
void CKS08MenuStatsLevel::PollBackButton() {
    CKInputDico* dico = FlashManagerDico();
    CKS08GameManager* gm = Gm(this);
    for (uint8_t player = 0; player < gm->GetPlayerCount(); ++player) {  // vt+0x154
        if (gm->IsPlayerActive(player) == 0) continue;                    // vt+0x180
        if (dico->GetButtonState(static_cast<uint8_t>(player * 0x14 + 4)) == 0xff) SetItemState(0, 1, 1);  // 0x00512040
    }
}

// 0x00569138 CKS08MenuStatsLevel_HandleInput_maybe: for each active player, action 10 (player 2: + 0x14) goes to menu 0x18,
// action 11 to menu 0x13 (each with the objectives menu's confirm sound: menu table entry 10), action 5 validates item 0.
void CKS08MenuStatsLevel::HandleInput() {
    CKInputDico* dico = FlashManagerDico();
    CKS08GameManager* gm = Gm(this);
    if (gm->GetPlayerCount() == 0) return;
    for (uint8_t player = 0; player < gm->GetPlayerCount(); ++player) {
        if (gm->IsPlayerActive(player) == 0) continue;
        const uint8_t base = static_cast<uint8_t>(player * 0x14);
        if (dico->GetButtonState(static_cast<uint8_t>((base + 10) & 0xfe)) == 0xff) {  // rlwinm 0,24,30
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));  // vt+0x344, 0x005587c0
            StartTransitionToMenu(0x18);  // 0x005148c0
        } else if (dico->GetButtonState(static_cast<uint8_t>(base + 11)) == 0xff) {
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));
            StartTransitionToMenu(0x13);
        } else if (dico->GetButtonState(static_cast<uint8_t>(base + 5)) == 0xff) {
            SetItemState(0, 1, 1);
        }
    }
}

// 0x00569f90 CKS08MenuStatsLevel_RefreshStatTexts_maybe: the level's collectibles of the categories 1, 2, 3, 0 and 4 (the
// collected / total counter variables 14.. of the game manager's table, set only when changed); a complete category's
// count in the menu's colour (+0x124), else white. As in CKS08MenuStatsGame's counters, the label's (slots 1..5) vt+0x28
// with the colour is CText2d_GetClassType_Thunk on a CText2d (no effect); the count (slots 6..10) gets SetColor and +0x6fc.
void CKS08MenuStatsLevel::RefreshStatTexts(uint8_t mainLevel) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    CLocManager* loc = g_pEngine->m_locManager;
    auto setVariable = [&](uint32_t slot, int32_t value) {
        if (value != loc->GetTextVariableValue(manager->GetCounterTextVarTable()[slot])) {  // 0x000376f8
            loc->SetTextVariableValue(manager->GetCounterTextVarTable()[slot], value);       // 0x00037730
        }
    };
    static const uint8_t kCategories[5] = {1, 2, 3, 0, 4};
    for (uint32_t i = 0; i < 5; ++i) {
        const uint8_t category = kCategories[i];
        const int32_t collected = static_cast<int32_t>(structure->CountLevelItemsByCategory(category, mainLevel, 1));  // 0x0050f638
        setVariable(14 + i * 2, collected);
        const int32_t total = static_cast<int32_t>(structure->CountLevelItemsByCategory(category, mainLevel, 0));
        setVariable(15 + i * 2, total);
        uint32_t count = 0xffffffffu;
        if (collected == total) count = m_unk124;
        if (IKSerializable* element = m_aWidgetSlots[6 + i].m_pElement) {
            IKText2d* text = static_cast<IKText2d*>(static_cast<CText2d*>(element));
            text->SetColor(reinterpret_cast<const uint8_t*>(&count));  // vt+0x44 0x0006a1f0
            text->m_VarColor = count;                                  // +0x6fc
        }
    }
}

// 0x0056ab38 CKS08MenuStatsLevel_OnMenuState_maybe (vt+0xdc). Enter (1): player 0 active, player 1 with two players; the
// title (slot 0: the game manager's +0xf00 texts at the main level), the counters; in chapter mode (+0xafc bit 9) the
// game manager's vt+0x214 text in slots 11 and 12, the first button's states 0, 2 and 4 take the menu's first text
// (+0x128), the button focused then normal. Update (0): the inputs, or in chapter mode the back button only.
uint8_t CKS08MenuStatsLevel::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* gm = Gm(this);
    if (phase == 0) {
        if ((gm->m_unkAFC & 0x200u) == 0) HandleInput();
        else PollBackButton();
    } else if (phase == 1) {
        gm->SetPlayerActive(0, 1);  // vt+0x184
        gm->SetPlayerActive(1, gm->GetPlayerCount() == 2 ? 1 : 0);
        const uint32_t level = CurrentMainLevelIndex(gm);
        if (level < 0xc) {
            static_cast<CText2d*>(m_aWidgetSlots[0].m_pElement)->SetTextById(AccessorText(gm->m_unkF00[0], level));  // vt+0x88
        }
        RefreshStatTexts(static_cast<uint8_t>(level));
        if ((gm->m_unkAFC & 0x200u) != 0) {
            if (CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[11].m_pElement)) text->SetTextById(gm->Vf214());
            if (CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[12].m_pElement)) text->SetTextById(gm->Vf214());
            CKInterfaceButton* button = nullptr;
            if (m_apButtons.m_ui32NbUsedElt != 0 && m_apButtons.m_pBlock[0] != nullptr) {
                button = static_cast<CKInterfaceButton*>(m_apButtons.m_pBlock[0]);
                SetStateAccessorText(button->m_aStates[0].m_pTextAccessor, AccessorText(m_pText, 0));
                SetStateAccessorText(button->m_aStates[2].m_pTextAccessor, AccessorText(m_pText, 0));
                SetStateAccessorText(button->m_aStates[4].m_pTextAccessor, AccessorText(m_pText, 0));
            }
            if (button != nullptr) {  // the original calls both on a null button when there is none
                button->SetVisualState(2);  // 0x0051c1c0
                button->SetVisualState(0);
            }
        }
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}
