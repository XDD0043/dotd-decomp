// CSGBkgRootNode.cpp - reconstructed original translation unit 0xcd078-0xcd528 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CSGBkgRootNode  key 0x28b  category SceneNode  size 0x24  vtable 0xb18088
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xcd078  CSGBkgRootNode_Delete
//   [ ] 0xcd0c8  RegisterCSGBkgRootNodeClass
//   [ ] 0xcd140  _GLOBAL__I_cd140
//   [x] 0xcd150  CSGBkgRootNode_Enqueue
//   [x] 0xcd190  CSGBkgRootNode_PostLoad  (= the inherited slot)
//   [x] 0xcd1b8  CSGBkgRootNode_Load
//   [ ] 0xcd1e0  CSGBkgRootNode_Save
//   [x] 0xcd208  CSGBkgRootNode_RecursiveRegistration  (CNode's (nothing))
//   [x] 0xcd230  CSGBkgRootNode_Destroy  (CNode's: inherited)
//   [x] 0xcd258  CSGBkgRootNode_DeletingDestructor  (C++ destructor chain + delete)
//   [x] 0xcd2a0  CSGBkgRootNode_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0xcd2d0  CSGBkgRootNode_BaseDestructor  (C++ destructor chain: vtable store, then CNode's)
//   [ ] 0xcd300  CSGBkgRootNode_Construct  [dead]
//   [ ] 0xcd338  CSGBkgRootNode_Construct_2  [dead]
//   [x] 0xcd370  CSGBkgRootNode_DeleteArray
//   [x] 0xcd418  CSGBkgRootNode_CreateArray
//   [x] 0xcd4d0  CSGBkgRootNode_Create
//
//   [ ] 0x9a25e8  CSGBkgRootNode_IsKindOfClass  [inline]
//   [x] 0x9a2640  CSGBkgRootNode_GetClassType  [inline]
//   [x] 0x9a2648  CSGBkgRootNode_GetClassID  [inline]
//   [ ] 0x9a2650  CSGBkgRootNode_GetSerializationFlags  [inline]
#include "k2000/scenegraph/CSGBkgRootNode.h"

#include "k2000/cameras/CameraContext.h"
#include "k2000/misc/Engine.h"

// 0x000cd1b8 CSGBkgRootNode_Load
int32_t CSGBkgRootNode::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);
    return 1;
}

// 0x000cd150 CSGBkgRootNode_Enqueue: the engine's camera context (+0x08), its scene camera (+0x24); f1 TOC -0x5518 (0.0f),
// r7 0.
void CSGBkgRootNode::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock, RwCamera* /*camera*/,
                                      int32_t /*distanceCull*/) {
    CameraContext* context = static_cast<CameraContext*>(g_pEngine->m_cameraContext);
    CNode::UpdateAndExtract(0.0f, stages, frameClock, context->m_pSceneCamera, 0);
}
