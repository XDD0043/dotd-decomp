// CKControlableHero.h - (key 0xa88c, vtable 0xb22e40, size 0xc). Original unit: CKControlableHero.cpp
// (0x344758-0x344ef0). Derived straight from IKSerializable. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKControlableHero : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a2)
    DOTD_DECLARE_FACTORIES(CKControlableHero)

    // 0x00344bd0 CKControlableHero_Create: +0x8 = 0, then the vtable.
    CKControlableHero() { m_unk08 = 0; }
    ~CKControlableHero() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00344c10 CKControlableHero_Load

    uint8_t m_unk04;  // +0x04 one byte from the file (LVL010: 0 or 1)
    uint8_t m_pad05[3];
    uint32_t m_unk08;  // +0x08 0 (constructor and Load); the attached hero_maybe (BindAndAttachHero 0x344948)
};
DOTD_ASSERT_SIZE(CKControlableHero, 0xc);
DOTD_ASSERT_OFFSET(CKControlableHero, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKControlableHero, m_unk08, 0x08);
