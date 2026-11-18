// CKColossusSequenceManager.h - the colossus' attack sequencer (key 0x7c4c, vtable 0xb27408, size 0x1c): a list of attack
// sequences run one after the other. Original unit: CKColossusSequenceManager.cpp (0x46b0c8-0x46bd08; Ghidra names the
// run-time methods ColossusAttackSequencer_*; CKHkColossus' Delete and a CKColossusAttackSequence accessor sit there
// too). CKHkColossus (+0x20) owns it: PostLoad makes the hook its owner, Start resets it, Update runs it, Stop stops the
// current sequence. No XXL2 class; names ours. No game file holds the class (C2.8 port-rest R06).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKColossusAttackSequenceBase;
class IKTime;

class CKColossusSequenceManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1f1)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7c4c || key == 0xc; }  // vt+0x08 0x9c4170
    DOTD_DECLARE_FACTORIES(CKColossusSequenceManager)

    // 0x0046b7d8 CKColossusSequenceManager_Create (0x46b720 CreateArray): an empty list with a capacity of 1 (no block).
    CKColossusSequenceManager();
    // 0x0046bc08 CKColossusSequenceManager_Destructor (0x46bb88 deleting): the block freed, the list emptied.
    ~CKColossusSequenceManager() override;

    void Destroy() override {}                                  // vt+0x10 0x0046b9e0 (empty)
    void RecursiveRegistration(int32_t /*type*/) override {}   // vt+0x24 0x0046b9d8 (returns 1, nothing)
    int32_t Load(IKFile* file, int32_t type) override;         // vt+0x2c 0x0046b830 CKColossusSequenceManager_Load
    int32_t PostLoad(int32_t type) override;                   // vt+0x30 0x0046b568 CKColossusSequenceManager_PostLoad

    // 0x0046b288 ColossusAttackSequencer_StopCurrent_maybe: the current sequence's stop (vt+0x54), when valid.
    void StopCurrent();
    // 0x0046b308 ColossusAttackSequencer_Reset_maybe: back to the first sequence, started (vt+0x50).
    void Reset();
    // 0x0046b368 ColossusAttackSequencer_Update_maybe: the current sequence advanced (vt+0x60) after moving on once it is
    // over (vt+0x64).
    void Update(IKTime* frameClock);
    // 0x0046b620 ColossusAttackSequencer_SwitchToSequence_maybe: another valid sequence started in place of the current
    // one.
    void SwitchToSequence(uint32_t index);

    IKSerializable* m_pOwner;                                // +0x04 the colossus hook (its PostLoad)
    TVector<CKColossusAttackSequenceBase*, 1> m_vSequences;  // +0x08 references (level files)
    int32_t m_i32Current;                                    // +0x14 the running sequence, -1 none; set by Reset
    uint32_t m_unk18;                                        // +0x18 not used by this unit
};
static_assert(CKColossusSequenceManager::kClassKey == 0x7c4c, "key");

class CKHkColossus;
class KBase7CCC;
// 0x0046bcc8 CKColossusAttackSequence_GetElementByIndex_maybe (this unit; its argument is the colossus hook, not a
// sequence): the colossus' attack element `index` (its +0x24 list), null for a negative index or one past the end.
// CKColossusAttackSequence's PostLoad looks its entries' elements up with it.
KBase7CCC* ColossusElementByIndex(CKHkColossus* colossus, int32_t index);
DOTD_ASSERT_SIZE(CKColossusSequenceManager, 0x1c);
DOTD_ASSERT_OFFSET(CKColossusSequenceManager, m_pOwner, 0x04);
DOTD_ASSERT_OFFSET(CKColossusSequenceManager, m_vSequences, 0x08);
DOTD_ASSERT_OFFSET(CKColossusSequenceManager, m_i32Current, 0x14);
