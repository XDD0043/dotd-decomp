// CKFearScream.h - the fear scream element attack (key 0x944c, vtable 0xb239b8, size 0x24c). Original unit:
// CKFearScream.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "k2000/logic/CKProjectileElement.h"

class CKSound;

class CKFearScream : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x251)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfdb0
        return key == 0x944c || key == 0xc || key == 0x934c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKFearScream)

    CKFearScream() {}  // 0x003a12c0 CKFearScream_Construct: the base constructor, then the vtable only
    ~CKFearScream() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003a1cb8 CKFearScream_Load
    // vt+0x30 0x003a1220 CKFearScream_PostLoad: the base's (ResetRuntime), then the charge node (+0x230) hidden under
    // sector 0's root (SceneNode_SetVisibleInLayer 1, 0, 0).
    int32_t PostLoad(int32_t type) override;

    // The ability protocol (CKProjectileElement.h).
    uint8_t GetAbilityId() override { return 0xf; }  // vt+0x50 0x003a0f50
    // vt+0x58 0x003a11d0 CKFearScream_Start: the loop sound dropped (+0x248), the base's; with a host the burst flag
    // (+0x244) cleared.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003a0fa8 CKFearScream_End: the loop sound stopped, the charge node hidden under sector 0's root, the
    // base's.
    void End(int32_t forced) override;
    // vt+0x6c 0x003a1628 CKFearScream_UpdateCharge: once the charge passes the level's full time, the burst (+0x22c,
    // once); the charge node (+0x230) under the hot spot 0 on the first charging frame, then its alpha with the charge.
    void UpdateCharge(float dt) override;
    // vt+0x70 0x003a1180 CKFearScream_ResetRuntime: the base's, the hot spot 2, the button 1, the sound and the burst
    // flag cleared.
    void ResetRuntime(int32_t type) override;
    // vt+0x78 0x003a2750 CKFearScream_Fire: the level's normal (+0x214) or charged (+0x220) scream explosion at the
    // launch point, turned towards the target or the aim, carrying the damage (vt+0x74: one rand draw); the start and
    // the level's loop sounds on the user.
    uint8_t Fire() override;
    // vt+0x7c 0x003a0f58 CKFearScream_IsChargeDisabled_maybe: the host's flag 10 (vt+0x40: the hero host answers
    // whether this is the fear scream, id 0xf).
    uint8_t IsChargeDisabled() override { return m_pHost->Vf40(this, 10); }
    // (vt+0x80 0x009bfe10 CKFearScream_StartEmitterFx only calls the base's.)

    // 0x003a1038 CKFearScream_GetFxSound_maybe: sound 0 of the dictionary (`which` 0, the start), or (1) the loop of
    // the level: index 1 by default, 2 at level index 1 and 2, 3 at level index 2, each only when it has a sample.
    CKSound* GetFxSound(int32_t which);

    IKSerializable* m_unk214[7];   // +0x214 CKExplosionFxData (live): [0..2] the normal scream per level, [3..5] the
                                   // charged one, [6] the full-charge burst
    IKSerializable* m_unk230;      // +0x230 CNode (live): the charge node
    float m_unk234[3];             // +0x234 one 12-byte read, three swapped words (live: 0, then floats): the charge
                                   // node's offset under the hot spot
    IKSerializable* m_unk240;      // +0x240 CKSoundDictionaryID (live)
    uint8_t m_unk244;              // +0x244 (not read) runtime: the full-charge burst went off
    uint8_t m_pad245[3];
    CKSound* m_pLoopSound;         // +0x248 (not read) runtime: the loop sound playing (Fire)
};
DOTD_ASSERT_SIZE(CKFearScream, 0x24c);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKFearScream, m_pLoopSound, 0x248);
