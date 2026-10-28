// CKBonusConfigTypeCone.h - bonus spawn layout "cone" (key 0x2d0c, vtable 0xb19ea8, size 0x18). Original
// unit: CKBonusConfigTypeCone.cpp (0x128258-0x128e18). Base: CKBonusConfigType (0x2c8c). No XXL2 class
// of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKBonusConfigType.h"

class CKBonusConfigTypeCone : public CKBonusConfigType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb4)
    DOTD_DECLARE_FACTORIES(CKBonusConfigTypeCone)

    CKBonusConfigTypeCone() {}  // 0x00128620 CKBonusConfigTypeCone_Create: the base, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00128678 CKBonusConfigTypeCone_Load
    void GenerateSpawns() override {}                   // vt+0x50 0x1287e8  STUB(C1.6)
    int32_t GetLayoutType() override { return 0; }      // vt+0x54 0x9a7120

    float m_unk08;  // +0x08
    float m_unk0c;  // +0x0c
    float m_unk10;  // +0x10
    float m_unk14;  // +0x14
};
DOTD_ASSERT_SIZE(CKBonusConfigTypeCone, 0x18);
DOTD_ASSERT_OFFSET(CKBonusConfigTypeCone, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKBonusConfigTypeCone, m_unk14, 0x14);
