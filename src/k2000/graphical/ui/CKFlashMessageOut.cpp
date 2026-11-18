// CKFlashMessageOut.cpp - reconstructed original translation unit 0x754e0-0x75960 (GAME_TOC1, main_toc1), 17 functions, 14 live.
// Primary class: CKFlashMessageOut  key 0x88d  category Graphical  size 0x24  vtable 0xb162a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x754e0  CKFlashMessageOut_Delete
//   [ ] 0x75530  CKFlashMessageOut_Construct  [dead]
//   [ ] 0x75548  CKFlashMessageOut_Construct_2  [dead]
//   [ ] 0x75560  RegisterCKFlashMessageOutClass
//   [ ] 0x755d8  _GLOBAL__I_755d8
//   [x] 0x755e8  CKFlashMessageOut_vf54
//   [x] 0x75610  CKFlashMessageOut_Send_maybe
//   [x] 0x75640  CKFlashMessageOut_DeleteArray
//   [x] 0x756e8  CKFlashMessageOut_CreateArray
//   [x] 0x75790  CKFlashMessageOut_Create
//   [x] 0x757d8  CKFlashMessageOut_RecursiveRegistration  (CKFlashMessageOut::RecursiveRegistration)
//   [ ] 0x75860  CKFlashMessageOut_Save
//   [x] 0x75888  CKFlashMessageOut_Load
//   [x] 0x758b0  CKFlashMessageOut_PostLoad
//   [x] 0x758d8  CKFlashMessageOut_Destructor
//   [ ] 0x758f8  CKFlashMessageOut_Destructor_2  [dead]
//   [x] 0x75918  CKFlashMessageOut_DeletingDestructor
//
//   [x] 0x999388  CKFlashMessageOut_GetClassType  [inline]
//   [x] 0x999390  CKFlashMessageOut_GetClassID  [inline]
//   [x] 0x999398  CKFlashMessageOut_IsKindOfClass  [inline]
//   [x] 0x9993d0  CKFlashMessageOut_Destroy  [inline]  (inherited: IKFlashObject_Destroy)
#include "k2000/graphical/ui/CKFlashMessageOut.h"

#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/io/IKFile.h"

// 0x00075888 CKFlashMessageOut_Load (as XXL2's: the base Load, then 1)
int32_t CKFlashMessageOut::Load(IKFile* file, int32_t type) {
    IKFlashMessage::Load(file, type);  // the original calls IKFlashObject_Load (IKFlashMessage's is inline)
    return 1;
}

// 0x00075610 CKFlashMessageOut_Send_maybe (XXL2 PostFlashMessage)
void CKFlashMessageOut::PostFlashMessage() {
    static_cast<CKFlashUI*>(m_pFlashUI)->PostMessage(static_cast<int32_t>(m_ui32LabelId));
}

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x000757d8 CKFlashMessageOut_RecursiveRegistration
void CKFlashMessageOut::RecursiveRegistration(int32_t type) {
    IKFlashObject::RecursiveRegistration(type);
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
