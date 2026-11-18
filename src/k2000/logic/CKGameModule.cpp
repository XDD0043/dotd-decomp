// CKGameModule.cpp - reconstructed original translation unit 0x3b4f0-0x3c4f0 (GAME_TOC1, main_toc1), 28 functions, 27 live.
// Primary class: CKGameModule  key 0x334c  category Logic  size 0x30  vtable 0xb147e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3b4f0  CKGameModule_SetField2C_maybe  (the member store, inlined at its call in CKDefaultGameStructure_2.cpp's PostLoad)
//   [x] 0x3b4f8  CKGameModule_vf78
//   [x] 0x3b500  CKGameModule_vf7C
//   [x] 0x3b508  CKGameModule_vf88
//   [x] 0x3b510  CKGameModule_vf8C
//   [x] 0x3b518  CKGameModule_vf90
//   [x] 0x3b520  CKGameModule_vf94
//   [ ] 0x3b5d0  RegisterCKGameModuleClass
//   [ ] 0x3b648  _GLOBAL__I_3b648
//   [x] 0x3b658  CKGameModule_vf68
//   [ ] 0x3b728  FUN_0003b728  [dead]
//   [x] 0x3b768  CKGameModule_ClearGameData_maybe
//   [x] 0x3b790  CKGameModule_ClearLevelData
//   [x] 0x3b808  CKGameModule_InitLevelData
//   [x] 0x3b868  CKGameModule_InitGameData
//   [x] 0x3b8f0  CKGameModule_RecursiveRegistration  (inherited: IKGameObject_vf24, nothing)
//   [x] 0x3b918  CKGameModule_Destroy  (inherited: IKGameObject_Destroy)
//   [x] 0x3b940  CKGameModule_DeleteArray
//   [x] 0x3b9e8  CKGameModule_Create
//   [x] 0x3ba58  CKGameModule_vf98
//   [x] 0x3bb08  CKGameModule_SetActivated_maybe
//   [x] 0x3bbc0  CKGameModule_PostLoad
//   [x] 0x3bcb0  CKGameModule_GetInfo
//   [x] 0x3bd08  CKGameModule_CreateArray
//   [x] 0x3bdf0  CKGameModule_UpdateTriggerDomains_maybe
//   [x] 0x3be88  CKGameModule_MessageProc
//   [x] 0x3bf18  CKGameModule_Load
//   [ ] 0x3c218  CKGameModule_Save
//
//   [ ] 0x994cf0  CKGameModule_IsKindOfClass  [inline]
//   [x] 0x994d18  CKGameModule_GetClassType  [inline]
//   [x] 0x994d20  CKGameModule_GetClassID  [inline]
//   [x] 0x994d28  CKGameModule_vf74  [inline]
//   [x] 0x994d38  CKGameModule_GetTriggerProp2  [inline]
//   [x] 0x994d80  CKGameModule_vf80  [inline]
//   [x] 0x994da0  CKGameModule_vf84  [inline]
//   [x] 0x994db0  CKGameModule_DeletingDestructor  [inline]  (the destructor; delete)
//   [x] 0x994e38  CKGameModule_Destructor  [inline]  (written out below (C2.8 port-all P12))
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKGameModule.h"
#include "k2000/core/IKInfo.h"
#include "k2000/logic/CKTriggerSynchro.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/GameVector.h"

// The constructor inlined in CKGameModule_Create 0x3b9e8: +0x20 = 0, the vtable, +0x24 = 8, +0x28 = 0.
// +0x18, +0x1c and +0x2c are left as they are.
CKGameModule::CKGameModule() {
    m_vObjects.m_pBlock = nullptr;
    m_vObjects.m_ui32NbElt = 8;
    m_vObjects.m_ui32NbUsedElt = 0;
}

// 0x0003b808 CKGameModule_InitLevelData. The old block is not freed; the length is not reset.
void CKGameModule::InitializeLevelData() {
    IKGameObject::InitializeLevelData();
    GameVector_Reserve(&m_vObjects);
    m_pTriggerSynchro = nullptr;
}

// 0x0003b868 CKGameModule_InitGameData
void CKGameModule::InitializeGameData() {
    IKGameObject::InitializeGameData();
    m_pGameStage = nullptr;
    SetActivated(0);  // vt+0x70
    SetFlag2(0);      // vt+0x80
}

// 0x0003bbc0 CKGameModule_PostLoad
int32_t CKGameModule::PostLoad(int32_t type) {
    if (type == 0 && (m_baFlags & 1u) == 0) {
        SetActivated(0);  // vt+0x70
        SetFlag2(0);      // vt+0x80
    }
    return IKGameObject::PostLoad(type);  // 0x42e40 IKGameObject_PostLoad: returns 1
}

// 0x0003bb08 CKGameModule_SetActivated_maybe
void CKGameModule::SetActivated(uint8_t activated) {
    m_baFlags = (m_baFlags & ~2u) | ((static_cast<uint32_t>(activated) << 1) & 0x1feu);
    if (CanSetFlag2() != 0) SetFlag2(activated);  // vt+0x90, vt+0x80
}

// 0x0003b790 CKGameModule_ClearLevelData
void CKGameModule::DestroyLevelData() {
    m_pTriggerSynchro = nullptr;
    if (m_vObjects.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vObjects.m_pBlock);
        m_vObjects.m_pBlock = nullptr;
    }
    m_vObjects.m_ui32NbUsedElt = 0;
    m_vObjects.m_pBlock = nullptr;
    IKGameObject::DestroyLevelData();  // 0x42d90
}

// 0x0003bf18 CKGameModule_Load
int32_t CKGameModule::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        GameVector_Resize(&m_vObjects, count);
        for (uint32_t i = count; i-- != 0;) {  // from the last object down
            SGameModuleObject& object = m_vObjects.m_pBlock[i];
            IKFile_ReadObjectRef(file, &object.m_pObject);
            ReadU32LE(file, &object.m_ui32Ident);
            ReadU32LE(file, &object.m_ui32StateIdForLeft);
            ReadU32LE(file, &object.m_ui32StateIdForDone);
        }
    } else if (type == kGameStructureBlock) {
        IKFile_ReadRef(file, &m_pGameStage);
        ReadU8(file, &m_unk1c);
    }
    return 1;
}

// 0x0003b658 CKGameModule_vf68 (XXL2 ApplyGameStateToLevel): IKGameObject's (0x42d98, empty), then ApplyDone
// (vt+0x98) when the module is activated (vt+0x74), else ApplyLeft (vt+0x94).
void CKGameModule::ApplyGameStateToLevel() {
    IKGameObject::ApplyGameStateToLevel();
    if (static_cast<uint8_t>(IsActivated()) != 0) {
        ApplyDone();
    } else {
        ApplyLeft();
    }
}

// 0x0003b520 CKGameModule_vf94 (XXL2 ApplyLeft): each object, first to last, gets SetGameState (vt+0x3c)
// with an SApplyGameState {m_ui32Ident, m_ui32StateIdForLeft} on the stack.
void CKGameModule::ApplyLeft() {
    for (uint32_t i = 0; i < m_vObjects.m_ui32NbUsedElt; ++i) {
        const SGameModuleObject& object = m_vObjects.m_pBlock[i];
        const SApplyGameState state = {object.m_ui32Ident, object.m_ui32StateIdForLeft};
        object.m_pObject->SetGameState(&state);
    }
}

// 0x0003ba58 CKGameModule_vf98 (XXL2 ApplyDone): the same with {m_ui32Ident, m_ui32StateIdForDone}.
void CKGameModule::ApplyDone() {
    for (uint32_t i = 0; i < m_vObjects.m_ui32NbUsedElt; ++i) {
        const SGameModuleObject& object = m_vObjects.m_pBlock[i];
        const SApplyGameState state = {object.m_ui32Ident, object.m_ui32StateIdForDone};
        object.m_pObject->SetGameState(&state);
    }
}

// 0x0003bdf0 CKGameModule_UpdateTriggerDomains_maybe: the activated bit (vt+0x74) read, then the trigger
// synchro's (+0x2c) domain set of sector 0 (TriggerDomains_FindSetForSector_maybe 0x239d98) enabled when
// the module is not activated and that of sector 1 when it is (CKTriggerDomainSet_SetEnabled_maybe
// 0x23a770: the set's domains enabled or disabled recursively, its triggers' vt+0x64 / +0x68).
void CKGameModule::UpdateTriggerDomains() {
    const uint8_t activated = static_cast<uint8_t>(IsActivated());
    m_pTriggerSynchro->FindSetForSector(0)->SetEnabled(activated ^ 1);
    m_pTriggerSynchro->FindSetForSector(1)->SetEnabled(activated);
}

// 0x0003be88 CKGameModule_MessageProc
int32_t CKGameModule::MessageProc(uint16_t message, void* data) {
    if (message != 0x200) return 1;
    SetActivated(*static_cast<const uint8_t*>(data));  // vt+0x70
    UpdateTriggerDomains();                            // 0x3bdf0
    return 0;
}

// 0x0003bcb0 CKGameModule_GetInfo
int32_t CKGameModule::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 2) return 1;
    // 0x00994d38 CKGameModule_GetTriggerProp2: the module's vt+0x74 (activated), its low byte.
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
        return static_cast<CKGameModule*>(o)->IsActivated() & 0xffu;
    }, 0);
}

// 0x00994e38 CKGameModule_Destructor [inline] (written out in CKS08GameModule_Destructor 0x5085b0; C2.8 port-all P12):
// the object vector's block freed, its length and block cleared.
CKGameModule::~CKGameModule() {
    if (m_vObjects.m_pBlock != nullptr) Mem_FreeAligned16(m_vObjects.m_pBlock);
    m_vObjects.m_ui32NbUsedElt = 0;
    m_vObjects.m_pBlock = nullptr;
}
