// CKIntegerCounter.cpp - reconstructed original translation unit 0x1ffc70-0x200820 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKIntegerCounter  key 0x220c  category Logic  size 0x34  vtable 0xb1ee58
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1ffc70  CKIntegerCounter_Delete
//   [ ] 0x1ffcc0  CKIntegerCounter_Reset_maybe
//   [ ] 0x1ffcd8  CKIntegerCounter_GetValue_maybe
//   [ ] 0x1ffce8  CKIntegerCounter_GetLoopCount_maybe
//   [ ] 0x1ffcf8  CKIntegerCounter_IsAtMax_maybe
//   [ ] 0x1ffd20  CKIntegerCounter_IsAtMin_maybe
//   [ ] 0x1ffd48  CKIntegerCounter_IsAtStart_maybe
//   [ ] 0x1ffd70  CKIntegerCounter_IsLoopLimitReached_maybe
//   [ ] 0x1ffd98  CKIntegerCounter_HasNoLoops_maybe
//   [ ] 0x1ffdb8  CKIntegerCounter_HasLoopedAtLeast_maybe
//   [ ] 0x1ffdd8  RegisterCKIntegerCounterClass
//   [ ] 0x1ffe50  _GLOBAL__I_1ffe50
//   [ ] 0x1ffe60  CKIntegerCounter_RecursiveRegistration
//   [ ] 0x1ffef0  CKIntegerCounter_Destroy
//   [x] 0x1fff18  CKIntegerCounter_DeleteArray
//   [x] 0x1fffb8  CKIntegerCounter_Create
//   [x] 0x1ffff0  CKIntegerCounter_CreateArray
//   [ ] 0x200080  CKIntegerCounter_GetInfo
//   [ ] 0x200230  CKIntegerCounter_MessageProc
//   [ ] 0x200470  CKIntegerCounter_PostLoad
//   [x] 0x200478  CKIntegerCounter_Load
//   [ ] 0x200660  CKIntegerCounter_Save
//
//   [ ] 0x9b12f8  CKIntegerCounter_IsKindOfClass  [inline]
//   [ ] 0x9b1320  CKIntegerCounter_GetClassType  [inline]
//   [ ] 0x9b1328  CKIntegerCounter_GetClassID  [inline]
//   [ ] 0x9b1330  CKIntegerCounter_DeletingDestructor  [inline]
//   [ ] 0x9b1378  CKIntegerCounter_Destructor  [inline]
#include "k2000/logic/CKIntegerCounter.h"

#include "k2000/io/IKFile.h"

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
