// CKPxBoxShape.h - a physics box shape (key 0x478c, vtable 0xb203e0, size 0xa4). Original unit: CKPxBoxShape.cpp
// (0x22db30-0x22e1c8). Base: KBase474C (the physics shapes). No game file holds one (outputs/remake/kp3-class-usage.json). Names
// ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase474C.h"

class CKPxBoxShape : public KBase474C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x11e)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x478c || key == 0x474c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxBoxShape)

    CKPxBoxShape() {}  // 0x0022dd50 CKPxBoxShape_Construct: the base, then the vtable
    ~CKPxBoxShape() override {}
    // vt+0x2c 0x0022dc08 CKPxBoxShape_Load: the base's, 1.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022dc80 CKPxBoxShape_Destroy: the base's (the two matrices destroyed).
    // vt+0x24 0x0022dc58 CKPxBoxShape_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    // C2.8 port-last Z7.
    // vt+0x5c 0x009b5868 CKPxBoxShape_ComputeInertiaTensor_maybe (inline): the box's unit-mass tensor, diagonal
    // ((hy^2 + hz^2) / 3, (hx^2 + hz^2) / 3, (hx^2 + hy^2) / 3) of the half extents (+0x1c).
    void ComputeInertiaTensor(CMatrix34* out) override;
    // vt+0x60 0x009b5730 CKPxBoxShape_vf60 (inline): the corner farthest along the world direction (the direction in
    // the box's frame, each half extent signed by its component: not greater than 0 takes the negative one).
    void GetSupportPoint(const CVector3* direction, CVector3* out) override;
    // vt+0x68 0x0022de60 CKPxBoxShape_vf68: the ground contact of the box's lowest corner (KBase474C's without the
    // second support point and the wave term).
    void AddGroundContact() override;
};
DOTD_ASSERT_SIZE(CKPxBoxShape, 0xa4);
