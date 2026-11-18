// CKBlenderController.h - an animation controller blending two controllers (key 0xd4d, vtable 0xb16608,
// size 0x5c). Original unit: CKBlenderController.cpp (0x7b2d8-...). No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/KBase98D.h"

class CKBlenderController : public KBase98D {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x35)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9997e8
        return key == 0xd4d || key == 0x98d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKBlenderController)

    CKBlenderController() {}  // 0x0007b7d8 CKBlenderController_Create: KBase98D's constructor only
    ~CKBlenderController() override {}
    // vt+0x10 0x0007b6f0 CKBlenderController_Destroy: the base's references, both controllers and the weight cleared.
    void Destroy() override;

    // vt+0x2c 0x0007b518 CKBlenderController_Load: the base's, then the two controllers and a float.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x24 0x0007b658 CKBlenderController_RecursiveRegistration: KBase98D's (0x7cff8), then both controllers' own
    // with the same type (not null-checked).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x0007b4f0 CKBlenderController_PostLoad: KBase98D::PostLoadBase. 1.
    int32_t PostLoad(int32_t type) override;

    // vt+0x50 0x0007b830 CKBlenderController_vf50: KBase98D_vf50 into its own evaluated mask, copied to `mask`.
    uint8_t Vf50(KBase98D* chain, uint32_t* mask) override;
    // vt+0x54 0x0007c4e0 CKBlenderController_GetBoundingSphere_maybe: inactive: null; a snapshot: the stored sphere; else
    // the children's spheres (the ones Evaluate would use) merged into +0x14 (one, or the sphere around both).
    float* GetBoundingSphere() override;
    // vt+0x60 0x0007b3b0 CKBlenderController_Reset_maybe: KBase98D_Reset_maybe and both children's Reset.
    void Reset() override;
    // vt+0x64 0x0007b968 CKBlenderController_Evaluate_maybe: a snapshot gives its stored mask; else each active child is
    // evaluated unless the weight +0x58 shuts it out (below 0.99 for the first, above 0.01 for the second, or the other
    // one flagged 8), the weight is (1 - w) w1 + w w2 (or the one child's), and the pose: the one child's interpolator
    // when only one was evaluated or the effective blend is outside [0.01, 0.99] (the other child's stamp cleared), else
    // the blend (RpHAnimKeyFrameBlend) of both into its own interpolator, per node of the union of both masks when they
    // differ from the node's mask. Returns the interpolator holding the pose (null with `skip`).
    RtAnimInterpolator* Evaluate(uint32_t* mask, float* weight, uint8_t skip) override;
    // vt+0x68 0x0007c110 CKBlenderController_UpdateActiveState_maybe: the children's states (updated first), active (4)
    // when a child that Evaluate would use is active or a snapshot keeps it; 0x10 when one of them needs evaluating.
    uint8_t UpdateActiveState() override;
    // vt+0x6c 0x0007b430 CKBlenderController_vf6C: this controller, else the first child, else the second child that was
    // evaluated in this render frame.
    KBase98D* GetIfEvaluatedThisFrame() override;

    IKSerializable* m_apControllers[2];  // +0x50 the blended controllers (CKAnmKeyFrameController in LVL010)
    float m_unk58;                       // +0x58 the blend weight: 0 the first controller, 1 the second
};
static_assert(CKBlenderController::kClassKey == 0xd4d, "key");
DOTD_ASSERT_SIZE(CKBlenderController, 0x5c);
DOTD_ASSERT_OFFSET(CKBlenderController, m_apControllers, 0x50);
DOTD_ASSERT_OFFSET(CKBlenderController, m_unk58, 0x58);
