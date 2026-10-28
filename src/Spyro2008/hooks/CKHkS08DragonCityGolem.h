// CKHkS08DragonCityGolem.h - the Dragon City golem's hook (key 0x31c2, vtable 0xb29df0, size 0xe0). Original
// unit: CKHkS08DragonCityGolem.cpp. No XXL2 class. Its Load is CKHkGolem's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkGolem.h"

class CKHkS08DragonCityGolem : public CKHkGolem {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc7)
    DOTD_DECLARE_FACTORIES(CKHkS08DragonCityGolem)

    // 0x004d6468 CKHkS08DragonCityGolem_Create (inlined constructor): CKHkGolem's, then +0xc0 = 0.
    CKHkS08DragonCityGolem() { m_unkC0 = 0; }
    ~CKHkS08DragonCityGolem() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d5c38 CKHkS08DragonCityGolem_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004d5c10 CKHkS08DragonCityGolem_PostLoad
    void Start() override;  // vt+0x50 0x004d5bb8 CKHkS08DragonCityGolem_Start (C2.2)

    uint32_t m_unkC0;       // +0xc0 constructor 0
    uint32_t m_unkC4[7];    // +0xc4 runtime
};
DOTD_ASSERT_SIZE(CKHkS08DragonCityGolem, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08DragonCityGolem, m_unkC0, 0xc0);
