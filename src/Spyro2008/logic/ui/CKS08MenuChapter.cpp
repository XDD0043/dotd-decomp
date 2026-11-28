// CKS08MenuChapter.cpp - reconstructed original translation unit 0x547150-0x548a88 (GAME_TOC1, main_toc1), 18 functions, 16 live.
// Primary class: CKS08MenuChapter  key 0x8b0c  category Logic  size 0x110  vtable 0xb2c238
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x547150  CKS08MenuChapter_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x547178  CKS08MenuChapter_Destroy  (inherited: CKMenuBase114c::Destroy)
//   [x] 0x5471a0  CKS08MenuChapter_DeleteArray
//   [ ] 0x547248  RegisterCKS08MenuChapterClass
//   [ ] 0x5472d0  _GLOBAL__D_5472d0
//   [ ] 0x5472e0  _GLOBAL__I_5472e0
//   [ ] 0x5472f0  CKS08MenuChapter_Construct  [dead]
//   [x] 0x547398  CKS08MenuChapter_vfE8
//   [ ] 0x547528  CKS08MenuChapter_Save
//   [x] 0x5475d0  CKS08MenuChapter_Load
//   [ ] 0x547678  CKS08MenuChapter_Construct_2  [dead]
//   [x] 0x547720  CKS08MenuChapter_CreateArray
//   [x] 0x547868  CKS08MenuChapter_Create
//   [x] 0x547950  CKS08MenuChapter_RefreshChapterTexts_maybe
//   [x] 0x548180  CKS08MenuChapter_OnMenuState_maybe
//   [x] 0x5486e0  CKS08MenuChapter_Destructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x548818  CKS08MenuChapter_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x548950  CKS08MenuChapter_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9c96f8  CKS08MenuChapter_IsKindOfClass  [inline]
//   [x] 0x9c9738  CKS08MenuChapter_GetClassType  [inline]
//   [x] 0x9c9740  CKS08MenuChapter_GetClassID  [inline]
//   [x] 0x9c9748  CKS08MenuChapter_vfB8  [inline]
//   [x] 0x9c9750  CKS08MenuChapter_vfE0  [inline]
//   [x] 0x9c9758  CKS08MenuChapter_GetWidgetSlotCount  [inline]
//   [x] 0x9c9760  CKS08MenuChapter_GetWidgetSlots  [inline]
//   [x] 0x9c9770  CKS08MenuChapter_vfC4  [inline]
//   [x] 0x9c9778  CKS08MenuChapter_vfC8  [inline]
//   [x] 0x9c9788  CKS08MenuChapter_vfCC  [inline]
//   [x] 0x9c9798  CKS08MenuChapter_vfBC  [inline]
//   [x] 0x9c97a0  CKS08MenuChapter_vfC0  [inline]
//   [x] 0x9c97b0  CKS08MenuChapter_vfF0  [inline]
//   [x] 0x9c97b8  CKS08MenuChapter_vfF4  [inline]
//   [x] 0x9c97c0  CKS08MenuChapter_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuChapter.h"

#include "Spyro2008/logic/CKS08GameLevel.h"
#include "Spyro2008/logic/CKS08GameLevelCollectible.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/ui/CKS08MenuMain.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGameState.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/misc/Engine.h"

// 0x005475d0 CKS08MenuChapter_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuChapter::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadRaw(file, &m_unk108, 4);
    ReadRaw(file, &m_unk10c, 4);
    return 1;
}

namespace {

// Local copies of two CKS08GameLevel / CKS08GameStructure functions (Spyro2008/logic/CKS08GameLevel.cpp and
// CKS08GameStructure.cpp are P12's: replace these with theirs once ported).
// 0x00507440 CKS08GameLevel_CountCollectedOfType_maybe: the level's collectibles of `type` (+0x1d) not collected (+0x1c 0:
// subi / rlwinm takes the sign of +0x1c - 1).
uint32_t CountUncollectedOfType(CKS08GameLevel* level, uint8_t type) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < level->m_vpCollectibles.m_ui32NbUsedElt; ++i) {
        CKS08GameLevelCollectible* collectible = level->m_vpCollectibles.m_pBlock[i];
        if (collectible->m_ui8Category != type) continue;
        count += (static_cast<uint32_t>(collectible->m_bCollected) - 1u) >> 31;
    }
    return count;
}
// 0x00510158 CKS08GameStructure_CountCollectedOfTypeInLevel_maybe: the same in the last stage of main level `level`; 0
// without one.
uint32_t CountUncollectedOfTypeInLevel(CKS08GameStructure* structure, uint8_t type, uint8_t level) {
    for (uint32_t i = structure->m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[i - 1];
        if (static_cast<int32_t>(level) != Level_GetMainLevelIndex(stage)) continue;  // 0x00506ba8
        return CountUncollectedOfType(static_cast<CKS08GameLevel*>(stage), type);
    }
    return 0;
}

}  // namespace

// 0x00547950 CKS08MenuChapter_RefreshChapterTexts_maybe
void CKS08MenuChapter::RefreshChapterTexts(uint8_t level) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    static const uint8_t kTypes[5] = {1, 2, 3, 0, 4};
    for (uint32_t k = 0; k != 5; ++k) {
        const int32_t count = static_cast<int32_t>(CountUncollectedOfTypeInLevel(structure, kTypes[k], level));  // 0x510158
        const uint32_t var = manager->GetCounterTextVarTable()[0xe + 2 * k];  // vt+0x354, +0x38 + 8k
        if (count != g_pEngine->m_locManager->GetTextVariableValue(var)) {    // 0x376f8
            g_pEngine->m_locManager->SetTextVariableValue(manager->GetCounterTextVarTable()[0xe + 2 * k], count);  // 0x37730
        }
        // Both words white unless none is left (then the two file colours).
        uint32_t iconColor = 0xffffffffu;
        uint32_t textColor = 0xffffffffu;
        if (count == 0) {
            iconColor = m_unk108;
            textColor = m_unk10c;
        }
        CBillboard2d* icon = static_cast<CBillboard2d*>(m_aWidgetSlots[k].m_pElement);
        if (icon != nullptr) {
            uint32_t color = iconColor;
            icon->IKBillboard2d::SetColor(reinterpret_cast<const uint8_t*>(&color));  // IKBillboard2d vt+0x28
        }
        CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[k + 5].m_pElement);
        if (text != nullptr) {
            uint32_t color = textColor;
            text->IKText2d::SetColor(reinterpret_cast<const uint8_t*>(&color));  // IKText2d vt+0x44
            text->m_VarColor = textColor;  // +0x6fc (the text part's +0x6d4)
        }
    }
}

// 0x00548180 CKS08MenuChapter_OnMenuState_maybe
uint8_t CKS08MenuChapter::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        // The focused chapter (+0x6c) to its main level index (chapter 4 is level 5, chapter 10 level 4, ...).
        static const uint8_t kLevels[11] = {0, 1, 2, 3, 5, 7, 8, 9, 10, 0xb, 4};
        if (m_aui8FocusedItem[0] <= 10) RefreshChapterTexts(kLevels[m_aui8FocusedItem[0]]);
    } else if (phase == 1) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
        static_cast<CKS08MenuMain*>(manager->Vf344()[9])->PlayLoopSounds();   // inlined in the original
        static_cast<CKS08MenuMain*>(manager->Vf344()[9])->PlayEnterSounds();  // inlined in the original
        // The buttons from the last: button i disabled unless its unlock byte is set.
        static const uint16_t kUnlock[11] = {0x23f, 0x240, 0x241, 0x242, 0x244, 0x246, 0x247, 0x248, 0x249, 0x24a, 0x243};
        for (uint32_t i = 11; i-- != 0;) {
            if (i >= m_apButtons.m_ui32NbUsedElt) continue;
            CKInterfaceButtonBase* button = static_cast<CKInterfaceButtonBase*>(m_apButtons.m_pBlock[i]);
            if (button == nullptr) continue;
            CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
            button->SetDisabled(static_cast<uint8_t>(structure->m_unk1f0[kUnlock[i] - 0x1f0] ^ 1));  // vt+0x84
        }
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x00547398 CKS08MenuChapter_vfE8
void CKS08MenuChapter::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (phase != 1 || state != 4 || item == 0xb) return;
    CKInterfaceButton* button =
        static_cast<CKInterfaceButton*>(item < m_apButtons.m_ui32NbUsedElt ? m_apButtons.m_pBlock[item] : nullptr);
    // BUG(original): no null test of the button nor a count test of its reference list.
    IKSerializable* spawnPoint = button->m_aStates[4].m_vpUnk64.m_pBlock[0];  // +0x374
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    const uint8_t filter = 1;
    IKGameStructure* structure = static_cast<IKGameStructure*>(manager->m_gameStructure);
    for (uint32_t i = structure->CountGameStates(&filter); i != 0; --i) {  // vt+0x68
        structure = static_cast<IKGameStructure*>(manager->m_gameStructure);
        CKGameState* gameState = structure->m_vpStates.m_pBlock[i - 1];
        if (reinterpret_cast<IKSerializable*>(gameState->m_pGameSpawnPoint) != spawnPoint) continue;
        manager->m_unkAFC = (manager->m_unkAFC & ~0x20u) | 0x20u;
        static_cast<IKGameStructure*>(manager->m_gameStructure)->m_vpStates.m_pBlock[i - 1]->ApplyToStructure();  // vt+0x70
        break;
    }
    manager->m_ui32MenuStackDepth = 1;
    manager->m_aMenuStack[0] = 0x20;
}
