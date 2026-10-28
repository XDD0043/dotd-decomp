// CKGolemAttackCommon.cpp - reconstructed original translation unit 0x4b7728-0x4ba5a0 (GAME_TOC1, main_toc1), 35 functions, 31 live.
// Primary class: CKGolemAttackCommon  key 0x994c  category Logic  size 0x98  vtable 0xb28fc0
// Other owners: IKSerializable (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4b7728  RegisterCKGolemAttackCommonClass
//   [ ] 0x4b77a0  _GLOBAL__I_4b77a0
//   [ ] 0x4b77b0  CKGolemAttackCommon_PlayRandomSlotSound_maybe
//   [ ] 0x4b7a38  CKGolemAttackCommon_ApplyPoseFromList58_maybe  [dead]
//   [ ] 0x4b7b10  KBaseC_vf88
//   [ ] 0x4b7b50  KBaseC_vf84
//   [ ] 0x4b7b88  KBaseC_vf8C_2
//   [ ] 0x4b7bc8  KBaseC_vf80_3
//   [ ] 0x4b7c08  CKGolemAttackCommon_QueueTriggerSignals_maybe  [dead]
//   [ ] 0x4b7c38  CKGolemAttackCommon_FireTimedTriggers_maybe  [dead]
//   [ ] 0x4b7d38  CKGolemAttackCommon_FireAnimMarkTriggers_maybe
//   [ ] 0x4b7fc8  CKGolemAttackCommon_Save
//   [ ] 0x4b7ff0  CKGolemAttackCommon_RecursiveRegistration
//   [ ] 0x4b8018  CKGolemAttackCommon_Construct_2
//   [x] 0x4b8088  CKGolemAttackCommon_DeleteArray
//   [ ] 0x4b8128  CKGolemAttackCommon_vf5C
//   [ ] 0x4b8230  KBaseC_vf9C_2
//   [ ] 0x4b8250  CKGolemAttackCommon_AttachVolumesToHotSpots_maybe
//   [ ] 0x4b8400  CKGolemAttackCommon_StartAttack_maybe
//   [x] 0x4b87b0  CKGolemAttackCommon_Construct
//   [ ] 0x4b8820  CKGolemAttackCommon_Destroy
//   [ ] 0x4b8908  CKGolemAttackCommon_StopAttack_maybe
//   [ ] 0x4b8a08  KStub_Return1_4b8a08
//   [ ] 0x4b8a10  CKGolemAttackCommon_ApplyPoseFromList5C_maybe  [dead]
//   [ ] 0x4b8ae8  CKGolemAttackCommon_Destructor
//   [ ] 0x4b8bc0  CKGolemAttackCommon_BaseDestructor
//   [ ] 0x4b8c98  CKGolemAttackCommon_DeletingDestructor
//   [ ] 0x4b8d80  CKGolemAttackCommon_PostLoad
//   [x] 0x4b8e90  CKGolemAttackCommon_CreateArray
//   [x] 0x4b8f88  CKGolemAttackCommon_Create
//   [ ] 0x4b9010  CKGolemAttackCommon_AdvanceStepsList58_maybe
//   [ ] 0x4b93a0  CKGolemAttackCommon_UpdateAnimAndAdvanceSteps_maybe
//   [ ] 0x4b9508  CKGolemAttackCommon_AdvanceStepsList5C_maybe
//   [ ] 0x4b9898  CKGolemAttackCommon_Update_maybe
//   [x] 0x4b9bb8  CKGolemAttackCommon_Load
//
//   [ ] 0x9c5580  CKGolemAttackCommon_IsKindOfClass  [inline]
//   [ ] 0x9c55b8  CKGolemAttackCommon_GetClassType  [inline]
//   [ ] 0x9c55c0  CKGolemAttackCommon_GetClassID  [inline]
#include "k2000/logic/CKGolemAttackCommon.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x004b87b0 CKGolemAttackCommon_Construct: KBase984C's constructor, then the stores in the original's order.
CKGolemAttackCommon::CKGolemAttackCommon() {
    m_apUnk08 = nullptr;
    m_unk08Capacity = 1;
    m_unk08Count = 0;
    m_unk14 = 0;
    m_unk6cCapacity = 1;
    m_unk6cCount = 0;
    m_apUnk6c = nullptr;
}

// 0x004b9bb8 CKGolemAttackCommon_Load: KBase984C's data, then, for K_LEVEL_PLATEFORMS only, a byte, a reference,
// two counted arrays of entries (each with its own reference in front), five byte+reference pairs and two
// more references.
int32_t CKGolemAttackCommon::Load(IKFile* file, int32_t type) {
    KBase984C::Load(file, type);
    if (type != 0) return 1;

    ReadU8(file, &m_unk64);
    IKFile_ReadRef(file, &m_unk60);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): a fresh one-entry block every Load; the old block is not freed and the count is kept.
    m_unk08Capacity = 1;
    m_apUnk08 = static_cast<Entry08**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry08*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry08* entry = new Entry08;
        IKFile_ReadRef(file, &entry->m_unk04);
        IKFile_ReadRef(file, &entry->m_unk00);
        ReadU8(file, &entry->m_unk0d);
        ReadU8(file, &entry->m_unk0c);
        ReadU8(file, &entry->m_unk09);
        ReadU8(file, &entry->m_unk08);
        ReadU8(file, &entry->m_unk0a);
        ReadU8(file, &entry->m_unk0b);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&entry->m_unk10), 3);
        if (m_unk08Capacity == m_unk08Count) {
            uint32_t capacity = m_unk08Count + 1;
            if (capacity == 0) capacity = 1;
            m_apUnk08 = static_cast<Entry08**>(
                Mem_ReallocAligned16(m_apUnk08, capacity * static_cast<uint32_t>(sizeof(Entry08*))));
            m_unk08Capacity = capacity;
        }
        m_apUnk08[m_unk08Count] = entry;
        m_unk08Count = m_unk08Count + 1;
    }

    IKFile_ReadRef(file, &m_unk68);
    count = 0;
    ReadU32LE(file, &count);
    // BUG(original): as above (a fresh block, the old one leaked, the count kept).
    m_unk6cCapacity = 1;
    m_apUnk6c = static_cast<Entry6C**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry6C*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry6C* entry = new Entry6C;
        ReadF32LE(file, &entry->m_unk00);
        ReadU32LE(file, &entry->m_unk0c);
        entry->m_unk04.Load(file, 0);
        if (m_unk6cCapacity == m_unk6cCount) {
            uint32_t capacity = m_unk6cCount + 1;
            if (capacity == 0) capacity = 1;
            m_apUnk6c = static_cast<Entry6C**>(
                Mem_ReallocAligned16(m_apUnk6c, capacity * static_cast<uint32_t>(sizeof(Entry6C*))));
            m_unk6cCapacity = capacity;
        }
        m_apUnk6c[m_unk6cCount] = entry;
        m_unk6cCount = m_unk6cCount + 1;
    }

    IKFile_ReadRef(file, &m_unk50);
    ReadU8(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk1c);
    ReadU8(file, &m_unk20);
    IKFile_ReadRef(file, &m_unk24);
    ReadU8(file, &m_unk28);
    IKFile_ReadRef(file, &m_unk2c);
    ReadU8(file, &m_unk30);
    IKFile_ReadRef(file, &m_unk34);
    ReadU8(file, &m_unk38);
    IKFile_ReadRef(file, &m_unk3c);
    IKFile_ReadRef(file, &m_unk54);
    return 1;
}
