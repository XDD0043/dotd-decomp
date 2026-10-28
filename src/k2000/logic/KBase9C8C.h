// KBase9C8C.h - an unregistered abstract base (key 0x9c8c, Ghidra: CKBhvBlockBase_maybe; no XXL2
// counterpart). Original unit: KBase9C8C.cpp (0x5c5788-0x5c5838). Derived straight from IKSerializable;
// base of the behaviour blocks (CKBhvBlockProjectiles 0xa7cc; _maybe also CKBhvBlockAnimation and
// CKBhvBlockSpeech). Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class KBase9C8C : public IKSerializable {
public:
    KBase9C8C() {}  // 0x005c5788 CKBhvBlockBase_maybe_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c57b0 BhvBlockBase_Load_maybe
};
