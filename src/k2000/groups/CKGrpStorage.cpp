// CKGrpStorage.cpp - reconstructed original translation unit 0x1de6d8-0x1dece0 (GAME_TOC1, main_toc1), 27 functions, 24 live.
// Primary class: CKGrpStorage  key 0x204  category Group  size 0x2c  vtable 0xb1e058
// Other owners: CKServiceLife (3), UnlinkLifeServiceChild (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1de6d8  CKGrpStorage_Delete
//   [ ] 0x1de728  CKGrpStorage_Construct  [dead]
//   [ ] 0x1de788  CKGrpStorage_vfB8  [dead: vt+0xb8 (returns 1), called only by the dead CKCoreManager 0x1c330 / 0x1d460 (raw ELF scan of the vt+0xb8 calls)]
//   [ ] 0x1de790  CKGrpStorage_Construct_2  [dead]
//   [ ] 0x1de7f0  RegisterCKGrpStorageClass
//   [ ] 0x1de868  _GLOBAL__I_1de868
//   [x] 0x1de878  CKGrpStorage_DeleteArray
//   [x] 0x1de918  CKGrpStorage_Update  (empty: the IKBaseGroup default)
//   [x] 0x1de920  CKGrpStorage_Resume  (empty: the IKBaseGroup default)
//   [x] 0x1de928  CKGrpStorage_Stop  (empty: the IKBaseGroup default)
//   [x] 0x1de930  CKGrpStorage_Pause  (empty: the IKBaseGroup default)
//   [x] 0x1de938  CKGrpStorage_Start  (empty: the IKBaseGroup default)
//   [x] 0x1de940  CKGrpStorage_vf94  (empty: the IKBaseGroup default)
//   [x] 0x1de948  CKGrpStorage_vf98  (empty: the IKBaseGroup default)
//   [x] 0x1de950  CKGrpStorage_CreateArray
//   [x] 0x1dea20  CKGrpStorage_Create
//   [x] 0x1dea98  CKGrpStorage_RecursiveRegistration  (inherited: IKGroup_LevelReset 0x12a68, IKBaseGroup.h)
//   [x] 0x1deac0  CKGrpStorage_Load
//   [ ] 0x1deae8  CKGrpStorage_Save
//   [x] 0x1deb10  CKGrpStorage_Destroy  (header)
//   [x] 0x1deb70  CKGrpStorage_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x1debc0  CKGrpStorage_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x1debe0  CKGrpStorage_Destructor_2  [dead]
//   [x] 0x1dec00  CKServiceLife_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKServiceLife))
//   [x] 0x1dec50  CKServiceLife_InitializeService  (CKServiceLife.h)
//   [x] 0x1dec60  CKServiceLife_DestroyService  (CKServiceLife.h)
//   [ ] 0x1dec68  UnlinkLifeServiceChild  [dead: no pointer to its descriptor 0xb75628, no call]
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
