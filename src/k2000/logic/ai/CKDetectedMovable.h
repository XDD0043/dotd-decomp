// CKDetectedMovable.h - the movables a detector watches (key 0x284c, vtable 0xb1c538, size 0x8).
// Original unit: CKDetectedMovable.cpp. XXL2: K/KServices/KServiceDetect/CKDetectedMovable.h, where the
// class is one movable (m_pMovable, m_v3OldPos, m_v3OldPosTeleport, m_ui32SectorNum, m_bIsLoaded); DotD
// keeps a list of such entries.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKDetectedMovable : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xa1)
    DOTD_DECLARE_FACTORIES(CKDetectedMovable)

    // One movable (0x1c bytes; FreeListPool 0x00ceaa84 in the original). Names after XXL2's members.
    struct Entry {
        // 0x001aab70 CKDetectedMovable_LoadMovable
        void Load(IKFile* file);

        IKSerializable* m_pMovable;  // +0x00 XXL2 m_pMovable (a CSGMovable reference)
        CVector3 m_v3OldPos;         // +0x04 XXL2 m_v3OldPos _maybe; not loaded
        uint32_t m_ui32SectorNum;    // +0x10 XXL2 m_ui32SectorNum
        uint8_t m_bIsLoaded;         // +0x14 XXL2 m_bIsLoaded _maybe; the Load sets 0
        uint8_t m_unk15;             // +0x15 a byte from the file
        uint8_t m_pad16[2];
        Entry* m_pNext;              // +0x18
    };

    CKDetectedMovable() { m_lMovables = nullptr; }  // inlined in 0x001ab1f8 CKDetectedMovable_Create
    ~CKDetectedMovable() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001aad68 CKDetectedMovable_Load

    // 0x001ab0d8 CKSrvDetect_DeactivateSectorDetectables_maybe: the entries of that sector are not loaded.
    void DeactivateSector(int32_t sector);
    // 0x001ab238 DetectorList_ActivateSectorEntries_maybe: the entries of that sector are loaded, their old position
    // taken from the movable's frame (the position of its LTM).
    void ActivateSector(int32_t sector);
    // 0x001ab008 CKSrvDetect_SetDetectablePosition_maybe: the old position of the loaded entry for `movable`.
    void SetDetectablePosition(const IKSerializable* movable, const float* position);
    // 0x001ab068 CKSrvDetect_RefreshDetectablePositions_maybe: the old position of every loaded entry that is flagged
    // (+0x15) taken from its movable's frame.
    void RefreshDetectablePositions();

    // 0x001ab120 CKSrvDetect_DisablePositionRefreshFor_maybe / 0x001ab170 CKSrvDetect_ActivateDetectableNode_maybe.
    void DisablePositionRefreshFor(IKSerializable* movable);
    void ActivateDetectableNode(IKSerializable* movable);
    Entry* m_lMovables;  // +0x04 the entry list (the last allocated first)
};
DOTD_ASSERT_SIZE(CKDetectedMovable::Entry, 0x1c);
DOTD_ASSERT_OFFSET(CKDetectedMovable::Entry, m_ui32SectorNum, 0x10);
DOTD_ASSERT_OFFSET(CKDetectedMovable::Entry, m_unk15, 0x15);
DOTD_ASSERT_OFFSET(CKDetectedMovable::Entry, m_pNext, 0x18);
DOTD_ASSERT_SIZE(CKDetectedMovable, 0x8);
DOTD_ASSERT_OFFSET(CKDetectedMovable, m_lMovables, 0x04);
