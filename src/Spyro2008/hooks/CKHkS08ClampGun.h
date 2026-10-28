// CKHkS08ClampGun.h - the clamp gun hook (key 0x2c42, size 0x158). Original unit: CKHkS08ClampGun.cpp.
// No XXL2 class. The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkS08ClampGun : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb1)
    DOTD_DECLARE_FACTORIES(CKHkS08ClampGun)

    // An element of the +0xb4 vector: OperatorNew(0xc), the three words zeroed, then the file's float,
    // +0x04 = 0 and the byte +0x08 = 0 (0.3, 0.3, 0.1, 0.1, 0.1 in the LVL samples: delays_maybe).
    struct SElem {
        float m_fUnk0;     // +0x00 read
        uint32_t m_unk4;   // +0x04 0
        uint8_t m_unk8;    // +0x08 0
        uint8_t m_pad9[3];
    };

    // 0x00487608 CKHkS08ClampGun_Construct (inlined in 0x004882a0 CKHkS08ClampGun_Create): +0x3c = 0,
    // the +0xb4 vector empty (capacity 1, length 0, block 0), +0x125/+0x124/+0x13d/+0x13c = 0xff.
    CKHkS08ClampGun() {
        m_unk3C = 0;
        m_vUnkB4.m_ui32NbElt = 1;
        m_vUnkB4.m_ui32NbUsedElt = 0;
        m_vUnkB4.m_pBlock = nullptr;
        m_unk125 = 0xff;
        m_unk124 = 0xff;
        m_unk13D = 0xff;
        m_unk13C = 0xff;
    }
    ~CKHkS08ClampGun() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00489690 CKHkS08ClampGun_Load

    IKSerializable* m_pUnk20;   // +0x20
    IKSerializable* m_pUnk24;   // +0x24
    IKSerializable* m_pUnk28;   // +0x28
    uint32_t m_unk2C[3];
    IKSerializable* m_pUnk38;   // +0x38 PostLoad configures it from +0x40/+0x44
    uint32_t m_unk3C;           // +0x3c constructor 0
    float m_fUnk40;             // +0x40
    float m_fUnk44;             // +0x44
    float m_fUnk48;             // +0x48
    float m_fUnk4C;             // +0x4c
    uint32_t m_unk50;
    float m_fUnk54;             // +0x54
    float m_fUnk58;             // +0x58
    uint8_t m_unk5C;
    uint8_t m_unk5D;            // +0x5d
    uint8_t m_unk5E[2];
    float m_fUnk60;             // +0x60 (1.0472 = pi/3 in the samples: an angle_maybe)
    uint32_t m_unk64[8];
    float m_fUnk84;             // +0x84
    uint32_t m_unk88;
    float m_fUnk8C;             // +0x8c
    float m_fUnk90;             // +0x90
    uint32_t m_unk94;
    float m_fUnk98;             // +0x98
    float m_fUnk9C;             // +0x9c
    float m_fUnkA0;             // +0xa0 (0.5236 = pi/6 in the samples)
    uint32_t m_unkA4[4];
    TVector<SElem*, 1> m_vUnkB4;  // +0xb4
    uint32_t m_unkC0[5];
    IKSerializable* m_pUnkD4;   // +0xd4
    IKSerializable* m_pUnkD8;   // +0xd8
    CTriggerStarter m_unkDC;    // +0xdc
    IKSerializable* m_pUnkE4;   // +0xe4
    uint32_t m_unkE8;
    IKSerializable* m_pUnkEC;   // +0xec
    uint32_t m_unkF0;
    IKSerializable* m_pUnkF4;   // +0xf4
    uint32_t m_unkF8;
    IKSerializable* m_pUnkFC;   // +0xfc
    uint32_t m_unk100;
    IKSerializable* m_pUnk104;  // +0x104
    uint32_t m_unk108;
    float m_fUnk10C;            // +0x10c
    uint32_t m_unk110;          // +0x110 (0 in every sample)
    float m_fUnk114;            // +0x114
    uint8_t m_unk118;           // +0x118
    uint8_t m_unk119;           // +0x119
    uint8_t m_unk11A;           // +0x11a
    uint8_t m_unk11B;
    uint8_t m_unk11C;           // +0x11c
    uint8_t m_unk11D;           // +0x11d
    uint8_t m_unk11E;           // +0x11e
    uint8_t m_unk11F;
    uint32_t m_unk120;
    uint8_t m_unk124;           // +0x124 constructor 0xff
    uint8_t m_unk125;           // +0x125 constructor 0xff
    uint8_t m_unk126[0x16];
    uint8_t m_unk13C;           // +0x13c constructor 0xff
    uint8_t m_unk13D;           // +0x13d constructor 0xff
    uint8_t m_unk13E[0x1a];
};
DOTD_ASSERT_SIZE(CKHkS08ClampGun::SElem, 0xc);
DOTD_ASSERT_SIZE(CKHkS08ClampGun, 0x158);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk5D, 0x5d);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_vUnkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk10C, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk11C, 0x11c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk13C, 0x13c);
