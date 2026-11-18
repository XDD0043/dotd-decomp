// CKLogicalBlockNor.h - a logical block: its output anchor gets the NOR of its two input anchors (key 0x64cc, size 0x1c).
// Original unit: CKLogicalBlockNor.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKLogicalBlock.h"

class CKLogicalBlockNor : public CKLogicalBlock {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x193)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1d80
        return key == 0x64cc || key == 0x640c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLogicalBlockNor)

    // 0x0020efc0 CKLogicalBlockNor_Construct (0x0020eff8 Construct_2, inlined in Create / CreateArray): the base and the vtable.
    CKLogicalBlockNor() {}
    // 0x0020ef60 CKLogicalBlockNor_Destructor (0x0020ef90 DestructBody, 0x0020ef18 DeletingDestructor): the base's.
    ~CKLogicalBlockNor() override {}

    // vt+0x2c 0x0020ee78 CKLogicalBlockNor_Load: the base's, 1. vt+0x24 0x0020eec8 RecursiveRegistration and vt+0x10 0x0020eef0
    // Destroy: the base's (nothing).
    int32_t Load(IKFile* file, int32_t type) override {
        CKLogicalBlock::Load(file, type);
        return 1;
    }
    // vt+0x64 0x9b1dc8 CKLogicalBlockNor_Evaluate: or; subi 1, bit 31: 1 when neither is set (the argument unused); the output anchor's vt+0x58.
    void Evaluate(uint8_t /*value*/) override {
        m_pOutput->SetValue((m_pInputs[0]->m_unk08 | m_pInputs[1]->m_unk08) == 0 ? 1 : 0);
    }
};
