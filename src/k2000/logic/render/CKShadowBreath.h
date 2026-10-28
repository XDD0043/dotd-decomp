// CKShadowBreath.h - Cynder's shadow breath (key 0xa90c, vtable 0xb24758, size 0x210). Original unit:
// CKShadowBreath.cpp. Base: CKBreathElement (0x914c), whose Load it calls first (the IsKindOfClass chain also
// names the ability base 0x90cc, outputs/ability-analysis/abilities.md). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBreathElement.h"

class CKShadowBreath : public CKBreathElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a4)
    DOTD_DECLARE_FACTORIES(CKShadowBreath)

    CKShadowBreath() {}  // 0x003d4428 CKShadowBreath_Construct: CKBreathElement, then the vtable
    ~CKShadowBreath() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d5518 CKShadowBreath_Load
    // vt+0x30 PostLoad 0x3d4308 (stays the default in C2.1).

    uint32_t m_unk178[10];     // +0x178 ten byte-swapped words, read one by one after the first references
    IKSerializable* m_unk1a0;  // +0x1a0 object references
    uint32_t m_unk1a4;         // +0x1a4 not read
    IKSerializable* m_unk1a8;  // +0x1a8
    IKSerializable* m_unk1ac;  // +0x1ac
    IKSerializable* m_unk1b0;  // +0x1b0
    uint32_t m_unk1b4;         // +0x1b4 not read
    IKSerializable* m_unk1b8;  // +0x1b8
    IKSerializable* m_unk1bc;  // +0x1bc
    IKSerializable* m_unk1c0;  // +0x1c0
    uint32_t m_unk1c4;         // +0x1c4 not read
    uint32_t m_unk1c8[3];      // +0x1c8 byte-swapped words (read last)
    IKSerializable* m_unk1d4;  // +0x1d4
    IKSerializable* m_unk1d8;  // +0x1d8
    uint32_t m_unk1dc;         // +0x1dc not read
    IKSerializable* m_unk1e0;  // +0x1e0
    IKSerializable* m_unk1e4;  // +0x1e4
    IKSerializable* m_unk1e8;  // +0x1e8
    IKSerializable* m_unk1ec;  // +0x1ec
    uint32_t m_unk1f0[5];      // +0x1f0 byte-swapped words
    uint32_t m_unk204[3];      // +0x204 not read
};
static_assert(CKShadowBreath::kClassKey == 0xa90c, "key");
DOTD_ASSERT_SIZE(CKShadowBreath, 0x210);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKShadowBreath, m_unk1f0, 0x1f0);
