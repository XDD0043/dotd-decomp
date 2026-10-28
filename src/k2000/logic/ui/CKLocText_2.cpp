// CKLocText_2.cpp - reconstructed original translation unit 0x35948-0x35e70 (GAME_TOC1, main_toc1), 19 functions, 18 live.
// Primary class: CKLocText  key 0x680c  category Logic  size 0x1c  vtable 0xb144a8
// Other owners: LocString (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x35948  CKLocText_Delete
//   [ ] 0x35998  CKLocText_RecursiveRegistration
//   [ ] 0x359a0  RegisterCKLocTextClass
//   [ ] 0x35a18  _GLOBAL__I_35a18
//   [ ] 0x35a28  CKLocText_PostLoad
//   [x] 0x35a50  CKLocText_Load
//   [ ] 0x35a78  CKLocText_Save
//   [x] 0x35aa0  CKLocText_ClearGameData_maybe
//   [x] 0x35ac8  CKLocText_InitGameData
//   [ ] 0x35b00  CKLocText_DeletingDestructor
//   [ ] 0x35b48  CKLocText_Destructor
//   [ ] 0x35b78  CKLocText_BaseDestructor
//   [ ] 0x35ba8  CKLocText_Construct_2  [dead]
//   [x] 0x35be0  CKLocText_Construct
//   [x] 0x35c18  CKLocText_DeleteArray
//   [x] 0x35cc0  LocString_CopyText
//   [x] 0x35d28  LocString_GetText
//   [x] 0x35d60  CKLocText_CreateArray
//   [x] 0x35e18  CKLocText_Create
//
//   [ ] 0x9944d0  CKLocText_IsKindOfClass  [inline]
//   [x] 0x994508  CKLocText_GetClassType  [inline]
//   [x] 0x994510  CKLocText_GetClassID  [inline]
#include "k2000/logic/ui/CKLocText.h"

#include "k2000/logic/ui/CLocManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Wcs.h"

// 0x00035a50 CKLocText_Load
int32_t CKLocText::Load(IKFile* file, int32_t type) {
    KBase700C::Load(file, type);
    return 1;
}

// 0x00035ac8 CKLocText_InitGameData
void CKLocText::InitializeGameData() {
    IKGameObject::InitializeGameData();
    m_pText = nullptr;
}

namespace {
// 0x00c2966e: the text copied while the loc manager has no game data: " ".
const uint16_t kLocTextSpace[2] = {0x20, 0};
}  // namespace

// 0x00035cc0 LocString_CopyText: the text's string, or " " while the engine's loc manager has no
// localised game data (CLocManager +0xb0).
void LocString_CopyText(const CKLocText* text, uint16_t* dst) {
    if (g_pEngine->m_locManager->m_bGameLocalizedDataValid == 0) {
        WStr_CopyReturnEnd(dst, kLocTextSpace);
        return;
    }
    WStr_CopyReturnEnd(dst, text->m_pText);
}

// 0x00035d28 LocString_GetText: the text's string while the loc manager has localised game data, else " ".
const uint16_t* LocString_GetText(const CKLocText* text) {
    if (g_pEngine->m_locManager->m_bGameLocalizedDataValid == 0) return kLocTextSpace;
    return text->m_pText;
}
