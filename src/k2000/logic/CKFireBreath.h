// CKFireBreath.h - the fire breath (key 0x924c, vtable 0xb23a48, size 0x1f0). Original unit: CKFireBreath.cpp
// (0x3a3240-0x3a5e60). Derives from CKBreathElement (its constructor and Load run first). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBreathElement.h"

class CKFireBreath : public CKBreathElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x249)
    DOTD_DECLARE_FACTORIES(CKFireBreath)

    CKFireBreath() {}  // 0x003a3408 CKFireBreath_Construct: CKBreathElement's constructor, then the vtable only
    ~CKFireBreath() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003a4288 CKFireBreath_Load

    float m_unk178[10];          // +0x178 (live: floats)
    IKSerializable* m_unk1a0;    // +0x1a0 reference (live: CKSparkFxData)
    uint32_t m_unk1a4;           // +0x1a4 (not loaded)
    IKSerializable* m_unk1a8[3]; // +0x1a8 references (live: heap objects)
    uint32_t m_unk1b4;           // +0x1b4 (not loaded)
    IKSerializable* m_unk1b8[3]; // +0x1b8 references (live: CKPointLightFxData)
    uint32_t m_unk1c4;           // +0x1c4 (not loaded)
    float m_unk1c8;              // +0x1c8
    float m_unk1cc;              // +0x1cc
    float m_unk1d0;              // +0x1d0
    IKSerializable* m_unk1d4;    // +0x1d4 reference (live: CKAnimatedFxCollection)
    IKSerializable* m_unk1d8;    // +0x1d8 reference (live: CKAnimatedFxCollection)
    uint32_t m_unk1dc;           // +0x1dc (not loaded)
    IKSerializable* m_unk1e0;    // +0x1e0 reference (live: CKSoundDictionaryID)
    IKSerializable* m_unk1e4;    // +0x1e4 reference (live: CKAimCamembert)
    uint32_t m_unk1e8;           // +0x1e8 (not loaded)
    uint32_t m_unk1ec;           // +0x1ec (not loaded)
};
DOTD_ASSERT_SIZE(CKFireBreath, 0x1f0);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKFireBreath, m_unk1e4, 0x1e4);
