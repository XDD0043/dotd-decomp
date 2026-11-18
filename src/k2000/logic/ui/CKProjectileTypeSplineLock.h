// CKProjectileTypeSplineLock.h - a projectile pool on Bezier curves (key 0x1d4c, vtable 0xb2e530, size 0x58): each
// projectile flies a cubic Bezier from its launch point (tangent: the launch direction times +0x40) to an end point (a
// fixed point, a locked target's aim point, or the world point under a screen point), reaching it after its duration
// (the distance over +0x3c with pool option 0x80000000, else +0x34 +- a random +0x38); the end tangent (+0x44) comes from
// the camera (a swirl at +0x4c degrees) for a screen point, the Y axis with option 0x40000000, else the side of the
// curve. Without a target it falls ballistically. Original unit: CKProjectileTypeSplineLock.cpp (0x597580-0x599ea8).
// Not in XXL2; names ours. No game file holds the class (C2.8 port-last Z4: read, not replayed).
//
// It keeps CKProjectileTypeBallisticPFX's MessageProc, LaunchEx, LaunchAtPoint(Ex) and GetProjectileAge slots; its
// Load replaces the base's 0x88-byte records with 0xd4-byte ones (Record).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"

class CKProjectileTypeSplineLock : public CKProjectileTypeBallisticPFX {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x75)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb760
        return key == 0x1d4c || key == 0x140c || key == 0x130c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileTypeSplineLock)

    // One projectile (0xd4 bytes): the base record, then the target and the curve. The Load sets what is noted.
    struct Record : Projectile {
        ProjectileTarget m_target;  // +0x88 the target, its hot spot, the hot spot index (Load 0); +0x90 / +0x98 unused
        uint8_t m_bTracking;        // +0x9c 1: the end point follows the target or the screen point; 0: m_vEndPoint (Load 1)
        uint8_t m_pad9d[3];
        CVector3 m_vEndPoint;       // +0xa0 the fixed end point; the screen point's last world point (Load (0, 0, 0))
        uint8_t m_bScreenPoint;     // +0xac the end is under m_afScreenPoint
        uint8_t m_padad[3];
        float m_afScreenPoint[2];   // +0xb0 the screen point (0..1)
        float m_fDuration;          // +0xb8 the time to the end point (Load 0)
        CVector3 m_vStart;          // +0xbc the launch point (Load (0, 0, 0))
        CVector3 m_vStartDir;       // +0xc8 the launch direction (Load the Y axis)
    };

    // The constructor inlined in 0x00597868 Create / 0x00597c00 CreateArray: IKProjectileType's (+0x18 = 8, +0x14 = 1),
    // then the vtables.
    CKProjectileTypeSplineLock() {}
    ~CKProjectileTypeSplineLock() override {}  // 0x009cb7a8 / 0x009cb7c8: the vtables only

    void Destroy() override;                            // vt+0x10 0x00599958: CKProjectileTypeBallisticPFX's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x005999b0: CKProjectileTypeBallisticPFX's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005999d8 CKProjectileTypeSplineLock_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00599988: the base's, then 1
    // (vt+0x28 0x599980 CKProjectileTypeSplineLock_Save returns 1.)

    void UpdateMotion(uint8_t index, float dt) override;       // vt+0x50 0x00599118
    void UpdateCollision(uint8_t index, float dt) override;    // vt+0x54 0x005977a0: the base's
    uint8_t IsDead(uint8_t index) override;                    // vt+0x58 0x00597988
    void OnDeath(uint8_t index) override;                      // vt+0x5c 0x00597778: the base's
    void KillProjectile(uint8_t index) override;               // vt+0x60 0x005978c0 CKProjectileTypeSplineLock_KillInstance
    void UpdateOrientation(uint8_t index, float dt) override;  // vt+0x64 0x00597e68: the base's
    uint8_t Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
                   const RwMatrix* matrix) override;           // vt+0x84 0x005975d0 (Ghidra _vf84)
    uint8_t LaunchAtTarget(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                           IKSerializable* owner, IKSerializable* target,
                           const RwMatrix* matrix) override;  // vt+0x8c 0x005983f8
    uint8_t LaunchAtTargetSpot(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                               IKSerializable* owner, const ProjectileTarget* target,
                               const RwMatrix* matrix) override;  // vt+0x94 0x00598778 (Ghidra _LaunchInstance_maybe)
    uint8_t LaunchAtScreenPoint(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                IKSerializable* owner, const float* screenPoint,
                                const RwMatrix* matrix) override;  // vt+0xa0 0x00599020 (Ghidra _vfA0)
    void ProcessDamageContacts(uint8_t index) override;        // vt+0xa4 0x00597a70
    void VfA8() override {}                                    // vt+0xa8 0x005976e8: empty
    // vt+0xb0 0x00598090 CKProjectileTypeSplineLock_LaunchAtPoint_maybe (a slot of its own): a projectile toward the
    // point `target` (copied); 1 when one was free.
    virtual uint8_t LaunchTowardPoint(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                      IKSerializable* owner, const CVector3* target, const RwMatrix* matrix);

    // 0x00597e90 _SpawnInstanceAtPoint_maybe / 0x00598190 _SpawnInstanceAtTarget_maybe / 0x005984e0 _SpawnInstance /
    // 0x00598cf8 _SpawnInstanceAtScreenPoint_maybe: the record's end set, its duration (from the distance to the end
    // with option 0x80000000, else one Rand_Int draw), the start and its direction kept, then the base's SpawnInstance
    // (no matrix, no damage object).
    void SpawnTowardPoint(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                          IKSerializable* owner, const CVector3* point);
    void SpawnAtTarget(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                       IKSerializable* owner, IKSerializable* target);
    void SpawnAtTargetSpot(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                           IKSerializable* owner, const ProjectileTarget* target);
    void SpawnAtScreenPoint(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                            IKSerializable* owner, const float* screenPoint);
    // 0x00598840 CKProjectileTypeSplineLock_ComputeSwirlOffset_maybe: cos(+0x4c deg) times the camera frame's right axis
    // plus its sine times the up axis.
    CVector3 ComputeSwirlOffset() const;
    // 0x00597cb8 ProjectWorldPointToNormalizedScreen_maybe: a point in front of the camera projected to the screen (0..1,
    // y up) with the scale +0x48 * +0x50 over its distance to the camera; 0 behind the camera. No caller in the
    // original (its descriptor is unreferenced).
    int32_t ProjectWorldPointToNormalizedScreen(const CVector3* point, float* screen, float* scale) const;

    float m_fDurationBase;    // +0x34 (Load, a word) the duration without option 0x80000000 ...
    float m_fDurationRandom;  // +0x38 ... plus or minus this, drawn
    float m_fCurveSpeed;      // +0x3c with option 0x80000000 the duration is the distance over this
    float m_fStartTangent;    // +0x40 the start tangent's length
    float m_fEndTangent;      // +0x44 the end tangent's length
    float m_fScreenDepth;     // +0x48 the depth of the screen points' plane in front of the camera
    float m_fSwirlAngle;      // +0x4c degrees: the screen points' end tangent round the camera axis
    float m_fScreenScale;     // +0x50 ProjectWorldPointToNormalizedScreen's scale factor
    float m_unk54;            // +0x54 (Load) not read in this unit
};
DOTD_ASSERT_SIZE(CKProjectileTypeSplineLock, 0x58);
DOTD_ASSERT_SIZE(CKProjectileTypeSplineLock::Record, 0xd4);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_target, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_bTracking, 0x9c);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_vEndPoint, 0xa0);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_bScreenPoint, 0xac);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_afScreenPoint, 0xb0);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_fDuration, 0xb8);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_vStart, 0xbc);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock::Record, m_vStartDir, 0xc8);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock, m_fDurationBase, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock, m_fScreenDepth, 0x48);
DOTD_ASSERT_OFFSET(CKProjectileTypeSplineLock, m_unk54, 0x54);
