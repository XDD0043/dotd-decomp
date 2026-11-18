// CKLogicalBlockXor.h - a logical block: its output anchor gets the XOR of its two input anchors (key 0x644c, size 0x1c).
// Original unit: CKLogicalBlockXor.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKLogicalBlock.h"

class CKLogicalBlockXor : public CKLogicalBlock {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x191)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1ed0
        return key == 0x644c || key == 0x640c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLogicalBlockXor)

    // 0x0020f890 CKLogicalBlockXor_Construct (0x0020f8c8 Construct_2, inlined in Create / CreateArray): the base and the vtable.
    CKLogicalBlockXor() {}
    // 0x0020f830 CKLogicalBlockXor_Destructor (0x0020f860 DestructBody, 0x0020f7e8 DeletingDestructor): the base's.
    ~CKLogicalBlockXor() override {}

    // vt+0x2c 0x0020f748 CKLogicalBlockXor_Load: the base's, 1. vt+0x24 0x0020f798 RecursiveRegistration and vt+0x10 0x0020f7c0
    // Destroy: the base's (nothing).
    int32_t Load(IKFile* file, int32_t type) override {
        CKLogicalBlock::Load(file, type);
        return 1;
    }
    // vt+0x64 0x9b1f18 CKLogicalBlockXor_Evaluate: xor; neg, bit 63: 1 when they differ (the argument unused); the output anchor's vt+0x58.
    void Evaluate(uint8_t /*value*/) override {
        m_pOutput->SetValue((m_pInputs[0]->m_unk08 ^ m_pInputs[1]->m_unk08) != 0 ? 1 : 0);
    }
};
