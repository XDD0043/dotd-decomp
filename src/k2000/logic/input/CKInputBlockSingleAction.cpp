// CKInputBlockSingleAction.cpp - reconstructed original translation unit 0x20afe0-0x20be68 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKInputBlockSingleAction  key 0x7b0c  category Logic  size 0x5c  vtable 0xb1f4a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x20afe0  CKInputBlockSingleAction_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x20b030  RegisterCKInputBlockSingleActionClass
//   [ ] 0x20b0b8  _GLOBAL__D_20b0b8
//   [ ] 0x20b0c8  _GLOBAL__I_20b0c8
//   [x] 0x20b0d8  CKInputBlockSingleAction_vfC4
//   [x] 0x20b1a8  CKInputBlockSingleAction_vf84
//   [ ] 0x20b260  CKInputBlockSingleAction_Save
//   [x] 0x20b288  CKInputBlockSingleAction_RecursiveRegistration  (KBase608C's vf24 0x20ced0: KBase628C's)
//   [x] 0x20b2b0  CKInputBlockSingleAction_Destroy  (KBase608C's Destroy 0x20cef8 (KBase608C.h))
//   [x] 0x20b2d8  CKInputBlockSingleAction_DeletingDestructor  (the destructor; delete)
//   [x] 0x20b320  CKInputBlockSingleAction_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x20b350  CKInputBlockSingleAction_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x20b380  CKInputBlockSingleAction_Construct  (header)
//   [x] 0x20b3b8  CKInputBlockSingleAction_Construct_2  (the same as 0x20b380 CKInputBlockSingleAction_Construct)
//   [x] 0x20b3f0  CKInputBlockSingleAction_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20b490  CKInputBlockSingleAction_vfC8
//   [x] 0x20b610  CKInputBlockSingleAction_GetButtonGlyph_maybe
//   [x] 0x20b778  CKInputBlockSingleAction_Load
//   [x] 0x20b888  CKInputBlockSingleAction_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20b938  CKInputBlockSingleAction_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20b990  CKInputBlockSingleAction_vf58
//
//   [x] 0x9b1a30  CKInputBlockSingleAction_IsKindOfClass  [inline]  (header)
//   [ ] 0x9b1a78  CKInputBlockSingleAction_GetClassType  [inline]
//   [ ] 0x9b1a80  CKInputBlockSingleAction_GetClassID  [inline]
//   [ ] 0x9b1a88  CKInputBlockSingleAction_vfA4  [inline]
//   [ ] 0x9b1a90  CKInputBlockSingleAction_vfA8  [inline]
//   [ ] 0x9b1a98  CKInputBlockSingleAction_vfA0  [inline]
//   [ ] 0x9b1ab8  CKInputBlockSingleAction_vf9C  [inline]
#include "k2000/logic/input/CKInputBlockSingleAction.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

namespace {
// Local copy of 0x000107d8 Str_HashXor4 (misc/Wcs.cpp, not ported yet; CKInput.cpp, CLocManager.cpp keep the same copy):
// the bytes XORed into four accumulators in turn, returned as a little-endian word.
uint32_t Str_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) | (static_cast<uint32_t>(acc[2]) << 16) |
           (static_cast<uint32_t>(acc[3]) << 24);
}
}  // namespace

// 0x0020b778 CKInputBlockSingleAction_Load
int32_t CKInputBlockSingleAction::Load(IKFile* file, int32_t type) {
    KBase608C::Load(file, type);  // 0x0020d5f0
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_i32Action);
    ReadRaw(file, &m_ui8Min, 1);
    ReadRaw(file, &m_ui8Max, 1);
    return 1;
}

// 0x0020b0d8 CKInputBlockSingleAction_vfC4. The value test (flag bit 3) is fcmpu + ble to the return 0: a NaN value does not count.
uint8_t CKInputBlockSingleAction::VfC4() {
    const uint8_t state = InputBlock_IsActionPressed(this, Action());  // 0x00209a90
    if (InBounds(state)) return 1;
    if ((m_ui8Flags & 8) == 0) return 0;
    return InputBlock_GetActionValue(this, Action()) > 0.0f ? 1 : 0;  // 0x0020a108; TOC -0xecc
}

// 0x0020b1a8 CKInputBlockSingleAction_vf84: vfC4 without the flag test.
uint8_t CKInputBlockSingleAction::Vf84() {
    const uint8_t state = InputBlock_IsActionPressed(this, Action());
    if (InBounds(state)) return 1;
    return InputBlock_GetActionValue(this, Action()) > 0.0f ? 1 : 0;
}

// 0x0020b490 CKInputBlockSingleAction_vfC8. The action count is asked again before each action; the block's own action
// (+0x54 compared as a word) is skipped; a negative filtered state or a value above 0 (fcmpu + ble to the skip: a NaN does not count) is wrong.
uint8_t CKInputBlockSingleAction::VfC8() {
    if ((m_ui8Flags & 4) == 0) return KBase608C::VfC8();  // 0x0020cd40
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    for (uint32_t i = 0;; i = (i + 1) & 0xffu) {
        if (!(i < manager->GetActionCount())) return 0;  // vt+0x16c
        if (m_i32Action == static_cast<int32_t>(i)) continue;
        const uint8_t action = static_cast<uint8_t>(i);
        if (static_cast<int8_t>(InputBlock_IsActionPressed(this, action)) < 0) return 1;
        if (InputBlock_GetActionValue(this, action) > 0.0f) return 1;
    }
}

// 0x0020b610 CKInputBlockSingleAction_GetButtonGlyph_maybe
int32_t CKInputBlockSingleAction::GetButtonGlyph() {
    const uint32_t own = static_cast<uint32_t>(KBase608C::GetButtonGlyph()) & 0xffffu;  // 0x0020ce40
    if (own != 0x3f) return static_cast<int32_t>(own);
    if (m_i32Action == -1) return 0x3f;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    const char* project = manager->GetInputProjectName();  // vt+0x14c
    if (project == nullptr) return 0x3f;
    const uint8_t player = m_unk0f;
    CKInput* input = g_pEngine->m_input;
    const uint32_t hash = Str_HashXor4(project);  // 0x000107d8
    const uint32_t action = g_pEngine->m_gameManager->GetIconAction(player, hash, 0, static_cast<uint32_t>(m_i32Action));  // vt+0x174
    return static_cast<int32_t>(input->GetActionButtonGlyph(hash, 0, action, 0, 0) & 0xffffu);  // 0x00109ee8
}

// 0x0020b990 CKInputBlockSingleAction_vf58: the timer advances and the pulses (flag bits 5 / 6) clear; 0 waits the start
// delay; 1 waits for the action within the window (a wrong input or the window's end fails); 2 holds it for the hold
// time (released early: failed; held: the percentage, then with flag bit 4 state 3 waits for the release); 4 waits the
// end delay. A success signals output 0, a failure (and the end delay's end) output 1; both deactivate the block.
void CKInputBlockSingleAction::Update(float dt) {
    m_fTime = m_fTime + dt;  // fadds
    m_ui8Flags = static_cast<uint8_t>(m_ui8Flags & 0x9fu);
    switch (static_cast<uint32_t>(m_i32State)) {
    case 0:
        if (m_fTime <= m_fStartDelay) return;  // ble
        m_i32State = 1;
        m_fTime = 0.0f;  // stw 0
        Update(dt);  // vt+0x58
        return;
    case 1:
        if (!(m_fTime > m_fWindow)) {  // bgt fails
            if (VfC4() != 0) {  // vt+0xc4
                m_i32State = 2;
                m_fTime = 0.0f;
                Update(dt);
                return;
            }
            if (VfC8() == 0) return;  // vt+0xc8
        }
        Deactivate();  // vt+0x6c
        SignalResult(0);
        return;
    case 2:
        if (!(m_fTime >= m_fHold)) {  // cror gt|eq + bne: a NaN goes here
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
        StoreProgress();
        if ((m_ui8Flags & 0x10) == 0) {
            m_i32State = 3;
            return;
        }
        if (m_fEndDelay == 0.0f) {
            Deactivate();
        } else {
            m_fTime = 0.0f;
            m_i32State = 4;
        }
        SignalResult(1);
        return;
    case 3:
        if (VfC4() != 0) return;
        if (m_fEndDelay == 0.0f) {
            Deactivate();
        } else {
            m_fTime = 0.0f;
            m_i32State = 4;
        }
        SignalResult(1);
        return;
    case 4:
        if (!(m_fTime >= m_fEndDelay)) return;  // cror gt|eq + bne
        Deactivate();
        SignalResult(0);
        return;
    default:
        return;
    }
}
