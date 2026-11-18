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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a71f8
        return key == 0x87 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraRigidTrack)

    // 0x0013a530 CKCameraRigidTrack_Create: IKCamera_ConstructBase, then the vtable.
    CKCameraRigidTrack() {}
    ~CKCameraRigidTrack() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0013a828 CKCameraRigidTrack_Load
    // vt+0x24 0x0013a418 CKCameraRigidTrack_RecursiveRegistration: IKCamera's (0x144108), then 1: inherited.
    // vt+0x10 0x0013a468 CKCameraRigidTrack_Destroy: CKCameraTrack_ClearReferences_BaseNop_maybe (empty): inherited.

    // The runtime slots (P21; CKCameraRigidTrack.cpp).
    void Start(const CVector3* startPosition) override;  // vt+0x50 0x0013a588 CKCameraRigidTrack_Activate_maybe
    void Pause() override {}                              // vt+0x54 0x0013a380 CKCameraRigidTrack_vf54 (empty)
    void Stop() override;                                 // vt+0x58 0x0013a440 CKCameraRigidTrack_Deactivate_maybe
    void Resume() override {}                             // vt+0x5c 0x0013a388 CKCameraRigidTrack_vf5C (empty)
    void Update(float frameTime) override;                // vt+0x60 0x0013a990 CKCameraRigidTrack_Update_maybe

    CVector3 m_offsetPosition;  // +0x58
    float m_unk64;              // +0x64
    float m_unk68;              // +0x68 _maybe XXL2 m_fHeightAboveGround
};
DOTD_ASSERT_SIZE(CKCameraRigidTrack, 0x6c);
DOTD_ASSERT_OFFSET(CKCameraRigidTrack, m_offsetPosition, +0x58);
DOTD_ASSERT_OFFSET(CKCameraRigidTrack, m_unk64, +0x64);
DOTD_ASSERT_OFFSET(CKCameraRigidTrack, m_unk68, +0x68);
