// CKCameraPathTrack.h - a camera that follows a path (key 0x107, vtable 0xb1a078, size 0x84). Original unit: CKCameraPathTrack.cpp.
// XXL2: the same members in the same load order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/math/CVector2.h"

class IKFile;

class CKCameraPathTrack : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0x4)
    DOTD_DECLARE_FACTORIES(CKCameraPathTrack)

    CKCameraPathTrack();  // 0x0013ba58 CKCameraPathTrack_Create (the same stores as CKCameraPathTrack_Construct 0x13b2b0)
    ~CKCameraPathTrack() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0013bab8 CKCameraPathTrack_Load
    // vt+0x30 0x0013b070 CKCameraPathTrack_PostLoad: IKCamera's (KStub_Return1_144570), 1: the default.

    // The runtime slots (step 5, FX).
    // vt+0x50 0x0013b138 CKCameraPathTrack_Activate_maybe: the attached fx started (CKCamera_StartAttachedFx_maybe); with a
    // path, the distance and the time back to 0 and one Update (vt+0x60) of 0 s.
    void Start(const CVector3* startPosition) override;
    void Pause() override {}   // vt+0x54 0x0013ae20 CKCameraPathTrack_vf54 (empty)
    // vt+0x58 0x0013b110 CKCameraPathTrack_Deactivate_maybe: the attached fx stopped (CKCamera_StopAttachedFx_maybe).
    void Stop() override;
    void Resume() override {}  // vt+0x5c 0x0013ae28 CKCameraPathTrack_vf5C (empty)
    // vt+0x60 0x0013b330 CKCameraPathTrack_Update_maybe: the time advances; the distance on the path by dt x speed
    // (fmadds), wrapped into [0, length) with the loop bit (+0x80 bit 2), else clamped to the length; the position is the
    // path's point there. The target by the mode (+0x80 bits 0-1): 0 the camera service's focus (+0x484), 1 the
    // reference (+0x74), both raised by +0x64; 2 the position plus the reference; 3 the position plus the reference in
    // the path's frame (right = the path direction, up = y).
    void Update(float frameTime) override;
    // vt+0x64 0x009a73e0 CKCameraPathTrack_IsAtPathEnd_maybe: without the loop bit, the distance equals the path's length.
    uint8_t IsFinished() override;
    void ResetTrack() override { m_fPosOnPath = 0.0f; }  // vt+0x6c 0x009a7358 CKCameraPathTrack_ResetTrack_maybe
    // vt+0x84 0x0013ae30 CKCameraPathTrack_GetRollAtTime_maybe: the roll at the current time from the (time, roll) points (+0x68): the
    // line through the points around it (lo.y when the segment is flat in either axis), an end value outside, 0
    // without points.
    float Vf84() const override;

    IKSerializable* m_pPath;       // +0x58 IKPath (CKSpline4L in the files)
    float m_fPosOnPath;            // +0x5c
    float m_fCameraSpeed;          // +0x60
    float m_fTargetOffset;         // +0x64
    CVector2* m_av2RollAlongTime;  // +0x68 new[] (the PS3 array has a count cookie); 0 in the constructor
    uint32_t m_ui32NbRollPoint;    // +0x6c
    float m_fTimeSinceStart;       // +0x70 runtime
    CVector3 m_v3StartTargetRef;   // +0x74
    uint8_t m_ba8PathTrackInfos;   // +0x80 CBitArray8
    uint8_t m_pad81[3];
};
DOTD_ASSERT_SIZE(CKCameraPathTrack, 0x84);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_pPath, +0x58);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_fPosOnPath, +0x5c);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_fCameraSpeed, +0x60);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_fTargetOffset, +0x64);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_av2RollAlongTime, +0x68);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_ui32NbRollPoint, +0x6c);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_fTimeSinceStart, +0x70);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_v3StartTargetRef, +0x74);
DOTD_ASSERT_OFFSET(CKCameraPathTrack, m_ba8PathTrackInfos, +0x80);
