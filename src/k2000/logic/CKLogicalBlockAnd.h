// CKLogicalBlockAnd.h - a logical block: its output anchor gets the AND of its two input anchors (key 0x654c, size 0x1c).
// Original unit: CKLogicalBlockAnd.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKLogicalBlock.h"

class CKLogicalBlockAnd : public CKLogicalBlock {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x195)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1c30
        return key == 0x654c || key == 0x640c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLogicalBlockAnd)

    // 0x0020e6f0 CKLogicalBlockAnd_Construct (0x0020e728 Construct_2, inlined in Create / CreateArray): the base and the vtable.
    CKLogicalBlockAnd() {}
    // 0x0020e690 CKLogicalBlockAnd_Destructor (0x0020e6c0 DestructBody, 0x0020e648 DeletingDestructor): the base's.
    ~CKLogicalBlockAnd() override {}

    // vt+0x2c 0x0020e5a8 CKLogicalBlockAnd_Load: the base's, 1. vt+0x24 0x0020e5f8 RecursiveRegistration and vt+0x10 0x0020e620
    // Destroy: the base's (nothing).
    int32_t Load(IKFile* file, int32_t type) override {
        CKLogicalBlock::Load(file, type);
        return 1;
    }
    // vt+0x64 0x9b1c78 CKLogicalBlockAnd_Evaluate: and; neg, bit 63: 1 when both are set (the argument unused); the output anchor's vt+0x58.
    void Evaluate(uint8_t /*value*/) override {
        m_pOutput->SetValue((m_pInputs[0]->m_unk08 & m_pInputs[1]->m_unk08) != 0 ? 1 : 0);
    }
};
