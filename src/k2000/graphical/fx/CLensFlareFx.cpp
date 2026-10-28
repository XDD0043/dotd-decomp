// CLensFlareFx.cpp - reconstructed original translation unit 0xb3170-0xb4808 (GAME_TOC1, main_toc1), 24 functions, 21 live.
// Primary class: CLensFlareFx  key 0x1b4d  category Graphical  size 0x30  vtable 0xb176f8
// Other owners: CLensFlareData (7), DrawLensFlareElements (2), RegisterCLensFlareFxAndDataClasses (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xb3170  FUN_000b3170  [dead]
//   [ ] 0xb32e0  CLensFlareFx_vf78
//   [ ] 0xb32e8  CLensFlareFx_SetEnabled
//   [ ] 0xb3308  CLensFlareFx_IsEnabled  [dead]
//   [ ] 0xb3318  FUN_000b3318  [dead]
//   [ ] 0xb3320  RegisterCLensFlareFxAndDataClasses
//   [ ] 0xb33d8  _GLOBAL__I_b33d8
//   [ ] 0xb33e8  CLensFlareData_DeleteArray
//   [x] 0xb3490  CLensFlareFx_DeleteArray
//   [ ] 0xb3538  CLensFlareData_Create
//   [x] 0xb3570  CLensFlareFx_Create
//   [ ] 0xb35c8  CLensFlareData_CreateArray
//   [x] 0xb3660  CLensFlareFx_CreateArray
//   [ ] 0xb3718  CLensFlareData_Save
//   [ ] 0xb3720  CLensFlareFx_RecursiveRegistration
//   [ ] 0xb3780  CLensFlareData_RecursiveRegistration
//   [ ] 0xb37e0  CLensFlareData_Destroy
//   [ ] 0xb3838  CLensFlareFx_Enqueue
//   [ ] 0xb3970  CLensFlareFx_PostLoad
//   [ ] 0xb39a0  CLensFlareFx_Destroy
//   [ ] 0xb39c8  DrawLensFlareElements
//   [ ] 0xb43b0  DrawLensFlareElements
//   [ ] 0xb43b8  CLensFlareFx_Draw
//   [ ] 0xb43d0  CLensFlareData_Load
//
//   [ ] 0x9a0aa8  CLensFlareData_GetClassType  [inline]
//   [ ] 0x9a0ab0  CLensFlareData_GetClassID  [inline]
//   [x] 0x9a0ab8  CLensFlareFx_GetClassType  [inline]
//   [x] 0x9a0ac0  CLensFlareFx_GetClassID  [inline]
//   [x] 0x9a0ac8  CLensFlareFx_GetSerializationFlags  [inline]
//   [ ] 0x9a0ad0  CLensFlareData_DeletingDestructor  [inline]
//   [ ] 0x9a0b18  CLensFlareData_Destructor  [inline]
//   [ ] 0x9a0b48  CLensFlareData_IsKindOfClass  [inline]
//   [x] 0x9a0b68  CLensFlareFx_IsKindOfClass  [inline]
//   [ ] 0x9a0ba0  CLensFlareFx_Save  [inline]
//   [x] 0x9a0bc8  CLensFlareFx_Load  [inline]
//   [ ] 0x9a0bf0  CLensFlareFx_Destructor  [inline]
//   [ ] 0x9a0c10  CLensFlareFx_DeletingDestructor  [inline]
#include "k2000/graphical/fx/CLensFlareFx.h"

// 0x000b3570 CLensFlareFx_Create: the inlined IRendableObject part, in the original's store order.
CLensFlareFx::CLensFlareFx() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x009a0bc8 CLensFlareFx_Load
int32_t CLensFlareFx::Load(IKFile* file, int32_t type) {
    IScreenFx::Load(file, type);  // the original calls IRendableObject_Load
    return 1;
}
