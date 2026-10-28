// CKHkS08TuningFork.h - key 0x2d42, size 0x174. Original unit: CKHkS08TuningFork.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08TuningFork : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb5)
    DOTD_DECLARE_FACTORIES(CKHkS08TuningFork)

    // 0x004ce218 CKHkS08TuningFork_Construct (inlined in 0x004cf0f0 CKHkS08TuningFork_Create): +0x131, +0x130 = 0xff.
    CKHkS08TuningFork() {
        m_unk131 = 0xff;
        m_unk130 = 0xff;
    }
    ~CKHkS08TuningFork() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004cfbb8 CKHkS08TuningFork_Load

    IKSerializable* m_pUnk20;  // +0x20
    IKSerializable* m_pUnk24;  // +0x24
    uint32_t m_unk28;
    uint32_t m_unk2C;  // +0x2c
    IKSerializable* m_pUnk30;  // +0x30
    float m_fUnk34;  // +0x34
    uint32_t m_unk38;
    float m_fUnk3C;  // +0x3c
    uint32_t m_unk40;
    float m_fUnk44;  // +0x44
    uint32_t m_unk48;
    IKSerializable* m_pUnk4C;  // +0x4c
    IKSerializable* m_pUnk50;  // +0x50
    IKSerializable* m_pUnk54;  // +0x54
    IKSerializable* m_pUnk58;  // +0x58
    IKSerializable* m_pUnk5C;  // +0x5c
    IKSerializable* m_pUnk60;  // +0x60
    uint32_t m_unk64;
    float m_fUnk68;  // +0x68
    float m_fUnk6C;  // +0x6c
    uint32_t m_unk70[3];
    IKSerializable* m_pUnk7C;  // +0x7c
    uint32_t m_unk80;
    IKSerializable* m_pUnk84;  // +0x84
    uint32_t m_unk88;
    IKSerializable* m_pUnk8C;  // +0x8c
    uint32_t m_unk90;
    IKSerializable* m_pUnk94;  // +0x94
    IKSerializable* m_pUnk98;  // +0x98
    uint32_t m_unk9C;
    float m_fUnkA0;  // +0xa0
    float m_fUnkA4;  // +0xa4
    float m_fUnkA8;  // +0xa8
    float m_fUnkAC;  // +0xac
    float m_fUnkB0;  // +0xb0
    float m_fUnkB4;  // +0xb4
    float m_fUnkB8;  // +0xb8
    float m_fUnkBC;  // +0xbc
    float m_fUnkC0;  // +0xc0
    float m_fUnkC4;  // +0xc4
    float m_fUnkC8;  // +0xc8
    float m_fUnkCC;  // +0xcc
    float m_fUnkD0;  // +0xd0
    float m_fUnkD4;  // +0xd4
    float m_fUnkD8;  // +0xd8
    IKSerializable* m_pUnkDC;  // +0xdc
    IKSerializable* m_pUnkE0;  // +0xe0
    IKSerializable* m_pUnkE4;  // +0xe4
    float m_fUnkE8;  // +0xe8
    float m_fUnkEC;  // +0xec
    uint8_t m_unkF0;  // +0xf0
    uint8_t m_unkF1;  // +0xf1
    uint8_t m_unkF2[2];
    float m_fUnkF4;  // +0xf4
    float m_fUnkF8;  // +0xf8
    uint8_t m_unkFC;  // +0xfc
    uint8_t m_unkFD;  // +0xfd
    uint8_t m_unkFE[2];
    IKSerializable* m_pUnk100;  // +0x100
    float m_fUnk104;  // +0x104
    float m_fUnk108;  // +0x108
    float m_fUnk10C;  // +0x10c
    float m_fUnk110;  // +0x110
    IKSerializable* m_pUnk114;  // +0x114
    float m_fUnk118;  // +0x118
    float m_fUnk11C;  // +0x11c
    uint32_t m_unk120[2];
    float m_fUnk128;  // +0x128
    uint32_t m_unk12C;
    uint8_t m_unk130;  // +0x130 constructor 0xff
    uint8_t m_unk131;  // +0x131 constructor 0xff
    uint8_t m_unk132[34];
    CTriggerStarter m_unk154;  // +0x154
    CTriggerStarter m_unk15C;  // +0x15c
    CTriggerStarter m_unk164;  // +0x164
    CTriggerStarter m_unk16C;  // +0x16c
};
DOTD_ASSERT_SIZE(CKHkS08TuningFork, 0x174);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkB8, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkD0, 0xd0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkF1, 0xf1);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkFD, 0xfd);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk100, 0x100);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk108, 0x108);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk10C, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk114, 0x114);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk118, 0x118);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk11C, 0x11c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk128, 0x128);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk131, 0x131);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk15C, 0x15c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk16C, 0x16c);
