// CKFearEyes.cpp - reconstructed original translation unit 0x39cf88-0x3a0f00 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKFearEyes  key 0x92cc  category Logic  size 0x228  vtable 0xb23920
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x39cf88  CKFearEyes_Delete
//   [ ] 0x39cfd8  CKFearEyes_GetAbilityId
//   [ ] 0x39cfe0  CKFearEyes_ResetRuntime
//   [ ] 0x39d070  CKFearEyes_GetFxSound_maybe
//   [ ] 0x39d290  CKFearEyes_End
//   [ ] 0x39d328  CKFearEyes_Update
//   [ ] 0x39d350  CKFearEyes_Start
//   [ ] 0x39d3a0  CKFearEyes_PostLoad
//   [ ] 0x39d420  CKFearEyes_RecursiveRegistration
//   [ ] 0x39d448  CKFearEyes_Destroy
//   [ ] 0x39d488  CKFearEyes_DeletingDestructor
//   [ ] 0x39d4d0  CKFearEyes_Destructor
//   [ ] 0x39d500  CKFearEyes_DestructBody
//   [x] 0x39d530  CKFearEyes_Construct
//   [ ] 0x39d568  CKFearEyes_Construct_2
//   [x] 0x39d5a0  CKFearEyes_DeleteArray
//   [ ] 0x39d640  RegisterCKFearEyesClass
//   [ ] 0x39d6c8  _GLOBAL__D_39d6c8
//   [ ] 0x39d6d8  _GLOBAL__I_39d6d8
//   [ ] 0x39d6e8  CKFearEyes_GetEmitterPosition
//   [ ] 0x39d7f0  CKFearEyes_StopBreathing
//   [x] 0x39d8c8  CKFearEyes_CreateArray
//   [x] 0x39d978  CKFearEyes_Create
//   [x] 0x39d9d0  CKFearEyes_Load
//   [ ] 0x39e688  CKFearEyes_Save
//   [ ] 0x39f228  CKFearEyes_UpdateBeamAndImpact_maybe
//   [ ] 0x39ff48  CKFearEyes_UpdateFx
//   [ ] 0x3a0518  CKFearEyes_SetFxActive
//
//   [ ] 0x9bfd28  CKFearEyes_IsKindOfClass  [inline]
//   [ ] 0x9bfd78  CKFearEyes_GetClassType  [inline]
//   [ ] 0x9bfd80  CKFearEyes_GetClassID  [inline]
//   [ ] 0x9bfd88  CKFearEyes_StartEmitterFx  [inline]
#include "k2000/logic/CKFearEyes.h"

#include "k2000/io/IKFile.h"

// 0x0039d9d0 CKFearEyes_Load: CKBreathElement's data, then (level data only) 0x88 bytes: three rows of three
// references, one reference, three rows of five words, five words and four references.
int32_t CKFearEyes::Load(IKFile* file, int32_t type) {
    CKBreathElement::Load(file, type);
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            IKFile_ReadRef(file, &m_unk1c8[i]);
            IKFile_ReadRef(file, &m_unk1d4[i]);
            IKFile_ReadRef(file, &m_unk1e8[i]);
        }
        IKFile_ReadRef(file, &m_unk204);
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk178[i]);
            ReadU32LE(file, &m_unk184[i]);
            ReadU32LE(file, &m_unk190[i]);
            ReadF32LE(file, &m_unk19c[i]);
            ReadF32LE(file, &m_unk1a8[i]);
        }
        ReadF32LE(file, &m_unk1b4);
        ReadF32LE(file, &m_unk1b8);
        ReadF32LE(file, &m_unk1bc);
        ReadF32LE(file, &m_unk1c0);
        ReadF32LE(file, &m_unk1c4);
        IKFile_ReadRef(file, &m_unk208);
        IKFile_ReadRef(file, &m_unk1f4[0]);
        IKFile_ReadRef(file, &m_unk1f4[1]);
        IKFile_ReadRef(file, &m_unk1f4[2]);
    }
    return 1;
}
