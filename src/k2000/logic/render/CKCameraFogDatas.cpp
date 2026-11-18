// CKCameraFogDatas.cpp - reconstructed original translation unit 0x143b58-0x144108 (GAME_TOC1, main_toc1), 15 functions, 12 live.
// Primary class: CKCameraFogDatas  key 0x3a4c  category Logic  size 0x28  vtable 0xb1a500
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x143b58  CKCameraFogDatas_Delete
//   [ ] 0x143ba8  CKCameraFogDatas_Construct  [dead]
//   [ ] 0x143bb8  RegisterCKCameraFogDatasClass
//   [ ] 0x143c30  _GLOBAL__I_143c30
//   [x] 0x143c40  CKCameraFogDatas_DeleteArray
//   [ ] 0x143ce8  CKCameraFogDatas_Construct_2  [dead]
//   [x] 0x143cf8  CKCameraFogDatas_Create
//   [x] 0x143d30  CKCameraFogDatas_CreateArray
//   [ ] 0x143dc8  CKCameraFogDatas_Save
//   [x] 0x143dd0  CKCameraFogDatas_RecursiveRegistration  (IKSerializable's: returns 1)
//   [x] 0x143dd8  CKCameraFogDatas_Destroy  (empty: IKSerializable's)
//   [x] 0x143de0  CKCameraFogDatas_Load
//   [x] 0x144098  CKCameraFogDatas_DeletingDestructor  (the destructor; delete)
//   [x] 0x1440d8  CKCameraFogDatas_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x1440f0  CKCameraFogDatas_Destructor_2  [dead]
//
//   [x] 0x9a78a0  CKCameraFogDatas_GetClassType  [inline]
//   [x] 0x9a78a8  CKCameraFogDatas_GetClassID  [inline]
//   [ ] 0x9a78b0  CKCameraFogDatas_IsKindOfClass  [inline]
#include "k2000/logic/render/CKCameraFogDatas.h"

#include "k2000/io/IKFile.h"

// 0x00143de0 CKCameraFogDatas_Load
int32_t CKCameraFogDatas::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, m_cMainColor, 4);
    ReadF32LE(file, &m_fUnk08);
    ReadF32LE(file, &m_fMainDensity);
    ReadRaw(file, m_cFarColor, 4);
    ReadF32LE(file, &m_fFarDistance);
    ReadF32LE(file, &m_fUnk18);
    ReadF32LE(file, &m_fFarDensity);
    ReadF32LE(file, &m_fFogEnd);
    ReadF32LE(file, &m_fFogStart);
    return 1;
}
