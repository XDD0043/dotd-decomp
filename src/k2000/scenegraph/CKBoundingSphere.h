// CKBoundingSphere.h - a collision sphere (key 0x38b, vtable 0xb12fa0, size 0x2c). Original unit:
// CKBoundingSphere.cpp (0xd6e60-0xd7160). XXL2: K/KModules/KGL/SceneGraph/KBoundingVolume/
// CKBoundingSphere.h, no members of its own (the radius is IKBoundingVolume's).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

class CKBoundingSphere : public IKBoundingVolume {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0xe)
    DOTD_DECLARE_FACTORIES(CKBoundingSphere)

    CKBoundingSphere() {}  // inlined in 0x000d70c8 CKBoundingSphere_Create (no stores of its own)
    ~CKBoundingSphere() override {}

    int32_t GetShapeType() const override { return kSphere; }  // vt+0x70 0x00d6eb0 CKBoundingSphere_GetShapeType_maybe

    // vt+0x2c 0x00991eb0 CKBoundingSphere_Load (out of line from this header): IKBoundingVolume's Load,
    // inlined; the same code as 0x00991ca0.
    int32_t Load(IKFile* file, int32_t type) override { return IKBoundingVolume::Load(file, type); }
};
static_assert(CKBoundingSphere::kClassKey == 0x38b, "key");
DOTD_ASSERT_SIZE(CKBoundingSphere, 0x2c);
