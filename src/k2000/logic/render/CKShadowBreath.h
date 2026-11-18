// CKShadowBreath.h - Cynder's shadow breath (key 0xa90c, vtable 0xb24758, size 0x210). Original unit:
// CKShadowBreath.cpp. Base: CKBreathElement (0x914c), whose Load it calls first (the IsKindOfClass chain also
// names the ability base 0x90cc, outputs/ability-analysis/abilities.md). Not in XXL2; names ours.
//
// The code is CKFireBreath's (the same effects: spark +0x1a0 -> +0x1a4, particles +0x1a8[level] -> +0x1b4, point light
// +0x1b8[level] -> +0x1c4, levels 1 / 2 an animated collection +0x1d4 / +0x1d8 -> +0x1dc, the loop sound now at
// +0x204, the flame's roll at +0x20c) without the hero-class test on the roll, plus at level index 2 a projectile
// (+0x1e8, with the damage +0x1ec) shot along the hot spot's levelled forward every +0x1f8 -/+ +0x1fc seconds.
// The shadow breath is table A's ability for Cynder's element 1 (button A needs that element's level 1, which a later
// level gives): no LVL010 path starts it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBreathElement.h"

class CKSound;

class CKShadowBreath : public CKBreathElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a4)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c07c0
        return key == 0xa90c || key == 0xc || key == 0x914c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKShadowBreath)

    CKShadowBreath() {}  // 0x003d4428 CKShadowBreath_Construct: CKBreathElement, then the vtable
    ~CKShadowBreath() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d5518 CKShadowBreath_Load
    uint8_t GetAbilityId() override { return 13; }  // vt+0x50 0x003d4038
    // vt+0x58 0x003d42d0 CKShadowBreath_Start: the loop sound forgotten (+0x204, not stopped), the first shot's timer
    // (+0x208) the interval's base (+0x1f8), then CKBreathElement's.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003d4258 CKShadowBreath_End: the loop sound stopped and forgotten, then CKBreathElement's.
    void End(int32_t forced) override;
    // vt+0x6c 0x003d4188 CKShadowBreath_ResetRuntime: the loop sound forgotten, CKBreathElement's, no effects, the shot
    // timer 0, the hot spot 2, the projectile damage's ability id (+0x1ec vt+0x68), the button 0, no roll.
    void ResetRuntime(int32_t type) override;
    void SetFxActive(uint8_t on) override;  // vt+0x70 0x003d6b38 CKShadowBreath_SetFxActive
    // (vt+0x74 0x009c0820 CKShadowBreath_StartEmitterFx: CKBreathElement's, a tail call.)
    void UpdateFx(float dt) override;  // vt+0x78 0x003d4850 UpdateShadowBreathEffects
    // vt+0x84 0x003d45e8 CKShadowBreath_GetEmitterPosition: the last particle node's world forward row (its LTM at; `raw`:
    // its modelling right row), else (no node, or the null vector) CKBreathElement's.
    CVector3 GetEmitterPosition(uint8_t raw) override;
    // (vt+0x30 PostLoad 0x3d4308: CKBreathElement's, ResetRuntime.)

    // 0x003d4040 CKShadowBreath_SelectSound_maybe: `which` 0 the start sound (0); 1 the loop sound of the level (3 at
    // level index 2, 2 at 1 or 2, when there and with a sample), else 1; null otherwise.
    CKSound* SelectSound(int32_t which);
    // 0x003d5128 CKShadowBreath_ConfigureSparkNode_maybe: CKFireBreath's (the burst's parameters from the cone).
    void ConfigureSparkNode(int32_t on);

    float m_unk178[10];          // +0x178 the spark's shaping (ten separate reads): +0x178..+0x184 scales,
                                 // +0x188..+0x194 the two ranges, +0x198 the speed, +0x19c the cone's full angle
    IKSerializable* m_unk1a0;    // +0x1a0 reference (CKSparkFxData)
    IKSerializable* m_unk1a4;    // +0x1a4 (not read) the spark effect (a CKSparkNodeFx)
    IKSerializable* m_unk1a8[3]; // +0x1a8 references: the particle effect data of each level (CKParticlesEffectFxData)
    IKSerializable* m_unk1b4;    // +0x1b4 (not read) the particle effect (a CKParticlesEffectNodeFx)
    IKSerializable* m_unk1b8[3]; // +0x1b8 references (CKPointLightFxData) of each level
    IKSerializable* m_unk1c4;    // +0x1c4 (not read) the point light effect
    float m_unk1c8[3];           // +0x1c8 the point light's reach of each level (read last)
    IKSerializable* m_unk1d4;    // +0x1d4 reference (CKAnimatedFxCollection) of level 1 (+0x1d0 + 4 x level)
    IKSerializable* m_unk1d8;    // +0x1d8 reference (CKAnimatedFxCollection) of level 2
    IKSerializable* m_unk1dc;    // +0x1dc (not read) the playing collection
    IKSerializable* m_unk1e0;    // +0x1e0 reference (CKSoundDictionaryID)
    IKSerializable* m_unk1e4;    // +0x1e4 reference (CKAimCamembert)
    IKSerializable* m_unk1e8;    // +0x1e8 reference: the level-2 shot's CKProjectileAccessor
    IKSerializable* m_unk1ec;    // +0x1ec reference: the shot's damage (a CKS08ElementDamage: vt+0x68 SetAbilityId)
    float m_unk1f0;              // +0x1f0 the shot's speed base
    float m_unk1f4;              // +0x1f4 the shot's speed spread (speed = base + spread x (1 - 2u))
    float m_unk1f8;              // +0x1f8 the shot interval's base
    float m_unk1fc;              // +0x1fc the shot interval's spread
    float m_unk200;              // +0x200 the shot's height above the hot spot
    CKSound* m_pLoopSound;       // +0x204 (not read) the loop sound
    float m_fShotTimer;          // +0x208 (not read) the time before the next level-2 shot
    float m_fRoll;               // +0x20c (not read) the flame's roll (radians)
};
static_assert(CKShadowBreath::kClassKey == 0xa90c, "key");
DOTD_ASSERT_SIZE(CKShadowBreath, 0x210);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_pLoopSound, 0x204);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_fRoll, 0x20c);
