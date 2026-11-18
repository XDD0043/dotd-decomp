// Reconstructed original translation unit: 0x599ea8-0x59a370 (GAME_TOC2, main_toc2), 10 functions, 10 live.
// Primary class: CKProjectileDataTypeFromExplosion  key 0xa68c  category Logic  size ?  vtable 0xb2e5f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x599ea8  CKProjectileDataTypeFromExplosion_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x599ef8  CKProjectileDataTypeFromExplosion_Save
//   [ ] 0x599f00  RegisterCKProjectileDataTypeFromExplosionClass
//   [ ] 0x599f78  _GLOBAL__I_599f78
//   [x] 0x599f88  CKProjectileDataTypeFromExplosion_Destroy
//   [x] 0x599fb0  CKProjectileDataTypeFromExplosion_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x59a050  CKProjectileDataTypeFromExplosion_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x59a098  CKProjectileDataTypeFromExplosion_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x59a138  CKProjectileDataTypeFromExplosion_PostLoad  (returns 1)
//   [x] 0x59a140  CKProjectileDataTypeFromExplosion_Load
//
//   [x] 0x9cb810  CKProjectileDataTypeFromExplosion_IsKindOfClass  [inline]
//   [x] 0x9cb870  CKProjectileDataTypeFromExplosion_GetClassType  [inline]
//   [x] 0x9cb878  CKProjectileDataTypeFromExplosion_GetClassID  [inline]
//   [ ] 0x9cb880  CKProjectileDataTypeFromExplosion_Destructor  [inline]
//   [ ] 0x9cb8c8  CKProjectileDataTypeFromExplosion_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKProjectileDataTypeFromExplosion.h"

#include "k2000/io/IKFile.h"

// 0x0059a140 CKProjectileDataTypeFromExplosion_Load: the base's, then (level files) the reference and five words.
int32_t CKProjectileDataTypeFromExplosion::Load(IKFile* file, int32_t type) {
    CKProjectileDataTypeBallisticPFX::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk74);
    ReadF32LE(file, &m_unk78);
    ReadF32LE(file, &m_unk7c);
    ReadF32LE(file, &m_unk80);
    ReadF32LE(file, &m_unk84);
    ReadF32LE(file, &m_unk88);
    return 1;
}
