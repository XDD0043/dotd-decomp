// CKAttackMoveElement.h - the shared base of the element attack moves (key 0x9a0c, vtable 0xb23340, size 0x1a8).
// Original unit: CKAttackMoveElement.cpp (0x374d50-0x3798b8). No XXL2 class of this name: the members keep
// placeholder names. Base of CKBlackCombo, CKCometDash, CKPoisonSpin, CKPurpleCombo (CKAttackMoveLeaf.h).
// Its own base is the unregistered abstract KBase90CC (CKAbilityElement_maybe); its Load is not called and its
// constructor only stores a vtable (+0x04 is the level index the family keeps).
//
// The move: Start plays the start animation (phase 0) or, without one, the loop (phase 1) at once; the mana cost
// (+0x38[level], scaled) is taken once the start animation is over (out of mana: the fizzle and the end animation). In
// the loop the move winds up (+0x128), is steered (SteerTowardsTarget: the impulse along the aim, the effects on), then
// attacks for +0x44[level] seconds (UpdateAttack / UpdateMovement, a ground trail for the fire element) and ends with the
// end animation (phase 4).
#pragma once
#include "k2000/logic/CKAbilityElement.h"
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/Vec3.h"

// Three floats read with one 12-byte Read and swapped word by word (the derived Loads' +0x1e4 records;
// file values such as 0.75 0.75 1.0: a scale, _maybe).
struct CKAttackMoveVec3 {
    float m_unk0;
    float m_unk4;
    float m_unk8;
};
DOTD_ASSERT_SIZE(CKAttackMoveVec3, 0xc);

class CKAttackMoveElement : public CKAbilityElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x268)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bf870
        return key == 0x9a0c || key == 0xc || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKAttackMoveElement)

    CKAttackMoveElement() {}  // 0x00374da0 CKAttackMoveElement_Construct: stores the vtable only
    ~CKAttackMoveElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00377578 CKAttackMoveElement_Load
    // vt+0x30 0x00376e60 CKAttackMoveElement_PostLoad: ResetRuntime (vt+0x6c), 1.
    int32_t PostLoad(int32_t type) override {
        ResetRuntime(type);
        return 1;
    }

    // The ability protocol (CKAbilityElement.h).
    uint8_t GetAbilityId() override { return 0x19; }  // vt+0x50 0x00374dc0
    uint8_t GetFamilyId() override { return 0x19; }   // vt+0x54 0x00374dc8
    // vt+0x58 0x003760b0 CKAttackMoveElement_Start: when not running and with a host: the runtime cleared, the host kept,
    // running, the level index, the hero control on; the start animation (phase 0, +0x182), else the loop (phase 1:
    // +0x185 and +0x181, the mana taken at the first Update); the start time (the game clock).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x5c 0x00374dd0 CKAttackMoveElement_Stop: while running, StopFxAndAttack (vt+0x84) and End(forced).
    void Stop(int32_t forced) override;
    // vt+0x60 0x00376238 CKAttackMoveElement_Update. 0 once over (End called).
    uint8_t Update(float dt) override;
    // vt+0x64 0x00374ee0 CKAttackMoveElement_End: the hero control off, the impulse cleared (host vt+0x60), not running,
    // the cooldown of the level (+0x2c forced, else +0x20) set through the host (per slot unless forced), the host dropped.
    void End(int32_t forced) override;
    // vt+0x68 0x00374ff8 CKAttackMoveElement_ApplyHeroControl
    void ApplyHeroControl(uint8_t on) override;
    // The attack-move family's slots.
    // vt+0x6c 0x003756d0 CKAttackMoveElement_ResetRuntime: the runtime state cleared (hot spot 0xff, start time -1).
    virtual void ResetRuntime(int32_t type);
    virtual void SetFxActive(uint8_t /*on*/) {}      // vt+0x70 0x009bf848 (empty)
    virtual void SetAttackActive(uint8_t /*on*/) {}  // vt+0x74 0x009bf850 CKAttackMoveElement_vf74 (empty)
    virtual void UpdateAttack(float /*dt*/) {}       // vt+0x78 0x009bf858 (empty)
    virtual void UpdateMovement(float /*dt*/) {}     // vt+0x7c 0x009bf860 (empty)
    // vt+0x80 0x003757c0 CKAttackMoveElement_StartEmitterFx: a pooled effect of the explosion data (+0x178) put at the hot
    // spot +0x186, triggered and released (the fizzle).
    virtual void StartEmitterFx();
    // vt+0x84 0x00374e60 CKAttackMoveElement_StopFxAndAttack: the effects and the attack off (vt+0x70 / +0x74), not
    // attacking (+0x181).
    virtual void StopFxAndAttack();
    // vt+0x88 0x00375b30 CKAttackMoveElement_ApplyDamageParams: the damage object (+0x19c) set up from the level's values.
    virtual void ApplyDamageParams(uint8_t continuous);
    virtual uint8_t IsGroundTrailActive() { return 0; }  // vt+0x8c 0x009bf868 CKAttackMoveElement_vf8C
    // vt+0x90 0x00376eb0 CKAttackMoveElement_SteerTowardsTarget_maybe: the dash's direction (`direction`, the hero's
    // forward for the null vector) pitched as the hero's speed allows (+0x11c[level], +0x12c..+0x130), the impulse started
    // along it (host vt+0x5c), the attack phase on (+0x198) and the impulse's time (+0x18c + +0x50[level]).
    virtual void SteerTowardsTarget(const CVector3* direction);

    uint32_t m_unk04;      // +0x04 (not loaded) the level index (0..2, host vt+0xf4) at Start
    int32_t m_unk08[3];    // +0x08 the damage amount (file: 90 135 270)
    float m_unk14[3];      // +0x14 the knock-back distance (the damage's +0x10 = this / 0.2)
    float m_unk20[3];      // +0x20 the cooldown after an End
    float m_unk2c[3];      // +0x2c the cooldown after a forced End
    int32_t m_unk38[3];    // +0x38 the mana cost (file: 80 100 133)
    float m_unk44[3];      // +0x44 the attack's duration
    float m_unk50[3];      // +0x50 the impulse's delay after the steer
    float m_unk5c;         // +0x5c the ground trail's period
    float m_unk60;         // +0x60 its random spread
    float m_unk64;         // +0x64 the trail's scatter radius
    float m_unk68;         // +0x68 the trail's height (file and live: 0)
    float m_unk6c;         // +0x6c its random spread (file and live: 0)
    float m_unk70;         // +0x70 the damage's knock angle (degrees; file and live: 0)
    float m_unk74;         // +0x74 its random spread (file and live: 0)
    float m_unk78[3];      // +0x78 the damage's stun duration (vt+0x60)
    float m_unk84[3];      // +0x84 the damage's stun (vt+0x5c)
    float m_unk90[3];      // +0x90 the damage's element value 0
    float m_unk9c[3];      // +0x9c element value 1 (file and live: 0)
    float m_unka8[3];      // +0xa8 element value 2
    float m_unkb4[3];      // +0xb4 element value 4
    float m_unkc0[3];      // +0xc0 element value 6
    float m_unkcc[3];      // +0xcc element value 5
    float m_unkd8[3];      // +0xd8 element value 7
    float m_unke4[3];      // +0xe4 element value 3 (the Load reads the three words apart)
    uint8_t m_unkf0[3];    // +0xf0 the damage's +0x34 (vt+0x6c)
    uint8_t m_unkf3[3];    // +0xf3 the damage's +0x35 (vt+0x70)
    uint8_t m_padF6[2];    // +0xf6
    float m_unkf8[3];      // +0xf8 the impulse's speed (over 0.001 s)
    float m_unk104[3];     // +0x104 the impulse's second value (host vt+0x5c)
    float m_unk110[3];     // +0x110 the impulse's first value, negated (host vt+0x5c)
    float m_unk11c[3];     // +0x11c the steer's pitch (degrees; file and live: 0)
    float m_unk128;        // +0x128 the wind-up before the steer
    float m_unk12c;        // +0x12c the hero speed up to which the pitch is not limited
    float m_unk130;        // +0x130 the hero speed from which it is limited most
    // The hero control of the three movement contexts (airborne +0x134.., flying +0x140.., ground +0x160..).
    uint8_t m_unk134;      // +0x134 airborne: permission 1
    uint8_t m_unk135;      // +0x135 airborne: permission 0
    uint8_t m_unk136;      // +0x136 airborne: the turn gate
    uint8_t m_pad137;      // +0x137
    float m_unk138;        // +0x138 airborne: turn A
    float m_unk13c;        // +0x13c airborne: turn B
    uint8_t m_unk140;      // +0x140 flying: permission 1
    uint8_t m_unk141;      // +0x141 flying: permission 0
    uint8_t m_unk142;      // +0x142 flying: the turn gate
    uint8_t m_pad143;      // +0x143
    float m_unk144;        // +0x144 flying: turn A
    float m_unk148;        // +0x148 flying: turn B
    float m_unk14c;        // +0x14c airborne: the move speed
    float m_unk150;        // +0x150 flying: the move speed
    uint8_t m_unk154;      // +0x154 airborne: the 11f8 gate
    uint8_t m_unk155;      // +0x155 flying: the 11f8 gate
    uint8_t m_pad156[2];   // +0x156
    float m_unk158;        // +0x158 airborne: the 11f8 value
    float m_unk15c;        // +0x15c flying: the 11f8 value
    uint8_t m_unk160;      // +0x160 ground: permission 1
    uint8_t m_unk161;      // +0x161 ground: permission 0
    uint8_t m_unk162;      // +0x162 ground: the turn gate
    uint8_t m_pad163;      // +0x163
    float m_unk164;        // +0x164 ground: turn A
    float m_unk168;        // +0x168 ground: turn B
    float m_unk16c;        // +0x16c ground: the move speed
    uint8_t m_unk170;      // +0x170 ground: the 11f8 gate (one byte loaded)
    uint8_t m_unk171[3];   // +0x171 (not loaded)
    float m_unk174;        // +0x174 ground: the 11f8 value
    IKSerializable* m_unk178;  // +0x178 reference (live: CKExplosionFxData): the fizzle
    // Runtime (not loaded).
    CKS08AbilityHostBase* m_pHost;  // +0x17c the host while running
    uint8_t m_bRunning;    // +0x180
    uint8_t m_unk181;      // +0x181 in the loop (phase 1)
    uint8_t m_unk182;      // +0x182 in the start animation (phase 0)
    uint8_t m_unk183;      // +0x183 in the end animation (phase 4)
    uint8_t m_unk184;      // +0x184 the hero control's grounded state (host vt+0x30 negated)
    uint8_t m_unk185;      // +0x185 started in the loop (the mana not taken yet)
    uint8_t m_unk186;      // +0x186 the hot spot of the fizzle (ResetRuntime 0xff)
    uint8_t m_unk187;      // +0x187 (ResetRuntime 0; nothing else accesses it)
    uint32_t m_unk188;     // +0x188 (never accessed)
    float m_unk18c;        // +0x18c the time since Start
    float m_fStartTime;    // +0x190 the game clock at Start (ResetRuntime: -1)
    float m_unk194;        // +0x194 the time left before the next ground trail
    uint8_t m_unk198;      // +0x198 steered (the attack phase)
    uint8_t m_unk199;      // +0x199 the impulse started
    uint8_t m_pad19a[2];
    IKSerializable* m_unk19c;  // +0x19c reference (live: CKS08ElementDamage)
    uint8_t m_unk1a0;      // +0x1a0 End's argument after the fizzle
    uint8_t m_pad1a1[3];
    float m_unk1a4;        // +0x1a4 the time the impulse starts at
};
DOTD_ASSERT_SIZE(CKAttackMoveElement, 0x1a8);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk9c, 0x9c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkd8, 0xd8);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unke4, 0xe4);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkf0, 0xf0);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkf3, 0xf3);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkf8, 0xf8);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk11c, 0x11c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk128, 0x128);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_pHost, 0x17c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_bRunning, 0x180);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk186, 0x186);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_fStartTime, 0x190);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk1a4, 0x1a4);
