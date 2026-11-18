// CKPxKinematic.h - a kinematic physics body (key 0x580c, vtable 0xb1fe90, size 0x12c). Original unit:
// CKPxKinematic.cpp (0x21ae38-0x21cb38). Base: CKPxBody. It adds the axis locks (+0x12b, read by its Load). No XXL2
// class; names ours. No game file holds one: C2.8 port-final F03 (see CKPxBody.h for what is not ported).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKPxBody.h"

class CKPxKinematic : public CKPxBody {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x160)  // vt+0x14 / +0x18 0x9b3840 / 0x9b3848
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b3808
        return key == 0x580c || key == 0x498c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxKinematic)

    // 0x0021b7e0 CKPxKinematic_Construct (= 0x21b818 _Construct_2; 0x21b9a0 Create): the body's constructor
    // (0x218638), then the vtable.
    CKPxKinematic();
    // 0x0021b780 _Destructor (= 0x21b7b0 _BaseDestructor; 0x21b738 _DeletingDestructor adds the delete): the vtable, then
    // the body's 0x218b80.
    ~CKPxKinematic() override;

    void Destroy() override { CKPxBody::Destroy(); }  // vt+0x10 0x0021b710
    // vt+0x24 0x0021b6e8: the body's 0x2183d0, 1.
    void RecursiveRegistration(int32_t type) override { CKPxBody::RecursiveRegistration(type); }
    // vt+0x2c 0x0021b628 CKPxKinematic_Load: the body's, then (level data) the lock byte +0x12b; 1.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x6c 0x009b3b10 CKPxKinematic_CreateRuntimeState_maybe (inline): a kinematic description (0x6c bytes).
    void CreateRuntimeState() override;

    // 0x0021ae88 CKPxKinematic_ApplyTranslationAxisConstraint_maybe: the lock bits 0-2 (+0x12b & 7) on the vectors
    // +0xd8, +0x6c and +0xa4: 1 / 2 / 4 take out their part along the world matrix's right / up / at axis, 6 / 5 / 3 keep
    // only the part along right / up / at, 7 clears them, 0 nothing.
    void ApplyTranslationAxisConstraint();
    // 0x0021b1c0 CKPxKinematic_ApplyRotationAxisConstraint_maybe: the same with the bits 3-5 (& 0x38: 8, 0x10, 0x20, ...)
    // on the vectors +0xe4, +0x94 and +0xb8.
    void ApplyRotationAxisConstraint();

    // C2.8 port-last Z7.
    void ExportState(CKPxBodyDesc* desc) override;          // vt+0x50 0x009b3850 (inline)
    void InitFromDesc(const CKPxBodyDesc* desc) override;   // vt+0x54 0x009b3c60 (inline)
    // vt+0x64 0x009b3ee0 CKPxKinematic_Step_maybe (inline)
    void Step(float dt, float dt2, float frequency, float halfFrequencySq, uint8_t lastStep) override;
    // 0x0021b9f8 CKPxKinematic_Integrate_maybe
    void Integrate(float dt, float dt2, float frequency, uint8_t lastStep);
    // 0x0021c568 CKPxKinematic_ComputeDriveVelocities_maybe
    void ComputeDriveVelocities(float dt, float dt2, float frequency, uint8_t lastStep);
};
static_assert(CKPxKinematic::kClassKey == 0x580c, "key");
DOTD_ASSERT_SIZE(CKPxKinematic, 0x12c);
