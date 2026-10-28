// CKFlashFxData_2.cpp - reconstructed original translation unit 0x1bb408-0x1bc520 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CKFlashFxData  key 0x170c  category Logic  size 0x68  vtable 0xb1cd00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1bb408  CKFlashFxData_GetNodeClassKey
//   [ ] 0x1bb410  CKFlashFxData_GetInfo
//   [ ] 0x1bb418  CKFlashFxData_MessageProc
//   [ ] 0x1bb7d8  CKFlashFxData_Destroy
//   [x] 0x1bb820  CKFlashFxData_PostLoad
//   [ ] 0x1bb848  CKFlashFxData_RecursiveRegistration
//   [x] 0x1bb870  CKFlashFxData_Load
//   [ ] 0x1bbe80  CKFlashFxData_Save
//
//   [ ] 0x9ac198  CKFlashFxData_IsKindOfClass  [inline]
//   [x] 0x9ac1d0  CKFlashFxData_GetClassType  [inline]
//   [x] 0x9ac1d8  CKFlashFxData_GetClassID  [inline]
//   [ ] 0x9ac1e0  CKFlashFxData_DeletingDestructor  [inline]
//   [ ] 0x9ac238  CKFlashFxData_Destructor  [inline]
#include "k2000/logic/fx/CKFlashFxData.h"

// 0x001bb820 CKFlashFxData_PostLoad only calls IKFxData's (0x1d8338, returns 1): the inherited PostLoad.

#include <cstring>

#include "k2000/io/IKFile.h"

namespace {
// One Read of count words, then every word byte-swapped in place (an lwbrx/stw loop on the PS3). The
// file is little-endian: on a little-endian host the bytes stay as they are.
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    ReadRaw(file, dst, count * 4);
    uint8_t* p = static_cast<uint8_t*>(dst);
    for (uint32_t i = 0; i < count; ++i, p += 4) {
        const uint32_t v = static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
                           (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
        std::memcpy(p, &v, 4);
    }
}
}  // namespace

// 0x001bb870 CKFlashFxData_Load
int32_t CKFlashFxData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFxData::Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    ReadF32LE(file, &m_unk5c);
    ReadF32LE(file, &m_unk60);
    ReadF32LE(file, &m_unk64);
    ReadWordsLE(file, m_unk34, 2);  // the pairs: one 8-byte read each
    ReadWordsLE(file, m_unk3c, 2);
    ReadWordsLE(file, m_unk14, 2);
    ReadWordsLE(file, m_unk1c, 2);
    ReadWordsLE(file, m_unk44, 2);
    IKFile_ReadTextureRef(file, &m_pTexture, 1);
    ReadRaw(file, m_Color, 4);
    ReadU8(file, &m_unk13);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk30);
    ReadU32LE(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    ReadU8(file, &m_unk10);
    ReadU8(file, &m_unk11);
    ReadU8(file, &m_unk12);
    ReadWordsLE(file, m_unk24, 2);
    return 1;
}
