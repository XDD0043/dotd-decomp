// CKPxCapsuleShape.cpp - reconstructed original translation unit 0x22e1c8-0x22e760 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPxCapsuleShape  key 0x480c  category Logic  size 0xb4  vtable 0xb20458
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22e1c8  CKPxCapsuleShape_Delete
//   [ ] 0x22e218  RegisterCKPxCapsuleShapeClass
//   [ ] 0x22e290  _GLOBAL__I_22e290
//   [ ] 0x22e2a0  CKPxCapsuleShape_Save
//   [x] 0x22e2c8  CKPxCapsuleShape_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x22e2f0  CKPxCapsuleShape_Destroy  (KBase474C's: the matrices destroyed)
//   [x] 0x22e318  CKPxCapsuleShape_DeletingDestructor  (the destructor; delete)
//   [x] 0x22e360  CKPxCapsuleShape_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22e390  CKPxCapsuleShape_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22e3c0  CKPxCapsuleShape_Construct  (header)
//   [x] 0x22e3f8  CKPxCapsuleShape_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22e430  CKPxCapsuleShape_DeleteArray
//   [x] 0x22e4d0  CKPxCapsuleShape_Create
//   [x] 0x22e528  CKPxCapsuleShape_CreateArray
//   [x] 0x22e5d8  CKPxCapsuleShape_Load
//
//   [ ] 0x9b5920  CKPxCapsuleShape_IsKindOfClass  [inline]
//   [ ] 0x9b5958  CKPxCapsuleShape_GetClassType  [inline]
//   [ ] 0x9b5960  CKPxCapsuleShape_GetClassID  [inline]
//   [ ] 0x9b5968  CKPxCapsuleShape_ExportState  [inline]
//   [ ] 0x9b5b70  CKPxCapsuleShape_InitFromDesc_maybe  [inline]
//   [ ] 0x9b5d78  CKPxCapsuleShape_vf64  [inline]
//   [ ] 0x9b5d80  CKPxCapsuleShape_vf60  [inline]
//   [ ] 0x9b5ec8  CKPxCapsuleShape_ComputeInertiaTensor_maybe  [inline]
//   [ ] 0x9b5f68  CKPxCapsuleShape_vf58  [inline]
#include "k2000/logic/CKPxCapsuleShape.h"

// 0x0022e5d8 CKPxCapsuleShape_Load
int32_t CKPxCapsuleShape::Load(IKFile* file, int32_t type) {
    KBase474C::Load(file, type);  // 0x0022d470
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unka4);
    ReadU32LE(file, &m_unka8);
    ReadU32LE(file, &m_unkac);
    ReadU32LE(file, &m_unkb0);
    return 1;
}
