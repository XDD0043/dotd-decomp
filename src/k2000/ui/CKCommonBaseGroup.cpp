// CKCommonBaseGroup.cpp - reconstructed original translation unit 0x5a7d20-0x5a8260 (GAME_TOC2, main_toc2), 22 functions, 19 live.
// Primary owner: CKCommonBaseGroup (not a registered class)
// Other owners: UpdateCKCommonBaseGroup (1), RegisterCKCommonBaseGroupClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5a7d20  CKCommonBaseGroup_Destroy
//   [ ] 0x5a7d70  CKCommonBaseGroup_Construct  [dead]
//   [ ] 0x5a7dd0  CKCommonBaseGroup_vf50
//   [ ] 0x5a7dd8  CKCommonBaseGroup_vf68
//   [ ] 0x5a7de0  CKCommonBaseGroup_vf70
//   [ ] 0x5a7de8  CKCommonBaseGroup_vf78
//   [ ] 0x5a7df0  UpdateCKCommonBaseGroup
//   [ ] 0x5a7df8  CKCommonBaseGroup_vfB8
//   [ ] 0x5a7e00  CKCommonBaseGroup_Construct_2  [dead]
//   [ ] 0x5a7e60  CKCommonBaseGroup_PostLoad
//   [ ] 0x5a7e88  RegisterCKCommonBaseGroupClass
//   [ ] 0x5a7f00  _GLOBAL__I_5a7f00
//   [ ] 0x5a7f10  CKCommonBaseGroup_DestroyArray
//   [x] 0x5a7fb0  CKCommonBaseGroup_CreateArray
//   [x] 0x5a8080  CKCommonBaseGroup_Create
//   [ ] 0x5a80f8  CKCommonBaseGroup_LevelReset
//   [x] 0x5a8120  CKCommonBaseGroup_Load
//   [ ] 0x5a8148  CKCommonBaseGroup_Save
//   [ ] 0x5a8170  CKCommonBaseGroup_ClearReferences
//   [ ] 0x5a81d0  CKCommonBaseGroup_Destructor
//   [ ] 0x5a81f0  CKCommonBaseGroup_DeletingDestructor
//   [ ] 0x5a8240  CKCommonBaseGroup_Destructor_2  [dead]
//
//   [x] 0x9cbbb8  CKCommonBaseGroup_GetClassGroup  [inline]
//   [x] 0x9cbbc0  CKCommonBaseGroup_GetClassId  [inline]
//   [ ] 0x9cbbc8  CKCommonBaseGroup_vfCC  [inline]
//   [ ] 0x9cbbd0  CKCommonBaseGroup_IsKindOf  [inline]
//   [ ] 0x9cbc28  KBase1744_vf8  [inline]
//   [ ] 0x9cbc80  KBase1744_vf14  [inline]
//   [ ] 0x9cbc88  KBase1744_vf18  [inline]
//   [ ] 0x9cbc90  KBase1744_vfCC  [inline]
#include "k2000/ui/CKCommonBaseGroup.h"

// 0x005a8120 CKCommonBaseGroup_Load: GroupBasicLoad only (through its TOC bridge).
int32_t CKCommonBaseGroup::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}
