// CClone.cpp - reconstructed original translation unit 0xcb2c0-0xcba58 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CClone  key 0x30b  category SceneNode  size 0x30  vtable 0xb17ef0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xcb2c0  CClone_Delete
//   [ ] 0xcb310  RegisterCCloneClass
//   [ ] 0xcb388  _GLOBAL__I_cb388
//   [x] 0xcb398  CClone_PostLoad
//   [x] 0xcb3c0  CClone_Load
//   [ ] 0xcb460  CClone_Save
//   [x] 0xcb488  CClone_RecursiveRegistration  (CNode's (returns 1, registers nothing): CSGLeaf's)
//   [x] 0xcb4b0  CClone_Enqueue
//   [x] 0xcb710  CClone_Destroy
//   [x] 0xcb740  CClone_DeletingDestructor  (C++ destructor chain + delete)
//   [x] 0xcb788  CClone_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0xcb7b8  CClone_BaseDestructor  (C++ destructor chain: vtable store, then CNode's)
//   [x] 0xcb7e8  CClone_Construct  [dead]
//   [ ] 0xcb830  CClone_Construct_2  [dead]
//   [x] 0xcb878  CClone_DeleteArray
//   [x] 0xcb920  CClone_Create
//   [x] 0xcb988  CClone_CreateArray
//
//   [ ] 0x9a24c8  CClone_IsKindOfClass  [inline]
//   [ ] 0x9a2520  CClone_GetClassType  [inline]
//   [ ] 0x9a2528  CClone_GetClassID  [inline]
//   [ ] 0x9a2530  CClone_GetSerializationFlags  [inline]
//   [ ] 0x9a2538  CClone_vf7C  [inline]
//   [ ] 0x9a2540  CClone_vf80  [inline]
#include "k2000/scenegraph/CClone.h"

#include "Renderware/rpteam/RpTeam.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/io/IKFile.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGMovable.h"

// 0x000cb7e8 CClone_Construct
CClone::CClone() {
    m_pTeamPlayer = nullptr;
    m_pRwPlayerBSphere = nullptr;
}

// 0x000cb3c0 CClone_Load
int32_t CClone::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);  // 0xcbd28
    uint8_t b[4];
    ReadRaw(file, b, 4);  // one read, each u16 swapped (lhbrx)
    m_ui16NumOriginal = static_cast<uint16_t>(b[0] | (b[1] << 8));
    m_ui16NbLods = static_cast<uint16_t>(b[2] | (b[3] << 8));
    return 1;
}

// 0x000cb710 CClone_Destroy
void CClone::Destroy() {
    m_pRwPlayerBSphere = nullptr;
    CNode::Destroy();
}

// 0x000cb4b0 CClone_Enqueue
void CClone::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                              int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    if (m_pTeamPlayer == nullptr) return;  // (the original dereferences it: every CClone is in the clone manager's list)
    // The player's bounding sphere (RwSphere: centre, radius) through the node frame's LTM; the radius is copied unscaled.
    const float* local = static_cast<const float*>(m_pRwPlayerBSphere);
    float world[4];
    RwV3dTransformPoints(reinterpret_cast<RwV3d*>(world), reinterpret_cast<const RwV3d*>(local), 1, RwFrameGetLTM(m_pRwFrame));
    world[3] = local[3];
    // CNode_GetFlag10Bit7_WhenBit8Set_maybe 0xcbab8: the distance-cull request (bit 7) when the flag word has bit 8. A clone
    // beyond the node's distance limit (squared, +0x20) from the camera is not drawn.
    bool tooFar = false;
    if ((m_sgProperties & 0x100) != 0 && ((m_sgProperties >> 7) & 1) != 0) {
        tooFar = true;
        const CameraContext* context = g_pRenderStateRenderer->m_cameraContext;
        const RwMatrix* pose = RwFrameGetLTM(static_cast<const CSGMovable*>(context->m_pCamera)->m_pRwFrame);
        const float dy = pose->pos.y - world[1];
        const float dx = pose->pos.x - world[0];
        const float dz = pose->pos.z - world[2];
        if (dz * dz + dx * dx + dy * dy <= m_fDistanceLimitSquared) tooFar = false;
    }
    const int32_t test = RwCameraFrustumTestSphere(camera, world);  // 0 outside, 1 boundary, 2 inside
    if (test != 0 && !tooFar) {
        m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
        RpTeamPlayer* player = static_cast<RpTeamPlayer*>(m_pTeamPlayer);
        player->unkF4 = g_ui16RenderFrameCounter;
        if (test == 1) {
            player->flags |= 0x10;
        } else {
            player->flags &= ~0x10u;
        }
    }
    for (CSGLeaf* child = m_lChildList; child != nullptr; child = child->m_pNext) {
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);
    }
    // rlwinm 28,1,31 then rlwinm 4,0,31 (0xcb670): only bit 3 cleared (the rotates keep bits 0-2).
    m_pRwFrame->object.privateFlags = static_cast<uint8_t>(m_pRwFrame->object.privateFlags & 0xf7);
}
