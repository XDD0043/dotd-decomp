// CKSekensMarker.h - a marker in a sekens (sequence) (key 0x660c, vtable 0xb1eb30, size 0x10). Original
// unit: CKSekensMarker.cpp. DotD only; it adds nothing to CKSekensElement.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKSekensElement.h"

class CKSekensMarker : public CKSekensElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x198)
    DOTD_DECLARE_FACTORIES(CKSekensMarker)

    CKSekensMarker() { m_fTime = 0.0f; }  // 0x001f8210 CKSekensMarker_Construct: +4 = 0
    ~CKSekensMarker() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f80c8 CKSekensMarker_Load
    int32_t IsKindOfClass(uint32_t key) override { return key == kClassKey || key == 0x658c || key == 0xc; }  // 0x9b0ed8
    uint8_t Vf50() override { return 1; }                       // vt+0x50 0x009b0f10
};
DOTD_ASSERT_SIZE(CKSekensMarker, 0x10);
