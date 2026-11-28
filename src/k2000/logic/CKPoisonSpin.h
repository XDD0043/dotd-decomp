// CKPoisonSpin.h - the poison spin attack (key 0xa2cc, vtable 0xb23d38, size 0x260). Original unit:
// CKPoisonSpin.cpp (0x3b8bd8-0x3bc818). Derives from CKAttackMoveElement (its Load and constructor are called
// first). No XXL2 class of this name. Same layout and Load as CKBlackCombo.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKAttackMoveElement.h"

class CKPoisonSpin : public CKAttackMoveElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x28b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c00d0
        return key == 0xa2cc || key == 0xc || key == 0x9a0c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKPoisonSpin)

    CKPoisonSpin() {}  // 0x003b90c0 CKPoisonSpin_Construct: CKAttackMoveElement's constructor, then the vtable only
    ~CKPoisonSpin() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003b9e38 CKPoisonSpin_Load
    // vt+0x30 0x003b9320 CKPoisonSpin_PostLoad: the base's (ResetRuntime), the cloud node (+0x248) put under sector 0's
    // root, the trail (+0x24c) moved under the cloud node (or the dynamic scene root without one).
    int32_t PostLoad(int32_t type) override;

    // The poison spin (Cynder, ability id 10, table A's slot for the poison element) needs the poison element's level
    // 1 (GetElementLevel 0x4f9558: 7000 points; a new game has 0), which only the pause menu's upgrade screen raises.
    uint8_t GetAbilityId() override { return 10; }    // vt+0x50 0x003b8c28
    uint8_t GetFamilyId() override { return 0x19; }   // vt+0x54 0x003b8c30
    // vt+0x58 0x003b8fa8 CKPoisonSpin_Start: the base's, the fizzle hot spot asked for (host vt+0xcc, the result
    // unused), +0x25c, +0x258 and +0x254 cleared.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x60 0x003b8f80 CKPoisonSpin_Update: the base's (inherited).
    // vt+0x64 0x003b8e08 CKPoisonSpin_End: the hero's 1d20 back to 1 (host vt+0x84), the base's, the cloud node put
    // under sector 0's root.
    void End(int32_t forced) override;
    // vt+0x68 0x003b8d48 CKPoisonSpin_ApplyHeroControl: the owner's state test 9 (host vt+0x40) kept, the base's, then
    // action 9 allowed by that answer in the three movement contexts (host vt+0x44).
    void ApplyHeroControl(uint8_t on) override;
    // vt+0x6c 0x003b9018 CKPoisonSpin_ResetRuntime: the base's, the fizzle hot spot 5, +0x258, +0x25c, +0x238, +0x240
    // and +0x254 cleared.
    void ResetRuntime(int32_t type) override;
    // vt+0x70 0x003bb3d8 CKPoisonSpin_SetFxActive, vt+0x78 0x003b96b0 UpdateAttack_maybe and vt+0x7c 0x003baf48
    // UpdateMovement_maybe: CKBlackCombo's instructions at the same offsets (C2.8 port-rest R06; CKPoisonSpin.cpp).
    void SetFxActive(uint8_t on) override;
    void UpdateAttack(float dt) override;
    void UpdateMovement(float dt) override;
    // vt+0x74 0x003b8c38 CKPoisonSpin_SetAttackActive_maybe: the damage parameters (vt+0x88), then the host's attack
    // spheres (vt+0xfc) on or off: the level's radius (+0x1a8) with the damage object (+0x19c), radius 1.0 without one.
    void SetAttackActive(uint8_t on) override;
    // vt+0x84 0x003b8e98 CKPoisonSpin_StopFxAndAttack: the base's, the cloud node hidden (+0x254 cleared), the attack
    // spheres off (radii 1.0), the hero's 1d20 back to 1.
    void StopFxAndAttack() override;
    // vt+0x8c 0x003b8ce8 CKPoisonSpin_IsGroundTrailActive_maybe: above level index 1 the host's airborne state (vt+0x30).
    uint8_t IsGroundTrailActive() override;
    // vt+0x90 0x003b9440 CKPoisonSpin_SteerTowardsTarget_maybe: a null direction is replaced by the host's aim within
    // the level's cone (+0x210 degrees, the aim cone +0x21c; host vt+0x58) with action 1 off; action 9 on; the base's.
    void SteerTowardsTarget(const CVector3* direction) override;

    float m_afHitSphereRadius[3];               // +0x1a8
    int32_t m_ai32MeshHoldAlpha[3];             // +0x1b4 (file: 150 175 254)
    int32_t m_ai32MeshStartAlpha[3];             // +0x1c0 (file: 0; int assumed, as +0x1b4)
    int32_t m_ai32MeshEndAlpha[3];             // +0x1cc (file: 0)
    float m_afMeshSpinDegPerSec[3];               // +0x1d8
    CKAttackMoveVec3 m_avMeshScale[3];    // +0x1e4
    float m_fFadeInTime;                  // +0x208
    float m_fFadeOutTime;                  // +0x20c
    float m_afSteerConeDeg[3];               // +0x210
    IKSerializable* m_pAimCone;        // +0x21c (live: CKAimCamembert)
    IKSerializable* m_pStartExplosion;        // +0x220 (live: CKExplosionFxData)
    IKSerializable* m_pStartExplosionLevel3;        // +0x224 (live: CKExplosionFxData)
    IKSerializable* m_pHitExplosionLevel1;        // +0x228 (live: CKExplosionFxData)
    IKSerializable* m_pHitExplosionLevel2;        // +0x22c (live: CKExplosionFxData)
    IKSerializable* m_pHitExplosionLevel3;        // +0x230 (live: CKExplosionFxData)
    IKSerializable* m_pParticlesDataA;        // +0x234
    IKSerializable* m_pActiveParticlesA;        // +0x238 (not loaded; live 0) runtime: the running particles of +0x234
    IKSerializable* m_pParticlesDataB;        // +0x23c
    IKSerializable* m_pActiveParticlesB;        // +0x240 (not loaded; live 0) runtime: the running particles of +0x23c
    IKSerializable* m_pAnimFxCollection;        // +0x244 (live: CKAnimatedFxCollection)
    IKSerializable* m_pCloudMesh;        // +0x248 (live: CNode)
    IKSerializable* m_pTrailNode;        // +0x24c (live: CTrailNodeFx)
    uint32_t m_ui32LastFadeOutAlpha;               // +0x250 runtime: the mesh's alpha when the fade-out last ran (a word store of the byte)
    uint8_t m_bMeshFadedIn;                // +0x254 runtime: the mesh has faded in (Start / StopFxAndAttack clear it)
    uint8_t m_pad255[3];
    float m_fHitSlowdownTimer;                  // +0x258 runtime: the time left of a hit's slow-down (Start / ResetRuntime: 0)
    uint8_t m_bHitHeld;                // +0x25c runtime (Start / ResetRuntime: 0)
    uint8_t m_pad25d[3];
};
DOTD_ASSERT_SIZE(CKPoisonSpin, 0x260);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_afHitSphereRadius, 0x1a8);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_ai32MeshHoldAlpha, 0x1b4);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_ai32MeshStartAlpha, 0x1c0);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_ai32MeshEndAlpha, 0x1cc);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_afMeshSpinDegPerSec, 0x1d8);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_avMeshScale, 0x1e4);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_fFadeInTime, 0x208);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_fFadeOutTime, 0x20c);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_afSteerConeDeg, 0x210);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_pAimCone, 0x21c);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_pHitExplosionLevel3, 0x230);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_pParticlesDataA, 0x234);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_pParticlesDataB, 0x23c);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_pAnimFxCollection, 0x244);
DOTD_ASSERT_OFFSET(CKPoisonSpin, m_pTrailNode, 0x24c);
