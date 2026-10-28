// CKTimeCounter.cpp - reconstructed original translation unit 0x200820-0x201390 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKTimeCounter  key 0x21cc  category Logic  size 0x30  vtable 0xb1eeb0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x200820  CKTimeCounter_Delete
//   [ ] 0x200870  CKTimeCounter_GetTime_maybe
//   [ ] 0x200878  CKTimeCounter_GetLoopCount_maybe
//   [ ] 0x200888  CKTimeCounter_IsLoopLimitReached_maybe
//   [ ] 0x2008b0  CKTimeCounter_HasNoLoops_maybe
//   [ ] 0x2008d0  CKTimeCounter_HasLoopedAtLeast_maybe
//   [ ] 0x2008f0  CKTimeCounter_GetFlag1cBit0_maybe
//   [ ] 0x200900  RegisterCKTimeCounterClass
//   [ ] 0x200978  _GLOBAL__I_200978
//   [x] 0x200988  CKTimeCounter_Reset
//   [ ] 0x200a10  CKTimeCounter_Save
//   [ ] 0x200a38  CKTimeCounter_RecursiveRegistration
//   [ ] 0x200b10  CKTimeCounter_Destroy
//   [x] 0x200b38  CKTimeCounter_DeleteArray
//   [x] 0x200be0  CKTimeCounter_Create
//   [x] 0x200c18  CKTimeCounter_CreateArray
//   [ ] 0x200cb0  CKTimeCounter_GetInfo
//   [ ] 0x200e08  CKTimeCounter_PostLoad
//   [x] 0x200e10  CKTimeCounter_Load
//   [ ] 0x200f98  CKTimeCounter_MessageProc
//
//   [ ] 0x9b1398  CKTimeCounter_IsKindOfClass  [inline]
//   [ ] 0x9b13c0  CKTimeCounter_GetClassType  [inline]
//   [ ] 0x9b13c8  CKTimeCounter_GetClassID  [inline]
//   [ ] 0x9b13d0  CKTimeCounter_DeletingDestructor  [inline]
//   [ ] 0x9b1418  CKTimeCounter_Destructor  [inline]
#include "k2000/logic/system/CKTimeCounter.h"

#include "k2000/io/IKFile.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/ClassRegistry.h"

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
