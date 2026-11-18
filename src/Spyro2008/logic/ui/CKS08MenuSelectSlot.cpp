// CKS08MenuSelectSlot.cpp - reconstructed original translation unit 0x5625a0-0x564680 (GAME_TOC2, main_toc2), 23 functions, 20 live.
// Primary class: CKS08MenuSelectSlot  key 0x824c  category Logic  size ?  vtable 0xb2d2b8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5625a0  CKS08MenuSelectSlot_Delete
//   [ ] 0x5625f0  CKS08MenuSelectSlot_Construct  [dead]
//   [x] 0x562698  CKS08MenuSelectSlot_QueueNextStateAfterSave_maybe
//   [ ] 0x562778  CKS08MenuSelectSlot_ResetSelectionState_maybe  [dead]
//   [x] 0x562798  CKS08MenuSelectSlot_UpdateSlotButtonStates_maybe
//   [x] 0x562be8  CKS08MenuSelectSlot_RefreshSlotInfo_maybe
//   [x] 0x563720  CKS08MenuSelectSlot_OnSaveGameDone_maybe
//   [x] 0x5637f0  CKS08MenuSelectSlot_RecursiveRegistration  (RecursiveRegistration, vt+0x24)
//   [x] 0x563860  CKS08MenuSelectSlot_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x563888  CKS08MenuSelectSlot_DeleteArray
//   [ ] 0x563930  RegisterCKS08MenuSelectSlotClass
//   [ ] 0x5639b8  _GLOBAL__D_5639b8
//   [ ] 0x5639c8  _GLOBAL__I_5639c8
//   [x] 0x5639d8  CKS08MenuSelectSlot_vfE8  (OnItemState, vt+0xe8)
//   [ ] 0x563a50  CKS08MenuSelectSlot_Construct_2  [dead]
//   [x] 0x563af8  CKS08MenuSelectSlot_CreateArray
//   [x] 0x563c40  CKS08MenuSelectSlot_Create
//   [x] 0x563d28  CKS08MenuSelectSlot_Load
//   [x] 0x563e08  CKS08MenuSelectSlot_OnMenuState_maybe  (OnMenuState, vt+0xdc)
//   [ ] 0x5641f8  CKS08MenuSelectSlot_Save
//   [x] 0x5642d8  CKS08MenuSelectSlot_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x564410  CKS08MenuSelectSlot_Destructor_2  (the same as 0x5642d8 CKS08MenuSelectSlot_Destructor)
//   [x] 0x564548  CKS08MenuSelectSlot_DeletingDestructor  (the deleting form of 0x5642d8 CKS08MenuSelectSlot_Destructor)
//
//   [x] 0x9ca2d8  CKS08MenuSelectSlot_IsKindOfClass  [inline]
//   [x] 0x9ca318  CKS08MenuSelectSlot_GetClassType  [inline]
//   [x] 0x9ca320  CKS08MenuSelectSlot_GetClassID  [inline]
//   [x] 0x9ca328  CKS08MenuSelectSlot_vfB8  [inline]
//   [x] 0x9ca330  CKS08MenuSelectSlot_vfE0  [inline]
//   [x] 0x9ca338  CKS08MenuSelectSlot_GetWidgetSlotCount  [inline]
//   [x] 0x9ca340  CKS08MenuSelectSlot_GetWidgetSlots  [inline]
//   [x] 0x9ca350  CKS08MenuSelectSlot_vfC4  [inline]
//   [x] 0x9ca358  CKS08MenuSelectSlot_vfC8  [inline]
//   [x] 0x9ca368  CKS08MenuSelectSlot_vfCC  [inline]
//   [x] 0x9ca378  CKS08MenuSelectSlot_vfBC  [inline]
//   [x] 0x9ca380  CKS08MenuSelectSlot_vfC0  [inline]
//   [x] 0x9ca390  CKS08MenuSelectSlot_vfF0  [inline]
//   [x] 0x9ca398  CKS08MenuSelectSlot_vfF4  [inline]
//   [x] 0x9ca3a0  CKS08MenuSelectSlot_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuSelectSlot.h"

#include "k2000/io/IKFile.h"

// 0x00563d28 CKS08MenuSelectSlot_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuSelectSlot::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}

// ==== C2.8 save-menu ===========================================================================================
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"

// 0x00563720 CKS08MenuSelectSlot_OnSaveGameDone_maybe
void CKS08MenuSelectSlot::OnSaveGameDone() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (manager->m_gameState.m_ui8Current == 7) {
        m_unk118 = 1;
        return;
    }
    if (*VfC0() == nullptr) return;                                         // vt+0xc0
    static_cast<CKFlashMessageOut*>(*VfC0())->PostFlashMessage();          // TocBridge -> 0x00075610
}

// 0x00562698 CKS08MenuSelectSlot_QueueNextStateAfterSave_maybe
void CKS08MenuSelectSlot::QueueNextStateAfterSave() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (manager->m_gameState.m_ui8Current == 7) {
        manager->m_ui32MenuStackDepth = 1;
        manager->m_aMenuStack[0] = 0x24;
        return;
    }
    if (m_unk116 == 0) {
        manager->m_ui32MenuStackDepth = 1;
        manager->m_aMenuStack[0] = 6;
        return;
    }
    const uint8_t menu = manager->MainMenuId();  // vt+0x2f8
    manager->m_ui32MenuStackDepth = 1;
    manager->m_aMenuStack[0] = menu;
}

// ==== C2.8 port-rest R11 =======================================================================================
#include <cstdio>
#include <cstring>

#include "Spyro2008/logic/CKS08GameStructure.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKGameState.h"
#include "k2000/logic/IKPlayer.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/ui/IKNode2d.h"

namespace {
CKS08GameManager* SlotGm(const CKS08MenuSelectSlot* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
// The save slot `slot`'s player: the game manager's +0x44 entry slot + 1 (the original's null test of &m_players
// always passes).
IKPlayer* SlotPlayer(CKS08GameManager* gm, uint32_t slot) { return static_cast<IKPlayer*>(gm->m_players[slot + 1]); }
// The slot button `index` (null past the vector's end, as the original's accessor; the callers do not test it).
CKInterfaceButtonBase* SlotButton(CKS08MenuSelectSlot* menu, uint32_t index) {
    if (index >= menu->m_apButtons.m_ui32NbUsedElt) return nullptr;
    return static_cast<CKInterfaceButtonBase*>(menu->m_apButtons.m_pBlock[index]);
}
// The text of a CKLocTextAccessor: its table's entry `index`, or its default (+0x10) without a table.
IKSerializable* SlotAccessorText(IKSerializable* object, uint32_t index) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(object);
    return accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[index] : accessor->m_pText;
}
CText2d* SlotText(CKS08MenuSelectSlot* menu, uint32_t slot) {
    return static_cast<CText2d*>(menu->m_aWidgetSlots[slot].m_pElement);
}
// The "Flash Manager" input project's second configuration (null: the original reads through address 0x10).
CKInputDico* SlotFlashManagerDico() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;  // 0x00106978
    if (project == 0xff) return nullptr;
    return &input->m_aaInputDico[project][1];
}
const char kNoSlotText[] = "---";                             // 0x00acb970
const char kNoNameText[] = "Erreur : Pas de nom associ\xe9";  // 0x00acb978 (Latin-1)
}  // namespace

// 0x00562798 CKS08MenuSelectSlot_UpdateSlotButtonStates_maybe
void CKS08MenuSelectSlot::UpdateSlotButtonStates() {
    CKS08GameManager* gm = SlotGm(this);
    const uint32_t flags = gm->m_unkAFC;
    if ((flags & 4u) != 0) {
        for (uint32_t i = 0; i < 5; ++i) {
            SlotButton(this, i)->SetDisabled(SlotPlayer(gm, i)->m_bUsed);  // vt+0x84
            SlotButton(this, i)->SetDisabled(SlotPlayer(gm, i)->m_unk09);
        }
    } else if ((flags & 8u) != 0) {
        for (uint32_t i = 0; i < 5; ++i) {
            IKPlayer* player = SlotPlayer(gm, i);
            if (player->m_unk09 != 0) SlotButton(this, i)->SetDisabled(1);
            else SlotButton(this, i)->SetDisabled(static_cast<uint8_t>(player->m_bUsed ^ 1));
        }
    } else if ((flags & 0x10u) != 0) {
        for (uint32_t i = 0; i < 5; ++i) SlotButton(this, i)->SetDisabled(0);
    }
}

// 0x00562be8 CKS08MenuSelectSlot_RefreshSlotInfo_maybe. The widgets: 0..3 the labels (the accessor's texts 0..3), 4 the
// level, 5 the spawn point, 6 the completion, 7 the play time.
void CKS08MenuSelectSlot::RefreshSlotInfo() {
    CKS08GameManager* gm = SlotGm(this);
    const uint32_t slot = m_unk110;
    if (slot <= 5 && SlotPlayer(gm, slot)->m_bUsed != 0) {
        IKPlayer* player = SlotPlayer(gm, slot);
        if (player->m_unk09 != 0) {
            for (uint32_t i = 0; i < 8; ++i) {
                if (CText2d* text = SlotText(this, i)) text->SetTextById(gm->Vf214());  // vt+0x88, vt+0x214
            }
            SlotText(this, 4)->SetTextById(SlotAccessorText(m_pText, 5));  // no null test
            return;
        }
        CKGameState* state = player->m_pGameState;
        IKGameStructure* structure = state->m_pGameStructure;
        for (uint32_t i = 4; i-- != 0;) {
            if (CText2d* text = SlotText(this, i)) text->SetTextById(SlotAccessorText(m_pText, i));
        }
        if (SlotText(this, 4) != nullptr) {
            const uint32_t level =
                static_cast<uint32_t>(Level_GetMainLevelIndex(state->m_pGameSpawnPoint->m_pGameStage));  // 0x00506ba8
            if (level <= 0xb) {
                SlotText(this, 4)->SetTextById(SlotAccessorText(gm->m_unkF00[0], level));
            } else {
                SlotText(this, 5)->SetTextAscii(kNoNameText);  // BUG(original): slot 5, not 4
            }
        }
        if (CText2d* text = SlotText(this, 5)) {
            const CKGameSpawnPoint* spawn = state->m_pGameSpawnPoint;
            IKSerializable* name = spawn != nullptr
                                       ? spawn->m_pUnk34
                                       : static_cast<CKGameState*>(gm->m_unk474.m_pBlock[0])->m_pGameSpawnPoint->m_pUnk34;
            if (name == nullptr) text->SetTextAscii(kNoNameText);
            else text->SetTextById(name);
        }
        char buffer[128];
        if (CText2d* text = SlotText(this, 6)) {
            int64_t percent = 100;
            if (state->CountCompletedTrackedModules() != static_cast<int32_t>(structure->CountTrackedModules())) {  // 0x3de18 / 0x40f58
                const uint32_t done = static_cast<uint32_t>(state->CountCompletedTrackedModules());
                const uint32_t total = structure->CountTrackedModules();
                const float ratio = static_cast<float>(static_cast<double>(static_cast<uint64_t>(done))) /
                                    static_cast<float>(static_cast<double>(static_cast<uint64_t>(total)));
                percent = ppc::fctidz(static_cast<double>(ratio * 100.0f));  // TOC2 -0x7b28
            }
            std::snprintf(buffer, sizeof(buffer), "%i/100", static_cast<int32_t>(static_cast<uint32_t>(percent)));  // 0x00acb998
            text->SetTextAscii(buffer);
        }
        if (CText2d* text = SlotText(this, 7)) {
            float time;
            std::memcpy(&time, &player->m_unk10, 4);  // +0x10 the play time (seconds)
            const uint32_t hours = static_cast<uint32_t>(ppc::fctidz(static_cast<double>(time))) / 3600u;
            const float rest =
                ppc::fmadds(static_cast<float>(static_cast<double>(static_cast<uint64_t>(hours))), -3600.0f, time);
            const uint32_t minutes = static_cast<uint32_t>(ppc::fctidz(static_cast<double>(rest))) / 60u;
            const float secondsF =
                ppc::fmadds(static_cast<float>(static_cast<double>(static_cast<uint64_t>(minutes))), -60.0f, rest);
            const uint32_t seconds = static_cast<uint32_t>(ppc::fctidz(static_cast<double>(secondsF)));
            std::snprintf(buffer, sizeof(buffer), "%d h %d min %d s", static_cast<int32_t>(hours),
                          static_cast<int32_t>(minutes), static_cast<int32_t>(seconds));  // 0x00acb9a0
            text->SetTextAscii(buffer);
        }
        return;
    }
    for (uint32_t i = 4; i-- != 0;) {
        if (CText2d* text = SlotText(this, i)) text->SetTextById(SlotAccessorText(m_pText, i));
    }
    for (uint32_t i = 8; i-- != 4;) {
        if (CText2d* text = SlotText(this, i)) text->SetTextAscii(kNoSlotText);
    }
}

// 0x005639d8 CKS08MenuSelectSlot_vfE8
void CKS08MenuSelectSlot::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (arg != 1) return;
    if (state == 4) {
        if (item <= 4) {
            m_unk110 = item;
            SlotGm(this)->m_unkE94[1] = item;  // +0xe98
            return;
        }
        m_unk116 = arg;  // stb r6: 1
        m_unk110 = 0xff;
        return;
    }
    if (static_cast<uint8_t>(state - 2) > 1) return;
    m_unk110 = item <= 4 ? item : 0xffu;
    RefreshSlotInfo();
}

// 0x00563e08 CKS08MenuSelectSlot_OnMenuState_maybe
uint8_t CKS08MenuSelectSlot::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* gm = SlotGm(this);
    if (phase == 0) {
        if ((gm->m_unkAFC & 8u) == 0) {
            CKInputDico* dico = SlotFlashManagerDico();
            if (dico->GetButtonState(0x10) == 0xff && m_unk110 != 0xff &&
                SlotPlayer(gm, m_unk110)->m_bUsed != 0) {  // 0x0010e7d0
                m_unk115 = 1;
                gm->m_unkE94[1] = m_unk110;  // +0xe98
            }
        }
        if (VfCC()[3] != 0) QueueNextStateAfterSave();  // vt+0xcc; the same code inlined
    } else if (phase == 1) {
        m_unk60[1] = 1;
        ResumeInterfaceVideo();  // TocBridge 0x00515c68
        m_unk118 = 0;
        m_unk110 = 0;
        m_unk114 = 0;
        m_unk115 = 0;
        m_unk116 = 0;
        if ((gm->m_unkAFC & 8u) == 0) {
            if (IKNode2d* node = static_cast<IKNode2d*>(m_aWidgetSlots[10].m_pElement)) node->Enable();  // vt+0x64
            if (IKNode2d* node = static_cast<IKNode2d*>(m_aWidgetSlots[9].m_pElement)) node->Disable();  // vt+0x68
            if (CText2d* text = SlotText(this, 8)) text->SetTextById(SlotAccessorText(m_pText, 4));
        } else {
            if (IKNode2d* node = static_cast<IKNode2d*>(m_aWidgetSlots[9].m_pElement)) node->Enable();
            if (IKNode2d* node = static_cast<IKNode2d*>(m_aWidgetSlots[10].m_pElement)) node->Disable();
            if (CText2d* text = SlotText(this, 8)) text->SetTextById(gm->Vf214());
        }
        UpdateSlotButtonStates();
        RefreshSlotInfo();
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}
