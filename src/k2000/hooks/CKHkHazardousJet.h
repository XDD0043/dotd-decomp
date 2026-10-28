// CKHkHazardousJet.h - a hazardous jet (key 0x2f42, vtable 0xb284d0, size 0xcc). Original unit:
// CKHkHazardousJet.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkHazardousJet : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xbd)
    DOTD_DECLARE_FACTORIES(CKHkHazardousJet)

    // 0x004a01c0 CKHkHazardousJet_Construct (inlined in 0x004a0740 CKHkHazardousJet_Create): +0xc8 = 0.
    CKHkHazardousJet() { m_unkC8 = 0; }
    ~CKHkHazardousJet() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004a07a0 CKHkHazardousJet_Load

    IKSerializable* m_pUnk20;                  // +0x20
    IKSerializable* m_pUnk24;                  // +0x24
    IKSerializable* m_pUnk28;                  // +0x28
    IKSerializable* m_pUnk2C;                  // +0x2c
    IKSerializable* m_pUnk30;                  // +0x30
    IKSerializable* m_pUnk34;                  // +0x34
    IKSerializable* m_pUnk38;                  // +0x38
    uint32_t m_unk3C;                          // +0x3c
    uint32_t m_unk40;                          // +0x40
    uint32_t m_unk44;                          // +0x44
    uint32_t m_unk48;                          // +0x48
    uint32_t m_unk4C;                          // +0x4c
    uint32_t m_unk50;                          // +0x50
    uint32_t m_unk54;                          // +0x54
    uint8_t m_unk58;                           // +0x58
    uint8_t m_pad59[3];
    uint32_t m_unk5C;                          // +0x5c
    uint32_t m_unk60;                          // +0x60
    float m_afUnk64[3];                        // +0x64 a vector
    IKSerializable* m_pUnk70;                  // +0x70
    IKSerializable* m_pUnk74;                  // +0x74
    IKSerializable* m_pUnk78;                  // +0x78
    uint32_t m_unk7C;                          // +0x7c
    uint32_t m_unk80;                          // +0x80
    uint32_t m_unk84;                          // +0x84
    uint32_t m_unk88;                          // +0x88
    uint32_t m_unk8C;                          // +0x8c
    uint32_t m_unk90;                          // +0x90
    CTriggerStarter m_tsUnk94;                 // +0x94 (PostLoad runs its PostLoad)
    CTriggerStarter m_tsUnk9C;                 // +0x9c
    uint8_t m_unkA4;                           // +0xa4
    uint8_t m_unkA5;                           // +0xa5
    uint8_t m_unkA6;                           // +0xa6
    uint8_t m_unkA7;                           // +0xa7
    uint32_t m_unkA8;                          // +0xa8
    uint32_t m_unkAC[7];                       // +0xac..+0xc7 runtime
    uint32_t m_unkC8;                          // +0xc8 constructor 0
};
DOTD_ASSERT_SIZE(CKHkHazardousJet, 0xcc);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_afUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_tsUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_tsUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unkC8, 0xc8);
