// CKInputIconNodeFx.h - the input-icon effect node (key 0x458c, vtable 0xb1d098, size 0x3c). Original unit:
// CKInputIconNodeFx.cpp. Its data is CKInputIconFxData (0x45cc). Not in XXL2; names ours. Load reads only the
// IKNodeFx part.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKInputIconNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x116)
    DOTD_DECLARE_FACTORIES(CKInputIconNodeFx)

    CKInputIconNodeFx() : m_pFxData(nullptr) {}  // inlined in 0x001c5d48 CKInputIconNodeFx_Create
    ~CKInputIconNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c4a10 CKInputIconNodeFx_Load
    // vt+0x30 PostLoad 0x1c49e8 (stays the default in C2.1).

    IKSerializable* m_pFxData;   // +0x14 the inline GetFxData (0x9ac798); the constructor sets 0
    uint32_t m_unk18[9];         // +0x18 run-time state
};
static_assert(CKInputIconNodeFx::kClassKey == 0x458c, "key");
DOTD_ASSERT_SIZE(CKInputIconNodeFx, 0x3c);
DOTD_ASSERT_OFFSET(CKInputIconNodeFx, m_pFxData, 0x14);
