// CKColossusBaseAttackElement.h - a colossus attack element (key 0x7e8c, vtable 0xb275e8, size 0x68). Original unit:
// CKColossusBaseAttackElement.cpp (0x46faa0-0x46ff50). Base: KBase7CCC (k2000/misc/KBase7CCC.h). Its own slots only
// call the base's code (non-virtual `bl`): vt+0x10 / +0x24 / +0x2c / +0x50 / +0x54 / +0x60. No XXL2 class; names ours.
// No game file holds one (work/level-class-keys.json): C2.8 port-final F03.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase7CCC.h"

class CKColossusBaseAttackElement : public KBase7CCC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1fa)  // vt+0x14 / +0x18 0x9c44d0 / 0x9c44d8
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c44a8
        return key == 0x7e8c || key == 0x7ccc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKColossusBaseAttackElement)

    // 0x0046fe48 CKColossusBaseAttackElement_Create: operator new 0x68, KBase7CCC's constructor 0x471160, the vtable.
    CKColossusBaseAttackElement();  // out of line (CKColossusBaseAttackElement.cpp), as CKBomb's
    // 0x0046fcd8 _Destructor (0x46fc90 _DeletingDestructor adds the delete): the vtable, then KBase7CCC's 0x472938.
    ~CKColossusBaseAttackElement() override;

    void Destroy() override { KBase7CCC::Destroy(); }  // vt+0x10 0x0046fc68: 0x4712f8
    // vt+0x24 0x0046fc40: 0x4712f0 (nothing), 1.
    void RecursiveRegistration(int32_t type) override { KBase7CCC::RecursiveRegistration(type); }
    // vt+0x2c 0x0046fbf0: 0x472148, then 1 whatever it answered.
    int32_t Load(IKFile* file, int32_t type) override {
        KBase7CCC::Load(file, type);
        return 1;
    }
    void Vf50() override { KBase7CCC::Vf50(); }  // vt+0x50 0x0046fba0 _StartAttack_maybe: 0x471df8
    void Vf54() override { KBase7CCC::Vf54(); }  // vt+0x54 0x0046fb78: 0x4713e8
    void Vf60(IKTime* frameClock) override { KBase7CCC::Vf60(frameClock); }  // vt+0x60 0x0046fbc8: 0x4706c0
    // vt+0x58 / +0x5c 0x9c44e0 / 0x9c44e8 (empty): KBase7CCC's.
};
static_assert(CKColossusBaseAttackElement::kClassKey == 0x7e8c, "key");
DOTD_ASSERT_SIZE(CKColossusBaseAttackElement, 0x68);
