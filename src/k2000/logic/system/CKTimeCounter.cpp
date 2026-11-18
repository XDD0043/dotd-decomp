// CKTimeCounter.cpp - reconstructed original translation unit 0x200820-0x201390 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKTimeCounter  key 0x21cc  category Logic  size 0x30  vtable 0xb1eeb0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x200820  CKTimeCounter_Delete
//   [x] 0x200870  CKTimeCounter_GetTime_maybe
//   [x] 0x200878  CKTimeCounter_GetLoopCount_maybe
//   [x] 0x200888  CKTimeCounter_IsLoopLimitReached_maybe
//   [x] 0x2008b0  CKTimeCounter_HasNoLoops_maybe
//   [x] 0x2008d0  CKTimeCounter_HasLoopedAtLeast_maybe
//   [x] 0x2008f0  CKTimeCounter_GetFlag1cBit0_maybe
//   [ ] 0x200900  RegisterCKTimeCounterClass
//   [ ] 0x200978  _GLOBAL__I_200978
//   [x] 0x200988  CKTimeCounter_Reset
//   [ ] 0x200a10  CKTimeCounter_Save
//   [x] 0x200a38  CKTimeCounter_RecursiveRegistration
//   [x] 0x200b10  CKTimeCounter_Destroy  (0x1ffc68 KStub_Nop: IKBaseClass's empty default)
//   [x] 0x200b38  CKTimeCounter_DeleteArray
//   [x] 0x200be0  CKTimeCounter_Create
//   [x] 0x200c18  CKTimeCounter_CreateArray
//   [x] 0x200cb0  CKTimeCounter_GetInfo
//   [x] 0x200e08  CKTimeCounter_PostLoad  (IKSerializable's default (1))
//   [x] 0x200e10  CKTimeCounter_Load
//   [x] 0x200f98  CKTimeCounter_MessageProc
//
//   [ ] 0x9b1398  CKTimeCounter_IsKindOfClass  [inline]
//   [ ] 0x9b13c0  CKTimeCounter_GetClassType  [inline]
//   [ ] 0x9b13c8  CKTimeCounter_GetClassID  [inline]
//   [ ] 0x9b13d0  CKTimeCounter_DeletingDestructor  [inline]
//   [ ] 0x9b1418  CKTimeCounter_Destructor  [inline]
#include "k2000/logic/system/CKTimeCounter.h"

#include "k2000/core/IKInfo.h"
#include "k2000/io/IKFile.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/services/CKSrvTrigger.h"

#include <cstring>

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x00200a38 CKTimeCounter_RecursiveRegistration: IKCounter_RecursiveRegistration 0x1ffbf8 (registered for type 0),
// then registered again for type 0. The starters' 0x2361b0 (KStub_Return1) do nothing.
void CKTimeCounter::RecursiveRegistration(int32_t type) {
    IKCounter::RecursiveRegistration(type);  // 0x001ffbf8
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x00200e10 CKTimeCounter_Load
int32_t CKTimeCounter::Load(IKFile* file, int32_t type) {
    IKCounter::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fMaxValue);
        ReadF32LE(file, &m_unk0c);
        ReadU32LE(file, &m_ui32MaxLoop);
        m_tsMaxValueReached.Load(file, K_LEVEL_PLATEFORMS);
        m_tsMaxLoopReached.Load(file, K_LEVEL_PLATEFORMS);
    }
    return 1;
}

// 0x00200988 CKTimeCounter_Reset
void CKTimeCounter::Reset() {
    m_fCurrentValue = 0.0f;
    const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffff;
    const float range = m_unk0c - m_fMaxValue;
    m_ui32CurrentLoop = 0;
    m_fDrawnMaxValue = ppc::fmadds(static_cast<float>(draw) / 65535.0f, range, m_fMaxValue);
    m_baFlags &= 0xfffffffeu;
}

// The maximum the counter waits for, drawn between +0x08 and +0x0c (rand() & 0xffff over 65535, TOC1 -0x10ec).
void CKTimeCounter::DrawMaxValue() {
    const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    m_fDrawnMaxValue = ppc::fmadds(static_cast<float>(draw) / 65535.0f, m_unk0c - m_fMaxValue, m_fMaxValue);
}

// 0x00200f98 CKTimeCounter_MessageProc (the jump table TOC1 -0x10c0 for 0x2100..0x210c; 0 = handled, 1 otherwise).
// 0x2100 restart the time (new maximum), 0x2103 clear the loops, 0x2104 restart time and loops, 0x2105 run,
// 0x2106 restart and run, 0x2107 restart everything and run, 0x2108 stop, 0x2109 stop and restart the time, 0x210a
// stop and restart everything, 0x210b add the action's time (as the counter service's update, while loops are
// left), 0x210c take it away (below zero: a loop back with the overshoot, or 0 on the first loop). 0x2101 / 0x2102
// are not handled.
int32_t CKTimeCounter::MessageProc(uint16_t message, void* data) {
    auto param = [data]() {
        float value;
        std::memcpy(&value, &static_cast<const CTriggerAction*>(data)->m_mdParam, sizeof value);
        return value;
    };
    switch (message) {
    case 0x2100:
        m_fCurrentValue = 0.0f;
        DrawMaxValue();
        return 0;
    case 0x2103:
        m_ui32CurrentLoop = 0;
        return 0;
    case 0x2104:
        m_ui32CurrentLoop = 0;
        m_fCurrentValue = 0.0f;
        DrawMaxValue();
        return 0;
    case 0x2105:
        m_baFlags = (m_baFlags & 0xfffffffeu) | 1u;
        return 0;
    case 0x2106:
        m_fCurrentValue = 0.0f;
        DrawMaxValue();
        m_baFlags = (m_baFlags & 0xfffffffeu) | 1u;
        return 0;
    case 0x2107:
        m_fCurrentValue = 0.0f;
        m_ui32CurrentLoop = 0;
        DrawMaxValue();
        m_baFlags = (m_baFlags & 0xfffffffeu) | 1u;
        return 0;
    case 0x2108:
        m_baFlags &= 0xfffffffeu;
        return 0;
    case 0x2109:
        m_baFlags &= 0xfffffffeu;
        m_fCurrentValue = 0.0f;
        DrawMaxValue();
        return 0;
    case 0x210a:
        m_baFlags &= 0xfffffffeu;
        m_fCurrentValue = 0.0f;
        m_ui32CurrentLoop = 0;
        DrawMaxValue();
        return 0;
    case 0x210b: {
        if (!(m_ui32CurrentLoop < m_ui32MaxLoop) && m_ui32MaxLoop != 0) return 0;
        float value = param() + m_fCurrentValue;
        if (!(m_fDrawnMaxValue <= value)) {
            m_fCurrentValue = value;
            return 0;
        }
        QueueTriggerSignals(&m_tsMaxValueReached);  // 0x00236338
        if (!(m_fDrawnMaxValue <= value)) return 0;
        for (;;) {
            m_ui32CurrentLoop = m_ui32CurrentLoop + 1;
            if (m_ui32MaxLoop == m_ui32CurrentLoop) {
                m_fCurrentValue = m_fDrawnMaxValue;
                QueueTriggerSignals(&m_tsMaxLoopReached);
                m_baFlags &= 0xfffffffeu;
                return 0;
            }
            value = value - m_fDrawnMaxValue;
            const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            m_fCurrentValue = value;
            m_fDrawnMaxValue = ppc::fmadds(static_cast<float>(draw) / 65535.0f, m_unk0c - m_fMaxValue, m_fMaxValue);
            if (!(m_fDrawnMaxValue <= value)) return 0;
        }
    }
    case 0x210c: {
        const float value = m_fCurrentValue - param();
        if (!(value < 0.0f)) {  // TOC1 -0x10bc
            m_fCurrentValue = value;
            return 0;
        }
        if (m_ui32CurrentLoop == 0) {
            m_fCurrentValue = 0.0f;
            return 0;
        }
        m_ui32CurrentLoop = m_ui32CurrentLoop - 1;
        m_fCurrentValue = value + m_fDrawnMaxValue;
        DrawMaxValue();
        return 0;
    }
    default:
        return 1;
    }
}

// 0x00200cb0 CKTimeCounter_GetInfo, with its accessors 0x200870 GetTime, 0x200878 GetLoopCount, 0x2008f0 GetFlag1cBit0,
// 0x200888 IsLoopLimitReached, 0x2008b0 HasNoLoops and 0x2008d0 HasLoopedAtLeast.
int32_t CKTimeCounter::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 1:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return FloatBits(static_cast<CKTimeCounter*>(o)->m_fCurrentValue); }, 2);
    case 2:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKTimeCounter*>(o)->m_ui32CurrentLoop; }, 1);
    case 3:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKTimeCounter*>(o)->m_baFlags & 1u; }, 0);
    case 4:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CKTimeCounter* counter = static_cast<const CKTimeCounter*>(o);
            return counter->m_ui32CurrentLoop == counter->m_ui32MaxLoop ? 1u : 0u;
        }, 0);
    case 5:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKTimeCounter*>(o)->m_ui32CurrentLoop == 0 ? 1u : 0u; }, 0);
    case 6:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t arg) {
            return arg <= static_cast<CKTimeCounter*>(o)->m_ui32CurrentLoop ? 1u : 0u;
        }, 0);
    default:
        return 1;
    }
}
