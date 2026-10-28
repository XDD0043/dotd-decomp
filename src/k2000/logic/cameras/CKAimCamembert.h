// CKAimCamembert.h - an aiming sector ("camembert") of the camera (DotD) (key 0x9b4c, vtable 0xb2f918, size 0x40). Original unit: CKAimCamembert.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"

class IKFile;

class CKAimCamembert : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x26d)
    DOTD_DECLARE_FACTORIES(CKAimCamembert)

    // 0x005be7f0 CKAimCamembert_Create: the vtable only (as the dead CKAimCamembert_Construct 0x5be028).
    CKAimCamembert() {}
    ~CKAimCamembert() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005be8c0 CKAimCamembert_Load

    float m_afUnk04[7];    // +0x04 seven floats (90, 2, 28, 0, 10, 1, 1 in LVL010)
    uint32_t m_aUnk20[8];  // +0x20 not set by the constructor nor the Load
};
DOTD_ASSERT_SIZE(CKAimCamembert, 0x40);
DOTD_ASSERT_OFFSET(CKAimCamembert, m_afUnk04, +0x04);
DOTD_ASSERT_OFFSET(CKAimCamembert, m_aUnk20, +0x20);
