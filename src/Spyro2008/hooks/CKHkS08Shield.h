// CKHkS08Shield.h - an enemy's shield hook (key 0x2f82, vtable 0xb222c8, size 0x24). Original unit:
// CKHkS08Shield.cpp (0x2ac320-0x2acb08). No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"

class CKHkS08Shield : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xbe)
    DOTD_DECLARE_FACTORIES(CKHkS08Shield)

    CKHkS08Shield() {}  // 0x002ac5d8 CKHkS08Shield_Create: the IKLife/IKHook defaults only
    ~CKHkS08Shield() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002ac400 CKHkS08Shield_Load

    uint32_t m_unk20;  // +0x20 read for every serialization type
};
DOTD_ASSERT_SIZE(CKHkS08Shield, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08Shield, m_unk20, 0x20);
