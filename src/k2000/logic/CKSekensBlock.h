// CKSekensBlock.h - a block of a sekens (sequence): a text shown for a time (key 0x65cc, vtable
// 0xb1ea70, size 0x1c). Original unit: CKSekensBlock.cpp. DotD only as a class (XXL2 keeps SSekensBlock
// records in CKSekens); the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKSekensElement.h"

class CKSekensBlock : public CKSekensElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x197)
    DOTD_DECLARE_FACTORIES(CKSekensBlock)

    CKSekensBlock() { m_pText = nullptr; }  // 0x001f71d8 CKSekensBlock_Construct
    ~CKSekensBlock() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f7388 CKSekensBlock_Load
    int32_t IsKindOfClass(uint32_t key) override { return key == kClassKey || key == 0x658c || key == 0xc; }  // 0x9b0e40
    uint8_t Vf50() override { return m_unk18; }                 // vt+0x50 0x001f7068
    uint8_t Vf58() override { return m_unk19; }                 // vt+0x58 0x009b0e78
    IKSerializable* Vf5C() override { return m_pText; }         // vt+0x5c 0x009b0e80

    IKSerializable* m_pText;  // +0x10 CKStdText in the files
    float m_unk14;            // +0x14 (-1.0 in the samples)
    uint8_t m_unk18;          // +0x18
    uint8_t m_unk19;          // +0x19
    uint8_t m_pad1a[2];
};
DOTD_ASSERT_SIZE(CKSekensBlock, 0x1c);
DOTD_ASSERT_OFFSET(CKSekensBlock, m_pText, 0x10);
DOTD_ASSERT_OFFSET(CKSekensBlock, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKSekensBlock, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKSekensBlock, m_unk19, 0x19);
