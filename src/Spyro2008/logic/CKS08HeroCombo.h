// CKS08HeroCombo.h - one node of the hero's combo tree (key 0x7acc, vtable 0xb23180, size 0x1c). Original
// unit: CKS08HeroCombo.cpp (0x36f578-0x36ffa0). No XXL2 class of this name. Five references (combo nodes
// and the blow), then a byte. See outputs/ability-analysis/combat.md (combo tree).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08HeroBlow;

class CKS08HeroCombo : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1eb)
    DOTD_DECLARE_FACTORIES(CKS08HeroCombo)

    CKS08HeroCombo() {}  // inlined in 0x0036f850 CKS08HeroCombo_Create: the vtable only
    ~CKS08HeroCombo() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0036f938 CKS08HeroCombo_Load

    CKS08HeroCombo* m_unk04;  // +0x04 a combo node (file: CKS08HeroCombo references)
    CKS08HeroCombo* m_unk08;  // +0x08 a combo node
    CKS08HeroCombo* m_unk0c;  // +0x0c a combo node
    CKS08HeroBlow* m_pBlow;   // +0x10 the blow of this node (file: CKS08HeroBlow references)
    CKS08HeroCombo* m_unk14;  // +0x14 a combo node
    uint8_t m_unk18;          // +0x18 (+0x19..+0x1b padding)
};
DOTD_ASSERT_SIZE(CKS08HeroCombo, 0x1c);
DOTD_ASSERT_OFFSET(CKS08HeroCombo, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKS08HeroCombo, m_pBlow, 0x10);
DOTD_ASSERT_OFFSET(CKS08HeroCombo, m_unk18, 0x18);
