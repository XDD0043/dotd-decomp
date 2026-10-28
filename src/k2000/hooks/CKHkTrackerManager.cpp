// CKHkTrackerManager.cpp - reconstructed original translation unit 0x451658-0x455dc0 (GAME_TOC1, main_toc1), 68 functions, 38 live.
// Primary class: CKHkTrackerManager  key 0xf42  category Hook  size 0x108  vtable 0xb26f78
// Other owners: CKSandal (7)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x451658  CKHkTrackerManager_UnassignAllHeroes_maybe  [dead]
//   [ ] 0x4516b0  CKHkTrackerManager_ReleaseTrack_maybe  [dead]
//   [ ] 0x451718  CKHkTrackerManager_CopyEntryByte9ToByte8_maybe  [dead]
//   [ ] 0x451768  CKHkTrackerManager_GetEntryType_maybe  [dead]
//   [ ] 0x451790  CKHkTrackerManager_FreeBuffers_maybe
//   [ ] 0x4519d0  RegisterCKHkTrackerManagerClass
//   [ ] 0x451a48  _GLOBAL__I_451a48
//   [ ] 0x451a58  CKHkTrackerManager_GetInfo
//   [ ] 0x451aa8  CKHkTrackerManager_OnDeactivate
//   [ ] 0x451ad0  CKHkTrackerManager_Resume
//   [ ] 0x451af8  CKHkTrackerManager_Pause
//   [x] 0x451b20  CKHkTrackerManager_SetDefaultState
//   [ ] 0x451b68  CKHkTrackerManager_Restart
//   [ ] 0x451b90  CKHkTrackerManager_Stop
//   [x] 0x451bb8  CKHkTrackerManager_Start
//   [ ] 0x451be0  CKHkTrackerManager_PostLoad
//   [ ] 0x451c08  CKHkTrackerManager_Save
//   [ ] 0x451c30  CKHkTrackerManager_RecursiveRegistration
//   [ ] 0x451c58  CKHkTrackerManager_Destroy
//   [x] 0x451c80  CKHkTrackerManager_Construct  [dead]
//   [ ] 0x451df0  CKHkTrackerManager_Construct_2  [dead]
//   [x] 0x451f60  CKHkTrackerManager_DeleteArray
//   [ ] 0x452008  CKHkTrackerManager_BaseDestructor
//   [ ] 0x452280  CKHkTrackerManager_SetEntryFlagBit0_maybe  [dead]
//   [ ] 0x4522b8  CKHkTrackerManager_SetEntryFieldC_maybe  [dead]
//   [ ] 0x4522e0  CKHkTrackerManager_SetEntryFloat8_maybe  [dead]
//   [ ] 0x452308  CKHkTrackerManager_SetEntryField4_maybe  [dead]
//   [ ] 0x452330  CKHkTrackerManager_SetEntryType_maybe  [dead]
//   [ ] 0x452358  CKHkTrackerManager_IsEntryType5_maybe  [dead]
//   [ ] 0x4523a0  FUN_004523a0  [dead]
//   [ ] 0x452428  CKHkTrackerManager_GetEntryFieldC_maybe  [dead]
//   [ ] 0x452450  CKHkTrackerManager_GetEntryFloat8_maybe  [dead]
//   [ ] 0x452478  CKHkTrackerManager_GetEntryField4_maybe  [dead]
//   [ ] 0x4524a0  CKHkTrackerManager_SetEntryFlagBit4_maybe  [dead]
//   [ ] 0x452508  CKHkTrackerManager_SetEntryFlagBit3_maybe  [dead]
//   [ ] 0x452570  CKHkTrackerManager_SetEntryFlagBit2_maybe  [dead]
//   [ ] 0x4525b0  CKHkTrackerManager_SetEntryFlagBit1_maybe  [dead]
//   [ ] 0x4525f0  CKHkTrackerManager_GetEntryFlagBit0_maybe  [dead]
//   [ ] 0x452620  CKHkTrackerManager_GetEntryFlagBit4_maybe  [dead]
//   [ ] 0x452650  CKHkTrackerManager_GetEntryFlagBit3_maybe  [dead]
//   [ ] 0x452680  CKHkTrackerManager_GetEntryFlagBit2_maybe  [dead]
//   [ ] 0x4526b0  CKHkTrackerManager_GetEntryFlagBit1_maybe  [dead]
//   [ ] 0x4526e0  CKHkTrackerManager_vfC8
//   [ ] 0x452720  CKHkTrackerManager_FilterCandidatesByCameraFrustum_maybe
//   [ ] 0x452c40  CKHkTrackerManager_FilterCandidatesByDistance_maybe
//   [ ] 0x453068  FUN_00453068  [dead]
//   [ ] 0x4530d0  FUN_004530d0  [dead]
//   [ ] 0x453128  FUN_00453128  [dead]
//   [ ] 0x4531d0  FUN_004531d0  [dead]
//   [ ] 0x453278  CKHkTrackerManager_OnActivate
//   [ ] 0x453378  CKHkTrackerManager_MessageProc
//   [ ] 0x4536e0  CKHkTrackerManager_DeletingDestructor
//   [ ] 0x453968  CKHkTrackerManager_Destructor
//   [x] 0x453be0  CKHkTrackerManager_CreateArray
//   [x] 0x453dd8  CKHkTrackerManager_Create
//   [ ] 0x453f68  CKHkTrackerManager_ApplyTrackFilterByType_maybe
//   [ ] 0x454178  CKHkTrackerManager_PickTrackForHero_maybe
//   [ ] 0x4544b8  CKHkTrackerManager_AssignHeroToTrack_maybe
//   [ ] 0x454888  CKHkTrackerManager_Update
//   [x] 0x4552f0  CKHkTrackerManager_Load
//   [ ] 0x455b58  CKSandal_Delete
//   [ ] 0x455ba8  CKSandal_UpdateCollision
//   [ ] 0x455bb0  CKSandal_vf58
//   [ ] 0x455be8  CKSandal_vf60
//   [ ] 0x455c80  CKSandal_vf6C
//   [ ] 0x455cd0  CKSandal_vf7C
//   [ ] 0x455cd8  CKSandal_vf80
//   [ ] 0x455ce0  FUN_00455ce0  [dead]
//
//   [ ] 0x9c3dd8  CKHkTrackerManager_IsKindOfClass  [inline]
//   [ ] 0x9c3e30  CKHkTrackerManager_GetClassType  [inline]
//   [ ] 0x9c3e38  CKHkTrackerManager_GetClassID  [inline]
#include "k2000/hooks/CKHkTrackerManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {

// The TVector sizing the Load inlines: a count of 0 gives one allocated element and leaves the length
// alone; otherwise capacity = length = count (the grow branch after the allocation cannot run).
template <class T>
void LoadReserve(TVector<T, 1>& v, uint32_t count) {
    if (count == 0) {
        v.m_ui32NbElt = 1;
        v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
        return;
    }
    v.m_ui32NbElt = count;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    v.m_ui32NbUsedElt = count;
}

}  // namespace

// 0x004552f0 CKHkTrackerManager_Load. The three element loops run from the last element down.
int32_t CKHkTrackerManager::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_ui8NbRows);
    ReadU8(file, &m_ui8NbCols34);
    ReadU8(file, &m_ui8NbCols38);
    uint32_t n = static_cast<uint32_t>(m_ui8NbRows) * m_ui8NbCols34;
    m_apRefs34 = static_cast<IKSerializable**>(Mem_AllocAligned16(n * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apRefs34, n);
    n = static_cast<uint32_t>(m_ui8NbRows) * m_ui8NbCols38;
    m_apRefs38 = static_cast<IKSerializable**>(Mem_AllocAligned16(n * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apRefs38, n);
    for (Slot& slot : m_aSlots) {
        ReadU8(file, &slot.m_unkC);
        ReadU32LE(file, &slot.m_unk10);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        LoadReserve(slot.m_vRefValues, count);
        for (uint32_t i = count; i-- != 0;) {
            IKFile_ReadRef(file, &slot.m_vRefValues.m_pBlock[i].m_pRef);
            ReadU32LE(file, &slot.m_vRefValues.m_pBlock[i].m_unk4);
        }
        ReadU32LE(file, &count);
        LoadReserve(slot.m_vValuesRefs, count);
        for (uint32_t i = count; i-- != 0;) {
            ValuesRef& v = slot.m_vValuesRefs.m_pBlock[i];
            ReadU32LE(file, &v.m_unk0);
            ReadU32LE(file, &v.m_unk4);
            ReadU32LE(file, &v.m_unk8);
            IKFile_ReadRef(file, &v.m_pRef);
        }
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadReserve(m_vRefBytes, count);
    for (uint32_t i = count; i-- != 0;) {
        IKFile_ReadRef(file, &m_vRefBytes.m_pBlock[i].m_pRef);
        ReadU8(file, &m_vRefBytes.m_pBlock[i].m_unk9);
    }
    return 1;
}

// 0x00451b20 CKHkTrackerManager_SetDefaultState: bit 9 set.
void CKHkTrackerManager::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
}

// 0x00451bb8 CKHkTrackerManager_Start: CKHkActorBase_d82_maybe_ResetRuntime only.
void CKHkTrackerManager::Start() { CKHkActorBase::Start(); }
