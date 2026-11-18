// CKQuadtreeAgentBranch.h - a quadtree branch agent: its child agents and their joint bounds (key 0x5e4c, vtable
// 0xb14d68, size 0x40). Original unit: CKQuadtreeAgentBranch.cpp (0x45500-0x46680). Base: CKQuadtreeAgent (0x600c).
// No game file holds one. Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKQuadtreeAgent.h"
#include "k2000/util/TVector.h"

class CKQuadtreeAgentBranch : public CKQuadtreeAgent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x179)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x995850
        return key == 0x5e4c || key == 0x600c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKQuadtreeAgentBranch)

    // Inlined in 0x000460b8 CKQuadtreeAgentBranch_Create (and CreateArray): the base, the vtable, the child list
    // (null, 1, 0).
    CKQuadtreeAgentBranch() {
        m_children.m_pBlock = nullptr;
        m_children.m_ui32NbElt = 1;
        m_children.m_ui32NbUsedElt = 0;
    }
    // 0x00045c90 CKQuadtreeAgentBranch_Destructor (and _2 0x45d00, the deleting 0x45848): the child list's block freed,
    // its length and block cleared, then the base's.
    ~CKQuadtreeAgentBranch() override;
    // vt+0x2c 0x000455d8 CKQuadtreeAgentBranch_Load: the base's, then (level data only) the child count and the
    // children (references; the block grows to count + 1 when it is too small).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x000457e8 CKQuadtreeAgentBranch_Destroy: the base's (KStub_Nop_47df0), then the child list freed.
    void Destroy() override;
    // vt+0x24 0x000457c0 CKQuadtreeAgentBranch_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).
    // vt+0x50 0x00045a20 CKQuadtreeAgentBranch_vf50: the bounds the union of the children's (each dirty child updated
    // first, vt+0x50; a child with the empty bounds left out); the empty bounds (-FLT_MAX, -FLT_MAX) for none.
    void UpdateBounds() override;

    TVector<CKQuadtreeAgent*, 1> m_children;  // +0x34 the constructor: null, 1, 0
};
DOTD_ASSERT_SIZE(CKQuadtreeAgentBranch, 0x40);
DOTD_ASSERT_OFFSET(CKQuadtreeAgentBranch, m_children, 0x34);
