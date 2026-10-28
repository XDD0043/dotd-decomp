// CKHkLaunchQuakeCamera.h - a hook that launches a camera quake (key 0x2202, vtable 0xb1a928, size 0x2c).
// Original unit: CKHkLaunchQuakeCamera.cpp. Derives from IKHook directly. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"

class CKHkLaunchQuakeCamera : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x88)
    DOTD_DECLARE_FACTORIES(CKHkLaunchQuakeCamera)

    CKHkLaunchQuakeCamera() {}  // 0x00152e28 CKHkLaunchQuakeCamera_Create: the IKLife/IKHook defaults only
    ~CKHkLaunchQuakeCamera() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00152e90 CKHkLaunchQuakeCamera_Load
    // vt+0x1c 0x00152cf0 CKHkLaunchQuakeCamera_MessageProc (step 5, FX): message 0x600 starts the quake once
    // (CKSrvCamera_StartQuake_maybe with the launcher) and returns 0; the others return 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x50 0x00152cd8 CKHkLaunchQuakeCamera_Start / vt+0x54 0x00152a40 CKHkLaunchQuakeCamera_Restart: the active byte
    // (+0x29) from the loaded one (+0x28).
    void Start() override { m_bActive = m_bStartActive; }
    void Restart() override { m_bActive = m_bStartActive; }
    // vt+0x7c 0x00152ad8 CKHkLaunchQuakeCamera_Update: while active, the node's world matrix forced (vt+0x50) and the
    // quake started (every frame: a running quake is not started again until an effect of its group is idle).
    void Update(IKTime* frameClock) override;

    IKSerializable* m_unk20;  // +0x20 CSGLeaf* (struct draft), read last
    IKSerializable* m_unk24;  // +0x24 CKQuakeCameraLauncher* (struct draft)
    uint8_t m_bStartActive;   // +0x28 loaded: the active byte at Start / Restart
    uint8_t m_bActive;        // +0x29 Start / Restart copy +0x28
    uint8_t m_pad2a[2];
};
DOTD_ASSERT_SIZE(CKHkLaunchQuakeCamera, 0x2c);
DOTD_ASSERT_OFFSET(CKHkLaunchQuakeCamera, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkLaunchQuakeCamera, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkLaunchQuakeCamera, m_bStartActive, 0x28);
DOTD_ASSERT_OFFSET(CKHkLaunchQuakeCamera, m_bActive, 0x29);
