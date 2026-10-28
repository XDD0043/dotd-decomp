// CKElectricSphere.h - the electric sphere attack (key 0x964c, vtable 0xb23888, size 0x334). Original unit: CKElectricSphere.cpp
// (0x396748-0x39cf88). Derives from CKTransformElement (its Load is called first). No XXL2 class of this name: the
// members keep placeholder names (types from the Ghidra struct and the level data). Unread runtime state is padding.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"

class CKElectricSphere : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x259)
    DOTD_DECLARE_FACTORIES(CKElectricSphere)

    CKElectricSphere() {}  // 0x00396c10 CKElectricSphere_Construct: CKTransformElement's constructor, then the vtable only
    ~CKElectricSphere() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00397348 CKElectricSphere_Load

    float m_unk154;                     // +0x154
    float m_unk158;                     // +0x158
    float m_unk15c;                     // +0x15c
    float m_unk160;                     // +0x160
    float m_unk164;                     // +0x164
    float m_unk168;                     // +0x168
    int32_t m_unk16c;                   // +0x16c
    int32_t m_unk170;                   // +0x170
    int32_t m_unk174;                   // +0x174
    float m_unk178;                     // +0x178
    float m_unk17c;                     // +0x17c
    float m_unk180;                     // +0x180
    float m_unk184;                     // +0x184
    float m_unk188;                     // +0x188
    IKSerializable* m_unk18c;           // +0x18c (reference; Ghidra: CKImpulsionCpnt *)
    float m_unk190;                     // +0x190
    float m_unk194;                     // +0x194
    float m_unk198;                     // +0x198
    float m_unk19c;                     // +0x19c
    float m_unk1a0;                     // +0x1a0
    float m_unk1a4;                     // +0x1a4
    float m_unk1a8;                     // +0x1a8
    float m_unk1ac;                     // +0x1ac
    float m_unk1b0;                     // +0x1b0
    float m_unk1b4;                     // +0x1b4
    float m_unk1b8;                     // +0x1b8
    float m_unk1bc;                     // +0x1bc
    float m_unk1c0;                     // +0x1c0
    float m_unk1c4;                     // +0x1c4
    float m_unk1c8;                     // +0x1c8
    float m_unk1cc;                     // +0x1cc
    float m_unk1d0;                     // +0x1d0
    float m_unk1d4;                     // +0x1d4
    float m_unk1d8;                     // +0x1d8
    IKSerializable* m_unk1dc;           // +0x1dc (reference)
    IKSerializable* m_unk1e0;           // +0x1e0 (reference)
    uint8_t m_pad1e4[0x8];
    IKSerializable* m_unk1ec;           // +0x1ec (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk1f0;           // +0x1f0 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk1f4;           // +0x1f4 (reference; Ghidra: CKExplosionFxData *)
    float m_unk1f8;                     // +0x1f8
    IKSerializable* m_unk1fc;           // +0x1fc (reference; Ghidra: CKS08ElementDamage *)
    IKSerializable* m_unk200;           // +0x200 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk204;           // +0x204 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk208;           // +0x208 (reference; Ghidra: CKExplosionFxData *)
    float m_unk20c;                     // +0x20c
    float m_unk210;                     // +0x210
    float m_unk214;                     // +0x214
    float m_unk218;                     // +0x218
    float m_unk21c;                     // +0x21c
    float m_unk220;                     // +0x220
    IKSerializable* m_unk224;           // +0x224 (reference; Ghidra: CNode *)
    IKSerializable* m_unk228;           // +0x228 (reference; Ghidra: CNode *)
    uint32_t m_unk22c;                  // +0x22c (type unknown)
    float m_unk230;                     // +0x230
    float m_unk234;                     // +0x234
    float m_unk238;                     // +0x238
    float m_unk23c;                     // +0x23c
    float m_unk240;                     // +0x240
    float m_unk244;                     // +0x244
    float m_unk248;                     // +0x248
    IKSerializable* m_unk24c;           // +0x24c (reference; Ghidra: CKElectricArcFxData *)
    IKSerializable* m_unk250;           // +0x250 (reference; Ghidra: CKElectricArcFxData *)
    IKSerializable* m_unk254;           // +0x254 (reference; Ghidra: CKElectricArcFxData *)
    uint8_t m_pad258[0x10];
    IKSerializable* m_unk268;           // +0x268 (reference)
    uint8_t m_pad26c[0x4];
    IKSerializable* m_unk270;           // +0x270 (reference; Ghidra: CKPointLightFxData *)
    IKSerializable* m_unk274;           // +0x274 (reference; Ghidra: CKPointLightFxData *)
    IKSerializable* m_unk278;           // +0x278 (reference; Ghidra: CKPointLightFxData *)
    uint8_t m_pad27c[0x4];
    IKSerializable* m_unk280;           // +0x280 (reference)
    IKSerializable* m_unk284;           // +0x284 (reference)
    uint8_t m_pad288[0x4];
    IKSerializable* m_unk28c;           // +0x28c (reference; Ghidra: CKSoundDictionaryID *)
    float m_unk290;                     // +0x290
    uint8_t m_pad294[0xa0];
};
DOTD_ASSERT_SIZE(CKElectricSphere, 0x334);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk15c, 0x15c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk180, 0x180);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1ac, 0x1ac);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk224, 0x224);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk290, 0x290);
