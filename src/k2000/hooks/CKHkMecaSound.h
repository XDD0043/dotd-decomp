// CKHkMecaSound.h - a mechanism's sound hook (key 0x3482, vtable 0xb2a360, size 0x3c). Original unit:
// CKHkMecaSound.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class IKTime;

class CKHkMecaSound : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd2)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c62c0
        return key == 0x3482 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkMecaSound)

    CKHkMecaSound() {}  // 0x004e0258 CKHkMecaSound_Create: the CKHkActorBase defaults only
    ~CKHkMecaSound() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e0600 CKHkMecaSound_Load
    // vt+0x1c 0x004dfcf8 CKHkMecaSound_MessageProc: the actor base's answer merged (3 and 2 stay, 0 stays, else 1).
    int32_t MessageProc(uint16_t message, void* data) override {
        const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
        if (base == 3) return 3;
        if (base == 2) return 2;
        return base == 0 ? 0 : 1;
    }
    // vt+0x40 0x004dfd50 CKHkMecaSound_GetInfo: the actor base's answer (KStub_Return1 0x3f7140) merged.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override {
        const int32_t base = CKHkActorBase::GetInfo(info, request);
        if (base == 2) return 2;
        return base == 0 ? 0 : 1;
    }
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x004dfeb8 CKHkMecaSound_SetDefaultState
    void Start() override;                        // vt+0x50 0x004dff18 CKHkMecaSound_Start

    // vt+0xcc 0x004dfc68 CKHkMecaSound_vfCC: +0x38 = `enabled`.
    void SetEnabled(int32_t enabled) override { m_unk38 = static_cast<uint8_t>(enabled); }
    // vt+0xc8 0x004dfbb0 CKHkMecaSound_vfC8 (unit CKHkS08Fire.cpp): the state preset: +0x38 = !`state` (xori 1, stb).
    void ApplyStatePreset(int32_t state) override { m_unk38 = static_cast<uint8_t>(state ^ 1); }
    // vt+0x7c 0x004e02b0 CKHkMecaSound_Update: enabled (+0x38), the listener (the camera, or with +0x2c the focused
    // hero) within +0x28 of the path +0x24 plays sounds 0 and 1 at the path's closest point moved by +0x30 / +0x34 along
    // the path's side (its direction x the up axis) unless they play; else (or disabled) both stop.
    void Update(IKTime* frameClock) override;
    // vt+0xa4 0x004dfda0 CKHkMecaSound_OnDeactivate: the actor base's, then sounds 0 and 1 stopped.
    void VfA4() override;

    IKSerializable* m_unk20;  // +0x20 a sound dictionary_maybe (LVL010 references of class key 0x109)
    IKSerializable* m_unk24;  // +0x24 CKSpline4L* (Ghidra type)
    float m_unk28;            // +0x28
    uint8_t m_unk2C;          // +0x2c
    uint8_t m_pad2D[3];
    float m_unk30;            // +0x30
    float m_unk34;            // +0x34
    uint8_t m_unk38;          // +0x38 runtime (SetDefaultState: 1)
    uint8_t m_pad39[3];
};
DOTD_ASSERT_SIZE(CKHkMecaSound, 0x3c);
DOTD_ASSERT_OFFSET(CKHkMecaSound, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkMecaSound, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkMecaSound, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkMecaSound, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkMecaSound, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkMecaSound, m_unk34, 0x34);
