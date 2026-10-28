// CKEarthBoulder.h - the earth boulder attack (key 0x95cc, vtable 0xb236c0, size 0x2d0). Original unit: CKEarthBoulder.cpp
// (0x389ec8-0x3928a0). Derives from CKTransformElement (its Load is called first). No XXL2 class of this name: the
// members keep placeholder names (types from the Ghidra struct and the level data). Unread runtime state is padding.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"

class CKEarthBoulder : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x257)
    DOTD_DECLARE_FACTORIES(CKEarthBoulder)

    CKEarthBoulder() {}  // 0x0038a890 CKEarthBoulder_Construct: CKTransformElement's constructor, then the vtable only
    ~CKEarthBoulder() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0038b200 CKEarthBoulder_Load

    float m_unk154;                     // +0x154
    float m_unk158;                     // +0x158
    float m_unk15c;                     // +0x15c
    uint32_t m_unk160;                  // +0x160 (type unknown)
    float m_unk164;                     // +0x164
    float m_unk168;                     // +0x168
    float m_unk16c;                     // +0x16c
    float m_unk170;                     // +0x170
    float m_unk174;                     // +0x174
    float m_unk178;                     // +0x178
    float m_unk17c;                     // +0x17c
    float m_unk180;                     // +0x180
    int32_t m_unk184;                   // +0x184
    uint32_t m_unk188;                  // +0x188 (type unknown)
    uint32_t m_unk18c;                  // +0x18c (type unknown)
    float m_unk190;                     // +0x190
    float m_unk194;                     // +0x194
    float m_unk198;                     // +0x198
    float m_unk19c;                     // +0x19c
    float m_unk1a0;                     // +0x1a0
    float m_unk1a4;                     // +0x1a4
    float m_unk1a8;                     // +0x1a8
    uint32_t m_unk1ac;                  // +0x1ac (type unknown)
    uint32_t m_unk1b0;                  // +0x1b0 (type unknown)
    uint32_t m_unk1b4;                  // +0x1b4 (type unknown)
    float m_unk1b8;                     // +0x1b8
    float m_unk1bc;                     // +0x1bc
    float m_unk1c0;                     // +0x1c0
    uint32_t m_unk1c4;                  // +0x1c4 (type unknown)
    uint32_t m_unk1c8;                  // +0x1c8 (type unknown)
    uint32_t m_unk1cc;                  // +0x1cc (type unknown)
    float m_unk1d0;                     // +0x1d0
    float m_unk1d4;                     // +0x1d4
    float m_unk1d8;                     // +0x1d8
    uint32_t m_unk1dc;                  // +0x1dc (type unknown)
    uint32_t m_unk1e0;                  // +0x1e0 (type unknown)
    uint32_t m_unk1e4;                  // +0x1e4 (type unknown)
    float m_unk1e8;                     // +0x1e8
    float m_unk1ec;                     // +0x1ec
    float m_unk1f0;                     // +0x1f0
    IKSerializable* m_unk1f4;           // +0x1f4 (reference)
    uint8_t m_pad1f8[0x4];
    IKSerializable* m_unk1fc;           // +0x1fc (reference)
    uint8_t m_pad200[0x4];
    IKSerializable* m_unk204;           // +0x204 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk208;           // +0x208 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk20c;           // +0x20c (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk210;           // +0x210 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk214;           // +0x214 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk218;           // +0x218 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk21c;           // +0x21c (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk220;           // +0x220 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk224;           // +0x224 (reference; Ghidra: CKS08ElementDamage *)
    IKSerializable* m_unk228;           // +0x228 (reference; Ghidra: CNode *)
    IKSerializable* m_unk22c;           // +0x22c (reference; Ghidra: CNode *)
    IKSerializable* m_unk230;           // +0x230 (reference; Ghidra: CNode *)
    IKSerializable* m_unk234;           // +0x234 (reference; Ghidra: CNode *)
    float m_unk238;                     // +0x238
    float m_unk23c;                     // +0x23c
    float m_unk240;                     // +0x240
    IKSerializable* m_unk244;           // +0x244 (reference)
    IKSerializable* m_unk248;           // +0x248 (reference)
    uint8_t m_pad24c[0x4];
    IKSerializable* m_unk250;           // +0x250 (reference)
    uint8_t m_pad254[0x4];
    IKSerializable* m_unk258;           // +0x258 (reference)
    IKSerializable* m_unk25c;           // +0x25c (reference)
    uint8_t m_pad260[0x4];
    IKSerializable* m_unk264;           // +0x264 (reference; Ghidra: CKPointLightFxData *)
    IKSerializable* m_unk268;           // +0x268 (reference; Ghidra: CKPointLightFxData *)
    IKSerializable* m_unk26c;           // +0x26c (reference; Ghidra: CKPointLightFxData *)
    uint8_t m_pad270[0x4];
    IKSerializable* m_unk274;           // +0x274 (reference; Ghidra: CKSoundDictionaryID *)
    float m_unk278;                     // +0x278
    float m_unk27c;                     // +0x27c
    uint32_t m_unk280;                  // +0x280 (type unknown)
    float m_unk284;                     // +0x284
    float m_unk288;                     // +0x288
    IKSerializable* m_unk28c;           // +0x28c (reference; Ghidra: CKMeshPopFxData *)
    IKSerializable* m_unk290;           // +0x290 (reference; Ghidra: CKMeshPopFxData *)
    IKSerializable* m_unk294;           // +0x294 (reference; Ghidra: CKMeshPopFxData *)
    uint8_t m_pad298[0x38];
};
DOTD_ASSERT_SIZE(CKEarthBoulder, 0x2d0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk15c, 0x15c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk180, 0x180);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1ac, 0x1ac);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk224, 0x224);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk27c, 0x27c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_unk294, 0x294);
