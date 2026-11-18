// CKHkS08Clamp.h - a clamp hook (key 0x2c82, size 0x130). Original unit:
// CKHkS08Clamp.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/CKHkActorBase.h"

class IKTime;
struct ContactHistoryNode;

class CKHkS08Clamp : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb2)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4940
        return key == 0x2c82 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08Clamp)

    // 0x0048d2b8 CKHkS08Clamp_Construct (inlined in 0x0048e240 CKHkS08Clamp_Create): +0x30 = 0, +0xd8 = 0,
    // +0xc4 = 3, +0xb0 = 0, +0xb4 = -1, +0x10d/+0x10c = 0xff. (+0xb0..+0xdb is a CGroundContactDatasInOut, its
    // constructor's defaults: UpdateGroundImpact probes the ground with it.)
    CKHkS08Clamp() {
        m_pContactHistory = nullptr;
        m_ui8NbStates = 0xff;
        m_ui8State = 0xff;
    }
    // vt+0x24 0x0048d248 CKHkS08Clamp_RecursiveRegistration: CKHkActorBase's (inherited here).
    // vt+0x94 0x0048d7e0 / vt+0x98 0x0048d7e8 CKHkS08Clamp_vf94 / vf98: empty, as IKLife's (inherited here).
    // 0x0048d768 CKHkS08Clamp_Destructor (0x0048d6e0 the deleting one): the contact history's nodes back to their pool
    // (FreeListPool 0x00ceaa20's 0x18-byte free list +0x54 = 0x00ceaa74: ContactHistory_FreeNode), the list cleared, then
    // CKHkActorBase's.
    ~CKHkS08Clamp() override;
    // vt+0x68 0x00491338 CKHkS08Clamp_Stop: CKHkActorBase's (empty), the collision volume out of its parent node (vt+0x78),
    // the trail off (SetTrailActive 0), the volume disabled in the collision service.
    void Stop() override;
    // vt+0x10 0x0048d270 CKHkS08Clamp_Destroy: CKHkActorBase's (empty), the two matrices destroyed (RwMatrixDestroy).
    void Destroy() override {
        RwMatrixDestroy_Thunk(m_pUnk3C);
        RwMatrixDestroy_Thunk(m_pUnk40);
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0048ee18 CKHkS08Clamp_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0048dbc0 CKHkS08Clamp_PostLoad
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x0048fe08 CKHkS08Clamp_MessageProc
    // vt+0x38 0x0048cbb0 CKHkS08Clamp_SetDefaultState: the byte at +0x20 cleared.
    void SetDefaultState(int32_t /*flag*/) override { m_unk20 &= 0x00ffffffu; }
    // vt+0xc8 0x0048cbc0 CKHkS08Clamp_vfC8 (the actors' ApplyStatePreset slot): the byte at +0x20 = `state` (stb).
    void ApplyStatePreset(int32_t state) override { m_unk20 = (m_unk20 & 0x00ffffffu) | (static_cast<uint32_t>(state & 0xff) << 24); }
    void Start() override;                  // vt+0x50 0x004913d8 CKHkS08Clamp_Start
    void Restart() override;                // vt+0x54 0x00490210 CKHkS08Clamp_Restart
    void Update(IKTime* clock) override;    // vt+0x7c 0x0048f8d8 CKHkS08Clamp_Update
    void VfA0() override;                   // vt+0xa0 0x0048d648 CKHkS08Clamp_OnActivate
    // vt+0x70 / +0x78 0x0048d1a8 / 0x0048d180 CKHkS08Clamp_Pause / Resume: the empty stubs 0x3f6e58 / 0x3f6e60.

    // The state machine (the table at +0x108: four (descriptor, adjust) pairs at +0x110; the current state +0x10c).
    // 1 waits for the heroes' link to cross the clamp, 2 holds the heroes (the hero group's external lock), 3 is off.
    using StateFn = uint8_t (CKHkS08Clamp::*)(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x0048df08 CKHkS08Clamp_State1
    uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);  // 0x0048e828 CKHkS08Clamp_State2
    uint8_t State3(IKTime* clock, int32_t phase, uint8_t other);  // 0x0048d580 CKHkS08Clamp_State3_Inactive_maybe
    // 0x0048cd00 CKHkS08Clamp_GetDistSqToHeroLink_maybe: whether the clamp is on the link between the two heroes (the
    // segment from hero 0 to hero 1, the clamp taken at hero 0's height, within +0xe4 of it).
    uint8_t IsOnHeroLink();
    // The State1 / State2 call of CKHkS08Clamp_SpawnFx_maybe 0x491938 (CKGrpS08Clamp::SpawnClampFx).
    void SpawnFx();
    // 0x004903f0 CKHkS08Clamp_UpdateCollisionVolumesFromBones_maybe: the trail +0xf8 (a CTrailNodeFx, not a collision
    // volume) ribbon 0 switched off and laid out again (CTrailNodeFx_SetRibbonActive_maybe inlined); with `active` its
    // anchors (mode 1) are put on the clamp's node, +-0.5 * +0xfc along the LTM's up axis, and the ribbon switched on.
    void SetTrailActive(int32_t active);
    // 0x0048cef8 CKHkS08Clamp_UpdateRotationBlend_maybe: a launched clamp's node blended from the matrix +0x40 to +0x3c
    // over +0x44 seconds (+0x48 the time; position lerp, quaternion nlerp); at the end the node takes +0x3c.
    void UpdateRotationBlend(IKTime* clock);
    // 0x0048d9c8 CKHkS08Clamp_ProcessContacts_maybe: the volume's collisions against volumes of property 8 with a contact
    // set, once per contact (ContactHistory, -1000 / -1000): in state 0 OnContactHit, in state 2 +0xe8 set; the history aged.
    void ProcessContacts(IKTime* clock);
    // 0x0048d7f0 CKHkS08Clamp_OnContactHit_maybe: sound 0 at the node; the velocity +0x64 away from `owner` in x / z,
    // raised by tan(+0x8c degrees), of length +0x90.
    void OnContactHit(IKSerializable* owner);

    // 0x00490cc8 CKHkS08Clamp_State0: a launched clamp flying. Entering: +0x71 cleared, +0x70 set, the trail on. Each
    // frame: the contacts; the velocity +0x64 gains +0x58 * dt, the position +0x4c = the node's + velocity * dt; the node
    // spins about +0x80 by +0x7c degrees a second (the angle wrapped into [0, 2pi) and given in degrees); the ground and
    // walls (UpdateGroundImpact); the node moved to +0x4c; the trail's ribbon 0 laid along the node's up axis. Once the
    // flight ends (+0x70 clear): not landed (+0x71 clear) the matrices +0x3c (the node's yaw only, at its position) and
    // +0x40 (the node's matrix) for State1's blend, state 1; landed, a node not drawn this frame (+0x16 against the render
    // frame counter) sends +0x28 0x900 and goes off (3).
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);
    // 0x0048e2c8 CKHkS08Clamp_UpdateGroundImpact_maybe: the ground under +0x4c (reach 0, height +0xdc, more when falling;
    // masks 1, 2): status 3, or a ground of property 0x200 not of engine flag 2, lands the clamp (+0x70 clear, +0x71 set);
    // status 1 / 2 bounce: sound 3, the position on the ground, the velocity reflected on the normal and scaled by +0x74
    // while slower than +0x78 (else, or unchanged, stopped: +0x70 clear). Then the walls (the cylinder +0xe0 / +0xdc swept
    // from the node to +0x4c): slid, the slide added and the velocity reflected the same way; pushed out, the push added.
    // On ground (not landed, status 1 / 2) the surface FX (CKS08GameManager_SpawnSurfaceFx, mode 1) at the projection.
    void UpdateGroundImpact(IKTime* clock);
    // 0x0048f330 CKHkS08Clamp_LaunchRandomDirection_maybe: the spin axis +0x80 from two random angles a, b in [0, 2pi]
    // (2 rand draws): (cos a cos b, sin a, cos a sin b).
    void LaunchRandomDirection();
    // 0x00490008 CKHkS08Clamp_Launch_maybe (CKHkS08ClampGun_FireShot_maybe's): the position (+0x4c and the node), the
    // velocity +0x64, the acceleration +0x58, a random spin axis, then state 0. Returns 1.
    uint8_t Launch(const CVector3* position, const CVector3* velocity, const CVector3* acceleration);
    // 0x0048ddc8 CKHkS08Clamp_PlaySound1AndSpawnFx_maybe (the clamp gun's): in state 0 or 1, sound 1 at the node and the
    // group's FX.
    void PlaySound1AndSpawnFx();
    // 0x0048fb80 CKHkS08Clamp_EnterState1_maybe (CKGrpS08Clamp_MessageProc's): +0xf4 set, then state 1.
    void EnterState1();
    // 0x0048fcc8 CKHkS08Clamp_EnterState3_maybe (CKHkS08ClampGun_ReturnClampToPool_maybe's): state 3.
    void EnterState3();
    // The state change these share (the current state left towards `next`, `next` entered; no clock).
    void ChangeState(uint8_t next);

    uint32_t m_unk20;          // +0x20 runtime (PostLoad clears the byte at +0x20)
    IKSerializable* m_pUnk24;  // +0x24 runtime (PostLoad: the clamp group, CKGrpS08Meca +0x40)
    IKSerializable* m_pUnk28;  // +0x28 runtime: a launched clamp's target (the clamp gun), sent 0x900 when it ends
    IKSerializable* m_pUnk2C;  // +0x2c
    ContactHistoryNode* m_pContactHistory;  // +0x30 constructor 0: the contacts of ProcessContacts (ContactHistory)
    float m_fStateTime;        // +0x34 State1: the time in the state (entering clears it)
    float m_fUnk38;            // +0x38 (0.7 in the LVL010 samples)
    CMatrix34* m_pUnk3C;       // +0x3c PostLoad: RwMatrixCreate (the second)
    CMatrix34* m_pUnk40;       // +0x40 PostLoad: RwMatrixCreate (the first)
    float m_fUnk44;            // +0x44
    float m_fBlendTime;        // +0x48 State1 entering clears it (stw 0); UpdateRotationBlend's time
    CVector3 m_vUnk4c;         // +0x4c Start: the null vector
    CVector3 m_vUnk58;         // +0x58 Start: the null vector
    CVector3 m_vUnk64;         // +0x64 Start: the null vector; OnContactHit: the velocity
    uint8_t m_bUnk70;          // +0x70 State0 entering: 1 (flying); cleared when the flight ends (UpdateGroundImpact)
    uint8_t m_bUnk71;          // +0x71 State0 entering: 0; UpdateGroundImpact: 1 when the clamp landed for good
    uint8_t m_pad72[2];
    float m_fUnk74;            // +0x74
    float m_fUnk78;            // +0x78
    float m_fUnk7C;            // +0x7c
    CVector3 m_vSpinAxis;      // +0x80 LaunchRandomDirection; State0 spins the node about it
    float m_fUnk8C;            // +0x8c
    float m_fUnk90;            // +0x90
    float m_fUnk94;            // +0x94
    CVector3 m_vHoldStart;     // +0x98 State2 entering: the heroes' middle
    CVector3 m_vHoldPosition;  // +0xa4 State2: the tether's middle, moving toward the clamp at +0x94 a frame
    CGroundContactDatasInOut m_gcInOut;  // +0xb0 UpdateGroundImpact's ground contact (constructor: its defaults)
    float m_fUnkDC;            // +0xdc
    float m_fUnkE0;            // +0xe0
    float m_fUnkE4;            // +0xe4
    uint8_t m_bUnkE8;          // +0xe8 State2 entering clears it (set: State2 sends 0x900 and ends)
    uint8_t m_padE9[3];
    IKSerializable* m_pUnkEC;  // +0xec
    uint32_t m_unkF0;          // +0xf0 passed to CKHkS08Clamp_SpawnFx_maybe, which never reads it
    uint8_t m_bUnkF4;          // +0xf4 Start clears it
    uint8_t m_padF5[3];
    IKSerializable* m_pUnkF8;  // +0xf8
    float m_fUnkFC;            // +0xfc
    uint32_t m_unk100;         // +0x100
    uint8_t m_unk104;          // +0x104
    uint8_t m_unk105[3];
    uint32_t* m_pStateTable;   // +0x108 Start: m_aStateTable
    uint8_t m_ui8State;        // +0x10c constructor 0xff
    uint8_t m_ui8NbStates;     // +0x10d constructor 0xff; Start: 4
    uint8_t m_pad10e[2];
    uint32_t m_aStateTable[8]; // +0x110 Start: the states' (descriptor, 0) pairs
};
DOTD_ASSERT_SIZE(CKHkS08Clamp, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pContactHistory, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fBlendTime, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_vUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_gcInOut, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_vSpinAxis, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_bUnk71, 0x71);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_ui8State, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pStateTable, 0x108);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_aStateTable, 0x110);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_vHoldPosition, 0xa4);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_bUnkF4, 0xf4);
