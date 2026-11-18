// CKInputBlockSingleAction.h - an input block waiting for one action (key 0x7b0c, vtable 0xb1f4a8, size 0x5c): the action's
// filtered state in [min, max] (or, with flag bit 3, a value above 0) within the window, held for the hold time. Original
// unit: CKInputBlockSingleAction.cpp (0x20afe0-0x20be68). Base: KBase608C. No game file holds one
// (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase608C.h"

class CKInputBlockSingleAction : public KBase608C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1ec)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1a30
        return key == 0x7b0c || key == 0x608c || key == 0x628c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKInputBlockSingleAction)

    CKInputBlockSingleAction() {}  // 0x0020b380 CKInputBlockSingleAction_Construct: KBase608C's, then the vtable
    ~CKInputBlockSingleAction() override {}

    // vt+0x2c 0x0020b778 CKInputBlockSingleAction_Load: KBase608C's, then (level data only) the action word and the two
    // state bounds (bytes).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x58 0x0020b990 CKInputBlockSingleAction_vf58: the state machine (see the definition).
    void Update(float dt) override;
    // vt+0x84 0x0020b1a8 CKInputBlockSingleAction_vf84: the action in its bounds, or its value above 0.
    uint8_t Vf84() override;
    // vt+0x90 0x0020b610 CKInputBlockSingleAction_GetButtonGlyph_maybe: KBase608C's button glyph, else (with an action)
    // the glyph of the device button the game manager's input project (vt+0x14c, hashed) maps the action to.
    int32_t GetButtonGlyph() override;
    // vt+0xc4 0x0020b0d8 CKInputBlockSingleAction_vfC4: the action in its bounds, or (flag bit 3) its value above 0.
    uint8_t VfC4() override;
    // vt+0xc8 0x0020b490 CKInputBlockSingleAction_vfC8: with flag bit 2, any other action of the game manager (vt+0x16c
    // of them) pressed or above 0; else KBase608C's (the listed actions).
    uint8_t VfC8() override;
    // vt+0x24 0x0020b288 / vt+0x10 0x0020b2b0: KBase608C's (KBase628C's registration; the word block freed).

    // The action: the word's low byte (the PS3 reads +0x57).
    uint8_t Action() const { return static_cast<uint8_t>(m_i32Action & 0xff); }
    // vfC4 / vf84: the filtered state in [min, max] (unsigned bytes).
    bool InBounds(uint8_t state) const { return !(state < m_ui8Min) && !(m_ui8Max < state); }

    int32_t m_i32Action;  // +0x54 (-1: none; vt+0xa0..: not declared)
    uint8_t m_ui8Min;     // +0x58 read raw (vt+0xa4 0x9b1a88)
    uint8_t m_ui8Max;     // +0x59 read raw (vt+0xa8 0x9b1a90)
    uint8_t m_pad5a[2];
};
static_assert(CKInputBlockSingleAction::kClassKey == 0x7b0c, "key");
DOTD_ASSERT_SIZE(CKInputBlockSingleAction, 0x5c);
DOTD_ASSERT_OFFSET(CKInputBlockSingleAction, m_i32Action, 0x54);
DOTD_ASSERT_OFFSET(CKInputBlockSingleAction, m_ui8Min, 0x58);
