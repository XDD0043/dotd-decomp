// IKLife.h - base of the hooks and the groups (key 0x2fe; XXL2: K/KCore/Interfaces/IKLife.h).
//
// PS3 layout: IKUpdatable (vtable) + XXL2's CSPriorityUpdatableLifeNode (+0x04 next, +0x08 priority) +
// m_bitArray (+0x0c) + m_iSectorIndex (+0x10). XXL2's m_iCountLock (cleared by its Load) is not in the
// PS3 build: the PS3 Load writes nothing but what it reads.
//
// The Load body is inline here: its original sits in the CDefaultGameManager.cpp TU (0x19cf0), and the
// group/hook classes of several families need it.
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"

class IKLife : public IKUpdatable {
public:
    // vt+0x08 0x00990d30 IKLife_IsKindOfClass: IKLife (0x2fe), IKUpdatable (0x3fe), IKSerializable (0xc).
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2fe || key == 0x3fe || key == 0xc; }
    // Inlined in every Create (CKGroupRoot_Create 0x22a58: +0x04 = 0, +0x08 = 0x7fffffff).
    IKLife() {
        m_pNext = nullptr;
        m_ui32Priority = 0x7fffffff;
    }

    // vt+0x2c 0x00019cf0 IKLife_Load. XXL2 IKLife::Load reads the same three things in the same order
    // (m_bitArray, m_iSectorIndex, then the update-list node through EUL_TSNodeList_Read).
    int32_t Load(IKFile* file, int32_t type) override {
        if (type != K_LEVEL_PLATEFORMS) return 1;
        ReadU32LE(file, &m_bitArray);
        ReadU32LE(file, &m_iSectorIndex);
        IKFile_ReadRef(file, &m_pNext);
        return 1;
    }

    // 0x00019f68 IKLife_PostLoad (not virtual: the PostLoad of the hooks and groups that call it, e.g.
    // CKHkActorBase 0x3f6e70, CKGrpMeca 0x3f82f8): the level type marks the life as in an unloaded sector
    // (bit 2 of the bit array; SectorLoaded clears it again).
    void PostLoadLife(int32_t type) {
        if (type != K_LEVEL_PLATEFORMS) return;
        m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    }

    // vt+0x94 0x990c78 (empty for hooks and groups): called by CKBundle_InitHooks_maybe on every life whose
    // bit 0 is clear. Arguments unverified.
    virtual void Vf94() {}
    // vt+0x98 0x990c80 (empty): the counterpart of Vf94, called when a life goes to sleep (CKServiceLife).
    virtual void Vf98() {}

    // vt+0x88 0x00019e60 IKLife_SectorLoaded / vt+0x8c 0x00019ed8 IKLife_SectorUnload (XXL2 IKLife::SectorLoaded /
    // SectorUnload): a life of that sector gets bit 2 of m_bitArray cleared and SectorNowValid (vt+0xa0), or
    // SectorNowInvalid (vt+0xa4) and the bit set.
    void SectorLoaded(int32_t sector) override {
        if (static_cast<int32_t>(m_iSectorIndex) != sector) return;
        m_bitArray &= 0xfffffffbu;
        VfA0();
    }
    void SectorUnload(int32_t sector) override {
        if (static_cast<int32_t>(m_iSectorIndex) != sector) return;
        VfA4();
        m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    }
    // vt+0x9c: IKHook 0x198c8 / IKGroup 0x12960 return -1. vt+0xa0 / +0xa4 (XXL2 SectorNowValid / SectorNowInvalid):
    // empty in the hooks and groups (0x990c88 / 0x990c90).
    virtual int32_t Vf9C() { return -1; }
    virtual void VfA0() {}
    virtual void VfA4() {}
    // vt+0xa8 / +0xac (XXL2 IKLife::Lock / Unlock, shifted by DotD's 0x18): called by SetObjectLocked (0x1c250) when
    // a cinematic scene (or another locker) locks / unlocks the object. Empty for the groups (0x990c98 /
    // 0x990ca0) and most hooks; CKHkS08Hero overrides them (0x2dbb88 CKHkS08Hero_OnLock / 0x2dafa8 OnUnlock).
    virtual void OnLock() {}
    virtual void OnUnlock() {}

    IKLife* m_pNext;          // +0x04 XXL2 CSPriorityUpdatableLifeNode::m_pNext (a reference in the file)
    uint32_t m_ui32Priority;  // +0x08 the node's priority_maybe (0x7fffffff, as IKService's); not loaded
    uint32_t m_bitArray;      // +0x0c XXL2 CBitArray m_bitArray (m_ui32Bits)
    uint32_t m_iSectorIndex;  // +0x10 XXL2 KSectorIndex m_iSectorIndex
};
DOTD_ASSERT_SIZE(IKLife, 0x14);
DOTD_ASSERT_OFFSET(IKLife, m_pNext, 0x04);
DOTD_ASSERT_OFFSET(IKLife, m_bitArray, 0x0c);
DOTD_ASSERT_OFFSET(IKLife, m_iSectorIndex, 0x10);
