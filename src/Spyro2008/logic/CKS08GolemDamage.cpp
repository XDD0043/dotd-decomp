// CKS08GolemDamage.cpp - reconstructed original translation unit 0x4c4a00-0x4c4f58 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CKS08GolemDamage  key 0xad4c  category Logic  size 0x34  vtable 0xb29390
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4c4a00  CKS08GolemDamage_Delete
//   [ ] 0x4c4a50  RegisterCKS08GolemDamageClass
//   [ ] 0x4c4ac8  _GLOBAL__I_4c4ac8
//   [x] 0x4c4ad8  CKS08GolemDamage_Load
//   [ ] 0x4c4c10  CKS08GolemDamage_Save
//   [x] 0x4c4c38  CKS08GolemDamage_RecursiveRegistration  (CKS08Damage's (CKDamage's: nothing registered), then 1)
//   [x] 0x4c4c60  CKS08GolemDamage_Destroy  (inherited: CKS08Damage_Destroy)
//   [x] 0x4c4c88  CKS08GolemDamage_DeletingDestructor  (the destructor; delete)
//   [x] 0x4c4cd0  CKS08GolemDamage_Destructor  (CKS08Damage's, inherited: nothing of its own)
//   [x] 0x4c4d00  CKS08GolemDamage_DestructBody  (C++ destructor chain: vtable stores, then CKS08Damage_BaseDestructor)
//   [x] 0x4c4d30  CKS08GolemDamage_Construct  [dead]
//   [ ] 0x4c4d68  CKS08GolemDamage_Construct_2  [dead]
//   [x] 0x4c4da0  CKS08GolemDamage_DeleteArray
//   [x] 0x4c4e40  CKS08GolemDamage_Create
//   [x] 0x4c4e98  CKS08GolemDamage_CreateArray
//   [x] 0x4c4f48  KStub_Nop_4c4f48  (GolemPhaseCondTimer vt+0x08 Update: empty, the base's (k2000/misc/GolemPhaseCondAnd.h))
//   [x] 0x4c4f50  KStub_Nop_4c4f50  (GolemPhaseCondTimer vt+0x0c OnStart: empty, the base's (k2000/misc/GolemPhaseCondAnd.h))
//
//   [ ] 0x9c57c0  CKS08GolemDamage_IsKindOfClass  [inline]
//   [ ] 0x9c5810  CKS08GolemDamage_GetClassType  [inline]
//   [ ] 0x9c5818  CKS08GolemDamage_GetClassID  [inline]
//   [ ] 0x9c5820  KStub_Nop_9c5820  [inline]
//   [ ] 0x9c5828  KStub_Nop_9c5828  [inline]
//   [ ] 0x9c5830  KStub_Return1_9c5830  [inline]
//   [ ] 0x9c5838  KStub_Nop_9c5838  [inline]
//   [ ] 0x9c5840  KStub_Nop_9c5840  [inline]
#include "Spyro2008/logic/CKS08GolemDamage.h"

#include "k2000/io/IKFile.h"

// 0x004c4ad8 CKS08GolemDamage_Load: CKS08Damage's data, then (level data only) a reference, a word, a byte.
int32_t CKS08GolemDamage::Load(IKFile* file, int32_t type) {
    CKS08Damage::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk28);
        ReadU32LE(file, &m_unk2c);
        ReadU8(file, &m_unk30);
    }
    return 1;
}
