// CKGrpS08TuningFork.cpp - reconstructed original translation unit 0x4cc920-0x4cdaa0 (GAME_TOC1, main_toc1), 29 functions, 25 live.
// Primary class: CKGrpS08TuningFork  key 0xcc4  category Group  size 0x38  vtable 0xb29968
// Other owners: CKHkS08TuningFork (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4cc920  CKGrpS08TuningFork_Delete
//   [ ] 0x4cc970  CKGrpS08TuningFork_Construct  [dead]
//   [ ] 0x4cc9e8  CKGrpS08TuningFork_vfB8
//   [ ] 0x4cc9f0  CKGrpS08TuningFork_Construct_2  [dead]
//   [ ] 0x4cca68  RegisterCKGrpS08TuningForkClass
//   [ ] 0x4ccae0  _GLOBAL__I_4ccae0
//   [x] 0x4ccaf0  CKGrpS08TuningFork_DeleteArray
//   [ ] 0x4ccb98  CKGrpS08TuningFork_ClearGroupSynced_maybe
//   [ ] 0x4ccbd8  CKGrpS08TuningFork_SyncGroupPhases_maybe
//   [ ] 0x4ccca8  CKGrpS08TuningFork_ClearGroupPendingFlagForFork_maybe
//   [ ] 0x4ccd48  CKGrpS08TuningFork_AreOtherForksVibrating_maybe
//   [ ] 0x4ccec8  CKGrpS08TuningFork_Update
//   [ ] 0x4cd158  CKGrpS08TuningFork_Pause
//   [ ] 0x4cd160  CKGrpS08TuningFork_Resume
//   [ ] 0x4cd168  CKGrpS08TuningFork_Start
//   [ ] 0x4cd228  CKGrpS08TuningFork_Restart
//   [ ] 0x4cd270  CKGrpS08TuningFork_Stop
//   [ ] 0x4cd278  CKGrpS08TuningFork_RecursiveRegistration
//   [ ] 0x4cd2a0  CKGrpS08TuningFork_Save
//   [x] 0x4cd2c8  CKGrpS08TuningFork_Load
//   [x] 0x4cd5e8  CKGrpS08TuningFork_CreateArray
//   [x] 0x4cd6e0  CKGrpS08TuningFork_Create
//   [ ] 0x4cd770  CKGrpS08TuningFork_Destroy
//   [ ] 0x4cd868  CKGrpS08TuningFork_Destructor_2  [dead]
//   [ ] 0x4cd8e8  CKGrpS08TuningFork_Destructor
//   [ ] 0x4cd968  CKGrpS08TuningFork_DeletingDestructor
//   [ ] 0x4cd9f0  CKHkS08TuningFork_Delete
//   [ ] 0x4cda40  CKHkS08TuningFork_State0_Idle_maybe
//   [ ] 0x4cda98  KStub_Nop_4cda98  [dead]
//
//   [x] 0x9c5ab8  CKGrpS08TuningFork_GetClassType  [inline]
//   [x] 0x9c5ac0  CKGrpS08TuningFork_GetClassID  [inline]
//   [ ] 0x9c5ac8  CKGrpS08TuningFork_vfCC  [inline]
//   [ ] 0x9c5b18  CKGrpS08TuningFork_vfB0  [inline]
//   [ ] 0x9c5b28  CKGrpS08TuningFork_vfB4  [inline]
//   [ ] 0x9c5b38  CKGrpS08TuningFork_vfBC  [inline]
//   [ ] 0x9c5be0  CKGrpS08TuningFork_vfE0  [inline]
//   [ ] 0x9c5be8  CKGrpS08TuningFork_vfE4  [inline]
//   [ ] 0x9c5bf0  CKGrpS08TuningFork_vfE8  [inline]
//   [ ] 0x9c5bf8  CKGrpS08TuningFork_vfD8  [inline]
//   [ ] 0x9c5c38  CKGrpS08TuningFork_vfDC  [inline]
//   [ ] 0x9c5cf8  CKGrpS08TuningFork_IsKindOfClass  [inline]
#include "Spyro2008/groups/CKGrpS08TuningFork.h"

#include "k2000/memory/Mem.h"

namespace {
// The inlined TVector push_back (grows by 1 when full).
template <class T>
void PushBack(TVector<T, 1>& vector, T value) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 1u;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock =
            static_cast<T*>(Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = value;
    ++vector.m_ui32NbUsedElt;
}
}  // namespace

// 0x004cd2c8 CKGrpS08TuningFork_Load
int32_t CKGrpS08TuningFork::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // A new one-element block (the old one is not freed); the count is left alone.
    m_vSets.m_ui32NbElt = 1;
    m_vSets.m_pBlock = static_cast<RefSet**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(RefSet*))));
    for (uint32_t i = 0; i < count; ++i) {
        RefSet* set = new RefSet;  // OperatorNew(0x10)
        set->m_vRefs.m_ui32NbElt = 1;
        set->m_vRefs.m_pBlock = nullptr;
        set->m_vRefs.m_ui32NbUsedElt = 0;
        set->m_vRefs.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
        uint32_t refs = 0;
        ReadU32LE(file, &refs);
        for (uint32_t k = 0; k < refs; ++k) {
            IKSerializable* ref = nullptr;
            IKFile_ReadRef(file, &ref);
            PushBack(set->m_vRefs, ref);
        }
        PushBack(m_vSets, set);
    }
    return 1;
}
