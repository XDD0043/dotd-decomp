// CKSekensLauncherCpnt.cpp - reconstructed original translation unit 0x1f7618-0x1f7ff0 (GAME_TOC1, main_toc1), 28 functions, 25 live.
// Primary class: CKSekensLauncherCpnt  key 0xd46  category Component  size 0x10  vtable 0xb1ead8
// Other owners: CKSrvSekensor (1), SekensList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f7618  CKSekensLauncherCpnt_Delete
//   [ ] 0x1f7668  CKSekensLauncherCpnt_Construct  [dead]
//   [ ] 0x1f7688  CKSekensLauncherCpnt_Construct_2  [dead]
//   [ ] 0x1f76a8  RegisterCKSekensLauncherCpntClass
//   [ ] 0x1f7720  _GLOBAL__I_1f7720
//   [ ] 0x1f7730  CKSekensLauncherCpnt_PlaySekens_maybe
//   [ ] 0x1f77b0  CKSekensLauncherCpnt_Destructor
//   [x] 0x1f7808  CKSekensLauncherCpnt_DeleteArray
//   [ ] 0x1f78a8  CKSekensLauncherCpnt_HasSekens
//   [ ] 0x1f78d8  CKSrvSekensor_IsSekensLineFinished_maybe
//   [ ] 0x1f7928  CKSekensLauncherCpnt_GetSekensLineCount_maybe  [dead]
//   [ ] 0x1f7958  CKSekensLauncherCpnt_IsSekensPlaying_maybe
//   [ ] 0x1f79b0  SekensList_IsEntryDone_maybe
//   [ ] 0x1f7a00  CKSekensLauncherCpnt_GetSekens
//   [ ] 0x1f7a18  CKSekensLauncherCpnt_StopSekens_maybe
//   [ ] 0x1f7aa8  CKSekensLauncherCpnt_GetCurrentLineIndex_maybe
//   [ ] 0x1f7b20  CKSekensLauncherCpnt_IsSekensPending_maybe
//   [ ] 0x1f7b98  CKSekensLauncherCpnt_IsSekensCurrent
//   [x] 0x1f7c10  CKSekensLauncherCpnt_Create
//   [x] 0x1f7c60  CKSekensLauncherCpnt_CreateArray
//   [x] 0x1f7d20  CKSekensLauncherCpnt_Load
//   [ ] 0x1f7ec8  CKSekensLauncherCpnt_MessageProc
//   [ ] 0x1f7ed0  CKSekensLauncherCpnt_Save
//   [ ] 0x1f7ed8  CKSekensLauncherCpnt_PostLoad
//   [ ] 0x1f7ee0  CKSekensLauncherCpnt_RecursiveRegistration
//   [ ] 0x1f7ee8  CKSekensLauncherCpnt_Destroy
//   [ ] 0x1f7f38  CKSekensLauncherCpnt_Destructor_2
//   [ ] 0x1f7f90  CKSekensLauncherCpnt_DeletingDestructor
//
//   [ ] 0x9b0e88  CKSekensLauncherCpnt_IsKindOfClass  [inline]
//   [x] 0x9b0eb0  CKSekensLauncherCpnt_GetClassType  [inline]
//   [x] 0x9b0eb8  CKSekensLauncherCpnt_GetClassID  [inline]
#include "k2000/components/CKSekensLauncherCpnt.h"

#include "k2000/components/TVectorLoad.h"

// 0x001f7d20 CKSekensLauncherCpnt_Load
int32_t CKSekensLauncherCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) TVector_LoadRefs(m_vSekens, file);
    return 1;
}
