// CKCameraEventCpnt.cpp - reconstructed original translation unit 0x165a08-0x166328 (GAME_TOC1, main_toc1), 22 functions, 20 live.
// Primary class: CKCameraEventCpnt  key 0x1246  category Component  size 0x18  vtable 0xb1ab10
// Other owners: ScriptedCameraHandle (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x165a08  CKCameraEventCpnt_Delete
//   [ ] 0x165a58  CKCameraEventCpnt_Construct  [dead]
//   [ ] 0x165a68  CKCameraEventCpnt_Construct_2  [dead]
//   [ ] 0x165a78  ScriptedCameraHandle_SetPositionAndTarget_maybe
//   [ ] 0x165af8  ScriptedCameraHandle_Reset_maybe
//   [ ] 0x165b50  RegisterCKCameraEventCpntClass
//   [ ] 0x165bc8  _GLOBAL__I_165bc8
//   [ ] 0x165bd8  ScriptedCameraHandle_Activate_maybe
//   [ ] 0x165d68  CKCameraEventCpnt_DeletingDestructor
//   [ ] 0x165db0  CKCameraEventCpnt_Destructor
//   [ ] 0x165de0  CKCameraEventCpnt_BaseDestructor
//   [x] 0x165e10  CKCameraEventCpnt_DeleteArray
//   [ ] 0x165eb8  ScriptedCameraHandle_TryActivate_maybe
//   [x] 0x166020  CKCameraEventCpnt_Create
//   [x] 0x166058  CKCameraEventCpnt_CreateArray
//   [ ] 0x1660f0  CKCameraEventCpnt_Save
//   [ ] 0x1660f8  CKCameraEventCpnt_MessageProc
//   [ ] 0x166100  CKCameraEventCpnt_RecursiveRegistration
//   [ ] 0x166108  CKCameraEventCpnt_PostLoad
//   [ ] 0x166128  CKCameraEventCpnt_Destroy
//   [ ] 0x166130  ScriptedCameraHandle_Release_maybe
//   [x] 0x166240  CKCameraEventCpnt_Load
//
//   [ ] 0x9a8bf8  CKCameraEventCpnt_IsKindOfClass  [inline]
//   [x] 0x9a8c20  CKCameraEventCpnt_GetClassType  [inline]
//   [x] 0x9a8c28  CKCameraEventCpnt_GetClassID  [inline]
#include "k2000/components/CKCameraEventCpnt.h"

#include "k2000/io/IKFile.h"

// 0x00166240 CKCameraEventCpnt_Load
int32_t CKCameraEventCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pCamera);
        ReadF32LE(file, &m_unk08);
    }
    return 1;
}
