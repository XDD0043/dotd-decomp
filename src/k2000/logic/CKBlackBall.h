// CKBlackBall.h - the black ball element attack (key 0x94cc, vtable 0xb23458, size 0x30c). Original unit:
// CKBlackBall.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name. Same member layout as CKPoisonGrenade (whose Load reads it in another order).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKBlackBall : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x253)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bf900
        return key == 0x94cc || key == 0xc || key == 0x934c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKBlackBall)

    // 0x00379ba0 CKBlackBall_Construct / 0x00379d20 CKBlackBall_Construct_2: the base constructor, then the vtable only.
    CKBlackBall() {}
    // 0x00379cc0 CKBlackBall_Destructor / 0x00379cf0 DestructBody / 0x00379c78 DeletingDestructor: the vtable, the base
    // destructor (CKProjectileElement_BaseDestructor 0x3bf2f8), operator delete for the deleting one.
    ~CKBlackBall() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0037c8a8 CKBlackBall_Load
    // vt+0x24 0x00379b38 CKBlackBall_RecursiveRegistration: the base's only (CKProjectileElement 0x3bf2c8 returns 1).
    void Destroy() override;  // vt+0x10 0x00379b60 CKBlackBall_Destroy: the matrix (+0x308) destroyed
    // vt+0x30 0x00379ad0 CKBlackBall_PostLoad: the base's (ResetRuntime), then both nodes (+0x2a8, +0x2e8) shown under
    // sector 0's root (SceneNode_SetVisibleInLayer 1, 0, 0).
    int32_t PostLoad(int32_t type) override;

    uint8_t GetAbilityId() override { return 0x14; }  // vt+0x50 0x00379908
    // vt+0x58 0x00379a88 CKBlackBall_Start: the base's, then (when it took the host) +0x300 cleared.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x00379930 CKBlackBall_End: both nodes shown under sector 0's root, both sounds of +0x2f8 stopped, then the
    // base's.
    void End(int32_t forced) override;
    // vt+0x6c 0x00379f08 CKBlackBall_UpdateCharge: instruction for instruction CKPoisonGrenade_UpdateCharge (the same
    // layout and TOC values): the ball grows under the hot spot with the charge, once full the burst, the charged sound,
    // the fade-out and the second node.
    void UpdateCharge(float dt) override;
    // vt+0x70 0x00379a20 CKBlackBall_ResetRuntime: the base's, +0x300 cleared, the hot spot 2, the button 0; a new matrix
    // at +0x308 for the level data (type 0).
    void ResetRuntime(int32_t type) override;
    // vt+0x78 0x0037ab10 CKBlackBall_Fire: the level's shots (one, or a fan) launched along a direction through the normal
    // (+0x28c) or charged (+0x298) accessor; above level index 0 the charge nodes hidden and the sounds stopped.
    uint8_t Fire() override;
    // vt+0x7c 0x00379910 CKBlackBall_IsChargeDisabled_maybe: at level index 0.
    uint8_t IsChargeDisabled() override { return m_unk04 == 0 ? 1 : 0; }

    // Arrays of 3: per level, like the base class's (the Load's 3-iteration loop).
    float m_unk214[3];             // +0x214
    float m_unk220[3];             // +0x220
    float m_unk22c[3];             // +0x22c
    float m_unk238[3];             // +0x238
    float m_unk244[3];             // +0x244
    float m_unk250[3];             // +0x250
    int32_t m_unk25c[3];           // +0x25c
    int32_t m_unk268[3];           // +0x268
    float m_unk274[3];             // +0x274
    float m_unk280[3];             // +0x280
    IKSerializable* m_unk28c[3];   // +0x28c CKProjectileAccessor (live; read interleaved with +0x298)
    IKSerializable* m_unk298[3];   // +0x298 CKProjectileAccessor (live)
    IKSerializable* m_unk2a4;      // +0x2a4 CKExplosionFxData (live)
    IKSerializable* m_unk2a8;      // +0x2a8 CNode (live)
    uint32_t m_unk2ac[3];          // +0x2ac one 12-byte read, three swapped words (always 0)
    float m_unk2b8[2][3];          // +0x2b8 two 12-byte reads (vectors_maybe)
    float m_unk2d0[2][3];          // +0x2d0 two 12-byte reads (vectors_maybe)
    IKSerializable* m_unk2e8;      // +0x2e8 CNode (live)
    float m_unk2ec;                // +0x2ec
    float m_unk2f0;                // +0x2f0
    uint32_t m_unk2f4;             // +0x2f4 (always 0)
    IKSerializable* m_unk2f8;      // +0x2f8 CKSoundDictionaryID (live)
    float m_unk2fc;                // +0x2fc
    uint8_t m_unk300;              // +0x300 (not read) runtime: charged once (cleared by Start, ResetRuntime and Fire)
    uint8_t m_pad301[3];
    float m_unk304;                // +0x304 (not read) runtime: the ball's fade-out time left once charged (0.3 s)
    // +0x308 (not read) RwMatrixCreate in ResetRuntime (type 0). DOTD: null until then (the original leaves it).
    struct RwMatrix* m_pUnk308 = nullptr;
};
DOTD_ASSERT_SIZE(CKBlackBall, 0x30c);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2d0, 0x2d0);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2e8, 0x2e8);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2ec, 0x2ec);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2f4, 0x2f4);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2f8, 0x2f8);
DOTD_ASSERT_OFFSET(CKBlackBall, m_unk2fc, 0x2fc);
