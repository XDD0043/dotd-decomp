// CKHkS08CristalKey.h - key 0x2b42, size 0x4c. Original unit: CKHkS08CristalKey.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08CristalKey : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xad)
    DOTD_DECLARE_FACTORIES(CKHkS08CristalKey)

    // 0x00478e78 CKHkS08CristalKey_Construct (inlined in 0x00479370 CKHkS08CristalKey_Create): the actor base only.
    CKHkS08CristalKey() {
    }
    ~CKHkS08CristalKey() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004793c8 CKHkS08CristalKey_Load

    uint32_t m_unk20;
    IKSerializable* m_pUnk24;  // +0x24
    IKSerializable* m_pUnk28;  // +0x28
    uint32_t m_unk2C[2];
    uint8_t m_unk34;  // +0x34
    uint8_t m_unk35[1];
    uint8_t m_unk36;  // +0x36
    uint8_t m_unk37;  // +0x37
    uint8_t m_unk38;  // +0x38
    uint8_t m_unk39[1];
    uint8_t m_unk3A;  // +0x3a
    uint8_t m_unk3B[1];
    CTriggerStarter m_unk3C;  // +0x3c
    uint32_t m_unk44[2];
};
DOTD_ASSERT_SIZE(CKHkS08CristalKey, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk36, 0x36);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk37, 0x37);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk3A, 0x3a);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk3C, 0x3c);
