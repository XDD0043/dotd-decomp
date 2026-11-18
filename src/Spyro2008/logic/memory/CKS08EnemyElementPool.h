// CKS08EnemyElementPool.h - a pool of CKS08EnemyElement objects (key 0x7a4c, vtable 0xb21ae0, size 0x24).
// Original unit: CKS08EnemyElementPool.cpp (0x26c918-0x26cfa0). No XXL2 class of this name.
// +0x04..+0x0c is an inlined growable array (data, capacity, count), as in CKSrvTrigger's named references.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08EnemyElement.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08EnemyElementPool : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e9)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7a4c || key == 0xc; }  // vt+0x08 0x9bbd90
    DOTD_DECLARE_FACTORIES(CKS08EnemyElementPool)

    // inlined in 0x0026ca10 CKS08EnemyElementPool_Create: the array empty with capacity 1 (no block yet).
    CKS08EnemyElementPool() {
        m_apElements = nullptr;
        m_capacity = 1;
        m_count = 0;
    }
    ~CKS08EnemyElementPool() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026cc60 CKS08EnemyElementPool_Load
    // vt+0x30 0x0026cc08 CKS08EnemyElementPool_PostLoad: every element free (+0x54 = 0), whatever the type; 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x0026cc00 (1) and vt+0x10 0x0026cc58 (nop): the IKSerializable defaults do the same.

    CKS08EnemyElement** m_apElements;  // +0x04 (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_capacity;               // +0x08
    uint32_t m_count;                  // +0x0c
    uint8_t m_unk10;                   // +0x10
    uint8_t m_pad11[3];
    int32_t m_unk14;                   // +0x14
    float m_unk18;                     // +0x18 (file: 70.0)
    float m_unk1c;                     // +0x1c (file: 0.1)
    IKSerializable* m_pConfig;         // +0x20 (file: CKS08AccessoryConfig references)
};
DOTD_ASSERT_SIZE(CKS08EnemyElementPool, 0x24);
DOTD_ASSERT_OFFSET(CKS08EnemyElementPool, m_apElements, 0x04);
DOTD_ASSERT_OFFSET(CKS08EnemyElementPool, m_capacity, 0x08);
DOTD_ASSERT_OFFSET(CKS08EnemyElementPool, m_count, 0x0c);
DOTD_ASSERT_OFFSET(CKS08EnemyElementPool, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08EnemyElementPool, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKS08EnemyElementPool, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKS08EnemyElementPool, m_pConfig, 0x20);
