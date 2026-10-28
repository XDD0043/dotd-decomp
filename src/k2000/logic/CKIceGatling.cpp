// CKIceGatling.cpp - reconstructed original translation unit 0x3a9c50-0x3abec0 (GAME_TOC1, main_toc1), 25 functions, 25 live.
// Primary class: CKIceGatling  key 0x940c  category Logic  size 0x264  vtable 0xb23b80
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3a9c50  CKIceGatling_Delete
//   [ ] 0x3a9ca0  CKIceGatling_GetAbilityId
//   [ ] 0x3a9ca8  CKIceGatling_IsChargeDisabled_maybe
//   [ ] 0x3a9cb0  CKIceGatling_ApplyDamageParams
//   [ ] 0x3aa170  CKIceGatling_ResetRuntime
//   [ ] 0x3aa1c0  CKIceGatling_Update
//   [ ] 0x3aa3c0  CKIceGatling_Start
//   [ ] 0x3aa498  CKIceGatling_PostLoad
//   [ ] 0x3aa4c0  CKIceGatling_RecursiveRegistration
//   [ ] 0x3aa4e8  CKIceGatling_Destroy
//   [ ] 0x3aa510  CKIceGatling_DeletingDestructor
//   [ ] 0x3aa558  CKIceGatling_Destructor
//   [ ] 0x3aa588  CKIceGatling_DestructBody
//   [x] 0x3aa5b8  CKIceGatling_Construct
//   [ ] 0x3aa5f0  CKIceGatling_Construct_2
//   [x] 0x3aa628  CKIceGatling_DeleteArray
//   [ ] 0x3aa6c8  RegisterCKIceGatlingClass
//   [ ] 0x3aa750  _GLOBAL__D_3aa750
//   [ ] 0x3aa760  _GLOBAL__I_3aa760
//   [ ] 0x3aa770  CKIceGatling_End
//   [x] 0x3aa800  CKIceGatling_CreateArray
//   [x] 0x3aa8b0  CKIceGatling_Create
//   [ ] 0x3aa908  CKIceGatling_Fire
//   [x] 0x3ab230  CKIceGatling_Load
//   [ ] 0x3ab820  CKIceGatling_Save
//
//   [ ] 0x9bff38  CKIceGatling_IsKindOfClass  [inline]
//   [ ] 0x9bff88  CKIceGatling_GetClassType  [inline]
//   [ ] 0x9bff90  CKIceGatling_GetClassID  [inline]
//   [ ] 0x9bff98  CKIceGatling_StartEmitterFx  [inline]
#include "k2000/logic/CKIceGatling.h"

#include "k2000/io/IKFile.h"

// 0x003ab230 CKIceGatling_Load: CKProjectileElement's data, then (level data only) 76 bytes: floats and
// seven object references (the original's reads are unrolled; the loops keep its order).
int32_t CKIceGatling::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_unk214[i]);
        ReadF32LE(file, &m_unk220[i]);
    }
    IKFile_ReadRef(file, &m_unk244[0]);
    IKFile_ReadRef(file, &m_unk244[1]);
    IKFile_ReadRef(file, &m_unk244[2]);
    IKFile_ReadRef(file, &m_unk250);
    ReadF32LE(file, &m_unk238[0]);
    ReadF32LE(file, &m_unk238[1]);
    ReadF32LE(file, &m_unk238[2]);
    IKFile_ReadRef(file, &m_unk254[0]);
    IKFile_ReadRef(file, &m_unk254[1]);
    IKFile_ReadRef(file, &m_unk254[2]);
    ReadF32LE(file, &m_unk22c[0]);
    ReadF32LE(file, &m_unk22c[1]);
    ReadF32LE(file, &m_unk22c[2]);
    return 1;
}
