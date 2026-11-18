// CKS08HeroElementWind.h - the wind hero element (key 0x8acc, vtable 0xb24528, size 0x2cc: no members of its own).
// Original unit: CKS08HeroElementWind.cpp (0x3d1298-0x3d1550). C2.8 port-final F08. No XXL2 class of this name; no
// level file of DotD holds one (CKS08HeroElement.h). Every element slot is the base's; Load / PostLoad / Destroy /
// RecursiveRegistration call the base's.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08HeroElement.h"

class CKS08HeroElementWind : public CKS08HeroElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x22b)
    // vt+0x08 0x009c0628 CKS08HeroElementWind_IsKindOfClass
    int32_t IsKindOfClass(uint32_t key) override {
        return (key == 0x8acc || key == 0x890c) ? 1 : (key == 0xc ? 1 : 0);
    }
    DOTD_DECLARE_FACTORIES(CKS08HeroElementWind)

    CKS08HeroElementWind() {}  // inlined in 0x003d14f0 CKS08HeroElementWind_Create: the vtable only
    // 0x009c0670 Destructor / 0x009c0690 DeletingDestructor: the base's vtables back, nothing freed.
    ~CKS08HeroElementWind() override {}
    void Destroy() override;                            // vt+0x10 0x003d1398: the base's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x003d1370: the base's, then 1
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d1320: the base's, then 1
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003d1528: the base's, then 1
};
DOTD_ASSERT_SIZE(CKS08HeroElementWind, 0x2cc);
