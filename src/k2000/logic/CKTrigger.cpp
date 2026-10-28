// CKTrigger.cpp - reconstructed original translation unit 0x2336a0-0x233db0 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary class: CKTrigger  key 0x238c  category Logic  size 0x1c  vtable 0xb208a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2336a0  CKTrigger_Delete
//   [ ] 0x2336f0  RegisterCKTriggerClass
//   [ ] 0x233768  _GLOBAL__I_233768
//   [ ] 0x233778  CKTrigger_RecursiveRegistration
//   [x] 0x2337a8  CKTrigger_DeleteArray
//   [x] 0x233850  CKTrigger_Create
//   [x] 0x233888  CKTrigger_CreateArray
//   [ ] 0x233920  CKTrigger_GetInfo
//   [x] 0x233928  CKTrigger_Load
//   [ ] 0x233af0  CKTrigger_Save
//   [ ] 0x233b20  CKTrigger_PostLoad
//   [ ] 0x233b50  CKTrigger_Destroy
//   [ ] 0x233b58  KStub_Return1_233b58  [dead]
//   [x] 0x233b60  CKTrigger_LoadAction
//
//   [ ] 0x9b7490  CKTrigger_GetClassType  [inline]
//   [ ] 0x9b7498  CKTrigger_GetClassID  [inline]
//   [ ] 0x9b74a0  CKTrigger_Destructor  [inline]
//   [ ] 0x9b74b8  CKTrigger_IsKindOfClass  [inline]
//   [ ] 0x9b74d8  CKTrigger_DeletingDestructor  [inline]
#include "k2000/logic/CKTrigger.h"

#include <cstdint>

#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKEvaluator.h"
#include "k2000/services/CKSrvTrigger.h"

// 0x00233928 CKTrigger_Load
int32_t CKTrigger::Load(IKFile* file, int32_t type) {
    m_tsStarter.Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pRootEvaluator);
    ReadU32LE(file, &m_ui32NbActions);
    // The actions come from the trigger service's block, sized by CKSrvTrigger_Load for the level.
    CKSrvTrigger* service = static_cast<CKSrvTrigger*>(g_pEngine->m_srvTrigger);
    const uint32_t first = service->m_ui32NbRequestedActions;
    service->m_ui32NbRequestedActions = m_ui32NbActions + first;
    m_aActions = service->m_aAllocatedActions + first;
    for (uint32_t i = 0; i < m_ui32NbActions; ++i) LoadAction(&m_aActions[i], file, K_LEVEL_PLATEFORMS);
    ReadU8(file, &m_unk18);
    m_unk19 = 0;
    return 1;
}

// 0x00233b60 CKTrigger_LoadAction: the target, the message, then the parameter by its type
// (0 a byte in all four bytes, 1/2 an integer or float word, 3 an object reference).
int32_t CKTrigger::LoadAction(CTriggerAction* action, IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &action->m_pObject);
    ReadU16LE(file, &action->m_mMsg);
    int32_t paramType = 0;
    ReadS32LE(file, &paramType);
    if (paramType == 1 || paramType == 2) {
        ReadU32LE(file, &action->m_mdParam.m_ui32Value);
    } else if (paramType == 0) {
        uint8_t b = 0;
        ReadU8(file, &b);
        action->m_mdParam.m_ui32Value = static_cast<uint32_t>(b) * 0x01010101u;
    } else if (paramType == 3) {
        IKSerializable* object = nullptr;
        IKFile_ReadRef(file, &object);
        action->m_mdParam.m_pObject = object;  // the CMultiData word holds the pointer
    }
    return 1;
}
