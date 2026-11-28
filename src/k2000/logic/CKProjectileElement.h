// CKProjectileElement.h - the shared base of the projectile element attacks (key 0x934c, vtable 0xb23dd8,
// size 0x214). Original unit: CKProjectileElement.cpp (0x3bc818-0x3c1f38). Derives from IKSerializable only
// (its Load calls no base Load). No XXL2 class of this name: the members keep placeholder names.
// Bases of CKIceGatling, CKBlackBall, CKEarthMissile, CKFearScream, CKPoisonGrenade.
#pragma once
#include "k2000/logic/CKAbilityElement.h"
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/core/Stub.h"
#include "k2000/math/CMatrix34.h"

class CKProjectileElement : public CKAbilityElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24d)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0178
        return key == 0x934c || key == 0xc || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileElement)

    CKProjectileElement() {}  // 0x003bc868 CKProjectileElement_Construct: stores the vtable only
    ~CKProjectileElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003bf360 CKProjectileElement_Load
    // vt+0x30 0x003bf280 CKProjectileElement_PostLoad: ResetRuntime(type) (vt+0x70).
    int32_t PostLoad(int32_t type) override {
        ResetRuntime(type);
        return 1;
    }

    // The ability protocol (CKAbilityElement.h).
    uint8_t GetAbilityId() override { return 0x16; }  // vt+0x50 0x003bc888
    uint8_t GetFamilyId() override { return 0x16; }   // vt+0x54 0x003bc890
    // vt+0x58 0x003bc898 CKProjectileElement_Start: when not running and with a host: the runtime cleared, the host
    // kept, running; the level index (host vt+0xf4), the hero control on, the start animation (phase 0) else the
    // charge animation (phase 1) played (flag +0x1f5 / +0x1f6); the start time (the game clock).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x5c 0x003bca10 CKProjectileElement_Stop: End(forced) while running.
    void Stop(int32_t forced) override {
        if (m_bRunning != 0) End(forced);
    }
    // vt+0x60 0x003be178 CKProjectileElement_Update: the phases (start animation, charge, aim, release, end
    // animation), the mana check, the launch (Fire, vt+0x78) or the fizzle (StartEmitterFx, vt+0x80). 0 once over (End
    // called).
    uint8_t Update(float dt) override;
    // vt+0x64 0x003bca60 CKProjectileElement_End: the hero control off, not running, the cooldown of the level (+0x44
    // forced, else +0x38) set through the host (per slot unless forced), the host dropped.
    void End(int32_t forced) override;
    // vt+0x68 0x003bcb48 CKProjectileElement_ApplyHeroControl: the hero's permissions, turn, 11f8 and move speed from
    // the data's air / flying / ground settings (on), or all of them off.
    void ApplyHeroControl(uint8_t on) override;
    // The projectile family's slots.
    virtual void UpdateCharge(float /*dt*/) {}  // vt+0x6c 0x009bff30 (empty)
    // vt+0x70 0x003bd1b0 CKProjectileElement_ResetRuntime: the runtime state cleared (start time -1, timer +0x1fc
    // from +0x74, bytes +0x208 / +0x209 0xff).
    virtual void ResetRuntime(int32_t type);
    // vt+0x74 0x003bd598 CKProjectileElement_ApplyDamageParams: the damage object (+0x20c, a CKS08ElementDamage) set
    // up for the shot from the level's normal or charged (the charge time +0x200 reached +0x68) values; one Rand_Int
    // draw (the knock angle +0x18).
    virtual void ApplyDamageParams(uint8_t continuous);
    virtual uint8_t Fire() { return 1; }             // vt+0x78 0x009c0168: launched
    virtual uint8_t IsChargeDisabled() { return 0; }  // vt+0x7c 0x009c0170
    // vt+0x80 0x003bdc88 CKProjectileElement_StartEmitterFx: a pooled effect of the explosion data (+0x1ec) for this
    // element (CKSrvFx::AcquireFx), put at the hot spot +0x208, triggered and released.
    virtual void StartEmitterFx();

    // 0x003bd1f8 CKProjectileElement_SetAimControl_maybe: the aiming hero control (on: the +0x1d8.. settings) or back
    // to the ability's (off: the +0x194.. settings).
    void SetAimControl(uint8_t on);
    // 0x003bdff8 CKProjectileElement_GetLaunchPosDir_maybe: the launch point: the hot spot +0x208's world position moved
    // by the launch offset +0x188 plus `offset` along the hot spot's axes (only a position, no direction).
    CVector3 GetLaunchPosDir(const CVector3* offset);

    // Arrays of 3: the Load's 3-iteration loop reads element i of each. Types from the level data (live
    // floats/ints); arrays that are zero in every sample are uint32_t.
    uint32_t m_ui32LevelIndex;                // +0x04 (not read) runtime: the level index (0..2, host vt+0xf4) at Start
    int32_t m_ai32DamageNormal[3];              // +0x08 (file: 10, 15, 30)
    int32_t m_ai32DamageCharged[3];              // +0x14 (file: 100, 80, 200)
    float m_unk20;                   // +0x20
    float m_unk24;                   // +0x24
    float m_unk28;                   // +0x28
    float m_unk2c;                   // +0x2c
    float m_unk30;                   // +0x30
    float m_unk34;                   // +0x34
    float m_afCooldown[3];                // +0x38 (always 0) the cooldown after an End, per level
    float m_afCooldownForced[3];                // +0x44 the cooldown after a forced End, per level (read after the loop)
    int32_t m_ai32ManaCostNormal[3];              // +0x50 (file: 6, 30, 45) the mana cost before the full charge, per level
    int32_t m_ai32ManaCostCharged[3];              // +0x5c (file: 100, 40, 45) the mana cost of a full charge, per level
    float m_afFullChargeTime[3];                // +0x68 (file: 5.0, 1.0, 2.0) the full charge time, per level
    float m_fTapWindow;                   // +0x74 (file: 0.22, 0.2) the tap window (ResetRuntime's +0x1fc)
    uint32_t m_unk78;                // +0x78 (always 0)
    uint32_t m_unk7c;                // +0x7c (always 0)
    uint32_t m_unk80;                // +0x80 (always 0)
    uint32_t m_unk84;                // +0x84 (always 0)
    float m_afDisarmAmountNormal[3];                // +0x88 (file: 0.9, 2.0)
    float m_afDisarmAmountCharged[3];                // +0x94 (file: 1.0)
    float m_afStunAmountNormal[3];                // +0xa0 (file: 0.5, 0.9, 1.5)
    float m_afStunAmountCharged[3];                // +0xac (file: 1.0)
    uint32_t m_afElem0Normal[3];             // +0xb8 (always 0)
    uint32_t m_afElem0Charged[3];             // +0xc4 (always 0)
    float m_afElem1Normal[3];                // +0xd0 (file: 1.5, 2.25, 4.0)
    uint32_t m_afElem1Charged[3];             // +0xdc (always 0)
    uint32_t m_afElem2Normal[3];             // +0xe8 (always 0)
    uint32_t m_afElem2Charged[3];             // +0xf4 (always 0)
    uint32_t m_afElem4Normal[3];            // +0x100 (always 0)
    uint32_t m_afElem4Charged[3];            // +0x10c (always 0)
    float m_afElem6Normal[3];               // +0x118 (file: 0.2, 0.3, 0.75)
    float m_afElem6Charged[3];               // +0x124 (file: 0.2, 0.4, 1.0)
    uint32_t m_afElem5Normal[3];            // +0x130 (always 0)
    uint32_t m_afElem5Charged[3];            // +0x13c (always 0)
    uint32_t m_afElem7Normal[3];            // +0x148 (always 0)
    uint32_t m_afElem7Charged[3];            // +0x154 (always 0)
    uint32_t m_unk160;               // +0x160
    uint32_t m_unk164;               // +0x164 (file: 0xcdcdcdcd, an uninitialised tool value)
    uint32_t m_unk168;               // +0x168 (file: 0xcdcdcdcd)
    uint32_t m_unk16c;               // +0x16c
    uint32_t m_unk170;               // +0x170 (file: 0xcdcdcdcd)
    uint32_t m_unk174;               // +0x174 (file: 0xcdcdcdcd)
    uint8_t m_abDmgFlag34Normal[3];             // +0x178
    uint8_t m_abDmgFlag34Charged[3];             // +0x17b
    uint8_t m_abDmgFlag35Normal[3];             // +0x17e
    uint8_t m_abDmgFlag35Charged[3];             // +0x181
    IKSerializable* m_pAimCone;        // +0x184 CKAimCamembert (live)
    uint32_t m_v3LaunchOffset[3];            // +0x188 one 12-byte read, three swapped words (always 0): the launch offset (floats)
    uint8_t m_unk194;                // +0x194
    uint8_t m_unk195;                // +0x195
    uint8_t m_unk196;                // +0x196 (+0x197 padding)
    float m_unk198;                  // +0x198
    float m_unk19c;                  // +0x19c
    uint8_t m_unk1a0;                // +0x1a0
    uint8_t m_unk1a1;                // +0x1a1
    uint8_t m_unk1a2;                // +0x1a2 (+0x1a3 padding)
    float m_unk1a4;                  // +0x1a4
    float m_unk1a8;                  // +0x1a8
    float m_fGroundMoveSpeed;                  // +0x1ac
    float m_fFlyMoveSpeed;                  // +0x1b0
    uint8_t m_unk1b4;                // +0x1b4
    uint8_t m_unk1b5;                // +0x1b5 (+0x1b6..+0x1b7 padding)
    float m_unk1b8;                  // +0x1b8
    float m_unk1bc;                  // +0x1bc
    uint8_t m_unk1c0;                // +0x1c0
    uint8_t m_unk1c1;                // +0x1c1
    uint8_t m_unk1c2;                // +0x1c2 (+0x1c3 padding)
    float m_unk1c4;                  // +0x1c4
    float m_unk1c8;                  // +0x1c8
    float m_fAirMoveSpeed;                  // +0x1cc
    uint8_t m_bAirParam11f8Enable;                // +0x1d0 (+0x1d1..+0x1d3 padding)
    float m_fAirParam11f8;                  // +0x1d4
    uint8_t m_unk1d8;                // +0x1d8
    uint8_t m_unk1d9;                // +0x1d9
    uint8_t m_unk1da;                // +0x1da
    uint8_t m_unk1db;                // +0x1db
    uint8_t m_unk1dc;                // +0x1dc
    uint8_t m_unk1dd;                // +0x1dd (+0x1de..+0x1df padding)
    float m_unk1e0;                  // +0x1e0
    float m_unk1e4;                  // +0x1e4
    float m_unk1e8;                  // +0x1e8
    IKSerializable* m_pFizzleExplosionFxData;        // +0x1ec CKExplosionFxData (live)
    // Runtime (not read).
    CKS08AbilityHostBase* m_pHost;   // +0x1f0 the host while running
    uint8_t m_bRunning;              // +0x1f4
    uint8_t m_bInStartAnim;                // +0x1f5 in the start animation (phase 0)
    uint8_t m_bInLoopAnim;                // +0x1f6 in the charge animation (phase 1)
    uint8_t m_bCharging;                // +0x1f7 aiming (phase 3)
    uint8_t m_bInEndAnim;                // +0x1f8 in the end animation (phase 4)
    uint8_t m_bInAir;                // +0x1f9 in the air (host vt+0x30, IsOnGround, inverted)
    uint8_t m_unk1fa;                // +0x1fa
    uint8_t m_pad1fb;
    float m_fTimeSinceRelease;                  // +0x1fc the time since the press (ResetRuntime: +0x74)
    float m_fChargeTime;                  // +0x200 the charge time
    float m_fStartTime;              // +0x204 the game clock at Start (ResetRuntime: -1)
    uint8_t m_ui8HotSpotIndex;                // +0x208 the hot spot index (host vt+0xcc / +0xd0)
    uint8_t m_ui8ButtonIndex;                // +0x209 the button (host vt+0x90 / +0x94)
    uint8_t m_pad20a[2];
    IKSerializable* m_pElementDamage;        // +0x20c CKS08ElementDamage (live)
    uint8_t m_bForcedEnd;                // +0x210 (not read) runtime: End's argument after a fizzle
    uint8_t m_pad211[3];
};
DOTD_ASSERT_SIZE(CKProjectileElement, 0x214);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_ai32DamageNormal, 0x08);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_ai32DamageCharged, 0x14);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afCooldown, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afCooldownForced, 0x44);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_ai32ManaCostNormal, 0x50);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_ai32ManaCostCharged, 0x5c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afFullChargeTime, 0x68);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_fTapWindow, 0x74);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afDisarmAmountNormal, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afDisarmAmountCharged, 0x94);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afStunAmountNormal, 0xa0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afStunAmountCharged, 0xac);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem0Normal, 0xb8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem0Charged, 0xc4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem1Normal, 0xd0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem1Charged, 0xdc);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem2Normal, 0xe8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem2Charged, 0xf4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem4Normal, 0x100);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem4Charged, 0x10c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem6Normal, 0x118);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem6Charged, 0x124);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem5Normal, 0x130);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem5Charged, 0x13c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem7Normal, 0x148);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_afElem7Charged, 0x154);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_abDmgFlag34Normal, 0x178);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_abDmgFlag34Charged, 0x17b);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_abDmgFlag35Normal, 0x17e);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_abDmgFlag35Charged, 0x181);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_pAimCone, 0x184);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_v3LaunchOffset, 0x188);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk196, 0x196);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1a2, 0x1a2);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_fFlyMoveSpeed, 0x1b0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1b5, 0x1b5);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1c2, 0x1c2);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_fAirMoveSpeed, 0x1cc);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_bAirParam11f8Enable, 0x1d0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_fAirParam11f8, 0x1d4);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1dd, 0x1dd);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_pFizzleExplosionFxData, 0x1ec);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_pHost, 0x1f0);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_unk1fa, 0x1fa);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_fTimeSinceRelease, 0x1fc);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_fStartTime, 0x204);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_ui8ButtonIndex, 0x209);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_bForcedEnd, 0x210);
DOTD_ASSERT_OFFSET(CKProjectileElement, m_pElementDamage, 0x20c);
