// CKCameraSpyTrack.h - a camera above the focused node that follows it with accelerated smoothing and can be moved and
// zoomed with the right stick (key 0x207, vtable 0xb1a440, size 0x108). Original unit: CKCameraSpyTrack.cpp
// (0x1419e0-0x143b58). XXL2: the same members in the same order (shifted by IKCamera's size). No level file holds the
// class: nothing exercises it.
//
// The position is the target raised by the current distance and turned about the world x axis by m_fXAngle degrees. The
// game manager's directions (vt+0x188): 5 / 6 zoom to the min / max distance (FloatApproach_Step), 0 / 1 move the camera in
// -z / +z and 2 / 3 in -x / +x (only while the camera service lets the player move it), 4 restores the smoothing speeds;
// otherwise the target and the position glide towards the node's and its raised point's (CSmoothedCVector3Accelerated-
// Linear: decelerating inside m_fTargetToTargetDistance / m_fPositionToPositionDistance, m_fSlowDistance percent of the
// distance when the node moved).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"

class IKFile;

class CKCameraSpyTrack : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0x8)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a77f0
        return key == 0x207 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraSpyTrack)

    // XXL2 CSmoothedFloat32Linear (the FloatApproach state {target, speed, current}).
    struct CSmoothedFloat32Linear {
        float m_fTargetedValue;  // +0x00
        float m_fCurrentSpeed;   // +0x04
        float m_fCurrentValue;   // +0x08
    };
    // XXL2 CSmoothedCVector3AcceleratedLinear.
    struct CSmoothedCVector3AcceleratedLinear {
        CVector3 m_v3TargetedVector;  // +0x00
        CVector3 m_v3CurrentVector;   // +0x0c
        float m_fTargetedSpeed;       // +0x18
        float m_fCurrentSpeed;        // +0x1c
        float m_fAcceleration;        // +0x20
    };
    // XXL2 CClippedSpringFloat32.
    struct CClippedSpringFloat32 {
        float m_fTargetedValue;  // +0x00
        float m_fCurrentValue;   // +0x04
        float m_fCurrentSpeed;   // +0x08
    };

    // 0x00141be8 CKCameraSpyTrack_Create: IKCamera_ConstructBase, the vtable, the distance and the two springs zeroed.
    CKCameraSpyTrack() {
        m_sfCurrentDistance = {0.0f, 0.0f, 0.0f};
        m_csfAxisSpeed = {0.0f, 0.0f, 0.0f};
        m_csfMoveSpeed = {0.0f, 0.0f, 0.0f};
    }
    ~CKCameraSpyTrack() override {}  // 0x9a7828 / 0x9a7858 (inline)

    // vt+0x10 0x00141b18 CKCameraSpyTrack_Destroy: CKCameraTrack_ClearReferences_BaseNop_maybe (empty): inherited.
    // vt+0x24 0x00141af0 CKCameraSpyTrack_RecursiveRegistration: IKCamera's (0x144108), then 1: inherited.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00141c70 CKCameraSpyTrack_Load

    void Start(const CVector3* startPosition) override;  // vt+0x50 0x00143540 CKCameraSpyTrack_Activate_maybe
    void Pause() override {}                              // vt+0x54 0x00141a30 CKCameraSpyTrack_vf54 (empty)
    void Stop() override;                                 // vt+0x58 0x00141ac8 CKCameraSpyTrack_Deactivate_maybe
    void Resume() override {}                             // vt+0x5c 0x00141a38 CKCameraSpyTrack_vf5C (empty)
    void Update(float frameTime) override;                // vt+0x60 0x00142080 CKCameraSpyTrack_Update_maybe

    // The raised and turned point (inlined three times): (x, y + the current distance, z) turned about x by m_fXAngle.
    void RaiseAndTurn(float x, float y, float z, float* outY, float* outZ) const;

    float m_fMaxCameraTargetDistance;          // +0x58
    float m_fMinCameraTargetDistance;          // +0x5c
    float m_fAxisSpeed;                        // +0x60
    float m_fMoveSpeed;                        // +0x64
    float m_fSlowDistance;                     // +0x68 (a percentage of the re-aim distances)
    float m_fXAngle;                           // +0x6c degrees
    float m_fTargetToTargetDistance;           // +0x70
    float m_fPositionToPositionDistance;       // +0x74
    CSmoothedFloat32Linear m_sfCurrentDistance;          // +0x78
    CSmoothedCVector3AcceleratedLinear m_sv3TargetPosition;  // +0x84
    CSmoothedCVector3AcceleratedLinear m_sv3CameraPosition;  // +0xa8
    CClippedSpringFloat32 m_csfAxisSpeed;      // +0xcc
    CClippedSpringFloat32 m_csfMoveSpeed;      // +0xd8 (not used by DotD's code)
    CVector3 m_v3OldTargetPosition;            // +0xe4
    CVector3 m_v3OldCameraPosition;            // +0xf0
    CVector3 m_v3CameraToTargetDir;            // +0xfc
};
DOTD_ASSERT_SIZE(CKCameraSpyTrack, 0x108);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_fMaxCameraTargetDistance, +0x58);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_fPositionToPositionDistance, +0x74);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_sfCurrentDistance, +0x78);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_sv3TargetPosition, +0x84);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_sv3CameraPosition, +0xa8);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_csfAxisSpeed, +0xcc);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_v3OldTargetPosition, +0xe4);
DOTD_ASSERT_OFFSET(CKCameraSpyTrack, m_v3CameraToTargetDir, +0xfc);
