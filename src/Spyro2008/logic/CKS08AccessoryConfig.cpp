// CKS08AccessoryConfig.cpp - reconstructed original translation unit 0x2c6d50-0x2c74d0 (GAME_TOC1, main_toc1), 19 functions, 13 live.
// Primary class: CKS08AccessoryConfig  key 0xa18c  category Logic  size 0x30  vtable 0xb228a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2c6d50  CKS08AccessoryConfig_Delete
//   [x] 0x2c6da0  CKS08AccessoryConfig_Construct  [dead]
//   [ ] 0x2c6db0  CKS08AccessoryConfig_CopyConstruct_maybe  [dead]
//   [ ] 0x2c6e10  CKS08AccessoryConfig_Assign_maybe  [dead]
//   [ ] 0x2c6e78  RegisterCKS08AccessoryConfigClass
//   [ ] 0x2c6ef0  _GLOBAL__I_2c6ef0
//   [x] 0x2c6f00  CKS08AccessoryConfig_DeleteArray
//   [ ] 0x2c6fa8  CKS08AccessoryConfig_Construct_2  [dead]
//   [ ] 0x2c6fb8  CKS08AccessoryConfig_CopyConstruct_2_maybe  [dead]
//   [x] 0x2c7018  CKS08AccessoryConfig_CreateArray
//   [x] 0x2c70b0  CKS08AccessoryConfig_Create
//   [ ] 0x2c70e8  CKS08AccessoryConfig_Save
//   [ ] 0x2c70f0  CKS08AccessoryConfig_PostLoad
//   [ ] 0x2c70f8  CKS08AccessoryConfig_RecursiveRegistration
//   [ ] 0x2c7100  CKS08AccessoryConfig_Destroy
//   [x] 0x2c7108  CKS08AccessoryConfig_Load
//   [ ] 0x2c7460  CKS08AccessoryConfig_DeletingDestructor
//   [ ] 0x2c74a0  CKS08AccessoryConfig_Destructor
//   [ ] 0x2c74b8  CKS08AccessoryConfig_Destructor_2  [dead]
//
//   [ ] 0x9bd0a8  CKS08AccessoryConfig_GetClassType  [inline]
//   [ ] 0x9bd0b0  CKS08AccessoryConfig_GetClassID  [inline]
//   [ ] 0x9bd0b8  CKS08AccessoryConfig_IsKindOfClass  [inline]
#include "Spyro2008/logic/CKS08AccessoryConfig.h"

#include "k2000/io/IKFile.h"

// 0x002c7108 CKS08AccessoryConfig_Load: eleven words in member order, whatever the type.
int32_t CKS08AccessoryConfig::Load(IKFile* file, int32_t /*type*/) {
    ReadF32LE(file, &m_unk04);
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    ReadF32LE(file, &m_unk18);
    ReadS32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk2c);
    return 1;
}
