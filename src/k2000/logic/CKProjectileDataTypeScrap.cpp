// CKProjectileDataTypeScrap.cpp - reconstructed original translation unit 0x591f58-0x5929d8 (GAME_TOC2, main_toc2), 16 functions, 14 live.
// Primary class: CKProjectileDataTypeScrap  key 0xa6cc  category Logic  size ?  vtable 0xb2e370
// Other owners: CKProjectileTypeScrap (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x591f58  CKProjectileDataTypeScrap_Delete
//   [ ] 0x591fa8  CKProjectileDataTypeScrap_Save
//   [ ] 0x591fb0  RegisterCKProjectileDataTypeScrapClass
//   [ ] 0x592028  _GLOBAL__I_592028
//   [x] 0x592038  CKProjectileDataTypeScrap_DeleteArray
//   [x] 0x5920e0  CKProjectileDataTypeScrap_Create
//   [x] 0x592128  CKProjectileDataTypeScrap_CreateArray
//   [ ] 0x5921d0  CKProjectileDataTypeScrap_PostLoad
//   [ ] 0x5921d8  CKProjectileDataTypeScrap_Destroy
//   [ ] 0x5921e0  CKProjectileDataTypeScrap_RecursiveRegistration
//   [x] 0x592328  CKProjectileDataTypeScrap_Load
//   [x] 0x5928a8  CKProjectileTypeScrap_Delete
//   [ ] 0x5928f8  CKProjectileTypeScrap_vf98
//   [ ] 0x592900  CKProjectileTypeScrap_vf9C
//   [ ] 0x592908  CKProjectileTypeScrap_AddFxEmitPointAndStart_maybe  [dead]
//   [ ] 0x5929d0  KStub_Nop_5929d0  [dead]
//
//   [ ] 0x9cb518  CKProjectileDataTypeScrap_GetClassType  [inline]
//   [ ] 0x9cb520  CKProjectileDataTypeScrap_GetClassID  [inline]
//   [ ] 0x9cb528  CKProjectileDataTypeScrap_Destructor  [inline]
//   [ ] 0x9cb568  CKProjectileDataTypeScrap_IsKindOfClass  [inline]
//   [ ] 0x9cb5b0  CKProjectileDataTypeScrap_DeletingDestructor  [inline]
#include "k2000/logic/CKProjectileDataTypeScrap.h"

#include "k2000/io/IKFile.h"

// 0x00592328 CKProjectileDataTypeScrap_Load: level data only, 67 bytes (fields out of address order as in
// the original).
int32_t CKProjectileDataTypeScrap::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk04);
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk14);
    ReadF32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk30);
    ReadU8(file, &m_unk34);
    ReadU16LE(file, &m_unk36);
    ReadU32LE(file, &m_unk38);
    IKFile_ReadRef(file, &m_unk44);
    IKFile_ReadRef(file, &m_unk3c);
    IKFile_ReadRef(file, &m_unk40);
    return 1;
}
