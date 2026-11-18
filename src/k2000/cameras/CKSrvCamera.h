// CKSrvCamera.h - the camera service (key 0xc1, vtable 0xb19f08, size 0xe2c). Original unit:
// CKSrvCamera.cpp. XXL2: K/KServices/KServiceCamera/CKSrvCamera.h. From m_SmoothVisc (+0x1cc) to
// m_baTemporaryFlags (+0x46c) and from m_GContactIn (+0x6c8) to m_AvoidanceCpnt (+0x754) the PS3 layout
// follows XXL2's member order; DotD adds blocks before and after (unnamed here).
//
// C1.3 ports the constructor and the Load; C2.2 (strict2) the level start (InitializeService, ResetState,
// PostLoad, UpdateInitialize with the camera sectors and constraint zones). The embedded CKCamera at +0x4a4
// is a real member (IKCamera_ConstructBase runs on it, as in the original). step 5 the per-frame update
// (CKSrvCamera_UpdateFrame, CKSrvCamera_2.cpp), the transitions, blends, locks and shakes.
#pragma once
#include "k2000/core/Stub.h"
#include <cstdint>
#include <cstdlib>

#include "k2000/cameras/CKCamera.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

struct RwMatrix;
class CameraContext;
class CKCameraConstraint;
class CKCameraSector;
class CKQuakeCameraLauncher;
class CKQuakeCpntUpdater;
class CSGMovable;
class IKCamera;

class CKSrvCamera : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x3)
    DOTD_DECLARE_FACTORIES(CKSrvCamera)

    // A node of the list at +0x8e8 (12 bytes on the PS3, FreeListPool 0xceaa20): a running shake effect.
    struct SShakeNode {
        CKQuakeCpntUpdater* m_pEffect;     // +0x00 the effect (an updater of the group's quake)
        CKQuakeCameraLauncher* m_pSource;  // +0x04 the launcher that started it (its distance attenuation)
        SShakeNode* m_pNext;               // +0x08
    };
    // A node of the sector-mode camera lists (FreeListPool at 0x00ceaa30 in the original; 8 bytes).
    struct CameraNode {
        IKSerializable* m_pObject;  // +0x00
        CameraNode* m_pNext;        // +0x04
    };
    // +0x934 (0x28 on the PS3): what UpdateCameraBeacon gives the beacons' view test (CKCameraBeacon vt+0xc4). Names ours.
    struct SBeaconFrustum {
        CVector3 m_v3Position;   // +0x00 the focus (or the camera's target when a held beacon is tested again)
        RwMatrix* m_pMatrix;     // +0x0c RwMatrixCreate in the constructor: the view axes and position
        float m_fNear;           // +0x10 0.001 of the far plane
        float m_fFar;            // +0x14
        float m_fHalfWidth;      // +0x18 tan(fov / 2) / (h/w * 4/3)
        float m_fHalfHeight;     // +0x1c tan(fov / 2) * 0.75
        IKCamera* m_pCamera;     // +0x20 the current camera
        IKSerializable* m_pBeacon;  // +0x24 the beacon held
    };
    struct SCameraAvoidingDatas {  // 0x10 (XXL2 has six floats; DotD loads four)
        float m_afValues[4];
    };
    struct CGroundContactDatasIn {  // XXL2 names
        float m_fDeltaMax;                 // +0x00
        float m_fObjectHeight;             // +0x04
        uint32_t m_MasksOfGrdForTest[2];   // +0x08 constructor 1, 8
    };
    struct CGroundContactDatasInOut {  // XXL2 names
        IKSerializable* m_pGround;     // +0x00 CGround*; constructor 0
        int32_t m_i32FaceIndex;        // +0x04 constructor -1
        CVector3 m_Normal;             // +0x08
        uint32_t m_eContactStatus;     // +0x14 constructor 3
        CVector3 m_ProjectionOnGround; // +0x18
        float m_fdH;                   // +0x24
        uint8_t m_ui8SectorNumber;     // +0x28 constructor 0
        uint8_t m_pad29[3];
    };
    struct CClippedSpringFloat32 {  // XXL2 names
        float m_fTargetedValue;
        float m_fCurrentValue;
        float m_fCurrentSpeed;
    };
    // +0x8ec elements (0x10): a reference and a reference vector.
    struct RefGroup {
        IKSerializable* m_pObject;              // +0x00
        TVector<IKSerializable*, 1> m_vRefs;    // +0x04
    };
    // +0xd08 entries (0x30): the target stack (XXL2 m_apStartTarget / the targeted leaf): the Load pushes the
    // start target, UpdateInitialize the spawn point's node. Names ours.
    struct StackEntry {
        IKSerializable* m_pTarget;  // +0x00 a CSGLeaf (the hero's node)
        uint8_t m_unk04;            // +0x04
        uint8_t m_unk05;            // +0x05 constructor 1
        uint8_t m_pad06[2];
        float m_unk08;              // +0x08 -1
        uint8_t m_unk0c;            // +0x0c 0
        uint8_t m_pad0d[3];
        float m_unk10[4];           // +0x10 1.0
        float m_unk20;              // +0x20 -1
        float m_unk24[3];           // +0x24 FLT_MAX
    };

    CKSrvCamera();  // 0x0012c930 CKSrvCamera_Construct (= 0x12ce08)
    ~CKSrvCamera() override;  // 0x00131530 CKSrvCamera_Destructor (0x12f0c0 the deleting one)
    // vt+0x24 0x0012c2f0 CKSrvCamera_LevelReset (RecursiveRegistration).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x40 0x0012b0a8 CKSrvCamera_vf40 (GetInfo): 1, IKSerializable's default.

    void Destroy() override;                            // vt+0x10 0x0012d5a0 CKSrvCamera_Destroy
    // vt+0x1c 0x00130200 CKSrvCamera_HandleMessage (XXL2 MessageProc; FX): 0x300 the camera's collisions from
    // CKSrvCollision_ProcessPairs (the dodge ejection +0x770), 0x600 the fov record index (+0xbc), 0x601 the fov factor
    // (the approach at +0x8f8), 0x604 every shake stopped; 0 for these, 1 for the others.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001316d0 CKSrvCamera_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x130ad8 CKSrvCamera_PostLoad
    // vt+0x38 0x0012c1b0 CKSrvCamera_SetDefaultState: every object of the sector-mode lists, then every constraint
    // zone, gets SetDefaultState(flag & 0xff).
    void SetDefaultState(int32_t flag) override;
    void Start() override {}                            // vt+0x50 0x12a8e0 CKSrvCamera_vf50 (empty)
    void Restart() override;                            // vt+0x54 0x130a00 CKSrvCamera_Restart
    void Stop() override;                               // vt+0x68 0x1308f0 CKSrvCamera_StopAll_maybe
    void Pause() override;                              // vt+0x70 0x12a8e8 CKSrvCamera_vf70: the current camera's vt+0x54
    void Resume() override;                             // vt+0x78 0x12a938 CKSrvCamera_vf78: the current camera's vt+0x5c
    // vt+0x7c 0x1395a0 UpdateCKSrvCamera: with the frame clock running (+0x30 state 0), CKSrvCamera_UpdateFrame
    // 0x137ae0 with the unscaled frame time (+0x20).
    void Update(IKTime* frameClock) override;
    void SectorUnload(int32_t sector) override;         // vt+0x8c 0x12cce0 CKSrvCamera_vf8C
    int32_t InitializeService() override;               // vt+0x94 0x12c8e0 CKSrvCamera_vf94
    void DestroyService() override {}                   // vt+0x98 0x12a8d8 CKSrvCamera_vf98 (empty)
    // vt+0x9c 0x1395b8 CKSrvCamera_OnLevelStart_maybe (XXL2 UpdateInitialize).
    void UpdateInitialize() override;

    // The inlined stack push (UpdateInitialize twice, 0x130cc8 CKSrvCamera_PushCamera_maybe): `target` becomes
    // entry 0 with `blend` as its two blend values; an entry for the same target further down is removed (the
    // last entry takes its place). Sets the stack-changed bit when the first entry changed.
    void PushStackTarget(IKSerializable* target, float blend);
    // The inlined stack edits of CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe 0x2dd340 (the hero's camera target):
    // the index of `target` from entry 0 (the count when absent); entry `index` removed (the count one less, the last
    // entry moved into its place, the stack-changed bit 0x800000 set); the entries after the first holding `target`
    // removed (the entry moved into a removed place is not looked at); a new last entry for `target` with the mode flag
    // `flagA` and the default blend values (no bit set: the caller does).
    uint32_t FindStackTarget(const IKSerializable* target) const;
    void RemoveStackEntry(uint32_t index);
    void RemoveStackDuplicates(const IKSerializable* target);
    void AddStackEntry(IKSerializable* target, uint8_t flagA);
    // 0x0012d810 CKSrvCamera_ResetState_maybe (XXL2 InitializeStateOfSrvCamera): the pose, the transition and
    // the stack counters back to the defaults.
    void ResetState();
    // 0x0012ac50 CKSrvCamera_ResetCollisionProbes_maybe (XXL2 InitializeCollisionDatas).
    void ResetCollisionProbes();
    // 0x0012ac08 CKSrvCamera_SetPlayerCanMoveCamera (XXL2 SetPlayerCanMoveCamera(bool)): m_baTemporaryFlags bit 2
    // (0x4) set when forbidden; cleared when allowed unless bit 14 (0x4000) holds it.
    void SetPlayerCanMoveCamera(bool canMove);
    // 0x00137820 / 0x001337c0 CKSrvCamera_ComputeDesiredBasis_maybe / ComputeViewBasis_maybe: the internal
    // camera's (+0x4c4 -> +0x4d0) and the calculation pose's (+0x550 -> +0x55c) axes.
    void ComputeDesiredBasis();
    void ComputeViewBasis();
    // PORT: the transition and parameter-blend code (step 5, FX) addresses the word blocks +0x7b0..+0x887
    // (m_unk7b0 .. m_bUnk884) and +0xbdc..+0xd07 (m_unkbdc, m_unkc40) by their PS3 offsets. This maps such an offset to
    // the native member: the blocks hold no pointers, so their inner layout is the PS3's on every build (x64 included).
    uint8_t* Ps3Field(uint32_t offset) {
        if (offset >= 0x7b0 && offset < 0x888) return reinterpret_cast<uint8_t*>(m_unk7b0) + (offset - 0x7b0);
        if (offset >= 0xbdc && offset < 0xd08) return reinterpret_cast<uint8_t*>(m_unkbdc) + (offset - 0xbdc);
        DOTD_STUB_ONCE("CKSrvCamera::Ps3Field: an offset outside the mapped blocks");
        std::abort();
    }
    const uint8_t* Ps3Field(uint32_t offset) const { return const_cast<CKSrvCamera*>(this)->Ps3Field(offset); }
    // 0x001339a8 CKCameraBase_SetPositionAndTarget_maybe: the calculation position (+0x550) and target (+0x55c), then
    // ComputeViewBasis (a tail call).
    void SetCalculationPose(const CVector3* position, const CVector3* target);
    // 0x00132d88 CKSrvCamera_CaptureHeroHeadingLock_maybe (the FX family's; declared by CT3, step 5: the follow
    // track calls it after a snap behind the focus).
    void CaptureHeroHeadingLock();
    // 0x0012b648 CKSrvCamera_ReleaseHeroHeadingLock_maybe (FX): the heading lock (+0x64c) dropped once the hero moved and
    // turned past the captured angle, or the hero is no longer the first target.
    void ReleaseHeroHeadingLock();
    // 0x0012bc98 CKSrvCamera_EnableDirectionLock_maybe (FX; the hero's jumps): the ground normal (+0x8c4, made to point
    // up) and the focus copy as the ground reference; bit 0 of +0x46c set, and on the first lock (bit 16) +0x8ac too.
    void EnableDirectionLock(const CVector3* direction);
    // 0x00133f28 CKSrvCamera_UpdateCameraTransition_maybe (FX; UpdateFrame after TurnViewTowardDesiredDirection): the
    // blend from the previous camera's pose to the current one (+0x824 / +0x828), the camera parameter blend.
    void UpdateCameraTransition(float dt);
    // 0x0012b0b0 CKSrvCamera_StartCameraParamBlend_maybe (FX; UpdateFrame at a camera switch): the parameter block
    // (+0xbdc..+0xc3c) set from the new camera's (+0x38), or blended from the previous one's over +0x824; with
    // `keepVelocities` 0 (no blend was running) the start values are the previous camera's.
    void StartCameraParamBlend(uint8_t keepVelocities);
    // 0x0012d290 CKSrvCamera_UpdateCameraParamBlend_maybe (FX; UpdateCameraTransition): one step of that blend.
    void UpdateCameraParamBlend(float dt);
    // The framing step and the parameter blend that end both switch transitions (inline in UpdateCameraTransition,
    // 0x1345b4..0x1347d4): FX.
    void ApplyTransitionFraming(float dt);
    // 0x0012dca0 CKSrvCamera_ApplyCameraEffects_maybe (FX; UpdateFrame after UpdateCameraTransition): the running shakes
    // (+0x8e8, bit 0x80 of +0x46c) summed and applied to the calculation pose (+0x550 / +0x55c / axes +0x574..).
    void ApplyCameraEffects(float dt);
    // 0x0012e300 CKSrvCamera_QueueCameraEffect_maybe (FX; CKQuakeCameraLauncher_Trigger): the last idle shake of group
    // `group` (+0x8ec) started with `source` (its distance attenuation); 0 when all of them run.
    int32_t QueueCameraEffect(uint32_t group, CKQuakeCameraLauncher* source);
    // 0x0012eee8 CKSrvCamera_StartQuake_maybe (FX; CKHkLaunchQuakeCamera): the same for the group whose object is the
    // source's +0x04 (a CKQuakeCpnt); 0 without one.
    int32_t StartQuake(CKQuakeCameraLauncher* source);
    // 0x0012ac08 CKSrvCamera_SetPlayerCanMoveCamera (FX; the camera collision): `value` 0 sets bit 2 of +0x46c;
    // otherwise bit 2 is cleared unless bit 0x4000 is set.
    void SetFlag46CBit2WhenZero(int32_t value);
    // 0x0012b420 / 0x0012b4f0 CKSrvCamera_CanStartScriptedCamera_maybe / SetActiveScriptedCamera_maybe (FX; the scripted
    // camera handles): no active handle and +0xe08 seconds since the last one; the active handle (+0xe0c) and its time.
    bool CanStartScriptedCamera(float time) const;
    void SetActiveScriptedCamera(float time, IKSerializable* handle);
    // 0x0012b558 CKSrvCamera_IsPointInActiveConstraint_maybe (FX; CKGrpS08Hero's coop focus): `point` in one of the
    // constraint zones (+0xe00) with +0x20 bit 20 that are enabled for `sectorMode`.
    bool IsPointInActiveConstraint(const float* point, uint32_t sectorMode) const;
    // 0x0012c7d0 CKSrvCamera_FindIndexByKey_maybe (FX; CKQuakeCameraLauncher_PostLoad): the index of the last shake group
    // (+0x8ec) whose object is `key`; 0 when none or `key` is null.
    uint32_t FindIndexByKey(const IKSerializable* key) const;
    // 0x0012cd40 CKSrvCamera_AddShake_maybe / 0x0012b9a0 CKSrvCamera_StopAllShakes_maybe / 0x0012ba78
    // CKSrvCamera_AccumulateShake_maybe (FX; no caller in the EBOOT): `effect` started on the shake list; every shake
    // stopped and the list emptied; `effect`'s first six outputs (attenuation 1) added to `sum`, its running byte returned.
    void AddShake(CKQuakeCpntUpdater* effect, CKQuakeCameraLauncher* source);
    void StopAllShakes();
    uint8_t AccumulateShake(float dt, float scale, float sum[6], CKQuakeCpntUpdater* effect);
    // ---- step 5 FRAME: the service's frame (CKSrvCamera_2.cpp) ----
    // 0x00137ae0 CKSrvCamera_UpdateFrame: the frame-time ring and its mean (the time every camera step uses), the focus
    // and the target stack's positions, the constraint zone and the camera sector at the focus (a sector change asks for
    // a switch: m_pNextCamera), the switch itself (the blend start pose, the new camera started, the parameter blend),
    // then the current camera's Update and pose, the smoothing, the margins, the velocities, the turn limit, the
    // transition and the effects, and the result on the camera node, the camera context and the dodge spheres.
    void UpdateFrame(float frameTime);
    // 0x0012e508 CKSrvCamera_UpdateHeroGroundReference_maybe: with m_baTemporaryFlags bit 0 or 0x10000 and a first target,
    // `focus` kept on the ground plane of +0x8ac / +0x8c4 by a spring (+0x8d0..+0x8d8) driven by the camera's frame
    // margins (vt+0x7c).
    void UpdateHeroGroundReference(float dt, CVector3* focus);
    // 0x00135fd0 CKSrvCamera_FetchTrackPose_maybe: the calculation pose from the current camera (position, target, far
    // (the sector's +0x28 object of class 0x6d gives its own), fov) and the roll toward the camera's vt+0x84 (an
    // oscillation of amplitude vt+0x8c and frequency vt+0x90 around it), at the rate vt+0x94 allows. `camera` is unused
    // (the current camera is read again).
    void FetchTrackPose(float dt, CKCameraSector* sector, IKCamera* camera);
    // 0x00136348 CKSrvCamera_OrientMatrixToTarget_maybe: `matrix` (an RwMatrix as 16 floats) turned to look from its
    // position at `target`, `up` its approximate up (the old right axis when `up` is parallel to the view); with
    // `keepPitch` the at axis keeps its y.
    void OrientMatrixToTarget(const float* target, const float* up, float* matrix, uint8_t keepPitch);
    // 0x001366a0 CKSrvCamera_UpdateCameraBeacon_maybe: the camera beacons (+0x914..+0x968): the best beacon in the view
    // (+0x920) turns the calculation pose toward its position (+0x924); entering or leaving one blends the turn
    // (+0x916, +0x918 / +0x91c, the start quaternion +0x95c) when `blend`.
    void UpdateCameraBeacon(float dt, uint8_t blend);
    // 0x001339e8 CKSrvCamera_TurnViewTowardDesiredDirection_maybe: the calculation axes turned from the real ones by at
    // most dt * +0x7ac (a camera with vt+0x98, outside a blend); the limit holds (+0x46c bit 15) until they meet.
    void TurnViewTowardDesiredDirection(float dt);
    // 0x0012f268 CKSrvCamera_ResolveGroundClearance_maybe: a camera with m_Flags 0x1000 keeps `position` above the ground
    // (the final ground probe +0x704 / +0x714, the clearance from the near plane's half height and vt+0x80).
    void ResolveGroundClearance(float dt, CVector3* position, const CVector3* internalPosition, const CVector3* savedPosition,
                                const CVector3* focus);
    // 0x001354b0 CKSrvCamera_SmoothCalculationPosition_maybe: the calculation position as an offset from the internal
    // camera's (its axes), followed by the spring of smoothing mode `mode` (+0x1cc / +0x268, speed +0x788) in steps of
    // at most 0.02 s.
    void StepViewOffsetSpring(float dt, uint8_t mode);
    // 0x00135c80 CKSrvCamera_SmoothCalculationTarget_maybe: the same for the calculation target (speed +0x77c), from
    // the internal camera's target distance.
    void StepSmoothedTowardTrackPose(float dt, uint8_t mode);
    // 0x001357d0 CKSrvCamera_ApplyFrameMarginAdjustment_maybe: `point` kept inside the frame margins of profile
    // `profile` (AdjustViewToKeepTargetInFrameMargins on the calculation axes), the target moved by a spring (+0x7a0 ..
    // +0x7a8) toward the adjusted view; 1 when the view was adjusted.
    uint8_t ApplyFrameMarginAdjustment(float dt, uint8_t profile, const float* point);
    // 0x00132fd8 CKSrvCamera_AdjustViewToKeepTargetInFrameMargins_maybe: `axes` (an RwMatrix: the view axes and the
    // position) turned so that `point` stays inside the safe margins of profile `profile` for the field of view `fov`;
    // bit 0 / bit 1 of the result: it turned up or down / left or right. (The original also receives the frame time in f2
    // and `point` a second time in r5; neither is read.)
    uint8_t AdjustViewToKeepTargetInFrameMargins(float fov, float* axes, const float* point, uint8_t profile);
    // 0x0012fd98 CKSrvCamera_UpdateFrustumPlanes_maybe: the six frustum planes of the real pose.
    void UpdateFrustumPlanes();
    // 0x0012c830 CKSrvCamera_TestSphereAgainstFrustum: `sphere` = (x, y, z, radius) against the frustum planes lastPlane down to
    // 0 (the renderers pass 5): 0 outside one of them, 1 touching one, 2 inside; 2 for lastPlane -1.
    uint32_t TestSphereAgainstFrustum(const float sphere[4], int32_t lastPlane) const;
    // The frustum helpers nothing reachable calls (C2.8 port-rest R01; see CKSrvCamera.cpp).
    // 0x0012c560 CKSrvCamera_ComputeFrustumOutcode_maybe: per plane 5..0, in front (0x41 << k) / crossing (1 << k).
    uint32_t ComputeFrustumOutcode(const CVector3* point, float radius) const;
    // 0x0012fa38 CKSrvCamera_IsPointInFrustumScaled_maybe / 0x0012fbe8 CKSrvCamera_IsExtentInsideFrustum_maybe (dead).
    uint8_t IsPointInFrustumScaled(const CVector3* point, float fovDeg, float far, const CMatrix34* matrix, float right,
                                   float left, float up, float down) const;
    uint8_t IsExtentInsideFrustum(const CVector3* point, float fovDeg, float far, const CMatrix34* matrix, float right,
                                  float left, float up, float down) const;
    // 0x00132cd8 CKSrvCamera_GetFrustumPlaneNormal_maybe: plane `index`'s normal (flattened and normalised but plane 4's).
    CVector3 GetFrustumPlaneNormal(int32_t index) const;

    // The fog of the current camera (its parameter block +0x38, a CKCameraFogDatas), or while a camera transition runs
    // (m_baTemporaryFlags bit 3) the blended values kept in the service (C2.4 step 6). The defaults without a current
    // camera are the original's: density 0.01 / far density 100, far distance 0.01, colour white, start 0, end 1000.
    float GetFogStart() const;                      // 0x0012be60 CKSrvCamera_GetFogStart_maybe
    float GetFogEnd() const;                        // 0x0012bea0 CKSrvCamera_GetFogEnd_maybe
    float GetMainFogDensity() const;                // 0x0012bee0 FogManager_GetMainDensity_maybe
    float GetFarFogDensity() const;                 // 0x0012bda0 FogManager_GetFarDensity_maybe
    float GetFarFogDistance() const;                // 0x0012be20 FogManager_GetFarDistance
    void GetMainFogColor(uint8_t color[4]) const;   // 0x0012bfc0 FogManager_GetMainColor_maybe
    void GetFarFogColor(uint8_t color[4]) const;    // 0x0012bf60 FogManager_GetColorForFarPass_maybe
    // 0x0012e058 CKSrvCamera_UpdateCameraZones_maybe: the constraint zone the focus is in.
    void UpdateCameraZones();
    // 0x0012ecd0 CKSrvCamera_FindCameraSectorAtFocus_maybe (XXL2 FindCurrentCameraSector): the first enabled
    // camera sector of the current sector mode that holds the focus position; `requireCameras` skips sectors
    // without cameras, `exclude` skips one sector. Null when none.
    CKCameraSector* FindCameraSectorAtFocus(bool requireCameras, CKCameraSector* exclude);
    // 0x0012eaa0 CKSrvCamera_FindZoneCameraAtPosition_maybe: the first enabled camera sector of the current sector mode
    // that holds the first target's position and has a valid camera, that camera; null when none. With `refuse` (the
    // original passes 0) a sector without a valid camera that the previous sector mode does not hold ends the search.
    IKCamera* FindZoneCameraAtPosition(uint8_t refuse);
    // 0x00130cc8 CKSrvCamera_PushCamera_maybe (XXL2 SwitchToTarget): `target` becomes the first camera target (the
    // stack push of PushStackTarget). Without `transition` the real pose is kept as the start of the blend (quaternion,
    // positions, `blend` as its duration); with it the camera is switched on the next frame (m_pNextCamera, the switch
    // timer `blend`, mode flags), and at blend 0 with no cinematic owner the sector and camera at the target are chosen
    // again.
    void PushCamera(float blend, IKSerializable* target, int32_t transition);
    // 0x001314f8 CKSrvCamera_SwitchCameraIfDifferent_maybe: PushCamera unless `target` already is the first target.
    void SwitchCameraIfDifferent(float blend, IKSerializable* target, int32_t transition);

    CameraContext* m_pCameraContext;          // +0x00c constructor 0; InitializeService: the renderer's camera context
    CSGMovable* m_pCameraNode;                // +0x010 constructor 0; InitializeService: the context's camera node (key 0x14b)
    IKSerializable* m_pStartTarget;           // +0x014 a CSGLeaf (XXL2 m_apStartTarget): pushed on the target stack by the Load
    IKSerializable* m_lKCamera;               // +0x018 XXL2 CameraList m_lKCamera (its head)
    CameraNode*** m_aCameraSectorMode;        // +0x01c one list head per sector mode (_maybe: XXL2's next member)
    uint32_t m_ui32NbCameraSectorMode;        // +0x020
    uint32_t m_unk24[2];                      // +0x024
    uint32_t m_unk2c[0x24];                   // +0x02c 0x90 bytes, word-swapped
    uint32_t m_unkbc;                         // +0x0bc constructor 1
    uint32_t m_unkc0[0x24];                   // +0x0c0 0x90 bytes, word-swapped
    uint32_t m_unk150[0x1e];                  // +0x150 0x78 bytes, word-swapped
    uint32_t m_unk1c8;                        // +0x1c8
    CVector3 m_SmoothVisc[13];                // +0x1cc
    CVector3 m_SmoothKSpring[13];             // +0x268
    float m_afSafeOffsetYFromBasicTarget[10]; // +0x304
    float m_afSafeLeft[10];                   // +0x32c
    float m_afSafeRight[10];                  // +0x354
    float m_afSafeUp[10];                     // +0x37c
    float m_afSafeDown[10];                   // +0x3a4
    SCameraAvoidingDatas m_asAvoidingDatas[10];  // +0x3cc
    uint32_t m_baTemporaryFlags;              // +0x46c XXL2 m_baTemporaryFlags (bits: 0x80 shakes running, 0x40 scripted start position, 0x800000 stack changed, 0x200000 level started)
    IKCamera* m_pNextCamera;                  // +0x470 the camera being switched to (0 outside a transition)
    IKCamera* m_pCurrentCamera;               // +0x474 constructor 0 (XXL2 m_pCurrentCamera)
    IKCamera* m_pPreviousCamera;              // +0x478
    CKCameraSector* m_pCurrentSector;         // +0x47c XXL2 m_pCurrentSector
    float m_fSectorTimer;                     // +0x480 the sector's transition time (CKCameraSector +0x54), -1 when none
    CVector3 m_v3FocusPos;                    // +0x484 the position of the first stack entry's node (modelling matrix under a class-2 parent, else the LTM)
    CVector3 m_v3FocusPosCopy;                // +0x490 copy of +0x484
    uint32_t m_unk49c;                        // +0x49c
    uint32_t m_unk4a0;                        // +0x4a0
    CKCamera m_InternalCamera;                // +0x4a4 XXL2 CKCamera m_InternalCamera (0x88); the constructor runs IKCamera_ConstructBase on it
    CVector3 m_v3InternalAxisX;               // +0x52c ComputeDesiredBasis from the internal camera (XXL2 ComputeInternalCameraAxis)
    CVector3 m_v3InternalAxisY;               // +0x538
    CVector3 m_v3InternalAxisZ;               // +0x544
    CVector3 m_v3CalcPos;                     // +0x550 XXL2 m_v3CalculationCameraPos
    CVector3 m_v3CalcTarget;                  // +0x55c XXL2 m_v3CalculationTargetPos
    float m_fCalcFar;                         // +0x568 XXL2 m_fCalculationFar
    float m_fCalcFov;                         // +0x56c XXL2 m_fCalculationFoV
    float m_fCalcRoll;                        // +0x570
    CVector3 m_v3CalcAxisX;                   // +0x574 XXL2 m_v3CalculationCameraAxisX (ComputeViewBasis)
    CVector3 m_v3CalcAxisY;                   // +0x580
    CVector3 m_v3CalcAxisZ;                   // +0x58c
    CVector3 m_v3RealPos;                     // +0x598 XXL2 m_v3RealCameraPos
    CVector3 m_v3RealTarget;                  // +0x5a4 XXL2 m_v3RealTargetPos
    CVector3 m_v3RealAxisX;                   // +0x5b0 XXL2 m_v3RealCameraAxisX
    CVector3 m_v3RealAxisY;                   // +0x5bc
    CVector3 m_v3RealAxisZ;                   // +0x5c8
    float m_fRealFov;                         // +0x5d4 XXL2 m_fRealCameraFov
    float m_fRealFar;                         // +0x5d8 XXL2 m_fRealCameraFar
    CVector3 m_v3FrameRight;                  // +0x5dc the camera frame's matrix read back after the update
    CVector3 m_v3FrameUp;                     // +0x5e8
    CVector3 m_v3FrameAt;                     // +0x5f4
    CVector3 m_v3VelocityPos;                 // +0x600 per-second change of the position (UpdateFrame)
    CVector3 m_v3VelocityTarget;              // +0x60c
    CVector3 m_v3VelocityAxis;                // +0x618
    CVector3 m_v3HeadingDir;                  // +0x624 the view direction kept while the heading lock holds
    CVector3 m_v3LockHeroHeading;             // +0x630 CaptureHeroHeadingLock: the hero's heading
    CVector3 m_v3LockHeroPos;                 // +0x63c the hero node's position at the capture (0 after the reset)
    float m_fLockAngle;                       // +0x648
    uint8_t m_bHeadingLocked;                 // +0x64c
    uint8_t m_bHeadingLockEnabled;            // +0x64d
    uint8_t m_pad64e[2];
    CVector3 m_v3SavedPos;                    // +0x650 the calculation position of the last frame
    CVector3 m_v3SavedTarget;                 // +0x65c
    float m_afFrustumPlanes[6][4];            // +0x668 six planes (nx, ny, nz, d): UpdateFrustumPlanes
    CGroundContactDatasIn m_GContactIn;               // +0x6c8
    CGroundContactDatasInOut m_GContactInOut;         // +0x6d8
    CGroundContactDatasIn m_FinalGrdDataIn;           // +0x704
    CGroundContactDatasInOut m_FinalGrdDataInOut;     // +0x714
    CClippedSpringFloat32 m_csfCollisionSmoothSpring; // +0x740
    IKSerializable* m_pDodgeBS;               // +0x74c XXL2 CKBoundingSphere*
    IKSerializable* m_pDodgeBSPushCam;        // +0x750 XXL2 CKBoundingSphere*
    // XXL2 CKAvoidanceCpnt m_AvoidanceCpnt (+0x754..+0x770).
    uint32_t m_bSubscribedToAvoidance;        // +0x754
    float m_fRadius;                          // +0x758
    IKSerializable* m_pKGLObject;             // +0x75c CSGLeaf*; the Load sets 0
    CVector3 m_v3DynamicAvoidForce;           // +0x760
    uint32_t m_ui32NbAffectingObst;           // +0x76c
    uint32_t m_unk770[3];                     // +0x770
    CVector3 m_v3Unk77c;                      // +0x77c PostLoad / ResetState: the null vector
    CVector3 m_v3Unk788;                      // +0x788 the null vector
    CVector3 m_v3Unk794;                      // +0x794 the calculation target (+0x55c)
    CVector3 m_v3Unk7a0;                      // +0x7a0 constructor 0.0
    uint32_t m_unk7ac;                        // +0x7ac
    uint32_t m_unk7b0[0x1d];                  // +0x7b0
    float m_fBlendDuration;                   // +0x824 the transition time to the new camera (StartCameraParamBlend divides by it)
    float m_fBlendElapsed;                    // +0x828
    float m_fSwitchTimer;                     // +0x82c
    uint8_t m_ui8TransitionMode;              // +0x830
    uint8_t m_ui8PreviousTransitionMode;      // +0x831
    uint8_t m_pad832[2];
    CVector3 m_v3ScriptedStart;               // +0x834 UpdateInitialize: the spawn point's camera position
    uint32_t m_unk840[2];                     // +0x840
    uint8_t m_unk848;                         // +0x848
    uint8_t m_unk849;                         // +0x849
    uint8_t m_pad84a[2];
    uint32_t m_unk84c[14];                    // +0x84c
    uint8_t m_bUnk884;                        // +0x884
    uint8_t m_bUnk885;                        // +0x885
    uint8_t m_pad886[2];
    uint8_t m_ui8ProbeFlags;                  // +0x888 the byte of the word at +0x888 (bits 0..2)
    uint8_t m_pad889[3];
    uint32_t m_unk88c[4];                     // +0x88c
    float m_fUnk89c;                          // +0x89c ResetCollisionProbes: 0
    float m_unk8a0[3];                        // +0x8a0 constructor 0.0
    CVector3 m_v3GroundRefA;                  // +0x8ac UpdateHeroGroundReference
    CVector3 m_v3GroundRefB;                  // +0x8b8
    CVector3 m_v3GroundNormal;                // +0x8c4
    float m_unk8d0[3];                        // +0x8d0 constructor 0.0
    uint32_t m_unk8dc;                        // +0x8dc
    uint32_t m_unk8e0;                        // +0x8e0
    float m_fUnk8e4;                          // +0x8e4 ResetState: 1.0
    SShakeNode* m_unk8e8;                     // +0x8e8 the running shake effects (FreeListPool 0xceaa20); constructor 0
    TVector<RefGroup, 1> m_vUnk8ec;           // +0x8ec
    uint32_t m_unk8f8[6];                     // +0x8f8 (the accel/decel state of Math_ApproachWithAccelDecel)
    uint32_t m_unk910;                        // +0x910
    uint8_t m_bUnk914;                        // +0x914 ResetState: 1
    uint8_t m_bUnk915;                        // +0x915
    uint8_t m_bUnk916;                        // +0x916
    uint8_t m_bUnk917;                        // +0x917
    float m_fBeaconBlendTime;                 // +0x918 the beacon turn's time left (UpdateCameraBeacon)
    float m_fBeaconBlendDuration;             // +0x91c
    IKSerializable* m_pUnk920;                // +0x920 the camera beacon in view (a CKCameraBeacon: its byte +0x23 is the camera profile index)
    CVector3 m_v3BeaconPos;                   // +0x924 the position of its node
    CameraNode* m_pUnk930;                    // +0x930 constructor 0; the beacons to test this frame (FreeListPool 0xceaa30; UpdateFrame empties it)
    SBeaconFrustum m_BeaconFrustum;           // +0x934 the view the beacons are tested against (CKCameraBeacon vt+0xc4)
    float m_afBeaconBlendQuat[4];             // +0x95c the start rotation of a beacon turn's blend (relative to the calculation axes)
    float m_unk96c[3];                        // +0x96c constructor 0.0
    uint32_t m_ui32FrameTimeIndex;            // +0x978 constructor 0: the ring index of the 150 frame times
    float m_afFrameTimes[0x96];               // +0x97c the last 150 frame times (UpdateFrame)
    float m_fFrameTimeSum;                    // +0xbd4 constructor 0
    float m_fFrameTimeMean;                   // +0xbd8 constructor 0
    float m_unkbdc[0x19];                     // +0xbdc constructor 0.0
    uint32_t m_unkc40[10][5];                 // +0xc40 0x14-byte records, five words each
    StackEntry m_aStack[5];                   // +0xd08
    uint32_t m_ui32NbStacked;                 // +0xdf8
    uint32_t m_ui32NbUnke00;                  // +0xdfc
    IKSerializable** m_apUnke00;              // +0xe00 OperatorNewArray; constructor 0
    CKCameraConstraint* m_pActiveConstraint;  // +0xe04 the constraint zone the focus is in (UpdateCameraZones)
    uint32_t m_unke08;                        // +0xe08
    IKSerializable* m_pScriptedCameraHandle;  // +0xe0c ScriptedCameraHandle (SetActiveScriptedCamera)
    float m_fScriptedCameraTimer;             // +0xe10 ResetState: -1
    IKSerializable* m_apCinematicOwner[4];    // +0xe14 CKCinematicScene* (CKSrvCinematic_AddOrRemoveCameraOwner_maybe)
    uint32_t m_unke24;                        // +0xe24 constructor 0: nonzero while a cinematic owns the camera
    uint32_t m_unke28;                        // +0xe28
};
DOTD_ASSERT_SIZE(CKSrvCamera::StackEntry, 0x30);
DOTD_ASSERT_SIZE(CKSrvCamera::CGroundContactDatasInOut, 0x2c);
DOTD_ASSERT_SIZE(CKSrvCamera::RefGroup, 0x10);
DOTD_ASSERT_SIZE(CKSrvCamera::SBeaconFrustum, 0x28);
DOTD_ASSERT_SIZE(CKSrvCamera, 0xe2c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pStartTarget, 0x14);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_lKCamera, 0x18);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_ui32NbCameraSectorMode, 0x20);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unkbc, 0xbc);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unkc0, 0xc0);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk150, 0x150);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_SmoothVisc, 0x1cc);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_SmoothKSpring, 0x268);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_afSafeOffsetYFromBasicTarget, 0x304);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_afSafeDown, 0x3a4);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_asAvoidingDatas, 0x3cc);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_baTemporaryFlags, 0x46c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk49c, 0x49c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_InternalCamera, 0x4a4);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_GContactIn, 0x6c8);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_GContactInOut, 0x6d8);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_FinalGrdDataIn, 0x704);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_FinalGrdDataInOut, 0x714);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_csfCollisionSmoothSpring, 0x740);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pDodgeBS, 0x74c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_bSubscribedToAvoidance, 0x754);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pKGLObject, 0x75c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk7ac, 0x7ac);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk8a0, 0x8a0);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk8d0, 0x8d0);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk8dc, 0x8dc);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk8e8, 0x8e8);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_vUnk8ec, 0x8ec);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pUnk930, 0x930);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_BeaconFrustum, 0x934);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_afBeaconBlendQuat, 0x95c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unk96c, 0x96c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_ui32FrameTimeIndex, 0x978);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_afFrameTimes, 0x97c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_fFrameTimeSum, 0xbd4);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pNextCamera, 0x470);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pCurrentSector, 0x47c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3FocusPos, 0x484);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3InternalAxisX, 0x52c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3CalcPos, 0x550);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3CalcAxisX, 0x574);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3RealPos, 0x598);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_fRealFov, 0x5d4);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3FrameRight, 0x5dc);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3VelocityPos, 0x600);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3HeadingDir, 0x624);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_bHeadingLocked, 0x64c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3SavedPos, 0x650);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_afFrustumPlanes, 0x668);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3Unk77c, 0x77c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3Unk7a0, 0x7a0);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_fBlendDuration, 0x824);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_ui8TransitionMode, 0x830);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3ScriptedStart, 0x834);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_bUnk884, 0x884);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_ui8ProbeFlags, 0x888);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_fUnk89c, 0x89c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_v3GroundRefA, 0x8ac);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_fUnk8e4, 0x8e4);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_bUnk914, 0x914);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pUnk920, 0x920);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pActiveConstraint, 0xe04);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_pScriptedCameraHandle, 0xe0c);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_fScriptedCameraTimer, 0xe10);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unkbdc, 0xbdc);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unkc40, 0xc40);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_aStack, 0xd08);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_ui32NbStacked, 0xdf8);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_apUnke00, 0xe00);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unke08, 0xe08);
DOTD_ASSERT_OFFSET(CKSrvCamera, m_unke24, 0xe24);
