// CKHkS08CristalEmitter.h - key 0x2bc2, size 0x88. Original unit: CKHkS08CristalEmitter.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08CristalEmitter : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xaf)
    DOTD_DECLARE_FACTORIES(CKHkS08CristalEmitter)

    // 0x00480920 CKHkS08CristalEmitter_Construct (inlined in 0x00480c30 CKHkS08CristalEmitter_Create): +0x75, +0x74 = 0xff.
    CKHkS08CristalEmitter() {
        m_unk75 = 0xff;
        m_unk74 = 0xff;
    }
    ~CKHkS08CristalEmitter() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004816a0 CKHkS08CristalEmitter_Load

    IKSerializable* m_pUnk20;  // +0x20
    IKSerializable* m_pUnk24;  // +0x24
    uint32_t m_unk28[2];
    IKSerializable* m_pUnk30;  // +0x30
    IKSerializable* m_pUnk34;  // +0x34
    uint32_t m_unk38;
    float m_fUnk3C;  // +0x3c
    IKSerializable* m_pUnk40;  // +0x40
    IKSerializable* m_pUnk44;  // +0x44
    CTriggerStarter m_unk48;  // +0x48
    IKSerializable* m_pUnk50;  // +0x50
    float m_fUnk54;  // +0x54
    uint32_t m_unk58;
    IKSerializable* m_pUnk5C;  // +0x5c
    uint32_t m_unk60;
    IKSerializable* m_pUnk64;  // +0x64
    IKSerializable* m_pUnk68;  // +0x68
    uint32_t m_unk6C[2];
    uint8_t m_unk74;  // +0x74 constructor 0xff
    uint8_t m_unk75;  // +0x75 constructor 0xff
    uint8_t m_unk76[18];
};
DOTD_ASSERT_SIZE(CKHkS08CristalEmitter, 0x88);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_fUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_unk75, 0x75);
