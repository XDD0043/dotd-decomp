// CKHkMecaSound.h - a mechanism's sound hook (key 0x3482, vtable 0xb2a360, size 0x3c). Original unit:
// CKHkMecaSound.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkMecaSound : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd2)
    DOTD_DECLARE_FACTORIES(CKHkMecaSound)

    CKHkMecaSound() {}  // 0x004e0258 CKHkMecaSound_Create: the CKHkActorBase defaults only
    ~CKHkMecaSound() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e0600 CKHkMecaSound_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x004dfeb8 CKHkMecaSound_SetDefaultState
    void Start() override;                        // vt+0x50 0x004dff18 CKHkMecaSound_Start

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
