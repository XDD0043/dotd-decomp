// CKHkS08Hero.h - Spyro and Cynder (key 0x25c2, vtable 0xb22c98, size 0x1e00). Original unit:
// Spyro2008/hooks/CKHkS08Hero.cpp (+ the CKHkS08Hero_N units). Base: IKHkHero (0x3642). No XXL2 class.
//
// C2.1 ports the constructor and the Load. The Load is ~560 reads (0x2e2198, 10.5k instructions); the members
// are named m_unkXXX after their offset. Types: float where the file data are floats, else the struct draft's
// integer type. Reference comments give the class seen there in the live LVL010 objects (struct draft).
#pragma once
#include <cstdint>
#include <cstring>

#include "Spyro2008/hooks/IKHkHero.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"

class IKBoundingVolume;
class IKTime;
class IKFx;
struct RtAnimAnimation;

// 0x00c50d64: the zero vector (the hero code reaches it through TOC +0x28e0, +0x2cd8 and others).
inline constexpr CVector3 kHeroZeroVector{0.0f, 0.0f, 0.0f};
// 0x00c50d40: the shared Y axis (zero in the EBOOT's BSS, filled by a static initialiser).
inline constexpr CVector3 kHeroAxisY{0.0f, 1.0f, 0.0f};

class ICollision;
class CKHkClimbZone;
class ICollisionMesh;

class CKHkS08Hero : public IKHkHero {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x97)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bd628
        return key == 0x25c2 || key == 0x3642 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08Hero)

    CKHkS08Hero();  // 0x002dd000 CKHkS08Hero_Create (inlined constructor)
    ~CKHkS08Hero() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002e2198 CKHkS08Hero_Load
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x002d98f8 CKHkS08Hero_RecursiveRegistration
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x002db098 CKHkS08Hero_PostLoad
    // vt+0x40 0x002daa78 CKHkS08Hero_GetInfo: IKHkHero's values, then its own (bytes): 0x14 climbing (staying on and
    // +0x1628 clear), 0x15 / 0x16 / 0x19 carrying a key / a weight / a power bucket, 0x1a a filled power bucket, 0x17
    // flying, 0x18 +0x13d8, 0xe6 holding an enemy in a grab combo.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    void VfD4() override;                               // vt+0xd4 0x002d8c58 CKHkS08Hero_vfD4
    void InitAnimBlendSlot() override;                  // vt+0xd8 0x002dbb50 CKHkS08Hero_InitAnimBlendSlot
    void RestoreDefaultVolumes() override;              // vt+0x130 0x0030d528 CKHkS08Hero_RestoreDefaultVolumes_maybe
    float Vf160() override { return m_unk894; }         // vt+0x160 (a getter of m_unk894)

    // C2.2 spyro: the level start (CKHkS08Hero_Start and what it calls).
    void Start() override;                                           // vt+0x50 0x002df3e0 CKHkS08Hero_Start
    void Restart() override;                                         // vt+0x54 0x002df308 CKHkS08Hero_Restart
    // vt+0x68 0x002db3d8 CKHkS08Hero_Stop: the boundings put back under the hero's node, the first one's collision off,
    // the carried object dropped, the speed reset, the link / attack effects released, the abilities cancelled.
    void Stop() override;
    // vt+0x10 0x002dcb60 CKHkS08Hero_Destroy: IKHkHero's buffers, the animated camera data's Destroy, then
    // FreeOwnedResources.
    void Destroy() override;
    // 0x002dca08 CKHkS08Hero_FreeOwnedResources_maybe: the two reference arrays freed, the matrices destroyed, the hero
    // off the dynamic service, the ability host deleted.
    void FreeOwnedResources();
    void ResetMotionState(int32_t flag);                             // 0x002d9410 CKHkS08Hero_ResetMotionState_maybe
    void ResetMovementFromFrame(int32_t flag);                       // 0x002f8a08 (CKHkS08Hero_2.cpp)
    void ResetCombatState(int32_t flag);                             // 0x002fc938 (CKHkS08Hero_3.cpp)
    void InitInputActionTable();                                     // 0x00340d28 (CKHkS08Hero_17.cpp)
    void InitLocomotionAnimSubStateMachines();                       // 0x002df070
    virtual void ResetControlState();                                // vt+0xdc 0x002dc3d8
    virtual uint8_t CanAttachTo(IKSerializable* object, int32_t count);  // vt+0xe0 0x002dacb0 (CKHkS08Hero.cpp)
    int32_t MessageProc(uint16_t message, void* data) override;      // vt+0x1c 0x002dbe68 (CKHkS08Hero.cpp)
    int32_t HeroBaseMessageProc(uint16_t message, void* data);       // 0x00348220 (IKHkHero.cpp)
    virtual void UpdateMovement(IKTime* clock);                      // vt+0x17c 0x002dc730
    void DisableSwingTrails();                                       // 0x00334e20 (CKHkS08Hero_15.cpp)
    void ResetToDefaultState();                                      // 0x00348ac0 (IKHkHero.cpp)
    void ApplyControlAssignment(uint32_t isNew, uint32_t flag);      // 0x00348010 (IKHkHero.cpp)
    void SetCollisionVolumeEnabled(IKBoundingVolume* volume, int32_t enabled);  // 0x00352f10 (CKHkS08Hero_18.cpp)
    void ResetComboAndAttackCredits();                               // 0x0033f9d0 (CKHkS08Hero_16.cpp)
    virtual AnimBlendSlot* GetAnimBlendSlot();                       // vt+0x194 0x00301508
    AnimBlendSlot* GetInactiveAnimBlendSlot();                       // 0x00301528
    // 0x00361f40 CKHkS08Hero_GetCurrentAnimResource (IKHkHero_2.cpp): the animation (+0x58) of the active blend slot's
    // active controller.
    RtAnimAnimation* GetCurrentAnimResource();
    // 0x00364100 CKHkS08Hero_GetAnimMarkWindow (IKHkHero_2.cpp): that controller's evaluated time (+0x54) into `from`
    // and its time (+0x50) wrapped into the animation's duration into `to`.
    void GetAnimMarkWindow(float* from, float* to);
    void GetBlendSlot(AnimBlendSlot** slots, int32_t* count) override;  // vt+0xbc 0x003045e8 CKHkS08Hero_GetCinematicAnimSlots
    // vt+0xb0 0x00344d30 CKHkS08Hero_GetComponentByKey_maybe (k2000/logic/CKControlableHero.cpp): for key 0x486 the shadow
    // data at +0x64 (the cinematic blocs' m_pShadowData: point +0x64, normal +0x70, height +0x7c, flags +0x80), else null.
    IKSerializable* GetComponent(uint32_t key) override;
    void ClearMovementFloatFields();                                 // 0x002db9d8
    void SetMainShadowActive(int32_t active);                        // 0x00365e78
    void ResetInactiveBlendLayers();                                 // 0x00351908
    // 0x003516e8 CKHkS08Hero_PlayAnimOnInnerBlender_maybe (CKHkS08Hero_18.cpp)
    void PlayAnimOnInnerBlender(float start, float blend, uint8_t layer, uint32_t animation);
    void ResetMoveInput(int32_t flag);                               // 0x00368de0 (CKHkS08Hero_19.cpp)
    void UpdateHeroInputDerivedState();                              // 0x00368f18 (CKHkS08Hero_19.cpp)
    void SetUnk894(float value);                                     // vt+0x198 0x009bd698
    void SetUnk890(float value);                                     // vt+0x19c 0x009bd6a8
    // 0x002dd340 CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe (C2.2 strict2; its real job is the hero's entry on
    // the camera service's target stack, then the movement-mode history and the camera mode): see
    // CKHkS08HeroCameraTarget.cpp.
    void UpdateModeFlagsAndTetherTimers();

    // ---- step 2: the hero's frame and its state machines. The vt+ slots below have one implementation (this
    // class's), so they are not virtual here. ----
    void Update(IKTime* clock) override;                             // vt+0x7c 0x002de6d0 UpdateCKHkS08Hero
    // vt+0x80 0x002dbde0 CKHkS08Hero_LockedUpdate: the update of a locked hero (IKLife flag 2, CKBundle::Update): the
    // two fade timers (+0x1178 / +0x1184) counted down, the model fade and the partner link bolt (CKHkS08Hero.cpp).
    void Vf80(IKTime* clock) override;
    // 0x003346d8 CKHkS08Hero_UpdateModelFade_maybe (CKHkS08Hero_15.cpp): the model's alpha from the fade timer +0x1178.
    void UpdateModelFade(float dt);
    // 0x00337898 CKHkS08Hero_UpdatePartnerLinkBolt_maybe (CKHkS08Hero_15.cpp): the two partner link bolts (+0x19c8 /
    // +0x19d0) at the heroes' middle, their intensity from the fade timer +0x1184.
    void UpdatePartnerLinkBolt();
    // 0x00359388 CKHkS08Hero_UpdateModelOffsetAndBank_maybe (IKHkHero_2.cpp): the model node of a hero out of its
    // locomotion: at the position (+ the decaying offset +0x468), turned by the pitch +0x594, the bank +0x598 and the
    // heading, or (+0x360 bit 9) its up axis turned toward +0x798.
    void UpdateModelOffsetAndBank(IKTime* clock);
    // vt+0x70 0x002d9730 CKHkS08Hero_Pause: the base's (CKHkS08Hero_BasePause_maybe 0x344e10, empty), then the
    // target cursor (+0x1a08) let go (vt+0x58) and forgotten. vt+0x78 0x002d96e8 CKHkS08Hero_Resume: the base's
    // (0x344e18, empty) unless ShouldStayClimbing.
    void Pause() override;
    void Resume() override;
    void UpdateMovementAndContacts(IKTime* clock);                   // 0x00347530 (IKHkHero.cpp)
    void UpdateControlStateMachine(IKTime* clock);                   // 0x003688a8 (CKHkS08Hero_19.cpp)
    void UpdateActionStateMachine(IKTime* clock);                    // 0x003656b0 (CKHkS08Hero_19.cpp)
    void UpdateLocomotionAndResolvePosition(IKTime* clock);          // 0x00360c50 (IKHkHero_2.cpp)
    void UpdateAnimStateMachine(IKTime* clock);                      // 0x00352468 (CKHkS08Hero_18.cpp)
    void VfF4();                                                     // vt+0xf4 0x0030d458 (CKHkS08Hero_6.cpp)
    void VfFC(IKTime* clock);                                        // vt+0xfc 0x0033ca98 (CKHkS08Hero_16.cpp)
    void Vf100(IKTime* clock);                                       // vt+0x100 0x0032d4b0 (CKHkS08Hero_13.cpp)
    void UpdateAnimation(IKTime* clock);                             // vt+0x104 0x00309d58 (CKHkS08Hero_4.cpp)
    void UpdateSecondaryAnimCrossfade(IKTime* clock);                // vt+0x108 0x00305cf0 (CKHkS08Hero_4.cpp)
    void Vf174();                                                    // vt+0x174 0x002f8678 (CKHkS08Hero_2.cpp)
    void Vf178(IKTime* clock, uint8_t flag);                         // vt+0x178 0x002f8708 (CKHkS08Hero_2.cpp)
    // vt+0x168 0x009bd6e8 CKHkS08Hero_RequestCatchUpPoint_maybe [inline]: +0xed0 bit 2, the catch-up point request (CtlState1's condition).
    void Vf168() { m_ui32StatusFlagsED0 = (m_ui32StatusFlagsED0 & 0xfffffffbu) | 4u; }
    uint8_t VfF0();                                                  // vt+0xf0 0x0032d4c0 (CKHkS08Hero_13.cpp)
    void ReadHeroPlayerInput();                                      // 0x00369670 (CKHkS08Hero_19.cpp)
    void AIUpdateFollowDestination(IKTime* clock);                   // 0x0036df50 (CKHkS08Hero_19.cpp)
    // ---- step 6 AI: the partner following a flying leader (CKHkS08Hero_16.cpp). ----
    uint8_t CtlAIFollowFlying(IKTime* clock, int32_t phase, uint8_t other);  // 0x0033f4d0 control state 9
    // 0x0033cc78: the point to fly to: the AI waypoint +0x3c4 (no tether, +0xec4 bit 20 clear), the follow trail's
    // record, or the partner's climb zone (its path, or the trail's height on it).
    CVector3 AIGetFollowFlyingTarget(IKTime* clock);
    // 0x0033ecf0: the direction to fly (+0x3b8, the trail's / the waypoint's flat direction, the climb directions);
    // clears or sets +0x358 bit 20.
    CVector3 AIGetFollowDirection();
    // 0x0033db90: the stick level +0x394 from the distance to `target` (in the end 0xff, or the group's +0xaac x 255
    // within its +0x1e8).
    void AIComputeFollowFlyingThrottle(float stopDistance, const CVector3* target);
    // 0x0033de60: the move request +0x37c (+0x370 when climbing) = `direction`, or zero near the target / the leader
    // or with a low level; +0x394 = 0 with a zero request.
    void AISteerFollowFlying(float stopDistance, const CVector3* target, const CVector3* direction);
    // ---- step 4 AI: the partner's follow helpers (CKHkS08Hero_19.cpp unless noted). ----
    // 0x0036de10: path to `target`, the lost check, then the steering (`speed` while the path has a waypoint).
    uint8_t AIUpdateFollowPathAndArrival(float speed, IKTime* clock, CVector3* target, const CVector3* facing,
                                         const CVector3* leaderFacing, uint8_t flag);
    // 0x0036dd08: path to `target` then AISteerToWaypoint; `lostCheck` runs AITeleportIfLost first.
    uint8_t AIMoveToTarget(IKTime* clock, CVector3* target, const CVector3* facing, uint8_t flag9, uint8_t flag10,
                           uint8_t lostCheck);
    // 0x0036d210: the path request / update; the next waypoint into `waypoint` (+0x3c4), the end into `end` (+0x3d0).
    uint8_t AIUpdatePathToTarget(IKTime* clock, CVector3* target, CVector3* waypoint, CVector3* end);
    void AITeleportIfLost(IKTime* clock, int32_t onPathFailure);    // 0x0036cc88
    // 0x0036c6a0: the move vector +0x3b8 and the speed +0x3dc toward the waypoint, slowing near the end.
    uint8_t AIComputeFollowSteeringAndSpeed(float speed, IKTime* clock, const CVector3* waypoint, const CVector3* end,
                                            const CVector3* facing, uint8_t useModeSpeed);
    // 0x0036c160: the same for a scripted / catch-up move.
    uint8_t AISteerToWaypoint(IKTime* clock, const CVector3* waypoint, const CVector3* end, const CVector3* facing,
                              uint8_t noPath, uint8_t useMaxSpeed, uint8_t useMaxSpeed2);
    void AIComputeFollowVec5F0(IKTime* clock);                       // 0x0036aec0
    const SHeroSpeedMode* AISelectSpeedModeUpTo1000();               // inlined three times in 0x0036c160 / 0x0036c6a0
    // 0x0036a578: the hero put at `position` facing `facing` (both may be null); 1 when done.
    uint8_t TeleportTo(const CVector3* position, const CVector3* facing, uint8_t keepGround, uint8_t checkNav,
                       uint16_t sector, uint8_t flag);
    void AIWriteStickFromDesiredMove();                              // 0x0033cb50 (CKHkS08Hero_16.cpp)
    int8_t FindNextEnabledJump(int8_t index);                        // 0x00354990 (IKHkHero_2.cpp)
    void StartJumpOrFall(IKTime* clock, uint8_t flag);               // 0x0035e3e8 IKHkHero_StartJumpOrFall_maybe (IKHkHero_2.cpp)
    float GetFloat218() const;                                       // 0x00361c98 (IKHkHero_2.cpp)
    void LeaveAttachedObject();                                      // 0x00344e88 (k2000/logic/CKControlableHero.cpp)
    void ResetBoundingSpheresAtDeltaPos(const CVector3* delta);      // 0x00352c38 (CKHkS08Hero_18.cpp)
    uint8_t CtlAIPickCatchUpPoint(IKTime* clock, int32_t phase, uint8_t other);     // 0x0033e108 (CKHkS08Hero_16.cpp)
    uint8_t CtlScriptedMoveTo(IKTime* clock, int32_t phase, uint8_t other);         // 0x0033e378 (CKHkS08Hero_16.cpp)
    uint8_t CtlControlLocked(IKTime* clock, int32_t phase, uint8_t other);          // 0x0033da70 (CKHkS08Hero_16.cpp)
    uint8_t IsPointWalkableInCurrentSector(const CVector3* position);              // 0x0033d7d8 (CKHkS08Hero_16.cpp)
    uint8_t MoveTowardDrivenTarget(float speed, const IKTime* clock, const CVector3* target);  // 0x0036bf20 (_19)
    uint8_t CtlMoveToTargetBody(IKTime* clock, int32_t phase, uint8_t other);       // 0x00368618 (CKHkS08Hero_19.cpp)
    uint8_t CtlAIWarpToCatchUpPoint(IKTime* clock, int32_t phase, uint8_t other);   // 0x0033f150 (CKHkS08Hero_16.cpp)
    uint8_t CtlPlayerFollowsFocus(IKTime* clock, int32_t phase, uint8_t other);     // 0x00368478
    uint8_t HandleAIFollowGroundPhase(IKTime* clock, int32_t phase, uint8_t other);  // 0x00368248 (CKHkS08Hero_19.cpp)
    void PlayAnimation(float start, float blend, uint16_t animation);  // vt+0x184 0x003015d0 (CKHkS08Hero_4.cpp)
    void AdvanceAnimTime(float dt);                                  // vt+0x188 0x00301578 (CKHkS08Hero_4.cpp)
    void PlayAnimBase(float start, float blend, uint16_t animation);  // 0x00351570 CKHkS08HeroBase_PlayAnim (CKHkS08Hero_18.cpp)
    void AdvanceAnimTimeBase(float dt);                              // 0x0034f970 CKHkS08HeroBase_AdvanceAnimTime (IKHkHero.cpp)
    void UpdateIdleVariationAnim(float dt);                          // 0x00302218 (CKHkS08Hero_4.cpp)
    float Vf158() const { return m_unk890; }                         // vt+0x158 0x009bd6a0: the animation speed
    uint8_t VfEC();                                                  // vt+0xec 0x0032d4b8 (CKHkS08Hero_13.cpp)
    void Vf180() {}                                                  // vt+0x180 0x002f8518 CKHkS08Hero_vf180 (empty)
    void TryUseInteractable();                                       // vt+0x16c 0x00340f40 (CKHkS08Hero_17.cpp)
    void ResolveHeroContactMovement(IKTime* clock);                  // 0x00353528 (CKHkS08Hero_18.cpp)
    // vt+0x190 0x0030d688 HandleHeroDamageAndReaction (_6): a hit from `source` at `point` through `volume`.
    void HandleHeroDamageAndReaction(IKSerializable* source, const CVector3* point, IKBoundingVolume* volume);
    float ComputeHeroDamageAfterReduction(float damage, uint8_t once);  // 0x002fead8 (_3)
    void SpawnHitExplosionFx();                                          // 0x00334450 (_15)
    void GrantKillUpgradeBonus(IKSerializable* enemy);                   // 0x0032e0f0 (_14)
    void UpdateHazardAndSavedPositionRespawn(IKTime* clock);         // 0x00355328 (IKHkHero_2.cpp)
    // 0x002dc660 CKHkS08Hero_UpdateGroundSurfaceFlags_maybe (vt+0x14c, CKHkS08Hero.cpp): +0xec4 bit 18 on a ground of
    // property 0x200 within +0x8e8 of it, +0xecc bit 28 on a ground of property 0x8000.
    void UpdateGroundSurfaceFlags(IKTime* clock);
    // The hazard outcomes (health, respawn; CKHkS08Hero_19.cpp / IKHkHero_2.cpp).
    uint8_t TeleportToSavedPosition();                               // 0x0036ac88
    void ApplyHazardHitAndLeaveAttach(uint8_t damage, uint8_t kind);  // 0x00354a80
    void RequestOwnDragonSelectionIfMultiHero();                     // 0x0036a260
    // 0x0036bbf8 IKHkHero_InitMoveRequestFromSourcePoint_maybe (CKHkS08Hero_19.cpp): a push away from `source`.
    void InitMoveRequestFromSourcePoint(const float* speeds, const CVector3* source, int32_t mode, int32_t savePosition);
    uint8_t ProcessPendingTeleport(uint8_t flag1, uint8_t flag2);    // 0x0036ad50 (CKHkS08Hero_19.cpp)
    void UpdateSpeedScaledVolumeRadius();                            // 0x00352dd0 (CKHkS08Hero_18.cpp)
    void UpdateFootsteps(IKTime* clock);                             // 0x003678f8 (CKHkS08Hero_19.cpp)
    uint8_t SelectMoveEntryIndexForSpeed(float speed);               // 0x00369ac8 (CKHkS08Hero_19.cpp)
    void UpdateDynamicGroundAttachment(IKTime* clock, uint32_t wasOnMovingGround);  // 0x00360648 (IKHkHero_2.cpp)
    // 0x0035b278 (IKHkHero_2.cpp): the move (+0x5b4) of the hero from its position to `target` against the walls
    // (`rootMotion` +0x5a8: the animation's part, swept from the position moved by it unless `noRootMotion`).
    void ResolveWallMovement(CVector3* move, CVector3* target, const CVector3* rootMotion, uint32_t noRootMotion);
    // 0x0036b1a0 (CKHkS08Hero_19.cpp): `target` kept on the walkable navigation, `move` (+0x5b4) recomputed from it.
    void ConstrainMovementToNavigation(IKTime* clock, CVector3* move, CVector3* target);
    // 0x0035f6f8 SetPositions (IKHkHero_2.cpp): `target` resolved on the ground (ResolveGroundContactAndPosition, then
    // again keeping the old position when the first finds no place), the position (+0x54c; the previous +0x558), the
    // ground's normal (+0x564) and point (+0x570; the previous +0x57c).
    void SetPositions(IKTime* clock, CVector3* target);
    // 0x0035ea70 CKHkS08Hero_ResolveGroundContactAndPosition_maybe (IKHkHero_2.cpp): the ground under `target` probed into
    // +0x4b8; `target` put on it, kept back at `previous` or pushed off a wall; 1 when the hero may stand there.
    // `keepPrevious`: the second try (the old position kept as is); `deactivated`: a ground the hero falls through
    // (its properties match vt+0x150, never for CKHkS08Hero) is switched off and returned there.
    uint8_t ResolveGroundContactAndPosition(IKTime* clock, CVector3* target, const CVector3* previous,
                                            uint32_t keepPrevious, ICollisionMesh** deactivated);
    // 0x009bdb48 CKHkS08Hero_SetAirborne_maybe (inline): +0x354 bit 0 (the hero is in the air: jumping or falling;
    // CKHkS08Hero_GetGroundObject_maybe 0x363c40 has no ground then) takes `airborne` (the camera told first, 0x354cf0);
    // leaving the ground clears bit 2, landing bit 9, +0x364 bit 10, +0x354 bit 1 and sets +0x590 = 0xff.
    void SetDirectionLock(uint8_t airborne) {
        SetCameraDirectionLock(airborne);
        const uint32_t flags = (m_ui32HeroFlags354 & 0xfffffffeu) | airborne;
        m_ui32HeroFlags354 = flags;
        if (airborne != 0) {
            m_ui32HeroFlags354 = flags & ~4u;
            return;
        }
        m_ui32HeroFlags354 = flags & ~0x200u;
        m_ui32HeroFlags364 &= ~0x400u;
        m_ui32HeroFlags354 &= ~2u;
        m_unk590 = 0xff;
    }
    // 0x00354cf0 CKHkS08Hero_SetCameraDirectionLock_maybe (IKHkHero_2.cpp): the player's hero leaving the ground locks the
    // game camera's direction (CKSrvCamera_EnableDirectionLock_maybe 0x12bc98), landing clears its bit 0 of +0x46c.
    void SetCameraDirectionLock(uint8_t airborne);
    // vt+0x150 0x002d8c78 CKHkS08Hero_vf150: 0 (the ground properties the hero falls through: none).
    uint16_t Vf150() const { return 0; }
    void UpdateSignedSlopePitchClass();                              // 0x00359c60 (IKHkHero_2.cpp)
    uint8_t IsLockedToObject();                                      // 0x00362040 (IKHkHero_2.cpp)
    // The lock and unlock (CKHkS08Hero_19.cpp): vt+0xa8 0x002dbb88 CKHkS08Hero_OnLock, vt+0xac 0x002dafa8
    // CKHkS08Hero_OnUnlock, 0x00348f00 ExitAllStateMachines_maybe, 0x00365f30 DetachWaterWaveFx_maybe, vt+0x134
    // 0x003349a8 ReleaseOwnedFx (non-virtual here: no other override), 0x00345e50 IKHkHero_AttachNodeToHotspot_maybe.
    // vt+0x170 0x002dbc60 CKHkS08Hero_CanDragonSwitch_maybe (CKHkS08Hero.cpp; non-virtual here).
    uint8_t CanDragonSwitch();
    void OnLock() override;
    void OnUnlock() override;
    void ExitAllStateMachines();
    void DetachWaterWaveFx();
    void ReleaseOwnedFx();
    void AttachNodeToHotspot(class CSGLeaf* node);
    // The attachment to an object (CKHkSequenceMgr_DetachHeroes_maybe's part of the hero; IKHkHero_2.cpp).
    IKSerializable* GetAttachedObject() { return m_unk90; }          // 0x00361d50 CKHkS08Hero_GetAttachedObject_maybe
    // 0x00361960 CKHkS08Hero_GetDragonIndex: the hero index (+0x24).
    uint8_t GetDragonIndex() const { return m_ui8Hero; }
    // 0x00362af0 CKHkS08Hero_IsPlayerControlled: the hero is the leader it tracks (+0x24 == +0x25).
    uint8_t IsPlayerControlled() const { return m_ui8Hero == m_ui8TrackedLeader ? 1 : 0; }
    // 0x00361968 CKHkS08Hero_GetPositionPtr: the position (+0x54c), or with life bit 1 and vt+0x164 clear (+0xed4
    // bit 4, CKHkS08Hero_vf164 0x9bd700) the node's world position.
    const float* GetPositionPtr() const;
    // 0x0032afc8 CKHkS08Hero_ShareCollectedBonusWithPartner_maybe (bonus-crumbly, C2.8): a health / mana bonus (pool types
    // 1 / 2) the hero collected, not itself shared, with +0xed0 bit 16 set: a copy of it spawned at his hot spot 5 flies
    // to his partner (vt+0xe4 of the new bonus).
    void ShareCollectedBonusWithPartner(IKSerializable* bonus);
    // 0x0032a840 CKHkS08Hero_GetEarthBoulderFlag2CC_maybe (bonus-crumbly, C2.8): Spyro's (hero 0) ability slot +0x1be0 when
    // it is a CKEarthBoulder (0x95cc): its +0x2cc byte (rolling in the air); else 0.
    uint8_t GetEarthBoulderFlag2CC();
    // 0x0032a520 CKHkS08Hero_ShouldJoinPartnerFlight_Thunk (bonus-crumbly, C2.8): ShouldJoinPartnerFlight's low byte.
    uint8_t ShouldJoinPartnerFlightThunk() { return ShouldJoinPartnerFlight(); }
    // 0x0032a010 CKHkS08Hero_IsAttachedToContextualMeca: attached (+0x358 bit 0) to a CKHkContextualMeca (0x2a82).
    uint8_t IsAttachedToContextualMeca();
    // 0x0032a090 CKHkS08Hero_IsCarryingTransportableKey_maybe: the carrier's (+0xfb8) carried object (vt+0x80) is of
    // class id 0xc2.
    uint8_t IsCarryingTransportableKey();
    // 0x00338130 CKHkS08Hero_SetSwitchFeedbackFxActive_maybe (CKHkS08Hero_15.cpp): the target cursor effect (+0x1a08, from
    // the CKTargetCursorFxData +0x1a04) acquired and placed at the hero, or faded out and forgotten.
    void SetSwitchFeedbackFxActive(uint8_t on);
    uint8_t IsCarryingTransportableWeight();  // 0x0032a148 (CKHkS08Hero_12.cpp): the carried object of class id 0xc5
    void SetInvulnerable(uint8_t invulnerable);                      // 0x00361b20 IKHkHero_SetInvulnerable_maybe
    // pre-C2.7 gamemgr: the attachment calls of the game manager's hero death state (IKHkHero_2.cpp unless noted).
    // 0x00362360 CKHkS08Hero_AttachToObject_maybe: when the hero may attach to `object` (vt+0xe0), it leaves its
    // current object, +0x90 / +0x94 = object / mode, +0x358 bit 0 set, +0x35c bit 17 cleared, then vt+0x120; 1 then.
    uint8_t AttachToObject(IKSerializable* object, int32_t mode);
    // 0x002dba30 CKHkS08Hero_OnAttachToObject (vt+0x120, CKHkS08Hero.cpp; non-virtual here): the anim marks, +0xec8 bit
    // 2 and the impulsion cleared; unless the object is of class id 0x247, the position adjustment and the moves
    // (+0x1268, +0x534, +0x5b4) cleared, the ground movement mode, +0xec8 bit 7 and +0xed0 bits 2-3 cleared.
    void OnAttachToObject();
    // 0x002dc5a0 CKHkS08Hero_OnDetachFromObject (vt+0x124, CKHkS08Hero.cpp; non-virtual here): unless the object left is of
    // class id 0x247, the position adjustment (+0x1268) cleared, the ground movement mode, +0xec8 bit 7 and +0xed0 bits
    // 2-3 cleared.
    void OnDetachFromObject();
    // While attached (+0x358 bit 0): 0x003622a8 IKHkHero_SetLockedToObject_maybe (+0x358 bit 2; locking or a lock kept
    // clears the camera's direction lock, an unlock places the hero at the hot spot or `position`), 0x00362010
    // ..._SetObjectControlsAnim_maybe (+0x358 bit 1), 0x00362050 ..._SetAttachedMovementEnabled_maybe (+0x358 bit 3;
    // turning it off clears +0x35c bits 6-7), 0x00362150 ..._SetCollisionDisabledWhileAttached_maybe (+0x360 bit 16; on,
    // the hero's collision volumes switched off, off, the default volumes back) and the flag setters 0x00363dc8 /
    // 0x00363df8 / 0x00363f98 (+0x360 bits 14, 15, 8), 0x00363ee8 / 0x00363fc8 (+0x35c bits 3, 21).
    void SetLockedToObject(uint8_t locked, const float* position, const float* direction);
    // 0x0035b058 IKHkHero_PlaceAtHotspotOrPosition_maybe: the hero put at `position` (else its body hot spot's) facing
    // `direction` flattened and normalised (else the hot spot's at axis): position, previous position, facing, yaw.
    void PlaceAtHotspotOrPosition(const float* position, const float* direction);
    void SetObjectControlsAnim(uint8_t value);
    void SetAttachedMovementEnabled(uint8_t enabled);
    void SetCollisionDisabledWhileAttached(uint8_t disabled);
    void SetFlag360Bit14IfAttached(uint8_t value);
    void SetFlag360Bit15IfAttached(uint8_t value);
    void SetFlag360Bit8IfAttached(uint8_t value);
    void SetFlag35CBit3IfAttached(uint8_t value);
    void SetFlag35CBit21IfAttached(uint8_t value);
    // 0x00363410 IKHkHero_AdvanceObjectAnimTime_maybe: with the object controlling the animation (+0x358 bit 1), +0x360
    // bit 11 set and the active controller of the animation slot (vt+0x194) runs `dt` further.
    void AdvanceObjectAnimTime(float dt);
    // 0x00364020 CKHkS08Hero_WillAnimEndWithin_maybe (C2.8 sequence): the animation slot's active controller ends within
    // `dt` (an animation, and its wrapped time plus `dt` reaches the duration).
    uint8_t WillAnimEndWithin(float dt);
    // CKHkS08Hero_12.cpp: 0x00329eb8 CKHkS08Hero_GetSubNodeB_maybe (sub-node `index` of +0x58, below the hero's count,
    // 14 for both dragons at 0x00a70728; else null), 0x0032a638 CKHkS08Hero_SetExternallyPositionedAndPhysics_maybe
    // (SetLockedToObject, then the dynamic service's entry flag of the hero = !locked) and vt+0xc0 0x0032ad80
    // CKHkS08Hero_PlayAnimResource_maybe (with the object controlling the animation: the root slot cuts, +0x360 bit 11,
    // the blender's weight word 1.0 / 0.0, then the active controller plays the animation word from `start`).
    IKSerializable* GetSubNodeB(uint32_t index);
    // CKHkS08Hero_12.cpp, the accessors the unported callers (CKS08HeroElement*, CKHkS08CristalEmitter) need:
    float GetCurrentSpeed() const { return m_fCurrentHorizSpeed; }                      // 0x00329d90 CKHkS08Hero_GetCurrentSpeed_maybe
    IKSerializable* GetCarrier() const { return m_pCarrierHero; }                  // 0x0032a000 CKHkS08Hero_GetCarrier
    void EnableSubNode(uint32_t index);                                       // 0x00329e00 CKHkS08Hero_EnableSubNode_maybe
    IKSerializable* GetSubNode(uint32_t index);                               // 0x00329e80 CKHkS08Hero_GetSubNode_maybe
    uint8_t IsCarryingPowerBucket();                                          // 0x0032a200 CKHkS08Hero_IsCarryingPowerBucket_maybe
    uint8_t IsCarryingFilledPowerBucket();                                    // 0x0032a2b8 CKHkS08Hero_IsCarryingFilledPowerBucket_maybe
    CVector3 GetHotspot4FlatDir();                                            // 0x0032ba68 CKHkS08Hero_GetHotspot4FlatDir_maybe
    void SetExternallyPositionedAndPhysics(uint8_t locked, const float* position, const float* direction);
    void PlayAnimResource(float start, uint32_t animation);
    void SetUnk530IfAttachedMovement(float value);                   // 0x003626a0 IKHkHero_SetFloat530_IfAttachedMovementEnabled_maybe
    void SetUnk534IfAttachedMovement(float value);                   // 0x00362688 IKHkHero_SetFloat534_IfAttachedMovementEnabled_maybe
    void DetachFromObject();                                         // 0x00364608 CKHkS08Hero_DetachFromObject_maybe
    // ---- C2.8 meca-hero: the moves and animations an object (a contextual mechanism) drives. ----
    // vt+0xc4 0x0032ac88 CKHkS08Hero_CrossfadeAnimResource_maybe (CKHkS08Hero_12.cpp): with the object controlling the
    // animation (+0x358 bit 1), the root slot (+0x10f0) starts a crossfade of `blend` (mode 1), +0x360 bit 11, and the
    // animation slot (vt+0x194) crossfades to `word` from `start` (AnimBlendSlot_CrossfadeToAnim); its mode, else 0.
    uint32_t CrossfadeAnimResource(float blend, float start, uint32_t word, uint32_t mode);
    // vt+0xcc 0x0032a548 CKHkS08Hero_SetMoveDestination (CKHkS08Hero_12.cpp): +0x354 bit 31 cleared, then 0x00364470
    // IKHkHero_SetMoveDestination_maybe (IKHkHero_2.cpp): with the attached movement on (+0x358 bit 3) and no lock (bit
    // 2), the destination +0x398, the flat normalised direction +0x3a4, +0x358 bit 4 = `flag4`, +0x360 bit 31 =
    // `flag31`, the timeout +0x480 (0: none) and its start +0x484 = -1000, +0x358 bit 29 set, +0x35c bit 15 cleared.
    void SetMoveDestination(float timeout, const CVector3* position, const CVector3* direction, uint32_t unused,
                            uint32_t flag4, uint32_t flag31);
    void SetMoveDestinationBase(float timeout, const CVector3* position, const CVector3* direction, uint32_t flag4,
                                uint32_t flag31);
    // vt+0xd0 0x0032b500 CKHkS08Hero_UpdateMoveTo_maybe (CKHkS08Hero_12.cpp): a ground of property 0x200 makes the hero
    // fly, the path character's walk type (2 / 4), the walk to +0x398 (0x00363900 IKHkHero_UpdateMoveTo_maybe), the
    // player-input copy of the steering (+0x37c, +0x394) and the arrival within 1 unit: 1 when arrived (`out`: blocked).
    uint8_t UpdateMoveTo(IKTime* clock, uint8_t* out);
    uint8_t UpdateMoveToBase(IKTime* clock, uint8_t* out);
    // 0x00362450 CKHkS08Hero_GetCurrentAnimDuration: the duration of the active controller of the animation slot.
    float GetCurrentAnimDuration();
    // 0x00363378 IKHkHero_SetObjectAnimTime_maybe: with +0x358 bit 1, +0x360 bit 11 and the active controller's time.
    void SetObjectAnimTime(float time);
    // 0x00361fa0 IKHkHero_IsAnimBlendCrossfading_maybe: the animation slot's crossfade mode (+0x14) is not 0.
    uint8_t IsAnimBlendCrossfading();
    // 0x00362a40 CKHkS08Hero_GetPlayerMoveVectorPtr / 0x00362dd0 CKHkS08Hero_GetPlayerInputByte394: a player's hero reads
    // its input (ReadHeroPlayerInput with +0x358 bit 3) and answers +0x37c / +0x394; another the zero vector / 0.
    const float* GetPlayerMoveVectorPtr();
    uint8_t GetPlayerInputByte394();
    // C2.8 port-all P16 (IKHkHero_2.cpp): 0x003626f8 CKHkS08Hero_GetPlayerInputFloat38C / 0x00362c98
    // _GetPlayerInputFlag358b21 (a player's hero reads its input first, as above; another 0 / 0); 0x00361df8
    // IKHkHero_CallVf140_maybe (vt+0x140 0x9bd610: 1); 0x00361ee0 IKHkHero_GetCurrentAnim_maybe / 0x003638a0
    // IKHkHero_GetCurrentAnimTime_maybe (the active controller's word +0x5c / time +0x54); 0x00362118
    // CKHkS08Hero_TeleportTo_Thunk (TeleportTo(position, facing, 0, 0, 0xffff, 0)).
    float GetPlayerInputFloat38C();
    uint32_t GetPlayerInputFlag358b21();
    uint8_t CallVf140() { return 1; }
    uint32_t GetCurrentAnim();
    float GetCurrentAnimTime();
    void TeleportToThunk(const CVector3* position, const CVector3* facing);
    // 0x0033cac0 / 0x0033cb08 CKHkS08Hero_CopyPointRecordWithType4 / 2_maybe (CKHkS08Hero_16.cpp): the path character's
    // walk type (bits 0-2 of +0x3e0) set and copied to the path-finding component (+0x3f8).
    void SetPathCharacterType(uint32_t type);
    // 0x00363e58 IKHkHero_SetFlag364Bit12_IfAttached_maybe / 0x00363e88 IKHkHero_SetFlag35CBit0_IfAttached_maybe: while
    // attached (+0x358 bit 0), +0x364 bit 12 / +0x35c bit 0 = `value`.
    void SetFlag364Bit12IfAttached(uint8_t value) {
        if ((m_ui32HeroFlags358 & 1u) == 0) return;
        m_ui32HeroFlags364 = (m_ui32HeroFlags364 & 0xffffefffu) | (static_cast<uint32_t>(value) << 12);
    }
    void SetFlag35CBit0IfAttached(uint8_t value) {
        if ((m_ui32HeroFlags358 & 1u) == 0) return;
        m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xfffffffeu) | value;
    }
    // 0x00362670 IKHkHero_SetAttachedMoveSpeed_maybe: with the attached movement on (+0x358 bit 3), +0x3dc = `speed`.
    void SetAttachedMoveSpeed(float speed) {
        if ((m_ui32HeroFlags358 & 8u) == 0) return;
        m_unk3dc = speed;
    }
    // 0x00361de8 IKHkHero_GetFlag354Bit30_maybe: +0x354 bit 30 (rldicl 34, 63).
    uint8_t GetFlag354Bit30() const { return static_cast<uint8_t>((m_ui32HeroFlags354 >> 30) & 1u); }
    // 0x003626e8 IKHkHero_IsAttachedMovementEnabled_maybe: +0x358 bit 3 (rldicl 61, 63).
    uint8_t IsAttachedMovementEnabled() const { return static_cast<uint8_t>((m_ui32HeroFlags358 >> 3) & 1u); }
    // 0x00363ff8 IKHkHero_IsFlag35CBit6_AndFlag3B0Bit6Clear_maybe: +0x35c bit 6 set and +0x3b0 bit 6 clear.
    uint8_t IsFlag35CBit6AndFlag3B0Bit6Clear() const {
        if ((m_ui32HeroFlags35C & 0x40u) == 0) return 0;
        return static_cast<uint8_t>(((m_unk3b0 ^ 0x40u) >> 6) & 1u);
    }
    // 0x00364268 IKHkHero_PassesTrackerAssignFlagChecks_maybe: a companion (+0x24 != +0x25) that is not +0x35c bit 5 /
    // bit 29, nor +0x360 bit 30, nor +0x35c bit 6 without +0x3b0 bit 6: +0x360 bit 12 clear.
    uint8_t PassesTrackerAssignFlagChecks() const {
        if (m_ui8Hero == m_ui8TrackedLeader || (m_ui32HeroFlags35C & 0x20u) != 0) return 0;
        if ((m_ui32HeroFlags360 & 0x40000000u) != 0 || (m_ui32HeroFlags35C & 0x20000000u) != 0) return 0;
        const uint8_t clear = static_cast<uint8_t>(((m_ui32HeroFlags360 >> 12) & 1u) ^ 1u);
        if ((m_ui32HeroFlags35C & 0x40u) == 0) return clear;
        return (m_unk3b0 & 0x40u) != 0 ? clear : 0;
    }
    // 0x0032a438 CKHkS08Hero_SetCarryingObject_maybe (CKHkS08Hero_12.cpp): +0xed4 bit 3 = `carrying` (slwi 3, or: a value
    // above 1 sets higher bits too).
    void SetCarryingObject(uint32_t carrying) { m_ui32StatusFlagsED4 = (m_ui32StatusFlagsED4 & 0xfffffff7u) | (carrying << 3); }
    // 0x00350c48 CKHkS08Hero_AdvanceInnerBlenderAnimTime_maybe (CKHkS08Hero_18.cpp): the active controller of blend slot
    // `slot` (+0x138, 24-byte slots) advanced by `dt` (its time +0x50).
    void AdvanceInnerBlenderAnimTime(float dt, uint32_t slot);
    void UpdateField794ByAnimAndElementLevel();                      // 0x003101e8 (CKHkS08Hero.cpp)
    void UpdateField1348Timers();                                    // 0x0033d8f0 (CKHkS08Hero.cpp)
    void ProcessHeroContactList();                                   // 0x002d8f38 (CKHkS08Hero.cpp)
    // The hero's collisions (ICollision lists of its volumes, filled by CKSrvCollision_ProcessPairs): the volume of
    // each side, its own first.
    IKSerializable* GetCollisionVolume8() { return m_apBoundings[8]; }  // 0x0030ce30 CKHkS08Hero_GetCollisionVolumeFromObj54_maybe
    void HandleHeroContactDamageAndImpulse(ICollision* collision, IKBoundingVolume* own, IKBoundingVolume* other);  // 0x0030ce40 (CKHkS08Hero_6.cpp)
    void HandleClimbZoneContact(ICollision* collision, IKBoundingVolume* own, IKBoundingVolume* other);  // 0x002f9fa8 (CKHkS08Hero_2.cpp)
    uint8_t GetClimbFlag1627Or1626And1628();                         // 0x0031d880 (CKHkS08Hero_11.cpp)
    uint8_t HasNonZeroSpeed530Or534();                               // 0x00369da0 (CKHkS08Hero_19.cpp)
    void Vf138(ICollision*, IKBoundingVolume*, IKBoundingVolume*) {}  // vt+0x138 0x0030cab8 CKHkS08Hero_vf138 (empty)
    void UpdateHeroStatusAndTimedDamage();                           // 0x002fef58 (CKHkS08Hero.cpp)
    // ---- step 4 ANIM: the equipped armour and the regeneration (CKHkS08Hero_5.cpp). ----
    void ApplyEquippedArmor();                                       // 0x0030c700
    void ShowArmorPieceMesh(uint8_t armor, uint8_t slot);            // 0x0030aec0
    void ClearArmorBonusFlags();                                     // 0x0030b0b8
    void SetArmorBonusFlags(uint8_t armor, uint8_t slot, int32_t count);  // 0x0030b340
    void UpdateRegenAndElementTimeout();                             // 0x0030b6b8
    void UpdateGroundMovement(float dt);                             // 0x003189a8 (CKHkS08Hero_9.cpp)
    CVector3 ComputeGroundMoveDirection();                           // 0x00318758 (CKHkS08Hero_9.cpp)
    // 0x002f96c8 CKHkS08Hero_FollowDynamicGround_maybe (CKHkS08Hero_2.cpp): on a moving ground (class 0x13) the position
    // and the node's axes are carried from the ground's last inverse matrix (+0x16f0) to its current world matrix (unless
    // +0x16f0 is still the identity: flags 0x20003); +0x16f0 takes the ground's inverse. 1 when carried.
    uint8_t FollowDynamicGround(IKTime* clock, IKSerializable* ground);
    // 0x0030fd50 (CKHkS08Hero_7.cpp): `base` moved along the facing (+0xec8 bits 13 / 18), or the zero vector.
    CVector3 ComputeBlendedVelocityFromFlagsEC8(const CVector3* base, float scale, float lift) const;
    uint8_t IsAnyComboKindActive() const;                            // 0x002fd030 (CKHkS08Hero_3.cpp)
    // 0x002fc1b0 CKHkS08Hero_IsComboKindFlagSet (CKHkS08Hero_2.cpp): one of the combo kind bytes +0x1abc / +0x1abd /
    // +0x1ac3 / +0x1ac0 / +0x1ac1 / +0x1ac2.
    uint8_t IsComboKindFlagSet() const;
    uint8_t IsInCombo() const { return IsComboKindFlagSet(); }     // 0x0032a698 CKHkS08Hero_IsInCombo
    // 0x00329f00 CKHkS08Hero_SetHitConfirmed: bit 1 of +0xecc (an enemy took the hero's hit).
    void SetHitConfirmed(uint8_t confirmed) { m_unkecc = (m_unkecc & ~2u) | (static_cast<uint32_t>(confirmed) << 1); }
    IKSerializable* GetGrabTarget() const { return m_pTargetedEnemy; }     // 0x00329df8 CKHkS08Hero_GetGrabTarget
    // 0x0032a7a8 CKHkS08Hero_IsUsingWindBeam: hero 1 (+0x24) with an object at +0x1cc0 of class 0xa50c.
    uint8_t IsUsingWindBeam();
    // 0x0032a8d0 CKHkS08Hero_GetAbilityElementLevel: the element level of ability `id` for this hero's dragon (0: none).
    uint8_t GetAbilityElementLevel(uint8_t id);
    // 0x0032a938 / 0x0032ab18 / 0x0032aa28 CKHkS08Hero_SetAttackSphere0 / 1 / 2: the ability's attack sphere `index`
    // (+0x1b8c[index]): `on` hangs it (when off) under the hot spot `hotspot` with `radius`, gives it `damage` (+0x1c)
    // and activates it; off disables it (when on) and marks the active list stale (+0x1bac -1). The count +0x1bac is
    // cleared first either way.
    void SetAttackSphere(uint32_t index, uint8_t on, float radius, int8_t hotspot, IKSerializable* damage);
    // 0x0030cad0 CKHkS08Hero_ActivateAttackSphere: the volume enabled and appended to the active hit spheres (+0x1b9c).
    void ActivateAttackSphere(IKSerializable* volume, int32_t enabled);
    // 0x00329f20 CKHkS08Hero_GetCurrentBlowFlag61: the current combo node's blow's flag +0x61 (vt+0xac); 0 without one.
    uint8_t GetCurrentBlowFlag61();
    // 0x0032ac08 CKHkS08Hero_GetElementColor_maybe (a colour returned through a hidden pointer): the current element's
    // (+0x1cc4) colour from +0x1c20 (`which` 0) or +0x1c34 (1), else white (0x00c50dfc); the 4 bytes as stored.
    uint32_t GetElementColor(uint32_t which) const;
    // 0x0032b138 CKHkS08Hero_GetHotspot4AimDir_maybe (CKHkS08Hero_12.cpp): the at row of hot spot 4's world matrix;
    // unless `raw`, its y replaced by +0x12a4 and the vector normalised (kept when its length is 0).
    CVector3 GetHotspot4AimDir(int32_t raw);
    // DOTD: AnimState7_ComboAnim's inlined pairing (three times): the held enemy (+0x124) crossfades to the animation
    // paired with the hero's `anim` (0xb2 on), remembered in +0x1ab0.
    void PairGrabbedEnemyAnim(int32_t anim, float blend, float start);
    // The targeting (CKHkS08Hero_3.cpp). `aim` is a CKAimCamembert (+0x1a78, +0x1a7c, +0x1d38).
    // 0x002fdec8 CKHkS08Hero_GetAimPointOnEnemy: where to aim at `enemy` from `from` (0x00c50da0, all FLT_MAX, when the
    // enemy is no valid target); with `clampHeight` the point is lowered to the hero frame's slope over the distance.
    CVector3 GetAimPointOnEnemy(IKSerializable* enemy, const CVector3* from, uint8_t hotSpotOnly, uint8_t clampHeight);
    // 0x002fe5b8 CKHkS08Hero_FindBestEnemyInAimCone_maybe: the best scored active enemy in the cone, or null.
    IKSerializable* FindBestEnemyInAimCone(IKSerializable* aim, const CVector3* direction);
    // 0x002fe7f0 CKHkS08Hero_AcquireTargetInAimCone: the same into +0x124 (1 and its score), else +0x1b0c cleared (0).
    uint8_t AcquireTargetInAimCone(IKSerializable* aim, const CVector3* direction, float* score);
    // 0x002fea88 CKHkS08Hero_TryAcquireTarget
    uint8_t TryAcquireTarget(IKSerializable* aim, const CVector3* direction);
    // 0x002fd7c0 CKHkS08Hero_GetAimPointOnHook: where to aim at the hook `hook` (the "no point" without one); with
    // `clampHeight` lowered to the hero frame's slope as GetAimPointOnEnemy's.
    CVector3 GetAimPointOnHook(IKSerializable* hook, uint8_t clampHeight);
    // 0x002fefb8 CKHkS08Hero_FindAbilityMecaTarget_maybe: the best scored active actor (the meca group's list) of the
    // classes `mask` selects (0: any) into +0x12c (1 and its score), else +0x1b0c cleared (0).
    uint8_t FindAbilityMecaTarget(IKSerializable* aim, const CVector3* direction, float* score, uint32_t mask);
    // 0x002ff6c8 CKHkS08Hero_AcquireAbilityTarget_maybe: an aim-cone enemy and a meca actor, the better weighted one kept.
    uint8_t AcquireAbilityTarget(float enemyWeight, float mecaWeight, IKSerializable* aim, const CVector3* direction,
                                 uint32_t mask);
    // 0x002ff978 CKHkS08Hero_ValidateOrAcquireTarget_maybe: the target kept or a new one taken (1 with one).
    uint8_t ValidateOrAcquireTarget();
    // 0x002fe200 CKHkS08Hero_ComputeLungeScale_maybe: the signed pitch (radians) of the lunge towards the target.
    float ComputeLungeScale();
    // 0x003006f0 CKHkS08Hero_ComputeFinisherCameraVector_maybe: `direction` turned by the angles (degrees).
    CVector3 ComputeFinisherCameraVector(float zDegrees, float yDegrees, float xDegrees, const CVector3* direction,
                                         uint8_t flat);
    // DOTD: the lunge start StartLungeFromMark 0x3008d8 inlines.
    void StartLunge(class CKS08HeroBlow* blow);
    // The partner's combat AI.
    uint8_t IsGrabComboKind() const { return m_unk1abd != 0 ? 1 : m_unk1ac3; }  // 0x002fc208 CKHkS08Hero_IsGrabComboKind
    // The combo system (outputs/ability-analysis/combat.md): the current node +0x1a88 (+0x1a8c when idle), its blow.
    uint8_t IsAnimFinished(int32_t anim) const;                              // 0x003013c8 (CKHkS08Hero_3.cpp)
    float GetComboAnimSpeed();                                               // 0x0032bee8 (CKHkS08Hero_13.cpp)
    static float ComputeSoundPitchFromAnimSpeed(float speed);                // 0x00333688 (CKHkS08Hero_15.cpp)
    uint8_t ConsumeAttackCredits();                                          // 0x0033f9e8 (CKHkS08Hero_16.cpp)
    void GrantPartnerAttackCredits();                                        // 0x0033fa78 (CKHkS08Hero_16.cpp)
    void SetupHitSphere(float radius, uint8_t enable, int8_t hotspot, IKSerializable* damage);  // 0x0030cc40 (_6)
    void ArmPendingHitSpheres();                                             // 0x0030e990 (_6)
    void UpdateComboHitSpheres();                                            // 0x0030f220 (_6)
    void AttachVolumeToHotspot(IKBoundingVolume* volume, int32_t hotspot, float radius);       // 0x00352f78 (_18)
    // 0x00335158 CKHkS08Hero_UpdateSwingTrails (vt+0x110, CKHkS08Hero_15.cpp): the swing trails A (+0xedc bit 0x20; the
    // trails +0x5c[0] / [1]) and B (bit 0x40; [2] / [3]) switched on or off with their ribbons, +0x1ad2 / +0x1ad3 the
    // state, +0x1ad4 / +0x1ad8 the particle index (the dragon / element table, or next to the other trail's).
    void UpdateSwingTrails();
    // 0x0030ec40 CKHkS08Hero_SetupTrailHitSpheres2 / 0x0030ee78 _SetupTrailHitSpheres4_maybe (CKHkS08Hero_6.cpp): the
    // attack volumes off, the first two (four) hung under the given hot spots with `radius` and `damage`; two (four)
    // spheres requested (+0xec4 bit 0x40 / 0x80).
    void SetupTrailHitSpheres2(float radius, class CSGHotSpot* a, class CSGHotSpot* b, IKSerializable* damage);
    void SetupTrailHitSpheres4(float radius, class CSGHotSpot* a, class CSGHotSpot* b, class CSGHotSpot* c, class CSGHotSpot* d,
                               IKSerializable* damage);
    void AdvanceCombo();                                                     // 0x0032d890 (CKHkS08Hero_14.cpp)
    void SetComboActive(uint8_t active, uint8_t kind);                       // 0x0032d9b0 (CKHkS08Hero_14.cpp)
    void DropGrabbedEnemy();                                                 // 0x002fc600 (CKHkS08Hero_3.cpp)
    void BreakGrabAndRecoil();                                               // 0x002fce90 (_3)
    uint8_t IsGrabTargetInRange();                                           // 0x002fd5b0 (_3)
    void StartGrab();                                                        // 0x002ffc80 (_3)
    void TryGrabTarget();                                                    // 0x002fff48 (_3)
    void ThrowGrabbedEnemy(IKSerializable* blow);                            // 0x00300010 (_3)
    void TryStartFinisherCamera();                                           // 0x0032d6b0 (CKHkS08Hero_14.cpp)
    // 0x00364ab0 CKHkS08Hero_GetAITarget_maybe: with `attack` +0x124 else +0x12c, without +0x120 else +0x128.
    IKSerializable* GetAITarget(uint8_t attack) const {
        if (attack != 0) return m_pTargetedEnemy != nullptr ? m_pTargetedEnemy : m_pTargetedMecaHook;
        return m_unk120 != nullptr ? m_unk120 : m_unk128;
    }
    CVector3 GetAimDirection() const { return CVector3{m_unk135c, m_unk1360, m_unk1364}; }  // 0x0032a708 CopyAimDirection
    void AIClearAttackButtons() { m_unkf30 = 0; m_unkf1c = 0; }   // 0x0033fdb8
    void AIAcquireTargetIfCredits();                               // 0x0033fae0 (CKHkS08Hero_17.cpp)
    void AIUpdateCombatMovement(IKTime* clock);                    // 0x0033fb80
    void AIQueueAttack();                                          // 0x0033fdc8
    uint8_t CtlAICombat(IKTime* clock, int32_t phase, uint8_t other);  // 0x0033d000 CtlState3 (CKHkS08Hero_16.cpp)
    float GetMaxGroundSpeed() const;                                 // 0x002f94b0 (CKHkS08Hero_2.cpp)
    // 0x002f8958 FUN_002f8958 (CKHkS08Hero_2.cpp): the ground normal blend (a * weight + b * count) / (2 * weight).
    static CVector3 BlendGroundNormals(const CVector3* a, const CVector3* b, float weight, float count);
    // 0x002fbfc0 CKHkS08Hero_UpdateBodyTiltSprings_maybe (CKHkS08Hero_2.cpp): the body's up vector after the pitch and
    // roll springs followed `target`.
    CVector3 UpdateBodyTiltSprings(const CVector3* current, const CVector3* target);
    float GetHeightAboveGround();                                    // 0x0032a008 (CKHkS08Hero_12.cpp)
    void UpdateFlyingMovement(float dt);                             // 0x003141b0 (CKHkS08Hero_8.cpp)
    void UpdateClimbMovement(float dt);                              // 0x0031f6a8 (CKHkS08Hero_11.cpp)
    void UpdateClimbSustainedMovement(float dt);                     // 0x0031ff88 (CKHkS08Hero_11.cpp)
    void UpdateTakeOffToPartnerMovement(float dt);                   // 0x0031ce28 (CKHkS08Hero_10.cpp)
    void UpdateAnimationMarkFlags(float dt);                         // 0x00301640 (CKHkS08Hero_4.cpp)
    float ComputeLocomotionBlendWeight();                            // 0x00301fe0 (CKHkS08Hero_4.cpp)
    void UpdateLocomotionAnimationBlend(float dt, uint8_t enabled);  // 0x00309418 (CKHkS08Hero_4.cpp)
    void UpdateSideBlendAnims(float dt, uint8_t enabled);            // 0x003096f8 (CKHkS08Hero_4.cpp)

    // DOTD: the native targets of the PS3 pointers to member in the hero's state tables (k2000/core/Ps3MemberFn.h).
    // A handler gets the phase (0 update, 1 enter, 2 exit) and the other state (update: the current one, enter: the
    // state left, exit: the state entered) and returns the next state (update); a condition gets its row index.
    using StateHandlerFn = uint8_t (CKHkS08Hero::*)(IKTime* clock, int32_t phase, uint8_t other);
    using StateConditionFn = uint8_t (CKHkS08Hero::*)(IKTime* clock, uint8_t row);
    uint8_t CallStateHandler(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallStateCondition(const uint32_t pair[2], IKTime* clock, uint8_t row);
    // The CKSrvDynamic hooks (PostLoad's RegisterHook): a physics time step each.
    using DynamicHookFn = void (CKHkS08Hero::*)(float step);
    void CallDynamicHook(const uint32_t pair[2], float step);
    // The transition and update blocks every state machine of the hero inlines (Ps3MemberFn calls through a table of
    // 8-byte handler pairs): leave `current` for `next`, then the current state's update and its answer.
    void SwitchState(const uint32_t* handlers, uint8_t& current, uint8_t next, IKTime* clock);
    void RunState(const uint32_t* handlers, uint8_t& current, IKTime* clock);

    // The control machine's states (0xc4b1e0) and conditions.
    uint8_t CtlInactive(IKTime* clock, int32_t phase, uint8_t other);           // 0x00367fc0 (CKHkS08Hero_19.cpp)
    uint8_t CtlInactiveCondition(IKTime* clock, uint8_t row);                   // 0x00367f50
    uint8_t CtlPlayer(IKTime* clock, int32_t phase, uint8_t other);             // 0x00367ff8
    uint8_t CtlPlayerCondition(IKTime* clock, uint8_t row);                     // 0x00368158
    uint8_t CtlPlayerFollowsFocusCondition(IKTime* clock, uint8_t row);         // 0x00368178
    uint8_t CtlScriptedMoveToCondition(IKTime* clock, uint8_t row);             // 0x00367f58
    uint8_t CtlControlLockedCondition(IKTime* clock, uint8_t row);              // 0x00367f98
    uint8_t CtlAIWarpToCatchUpPointCondition(IKTime* clock, uint8_t row);       // 0x0033caa0 (CKHkS08Hero_16.cpp)
    uint8_t CtlAIPickCatchUpPointCondition(IKTime* clock, uint8_t row);         // 0x0033cab0
    uint8_t CtlAICombatCondition(IKTime* clock, uint8_t row);                   // 0x0033d250
    uint8_t CtlAIClimbingCondition(IKTime* clock, uint8_t row);                 // 0x0033d330
    uint8_t CtlAIFollowFlyingCondition(IKTime* clock, uint8_t row);             // 0x0033d570
    uint8_t CtlAIFollowGroundCondition(IKTime* clock, uint8_t row);             // 0x0033d428
    uint8_t CtlAIFollowGround(IKTime* clock, int32_t phase, uint8_t other);     // 0x0033e600
    // The action machine's (0xc4b3fc).
    uint8_t ActFreeMovement(IKTime* clock, int32_t phase, uint8_t other);       // 0x00364a30 (IKHkHero_2.cpp)
    uint8_t ActGroundCombo(IKTime* clock, int32_t phase, uint8_t other);        // 0x00330528 ActState11 (_14)
    uint8_t ActGroundGrabCombo(IKTime* clock, int32_t phase, uint8_t other);    // 0x00332078 ActState7 (_14)
    uint8_t ActGroundAltCombo(IKTime* clock, int32_t phase, uint8_t other);     // 0x0032fce0 ActState10 (_14)
    uint8_t ActClimbCombo(IKTime* clock, int32_t phase, uint8_t other);         // 0x0032e820 ActState9 (_14)
    uint8_t ActFlyingCombo(IKTime* clock, int32_t phase, uint8_t other);        // 0x0032f470 ActState8 (_14)
    // DOTD: the pieces the three combo rows above inline (_14).
    bool ComboLaunchEndsInSlam();
    bool ComboSlamEndsEarly(uint8_t kind);
    void ComboSlamShockwave();
    uint8_t ComboBlowStep(IKTime* clock, uint8_t kind, uint8_t other);
    uint8_t ActGrabDashCombo(IKTime* clock, int32_t phase, uint8_t other);      // 0x00331540 ActState6 (_14)
    uint8_t ActGrabSlamSeq(IKTime* clock, int32_t phase, uint8_t other);        // 0x00332a70 ActState5 (_14)
    uint8_t ActAbility(IKTime* clock, int32_t phase, uint8_t other);            // 0x003276d0 ActState4 (_12)
    void CancelAbilityA(uint8_t forced);                                        // 0x00326ee0 (_12)
    void CancelAbilityB(uint8_t forced);                                        // 0x003272d8 (_12)
    void CancelAbility(uint8_t forced);                                         // DOTD: their shared body
    uint8_t CanStartFury();                                                     // 0x00326830 (_12)
    void SetFuryMode(int32_t on);                                               // 0x00328e40 (_12)
    uint8_t IsTargetEnemyOnGround();                                            // 0x002fc6e0 (_14)
    void ReleaseGrabbedEnemyWithDamage(CKS08HeroBlow* blow);                    // 0x002fc720 (_14)
    uint8_t ActFreeMovementCondition(IKTime* clock, uint8_t row);               // 0x00364a28
    uint8_t ActHurtReactionCondition(IKTime* clock, uint8_t row);               // 0x0032d4c8 (CKHkS08Hero_13.cpp)
    uint8_t ActRecoveryCondition(IKTime* clock, uint8_t row);                   // 0x0032d4d0
    uint8_t ActFuryCoopCondition(IKTime* clock, uint8_t row);                   // 0x003267e8 (CKHkS08Hero_12.cpp)
    // 0x00326950 CKHkS08Hero_ActState1_FuryCoop_maybe (CKHkS08Hero_12.cpp): the fury's charge (see the definition).
    uint8_t ActFuryCoop(IKTime* clock, int32_t phase, uint8_t other);
    // 0x0033bf58 CKHkS08Hero_SpawnFuryChargeFx_maybe / 0x0033bbe0 CKHkS08Hero_SpawnFuryReleaseFx_maybe (CKHkS08Hero_15.cpp).
    void SpawnFuryChargeFx();
    void SpawnFuryReleaseFx();
    // DOTD: the fury node's geometry walk both inline: every geometry of the CNode `node` takes the alpha of `curve` at
    // `x` (evaluated per geometry; at most 0 is 0, at least 255 is opaque) and the translucent bit 11 of its properties
    // (vt+0x60 when it changes); a property bit 12 geometry of material mode 1..6 stays opaque.
    static void SetNodeAlphaFromCurve(IKSerializable* node, IKSerializable* curve, float x);
    // The combo and death conditions (CKHkS08Hero_14.cpp).
    uint8_t ActGroundComboCondition(IKTime* clock, uint8_t row);                // 0x0032e158 ActState11
    uint8_t ActGrabSlamSeqCondition(IKTime* clock, uint8_t row);                // 0x0032e378 ActState5
    uint8_t ActClimbComboCondition(IKTime* clock, uint8_t row);                 // 0x0032e3d0 ActState9
    uint8_t ActFlyingComboCondition(IKTime* clock, uint8_t row);                // 0x0032e488 ActState8
    uint8_t ActGroundAltComboCondition(IKTime* clock, uint8_t row);             // 0x0032e668 ActState10
    uint8_t ActGrabDashComboCondition(IKTime* clock, uint8_t row);              // 0x0032eb80 ActState6
    uint8_t ActGroundGrabComboCondition(IKTime* clock, uint8_t row);            // 0x0032ecc0 ActState7
    uint8_t ActDeadCondition(IKTime* clock, uint8_t row);                       // 0x0032f170 ActState0
    uint8_t ActAbilityCondition(IKTime* clock, uint8_t row);                    // 0x00326498 ActState4 (CKHkS08Hero_12.cpp)
    // UpdateHeroStatusAndTimedDamage's steps after the armour.
    void ApplyTimedHeroDamage(float dt);                                        // 0x002fed80 (CKHkS08Hero_3.cpp)
    void ApproachField1108AndNotifyCamera();                                    // 0x0032e028 (CKHkS08Hero_14.cpp)
    void ApplyGrabbedEnemyMarkDamage();                                         // 0x0032edd0
    void InitFlightField1D9CBlock();                                            // 0x0032f048
    void SpawnShockwave(uint8_t kind, const CVector3* position);               // 0x0033c688 (CKHkS08Hero_15.cpp)
    // The locomotion machine's (0xc4b398).
    uint8_t LocoGround(IKTime* clock, int32_t phase, uint8_t other);            // 0x00319a10 (CKHkS08Hero_9.cpp)
    uint8_t LocoGroundCondition(IKTime* clock, uint8_t row);                    // 0x00317e90
    uint8_t LocoFlyingCondition(IKTime* clock, uint8_t row);                    // 0x00313780 (CKHkS08Hero_8.cpp)
    uint8_t LocoClimbSustainedCondition(IKTime* clock, uint8_t row);            // 0x0031e1e8 (CKHkS08Hero_11.cpp)
    uint8_t LocoClimbCondition(IKTime* clock, uint8_t row);                     // 0x0031f2a0
    uint8_t LocoTakeOffToPartnerCondition(IKTime* clock, uint8_t row);          // 0x00317e68 (CKHkS08Hero_9.cpp)
    // The animation machine's (0xc4b2bc).
    uint8_t AnimLocomotionGround(IKTime* clock, int32_t phase, uint8_t other);  // 0x0030aa78 (CKHkS08Hero_5.cpp)
    uint8_t AnimComboAnim(IKTime* clock, int32_t phase, uint8_t other);         // 0x0032cb98 AnimState7 (_13)
    uint8_t AnimHurt(IKTime* clock, int32_t phase, uint8_t other);              // 0x0032c628 AnimState4 (_13)
    uint8_t AnimGuardedHurt(IKTime* clock, int32_t phase, uint8_t other);       // 0x0032c780 AnimState3 (_13)
    uint8_t AnimFury(IKTime* clock, int32_t phase, uint8_t other);              // 0x0032c268 AnimState1 (_13)
    uint8_t AnimDead(IKTime* clock, int32_t phase, uint8_t other);              // 0x0032c380 AnimState0 (_13)
    uint8_t AnimAbility(IKTime* clock, int32_t phase, uint8_t other);           // 0x0032c520 AnimState6 (_13)
    uint8_t AnimHurtType1(IKTime* clock, int32_t phase, uint8_t other);         // 0x0032c950 AnimState2 (_13)
    uint8_t ActDead(IKTime* clock, int32_t phase, uint8_t other);               // 0x003332c0 ActState0 (_14)
    void AdvanceAnimTimeUnlessMarkOverride(float dt);                           // 0x00301408 (_4)
    uint8_t AnimRecovery(IKTime* clock, int32_t phase, uint8_t other);          // 0x0032c170 AnimState5 (_13)
    uint8_t ActHurtReaction(IKTime* clock, int32_t phase, uint8_t other);       // 0x00330fe8 ActState2 (_14)
    uint8_t ActRecovery(IKTime* clock, int32_t phase, uint8_t other);           // 0x0032f268 ActState3 (_14)
    void UpdateComboTimeScale();                                                // 0x0032bc10 (_13)
    uint8_t AnimLocomotionGroundCondition(IKTime* clock, uint8_t row);          // 0x003024d0 (CKHkS08Hero_4.cpp)
    uint8_t AnimLocomotionClimbCondition(IKTime* clock, uint8_t row);           // 0x003024a8
    uint8_t AnimLocomotionFlyingCondition(IKTime* clock, uint8_t row);          // 0x003024f8
    uint8_t IsComboActive(IKTime* clock, uint8_t row);                          // 0x0032bb30 (CKHkS08Hero_13.cpp)
    uint8_t AnimHurtCondition(IKTime* clock, uint8_t row);                      // 0x0032bb58
    uint8_t AnimHurtType1Condition(IKTime* clock, uint8_t row);                 // 0x0032bb60
    uint8_t AnimFuryCondition(IKTime* clock, uint8_t row);                      // 0x0032bbc0
    uint8_t AnimRecoveryCondition(IKTime* clock, uint8_t row);                  // 0x0032bc08
    uint8_t AnimDeadCondition(IKTime* clock, uint8_t row);                      // 0x0032bed8
    uint8_t AnimAbilityCondition(IKTime* clock, uint8_t row);                   // 0x0032c130
    uint8_t AnimGuardedHurtCondition(IKTime* clock, uint8_t row);               // 0x0032c5e0
    uint8_t IsAbilityActive();                                                  // 0x002fc228 (CKHkS08Hero_2.cpp)
    // The ground animation sub-machine's states (+0x18d4).
    uint8_t GroundAnimState00(IKTime* clock, int32_t phase, uint8_t other);     // 0x00304a30 (CKHkS08Hero_4.cpp)
    // ---- step 6 ANIM: the flying / climbing animation states and their sub-machines (CKHkS08Hero_4.cpp). ----
    uint8_t AnimLocomotionFlying(IKTime* clock, int32_t phase, uint8_t other);  // 0x0030a518
    uint8_t AnimLocomotionClimb(IKTime* clock, int32_t phase, uint8_t other);   // 0x0030a0d8
    // The flying animation sub-machine's states (+0x183c).
    uint8_t FlyAnimState00(IKTime* clock, int32_t phase, uint8_t other);        // 0x003059d0 Anim30_37
    uint8_t FlyAnimState01(IKTime* clock, int32_t phase, uint8_t other);        // 0x00305d20 Anim33_36
    uint8_t FlyAnimState02(IKTime* clock, int32_t phase, uint8_t other);        // 0x00306028 Anim3A_3D
    uint8_t FlyAnimState03(IKTime* clock, int32_t phase, uint8_t other);        // 0x00307cf8 Anim45_46
    uint8_t FlyAnimState04(IKTime* clock, int32_t phase, uint8_t other);        // 0x00307ac8 Anim44
    uint8_t FlyAnimState05(IKTime* clock, int32_t phase, uint8_t other);        // 0x00302808 Anim43
    uint8_t FlyAnimState06(IKTime* clock, int32_t phase, uint8_t other);        // 0x00303d48 Anim3E_3F
    uint8_t FlyAnimState07(IKTime* clock, int32_t phase, uint8_t other);        // 0x00302fe0 Anim40
    uint8_t FlyAnimState08(IKTime* clock, int32_t phase, uint8_t other);        // 0x00308028 Anim5B
    uint8_t FlyAnimState09(IKTime* clock, int32_t phase, uint8_t other);        // 0x00302de0 Anim47_4B
    uint8_t FlyAnimState10(IKTime* clock, int32_t phase, uint8_t other);        // 0x003026f8 Anim48
    uint8_t FlyAnimState11(IKTime* clock, int32_t phase, uint8_t other);        // 0x003025f8 Anim49
    uint8_t FlyAnimState12(IKTime* clock, int32_t phase, uint8_t other);        // 0x00302c98 Anim4A
    uint8_t FlyAnimState13(IKTime* clock, int32_t phase, uint8_t other);        // 0x00304090 NoAnim
    uint8_t FlyAnimState14(IKTime* clock, int32_t phase, uint8_t other);        // 0x00302bb0 Anim52
    uint8_t FlyAnimState15(IKTime* clock, int32_t phase, uint8_t other);        // 0x003083d0 NoAnim
    uint8_t FlyAnimState16(IKTime* clock, int32_t phase, uint8_t other);        // 0x00304d00 NoAnim
    uint8_t FlyAnimState17(IKTime* clock, int32_t phase, uint8_t other);        // 0x003081a0 Anim55
    // The climbing animation sub-machine's states (+0x1964).
    uint8_t ClimbAnimState00(IKTime* clock, int32_t phase, uint8_t other);      // 0x00303878 NoAnim
    uint8_t ClimbAnimState01(IKTime* clock, int32_t phase, uint8_t other);      // 0x003054e0 Anim5F_65_67_63
    uint8_t ClimbAnimState02(IKTime* clock, int32_t phase, uint8_t other);      // 0x003068e0 Anim8B
    uint8_t ClimbAnimState03(IKTime* clock, int32_t phase, uint8_t other);      // 0x00306708 NoAnim
    uint8_t ClimbAnimState04(IKTime* clock, int32_t phase, uint8_t other);      // 0x003047a8 NoAnim
    uint8_t ClimbAnimState05(IKTime* clock, int32_t phase, uint8_t other);      // 0x00309e68 Anim87_88
    uint8_t ClimbAnimState06(IKTime* clock, int32_t phase, uint8_t other);      // 0x00303698 NoAnim
    uint8_t ClimbAnimState07(IKTime* clock, int32_t phase, uint8_t other);      // 0x00306cf0 Anim8C
    // ---- step 4 ANIM: the rest of the ground animation sub-machine and the animation helpers (CKHkS08Hero_4.cpp). ----
    uint8_t GroundAnimState01(IKTime* clock, int32_t phase, uint8_t other);     // 0x00306538 Anim09
    uint8_t GroundAnimState02(IKTime* clock, int32_t phase, uint8_t other);     // 0x00306368 Anim0C
    uint8_t GroundAnimState03(IKTime* clock, int32_t phase, uint8_t other);     // 0x00303168 Anim13
    uint8_t GroundAnimState04(IKTime* clock, int32_t phase, uint8_t other);     // 0x00303448 Anim10_11
    uint8_t GroundAnimState05(IKTime* clock, int32_t phase, uint8_t other);     // 0x003076c0 Anim18_23
    uint8_t GroundAnimState06(IKTime* clock, int32_t phase, uint8_t other);     // 0x003072b8 Anim18_23
    uint8_t GroundAnimState07(IKTime* clock, int32_t phase, uint8_t other);     // 0x00304dc8 Anim19
    uint8_t GroundAnimState08(IKTime* clock, int32_t phase, uint8_t other);     // 0x003029f8 NoAnim
    uint8_t GroundAnimState09(IKTime* clock, int32_t phase, uint8_t other);     // 0x00302520 Anim1D
    uint8_t GroundAnimState10(IKTime* clock, int32_t phase, uint8_t other);     // 0x003050d0 Anim1B_1C
    uint8_t GroundAnimState11(IKTime* clock, int32_t phase, uint8_t other);     // 0x00308f48 Anim26_27_2A
    uint8_t GroundAnimState12(IKTime* clock, int32_t phase, uint8_t other);     // 0x003089f8 NoAnim
    uint8_t GroundAnimState13(IKTime* clock, int32_t phase, uint8_t other);     // 0x00308778 AnimD1
    uint8_t GroundAnimState14(IKTime* clock, int32_t phase, uint8_t other);     // 0x00307110 Anim30
    uint8_t GroundAnimState15(IKTime* clock, int32_t phase, uint8_t other);     // 0x00306fc0 Anim8F
    uint8_t GroundAnimState16(IKTime* clock, int32_t phase, uint8_t other);     // 0x00306e50 Anim90
    // 0x00301e70: the animation time on by `dt` scaled by `speed / reference`; with `toEnd`, a step past the end of the
    // animation skips to its end instead (vt+0x18c).
    void AdvanceAnimScaled(float dt, float reference, float speed, uint32_t toEnd);
    void SkipAnimToEnd();                                                       // vt+0x18c 0x00301550
    void SkipAnimToEndBase();                                                   // 0x00351450 (CKHkS08Hero_18.cpp)
    // 0x0032aec8 (CKHkS08Hero_12.cpp): with +0x358 bit 1, the root slot cut (+0x360 bit 11) and the pair set on the slot.
    void SetAnimPairAndWeight(float start1, float start2, float weight, uint32_t word1, uint32_t word2);
    // ---- step 4 ANIM: the hero's sounds (CKHkS08Hero_15.cpp, CKHkS08Hero_2.cpp, CKHkS08Hero_19.cpp). ----
    // 0x003336c0: 0 plain, 1 / 2 / 3 the surfaces of the ground's properties 0x1000 / 0x2000 / engine flag 2, 4 climbing.
    uint8_t GetFootstepSurfaceType();
    // 0x00333fc8: sound `index` of the hero's dictionary (+0x168) with the pitch clamped to [0.5, 2] and the volume (times
    // the group's +0x204 for a hero that is not the tracked leader, with `scaled`); started unless already playing
    // (`restart`: always).
    void PlaySoundIfIdle(float volume, float pitch, uint32_t index, uint32_t scaled, uint32_t restart);
    void PlaySoundIfIdleThunk(float volume, float pitch, uint32_t index, uint32_t scaled);  // 0x00334108 (restart 1)
    void PlaySound(float volume, float pitch, uint32_t index, uint32_t scaled);  // 0x00334188 (restarted when playing)
    void StopSound(uint32_t index);                                  // 0x003343d8
    void PlayFootstepSounds(IKTime* clock);                          // vt+0x118 0x00334110 -> 0x002fa928 (CKHkS08Hero_2.cpp)
    void PlayMovementEventSounds(IKTime* clock);                     // 0x00366098 (CKHkS08Hero_19.cpp)
    void UpdateFootstepFx(IKTime* clock);                            // 0x00366ba8 (CKHkS08Hero_19.cpp)
    void UpdateMainShadowAndSurfaceFx(IKTime* clock);                // 0x003670f8 (CKHkS08Hero_19.cpp)
    void UpdateShadowsAndFlightFx();                                 // vt+0x11c 0x0033a050 (CKHkS08Hero_15.cpp)
    void UpdateTrailAndFootstepFx();                                 // vt+0x10c 0x00336598 (CKHkS08Hero_15.cpp)
    void UpdatePartnerLinkFx(uint32_t active);                       // 0x00339050 (CKHkS08Hero_15.cpp)
    void UpdateTriggeredExplosionFxAndVibration();                   // 0x00338458 (CKHkS08Hero_15.cpp)
    void UpdateShadowGroundPoint();                                  // 0x00365c00 (CKHkS08Hero_19.cpp)

    // Movement-mode accessors (CKHkS08Hero_17.cpp).
    uint8_t IsMovementMode0();                                       // 0x00340178 CKHkS08Hero_IsMovementMode0
    uint8_t IsFlyingMovementMode1();                                 // 0x00340188 CKHkS08Hero_IsFlying_MovementMode1
    uint8_t IsClimbingMovementMode2();                               // 0x003401a0 CKHkS08Hero_IsClimbing_MovementMode2
    uint8_t GetMovementMode();                                       // 0x003401b8 CKHkS08Hero_GetMovementMode
    CKHkS08Hero* GetControllingHero();                               // 0x00344e68 (k2000/logic/CKControlableHero.cpp)
    uint8_t ShouldJoinPartnerFlight();                               // 0x00341fa0 (CKHkS08Hero_17.cpp)
    uint8_t ShouldStayClimbing();                                    // 0x00342fa8 (CKHkS08HeroCameraTarget.cpp)
    void SetMovementMode(uint8_t mode);                              // 0x00340c18 (CKHkS08Hero_17.cpp)
    void UpdateSlopeAngleAndFlagEC8Bit24();                          // 0x002f9540 (CKHkS08Hero_2.cpp)
    void ComputeCameraRelativeMove();                                // 0x00311df0 (CKHkS08Hero_7.cpp)
    void ApplyPartnerTetherToVelocity();                             // 0x003105d8 (CKHkS08Hero_7.cpp)
    // ---- step 6 FLY: flying and taking off to the partner (CKHkS08Hero_8.cpp, CKHkS08Hero_10.cpp, _7, _17). ----
    uint8_t LocoFlying(IKTime* clock, int32_t phase, uint8_t other);            // 0x00315088 (CKHkS08Hero_8.cpp)
    uint8_t LocoTakeOffToPartner(IKTime* clock, int32_t phase, uint8_t other);  // 0x0031b658 (CKHkS08Hero_10.cpp)
    void UpdateFlyingLocomotion(float dt);                           // 0x003167e0 (frame hook, flying)
    void UpdateFlightAltitudeAndProbes();                            // 0x00312bb0
    void DynamicStage1Flying(float dt);                              // 0x00315d60 (each fixed sub-step)
    CVector3 ComputeFlightGravityAccel();                            // 0x00313340
    CVector3 ComputeFlightDragForce();                               // 0x003137f8
    CVector3 ComputeFlightDashImpulse(float dt);                     // 0x00313a48
    CVector3 ComputeFlightField13D8Displacement(float dt);           // 0x00313d20
    CVector3 ComputeFlightThrustForce(float dt);                     // 0x00313f50
    CVector3 ComputeFlightTargetHeightForce();                       // 0x00314b58
    // 0x00314dc8: `callerF27` is the caller's f27 (DynamicStage1Flying's mass) the original reads uninitialised.
    CVector3 ComputeFlightAuxForce(float callerF27);
    CVector3 ComputeFlightInputForce(float dt);                      // 0x00315970
    void AccumulateFlightDisplacement(float dt);                     // 0x00312f98
    void TryStartFlightDash();                                       // 0x00310ef0 (CKHkS08Hero_7.cpp)
    void UpdateTakeOffToPartnerLocomotion(float dt);                 // 0x0031b8c8 (CKHkS08Hero_10.cpp)
    CVector3 ComputeTakeOffToPartnerVelocity();                      // 0x0031c4d8
    void DynamicStage1TakeOffToPartner(float dt);                    // 0x0031c788
    void AccumulateVelocityDisplacement(float dt);                   // 0x0031b450
    // ---- step 4 DYN: the dynamics (CKSrvDynamic hooks, forces, ground locomotion), navigation checks. ----
    // A word the hero code reads with lfs (a member typed uint32_t until its users are ported), as a float.
    template <class T>
    static float AsF32(const T& word) {
        static_assert(sizeof(T) == 4, "a 32-bit member");
        float value;
        std::memcpy(&value, &word, 4);
        return value;
    }
    float GetMass();                                                 // 0x002f8818 (CKHkS08Hero_2.cpp)
    void SetMovementModeUnlessLocked(uint8_t mode);                  // 0x00342ef8 (CKHkS08Hero_17.cpp)
    // DOTD: CKSrvDynamic's native dispatcher of the hero's entry (CallDynamicHook).
    static void DispatchDynamicHook(IKSerializable* object, const uint32_t pair[2], float step);
    CVector3 ComputeGroundBrakeForce(float speed);                   // 0x003174b0
    CVector3 ComputeGroundInputForce(float dt, const CVector3* force);  // 0x00317658
    void AccumulateGroundDisplacement(float dt);                     // 0x00317cc0
    CVector3 ComputeJumpImpulseForce(float dt);                      // 0x00318538
    CVector3 ComputeGroundRunForce();                                // 0x00319110
    void DynamicStage1Ground(float dt);                              // 0x00319420
    void UpdateGroundLocomotionState();                              // 0x0031a040
    // A word the hero code writes with stfs (a member typed uint32_t until its users are ported).
    template <class T>
    static void SetF32(T& word, float value) {
        static_assert(sizeof(T) == 4, "a 32-bit member");
        std::memcpy(&word, &value, 4);
    }
    // The CKSrvDynamic hooks (CKHkS08Hero_7.cpp): each fixed sub-step, the frame's remainder, once per frame.
    void DynamicStage1ByMode(float dt);                              // 0x0030f778
    void DynamicStage3PredictPosition(float dt);                     // 0x0030ffa0
    void UpdateLocomotionByMode(float dt);                           // 0x00310708
    void DynamicStageTail(float dt, int32_t fixedStep);              // 0x003046a8 (CKHkS08Hero_4.cpp)
    void GetAnimParams13to18(float* out, int32_t animation);         // 0x00303a78 (CKHkS08Hero_4.cpp)
    CVector3 ScaleVec3(float scale, const CVector3* v) const;        // 0x0030f8c0
    CVector3 GetGameManagerExternalForce() const;                    // 0x0030f8f0
    CVector3 AccelToForce(float mass, const CVector3* accel) const;  // 0x0030fb68
    CVector3 AccelToVelocityDelta(float dt, const CVector3* accel) const;  // 0x0030fb98
    CVector3 GetExternalDisplacement() const;                        // 0x0030fe18
    // step 4 (AI-GRP; CKHkS08Hero_12.cpp): the hero group's tether pull (+0x1674 its flag, +0x1668 the
    // displacement) and the pair geometry's inputs (+0x54c + +0x1268, +0x127c).
    void SetExternalDisplacementFlag(uint8_t on);                    // 0x00329d88
    void SetExternalDisplacement(const CVector3* displacement);      // 0x0032a6e8
    CVector3 GetDerivedVelocity() const;                             // 0x0032a730 CKHkS08Hero_GetPredictedVelocity_maybe
    CVector3 GetAdjustedPosition() const;                            // 0x0032a758 CopyHeroAdjustedPosition
    CVector3 ComputePartnerTetherDampingForce(float radius, float coeff);  // 0x0030fe70
    float UpdateAndGetField11C8();                                   // 0x00310330
    CVector3 ComputePartnerTetherSpringForce(float radius, float unused);  // 0x003103f0
    // 0x00310888 (replaces the earlier `void ComputePairedHotspotCollisionResponse()`): LocoState4_Ground passes +0xa44
    // and stores the result at +0x17fc.
    CVector3 ComputePairedHotspotCollisionResponse(float stiffness);
    CVector3 ForceToAccel(float unused, float mass, const CVector3* force) const;  // 0x00310ba8
    void UpdateForwardAndSpeedStats();                               // 0x00310d88
    void ProbeGroundAndUpdateLocomotionFlags();                      // 0x003110a8
    CVector3 ComputeTimedAnimDisplacement(float dt);                 // 0x00311950
    CVector3 ClampDragToStopVelocity(float dt, const CVector3* drag, const CVector3* velocity);  // 0x00311c50
    void ComputeLungeOffset();                                       // 0x002fe3a8 (CKHkS08Hero_3.cpp)
    CVector3 StartLungeFromMark(float dt);                           // 0x003008d8 (CKHkS08Hero_3.cpp)
    CVector3 ComputeExternalPushForce(float dt);                     // 0x003011c8 (CKHkS08Hero_3.cpp)
    IKSerializable* GetHotSpot(uint8_t index);                       // 0x00361b70 (IKHkHero_2.cpp)
    uint32_t GetNavTransitionFlag2IfAllowed(int16_t from, int16_t to);  // 0x00369f40 (CKHkS08Hero_19.cpp)
    // 0x0036a2f8 (CKHkS08Hero_19.cpp): 1 when the hero may stand at `point` (snapped to the ground into `contact`).
    uint8_t ValidateNavPosition(CGroundContactDatasInOut* contact, CPFPoint* point, const CPFCharacter* character,
                                int32_t sameSector, uint8_t* raised);
    IKSerializable* GetGroundInfo();                                 // 0x00361b68 (IKHkHero_2.cpp): the current ground
    // 0x00363c40 CKHkS08Hero_GetGroundObject_maybe (IKHkHero_2.cpp): the current ground of a hero not in the air
    // (+0x354 bit 0) nor attached (+0x35c bit 8), else null.
    IKSerializable* GetGroundObject() const {
        if ((m_ui32HeroFlags354 & 1u) != 0 || (m_ui32HeroFlags35C & 0x100u) != 0) return nullptr;
        return m_gcCurDatasInOut.m_pGround;
    }
    CKHkS08Hero* GetPartnerHero();                                   // 0x002f85f8 (CKHkS08Hero_2.cpp)
    uint8_t GetByte1679();                                           // 0x002f85f0 (CKHkS08Hero_2.cpp)
    uint8_t PartnerShouldStayClimbing();                             // 0x002f8628 (CKHkS08Hero_2.cpp)
    uint8_t IsPartnerClimbFlagSet();                                 // 0x002f87e8 (CKHkS08Hero_2.cpp)
    // ---- step 6 CLIMB: the climb zones (+0x1690..+0x16a8, +0x16b0 / +0x16bc lists), the climbing locomotion and its
    // dynamics (CKHkS08Hero_11.cpp unless noted). ----
    uint8_t LocoClimbSustained(IKTime* clock, int32_t phase, uint8_t other);    // 0x00324780 LocoState1_ClimbSustained
    uint8_t LocoClimb(IKTime* clock, int32_t phase, uint8_t other);             // 0x0031f318 LocoState2_Climb
    uint8_t CtlAIClimbing(IKTime* clock, int32_t phase, uint8_t other);         // 0x0033f080 (CKHkS08Hero_16.cpp)
    void UpdateClimbMountState();                                               // 0x00324190
    void UpdateClimbZoneAttachment(float dt);                                   // 0x0031ea00
    CMatrix34 BlendClimbAttachMatrix(const CMatrix34* from, const CMatrix34* to);  // 0x002f9bd8 (CKHkS08Hero_2.cpp)
    float GetClimbSpeed();                                                      // 0x002f94d0 (CKHkS08Hero_2.cpp)
    CVector3 ComputeClimbMountOffset(CKHkClimbZone* zone, uint16_t animation);  // the two below
    CVector3 ComputeClimbMountOffset16B0();                                     // 0x0031e480
    CVector3 ComputeClimbMountOffset16BC();                                     // 0x0031e210
    void ApplyClimbMountAnimOffset();                                           // 0x0031e6f0
    uint8_t TryAttachToClimbZoneList(CKHkClimbZone** zones, uint32_t count);    // the two below
    uint8_t TryAttachToClimbZoneList16B0();                                     // 0x0031fd78
    uint8_t TryAttachToClimbZoneList16BC();                                     // 0x0031fb68
    void StickToCurrentClimbZone();                                             // 0x0031df00
    void BlendOrientationFromClimbSnapshot();                                   // 0x0031d8b8
    void TryClimbLeap();                                                        // 0x0031db40
    CVector3 ComputeClimbMoveVectorByMode(float dt);                            // 0x0031ef70
    CVector3 ComputeClimbDetachForce(float dt, const CVector3* force);          // 0x0031ece8
    uint32_t ClassifyClimbZoneApproach(const CVector3* at, const CVector3* right);  // 0x00321080
    CVector3 IntegrateClimbVelocity(float dt, float maxSpeed, const CVector3* direction);  // 0x00321438
    void UpdateClimbDisplacement(float dt);                                     // 0x00321948
    void DynamicStage1Climb(float dt);                                          // 0x00322518
    void AccumulateClimbDetachDisplacement(float dt);                           // 0x003229f8
    void DynamicStage1ClimbDetach(float dt);                                    // 0x00322d40
    void UpdateClimbSustainedLocomotion(float dt);                              // 0x00325108
    void UpdateClimbLocomotion(float dt);                                       // 0x00325c88
    void StartClimbFromInput();  // the climbing part of 0x003438b0 UpdateMovementModeFromInput (CKHkS08Hero_17.cpp)
    // ---- step 4 INPUT: the player's pad to the hero (ReadHeroPlayerInput and what it calls). ----
    void UpdateHeroActionInput();                                    // vt+0xe4 0x003445d8 (CKHkS08Hero_17.cpp)
    void UpdateButtonRecords();                                      // 0x003411d8 (CKHkS08Hero_17.cpp)
    void UpdateMovementModeFromInput();                              // 0x003438b0 (CKHkS08Hero_17.cpp)
    void UpdateGuardAndDodgeInput();                                 // 0x00342808 (CKHkS08Hero_17.cpp)
    void HandleAirborneActionCInput();                               // 0x003430a8 (CKHkS08Hero_17.cpp)
    void UpdateCarriedPowerBucketGroundTrigger();                    // 0x00340a20 (CKHkS08Hero_17.cpp)
    void UpdateFlightFlapImpulse();                                  // 0x003402a0 (CKHkS08Hero_17.cpp)
    void UpdateHeroHealthAndManaSharing(float dt);                   // 0x003408f8 (CKHkS08Hero_17.cpp)
    void TransferHeroManaToOtherDragon(float* elapsed);              // 0x003403f8 (CKHkS08Hero_17.cpp)
    IKSerializable* GetCarriedPowerBucket();                         // 0x003401f0 (CKHkS08Hero_17.cpp)
    void TransferHeroHealthToOtherDragon(float* elapsed);            // 0x003405f0 (CKHkS08Hero_17.cpp)
    void QueueAttackInputAndSelectElement();                         // 0x00330ab8 (CKHkS08Hero_14.cpp)
    uint8_t Vf144();                                                 // vt+0x144 0x00345080 (IKHkHero.cpp)

    uint32_t m_unk848;  // +0x848  (C2.2 strict3)
    uint32_t m_unk84c;  // +0x84c  (C2.2 strict3)
    uint32_t m_unk850;  // +0x850  (C2.2 strict3)
    float m_unk854;  // +0x854  (C2.2 strict3)
    float m_unk858;  // +0x858  (C2.2 strict3)
    float m_unk85c;  // +0x85c  (C2.2 strict3)
    float m_unk860;  // +0x860  (C2.2 strict3)
    float m_unk864;  // +0x864  (C2.2 strict3)
    float m_unk868;  // +0x868  (C2.2 strict3)
    float m_unk86c;  // +0x86c  (C2.2 strict3)
    float m_unk870;  // +0x870  (C2.2 strict3)
    uint32_t m_unk874;  // +0x874  (C2.2 strict3)
    float m_unk878;  // +0x878  (C2.2 strict3)
    float m_unk87c;  // +0x87c  (C2.2 strict3)
    float m_unk880;  // +0x880  (C2.2 strict3)
    float m_unk884;  // +0x884  (C2.2 strict3)
    uint32_t m_unk888;  // +0x888  (C2.2 strict3)
    float m_unk88c;  // +0x88c  the frame's dt (UpdateCKHkS08Hero 0x2de920 stfs; Ghidra's field name flPositionY is wrong)
    float m_unk890;  // +0x890  (C2.2 spyro)
    float m_unk894;  // +0x894  (C2.2 spyro)
    uint32_t m_pad898;
    float m_unk89c;                              // +0x89c
    float m_unk8a0;                              // +0x8a0
    float m_unk8a4;                              // +0x8a4
    float m_unk8a8;                              // +0x8a8
    float m_unk8ac;                              // +0x8ac
    float m_unk8b0;                              // +0x8b0
    float m_unk8b4;                              // +0x8b4
    float m_unk8b8;                              // +0x8b8
    float m_unk8bc;                              // +0x8bc
    float m_unk8c0;                              // +0x8c0
    float m_unk8c4;                              // +0x8c4
    float m_unk8c8;                              // +0x8c8
    float m_unk8cc;                              // +0x8cc
    float m_unk8d0;                              // +0x8d0
    float m_unk8d4;                              // +0x8d4
    float m_unk8d8;                              // +0x8d8
    float m_unk8dc;                              // +0x8dc
    float m_unk8e0;                              // +0x8e0
    float m_unk8e4;                              // +0x8e4
    float m_unk8e8;                              // +0x8e8
    float m_unk8ec;                              // +0x8ec
    float m_unk8f0;                              // +0x8f0
    float m_unk8f4;                              // +0x8f4
    float m_unk8f8;                              // +0x8f8
    float m_unk8fc;                              // +0x8fc
    float m_unk900;                              // +0x900
    float m_unk904;                              // +0x904
    float m_unk908;                              // +0x908
    float m_unk90c;                              // +0x90c
    float m_unk910;                              // +0x910
    float m_unk914;                              // +0x914
    float m_unk918;                              // +0x918
    float m_unk91c;                              // +0x91c
    float m_unk920;                              // +0x920
    float m_unk924;                              // +0x924
    float m_unk928;                              // +0x928
    float m_unk92c;                              // +0x92c
    float m_unk930;                              // +0x930
    uint32_t m_unk934;                           // +0x934
    float m_unk938;                              // +0x938
    float m_unk93c;                              // +0x93c
    float m_unk940;                              // +0x940
    float m_unk944;                              // +0x944
    float m_unk948;                              // +0x948
    float m_unk94c;                              // +0x94c
    float m_unk950;                              // +0x950
    float m_unk954;                              // +0x954
    float m_unk958;                              // +0x958
    float m_unk95c;                              // +0x95c
    float m_unk960;                              // +0x960
    float m_unk964;                              // +0x964
    float m_unk968;                              // +0x968
    float m_unk96c;                              // +0x96c
    float m_unk970;                              // +0x970
    float m_unk974;                              // +0x974
    float m_unk978;                              // +0x978
    float m_unk97c;                              // +0x97c
    float m_unk980;                              // +0x980
    float m_unk984;                              // +0x984
    float m_unk988;                              // +0x988
    float m_unk98c;                              // +0x98c
    float m_unk990;                              // +0x990
    float m_unk994;                              // +0x994
    float m_unk998;                              // +0x998
    float m_unk99c;                              // +0x99c
    float m_unk9a0;                              // +0x9a0
    float m_unk9a4;                              // +0x9a4
    float m_unk9a8;                              // +0x9a8
    float m_unk9ac;                              // +0x9ac
    float m_unk9b0;                              // +0x9b0
    float m_unk9b4;                              // +0x9b4
    float m_unk9b8;                              // +0x9b8
    float m_unk9bc;                              // +0x9bc
    float m_unk9c0;                              // +0x9c0
    float m_unk9c4;                              // +0x9c4
    float m_unk9c8;                              // +0x9c8
    float m_unk9cc;                              // +0x9cc
    float m_unk9d0;                              // +0x9d0
    float m_unk9d4;                              // +0x9d4
    float m_unk9d8;                              // +0x9d8
    float m_unk9dc;                              // +0x9dc
    float m_unk9e0;                              // +0x9e0
    float m_unk9e4;                              // +0x9e4
    float m_unk9e8;                              // +0x9e8
    float m_unk9ec;                              // +0x9ec
    float m_unk9f0;                              // +0x9f0
    float m_unk9f4;                              // +0x9f4
    float m_unk9f8;                              // +0x9f8
    float m_unk9fc;                              // +0x9fc
    float m_unka00;                              // +0xa00
    float m_unka04;                              // +0xa04
    float m_unka08;                              // +0xa08
    float m_unka0c;                              // +0xa0c
    float m_unka10;                              // +0xa10
    float m_unka14;                              // +0xa14
    float m_unka18;                              // +0xa18
    uint32_t m_unka1c;                           // +0xa1c
    float m_unka20;                              // +0xa20
    float m_unka24;                              // +0xa24
    float m_unka28;                              // +0xa28
    float m_unka2c;                              // +0xa2c
    float m_unka30;                              // +0xa30
    float m_unka34;                              // +0xa34
    float m_unka38;                              // +0xa38
    float m_unka3c;                              // +0xa3c
    float m_unka40;                              // +0xa40
    float m_unka44;                              // +0xa44
    int32_t m_unka48;                            // +0xa48
    float m_unka4c;                              // +0xa4c
    float m_unka50;                              // +0xa50
    float m_unka54;                              // +0xa54
    int32_t m_unka58;                            // +0xa58
    float m_unka5c;                              // +0xa5c
    float m_unka60;                              // +0xa60
    float m_unka64;                              // +0xa64
    float m_unka68;                              // +0xa68
    float m_unka6c;                              // +0xa6c
    float m_unka70;                              // +0xa70
    float m_unka74;                              // +0xa74
    float m_unka78;                              // +0xa78
    float m_unka7c;                              // +0xa7c
    float m_unka80;                              // +0xa80
    float m_unka84;                              // +0xa84
    float m_unka88;                              // +0xa88
    float m_unka8c;                              // +0xa8c
    float m_unka90;                              // +0xa90
    float m_unka94;                              // +0xa94
    float m_unka98;                              // +0xa98
    float m_unka9c;                              // +0xa9c
    float m_unkaa0;                              // +0xaa0
    float m_unkaa4;                              // +0xaa4
    float m_unkaa8;                              // +0xaa8
    float m_unkaac;                              // +0xaac
    uint8_t m_unkab0;                            // +0xab0
    uint8_t m_padab1[3];
    float m_unkab4;                              // +0xab4
    float m_unkab8;                              // +0xab8
    float m_unkabc;                              // +0xabc
    float m_unkac0;                              // +0xac0
    float m_unkac4;                              // +0xac4
    float m_unkac8;                              // +0xac8
    uint8_t m_unkacc;                            // +0xacc
    uint8_t m_padacd[3];
    float m_unkad0;                              // +0xad0
    float m_unkad4;                              // +0xad4
    float m_unkad8;                              // +0xad8
    float m_unkadc;                              // +0xadc
    float m_unkae0;                              // +0xae0
    float m_unkae4;                              // +0xae4
    float m_unkae8;                              // +0xae8
    float m_unkaec;                              // +0xaec
    float m_unkaf0;                              // +0xaf0
    float m_unkaf4;                              // +0xaf4
    float m_unkaf8;                              // +0xaf8
    float m_unkafc;                              // +0xafc
    float m_unkb00;                              // +0xb00
    float m_unkb04;                              // +0xb04
    float m_unkb08;                              // +0xb08
    float m_unkb0c;                              // +0xb0c
    float m_unkb10;                              // +0xb10
    float m_unkb14;                              // +0xb14
    float m_unkb18;                              // +0xb18
    float m_unkb1c;                              // +0xb1c
    float m_unkb20;                              // +0xb20
    float m_unkb24;                              // +0xb24
    float m_unkb28;                              // +0xb28
    float m_unkb2c;                              // +0xb2c
    float m_unkb30;                              // +0xb30
    float m_unkb34;                              // +0xb34
    float m_unkb38;                              // +0xb38
    float m_unkb3c;                              // +0xb3c
    float m_unkb40;                              // +0xb40
    float m_unkb44;                              // +0xb44
    float m_unkb48;                              // +0xb48
    float m_unkb4c;                              // +0xb4c
    float m_unkb50;                              // +0xb50
    float m_unkb54;                              // +0xb54
    float m_unkb58;                              // +0xb58
    float m_unkb5c;                              // +0xb5c
    float m_unkb60;                              // +0xb60
    float m_unkb64;                              // +0xb64
    float m_unkb68;                              // +0xb68
    float m_unkb6c;                              // +0xb6c
    float m_unkb70;                              // +0xb70
    float m_unkb74;                              // +0xb74
    float m_unkb78;                              // +0xb78
    float m_unkb7c;                              // +0xb7c
    float m_unkb80;                              // +0xb80
    float m_unkb84;                              // +0xb84
    float m_unkb88;                              // +0xb88
    float m_unkb8c;                              // +0xb8c
    float m_unkb90;                              // +0xb90
    float m_unkb94;                              // +0xb94
    uint32_t m_unkb98;                           // +0xb98
    float m_unkb9c;                              // +0xb9c
    uint32_t m_unkba0;                           // +0xba0
    float m_unkba4;                              // +0xba4
    float m_unkba8;                              // +0xba8
    float m_unkbac;                              // +0xbac
    float m_unkbb0;                              // +0xbb0
    uint32_t m_unkbb4;                           // +0xbb4
    float m_unkbb8;                              // +0xbb8
    float m_unkbbc;                              // +0xbbc
    float m_unkbc0;                              // +0xbc0
    float m_unkbc4;                              // +0xbc4
    float m_unkbc8;                           // +0xbc8
    float m_unkbcc;                           // +0xbcc
    float m_unkbd0;                              // +0xbd0
    float m_unkbd4;                              // +0xbd4
    float m_unkbd8;                              // +0xbd8
    float m_unkbdc;                              // +0xbdc
    float m_unkbe0;                              // +0xbe0
    float m_unkbe4;                              // +0xbe4
    float m_unkbe8;                              // +0xbe8
    float m_unkbec;                              // +0xbec
    float m_unkbf0;                              // +0xbf0
    float m_unkbf4;                              // +0xbf4
    float m_unkbf8;                              // +0xbf8
    float m_unkbfc;                              // +0xbfc
    float m_unkc00;                              // +0xc00
    float m_unkc04;                              // +0xc04
    float m_unkc08;                              // +0xc08
    float m_unkc0c;                              // +0xc0c
    float m_unkc10;                              // +0xc10
    float m_unkc14;                              // +0xc14
    float m_unkc18;                              // +0xc18
    float m_unkc1c;                              // +0xc1c
    float m_unkc20;                              // +0xc20
    float m_unkc24;                              // +0xc24
    float m_unkc28;                              // +0xc28
    float m_unkc2c;                              // +0xc2c
    float m_unkc30;                              // +0xc30
    float m_unkc34;                              // +0xc34
    float m_unkc38;                              // +0xc38
    float m_unkc3c;                              // +0xc3c
    float m_unkc40;                              // +0xc40
    float m_unkc44;                              // +0xc44
    float m_unkc48;                              // +0xc48
    float m_unkc4c;                              // +0xc4c
    float m_unkc50;                              // +0xc50
    float m_unkc54;                              // +0xc54
    float m_unkc58;                              // +0xc58
    float m_unkc5c;                              // +0xc5c
    float m_unkc60;                              // +0xc60
    float m_unkc64;                              // +0xc64
    float m_unkc68;                              // +0xc68
    float m_unkc6c;                              // +0xc6c
    float m_unkc70;                              // +0xc70
    float m_unkc74;                              // +0xc74
    float m_unkc78;                              // +0xc78
    float m_unkc7c;                              // +0xc7c
    float m_unkc80;                              // +0xc80
    float m_unkc84;                              // +0xc84
    float m_unkc88;                              // +0xc88
    float m_unkc8c;                              // +0xc8c
    float m_unkc90;                              // +0xc90
    float m_unkc94;                              // +0xc94
    float m_unkc98;                              // +0xc98
    float m_unkc9c;                              // +0xc9c
    float m_unkca0;                              // +0xca0
    uint32_t m_unkca4;                           // +0xca4
    float m_unkca8;                              // +0xca8
    float m_unkcac;                              // +0xcac
    float m_unkcb0;                              // +0xcb0
    float m_unkcb4;                              // +0xcb4
    float m_unkcb8;                              // +0xcb8
    float m_unkcbc;                              // +0xcbc
    float m_unkcc0;                              // +0xcc0
    float m_unkcc4;                              // +0xcc4
    float m_unkcc8;                              // +0xcc8
    float m_unkccc;                              // +0xccc
    float m_unkcd0;                              // +0xcd0
    float m_unkcd4;                              // +0xcd4
    float m_unkcd8;                              // +0xcd8
    float m_unkcdc;                              // +0xcdc
    float m_unkce0;                              // +0xce0
    float m_unkce4;                              // +0xce4
    float m_unkce8;                              // +0xce8
    float m_unkcec;                              // +0xcec
    float m_unkcf0;                              // +0xcf0
    float m_unkcf4;                              // +0xcf4
    float m_unkcf8;                              // +0xcf8
    float m_unkcfc;                              // +0xcfc
    float m_unkd00;                              // +0xd00
    float m_unkd04;                              // +0xd04
    float m_unkd08;                              // +0xd08
    float m_unkd0c;                              // +0xd0c
    float m_unkd10;                              // +0xd10
    float m_unkd14;                              // +0xd14
    float m_unkd18;                              // +0xd18
    float m_unkd1c;                              // +0xd1c
    float m_unkd20;                              // +0xd20
    float m_unkd24;                              // +0xd24
    float m_unkd28;                              // +0xd28
    float m_unkd2c;                              // +0xd2c
    float m_unkd30;                              // +0xd30
    float m_unkd34;                              // +0xd34
    float m_unkd38;                              // +0xd38
    float m_unkd3c;                              // +0xd3c
    float m_unkd40;                              // +0xd40
    float m_unkd44;                              // +0xd44
    float m_unkd48;                              // +0xd48
    float m_unkd4c;                              // +0xd4c
    float m_unkd50;                              // +0xd50
    float m_unkd54;                              // +0xd54
    float m_unkd58;                              // +0xd58
    float m_unkd5c;                              // +0xd5c
    float m_unkd60;                              // +0xd60
    float m_unkd64;                              // +0xd64
    float m_unkd68;                              // +0xd68
    float m_unkd6c;                              // +0xd6c
    float m_unkd70;                              // +0xd70
    float m_unkd74;                              // +0xd74
    float m_unkd78;                              // +0xd78
    float m_unkd7c;                              // +0xd7c
    float m_unkd80;                              // +0xd80
    float m_unkd84;                              // +0xd84
    float m_unkd88;                              // +0xd88
    float m_unkd8c;                              // +0xd8c
    float m_unkd90;                              // +0xd90
    float m_unkd94;                              // +0xd94
    float m_unkd98;                              // +0xd98
    int32_t m_unkd9c;                            // +0xd9c
    int32_t m_unkda0;                            // +0xda0
    float m_unkda4;                              // +0xda4
    float m_unkda8;                              // +0xda8
    float m_unkdac;                              // +0xdac
    float m_unkdb0;                              // +0xdb0
    float m_unkdb4;                              // +0xdb4
    float m_unkdb8;                              // +0xdb8
    int32_t m_unkdbc;                            // +0xdbc
    float m_unkdc0;                              // +0xdc0
    float m_unkdc4;                              // +0xdc4
    float m_unkdc8;                              // +0xdc8
    float m_unkdcc;                              // +0xdcc
    float m_unkdd0;                              // +0xdd0
    float m_unkdd4;                              // +0xdd4
    float m_unkdd8;                              // +0xdd8
    float m_unkddc;                              // +0xddc
    float m_unkde0;                              // +0xde0
    float m_unkde4;                              // +0xde4
    float m_unkde8;                              // +0xde8
    float m_unkdec;                              // +0xdec
    float m_unkdf0;                              // +0xdf0
    float m_unkdf4;                              // +0xdf4
    float m_unkdf8;                              // +0xdf8
    uint32_t m_unkdfc;                           // +0xdfc
    uint32_t m_unke00;                           // +0xe00
    float m_unke04;                              // +0xe04
    uint8_t m_unke08;                            // +0xe08
    uint8_t m_pade09[3];
    float m_unke0c;                              // +0xe0c
    float m_unke10;                              // +0xe10
    float m_unke14;                              // +0xe14
    float m_unke18;                              // +0xe18
    float m_unke1c;                              // +0xe1c
    float m_unke20;                              // +0xe20
    float m_unke24;                              // +0xe24
    uint32_t m_unke28;                           // +0xe28
    uint32_t m_unke2c;                           // +0xe2c
    float m_unke30;                              // +0xe30
    float m_unke34;                              // +0xe34
    float m_unke38;                              // +0xe38
    float m_unke3c;                              // +0xe3c
    float m_unke40;                              // +0xe40
    uint32_t m_unke44;                           // +0xe44
    float m_unke48;                              // +0xe48
    float m_unke4c;                              // +0xe4c
    float m_unke50;                              // +0xe50
    float m_unke54;                              // +0xe54
    float m_unke58;                              // +0xe58
    float m_unke5c;                              // +0xe5c
    float m_unke60;                              // +0xe60
    float m_unke64;                              // +0xe64
    float m_unke68;                              // +0xe68
    float m_unke6c;                              // +0xe6c
    float m_unke70;                              // +0xe70
    float m_unke74;                              // +0xe74
    float m_unke78;                              // +0xe78
    float m_unke7c;                              // +0xe7c
    float m_unke80;                              // +0xe80
    float m_unke84;                              // +0xe84
    float m_unke88;                              // +0xe88
    float m_unke8c;                              // +0xe8c
    float m_unke90;                              // +0xe90
    float m_unke94;                              // +0xe94
    float m_unke98;                              // +0xe98
    int32_t m_unke9c;                            // +0xe9c
    float m_unkea0;                              // +0xea0
    float m_unkea4;                              // +0xea4
    float m_unkea8;                              // +0xea8
    float m_unkeac;                              // +0xeac
    float m_unkeb0;                              // +0xeb0
    float m_unkeb4;                              // +0xeb4
    float m_unkeb8;                              // +0xeb8
    float m_unkebc;                              // +0xebc
    float m_unkec0;                              // +0xec0
    uint32_t m_unkec4;  // +0xec4  (C2.2 spyro)
    uint32_t m_unkec8;  // +0xec8  (C2.2 spyro)
    uint32_t m_unkecc;  // +0xecc  (C2.2 spyro)
    uint32_t m_ui32StatusFlagsED0;  // +0xed0  (C2.2 spyro)
    uint32_t m_ui32StatusFlagsED4;  // +0xed4  (C2.2 spyro)
    uint32_t m_unked8;  // +0xed8  (C2.2 spyro)
    uint32_t m_unkedc;  // +0xedc flags (bit 7: the lunge mark seen _maybe, StartLungeFromMark)
    uint32_t m_unkee0;  // +0xee0 cleared by DynamicStageTail 0x3046a8
    uint32_t m_padee4;
    IKSerializable* m_unkee8;                    // +0xee8 CKBlurFxData*
    float m_unkeec;  // +0xeec  (C2.2 strict3)
    // +0xef0..+0xfb7: ten button records of 0x14 bytes (CKHkS08Hero_UpdateButtonRecords 0x3411d8): the game manager
    // action (low byte of the word), the state (0 up, 1 pressed, 3 held, 2 released), the held time and the previous
    // one (floats), a consumed byte.
    uint32_t m_aButtonRecords;  // +0xef0  (C2.2 spyro)
    uint32_t m_unkef4;  // +0xef4  (C2.2 spyro)
    float m_unkef8;  // +0xef8  (C2.2 spyro)
    float m_unkefc;  // +0xefc  (C2.2 spyro)
    uint8_t m_unkf00;  // +0xf00  (C2.2 spyro)
    uint8_t m_padf01[3];
    uint32_t m_unkf04;  // +0xf04  (C2.2 spyro)
    uint32_t m_unkf08;  // +0xf08  (C2.2 spyro)
    float m_unkf0c;  // +0xf0c  (C2.2 spyro)
    float m_unkf10;  // +0xf10  (C2.2 spyro)
    uint8_t m_unkf14;  // +0xf14  (C2.2 spyro)
    uint8_t m_padf15[3];
    uint32_t m_unkf18;  // +0xf18  (C2.2 spyro)
    uint32_t m_unkf1c;  // +0xf1c  (C2.2 spyro)
    float m_unkf20;  // +0xf20  (C2.2 spyro)
    float m_unkf24;  // +0xf24  (C2.2 spyro)
    uint8_t m_unkf28;  // +0xf28  (C2.2 spyro)
    uint8_t m_padf29[3];
    uint32_t m_unkf2c;  // +0xf2c  (C2.2 spyro)
    uint32_t m_unkf30;  // +0xf30  (C2.2 spyro)
    float m_unkf34;  // +0xf34  (C2.2 spyro)
    float m_unkf38;  // +0xf38  (C2.2 spyro)
    uint8_t m_unkf3c;  // +0xf3c  (C2.2 spyro)
    uint8_t m_padf3d[3];
    uint32_t m_unkf40;  // +0xf40  (C2.2 spyro)
    uint32_t m_unkf44;  // +0xf44  (C2.2 spyro)
    float m_unkf48;  // +0xf48  (C2.2 spyro)
    float m_unkf4c;  // +0xf4c  (C2.2 spyro)
    uint8_t m_unkf50;  // +0xf50  (C2.2 spyro)
    uint8_t m_padf51[3];
    uint32_t m_unkf54;  // +0xf54  (C2.2 spyro)
    uint32_t m_unkf58;  // +0xf58  (C2.2 spyro)
    float m_unkf5c;  // +0xf5c  (C2.2 spyro)
    float m_unkf60;  // +0xf60  (C2.2 spyro)
    uint8_t m_unkf64;  // +0xf64  (C2.2 spyro)
    uint8_t m_padf65[3];
    uint32_t m_unkf68;  // +0xf68  (C2.2 spyro)
    uint32_t m_unkf6c;  // +0xf6c  (C2.2 spyro)
    float m_unkf70;  // +0xf70  (C2.2 spyro)
    float m_unkf74;  // +0xf74  (C2.2 spyro)
    uint8_t m_unkf78;  // +0xf78  (C2.2 spyro)
    uint8_t m_padf79[3];
    uint32_t m_unkf7c;  // +0xf7c  (C2.2 spyro)
    uint32_t m_unkf80;  // +0xf80  (C2.2 spyro)
    float m_unkf84;  // +0xf84  (C2.2 spyro)
    float m_unkf88;  // +0xf88  (C2.2 spyro)
    uint8_t m_unkf8c;  // +0xf8c  (C2.2 spyro)
    uint8_t m_padf8d[3];
    uint32_t m_unkf90;  // +0xf90  (C2.2 spyro)
    uint32_t m_unkf94;  // +0xf94  (C2.2 spyro)
    float m_unkf98;  // +0xf98  (C2.2 spyro)
    float m_unkf9c;  // +0xf9c  (C2.2 spyro)
    uint8_t m_unkfa0;  // +0xfa0  (C2.2 spyro)
    uint8_t m_padfa1[3];
    uint32_t m_unkfa4;  // +0xfa4  (C2.2 spyro)
    uint32_t m_unkfa8;  // +0xfa8  (C2.2 spyro)
    float m_unkfac;  // +0xfac  (C2.2 spyro)
    float m_unkfb0;  // +0xfb0  (C2.2 spyro)
    uint8_t m_unkfb4;  // +0xfb4  (C2.2 spyro)
    uint8_t m_padfb5[3];
    IKSerializable* m_pCarrierHero;                    // +0xfb8 CKS08CarrierHero*
    IKSerializable* m_apUnkfbc[5];               // +0xfbc one array read of 5 references (CKShadowCpnt first, struct draft)
    float m_unkfd0;  // +0xfd0  (C2.2 spyro)
    float m_unkfd4;  // +0xfd4  (C2.2 spyro)
    float m_unkfd8;  // +0xfd8  (C2.2 spyro)
    uint32_t m_unkfdc;  // +0xfdc  (C2.2 spyro)
    uint32_t m_unkfe0;  // +0xfe0  (C2.2 spyro)
    uint32_t m_unkfe4;  // +0xfe4  (C2.2 spyro)
    uint32_t m_unkfe8;  // +0xfe8  (C2.2 spyro)
    uint8_t m_unkFec;                            // +0xfec constructor 0
    uint8_t m_unkfed;  // +0xfed  (C2.2 strict3)
    uint8_t m_padfee[2];
    float m_unkff0;  // +0xff0  (C2.2 spyro)
    float m_unkff4;  // +0xff4  (C2.2 spyro)
    float m_unkff8;  // +0xff8  (C2.2 spyro)
    uint32_t m_unkffc;  // +0xffc  (C2.2 spyro)
    uint32_t m_unk1000;  // +0x1000  (C2.2 spyro)
    uint32_t m_unk1004;  // +0x1004  (C2.2 spyro)
    uint32_t m_unk1008;  // +0x1008  (C2.2 spyro)
    uint8_t m_unk100c;                           // +0x100c constructor 0
    uint8_t m_unk100d;  // +0x100d  (C2.2 strict3)
    uint8_t m_pad100e[2];
    float m_unk1010;  // +0x1010  (C2.2 spyro)
    float m_unk1014;  // +0x1014  (C2.2 spyro)
    float m_unk1018;  // +0x1018  (C2.2 spyro)
    uint32_t m_unk101c;  // +0x101c  (C2.2 spyro)
    uint32_t m_unk1020;  // +0x1020  (C2.2 spyro)
    uint32_t m_unk1024;  // +0x1024  (C2.2 spyro)
    uint32_t m_unk1028;  // +0x1028  (C2.2 spyro)
    uint8_t m_unk102c;                           // +0x102c constructor 0
    uint8_t m_unk102d;  // +0x102d  (C2.2 strict3)
    uint8_t m_pad102e[2];
    float m_unk1030;  // +0x1030  (C2.2 spyro)
    float m_unk1034;  // +0x1034  (C2.2 spyro)
    float m_unk1038;  // +0x1038  (C2.2 spyro)
    uint32_t m_unk103c;  // +0x103c  (C2.2 spyro)
    uint32_t m_unk1040;  // +0x1040  (C2.2 spyro)
    uint32_t m_unk1044;  // +0x1044  (C2.2 spyro)
    uint32_t m_unk1048;  // +0x1048  (C2.2 spyro)
    uint8_t m_unk104c;                           // +0x104c constructor 0
    uint8_t m_unk104d;  // +0x104d  (C2.2 strict3)
    uint8_t m_pad104e[2];
    float m_unk1050;  // +0x1050  (C2.2 spyro)
    float m_unk1054;  // +0x1054  (C2.2 spyro)
    float m_unk1058;  // +0x1058  (C2.2 spyro)
    uint32_t m_unk105c;  // +0x105c  (C2.2 spyro)
    uint32_t m_unk1060;  // +0x1060  (C2.2 spyro)
    uint32_t m_unk1064;  // +0x1064  (C2.2 spyro)
    uint32_t m_unk1068;  // +0x1068  (C2.2 spyro)
    uint8_t m_unk106c;                           // +0x106c constructor 0
    uint8_t m_unk106d;  // +0x106d  (C2.2 strict3)
    uint8_t m_pad106e[2];
    IKSerializable* m_apUnk1070[8][4];           // +0x1070 8 x 4 references (CAnimatedNode, CSGHotSpot, ...)
    AnimBlendSlot m_animBlendSlot10f0;           // +0x10f0 embedded AnimBlendSlot (vtable 0xb16560); constructor: m_pController (+0x10f4) = 0
    // +0x1108..+0x1120: the field of view approach (Math_ApproachWithAccelDecel, 7 floats; ApproachField1108AndNotifyCamera).
    float m_unk1108;   // +0x1108 TryStartFinisherCamera: 300
    float m_unk110c;   // +0x110c TryStartFinisherCamera: 300
    float m_unk1110;   // +0x1110 TryStartFinisherCamera: 100
    float m_unk1114;  // +0x1114  (C2.2 strict2; TryStartFinisherCamera: the camera's real field of view)
    float m_unk1118;   // +0x1118 TryStartFinisherCamera: 0
    float m_unk111c;  // +0x111c  (C2.2 strict2; TryStartFinisherCamera: the finisher's field of view)
    float m_unk1120;   // +0x1120 TryStartFinisherCamera: 0
    float m_unk1124;  // +0x1124  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    float m_unk1128;  // +0x1128  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    float m_unk112c;  // +0x112c  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    float m_unk1130;  // +0x1130  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    float m_unk1134;  // +0x1134  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    float m_unk1138;  // +0x1138  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    float m_unk113c;  // +0x113c  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    float m_unk1140;  // +0x1140  (C2.2 spyro; a float: the catch-up warp, CtlState1 / CtlState0)
    uint8_t m_unk1144;  // +0x1144  (C2.2 spyro)
    uint8_t m_pad1145[3];
    float m_unk1148;  // +0x1148  (C2.2 spyro; a float: the catch-up warp's curve parameter)
    CTriggerStarter m_tsStartCarrying;                   // +0x114c
    CTriggerStarter m_tsHit;                   // +0x1154
    float m_unk115c;  // +0x115c  (C2.2 strict3)
    float m_unk1160;  // +0x1160  (C2.2 strict3)
    IKSerializable* m_unk1164;                   // +0x1164 CKVibrationData*
    IKSerializable* m_unk1168;                   // +0x1168 CKVibrationData*
    IKSerializable* m_unk116c;                   // +0x116c CKVibrationData*
    IKSerializable* m_unk1170;                   // +0x1170 CKVibrationData*
    uint8_t m_unk1174;                           // +0x1174 OnLock: 0
    uint8_t m_unk1175;                           // +0x1175 OnLock: 0
    uint8_t m_pad1176[2];
    float m_unk1178;                             // +0x1178 OnLock: 0.0
    float m_unk117c;                             // +0x117c OnLock: 0.0
    uint8_t m_unk1180;                           // +0x1180 OnLock: 0
    uint8_t m_unk1181;                           // +0x1181 OnLock: 0
    uint8_t m_pad1182[2];
    float m_unk1184;                             // +0x1184 OnLock: 0.0
    float m_unk1188;                             // +0x1188 OnLock: 0.0
    uint8_t m_unk118c;                           // +0x118c OnLock: 0
    uint8_t m_unk118d;  // +0x118d  (C2.2 strict3)
    uint8_t m_unk118e;  // +0x118e  (C2.2 strict3)
    uint8_t m_pad118f[1];
    IKSerializable* m_pFlightImpulsionCpnt;                   // +0x1190 CKImpulsionCpnt*
    uint8_t m_unk1194;  // +0x1194  (C2.2 strict3)
    uint8_t m_unk1195;  // +0x1195  (C2.2 strict3)
    uint8_t m_pad1196[2];
    float m_unk1198;  // +0x1198  (C2.2 strict3)
    float m_unk119c;  // +0x119c the stick in the node's frame (ComputeCameraRelativeMove 0x311df0)
    float m_unk11a0;  // +0x11a0
    float m_unk11a4;  // +0x11a4
    float m_unk11a8;  // +0x11a8  (C2.2 strict3)
    float m_unk11ac;  // +0x11ac  (C2.2 strict3)
    float m_unk11b0;  // +0x11b0  (C2.2 strict3)
    float m_unk11b4;  // +0x11b4  (C2.2 strict3)
    float m_unk11b8;  // +0x11b8  (C2.2 strict3)
    float m_unk11bc;  // +0x11bc  (C2.2 strict3)
    uint8_t m_unk11c0;  // +0x11c0  (C2.2 strict3)
    uint8_t m_pad11c1[3];
    float m_unk11c4;  // +0x11c4  (C2.2 strict3)
    uint32_t m_unk11c8;  // +0x11c8  (C2.2 strict3)
    float m_unk11cc;  // +0x11cc  (C2.2 strict3)
    float m_unk11d0;  // +0x11d0  (C2.2 strict3)
    float m_unk11d4;  // +0x11d4  (C2.2 strict3)
    uint32_t m_unk11d8;  // +0x11d8  (C2.2 strict3)
    float m_unk11dc;  // +0x11dc  (C2.2 strict3)
    float m_unk11e0;  // +0x11e0  (C2.2 strict3)
    float m_unk11e4;  // +0x11e4  (C2.2 strict3)
    float m_unk11e8;  // +0x11e8 (SetAbilityHeroMode: +0x8cc)
    float m_unk11ec;  // +0x11ec  (C2.2 strict3)
    float m_unk11f0;  // +0x11f0  (C2.2 strict3)
    float m_unk11f4;  // +0x11f4  (C2.2 strict3)
    float m_unk11f8;  // +0x11f8  (C2.2 strict3)
    CGroundContactDatasInOut m_gcContact11FC;          // +0x11fc constructor defaults only
    uint8_t m_unk1228;  // +0x1228  (C2.2 strict3)
    uint8_t m_pad1229[3];
    float m_unk122c;  // +0x122c (UpdateLocomotionByMode adds the dt with +0xec8 bit 1)
    float m_unk1230;  // +0x1230
    float m_unk1234;  // +0x1234
    float m_unk1238;  // +0x1238
    float m_unk123c;  // +0x123c
    float m_unk1240;  // +0x1240
    float m_unk1244;  // +0x1244
    float m_unk1248;  // +0x1248  (C2.2 strict3)
    float m_unk124c;  // +0x124c  (C2.2 strict3)
    float m_unk1250;  // +0x1250  (C2.2 strict3)
    uint32_t m_pad1254;
    float m_unk1258;  // +0x1258  (C2.2 strict3; a float: UpdateCKHkS08Hero stores the carried object's vt+0x104)
    float m_unk125c;  // +0x125c the take-off point (UpdateGroundLocomotionState)
    float m_unk1260;  // +0x1260
    float m_unk1264;  // +0x1264
    float m_unk1268;  // +0x1268  (C2.2 strict3)
    float m_unk126c;  // +0x126c  (C2.2 strict3)
    float m_unk1270;  // +0x1270  (C2.2 strict3)
    float m_unk1274;  // +0x1274  (C2.2 strict3)
    uint32_t m_unk1278;  // +0x1278  (C2.2 strict3)
    float m_unk127c;  // +0x127c  (C2.2 strict3)
    float m_unk1280;  // +0x1280  (C2.2 strict3)
    float m_unk1284;  // +0x1284  (C2.2 strict3)
    float m_unk1288;  // +0x1288  (C2.2 strict3)
    float m_unk128c;  // +0x128c  (C2.2 strict3)
    float m_unk1290;  // +0x1290  (C2.2 strict3)
    float m_unk1294;  // +0x1294 the horizontal velocity's direction (ComputeCameraRelativeMove)
    float m_unk1298;  // +0x1298
    float m_unk129c;  // +0x129c
    float m_unk12a0;  // +0x12a0  (C2.2 strict3)
    float m_unk12a4;  // +0x12a4  (C2.2 strict3)
    float m_unk12a8;  // +0x12a8  (C2.2 strict3)
    float m_unk12ac;  // +0x12ac the velocity along +0x1288 (ComputeCameraRelativeMove)
    float m_unk12b0;  // +0x12b0
    float m_unk12b4;  // +0x12b4
    float m_unk12b8;  // +0x12b8 the run direction (ComputeGroundRunForce)
    float m_unk12bc;  // +0x12bc
    float m_unk12c0;  // +0x12c0
    float m_fCurrentHorizSpeed;  // +0x12c4 the horizontal speed (ComputeCameraRelativeMove)
    float m_fCurrentAbsVertSpeed;  // +0x12c8 the vertical speed, absolute
    float m_unk12cc;  // +0x12cc the push clamp's speed factor (ProcessHeroContactList: at least 1)
    float m_unk12d0;  // +0x12d0 (UpdateGroundMovement: the speed range's start for the turn rate)
    float m_unk12d4;  // +0x12d4 +0x12ac along the facing (ComputeCameraRelativeMove)
    uint32_t m_unk12d8;  // +0x12d8  (C2.2 strict3)
    uint32_t m_unk12dc;  // +0x12dc  (C2.2 strict3)
    uint32_t m_unk12e0;  // +0x12e0  (C2.2 strict3)
    float m_unk12e4;  // +0x12e4  (C2.2 strict3)
    float m_unk12e8;  // +0x12e8  (C2.2 strict3)
    float m_unk12ec;  // +0x12ec  (C2.2 strict3)
    uint8_t m_unk12f0;  // +0x12f0 the ground is more than 0.01 below (ComputeCameraRelativeMove)
    uint8_t m_pad12f1[3];
    float m_unk12f4;  // +0x12f4  (C2.2 strict3)
    float m_unk12f8;  // +0x12f8  (C2.2 strict3)
    float m_unk12fc;                             // +0x12fc (side blend limit)
    float m_unk1300;                             // +0x1300 (side blend limit)
    uint8_t m_unk1304;  // +0x1304  (C2.2 strict3)
    uint8_t m_unk1305;  // +0x1305  (C2.2 strict3)
    uint8_t m_pad1306[2];
    float m_unk1308;  // +0x1308  (C2.2 strict3; the held time +0x388 while held, UpdateHeroActionInput)
    float m_unk130c;                             // +0x130c
    float m_unk1310;                             // +0x1310
    float m_unk1314;                             // +0x1314
    float m_unk1318;                             // +0x1318
    float m_unk131c;                             // +0x131c
    float m_unk1320;                             // +0x1320
    float m_unk1324;                             // +0x1324
    float m_unk1328;                             // +0x1328
    float m_unk132c;                             // +0x132c
    float m_unk1330;                             // +0x1330
    float m_unk1334;                             // +0x1334
    float m_unk1338;                             // +0x1338
    uint32_t m_unk133c;  // +0x133c
    float m_unk1340;  // +0x1340
    uint32_t m_pad1344;
    float m_unk1348;  // +0x1348  (C2.2 strict3)
    uint8_t m_unk134c;  // +0x134c  (C2.2 strict3)
    uint8_t m_pad134d[3];
    float m_unk1350;  // +0x1350  (C2.2 strict3)
    uint8_t m_unk1354;  // +0x1354  (C2.2 strict3)
    uint8_t m_pad1355[7];
    float m_unk135c;  // +0x135c  (C2.2 strict3)
    float m_unk1360;  // +0x1360  (C2.2 strict3)
    float m_unk1364;  // +0x1364  (C2.2 strict3)
    float m_unk1368;  // +0x1368  (C2.2 strict3)
    float m_unk136c;  // +0x136c  (C2.2 strict3)
    float m_unk1370;  // +0x1370  (C2.2 strict3)
    float m_unk1374;  // +0x1374 the turn amount the move kinds read
    float m_unk1378;  // +0x1378  (C2.2 spyro)
    float m_unk137c;  // +0x137c  (C2.2 strict3)
    uint32_t m_unk1380;  // +0x1380  (C2.2 strict3)
    uint8_t m_unk1384;  // +0x1384 the flying hero's end-of-push byte (FlyAnimState09..13 go to the end pose, state 12)
    uint8_t m_unk1385;  // +0x1385
    uint8_t m_pad1386[2];
    float m_unk1388;  // +0x1388
    float m_unk138c;  // +0x138c
    float m_unk1390;  // +0x1390
    float m_unk1394;  // +0x1394
    float m_unk1398;  // +0x1398  (C2.2 strict3)
    float m_unk139c;  // +0x139c  (C2.2 strict3)
    float m_unk13a0;  // +0x13a0  (C2.2 strict3)
    uint8_t m_unk13a4;  // +0x13a4 the flight's landing approach (FlyAnimState00..04 answer state 3)
    uint8_t m_unk13a5;  // +0x13a5
    uint8_t m_unk13a6;  // +0x13a6 cleared by AnimLocomotionFlying's enter
    uint8_t m_unk13a7;  // +0x13a7 set by FlyAnimState12's enter, cleared by AnimLocomotionFlying's
    CVector3 m_unk13a8;                          // +0x13a8 constructor 0.0 (TOC 0x1da4)
    CVector3 m_unk13b4;                          // +0x13b4 constructor 0.0
    float m_unk13c0;  // +0x13c0 the time in the current flying animation state (FlyAnimState01 / 02 / 04 / 05 add the dt)
    float m_unk13c4;  // +0x13c4 cleared by AnimLocomotionFlying's enter / exit
    float m_unk13c8;  // +0x13c8 cleared by AnimLocomotionFlying's enter / exit
    uint8_t m_unk13cc;  // +0x13cc  (C2.2 strict3)
    uint8_t m_unk13cd;  // +0x13cd  (C2.2 strict3)
    uint8_t m_unk13ce;  // +0x13ce  (C2.2 strict3)
    uint8_t m_unk13cf;  // +0x13cf the flying animation states 03 / 04 answer state 5 (0x43)
    uint8_t m_unk13d0;  // +0x13d0  (C2.2 strict3)
    uint8_t m_unk13d1;  // +0x13d1  (C2.2 strict2)
    uint8_t m_unk13d2;  // +0x13d2
    uint8_t m_unk13d3;  // +0x13d3  (C2.2 strict3)
    float m_unk13d4;  // +0x13d4  (C2.2 strict2)
    uint8_t m_unk13d8;  // +0x13d8  (C2.2 strict3)
    uint8_t m_unk13d9;  // +0x13d9  (C2.2 strict3)
    uint8_t m_pad13da[2];
    float m_unk13dc;  // +0x13dc  (C2.2 strict3)
    float m_unk13e0;  // +0x13e0  (C2.2 strict3)
    float m_unk13e4;  // +0x13e4  (C2.2 strict3)
    float m_unk13e8;  // +0x13e8  (C2.2 strict3)
    float m_unk13ec;  // +0x13ec  (C2.2 strict3)
    float m_unk13f0;  // +0x13f0  (C2.2 strict3)
    float m_unk13f4;  // +0x13f4  (C2.2 strict3)
    uint32_t m_unk13f8;  // +0x13f8  (C2.2 strict3)
    uint8_t m_unk13fc;  // +0x13fc  (C2.2 strict3)
    uint8_t m_pad13fd[3];
    float m_unk1400;  // +0x1400  (C2.2 strict3)
    float m_unk1404;  // +0x1404  (C2.2 strict3)
    float m_unk1408;  // +0x1408  (C2.2 strict3)
    uint32_t m_unk140c;  // +0x140c  (C2.2 strict3)
    uint32_t m_unk1410;  // +0x1410  (C2.2 strict3)
    float m_unk1414;  // +0x1414  (C2.2 strict3)
    float m_unk1418;  // +0x1418  (C2.2 strict3)
    uint8_t m_unk141c;  // +0x141c  (C2.2 strict3)
    uint8_t m_pad141d[3];
    float m_unk1420;  // +0x1420  (C2.2 strict3)
    float m_unk1424;  // +0x1424  (C2.2 strict3)
    float m_unk1428;  // +0x1428  (C2.2 strict3)
    float m_unk142c;  // +0x142c  (C2.2 strict3)
    float m_unk1430;  // +0x1430  (C2.2 strict3)
    uint32_t m_unk1434;  // +0x1434  (C2.2 strict3)
    uint8_t m_unk1438;  // +0x1438  (C2.2 strict3)
    uint8_t m_pad1439[3];
    float m_unk143c;  // +0x143c  (C2.2 strict3; the air action's cooldown, HandleAirborneActionCInput)
    uint32_t m_unk1440;  // +0x1440  (C2.2 strict3)
    uint32_t m_unk1444;  // +0x1444  (C2.2 strict3)
    float m_unk1448;  // +0x1448 (C2.2 strict3; a float: the landing approach's time, FlyAnimState03)
    CVector3 m_unk144c;                          // +0x144c constructor 0.0
    float m_fFlightHeight;  // +0x1458  (C2.2 strict3; a float: the flight height)
    float m_unk145c;  // +0x145c  (C2.2 strict3)
    uint32_t m_unk1460;  // +0x1460  (C2.2 strict3)
    uint8_t m_unk1464;  // +0x1464  (C2.2 strict3)
    uint8_t m_pad1465[3];
    float m_unk1468;  // +0x1468  (C2.2 strict3)
    float m_unk146c;  // +0x146c  (C2.2 strict3)
    float m_unk1470;  // +0x1470  (C2.2 strict3)
    uint32_t m_unk1474;  // +0x1474  (C2.2 strict3)
    uint32_t m_unk1478;  // +0x1478  (C2.2 strict3)
    IKSerializable* m_unk147c;                   // +0x147c CKCurve2DCpnt*
    float m_unk1480;                             // +0x1480
    float m_unk1484;                             // +0x1484
    float m_unk1488;                             // +0x1488
    float m_unk148c;                             // +0x148c
    float m_unk1490;                             // +0x1490
    float m_unk1494;                             // +0x1494
    float m_unk1498;                             // +0x1498
    float m_unk149c;                             // +0x149c
    float m_unk14a0;                             // +0x14a0
    float m_unk14a4;                             // +0x14a4
    float m_unk14a8;                             // +0x14a8
    float m_unk14ac;                             // +0x14ac
    float m_unk14b0;                             // +0x14b0
    float m_unk14b4;                             // +0x14b4
    float m_unk14b8;                             // +0x14b8
    float m_unk14bc;                             // +0x14bc
    float m_unk14c0;                             // +0x14c0
    float m_unk14c4;                             // +0x14c4
    float m_unk14c8;                             // +0x14c8
    float m_unk14cc;                             // +0x14cc
    float m_unk14d0;                             // +0x14d0
    float m_unk14d4;                             // +0x14d4
    float m_unk14d8;                             // +0x14d8
    float m_unk14dc;                             // +0x14dc
    float m_unk14e0[6];  // +0x14e0 the animation's mark parameters 13..18 (GetAnimParams13to18 0x303a78)
    float m_unk14f8;                             // +0x14f8 (locomotion)
    float m_unk14fc;                             // +0x14fc (locomotion)
    float m_unk1500;                             // +0x1500 (locomotion)
    uint8_t m_unk1504;  // +0x1504  (C2.2 strict3)
    uint8_t m_unk1505;                           // +0x1505 (locomotion)
    uint8_t m_unk1506;                           // +0x1506 (locomotion)
    uint8_t m_unk1507;  // +0x1507  (C2.2 strict3)
    uint8_t m_unk1508;                           // +0x1508 (locomotion)
    uint8_t m_unk1509;                           // +0x1509 (locomotion)
    uint8_t m_unk150a;                           // +0x150a (locomotion)
    uint8_t m_unk150b;                           // +0x150b (locomotion)
    uint8_t m_unk150c;                           // +0x150c (locomotion)
    uint8_t m_unk150d;                           // +0x150d (locomotion)
    uint8_t m_unk150e;                           // +0x150e (locomotion)
    uint8_t m_pad150f[2];
    uint8_t m_unk1511;                           // +0x1511 (locomotion)
    uint8_t m_unk1512;                           // +0x1512 (locomotion)
    uint8_t m_unk1513;                           // +0x1513 (locomotion)
    uint8_t m_unk1514;  // +0x1514 (UpdateGroundLocomotionState)
    uint8_t m_pad1515[2];
    uint8_t m_unk1517;  // +0x1517 (UpdateGroundLocomotionState)
    uint8_t m_unk1518;  // +0x1518  (C2.2 strict3)
    uint8_t m_pad1519[3];
    float m_unk151c;                             // +0x151c (locomotion)
    float m_unk1520;                             // +0x1520 (locomotion)
    float m_unk1524;                             // +0x1524 (locomotion)
    float m_unk1528;                             // +0x1528 (locomotion)
    uint8_t m_pad152c[4];
    uint8_t m_unk1530;  // +0x1530  (C2.2 strict3)
    uint8_t m_pad1531[3];
    uint32_t m_unk1534;  // +0x1534  (C2.2 strict3)
    uint8_t m_unk1538;  // +0x1538  (C2.2 strict3)
    uint8_t m_unk1539;  // +0x1539  (C2.2 strict3)
    uint8_t m_pad153a[2];
    uint32_t m_unk153c;  // +0x153c  (C2.2 strict3)
    float m_unk1540;  // +0x1540 the landing animation's start (GroundAnimState10)
    float m_unk1544;  // +0x1544 (UpdateGroundLocomotionState)
    float m_unk1548;                             // +0x1548 (the frame's time, UpdateCKHkS08Hero)
    float m_unk154c;  // +0x154c  (C2.2 strict3)
    float m_unk1550;  // +0x1550  (C2.2 strict3)
    uint8_t m_unk1554;  // +0x1554  (C2.2 strict3)
    uint8_t m_pad1555[3];
    float m_unk1558;  // +0x1558  (C2.2 strict3)
    float m_unk155c;  // +0x155c  (C2.2 strict3)
    float m_unk1560;  // +0x1560  (C2.2 strict3)
    uint32_t m_unk1564;  // +0x1564  (C2.2 strict3)
    uint32_t m_unk1568;  // +0x1568  (C2.2 strict3)
    float m_unk156c;  // +0x156c  (C2.2 strict3)
    float m_unk1570;  // +0x1570  (C2.2 strict3)
    uint8_t m_unk1574;  // +0x1574  (C2.2 strict3)
    uint8_t m_pad1575[3];
    float m_unk1578;  // +0x1578  (C2.2 strict3)
    float m_unk157c;  // +0x157c  (C2.2 strict3)
    float m_unk1580;  // +0x1580  (C2.2 strict3)
    uint32_t m_unk1584;  // +0x1584  (C2.2 strict3)
    uint32_t m_unk1588;  // +0x1588  (C2.2 strict3)
    float m_unk158c;  // +0x158c  (C2.2 strict3)
    float m_unk1590;  // +0x1590  (C2.2 strict3)
    uint8_t m_unk1594;  // +0x1594  (C2.2 strict3)
    uint8_t m_pad1595[3];
    float m_unk1598;  // +0x1598  (C2.2 strict3)
    float m_unk159c;  // +0x159c  (C2.2 strict3)
    float m_unk15a0;  // +0x15a0  (C2.2 strict3)
    uint32_t m_unk15a4;  // +0x15a4  (C2.2 strict3)
    uint32_t m_unk15a8;  // +0x15a8  (C2.2 strict3)
    float m_unk15ac;  // +0x15ac  (C2.2 strict3)
    float m_unk15b0;  // +0x15b0  (C2.2 strict3)
    uint8_t m_unk15b4;  // +0x15b4  (C2.2 strict3)
    uint8_t m_pad15b5[3];
    float m_unk15b8;  // +0x15b8  (C2.2 strict3)
    float m_unk15bc;  // +0x15bc  (C2.2 strict3)
    float m_unk15c0;  // +0x15c0  (C2.2 strict3)
    uint32_t m_unk15c4;  // +0x15c4  (C2.2 strict3)
    uint32_t m_unk15c8;  // +0x15c8  (C2.2 strict3)
    uint8_t m_unk15cc;  // +0x15cc  (C2.2 strict3)
    uint8_t m_unk15cd;  // +0x15cd  (C2.2 strict3)
    uint8_t m_unk15ce;  // +0x15ce  (C2.2 strict3)
    uint8_t m_unk15cf;  // +0x15cf  (C2.2 strict3)
    uint8_t m_unk15d0;  // +0x15d0  (C2.2 strict3)
    uint8_t m_unk15d1;  // +0x15d1  (C2.2 strict3)
    uint8_t m_unk15d2;  // +0x15d2  (C2.2 strict3)
    uint8_t m_pad15d3[1];
    float m_unk15d4;  // +0x15d4  (C2.2 strict3)
    float m_unk15d8;  // +0x15d8  (C2.2 strict3)
    float m_unk15dc;  // +0x15dc  (C2.2 strict3)
    float m_unk15e0;  // +0x15e0  (C2.2 strict3)
    float m_unk15e4;  // +0x15e4  (C2.2 strict3)
    float m_unk15e8;  // +0x15e8  (C2.2 strict3)
    uint32_t m_unk15ec;  // +0x15ec  (C2.2 strict3)
    float m_unk15f0;  // +0x15f0  (C2.2 strict3)
    float m_unk15f4;  // +0x15f4  (C2.2 strict3)
    float m_unk15f8;  // +0x15f8  (C2.2 strict3)
    uint8_t m_unk15fc;  // +0x15fc  (C2.2 strict3)
    uint8_t m_pad15fd[3];
    uint32_t m_unk1600;  // +0x1600  (C2.2 strict3)
    float m_unk1604;  // +0x1604  (C2.2 strict3)
    float m_unk1608;  // +0x1608  (C2.2 strict3)
    float m_unk160c;  // +0x160c  (C2.2 strict3)
    uint32_t m_unk1610;  // +0x1610  (C2.2 strict3)
    uint8_t m_unk1614;  // +0x1614  (C2.2 strict3)
    uint8_t m_unk1615;  // +0x1615  (C2.2 strict3)
    uint8_t m_pad1616[2];
    float m_unk1618;  // +0x1618  (C2.2 strict3)
    uint8_t m_unk161c;  // +0x161c  (C2.2 strict3)
    uint8_t m_pad161d[2];
    uint8_t m_unk161f;  // +0x161f  (C2.2 strict3)
    uint8_t m_unk1620;                           // +0x1620 (step 6 CLIMB: the climb bytes +0x1620..+0x1625)
    uint8_t m_unk1621;                           // +0x1621
    uint8_t m_unk1622;                           // +0x1622
    uint8_t m_unk1623;                           // +0x1623 the climb's grab (ClimbAnimState02 plays the kind's +0x64 row)
    uint8_t m_unk1624;                           // +0x1624
    uint8_t m_unk1625;                           // +0x1625
    uint8_t m_unk1626;  // +0x1626  (C2.2 strict3)
    uint8_t m_unk1627;  // +0x1627  (C2.2 strict3)
    uint8_t m_unk1628;  // +0x1628  (C2.2 strict3)
    uint8_t m_unk1629;  // +0x1629  (C2.2 strict3)
    uint8_t m_pad162a[2];
    float m_unk162c;                             // +0x162c (step 6 CLIMB)
    float m_unk1630;  // +0x1630  (C2.2 strict3; a float: step 6 CLIMB)
    float m_unk1634;  // +0x1634  (C2.2 strict3; a float: step 6 CLIMB)
    uint32_t m_unk1638;                          // +0x1638 (step 6 CLIMB)
    float m_unk163c;                             // +0x163c (step 6 CLIMB: the orientation blend time)
    float m_unk1640[3];                          // +0x1640 (step 6 CLIMB)
    float m_unk164c;  // +0x164c  (C2.2 strict3)
    float m_unk1650;  // +0x1650  (C2.2 strict3)
    float m_unk1654;  // +0x1654  (C2.2 strict3)
    float m_unk1658;  // +0x1658  (C2.2 strict3)
    float m_unk165c;  // +0x165c  (C2.2 strict3)
    float m_unk1660;  // +0x1660  (C2.2 strict3)
    uint8_t m_unk1664;  // +0x1664 the climb kind (6 / 7: HandleAirborneActionCInput probes along -up)
    uint8_t m_unk1665;  // +0x1665  (C2.2 strict3)
    uint8_t m_pad1666[2];
    float m_unk1668;  // +0x1668  (C2.2 strict3)
    float m_unk166c;  // +0x166c  (C2.2 strict3)
    float m_unk1670;  // +0x1670  (C2.2 strict3)
    uint8_t m_bExternalDisplacementActive;  // +0x1674  (C2.2 strict3)
    uint8_t m_unk1675;  // +0x1675  (C2.2 strict3)
    uint8_t m_unk1676;  // +0x1676  (C2.2 strict3)
    uint8_t m_unk1677;  // +0x1677  (C2.2 strict3)
    uint8_t m_unk1678;  // +0x1678  (C2.2 strict3)
    uint8_t m_unk1679;  // +0x1679  (C2.2 strict3)
    uint8_t m_unk167a;  // +0x167a  (C2.2 strict3)
    uint8_t m_unk167b;  // +0x167b  (C2.2 strict3)
    uint8_t m_unk167c;  // +0x167c  (C2.2 strict3)
    uint8_t m_unk167d;  // +0x167d  (C2.2 strict3)
    uint8_t m_unk167e;                           // +0x167e (step 6 CLIMB)
    uint8_t m_pad167f[1];
    uint32_t m_unk1680;                          // +0x1680 (step 6 CLIMB)
    uint8_t m_unk1684;                           // +0x1684 (step 6 CLIMB)
    uint8_t m_pad1685[3];
    float m_unk1688;                             // +0x1688 (step 6 CLIMB)
    uint8_t m_unk168c;  // +0x168c  (C2.2 strict3)
    uint8_t m_unk168d;  // +0x168d  (C2.2 strict3)
    uint8_t m_unk168e;  // +0x168e  (C2.2 strict3)
    uint8_t m_pad168f[1];
    CKHkClimbZone* m_pHeldClimbZone;  // _maybe: +0x1690 the climb zone of this frame while held (step 6 CLIMB)
    CKHkClimbZone* m_pCurrentClimbZone;  // +0x1694 the climb zone the hero is in (HandleClimbZoneContact; cleared each frame)
    CKHkClimbZone* m_unk1698;  // +0x1698 the zone before the last one
    CKHkClimbZone* m_unk169c;  // +0x169c the last zone
    IKSerializable* m_unk16a0;  // +0x16a0 the zone's +0x4c
    CKHkClimbZone* m_unk16a4;  // +0x16a4 a zone the hero is recorded in (TryAttachToClimbZoneList16B0)
    CKHkClimbZone* m_unk16a8;  // +0x16a8 the same (TryAttachToClimbZoneList16BC)
    CKHkClimbZone* m_unk16ac;  // +0x16ac the zone a leap started from (step 6 CLIMB)
    CKHkClimbZone* m_unk16b0[2];                 // +0x16b0 the zones touched in front this frame (step 6 CLIMB)
    uint32_t m_unk16b8;                          // +0x16b8 constructor 0
    CKHkClimbZone* m_unk16bc[2];                 // +0x16bc the zones touched behind this frame
    uint32_t m_unk16c4;                          // +0x16c4 constructor 0
    float m_unk16c8;                             // +0x16c8 the position where a zone list was attached (step 6 CLIMB)
    float m_unk16cc;                             // +0x16cc
    float m_unk16d0;                             // +0x16d0
    CMatrix34* m_unk16d4;  // +0x16d4  (C2.2 strict3)
    CMatrix34* m_unk16d8;  // +0x16d8  (C2.2 strict3)
    CMatrix34* m_unk16dc;  // +0x16dc  (C2.2 strict3)
    CMatrix34* m_unk16e0;  // +0x16e0  (C2.2 strict3)
    CMatrix34* m_unk16e4;  // +0x16e4  (C2.2 strict3)
    CMatrix34* m_unk16e8;  // +0x16e8  (C2.2 strict3)
    CMatrix34* m_unk16ec;  // +0x16ec  (C2.2 strict3)
    CMatrix34* m_unk16f0;  // +0x16f0  (C2.2 strict3)
    float m_unk16f4;  // +0x16f4  (C2.2 strict3; the mount distance, a float: step 6 CLIMB)
    uint8_t m_unk16f8;  // +0x16f8  (C2.2 strict3)
    uint8_t m_unk16f9;  // +0x16f9  (C2.2 strict3)
    uint8_t m_pad16fa[2];
    uint32_t m_unk16fc;  // +0x16fc  (C2.2 strict3)
    float m_unk1700[3];                          // +0x1700 (step 6 CLIMB)
    float m_unk170c[3];                          // +0x170c (step 6 CLIMB)
    uint32_t m_pad1718[3];
    float m_unk1724;  // +0x1724  (C2.2 strict3)
    float m_unk1728;  // +0x1728  (C2.2 strict3)
    float m_unk172c;  // +0x172c  (C2.2 strict3)
    float m_unk1730;  // +0x1730  (C2.2 strict3)
    float m_unk1734;  // +0x1734  (C2.2 strict3)
    float m_unk1738;  // +0x1738  (C2.2 strict3)
    float m_unk173c;  // +0x173c  (C2.2 strict3)
    uint32_t m_unk1740;  // +0x1740  (C2.2 strict3)
    uint32_t m_unk1744;                          // +0x1744 (tested non-zero by the AI follow handler)
    float m_unk1748;  // +0x1748  (C2.2 strict3)
    float m_unk174c;  // +0x174c  (C2.2 strict3)
    float m_unk1750;  // +0x1750  (C2.2 strict3)
    float m_unk1754;  // +0x1754  (C2.2 strict3; the mount blend length, a float: step 6 CLIMB)
    float m_unk1758;  // +0x1758  (C2.2 strict3)
    uint32_t m_unk175c;  // +0x175c  (C2.2 strict3)
    uint8_t m_unk1760;  // +0x1760  (C2.2 strict3)
    uint8_t m_pad1761[3];
    float m_unk1764;  // +0x1764  (C2.2 strict3)
    float m_unk1768;  // +0x1768  (C2.2 strict3)
    float m_unk176c;  // +0x176c  (C2.2 strict3)
    uint32_t m_unk1770;  // +0x1770  (C2.2 strict3)
    uint32_t m_unk1774;  // +0x1774  (C2.2 strict3)
    float m_unk1778;  // +0x1778  (C2.2 strict3)
    float m_unk177c;  // +0x177c  (C2.2 strict3)
    float m_unk1780;  // +0x1780  (C2.2 strict3)
    uint8_t m_unk1784;  // +0x1784  (C2.2 strict3)
    uint8_t m_pad1785[3];
    float m_unk1788;  // +0x1788  (C2.2 strict3)
    uint8_t m_unk178c;  // +0x178c  (C2.2 strict3)
    uint8_t m_pad178d[3];
    CVector3 m_unk1790;  // +0x1790
    CVector3 m_unk179c;  // +0x179c
    CVector3 m_unk17a8;  // +0x17a8
    CVector3 m_unk17b4;  // +0x17b4
    CVector3 m_unk17c0;  // +0x17c0
    CVector3 m_unk17cc;  // +0x17cc
    CVector3 m_unk17d8;  // +0x17d8
    CVector3 m_unk17e4;  // +0x17e4
    float m_unk17f0;                             // +0x17f0 (locomotion)
    float m_unk17f4;                             // +0x17f4 (locomotion)
    float m_unk17f8;                             // +0x17f8 (locomotion)
    float m_unk17fc;  // +0x17fc  (C2.2 strict3)
    float m_unk1800;  // +0x1800  (C2.2 strict3)
    float m_unk1804;  // +0x1804  (C2.2 strict3)
    uint8_t m_ui8MovementMode;  // +0x1808  (C2.2 strict3)
    uint8_t m_bTakeOffPending;  // +0x1809  (C2.2 strict3)
    uint8_t m_bMovementModeChanged;                           // +0x180a (the movement mode changed this frame, SetMovementMode)
    uint8_t m_pad180b[1];
    float m_unk180c;  // +0x180c  (C2.2 strict3)
    uint8_t m_unk1810;  // +0x1810  (C2.2 strict3)
    uint8_t m_unk1811;  // +0x1811  (C2.2 strict3)
    uint8_t m_unk1812;  // +0x1812  (C2.2 strict3)
    uint8_t m_unk1813;  // +0x1813  (C2.2 strict3)
    uint8_t m_unk1814;  // +0x1814  (C2.2 strict3)
    uint8_t m_unk1815;  // +0x1815  (C2.2 strict3)
    uint8_t m_pad1816[2];
    IKSerializable* m_pCameraTargetNode;                   // +0x1818 CSGLeaf*
    float m_unk181c;  // +0x181c  (C2.2 strict3)
    float m_unk1820;  // +0x1820  (C2.2 strict3)
    float m_unk1824;  // +0x1824  (C2.2 strict3)
    float m_unk1828;  // +0x1828 the side factor a ground run state starts with when +0xecc bit 16 (GroundAnimState05/06)
    float m_unk182c;  // +0x182c  (C2.2 strict3; 0.2 then 0 by GroundAnimState05/06's enter)
    float m_unk1830;  // +0x1830 the shared time of the locomotion / side blend pair (UpdateLocomotionAnimationBlend)
    float m_unk1834;  // +0x1834 its previous value (UpdateAnimationMarkFlags)
    uint8_t m_unk1838;  // +0x1838  (C2.2 strict3)
    uint8_t m_unk1839;  // +0x1839  (C2.2 strict3)
    uint8_t m_pad183a[2];
    uint32_t m_unk183c;  // +0x183c  (C2.2 spyro)
    uint32_t m_unk1840;  // +0x1840  (C2.2 spyro)
    uint32_t m_unk1844;  // +0x1844  (C2.2 spyro)
    uint32_t m_unk1848;  // +0x1848  (C2.2 spyro)
    uint32_t m_unk184c;  // +0x184c  (C2.2 spyro)
    uint32_t m_unk1850;  // +0x1850  (C2.2 spyro)
    uint32_t m_unk1854;  // +0x1854  (C2.2 spyro)
    uint32_t m_unk1858;  // +0x1858  (C2.2 spyro)
    uint32_t m_unk185c;  // +0x185c  (C2.2 spyro)
    uint32_t m_unk1860;  // +0x1860  (C2.2 spyro)
    uint32_t m_unk1864;  // +0x1864  (C2.2 spyro)
    uint32_t m_unk1868;  // +0x1868  (C2.2 spyro)
    uint32_t m_unk186c;  // +0x186c  (C2.2 spyro)
    uint32_t m_unk1870;  // +0x1870  (C2.2 spyro)
    uint32_t m_unk1874;  // +0x1874  (C2.2 spyro)
    uint32_t m_unk1878;  // +0x1878  (C2.2 spyro)
    uint32_t m_unk187c;  // +0x187c  (C2.2 spyro)
    uint32_t m_unk1880;  // +0x1880  (C2.2 spyro)
    uint32_t m_unk1884;  // +0x1884  (C2.2 spyro)
    uint32_t m_unk1888;  // +0x1888  (C2.2 spyro)
    uint32_t m_unk188c;  // +0x188c  (C2.2 spyro)
    uint32_t m_unk1890;  // +0x1890  (C2.2 spyro)
    uint32_t m_unk1894;  // +0x1894  (C2.2 spyro)
    uint32_t m_unk1898;  // +0x1898  (C2.2 spyro)
    uint32_t m_unk189c;  // +0x189c  (C2.2 spyro)
    uint32_t m_unk18a0;  // +0x18a0  (C2.2 spyro)
    uint32_t m_unk18a4;  // +0x18a4  (C2.2 spyro)
    uint32_t m_unk18a8;  // +0x18a8  (C2.2 spyro)
    uint32_t m_unk18ac;  // +0x18ac  (C2.2 spyro)
    uint32_t m_unk18b0;  // +0x18b0  (C2.2 spyro)
    uint32_t m_unk18b4;  // +0x18b4  (C2.2 spyro)
    uint32_t m_unk18b8;  // +0x18b8  (C2.2 spyro)
    uint32_t m_unk18bc;  // +0x18bc  (C2.2 spyro)
    uint32_t m_unk18c0;  // +0x18c0  (C2.2 spyro)
    uint32_t m_unk18c4;  // +0x18c4  (C2.2 spyro)
    uint32_t m_unk18c8;  // +0x18c8  (C2.2 spyro)
    void* m_unk18cc;  // +0x18cc  (C2.2 spyro)
    uint8_t m_ui8FlyAnimState;                           // +0x18d0 constructor 0xff
    uint8_t m_unk18d1;                           // +0x18d1 constructor 0xff
    uint8_t m_pad18d2[2];
    uint32_t m_unk18d4;  // +0x18d4  (C2.2 spyro)
    uint32_t m_unk18d8;  // +0x18d8  (C2.2 spyro)
    uint32_t m_unk18dc;  // +0x18dc  (C2.2 spyro)
    uint32_t m_unk18e0;  // +0x18e0  (C2.2 spyro)
    uint32_t m_unk18e4;  // +0x18e4  (C2.2 spyro)
    uint32_t m_unk18e8;  // +0x18e8  (C2.2 spyro)
    uint32_t m_unk18ec;  // +0x18ec  (C2.2 spyro)
    uint32_t m_unk18f0;  // +0x18f0  (C2.2 spyro)
    uint32_t m_unk18f4;  // +0x18f4  (C2.2 spyro)
    uint32_t m_unk18f8;  // +0x18f8  (C2.2 spyro)
    uint32_t m_unk18fc;  // +0x18fc  (C2.2 spyro)
    uint32_t m_unk1900;  // +0x1900  (C2.2 spyro)
    uint32_t m_unk1904;  // +0x1904  (C2.2 spyro)
    uint32_t m_unk1908;  // +0x1908  (C2.2 spyro)
    uint32_t m_unk190c;  // +0x190c  (C2.2 spyro)
    uint32_t m_unk1910;  // +0x1910  (C2.2 spyro)
    uint32_t m_unk1914;  // +0x1914  (C2.2 spyro)
    uint32_t m_unk1918;  // +0x1918  (C2.2 spyro)
    uint32_t m_unk191c;  // +0x191c  (C2.2 spyro)
    uint32_t m_unk1920;  // +0x1920  (C2.2 spyro)
    uint32_t m_unk1924;  // +0x1924  (C2.2 spyro)
    uint32_t m_unk1928;  // +0x1928  (C2.2 spyro)
    uint32_t m_unk192c;  // +0x192c  (C2.2 spyro)
    uint32_t m_unk1930;  // +0x1930  (C2.2 spyro)
    uint32_t m_unk1934;  // +0x1934  (C2.2 spyro)
    uint32_t m_unk1938;  // +0x1938  (C2.2 spyro)
    uint32_t m_unk193c;  // +0x193c  (C2.2 spyro)
    uint32_t m_unk1940;  // +0x1940  (C2.2 spyro)
    uint32_t m_unk1944;  // +0x1944  (C2.2 spyro)
    uint32_t m_unk1948;  // +0x1948  (C2.2 spyro)
    uint32_t m_unk194c;  // +0x194c  (C2.2 spyro)
    uint32_t m_unk1950;  // +0x1950  (C2.2 spyro)
    uint32_t m_unk1954;  // +0x1954  (C2.2 spyro)
    uint32_t m_unk1958;  // +0x1958  (C2.2 spyro)
    void* m_unk195c;  // +0x195c  (C2.2 spyro)
    uint8_t m_ui8GroundAnimState;                           // +0x1960 constructor 0xff
    uint8_t m_unk1961;                           // +0x1961 constructor 0xff
    uint8_t m_pad1962[2];
    uint32_t m_unk1964;  // +0x1964  (C2.2 spyro)
    uint32_t m_unk1968;  // +0x1968  (C2.2 spyro)
    uint32_t m_unk196c;  // +0x196c  (C2.2 spyro)
    uint32_t m_unk1970;  // +0x1970  (C2.2 spyro)
    uint32_t m_unk1974;  // +0x1974  (C2.2 spyro)
    uint32_t m_unk1978;  // +0x1978  (C2.2 spyro)
    uint32_t m_unk197c;  // +0x197c  (C2.2 spyro)
    uint32_t m_unk1980;  // +0x1980  (C2.2 spyro)
    uint32_t m_unk1984;  // +0x1984  (C2.2 spyro)
    uint32_t m_unk1988;  // +0x1988  (C2.2 spyro)
    uint32_t m_unk198c;  // +0x198c  (C2.2 spyro)
    uint32_t m_unk1990;  // +0x1990  (C2.2 spyro)
    uint32_t m_unk1994;  // +0x1994  (C2.2 spyro)
    uint32_t m_unk1998;  // +0x1998  (C2.2 spyro)
    uint32_t m_unk199c;  // +0x199c  (C2.2 spyro)
    uint32_t m_unk19a0;  // +0x19a0  (C2.2 spyro)
    void* m_unk19a4;  // +0x19a4  (C2.2 spyro)
    uint8_t m_ui8ClimbAnimState;                           // +0x19a8 constructor 0xff
    uint8_t m_unk19a9;                           // +0x19a9 constructor 0xff
    uint8_t m_pad19aa[2];
    float m_unk19ac;  // +0x19ac  (C2.2 strict3; a float: the idle variation timer)
    uint16_t m_unk19b0;  // +0x19b0  (C2.2 strict3)
    uint8_t m_pad19b2[2];
    IKSerializable* m_unk19b4;                   // +0x19b4 CKElectricArcFxData*
    IKSerializable* m_unk19b8;  // +0x19b8  (C2.2 strict3)
    IKSerializable* m_unk19bc;                   // +0x19bc CKElectricArcFxData*
    IKSerializable* m_unk19c0;  // +0x19c0  (C2.2 strict3)
    IKSerializable* m_unk19c4;                   // +0x19c4 CKLightningBoltFxData*
    IKSerializable* m_unk19c8;  // +0x19c8  (C2.2 strict3)
    IKSerializable* m_unk19cc;                   // +0x19cc CKLightningBoltFxData*
    IKSerializable* m_unk19d0;  // +0x19d0  (C2.2 strict3)
    IKSerializable* m_unk19d4;                   // +0x19d4 CKSparkFxData*
    IKSerializable* m_unk19d8;  // +0x19d8 CKSparkNodeFx* the partner link's far spark (+0x19d4's, UpdatePartnerLinkFx)
    IKSerializable* m_unk19dc;                   // +0x19dc CKSparkFxData*
    IKSerializable* m_unk19e0;  // +0x19e0 CKSparkNodeFx* the flight spark (+0x19dc's, UpdateShadowsAndFlightFx)
    IKSerializable* m_unk19e4;                   // +0x19e4 CKSparkFxData*
    IKSerializable* m_unk19e8;  // +0x19e8 CKSparkNodeFx* the air-current flight spark (+0x19e4's)
    uint32_t m_pad19ec;
    IKSerializable* m_unk19f0;                   // +0x19f0
    IKSerializable* m_unk19f4;  // +0x19f4 the dust particle effect (UpdateTrailAndFootstepFx, animations 0x63 / 0x67)
    IKSerializable* m_unk19f8;                   // +0x19f8 CKFlashFxData*
    IKSerializable* m_unk19fc;                   // +0x19fc CKExplosionFxData*
    IKSerializable* m_unk1a00;                   // +0x1a00 CKExplosionFxData*
    IKSerializable* m_unk1a04;                   // +0x1a04 CKTargetCursorFxData*
    IKFx* m_unk1a08;  // +0x1a08 the switch feedback's target cursor effect (SetSwitchFeedbackFxActive)
    float m_unk1a0c;  // +0x1a0c  (C2.2 strict3; the health share time (UpdateHeroHealthAndManaSharing))
    float m_unk1a10;  // +0x1a10  (C2.2 strict3; the mana share time)
    uint8_t m_unk1a14;  // +0x1a14  (C2.2 strict3)
    uint8_t m_pad1a15[3];
    uint32_t m_unk1a18;  // +0x1a18  (C2.2 spyro)
    uint32_t m_unk1a1c;  // +0x1a1c  (C2.2 spyro)
    uint32_t m_unk1a20;  // +0x1a20  (C2.2 spyro)
    IKSerializable** m_apUnk1a24;                // +0x1a24 inlined array {data, capacity +0x1a28, size +0x1a2c}; PostLoad calls vt+0x98 on each (Ghidra dwComboObjArray)
    uint32_t m_unk1a28;                          // +0x1a28 capacity (constructor 1)
    uint32_t m_unk1a2c;                          // +0x1a2c size (constructor 0)
    IKSerializable** m_apUnk1a30;                // +0x1a30 inlined array of 3 references (capacity +0x1a34, size +0x1a38)
    uint32_t m_unk1a34;                          // +0x1a34 capacity (constructor 1)
    uint32_t m_unk1a38;                          // +0x1a38 size (constructor 0)
    float m_unk1a3c;                             // +0x1a3c
    float m_unk1a40;                             // +0x1a40
    float m_unk1a44;                             // +0x1a44
    float m_unk1a48;                             // +0x1a48
    float m_unk1a4c;                             // +0x1a4c
    float m_unk1a50;                             // +0x1a50
    float m_unk1a54;                             // +0x1a54
    float m_unk1a58;                             // +0x1a58
    float m_unk1a5c;                             // +0x1a5c
    float m_unk1a60;                             // +0x1a60
    float m_unk1a64;                             // +0x1a64
    float m_unk1a68;                             // +0x1a68
    float m_unk1a6c;                             // +0x1a6c
    float m_unk1a70;                             // +0x1a70
    float m_unk1a74;                             // +0x1a74
    IKSerializable* m_unk1a78;                   // +0x1a78 CKAimCamembert*
    IKSerializable* m_unk1a7c;                   // +0x1a7c CKAimCamembert*
    uint32_t m_pad1a80;
    uint32_t m_unk1a84;  // +0x1a84  (C2.2 strict3)
    IKSerializable* m_pCurrentComboNode;  // +0x1a88  (C2.2 spyro)
    IKSerializable* m_unk1a8c;                   // +0x1a8c CKS08HeroCombo*
    IKSerializable* m_unk1a90;                   // +0x1a90 CKS08HeroCombo*
    IKSerializable* m_unk1a94;                   // +0x1a94 CKS08HeroCombo*
    IKSerializable* m_unk1a98;                   // +0x1a98 CKS08HeroCombo*
    IKSerializable* m_unk1a9c;                   // +0x1a9c CKS08HeroCombo*
    IKSerializable* m_unk1aa0;                   // +0x1aa0 CKS08HeroCombo*
    IKSerializable* m_unk1aa4;                   // +0x1aa4 CKS08HeroCombo*
    float m_unk1aa8;  // +0x1aa8 SetComboActive: -1
    float m_unk1aac;  // +0x1aac SetComboActive: the blow's vt+0x70
    int16_t m_unk1ab0;   // +0x1ab0 the grabbed enemy's paired animation (AnimState7_ComboAnim)
    uint16_t m_unk1ab2;  // +0x1ab2  (C2.2 strict3)
    uint8_t m_unk1ab4;  // +0x1ab4  (C2.2 strict3)
    uint8_t m_unk1ab5;  // +0x1ab5  (C2.2 strict3)
    uint8_t m_unk1ab6;  // +0x1ab6  (C2.2 strict3)
    uint8_t m_pad1ab7[1];
    uint32_t m_unk1ab8;  // +0x1ab8  (C2.2 strict3)
    uint8_t m_unk1abc;  // +0x1abc  (C2.2 strict3)
    uint8_t m_unk1abd;  // +0x1abd  (C2.2 strict3)
    uint8_t m_unk1abe;  // +0x1abe  (C2.2 strict3)
    uint8_t m_unk1abf;  // +0x1abf  (C2.2 strict3)
    uint8_t m_unk1ac0;  // +0x1ac0  (C2.2 strict3)
    uint8_t m_unk1ac1;  // +0x1ac1  (C2.2 strict3)
    uint8_t m_unk1ac2;  // +0x1ac2  (C2.2 strict3)
    uint8_t m_unk1ac3;  // +0x1ac3  (C2.2 strict3)
    uint8_t m_unk1ac4;  // +0x1ac4  (C2.2 strict3)
    uint8_t m_unk1ac5;  // +0x1ac5  (C2.2 strict3)
    uint8_t m_unk1ac6;  // +0x1ac6  (C2.2 strict3)
    uint8_t m_unk1ac7;  // +0x1ac7  (C2.2 strict3)
    uint8_t m_unk1ac8;  // +0x1ac8  (C2.2 strict3)
    uint8_t m_unk1ac9;  // +0x1ac9  (C2.2 strict3)
    uint8_t m_unk1aca;  // +0x1aca  (C2.2 strict3)
    uint8_t m_unk1acb;  // +0x1acb  (C2.2 strict3)
    uint8_t m_unk1acc;  // +0x1acc  (C2.2 strict3)
    uint8_t m_unk1acd;  // +0x1acd  (C2.2 strict3)
    uint8_t m_unk1ace;  // +0x1ace  (C2.2 strict3)
    uint8_t m_unk1acf;  // +0x1acf  (C2.2 strict3)
    uint8_t m_unk1ad0;  // +0x1ad0  (C2.2 strict3)
    uint8_t m_unk1ad1;  // +0x1ad1  (C2.2 strict3)
    uint8_t m_unk1ad2;  // +0x1ad2  (C2.2 strict3)
    uint8_t m_unk1ad3;  // +0x1ad3  (C2.2 strict3)
    uint32_t m_unk1ad4;  // +0x1ad4  (C2.2 strict3)
    uint32_t m_unk1ad8;  // +0x1ad8  (C2.2 strict3)
    uint32_t m_unk1adc;  // +0x1adc  (C2.2 strict3)
    IKSerializable* m_unk1ae0;                   // +0x1ae0 CKAnimatedCameraData*
    IKSerializable* m_unk1ae4;                   // +0x1ae4 CKExplosionFxData*
    uint32_t m_unk1ae8;  // +0x1ae8  (C2.2 strict3)
    float m_unk1aec;  // +0x1aec  (C2.2 strict3)
    float m_unk1af0;  // +0x1af0 SetComboActive: the grab blow's throw delay (vt+0xa4)
    float m_unk1af4;  // +0x1af4 SetComboActive: the grab blow's release delay (vt+0xa8)
    uint32_t m_unk1af8;  // +0x1af8  (C2.2 strict3)
    float m_unk1afc;  // +0x1afc  (C2.2 strict3)
    float m_unk1b00;  // +0x1b00  (C2.2 strict3)
    float m_unk1b04;  // +0x1b04  (C2.2 strict3)
    float m_unk1b08;  // +0x1b08 the time above the fall-damage height (ApplyTimedHeroDamage)
    float m_unk1b0c;  // +0x1b0c  (C2.2 strict3)
    float m_unk1b10;  // +0x1b10  (C2.2 strict3)
    float m_unk1b14;  // +0x1b14  (C2.2 strict3)
    float m_unk1b18;  // +0x1b18  (C2.2 strict3)
    IKSerializable* m_unk1b1c;                   // +0x1b1c CKExplosionFxData*
    IKSerializable* m_unk1b20;                   // +0x1b20 CKExplosionFxData*
    IKSerializable* m_unk1b24;                   // +0x1b24 CKExplosionFxData*
    IKSerializable* m_unk1b28;                   // +0x1b28 CKAnimatedCamera*
    float m_fExtraMass;  // +0x1b2c the extra mass with +0xed4 bit 0 (GetMass 0x2f8818; the armour _maybe)
    float m_unk1b30;  // +0x1b30 a timer counted down by the frame dt (ApplyGrabbedEnemyMarkDamage)
    float m_unk1b34;  // +0x1b34  (C2.2 strict2/3)
    float m_unk1b38;  // +0x1b38  (C2.2 strict3)
    float m_unk1b3c;  // +0x1b3c  (C2.2 strict3)
    uint32_t m_unk1b40;  // +0x1b40  (C2.2 strict3)
    float m_unk1b44;  // +0x1b44  (C2.2 strict3)
    float m_unk1b48;  // +0x1b48  (C2.2 strict3)
    float m_unk1b4c;  // +0x1b4c  (C2.2 strict3)
    IKSerializable* m_unk1b50;                   // +0x1b50 CKS08HeroDamage*
    IKSerializable* m_unk1b54;                   // +0x1b54 CKS08Damage*
    IKSerializable* m_unk1b58;                   // +0x1b58 CKExplosionFxData*
    IKSerializable* m_unk1b5c;                   // +0x1b5c CKExplosionFxData*
    IKSerializable* m_unk1b60;                   // +0x1b60 CKS08Damage*
    IKSerializable* m_unk1b64;                   // +0x1b64
    IKSerializable* m_unk1b68;  // +0x1b68 the aura particles (UpdateRegenAndElementTimeout)
    IKSerializable* m_unk1b6c;                   // +0x1b6c CKBonusData*
    IKSerializable* m_unk1b70;                   // +0x1b70 CKBonusData*
    IKSerializable* m_unk1b74;                   // +0x1b74 CKBonusData*
    float m_unk1b78;  // +0x1b78  (C2.2 strict3; a float: UpdateRegenAndElementTimeout)
    float m_unk1b7c;  // +0x1b7c  (C2.2 strict3; a float: UpdateRegenAndElementTimeout)
    float m_unk1b80;  // +0x1b80  (C2.2 strict3; a float: UpdateRegenAndElementTimeout)
    float m_unk1b84;  // +0x1b84  (C2.2 strict3; a float: UpdateRegenAndElementTimeout)
    float m_unk1b88;  // +0x1b88  (C2.2 strict3; a float: UpdateRegenAndElementTimeout)
    IKSerializable* m_unk1b8c;  // +0x1b8c  (C2.2 strict3)
    IKSerializable* m_unk1b90;  // +0x1b90  (C2.2 strict3)
    IKSerializable* m_unk1b94;  // +0x1b94  (C2.2 strict3)
    IKSerializable* m_unk1b98;  // +0x1b98  (C2.2 strict3)
    IKSerializable* m_apActiveHitSpheres[4];  // +0x1b9c the active hit spheres (CKHkS08Hero_GetActiveHitSpheres 0x329de0; count +0x1bac)
    uint32_t m_ui32ActiveHitSphereCount;  // +0x1bac  (C2.2 strict3)
    uint8_t m_unk1bb0;  // +0x1bb0  (C2.2 strict3)
    uint8_t m_pad1bb1[3];
    uint32_t m_unk1bb4;  // +0x1bb4  (C2.2 strict3)
    uint32_t m_unk1bb8;  // +0x1bb8  (C2.2 strict3)
    uint32_t m_unk1bbc;  // +0x1bbc  (C2.2 strict3)
    uint32_t m_unk1bc0;  // +0x1bc0  (C2.2 strict3)
    uint32_t m_unk1bc4;  // +0x1bc4  (C2.2 strict3)
    uint32_t m_unk1bc8;  // +0x1bc8  (C2.2 strict3)
    uint32_t m_unk1bcc;  // +0x1bcc  (C2.2 strict3)
    IKSerializable* m_apAbilities[10];             // +0x1bd0 10 references, one read each (CKPoisonSpin first, struct draft)
    float m_afAbilityCooldown[10];  // +0x1bf8 per ability (ActState4_Ability_Condition counts them down)
    uint32_t m_unk1c20;                          // +0x1c20 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c24;                          // +0x1c24 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c28;                          // +0x1c28 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c2c;                          // +0x1c2c read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c30;                          // +0x1c30 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c34;                          // +0x1c34 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c38;                          // +0x1c38 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c3c;                          // +0x1c3c read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c40;                          // +0x1c40 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c44;                          // +0x1c44 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c48;                          // +0x1c48 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c4c;                          // +0x1c4c read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c50;                          // +0x1c50 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c54;                          // +0x1c54 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c58;                          // +0x1c58 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c5c;                          // +0x1c5c read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c60;                          // +0x1c60 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c64;                          // +0x1c64 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c68;                          // +0x1c68 read raw (4 colour bytes, RGBA_maybe)
    uint32_t m_unk1c6c;                          // +0x1c6c read raw (4 colour bytes, RGBA_maybe)
    int32_t m_unk1c70;                           // +0x1c70
    int32_t m_unk1c74;                           // +0x1c74
    int32_t m_unk1c78;                           // +0x1c78
    int32_t m_unk1c7c;                           // +0x1c7c
    int32_t m_unk1c80;                           // +0x1c80
    int32_t m_unk1c84;                           // +0x1c84
    int32_t m_unk1c88;                           // +0x1c88
    uint32_t m_unk1c8c;                          // +0x1c8c
    uint32_t m_unk1c90;                          // +0x1c90
    int32_t m_unk1c94;                           // +0x1c94
    int32_t m_unk1c98;                           // +0x1c98
    int32_t m_unk1c9c;                           // +0x1c9c
    int32_t m_unk1ca0;                           // +0x1ca0
    int32_t m_unk1ca4;                           // +0x1ca4
    int32_t m_unk1ca8;                           // +0x1ca8
    int32_t m_unk1cac;                           // +0x1cac
    int32_t m_unk1cb0;                           // +0x1cb0
    int32_t m_unk1cb4;                           // +0x1cb4
    uint32_t m_unk1cb8;                          // +0x1cb8
    int32_t m_unk1cbc;                           // +0x1cbc
    IKSerializable* m_pActiveAbility;  // +0x1cc0 an object of class 0xa50c while hero 1 uses the wind beam (IsUsingWindBeam)
    uint32_t m_unk1cc4;  // +0x1cc4  (C2.2 strict3)
    uint32_t m_unk1cc8;  // +0x1cc8  (C2.2 strict3)
    IKSerializable* m_unk1ccc;                   // +0x1ccc CKFilterFxData*
    IKSerializable* m_unk1cd0;                   // +0x1cd0 CKFilterFxData*
    IKSerializable* m_unk1cd4;                   // +0x1cd4 CKFilterFxData*
    IKSerializable* m_unk1cd8;                   // +0x1cd8 CKFilterFxData*
    IKSerializable* m_unk1cdc;                   // +0x1cdc CKFilterFxData*
    IKSerializable* m_unk1ce0;                   // +0x1ce0 CKFilterFxData*
    IKSerializable* m_unk1ce4;                   // +0x1ce4 CKFilterFxData*
    IKSerializable* m_unk1ce8;                   // +0x1ce8 CKFilterFxData*
    IKSerializable* m_unk1cec;                   // +0x1cec CKFilterFxData*
    IKSerializable* m_unk1cf0;                   // +0x1cf0 CKFilterFxData*
    IKSerializable* m_unk1cf4;  // +0x1cf4  (C2.2 strict3)
    IKSerializable* m_unk1cf8;                   // +0x1cf8 CKQuakeCameraLauncher*
    float m_unk1cfc;  // +0x1cfc the ability quake timer (ActAbility)
    float m_unk1d00;                             // +0x1d00
    float m_unk1d04;  // +0x1d04  (C2.2 strict3)
    float m_unk1d08;  // +0x1d08  (C2.2 strict3)
    float m_unk1d0c;  // +0x1d0c the ability turn rate (SetAbilityTurnParams: +0x1d04, else +0xaf8)
    uint8_t m_unk1d10;  // +0x1d10  (C2.2 strict3)
    uint8_t m_unk1d11;  // +0x1d11  (C2.2 strict3)
    uint8_t m_pad1d12[2];
    float m_unk1d14;  // +0x1d14  (C2.2 strict3)
    uint8_t m_unk1d18;  // +0x1d18  (C2.2 strict3)
    uint8_t m_pad1d19[3];
    float m_unk1d1c;  // +0x1d1c  (C2.2 strict3)
    float m_fAbilityAnimSpeedScale;  // +0x1d20  (C2.2 strict3)
    float m_fAbilityFuryTimer;  // +0x1d24 the ability fury timer (ActAbility, 0.3 s)
    IKSerializable* m_pFlightAimEnemy;  // +0x1d28 the enemy aimed at in flight (UpdateFlyingLocomotion: FindBestEnemyInAimCone)
    float m_unk1d2c;  // +0x1d2c  (C2.2 strict3)
    float m_unk1d30;  // +0x1d30  (C2.2 strict3)
    float m_unk1d34;  // +0x1d34  (C2.2 strict3)
    IKSerializable* m_pFlightAimCone;                   // +0x1d38 CKAimCamembert*
    float m_unk1d3c;  // +0x1d3c  (C2.2 strict3)
    uint32_t m_unk1d40;  // +0x1d40  (C2.2 strict3)
    uint8_t m_unk1d44;  // +0x1d44  (C2.2 strict3)
    uint8_t m_pad1d45[3];
    float m_unk1d48;  // +0x1d48  (C2.2 strict3)
    float m_unk1d4c;  // +0x1d4c  (C2.2 strict3)
    float m_unk1d50;  // +0x1d50  (C2.2 strict3)
    uint32_t m_unk1d54;  // +0x1d54  (C2.2 strict3)
    uint32_t m_unk1d58;  // +0x1d58  (C2.2 strict3)
    float m_unk1d5c;  // +0x1d5c  (C2.2 strict3)
    uint32_t m_unk1d60;  // +0x1d60  (C2.2 strict3)
    uint8_t m_unk1d64;  // +0x1d64  (C2.2 strict3)
    uint8_t m_pad1d65[3];
    float m_unk1d68;  // +0x1d68  (C2.2 strict3)
    float m_unk1d6c;  // +0x1d6c  (C2.2 strict3)
    float m_unk1d70;  // +0x1d70  (C2.2 strict3)
    uint32_t m_unk1d74;  // +0x1d74  (C2.2 strict3)
    uint32_t m_unk1d78;  // +0x1d78  (C2.2 strict3)
    float m_unk1d7c;  // +0x1d7c  (C2.2 strict3)
    uint32_t m_unk1d80;  // +0x1d80  (C2.2 strict3)
    uint8_t m_unk1d84;  // +0x1d84  (C2.2 strict3)
    uint8_t m_pad1d85[3];
    float m_unk1d88;  // +0x1d88  (C2.2 strict3)
    float m_unk1d8c;  // +0x1d8c  (C2.2 strict3)
    float m_unk1d90;  // +0x1d90  (C2.2 strict3)
    uint32_t m_unk1d94;  // +0x1d94  (C2.2 strict3)
    uint32_t m_unk1d98;  // +0x1d98  (C2.2 strict3)
    float m_unk1d9c;  // +0x1d9c  (C2.2 strict3)
    float m_unk1da0;  // +0x1da0 the flight impulse time (InitFlightField1D9CBlock: 0.01)
    uint8_t m_unk1da4;  // +0x1da4  (C2.2 strict3)
    uint8_t m_pad1da5[3];
    float m_unk1da8;  // +0x1da8  (C2.2 strict3)
    float m_unk1dac;  // +0x1dac  (C2.2 strict3)
    float m_unk1db0;  // +0x1db0  (C2.2 strict3)
    uint32_t m_unk1db4;  // +0x1db4  (C2.2 strict3)
    uint32_t m_unk1db8;  // +0x1db8  (C2.2 strict3)
    IKSerializable* m_unk1dbc;                   // +0x1dbc CKS08HeroDamage*
    uint8_t m_unk1dc0;  // +0x1dc0  (C2.2 strict3)
    uint8_t m_pad1dc1[3];
    IKSerializable* m_unk1dc4;                   // +0x1dc4 CGlowNodeFx*
    IKSerializable* m_unk1dc8;                   // +0x1dc8 CKPointLightFxData*
    IKSerializable* m_unk1dcc;  // +0x1dcc  (C2.2 strict3)
    uint8_t m_unk1dd0;  // +0x1dd0  (C2.2 strict3)
    uint8_t m_unk1dd1;  // +0x1dd1  (C2.2 strict3)
    uint8_t m_pad1dd2[2];
    IKSerializable* m_unk1dd4;                   // +0x1dd4 CKExplosionFxData*
    IKSerializable* m_unk1dd8;                   // +0x1dd8 CKExplosionFxData*
    IKSerializable* m_unk1ddc;                   // +0x1ddc CKS08StunDamage*
    IKSerializable* m_unk1de0;                   // +0x1de0 CNode*
    IKSerializable* m_unk1de4;                   // +0x1de4 CKMoveCpnt*
    IKSerializable* m_unk1de8;                   // +0x1de8 CKMoveCpntUpdater*
    IKSerializable* m_unk1dec;                   // +0x1dec CKCurve2DCpnt*
    IKSerializable* m_unk1df0;                   // +0x1df0 CKMeshPopFxData*
    IKSerializable* m_unk1df4;  // +0x1df4 the fury charge's mesh pop (a CKMeshPopNodeFx; SpawnFuryChargeFx)
    class CKS08HeroAbilityHost* m_pAbilityHost;  // +0x1df8 the ability host (ActAbility builds it)
    uint8_t m_unk1dfc;                           // +0x1dfc (the side blend flag while climbing, UpdateAnimation)
    uint8_t m_pad1dfd[3];
};
DOTD_ASSERT_SIZE(CKHkS08Hero, 0x1e00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk89c, 0x89c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8a0, 0x8a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8a4, 0x8a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8a8, 0x8a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8ac, 0x8ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8b0, 0x8b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8b4, 0x8b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8b8, 0x8b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8bc, 0x8bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8c0, 0x8c0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8c4, 0x8c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8c8, 0x8c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8cc, 0x8cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8d0, 0x8d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8d4, 0x8d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8d8, 0x8d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8dc, 0x8dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8e0, 0x8e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8e4, 0x8e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8e8, 0x8e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8ec, 0x8ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8f0, 0x8f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8f4, 0x8f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8f8, 0x8f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk8fc, 0x8fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk900, 0x900);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk904, 0x904);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk908, 0x908);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk90c, 0x90c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk910, 0x910);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk914, 0x914);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk918, 0x918);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk91c, 0x91c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk920, 0x920);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk924, 0x924);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk928, 0x928);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk92c, 0x92c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk930, 0x930);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk934, 0x934);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk938, 0x938);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk93c, 0x93c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk940, 0x940);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk944, 0x944);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk948, 0x948);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk94c, 0x94c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk950, 0x950);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk954, 0x954);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk958, 0x958);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk95c, 0x95c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk960, 0x960);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk964, 0x964);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk968, 0x968);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk96c, 0x96c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk970, 0x970);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk974, 0x974);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk978, 0x978);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk97c, 0x97c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk980, 0x980);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk984, 0x984);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk988, 0x988);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk98c, 0x98c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk990, 0x990);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk994, 0x994);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk998, 0x998);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk99c, 0x99c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9a0, 0x9a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9a4, 0x9a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9a8, 0x9a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9ac, 0x9ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9b0, 0x9b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9b4, 0x9b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9b8, 0x9b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9bc, 0x9bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9c0, 0x9c0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9c4, 0x9c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9c8, 0x9c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9cc, 0x9cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9d0, 0x9d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9d4, 0x9d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9d8, 0x9d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9dc, 0x9dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9e0, 0x9e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9e4, 0x9e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9e8, 0x9e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9ec, 0x9ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9f0, 0x9f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9f4, 0x9f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9f8, 0x9f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk9fc, 0x9fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka00, 0xa00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka04, 0xa04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka08, 0xa08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka0c, 0xa0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka10, 0xa10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka14, 0xa14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka18, 0xa18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka1c, 0xa1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka20, 0xa20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka24, 0xa24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka28, 0xa28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka2c, 0xa2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka30, 0xa30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka34, 0xa34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka38, 0xa38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka3c, 0xa3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka40, 0xa40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka44, 0xa44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka48, 0xa48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka4c, 0xa4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka50, 0xa50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka54, 0xa54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka58, 0xa58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka5c, 0xa5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka60, 0xa60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka64, 0xa64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka68, 0xa68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka6c, 0xa6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka70, 0xa70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka74, 0xa74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka78, 0xa78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka7c, 0xa7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka80, 0xa80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka84, 0xa84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka88, 0xa88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka8c, 0xa8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka90, 0xa90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka94, 0xa94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka98, 0xa98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unka9c, 0xa9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaa0, 0xaa0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaa4, 0xaa4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaa8, 0xaa8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaac, 0xaac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkab0, 0xab0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkab4, 0xab4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkab8, 0xab8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkabc, 0xabc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkac0, 0xac0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkac4, 0xac4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkac8, 0xac8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkacc, 0xacc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkad0, 0xad0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkad4, 0xad4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkad8, 0xad8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkadc, 0xadc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkae0, 0xae0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkae4, 0xae4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkae8, 0xae8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaec, 0xaec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaf0, 0xaf0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaf4, 0xaf4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkaf8, 0xaf8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkafc, 0xafc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb00, 0xb00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb04, 0xb04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb08, 0xb08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb0c, 0xb0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb10, 0xb10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb14, 0xb14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb18, 0xb18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb1c, 0xb1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb20, 0xb20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb24, 0xb24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb28, 0xb28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb2c, 0xb2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb30, 0xb30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb34, 0xb34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb38, 0xb38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb3c, 0xb3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb40, 0xb40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb44, 0xb44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb48, 0xb48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb4c, 0xb4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb50, 0xb50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb54, 0xb54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb58, 0xb58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb5c, 0xb5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb60, 0xb60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb64, 0xb64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb68, 0xb68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb6c, 0xb6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb70, 0xb70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb74, 0xb74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb78, 0xb78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb7c, 0xb7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb80, 0xb80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb84, 0xb84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb88, 0xb88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb8c, 0xb8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb90, 0xb90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb94, 0xb94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb98, 0xb98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkb9c, 0xb9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkba0, 0xba0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkba4, 0xba4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkba8, 0xba8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbac, 0xbac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbb0, 0xbb0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbb4, 0xbb4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbb8, 0xbb8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbbc, 0xbbc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbc0, 0xbc0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbc4, 0xbc4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbc8, 0xbc8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbcc, 0xbcc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbd0, 0xbd0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbd4, 0xbd4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbd8, 0xbd8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbdc, 0xbdc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbe0, 0xbe0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbe4, 0xbe4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbe8, 0xbe8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbec, 0xbec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbf0, 0xbf0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbf4, 0xbf4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbf8, 0xbf8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkbfc, 0xbfc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc00, 0xc00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc04, 0xc04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc08, 0xc08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc0c, 0xc0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc10, 0xc10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc14, 0xc14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc18, 0xc18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc1c, 0xc1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc20, 0xc20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc24, 0xc24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc28, 0xc28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc2c, 0xc2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc30, 0xc30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc34, 0xc34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc38, 0xc38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc3c, 0xc3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc40, 0xc40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc44, 0xc44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc48, 0xc48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc4c, 0xc4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc50, 0xc50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc54, 0xc54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc58, 0xc58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc5c, 0xc5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc60, 0xc60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc64, 0xc64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc68, 0xc68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc6c, 0xc6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc70, 0xc70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc74, 0xc74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc78, 0xc78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc7c, 0xc7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc80, 0xc80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc84, 0xc84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc88, 0xc88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc8c, 0xc8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc90, 0xc90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc94, 0xc94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc98, 0xc98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkc9c, 0xc9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkca0, 0xca0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkca4, 0xca4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkca8, 0xca8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcac, 0xcac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcb0, 0xcb0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcb4, 0xcb4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcb8, 0xcb8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcbc, 0xcbc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcc0, 0xcc0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcc4, 0xcc4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcc8, 0xcc8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkccc, 0xccc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcd0, 0xcd0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcd4, 0xcd4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcd8, 0xcd8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcdc, 0xcdc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkce0, 0xce0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkce4, 0xce4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkce8, 0xce8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcec, 0xcec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcf0, 0xcf0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcf4, 0xcf4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcf8, 0xcf8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkcfc, 0xcfc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd00, 0xd00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd04, 0xd04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd08, 0xd08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd0c, 0xd0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd10, 0xd10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd14, 0xd14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd18, 0xd18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd1c, 0xd1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd20, 0xd20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd24, 0xd24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd28, 0xd28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd2c, 0xd2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd30, 0xd30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd34, 0xd34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd38, 0xd38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd3c, 0xd3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd40, 0xd40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd44, 0xd44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd48, 0xd48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd4c, 0xd4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd50, 0xd50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd54, 0xd54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd58, 0xd58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd5c, 0xd5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd60, 0xd60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd64, 0xd64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd68, 0xd68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd6c, 0xd6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd70, 0xd70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd74, 0xd74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd78, 0xd78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd7c, 0xd7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd80, 0xd80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd84, 0xd84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd88, 0xd88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd8c, 0xd8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd90, 0xd90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd94, 0xd94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd98, 0xd98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkd9c, 0xd9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkda0, 0xda0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkda4, 0xda4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkda8, 0xda8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdac, 0xdac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdb0, 0xdb0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdb4, 0xdb4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdb8, 0xdb8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdbc, 0xdbc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdc0, 0xdc0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdc4, 0xdc4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdc8, 0xdc8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdcc, 0xdcc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdd0, 0xdd0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdd4, 0xdd4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdd8, 0xdd8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkddc, 0xddc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkde0, 0xde0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkde4, 0xde4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkde8, 0xde8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdec, 0xdec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdf0, 0xdf0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdf4, 0xdf4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdf8, 0xdf8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkdfc, 0xdfc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke00, 0xe00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke04, 0xe04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke08, 0xe08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke0c, 0xe0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke10, 0xe10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke14, 0xe14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke18, 0xe18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke1c, 0xe1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke20, 0xe20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke24, 0xe24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke28, 0xe28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke2c, 0xe2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke30, 0xe30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke34, 0xe34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke38, 0xe38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke3c, 0xe3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke40, 0xe40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke44, 0xe44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke48, 0xe48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke4c, 0xe4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke50, 0xe50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke54, 0xe54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke58, 0xe58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke5c, 0xe5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke60, 0xe60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke64, 0xe64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke68, 0xe68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke6c, 0xe6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke70, 0xe70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke74, 0xe74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke78, 0xe78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke7c, 0xe7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke80, 0xe80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke84, 0xe84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke88, 0xe88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke8c, 0xe8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke90, 0xe90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke94, 0xe94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke98, 0xe98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unke9c, 0xe9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkea0, 0xea0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkea4, 0xea4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkea8, 0xea8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkeac, 0xeac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkeb0, 0xeb0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkeb4, 0xeb4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkeb8, 0xeb8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkebc, 0xebc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkec0, 0xec0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkee8, 0xee8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pCarrierHero, 0xfb8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_apUnkfbc, 0xfbc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkFec, 0xfec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk100c, 0x100c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk102c, 0x102c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk104c, 0x104c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk106c, 0x106c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_apUnk1070, 0x1070);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_animBlendSlot10f0, 0x10f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_tsStartCarrying, 0x114c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_tsHit, 0x1154);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1164, 0x1164);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1168, 0x1168);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk116c, 0x116c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1170, 0x1170);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pFlightImpulsionCpnt, 0x1190);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_gcContact11FC, 0x11fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk130c, 0x130c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1310, 0x1310);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1314, 0x1314);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1318, 0x1318);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk131c, 0x131c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1320, 0x1320);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1324, 0x1324);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1328, 0x1328);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk132c, 0x132c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1330, 0x1330);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1334, 0x1334);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1338, 0x1338);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13a8, 0x13a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13b4, 0x13b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk144c, 0x144c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk147c, 0x147c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1480, 0x1480);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1484, 0x1484);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1488, 0x1488);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk148c, 0x148c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1490, 0x1490);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1494, 0x1494);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1498, 0x1498);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk149c, 0x149c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14a0, 0x14a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14a4, 0x14a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14a8, 0x14a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14ac, 0x14ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14b0, 0x14b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14b4, 0x14b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14b8, 0x14b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14bc, 0x14bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14c0, 0x14c0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14c4, 0x14c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14c8, 0x14c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14cc, 0x14cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14d0, 0x14d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14d4, 0x14d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14d8, 0x14d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk14dc, 0x14dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16b8, 0x16b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16c4, 0x16c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pCameraTargetNode, 0x1818);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_ui8FlyAnimState, 0x18d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18d1, 0x18d1);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_ui8GroundAnimState, 0x1960);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1961, 0x1961);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_ui8ClimbAnimState, 0x19a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19a9, 0x19a9);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19b4, 0x19b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19bc, 0x19bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19c4, 0x19c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19cc, 0x19cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19d4, 0x19d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19dc, 0x19dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19e4, 0x19e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19f0, 0x19f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19f8, 0x19f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19fc, 0x19fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a00, 0x1a00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a04, 0x1a04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_apUnk1a24, 0x1a24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a28, 0x1a28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a2c, 0x1a2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_apUnk1a30, 0x1a30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a34, 0x1a34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a38, 0x1a38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a3c, 0x1a3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a40, 0x1a40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a44, 0x1a44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a48, 0x1a48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a4c, 0x1a4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a50, 0x1a50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a54, 0x1a54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a58, 0x1a58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a5c, 0x1a5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a60, 0x1a60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a64, 0x1a64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a68, 0x1a68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a6c, 0x1a6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a70, 0x1a70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a74, 0x1a74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a78, 0x1a78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a7c, 0x1a7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a8c, 0x1a8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a90, 0x1a90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a94, 0x1a94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a98, 0x1a98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a9c, 0x1a9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1aa0, 0x1aa0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1aa4, 0x1aa4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ae0, 0x1ae0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ae4, 0x1ae4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b1c, 0x1b1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b20, 0x1b20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b24, 0x1b24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b28, 0x1b28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b50, 0x1b50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b54, 0x1b54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b58, 0x1b58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b5c, 0x1b5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b60, 0x1b60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b64, 0x1b64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b6c, 0x1b6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b70, 0x1b70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b74, 0x1b74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_apAbilities, 0x1bd0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c20, 0x1c20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c24, 0x1c24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c28, 0x1c28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c2c, 0x1c2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c30, 0x1c30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c34, 0x1c34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c38, 0x1c38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c3c, 0x1c3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c40, 0x1c40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c44, 0x1c44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c48, 0x1c48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c4c, 0x1c4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c50, 0x1c50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c54, 0x1c54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c58, 0x1c58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c5c, 0x1c5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c60, 0x1c60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c64, 0x1c64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c68, 0x1c68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c6c, 0x1c6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c70, 0x1c70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c74, 0x1c74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c78, 0x1c78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c7c, 0x1c7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c80, 0x1c80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c84, 0x1c84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c88, 0x1c88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c8c, 0x1c8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c90, 0x1c90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c94, 0x1c94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c98, 0x1c98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1c9c, 0x1c9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ca0, 0x1ca0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ca4, 0x1ca4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ca8, 0x1ca8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cac, 0x1cac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cb0, 0x1cb0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cb4, 0x1cb4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cb8, 0x1cb8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cbc, 0x1cbc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ccc, 0x1ccc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cd0, 0x1cd0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cd4, 0x1cd4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cd8, 0x1cd8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cdc, 0x1cdc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ce0, 0x1ce0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ce4, 0x1ce4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ce8, 0x1ce8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cec, 0x1cec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cf0, 0x1cf0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cf8, 0x1cf8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d00, 0x1d00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pFlightAimCone, 0x1d38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dbc, 0x1dbc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dc4, 0x1dc4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dc8, 0x1dc8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dd4, 0x1dd4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dd8, 0x1dd8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ddc, 0x1ddc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1de0, 0x1de0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1de4, 0x1de4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1de8, 0x1de8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dec, 0x1dec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1df0, 0x1df0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1378, 0x1378);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkec8, 0xec8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkefc, 0xefc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkef4, 0xef4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf10, 0xf10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf00, 0xf00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkef8, 0xef8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf24, 0xf24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf08, 0xf08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf14, 0xf14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf0c, 0xf0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf38, 0xf38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf1c, 0xf1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf28, 0xf28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf20, 0xf20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf4c, 0xf4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf30, 0xf30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf3c, 0xf3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf34, 0xf34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf60, 0xf60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf44, 0xf44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf74, 0xf74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf50, 0xf50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf48, 0xf48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf58, 0xf58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf64, 0xf64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf5c, 0xf5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf6c, 0xf6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf78, 0xf78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf70, 0xf70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf88, 0xf88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf80, 0xf80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf8c, 0xf8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf84, 0xf84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf9c, 0xf9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfb0, 0xfb0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf94, 0xf94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfa0, 0xfa0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf98, 0xf98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfb4, 0xfb4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfa8, 0xfa8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfac, 0xfac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfd0, 0xfd0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfd4, 0xfd4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfd8, 0xfd8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfdc, 0xfdc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfe0, 0xfe0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfe4, 0xfe4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfe8, 0xfe8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkff0, 0xff0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkff4, 0xff4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkff8, 0xff8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkffc, 0xffc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1000, 0x1000);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1004, 0x1004);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1008, 0x1008);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1010, 0x1010);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1014, 0x1014);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1018, 0x1018);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk101c, 0x101c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1020, 0x1020);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1024, 0x1024);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1028, 0x1028);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1030, 0x1030);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1034, 0x1034);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1038, 0x1038);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk103c, 0x103c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1044, 0x1044);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1040, 0x1040);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1048, 0x1048);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1050, 0x1050);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1054, 0x1054);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1058, 0x1058);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk105c, 0x105c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1064, 0x1064);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1060, 0x1060);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1068, 0x1068);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1124, 0x1124);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk112c, 0x112c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1128, 0x1128);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk113c, 0x113c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1130, 0x1130);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1138, 0x1138);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1134, 0x1134);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1148, 0x1148);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1144, 0x1144);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1140, 0x1140);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk183c, 0x183c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1844, 0x1844);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk184c, 0x184c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1854, 0x1854);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk185c, 0x185c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1864, 0x1864);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk186c, 0x186c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1874, 0x1874);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1884, 0x1884);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk188c, 0x188c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1894, 0x1894);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1840, 0x1840);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1848, 0x1848);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1850, 0x1850);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18a4, 0x18a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk189c, 0x189c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18ac, 0x18ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18b4, 0x18b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18bc, 0x18bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18c4, 0x18c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk187c, 0x187c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1858, 0x1858);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1860, 0x1860);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1868, 0x1868);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1870, 0x1870);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1878, 0x1878);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1888, 0x1888);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1890, 0x1890);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1898, 0x1898);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18a0, 0x18a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18a8, 0x18a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18b0, 0x18b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18b8, 0x18b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18c0, 0x18c0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18c8, 0x18c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1880, 0x1880);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18cc, 0x18cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18d4, 0x18d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18dc, 0x18dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18e4, 0x18e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18ec, 0x18ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18f4, 0x18f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18fc, 0x18fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1904, 0x1904);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk190c, 0x190c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1914, 0x1914);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk191c, 0x191c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1924, 0x1924);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk192c, 0x192c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1934, 0x1934);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk193c, 0x193c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1944, 0x1944);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18d8, 0x18d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18e0, 0x18e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18e8, 0x18e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18f0, 0x18f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk18f8, 0x18f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1900, 0x1900);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk194c, 0x194c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1954, 0x1954);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1908, 0x1908);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1910, 0x1910);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1918, 0x1918);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1920, 0x1920);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1928, 0x1928);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1930, 0x1930);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1938, 0x1938);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1940, 0x1940);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1948, 0x1948);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1950, 0x1950);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1958, 0x1958);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk195c, 0x195c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1994, 0x1994);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19a0, 0x19a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1964, 0x1964);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk196c, 0x196c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1974, 0x1974);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk197c, 0x197c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1984, 0x1984);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk198c, 0x198c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk199c, 0x199c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1968, 0x1968);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1970, 0x1970);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1978, 0x1978);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1980, 0x1980);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1988, 0x1988);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1990, 0x1990);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1998, 0x1998);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19a4, 0x19a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unked8, 0xed8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkec4, 0xec4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkecc, 0xecc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_ui32StatusFlagsED0, 0xed0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_ui32StatusFlagsED4, 0xed4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pCurrentComboNode, 0x1a88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk894, 0x894);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk890, 0x890);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a20, 0x1a20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a1c, 0x1a1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a18, 0x1a18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf04, 0xf04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf18, 0xf18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf2c, 0xf2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf40, 0xf40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf54, 0xf54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf68, 0xf68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_aButtonRecords, 0xef0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfa4, 0xfa4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf7c, 0xf7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkf90, 0xf90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk848, 0x848);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk84c, 0x84c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk850, 0x850);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk854, 0x854);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk858, 0x858);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk85c, 0x85c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk860, 0x860);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk864, 0x864);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk868, 0x868);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk86c, 0x86c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk870, 0x870);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk874, 0x874);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk878, 0x878);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk87c, 0x87c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk880, 0x880);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk884, 0x884);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk888, 0x888);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkeec, 0xeec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk118d, 0x118d);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk118e, 0x118e);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1194, 0x1194);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1195, 0x1195);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1198, 0x1198);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11a8, 0x11a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11ac, 0x11ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11b0, 0x11b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11b4, 0x11b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11b8, 0x11b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11bc, 0x11bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11c0, 0x11c0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11c4, 0x11c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11c8, 0x11c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11cc, 0x11cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11d0, 0x11d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11d4, 0x11d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11d8, 0x11d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11dc, 0x11dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11e0, 0x11e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11e4, 0x11e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11e8, 0x11e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11ec, 0x11ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11f0, 0x11f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11f4, 0x11f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk11f8, 0x11f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1228, 0x1228);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1248, 0x1248);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk124c, 0x124c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1250, 0x1250);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1258, 0x1258);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1268, 0x1268);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk126c, 0x126c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1270, 0x1270);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1274, 0x1274);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1278, 0x1278);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk127c, 0x127c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1280, 0x1280);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1284, 0x1284);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1288, 0x1288);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk128c, 0x128c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1290, 0x1290);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12a0, 0x12a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12a4, 0x12a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12a8, 0x12a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12d8, 0x12d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12dc, 0x12dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12e0, 0x12e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12e4, 0x12e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12e8, 0x12e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12ec, 0x12ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12f4, 0x12f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk12f8, 0x12f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1304, 0x1304);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1305, 0x1305);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1308, 0x1308);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk135c, 0x135c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1360, 0x1360);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1364, 0x1364);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1368, 0x1368);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk136c, 0x136c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1370, 0x1370);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk137c, 0x137c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1380, 0x1380);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1398, 0x1398);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk139c, 0x139c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13a0, 0x13a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13cc, 0x13cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13cd, 0x13cd);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13ce, 0x13ce);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13d0, 0x13d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13d3, 0x13d3);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13d8, 0x13d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13d9, 0x13d9);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13dc, 0x13dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13e0, 0x13e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13e4, 0x13e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13e8, 0x13e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13ec, 0x13ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13f0, 0x13f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13f4, 0x13f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13f8, 0x13f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk13fc, 0x13fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1400, 0x1400);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1404, 0x1404);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1408, 0x1408);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk140c, 0x140c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1410, 0x1410);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1414, 0x1414);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1418, 0x1418);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk141c, 0x141c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1420, 0x1420);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1424, 0x1424);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1428, 0x1428);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk142c, 0x142c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1430, 0x1430);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1434, 0x1434);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1438, 0x1438);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk143c, 0x143c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1440, 0x1440);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1444, 0x1444);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1448, 0x1448);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_fFlightHeight, 0x1458);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk145c, 0x145c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1460, 0x1460);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1464, 0x1464);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1468, 0x1468);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk146c, 0x146c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1470, 0x1470);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1474, 0x1474);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1478, 0x1478);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1504, 0x1504);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1507, 0x1507);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1518, 0x1518);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1530, 0x1530);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1534, 0x1534);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1538, 0x1538);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1539, 0x1539);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk153c, 0x153c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk154c, 0x154c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1550, 0x1550);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1554, 0x1554);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1558, 0x1558);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk155c, 0x155c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1560, 0x1560);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1564, 0x1564);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1568, 0x1568);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk156c, 0x156c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1570, 0x1570);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1574, 0x1574);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1578, 0x1578);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk157c, 0x157c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1580, 0x1580);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1584, 0x1584);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1588, 0x1588);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk158c, 0x158c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1590, 0x1590);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1594, 0x1594);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1598, 0x1598);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk159c, 0x159c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15a0, 0x15a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15a4, 0x15a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15a8, 0x15a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15ac, 0x15ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15b0, 0x15b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15b4, 0x15b4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15b8, 0x15b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15bc, 0x15bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15c0, 0x15c0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15c4, 0x15c4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15c8, 0x15c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15cc, 0x15cc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15cd, 0x15cd);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15ce, 0x15ce);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15cf, 0x15cf);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15d0, 0x15d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15d1, 0x15d1);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15d2, 0x15d2);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15d4, 0x15d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15d8, 0x15d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15dc, 0x15dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15e0, 0x15e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15e4, 0x15e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15e8, 0x15e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15ec, 0x15ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15f0, 0x15f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15f4, 0x15f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15f8, 0x15f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk15fc, 0x15fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1600, 0x1600);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1604, 0x1604);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1608, 0x1608);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk160c, 0x160c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1610, 0x1610);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1614, 0x1614);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1615, 0x1615);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk161c, 0x161c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk161f, 0x161f);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1626, 0x1626);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1627, 0x1627);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1628, 0x1628);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1629, 0x1629);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1630, 0x1630);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1634, 0x1634);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk164c, 0x164c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1650, 0x1650);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1654, 0x1654);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1658, 0x1658);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk165c, 0x165c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1660, 0x1660);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1665, 0x1665);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1668, 0x1668);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk166c, 0x166c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1670, 0x1670);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_bExternalDisplacementActive, 0x1674);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1675, 0x1675);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1676, 0x1676);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1677, 0x1677);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1678, 0x1678);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1679, 0x1679);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk167a, 0x167a);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk167b, 0x167b);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk167c, 0x167c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk167d, 0x167d);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk168c, 0x168c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk168d, 0x168d);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk168e, 0x168e);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pHeldClimbZone, 0x1690);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pCurrentClimbZone, 0x1694);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1698, 0x1698);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk169c, 0x169c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16a0, 0x16a0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16a4, 0x16a4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16a8, 0x16a8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16ac, 0x16ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16d4, 0x16d4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1620, 0x1620);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1625, 0x1625);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk162c, 0x162c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1638, 0x1638);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk163c, 0x163c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1640, 0x1640);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk167e, 0x167e);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1680, 0x1680);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1684, 0x1684);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1688, 0x1688);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16b0, 0x16b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16bc, 0x16bc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16c8, 0x16c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16d0, 0x16d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1700, 0x1700);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk170c, 0x170c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16d8, 0x16d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16dc, 0x16dc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16e0, 0x16e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16e4, 0x16e4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16e8, 0x16e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16ec, 0x16ec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16f0, 0x16f0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16f4, 0x16f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16f8, 0x16f8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16f9, 0x16f9);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk16fc, 0x16fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1724, 0x1724);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1728, 0x1728);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk172c, 0x172c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1730, 0x1730);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1734, 0x1734);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1738, 0x1738);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk173c, 0x173c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1740, 0x1740);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1748, 0x1748);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk174c, 0x174c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1750, 0x1750);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1754, 0x1754);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1758, 0x1758);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk175c, 0x175c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1760, 0x1760);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1764, 0x1764);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1768, 0x1768);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk176c, 0x176c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1770, 0x1770);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1774, 0x1774);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk178c, 0x178c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk17fc, 0x17fc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1800, 0x1800);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1804, 0x1804);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_ui8MovementMode, 0x1808);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_bTakeOffPending, 0x1809);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk180c, 0x180c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1810, 0x1810);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1811, 0x1811);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1812, 0x1812);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1813, 0x1813);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1814, 0x1814);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1815, 0x1815);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk181c, 0x181c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1820, 0x1820);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1824, 0x1824);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk182c, 0x182c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1838, 0x1838);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1839, 0x1839);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19ac, 0x19ac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19b0, 0x19b0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19b8, 0x19b8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19c0, 0x19c0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19c8, 0x19c8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19d0, 0x19d0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19d8, 0x19d8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19e0, 0x19e0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19e8, 0x19e8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk19f4, 0x19f4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a08, 0x1a08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a0c, 0x1a0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a10, 0x1a10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a14, 0x1a14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1a84, 0x1a84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ab2, 0x1ab2);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ab4, 0x1ab4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ab5, 0x1ab5);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ab6, 0x1ab6);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ab8, 0x1ab8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1abc, 0x1abc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1abd, 0x1abd);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1abe, 0x1abe);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1abf, 0x1abf);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac0, 0x1ac0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac1, 0x1ac1);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac2, 0x1ac2);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac3, 0x1ac3);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac4, 0x1ac4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac5, 0x1ac5);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac6, 0x1ac6);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac7, 0x1ac7);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac8, 0x1ac8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ac9, 0x1ac9);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1aca, 0x1aca);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1acb, 0x1acb);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1acc, 0x1acc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1acd, 0x1acd);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ace, 0x1ace);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1acf, 0x1acf);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ad0, 0x1ad0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ad1, 0x1ad1);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ad2, 0x1ad2);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ad3, 0x1ad3);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ad4, 0x1ad4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ad8, 0x1ad8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1adc, 0x1adc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1ae8, 0x1ae8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1aec, 0x1aec);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1af8, 0x1af8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b08, 0x1b08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b0c, 0x1b0c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b10, 0x1b10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b14, 0x1b14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b18, 0x1b18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b30, 0x1b30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b34, 0x1b34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b38, 0x1b38);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b3c, 0x1b3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b40, 0x1b40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b44, 0x1b44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b48, 0x1b48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b4c, 0x1b4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b68, 0x1b68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b78, 0x1b78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b7c, 0x1b7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b80, 0x1b80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b84, 0x1b84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b88, 0x1b88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b8c, 0x1b8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b90, 0x1b90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b94, 0x1b94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b98, 0x1b98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_ui32ActiveHitSphereCount, 0x1bac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bb0, 0x1bb0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bb4, 0x1bb4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bb8, 0x1bb8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bbc, 0x1bbc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bc0, 0x1bc0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bc4, 0x1bc4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bc8, 0x1bc8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1bcc, 0x1bcc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_afAbilityCooldown, 0x1bf8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pActiveAbility, 0x1cc0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cc4, 0x1cc4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cc8, 0x1cc8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cf4, 0x1cf4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1cfc, 0x1cfc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d04, 0x1d04);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d08, 0x1d08);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d10, 0x1d10);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d11, 0x1d11);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d14, 0x1d14);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d18, 0x1d18);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d1c, 0x1d1c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_fAbilityAnimSpeedScale, 0x1d20);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_fAbilityFuryTimer, 0x1d24);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pFlightAimEnemy, 0x1d28);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d2c, 0x1d2c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d30, 0x1d30);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d34, 0x1d34);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d3c, 0x1d3c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d40, 0x1d40);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d44, 0x1d44);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d48, 0x1d48);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d4c, 0x1d4c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d50, 0x1d50);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d54, 0x1d54);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d58, 0x1d58);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d5c, 0x1d5c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d60, 0x1d60);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d64, 0x1d64);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d68, 0x1d68);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d6c, 0x1d6c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d70, 0x1d70);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d74, 0x1d74);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d78, 0x1d78);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d7c, 0x1d7c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d80, 0x1d80);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d84, 0x1d84);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d88, 0x1d88);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d8c, 0x1d8c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d90, 0x1d90);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d94, 0x1d94);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d98, 0x1d98);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1d9c, 0x1d9c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1da0, 0x1da0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1da4, 0x1da4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1da8, 0x1da8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dac, 0x1dac);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1db0, 0x1db0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1db4, 0x1db4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1db8, 0x1db8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dc0, 0x1dc0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dcc, 0x1dcc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dd0, 0x1dd0);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1dd1, 0x1dd1);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1df4, 0x1df4);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_pAbilityHost, 0x1df8);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unkfed, 0xfed);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk100d, 0x100d);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk102d, 0x102d);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk104d, 0x104d);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk106d, 0x106d);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk115c, 0x115c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1160, 0x1160);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1348, 0x1348);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk134c, 0x134c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1350, 0x1350);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1354, 0x1354);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1618, 0x1618);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1778, 0x1778);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk177c, 0x177c);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1780, 0x1780);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1784, 0x1784);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1788, 0x1788);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1afc, 0x1afc);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b00, 0x1b00);
DOTD_ASSERT_OFFSET(CKHkS08Hero, m_unk1b04, 0x1b04);

// Free helpers of the hero units (CKHkS08Hero_2.cpp, CKHkS08Hero_15.cpp).
// 0x002f8520 Angle_StepTowardInDirection_maybe
float Angle_StepTowardInDirection(float current, float target, float speed, float dt, uint32_t backwards);
// 0x002fa6a8 GroundProbe_ComputeRadialAverageNormal_maybe: the normalised sum of the ground normals under `count` points
// around `center` (the zero vector when none counts).
CVector3 GroundProbe_ComputeRadialAverageNormal(const CVector3* center, const CVector3* direction, float radius, float lift,
                                                float maxDrop, int32_t count);
// 0x002fbd78 Vec3_TiltUpVectorAroundLocalX_maybe (normalises `up` and `at` in place)
CVector3 Vec3_TiltUpVectorAroundLocalX(float angle, CVector3* up, CVector3* at);
// A carried object's weight (its vt+0x104: the transportable key, weight and power bucket; CKHkS08Hero.cpp).
float CarriedObjectWeight(IKSerializable* object);
// 0x002fbbf8 Vec3_AngleBetween (CKHkS08Hero_2.cpp): the angle in radians between `a` and `b` (both normalised in place).
float Vec3_AngleBetween(CVector3* a, CVector3* b);
// 0x00333618 Math_RemapClamped
float Math_RemapClamped(float from0, float from1, float value, float to0, float to1);
