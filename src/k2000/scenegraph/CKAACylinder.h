// CKAACylinder.h - a vertical collision cylinder (key 0x60b, vtable 0xb18710, size 0x34). Original unit:
// CKAACylinder.cpp. XXL2: K/KModules/KGL/SceneGraph/KBoundingVolume/CKAACylinder.h, members
// m_fCylinderRadius and m_fCylinderHalfHeight (read in that order).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

class CKAACylinder : public IKBoundingVolume {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x18)
    DOTD_DECLARE_FACTORIES(CKAACylinder)

    CKAACylinder() {}  // 0x000d6740 CKAACylinder_Create: CSGLeaf's constructor, +0x1c and +0x28 cleared
    ~CKAACylinder() override {}

    int32_t GetShapeType() const override { return kCylinder; }  // vt+0x70 0x00d6610 CKAACylinder_GetShapeType_maybe

    // vt+0x2c 0x000d68e8 CKAACylinder_Load: IKBoundingVolume's (inlined), then one 8-byte read.
    int32_t Load(IKFile* file, int32_t type) override;

    float m_fCylinderRadius;      // +0x2c
    float m_fCylinderHalfHeight;  // +0x30
};
static_assert(CKAACylinder::kClassKey == 0x60b, "key");
DOTD_ASSERT_SIZE(CKAACylinder, 0x34);
DOTD_ASSERT_OFFSET(CKAACylinder, m_fCylinderRadius, 0x2c);
DOTD_ASSERT_OFFSET(CKAACylinder, m_fCylinderHalfHeight, 0x30);
