// CKCinematicDoor.cpp - reconstructed original translation unit 0x18fc20-0x18ff28 (GAME_TOC1, main_toc1), 3 functions, 3 live.
// Primary owner: CKCinematicDoor (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18fc20  IKLogicalDoor_LevelReset  (IKLogicalDoor::RecursiveRegistration)
//   [ ] 0x18fc88  CKCinematicDoor_Save
//   [x] 0x18fc90  CKCinematicDoor_Load
//
//   [ ] 0x9a8e08  IKLogicalDoor_vf8  [inline]
//   [ ] 0x9a8e30  IKLogicalDoor_vf14  [inline]
//   [ ] 0x9a8e38  IKLogicalDoor_vf18  [inline]
//   [ ] 0x9a8e40  IKLogicalDoor_vf5C  [inline]
//   [ ] 0x9a8e48  IKLogicalDoor_vf64  [inline]
//   [ ] 0x9a8e50  IKLogicalDoor_vf68  [inline]
//   [ ] 0x9a8e58  KStub_Nop_9a8e58  [inline]
//   [ ] 0x9a8ea8  IKLogicalDoor_vf0  [inline]
//   [ ] 0x9a8f30  IKLogicalDoor_DeletingDestructor  [inline]
#include "k2000/misc/IKLogicalDoor.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"

// 0x0018fc90 CKCinematicDoor_Load (XXL2 IKLogicalDoor::BasicLoadCinematicElement)
int32_t IKLogicalDoor::BasicLoadCinematicElement(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_ui32IncomingNumber);
        ReadU16LE(file, &m_ui16StartElementsFirstIndex);
        ReadU16LE(file, &m_ui16InterruptElementsFirstIndex);
        ReadU16LE(file, &m_ui16ElementsNumber);
        ReadU32LE(file, &m_DataFlags);
        IKFile_ReadRef(file, &m_pParentGroup);
        IKFile_ReadRef(file, &m_pRelatedScene);
        m_ui32CurrentIncomingNumber = 0;
    }
    m_pElementData = nullptr;
    m_DataFlags &= 0xfffffffeu;
    return 1;
}

// CKEndDoor_Start 0x16eac0 / CKLogicalAnd_ActivateInput 0x16f528 (first lines): the incoming counter.
void IKLogicalDoor::CountIncomingActivation() {
    uint32_t count = m_ui32CurrentIncomingNumber;
    if (count == 0) {
        m_pRelatedScene->AddActiveNode(this);
        m_DataFlags = (m_DataFlags & 0xfffffff8u) | (m_DataFlags & 2) | 1;
        count = m_ui32CurrentIncomingNumber;
    }
    m_ui32CurrentIncomingNumber = count + 1;
}

// 0x0016e8f0 CKEndDoor_Complete (also the body of CKLogicalAnd_Complete 0x16ef40 and CKLogicalOr_Complete 0x16f840)
void IKLogicalDoor::CompleteDoor() {
    uint32_t count = 0;
    m_ui32CurrentIncomingNumber = 0;
    m_pRelatedScene->RemoveActiveNode(this);
    m_DataFlags = (m_DataFlags & 0xfffffffau) | 4;
    if ((m_DataFlags & 0x10) == 0) return;
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    IKCinematicElement** outputs = m_pRelatedScene->GetNodeOutputs(&count, 1, this);
    for (uint32_t i = 0; i < count; ++i) service->ActivateNode(this, outputs[i]);
    count = 0;
    outputs = m_pRelatedScene->GetNodeOutputs(&count, 2, this);
    for (uint32_t i = 0; i < count; ++i) outputs[i]->Stop();  // vt+0x6c
}

#include "k2000/logic/CKSavingManager.h"

// 0x0018fc20 IKLogicalDoor_LevelReset (the recursive registration)
void IKLogicalDoor::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
