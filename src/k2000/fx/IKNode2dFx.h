// IKNode2dFx.h - an effect on a 2D node (key 0x158c, not registered; vtable 0xb1dd50; Ghidra calls it
// CKNode2dFx).
// Original unit: CKNode2dFx.cpp (0x1d84f0-0x1d8898). XXL2: K/KServices/KServiceFx/Effects/IKNode2dFx.h,
// member m_pNode.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKFx.h"

class IKNode2dFx : public IKFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x56)

    IKNode2dFx();  // 0x001d8840 CKNode2dFx_ConstructBase
    ~IKNode2dFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d85a8 CKNode2dFx_Load
    // vt+0x6c 0x009ad980 CKNode2dFx_Stop: stopped and not reserved. (The other 2D slots 0x54-0x64 are not
    // ported; IKFx's are the 3D ones.)
    void Stop() override { m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 1); }

    IKSerializable* m_pNode;  // +0x10 XXL2 IKNode2d* (LVL000: CBillboard2d); the constructor sets 0
};
static_assert(IKNode2dFx::kClassKey == 0x158c, "key");
DOTD_ASSERT_SIZE(IKNode2dFx, 0x14);
DOTD_ASSERT_OFFSET(IKNode2dFx, m_pNode, 0x10);
