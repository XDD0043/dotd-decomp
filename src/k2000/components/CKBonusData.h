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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a7040
        return key == 0x686 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKBonusData)

    // 0x20 bytes (OperatorNewArray(count << 5)); CKBonusData_LoadEntry reads six byte-swapped words.
    // +0x14 and +0x18 are not read. CKSrvBonus_SpawnBonuses_maybe / the config types' GenerateSpawns use them.
    struct Entry {
        uint32_t m_unk00;  // +0x00 the bonus kind (CKSrvBonus vt+0xa8)
        uint32_t m_unk04;  // +0x04 the least count
        uint32_t m_unk08;  // +0x08 the most count
        uint32_t m_unk0c;  // +0x0c the spawn layout (CKSrvBonus +0x20 index; a word, 0x3f800000 in LVL000: none)
        uint32_t m_unk10;  // +0x10 the count mode: 0 random in [+0x04, +0x08], 1 a share of a drawn total
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
    void Destroy() override;  // vt+0x10 0x00127090 CKBonusData_Destroy: the entries deleted

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
