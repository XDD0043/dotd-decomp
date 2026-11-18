// CKHkS08ClampGun.h - the clamp gun hook (key 0x2c42, size 0x158). Original unit: CKHkS08ClampGun.cpp.
// No XXL2 class. The fields are named by offset until their use is known. Level use: LVL110 only (four guns: the
// references +0x20 a CNode, +0x24 a CKSoundDictionaryID, +0x38 a CKAACylinder, +0xd4 a CSGHotSpot, +0xd8 the
// CKGrpS08Clamp, +0xe4 / +0xec / +0xf4 CKExplosionFxData, +0xfc / +0x104 CKParticlesEffectFxData).
//
// The run time (port-final F06): two state machines. The machine at +0x120 (Restart's table at +0x128): State0 turns
// the gun towards its preset yaws (+0x98 / +0x9c degrees, alternating), every +0x84 seconds a particle effect (+0xfc)
// and sound 1, and leaves for State1 once the heroes are inside +0x4c (or not all beyond +0x48) and free; State1 takes
// clamps from the clamp group, aims at the heroes' predicted midpoint (a ballistic speed, gravity 30) and, after the
// warm-up +0x90 (particles +0x104 after +0x8c), runs the salvo machine (+0x138: FireSalvoState, Cooldown, idle). The
// gun loses +0x50 by the damage of what hits its cylinder (impact effect +0xe4, sound 3); at 0 it explodes (+0xf4).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKTime;
class IKFx;
struct ContactHistoryNode;

class CKHkS08ClampGun : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c48d0
        return key == 0x2c42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08ClampGun)

    // An element of the +0xb4 vector (a shot of the salvo): OperatorNew(0xc), the three words zeroed, then the file's
    // float, +0x04 = 0 and the byte +0x08 = 0 (0.3, 0.3, 0.1, 0.1, 0.1 in the LVL110 samples).
    struct SElem {
        float m_fUnk0;           // +0x00 read: the delay before the next shot (FireSalvoState)
        IKSerializable* m_unk4;  // +0x04 the clamp (a CKHkS08Clamp) taken from the clamp group (State1's entry)
        uint8_t m_unk8;          // +0x08 the clamp was fired (FireShot); 0x900 from the clamp clears it
        uint8_t m_pad9[3];
    };

    // 0x00487608 CKHkS08ClampGun_Construct (inlined in 0x004882a0 CKHkS08ClampGun_Create): +0x3c = 0,
    // the +0xb4 vector empty (capacity 1, length 0, block 0), +0x125/+0x124/+0x13d/+0x13c = 0xff.
    CKHkS08ClampGun() {
        m_pContactHistory = nullptr;
        m_vUnkB4.m_ui32NbElt = 1;
        m_vUnkB4.m_ui32NbUsedElt = 0;
        m_vUnkB4.m_pBlock = nullptr;
        m_unk125 = 0xff;
        m_unk124 = 0xff;
        m_unk13D = 0xff;
        m_unk13C = 0xff;
    }
    // 0x00487df8 CKHkS08ClampGun_Destructor (0x00487a00 the deleting one): the vector's block freed (the length and the
    // block cleared, the elements are Destroy's), the contact history's nodes back to their pool (ContactHistory_FreeNode),
    // then CKHkActorBase's.
    ~CKHkS08ClampGun() override;
    // vt+0x24 RecursiveRegistration 0x4875e0, vt+0x70 Pause 0x487458, vt+0x78 Resume 0x487430: CKHkActorBase's /
    // IKHook's (inherited here).
    // vt+0x10 0x00487818 CKHkS08ClampGun_Destroy: the base's, then each element of +0xb4 deleted (OperatorDelete_Bridge;
    // the block stays for the destructor).
    void Destroy() override {
        CKHkActorBase::Destroy();
        for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) delete m_vUnkB4.m_pBlock[i];
    }
    // vt+0x38 0x004873f0 CKHkS08ClampGun_SetDefaultState: the base's (empty), +0x11b = +0x11a, +0x11f = +0x11e.
    void SetDefaultState(int32_t flag) override {
        CKHkActorBase::SetDefaultState(flag);  // 0x3f72a0
        m_unk11B = m_unk11A;
        m_unk11F = m_unk11E;
    }
    // vt+0xc8 0x004865c0 CKHkS08ClampGun_vfC8 (ApplyStatePreset): state != 0: +0x11f = +0x11c, +0x11b = +0x118; else
    // +0x11f = +0x11d, +0x11b = +0x119.
    void ApplyStatePreset(int32_t state) override {
        if (state != 0) {
            m_unk11F = m_unk11C;
            m_unk11B = m_unk118;
        } else {
            m_unk11F = m_unk11D;
            m_unk11B = m_unk119;
        }
    }
    // vt+0x30 0x00488490 CKHkS08ClampGun_PostLoad: the base's; the cylinder +0x38 becomes this hook's (owner type 1, owner,
    // info bit 7), radius +0x40, half height +0x44 / 2, its bounding radius sqrt(h^2 + r^2) (once before the height).
    int32_t PostLoad(int32_t type) override;
    // vt+0x40 0x004874d8 CKHkS08ClampGun_GetInfo: value 0x96 (GetTriggerProp96 0x4866c8: +0x50 <= 0, NaN not, a byte).
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00489690 CKHkS08ClampGun_Load

    // vt+0xcc 0x004866f0 CKHkS08ClampGun_vfCC: +0x11b = `enabled`.
    void SetEnabled(int32_t enabled) override { m_unk11B = static_cast<uint8_t>(enabled); }
    // vt+0xd0 0x004877d0 CKHkS08ClampGun_vfD0: the hidden bit (+0x10 bit 2) of the node (+0x1c) and of +0x20 = !visible
    // (the argument xor 1, shifted, not masked).
    void SetVisible(int32_t visible) override;

    // port-final F06: the run time.
    // vt+0x1c 0x00488558 CKHkS08ClampGun_MessageProc: 0x900 (from a clamp: the data is the clamp) clears the fired byte of
    // that clamp's element; 0x996 sends every fired clamp that does not hold the heroes (not in state 2) back to the
    // pool with its sound 1 and FX. The answer is the actor base's (3 / 2 kept, 0, else 1).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x50 0x00487480 CKHkS08ClampGun_Start: the base's (empty), then Restart (vt+0x54).
    void Start() override;
    // vt+0x54 0x0048a1c0 CKHkS08ClampGun_Restart: both state tables, State0 entered (no clock), the salvo machine in
    // its idle state 2; the fired bytes cleared; woken in the game manager's context group; +0x50 = +0x54; a gun not
    // destroyed (+0x0c bit 2 clear) is shown, its modelling matrix ortho-normalised, +0x70 = 0, its cylinder registered
    // when +0x11f, else the cylinder is unregistered; the two particle effects forgotten, every clamp back to the pool,
    // and (not destroyed) the hidden bits = !+0x11f.
    void Restart() override;
    // vt+0x68 0x004880d0 CKHkS08ClampGun_Stop: the base's (empty), every clamp back to the pool.
    void Stop() override;
    // vt+0x7c 0x0048a560 CKHkS08ClampGun_Update: while +0x11b: the two particle effects stopped and released, the
    // machine +0x120, the contacts; at +0x50 <= 0 the gun is destroyed (the cylinder unregistered, sound 4 stopped, both
    // nodes hidden, put to sleep in the game manager's context group, the explosion +0xf4 at the node +0x20).
    void Update(IKTime* clock) override;
    // vt+0xa0 0x00487ac0 CKHkS08ClampGun_OnActivate: +0x74 = the node's modelling at; the cylinder under the node; the
    // node's modelling matrix the identity (flags 0x20003), +0x70 = 0; both nodes shown, the cylinder registered when
    // +0x11f, the particle effects forgotten, the hidden bits = !+0x11f. (The actor base's OnActivate is not called.)
    void VfA0() override;
    // vt+0xa4 0x004878f8 CKHkS08ClampGun_OnDeactivate: the cylinder out of the node, the two particle effects stopped
    // and released, the cylinder unregistered. (The actor base's OnDeactivate is not called.)
    void VfA4() override;

    // The state engine (handler: clock, phase 0 tick / 1 enter / 2 leave, the other state -> the next state).
    using StateFn = uint8_t (CKHkS08ClampGun::*)(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    // The machine +0x120 / +0x124 (two states, the table +0x128).
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);  // 0x0048b680 CKHkS08ClampGun_SM128_State0
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x0048bc30 CKHkS08ClampGun_SM128_State1
    // The salvo machine +0x138 / +0x13c (three states, the table +0x140).
    uint8_t SalvoState0(IKTime* clock, int32_t phase, uint8_t other);  // 0x0048b4f8 CKHkS08ClampGun_FireSalvoState_maybe
    uint8_t SalvoState1(IKTime* clock, int32_t phase, uint8_t other);  // 0x00487898 CKHkS08ClampGun_SM140_State1_Cooldown_maybe
    // 0x009c4938 KStub_ReturnArg4_9c4938 (the salvo machine's idle state 2): the other state.
    uint8_t SalvoState2(IKTime* /*clock*/, int32_t /*phase*/, uint8_t other) { return other; }
    // The machines' inlined switch: the current state left (phase 2, other `leaveOther`), `next` entered (phase 1, other
    // the old state; none when `next` is 0xff); and one tick (phase 0) with the switch to the state it returns.
    void SwitchState(uint8_t* state, const uint32_t* table, uint8_t next, IKTime* clock, uint8_t leaveOther);
    void RunStateMachine(uint8_t* state, const uint32_t* table, IKTime* clock);

    // 0x00486cc0 CKHkS08ClampGun_UpdateTurnSound_maybe: sound 4 loops at the node +0x20 while the turn step +0x6c is not
    // 0 (stopped when it is); `click` plays sound 5 there once.
    void UpdateTurnSound(uint8_t click);
    // 0x00486e60 CKHkS08ClampGun_TickTimerAndPlayImpactFx_maybe: +0x50 loses `damage` (an integer, as a float); at 0 or
    // less it is 0 and nothing else; else the impact effect (+0xe4) at `point` and sound 3 at the node.
    void TakeDamage(uint32_t damage, const CVector3* point);
    // 0x004871b0 CKHkS08ClampGun_ProcessContacts_maybe: the cylinder's collisions with volumes of property 8 that have a
    // contact set, once per contact (ContactHistory, -1000 / -1000): a damage (+0x1c) with +0x08 0 hits the gun at the
    // contact point; the history aged.
    void ProcessContacts(IKTime* clock);
    // 0x00488330 CKHkS08ClampGun_ComputeBallisticSpeed_maybe: the launch speed at the pitch `angle` from `from` to `to`
    // under gravity 30 (15 = g / 2): sqrt(d^2 / cos^2 * 15 / (tan d - dy)), 0 when not positive.
    float ComputeBallisticSpeed(float angle, const CVector3* from, const CVector3* to);
    // 0x00488738 CKHkS08ClampGun_AimAtHeroesMidpoint_maybe: the pitch towards the heroes' middle (the flat direction from
    // the node +0x20 raised by 0.5, against the flat one), the flight time there, the heroes' predicted middle +0x2c and
    // the launch speed +0xd0 to it.
    void AimAtHeroesMidpoint();
    // 0x00488b10 CKHkS08ClampGun_RotateTowardPresetYaw_maybe: the gun (node +0x1c) turns at +0xa8 towards the preset
    // yaw +0x98 (side 0) or -+0x9c (side 1) degrees, switching side on arrival; the turn sounds.
    void RotateTowardPresetYaw(IKTime* clock);
    // 0x00488f98 CKHkS08ClampGun_RotateTowardTarget_maybe: the gun turns at +0x68 towards the aim point +0x2c (its yaw
    // taken relative to the node +0x20's); the turn sound.
    void RotateTowardTarget(IKTime* clock);
    // 0x0048ab98 CKHkS08ClampGun_FireShot_maybe: element `index`'s clamp launched from the hot spot +0xd4 along its at
    // axis at +0xd0 with two random spreads of +0x10c degrees (2 Rand_Int draws), gravity -30 y (the speed +0x114 when
    // the heroes are all inside +0x4c); sound 0 and the shot effect (+0xec, kept at +0xe8). 0 without a clamp or speed.
    uint8_t FireShot(uint32_t index);
    // The particle effect State0 / State1 start (+0xfc / +0x104 attached to the node +0x20, 2 above it): the inlined
    // CKSrvFx::AcquireFx with the data set up first.
    IKFx* StartParticles(IKSerializable* data, IKFx* current);

    IKSerializable* m_pUnk20;   // +0x20 a CNode (the gun's base; the turret +0x1c is under it)
    IKSerializable* m_pUnk24;   // +0x24 the CKSoundDictionaryID
    IKSerializable* m_pUnk28;   // +0x28 (null in LVL110)
    CVector3 m_vAimPoint;       // +0x2c AimAtHeroesMidpoint: the heroes' predicted middle
    IKSerializable* m_pUnk38;   // +0x38 the CKAACylinder; PostLoad configures it from +0x40/+0x44
    ContactHistoryNode* m_pContactHistory;  // +0x3c constructor 0: the contacts (ContactHistory)
    float m_fUnk40;             // +0x40
    float m_fUnk44;             // +0x44
    float m_fUnk48;             // +0x48 the heroes all beyond it: State0 keeps turning (20)
    float m_fUnk4C;             // +0x4c the heroes all inside it: State0 leaves; FireShot uses +0x114 (4)
    float m_fUnk50;             // +0x50 the hit points (Restart: +0x54); GetTriggerProp96: not above 0
    float m_fUnk54;             // +0x54 (100)
    float m_fUnk58;             // +0x58 the salvo cooldown (1)
    uint8_t m_unk5C;
    uint8_t m_unk5D;            // +0x5d
    uint8_t m_bSalvoWait;       // +0x5e FireSalvoState: a fired clamp is still out
    uint8_t m_pad5F;
    float m_fUnk60;             // +0x60 the aim turn speed (1.0472 = pi/3 in the samples); State1's entry: +0x68
    float m_afAimTurn[3];       // +0x64 FloatApproach {delta, speed, step} of RotateTowardTarget
    float m_fYaw;               // +0x70 the turret's yaw (OnActivate / Restart: 0)
    CVector3 m_vInitialAt;      // +0x74 OnActivate: the node's modelling at
    float m_fFireTimer;         // +0x80 State0: the time since the last particle effect
    float m_fUnk84;             // +0x84 State0: its period (0.5)
    float m_fWarmTimer;         // +0x88 State1: the time towards +0x8c
    float m_fUnk8C;             // +0x8c (0.2)
    float m_fUnk90;             // +0x90 State1's warm-up (1.5)
    float m_fStateTime;         // +0x94 State1: the time in the state
    float m_fUnk98;             // +0x98 the preset yaw of side 0, degrees (25)
    float m_fUnk9C;             // +0x9c the preset yaw of side 1, negated degrees (25)
    float m_fUnkA0;             // +0xa0 the preset turn speed (0.5236 = pi/6 in the samples); State0's entry: +0xa8
    float m_afPresetTurn[3];    // +0xa4 FloatApproach {delta, speed, step} of RotateTowardPresetYaw
    uint32_t m_ui32PresetSide;  // +0xb0 RotateTowardPresetYaw: 0 / 1 (State0's entry: 0)
    TVector<SElem*, 1> m_vUnkB4;  // +0xb4
    uint32_t m_ui32ShotIndex;   // +0xc0 FireSalvoState: the element fired last
    float m_fShotTimer;         // +0xc4 FireSalvoState: the time since that shot
    float m_fCooldownTimer;     // +0xc8 the salvo machine's state 1
    uint32_t m_unkCC;
    float m_fShotSpeed;         // +0xd0 AimAtHeroesMidpoint: the launch speed (FireShot: 0 fires nothing)
    IKSerializable* m_pUnkD4;   // +0xd4 the CSGHotSpot the clamps leave from
    IKSerializable* m_pUnkD8;   // +0xd8 the CKGrpS08Clamp
    CTriggerStarter m_unkDC;    // +0xdc
    IKSerializable* m_pUnkE4;   // +0xe4 CKExplosionFxData: the impact (TakeDamage)
    IKFx* m_pShotFx;            // +0xe8 FireShot: the shot effect of +0xec (released at once)
    IKSerializable* m_pUnkEC;   // +0xec CKExplosionFxData: the shot
    IKFx* m_pDestroyFx;         // +0xf0 Update: the explosion of +0xf4 (released at once)
    IKSerializable* m_pUnkF4;   // +0xf4 CKExplosionFxData: the destruction
    uint32_t m_unkF8;
    IKSerializable* m_pUnkFC;   // +0xfc CKParticlesEffectFxData (State0)
    IKFx* m_pIdleFx;            // +0x100 State0's particle effect (Update stops and releases it)
    IKSerializable* m_pUnk104;  // +0x104 CKParticlesEffectFxData (State1)
    IKFx* m_pWarmFx;            // +0x108 State1's particle effect (Update stops and releases it)
    float m_fUnk10C;            // +0x10c FireShot: the spread, degrees (15)
    uint32_t m_unk110;          // +0x110 (0 in every sample)
    float m_fUnk114;            // +0x114 FireShot: the speed when the heroes are all inside +0x4c (30)
    uint8_t m_unk118;           // +0x118
    uint8_t m_unk119;           // +0x119
    uint8_t m_unk11A;           // +0x11a
    uint8_t m_unk11B;           // +0x11b the gun runs (Update)
    uint8_t m_unk11C;           // +0x11c
    uint8_t m_unk11D;           // +0x11d
    uint8_t m_unk11E;           // +0x11e
    uint8_t m_unk11F;           // +0x11f the gun is shown and its cylinder registered
    uint32_t* m_pStateTable;    // +0x120 Restart: m_aStateTable
    uint8_t m_unk124;           // +0x124 constructor 0xff: the state
    uint8_t m_unk125;           // +0x125 constructor 0xff: the state count (Restart: 2)
    uint8_t m_pad126[2];
    uint32_t m_aStateTable[4];  // +0x128 Restart: State0 0xbc3420, State1 0xbc3428
    uint32_t* m_pSalvoTable;    // +0x138 Restart: m_aSalvoTable
    uint8_t m_unk13C;           // +0x13c constructor 0xff: the salvo state
    uint8_t m_unk13D;           // +0x13d constructor 0xff: the salvo state count (Restart: 3)
    uint8_t m_pad13E[2];
    uint32_t m_aSalvoTable[6];  // +0x140 Restart: 0xbc3418, 0xbc31e8, 0xbc2f60
};
DOTD_ASSERT_SIZE(CKHkS08ClampGun::SElem, 0xc);
DOTD_ASSERT_SIZE(CKHkS08ClampGun, 0x158);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_vAimPoint, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pContactHistory, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk5D, 0x5d);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_bSalvoWait, 0x5e);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_afAimTurn, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fYaw, 0x70);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_vInitialAt, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fFireTimer, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fWarmTimer, 0x88);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fStateTime, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_afPresetTurn, 0xa4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_ui32PresetSide, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_vUnkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_ui32ShotIndex, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fCooldownTimer, 0xc8);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fShotSpeed, 0xd0);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pShotFx, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pDestroyFx, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pIdleFx, 0x100);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pUnk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pWarmFx, 0x108);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_fUnk10C, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk11C, 0x11c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pStateTable, 0x120);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_aStateTable, 0x128);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_pSalvoTable, 0x138);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_unk13C, 0x13c);
DOTD_ASSERT_OFFSET(CKHkS08ClampGun, m_aSalvoTable, 0x140);
