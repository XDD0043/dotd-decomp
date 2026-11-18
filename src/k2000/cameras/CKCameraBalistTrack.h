// CKCameraBalistTrack.h - a camera fixed in the frame of the focused node (key 0x2c7, vtable 0xb1a6d8, size 0x70).
// Original unit: CKCameraBalistTrack.cpp (0x14f888-0x1502f0). XXL2 loads m_fAxisXOffset, m_fAxisYOffset, m_fAxisZOffset,
// m_fHeightAboveGround; DotD loads six floats (the names below follow what the code does with them). No level file holds
// the class: nothing exercises it.
//
// The target is the node's position + m_fTargetRight * its right axis + m_fTargetUp * its up axis, the position the
// target + m_fCameraAt * its at axis + m_fCameraRight * the modelling right + m_fCameraUp * the modelling up (the first
// three from the modelling matrix under a parent of class id 2, else from the stored LTM; all fused).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"

class IKFile;

class CKCameraBalistTrack : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0xb)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a7950
        return key == 0x2c7 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraBalistTrack)

    // 0x0014fab8 CKCameraBalistTrack_Create: IKCamera_ConstructBase, then the vtable.
    CKCameraBalistTrack() {}
    ~CKCameraBalistTrack() override {}  // 0x9a79d8 / 0x9a7990 (inline)

    // vt+0x10 0x0014f9e8 CKCameraBalistTrack_Destroy: CKCameraTrack_ClearReferences_BaseNop_maybe (empty): inherited.
    // vt+0x24 0x0014f998 CKCameraBalistTrack_RecursiveRegistration: IKCamera's (0x144108), then 1: inherited.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001500d0 CKCameraBalistTrack_Load
    // vt+0x30 0x0014f970 CKCameraBalistTrack_PostLoad: KStub_Return1_144570, then 1: IKSerializable's default (1).

    void Start(const CVector3* startPosition) override;  // vt+0x50 0x0014fb10 CKCameraBalistTrack_Activate_maybe
    void Pause() override {}                              // vt+0x54 0x0014f8d8 CKCameraBalistTrack_vf54 (empty)
    void Stop() override;                                 // vt+0x58 0x0014f9c0 CKCameraBalistTrack_Deactivate_maybe
    void Resume() override {}                             // vt+0x5c 0x0014f8e0 CKCameraBalistTrack_vf5C (empty)
    void Update(float frameTime) override;                // vt+0x60 0x0014fd78 CKCameraBalistTrack_Update
    float Vf80() const override { return m_fHeightAboveGround; }  // vt+0x80 0x9a7988: +0x6c

    // The pose shared by Start and Update.
    void PlaceInNodeFrame();

    float m_fTargetRight;        // +0x58
    float m_fTargetUp;           // +0x5c
    float m_fCameraAt;           // +0x60
    float m_fCameraRight;        // +0x64 (along the modelling right)
    float m_fCameraUp;           // +0x68 (along the modelling up)
    float m_fHeightAboveGround;  // +0x6c _maybe (vt+0x80; XXL2 m_fHeightAboveGround)
};
DOTD_ASSERT_SIZE(CKCameraBalistTrack, 0x70);
DOTD_ASSERT_OFFSET(CKCameraBalistTrack, m_fTargetRight, +0x58);
DOTD_ASSERT_OFFSET(CKCameraBalistTrack, m_fHeightAboveGround, +0x6c);
