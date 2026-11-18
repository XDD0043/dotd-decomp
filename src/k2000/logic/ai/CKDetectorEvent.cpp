// CKDetectorEvent.cpp - reconstructed original translation unit 0x1a9890-0x1a9ff0 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKDetectorEvent  key 0x280c  category Logic  size 0x2c  vtable 0xb1c410
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a9890  CKDetectorEvent_Delete
//   [x] 0x1a98e0  CKDetectorEvent_QueryVf54Mode1_maybe  (the accessor of the trigger value 100, CKDetectorEvent::GetInfo)
//   [ ] 0x1a9928  RegisterCKDetectorEventClass
//   [ ] 0x1a99a0  _GLOBAL__I_1a99a0
//   [x] 0x1a99b0  CKDetectorEvent_FireDetectionEvents_maybe
//   [x] 0x1a9b20  CKDetectorEvent_GetInfo
//   [x] 0x1a9c00  CKDetectorEvent_MessageProc  (CKDetectorBase's (inherited))
//   [x] 0x1a9c28  CKDetectorEvent_PostLoad  (the starters' PostLoad (TriggerEventList_PostLoad_maybe, returns 1) and the base's: returns 1, the default slot)
//   [x] 0x1a9ca8  CKDetectorEvent_Load
//   [ ] 0x1a9d58  CKDetectorEvent_Save
//   [x] 0x1a9e08  CKDetectorEvent_RecursiveRegistration  (the base's (returns 1) and the starters' KStub_Return1_2361b0: registers nothing; the default slot)
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
#include "k2000/core/IKInfo.h"

// 0x001a99b0 CKDetectorEvent_FireDetectionEvents_maybe (QueueTriggerSignals 0x236338 also gets the detector, unused)
int32_t CKDetectorEvent::Detect() {
    if ((CKDetectorBase::Detect() & 0xff) == 0) return 0;  // 0x1a8c70
    if ((GetDetectionType(0) & 0xff) != 0) QueueTriggerSignals(&m_tsDetectTrigger[0]);
    if ((GetDetectionType(1) & 0xff) != 0) QueueTriggerSignals(&m_tsDetectTrigger[1]);
    if ((GetDetectionType(2) & 0xff) != 0) QueueTriggerSignals(&m_tsDetectTrigger[2]);
    return 1;
}

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

// 0x001a9b20 CKDetectorEvent_GetInfo
int32_t CKDetectorEvent::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKDetectorBase::GetInfo(info, request);  // 0x1a8978
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 100) {
        // 0x001a98e0 CKDetectorEvent_QueryVf54Mode1_maybe: vt+0x54 (GetDetectionType) with 1, a byte.
        own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return static_cast<uint32_t>(static_cast<CKDetectorEvent*>(o)->GetDetectionType(1)) & 0xffu;
        }, 0);
    }
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}
