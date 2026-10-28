// KBase984C.h - an unregistered abstract base (key 0x984c, Ghidra: CKGolemAttackBase_maybe; no XXL2
// counterpart). Original unit: KBase984C.cpp (0x4c7410-0x4c75f8). Derived straight from IKSerializable;
// its class is CKGolemAttackCommon (0x994c). Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class KBase984C : public IKSerializable {
public:
    KBase984C() {}  // 0x004c7410 CKGolemAttackCommon_ConstructBase_maybe: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c74e8 CKGolemAttackBase_maybe_Load

    IKSerializable* m_unk04;  // +0x04 object reference (level data)
};
DOTD_ASSERT_OFFSET(KBase984C, m_unk04, 0x04);
