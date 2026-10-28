// CKDetectorEvent.cpp - reconstructed original translation unit 0x1a9890-0x1a9ff0 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKDetectorEvent  key 0x280c  category Logic  size 0x2c  vtable 0xb1c410
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a9890  CKDetectorEvent_Delete
//   [ ] 0x1a98e0  CKDetectorEvent_QueryVf54Mode1_maybe
//   [ ] 0x1a9928  RegisterCKDetectorEventClass
//   [ ] 0x1a99a0  _GLOBAL__I_1a99a0
//   [ ] 0x1a99b0  CKDetectorEvent_FireDetectionEvents_maybe
//   [ ] 0x1a9b20  CKDetectorEvent_GetInfo
//   [ ] 0x1a9c00  CKDetectorEvent_MessageProc
//   [ ] 0x1a9c28  CKDetectorEvent_PostLoad
//   [x] 0x1a9ca8  CKDetectorEvent_Load
//   [ ] 0x1a9d58  CKDetectorEvent_Save
//   [ ] 0x1a9e08  CKDetectorEvent_RecursiveRegistration
//   [x] 0x1a9e88  CKDetectorEvent_DeleteArray
//   [x] 0x1a9f28  CKDetectorEvent_CreateArray
//   [x] 0x1a9fb8  CKDetectorEvent_Create
//
//   [ ] 0x9ab008  CKDetectorEvent_IsKindOfClass  [inline]
//   [ ] 0x9ab030  CKDetectorEvent_GetClassType  [inline]
//   [ ] 0x9ab038  CKDetectorEvent_GetClassID  [inline]
//   [ ] 0x9ab040  CKDetectorEvent_Destructor  [inline]
//   [ ] 0x9ab060  CKDetectorEvent_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKDetectorEvent.h"

#include "k2000/io/IKFile.h"

// 0x001a9ca8 CKDetectorEvent_Load
int32_t CKDetectorEvent::Load(IKFile* file, int32_t type) {
    const int32_t result = CKDetectorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        m_tsDetectTrigger[2].Load(file, K_LEVEL_PLATEFORMS);
        m_tsDetectTrigger[1].Load(file, K_LEVEL_PLATEFORMS);
        m_tsDetectTrigger[0].Load(file, K_LEVEL_PLATEFORMS);
    }
    return result;
}
