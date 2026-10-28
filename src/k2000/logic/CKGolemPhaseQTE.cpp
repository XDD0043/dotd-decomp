// CKGolemPhaseQTE.cpp - reconstructed original translation unit 0x4bddd8-0x4bed00 (GAME_TOC1, main_toc1), 43 functions, 37 live.
// Primary class: CKGolemPhaseQTE  key 0xa10c  category Logic  size 0x2c  vtable 0xb291d0
// Other owners: CKHkGolem (8)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4bddd8  CKGolemPhaseQTE_Delete
//   [ ] 0x4bde28  CKGolemPhaseQTE_ResetPhases_maybe
//   [ ] 0x4bde30  CKGolemPhaseQTE_vf60
//   [ ] 0x4bde38  CKGolemPhaseQTE_vf64
//   [ ] 0x4bde40  CKGolemPhaseQTE_vf68
//   [ ] 0x4bde48  CKGolemPhaseQTE_MessageProc
//   [ ] 0x4bde80  CKGolemPhaseQTE_vf84
//   [ ] 0x4bde88  RegisterCKGolemPhaseQTEClass
//   [ ] 0x4bdf00  _GLOBAL__I_4bdf00
//   [ ] 0x4bdf10  CKGolemPhaseQTE_GetDamageSinceUpdate_maybe
//   [ ] 0x4bdf50  CKGolemPhaseQTE_vf74
//   [ ] 0x4bdf90  CKGolemPhaseQTE_MarkDamageBaseline_maybe
//   [ ] 0x4bdfc8  CKGolemPhaseQTE_GetDamageSincePhaseStart_maybe
//   [ ] 0x4be008  CKGolemPhaseQTE_vf58
//   [ ] 0x4be038  CKGolemPhaseQTE_Save
//   [ ] 0x4be060  CKGolemPhaseQTE_RecursiveRegistration
//   [ ] 0x4be088  CKGolemPhaseQTE_Destroy
//   [ ] 0x4be0b0  CKGolemPhaseQTE_DeletingDestructor
//   [ ] 0x4be0f8  CKGolemPhaseQTE_Destructor
//   [ ] 0x4be128  CKGolemPhaseQTE_DestructBody
//   [x] 0x4be158  CKGolemPhaseQTE_Construct  [dead]
//   [ ] 0x4be190  CKGolemPhaseQTE_Construct_2  [dead]
//   [x] 0x4be1c8  CKGolemPhaseQTE_DeleteArray
//   [ ] 0x4be268  CKGolemPhaseQTE_Start
//   [ ] 0x4be2e0  CKGolemPhaseQTE_vf80
//   [ ] 0x4be2f8  CKGolemPhaseQTE_vf7C
//   [ ] 0x4be310  CKGolemPhaseQTE_Update_maybe
//   [x] 0x4be3b8  CKGolemPhaseQTE_CreateArray
//   [x] 0x4be468  CKGolemPhaseQTE_Create
//   [x] 0x4be4c0  CKGolemPhaseQTE_Load
//   [ ] 0x4be6f0  CKHkGolem_Delete
//   [ ] 0x4be740  FUN_004be740  [dead]
//   [ ] 0x4be8e8  FUN_004be8e8  [dead]
//   [ ] 0x4bea90  CKHkGolem_ReleaseEntryObjectsById_maybe  [dead]
//   [ ] 0x4bec68  CKHkGolem_GetDamageTakenSinceMark_maybe
//   [ ] 0x4bec80  CKHkGolem_GetTotalDamageTaken
//   [ ] 0x4bec88  CKHkGolem_MarkDamageTaken_maybe
//   [ ] 0x4bec98  FUN_004bec98  [dead]
//   [ ] 0x4becb0  CKHkGolem_GetTime50_maybe
//   [ ] 0x4becb8  CKHkGolem_GetTime54_maybe
//   [ ] 0x4becc0  KStub_Return1_4becc0
//   [ ] 0x4becc8  CKHkGolem_ApplyDamagePoints_maybe
//   [ ] 0x4becf8  KStub_Nop_4becf8
//
//   [ ] 0x9c56a0  CKGolemPhaseQTE_IsKindOfClass  [inline]
//   [ ] 0x9c56d8  CKGolemPhaseQTE_GetClassType  [inline]
//   [ ] 0x9c56e0  CKGolemPhaseQTE_GetClassID  [inline]
#include "k2000/logic/CKGolemPhaseQTE.h"

#include "k2000/io/IKFile.h"

// 0x004be4c0 CKGolemPhaseQTE_Load: CKGolemPhaseBase's data, then, for K_LEVEL_PLATEFORMS only, a reference and
// five words.
int32_t CKGolemPhaseQTE::Load(IKFile* file, int32_t type) {
    CKGolemPhaseBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk08);
        ReadS32LE(file, &m_unk18);
        ReadS32LE(file, &m_unk1c);
        ReadS32LE(file, &m_unk20);
        ReadS32LE(file, &m_unk24);
        ReadS32LE(file, &m_unk28);
    }
    return 1;
}
