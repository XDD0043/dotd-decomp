// CKHkPressionStone.h - a pressure plate (key 0x542, vtable 0xb26100, size 0xd0). Original unit:
// CKHkPressionStone.cpp. XXL2 has CKHkPressionStone (K/KMeca/PressionStone, base IKHkMeca); DotD's derives
// from CKHkActorBase and loads more. XXL2 reads m_fMaxClearance, m_fUpSpeed, m_fDownSpeed and
// m_ui16HerosToTest in that order; DotD reads +0x50, +0x54, +0x58, then an extra word (+0x60), then the
// 16-bit word (+0x4e): the names below follow that order (_maybe).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkPressionStone : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x15)
    DOTD_DECLARE_FACTORIES(CKHkPressionStone)

    CKHkPressionStone() {}  // 0x00427060 CKHkPressionStone_Create: the CKHkActorBase defaults only
    ~CKHkPressionStone() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00429618 CKHkPressionStone_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00426e50 CKHkPressionStone_SetDefaultState
    void Start() override;                        // vt+0x50 0x004263a8 CKHkPressionStone_Start
    // vt+0xc8 0x00426d20 CKHkPressionStone_ApplyStatePreset_maybe
    void ApplyStatePreset(int32_t state) override;

    uint32_t m_unk20[11];                 // +0x20 runtime (not set by Create or Load)
    uint8_t m_unk4C;                      // +0x4c
    uint8_t m_pad4D;
    uint16_t m_ui16HerosToTest;           // +0x4e _maybe XXL2 m_ui16HerosToTest
    float m_fMaxClearance;                // +0x50 _maybe XXL2 m_fMaxClearance
    float m_fUpSpeed;                     // +0x54 _maybe XXL2 m_fUpSpeed
    float m_fDownSpeed;                   // +0x58 _maybe XXL2 m_fDownSpeed
    float m_unk5C;                        // +0x5c
    float m_unk60;                        // +0x60
    IKSerializable* m_unk64;              // +0x64
    IKSerializable* m_unk68;              // +0x68
    IKSerializable* m_apUnk6C[3];         // +0x6c one contiguous read of three references
    IKSerializable* m_unk78;              // +0x78
    uint8_t m_unk7C;                      // +0x7c the count of +0x80
    uint8_t m_pad7D[3];
    IKSerializable** m_apUnk80;           // +0x80 references (Mem_AllocAligned16), 0 without
    float m_unk84;                        // +0x84
    IKSerializable* m_unk88;              // +0x88
    IKSerializable* m_unk8C;              // +0x8c
    IKSerializable* m_unk90;              // +0x90 read for K_LEVEL_PLATEFORMS only
    uint32_t m_unk94;                     // +0x94 runtime: 0 at PostLoad (0x426410)
    uint32_t m_unk98;                     // +0x98 runtime: 0 at PostLoad
    CTriggerStarter m_unk9C;              // +0x9c
    CTriggerStarter m_unkA4;              // +0xa4
    CTriggerStarter m_unkAC;              // +0xac
    CTriggerStarter m_unkB4;              // +0xb4
    CTriggerStarter m_unkBC;              // +0xbc
    CTriggerStarter m_unkC4;              // +0xc4
    uint8_t m_unkCC;                      // +0xcc runtime (Start stores a byte)
    uint8_t m_padCD[3];
};
DOTD_ASSERT_SIZE(CKHkPressionStone, 0xd0);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_ui16HerosToTest, 0x4e);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_fMaxClearance, 0x50);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_apUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_apUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unkC4, 0xc4);
