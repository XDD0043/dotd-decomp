// CKDynBSphereProjectile.h - the collision sphere of a projectile (key 0x18b, vtable 0xb18810, size 0x50).
// Original unit: CKDynBSphereProjectile.cpp (0xd7878-0xd7d68). XXL2: K/KModules/KGL/SceneGraph/
// KBoundingVolume/CKDynBSphereProjectile.h, no members of its own.
//
// CKSrvCollision creates the 50 of the pool (CreateObjectArray(11, 6, 50)) and hands them to the loader
// as non-recreatable instances; LVL000 then loads them in place.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"

class CKDynBSphereProjectile : public CKDynamicBoundingSphere {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x6)
    DOTD_DECLARE_FACTORIES(CKDynBSphereProjectile)

    CKDynBSphereProjectile() {}  // inlined in 0x000d7ae8 CKDynBSphereProjectile_Create (no stores of its own)
    ~CKDynBSphereProjectile() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000d7b80 CKDynBSphereProjectile_Load
};
static_assert(CKDynBSphereProjectile::kClassKey == 0x18b, "key");
DOTD_ASSERT_SIZE(CKDynBSphereProjectile, 0x50);
