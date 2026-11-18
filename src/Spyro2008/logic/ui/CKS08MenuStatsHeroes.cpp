// CKS08MenuStatsHeroes.cpp - reconstructed original translation unit 0x567768-0x568f08 (GAME_TOC2, main_toc2), 21 functions, 18 live.
// Primary class: CKS08MenuStatsHeroes  key 0xa98c  category Logic  size ?  vtable 0xb2d5d0
// Other owners: Time (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x567768  CKS08MenuStatsHeroes_Delete
//   [ ] 0x5677b8  CKS08MenuStatsHeroes_Construct  [dead]
//   [ ] 0x567860  Time_SplitSecondsToHMS_2  [dead]
//   [x] 0x5678b8  CKS08MenuStatsHeroes_HandlePageInput_maybe  (HandlePageInput)
//   [x] 0x567b00  CKS08MenuStatsHeroes_OnItemEvent  (OnItemState, vt+0xe8)
//   [x] 0x567b48  CKS08MenuStatsHeroes_Load
//   [ ] 0x567b70  CKS08MenuStatsHeroes_Save
//   [x] 0x567b98  CKS08MenuStatsHeroes_RecursiveRegistration  (inherited: CKMenuBase114c's (0x513c38, KBase730C's))
//   [x] 0x567bc0  CKS08MenuStatsHeroes_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x567be8  CKS08MenuStatsHeroes_DeleteArray
//   [ ] 0x567c88  RegisterCKS08MenuStatsHeroesClass
//   [ ] 0x567d10  _GLOBAL__D_567d10
//   [ ] 0x567d20  _GLOBAL__I_567d20
//   [ ] 0x567d30  CKS08MenuStatsHeroes_Construct_2  [dead]
//   [x] 0x567dd8  CKS08MenuStatsHeroes_CreateArray
//   [x] 0x567f18  CKS08MenuStatsHeroes_Create
//   [x] 0x568000  CKS08MenuStatsHeroes_Destructor_2  (the same as 0x568270 CKS08MenuStatsHeroes_Destructor)
//   [x] 0x568138  CKS08MenuStatsHeroes_DeletingDestructor  (the deleting form of 0x568270 CKS08MenuStatsHeroes_Destructor)
//   [x] 0x568270  CKS08MenuStatsHeroes_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x5683a8  CKS08MenuStatsHeroes_RefreshStatTexts_maybe  (RefreshStatTexts (the game structure getters 0x50f0b8 / 0x50f0d0 / 0x50f0e8 / 0x50f200 as local copies))
//   [x] 0x568cc0  CKS08MenuStatsHeroes_OnMenuState_maybe  (OnMenuState, vt+0xdc)
//
//   [x] 0x9ca518  CKS08MenuStatsHeroes_IsKindOfClass  [inline]
//   [x] 0x9ca558  CKS08MenuStatsHeroes_GetClassType  [inline]
//   [x] 0x9ca560  CKS08MenuStatsHeroes_GetClassID  [inline]
//   [x] 0x9ca568  CKS08MenuStatsHeroes_vfB8  [inline]
//   [x] 0x9ca570  CKS08MenuStatsHeroes_vfE0  [inline]
//   [x] 0x9ca578  CKS08MenuStatsHeroes_vfC4  [inline]
//   [x] 0x9ca580  CKS08MenuStatsHeroes_vfC8  [inline]
//   [x] 0x9ca590  CKS08MenuStatsHeroes_vfCC  [inline]
//   [x] 0x9ca5a0  CKS08MenuStatsHeroes_vfBC  [inline]
//   [x] 0x9ca5a8  CKS08MenuStatsHeroes_vfC0  [inline]
//   [x] 0x9ca5b8  CKS08MenuStatsHeroes_GetWidgetSlotCount  [inline]
//   [x] 0x9ca5c0  CKS08MenuStatsHeroes_GetWidgetSlots  [inline]
//   [x] 0x9ca5d0  CKS08MenuStatsHeroes_vfF0  [inline]
//   [x] 0x9ca5d8  CKS08MenuStatsHeroes_vfF4  [inline]
//   [x] 0x9ca5e0  CKS08MenuStatsHeroes_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsHeroes.h"

// 0x00567b48 CKS08MenuStatsHeroes_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuStatsHeroes::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// ==== P14: the inputs, the statistics and the menu state ===========================================================
#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/ui/CKS08MenuObjectives.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

namespace {
CKS08GameManager* Gm(const CKS08MenuStatsHeroes* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
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
// Local copies of the getters of CKS08GameState.cpp's unit (not ported there; run-time words of the structure):
// 0x0050f0d0 CKS08GameStructure_GetBestCombo_maybe: the word at +0x114 + 4 * dragon.
uint32_t BestCombo(const CKS08GameStructure* s, int32_t dragon) { return s->RtWord(0x114 + 4 * static_cast<uint32_t>(dragon)); }
// 0x0050f0b8 CKS08GameStructure_GetEnemyKills_maybe: the word at +0x10c + 4 * dragon.
uint32_t EnemyKills(const CKS08GameStructure* s, int32_t dragon) { return s->RtWord(0x10c + 4 * static_cast<uint32_t>(dragon)); }
// 0x0050f0e8 CKS08GameStructure_GetMostUsedElement_maybe: of the five element counters (+0x11c.. for dragon 0, +0x130..
// for dragon 1) the index of the largest, unsigned, scanned from element 4 down (a later one wins only when strictly
// larger; element 4 starts as the answer only when non-zero, else 0).
uint32_t MostUsedElement(const CKS08GameStructure* s, int32_t dragon) {
    const uint32_t base = dragon != 0 ? 0x130u : 0x11cu;
    uint32_t index = s->RtWord(base + 0x10) != 0 ? 4u : 0u;
    uint32_t best = s->RtWord(base + 0x10);
    for (int32_t e = 3; e >= 0; --e) {
        const uint32_t value = s->RtWord(base + 4u * static_cast<uint32_t>(e));
        if (best < value) {
            best = value;
            index = static_cast<uint32_t>(e);
        }
    }
    return index;
}
// 0x0050f200 CKS08GameStructure_GetDragonPlayTime_maybe: the float at +0x144 + 4 * dragon.
float DragonPlayTime(const CKS08GameStructure* s, int32_t dragon) {
    const uint32_t bits = s->RtWord(0x144 + 4 * static_cast<uint32_t>(dragon));
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
}
}  // namespace

// 0x00567b00 CKS08MenuStatsHeroes_OnItemEvent (vt+0xe8): item 0 validated: back in game (game state 7).
void CKS08MenuStatsHeroes::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (item == 0 && state == 4 && arg == 1) Gm(this)->RequestState(7);  // 0x004ec420
}

// 0x005678b8 CKS08MenuStatsHeroes_HandlePageInput_maybe
void CKS08MenuStatsHeroes::HandlePageInput() {
    CKInputDico* dico = FlashManagerDico();
    CKS08GameManager* gm = Gm(this);
    if (gm->GetPlayerCount() == 0) return;  // vt+0x154
    for (uint8_t player = 0; player < gm->GetPlayerCount(); ++player) {
        if (gm->IsPlayerActive(player) == 0) continue;  // vt+0x180
        const uint8_t base = static_cast<uint8_t>(player * 0x14);
        if (dico->GetButtonState(static_cast<uint8_t>((base + 10) & 0xfe)) == 0xff) {  // rlwinm 0,24,30
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));  // vt+0x344, 0x005587c0
            StartTransitionToMenu(0x13);  // 0x005148c0
        } else if (dico->GetButtonState(static_cast<uint8_t>(base + 11)) == 0xff) {
            Menu_PlayConfirmSound(static_cast<CKS08MenuObjectives*>(gm->Vf344()[10]));
            StartTransitionToMenu(10);
        }
    }
}

// 0x005683a8 CKS08MenuStatsHeroes_RefreshStatTexts_maybe
void CKS08MenuStatsHeroes::RefreshStatTexts() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    auto setVariable = [&](uint32_t slot, int32_t value) {
        if (value != g_pEngine->m_locManager->GetTextVariableValue(manager->GetCounterTextVarTable()[slot])) {  // 0x000376f8
            g_pEngine->m_locManager->SetTextVariableValue(manager->GetCounterTextVarTable()[slot], value);       // 0x00037730
        }
    };
    setVariable(28, static_cast<int32_t>(GetDragonTotalUpgradePoints(structure, 0)));  // 0x0050f050
    setVariable(34, static_cast<int32_t>(GetDragonTotalUpgradePoints(structure, 1)));
    setVariable(29, static_cast<int32_t>(BestCombo(structure, 0)));
    setVariable(35, static_cast<int32_t>(BestCombo(structure, 1)));
    setVariable(30, static_cast<int32_t>(EnemyKills(structure, 0)));
    setVariable(36, static_cast<int32_t>(EnemyKills(structure, 1)));
    if (CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[0].m_pElement)) {
        text->SetTextById(AccessorText(manager->m_unkF00[1], MostUsedElement(structure, 0)));  // vt+0x88
    }
    if (CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[1].m_pElement)) {
        text->SetTextById(AccessorText(manager->m_unkF00[1], MostUsedElement(structure, 1) + 5));
    }
    for (int32_t dragon = 0; dragon < 2; ++dragon) {
        const uint32_t seconds = static_cast<uint32_t>(ppc::fctidz(DragonPlayTime(structure, dragon)));  // the low word
        const uint32_t hours = seconds / 3600u;
        const uint32_t rest = seconds - hours * 3600u;
        const uint32_t minutes = rest / 60u;
        const uint32_t first = dragon == 0 ? 31u : 37u;
        setVariable(first, static_cast<int32_t>(hours));
        setVariable(first + 1, static_cast<int32_t>(minutes));
        setVariable(first + 2, static_cast<int32_t>(rest - minutes * 60u));
    }
}

// 0x00568cc0 CKS08MenuStatsHeroes_OnMenuState_maybe (vt+0xdc)
uint8_t CKS08MenuStatsHeroes::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (phase == 0) {
        HandlePageInput();
    } else if (phase == 1) {
        static const uint32_t kTimeVariables[6] = {31, 32, 33, 37, 38, 39};
        for (uint32_t slot : kTimeVariables) {
            g_pEngine->m_locManager->SetTextVariable(manager->GetCounterTextVarTable()[slot], 2);  // 0x000375b0
        }
        RefreshStatTexts();
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}
