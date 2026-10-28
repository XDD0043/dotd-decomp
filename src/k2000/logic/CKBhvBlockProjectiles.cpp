// CKBhvBlockProjectiles.cpp - reconstructed original translation unit 0x5c3088-0x5c4e50 (GAME_TOC2, main_toc2), 28 functions, 23 live.
// Primary class: CKBhvBlockProjectiles  key 0xa7cc  category Logic  size ?  vtable 0xb2fc60
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c3088  CKBhvBlockProjectiles_Delete
//   [ ] 0x5c30d8  CKBhvBlockProjectiles_FindTarget_maybe  [dead]
//   [ ] 0x5c3228  CKBhvBlockProjectiles_IsTargetValid_maybe  [dead]
//   [ ] 0x5c32d8  CKBhvBlockProjectiles_LaunchAtTarget_maybe
//   [ ] 0x5c3428  CKBhvBlockProjectiles_IsPlayingSecondAnim_maybe  [dead]
//   [ ] 0x5c34b0  CKBhvBlockProjectiles_FireOnAnimMark_maybe
//   [ ] 0x5c3718  CKBhvBlockProjectiles_PlayFirstAnim_maybe  [dead]
//   [ ] 0x5c3820  CKBhvBlockProjectiles_PlaySecondAnim_maybe  [dead]
//   [ ] 0x5c3928  CKBhvBlockProjectiles_GetRandomizedInterval_maybe
//   [ ] 0x5c3988  CKBhvBlockProjectiles_vf68
//   [ ] 0x5c39f8  CKBhvBlockProjectiles_Save
//   [ ] 0x5c3a20  CKBhvBlockProjectiles_RecursiveRegistration
//   [ ] 0x5c3a48  CKBhvBlockProjectiles_Destroy
//   [ ] 0x5c3a70  CKBhvBlockProjectiles_Construct_2
//   [x] 0x5c3aa8  CKBhvBlockProjectiles_Construct
//   [x] 0x5c3ae0  CKBhvBlockProjectiles_DeleteArray
//   [ ] 0x5c3b80  CKBhvBlockProjectiles_BaseDestructor
//   [ ] 0x5c3bb0  RegisterCKBhvBlockProjectilesClass
//   [ ] 0x5c3c38  _GLOBAL__D_5c3c38
//   [ ] 0x5c3c48  _GLOBAL__I_5c3c48
//   [ ] 0x5c3c58  CKBhvBlockProjectiles_DeletingDestructor
//   [ ] 0x5c3ca0  CKBhvBlockProjectiles_Destructor
//   [x] 0x5c3cd0  CKBhvBlockProjectiles_CreateArray
//   [x] 0x5c3d80  CKBhvBlockProjectiles_Create
//   [ ] 0x5c3dd8  CKBhvBlockProjectiles_FaceTarget_maybe
//   [ ] 0x5c3f88  CKBhvBlockProjectiles_Update_maybe
//   [ ] 0x5c4470  CKBhvBlockProjectiles_vf64
//   [x] 0x5c4850  CKBhvBlockProjectiles_Load
//
//   [ ] 0x9cd408  CKBhvBlockProjectiles_IsKindOfClass  [inline]
//   [ ] 0x9cd440  CKBhvBlockProjectiles_GetClassType  [inline]
//   [ ] 0x9cd448  CKBhvBlockProjectiles_GetClassID  [inline]
#include "k2000/logic/CKBhvBlockProjectiles.h"

#include "k2000/io/IKFile.h"

// 0x005c4850 CKBhvBlockProjectiles_Load: the base's Load, then (level data only) the fields in the file's
// order.
int32_t CKBhvBlockProjectiles::Load(IKFile* file, int32_t type) {
    KBase9C8C::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk0c);
        IKFile_ReadRef(file, &m_unk2c);
        ReadU32LE(file, &m_unk14);
        ReadU32LE(file, &m_unk10);
        ReadU32LE(file, &m_unk1c);
        ReadU32LE(file, &m_unk20);
        IKFile_ReadRef(file, &m_unk28);
        IKFile_ReadRef(file, &m_unk30);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk38), 3);
        IKFile_ReadRef(file, &m_unk5c);
        IKFile_ReadRef(file, &m_unk44);
        ReadF32LE(file, &m_unk60);
        IKFile_ReadRef(file, &m_unk08);
        IKFile_ReadRef(file, &m_unk04);
        IKFile_ReadRef(file, &m_unk64);
    }
    return 1;
}
