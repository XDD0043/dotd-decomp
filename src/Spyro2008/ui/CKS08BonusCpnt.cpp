// CKS08BonusCpnt.cpp - reconstructed original translation unit 0x5b9f08-0x5ba9f8 (GAME_TOC2, main_toc2), 11 functions, 10 live.
// Primary owner: CKS08BonusCpnt (not a registered class)
// Other owners: RegisterCKS08BonusCpntClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5b9f08  CKS08BonusCpnt_Destroy  (the Delete factory: DOTD_DECLARE_FACTORIES(CKS08BonusCpnt))
//   [x] 0x5b9f58  CKS08BonusCpnt_ClearReferences  (empty: IKBaseClass's Destroy)
//   [ ] 0x5b9f60  CKS08BonusCpnt_Save
//   [ ] 0x5b9f68  RegisterCKS08BonusCpntClass
//   [ ] 0x5b9fe0  _GLOBAL__I_5b9fe0
//   [x] 0x5b9ff0  CKS08BonusCpnt_DestroyArray  (vtable-only destructors (implicit here))
//   [x] 0x5ba090  CKS08BonusCpnt_Create
//   [ ] 0x5ba0d8  CKS08BonusCpnt_GetSplineLockLaunchData_maybe  [dead]
//   [x] 0x5ba170  CKS08BonusCpnt_CreateArray
//   [x] 0x5ba210  CKS08BonusCpnt_LevelReset  (RecursiveRegistration)
//   [x] 0x5ba2f8  CKS08BonusCpnt_Load
//
//   [ ] 0x9cc988  KBase606_vf24  [inline]
//   [x] 0x9cca58  CKS08BonusCpnt_GetClassGroup  [inline]
//   [x] 0x9cca60  CKS08BonusCpnt_GetClassId  [inline]
//   [ ] 0x9cca68  KBase606_DeletingDestructor  [inline]
//   [x] 0x9ccab0  KBase606_Destructor  [inline]  (vtable only (implicit))
//   [ ] 0x9ccae0  CKS08BonusCpnt_DeletingDestructor  [inline]
//   [x] 0x9ccb38  CKS08BonusCpnt_IsKindOf  [inline]
//   [x] 0x9ccb70  CKS08BonusCpnt_Destructor  [inline]  (vtable only (implicit))
//   [ ] 0x9ccbb0  KBase606_vf28  [inline]
//   [ ] 0x9ccd00  KBase606_vf2C  [inline]
#include "Spyro2008/ui/CKS08BonusCpnt.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x005ba2f8 CKS08BonusCpnt_Load. Types 4..7 (the save restores) read nothing; the references only for
// type 0.
int32_t CKS08BonusCpnt::Load(IKFile* file, int32_t type) {
    if (static_cast<uint32_t>(type) - 4u <= 3u) return 1;
    ReadF32LE(file, &m_fSquareCatchDist);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pSoundDictionary);
        ReadF32LE(file, &m_fSpawnedLifeExpectancy);
        IKFile_ReadRef(file, &m_pProjectileAccessor);
    } else {
        ReadF32LE(file, &m_fSpawnedLifeExpectancy);
    }
    ReadF32LE(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    for (float& v : m_unk14) ReadF32LE(file, &v);
    ReadU32LE(file, &m_unk2c);
    // +0x30, +0x34, then one 8-byte read for +0x38/+0x3c and one for +0x40/+0x44 (each word swapped).
    for (float& v : m_unk30) ReadF32LE(file, &v);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    for (float& v : m_unk54) ReadF32LE(file, &v);
    ReadU8(file, &m_bFloatingOrbMode);
    return 1;
}

// 0x005ba210 CKS08BonusCpnt_LevelReset (vt+0x24)
void CKS08BonusCpnt::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) {
        g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
        if (type == 0) m_pSoundDictionary->RecursiveRegistration(0);
    }
    m_pProjectileAccessor->RecursiveRegistration(type);
}
