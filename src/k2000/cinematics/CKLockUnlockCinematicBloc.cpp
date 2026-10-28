// CKLockUnlockCinematicBloc.cpp - reconstructed original translation unit 0x17e7f0-0x17f458 (GAME_TOC1, main_toc1), 20 functions, 19 live.
// Primary class: CKLockUnlockCinematicBloc  key 0x908  category CinematicNode  size 0x38  vtable 0xb1b4e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x17e7f0  CKLockUnlockCinematicBloc_Delete
//   [ ] 0x17e840  CKLockUnlockCinematicBloc_Abort
//   [ ] 0x17e850  RegisterCKLockUnlockCinematicBlocClass
//   [ ] 0x17e8c8  _GLOBAL__I_17e8c8
//   [ ] 0x17e8d8  CKLockUnlockCinematicBloc_Complete
//   [x] 0x17eab0  CKLockUnlockCinematicBloc_Load
//   [ ] 0x17ead8  CKLockUnlockCinematicBloc_Save
//   [ ] 0x17eb00  CKLockUnlockCinematicBloc_RecursiveRegistration
//   [x] 0x17eb28  CKLockUnlockCinematicBloc_Construct
//   [ ] 0x17eb60  CKLockUnlockCinematicBloc_Construct_2
//   [x] 0x17eb98  CKLockUnlockCinematicBloc_DeleteArray
//   [ ] 0x17ec40  CKLockUnlockCinematicBloc_Update
//   [ ] 0x17ee40  CKLockUnlockCinematicBloc_Destroy
//   [ ] 0x17ee48  CKLockUnlockCinematicBloc_Start
//   [x] 0x17f0e0  CKLockUnlockCinematicBloc_Create
//   [x] 0x17f138  CKLockUnlockCinematicBloc_CreateArray
//   [ ] 0x17f1f0  CKLockUnlockCinematicBloc_DeletingDestructor
//   [ ] 0x17f238  CKLockUnlockCinematicBloc_Stop
//   [ ] 0x17f418  CKLockUnlockCinematicBloc_Destructor_2  [dead]
//   [ ] 0x17f438  CKLockUnlockCinematicBloc_Destructor
//
//   [ ] 0x9a9988  CKLockUnlockCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a99c0  CKLockUnlockCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a99c8  CKLockUnlockCinematicBloc_GetClassID  [inline]
#include "k2000/cinematics/CKLockUnlockCinematicBloc.h"

// 0x0017eab0 CKLockUnlockCinematicBloc_Load
int32_t CKLockUnlockCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    return 1;
}
