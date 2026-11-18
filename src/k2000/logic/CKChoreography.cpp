// CKChoreography.cpp - reconstructed original translation unit 0x264590-0x264e18 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKChoreography  key 0x6cc  category Logic  size 0x18  vtable 0xb213a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x264590  CKChoreography_Delete
//   [x] 0x2645e0  CKChoreography_Destroy  (empty)
//   [x] 0x2645e8  CKChoreography_RecursiveRegistration
//   [ ] 0x264650  CKChoreography_Save
//   [ ] 0x264658  RegisterCKChoreographyClass
//   [ ] 0x2646d0  _GLOBAL__I_2646d0
//   [x] 0x2646e0  CKChoreography_DeleteArray
//   [x] 0x264788  CKChoreography_Create
//   [x] 0x2647d8  CKChoreography_Reset_maybe
//   [x] 0x264818  CKChoreography_Update_maybe
//   [x] 0x2649e8  CKChoreography_GetCurrentKey_maybe
//   [x] 0x264a20  CKChoreography_SwitchToKey_maybe
//   [x] 0x264b40  CKChoreography_CreateArray
//   [x] 0x264bf8  CKChoreography_Load
//
//   [x] 0x9bafc8  CKChoreography_GetClassType  [inline]
//   [x] 0x9bafd0  CKChoreography_GetClassID  [inline]
//   [ ] 0x9bafd8  CKChoreography_Destructor  [inline]
//   [ ] 0x9bb040  CKChoreography_IsKindOfClass  [inline]
//   [ ] 0x9bb060  CKChoreography_DeletingDestructor  [inline]
#include "k2000/logic/CKChoreography.h"

#include "Spyro2008/groups/CKChoreoKey.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/memory/Mem.h"
#include "k2000/system/IKTime.h"

// 0x00264bf8 CKChoreography_Load. Types 4..7 (the save restores) read nothing.
int32_t CKChoreography::Load(IKFile* file, int32_t type) {
    if (static_cast<uint32_t>(type) - 4u <= 3u) return 1;
    ReadF32LE(file, &m_fElapsedTime);
    ReadU8(file, &m_ui8CurrentKey);
    uint8_t count = 0;  // XXL2 m_ui8NbKey
    ReadU8(file, &count);
    // The block is replaced (the old one is not freed). Without keys the capacity is 1 and the count is
    // left alone; the reserve that follows never grows it.
    if (count == 0) {
        m_apChoreoKey.m_ui32NbElt = 1;
        m_apChoreoKey.m_pBlock = static_cast<CKChoreoKey**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CKChoreoKey*))));
    } else {
        m_apChoreoKey.m_ui32NbElt = count;
        m_apChoreoKey.m_pBlock = static_cast<CKChoreoKey**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CKChoreoKey*))));
        if (m_apChoreoKey.m_ui32NbElt < count) {
            uint32_t capacity = count + 1u;
            if (capacity == 0) capacity = 1;
            m_apChoreoKey.m_pBlock = static_cast<CKChoreoKey**>(Mem_ReallocAligned16(
                m_apChoreoKey.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CKChoreoKey*))));
            m_apChoreoKey.m_ui32NbElt = capacity;
        }
        m_apChoreoKey.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_apChoreoKey.m_pBlock[i]);
    return 1;
}

// 0x002647d8 CKChoreography_Reset_maybe (the squads' phases)
void CKChoreography::Reset() {
    m_fElapsedTime = 0.0f;
    m_ui8CurrentKey = 0;
    m_apChoreoKey.m_pBlock[0]->ClearSlotsTaken();  // 0x2650b0
}

// 0x00264818 CKChoreography_Update_maybe
uint8_t CKChoreography::Update(IKTime* clock) {
    const uint32_t previous = m_ui8CurrentKey;
    CKChoreoKey* key = m_apChoreoKey.m_pBlock[previous];
    const uint32_t count = m_apChoreoKey.m_ui32NbUsedElt;
    if (!(key->m_fKeyDuration >= 0.0f)) return 0;
    m_fElapsedTime = m_fElapsedTime + clock->m_afDeltaTime[0];
    if (!(m_fElapsedTime >= key->m_fKeyDuration)) return 0;
    m_fElapsedTime = m_fElapsedTime - key->m_fKeyDuration;
    if (count <= 1) return 1;
    m_ui8CurrentKey = static_cast<uint8_t>(previous + 1);
    if (m_ui8CurrentKey >= count) m_ui8CurrentKey = 0;
    m_apChoreoKey.m_pBlock[m_ui8CurrentKey]->ClearSlotsTaken();  // 0x2650b0
    const CKChoreoKey* old = m_apChoreoKey.m_pBlock[previous];
    for (uint32_t i = 0; old->m_asPos.m_ui32NbUsedElt > i; ++i) {
        CKChoreoKey* current = m_apChoreoKey.m_pBlock[m_ui8CurrentKey];
        if (current->m_asPos.m_ui32NbUsedElt > i) current->m_asPos.m_pBlock[i].m_bUsed = old->m_asPos.m_pBlock[i].m_bUsed;
    }
    return 1;
}

// 0x00264a20 CKChoreography_SwitchToKey_maybe: with more than one key, `key` becomes current (0 when out of range; the
// time is kept), its slots freed then given the previous key's taken flags (as Update).
void CKChoreography::SwitchToKey(uint8_t key) {
    const uint32_t count = m_apChoreoKey.m_ui32NbUsedElt;
    if (count <= 1) return;
    const uint32_t previous = m_ui8CurrentKey;
    m_ui8CurrentKey = key;
    if (key >= count) m_ui8CurrentKey = 0;
    m_apChoreoKey.m_pBlock[m_ui8CurrentKey]->ClearSlotsTaken();  // 0x2650b0
    const CKChoreoKey* old = m_apChoreoKey.m_pBlock[previous];
    for (uint32_t i = 0; old->m_asPos.m_ui32NbUsedElt > i; ++i) {
        CKChoreoKey* current = m_apChoreoKey.m_pBlock[m_ui8CurrentKey];
        if (current->m_asPos.m_ui32NbUsedElt > i) current->m_asPos.m_pBlock[i].m_bUsed = old->m_asPos.m_pBlock[i].m_bUsed;
    }
}

// 0x002645e8 CKChoreography_RecursiveRegistration (returns 1)
void CKChoreography::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) - 4u > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
