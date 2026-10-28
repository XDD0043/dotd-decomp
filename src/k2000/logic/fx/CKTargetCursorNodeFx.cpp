// CKTargetCursorNodeFx.cpp - reconstructed original translation unit 0x1d57b8-0x1d7298 (GAME_TOC1, main_toc1), 23 functions, 18 live.
// Primary class: CKTargetCursorNodeFx  key 0x460c  category Logic  size 0x38  vtable 0xb1da88
// Other owners: StopOwnedEffectWithFadeOut (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d57b8  CKTargetCursorNodeFx_Delete
//   [ ] 0x1d5808  CKTargetCursorNodeFx_RecursiveRegistration
//   [ ] 0x1d5860  FUN_001d5860  [dead]
//   [ ] 0x1d58e0  FUN_001d58e0  [dead]
//   [ ] 0x1d5988  CKTargetCursorNodeFx_StopForOwner_maybe
//   [ ] 0x1d5a50  CKTargetCursorNodeFx_SetAlpha_maybe  [dead]
//   [ ] 0x1d5bc0  RegisterCKTargetCursorNodeFxClass
//   [ ] 0x1d5c38  _GLOBAL__I_1d5c38
//   [x] 0x1d5c48  CKTargetCursorNodeFx_PostLoad
//   [x] 0x1d5ca0  CKTargetCursorNodeFx_Load
//   [ ] 0x1d5d60  CKTargetCursorNodeFx_Save
//   [ ] 0x1d5d88  CKTargetCursorNodeFx_Destroy
//   [x] 0x1d5dc8  CKTargetCursorNodeFx_DeleteArray
//   [x] 0x1d5e70  CKTargetCursorNodeFx_Create
//   [ ] 0x1d5ec8  CKTargetCursorNodeFx_SetPositionForOwner_maybe
//   [ ] 0x1d5fa0  CKTargetCursorNodeFx_Stop
//   [ ] 0x1d5fe0  FUN_001d5fe0  [dead]
//   [ ] 0x1d6020  FUN_001d6020  [dead]
//   [x] 0x1d60f0  CKTargetCursorNodeFx_CreateArray
//   [ ] 0x1d61a8  CKTargetCursorNodeFx_SetupCursorStateForOwner_maybe
//   [ ] 0x1d63d8  CKTargetCursorNodeFx_Start
//   [ ] 0x1d6640  CKTargetCursorNodeFx_Update
//   [ ] 0x1d7190  StopOwnedEffectWithFadeOut_maybe
//
//   [ ] 0x9ad590  CKTargetCursorNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad5c8  CKTargetCursorNodeFx_GetClassType  [inline]
//   [x] 0x9ad5d0  CKTargetCursorNodeFx_GetClassID  [inline]
//   [ ] 0x9ad5d8  CKTargetCursorNodeFx_GetFxData  [inline]
//   [ ] 0x9ad5e0  CKTargetCursorNodeFx_SetFxData  [inline]
//   [ ] 0x9ad5e8  CKTargetCursorNodeFx_Destruct  [inline]
//   [ ] 0x9ad608  CKTargetCursorNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKTargetCursorNodeFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"

// 0x001d5ca0 CKTargetCursorNodeFx_Load
int32_t CKTargetCursorNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pCursorNode);
    return 1;
}

// 0x001d5c48 CKTargetCursorNodeFx_PostLoad: IKNodeFx_PostLoad, then for the level type a matrix (RwMatrixCreate_Thunk).
int32_t CKTargetCursorNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) m_pMatrix1c = RwMatrixCreate_Thunk();
    return 1;
}
