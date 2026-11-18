// CKCameraClassicTrack3.h - the third-person follow camera (key 0x387, vtable 0xb1aa50, size 0x318). Original unit: CKCameraClassicTrack3.cpp.
// Not in XXL2. The Load reads 35 swapped words, +0x5c..+0xe4, in a scrambled order (see the Load).
//
// How it works (step 5): the focus point is the weighted mean of the camera service's focus targets (the heroes,
// CKSrvCamera +0xd0c) plus the active constraint zone's offsets; the camera orbits it at m_distance along -m_viewDir.
// A change of constraint zone starts a blend (m_blendStart -> m_blendEnd over m_blendDuration seconds); otherwise
// UpdateSteady follows the focus with a damped spring (IntegrateFollowOffset11C/120), turns with the right stick
// (ApplyStickYaw) and keeps the targets in the view frustum (UpdateFramingAndPlaceCamera). The collision / constraint
// helpers (ResolveWallMovement .. ConstrainOrbitAnglesToVolume) are the COLL family's (step 5).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/services/CollisionDatas.h"

class IKFile;
class CKCameraConstraint;

class CKCameraClassicTrack3 : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0xe)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a7cb0
        return key == 0x387 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraClassicTrack3)

    // The state of Math_ApproachWithAccelDecel / Math_ApproachAngleWithAccelDecel (k2000/misc/FloatApproach.h; 7 floats):
    // m_current approaches m_target at m_speed, accelerating by m_accel and braking by m_decel up to m_maxSpeed (+ m_speedBonus).
    struct SAccelDecelApproach {
        float m_accel;       // +0x00
        float m_decel;       // +0x04
        float m_maxSpeed;    // +0x08
        float m_current;     // +0x0c
        float m_speed;       // +0x10
        float m_target;      // +0x14
        float m_speedBonus;  // +0x18
        float* Data() { return &m_accel; }
    };
    // An orbit pose of the blends: the distance, the pitch and yaw angles (radians) and the focus point.
    struct SOrbitPose {
        float m_distance;  // +0x00
        float m_pitch;     // +0x04 (the m_pitch.m_current convention: asin of the view direction's -y)
        float m_yaw;       // +0x08 (Vec3_GetYawAngleFromZ of the view direction)
        CVector3 m_focus;  // +0x0c
    };

    CKCameraClassicTrack3();  // 0x00158808 CKCameraClassicTrack3_Create (the same stores as CKCameraClassicTrack3_Construct 0x158500)
    ~CKCameraClassicTrack3() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00158880 CKCameraClassicTrack3_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00158460 CKCameraClassicTrack3_PostLoad

    // The camera slots (IKCamera.h).
    void Start(const CVector3* startPosition) override;  // vt+0x50 0x00163dc0 CKCameraClassicTrack3_Activate_maybe
    void Pause() override {}                              // vt+0x54 0x00157b48 CKCameraClassicTrack3_Pause (empty)
    void Stop() override;                                 // vt+0x58 0x00158428 CKCameraClassicTrack3_Deactivate_maybe
    void Resume() override {}                             // vt+0x5c 0x00157b50 CKCameraClassicTrack3_Resume (empty)
    void Update(float frameTime) override;                // vt+0x60 0x001653c0 CKCameraClassicTrack3_Update_maybe
    void SetFov(float value) override { m_requestedFov = value; }  // vt+0x68 0x9a7d08 CKCameraClassicTrack3_SetFov: +0x2c8
    void ResetTrack() override {}                         // vt+0x6c 0x9a7d00 CKCameraClassicTrack3_vf6C (empty)
    float Vf80() const override { return m_param5c; }     // vt+0x80 0x9a7d10 CKCameraClassicTrack3_vf80: +0x5c
    float Vf84() const override { return m_unk44Approach.m_current; }  // vt+0x84 0x9a7ce8 CKCameraClassicTrack3_vf84: +0x2f4
    float Vf8C() const override { return m_unk304; }      // vt+0x8c 0x9a7cf0 CKCameraClassicTrack3_vf8C: +0x304
    float Vf90() const override { return m_unk308; }      // vt+0x90 0x9a7cf8 CKCameraClassicTrack3_vf90: +0x308
    // vt+0x94 0x9a7d18 CKCameraClassicTrack3_vf94: !(m_trackFlags bit 18) (the blend that CaptureBlendStart skipped).
    uint8_t Vf94() const override { return static_cast<uint8_t>(((m_trackFlags ^ 0x40000u) >> 18) & 1u); }
    uint8_t VfB0() const override { return 1; }           // vt+0xb0 0x9a7d28 CKCameraClassicTrack3_vfB0
    uint8_t VfB4() const override { return 1; }           // vt+0xb4 0x9a7d30 CKCameraClassicTrack3_vfB4

    // The track's own functions (CT3 family, step 5).
    void ResetState();                                                      // 0x001579f0 CKCameraClassicTrack3_ResetState_maybe
    void ComputeFocusPoint(CVector3* focus);                                // 0x001592e0 CKCameraClassicTrack3_ComputeFocusPoint_maybe
    void BuildFrustumPlanes(const CVector3* position);                      // 0x00159950 CKCameraClassicTrack3_BuildFrustumPlanes_maybe
    uint8_t UpdateFramingAndPlaceCamera(float dt, CVector3* position);      // 0x00159ec0 CKCameraClassicTrack3_UpdateFramingAndPlaceCamera_maybe
    void IntegrateFollowOffset120(float dt, CVector3* focus, CVector3* delta);  // 0x0015a690 CKCameraClassicTrack3_IntegrateSplitFollowSpring_maybe
    void IntegrateFollowOffset11C(float dt, CVector3* focus, CVector3* delta);  // 0x0015aa10 CKCameraClassicTrack3_IntegrateFollowSpring_maybe
    void UpdateFollowOffsets(float dt, CVector3* focus);                    // 0x0015acf0 CKCameraClassicTrack3_UpdateFollowOffsets_maybe
    void ApplyStickYaw(float dt, CVector3* position);                       // 0x0015ce68 CKCameraClassicTrack3_ApplyRightStick_maybe
    // 0x0015ddc0 CKCameraClassicTrack3_ComputeDesiredPose_maybe: m_blendEnd from the focus and the constraint zone;
    // r4 is the caller's position buffer, the flag the constraint's +0x20 bit 5.
    void ComputeDesiredPose(CVector3* position, const CVector3* focus, uint32_t keepYaw);
    // 0x0015f520 CKCameraClassicTrack3_CaptureBlendStart_maybe (f1 = the blend time scale; r4 = the position, r5 = the target).
    void CaptureBlendStart(float timeScale, CVector3* position, CVector3* target);
    void UpdateSteady(float dt);                                            // 0x001615c8 CKCameraClassicTrack3_UpdateSteady_maybe
    void UpdateBlending(float dt);                                          // 0x00164448 CKCameraClassicTrack3_UpdateBlending_maybe
    // The snap behind the target the original inlines in ComputeFocusPoint, UpdateFramingAndPlaceCamera and UpdateSteady.
    void SnapBehindTarget();
    // The framing push of one focus target against the frustum planes 5..2 and 0 (UpdateFramingAndPlaceCamera and
    // ComputeDesiredPose inline it): the largest distance the camera must move back for the sphere to be inside.
    float FramingPush(float x, float y, float z, float radius) const;
    // m_right = y x m_viewDir, normalised (inlined in Start, ComputeDesiredPose, UpdateSteady, UpdateBlending).
    void UpdateRightVector();
    // The orbit position at (yaw, pitch, distance) from `focus` (inlined in ComputeDesiredPose and UpdateBlending):
    // focus - (cos p sin y, -sin p, cos p cos y) * distance, with the original's operation order.
    static void OrbitPosition(const CVector3* focus, float yaw, float pitch, float distance, CVector3* out);
    // 0x009a7d38 CKCameraConstraint_ComputeLookDirection_maybe (an out-of-line inline of the unit): the constraint
    // zone's look direction for the point (the zone's mode byte +0x38: 2 = towards its +0x3c object, ...). Returned by value.
    // Mode 3 with the zone flag 0x40000 moves the zone's +0x74 (hence not const).
    static CVector3 ComputeLookDirection(CKCameraConstraint* constraint, const CVector3* point);

    // The collision / constraint helpers (COLL family, step 5: declared here, defined by COLL).
    // 0x00157e50 CKCameraClassicTrack3_ResolveWallMovement_maybe: the move from -> to against the walls.
    void ResolveWallMovement(const CVector3* from, CVector3* to);
    // 0x00159720 CKCameraClassicTrack3_ApplyPushSphereContact_maybe (r4 unused by the callers' convention).
    uint8_t PushOutOfConstraintPlane(float dt, CVector3* position);
    // 0x0015b000 CKCameraClassicTrack3_FindGroundContact_maybe = the override of IKCamera vt+0x78
    // (IKCamera_FindGroundContact_maybe 0x1461a0).
    void ResolveCameraCollision(const CVector3* target, CVector3* position) override;
    // 0x0015c0d8 CKCameraClassicTrack3_ConstrainOrbitAnglesToVolume_maybe (r4: the caller's position buffer, unused).
    void ConstrainOrbitAnglesToVolume(CVector3* position, const CVector3* focus, CKCameraConstraint* constraint);
    // 0x0015c800 CKCameraClassicTrack3_TestCameraObstruction_maybe: fills m_obstructionHit / m_wallHit for from -> to.
    void TestCameraObstruction(const CVector3* from, CVector3* to);
    // 0x0015fa00 CKCameraClassicTrack3_ConstrainFollowToVolume_maybe (r5 unused).
    void ConstrainFollowToVolume(float dt, CKCameraConstraint* constraint, CVector3* position);
    // 0x00162910 CKCameraClassicTrack3_FindAndRepairOcclusion_maybe = the override of IKCamera vt+0x74 (IKCamera_FindAndRepairOcclusion_maybe
    // 0x145088). focus: a copy of the first focus target's position (+0xd2c).
    void ResolveViewObstructions(float dt, const CVector3* focus, CVector3* position) override;

    uint32_t m_unk58;  // +0x58 not set by the constructor nor the Load
    // The loaded parameters (+0x5c..+0xe4; floats in the files). The names follow the code that reads them.
    float m_param5c;                 // +0x5c returned by Vf80
    float m_pitchAccel;              // +0x60 m_pitch.m_accel (ResetState; UpdateSteady when the stick does not hold the pitch)
    float m_pitchDecel;              // +0x64 m_pitch.m_decel (ResetState)
    float m_pullInAccel;             // +0x68 m_pullInSpeed += dt * this while farther than m_defaultDistance (UpdateSteady)
    float m_pullInMaxSpeed;          // +0x6c the cap of m_pullInSpeed
    float m_followStiffness;         // +0x70 the follow spring: speed += dt * (distance * this - m_followDamping * speed)
    float m_followDamping;           // +0x74
    float m_followAccelFixed;        // +0x78 the spring's acceleration while m_trackFlags bit 9 (0x200) is set
    float m_followDampingFixed;      // +0x7c the damping while bit 9 is set
    float m_followStiffnessUp;       // +0x80 the vertical spring's stiffness going up (camera service flag 0x4000000)
    float m_followDampingUp;         // +0x84 its damping (IntegrateFollowOffset120)
    float m_minDistance;             // +0x88 the near plane of the framing frustum and the shortest orbit distance
    float m_maxDistance;             // +0x8c
    float m_leadAtMinDistance;       // +0x90 _maybe: the focus is moved along the view direction by the lerp of these two
    float m_leadAtMaxDistance;       // +0x94 _maybe  (UpdateSteady)
    float m_defaultDistance;         // +0x98 the orbit distance at Start and after a reset
    float m_param9c;                 // +0x9c
    float m_yawStickAccel;           // +0xa0 the right stick's x: the yaw speed m_yawStickSpeed (ApplyStickYaw)
    float m_yawStickDecel;           // +0xa4
    float m_yawStickMaxSpeed;        // +0xa8
    float m_zoomStickAccel;          // +0xac the right stick's y: the distance speed m_zoomStickSpeed
    float m_zoomStickDecel;          // +0xb0
    float m_zoomStickMaxSpeed;       // +0xb4
    float m_stickPitchMin;           // +0xb8 the range of m_stickPitch
    float m_stickPitchMax;           // +0xbc
    float m_pitchStickMaxSpeed;      // +0xc0 the right stick's y: the pitch speed m_pitchStickSpeed
    float m_pitchStickAccel;         // +0xc4 (also m_pitch.m_accel while the stick holds the pitch)
    float m_pitchStickDecel;         // +0xc8
    float m_pitchReturnSpeed;        // +0xcc m_stickPitch back to the pitch limits after the stick
    float m_paramD0;                 // +0xd0 (ResolveViewObstructions)
    float m_paramD4;                 // +0xd4 (ResolveViewObstructions)
    float m_paramD8;                 // +0xd8 (ResolveViewObstructions)
    float m_paramDC;                 // +0xdc (ConstrainFollowToVolume)
    float m_paramE0;                 // +0xe0 (ConstrainFollowToVolume)
    float m_paramE4;                 // +0xe4 (ConstrainFollowToVolume)

    // The runtime state.
    // +0xe8 the track's flags (bit n = 1 << n): 4 (0x10) the camera service's flag 0x2000000, 5 (0x20) the stick pitch
    // returns, 6 (0x40) the stick moves the camera, 7 (0x80), 8 (0x100) the constraint zone did not change this frame,
    // 9 (0x200) the fixed follow spring, 10 (0x400) UpdateFramingAndPlaceCamera's result, 11 (0x800), 12 (0x1000),
    // 13 (0x2000) the stick is off, 15 (0x8000) no framing, 16 (0x10000) the zone's offset changed, 17 (0x20000),
    // 18 (0x40000) the last blend was skipped (a snap), 20 (0x100000), 21 (0x200000) the zone's +0x20 bit 15.
    uint32_t m_trackFlags;           // +0xe8 (Start clears it)
    SAccelDecelApproach m_pitch;     // +0xec the pitch (Math_ApproachAngleWithAccelDecel): m_current +0xf8, m_target +0x100
    float m_desiredPitch;            // +0x108 ComputeFocusPoint: the focus targets' weighted pitch (or the zone's +0x4c)
    float m_pitchMinA;               // +0x10c the pitch limits: the pitch is clamped to [max(A, B) min, min(A, B) max]
    float m_pitchMaxA;               // +0x110   (ResetState: -FLT_MAX / FLT_MAX)
    float m_pitchMinB;               // +0x114
    float m_pitchMaxB;               // +0x118
    float m_followSpeedXZ;           // +0x11c the follow spring's speed (IntegrateFollowOffset11C)
    float m_followSpeedY;            // +0x120 the vertical spring's speed (IntegrateFollowOffset120)
    float m_distance;                // +0x124 the orbit distance (target - position)
    float m_unk128;                  // +0x128 Update zeroes it on a zone change; ConstrainFollowToVolume
    float m_pullInSpeed;             // +0x12c the speed the distance shrinks back to m_defaultDistance
    CVector3 m_viewDir;              // +0x130 target - position, normalised
    float m_frustumPlanes[6][4];     // +0x13c BuildFrustumPlanes: (normal, d) x 6 (back, near, then the four sides)
    float m_yawStickSpeed;           // +0x19c
    float m_zoomStickSpeed;          // +0x1a0
    float m_stickPitch;              // +0x1a4 the pitch the stick asks for (ResetState: m_pitch.m_current)
    float m_pitchStickSpeed;         // +0x1a8
    float m_focusHeightOffset;       // +0x1ac added to the focus point's y (ComputeFocusPoint)
    float m_obstructionOffset;       // +0x1b0 _maybe (ResolveViewObstructions)
    CVector3 m_obstructionPoint;     // +0x1b4 _maybe (ResolveViewObstructions)
    float m_obstructionTime;         // +0x1c0 _maybe (ResolveViewObstructions: += dt)
    CVector3 m_unk1c4;               // +0x1c4 ResetState: the null vector
    float m_framingScale;            // +0x1d0 the framing's scale of the targets' radii, approaching m_framingScaleTarget
    float m_framingScaleTarget;      // +0x1d4
    CKCameraConstraint* m_pConstraint;  // +0x1d8 the constraint zone the track follows (the camera service's +0xe04)
    float m_volumeYawSpeed;          // +0x1dc _maybe (ConstrainFollowToVolume)
    float m_volumeYaw;               // +0x1e0 _maybe (ConstrainFollowToVolume; UpdateSteady: the yaw range's centre)
    float m_volumeYawRange;          // +0x1e4 the zone's yaw half range (+0x48 in look mode 1)
    CLineCollisionDatas m_obstructionHit;  // +0x1e8 TestCameraObstruction's mesh hit (the constructor: FLT_MAX, 0, -1, 0)
    CGroundEdgeDatasOut m_wallHit;   // +0x1f8 TestCameraObstruction's wall hit
    CVector3 m_lookDirection;        // +0x230 ComputeLookDirection's result for the zone
    CVector3 m_prevFocus;            // +0x23c the focus point of the previous frame
    float m_blendTime;               // +0x248 the time into the blend
    float m_blendDuration;           // +0x24c the blend's length (-1: no blend; 0 while it is set up)
    float m_blendSpeed;              // +0x250 _maybe (CaptureBlendStart: 6 t - 6 t^2 of the interrupted blend)
    float m_blendTimeScale;          // +0x254 CaptureBlendStart's f1
    SOrbitPose m_blendStart;         // +0x258
    SOrbitPose m_blendEnd;           // +0x270 ComputeDesiredPose
    SOrbitPose m_blendCurrent;       // +0x288
    CVector3 m_right;                // +0x2a0 (0, 1, 0) x m_viewDir, normalised
    SAccelDecelApproach m_fov;       // +0x2ac the field of view (Start: the camera service's +0x38 / +0x40 / +0x3c, m_fFov)
    float m_requestedFov;            // +0x2c8 SetFov (-1: none)
    float m_wallDistance;            // +0x2cc _maybe: the distance a wall left (ResolveWallMovement; -1: none)
    CVector3 m_zoneOffset;           // +0x2d0 the zone's offset (+0x70 / +0x74 of the constraint), approaching m_zoneOffsetTarget
    CVector3 m_zoneOffsetTarget;     // +0x2dc
    SAccelDecelApproach m_unk44Approach;  // +0x2e8 IKCamera +0x44 (Vf84 / Vf88) approached (m_current +0x2f4, m_target +0x2fc)
    float m_unk304;                  // +0x304 IKCamera +0x48 or the zone's +0x94 (Vf8C)
    float m_unk308;                  // +0x308 IKCamera +0x4c or the zone's +0x98 (Vf90)
    CVector3 m_groundPoint;          // +0x30c _maybe (ResolveGroundClearance)
};
DOTD_ASSERT_SIZE(CKCameraClassicTrack3, 0x318);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_unk58, +0x58);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_param5c, +0x5c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_followStiffness, +0x70);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_minDistance, +0x88);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_defaultDistance, +0x98);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_yawStickAccel, +0xa0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_stickPitchMin, +0xb8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_pitchReturnSpeed, +0xcc);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_paramE4, +0xe4);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_trackFlags, +0xe8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_pitch, +0xec);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_desiredPitch, +0x108);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_pitchMinA, +0x10c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_pitchMaxB, +0x118);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_followSpeedXZ, +0x11c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_followSpeedY, +0x120);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_distance, +0x124);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_unk128, +0x128);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_pullInSpeed, +0x12c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_viewDir, +0x130);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_frustumPlanes, +0x13c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_yawStickSpeed, +0x19c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_zoomStickSpeed, +0x1a0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_stickPitch, +0x1a4);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_pitchStickSpeed, +0x1a8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_focusHeightOffset, +0x1ac);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_obstructionOffset, +0x1b0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_obstructionPoint, +0x1b4);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_obstructionTime, +0x1c0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_unk1c4, +0x1c4);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_framingScale, +0x1d0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_framingScaleTarget, +0x1d4);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_pConstraint, +0x1d8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_volumeYawSpeed, +0x1dc);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_volumeYaw, +0x1e0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_volumeYawRange, +0x1e4);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_obstructionHit, +0x1e8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_wallHit, +0x1f8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_lookDirection, +0x230);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_prevFocus, +0x23c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_blendTime, +0x248);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_blendDuration, +0x24c);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_blendSpeed, +0x250);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_blendTimeScale, +0x254);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_blendStart, +0x258);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_blendEnd, +0x270);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_blendCurrent, +0x288);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_right, +0x2a0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_fov, +0x2ac);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_requestedFov, +0x2c8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_wallDistance, +0x2cc);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_zoneOffset, +0x2d0);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_zoneOffsetTarget, +0x2dc);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_unk44Approach, +0x2e8);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_unk304, +0x304);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_unk308, +0x308);
DOTD_ASSERT_OFFSET(CKCameraClassicTrack3, m_groundPoint, +0x30c);
