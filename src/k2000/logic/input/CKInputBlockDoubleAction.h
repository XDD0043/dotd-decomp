// CKInputBlockDoubleAction.h - an input block waiting for two actions at once (key 0x7e4c, vtable 0xb1f3d0, size 0x60):
// both actions' filtered states in [min, max] (or, with flag bit 3, their values above 0) within the window, held for the
// hold time. Original unit: CKInputBlockDoubleAction.cpp (0x20a208-0x20afe0). Base: KBase608C. No game file holds one
// (outputs/remake/kp3-class-usage.json). Names ours (C2.8 port-rest R07).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase608C.h"

class CKInputBlockDoubleAction : public KBase608C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1f9)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1940
        return key == 0x7e4c || key == 0x608c || key == 0x628c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKInputBlockDoubleAction)

    // 0x0020a6b0 CKInputBlockDoubleAction_Construct (= 0x20a6e8 Construct_2; inlined in 0x20a9a0 Create): KBase608C's,
    // then the vtable.
    CKInputBlockDoubleAction() {}
    // 0x0020a650 CKInputBlockDoubleAction_Destructor / 0x20a680 DestructBody (the vtable, then KBase608C's BaseDestructor
    // 0x20d2e0) / 0x20a608 DeletingDestructor (+ delete).
    ~CKInputBlockDoubleAction() override {}

    // vt+0x2c 0x0020a7c8 CKInputBlockDoubleAction_Load: KBase608C's, then (level data only) the two action words (one
    // 8-byte read, each swapped) and the two state bounds (bytes).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x58 0x0020ab08 CKInputBlockDoubleAction_vf58: the state machine (CKInputBlockSingleAction's, the same code).
    void Update(float dt) override;
    // vt+0xc4 0x0020a9f8 CKInputBlockDoubleAction_vfC4: both actions in their bounds, or (flag bit 3) above 0.
    uint8_t VfC4() override;
    // vt+0xc8 0x0020a408 CKInputBlockDoubleAction_vfC8: with flag bit 2, any action of the game manager (vt+0x16c of
    // them) pressed or above 0, except when both block actions are that action; else KBase608C's (the listed actions).
    uint8_t VfC8() override;
    // vt+0x24 0x0020a5b8 RecursiveRegistration / vt+0x10 0x0020a5e0 Destroy: KBase608C's (KBase628C's registration; the
    // word block freed). vt+0x84: KStub_Return0_9b1750 (KBase628C's). vt+0x90: KBase608C's button glyph.

    // The actions: the words' low bytes (the PS3 reads +0x57 / +0x5b).
    uint8_t Action1() const { return static_cast<uint8_t>(m_i32Action1 & 0xff); }
    uint8_t Action2() const { return static_cast<uint8_t>(m_i32Action2 & 0xff); }
    // vfC4: one action held: its filtered state in [min, max] (unsigned bytes), or with flag bit 3 its value above 0
    // (fcmpu + ble to the failure: a NaN is not above).
    bool ActionHeld(uint8_t action);

    int32_t m_i32Action1;  // +0x54 (vt+0x9c..+0xa8 0x9b1a10.. not declared)
    int32_t m_i32Action2;  // +0x58
    uint8_t m_ui8Min;      // +0x5c read raw
    uint8_t m_ui8Max;      // +0x5d read raw
    uint8_t m_pad5e[2];
};
static_assert(CKInputBlockDoubleAction::kClassKey == 0x7e4c, "key");
DOTD_ASSERT_SIZE(CKInputBlockDoubleAction, 0x60);
DOTD_ASSERT_OFFSET(CKInputBlockDoubleAction, m_i32Action1, 0x54);
DOTD_ASSERT_OFFSET(CKInputBlockDoubleAction, m_i32Action2, 0x58);
DOTD_ASSERT_OFFSET(CKInputBlockDoubleAction, m_ui8Min, 0x5c);
DOTD_ASSERT_OFFSET(CKInputBlockDoubleAction, m_ui8Max, 0x5d);
