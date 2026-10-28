// CKCameraRigidTrack.h - a camera rigidly attached to its target (key 0x87, vtable 0xb19fb8, size 0x6c). Original unit: CKCameraRigidTrack.cpp.
// XXL2: m_offsetPosition, m_offsetTarget, m_fHeightAboveGround; DotD loads a vector and two words.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"

class IKFile;

class CKCameraRigidTrack : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0x2)
    DOTD_DECLARE_FACTORIES(CKCameraRigidTrack)

    // 0x0013a530 CKCameraRigidTrack_Create: IKCamera_ConstructBase, then the vtable.
    CKCameraRigidTrack() {}
    ~CKCameraRigidTrack() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0013a828 CKCameraRigidTrack_Load

    CVector3 m_offsetPosition;  // +0x58
    float m_unk64;              // +0x64
    float m_unk68;              // +0x68 _maybe XXL2 m_fHeightAboveGround
};
DOTD_ASSERT_SIZE(CKCameraRigidTrack, 0x6c);
DOTD_ASSERT_OFFSET(CKCameraRigidTrack, m_offsetPosition, +0x58);
DOTD_ASSERT_OFFSET(CKCameraRigidTrack, m_unk64, +0x64);
DOTD_ASSERT_OFFSET(CKCameraRigidTrack, m_unk68, +0x68);
