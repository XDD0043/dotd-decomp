// CKHkS08Shield.cpp - reconstructed original translation unit 0x2ac320-0x2acb08 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKHkS08Shield  key 0x2f82  category Hook  size 0x24  vtable 0xb222c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2ac320  CKHkS08Shield_Delete
//   [ ] 0x2ac370  CKHkS08Shield_Destroy
//   [ ] 0x2ac378  CKHkS08Shield_Start
//   [ ] 0x2ac380  CKHkS08Shield_Pause
//   [ ] 0x2ac388  CKHkS08Shield_Resume
//   [ ] 0x2ac390  CKHkS08Shield_Update
//   [ ] 0x2ac398  CKHkS08Shield_vfC0
//   [ ] 0x2ac3a0  CKHkS08Shield_vfCC
//   [ ] 0x2ac3a8  CKHkS08Shield_PostLoad
//   [x] 0x2ac400  CKHkS08Shield_Load
//   [ ] 0x2ac488  CKHkS08Shield_Save
//   [ ] 0x2ac508  CKHkS08Shield_RecursiveRegistration
//   [x] 0x2ac530  CKHkS08Shield_DeleteArray
//   [x] 0x2ac5d8  CKHkS08Shield_Create
//   [ ] 0x2ac640  RegisterCKHkS08ShieldClass
//   [ ] 0x2ac6c8  _GLOBAL__D_2ac6c8
//   [ ] 0x2ac6d8  _GLOBAL__I_2ac6d8
//   [ ] 0x2ac6e8  CKHkS08Shield_TakeFromPool_maybe
//   [ ] 0x2ac840  CKHkS08Shield_Stop
//   [ ] 0x2ac900  CKHkS08Shield_ReturnToPool_maybe
//   [x] 0x2aca30  CKHkS08Shield_CreateArray
//   [ ] 0x2acb00  CKHkS08Shield_MessageProc
//
//   [ ] 0x9bc9a8  CKHkS08Shield_IsKindOfClass  [inline]
//   [ ] 0x9bc9f0  CKHkS08Shield_GetClassType  [inline]
//   [ ] 0x9bc9f8  CKHkS08Shield_GetClassID  [inline]
//   [ ] 0x9bca00  CKHkS08Shield_Destructor  [inline]
//   [ ] 0x9bca20  CKHkS08Shield_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08Shield.h"

#include "k2000/io/IKFile.h"

// 0x002ac400 CKHkS08Shield_Load: IKHook's part, then one word whatever the type.
int32_t CKHkS08Shield::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    ReadU32LE(file, &m_unk20);
    return 1;
}
