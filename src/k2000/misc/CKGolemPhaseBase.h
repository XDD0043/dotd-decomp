// CKGolemPhaseBase.h - an unregistered abstract base (key 0x978c, Ghidra: CKGolemPhaseBase_maybe / KBase978C;
// no XXL2 counterpart). Original unit: CKGolemPhaseBase.cpp (0x4c75f8-0x4c7730). Derived straight from
// IKSerializable; its classes are CKGolemPhaseAttack (0x97cc) and CKGolemPhaseQTE (0xa10c), the golem boss's
// phases (CKGolemPhaseManager holds them). Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKGolemPhaseBase : public IKSerializable {
public:
    CKGolemPhaseBase() {}  // 0x004c7620 CKGolemPhaseBase_maybe_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c7630 CKGolemPhaseBase_maybe_Load

    IKSerializable* m_unk04;  // +0x04 object reference (file: the golem hook, CKHkS08DragonCityGolem 0x31c2)
};
DOTD_ASSERT_OFFSET(CKGolemPhaseBase, m_unk04, 0x04);
