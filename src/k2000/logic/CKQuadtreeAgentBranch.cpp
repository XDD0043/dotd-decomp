// CKQuadtreeAgentBranch.cpp - reconstructed original translation unit 0x45500-0x46680 (GAME_TOC1, main_toc1), 19 functions, 14 live.
// Primary class: CKQuadtreeAgentBranch  key 0x5e4c  category Logic  size 0x40  vtable 0xb14d68
// Other owners: CKQuadtreeAgent (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x45500  CKQuadtreeAgentBranch_Delete
//   [ ] 0x45550  RegisterCKQuadtreeAgentBranchClass
//   [ ] 0x455c8  _GLOBAL__I_455c8
//   [x] 0x455d8  CKQuadtreeAgentBranch_Load
//   [ ] 0x45798  CKQuadtreeAgentBranch_Save
//   [x] 0x457c0  CKQuadtreeAgentBranch_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x457e8  CKQuadtreeAgentBranch_Destroy
//   [x] 0x45848  CKQuadtreeAgentBranch_DeletingDestructor  (the destructor; delete)
//   [ ] 0x458c0  CKQuadtreeAgentBranch_Construct  [dead]
//   [ ] 0x45920  CKQuadtreeAgentBranch_Construct_2  [dead]
//   [x] 0x45980  CKQuadtreeAgentBranch_DeleteArray
//   [x] 0x45a20  CKQuadtreeAgentBranch_vf50  (UpdateBounds)
//   [x] 0x45c90  CKQuadtreeAgentBranch_Destructor
//   [x] 0x45d00  CKQuadtreeAgentBranch_Destructor_2  (the destructor)
//   [ ] 0x45d70  CKQuadtreeAgentBranch_RemoveChild_maybe  [dead]
//   [ ] 0x45f08  CKQuadtreeAgentBranch_AddChild_maybe  [dead]
//   [x] 0x45fd8  CKQuadtreeAgentBranch_CreateArray
//   [x] 0x460b8  CKQuadtreeAgentBranch_Create
//   [ ] 0x46128  CKQuadtreeAgent_SetDepthRecursive_maybe  [dead]
//
//   [ ] 0x995850  CKQuadtreeAgentBranch_IsKindOfClass  [inline]
//   [ ] 0x995878  CKQuadtreeAgentBranch_GetClassType  [inline]
//   [ ] 0x995880  CKQuadtreeAgentBranch_GetClassID  [inline]
#include "k2000/logic/CKQuadtreeAgentBranch.h"

#include <cfloat>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// 0x00c51828 (StaticInitAndDestruction_482f8: the vector 0x00c50ddc): the empty bounds, (-FLT_MAX, -FLT_MAX).
constexpr float kEmpty = -FLT_MAX;
}  // namespace

// 0x00045c90 CKQuadtreeAgentBranch_Destructor
CKQuadtreeAgentBranch::~CKQuadtreeAgentBranch() {
    if (m_children.m_pBlock != nullptr) Mem_FreeAligned16(m_children.m_pBlock);  // 0x00052fb8
    m_children.m_ui32NbUsedElt = 0;
    m_children.m_pBlock = nullptr;
}

// 0x000457e8 CKQuadtreeAgentBranch_Destroy
void CKQuadtreeAgentBranch::Destroy() {
    CKQuadtreeAgent::Destroy();  // KStub_Nop_47df0
    if (m_children.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_children.m_pBlock);
        m_children.m_pBlock = nullptr;
    }
    m_children.m_ui32NbUsedElt = 0;
    m_children.m_pBlock = nullptr;
}

// 0x000455d8 CKQuadtreeAgentBranch_Load
int32_t CKQuadtreeAgentBranch::Load(IKFile* file, int32_t type) {
    CKQuadtreeAgent::Load(file, type);  // 0x00047df8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    const uint32_t capacity = count + 1;
    if (m_children.m_ui32NbElt < count) {
        // Mem_ReallocAligned16 (0x00053190): count + 1 pointers (one when that wraps to 0); native pointer size.
        if (capacity == 0) {
            m_children.m_pBlock = static_cast<CKQuadtreeAgent**>(
                Mem_ReallocAligned16(m_children.m_pBlock, static_cast<uint32_t>(sizeof(CKQuadtreeAgent*))));
            m_children.m_ui32NbElt = 1;
        } else {
            m_children.m_pBlock = static_cast<CKQuadtreeAgent**>(
                Mem_ReallocAligned16(m_children.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CKQuadtreeAgent*))));
            m_children.m_ui32NbElt = capacity;
        }
    }
    m_children.m_ui32NbUsedElt = count;
    // The references in one go (the resolver's vt+0x28, or count raw ids).
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_children.m_pBlock), count);
    return 1;
}

// 0x00045a20 CKQuadtreeAgentBranch_vf50. The minimum starts at (FLT_MAX, FLT_MAX) (0x00c50de4) and the maximum at
// (-FLT_MAX, -FLT_MAX) (0x00c50ddc); the comparisons keep the PS3 branches (a NaN takes the child's value for the
// maximum, the running value for the minimum). The branch's own +0x30 is left as it is.
void CKQuadtreeAgentBranch::UpdateBounds() {
    uint32_t count = m_children.m_ui32NbUsedElt;
    if (count == 0) {
        m_vMin[0] = kEmpty;
        m_vMin[1] = kEmpty;
        m_vMax[0] = kEmpty;
        m_vMax[1] = kEmpty;
        return;
    }
    uint8_t empty = 1;
    float minX = FLT_MAX;
    float minY = FLT_MAX;
    float maxX = -FLT_MAX;
    float maxY = -FLT_MAX;
    uint32_t i = 0;
    do {
        CKQuadtreeAgent* child = m_children.m_pBlock[i];
        if (child->m_bDirty != 0) {
            child->UpdateBounds();  // vt+0x50
            count = m_children.m_ui32NbUsedElt;
        }
        float x = child->m_vMin[0];
        float y = child->m_vMin[1];
        if (!(x == kEmpty && y == kEmpty)) {
            if (!(minX > x)) x = minX;  // fcmpu; bgt keeps the child's
            if (!(minY > y)) y = minY;
            const float cx = child->m_vMax[0];
            if (!(cx < maxX)) maxX = cx;  // blt keeps the running maximum
            const float cy = child->m_vMax[1];
            if (!(maxY > cy)) maxY = cy;
            minY = y;
            empty = 0;
            minX = x;
        }
        ++i;
    } while (i < count);
    if (empty != 0) {
        m_vMin[0] = kEmpty;
        m_vMin[1] = kEmpty;
        m_vMax[0] = kEmpty;
        m_vMax[1] = kEmpty;
        return;
    }
    m_vMax[0] = maxX;
    m_vMin[0] = minX;
    m_vMin[1] = minY;
    m_vMax[1] = maxY;
}
