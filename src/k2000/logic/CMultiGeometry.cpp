// CMultiGeometry.cpp - reconstructed original translation unit 0x1aa680-0x1aa998 (GAME_TOC1, main_toc1), 10 functions, 10 live.
// Primary class: CMultiGeometry  key 0x278c  category Logic  size 0x20  vtable 0xb1c4e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1aa680  CMultiGeometry_Delete
//   [ ] 0x1aa6d0  CMultiGeometry_RecursiveRegistration
//   [ ] 0x1aa730  RegisterCMultiGeometryClass
//   [ ] 0x1aa7a8  _GLOBAL__I_1aa7a8
//   [ ] 0x1aa7b8  CMultiGeometry_Destroy
//   [x] 0x1aa7e0  CMultiGeometry_Load
//   [ ] 0x1aa808  CMultiGeometry_Save
//   [x] 0x1aa830  CMultiGeometry_DeleteArray
//   [x] 0x1aa8d0  CMultiGeometry_CreateArray
//   [x] 0x1aa960  CMultiGeometry_Create
//
//   [ ] 0x9ab148  CMultiGeometry_IsKindOfClass  [inline]
//   [ ] 0x9ab170  CMultiGeometry_GetClassType  [inline]
//   [ ] 0x9ab178  CMultiGeometry_GetClassID  [inline]
//   [ ] 0x9ab180  CMultiGeometry_Destructor  [inline]
//   [ ] 0x9ab1a0  CMultiGeometry_DeletingDestructor  [inline]
#include "k2000/logic/CMultiGeometry.h"

// 0x001aa7e0 CMultiGeometry_Load
int32_t CMultiGeometry::Load(IKFile* file, int32_t type) {
    CMultiGeometryBasic::Load(file, type);  // 0x2455c8
    return 1;
}
