// CKCameraClassicTrack2.h - the follow camera with stick control and the co-op framing (key 0x307, vtable 0xb1a618,
// size 0x130). Original unit: CKCameraClassicTrack2.cpp (0x146de8-0x14f888). XXL2 has the class
// (K/KServices/KServiceCamera/KCameraClassicTrack2, size 0xe0): its members +0x40.. are DotD's +0x58.. (IKCamera is
// 0x18 bytes longer here), in the same load order; DotD loads six target offsets / camera offsets where XXL2 has four,
// and more parameters after them. Member names are XXL2's where the code matches them, else ours. No level file holds
// the class (nothing replays it); C2.8 port-last Z1 ported it from the disassembly.
//
// How it works: one state (m_sapUpdateFunc[1] = StateFollow, a TStateEngine at +0xe0). The camera stays behind the
// focus (the camera service's +0x484, moved toward the second hero in co-op by ApplyCoopTargetOffset) at the current
// camera offset (m_v2CurrentCameraOffset: x the distance, y the height) along the matrix's at axis, the target at the
// current target offset height. The right stick turns the matrix about the target (x) and moves between the near
// (position 0) and far (position 1) offsets (y; AdaptTargetAndCameraCurrentOffset); a wanted position (+0x124, XXL2
// E_CT2_CAMERA_POSITION_WANTED) moves there over time; after an idle time the camera comes back to the normal offset
// (position 2) or follows the focus's move (UpdateAutoRecenter). The target leads sideways with the focused hero's move
// (m_fCurrentTargetOffsetLR, ComputeFollowPose). Co-op (two stacked targets): the offsets blend toward the co-op ones
// (index 4 / 5) with the heroes' distance (m_fCoopBlend).
#pragma once
#include <cstdint>

#include "k2000/cameras/IKCamera.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/CVector2.h"

class IKFile;

class CKCameraClassicTrack2 : public IKCamera {
public:
    // vt+0x14 / +0x18 0x9a7928 / 0x9a7930: category 7 (camera), id 0xc.
    DOTD_CLASS_KEY(kCategoryCamera, 0xc)
    // vt+0x08 0x009a7900 CKCameraClassicTrack2_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x307 || key == 0x347 || key == 0xc; }
    // 0x00146de8 _Delete, 0x001474d8 _DeleteArray, 0x00147690 _CreateArray, 0x00147790 _Create.
    DOTD_DECLARE_FACTORIES(CKCameraClassicTrack2)

    // A state handler (XXL2 TStateEngine<float>::TStateFunc: the original's pointers to member functions): phase 1 on
    // enter (the previous state), 2 on leave (the next state), 0 every frame (returns the next state); `dt` points to
    // the frame time (0 for the switch in Start).
    typedef uint8_t (CKCameraClassicTrack2::*StateHandler)(float* dt, int32_t phase, uint8_t other);

    // 0x00147790 CKCameraClassicTrack2_Create (= the dead 0x147468 _Construct / 0x1475a8 _Construct_2): IKCamera's
    // constructor, no state (+0xe4 / +0xe5 = 0xff), the approach +0x118..+0x120 = 0, no matrix; the rest is the fresh
    // heap's zeroes.
    CKCameraClassicTrack2();
    // 0x00147660 _Destructor / 0x00147618 _DeletingDestructor (+ operator delete; the dead 0x147578 _BaseDestructor):
    // the vtable, IKCamera's destructor.
    ~CKCameraClassicTrack2() override {}

    // vt+0x10 0x00147420 CKCameraClassicTrack2_Destroy: IKCamera's (CKCameraTrack_ClearReferences_BaseNop_maybe), then
    // the matrix destroyed (RwMatrixDestroy_Thunk) and cleared.
    void Destroy() override;
    // vt+0x24 0x001473f8 _RecursiveRegistration: IKCamera's (0x144108), then 1.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x28 0x148078 _Save: not ported (the saves are out of scope).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00147a38 CKCameraClassicTrack2_Load
    // vt+0x30 0x00147378 _PostLoad: IKCamera's (KStub_Return1_144570); type 0: the matrix created, the state table
    // (m_sapUpdateFunc, TOC -0x3ba0), no state, one state; 1.
    int32_t PostLoad(int32_t type) override;

    void Start(const CVector3* startPosition) override;  // vt+0x50 0x0014f278 CKCameraClassicTrack2_Activate_maybe
    void Pause() override {}                              // vt+0x54 0x00146e38 CKCameraClassicTrack2_vf54 (empty)
    // vt+0x58 0x00147350 CKCameraClassicTrack2_Deactivate_maybe: the attached fx stopped.
    void Stop() override { StopAttachedFx(); }
    void Resume() override {}                             // vt+0x5c 0x00146e40 CKCameraClassicTrack2_vf5C (empty)
    void Update(float frameTime) override;                // vt+0x60 0x00147818 CKCameraClassicTrack2_Update
    // vt+0x80 0x009a7938 CKCameraClassicTrack2_vf80 [inline]: +0xbc (XXL2 GetAboveGroundHeight).
    float Vf80() const override { return m_fHeightAboveGround; }
    // vt+0x74 0x0014a018 CKCameraClassicTrack2_vf74 (XXL2 FindAndRepairOcclusion): the position kept clear of the walls
    // and grounds between the focus and the camera (IKCamera's 0x145088 with the track's changes).
    void ResolveViewObstructions(float dt, const CVector3* focus, CVector3* position) override;
    // vt+0x78 0x0014c4f8 CKCameraClassicTrack2_ResolveCameraCollision_maybe (XXL2 FindGroundContact): the position
    // kept out of the grounds (IKCamera's 0x1461a0 with the track's radius, focus and target plane).
    void ResolveCameraCollision(const CVector3* target, CVector3* position) override;
    uint8_t VfB0() const override { return 1; }  // vt+0xb0 0x009a7940 [inline]
    uint8_t VfB4() const override { return 1; }  // vt+0xb4 0x009a7948 [inline]

    // 0x0014c440 CKCameraClassicTrack2_StateFollow_maybe (the only state): enter: ComputeFollowPose (dt 1000) on the
    // matrix and the target; every frame: UpdateFollow, state 0.
    uint8_t StateFollow(float* dt, int32_t phase, uint8_t other);
    // 0x0014be30 CKCameraClassicTrack2_UpdateFollow_maybe (XXL2 ExploreUpdate): the follow step.
    void UpdateFollow(float dt);
    // 0x00148958 CKCameraClassicTrack2_ComputeFollowPose_maybe (XXL2 ModifyTargetPositionWithCurrentTargetOffsetLR):
    // m_fCurrentTargetOffsetLR toward the focused hero's sideways move (or 0) at m_fTargetOffsetLRSpeed a second, then
    // `target` moved along the matrix's right axis by twice it times the half width at the camera-target distance.
    void ComputeFollowPose(float dt, CMatrix34* m, CVector3* target);
    // 0x00148f50 CKCameraClassicTrack2_UpdateAxisController_maybe (XXL2 AdaptTargetAndCameraCurrentOffset, DotD adds
    // dt): the current offsets moved toward those of `position` (0 near, 1 far, 2 normal, 3 normal keeping the height),
    // the ones `flags` selects (1 target y, 2 camera x, 4 camera y), the largest by |step| and the others in proportion;
    // then the height kept over the focus' ground reference near the focus; 1 when that raised it.
    uint8_t AdaptTargetAndCameraCurrentOffset(float dt, int32_t position, float step, uint32_t flags);
    // 0x00149470 CKCameraClassicTrack2_ApplyStickRotation_maybe (XXL2 ExploreComputeOffsetsAndRotationFromInputs): the
    // right stick (camera service flag 0x200000, not 4): x turns `m` about the target (m_fCurrentRotationSpeed), y moves
    // the offsets (m_fCurrentOffsetSpeed). Result bits: 1 turned, 2 the stick y moved, 4 toward far, 8 toward near.
    uint32_t ApplyStickRotation(float dt, CMatrix34* m);
    // 0x00149a00 CKCameraClassicTrack2_UpdateModeSpeedAndAxis_maybe: the move to the wanted position (+0x124) for
    // m_fTimeToGoToWantedPosition seconds; 1 while there is one.
    uint8_t UpdateWantedPosition(float dt);
    // 0x00149c30 CKCameraClassicTrack2_ApplyCoopTargetOffset_maybe: `point` moved half way toward the second stacked
    // target (+0xd5c), its part along the matrix's flat at axis limited to m_fCoopMaxOffset.
    void ApplyCoopTargetOffset(CVector3* point);
    // 0x0014b3f8 CKCameraClassicTrack2_PlaceBehindTarget_maybe (XXL2 ComputeCameraFromOffsets): `m`'s position at the
    // current offsets behind the focus along its flat at axis, then turned to `target`.
    void PlaceBehindTarget(const CVector3* target, CMatrix34* m);
    // 0x0014b670 CKCameraClassicTrack2_UpdateAutoRecenter_maybe (XXL2 ExploreComputeOffsetsFromTargetedPositionMove):
    // the offsets follow the focus's move along the view, or come back to the normal one after +0xc4 seconds.
    uint8_t UpdateAutoRecenter(float dt, CMatrix34* m);
    // 0x0014bbd8 CKCameraClassicTrack2_InitDistanceAndHeight_maybe (XXL2 ForceCurrentOffsetsFromPosition): the current
    // offsets from the camera position `cameraPos` and the target `target` (clamped to the offsets' ranges).
    void ForceCurrentOffsetsFromPosition(const CVector3* target, const CVector3* cameraPos);
    // 0x0014f030 CKCameraClassicTrack2_ResolveWallCollision_maybe (with m_Flags 0x2000): the cylinder from `from` to
    // `position` slid along the walls; a slide that brings the camera nearer than 0.75 of the distance searches another
    // angle around the focus (SearchUnobstructedAngle).
    void ResolveWallCollision(const CVector3* from, CVector3* position);
    // 0x0014ddc8 CKCameraClassicTrack2_SearchUnobstructedAngle_maybe: the camera at the current distance behind the
    // focus turned by 0, +-45, +-90, 180 -+ 45 ... degrees until a position at least as far as 0.75 of the distance
    // (and 1.1 times `distanceSquare`) is free; 1 when a farther position than `distanceSquare` was found.
    uint8_t SearchUnobstructedAngle(float distanceSquare, const CVector3* from, CVector3* position);
    // 0x001470a8 CameraTrack_ClampPositionByCollision_maybe (non-member in the original, r3 the camera): the camera's
    // cylinder (wall sweep) or the line (grounds, 0.1 further) from `from` to `to`; the hit point goes to `out` when
    // its squared distance from `from` beats `best`; no hit: `to`, FLT_MAX. Returns the best squared distance.
    static float ClampPositionByCollision(IKCamera* camera, float best, const CVector3* from, const CVector3* to,
                                          CVector3* out);

    float m_fPlayerCtrl_UpDown_MaxSpeed;          // +0x58 the stick y's top offset speed (x |stick|)
    float m_fPlayerCtrl_UpDown_Acceleration;      // +0x5c
    float m_fPlayerCtrl_Rotation_MaxSpeed;        // +0x60 the stick x's top turn speed (degrees a second x |stick|)
    float m_fPlayerCtrl_Rotation_Acceleration;    // +0x64
    float m_afTargetOffsetY[6];                   // +0x68 per position (0 near, 1 far, 2 normal, 3, 4 / 5 the co-op near / far)
    CVector2 m_av2CameraOffset[6];                // +0x80 per position: x the distance, y the height
    float m_fTargetOffsetLR;                      // +0xb0 the sideways lead's gain (the hero's move ^4)
    float m_fTargetOffsetLRSpeed;                 // +0xb4
    float m_fCameraMaxSpeed;                      // +0xb8 the camera's vertical speed limit (UpdateFollow)
    float m_fHeightAboveGround;                   // +0xbc (Vf80)
    float m_fIdleTimeAfterPlayerInput;            // +0xc0 the idle time before UpdateAutoRecenter's follow (m_fCurrentIdleTimeLeft)
    float m_fRecenterDelay;                       // +0xc4 _maybe: the time before the comeback to the normal offset (+0x110, +0x114)
    float m_unkC8;                                // +0xc8 (loaded; not read by the ported code)
    float m_fCoopDistanceRange;                   // +0xcc the heroes' distance that gives the full co-op blend
    float m_fCoopMaxOffset;                       // +0xd0 ApplyCoopTargetOffset's limit
    float m_fCoopBlendDownSpeed;                  // +0xd4 m_fCoopBlend's speed down / up
    float m_fCoopBlendUpSpeed;                    // +0xd8
    CMatrix34* m_pMatrix;                         // +0xdc RwMatrixCreate at PostLoad: the camera's frame
    // XXL2 TStateEngine<float> m_UpdateStateEngine: the table, the state, the state count.
    const StateHandler* m_pStateTable;            // +0xe0
    uint8_t m_ui8State;                           // +0xe4 0xff: none
    uint8_t m_ui8NbStates;                        // +0xe5
    uint8_t m_padE6[2];
    float m_fCurrentRotationSpeed;                // +0xe8 the stick x's turn speed
    float m_fCurrentTargetOffsetY;                // +0xec the target's height over the focus
    CVector2 m_v2CurrentCameraOffset;             // +0xf0 x the distance, y the height
    float m_fCurrentOffsetSpeed;                  // +0xf8 the stick y's / wanted position's offset speed
    float m_fCurrentTargetOffsetLR;               // +0xfc the target's sideways lead
    CVector3 m_v3PreviousTargetedPositionRefForTarget;  // +0x100 the focus of the last frame
    float m_fCurrentIdleTimeLeft;                 // +0x10c
    float m_fRecenterTimer;                       // +0x110 _maybe: the comeback's countdown (FLT_MAX: off)
    float m_fTargetOffsetLRHold;                  // +0x114 _maybe: the sideways lead's hold time (ComputeFollowPose)
    float m_afRecenterApproach[3];                // +0x118 FloatApproach {target, speed, current}: the comeback's speed
    int32_t m_eCurrentWantedPosition;             // +0x124 XXL2 E_CT2_CAMERA_POSITION_WANTED (0 none, 1 near, 2 far, 3 normal)
    float m_fTimeToGoToWantedPosition;            // +0x128
    float m_fCoopBlend;                           // +0x12c 0..1 toward the co-op offsets
};
DOTD_ASSERT_SIZE(CKCameraClassicTrack2, 0x130);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_fPlayerCtrl_UpDown_MaxSpeed, 0x58);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_afTargetOffsetY, 0x68);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_av2CameraOffset, 0x80);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_fTargetOffsetLR, 0xb0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_fHeightAboveGround, 0xbc);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_fCoopBlendUpSpeed, 0xd8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_pMatrix, 0xdc);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_pStateTable, 0xe0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_ui8State, 0xe4);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_ui8NbStates, 0xe5);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_fCurrentRotationSpeed, 0xe8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_v2CurrentCameraOffset, 0xf0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_v3PreviousTargetedPositionRefForTarget, 0x100);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_fCurrentIdleTimeLeft, 0x10c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_afRecenterApproach, 0x118);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_eCurrentWantedPosition, 0x124);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack2, m_fCoopBlend, 0x12c);
