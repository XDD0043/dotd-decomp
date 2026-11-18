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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1758
        return key == 0x624c || key == 0x628c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKInputBlockSequential)

    CKInputBlockSequential();  // 0x00205f58 CKInputBlockSequential_Construct (0x00205fc8 Construct_2: the same)
    // 0x002074d8 CKInputBlockSequential_Destructor (0x00207428 DeletingDestructor and 0x00207388 DestructBody: the
    // same): the child and action blocks freed.
    ~CKInputBlockSequential() override;

    // vt+0x24 0x00205e98 CKInputBlockSequential_RecursiveRegistration: the base's (0x209c68).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00208268 CKInputBlockSequential_Load
    void Destroy() override;                            // vt+0x10 0x00205ec0 CKInputBlockSequential_Destroy
    // vt+0x5c 0x00207c38 CKInputBlockSequential_CollectAnchors_maybe: the base's two, then +0x70..+0x84.
    void CollectAnchors(TVector<KBase610C*, 1>* out) override;
    // vt+0x60 0x00206aa8 CKInputBlockSequential_vf60: the base's, then the six anchors' links removed (vt+0x54).
    void DisconnectAnchors() override;
    // vt+0x70 0x002061c0 CKInputBlockSequential_vf70: +0x0f = value ^ 1, then passed on to every KBase628C child.
    void SetEnabled(uint8_t value) override;
    int32_t GetCommonValue1C() override { return m_unk1c; }  // vt+0x74 0x009b17a0
    // vt+0x78 0x00206970 CKInputBlockSequential_vf78: +0x1c set and passed on (children: propagate 0); with `propagate`
    // the parent recomputes its own (RecomputeCommonValue1C).
    void SetCommonValue1C(int32_t value, int32_t propagate) override;
    void SetBit0(uint8_t value) override;  // vt+0x80 0x00206398 CKInputBlockSequential_vf80: +0x88 bit 0, passed on
    void SetBit1(uint8_t value) override;  // vt+0x8c 0x00206d10 CKInputBlockSequential_vf8C: +0x88 bit 1, passed on
    // vt+0x98 0x00206838 CKInputBlockSequential_vf98: as vt+0x78 for the step index +0x20 (RecomputeCommonValue20).
    void SetStepIndex(int32_t value, int32_t propagate) override;
    void Vf9C(uint8_t value) override;  // vt+0x9c 0x002062b0: passed on to every KBase628C child
    void VfA0(uint8_t value) override;  // vt+0xa0 0x002060d8: passed on
    void VfA4(uint8_t value) override;  // vt+0xa4 0x00206750: passed on
    void VfA8(uint8_t value) override;  // vt+0xa8 0x00206668: passed on
    void SetStartDelay(float value) override { m_unk5c = value; }  // vt+0xac 0x009b17d0
    void VfB0(float value) override;    // vt+0xb0 0x00206580: passed on
    void VfB4(float value) override;    // vt+0xb4 0x00206498: passed on
    void SetEndDelay(float value) override { m_unk60 = value; }    // vt+0xb8 0x009b17d8
    // vt+0xc0 0x00206bc8 CKInputBlockSequential_vfC0: a top-level sequence asks its activating child (+0x54), else bit 3
    // of +0x88 (the block ended).
    uint8_t VfC0() override;

    // 0x00205930 CKInputBlockSequential_RecomputeCommonValue1C_maybe: +0x1c = the first CKInputBlockSequential child's
    // value other than -1 when all such children agree, else -1; up the parent chain while the value changes.
    void RecomputeCommonValue1C();
    // 0x00205b08 CKInputBlockSequential_RecomputeCommonValue20_maybe: the same for the step index +0x20 over the
    // KBase628C children.
    void RecomputeCommonValue20();
    // 0x00207578 CKInputBlockSequential_DetachChild_maybe: `child` deactivated when active (vt+0x6c), its anchors
    // unlinked (vt+0x60) and taken out of +0x38 (the last child moves into its slot; the block shrinks by one).
    void DetachChild(KBase60CC* child);
    // 0x002090c8 CKInputBlockSequential_RefreshButtonMaskUpward_maybe: +0x0c = the OR of the KBase628C children's,
    // up the parent chain while it differs from the parent's.
    void RefreshButtonMaskUpward();
    // 0x002096b8 InputBlock_AddChild_maybe (CKSrvInput_AttachBlock_maybe 0x202ff8 calls it): a KBase628C child gets its
    // deactivate input (+0x14) linked to output +0x74 (both sides; the input service's link count +1 when both link);
    // appended to +0x38; the button mask refreshed when the child's differs.
    void AddChild(KBase60CC* child);

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
    uint8_t Vf7C() override { return m_unk88 & 1; }         // vt+0x7c 0x009b17b0: bit 0 of +0x88
    uint8_t Vf88() override { return (m_unk88 >> 1) & 1; }  // vt+0x88 0x009b17e0: bit 1 of +0x88
    // vt+0x90 0x00205e08 CKInputBlockSequential_vf90: '?' without a button (+0x1c -1), else the pad glyph
    // 0xe800 + 2 x (0x2c + button).
    int32_t GetButtonGlyph() override;
    // vt+0x94 0x009b17c0 CKInputBlockSequential_vf94
    int32_t GetStepIndex() override { return m_unk20; }
    // vt+0xbc 0x00206c50 CKInputBlockSequential_vfBC: a top-level sequence (no parent) asks its activating child (+0x54),
    // else bit 2 of +0x88 (a step done).
    uint8_t VfBC() override;

    // 0x002052e0 CKInputBlockSequential_FindActionBlockById_maybe: the first child block (depth first) whose step index is
    // `id` and whose glyph is not '?' (the glyph into *glyph), or null.
    KBase628C* FindActionBlockById(int32_t id, uint16_t* glyph);
    // 0x002054b0 CKInputBlockSequential_GetActiveActionBlock_maybe: the current block (+0x50), else the compared block
    // (+0x4c), when it is active (+0x0e), with its glyph into *glyph; else null (*glyph unchanged).
    KBase60CC* GetActiveActionBlock(uint16_t* glyph);

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
    KBase60CC* m_unk48;                 // +0x48 the active position block (KBase620C OnActivate); the Load sets 0
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
