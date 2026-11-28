// CKEarthBoulder.h - the earth boulder attack (key 0x95cc, vtable 0xb236c0, size 0x2d0; ability id 5, Spyro's element 2,
// hero slot 4). Original unit: CKEarthBoulder.cpp (0x389ec8-0x3928a0). Derives from CKTransformElement (its Load is called
// first). No XXL2 class of this name: the members keep placeholder names (types from the code that reads them and the
// level data). Spyro rolls inside a boulder (the node +0x228[level], with the extra node +0x234 at level 2): the boulder
// fades in (+0x188 -> +0x184 over +0x190 s), rolls with the hero's velocity, hurts what it touches above a speed (the
// hero's attack sphere 0), can charge (button 3: +0x1a0) and launch the hero forward, and fades out (+0x2a0 -> +0x18c
// over +0x194 s) when the effects stop.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"

class CKSound;

class CKEarthBoulder : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x257)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfaf0
        return key == 0x95cc || key == 0xc || key == 0x954c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKEarthBoulder)

    CKEarthBoulder() {}  // 0x0038a890 CKEarthBoulder_Construct: CKTransformElement's constructor, then the vtable only
    ~CKEarthBoulder() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0038b200 CKEarthBoulder_Load
    // vt+0x30 0x0038a700 CKEarthBoulder_PostLoad: the base's (ResetRuntime), then the three level boulders and the extra
    // node hidden in the sector 0 root (SceneNode_SetVisibleInLayer_maybe 0x5832a8).
    int32_t PostLoad(int32_t type) override;

    uint8_t GetAbilityId() override { return 5; }     // vt+0x50 0x00389f18
    uint8_t GetFamilyId() override { return 0x17; }   // vt+0x54 0x00389f20
    // vt+0x58 0x0038ade8 CKEarthBoulder_Start: the sounds cleared, the base's Start, the level's boulder shown at the
    // start alpha and put at the user's hot spot (one frame of velocity ahead, raised by +0x16c[level]), the extra node
    // too at level 2; the run-time state cleared.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x60 0x0038ab80 CKEarthBoulder_Update: the damage's knock (+0x10) and amount from the user's speed (host vt+0x4c)
    // over +0x108 squared, each capped at 1.5 x the level's value; then the base's Update.
    uint8_t Update(float dt) override;
    // vt+0x64 0x0038a3c8 CKEarthBoulder_End: the sounds stopped, the base's End, the boulders hidden, the effects
    // released.
    void End(int32_t forced) override;
    // vt+0x68 0x0038a270 CKEarthBoulder_ApplyHeroControl: the base's, then action 11 and the host's vt+0x78 (the hero's
    // +0xed4 bit 0 and +0x1b2c = +0x16c[level]).
    void ApplyHeroControl(uint8_t on) override;
    void ResetRuntime() override;                 // vt+0x6c 0x0038a600 CKEarthBoulder_ResetRuntime
    // vt+0x70 0x0038fac8 CKEarthBoulder_SetFxActive: on: the start effects (particles +0x250, explosion +0x204, spark
    // +0x1f4, the level's animated collection +0x244 / +0x248, point light +0x264[level]) and the start / roll sounds;
    // off: the stop effects (particles +0x258, explosion +0x214) when the start particles ran, then everything released.
    void SetFxActive(int32_t on) override;
    // vt+0x74 0x0038e4a8 CKEarthBoulder_UpdateEffect_maybe: the sounds follow the speed, the boulder rolls (rotated
    // about the axis across the velocity and up, placed at the hot spot) and fades in or out, the attack sphere and the
    // ground mesh pop follow the speed, the landing's held actions come back.
    void UpdateEffect(float dt) override;
    // vt+0x78 0x009bfb50 CKEarthBoulder_StartEmitterFx: the base's (a thunk).
    // vt+0x7c 0x00391588 CKEarthBoulder_UpdateAttack_maybe: the rolling mesh pop, the charge (button 3) and the launch
    // (the host's impulse along the user's forward).
    void UpdateAttack(float dt) override;
    // vt+0x80 0x00390e00 CKEarthBoulder_SwitchLoopAnim_maybe: the base's; leaving the ground plays the jump sound; landing
    // fast enough (-vy >= +0x19c) fires the level's landing explosion (+0x208[level], with the damage +0x224) and the
    // landing mesh pop, and holds actions 0, 1 and 3 for +0x198 s.
    void SwitchLoopAnim(uint8_t airborne) override;
    // vt+0x84 0x0038aa48 CKEarthBoulder_StopFx: the base's, then the fade-out starts from the boulder's current alpha
    // (when +0x194 is not 0; else the boulders are hidden at once), the attack sphere off.
    void StopFx() override;
    // vt+0x8c 0x00389f28 CKEarthBoulder_IsGroundTrailActive_maybe: above level 0, the host's vt+0x30.
    uint8_t IsGroundTrailActive() override;

    // 0x00389f88 CKEarthBoulder_PlaySoundByIndex_maybe (not virtual; it plays nothing): the sound of `which` (a jump
    // table of 8): 1 the roll (dictionary 1, 2 or 3 by level), 2 the start (0), 3 the charge (4), 6 the launch (5 or 6,
    // level 1 and up), 7 the jump (7, 8 or 9). A level's own sound only when it is there and has a sample.
    CKSound* GetSoundByIndex(uint32_t which);
    // The roll sound's volume and pitch from the user's speed (SetFxActive and UpdateEffect inline it).
    void UpdateRollSound();
    // The fades' alpha on the boulder and, while shown, the extra node (UpdateEffect inlines the walks).
    void SetBouldersAlpha(uint8_t alpha);

    float m_afBoulderRadius[3];                  // +0x154 the attack sphere's radius (and the roll's), per level
    float m_afBoulderHeightOffset[3];                  // +0x160 the boulder's height above the hot spot, per level
    float m_afExtraHeroMass[3];                  // _maybe: +0x16c the host's vt+0x78 value (the hero's +0x1b2c), per level
    float m_afMinDamageSpeed[3];                  // +0x178 the speed above which the attack sphere is on, per level
    int32_t m_i32RollAlpha;                   // +0x184 the boulder's alpha while rolling (lwz: unsigned)
    uint32_t m_ui32StartAlpha;                  // +0x188 the boulder's alpha at the start (its low byte: Start)
    uint32_t m_ui32EndAlpha;                  // +0x18c the boulder's alpha at the end of the fade-out
    float m_fFadeInTime;                     // +0x190 the fade-in time
    float m_fFadeOutTime;                     // +0x194 the fade-out time (0: hidden at once)
    float m_fLandingActionHoldTime;                     // +0x198 how long a landing holds actions 0, 1 and 3
    float m_fLandingMinFallSpeed;                     // +0x19c the falling speed of a landing
    float m_afFullChargeTime[3];                  // +0x1a0 the full charge time, per level
    float m_afLaunchStrengthMin[3];                  // +0x1ac the launch impulse's strength, no charge
    float m_afLaunchStrengthMax[3];                  // +0x1b8 the launch impulse's strength, full charge
    float m_afLaunchDurationMin[3];                  // +0x1c4 the launch impulse's duration, no charge
    float m_afLaunchDurationMax[3];                  // +0x1d0 the launch impulse's duration, full charge
    float m_afChargeRollSpeedMin[3];                  // +0x1dc the roll speed while charging, no charge
    float m_afChargeRollSpeedMax[3];                  // +0x1e8 the roll speed while charging, full charge
    IKSerializable* m_pStartSparkFxData;           // +0x1f4 (reference; CKSparkFxData) the start spark
    IKSerializable* m_pActiveStartSparks;           // +0x1f8 runtime: its effect (a CKSparkNodeFx)
    IKSerializable* m_pChargeSparkFxData;           // +0x1fc (reference; CKSparkFxData) the charge spark
    IKSerializable* m_pActiveChargeSparks;           // +0x200 runtime: its effect
    IKSerializable* m_pStartExplosion;           // +0x204 (reference; Ghidra: CKExplosionFxData *) the start explosion
    IKSerializable* m_apLandingExplosions[3];        // +0x208 (references; Ghidra: CKExplosionFxData *) the landing, per level
    IKSerializable* m_pStopExplosion;           // +0x214 (reference; Ghidra: CKExplosionFxData *) the stop explosion
    IKSerializable* m_pFullChargeExplosion;           // +0x218 (reference; Ghidra: CKExplosionFxData *) the full charge
    IKSerializable* m_pLaunchExplosion;           // +0x21c (reference; Ghidra: CKExplosionFxData *) the launch (levels 0, 1)
    IKSerializable* m_pLaunchExplosionLevel2;           // +0x220 (reference; Ghidra: CKExplosionFxData *) the launch (level 2)
    IKSerializable* m_pLandingDamage;           // +0x224 (reference; Ghidra: CKS08ElementDamage *) the landing's damage
    IKSerializable* m_apBoulderMeshes[3];        // +0x228 (references; Ghidra: CNode *) the boulder, per level
    IKSerializable* m_pLevel2ExtraNode;           // +0x234 (reference; Ghidra: CNode *) the level 2 extra node (scaled by speed)
    float m_fExtraNodeScaleMin;                     // +0x238 the extra node's scale at speed 0
    float m_fExtraNodeScaleMax;                     // +0x23c its scale at speed +0x240 (and its maximum)
    float m_fExtraNodeMaxScaleSpeed;                     // +0x240
    IKSerializable* m_pAnimFxLevel1;           // +0x244 (reference; CKAnimatedFxCollection) level 1
    IKSerializable* m_pAnimFxLevel2;           // +0x248 (reference; CKAnimatedFxCollection) level 2
    IKSerializable* m_pActiveAnimFx;           // +0x24c runtime: the collection that plays
    IKSerializable* m_pStartParticlesData;           // +0x250 (reference; CKParticlesEffectFxData) the start particles
    IKSerializable* m_pActiveStartParticles;           // +0x254 runtime: their effect
    IKSerializable* m_pStopParticlesData;           // +0x258 (reference; CKParticlesEffectFxData) the stop particles
    IKSerializable* m_pFullChargeParticlesData;           // +0x25c (reference; CKParticlesEffectFxData) the full charge particles
    IKSerializable* m_pActiveFullChargeParticles;           // +0x260 runtime: their effect
    IKSerializable* m_apPointLightFxData[3];        // +0x264 (references; Ghidra: CKPointLightFxData *) per level
    IKSerializable* m_pActivePointLight;           // +0x270 runtime: the light's effect
    IKSerializable* m_pSoundDico;           // +0x274 (reference; Ghidra: CKSoundDictionaryID *)
    float m_fChargeSoundMaxPitch;                     // +0x278 the charge sound's pitch at full charge
    float m_fChargeSoundPitchTimeScale;                     // +0x27c the charge time's scale of the charge sound's pitch
    float m_fRollSoundMinVolume;                     // +0x280 the roll sound's volume at speed 0
    float m_fRollSoundMaxPitch;                     // +0x284 the roll sound's pitch at full speed
    float m_fRollSoundFullVolSpeedRatio;                     // +0x288 the speed ratio of the roll sound's full volume
    IKSerializable* m_pRollPopFxData;           // +0x28c (reference; Ghidra: CKMeshPopFxData *) the airborne ground pop
    IKSerializable* m_pChargePopFxData;           // +0x290 (reference; Ghidra: CKMeshPopFxData *) the charge ground pop
    IKSerializable* m_pLandingPopFxData;           // +0x294 (reference; Ghidra: CKMeshPopFxData *) the landing pop
    // The run-time state (not loaded; ResetRuntime / Start).
    IKSerializable* m_pActiveRollPop;           // +0x298 the airborne pop's effect (a CKMeshPopNodeFx)
    IKSerializable* m_pActiveChargePop;           // +0x29c the charge pop's effect
    uint32_t m_ui32FadeOutStartAlpha;                  // +0x2a0 the fade-out's start alpha
    float m_fFadeTimer;                     // +0x2a4 the fade timer
    float m_fFadeOutStartTime;                     // +0x2a8 the fade timer when the fade-out started
    float m_fChargeTime;                     // +0x2ac the charge time
    uint8_t m_bFadingOut;                   // +0x2b0 fading out
    uint8_t m_bFadedIn;                   // +0x2b1 faded in: the attack runs
    uint8_t m_bCharging;                   // +0x2b2 charging
    uint8_t m_bLaunched;                   // +0x2b3 launched
    float m_fLaunchTimeLeft;                     // +0x2b4 the launch's time left
    float m_fLandingHoldTimeLeft;                     // +0x2b8 the landing's hold time left
    IKSerializable* m_pActiveBoulderMesh;           // +0x2bc the level's boulder (a CNode)
    uint8_t m_bFullChargeFired;                   // +0x2c0 the full charge effects fired
    uint8_t m_pad2c1[3];
    CKSound* m_pRollSound;                  // +0x2c4 the roll sound
    CKSound* m_pChargeSound;                  // +0x2c8 the charge sound
    // +0x2cc set in the air (SwitchLoopAnim), cleared by Start / End / Update (read by the hero:
    // CKHkS08Hero_GetEarthBoulderFlag2CC_maybe 0x32a840).
    uint8_t m_bJustLanded;
    uint8_t m_pad2cd[3];
};
DOTD_ASSERT_SIZE(CKEarthBoulder, 0x2d0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afBoulderRadius, 0x154);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afBoulderHeightOffset, 0x160);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afExtraHeroMass, 0x16c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afMinDamageSpeed, 0x178);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_i32RollAlpha, 0x184);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_ui32StartAlpha, 0x188);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_ui32EndAlpha, 0x18c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fFadeInTime, 0x190);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fLandingMinFallSpeed, 0x19c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afFullChargeTime, 0x1a0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afLaunchStrengthMin, 0x1ac);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afLaunchStrengthMax, 0x1b8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afLaunchDurationMin, 0x1c4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afLaunchDurationMax, 0x1d0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afChargeRollSpeedMin, 0x1dc);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_afChargeRollSpeedMax, 0x1e8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pStartSparkFxData, 0x1f4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveStartSparks, 0x1f8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pChargeSparkFxData, 0x1fc);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveChargeSparks, 0x200);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pStartExplosion, 0x204);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_apLandingExplosions, 0x208);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pStopExplosion, 0x214);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pFullChargeExplosion, 0x218);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pLaunchExplosion, 0x21c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pLaunchExplosionLevel2, 0x220);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pLandingDamage, 0x224);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_apBoulderMeshes, 0x228);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pLevel2ExtraNode, 0x234);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fExtraNodeScaleMin, 0x238);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fExtraNodeMaxScaleSpeed, 0x240);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pAnimFxLevel1, 0x244);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveAnimFx, 0x24c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pStartParticlesData, 0x250);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveStartParticles, 0x254);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pStopParticlesData, 0x258);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pFullChargeParticlesData, 0x25c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveFullChargeParticles, 0x260);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_apPointLightFxData, 0x264);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActivePointLight, 0x270);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pSoundDico, 0x274);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fChargeSoundMaxPitch, 0x278);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fRollSoundMinVolume, 0x280);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fRollSoundFullVolSpeedRatio, 0x288);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pRollPopFxData, 0x28c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pLandingPopFxData, 0x294);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveRollPop, 0x298);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveChargePop, 0x29c);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_ui32FadeOutStartAlpha, 0x2a0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fChargeTime, 0x2ac);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_bFadingOut, 0x2b0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_bLaunched, 0x2b3);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fLaunchTimeLeft, 0x2b4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_fLandingHoldTimeLeft, 0x2b8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pActiveBoulderMesh, 0x2bc);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_bFullChargeFired, 0x2c0);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pRollSound, 0x2c4);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_pChargeSound, 0x2c8);
DOTD_ASSERT_OFFSET(CKEarthBoulder, m_bJustLanded, 0x2cc);
