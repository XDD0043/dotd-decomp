// CKInputBlockStickCircleAction.cpp - reconstructed original translation unit 0x20be68-0x20ccf0 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKInputBlockStickCircleAction  key 0x7b8c  category Logic  size 0x64  vtable 0xb1f580
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x20be68  CKInputBlockStickCircleAction_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x20beb8  RegisterCKInputBlockStickCircleActionClass
//   [ ] 0x20bf40  _GLOBAL__D_20bf40
//   [ ] 0x20bf50  _GLOBAL__I_20bf50
//   [x] 0x20bf60  CKInputBlockStickCircleAction_OnActivate_maybe
//   [ ] 0x20bf98  CKInputBlockStickCircleAction_Save
//   [x] 0x20bfc0  CKInputBlockStickCircleAction_RecursiveRegistration  (KBase608C's vf24 0x20ced0: KBase628C's)
//   [x] 0x20bfe8  CKInputBlockStickCircleAction_Destroy  (KBase608C's Destroy 0x20cef8 (KBase608C.h))
//   [x] 0x20c010  CKInputBlockStickCircleAction_DeletingDestructor  (the destructor; delete)
//   [x] 0x20c058  CKInputBlockStickCircleAction_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x20c088  CKInputBlockStickCircleAction_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x20c0b8  CKInputBlockStickCircleAction_Construct  (header)
//   [x] 0x20c0f0  CKInputBlockStickCircleAction_Construct_2  (the same as 0x20c0b8 CKInputBlockStickCircleAction_Construct)
//   [x] 0x20c128  CKInputBlockStickCircleAction_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20c1c8  CKInputBlockStickCircleAction_Load
//   [x] 0x20c2f8  CKInputBlockStickCircleAction_TrackQuadrant_maybe
//   [x] 0x20c6d8  CKInputBlockStickCircleAction_vfC4
//   [x] 0x20c788  CKInputBlockStickCircleAction_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20c838  CKInputBlockStickCircleAction_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20c890  CKInputBlockStickCircleAction_vf58
//
//   [x] 0x9b1ad8  CKInputBlockStickCircleAction_IsKindOfClass  [inline]  (header)
//   [ ] 0x9b1b20  CKInputBlockStickCircleAction_GetClassType  [inline]
//   [ ] 0x9b1b28  CKInputBlockStickCircleAction_GetClassID  [inline]
#include "k2000/logic/input/CKInputBlockStickCircleAction.h"

#include "k2000/io/IKFile.h"

// 0x0020c1c8 CKInputBlockStickCircleAction_Load
int32_t CKInputBlockStickCircleAction::Load(IKFile* file, int32_t type) {
    KBase608C::Load(file, type);  // 0x0020d5f0
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_i32Stick);
    ReadS32LE(file, &m_i32Direction);
    ReadRaw(file, &m_ui8Quarters, 1);
    return 1;
}

// 0x0020bf60 CKInputBlockStickCircleAction_OnActivate_maybe
void CKInputBlockStickCircleAction::OnActivate() {
    KBase608C::OnActivate();  // 0x0020cfb8
    m_i32Quadrant = 4;
}

// 0x0020c2f8 CKInputBlockStickCircleAction_TrackQuadrant_maybe
uint8_t CKInputBlockStickCircleAction::TrackQuadrant(int32_t quadrant) {
    // The stick direction (0..3 of the left stick, 4..7 of the right one); 0 for another stick value.
    auto pressed = [this](uint32_t direction) -> uint8_t {
        if (m_i32Stick == 0) return InputBlock_IsStickDirectionPressed(this, direction);  // 0x0020a158
        if (m_i32Stick == 1) return InputBlock_IsStickDirectionPressed(this, direction + 4);
        return 0;
    };
    uint32_t first;
    uint32_t second;
    switch (quadrant) {
    case 0: first = 0; second = 3; break;
    case 1: first = 0; second = 2; break;
    case 2: first = 1; second = 3; break;
    case 3: first = 1; second = 2; break;
    default: return 1;
    }
    if (pressed(first) == 0) return 1;
    if (pressed(second) == 0) return 1;
    const int32_t current = m_i32Quadrant;
    if (current == 4) {
        m_i32Quadrant = quadrant;
        return 1;
    }
    static const int32_t kForward[4] = {1, 3, 0, 2};   // the tracked quadrant a forward step comes from
    static const int32_t kBackward[4] = {2, 0, 3, 1};  // ... a backward step
    if (current == kForward[quadrant]) {
        if (m_i32Direction == 0) return 0;
        m_i32Quadrant = quadrant;
        m_i8Count = static_cast<int8_t>(m_i8Count - 1);
        return 1;
    }
    if (current == kBackward[quadrant]) {
        if (m_i32Direction == 1) return 0;
        m_i32Quadrant = quadrant;
        m_i8Count = static_cast<int8_t>(m_i8Count + 1);
        return 1;
    }
    return quadrant == current ? 1 : 0;
}

// 0x0020c6d8 CKInputBlockStickCircleAction_vfC4: the four quadrants in turn, stopping at the first wrong one.
uint8_t CKInputBlockStickCircleAction::VfC4() {
    if (TrackQuadrant(0) == 0) return 0;
    if (TrackQuadrant(1) == 0) return 0;
    if (TrackQuadrant(2) == 0) return 0;
    return TrackQuadrant(3) != 0 ? 1 : 0;
}

// 0x0020c890 CKInputBlockStickCircleAction_vf58: CKInputBlockSingleAction_vf58's machine with the turn count: state 1 ->
// 2 clears the count; state 2 succeeds once |count| reaches the quarters (no state 3); a stick off the circle fails.
void CKInputBlockStickCircleAction::Update(float dt) {
    m_fTime = m_fTime + dt;  // fadds
    m_ui8Flags = static_cast<uint8_t>(m_ui8Flags & 0x9fu);
    const int32_t state = m_i32State;
    if (state == 1) {
        if (!(m_fTime > m_fWindow)) {  // bgt fails
            if (VfC4() != 0) {  // vt+0xc4
                m_i32State = 2;
                m_fTime = 0.0f;
                m_i8Count = 0;
                Update(dt);  // vt+0x58
                return;
            }
            if (VfC8() == 0) return;  // vt+0xc8
        }
        Deactivate();  // vt+0x6c
        SignalResult(0);
        return;
    }
    if (state < 2) {
        if (state != 0) return;
        if (m_fTime <= m_fStartDelay) return;  // ble
        m_i32State = 1;
        m_fTime = 0.0f;
        Update(dt);
        return;
    }
    if (state == 2) {
        const int32_t count = m_i8Count;
        const int32_t magnitude = count < 0 ? -count : count;
        if (magnitude < static_cast<int32_t>(m_ui8Quarters)) {  // blt
            if (VfC4() != 0) {
                if (VfC8() == 0) return;
                Deactivate();
                SignalResult(0);
                return;
            }
            StoreProgress();
            Deactivate();
            SignalResult(0);
            return;
        }
        StoreProgress();  // TOC -0xe78: 100.0
        if (m_fEndDelay != 0.0f) {  // TOC -0xe74: 0.0
            m_fTime = 0.0f;
            m_i32State = 4;
        } else {
            Deactivate();
        }
        SignalResult(1);
        return;
    }
    if (state != 4) return;
    if (!(m_fTime >= m_fEndDelay)) return;  // cror gt|eq + bne
    Deactivate();
    SignalResult(0);
}
