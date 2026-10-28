// CKLightningBoltNodeFx.h - the lightning-bolt effect node (key 0xa60c, vtable 0xb2e0b0, size 0x250).
// Original unit: CKLightningBoltNodeFx.cpp. Its data is CKLightningBoltFxData (0xa64c). Not in XXL2; names
// ours. Only the words the constructor and Load touch are named; the rest is run-time state.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/util/TVector.h"

class CKLightningBoltNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x298)
    DOTD_DECLARE_FACTORIES(CKLightningBoltNodeFx)

    CKLightningBoltNodeFx();  // inlined in 0x0057b710 CKLightningBoltNodeFx_Create
    ~CKLightningBoltNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0057bae0 CKLightningBoltNodeFx_Load
    // vt+0x30 PostLoad 0x57c3c8 (stays the default in C2.1).

    IKSerializable* m_pFxData;   // +0x14 the inline GetFxData/SetFxData (0x9cb0b8/0x9cb0c0) use it
    uint8_t m_unk18;             // +0x18
    uint8_t m_pad19[3];
    uint32_t m_unk1c;            // +0x1c (LVL010: 2)
    uint32_t m_unk20;            // +0x20 (LVL010: 100)
    uint32_t m_unk24[12];        // +0x24 run-time state
    TVector<void*, 1> m_unk54;   // +0x54 the constructor: null, 1, 0 (element type unknown)
    uint32_t m_unk60[124];       // +0x60 run-time state
};
static_assert(CKLightningBoltNodeFx::kClassKey == 0xa60c, "key");
DOTD_ASSERT_SIZE(CKLightningBoltNodeFx, 0x250);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_unk54, 0x54);
