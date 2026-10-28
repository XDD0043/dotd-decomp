// CKFightZoneSectorGrpRoot.cpp - reconstructed original translation unit 0x26d6b8-0x26df60 (GAME_TOC1, main_toc1), 27 functions, 24 live.
// Primary class: CKFightZoneSectorGrpRoot  key 0x1904  category Group  size 0x2c  vtable 0xb21c38
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26d6b8  CKFightZoneSectorGrpRoot_Delete
//   [ ] 0x26d708  CKFightZoneSectorGrpRoot_Construct  [dead]
//   [ ] 0x26d778  CKFightZoneSectorGrpRoot_Start
//   [ ] 0x26d780  CKFightZoneSectorGrpRoot_Stop
//   [ ] 0x26d788  CKFightZoneSectorGrpRoot_Pause
//   [ ] 0x26d790  CKFightZoneSectorGrpRoot_Resume
//   [ ] 0x26d798  CKFightZoneSectorGrpRoot_Update
//   [ ] 0x26d7a0  CKFightZoneSectorGrpRoot_vfB8
//   [ ] 0x26d7a8  CKFightZoneSectorGrpRoot_Construct_2  [dead]
//   [ ] 0x26d818  CKFightZoneSectorGrpRoot_PostLoad
//   [ ] 0x26d840  RegisterCKFightZoneSectorGrpRootClass
//   [ ] 0x26d8b8  _GLOBAL__I_26d8b8
//   [x] 0x26d8c8  CKFightZoneSectorGrpRoot_DeleteArray
//   [ ] 0x26d968  CKFightZoneSectorGrpRoot_Restart
//   [ ] 0x26da60  CKFightZoneSectorGrpRoot_EnableMembers
//   [ ] 0x26dad0  CKFightZoneSectorGrpRoot_OnActivate
//   [ ] 0x26db40  CKFightZoneSectorGrpRoot_DisableMembers
//   [ ] 0x26dbb0  CKFightZoneSectorGrpRoot_OnDeactivate
//   [x] 0x26dc90  CKFightZoneSectorGrpRoot_CreateArray
//   [x] 0x26dd70  CKFightZoneSectorGrpRoot_Create
//   [ ] 0x26ddf8  CKFightZoneSectorGrpRoot_RecursiveRegistration
//   [ ] 0x26de20  CKFightZoneSectorGrpRoot_Save
//   [x] 0x26de48  CKFightZoneSectorGrpRoot_Load
//   [ ] 0x26de70  CKFightZoneSectorGrpRoot_Destroy
//   [ ] 0x26ded0  CKFightZoneSectorGrpRoot_DeletingDestructor
//   [ ] 0x26df20  CKFightZoneSectorGrpRoot_Destructor_2  [dead]
//   [ ] 0x26df40  CKFightZoneSectorGrpRoot_Destructor
//
//   [x] 0x9bbf50  CKFightZoneSectorGrpRoot_GetClassType  [inline]
//   [x] 0x9bbf58  CKFightZoneSectorGrpRoot_GetClassID  [inline]
//   [ ] 0x9bbf60  CKFightZoneSectorGrpRoot_vfCC  [inline]
//   [ ] 0x9bbf68  CKFightZoneSectorGrpRoot_IsKindOfClass  [inline]
#include "k2000/groups/CKFightZoneSectorGrpRoot.h"

// 0x0026de48 CKFightZoneSectorGrpRoot_Load: GroupBasicLoad only.
int32_t CKFightZoneSectorGrpRoot::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}
