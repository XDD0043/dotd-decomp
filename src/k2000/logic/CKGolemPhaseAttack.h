// CKGolemPhaseAttack.h - an attack phase of the golem boss (key 0x97cc, vtable 0xb290c8, size 0x30). Original
// unit: CKGolemPhaseAttack.cpp (0x4baab0-0x4bcf30). Derives from CKGolemPhaseBase (+0x04 the golem hook).
// No XXL2 class of this name: placeholder member names. Its Load builds a tree of heap records: steps, each
// with two lists of attacks, each attack with a list of phase conditions (GolemPhaseCondAnd.h) made through
// the golem hook's CreatePhaseCondition (vt+0x118).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKGolemPhaseBase.h"
#include "k2000/misc/GolemPhaseCondAnd.h"
#include "k2000/util/TVector.h"

class CKGolemPhaseAttack : public CKGolemPhaseBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25f)
    DOTD_DECLARE_FACTORIES(CKGolemPhaseAttack)

    // OperatorNew(0x20) record: an attack of the first kind.
    struct AttackA {
        uint32_t m_unk00;                          // +0x00
        uint32_t m_unk04;                          // +0x04
        TVector<GolemPhaseCond*, 1> m_conditions;  // +0x08 (null entries for condition id -1)
        IKSerializable* m_unk14;                   // +0x14 a reference, read after the conditions
        uint8_t m_unk18;                           // +0x18
        uint8_t m_unk19;                           // +0x19 (+0x1a..+0x1b padding)
        uint8_t m_pad1a[2];
        uint32_t m_unk1c;                          // +0x1c
    };
    // OperatorNew(0x24) record: an attack of the second kind (one more word at +0x08).
    struct AttackB {
        uint32_t m_unk00;                          // +0x00
        uint32_t m_unk04;                          // +0x04
        uint32_t m_unk08;                          // +0x08
        TVector<GolemPhaseCond*, 1> m_conditions;  // +0x0c
        IKSerializable* m_unk18;                   // +0x18
        uint8_t m_unk1c;                           // +0x1c
        uint8_t m_unk1d;                           // +0x1d
        uint8_t m_pad1e[2];
        uint32_t m_unk20;                          // +0x20
    };
    // OperatorNew(0x1c) record: one step of the phase.
    struct Step {
        IKSerializable* m_unk00;           // +0x00 a reference (read first, stored last)
        TVector<AttackA*, 1> m_attacksA;   // +0x04
        TVector<AttackB*, 1> m_attacksB;   // +0x10
    };

    // 0x004bad58 CKGolemPhaseAttack_Construct (inlined the same in Create): the step list empty, capacity 1.
    CKGolemPhaseAttack() {
        m_steps.m_pBlock = nullptr;
        m_steps.m_ui32NbElt = 1;
        m_steps.m_ui32NbUsedElt = 0;
    }
    ~CKGolemPhaseAttack() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004bc3d8 CKGolemPhaseAttack_Load

    TVector<Step*, 1> m_steps;  // +0x08
    uint32_t m_unk14;           // +0x14 runtime
    uint32_t m_unk18;           // +0x18 read first
    uint32_t m_unk1c[5];        // +0x1c..+0x2f runtime
};
DOTD_ASSERT_SIZE(CKGolemPhaseAttack, 0x30);
DOTD_ASSERT_SIZE(CKGolemPhaseAttack::AttackA, 0x20);
DOTD_ASSERT_SIZE(CKGolemPhaseAttack::AttackB, 0x24);
DOTD_ASSERT_SIZE(CKGolemPhaseAttack::Step, 0x1c);
DOTD_ASSERT_OFFSET(CKGolemPhaseAttack, m_steps, 0x08);
DOTD_ASSERT_OFFSET(CKGolemPhaseAttack, m_unk18, 0x18);
