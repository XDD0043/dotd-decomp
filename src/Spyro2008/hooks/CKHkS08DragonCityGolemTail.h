// CKHkS08DragonCityGolemTail.h - the Dragon City golem's tail hook (key 0x33c2, vtable 0xb29f20, size 0xc0).
// Original unit: CKHkS08DragonCityGolemTail.cpp. No XXL2 class. No members of its own; its Load is CKHkGolem's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkGolem.h"

class CKHkS08DragonCityGolemTail : public CKHkGolem {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcf)
    DOTD_DECLARE_FACTORIES(CKHkS08DragonCityGolemTail)

    CKHkS08DragonCityGolemTail() {}  // 0x004d7108 CKHkS08DragonCityGolemTail_Create (CKHkGolem's constructor)
    ~CKHkS08DragonCityGolemTail() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d6ea8 CKHkS08DragonCityGolemTail_Load
};
DOTD_ASSERT_SIZE(CKHkS08DragonCityGolemTail, 0xc0);
