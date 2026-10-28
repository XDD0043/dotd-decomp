// CKSparkFxData.cpp - reconstructed original translation unit 0x1d3908-0x1d3e68 (GAME_TOC1, main_toc1), 11 functions, 9 live.
// Primary owner: CKSparkFxData (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d3908  CKSparkFxData_ConstructBase_maybe
//   [x] 0x1d3930  CKSparkFxData_GetNodeClassKey
//   [ ] 0x1d3938  KStub_Nop_1d3938  [dead]
//   [ ] 0x1d3940  CKSparkFxData_PostLoad
//   [x] 0x1d39c8  CKSparkFxData_Load
//   [ ] 0x1d3a88  CKSparkFxData_Save
//   [ ] 0x1d3ab0  CKSparkFxData_LevelReset
//   [ ] 0x1d3ad8  CKSparkFxData_ConstructBase_2_maybe  [dead]
//   [ ] 0x1d3b00  CKSparkFxData_HandleMessage
//   [ ] 0x1d3e18  CKSparkFxData_vf40
//   [ ] 0x1d3e20  CKSparkFxData_ClearReferences
//
//   [ ] 0x9ad310  CKSparkFxData_IsKindOf  [inline]
//   [x] 0x9ad348  CKSparkFxData_GetClassGroup  [inline]
//   [x] 0x9ad350  CKSparkFxData_GetClassId  [inline]
//   [ ] 0x9ad358  CKSparkFxData_DeletingDestructor  [inline]
//   [ ] 0x9ad3b0  CKSparkFxData_Destructor  [inline]
#include "k2000/fx/CKSparkFxData.h"

#include "k2000/io/IKFile.h"

// 0x001d3908 CKSparkFxData_ConstructBase_maybe, in its store order.
CKSparkFxData::CKSparkFxData() {
    m_unk14 = nullptr;
    m_pSparkParam = nullptr;
    m_unk0c = 0;
    m_unk10 = 0;
}

// 0x001d39c8 CKSparkFxData_Load
int32_t CKSparkFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pSparkParam);
    return 1;
}
