// CKStdText.cpp - reconstructed original translation unit 0x36500-0x36a90 (GAME_TOC1, main_toc1), 17 functions, 14 live.
// Primary class: CKStdText  key 0x688c  category Logic  size 0x20  vtable 0xb14578
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x36500  CKStdText_Delete
//   [ ] 0x36550  RegisterCKStdTextClass
//   [ ] 0x365c8  _GLOBAL__I_365c8
//   [ ] 0x365d8  CKStdText_PostLoad
//   [x] 0x36600  CKStdText_Load
//   [ ] 0x366e0  CKStdText_Save
//   [ ] 0x36708  CKStdText_RecursiveRegistration
//   [x] 0x36730  CKStdText_ClearGameData_maybe
//   [x] 0x36758  CKStdText_InitGameData
//   [ ] 0x36790  CKStdText_Destructor
//   [ ] 0x367c8  CKStdText_Construct  [dead]
//   [ ] 0x36808  CKStdText_Construct_2  [dead]
//   [x] 0x36848  CKStdText_DeleteArray
//   [ ] 0x368e8  CKStdText_Destructor_2  [dead]
//   [ ] 0x36920  CKStdText_DeletingDestructor
//   [x] 0x36970  CKStdText_CreateArray
//   [x] 0x36a30  CKStdText_Create
//
//   [ ] 0x994550  CKStdText_IsKindOfClass  [inline]
//   [x] 0x994598  CKStdText_GetClassType  [inline]
//   [x] 0x9945a0  CKStdText_GetClassID  [inline]
#include "k2000/logic/ui/CKStdText.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/ui/CKLocSpeaker.h"

// 0x00036600 CKStdText_Load
int32_t CKStdText::Load(IKFile* file, int32_t type) {
    CKLocText::Load(file, type);
    if (type != K_GAME_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pSpeaker);
    return 1;
}

// 0x00036758 CKStdText_InitGameData
void CKStdText::InitializeGameData() {
    CKLocText::InitializeGameData();
    m_pSpeaker = nullptr;
}
