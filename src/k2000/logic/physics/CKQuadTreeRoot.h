// CKQuadTreeRoot.h - the root of the navigation quadtree (key 0x18cc, vtable 0xb1e7f8, size 0x24).
// Original unit: CKQuadTreeRoot.cpp. CKSrvPathFinding embeds one at +0x24. No XXL2 class; the names are
// ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/physics/CKQuadTreeBranch.h"

class CKQuadTreeRoot : public CKQuadTreeBranch {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x63)
    DOTD_DECLARE_FACTORIES(CKQuadTreeRoot)

    // 0x001f2338 CKQuadTreeRoot_Construct (= 0x1f22e8 NavSectorQuadTree_Construct_maybe): the branch
    // constructor, then the same four children cleared again; +0x1c and +0x20 are left alone.
    CKQuadTreeRoot() {
        m_apChildren[3] = nullptr;
        m_apChildren[0] = nullptr;
        m_apChildren[2] = nullptr;
        m_apChildren[1] = nullptr;
    }
    ~CKQuadTreeRoot() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f2620 CKQuadTreeRoot_Load
    // 0x001f2430 NavSectorQuadTree_FindSector_maybe: the cell of `position` (x and z times the grid scale,
    // floored) inside the tree's extent (centre m_unk14/m_unk18, half-sizes m_unk1c/m_unk20) is looked up with
    // FindLeaf; 0xffff outside it or when no sector holds the point.
    uint16_t FindSector(const float* position, IKSerializable** const* graphNodes);

    int32_t m_unk1c;  // +0x1c
    int32_t m_unk20;  // +0x20
};
DOTD_ASSERT_SIZE(CKQuadTreeRoot, 0x24);
DOTD_ASSERT_OFFSET(CKQuadTreeRoot, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKQuadTreeRoot, m_unk20, 0x20);
