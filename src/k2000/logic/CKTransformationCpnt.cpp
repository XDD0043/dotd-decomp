// CKTransformationCpnt.cpp - reconstructed original translation unit 0x251628-0x2520c0 (GAME_TOC1, main_toc1), 19 functions, 14 live.
// Primary class: CKTransformationCpnt  key 0xa80c  category Logic  size 0x14  vtable 0xb210b0
// Other owners: CKTransformationCpntUpdater (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x251628  CKTransformationCpnt_Delete
//   [ ] 0x251678  CKTransformationCpnt_StartUpdater_maybe
//   [ ] 0x251698  CKTransformationCpnt_StopUpdater_maybe  [dead]
//   [ ] 0x2516b0  CKTransformationCpnt_PauseUpdater_maybe  [dead]
//   [ ] 0x2516c0  CKTransformationCpnt_ResumeUpdater_maybe  [dead]
//   [ ] 0x2516d0  RegisterCKTransformationCpntClass
//   [ ] 0x251748  _GLOBAL__I_251748
//   [ ] 0x251758  CKTransformationCpnt_Evaluate_maybe
//   [ ] 0x251af8  CKTransformationCpnt_EvaluateRunning_maybe  [dead]
//   [x] 0x251b58  CKTransformationCpnt_DeleteArray
//   [x] 0x251c00  CKTransformationCpnt_Create
//   [x] 0x251c50  CKTransformationCpnt_CreateArray
//   [ ] 0x251d18  CKTransformationCpnt_Save
//   [ ] 0x251d20  CKTransformationCpnt_PostLoad
//   [ ] 0x251d28  CKTransformationCpnt_RecursiveRegistration
//   [ ] 0x251d30  CKTransformationCpnt_Destroy
//   [x] 0x251d38  CKTransformationCpnt_Load
//   [ ] 0x252068  CKTransformationCpntUpdater_Delete
//   [ ] 0x2520b8  KStub_Nop_2520b8  [dead]
//
//   [ ] 0x9ba528  CKTransformationCpnt_IsKindOfClass  [inline]
//   [x] 0x9ba558  CKTransformationCpnt_GetClassType  [inline]
//   [x] 0x9ba560  CKTransformationCpnt_GetClassID  [inline]
//   [ ] 0x9ba568  CKTransformationCpnt_Destructor  [inline]
//   [ ] 0x9ba5c0  CKTransformationCpnt_DeletingDestructor  [inline]
#include "k2000/logic/CKTransformationCpnt.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00251c00 CKTransformationCpnt_Create, the inlined constructor: the entry list only.
CKTransformationCpnt::CKTransformationCpnt() {
    m_entries.m_pBlock = nullptr;
    m_entries.m_ui32NbElt = 1;
    m_entries.m_ui32NbUsedElt = 0;
}

// 0x00251d38 CKTransformationCpnt_Load
int32_t CKTransformationCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk04);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    m_entries.m_ui32NbElt = count;
    m_entries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Entry))));
    if (m_entries.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Entry));
        if (capacity == 0) {
            capacity = 1;
            bytes = static_cast<uint32_t>(sizeof(Entry));
        }
        m_entries.m_pBlock = static_cast<Entry*>(Mem_ReallocAligned16(m_entries.m_pBlock, bytes));
        m_entries.m_ui32NbElt = capacity;
    }
    m_entries.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Entry& entry = m_entries.m_pBlock[i];
        IKFile_ReadRef(file, &entry.m_pCurve);
        ReadU32LE(file, &entry.m_unk04);
        ReadF32LE(file, &entry.m_unk08);
        ReadF32LE(file, &entry.m_unk0c);
        ReadF32LE(file, &entry.m_unk10);
        ReadF32LE(file, &entry.m_unk14);
    }
    return 1;
}
