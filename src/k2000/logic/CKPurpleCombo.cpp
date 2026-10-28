// CKPurpleCombo.cpp - reconstructed original translation unit 0x3c1f38-0x3c5af0 (GAME_TOC1, main_toc1), 30 functions, 30 live.
// Primary class: CKPurpleCombo  key 0xa48c  category Logic  size 0x25c  vtable 0xb23e68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3c1f38  CKPurpleCombo_Delete
//   [ ] 0x3c1f88  CKPurpleCombo_GetAbilityId
//   [ ] 0x3c1f90  CKPurpleCombo_GetFamilyId
//   [ ] 0x3c1f98  CKPurpleCombo_SetAttackActive_maybe
//   [ ] 0x3c2048  CKPurpleCombo_IsGroundTrailActive_maybe
//   [ ] 0x3c20a8  CKPurpleCombo_End
//   [ ] 0x3c2138  CKPurpleCombo_Update
//   [ ] 0x3c2160  CKPurpleCombo_Start
//   [ ] 0x3c21d0  CKPurpleCombo_ResetRuntime
//   [ ] 0x3c2220  CKPurpleCombo_RecursiveRegistration
//   [ ] 0x3c2248  CKPurpleCombo_Destroy
//   [x] 0x3c2270  CKPurpleCombo_Construct
//   [ ] 0x3c22a8  CKPurpleCombo_Construct_2
//   [x] 0x3c22e0  CKPurpleCombo_DeleteArray
//   [ ] 0x3c2380  CKPurpleCombo_DeletingDestructor
//   [ ] 0x3c23c8  CKPurpleCombo_Destructor
//   [ ] 0x3c23f8  CKPurpleCombo_DestructBody
//   [ ] 0x3c2428  RegisterCKPurpleComboClass
//   [ ] 0x3c24b0  _GLOBAL__D_3c24b0
//   [ ] 0x3c24c0  _GLOBAL__I_3c24c0
//   [ ] 0x3c24d0  CKPurpleCombo_PostLoad
//   [ ] 0x3c25a0  CKPurpleCombo_SteerTowardsTarget_maybe
//   [ ] 0x3c26d0  CKPurpleCombo_StopFxAndAttack
//   [x] 0x3c27b8  CKPurpleCombo_CreateArray
//   [x] 0x3c2868  CKPurpleCombo_Create
//   [ ] 0x3c28c0  CKPurpleCombo_UpdateAttack_maybe
//   [x] 0x3c3048  CKPurpleCombo_Load
//   [ ] 0x3c3880  CKPurpleCombo_Save
//   [ ] 0x3c4158  CKPurpleCombo_UpdateMovement_maybe
//   [ ] 0x3c48e0  CKPurpleCombo_SetFxActive
//
//   [ ] 0x9c01b0  CKPurpleCombo_IsKindOfClass  [inline]
//   [ ] 0x9c0200  CKPurpleCombo_GetClassType  [inline]
//   [ ] 0x9c0208  CKPurpleCombo_GetClassID  [inline]
//   [ ] 0x9c0210  CKPurpleCombo_StartEmitterFx  [inline]
#include "k2000/logic/CKPurpleCombo.h"

#include "k2000/io/IKFile.h"

// 0x003c3048 CKPurpleCombo_Load: CKAttackMoveElement's data, then (type 0 only) 160 bytes: six references,
// three passes over seven per-index fields, two floats and five references.
int32_t CKPurpleCombo::Load(IKFile* file, int32_t type) {
    CKAttackMoveElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk220);
        IKFile_ReadRef(file, &m_unk244);
        IKFile_ReadRef(file, &m_unk248);
        IKFile_ReadRef(file, &m_unk21c);
        IKFile_ReadRef(file, &m_unk224);
        IKFile_ReadRef(file, &m_unk240);
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
        IKFile_ReadRef(file, &m_unk234);
        IKFile_ReadRef(file, &m_unk238);
    }
    return 1;
}
