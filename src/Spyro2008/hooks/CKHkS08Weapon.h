// CKHkS08Weapon.h - an enemy's weapon hook (key 0x2902, vtable 0xb223f8, size 0xd0). Original unit:
// CKHkS08Weapon.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"

class CKHkS08Weapon : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xa4)
    DOTD_DECLARE_FACTORIES(CKHkS08Weapon)

    // 0x002b1198 CKHkS08Weapon_Create (inlined constructor): the ground-contact defaults and the two bytes
    // at +0xbc/+0xbd = 0xff.
    CKHkS08Weapon() {
        m_unkBD = 0xff;
        m_unkBC = 0xff;
    }
    ~CKHkS08Weapon() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002b1870 CKHkS08Weapon_Load
    void Start() override;  // vt+0x50 0x002b1be8 CKHkS08Weapon_Start (C2.2)
    // The state engine's handler signature (clock, phase 0 tick / 1 enter / 2 leave, the other state) -> next state.
    using StateFn = uint8_t (CKHkS08Weapon::*)(IKTime* clock, int32_t phase, uint8_t other);
    // A handler pair of the table at +0xc0 (descriptor, adjust) called natively; not ported: the state as given.
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);

    // +0x20 the weapon kind_maybe: indexes the per-kind reference counts (kWeaponRefCount, 0xc4092c).
    // Read for every serialization type.
    uint32_t m_unk20;
    uint32_t m_unk24[0x12];                    // +0x24..+0x6b runtime (not set by Create or Load)
    CGroundContactDatasIn m_GContactIn;        // +0x6c
    CGroundContactDatasInOut m_GContactInOut;  // +0x7c
    uint32_t m_unkA8;                          // +0xa8
    IKSerializable** m_apUnkAC;                // +0xac references, sized by the weapon kind (Load)
    uint32_t m_unkB0[2];                       // +0xb0
    void* m_unkB8;                             // +0xb8 runtime: points into +0xc0 (live dump)
    uint8_t m_unkBC;                           // +0xbc constructor 0xff
    uint8_t m_unkBD;                           // +0xbd constructor 0xff
    uint8_t m_padBE[2];
    uint32_t m_unkC0[4];                       // +0xc0 runtime
};
DOTD_ASSERT_SIZE(CKHkS08Weapon, 0xd0);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_GContactIn, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_GContactInOut, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_apUnkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_unkBC, 0xbc);
