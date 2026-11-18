// CKFearEyes.h - the fear breath (key 0x92cc, vtable 0xb23920, size 0x228): Cynder's fury (element 4) breath, ability
// id 16. Original unit: CKFearEyes.cpp (0x39cf88-0x3a0f00). Derives from CKBreathElement (its constructor and Load run
// first). No XXL2 class of this name. CKPurpleRay (physics/) is the same code: the bodies are in CKBeamBreath (DOTD).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBeamBreath.h"

class CKFearEyes : public CKBeamBreath {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfd28
        return key == 0x92cc || key == 0xc || key == 0x914c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKFearEyes)

    CKFearEyes() {}  // 0x0039d530 CKFearEyes_Construct: CKBreathElement's constructor, then the vtable only
    ~CKFearEyes() override {}
    // vt+0x10 0x0039d448 CKFearEyes_Destroy: CKBreathElement's (empty), then the mesh matrix (+0x21c) destroyed.
    void Destroy() override;
    uint8_t GetAbilityId() override { return 16; }  // vt+0x50 0x0039cfd8
    // vt+0x6c 0x0039cfe0 CKFearEyes_ResetRuntime: CKBeamBreath::ResetBeamRuntime with the hot spot 6.
    void ResetRuntime(int32_t type) override { ResetBeamRuntime(type, 6); }
    // vt+0x70 0x003a0518 CKFearEyes_SetFxActive (the impact pulled back by 0.2, TOC +0x373c).
    void SetFxActive(uint8_t on) override { SetBeamFxActive(on, kImpactPullBack); }
    // vt+0x78 0x0039ff48 CKFearEyes_UpdateFx
    void UpdateFx(float dt) override { UpdateBeamFx(dt, kImpactPullBack); }

    static constexpr float kImpactPullBack = 0x1.99999ap-3f;  // TOC +0x373c (0x3e4ccccd, 0.2)
};
DOTD_ASSERT_SIZE(CKFearEyes, 0x228);
