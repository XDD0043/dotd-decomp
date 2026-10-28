// CSGAnchor.cpp - reconstructed original translation unit 0xccaa0-0xcd078 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CSGAnchor  key 0x10b  category SceneNode  size 0x1c  vtable 0xb18010
// Other owners: PrimaryCamera (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xccaa0  CSGAnchor_Delete
//   [ ] 0xccaf0  CSGAnchor_vf58
//   [ ] 0xccb80  CSGAnchor_Save
//   [ ] 0xccba8  CSGAnchor_RecursiveRegistration
//   [ ] 0xccbd0  CSGAnchor_DeletingDestructor
//   [ ] 0xccc18  CSGAnchor_Destructor
//   [ ] 0xccc48  CSGAnchor_BaseDestructor
//   [ ] 0xccc78  CSGAnchor_Destroy
//   [ ] 0xccca0  RegisterCSGAnchorClass
//   [ ] 0xccd18  _GLOBAL__I_ccd18
//   [ ] 0xccd28  PrimaryCamera_IsSphereVisible_maybe
//   [ ] 0xccd90  CSGAnchor_Construct  [dead]
//   [ ] 0xccdc8  CSGAnchor_Construct_2  [dead]
//   [x] 0xcce00  CSGAnchor_DeleteArray
//   [x] 0xccea8  CSGAnchor_CreateArray
//   [x] 0xccf60  CSGAnchor_Create
//   [x] 0xccfb8  CSGAnchor_Load
//
//   [ ] 0x9a25a0  CSGAnchor_IsKindOfClass  [inline]
//   [ ] 0x9a25d8  CSGAnchor_GetClassType  [inline]
//   [ ] 0x9a25e0  CSGAnchor_GetClassID  [inline]
#include "k2000/scenegraph/CSGAnchor.h"

#include "k2000/io/IKFile.h"

// 0x000ccfb8 CSGAnchor_Load
int32_t CSGAnchor::Load(IKFile* file, int32_t type) {
    CSGLeaf::Load(file, type);  // 0xcf550
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pTarget);
    return 1;
}
