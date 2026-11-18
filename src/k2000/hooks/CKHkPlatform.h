// CKHkPlatform.h - a moving platform (key 0x3a42, vtable 0xb26000, size 0x1f4). Original unit:
// CKHkPlatform.cpp. XXL2 has CKHkPlatform (K/KMeca/Platform, base IKHkMeca); DotD's derives from
// CKHkActorBase and loads more (reference arrays, more floats). The motion: C2.8 port-final F01. XXL2 names are used where the layout
// matches: the three vectors and the quaternion read in XXL2's order (m_vPositionOffset, m_vStartPath,
// m_vDirPath, m_qBaseOrientation), the ground-contact pair, and the runtime block that the Load's inlined
// InitVariables sets (XXL2 CKHkPlatform::InitVariables, called at the end of its Load for every type).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkPlatform : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xe9)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c2ff8
        return key == 0x3a42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkPlatform)

    // 0x0041f278 CKHkPlatform_Create (inlined constructor): the ground-contact defaults, +0x08 = -1 (the
    // IKLife priority word) and +0x190 = 0xffff.
    CKHkPlatform() {
        m_ui32Priority = 0xffffffffu;
        m_pfPointIndex = 0xffff;
    }
    ~CKHkPlatform() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004212a0 CKHkPlatform_Load
    // vt+0x30 0x0041fbd0 CKHkPlatform_PostLoad: the actor base's; for the level type (0) the ground contact's defaults
    // (delta max 1, object height 0.5, masks {1, 8}, no ground, face -1, status 3, sector 0).
    int32_t PostLoad(int32_t type) override;
    // vt+0x10 0x0041f650 CKHkPlatform_Destroy: the actor base's, then both reference arrays freed (Mem_FreeAligned16).
    void Destroy() override;
    // vt+0x24 0x0041efb8 CKHkPlatform_RecursiveRegistration (see the .cpp).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x40 0x0041f498 CKHkPlatform_GetInfo: the trigger values 0x15e at start, 0x15f at end, 0x160 moving, 0x161
    // moving forward, 0x162 moving backward (all bytes; 0x0041e498 / 0x0041e4c0 / 0x0041f428 / 0x0041f3a0 / 0x0041f8d8);
    // the actor base (KStub_Return1 0x3f7140) answers 1.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    // vt+0x54 0x0041fde0 CKHkPlatform_Restart: unless bit 2, the node back to the path orientation and position, the
    // path-finding box blocked, the first ground's properties bit 1 cleared, sounds 3 and 1 stopped, the node's at row
    // kept (+0x1e0), the visibility applied (vt+0xd0 with bit 31), +0x10c = 1.
    void Restart() override;
    // vt+0xa0 0x0041f698 CKHkPlatform_OnActivate (see the .cpp).
    void VfA0() override;
    // vt+0xa4 0x0041fc78 CKHkPlatform_OnDeactivate: the actor base's, the grounds off, sounds 3 and 1 stopped, the
    // path-finding box freed, the particles (+0x150) off.
    void VfA4() override;
    // vt+0xb4 0x0041f310 CKHkPlatform_AttachSounds: the ten sounds of +0xbc (when there) attached to `leaf`.
    void KGLObjectAttached(IKSerializable* leaf) override;
    // vt+0xd0 0x0041f958 CKHkPlatform_vfD0: bit 31 = visible, the node's hidden bit, the particles (+0x150) on / off, the
    // grounds switched.
    void SetVisible(int32_t visible) override;
    // vt+0xf0 0x0041e4e8 CKHkPlatform_vfF0: 0.
    virtual int32_t VfF0() { return 0; }
    // vt+0x38 0x00421020 CKHkPlatform_SetDefaultState: the actor base's (empty); with `flag` an enabled platform's box
    // freed; the Load's runtime block again (InitVariables: the path distance +0x40 * +0x6c, the rotations, the points),
    // the movement bits from the bits 10..13 (flag 0: the start preset +0x154 / +0x156 / +0x158 too), then the
    // platform at the start distance (SetPathDistance, no box change).
    void SetDefaultState(int32_t flag) override;
    // vt+0xc8 0x00420630 CKHkPlatform_vfC8: the preset `state` (1: bits 14..16 / 18, the distance +0x80 * +0x6c, the bytes
    // +0x155 / +0x157 / +0x159; 0: bits 10..12 / 13, +0x40 * +0x6c, +0x154 / +0x156 / +0x158) into the movement bits.
    void ApplyStatePreset(int32_t state) override;
    // 0x004204a8 CKHkPlatform_SetPathDistance_maybe: with `block` the box freed first and blocked again after; the
    // distance kept (+0x15c), the position on the path (+0x194, plus the offset +0x88) and with bit 4 the orientation
    // along the path's direction (flat and normalised without bit 20) into +0x174.
    void SetPathDistance(float distance, int32_t block);
    // 0x0041ffe8 CKHkPlatform_EvaluatePathPosition_maybe: with bit 8 the path's point (the IKPath +0x28 vt+0x50, else
    // the flagged path +0x2c, whose waypoints crossed since its last distance each play the waypoint effect), else the
    // straight line from +0x94 along +0xa0 (distance / +0x6c) and the line's normalised direction.
    void EvaluatePathPosition(float distance, CVector3* position, CVector3* direction);
    // 0x00420270 CKHkPlatform_OrientAlongDirection_maybe: `q` the yaw of `direction` (about the Y axis); with bit 20 the
    // pitch first (about the flat side axis).
    void OrientAlongDirection(const CVector3* direction, float* q);
    // 0x0041ecd8 CKHkPlatform_PlayWaypointFx_maybe: an effect of +0x14c acquired (CKSrvFx::AcquireFx inlined), triggered
    // at the node's LTM (CKExplosionNodeFx::Trigger) and released (vt+0x54).
    void PlayWaypointFx();
    // 0x0041eb18 CKHkPlatform_StartMoveSounds_maybe: an enabled platform (bit 2 clear) whose loop (sound 1) is not playing
    // starts sound 0 once and the loop, both at the speed +0x84.
    void StartMoveSounds();
    // vt+0x1c 0x00425378 CKHkPlatform_MessageProc: the actor messages, then the platform's (the jump table 0x0042548c on
    // the low byte less 0x96, messages 0x996..0x9a8): reset, to the start / end / preset distance, stop, the move modes
    // (bits 24..27), the path-finding box on / off, bits 29 / 30, to a distance sent; the answers merged.
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x0041e578 CKHkPlatform_SetNavBlocking_maybe: with bit 9, a change of the blocked state (bit 28): the path-finding
    // box around the position (the node's at / right rows scaled by +0x70 / +0x74) blocked or freed.
    void SetNavBlocking(uint8_t blocked);
    // vt+0x7c 0x00424690 CKHkPlatform_Update: with bit 31 the platform moves (bit 23: UpdateMotion, else
    // AdvanceAlongPath); the heroes on its first ground sway it (bits 5 / 6, sounds 4..9) and sink it (bit 22); the
    // companions there at an end are told to leave (bit 7); the slope and path orientations are eased into the node
    // (with the quake +0x148 when it runs); the first ground is slippery past the tilt +0x30; the grounds refreshed.
    void Update(IKTime* clock) override;
    // 0x0041ec28 CKHkPlatform_EnsureLoopSoundPlaying_maybe: the loop (sound 1), when not playing, looped at the speed
    // +0x84 and played.
    void EnsureLoopSoundPlaying();
    // 0x004207c0 CKHkPlatform_SimulateSwaySpring_maybe: the spring's impulse (+0x1ac, plus the pushers +0x138 within
    // +0x13c or else `force`) integrated in 0.01 s steps into the velocity (+0x1c8) and the offset (+0x1d4) (on a path:
    // the distance `delta` along the direction +0x1e0); the heroes' tilt (+0x1b8 / +0x1c4) as `axis` and `rot`.
    void SimulateSwaySpring(float dt, float* delta, CVector3* axis, float* rot, const CVector3* force);
    // 0x00423620 CKHkPlatform_UpdateMotion_maybe (bit 23): the spring-driven motion (see the .cpp).
    void UpdateMotion(float dt, float* q, CVector3* at, CVector3* right);
    // 0x00423f70 CKHkPlatform_AdvanceAlongPath_maybe: the speed-driven motion (see the .cpp).
    void AdvanceAlongPath(float dt, float* q, CVector3* at, CVector3* right);

    uint8_t m_unk20;                           // +0x20 the count of +0x24
    uint8_t m_pad21[3];
    IKSerializable** m_apUnk24;                // +0x24 references (Mem_AllocAligned16)
    IKSerializable* m_unk28;                   // +0x28
    IKSerializable* m_unk2C;                   // +0x2c
    float m_unk30[8];                          // +0x30..+0x4c read in order
    float m_unk50[3];                          // +0x50..+0x58 read after the quaternion
    float m_unk5C[11];                         // +0x5c..+0x84 read after +0x4c
    CVector3 m_vPositionOffset;                // +0x88 XXL2 name (12-byte read)
    CVector3 m_vStartPath;                     // +0x94 XXL2 name
    CVector3 m_vDirPath;                       // +0xa0 XXL2 name
    float m_qBaseOrientation[4];               // +0xac XXL2 CQuaternion m_qBaseOrientation (16-byte read)
    IKSerializable* m_unkBC;                   // +0xbc
    CGroundContactDatasIn m_GrndDataIn;        // +0xc0 XXL2 name
    CGroundContactDatasInOut m_GrndDataInOut;  // +0xd0 XXL2 name
    CTriggerStarter m_unkFC;                   // +0xfc _maybe XXL2 m_tsReachedEnd
    CTriggerStarter m_unk104;                  // +0x104 _maybe XXL2 m_tsReachedStart
    uint8_t m_unk10C;                          // +0x10c runtime
    uint8_t m_unk10D;                          // +0x10d
    uint8_t m_pad10E[2];
    float m_unk110[9];                         // +0x110..+0x130
    uint8_t m_unk134;                          // +0x134 the count of +0x138
    uint8_t m_pad135[3];
    IKSerializable** m_apUnk138;               // +0x138 references (Mem_AllocAligned16), 0 without
    float m_unk13C;                            // +0x13c
    float m_unk140;                            // +0x140
    IKSerializable* m_unk144[4];               // +0x144..+0x150 four single reference reads
    uint8_t m_unk154[6];                       // +0x154..+0x159
    uint8_t m_pad15A[2];
    // The block below is set by the Load's inlined InitVariables for every serialization type.
    float m_fPositionOnPath;                   // +0x15c _maybe XXL2: +0x40 * +0x6c
    float m_fTimer;                            // +0x160 _maybe XXL2: 0
    float m_qLastSlopeRotation[4];             // +0x164 _maybe XXL2: (0, 0, 0, 1)
    float m_qLastPathRotation[4];              // +0x174 _maybe XXL2: m_qBaseOrientation
    CVector3 m_pfPoint;                        // +0x184 _maybe XXL2 CPFPoint m_pfPoint: (0, 0, 0)
    uint16_t m_pfPointIndex;                   // +0x190 constructor and InitVariables 0xffff
    uint8_t m_pad192[2];
    CVector3 m_vPosition;                      // +0x194 _maybe XXL2: (0, 0, 0)
    float m_unk1A0[2];                         // +0x1a0 runtime: the heroes' sway about the right / at axes (Update)
    float m_unk1A8;                            // +0x1a8 InitVariables 0
    CVector3 m_unk1AC;                         // +0x1ac InitVariables (0, 0, 0)
    CVector3 m_unk1B8;                         // +0x1b8 InitVariables (0, 0, 0)
    uint8_t m_unk1C4;                          // +0x1c4 InitVariables 0
    uint8_t m_pad1C5[3];
    CVector3 m_unk1C8;                         // +0x1c8 InitVariables (0, 0, 0)
    CVector3 m_unk1D4;                         // +0x1d4 InitVariables (0, 0, 0)
    CVector3 m_unk1E0;                         // +0x1e0 runtime: OnActivate / Restart keep the node's LTM at row
    uint8_t m_unk1EC;                          // +0x1ec runtime
    uint8_t m_pad1ED[3];
    float m_fUnk1F0;                           // +0x1f0 runtime (OnActivate: 0)
};
DOTD_ASSERT_SIZE(CKHkPlatform, 0x1f4);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_apUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vPositionOffset, 0x88);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vStartPath, 0x94);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vDirPath, 0xa0);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_qBaseOrientation, 0xac);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_GrndDataIn, 0xc0);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_GrndDataInOut, 0xd0);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk10D, 0x10d);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_apUnk138, 0x138);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk13C, 0x13c);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_fPositionOnPath, 0x15c);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_qLastSlopeRotation, 0x164);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_qLastPathRotation, 0x174);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_pfPoint, 0x184);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_pfPointIndex, 0x190);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vPosition, 0x194);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1A8, 0x1a8);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1AC, 0x1ac);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1B8, 0x1b8);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1C4, 0x1c4);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1C8, 0x1c8);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1D4, 0x1d4);
