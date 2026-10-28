// CKShadowSurprise.h - Cynder's shadow surprise (key 0xa4cc, vtable 0xb247f0, size 0x274). Original unit:
// CKShadowSurprise.cpp. Base: CKTransformElement (0x954c), whose Load it calls first. Not in XXL2; names ours.
// The per-level arrays (three entries) follow the base's convention: indexed by the element's upgrade level.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/math/CMatrix34.h"

class CKShadowSurprise : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x293)
    DOTD_DECLARE_FACTORIES(CKShadowSurprise)

    CKShadowSurprise() {}  // 0x003d7ee0 CKShadowSurprise_Construct: CKTransformElement, then the vtable
    ~CKShadowSurprise() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d8ef8 CKShadowSurprise_Load
    int32_t PostLoad(int32_t type) override;           // vt+0x30 0x003d7e40 CKShadowSurprise_PostLoad
    uint8_t GetAbilityId() override { return 0xe; }    // vt+0x50 0x003d7550 CKShadowSurprise_GetAbilityId
    void ResetRuntime() override;                      // vt+0x6c 0x003d7d70 CKShadowSurprise_ResetRuntime

    float m_unk154[3];         // +0x154 per level
    uint32_t m_unk160[3];      // +0x160 per level
    uint32_t m_unk16c[3];      // +0x16c per level
    uint32_t m_unk178[3];      // +0x178 per level
    float m_unk184[3];         // +0x184 per level
    float m_unk190[3];         // +0x190 per level
    float m_unk19c[3];         // +0x19c per level
    CVector3 m_unk1a8[3];      // +0x1a8 per level, one 12-byte read each
    float m_unk1cc;            // +0x1cc
    float m_unk1d0;            // +0x1d0
    IKSerializable* m_unk1d4;  // +0x1d4 object references
    IKSerializable* m_unk1d8;  // +0x1d8
    IKSerializable* m_unk1dc;  // +0x1dc
    IKSerializable* m_unk1e0;  // +0x1e0
    IKSerializable* m_unk1e4;  // +0x1e4
    uint32_t m_unk1e8;         // +0x1e8 not read
    IKSerializable* m_unk1ec;  // +0x1ec
    IKSerializable* m_unk1f0;  // +0x1f0
    IKSerializable* m_unk1f4;  // +0x1f4
    uint32_t m_unk1f8;         // +0x1f8 not read
    IKSerializable* m_unk1fc;  // +0x1fc
    IKSerializable* m_unk200;  // +0x200
    IKSerializable* m_unk204;  // +0x204
    uint32_t m_unk208;         // +0x208 not read
    IKSerializable* m_unk20c;  // +0x20c
    IKSerializable* m_unk210;  // +0x210
    IKSerializable* m_unk214;  // +0x214
    IKSerializable* m_unk218;  // +0x218
    IKSerializable* m_unk21c;  // +0x21c
    IKSerializable* m_unk220;  // +0x220
    IKSerializable* m_unk224;  // +0x224
    IKSerializable* m_unk228;  // +0x228
    IKSerializable* m_unk22c;  // +0x22c
    IKSerializable* m_unk230;  // +0x230 (Ghidra draft: CKS08ElementDamage*)
    float m_unk234[6];         // +0x234
    IKSerializable* m_unk24c;  // +0x24c (Ghidra draft: CKSoundDictionaryID*)
    float m_unk250;            // +0x250
    float m_unk254;            // +0x254 not read; ResetRuntime sets it 1.0f (TOC +0x4118)
    uint32_t m_unk258;         // +0x258 ResetRuntime 0
    uint32_t m_unk25c;         // +0x25c ResetRuntime 0
    uint32_t m_unk260;         // +0x260 ResetRuntime 0
    uint8_t m_unk264;          // +0x264 ResetRuntime 0
    uint8_t m_pad265[3];
    uint32_t m_unk268;         // +0x268 never written (heap leftovers live)
    uint32_t m_unk26c;         // +0x26c ResetRuntime 0
    uint32_t m_unk270;         // +0x270 ResetRuntime 0
};
static_assert(CKShadowSurprise::kClassKey == 0xa4cc, "key");
DOTD_ASSERT_SIZE(CKShadowSurprise, 0x274);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk250, 0x250);
