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
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7acc || key == 0xc; }  // vt+0x08 0x9bed68
    DOTD_DECLARE_FACTORIES(CKS08HeroCombo)

    CKS08HeroCombo() {}  // inlined in 0x0036f850 CKS08HeroCombo_Create: the vtable only
    ~CKS08HeroCombo() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0036f938 CKS08HeroCombo_Load

    // The run-time slots (vt+0x54..+0x68), non-virtual here (no class derives from CKS08HeroCombo).
    CKS08HeroBlow* GetBlow() const { return m_pBlow; }         // vt+0x54 0x009bed40
    void SetBlow(CKS08HeroBlow* blow) { m_pBlow = blow; }     // vt+0x58 0x009bed48
    void SetRef14(CKS08HeroCombo* node) { m_unk14 = node; }   // vt+0x5c 0x009bed50
    CKS08HeroCombo* GetRef14() const { return m_unk14; }      // vt+0x60 0x009bed58
    uint8_t GetByte18() const { return m_unk18; }             // vt+0x64 0x009bed60
    // vt+0x68 0x0036f578 CKS08HeroCombo_GetNext: the next node for a link code: 1 / 7 -> +0x04, 2 / 8 -> +0x08,
    // 3 / 11 -> +0x0c, any other none.
    CKS08HeroCombo* GetNext(uint32_t code) const {
        switch (code) {
            case 1:
            case 7:
                return m_unk04;
            case 2:
            case 8:
                return m_unk08;
            case 3:
            case 11:
                return m_unk0c;
            default:
                return nullptr;
        }
    }

    // 0x0036f610 CKS08HeroCombo_GetMinRemainingDamage: this node's blow's damage plus the least of what its code 1 and code
    // 2 nodes still deal (unsigned: none -1); 0 without a blow, the blow's alone without either node.
    int32_t GetMinRemainingDamage() const;

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
