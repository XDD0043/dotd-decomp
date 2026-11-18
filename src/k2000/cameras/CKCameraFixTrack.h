// CKCameraFixTrack.h - a fixed camera that tracks a target (key 0x187, vtable 0xb1a138, size 0x60). Original unit: CKCameraFixTrack.cpp.
// XXL2: the same members in the same load order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"

class IKFile;

class CKCameraFixTrack : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0x6)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a7470
        return key == 0x187 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraFixTrack)

    // 0x0013c318 CKCameraFixTrack_Create: IKCamera_ConstructBase, then the vtable.
    CKCameraFixTrack() {}
    ~CKCameraFixTrack() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0013c528 CKCameraFixTrack_Load
    // vt+0x24 0x0013c220 CKCameraFixTrack_RecursiveRegistration: IKCamera's (0x144108), then 1: inherited.
    // vt+0x10 0x0013c248 CKCameraFixTrack_Destroy: CKCameraTrack_ClearReferences_BaseNop_maybe (empty): inherited.

    // The runtime slots (P21). vt+0x50 0x0013c370 CKCameraFixTrack_Activate_maybe: the attached fx started, then the
    // target the camera service's focus (+0x484) raised by m_fTargetHighOffset.
    void Start(const CVector3* startPosition) override;
    void Pause() override {}   // vt+0x54 0x0013c160 CKCameraFixTrack_vf54 (empty)
    // vt+0x58 0x0013c1f8 CKCameraFixTrack_Deactivate_maybe: the attached fx stopped.
    void Stop() override;
    void Resume() override {}  // vt+0x5c 0x0013c168 CKCameraFixTrack_vf5C (empty)
    // vt+0x60 0x0013c3f0 CKCameraFixTrack_Update: IKCamera_UpdateTrackBase_maybe, then the target as in Start.
    void Update(float frameTime) override;

    float m_fTargetHighOffset;  // +0x58
    float m_fRollAngle;         // +0x5c
};
DOTD_ASSERT_SIZE(CKCameraFixTrack, 0x60);
DOTD_ASSERT_OFFSET(CKCameraFixTrack, m_fTargetHighOffset, +0x58);
DOTD_ASSERT_OFFSET(CKCameraFixTrack, m_fRollAngle, +0x5c);
