// CKTrcText.cpp - reconstructed original translation unit 0x36a90-0x36fc8 (GAME_TOC1, main_toc1), 22 functions, 17 live.
// Primary class: CKTrcText  key 0x684c  category Logic  size 0x1c  vtable 0xb145f0
// Other owners: CLocManager (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x36a90  CKTrcText_Delete
//   [ ] 0x36ae0  RegisterCKTrcTextClass
//   [ ] 0x36b58  _GLOBAL__I_36b58
//   [ ] 0x36b68  CKTrcText_PostLoad
//   [x] 0x36b90  CKTrcText_Load
//   [ ] 0x36bb8  CKTrcText_Save
//   [ ] 0x36be0  CKTrcText_RecursiveRegistration
//   [x] 0x36c08  CKTrcText_ClearGameData_maybe
//   [x] 0x36c30  CKTrcText_InitGameData
//   [ ] 0x36c58  CKTrcText_DeletingDestructor
//   [ ] 0x36ca0  CKTrcText_Destructor
//   [ ] 0x36cd0  CKTrcText_BaseDestructor
//   [ ] 0x36d00  CKTrcText_Construct  [dead]
//   [ ] 0x36d38  CKTrcText_Construct_2  [dead]
//   [x] 0x36d70  CKTrcText_DeleteArray
//   [x] 0x36e18  CKTrcText_CreateArray
//   [x] 0x36ed0  CKTrcText_Create
//   [ ] 0x36f28  CLocManager_Delete
//   [ ] 0x36f78  FUN_00036f78  [dead]
//   [ ] 0x36f80  FUN_00036f80  [dead]
//   [x] 0x36fb8  CLocManager_vf50
//   [ ] 0x36fc0  KStub_Nop_36fc0  [dead]
//
//   [ ] 0x9945a8  CKTrcText_IsKindOfClass  [inline]
//   [x] 0x9945f0  CKTrcText_GetClassType  [inline]
//   [x] 0x9945f8  CKTrcText_GetClassID  [inline]
#include "k2000/logic/ui/CKTrcText.h"

// 0x00036b90 CKTrcText_Load
int32_t CKTrcText::Load(IKFile* file, int32_t type) {
    CKLocText::Load(file, type);
    return 1;
}
