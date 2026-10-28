// CKDOFNodeFx.h - the depth-of-field effect (key 0x7fcc, vtable 0xb1c7b8, size 0x20). Original unit:
// CKDOFNodeFx.cpp. Not in XXL2.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKDOFNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1ff)
    DOTD_DECLARE_FACTORIES(CKDOFNodeFx)

    CKDOFNodeFx() {}  // inlined in 0x001b0eb8 CKDOFNodeFx_Create: the IKNodeFx part only
    ~CKDOFNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b10f8 CKDOFNodeFx_Load

    uint32_t m_unk14;            // +0x14 PostLoad (0x1b07d8) sets 0
    // +0x18 the CDOFData reference (LVL000: class 0x10cd); name ours. PostLoad clears its +0x04..+0x10.
    IKSerializable* m_pDOFData;
    uint32_t m_unk1c;            // +0x1c PostLoad sets 0
};
static_assert(CKDOFNodeFx::kClassKey == 0x7fcc, "key");
DOTD_ASSERT_SIZE(CKDOFNodeFx, 0x20);
DOTD_ASSERT_OFFSET(CKDOFNodeFx, m_pDOFData, 0x18);
