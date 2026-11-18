// CKEnemyCpnt.cpp - reconstructed original translation unit 0x2b2d08-0x2b30b8 (GAME_TOC1, main_toc1), 10 functions, 10 live.
// Primary class: CKEnemyCpnt  key 0x186  category Component  size 0xb8  vtable 0xb224d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b2d08  CKEnemyCpnt_Delete
//   [x] 0x2b2d58  CKEnemyCpnt_Destroy  (empty, the default)
//   [x] 0x2b2d60  CKEnemyCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [ ] 0x2b2d68  RegisterCKEnemyCpntClass
//   [ ] 0x2b2de0  _GLOBAL__I_2b2de0
//   [x] 0x2b2df0  CKEnemyCpnt_DeleteArray
//   [x] 0x2b2e90  CKEnemyCpnt_Create
//   [x] 0x2b2ee8  CKEnemyCpnt_CreateArray
//   [x] 0x2b2fb0  CKEnemyCpnt_Load
//   [ ] 0x2b30b0  CKEnemyCpnt_Save
//
//   [ ] 0x9bcb60  CKEnemyCpnt_IsKindOfClass  [inline]
//   [ ] 0x9bcb88  CKEnemyCpnt_GetClassType  [inline]
//   [ ] 0x9bcb90  CKEnemyCpnt_GetClassID  [inline]
//   [ ] 0x9bcb98  CKEnemyCpnt_DeletingDestructor  [inline]
//   [ ] 0x9bcbf8  CKEnemyCpnt_Destructor  [inline]
#include "k2000/components/CKEnemyCpnt.h"

#include "k2000/io/IKFile.h"

// 0x002b2fb0 CKEnemyCpnt_Load
int32_t CKEnemyCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_baOptionFlags);
        m_MoveCpnt.Load(file, K_LEVEL_PLATEFORMS);  // a direct call (bl 0x2bcc98), not through the vtable
    }
    ReadU32LE(file, &m_unkb4);
    return 1;
}
