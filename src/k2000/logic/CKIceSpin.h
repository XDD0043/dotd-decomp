// CKIceSpin.h - the ice spin attack (key 0x988c, vtable 0xb23c10, size 0x33c). Original unit: CKIceSpin.cpp
// (0x3abec0-0x3b47b8). Derives from CKTransformElement (its Load is called first). No XXL2 class of this name: the
// members keep placeholder names (types from the code that reads them and the level data).
//
// The effect: three spinning ice nodes hang under the user's hot spot +0x13c: the top node A (+0x2b0, every level), the
// ground rings B (+0x2b4, every level) and C (+0x2b8, level 2). Each fades in over its time while the loop runs, spins
// about the parent's up axis (its speed per level), takes a random scale every frame and fades out once the loop is over;
// the rings sit at the ground under the user and fade with the user's height. Level 2 also throws ice shards (one of
// two projectile accessors) every +0x2f0 (+- +0x2f4) seconds. The dash (button 3, level 1 and up) runs the impulse
// component +0x268, whose value +0x318 is the effect's time scale and the hero's +0x1d20.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"

class CKSound;

class CKIceSpin : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x262)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bffc0
        return key == 0x988c || key == 0xc || key == 0x954c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKIceSpin)

    CKIceSpin() {}  // 0x003ac4f0 CKIceSpin_Construct: CKTransformElement's constructor, then the vtable only
    ~CKIceSpin() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003ad010 CKIceSpin_Load
    // vt+0x30 0x003ac600 CKIceSpin_PostLoad: the base's (ResetRuntime), the three level nodes hidden in the sector 0
    // root (SceneNode_SetVisibleInLayer_maybe 0x5832a8), the trail (+0x2bc) moved from its parent (vt+0x78) under the
    // level 0 node (vt+0x70), or under the dynamic scene root without one.
    int32_t PostLoad(int32_t type) override;
    // vt+0x6c 0x003ac318 CKIceSpin_ResetRuntime: the base's, the element's own words, and its damage (+0x2e4) learns the
    // ability id (vt+0x68).
    void ResetRuntime() override;
    uint8_t GetAbilityId() override { return 3; }    // vt+0x50 0x003abf10
    uint8_t GetFamilyId() override { return 0x17; }  // vt+0x54 0x003abf18
    // vt+0x58 0x003acb50 CKIceSpin_Start: the sounds cleared, the base's Start, the three nodes shown (C at level 2 only)
    // and hung under the user's hot spot +0x13c (A at its start alpha +0x16c[level], B and C at 0), the dash cleared,
    // the timers and fade flags reset, the shard timer +0x32c = +0x2f0.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003ac1b0 CKIceSpin_End: the hero's +0x1d20 back to 1, the sounds stopped, the base's End, the three nodes
    // hidden in the sector 0 root, the mesh pop (+0x270) let go.
    void End(int32_t forced) override;
    void ApplyHeroControl(uint8_t on) override;  // vt+0x68 0x003ac188: the base's only
    // vt+0x70 0x003b3668 CKIceSpin_SetFxActive: on: the loop particles (+0x2a0 on the hot spot), the level's animated
    // collection (level 1 +0x2d0, level 2 +0x2d4), the level's point light (+0x2c0), the loop and dash sounds, the damage
    // (vt+0x88, one Rand_Int), the attack sphere (+0x154[level]), the trail's ribbons on; off: every effect let go, the end
    // sound (dictionary 3) played when the loop sound ran, the sounds stopped, the trail's ribbons off.
    void SetFxActive(int32_t on) override;
    // vt+0x74 0x003b1848 CKIceSpin_UpdateEffect_maybe: the timers (dt x +0x318), the dash sound's pitch, the three nodes'
    // fades and spins (one Rand_Int each for the scale), the collection, the ground mesh pop while IsGroundTrailActive,
    // and at level 2 the shards (three Rand_Int draws per shard).
    void UpdateEffect(float dt) override;
    // vt+0x7c 0x003b0e60 CKIceSpin_UpdateAttack_maybe: above level 0, the dash: button 3 kicks the impulse component and
    // starts the dash sparks (+0x29c); the value (+0x318) goes to the hero (host vt+0x84); near its top the dash
    // particles (+0x2a8) and sparks (+0x294) run, below it they are let go.
    void UpdateAttack(float dt) override;
    // vt+0x84 0x003ac7f8 CKIceSpin_StopFx: the base's, the stop time (+0x310), each node's alpha kept for its fade-out
    // (or the node hidden at once without a fade-out time), the attack sphere off, the hero's +0x1d20 back to 1.
    void StopFx() override;
    // vt+0x8c 0x003abf20 CKIceSpin_IsGroundTrailActive_maybe: above level 0, the host's vt+0x30.
    uint8_t IsGroundTrailActive() override;
    // vt+0x78 0x009c0020 CKIceSpin_StartEmitterFx: an out-of-line copy that calls CKTransformElement's (no override).

    // 0x003abf80 CKIceSpin_GetFxSound_maybe (not virtual): `which` 1: the loop sound (level 2: 2, level 1 and up: 1, a
    // level's own sound only when it is there and has a sample; else 0); 3: the dash sound (level 2: 5, level 1 and up:
    // 4, same test; level 0 none); 4: the end sound (3).
    CKSound* GetFxSound(uint32_t which);

    float m_afHitSphereRadius[3];                  // +0x154 the attack sphere's radius, per level (SetFxActive)
    int32_t m_ai32NodeAFullAlpha[3];                // +0x160 node A's alpha once faded in, per level
    int32_t m_ai32NodeAStartAlpha[3];                // +0x16c node A's start alpha, per level
    int32_t m_ai32NodeAEndAlpha[3];                // +0x178 node A's alpha at the end of its fade-out, per level
    float m_afNodeASpinDegPerSec[3];                  // +0x184 node A's spin (degrees per second of the timer), per level
    float m_fNodeAScaleWobble;                     // +0x190 node A's scale spread (1 +- this, one draw per frame)
    float m_fNodeAFadeInTime;                     // +0x194 node A's fade-in time
    float m_fNodeAFadeOutTime;                     // +0x198 node A's fade-out time (0: hidden at once)
    float m_afNodeAScale[3];                  // +0x19c node A's scale, per level
    int32_t m_ai32RingBFullAlpha[3];                // +0x1a8 ring B's alpha once faded in, per level
    int32_t m_ai32RingBStartAlpha[3];                // +0x1b4 ring B's start alpha, per level
    int32_t m_ai32RingBEndAlpha[3];                // +0x1c0 ring B's alpha at the end of its fade-out, per level
    float m_afRingBSpinDegPerSec[3];                  // +0x1cc ring B's spin, per level
    float m_fRingBScaleWobble;                     // +0x1d8 ring B's scale spread
    float m_fRingBFadeInTime;                     // +0x1dc ring B's fade-in time
    float m_fRingBFadeOutTime;                     // +0x1e0 ring B's fade-out time (0: hidden at once)
    float m_afRingBScale[3];                  // +0x1e4 ring B's scale, per level
    float m_afRingBFadeHeightStart[3];                  // +0x1f0 ring B: the user's height where it starts to fade, per level
    float m_afRingBFadeHeightEnd[3];                  // +0x1fc ring B: the user's height above which it is invisible, per level
    int32_t m_ai32RingCFullAlpha[3];                // +0x208 ring C's alpha once faded in, per level
    int32_t m_ai32RingCStartAlpha[3];                // +0x214 ring C's start alpha, per level
    int32_t m_ai32RingCEndAlpha[3];                // +0x220 ring C's alpha at the end of its fade-out, per level
    float m_afRingCSpinDegPerSec[3];                  // +0x22c ring C's spin, per level
    float m_fRingCScaleWobble;                     // +0x238 ring C's scale spread
    float m_fRingCFadeInTime;                     // +0x23c ring C's fade-in time
    float m_fRingCFadeOutTime;                     // +0x240 ring C's fade-out time (0: hidden at once)
    float m_afRingCScale[3];                  // +0x244 ring C's scale, per level
    float m_afRingCFadeHeightStart[3];                  // +0x250 ring C: the height where it starts to fade, per level
    float m_afRingCFadeHeightEnd[3];                  // +0x25c ring C: the height above which it is invisible, per level
    IKSerializable* m_pDashImpulsion;           // +0x268 (reference; Ghidra: CKImpulsionCpnt *) the dash
    IKSerializable* m_pMeshPopFxData;           // +0x26c (reference; Ghidra: CKMeshPopFxData *) the ground mesh pop
    IKSerializable* m_pActiveMeshPopFx;           // +0x270 runtime: the mesh pop effect (ResetRuntime null)
    float m_unk274;                     // +0x274
    float m_unk278;                     // +0x278
    float m_unk27c;                     // +0x27c
    float m_unk280;                     // +0x280
    float m_unk284;                     // +0x284
    float m_unk288;                     // +0x288
    int32_t m_unk28c;                   // +0x28c
    uint32_t m_unk290;                  // +0x290 (type unknown)
    IKSerializable* m_pDashTopSparkFxData;           // +0x294 (reference; a CKSparkFxData) the dash sparks near the top
    IKSerializable* m_pActiveDashTopSparks;           // +0x298 runtime: their effect (ResetRuntime null)
    IKSerializable* m_pDashKickSparkFxData;           // +0x29c (reference; a CKSparkFxData) the dash kick's sparks (not kept)
    IKSerializable* m_pLoopParticlesData;           // +0x2a0 (reference; a CKParticlesEffectFxData) the loop particles
    IKSerializable* m_pActiveLoopParticles;           // +0x2a4 runtime: their effect (ResetRuntime null)
    IKSerializable* m_pDashParticlesData;           // +0x2a8 (reference; a CKParticlesEffectFxData) the dash particles near the top
    IKSerializable* m_pActiveDashParticles;           // +0x2ac runtime: their effect (ResetRuntime null)
    IKSerializable* m_pNodeA;           // +0x2b0 (reference; Ghidra: CNode *) node A
    IKSerializable* m_pRingB;           // +0x2b4 (reference; Ghidra: CNode *) ring B
    IKSerializable* m_pRingC;           // +0x2b8 (reference; Ghidra: CNode *) ring C
    IKSerializable* m_pTrailNode;           // +0x2bc (reference; Ghidra: CTrailNodeFx *)
    IKSerializable* m_apPointLightFxData[3];        // +0x2c0 (references; Ghidra: CKPointLightFxData *) per level
    IKSerializable* m_pActivePointLight;           // +0x2cc runtime: the light effect (ResetRuntime null)
    IKSerializable* m_pAnimFxLevel1;           // +0x2d0 (reference) the level 1 animated collection
    IKSerializable* m_pAnimFxLevel2;           // +0x2d4 (reference) the level 2 animated collection
    IKSerializable* m_pActiveAnimFx;           // +0x2d8 runtime: the collection that plays (ResetRuntime null)
    IKSerializable* m_pShardAccessorA;           // +0x2dc (reference; Ghidra: CKProjectileAccessor *) the first shard
    IKSerializable* m_pShardAccessorB;           // +0x2e0 (reference; Ghidra: CKProjectileAccessor *) the second shard
    IKSerializable* m_pShardDamage;           // +0x2e4 (reference; Ghidra: CKS08ElementDamage *) the shards' damage
    float m_fShardSpeedMin;                     // +0x2e8 the shards' speed at the dash's bottom
    float m_fShardSpeedMax;                     // +0x2ec the shards' speed at the dash's top
    float m_fShardInterval;                     // +0x2f0 the time between two shards
    float m_fShardIntervalSpread;                     // +0x2f4 its spread (+-, one draw)
    float m_fShardHeightOffset;                     // +0x2f8 the shards' height above the hot spot
    float m_fShardDirY;                     // +0x2fc the shards' direction y
    float m_fShardConeDeg;                     // +0x300 the shards' cone (degrees, one draw)
    IKSerializable* m_pSoundDico;           // +0x304 (reference; Ghidra: CKSoundDictionaryID *)
    float m_fDashSoundTopPitch;                     // +0x308 the dash sound's pitch at the dash's top
    float m_fEffectTimer;                     // +0x30c runtime: the effect timer (dt x +0x318; Start 0)
    float m_fStopFxTime;                     // +0x310 runtime: the timer at StopFx (the fade-outs)
    float m_fUnusedTimer2;                     // +0x314 runtime: a second timer (dt x +0x318; Start 0; nothing reads it)
    float m_fDashTimeScale;                     // +0x318 runtime: the dash's value, the time scale (ResetRuntime / Start 1.0f)
    uint32_t m_unk31c;                  // +0x31c runtime: node A's alpha at StopFx (a word)
    uint32_t m_unk320;                  // +0x320 runtime: ring B's alpha at StopFx
    uint32_t m_unk324;                  // +0x324 runtime: ring C's alpha at StopFx
    uint8_t m_abNodeFadeState[3];                // +0x328 runtime: A / B / C faded in, or fading out after StopFx
    uint8_t m_pad32b;
    float m_fNextShardTimer;                     // +0x32c runtime: the time to the next shard (Start +0x2f0)
    uint32_t m_unk330;                  // +0x330 runtime (ResetRuntime / Start 0; nothing reads it)
    CKSound* m_pLoopSound;                  // +0x334 runtime: the loop sound (ResetRuntime null)
    CKSound* m_pDashSound;                  // +0x338 runtime: the dash sound (ResetRuntime null)
};
DOTD_ASSERT_SIZE(CKIceSpin, 0x33c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afHitSphereRadius, 0x154);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32NodeAFullAlpha, 0x160);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32NodeAStartAlpha, 0x16c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32NodeAEndAlpha, 0x178);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afNodeASpinDegPerSec, 0x184);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fNodeAScaleWobble, 0x190);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fNodeAFadeInTime, 0x194);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fNodeAFadeOutTime, 0x198);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afNodeAScale, 0x19c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32RingBFullAlpha, 0x1a8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32RingBStartAlpha, 0x1b4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32RingBEndAlpha, 0x1c0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingBSpinDegPerSec, 0x1cc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fRingBScaleWobble, 0x1d8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fRingBFadeInTime, 0x1dc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fRingBFadeOutTime, 0x1e0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingBScale, 0x1e4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingBFadeHeightStart, 0x1f0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingBFadeHeightEnd, 0x1fc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32RingCFullAlpha, 0x208);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32RingCStartAlpha, 0x214);
DOTD_ASSERT_OFFSET(CKIceSpin, m_ai32RingCEndAlpha, 0x220);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingCSpinDegPerSec, 0x22c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fRingCScaleWobble, 0x238);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fRingCFadeInTime, 0x23c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fRingCFadeOutTime, 0x240);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingCScale, 0x244);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingCFadeHeightStart, 0x250);
DOTD_ASSERT_OFFSET(CKIceSpin, m_afRingCFadeHeightEnd, 0x25c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pDashImpulsion, 0x268);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pMeshPopFxData, 0x26c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pActiveMeshPopFx, 0x270);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pDashTopSparkFxData, 0x294);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pActiveDashTopSparks, 0x298);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pDashKickSparkFxData, 0x29c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pLoopParticlesData, 0x2a0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pActiveLoopParticles, 0x2a4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pDashParticlesData, 0x2a8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pActiveDashParticles, 0x2ac);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pNodeA, 0x2b0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pRingB, 0x2b4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pRingC, 0x2b8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pTrailNode, 0x2bc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_apPointLightFxData, 0x2c0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pActivePointLight, 0x2cc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pAnimFxLevel1, 0x2d0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pAnimFxLevel2, 0x2d4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pActiveAnimFx, 0x2d8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pShardAccessorA, 0x2dc);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pShardAccessorB, 0x2e0);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pShardDamage, 0x2e4);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fShardSpeedMin, 0x2e8);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fShardConeDeg, 0x300);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pSoundDico, 0x304);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fDashSoundTopPitch, 0x308);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fEffectTimer, 0x30c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fStopFxTime, 0x310);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fUnusedTimer2, 0x314);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fDashTimeScale, 0x318);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk31c, 0x31c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk320, 0x320);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk324, 0x324);
DOTD_ASSERT_OFFSET(CKIceSpin, m_abNodeFadeState, 0x328);
DOTD_ASSERT_OFFSET(CKIceSpin, m_fNextShardTimer, 0x32c);
DOTD_ASSERT_OFFSET(CKIceSpin, m_unk330, 0x330);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pLoopSound, 0x334);
DOTD_ASSERT_OFFSET(CKIceSpin, m_pDashSound, 0x338);
