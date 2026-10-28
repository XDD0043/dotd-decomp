// CKPurpleCombo.h - the purple combo attack (key 0xa48c, vtable 0xb23e68, size 0x25c). Original unit:
// CKPurpleCombo.cpp (0x3c1f38-0x3c5af0). Derives from CKAttackMoveElement (its Load and constructor are called
// first). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKAttackMoveElement.h"

class CKPurpleCombo : public CKAttackMoveElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x292)
    DOTD_DECLARE_FACTORIES(CKPurpleCombo)

    CKPurpleCombo() {}  // 0x003c2270 CKPurpleCombo_Construct: CKAttackMoveElement's constructor, then the vtable only
    ~CKPurpleCombo() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003c3048 CKPurpleCombo_Load

    float m_unk1a8[3];               // +0x1a8
    int32_t m_unk1b4[3];             // +0x1b4 (file: 100 150 254)
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
    IKSerializable* m_unk230;        // +0x230
    IKSerializable* m_unk234;        // +0x234
    IKSerializable* m_unk238;        // +0x238
    uint32_t m_unk23c;               // +0x23c (not loaded; live 0)
    IKSerializable* m_unk240;        // +0x240 (live: CKAnimatedFxCollection)
    IKSerializable* m_unk244;        // +0x244 (live: CNode)
    IKSerializable* m_unk248;        // +0x248 (live: CTrailNodeFx)
    uint8_t m_unk24c[0x10];          // +0x24c..+0x25b runtime (not loaded)
};
DOTD_ASSERT_SIZE(CKPurpleCombo, 0x25c);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk248, 0x248);
