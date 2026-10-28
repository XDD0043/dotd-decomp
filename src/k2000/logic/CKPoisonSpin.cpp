// CKPoisonSpin.cpp - reconstructed original translation unit 0x3b8bd8-0x3bc818 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKPoisonSpin  key 0xa2cc  category Logic  size 0x260  vtable 0xb23d38
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3b8bd8  CKPoisonSpin_Delete
//   [ ] 0x3b8c28  CKPoisonSpin_GetAbilityId
//   [ ] 0x3b8c30  CKPoisonSpin_GetFamilyId
//   [ ] 0x3b8c38  CKPoisonSpin_SetAttackActive_maybe
//   [ ] 0x3b8ce8  CKPoisonSpin_IsGroundTrailActive_maybe
//   [ ] 0x3b8d48  CKPoisonSpin_ApplyHeroControl
//   [ ] 0x3b8e08  CKPoisonSpin_End
//   [ ] 0x3b8e98  CKPoisonSpin_StopFxAndAttack
//   [ ] 0x3b8f80  CKPoisonSpin_Update
//   [ ] 0x3b8fa8  CKPoisonSpin_Start
//   [ ] 0x3b9018  CKPoisonSpin_ResetRuntime
//   [ ] 0x3b9070  CKPoisonSpin_RecursiveRegistration
//   [ ] 0x3b9098  CKPoisonSpin_Destroy
//   [x] 0x3b90c0  CKPoisonSpin_Construct
//   [ ] 0x3b90f8  CKPoisonSpin_Construct_2
//   [x] 0x3b9130  CKPoisonSpin_DeleteArray
//   [ ] 0x3b91d0  CKPoisonSpin_DeletingDestructor
//   [ ] 0x3b9218  CKPoisonSpin_Destructor
//   [ ] 0x3b9248  CKPoisonSpin_DestructBody
//   [ ] 0x3b9278  RegisterCKPoisonSpinClass
//   [ ] 0x3b9300  _GLOBAL__D_3b9300
//   [ ] 0x3b9310  _GLOBAL__I_3b9310
//   [ ] 0x3b9320  CKPoisonSpin_PostLoad
//   [ ] 0x3b9440  CKPoisonSpin_SteerTowardsTarget_maybe
//   [x] 0x3b95a8  CKPoisonSpin_CreateArray
//   [x] 0x3b9658  CKPoisonSpin_Create
//   [ ] 0x3b96b0  CKPoisonSpin_UpdateAttack_maybe
//   [x] 0x3b9e38  CKPoisonSpin_Load
//   [ ] 0x3ba670  CKPoisonSpin_Save
//   [ ] 0x3baf48  CKPoisonSpin_UpdateMovement_maybe
//   [ ] 0x3bb3d8  CKPoisonSpin_SetFxActive
//
//   [ ] 0x9c00d0  CKPoisonSpin_IsKindOfClass  [inline]
//   [ ] 0x9c0120  CKPoisonSpin_GetClassType  [inline]
//   [ ] 0x9c0128  CKPoisonSpin_GetClassID  [inline]
//   [ ] 0x9c0130  CKPoisonSpin_StartEmitterFx  [inline]
#include "k2000/logic/CKPoisonSpin.h"

#include "k2000/io/IKFile.h"

// 0x003b9e38 CKPoisonSpin_Load: CKAttackMoveElement's data, then (type 0 only) 160 bytes: eight references,
// three passes over seven per-index fields, two floats and three references (as CKBlackCombo_Load).
int32_t CKPoisonSpin::Load(IKFile* file, int32_t type) {
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
