// CKEnemySectorCpnt.h - the reference lists an enemy keeps per sector (key 0x386, vtable 0xb22528, size
// 0x28). Original unit: CKEnemySectorCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKEnemySectorCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0xe)
    DOTD_DECLARE_FACTORIES(CKEnemySectorCpnt)

    CKEnemySectorCpnt() {}  // 0x002b3470 CKEnemySectorCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002b35c0 CKEnemySectorCpnt_Load

    // Reference arrays (Mem_AllocAligned16 for their u8 counts; the counts are not stored). +0x04, +0x08
    // and +0x0c share one count, +0x20 and +0x24 another.
    IKSerializable** m_apUnk04;  // +0x04
    IKSerializable** m_apUnk08;  // +0x08
    IKSerializable** m_apUnk0c;  // +0x0c
    IKSerializable** m_apUnk10;  // +0x10
    IKSerializable** m_apUnk14;  // +0x14
    IKSerializable** m_apUnk18;  // +0x18
    IKSerializable* m_pUnk1c;    // +0x1c one reference
    IKSerializable** m_apUnk20;  // +0x20
    IKSerializable** m_apUnk24;  // +0x24
};
DOTD_ASSERT_SIZE(CKEnemySectorCpnt, 0x28);
DOTD_ASSERT_OFFSET(CKEnemySectorCpnt, m_apUnk04, 0x04);
DOTD_ASSERT_OFFSET(CKEnemySectorCpnt, m_pUnk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKEnemySectorCpnt, m_apUnk24, 0x24);
