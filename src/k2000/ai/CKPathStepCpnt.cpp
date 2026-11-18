// CKPathStepCpnt.cpp - reconstructed original translation unit 0x59c668-0x59cb80 (GAME_TOC2, main_toc2), 16 functions, 14 live.
// Primary owner: CKPathStepCpnt (not a registered class)
// Other owners: FloatArray (1), RegisterCKPathStepCpntClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x59c668  CKPathStepCpnt_Destroy  (the Delete factory: DOTD_DECLARE_FACTORIES(CKPathStepCpnt))
//   [ ] 0x59c6b8  CKPathStepCpnt_Construct  [dead]
//   [ ] 0x59c6d0  CKPathStepCpnt_Construct_2  [dead]
//   [x] 0x59c6e8  CKPathStepCpnt_LevelReset  (RecursiveRegistration, vt+0x24)
//   [ ] 0x59c6f0  CKPathStepCpnt_Save
//   [x] 0x59c6f8  FloatArray_CountInRange_maybe  (CKPathStepCpnt::CountStepsInRange)
//   [ ] 0x59c758  RegisterCKPathStepCpntClass
//   [ ] 0x59c7d0  _GLOBAL__I_59c7d0
//   [x] 0x59c7e0  CKPathStepCpnt_Load
//   [x] 0x59c920  CKPathStepCpnt_ClearReferences  (Destroy, vt+0x10)
//   [x] 0x59c948  CKPathStepCpnt_DeletingDestructor  (the implicit destructor)
//   [x] 0x59c990  CKPathStepCpnt_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x59c9c0  CKPathStepCpnt_BaseDestructor  (the implicit destructor)
//   [x] 0x59c9f0  CKPathStepCpnt_DestroyArray  (the DeleteArray factory: DOTD_DECLARE_FACTORIES(CKPathStepCpnt))
//   [x] 0x59ca98  CKPathStepCpnt_Create
//   [x] 0x59cad8  CKPathStepCpnt_CreateArray
//
//   [ ] 0x9cb9d8  CKPathStepCpnt_IsKindOf  [inline]
//   [x] 0x9cba00  CKPathStepCpnt_GetClassGroup  [inline]
//   [x] 0x9cba08  CKPathStepCpnt_GetClassId  [inline]
#include "k2000/ai/CKPathStepCpnt.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0059c7e0 CKPathStepCpnt_Load
int32_t CKPathStepCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32Count);
    m_pSteps = static_cast<float*>(Mem_AllocAligned16(m_ui32Count * static_cast<uint32_t>(sizeof(float))));
    for (uint32_t i = 0; i < m_ui32Count; ++i) ReadF32LE(file, &m_pSteps[i]);
    return 1;
}

// 0x0059c920 CKPathStepCpnt_Destroy
void CKPathStepCpnt::Destroy() { Mem_FreeAligned16(m_pSteps); }

// 0x0059c6f8 FloatArray_CountInRange_maybe
uint32_t CKPathStepCpnt::CountStepsInRange(float lo, float hi) const {
    uint32_t count = 0;
    for (uint32_t i = 0; i < m_ui32Count; ++i) {
        const float step = m_pSteps[i];
        if (step >= lo && step < hi) ++count;  // fcmpu + cror (not less), then bge skips (not less than hi)
    }
    return count;
}
