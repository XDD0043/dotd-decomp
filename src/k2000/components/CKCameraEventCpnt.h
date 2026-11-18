// CKCameraEventCpnt.h - a camera to switch to, with a value (key 0x1246, vtable 0xb1ab10, size 0x18).
// Original unit: CKCameraEventCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKCameraEventCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x49)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a8bf8
        return key == 0x1246 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraEventCpnt)

    CKCameraEventCpnt() {}  // 0x00166020 CKCameraEventCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00166240 CKCameraEventCpnt_Load
    // vt+0x30 0x00166108 CKCameraEventCpnt_PostLoad: (type 0) the camera's fov (+0x18) kept in +0x14.
    int32_t PostLoad(int32_t type) override;

    // The scripted camera handle (Ghidra ScriptedCameraHandle_*: this component). 0x00165af8 _Reset_maybe: no activation
    // time (-1), not active, the camera's track reset (vt+0x6c).
    void Reset();
    // 0x00165a78 _SetPositionAndTarget_maybe: while active, the camera at `position` looking at position + `direction`,
    // its fov the kept one times `fovScale`.
    void SetPositionAndTarget(float fovScale, const CVector3* position, const CVector3* direction);
    // 0x00165eb8 _TryActivate_maybe: forced, or when the handle's delay (+0x08) since its last activation has passed (or
    // it never was) and the camera service lets a scripted camera start: Activate at the clock's time. 1 when activated.
    uint8_t TryActivate(const CVector3* position, const CVector3* direction, float fovScale, float blend, int32_t force);
    // 0x00165bd8 _Activate_maybe: active since `time`, in the service's camera owner list (+0xe14), the service switching
    // to the camera (+0x470) with the blend `blend` (+0x82c, mode 0), flags +0x46c bit 22 set and bits 4-5 cleared, the
    // active scripted camera; then placed (SetPositionAndTarget).
    void Activate(float fovScale, float blend, float time, const CVector3* position, const CVector3* direction);
    // 0x00166130 _Release_maybe: an active handle gives the camera its fov back, is no longer the active scripted camera
    // and leaves the owner list (the last entry moved into its place).
    void Release();

    IKSerializable* m_pCamera;  // +0x04 CKCamera (Ghidra type; LVL010 refs of key 0x47, category camera)
    float m_unk08;              // +0x08 (LVL010: 3, 1) _maybe a duration
    // +0x0c..+0x17 not set by the constructor or the Load (Reset / Activate / PostLoad).
    float m_fLastActivation;    // +0x0c the clock's time at the last activation, -1 after Reset
    uint8_t m_bActive;          // +0x10
    uint8_t m_pad11[3];
    float m_fBaseFov;           // +0x14 PostLoad: the camera's fov
};
DOTD_ASSERT_SIZE(CKCameraEventCpnt, 0x18);
DOTD_ASSERT_OFFSET(CKCameraEventCpnt, m_pCamera, 0x04);
DOTD_ASSERT_OFFSET(CKCameraEventCpnt, m_unk08, 0x08);
