// CKHkS08FlamingTorch.h - a flaming torch hook (key 0x2e82, size 0x10c). Original unit:
// CKHkS08FlamingTorch.cpp. No XXL2 class. The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08FlamingTorch : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xba)
    DOTD_DECLARE_FACTORIES(CKHkS08FlamingTorch)

    // A 0x14-byte entry of the +0x5c table (all 1.0f in the LVL040 samples).
    struct SEntry {
        float m_fUnk0;  // +0x00 read third
        float m_fUnk4;  // +0x04 read fourth
        float m_fUnk8;  // +0x08 read first
        float m_fUnkC;  // +0x0c read second
        float m_fUnk10; // +0x10 read last
    };

    // 0x00496c10 CKHkS08FlamingTorch_Construct (inlined in 0x00497558 CKHkS08FlamingTorch_Create): +0x2c = 0,
    // +0xe9/+0xe8 = 0xff.
    CKHkS08FlamingTorch() {
        m_unk2C = 0;
        m_unkE9 = 0xff;
        m_unkE8 = 0xff;
    }
    ~CKHkS08FlamingTorch() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00498f90 CKHkS08FlamingTorch_Load

    IKSerializable* m_pUnk20;   // +0x20
    IKSerializable* m_pUnk24;   // +0x24
    IKSerializable* m_pUnk28;   // +0x28 PostLoad configures it (+0x18..+0x30 of the target) from +0x30/+0x34
    uint32_t m_unk2C;           // +0x2c constructor 0
    float m_fUnk30;             // +0x30
    float m_fUnk34;             // +0x34
    uint32_t m_unk38;
    float m_fUnk3C;             // +0x3c
    uint32_t m_unk40;
    float m_fUnk44;             // +0x44
    float m_fUnk48;             // +0x48
    IKSerializable* m_pUnk4C;   // +0x4c
    uint32_t m_unk50;           // +0x50 runtime (PostLoad: 0)
    IKSerializable* m_pUnk54;   // +0x54
    uint32_t m_unk58;
    SEntry m_aUnk5C[2];         // +0x5c the file gives the count (2 in every sample)
    uint32_t m_unk84;
    IKSerializable* m_pUnk88;   // +0x88
    IKSerializable* m_pUnk8C;   // +0x8c
    IKSerializable* m_pUnk90;   // +0x90
    IKSerializable* m_pUnk94;   // +0x94
    uint32_t m_unk98;           // +0x98
    IKSerializable* m_pUnk9C;   // +0x9c
    IKSerializable* m_pUnkA0;   // +0xa0
    IKSerializable* m_pUnkA4;   // +0xa4
    IKSerializable* m_pUnkA8;   // +0xa8
    CTriggerStarter m_unkAC;    // +0xac
    CTriggerStarter m_unkB4;    // +0xb4
    IKSerializable* m_pUnkBC;   // +0xbc
    IKSerializable* m_pUnkC0;   // +0xc0
    uint32_t m_unkC4[5];
    uint8_t m_unkD8;            // +0xd8
    uint8_t m_unkD9;            // +0xd9
    uint8_t m_unkDA;            // +0xda
    uint8_t m_unkDB[2];
    uint8_t m_unkDD;            // +0xdd
    uint8_t m_unkDE;            // +0xde
    uint8_t m_unkDF;            // +0xdf
    IKSerializable* m_pUnkE0;   // +0xe0
    uint32_t m_unkE4;           // +0xe4 runtime (PostLoad: points to +0xec)
    uint8_t m_unkE8;            // +0xe8 constructor 0xff
    uint8_t m_unkE9;            // +0xe9 constructor 0xff
    uint8_t m_unkEA[2];
    uint32_t m_unkEC[8];        // +0xec runtime (PostLoad)
};
DOTD_ASSERT_SIZE(CKHkS08FlamingTorch::SEntry, 0x14);
DOTD_ASSERT_SIZE(CKHkS08FlamingTorch, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_aUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkDD, 0xdd);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkE8, 0xe8);
