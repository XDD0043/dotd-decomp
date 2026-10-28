// CKInputBlockSequential.h - (key 0x624c, vtable 0xb1f230, size 0x8c). Original unit:
// CKInputBlockSequential.cpp. No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/input/KBase628C.h"
#include "k2000/util/TVector.h"

class CKInputAnchor;
class CKOutputAnchor;

class CKInputBlockSequential : public KBase628C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x189)
    DOTD_DECLARE_FACTORIES(CKInputBlockSequential)

    CKInputBlockSequential();  // 0x00205f58 CKInputBlockSequential_Construct
    ~CKInputBlockSequential() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00208268 CKInputBlockSequential_Load

    // vt+0x50 0x00206eb0 CKInputBlockSequential_OnActivate: Activate, the block made current up its parent
    // chain, state 0 with the timer and step count reset, all anchors cleared, output +0x70 pulsed.
    void OnActivate() override;
    // vt+0x54 0x00207158 CKInputBlockSequential_OnDeactivate: Deactivate, state 3, the active children
    // deactivated (their vt+0x54), the run state cleared, output +0x74 pulsed.
    void OnDeactivate() override;
    // vt+0x58 0x00208c68 CKInputBlockSequential_Update_maybe: the state machine (0 waits +0x5c seconds,
    // 1 runs the children and watches the actions of +0x2c, 2 waits +0x60 seconds).
    void Update(float dt) override;
    // vt+0x64 0x002088b0 CKInputBlockSequential_Evaluate: KBase628C_Evaluate (inlined), then the step inputs
    // +0x78 (step done) / +0x7c (abort).
    void Evaluate(uint8_t value) override;
    // vt+0x94 0x009b17c0 CKInputBlockSequential_vf94
    int32_t GetStepIndex() override { return m_unk20; }

    // 0x00205660 CKInputBlockSequential_ComputeStepCount_maybe: *count raised above the step index of every
    // KBase628C child in +0x38, recursively through the CKInputBlockSequential ones (flag passed on, unused).
    void ComputeStepCount(int32_t* count, uint8_t flag);
    // 0x00205ce0 CKInputBlockSequential_PushActiveChild_maybe: `child` pushed onto the +0x44 list.
    void PushActiveChild(KBase60CC* child);
    // 0x00205cf0 CKInputBlockSequential_RemoveActiveChild_maybe
    void RemoveActiveChild(KBase60CC* child);

    int32_t m_unk18;                    // +0x18 state: the Load sets 3; 0 start delay, 1 running, 2 end delay, 3 off
    int32_t m_unk1c;                    // +0x1c
    int32_t m_unk20;                    // +0x20 the step index (vt+0x94)
    int32_t m_unk24;                    // +0x24 read; OnActivate: the step count (ComputeStepCount)
    float m_unk28;                      // +0x28 the timer: the Load sets 0, Update adds dt
    TVector<uint32_t, 1> m_vUnk2c;      // +0x2c words (read, then each swapped): game-manager actions (low byte; -1 none)
    TVector<IKSerializable*, 1> m_vUnk38;  // +0x38 references: the child blocks
    KBase60CC* m_unk44;                 // +0x44 the active children (linked through +0x04); 0 (constructor and Load)
    uint32_t m_unk48;                   // +0x48 the Load sets 0
    KBase60CC* m_unk4c;                 // +0x4c a block whose step index Update compares; the Load sets 0
    KBase60CC* m_unk50;                 // +0x50 the current block (OnActivate of this block or of a child)
    KBase60CC* m_unk54;                 // +0x54 the top-level child that activated (OnActivate)
    float m_unk58;                      // +0x58
    float m_unk5c;                      // +0x5c state 0: seconds before the block runs
    float m_unk60;                      // +0x60 state 2: seconds before it completes (0: completes at once)
    float m_unk64;                      // +0x64 progress (the Load sets 0; Evaluate / Update add steps)
    float m_unk68;                      // +0x68 progress at OnActivate (restored on completion)
    float m_unk6c;                      // +0x6c the timer at the last step (Evaluate)
    CKOutputAnchor* m_apUnk70[2];       // +0x70 references (CKOutputAnchor in the samples)
    CKInputAnchor* m_apUnk78[2];        // +0x78 references (CKInputAnchor in the samples)
    CKOutputAnchor* m_apUnk80[2];       // +0x80 references (CKOutputAnchor in the samples)
    // +0x88 read raw. Bits 2 and 3 are one-update pulses (the Load and every Update clear them): bit 2 a
    // step done (Evaluate, input +0x78), bit 3 the block ended (completed by action or end delay, or aborted).
    uint8_t m_unk88;
    uint8_t m_pad89[3];
};
DOTD_ASSERT_SIZE(CKInputBlockSequential, 0x8c);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_vUnk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_vUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_apUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_apUnk78, 0x78);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_apUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKInputBlockSequential, m_unk88, 0x88);
