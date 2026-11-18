// CKLogicalBlockOr.h - a logical block: its output anchor gets the OR of its two input anchors (key 0x648c, size 0x1c).
// Original unit: CKLogicalBlockOr.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKLogicalBlock.h"

class CKLogicalBlockOr : public CKLogicalBlock {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x192)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1e28
        return key == 0x648c || key == 0x640c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLogicalBlockOr)

    // 0x0020f428 CKLogicalBlockOr_Construct (0x0020f460 Construct_2, inlined in Create / CreateArray): the base and the vtable.
    CKLogicalBlockOr() {}
    // 0x0020f3c8 CKLogicalBlockOr_Destructor (0x0020f3f8 DestructBody, 0x0020f380 DeletingDestructor): the base's.
    ~CKLogicalBlockOr() override {}

    // vt+0x2c 0x0020f2e0 CKLogicalBlockOr_Load: the base's, 1. vt+0x24 0x0020f330 RecursiveRegistration and vt+0x10 0x0020f358
    // Destroy: the base's (nothing).
    int32_t Load(IKFile* file, int32_t type) override {
        CKLogicalBlock::Load(file, type);
        return 1;
    }
    // vt+0x64 0x9b1e70 CKLogicalBlockOr_Evaluate: or; neg, bit 63: 1 when either is set (the argument unused); the output anchor's vt+0x58.
    void Evaluate(uint8_t /*value*/) override {
        m_pOutput->SetValue((m_pInputs[0]->m_unk08 | m_pInputs[1]->m_unk08) != 0 ? 1 : 0);
    }
};
