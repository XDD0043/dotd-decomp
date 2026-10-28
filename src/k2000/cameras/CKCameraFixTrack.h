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
    DOTD_DECLARE_FACTORIES(CKCameraFixTrack)

    // 0x0013c318 CKCameraFixTrack_Create: IKCamera_ConstructBase, then the vtable.
    CKCameraFixTrack() {}
    ~CKCameraFixTrack() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0013c528 CKCameraFixTrack_Load

    float m_fTargetHighOffset;  // +0x58
    float m_fRollAngle;         // +0x5c
};
DOTD_ASSERT_SIZE(CKCameraFixTrack, 0x60);
DOTD_ASSERT_OFFSET(CKCameraFixTrack, m_fTargetHighOffset, +0x58);
DOTD_ASSERT_OFFSET(CKCameraFixTrack, m_fRollAngle, +0x5c);
