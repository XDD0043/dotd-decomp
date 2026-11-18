// CKHkS08Shield.h - an enemy's shield hook (key 0x2f82, vtable 0xb222c8, size 0x24). Original unit:
// CKHkS08Shield.cpp (0x2ac320-0x2acb08). No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"

class CKHkS08Shield : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xbe)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bc9a8
        return key == 0x2f82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08Shield)

    CKHkS08Shield() {}  // 0x002ac5d8 CKHkS08Shield_Create: the IKLife/IKHook defaults only
    ~CKHkS08Shield() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002ac400 CKHkS08Shield_Load
    // vt+0x30 0x002ac3a8 CKHkS08Shield_PostLoad: IKLife's (the level bit), the node hidden (flag 4); 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x68 0x002ac840 CKHkS08Shield_Stop: the node back under the dynamic scene root (engine +0x14) when it is not
    // there (out of its parent, vt+0x78; then the root's AddChild, vt+0x70), as CKHkS08Weapon_Stop.
    void Stop() override;
    // vt+0x10 0x002ac370 Destroy, vt+0x50 0x002ac378 Start, vt+0x70 / +0x78 0x002ac380 / 0x002ac388 Pause / Resume and
    // vt+0x7c 0x002ac390 Update are empty; vt+0x1c 0x002acb00 MessageProc returns 1; vt+0x24 0x002ac508
    // RecursiveRegistration is IKHook's (the inherited defaults).

    virtual void VfC0() {}  // vt+0xc0 0x002ac398 CKHkS08Shield_vfC0 (empty)
    // vt+0xc4 0x002ac6e8 CKHkS08Shield_TakeFromPool_maybe: out of the enemy group's shield pool of its kind (+0x19c[+0x20])
    // into the shield group (+0x1ac) when it is there, woken in the shield group, its node shown.
    virtual void TakeFromPool();
    // vt+0xc8 0x002ac900 CKHkS08Shield_ReturnToPool_maybe: asleep in the shield group, back in its pool when it is in
    // the shield group, its node hidden.
    virtual void ReturnToPool();
    virtual void VfCC() {}  // vt+0xcc 0x002ac3a0 CKHkS08Shield_vfCC (empty)

    uint32_t m_unk20;  // +0x20 read for every serialization type
};
DOTD_ASSERT_SIZE(CKHkS08Shield, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08Shield, m_unk20, 0x20);
