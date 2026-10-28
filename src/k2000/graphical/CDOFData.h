// CDOFData.h - depth-of-field parameters (key 0x10cd, vtable 0xb17808, size 0x14). Original unit:
// CDOFData.cpp (0xb5c70-0xb6bd8, with CHDRData and CBlurData). XXL2's CDOFData has another layout (no
// members), so the names are ours.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CDOFData : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x43)
    DOTD_DECLARE_FACTORIES(CDOFData)

    CDOFData() {}  // 0x000b6398 CDOFData_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000b64d8 CDOFData_Load

    uint32_t m_unk04;  // +0x04..+0x10 four byte-swapped words (all 0 in LVL000)
    uint32_t m_unk08;
    uint32_t m_unk0c;
    uint32_t m_unk10;
};
DOTD_ASSERT_SIZE(CDOFData, 0x14);
DOTD_ASSERT_OFFSET(CDOFData, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CDOFData, m_unk10, 0x10);
