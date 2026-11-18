// CKGrpMeca.cpp - reconstructed original translation unit 0x3f8130-0x3f8ba8 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary owner: CKGrpMeca (not a registered class)
// Other owners: CKGrpS08Meca (4), ActiveActorList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f8130  CKGrpS08Meca_ConstructBase_maybe
//   [x] 0x3f81c0  CKGrpMeca_vf50
//   [x] 0x3f8268  CKGrpS08Meca_vfA8  (CKGrpMeca::OnLock)
//   [x] 0x3f82f8  CKGrpMeca_PostLoad
//   [ ] 0x3f8340  CKGrpMeca_FreeBuffer_maybe  [dead]
//   [x] 0x3f8368  CKGrpMeca_UpdateMembers_maybe
//   [x] 0x3f8480  CKGrpMeca_OnLevelExit
//   [x] 0x3f8508  ActiveActorList_Remove_maybe
//   [x] 0x3f8630  CKGrpS08Meca_vfAC  (CKGrpMeca::OnUnlock)
//   [ ] 0x3f86c0  CKGrpS08Meca_ConstructBase_2_maybe  [dead]
//   [ ] 0x3f8750  CKGrpMeca_Save
//   [x] 0x3f8778  CKGrpMeca_Load
//   [x] 0x3f8988  CKGrpMeca_LevelReset  (RecursiveRegistration: IKGroup's (inherited; IKGroup_LevelReset 0x12a68), then 1)
//   [x] 0x3f89b0  CKGrpMeca_ClearReferences
//   [x] 0x3f8a20  CKGrpMeca_Destructor  (~CKGrpMeca, CKGrpMeca.h)
//   [x] 0x3f8aa0  CKGrpMeca_DeletingDestructor  (~CKGrpMeca, CKGrpMeca.h; delete)
//   [x] 0x3f8b28  CKGrpMeca_BaseDestructor
//
//   [x] 0x9c0d60  CKGrpMeca_GetClassGroup  [inline]
//   [x] 0x9c0d68  CKGrpMeca_GetClassId  [inline]
//   [ ] 0x9c0d70  CKGrpMeca_vfCC  [inline]
//   [ ] 0x9c0d78  CKGrpMeca_IsKindOf  [inline]
#include "k2000/misc/CKGrpMeca.h"

#include "k2000/groups/TVectorPush.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/misc/CKMecaCpntBase.h"

// 0x003f8778 CKGrpMeca_Load. A u16 count; without components the capacity is 10 and the Load returns.
int32_t CKGrpMeca::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint16_t count = 0;
    ReadU16LE(file, &count);
    TVector_ResizeForLoad(m_apMecaCpnts, count);
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_apMecaCpnts.m_pBlock[i]);
    return 1;
}

// 0x003f82f8 CKGrpMeca_PostLoad: IKLife_PostLoad, then 300 words (4 bytes each) at +0x2c whatever the type.
int32_t CKGrpMeca::PostLoad(int32_t type) {
    PostLoadLife(type);
    m_pUnk2c = static_cast<IKHook**>(Mem_CallocAligned16(sizeof(IKHook*), 300));  // DOTD: 4 bytes a slot on the PS3
    return 1;
}

// 0x003f81c0 CKGrpMeca_vf50 (the Start): the halfword +0x30 cleared, every mechanism component told (vt+0x58),
// then the byte +0x32 cleared.
void CKGrpMeca::Start() {
    m_unk30 = 0;
    for (uint32_t i = 0; i < m_apMecaCpnts.m_ui32NbUsedElt; ++i) {
        static_cast<IKMecaCpnt*>(m_apMecaCpnts.m_pBlock[i])->Vf58();
    }
    m_unk32 = 0;
}

// 0x003f8368 CKGrpMeca_UpdateMembers_maybe
void CKGrpMeca::UpdateMembers(IKTime* clock) {
    for (uint32_t i = 0; i < m_apMecaCpnts.m_ui32NbUsedElt; ++i) {
        static_cast<IKMecaCpnt*>(m_apMecaCpnts.m_pBlock[i])->Vf60(clock);  // vt+0x60
    }
    const int8_t step = static_cast<int8_t>(m_unk32);
    if (step == 1 || step == 3) {
        m_unk32 = 2;
    } else if (step == 2) {
        m_unk32 = 0;
    }
}

// 0x003f80d0 ActiveActorList_AddUnique_maybe: the first null slot of +0x2c takes `actor` and +0x30 grows by one, unless
// `actor` is met first. Start clears only the count, so the slots of earlier actors stay.
void CKGrpMeca::AddActiveActor(IKHook* actor) {
    IKHook** slot = m_pUnk2c;
    while (*slot != nullptr) {
        if (*slot == actor) return;
        ++slot;
    }
    *slot = actor;
    m_unk30 = static_cast<uint16_t>(m_unk30 + 1);
}

// 0x003f8508 ActiveActorList_Remove_maybe: from `actor` on, each slot takes the next one's entry (up to the null one);
// on finding it the count drops by one and, with bit 1 of its bit array (locked), the actor is unlocked
// (SetObjectLocked 0x0001c250, the engine's core manager +0x2c).
void CKGrpMeca::RemoveActiveActor(IKHook* actor) {
    IKHook** list = m_pUnk2c;
    if (list[0] == nullptr) return;
    bool found = false;
    for (uint32_t i = 0; list[i] != nullptr; ++i) {
        if (list[i] == actor) {
            m_unk30 = static_cast<uint16_t>(m_unk30 - 1);
            if ((list[i]->m_bitArray & 2u) != 0) SetObjectLocked(g_pEngine->m_coreManager, list[i], 0);
            found = true;
        }
        if (found) list[i] = list[i + 1];
        list = m_pUnk2c;
    }
}

// 0x003f89b0 CKGrpMeca_Destroy
void CKGrpMeca::Destroy() {
    m_lChilds = nullptr;
    *GetMemberListHead() = nullptr;  // vt+0xb0
    // BUG(original): the slots' pointer is not cleared (and freed even when null: Mem_FreeAligned16 takes null).
    Mem_FreeAligned16(m_pUnk2c);
}

// 0x003f8480 CKGrpMeca_Stop
void CKGrpMeca::Stop() {
    for (uint32_t i = 0; i < m_apMecaCpnts.m_ui32NbUsedElt; ++i) static_cast<IKMecaCpnt*>(m_apMecaCpnts.m_pBlock[i])->Vf5C();
}

// 0x003f8268 CKGrpS08Meca_vfA8 (OnLock): the core manager read once, then each actor slot up to the null one.
void CKGrpMeca::OnLock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKHook** slot = m_pUnk2c; *slot != nullptr; ++slot) SetObjectLocked(core, *slot, 1);
}

// 0x003f8630 CKGrpS08Meca_vfAC (OnUnlock)
void CKGrpMeca::OnUnlock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKHook** slot = m_pUnk2c; *slot != nullptr; ++slot) SetObjectLocked(core, *slot, 0);
}
