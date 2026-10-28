// CKAABB.h - an axis-aligned collision box (key 0x44b, vtable 0xb18610, size 0x38). Original unit:
// CKAABB.cpp. XXL2: K/KModules/KGL/SceneGraph/KBoundingVolume/CKAABB.h (no members of its own).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/IKBoundingBox.h"

class CKAABB : public IKBoundingBox {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x11)
    DOTD_DECLARE_FACTORIES(CKAABB)

    CKAABB() {}  // 0x000d6528 CKAABB_Create: CSGLeaf's constructor, +0x28 and +0x1c cleared, the vtables
    ~CKAABB() override {}

    int32_t GetShapeType() const override { return kAABB; }  // vt+0x70 0x00d6300 CKAABB_GetShapeType_maybe

    // vt+0x2c 0x009a35d8 CKAABB_Load (out of line from this header): IKBoundingBox's, inlined.
    int32_t Load(IKFile* file, int32_t type) override { return IKBoundingBox::Load(file, type); }
};
static_assert(CKAABB::kClassKey == 0x44b, "key");
DOTD_ASSERT_SIZE(CKAABB, 0x38);
