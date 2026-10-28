// CKDisplayBox.cpp - reconstructed original translation unit 0x94bf0-0x94eb0 (GAME_TOC1, main_toc1), 10 functions, 10 live.
// Primary class: CKDisplayBox  key 0x604c  category Logic  size 0x20  vtable 0xb16e10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x94bf0  CKDisplayBox_Delete
//   [ ] 0x94c40  CKDisplayBox_RecursiveRegistration
//   [ ] 0x94c48  RegisterCKDisplayBoxClass
//   [ ] 0x94cc0  _GLOBAL__I_94cc0
//   [ ] 0x94cd0  CKDisplayBox_Destroy
//   [x] 0x94cf8  CKDisplayBox_Load
//   [ ] 0x94d20  CKDisplayBox_Save
//   [x] 0x94d48  CKDisplayBox_DeleteArray
//   [x] 0x94de8  CKDisplayBox_CreateArray
//   [x] 0x94e78  CKDisplayBox_Create
//
//   [ ] 0x99c8a8  CKDisplayBox_IsKindOfClass  [inline]
//   [ ] 0x99c8d0  CKDisplayBox_GetClassType  [inline]
//   [ ] 0x99c8d8  CKDisplayBox_GetClassID  [inline]
//   [ ] 0x99c8e0  CKDisplayBox_DeletingDestructor  [inline]
//   [ ] 0x99c928  CKDisplayBox_Destructor  [inline]
#include "k2000/logic/CKDisplayBox.h"

#include "k2000/io/IKFile.h"

// 0x00094cf8 CKDisplayBox_Load
int32_t CKDisplayBox::Load(IKFile* file, int32_t type) {
    CMultiGeometryBasic::Load(file, type);
    return 1;
}
