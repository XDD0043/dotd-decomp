// CKFlashNode2dFx.cpp - reconstructed original translation unit 0x1bc520-0x1be2a0 (GAME_TOC1, main_toc1), 21 functions, 17 live.
// Primary class: CKFlashNode2dFx  key 0x15cc  category Logic  size 0x7c  vtable 0xb1cd68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1bc520  CKFlashNode2dFx_Delete
//   [ ] 0x1bc570  CKFlashNode2dFx_Destroy
//   [ ] 0x1bc578  FUN_001bc578  [dead]
//   [ ] 0x1bc610  FUN_001bc610  [dead]
//   [ ] 0x1bc638  CKFlashNode2dFx_Stop
//   [ ] 0x1bc6d8  CKFlashNode2dFx_PostLoad
//   [ ] 0x1bc728  RegisterCKFlashNode2dFxClass
//   [ ] 0x1bc7a0  _GLOBAL__I_1bc7a0
//   [ ] 0x1bc7b0  FUN_001bc7b0  [dead]
//   [ ] 0x1bc8b0  CKFlashNode2dFx_MoveTowardTarget_maybe  [dead]
//   [x] 0x1bca10  CKFlashNode2dFx_Load
//   [ ] 0x1bca38  CKFlashNode2dFx_Save
//   [ ] 0x1bca60  CKFlashNode2dFx_RecursiveRegistration
//   [x] 0x1bcae0  CKFlashNode2dFx_DeleteArray
//   [x] 0x1bcb88  CKFlashNode2dFx_Create
//   [x] 0x1bcbf0  CKFlashNode2dFx_CreateArray
//   [ ] 0x1bccc8  CKFlashNode2dFx_Start
//   [ ] 0x1bcf30  CKFlashNode2dFx_State0
//   [ ] 0x1bd4a0  CKFlashNode2dFx_State2
//   [ ] 0x1bda30  CKFlashNode2dFx_State1
//   [ ] 0x1bdd68  CKFlashNode2dFx_Update
//
//   [ ] 0x9ac278  CKFlashNode2dFx_IsKindOfClass  [inline]
//   [x] 0x9ac2b0  CKFlashNode2dFx_GetClassType  [inline]
//   [x] 0x9ac2b8  CKFlashNode2dFx_GetClassID  [inline]
//   [ ] 0x9ac2c0  CKFlashNode2dFx_GetFxData  [inline]
//   [ ] 0x9ac2c8  CKFlashNode2dFx_SetFxData  [inline]
//   [ ] 0x9ac2d0  CKFlashNode2dFx_DeletingDestruct  [inline]
//   [ ] 0x9ac318  CKFlashNode2dFx_Destruct  [inline]
#include "k2000/logic/fx/CKFlashNode2dFx.h"

// Inlined in 0x001bcb88 CKFlashNode2dFx_Create (+0x61 is stored first).
CKFlashNode2dFx::CKFlashNode2dFx() {
    m_unk61 = 0xff;
    m_unk60 = 0xff;
}

// 0x001bca10 CKFlashNode2dFx_Load
int32_t CKFlashNode2dFx::Load(IKFile* file, int32_t type) {
    IKNode2dFx::Load(file, type);
    return 1;
}
