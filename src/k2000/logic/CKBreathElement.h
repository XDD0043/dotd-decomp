// CKBreathElement.h - the breath-attack element base (key 0x914c, vtable 0xb23588, size 0x178). Original unit:
// CKBreathElement.cpp (0x380ed0-0x385a78). No XXL2 class of this name: the members keep placeholder names.
// Base of CKFireBreath, CKFearEyes, CKPurpleRay and CKShadowBreath (their Loads call this one first).
//
// The breath: Start plays the start animation (phase 0) or the loop (phase 1, phase 2 the alternative loop); while the
// button is held the loop spends mana per second (+0x38[level]) and emits damage spheres from the hero's hot spot 2
// along the aim direction (UpdateDamageSpheres): each sphere moves at the hero's speed plus +0x138, grows with the
// cone's half angle (+0x44[level]) from the base radius (+0x50[level]) and lives +0x130 seconds; a new one leaves once
// the newest is +0x134 away. Out of mana: the fizzle (StartEmitterFx) and the end animation (phase 4).
#pragma once
#include "k2000/logic/CKAbilityElement.h"
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/Mem.h"

class CKDynamicBoundingSphere;

class CKBreathElement : public CKAbilityElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x245)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfa30
        return key == 0x914c || key == 0xc || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKBreathElement)

    CKBreathElement();  // 0x00381eb8 CKBreathElement_Construct
    // 0x00382de8 CKBreathElement_Destructor / 0x00383bb0 DestructBody / 0x00384ba8 DeletingDestructor: the spheres'
    // block freed (Mem_FreeAligned16 0x52fb8, when there is one), the count and the block cleared.
    ~CKBreathElement() override {
        if (m_pSegments != nullptr) Mem_FreeAligned16(m_pSegments);
        m_ui32SegmentCount = 0;
        m_pSegments = nullptr;
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00383c30 CKBreathElement_Load
    // vt+0x30 0x00382d98 CKBreathElement_PostLoad: ResetRuntime(type) (vt+0x6c), 1.
    int32_t PostLoad(int32_t type) override {
        ResetRuntime(type);
        return 1;
    }

    // The ability protocol (CKAbilityElement.h).
    uint8_t GetAbilityId() override { return 0x15; }  // vt+0x50 0x00380f40
    uint8_t GetFamilyId() override { return 0x15; }   // vt+0x54 0x00380f48
    // vt+0x58 0x00380f50 CKBreathElement_Start: when not running and with a host: the host kept, running, the level
    // index, the hero control on, the alternative loop's test, the counters cleared; the start animation (phase 0)
    // else the loop (phase 2 with the alternative loop, else 1) with the effects on when the dragon has mana; the start
    // time (the game clock).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x5c 0x00381190 CKBreathElement_Stop: while running, StopBreathing (vt+0x7c) and End(forced).
    void Stop(int32_t forced) override;
    // vt+0x60 0x00382430 CKBreathElement_Update. 0 once over (End called).
    uint8_t Update(float dt) override;
    // vt+0x64 0x00381220 CKBreathElement_End: every damage sphere released, the hero control off, not running, the
    // cooldown of the level (+0x2c forced, else +0x20) set through the host (per slot unless forced), the host dropped.
    void End(int32_t forced) override;
    // vt+0x68 0x00381330 CKBreathElement_ApplyHeroControl
    void ApplyHeroControl(uint8_t on) override;
    // The breath family's slots.
    // vt+0x6c 0x00381ed8 CKBreathElement_ResetRuntime: the runtime state cleared (hot spot 0xff, button 1, start time
    // -1); level data (type 0) also gets a new one-segment block for the damage spheres.
    virtual void ResetRuntime(int32_t type);
    virtual void SetFxActive(uint8_t /*on*/) {}  // vt+0x70 0x009bfa20 (empty)
    // vt+0x74 0x00382028 CKBreathElement_StartEmitterFx: a pooled effect of the explosion data (+0x120) for this
    // element (CKSrvFx::AcquireFx), put at the hot spot +0x15c, triggered and released (the fizzle).
    virtual void StartEmitterFx();
    virtual void UpdateFx(float /*dt*/) {}  // vt+0x78 0x009bfa28 (empty)
    // vt+0x7c 0x00381928 CKBreathElement_StopBreathing: the effects off (vt+0x70), the loop over (+0x155).
    virtual void StopBreathing();
    // vt+0x80 0x00382e68 CKBreathElement_UpdateDamageSpheres: `releaseAll` frees every sphere; else they move, grow and
    // die, the fire elements' spheres scorch the ground, and a new one leaves while breathing.
    virtual void UpdateDamageSpheres(float dt, uint8_t releaseAll);
    // vt+0x84 0x00382398 CKBreathElement_GetEmitterPosition: the direction of the breath: the x axis with `raw`, else
    // the host's aim direction (vt+0x24, levelled).
    virtual CVector3 GetEmitterPosition(uint8_t raw);
    // vt+0x88 0x00381980 CKBreathElement_ApplyDamageParams: the damage object (+0x170, a CKS08ElementDamage) set up
    // from the level's values.
    virtual void ApplyDamageParams(uint8_t continuous);

    // One damage sphere in flight (0x18 bytes on the PS3).
    struct Segment {
        CKDynamicBoundingSphere* m_pSphere;  // +0x00 a projectile volume of the collision service's pool
        CVector3 m_v3Direction;       // +0x04
        float m_fTime;                // +0x10 its age (at most +0x130)
        float m_fSpeed;               // +0x14
    };

    // The per-level arrays ([3], indexed by the level index +0x04).
    uint32_t m_dwLevelIndex;        // +0x04 (not loaded) runtime: the level index (0..2, host vt+0xf4) at Start
    int32_t m_ai32Damage[3];      // +0x08 the damage amount (file: 500/1000/3000)
    float m_afKnockbackDist[3];        // +0x14 the knock-back distance (the damage's +0x10 = this / 0.2)
    float m_afCooldown[3];        // +0x20 the cooldown after an End (file and live: 0)
    float m_afCooldownForced[3];        // +0x2c the cooldown after a forced End
    int32_t m_ai32ManaPerSecond[3];      // +0x38 the mana per second (file: 200/300/500)
    float m_afConeAngleDeg[3];        // +0x44 the cone's angle in degrees (the spheres grow by tan(half of it))
    float m_unk50[3];        // +0x50 the spheres' base radius
    float m_afDisarmAmount[3];        // +0x5c the damage's disarm amount (vt+0x60: damage +0x2c, added to the enemy's disarm gauge +0x278)
    float m_afStunAmount[3];        // +0x68 the damage's stun (vt+0x5c)
    float m_afElementEffect0[3];        // +0x74 the damage's element value 0
    float m_afElementEffect1[3];        // +0x80 element value 1 (file and live: 0)
    float m_afElementEffect2[3];        // +0x8c element value 2
    float m_afElementEffect4[3];        // +0x98 element value 4
    float m_afElementEffect6[3];        // +0xa4 element value 6
    float m_afElementEffect5[3];        // +0xb0 element value 5
    float m_afElementEffect7[3];        // +0xbc element value 7
    float m_afElementEffect3[3];        // +0xc8 element value 3
    uint8_t m_abDamageFlag34[3];      // +0xd4 the damage's +0x34 (vt+0x6c)
    uint8_t m_abDamageFlag35[3];      // +0xd7 the damage's +0x35 (vt+0x70)
    // The hero control of the three movement contexts (airborne +0xda.., flying +0xe8.., ground +0x108..).
    uint8_t m_bGroundPerm1;         // +0xda on the ground: permission 1
    uint8_t m_bGroundPerm0;         // +0xdb on the ground: permission 0
    uint8_t m_bGroundTurnEnable;         // +0xdc on the ground: the turn gate
    uint8_t m_padDd[3];      // +0xdd (not loaded)
    float m_fGroundTurnA;           // +0xe0 on the ground: turn A (CKFireBreath: the spark's turn rate)
    float m_fGroundTurnB;           // +0xe4 on the ground: turn B
    uint8_t m_bFlyPerm1;         // +0xe8 flying: permission 1
    uint8_t m_bFlyPerm0;         // +0xe9 flying: permission 0
    uint8_t m_bFlyTurnEnable;         // +0xea flying: the turn gate
    uint8_t m_padEb;         // +0xeb
    float m_fFlyTurnA;           // +0xec flying: turn A
    float m_fFlyTurnB;           // +0xf0 flying: turn B
    float m_fGroundMoveSpeed;           // +0xf4 on the ground: the move speed
    float m_fFlyMoveSpeed;           // +0xf8 flying: the move speed
    uint8_t m_bGroundParam11f8Enable;         // +0xfc on the ground: the 11f8 gate
    uint8_t m_bFlyParam11f8Enable;         // +0xfd flying: the 11f8 gate
    uint8_t m_padFe[2];      // +0xfe (not loaded)
    float m_fGroundParam11f8;          // +0x100 on the ground: the 11f8 value
    float m_fFlyParam11f8;          // +0x104 flying: the 11f8 value
    uint8_t m_bAirPerm1;        // +0x108 in the air: permission 1
    uint8_t m_bAirPerm0;        // +0x109 in the air: permission 0
    uint8_t m_bAirTurnEnable;        // +0x10a in the air: the turn gate
    uint8_t m_pad10b;        // +0x10b
    float m_fAirTurnA;          // +0x10c in the air: turn A
    float m_fAirTurnB;          // +0x110 in the air: turn B
    float m_fAirMoveSpeed;          // +0x114 in the air: the move speed
    uint8_t m_bAirParam11f8Enable;        // +0x118 in the air: the 11f8 gate
    uint8_t m_pad119[3];     // +0x119 (not loaded)
    float m_fAirParam11f8;          // +0x11c in the air: the 11f8 value
    IKSerializable* m_pFizzleExplosionFxData;  // +0x120 reference (live: CKExplosionFxData): the fizzle
    Segment* m_pSegments;    // +0x124 the damage spheres in flight (a K array: block, capacity, count); constructor 0
    uint32_t m_ui32SegmentCapacity;  // +0x128 constructor: 1
    uint32_t m_ui32SegmentCount;     // +0x12c constructor: 0
    float m_fSphereLifetime;          // +0x130 a sphere's life time
    float m_fSphereSpacing;          // +0x134 the distance the newest sphere covers before the next leaves
    float m_fSphereSpeed;          // +0x138 the spheres' speed (added to the hero's)
    float m_fGroundScorchPeriod;          // +0x13c the ground scorch's period
    float m_fGroundScorchPeriodSpread;          // +0x140 its random spread
    float m_fGroundScorchHeight;          // +0x144 the scorch's height above the ground (file and live: 0)
    float m_fGroundScorchHeightSpread;          // +0x148 its random spread (file and live: 0)
    uint8_t m_bScorchesGround;        // +0x14c the spheres scorch the ground (fire elements only)
    uint8_t m_pad14d[3];     // +0x14d
    // Runtime (not loaded).
    CKS08AbilityHostBase* m_pHost;  // +0x150 the host while running
    uint8_t m_bRunning;      // +0x154
    uint8_t m_bBreathing;        // +0x155 breathing (the loop, phase 1 / 2)
    uint8_t m_bInStartAnim;        // +0x156 in the start animation (phase 0)
    uint8_t m_bInEndAnim;        // +0x157 in the end animation (phase 4)
    float m_fManaRemainder;          // +0x158 the mana spent but not taken yet (a fraction)
    uint8_t m_ui8HotspotIndex;        // +0x15c the hot spot index (host vt+0xcc / +0xd0; ResetRuntime 0xff)
    uint8_t m_ui8ButtonIndex;        // +0x15d the button (host vt+0x8c / +0x94; ResetRuntime 1)
    uint8_t m_bAltLoopAnim;        // +0x15e in the alternative loop (phase 2)
    uint8_t m_bInAir;        // +0x15f in the air (host vt+0x30, IsOnGround, negated)
    float m_fStartTime;      // +0x160 the game clock at Start (ResetRuntime: -1)
    float m_fGroundScorchTimer;          // +0x164 the time left before the next ground scorch
    uint32_t m_dwScorchSegmentIndex;       // +0x168 the spheres that scorched (index) since the timer ran out
    float m_fBreathElapsedTime;          // +0x16c the breathing time
    IKSerializable* m_pElementDamage;  // +0x170 reference (live: CKS08ElementDamage)
    uint8_t m_bForcedEnd;        // +0x174 End's argument after the fizzle (a byte; the other three are never written)
    uint8_t m_pad175[3];
};
DOTD_ASSERT_SIZE(CKBreathElement::Segment, 0x18);
DOTD_ASSERT_SIZE(CKBreathElement, 0x178);
DOTD_ASSERT_OFFSET(CKBreathElement, m_ai32Damage, 0x08);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afKnockbackDist, 0x14);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afCooldown, 0x20);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afCooldownForced, 0x2c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_ai32ManaPerSecond, 0x38);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afConeAngleDeg, 0x44);
DOTD_ASSERT_OFFSET(CKBreathElement, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afDisarmAmount, 0x5c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afStunAmount, 0x68);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect0, 0x74);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect1, 0x80);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect2, 0x8c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect4, 0x98);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect6, 0xa4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect5, 0xb0);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect7, 0xbc);
DOTD_ASSERT_OFFSET(CKBreathElement, m_afElementEffect3, 0xc8);
DOTD_ASSERT_OFFSET(CKBreathElement, m_abDamageFlag34, 0xd4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_abDamageFlag35, 0xd7);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bGroundPerm1, 0xda);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bGroundPerm0, 0xdb);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bGroundTurnEnable, 0xdc);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundTurnA, 0xe0);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundTurnB, 0xe4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bFlyPerm1, 0xe8);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bFlyPerm0, 0xe9);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bFlyTurnEnable, 0xea);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fFlyTurnA, 0xec);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fFlyTurnB, 0xf0);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundMoveSpeed, 0xf4);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fFlyMoveSpeed, 0xf8);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bGroundParam11f8Enable, 0xfc);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bFlyParam11f8Enable, 0xfd);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundParam11f8, 0x100);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fFlyParam11f8, 0x104);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bAirPerm1, 0x108);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bAirPerm0, 0x109);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bAirTurnEnable, 0x10a);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fAirTurnA, 0x10c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fAirTurnB, 0x110);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fAirMoveSpeed, 0x114);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bAirParam11f8Enable, 0x118);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fAirParam11f8, 0x11c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_pFizzleExplosionFxData, 0x120);
DOTD_ASSERT_OFFSET(CKBreathElement, m_pSegments, 0x124);
DOTD_ASSERT_OFFSET(CKBreathElement, m_ui32SegmentCapacity, 0x128);
DOTD_ASSERT_OFFSET(CKBreathElement, m_ui32SegmentCount, 0x12c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fSphereLifetime, 0x130);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fSphereSpacing, 0x134);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fSphereSpeed, 0x138);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundScorchPeriod, 0x13c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundScorchPeriodSpread, 0x140);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundScorchHeight, 0x144);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundScorchHeightSpread, 0x148);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bScorchesGround, 0x14c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_pHost, 0x150);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bRunning, 0x154);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fManaRemainder, 0x158);
DOTD_ASSERT_OFFSET(CKBreathElement, m_ui8HotspotIndex, 0x15c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bInAir, 0x15f);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fStartTime, 0x160);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fGroundScorchTimer, 0x164);
DOTD_ASSERT_OFFSET(CKBreathElement, m_dwScorchSegmentIndex, 0x168);
DOTD_ASSERT_OFFSET(CKBreathElement, m_fBreathElapsedTime, 0x16c);
DOTD_ASSERT_OFFSET(CKBreathElement, m_pElementDamage, 0x170);
DOTD_ASSERT_OFFSET(CKBreathElement, m_bForcedEnd, 0x174);
