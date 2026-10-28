// CKS08Damage.cpp - reconstructed original translation unit 0x4eb8c8-0x4ec6e8 (GAME_TOC1, main_toc1), 30 functions, 28 live.
// Primary class: CKS08Damage  key 0x970c  category Logic  size 0x28  vtable 0xb2aab0
// Other owners: IKCommonGameManager (6), CKS08GameManager (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4eb8c8  CKS08Damage_Delete
//   [ ] 0x4eb918  RegisterCKS08DamageClass
//   [ ] 0x4eb990  _GLOBAL__I_4eb990
//   [ ] 0x4eb9a0  CKS08Damage_Destroy
//   [ ] 0x4eb9c8  CKS08Damage_PostLoad
//   [ ] 0x4eb9f0  CKS08Damage_RecursiveRegistration
//   [ ] 0x4eba18  CKS08Damage_Assign
//   [ ] 0x4ebab8  CKS08Damage_DeletingDestructor
//   [ ] 0x4ebb00  CKS08Damage_Destructor
//   [ ] 0x4ebb30  CKS08Damage_BaseDestructor
//   [ ] 0x4ebb60  CKS08Damage_Construct_3
//   [ ] 0x4ebbe8  CKS08Damage_Construct_4
//   [x] 0x4ebc70  CKS08Damage_Construct
//   [ ] 0x4ebce0  CKS08Damage_Construct_2
//   [x] 0x4ebd50  CKS08Damage_DeleteArray
//   [x] 0x4ebdf8  CKS08Damage_Load
//   [ ] 0x4ec040  CKS08Damage_Save
//   [x] 0x4ec260  CKS08Damage_Create
//   [x] 0x4ec2f0  CKS08Damage_CreateArray
//   [x] 0x4ec420  CKS08GameManager_RequestState_maybe
//   [ ] 0x4ec438  IKCommonGameManager_vf94
//   [ ] 0x4ec440  IKCommonGameManager_vf98
//   [ ] 0x4ec450  IKCommonGameManager_vfBC
//   [ ] 0x4ec458  IKCommonGameManager_vfCC
//   [ ] 0x4ec4a0  IKCommonGameManager_vfD0
//   [ ] 0x4ec4a8  FUN_004ec4a8  [dead]
//   [x] 0x4ec540  CKS08GameManager_RequestLevelChange_maybe
//   [ ] 0x4ec560  IKCommonGameManager_vf2EC
//   [ ] 0x4ec5b8  CKS08GameManager_vf13C
//   [ ] 0x4ec658  FUN_004ec658  [dead]
//
//   [ ] 0x9c67c8  CKS08Damage_IsKindOfClass  [inline]
//   [ ] 0x9c6800  CKS08Damage_GetClassType  [inline]
//   [ ] 0x9c6808  CKS08Damage_GetClassID  [inline]
#include "Spyro2008/logic/CKS08GameManager.h"

// 0x004ec420 CKS08GameManager_RequestState_maybe: a game state other than the current one requested (+0x2fa;
// IKGameManager_Update switches before the frame's update).
void CKS08GameManager::RequestState(uint8_t state) {
    if (m_gameState.m_ui8Current == state) return;
    m_ui8RequestedState = state;
}

// 0x004ec540 CKS08GameManager_RequestLevelChange_maybe
uint8_t CKS08GameManager::RequestLevelChange(int32_t level, int32_t sector) {
    m_unk2FC = 2;
    m_requestedSector = sector;
    m_requestedLevel = level;
    return 1;
}
#include "Spyro2008/logic/CKS08Damage.h"

#include "k2000/io/IKFile.h"

// 0x004ebc70 CKS08Damage_Construct: CKDamage's constructor, then the stores in the original's order
// (it also zeroes CKDamage's three members).
CKS08Damage::CKS08Damage() {
    m_unk26 = 0;
    m_unk1c = 0.0f;
    m_unk04 = 0.0f;
    m_unk08 = 0;
    m_unk0c = 0;
    m_unk10 = 0.0f;
    m_unk14 = 0.0f;
    m_unk18 = 0;
    m_unk24 = 0;
    m_unk20 = 0;
    m_unk25 = 0;
}

// 0x004ebdf8 CKS08Damage_Load: CKDamage's data, five words and three bytes, whatever the type.
int32_t CKS08Damage::Load(IKFile* file, int32_t type) {
    CKDamage::Load(file, type);
    ReadF32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    ReadU32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk1c);
    ReadU32LE(file, &m_unk20);
    ReadU8(file, &m_unk24);
    ReadU8(file, &m_unk25);
    ReadU8(file, &m_unk26);
    return 1;
}
