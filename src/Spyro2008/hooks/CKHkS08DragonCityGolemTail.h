// CKHkS08DragonCityGolemTail.h - the Dragon City golem's tail hook (key 0x33c2, vtable 0xb29f20, size 0xc0).
// Original unit: CKHkS08DragonCityGolemTail.cpp. No XXL2 class. No members of its own; its Load is CKHkGolem's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkGolem.h"

class CKHkS08DragonCityGolemTail : public CKHkGolem {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcf)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5f38
        return key == 0x33c2 || key == 0x3182 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08DragonCityGolemTail)

    CKHkS08DragonCityGolemTail() {}  // 0x004d7108 CKHkS08DragonCityGolemTail_Create (CKHkGolem's constructor)
    ~CKHkS08DragonCityGolemTail() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d6ea8 CKHkS08DragonCityGolemTail_Load
    // vt+0x30 0x004d6e80 CKHkS08DragonCityGolemTail_PostLoad: CKHkGolem's, then 1.
    int32_t PostLoad(int32_t type) override {
        CKHkGolem::PostLoad(type);
        return 1;
    }
    uint32_t GetMaxExplosionMark() override { return 10; }  // vt+0x100 0x004d6d18 CKHkS08DragonCityGolemTail_vf100
    uint32_t GetMaxParticleMark() override { return 1; }    // vt+0x104 0x004d6d20 CKHkS08DragonCityGolemTail_vf104
    uint32_t GetMaxLauncherMark() override { return 1; }    // vt+0x108 0x004d6d28 CKHkS08DragonCityGolemTail_vf108
    // Update / Resume / Pause / Stop / Start / Destroy / RecursiveRegistration and the destructors (0x4d6db8 .. 0x4d6f90)
    // only call CKHkGolem's: inherited.
};
DOTD_ASSERT_SIZE(CKHkS08DragonCityGolemTail, 0xc0);
