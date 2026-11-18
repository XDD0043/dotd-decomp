// CKCameraPassivePathTrack.h - a camera that slides along a path (+0x74) while it watches a target that follows a second
// path (+0x78) or the camera service's focus (key 0x287, vtable 0xb1a380, size 0x134). Original unit:
// CKCameraPassivePathTrack.cpp (0x13e2b8-0x1419e0). Not in XXL2; no level file holds the class (nothing replays it).
// C2.8 port-rest R01 analysed it (field map in work/c28-report-port-R01.json); C2.8 port-final F01 ported it from the
// disassembly. Member names are ours.
//
// Four parameters blend with Math_ApproachWithAccelDecel (+0xc4 the target's offset along the focus node's at axis,
// +0xe0 the target's height, +0xfc the camera's lowest height above the focus, +0x118 the camera's distance), each
// started on its loaded value (+0x80..+0x8c) and retargeted by the messages 0x601 / 0x603 / 0x605 / 0x607 from the
// camera service's parameter table (+0x150, the entry +0xb4..+0xc0 that 0x600 / 0x602 / 0x604 / 0x606 choose). The
// flags +0xb0: bits 0-2 the start / follow mode (0 the nearer path end, 1 / 2 the path point nearest the target or the
// previous camera, 3 / 4 the direction, 4 the spring), bit 3 the distance in 3D (else flat), bit 5 the lateral lead
// (ComputeCameraPose), bit 6 the path wraps, bit 7 the direction, bits 8-9 the direction choice of modes 3 / 4.
#pragma once
#include <cstdint>

#include "k2000/cameras/IKCamera.h"
#include "k2000/core/Layout.h"

class IKFile;

class CKCameraPassivePathTrack : public IKCamera {
public:
    // vt+0x14 / +0x18 0x9a7760 / 0x9a7768: category 7 (camera), id 0xa.
    DOTD_CLASS_KEY(kCategoryCamera, 0xa)
    // vt+0x08 0x009a7738 CKCameraPassivePathTrack_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x287 || key == 0x347 || key == 0xc; }
    // 0x0013e2b8 _Delete, 0x0013eb98 _DeleteArray, 0x0013edf8 _CreateArray, 0x0013ef68 _Create.
    DOTD_DECLARE_FACTORIES(CKCameraPassivePathTrack)

    // 0x0013ef68 CKCameraPassivePathTrack_Create (= 0x13ea38 _Construct / 0x13eae8 _Construct_2): IKCamera's
    // constructor, then the defaults below; the rest is the fresh heap's zeroes.
    CKCameraPassivePathTrack();
    // 0x009a7778 / 0x009a77a8 [inline]: the vtable, IKCamera's destructor.
    ~CKCameraPassivePathTrack() override {}

    // vt+0x10 0x0013ea10 _Destroy: CKCameraTrack_ClearReferences_BaseNop_maybe (IKCamera's, empty): inherited.
    // vt+0x1c 0x0013ec38 _MessageProc: 0x600..0x607 (see the header comment); 0 for those, 1 for the others.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x0013e630 _RecursiveRegistration: IKCamera's, then both paths' (when set) with the same type.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x28 0x141548 _Save: not ported (the saves are out of scope).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00141020 CKCameraPassivePathTrack_Load
    // vt+0x30 0x0013e5e8 _PostLoad: IKCamera's (KStub_Return1_144570), the four parameter indices 0; 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x50 0x0013f030 CKCameraPassivePathTrack_Activate_maybe
    void Start(const CVector3* startPosition) override;
    void Pause() override {}   // vt+0x54 0x0013e308 CKCameraPassivePathTrack_vf54 (empty)
    // vt+0x58 0x0013e9e8 CKCameraPassivePathTrack_Deactivate_maybe: the attached fx stopped.
    void Stop() override { StopAttachedFx(); }
    void Resume() override {}  // vt+0x5c 0x0013e310 CKCameraPassivePathTrack_vf5C (empty)
    void Update(float frameTime) override;  // vt+0x60 0x0013fa18 CKCameraPassivePathTrack_Update_maybe
    float Vf84() const override { return m_unkAC; }  // vt+0x84 0x009a7770 [inline]: +0xac

    // 0x0013e6e0 CKCameraPassivePathTrack_ComputeCameraPose_maybe: the camera at `cameraPos` turned to `target`; the
    // lateral lead (+0x70) approaches (at +0xa8 a second) the focused hero's flat move direction along the camera's
    // right axis x +0xa4 (0 unless the service's first target is the focused hero's), and `target` moves along the right
    // axis by twice the lead x the half width at the camera-target distance.
    void ComputeCameraPose(float dt, const CVector3* cameraPos, CVector3* target);
    // The follow spring Update inlines (+0x60..+0x68): one step from `start`; the new current.
    float StepFollowSpring(float dt, float start);
    // Update's inlined far / near moves: the spring from `v`, the distance moved along `sign` (wrapped with bit 6, else
    // clamped to the path, the spring stopped there), the camera placed; the distance covered.
    float FollowAlongPath(float dt, float v, float sign);

    // The parameter blends (Math_ApproachWithAccelDecel states, k2000/misc/FloatApproach.h).
    struct SParamBlend {
        float m_accel;       // +0x00
        float m_decel;       // +0x04
        float m_maxSpeed;    // +0x08
        float m_current;     // +0x0c
        float m_speed;       // +0x10
        float m_target;      // +0x14
        float m_speedBonus;  // +0x18
    };

    float m_fTargetPathDist;       // +0x58 the target's distance on the target path
    float m_fCameraPathDist;       // +0x5c the camera's distance on the camera path
    float m_unk60;                 // +0x60 (Update's spring)
    float m_unk64;                 // +0x64
    float m_unk68;                 // +0x68
    int32_t m_i32Direction;        // +0x6c 1 / -1 (Start: 1)
    float m_fLateral;              // +0x70 the lateral lead (ComputeCameraPose)
    IKSerializable* m_pCameraPath; // +0x74 (Load) an IKPath
    IKSerializable* m_pTargetPath; // +0x78 (Load) an IKPath, or null: the service's focus
    float m_fPathSpeed;            // +0x7c (Load, read last)
    float m_afStart[4];            // +0x80..+0x8c (Load) the four blends' start values
    float m_unk90;                 // +0x90 (Load) the nearest distance (squared)
    float m_unk94;                 // +0x94 (Load) the follow spring's stiffness
    float m_unk98;                 // +0x98 (Load) its damping
    float m_unk9C;                 // +0x9c (Load) its top speed
    float m_unkA0;                 // +0xa0 (Load) the height offset (below the path when negative)
    float m_unkA4;                 // +0xa4 (Load) the lateral lead's gain
    float m_unkA8;                 // +0xa8 (Load) the lateral lead's speed
    float m_unkAC;                 // +0xac (Load; vt+0x84)
    uint16_t m_ui16Flags;          // +0xb0 (Load)
    uint8_t m_padB2[2];
    uint32_t m_aui32ParamIndex[4]; // +0xb4..+0xc0 the parameter table entries (0x600 / 0x602 / 0x604 / 0x606)
    SParamBlend m_aBlend[4];       // +0xc4 / +0xe0 / +0xfc / +0x118
};
DOTD_ASSERT_SIZE(CKCameraPassivePathTrack, 0x134);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_fTargetPathDist, 0x58);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_i32Direction, 0x6c);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_pCameraPath, 0x74);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_fPathSpeed, 0x7c);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_afStart, 0x80);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_unkAC, 0xac);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_ui16Flags, 0xb0);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_aui32ParamIndex, 0xb4);
DOTD_ASSERT_OFFSET(CKCameraPassivePathTrack, m_aBlend, 0xc4);
