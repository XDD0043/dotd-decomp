// CKS08EnemyCpnt.cpp - reconstructed original translation unit 0x2b3bc8-0x2b85e8 (GAME_TOC1, main_toc1), 13 functions, 13 live.
// Primary class: CKS08EnemyCpnt  key 0x906  category Component  size 0x568  vtable 0xb22580
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b3bc8  CKS08EnemyCpnt_Delete
//   [ ] 0x2b3c18  CKS08EnemyCpnt_PostLoad
//   [ ] 0x2b3c20  CKS08EnemyCpnt_Save
//   [ ] 0x2b3c48  CKS08EnemyCpnt_RecursiveRegistration
//   [ ] 0x2b3c70  CKS08EnemyCpnt_Destroy
//   [x] 0x2b3c98  CKS08EnemyCpnt_DeleteArray
//   [x] 0x2b3d38  CKS08EnemyCpnt_Create
//   [ ] 0x2b3e18  RegisterCKS08EnemyCpntClass
//   [ ] 0x2b3ea0  _GLOBAL__D_2b3ea0
//   [ ] 0x2b3eb0  _GLOBAL__I_2b3eb0
//   [ ] 0x2b3ec0  CKS08EnemyCpnt_GetAttackAnimTableEntryPtr_maybe
//   [x] 0x2b3f00  CKS08EnemyCpnt_CreateArray
//   [x] 0x2b4060  CKS08EnemyCpnt_Load
//
//   [ ] 0x9bccf0  CKS08EnemyCpnt_IsKindOfClass  [inline]
//   [ ] 0x9bcd28  CKS08EnemyCpnt_GetClassType  [inline]
//   [ ] 0x9bcd30  CKS08EnemyCpnt_GetClassID  [inline]
//   [ ] 0x9bcd38  CKS08EnemyCpnt_DeletingDestructor  [inline]
//   [ ] 0x9bce68  CKS08EnemyCpnt_Destructor  [inline]
#include "Spyro2008/components/CKS08EnemyCpnt.h"

#include "k2000/groups/TVectorPush.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// 0x00a70424 (the TOC 0x17e8 table + 0x24): four bytes per enemy type (CKS08EnemyCpnt::m_unkb8), constant
// data. Byte 3 sizes the Load's byte vector +0x348; the run time reads the table too
// (CKS08EnemyCpnt_GetAttackAnimTableEntryPtr_maybe 0x2b3ec0).
const uint8_t kEnemyTypeTable[] = {
    0x01, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, 0x07, 0x07, 0x02, 0x01, 0x07, 0x07, 0x01,
    0x01, 0x07, 0x07, 0x02, 0x01, 0x0a, 0x0a, 0x03, 0x01, 0x0d, 0x0d, 0x02, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x06, 0x06, 0x02,
    // The data that follows the nine entries in the EBOOT (to 0xa70480), kept so that a larger type reads
    // what the PS3 reads (no bounds check in the original).
    0x21, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0d, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0d, 0x0a, 0x0b, 0x02, 0x03, 0x05, 0x04,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
}  // namespace

// 0x002b4060 CKS08EnemyCpnt_Load
int32_t CKS08EnemyCpnt::Load(IKFile* file, int32_t type) {
    CKEnemyCpnt::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_unkb8);
    ReadU32LE(file, &m_unkbc);
    ReadF32LE(file, &m_unkc0);
    ReadF32LE(file, &m_unkc4);
    ReadF32LE(file, &m_unkc8);
    ReadF32LE(file, &m_unkf8);
    ReadF32LE(file, &m_unkfc);
    ReadF32LE(file, &m_unkcc);
    ReadF32LE(file, &m_unkd0);
    ReadF32LE(file, &m_unkd4);
    ReadF32LE(file, &m_unke4);
    ReadF32LE(file, &m_unk118);
    // References: the count, then capacity = used = count (the original's "capacity < count" reserve never
    // runs; no special case for 0: a 0-byte block).
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vUnk11c.m_ui32NbElt = count;
    m_vUnk11c.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    m_vUnk11c.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vUnk11c.m_pBlock[i]);
    ReadF32LE(file, &m_unk188);
    ReadS32LE(file, &m_unk198);
    ReadS32LE(file, &m_unk19c);
    ReadS32LE(file, &m_unk1a0);
    ReadS32LE(file, &m_unk1a4);
    ReadF32LE(file, &m_unk1a8);
    ReadF32LE(file, &m_unk1ac);
    ReadF32LE(file, &m_unk1b0);
    ReadF32LE(file, &m_unk1b8);
    ReadF32LE(file, &m_unk1bc);
    ReadF32LE(file, &m_unk1c0);
    ReadRaw(file, &m_unke8, 1);
    ReadF32LE(file, &m_unk1d0);
    ReadF32LE(file, &m_unkdc);
    ReadF32LE(file, &m_unk1f0);
    ReadF32LE(file, &m_unk1d8);
    ReadF32LE(file, &m_unk1d4);
    ReadU32LE(file, &m_unk1f4);
    ReadRaw(file, &m_unk1f8, 1);
    ReadRaw(file, &m_unk1f9, 1);
    ReadF32LE(file, &m_unk1fc);
    ReadF32LE(file, &m_unk200);
    ReadF32LE(file, &m_unk204);
    m_unk21c = 0.0f;
    m_unk208 = 0.0f;
    m_unk20c = 0.0f;
    m_unk210 = 0.0f;
    m_unk214 = 0.0f;
    m_unk218 = 0.0f;
    ReadF32LE(file, &m_unk208);
    ReadF32LE(file, &m_unk20c);
    ReadF32LE(file, &m_unk210);
    ReadF32LE(file, &m_unk214);
    ReadF32LE(file, &m_unk218);
    ReadF32LE(file, &m_unk21c);
    ReadF32LE(file, &m_unk1b4);
    IKFile_ReadRef(file, &m_pUnk224);
    ReadF32LE(file, &m_unk23c);
    ReadF32LE(file, &m_unk230);
    ReadF32LE(file, &m_unk234);
    ReadF32LE(file, &m_unk228);
    ReadF32LE(file, &m_unk238);
    ReadF32LE(file, &m_unkd8);
    ReadF32LE(file, &m_unk240);
    ReadF32LE(file, &m_unk220);
    ReadF32LE(file, &m_unk1c4);
    ReadS32LE(file, &m_unk1c8);
    ReadF32LE(file, &m_unk190);
    ReadF32LE(file, &m_unk194);
    ReadF32LE(file, &m_unke0);
    ReadF32LE(file, &m_unk244);
    ReadF32LE(file, &m_unk26c);
    ReadF32LE(file, &m_unk270);
    ReadF32LE(file, &m_unk248);
    ReadF32LE(file, &m_unk24c);
    ReadF32LE(file, &m_unk250);
    ReadF32LE(file, &m_unk254);
    ReadF32LE(file, &m_unk258);
    ReadF32LE(file, &m_unk25c);
    ReadF32LE(file, &m_unk274);
    ReadF32LE(file, &m_unk278);
    ReadF32LE(file, &m_unk27c);
    ReadF32LE(file, &m_unk264);
    ReadF32LE(file, &m_unk268);
    ReadF32LE(file, &m_unk280);
    ReadF32LE(file, &m_unk284);
    ReadF32LE(file, &m_unk288);
    ReadF32LE(file, &m_unk290);
    ReadF32LE(file, &m_unk294);
    ReadF32LE(file, &m_unk298);
    ReadF32LE(file, &m_unk29c);
    ReadF32LE(file, &m_unk2a0);
    ReadF32LE(file, &m_unk2b0);
    ReadF32LE(file, &m_unk2b4);
    ReadF32LE(file, &m_unk2b8);
    ReadF32LE(file, &m_unk2cc);
    ReadF32LE(file, &m_unk2d0);
    ReadF32LE(file, &m_unk2d4);
    ReadF32LE(file, &m_unk2d8);
    ReadF32LE(file, &m_unk2dc);
    ReadF32LE(file, &m_unk2e0);
    ReadF32LE(file, &m_unk2a4);
    ReadF32LE(file, &m_unk2a8);
    ReadF32LE(file, &m_unk2e4);
    ReadF32LE(file, &m_unk2e8);
    ReadF32LE(file, &m_unk2ec);
    ReadF32LE(file, &m_unk2f0);
    ReadF32LE(file, &m_unk2f4);
    ReadF32LE(file, &m_unk300);
    ReadF32LE(file, &m_unk304);
    ReadF32LE(file, &m_unk308);
    ReadS32LE(file, &m_unk30c);
    ReadF32LE(file, &m_unk310);
    ReadF32LE(file, &m_unk2f8);
    ReadF32LE(file, &m_unk2fc);
    ReadF32LE(file, &m_unkec);
    ReadF32LE(file, &m_unk260);
    ReadF32LE(file, &m_unk318);
    ReadF32LE(file, &m_unk31c);
    IKFile_ReadRef(file, &m_pUnk32c);
    ReadF32LE(file, &m_unk314);
    ReadF32LE(file, &m_unk1e8);
    ReadF32LE(file, &m_unk334);
    ReadF32LE(file, &m_unk1ec);
    ReadRaw(file, &m_unk338, 1);
    ReadF32LE(file, &m_unk1e0);
    ReadF32LE(file, &m_unk1dc);
    ReadF32LE(file, &m_unk1e4);
    ReadS32LE(file, &m_unk33c);
    ReadS32LE(file, &m_unk340);
    ReadF32LE(file, &m_unk2bc);
    // References pushed at the end of m_vUnk128 (a one-element block first when it has none).
    {
        IKSerializable* ref = nullptr;
        uint32_t refCount = 0;
        ReadU32LE(file, &refCount);
        if (m_vUnk128.m_pBlock == nullptr) {
            m_vUnk128.m_ui32NbElt = 1;
            m_vUnk128.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
        }
        for (uint32_t i = 0; i < refCount; ++i) {
            IKFile_ReadRef(file, &ref);
            TVector_GrowIfFull(m_vUnk128);
            m_vUnk128.m_pBlock[m_vUnk128.m_ui32NbUsedElt++] = ref;
        }
    }
    ReadF32LE(file, &m_unk354);
    ReadF32LE(file, &m_unk358);
    ReadF32LE(file, &m_unk35c);
    ReadF32LE(file, &m_unk36c);
    // Exactly four bytes: a new block (the old one freed), capacity 5, used 4; missing bytes are 0, extra
    // bytes are read and dropped.
    {
        uint32_t byteCount = 0;
        ReadU32LE(file, &byteCount);
        if (m_vUnk370.m_pBlock != nullptr) {
            Mem_FreeAligned16(m_vUnk370.m_pBlock);
            m_vUnk370.m_pBlock = nullptr;
        }
        m_vUnk370.m_ui32NbElt = 1;
        m_vUnk370.m_ui32NbUsedElt = 0;
        m_vUnk370.m_pBlock = nullptr;
        m_vUnk370.m_pBlock = static_cast<uint8_t*>(Mem_AllocAligned16(1));
        if (m_vUnk370.m_ui32NbElt < 4) {
            m_vUnk370.m_pBlock = static_cast<uint8_t*>(Mem_ReallocAligned16(m_vUnk370.m_pBlock, 5));
            m_vUnk370.m_ui32NbElt = 5;
        }
        m_vUnk370.m_ui32NbUsedElt = 4;
        if (byteCount <= 4) {
            for (uint32_t i = 0; i < byteCount; ++i) ReadRaw(file, &m_vUnk370.m_pBlock[i], 1);
            for (uint32_t i = byteCount; i < 4; ++i) m_vUnk370.m_pBlock[i] = 0;
        } else {
            for (uint32_t i = 0; i < 4; ++i) ReadRaw(file, &m_vUnk370.m_pBlock[i], 1);
            for (uint32_t i = 4; i < byteCount; ++i) {
                uint8_t dropped = 0;
                ReadRaw(file, &dropped, 1);
            }
        }
    }
    ReadF32LE(file, &m_unkf0);
    IKFile_ReadRef(file, &m_pUnk344);
    // As many bytes as the enemy type's entry says (kEnemyTypeTable byte 3, by m_unkb8): missing bytes are 0,
    // extra bytes are read and dropped.
    {
        const uint32_t size = kEnemyTypeTable[static_cast<uint32_t>(m_unkb8) * 4 + 3];
        uint32_t byteCount = 0;
        ReadU32LE(file, &byteCount);
        if (m_vUnk348.m_pBlock == nullptr) {
            m_vUnk348.m_ui32NbElt = 1;
            m_vUnk348.m_pBlock = static_cast<uint8_t*>(Mem_AllocAligned16(1));
        }
        if (m_vUnk348.m_ui32NbElt < size) {
            m_vUnk348.m_pBlock = static_cast<uint8_t*>(Mem_ReallocAligned16(m_vUnk348.m_pBlock, size + 1));
            m_vUnk348.m_ui32NbElt = size + 1;
        }
        m_vUnk348.m_ui32NbUsedElt = size;
        if (size < byteCount) {
            for (uint32_t i = 0; i < size; ++i) ReadRaw(file, &m_vUnk348.m_pBlock[i], 1);
            for (uint32_t i = size; i < byteCount; ++i) {
                uint8_t dropped = 0;
                ReadRaw(file, &dropped, 1);
            }
        } else {
            for (uint32_t i = 0; i < byteCount; ++i) ReadRaw(file, &m_vUnk348.m_pBlock[i], 1);
            for (uint32_t i = byteCount; i < size; ++i) m_vUnk348.m_pBlock[i] = 0;
        }
    }
    ReadF32LE(file, &m_unk458);
    ReadF32LE(file, &m_unk45c);
    ReadF32LE(file, &m_unk460);
    ReadF32LE(file, &m_unk464);
    // Twelve words: missing ones are 0, extra ones are read (not swapped) and dropped.
    {
        uint32_t wordCount = 0;
        ReadU32LE(file, &wordCount);
        if (wordCount <= 12) {
            for (uint32_t i = 0; i < wordCount; ++i) ReadU32LE(file, &m_aUnk428[i]);
            for (uint32_t i = wordCount; i < 12; ++i) m_aUnk428[i] = 0;
        } else {
            for (uint32_t i = 0; i < 12; ++i) ReadU32LE(file, &m_aUnk428[i]);
            for (uint32_t i = 12; i < wordCount; ++i) {
                uint32_t dropped = 0;
                ReadRaw(file, &dropped, 4);
            }
        }
    }
    ReadF32LE(file, &m_unk468);
    ReadF32LE(file, &m_unk46c);
    ReadS32LE(file, &m_unk47c);
    ReadS32LE(file, &m_unk480);
    ReadF32LE(file, &m_unk484);
    ReadF32LE(file, &m_unk488);
    ReadF32LE(file, &m_unk320);
    ReadF32LE(file, &m_unk324);
    ReadF32LE(file, &m_unk328);
    ReadF32LE(file, &m_unk48c);
    ReadF32LE(file, &m_unk490);
    IKFile_ReadRef(file, &m_pUnk4b4);
    ReadF32LE(file, &m_unk4b8);
    ReadRaw(file, &m_unk28c, 1);
    ReadRaw(file, &m_unk4bc, 1);
    ReadF32LE(file, &m_unkf4);
    ReadF32LE(file, &m_unk4c0);
    ReadF32LE(file, &m_unk4c4);
    ReadF32LE(file, &m_unk4c8);
    ReadF32LE(file, &m_unk4cc);
    ReadF32LE(file, &m_unk4d4);
    ReadF32LE(file, &m_unk4d8);
    ReadS32LE(file, &m_unk4dc);
    ReadF32LE(file, &m_unk470);
    ReadRaw(file, &m_unk474, 1);
    ReadF32LE(file, &m_unk2c0);
    ReadF32LE(file, &m_unk2c4);
    ReadRaw(file, &m_unk4bd, 1);
    ReadF32LE(file, &m_unk494);
    ReadF32LE(file, &m_unk478);
    ReadF32LE(file, &m_unk4e0);
    ReadF32LE(file, &m_unk4d0);
    ReadF32LE(file, &m_unk1cc);
    ReadF32LE(file, &m_unk4e4);
    ReadU32LE(file, &m_unk4e8);
    ReadF32LE(file, &m_unk4ec);
    ReadF32LE(file, &m_unk360);
    ReadF32LE(file, &m_unk364);
    ReadF32LE(file, &m_unk4f4);
    ReadF32LE(file, &m_unk4f8);
    m_MoveCpnt37c.Load(file, K_LEVEL_PLATEFORMS);  // a direct call (bl 0x2bcc98)
    ReadF32LE(file, &m_unk4fc);
    ReadF32LE(file, &m_unk500);
    ReadF32LE(file, &m_unk504);
    ReadF32LE(file, &m_unk508);
    ReadF32LE(file, &m_unk50c);
    ReadF32LE(file, &m_unk510);
    ReadF32LE(file, &m_unk514);
    ReadF32LE(file, &m_unk518);
    ReadF32LE(file, &m_unk51c);
    ReadF32LE(file, &m_unk2c8);
    IKFile_ReadRef(file, &m_pUnk4f0);
    ReadF32LE(file, &m_unk520);
    ReadF32LE(file, &m_unk524);
    ReadF32LE(file, &m_unk528);
    ReadF32LE(file, &m_unk52c);
    ReadF32LE(file, &m_unk530);
    ReadF32LE(file, &m_unk538);
    ReadF32LE(file, &m_unk53c);
    ReadF32LE(file, &m_unk540);
    IKFile_ReadRef(file, &m_pUnk544);
    IKFile_ReadRef(file, &m_pUnk548);
    ReadF32LE(file, &m_unk54c);
    ReadF32LE(file, &m_unk550);
    ReadF32LE(file, &m_unk498);
    ReadF32LE(file, &m_unk368);
    ReadF32LE(file, &m_unk49c);
    ReadF32LE(file, &m_unk554);
    ReadF32LE(file, &m_unk4a0);
    ReadF32LE(file, &m_unk4a4);
    ReadF32LE(file, &m_unk4a8);
    ReadF32LE(file, &m_unk4b0);
    ReadF32LE(file, &m_unk2ac);
    ReadF32LE(file, &m_unk4ac);
    ReadF32LE(file, &m_unk534);
    ReadF32LE(file, &m_unk558);
    ReadF32LE(file, &m_unk55c);
    ReadF32LE(file, &m_unk560);
    ReadF32LE(file, &m_unk564);
    return 1;
}
