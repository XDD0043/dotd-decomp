// CKPoisonGrenade.h - the poison grenade element attack (key 0x948c, vtable 0xb23ca8, size 0x30c). Original unit:
// CKPoisonGrenade.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name. Same member layout as CKBlackBall (whose Load reads it in another order).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKPoisonGrenade : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x252)
    DOTD_DECLARE_FACTORIES(CKPoisonGrenade)

    CKPoisonGrenade() {}  // 0x003b4aa8 CKPoisonGrenade_Construct: the base constructor, then the vtable only
    ~CKPoisonGrenade() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003b7ce0 CKPoisonGrenade_Load

    // Arrays of 3: per level, like the base class's (read element by element).
    float m_unk214[3];             // +0x214
    float m_unk220[3];             // +0x220
    float m_unk22c[3];             // +0x22c
    float m_unk238[3];             // +0x238
    float m_unk244[3];             // +0x244
    float m_unk250[3];             // +0x250
    int32_t m_unk25c[3];           // +0x25c
    int32_t m_unk268[3];           // +0x268
    float m_unk274[3];             // +0x274 (float per CKBlackBall's data; zero here)
    float m_unk280[3];             // +0x280
    IKSerializable* m_unk28c[3];   // +0x28c CKProjectileAccessor (live; read interleaved with +0x298)
    IKSerializable* m_unk298[3];   // +0x298 CKProjectileAccessor (live)
    IKSerializable* m_unk2a4;      // +0x2a4 CKExplosionFxData (live)
    IKSerializable* m_unk2a8;      // +0x2a8 CNode (live)
    uint32_t m_unk2ac[3];          // +0x2ac one 12-byte read, three swapped words (always 0)
    float m_unk2b8[2][3];          // +0x2b8 two 12-byte reads (vectors, _maybe)
    float m_unk2d0[2][3];          // +0x2d0 two 12-byte reads (vectors, _maybe)
    IKSerializable* m_unk2e8;      // +0x2e8 CNode (live)
    float m_unk2ec;                // +0x2ec
    float m_unk2f0;                // +0x2f0
    uint32_t m_unk2f4;             // +0x2f4 (always 0)
    IKSerializable* m_unk2f8;      // +0x2f8 CKSoundDictionaryID (live)
    float m_unk2fc;                // +0x2fc
    uint32_t m_unk300;             // +0x300 (not read)
    uint32_t m_unk304;             // +0x304 (not read)
    uint32_t m_unk308;             // +0x308 (not read)
};
DOTD_ASSERT_SIZE(CKPoisonGrenade, 0x30c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2d0, 0x2d0);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2e8, 0x2e8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2ec, 0x2ec);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2f4, 0x2f4);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2f8, 0x2f8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2fc, 0x2fc);
