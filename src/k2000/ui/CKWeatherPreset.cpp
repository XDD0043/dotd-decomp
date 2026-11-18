// CKWeatherPreset.cpp - reconstructed original translation unit 0x5ae528-0x5aeb88 (GAME_TOC2, main_toc2), 17 functions, 15 live.
// Primary owner: CKWeatherPreset (not a registered class)
// Other owners: RegisterCKWeatherPresetClass (1), WeatherPreset (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5ae528  CKWeatherPreset_Destroy
//   [ ] 0x5ae578  CKWeatherPreset_Construct  [dead]
//   [ ] 0x5ae588  RegisterCKWeatherPresetClass
//   [ ] 0x5ae600  _GLOBAL__I_5ae600
//   [x] 0x5ae610  CKWeatherPreset_DestroyArray
//   [x] 0x5ae6b0  CKWeatherPreset_BaseDestructor  (implicit: the vtable, IKComponent's destructor)
//   [x] 0x5ae6e0  CKWeatherPreset_DeletingDestructor  (implicit, then delete)
//   [x] 0x5ae728  CKWeatherPreset_Destructor  (implicit: the vtable, IKComponent's destructor)
//   [x] 0x5ae758  WeatherPreset_CopyFrom_maybe  (CKWeatherPreset::CopyFrom)
//   [ ] 0x5ae7f0  CKWeatherPreset_Construct_2  [dead]
//   [ ] 0x5ae800  CKWeatherPreset_Save
//   [x] 0x5ae808  CKWeatherPreset_LevelReset  (returns 1, registers nothing: the default)
//   [x] 0x5ae810  CKWeatherPreset_PostLoad  (returns 1: the default)
//   [x] 0x5ae818  CKWeatherPreset_CreateArray
//   [x] 0x5ae8a8  CKWeatherPreset_Create
//   [x] 0x5ae8e0  CKWeatherPreset_ClearReferences  (empty: the default Destroy)
//   [x] 0x5ae8e8  CKWeatherPreset_Load
//
//   [x] 0x9cbf48  CKWeatherPreset_IsKindOf  [inline]
//   [x] 0x9cbf70  CKWeatherPreset_GetClassGroup  [inline]
//   [x] 0x9cbf78  CKWeatherPreset_GetClassId  [inline]
#include "k2000/ui/CKWeatherPreset.h"

#include <cstring>

#include "k2000/io/IKFile.h"

// 0x005ae8e8 CKWeatherPreset_Load
int32_t CKWeatherPreset::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk04), 8);  // one 32-byte read
    ReadU32LEWords(file, m_unk24, 3);                                // one 12-byte read
    ReadRaw(file, m_unk30, 8);
    ReadRaw(file, m_unk3c, 4);
    ReadRaw(file, m_unk38, 4);
    uint8_t value = 0;
    ReadU8(file, &value);  // read into a local, then stored
    m_unk48 = value;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk40), 2);  // one 8-byte read
    return 1;
}

// 0x005ae758 WeatherPreset_CopyFrom_maybe (word copies; +0x48 the byte).
void CKWeatherPreset::CopyFrom(const CKWeatherPreset* other) {
    m_unk48 = other->m_unk48;
    std::memcpy(m_unk3c, other->m_unk3c, sizeof m_unk3c);
    std::memcpy(m_unk38, other->m_unk38, sizeof m_unk38);
    for (int i = 0; i < 8; ++i) m_unk04[i] = other->m_unk04[i];
    for (int i = 0; i < 3; ++i) m_unk24[i] = other->m_unk24[i];
    std::memcpy(m_unk30, other->m_unk30, sizeof m_unk30);
}
