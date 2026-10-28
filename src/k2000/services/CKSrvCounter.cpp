// CKSrvCounter.cpp - reconstructed original translation unit 0x201390-0x202248 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKSrvCounter  key 0x441  category Service  size 0x24  vtable 0xb1ef08
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x201390  CKSrvCounter_Delete
//   [ ] 0x2013e0  CKSrvCounter_RecursiveRegistration
//   [ ] 0x2013e8  CKSrvCounter_Stop
//   [ ] 0x2013f0  CKSrvCounter_Pause
//   [ ] 0x2013f8  CKSrvCounter_Resume
//   [x] 0x201400  CKSrvCounter_InitializeService
//   [x] 0x201408  CKSrvCounter_DestroyService
//   [ ] 0x201410  RegisterCKSrvCounterClass
//   [ ] 0x201488  _GLOBAL__I_201488
//   [ ] 0x201498  CKSrvCounter_PostLoad
//   [x] 0x2014c0  CKSrvCounter_Destroy
//   [x] 0x201558  CKSrvCounter_Construct
//   [ ] 0x2015f0  CKSrvCounter_Construct_2
//   [x] 0x201688  CKSrvCounter_DeleteArray
//   [ ] 0x201730  CKSrvCounter_Restart
//   [ ] 0x201838  UpdateCKSrvCounter
//   [ ] 0x201a20  CKSrvCounter_Start
//   [x] 0x201ad8  CKSrvCounter_Load
//   [ ] 0x201df8  CKSrvCounter_Save
//   [x] 0x202050  CKSrvCounter_CreateArray
//   [x] 0x202198  CKSrvCounter_Create
//
//   [ ] 0x9b1438  CKSrvCounter_IsKindOfClass  [inline]
//   [ ] 0x9b1470  CKSrvCounter_GetClassType  [inline]
//   [ ] 0x9b1478  CKSrvCounter_GetClassID  [inline]
//   [ ] 0x9b1480  CKSrvCounter_DeletingDestructor  [inline]
//   [ ] 0x9b1538  CKSrvCounter_Destructor  [inline]
#include "k2000/services/CKSrvCounter.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

namespace {
// The inlined TVector load of both lists: a count; when non-zero the block is sized to it (the growth
// to count + 1 cannot trigger right after), the length set and the references read.
void LoadCounterList(TVector<IKSerializable*, 1>* list, IKFile* file, uint32_t count) {
    list->m_ui32NbElt = count;
    list->m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    if (list->m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        list->m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(list->m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        list->m_ui32NbElt = capacity;
    }
    list->m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, list->m_pBlock, count);
}
}  // namespace

// 0x00201558 CKSrvCounter_Construct (the same stores inlined in 0x202198 CKSrvCounter_Create).
CKSrvCounter::CKSrvCounter() {
    m_vpIntegerCounterList.m_ui32NbElt = 1;
    m_vpIntegerCounterList.m_pBlock = nullptr;
    m_vpIntegerCounterList.m_ui32NbUsedElt = 0;
    m_vpTimeCounterList.m_ui32NbElt = 1;
    m_vpTimeCounterList.m_ui32NbUsedElt = 0;
    m_vpTimeCounterList.m_pBlock = nullptr;
    m_ui32Priority = 0x87;
    Engine_SetSrvCounter(this);
}

// 0x002014c0 CKSrvCounter_Destroy (the level unload): both counter lists emptied and freed (IKService's part is empty).
void CKSrvCounter::Destroy() {
    if (m_vpIntegerCounterList.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpIntegerCounterList.m_pBlock);
        m_vpIntegerCounterList.m_pBlock = nullptr;
    }
    m_vpIntegerCounterList.m_ui32NbUsedElt = 0;
    m_vpIntegerCounterList.m_pBlock = nullptr;
    if (m_vpTimeCounterList.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpTimeCounterList.m_pBlock);
        m_vpTimeCounterList.m_pBlock = nullptr;
    }
    m_vpTimeCounterList.m_ui32NbUsedElt = 0;
    m_vpTimeCounterList.m_pBlock = nullptr;
}

// 0x00201ad8 CKSrvCounter_Load: the integer counters, then the time counters; an empty list keeps its
// constructor state.
int32_t CKSrvCounter::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count != 0) LoadCounterList(&m_vpIntegerCounterList, file, count);
    ReadU32LE(file, &count);
    if (count != 0) LoadCounterList(&m_vpTimeCounterList, file, count);
    return 1;
}
