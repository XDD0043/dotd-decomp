// CKEarthMissile.h - the earth missile element attack (key 0x938c, vtable 0xb23758, size 0x27c). Original
// unit: CKEarthMissile.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKEarthMissile : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24e)
    DOTD_DECLARE_FACTORIES(CKEarthMissile)

    CKEarthMissile() {}  // 0x00392ac8 CKEarthMissile_Construct: the base constructor, then the vtable only
    ~CKEarthMissile() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00394778 CKEarthMissile_Load

    float m_unk214[3];             // +0x214 (read interleaved with +0x220)
    float m_unk220[3];             // +0x220
    IKSerializable* m_unk22c[3];   // +0x22c CKProjectileAccessor (live; read interleaved with +0x238)
    IKSerializable* m_unk238[3];   // +0x238 CKProjectileAccessor (live)
    IKSerializable* m_unk244;      // +0x244 CKAnimatedFxCollection (live)
    IKSerializable* m_unk248;      // +0x248 CKExplosionFxData (live)
    IKSerializable* m_unk24c;      // +0x24c CNode (live)
    uint32_t m_unk250;             // +0x250 (always 0)
    float m_unk254;                // +0x254
    uint32_t m_unk258;             // +0x258 (always 0)
    IKSerializable* m_unk25c;      // +0x25c CNode (live)
    float m_unk260;                // +0x260
    float m_unk264;                // +0x264
    uint32_t m_unk268;             // +0x268 (always 0)
    IKSerializable* m_unk26c;      // +0x26c CKSoundDictionaryID (live)
    float m_unk270;                // +0x270
    uint32_t m_unk274;             // +0x274 (not read)
    uint32_t m_unk278;             // +0x278 (not read; live: a CKObjectRoot pointer)
};
DOTD_ASSERT_SIZE(CKEarthMissile, 0x27c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk270, 0x270);
