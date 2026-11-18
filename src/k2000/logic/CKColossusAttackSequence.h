// CKColossusAttackSequence.h - one attack sequence of the colossus (key 0x7c8c, vtable 0xb27558, size 0x68). Original
// unit: CKColossusAttackSequence.cpp (0x46cbe8-0x46faa0). Base: CKColossusAttackSequenceBase (0x7c0c). No XXL2 class;
// names ours. No game file holds one (work/level-class-keys.json): C2.8 port-final F03 ported it from the code.
//
// A sequence runs attack elements (KBase7CCC: CKColossusContextualAttackElement / CKColossusBaseAttackElement, found by
// index in the colossus hook's element list, CKHkColossus +0x24) in two lists:
// - the main list (+0x30): run one after the other; each entry's condition (on its element) moves on to the next one;
//   past the end the sequence loops (flag bit 2) or ends (index -1, flag bit 1);
// - the reaction list (+0x24): when the running main element has flag bit 2 (its +0x58 & 4) and an entry lists that
//   element and its condition (the hero beyond a radius) holds, that entry's element runs instead until its own
//   condition: then the next reaction entry (+0x10 set) or the main list again.
// A three-state machine (+0x44..+0x63; the PS3 keeps pointers to member functions to vt+0x7c / +0x80 / +0x84) picks the
// list: state 0 the main list (vt+0x7c), 1 the reaction list (vt+0x80), 2 idle (vt+0x84). The reaction list's hook
// (+0x14) with its bit 0x400 switches the manager to the next sequence. The sequence is over (vt+0x64 -> vt+0x6c) when
// its own condition (+0x18) holds.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKColossusAttackSequenceBase.h"
#include "k2000/util/TVector.h"

class IKHook;
class KBase7CCC;

class CKColossusAttackSequence : public CKColossusAttackSequenceBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1f2)  // vt+0x14 / +0x18 0x9c4228 / 0x9c4230
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4200
        return key == 0x7c8c || key == 0x7c0c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKColossusAttackSequence)

    // A condition block (operator new, zeroed by the Load). m_i32Type -1 = none; the sequence's own (+0x18, 0x10 bytes)
    // picks 0..6, an entry's (0x0c bytes) 0..3 (the main / reaction run) or 0..1 (the reaction switch). The functions
    // get the words after the type (the PS3 passes &block[1]).
    struct Condition {
        int32_t m_i32Type;  // +0x00
        int32_t m_i32Arg;   // +0x04 a count (type 2 of the sequence's: the colossus' +0x54 at most this)
        float m_fArg;       // +0x08 a time or a radius
        uint32_t m_unk0c;   // +0x0c (the 0x10 blocks only) read by the Load for +0x18, 0 for +0x1c; not used
    };
    // A main list entry (0x10 bytes).
    struct MainEntry {
        uint32_t m_ui32Element;     // +0x00 the element's index in the colossus' list (Load)
        KBase7CCC* m_pElement;      // +0x04 PostLoad: the element (null past the list)
        Condition* m_pCondition;    // +0x08 when the element is done (the main run, vt+0x7c)
        IKHook* m_pHook;            // +0x0c reference: given to the element (its +0x64) when it starts
    };
    // A reaction list entry (0x30 bytes).
    struct ReactionEntry {
        uint32_t m_ui32Element;                  // +0x00 the element's index (Load)
        KBase7CCC* m_pElement;                   // +0x04 PostLoad: the element
        Condition* m_pSwitchCondition;           // +0x08 when this entry takes over (TrySwitchToMatchingList24Entry)
        Condition* m_pEndCondition;              // +0x0c when this entry is done (the reaction run, vt+0x80)
        uint8_t m_ui8Chain;                      // +0x10 done: on to the next reaction entry (else back to the main list)
        uint8_t m_ui8Unk11;                      // +0x11 read by the Load; not used
        uint8_t m_pad12[2];
        IKHook* m_pHook;                         // +0x14 reference: given to the element; its bit 0x400 ends the sequence
        TVector<KBase7CCC*, 1> m_vFromElements;  // +0x18 PostLoad: the main elements this entry can interrupt
        TVector<uint32_t, 1> m_vFromIndices;     // +0x24 Load: their indices
    };

    // 0x0046dcd0 CKColossusAttackSequence_Create (= the dead-looking 0x46d3c8 / 0x46d448 _Construct copies, the same
    // stores): the base, both lists empty with a capacity of 1, no state (+0x48 / +0x49 0xff).
    CKColossusAttackSequence();
    // 0x0046dae0 CKColossusAttackSequence_Destructor (= 0x46db80 _DestructBody; 0x46dc20 _DeletingDestructor): both list
    // blocks freed and cleared (+0x30, then +0x24), then the base's.
    ~CKColossusAttackSequence() override;

    void Destroy() override;                                  // vt+0x10 0x0046d7d0
    // vt+0x24 0x0046d3a0: the base's (0x470470, nothing), 1.
    void RecursiveRegistration(int32_t type) override { CKColossusAttackSequenceBase::RecursiveRegistration(type); }
    int32_t Load(IKFile* file, int32_t type) override;        // vt+0x2c 0x0046eec8
    int32_t PostLoad(int32_t type) override;                  // vt+0x30 0x0046d598

    void Vf50() override;                                     // vt+0x50 0x0046e330 _StartAttack_maybe
    void Vf54() override;                                     // vt+0x54 0x0046de70
    void Vf60(IKTime* frameClock) override;                   // vt+0x60 0x0046ecb8
    uint8_t Vf64() override { return Vf6C(); }                // vt+0x64 0x0046d198: the end condition
    uint8_t Vf6C() override;                                  // vt+0x6c 0x0046d1e0
    void Vf70() override { m_ui32Flags = m_ui32Flags | 8u; }  // vt+0x70 0x0046d2e0
    void Vf74() override;                                     // vt+0x74 0x0046d9e0
    void Vf78() override { CKColossusAttackSequenceBase::Vf78(); }  // vt+0x78 0x0046d378
    // The three states (phase 0 every frame (returns the next state), 1 enter (`other` the previous state), 2 leave
    // (`other` the next state)).
    virtual uint8_t Vf7C(IKTime* frameClock, int32_t phase, uint8_t other);  // vt+0x7c 0x0046eab0: the main list
    virtual uint8_t Vf80(IKTime* frameClock, int32_t phase, uint8_t other);  // vt+0x80 0x0046e708: the reaction list
    // vt+0x84 0x0046d190: idle (the state it is given).
    virtual uint8_t Vf84(IKTime* /*frameClock*/, int32_t /*phase*/, uint8_t other) { return other; }

    // 0x0046dfc0 CKColossusAttackSequence_TrySwitchToMatchingList24Entry_maybe
    uint8_t TrySwitchToReaction();
    // 0x0046e508 CKColossusAttackSequence_AdvanceToNextList30Entry_maybe
    uint8_t AdvanceToNextMain();
    // The state machine's call (inlined): the table pair of `state` (a PS3 pointer to member function) on this.
    uint8_t CallState(uint8_t state, IKTime* frameClock, int32_t phase, uint8_t other);

    Condition* m_pEndCondition;                 // +0x18 the sequence's end (vt+0x6c)
    Condition* m_pUnk1C;                        // +0x1c read by the Load (three words); not used
    // +0x20 bit 0 stopped (vt+0x54), bit 1 the main list ran out (AdvanceToNextMain), bit 2 the main list loops
    // (Load), bit 3 vt+0x70; bit 1 also read by the Load (a byte).
    uint32_t m_ui32Flags;
    TVector<ReactionEntry*, 1> m_vReactions;    // +0x24
    TVector<MainEntry*, 1> m_vMain;             // +0x30
    int32_t m_i32Main;                          // +0x3c the running main entry (-1 none)
    int32_t m_i32Reaction;                      // +0x40 the running reaction entry (-1: the main one runs)
    uint32_t* m_pStateTable;                    // +0x44 Vf50: the table below
    uint8_t m_ui8State;                         // +0x48 the current state (0xff none)
    uint8_t m_ui8StateCount;                    // +0x49 Vf50: 3 (0xff before)
    uint8_t m_pad4a[2];
    // +0x4c the PS3 pointers to member functions (descriptor word, this-adjust word): {0x7d, 0}, {0x81, 0}, {0x85, 0}
    // (virtual: vt+0x7c / +0x80 / +0x84). Kept as the words; CallState dispatches them.
    uint32_t m_aStateTable[6];
    IKHook* m_pHook;                            // +0x64 reference: woken while the sequence runs (vt+0x50 / +0x54)
};
static_assert(CKColossusAttackSequence::kClassKey == 0x7c8c, "key");
DOTD_ASSERT_SIZE(CKColossusAttackSequence, 0x68);
DOTD_ASSERT_SIZE(CKColossusAttackSequence::Condition, 0x10);
DOTD_ASSERT_SIZE(CKColossusAttackSequence::MainEntry, 0x10);
DOTD_ASSERT_SIZE(CKColossusAttackSequence::ReactionEntry, 0x30);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence::ReactionEntry, m_pHook, 0x14);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence::ReactionEntry, m_vFromElements, 0x18);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence::ReactionEntry, m_vFromIndices, 0x24);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_pEndCondition, 0x18);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_ui32Flags, 0x20);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_vReactions, 0x24);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_vMain, 0x30);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_i32Main, 0x3c);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_i32Reaction, 0x40);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_pStateTable, 0x44);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_ui8State, 0x48);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_aStateTable, 0x4c);
DOTD_ASSERT_OFFSET(CKColossusAttackSequence, m_pHook, 0x64);
