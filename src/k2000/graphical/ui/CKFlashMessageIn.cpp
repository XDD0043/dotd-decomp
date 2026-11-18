// CKFlashMessageIn.cpp - reconstructed original translation unit 0x74e30-0x754e0 (GAME_TOC1, main_toc1), 21 functions, 16 live.
// Primary class: CKFlashMessageIn  key 0x84d  category Graphical  size 0x2c  vtable 0xb161b8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x74e30  CKFlashMessageIn_Delete
//   [ ] 0x74e80  CKFlashMessageIn_Construct  [dead]
//   [ ] 0x74e98  CKFlashMessageIn_Construct_2  [dead]
//   [ ] 0x74eb0  CKFlashMessageIn_GetRefArray_maybe  [dead]
//   [ ] 0x74ec0  CKFlashMessageIn_GetRefCount_maybe  [dead]
//   [ ] 0x74ec8  RegisterCKFlashMessageInClass
//   [ ] 0x74f40  _GLOBAL__I_74f40
//   [x] 0x74f50  CKFlashMessageIn_vf54
//   [x] 0x74f78  CKFlashMessageIn_DeleteArray
//   [x] 0x75018  CKFlashMessageIn_CreateArray
//   [x] 0x750b8  CKFlashMessageIn_Create
//   [x] 0x75100  CKFlashMessageIn_GetInfo
//   [x] 0x75108  CKFlashMessageIn_TriggerTargets_maybe
//   [x] 0x75190  CKFlashMessageIn_PostLoad
//   [x] 0x751b8  CKFlashMessageIn_Destroy
//   [x] 0x75200  CKFlashMessageIn_RecursiveRegistration  (CKFlashMessageIn::RecursiveRegistration)
//   [ ] 0x75288  CKFlashMessageIn_Save
//   [x] 0x752b0  CKFlashMessageIn_Load
//   [x] 0x75458  CKFlashMessageIn_DeletingDestructor
//   [x] 0x754a0  CKFlashMessageIn_Destructor
//   [ ] 0x754c0  CKFlashMessageIn_Destructor_2  [dead]
//
//   [x] 0x999210  CKFlashMessageIn_GetClassType  [inline]
//   [x] 0x999218  CKFlashMessageIn_GetClassID  [inline]
//   [ ] 0x999220  IKFlashMessage_vf30  [inline]
//   [x] 0x999248  IKFlashMessage_vf2C  [inline]
//   [ ] 0x999270  IKFlashMessage_vf28  [inline]
//   [ ] 0x999298  IKFlashMessage_vf24  [inline]
//   [ ] 0x9992c0  IKFlashMessage_vf10  [inline]
//   [x] 0x9992e8  CKFlashMessageIn_IsKindOfClass  [inline]
//   [x] 0x999320  IKFlashMessage_DeletingDestructor  [inline]
//   [x] 0x999368  IKFlashMessage_vf0  [inline]
#include "k2000/graphical/ui/CKFlashMessageIn.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x000752b0 CKFlashMessageIn_Load
int32_t CKFlashMessageIn::Load(IKFile* file, int32_t type) {
    IKFlashMessage::Load(file, type);  // the original calls IKFlashObject_Load (IKFlashMessage's is inline)
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32GenericEventNb);
    if (m_ui32GenericEventNb == 0) {
        m_apGenericEvent = nullptr;
        return 1;
    }
    m_apGenericEvent = static_cast<IKFlashGenericEvent**>(
        Mem_AllocAligned16(m_ui32GenericEventNb * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apGenericEvent), m_ui32GenericEventNb);
    return 1;
}

// 0x000751b8 CKFlashMessageIn_Destroy: the base's, then the event table freed (the pointer is kept).
void CKFlashMessageIn::Destroy() {
    IKFlashMessage::Destroy();
    if (m_apGenericEvent != nullptr) Mem_FreeAligned16(m_apGenericEvent);
}

// 0x00075108 CKFlashMessageIn_TriggerTargets_maybe (XXL2 StartAllEvents)
void CKFlashMessageIn::StartAllEvents() {
    for (uint32_t i = 0; i < m_ui32GenericEventNb; ++i) m_apGenericEvent[i]->Vf50();
}

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x00075200 CKFlashMessageIn_RecursiveRegistration
void CKFlashMessageIn::RecursiveRegistration(int32_t type) {
    IKFlashObject::RecursiveRegistration(type);
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
