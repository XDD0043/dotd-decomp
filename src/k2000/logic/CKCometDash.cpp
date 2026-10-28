// CKCometDash.cpp - reconstructed original translation unit 0x385a78-0x389ec8 (GAME_TOC1, main_toc1), 30 functions, 30 live.
// Primary class: CKCometDash  key 0x9a4c  category Logic  size 0x264  vtable 0xb23620
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x385a78  CKCometDash_Delete
//   [ ] 0x385ac8  CKCometDash_GetAbilityId
//   [ ] 0x385ad0  CKCometDash_GetFamilyId
//   [ ] 0x385ad8  CKCometDash_SetAttackActive_maybe
//   [ ] 0x385b88  CKCometDash_IsGroundTrailActive_maybe
//   [ ] 0x385be8  CKCometDash_End
//   [ ] 0x385c78  CKCometDash_StopFxAndAttack
//   [ ] 0x385d60  CKCometDash_Update
//   [ ] 0x385d88  CKCometDash_Start
//   [ ] 0x385df8  CKCometDash_ResetRuntime
//   [ ] 0x385e50  CKCometDash_RecursiveRegistration
//   [ ] 0x385e78  CKCometDash_Destroy
//   [x] 0x385ea0  CKCometDash_Construct
//   [ ] 0x385ed8  CKCometDash_Construct_2
//   [x] 0x385f10  CKCometDash_DeleteArray
//   [ ] 0x385fb0  CKCometDash_DeletingDestructor
//   [ ] 0x385ff8  CKCometDash_Destructor
//   [ ] 0x386028  CKCometDash_DestructBody
//   [ ] 0x386058  RegisterCKCometDashClass
//   [ ] 0x3860e0  _GLOBAL__D_3860e0
//   [ ] 0x3860f0  _GLOBAL__I_3860f0
//   [ ] 0x386100  CKCometDash_PostLoad
//   [ ] 0x386220  CKCometDash_SteerTowardsTarget_maybe
//   [x] 0x386350  CKCometDash_CreateArray
//   [x] 0x386400  CKCometDash_Create
//   [ ] 0x386458  CKCometDash_UpdateAttack_maybe
//   [x] 0x386be0  CKCometDash_Load
//   [ ] 0x387730  CKCometDash_Save
//   [ ] 0x3882d0  CKCometDash_UpdateMovement_maybe
//   [ ] 0x388a58  CKCometDash_SetFxActive
//
//   [ ] 0x9bfa68  CKCometDash_IsKindOfClass  [inline]
//   [ ] 0x9bfab8  CKCometDash_GetClassType  [inline]
//   [ ] 0x9bfac0  CKCometDash_GetClassID  [inline]
//   [ ] 0x9bfac8  CKCometDash_StartEmitterFx  [inline]
#include "k2000/logic/CKCometDash.h"

#include "k2000/io/IKFile.h"

// 0x00386be0 CKCometDash_Load: CKAttackMoveElement's data, then (type 0 only) 164 bytes, interleaving
// references and floats (the first per-index pass is unrolled in the original; same order as this loop).
int32_t CKCometDash::Load(IKFile* file, int32_t type) {
    CKAttackMoveElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk220);
        IKFile_ReadRef(file, &m_unk24c);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_unk1a8[i]);
            ReadS32LE(file, &m_unk1b4[i]);
            ReadS32LE(file, &m_unk1c0[i]);
            ReadS32LE(file, &m_unk1cc[i]);
        }
        ReadF32LE(file, &m_unk208);
        ReadF32LE(file, &m_unk20c);
        IKFile_ReadRef(file, &m_unk250);
        ReadF32LE(file, &m_unk1d8[0]);
        ReadF32LE(file, &m_unk1d8[1]);
        ReadF32LE(file, &m_unk1d8[2]);
        IKFile_ReadRef(file, &m_unk21c);
        ReadF32LE(file, &m_unk210[0]);
        ReadF32LE(file, &m_unk210[1]);
        ReadF32LE(file, &m_unk210[2]);
        IKFile_ReadRef(file, &m_unk230);
        IKFile_ReadRef(file, &m_unk234);
        IKFile_ReadRef(file, &m_unk238);
        IKFile_ReadRef(file, &m_unk224);
        IKFile_ReadRef(file, &m_unk240);
        for (int32_t i = 0; i < 3; ++i) {
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk1e4[i]), 3);
        }
        IKFile_ReadRef(file, &m_unk228);
        IKFile_ReadRef(file, &m_unk22c);
        IKFile_ReadRef(file, &m_unk244);
    }
    return 1;
}
