// CMultiGeometry.h - a detection shape (key 0x278c, vtable 0xb1c4e0, size 0x20). Original unit:
// CMultiGeometry.cpp. XXL2: K/KServices/KServiceDetect/CMultiGeometry/CMultiGeometry.h (no members).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CMultiGeometryBasic.h"

class CMultiGeometry : public CMultiGeometryBasic {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x9e)
    DOTD_DECLARE_FACTORIES(CMultiGeometry)

    CMultiGeometry() {}  // 0x001aa960 CMultiGeometry_Create: only the vtable
    ~CMultiGeometry() override {}

    // vt+0x2c 0x001aa7e0 CMultiGeometry_Load: CMultiGeometryBasic's.
    int32_t Load(IKFile* file, int32_t type) override;
};
static_assert(CMultiGeometry::kClassKey == 0x278c, "key");
DOTD_ASSERT_SIZE(CMultiGeometry, 0x20);
