// CKGrpMeca.h - the base of the mechanism groups (key 0x2c4, vtable 0xb24f80, size 0x40). Original unit:
// CKGrpMeca.cpp (0x3f8130 the constructor, Ghidra CKGrpS08Meca_ConstructBase_maybe; 0x3f8778 Load). XXL2:
// K/KMeca/Group/CKGrpMeca.h; its last member m_apMecaCpnts (TVector<IKMecaCpnt*, 10>) is the vector the
// Load reads (same growth step). +0x2c/+0x30 are not set by the constructor or the Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

class CKGrpMeca : public IKGroup<IKHook> {
public:
    // vt+0x10 0x003f89b0 CKGrpMeca_Destroy: no child groups, no members (vt+0xb0's head), the actor slots (+0x2c) freed.
    void Destroy() override;
public:
    // 0x003f8130 CKGrpS08Meca_ConstructBase_maybe (CKGrpMeca's constructor): the vector null, 10, 0 and the
    // priority word 0x80000027.
    CKGrpMeca() {
        m_apMecaCpnts = {nullptr, 10, 0};
        m_ui32Priority = 0x80000027u;
    }
    // 0x003f8b28 CKGrpMeca_BaseDestructor: the mechanism component block freed, its size and block cleared.
    ~CKGrpMeca() override {
        if (m_apMecaCpnts.m_pBlock != nullptr) Mem_FreeAligned16(m_apMecaCpnts.m_pBlock);
        m_apMecaCpnts.m_ui32NbUsedElt = 0;
        m_apMecaCpnts.m_pBlock = nullptr;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f8778 CKGrpMeca_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x003f82f8 CKGrpMeca_PostLoad
    void Start() override;  // vt+0x50 0x003f81c0 CKGrpMeca_vf50
    void Stop() override;  // vt+0x68 0x003f8480 CKGrpMeca_Stop: every mechanism component's vt+0x5c
    // vt+0xa8 0x003f8268 CKGrpS08Meca_vfA8 / vt+0xac 0x003f8630 CKGrpS08Meca_vfAC (OnLock / OnUnlock): every active
    // actor of +0x2c (up to the null slot) locked / unlocked (SetObjectLocked 0x1c250).
    void OnLock() override;
    void OnUnlock() override;
    // The active actor list (+0x2c, null-terminated; +0x30 the count) the actor base's OnActivate / OnDeactivate keep.
    // 0x003f80d0 ActiveActorList_AddUnique_maybe: `actor` stored in the first free slot unless it is listed already.
    void AddActiveActor(IKHook* actor);
    // 0x003f8508 ActiveActorList_Remove_maybe: `actor` taken out (the later entries moved down), the count lowered and a
    // locked actor (bit 1 of its bit array) unlocked (SetObjectLocked 0x1c250).
    void RemoveActiveActor(IKHook* actor);
    // 0x003f8368 CKGrpMeca_UpdateMembers_maybe (CKGrpS08Meca_Update): every mechanism component's vt+0x60 with the clock
    // (the crumbly zone component's queued impulse placements), then the step byte +0x32 moves on (1 / 3 -> 2, 2 -> 0).
    void UpdateMembers(IKTime* clock);
    // vt+0xb8 0x003f80c8 CKGrpMeca_vfB8 (XXL2 CKGrpMeca::GetParentClassID): 1. IKBaseGroup declares no slot past +0xb0
    // here, and no caller of the slot was found (C2.8 port-rest R02).
    virtual int32_t GetParentClassID() { return 1; }

    IKHook** m_pUnk2c;                           // +0x2c not set by the constructor or the Load; PostLoad: 300 words,
                                                 //       the active actor list (AddActiveActor)
    uint16_t m_unk30;                            // +0x30 runtime (Start: 0): the active actors counted
    uint8_t m_unk32;                             // +0x32 runtime (Start: 0)
    uint8_t m_pad33;
    TVector<IKSerializable*, 10> m_apMecaCpnts;  // +0x34 XXL2 IKMecaCpnt* (LVL010: a CKCrumblyZoneCpnt ref)
};
DOTD_ASSERT_SIZE(CKGrpMeca, 0x40);
DOTD_ASSERT_OFFSET(CKGrpMeca, m_pUnk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpMeca, m_apMecaCpnts, 0x34);
