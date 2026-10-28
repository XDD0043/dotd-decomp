// CKS08MenuGame.cpp - reconstructed original translation unit 0x553bc8-0x5554c8 (GAME_TOC1, main_toc1), 23 functions, 17 live.
// Primary class: CKS08MenuGame  key 0x82cc  category Logic  size 0xec  vtable 0xb2c658
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x553bc8  CKS08MenuGame_Delete
//   [ ] 0x553c18  CKS08MenuGame_Construct  [dead]
//   [ ] 0x553cc0  FUN_00553cc0  [dead]
//   [ ] 0x553d70  CKS08MenuGame_IsOnlyComboButtonPressed_maybe  [dead]
//   [ ] 0x553ee0  CKS08MenuGame_SetAllUnlockFlags_maybe  [dead]
//   [ ] 0x554148  CKS08MenuGame_RecursiveRegistration
//   [ ] 0x5541b8  CKS08MenuGame_Destroy
//   [x] 0x5541e0  CKS08MenuGame_DeleteArray
//   [ ] 0x554280  RegisterCKS08MenuGameClass
//   [ ] 0x554308  _GLOBAL__D_554308
//   [ ] 0x554318  _GLOBAL__I_554318
//   [x] 0x554328  CKS08MenuGame_OnMenuState_maybe
//   [x] 0x5545b0  CKS08MenuGame_OnItemEvent
//   [ ] 0x554700  CKS08MenuGame_Construct_2  [dead]
//   [x] 0x5547a8  CKS08MenuGame_Create
//   [x] 0x554890  CKS08MenuGame_CreateArray
//   [x] 0x5549d0  CKS08MenuGame_Load
//   [ ] 0x554ab0  CKS08MenuGame_Save
//   [x] 0x554b90  CKS08MenuGame_vfEC
//   [ ] 0x554de8  CKS08MenuGame_UpdateSecretCodeInput_maybe  [dead]
//   [ ] 0x555120  CKS08MenuGame_DeletingDestructor
//   [ ] 0x555258  CKS08MenuGame_Destructor
//   [ ] 0x555390  CKS08MenuGame_Destructor_2
//
//   [x] 0x9c9a10  CKS08MenuGame_IsKindOfClass  [inline]
//   [x] 0x9c9a50  CKS08MenuGame_GetClassType  [inline]
//   [x] 0x9c9a58  CKS08MenuGame_GetClassID  [inline]
//   [x] 0x9c9a60  CKS08MenuGame_vfB8  [inline]
//   [x] 0x9c9a68  CKS08MenuGame_vfE0  [inline]
//   [x] 0x9c9a70  CKS08MenuGame_vfC4  [inline]
//   [x] 0x9c9a78  CKS08MenuGame_vfC8  [inline]
//   [x] 0x9c9a88  CKS08MenuGame_vfCC  [inline]
//   [x] 0x9c9a98  CKS08MenuGame_vfBC  [inline]
//   [x] 0x9c9aa0  CKS08MenuGame_vfC0  [inline]
//   [x] 0x9c9ab0  CKS08MenuGame_GetWidgetSlotCount  [inline]
//   [x] 0x9c9ab8  CKS08MenuGame_GetWidgetSlots  [inline]
#include "Spyro2008/logic/ui/CKS08MenuGame.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/components/CKLocTextAccessor.h"
#include <cstring>

#include "k2000/misc/CKInterfaceButtonBase.h"

#include "k2000/graphical/system/IKVideo.h"

#include "Spyro2008/logic/ui/CKS08MenuMain.h"

#include "Spyro2008/logic/CKS08GameStructure.h"

#include "Spyro2008/logic/CKS08GameManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/IKPlayer.h"
#include "k2000/misc/IKGameStructure.h"

// 0x005549d0 CKS08MenuGame_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuGame::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}

// 0x00554328 CKS08MenuGame_OnMenuState_maybe
uint8_t CKS08MenuGame::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
        static_cast<CKS08MenuMain*>(manager->Vf344()[9])->PlayLoopSounds();
        if ((manager->GetInterfaceVideo()->m_baData & 1) != 0) PlayScreenVideo(3, 1);
        static_cast<CKS08MenuMain*>(manager->Vf344()[9])->PlayEnterSounds();
        CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
        // BUG(original): no test of the button count; with no buttons the calls go through null.
        CKInterfaceButtonBase* button =
            static_cast<CKInterfaceButtonBase*>(m_apButtons.m_ui32NbUsedElt != 0 ? m_apButtons.m_pBlock[0] : nullptr);
        button->SetDisabled(structure->m_unk1f0[0x24a - 0x1f0]);  // +0x24a
        button = static_cast<CKInterfaceButtonBase*>(m_apButtons.m_ui32NbUsedElt > 1 ? m_apButtons.m_pBlock[1] : nullptr);
        button->SetDisabled(static_cast<uint8_t>(structure->m_unk1f0[0x23f - 0x1f0] ^ 1));  // +0x23f
        manager->SetPlayerActive(0, 1);
        manager->SetPlayerActive(1, manager->GetPlayerCount() == 2 ? 1 : 0);
        m_unke4 = 0;
        m_unke8 = 0;
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x005545b0 CKS08MenuGame_OnItemEvent
void CKS08MenuGame::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (item == 0) {
        if (state == 4 && phase == 1) {
            manager->m_unkAFC &= ~0x20u;
            static_cast<IKGameStructure*>(manager->m_gameStructure)
                ->ApplyPlayerGameState(static_cast<IKPlayer*>(manager->m_players[0]));  // vt+0x60
            MenuGm_RequestMenu(manager, 0x23);
        }
    } else if (item == 3 && state == 4 && phase == 1) {
        manager->BackupOptions();
        MenuGm_RequestMenu(manager, 0x19);
    }
}

namespace {
// 0x0050f200 CKS08GameStructure_GetDragonPlayTime_maybe (CKS08GameStructure.cpp, not ported there; the
// float at +0x144 + 4 * dragon, inside the run-time bytes the structure's header keeps as m_unk84).
float DragonPlayTime(CKS08GameStructure* structure, int32_t dragon) {
    float value;
    std::memcpy(&value, &structure->m_unk84[0x144 - 0x84 + 4 * dragon], 4);
    return value;
}

// The text an accessor gives: its first table entry `index`, or its default (+0x10) with no table.
IKSerializable* AccessorText(CKLocTextAccessor* accessor, uint32_t index) {
    return accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[index] : accessor->m_pText;
}

// The state's first text action gets `text` (its accessor's first entry, or its default).
void SetStateText(CKInterfaceButton::StateVisual& state, IKSerializable* text) {
    if (state.m_vTexts.m_ui32NbUsedElt == 0) return;
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(state.m_vTexts.m_pBlock[0].m_second);
    if (accessor->m_texts.m_pBlock == nullptr)
        accessor->m_pText = text;
    else
        accessor->m_texts.m_pBlock[0] = text;
}
}  // namespace

// 0x00554b90 CKS08MenuGame_vfEC
void CKS08MenuGame::VfEC(IKSerializable* button) {
    if (m_apButtons.m_ui32NbUsedElt == 0) return;
    if (m_apButtons.m_pBlock[0] != button) return;
    CKInterfaceButton* first = static_cast<CKInterfaceButton*>(m_apButtons.m_pBlock[0]);
    if (first == nullptr) return;
    CKS08GameStructure* structure =
        static_cast<CKS08GameStructure*>(static_cast<CKS08GameManager*>(m_pGameManager)->m_gameStructure);
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(m_pText);
    IKSerializable* text;
    if (structure->m_unk1f0[0x24a - 0x1f0] != 0) {
        text = AccessorText(texts, 2);
    } else if (DragonPlayTime(structure, 0) >= 0x1p+0f || DragonPlayTime(structure, 1) >= 0x1p+0f) {  // TOC1 +0x7ef0
        text = AccessorText(texts, 1);
    } else {
        text = AccessorText(texts, 0);
    }
    SetStateText(first->m_aStates[0], text);
    SetStateText(first->m_aStates[2], text);
    SetStateText(first->m_aStates[4], text);
}
