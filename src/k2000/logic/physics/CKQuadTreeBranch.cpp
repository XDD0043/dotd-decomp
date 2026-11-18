// CKQuadTreeBranch.cpp - reconstructed original translation unit 0x1f14a0-0x1f1a58 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKQuadTreeBranch  key 0x1acc  category Logic  size 0x1c  vtable 0xb1e6d8
// Other owners: CKQuadTreeRoot (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f14a0  CKQuadTreeBranch_Delete
//   [x] 0x1f14f0  CKQuadTreeRoot_ConstructBase_maybe
//   [ ] 0x1f1510  CKQuadTreeRoot_ConstructBase_2_maybe  [dead]
//   [x] 0x1f1530  CKQuadTreeBranch_FindLeaf
//   [ ] 0x1f1628  RegisterCKQuadTreeBranchClass
//   [ ] 0x1f16a0  _GLOBAL__I_1f16a0
//   [x] 0x1f16b0  CKQuadTreeBranch_DeleteArray
//   [ ] 0x1f1758  CKQuadTreeBranch_Save
//   [x] 0x1f1760  CKQuadTreeBranch_RecursiveRegistration  (IKSerializable's: returns 1)
//   [x] 0x1f1768  CKQuadTreeBranch_CreateArray
//   [x] 0x1f1820  CKQuadTreeBranch_Create
//   [x] 0x1f1870  CKQuadTreeBranch_Destroy  (empty)
//   [x] 0x1f1878  CKQuadTreeBranch_Load
//   [x] 0x1f19d0  CKQuadTreeBranch_DeletingDestructor  (the destructor; delete)
//   [x] 0x1f1a18  CKQuadTreeBranch_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1f1a38  CKQuadTreeBranch_Destructor  (C++ destructor chain: vtable stores only)
//
//   [ ] 0x9b0690  CKQuadTreeBranch_GetClassType  [inline]
//   [ ] 0x9b0698  CKQuadTreeBranch_GetClassID  [inline]
//   [ ] 0x9b06a0  CKQuadTreeBranch_IsKindOfClass  [inline]
//   [ ] 0x9b06c8  KBase16CC_DeletingDestructor  [inline]
//   [ ] 0x9b0708  KBase16CC_vf0  [inline]
#include "k2000/logic/physics/CKQuadTreeBranch.h"

#include "k2000/io/IKFile.h"

// 0x001f1878 CKQuadTreeBranch_Load
int32_t CKQuadTreeBranch::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadObjectRefArray(file, m_apChildren, 4);
    ReadS32LE(file, &m_unk14);
    ReadS32LE(file, &m_unk18);
    return 1;
}

// 0x001f1530 CKQuadTreeBranch_FindLeaf: children 0, 1 for x below the centre (z below, z not below), 2, 3 for
// x at or above it.
int16_t CKQuadTreeBranch::FindLeaf(int32_t x, int32_t z, float y, IKSerializable** const* graphNodes) {
    IKSerializable* child;
    if (x < m_unk14) {
        child = z < m_unk18 ? m_apChildren[0] : m_apChildren[1];
    } else {
        child = z < m_unk18 ? m_apChildren[2] : m_apChildren[3];
    }
    return static_cast<KBase16CC*>(child)->FindLeaf(x, z, y, graphNodes);
}
