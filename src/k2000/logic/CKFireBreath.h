// CKFireBreath.h - the fire breath (key 0x924c, vtable 0xb23a48, size 0x1f0). Original unit: CKFireBreath.cpp
// (0x3a3240-0x3a5e60). Derives from CKBreathElement (its constructor and Load run first). No XXL2 class of this name.
//
// Its effects (SetFxActive / UpdateFx): a spark burst (+0x1a0 -> +0x1a4) shaped by the cone (ConfigureSparkNode), the
// level's particle effect (+0x1a8[level] -> +0x1b4) along the aim, the level's point light (+0x1b8[level] -> +0x1c4)
// at the flame's reach (stopped by walls), levels 1 / 2 an animated FX collection (+0x1d4 / +0x1d8 -> +0x1dc), the
// start sound and the loop sound (+0x1e8). The flame's roll towards the target (+0x1ec) follows the hot spot 2.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBreathElement.h"

class CKSound;

class CKFireBreath : public CKBreathElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x249)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfe38
        return key == 0x924c || key == 0xc || key == 0x914c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKFireBreath)

    CKFireBreath() {}  // 0x003a3408 CKFireBreath_Construct: CKBreathElement's constructor, then the vtable only
    ~CKFireBreath() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003a4288 CKFireBreath_Load

    uint8_t GetAbilityId() override { return 1; }  // vt+0x50 0x003a3090
    // vt+0x58 0x003a32b8 CKFireBreath_Start: the loop sound forgotten (+0x1e8, not stopped), then CKBreathElement's.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003a3240 CKFireBreath_End: the loop sound stopped and forgotten, then CKBreathElement's.
    void End(int32_t forced) override;
    // vt+0x6c 0x003a31e0 ResetFireBreathRuntimeEffects: CKBreathElement's, the hot spot 2, no effects, no roll.
    void ResetRuntime(int32_t type) override;
    void SetFxActive(uint8_t on) override;  // vt+0x70 0x003a5498 SetFireBreathEffectsActive
    // vt+0x74 0x009bfe98 CKFireBreath_StartEmitterFx: CKBreathElement's (a tail call).
    void UpdateFx(float dt) override;  // vt+0x78 0x003a3720 UpdateFireBreathEffects
    // vt+0x84 0x003a35c8 CKFireBreath_GetEmitterPosition: the last particle node's world forward row (its LTM at; `raw`:
    // its modelling right row), else (no node, or the null vector) CKBreathElement's.
    CVector3 GetEmitterPosition(uint8_t raw) override;

    // 0x003a3098 CKFireBreath_GetSound_maybe: `which` 0 the start sound (0); 1 the loop sound of the level (3 at level
    // index 2, 2 at 1 or 2, when there and with a sample), else 1; null otherwise.
    CKSound* GetSound(int32_t which);
    // 0x003a3e98 CKFireBreath_ConfigureSparkNode_maybe: (on, with the spark) the burst's parameters from the cone: the
    // level's angle over level 0's (scaled up by +0x178..+0x184 above 1), the half angle (+0x19c / 2, at most 180)
    // giving its sine (1 above pi / 2) and cosine.
    void ConfigureSparkNode(int32_t on);

    float m_unk178[10];          // +0x178 the spark's shaping (live: floats): +0x178..+0x184 scales, +0x188..+0x194 the
                                 // two ranges, +0x198 the speed, +0x19c the cone's full angle (degrees)
    IKSerializable* m_pSparkFxData;    // +0x1a0 reference (live: CKSparkFxData)
    IKSerializable* m_pSparkNodeFx;    // +0x1a4 (not loaded) the spark effect (a CKSparkNodeFx)
    IKSerializable* m_apParticlesFxData[3]; // +0x1a8 references: the particle effect data of each level (CKParticlesEffectFxData)
    IKSerializable* m_pParticlesNodeFx;    // +0x1b4 (not loaded) the particle effect (a CKParticlesEffectNodeFx)
    IKSerializable* m_apPointLightFxData[3]; // +0x1b8 references (live: CKPointLightFxData) of each level
    IKSerializable* m_pPointLightNodeFx;    // +0x1c4 (not loaded) the point light effect
    float m_afPointLightReach[3];           // +0x1c8 the point light's reach of each level (+0x1d0 is the last one)
    IKSerializable* m_pAnimFxLevel1;    // +0x1d4 reference (live: CKAnimatedFxCollection) of level 1 (+0x1d0 + 4 x level)
    IKSerializable* m_pAnimFxLevel2;    // +0x1d8 reference (live: CKAnimatedFxCollection) of level 2
    IKSerializable* m_pActiveAnimFx;    // +0x1dc (not loaded) the playing collection
    IKSerializable* m_pSoundDico;    // +0x1e0 reference (live: CKSoundDictionaryID)
    IKSerializable* m_pAimCamembert;    // +0x1e4 reference (live: CKAimCamembert)
    CKSound* m_pLoopSound;           // +0x1e8 (not loaded) the loop sound
    float m_fFlameRollRad;              // +0x1ec (not loaded) the flame's roll (radians)
};
DOTD_ASSERT_SIZE(CKFireBreath, 0x1f0);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pSparkFxData, 0x1a0);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pSparkNodeFx, 0x1a4);
DOTD_ASSERT_OFFSET(CKFireBreath, m_apParticlesFxData, 0x1a8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pParticlesNodeFx, 0x1b4);
DOTD_ASSERT_OFFSET(CKFireBreath, m_apPointLightFxData, 0x1b8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pPointLightNodeFx, 0x1c4);
DOTD_ASSERT_OFFSET(CKFireBreath, m_afPointLightReach, 0x1c8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pAnimFxLevel1, 0x1d4);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pAnimFxLevel2, 0x1d8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pActiveAnimFx, 0x1dc);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pSoundDico, 0x1e0);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pAimCamembert, 0x1e4);
DOTD_ASSERT_OFFSET(CKFireBreath, m_pLoopSound, 0x1e8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_fFlameRollRad, 0x1ec);
