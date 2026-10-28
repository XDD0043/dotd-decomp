// CKDistortionNodeFx.cpp - reconstructed original translation unit 0x1af060-0x1af710 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKDistortionNodeFx  key 0x38cc  category Logic  size 0x2c  vtable 0xb1c6a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1af060  CKDistortionNodeFx_Delete
//   [ ] 0x1af0b0  CKDistortionNodeFx_Destroy
//   [ ] 0x1af0b8  CKDistortionNodeFx_RecursiveRegistration
//   [ ] 0x1af110  CKDistortionNodeFx_PostLoad
//   [ ] 0x1af118  CKDistortionNodeFx_Update
//   [ ] 0x1af1c0  RegisterCKDistortionNodeFxClass
//   [ ] 0x1af238  _GLOBAL__I_1af238
//   [x] 0x1af248  CKDistortionNodeFx_Load
//   [ ] 0x1af270  CKDistortionNodeFx_Save
//   [x] 0x1af298  CKDistortionNodeFx_DeleteArray
//   [x] 0x1af338  CKDistortionNodeFx_Create
//   [ ] 0x1af390  CKDistortionNodeFx_Start
//   [ ] 0x1af410  CKDistortionNodeFx_SetCenterForOwner_maybe
//   [ ] 0x1af4c0  FUN_001af4c0  [dead]
//   [ ] 0x1af558  CKDistortionNodeFx_Stop
//   [x] 0x1af660  CKDistortionNodeFx_CreateArray
//
//   [ ] 0x9ab528  CKDistortionNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ab560  CKDistortionNodeFx_GetClassType  [inline]
//   [x] 0x9ab568  CKDistortionNodeFx_GetClassID  [inline]
//   [ ] 0x9ab570  CKDistortionNodeFx_GetFxData  [inline]
//   [ ] 0x9ab578  CKDistortionNodeFx_SetFxData  [inline]
//   [ ] 0x9ab660  CKDistortionNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9ab6a8  CKDistortionNodeFx_Destruct  [inline]
#include "k2000/logic/fx/CKDistortionNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x001af248 CKDistortionNodeFx_Load
int32_t CKDistortionNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}
