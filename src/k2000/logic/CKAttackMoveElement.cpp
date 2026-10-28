// CKAttackMoveElement.cpp - reconstructed original translation unit 0x374d50-0x3798b8 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKAttackMoveElement  key 0x9a0c  category Logic  size 0x1a8  vtable 0xb23340
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x374d50  CKAttackMoveElement_Delete
//   [x] 0x374da0  CKAttackMoveElement_Construct
//   [ ] 0x374db0  CKAttackMoveElement_Construct_2  [dead]
//   [ ] 0x374dc0  CKAttackMoveElement_GetAbilityId
//   [ ] 0x374dc8  CKAttackMoveElement_GetFamilyId
//   [ ] 0x374dd0  CKAttackMoveElement_Stop
//   [ ] 0x374e60  CKAttackMoveElement_StopFxAndAttack
//   [ ] 0x374ee0  CKAttackMoveElement_End
//   [ ] 0x374ff8  CKAttackMoveElement_ApplyHeroControl
//   [ ] 0x3756d0  CKAttackMoveElement_ResetRuntime
//   [x] 0x375720  CKAttackMoveElement_DeleteArray
//   [ ] 0x3757c0  CKAttackMoveElement_StartEmitterFx
//   [ ] 0x375a88  RegisterCKAttackMoveElementClass
//   [ ] 0x375b10  _GLOBAL__D_375b10
//   [ ] 0x375b20  _GLOBAL__I_375b20
//   [ ] 0x375b30  CKAttackMoveElement_ApplyDamageParams
//   [ ] 0x3760b0  CKAttackMoveElement_Start
//   [ ] 0x376238  CKAttackMoveElement_Update
//   [x] 0x376d90  CKAttackMoveElement_CreateArray
//   [x] 0x376e20  CKAttackMoveElement_Create
//   [ ] 0x376e58  CKAttackMoveElement_RecursiveRegistration
//   [ ] 0x376e60  CKAttackMoveElement_PostLoad
//   [ ] 0x376ea8  CKAttackMoveElement_Destroy
//   [ ] 0x376eb0  CKAttackMoveElement_SteerTowardsTarget_maybe
//   [ ] 0x3774f0  CKAttackMoveElement_DestructBody
//   [ ] 0x377510  CKAttackMoveElement_DeletingDestructor
//   [ ] 0x377558  CKAttackMoveElement_Destructor
//   [x] 0x377578  CKAttackMoveElement_Load
//   [ ] 0x378800  CKAttackMoveElement_Save
//
//   [ ] 0x9bf838  CKAttackMoveElement_GetClassType  [inline]
//   [ ] 0x9bf840  CKAttackMoveElement_GetClassID  [inline]
//   [ ] 0x9bf848  CKAttackMoveElement_SetFxActive  [inline]
//   [ ] 0x9bf850  CKAttackMoveElement_vf74  [inline]
//   [ ] 0x9bf858  CKAttackMoveElement_UpdateAttack_maybe  [inline]
//   [ ] 0x9bf860  CKAttackMoveElement_UpdateMovement_maybe  [inline]
//   [ ] 0x9bf868  CKAttackMoveElement_vf8C  [inline]
//   [ ] 0x9bf870  CKAttackMoveElement_IsKindOfClass  [inline]
//   [ ] 0x9bf8a8  KBase90CC_DeletingDestructor  [inline]
//   [ ] 0x9bf8e8  CKAbilityElement_maybe_Destructor  [inline]
#include "k2000/logic/CKAttackMoveElement.h"

#include "k2000/io/IKFile.h"

// 0x00377578 CKAttackMoveElement_Load: only for type 0 (K_LEVEL_PLATEFORMS); 366 bytes: three passes over
// eighteen per-index fields, then single fields and two object references. No base Load is called.
int32_t CKAttackMoveElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk08[i]);
            ReadF32LE(file, &m_unk20[i]);
            ReadS32LE(file, &m_unk38[i]);
            ReadF32LE(file, &m_unk44[i]);
            ReadF32LE(file, &m_unk78[i]);
            ReadF32LE(file, &m_unk84[i]);
            ReadF32LE(file, &m_unk90[i]);
            ReadF32LE(file, &m_unk9c[i]);
            ReadF32LE(file, &m_unka8[i]);
            ReadF32LE(file, &m_unkb4[i]);
            ReadF32LE(file, &m_unkc0[i]);
            ReadF32LE(file, &m_unkcc[i]);
            ReadF32LE(file, &m_unkd8[i]);
            ReadU8(file, &m_unkf0[i]);
            ReadU8(file, &m_unkf3[i]);
            ReadF32LE(file, &m_unkf8[i]);
            ReadF32LE(file, &m_unk104[i]);
            ReadF32LE(file, &m_unk110[i]);
        }
        ReadU8(file, &m_unk134);
        ReadU8(file, &m_unk135);
        ReadU8(file, &m_unk136);
        ReadF32LE(file, &m_unk138);
        ReadF32LE(file, &m_unk13c);
        ReadF32LE(file, &m_unk14c);
        ReadU8(file, &m_unk140);
        ReadU8(file, &m_unk141);
        ReadU8(file, &m_unk142);
        ReadF32LE(file, &m_unk144);
        ReadF32LE(file, &m_unk148);
        ReadF32LE(file, &m_unk150);
        ReadU8(file, &m_unk154);
        ReadU8(file, &m_unk155);
        ReadF32LE(file, &m_unk158);
        ReadF32LE(file, &m_unk15c);
        ReadF32LE(file, &m_unke4);
        ReadF32LE(file, &m_unke8);
        ReadF32LE(file, &m_unkec);
        ReadF32LE(file, &m_unk50);
        ReadF32LE(file, &m_unk54);
        ReadF32LE(file, &m_unk58);
        ReadF32LE(file, &m_unk128);
        IKFile_ReadRef(file, &m_unk19c);
        ReadU8(file, &m_unk160);
        ReadU8(file, &m_unk161);
        ReadU8(file, &m_unk162);
        ReadF32LE(file, &m_unk164);
        ReadF32LE(file, &m_unk168);
        ReadF32LE(file, &m_unk16c);
        ReadU8(file, &m_unk170);
        ReadF32LE(file, &m_unk174);
        ReadF32LE(file, &m_unk5c);
        ReadF32LE(file, &m_unk60);
        ReadF32LE(file, &m_unk64);
        ReadF32LE(file, &m_unk68);
        ReadF32LE(file, &m_unk6c);
        ReadF32LE(file, &m_unk2c);
        ReadF32LE(file, &m_unk30);
        ReadF32LE(file, &m_unk34);
        IKFile_ReadRef(file, &m_unk178);
        ReadF32LE(file, &m_unk11c);
        ReadF32LE(file, &m_unk120);
        ReadF32LE(file, &m_unk124);
        ReadF32LE(file, &m_unk14);
        ReadF32LE(file, &m_unk18);
        ReadF32LE(file, &m_unk1c);
        ReadF32LE(file, &m_unk70);
        ReadF32LE(file, &m_unk74);
        ReadF32LE(file, &m_unk12c);
        ReadF32LE(file, &m_unk130);
    }
    return 1;
}
