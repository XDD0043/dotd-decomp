// CKIceGatling.h - the ice gatling element attack (key 0x940c, vtable 0xb23b80, size 0x264). Original unit:
// CKIceGatling.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKIceGatling : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x250)
    DOTD_DECLARE_FACTORIES(CKIceGatling)

    CKIceGatling() {}  // 0x003aa5b8 CKIceGatling_Construct: the base constructor, then the vtable only
    ~CKIceGatling() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003ab230 CKIceGatling_Load

    float m_unk214[3];             // +0x214 (read interleaved with +0x220: [i], then +0x220[i])
    float m_unk220[3];             // +0x220
    float m_unk22c[3];             // +0x22c
    float m_unk238[3];             // +0x238
    IKSerializable* m_unk244[3];   // +0x244 CKProjectileAccessor (live)
    IKSerializable* m_unk250;      // +0x250 CKAnimatedFxCollection (live)
    IKSerializable* m_unk254[3];   // +0x254 CKExplosionFxData (live)
    uint32_t m_unk260;             // +0x260 (not read)
};
DOTD_ASSERT_SIZE(CKIceGatling, 0x264);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk254, 0x254);
