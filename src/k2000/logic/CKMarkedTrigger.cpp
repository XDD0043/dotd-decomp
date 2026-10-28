// CKMarkedTrigger.cpp - reconstructed original translation unit 0x5d1748-0x5d2510 (GAME_TOC2, main_toc2), 26 functions, 19 live.
// Primary class: CKMarkedTrigger  key 0xb08c  category Logic  size ?  vtable 0xb30238
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5d1748  CKMarkedTrigger_Delete
//   [x] 0x5d1798  CKMarkedTrigger_Construct  [dead]
//   [ ] 0x5d17b8  KStub_Nop_5d17b8  [dead]
//   [ ] 0x5d17c0  KStub_Nop_5d17c0  [dead]
//   [ ] 0x5d17c8  KStub_Nop_5d17c8  [dead]
//   [ ] 0x5d17d0  KStub_Nop_5d17d0  [dead]
//   [ ] 0x5d17d8  KStub_Nop_5d17d8  [dead]
//   [ ] 0x5d17e0  CKMarkedTrigger_Construct_2  [dead]
//   [ ] 0x5d1800  RegisterCKMarkedTriggerClass
//   [ ] 0x5d1878  _GLOBAL__I_5d1878
//   [ ] 0x5d1888  CKMarkedTrigger_FireMatchingEntries_maybe
//   [x] 0x5d1948  CKMarkedTrigger_DeleteArray
//   [x] 0x5d19f0  CKMarkedTrigger_CreateArray
//   [x] 0x5d1aa8  CKMarkedTrigger_Create
//   [ ] 0x5d1af8  CKMarkedTrigger_GetInfo
//   [ ] 0x5d1b00  CKMarkedTrigger_Save
//   [ ] 0x5d1b08  CKMarkedTrigger_RecursiveRegistration
//   [ ] 0x5d1b10  CKMarkedTrigger_PostLoad
//   [ ] 0x5d1b90  CKMarkedTrigger_Destroy
//   [x] 0x5d1c10  CKMarkedTrigger_Load
//   [ ] 0x5d1f48  CKMarkedTrigger_FireMark_maybe
//   [ ] 0x5d2068  CKMarkedTrigger_UpdateFromAnimMarks_maybe
//   [ ] 0x5d23b8  CKMarkedTrigger_DeletingDestructor
//   [ ] 0x5d2438  CKMarkedTrigger_Destructor
//   [ ] 0x5d24a0  CKMarkedTrigger_Destructor_2
//   [ ] 0x5d2508  KStub_Return0_5d2508
//
//   [ ] 0x9cd6f0  CKMarkedTrigger_GetClassType  [inline]
//   [ ] 0x9cd6f8  CKMarkedTrigger_GetClassID  [inline]
//   [ ] 0x9cd700  CKMarkedTrigger_IsKindOfClass  [inline]
#include "k2000/logic/CKMarkedTrigger.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x005d1798 CKMarkedTrigger_Construct (also inlined in 0x005d1aa8 CKMarkedTrigger_Create).
CKMarkedTrigger::CKMarkedTrigger() {
    m_vMarks.m_pBlock = nullptr;
    m_vMarks.m_ui32NbUsedElt = 0;
    m_vMarks.m_ui32NbElt = 1;
}

// 0x005d1c10 CKMarkedTrigger_Load: a one-slot block, then each mark pushed back (grow by one).
int32_t CKMarkedTrigger::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vMarks.m_ui32NbElt = 1;
    m_vMarks.m_pBlock = static_cast<Mark**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Mark*))));
    for (uint32_t i = 0; i < count; ++i) {
        Mark* mark = static_cast<Mark*>(::operator new(sizeof(Mark)));  // OperatorNew(0x10)
        ReadU32LE(file, &mark->m_unk08);
        ReadU32LE(file, &mark->m_unk0c);
        mark->m_tsStarter.Load(file, K_LEVEL_PLATEFORMS);
        const uint32_t used = m_vMarks.m_ui32NbUsedElt;
        if (m_vMarks.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            if (capacity == 0) capacity = 1;
            m_vMarks.m_pBlock = static_cast<Mark**>(
                Mem_ReallocAligned16(m_vMarks.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Mark*))));
            m_vMarks.m_ui32NbElt = capacity;
        }
        m_vMarks.m_pBlock[m_vMarks.m_ui32NbUsedElt] = mark;
        m_vMarks.m_ui32NbUsedElt = m_vMarks.m_ui32NbUsedElt + 1;
    }
    IKFile_ReadRef(file, &m_unk10);
    IKFile_ReadRef(file, &m_unk14);
    ReadU32LE(file, &m_unk18);
    return 1;
}
