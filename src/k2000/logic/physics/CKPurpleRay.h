// CKPurpleRay.h - the purple ray breath (key 0x930c, vtable 0xb23f08, size 0x228): Spyro's fury (element 4) breath,
// ability id 9. Original unit: CKPurpleRay.cpp (0x3c5af0-0x3c9a68). Derives from CKBreathElement (its constructor and
// Load run first). No XXL2 class of this name. The same code as CKFearEyes: the bodies are in CKBeamBreath (DOTD).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBeamBreath.h"

class CKPurpleRay : public CKBeamBreath {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24c)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0238
        return key == 0x930c || key == 0xc || key == 0x914c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKPurpleRay)

    CKPurpleRay() {}  // 0x003c6098 CKPurpleRay_Construct: CKBreathElement's constructor, then the vtable only
    ~CKPurpleRay() override {}
    uint8_t GetAbilityId() override { return 9; }  // vt+0x50 0x003c5b40
    // vt+0x10 0x003c5fb0 CKPurpleRay_Destroy: CKBreathElement's, then the mesh matrix (+0x21c) destroyed.
    void Destroy() override;
    // vt+0x6c 0x003c5b48 CKPurpleRay_ResetRuntime: CKBeamBreath::ResetBeamRuntime with the hot spot 2.
    void ResetRuntime(int32_t type) override { ResetBeamRuntime(type, 2); }
    // vt+0x70 0x003c9080 CKPurpleRay_SetFxActive (the impact pulled back by 0.1, TOC +0x3d60).
    void SetFxActive(uint8_t on) override { SetBeamFxActive(on, kImpactPullBack); }
    // vt+0x78 0x003c8ab0 CKPurpleRay_UpdateFx
    void UpdateFx(float dt) override { UpdateBeamFx(dt, kImpactPullBack); }

    static constexpr float kImpactPullBack = 0x1.99999ap-4f;  // TOC +0x3d60 (0x3dcccccd, 0.1)
};
DOTD_ASSERT_SIZE(CKPurpleRay, 0x228);
