// CKHkS08CristalReceiver.h - key 0x2c02, size 0x94. Original unit: CKHkS08CristalReceiver.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08CristalReceiver : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb0)
    DOTD_DECLARE_FACTORIES(CKHkS08CristalReceiver)

    // 0x00483870 CKHkS08CristalReceiver_Construct (inlined in 0x00483da0 CKHkS08CristalReceiver_Create): +0x81, +0x80 = 0xff.
    CKHkS08CristalReceiver() {
        m_unk81 = 0xff;
        m_unk80 = 0xff;
    }
    ~CKHkS08CristalReceiver() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004846c8 CKHkS08CristalReceiver_Load

    IKSerializable* m_pUnk20;  // +0x20
    IKSerializable* m_pUnk24;  // +0x24
    IKSerializable* m_pUnk28;  // +0x28
    IKSerializable* m_pUnk2C;  // +0x2c
    float m_fUnk30;  // +0x30
    IKSerializable* m_pUnk34;  // +0x34
    IKSerializable* m_pUnk38;  // +0x38
    IKSerializable* m_pUnk3C;  // +0x3c
    uint32_t m_unk40[2];
    IKSerializable* m_pUnk48;  // +0x48
    IKSerializable* m_pUnk4C;  // +0x4c
    uint32_t m_unk50;
    IKSerializable* m_pUnk54;  // +0x54
    IKSerializable* m_pUnk58;  // +0x58
    IKSerializable* m_pUnk5C;  // +0x5c
    IKSerializable* m_pUnk60;  // +0x60
    float m_fUnk64;  // +0x64
    CTriggerStarter m_unk68;  // +0x68
    uint32_t m_unk70[2];
    float m_fUnk78;  // +0x78
    uint32_t m_unk7C;
    uint8_t m_unk80;  // +0x80 constructor 0xff
    uint8_t m_unk81;  // +0x81 constructor 0xff
    uint8_t m_unk82[18];
};
DOTD_ASSERT_SIZE(CKHkS08CristalReceiver, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_fUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_fUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_fUnk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk81, 0x81);
