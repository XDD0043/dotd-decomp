// CKInputIconNodeFx.cpp - reconstructed original translation unit 0x1c4480-0x1c5f28 (GAME_TOC1, main_toc1), 28 functions, 26 live.
// Primary class: CKInputIconNodeFx  key 0x458c  category Logic  size 0x3c  vtable 0xb1d098
// Other owners: InputIconFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c4480  CKInputIconNodeFx_Delete
//   [ ] 0x1c44d0  CKInputIconNodeFx_StopIfLinkedTo
//   [ ] 0x1c4588  CKInputIconNodeFx_OnPause
//   [ ] 0x1c45c8  CKInputIconNodeFx_SetPosition_maybe
//   [ ] 0x1c4620  RegisterCKInputIconNodeFxClass
//   [ ] 0x1c46a8  _GLOBAL__D_1c46a8
//   [ ] 0x1c46b8  _GLOBAL__I_1c46b8
//   [ ] 0x1c46c8  CKInputIconNodeFx_ApplyDisplayMode_maybe
//   [ ] 0x1c4968  CKInputIconNodeFx_Stop
//   [ ] 0x1c49e8  CKInputIconNodeFx_PostLoad
//   [x] 0x1c4a10  CKInputIconNodeFx_Load
//   [ ] 0x1c4a38  CKInputIconNodeFx_Save
//   [ ] 0x1c4a60  CKInputIconNodeFx_RecursiveRegistration
//   [ ] 0x1c4a88  CKInputIconNodeFx_Destroy
//   [ ] 0x1c4ab0  CKInputIconNodeFx_Construct
//   [ ] 0x1c4af0  CKInputIconNodeFx_Construct_2
//   [x] 0x1c4b30  CKInputIconNodeFx_DeleteArray
//   [ ] 0x1c4bd8  InputIconFx_UpdateWorldPosition_maybe
//   [ ] 0x1c4ca0  FUN_001c4ca0  [dead]
//   [ ] 0x1c4d30  CKInputIconNodeFx_UpdatePlacement_maybe
//   [ ] 0x1c5558  CKInputIconNodeFx_Update
//   [ ] 0x1c5a88  CKInputIconNodeFx_Start
//   [x] 0x1c5c80  CKInputIconNodeFx_CreateArray
//   [x] 0x1c5d48  CKInputIconNodeFx_Create
//   [ ] 0x1c5da8  CKInputIconNodeFx_SetAlpha_maybe
//   [ ] 0x1c5ea0  CKInputIconNodeFx_Destruct_2  [dead]
//   [ ] 0x1c5ec0  CKInputIconNodeFx_Destruct
//   [ ] 0x1c5ee0  CKInputIconNodeFx_DeletingDestruct
//
//   [ ] 0x9ac750  CKInputIconNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ac788  CKInputIconNodeFx_GetClassType  [inline]
//   [x] 0x9ac790  CKInputIconNodeFx_GetClassID  [inline]
//   [ ] 0x9ac798  CKInputIconNodeFx_GetFxData  [inline]
//   [ ] 0x9ac7a0  CKInputIconNodeFx_SetFxData  [inline]
#include "k2000/logic/fx/CKInputIconNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x001c4a10 CKInputIconNodeFx_Load
int32_t CKInputIconNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}
