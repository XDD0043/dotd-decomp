// CKPathStepCpnt.h - a list of steps along a path (key 0x446, size 0xc, vtable at TOC2 -0x6b3c). Original
// unit: CKPathStepCpnt.cpp (0x59c668-0x59cb80). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKPathStepCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x11)
    DOTD_DECLARE_FACTORIES(CKPathStepCpnt)

    // 0x0059ca98 CKPathStepCpnt_Create (inlined constructor; 0x59c6b8 Construct is a dead copy): +0x04 = 0.
    CKPathStepCpnt() { m_pSteps = nullptr; }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0059c7e0 CKPathStepCpnt_Load

    float* m_pSteps;      // +0x04 Mem_AllocAligned16, count words byte-swapped (FloatArray_CountInRange_maybe
                          //   0x59c6f8 reads them as floats; LVL010's samples are empty)
    uint32_t m_ui32Count;  // +0x08
};
DOTD_ASSERT_SIZE(CKPathStepCpnt, 0xc);
DOTD_ASSERT_OFFSET(CKPathStepCpnt, m_pSteps, 0x04);
DOTD_ASSERT_OFFSET(CKPathStepCpnt, m_ui32Count, 0x08);
