// CKGrpS08WeaponPool.cpp - reconstructed original translation unit 0x26cfa0-0x26d6b8 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CKGrpS08WeaponPool  key 0xb84  category Group  size 0x54  vtable 0xb21b40
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26cfa0  CKGrpS08WeaponPool_Delete
//   [x] 0x26cff0  CKGrpS08WeaponPool_vfB8  (returns 99: undeclared slot, see CKGrpS08WeaponPool.h)
//   [x] 0x26cff8  CKGrpS08WeaponPool_PostLoad  (header)
//   [ ] 0x26d020  RegisterCKGrpS08WeaponPoolClass
//   [ ] 0x26d098  _GLOBAL__I_26d098
//   [x] 0x26d0a8  CKGrpS08WeaponPool_DeleteArray
//   [x] 0x26d148  CKGrpS08WeaponPool_Create
//   [x] 0x26d1c0  CKGrpS08WeaponPool_CreateArray
//   [x] 0x26d290  CKGrpS08WeaponPool_RecursiveRegistration
//   [ ] 0x26d318  CKGrpS08WeaponPool_Save
//   [x] 0x26d340  CKGrpS08WeaponPool_Destroy  (DestroyGroupLists, CKGrpS08WeaponPool.h)
//   [x] 0x26d3a0  CKGrpS08WeaponPool_Load
//
//   [x] 0x9bbe68  CKGrpS08WeaponPool_GetClassType  [inline]
//   [x] 0x9bbe70  CKGrpS08WeaponPool_GetClassID  [inline]
//   [ ] 0x9bbe78  CKGrpS08WeaponPool_vfCC  [inline]
//   [ ] 0x9bbe80  CKGrpS08WeaponPool_vfEC  [inline]
//   [ ] 0x9bbe88  CKGrpS08WeaponPool_IsKindOfClass  [inline]
//   [ ] 0x9bbee0  CKGrpS08WeaponPool_DeletingDestructor  [inline]
//   [ ] 0x9bbf30  CKGrpS08WeaponPool_Destructor  [inline]
#include "Spyro2008/groups/CKGrpS08WeaponPool.h"

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x0026d3a0 CKGrpS08WeaponPool_Load. The floats are read for every type (no type test after the base).
int32_t CKGrpS08WeaponPool::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk34);
    ReadF32LE(file, &m_unk38);
    ReadF32LE(file, &m_unk3c);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk50);
    ReadF32LE(file, &m_unk40);
    ReadF32LE(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    ReadF32LE(file, &m_unk4c);
    return 1;
}

// 0x0026d290 CKGrpS08WeaponPool_RecursiveRegistration (vt+0x24)
void CKGrpS08WeaponPool::RecursiveRegistration(int32_t type) {
    IKBaseGroup::RecursiveRegistration(type);  // 0x00012a68 IKGroup_LevelReset
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
