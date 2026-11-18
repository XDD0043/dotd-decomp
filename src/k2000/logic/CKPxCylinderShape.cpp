// CKPxCylinderShape.cpp - reconstructed original translation unit 0x22e760-0x22ecf8 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPxCylinderShape  key 0x524c  category Logic  size 0xb4  vtable 0xb204d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22e760  CKPxCylinderShape_Delete
//   [ ] 0x22e7b0  RegisterCKPxCylinderShapeClass
//   [ ] 0x22e828  _GLOBAL__I_22e828
//   [ ] 0x22e838  CKPxCylinderShape_Save
//   [x] 0x22e860  CKPxCylinderShape_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x22e888  CKPxCylinderShape_Destroy  (KBase474C's: the matrices destroyed)
//   [x] 0x22e8b0  CKPxCylinderShape_DeletingDestructor  (the destructor; delete)
//   [x] 0x22e8f8  CKPxCylinderShape_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22e928  CKPxCylinderShape_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22e958  CKPxCylinderShape_Construct  (header)
//   [x] 0x22e990  CKPxCylinderShape_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22e9c8  CKPxCylinderShape_DeleteArray
//   [x] 0x22ea68  CKPxCylinderShape_Create
//   [x] 0x22eac0  CKPxCylinderShape_CreateArray
//   [x] 0x22eb70  CKPxCylinderShape_Load
//
//   [ ] 0x9b6208  CKPxCylinderShape_IsKindOfClass  [inline]
//   [ ] 0x9b6240  CKPxCylinderShape_GetClassType  [inline]
//   [ ] 0x9b6248  CKPxCylinderShape_GetClassID  [inline]
//   [ ] 0x9b6250  CKPxCylinderShape_ExportState  [inline]
//   [ ] 0x9b6458  CKPxCylinderShape_InitFromDesc_maybe  [inline]
//   [ ] 0x9b6660  CKPxCylinderShape_vf64  [inline]
//   [ ] 0x9b6668  CKPxCylinderShape_vf60  [inline]
//   [ ] 0x9b67a0  CKPxCylinderShape_ComputeInertiaTensor_maybe  [inline]
//   [ ] 0x9b6840  CKPxCylinderShape_vf58  [inline]
#include "k2000/logic/CKPxCylinderShape.h"

// 0x0022eb70 CKPxCylinderShape_Load
int32_t CKPxCylinderShape::Load(IKFile* file, int32_t type) {
    KBase474C::Load(file, type);  // 0x0022d470
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unka4);
    ReadU32LE(file, &m_unka8);
    ReadU32LE(file, &m_unkac);
    ReadU32LE(file, &m_unkb0);
    return 1;
}
