// CKCameraConstraint.h - a camera constraint zone (DotD; not in XXL2) (key 0x7f0c, vtable 0xb130a0, size 0xa0). Original unit: CKCameraConstraint.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/services/CTriggerStarter.h"

class IKFile;
struct CVector3;

class CKCameraConstraint : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1fc)
    DOTD_DECLARE_FACTORIES(CKCameraConstraint)

    // 0x00153e18 CKCameraConstraint_Create: the vtable only.
    CKCameraConstraint() {}
    ~CKCameraConstraint() override {}

    // vt+0x1c 0x00154278 CKCameraConstraint_MessageProc: 0x600 switch on, 0x601 switch off (and leave), 0x602 enter
    // (become the camera service's active zone), 0x603 leave; 0 for these, 1 for any other message.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00155c68 CKCameraConstraint_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00154070 CKCameraConstraint_PostLoad
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x00153b10 CKCameraConstraint_SetDefaultState
    int32_t SetGameState(const SApplyGameState* state) override;  // vt+0x3c 0x00153ea0 CKCameraConstraint_SetGameState

    // 0x00153f00 CKCameraConstraint_IsEnabledFor_maybe: the constraint is switched on (m_unk1c bit 2), belongs to
    // the current sector (or to none: +0x24 is 0) and its mask (+0x8c) holds bit `sectorMode`.
    bool IsEnabledFor(uint32_t sectorMode) const;
    // 0x001540d8 CKCameraConstraint_ContainsPoint_maybe: the point (x, y, z) is in the zone: its camera volume's
    // test (+0x7c, vt+0xc4) or the box (+0x04, six floats: max x, y, z then min x, y, z) narrowed by the
    // shape in m_unk1c bits 3-4 (0 box, 1 cylinder over x/z, 2 sphere over the x extent).
    bool ContainsPoint(const float* point) const;

    float m_afBox[6];           // +0x04 one 0x18 read, six swapped words: the maximum corner then the minimum (a CBBox)
    // +0x1c bit 0 the initial "on" state (SetDefaultState copies it to bit 2), bit 1 _maybe "searchable" (CKSrvCamera::
    // UpdateCameraZones stops at the first zone without it and keeps a current zone without it), bit 2 on (messages
    // 0x600 / 0x601, SetGameState), bits 3-4 the volume shape (0 box, 1 vertical cylinder, 2 sphere; 3 none), bits 5-6
    // the look mode (3: keep the previous zone).
    uint8_t m_unk1c;
    uint8_t m_pad1d[3];
    float m_unk20;              // +0x20
    float m_unk24;              // +0x24
    CTriggerStarter m_tsUnk28;  // +0x28
    CTriggerStarter m_tsUnk30;  // +0x30
    uint8_t m_unk38;            // +0x38
    uint8_t m_pad39[3];
    IKSerializable* m_unk3c;    // +0x3c
    IKSerializable* m_unk40;    // +0x40
    float m_afUnk44[12];        // +0x44 read in a scrambled order (see the Load)
    uint32_t m_unk74;           // +0x74 not set by the constructor nor the Load; entering the zone copies +0x6c here
    float m_unk78;              // +0x78
    IKSerializable* m_unk7c;    // +0x7c a CKHkDetectorGroup (LVL010): its IsTriggered (vt+0xc4) replaces the box test
    float m_afUnk80[7];         // +0x80
    // +0x9c not set by the constructor nor the Load. Its first byte (bits 24-31, signed): the box face the last
    // spherical constraint chose (CameraVolume_ComputeConstrainedSphericalPosition, 0..5; -1 none: set on entering).
    uint32_t m_unk9c;
};
DOTD_ASSERT_SIZE(CKCameraConstraint, 0xa0);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_afBox, +0x04);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk1c, +0x1c);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk20, +0x20);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk24, +0x24);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_tsUnk28, +0x28);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_tsUnk30, +0x30);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk38, +0x38);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk3c, +0x3c);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk40, +0x40);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_afUnk44, +0x44);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk74, +0x74);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk78, +0x78);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk7c, +0x7c);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_afUnk80, +0x80);
DOTD_ASSERT_OFFSET(CKCameraConstraint, m_unk9c, +0x9c);

// The camera volume functions (CKCameraConstraint.cpp; r3 / the first argument is the zone: its box +0x04..+0x18 and
// the shape bits +0x1c bits 3-4). The COLL family's (step 5).
// 0x001539d8 CameraVolume_ContainsPoint_maybe: the box / cylinder / sphere test of CKCameraConstraint::ContainsPoint
// without the detector group (called directly by CKCameraClassicTrack3::ConstrainFollowToVolume).
bool CameraVolume_ContainsPoint(const CKCameraConstraint* zone, const CVector3* point);
// 0x00155018 CameraVolume_ComputeNearestBoundaryPoint_maybe (r3 the returned point, r4 the zone, r5 / r6 two points):
// `to` brought into the volume shrunk by 0.001: box, the move from `from` scaled down to stay inside; cylinder, the
// height clamped along the move then the x/z offset cut to the radius; sphere, the centre plus (to - centre) times the
// radius (not normalised).
CVector3 CameraVolume_ComputeNearestBoundaryPoint(const CKCameraConstraint* zone, const CVector3* from, const CVector3* to);
// 0x00155440 CameraVolume_ComputeBoundaryPointForShapeBits_maybe (the same registers): box, `from` plus the move with
// each axis that leaves the box zeroed; cylinder, as the nearest point; sphere, the point of the sphere towards `to`.
CVector3 CameraVolume_ComputeBoundaryPointForShapeBits(const CKCameraConstraint* zone, const CVector3* from, const CVector3* to);

// 0x00156da8 CameraVolume_ComputeConstrainedSphericalPosition_maybe (the COLL family's, step 5; declared by CT3,
// whose UpdateBlending calls it at the end of a blend): the orbit position at (yaw, pitch, distance) from `focus`, kept
// inside the zone's volume; *constrained (r9) tells whether it was moved. r6..r8 are not used.
CVector3 CameraVolume_ComputeConstrainedSphericalPosition(float yaw, float pitch, float distance, CKCameraConstraint* zone,
                                                          const CVector3* focus, uint8_t* constrained);
