// CKBlackCombo.h - the black combo attack (key 0xa44c, vtable 0xb234e8, size 0x260). Original unit:
// CKBlackCombo.cpp (0x37d2e0-0x380ed0). Derives from CKAttackMoveElement (its Load and constructor are called
// first). No XXL2 class of this name. Same layout and Load as CKPoisonSpin.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKAttackMoveElement.h"

class CKBlackCombo : public CKAttackMoveElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x291)
    DOTD_DECLARE_FACTORIES(CKBlackCombo)

    CKBlackCombo() {}  // 0x0037d7c8 CKBlackCombo_Construct: CKAttackMoveElement's constructor, then the vtable only
    ~CKBlackCombo() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0037e4f0 CKBlackCombo_Load

    float m_unk1a8[3];               // +0x1a8
    int32_t m_unk1b4[3];             // +0x1b4 (file: 254 254 254)
    int32_t m_unk1c0[3];             // +0x1c0 (file: 0; int assumed, as +0x1b4)
    int32_t m_unk1cc[3];             // +0x1cc (file: 0)
    float m_unk1d8[3];               // +0x1d8
    CKAttackMoveVec3 m_unk1e4[3];    // +0x1e4
    float m_unk208;                  // +0x208
    float m_unk20c;                  // +0x20c
    float m_unk210[3];               // +0x210
    IKSerializable* m_unk21c;        // +0x21c (live: CKAimCamembert)
    IKSerializable* m_unk220;        // +0x220 (live: CKExplosionFxData)
    IKSerializable* m_unk224;        // +0x224 (live: CKExplosionFxData)
    IKSerializable* m_unk228;        // +0x228 (live: CKExplosionFxData)
    IKSerializable* m_unk22c;        // +0x22c (live: CKExplosionFxData)
    IKSerializable* m_unk230;        // +0x230 (live: CKExplosionFxData)
    IKSerializable* m_unk234;        // +0x234
    uint32_t m_unk238;               // +0x238 (not loaded; live 0)
    IKSerializable* m_unk23c;        // +0x23c
    uint32_t m_unk240;               // +0x240 (not loaded; live 0)
    IKSerializable* m_unk244;        // +0x244 (live: CKAnimatedFxCollection)
    IKSerializable* m_unk248;        // +0x248 (live: CNode)
    IKSerializable* m_unk24c;        // +0x24c (live: CTrailNodeFx)
    uint8_t m_unk250[0x10];          // +0x250..+0x25f runtime (not loaded)
};
DOTD_ASSERT_SIZE(CKBlackCombo, 0x260);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk24c, 0x24c);
