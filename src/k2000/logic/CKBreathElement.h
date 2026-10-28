// CKBreathElement.h - the breath-attack element base (key 0x914c, vtable 0xb23588, size 0x178). Original unit:
// CKBreathElement.cpp (0x380ed0-0x385a78). No XXL2 class of this name: the members keep placeholder names.
// Base of CKFireBreath, CKFearEyes and CKPurpleRay (their Loads call this one first).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKBreathElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x245)
    DOTD_DECLARE_FACTORIES(CKBreathElement)

    CKBreathElement();  // 0x00381eb8 CKBreathElement_Construct
    ~CKBreathElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00383c30 CKBreathElement_Load

    uint32_t m_unk04;        // +0x04 (not loaded; live: 0)
    int32_t m_unk08[3];      // +0x08 (file: 500/1000/3000)
    float m_unk14;           // +0x14
    float m_unk18;           // +0x18
    float m_unk1c;           // +0x1c
    uint32_t m_unk20[3];     // +0x20 (file and live: 0)
    float m_unk2c;           // +0x2c
    float m_unk30;           // +0x30
    float m_unk34;           // +0x34
    int32_t m_unk38[3];      // +0x38 (file: 200/300/500)
    float m_unk44[3];        // +0x44
    float m_unk50[3];        // +0x50
    float m_unk5c[3];        // +0x5c
    float m_unk68[3];        // +0x68
    float m_unk74[3];        // +0x74 (live: floats in CKFireBreath)
    uint32_t m_unk80[3];     // +0x80 (file and live: 0; type unknown)
    uint32_t m_unk8c[3];     // +0x8c (idem)
    uint32_t m_unk98[3];     // +0x98 (idem)
    uint32_t m_unkA4[3];     // +0xa4 (idem)
    uint32_t m_unkB0[3];     // +0xb0 (idem)
    uint32_t m_unkBc[3];     // +0xbc (idem)
    uint32_t m_unkC8;        // +0xc8 (idem)
    uint32_t m_unkCc;        // +0xcc (idem)
    uint32_t m_unkD0;        // +0xd0 (idem)
    uint8_t m_unkD4[3];      // +0xd4
    uint8_t m_unkD7[3];      // +0xd7
    uint8_t m_unkDa;         // +0xda
    uint8_t m_unkDb;         // +0xdb
    uint8_t m_unkDc;         // +0xdc
    uint8_t m_padDd[3];      // +0xdd (not loaded)
    float m_unkE0;           // +0xe0
    float m_unkE4;           // +0xe4
    uint8_t m_unkE8;         // +0xe8
    uint8_t m_unkE9;         // +0xe9
    uint8_t m_unkEa;         // +0xea
    uint8_t m_padEb;         // +0xeb
    float m_unkEc;           // +0xec
    float m_unkF0;           // +0xf0
    float m_unkF4;           // +0xf4
    float m_unkF8;           // +0xf8
    uint8_t m_unkFc;         // +0xfc
    uint8_t m_unkFd;         // +0xfd
    uint8_t m_padFe[2];      // +0xfe (not loaded)
    float m_unk100;          // +0x100
    float m_unk104;          // +0x104
    uint8_t m_unk108;        // +0x108
    uint8_t m_unk109;        // +0x109
    uint8_t m_unk10a;        // +0x10a
    uint8_t m_pad10b;        // +0x10b
    float m_unk10c;          // +0x10c
    float m_unk110;          // +0x110
    float m_unk114;          // +0x114
    uint8_t m_unk118;        // +0x118
    uint8_t m_pad119[3];     // +0x119 (not loaded)
    float m_unk11c;          // +0x11c
    IKSerializable* m_unk120;  // +0x120 reference (live: CKExplosionFxData)
    void* m_unk124;          // +0x124 constructor: 0 (live: heap pointer)
    int32_t m_unk128;        // +0x128 constructor: 1
    uint32_t m_unk12c;       // +0x12c constructor: 0
    float m_unk130;          // +0x130
    float m_unk134;          // +0x134
    float m_unk138;          // +0x138
    float m_unk13c;          // +0x13c
    float m_unk140;          // +0x140
    float m_unk144;          // +0x144 (file and live: 0)
    float m_unk148;          // +0x148 (file and live: 0)
    uint8_t m_unk14c;        // +0x14c
    uint8_t m_pad14d[3];     // +0x14d
    uint8_t m_pad150[0x20];  // +0x150 runtime state (not loaded)
    IKSerializable* m_unk170;  // +0x170 reference (live: CKS08ElementDamage)
    uint32_t m_unk174;       // +0x174 (not loaded; live: heap pointer)
};
DOTD_ASSERT_SIZE(CKBreathElement, 0x178);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk8c, 0x8c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkBc, 0xbc);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkCc, 0xcc);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkD0, 0xd0);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkD7, 0xd7);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkDa, 0xda);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkDb, 0xdb);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkDc, 0xdc);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkE9, 0xe9);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkEa, 0xea);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkEc, 0xec);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkFc, 0xfc);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unkFd, 0xfd);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk109, 0x109);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk10a, 0x10a);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk10c, 0x10c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk11c, 0x11c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk128, 0x128);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk13c, 0x13c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk170, 0x170);
