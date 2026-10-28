// CKQuadTreeBranch.h - a branch of the navigation quadtree (key 0x1acc, vtable 0xb1e6d8, size 0x1c), and
// its unregistered base KBase16CC (no fields). Original unit: CKQuadTreeBranch.cpp (0x1f14a0-...). No
// XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

// key 0x16cc: the vtable only.
class KBase16CC : public IKSerializable {
public:
    // vt+0x50 (CKQuadTreeBranch_FindLeaf 0x1f1530 / CKQuadTreeLeaf_FindLeaf 0x1f1c00): the index of the path-finding
    // graph node (a sector) at the cell (x, z) whose box holds the point, -1 when none. `graphNodes` points at the
    // service's node array pointer.
    virtual int16_t FindLeaf(int32_t x, int32_t z, float y, IKSerializable** const* graphNodes) = 0;
};

class CKQuadTreeBranch : public KBase16CC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x6b)
    DOTD_DECLARE_FACTORIES(CKQuadTreeBranch)

    // 0x001f14f0 (Ghidra CKQuadTreeRoot_ConstructBase_maybe; also inlined in CKQuadTreeBranch_Create).
    CKQuadTreeBranch() {
        m_apChildren[3] = nullptr;
        m_apChildren[0] = nullptr;
        m_apChildren[2] = nullptr;
        m_apChildren[1] = nullptr;
    }
    ~CKQuadTreeBranch() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f1878 CKQuadTreeBranch_Load
    // vt+0x50 0x001f1530 CKQuadTreeBranch_FindLeaf: the child of the quadrant (x against m_unk14, z against
    // m_unk18) answers.
    int16_t FindLeaf(int32_t x, int32_t z, float y, IKSerializable** const* graphNodes) override;

    IKSerializable* m_apChildren[4];  // +0x04 branches or leaves (CKQuadTreeLeaf / CKQuadTreeBranch)
    int32_t m_unk14;                  // +0x14
    int32_t m_unk18;                  // +0x18
};
DOTD_ASSERT_SIZE(CKQuadTreeBranch, 0x1c);
DOTD_ASSERT_OFFSET(CKQuadTreeBranch, m_apChildren, 0x04);
DOTD_ASSERT_OFFSET(CKQuadTreeBranch, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKQuadTreeBranch, m_unk18, 0x18);
