// CKHkS08Sparx.h - Sparx, the hero's dragonfly companion (key 0x3282, vtable 0xb24be8, size 0xd4). Original
// unit: CKHkS08Sparx.cpp (0x3f4108-0x3f6dc0). Derived straight from IKHook (IsKindOf: 0x2 IKHook, 0x2fe IKLife,
// 0x3fe IKUpdatable, 0xc IKSerializable). No XXL2 class. Field names: the Ghidra struct (CKHkS08Sparx).
//
// Sparx flies around the focused hero (a random point picked around it, steered to with a turn rate and an
// acceleration) unless a linked beacon (CKKLBCharacterSparx, +0xb8) leads it: then it follows a move updater
// (+0xc0) or steers to the beacon's goal (+0x58 / +0x64).
#pragma once
#include <cstdint>
#include <cstring>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"

class IKTime;

class CKHkS08Sparx : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xca)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0b18
        return key == 0x3282 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08Sparx)

    // 0x003f4c28 CreateCKHkS08Sparx (inlined constructor, the same stores as the dead 0x3f4158
    // CKHkS08Sparx_Construct): the IKLife/IKHook defaults and the ground-contact pair at +0x7c/+0x8c.
    CKHkS08Sparx() {}
    // 0x003f4dc8 CKHkS08Sparx_Destructor / 0x003f6d78 CKHkS08Sparx_DeletingDestructor: the vtables of the IKHook chain
    // put back (and the memory freed); nothing of the Sparx's own.
    ~CKHkS08Sparx() override {}

    void Destroy() override;                            // vt+0x10 0x003f45e8 CKHkS08Sparx_Destroy
    // vt+0x1c 0x003f4a60 CKHkS08Sparx_MessageProc: 0 (handled) for message 0x496, 1 for every other one.
    int32_t MessageProc(uint16_t message, void* /*data*/) override { return message != 0x496 ? 1 : 0; }
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x003f45c0 CKHkS08Sparx_RecursiveRegistration
    // vt+0x28 0x003f4598 CKHkS08Sparx_Save: IKHook_Save 0x198d8 (its KStub_Return1_19ce8 call writes nothing), then 1.
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f6860 CKHkS08Sparx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003f4540 CKHkS08Sparx_PostLoad
    void SetDefaultState(int32_t /*flag*/) override {}  // vt+0x38 0x003f4a70 CKHkS08Sparx_SetDefaultState (empty)
    // vt+0x3c 0x003f4a78 CKHkS08Sparx_SetGameState / vt+0x40 0x003f4a58 CKHkS08Sparx_GetInfo: 1.
    int32_t SetGameState(const SApplyGameState* /*state*/) override { return 1; }
    int32_t GetInfo(struct IKInfo* /*info*/, int32_t /*request*/) override { return 1; }
    void Start() override;  // vt+0x50 0x003f67e8 CKHkS08Sparx_Start (C2.2)
    void Restart() override;  // vt+0x54 0x003f66e8 CKHkS08Sparx_Restart
    void Stop() override {}    // vt+0x68 0x003f4250 CKHkS08Sparx_Stop (empty)
    void Pause() override {}   // vt+0x70 0x003f4258 CKHkS08Sparx_Pause (empty)
    void Resume() override {}  // vt+0x78 0x003f4260 CKHkS08Sparx_Resume (empty)
    void Update(IKTime* frameClock) override;  // vt+0x7c 0x003f5da8 UpdateCKHkS08Sparx
    void VfA0() override;  // vt+0xa0 0x003f5488 CKHkS08Sparx_OnActivate
    void VfA4() override;  // vt+0xa4 0x003f4a80 CKHkS08Sparx_OnDeactivate

    // 0x003f46b0 CKHkS08Sparx_SetDirectionVec_maybe: the goal direction (+0x64..+0x6c) the linked beacon gives.
    void SetDirectionVec(const float* direction) {
        std::memcpy(&m_v3GoalDir.x, &direction[0], 4);
        std::memcpy(&m_v3GoalDir.z, &direction[2], 4);
        std::memcpy(&m_v3GoalDir.y, &direction[1], 4);
    }
    // 0x003f4268 CKHkS08Sparx_SetTarget_maybe: a current target that answers message 0x940 (the Sparx as data) keeps
    // the Sparx (0); otherwise `beacon` becomes the target, +0x54 bit 4 is set and 1.
    uint8_t SetTarget(IKSerializable* beacon);
    // 0x003f47f8 CKHkS08Sparx_ResetMoveTargetToCurrentPosition_maybe: the goal at the node's position, the null
    // direction, the default speed (-1).
    void ResetMoveTargetToCurrentPosition();
    // 0x003f4850 CKHkS08Sparx_SetMoveGoalPosDirFloat70_maybe: the goal `position` / `direction` / `speed` (-1: the
    // default +0x2c), +0x54 bit 4 (reached) cleared. The callers pass a fifth word the body never reads.
    void SetMoveGoal(const CVector3* position, const CVector3* direction, float speed);
    // 0x003f48a8 CKHkS08Sparx_ClearTargetIfCurrentAndPlayAnim_maybe: when `beacon` is the target (+0xb8), the target
    // cleared, the node plays the dictionary's first animation from 0 and +0x54 bit 2 is set.
    void ClearTargetIfCurrentAndPlayAnim(IKSerializable* beacon);
    // 0x003f4318 CKHkS08Sparx_StopMoveUpdaterIfCurrent_maybe: when `updater` drives the Sparx (+0xc0), it is stopped and
    // forgotten.
    void StopMoveUpdaterIfCurrent(class CKMoveCpntUpdater* updater);
    // 0x003f4938 CKHkS08Sparx_StartMoveUpdater_maybe: without an updater driving the Sparx, `updater` starts driving it
    // from the node's modelling matrix (copied whole to +0xc4).
    void StartMoveUpdater(class CKMoveCpntUpdater* updater);
    // 0x003f4cc0 CKHkS08Sparx_SetPositionAndDirection_maybe: placed (+0x54 bit 0), the goal at `position` facing
    // `direction`, the node moved there and turned along it (Y up), +0xc8 = `direction`.
    void SetPositionAndDirection(const CVector3* position, const CVector3* direction);
    // 0x003f4de8 CKHkS08Sparx_PickRandomPointAround_maybe: three Rand_Int draws (an angle in -pi..pi, a radius between
    // +0x3c and +0x40, a height between +0x44 and +0x48), then up to 4 x 8 + 4 candidate points around `center` (the
    // angle turned by 45 degrees a step, the radius growing by an eighth of the band a ring and wrapping into it)
    // until one is at least 2 away from the node in x / z and finds ground below (GroundProbePoints into +0x7c /
    // +0x8c); else `center` raised by +0x44.
    CVector3 PickRandomPointAround(const CVector3* center);
    // 0x003f52d0 CKHkS08Sparx_PlaceNearFocusedHero_maybe: with a focused hero, at a random point around it (placed:
    // +0x54 bit 0) facing the hero's direction (+0x540); without one at the null vector facing the Z axis. The goal
    // there, +0xc8 = the facing, +0x54 bit 2 (the node animates) set.
    void PlaceNearFocusedHero();
    // 0x003f5568 CKHkS08Sparx_SteerTowardTarget_maybe: `direction` turned towards `goal` (slerp at +0x34 degrees a
    // second) and `position` advanced along it at +0x74, which accelerates / brakes by +0x38 towards the wanted
    // speed (slower in sharp turns, braking near the goal, the hero's speed added without a target).
    void SteerTowardTarget(float dt, CVector3* position, CVector3* direction, const CVector3* goal);
    // 0x003f5c38 CKHkS08Sparx_MoveTowardTarget_maybe: SteerTowardTarget from the node's position and +0xc8 to the goal,
    // the node moved and turned; +0x54 bit 4 = nearer than sqrt(0.2) to the goal, returned.
    uint8_t MoveTowardTarget(float dt);

    IKSerializable* m_pNode;                 // +0x20 CNode* (struct draft); read 5th. Spun 180 degrees a frame (Update)
    IKSerializable* m_pAnimationDictionary;  // +0x24 CAnimationDictionary*
    IKSerializable* m_pParticlesNode;        // +0x28 CParticlesNodeFx*
    // +0x2c..+0x48 eight floats (LVL010: 15, 30, 90, 75, 1, 5, 1, 3); their use in SteerTowardTarget /
    // PickRandomPointAround:
    float m_fl2c;                            // +0x2c the default speed_maybe
    float m_fl30;                            // +0x30 the catch-up speed_maybe (far from the hero, +0x54 bit 1)
    float m_fl34;                            // +0x34 the turn rate_maybe (degrees a second)
    float m_fl38;                            // +0x38 the acceleration_maybe
    float m_fl3c;                            // +0x3c (Ghidra dwDw_3c; the data is a float, 1.0) the inner radius_maybe
    float m_fl40;                            // +0x40 the outer radius_maybe
    float m_fl44;                            // +0x44 (Ghidra field_0x44; the data is a float, 1.0) the low height_maybe
    float m_fl48;                            // +0x48 the high height_maybe
    IKSerializable* m_pGlowNode;             // +0x4c CGlowNodeFx*
    IKSerializable* m_pPointLightFxData;     // +0x50 CKPointLightFxData*
    // +0x54 runtime flags: bit 0 placed, bit 1 the goal is far from the hero (catch-up speed), bit 2 the node's
    // animation advances (Update), bit 4 the goal is reached (or a new target is set).
    uint32_t m_ui32Flags;                    // +0x54
    CVector3 m_v3Goal;                       // +0x58 runtime: where the Sparx flies to
    CVector3 m_v3GoalDir;                    // +0x64 runtime: the goal's direction (null: none)
    float m_fGoalSpeed;                      // +0x70 runtime: the goal's speed, -1 the default (+0x2c)
    float m_fSpeed;                          // +0x74 runtime: the current speed (Start 0)
    uint32_t m_unk78;                        // +0x78 runtime: Start / Restart store 0; nothing in the unit reads it
    CGroundContactDatasIn m_GContactIn;      // +0x7c (masks at +0x84/+0x88 = 1, 8)
    CGroundContactDatasInOut m_GContactInOut;  // +0x8c
    IKSerializable* m_pTargetB8;             // +0xb8 runtime: the linked beacon the Sparx follows (Start clears it)
    IKSerializable* m_pPointLightBC;         // +0xbc runtime: CKPointLightNodeFx* live (OnActivate 0, Update acquires it)
    class CKMoveCpntUpdater* m_pMoveUpdaterC0;  // +0xc0 runtime: the move updater driving the Sparx (Start clears it)
    CMatrix34* m_pMatrixC4;                  // +0xc4 PostLoad: RwMatrixCreate_Thunk (0x3f4540)
    CVector3 m_v3Direction;                  // +0xc8 runtime: the flight direction (the node's at axis after Update)
};
DOTD_ASSERT_SIZE(CKHkS08Sparx, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pNode, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pAnimationDictionary, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pParticlesNode, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_fl2c, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_fl48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pGlowNode, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pPointLightFxData, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_ui32Flags, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_v3Goal, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_v3GoalDir, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_fGoalSpeed, 0x70);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_fSpeed, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_GContactIn, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_GContactInOut, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pTargetB8, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pPointLightBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pMoveUpdaterC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pMatrixC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_v3Direction, 0xc8);
