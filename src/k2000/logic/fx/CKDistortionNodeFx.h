// CKDistortionNodeFx.h - the screen distortion effect node (key 0x38cc, vtable 0xb1c6a8, size 0x2c).
// Original unit: CKDistortionNodeFx.cpp. Its data is CKDistortionFxData (0x394c). Not in XXL2; names ours.
// Load reads only the IKNodeFx part.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKDistortionNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xe3)
    DOTD_DECLARE_FACTORIES(CKDistortionNodeFx)

    CKDistortionNodeFx() {}  // inlined in 0x001af338 CKDistortionNodeFx_Create: the IKNodeFx part only
    ~CKDistortionNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001af248 CKDistortionNodeFx_Load
    // vt+0x30 PostLoad 0x1af110 (stays the default in C2.1).

    uint32_t m_unk14;            // +0x14
    IKSerializable* m_pFxData;   // +0x18 the inline GetFxData (0x9ab570) returns it
    uint32_t m_unk1c[4];         // +0x1c run-time state
};
static_assert(CKDistortionNodeFx::kClassKey == 0x38cc, "key");
DOTD_ASSERT_SIZE(CKDistortionNodeFx, 0x2c);
DOTD_ASSERT_OFFSET(CKDistortionNodeFx, m_pFxData, 0x18);
