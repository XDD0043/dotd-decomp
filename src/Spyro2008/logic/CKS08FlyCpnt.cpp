// CKS08FlyCpnt.cpp - reconstructed original translation unit 0x2b85e8-0x2bc640 (GAME_TOC1, main_toc1), 25 functions, 13 live.
// Primary class: CKS08FlyCpnt  key 0x9a8c  category Logic  size 0x84  vtable 0xb225d8
// Other owners: NavSectors (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b85e8  CKS08FlyCpnt_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x2b8638  CKS08FlyCpnt_Construct  [dead]
//   [ ] 0x2b86c8  CKS08FlyCpnt_Assign  [dead]
//   [ ] 0x2b8788  CKS08FlyCpnt_AddToVec3At4_maybe  [dead]
//   [ ] 0x2b87c0  RegisterCKS08FlyCpntClass
//   [ ] 0x2b8838  _GLOBAL__I_2b8838
//   [ ] 0x2b8848  NavSectors_IsPointInAllowedSector_maybe  [dead]
//   [x] 0x2b8a20  CKS08FlyCpnt_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x2b8ac8  CKS08FlyCpnt_Construct_2  [dead]
//   [ ] 0x2b8b58  CKS08FlyCpnt_CopyConstruct  [dead]
//   [ ] 0x2b8c20  CKS08FlyCpnt_CopyConstruct_2  [dead]
//   [ ] 0x2b8ce8  CKS08FlyCpnt_ZeroVec3At4_maybe  [dead]
//   [ ] 0x2b8d00  CKS08FlyCpnt_Save
//   [x] 0x2b8d08  CKS08FlyCpnt_PostLoad  (the IKSerializable default: 1)
//   [x] 0x2b8d10  CKS08FlyCpnt_RecursiveRegistration  (the IKSerializable default)
//   [x] 0x2b8d18  CKS08FlyCpnt_Destroy  (empty: the IKSerializable default)
//   [x] 0x2b8d20  CKS08FlyCpnt_CreateArray  (DOTD_DECLARE_FACTORIES, the header constructor)
//   [x] 0x2b8e48  CKS08FlyCpnt_Create  (DOTD_DECLARE_FACTORIES, the header constructor)
//   [x] 0x2b8f00  CKS08FlyCpnt_Destructor  (the destructor)
//   [ ] 0x2b8f18  CKS08FlyCpnt_Destructor_2  [dead]
//   [x] 0x2b8f30  CKS08FlyCpnt_DeletingDestructor  (the destructor)
//   [x] 0x2b8f70  CKS08FlyCpnt_Load
//   [ ] 0x2b94d8  FUN_002b94d8  [dead]
//   [ ] 0x2b9b18  FUN_002b9b18  [dead]
//   [ ] 0x2bbcc8  FUN_002bbcc8  [dead]
//
//   [ ] 0x9bcf90  CKS08FlyCpnt_GetClassType  [inline]
//   [ ] 0x9bcf98  CKS08FlyCpnt_GetClassID  [inline]
//   [ ] 0x9bcfa0  CKS08FlyCpnt_IsKindOfClass  [inline]
#include "Spyro2008/logic/CKS08FlyCpnt.h"

#include "k2000/io/IKFile.h"

// 0x002b8f70 CKS08FlyCpnt_Load: the level type only; eighteen words in the file's order.
int32_t CKS08FlyCpnt::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        ReadF32LE(file, &m_unk10);
        ReadF32LE(file, &m_unk14);
        ReadF32LE(file, &m_unk44);
        ReadF32LE(file, &m_unk40);
        ReadF32LE(file, &m_unk3c);
        ReadF32LE(file, &m_unk48);
        ReadF32LE(file, &m_unk4c);
        ReadF32LE(file, &m_unk18);
        ReadF32LE(file, &m_unk1c);
        ReadF32LE(file, &m_unk20);
        ReadF32LE(file, &m_unk24);
        ReadF32LE(file, &m_unk28);
        ReadF32LE(file, &m_unk2c);
        ReadF32LE(file, &m_unk30);
        ReadF32LE(file, &m_unk34);
        ReadF32LE(file, &m_unk38);
        ReadF32LE(file, &m_unk78);
        ReadS32LE(file, &m_unk7c);
    }
    return 1;
}
