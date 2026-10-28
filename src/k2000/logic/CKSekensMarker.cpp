// CKSekensMarker.cpp - reconstructed original translation unit 0x1f7ff0-0x1f8450 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKSekensMarker  key 0x660c  category Logic  size 0x10  vtable 0xb1eb30
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f7ff0  CKSekensMarker_Delete
//   [ ] 0x1f8040  RegisterCKSekensMarkerClass
//   [ ] 0x1f80b8  _GLOBAL__I_1f80b8
//   [x] 0x1f80c8  CKSekensMarker_Load
//   [ ] 0x1f80f0  CKSekensMarker_Save
//   [ ] 0x1f8118  CKSekensMarker_RecursiveRegistration
//   [ ] 0x1f8140  CKSekensMarker_Destroy
//   [ ] 0x1f8168  CKSekensMarker_DeletingDestructor
//   [ ] 0x1f81b0  CKSekensMarker_Destructor
//   [ ] 0x1f81e0  CKSekensMarker_DestructBody
//   [x] 0x1f8210  CKSekensMarker_Construct
//   [ ] 0x1f8250  CKSekensMarker_Construct_2
//   [x] 0x1f8290  CKSekensMarker_DeleteArray
//   [x] 0x1f8330  CKSekensMarker_Create
//   [x] 0x1f8390  CKSekensMarker_CreateArray
//
//   [ ] 0x9b0ec0  CKSekensMarker_vf54  [inline]
//   [ ] 0x9b0ec8  CKSekensMarker_vf58  [inline]
//   [ ] 0x9b0ed0  CKSekensMarker_vf5C  [inline]
//   [ ] 0x9b0ed8  CKSekensMarker_IsKindOfClass  [inline]
//   [ ] 0x9b0f00  CKSekensMarker_GetClassType  [inline]
//   [ ] 0x9b0f08  CKSekensMarker_GetClassID  [inline]
//   [ ] 0x9b0f10  CKSekensMarker_vf50  [inline]
#include "k2000/logic/CKSekensMarker.h"

// 0x001f80c8 CKSekensMarker_Load
int32_t CKSekensMarker::Load(IKFile* file, int32_t type) {
    CKSekensElement::Load(file, type);
    return 1;
}
