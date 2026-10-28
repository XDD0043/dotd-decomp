// CKEarthMissile.cpp - reconstructed original translation unit 0x3928a0-0x395018 (GAME_TOC1, main_toc1), 25 functions, 25 live.
// Primary class: CKEarthMissile  key 0x938c  category Logic  size 0x27c  vtable 0xb23758
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3928a0  CKEarthMissile_Delete
//   [ ] 0x3928f0  CKEarthMissile_GetAbilityId
//   [ ] 0x3928f8  CKEarthMissile_IsChargeDisabled_maybe
//   [ ] 0x392918  CKEarthMissile_ResetRuntime
//   [ ] 0x392960  CKEarthMissile_Update
//   [ ] 0x3929c8  CKEarthMissile_Start
//   [ ] 0x392a10  CKEarthMissile_PostLoad
//   [ ] 0x392a78  CKEarthMissile_RecursiveRegistration
//   [ ] 0x392aa0  CKEarthMissile_Destroy
//   [x] 0x392ac8  CKEarthMissile_Construct
//   [x] 0x392b00  CKEarthMissile_DeleteArray
//   [ ] 0x392ba0  CKEarthMissile_DeletingDestructor
//   [ ] 0x392be8  CKEarthMissile_Destructor
//   [ ] 0x392c18  CKEarthMissile_DestructBody
//   [ ] 0x392c48  RegisterCKEarthMissileClass
//   [ ] 0x392cd0  _GLOBAL__D_392cd0
//   [ ] 0x392ce0  _GLOBAL__I_392ce0
//   [ ] 0x392cf0  CKEarthMissile_Construct_2
//   [ ] 0x392d28  CKEarthMissile_End
//   [x] 0x392e40  CKEarthMissile_Create
//   [x] 0x392e98  CKEarthMissile_CreateArray
//   [ ] 0x392f48  CKEarthMissile_Fire
//   [ ] 0x393538  CKEarthMissile_UpdateCharge
//   [ ] 0x393fc8  CKEarthMissile_Save
//   [x] 0x394778  CKEarthMissile_Load
//
//   [ ] 0x9bfb78  CKEarthMissile_IsKindOfClass  [inline]
//   [ ] 0x9bfbc8  CKEarthMissile_GetClassType  [inline]
//   [ ] 0x9bfbd0  CKEarthMissile_GetClassID  [inline]
//   [ ] 0x9bfbd8  CKEarthMissile_StartEmitterFx  [inline]
#include "k2000/logic/CKEarthMissile.h"

#include "k2000/io/IKFile.h"

// 0x00394778 CKEarthMissile_Load: CKProjectileElement's data, then (level data only) 96 bytes: object
// references and floats (the original's reads are unrolled; the loops keep its order).
int32_t CKEarthMissile::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        IKFile_ReadRef(file, &m_unk22c[i]);
        IKFile_ReadRef(file, &m_unk238[i]);
    }
    for (int32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_unk214[i]);
        ReadF32LE(file, &m_unk220[i]);
    }
    IKFile_ReadRef(file, &m_unk244);
    IKFile_ReadRef(file, &m_unk248);
    IKFile_ReadRef(file, &m_unk24c);
    ReadU32LE(file, &m_unk250);
    ReadF32LE(file, &m_unk254);
    ReadU32LE(file, &m_unk258);
    IKFile_ReadRef(file, &m_unk26c);
    ReadF32LE(file, &m_unk270);
    IKFile_ReadRef(file, &m_unk25c);
    ReadF32LE(file, &m_unk260);
    ReadF32LE(file, &m_unk264);
    ReadU32LE(file, &m_unk268);
    return 1;
}
