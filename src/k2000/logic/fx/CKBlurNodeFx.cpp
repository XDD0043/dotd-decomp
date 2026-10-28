// CKBlurNodeFx.cpp - reconstructed original translation unit 0x571be0-0x5721e0 (GAME_TOC2, main_toc2), 14 functions, 14 live.
// Primary class: CKBlurNodeFx  key 0x30c  category Logic  size ?  vtable 0xb2dd80
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x571be0  CKBlurNodeFx_Delete
//   [ ] 0x571c30  CKBlurNodeFx_Destroy
//   [ ] 0x571c38  CKBlurNodeFx_RecursiveRegistration
//   [ ] 0x571c90  CKBlurNodeFx_PostLoad
//   [ ] 0x571c98  CKBlurNodeFx_Start
//   [ ] 0x571d38  RegisterCKBlurNodeFxClass
//   [ ] 0x571db0  _GLOBAL__I_571db0
//   [x] 0x571dc0  CKBlurNodeFx_Load
//   [ ] 0x571de8  CKBlurNodeFx_Save
//   [x] 0x571e10  CKBlurNodeFx_DeleteArray
//   [x] 0x571eb0  CKBlurNodeFx_CreateArray
//   [ ] 0x571f60  CKBlurNodeFx_Update
//   [ ] 0x572080  CKBlurNodeFx_Stop
//   [x] 0x572188  CKBlurNodeFx_Create
//
//   [ ] 0x9cad08  CKBlurNodeFx_IsKindOfClass  [inline]
//   [x] 0x9cad40  CKBlurNodeFx_GetClassType  [inline]
//   [x] 0x9cad48  CKBlurNodeFx_GetClassID  [inline]
//   [ ] 0x9cad50  CKBlurNodeFx_GetFxData  [inline]
//   [ ] 0x9cad58  CKBlurNodeFx_SetFxData  [inline]
//   [ ] 0x9cad60  CKBlurNodeFx_Destruct  [inline]
//   [ ] 0x9cad80  CKBlurNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKBlurNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x00571dc0 CKBlurNodeFx_Load
int32_t CKBlurNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);  // through TocBridge_IKNodeFx_Load
    return 1;
}
