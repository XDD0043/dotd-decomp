// CKWindTwister.h - the wind twister attack (key 0x98cc, vtable 0xb249c0, size 0x344). Original unit: CKWindTwister.cpp
// (0x3e6f80-0x3ee198). Derives from CKTransformElement (its Load is called first). No XXL2 class of this name: the
// members keep placeholder names (types from the Ghidra struct, the level data and the attack code).
//
// The twister is three cone nodes (CNode +0x2cc / +0x2d0 / +0x2d4, the third at level 2 only) hung under the user's hot
// spot: each spins about the world up, scales with a random wobble, fades in over its own time, out after the loop, and
// the outer two fade with the user's height above the ground. Button 3 dashes (the impulse component +0x284, its value
// the time scale +0x320 of the effects); at level 2 the dash throws projectiles (+0x2e8 / +0x2ec).
//
// Per node n (0, 1, 2) the level data are in groups (per level unless said): the full alpha, the start alpha, the end
// alpha (words), the spin speed (degrees per second), [n = 1, 2: the height where the fading starts and ends], the
// scale, then three floats: the wobble, the fade-in time, the fade-out time.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"

class CKSound;

class CKWindTwister : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x263)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c09c0
        return key == 0x98cc || key == 0xc || key == 0x954c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKWindTwister)

    CKWindTwister() {}  // 0x003e7740 CKWindTwister_Construct: CKTransformElement's constructor, then the vtable only
    ~CKWindTwister() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003e8260 CKWindTwister_Load
    // vt+0x30 0x003e7850 CKWindTwister_PostLoad: the base's (ResetRuntime), the three level nodes hidden in the sector 0
    // root (SceneNode_SetVisibleInLayer_maybe 0x5832a8), the trail (+0x2d8) moved from its parent (vt+0x78) under the
    // level 0 node (vt+0x70), or under the dynamic scene root without one.
    int32_t PostLoad(int32_t type) override;
    // vt+0x6c 0x003e7480 CKWindTwister_ResetRuntime: the base's, the element's own words; its damage (+0x2f0) and the
    // second damage (+0x280: the ability id, its damage type, continuous, +0x1c = pi) set up.
    void ResetRuntime() override;
    uint8_t GetAbilityId() override { return 0x11; }  // vt+0x50 0x003e6fd0
    uint8_t GetFamilyId() override { return 0x17; }   // vt+0x54 0x003e6fd8
    // vt+0x58 0x003e7da0 CKWindTwister_Start: the sounds cleared, the base's Start; each node (the third at level 2)
    // shown at its start alpha (node 0: +0x16c[level]'s low byte; nodes 1, 2: 0), moved under the user's hot spot
    // +0x13c; the dash (+0x284) cleared and the run-time words reset (the projectile timer +0x334 = +0x2fc).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003e7318 CKWindTwister_End: the hero's +0x1d20 back to 1, the sounds stopped, the base's End, the three
    // nodes hidden in the sector 0 root, the ground mesh pop (+0x28c) let go.
    void End(int32_t forced) override;
    void ApplyHeroControl(uint8_t on) override;  // vt+0x68 0x003e7248: the base's, then action 7
    // vt+0x70 0x003ed2c0 CKWindTwister_SetFxActive: on: the loop particles (+0x2bc), the level's animated collection
    // (+0x2dc / +0x2e0, levels 1 and 2), the loop and dash sounds, the damage (vt+0x88, one Rand_Int), the second
    // damage's +0x10, the two attack spheres, the trail's ribbons on; off: the particles, the dash particles / spark,
    // the collection let go, the end sound played (dictionary 3), the sounds stopped, the trail's ribbons off.
    void SetFxActive(int32_t on) override;
    // vt+0x74 0x003ead10 CKWindTwister_UpdateEffect_maybe: the timers on by dt x the time scale; the dash sound's pitch;
    // the second damage's +0x10; the three nodes (alpha, spin, wobble: one Rand_Int each); the collection; the ground
    // mesh pop while the user is in the air (above level 0); level 2: the dash projectiles (four Rand_Int per shot).
    void UpdateEffect(float dt) override;
    // vt+0x7c 0x003ec8d8 CKWindTwister_UpdateAttack_maybe: above level 0, button 3 kicks the dash (the spark +0x2b8
    // started); the dash's value is the time scale (+0x320, host vt+0x84); near the top speed the dash particles
    // (+0x2c4) and spark (+0x2b0) are taken, below they are let go.
    void UpdateAttack(float dt) override;
    // vt+0x84 0x003e7a48 CKWindTwister_StopFx: the base's, the stop time kept (+0x318), each node's alpha at the stop
    // kept (+0x324[n]) and its fade-out started (+0x330[n]; hidden at once without a fade-out time), the attack spheres
    // off, the hero's +0x1d20 back to 1.
    void StopFx() override;
    // vt+0x8c 0x003e6fe0 CKWindTwister_IsGroundTrailActive_maybe: above level 0, the host's vt+0x30 (the hero: in the
    // air). The base's ground FX table has no type for this ability (3), so the base only runs its timer.
    uint8_t IsGroundTrailActive() override;
    // 0x003e7040 CKWindTwister_GetFxSound_maybe (not virtual): `which` 1: the loop sound (dictionary 2 at level 2, 1 at
    // levels 1 and 2, else 0); 3: the dash sound (5 at level 2, 4 at levels 1 and 2, none at level 0); 4: the end sound
    // (3). A level's own sound only when it is there and has a sample.
    CKSound* GetFxSound(uint32_t which);

    float m_afPrimarySphereRadius[3];                  // +0x154 per level: the first attack sphere's radius (host vt+0xfc)
    int32_t m_ai32Cone0FullAlpha[3];                // +0x160 per level: node 0's full alpha
    int32_t m_ai32Cone0StartAlpha[3];                // +0x16c per level: node 0's start alpha (Start: its low byte)
    int32_t m_ai32Cone0EndAlpha[3];                // +0x178 per level: node 0's end alpha
    float m_afCone0SpinDegPerSec[3];                  // +0x184 per level: node 0's spin (degrees per second)
    float m_fCone0ScaleWobble;                     // +0x190 node 0's scale wobble
    float m_fCone0FadeInTime;                     // +0x194 node 0's fade-in time
    float m_fCone0FadeOutTime;                     // +0x198 node 0's fade-out time (0: hidden at the stop)
    float m_afCone0Scale[3];                  // +0x19c per level: node 0's scale
    int32_t m_ai32Cone1FullAlpha[3];                // +0x1a8 per level: node 1's full alpha
    int32_t m_ai32Cone1StartAlpha[3];                // +0x1b4 per level: node 1's start alpha
    int32_t m_ai32Cone1EndAlpha[3];                // +0x1c0 per level: node 1's end alpha
    float m_afCone1SpinDegPerSec[3];                  // +0x1cc per level: node 1's spin
    float m_fCone1ScaleWobble;                     // +0x1d8 node 1's scale wobble
    float m_fCone1FadeInTime;                     // +0x1dc node 1's fade-in time
    float m_fCone1FadeOutTime;                     // +0x1e0 node 1's fade-out time
    float m_afCone1Scale[3];                  // +0x1e4 per level: node 1's scale
    float m_afCone1FadeHeightStart[3];                  // +0x1f0 per level: node 1's height where it starts to fade
    float m_afCone1FadeHeightEnd[3];                  // +0x1fc per level: node 1's height where it is gone
    int32_t m_ai32Cone2FullAlpha[3];                // +0x208 per level: node 2's full alpha
    int32_t m_ai32Cone2StartAlpha[3];                // +0x214 per level: node 2's start alpha
    int32_t m_ai32Cone2EndAlpha[3];                // +0x220 per level: node 2's end alpha
    float m_afCone2SpinDegPerSec[3];                  // +0x22c per level: node 2's spin
    float m_fCone2ScaleWobble;                     // +0x238 node 2's scale wobble
    float m_fCone2FadeInTime;                     // +0x23c node 2's fade-in time
    float m_fCone2FadeOutTime;                     // +0x240 node 2's fade-out time
    float m_afCone2Scale[3];                  // +0x244 per level: node 2's scale
    float m_afCone2FadeHeightStart[3];                  // +0x250 per level: node 2's height where it starts to fade
    float m_afCone2FadeHeightEnd[3];                  // +0x25c per level: node 2's height where it is gone
    float m_afSecondarySphereRadius[3];                  // +0x268 per level: the second attack sphere's radius
    float m_afSecondaryKnockbackSpeed[3];                  // +0x274 per level: the second damage's +0x10 (times the time scale)
    IKSerializable* m_pSecondaryDamage;           // +0x280 (reference; CKS08ElementDamage): the second sphere's damage
    IKSerializable* m_pDashImpulsion;           // +0x284 (reference; CKImpulsionCpnt): the dash
    IKSerializable* m_pGroundMeshPopFxData;           // +0x288 (reference; CKMeshPopFxData): the ground mesh pop under the user
    IKSerializable* m_pActiveMeshPop;           // +0x28c runtime: the mesh pop effect (ResetRuntime 0)
    float m_unk290;                     // +0x290
    float m_unk294;                     // +0x294
    float m_unk298;                     // +0x298
    float m_unk29c;                     // +0x29c
    float m_unk2a0;                     // +0x2a0
    float m_unk2a4;                     // +0x2a4
    int32_t m_unk2a8;                   // +0x2a8
    uint32_t m_unk2ac;                  // +0x2ac (type unknown)
    IKSerializable* m_pDashSparkFxData;           // +0x2b0 (reference; CKSparkFxData): the dash spark (UpdateAttack)
    IKSerializable* m_pActiveDashSparks;           // +0x2b4 runtime: its effect (ResetRuntime 0)
    IKSerializable* m_pDashKickSparkFxData;           // +0x2b8 (reference; CKSparkFxData): the dash kick's spark (started, not kept)
    IKSerializable* m_pLoopParticlesData;           // +0x2bc (reference; CKParticlesEffectFxData): the loop particles
    IKSerializable* m_pActiveLoopParticles;           // +0x2c0 runtime: their effect (ResetRuntime 0)
    IKSerializable* m_pDashParticlesData;           // +0x2c4 (reference; CKParticlesEffectFxData): the dash particles
    IKSerializable* m_pActiveDashParticles;           // +0x2c8 runtime: their effect (ResetRuntime 0)
    IKSerializable* m_pConeMesh0;           // +0x2cc (reference; CNode): cone node 0
    IKSerializable* m_pConeMesh1;           // +0x2d0 (reference; CNode): cone node 1
    IKSerializable* m_pConeMesh2;           // +0x2d4 (reference; CNode): cone node 2 (level 2)
    IKSerializable* m_pTrailNode;           // +0x2d8 (reference; CTrailNodeFx): the trail (under node 0)
    IKSerializable* m_pAnimFxLevel1;           // +0x2dc (reference; CKAnimatedFxCollection): level 1's collection
    IKSerializable* m_pAnimFxLevel2;           // +0x2e0 (reference; CKAnimatedFxCollection): level 2's collection
    IKSerializable* m_pActiveAnimFx;           // +0x2e4 runtime: the playing collection (ResetRuntime 0)
    IKSerializable* m_pProjectileAccessorA;           // +0x2e8 (reference; CKProjectileAccessor): the dash projectile (draw >= 0)
    IKSerializable* m_pProjectileAccessorB;           // +0x2ec (reference; CKProjectileAccessor): the other one (draw < 0)
    IKSerializable* m_pProjectileDamage;           // +0x2f0 (reference; CKS08ElementDamage): the projectiles' damage
    float m_fProjSpeedMin;                     // +0x2f4 the projectile speed at the dash's low value
    float m_fProjSpeedMax;                     // +0x2f8 the projectile speed at its top value
    float m_fProjInterval;                     // +0x2fc the time between projectiles
    float m_fProjIntervalSpread;                     // +0x300 its spread
    float m_fProjHeightOffset;                     // +0x304 the launch height above the hot spot
    float m_fProjDirY;                     // +0x308 the launch direction's y
    IKSerializable* m_pSoundDico;           // +0x30c (reference; CKSoundDictionaryID)
    float m_fDashSoundTopPitch;                     // +0x310 the dash sound's top pitch
    float m_fEffectTimer;                     // +0x314 runtime: the effect timer (scaled; Start 0)
    float m_fStopFxTime;                     // +0x318 runtime: the timer at the stop (StopFx)
    float m_fUnusedTimer2;                     // +0x31c runtime: a second timer (scaled; Start 0; not read here)
    float m_fDashTimeScale;                     // +0x320 runtime: the time scale, the dash's value (ResetRuntime 1.0f)
    uint32_t m_aui32FadeOutStartAlpha[3];               // +0x324 runtime: each node's alpha at the stop (StopFx; not ResetRuntime)
    uint8_t m_abConeFadeState[3];                // +0x330 runtime: each node at full alpha / fading out (ResetRuntime 0)
    uint8_t m_pad333;
    float m_fNextProjTimer;                     // +0x334 runtime: the time to the next projectile (ResetRuntime 0)
    uint32_t m_unk338;                  // +0x338 runtime (ResetRuntime / Start 0; not read here)
    CKSound* m_pLoopSound;                  // +0x33c runtime: the loop sound (ResetRuntime 0)
    CKSound* m_pDashSound;                  // +0x340 runtime: the dash sound (ResetRuntime 0)
};
DOTD_ASSERT_SIZE(CKWindTwister, 0x344);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afPrimarySphereRadius, 0x154);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone0FullAlpha, 0x160);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone0StartAlpha, 0x16c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone0EndAlpha, 0x178);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone0SpinDegPerSec, 0x184);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone0ScaleWobble, 0x190);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone0FadeInTime, 0x194);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone0FadeOutTime, 0x198);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone0Scale, 0x19c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone1FullAlpha, 0x1a8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone1StartAlpha, 0x1b4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone1EndAlpha, 0x1c0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone1SpinDegPerSec, 0x1cc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone1ScaleWobble, 0x1d8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone1FadeInTime, 0x1dc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone1FadeOutTime, 0x1e0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone1Scale, 0x1e4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone1FadeHeightStart, 0x1f0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone1FadeHeightEnd, 0x1fc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone2FullAlpha, 0x208);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone2StartAlpha, 0x214);
DOTD_ASSERT_OFFSET(CKWindTwister, m_ai32Cone2EndAlpha, 0x220);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone2SpinDegPerSec, 0x22c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone2ScaleWobble, 0x238);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone2FadeInTime, 0x23c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fCone2FadeOutTime, 0x240);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone2Scale, 0x244);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone2FadeHeightStart, 0x250);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afCone2FadeHeightEnd, 0x25c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afSecondarySphereRadius, 0x268);
DOTD_ASSERT_OFFSET(CKWindTwister, m_afSecondaryKnockbackSpeed, 0x274);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pSecondaryDamage, 0x280);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pDashImpulsion, 0x284);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pGroundMeshPopFxData, 0x288);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pActiveMeshPop, 0x28c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pDashSparkFxData, 0x2b0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pActiveDashSparks, 0x2b4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pDashKickSparkFxData, 0x2b8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pLoopParticlesData, 0x2bc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pActiveLoopParticles, 0x2c0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pDashParticlesData, 0x2c4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pActiveDashParticles, 0x2c8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pConeMesh0, 0x2cc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pConeMesh1, 0x2d0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pConeMesh2, 0x2d4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pTrailNode, 0x2d8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pAnimFxLevel1, 0x2dc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pAnimFxLevel2, 0x2e0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pActiveAnimFx, 0x2e4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pProjectileAccessorA, 0x2e8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pProjectileAccessorB, 0x2ec);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pProjectileDamage, 0x2f0);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fProjSpeedMin, 0x2f4);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fProjSpeedMax, 0x2f8);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fProjInterval, 0x2fc);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fProjIntervalSpread, 0x300);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fProjHeightOffset, 0x304);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fProjDirY, 0x308);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pSoundDico, 0x30c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fDashSoundTopPitch, 0x310);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fEffectTimer, 0x314);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fStopFxTime, 0x318);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fUnusedTimer2, 0x31c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fDashTimeScale, 0x320);
DOTD_ASSERT_OFFSET(CKWindTwister, m_aui32FadeOutStartAlpha, 0x324);
DOTD_ASSERT_OFFSET(CKWindTwister, m_abConeFadeState, 0x330);
DOTD_ASSERT_OFFSET(CKWindTwister, m_fNextProjTimer, 0x334);
DOTD_ASSERT_OFFSET(CKWindTwister, m_unk338, 0x338);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pLoopSound, 0x33c);
DOTD_ASSERT_OFFSET(CKWindTwister, m_pDashSound, 0x340);
