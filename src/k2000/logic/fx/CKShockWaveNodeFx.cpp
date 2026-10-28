// CKShockWaveNodeFx.cpp - reconstructed original translation unit 0x1d22e8-0x1d3568 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKShockWaveNodeFx  key 0x30cc  category Logic  size 0x58  vtable 0xb1d808
// Other owners: FxAttachment (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d22e8  CKShockWaveNodeFx_Delete
//   [ ] 0x1d2338  CKShockWaveNodeFx_PostLoad
//   [ ] 0x1d2388  RegisterCKShockWaveNodeFxClass
//   [ ] 0x1d2400  _GLOBAL__I_1d2400
//   [ ] 0x1d2410  FxAttachment_SetPositionIfOwner_maybe
//   [x] 0x1d24b0  CKShockWaveNodeFx_Load
//   [ ] 0x1d24d8  CKShockWaveNodeFx_Save
//   [ ] 0x1d2500  CKShockWaveNodeFx_RecursiveRegistration
//   [ ] 0x1d2580  CKShockWaveNodeFx_Destroy
//   [x] 0x1d25a8  CKShockWaveNodeFx_DeleteArray
//   [x] 0x1d2648  CKShockWaveNodeFx_Create
//   [ ] 0x1d26a0  CKShockWaveNodeFx_SetDamageFlags
//   [ ] 0x1d26c8  CKShockWaveNodeFx_SetDamageType
//   [ ] 0x1d26f0  CKShockWaveNodeFx_SetDamageOwner
//   [ ] 0x1d2718  CKShockWaveNodeFx_Start
//   [ ] 0x1d2770  CKShockWaveNodeFx_Stop
//   [x] 0x1d2878  CKShockWaveNodeFx_CreateArray
//   [ ] 0x1d2928  CKShockWaveNodeFx_Trigger
//   [ ] 0x1d2cc8  CKShockWaveNodeFx_Trigger
//   [ ] 0x1d2cd0  CKShockWaveNodeFx_SetPosition
//   [ ] 0x1d2d70  CKShockWaveNodeFx_Update
//   [ ] 0x1d3340  CKShockWaveNodeFx_SetDirection_maybe
//
//   [ ] 0x9ad220  CKShockWaveNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad258  CKShockWaveNodeFx_GetClassType  [inline]
//   [x] 0x9ad260  CKShockWaveNodeFx_GetClassID  [inline]
//   [ ] 0x9ad268  CKShockWaveNodeFx_GetFxData  [inline]
//   [ ] 0x9ad270  CKShockWaveNodeFx_SetFxData  [inline]
//   [ ] 0x9ad278  CKShockWaveNodeFx_Destruct  [inline]
//   [ ] 0x9ad298  CKShockWaveNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKShockWaveNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x001d24b0 CKShockWaveNodeFx_Load
int32_t CKShockWaveNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}
