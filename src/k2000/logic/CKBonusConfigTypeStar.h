// CKBonusConfigTypeStar.h - bonus spawn layout "star" (key 0x2f8c, vtable 0xb19e48, size 0x1c). Original
// unit: CKBonusConfigTypeStar.cpp (0x1275b0-0x128258). Base: CKBonusConfigType (0x2c8c). No XXL2 class
// of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKBonusConfigType.h"

class CKBonusConfigTypeStar : public CKBonusConfigType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xbe)
    DOTD_DECLARE_FACTORIES(CKBonusConfigTypeStar)

    CKBonusConfigTypeStar() {}  // 0x001278c0 CKBonusConfigTypeStar_Create: the base, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001279d0 CKBonusConfigTypeStar_Load
    void GenerateSpawns() override {}                   // vt+0x50 0x127b78  STUB(C1.6)
    int32_t GetLayoutType() override { return 1; }      // vt+0x54 0x9a70e0

    float m_unk08;     // +0x08
    float m_unk0c;     // +0x0c
    float m_unk10;     // +0x10
    uint8_t m_unk14;   // +0x14
    uint8_t m_pad15[3];
    float m_unk18;     // +0x18
};
DOTD_ASSERT_SIZE(CKBonusConfigTypeStar, 0x1c);
DOTD_ASSERT_OFFSET(CKBonusConfigTypeStar, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKBonusConfigTypeStar, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKBonusConfigTypeStar, m_unk18, 0x18);
