// CKBhvBlockAnimation.h - a behaviour block that plays an animation (DotD) (key 0x9d0c, vtable 0xb2fb40, size 0x44). Original unit: CKBhvBlockAnimation.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9C8C.h"
#include "k2000/math/CMatrix34.h"

class IKFile;

class CKBhvBlockAnimation : public KBase9C8C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x274)
    DOTD_DECLARE_FACTORIES(CKBhvBlockAnimation)

    // 0x005c2360 CKBhvBlockAnimation_Create: CKBhvBlockBase_maybe_Construct, then the vtable (CKBhvBlockAnimation_Construct 0x5c1e90).
    CKBhvBlockAnimation() {}
    ~CKBhvBlockAnimation() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c23b8 CKBhvBlockAnimation_Load

    IKSerializable* m_unk04;  // +0x04 read last
    IKSerializable* m_unk08;  // +0x08
    IKSerializable* m_unk0c;  // +0x0c
    IKSerializable* m_unk10;  // +0x10 CAnimationDictionary in the files; read first
    IKSerializable* m_unk14;  // +0x14
    uint8_t m_unk18;          // +0x18
    uint8_t m_unk19;          // +0x19
    uint8_t m_unk1a;          // +0x1a
    uint8_t m_pad1b;
    uint32_t m_unk1c;         // +0x1c
    uint32_t m_unk20;         // +0x20 not set by the constructor nor the Load
    uint8_t m_unk24;          // +0x24
    uint8_t m_pad25[3];
    IKSerializable* m_unk28;  // +0x28
    uint8_t m_unk2c;          // +0x2c
    uint8_t m_pad2d[3];
    CVector3 m_unk30;         // +0x30 one 0xc read, swapped
    uint8_t m_unk3c;          // +0x3c
    uint8_t m_pad3d[3];
    uint32_t m_unk40;         // +0x40
};
DOTD_ASSERT_SIZE(CKBhvBlockAnimation, 0x44);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk04, +0x04);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk08, +0x08);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk0c, +0x0c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk10, +0x10);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk14, +0x14);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk18, +0x18);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk19, +0x19);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk1a, +0x1a);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk1c, +0x1c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk20, +0x20);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk24, +0x24);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk28, +0x28);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk2c, +0x2c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk30, +0x30);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk3c, +0x3c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk40, +0x40);
