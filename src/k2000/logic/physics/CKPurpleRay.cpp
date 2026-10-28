// CKPurpleRay.cpp - reconstructed original translation unit 0x3c5af0-0x3c9a68 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKPurpleRay  key 0x930c  category Logic  size 0x228  vtable 0xb23f08
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3c5af0  CKPurpleRay_Delete
//   [ ] 0x3c5b40  CKPurpleRay_GetAbilityId
//   [ ] 0x3c5b48  CKPurpleRay_ResetRuntime
//   [ ] 0x3c5bd8  CKPurpleRay_GetFxSound_maybe
//   [ ] 0x3c5df8  CKPurpleRay_End
//   [ ] 0x3c5e90  CKPurpleRay_Update
//   [ ] 0x3c5eb8  CKPurpleRay_Start
//   [ ] 0x3c5f08  CKPurpleRay_PostLoad
//   [ ] 0x3c5f88  CKPurpleRay_RecursiveRegistration
//   [ ] 0x3c5fb0  CKPurpleRay_Destroy
//   [ ] 0x3c5ff0  CKPurpleRay_DeletingDestructor
//   [ ] 0x3c6038  CKPurpleRay_Destructor
//   [ ] 0x3c6068  CKPurpleRay_DestructBody
//   [x] 0x3c6098  CKPurpleRay_Construct
//   [ ] 0x3c60d0  CKPurpleRay_Construct_2
//   [x] 0x3c6108  CKPurpleRay_DeleteArray
//   [ ] 0x3c61a8  RegisterCKPurpleRayClass
//   [ ] 0x3c6230  _GLOBAL__D_3c6230
//   [ ] 0x3c6240  _GLOBAL__I_3c6240
//   [ ] 0x3c6250  CKPurpleRay_GetEmitterPosition
//   [ ] 0x3c6358  CKPurpleRay_StopBreathing
//   [x] 0x3c6430  CKPurpleRay_CreateArray
//   [x] 0x3c64e0  CKPurpleRay_Create
//   [x] 0x3c6538  CKPurpleRay_Load
//   [ ] 0x3c71f0  CKPurpleRay_Save
//   [ ] 0x3c7d90  CKPurpleRay_UpdateBeamAndImpact_maybe
//   [ ] 0x3c8ab0  CKPurpleRay_UpdateFx
//   [ ] 0x3c9080  CKPurpleRay_SetFxActive
//
//   [ ] 0x9c0238  CKPurpleRay_IsKindOfClass  [inline]
//   [ ] 0x9c0288  CKPurpleRay_GetClassType  [inline]
//   [ ] 0x9c0290  CKPurpleRay_GetClassID  [inline]
//   [ ] 0x9c0298  CKPurpleRay_StartEmitterFx  [inline]
#include "k2000/logic/physics/CKPurpleRay.h"

#include "k2000/io/IKFile.h"

// 0x003c6538 CKPurpleRay_Load: CKBreathElement's data, then (level data only) 0x88 bytes, read exactly like
// CKFearEyes_Load: three rows of three references, one reference, three rows of five words, five words and four
// references.
int32_t CKPurpleRay::Load(IKFile* file, int32_t type) {
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
