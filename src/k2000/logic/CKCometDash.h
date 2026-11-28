// CKCometDash.h - the comet dash attack (key 0x9a4c, vtable 0xb23620, size 0x264). Original unit:
// CKCometDash.cpp (0x385a78-0x389ec8). Derives from CKAttackMoveElement (its Load and constructor are called
// first). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKAttackMoveElement.h"

class CKCometDash : public CKAttackMoveElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x269)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfa68
        return key == 0x9a4c || key == 0xc || key == 0x9a0c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKCometDash)

    CKCometDash() {}  // 0x00385ea0 CKCometDash_Construct: CKAttackMoveElement's constructor, then the vtable only
    ~CKCometDash() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00386be0 CKCometDash_Load
    // 0x00385ea0 CKCometDash_Construct / 0x00385ed8 Construct_2: CKAttackMoveElement's constructor, then the vtable.
    // 0x00385ff8 CKCometDash_Destructor / 0x00386028 DestructBody / 0x00385fb0 DeletingDestructor: the vtable, the base
    // destructor (operator delete for the deleting one). vt+0x24 0x00385e50 RecursiveRegistration: the base's (returns 1).
    // vt+0x60 0x00385d60 CKCometDash_Update: the base's only.
    // The comet dash (Spyro, ability id 0, table A's slot for the fire element) needs the fire element's level 1
    // (GetElementLevel 0x4f9558: 7000 points in LVL010's game manager record; a new game has 0), which only the pause
    // menu's upgrade screen raises (C2.8): no LVL010 recording starts it.
    uint8_t GetAbilityId() override { return 0; }     // vt+0x50 0x00385ac8
    uint8_t GetFamilyId() override { return 0x19; }  // vt+0x54 0x00385ad0
    // vt+0x30 0x00386100 CKCometDash_PostLoad: the base's (ResetRuntime), the mesh shown under sector 0, the trail hung
    // under the mesh (or the dynamic scene root).
    int32_t PostLoad(int32_t type) override;
    void Start(CKS08AbilityHostBase* host) override;  // vt+0x58 0x00385d88 CKCometDash_Start
    void End(int32_t forced) override;                // vt+0x64 0x00385be8 CKCometDash_End
    void ResetRuntime(int32_t type) override;         // vt+0x6c 0x00385df8 CKCometDash_ResetRuntime
    void SetFxActive(uint8_t on) override;            // vt+0x70 0x00388a58 CKCometDash_SetFxActive
    void SetAttackActive(uint8_t on) override;        // vt+0x74 0x00385ad8 CKCometDash_SetAttackActive_maybe
    void UpdateAttack(float dt) override;             // vt+0x78 0x00386458 CKCometDash_UpdateAttack_maybe
    void UpdateMovement(float dt) override;           // vt+0x7c 0x003882d0 CKCometDash_UpdateMovement_maybe
    void StopFxAndAttack() override;                  // vt+0x84 0x00385c78 CKCometDash_StopFxAndAttack
    uint8_t IsGroundTrailActive() override;           // vt+0x8c 0x00385b88 CKCometDash_IsGroundTrailActive_maybe
    void SteerTowardsTarget(const CVector3* direction) override;  // vt+0x90 0x00386220 CKCometDash_SteerTowardsTarget_maybe

    float m_afHitSphereRadius[3];               // +0x1a8
    int32_t m_ai32MeshHoldAlpha[3];             // +0x1b4 (file: 100 150 254)
    int32_t m_ai32MeshStartAlpha[3];             // +0x1c0 (file: 0; int assumed, as +0x1b4)
    int32_t m_ai32MeshEndAlpha[3];             // +0x1cc (file: 0)
    float m_afMeshSpinDegPerSec[3];               // +0x1d8
    CKAttackMoveVec3 m_avMeshScale[3];    // +0x1e4
    float m_fFadeInTime;                  // +0x208
    float m_fFadeOutTime;                  // +0x20c
    float m_afSteerConeDeg[3];               // +0x210
    IKSerializable* m_pAimCamembert;        // +0x21c (live: CKAimCamembert)
    IKSerializable* m_pStartExplosionLow;        // +0x220 (live: CKExplosionFxData)
    IKSerializable* m_pStartExplosionMax;        // +0x224 (live: CKExplosionFxData)
    IKSerializable* m_pHitExplosionMax;        // +0x228 (live: CKExplosionFxData)
    IKSerializable* m_pHitExplosionLow;        // +0x22c (live: CKExplosionFxData)
    IKSerializable* m_unk230;        // +0x230
    IKSerializable* m_unk234;        // +0x234
    IKSerializable* m_unk238;        // +0x238
    IKSerializable* m_pActiveParticles;        // +0x23c (not loaded; live 0) runtime: the running particles (SetFxActive)
    IKSerializable* m_pAnimFxCollection;        // +0x240 (live: CKAnimatedFxCollection)
    IKSerializable* m_pSparkFxData;        // +0x244 (live: CKSparkFxData)
    IKSerializable* m_pActiveSparks;        // +0x248 (not loaded; live 0) runtime: the running sparks (SetFxActive)
    IKSerializable* m_pDashMesh;        // +0x24c (live: CNode)
    IKSerializable* m_pTrailNode;        // +0x250 (live: CTrailNodeFx)
    // Runtime (not loaded).
    uint32_t m_ui32FadeOutStartAlpha;               // _maybe: +0x254 the mesh's alpha when the fade-out last ran (a word store of the byte)
    uint8_t m_bMeshFadedIn;                // +0x258 the mesh has faded in
    uint8_t m_pad259[3];
    float m_fHitSlowdownTimer;                  // +0x25c level index 2: the time left of the hit's slow-down
    uint8_t m_bHitHeld;                // +0x260 level index 2: a hit is being held
    uint8_t m_pad261[3];
};
DOTD_ASSERT_SIZE(CKCometDash, 0x264);
DOTD_ASSERT_OFFSET(CKCometDash, m_afHitSphereRadius, 0x1a8);
DOTD_ASSERT_OFFSET(CKCometDash, m_ai32MeshHoldAlpha, 0x1b4);
DOTD_ASSERT_OFFSET(CKCometDash, m_ai32MeshStartAlpha, 0x1c0);
DOTD_ASSERT_OFFSET(CKCometDash, m_ai32MeshEndAlpha, 0x1cc);
DOTD_ASSERT_OFFSET(CKCometDash, m_afMeshSpinDegPerSec, 0x1d8);
DOTD_ASSERT_OFFSET(CKCometDash, m_avMeshScale, 0x1e4);
DOTD_ASSERT_OFFSET(CKCometDash, m_fFadeInTime, 0x208);
DOTD_ASSERT_OFFSET(CKCometDash, m_fFadeOutTime, 0x20c);
DOTD_ASSERT_OFFSET(CKCometDash, m_afSteerConeDeg, 0x210);
DOTD_ASSERT_OFFSET(CKCometDash, m_pAimCamembert, 0x21c);
DOTD_ASSERT_OFFSET(CKCometDash, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKCometDash, m_pAnimFxCollection, 0x240);
DOTD_ASSERT_OFFSET(CKCometDash, m_pSparkFxData, 0x244);
DOTD_ASSERT_OFFSET(CKCometDash, m_pDashMesh, 0x24c);
DOTD_ASSERT_OFFSET(CKCometDash, m_pTrailNode, 0x250);
