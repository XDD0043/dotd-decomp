// KBase910C.h - an unregistered abstract base (key 0x910c, Ghidra: CKS08CarrierBase_maybe; no XXL2
// counterpart). Original unit: KBase910C.cpp (0x4ac358-0x4ac580). Derived straight from IKSerializable;
// its classes are CKS08CarrierHero (0x91cc) and CKS08CarrierEnemy (0x958c). Minimal for C2.1: constructor
// and Load.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class KBase910C : public IKSerializable {
public:
    KBase910C() {}  // 0x004ac358 CKS08CarrierBase_maybe_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004ac380 KStub_Return1_4ac380
};
