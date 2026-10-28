// CKGrpS08ShieldPool.cpp - reconstructed original translation unit 0x26a1b8-0x26a5e0 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CKGrpS08ShieldPool  key 0xd04  category Group  size 0x2c  vtable 0xb21798
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26a1b8  CKGrpS08ShieldPool_Delete
//   [ ] 0x26a208  CKGrpS08ShieldPool_vfB8
//   [ ] 0x26a210  CKGrpS08ShieldPool_PostLoad
//   [ ] 0x26a238  RegisterCKGrpS08ShieldPoolClass
//   [ ] 0x26a2b0  _GLOBAL__I_26a2b0
//   [x] 0x26a2c0  CKGrpS08ShieldPool_DeleteArray
//   [x] 0x26a360  CKGrpS08ShieldPool_Create
//   [x] 0x26a3d8  CKGrpS08ShieldPool_CreateArray
//   [ ] 0x26a4a8  CKGrpS08ShieldPool_RecursiveRegistration
//   [x] 0x26a530  CKGrpS08ShieldPool_Load
//   [ ] 0x26a558  CKGrpS08ShieldPool_Save
//   [ ] 0x26a580  CKGrpS08ShieldPool_Destroy
//
//   [x] 0x9bb930  CKGrpS08ShieldPool_GetClassType  [inline]
//   [x] 0x9bb938  CKGrpS08ShieldPool_GetClassID  [inline]
//   [ ] 0x9bb940  CKGrpS08ShieldPool_vfCC  [inline]
//   [ ] 0x9bb948  CKGrpS08ShieldPool_vfEC  [inline]
//   [ ] 0x9bb950  CKGrpS08ShieldPool_IsKindOfClass  [inline]
//   [ ] 0x9bb9a8  CKGrpS08ShieldPool_DeletingDestructor  [inline]
//   [ ] 0x9bb9f8  CKGrpS08ShieldPool_Destructor  [inline]
#include "Spyro2008/groups/CKGrpS08ShieldPool.h"

// 0x0026a530 CKGrpS08ShieldPool_Load: GroupBasicLoad only.
int32_t CKGrpS08ShieldPool::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}
