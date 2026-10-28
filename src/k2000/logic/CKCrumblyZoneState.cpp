// CKCrumblyZoneState.cpp - reconstructed original translation unit 0x403720-0x405608 (GAME_TOC1, main_toc1), 38 functions, 22 live.
// Primary class: CKCrumblyZoneState  key 0xa40c  category Logic  size 0x4c  vtable 0xb25758
// Other owners: CrumblyZoneState (7), CKSrvBonus (1), CKHkCrumblyZoneMultiState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x403720  CKCrumblyZoneState_Delete
//   [x] 0x403770  CKCrumblyZoneState_Construct  [dead]
//   [ ] 0x403798  FUN_00403798  [dead]
//   [ ] 0x4037d0  CKCrumblyZoneState_GetFlagBit0_maybe  [dead]
//   [ ] 0x4037e0  CKCrumblyZoneState_GetFlagBit4_maybe  [dead]
//   [ ] 0x4037f0  CKCrumblyZoneState_GetFlagBit6_maybe  [dead]
//   [ ] 0x403800  CrumblyZoneState_ClearContactList_maybe  [dead]
//   [ ] 0x403840  CKCrumblyZoneState_Construct_2  [dead]
//   [ ] 0x403868  RegisterCKCrumblyZoneStateClass
//   [ ] 0x4038e0  _GLOBAL__I_4038e0
//   [x] 0x4038f0  CKCrumblyZoneState_SetVolumesDamage_maybe
//   [ ] 0x403918  CKSrvBonus_SpawnBonusesArgSwap_ViaEngine_maybe  [dead]
//   [ ] 0x403948  CKCrumblyZoneState_ShrinkBoxAndSetNavBlocked_maybe  [dead]
//   [ ] 0x403a00  CrumblyZoneState_ComputeCenter_maybe
//   [x] 0x403b10  CKCrumblyZoneState_DeleteArray
//   [ ] 0x403bb0  CKCrumblyZoneState_GetFlagBit2_maybe  [dead]
//   [ ] 0x403bc0  CKCrumblyZoneState_GetFlagBit3_maybe  [dead]
//   [ ] 0x403bd0  CKCrumblyZoneState_GetFlagBit1_maybe  [dead]
//   [ ] 0x403be0  CKCrumblyZoneState_GetFlagBit9_maybe
//   [ ] 0x403bf0  CKCrumblyZoneState_GetFlagBit8_maybe  [dead]
//   [ ] 0x403c00  CKCrumblyZoneState_GetFlagBit7_maybe  [dead]
//   [ ] 0x403c10  CKCrumblyZoneState_GetFlagBit5_maybe  [dead]
//   [ ] 0x403c20  CrumblyZoneState_CopyContactList_maybe
//   [x] 0x403d38  CKCrumblyZoneState_CreateArray
//   [x] 0x403de8  CKCrumblyZoneState_Create
//   [ ] 0x403e40  CKCrumblyZoneState_Save
//   [ ] 0x403e48  CKCrumblyZoneState_RecursiveRegistration
//   [ ] 0x403e50  CKCrumblyZoneState_PostLoad
//   [ ] 0x403ec8  CKHkCrumblyZoneMultiState_UpdateState_maybe
//   [ ] 0x403ff8  CKCrumblyZoneState_Destroy
//   [ ] 0x404050  CrumblyZoneState_SetEnabled_maybe
//   [ ] 0x404378  CrumblyZoneState_UpdateNavBlocking_maybe
//   [ ] 0x4047d0  CrumblyZoneState_ApplyDamage_maybe
//   [ ] 0x404bc0  CrumblyZoneState_OnContact_maybe
//   [x] 0x404d98  CKCrumblyZoneState_Load
//   [ ] 0x405400  CKCrumblyZoneState_DeletingDestructor
//   [ ] 0x4054b8  CKCrumblyZoneState_Destructor
//   [ ] 0x405560  CKCrumblyZoneState_Destructor_2  [dead]
//
//   [ ] 0x9c1140  CKCrumblyZoneState_GetClassType  [inline]
//   [ ] 0x9c1148  CKCrumblyZoneState_GetClassID  [inline]
//   [ ] 0x9c1150  CKCrumblyZoneState_IsKindOfClass  [inline]
#include "k2000/logic/CKCrumblyZoneState.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/components/CKBoundingCpnt.h"

// 0x00403770 CKCrumblyZoneState_Construct
CKCrumblyZoneState::CKCrumblyZoneState() {
    m_vEntries.m_pBlock = nullptr;
    m_vEntries.m_ui32NbElt = 1;
    m_vEntries.m_ui32NbUsedElt = 0;
    m_unk24 = 0;
}

// 0x00404d98 CKCrumblyZoneState_Load
int32_t CKCrumblyZoneState::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pZone);
    IKFile_ReadRef(file, &m_pGroundCpnt);
    IKFile_ReadRef(file, &m_pBoundingCpnt);
    ReadF32LE(file, &m_unk0c);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry))));
    } else {
        m_vEntries.m_ui32NbElt = count;
        m_vEntries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Entry))));
    }
    if (m_vEntries.m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vEntries.m_pBlock = static_cast<Entry*>(
            Mem_ReallocAligned16(m_vEntries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Entry))));
        m_vEntries.m_ui32NbElt = capacity;
    }
    m_vEntries.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Entry& entry = m_vEntries.m_pBlock[i];
        ReadU8(file, &entry.m_unk00);
        ReadU8(file, &entry.m_unk01);
        ReadU8(file, &entry.m_unk02);
        ReadU32LE(file, &entry.m_unk04);
        ReadU32LEWords(file, entry.m_unk08, 3);
    }
    IKFile_ReadRef(file, &m_pSound);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk30);
    ReadU32LE(file, &m_unk38);
    IKFile_ReadRef(file, &m_pBonusData);
    ReadF32LE(file, &m_unk40);
    ReadS32LE(file, &m_unk44);
    ReadS32LE(file, &m_unk48);
    return 1;
}

// 0x004038f0 CKCrumblyZoneState_SetVolumesDamage_maybe
void CKCrumblyZoneState::SetVolumesDamage(IKSerializable* damage) {
    static_cast<CKBoundingCpnt*>(m_pBoundingCpnt)->SetVolumesDamage(damage);
}
