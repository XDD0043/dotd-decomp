// CKCameraFirstPersonTrack.h - a first-person camera at the focus, turned by the right stick (key 0x3c7, vtable
// 0xb1a798, size 0x70). Original unit: CKCameraFirstPersonTrack.cpp (0x1504c8-0x151140). XXL2: m_v3CameraDirection,
// m_fCameraYOffsetFromTargetedLeaf, m_fPlayerCtrl_LR_Speed, m_fPlayerCtrl_UD_Speed in the same order. No level file holds
// the class: nothing exercises it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"

class IKFile;

class CKCameraFirstPersonTrack : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0xf)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a7a08
        return key == 0x3c7 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraFirstPersonTrack)

    // 0x00150c00 CKCameraFirstPersonTrack_Create: IKCamera_ConstructBase, then the vtable.
    CKCameraFirstPersonTrack() {}
    ~CKCameraFirstPersonTrack() override {}  // 0x9a7a58 / 0x9a7a88 (inline)

    // vt+0x10 0x00150b30 CKCameraFirstPersonTrack_Destroy: CKCameraTrack_ClearReferences_BaseNop_maybe (empty): inherited.
    // vt+0x24 0x001505b0 CKCameraFirstPersonTrack_RecursiveRegistration: IKCamera's (0x144108), then 1: inherited.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00150de8 CKCameraFirstPersonTrack_Load

    void Start(const CVector3* startPosition) override;  // vt+0x50 0x00150f28 CKCameraFirstPersonTrack_Activate_maybe
    void Pause() override {}                              // vt+0x54 0x00150518 CKCameraFirstPersonTrack_vf54 (empty)
    void Stop() override;                                 // vt+0x58 0x00150b08 CKCameraFirstPersonTrack_Deactivate_maybe
    void Resume() override {}                             // vt+0x5c 0x00150520 CKCameraFirstPersonTrack_vf5C (empty)
    void Update(float frameTime) override;                // vt+0x60 0x00150c58 CKCameraFirstPersonTrack_Update
    uint8_t Vf70() const override { return 1; }           // vt+0x70 0x9a7a40
    uint8_t Vf98() const override { return 0; }           // vt+0x98 0x9a7a48
    uint8_t VfB0() const override { return 0; }           // vt+0xb0 0x9a7a50

    // 0x001505d8 CKCameraFirstPersonTrack_ApplyStickLook_maybe: the direction turned by the right stick (XXL2
    // ComputeMoveFromInputs): its x axis (directions 2 / 3) about y by m_fPlayerCtrl_LR_Speed degrees per second, its y
    // axis (0 / 1, inverted by the game manager's vt+0x1b0) up or down by m_fPlayerCtrl_UD_Speed degrees per second, the
    // pitch kept within 85 degrees of the horizontal; only while the camera service lets the player move the camera
    // (m_baTemporaryFlags 0x200000), which then gets 0x100000.
    void ApplyStickLook(float dt);

    CVector3 m_v3CameraDirection;              // +0x58
    float m_fCameraYOffsetFromTargetedLeaf;    // +0x64
    float m_fPlayerCtrl_LR_Speed;              // +0x68
    float m_fPlayerCtrl_UD_Speed;              // +0x6c
};
DOTD_ASSERT_SIZE(CKCameraFirstPersonTrack, 0x70);
DOTD_ASSERT_OFFSET(CKCameraFirstPersonTrack, m_v3CameraDirection, +0x58);
DOTD_ASSERT_OFFSET(CKCameraFirstPersonTrack, m_fCameraYOffsetFromTargetedLeaf, +0x64);
DOTD_ASSERT_OFFSET(CKCameraFirstPersonTrack, m_fPlayerCtrl_UD_Speed, +0x6c);
