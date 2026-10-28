// CKHkS08Fire.h - a fire hook (key 0x3442, size 0xd8). Original unit: CKHkS08Fire.cpp. No XXL2 class.
// The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08Fire : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd1)
    DOTD_DECLARE_FACTORIES(CKHkS08Fire)

    // 0x004db3d0 CKHkS08Fire_Construct (inlined in 0x004db538 CKHkS08Fire_Create): +0x58 = 0,
    // +0x85/+0x84 = 0xff.
    CKHkS08Fire() {
        m_unk58 = 0;
        m_unk85 = 0xff;
        m_unk84 = 0xff;
    }
    ~CKHkS08Fire() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004db7c8 CKHkS08Fire_Load

    float m_fUnk20;             // +0x20 (3600 in the sample: a duration in seconds_maybe)
    float m_fUnk24;             // +0x24
    uint32_t m_unk28;
    IKSerializable* m_pUnk2C;   // +0x2c
    IKSerializable* m_pUnk30;   // +0x30
    uint32_t m_unk34;
    IKSerializable* m_pUnk38;   // +0x38
    uint32_t m_unk3C;
    IKSerializable* m_pUnk40;   // +0x40
    uint32_t m_unk44;
    IKSerializable* m_pUnk48;   // +0x48
    uint32_t m_unk4C;
    uint8_t m_unk50;            // +0x50
    uint8_t m_unk51[3];
    IKSerializable* m_pUnk54;   // +0x54
    uint32_t m_unk58;           // +0x58 constructor 0
    float m_fUnk5C;             // +0x5c
    float m_fUnk60;             // +0x60
    CMatrix34* m_pMatrix64;     // +0x64 RwMatrixCreate in the Load, then pos, at, up, right from the file
    uint32_t m_unk68;
    CTriggerStarter m_unk6C;    // +0x6c
    CTriggerStarter m_unk74;    // +0x74
    uint8_t m_unk7C;            // +0x7c
    uint8_t m_unk7D;            // +0x7d
    uint8_t m_unk7E;            // +0x7e
    uint8_t m_unk7F;
    uint32_t m_unk80;
    uint8_t m_unk84;            // +0x84 constructor 0xff
    uint8_t m_unk85;            // +0x85 constructor 0xff
    uint8_t m_unk86[2];
    uint32_t m_unk88[8];
    IKSerializable* m_pUnkA8;   // +0xa8
    IKSerializable* m_pUnkAC;   // +0xac
    IKSerializable* m_pUnkB0;   // +0xb0
    IKSerializable* m_pUnkB4;   // +0xb4
    uint32_t m_unkB8[4];
    IKSerializable* m_pUnkC8;   // +0xc8 (paired with +0xa8; +0xcc with +0xac, ...)
    IKSerializable* m_pUnkCC;   // +0xcc
    IKSerializable* m_pUnkD0;   // +0xd0
    IKSerializable* m_pUnkD4;   // +0xd4
};
DOTD_ASSERT_SIZE(CKHkS08Fire, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_fUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_fUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_fUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pMatrix64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkD4, 0xd4);
