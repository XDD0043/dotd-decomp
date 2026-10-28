// CKHkHazardousJet.cpp - reconstructed original translation unit 0x49f968-0x4a40d0 (GAME_TOC1, main_toc1), 40 functions, 32 live.
// Primary class: CKHkHazardousJet  key 0x2f42  category Hook  size 0xcc  vtable 0xb284d0
// Other owners: CKHkScrapShower (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x49f968  CKHkHazardousJet_Delete
//   [ ] 0x49f9b8  RegisterCKHkHazardousJetClass
//   [ ] 0x49fa30  _GLOBAL__I_49fa30
//   [ ] 0x49fa40  CKHkHazardousJet_SetDefaultState
//   [ ] 0x49faa0  CKHkHazardousJet_MessageProc
//   [ ] 0x49fc00  CKHkHazardousJet_GetInfo
//   [ ] 0x49fc50  CKHkHazardousJet_UpdateHeroContactTimers_maybe  [dead]
//   [ ] 0x49fdb0  CKHkHazardousJet_LaunchProjectile_maybe
//   [ ] 0x49fff8  CKHkHazardousJet_Resume
//   [ ] 0x4a0020  CKHkHazardousJet_Pause
//   [ ] 0x4a0048  CKHkHazardousJet_Stop
//   [ ] 0x4a0070  CKHkHazardousJet_Start
//   [ ] 0x4a00e0  CKHkHazardousJet_PostLoad
//   [ ] 0x4a0148  CKHkHazardousJet_Save
//   [ ] 0x4a0170  CKHkHazardousJet_RecursiveRegistration
//   [ ] 0x4a0198  CKHkHazardousJet_Destroy
//   [x] 0x4a01c0  CKHkHazardousJet_Construct  [dead]
//   [x] 0x4a0200  CKHkHazardousJet_DeleteArray
//   [ ] 0x4a02a0  CKHkHazardousJet_Destructor_2  [dead]
//   [ ] 0x4a0318  CKHkHazardousJet_DeletingDestructor
//   [ ] 0x4a03a0  CKHkHazardousJet_Destructor
//   [ ] 0x4a0418  CKHkHazardousJet_vfC8
//   [ ] 0x4a0480  CKHkHazardousJet_Construct_2  [dead]
//   [ ] 0x4a04c0  CKHkHazardousJet_OnActivate
//   [x] 0x4a0680  CKHkHazardousJet_CreateArray
//   [x] 0x4a0740  CKHkHazardousJet_Create
//   [x] 0x4a07a0  CKHkHazardousJet_Load
//   [ ] 0x4a1288  CKHkHazardousJet_UpdateLightningTargets_maybe
//   [ ] 0x4a1618  CKHkHazardousJet_ProcessHeroContacts_maybe
//   [ ] 0x4a1ad8  CKHkHazardousJet_AcquireFxBC_maybe  [dead]
//   [ ] 0x4a1d50  CKHkHazardousJet_AcquireFxB8_maybe  [dead]
//   [ ] 0x4a1fc8  CKHkHazardousJet_SetFxC0Active_maybe  [dead]
//   [ ] 0x4a2350  CKHkHazardousJet_StopJetFx_maybe
//   [ ] 0x4a24a8  CKHkHazardousJet_SetJetActive_maybe
//   [ ] 0x4a2eb8  CKHkHazardousJet_vfCC
//   [ ] 0x4a2f40  CKHkHazardousJet_Update
//   [ ] 0x4a3e68  CKHkHazardousJet_OnDeactivate
//   [ ] 0x4a3f40  CKHkHazardousJet_Restart
//   [ ] 0x4a4048  CKHkScrapShower_Delete
//   [ ] 0x4a4098  FUN_004a4098  [dead]
//
//   [ ] 0x9c4de8  CKHkHazardousJet_IsKindOfClass  [inline]
//   [ ] 0x9c4e40  CKHkHazardousJet_GetClassType  [inline]
//   [ ] 0x9c4e48  CKHkHazardousJet_GetClassID  [inline]
#include "k2000/hooks/CKHkHazardousJet.h"

#include "k2000/io/IKFile.h"

// 0x004a07a0 CKHkHazardousJet_Load
int32_t CKHkHazardousJet::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk20);
    for (float& f : m_afUnk64) ReadF32LE(file, &f);
    IKFile_ReadRef(file, &m_pUnk24);
    IKFile_ReadRef(file, &m_pUnk28);
    IKFile_ReadRef(file, &m_pUnk2C);
    IKFile_ReadRef(file, &m_pUnk38);
    IKFile_ReadRef(file, &m_pUnk70);
    IKFile_ReadRef(file, &m_pUnk74);
    IKFile_ReadRef(file, &m_pUnk78);
    ReadU32LE(file, &m_unk7C);
    ReadU32LE(file, &m_unk80);
    ReadU32LE(file, &m_unk3C);
    ReadU32LE(file, &m_unk40);
    ReadU32LE(file, &m_unk44);
    ReadU32LE(file, &m_unk4C);
    ReadU32LE(file, &m_unk50);
    ReadU32LE(file, &m_unk54);
    ReadU8(file, &m_unk58);
    ReadU32LE(file, &m_unk5C);
    ReadU32LE(file, &m_unk60);
    ReadU32LE(file, &m_unk48);
    ReadU32LE(file, &m_unk84);
    ReadU32LE(file, &m_unk88);
    ReadU32LE(file, &m_unk8C);
    ReadU32LE(file, &m_unk90);
    IKFile_ReadRef(file, &m_pUnk30);
    IKFile_ReadRef(file, &m_pUnk34);
    m_tsUnk94.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk9C.Load(file, K_LEVEL_PLATEFORMS);
    ReadU8(file, &m_unkA4);
    ReadU8(file, &m_unkA5);
    ReadU8(file, &m_unkA6);
    ReadU8(file, &m_unkA7);
    ReadU32LE(file, &m_unkA8);
    return 1;
}
