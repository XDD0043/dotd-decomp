// CKHedgeHopTrailFxData.cpp - reconstructed original translation unit: 0x1c06d0-0x1c0f90 (GAME_TOC1, main_toc1), 9 functions, 7 live.
// Primary class: CKHedgeHopTrailFxData  key 0x2d4c  category Logic  size 0x3c  vtable 0xb1cf20
// Other owners: CKHedgeHopTrailNodeFx (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c06d0  CKHedgeHopTrailFxData_GetNodeClassKey  (CKHedgeHopTrailFxData.h)
//   [ ] 0x1c06d8  FUN_001c06d8  [dead]
//   [x] 0x1c0738  CKHedgeHopTrailFxData_RecursiveRegistration  (IKFxData's: the default)
//   [x] 0x1c0760  CKHedgeHopTrailFxData_Destroy  (empty: CKHedgeHopTrailFxData.h)
//   [x] 0x1c0768  CKHedgeHopTrailFxData_Load
//   [ ] 0x1c0b68  CKHedgeHopTrailFxData_Save
//   [x] 0x1c0ee0  CKHedgeHopTrailNodeFx_Delete  (DOTD_DECLARE_FACTORIES in CKHedgeHopTrailNodeFx.h)
//   [x] 0x1c0f30  CKHedgeHopTrailNodeFx_PostLoad  (CKHedgeHopTrailNodeFx.h)
//   [ ] 0x1c0f38  FUN_001c0f38  [dead]
//
//   [x] 0x9ac568  CKHedgeHopTrailFxData_IsKindOfClass  [inline]  (CKHedgeHopTrailFxData.h)
//   [x] 0x9ac5a0  CKHedgeHopTrailFxData_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac5a8  CKHedgeHopTrailFxData_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac5b0  CKHedgeHopTrailFxData_Destructor  [inline]  (CKHedgeHopTrailFxData.h)
//   [x] 0x9ac5f0  CKHedgeHopTrailFxData_DeletingDestructor  [inline]  (CKHedgeHopTrailFxData.h)
#include "k2000/logic/fx/CKHedgeHopTrailFxData.h"

#include "k2000/io/IKFile.h"

// 0x001c0768 CKHedgeHopTrailFxData_Load: level files only: IKFxData's, four raw bytes, then twelve byte-swapped words in
// the file's order.
int32_t CKHedgeHopTrailFxData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFxData::Load(file, K_LEVEL_PLATEFORMS);
    ReadRaw(file, m_unk08, 4);
    ReadF32LE(file, &m_fExtendSpeed);
    ReadF32LE(file, &m_fLength);
    ReadF32LE(file, &m_fMinSpread);
    ReadF32LE(file, &m_fMaxSegment);
    ReadF32LE(file, &m_fSegmentDecay);
    ReadF32LE(file, &m_fFadeSpeed);
    ReadF32LE(file, &m_fMaxSpread);
    ReadF32LE(file, &m_fSpreadSpeed);
    ReadF32LE(file, &m_unk14);
    ReadF32LE(file, &m_unk34);
    ReadF32LE(file, &m_fSpreadGrowth);
    ReadF32LE(file, &m_fMinSegment);
    return 1;
}
