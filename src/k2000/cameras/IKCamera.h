// IKCamera.h - the cameras (key 0x347, abstract; XXL2: K/KServices/KServiceCamera/IKCamera.h). PS3 size
// 0x58. Original unit: IKCamera.cpp (0x144108-0x146de8): the constructor (IKCamera_ConstructBase) and the
// common Load (CKCameraBase_Load), which every camera's Load calls first.
//
// XXL2's members are +0x08..+0x37 here, in XXL2's load order; DotD loads a reference at +0x04 (XXL2's
// CSBaseNode link) and adds +0x38..+0x57. The runtime slots (vt+0x50..) come with C2.2.
#pragma once
#include <cstdint>
#include <cstring>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class IKFile;

class IKCamera : public IKSerializable {
public:
    IKCamera();  // 0x001444a8 IKCamera_ConstructBase
    ~IKCamera() override {}

    // The cameras' runtime slots (XXL2 CKCamera: Start(const CVector3*), Pause, Stop, Resume, Update(float);
    // the tracks implement them, DotD's Start ignores the argument in CKCamera). The base defaults are empty:
    // a track class that is not ported starts / stops / updates nothing (LVL010 has CKCamera, CKCameraPathTrack,
    // CKCameraClassicTrack3 and CKAnimatedCamera; the others are later levels').
    virtual void Start(const CVector3* /*startPosition*/) {}  // vt+0x50 (CKCamera 0x13d9d8)
    virtual void Pause() {}                                   // vt+0x54 (CKCamera 0x13d918: empty)
    virtual void Stop() {}                                    // vt+0x58 (CKCamera 0x13db90; CKSrvCamera_StopAll_maybe calls it)
    virtual void Resume() {}                                  // vt+0x5c (CKCamera 0x13d920: empty)
    virtual void Update(float /*frameTime*/) {}               // vt+0x60 (CKCamera 0x13dc60)
    // vt+0x64 0x9a7170 (0): a path camera answers whether it is at the end of its path (CKCameraPathTrack 0x9a73e0
    // IsAtPathEnd_maybe); CKManageCameraCinematicBloc waits for it.
    virtual uint8_t IsFinished() { return 0; }
    // vt+0x68 0x9a7178 IKCamera_vf68: m_unk18 = value (CKCameraClassicTrack3 0x9a7d08: its +0x2c8).
    virtual void SetFov(float value) { m_unk18 = value; }
    // vt+0x6c 0x9a7180 (empty): CKCamera 0x13db38 CKCamera_ResetTrack_maybe, CKCameraPathTrack 0x9a7358.
    virtual void ResetTrack() {}
    // The slots after vt+0x6c (step 5; the vtables of CKCamera 0xb1a2b8, CKCameraPathTrack 0xb1a078 and
    // CKCameraClassicTrack3 0xb1aa50). The bit getters read big-endian bit numbers of the words (bit 0 = the low bit).
    virtual uint8_t Vf70() const { return static_cast<uint8_t>((m_Flags >> 12) & 1u); }  // vt+0x70 0x9a71e8
    // vt+0x74 0x00145088 IKCamera_FindAndRepairOcclusion_maybe (CKCameraClassicTrack3 0x162910 ResolveViewObstructions_maybe): f1 = dt, r5 = a
    // copy of the first focus target's position, r6 = the camera position to correct (r4 is not set by the callers).
    virtual void ResolveViewObstructions(float dt, const CVector3* focus, CVector3* position);
    // vt+0x78 0x001461a0 IKCamera_FindGroundContact_maybe (CKCameraClassicTrack3 0x15b000
    // ResolveGroundClearance_maybe): r4 = the target, r5 = the camera position to correct.
    virtual void ResolveCameraCollision(const CVector3* target, CVector3* position);
    virtual void GetFrameMargins(float* a, float* b) const;  // vt+0x7c 0x144378 IKCamera_GetFreezeYSpringStiffnessAndFriction_maybe: CKSrvCamera +0x8dc / +0x8e0
    virtual float Vf80() const { return 0.0f; }                // vt+0x80 0x9a7310 (TOC -0x3f48 = 0.0; CKCameraClassicTrack3 0x9a7d10: +0x5c)
    virtual float Vf84() const { return AsFloat(m_unk44); }    // vt+0x84 0x9a7188 (+0x44; CKCamera 0x9a7620: +0x58)
    virtual void Vf88(float value) { m_unk44 = AsWord(value); }  // vt+0x88 0x9a7190 (CKCamera 0x9a7638: +0x58 clamped to [-80, 80])
    virtual float Vf8C() const { return AsFloat(m_unk48); }    // vt+0x8c 0x9a7198 (CKCameraClassicTrack3 0x9a7cf0: +0x304)
    virtual float Vf90() const { return AsFloat(m_unk4c); }    // vt+0x90 0x9a71a0 (CKCameraClassicTrack3 0x9a7cf8: +0x308)
    virtual uint8_t Vf94() const { return 0; }                 // vt+0x94 0x9a71a8 (CKCameraClassicTrack3 0x9a7d18: !(+0xe8 bit 18))
    virtual uint8_t Vf98() const { return static_cast<uint8_t>(m_unk0c & 1u); }         // vt+0x98 0x9a72b8: +0x0c bit 0
    virtual void Vf9C(uint32_t value) { m_unk0c = (m_unk0c & ~1u) | value; }            // vt+0x9c 0x9a72f8
    virtual uint8_t VfA0() const { return static_cast<uint8_t>((m_unk0c >> 1) & 1u); }  // vt+0xa0 0x9a71b0: +0x0c bit 1
    virtual void VfA4(uint32_t value) { m_unk0c = (m_unk0c & ~2u) | (value << 1); }     // vt+0xa4 0x9a72d8
    virtual uint8_t VfA8() const { return static_cast<uint8_t>((m_unk0c >> 2) & 1u); }  // vt+0xa8 0x9a72c8: +0x0c bit 2
    virtual void VfAC(uint32_t value) { m_unk0c = (m_unk0c & ~4u) | (value << 2); }     // vt+0xac 0x9a71c0
    virtual uint8_t VfB0() const { return 1; }  // vt+0xb0 0x9a71e0 (CKCamera 0x9a7628: m_Flags bit 8; CKCameraClassicTrack3 0x9a7d28: 1)
    virtual uint8_t VfB4() const { return 0; }  // vt+0xb4 0x9a7318 (CKCameraClassicTrack3 0x9a7d30: 1)
    // CKCamera's vt+0xb8 0x9a76e8 (its own slot): CKCamera::SetPosition.

    static float AsFloat(uint32_t word) { float value; std::memcpy(&value, &word, 4); return value; }
    static uint32_t AsWord(float value) { uint32_t word; std::memcpy(&word, &value, 4); return word; }

    // 0x00144580 CKCameraBase_Load (non-virtual; the cameras' Loads call it first).
    int32_t BaseLoad(IKFile* file, int32_t type);
    // 0x00144398 IKCamera_UpdateTrackBase_maybe (non-virtual; the tracks' Updates call it first): the attached fx.
    void UpdateTrackBase();
    // 0x00144278 IKCamera_GetHalfExtentsAtDistance_maybe (non-virtual; r3 the camera, f1 the distance, r5 / r6 the
    // outputs): tan(m_unk18 / 2) * distance and that times the screen's height / width.
    void GetHalfExtentsAtDistance(float distance, float* halfWidth, float* halfHeight) const;
    // 0x00144330 IKCamera_GetEffectiveProfileIndex_maybe (non-virtual): the camera's avoiding-system index (+0x12), or
    // while the service holds a camera beacon (CKSrvCamera +0x915 / +0x920) the beacon's (+0x23). step 5 FRAME.
    uint8_t GetEffectiveProfileIndex() const;

    IKSerializable* m_unk04;                  // +0x04 a reference; 0 in the constructor
    uint32_t m_Flags;                         // +0x08 XXL2 CBitArray
    uint32_t m_unk0c;                         // +0x0c bits; the constructor sets bits 0 and 1, clears bit 2
    uint8_t m_CameraSmoothMode;               // +0x10
    uint8_t m_TargetSmoothMode;               // +0x11
    uint8_t m_TargetSafeMode;                 // +0x12
    uint8_t m_ui8CameraAvoidingSystemIndex;   // +0x13 (read after the +0x04 reference)
    float m_fFar;                             // +0x14
    float m_unk18;                            // +0x18 every Load copies m_fFov here (_maybe the current fov)
    float m_fFov;                             // +0x1c
    CVector3 m_WorldPosition;                 // +0x20
    CVector3 m_WorldTarget;                   // +0x2c
    IKSerializable* m_unk38;                  // +0x38 a reference (DotD)
    uint8_t m_unk3c;                          // +0x3c not set by the constructor nor the Load
    uint8_t m_unk3d;                          // +0x3d
    uint8_t m_unk3e;                          // +0x3e
    uint8_t m_pad3f;
    uint32_t m_unk40;                         // +0x40
    uint32_t m_unk44;                         // +0x44 0 in the constructor
    uint32_t m_unk48;                         // +0x48 0 in the constructor
    uint32_t m_unk4c;                         // +0x4c 0 in the constructor
    IKSerializable* m_unk50;                  // +0x50 a reference (DotD)
    uint32_t m_unk54;                         // +0x54 not set by the constructor nor the Load
};
DOTD_ASSERT_SIZE(IKCamera, 0x58);
DOTD_ASSERT_OFFSET(IKCamera, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(IKCamera, m_Flags, 0x08);
DOTD_ASSERT_OFFSET(IKCamera, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(IKCamera, m_CameraSmoothMode, 0x10);
DOTD_ASSERT_OFFSET(IKCamera, m_ui8CameraAvoidingSystemIndex, 0x13);
DOTD_ASSERT_OFFSET(IKCamera, m_fFar, 0x14);
DOTD_ASSERT_OFFSET(IKCamera, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(IKCamera, m_fFov, 0x1c);
DOTD_ASSERT_OFFSET(IKCamera, m_WorldPosition, 0x20);
DOTD_ASSERT_OFFSET(IKCamera, m_WorldTarget, 0x2c);
DOTD_ASSERT_OFFSET(IKCamera, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(IKCamera, m_unk3d, 0x3d);
DOTD_ASSERT_OFFSET(IKCamera, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(IKCamera, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(IKCamera, m_unk50, 0x50);
