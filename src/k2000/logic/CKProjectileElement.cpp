// CKProjectileElement.cpp - reconstructed original translation unit 0x3bc818-0x3c1f38 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKProjectileElement  key 0x934c  category Logic  size 0x214  vtable 0xb23dd8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3bc818  CKProjectileElement_Delete
//   [x] 0x3bc868  CKProjectileElement_Construct
//   [ ] 0x3bc878  CKProjectileElement_Construct_2  [dead]
//   [ ] 0x3bc888  CKProjectileElement_GetAbilityId
//   [ ] 0x3bc890  CKProjectileElement_GetFamilyId
//   [ ] 0x3bc898  CKProjectileElement_Start
//   [ ] 0x3bca10  CKProjectileElement_Stop
//   [ ] 0x3bca60  CKProjectileElement_End
//   [ ] 0x3bcb48  CKProjectileElement_ApplyHeroControl
//   [ ] 0x3bd1b0  CKProjectileElement_ResetRuntime
//   [ ] 0x3bd1f8  CKProjectileElement_SetAimControl_maybe
//   [ ] 0x3bd598  CKProjectileElement_ApplyDamageParams
//   [x] 0x3bdbe8  CKProjectileElement_DeleteArray
//   [ ] 0x3bdc88  CKProjectileElement_StartEmitterFx
//   [ ] 0x3bdf50  RegisterCKProjectileElementClass
//   [ ] 0x3bdfd8  _GLOBAL__D_3bdfd8
//   [ ] 0x3bdfe8  _GLOBAL__I_3bdfe8
//   [ ] 0x3bdff8  CKProjectileElement_GetLaunchPosDir_maybe
//   [ ] 0x3be178  CKProjectileElement_Update
//   [x] 0x3bf1b8  CKProjectileElement_CreateArray
//   [x] 0x3bf248  CKProjectileElement_Create
//   [ ] 0x3bf280  CKProjectileElement_PostLoad
//   [ ] 0x3bf2c8  CKProjectileElement_RecursiveRegistration
//   [ ] 0x3bf2d0  CKProjectileElement_Destroy
//   [ ] 0x3bf2d8  CKProjectileElement_Destructor
//   [ ] 0x3bf2f8  CKProjectileElement_BaseDestructor
//   [ ] 0x3bf318  CKProjectileElement_DeletingDestructor
//   [x] 0x3bf360  CKProjectileElement_Load
//   [ ] 0x3c0a98  CKProjectileElement_Save
//
//   [ ] 0x9bff30  CKProjectileElement_UpdateCharge  [inline]
//   [ ] 0x9c0158  CKProjectileElement_GetClassType  [inline]
//   [ ] 0x9c0160  CKProjectileElement_GetClassID  [inline]
//   [ ] 0x9c0168  CKProjectileElement_Fire  [inline]
//   [ ] 0x9c0170  CKProjectileElement_IsChargeDisabled_maybe  [inline]
//   [ ] 0x9c0178  CKProjectileElement_IsKindOfClass  [inline]
#include "k2000/logic/CKProjectileElement.h"

#include "k2000/io/IKFile.h"

// 0x003bf360 CKProjectileElement_Load: level data only (type 0 = K_LEVEL_PLATEFORMS; any other type reads
// nothing). Three levels of per-level parameters (a 3-iteration loop), then the shared settings and three
// object references. 482 bytes.
int32_t CKProjectileElement::Load(IKFile* file, int32_t type) {
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        ReadS32LE(file, &m_unk08[i]);
        ReadU32LE(file, &m_unk38[i]);
        ReadS32LE(file, &m_unk50[i]);
        ReadF32LE(file, &m_unk68[i]);
        ReadF32LE(file, &m_unk88[i]);
        ReadF32LE(file, &m_unka0[i]);
        ReadU32LE(file, &m_unkb8[i]);
        ReadF32LE(file, &m_unkd0[i]);
        ReadU32LE(file, &m_unke8[i]);
        ReadU32LE(file, &m_unk100[i]);
        ReadF32LE(file, &m_unk118[i]);
        ReadU32LE(file, &m_unk130[i]);
        ReadU32LE(file, &m_unk148[i]);
        ReadU8(file, &m_unk178[i]);
        ReadU8(file, &m_unk17e[i]);
        ReadS32LE(file, &m_unk14[i]);
        ReadS32LE(file, &m_unk5c[i]);
        ReadF32LE(file, &m_unk94[i]);
        ReadF32LE(file, &m_unkac[i]);
        ReadU32LE(file, &m_unkc4[i]);
        ReadU32LE(file, &m_unkdc[i]);
        ReadU32LE(file, &m_unkf4[i]);
        ReadU32LE(file, &m_unk10c[i]);
        ReadF32LE(file, &m_unk124[i]);
        ReadU32LE(file, &m_unk13c[i]);
        ReadU32LE(file, &m_unk154[i]);
        ReadU8(file, &m_unk17b[i]);
        ReadU8(file, &m_unk181[i]);
    }
    ReadU8(file, &m_unk194);
    ReadU8(file, &m_unk195);
    ReadU8(file, &m_unk196);
    ReadF32LE(file, &m_unk198);
    ReadF32LE(file, &m_unk19c);
    ReadF32LE(file, &m_unk1ac);
    ReadU8(file, &m_unk1a0);
    ReadU8(file, &m_unk1a1);
    ReadU8(file, &m_unk1a2);
    ReadF32LE(file, &m_unk1a4);
    ReadF32LE(file, &m_unk1a8);
    ReadF32LE(file, &m_unk1b0);
    ReadF32LE(file, &m_unk74);
    ReadU8(file, &m_unk1d8);
    ReadU8(file, &m_unk1d9);
    ReadU8(file, &m_unk1db);
    ReadU8(file, &m_unk1dc);
    ReadF32LE(file, &m_unk1e0);
    ReadF32LE(file, &m_unk1e4);
    ReadU8(file, &m_unk1b4);
    ReadU8(file, &m_unk1b5);
    ReadF32LE(file, &m_unk1b8);
    ReadF32LE(file, &m_unk1bc);
    ReadU32LE(file, &m_unk160);
    ReadU32LE(file, &m_unk16c);
    ReadU32LE(file, &m_unk164);
    ReadU32LE(file, &m_unk170);
    ReadU32LE(file, &m_unk168);
    ReadU32LE(file, &m_unk174);
    IKFile_ReadRef(file, &m_unk20c);
    ReadU8(file, &m_unk1c0);
    ReadU8(file, &m_unk1c1);
    ReadU8(file, &m_unk1c2);
    ReadF32LE(file, &m_unk1c4);
    ReadF32LE(file, &m_unk1c8);
    ReadF32LE(file, &m_unk1cc);
    ReadU8(file, &m_unk1d0);
    ReadF32LE(file, &m_unk1d4);
    ReadU8(file, &m_unk1da);
    ReadU8(file, &m_unk1dd);
    ReadF32LE(file, &m_unk1e8);
    IKFile_ReadRef(file, &m_unk184);
    ReadU32LEWords(file, m_unk188, 3);
    ReadF32LE(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    ReadF32LE(file, &m_unk4c);
    IKFile_ReadRef(file, &m_unk1ec);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk34);
    ReadU32LE(file, &m_unk78);
    ReadU32LE(file, &m_unk80);
    ReadU32LE(file, &m_unk7c);
    ReadU32LE(file, &m_unk84);
    return 1;
}
