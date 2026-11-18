// Reconstructed original translation unit: 0x1d3568-0x1d3908 (GAME_TOC1, main_toc1), 15 functions, 12 live.
// Primary class: CKSpark  key 0x25cc  category Logic  size 0x68  vtable 0xb1d8b0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d3568  CKSpark_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x1d35b8  CKSpark_Construct  [dead]
//   [ ] 0x1d35d0  RegisterCKSparkClass
//   [ ] 0x1d3648  _GLOBAL__I_1d3648
//   [x] 0x1d3658  CKSpark_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x1d36f8  CKSpark_Construct_2  [dead]
//   [x] 0x1d3710  CKSpark_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1d37b0  CKSpark_Create  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x1d37f0  CKSpark_Save
//   [x] 0x1d37f8  CKSpark_Load
//   [x] 0x1d3888  CKSpark_RecursiveRegistration  (nothing)
//   [x] 0x1d3890  CKSpark_Destroy  (empty)
//   [ ] 0x1d3898  CKSpark_Destructor_2  [dead]
//   [x] 0x1d38b0  CKSpark_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x1d38f0  CKSpark_Destructor  (C++ destructor)
//
//   [x] 0x9ad2e0  CKSpark_GetClassType  [inline]
//   [x] 0x9ad2e8  CKSpark_GetClassID  [inline]
//   [x] 0x9ad2f0  CKSpark_IsKindOfClass  [inline]
#include "k2000/logic/fx/CKSpark.h"

#include "k2000/io/IKFile.h"

// 0x001d37f8 CKSpark_Load: level files hold the reference (no base Load).
int32_t CKSpark::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pRef);
    return 1;
}
