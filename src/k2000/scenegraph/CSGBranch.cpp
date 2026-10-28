// CSGBranch.cpp - reconstructed original translation unit 0xcd528-0xcdf20 (GAME_TOC1, main_toc1), 21 functions, 18 live.
// Primary class: CSGBranch  key 0x24b  category SceneNode  size 0x1c  vtable 0xb18118
// Other owners: EnqueueSceneRootChildren (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xcd528  CSGBranch_Delete
//   [ ] 0xcd578  CSGBranch_RecursiveRegistration
//   [ ] 0xcd580  CSGBranch_CollectFlaggedChildren_maybe
//   [ ] 0xcd5f0  RegisterCSGBranchClass
//   [ ] 0xcd668  _GLOBAL__I_cd668
//   [x] 0xcd678  CSGBranch_PostLoad
//   [x] 0xcd6a0  CSGBranch_Load
//   [x] 0xcd780  CSGBranch_AddChildKeepWorldTransform_maybe
//   [x] 0xcd808  CSGBranch_AddChild_maybe
//   [x] 0xcd870  CSGBranch_Destroy
//   [x] 0xcd8a0  CSGBranch_DeleteArray
//   [x] 0xcd948  CSGBranch_CreateArray
//   [ ] 0xcda10  CSGBranch_SetHAnimFrameID_maybe  [dead]
//   [ ] 0xcda38  CSGBranch_GetHAnimFrameID_maybe  [dead]
//   [ ] 0xcda68  CSGBranch_RemoveAllChildren_maybe
//   [x] 0xcdb30  CSGBranch_RemoveChild_maybe
//   [ ] 0xcdc28  CSGBranch_LevelResetChildren_maybe  [dead]
//   [x] 0xcdca8  EnqueueSceneRootChildren
//   [ ] 0xcdd60  CSGBranch_UpdateWorldMatrices
//   [ ] 0xcdde0  CSGBranch_Save
//   [x] 0xcdec0  CSGBranch_Create
//
//   [ ] 0x9a2658  CSGBranch_IsKindOfClass  [inline]
//   [x] 0x9a2690  CSGBranch_GetClassType  [inline]
//   [x] 0x9a2698  CSGBranch_GetClassID  [inline]
//   [ ] 0x9a26a0  CSGBranch_DeletingDestructor  [inline]
//   [ ] 0x9a26e8  CSGBranch_Destructor  [inline]
#include "k2000/scenegraph/CSGBranch.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/core/Stub.h"
#include "k2000/render/CRenderer.h"

#include "k2000/io/IKFile.h"

// Inlined in 0x000cdec0 CSGBranch_Create and the derived constructors.
CSGBranch::CSGBranch() { m_lChildList = nullptr; }

// 0x000cd6a0 CSGBranch_Load. No type check.
int32_t CSGBranch::Load(IKFile* file, int32_t type) {
    CSGLeaf::Load(file, type);
    IKFile_ReadRef(file, &m_lChildList);
    return 1;
}

// 0x000cd808 CSGBranch_AddChild_maybe (RwFrameAddChild 0x74c6a0 is inlined there)
void CSGBranch::AddChild(CSGLeaf* child) {
    child->m_pNext = m_lChildList;
    m_lChildList = child;
    RwFrameAddChild(m_pRwFrame, child->m_pRwFrame);
    child->SetParent(this, 0xff);
}

// 0x000cd780 CSGBranch_AddChildKeepWorldTransform_maybe
// AddChild (vt+0x70), then Mat4_Invert_maybe 0x23f878 of this node's LTM and SceneNode_SetLocalFromWorldTimes_maybe 0xd0b90: the
// child's modelling matrix = its world matrix times the inverse (RwMatrixMultiply), the frame marked dirty. The original takes the
// child's LTM as the last sync left it (its world matrix); the LTM here is computed on demand, so it is taken before the child
// joins this node.
void CSGBranch::AddChildKeepWorldTransform(CSGLeaf* child) {
    const RwMatrix world = *RwFrameGetLTM(child->m_pRwFrame);
    AddChild(child);  // vt+0x70
    RwMatrix inverse;
    RwMatrixInvert(&inverse, RwFrameGetLTM(m_pRwFrame));
    RwMatrixMultiply(&child->m_pRwFrame->modelling, &world, &inverse);
    RwFrame_MarkDirty(child->m_pRwFrame);
}

// 0x000cdb30 CSGBranch_RemoveChild_maybe (RwFrameRemoveChild inlined). A child that is not in the list is
// still unparented.
void CSGBranch::RemoveChild(CSGLeaf* child) {
    RwFrameRemoveChild(child->m_pRwFrame);
    CSGLeaf* head = m_lChildList;
    if (head != nullptr) {
        if (child == head) {
            m_lChildList = child->m_pNext;
        } else {
            CSGLeaf* prev = head;
            CSGLeaf* cur = prev->m_pNext;
            while (cur != nullptr && cur != child) {
                prev = cur;
                cur = cur->m_pNext;
            }
            if (cur == nullptr) {
                child->SetParent(nullptr, 0xff);
                return;
            }
            prev->m_pNext = child->m_pNext;
        }
        child->m_pNext = nullptr;
    }
    child->SetParent(nullptr, 0xff);
}

// 0x000cdca8 EnqueueSceneRootChildren (TOC -0x54e8: 0.0f)
void CSGBranch::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                 RwCamera* camera, int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
    for (CSGLeaf* child = m_lChildList; child != nullptr; child = child->m_pNext) {
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);
    }
}

// 0x000cd870 CSGBranch_Destroy
void CSGBranch::Destroy() {
    m_lChildList = nullptr;
    CSGLeaf::Destroy();
}

// 0x000cd678 CSGBranch_PostLoad
int32_t CSGBranch::PostLoad(int32_t type) {
    CSGLeaf::PostLoad(type);
    return 1;
}
