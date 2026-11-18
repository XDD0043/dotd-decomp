// Reconstructed original translation unit: 0x5721e0-0x572e48 (GAME_TOC2, main_toc2), 18 functions, 15 live.
// Primary class: CKTrailShockWaveFxData  key 0x448c  category Logic  size ?  vtable 0xb2de28
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5721e0  CKTrailShockWaveFxData_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x572230  CKTrailShockWaveFxData_Construct  [dead]
//   [ ] 0x572248  CKTrailShockWaveFxData_Construct_2  [dead]
//   [x] 0x572260  CKTrailShockWaveFxData_Destroy  (empty)
//   [ ] 0x572268  FUN_00572268  [dead]
//   [x] 0x572278  CKTrailShockWaveFxData_GetNodeClassKey
//   [ ] 0x572280  RegisterCKTrailShockWaveFxDataClass
//   [ ] 0x5722f8  _GLOBAL__I_5722f8
//   [x] 0x572308  CKTrailShockWaveFxData_PostLoad  (IKFxData's)
//   [x] 0x572330  CKTrailShockWaveFxData_RecursiveRegistration  (IKFxData's, nothing)
//   [x] 0x572358  CKTrailShockWaveFxData_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x5723b0  CKTrailShockWaveFxData_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x572458  CKTrailShockWaveFxData_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x572500  CKTrailShockWaveFxData_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x572548  CKTrailShockWaveFxData_Destructor  (C++ destructor)
//   [x] 0x572588  CKTrailShockWaveFxData_BaseDestructor  (C++ destructor chain)
//   [x] 0x5725c8  CKTrailShockWaveFxData_Load
//   [ ] 0x572a10  CKTrailShockWaveFxData_Save
//
//   [x] 0x9cadc8  CKTrailShockWaveFxData_IsKindOfClass  [inline]
//   [x] 0x9cae00  CKTrailShockWaveFxData_GetClassType  [inline]
//   [x] 0x9cae08  CKTrailShockWaveFxData_GetClassID  [inline]
#include "k2000/logic/fx/CKTrailShockWaveFxData.h"

#include "k2000/io/IKFile.h"

// 0x005725c8 CKTrailShockWaveFxData_Load: IKFxData's, then (level files) the 60 range words, one at a time, and the four
// words of +0xf8. +0x108..+0x10e are not read (the fresh heap leaves them 0).
int32_t CKTrailShockWaveFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 10; ++k) ReadF32LE(file, &m_afParticleRanges[i][j][k]);
    ReadF32LE(file, &m_fSpacing);
    ReadF32LE(file, &m_unkFC);
    ReadF32LE(file, &m_unk100);
    ReadF32LE(file, &m_unk104);
    return 1;
}
