// CKHkMovableCharacter.h - a hook that walks with the path finder (key 0x3402, vtable 0xb2e760, size 0x318).
// Original unit: CKHkMovableCharacter.cpp (0x59cb80-0x5a7d20, library-TOC code). No XXL2 class. Derives from
// IKHook directly (CKHkMovableCharacter_Create 0x59e080 stores vtable_CKHook, then its own). Fields are ours
// (m_unkXX) except the embedded XXL2 structs. LVL010's townsfolk (9 of them; C2.7).
//
// The update (0x5a23c0) runs a seven-state machine: the table at +0x2c8 holds PS3 pointers to member (descriptor,
// adjust) that k2000/core/Ps3MemberFn.h maps to the native handlers; +0x2c0 points at it, +0x2c4 is the current
// state (0xff none), +0x2c5 the state count. ChooseState (0x5a4800) picks the state from the flags: 6 a hero came
// near (+0x68 bit 14), 5 hit (bit 4, with +0x140 bits 3-5), 4 looking at an entity (bit 3, +0x140 bit 2), 3 a random
// action (bit 0, +0x140 bit 1), 1 on a path (+0x2a0), else 2 (wander) or 0 (stand; +0x140 bit 0).
//
// m_unk68 (runtime flags): bit 0 a random action is due, bit 1 / bit 5 the action draw made / passed, bit 3
// looking at an entity, bit 4 / bit 6 hit, bit 9 fading out, bit 10 hide when not drawn, bit 11 the shadow is on,
// bit 12 the ground contact was updated this frame, bit 14 a hero came near, bit 15 drops a bonus when destroyed,
// bit 16 the bonus is due.
// m_unk140 (loaded properties): bit 0 stands still, bit 1 random actions, bit 2 looks at entities, bits 3-5 can be
// hit, bit 7 avoids blocked cells, bit 10 plays a locomotion animation, bit 11 hidden at start, bits 12-13 the spin
// axis, bit 16 random start time, bit 17 no collision checks, bit 18 starts a sequence near the hero, bit 21 a
// looping sound, bit 22 collision volume.
#pragma once
#include <cstdint>

#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKTime;

class CKHkMovableCharacter : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd0)
    DOTD_DECLARE_FACTORIES(CKHkMovableCharacter)

    CKHkMovableCharacter();  // inlined in 0x0059e080 CKHkMovableCharacter_Create
    ~CKHkMovableCharacter() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005a30f0 CKHkMovableCharacter_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0059e4d8 CKHkMovableCharacter_PostLoad
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x0059e050 CKHkMovableCharacter_vf38
    // vt+0x50 0x0059cbd8 CKHkMovableCharacter_ResetRuntime (the Start).
    void Start() override;
    void Restart() override;  // vt+0x54 0x005a1860 CKHkMovableCharacter_ReinitRuntime
    // vt+0x68 0x0059dd60 CKHkMovableCharacter_OnLevelExit_maybe: the path-finding component's request cancelled.
    void Stop() override { m_PFCpnt.CancelPathRequest(); }  // 0x001e2820
    void Update(IKTime* clock) override;                // vt+0x7c 0x005a23c0 CKHkMovableCharacter_Update
    void VfA0() override;                               // vt+0xa0 0x005a1998 CKHkMovableCharacter_OnActivate
    void VfA4() override;                               // vt+0xa4 0x0059fc60 CKHkMovableCharacter_OnDeactivate
    // vt+0x1c 0x0059e7a8 CKHkMovableCharacter_MessageProc: the 0x4xx messages: 0x498 shows (data 1) or hides the
    // character, 0x496 fades it in or out, 0x49a / 0x49b / 0x49c / 0x49d / 0x497 / 0x499 set its flags, 0x400 / 0x402
    // answer with +0x140 bit 14 (3 without it).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x10 0x0059dfe8 CKHkMovableCharacter_Destroy: the shadow component reference (+0x290) cleared.
    void Destroy() override { m_unk290 = nullptr; }
    // vt+0x3c 0x0059e060 CKHkMovableCharacter_vf3C (SetGameState): disabled (+0x130) when the state id is not 0.
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x40 0x0059dff8 CKHkMovableCharacter_vf40 (GetInfo): 0xc the visibility accessor (0x9cba68 IsVisible_maybe:
    // the node's hidden bit 2 clear), value type 0.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0xb0 0x0059df38 CKHkMovableCharacter_GetComponentByKey_maybe: for 0x486 the shadow ground (+0xd4), registered with
    // the shadow service first when the shadow is on (+0x68 bit 11), there is a shadow component and it is not used yet.
    IKSerializable* GetComponent(uint32_t key) override;
    // vt+0x24 0x59ddb8: IKHook's RecursiveRegistration (inherited). vt+0x70 / +0x78 0x59cc50 / 0x59cc58 and vt+0xb4
    // 0x59cbd0: empty (IKHook's).

    // The state handlers (clock, phase 0 tick / 1 enter / 2 leave, the other state) -> the next state.
    using StateFn = uint8_t (CKHkMovableCharacter::*)(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);  // 0x005a64e8 CKHkMovableCharacter_State0
    uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);  // 0x005a5f00 CKHkMovableCharacter_State2
    uint8_t State3(IKTime* clock, int32_t phase, uint8_t other);  // 0x005a4668 CKHkMovableCharacter_State3
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x005a4ef8 CKHkMovableCharacter_State1 (on a path)
    uint8_t State4(IKTime* clock, int32_t phase, uint8_t other);  // 0x005a5698 CKHkMovableCharacter_State4 (looking)
    uint8_t State5(IKTime* clock, int32_t phase, uint8_t other);  // 0x005a5010 CKHkMovableCharacter_State5 (hit)
    uint8_t State6(IKTime* clock, int32_t phase, uint8_t other);  // 0x005a7458 CKHkMovableCharacter_State6 (a hero near)

    // The walking machinery (C2.8 lvl020-walkers).
    void PushTargetInsideBounds(const CVector3* at);         // 0x0059cc60 CKHkMovableCharacter_PushTargetInsideBounds_maybe
    float DirectionToYaw(const CVector3* direction);         // 0x0059dde0 CKHkMovableCharacter_DirectionToYaw_maybe
    void ProbeGround(CVector3* position, CVector3* normal);  // 0x0059f160 CKHkMovableCharacter_ProbeGround_maybe
    void GetHeadingDirection(CVector3* out);                 // 0x005a02d0 CKHkMovableCharacter_GetHeadingDirection_maybe
    void ResetTargetIfOutOfBounds();                         // 0x005a0498 CKHkMovableCharacter_ResetTargetIfOutOfBounds_maybe
    void ClampToMoveBounds(CVector3* position, CVector3* direction);  // 0x005a0590 CKHkMovableCharacter_ClampToMoveBounds_maybe
    void CheckNavCellBlocked(CVector3* position, CVector3* direction);  // 0x005a0698 ..._CheckNavCellBlocked_maybe
    void CheckBlockingCollision(CVector3* position, CVector3* direction);  // 0x005a08c0 ..._CheckBlockingCollision_maybe
    void ProbeGroundAtTarget(CVector3* position, CVector3* direction, CVector3* up);  // 0x005a0ab0 ..._ProbeGroundAtTarget_maybe
    void PickRandomWanderTarget(const CVector3* at);         // 0x005a0e50 CKHkMovableCharacter_PickRandomWanderTarget_maybe
    uint8_t TurnTowardDirectionFlat(const CVector3* direction);  // 0x005a1b28 ..._TurnTowardDirectionFlat_maybe
    uint8_t TurnTowardDirectionAligned(const CVector3* direction, const CVector3* up);  // 0x005a1f18 ..._Aligned_maybe
    void MoveAlongPath(float speed, float acceleration);     // 0x005a4998 CKHkMovableCharacter_MoveAlongPath_maybe
    uint8_t MoveToWithPathfinding(const CVector3* target, CVector3* position, CVector3* up, IKTime* clock);  // 0x005a6ce8
    uint8_t TurnTowardPoint(const CVector3* target, CVector3* up, IKTime* clock, uint8_t point);  // 0x005a7080

    void UpdateFade(IKTime* clock);         // 0x0059ed48 CKHkMovableCharacter_UpdateFade_maybe
    void ProcessHitContacts();              // 0x0059d870 CKHkMovableCharacter_ProcessHitContacts_maybe
    void UpdateLookAtNearbyEntity();        // 0x0059f5c8 CKHkMovableCharacter_UpdateLookAtNearbyEntity_maybe
    void UpdateInputIcon(int32_t show);     // 0x0059f840 CKHkMovableCharacter_UpdateInputIcon_maybe
    void UpdateRandomActionTimer();         // 0x005a44e8 CKHkMovableCharacter_UpdateRandomActionTimer_maybe
    void UpdateHeroProximity();             // 0x0059fb18 CKHkMovableCharacter_UpdateHeroProximity_maybe
    void UpdateMoveSound();                 // 0x0059d328 CKHkMovableCharacter_UpdateMoveSound_maybe
    void UpdateGroundContact();             // 0x0059efa8 CKHkMovableCharacter_UpdateGroundContact_maybe
    void UpdateLocomotionAnim();            // 0x0059d490 CKHkMovableCharacter_UpdateLocomotionAnim_maybe
    uint8_t ChooseState();                  // 0x005a4800 CKHkMovableCharacter_ChooseState_maybe
    void InitMovementFields();              // 0x0059e1e0 CKHkMovableCharacter_InitMovementFields_maybe
    void InitRuntimeState(uint8_t keepShadow);  // 0x005a12c0 CKHkMovableCharacter_InitRuntimeState_maybe
    void ApplyPoseToNode();                 // 0x0059fe48 CKHkMovableCharacter_ApplyPoseToNode_maybe
    void SetUniformScale(float scale);      // 0x0059f338 CKHkMovableCharacter_SetUniformScale_maybe
    // The state engine's call of state `state` (the table at m_pStateTable).
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other);

    IKTime* m_pClock;                           // +0x20 the last Update's clock (InitMovementFields: null)
    uint8_t m_unk24;                            // +0x24 InitMovementFields 0
    uint8_t m_unk25;                            // +0x25 InitMovementFields 0
    uint8_t m_pad26[2];
    CGroundContactDatasIn m_GContactIn;         // +0x28
    CGroundContactDatasInOut m_GContactInOut;   // +0x38
    uint8_t m_unk64;                            // +0x64 the locomotion animation's index in m_unk138 (0 / 1)
    uint8_t m_unk65;                            // +0x65 1 while standing or wandering, 0 in a random action
    uint8_t m_pad66[2];
    uint32_t m_unk68;                           // +0x68 the runtime flags (above)
    uint16_t m_unk6c;                           // +0x6c InitMovementFields 0xffff
    uint8_t m_pad6e[2];
    IKSerializable* m_unk70;                    // +0x70 the hook whose volume hit this one
    float m_unk74;                              // +0x74 the yaw towards the entity looked at
    float m_unk78;                              // +0x78 the random action timer (seconds)
    float m_unk7c[3];                           // +0x7c a FloatApproach {target, speed, current}: the walk speed
    float m_unk88[3];                           // +0x88 a FloatApproach {target, speed, current}: the yaw
    CVector3 m_unk94;                           // +0x94 the walk target
    float m_unkA0;                              // +0xa0 the turn radius_maybe
    CVector3 m_unkA4;                           // +0xa4 the move bounds' corners (+0x148 < 2)
    CVector3 m_unkB0;                           // +0xb0
    CVector3 m_unkBC;                           // +0xbc
    CVector3 m_unkC8;                           // +0xc8
    // +0xd4 the shadow caster's ground (CKShadowGround: the position, the normal, a word, the used byte +0xf1).
    CVector3 m_shadowPos;                       // +0xd4
    CVector3 m_shadowNormal;                    // +0xe0
    uint32_t m_unkEC;                           // +0xec
    uint8_t m_unkF0;                            // +0xf0 constructor 0
    uint8_t m_unkF1;                            // +0xf1 the shadow is registered (CKShadowGround used byte)
    uint8_t m_padF2[2];
    float m_unkF4;                              // +0xf4 InitMovementFields: rand() / 65535
    float m_unkF8;                              // +0xf8 the fade timer
    float m_unkFC;                              // +0xfc the shadow fade timer (> 0 in, < 0 out)
    uint8_t m_unk100;                           // +0x100 the shadow's full alpha
    uint8_t m_pad101[3];
    float m_unk104;                             // +0x104 State6's timer (seconds; entering 0)
    CVector3 m_unk108;                          // +0x108 the start pose: position
    CVector3 m_unk114;                          // +0x114 at
    CVector3 m_unk120;                          // +0x120 up
    float m_unk12c;                             // +0x12c MoveToWithPathfinding's walk speed (State6 entering: 0)
    uint8_t m_unk130;                           // +0x130 disabled: no update
    uint8_t m_pad131[3];
    IKSerializable* m_unk134;                   // +0x134 the input icon effect (IKFx)
    IKSerializable* m_unk138;                   // +0x138 the animations (+0x04: the animation array)
    IKSerializable* m_unk13c;                   // +0x13c the sound dictionary (CKSoundDictionaryID)
    uint32_t m_unk140;                          // +0x140 the loaded properties (above)
    IKSerializable* m_unk144;                   // +0x144 the collision volume (IKBoundingVolume)
    uint8_t m_unk148;                           // +0x148 read before +0x140; < 2: wanders in the bounds
    uint8_t m_pad149[3];
    CVector3 m_unk14c;                          // +0x14c
    CVector3 m_unk158;                          // +0x158
    CVector3 m_unk164;                          // +0x164 the start position
    float m_unk170;                             // +0x170 the start yaw (radians) / the path distance
    uint8_t m_unk174;                           // +0x174 non-zero: the node keeps its pose
    uint8_t m_pad175[3];
    // +0x178..+0x1ef 30 loaded words (floats), each read and swapped.
    float m_unk178;                             // +0x178 the walk speed (0: stands)
    float m_unk17c;                             // +0x17c the walk acceleration
    float m_unk180;                             // +0x180 the turn speed
    float m_unk184;                             // +0x184 the random action timer: min (seconds)
    float m_unk188;                             // +0x188 max
    float m_unk18c;                             // +0x18c
    float m_unk190;                             // +0x190 the random action's probability
    float m_unk194;                             // +0x194 the random action's duration: min
    float m_unk198;                             // +0x198 max
    float m_unk19c;                             // +0x19c
    float m_unk1a0;                             // +0x1a0
    float m_unk1a4;                             // +0x1a4 the look-at distance
    float m_unk1a8;                             // +0x1a8
    float m_unk1ac;                             // +0x1ac
    float m_unk1b0;                             // +0x1b0 the fade duration
    float m_unk1b4;                             // +0x1b4 the fade's full alpha
    float m_unk1b8;                             // +0x1b8 the spin speed (degrees per second)
    float m_unk1bc;                             // +0x1bc the uniform scale
    float m_unk1c0;                             // +0x1c0 the shadow fade duration
    float m_unk1c4;                             // +0x1c4 the hero distance that sets +0x68 bit 14
    float m_unk1c8[8];                          // +0x1c8..+0x1e7
    float m_unk1e8;                             // +0x1e8 the ground contact's object height
    float m_unk1ec;                             // +0x1ec the ground contact's delta max
    CKPathFindingCpnt m_PFCpnt;                 // +0x1f0 (vtables 0xb12ce8 then 0xb1e4f0 in Create)
    float m_unk268[4];                          // +0x268 the animation speed factors of indices 0..3 (UpdateLocomotionAnim)
    CVector3 m_unk278;                          // +0x278 the move bounds: min
    CVector3 m_unk284;                          // +0x284 max
    IKSerializable* m_unk290;                   // +0x290 the shadow component (CKShadowCpnt: +0x1f the alpha)
    TVector<IKSerializable*, 1> m_vUnk294;      // +0x294 u16-counted references: the entities to look at (nodes)
    IKSerializable* m_unk2a0[3];                // +0x2a0 three single references: the path, its flags, the sequence launcher
    float m_unk2ac;                             // +0x2ac the hero distance that starts the sequence
    IKSerializable* m_unk2b0[3];                // +0x2b0 three single references (after the path-finding Load): the
                                                //        destruction's explosion, the bonus, the input icon data
    uint32_t m_unk2bc;                          // +0x2bc
    uint32_t* m_pStateTable;                    // +0x2c0 PostLoad: the table at +0x2c8
    uint8_t m_unk2c4;                           // +0x2c4 the current state; constructor 0xff
    uint8_t m_unk2c5;                           // +0x2c5 the state count (PostLoad 7); constructor 0xff
    uint8_t m_pad2c6[2];
    uint32_t m_unk2c8[0xe];                     // +0x2c8 the state table: seven (descriptor, adjust) pairs
    CTriggerStarter m_unk300;                   // +0x300
    CTriggerStarter m_unk308;                   // +0x308
    CTriggerStarter m_unk310;                   // +0x310 queued when destroyed
};
DOTD_ASSERT_SIZE(CKHkMovableCharacter, 0x318);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_pClock, 0x20);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_GContactIn, 0x28);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_GContactInOut, 0x38);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_shadowPos, 0xd4);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unkF1, 0xf1);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_PFCpnt, 0x1f0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_vUnk294, 0x294);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2bc, 0x2bc);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_pStateTable, 0x2c0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2c4, 0x2c4);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2c8, 0x2c8);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk300, 0x300);
