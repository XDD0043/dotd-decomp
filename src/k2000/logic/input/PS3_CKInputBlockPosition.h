// PS3_CKInputBlockPosition.h - the PS3 position block (key 0x678c, vtable 0xb1f800, size 0x2c): the left stick moves a
// normalised screen position at +0x28 per second. Original unit: PS3_CKInputBlockPosition.cpp (0x20ddd8-0x20e458). Base:
// KBase620C. No game file holds one (outputs/remake/kp3-class-usage.json). Names ours. Its other slots are KBase628C's
// (vt+0x5c / +0x60, vt+0x70..+0xc0: the shared stubs 0x9b1828..0x9b18b8, not declared).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase620C.h"

class PS3_CKInputBlockPosition : public KBase620C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x19e)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1bc0
        return key == 0x678c || key == 0x620c || key == 0x628c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(PS3_CKInputBlockPosition)

    PS3_CKInputBlockPosition() {}  // 0x0020e1f0 PS3_CKInputBlockPosition_Construct: KBase620C's, then the vtable
    ~PS3_CKInputBlockPosition() override {}

    // vt+0x2c 0x0020e028 PS3_CKInputBlockPosition_Load: KBase620C's, then (level data only) the speed.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x58 0x0020de28 PS3_CKInputBlockPosition_vf58: see the definition.
    void Update(float dt) override;
    // vt+0x50 0x0020e000 / vt+0x54 0x0020dfd8: KBase620C's OnActivate / OnDeactivate (the slots call them).
    // vt+0x24 0x0020e0f8 / vt+0x10 0x0020e120: KBase620C's (KBase628C's).

    float m_fSpeed;  // +0x28 the position's speed (pixels per second)
};
static_assert(PS3_CKInputBlockPosition::kClassKey == 0x678c, "key");
DOTD_ASSERT_SIZE(PS3_CKInputBlockPosition, 0x2c);
DOTD_ASSERT_OFFSET(PS3_CKInputBlockPosition, m_fSpeed, 0x28);
