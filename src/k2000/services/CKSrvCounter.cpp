// CKSrvCounter.cpp - reconstructed original translation unit 0x201390-0x202248 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKSrvCounter  key 0x441  category Service  size 0x24  vtable 0xb1ef08
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x201390  CKSrvCounter_Delete
//   [x] 0x2013e0  CKSrvCounter_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x2013e8  CKSrvCounter_Stop
//   [x] 0x2013f0  CKSrvCounter_Pause
//   [x] 0x2013f8  CKSrvCounter_Resume
//   [x] 0x201400  CKSrvCounter_InitializeService
//   [x] 0x201408  CKSrvCounter_DestroyService
//   [ ] 0x201410  RegisterCKSrvCounterClass
//   [ ] 0x201488  _GLOBAL__I_201488
//   [x] 0x201498  CKSrvCounter_PostLoad  (= the inherited slot)
//   [x] 0x2014c0  CKSrvCounter_Destroy
//   [x] 0x201558  CKSrvCounter_Construct
//   [x] 0x2015f0  CKSrvCounter_Construct_2  (the not-in-charge copy of the constructor: CKSrvCounter())
//   [x] 0x201688  CKSrvCounter_DeleteArray
//   [x] 0x201730  CKSrvCounter_Restart
//   [x] 0x201838  UpdateCKSrvCounter
//   [x] 0x201a20  CKSrvCounter_Start
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
#include "crt/ppc_ops.h"
#include "k2000/logic/CKIntegerCounter.h"
#include "k2000/logic/system/CKTimeCounter.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/system/IKTime.h"

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

// 0x00201a20 CKSrvCounter_Start: every integer counter, then every time counter reset (each time counter draws a new
// maximum: one rand() per counter).
void CKSrvCounter::Start() {
    for (uint32_t i = 0; i < m_vpIntegerCounterList.m_ui32NbUsedElt; ++i) {
        static_cast<CKIntegerCounter*>(m_vpIntegerCounterList.m_pBlock[i])->Reset();
    }
    for (uint32_t i = 0; i < m_vpTimeCounterList.m_ui32NbUsedElt; ++i) {
        static_cast<CKTimeCounter*>(m_vpTimeCounterList.m_pBlock[i])->Reset();
    }
}

// 0x00201730 CKSrvCounter_Restart (vt+0x54): every time counter reset (CKTimeCounter_Reset inlined: no loop, no time,
// a new maximum drawn: one rand() per counter, stopped). The integer counters are left as they are. The reset is written
// out here as in the original, so that the rand log names this function (the original's draws are CKSrvCounter_Restart's).
void CKSrvCounter::Restart() {
    for (uint32_t i = 0; i < m_vpTimeCounterList.m_ui32NbUsedElt; ++i) {
        CKTimeCounter* counter = static_cast<CKTimeCounter*>(m_vpTimeCounterList.m_pBlock[i]);
        counter->m_fCurrentValue = 0.0f;
        const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffff;
        const float range = counter->m_unk0c - counter->m_fMaxValue;
        counter->m_ui32CurrentLoop = 0;
        counter->m_fDrawnMaxValue = ppc::fmadds(static_cast<float>(draw) / 65535.0f, range, counter->m_fMaxValue);
        counter->m_baFlags &= 0xfffffffeu;
    }
}

// 0x00201838 UpdateCKSrvCounter: while the clock runs (state 0), every running time counter (flag bit 0) whose loops
// are not used up adds the scaled dt; reaching its drawn maximum queues +0x20 and starts the next loop with the
// overshoot and a new maximum (one rand() per loop, between +0x08 and +0x0c); the last loop leaves the value at the
// maximum, queues +0x28 and stops the counter.
void CKSrvCounter::Update(IKTime* clock) {
    if (clock->m_eCurrentState != 0) return;
    for (uint32_t i = 0; i < m_vpTimeCounterList.m_ui32NbUsedElt; ++i) {
        CKTimeCounter* counter = static_cast<CKTimeCounter*>(m_vpTimeCounterList.m_pBlock[i]);
        if ((counter->m_baFlags & 1u) == 0) continue;
        if (!(counter->m_ui32CurrentLoop < counter->m_ui32MaxLoop) && counter->m_ui32MaxLoop != 0) continue;
        float value = clock->m_afDeltaTime[0] + counter->m_fCurrentValue;
        if (!(counter->m_fDrawnMaxValue <= value)) {
            counter->m_fCurrentValue = value;
            continue;
        }
        QueueTriggerSignals(&counter->m_tsMaxValueReached);
        if (!(counter->m_fDrawnMaxValue <= value)) continue;
        bool last = false;
        for (;;) {
            counter->m_ui32CurrentLoop = counter->m_ui32CurrentLoop + 1;
            if (counter->m_ui32MaxLoop == counter->m_ui32CurrentLoop) {
                last = true;
                break;
            }
            value = value - counter->m_fDrawnMaxValue;
            const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            counter->m_fCurrentValue = value;
            const float drawn = ppc::fmadds(static_cast<float>(draw) / 65535.0f, counter->m_unk0c - counter->m_fMaxValue,
                                            counter->m_fMaxValue);
            counter->m_fDrawnMaxValue = drawn;
            if (!(drawn <= value)) break;
        }
        if (last) {
            counter->m_fCurrentValue = counter->m_fDrawnMaxValue;
            QueueTriggerSignals(&counter->m_tsMaxLoopReached);
            counter->m_baFlags &= 0xfffffffeu;
        }
    }
}
