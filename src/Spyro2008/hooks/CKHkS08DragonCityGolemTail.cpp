// CKHkS08DragonCityGolemTail.cpp - reconstructed original translation unit 0x4d6cc8-0x4d7218 (GAME_TOC1, main_toc1), 24 functions, 22 live.
// Primary class: CKHkS08DragonCityGolemTail  key 0x33c2  category Hook  size 0xc0  vtable 0xb29f20
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d6cc8  CKHkS08DragonCityGolemTail_Delete
//   [ ] 0x4d6d18  CKHkS08DragonCityGolemTail_vf100
//   [ ] 0x4d6d20  CKHkS08DragonCityGolemTail_vf104
//   [ ] 0x4d6d28  CKHkS08DragonCityGolemTail_vf108
//   [ ] 0x4d6d30  RegisterCKHkS08DragonCityGolemTailClass
//   [ ] 0x4d6da8  _GLOBAL__I_4d6da8
//   [ ] 0x4d6db8  CKHkS08DragonCityGolemTail_Update
//   [ ] 0x4d6de0  CKHkS08DragonCityGolemTail_Resume
//   [ ] 0x4d6e08  CKHkS08DragonCityGolemTail_Pause
//   [ ] 0x4d6e30  CKHkS08DragonCityGolemTail_Stop
//   [ ] 0x4d6e58  CKHkS08DragonCityGolemTail_Start
//   [ ] 0x4d6e80  CKHkS08DragonCityGolemTail_PostLoad
//   [x] 0x4d6ea8  CKHkS08DragonCityGolemTail_Load
//   [ ] 0x4d6ed0  CKHkS08DragonCityGolemTail_Save
//   [ ] 0x4d6ef8  CKHkS08DragonCityGolemTail_RecursiveRegistration
//   [ ] 0x4d6f20  CKHkS08DragonCityGolemTail_Destroy
//   [ ] 0x4d6f48  CKHkS08DragonCityGolemTail_DeletingDestructor
//   [ ] 0x4d6f90  CKHkS08DragonCityGolemTail_Destructor
//   [ ] 0x4d6fc0  CKHkS08DragonCityGolemTail_DestructBody
//   [ ] 0x4d6ff0  CKHkS08DragonCityGolemTail_Construct  [dead]
//   [ ] 0x4d7028  CKHkS08DragonCityGolemTail_Construct_2  [dead]
//   [x] 0x4d7060  CKHkS08DragonCityGolemTail_DeleteArray
//   [x] 0x4d7108  CKHkS08DragonCityGolemTail_Create
//   [x] 0x4d7160  CKHkS08DragonCityGolemTail_CreateArray
//
//   [ ] 0x9c5f38  CKHkS08DragonCityGolemTail_IsKindOfClass  [inline]
//   [ ] 0x9c5f98  CKHkS08DragonCityGolemTail_GetClassType  [inline]
//   [ ] 0x9c5fa0  CKHkS08DragonCityGolemTail_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08DragonCityGolemTail.h"

// 0x004d6ea8 CKHkS08DragonCityGolemTail_Load: CKHkGolem's part only.
int32_t CKHkS08DragonCityGolemTail::Load(IKFile* file, int32_t type) {
    CKHkGolem::Load(file, type);
    return 1;
}
