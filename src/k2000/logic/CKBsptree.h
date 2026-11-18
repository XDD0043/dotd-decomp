// CKBsptree.h - a BSP tree (key 0x770c, vtable 0xb14c50, size 0x24). Original unit: CKBsptree.cpp (0x43480-0x43948).
// Derived straight from IKSerializable. No XXL2 class of this name; no level of DotD holds one (level-class-keys.json).
// The members keep placeholder names.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKBsptree : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1dc)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x770c || key == 0xc; }  // vt+0x08 0x9957d0
    DOTD_DECLARE_FACTORIES(CKBsptree)

    // 0x000436b8 CKBsptree_Create / 0x00043620 CreateArray: the vtable only.
    CKBsptree() {}
    // 0x00043918 CKBsptree_Destructor / 0x000438d8 DeletingDestructor: vtable stores only (operator delete).
    ~CKBsptree() override {}
    // vt+0x2c 0x00043708 CKBsptree_Load: for type 0 a reference and four words (+0x10..+0x1b are not read).
    // (vt+0x24 0x000436f8 RecursiveRegistration returns 1; vt+0x10 0x00043700 Destroy is empty.)
    int32_t Load(IKFile* file, int32_t type) override;

    IKSerializable* m_unk04;  // +0x04 a reference
    uint32_t m_unk08;         // +0x08
    uint32_t m_unk0c;         // +0x0c
    uint32_t m_unk10[3];      // +0x10 (not loaded)
    uint32_t m_unk1c;         // +0x1c
    uint32_t m_unk20;         // +0x20
};
DOTD_ASSERT_SIZE(CKBsptree, 0x24);
DOTD_ASSERT_OFFSET(CKBsptree, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKBsptree, m_unk1c, 0x1c);
