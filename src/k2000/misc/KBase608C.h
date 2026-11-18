// KBase608C.h - the action input blocks' unregistered base (key 0x608c, vtable 0xb1f658, size 0x54; Ghidra
// CKInputBlockAction_608c_maybe_* / KBase608C_*). Original unit: CKInputBlockAction.cpp (0x20cea8-0x20da38, k2000/input).
// Base: KBase628C. Its classes are CKInputBlockSingleAction, CKInputBlockDoubleAction and CKInputBlockStickCircleAction,
// none in a game file (outputs/remake/kp3-class-usage.json). Names ours.
//
// C2.8 port-all P06 wrote this header for its two action blocks (their constructor, Load, Destroy and slots need it); the
// bodies are inline here and CKInputBlockAction.cpp's checklist (P21's file) is left as it was: Construct 0x20cf58,
// Load 0x20d5f0, Destroy 0x20cef8, BaseDestructor 0x20d2e0 (the destructor), vf24 0x20ced0 / vf28 0x20cea8 (KBase628C's),
// OnActivate 0x20cfb8, OnDeactivate 0x20d450, vf90 0x20ce40 (GetButtonGlyph), vf7C 0x9b19a8 / vf88 0x9b18e0 / vfBC
// 0x9b19c8, and vfC8 0x20cd40 (Ghidra CKInputBlockStickCircleAction_vfC8, unit CKInputBlockStickCircleAction_2.cpp: the
// base's, StickCircleAction keeps it). Not declared: vt+0x5c / +0x60 (CollectAnchors 0x20d108, vf60 0x20d088) and the
// KBase628C slots vt+0x70..+0xc0 KBase628C.h does not declare (vf74 / vf78 / vf80 / vf8C / vf94 / vf98 / vfAC..vfB8 /
// vfC0: the button / step setters and getters, +0x1c / +0x20 / +0x34..+0x40 / flag bits).
#pragma once
#include <cstdint>

#include "crt/ppc_ops.h"
#include "k2000/core/Layout.h"
#include "k2000/input/KBase628C.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKOutputAnchor.h"
#include "k2000/logic/input/CKInputBlockSequential.h"
#include "k2000/logic/input/InputBlockQueries.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

class KBase608C : public KBase628C {
public:
    // 0x0020cf58 CKInputBlockAction_608c_maybe_Construct: the base, the vtable, the word vector empty (capacity 1).
    KBase608C() {
        m_vActions.m_pBlock = nullptr;
        m_vActions.m_ui32NbElt = 1;
        m_vActions.m_ui32NbUsedElt = 0;
    }
    // 0x0020d2e0 CKInputBlockAction_608c_maybe_BaseDestructor: the word block freed and cleared, then the base's.
    ~KBase608C() override {
        if (m_vActions.m_pBlock != nullptr) Mem_FreeAligned16(m_vActions.m_pBlock);
        m_vActions.m_ui32NbUsedElt = 0;
        m_vActions.m_pBlock = nullptr;
    }

    // vt+0x2c 0x0020d5f0 CKInputBlockAction_608c_maybe_Load: the base's, then (level data only) the state 5, the button
    // and the step index, the timer 0, the flag byte, the action words (one Read, then each swapped), four durations,
    // the progress 0, two output anchors (one contiguous read) and flag bits 5 / 6 cleared.
    int32_t Load(IKFile* file, int32_t type) override {
        KBase628C::Load(file, type);  // 0x00209b38
        if (type != K_LEVEL_PLATEFORMS) return 1;
        m_i32State = 5;
        ReadS32LE(file, &m_i32Button);
        ReadS32LE(file, &m_i32StepIndex);
        m_fTime = 0.0f;
        ReadRaw(file, &m_ui8Flags, 1);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        m_vActions.m_ui32NbElt = 1;
        m_vActions.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
        if (m_vActions.m_ui32NbElt < count) {
            uint32_t capacity = count + 1;
            if (capacity == 0) capacity = 1;
            m_vActions.m_pBlock = static_cast<uint32_t*>(Mem_ReallocAligned16(m_vActions.m_pBlock, capacity * 4));
            m_vActions.m_ui32NbElt = capacity;
        }
        m_vActions.m_ui32NbUsedElt = count;
        ReadU32LEWords(file, m_vActions.m_pBlock, count);
        ReadF32LE(file, &m_fStartDelay);
        ReadF32LE(file, &m_fWindow);
        ReadF32LE(file, &m_fHold);
        ReadF32LE(file, &m_fEndDelay);
        m_i32Progress = 0;
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apOutputs), 2);
        m_ui8Flags = static_cast<uint8_t>(m_ui8Flags & 0x9fu);
        return 1;
    }
    // vt+0x10 0x0020cef8 CKInputBlockAction_608c_maybe_Destroy: the base's (empty), the word block freed and cleared.
    void Destroy() override {
        KBase628C::Destroy();
        if (m_vActions.m_pBlock != nullptr) {
            Mem_FreeAligned16(m_vActions.m_pBlock);
            m_vActions.m_pBlock = nullptr;
        }
        m_vActions.m_ui32NbUsedElt = 0;
        m_vActions.m_pBlock = nullptr;
    }

    // vt+0x50 0x0020cfb8 KBase608C_OnActivate_maybe: KBase628C's (Activate); a block with a step index becomes the
    // compared block (+0x4c) of every parent sequence; the state and the timer 0, both outputs 0.
    void OnActivate() override {
        KBase628C::OnActivate();  // 0x00209a10
        if (m_i32StepIndex != -1) {
            for (IKSerializable* p = m_unk08; p != nullptr; p = static_cast<KBase60CC*>(p)->m_unk08) {
                static_cast<CKInputBlockSequential*>(p)->m_unk4c = this;
            }
        }
        m_i32State = 0;
        m_fTime = 0.0f;
        m_apOutputs[0]->SetValue(0);  // vt+0x58
        m_apOutputs[1]->SetValue(0);
    }
    // vt+0x54 0x0020d450 KBase608C_OnDeactivate_maybe: KBase628C's (Deactivate), the state 5, the timer 0, both outputs
    // 0, flag bits 5 / 6 cleared.
    void OnDeactivate() override {
        KBase628C::OnDeactivate();  // 0x00209a50
        m_i32State = 5;
        m_fTime = 0.0f;
        m_apOutputs[0]->SetValue(0);
        m_apOutputs[1]->SetValue(0);
        m_ui8Flags = static_cast<uint8_t>(m_ui8Flags & 0x9fu);
    }
    // vt+0x5c 0x0020d108 KBase608C_CollectAnchors_maybe (P21): KBase628C's two inputs, then the two outputs appended.
    void CollectAnchors(TVector<KBase610C*, 1>* out) override {
        KBase628C::CollectAnchors(out);  // 0x00209dd0
        KAnchor_PushBack(out, m_apOutputs[0]);
        KAnchor_PushBack(out, m_apOutputs[1]);
    }
    // vt+0x60 0x0020d088 KBase608C_vf60 (P21): KBase628C's (the inputs' links), then each output's links removed (vt+0x54).
    void DisconnectAnchors() override {
        KBase628C::DisconnectAnchors();  // 0x00209998
        m_apOutputs[0]->DisconnectAll();
        m_apOutputs[1]->DisconnectAll();
    }
    // vt+0x78 0x0020d350 KBase608C_vf78 (P21): the button = value; with a parent and `propagate` the parent sequence
    // recomputes its common button (CKInputBlockSequential_RecomputeCommonValue1C_maybe 0x205930).
    void SetCommonValue1C(int32_t value, int32_t propagate) override {
        m_i32Button = value;
        if (m_unk08 != nullptr && propagate != 0) static_cast<CKInputBlockSequential*>(m_unk08)->RecomputeCommonValue1C();
    }
    // vt+0x98 0x0020d3a0 KBase608C_vf98 (P21): the step index = value; with a parent and `propagate` the parent
    // recomputes its common step index (0x205b08).
    void SetStepIndex(int32_t value, int32_t propagate) override {
        m_i32StepIndex = value;
        if (m_unk08 != nullptr && propagate != 0) static_cast<CKInputBlockSequential*>(m_unk08)->RecomputeCommonValue20();
    }
    uint8_t Vf7C() override { return m_ui8Flags & 1; }          // vt+0x7c 0x009b19a8: flag bit 0
    uint8_t Vf88() override { return (m_ui8Flags >> 1) & 1; }   // vt+0x88 0x009b18e0: flag bit 1
    uint8_t VfBC() override { return (m_ui8Flags >> 5) & 1; }   // vt+0xbc 0x009b19c8: flag bit 5 (done this update)
    // vt+0x90 0x0020ce40 KBase608C_vf90: '?' without a button (-1), else the pad glyph 0xe800 + 2 x (button + the input's
    // KStub_Return44_105300: 0x2c).
    int32_t GetButtonGlyph() override {
        uint32_t glyph = 0x3f;
        if (m_i32Button != -1) glyph = (0x2cu * 2u + static_cast<uint32_t>(m_i32Button) * 2u - 0x1800u) & 0xffffu;
        return static_cast<int32_t>(glyph);
    }
    int32_t GetStepIndex() override { return m_i32StepIndex; }  // vt+0x94 0x009b1910

    // vt+0xc4 (pure in KBase608C): the block's action is done (Update moves to the hold state).
    virtual uint8_t VfC4() = 0;
    // vt+0xc8 0x0020cd40 (Ghidra CKInputBlockStickCircleAction_vfC8, unit CKInputBlockStickCircleAction_2.cpp): a wrong
    // input: any listed action (+0x28, -1 skipped, the low byte) pressed (a negative filtered state) or with a value
    // above 0.0 (TOC -0xe60; fcmpu + bgt: a NaN is not).
    virtual uint8_t VfC8() {
        for (uint32_t i = 0; i < m_vActions.m_ui32NbUsedElt;) {
            const uint32_t word = m_vActions.m_pBlock[i];
            ++i;
            if (word == 0xffffffffu) continue;
            const uint8_t action = static_cast<uint8_t>(word & 0xff);
            if (static_cast<int8_t>(InputBlock_IsActionPressed(this, action)) < 0) return 1;
            if (InputBlock_GetActionValue(this, action) > 0.0f) return 1;
        }
        return 0;
    }

    // The two update tails the action blocks share (CKInputBlockSingleAction_vf58 / StickCircleAction_vf58): output 0 to
    // `success`, output 1 to the opposite, with flag bit 5 (succeeded) or bit 6 (failed) set for this update.
    void SignalResult(uint8_t success) {
        m_apOutputs[0]->SetValue(success);  // vt+0x58
        m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xdfu) | (success != 0 ? 0x20u : 0u));
        m_apOutputs[1]->SetValue(success != 0 ? 0 : 1);
        m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xbfu) | (success != 0 ? 0u : 0x40u));
    }
    // The hold percentage both store: fctidz((time / hold) x 100.0f), the low word (TOC 100.0).
    void StoreProgress() {
        m_i32Progress = static_cast<int32_t>(ppc::fctidz((m_fTime / m_fHold) * 100.0f));
    }

    int32_t m_i32State;           // +0x18 0 start delay, 1 the window, 2 holding, 3 held, 4 end delay, 5 off (Load)
    int32_t m_i32Button;          // +0x1c the button of the glyph (-1 none; vt+0x74 / +0x78)
    int32_t m_i32StepIndex;       // +0x20 vt+0x94 / +0x98; -1 none
    float m_fTime;                // +0x24 the state's timer
    TVector<uint32_t, 1> m_vActions;  // +0x28 the wrong-input actions (vfC8; the low byte, -1 none)
    float m_fStartDelay;          // +0x34 state 0's length (vt+0xac)
    float m_fWindow;              // +0x38 state 1's length (vt+0xb0)
    float m_fHold;                // +0x3c state 2's length (vt+0xb4)
    float m_fEndDelay;            // +0x40 state 4's length (vt+0xb8); 0: no end delay
    int32_t m_i32Progress;        // +0x44 the hold percentage at its end (Load 0)
    CKOutputAnchor* m_apOutputs[2];  // +0x48 [0] succeeded, [1] failed (one contiguous read)
    // +0x50 read raw. Bit 0 vf7C, bit 1 vf88 / vf8C, bit 2 (SingleAction: any other action is wrong), bit 3
    // (SingleAction: a value above 0 counts), bit 4 (SingleAction: wait in state 3 for the release), bits 5 / 6 the
    // one-update success / failure pulses.
    uint8_t m_ui8Flags;
    uint8_t m_pad51[3];
};
DOTD_ASSERT_SIZE(KBase608C, 0x54);
DOTD_ASSERT_OFFSET(KBase608C, m_i32State, 0x18);
DOTD_ASSERT_OFFSET(KBase608C, m_vActions, 0x28);
DOTD_ASSERT_OFFSET(KBase608C, m_fStartDelay, 0x34);
DOTD_ASSERT_OFFSET(KBase608C, m_i32Progress, 0x44);
DOTD_ASSERT_OFFSET(KBase608C, m_apOutputs, 0x48);
DOTD_ASSERT_OFFSET(KBase608C, m_ui8Flags, 0x50);
