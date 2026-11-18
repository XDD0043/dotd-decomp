// CKPurpleCombo.h - the purple combo attack (key 0xa48c, vtable 0xb23e68, size 0x25c). Original unit:
// CKPurpleCombo.cpp (0x3c1f38-0x3c5af0). Derives from CKAttackMoveElement (its Load and constructor are called
// first). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKAttackMoveElement.h"

class CKPurpleCombo : public CKAttackMoveElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x292)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c01b0
        return key == 0xa48c || key == 0xc || key == 0x9a0c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKPurpleCombo)

    CKPurpleCombo() {}  // 0x003c2270 CKPurpleCombo_Construct: CKAttackMoveElement's constructor, then the vtable only
    ~CKPurpleCombo() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003c3048 CKPurpleCombo_Load
    // vt+0x30 0x003c24d0 CKPurpleCombo_PostLoad: the base's (ResetRuntime), then the dash mesh (+0x244) hidden in the
    // sector 0 root (SceneNode_SetVisibleInLayer 1, 0, 0) and the trail (+0x248) moved from its parent (vt+0x78) under it
    // (vt+0x70); 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x003c2220 CKPurpleCombo_RecursiveRegistration: CKAttackMoveElement's, 1.
    void RecursiveRegistration(int32_t type) override { CKAttackMoveElement::RecursiveRegistration(type); }

    // The ability protocol. The purple combo (Spyro, ability id 8, hero slot 8) is never started in LVL010: neither
    // ability slot table (A 0xc40988, B 0xc40978, read only by the ability state) gives slot 8, and no other code reads
    // the hero's +0x1bf0 (Load, Save, RecursiveRegistration only). C2.8 port-all P03 ports its methods all the same.
    uint8_t GetAbilityId() override { return 8; }     // vt+0x50 0x003c1f88
    uint8_t GetFamilyId() override { return 0x19; }   // vt+0x54 0x003c1f90
    // vt+0x58 0x003c2160 CKPurpleCombo_Start: the base's, the host's hot spot +0x186 asked (vt+0xcc, the answer unused),
    // the runtime bytes +0x258 / +0x250 and the time +0x254 cleared.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x60 0x003c2138 CKPurpleCombo_Update: the base's.
    uint8_t Update(float dt) override { return CKAttackMoveElement::Update(dt); }
    // vt+0x64 0x003c20a8 CKPurpleCombo_End: the host's vt+0x84 (1.0), the base's End, the dash mesh hidden in the sector 0
    // root again.
    void End(int32_t forced) override;
    // vt+0x6c 0x003c21d0 CKPurpleCombo_ResetRuntime: the base's, the hot spot 4, the runtime words cleared.
    void ResetRuntime(int32_t type) override;
    // vt+0x70 0x003c48e0 CKPurpleCombo_SetFxActive: on: the attack spheres (vt+0x74), the level's particles on the hot spot
    // (+0x23c), an explosion at the hot spot 1 (+0x220 below level 2, else +0x224), the animated collection above level 1,
    // the dash mesh hung under the hot spot (scaled, shown, alpha +0x1c0[level]) and the trail's ribbons on. Off: the
    // particles released, the collection stopped, the ribbons off.
    void SetFxActive(uint8_t on) override;
    // vt+0x74 0x003c1f98 CKPurpleCombo_SetAttackActive_maybe: the damage parameters (vt+0x88, continuous 0), then the
    // host's attack spheres (vt+0xfc) with the level's radius +0x1a8 and the damage +0x19c.
    void SetAttackActive(uint8_t on) override;
    // vt+0x78 0x003c28c0 CKPurpleCombo_UpdateAttack_maybe: the dash mesh fades in (+0x208), holds and fades out (+0x20c
    // before the duration) and spins about its Z axis (+0x1d8[level] degrees per second, scaled +0x1e4[level]); the
    // animated collection advances while it plays.
    void UpdateAttack(float dt) override;
    // vt+0x7c 0x003c4158 CKPurpleCombo_UpdateMovement_maybe: the hit explosions (host vt+0xf0): +0x22c, or at level 3 (no
    // level reaches it) +0x228 with a delayed re-aim.
    void UpdateMovement(float dt) override;
    // vt+0x84 0x003c26d0 CKPurpleCombo_StopFxAndAttack: the base's, the dash mesh hidden (scene bits 0..2 = 4) with its
    // fade flag cleared, the attack spheres off (vt+0xfc) and the host's vt+0x84 (1.0).
    void StopFxAndAttack() override;
    // vt+0x8c 0x003c2048 CKPurpleCombo_IsGroundTrailActive_maybe: above level 1, the host's vt+0x30.
    uint8_t IsGroundTrailActive() override;
    // vt+0x90 0x003c25a0 CKPurpleCombo_SteerTowardsTarget_maybe: for the null direction, the aim within +0x210[level]
    // degrees of the aim cone +0x21c (host vt+0x58) and the action 1 locked (vt+0x44); then the base's along it.
    void SteerTowardsTarget(const CVector3* direction) override;

    float m_unk1a8[3];               // +0x1a8
    int32_t m_unk1b4[3];             // +0x1b4 (file: 100 150 254)
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
    IKSerializable* m_unk230;        // +0x230
    IKSerializable* m_unk234;        // +0x234
    IKSerializable* m_unk238;        // +0x238
    IKSerializable* m_unk23c;        // +0x23c (not loaded) the pooled particles of SetFxActive
    IKSerializable* m_unk240;        // +0x240 (live: CKAnimatedFxCollection)
    IKSerializable* m_unk244;        // +0x244 (live: CNode)
    IKSerializable* m_unk248;        // +0x248 (live: CTrailNodeFx)
    // Runtime (not loaded).
    uint32_t m_unk24c;               // +0x24c the mesh alpha the fade-out starts from (a word)
    uint8_t m_unk250;                // +0x250 the fade-in done
    uint8_t m_pad251[3];
    float m_unk254;                  // +0x254 the level 3 re-aim delay (a time scaling's +0x0c)
    uint8_t m_unk258;                // +0x258 the level 3 re-aim pending
    uint8_t m_pad259[3];
};
DOTD_ASSERT_SIZE(CKPurpleCombo, 0x25c);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKPurpleCombo, m_unk258, 0x258);
