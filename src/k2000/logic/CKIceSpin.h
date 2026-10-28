// CKIceSpin.h - the ice spin attack (key 0x988c, vtable 0xb23c10, size 0x33c). Original unit: CKIceSpin.cpp
// (0x3abec0-0x3b47b8). Derives from CKTransformElement (its Load is called first). No XXL2 class of this name: the
// members keep placeholder names (types from the Ghidra struct and the level data). Unread runtime state is padding.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"

class CKIceSpin : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x262)
    DOTD_DECLARE_FACTORIES(CKIceSpin)

    CKIceSpin() {}  // 0x003ac4f0 CKIceSpin_Construct: CKTransformElement's constructor, then the vtable only
    ~CKIceSpin() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003ad010 CKIceSpin_Load

    float m_unk154;                     // +0x154
    float m_unk158;                     // +0x158
    float m_unk15c;                     // +0x15c
    int32_t m_unk160;                   // +0x160
    int32_t m_unk164;                   // +0x164
    int32_t m_unk168;                   // +0x168
    int32_t m_unk16c;                   // +0x16c
    int32_t m_unk170;                   // +0x170
    int32_t m_unk174;                   // +0x174
    int32_t m_unk178;                   // +0x178
    int32_t m_unk17c;                   // +0x17c
    int32_t m_unk180;                   // +0x180
    float m_unk184;                     // +0x184
    float m_unk188;                     // +0x188
    float m_unk18c;                     // +0x18c
    float m_unk190;                     // +0x190
    float m_unk194;                     // +0x194
    float m_unk198;                     // +0x198
    float m_unk19c;                     // +0x19c
    float m_unk1a0;                     // +0x1a0
    float m_unk1a4;                     // +0x1a4
    int32_t m_unk1a8;                   // +0x1a8
    int32_t m_unk1ac;                   // +0x1ac
    int32_t m_unk1b0;                   // +0x1b0
    int32_t m_unk1b4;                   // +0x1b4
    int32_t m_unk1b8;                   // +0x1b8
    int32_t m_unk1bc;                   // +0x1bc
    int32_t m_unk1c0;                   // +0x1c0
    int32_t m_unk1c4;                   // +0x1c4
    int32_t m_unk1c8;                   // +0x1c8
    float m_unk1cc;                     // +0x1cc
    float m_unk1d0;                     // +0x1d0
    float m_unk1d4;                     // +0x1d4
    float m_unk1d8;                     // +0x1d8
    float m_unk1dc;                     // +0x1dc
    float m_unk1e0;                     // +0x1e0
    float m_unk1e4;                     // +0x1e4
    float m_unk1e8;                     // +0x1e8
    float m_unk1ec;                     // +0x1ec
    float m_unk1f0;                     // +0x1f0
    float m_unk1f4;                     // +0x1f4
    float m_unk1f8;                     // +0x1f8
    float m_unk1fc;                     // +0x1fc
    float m_unk200;                     // +0x200
    float m_unk204;                     // +0x204
    int32_t m_unk208;                   // +0x208
    int32_t m_unk20c;                   // +0x20c
    int32_t m_unk210;                   // +0x210
    int32_t m_unk214;                   // +0x214
    int32_t m_unk218;                   // +0x218
    int32_t m_unk21c;                   // +0x21c
    int32_t m_unk220;                   // +0x220
    int32_t m_unk224;                   // +0x224
    int32_t m_unk228;                   // +0x228
    float m_unk22c;                     // +0x22c
    float m_unk230;                     // +0x230
    float m_unk234;                     // +0x234
    float m_unk238;                     // +0x238
    float m_unk23c;                     // +0x23c
    float m_unk240;                     // +0x240
    float m_unk244;                     // +0x244
    float m_unk248;                     // +0x248
    float m_unk24c;                     // +0x24c
    float m_unk250;                     // +0x250
    float m_unk254;                     // +0x254
    float m_unk258;                     // +0x258
    float m_unk25c;                     // +0x25c
    float m_unk260;                     // +0x260
    float m_unk264;                     // +0x264
    IKSerializable* m_unk268;           // +0x268 (reference; Ghidra: CKImpulsionCpnt *)
    IKSerializable* m_unk26c;           // +0x26c (reference; Ghidra: CKMeshPopFxData *)
    uint8_t m_pad270[0x4];
    float m_unk274;                     // +0x274
    float m_unk278;                     // +0x278
    float m_unk27c;                     // +0x27c
    float m_unk280;                     // +0x280
    float m_unk284;                     // +0x284
    float m_unk288;                     // +0x288
    int32_t m_unk28c;                   // +0x28c
    uint32_t m_unk290;                  // +0x290 (type unknown)
    IKSerializable* m_unk294;           // +0x294 (reference)
    uint8_t m_pad298[0x4];
    IKSerializable* m_unk29c;           // +0x29c (reference)
    IKSerializable* m_unk2a0;           // +0x2a0 (reference)
    uint8_t m_pad2a4[0x4];
    IKSerializable* m_unk2a8;           // +0x2a8 (reference)
    uint8_t m_pad2ac[0x4];
    IKSerializable* m_unk2b0;           // +0x2b0 (reference; Ghidra: CNode *)
    IKSerializable* m_unk2b4;           // +0x2b4 (reference; Ghidra: CNode *)
    IKSerializable* m_unk2b8;           // +0x2b8 (reference; Ghidra: CNode *)
    IKSerializable* m_unk2bc;           // +0x2bc (reference; Ghidra: CTrailNodeFx *)
    IKSerializable* m_unk2c0;           // +0x2c0 (reference; Ghidra: CKPointLightFxData *)
    IKSerializable* m_unk2c4;           // +0x2c4 (reference; Ghidra: CKPointLightFxData *)
    IKSerializable* m_unk2c8;           // +0x2c8 (reference; Ghidra: CKPointLightFxData *)
    uint8_t m_pad2cc[0x4];
    IKSerializable* m_unk2d0;           // +0x2d0 (reference)
    IKSerializable* m_unk2d4;           // +0x2d4 (reference)
    uint8_t m_pad2d8[0x4];
    IKSerializable* m_unk2dc;           // +0x2dc (reference; Ghidra: CKProjectileAccessor *)
    IKSerializable* m_unk2e0;           // +0x2e0 (reference; Ghidra: CKProjectileAccessor *)
    IKSerializable* m_unk2e4;           // +0x2e4 (reference; Ghidra: CKS08ElementDamage *)
    float m_unk2e8;                     // +0x2e8
    float m_unk2ec;                     // +0x2ec
    float m_unk2f0;                     // +0x2f0
    float m_unk2f4;                     // +0x2f4
    float m_unk2f8;                     // +0x2f8
    float m_unk2fc;                     // +0x2fc
    float m_unk300;                     // +0x300
    IKSerializable* m_unk304;           // +0x304 (reference; Ghidra: CKSoundDictionaryID *)
    float m_unk308;                     // +0x308
    uint8_t m_pad30c[0x30];
};
DOTD_ASSERT_SIZE(CKIceSpin, 0x33c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk15c, 0x15c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk180, 0x180);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1ac, 0x1ac);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk224, 0x224);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk27c, 0x27c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2b4, 0x2b4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2bc, 0x2bc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2c0, 0x2c0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2c4, 0x2c4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2c8, 0x2c8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2d0, 0x2d0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2d4, 0x2d4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2dc, 0x2dc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2e0, 0x2e0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2e4, 0x2e4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2e8, 0x2e8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2ec, 0x2ec);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2f4, 0x2f4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2f8, 0x2f8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk2fc, 0x2fc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk300, 0x300);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk304, 0x304);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk308, 0x308);
