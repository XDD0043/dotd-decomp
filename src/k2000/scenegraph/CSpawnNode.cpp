// CSpawnNode.cpp - reconstructed original translation unit 0xd3888-0xd3dd8 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CSpawnNode  key 0x8cb  category SceneNode  size 0x84  vtable 0xb184e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd3888  CSpawnNode_Delete
//   [ ] 0xd38d8  RegisterCSpawnNodeClass
//   [ ] 0xd3950  _GLOBAL__I_d3950
//   [ ] 0xd3960  CSpawnNode_Enqueue
//   [x] 0xd3aa8  CSpawnNode_PostLoad
//   [x] 0xd3b10  CSpawnNode_Load
//   [ ] 0xd3b88  CSpawnNode_Save
//   [ ] 0xd3bb0  CSpawnNode_RecursiveRegistration
//   [ ] 0xd3bd8  CSpawnNode_Destroy
//   [x] 0xd3c20  CSpawnNode_DeleteArray
//   [x] 0xd3cc8  CSpawnNode_Create
//   [x] 0xd3d20  CSpawnNode_CreateArray
//
//   [ ] 0x9a2be0  CSpawnNode_IsKindOfClass  [inline]
//   [ ] 0x9a2c38  CSpawnNode_GetClassType  [inline]
//   [ ] 0x9a2c40  CSpawnNode_GetClassID  [inline]
//   [ ] 0x9a2c48  CSpawnNode_vf88  [inline]
//   [ ] 0x9a2c50  CSpawnNode_Destructor  [inline]
//   [ ] 0x9a2c80  CSpawnNode_DeletingDestructor  [inline]
#include "k2000/scenegraph/CSpawnNode.h"

#include "k2000/io/IKFile.h"

// 0x000d3aa8 CSpawnNode_PostLoad
int32_t CSpawnNode::PostLoad(int32_t type) {
    CNode::PostLoad(type);  // 0x000cc340
    ISpawnNode::PostLoad(type, this);
    return 1;
}

// 0x000d3b10 CSpawnNode_Load
int32_t CSpawnNode::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) ISpawnNode::Load(file, K_LEVEL_PLATEFORMS);  // 0xd5198 at this + 0x24
    return 1;
}
