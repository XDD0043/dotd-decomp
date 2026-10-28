// CKHkS08Bonus.h - a bonus gem/orb hook (key 0x3302, vtable 0xb2f518, size 0xb8; library-TOC code).
// Original unit: Spyro2008/ui/CKHkS08Bonus.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"

class CKHkS08Bonus : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcc)
    DOTD_DECLARE_FACTORIES(CKHkS08Bonus)

    // 0x005b7580 CKHkS08Bonus_Create (inlined constructor): the IKLife/IKHook defaults, the ground-contact
    // InOut defaults at +0x54 (sector byte, status 3, ground 0, face -1), then the four halfwords at
    // +0xb0..+0xb7 = 0xffff (stored in the order +0xb0, +0xb6, +0xb2, +0xb4). No CGroundContactDatasIn.
    CKHkS08Bonus() {
        m_unkB0[0] = 0xffff;
        m_unkB0[3] = 0xffff;
        m_unkB0[1] = 0xffff;
        m_unkB0[2] = 0xffff;
    }
    ~CKHkS08Bonus() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b7bf0 CKHkS08Bonus_Load

    IKSerializable* m_pUnk20;                  // +0x20 reference (Load)
    uint32_t m_unk24;                          // +0x24 runtime (not set by Create or Load)
    IKSerializable* m_pUnk28;                  // +0x28 reference (Load)
    IKSerializable* m_pUnk2C;                  // +0x2c reference (Load)
    uint32_t m_unk30[9];                       // +0x30..+0x53 runtime
    CGroundContactDatasInOut m_GContactInOut;  // +0x54
    uint32_t m_unk80[12];                      // +0x80..+0xaf runtime
    uint16_t m_unkB0[4];                       // +0xb0 constructor 0xffff each
};
DOTD_ASSERT_SIZE(CKHkS08Bonus, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_GContactInOut, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_unkB0, 0xb0);
