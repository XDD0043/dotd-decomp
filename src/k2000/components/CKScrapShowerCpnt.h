// CKScrapShowerCpnt.h - a scrap shower's emitters (key 0x5c6, vtable 0xb286c0, size 0x20; an IKMecaCpnt).
// Original unit: CKScrapShowerCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKMecaCpntBase.h"

class CKScrapShowerCpnt : public IKMecaCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x17)
    DOTD_DECLARE_FACTORIES(CKScrapShowerCpnt)

    // 8 bytes (OperatorNewArray(n * 8), no cookie): a reference and a byte the Load sets to 1.
    struct Entry {
        IKSerializable* m_pRef;  // +0x00 (LVL060: refs of key 0x486, CKShadowCpnt)
        uint8_t m_bEnabled;      // +0x04 _maybe; 1 after the Load
        uint8_t m_pad05[3];
    };

    CKScrapShowerCpnt() {}  // 0x004a6de0 CKScrapShowerCpnt_Create: the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004a7138 CKScrapShowerCpnt_Load

    Entry* m_aEntries;         // +0x04
    uint8_t m_ui8NbEntries;    // +0x08
    uint8_t m_pad09[3];
    IKSerializable* m_pUnk0c;  // +0x0c reference, read first
    IKSerializable* m_pUnk10;  // +0x10 reference
    IKSerializable* m_pUnk14;  // +0x14 reference, read last
    float m_unk18;             // +0x18 (LVL060: 0.5)
    float m_unk1c;             // +0x1c (LVL060: 5.0)
};
DOTD_ASSERT_SIZE(CKScrapShowerCpnt::Entry, 0x8);
DOTD_ASSERT_SIZE(CKScrapShowerCpnt, 0x20);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_aEntries, 0x04);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_ui8NbEntries, 0x08);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_pUnk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_unk18, 0x18);
