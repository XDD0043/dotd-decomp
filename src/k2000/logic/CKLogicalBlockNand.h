// CKLogicalBlockNand.h - a logical block: its output anchor gets the NAND of its two input anchors (key 0x650c, size 0x1c).
// Original unit: CKLogicalBlockNand.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKLogicalBlock.h"

class CKLogicalBlockNand : public CKLogicalBlock {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x194)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1cd8
        return key == 0x650c || key == 0x640c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLogicalBlockNand)

    // 0x0020eb58 CKLogicalBlockNand_Construct (0x0020eb90 Construct_2, inlined in Create / CreateArray): the base and the vtable.
    CKLogicalBlockNand() {}
    // 0x0020eaf8 CKLogicalBlockNand_Destructor (0x0020eb28 DestructBody, 0x0020eab0 DeletingDestructor): the base's.
    ~CKLogicalBlockNand() override {}

    // vt+0x2c 0x0020ea10 CKLogicalBlockNand_Load: the base's, 1. vt+0x24 0x0020ea60 RecursiveRegistration and vt+0x10 0x0020ea88
    // Destroy: the base's (nothing).
    int32_t Load(IKFile* file, int32_t type) override {
        CKLogicalBlock::Load(file, type);
        return 1;
    }
    // vt+0x64 0x9b1d20 CKLogicalBlockNand_Evaluate: and; subi 1, bit 31: 1 unless both are set (the argument unused); the output anchor's vt+0x58.
    void Evaluate(uint8_t /*value*/) override {
        m_pOutput->SetValue((m_pInputs[0]->m_unk08 & m_pInputs[1]->m_unk08) == 0 ? 1 : 0);
    }
};
