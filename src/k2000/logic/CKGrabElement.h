// CKGrabElement.h - the grab-attack element base (key 0x9fcc, vtable 0xb23ae0, size 0x140). Original unit:
// CKGrabElement.cpp (0x3a5e60-0x3a9c50). No XXL2 class of this name: the members keep placeholder names.
// Base of CKElectricalGrapple and CKWindBeam (their Loads call this one first). The family drives its user only through
// the ability host (CKS08AbilityHostBase), so the heroes' grab abilities and the enemies' (CKS08EnemyAbilityHost) share
// it. Phases: the start animation (+0x126, phase 0), the loop (+0x125, phase 1, or the alternative 2 while the host
// allows it, +0x134), the end animation (+0x127, phase 4); the mana is spent by the second (+0x2c per second), the grab
// (vt+0x7c) goes through the host's GrabEnemy (vt+0xec) on its locked target.
#pragma once
#include "k2000/logic/CKAbilityElement.h"
#include <cstdint>

#include "k2000/math/Vec3.h"

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKGrabElement : public CKAbilityElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x27f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfef8
        return key == 0x9fcc || key == 0xc || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKGrabElement)

    CKGrabElement() {}  // 0x003a5eb0 CKGrabElement_Construct: stores the vtable only
    ~CKGrabElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003a83c0 CKGrabElement_Load
    // vt+0x30 0x003a8370 CKGrabElement_PostLoad: ResetRuntime (vt+0x6c).
    int32_t PostLoad(int32_t /*type*/) override {
        ResetRuntime();
        return 1;
    }

    // The ability protocol (CKAbilityElement.h).
    uint8_t GetAbilityId() override { return 0x18; }  // vt+0x50 0x003a5ed0
    uint8_t GetFamilyId() override { return 0x18; }   // vt+0x54 0x003a5ed8
    // vt+0x58 0x003a7c80 CKGrabElement_Start: when not running and with a host: the host kept, the phases and the
    // target cleared, running; the level index (host vt+0xf4), the hero control on, the mana accumulator cleared, the
    // alternative loop allowed (host vt+0x38); the start animation (phase 0), else the loop (phase 2 when allowed,
    // else 1); the start time (the game clock).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x5c 0x003a5ee0 CKGrabElement_Stop: while running, the grab let go (vt+0x88) and End(forced).
    void Stop(int32_t forced) override;
    // vt+0x60 0x003a7070 CKGrabElement_Update: the phases, the mana, the grab and its hold; 0 once over (End called).
    uint8_t Update(float dt) override;
    // vt+0x64 0x003a5f70 CKGrabElement_End: the hero control off, not running, the level's cooldown (+0x20 forced,
    // else +0x14) set through the host (per slot unless forced), the host dropped.
    void End(int32_t forced) override;
    // vt+0x68 0x003a6058 CKGrabElement_ApplyHeroControl: the user's permissions, turn, 11f8 and move speed from the
    // data's air / flying / ground settings (on), or all of them off; +0x12e = standing (host vt+0x30 inverted).
    void ApplyHeroControl(uint8_t on) override;
    // The grab family's slots.
    // vt+0x6c 0x003a6650 CKGrabElement_ResetRuntime: the runtime state cleared (start time -1, hot spot 0xff, button 1).
    virtual void ResetRuntime();
    virtual void SetFxActive(int32_t /*on*/) {}  // vt+0x70 0x009bfed0 (empty)
    virtual void UpdateGrab() {}                // vt+0x74 0x009bfed8 KBaseC_vf74_2 (empty)
    // vt+0x78 0x003a6c48 CKGrabElement_StartEmitterFx: a pooled effect of the explosion data (+0x11c) for this element
    // (CKSrvFx::AcquireFx), put at the hot spot +0x12c, triggered and released.
    virtual void StartEmitterFx();
    // vt+0x7c 0x003a7eb8 CKGrabElement_GrabTarget_maybe: `grab` 1: a held target let go (host vt+0xec with grab 0), then
    // the host's target point grabbed (vt+0x98, then vt+0xec with grab 1: +0x12f = held; held: +0xd4 = the locked
    // target, vt+0xd4); `grab` 0: the held target let go (+0x12f = not let go), +0xd4 cleared. A null `direction`
    // becomes the target's position minus the user's.
    virtual void GrabTarget(uint8_t grab, uint8_t mode, CVector3* direction);
    virtual uint8_t Vf80(float /*dt*/) { return 1; }  // vt+0x80 0x009bfee0: the hold goes on
    virtual void Vf84(float /*dt*/) {}                // vt+0x84 0x009bfee8 (empty)
    // vt+0x88 0x003a6fb8 CKGrabElement_ReleaseAndStopFx_maybe: a held target let go (vt+0x7c with grab 0), the
    // effects off (vt+0x70), the loop phase over.
    virtual void ReleaseAndStopFx();
    // vt+0x8c 0x003a66a0 CKGrabElement_ApplyDamageParams: the damage object (+0x138, a CKS08ElementDamage) set up from
    // the level's values, scaled by the host's damage / effect scales.
    virtual void ApplyDamageParams(uint8_t continuous);
    virtual uint8_t Vf90() { return 0; }  // vt+0x90 0x009bfc00 KBaseC_vf90_2
    virtual uint8_t Vf94() { return 0; }  // vt+0x94 0x009bfef0 KBaseC_vf94_2

    uint32_t m_dwLevelIndex;          // +0x04 runtime: the level index (0..2, host vt+0xf4) at Start
    int32_t m_ai32Damage[3];        // +0x08 (file: 40/60/120)
    float m_afCooldown[3];          // +0x14
    float m_unk20;             // +0x20
    float m_unk24;             // +0x24
    float m_unk28;             // +0x28
    int32_t m_ai32ManaPerSecond[3];        // +0x2c (file: 10/12/16)
    float m_unk38[3];          // +0x38
    float m_unk44[3];          // +0x44
    float m_afDisarmAmount[3];  // +0x50 the damage's disarm amount (vt+0x60: damage +0x2c, added to the enemy's disarm gauge +0x278)
    // The damage per level (ApplyDamageParams reads them with lfs: floats; LVL010's are 0).
    float m_afStunAmount[3];          // _maybe: +0x5c the stun (damage vt+0x5c)
    float m_afElementEffect0[3];          // +0x68 element value 0
    float m_afElementEffect1[3];          // +0x74 element value 1
    float m_afElementEffect2[3];          // +0x80 element value 2
    float m_afElementEffect4[3];          // +0x8c element value 4
    float m_afElementEffect6[3];          // +0x98 element value 6
    float m_afElementEffect5[3];          // +0xa4 element value 5
    float m_afElementEffect7[3];          // +0xb0 element value 7
    float m_afElementEffect3[3];          // +0xbc element value 3
    uint8_t m_abDamageFlag34[3];        // +0xc8 the damage's +0x34
    uint8_t m_abDamageFlag35[3];        // +0xcb the damage's +0x35
    uint8_t m_padCe[2];        // +0xce
    IKSerializable* m_pAimCone;   // +0xd0 reference (live: CKAimCamembert): passed to the host's aim (vt+0x58)
    IKSerializable* m_pTarget;  // +0xd4 runtime: the grabbed target (the host's locked target, vt+0xd4)
    uint8_t m_unkD8;           // +0xd8
    uint8_t m_unkD9;           // +0xd9
    uint8_t m_unkDa;           // +0xda
    uint8_t m_padDb;           // +0xdb
    float m_unkDc;             // +0xdc
    float m_unkE0;             // +0xe0
    uint8_t m_unkE4;           // +0xe4
    uint8_t m_unkE5;           // +0xe5
    uint8_t m_unkE6;           // +0xe6
    uint8_t m_padE7;           // +0xe7
    float m_unkE8;             // +0xe8
    float m_unkEc;             // +0xec
    float m_fGroundMoveSpeed;             // +0xf0
    float m_fFlyMoveSpeed;             // +0xf4
    uint8_t m_unkF8;           // +0xf8
    uint8_t m_unkF9;           // +0xf9
    uint8_t m_padFa[2];        // +0xfa (not loaded)
    float m_unkFc;             // +0xfc
    float m_unk100;            // +0x100
    uint8_t m_unk104;          // +0x104
    uint8_t m_unk105;          // +0x105
    uint8_t m_unk106;          // +0x106
    uint8_t m_pad107;          // +0x107
    float m_unk108;            // +0x108
    float m_unk10c;            // +0x10c
    float m_fAirMoveSpeed;            // +0x110
    uint8_t m_bAirParam11f8Enable;          // +0x114
    uint8_t m_pad115[3];       // +0x115 (not loaded)
    float m_fAirParam11f8;            // +0x118
    IKSerializable* m_pFizzleExplosionFxData;  // +0x11c reference (live: CKExplosionFxData): StartEmitterFx's effect
    // The runtime (not loaded; ResetRuntime / Start).
    CKS08AbilityHostBase* m_pHost;  // +0x120 the host while running
    uint8_t m_bRunning;        // +0x124
    uint8_t m_bInLoop;          // +0x125 in the loop phase
    uint8_t m_bInStartAnim;          // +0x126 in the start animation (phase 0)
    uint8_t m_bInEndAnim;          // +0x127 in the end animation (phase 4)
    float m_fMana;             // +0x128 the mana spent and not yet taken (whole points go to the host, vt+0xb8)
    uint8_t m_bHotspotIndex;          // +0x12c the hot spot index (host vt+0xcc / +0xd0; ResetRuntime 0xff)
    uint8_t m_bButtonIndex;          // +0x12d the button (host vt+0x8c / +0x94; ResetRuntime 1)
    uint8_t m_bInAir;          // +0x12e in the air (host vt+0x30, IsOnGround, inverted; ApplyHeroControl, Update)
    uint8_t m_bTargetHeld;          // +0x12f a target is held (GrabTarget)
    float m_fStartTime;        // +0x130 the game clock at Start (ResetRuntime -1)
    uint8_t m_bAltLoopAnim;          // +0x134 the alternative loop (phase 2) plays
    uint8_t m_pad135[3];       // +0x135
    IKSerializable* m_pElementDamage;  // +0x138 reference (live: CKS08ElementDamage)
    uint8_t m_bForcedEnd;          // +0x13c the end is forced (out of mana): End's argument
    uint8_t m_pad13d[3];       // +0x13d
};
DOTD_ASSERT_SIZE(CKGrabElement, 0x140);
DOTD_ASSERT_OFFSET(CKGrabElement, m_ai32Damage, 0x08);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afCooldown, 0x14);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKGrabElement, m_ai32ManaPerSecond, 0x2c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afDisarmAmount, 0x50);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afStunAmount, 0x5c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect0, 0x68);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect1, 0x74);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect2, 0x80);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect4, 0x8c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect6, 0x98);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect5, 0xa4);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect7, 0xb0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_afElementEffect3, 0xbc);
DOTD_ASSERT_OFFSET(CKGrabElement, m_abDamageFlag34, 0xc8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_abDamageFlag35, 0xcb);
DOTD_ASSERT_OFFSET(CKGrabElement, m_pAimCone, 0xd0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkD9, 0xd9);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkDa, 0xda);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkDc, 0xdc);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE5, 0xe5);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE6, 0xe6);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkEc, 0xec);
DOTD_ASSERT_OFFSET(CKGrabElement, m_fGroundMoveSpeed, 0xf0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_fFlyMoveSpeed, 0xf4);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkF9, 0xf9);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkFc, 0xfc);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk105, 0x105);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk106, 0x106);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk10c, 0x10c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_fAirMoveSpeed, 0x110);
DOTD_ASSERT_OFFSET(CKGrabElement, m_bAirParam11f8Enable, 0x114);
DOTD_ASSERT_OFFSET(CKGrabElement, m_fAirParam11f8, 0x118);
DOTD_ASSERT_OFFSET(CKGrabElement, m_pFizzleExplosionFxData, 0x11c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_pTarget, 0xd4);
DOTD_ASSERT_OFFSET(CKGrabElement, m_pHost, 0x120);
DOTD_ASSERT_OFFSET(CKGrabElement, m_bRunning, 0x124);
DOTD_ASSERT_OFFSET(CKGrabElement, m_fMana, 0x128);
DOTD_ASSERT_OFFSET(CKGrabElement, m_bHotspotIndex, 0x12c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_bTargetHeld, 0x12f);
DOTD_ASSERT_OFFSET(CKGrabElement, m_fStartTime, 0x130);
DOTD_ASSERT_OFFSET(CKGrabElement, m_bAltLoopAnim, 0x134);
DOTD_ASSERT_OFFSET(CKGrabElement, m_pElementDamage, 0x138);
DOTD_ASSERT_OFFSET(CKGrabElement, m_bForcedEnd, 0x13c);
