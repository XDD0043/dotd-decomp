// CKLocSpeaker.cpp - reconstructed original translation unit 0x35470-0x35948 (GAME_TOC1, main_toc1), 18 functions, 15 live.
// Primary class: CKLocSpeaker  key 0x68cc  category Logic  size 0x18  vtable 0xb14340
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x35470  CKLocSpeaker_Delete
//   [x] 0x354c0  CKLocSpeaker_RecursiveRegistration  (in the header)
//   [x] 0x354c8  CKLocSpeaker_PostLoad
//   [ ] 0x354d0  RegisterCKLocSpeakerClass
//   [ ] 0x35548  _GLOBAL__I_35548
//   [x] 0x35558  CKLocSpeaker_IsCurrentSekensSpeaker_maybe
//   [x] 0x355f8  CKLocSpeaker_Load
//   [ ] 0x35620  CKLocSpeaker_Save
//   [x] 0x35648  CKLocSpeaker_ClearGameData_maybe
//   [x] 0x35670  CKLocSpeaker_InitGameData
//   [ ] 0x35698  CKLocSpeaker_Construct  [dead]
//   [ ] 0x356d0  CKLocSpeaker_Construct_2  [dead]
//   [x] 0x35708  CKLocSpeaker_DeleteArray
//   [x] 0x357b0  CKLocSpeaker_Create
//   [x] 0x35808  CKLocSpeaker_CreateArray
//   [x] 0x358c0  CKLocSpeaker_Destructor  (the vtables only: ~CKLocSpeaker)
//   [ ] 0x358e0  CKLocSpeaker_Destructor_2  [dead]
//   [x] 0x35900  CKLocSpeaker_DeletingDestructor  (the deleting form of 0x358c0)
//
//   [ ] 0x994220  CKLocSpeaker_IsKindOfClass  [inline]
//   [x] 0x994248  CKLocSpeaker_GetClassType  [inline]
//   [x] 0x994250  CKLocSpeaker_GetClassID  [inline]
//   [ ] 0x994258  KStub_Return2_994258  [inline]
#include "k2000/logic/ui/CKLocSpeaker.h"

#include "k2000/logic/CKSekens.h"
#include "k2000/logic/ui/CKStdText.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvSekensor.h"

// 0x00035558 CKLocSpeaker_IsCurrentSekensSpeaker_maybe (the engine's sekensor +0x84; the speaker compared as words).
uint8_t CKLocSpeaker_IsCurrentSekensSpeaker(const IKSerializable* speaker) {
    CKSekens* sekens = static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->GetCurrentSekens();  // 0x001f8588
    if (sekens == nullptr) return 0;
    IKSerializable* text = sekens->CallCurrentLineVf5C();  // 0x001f40a8
    if (text == nullptr) return 0;
    return static_cast<CKStdText*>(text)->m_pSpeaker == speaker ? 1 : 0;
}

// 0x000355f8 CKLocSpeaker_Load
int32_t CKLocSpeaker::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    return 1;
}
