// CKHkS08CrumblyZoneMultiState_2.cpp - reconstructed original translation unit 0x4150b8-0x416710 (GAME_TOC1, main_toc1), 25 functions, 23 live.
// Primary class: CKHkS08CrumblyZoneMultiState  key 0x3582  category Hook  size 0xd4  vtable 0xb25bf8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4150b8  CKHkS08CrumblyZoneMultiState_Delete
//   [ ] 0x415108  CKHkS08CrumblyZoneMultiState_IsStateBitSet_maybe  [dead]
//   [ ] 0x415168  CKHkS08CrumblyZoneMultiState_OnDeactivate
//   [ ] 0x415190  CKHkS08CrumblyZoneMultiState_OnActivate
//   [ ] 0x4151c8  CKHkS08CrumblyZoneMultiState_Stop
//   [ ] 0x4151f0  CKHkS08CrumblyZoneMultiState_Restart
//   [ ] 0x415218  CKHkS08CrumblyZoneMultiState_MessageProc
//   [ ] 0x415270  CKHkS08CrumblyZoneMultiState_GetInfo
//   [ ] 0x4152c0  CKHkS08CrumblyZoneMultiState_PostLoad
//   [ ] 0x4152e8  CKHkS08CrumblyZoneMultiState_Save
//   [ ] 0x415310  CKHkS08CrumblyZoneMultiState_RecursiveRegistration
//   [x] 0x415338  CKHkS08CrumblyZoneMultiState_DeleteArray
//   [x] 0x4153d8  CKHkS08CrumblyZoneMultiState_Create
//   [ ] 0x415498  RegisterCKHkS08CrumblyZoneMultiStateClass
//   [ ] 0x415520  _GLOBAL__D_415520
//   [ ] 0x415530  _GLOBAL__I_415530
//   [x] 0x415540  CKHkS08CrumblyZoneMultiState_Start
//   [ ] 0x415638  CKHkS08CrumblyZoneMultiState_SetStateBit_maybe  [dead]
//   [ ] 0x415690  CKHkS08CrumblyZoneMultiState_vfF0
//   [ ] 0x415740  CKHkS08CrumblyZoneMultiState_SpawnExplosionFx
//   [ ] 0x4157b8  CKHkS08CrumblyZoneMultiState_Update
//   [ ] 0x415b48  CKHkS08CrumblyZoneMultiState_GetHitDamage_maybe
//   [ ] 0x415e70  CKHkS08CrumblyZoneMultiState_Destroy
//   [x] 0x415f30  CKHkS08CrumblyZoneMultiState_CreateArray
//   [x] 0x416080  CKHkS08CrumblyZoneMultiState_Load
//
//   [ ] 0x9c2b50  CKHkS08CrumblyZoneMultiState_IsKindOfClass  [inline]
//   [ ] 0x9c2bb0  CKHkS08CrumblyZoneMultiState_GetClassType  [inline]
//   [ ] 0x9c2bb8  CKHkS08CrumblyZoneMultiState_GetClassID  [inline]
//   [ ] 0x9c2bc0  CKHkS08CrumblyZoneMultiState_Destructor  [inline]
//   [ ] 0x9c2ce8  CKHkS08CrumblyZoneMultiState_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "Spyro2008/groups/C22SpyroShims.h"

#include "k2000/io/IKFile.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CKCrumblyZoneState.h"
#include "k2000/memory/Mem.h"

namespace {

// The inlined TVector<T, 1> push of one element: grow to length + 1 when full, then bump the length.
// Returns the new element.
template <class T>
T* PushBack(TVector<T, 1>& v) {
    uint32_t used = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        used = v.m_ui32NbUsedElt;
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = used + 1;
    return &v.m_pBlock[used];
}

// The Load's reset of a vector: capacity 1 and a fresh one-element block (the length is left alone).
template <class T>
void Reserve1(TVector<T, 1>& v) {
    v.m_ui32NbElt = 1;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
}

}  // namespace

// 0x00416080 CKHkS08CrumblyZoneMultiState_Load
int32_t CKHkS08CrumblyZoneMultiState::Load(IKFile* file, int32_t type) {
    CKHkCrumblyZoneMultiState::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk8C);
    ReadU8(file, &m_unk9C);
    ReadF32LE(file, &m_fUnkA0);
    ReadF32LE(file, &m_fUnkA4);
    IKFile_ReadRef(file, &m_pUnkAC);
    // One count for the three vectors.
    uint32_t count = 0;
    ReadU32LE(file, &count);
    Reserve1(m_vUnkB0);
    for (uint32_t i = 0; i < count; ++i) ReadU8(file, PushBack(m_vUnkB0));
    IKFile_ReadRef(file, &m_pUnkBC);
    Reserve1(m_vUnk90);
    for (uint32_t i = 0; i < count; ++i) {
        StateEntry* entry = PushBack(m_vUnk90);
        ReadU32LE(file, &entry->m_unk0);
        for (uint8_t& b : entry->m_unk4) ReadU8(file, &b);
    }
    Reserve1(m_vUnkC0);
    for (uint32_t i = 0; i < count; ++i) ReadU8(file, PushBack(m_vUnkC0));
    ReadU8(file, &m_unkCC);
    ReadU8(file, &m_unkCD);
    ReadU32LE(file, &m_unkD0);
    return 1;
}

// 0x00415540 CKHkS08CrumblyZoneMultiState_Start
void CKHkS08CrumblyZoneMultiState::Start() {
    // 0x004122b8 CKHkCrumblyZoneMultiState_Start (k2000/hooks/CKHkCrumblyZoneMultiState.cpp, family hooks; local
    // copy): the states below +0x28 start with their +0x08 at 0, the others with +0x0c.
    // CKHkActorBase_d82_maybe_ResetRuntime 0x3f6e48: empty.
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        if (m_unk28 > i - 1) {
            state->m_unk08 = 0.0f;
        } else {
            state->m_unk08 = state->m_unk0c;
        }
    }
    // Every state's volumes get the damage object of +0x8c (0x4038f0 -> 0x1903c0, last to first).
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        c22spyro::VolumeArraySetDamage(static_cast<CKBoundingCpnt*>(state->m_pBoundingCpnt), m_pUnk8C);
    }
    // STUB(C2.2): the boss gauge registrations (CKS08GameManager_RegisterBossGaugeZone_maybe 0x4fe330 /
    // _RegisterSecondBossGaugeZone_maybe 0x4feba0, Spyro2008/logic/CKS08GameManager_4.cpp / _5.cpp: family gm)
    // append this zone to the manager's +0xbb4 / +0xbc8 lists, which are TVector<uint32_t> and so cannot hold a
    // pointer in the x64 build. They run only for a boss zone (m_unkCC / m_unkCD set, no LVL010 zone has them).
    if (m_unkCC != 0) {
        DOTD_STUB_ONCE("CKHkS08CrumblyZoneMultiState::Start: RegisterBossGaugeZone");
    }
    if (m_unkCD != 0) {
        DOTD_STUB_ONCE("CKHkS08CrumblyZoneMultiState::Start: RegisterSecondBossGaugeZone");
    }
}
