// CKKLBCharacterBase.h - the unregistered base of the linked-beacon characters (key 0x9f0c, Ghidra KBase9F0C;
// name _maybe: "KLB" = K linked beacon, from its one registered class CKKLBCharacterSparx 0x9f8c). Not in
// CKKLBCharacterSparx's IsKindOf chain (that is IKSerializable only). Its Load 0x451510 sits in the
// CKLinkedBeaconSeq.cpp unit (0x450df0-0x451658), where it is ported.
// No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKFile;

class CKKLBCharacterBase : public IKSerializable {
public:
    CKKLBCharacterBase() {}  // the derived Create stores the vtable only
    ~CKKLBCharacterBase() override {}

    // vt+0x2c 0x00451510 CKKLBCharacterSparx_LoadBase_maybe (CKLinkedBeaconSeq.cpp): one reference.
    int32_t Load(IKFile* file, int32_t type) override;

    // The character interface sits in slots +0x50 onwards (not IKUpdatable's meanings; the other slots are not
    // declared yet). CKHkLinkedBeacon calls these two (its Start / Restart).
    virtual void Vf50() = 0;  // vt+0x50 CKKLBCharacterSparx_vf50 0x4504f8: bind to the hero group's Sparx
    virtual void Vf54() = 0;  // vt+0x54 CKKLBCharacterSparx_vf54 0x450690: release the Sparx's target

    IKSerializable* m_pBeacon;  // +0x04 CKHkLinkedBeacon* in every live sample (struct draft)_maybe
};
DOTD_ASSERT_SIZE(CKKLBCharacterBase, 0x8);
DOTD_ASSERT_OFFSET(CKKLBCharacterBase, m_pBeacon, 0x04);
