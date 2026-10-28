// CSkinGeometry.h - a skinned geometry (key 0xca, vtable 0xb16a68, size 0x30). Original
// unit: CSkinGeometry.cpp. XXL2: K/KModules/KGL/Geometry/CSkinGeometry.h (no members of its own). The
// streamed atomic (chunk 0x14) carries the skin plugin (Renderware/rpskin/RpSkin.h: the geometry's RpSkin, the
// atomic's skin pipeline and hierarchy).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/geometry/CGeometry.h"

class CSkinGeometry : public CGeometry {
public:
    DOTD_CLASS_KEY(kCategoryGeometry, 0x3)
    DOTD_DECLARE_FACTORIES(CSkinGeometry)

    CSkinGeometry() {}  // 0x0008b500 CSkinGeometry_Create: CGeometry's constructor (inlined), then the vtable
    ~CSkinGeometry() override {}

    // vt+0x2c 0x0008b290 CSkinGeometry_Load: CGeometry's.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x0008b2b8 CSkinGeometry_PostLoad: CGeometry's.
    int32_t PostLoad(int32_t type) override;
};
static_assert(CSkinGeometry::kClassKey == 0xca, "key");
DOTD_ASSERT_SIZE(CSkinGeometry, 0x30);

struct RpHAnimHierarchy;
// 0x0008b368 CSkinGeometry_SetHAnimHierarchy_maybe: the geometry's atomic gets the hierarchy (the skin plugin data,
// RpSkinAtomicSetHAnimHierarchy). CAnimatedNode_SetHAnimHierarchy_maybe calls it on every geometry of the node,
// skinned or not, so it takes a CGeometry.
void CSkinGeometry_SetHAnimHierarchy(CGeometry* geometry, RpHAnimHierarchy* hierarchy);
