// IKEvaluator.h - the abstract trigger condition (key 0x228c, vtable 0xb209f0; XXL2:
// K/KServices/KServiceTrigger/IKEvaluator.h, bases IKUObjectInfos and CSBaseNode<IKEvaluator*>).
// Original unit: CKConditionNode.cpp (0x235030-0x235188; Ghidra names its Load CKConditionNode_Load).
// The registered evaluators are CKComparator and CKCombiner; a CKCombiner chains its evaluators
// through m_pNext while it loads.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKEvaluator : public IKSerializable {
public:
    IKEvaluator() { m_pNext = nullptr; }  // inlined in the Creates (CKComparator_Create): +4 = 0
    ~IKEvaluator() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00235090 CKConditionNode_Load
    // vt+0x24 0x00235030 IKEvaluator_RecursiveRegistration (CKConditionNode.cpp's unit; Ghidra's other name
    // IKEvaluator_LevelReset): for type 0 the evaluator registers itself with the saving manager (vt+0x24, no owner).
    void RecursiveRegistration(int32_t type) override;

    // The evaluators' runtime slots (vtable 0xb209f0 holds the pure stub 0x9873c8 in all of them). XXL2: +0x50
    // TriggerOccured, +0x54 Evaluate, +0x58 Start, +0x5c Stop, +0x64 Asleep; +0x60 and +0x68 are DotD's: the trigger
    // domains call 0x60 when they reset their triggers and 0x64 / 0x68 when they are enabled / disabled.
    virtual void Vf50() {}   // vt+0x50 TriggerOccured: CKComparator 0x234f78, CKCombiner 0x2341f0 (called after the trigger fired)
    virtual bool Vf54() { return false; }  // vt+0x54 Evaluate: CKComparator 0x234ff8, CKCombiner 0x234508
    virtual void Start() {}  // vt+0x58 0x2343f8 CKCombiner_ClearFiredEvents_maybe / 0x234d30 CKComparator's
    virtual void Vf5C() {}   // vt+0x5c Stop: CKComparator 0x234db0, CKCombiner 0x234390
    virtual void Vf60() {}   // vt+0x60 CKComparator 0x2348a0 (empty), CKCombiner 0x234328
    virtual void Asleep() {} // vt+0x64 0x2342c0 / 0x234e30
    virtual void Vf68() {}   // vt+0x68 0x234258 / 0x2348a8 (empty in the comparator)

    IKEvaluator* m_pNext;  // +0x04 XXL2 CSBaseNode<IKEvaluator*>::m_pNext (CKCombiner's list)
    uint32_t m_ba32Flags;   // +0x08 XXL2 CBitArray m_ba32Flags; not set by the constructor
};
DOTD_ASSERT_SIZE(IKEvaluator, 0xc);
DOTD_ASSERT_OFFSET(IKEvaluator, m_pNext, 0x04);
DOTD_ASSERT_OFFSET(IKEvaluator, m_ba32Flags, 0x08);
