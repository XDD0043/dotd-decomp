// CKBoundingSphere.cpp - reconstructed original translation unit 0xd6e60-0xd7160 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CKBoundingSphere  key 0x38b  category SceneNode  size 0x2c  vtable 0xb12fa0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd6e60  CKBoundingSphere_Delete
//   [x] 0xd6eb0  CKBoundingSphere_GetShapeType_maybe
//   [ ] 0xd6eb8  RegisterCKBoundingSphereClass
//   [ ] 0xd6f30  _GLOBAL__I_d6f30
//   [x] 0xd6f40  CKBoundingSphere_DeleteArray
//   [x] 0xd6fe0  CKBoundingSphere_CreateArray
//   [x] 0xd70c8  CKBoundingSphere_Create
//   [x] 0xd7138  CKBoundingSphere_RecursiveRegistration  (CSGLeaf's (nothing))
//
//   [x] 0x991630  CKBoundingSphere_GetClassType  [inline]
//   [x] 0x991638  CKBoundingSphere_GetClassID  [inline]
//   [ ] 0x991640  IKBoundingVolume_LevelReset  [inline]
//   [x] 0x991668  CKBoundingSphere_Destructor  [inline]  (C++ destructor chain: vtable stores only)
//   [x] 0x9916a8  IKBoundingVolume_PostLoad  [inline]
//   [x] 0x9916e0  IKBoundingVolume_Destroy  [inline]  (inherited: CSGLeaf_Destroy)
//   [ ] 0x9918d0  CKBoundingSphere_IsKindOfClass  [inline]
//   [ ] 0x991918  CKBoundingSphere_DeletingDestructor  [inline]
//   [ ] 0x991970  CKBoundingShape_Save  [inline]
//   [x] 0x991ca0  CKBoundingShape_Load  [inline]
//   [x] 0x991eb0  CKBoundingSphere_Load  [inline]
//   [ ] 0x992258  CKBoundingSphere_Save  [inline]
#include "k2000/scenegraph/CKBoundingSphere.h"

// The constructor and both Loads (0x00991ca0 IKBoundingVolume, 0x00991eb0 CKBoundingSphere) are inline
// in IKBoundingVolume.h and CKBoundingSphere.h.
