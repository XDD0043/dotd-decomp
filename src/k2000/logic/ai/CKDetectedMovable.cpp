// CKDetectedMovable.cpp - reconstructed original translation unit 0x1aa998-0x1ab2b0 (GAME_TOC1, main_toc1), 18 functions, 17 live.
// Primary class: CKDetectedMovable  key 0x284c  category Logic  size 0x8  vtable 0xb1c538
// Other owners: CKSrvDetect (5), DetectorList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1aa998  CKDetectedMovable_Delete
//   [ ] 0x1aa9e8  CKDetectedMovable_RecursiveRegistration
//   [ ] 0x1aaa48  FUN_001aaa48  [dead]
//   [x] 0x1aab70  CKDetectedMovable_LoadMovable
//   [ ] 0x1aac98  CKDetectedMovable_Save
//   [ ] 0x1aaca0  CKDetectedMovable_Destroy
//   [ ] 0x1aace0  RegisterCKDetectedMovableClass
//   [ ] 0x1aad58  _GLOBAL__I_1aad58
//   [x] 0x1aad68  CKDetectedMovable_Load
//   [x] 0x1aaec8  CKDetectedMovable_DeleteArray
//   [x] 0x1aaf68  CKDetectedMovable_CreateArray
//   [x] 0x1ab008  CKSrvDetect_SetDetectablePosition_maybe
//   [x] 0x1ab068  CKSrvDetect_RefreshDetectablePositions_maybe
//   [x] 0x1ab0d8  CKSrvDetect_DeactivateSectorDetectables_maybe
//   [x] 0x1ab120  CKSrvDetect_DisablePositionRefreshFor_maybe
//   [x] 0x1ab170  CKSrvDetect_ActivateDetectableNode_maybe
//   [x] 0x1ab1f8  CKDetectedMovable_Create
//   [x] 0x1ab238  DetectorList_ActivateSectorEntries_maybe
//
//   [ ] 0x9ab1e8  CKDetectedMovable_GetClassType  [inline]
//   [ ] 0x9ab1f0  CKDetectedMovable_GetClassID  [inline]
//   [ ] 0x9ab1f8  CKDetectedMovable_Destructor  [inline]
//   [ ] 0x9ab250  CKDetectedMovable_IsKindOfClass  [inline]
//   [ ] 0x9ab270  CKDetectedMovable_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKDetectedMovable.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGMovable.h"

// 0x001aab70 CKDetectedMovable_LoadMovable
void CKDetectedMovable::Entry::Load(IKFile* file) {
    IKFile_ReadRef(file, &m_pMovable);
    ReadU32LE(file, &m_ui32SectorNum);
    ReadU8(file, &m_unk15);
    m_bIsLoaded = 0;
}

// 0x001aad68 CKDetectedMovable_Load: the entries are taken first (each pushed at the head), then the
// first `count` of the list are loaded from the head.
int32_t CKDetectedMovable::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return 1;
    Entry* entry = nullptr;
    for (uint32_t i = 0; i < count; ++i) {
        entry = new Entry;  // a FreeListPool node in the original (not cleared)
        entry->m_pNext = m_lMovables;
        m_lMovables = entry;
    }
    for (uint32_t i = 0; i < count; ++i) {
        entry->Load(file);
        entry = entry->m_pNext;
    }
    return 1;
}

// 0x001ab0d8 CKSrvDetect_DeactivateSectorDetectables_maybe
void CKDetectedMovable::DeactivateSector(int32_t sector) {
    for (Entry* entry = m_lMovables; entry != nullptr; entry = entry->m_pNext) {
        if (static_cast<int32_t>(entry->m_ui32SectorNum) == sector) entry->m_bIsLoaded = 0;
    }
}

// 0x001ab238 DetectorList_ActivateSectorEntries_maybe
void CKDetectedMovable::ActivateSector(int32_t sector) {
    for (Entry* entry = m_lMovables; entry != nullptr; entry = entry->m_pNext) {
        if (static_cast<int32_t>(entry->m_ui32SectorNum) != sector) continue;
        entry->m_bIsLoaded = 1;
        const RwV3d& position = RwFrameGetLTM(static_cast<CSGMovable*>(entry->m_pMovable)->m_pRwFrame)->pos;
        entry->m_v3OldPos = {position.x, position.y, position.z};
    }
}

// 0x001ab008 CKSrvDetect_SetDetectablePosition_maybe
void CKDetectedMovable::SetDetectablePosition(const IKSerializable* movable, const float* position) {
    for (Entry* entry = m_lMovables; entry != nullptr; entry = entry->m_pNext) {
        if (entry->m_bIsLoaded != 0 && entry->m_pMovable == movable) {
            entry->m_v3OldPos = {position[0], position[1], position[2]};
        }
    }
}

// 0x001ab068 CKSrvDetect_RefreshDetectablePositions_maybe
void CKDetectedMovable::RefreshDetectablePositions() {
    for (Entry* entry = m_lMovables; entry != nullptr; entry = entry->m_pNext) {
        if (entry->m_bIsLoaded != 0 && entry->m_unk15 != 0) {
            const RwV3d& position = RwFrameGetLTM(static_cast<CSGMovable*>(entry->m_pMovable)->m_pRwFrame)->pos;
            entry->m_v3OldPos = {position.x, position.y, position.z};
        }
    }
}

// 0x001ab120 CKSrvDetect_DisablePositionRefreshFor_maybe: the loaded entries of `movable` stop refreshing (+0x15 = 0).
void CKDetectedMovable::DisablePositionRefreshFor(IKSerializable* movable) {
    if (movable == nullptr) return;
    for (Entry* entry = m_lMovables; entry != nullptr; entry = entry->m_pNext) {
        if (entry->m_bIsLoaded != 0 && entry->m_pMovable == movable) entry->m_unk15 = 0;
    }
}

// 0x001ab170 CKSrvDetect_ActivateDetectableNode_maybe: the loaded entries of `movable` not refreshing yet start (+0x15 =
// 1) from the node's world position (its frame's LTM, +0x80).
void CKDetectedMovable::ActivateDetectableNode(IKSerializable* movable) {
    if (movable == nullptr) return;
    for (Entry* entry = m_lMovables; entry != nullptr; entry = entry->m_pNext) {
        if (entry->m_bIsLoaded == 0 || entry->m_pMovable != movable || entry->m_unk15 != 0) continue;
        entry->m_unk15 = 1;
        const RwFrame* frame = static_cast<CSGMovable*>(movable)->m_pRwFrame;
        entry->m_v3OldPos.z = frame->ltm.pos.z;
        entry->m_v3OldPos.x = frame->ltm.pos.x;
        entry->m_v3OldPos.y = frame->ltm.pos.y;
    }
}
