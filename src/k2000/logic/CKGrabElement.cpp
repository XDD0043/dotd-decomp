// CKGrabElement.cpp - reconstructed original translation unit 0x3a5e60-0x3a9c50 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKGrabElement  key 0x9fcc  category Logic  size 0x140  vtable 0xb23ae0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3a5e60  CKGrabElement_Delete
//   [x] 0x3a5eb0  CKGrabElement_Construct
//   [ ] 0x3a5ec0  CKGrabElement_Construct_2  [dead]
//   [ ] 0x3a5ed0  CKGrabElement_GetAbilityId
//   [ ] 0x3a5ed8  CKGrabElement_GetFamilyId
//   [ ] 0x3a5ee0  CKGrabElement_Stop
//   [ ] 0x3a5f70  CKGrabElement_End
//   [ ] 0x3a6058  CKGrabElement_ApplyHeroControl
//   [ ] 0x3a6650  CKGrabElement_ResetRuntime
//   [ ] 0x3a66a0  CKGrabElement_ApplyDamageParams
//   [x] 0x3a6ba0  CKGrabElement_DeleteArray
//   [ ] 0x3a6c48  CKGrabElement_StartEmitterFx
//   [ ] 0x3a6f10  RegisterCKGrabElementClass
//   [ ] 0x3a6f98  _GLOBAL__D_3a6f98
//   [ ] 0x3a6fa8  _GLOBAL__I_3a6fa8
//   [ ] 0x3a6fb8  CKGrabElement_ReleaseAndStopFx_maybe
//   [ ] 0x3a7070  CKGrabElement_Update
//   [ ] 0x3a7c80  CKGrabElement_Start
//   [ ] 0x3a7eb8  CKGrabElement_GrabTarget_maybe
//   [x] 0x3a8298  CKGrabElement_CreateArray
//   [x] 0x3a8330  CKGrabElement_Create
//   [ ] 0x3a8368  CKGrabElement_RecursiveRegistration
//   [ ] 0x3a8370  CKGrabElement_PostLoad
//   [ ] 0x3a83b8  CKGrabElement_Destroy
//   [x] 0x3a83c0  CKGrabElement_Load
//   [ ] 0x3a9018  CKGrabElement_Save
//   [ ] 0x3a9bc8  CKGrabElement_Destructor
//   [ ] 0x3a9be8  CKGrabElement_BaseDestructor
//   [ ] 0x3a9c08  CKGrabElement_DeletingDestructor
//
//   [ ] 0x9bfec0  CKGrabElement_GetClassType  [inline]
//   [ ] 0x9bfec8  CKGrabElement_GetClassID  [inline]
//   [ ] 0x9bfed0  CKGrabElement_SetFxActive  [inline]
//   [ ] 0x9bfee0  CKGrabElement_vf80  [inline]
//   [ ] 0x9bfee8  CKGrabElement_vf84  [inline]
//   [ ] 0x9bfef8  CKGrabElement_IsKindOfClass  [inline]
#include "k2000/logic/CKGrabElement.h"

#include "k2000/io/IKFile.h"

// 0x003a83c0 CKGrabElement_Load: level data only (type 0, K_LEVEL_PLATEFORMS); 0x10e bytes. Three rows of
// fifteen words and two bytes, then the scalars and three references; every word byte-swapped.
int32_t CKGrabElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk08[i]);
            ReadF32LE(file, &m_unk14[i]);
            ReadS32LE(file, &m_unk2c[i]);
            ReadF32LE(file, &m_unk38[i]);
            ReadF32LE(file, &m_unk44[i]);
            ReadF32LE(file, &m_unk50[i]);
            ReadU32LE(file, &m_unk5c[i]);
            ReadU32LE(file, &m_unk68[i]);
            ReadU32LE(file, &m_unk74[i]);
            ReadU32LE(file, &m_unk80[i]);
            ReadU32LE(file, &m_unk8c[i]);
            ReadU32LE(file, &m_unk98[i]);
            ReadU32LE(file, &m_unkA4[i]);
            ReadF32LE(file, &m_unkB0[i]);
            ReadU32LE(file, &m_unkBc[i]);
            ReadU8(file, &m_unkC8[i]);
            ReadU8(file, &m_unkCb[i]);
        }
        ReadU8(file, &m_unkD8);
        ReadU8(file, &m_unkD9);
        ReadU8(file, &m_unkDa);
        ReadF32LE(file, &m_unkDc);
        ReadF32LE(file, &m_unkE0);
        ReadF32LE(file, &m_unkF0);
        ReadU8(file, &m_unkE4);
        ReadU8(file, &m_unkE5);
        ReadU8(file, &m_unkE6);
        ReadF32LE(file, &m_unkE8);
        ReadF32LE(file, &m_unkEc);
        ReadF32LE(file, &m_unkF4);
        ReadU8(file, &m_unkF8);
        ReadU8(file, &m_unkF9);
        ReadF32LE(file, &m_unkFc);
        ReadF32LE(file, &m_unk100);
        IKFile_ReadRef(file, &m_unk138);
        ReadU8(file, &m_unk104);
        ReadU8(file, &m_unk105);
        ReadU8(file, &m_unk106);
        ReadF32LE(file, &m_unk108);
        ReadF32LE(file, &m_unk10c);
        ReadF32LE(file, &m_unk110);
        ReadU8(file, &m_unk114);
        ReadF32LE(file, &m_unk118);
        IKFile_ReadRef(file, &m_unkD0);
        ReadF32LE(file, &m_unk20);
        ReadF32LE(file, &m_unk24);
        ReadF32LE(file, &m_unk28);
        IKFile_ReadRef(file, &m_unk11c);
    }
    return 1;
}
