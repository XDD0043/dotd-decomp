// CKS08MenuChapter.cpp - reconstructed original translation unit 0x547150-0x548a88 (GAME_TOC1, main_toc1), 18 functions, 16 live.
// Primary class: CKS08MenuChapter  key 0x8b0c  category Logic  size 0x110  vtable 0xb2c238
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x547150  CKS08MenuChapter_RecursiveRegistration
//   [ ] 0x547178  CKS08MenuChapter_Destroy
//   [x] 0x5471a0  CKS08MenuChapter_DeleteArray
//   [ ] 0x547248  RegisterCKS08MenuChapterClass
//   [ ] 0x5472d0  _GLOBAL__D_5472d0
//   [ ] 0x5472e0  _GLOBAL__I_5472e0
//   [ ] 0x5472f0  CKS08MenuChapter_Construct  [dead]
//   [ ] 0x547398  CKS08MenuChapter_vfE8
//   [ ] 0x547528  CKS08MenuChapter_Save
//   [x] 0x5475d0  CKS08MenuChapter_Load
//   [ ] 0x547678  CKS08MenuChapter_Construct_2  [dead]
//   [x] 0x547720  CKS08MenuChapter_CreateArray
//   [x] 0x547868  CKS08MenuChapter_Create
//   [ ] 0x547950  CKS08MenuChapter_RefreshChapterTexts_maybe
//   [ ] 0x548180  CKS08MenuChapter_OnMenuState_maybe
//   [ ] 0x5486e0  CKS08MenuChapter_Destructor
//   [ ] 0x548818  CKS08MenuChapter_Destructor_2
//   [ ] 0x548950  CKS08MenuChapter_DeletingDestructor
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
//   [ ] 0x9c97b0  CKS08MenuChapter_vfF0  [inline]
//   [ ] 0x9c97b8  CKS08MenuChapter_vfF4  [inline]
//   [ ] 0x9c97c0  CKS08MenuChapter_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuChapter.h"

#include "k2000/io/IKFile.h"

// 0x005475d0 CKS08MenuChapter_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuChapter::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadRaw(file, &m_unk108, 4);
    ReadRaw(file, &m_unk10c, 4);
    return 1;
}
