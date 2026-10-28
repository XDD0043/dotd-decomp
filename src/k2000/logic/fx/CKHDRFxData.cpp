// CKHDRFxData.cpp - reconstructed original translation unit 0x1be2a0-0x1bef50 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKHDRFxData  key 0xf0c  category Logic  size 0x18  vtable 0xb1ce10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1be2a0  CKHDRFxData_Delete
//   [x] 0x1be2f0  CKHDRFxData_GetNodeClassKey
//   [ ] 0x1be2f8  RegisterCKHDRFxDataClass
//   [ ] 0x1be370  _GLOBAL__I_1be370
//   [ ] 0x1be380  CKHDRFxData_PostLoad
//   [x] 0x1be3c0  CKHDRFxData_Load
//   [ ] 0x1be4c0  CKHDRFxData_Save
//   [ ] 0x1be4e8  CKHDRFxData_RecursiveRegistration
//   [x] 0x1be560  CKHDRFxData_DeleteArray
//   [x] 0x1be608  CKHDRFxData_Create
//   [x] 0x1be650  CKHDRFxData_CreateArray
//   [ ] 0x1be6f8  CKHDRFxData_GetInfo
//   [ ] 0x1be700  CKHDRFxData_Destroy
//   [ ] 0x1be708  CKHDRFxData_MessageProc
//
//   [ ] 0x9ac338  CKHDRFxData_IsKindOfClass  [inline]
//   [x] 0x9ac370  CKHDRFxData_GetClassType  [inline]
//   [x] 0x9ac378  CKHDRFxData_GetClassID  [inline]
//   [x] 0x9ac380  CKHDRFxData_vf50  [inline]
//   [ ] 0x9ac388  CKHDRFxData_Destructor  [inline]
//   [ ] 0x9ac3c8  CKHDRFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKHDRFxData.h"

#include "k2000/io/IKFile.h"

// 0x001be3c0 CKHDRFxData_Load
int32_t CKHDRFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pHDRData);
        ReadF32LE(file, &m_unk0c);
    }
    return 1;
}
