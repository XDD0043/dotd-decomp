// CSGBkgRootNode.h - the root node of the background (key 0x28b, vtable 0xb18088, size 0x24). Original
// unit: CSGBkgRootNode.cpp (0xcd078-0xcd528). Not in XXL2. No members of its own.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

class CSGBkgRootNode : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0xa)
    DOTD_DECLARE_FACTORIES(CSGBkgRootNode)

    CSGBkgRootNode() {}  // inlined in 0x000cd4d0 CSGBkgRootNode_Create: InitializeCNode, then the vtable
    ~CSGBkgRootNode() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000cd1b8 CSGBkgRootNode_Load
};
static_assert(CSGBkgRootNode::kClassKey == 0x28b, "key");
DOTD_ASSERT_SIZE(CSGBkgRootNode, 0x24);
