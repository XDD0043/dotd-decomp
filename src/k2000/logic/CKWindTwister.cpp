// CKWindTwister.cpp - reconstructed original translation unit 0x3e6f80-0x3ee198 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKWindTwister  key 0x98cc  category Logic  size 0x344  vtable 0xb249c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3e6f80  CKWindTwister_Delete
//   [ ] 0x3e6fd0  CKWindTwister_GetAbilityId
//   [ ] 0x3e6fd8  CKWindTwister_GetFamilyId
//   [ ] 0x3e6fe0  CKWindTwister_IsGroundTrailActive_maybe
//   [ ] 0x3e7040  CKWindTwister_GetFxSound_maybe
//   [ ] 0x3e7248  CKWindTwister_ApplyHeroControl
//   [ ] 0x3e7318  CKWindTwister_End
//   [ ] 0x3e7480  CKWindTwister_ResetRuntime
//   [ ] 0x3e7648  CKWindTwister_RecursiveRegistration
//   [ ] 0x3e7670  CKWindTwister_Destroy
//   [ ] 0x3e7698  CKWindTwister_DeletingDestructor
//   [ ] 0x3e76e0  CKWindTwister_Destructor
//   [ ] 0x3e7710  CKWindTwister_DestructBody
//   [x] 0x3e7740  CKWindTwister_Construct
//   [ ] 0x3e7778  CKWindTwister_Construct_2
//   [x] 0x3e77b0  CKWindTwister_DeleteArray
//   [ ] 0x3e7850  CKWindTwister_PostLoad
//   [ ] 0x3e79a0  RegisterCKWindTwisterClass
//   [ ] 0x3e7a28  _GLOBAL__D_3e7a28
//   [ ] 0x3e7a38  _GLOBAL__I_3e7a38
//   [ ] 0x3e7a48  CKWindTwister_StopFx
//   [x] 0x3e7c98  CKWindTwister_CreateArray
//   [x] 0x3e7d48  CKWindTwister_Create
//   [ ] 0x3e7da0  CKWindTwister_Start
//   [x] 0x3e8260  CKWindTwister_Load
//   [ ] 0x3e9870  CKWindTwister_Save
//   [ ] 0x3ead10  CKWindTwister_UpdateEffect_maybe
//   [ ] 0x3ec8d8  CKWindTwister_UpdateAttack_maybe
//   [ ] 0x3ed2c0  CKWindTwister_SetFxActive
//
//   [ ] 0x9c09c0  CKWindTwister_IsKindOfClass  [inline]
//   [ ] 0x9c0a10  CKWindTwister_GetClassType  [inline]
//   [ ] 0x9c0a18  CKWindTwister_GetClassID  [inline]
//   [ ] 0x9c0a20  CKWindTwister_StartEmitterFx  [inline]
#include "k2000/logic/CKWindTwister.h"

#include "k2000/io/IKFile.h"

// 0x003e8260 CKWindTwister_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 428
// bytes of references and words (714 bytes in all).
int32_t CKWindTwister::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk2b0);
        IKFile_ReadRef(file, &m_unk2b8);
        IKFile_ReadRef(file, &m_unk288);
        IKFile_ReadRef(file, &m_unk2bc);
        IKFile_ReadRef(file, &m_unk2c4);
        IKFile_ReadRef(file, &m_unk2cc);
        IKFile_ReadRef(file, &m_unk2d0);
        IKFile_ReadRef(file, &m_unk2d4);
        IKFile_ReadRef(file, &m_unk284);
        IKFile_ReadRef(file, &m_unk2e8);
        IKFile_ReadRef(file, &m_unk2ec);
        IKFile_ReadRef(file, &m_unk2dc);
        IKFile_ReadRef(file, &m_unk2e0);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_unk154[i]);
            ReadS32LE(file, &m_unk160[i]);
            ReadU32LE(file, &m_unk16c[i]);
            ReadU32LE(file, &m_unk178[i]);
            ReadF32LE(file, &m_unk19c[i]);
            ReadF32LE(file, &m_unk184[i]);
            ReadS32LE(file, &m_unk1a8[i]);
            ReadU32LE(file, &m_unk1b4[i]);
            ReadU32LE(file, &m_unk1c0[i]);
            ReadF32LE(file, &m_unk1e4[i]);
            ReadF32LE(file, &m_unk1cc[i]);
            ReadF32LE(file, &m_unk1f0[i]);
            ReadF32LE(file, &m_unk1fc[i]);
            ReadU32LE(file, &m_unk208[i]);
            ReadU32LE(file, &m_unk214[i]);
            ReadU32LE(file, &m_unk220[i]);
            ReadF32LE(file, &m_unk244[i]);
            ReadF32LE(file, &m_unk22c[i]);
            ReadU32LE(file, &m_unk250[i]);
            ReadF32LE(file, &m_unk25c[i]);
        }
        ReadF32LE(file, &m_unk190);
        ReadF32LE(file, &m_unk194);
        ReadF32LE(file, &m_unk198);
        ReadF32LE(file, &m_unk2f4);
        ReadF32LE(file, &m_unk2f8);
        ReadF32LE(file, &m_unk2fc);
        ReadF32LE(file, &m_unk300);
        ReadF32LE(file, &m_unk304);
        ReadF32LE(file, &m_unk308);
        ReadF32LE(file, &m_unk1d8);
        ReadF32LE(file, &m_unk1dc);
        ReadF32LE(file, &m_unk1e0);
        ReadF32LE(file, &m_unk290);
        ReadF32LE(file, &m_unk294);
        ReadF32LE(file, &m_unk298);
        ReadF32LE(file, &m_unk29c);
        ReadF32LE(file, &m_unk2a0);
        ReadF32LE(file, &m_unk2a4);
        ReadS32LE(file, &m_unk2a8);
        ReadU32LE(file, &m_unk2ac);
        ReadF32LE(file, &m_unk238);
        ReadF32LE(file, &m_unk23c);
        ReadF32LE(file, &m_unk240);
        IKFile_ReadRef(file, &m_unk30c);
        ReadF32LE(file, &m_unk310);
        IKFile_ReadRef(file, &m_unk2f0);
        IKFile_ReadRef(file, &m_unk280);
        ReadF32LE(file, &m_unk268);
        ReadF32LE(file, &m_unk274);
        ReadF32LE(file, &m_unk26c);
        ReadF32LE(file, &m_unk278);
        ReadF32LE(file, &m_unk270);
        ReadF32LE(file, &m_unk27c);
        IKFile_ReadRef(file, &m_unk2d8);
    }
    return 1;
}
