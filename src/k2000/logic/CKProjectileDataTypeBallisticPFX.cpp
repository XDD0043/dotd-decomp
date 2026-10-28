// CKProjectileDataTypeBallisticPFX.cpp - reconstructed original translation unit 0x5854c8-0x586258 (GAME_TOC2, main_toc2), 13 functions, 12 live.
// Primary class: CKProjectileDataTypeBallisticPFX  key 0xa5cc  category Logic  size ?  vtable 0xb2e158
// Other owners: IKComponent (1), CKProjectileTypeBallisticPFX (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5854c8  CKProjectileDataTypeBallisticPFX_Delete
//   [ ] 0x585518  CKProjectileDataTypeBallisticPFX_Save
//   [ ] 0x585520  RegisterCKProjectileDataTypeBallisticPFXClass
//   [ ] 0x585598  _GLOBAL__I_585598
//   [x] 0x5855a8  CKProjectileDataTypeBallisticPFX_DeleteArray
//   [x] 0x585648  CKProjectileDataTypeBallisticPFX_Create
//   [x] 0x585690  CKProjectileDataTypeBallisticPFX_CreateArray
//   [ ] 0x585730  CKProjectileDataTypeBallisticPFX_PostLoad
//   [ ] 0x585738  CKProjectileDataTypeBallisticPFX_Destroy
//   [ ] 0x585740  IKComponent_RecursiveRegistration
//   [x] 0x585928  CKProjectileDataTypeBallisticPFX_Load
//   [x] 0x5861e0  CKProjectileTypeBallisticPFX_Delete
//   [ ] 0x586230  FUN_00586230  [dead]
//
//   [ ] 0x991218  IKComponent_IsKindOf  [inline]
//   [ ] 0x9cb210  KBaseA58C_vf24  [inline]
//   [ ] 0x9cb270  CKProjectileDataTypeBallisticPFX_GetClassType  [inline]
//   [ ] 0x9cb278  CKProjectileDataTypeBallisticPFX_GetClassID  [inline]
//   [ ] 0x9cb280  KBaseA58C_vf4  [inline]
//   [ ] 0x9cb2c8  KBaseA58C_Destructor  [inline]
//   [ ] 0x9cb2f8  CKProjectileDataTypeBallisticPFX_Destructor  [inline]
//   [ ] 0x9cb338  CKProjectileDataTypeBallisticPFX_IsKindOfClass  [inline]
//   [ ] 0x9cb380  CKProjectileDataTypeBallisticPFX_DeletingDestructor  [inline]
#include "k2000/logic/CKProjectileDataTypeBallisticPFX.h"

#include "k2000/io/IKFile.h"

// 0x00585928 CKProjectileDataTypeBallisticPFX_Load: level data only, 106 bytes (fields out of address order
// as in the original).
int32_t CKProjectileDataTypeBallisticPFX::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk34);
    ReadF32LE(file, &m_unk38);
    ReadF32LE(file, &m_unk3c);
    ReadF32LE(file, &m_unk40);
    ReadU8(file, &m_unk44);
    ReadU8(file, &m_unk45);
    ReadU32LE(file, &m_unk48);
    ReadU8(file, &m_unk4c);
    ReadU16LE(file, &m_unk4e);
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    ReadF32LE(file, &m_unk5c);
    ReadU32LE(file, &m_unk50);
    ReadF32LE(file, &m_unk64);
    ReadF32LE(file, &m_unk68);
    ReadF32LE(file, &m_unk6c);
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk0c);
    IKFile_ReadRef(file, &m_unk10);
    IKFile_ReadRef(file, &m_unk14);
    IKFile_ReadRef(file, &m_unk18);
    ReadU32LE(file, &m_unk70);
    ReadU32LE(file, &m_unk60);
    ReadU8(file, &m_unk2c);
    return 1;
}
