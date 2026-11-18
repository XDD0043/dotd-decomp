// CKColossusContextualAttackElement.h - a colossus attack element (key 0x7d0c, vtable 0xb27678, size 0x68). Original
// unit: CKColossusContextualAttackElement.cpp (0x46ff50-0x470388). Base: KBase7CCC (k2000/misc/KBase7CCC.h), every
// slot from vt+0x50 on is the base's; its own Destroy / RecursiveRegistration / Load only call the base's code. No XXL2
// class; names ours. No game file holds one (work/level-class-keys.json): C2.8 port-final F03.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase7CCC.h"

class CKColossusContextualAttackElement : public KBase7CCC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1f4)  // vt+0x14 / +0x18 0x9c4520 / 0x9c4528
    // vt+0x08 0x9c4500: 0x7d0c or 0xc (not the base's 0x7ccc, as the original answers).
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7d0c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKColossusContextualAttackElement)

    // 0x00470330 CKColossusContextualAttackElement_Create: operator new 0x68, KBase7CCC's constructor 0x471160, the
    // vtable.
    CKColossusContextualAttackElement();  // out of line (the .cpp), as CKBomb's
    // 0x00470110 _Destructor (0x4700c8 _DeletingDestructor adds the delete): the vtable, then KBase7CCC's 0x472938.
    ~CKColossusContextualAttackElement() override;

    void Destroy() override { KBase7CCC::Destroy(); }  // vt+0x10 0x004700a0: 0x4712f8
    // vt+0x24 0x00470078: 0x4712f0 (nothing), 1.
    void RecursiveRegistration(int32_t type) override { KBase7CCC::RecursiveRegistration(type); }
    // vt+0x2c 0x00470028: 0x472148, then 1 whatever it answered.
    int32_t Load(IKFile* file, int32_t type) override {
        KBase7CCC::Load(file, type);
        return 1;
    }
};
static_assert(CKColossusContextualAttackElement::kClassKey == 0x7d0c, "key");
DOTD_ASSERT_SIZE(CKColossusContextualAttackElement, 0x68);
