// CKBonusConfigTypeStar.h - bonus spawn layout "star" (key 0x2f8c, vtable 0xb19e48, size 0x1c). Original
// unit: CKBonusConfigTypeStar.cpp (0x1275b0-0x128258). Base: CKBonusConfigType (0x2c8c). No XXL2 class
// of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/CKBonusConfigType.h"

class CKBonusConfigTypeStar : public CKBonusConfigType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xbe)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a70a8
        return key == 0x2f8c || key == 0x2c8c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKBonusConfigTypeStar)

    CKBonusConfigTypeStar() {}  // 0x001278c0 CKBonusConfigTypeStar_Create: the base, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001279d0 CKBonusConfigTypeStar_Load
    // vt+0x50 0x00127b78 CKBonusConfigTypeStar_GenerateSpawns_maybe (no LVL010 recording drops through a star).
    void GenerateSpawns(CKBonusData::Entry* entry, const CVector3* pos, const CVector3* dir, const CVector3* base,
                        uint8_t immediate, uint8_t randomAngle) override;
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
