// CKInputBlockStickCircleAction.h - an input block waiting for stick turns (key 0x7b8c, vtable 0xb1f580, size 0x64): the
// stick (+0x54: 0 the left one, directions 0..3; 1 the right one, 4..7) goes round its four diagonal quadrants; each step
// to the next quadrant counts one turn quarter in the allowed direction (+0x58), until |count| reaches +0x60. Original
// unit: CKInputBlockStickCircleAction.cpp (0x20be68-0x20cd40; its _2 unit holds KBase608C's vfC8). Base: KBase608C. No game
// file holds one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase608C.h"

class CKInputBlockStickCircleAction : public KBase608C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1ee)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1ad8
        return key == 0x7b8c || key == 0x608c || key == 0x628c || key == 0x60cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKInputBlockStickCircleAction)

    CKInputBlockStickCircleAction() {}  // 0x0020c0b8 CKInputBlockStickCircleAction_Construct: KBase608C's, the vtable
    ~CKInputBlockStickCircleAction() override {}

    // vt+0x2c 0x0020c1c8 CKInputBlockStickCircleAction_Load: KBase608C's, then (level data only) the stick, the turn
    // direction (words) and the quarter count (a byte).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x50 0x0020bf60 CKInputBlockStickCircleAction_OnActivate_maybe: KBase608C's, no quadrant yet (4).
    void OnActivate() override;
    // vt+0x58 0x0020c890 CKInputBlockStickCircleAction_vf58: the state machine (see the definition).
    void Update(float dt) override;
    uint8_t Vf84() override { return 0; }  // vt+0x84 0x009b1750 KStub_Return0_9b1750 (KBase628C's)
    // vt+0xc4 0x0020c6d8 CKInputBlockStickCircleAction_vfC4: TrackQuadrant of the four quadrants in turn, all not wrong.
    uint8_t VfC4() override;
    // vt+0xc8 0x0020cd40: KBase608C's (KBase608C.h). vt+0x24 0x0020bfc0 / vt+0x10 0x0020bfe8: KBase608C's.

    // 0x0020c2f8 CKInputBlockStickCircleAction_TrackQuadrant_maybe: the stick in diagonal quadrant `quadrant` (0: dirs 0 and
    // 3, 1: 0 and 2, 2: 1 and 3, 3: 1 and 2) moves the tracked quadrant (+0x5c) one step: forward (the quadrant after
    // the tracked one) counts -1 unless the direction (+0x58) is 0, backward (the one before) +1 unless it is 1; 0 for a
    // step the direction forbids. Not held there, the first quadrant, a step forward / backward or the same quadrant: 1;
    // the opposite quadrant: 0.
    uint8_t TrackQuadrant(int32_t quadrant);

    int32_t m_i32Stick;      // +0x54 0 the left stick, 1 the right one
    int32_t m_i32Direction;  // +0x58 0 only backward steps count, 1 only forward ones, else both
    int32_t m_i32Quadrant;   // +0x5c the tracked quadrant (4: none; OnActivate)
    uint8_t m_ui8Quarters;   // +0x60 the quarter steps to reach (|+0x61|)
    int8_t m_i8Count;        // +0x61 the signed step count (state 1 -> 2 clears it)
    uint8_t m_pad62[2];
};
static_assert(CKInputBlockStickCircleAction::kClassKey == 0x7b8c, "key");
DOTD_ASSERT_SIZE(CKInputBlockStickCircleAction, 0x64);
DOTD_ASSERT_OFFSET(CKInputBlockStickCircleAction, m_i32Stick, 0x54);
DOTD_ASSERT_OFFSET(CKInputBlockStickCircleAction, m_ui8Quarters, 0x60);
DOTD_ASSERT_OFFSET(CKInputBlockStickCircleAction, m_i8Count, 0x61);
