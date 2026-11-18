// CKPxMeshShape.cpp - reconstructed original translation unit 0x22ecf8-0x22f1c8 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPxMeshShape  key 0x484c  category Logic  size 0xa8  vtable 0xb20548
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22ecf8  CKPxMeshShape_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x22ed48  RegisterCKPxMeshShapeClass
//   [ ] 0x22edc0  _GLOBAL__I_22edc0
//   [x] 0x22edd0  CKPxMeshShape_Load
//   [ ] 0x22ee90  CKPxMeshShape_Save
//   [x] 0x22eeb8  CKPxMeshShape_RecursiveRegistration  (KBase474C's vf24 0x22cbd0: returns 1)
//   [x] 0x22eee0  CKPxMeshShape_Destroy  (KBase474C's: the matrices destroyed)
//   [x] 0x22ef08  CKPxMeshShape_DeletingDestructor  (the destructor; delete)
//   [x] 0x22ef50  CKPxMeshShape_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22ef80  CKPxMeshShape_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22efb0  CKPxMeshShape_Construct  (header)
//   [x] 0x22efe8  CKPxMeshShape_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22f020  CKPxMeshShape_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x22f0c0  CKPxMeshShape_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x22f170  CKPxMeshShape_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//
//   [ ] 0x9b4f80  CKPxMeshShape_InitFromDesc_maybe  [inline]
//   [ ] 0x9b5158  CKPxMeshShape_ExportState  [inline]
//   [ ] 0x9b6ae0  CKPxMeshShape_IsKindOfClass  [inline]
//   [ ] 0x9b6b18  CKPxMeshShape_GetClassType  [inline]
//   [ ] 0x9b6b20  CKPxMeshShape_GetClassID  [inline]
//   [ ] 0x9b6b28  CKPxMeshShape_ComputeInertiaTensor_maybe  [inline]
//   [ ] 0x9b6b70  CKPxMeshShape_vf60  [inline]
//   [ ] 0x9b6b78  CKPxMeshShape_vf64  [inline]
#include "k2000/logic/render/CKPxMeshShape.h"

// 0x0022edd0 CKPxMeshShape_Load: the reference through the file's resolver (+0x10, its vt+0x24), else 4 raw bytes.
int32_t CKPxMeshShape::Load(IKFile* file, int32_t type) {
    KBase474C::Load(file, type);  // 0x0022d470
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unka4);
    return 1;
}
