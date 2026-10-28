// CKTriggerSynchro.cpp - reconstructed original translation unit 0x239b10-0x23a9a8 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CKTriggerSynchro  key 0x56cc  category Logic  size 0x14  vtable 0xb20b78
// Other owners: TriggerDomains (2), CKTriggerSynchroEntry (1), CKTriggerDomainSet (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x239b10  CKTriggerSynchro_Delete
//   [ ] 0x239b60  CKTriggerSynchro_RecursiveRegistration
//   [ ] 0x239bc0  CKTriggerSynchroEntry_FreeArray_maybe  [dead]
//   [ ] 0x239c18  RegisterCKTriggerSynchroClass
//   [ ] 0x239c90  _GLOBAL__I_239c90
//   [x] 0x239ca0  CKTriggerSynchro_DeleteArray
//   [x] 0x239d48  CKTriggerSynchro_Create
//   [x] 0x239d98  TriggerDomains_FindSetForSector_maybe
//   [ ] 0x239e00  TriggerDomains_FindSetForSector_2_maybe  [dead]
//   [x] 0x239e68  CKTriggerSynchro_CreateArray
//   [ ] 0x239f20  CKTriggerSynchro_PostLoad
//   [ ] 0x239f28  CKTriggerSynchro_Destroy
//   [x] 0x239ff0  CKTriggerSynchro_LoadEntry
//   [x] 0x23a210  CKTriggerSynchro_Load
//   [ ] 0x23a4c8  CKTriggerSynchro_SaveEntry
//   [ ] 0x23a620  CKTriggerSynchro_Save
//   [x] 0x23a770  CKTriggerDomainSet_SetEnabled_maybe
//
//   [ ] 0x9b99d8  CKTriggerSynchro_GetClassType  [inline]
//   [ ] 0x9b99e0  CKTriggerSynchro_GetClassID  [inline]
//   [ ] 0x9b99e8  CKTriggerSynchro_IsKindOfClass  [inline]
//   [ ] 0x9b9a08  CKTriggerSynchro_Destructor  [inline]
//   [ ] 0x9b9ae0  CKTriggerSynchro_DeletingDestructor  [inline]
#include "k2000/logic/CKTriggerSynchro.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKTriggerDomain.h"
#include "k2000/memory/Mem.h"

// Inlined in 0x00239d48 CKTriggerSynchro_Create: an empty entry vector with a capacity of 4.
CKTriggerSynchro::CKTriggerSynchro() {
    m_vEntries.m_pBlock = nullptr;
    m_vEntries.m_ui32NbElt = 4;
    m_vEntries.m_ui32NbUsedElt = 0;
}

// 0x00239ff0 CKTriggerSynchro_LoadEntry
void CKTriggerSynchro::Entry::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vRefs.m_ui32NbElt = 1;
        m_vRefs.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_vRefs.m_ui32NbElt = count;
        m_vRefs.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (m_vRefs.m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = (count & ~3u) + 4;
        if (capacity == 0) capacity = 4;
        m_vRefs.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vRefs.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vRefs.m_ui32NbElt = capacity;
    }
    m_vRefs.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, m_vRefs.m_pBlock, count);  // also for 0 (a Read of 0 bytes)
    ReadU32LE(file, &m_unk0c);
    m_unk10 = 0;
}

// 0x0023a210 CKTriggerSynchro_Load
int32_t CKTriggerSynchro::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vEntries.m_ui32NbElt = count;
    m_vEntries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Entry))));
    if (m_vEntries.m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = (count & ~3u) + 4;
        if (capacity == 0) capacity = 4;
        m_vEntries.m_pBlock = static_cast<Entry*>(
            Mem_ReallocAligned16(m_vEntries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Entry))));
        m_vEntries.m_ui32NbElt = capacity;
    }
    // The vector resize: new entries get an empty reference vector (capacity 4), dropped ones are freed.
    for (uint32_t i = m_vEntries.m_ui32NbUsedElt; i < count; ++i) {
        Entry& entry = m_vEntries.m_pBlock[i];
        entry.m_vRefs.m_ui32NbElt = 4;
        entry.m_vRefs.m_pBlock = nullptr;
        entry.m_vRefs.m_ui32NbUsedElt = 0;
    }
    for (uint32_t i = count; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        Entry& entry = m_vEntries.m_pBlock[i];
        if (entry.m_vRefs.m_pBlock != nullptr) Mem_FreeAligned16(entry.m_vRefs.m_pBlock);
        entry.m_vRefs.m_ui32NbUsedElt = 0;
        entry.m_vRefs.m_pBlock = nullptr;
    }
    m_vEntries.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) m_vEntries.m_pBlock[i].Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unk10);
    return 1;
}

// 0x00239d98 TriggerDomains_FindSetForSector_maybe
CKTriggerSynchro::Entry* CKTriggerSynchro::FindSetForSector(int32_t sector) {
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        if (static_cast<int32_t>(m_vEntries.m_pBlock[i].m_unk0c) == sector) return &m_vEntries.m_pBlock[i];
    }
    return nullptr;
}

// 0x0023a770 CKTriggerDomainSet_SetEnabled_maybe
void CKTriggerSynchro::Entry::SetEnabled(uint8_t enabled) {
    m_unk10 = enabled;
    for (uint32_t i = 0; i < m_vRefs.m_ui32NbUsedElt; ++i) {
        CKTriggerDomain* domain = static_cast<CKTriggerDomain*>(m_vRefs.m_pBlock[i]);
        domain->m_ba32Flags = enabled | (domain->m_ba32Flags & 0xfffffffeu);
        if (enabled != 0) {
            domain->EnableRecursive();
        } else {
            domain->DisableRecursive();
        }
    }
}
