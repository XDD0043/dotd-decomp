// CKFlaggedPath.cpp - reconstructed original translation unit 0xc4048-0xc5140 (GAME_TOC1, main_toc1), 20 functions, 17 live.
// Primary class: CKFlaggedPath  key 0x5cc  category Logic  size 0x28  vtable 0xb17bd8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc4048  CKFlaggedPath_Delete
//   [ ] 0xc4098  CKFlaggedPath_RecursiveRegistration
//   [ ] 0xc40a0  CKFlaggedPath_Construct  [dead]
//   [ ] 0xc40c0  CKFlaggedPath_InterpolateAtDistance_maybe  [dead]
//   [ ] 0xc4200  CKFlaggedPath_Construct_2  [dead]
//   [ ] 0xc4220  RegisterCKFlaggedPathClass
//   [ ] 0xc4298  _GLOBAL__I_c4298
//   [x] 0xc42a8  CKFlaggedPath_DeleteArray
//   [ ] 0xc4350  CKFlaggedPath_GetSegmentValueAt_maybe
//   [x] 0xc43f8  CKFlaggedPath_CreateArray
//   [x] 0xc44b0  CKFlaggedPath_Create
//   [ ] 0xc4500  CKFlaggedPath_GetInfo
//   [ ] 0xc4508  CKFlaggedPath_MessageProc
//   [ ] 0xc4510  CKFlaggedPath_Save
//   [ ] 0xc4518  CKFlaggedPath_PostLoad
//   [ ] 0xc4520  CKFlaggedPath_Destroy
//   [x] 0xc4568  CKFlaggedPath_Load
//   [ ] 0xc4908  CKFlaggedPath_ComputeRollUpVector_maybe
//   [ ] 0xc4d88  CKFlaggedPath_SetDistanceAndGetPositionUp_maybe
//   [ ] 0xc4eb8  CKFlaggedPath_SetDistanceAndGetPosition
//
//   [ ] 0x9a1c60  CKFlaggedPath_GetClassType  [inline]
//   [ ] 0x9a1c68  CKFlaggedPath_GetClassID  [inline]
//   [ ] 0x9a1c70  CKFlaggedPath_IsKindOfClass  [inline]
//   [ ] 0x9a1c90  CKFlaggedPath_DeletingDestructor  [inline]
//   [ ] 0x9a1d10  CKFlaggedPath_Destructor  [inline]
//   [ ] 0x9a1d78  IKPath_IsKindOf  [inline]
#include "k2000/logic/ai/CKFlaggedPath.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// Inlined in 0x000c44b0 CKFlaggedPath_Create.
CKFlaggedPath::CKFlaggedPath() {
    m_vPairs.m_pBlock = nullptr;
    m_vPairs.m_ui32NbElt = 1;
    m_vPairs.m_ui32NbUsedElt = 0;
}

// 0x000c4568 CKFlaggedPath_Load
int32_t CKFlaggedPath::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pPath);
    ReadU32LE(file, &m_ui32NbOfBeacon);
    ReadF32LE(file, &m_fCursorPos);
    uint32_t n = m_ui32NbOfBeacon;
    if (n == 0) {
        m_aTriggerToCallList = nullptr;
        m_aBeaconList = nullptr;
    } else {
        // One block: the positions (a float each), then the starters.
        void* block = Mem_AllocAligned16(n * static_cast<uint32_t>(sizeof(float) + sizeof(CTriggerStarter)));
        n = m_ui32NbOfBeacon;
        m_aBeaconList = static_cast<float*>(block);
        m_aTriggerToCallList = reinterpret_cast<CTriggerStarter*>(m_aBeaconList + n);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aBeaconList), n);
        for (uint32_t i = 0; i < m_ui32NbOfBeacon; ++i) m_aTriggerToCallList[i].Load(file, K_LEVEL_PLATEFORMS);
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        // BUG(original): the used count is not set here (it keeps the constructor's 0).
        m_vPairs.m_ui32NbElt = 1;
        m_vPairs.m_pBlock = static_cast<Pair*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Pair))));
    } else {
        m_vPairs.m_ui32NbElt = count;
        m_vPairs.m_pBlock = static_cast<Pair*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Pair))));
        if (m_vPairs.m_ui32NbElt < count) {  // as in the original: cannot happen
            uint32_t capacity = count + 1;
            if (capacity == 0) capacity = 1;
            m_vPairs.m_pBlock = static_cast<Pair*>(
                Mem_ReallocAligned16(m_vPairs.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Pair))));
            m_vPairs.m_ui32NbElt = capacity;
        }
        m_vPairs.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) {
        ReadU32LE(file, &m_vPairs.m_pBlock[i].m_unk0);
        ReadU32LE(file, &m_vPairs.m_pBlock[i].m_unk4);
    }
    return 1;
}
