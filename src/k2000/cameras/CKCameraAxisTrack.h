// CKCameraAxisTrack.h - a camera that keeps its target between itself and an axis object (key 0x1c7, vtable 0xb1a1f8,
// size 0x98). Original unit: CKCameraAxisTrack.cpp (0x13c700-0x13d8c8). XXL2: m_fTargetHighOffset, m_fCameraHighOffset,
// m_fCameraTargetDistance, m_fHeightAboveGround, m_pAxis (and m_bAxisIsLeaf, here a type word) in the same load order;
// DotD adds the yaw approach. No level file holds the class: nothing exercises it.
//
// The camera looks at the service's focus (raised by m_fTargetHighOffset) from m_fCameraTargetDistance away, on the side
// opposite the axis point: its yaw (from +z) approaches the yaw of focus - axis point (Math_ApproachAngleWithAccelDecel).
// The axis point by m_eAxisType: 0 the axis node's LTM position (a CSGMovable), 2 the point of the axis path nearest the
// focus (an IKPath), 1 a vector of an object of a class no level file shows (not mapped).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"

class IKFile;

class CKCameraAxisTrack : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0x7)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a7528
        return key == 0x1c7 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraAxisTrack)

    // The state of Math_ApproachAngleWithAccelDecel (k2000/misc/FloatApproach.h; 7 floats).
    struct SYawApproach {
        float m_accel;       // +0x00
        float m_decel;       // +0x04
        float m_maxSpeed;    // +0x08
        float m_current;     // +0x0c
        float m_speed;       // +0x10
        float m_target;      // +0x14
        float m_speedBonus;  // +0x18
        float* Data() { return &m_accel; }
    };

    // 0x0013c988 CKCameraAxisTrack_Create: IKCamera_ConstructBase, then the vtable.
    CKCameraAxisTrack() {}
    ~CKCameraAxisTrack() override {}  // 0x9a7570 / 0x9a75a0 (inline): the vtable, then IKCamera's

    // vt+0x10 0x0013c8c0 CKCameraAxisTrack_Destroy: CKCameraTrack_ClearReferences_BaseNop_maybe (empty): inherited.
    // vt+0x24 0x0013c810 CKCameraAxisTrack_RecursiveRegistration: IKCamera's, then for axis types 1 and 2 the axis's.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0013ca90 CKCameraAxisTrack_Load

    void Start(const CVector3* startPosition) override;  // vt+0x50 0x0013d4b8 CKCameraAxisTrack_Activate_maybe
    void Pause() override {}                              // vt+0x54 0x0013c750 CKCameraAxisTrack_vf54 (empty)
    void Stop() override;                                 // vt+0x58 0x0013c7e8 CKCameraAxisTrack_Deactivate_maybe
    void Resume() override {}                             // vt+0x5c 0x0013c758 CKCameraAxisTrack_vf5C (empty)
    void Update(float frameTime) override;                // vt+0x60 0x0013d058 CKCameraAxisTrack_Update_maybe
    float Vf80() const override { return m_fHeightAboveGround; }  // vt+0x80 0x9a7568 (XXL2 GetAboveGroundHeight)
    uint8_t VfB4() const override { return 1; }                   // vt+0xb4 0x9a7560

    // The focus copied into the target, then the axis point by the type (both slots read it the same way); type 1 is not
    // mapped and other values leave `point` as it is (the original's uninitialised stack).
    void ComputeAxisPoint(CVector3* point);

    float m_fTargetHighOffset;      // +0x58
    float m_fCameraHighOffset;      // +0x5c
    float m_fCameraTargetDistance;  // +0x60
    float m_fHeightAboveGround;     // +0x64 (vt+0x80)
    float m_fYawMaxSpeed;           // +0x68 the yaw approach's top speed (Start copies it)
    float m_fYawAccel;              // +0x6c
    float m_fYawDecel;              // +0x70
    IKSerializable* m_pAxis;        // +0x74 a reference (XXL2 m_pAxis)
    uint32_t m_eAxisType;           // +0x78 0 node, 1 (unknown), 2 path (XXL2 m_bAxisIsLeaf)
    SYawApproach m_yaw;             // +0x7c Start: zero, then the three parameters and the current / target yaw
};
DOTD_ASSERT_SIZE(CKCameraAxisTrack, 0x98);
DOTD_ASSERT_OFFSET(CKCameraAxisTrack, m_fTargetHighOffset, +0x58);
DOTD_ASSERT_OFFSET(CKCameraAxisTrack, m_fYawDecel, +0x70);
DOTD_ASSERT_OFFSET(CKCameraAxisTrack, m_pAxis, +0x74);
DOTD_ASSERT_OFFSET(CKCameraAxisTrack, m_eAxisType, +0x78);
DOTD_ASSERT_OFFSET(CKCameraAxisTrack, m_yaw, +0x7c);
