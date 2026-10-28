// CSGRootNode.h - the root of a scene graph (key 0x4b, vtable 0xb140b0, size 0x34). Original unit:
// CSGRootNode.cpp (0xd29c8-0xd2e28). XXL2: K/KModules/KGL/SceneGraph/CSGRootNode.h, member m_AABB.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CBBox.h"
#include "k2000/scenegraph/CSGBranch.h"

class CSGRootNode : public CSGBranch {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x1)
    DOTD_DECLARE_FACTORIES(CSGRootNode)

    CSGRootNode() {}  // inlined in 0x000d2ce0 CreateCSGRootNode: the CSGBranch part only
    ~CSGRootNode() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000d2ad0 CSGRootNode_Load
    int32_t PostLoad(int32_t type) override;             // vt+0x30 0x000d2aa8 CSGRootNode_PostLoad: CSGBranch's
    uint32_t GetSectorIndex() override { return 0; }     // vt+0x6c 0x000d2a18 CSGRootNode_GetSectorIndex_maybe

    CBBox m_AABB;  // +0x1c not set by the constructor or Load
};
static_assert(CSGRootNode::kClassKey == 0x4b, "key");
DOTD_ASSERT_SIZE(CSGRootNode, 0x34);
DOTD_ASSERT_OFFSET(CSGRootNode, m_AABB, 0x1c);
