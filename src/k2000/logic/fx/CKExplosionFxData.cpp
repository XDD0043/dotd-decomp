// CKExplosionFxData.cpp - reconstructed original translation unit 0x1b3510-0x1b5d98 (GAME_TOC1, main_toc1), 17 functions, 11 live.
// Primary class: CKExplosionFxData  key 0x1a8c  category Logic  size 0x3c  vtable 0xb1c988
// Other owners: Vt (3), CKExplosionNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1b3510  CKExplosionFxData_CreateElementByType_maybe
//   [ ] 0x1b36f0  CKExplosionFxData_PostLoad
//   [ ] 0x1b37a0  CKExplosionFxData_RecursiveRegistration
//   [ ] 0x1b3920  FUN_001b3920  [dead]
//   [ ] 0x1b3990  CKExplosionFxData_GetInfo
//   [ ] 0x1b3998  Vt_b1c970_DeletingDestructor_maybe
//   [ ] 0x1b39c8  Vt_b1c970_Destructor_maybe
//   [ ] 0x1b39d8  Vt_b1c970_Destructor_2_maybe  [dead]
//   [ ] 0x1b39e8  CKExplosionFxData_Destroy
//   [ ] 0x1b3b20  CKExplosionFxData_ReleaseAndDestroyAllEntries_maybe  [dead]
//   [ ] 0x1b3c78  CKExplosionFxData_MessageProc
//   [x] 0x1b4328  CKExplosionFxData_Load
//   [ ] 0x1b4ea8  CKExplosionFxData_Save
//   [ ] 0x1b5ca8  CKExplosionNodeFx_Delete
//   [ ] 0x1b5cf8  FUN_001b5cf8  [dead]
//   [ ] 0x1b5d18  FUN_001b5d18  [dead]
//   [ ] 0x1b5d88  FUN_001b5d88  [dead]
//
//   [ ] 0x9aba20  CKExplosionFxData_IsKindOfClass  [inline]
//   [x] 0x9aba58  CKExplosionFxData_GetClassType  [inline]
//   [x] 0x9aba60  CKExplosionFxData_GetClassID  [inline]
//   [ ] 0x9abad8  CKExplosionFxData_DeletingDestructor  [inline]
//   [ ] 0x9abba0  CKExplosionFxData_Destructor  [inline]
#include "k2000/logic/fx/CKExplosionFxData.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

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

// CVector3 globals the type-1 part copies (initialised at run time; these are their live values):
// 0xc50d40 and 0xc50d64. XXL2 has no such named constants.
const CVector3 kVector3_c50d40 = {0.0f, 1.0f, 0.0f};
const CVector3 kVector3_c50d64 = {0.0f, 0.0f, 0.0f};
}  // namespace

// 0x001ae948 CKExplosionFxData_Create, the inlined constructor: the part list only.
CKExplosionFxData::CKExplosionFxData() {
    m_parts.m_pBlock = nullptr;
    m_parts.m_ui32NbElt = 10;
    m_parts.m_ui32NbUsedElt = 0;
}

// The type-0 part as CreatePart builds it, in the original's store order.
CKExplosionFxData::PartType0::PartType0() {
    m_unk14.x = 1.0f;
    m_unk2c.x = 0.0f;
    m_unk38.x = 0.0f;
    m_unk20.x = 0.0f;
    m_unk10 = 0;
    m_type = 0;
    m_unk0c = 0;
    m_unk44 = 5.0f;
    m_unk08 = 0.0f;
    m_unk48 = 1.0f;
    m_unk4c = 1.0f;
    m_unk50 = 1.0f;
    m_unk5c = 1.0f;
    m_unk60 = 1.0f;
    m_unk54 = 0.0f;
    m_unk58 = 0.0f;
    m_unk64 = 0.0f;
    m_unk68 = 0.0f;
    m_unk14.z = 1.0f;
    m_unk14.y = 1.0f;
    m_unk2c.z = 0.0f;
    m_unk2c.y = 0.0f;
    m_unk38.z = 0.0f;
    m_unk38.y = 0.0f;
    m_unk20.z = 0.0f;
    m_unk20.y = 0.0f;
    m_unk6c = 0x1ff;
}

// The type-1 part as CreatePart builds it, in the original's store order.
CKExplosionFxData::PartType1::PartType1() {
    m_unk14 = 5.0f;
    m_type = 1;
    m_unk08 = 0.0f;  // an integer 0 store
    m_unk18 = 1.0f;
    m_pObject = nullptr;
    m_unk1c = kVector3_c50d40;
    m_unk28 = kVector3_c50d64;
    m_unk10 = 0;
    m_unk34 = kVector3_c50d64;
}

// A part of types 2..8 as CreatePart builds it.
CKExplosionFxData::PartObject::PartObject(uint32_t type) {
    m_unk08 = 0.0f;  // an integer 0 store
    m_pObject = nullptr;
    m_type = type;
}

// 0x001b3510 CKExplosionFxData_CreateElementByType_maybe: OperatorNew(0x70 / 0x40 / 0x10).
CKExplosionFxData::Part* CKExplosionFxData::CreatePart(uint32_t type) {
    if (type == 1) return new PartType1();
    if (type < 1) return new PartType0();
    if (type > 8) return nullptr;
    return new PartObject(type);
}

// 0x001b4328 CKExplosionFxData_Load
int32_t CKExplosionFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    IKFile_ReadRef(file, &m_pSoundDico);
    IKFile_ReadRef(file, &m_pVibrationPadData);
    ReadU8(file, &m_unk18);
    ReadRaw(file, m_unk38, 4);
    IKFile_ReadRef(file, &m_pQuakeLauncher);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return 1;
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    m_parts.m_ui32NbElt = count;
    m_parts.m_pBlock = static_cast<Part**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Part*))));
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t partType = 0;
        ReadU32LE(file, &partType);
        Part* created = CreatePart(partType);
        if (m_parts.m_ui32NbElt == m_parts.m_ui32NbUsedElt) {  // full: grow by 10
            uint32_t capacity = m_parts.m_ui32NbUsedElt + 10;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Part*));
            if (capacity == 0) {
                capacity = 10;
                bytes = 10 * static_cast<uint32_t>(sizeof(Part*));
            }
            m_parts.m_pBlock = static_cast<Part**>(Mem_ReallocAligned16(m_parts.m_pBlock, bytes));
            m_parts.m_ui32NbElt = capacity;
        }
        m_parts.m_pBlock[m_parts.m_ui32NbUsedElt] = created;
        ++m_parts.m_ui32NbUsedElt;
        // The part is read back by the loop index, not by its push position.
        // BUG(original): a type above 8 creates no part, and the next line reads the null part's type.
        Part* part = m_parts.m_pBlock[i];
        const uint32_t kind = part->m_type;
        if (kind == 1) {
            PartType1* p = static_cast<PartType1*>(part);
            IKFile_ReadRef(file, &p->m_pObject);
            ReadU32LE(file, &p->m_unk10);
            ReadF32LE(file, &p->m_unk14);
            ReadF32LE(file, &p->m_unk18);
            ReadWordsLE(file, &p->m_unk1c, 3);
            ReadWordsLE(file, &p->m_unk28, 3);
            ReadWordsLE(file, &p->m_unk34, 3);
        } else if (kind == 0) {
            PartType0* p = static_cast<PartType0*>(part);
            ReadF32LE(file, &p->m_unk44);
            ReadF32LE(file, &p->m_unk48);
            ReadF32LE(file, &p->m_unk4c);
            ReadF32LE(file, &p->m_unk50);
            ReadF32LE(file, &p->m_unk5c);
            ReadF32LE(file, &p->m_unk60);
            ReadU32LE(file, &p->m_unk0c);
            ReadU32LE(file, &p->m_unk10);
            ReadWordsLE(file, &p->m_unk14, 3);
            ReadWordsLE(file, &p->m_unk2c, 3);
            ReadWordsLE(file, &p->m_unk38, 3);
            ReadWordsLE(file, &p->m_unk20, 3);
            ReadF32LE(file, &p->m_unk54);
            ReadF32LE(file, &p->m_unk58);
            ReadF32LE(file, &p->m_unk64);
            ReadF32LE(file, &p->m_unk68);
        } else if (kind <= 8) {
            IKFile_ReadRef(file, &static_cast<PartObject*>(part)->m_pObject);
        }
        ReadF32LE(file, &part->m_unk08);
    }
    return 1;
}
