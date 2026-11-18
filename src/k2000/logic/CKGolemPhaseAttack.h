// CKGolemPhaseAttack.h - a golem boss phase of attacks (key 0x97cc, vtable 0xb290c8, size 0x30). Original unit:
// CKGolemPhaseAttack.cpp. No XXL2 class. A list of steps: each runs one attack (CKGolemAttackCommon) with two lists
// of condition records that choose the next phase and step.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGolemAttackCommon.h"
#include "k2000/misc/CKGolemPhaseBase.h"
#include "k2000/misc/GolemPhaseCondAnd.h"
#include "k2000/util/TVector.h"

class CKGolemPhaseAttack : public CKGolemPhaseBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5620
        return key == 0x97cc || key == 0xc || key == 0x978c;
    }
    DOTD_DECLARE_FACTORIES(CKGolemPhaseAttack)

    using AttackA = GolemStepA;
    using AttackB = GolemStepB;
    // OperatorNew(0x1c) record: one step of the phase.
    struct Step {
        CKGolemAttackCommon* m_unk00;      // +0x00 the attack (a reference: read first, stored last)
        TVector<AttackA*, 1> m_attacksA;   // +0x04
        TVector<AttackB*, 1> m_attacksB;   // +0x10
    };

    // 0x004bad58 CKGolemPhaseAttack_Construct (inlined the same in Create): the step list empty, capacity 1.
    CKGolemPhaseAttack() {
        m_steps.m_pBlock = nullptr;
        m_steps.m_ui32NbElt = 1;
        m_steps.m_ui32NbUsedElt = 0;
    }
    ~CKGolemPhaseAttack() override;  // vt+0x00 0x004bc1a0 CKGolemPhaseAttack_Destructor
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004bc3d8 CKGolemPhaseAttack_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004bbbe8 CKGolemPhaseAttack_PostLoad
    void Destroy() override;                            // vt+0x10 0x004bc080 CKGolemPhaseAttack_Destroy

    void Update(IKTime* clock) override;                // vt+0x50 0x004bb028 CKGolemPhaseAttack_Update
    void Start() override;                              // vt+0x54 0x004bb950 CKGolemPhaseAttack_Start
    void Stop() override;                               // vt+0x58 0x004bb320 CKGolemPhaseAttack_Stop
    void ResetPhases() override;                        // vt+0x5c 0x004bb3f8 CKGolemPhaseAttack_ResetPhases_maybe
    void Vf60() override;                               // vt+0x60 0x004bb6a0 CKGolemPhaseAttack_vf60
    void SwitchToStep(uint32_t step, float blend) override;     // vt+0x64 0x004bb0c8 CKGolemPhaseAttack_SwitchToStep
    void StartStepNoStop(uint32_t step, float blend) override;  // vt+0x68 0x004baec0 CKGolemPhaseAttack_StartStepNoStop_maybe
    int32_t GetDamageSincePhaseStart() override;  // vt+0x6c 0x004bac50 CKGolemPhaseAttack_GetDamageSincePhaseStart_maybe
    void MarkDamageBaseline() override;           // vt+0x70 0x004bab98 CKGolemPhaseAttack_MarkDamageBaseline_maybe
    int32_t GetDamageSinceMark2() override;       // vt+0x74 0x004bac10 CKGolemPhaseAttack_GetDamageSinceMark2_maybe
    int32_t GetDamageSinceUpdate() override;      // vt+0x78 0x004babd0 CKGolemPhaseAttack_GetDamageSinceUpdate_maybe
    float GetStartTime() override { return m_unk28; }   // vt+0x7c 0x004bab00 CKGolemPhaseAttack_vf7C
    float GetMarkedTime() override { return m_unk2c; }  // vt+0x80 0x004bab08 CKGolemPhaseAttack_GetMarkedTime_maybe
    void MarkTime() override;                           // vt+0x84 0x004bb930 CKGolemPhaseAttack_MarkTime_maybe
    // vt+0x88 0x004bb3c0 CKGolemPhaseAttack_GetCurrentStep: the current step, null past the count.
    virtual Step* GetCurrentStep() {
        return m_unk14 < m_steps.m_ui32NbUsedElt ? m_steps.m_pBlock[m_unk14] : nullptr;
    }
    // 0x004bbe48 CKGolemPhaseAttack_FreeAttackLists_maybe (the Destroy's body)
    void FreeAttackLists();

    TVector<Step*, 1> m_steps;  // +0x08
    uint32_t m_unk14;           // +0x14 the current step (PostLoad / Stop / ResetPhases: -1)
    uint32_t m_unk18;           // +0x18 read first: the first step (Start)
    int32_t m_unk1c;            // +0x1c the golem's total damage at the start (vt+0x70 marks it again)
    int32_t m_unk20;            // +0x20 the golem's total damage at the start
    int32_t m_unk24;            // +0x24 the golem's damage since its mark (each Update)
    float m_unk28;              // +0x28 the clock's time at the start
    float m_unk2c;              // +0x2c the clock's time at the start (vt+0x84 marks it again)
};
DOTD_ASSERT_SIZE(CKGolemPhaseAttack, 0x30);
DOTD_ASSERT_SIZE(CKGolemPhaseAttack::Step, 0x1c);
DOTD_ASSERT_OFFSET(CKGolemPhaseAttack, m_steps, 0x08);
DOTD_ASSERT_OFFSET(CKGolemPhaseAttack, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKGolemPhaseAttack, m_unk2c, 0x2c);
