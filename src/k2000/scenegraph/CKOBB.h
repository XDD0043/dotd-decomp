// CKOBB.h - an oriented collision box (key 0x48b, vtable 0xb18890, size 0x38). Original unit: CKOBB.cpp.
// XXL2: K/KModules/KGL/SceneGraph/KBoundingVolume/CKOBB.h (no members of its own).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/IKBoundingBox.h"

class CKOBB : public IKBoundingBox {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x12)
    DOTD_DECLARE_FACTORIES(CKOBB)

    CKOBB() {}  // 0x000d7fe0 CKOBB_Create: CSGLeaf's constructor, +0x28 and +0x1c cleared, the vtables
    ~CKOBB() override {}

    int32_t GetShapeType() const override { return kOBB; }  // vt+0x70 0x00d7db8 CKOBB_GetShapeType_maybe

    // vt+0x2c 0x009a46d8 CKOBB_Load (out of line from this header): IKBoundingBox's, inlined.
    int32_t Load(IKFile* file, int32_t type) override { return IKBoundingBox::Load(file, type); }
};
static_assert(CKOBB::kClassKey == 0x48b, "key");
DOTD_ASSERT_SIZE(CKOBB, 0x38);
