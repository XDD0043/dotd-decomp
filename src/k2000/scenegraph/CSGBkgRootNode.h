// CSGBkgRootNode.h - the root node of the background (key 0x28b, vtable 0xb18088, size 0x24). Original
// unit: CSGBkgRootNode.cpp (0xcd078-0xcd528). Not in XXL2. No members of its own.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

class CSGBkgRootNode : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0xa)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a25e8
        return key == 0x28b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CSGBkgRootNode)

    CSGBkgRootNode() {}  // inlined in 0x000cd4d0 CSGBkgRootNode_Create: InitializeCNode, then the vtable
    ~CSGBkgRootNode() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000cd1b8 CSGBkgRootNode_Load
    // vt+0x58 0x000cd150 CSGBkgRootNode_Enqueue: CNode's traversal (EnqueueSceneNodeAndChildren 0xcc160) with the
    // scene camera (the camera context's +0x24, the far group's camera) instead of the caller's.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
};
static_assert(CSGBkgRootNode::kClassKey == 0x28b, "key");
DOTD_ASSERT_SIZE(CSGBkgRootNode, 0x24);
