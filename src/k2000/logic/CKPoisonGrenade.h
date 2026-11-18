// CKPoisonGrenade.h - the poison grenade element attack (key 0x948c, vtable 0xb23ca8, size 0x30c). Original unit:
// CKPoisonGrenade.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name. Same member layout as CKBlackBall (whose Load reads it in another order).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKPoisonGrenade : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x252)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0048
        return key == 0x948c || key == 0xc || key == 0x934c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKPoisonGrenade)

    CKPoisonGrenade() {}  // 0x003b4aa8 CKPoisonGrenade_Construct: the base constructor, then the vtable only
    ~CKPoisonGrenade() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003b7ce0 CKPoisonGrenade_Load
    void Destroy() override;  // vt+0x10 0x003b4a68 CKPoisonGrenade_Destroy: the matrix (+0x308) destroyed
    // vt+0x30 0x003b49d8 CKPoisonGrenade_PostLoad: the base's (ResetRuntime), then both nodes (+0x2a8, +0x2e8) shown
    // under sector 0's root (SceneNode_SetVisibleInLayer 1, 0, 0).
    int32_t PostLoad(int32_t type) override;

    uint8_t GetAbilityId() override { return 0xb; }  // vt+0x50 0x003b4808
    // vt+0x58 0x003b4990 CKPoisonGrenade_Start: the base's, then (when it took the host) +0x300 cleared.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003b4830 CKPoisonGrenade_End: both nodes shown under sector 0's root, both sounds of +0x2f8 stopped, then
    // the base's.
    void End(int32_t forced) override;
    // vt+0x6c 0x003b6148 CKPoisonGrenade_UpdateCharge: the ball (+0x2a8) grows under the hot spot with the charge
    // (alpha, scale +0x2ac[level] -> +0x2c4[level], the charge sound's pitch 1 -> +0x2fc); once full the burst (+0x2a4),
    // the charged sound, the ball's fade-out and the second node (+0x2e8) under the hot spot.
    void UpdateCharge(float dt) override;
    // vt+0x70 0x003b4920 CKPoisonGrenade_ResetRuntime: the base's, the hot spot 2, the button 1, +0x300 cleared; a new
    // matrix at +0x308 for the level data (type 0).
    void ResetRuntime(int32_t type) override;
    // vt+0x78 0x003b4d08 CKPoisonGrenade_Fire: the level's shots (one, or a fan) launched at a point through the normal
    // (+0x28c) or charged (+0x298) accessor; above level index 0 the charge nodes hidden and the sounds stopped.
    uint8_t Fire() override;
    // vt+0x7c 0x003b4810 CKPoisonGrenade_IsChargeDisabled_maybe: at level index 0.
    uint8_t IsChargeDisabled() override { return m_unk04 == 0 ? 1 : 0; }
    // (vt+0x80 0x009c00a8 CKPoisonGrenade_StartEmitterFx only calls the base's.)

    // Arrays of 3: per level, like the base class's (read element by element).
    float m_unk214[3];             // +0x214 the launch speed (Fire: plus the hero's)
    float m_unk220[3];             // +0x220 the charged launch speed
    float m_unk22c[3];             // +0x22c the aim cone's near distance (Fire)
    float m_unk238[3];             // +0x238 the charged near distance
    float m_unk244[3];             // +0x244 the aim cone's far distance
    float m_unk250[3];             // +0x250 the charged far distance
    int32_t m_unk25c[3];           // +0x25c the shot count (its low byte)
    int32_t m_unk268[3];           // +0x268 the charged shot count
    float m_unk274[3];             // +0x274 the fan's spread in degrees (zero here)
    float m_unk280[3];             // +0x280 the charged spread
    IKSerializable* m_unk28c[3];   // +0x28c CKProjectileAccessor (live; read interleaved with +0x298)
    IKSerializable* m_unk298[3];   // +0x298 CKProjectileAccessor (live)
    IKSerializable* m_unk2a4;      // +0x2a4 CKExplosionFxData (live)
    IKSerializable* m_unk2a8;      // +0x2a8 CNode (live)
    uint32_t m_unk2ac[3];          // +0x2ac one 12-byte read, three swapped words (always 0)
    float m_unk2b8[2][3];          // +0x2b8 two 12-byte reads (vectors, _maybe)
    float m_unk2d0[2][3];          // +0x2d0 two 12-byte reads (vectors, _maybe)
    IKSerializable* m_unk2e8;      // +0x2e8 CNode (live)
    float m_unk2ec;                // +0x2ec
    float m_unk2f0;                // +0x2f0
    uint32_t m_unk2f4;             // +0x2f4 (always 0)
    IKSerializable* m_unk2f8;      // +0x2f8 CKSoundDictionaryID (live)
    float m_unk2fc;                // +0x2fc
    uint8_t m_unk300;              // +0x300 (not read) runtime: cleared by Start, ResetRuntime and Fire
    uint8_t m_pad301[3];
    float m_unk304;                // +0x304 (not read) runtime: the ball's fade-out time left once charged (0.3 s)
    // +0x308 (not read) RwMatrixCreate in ResetRuntime (type 0). DOTD: null until then (the original leaves it).
    struct RwMatrix* m_pUnk308 = nullptr;
};
DOTD_ASSERT_SIZE(CKPoisonGrenade, 0x30c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2d0, 0x2d0);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2e8, 0x2e8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2ec, 0x2ec);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2f4, 0x2f4);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2f8, 0x2f8);
DOTD_ASSERT_OFFSET(CKPoisonGrenade, m_unk2fc, 0x2fc);
