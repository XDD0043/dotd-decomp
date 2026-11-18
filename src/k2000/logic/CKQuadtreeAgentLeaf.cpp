// CKQuadtreeAgentLeaf.cpp - reconstructed original translation unit 0x46680-0x46ab8 (GAME_TOC1, main_toc1), 15 functions, 13 live.
// Primary class: CKQuadtreeAgentLeaf  key 0x5e8c  category Logic  size 0x34  vtable 0xb14dc8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x46680  CKQuadtreeAgentLeaf_Delete
//   [ ] 0x466d0  RegisterCKQuadtreeAgentLeafClass
//   [ ] 0x46748  _GLOBAL__I_46748
//   [x] 0x46758  CKQuadtreeAgentLeaf_Load
//   [ ] 0x46780  CKQuadtreeAgentLeaf_Save
//   [x] 0x467a8  CKQuadtreeAgentLeaf_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x467d0  CKQuadtreeAgentLeaf_Destroy  (the base's KStub_Nop_47df0: empty)
//   [x] 0x467f8  CKQuadtreeAgentLeaf_DeletingDestructor  (the destructor; delete)
//   [x] 0x46840  CKQuadtreeAgentLeaf_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x46870  CKQuadtreeAgentLeaf_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x468a0  CKQuadtreeAgentLeaf_Construct  [dead]
//   [ ] 0x468d8  CKQuadtreeAgentLeaf_Construct_2  [dead]
//   [x] 0x46910  CKQuadtreeAgentLeaf_DeleteArray
//   [x] 0x469b0  CKQuadtreeAgentLeaf_Create  (header)
//   [x] 0x46a08  CKQuadtreeAgentLeaf_CreateArray
//
//   [ ] 0x995888  CKQuadtreeAgentLeaf_vf50  [inline]
//   [ ] 0x995898  CKQuadtreeAgentLeaf_IsKindOfClass  [inline]
//   [ ] 0x9958c0  CKQuadtreeAgentLeaf_GetClassType  [inline]
//   [ ] 0x9958c8  CKQuadtreeAgentLeaf_GetClassID  [inline]
#include "k2000/logic/CKQuadtreeAgentLeaf.h"

// 0x00046758 CKQuadtreeAgentLeaf_Load
int32_t CKQuadtreeAgentLeaf::Load(IKFile* file, int32_t type) {
    CKQuadtreeAgent::Load(file, type);  // 0x00047df8
    return 1;
}
