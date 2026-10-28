// CSGRootNode.cpp - reconstructed original translation unit 0xd29c8-0xd2e28 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CSGRootNode  key 0x4b  category SceneNode  size 0x34  vtable 0xb140b0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd29c8  CSGRootNode_Delete
//   [ ] 0xd2a18  CSGRootNode_GetSectorIndex_maybe
//   [ ] 0xd2a20  RegisterCSGRootNodeClass
//   [ ] 0xd2a98  _GLOBAL__I_d2a98
//   [x] 0xd2aa8  CSGRootNode_PostLoad
//   [x] 0xd2ad0  CSGRootNode_Load
//   [ ] 0xd2af8  CSGRootNode_Save
//   [ ] 0xd2b20  CSGRootNode_RecursiveRegistration
//   [ ] 0xd2c18  CSGRootNode_Destroy
//   [x] 0xd2c40  CSGRootNode_DeleteArray
//   [x] 0xd2ce0  CreateCSGRootNode
//   [x] 0xd2d48  CSGRootNode_CreateArray
//
//   [ ] 0x993eb0  CSGRootNode_IsKindOfClass  [inline]
//   [x] 0x993ef8  CSGRootNode_GetClassType  [inline]
//   [x] 0x993f00  CSGRootNode_GetClassID  [inline]
//   [ ] 0x993f08  CSGRootNode_GetSerializationFlags  [inline]
//   [ ] 0x993f10  CSGRootNode_Destructor  [inline]
//   [ ] 0x993f78  CSGRootNode_DeletingDestructor  [inline]
#include "k2000/scenegraph/CSGRootNode.h"

// 0x000d2ad0 CSGRootNode_Load. m_AABB is not read.
int32_t CSGRootNode::Load(IKFile* file, int32_t type) {
    CSGBranch::Load(file, type);
    return 1;
}

// 0x000d2aa8 CSGRootNode_PostLoad
int32_t CSGRootNode::PostLoad(int32_t type) {
    CSGBranch::PostLoad(type);
    return 1;
}
