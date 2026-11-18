// CKColossusSequenceManager.cpp - reconstructed original translation unit: 0x46b0c8-0x46bd08 (GAME_TOC1, main_toc1), 26 functions, 19 live.
// Primary class: CKColossusSequenceManager  key 0x7c4c  category Logic  size 0x1c  vtable 0xb27408
// Other owners: ColossusAttackSequencer (4), CKHkColossus (1), CKColossusAttackSequence (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x46b0c8  CKColossusSequenceManager_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x46b118  CKColossusSequenceManager_Construct  [dead]
//   [ ] 0x46b138  CKColossusSequenceManager_Construct_2  [dead]
//   [ ] 0x46b158  RegisterCKColossusSequenceManagerClass
//   [ ] 0x46b1d0  _GLOBAL__I_46b1d0
//   [x] 0x46b1e0  CKColossusSequenceManager_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x46b288  ColossusAttackSequencer_StopCurrent_maybe  (StopCurrent)
//   [x] 0x46b308  ColossusAttackSequencer_Reset_maybe  (Reset)
//   [x] 0x46b368  ColossusAttackSequencer_Update_maybe  (Update)
//   [x] 0x46b568  CKColossusSequenceManager_PostLoad
//   [ ] 0x46b5e0  CKColossusSequenceManager_GetSequenceByIndex_maybe  [dead]
//   [x] 0x46b620  ColossusAttackSequencer_SwitchToSequence_maybe  (SwitchToSequence)
//   [x] 0x46b720  CKColossusSequenceManager_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x46b7d8  CKColossusSequenceManager_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [ ] 0x46b828  CKColossusSequenceManager_Save
//   [x] 0x46b830  CKColossusSequenceManager_Load
//   [x] 0x46b9d8  CKColossusSequenceManager_RecursiveRegistration  (CKColossusSequenceManager.h)
//   [x] 0x46b9e0  CKColossusSequenceManager_Destroy  (empty: CKColossusSequenceManager.h)
//   [ ] 0x46b9e8  CKColossusSequenceManager_InitSequenceArray_maybe  [dead]
//   [ ] 0x46ba40  CKColossusSequenceManager_AppendSequence_maybe  [dead]
//   [ ] 0x46bb20  CKColossusSequenceManager_Destructor_2  [dead]
//   [x] 0x46bb88  CKColossusSequenceManager_DeletingDestructor  (the destructor)
//   [x] 0x46bc08  CKColossusSequenceManager_Destructor  (the destructor)
//   [x] 0x46bc70  CKHkColossus_Delete  (DOTD_DECLARE_FACTORIES in CKHkColossus.h: R03's class)
//   [ ] 0x46bcc0  KStub_Nop_46bcc0  [dead]
//   [x] 0x46bcc8  CKColossusAttackSequence_GetElementByIndex_maybe  (ColossusElementByIndex)
//
//   [x] 0x9c4160  CKColossusSequenceManager_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c4168  CKColossusSequenceManager_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c4170  CKColossusSequenceManager_IsKindOfClass  [inline]  (CKColossusSequenceManager.h)
#include "k2000/logic/CKColossusSequenceManager.h"

#include "k2000/hooks/CKHkColossus.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKColossusAttackSequenceBase.h"
#include "k2000/misc/KBase7CCC.h"

CKColossusSequenceManager::CKColossusSequenceManager() {
    m_vSequences.m_pBlock = nullptr;
    m_vSequences.m_ui32NbElt = 1;
    m_vSequences.m_ui32NbUsedElt = 0;
}

CKColossusSequenceManager::~CKColossusSequenceManager() {
    if (m_vSequences.m_pBlock != nullptr) Mem_FreeAligned16(m_vSequences.m_pBlock);
    m_vSequences.m_ui32NbUsedElt = 0;
    m_vSequences.m_pBlock = nullptr;
}

// 0x0046b830 CKColossusSequenceManager_Load: level files: the count (byte-swapped), a fresh one-slot block (capacity 1),
// then one reference per sequence appended (the block grows by one slot when full; Mem_ReallocAligned16).
int32_t CKColossusSequenceManager::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    int32_t count = 0;
    ReadS32LE(file, &count);
    m_vSequences.m_ui32NbElt = 1;
    m_vSequences.m_pBlock = static_cast<CKColossusAttackSequenceBase**>(
        Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CKColossusAttackSequenceBase*))));
    for (int32_t i = 0; i < count; ++i) {
        CKColossusAttackSequenceBase* sequence = nullptr;
        IKFile_ReadRef(file, &sequence);
        uint32_t used = m_vSequences.m_ui32NbUsedElt;
        if (m_vSequences.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            if (capacity == 0) capacity = 1;
            m_vSequences.m_pBlock = static_cast<CKColossusAttackSequenceBase**>(Mem_ReallocAligned16(
                m_vSequences.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CKColossusAttackSequenceBase*))));
            m_vSequences.m_ui32NbElt = capacity;
            used = m_vSequences.m_ui32NbUsedElt;
        }
        m_vSequences.m_pBlock[used] = sequence;
        m_vSequences.m_ui32NbUsedElt = m_vSequences.m_ui32NbUsedElt + 1;
    }
    return 1;
}

// 0x0046b568 CKColossusSequenceManager_PostLoad: every sequence gets the owner, its index and the manager.
int32_t CKColossusSequenceManager::PostLoad(int32_t /*type*/) {
    for (uint32_t i = 0; i < m_vSequences.m_ui32NbUsedElt; ++i) {
        m_vSequences.m_pBlock[i]->m_pOwner = m_pOwner;
        m_vSequences.m_pBlock[i]->m_ui32Index = i;
        m_vSequences.m_pBlock[i]->m_pManager = this;
    }
    return 1;
}

// 0x0046b288 ColossusAttackSequencer_StopCurrent_maybe
void CKColossusSequenceManager::StopCurrent() {
    const uint32_t current = static_cast<uint32_t>(m_i32Current);
    if (static_cast<int32_t>(current) >= 0 && current < m_vSequences.m_ui32NbUsedElt) {
        m_vSequences.m_pBlock[current]->Vf54();
    }
}

// 0x0046b308 ColossusAttackSequencer_Reset_maybe
void CKColossusSequenceManager::Reset() {
    if (m_vSequences.m_ui32NbUsedElt == 0) return;
    m_i32Current = 0;
    m_vSequences.m_pBlock[0]->Vf50();
}

// 0x0046b368 ColossusAttackSequencer_Update_maybe: a valid current sequence that is over (vt+0x64) is stopped (vt+0x54)
// and the next one (vt+0x68 true) or the previous one becomes current; past either end there is none (-1) and nothing
// more happens, else it is started (vt+0x50). The current sequence then runs (vt+0x60).
void CKColossusSequenceManager::Update(IKTime* frameClock) {
    uint32_t current = static_cast<uint32_t>(m_i32Current);
    if (current == 0xffffffffu || current >= m_vSequences.m_ui32NbUsedElt || static_cast<int32_t>(current) < 0) return;
    if (m_vSequences.m_pBlock[current]->Vf64() != 0) {
        const int32_t old = m_i32Current;
        m_i32Current = m_vSequences.m_pBlock[old]->Vf68() != 0 ? old + 1 : old - 1;
        m_vSequences.m_pBlock[old]->Vf54();
        current = static_cast<uint32_t>(m_i32Current);
        if (m_vSequences.m_ui32NbUsedElt <= current || static_cast<int32_t>(current) < 0) {
            m_i32Current = -1;
            return;
        }
        m_vSequences.m_pBlock[current]->Vf50();
    }
    m_vSequences.m_pBlock[m_i32Current]->Vf60(frameClock);
}

// 0x0046b620 ColossusAttackSequencer_SwitchToSequence_maybe. BUG(original): the current sequence is stopped without a
// check (none current: the word before the block).
void CKColossusSequenceManager::SwitchToSequence(uint32_t index) {
    if (static_cast<uint32_t>(m_i32Current) == index || index == 0xffffffffu || index >= m_vSequences.m_ui32NbUsedElt) return;
    m_vSequences.m_pBlock[m_i32Current]->Vf54();
    m_vSequences.m_pBlock[index]->Vf50();
    m_i32Current = static_cast<int32_t>(index);
}

// 0x0046bcc8 CKColossusAttackSequence_GetElementByIndex_maybe (bge, then cmplw / ble: a signed then an unsigned bound)
KBase7CCC* ColossusElementByIndex(CKHkColossus* colossus, int32_t index) {
    if (index < 0) return nullptr;
    if (colossus->m_vUnk24.m_ui32NbUsedElt <= static_cast<uint32_t>(index)) return nullptr;
    return static_cast<KBase7CCC*>(colossus->m_vUnk24.m_pBlock[index]);
}
