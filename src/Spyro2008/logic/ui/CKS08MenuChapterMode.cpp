// CKS08MenuChapterMode.cpp - reconstructed original translation unit 0x548a88-0x549bb0 (GAME_TOC1, main_toc1), 19 functions, 16 live.
// Primary class: CKS08MenuChapterMode  key 0xafcc  category Logic  size 0xf8  vtable 0xb2c340
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x548a88  CKS08MenuChapterMode_Delete
//   [ ] 0x548ad8  CKS08MenuChapterMode_Construct  [dead]
//   [ ] 0x548b80  CKS08MenuChapterMode_Save
//   [ ] 0x548ba8  CKS08MenuChapterMode_RecursiveRegistration
//   [ ] 0x548cb8  CKS08MenuChapterMode_Destroy
//   [x] 0x548ce0  CKS08MenuChapterMode_DeleteArray
//   [ ] 0x548d88  RegisterCKS08MenuChapterModeClass
//   [ ] 0x548e10  _GLOBAL__D_548e10
//   [ ] 0x548e20  _GLOBAL__I_548e20
//   [ ] 0x548e30  FUN_00548e30  [dead]
//   [ ] 0x548ea8  CKS08MenuChapterMode_vfE8
//   [ ] 0x548f90  CKS08MenuChapterMode_OnMenuState_maybe
//   [ ] 0x549220  CKS08MenuChapterMode_Construct_2  [dead]
//   [x] 0x5492c8  CKS08MenuChapterMode_CreateArray
//   [x] 0x549410  CKS08MenuChapterMode_Create
//   [x] 0x5494f8  CKS08MenuChapterMode_Load
//   [ ] 0x549808  CKS08MenuChapterMode_DeletingDestructor
//   [ ] 0x549940  CKS08MenuChapterMode_Destructor
//   [ ] 0x549a78  CKS08MenuChapterMode_Destructor_2
//
//   [x] 0x9c97c8  CKS08MenuChapterMode_IsKindOfClass  [inline]
//   [x] 0x9c9808  CKS08MenuChapterMode_GetClassType  [inline]
//   [x] 0x9c9810  CKS08MenuChapterMode_GetClassID  [inline]
//   [x] 0x9c9818  CKS08MenuChapterMode_vfB8  [inline]
//   [x] 0x9c9820  CKS08MenuChapterMode_vfE0  [inline]
//   [x] 0x9c9828  CKS08MenuChapterMode_vfBC  [inline]
//   [x] 0x9c9830  CKS08MenuChapterMode_vfC0  [inline]
//   [x] 0x9c9840  CKS08MenuChapterMode_GetWidgetSlotCount  [inline]
//   [x] 0x9c9848  CKS08MenuChapterMode_GetWidgetSlots  [inline]
//   [x] 0x9c9858  CKS08MenuChapterMode_vfC4  [inline]
//   [x] 0x9c9860  CKS08MenuChapterMode_vfC8  [inline]
//   [x] 0x9c9870  CKS08MenuChapterMode_vfCC  [inline]
//   [ ] 0x9c9880  CKS08MenuChapterMode_vfF0  [inline]
//   [ ] 0x9c9888  CKS08MenuChapterMode_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuChapterMode.h"

#include "k2000/io/IKFile.h"

// 0x005494f8 CKS08MenuChapterMode_Load
int32_t CKS08MenuChapterMode::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnkdc);
    IKFile_ReadRef(file, &m_pColorizedFx);
    IKFile_ReadRef(file, &m_pColorizedData0);
    IKFile_ReadRef(file, &m_pColorizedData1);
    ReadF32LE(file, &m_fDuration);
    ReadU8(file, &m_unked);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}
