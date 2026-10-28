// CKWindTwister.h - the wind twister attack (key 0x98cc, vtable 0xb249c0, size 0x344). Original unit: CKWindTwister.cpp
// (0x3e6f80-0x3ee198). Derives from CKTransformElement (its Load is called first). No XXL2 class of this name: the
// members keep placeholder names (types from the Ghidra struct and the level data). Unread runtime state is padding.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"

class CKWindTwister : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x263)
    DOTD_DECLARE_FACTORIES(CKWindTwister)

    CKWindTwister() {}  // 0x003e7740 CKWindTwister_Construct: CKTransformElement's constructor, then the vtable only
    ~CKWindTwister() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003e8260 CKWindTwister_Load

    float m_unk154[3];                  // +0x154 per level
    int32_t m_unk160[3];                // +0x160 per level
    uint32_t m_unk16c[3];               // +0x16c per level (type unknown)
    uint32_t m_unk178[3];               // +0x178 per level (type unknown)
    float m_unk184[3];                  // +0x184 per level
    float m_unk190;                     // +0x190
    float m_unk194;                     // +0x194
    float m_unk198;                     // +0x198
    float m_unk19c[3];                  // +0x19c per level
    int32_t m_unk1a8[3];                // +0x1a8 per level
    uint32_t m_unk1b4[3];               // +0x1b4 per level (type unknown)
    uint32_t m_unk1c0[3];               // +0x1c0 per level (type unknown)
    float m_unk1cc[3];                  // +0x1cc per level
    float m_unk1d8;                     // +0x1d8
    float m_unk1dc;                     // +0x1dc
    float m_unk1e0;                     // +0x1e0
    float m_unk1e4[3];                  // +0x1e4 per level
    float m_unk1f0[3];                  // +0x1f0 per level
    float m_unk1fc[3];                  // +0x1fc per level
    uint32_t m_unk208[3];               // +0x208 per level (type unknown)
    uint32_t m_unk214[3];               // +0x214 per level (type unknown)
    uint32_t m_unk220[3];               // +0x220 per level (type unknown)
    float m_unk22c[3];                  // +0x22c per level
    float m_unk238;                     // +0x238
    float m_unk23c;                     // +0x23c
    float m_unk240;                     // +0x240
    float m_unk244[3];                  // +0x244 per level
    uint32_t m_unk250[3];               // +0x250 per level (type unknown)
    float m_unk25c[3];                  // +0x25c per level
    float m_unk268;                     // +0x268
    float m_unk26c;                     // +0x26c
    float m_unk270;                     // +0x270
    float m_unk274;                     // +0x274
    float m_unk278;                     // +0x278
    float m_unk27c;                     // +0x27c
    IKSerializable* m_unk280;           // +0x280 (reference; Ghidra: CKS08ElementDamage *)
    IKSerializable* m_unk284;           // +0x284 (reference; Ghidra: CKImpulsionCpnt *)
    IKSerializable* m_unk288;           // +0x288 (reference; Ghidra: CKMeshPopFxData *)
    uint8_t m_pad28c[0x4];
    float m_unk290;                     // +0x290
    float m_unk294;                     // +0x294
    float m_unk298;                     // +0x298
    float m_unk29c;                     // +0x29c
    float m_unk2a0;                     // +0x2a0
    float m_unk2a4;                     // +0x2a4
    int32_t m_unk2a8;                   // +0x2a8
    uint32_t m_unk2ac;                  // +0x2ac (type unknown)
    IKSerializable* m_unk2b0;           // +0x2b0 (reference)
    uint8_t m_pad2b4[0x4];
    IKSerializable* m_unk2b8;           // +0x2b8 (reference)
    IKSerializable* m_unk2bc;           // +0x2bc (reference)
    uint8_t m_pad2c0[0x4];
    IKSerializable* m_unk2c4;           // +0x2c4 (reference)
    uint8_t m_pad2c8[0x4];
    IKSerializable* m_unk2cc;           // +0x2cc (reference; Ghidra: CNode *)
    IKSerializable* m_unk2d0;           // +0x2d0 (reference; Ghidra: CNode *)
    IKSerializable* m_unk2d4;           // +0x2d4 (reference; Ghidra: CNode *)
    IKSerializable* m_unk2d8;           // +0x2d8 (reference; Ghidra: CTrailNodeFx *)
    IKSerializable* m_unk2dc;           // +0x2dc (reference)
    IKSerializable* m_unk2e0;           // +0x2e0 (reference)
    uint8_t m_pad2e4[0x4];
    IKSerializable* m_unk2e8;           // +0x2e8 (reference; Ghidra: CKProjectileAccessor *)
    IKSerializable* m_unk2ec;           // +0x2ec (reference; Ghidra: CKProjectileAccessor *)
    IKSerializable* m_unk2f0;           // +0x2f0 (reference; Ghidra: CKS08ElementDamage *)
    float m_unk2f4;                     // +0x2f4
    float m_unk2f8;                     // +0x2f8
    float m_unk2fc;                     // +0x2fc
    float m_unk300;                     // +0x300
    float m_unk304;                     // +0x304
    float m_unk308;                     // +0x308
    IKSerializable* m_unk30c;           // +0x30c (reference; Ghidra: CKSoundDictionaryID *)
    float m_unk310;                     // +0x310
    uint8_t m_pad314[0x30];
};
DOTD_ASSERT_SIZE(CKWindTwister, 0x344);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk27c, 0x27c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2bc, 0x2bc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2c4, 0x2c4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2cc, 0x2cc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2d0, 0x2d0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2d4, 0x2d4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2d8, 0x2d8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2dc, 0x2dc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2e0, 0x2e0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2e8, 0x2e8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2ec, 0x2ec);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2f4, 0x2f4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2f8, 0x2f8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2fc, 0x2fc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk300, 0x300);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk304, 0x304);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk308, 0x308);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk30c, 0x30c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk310, 0x310);
