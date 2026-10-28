// CKElectricSphere.cpp - reconstructed original translation unit 0x396748-0x39cf88 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKElectricSphere  key 0x964c  category Logic  size 0x334  vtable 0xb23888
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x396748  CKElectricSphere_Delete
//   [ ] 0x396798  CKElectricSphere_GetAbilityId
//   [ ] 0x3967a0  CKElectricSphere_GetFamilyId
//   [ ] 0x3967a8  CKElectricSphere_GetFxSound_maybe
//   [ ] 0x3968c8  CKElectricSphere_ApplyHeroControl
//   [ ] 0x396998  CKElectricSphere_End
//   [ ] 0x396a90  CKElectricSphere_ResetRuntime
//   [ ] 0x396b58  CKElectricSphere_PostLoad
//   [ ] 0x396bc0  CKElectricSphere_RecursiveRegistration
//   [ ] 0x396be8  CKElectricSphere_Destroy
//   [x] 0x396c10  CKElectricSphere_Construct
//   [x] 0x396c48  CKElectricSphere_DeleteArray
//   [ ] 0x396ce8  CKElectricSphere_DeletingDestructor
//   [ ] 0x396d30  CKElectricSphere_Destructor
//   [ ] 0x396d60  CKElectricSphere_DestructBody
//   [ ] 0x396d90  RegisterCKElectricSphereClass
//   [ ] 0x396e18  _GLOBAL__D_396e18
//   [ ] 0x396e28  _GLOBAL__I_396e28
//   [ ] 0x396e38  CKElectricSphere_Construct_2
//   [ ] 0x396e70  CKElectricSphere_Start
//   [ ] 0x397130  CKElectricSphere_StopFx
//   [x] 0x397240  CKElectricSphere_CreateArray
//   [x] 0x3972f0  CKElectricSphere_Create
//   [x] 0x397348  CKElectricSphere_Load
//   [ ] 0x398a48  CKElectricSphere_Save
//   [ ] 0x39a0c0  CKElectricSphere_UpdateAttack_maybe
//   [ ] 0x39a798  CKElectricSphere_UpdateEffect_maybe
//   [ ] 0x39bd78  CKElectricSphere_SetFxActive
//
//   [ ] 0x9bfca0  CKElectricSphere_IsKindOfClass  [inline]
//   [ ] 0x9bfcf0  CKElectricSphere_GetClassType  [inline]
//   [ ] 0x9bfcf8  CKElectricSphere_GetClassID  [inline]
//   [ ] 0x9bfd00  CKElectricSphere_StartEmitterFx  [inline]
#include "k2000/logic/physics/CKElectricSphere.h"

#include "k2000/io/IKFile.h"

// 0x00397348 CKElectricSphere_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 284
// bytes of references and words (570 bytes in all).
int32_t CKElectricSphere::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk1ec);
        IKFile_ReadRef(file, &m_unk1f0);
        IKFile_ReadRef(file, &m_unk1dc);
        IKFile_ReadRef(file, &m_unk1e0);
        IKFile_ReadRef(file, &m_unk224);
        IKFile_ReadRef(file, &m_unk18c);
        ReadF32LE(file, &m_unk154);
        ReadF32LE(file, &m_unk160);
        ReadS32LE(file, &m_unk16c);
        ReadF32LE(file, &m_unk158);
        ReadF32LE(file, &m_unk164);
        ReadS32LE(file, &m_unk170);
        ReadF32LE(file, &m_unk15c);
        ReadF32LE(file, &m_unk168);
        ReadS32LE(file, &m_unk174);
        ReadF32LE(file, &m_unk178);
        IKFile_ReadRef(file, &m_unk24c);
        IKFile_ReadRef(file, &m_unk250);
        IKFile_ReadRef(file, &m_unk254);
        ReadF32LE(file, &m_unk190);
        ReadF32LE(file, &m_unk19c);
        ReadF32LE(file, &m_unk1a8);
        ReadF32LE(file, &m_unk1b4);
        ReadF32LE(file, &m_unk1c0);
        ReadF32LE(file, &m_unk1cc);
        ReadF32LE(file, &m_unk194);
        ReadF32LE(file, &m_unk1a0);
        ReadF32LE(file, &m_unk1ac);
        ReadF32LE(file, &m_unk1b8);
        ReadF32LE(file, &m_unk1c4);
        ReadF32LE(file, &m_unk1d0);
        ReadF32LE(file, &m_unk198);
        ReadF32LE(file, &m_unk1a4);
        ReadF32LE(file, &m_unk1b0);
        ReadF32LE(file, &m_unk1bc);
        ReadF32LE(file, &m_unk1c8);
        ReadF32LE(file, &m_unk1d4);
        ReadF32LE(file, &m_unk1d8);
        ReadF32LE(file, &m_unk17c);
        IKFile_ReadRef(file, &m_unk280);
        IKFile_ReadRef(file, &m_unk284);
        IKFile_ReadRef(file, &m_unk268);
        IKFile_ReadRef(file, &m_unk228);
        ReadU32LE(file, &m_unk22c);
        ReadF32LE(file, &m_unk230);
        ReadF32LE(file, &m_unk234);
        ReadF32LE(file, &m_unk238);
        ReadF32LE(file, &m_unk23c);
        IKFile_ReadRef(file, &m_unk1f4);
        ReadF32LE(file, &m_unk1f8);
        ReadF32LE(file, &m_unk180);
        ReadF32LE(file, &m_unk240);
        ReadF32LE(file, &m_unk184);
        ReadF32LE(file, &m_unk244);
        ReadF32LE(file, &m_unk188);
        ReadF32LE(file, &m_unk248);
        IKFile_ReadRef(file, &m_unk28c);
        ReadF32LE(file, &m_unk290);
        IKFile_ReadRef(file, &m_unk1fc);
        IKFile_ReadRef(file, &m_unk270);
        IKFile_ReadRef(file, &m_unk274);
        IKFile_ReadRef(file, &m_unk278);
        IKFile_ReadRef(file, &m_unk200);
        IKFile_ReadRef(file, &m_unk204);
        IKFile_ReadRef(file, &m_unk208);
        ReadF32LE(file, &m_unk20c);
        ReadF32LE(file, &m_unk218);
        ReadF32LE(file, &m_unk210);
        ReadF32LE(file, &m_unk21c);
        ReadF32LE(file, &m_unk214);
        ReadF32LE(file, &m_unk220);
    }
    return 1;
}
