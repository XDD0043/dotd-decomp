// CKSrvFxParticlesAccessor.cpp - reconstructed original translation unit 0x1d8bf0-0x1d9080 (GAME_TOC1, main_toc1), 13 functions, 13 live.
// Primary class: CKSrvFxParticlesAccessor  key 0x2c0c  category Logic  size 0x8  vtable 0xb1dea0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1d8bf0  RegisterCKSrvFxParticlesAccessorClass
//   [ ] 0x1d8c68  _GLOBAL__I_1d8c68
//   [x] 0x1d8c78  CKSrvFxParticlesAccessor_Load
//   [ ] 0x1d8d38  CKSrvFxParticlesAccessor_Save
//   [x] 0x1d8d60  CKSrvFxParticlesAccessor_Destroy  (in the header)
//   [x] 0x1d8d98  CKSrvFxParticlesAccessor_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x1d8de0  CKSrvFxParticlesAccessor_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1d8e10  CKSrvFxParticlesAccessor_BaseDestructor  (C++ destructor chain)
//   [x] 0x1d8e40  CKSrvFxParticlesAccessor_Construct
//   [x] 0x1d8e80  CKSrvFxParticlesAccessor_Construct_2  (the constructor)
//   [x] 0x1d8ec0  CKSrvFxParticlesAccessor_DeleteArray
//   [x] 0x1d8f60  CKSrvFxParticlesAccessor_Create
//   [x] 0x1d8fc0  CKSrvFxParticlesAccessor_CreateArray
//
//   [ ] 0x9adaf8  CKSrvFxParticlesAccessor_IsKindOfClass  [inline]
//   [x] 0x9adb20  CKSrvFxParticlesAccessor_GetClassType  [inline]
//   [x] 0x9adb28  CKSrvFxParticlesAccessor_GetClassID  [inline]
#include "k2000/logic/fx/CKSrvFxParticlesAccessor.h"

#include "k2000/io/IKFile.h"

// 0x001d8c78 CKSrvFxParticlesAccessor_Load
int32_t CKSrvFxParticlesAccessor::Load(IKFile* file, int32_t type) {
    KBase1DCC::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pParticles);
    return 1;
}
