// CKEarthMissile.h - the earth missile element attack (key 0x938c, vtable 0xb23758, size 0x27c). Original
// unit: CKEarthMissile.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKEarthMissile : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24e)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfb78
        return key == 0x938c || key == 0xc || key == 0x934c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKEarthMissile)

    CKEarthMissile() {}  // 0x00392ac8 CKEarthMissile_Construct: the base constructor, then the vtable only
    ~CKEarthMissile() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00394778 CKEarthMissile_Load
    // vt+0x30 0x00392a10 CKEarthMissile_PostLoad: the base's (ResetRuntime), then both charge nodes (+0x24c, +0x25c)
    // put under sector 0's root (SceneNode_SetVisibleInLayer 1, 0, 0).
    int32_t PostLoad(int32_t type) override;

    uint8_t GetAbilityId() override { return 4; }  // vt+0x50 0x003928f0
    // vt+0x58 0x003929c8 CKEarthMissile_Start: the base's, then (when it took the host) +0x274 cleared.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x60 0x00392960 CKEarthMissile_Update: the effect collection (+0x244) advanced while it plays, then the base's.
    uint8_t Update(float dt) override;
    // vt+0x64 0x00392d28 CKEarthMissile_End: the effect collection stopped, both sounds of +0x26c stopped, both charge
    // nodes put under sector 0's root, then the base's.
    void End(int32_t forced) override;
    // vt+0x6c 0x00393538 CKEarthMissile_UpdateCharge: the rock (+0x24c) appears under the hot spot with the charge
    // (alpha, the charge sound's pitch 1 -> +0x270); once full the burst (+0x248), the charged sound, the rock's
    // fade-out and the second node (+0x25c) under the hot spot.
    void UpdateCharge(float dt) override;
    // vt+0x70 0x00392918 CKEarthMissile_ResetRuntime: the base's, +0x274 cleared, the hot spot 2, the button 0.
    void ResetRuntime(int32_t type) override;
    // vt+0x78 0x00392f48 CKEarthMissile_Fire: one missile along the aim (to the locked target, else the host's aim
    // direction) through the normal (+0x22c) or charged (+0x238) accessor; above level index 0 the effect collection
    // plays, the charge nodes hide and the sounds stop.
    uint8_t Fire() override;
    // vt+0x7c 0x003928f8 CKEarthMissile_IsChargeDisabled_maybe: at level index 0 (abs(level) - 1 < 0).
    uint8_t IsChargeDisabled() override { return m_ui32LevelIndex == 0 ? 1 : 0; }
    // (vt+0x80 0x009bfbd8 CKEarthMissile_StartEmitterFx only calls the base's.)

    float m_afLaunchSpeedNormal[3];             // +0x214 (read interleaved with +0x220)
    float m_afLaunchSpeedCharged[3];             // +0x220
    IKSerializable* m_apNormalProjectiles[3];   // +0x22c CKProjectileAccessor (live; read interleaved with +0x238)
    IKSerializable* m_apChargedProjectiles[3];   // +0x238 CKProjectileAccessor (live)
    IKSerializable* m_pAnimFxCollection;      // +0x244 CKAnimatedFxCollection (live)
    IKSerializable* m_pFullChargeBurst;      // +0x248 CKExplosionFxData (live)
    IKSerializable* m_pChargeRockNode;      // +0x24c CNode (live)
    uint32_t m_unk250;             // +0x250 (always 0)
    float m_fChargeRockOffsetY;                // +0x254
    uint32_t m_unk258;             // +0x258 (always 0)
    IKSerializable* m_pChargedNode;      // +0x25c CNode (live)
    float m_fChargedNodeOffsetX;                // +0x260
    float m_fChargedNodeOffsetY;                // +0x264
    uint32_t m_unk268;             // +0x268 (always 0)
    IKSerializable* m_pSoundDico;      // +0x26c CKSoundDictionaryID (live)
    float m_fChargeSoundMaxPitch;                // +0x270
    uint8_t m_bChargedBurstFired;              // +0x274 (not read) runtime: charged (UpdateCharge's burst done)
    uint8_t m_pad275[3];
    float m_fRockFadeOutLeft;                // +0x278 (not read) runtime: the rock's fade-out time left (0.3 at the burst)
};
DOTD_ASSERT_SIZE(CKEarthMissile, 0x27c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_afLaunchSpeedNormal, 0x214);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_afLaunchSpeedCharged, 0x220);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_apNormalProjectiles, 0x22c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_apChargedProjectiles, 0x238);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_pAnimFxCollection, 0x244);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_pFullChargeBurst, 0x248);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_pChargeRockNode, 0x24c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_fChargeRockOffsetY, 0x254);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_pChargedNode, 0x25c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_fChargedNodeOffsetX, 0x260);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_fChargedNodeOffsetY, 0x264);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_pSoundDico, 0x26c);
DOTD_ASSERT_OFFSET(CKEarthMissile, m_fChargeSoundMaxPitch, 0x270);
