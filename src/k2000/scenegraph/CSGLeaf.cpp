// CSGLeaf.cpp - reconstructed original translation unit 0xceb28-0xcf6e0 (GAME_TOC1, main_toc1), 25 functions, 23 live.
// Primary class: CSGLeaf  key 0x20b  category SceneNode  size 0x18  vtable 0xb181f8
// Other owners: SceneNode (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xceb28  CSGLeaf_Delete
//   [x] 0xceb78  CSGLeaf_RecursiveRegistration  (returns 1, registers nothing: the IKSerializable default slot)
//   [x] 0xceb80  CSGLeaf_Enqueue
//   [x] 0xceba0  KStub_Return0_ceba0
//   [x] 0xceba8  CSGLeaf_GetSectorIndex_maybe  (GetSectorIndex, CSGLeaf.cpp)
//   [x] 0xcec08  SceneNode_SetParent_maybe
//   [ ] 0xcec30  SceneNode_IsAttachedChildOfAnimatedParent_maybe  [dead]
//   [ ] 0xcecf8  RegisterCSGLeafClass
//   [ ] 0xced70  _GLOBAL__I_ced70
//   [ ] 0xced80  CSGLeaf_Save
//   [x] 0xceda8  CSGLeaf_Destroy
//   [x] 0xcede0  SceneNode_UpdateWorldMatrix
//   [x] 0xcef68  CSGLeaf_UpdateWorldMatrices
//   [x] 0xcef70  CSGLeaf_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0xcefa0  CSGLeaf_Construct_2  [dead]
//   [x] 0xcefe0  CSGLeaf_Construct
//   [x] 0xcf020  CSGLeaf_DeleteArray
//   [x] 0xcf0c8  CSGLeaf_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0xcf0f8  CSGLeaf_PostLoad
//   [x] 0xcf1e0  CSGLeaf_ComputeLTMWithParent_maybe
//   [x] 0xcf300  CSGLeaf_ComputeLTM_maybe
//   [x] 0xcf3e0  CSGLeaf_DeletingDestructor  (C++ destructor chain + delete)
//   [x] 0xcf428  CSGLeaf_Create
//   [x] 0xcf488  CSGLeaf_CreateArray
//   [x] 0xcf550  CSGLeaf_Load
//
//   [x] 0x991568  CSGLeaf_vf60  [inline]
//   [x] 0x991580  KStub_Return0_991580  [inline]
//   [ ] 0x9a27a0  CSGLeaf_IsKindOfClass  [inline]
//   [x] 0x9a27c8  CSGLeaf_GetClassType  [inline]
//   [x] 0x9a27d0  CSGLeaf_GetClassID  [inline]
#include "k2000/scenegraph/CSGLeaf.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"

// 0x000cefe0 CSGLeaf_Construct
CSGLeaf::CSGLeaf() { m_pNext = nullptr; }

// 0x000cf1e0 CSGLeaf_ComputeLTMWithParent_maybe. The 4x16-byte row copy of the original (the rows loaded
// first, then stored) is one RwMatrix assignment.
void CSGLeaf::ChildWorldMatrixUpdate(CSGMovable* child) {
    RwFrame* frame = m_pRwFrame;
    if (m_pParent != nullptr) {
        m_pParent->ChildWorldMatrixUpdate(this);  // vt+0x54
    } else {
        frame->ltm = frame->modelling;
    }
    RwFrame* childFrame = child->m_pRwFrame;
    RwMatrixMultiply(&childFrame->ltm, &childFrame->modelling, &frame->ltm);
}

// 0x000cf300 CSGLeaf_ComputeLTM_maybe
void CSGLeaf::ForceWorldMatrixUpdate() {
    RwFrame* frame = m_pRwFrame;
    if (m_ui8BoneParent != 0xff || (frame->root->object.privateFlags & 1) != 0) {
        if (m_pParent == nullptr) {
            frame->ltm = frame->modelling;
        } else {
            m_pParent->ChildWorldMatrixUpdate(this);  // vt+0x54
        }
    }
}

// 0x000cf550 CSGLeaf_Load. No type check.
int32_t CSGLeaf::Load(IKFile* file, int32_t type) {
    CSGMovable::Load(file, type);
    IKFile_ReadRef(file, &m_pParent);
    ReadU32LE(file, &m_sgProperties);
    ReadU8(file, &m_ui8BoneParent);
    IKFile_ReadRef(file, &m_pNext);
    m_ui16LastRenderedFrame = 0;
    return 1;
}

// 0x000ceda8 CSGLeaf_Destroy
void CSGLeaf::Destroy() {
    m_pParent = nullptr;
    m_ui8BoneParent = 0xff;
    CSGMovable::Destroy();
}

// 0x000ceb80 CSGLeaf_Enqueue
void CSGLeaf::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** /*stages*/, IKTime* /*frameClock*/,
                               RwCamera* /*camera*/, int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
}

// 0x000cf0f8 CSGLeaf_PostLoad: the frame becomes the parent frame's first child (next = the old first),
// its parent and hierarchy root set, and its sync bits (private flags 0-1) cleared. Every type.
int32_t CSGLeaf::PostLoad(int32_t /*type*/) {
    if (m_pParent == nullptr || m_ui8BoneParent != 0xff) return 1;
    RenderLock_Lock();
    RwFrame* parent = m_pParent->m_pRwFrame;
    m_pRwFrame->next = parent->child;
    parent->child = m_pRwFrame;
    m_pRwFrame->object.parent = parent;
    rwSetHierarchyRoot(m_pRwFrame, parent->root);
    const uint8_t flags = m_pRwFrame->object.privateFlags;
    if ((flags & 3) != 0) m_pRwFrame->object.privateFlags = static_cast<uint8_t>(flags & 0xfc);
    RenderLock_Unlock();
    return 1;
}

// 0x000ceba8 CSGLeaf_GetSectorIndex_maybe
uint32_t CSGLeaf::GetSectorIndex() { return m_pParent != nullptr ? m_pParent->GetSectorIndex() : 0xfffffffeu; }

// 0x000cede0 SceneNode_UpdateWorldMatrix
uint8_t CSGLeaf::UpdateWorldMatrix(int32_t force) {
    RwFrame* frame = m_pRwFrame;
    if (force == 0 && (frame->root->object.privateFlags & 1u) == 0 && (frame->object.privateFlags & 4u) == 0) return 0;
    CSGBranch* parent = m_pParent;
    if (parent == nullptr) {
        frame->ltm = frame->modelling;  // the four rows copied
    } else if (m_ui8BoneParent == 0xff || parent->m_ui16LastRenderedFrame == 0) {
        RwMatrixMultiply(&frame->ltm, &frame->modelling, &parent->m_pRwFrame->ltm);  // 0x00759648
    } else {
        RwMatrix bone;
        RwMatrixMultiply(&bone, static_cast<CAnimatedNode*>(parent)->GetBoneMatrix(m_ui8BoneParent),
                         &parent->m_pRwFrame->ltm);  // 0x000c8bd8
        RwMatrixMultiply(&frame->ltm, &frame->modelling, &bone);
    }
    frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & 0xfau);
    return 1;
}
