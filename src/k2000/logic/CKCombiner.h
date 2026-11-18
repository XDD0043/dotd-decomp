// CKCombiner.h - a trigger condition combining other evaluators (key 0x22cc, vtable 0xb20900, size 0x10).
// Original unit: CKCombiner.cpp. XXL2: K/KServices/KServiceTrigger/CKCombiner.h (m_lEvaluators, a
// CEvaluatorList: an intrusive list through IKEvaluator::m_pNext).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKEvaluator.h"

class CKCombiner : public IKEvaluator {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x8b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b7518
        return key == 0x22cc || key == 0x228c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCombiner)

    CKCombiner() { m_lEvaluators = nullptr; }  // inlined in 0x00234100 CKCombiner_Create
    ~CKCombiner() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00233e88 CKCombiner_Load
    // vt+0x24 0x00234150 CKCombiner_RecursiveRegistration: the base's (0x235030), then for type 0 each evaluator of the
    // list (vt+0x24 with 0). Returns the base's result.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x00234038 CKCombiner_Destroy: KStub_Nop_235180 (IKEvaluator's empty Destroy) only.
    void Vf60() override;    // vt+0x60 0x00234328 CKCombiner_vf60
    void Start() override;   // vt+0x58 0x002343f8 CKCombiner_ClearFiredEvents_maybe
    void Vf50() override;    // vt+0x50 0x002341f0 CKCombiner_vf50: Vf50 on each evaluator, in list order
    bool Vf54() override;    // vt+0x54 0x00234508 CKCombiner_Evaluate: the evaluators' results combined by flags bits 1-3
    void Vf5C() override;    // vt+0x5c 0x00234390 CKCombiner_ClearEventLatches_maybe: Vf5C on each evaluator
    void Asleep() override;  // vt+0x64 0x002342c0 CKCombiner_vf64
    void Vf68() override;    // vt+0x68 0x00234258 CKCombiner_vf68

    IKEvaluator* m_lEvaluators;  // +0x0c XXL2 m_lEvaluators: the list head (the last one read first)
};
DOTD_ASSERT_SIZE(CKCombiner, 0x10);
DOTD_ASSERT_OFFSET(CKCombiner, m_lEvaluators, 0x0c);
