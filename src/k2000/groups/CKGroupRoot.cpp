// CKGroupRoot.cpp - reconstructed original translation unit 0x228b8-0x22cd0 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary class: CKGroupRoot  key 0x44  category Group  size 0x2c  vtable 0xb13990
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x228b8  CKGroupRoot_Delete
//   [ ] 0x22908  CKGroupRoot_PostLoad
//   [ ] 0x22930  RegisterCKGroupRootType
//   [ ] 0x229a8  _GLOBAL__I_229a8
//   [x] 0x229b8  CKGroupRoot_DeleteArray
//   [x] 0x22a58  CKGroupRoot_Create
//   [x] 0x22ad0  CKGroupRoot_CreateArray
//   [x] 0x22ba0  CKGroupRoot_Load
//   [ ] 0x22bc8  CKGroupRoot_RecursiveRegistration
//   [ ] 0x22c48  CKGroupRoot_Save
//   [ ] 0x22c70  CKGroupRoot_Destroy
//
//   [ ] 0x992cd8  CKGroupRoot_GetClassID  [inline]
//   [ ] 0x992ce0  CKGroupRoot_GetClassType  [inline]
//   [ ] 0x992ce8  CKGroupRoot_vfB8  [inline]
//   [ ] 0x992cf8  CKGroupRoot_vfCC  [inline]
//   [ ] 0x992d00  CKGroupRoot_vfC0  [inline]
//   [ ] 0x992f30  CKGroupRoot_IsKindOfClass  [inline]
//   [ ] 0x992f88  CKGroupRoot_DeletingDestructor  [inline]
//   [ ] 0x993040  CKGroupRoot_Destructor  [inline]
//   [ ] 0x993060  IKModule_IsKindOf  [inline]
//   [ ] 0x993088  IKModule_vfA4  [inline]
//   [ ] 0x993090  KStub_Return0_993090  [inline]
#include "k2000/groups/CKGroupRoot.h"

// 0x00022ba0 CKGroupRoot_Load (XXL2 CKGroupRoot::Load: GroupBasicLoad, then 1).
int32_t CKGroupRoot::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}
