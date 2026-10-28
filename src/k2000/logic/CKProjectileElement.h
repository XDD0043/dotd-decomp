// CKProjectileElement.h - the shared base of the projectile element attacks (key 0x934c, vtable 0xb23dd8,
// size 0x214). Original unit: CKProjectileElement.cpp (0x3bc818-0x3c1f38). Derives from IKSerializable only
// (its Load calls no base Load). No XXL2 class of this name: the members keep placeholder names.
// Bases of CKIceGatling, CKBlackBall, CKEarthMissile, CKFearScream, CKPoisonGrenade.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKProjectileElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24d)
    DOTD_DECLARE_FACTORIES(CKProjectileElement)

    CKProjectileElement() {}  // 0x003bc868 CKProjectileElement_Construct: stores the vtable only
    ~CKProjectileElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003bf360 CKProjectileElement_Load

    // Arrays of 3: the Load's 3-iteration loop reads element i of each. Types from the level data (live
    // floats/ints); arrays that are zero in every sample are uint32_t.
    uint32_t m_unk04;                // +0x04 (not read)
    int32_t m_unk08[3];              // +0x08 (file: 10, 15, 30)
    int32_t m_unk14[3];              // +0x14 (file: 100, 80, 200)
    float m_unk20;                   // +0x20
    float m_unk24;                   // +0x24
    float m_unk28;                   // +0x28
    float m_unk2c;                   // +0x2c
    float m_unk30;                   // +0x30
    float m_unk34;                   // +0x34
    uint32_t m_unk38[3];             // +0x38 (always 0)
    float m_unk44;                   // +0x44
    float m_unk48;                   // +0x48
    float m_unk4c;                   // +0x4c
    int32_t m_unk50[3];              // +0x50 (file: 6, 30, 45)
    int32_t m_unk5c[3];              // +0x5c (file: 100, 40, 45)
    float m_unk68[3];                // +0x68 (file: 5.0, 1.0, 2.0)
    float m_unk74;                   // +0x74 (file: 0.22, 0.2)
    uint32_t m_unk78;                // +0x78 (always 0)
    uint32_t m_unk7c;                // +0x7c (always 0)
    uint32_t m_unk80;                // +0x80 (always 0)
    uint32_t m_unk84;                // +0x84 (always 0)
    float m_unk88[3];                // +0x88 (file: 0.9, 2.0)
    float m_unk94[3];                // +0x94 (file: 1.0)
    float m_unka0[3];                // +0xa0 (file: 0.5, 0.9, 1.5)
    float m_unkac[3];                // +0xac (file: 1.0)
    uint32_t m_unkb8[3];             // +0xb8 (always 0)
    uint32_t m_unkc4[3];             // +0xc4 (always 0)
    float m_unkd0[3];                // +0xd0 (file: 1.5, 2.25, 4.0)
    uint32_t m_unkdc[3];             // +0xdc (always 0)
    uint32_t m_unke8[3];             // +0xe8 (always 0)
    uint32_t m_unkf4[3];             // +0xf4 (always 0)
    uint32_t m_unk100[3];            // +0x100 (always 0)
    uint32_t m_unk10c[3];            // +0x10c (always 0)
    float m_unk118[3];               // +0x118 (file: 0.2, 0.3, 0.75)
    float m_unk124[3];               // +0x124 (file: 0.2, 0.4, 1.0)
    uint32_t m_unk130[3];            // +0x130 (always 0)
    uint32_t m_unk13c[3];            // +0x13c (always 0)
    uint32_t m_unk148[3];            // +0x148 (always 0)
    uint32_t m_unk154[3];            // +0x154 (always 0)
    uint32_t m_unk160;               // +0x160
    uint32_t m_unk164;               // +0x164 (file: 0xcdcdcdcd, an uninitialised tool value)
    uint32_t m_unk168;               // +0x168 (file: 0xcdcdcdcd)
    uint32_t m_unk16c;               // +0x16c
    uint32_t m_unk170;               // +0x170 (file: 0xcdcdcdcd)
    uint32_t m_unk174;               // +0x174 (file: 0xcdcdcdcd)
    uint8_t m_unk178[3];             // +0x178
    uint8_t m_unk17b[3];             // +0x17b
    uint8_t m_unk17e[3];             // +0x17e
    uint8_t m_unk181[3];             // +0x181
    IKSerializable* m_unk184;        // +0x184 CKAimCamembert (live)
    uint32_t m_unk188[3];            // +0x188 one 12-byte read, three swapped words (always 0)
    uint8_t m_unk194;                // +0x194
    uint8_t m_unk195;                // +0x195
    uint8_t m_unk196;                // +0x196 (+0x197 padding)
    float m_unk198;                  // +0x198
    float m_unk19c;                  // +0x19c
    uint8_t m_unk1a0;                // +0x1a0
    uint8_t m_unk1a1;                // +0x1a1
    uint8_t m_unk1a2;                // +0x1a2 (+0x1a3 padding)
    float m_unk1a4;                  // +0x1a4
    float m_unk1a8;                  // +0x1a8
    float m_unk1ac;                  // +0x1ac
    float m_unk1b0;                  // +0x1b0
    uint8_t m_unk1b4;                // +0x1b4
    uint8_t m_unk1b5;                // +0x1b5 (+0x1b6..+0x1b7 padding)
    float m_unk1b8;                  // +0x1b8
    float m_unk1bc;                  // +0x1bc
    uint8_t m_unk1c0;                // +0x1c0
    uint8_t m_unk1c1;                // +0x1c1
    uint8_t m_unk1c2;                // +0x1c2 (+0x1c3 padding)
    float m_unk1c4;                  // +0x1c4
    float m_unk1c8;                  // +0x1c8
    float m_unk1cc;                  // +0x1cc
    uint8_t m_unk1d0;                // +0x1d0 (+0x1d1..+0x1d3 padding)
    float m_unk1d4;                  // +0x1d4
    uint8_t m_unk1d8;                // +0x1d8
    uint8_t m_unk1d9;                // +0x1d9
    uint8_t m_unk1da;                // +0x1da
    uint8_t m_unk1db;                // +0x1db
    uint8_t m_unk1dc;                // +0x1dc
    uint8_t m_unk1dd;                // +0x1dd (+0x1de..+0x1df padding)
    float m_unk1e0;                  // +0x1e0
    float m_unk1e4;                  // +0x1e4
    float m_unk1e8;                  // +0x1e8
    IKSerializable* m_unk1ec;        // +0x1ec CKExplosionFxData (live)
    uint8_t m_unk1f0[0x1c];          // +0x1f0..+0x20b (not read; runtime state)
    IKSerializable* m_unk20c;        // +0x20c CKS08ElementDamage (live)
    uint32_t m_unk210;               // +0x210 (not read)
};
DOTD_ASSERT_SIZE(CKProjectileElement, 0x214);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unka0, 0xa0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unkac, 0xac);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unkb8, 0xb8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unkc4, 0xc4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unkd0, 0xd0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unkdc, 0xdc);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unke8, 0xe8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unkf4, 0xf4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk10c, 0x10c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk13c, 0x13c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk17b, 0x17b);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk17e, 0x17e);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk181, 0x181);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk196, 0x196);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1a2, 0x1a2);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1b5, 0x1b5);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1c2, 0x1c2);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1dd, 0x1dd);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk20c, 0x20c);
