// CKAnimatedCamera.h - an animated camera (DotD; not in XXL2) (key 0x9c4c, vtable 0xb2fa60, size 0x20). Original unit: CKAnimatedCamera.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"

class CKAnimatedCameraData;
class CSGBranch;
class IKFile;

class CKAnimatedCamera : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x271)
    DOTD_DECLARE_FACTORIES(CKAnimatedCamera)

    // 0x005c00e8 CKAnimatedCamera_Create: the vtable only (as the dead CKAnimatedCamera_Construct 0x5bf928).
    CKAnimatedCamera() {}
    ~CKAnimatedCamera() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c0178 CKAnimatedCamera_Load
    // vt+0x30 0x005c0128 CKAnimatedCamera_PostLoad: Reset (vt+0x5c), 1.
    int32_t PostLoad(int32_t type) override;

    // The runtime (step 5, FX). The camera is a CAnimatedNode (+0x08) playing an animation of the dictionary
    // (+0x04) whose hot spot (+0x0c) gives the scripted camera handle (+0x10, a CKCameraEventCpnt) its pose.
    // vt+0x50 0x005bfd10 CKAnimatedCamera_Start_maybe: when idle, an animation picked by `data` (vf50) is played from
    // `start` with the node moved under `parent` (vt+0x70; out of its old parent first, vt+0x78), turned about its
    // position to the camera's real heading when the entry asks for it (vf5C), else reset to the identity; the handle
    // reset, the camera active, its speed and +0x1c the entry's. 1 when it started.
    virtual uint8_t Start(float start, CKAnimatedCameraData* data, CSGBranch* parent);
    // vt+0x54 0x005bfad8 CKAnimatedCamera_Update_maybe: while active, the hot spot's pose to the handle (activated first
    // unless it already is; a refused activation ends the camera), the animation advanced by dt x speed; past the
    // animation's duration the handle is released and the camera ends. 1 while it runs.
    virtual uint8_t Update(float dt);
    // vt+0x58 0x005bffe8 CKAnimatedCamera_End_maybe: an active camera ends (the handle released when it was activated here).
    virtual void End();
    // vt+0x5c 0x005bf948 CKAnimatedCamera_Reset_maybe: inactive, speed 1, +0x1c 0.2.
    virtual void Reset();
    // vt+0x60 0x005bf9f0 CKAnimatedCamera_PlayAnim_maybe: the node plays the dictionary's animation `index` from `start`.
    virtual void PlayAnim(float start, uint32_t index);

    // +0x04 the animation dictionary (CAnimationDictionary), +0x08 the node (CAnimatedNode), +0x0c the hot spot
    // (CSGHotSpot), +0x10 the scripted camera handle (CKCameraEventCpnt): the Ghidra types of the uses (_maybe).
    IKSerializable* m_apUnk04[4];  // +0x04 four references
    uint8_t m_bActive;             // +0x14 Start 1, the end 0 (not set by the constructor nor the Load)
    uint8_t m_pad15[3];
    float m_fSpeed;                // +0x18 the animation speed (Reset 1.0)
    float m_fUnk1c;                // +0x1c the entry's +0x74 (Reset 0.2); read by nothing here
};
DOTD_ASSERT_SIZE(CKAnimatedCamera, 0x20);
DOTD_ASSERT_OFFSET(CKAnimatedCamera, m_apUnk04, +0x04);
DOTD_ASSERT_OFFSET(CKAnimatedCamera, m_bActive, +0x14);
DOTD_ASSERT_OFFSET(CKAnimatedCamera, m_fSpeed, +0x18);
DOTD_ASSERT_OFFSET(CKAnimatedCamera, m_fUnk1c, +0x1c);
