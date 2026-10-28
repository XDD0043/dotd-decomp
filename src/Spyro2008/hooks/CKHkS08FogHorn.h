// CKHkS08FogHorn.h - key 0x2f02, size 0x16c. Original unit: CKHkS08FogHorn.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08FogHorn : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xbc)
    DOTD_DECLARE_FACTORIES(CKHkS08FogHorn)

    // 0x0049bfa8 CKHkS08FogHorn_Construct (inlined in 0x0049d1d8 CKHkS08FogHorn_Create):
    // +0x3c = 0, +0x54 = 5.0f (TOC +0x6080), +0x60/+0x58/+0x5c = 0, +0x13d/+0x13c = 0xff.
    CKHkS08FogHorn() {
        m_unk3C = 0;
        m_fUnk54 = 5.0f;
        m_fUnk60 = 0.0f;
        m_fUnk58 = 0.0f;
        m_fUnk5C = 0.0f;
        m_unk13D = 0xff;
        m_unk13C = 0xff;
    }
    ~CKHkS08FogHorn() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0049e860 CKHkS08FogHorn_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0049d430 CKHkS08FogHorn_PostLoad
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x0049be48 CKHkS08FogHorn_SetDefaultState (C2.2)
    void Start() override;                              // vt+0x50 0x0049bef8 CKHkS08FogHorn_Start (C2.2)
    void Restart() override;                            // vt+0x54 0x0049c880 CKHkS08FogHorn_Restart (C2.2)
    void ResetEffects();                                // 0x0049c548 CKHkS08FogHorn_ResetEffects_maybe (C2.2)

    float m_fUnk20;  // +0x20
    float m_fUnk24;  // +0x24
    float m_fUnk28;  // +0x28
    uint32_t m_unk2C;
    float m_fUnk30;  // +0x30
    uint32_t m_unk34;  // +0x34 (Restart clears the bytes at +0x34 and +0x35)
    IKSerializable* m_pUnk38;  // +0x38
    uint32_t m_unk3C;  // +0x3c constructor 0
    float m_fUnk40;  // +0x40
    float m_fUnk44;  // +0x44
    uint32_t m_unk48;
    IKSerializable* m_pUnk4C;  // +0x4c
    IKSerializable* m_pUnk50;  // +0x50
    float m_fUnk54;  // +0x54 constructor 5.0f
    float m_fUnk58;  // +0x58 constructor 0
    float m_fUnk5C;  // +0x5c constructor 0
    float m_fUnk60;  // +0x60 constructor 0
    uint32_t m_unk64;
    IKSerializable* m_pUnk68;  // +0x68
    IKSerializable* m_pUnk6C;  // +0x6c
    CMatrix34* m_pUnk70;  // +0x70 PostLoad: RwMatrixCreate_Thunk
    uint32_t m_unk74;  // +0x74
    uint8_t m_unk78;  // +0x78
    uint8_t m_unk79;  // +0x79
    uint8_t m_unk7A;  // +0x7a
    uint8_t m_unk7B[1];
    IKSerializable* m_pUnk7C;  // +0x7c
    IKSerializable* m_pUnk80;  // +0x80
    IKSerializable* m_pUnk84;  // +0x84
    IKSerializable* m_pUnk88;  // +0x88
    uint32_t m_unk8C;
    IKSerializable* m_pUnk90;  // +0x90
    uint8_t m_unk94;  // +0x94
    uint8_t m_unk95;  // +0x95
    uint8_t m_unk96[2];
    float m_fUnk98[2];  // +0x98 one 8-byte read, both words swapped
    float m_fUnkA0[2];  // +0xa0 one 8-byte read, both words swapped
    float m_fUnkA8[2];  // +0xa8 one 8-byte read, both words swapped
    float m_fUnkB0[2];  // +0xb0 one 8-byte read, both words swapped
    float m_fUnkB8;  // +0xb8
    float m_fUnkBC;  // +0xbc
    float m_fUnkC0;  // +0xc0
    float m_fUnkC4;  // +0xc4
    float m_fUnkC8;  // +0xc8
    float m_fUnkCC;  // +0xcc
    float m_fUnkD0;  // +0xd0
    float m_fUnkD4;  // +0xd4
    float m_fUnkD8;  // +0xd8
    float m_fUnkDC;  // +0xdc
    float m_fUnkE0;  // +0xe0
    float m_fUnkE4;  // +0xe4
    uint8_t m_unkE8;  // +0xe8
    uint8_t m_unkE9;  // +0xe9
    uint8_t m_unkEA[2];
    float m_fUnkEC;  // +0xec
    float m_fUnkF0;  // +0xf0
    float m_fUnkF4;  // +0xf4
    float m_fUnkF8;  // +0xf8
    float m_fUnkFC;  // +0xfc
    float m_fUnk100;  // +0x100
    float m_fUnk104;  // +0x104
    float m_fUnk108;  // +0x108
    float m_fUnk10C;  // +0x10c
    float m_fUnk110;  // +0x110
    uint8_t m_unk114;  // +0x114
    uint8_t m_unk115;  // +0x115
    uint8_t m_unk116;  // +0x116
    uint8_t m_unk117;  // +0x117
    float m_fUnk118;  // +0x118
    uint8_t m_unk11C;  // +0x11c
    uint8_t m_unk11D;  // +0x11d
    uint8_t m_unk11E[2];
    float m_fUnk120;  // +0x120
    CTriggerStarter m_unk124;  // +0x124
    CTriggerStarter m_unk12C;  // +0x12c
    uint32_t m_unk134[2];
    uint8_t m_unk13C;  // +0x13c constructor 0xff
    uint8_t m_unk13D;  // +0x13d constructor 0xff
    uint8_t m_unk13E[42];
    IKSerializable* m_pUnk168;  // +0x168
};
DOTD_ASSERT_SIZE(CKHkS08FogHorn, 0x16c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk79, 0x79);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk7A, 0x7a);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk95, 0x95);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkB8, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkD0, 0xd0);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unkE9, 0xe9);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk100, 0x100);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk108, 0x108);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk10C, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk115, 0x115);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk116, 0x116);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk117, 0x117);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk118, 0x118);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk11C, 0x11c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk11D, 0x11d);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_fUnk120, 0x120);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk12C, 0x12c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk13C, 0x13c);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_unk13D, 0x13d);
DOTD_ASSERT_OFFSET(CKHkS08FogHorn, m_pUnk168, 0x168);
