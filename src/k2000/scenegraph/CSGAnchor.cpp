// CSGAnchor.cpp - reconstructed original translation unit 0xccaa0-0xcd078 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CSGAnchor  key 0x10b  category SceneNode  size 0x1c  vtable 0xb18010
// Other owners: PrimaryCamera (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xccaa0  CSGAnchor_Delete
//   [x] 0xccaf0  CSGAnchor_vf58  (CSGAnchor::UpdateAndExtract, port-final F05)
//   [ ] 0xccb80  CSGAnchor_Save
//   [x] 0xccba8  CSGAnchor_RecursiveRegistration  (CSGLeaf's (nothing))
//   [x] 0xccbd0  CSGAnchor_DeletingDestructor  (C++ destructor chain + delete)
//   [x] 0xccc18  CSGAnchor_Destructor  (C++ destructor chain: vtable store, then CSGLeaf's)
//   [x] 0xccc48  CSGAnchor_BaseDestructor  (C++ destructor chain: vtable store, then CSGLeaf's)
//   [x] 0xccc78  CSGAnchor_Destroy  (CSGLeaf's Destroy, inherited)
//   [ ] 0xccca0  RegisterCSGAnchorClass
//   [ ] 0xccd18  _GLOBAL__I_ccd18
//   [ ] 0xccd28  PrimaryCamera_IsSphereVisible_maybe  [dead: no pointer to its descriptor 0xb4f050]
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

#include "k2000/hooks/KBase4C2.h"
#include "k2000/io/IKFile.h"

// 0x000ccfb8 CSGAnchor_Load
int32_t CSGAnchor::Load(IKFile* file, int32_t type) {
    CSGLeaf::Load(file, type);  // 0xcf550
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pTarget);
    return 1;
}

// 0x000ccaf0 CSGAnchor_vf58 (TOC1 -0x557c 0)
void CSGAnchor::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                 RwCamera* camera, int32_t /*distanceCull*/) {
    CSGLeaf::UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // 0x000ceb80
    if ((m_sgProperties & 4) == 0) static_cast<KBase4C2*>(m_pTarget)->VfC0(frameClock);  // vt+0xc0
}
