// CKAdvancedCameraCinematicBloc.h - a scripted camera move (key 0x208, vtable 0xb1af70, size 0xb0). Original unit: CKAdvancedCameraCinematicBloc.cpp.
// Not in XXL2. Ten references (CKCurve2DCpnt in the Ghidra struct at +0x5c), a byte and three words.
//
// The move: from the start camera's pose (+0x38, or the camera service's real pose) to the end camera's (+0x3c, or the
// start), the position blended and offset by three curves, the view by yaw / pitch around the position (plus two curves
// in degrees), the field of view and the camera's vt+0x84 value blended plus a curve each; the camera that moves is
// +0x40 (or the end camera). Runtime +0x74: -2 after Start, -1 for the switch to the moving camera, then the time left.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKAdvancedCameraCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x8)
    DOTD_DECLARE_FACTORIES(CKAdvancedCameraCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00170b58 CKAdvancedCameraCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKAdvancedCameraCinematicBloc() {}
    ~CKAdvancedCameraCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00172560 CKAdvancedCameraCinematicBloc_Load
    // vt+0x24 0x001707e0 CKAdvancedCameraCinematicBloc_RecursiveRegistration: registered (unless the type is 4..7), the base's
    // (IKCinematicBloc_LevelReset), then each of the ten references +0x38..+0x5c (the cameras, the moved one, the
    // curves) that is set.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x5c 0x00171d40 CKAdvancedCameraCinematicBloc_Start: the scene takes the camera (its +0x24 bit 0), the shared
    // start, the start camera reset and switched to (transition +0x60 - 1 over +0x68, or none), both poses kept (the
    // yaw / pitch of the view, the end's turned the short way unless flag 0x100), the state -2.
    void Start() override;
    void Complete() override;               // vt+0x64 0x00171350: the completion, both cameras reset (vt+0x6c)
    // vt+0x68 0x00171570 CKAdvancedCameraCinematicBloc_Update (see the header comment); with flag 0x80 the bloc completes
    // +0x6c seconds after the move.
    void Update(IKTime* time) override;
    void Stop() override;                   // vt+0x6c 0x001704c8: the completion inlined, then Complete
    void Abort() override;                  // vt+0x70 0x001703a0: not running, both cameras reset

    // 0x00170da8 CKAdvancedCameraCinematicBloc_ComputeOrbitPoint_maybe: `base` plus the unit vector of `yaw` / `pitch`
    // (x = cos pitch sin yaw, y = sin pitch, z = cos yaw cos pitch).
    static CVector3 ComputeOrbitPoint(float yaw, float pitch, const CVector3& base);

    IKSerializable* m_apUnk38[10];  // +0x38 the start camera, +0x3c the end camera, +0x40 the camera moved (null: the end
                                    // camera); +0x44..+0x5c the curves (CKCurve2DCpnt) of x, y, z, yaw and pitch (degrees),
                                    // the field of view and the vt+0x84 value
    uint8_t m_unk60;                // +0x60 the start camera's transition + 1 (0: no transition)
    uint8_t m_pad61[3];
    float m_unk64;                  // +0x64 the move's duration (10.0 in LVL010)
    float m_unk68;                  // +0x68 the start camera's transition time
    float m_unk6c;                  // +0x6c with flag 0x80, the time the bloc holds after the move
    // Runtime (not set by the constructor nor the Load).
    float m_fEndTime;               // +0x70 the game clock when the move ended
    float m_fTimeLeft;              // +0x74 -2 / -1 / the move time left (see above)
    CVector3 m_v3StartPos;          // +0x78
    CVector3 m_v3EndPos;            // +0x84
    float m_fStartFov;              // +0x90 the start camera's +0x18
    float m_fStartValue84;          // +0x94 the start camera's vt+0x84
    float m_fEndFov;                // +0x98
    float m_fEndValue84;            // +0x9c
    float m_fStartYaw;              // +0xa0
    float m_fStartPitch;            // +0xa4
    float m_fEndYaw;                // +0xa8
    float m_fEndPitch;              // +0xac
};
DOTD_ASSERT_SIZE(CKAdvancedCameraCinematicBloc, 0xb0);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_apUnk38, +0x38);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk60, +0x60);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk64, +0x64);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk68, +0x68);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk6c, +0x6c);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_fEndTime, +0x70);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_v3StartPos, +0x78);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_fStartFov, +0x90);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_fEndPitch, +0xac);

// 0x001706a8 Math_GetYawPitchToPoint_maybe (dead in the original): the yaw and pitch of the direction from -> to.
void Math_GetYawPitchToPoint(const CVector3* from, const CVector3* to, float* yaw, float* pitch);
