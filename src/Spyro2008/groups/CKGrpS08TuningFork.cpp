// CKGrpS08TuningFork.cpp - reconstructed original translation unit 0x4cc920-0x4cdaa0 (GAME_TOC1, main_toc1), 29 functions, 25 live.
// Primary class: CKGrpS08TuningFork  key 0xcc4  category Group  size 0x38  vtable 0xb29968
// Other owners: CKHkS08TuningFork (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4cc920  CKGrpS08TuningFork_Delete
//   [ ] 0x4cc970  CKGrpS08TuningFork_Construct  [dead]
//   [x] 0x4cc9e8  CKGrpS08TuningFork_vfB8  (returns 0x2f: undeclared slot, see CKGrpS08TuningFork.h)
//   [ ] 0x4cc9f0  CKGrpS08TuningFork_Construct_2  [dead]
//   [ ] 0x4cca68  RegisterCKGrpS08TuningForkClass
//   [ ] 0x4ccae0  _GLOBAL__I_4ccae0
//   [x] 0x4ccaf0  CKGrpS08TuningFork_DeleteArray
//   [x] 0x4ccb98  CKGrpS08TuningFork_ClearGroupSynced_maybe
//   [x] 0x4ccbd8  CKGrpS08TuningFork_SyncGroupPhases_maybe
//   [x] 0x4ccca8  CKGrpS08TuningFork_ClearGroupPendingFlagForFork_maybe
//   [x] 0x4ccd48  CKGrpS08TuningFork_AreOtherForksVibrating_maybe
//   [x] 0x4ccec8  CKGrpS08TuningFork_Update  (port-final F08)
//   [x] 0x4cd158  CKGrpS08TuningFork_Pause  (empty: IKBaseGroup's Pause)
//   [x] 0x4cd160  CKGrpS08TuningFork_Resume  (empty: IKBaseGroup's Resume)
//   [x] 0x4cd168  CKGrpS08TuningFork_Start
//   [x] 0x4cd228  CKGrpS08TuningFork_Restart
//   [x] 0x4cd270  CKGrpS08TuningFork_Stop  (empty: IKBaseGroup's Stop)
//   [x] 0x4cd278  CKGrpS08TuningFork_RecursiveRegistration  (IKGroup's only: IKBaseGroup::RecursiveRegistration inherited)
//   [ ] 0x4cd2a0  CKGrpS08TuningFork_Save
//   [x] 0x4cd2c8  CKGrpS08TuningFork_Load
//   [x] 0x4cd5e8  CKGrpS08TuningFork_CreateArray
//   [x] 0x4cd6e0  CKGrpS08TuningFork_Create
//   [x] 0x4cd770  CKGrpS08TuningFork_Destroy
//   [ ] 0x4cd868  CKGrpS08TuningFork_Destructor_2  [dead]
//   [x] 0x4cd8e8  CKGrpS08TuningFork_Destructor  (~CKGrpS08TuningFork, CKGrpS08TuningFork.h)
//   [x] 0x4cd968  CKGrpS08TuningFork_DeletingDestructor  (~CKGrpS08TuningFork, CKGrpS08TuningFork.h; delete)
//   [x] 0x4cd9f0  CKHkS08TuningFork_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKHkS08TuningFork))
//   [x] 0x4cda40  CKHkS08TuningFork_State0_Idle_maybe  (CKHkS08TuningFork::State0 in CKHkS08TuningFork.cpp, port-final F07)
//   [ ] 0x4cda98  KStub_Nop_4cda98  [dead]
//
//   [x] 0x9c5ab8  CKGrpS08TuningFork_GetClassType  [inline]
//   [x] 0x9c5ac0  CKGrpS08TuningFork_GetClassID  [inline]
//   [ ] 0x9c5ac8  CKGrpS08TuningFork_vfCC  [inline]
//   [ ] 0x9c5b18  CKGrpS08TuningFork_vfB0  [inline]
//   [ ] 0x9c5b28  CKGrpS08TuningFork_vfB4  [inline]
//   [ ] 0x9c5b38  CKGrpS08TuningFork_vfBC  [inline]
//   [ ] 0x9c5be0  CKGrpS08TuningFork_vfE0  [inline]
//   [ ] 0x9c5be8  CKGrpS08TuningFork_vfE4  [inline]
//   [ ] 0x9c5bf0  CKGrpS08TuningFork_vfE8  [inline]
//   [ ] 0x9c5bf8  CKGrpS08TuningFork_vfD8  [inline]
//   [ ] 0x9c5c38  CKGrpS08TuningFork_vfDC  [inline]
//   [ ] 0x9c5cf8  CKGrpS08TuningFork_IsKindOfClass  [inline]
#include "Spyro2008/groups/CKGrpS08TuningFork.h"

#include "k2000/memory/Mem.h"
#include "Spyro2008/hooks/CKHkS08TuningFork.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/misc/Engine.h"

namespace {
// The inlined TVector push_back (grows by 1 when full).
template <class T>
void PushBack(TVector<T, 1>& vector, T value) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 1u;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock =
            static_cast<T*>(Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = value;
    ++vector.m_ui32NbUsedElt;
}
}  // namespace

// 0x004cd2c8 CKGrpS08TuningFork_Load
int32_t CKGrpS08TuningFork::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // A new one-element block (the old one is not freed); the count is left alone.
    m_vSets.m_ui32NbElt = 1;
    m_vSets.m_pBlock = static_cast<RefSet**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(RefSet*))));
    for (uint32_t i = 0; i < count; ++i) {
        RefSet* set = new RefSet;  // OperatorNew(0x10)
        set->m_vRefs.m_ui32NbElt = 1;
        set->m_vRefs.m_pBlock = nullptr;
        set->m_vRefs.m_ui32NbUsedElt = 0;
        set->m_vRefs.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
        uint32_t refs = 0;
        ReadU32LE(file, &refs);
        for (uint32_t k = 0; k < refs; ++k) {
            IKSerializable* ref = nullptr;
            IKFile_ReadRef(file, &ref);
            PushBack(set->m_vRefs, ref);
        }
        PushBack(m_vSets, set);
    }
    return 1;
}

// 0x004cd770 CKGrpS08TuningFork_Destroy (vt+0x10)
void CKGrpS08TuningFork::Destroy() {
    DestroyGroupLists();
    for (uint32_t i = 0; i < m_vSets.m_ui32NbUsedElt; ++i) {
        RefSet* set = m_vSets.m_pBlock[i];
        if (set == nullptr) continue;
        if (set->m_vRefs.m_pBlock != nullptr) Mem_FreeAligned16(set->m_vRefs.m_pBlock);
        set->m_vRefs.m_pBlock = nullptr;
        set->m_vRefs.m_ui32NbUsedElt = 0;
        ::operator delete(set);  // OperatorDelete
    }
    m_vSets.m_ui32NbUsedElt = 0;
}

// 0x004cd168 CKGrpS08TuningFork_Start (vt+0x50)
void CKGrpS08TuningFork::Start() {
    for (uint32_t i = 0; i < m_vSets.m_ui32NbUsedElt; ++i) m_vSets.m_pBlock[i]->m_unk0c = 0;
    SetObjectActive(g_pEngine->m_coreManager, this, 1);  // 0x0001d1c0
    Restart();  // vt+0x54
}

// 0x004cd228 CKGrpS08TuningFork_Restart (vt+0x54)
void CKGrpS08TuningFork::Restart() {
    for (uint32_t i = 0; i < m_vSets.m_ui32NbUsedElt; ++i) m_vSets.m_pBlock[i]->m_unk0d = 0;
}

// 0x004ccec8 CKGrpS08TuningFork_Update (vt+0x7c, port-final F08): every pending set whose forks are all in state 1
// with +0x121 (IsState1AndFlag121Set 0x004ce4b8) switches each fork to state 2 through its state table (the inlined
// state change: the current state left with 2, unless none, then state 2 entered with the previous one).
void CKGrpS08TuningFork::Update(IKTime* clock) {
    for (uint32_t i = 0; i < m_vSets.m_ui32NbUsedElt; ++i) {
        if (m_vSets.m_pBlock[i]->m_unk0d == 0) continue;
        if (m_vSets.m_pBlock[i]->m_vRefs.m_ui32NbUsedElt == 0) continue;
        uint32_t all = 1;
        uint32_t k = 0;
        do {
            CKHkS08TuningFork* fork = static_cast<CKHkS08TuningFork*>(m_vSets.m_pBlock[i]->m_vRefs.m_pBlock[k]);
            ++k;
            if ((fork->IsState1AndFlag121Set() & 0xffu) == 0) all = 0;  // neg / srawi / and
        } while (k < m_vSets.m_pBlock[i]->m_vRefs.m_ui32NbUsedElt);
        if (m_vSets.m_pBlock[i]->m_vRefs.m_ui32NbUsedElt == 0) continue;
        for (uint32_t n = 0; n < m_vSets.m_pBlock[i]->m_vRefs.m_ui32NbUsedElt; ++n) {
            if ((all & 0xffu) == 0) continue;
            CKHkS08TuningFork* fork = static_cast<CKHkS08TuningFork*>(m_vSets.m_pBlock[i]->m_vRefs.m_pBlock[n]);
            fork->ChangeState(2, clock);  // +0x130 = 2 between the two handler calls
        }
    }
}

// 0x004ccb98 CKGrpS08TuningFork_ClearGroupSynced_maybe
void CKGrpS08TuningFork::ClearGroupSynced(uint32_t index) {
    if (!(index < m_vSets.m_ui32NbUsedElt)) return;
    RefSet* set = m_vSets.m_pBlock[index];
    if (set->m_unk0c == 0) return;
    set->m_unk0c = 0;
}

// 0x004ccbd8 CKGrpS08TuningFork_SyncGroupPhases_maybe
void CKGrpS08TuningFork::SyncGroupPhases(uint32_t index) {
    if (!(index < m_vSets.m_ui32NbUsedElt)) return;
    RefSet* set = m_vSets.m_pBlock[index];
    if (set->m_unk0c != 0 || set->m_vRefs.m_ui32NbUsedElt == 0) return;
    const float phase = static_cast<CKHkS08TuningFork*>(set->m_vRefs.m_pBlock[0])->m_fUnk70;
    uint32_t i = 0;
    do {
        static_cast<CKHkS08TuningFork*>(set->m_vRefs.m_pBlock[i])->SetPhaseOffsetFrom(phase);  // 0x004ce910
        ++i;
        set = m_vSets.m_pBlock[index];
    } while (i < set->m_vRefs.m_ui32NbUsedElt);
    set->m_unk0c = 1;
}

// 0x004ccca8 CKGrpS08TuningFork_ClearGroupPendingFlagForFork_maybe
uint32_t CKGrpS08TuningFork::ClearGroupPendingFlagForFork(IKSerializable* fork, uint32_t index) {
    if (!(index < m_vSets.m_ui32NbUsedElt)) return 0;
    RefSet* set = m_vSets.m_pBlock[index];
    const uint32_t count = set->m_vRefs.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        if (set->m_vRefs.m_pBlock[i] == fork) {
            set->m_unk0d = 0;
            return 1;
        }
    }
    return 0;
}

// 0x004ccd48 CKGrpS08TuningFork_AreOtherForksVibrating_maybe
uint32_t CKGrpS08TuningFork::AreOtherForksVibrating(IKSerializable* fork, uint32_t index) {
    uint32_t found = 0;
    if (index < m_vSets.m_ui32NbUsedElt) {
        RefSet* set = m_vSets.m_pBlock[index];
        if (set->m_vRefs.m_ui32NbUsedElt != 0) {
            bool all = true;
            for (uint32_t i = 0; i < m_vSets.m_pBlock[index]->m_vRefs.m_ui32NbUsedElt; ++i) {
                IKSerializable* other = m_vSets.m_pBlock[index]->m_vRefs.m_pBlock[i];
                if (other == fork) {
                    found = 1;
                    continue;
                }
                if ((static_cast<CKHkS08TuningFork*>(other)->IsVibrating() & 0xffu) == 0) all = false;  // 0x004ce660
            }
            if (!all) return found;
        }
    }
    m_vSets.m_pBlock[index]->m_unk0d = 1;  // BUG(original): also past the count
    return found;
}
