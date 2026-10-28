// CKBlurNodeFx.h - the blur effect node (key 0x30c, vtable 0xb2dd80, size 0x20). Original unit:
// CKBlurNodeFx.cpp. Its data is CKBlurFxData (0x28c). Not in XXL2; names ours. Load reads only the IKNodeFx
// part.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKBlurNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc)
    DOTD_DECLARE_FACTORIES(CKBlurNodeFx)

    CKBlurNodeFx() {}  // inlined in 0x00572188 CKBlurNodeFx_Create: the IKNodeFx part only
    ~CKBlurNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00571dc0 CKBlurNodeFx_Load
    // vt+0x30 PostLoad 0x571c90 (stays the default in C2.1).

    uint32_t m_unk14;            // +0x14
    IKSerializable* m_pFxData;   // +0x18 the inline GetFxData (0x9cad50) returns it
    uint32_t m_unk1c;            // +0x1c
};
static_assert(CKBlurNodeFx::kClassKey == 0x30c, "key");
DOTD_ASSERT_SIZE(CKBlurNodeFx, 0x20);
DOTD_ASSERT_OFFSET(CKBlurNodeFx, m_pFxData, 0x18);
