// CKProjectileDataTypeScrap.h - the launch parameters of a debris projectile (a component; key 0xa6cc,
// vtable 0xb2e370, size 0x48). Original unit: CKProjectileDataTypeScrap.cpp (0x591f58-0x5929d8). Base:
// IKComponent. Referenced by CKProjectileAccessor (+0x08). No XXL2 class of this name. Types from the
// LVL010 data (twelve floats, then a byte, a half-word, a word and three references).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKProjectileDataTypeScrap : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x29b)
    DOTD_DECLARE_FACTORIES(CKProjectileDataTypeScrap)

    // The constructor inlined in 0x005920e0 CKProjectileDataTypeScrap_Create: the vtable only.
    CKProjectileDataTypeScrap() {}
    ~CKProjectileDataTypeScrap() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00592328 CKProjectileDataTypeScrap_Load

    float m_unk04;            // +0x04 (samples: 15.0)
    float m_unk08;            // +0x08
    float m_unk0c;            // +0x0c
    float m_unk10;            // +0x10
    float m_unk14;            // +0x14
    float m_unk18;            // +0x18
    float m_unk1c;            // +0x1c
    float m_unk20;            // +0x20
    float m_unk24;            // +0x24
    float m_unk28;            // +0x28
    float m_unk2c;            // +0x2c (samples: -1.0)
    float m_unk30;            // +0x30
    uint8_t m_unk34;          // +0x34 (+0x35 padding)
    uint8_t m_pad35;
    uint16_t m_unk36;         // +0x36 (samples: 0xe300)
    uint32_t m_unk38;         // +0x38 (samples: 0xff000010)
    IKSerializable* m_unk3c;  // +0x3c a reference
    IKSerializable* m_unk40;  // +0x40 a reference
    IKSerializable* m_unk44;  // +0x44 a reference (read first of the three)
};
DOTD_ASSERT_SIZE(CKProjectileDataTypeScrap, 0x48);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk36, 0x36);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeScrap, m_unk44, 0x44);
