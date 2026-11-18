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

    // 0x0059c990 CKPathStepCpnt_Destructor / 0x0059c9c0 (Ghidra CKPathStepCpnt_BaseDestructor) / 0x0059c948
    // CKPathStepCpnt_DeletingDestructor: the vtables only (the steps are freed by Destroy).
    ~CKPathStepCpnt() override {}

    // vt+0x10 0x0059c920 CKPathStepCpnt_Destroy (row name ClearReferences): the steps freed (Mem_FreeAligned16), the
    // pointer left as it is.
    void Destroy() override;
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x0059c6e8 (returns 1; row name LevelReset)
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0059c7e0 CKPathStepCpnt_Load
    // 0x0059c6f8 FloatArray_CountInRange_maybe: the number of steps s with lo <= s < hi (NaN counts nowhere). Its one
    // caller, CKHkMovableCharacter_MoveAlongPath_maybe 0x5a4998 (k2000/ui/CKHkMovableCharacter.cpp), is not ported yet.
    uint32_t CountStepsInRange(float lo, float hi) const;

    float* m_pSteps;      // +0x04 Mem_AllocAligned16, count words byte-swapped (FloatArray_CountInRange_maybe
                          //   0x59c6f8 reads them as floats; LVL010's samples are empty)
    uint32_t m_ui32Count;  // +0x08
};
DOTD_ASSERT_SIZE(CKPathStepCpnt, 0xc);
DOTD_ASSERT_OFFSET(CKPathStepCpnt, m_pSteps, 0x04);
DOTD_ASSERT_OFFSET(CKPathStepCpnt, m_ui32Count, 0x08);
