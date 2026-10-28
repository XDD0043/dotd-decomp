// CKFilterNode2dFx.h - a colour filter on a 2D node (key 0x19cc, vtable 0xb1cb48, size 0x3c). Original
// unit: CKFilterNode2dFx.cpp. XXL2: K/KServices/KServiceFx/Effects/CKFilterNode2dFx.h, the same members
// (with DotD's 0x24-byte CSmoothedCColorLinear the PS3 size is exactly XXL2's layout).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/CSmoothedCColorLinear.h"
#include "k2000/fx/IKNode2dFx.h"

class CKFilterNode2dFx : public IKNode2dFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x67)
    DOTD_DECLARE_FACTORIES(CKFilterNode2dFx)

    CKFilterNode2dFx() {}  // inlined in 0x001b9620 CKFilterNode2dFx_Create: the IKNode2dFx part only
    ~CKFilterNode2dFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b94a8 CKFilterNode2dFx_Load

    IKSerializable* m_pFilterData;   // +0x14 XXL2 CKFilterFxData*; not set by the constructor or Load
    CSmoothedCColorLinear m_sColor;  // +0x18
};
static_assert(CKFilterNode2dFx::kClassKey == 0x19cc, "key");
DOTD_ASSERT_SIZE(CKFilterNode2dFx, 0x3c);
DOTD_ASSERT_OFFSET(CKFilterNode2dFx, m_pFilterData, 0x14);
DOTD_ASSERT_OFFSET(CKFilterNode2dFx, m_sColor, 0x18);
