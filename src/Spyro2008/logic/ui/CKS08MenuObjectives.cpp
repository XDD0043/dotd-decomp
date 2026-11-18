// CKS08MenuObjectives.cpp - reconstructed original translation unit 0x5582b8-0x55aec0 (GAME_TOC2, main_toc2), 30 functions, 22 live.
// Primary class: CKS08MenuObjectives  key 0x878c  category Logic  size ?  vtable 0xb2ca78
// Other owners: Menu (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5582b8  CKS08MenuObjectives_Delete
//   [ ] 0x558308  CKS08MenuObjectives_ClearObjectiveList_maybe  [dead]
//   [ ] 0x558540  CKS08MenuObjectives_SetTitleTextByIndex_maybe  [dead]
//   [x] 0x5585c0  CKS08MenuObjectives_SetEntryFontAndScale_maybe
//   [x] 0x5587c0  Menu_PlayConfirmSound_maybe
//   [x] 0x558820  CKS08MenuObjectives_SetEntryText_maybe
//   [ ] 0x558988  CKS08MenuObjectives_SetEntryTextVariantC_maybe  [dead]
//   [ ] 0x558aa8  CKS08MenuObjectives_SetEntryTextVariantB_maybe  [dead]
//   [ ] 0x558bc8  CKS08MenuObjectives_SetEntryTextVariantA_maybe  [dead]
//   [x] 0x558ce8  CKS08MenuObjectives_BuildObjectiveList_maybe
//   [x] 0x558e30  CKS08MenuObjectives_RecursiveRegistration
//   [x] 0x558ed0  CKS08MenuObjectives_Destroy
//   [x] 0x558f18  CKS08MenuObjectives_DeleteArray
//   [ ] 0x558fc0  RegisterCKS08MenuObjectivesClass
//   [ ] 0x559048  _GLOBAL__D_559048
//   [ ] 0x559058  _GLOBAL__I_559058
//   [x] 0x559068  CKS08MenuObjectives_OnItemEvent
//   [ ] 0x5590b0  CKS08MenuObjectives_SetSelectionAndWidgetStates_maybe  [dead]
//   [ ] 0x559198  CKS08MenuObjectives_Construct  [dead]
//   [ ] 0x559240  CKS08MenuObjectives_Construct_2  [dead]
//   [x] 0x5592e8  CKS08MenuObjectives_CreateArray
//   [x] 0x559438  CKS08MenuObjectives_Create
//   [x] 0x559528  CKS08MenuObjectives_RefreshPage_maybe
//   [x] 0x559a10  CKS08MenuObjectives_HandleInput_maybe
//   [x] 0x559c60  CKS08MenuObjectives_OnMenuState_maybe
//   [x] 0x55a128  CKS08MenuObjectives_Load
//   [ ] 0x55a660  CKS08MenuObjectives_Save
//   [x] 0x55ab18  CKS08MenuObjectives_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x55ac50  CKS08MenuObjectives_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x55ad88  CKS08MenuObjectives_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9c9d00  CKS08MenuObjectives_IsKindOfClass  [inline]
//   [x] 0x9c9d40  CKS08MenuObjectives_GetClassType  [inline]
//   [x] 0x9c9d48  CKS08MenuObjectives_GetClassID  [inline]
//   [x] 0x9c9d50  CKS08MenuObjectives_vfB8  [inline]
//   [x] 0x9c9d58  CKS08MenuObjectives_vfE0  [inline]
//   [x] 0x9c9d60  CKS08MenuObjectives_vfC4  [inline]
//   [x] 0x9c9d68  CKS08MenuObjectives_vfC8  [inline]
//   [x] 0x9c9d78  CKS08MenuObjectives_vfCC  [inline]
//   [x] 0x9c9d88  CKS08MenuObjectives_vfBC  [inline]
//   [x] 0x9c9d90  CKS08MenuObjectives_vfC0  [inline]
//   [x] 0x9c9da0  CKS08MenuObjectives_GetWidgetSlotCount  [inline]
//   [x] 0x9c9da8  CKS08MenuObjectives_GetWidgetSlots  [inline]
//   [x] 0x9c9db8  CKS08MenuObjectives_vfF0  [inline]
//   [x] 0x9c9dc0  CKS08MenuObjectives_vfF4  [inline]
//   [x] 0x9c9dc8  CKS08MenuObjectives_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuObjectives.h"

#include "k2000/io/IKFile.h"

// 0x0055a128 CKS08MenuObjectives_Load
int32_t CKS08MenuObjectives::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadTextureRef(file, &m_pTexture, 1);
    for (float& value : m_afUnk1e0) ReadF32LE(file, &value);
    ReadRaw(file, &m_unk1f8, 4);
    ReadRaw(file, &m_unk1fc, 4);
    for (float& value : m_afUnk200) ReadF32LE(file, &value);
    if (type == K_LEVEL_PLATEFORMS) m_unk1dc = 0;
    IKFile_ReadRef(file, &m_pText);
    IKFile_ReadRef(file, &m_pSound);
    return 1;
}

// 0x00558ed0 CKS08MenuObjectives_Destroy (C2.8 save-menu)
#include "Renderware/rwcore/RwTexture.h"
void CKS08MenuObjectives::Destroy() {
    CKMenuBase114c::Destroy();  // 0x00513c60
    if (m_pTexture != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_pTexture));
}

// ==== C2.8 menus-load ===============================================================================================
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"

// 0x005587c0 Menu_PlayConfirmSound_maybe: sound 0 of the menu's dictionary (+0x21c) from its start, the pan reset.
void Menu_PlayConfirmSound(CKS08MenuObjectives* menu) {
    CKSound* sound = static_cast<CKSoundDictionaryID*>(menu->m_pSound)->GetSound2(0);  // 0x00112bd8
    if (sound == nullptr) return;
    sound->ResetPan(1);   // 0x00111b70
    sound->Play(0.0f);    // 0x00111230
}

// 0x00558e30 CKS08MenuObjectives_RecursiveRegistration: the referenced objects' registration, then the base.
void CKS08MenuObjectives::RecursiveRegistration(int32_t type) {
    m_pText->RecursiveRegistration(type);
    m_pSound->RecursiveRegistration(type);
    CKMenuBase114c::RecursiveRegistration(type);
}

// ==== port-all P13 ==================================================================================================
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"

namespace {
// 0x004f6de0 CKS08GameManager_GetCurrentMainLevelIndex_maybe (CKS08GameManager_3.cpp; a local copy, as
// CKS08MenuStatsLevel.cpp's).
uint32_t ObjectivesCurrentMainLevelIndex(CKS08GameManager* manager) {
    return static_cast<uint32_t>(
        Level_GetMainLevelIndex(static_cast<IKGameStructure*>(manager->m_gameStructure)->GetCurrentLevel()));  // 0x00040be8
}
IKSerializable* ObjectivesAccessorText(IKSerializable* object, uint32_t index) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(object);
    return accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[index] : accessor->m_pText;
}
}  // namespace

// 0x005585c0 CKS08MenuObjectives_SetEntryFontAndScale_maybe
void CKS08MenuObjectives::SetEntryFontAndScale(float x, float scale, uint8_t row, void* texture, const uint32_t* color) {
    const uint32_t slot = row + 6u;
    IKNode2d* node = static_cast<IKNode2d*>(m_aWidgetSlots[slot].m_pElement);
    // BUG(original): no null test before the billboard part's calls.
    CBillboard2d* icon = static_cast<CBillboard2d*>(node);
    if (node != nullptr) node->Enable();                              // vt+0x64
    icon->IKBillboard2d::SetTexture(static_cast<RwTexture*>(texture));  // the part's vt+0x3c 0x66cb8
    SetElementX(x, slot & 0x1ff);                                       // vt+0x7c
    IKSerializable* element = GetWidgetSlots()[slot].m_pElement;        // vt+0x6c
    if (element != nullptr) {
        bool found = false;
        for (uint32_t i = m_aElementAnims.m_ui32NbUsedElt; i != 0; --i) {
            if (m_aElementAnims.m_pBlock[i - 1].m_pElement != element) continue;
            m_aElementAnims.m_pBlock[i - 1].m_fUnk28 = scale;
            found = true;
            break;
        }
        if (!found) {
            static_cast<IKNode2d*>(element)->m_v2ConstantScale.m_fY = scale;
            static_cast<IKNode2d*>(element)->m_v2ConstantScale.m_fX = scale;
        }
    }
    uint32_t copy = *color;
    icon->IKBillboard2d::SetColor(reinterpret_cast<const uint8_t*>(&copy));  // the part's vt+0x28
}

// 0x00558820 CKS08MenuObjectives_SetEntryText_maybe
void CKS08MenuObjectives::SetEntryText(float x, float height, uint8_t row, IKSerializable* text, const uint32_t* color) {
    const uint32_t slot = row + 1u;
    CText2d* label = static_cast<CText2d*>(m_aWidgetSlots[slot].m_pElement);
    // BUG(original): no null test before the text's calls.
    if (label != nullptr) label->Enable();  // vt+0x64
    label->SetTextById(text);               // vt+0x88
    SetElementX(x, slot & 0x1ff);           // vt+0x7c
    label->IKText2d::SetFontHeight(height); // 0x6b530 (bridge 0x98f7f0)
    uint32_t copy = *color;
    label->IKText2d::SetColor(reinterpret_cast<const uint8_t*>(&copy));  // the part's vt+0x44
}

// 0x00558ce8 CKS08MenuObjectives_BuildObjectiveList_maybe
void CKS08MenuObjectives::BuildObjectiveList() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    manager->UpdateCounterTextVariables();  // 0x502a80 (bridge 0x98f810)
    for (uint32_t level = 0; level != 12; ++level) {
        CKS08ObjectiveList* list = static_cast<CKS08ObjectiveList*>(manager->m_unkEC8[level]);
        const TVector<uint8_t, 8>& states = structure->m_avbUnk154[level];
        if (list == nullptr || states.m_ui32NbUsedElt == 0) continue;
        for (uint8_t j = 0; j < states.m_ui32NbUsedElt; ++j) {
            if (states.m_pBlock[j] != 1) continue;
            ObjectiveItem* item = &m_aItems[m_unk1dc++];
            item->m_ui32Index = j;
            item->m_pEntry = &list->m_aEntries[j];
            item->m_ui32Level = level;
        }
    }
}

// 0x00559528 CKS08MenuObjectives_RefreshPage_maybe
void CKS08MenuObjectives::RefreshPage(uint32_t first) {
    if (m_unk1dc == 0) {
        CText2d* bottom = static_cast<CText2d*>(m_aWidgetSlots[11].m_pElement);
        if (bottom != nullptr) {
            bottom->Enable();                                  // vt+0x64
            bottom->SetTextById(ObjectivesAccessorText(m_pText, 0));  // vt+0x88
        }
        return;
    }
    // BUG(original): the three colour words are registers set only by a state of 1 or 2; any other state reuses the
    // previous row's of the same type (the first one: an unset stack word; 0 here).
    uint32_t colors[3] = {0, 0, 0};
    uint8_t row = 0;
    for (uint32_t i = first; i < first + 5 && i < m_unk1dc; ++i) {
        const ObjectiveItem& item = m_aItems[i];
        const uint16_t type = item.m_pEntry->m_ui16Unk6;
        if (type > 2) continue;
        CKS08GameStructure* structure =
            static_cast<CKS08GameStructure*>(static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_gameStructure);
        const uint8_t state = structure->m_avbUnk154[item.m_ui32Level].m_pBlock[item.m_ui32Index];
        if (state == 1) {
            colors[type] = m_unk1f8;
        } else if (state == 2) {
            colors[type] = m_unk1fc;
        }
        SetEntryFontAndScale(m_afUnk200[3 + type], m_afUnk200[type], row, m_pTexture, &colors[type]);
        IKSerializable* text = CKS08ObjectiveList::GetFirstText(item.m_pEntry);  // 0x506400 (bridge 0x98f800)
        SetEntryText(m_afUnk1e0[3 + type], m_afUnk1e0[type], row, text, &colors[type]);
        ++row;
    }
    CText2d* bottom = static_cast<CText2d*>(m_aWidgetSlots[11].m_pElement);
    if (bottom != nullptr) {
        bottom->Disable();  // vt+0x68
        IKSerializable* text = static_cast<CKS08GameManager*>(m_pGameManager)->Vf214();  // vt+0x214
        bottom->SetTextById(text);  // vt+0x88
    }
}

// 0x00559a10 CKS08MenuObjectives_HandleInput_maybe
void CKS08MenuObjectives::HandleInput() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;  // 0x00106978
    CKInputDico* dico = project == 0xff ? nullptr : &input->m_aaInputDico[project][1];  // null: the original reads at 0x10
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    for (uint8_t player = 0; player < manager->GetPlayerCount(); ++player) {  // vt+0x154
        if (manager->IsPlayerActive(player) == 0) continue;                    // vt+0x180
        if (dico->GetButtonState(static_cast<uint8_t>((player * 0x14 + 10) & 0xfe)) == 0xff) {  // 0x0010e7d0
            Menu_PlayConfirmSound(this);
            StartTransitionToMenu(0x14);
        } else if (dico->GetButtonState(static_cast<uint8_t>(player * 0x14 + 0xb)) == 0xff) {
            Menu_PlayConfirmSound(this);
            StartTransitionToMenu(0x18);
        }
    }
}

// 0x00559c60 CKS08MenuObjectives_OnMenuState_maybe
uint8_t CKS08MenuObjectives::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        HandleInput();
    } else if (phase == 1) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
        manager->SetPlayerActive(0, 1);                                    // vt+0x184
        manager->SetPlayerActive(1, manager->GetPlayerCount() == 2 ? 1 : 0);
        const uint32_t level = ObjectivesCurrentMainLevelIndex(manager);  // 0x4f6de0 (bridge 0x98f860)
        static const uint8_t kRows[10] = {6, 1, 7, 2, 8, 3, 9, 4, 10, 5};
        for (uint8_t slot : kRows) {
            IKNode2d* node = static_cast<IKNode2d*>(m_aWidgetSlots[slot].m_pElement);
            if (node != nullptr) node->Disable();  // vt+0x68
        }
        m_unk1dc = 0;
        if (level < 12) {
            // BUG(original): no null test of the title's text.
            static_cast<CText2d*>(m_aWidgetSlots[0].m_pElement)
                ->SetTextById(ObjectivesAccessorText(manager->m_unkF00[0], level));  // vt+0x88
        }
        BuildObjectiveList();  // inlined in the original
        RefreshPage(0);
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x00559068 CKS08MenuObjectives_OnItemEvent
void CKS08MenuObjectives::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (item == 0 && state == 4 && phase == 1) {
        static_cast<CKS08GameManager*>(m_pGameManager)->RequestState(7);  // 0x4ec420 CKS08GameManager_RequestState_maybe
    }
}
