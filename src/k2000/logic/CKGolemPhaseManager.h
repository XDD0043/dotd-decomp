// CKGolemPhaseManager.h - the golem boss's phase list (key 0x974c, vtable 0xb29160, size 0x28). Original unit:
// CKGolemPhaseManager.cpp (0x4bcf30-0x4bddd8). Derived straight from IKSerializable. No XXL2 class of this
// name: the members keep placeholder names. Minimal for C2.1: constructor and Load. Two inlined growable
// arrays (TVector, grow by 1) of references.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKGolemPhaseManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25d)
    DOTD_DECLARE_FACTORIES(CKGolemPhaseManager)

    CKGolemPhaseManager();  // 0x004bcf80 CKGolemPhaseManager_Construct
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004bd7d8 CKGolemPhaseManager_Load

    IKSerializable* m_unk04;                   // +0x04 object reference (file: the golem hook, 0x31c2)
    TVector<IKSerializable*, 1> m_phases;      // +0x08 CKGolemPhaseAttack / CKGolemPhaseQTE references
    TVector<IKSerializable*, 1> m_unk14;       // +0x14 CKGolemAttackCommon references
    int32_t m_unk20;                           // +0x20 PostLoad: -1 (_maybe: the current phase index)
    int32_t m_unk24;                           // +0x24 (file: -1, 0, 1)
};
DOTD_ASSERT_SIZE(CKGolemPhaseManager, 0x28);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_phases, 0x08);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk24, 0x24);
