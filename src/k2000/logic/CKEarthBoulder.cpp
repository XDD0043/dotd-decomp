// CKEarthBoulder.cpp - reconstructed original translation unit 0x389ec8-0x3928a0 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKEarthBoulder  key 0x95cc  category Logic  size 0x2d0  vtable 0xb236c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x389ec8  CKEarthBoulder_Delete
//   [ ] 0x389f18  CKEarthBoulder_GetAbilityId
//   [ ] 0x389f20  CKEarthBoulder_GetFamilyId
//   [ ] 0x389f28  CKEarthBoulder_IsGroundTrailActive_maybe
//   [ ] 0x389f88  CKEarthBoulder_PlaySoundByIndex_maybe
//   [ ] 0x38a270  CKEarthBoulder_ApplyHeroControl
//   [ ] 0x38a3c8  CKEarthBoulder_End
//   [ ] 0x38a600  CKEarthBoulder_ResetRuntime
//   [ ] 0x38a700  CKEarthBoulder_PostLoad
//   [ ] 0x38a798  CKEarthBoulder_RecursiveRegistration
//   [ ] 0x38a7c0  CKEarthBoulder_Destroy
//   [ ] 0x38a7e8  CKEarthBoulder_DeletingDestructor
//   [ ] 0x38a830  CKEarthBoulder_Destructor
//   [ ] 0x38a860  CKEarthBoulder_DestructBody
//   [x] 0x38a890  CKEarthBoulder_Construct
//   [ ] 0x38a8c8  CKEarthBoulder_Construct_2
//   [x] 0x38a900  CKEarthBoulder_DeleteArray
//   [ ] 0x38a9a0  RegisterCKEarthBoulderClass
//   [ ] 0x38aa28  _GLOBAL__D_38aa28
//   [ ] 0x38aa38  _GLOBAL__I_38aa38
//   [ ] 0x38aa48  CKEarthBoulder_StopFx
//   [ ] 0x38ab80  CKEarthBoulder_Update
//   [x] 0x38ace0  CKEarthBoulder_Create
//   [x] 0x38ad38  CKEarthBoulder_CreateArray
//   [ ] 0x38ade8  CKEarthBoulder_Start
//   [x] 0x38b200  CKEarthBoulder_Load
//   [ ] 0x38cbd8  CKEarthBoulder_Save
//   [ ] 0x38e4a8  CKEarthBoulder_UpdateEffect_maybe
//   [ ] 0x38fac8  CKEarthBoulder_SetFxActive
//   [ ] 0x390e00  CKEarthBoulder_SwitchLoopAnim_maybe
//   [ ] 0x391588  CKEarthBoulder_UpdateAttack_maybe
//
//   [ ] 0x9bfaf0  CKEarthBoulder_IsKindOfClass  [inline]
//   [ ] 0x9bfb40  CKEarthBoulder_GetClassType  [inline]
//   [ ] 0x9bfb48  CKEarthBoulder_GetClassID  [inline]
//   [ ] 0x9bfb50  CKEarthBoulder_StartEmitterFx  [inline]
#include "k2000/logic/CKEarthBoulder.h"

#include "k2000/io/IKFile.h"

// 0x0038b200 CKEarthBoulder_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 300
// bytes of references and words (586 bytes in all).
int32_t CKEarthBoulder::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk204);
        IKFile_ReadRef(file, &m_unk208);
        IKFile_ReadRef(file, &m_unk20c);
        IKFile_ReadRef(file, &m_unk210);
        IKFile_ReadRef(file, &m_unk214);
        IKFile_ReadRef(file, &m_unk1f4);
        IKFile_ReadRef(file, &m_unk250);
        IKFile_ReadRef(file, &m_unk258);
        ReadF32LE(file, &m_unk154);
        ReadF32LE(file, &m_unk158);
        ReadF32LE(file, &m_unk15c);
        ReadS32LE(file, &m_unk184);
        ReadU32LE(file, &m_unk188);
        ReadU32LE(file, &m_unk18c);
        ReadF32LE(file, &m_unk190);
        ReadF32LE(file, &m_unk194);
        ReadF32LE(file, &m_unk1a0);
        ReadU32LE(file, &m_unk1ac);
        ReadF32LE(file, &m_unk1b8);
        ReadU32LE(file, &m_unk1c4);
        ReadF32LE(file, &m_unk1d0);
        ReadU32LE(file, &m_unk1dc);
        ReadF32LE(file, &m_unk1e8);
        ReadF32LE(file, &m_unk1a4);
        ReadU32LE(file, &m_unk1b0);
        ReadF32LE(file, &m_unk1bc);
        ReadU32LE(file, &m_unk1c8);
        ReadF32LE(file, &m_unk1d4);
        ReadU32LE(file, &m_unk1e0);
        ReadF32LE(file, &m_unk1ec);
        ReadF32LE(file, &m_unk1a8);
        ReadU32LE(file, &m_unk1b4);
        ReadF32LE(file, &m_unk1c0);
        ReadU32LE(file, &m_unk1cc);
        ReadF32LE(file, &m_unk1d8);
        ReadU32LE(file, &m_unk1e4);
        ReadF32LE(file, &m_unk1f0);
        IKFile_ReadRef(file, &m_unk228);
        IKFile_ReadRef(file, &m_unk22c);
        IKFile_ReadRef(file, &m_unk230);
        ReadF32LE(file, &m_unk198);
        IKFile_ReadRef(file, &m_unk1fc);
        IKFile_ReadRef(file, &m_unk218);
        IKFile_ReadRef(file, &m_unk244);
        IKFile_ReadRef(file, &m_unk248);
        IKFile_ReadRef(file, &m_unk274);
        ReadF32LE(file, &m_unk278);
        ReadU32LE(file, &m_unk280);
        ReadF32LE(file, &m_unk284);
        ReadF32LE(file, &m_unk288);
        IKFile_ReadRef(file, &m_unk224);
        IKFile_ReadRef(file, &m_unk28c);
        IKFile_ReadRef(file, &m_unk290);
        IKFile_ReadRef(file, &m_unk294);
        IKFile_ReadRef(file, &m_unk21c);
        IKFile_ReadRef(file, &m_unk220);
        IKFile_ReadRef(file, &m_unk25c);
        ReadU32LE(file, &m_unk160);
        ReadF32LE(file, &m_unk16c);
        ReadF32LE(file, &m_unk164);
        ReadF32LE(file, &m_unk170);
        ReadF32LE(file, &m_unk168);
        ReadF32LE(file, &m_unk174);
        ReadF32LE(file, &m_unk19c);
        ReadF32LE(file, &m_unk178);
        ReadF32LE(file, &m_unk17c);
        ReadF32LE(file, &m_unk180);
        IKFile_ReadRef(file, &m_unk264);
        IKFile_ReadRef(file, &m_unk268);
        IKFile_ReadRef(file, &m_unk26c);
        ReadF32LE(file, &m_unk27c);
        IKFile_ReadRef(file, &m_unk234);
        ReadF32LE(file, &m_unk238);
        ReadF32LE(file, &m_unk23c);
        ReadF32LE(file, &m_unk240);
    }
    return 1;
}
