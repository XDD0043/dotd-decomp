// CKIceSpin.cpp - reconstructed original translation unit 0x3abec0-0x3b47b8 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKIceSpin  key 0x988c  category Logic  size 0x33c  vtable 0xb23c10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3abec0  CKIceSpin_Delete
//   [ ] 0x3abf10  CKIceSpin_GetAbilityId
//   [ ] 0x3abf18  CKIceSpin_GetFamilyId
//   [ ] 0x3abf20  CKIceSpin_IsGroundTrailActive_maybe
//   [ ] 0x3abf80  CKIceSpin_GetFxSound_maybe
//   [ ] 0x3ac188  CKIceSpin_ApplyHeroControl
//   [ ] 0x3ac1b0  CKIceSpin_End
//   [ ] 0x3ac318  CKIceSpin_ResetRuntime
//   [ ] 0x3ac3f8  CKIceSpin_RecursiveRegistration
//   [ ] 0x3ac420  CKIceSpin_Destroy
//   [ ] 0x3ac448  CKIceSpin_DeletingDestructor
//   [ ] 0x3ac490  CKIceSpin_Destructor
//   [ ] 0x3ac4c0  CKIceSpin_DestructBody
//   [x] 0x3ac4f0  CKIceSpin_Construct
//   [ ] 0x3ac528  CKIceSpin_Construct_2
//   [x] 0x3ac560  CKIceSpin_DeleteArray
//   [ ] 0x3ac600  CKIceSpin_PostLoad
//   [ ] 0x3ac750  RegisterCKIceSpinClass
//   [ ] 0x3ac7d8  _GLOBAL__D_3ac7d8
//   [ ] 0x3ac7e8  _GLOBAL__I_3ac7e8
//   [ ] 0x3ac7f8  CKIceSpin_StopFx
//   [x] 0x3aca48  CKIceSpin_CreateArray
//   [x] 0x3acaf8  CKIceSpin_Create
//   [ ] 0x3acb50  CKIceSpin_Start
//   [x] 0x3ad010  CKIceSpin_Load
//   [ ] 0x3af0f8  CKIceSpin_Save
//   [ ] 0x3b0e60  CKIceSpin_UpdateAttack_maybe
//   [ ] 0x3b1848  CKIceSpin_UpdateEffect_maybe
//   [ ] 0x3b3668  CKIceSpin_SetFxActive
//
//   [ ] 0x9bffc0  CKIceSpin_IsKindOfClass  [inline]
//   [ ] 0x9c0010  CKIceSpin_GetClassType  [inline]
//   [ ] 0x9c0018  CKIceSpin_GetClassID  [inline]
//   [ ] 0x9c0020  CKIceSpin_StartEmitterFx  [inline]
#include "k2000/logic/CKIceSpin.h"

#include "k2000/io/IKFile.h"

// 0x003ad010 CKIceSpin_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 416
// bytes of references and words (702 bytes in all).
int32_t CKIceSpin::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk294);
        IKFile_ReadRef(file, &m_unk2a0);
        IKFile_ReadRef(file, &m_unk2b0);
        IKFile_ReadRef(file, &m_unk268);
        IKFile_ReadRef(file, &m_unk2dc);
        ReadF32LE(file, &m_unk154);
        ReadS32LE(file, &m_unk160);
        ReadS32LE(file, &m_unk16c);
        ReadS32LE(file, &m_unk178);
        ReadF32LE(file, &m_unk19c);
        ReadF32LE(file, &m_unk158);
        ReadS32LE(file, &m_unk164);
        ReadS32LE(file, &m_unk170);
        ReadS32LE(file, &m_unk17c);
        ReadF32LE(file, &m_unk1a0);
        ReadF32LE(file, &m_unk15c);
        ReadS32LE(file, &m_unk168);
        ReadS32LE(file, &m_unk174);
        ReadS32LE(file, &m_unk180);
        ReadF32LE(file, &m_unk1a4);
        ReadF32LE(file, &m_unk190);
        ReadF32LE(file, &m_unk194);
        ReadF32LE(file, &m_unk198);
        ReadF32LE(file, &m_unk2e8);
        ReadF32LE(file, &m_unk2ec);
        ReadF32LE(file, &m_unk2f0);
        ReadF32LE(file, &m_unk2f4);
        ReadF32LE(file, &m_unk2f8);
        ReadF32LE(file, &m_unk2fc);
        ReadF32LE(file, &m_unk184);
        ReadF32LE(file, &m_unk188);
        ReadF32LE(file, &m_unk18c);
        ReadS32LE(file, &m_unk1a8);
        ReadS32LE(file, &m_unk1b4);
        ReadS32LE(file, &m_unk1c0);
        ReadF32LE(file, &m_unk1e4);
        ReadF32LE(file, &m_unk1cc);
        ReadS32LE(file, &m_unk1ac);
        ReadS32LE(file, &m_unk1b8);
        ReadS32LE(file, &m_unk1c4);
        ReadF32LE(file, &m_unk1e8);
        ReadF32LE(file, &m_unk1d0);
        ReadS32LE(file, &m_unk1b0);
        ReadS32LE(file, &m_unk1bc);
        ReadS32LE(file, &m_unk1c8);
        ReadF32LE(file, &m_unk1ec);
        ReadF32LE(file, &m_unk1d4);
        ReadF32LE(file, &m_unk1d8);
        ReadF32LE(file, &m_unk1dc);
        ReadF32LE(file, &m_unk1e0);
        IKFile_ReadRef(file, &m_unk2b4);
        IKFile_ReadRef(file, &m_unk29c);
        IKFile_ReadRef(file, &m_unk2d0);
        IKFile_ReadRef(file, &m_unk2d4);
        ReadF32LE(file, &m_unk1f0);
        ReadF32LE(file, &m_unk1fc);
        ReadF32LE(file, &m_unk1f4);
        ReadF32LE(file, &m_unk200);
        ReadF32LE(file, &m_unk1f8);
        ReadF32LE(file, &m_unk204);
        ReadF32LE(file, &m_unk274);
        ReadF32LE(file, &m_unk278);
        ReadF32LE(file, &m_unk27c);
        ReadF32LE(file, &m_unk280);
        ReadF32LE(file, &m_unk284);
        ReadF32LE(file, &m_unk288);
        ReadS32LE(file, &m_unk28c);
        ReadU32LE(file, &m_unk290);
        IKFile_ReadRef(file, &m_unk26c);
        ReadS32LE(file, &m_unk208);
        ReadS32LE(file, &m_unk214);
        ReadS32LE(file, &m_unk220);
        ReadF32LE(file, &m_unk244);
        ReadF32LE(file, &m_unk22c);
        ReadF32LE(file, &m_unk250);
        ReadF32LE(file, &m_unk25c);
        ReadS32LE(file, &m_unk20c);
        ReadS32LE(file, &m_unk218);
        ReadS32LE(file, &m_unk224);
        ReadF32LE(file, &m_unk248);
        ReadF32LE(file, &m_unk230);
        ReadF32LE(file, &m_unk254);
        ReadF32LE(file, &m_unk260);
        ReadS32LE(file, &m_unk210);
        ReadS32LE(file, &m_unk21c);
        ReadS32LE(file, &m_unk228);
        ReadF32LE(file, &m_unk24c);
        ReadF32LE(file, &m_unk234);
        ReadF32LE(file, &m_unk258);
        ReadF32LE(file, &m_unk264);
        ReadF32LE(file, &m_unk238);
        ReadF32LE(file, &m_unk23c);
        ReadF32LE(file, &m_unk240);
        IKFile_ReadRef(file, &m_unk2b8);
        IKFile_ReadRef(file, &m_unk2e0);
        IKFile_ReadRef(file, &m_unk2a8);
        IKFile_ReadRef(file, &m_unk304);
        ReadF32LE(file, &m_unk308);
        IKFile_ReadRef(file, &m_unk2e4);
        IKFile_ReadRef(file, &m_unk2c0);
        IKFile_ReadRef(file, &m_unk2c4);
        IKFile_ReadRef(file, &m_unk2c8);
        ReadF32LE(file, &m_unk300);
        IKFile_ReadRef(file, &m_unk2bc);
    }
    return 1;
}
