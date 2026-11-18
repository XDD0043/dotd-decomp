// CKQuadTreeRoot.cpp - reconstructed original translation unit 0x1f20d0-0x1f2868 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKQuadTreeRoot  key 0x18cc  category Logic  size 0x24  vtable 0xb1e7f8
// Other owners: NavSectorQuadTree (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f20d0  CKQuadTreeRoot_Delete
//   [ ] 0x1f2120  RegisterCKQuadTreeRootClass
//   [ ] 0x1f2198  _GLOBAL__I_1f2198
//   [ ] 0x1f21a8  CKQuadTreeRoot_Save
//   [x] 0x1f21d0  CKQuadTreeRoot_RecursiveRegistration  (inherited: CKQuadTreeBranch's, returns 1)
//   [x] 0x1f21f8  CKQuadTreeRoot_Destroy  (header)
//   [x] 0x1f2240  CKQuadTreeRoot_DeletingDestructor  (the destructor; delete)
//   [x] 0x1f2288  CKQuadTreeRoot_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1f22b8  CKQuadTreeRoot_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1f22e8  NavSectorQuadTree_Construct_maybe
//   [x] 0x1f2338  CKQuadTreeRoot_Construct
//   [x] 0x1f2388  CKQuadTreeRoot_DeleteArray
//   [x] 0x1f2430  NavSectorQuadTree_FindSector_maybe
//   [x] 0x1f2620  CKQuadTreeRoot_Load
//   [x] 0x1f2710  CKQuadTreeRoot_CreateArray
//   [x] 0x1f27f8  CKQuadTreeRoot_Create
//
//   [ ] 0x9b0758  CKQuadTreeRoot_IsKindOfClass  [inline]
//   [ ] 0x9b0790  CKQuadTreeRoot_GetClassType  [inline]
//   [ ] 0x9b0798  CKQuadTreeRoot_GetClassID  [inline]
#include <cstring>

#include "k2000/logic/physics/CKQuadTreeRoot.h"

#include "k2000/io/IKFile.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKSrvPathFinding.h"

// 0x001f2620 CKQuadTreeRoot_Load
int32_t CKQuadTreeRoot::Load(IKFile* file, int32_t type) {
    CKQuadTreeBranch::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_unk1c);
    ReadS32LE(file, &m_unk20);
    return 1;
}

namespace {
// The inlined floor of the grid cell: the truncated value, one lower for a negative fraction (only below 2^24,
// where floats have fractions). `scaled` is the position times the grid scale.
int32_t FloorCell(float scaled) {
    int32_t cell = ppc::fctiwz(scaled);
    const float difference = static_cast<float>(cell) - scaled;
    uint32_t bits;
    std::memcpy(&bits, &scaled, 4);
    if (difference != 0.0f && (bits & 0x7f800000u) < 0x4b800000u) {
        float floored = static_cast<float>(cell);
        if (static_cast<int32_t>(bits) < 0) floored = static_cast<float>(cell - 1);
        cell = ppc::fctiwz(floored);
    }
    return cell;
}
}  // namespace

// 0x001f2430 NavSectorQuadTree_FindSector_maybe
uint16_t CKQuadTreeRoot::FindSector(const float* position, IKSerializable** const* graphNodes) {
    const float scale = g_pfGridScale.m_invCellSize;
    const int32_t x = FloorCell(scale * position[0]);
    const int32_t z = FloorCell(scale * position[2]);
    if (m_unk14 + m_unk1c > x && m_unk14 - m_unk1c <= x && m_unk18 + m_unk20 > z && m_unk18 - m_unk20 <= z) {
        return static_cast<uint16_t>(FindLeaf(x, z, position[1], graphNodes));
    }
    return 0xffff;
}
