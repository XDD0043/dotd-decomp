// CKGrpStorage.cpp - reconstructed original translation unit 0x1de6d8-0x1dece0 (GAME_TOC1, main_toc1), 27 functions, 24 live.
// Primary class: CKGrpStorage  key 0x204  category Group  size 0x2c  vtable 0xb1e058
// Other owners: CKServiceLife (3), UnlinkLifeServiceChild (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1de6d8  CKGrpStorage_Delete
//   [ ] 0x1de728  CKGrpStorage_Construct  [dead]
//   [ ] 0x1de788  CKGrpStorage_vfB8
//   [ ] 0x1de790  CKGrpStorage_Construct_2  [dead]
//   [ ] 0x1de7f0  RegisterCKGrpStorageClass
//   [ ] 0x1de868  _GLOBAL__I_1de868
//   [x] 0x1de878  CKGrpStorage_DeleteArray
//   [ ] 0x1de918  CKGrpStorage_Update
//   [ ] 0x1de920  CKGrpStorage_Resume
//   [ ] 0x1de928  CKGrpStorage_Stop
//   [ ] 0x1de930  CKGrpStorage_Pause
//   [ ] 0x1de938  CKGrpStorage_Start
//   [ ] 0x1de940  CKGrpStorage_vf94
//   [ ] 0x1de948  CKGrpStorage_vf98
//   [x] 0x1de950  CKGrpStorage_CreateArray
//   [x] 0x1dea20  CKGrpStorage_Create
//   [ ] 0x1dea98  CKGrpStorage_RecursiveRegistration
//   [x] 0x1deac0  CKGrpStorage_Load
//   [ ] 0x1deae8  CKGrpStorage_Save
//   [ ] 0x1deb10  CKGrpStorage_Destroy
//   [ ] 0x1deb70  CKGrpStorage_DeletingDestructor
//   [ ] 0x1debc0  CKGrpStorage_Destructor
//   [ ] 0x1debe0  CKGrpStorage_Destructor_2  [dead]
//   [ ] 0x1dec00  CKServiceLife_Delete
//   [ ] 0x1dec50  CKServiceLife_InitializeService
//   [ ] 0x1dec60  CKServiceLife_DestroyService
//   [ ] 0x1dec68  UnlinkLifeServiceChild
//
//   [x] 0x9adc40  CKGrpStorage_GetClassType  [inline]
//   [x] 0x9adc48  CKGrpStorage_GetClassID  [inline]
//   [ ] 0x9adc50  CKGrpStorage_vfCC  [inline]
//   [ ] 0x9adc58  CKGrpStorage_IsKindOfClass  [inline]
#include "k2000/groups/CKGrpStorage.h"

// 0x001deac0 CKGrpStorage_Load: GroupBasicLoad only.
int32_t CKGrpStorage::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}
