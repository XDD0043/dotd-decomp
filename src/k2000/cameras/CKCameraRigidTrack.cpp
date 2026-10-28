// CKCameraRigidTrack.cpp - reconstructed original translation unit 0x13a330-0x13add0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCameraRigidTrack  key 0x87  category Camera  size 0x6c  vtable 0xb19fb8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13a330  CKCameraRigidTrack_Delete
//   [ ] 0x13a380  CKCameraRigidTrack_vf54
//   [ ] 0x13a388  CKCameraRigidTrack_vf5C
//   [ ] 0x13a390  RegisterCKCameraRigidTrackClass
//   [ ] 0x13a408  _GLOBAL__I_13a408
//   [ ] 0x13a418  CKCameraRigidTrack_RecursiveRegistration
//   [ ] 0x13a440  CKCameraRigidTrack_Deactivate_maybe
//   [ ] 0x13a468  CKCameraRigidTrack_Destroy
//   [x] 0x13a490  CKCameraRigidTrack_DeleteArray
//   [x] 0x13a530  CKCameraRigidTrack_Create
//   [ ] 0x13a588  CKCameraRigidTrack_Activate_maybe
//   [x] 0x13a778  CKCameraRigidTrack_CreateArray
//   [x] 0x13a828  CKCameraRigidTrack_Load
//   [ ] 0x13a990  CKCameraRigidTrack_Update_maybe
//   [ ] 0x13ac18  CKCameraRigidTrack_Save
//
//   [ ] 0x9a71f8  CKCameraRigidTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7220  CKCameraRigidTrack_GetClassType  [inline]
//   [ ] 0x9a7228  CKCameraRigidTrack_GetClassID  [inline]
//   [ ] 0x9a7230  CKCameraRigidTrack_vfB4  [inline]
//   [ ] 0x9a7238  CKCameraRigidTrack_vf80  [inline]
//   [ ] 0x9a7240  CKCameraRigidTrack_DeletingDestructor  [inline]
//   [ ] 0x9a7288  CKCameraRigidTrack_Destructor  [inline]
#include "k2000/cameras/CKCameraRigidTrack.h"

#include "k2000/io/IKFile.h"

// 0x0013a828 CKCameraRigidTrack_Load
int32_t CKCameraRigidTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_offsetPosition), 3);  // one 0xc read, swapped
        ReadF32LE(file, &m_unk64);
        ReadF32LE(file, &m_unk68);
    }
    return 1;
}
