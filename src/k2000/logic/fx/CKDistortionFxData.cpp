// CKDistortionFxData.cpp - reconstructed original translation unit 0x1ae9a0-0x1af060 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CKDistortionFxData  key 0x394c  category Logic  size 0xc  vtable 0xb1c640
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1ae9a0  CKDistortionFxData_GetNodeClassKey
//   [ ] 0x1ae9a8  CKDistortionFxData_Destroy
//   [ ] 0x1ae9f0  CKDistortionFxData_PostLoad
//   [x] 0x1aea18  CKDistortionFxData_Load
//   [ ] 0x1aead8  CKDistortionFxData_Save
//   [ ] 0x1aeb98  CKDistortionFxData_RecursiveRegistration
//   [ ] 0x1aec10  CKDistortionFxData_MessageProc
//   [ ] 0x1af058  CKDistortionFxData_GetInfo
//
//   [ ] 0x9ab3b0  CKDistortionFxData_IsKindOfClass  [inline]
//   [x] 0x9ab3e8  CKDistortionFxData_GetClassType  [inline]
//   [x] 0x9ab3f0  CKDistortionFxData_GetClassID  [inline]
//   [ ] 0x9ab3f8  CKDistortionFxData_DeletingDestructor  [inline]
//   [ ] 0x9ab450  CKDistortionFxData_Destructor  [inline]
#include "k2000/logic/fx/CKDistortionFxData.h"

#include "k2000/io/IKFile.h"

// 0x001aea18 CKDistortionFxData_Load
int32_t CKDistortionFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pDistortionData);
    return 1;
}
