// CKIceGatling.h - the ice gatling element attack (key 0x940c, vtable 0xb23b80, size 0x264). Original unit:
// CKIceGatling.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKIceGatling : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x250)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bff38
        return key == 0x940c || key == 0xc || key == 0x934c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKIceGatling)

    CKIceGatling() {}  // 0x003aa5b8 CKIceGatling_Construct: the base constructor, then the vtable only
    ~CKIceGatling() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003ab230 CKIceGatling_Load
    // (vt+0x30 0x003aa498 CKIceGatling_PostLoad only calls the base's: CKProjectileElement::PostLoad.)

    // The ability protocol (CKProjectileElement.h).
    uint8_t GetAbilityId() override { return 2; }  // vt+0x50 0x003a9ca0
    // vt+0x58 0x003aa3c0 CKIceGatling_Start: the base's; with a host the hero's +0x1d20 (host vt+0x84) the level's
    // +0x214; the shot flags cleared (+0x262, +0x260; +0x261 set: the first shot is held back) and one Rand_Int draw
    // for the side of the first shot (+0x263).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x60 0x003aa1c0 CKIceGatling_Update: +0x260 = released past the tap window; the animated collection advances
    // while it plays; the base's step; while it goes on, a skipped shot clears the press time, and a held button
    // plays the charge animation (phase 1) again.
    uint8_t Update(float dt) override;
    // vt+0x64 0x003aa770 CKIceGatling_End: the hero's +0x1d20 back to 1, the collection stopped while it plays, the base's.
    void End(int32_t forced) override;
    // vt+0x70 0x003aa170 CKIceGatling_ResetRuntime: the base's, the hot spot 2, the button 1, the shot flags cleared.
    void ResetRuntime(int32_t type) override;
    // vt+0x74 0x003a9cb0 CKIceGatling_ApplyDamageParams: the base's normal values only (no charged set, no knock, no
    // rand draw), its own damage-type table (0x00a709f0, the same words).
    void ApplyDamageParams(uint8_t continuous) override;
    // vt+0x78 0x003aa908 CKIceGatling_Fire: one ice shot from alternating sides of the hot spot, jittered (three
    // Rand_Int draws), towards the locked target's aim point or along the aim, through the level's accessor; the
    // level's muzzle explosion. See the definition.
    uint8_t Fire() override;
    uint8_t IsChargeDisabled() override { return 1; }  // vt+0x7c 0x003a9ca8
    // (vt+0x80 0x009bff98 CKIceGatling_StartEmitterFx only calls the base's.)

    // Per level (the Load's loop): the hero's +0x1d20 while firing (host vt+0x84; file 1.0 / 1.25 / 1.75).
    float m_unk214[3];             // +0x214 (read interleaved with +0x220: [i], then +0x220[i])
    float m_unk220[3];             // +0x220 the launch point's jitter (file 0.1 / 0.1 / 0.5)
    float m_unk22c[3];             // +0x22c the side offset of the launch point (file 0.2 / 0.45 / 0.8)
    float m_unk238[3];             // +0x238 the launch speed (plus the hero's; file 7 / 9 / 12)
    IKSerializable* m_unk244[3];   // +0x244 CKProjectileAccessor (live; LVL010: CKProjectileTypeBallisticPFX)
    IKSerializable* m_unk250;      // +0x250 CKAnimatedFxCollection (live): played on the hero above level index 0
    IKSerializable* m_unk254[3];   // +0x254 CKExplosionFxData (live): the muzzle explosion per level
    // Runtime (not read).
    uint8_t m_unk260;              // +0x260 released past the tap window (Update): Fire launches nothing
    uint8_t m_unk261;              // +0x261 the first Fire after Start only sets +0x262
    uint8_t m_unk262;              // +0x262 Fire skipped its shot: Update clears the press time (+0x1fc)
    uint8_t m_unk263;              // +0x263 the side of the next shot (0: -+0x22c, else +0x22c), flipped per shot
};
DOTD_ASSERT_SIZE(CKIceGatling, 0x264);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKIceGatling, m_unk263, 0x263);
