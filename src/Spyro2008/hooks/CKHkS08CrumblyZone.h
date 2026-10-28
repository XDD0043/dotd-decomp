// CKHkS08CrumblyZone.h - Spyro's crumbly zone (key 0x2ec2, vtable 0xb25ae8, size 0x1cc). Original unit:
// CKHkS08CrumblyZone.cpp (0x4140f0-0x4150b8). No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkCrumblyZone.h"

class CKHkS08CrumblyZone : public CKHkCrumblyZone {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xbb)
    DOTD_DECLARE_FACTORIES(CKHkS08CrumblyZone)

    // 0x00414e60 CKHkS08CrumblyZone_Create (inlined constructor): the base's only.
    CKHkS08CrumblyZone() {}
    ~CKHkS08CrumblyZone() override {}

    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004143d0 CKHkS08CrumblyZone_PostLoad: CKHkCrumblyZone's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00414f28 CKHkS08CrumblyZone_Load
    void Start() override;  // vt+0x50 0x00414320 CKHkS08CrumblyZone_Start (C2.2)
    void VfA0() override;   // vt+0xa0 0x004142b0 CKHkS08CrumblyZone_OnActivate (C2.4 exit)

    uint32_t m_unk1BC;     // +0x1bc
    uint8_t m_unk1C0;      // +0x1c0 read last
    uint8_t m_unk1C1;      // +0x1c1
    uint8_t m_unk1C2;      // +0x1c2
    uint8_t m_pad1C3;
    uint32_t m_unk1C4;     // +0x1c4
    uint32_t m_unk1C8;     // +0x1c8 not set by Create or Load
};
DOTD_ASSERT_SIZE(CKHkS08CrumblyZone, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1BC, 0x1bc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C0, 0x1c0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C1, 0x1c1);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C2, 0x1c2);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C4, 0x1c4);
