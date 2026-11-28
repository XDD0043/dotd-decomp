// CKS08Damage.cpp - reconstructed original translation unit 0x4eb8c8-0x4ec6e8 (GAME_TOC1, main_toc1), 30 functions, 28 live.
// Primary class: CKS08Damage  key 0x970c  category Logic  size 0x28  vtable 0xb2aab0
// Other owners: IKCommonGameManager (6), CKS08GameManager (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4eb8c8  CKS08Damage_Delete
//   [ ] 0x4eb918  RegisterCKS08DamageClass
//   [ ] 0x4eb990  _GLOBAL__I_4eb990
//   [x] 0x4eb9a0  CKS08Damage_Destroy  (inherited: CKDamage_Destroy)
//   [x] 0x4eb9c8  CKS08Damage_PostLoad  (= the inherited slot)
//   [x] 0x4eb9f0  CKS08Damage_RecursiveRegistration  (CKDamage's (returns 1, nothing registered), then 1)
//   [x] 0x4eba18  CKS08Damage_Assign
//   [x] 0x4ebab8  CKS08Damage_DeletingDestructor  (the destructor; delete)
//   [x] 0x4ebb00  CKS08Damage_Destructor  (C++ destructor chain: vtable stores, then CKDamage_BaseDestructor)
//   [x] 0x4ebb30  CKS08Damage_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x4ebb60  CKS08Damage_Construct_3  (the copy constructor, CKS08Damage.h)
//   [x] 0x4ebbe8  CKS08Damage_Construct_4  (= 0x4ebb60)
//   [x] 0x4ebc70  CKS08Damage_Construct
//   [x] 0x4ebce0  CKS08Damage_Construct_2  (the constructor's second C++ variant)
//   [x] 0x4ebd50  CKS08Damage_DeleteArray
//   [x] 0x4ebdf8  CKS08Damage_Load
//   [ ] 0x4ec040  CKS08Damage_Save
//   [x] 0x4ec260  CKS08Damage_Create
//   [x] 0x4ec2f0  CKS08Damage_CreateArray
//   [x] 0x4ec420  CKS08GameManager_RequestState_maybe
//   [x] 0x4ec438  IKCommonGameManager_vf94  (IKCommonGameManager's: 1; written out in CKS08GameManager::Vf94Slot, CKS08GameManager_3.cpp)
//   [x] 0x4ec440  IKCommonGameManager_vf98  (IKCommonGameManager's: +0x494 = 0, 1; written out in CKS08GameManager::Vf98Slot, CKS08GameManager_3.cpp)
//   [x] 0x4ec450  IKCommonGameManager_vfBC  (IKCommonGameManager's empty part of CKS08GameManager::VfBC (CKS08GameManager_3.cpp))
//   [x] 0x4ec458  IKCommonGameManager_vfCC  (CKS08GameManager::VfCCCommon, called first by CKS08GameManager::VfCC)
//   [x] 0x4ec4a0  IKCommonGameManager_vfD0  (IKCommonGameManager's empty part of CKS08GameManager::VfD0 (CKS08GameManager_3.cpp))
//   [ ] 0x4ec4a8  FUN_004ec4a8  [dead]
//   [x] 0x4ec540  CKS08GameManager_RequestLevelChange_maybe
//   [x] 0x4ec560  IKCommonGameManager_vf2EC
//   [x] 0x4ec5b8  CKS08GameManager_vf13C  (local copy GameManagerAcceptsTarget in CKLightningBoltNodeFx.cpp, the only caller)
//   [ ] 0x4ec658  FUN_004ec658  [dead]
//
//   [ ] 0x9c67c8  CKS08Damage_IsKindOfClass  [inline]
//   [ ] 0x9c6800  CKS08Damage_GetClassType  [inline]
//   [ ] 0x9c6808  CKS08Damage_GetClassID  [inline]
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/logic/CKGameLevel.h"

// 0x004ec420 CKS08GameManager_RequestState_maybe: a game state other than the current one requested (+0x2fa;
// IKGameManager_Update switches before the frame's update).
void CKS08GameManager::RequestState(uint8_t state) {
    if (m_gameState.m_ui8Current == state) return;
    m_ui8RequestedState = state;
}

// 0x004ec540 CKS08GameManager_RequestLevelChange_maybe
uint8_t CKS08GameManager::RequestLevelChange(int32_t level, int32_t sector) {
    m_i32FrontEndEntryMenu = 2;
    m_requestedSector = sector;
    m_requestedLevel = level;
    return 1;
}

// 0x004ec560 IKCommonGameManager_vf2EC: the front-end level (+0x2cc) requested, sector 0 (vt+0x2e4).
uint8_t CKS08GameManager::Vf2ECCommon() {
    return RequestLevelChange(static_cast<CKGameLevel*>(m_pFrontEndLevel)->m_i32StageIndex, 0);
}

// 0x004ec458 IKCommonGameManager_vfCC: the input frame (vt+0x320), then 0 (no slot chosen). CKS08GameManager::VfCC
// (CKS08GameManager_3.cpp) calls it first.
uint8_t CKS08GameManager::VfCCCommon() {
    Vf320();  // vt+0x320
    return 0;
}
#include "Spyro2008/logic/CKS08Damage.h"

#include "k2000/io/IKFile.h"

// 0x004ebc70 CKS08Damage_Construct: CKDamage's constructor, then the stores in the original's order
// (it also zeroes CKDamage's three members).
CKS08Damage::CKS08Damage() {
    m_unk26 = 0;
    m_unk1c = 0.0f;
    m_fAmount = 0.0f;
    m_i32DamageKind = 0;
    m_bContinuous = 0;
    m_fKnockbackForce = 0.0f;
    m_fKnockbackTime = 0.0f;
    m_unk18 = 0;
    m_unk24 = 0;
    m_ui32DamageType = 0;
    m_unk25 = 0;
}

// 0x004ebdf8 CKS08Damage_Load: CKDamage's data, five words and three bytes, whatever the type.
int32_t CKS08Damage::Load(IKFile* file, int32_t type) {
    CKDamage::Load(file, type);
    ReadF32LE(file, &m_fKnockbackForce);
    ReadF32LE(file, &m_fKnockbackTime);
    ReadU32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk1c);
    ReadU32LE(file, &m_ui32DamageType);
    ReadU8(file, &m_unk24);
    ReadU8(file, &m_unk25);
    ReadU8(file, &m_unk26);
    return 1;
}

// 0x004ebb60 CKS08Damage_Construct_3 (0x4ebbe8 _Construct_4 the same): the copy constructor. CKDamage's constructor
// (the vtable only: BUG(original)? CKDamage's three members are not copied), then +0x10..+0x26 copied. No caller in the
// original (only their OPDs; the derived copy constructors call the default constructor 0x4ebce0).
CKS08Damage::CKS08Damage(const CKS08Damage& other) : CKDamage() {
    m_unk26 = other.m_unk26;
    m_fKnockbackForce = other.m_fKnockbackForce;
    m_fKnockbackTime = other.m_fKnockbackTime;
    m_unk18 = other.m_unk18;
    m_unk1c = other.m_unk1c;
    m_ui32DamageType = other.m_ui32DamageType;
    m_unk24 = other.m_unk24;
    m_unk25 = other.m_unk25;
}
