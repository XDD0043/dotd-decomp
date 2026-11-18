// Reconstructed original translation unit: 0xd32b8-0xd3888 (GAME_TOC1, main_toc1), 13 functions, 12 live.
// Primary class: CSpawnAnimatedNode  key 0x90b  category SceneNode  size 0xc8  vtable 0xb18450
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd32b8  CSpawnAnimatedNode_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0xd3308  CSpawnAnimatedNode_RecursiveRegistration  (nothing registered: CSGLeaf's, inherited)
//   [ ] 0xd3310  RegisterCSpawnAnimatedNodeClass
//   [ ] 0xd3388  _GLOBAL__I_d3388
//   [ ] 0xd3398  CSpawnAnimatedNode_ResetHierarchy_maybe  [dead]
//   [x] 0xd33d8  CSpawnAnimatedNode_Enqueue  (UpdateAndExtract, port-final F05)
//   [x] 0xd3508  CSpawnAnimatedNode_PostLoad
//   [x] 0xd3598  CSpawnAnimatedNode_Load
//   [x] 0xd3610  CSpawnAnimatedNode_Destroy
//   [x] 0xd3668  CSpawnAnimatedNode_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0xd3708  CSpawnAnimatedNode_Create  (the header's constructor, DOTD_DECLARE_FACTORIES)
//   [x] 0xd3760  CSpawnAnimatedNode_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0xd3810  CSpawnAnimatedNode_Save
//
//   [x] 0x9a2af0  CSpawnAnimatedNode_IsKindOfClass  [inline]
//   [x] 0x9a2b50  CSpawnAnimatedNode_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a2b58  CSpawnAnimatedNode_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [ ] 0x9a2b60  CSpawnAnimatedNode_vf88  [inline]
//   [x] 0x9a2b68  CSpawnAnimatedNode_Destructor  [inline]
//   [x] 0x9a2b98  CSpawnAnimatedNode_DeletingDestructor  [inline]
#include "k2000/scenegraph/CSpawnAnimatedNode.h"

#include "k2000/io/IKFile.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CZoneNode.h"

// 0x000d3508 CSpawnAnimatedNode_PostLoad
int32_t CSpawnAnimatedNode::PostLoad(int32_t type) {
    CAnimatedNode::PostLoad(type);     // 0x000c9d48
    ISpawnNode::PostLoad(type, this);  // 0x000d5488 at this + 0x64
    if (type == K_LEVEL_PLATEFORMS) m_i32AnimSlot = -1;
    return 1;
}

// 0x000d3598 CSpawnAnimatedNode_Load
int32_t CSpawnAnimatedNode::Load(IKFile* file, int32_t type) {
    CAnimatedNode::Load(file, type);  // 0x000ca4c0
    if (type == K_LEVEL_PLATEFORMS) ISpawnNode::Load(file, K_LEVEL_PLATEFORMS);  // 0x000d5198
    return 1;
}

// 0x000d3610 CSpawnAnimatedNode_Destroy
void CSpawnAnimatedNode::Destroy() {
    m_pRpHAnimHierarchy = nullptr;
    m_i32AnimSlot = -1;
    CAnimatedNode::Destroy();       // 0x000c92e0
    ISpawnNode::ClearReferences();  // 0x000d4ba8
}

// 0x000d33d8 CSpawnAnimatedNode_Enqueue. The spawn data is called with the clock only (r5 left as it came); the sphere
// pair lives in the frame (+0x70 local, +0x80 world).
void CSpawnAnimatedNode::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                          RwCamera* camera, int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    if (CullAndUpdate(this, frameClock) == 0) return;  // 0x000d5e20
    m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
    float sphere[4];
    float worldSphere[4];
    CSpawnAnimatedNode_UpdateSharedAnim(this, this, stages, frameClock, &m_i32AnimSlot, sphere, worldSphere,
                                        camera);                            // 0x000d4a60 (CZoneNode.h, F06)
    EnqueueGeometries(this, stages, frameClock, worldSphere, camera);  // 0x000d4bf0
}
