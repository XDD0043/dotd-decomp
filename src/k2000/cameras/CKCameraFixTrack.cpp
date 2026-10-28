// CKCameraFixTrack.cpp - reconstructed original translation unit 0x13c110-0x13c700 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCameraFixTrack  key 0x187  category Camera  size 0x60  vtable 0xb1a138
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13c110  CKCameraFixTrack_Delete
//   [ ] 0x13c160  CKCameraFixTrack_vf54
//   [ ] 0x13c168  CKCameraFixTrack_vf5C
//   [ ] 0x13c170  RegisterCKCameraFixTrackClass
//   [ ] 0x13c1e8  _GLOBAL__I_13c1e8
//   [ ] 0x13c1f8  CKCameraFixTrack_Deactivate_maybe
//   [ ] 0x13c220  CKCameraFixTrack_RecursiveRegistration
//   [ ] 0x13c248  CKCameraFixTrack_Destroy
//   [x] 0x13c270  CKCameraFixTrack_DeleteArray
//   [x] 0x13c318  CKCameraFixTrack_Create
//   [ ] 0x13c370  CKCameraFixTrack_Activate_maybe
//   [ ] 0x13c3f0  CKCameraFixTrack_Update
//   [x] 0x13c470  CKCameraFixTrack_CreateArray
//   [x] 0x13c528  CKCameraFixTrack_Load
//   [ ] 0x13c618  CKCameraFixTrack_Save
//
//   [ ] 0x9a7470  CKCameraFixTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7498  CKCameraFixTrack_GetClassType  [inline]
//   [ ] 0x9a74a0  CKCameraFixTrack_GetClassID  [inline]
//   [ ] 0x9a74a8  CKCameraFixTrack_vf84  [inline]
//   [ ] 0x9a74b0  CKCameraFixTrack_DeletingDestructor  [inline]
//   [ ] 0x9a74f8  CKCameraFixTrack_Destructor  [inline]
#include "k2000/cameras/CKCameraFixTrack.h"

#include "k2000/io/IKFile.h"

// 0x0013c528 CKCameraFixTrack_Load
int32_t CKCameraFixTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fTargetHighOffset);
        ReadF32LE(file, &m_fRollAngle);
    }
    return 1;
}
