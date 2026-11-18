// CKQuadtreeAgentLeaf.h - a quadtree leaf agent (key 0x5e8c, vtable 0xb14dc8, size 0x34). Original unit:
// CKQuadtreeAgentLeaf.cpp (0x46680-0x46ab8). Base: CKQuadtreeAgent (0x600c). No game file holds one. Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKQuadtreeAgent.h"

class CKQuadtreeAgentLeaf : public CKQuadtreeAgent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x17a)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x995898
        return key == 0x5e8c || key == 0x600c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKQuadtreeAgentLeaf)

    CKQuadtreeAgentLeaf() {}  // inlined in 0x000469b0 CKQuadtreeAgentLeaf_Create: the base, then the vtable
    ~CKQuadtreeAgentLeaf() override {}
    // vt+0x2c 0x00046758 CKQuadtreeAgentLeaf_Load: the base's, 1.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x24 0x000467a8 CKQuadtreeAgentLeaf_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).
    // vt+0x10 0x000467d0 CKQuadtreeAgentLeaf_Destroy: the base's KStub_Nop_47df0 (empty).
    // vt+0x50 0x995888 CKQuadtreeAgentLeaf_vf50: the base's UpdateBounds (+0x30 = 0).
};
DOTD_ASSERT_SIZE(CKQuadtreeAgentLeaf, 0x34);
