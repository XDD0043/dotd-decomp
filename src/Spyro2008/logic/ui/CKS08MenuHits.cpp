// CKS08MenuHits.cpp - reconstructed original translation unit 0x5554c8-0x556840 (GAME_TOC1, main_toc1), 20 functions, 18 live.
// Primary class: CKS08MenuHits  key 0xa74c  category Logic  size 0xf0  vtable 0xb2c760
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5554c8  CKS08MenuHits_Delete
//   [ ] 0x555518  CKS08MenuHits_Construct  [dead]
//   [x] 0x5555c0  CKS08MenuHits_RefreshPageTexts
//   [x] 0x555800  CKS08MenuHits_OnItemEvent
//   [x] 0x555888  CKS08MenuHits_HandlePagingButtons
//   [x] 0x555a70  CKS08MenuHits_OnStatePhase
//   [x] 0x555b78  CKS08MenuHits_RecursiveRegistration
//   [x] 0x555c40  CKS08MenuHits_Destroy  (inherited: CKMenuBase_114c_maybe_Destroy)
//   [x] 0x555c68  CKS08MenuHits_DeleteArray
//   [ ] 0x555d10  RegisterCKS08MenuHitsClass
//   [ ] 0x555d98  _GLOBAL__D_555d98
//   [ ] 0x555da8  _GLOBAL__I_555da8
//   [ ] 0x555db8  CKS08MenuHits_Construct_2  [dead]
//   [x] 0x555e60  CKS08MenuHits_CreateArray
//   [x] 0x555fa8  CKS08MenuHits_Create
//   [x] 0x556090  CKS08MenuHits_Load
//   [ ] 0x556290  CKS08MenuHits_Save
//   [x] 0x556498  CKS08MenuHits_Destructor  (~CKMenuBase114c inlined: the same frees)
//   [x] 0x5565d0  CKS08MenuHits_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x556708  CKS08MenuHits_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9c9ac8  CKS08MenuHits_IsKindOfClass  [inline]
//   [x] 0x9c9b08  CKS08MenuHits_GetClassType  [inline]
//   [x] 0x9c9b10  CKS08MenuHits_GetClassID  [inline]
//   [x] 0x9c9b18  CKS08MenuHits_vfB8  [inline]
//   [x] 0x9c9b20  CKS08MenuHits_vfE0  [inline]
//   [x] 0x9c9b28  CKS08MenuHits_vfC4  [inline]
//   [x] 0x9c9b30  CKS08MenuHits_vfC8  [inline]
//   [x] 0x9c9b40  CKS08MenuHits_vfCC  [inline]
//   [x] 0x9c9b50  CKS08MenuHits_vfBC  [inline]
//   [x] 0x9c9b58  CKS08MenuHits_vfC0  [inline]
//   [x] 0x9c9b68  CKS08MenuHits_GetWidgetSlotCount  [inline]
//   [x] 0x9c9b70  CKS08MenuHits_GetWidgetSlots  [inline]
//   [x] 0x9c9b80  CKS08MenuHits_vfF0  [inline]
//   [x] 0x9c9b88  CKS08MenuHits_vfF4  [inline]
//   [x] 0x9c9b90  CKS08MenuHits_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuHits.h"

#include "k2000/io/IKFile.h"

// 0x00556090 CKS08MenuHits_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuHits::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pTextE0);
    IKFile_ReadRef(file, &m_pTextE4);
    IKFile_ReadRef(file, &m_pTextE8);
    return 1;
}

// ==== C2.8 live-fixes-3: the moves page ===========================================================================
// The pause menu's moves page (interface menu 7, "Menu Hits"): 32 pages, one per move, each a title (+0xe0), two texts
// (+0xe4, +0xe8) and the titles of the previous and next pages. Items 0 / 1 are the previous / next buttons (validated
// with Cross when focused, or at once with "Flash Manager" actions 8 / 9), item 2 the back item (Circle).
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

namespace {
// Entry `index` of a CKLocTextAccessor's table, or its default text (+0x10) without a table (no bounds test, as the original).
IKSerializable* AccessorText(IKSerializable* object, uint32_t index) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(object);
    return accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[index] : accessor->m_pText;
}
void SetSlotText(CKS08MenuHits* menu, uint32_t slot, IKSerializable* accessor, uint32_t index) {
    CText2d* text = static_cast<CText2d*>(menu->m_aWidgetSlots[slot].m_pElement);
    if (text == nullptr) return;
    text->SetTextById(AccessorText(accessor, index));  // vt+0x88
}
}  // namespace

// 0x005555c0 CKS08MenuHits_RefreshPageTexts: slot 0 the page's title, slots 1 and 2 its texts, slot 4 the next page's
// title, slot 3 the previous page's (in that order).
void CKS08MenuHits::RefreshPageTexts() {
    const uint32_t page = m_ui32Page;
    const uint32_t previous = page != 0 ? page - 1 : 0x1fu;
    SetSlotText(this, 0, m_pTextE0, page);
    SetSlotText(this, 1, m_pTextE4, m_ui32Page);
    SetSlotText(this, 2, m_pTextE8, m_ui32Page);
    SetSlotText(this, 4, m_pTextE0, (page + 1) & 0x1fu);
    SetSlotText(this, 3, m_pTextE0, previous);
}

// 0x00555800 CKS08MenuHits_OnItemEvent: after (arg 1) item 0 or 1 turned validated (state 4), the previous or next page.
void CKS08MenuHits::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (item == 0) {
        if (state != 4 || arg != 1) return;
        m_ui32Page = m_ui32Page == 0 ? 0x1fu : m_ui32Page - 1;
    } else if (item == 1) {
        if (state != 4 || arg != 1) return;
        m_ui32Page = m_ui32Page == 0x1f ? 0u : m_ui32Page + 1;
    } else {
        return;
    }
    RefreshPageTexts();
}

// 0x00555888 CKS08MenuHits_HandlePagingButtons: the player count read again each turn (vt+0x154); for an active player
// (vt+0x180), action 9 (+ 0x14 per player) validates item 1 with its delay, else action 8 item 0.
void CKS08MenuHits::HandlePagingButtons() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;  // 0x00106978
    CKInputDico* dico = project == 0xff ? nullptr : &input->m_aaInputDico[project][1];  // null: the original reads at 0x10
    for (uint8_t player = 0; player < static_cast<CKS08GameManager*>(m_pGameManager)->GetPlayerCount(); ++player) {
        if (static_cast<CKS08GameManager*>(m_pGameManager)->IsPlayerActive(player) == 0) continue;
        if (dico->GetButtonState(static_cast<uint8_t>(player * 0x14 + 9)) == 0xff) {  // 0x0010e7d0
            SetItemState(1, 1, 1);  // 0x00512040
        } else if (dico->GetButtonState(static_cast<uint8_t>((player * 0x14 + 8) & 0xfc)) == 0xff) {
            SetItemState(0, 1, 1);
        }
    }
}

// 0x00555a70 CKS08MenuHits_OnStatePhase
uint8_t CKS08MenuHits::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        HandlePagingButtons();
    } else if (phase == 1) {
        m_ui32Page = 0;
        RefreshPageTexts();
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}

// 0x00555b78 CKS08MenuHits_RecursiveRegistration: the base first, then the referenced objects' registration.
void CKS08MenuHits::RecursiveRegistration(int32_t type) {
    CKMenuBase114c::RecursiveRegistration(type);
    m_pTextE0->RecursiveRegistration(type);
    m_pTextE4->RecursiveRegistration(type);
    m_pTextE8->RecursiveRegistration(type);
}
