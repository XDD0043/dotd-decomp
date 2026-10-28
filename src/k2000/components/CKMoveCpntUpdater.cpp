// CKMoveCpntUpdater.cpp - reconstructed original translation unit 0x24d2a8-0x24df08 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKMoveCpntUpdater  key 0x12c6  category Component  size 0x10  vtable 0xb20ea0
// Other owners: CKMoveCpnt (1), CKHkMovingObject (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x24d2a8  CKMoveCpntUpdater_GetMoveCpnt
//   [ ] 0x24d2b0  RegisterCKMoveCpntUpdaterClass
//   [ ] 0x24d328  _GLOBAL__I_24d328
//   [ ] 0x24d338  CKMoveCpnt_ApplySampleToMatrix_maybe
//   [ ] 0x24d9c0  CKMoveCpntUpdater_ApplyToNode
//   [ ] 0x24dad0  CKHkMovingObject_SampleMoveCpnt_maybe
//   [ ] 0x24db60  CKMoveCpntUpdater_Evaluate
//   [ ] 0x24dbf0  CKMoveCpntUpdater_Resume
//   [ ] 0x24dc28  CKMoveCpntUpdater_Pause
//   [ ] 0x24dc60  CKMoveCpntUpdater_Stop
//   [ ] 0x24dc98  CKMoveCpntUpdater_Start
//   [x] 0x24dcd0  CKMoveCpntUpdater_DeleteArray
//   [x] 0x24dd70  CKMoveCpntUpdater_Create
//   [ ] 0x24dda8  CKMoveCpntUpdater_SetMoveCpnt
//   [x] 0x24ddb0  CKMoveCpntUpdater_CreateArray
//   [ ] 0x24de40  CKMoveCpntUpdater_Save
//   [x] 0x24de48  CKMoveCpntUpdater_Load
//   [ ] 0x24ded8  CKMoveCpntUpdater_PostLoad
//   [ ] 0x24def8  CKMoveCpntUpdater_RecursiveRegistration
//   [ ] 0x24df00  CKMoveCpntUpdater_Destroy
//
//   [ ] 0x9ba0f8  CKMoveCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9ba120  CKMoveCpntUpdater_GetClassType  [inline]
//   [x] 0x9ba128  CKMoveCpntUpdater_GetClassID  [inline]
//   [ ] 0x9ba130  CKMoveCpntUpdater_DeletingDestructor  [inline]
//   [ ] 0x9ba178  CKMoveCpntUpdater_Destructor  [inline]
#include "k2000/components/CKMoveCpntUpdater.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKMoveCpnt.h"

// 0x0024de48 CKMoveCpntUpdater_Load
int32_t CKMoveCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pMoveCpnt);
    return 1;
}
