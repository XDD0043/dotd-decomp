// CKGroupBlocCinematicBloc.cpp - reconstructed original translation unit 0x17c080-0x17d0f0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKGroupBlocCinematicBloc  key 0x1c8  category CinematicNode  size 0x48  vtable 0xb1b3b0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x17c080  RegisterCKGroupBlocCinematicBlocClass
//   [ ] 0x17c0f8  _GLOBAL__I_17c0f8
//   [x] 0x17c108  CKGroupBlocCinematicBloc_MessageProc
//   [x] 0x17c1b8  CKGroupBlocCinematicBloc_Update
//   [ ] 0x17c260  CKGroupBlocCinematicBloc_Save
//   [x] 0x17c288  CKGroupBlocCinematicBloc_RecursiveRegistration
//   [x] 0x17c388  CKGroupBlocCinematicBloc_DeleteArray
//   [x] 0x17c430  CKGroupBlocCinematicBloc_Create
//   [x] 0x17c488  CKGroupBlocCinematicBloc_Abort
//   [x] 0x17c598  CKGroupBlocCinematicBloc_Stop
//   [x] 0x17c818  CKGroupBlocCinematicBloc_Destroy  (CKGroupBlocCinematicBloc.h)
//   [x] 0x17c850  CKGroupBlocCinematicBloc_CreateArray
//   [x] 0x17c908  CKGroupBlocCinematicBloc_Start
//   [x] 0x17cc38  CKGroupBlocCinematicBloc_Load
//   [x] 0x17ce68  CKGroupBlocCinematicBloc_Complete
//
//   [ ] 0x9a9790  CKGroupBlocCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a97c8  CKGroupBlocCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a97d0  CKGroupBlocCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a97d8  CKGroupBlocCinematicBloc_Destructor  [inline]
//   [ ] 0x9a97f8  CKGroupBlocCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKGroupBlocCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"

// 0x0017cc38 CKGroupBlocCinematicBloc_Load
int32_t CKGroupBlocCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32EltNumber);
    if (m_ui32EltNumber != 0) {
        m_pEltPointer = new IKSerializable*[m_ui32EltNumber];
        IKFile_ReadObjectRefArray(file, m_pEltPointer, m_ui32EltNumber);
    }
    IKFile_ReadRef(file, &m_pBegin);
    IKFile_ReadRef(file, &m_pEnd);
    return 1;
}

// 0x0017c908 CKGroupBlocCinematicBloc_Start
void CKGroupBlocCinematicBloc::Start() {
    StartCommon();
    IKCinematicElement* end = static_cast<IKCinematicElement*>(m_pEnd);
    end->m_DataFlags &= 0xfffffffbu;
    if (m_pBegin != nullptr) {
        static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic)->ActivateNode(this, static_cast<IKCinematicElement*>(m_pBegin));
    }
    for (uint32_t i = 0; i < m_ui32EltNumber; ++i) {
        IKCinematicElement* element = static_cast<IKCinematicElement*>(m_pEltPointer[i]);
        element->m_DataFlags = (element->m_DataFlags & 0xffffffefu) | 0x10;
    }
}

// 0x0017c1b8 CKGroupBlocCinematicBloc_Update
void CKGroupBlocCinematicBloc::Update(IKTime* /*time*/) {
    if (CheckSekensStop() == 0) return;
    const IKCinematicElement* end = static_cast<IKCinematicElement*>(m_pEnd);
    if ((end->m_DataFlags & 4) != 0 && end->m_ui16StartElementsFirstIndex == 0xffff &&
        end->m_ui16InterruptElementsFirstIndex == 0xffff) {
        Complete();  // vt+0x64
    }
}

// 0x0017c108 CKGroupBlocCinematicBloc_MessageProc
int32_t CKGroupBlocCinematicBloc::MessageProc(uint16_t message, void* data) {
    if (message == 0x501) {
        Stop();  // vt+0x6c
        return 0;
    }
    const int32_t result = ElementMessageProc(message, data);  // 0x0018faf8
    if (result == 3 || result == 2) return result;
    return result != 0 ? 1 : 0;
}

// 0x0017c488 CKGroupBlocCinematicBloc_Abort
void CKGroupBlocCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    for (uint32_t i = 0; i < m_ui32EltNumber; ++i) {
        IKCinematicElement* element = static_cast<IKCinematicElement*>(m_pEltPointer[i]);
        if ((element->m_DataFlags & 1) != 0) element->Abort();  // vt+0x70
        element->m_DataFlags = (element->m_DataFlags & 0xffffffefu) | 0x10;
    }
}

// 0x0017c598 CKGroupBlocCinematicBloc_Stop
void CKGroupBlocCinematicBloc::Stop() {
    CompleteBloc();
    for (uint32_t i = 0; i < m_ui32EltNumber; ++i) {
        IKCinematicElement* element = static_cast<IKCinematicElement*>(m_pEltPointer[i]);
        if ((element->m_DataFlags & 1) == 0) continue;
        element->m_DataFlags &= 0xffffffefu;
        element->Stop();  // vt+0x6c
    }
    Complete();  // vt+0x64
}

// 0x0017ce68 CKGroupBlocCinematicBloc_Complete
void CKGroupBlocCinematicBloc::Complete() {
    CompleteBloc();
    for (uint32_t i = 0; i < m_ui32EltNumber; ++i) {
        IKCinematicElement* element = static_cast<IKCinematicElement*>(m_pEltPointer[i]);
        if ((element->m_DataFlags & 1) != 0) element->Abort();  // vt+0x70
        element->m_DataFlags = (element->m_DataFlags & 0xffffffefu) | 0x10;
    }
    m_pRelatedScene->RemoveActiveNode(static_cast<IKCinematicElement*>(m_pEnd));
}

// 0x0017c288 CKGroupBlocCinematicBloc_RecursiveRegistration
void CKGroupBlocCinematicBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    for (uint32_t i = 0; i < m_ui32EltNumber; ++i) m_pEltPointer[i]->RecursiveRegistration(type);  // vt+0x24
}
