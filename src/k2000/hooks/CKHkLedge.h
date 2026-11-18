// CKHkLedge.h - a ledge that shakes while a hero stands on it, falls, and comes back (key 0x1582, vtable 0xb25e08,
// size 0xa0). Original unit: CKHkLedge.cpp (0x419a18-0x41be10). No XXL2 class of this key; the layout comes from the
// Load (every word read for every serialization type) and the users in the unit. No level of the game holds one
// (C2.8 port-rest R04: ported from the disassembly, nothing replays it).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKFx;
class IKTime;

class CKHkLedge : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x56)
    // vt+0x08 0x009c2f20 CKHkLedge_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x1582 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkLedge)

    CKHkLedge() {}  // 0x0041a378 CKHkLedge_Create: the CKHkActorBase defaults only
    ~CKHkLedge() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0041b640 CKHkLedge_Load
    // vt+0x38 0x00419e28 CKHkLedge_SetDefaultState: the actor base's (empty), then the preset 0 (vt+0xc8).
    void SetDefaultState(int32_t flag) override {
        CKHkActorBase::SetDefaultState(flag);
        ApplyStatePreset(0);
    }
    // vt+0xc8 0x00419a68 CKHkLedge_vfC8: +0x51 = the preset byte; the respawn timer (+0x44) -1 with a preset (the
    // ledge stays down: Update's respawn needs +0x44 >= 0), else 0.
    void ApplyStatePreset(int32_t state) override {
        m_unk51 = static_cast<uint8_t>(state);
        m_fRespawnTimer = state == 0 ? 0.0f : -1.0f;  // TOC +0x4c48 -1.0
    }
    // vt+0x40 0x00419b18 CKHkLedge_GetInfo: the actor base's answer (KStub_Return1 0x3f7140) merged with none.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    // vt+0x1c 0x0041a1c0 CKHkLedge_MessageProc: the actor messages (0x3f7148), then 0x996 starts the shaking (the timer
    // +0x40 = +0x60) when it is not running and the ledge is up; the answers merged.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x54 0x0041a4d0 CKHkLedge_Restart: an enabled ledge (flag bit 2 clear) back up (Reset; the node hidden and the
    // ground off while the respawn timer is negative), the timer -1 again with a preset.
    void Restart() override;
    // vt+0xa0 0x0041a5c0 CKHkLedge_OnActivate: the actor base's, Reset as Restart, the node at the null vector, the hook
    // node shown, no effect, no vibration owner.
    void VfA0() override;
    // vt+0xa4 0x0041a3d0 CKHkLedge_OnDeactivate: the actor base's, sound 1 stopped, the ground off, StopFeedback.
    void VfA4() override;
    // vt+0xb4 0x0041a0b0 CKHkLedge_AttachSounds: sounds 0 and 1 (+0x74, GetSound_2) on the hook node.
    void KGLObjectAttached(IKSerializable* leaf) override;
    void Update(IKTime* frameClock) override;  // vt+0x7c 0x0041a710 CKHkLedge_Update

    // 0x00419b68 CKHkLedge_IsHeroOnLedge_maybe: a hero of the +0x52 mask (from the last dragon index, stopping at the
    // first) whose ledge ground (IKHkHero_GetLedgeGroundContact_maybe), or with flag bit 4 whose ground, is +0x78.
    uint8_t IsHeroOnLedge();
    // The reset Update / Restart / OnActivate inline (0.0): the timers, the shaking state and the alpha (0xff) back.
    void ResetShake();
    // The end of the shaking Update / OnDeactivate inline: the shake effect (+0x48) stopped and released (vt+0x58) and
    // the pad vibration (+0x4c) stopped (CKInput_StopVibration_maybe) when it runs.
    void StopShakeFx();
    void StopVibration();

    // FloatApproachAccel_Step's state {target, top speed, speed, acceleration, current}: the shaking offset.
    float m_afShake[5];                   // +0x20 (+0x2c = +0x54, +0x24 = +0x58 at reset; +0x30 the node's y)
    uint8_t m_pad34[0xc];                 // +0x34 never used
    float m_fShakeTimer;                  // +0x40 the time left before the fall (MessageProc / a hero on it: +0x60)
    float m_fRespawnTimer;                // +0x44 the time since the fall (respawn after +0x64; -1 with a preset)
    IKFx* m_pShakeFx;                     // +0x48 the effect of +0x84 while shaking
    IKSerializable* m_pVibration;         // +0x4c a CKVibrationData (pad vibration while a hero is on it)
    uint8_t m_ui8Alpha;                   // +0x50 the fade-in alpha after a respawn (0xff: done)
    uint8_t m_unk51;                      // +0x51 the preset (vt+0xc8)
    uint8_t m_ui8HeroMask;                // +0x52 the dragon indices tested (bit = index)
    uint8_t m_pad53;
    float m_unk54;                        // +0x54 the shaking's acceleration
    float m_unk58;                        // +0x58 the shaking's top speed
    float m_unk5C;                        // +0x5c the shaking's amplitude (the offset swings between -/+ it)
    float m_unk60;                        // +0x60 the shaking time before the fall
    float m_unk64;                        // +0x64 the respawn delay (0: never)
    float m_afProjectileOffset[3];        // +0x68 along the node's LTM right row, for the three launchers
    IKSerializable* m_pSounds;            // +0x74 a CKSoundDictionaryID: 0 the fall, 1 the shaking loop
    IKSerializable* m_pGround;            // +0x78 the ledge's collision mesh
    IKSerializable* m_pNode;              // +0x7c the shaking node (a CSGMovable)
    IKSerializable* m_pFallFxData;        // +0x80 started at the fall (CKSrvFx::StartEffect)
    IKSerializable* m_pShakeFxData;       // +0x84 acquired while shaking (CKSrvFx::AcquireFx)
    IKSerializable* m_apLauncher[3];      // +0x88 CKProjectileAccessor, launched at the fall
    IKSerializable* m_pSekens;            // +0x94 a CKSekensLauncherCpnt, played at the fall
    CTriggerStarter m_tsFall;             // +0x98 queued at the fall
};
DOTD_ASSERT_SIZE(CKHkLedge, 0xa0);
DOTD_ASSERT_OFFSET(CKHkLedge, m_afShake, 0x20);
DOTD_ASSERT_OFFSET(CKHkLedge, m_fShakeTimer, 0x40);
DOTD_ASSERT_OFFSET(CKHkLedge, m_pShakeFx, 0x48);
DOTD_ASSERT_OFFSET(CKHkLedge, m_ui8Alpha, 0x50);
DOTD_ASSERT_OFFSET(CKHkLedge, m_ui8HeroMask, 0x52);
DOTD_ASSERT_OFFSET(CKHkLedge, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkLedge, m_afProjectileOffset, 0x68);
DOTD_ASSERT_OFFSET(CKHkLedge, m_pSounds, 0x74);
DOTD_ASSERT_OFFSET(CKHkLedge, m_pNode, 0x7c);
DOTD_ASSERT_OFFSET(CKHkLedge, m_apLauncher, 0x88);
DOTD_ASSERT_OFFSET(CKHkLedge, m_pSekens, 0x94);
DOTD_ASSERT_OFFSET(CKHkLedge, m_tsFall, 0x98);
