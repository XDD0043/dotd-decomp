// CKS08MenuStatsGame.cpp - reconstructed original translation unit 0x565218-0x567768 (GAME_TOC2, main_toc2), 21 functions, 19 live.
// Primary class: CKS08MenuStatsGame  key 0xaa0c  category Logic  size ?  vtable 0xb2d4c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x565218  CKS08MenuStatsGame_PollBackButton_maybe  (PollBackButton)
//   [x] 0x565378  CKS08MenuStatsGame_HandleInput_maybe  (HandleInput)
//   [x] 0x565600  CKS08MenuStatsGame_OnItemEvent  (OnItemState, vt+0xe8)
//   [x] 0x565648  CKS08MenuStatsGame_RecursiveRegistration  (RecursiveRegistration, vt+0x24)
//   [x] 0x5656b8  CKS08MenuStatsGame_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x5656e0  CKS08MenuStatsGame_DeleteArray
//   [ ] 0x565780  RegisterCKS08MenuStatsGameClass
//   [ ] 0x565808  _GLOBAL__D_565808
//   [ ] 0x565818  _GLOBAL__I_565818
//   [ ] 0x565828  CKS08MenuStatsGame_Construct  [dead]
//   [ ] 0x5658d0  CKS08MenuStatsGame_Save
//   [ ] 0x565a18  CKS08MenuStatsGame_Construct_2  [dead]
//   [x] 0x565ac0  CKS08MenuStatsGame_Create
//   [x] 0x565ba8  CKS08MenuStatsGame_CreateArray
//   [x] 0x565ce8  CKS08MenuStatsGame_Load
//   [x] 0x565e28  CKS08MenuStatsGame_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x565f60  CKS08MenuStatsGame_Destructor_2  (the same as 0x565e28 CKS08MenuStatsGame_Destructor)
//   [x] 0x566098  CKS08MenuStatsGame_DeletingDestructor  (the deleting form of 0x565e28 CKS08MenuStatsGame_Destructor)
//   [x] 0x5661d0  CKS08MenuStatsGame_RefreshCollectibleCounters_maybe
//   [x] 0x567048  CKS08MenuStatsGame_BuildSaveDetailText_maybe
//   [x] 0x5671e8  CKS08MenuStatsGame_OnMenuState_maybe  (OnMenuState, vt+0xdc)
//
//   [x] 0x9ca458  CKS08MenuStatsGame_IsKindOfClass  [inline]
//   [x] 0x9ca498  CKS08MenuStatsGame_GetClassType  [inline]
//   [x] 0x9ca4a0  CKS08MenuStatsGame_GetClassID  [inline]
//   [x] 0x9ca4a8  CKS08MenuStatsGame_vfB8  [inline]
//   [x] 0x9ca4b0  CKS08MenuStatsGame_vfE0  [inline]
//   [x] 0x9ca4b8  CKS08MenuStatsGame_vfC4  [inline]
//   [x] 0x9ca4c0  CKS08MenuStatsGame_vfC8  [inline]
//   [x] 0x9ca4d0  CKS08MenuStatsGame_vfCC  [inline]
//   [x] 0x9ca4e0  CKS08MenuStatsGame_vfBC  [inline]
//   [x] 0x9ca4e8  CKS08MenuStatsGame_vfC0  [inline]
//   [x] 0x9ca4f8  CKS08MenuStatsGame_GetWidgetSlotCount  [inline]
//   [x] 0x9ca500  CKS08MenuStatsGame_GetWidgetSlots  [inline]
//   [x] 0x9ca510  CKS08MenuStatsGame_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsGame.h"

#include "k2000/io/IKFile.h"

// 0x00565ce8 CKS08MenuStatsGame_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuStatsGame::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadRaw(file, &m_unk138, 4);
    ReadRaw(file, &m_unk13c, 4);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}

// ==== C2.8 save-menu: the save's detail text ======================================================================
#include "k2000/core/Stub.h"
#include "k2000/graphical/ui/CText2d.h"

namespace {
// The text part of a widget slot's element (a CText2d: its IKText2d at +0x28).
IKText2d* SlotText(IKSerializable* element) { return static_cast<IKText2d*>(static_cast<CText2d*>(element)); }
// WStr_CatReturnEnd (the library's, through TocBridge 0x98fac0): `src` appended to `dst`; the end.
uint16_t* WStrCat(uint16_t* dst, const uint16_t* src) {
    while (*dst != 0) ++dst;
    while ((*dst = *src) != 0) {
        ++dst;
        ++src;
    }
    return dst;
}
const uint16_t kColonSeparator[] = {' ', ':', ' ', ' ', 0};  // 0x00acba20 (TOC2 -0x79c8)
const uint16_t kLineSeparator[] = {'\n', 0};                 // 0x00acba30 (TOC2 -0x79c4)
}  // namespace

#include <cstring>
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "crt/ppc_ops.h"
#include "k2000/logic/IKPlayer.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/misc/Engine.h"
namespace {
// Player 0's +0x10 (a float word: the play time in seconds; lfs, fctidz, the low word).
float PlayTimeSeconds(CKS08GameManager* manager) {
    const uint32_t bits = static_cast<IKPlayer*>(manager->m_players[0])->m_unk10;
    float seconds;
    std::memcpy(&seconds, &bits, 4);
    return seconds;
}
}  // namespace

// 0x005661d0 CKS08MenuStatsGame_RefreshCollectibleCounters_maybe. The counter table is the game manager's vt+0x354
// (+0xcc0); a text variable is set only when its value changed (SetTextVariableValue posts the 2D event 5).
void CKS08MenuStatsGame::RefreshCollectibleCounters() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    CLocManager* loc = g_pEngine->m_locManager;
    auto setVariable = [&](uint32_t slot, int32_t value) {
        if (value != loc->GetTextVariableValue(manager->GetCounterTextVarTable()[slot])) {  // 0x000376f8
            loc->SetTextVariableValue(manager->GetCounterTextVarTable()[slot], value);       // 0x00037730
        }
    };
    // The categories in the menu's order: their collected / total variables (+0x38.. of the table) and the widget slots
    // of their label (0..4) and count (5..9).
    static const uint8_t kCategories[5] = {1, 2, 3, 0, 4};
    for (uint32_t i = 0; i < 5; ++i) {
        const uint8_t category = kCategories[i];
        const int32_t collected = static_cast<int32_t>(structure->CountItemsByCategory(category, 1));  // 0x0050f730
        setVariable(14 + i * 2, collected);
        const int32_t total = static_cast<int32_t>(structure->CountItemsByCategory(category, 0));
        setVariable(15 + i * 2, total);
        uint32_t label = 0xffffffffu;  // white (four 0xff bytes)
        uint32_t count = 0xffffffffu;
        if (collected == total) {
            label = m_unk138;
            count = m_unk13c;
        }
        // The label's text part vt+0x28 with the colour: on a CText2d that slot is CText2d_GetClassType_Thunk (0x9981c0),
        // which ignores it.
        (void)label;
        if (IKSerializable* element = m_aWidgetSlots[5 + i].m_pElement) {
            IKText2d* text = SlotText(element);
            text->SetColor(reinterpret_cast<const uint8_t*>(&count));  // vt+0x44 0x0006a1f0
            text->m_VarColor = count;
        }
    }
    // The play time (player 0's +0x10, seconds) as hours, minutes and seconds.
    const uint32_t seconds = static_cast<uint32_t>(ppc::fctidz(PlayTimeSeconds(manager)));
    const uint32_t hours = seconds / 3600u;
    const uint32_t rest = seconds - hours * 3600u;
    const uint32_t minutes = rest / 60u;
    setVariable(24, static_cast<int32_t>(hours));
    setVariable(25, static_cast<int32_t>(minutes));
    setVariable(26, static_cast<int32_t>(rest - minutes * 60u));
    // The completion: 100, or the tracked modules' active share in percent.
    int32_t percent = 100;
    if (structure->CountTrackedActiveModules() != structure->CountTrackedModules()) {  // 0x00040dd0, 0x00040f58
        const float active = static_cast<float>(structure->CountTrackedActiveModules());
        const float tracked = static_cast<float>(structure->CountTrackedModules());
        percent = static_cast<int32_t>(ppc::fctidz((active / tracked) * 100.0f));  // TOC2 -0x79cc: 100.0
    }
    setVariable(27, percent);
}

// 0x00567048 CKS08MenuStatsGame_BuildSaveDetailText_maybe
void CKS08MenuStatsGame::BuildSaveDetailText(uint16_t* text) {
    RefreshCollectibleCounters();
    IKSerializable* a = m_aWidgetSlots[10].m_pElement;  // +0xe8
    IKSerializable* b = m_aWidgetSlots[11].m_pElement;  // +0xf0
    IKSerializable* c = m_aWidgetSlots[12].m_pElement;  // +0xf8
    IKSerializable* d = m_aWidgetSlots[13].m_pElement;  // +0x100
    bool missing = true;
    if (b != nullptr) missing = a == nullptr;
    if (c == nullptr) missing = true;
    if (d == nullptr || missing) return;
    IKText2d* parts[4] = {SlotText(a), SlotText(b), SlotText(c), SlotText(d)};
    const uint16_t* separators[3] = {kColonSeparator, kLineSeparator, kColonSeparator};
    for (int i = 0; i < 4; ++i) {
        parts[i]->RefreshFromLocString();   // TocBridge -> 0x0006bd10
        parts[i]->AppendWordsToWStr(text);  // TocBridge -> 0x0006a238
        if (i < 3) WStrCat(text, separators[i]);
    }
}

// ==== P14: the inputs and the menu state ============================================================================
#include "Spyro2008/logic/ui/CKS08MenuObjectives.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/managers/CKInput.h"

namespace {
CKS08GameManager* Gm(const CKS08MenuStatsGame* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
// The "Flash Manager" input project's second configuration (null: the original reads through address 0x10).
CKInputDico* FlashManagerDico() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;  // 0x00106978
    if (project == 0xff) return nullptr;
    return &input->m_aaInputDico[project][1];
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

// 0x00565600 CKS08MenuStatsGame_OnItemEvent (vt+0xe8): item 0 validated: back in game (game state 7).
void CKS08MenuStatsGame::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (item == 0 && state == 4 && arg == 1) Gm(this)->RequestState(7);  // 0x004ec420
}

// 0x00565218 CKS08MenuStatsGame_PollBackButton_maybe: an active player's action 4 (player 2: + 0x14) validates item 0
// with its delay.
void CKS08MenuStatsGame::PollBackButton() {
    CKInputDico* dico = FlashManagerDico();
    CKS08GameManager* gm = Gm(this);
    for (uint8_t player = 0; player < gm->GetPlayerCount(); ++player) {  // vt+0x154
        if (gm->IsPlayerActive(player) == 0) continue;                    // vt+0x180
        if (dico->GetButtonState(static_cast<uint8_t>(player * 0x14 + 4)) == 0xff) SetItemState(0, 1, 1);  // 0x00512040
    }
}

// 0x00565378 CKS08MenuStatsGame_HandleInput_maybe: for each active player, action 10 (player 2: + 0x14) goes to menu
// 0x15, action 11 to menu 0x14 (each with the objectives menu's confirm sound: menu table entry 10), action 5 validates
// item 0.
void CKS08MenuStatsGame::HandleInput() {
    CKInputDico* dico = FlashManagerDico();
    CKS08GameManager* gm = Gm(this);
    if (gm->GetPlayerCount() == 0) return;
    for (uint8_t player = 0; player < gm->GetPlayerCount(); ++player) {
        if (gm->IsPlayerActive(player) == 0) continue;
        const uint8_t base = static_cast<uint8_t>(player * 0x14);
        if (dico->GetButtonState(static_cast<uint8_t>((base + 10) & 0xfe)) == 0xff) {  // rlwinm 0,24,30
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));  // vt+0x344, 0x005587c0
            StartTransitionToMenu(0x15);  // 0x005148c0
        } else if (dico->GetButtonState(static_cast<uint8_t>(base + 11)) == 0xff) {
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));
            StartTransitionToMenu(0x14);
        } else if (dico->GetButtonState(static_cast<uint8_t>(base + 5)) == 0xff) {
            SetItemState(0, 1, 1);
        }
    }
}

// 0x005671e8 CKS08MenuStatsGame_OnMenuState_maybe (vt+0xdc)
uint8_t CKS08MenuStatsGame::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (phase == 0) {
        if ((Gm(this)->m_unkAFC & 0x400u) == 0) HandleInput();
        else PollBackButton();
        // The play time (player 0's +0x10, seconds; fctidz, the low word) as hours, minutes and seconds.
        const uint32_t seconds = static_cast<uint32_t>(ppc::fctidz(PlayTimeSeconds(manager)));
        const uint32_t hours = seconds / 3600u;
        const uint32_t rest = seconds - hours * 3600u;
        const uint32_t minutes = rest / 60u;
        const uint32_t values[3] = {hours, minutes, rest - minutes * 60u};
        for (uint32_t i = 0; i < 3; ++i) {
            CLocManager* loc = g_pEngine->m_locManager;
            if (static_cast<int32_t>(values[i]) != loc->GetTextVariableValue(manager->GetCounterTextVarTable()[24 + i])) {
                g_pEngine->m_locManager->SetTextVariableValue(manager->GetCounterTextVarTable()[24 + i],
                                                              static_cast<int32_t>(values[i]));
            }
        }
    } else if (phase == 1) {
        for (uint32_t i = 0; i < 3; ++i) {
            g_pEngine->m_locManager->SetTextVariable(manager->GetCounterTextVarTable()[24 + i], 2);  // 0x000375b0
        }
        RefreshCollectibleCounters();
        CKS08GameManager* gm = Gm(this);
        if ((gm->m_unkAFC & 0x400u) != 0) {
            if (CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[14].m_pElement)) text->SetTextById(gm->Vf214());  // vt+0x88
            if (CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[15].m_pElement)) text->SetTextById(gm->Vf214());
            if (m_apButtons.m_ui32NbUsedElt != 0 && m_apButtons.m_pBlock[0] != nullptr) {
                CKInterfaceButton* button = static_cast<CKInterfaceButton*>(m_apButtons.m_pBlock[0]);
                SetStateAccessorText(button->m_aStates[0].m_pTextAccessor, AccessorText(m_pText, 0));
                SetStateAccessorText(button->m_aStates[2].m_pTextAccessor, AccessorText(m_pText, 0));
                SetStateAccessorText(button->m_aStates[4].m_pTextAccessor, AccessorText(m_pText, 0));
            }
        }
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}
