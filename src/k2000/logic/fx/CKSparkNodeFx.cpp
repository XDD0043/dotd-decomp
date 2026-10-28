// CKSparkNodeFx.cpp - reconstructed original translation unit 0x1d3e68-0x1d4890 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKSparkNodeFx  key 0x244c  category Logic  size 0x1c  vtable 0xb1d970
// Other owners: StopOwnedSparkEffect (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d3e68  CKSparkNodeFx_Delete
//   [ ] 0x1d3eb8  CKSparkNodeFx_ExtraSlot9C
//   [ ] 0x1d3f80  KStub_Nop_1d3f80
//   [ ] 0x1d3f88  CKSparkNodeFx_SetParamVec2_40_maybe
//   [ ] 0x1d3fa8  FUN_001d3fa8  [dead]
//   [ ] 0x1d3fd8  CKSparkNodeFx_SetParamVec2_50_maybe
//   [ ] 0x1d3ff8  FUN_001d3ff8  [dead]
//   [ ] 0x1d4028  CKSparkNodeFx_SetParamFloat_68_maybe
//   [ ] 0x1d4038  FUN_001d4038  [dead]
//   [ ] 0x1d4048  CKSparkNodeFx_SetParamVec3_10_maybe
//   [ ] 0x1d4078  FUN_001d4078  [dead]
//   [ ] 0x1d40b0  CKSparkNodeFx_SetParamVec3_1c_maybe
//   [ ] 0x1d40e0  FUN_001d40e0  [dead]
//   [ ] 0x1d4118  RegisterCKSparkNodeFxClass
//   [ ] 0x1d4190  _GLOBAL__I_1d4190
//   [ ] 0x1d41a0  CKSparkNodeFx_Stop
//   [ ] 0x1d4260  CKSparkNodeFx_Start
//   [ ] 0x1d44a0  CKSparkNodeFx_PostLoad
//   [x] 0x1d44c8  CKSparkNodeFx_Load
//   [ ] 0x1d4520  CKSparkNodeFx_Save
//   [ ] 0x1d4548  CKSparkNodeFx_RecursiveRegistration
//   [ ] 0x1d4570  CKSparkNodeFx_Destroy
//   [x] 0x1d4598  CKSparkNodeFx_DeleteArray
//   [x] 0x1d4640  CKSparkNodeFx_Create
//   [ ] 0x1d4698  StopOwnedSparkEffect_maybe
//   [ ] 0x1d46c8  CKSparkNodeFx_ExtraSlotA0
//   [ ] 0x1d4788  CKSparkNodeFx_Update
//   [x] 0x1d47d8  CKSparkNodeFx_CreateArray
//
//   [ ] 0x9ad3f0  CKSparkNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad428  CKSparkNodeFx_GetClassType  [inline]
//   [x] 0x9ad430  CKSparkNodeFx_GetClassID  [inline]
//   [ ] 0x9ad438  CKSparkNodeFx_GetFxData  [inline]
//   [ ] 0x9ad440  CKSparkNodeFx_SetFxData  [inline]
//   [ ] 0x9ad448  CKSparkNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9ad490  CKSparkNodeFx_Destruct  [inline]
#include "k2000/logic/fx/CKSparkNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x001d44c8 CKSparkNodeFx_Load
int32_t CKSparkNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) m_pSparkNode = m_pNode;
    return 1;
}
