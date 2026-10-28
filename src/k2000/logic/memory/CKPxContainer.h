// CKPxContainer.h - (key 0x46cc, vtable 0xb1ff18, size 0x28). Original unit: CKPxContainer.cpp. No XXL2
// class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase468C.h"

class CKPxContainer : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x11b)
    DOTD_DECLARE_FACTORIES(CKPxContainer)

    CKPxContainer() {}  // 0x0021cd30 CKPxContainer_Construct: the base, then the vtable
    ~CKPxContainer() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0021cf58 CKPxContainer_Load

    IKSerializable* m_unk18;  // +0x18 three references
    IKSerializable* m_unk1c;  // +0x1c
    IKSerializable* m_unk20;  // +0x20
    uint16_t m_unk24;         // +0x24
    uint16_t m_pad26;
};
DOTD_ASSERT_SIZE(CKPxContainer, 0x28);
DOTD_ASSERT_OFFSET(CKPxContainer, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKPxContainer, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKPxContainer, m_unk24, 0x24);
