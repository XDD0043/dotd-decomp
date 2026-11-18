// KBase9CCC.h - an unregistered abstract base (key 0x9ccc, Ghidra: CKNPCBehaviourBlockUserBase_maybe; no
// XXL2 counterpart). Original unit: KBase9CCC.cpp (0x5c5838-0x5c58e8). Derived straight from IKSerializable;
// its class is CKNPCBehaviourBlockUser (0x9ecc). Its vtable 0xb2fe10 (TOC1 -0x5fe4) adds the user side of the
// behaviour blocks at +0x50..+0x64, all pure (__cxa_pure_virtual): what a block (KBase9C8C) asks of the one it runs
// for.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class KBase9C8C;

class KBase9CCC : public IKSerializable {
public:
    KBase9CCC() {}  // 0x005c5860 CKNPCBehaviourBlockUserBase_maybe_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c5870 KStub_Return1_5c5870

    virtual IKSerializable* GetOwner() = 0;                  // vt+0x50: the object the blocks run for
    virtual IKSerializable* GetAnimatedNode() = 0;           // vt+0x54: its CAnimatedNode
    virtual IKSerializable* GetMovable() = 0;                // vt+0x58: its node as a CSGMovable
    virtual void SetStream(IKSerializable* stream) = 0;      // vt+0x5c: the cinematic stream a block plays (or 0)
    virtual IKSerializable* GetHotSpot() = 0;                // vt+0x60
    virtual void OnBlockDone(KBase9C8C* block) = 0;          // vt+0x64: a block reached its end
};
