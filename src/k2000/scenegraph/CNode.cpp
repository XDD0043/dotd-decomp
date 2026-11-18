// CNode.cpp - reconstructed original translation unit 0xcba58-0xccaa0 (GAME_TOC1, main_toc1), 27 functions, 20 live.
// Primary class: CNode  key 0xcb  category SceneNode  size 0x24  vtable 0xb17f80
// Other owners: TransformNodeBoundingSphereToWorld (1), EnqueueSceneNodeAndChildren (1), InitializeCNode (1), CullAndEnqueueNodeGeometry (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xcba58  CNode_Delete
//   [x] 0xcbaa8  CNode_RecursiveRegistration  (returns 1, registers nothing: CSGLeaf's)
//   [ ] 0xcbab0  CNode_Save
//   [x] 0xcbab8  CNode_GetFlag10Bit7_WhenBit8Set_maybe  (inlined in CKHkS08TransportableWeight::Update)
//   [ ] 0xcbad8  FUN_000cbad8  [dead]
//   [ ] 0xcbb18  CNode_AddGeometry_maybe  [dead]
//   [ ] 0xcbba0  CNode_RemoveGeometry_maybe  [dead]
//   [x] 0xcbc60  CNode_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0xcbca0  RegisterCNodeClass
//   [ ] 0xcbd18  _GLOBAL__I_cbd18
//   [x] 0xcbd28  CNode_Load
//   [x] 0xcbe10  CNode_Destroy
//   [x] 0xcbe40  InitializeCNode
//   [x] 0xcbea0  CNode_DeleteArray
//   [ ] 0xcbf48  CNode_LevelResetGeometries_maybe  [dead]
//   [x] 0xcbfc0  TransformNodeBoundingSphereToWorld
//   [x] 0xcc160  EnqueueSceneNodeAndChildren  (CNode::UpdateAndExtract)
//   [ ] 0xcc290  CNode_RemoveAllGeometries_maybe  [dead]
//   [x] 0xcc340  CNode_PostLoad
//   [ ] 0xcc400  InitializeCNode_2  [dead]
//   [x] 0xcc460  CullAndEnqueueNodeGeometry
//   [x] 0xcc808  CNode_SetFlag10Bit5_ResetField20To1_maybe
//   [ ] 0xcc858  FUN_000cc858  [dead]
//   [x] 0xcc8a8  CNode_CreateArray
//   [x] 0xcc998  CNode_Create
//   [x] 0xcca08  CNode_DeletingDestructor  (C++ destructor chain + delete)
//   [x] 0xcca60  CNode_Destructor  (C++ destructor chain: vtable stores only)
//
//   [ ] 0x9a2548  CNode_IsKindOfClass  [inline]
//   [x] 0x9a2590  CNode_GetClassType  [inline]
//   [x] 0x9a2598  CNode_GetClassID  [inline]
#include "k2000/scenegraph/CNode.h"

#include <cmath>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/geometry/CGeometry.h"

#include "k2000/io/IKFile.h"
#include "k2000/render/CRenderer.h"

// 0x000cbe40 InitializeCNode: the CSGBranch part, then m_pParent and the geometry list.
CNode::CNode() {
    m_pParent = nullptr;
    m_lGeometryList = nullptr;
}

// 0x000cc808 CNode_SetFlag10Bit5_ResetField20To1_maybe
void CNode::SetFlag10Bit5ResetField20To1(uint32_t on) {
    if (on == ((m_sgProperties >> 5) & 1u)) return;
    m_sgProperties = (m_sgProperties & 0xffffffdfu) | (on << 5);
    if (on == 0) return;
    m_sgProperties &= 0xff9fffffu;
    m_fDistanceLimitSquared = 1.0f;
}

// 0x000cbe10 CNode_Destroy
void CNode::Destroy() {
    m_lGeometryList = nullptr;
    CSGBranch::Destroy();
}

// 0x000cbd28 CNode_Load. No type check.
int32_t CNode::Load(IKFile* file, int32_t type) {
    CSGBranch::Load(file, type);
    IKFile_ReadRef(file, &m_lGeometryList);
    ReadF32LE(file, &m_fDistanceLimitSquared);
    return 1;
}

namespace {
// BridgeRwCameraFrustumTestSphere_maybe (RwCameraFrustumTestSphere): 0 outside, 1 boundary, 2 inside.
int32_t CameraFrustumTestSphere(RwCamera* camera, const float* sphere) { return RwCameraFrustumTestSphere(camera, sphere); }

// The node's frame: bit 3 of its private flags cleared (lbz +0x03; rlwinm 28,1,31 then rlwinm 4,0,31: the rotates keep
// bits 0-2, so only the object-sync subtree bit 0x8 goes). The LTM-sync bit 0x4 stays: a node marked dirty during the
// traversal (CGlowNodeFx_Enqueue's follow) gets its LTM at the next sync of its hierarchy.
void MarkFrame(RwFrame* frame) { frame->object.privateFlags = static_cast<uint8_t>(frame->object.privateFlags & 0xf7); }
}  // namespace

// 0x000cc460 CullAndEnqueueNodeGeometry
uint32_t CNode::CullAndEnqueueGeometry(RenderQueue** stages, IKTime* frameClock, RwCamera* camera) {
    if ((m_sgProperties & 4) != 0) return 0;
    uint32_t state = (m_sgProperties >> 4) & 3;
    CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList);
    if (state == 1) {
        if (m_ui16LastRenderedFrame == 0) {
            m_ui16LastRenderedFrame = 0xffff;
            for (; geometry != nullptr; geometry = geometry->m_pNext) geometry->GetWorldBoundingSphere(this);
            MarkFrame(m_pRwFrame);
            geometry = static_cast<CGeometry*>(m_lGeometryList);
        }
        if (geometry == nullptr) return 0;
        state = 0;
        do {
            int32_t distanceCull = 0;
            if (CameraFrustumTestSphere(camera, geometry->m_pRpAtomic->worldSphere) != 0) {
                state = 1;
                if ((m_sgProperties & 0x100) != 0) distanceCull = (m_sgProperties >> 7) & 1;
                geometry->EnqueueVisible(m_fDistanceLimitSquared, stages, frameClock, camera, distanceCull);
            }
            geometry = geometry->m_pNext;
        } while (geometry != nullptr);
        return state;
    }
    if (state == 0) {
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            const float* sphere = geometry->GetWorldBoundingSphere(this);
            int32_t distanceCull = 0;
            if (CameraFrustumTestSphere(camera, sphere) != 0) {
                state = 1;
                if ((m_sgProperties & 0x100) != 0) distanceCull = (m_sgProperties >> 7) & 1;
                geometry->EnqueueVisible(m_fDistanceLimitSquared, stages, frameClock, camera, distanceCull);
            }
        }
    } else {
        if (state != 2) return 0;
        state = 0;
        if (geometry != nullptr) {
            do {
                geometry->GetWorldBoundingSphere(this);
                int32_t distanceCull = 0;
                if ((m_sgProperties & 0x100) != 0) distanceCull = (m_sgProperties >> 7) & 1;
                geometry->EnqueueVisible(m_fDistanceLimitSquared, stages, frameClock, camera, distanceCull);
                geometry = geometry->m_pNext;
            } while (geometry != nullptr);
            state = 1;
        }
    }
    MarkFrame(m_pRwFrame);
    return state;
}

// 0x000cc160 EnqueueSceneNodeAndChildren
void CNode::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                             int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    if (CullAndEnqueueGeometry(stages, frameClock, camera) != 0) m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
    for (CSGLeaf* child = m_lChildList; child != nullptr; child = child->m_pNext) {
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);
    }
}

// 0x000cc340 CNode_PostLoad. The frames' attached-object lists are not modelled (the atomic only records
// its frame).
int32_t CNode::PostLoad(int32_t type) {
    CSGBranch::PostLoad(type);
    for (CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        RpAtomic* atomic = geometry->m_pRpAtomic;
        atomic->frame = m_pRwFrame;
        atomic->privateFlags |= 1;
    }
    return 1;
}

// 0x000cbfc0 TransformNodeBoundingSphereToWorld (from the assembly): the local sphere through the node frame's
// LTM. A matrix with flag 0x20000 copies it unchanged; otherwise the centre is transformed
// (Mat4_TransformPoints 0x23f7e8 = RwV3dTransformPoints) and, unless the matrix is flagged 1, the radius is
// scaled by the longest axis: sqrt (Math_Sqrtf 0x10690, fsqrts) of the largest of |right|^2, |up|^2,
// |at|^2 (fmadds sums; the max picked with the asm's compares). The frame's stored LTM (+0x50) as the last sync left it
// (no RwFrameGetLTM): a node moved during the traversal (CGlowNodeFx_Enqueue's follow, RwFrame_MarkDirty) is culled
// at its last synced place until the next sync (G +8992: a following glow enters the view a frame later).
void TransformNodeBoundingSphereToWorld(float radius, CNode* node, float* worldCenter, float* worldRadius,
                                        const float* localCenter) {
    const RwMatrix* m = FrameLtm(node->m_pRwFrame);
    const uint32_t flags = m->flags;
    if ((flags & 0x20000) != 0) {
        *worldRadius = radius;
        worldCenter[2] = localCenter[2];
        worldCenter[0] = localCenter[0];
        worldCenter[1] = localCenter[1];
        return;
    }
    RwV3dTransformPoints(reinterpret_cast<RwV3d*>(worldCenter), reinterpret_cast<const RwV3d*>(localCenter), 1, m);
    if ((flags & 1) != 0) {
        *worldRadius = radius;
        return;
    }
    const float right = ppc::fmadds(m->right.z, m->right.z, ppc::fmadds(m->right.x, m->right.x, m->right.y * m->right.y));
    const float up = ppc::fmadds(m->up.z, m->up.z, ppc::fmadds(m->up.x, m->up.x, m->up.y * m->up.y));
    const float at = ppc::fmadds(m->at.z, m->at.z, ppc::fmadds(m->at.x, m->at.x, m->at.y * m->at.y));
    const float upOrAt = up >= at ? up : at;  // fcmpu + cror gt|eq
    float largest;
    if (upOrAt <= right) {
        largest = right;
    } else {
        largest = up >= at ? up : at;
    }
    *worldRadius = std::sqrt(largest) * radius;
}
