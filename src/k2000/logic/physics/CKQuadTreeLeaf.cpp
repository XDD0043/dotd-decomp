// CKQuadTreeLeaf.cpp - reconstructed original translation unit 0x1f1a58-0x1f20d0 (GAME_TOC1, main_toc1), 16 functions, 13 live.
// Primary class: CKQuadTreeLeaf  key 0x190c  category Logic  size 0x8  vtable 0xb1e798
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f1a58  CKQuadTreeLeaf_Delete
//   [ ] 0x1f1aa8  CKQuadTreeLeaf_Construct  [dead]
//   [ ] 0x1f1ac0  CKQuadTreeLeaf_Construct_2  [dead]
//   [ ] 0x1f1ad8  RegisterCKQuadTreeLeafClass
//   [ ] 0x1f1b50  _GLOBAL__I_1f1b50
//   [x] 0x1f1b60  CKQuadTreeLeaf_DeleteArray
//   [x] 0x1f1c00  CKQuadTreeLeaf_FindLeaf
//   [x] 0x1f1cf8  CKQuadTreeLeaf_CreateArray
//   [x] 0x1f1d98  CKQuadTreeLeaf_Create
//   [ ] 0x1f1dd8  CKQuadTreeLeaf_Save
//   [x] 0x1f1de0  CKQuadTreeLeaf_Load
//   [ ] 0x1f1f40  CKQuadTreeLeaf_RecursiveRegistration
//   [ ] 0x1f1f48  CKQuadTreeLeaf_Destroy
//   [ ] 0x1f1f88  CKQuadTreeLeaf_Destructor
//   [ ] 0x1f1fe8  CKQuadTreeLeaf_Destructor_2  [dead]
//   [ ] 0x1f2048  CKQuadTreeLeaf_DeletingDestructor
//
//   [ ] 0x9b0720  CKQuadTreeLeaf_GetClassType  [inline]
//   [ ] 0x9b0728  CKQuadTreeLeaf_GetClassID  [inline]
//   [ ] 0x9b0730  CKQuadTreeLeaf_IsKindOfClass  [inline]
#include "k2000/logic/physics/CKQuadTreeLeaf.h"

#include "k2000/io/IKFile.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CKPFGraphNode.h"

// 0x001f1de0 CKQuadTreeLeaf_Load: a count, then count u16 values, each pushed at the list's head.
int32_t CKQuadTreeLeaf::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        uint16_t value = 0;
        ReadU16LE(file, &value);
        LeafNode* node = new LeafNode;  // FreeListPool (TOC -0x14bc), grown by FreeListPool_Grow 0x244908
        node->m_pNext = nullptr;
        node->m_ui16Value = value;
        node->m_pNext = m_pList;
        m_pList = node;
    }
    return 1;
}

// 0x001f1c00 CKQuadTreeLeaf_FindLeaf
int16_t CKQuadTreeLeaf::FindLeaf(int32_t x, int32_t z, float y, IKSerializable** const* graphNodes) {
    const LeafNode* node = m_pList;
    if (node == nullptr) return -1;
    const float cell = g_pfGridScale.m_cellSize;
    const float zCentre = ppc::fmadds(cell, static_cast<float>(z), 0.001f);
    const float xCentre = ppc::fmadds(static_cast<float>(x), cell, 0.001f);
    IKSerializable** nodes = *graphNodes;
    do {
        const uint16_t index = node->m_ui16Value;
        const CBBox& box = static_cast<CKPFGraphNode*>(nodes[index])->m_Sector.m_box;
        if (box.m_inf.x <= xCentre && box.m_sup.x >= xCentre && box.m_inf.z <= zCentre && box.m_sup.z >= zCentre &&
            box.m_inf.y <= y && box.m_sup.y >= y) {
            return static_cast<int16_t>(index);
        }
        node = node->m_pNext;
    } while (node != nullptr);
    return -1;
}
