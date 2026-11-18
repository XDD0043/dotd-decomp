// CKInputBlockDoubleAction.cpp - reconstructed original translation unit: 0x20a208-0x20afe0 (GAME_TOC1, main_toc1), 20 functions, 19 live.
// Primary class: CKInputBlockDoubleAction  key 0x7e4c  category Logic  size 0x60  vtable 0xb1f3d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x20a208  CKInputBlockDoubleAction_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES; port-rest R07)
//   [ ] 0x20a258  RegisterCKInputBlockDoubleActionClass
//   [ ] 0x20a2e0  _GLOBAL__D_20a2e0
//   [ ] 0x20a2f0  _GLOBAL__I_20a2f0
//   [ ] 0x20a300  CKInputBlockDoubleAction_IsActionInRange_maybe  [dead]
//   [x] 0x20a408  CKInputBlockDoubleAction_vfC8  (VfC8; port-rest R07)
//   [ ] 0x20a590  CKInputBlockDoubleAction_Save
//   [x] 0x20a5b8  CKInputBlockDoubleAction_RecursiveRegistration  (KBase608C's (KBase628C's registration); port-rest R07)
//   [x] 0x20a5e0  CKInputBlockDoubleAction_Destroy  (KBase608C::Destroy (inherited); port-rest R07)
//   [x] 0x20a608  CKInputBlockDoubleAction_DeletingDestructor  (the destructor; delete; port-rest R07)
//   [x] 0x20a650  CKInputBlockDoubleAction_Destructor  (C++ destructor chain: vtable stores, KBase608C's; port-rest R07)
//   [x] 0x20a680  CKInputBlockDoubleAction_DestructBody  (C++ destructor chain: vtable stores, KBase608C's; port-rest R07)
//   [x] 0x20a6b0  CKInputBlockDoubleAction_Construct  (the constructor (header); port-rest R07)
//   [x] 0x20a6e8  CKInputBlockDoubleAction_Construct_2  (the same as 0x20a6b0 Construct; port-rest R07)
//   [x] 0x20a720  CKInputBlockDoubleAction_DeleteArray  (the DeleteArray factory: DOTD_DECLARE_FACTORIES; port-rest R07)
//   [x] 0x20a7c8  CKInputBlockDoubleAction_Load  (Load; port-rest R07)
//   [x] 0x20a8e8  CKInputBlockDoubleAction_CreateArray  (the CreateArray factory: DOTD_DECLARE_FACTORIES; port-rest R07)
//   [x] 0x20a9a0  CKInputBlockDoubleAction_Create  (the Create factory: DOTD_DECLARE_FACTORIES (the constructor inlined); port-rest R07)
//   [x] 0x20a9f8  CKInputBlockDoubleAction_vfC4  (VfC4; port-rest R07)
//   [x] 0x20ab08  CKInputBlockDoubleAction_vf58  (Update; port-rest R07)
//
//   [ ] 0x9b1940  CKInputBlockDoubleAction_IsKindOfClass  [inline]
//   [ ] 0x9b1988  CKInputBlockDoubleAction_GetClassType  [inline]
//   [ ] 0x9b1990  CKInputBlockDoubleAction_GetClassID  [inline]
//   [ ] 0x9b1998  CKInputBlockDoubleAction_vfA4  [inline]
//   [ ] 0x9b19a0  CKInputBlockDoubleAction_vfA8  [inline]
//   [ ] 0x9b19f0  CKInputBlockDoubleAction_vfA0  [inline]
//   [ ] 0x9b1a10  CKInputBlockDoubleAction_vf9C  [inline]
#include "k2000/logic/input/CKInputBlockDoubleAction.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"

// 0x0020a7c8 CKInputBlockDoubleAction_Load (the two words are one 8-byte read, each swapped: the same bytes)
int32_t CKInputBlockDoubleAction::Load(IKFile* file, int32_t type) {
    KBase608C::Load(file, type);  // 0x0020d5f0
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_i32Action1);
    ReadS32LE(file, &m_i32Action2);
    ReadRaw(file, &m_ui8Min, 1);
    ReadRaw(file, &m_ui8Max, 1);
    return 1;
}

bool CKInputBlockDoubleAction::ActionHeld(uint8_t action) {
    const uint8_t state = InputBlock_IsActionPressed(this, action);  // 0x00209a90
    if (!(m_ui8Min > state) && !(m_ui8Max < state)) return true;     // cmplw / bgt, cmplw / bge
    if ((m_ui8Flags & 8) == 0) return false;
    return InputBlock_GetActionValue(this, action) > 0.0f;  // 0x0020a108; TOC -0xf10 0.0, fcmpu / ble
}

// 0x0020a9f8 CKInputBlockDoubleAction_vfC4
uint8_t CKInputBlockDoubleAction::VfC4() {
    if (!ActionHeld(Action1())) return 0;
    return ActionHeld(Action2()) ? 1 : 0;
}

// 0x0020a408 CKInputBlockDoubleAction_vfC8. The action count is asked again before each action; an action is wrong when
// pressed (a negative filtered state) or above 0 (fcmpu + ble back to the loop: a NaN is not), unless both block actions
// (+0x54 compared as a word with the index, +0x58 with +0x54) are that action.
uint8_t CKInputBlockDoubleAction::VfC8() {
    if ((m_ui8Flags & 4) == 0) return KBase608C::VfC8();  // 0x0020cd40
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    for (uint32_t i = 0;; i = (i + 1) & 0xffu) {
        if (!(i < manager->GetActionCount())) return 0;  // vt+0x16c
        const uint8_t action = static_cast<uint8_t>(i);
        if (!(static_cast<int8_t>(InputBlock_IsActionPressed(this, action)) < 0) &&
            !(InputBlock_GetActionValue(this, action) > 0.0f)) {
            continue;
        }
        if (m_i32Action1 == static_cast<int32_t>(i) && m_i32Action2 == m_i32Action1) continue;
        return 1;
    }
}

// 0x0020ab08 CKInputBlockDoubleAction_vf58: CKInputBlockSingleAction_vf58's code (the timer advances and the pulses clear;
// 0 the start delay, 1 the window, 2 the hold, 3 waits for the release, 4 the end delay; a success signals output 0, a
// failure output 1, both deactivate the block).
void CKInputBlockDoubleAction::Update(float dt) {
    m_fTime = m_fTime + dt;  // fadds
    m_ui8Flags = static_cast<uint8_t>(m_ui8Flags & 0x9fu);
    switch (static_cast<uint32_t>(m_i32State)) {  // jump table 0x20ab7c
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
            StoreProgress();  // TOC -0xef4 100.0
            Deactivate();
            SignalResult(0);
            return;
        }
        StoreProgress();
        if ((m_ui8Flags & 0x10) == 0) {
            m_i32State = 3;
            return;
        }
        if (m_fEndDelay == 0.0f) {  // fcmpu / bne
            Deactivate();
        } else {
            m_fTime = 0.0f;  // stfs of the TOC 0.0
            m_i32State = 4;
        }
        SignalResult(1);
        return;
    case 3:
        if (VfC4() != 0) return;
        if (m_fEndDelay == 0.0f) {  // fcmpu / beq
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
