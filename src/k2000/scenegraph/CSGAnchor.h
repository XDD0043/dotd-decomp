// CSGAnchor.h - a scene-graph anchor (key 0x10b, vtable 0xb18010, size 0x1c). Original unit: CSGAnchor.cpp
// (0xccaa0-0xcd078). No XXL2 class of this name; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CSGLeaf.h"

class CSGAnchor : public CSGLeaf {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x4)
    DOTD_DECLARE_FACTORIES(CSGAnchor)

    CSGAnchor() {}  // 0x000ccf60 CSGAnchor_Create: CSGLeaf's constructor, then the vtable
    ~CSGAnchor() override {}

    // vt+0x2c 0x000ccfb8 CSGAnchor_Load: CSGLeaf's, then (type 0) one reference.
    int32_t Load(IKFile* file, int32_t type) override;

    IKSerializable* m_pTarget;  // +0x18 _maybe the anchored object
};
static_assert(CSGAnchor::kClassKey == 0x10b, "key");
DOTD_ASSERT_SIZE(CSGAnchor, 0x1c);
DOTD_ASSERT_OFFSET(CSGAnchor, m_pTarget, 0x18);
