// KBase9CCC.h - an unregistered abstract base (key 0x9ccc, Ghidra: CKNPCBehaviourBlockUserBase_maybe; no
// XXL2 counterpart). Original unit: KBase9CCC.cpp (0x5c5838-0x5c58e8). Derived straight from IKSerializable;
// its class is CKNPCBehaviourBlockUser (0x9ecc). Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class KBase9CCC : public IKSerializable {
public:
    KBase9CCC() {}  // 0x005c5860 CKNPCBehaviourBlockUserBase_maybe_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c5870 KStub_Return1_5c5870
};
