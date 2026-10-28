// CKGolemPhaseQTE.h - a golem boss phase (key 0xa10c, vtable 0xb291d0, size 0x2c). Original unit:
// CKGolemPhaseQTE.cpp (0x4bddd8-0x4bed00). Derives from CKGolemPhaseBase (k2000/misc; its Load and
// constructor are called first). No XXL2 class of this name: the members keep placeholder names. Minimal for
// C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKGolemPhaseBase.h"

class CKGolemPhaseQTE : public CKGolemPhaseBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x284)
    DOTD_DECLARE_FACTORIES(CKGolemPhaseQTE)

    CKGolemPhaseQTE() {}  // 0x004be158 CKGolemPhaseQTE_Construct: the base constructor, then the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004be4c0 CKGolemPhaseQTE_Load

    IKSerializable* m_unk08;  // +0x08 object reference (file: key 0x18c2)
    uint8_t m_pad0c[0xc];     // +0x0c..+0x17 not read by the Load
    int32_t m_unk18;          // +0x18 (file: -1)
    int32_t m_unk1c;          // +0x1c (file: -1)
    int32_t m_unk20;          // +0x20 (file: -1)
    int32_t m_unk24;          // +0x24 (file: -1)
    int32_t m_unk28;          // +0x28 (file: 0)
};
DOTD_ASSERT_SIZE(CKGolemPhaseQTE, 0x2c);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk28, 0x28);
