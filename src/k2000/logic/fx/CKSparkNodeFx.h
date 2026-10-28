// CKSparkNodeFx.h - the spark effect node (key 0x244c, vtable 0xb1d970, size 0x1c). Original unit:
// CKSparkNodeFx.cpp (0x1d3e68-0x1d4890). Its data is CKSparkFxData (0x24cc). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKSparkNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x91)
    DOTD_DECLARE_FACTORIES(CKSparkNodeFx)

    CKSparkNodeFx() {}  // inlined in 0x001d4640 CKSparkNodeFx_Create: the IKNodeFx part only
    ~CKSparkNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d44c8 CKSparkNodeFx_Load

    IKSerializable* m_pFxData;  // +0x14 the inline GetFxData/SetFxData (0x9ad438/0x9ad440) use it
    CNode* m_pSparkNode;        // +0x18 Load (type 0) copies m_pNode here (Ghidra draft: CSparkNodeFx*)
};
static_assert(CKSparkNodeFx::kClassKey == 0x244c, "key");
DOTD_ASSERT_SIZE(CKSparkNodeFx, 0x1c);
DOTD_ASSERT_OFFSET(CKSparkNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKSparkNodeFx, m_pSparkNode, 0x18);
