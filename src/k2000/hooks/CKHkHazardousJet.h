// CKHkHazardousJet.h - a hazardous jet (key 0x2f42, vtable 0xb284d0, size 0xcc). Original unit:
// CKHkHazardousJet.cpp. No XXL2 class. LVL090 / LVL100 hold some; C2.1 ported the Load, C2.8 port-rest R03 the rest.
// Field names are placeholders; the purposes are _maybe from the code.
//
// While enabled (+0x0c bit 3) a jet starts when a controlled hero comes within +0x3c of its box (the box +0x20, its
// centre the node's position less the box's height): the start effect (+0x24) and quake (+0x70), sounds 0 / 2, the
// start signals (+0x94), the warm-up time (+0xac = +0x44). The warm-up runs down (a hero within +0x40 cuts it to 0.2 s,
// with the boost effect +0x28, the spark +0x30, the quake +0x74, the pad rumble and the looping sound 1); at its end the
// jet is at full strength (bit 5): the box switched on and shrinking back over +0x48 seconds, the lightning bolt (+0x34)
// from the node up the box, projectiles every +0x7c..+0x80 seconds (+0x78) and the heroes that touch the box hurt every
// +0x60 seconds for +0x5c seconds (the contact list +0xc8, the explosion +0x2c). With no hero in range the jet stops
// (sound 3, the stop signals +0x9c, its effects after +0x90 seconds). Bit 6: started / stopped by messages
// (SetJetActive, vt+0xd4) instead of the heroes.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKFx;

class CKHkHazardousJet : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xbd)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4de8
        return key == 0x2f42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkHazardousJet)

    // A hero touching the jet (0x14 bytes, FreeListPool 0x00ceaa60 in the original: free list 0x00ceaa64; here new /
    // delete). New entries go to the front.
    struct JetContact {
        IKSerializable* m_pHero;  // +0x00 the hero (a 0x3642)
        float m_fTime;            // +0x04 the time since the first touch
        float m_fWindowStart;     // +0x08 the time of the last new touch: the entry lives until +0x5c after it
        uint8_t m_bTouched;       // +0x0c touched this frame (Update clears it)
        JetContact* m_pNext;      // +0x10
    };

    // 0x004a01c0 CKHkHazardousJet_Construct (inlined in 0x004a0740 CKHkHazardousJet_Create): +0xc8 = 0. The runtime
    // members past the Load's are what the fresh heap leaves (zero).
    CKHkHazardousJet();
    // 0x004a03a0 CKHkHazardousJet_Destructor (= 0x4a0318 _DeletingDestructor, the dead 0x4a02a0): the contact list
    // given back, then the actor base's.
    ~CKHkHazardousJet() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004a07a0 CKHkHazardousJet_Load
    // vt+0x30 0x004a00e0 CKHkHazardousJet_PostLoad: the actor base's (IKLife_PostLoad); for the level type the trigger
    // starter +0x94's PostLoad (TriggerEventList_PostLoad_maybe 0x236330: nothing); 1.
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);  // 0x003f6e70
        if (type == K_LEVEL_PLATEFORMS) m_tsUnk94.PostLoad(0);
        return 1;
    }
    // vt+0x40 0x0049fc00 CKHkHazardousJet_GetInfo: the actor base's answer (KStub_Return1 0x3f7140) merged.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override {
        const int32_t base = CKHkActorBase::GetInfo(info, request);
        if (base == 2) return 2;
        return base == 0 ? 0 : 1;
    }

    // ---- C2.8 port-rest R03 ----
    // vt+0x38 0x0049fa40 CKHkHazardousJet_SetDefaultState: the actor base's (empty), then enabled (bit 3) = +0xa4.
    void SetDefaultState(int32_t flag) override;
    // vt+0x1c 0x0049faa0 CKHkHazardousJet_MessageProc: the actor messages, then the hero's hazard query 0xc32 (the
    // damage +0x58; with a volume the knock values +0x4c..+0x54 and the volume's position, else no knock).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x50 0x004a0070 CKHkHazardousJet_Start: the actor base's (empty), no effects, the projectile delay +0x80, then
    // Restart (vt+0x54).
    void Start() override;
    // vt+0x54 0x004a3f40 CKHkHazardousJet_Restart: bit 6 cleared; unless bit 2 the timers reset, the contacts given back,
    // bits 4 / 5 cleared and the effects stopped.
    void Restart() override;
    void Update(IKTime* clock) override;  // vt+0x7c 0x004a2f40 CKHkHazardousJet_Update
    // vt+0xa0 0x004a04c0 CKHkHazardousJet_OnActivate: the actor base's, the box under the node at its full size, the
    // timers and contacts reset.
    void VfA0() override;
    // vt+0xa4 0x004a3e68 CKHkHazardousJet_OnDeactivate: the actor base's, the box off and under the engine's dynamic
    // scene root, the effects stopped.
    void VfA4() override;
    // vt+0xc8 0x004a0418 CKHkHazardousJet_vfC8 (the state preset): enabled = +0xa4 for 0, +0xa5 for 1.
    void ApplyStatePreset(int32_t state) override;
    // vt+0xcc 0x004a2eb8 CKHkHazardousJet_vfCC: disabling stops the effects and switches the box off; bit 3 = `enabled`.
    void SetEnabled(int32_t enabled) override;
    // vt+0xd4 0x004a24a8 CKHkHazardousJet_SetJetActive_maybe (the actor messages 0x90c..0x90f): bit 6 = `on`; a
    // running jet stops (off), a stopped one starts (on): mode 0 as the heroes start it, mode 1 at full boost.
    void VfD4(int32_t on, int32_t mode) override;

    // 0x0049fdb0 CKHkHazardousJet_LaunchProjectile_maybe: a projectile (+0x78) from half the node's up axis above it,
    // up and spread by two draws (+0x8c along the at and right axes), at a drawn speed between +0x84 and +0x88.
    void LaunchProjectile();
    // 0x004a1288 CKHkHazardousJet_UpdateLightningTargets_maybe: the bolt (+0xc4, acquired from +0x34) from the node up to
    // twice the box's height along the box's up axis, switched on.
    void UpdateLightningTargets();
    // 0x004a1618 CKHkHazardousJet_ProcessHeroContacts_maybe: every hero touching the box: a new one joins the contact
    // list and an explosion (+0x2c) goes off at the contact; one already listed and not touched this frame restarts its
    // window.
    void ProcessHeroContacts();
    // 0x004a2350 CKHkHazardousJet_StopJetFx_maybe: the two particle effects (+0xb8 / +0xbc) stopped and released, the
    // bolt (+0xc4) and the spark (+0xc0) released.
    void StopJetFx();

    IKSerializable* m_pUnk20;                  // +0x20 reference: the box (an IKBoundingBox)
    IKSerializable* m_pUnk24;                  // +0x24 reference: the start effect (a CKParticlesEffectFxData)
    IKSerializable* m_pUnk28;                  // +0x28 reference: the boost effect (a CKParticlesEffectFxData)
    IKSerializable* m_pUnk2C;                  // +0x2c reference: the contact explosion (its node a CKExplosionNodeFx)
    IKSerializable* m_pUnk30;                  // +0x30 reference: the spark (a CKSparkFxData)
    IKSerializable* m_pUnk34;                  // +0x34 reference: the bolt (a CKLightningBoltFxData)
    IKSerializable* m_pUnk38;                  // +0x38 reference: the sounds (a CKSoundDictionaryID: 0..3)
    float m_fUnk3C;                            // +0x3c the start range
    float m_fUnk40;                            // +0x40 the boost range
    float m_fUnk44;                            // +0x44 the warm-up time
    float m_fUnk48;                            // +0x48 the box's shrink time at full strength
    float m_afUnk4C[3];                        // +0x4c..+0x57 the hazard query's knock values
    uint8_t m_unk58;                           // +0x58 the hazard query's damage
    uint8_t m_pad59[3];
    float m_fUnk5C;                            // +0x5c a contact's lifetime after its last new touch
    float m_fUnk60;                            // +0x60 a contact's hurt period
    float m_afUnk64[3];                        // +0x64 the box's half sizes at full size
    IKSerializable* m_pUnk70;                  // +0x70 reference: the start quake (a CKQuakeCameraLauncher)
    IKSerializable* m_pUnk74;                  // +0x74 reference: the boost quake (a CKQuakeCameraLauncher)
    IKSerializable* m_pUnk78;                  // +0x78 reference: the projectiles (a CKProjectileAccessor)
    float m_fUnk7C;                            // +0x7c the projectile delay's minimum
    float m_fUnk80;                            // +0x80 the projectile delay's maximum (also the first delay)
    float m_fUnk84;                            // +0x84 the projectile speed's minimum
    float m_fUnk88;                            // +0x88 the projectile speed's maximum
    float m_fUnk8C;                            // +0x8c the projectile spread
    float m_fUnk90;                            // +0x90 the delay before a stopped jet's effects go
    CTriggerStarter m_tsUnk94;                 // +0x94 the start signals (PostLoad runs its PostLoad)
    CTriggerStarter m_tsUnk9C;                 // +0x9c the stop signals
    uint8_t m_unkA4;                           // +0xa4 enabled for the default state / preset 0
    uint8_t m_unkA5;                           // +0xa5 enabled for preset 1
    uint8_t m_unkA6;                           // +0xa6 the rumble's motor
    uint8_t m_unkA7;                           // +0xa7 the rumble's value
    float m_fUnkA8;                            // +0xa8 the rumble's duration
    float m_fUnkAC;                            // +0xac runtime: the warm-up / full-strength timer
    float m_fUnkB0;                            // +0xb0 runtime: the time to the next projectile
    float m_fUnkB4;                            // +0xb4 runtime: the time before a stopped jet's effects go
    IKFx* m_pUnkB8;                            // +0xb8 runtime: the start effect (a CKParticlesEffectNodeFx)
    IKFx* m_pUnkBC;                            // +0xbc runtime: the boost effect (a CKParticlesEffectNodeFx)
    IKFx* m_pUnkC0;                            // +0xc0 runtime: the spark
    IKFx* m_pUnkC4;                            // +0xc4 runtime: the bolt (a CKLightningBoltNodeFx)
    JetContact* m_pUnkC8;                      // +0xc8 runtime: the contact list; constructor 0
};
DOTD_ASSERT_SIZE(CKHkHazardousJet, 0xcc);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_afUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_fUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_afUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_fUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_fUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_tsUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_tsUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_fUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_fUnkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnkB8, 0xb8);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkHazardousJet, m_pUnkC8, 0xc8);
