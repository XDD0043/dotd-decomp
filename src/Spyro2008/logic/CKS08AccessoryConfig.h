// CKS08AccessoryConfig.h - the settings of an accessory (enemy armour part) type (key 0xa18c, vtable 0xb228a8,
// size 0x30). Original unit: CKS08AccessoryConfig.cpp (0x2c6d50-0x2c74d0). No XXL2 class of this name.
// Eleven words, all read by the Load. Referenced by CKS08AccessoryManager and CKS08EnemyElementPool.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08AccessoryConfig : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x286)
    DOTD_DECLARE_FACTORIES(CKS08AccessoryConfig)

    CKS08AccessoryConfig() {}  // 0x002c6da0 CKS08AccessoryConfig_Construct: the vtable only
    ~CKS08AccessoryConfig() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002c7108 CKS08AccessoryConfig_Load

    float m_unk04;    // +0x04 (file: 4.23, 4.5)
    float m_unk08;    // +0x08 (file: 80)
    float m_unk0c;    // +0x0c (file: 25.1, 12.6 = 8 pi, 4 pi)
    float m_unk10;    // +0x10
    float m_unk14;    // +0x14
    float m_unk18;    // +0x18 (file: 0.3)
    int32_t m_unk1c;  // +0x1c (file: 2, 3)
    float m_unk20;    // +0x20
    float m_unk24;    // +0x24 (file: 45)
    float m_unk28;    // +0x28 (file: 1250)
    float m_unk2c;    // +0x2c (file: 0.1)
};
DOTD_ASSERT_SIZE(CKS08AccessoryConfig, 0x30);
DOTD_ASSERT_OFFSET(CKS08AccessoryConfig, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKS08AccessoryConfig, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKS08AccessoryConfig, m_unk2c, 0x2c);
