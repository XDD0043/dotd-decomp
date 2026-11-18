// CKGrpS08TuningFork.h - the tuning-fork puzzle group (key 0xcc4, vtable 0xb29968, size 0x38). Original
// unit: CKGrpS08TuningFork.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

class CKGrpS08TuningFork : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x33)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5cf8
        return key == 0xcc4 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpS08TuningFork)

    // One reference list (OperatorNew(0x10): the vector, then a word nobody sets).
    struct RefSet {
        TVector<IKSerializable*, 1> m_vRefs;  // +0x00 null, 1, 0, then a 4-byte block
        uint8_t m_unk0c;                      // +0x0c not set by the Load: the forks' phases synced (SyncGroupPhases)
        uint8_t m_unk0d;                      // +0x0d not set by the Load: the set pending (AreOtherForksVibrating)
        uint8_t m_pad0e[2];
    };

    // 0x004cd6e0 CKGrpS08TuningFork_Create (the constructor 0x4cc970 inlined): the vector null, 1, 0.
    CKGrpS08TuningFork() {
        m_vSets.m_pBlock = nullptr;
        m_vSets.m_ui32NbElt = 1;
        m_vSets.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004cd2c8 CKGrpS08TuningFork_Load
    // port-all P22:
    // 0x004cd8e8 CKGrpS08TuningFork_Destructor / 0x004cd968 _DeletingDestructor: the set vector's block freed, its count
    // and block cleared (the sets themselves are Destroy's).
    ~CKGrpS08TuningFork() override {
        if (m_vSets.m_pBlock != nullptr) Mem_FreeAligned16(m_vSets.m_pBlock);
        m_vSets.m_ui32NbUsedElt = 0;
        m_vSets.m_pBlock = nullptr;
    }
    // vt+0x10 0x004cd770 CKGrpS08TuningFork_Destroy: no child groups, no members (vt+0xb0's head), every set's block
    // freed and the set deleted, no set.
    void Destroy() override;
    // vt+0x50 0x004cd168 CKGrpS08TuningFork_Start: no set synced, the group woken (SetObjectActive_maybe), Restart (vt+0x54).
    void Start() override;
    // vt+0x54 0x004cd228 CKGrpS08TuningFork_Restart: no set pending.
    void Restart() override;
    // vt+0x68 0x004cd270 Stop / vt+0x70 0x004cd158 Pause / vt+0x78 0x004cd160 Resume: empty (IKBaseGroup's). vt+0x24
    // 0x004cd278 RecursiveRegistration: IKGroup's (0x12a68) only, inherited. vt+0xb8 0x004cc9e8 vfB8 returns 0x2f:
    // IKBaseGroup models no slot there and no ported code calls it.
    // vt+0x7c 0x004ccec8 CKGrpS08TuningFork_Update (port-final F08): every pending set whose forks are all in state 1
    // with +0x121 switches each fork to state 2 through the fork's state table (CKHkS08TuningFork::ChangeState).
    void Update(IKTime* clock) override;
    // 0x004ccb98 CKGrpS08TuningFork_ClearGroupSynced_maybe: set `index`'s synced flag cleared.
    void ClearGroupSynced(uint32_t index);
    // 0x004ccbd8 CKGrpS08TuningFork_SyncGroupPhases_maybe: an unsynced set's forks all take their phase offset from the
    // first fork's phase (+0x70), then the set is synced.
    void SyncGroupPhases(uint32_t index);
    // 0x004ccca8 CKGrpS08TuningFork_ClearGroupPendingFlagForFork_maybe: when `fork` is in set `index`, its pending flag
    // cleared and 1; else 0.
    uint32_t ClearGroupPendingFlagForFork(IKSerializable* fork, uint32_t index);
    // 0x004ccd48 CKGrpS08TuningFork_AreOtherForksVibrating_maybe: whether `fork` is in set `index`; when every other fork
    // vibrates (or the set is empty) the set is pending. BUG(original): an index past the count marks that slot anyway.
    uint32_t AreOtherForksVibrating(IKSerializable* fork, uint32_t index);

    TVector<RefSet*, 1> m_vSets;  // +0x2c
};
DOTD_ASSERT_SIZE(CKGrpS08TuningFork::RefSet, 0x10);
DOTD_ASSERT_SIZE(CKGrpS08TuningFork, 0x38);
DOTD_ASSERT_OFFSET(CKGrpS08TuningFork, m_vSets, 0x2c);
