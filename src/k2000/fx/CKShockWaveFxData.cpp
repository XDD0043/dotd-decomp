// CKShockWaveFxData.cpp - reconstructed original translation unit 0x1d1288-0x1d22e8 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary owner: CKShockWaveFxData (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1d1288  CKShockWaveFxData_ConstructBase_2_maybe  [dead]
//   [x] 0x1d12b0  CKShockWaveFxData_GetNodeClassKey
//   [ ] 0x1d12b8  CKShockWaveFxData_EvalRadiusScale_maybe
//   [ ] 0x1d1388  CKShockWaveFxData_EvalHeightScale_maybe
//   [ ] 0x1d1458  CKShockWaveFxData_EvalAlpha_maybe
//   [ ] 0x1d1500  CKShockWaveFxData_PostLoad
//   [ ] 0x1d1548  CKShockWaveFxData_LevelReset
//   [ ] 0x1d1570  CKShockWaveFxData_DeletingDestructor
//   [x] 0x1d15c8  CKShockWaveFxData_ConstructBase_maybe
//   [ ] 0x1d15f0  CKShockWaveFxData_vf40
//   [ ] 0x1d15f8  CKShockWaveFxData_HandleMessage
//   [ ] 0x1d1950  CKShockWaveFxData_ClearReferences
//   [ ] 0x1d19e8  CKShockWaveFxData_Destructor
//   [ ] 0x1d1a28  CKShockWaveFxData_BaseDestructor
//   [x] 0x1d1a68  CKShockWaveFxData_Load
//   [ ] 0x1d1ef0  CKShockWaveFxData_Save
//
//   [ ] 0x9ad1d8  CKShockWaveFxData_IsKindOf  [inline]
//   [x] 0x9ad210  CKShockWaveFxData_GetClassGroup  [inline]
//   [x] 0x9ad218  CKShockWaveFxData_GetClassId  [inline]
#include "k2000/fx/CKShockWaveFxData.h"

#include "k2000/io/IKFile.h"

namespace {
// A count, then new[] of count keys read in one block and byte-swapped word by word.
CKShockWaveFxData::Key* ReadKeys(IKFile* file, uint32_t count) {
    CKShockWaveFxData::Key* keys = new CKShockWaveFxData::Key[count];
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(keys), count * 2);
    return keys;
}
}  // namespace

// 0x001d15c8 CKShockWaveFxData_ConstructBase_maybe, in its store order.
CKShockWaveFxData::CKShockWaveFxData() {
    m_unk3c = 0;
    m_unk24 = nullptr;
    m_unk1c = nullptr;
    m_unk14 = nullptr;
}

// 0x001d1a68 CKShockWaveFxData_Load
int32_t CKShockWaveFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk18);
    m_unk1c = ReadKeys(file, m_unk18);
    ReadU32LE(file, &m_unk10);
    m_unk14 = ReadKeys(file, m_unk10);
    ReadU32LE(file, &m_unk20);
    m_unk24 = ReadKeys(file, m_unk20);
    ReadU8(file, &m_unk30);
    ReadF32LE(file, &m_unk34);
    ReadF32LE(file, &m_unk38);
    ReadRaw(file, m_unk40, 4);
    return 1;
}
