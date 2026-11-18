// CKShadowArms.h - Cynder's shadow arms element attack (key 0x928c, vtable 0xb246c8, size 0x264), ability id 12.
// Original unit: CKShadowArms.cpp (0x3d1c38-0x3d3fe8). Derives from CKProjectileElement (its Load and constructor are
// called first). The code is CKIceGatling's with two hands instead of a side offset: the shots alternate between the
// hot spots +0x261 and +0x262, each with its own accessor per level. No game file holds one
// (outputs/remake/kp3-class-usage.json). No XXL2 class of this name; names ours.
#pragma once
#include <cstdint>

#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKShadowArms : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24a)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0738
        return key == 0x928c || key == 0x934c || key == 0x90cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKShadowArms)

    CKShadowArms() {}  // 0x003d2490 CKShadowArms_Construct: the base constructor, then the vtable only
    ~CKShadowArms() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d3098 CKShadowArms_Load
    // (vt+0x30 0x003d2370 PostLoad, vt+0x24 0x003d2398 RecursiveRegistration and vt+0x10 0x003d23c0 Destroy only call
    // the base's.)

    // The ability protocol (CKProjectileElement.h).
    uint8_t GetAbilityId() override { return 0xc; }  // vt+0x50 0x003d1c88
    // vt+0x58 0x003d22d8 CKShadowArms_Start: the base's; with a host the hero's +0x1d20 (host vt+0x84) the level's
    // +0x214; the first hand (+0x261) as the hot spot, not released.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x60 0x003d21e0 CKShadowArms_Update: +0x260 set once the button is neither down (host vt+0x8c) nor held
    // (vt+0x94) (never cleared here); the animated collection advances while it plays; the base's step.
    uint8_t Update(float dt) override;
    // vt+0x64 0x003d2648 CKShadowArms_End: the hero's +0x1d20 back to 1, the collection stopped while it plays, the base's.
    void End(int32_t forced) override;
    // vt+0x68 0x003d21a8 CKShadowArms_ApplyHeroControl: the base's, then the first hand (+0x261) as the hot spot.
    void ApplyHeroControl(uint8_t on) override;
    // vt+0x70 0x003d2150 CKShadowArms_ResetRuntime: the base's, the hands 7 / 8 (hot spot 7), the button 1, not released.
    void ResetRuntime(int32_t type) override;
    // vt+0x74 0x003d1c98 CKShadowArms_ApplyDamageParams: the base's normal values only (no charged set, no knock, no
    // rand draw, +0x26 left alone), its own damage-type table (0x00a70ac0, the same words).
    void ApplyDamageParams(uint8_t continuous) override;
    // vt+0x78 0x003d27e0 CKShadowArms_Fire: see the definition.
    uint8_t Fire() override;
    uint8_t IsChargeDisabled() override { return 1; }  // vt+0x7c 0x003d1c90
    // (vt+0x80 0x009c0798 CKShadowArms_StartEmitterFx only calls the base's.)

    // Per level (the Load's loop: +0x214[i], +0x220[i], +0x22c[i]).
    float m_unk214[3];             // +0x214 the hero's +0x1d20 while the attack runs (host vt+0x84)
    float m_unk220[3];             // +0x220 the launch point's jitter
    float m_unk22c[3];             // +0x22c the launch speed (plus the hero's)
    IKSerializable* m_unk238[3];   // +0x238 CKProjectileAccessor: the shot from the second hand (+0x262)
    IKSerializable* m_unk244[3];   // +0x244 CKProjectileAccessor: the shot from the first hand (+0x261)
    IKSerializable* m_unk250;      // +0x250 CKAnimatedFxCollection: played on the hero above level index 0
    IKSerializable* m_unk254[3];   // +0x254 CKExplosionFxData: the muzzle explosion per level
    // Runtime (not read).
    uint8_t m_unk260;              // +0x260 released (Update): with the press past the tap window Fire launches nothing
    uint8_t m_unk261;              // +0x261 the first hand's hot spot (ResetRuntime 7)
    uint8_t m_unk262;              // +0x262 the second hand's hot spot (ResetRuntime 8)
    uint8_t m_pad263;
};
DOTD_ASSERT_SIZE(CKShadowArms, 0x264);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKShadowArms, m_unk262, 0x262);
