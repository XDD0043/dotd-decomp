// CKFireBreath.cpp - reconstructed original translation unit 0x3a3240-0x3a5e60 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKFireBreath  key 0x924c  category Logic  size 0x1f0  vtable 0xb23a48
// Other owners: UpdateFireBreathEffects (1), SetFireBreathEffectsActive (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x3a3240  CKFireBreath_End
//   [ ] 0x3a32b8  CKFireBreath_Start
//   [ ] 0x3a32e8  CKFireBreath_PostLoad
//   [ ] 0x3a3310  CKFireBreath_RecursiveRegistration
//   [ ] 0x3a3338  CKFireBreath_Destroy
//   [ ] 0x3a3360  CKFireBreath_DeletingDestructor
//   [ ] 0x3a33a8  CKFireBreath_Destructor
//   [ ] 0x3a33d8  CKFireBreath_DestructBody
//   [x] 0x3a3408  CKFireBreath_Construct
//   [ ] 0x3a3440  CKFireBreath_Construct_2
//   [x] 0x3a3478  CKFireBreath_DeleteArray
//   [ ] 0x3a3520  RegisterCKFireBreathClass
//   [ ] 0x3a35a8  _GLOBAL__D_3a35a8
//   [ ] 0x3a35b8  _GLOBAL__I_3a35b8
//   [ ] 0x3a35c8  CKFireBreath_GetEmitterPosition
//   [ ] 0x3a3720  UpdateFireBreathEffects
//   [x] 0x3a3d88  CKFireBreath_CreateArray
//   [x] 0x3a3e40  CKFireBreath_Create
//   [ ] 0x3a3e98  CKFireBreath_ConfigureSparkNode_maybe
//   [x] 0x3a4288  CKFireBreath_Load
//   [ ] 0x3a4ba8  CKFireBreath_Save
//   [ ] 0x3a5498  SetFireBreathEffectsActive
//
//   [ ] 0x9bfe38  CKFireBreath_IsKindOfClass  [inline]
//   [ ] 0x9bfe88  CKFireBreath_GetClassType  [inline]
//   [ ] 0x9bfe90  CKFireBreath_GetClassID  [inline]
//   [ ] 0x9bfe98  CKFireBreath_StartEmitterFx  [inline]
#include "k2000/logic/CKFireBreath.h"

#include "k2000/io/IKFile.h"

// 0x003a4288 CKFireBreath_Load: CKBreathElement's data, then (level data only) 0x60 bytes: a reference, ten
// words, ten references and three words.
int32_t CKFireBreath::Load(IKFile* file, int32_t type) {
    CKBreathElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk1a0);
        for (int32_t i = 0; i < 10; ++i) ReadF32LE(file, &m_unk178[i]);
        IKFile_ReadRef(file, &m_unk1d4);
        IKFile_ReadRef(file, &m_unk1d8);
        IKFile_ReadRef(file, &m_unk1e0);
        IKFile_ReadRef(file, &m_unk1a8[0]);
        IKFile_ReadRef(file, &m_unk1a8[1]);
        IKFile_ReadRef(file, &m_unk1a8[2]);
        IKFile_ReadRef(file, &m_unk1e4);
        IKFile_ReadRef(file, &m_unk1b8[0]);
        IKFile_ReadRef(file, &m_unk1b8[1]);
        IKFile_ReadRef(file, &m_unk1b8[2]);
        ReadF32LE(file, &m_unk1c8);
        ReadF32LE(file, &m_unk1cc);
        ReadF32LE(file, &m_unk1d0);
    }
    return 1;
}
