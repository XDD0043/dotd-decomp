// CKHkS08Malefor.h - Malefor's hook (key 0x3502, vtable 0xb2a660, size 0x1d4). Original unit:
// CKHkS08Malefor.cpp. No XXL2 class. Derives from CKHkGolem. Values in the comments: LVL120.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkGolem.h"

class CKHkS08Malefor : public CKHkGolem {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd4)
    DOTD_DECLARE_FACTORIES(CKHkS08Malefor)

    // 0x004e2860 CKHkS08Malefor_Construct (inlined in CKHkS08Malefor_Create 0x4e3070): +0xc0 = 0.
    CKHkS08Malefor() { m_unkC0 = 0; }
    ~CKHkS08Malefor() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e3eb8 CKHkS08Malefor_Load

    uint32_t m_unkC0;                   // +0xc0 constructor 0
    uint32_t m_unkC4[7];                // +0xc4
    float m_unkE0;                      // +0xe0 (0.5)
    IKSerializable* m_unkE4;            // +0xe4 reference (read first)
    IKSerializable* m_unkE8;            // +0xe8 reference
    uint8_t m_unkEC;                    // +0xec the +0xf0 count (12)
    uint8_t m_padED[3];
    IKSerializable** m_apUnkF0;         // +0xf0 m_unkEC references (Mem_AllocAligned16)
    IKSerializable* m_apUnkF4[2];       // +0xf4 two references (one array read)
    uint32_t m_unkFC[5];                // +0xfc (0, 1, 10, 1, 10)
    IKSerializable* m_apUnk110[9];      // +0x110 references
    uint32_t m_unk134[3];               // +0x134
    IKSerializable* m_apUnk140[9];      // +0x140 references
    IKSerializable* m_unk164;           // +0x164 reference (PostLoad configures that object)
    uint8_t m_unk168;                   // +0x168
    uint8_t m_pad169[3];
    uint32_t m_unk16C;                  // +0x16c (75)
    uint32_t m_unk170;                  // +0x170 (50)
    IKSerializable* m_apUnk174[5];      // +0x174 references (read one by one)
    IKSerializable* m_unk188;           // +0x188 reference
    IKSerializable* m_unk18C;           // +0x18c reference
    IKSerializable* m_unk190;           // +0x190 reference
    uint32_t m_unk194[16];              // +0x194
};
DOTD_ASSERT_SIZE(CKHkS08Malefor, 0x1d4);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnk140, 0x140);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk16C, 0x16c);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnk174, 0x174);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk194, 0x194);
