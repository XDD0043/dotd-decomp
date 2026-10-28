// CKBonusData.h - bonus drop table (key 0x686, vtable 0xb19d90, size 0x14). Original unit:
// CKBonusData.cpp (0x126d20-0x127470). No XXL2 class of this name.
//
// Load (every type): u8 count, count entries of 0x20 bytes read from the last one down
// (CKBonusData_LoadEntry 0x1270d8), then a float and a byte. For a type other than 0 the old entries are
// freed first.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKBonusData : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x1a)
    DOTD_DECLARE_FACTORIES(CKBonusData)

    // 0x20 bytes (OperatorNewArray(count << 5)); CKBonusData_LoadEntry reads six byte-swapped words.
    // +0x14 and +0x18 are not read. Types from the data (_maybe).
    struct Entry {
        uint32_t m_unk00;  // +0x00
        uint32_t m_unk04;  // +0x04
        uint32_t m_unk08;  // +0x08
        float m_unk0c;     // +0x0c (1.0 in LVL000)
        uint32_t m_unk10;  // +0x10
        uint32_t m_unk14;  // +0x14 not read
        uint32_t m_unk18;  // +0x18 not read
        uint32_t m_unk1c;  // +0x1c
    };

    CKBonusData() {}  // 0x00127048 CKBonusData_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001272c8 CKBonusData_Load
    // C1.6 gm: 0x00126d90 CKBonusData_ResetRuntime_maybe: every entry's +0x18 = -1 (CKS08GameManager_Start).
    void ResetRuntime();

    uint8_t m_count;      // +0x04 number of entries
    uint8_t m_pad05[3];
    Entry* m_pEntries;    // +0x08 OperatorNewArray; null without entries
    float m_unk0c;        // +0x0c
    uint8_t m_unk10;      // +0x10
    uint8_t m_pad11[3];
};
DOTD_ASSERT_SIZE(CKBonusData::Entry, 0x20);
DOTD_ASSERT_SIZE(CKBonusData, 0x14);
DOTD_ASSERT_OFFSET(CKBonusData, m_count, 0x04);
DOTD_ASSERT_OFFSET(CKBonusData, m_pEntries, 0x08);
DOTD_ASSERT_OFFSET(CKBonusData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKBonusData, m_unk10, 0x10);
