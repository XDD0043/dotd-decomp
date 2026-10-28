// CKBhvBlockProjectiles.h - an NPC behaviour block that fires projectiles_maybe (key 0xa7cc, vtable 0xb2fc60,
// size 0x68). Original unit: CKBhvBlockProjectiles.cpp (0x5c3088-0x5c4e50). Base: KBase9C8C
// (CKBhvBlockBase_maybe). No XXL2 class of this name and no live struct draft: types from the file data.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9C8C.h"

class CKBhvBlockProjectiles : public KBase9C8C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x29f)
    DOTD_DECLARE_FACTORIES(CKBhvBlockProjectiles)

    CKBhvBlockProjectiles() {}  // 0x005c3aa8 CKBhvBlockProjectiles_Construct: the base, then the vtable
    ~CKBhvBlockProjectiles() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c4850 CKBhvBlockProjectiles_Load

    IKSerializable* m_unk04;  // +0x04
    IKSerializable* m_unk08;  // +0x08
    IKSerializable* m_unk0c;  // +0x0c (file: key 0x9ecc references, CKNPCBehaviourBlockUser)
    uint32_t m_unk10;         // +0x10
    uint32_t m_unk14;         // +0x14
    uint32_t m_unk18;         // +0x18 runtime
    uint32_t m_unk1c;         // +0x1c
    uint32_t m_unk20;         // +0x20
    uint32_t m_unk24;         // +0x24 runtime
    IKSerializable* m_unk28;  // +0x28 (file: key 0x2b4c references)
    IKSerializable* m_unk2c;  // +0x2c
    IKSerializable* m_unk30;  // +0x30
    uint32_t m_unk34;         // +0x34 runtime
    float m_unk38[3];         // +0x38 one 12-byte read, three swapped words (file: a unit direction)
    IKSerializable* m_unk44;  // +0x44
    uint32_t m_unk48[5];      // +0x48..+0x5b runtime
    IKSerializable* m_unk5c;  // +0x5c
    float m_unk60;            // +0x60 (file: 35.0)
    IKSerializable* m_unk64;  // +0x64 (file: key 0x96cc references, CKDamage)
};
DOTD_ASSERT_SIZE(CKBhvBlockProjectiles, 0x68);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk64, 0x64);
