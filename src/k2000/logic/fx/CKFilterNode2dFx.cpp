// CKFilterNode2dFx.cpp - reconstructed original translation unit 0x1b9358-0x1ba218 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKFilterNode2dFx  key 0x19cc  category Logic  size 0x3c  vtable 0xb1cb48
// Other owners: CKFireBallFxData (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1b9358  RegisterCKFilterNode2dFxClass
//   [ ] 0x1b93d0  _GLOBAL__I_1b93d0
//   [ ] 0x1b93e0  CKFilterNode2dFx_Stop
//   [x] 0x1b94a8  CKFilterNode2dFx_Load
//   [ ] 0x1b94d0  CKFilterNode2dFx_Save
//   [ ] 0x1b94f8  CKFilterNode2dFx_RecursiveRegistration
//   [x] 0x1b9578  CKFilterNode2dFx_DeleteArray
//   [x] 0x1b9620  CKFilterNode2dFx_Create
//   [ ] 0x1b9678  CKFilterNode2dFx_Update
//   [ ] 0x1b9a18  CKFilterNode2dFx_BeginFadeOut_maybe
//   [ ] 0x1b9ad0  CKFilterNode2dFx_Start
//   [x] 0x1b9d08  CKFilterNode2dFx_CreateArray
//   [ ] 0x1b9dc0  CKFireBallFxData_GetNodeClassKey
//   [ ] 0x1b9dc8  CKFireBallFxData_Destroy
//   [ ] 0x1b9dd0  CKFireBallFxData_PostLoad
//   [ ] 0x1b9df8  CKFireBallFxData_RecursiveRegistration
//   [ ] 0x1b9e20  CKFireBallFxData_Load
//   [ ] 0x1ba040  CKFireBallFxData_Save
//
//   [ ] 0x9abf38  CKFilterNode2dFx_IsKindOfClass  [inline]
//   [x] 0x9abf70  CKFilterNode2dFx_GetClassType  [inline]
//   [x] 0x9abf78  CKFilterNode2dFx_GetClassID  [inline]
//   [ ] 0x9abf80  CKFilterNode2dFx_GetFxData  [inline]
//   [ ] 0x9abf88  CKFilterNode2dFx_SetFxData  [inline]
//   [ ] 0x9abf90  CKFilterNode2dFx_DeletingDestruct  [inline]
//   [ ] 0x9abfd8  CKFilterNode2dFx_Destruct  [inline]
//   [ ] 0x9abff8  CKFireBallFxData_IsKindOfClass  [inline]
//   [ ] 0x9ac030  CKFireBallFxData_GetClassType  [inline]
//   [ ] 0x9ac038  CKFireBallFxData_GetClassID  [inline]
//   [ ] 0x9ac040  CKFireBallFxData_DeletingDestructor  [inline]
//   [ ] 0x9ac098  CKFireBallFxData_Destructor  [inline]
#include "k2000/logic/fx/CKFilterNode2dFx.h"

// 0x001b94a8 CKFilterNode2dFx_Load
int32_t CKFilterNode2dFx::Load(IKFile* file, int32_t type) {
    IKNode2dFx::Load(file, type);
    return 1;
}
