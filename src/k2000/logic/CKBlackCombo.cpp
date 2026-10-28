// CKBlackCombo.cpp - reconstructed original translation unit 0x37d2e0-0x380ed0 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKBlackCombo  key 0xa44c  category Logic  size 0x260  vtable 0xb234e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x37d2e0  CKBlackCombo_Delete
//   [ ] 0x37d330  CKBlackCombo_GetAbilityId
//   [ ] 0x37d338  CKBlackCombo_GetFamilyId
//   [ ] 0x37d340  CKBlackCombo_SetAttackActive_maybe
//   [ ] 0x37d3f0  CKBlackCombo_IsGroundTrailActive_maybe
//   [ ] 0x37d450  CKBlackCombo_ApplyHeroControl
//   [ ] 0x37d510  CKBlackCombo_End
//   [ ] 0x37d5a0  CKBlackCombo_StopFxAndAttack
//   [ ] 0x37d688  CKBlackCombo_Update
//   [ ] 0x37d6b0  CKBlackCombo_Start
//   [ ] 0x37d720  CKBlackCombo_ResetRuntime
//   [ ] 0x37d778  CKBlackCombo_RecursiveRegistration
//   [ ] 0x37d7a0  CKBlackCombo_Destroy
//   [x] 0x37d7c8  CKBlackCombo_Construct
//   [ ] 0x37d800  CKBlackCombo_Construct_2
//   [x] 0x37d838  CKBlackCombo_DeleteArray
//   [ ] 0x37d8d8  CKBlackCombo_DeletingDestructor
//   [ ] 0x37d920  CKBlackCombo_Destructor
//   [ ] 0x37d950  CKBlackCombo_DestructBody
//   [ ] 0x37d980  RegisterCKBlackComboClass
//   [ ] 0x37da08  _GLOBAL__D_37da08
//   [ ] 0x37da18  _GLOBAL__I_37da18
//   [ ] 0x37da28  CKBlackCombo_PostLoad
//   [ ] 0x37daf8  CKBlackCombo_SteerTowardsTarget_maybe
//   [x] 0x37dc60  CKBlackCombo_CreateArray
//   [x] 0x37dd10  CKBlackCombo_Create
//   [ ] 0x37dd68  CKBlackCombo_UpdateAttack_maybe
//   [x] 0x37e4f0  CKBlackCombo_Load
//   [ ] 0x37ed28  CKBlackCombo_Save
//   [ ] 0x37f600  CKBlackCombo_UpdateMovement_maybe
//   [ ] 0x37fa90  CKBlackCombo_SetFxActive
//
//   [ ] 0x9bf988  CKBlackCombo_IsKindOfClass  [inline]
//   [ ] 0x9bf9d8  CKBlackCombo_GetClassType  [inline]
//   [ ] 0x9bf9e0  CKBlackCombo_GetClassID  [inline]
//   [ ] 0x9bf9e8  CKBlackCombo_StartEmitterFx  [inline]
#include "k2000/logic/CKBlackCombo.h"

#include "k2000/io/IKFile.h"

// 0x0037e4f0 CKBlackCombo_Load: CKAttackMoveElement's data, then (type 0 only) 160 bytes: eight references,
// three passes over seven per-index fields, two floats and three references.
int32_t CKBlackCombo::Load(IKFile* file, int32_t type) {
    CKAttackMoveElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk220);
        IKFile_ReadRef(file, &m_unk248);
        IKFile_ReadRef(file, &m_unk24c);
        IKFile_ReadRef(file, &m_unk21c);
        IKFile_ReadRef(file, &m_unk234);
        IKFile_ReadRef(file, &m_unk23c);
        IKFile_ReadRef(file, &m_unk224);
        IKFile_ReadRef(file, &m_unk244);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_unk1a8[i]);
            ReadS32LE(file, &m_unk1b4[i]);
            ReadS32LE(file, &m_unk1c0[i]);
            ReadS32LE(file, &m_unk1cc[i]);
            ReadF32LE(file, &m_unk1d8[i]);
            ReadF32LE(file, &m_unk210[i]);
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk1e4[i]), 3);
        }
        ReadF32LE(file, &m_unk208);
        ReadF32LE(file, &m_unk20c);
        IKFile_ReadRef(file, &m_unk228);
        IKFile_ReadRef(file, &m_unk22c);
        IKFile_ReadRef(file, &m_unk230);
    }
    return 1;
}
