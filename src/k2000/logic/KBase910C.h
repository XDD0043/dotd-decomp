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
    // vt+0x10 0x004ac390 KStub_Nop_4ac390 (the base's Destroy, empty).
    void Destroy() override {}
    // 0x004ac398 CKS08Carrier_DestructBody: the base's vtable, then the root's (nothing to free).
    ~KBase910C() override {}

    // The carrier slots the transportables call (pure in this base; CKS08CarrierHero 0xb28d98, CKS08CarrierEnemy 0xb297e0).
    virtual uint8_t StartCarrying(IKSerializable* /*object*/) { return 0; }  // vt+0x50
    virtual uint8_t StopCarrying(IKSerializable* /*object*/) { return 0; }   // vt+0x54
    virtual uint8_t CanPickUp(IKSerializable* /*object*/) { return 0; }      // vt+0x58
    virtual uint8_t Vf5C(IKSerializable* /*object*/) { return 0; }           // vt+0x5c
    virtual void DropCarriedObject() {}                                     // vt+0x6c
};
