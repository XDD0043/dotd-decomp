// CKS08EnemyCpnt.h - DotD's enemy component: the per-enemy-type tuning data (key 0x906, vtable 0xb22580,
// size 0x568). Original unit: CKS08EnemyCpnt.cpp. No XXL2 class of this name; the fields keep their offset
// names (Ghidra's float/int typing). A second CKHkMoveCpnt is embedded at +0x37c (its own vtable 0xb22630).
#pragma once
#include <cstdint>

#include "k2000/components/CKEnemyCpnt.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/CKHkMoveCpnt.h"
#include "k2000/util/TVector.h"

class CKS08EnemyCpnt : public CKEnemyCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x24)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bccf0
        return key == 0x906 || key == 0x186 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKS08EnemyCpnt)

    // 0x002b3d38 CKS08EnemyCpnt_Create (after CKEnemyCpnt's inlined constructor), in its order; the
    // CKHkMoveCpnt member constructor sets +0x400..+0x408.
    CKS08EnemyCpnt() {
        m_vUnk11c = {nullptr, 1, 0};
        m_vUnk128 = {nullptr, 1, 0};
        m_vUnk348 = {nullptr, 1, 0};
        m_vUnk370 = {nullptr, 1, 0};
    }
    ~CKS08EnemyCpnt() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002b4060 CKS08EnemyCpnt_Load

    // 0x002b3ec0 CKS08EnemyCpnt_GetAttackAnimTableEntryPtr_maybe (port-all P22): the attack's animation row base, the
    // word of 0x00a70400 for the type (+0xb8) plus four rows per attack index (+0x24) of the attack +0x11c[`index`]
    // (CKHkS08Enemy_11.cpp has a copy, AttackAnimBase). vt+0x30 0x002b3c18 PostLoad: 1 (IKSerializable's). vt+0x24
    // 0x002b3c48 RecursiveRegistration: CKEnemyCpnt's, inherited.
    uint32_t GetAttackAnimBase(uint32_t index) const;
    int32_t m_unkb8;  // +0xb8
    uint32_t m_unkbc;  // +0xbc
    float m_unkc0;  // +0xc0
    float m_unkc4;  // +0xc4
    float m_unkc8;  // +0xc8
    float m_unkcc;  // +0xcc
    float m_unkd0;  // +0xd0
    float m_unkd4;  // +0xd4
    float m_unkd8;  // +0xd8
    float m_unkdc;  // +0xdc
    float m_unke0;  // +0xe0
    float m_unke4;  // +0xe4
    uint8_t m_unke8;  // +0xe8
    uint8_t m_pade9;
    uint8_t m_padea;
    uint8_t m_padeb;
    float m_unkec;  // +0xec
    float m_unkf0;  // +0xf0
    float m_unkf4;  // +0xf4
    float m_unkf8;  // +0xf8
    float m_unkfc;  // +0xfc
    uint32_t m_unk100[6];  // +0x100..+0x114 not loaded
    float m_unk118;  // +0x118
    TVector<IKSerializable*, 1> m_vUnk11c;  // +0x11c
    TVector<IKSerializable*, 1> m_vUnk128;  // +0x128
    uint32_t m_unk134[21];  // +0x134..+0x184 not loaded
    float m_unk188;  // +0x188
    uint32_t m_unk18c;  // +0x18c not loaded
    float m_unk190;  // +0x190
    float m_unk194;  // +0x194
    int32_t m_unk198;  // +0x198
    int32_t m_unk19c;  // +0x19c
    int32_t m_unk1a0;  // +0x1a0
    int32_t m_unk1a4;  // +0x1a4
    float m_unk1a8;  // +0x1a8
    float m_unk1ac;  // +0x1ac
    float m_unk1b0;  // +0x1b0
    float m_unk1b4;  // +0x1b4
    float m_unk1b8;  // +0x1b8
    float m_unk1bc;  // +0x1bc
    float m_unk1c0;  // +0x1c0
    float m_unk1c4;  // +0x1c4
    int32_t m_unk1c8;  // +0x1c8
    float m_unk1cc;  // +0x1cc
    float m_unk1d0;  // +0x1d0
    float m_unk1d4;  // +0x1d4
    float m_unk1d8;  // +0x1d8
    float m_unk1dc;  // +0x1dc
    float m_unk1e0;  // +0x1e0
    float m_unk1e4;  // +0x1e4
    float m_unk1e8;  // +0x1e8
    float m_unk1ec;  // +0x1ec
    float m_unk1f0;  // +0x1f0
    uint32_t m_unk1f4;  // +0x1f4
    uint8_t m_unk1f8;  // +0x1f8
    uint8_t m_unk1f9;  // +0x1f9
    uint8_t m_pad1fa;
    uint8_t m_pad1fb;
    float m_unk1fc;  // +0x1fc
    float m_unk200;  // +0x200
    float m_unk204;  // +0x204
    float m_unk208;  // +0x208
    float m_unk20c;  // +0x20c
    float m_unk210;  // +0x210
    float m_unk214;  // +0x214
    float m_unk218;  // +0x218
    float m_unk21c;  // +0x21c
    float m_unk220;  // +0x220
    IKSerializable* m_pUnk224;  // +0x224 reference
    float m_unk228;  // +0x228
    uint32_t m_unk22c;  // +0x22c not loaded
    float m_unk230;  // +0x230
    float m_unk234;  // +0x234
    float m_unk238;  // +0x238
    float m_unk23c;  // +0x23c
    float m_unk240;  // +0x240
    float m_unk244;  // +0x244
    float m_unk248;  // +0x248
    float m_unk24c;  // +0x24c
    float m_unk250;  // +0x250
    float m_unk254;  // +0x254
    float m_unk258;  // +0x258
    float m_unk25c;  // +0x25c
    float m_unk260;  // +0x260
    float m_unk264;  // +0x264
    float m_unk268;  // +0x268
    float m_unk26c;  // +0x26c
    float m_unk270;  // +0x270
    float m_unk274;  // +0x274
    float m_unk278;  // +0x278
    float m_unk27c;  // +0x27c
    float m_unk280;  // +0x280
    float m_unk284;  // +0x284
    float m_unk288;  // +0x288
    uint8_t m_unk28c;  // +0x28c
    uint8_t m_pad28d;
    uint8_t m_pad28e;
    uint8_t m_pad28f;
    float m_unk290;  // +0x290
    float m_unk294;  // +0x294
    float m_unk298;  // +0x298
    float m_unk29c;  // +0x29c
    float m_unk2a0;  // +0x2a0
    float m_unk2a4;  // +0x2a4
    float m_unk2a8;  // +0x2a8
    float m_unk2ac;  // +0x2ac
    float m_unk2b0;  // +0x2b0
    float m_unk2b4;  // +0x2b4
    float m_unk2b8;  // +0x2b8
    float m_unk2bc;  // +0x2bc
    float m_unk2c0;  // +0x2c0
    float m_unk2c4;  // +0x2c4
    float m_unk2c8;  // +0x2c8
    float m_unk2cc;  // +0x2cc
    float m_unk2d0;  // +0x2d0
    float m_unk2d4;  // +0x2d4
    float m_unk2d8;  // +0x2d8
    float m_unk2dc;  // +0x2dc
    float m_unk2e0;  // +0x2e0
    float m_unk2e4;  // +0x2e4
    float m_unk2e8;  // +0x2e8
    float m_unk2ec;  // +0x2ec
    float m_unk2f0;  // +0x2f0
    float m_unk2f4;  // +0x2f4
    float m_unk2f8;  // +0x2f8
    float m_unk2fc;  // +0x2fc
    float m_unk300;  // +0x300
    float m_unk304;  // +0x304
    float m_unk308;  // +0x308
    int32_t m_unk30c;  // +0x30c
    float m_unk310;  // +0x310
    float m_unk314;  // +0x314
    float m_unk318;  // +0x318
    float m_unk31c;  // +0x31c
    float m_unk320;  // +0x320
    float m_unk324;  // +0x324
    float m_unk328;  // +0x328
    IKSerializable* m_pUnk32c;  // +0x32c reference
    class IKFx* m_unk330;  // +0x330 not loaded: the stun spark held (CKHkS08Enemy_SetStunFxActive_maybe)
    float m_unk334;  // +0x334
    uint8_t m_unk338;  // +0x338
    uint8_t m_pad339;
    uint8_t m_pad33a;
    uint8_t m_pad33b;
    int32_t m_unk33c;  // +0x33c
    int32_t m_unk340;  // +0x340
    IKSerializable* m_pUnk344;  // +0x344 reference
    TVector<uint8_t, 1> m_vUnk348;  // +0x348
    float m_unk354;  // +0x354
    float m_unk358;  // +0x358
    float m_unk35c;  // +0x35c
    float m_unk360;  // +0x360
    float m_unk364;  // +0x364
    float m_unk368;  // +0x368
    float m_unk36c;  // +0x36c
    TVector<uint8_t, 1> m_vUnk370;  // +0x370
    CKHkMoveCpnt m_MoveCpnt37c;  // +0x37c a second CKHkMoveCpnt (its own vtable)
    uint32_t m_aUnk428[12];  // +0x428..+0x454
    float m_unk458;  // +0x458
    float m_unk45c;  // +0x45c
    float m_unk460;  // +0x460
    float m_unk464;  // +0x464
    float m_unk468;  // +0x468
    float m_unk46c;  // +0x46c
    float m_unk470;  // +0x470
    uint8_t m_unk474;  // +0x474
    uint8_t m_pad475;
    uint8_t m_pad476;
    uint8_t m_pad477;
    float m_unk478;  // +0x478
    int32_t m_unk47c;  // +0x47c
    int32_t m_unk480;  // +0x480
    float m_unk484;  // +0x484
    float m_unk488;  // +0x488
    float m_unk48c;  // +0x48c
    float m_unk490;  // +0x490
    float m_unk494;  // +0x494
    float m_unk498;  // +0x498
    float m_unk49c;  // +0x49c
    float m_unk4a0;  // +0x4a0
    float m_unk4a4;  // +0x4a4
    float m_unk4a8;  // +0x4a8
    float m_unk4ac;  // +0x4ac
    float m_unk4b0;  // +0x4b0
    IKSerializable* m_pUnk4b4;  // +0x4b4 reference
    float m_unk4b8;  // +0x4b8
    uint8_t m_unk4bc;  // +0x4bc
    uint8_t m_unk4bd;  // +0x4bd
    uint8_t m_pad4be;
    uint8_t m_pad4bf;
    float m_unk4c0;  // +0x4c0
    float m_unk4c4;  // +0x4c4
    float m_unk4c8;  // +0x4c8
    float m_unk4cc;  // +0x4cc
    float m_unk4d0;  // +0x4d0
    float m_unk4d4;  // +0x4d4
    float m_unk4d8;  // +0x4d8
    int32_t m_unk4dc;  // +0x4dc
    float m_unk4e0;  // +0x4e0
    float m_unk4e4;  // +0x4e4
    float m_unk4e8;  // +0x4e8
    float m_unk4ec;  // +0x4ec
    IKSerializable* m_pUnk4f0;  // +0x4f0 reference
    float m_unk4f4;  // +0x4f4
    float m_unk4f8;  // +0x4f8
    float m_unk4fc;  // +0x4fc
    float m_unk500;  // +0x500
    float m_unk504;  // +0x504
    float m_unk508;  // +0x508
    float m_unk50c;  // +0x50c
    float m_unk510;  // +0x510
    float m_unk514;  // +0x514
    float m_unk518;  // +0x518
    float m_unk51c;  // +0x51c
    float m_unk520;  // +0x520
    float m_unk524;  // +0x524
    float m_unk528;  // +0x528
    float m_unk52c;  // +0x52c
    float m_unk530;  // +0x530
    float m_unk534;  // +0x534
    float m_unk538;  // +0x538
    float m_unk53c;  // +0x53c
    float m_unk540;  // +0x540
    IKSerializable* m_pUnk544;  // +0x544 reference
    IKSerializable* m_pUnk548;  // +0x548 reference
    float m_unk54c;  // +0x54c
    float m_unk550;  // +0x550
    float m_unk554;  // +0x554
    float m_unk558;  // +0x558
    float m_unk55c;  // +0x55c
    float m_unk560;  // +0x560
    float m_unk564;  // +0x564
};
static_assert(CKS08EnemyCpnt::kClassKey == 0x906, "key");
DOTD_ASSERT_SIZE(CKS08EnemyCpnt, 0x568);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkb8, 0xb8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkbc, 0xbc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkc0, 0xc0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkc4, 0xc4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkc8, 0xc8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkcc, 0xcc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkd0, 0xd0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkd4, 0xd4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkd8, 0xd8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkdc, 0xdc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unke0, 0xe0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unke4, 0xe4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unke8, 0xe8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkec, 0xec);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkf0, 0xf0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkf4, 0xf4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkf8, 0xf8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unkfc, 0xfc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_vUnk11c, 0x11c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_vUnk128, 0x128);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1ac, 0x1ac);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1f9, 0x1f9);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_pUnk224, 0x224);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk27c, 0x27c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2b4, 0x2b4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2bc, 0x2bc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2c0, 0x2c0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2c4, 0x2c4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2c8, 0x2c8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2cc, 0x2cc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2d0, 0x2d0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2d4, 0x2d4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2d8, 0x2d8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2dc, 0x2dc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2e0, 0x2e0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2e4, 0x2e4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2e8, 0x2e8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2ec, 0x2ec);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2f4, 0x2f4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2f8, 0x2f8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk2fc, 0x2fc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk300, 0x300);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk304, 0x304);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk308, 0x308);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk30c, 0x30c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk310, 0x310);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk314, 0x314);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk318, 0x318);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk31c, 0x31c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk320, 0x320);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk324, 0x324);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk328, 0x328);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_pUnk32c, 0x32c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk330, 0x330);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk334, 0x334);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk338, 0x338);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk33c, 0x33c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk340, 0x340);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_pUnk344, 0x344);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_vUnk348, 0x348);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk354, 0x354);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk358, 0x358);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk35c, 0x35c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk360, 0x360);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk364, 0x364);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk368, 0x368);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk36c, 0x36c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_vUnk370, 0x370);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_MoveCpnt37c, 0x37c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_aUnk428, 0x428);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk458, 0x458);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk45c, 0x45c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk460, 0x460);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk464, 0x464);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk468, 0x468);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk46c, 0x46c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk470, 0x470);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk474, 0x474);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk478, 0x478);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk47c, 0x47c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk480, 0x480);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk484, 0x484);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk488, 0x488);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk48c, 0x48c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk490, 0x490);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk494, 0x494);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk498, 0x498);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk49c, 0x49c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4a0, 0x4a0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4a4, 0x4a4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4a8, 0x4a8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4ac, 0x4ac);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4b0, 0x4b0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_pUnk4b4, 0x4b4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4b8, 0x4b8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4bc, 0x4bc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4bd, 0x4bd);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4c0, 0x4c0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4c4, 0x4c4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4c8, 0x4c8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4cc, 0x4cc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4d0, 0x4d0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4d4, 0x4d4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4d8, 0x4d8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4dc, 0x4dc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4e0, 0x4e0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4e4, 0x4e4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4e8, 0x4e8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4ec, 0x4ec);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_pUnk4f0, 0x4f0);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4f4, 0x4f4);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4f8, 0x4f8);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk4fc, 0x4fc);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk500, 0x500);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk504, 0x504);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk508, 0x508);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk50c, 0x50c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk510, 0x510);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk514, 0x514);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk518, 0x518);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk51c, 0x51c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk520, 0x520);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk524, 0x524);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk528, 0x528);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk52c, 0x52c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk530, 0x530);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk534, 0x534);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk538, 0x538);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk53c, 0x53c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk540, 0x540);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_pUnk544, 0x544);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_pUnk548, 0x548);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk54c, 0x54c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk550, 0x550);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk554, 0x554);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk558, 0x558);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk55c, 0x55c);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk560, 0x560);
DOTD_ASSERT_OFFSET(CKS08EnemyCpnt, m_unk564, 0x564);
