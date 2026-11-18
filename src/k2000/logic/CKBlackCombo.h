// CKBlackCombo.h - the black combo attack (key 0xa44c, vtable 0xb234e8, size 0x260). Original unit:
// CKBlackCombo.cpp (0x37d2e0-0x380ed0). Derives from CKAttackMoveElement (its Load and constructor are called
// first). No XXL2 class of this name. Same layout and Load as CKPoisonSpin.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKAttackMoveElement.h"

class CKBlackCombo : public CKAttackMoveElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x291)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bf988
        return key == 0xa44c || key == 0xc || key == 0x9a0c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKBlackCombo)

    CKBlackCombo() {}  // 0x0037d7c8 CKBlackCombo_Construct: CKAttackMoveElement's constructor, then the vtable only
    ~CKBlackCombo() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0037e4f0 CKBlackCombo_Load
    // 0x0037d7c8 CKBlackCombo_Construct / 0x0037d800 Construct_2: CKAttackMoveElement's constructor, then the vtable.
    // 0x0037d950 CKBlackCombo_DestructBody / 0x0037d8d8 DeletingDestructor: the vtable, the base destructor (operator
    // delete for the deleting one). vt+0x24 0x0037d778 RecursiveRegistration: the base's (returns 1). vt+0x60 0x0037d688
    // CKBlackCombo_Update: the base's only.
    // The black combo (Cynder, ability id 19, hero slot 8) is never started in DotD: neither ability slot table (A
    // 0xc40988, B 0xc40978, read only by the ability state) gives slot 8, and no other code reads the hero's +0x1bf0
    // (Load, Save, RecursiveRegistration only). Ported all the same (the poison spin's code at its own offsets).
    uint8_t GetAbilityId() override { return 0x13; }  // vt+0x50 0x0037d330
    uint8_t GetFamilyId() override { return 0x19; }   // vt+0x54 0x0037d338
    // vt+0x30 0x0037da28 CKBlackCombo_PostLoad: the base's (ResetRuntime); with a mesh, it is shown under sector 0 and the
    // trail hung under it.
    int32_t PostLoad(int32_t type) override;
    void Start(CKS08AbilityHostBase* host) override;  // vt+0x58 0x0037d6b0 CKBlackCombo_Start
    void End(int32_t forced) override;                // vt+0x64 0x0037d510 CKBlackCombo_End
    void ApplyHeroControl(uint8_t on) override;       // vt+0x68 0x0037d450 CKBlackCombo_ApplyHeroControl
    void ResetRuntime(int32_t type) override;         // vt+0x6c 0x0037d720 CKBlackCombo_ResetRuntime
    void SetFxActive(uint8_t on) override;            // vt+0x70 0x0037fa90 CKBlackCombo_SetFxActive
    void SetAttackActive(uint8_t on) override;        // vt+0x74 0x0037d340 CKBlackCombo_SetAttackActive_maybe
    void UpdateAttack(float dt) override;             // vt+0x78 0x0037dd68 CKBlackCombo_UpdateAttack_maybe
    void UpdateMovement(float dt) override;           // vt+0x7c 0x0037f600 CKBlackCombo_UpdateMovement_maybe
    void StopFxAndAttack() override;                  // vt+0x84 0x0037d5a0 CKBlackCombo_StopFxAndAttack
    uint8_t IsGroundTrailActive() override;           // vt+0x8c 0x0037d3f0 CKBlackCombo_IsGroundTrailActive_maybe
    void SteerTowardsTarget(const CVector3* direction) override;  // vt+0x90 0x0037daf8 CKBlackCombo_SteerTowardsTarget_maybe

    float m_unk1a8[3];               // +0x1a8
    int32_t m_unk1b4[3];             // +0x1b4 (file: 254 254 254)
    int32_t m_unk1c0[3];             // +0x1c0 (file: 0; int assumed, as +0x1b4)
    int32_t m_unk1cc[3];             // +0x1cc (file: 0)
    float m_unk1d8[3];               // +0x1d8
    CKAttackMoveVec3 m_unk1e4[3];    // +0x1e4
    float m_unk208;                  // +0x208
    float m_unk20c;                  // +0x20c
    float m_unk210[3];               // +0x210
    IKSerializable* m_unk21c;        // +0x21c (live: CKAimCamembert)
    IKSerializable* m_unk220;        // +0x220 (live: CKExplosionFxData)
    IKSerializable* m_unk224;        // +0x224 (live: CKExplosionFxData)
    IKSerializable* m_unk228;        // +0x228 (live: CKExplosionFxData)
    IKSerializable* m_unk22c;        // +0x22c (live: CKExplosionFxData)
    IKSerializable* m_unk230;        // +0x230 (live: CKExplosionFxData)
    IKSerializable* m_unk234;        // +0x234
    IKSerializable* m_unk238;        // +0x238 (not loaded; live 0) runtime: the running particles of +0x234
    IKSerializable* m_unk23c;        // +0x23c
    IKSerializable* m_unk240;        // +0x240 (not loaded; live 0) runtime: the running particles of +0x23c
    IKSerializable* m_unk244;        // +0x244 (live: CKAnimatedFxCollection)
    IKSerializable* m_unk248;        // +0x248 (live: CNode)
    IKSerializable* m_unk24c;        // +0x24c (live: CTrailNodeFx)
    // Runtime (not loaded).
    uint32_t m_unk250;               // +0x250 the mesh's alpha when the fade-out last ran (a word store of the byte)
    uint8_t m_unk254;                // +0x254 the mesh has faded in
    uint8_t m_pad255[3];
    float m_unk258;                  // +0x258 the time left of a hit's slow-down
    uint8_t m_unk25c;                // +0x25c a hit is being held
    uint8_t m_pad25d[3];
};
DOTD_ASSERT_SIZE(CKBlackCombo, 0x260);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKBlackCombo, m_unk24c, 0x24c);
