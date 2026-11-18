// CKIntegerCounter.cpp - reconstructed original translation unit 0x1ffc70-0x200820 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKIntegerCounter  key 0x220c  category Logic  size 0x34  vtable 0xb1ee58
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1ffc70  CKIntegerCounter_Delete
//   [x] 0x1ffcc0  CKIntegerCounter_Reset_maybe
//   [x] 0x1ffcd8  CKIntegerCounter_GetValue_maybe
//   [x] 0x1ffce8  CKIntegerCounter_GetLoopCount_maybe
//   [x] 0x1ffcf8  CKIntegerCounter_IsAtMax_maybe
//   [x] 0x1ffd20  CKIntegerCounter_IsAtMin_maybe
//   [x] 0x1ffd48  CKIntegerCounter_IsAtStart_maybe
//   [x] 0x1ffd70  CKIntegerCounter_IsLoopLimitReached_maybe
//   [x] 0x1ffd98  CKIntegerCounter_HasNoLoops_maybe
//   [x] 0x1ffdb8  CKIntegerCounter_HasLoopedAtLeast_maybe
//   [ ] 0x1ffdd8  RegisterCKIntegerCounterClass
//   [ ] 0x1ffe50  _GLOBAL__I_1ffe50
//   [x] 0x1ffe60  CKIntegerCounter_RecursiveRegistration  (inherited: IKCounter's, then the three starters' KStub_Return1_2361b0, nothing)
//   [x] 0x1ffef0  CKIntegerCounter_Destroy  (inherited: KStub_Nop_1ffc68)
//   [x] 0x1fff18  CKIntegerCounter_DeleteArray
//   [x] 0x1fffb8  CKIntegerCounter_Create
//   [x] 0x1ffff0  CKIntegerCounter_CreateArray
//   [x] 0x200080  CKIntegerCounter_GetInfo
//   [x] 0x200230  CKIntegerCounter_MessageProc
//   [x] 0x200470  CKIntegerCounter_PostLoad
//   [x] 0x200478  CKIntegerCounter_Load
//   [ ] 0x200660  CKIntegerCounter_Save
//
//   [ ] 0x9b12f8  CKIntegerCounter_IsKindOfClass  [inline]
//   [ ] 0x9b1320  CKIntegerCounter_GetClassType  [inline]
//   [ ] 0x9b1328  CKIntegerCounter_GetClassID  [inline]
//   [ ] 0x9b1330  CKIntegerCounter_DeletingDestructor  [inline]
//   [ ] 0x9b1378  CKIntegerCounter_Destructor  [inline]
#include "k2000/logic/CKIntegerCounter.h"

#include "k2000/core/IKInfo.h"
#include "k2000/core/Stub.h"

#include "k2000/io/IKFile.h"
#include "k2000/services/CKSrvTrigger.h"

// 0x00200478 CKIntegerCounter_Load
int32_t CKIntegerCounter::Load(IKFile* file, int32_t type) {
    IKCounter::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadS32LE(file, &m_i32StartValue);
        ReadS32LE(file, &m_i32MinValue);
        ReadS32LE(file, &m_i32MaxValue);
        ReadU32LE(file, &m_ui32MaxLoop);
        m_tsMaxValueReached.Load(file, K_LEVEL_PLATEFORMS);
        m_tsMinValueReached.Load(file, K_LEVEL_PLATEFORMS);
        m_tsMaxLoopReached.Load(file, K_LEVEL_PLATEFORMS);
    }
    return 1;
}

// 0x00200080 CKIntegerCounter_GetInfo, with the accessors 0x1ffcd8 GetValue, 0x1ffce8 GetLoopCount, 0x1ffd20 IsAtMin,
// 0x1ffcf8 IsAtMax, 0x1ffd48 IsAtStart, 0x1ffd70 IsLoopLimitReached, 0x1ffd98 HasNoLoops, 0x1ffdb8 HasLoopedAtLeast.
int32_t CKIntegerCounter::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 1:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<uint32_t>(static_cast<CKIntegerCounter*>(o)->m_i32CurrentValue); }, 1);
    case 2:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKIntegerCounter*>(o)->m_ui32CurrentLoop; }, 1);
    case 3:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CKIntegerCounter* c = static_cast<CKIntegerCounter*>(o);
            return static_cast<uint32_t>(c->m_i32CurrentValue == c->m_i32MinValue);
        }, 0);
    case 4:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CKIntegerCounter* c = static_cast<CKIntegerCounter*>(o);
            return static_cast<uint32_t>(c->m_i32CurrentValue == c->m_i32MaxValue);
        }, 0);
    case 5:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CKIntegerCounter* c = static_cast<CKIntegerCounter*>(o);
            return static_cast<uint32_t>(c->m_i32CurrentValue == c->m_i32StartValue);
        }, 0);
    case 6:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CKIntegerCounter* c = static_cast<CKIntegerCounter*>(o);
            return static_cast<uint32_t>(c->m_ui32CurrentLoop == c->m_ui32MaxLoop);
        }, 0);
    case 7:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<uint32_t>(static_cast<CKIntegerCounter*>(o)->m_ui32CurrentLoop == 0); }, 0);
    case 8:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t arg) { return static_cast<uint32_t>(arg <= static_cast<CKIntegerCounter*>(o)->m_ui32CurrentLoop); }, 0);
    default:
        return 1;
    }
}

// 0x00200230 CKIntegerCounter_MessageProc (the jump table TOC1 -0x1114 for 0x2100..0x210c): 0x2100 / 0x2101 / 0x2102
// the value set to the start / minimum / maximum, 0x2103 the loop count cleared, 0x2104 both (the start value).
// 0x210b adds the action's integer: reaching the maximum counts a loop, fires the max-value starter and wraps the
// overshoot from the minimum, or on the last loop keeps the maximum and fires the max-loop starter; nothing is added
// once the loop limit is reached (a limit of 0: none). 0x210c takes it away: below the minimum the min-value starter
// fires and the undershoot wraps from the maximum with a loop given back (on loop 0 with a limit the value stays at
// the minimum); taking from the maximum gives a loop back too. 0x2105..0x210a are not handled (1).
int32_t CKIntegerCounter::MessageProc(uint16_t message, void* data) {
    auto param = [data]() { return static_cast<int32_t>(static_cast<const CTriggerAction*>(data)->m_mdParam.m_ui32Value); };
    switch (message) {
    case 0x2100:
        m_i32CurrentValue = m_i32StartValue;
        return 0;
    case 0x2101:
        m_i32CurrentValue = m_i32MinValue;
        return 0;
    case 0x2102:
        m_i32CurrentValue = m_i32MaxValue;
        return 0;
    case 0x2103:
        m_ui32CurrentLoop = 0;
        return 0;
    case 0x2104:
        m_ui32CurrentLoop = 0;
        m_i32CurrentValue = m_i32StartValue;
        return 0;
    case 0x210b: {
        const uint32_t loop = m_ui32CurrentLoop;
        const int32_t add = param();
        if (loop >= m_ui32MaxLoop && m_ui32MaxLoop != 0) return 0;  // cmplw / bge, then the limit 0 test
        const int32_t value = add + m_i32CurrentValue;
        if (m_i32MaxValue > value) {
            m_i32CurrentValue = value;
            return 0;
        }
        m_ui32CurrentLoop = loop + 1;
        QueueTriggerSignals(&m_tsMaxValueReached);  // +0x1c (0x236338; the counter is the sender)
        if (static_cast<int32_t>(m_ui32CurrentLoop) == static_cast<int32_t>(m_ui32MaxLoop)) {
            m_i32CurrentValue = m_i32MaxValue;
            QueueTriggerSignals(&m_tsMaxLoopReached);  // +0x2c
            return 0;
        }
        m_i32CurrentValue = m_i32MinValue + (value - m_i32MaxValue);
        return 0;
    }
    case 0x210c: {
        const int32_t current = m_i32CurrentValue;
        const int32_t value = current - param();
        if (m_i32MinValue > value) {
            QueueTriggerSignals(&m_tsMinValueReached);  // +0x24
            if (m_ui32CurrentLoop != 0) {
                --m_ui32CurrentLoop;
            } else if (m_ui32MaxLoop != 0) {
                m_i32CurrentValue = m_i32MinValue;
                return 0;
            }
            m_i32CurrentValue = m_i32MaxValue - (m_i32MinValue - value);
            return 0;
        }
        if (m_i32MaxValue == current) --m_ui32CurrentLoop;
        m_i32CurrentValue = value;
        return 0;
    }
    default:
        return 1;
    }
}
