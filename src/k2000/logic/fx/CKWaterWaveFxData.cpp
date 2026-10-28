// CKWaterWaveFxData.cpp - reconstructed original translation unit 0x5710f0-0x571348 (GAME_TOC2, main_toc2), 8 functions, 8 live.
// Primary class: CKWaterWaveFxData  key 0x3b8c  category Logic  size ?  vtable 0xb2dcb0
// Other owners: CKBlurFxData (1), BlurCurve (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5710f0  CKWaterWaveFxData_GetNodeClassKey
//   [ ] 0x5710f8  CKWaterWaveFxData_Destroy
//   [ ] 0x571100  CKWaterWaveFxData_EvaluateCurve_maybe
//   [ ] 0x571140  CKWaterWaveFxData_Save
//   [ ] 0x571168  CKWaterWaveFxData_RecursiveRegistration
//   [x] 0x571190  CKWaterWaveFxData_Load
//   [x] 0x5712a0  CKBlurFxData_GetNodeClassKey
//   [ ] 0x5712a8  BlurCurve_EvaluateLinear_maybe
//
//   [ ] 0x9cab48  CKWaterWaveFxData_IsKindOfClass  [inline]
//   [x] 0x9cab80  CKWaterWaveFxData_GetClassType  [inline]
//   [x] 0x9cab88  CKWaterWaveFxData_GetClassID  [inline]
//   [ ] 0x9cab90  CKWaterWaveFxData_Destructor  [inline]
//   [ ] 0x9cabd0  CKWaterWaveFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKWaterWaveFxData.h"

#include "k2000/io/IKFile.h"

// 0x00571190 CKWaterWaveFxData_Load
int32_t CKWaterWaveFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk08);
        ReadF32LE(file, &m_unk0c);
    }
    m_unk10 = -m_unk08 / m_unk0c;  // fneg, fdivs
    return 1;
}
