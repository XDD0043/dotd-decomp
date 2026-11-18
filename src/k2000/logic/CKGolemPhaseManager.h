// CKGolemPhaseManager.h - the golem boss's phase list (key 0x974c, vtable 0xb29160, size 0x28). Original unit:
// CKGolemPhaseManager.cpp (0x4bcf30-0x4bddd8). Derived straight from IKSerializable. No XXL2 class of this
// name: the members keep placeholder names. Minimal for C2.1: constructor and Load. Two inlined growable
// arrays (TVector, grow by 1) of references.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class IKTime;

class CKGolemPhaseManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25d)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x974c || key == 0xc; }  // vt+0x08 0x9c5678
    DOTD_DECLARE_FACTORIES(CKGolemPhaseManager)

    CKGolemPhaseManager();  // 0x004bcf80 CKGolemPhaseManager_Construct
    ~CKGolemPhaseManager() override;  // 0x004bdca8 CKGolemPhaseManager_Destructor
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004bd7d8 CKGolemPhaseManager_Load
    // vt+0x30 0x004bcfb8 CKGolemPhaseManager_PostLoad: for the level (type 0) no current phase (+0x20 = -1).
    int32_t PostLoad(int32_t type) override {
        if (type == 0) m_unk20 = -1;
        return 1;
    }
    // 0x004bd330 CKGolemPhaseManager_GetCurrentPhase_maybe: the phase at +0x20 (unsigned) when it is below the count,
    // else null.
    IKSerializable* GetCurrentPhase() const {
        const uint32_t index = static_cast<uint32_t>(m_unk20);
        return index < m_phases.m_ui32NbUsedElt ? m_phases.m_pBlock[index] : nullptr;
    }

    // The manager slots (the golem hook calls them).
    virtual void UpdateCurrentPhase(IKTime* clock);  // vt+0x50 0x004bd138 CKGolemPhaseManager_UpdateCurrentPhase
    virtual void StartCurrentPhase();                // vt+0x54 0x004bd618 CKGolemPhaseManager_vf54
    virtual void StopCurrentPhase();                 // vt+0x58 0x004bd598 CKGolemPhaseManager_StopCurrentPhase
    virtual void ResetAllPhases();                   // vt+0x5c 0x004bd4f8 CKGolemPhaseManager_ResetAllPhases_maybe
    virtual void Vf60();                             // vt+0x60 0x004bd470 CKGolemPhaseManager_vf60
    // 0x004bd1a8 CKGolemPhaseManager_SwitchToPhase_maybe
    void SwitchToPhase(uint32_t phase, uint32_t step, float blend);

    IKSerializable* m_unk04;                   // +0x04 object reference (file: the golem hook, 0x31c2)
    TVector<IKSerializable*, 1> m_phases;      // +0x08 CKGolemPhaseAttack / CKGolemPhaseQTE references
    TVector<IKSerializable*, 1> m_unk14;       // +0x14 CKGolemAttackCommon references
    int32_t m_unk20;                           // +0x20 PostLoad: -1 (_maybe: the current phase index)
    int32_t m_unk24;                           // +0x24 (file: -1, 0, 1)
};
DOTD_ASSERT_SIZE(CKGolemPhaseManager, 0x28);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_phases, 0x08);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGolemPhaseManager, m_unk24, 0x24);
