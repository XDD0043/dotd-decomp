// CKS08HeroElementShadow.h - the shadow hero element (key 0x8a8c, vtable 0xb243e0, size 0x2cc: no members of its own).
// Original unit: render/CKS08HeroElementShadow.cpp (0x3d0f88-0x3d1298). C2.8 port-final F08. No XXL2 class of this name; no
// level file of DotD holds one (CKS08HeroElement.h). Every element slot is the base's; Load / PostLoad / Destroy /
// RecursiveRegistration call the base's.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08HeroElement.h"

class CKS08HeroElementShadow : public CKS08HeroElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x22a)
    // vt+0x08 0x009c0578 CKS08HeroElementShadow_IsKindOfClass
    int32_t IsKindOfClass(uint32_t key) override {
        return (key == 0x8a8c || key == 0x890c) ? 1 : (key == 0xc ? 1 : 0);
    }
    DOTD_DECLARE_FACTORIES(CKS08HeroElementShadow)

    CKS08HeroElementShadow() {}  // inlined in 0x003d11e0 CKS08HeroElementShadow_Create: the vtable only
    // 0x009c05c0 Destructor / 0x009c05e0 DeletingDestructor: the base's vtables back, nothing freed.
    ~CKS08HeroElementShadow() override {}
    void Destroy() override;                            // vt+0x10 0x003d1088: the base's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x003d1060: the base's, then 1
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d1010: the base's, then 1
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003d1218: the base's, then 1
};
DOTD_ASSERT_SIZE(CKS08HeroElementShadow, 0x2cc);
