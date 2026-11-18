// CKCoreError.cpp - reconstructed original translation unit 0x12178-0x12f40 (GAME_TOC1, main_toc1), 22 functions, 14 live.
// Primary class: CKCoreError  key 0x8e  category Error  size 0x4  vtable 0xb12b88
// Other owners: Group (5), IKGroup (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x12178  CKCoreError_Delete
//   [ ] 0x121c8  CKCoreError_Construct  [dead]
//   [ ] 0x121d8  CKCoreError_Construct_2  [dead]
//   [x] 0x121e8  CKCoreError_GetErrorMessage
//   [ ] 0x12250  RegisterCKCoreErrorClass
//   [ ] 0x122c8  _GLOBAL__I_122c8
//   [x] 0x122d8  CKCoreError_DeleteArray
//   [x] 0x12378  CKCoreError_Create
//   [x] 0x123b0  CKCoreError_CreateArray
//   [x] 0x12440  CKCoreError_Destructor
//   [ ] 0x12458  CKCoreError_Destructor_2  [dead]
//   [x] 0x12470  CKCoreError_DeletingDestructor
//   [x] 0x124b0  Group_CanAcceptHookRecursive_maybe  (local copy)
//   [ ] 0x12618  Group_CanAcceptHookByClassId_maybe  [dead]
//   [ ] 0x12710  Group_CanAcceptHookByClassIdRecursive_maybe  [dead]
//   [ ] 0x12860  Group_RemoveHook_maybe  [dead]
//   [x] 0x12960  IKGroup_vf9C  (IKBaseGroup::Vf9C, k2000/groups/IKBaseGroup.h)
//   [ ] 0x12970  IKGroup_ContainsMember_maybe  [dead]
//   [x] 0x12a68  IKGroup_LevelReset  (IKBaseGroup::RecursiveRegistration, k2000/groups/IKBaseGroup.h)
//   [ ] 0x12b78  IKGroup_Save
//   [ ] 0x12ba0  Group_AddHook_maybe  [dead]
//   [x] 0x12ce8  IKGroup_Load  (inline in the header)
//
//   [x] 0x990f10  CKCoreError_GetClassID  [inline]
//   [x] 0x990f18  CKCoreError_GetClassType  [inline]
//   [x] 0x990f20  CKCoreError_Destroy  [inline]
//   [ ] 0x990f28  IKError_DeletingDestructor  [inline]
//   [x] 0x990f58  CKCoreError_IsKindOfClass  [inline]
//   [ ] 0x990f78  IKError_Destructor  [inline]
//   [ ] 0x990f88  KStub_Nop_990f88  [inline]
//   [ ] 0x990f90  KStub_Nop_990f90  [inline]
//   [ ] 0x990f98  KStub_Nop_990f98  [inline]
//   [ ] 0x990fa0  KStub_Nop_990fa0  [inline]
//   [ ] 0x990fa8  KStub_Nop_990fa8  [inline]
//   [ ] 0x990fb0  KStub_Nop_990fb0  [inline]
//   [ ] 0x990fb8  KStub_Return1_990fb8  [inline]
//   [ ] 0x990fc0  KStub_Nop_990fc0  [inline]
//   [ ] 0x990fc8  KStub_Nop_990fc8  [inline]
//   [ ] 0x990fd0  KStub_Return1_990fd0  [inline]
//   [ ] 0x990fd8  KStub_Return1_990fd8  [inline]
//   [ ] 0x991100  IKGroup_Load_2  [inline]
//   [ ] 0x991108  IKBaseGroup_LevelReset  [inline]
//   [ ] 0x992d08  IKGroup_IsKindOf  [inline]
//   [ ] 0x992d50  IKGroup_GetMemberListHead  [inline]
//   [ ] 0x992d60  IKGroup_vfB4  [inline]
//   [x] 0x992d70  IKGroup_CanAcceptMember_maybe  [inline]  (local copy)
//   [ ] 0x992e18  KStub_Nop_992e18  [inline]
//   [ ] 0x992e20  KStub_Nop_992e20  [inline]
//   [ ] 0x992e28  KStub_Return0_992e28  [inline]
//   [x] 0x992e30  IKGroup_AddMember  [inline]  (local copy)
//   [x] 0x992e70  IKGroup_RemoveMember  [inline]  (local copy)
//   [ ] 0x992fd8  IKGroup_DeletingDestructor  [inline]
//   [ ] 0x993020  IKGroup_Destructor  [inline]
//   [ ] 0x9ba708  IKGroup_GetMemberListHead_2  [inline]
//   [ ] 0x9ba718  IKGroup_vfB4_2  [inline]
//   [ ] 0x9ba728  IKGroup_CanAcceptMember_2_maybe  [inline]
//   [ ] 0x9ba7d0  IKGroup_vfE0  [inline]
//   [ ] 0x9ba7d8  IKGroup_vfE4  [inline]
//   [ ] 0x9ba7e0  IKGroup_vfE8  [inline]
//   [ ] 0x9ba7e8  IKGroup_AddMember_2  [inline]
//   [ ] 0x9ba828  IKGroup_RemoveMember_2  [inline]
//   [ ] 0x9ba8e8  IKGroup_IsKindOf_2  [inline]
//   [ ] 0x9ba930  IKGroup_Destructor_2  [inline]
//   [ ] 0x9ba950  IKGroup_DeletingDestructor_2  [inline]
//   [ ] 0x9c35a0  IKGroup_IsKindOf_3  [inline]
//   [ ] 0x9c3820  IKGroup_DeletingDestructor_3  [inline]
//   [ ] 0x9c3920  IKGroup_Destructor_3  [inline]
//   [ ] 0x9c49c0  IKGroup_IsKindOf_4  [inline]
//   [ ] 0x9c4c40  IKGroup_Destructor_4  [inline]
//   [ ] 0x9c4c60  IKGroup_DeletingDestructor_4  [inline]
//   [ ] 0x9c4f28  IKGroup_IsKindOf_5  [inline]
//   [ ] 0x9c51a8  IKGroup_DeletingDestructor_5  [inline]
//   [ ] 0x9c51f0  IKGroup_Destructor_5  [inline]
//   [ ] 0x9c5ad0  IKGroup_IsKindOf_6  [inline]
//   [ ] 0x9c5d50  IKGroup_Destructor_6  [inline]
//   [ ] 0x9c5d70  IKGroup_DeletingDestructor_6  [inline]
//   [ ] 0x9cc088  IKGroup_IsKindOf_7  [inline]
//   [ ] 0x9cc0d0  IKGroup_GetMemberListHead_3  [inline]
//   [ ] 0x9cc0e0  IKGroup_vfB4_3  [inline]
//   [ ] 0x9cc0f0  IKGroup_CanAcceptMember_3_maybe  [inline]
//   [ ] 0x9cc198  KStub_Nop_9cc198  [inline]
//   [ ] 0x9cc1a0  KStub_Nop_9cc1a0  [inline]
//   [ ] 0x9cc1a8  KStub_Return0_9cc1a8  [inline]
//   [ ] 0x9cc1b0  IKGroup_AddMember_3  [inline]
//   [ ] 0x9cc1f0  IKGroup_RemoveMember_3  [inline]
//   [ ] 0x9cc2b0  IKGroup_Destructor_7  [inline]
//   [ ] 0x9cc2d0  IKGroup_DeletingDestructor_7  [inline]
#include "k2000/core/CKCoreError.h"

// C2.8 port-rest R02. The messages are the original bytes (Latin-1, octal escapes); nothing displays them.

// 0x000121e8 CKCoreError_GetErrorMessage
const char* CKCoreError::GetErrorMessage(int32_t code) {
    if (code == 0x20001)
        return "La sauvegarde de cet objet a chang\351 et on a plus besoin de lire les anciennes donn\351es. il faut donc "
               "faire un seek dans le fichier.";
    if (code == 0x20002)
        return "La lecture de l'objet n'a pas \351t\351 faite avec succ\350s (surement \340 cause de changement de "
               "version). Les donn\351es de l'objet sont donc remis \340 leur valeur par d\351faut.";
    if (code == 0x20000) return "Le fichier demand\351 n'a pu \352tre ouvert.";
    return "L'erreur n'est pas document\351e par le module KCore";
}
