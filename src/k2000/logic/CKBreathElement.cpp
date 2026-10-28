// CKBreathElement.cpp - reconstructed original translation unit 0x380ed0-0x385a78 (GAME_TOC1, main_toc1), 30 functions, 29 live.
// Primary class: CKBreathElement  key 0x914c  category Logic  size 0x178  vtable 0xb23588
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x380ed0  CKBreathElement_Delete
//   [ ] 0x380f20  CKBreathElement_Construct_2  [dead]
//   [ ] 0x380f40  CKBreathElement_GetAbilityId
//   [ ] 0x380f48  CKBreathElement_GetFamilyId
//   [ ] 0x380f50  CKBreathElement_Start
//   [ ] 0x381190  CKBreathElement_Stop
//   [ ] 0x381220  CKBreathElement_End
//   [ ] 0x381330  CKBreathElement_ApplyHeroControl
//   [ ] 0x381928  CKBreathElement_StopBreathing
//   [ ] 0x381980  CKBreathElement_ApplyDamageParams
//   [x] 0x381eb8  CKBreathElement_Construct
//   [ ] 0x381ed8  CKBreathElement_ResetRuntime
//   [x] 0x381f88  CKBreathElement_DeleteArray
//   [ ] 0x382028  CKBreathElement_StartEmitterFx
//   [ ] 0x3822f0  RegisterCKBreathElementClass
//   [ ] 0x382378  _GLOBAL__D_382378
//   [ ] 0x382388  _GLOBAL__I_382388
//   [ ] 0x382398  CKBreathElement_GetEmitterPosition
//   [ ] 0x382430  CKBreathElement_Update
//   [x] 0x382c80  CKBreathElement_CreateArray
//   [x] 0x382d40  CKBreathElement_Create
//   [ ] 0x382d90  CKBreathElement_RecursiveRegistration
//   [ ] 0x382d98  CKBreathElement_PostLoad
//   [ ] 0x382de0  CKBreathElement_Destroy
//   [ ] 0x382de8  CKBreathElement_Destructor
//   [ ] 0x382e68  CKBreathElement_UpdateDamageSpheres
//   [ ] 0x383bb0  CKBreathElement_DestructBody
//   [x] 0x383c30  CKBreathElement_Load
//   [ ] 0x384ba8  CKBreathElement_DeletingDestructor
//   [ ] 0x384c30  CKBreathElement_Save
//
//   [ ] 0x9bfa10  CKBreathElement_GetClassType  [inline]
//   [ ] 0x9bfa18  CKBreathElement_GetClassID  [inline]
//   [ ] 0x9bfa20  CKBreathElement_SetFxActive  [inline]
//   [ ] 0x9bfa28  CKBreathElement_UpdateFx  [inline]
//   [ ] 0x9bfa30  CKBreathElement_IsKindOfClass  [inline]
#include "k2000/logic/CKBreathElement.h"

#include "k2000/io/IKFile.h"

// 0x00381eb8 CKBreathElement_Construct: the vtable, then three runtime words (CKBreathElement_Create inlines the same).
CKBreathElement::CKBreathElement() {
    m_unk124 = nullptr;
    m_unk128 = 1;
    m_unk12c = 0;
}

// 0x00383c30 CKBreathElement_Load: level data only (type 0, K_LEVEL_PLATEFORMS); 0x133 bytes. Three rows of
// fourteen words and two bytes, then the scalars and two references; every word byte-swapped.
int32_t CKBreathElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk08[i]);
            ReadU32LE(file, &m_unk20[i]);
            ReadS32LE(file, &m_unk38[i]);
            ReadF32LE(file, &m_unk44[i]);
            ReadF32LE(file, &m_unk50[i]);
            ReadF32LE(file, &m_unk5c[i]);
            ReadF32LE(file, &m_unk68[i]);
            ReadF32LE(file, &m_unk74[i]);
            ReadU32LE(file, &m_unk80[i]);
            ReadU32LE(file, &m_unk8c[i]);
            ReadU32LE(file, &m_unk98[i]);
            ReadU32LE(file, &m_unkA4[i]);
            ReadU32LE(file, &m_unkB0[i]);
            ReadU32LE(file, &m_unkBc[i]);
            ReadU8(file, &m_unkD4[i]);
            ReadU8(file, &m_unkD7[i]);
        }
        ReadU8(file, &m_unkDa);
        ReadU8(file, &m_unkDb);
        ReadU8(file, &m_unkDc);
        ReadF32LE(file, &m_unkE0);
        ReadF32LE(file, &m_unkE4);
        ReadF32LE(file, &m_unkF4);
        ReadU8(file, &m_unkE8);
        ReadU8(file, &m_unkE9);
        ReadU8(file, &m_unkEa);
        ReadF32LE(file, &m_unkEc);
        ReadF32LE(file, &m_unkF0);
        ReadF32LE(file, &m_unkF8);
        ReadF32LE(file, &m_unk130);
        ReadF32LE(file, &m_unk134);
        ReadF32LE(file, &m_unk138);
        ReadU8(file, &m_unkFc);
        ReadU8(file, &m_unkFd);
        ReadF32LE(file, &m_unk100);
        ReadF32LE(file, &m_unk104);
        ReadU32LE(file, &m_unkC8);
        ReadU32LE(file, &m_unkCc);
        ReadU32LE(file, &m_unkD0);
        IKFile_ReadRef(file, &m_unk170);
        ReadU8(file, &m_unk108);
        ReadU8(file, &m_unk109);
        ReadU8(file, &m_unk10a);
        ReadF32LE(file, &m_unk10c);
        ReadF32LE(file, &m_unk110);
        ReadF32LE(file, &m_unk114);
        ReadU8(file, &m_unk118);
        ReadF32LE(file, &m_unk11c);
        ReadF32LE(file, &m_unk13c);
        ReadF32LE(file, &m_unk140);
        ReadF32LE(file, &m_unk144);
        ReadF32LE(file, &m_unk148);
        ReadF32LE(file, &m_unk2c);
        ReadF32LE(file, &m_unk30);
        ReadF32LE(file, &m_unk34);
        IKFile_ReadRef(file, &m_unk120);
        ReadF32LE(file, &m_unk14);
        ReadF32LE(file, &m_unk18);
        ReadF32LE(file, &m_unk1c);
        ReadU8(file, &m_unk14c);
    }
    return 1;
}
