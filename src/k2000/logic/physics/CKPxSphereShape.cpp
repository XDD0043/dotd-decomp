// CKPxSphereShape.cpp - reconstructed original translation unit 0x22f1c8-0x22f6c8 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPxSphereShape  key 0x47cc  category Logic  size 0xac  vtable 0xb205c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22f1c8  CKPxSphereShape_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x22f218  RegisterCKPxSphereShapeClass
//   [ ] 0x22f290  _GLOBAL__I_22f290
//   [ ] 0x22f2a0  CKPxSphereShape_Save
//   [x] 0x22f2c8  CKPxSphereShape_RecursiveRegistration  (KBase474C's vf24 0x22cbd0: returns 1)
//   [x] 0x22f2f0  CKPxSphereShape_Destroy  (KBase474C's: the matrices destroyed)
//   [x] 0x22f318  CKPxSphereShape_DeletingDestructor  (the destructor; delete)
//   [x] 0x22f360  CKPxSphereShape_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22f390  CKPxSphereShape_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22f3c0  CKPxSphereShape_Construct  (header)
//   [x] 0x22f3f8  CKPxSphereShape_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22f430  CKPxSphereShape_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x22f4d0  CKPxSphereShape_Load
//   [x] 0x22f5c0  CKPxSphereShape_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x22f670  CKPxSphereShape_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//
//   [ ] 0x9b6b80  CKPxSphereShape_IsKindOfClass  [inline]
//   [ ] 0x9b6bb8  CKPxSphereShape_GetClassType  [inline]
//   [ ] 0x9b6bc0  CKPxSphereShape_GetClassID  [inline]
//   [ ] 0x9b6bc8  CKPxSphereShape_ExportState  [inline]
//   [ ] 0x9b6dc0  CKPxSphereShape_InitFromDesc_maybe  [inline]
//   [ ] 0x9b6fb8  CKPxSphereShape_vf58  [inline]
//   [ ] 0x9b7120  CKPxSphereShape_vf60  [inline]
//   [ ] 0x9b7168  CKPxSphereShape_vf64  [inline]
//   [ ] 0x9b7170  CKPxSphereShape_ComputeInertiaTensor_maybe  [inline]
#include "k2000/logic/physics/CKPxSphereShape.h"

// 0x0022f4d0 CKPxSphereShape_Load
int32_t CKPxSphereShape::Load(IKFile* file, int32_t type) {
    KBase474C::Load(file, type);  // 0x0022d470
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unka4);
    ReadU32LE(file, &m_unka8);
    return 1;
}
