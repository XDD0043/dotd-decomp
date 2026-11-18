// CKDynamicBoundingSphere.cpp - reconstructed original translation unit 0xd7480-0xd7878 (GAME_TOC1, main_toc1), 9 functions, 9 live.
// Primary class: CKDynamicBoundingSphere  key 0x3cb  category SceneNode  size 0x50  vtable 0xb13d10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd7480  CKDynamicBoundingSphere_Delete
//   [x] 0xd74d0  CKDynamicBoundingSphere_GetShapeType_maybe
//   [x] 0xd74e8  CKDynamicBoundingSphere_RecursiveRegistration  (CKBoundingSphere's: CSGLeaf's (nothing))
//   [ ] 0xd7510  RegisterCKDynamicBoundingSphereClass
//   [ ] 0xd7588  _GLOBAL__I_d7588
//   [x] 0xd7598  CKDynamicBoundingSphere_DeleteArray
//   [x] 0xd7640  CKDynamicBoundingSphere_Create
//   [x] 0xd76b0  CKDynamicBoundingSphere_Enqueue
//   [x] 0xd7788  CKDynamicBoundingSphere_CreateArray
//
//   [x] 0x993178  CKDynamicBoundingSphere_GetClassType  [inline]
//   [x] 0x993180  CKDynamicBoundingSphere_GetClassID  [inline]
//   [ ] 0x993228  CKDynamicBoundingSphere_IsKindOfClass  [inline]
//   [ ] 0x993280  CKDynamicBoundingSphere_DeletingDestructor  [inline]
//   [x] 0x9932e0  CKDynamicBoundingSphere_Destructor  [inline]  (C++ destructor chain: vtable stores only)
//   [x] 0x993328  CKDynamicBoundingSphere_Load  [inline]
//   [ ] 0x993508  CKDynamicBoundingSphere_Save  [inline]
//   [ ] 0x993850  HashTableU32_HashKey  [inline]
//   [ ] 0x993868  HashTableU32_KeysEqual  [inline]
//   [ ] 0x993888  KStub_Nop_993888  [inline]
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"

#include "Renderware/rwcore/RwCamera.h"

// The constructor and the Load (0x00993328) are inline in CKDynamicBoundingSphere.h.

// 0x000d76b0 CKDynamicBoundingSphere_Enqueue
void CKDynamicBoundingSphere::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                               RwCamera* camera, int32_t /*distanceCull*/) {
    CSGLeaf::UpdateAndExtract(0.0f, stages, frameClock, camera, 0);
    if (((m_ba8Infos >> 4) & 1) == 0) return;
    m_v3OldPos = m_v3LastWorldPos;
    const RwV3d& position = m_pRwFrame->ltm.pos;  // RwFrame +0x80, read as stored (no RwFrameGetLTM)
    m_v3WorldMove.x = position.x - m_v3LastWorldPos.x;
    m_v3WorldMove.z = position.z - m_v3LastWorldPos.z;
    m_v3WorldMove.y = position.y - m_v3LastWorldPos.y;
    m_v3LastWorldPos.z = position.z;
    m_v3LastWorldPos.x = position.x;
    m_v3LastWorldPos.y = position.y;
}
