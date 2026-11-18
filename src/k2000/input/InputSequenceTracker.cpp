// InputSequenceTracker.cpp - reconstructed original translation unit 0x102010-0x102d70 (GAME_TOC1, main_toc1), 14 functions, 7 live.
// Primary owner: InputSequenceTracker (not a registered class)
// Other owners: InputSequenceStep (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x102010  InputSequenceTracker_Construct_2_maybe  [dead]
//   [x] 0x102030  InputSequenceTracker_Construct_maybe
//   [x] 0x102050  InputSequenceTracker_SetSequence_maybe
//   [x] 0x102068  KStub_Return1_102068  (CKComboManager::Shutdown, CKComboManager.h (CKInput::DestroyModule))
//   [x] 0x102070  InputSequenceTracker_SetEnabled_maybe
//   [ ] 0x102078  InputSequenceTracker_ResetAll_maybe  [dead]
//   [ ] 0x1020f8  InputSequenceTracker_ResetSequence_maybe  [dead]
//   [ ] 0x102138  InputSequenceTracker_SetAllSequencesEnabled_maybe  [dead]
//   [x] 0x1021d0  InputSequenceTracker_SetSequenceEnabled_maybe
//   [x] 0x102220  InputSequenceTracker_Update_maybe
//   [ ] 0x1026e0  InputSequenceTracker_SetSequenceBlocked_maybe  [dead]
//   [x] 0x102730  InputSequenceStep_Init_maybe
//   [ ] 0x102770  InputSequenceStep_Load_maybe  [dead]
//   [ ] 0x102ae0  InputSequenceStep_Save_maybe  [dead]
#include "k2000/input/CKComboManager.h"

#include <cstdint>

#include "k2000/input/CKAction.h"
#include "k2000/input/CKCombo.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x00102030 InputSequenceTracker_Construct_maybe, in the original's store order.
CKComboManager::CKComboManager() {
    m_aCombos = nullptr;
    m_ui8NbCombo = 0;
    m_bActive = 0;
}

// 0x00102050 InputSequenceTracker_SetSequence_maybe
int32_t CKComboManager::Initialize(uint8_t nbCombo, CKCombo* combos) {
    m_aCombos = combos;
    m_ui8NbCombo = nbCombo;
    return 1;
}

// 0x00102070 InputSequenceTracker_SetEnabled_maybe
void CKComboManager::ActiveComboManager(uint8_t active) { m_bActive = active; }

// 0x00102730 InputSequenceStep_Init_maybe: a list is null when its count is 0.
void CKComboTransition::InitializeData(uint8_t nbValid, uint8_t nbBreak, CKCommand* valid, CKCommand* breaks) {
    m_ui8NbBreakCommand = nbBreak;
    m_ui8NbValidCommand = nbValid;
    m_aValidCommand = nbValid != 0 ? valid : nullptr;
    m_aBreakCommand = m_ui8NbBreakCommand != 0 ? breaks : nullptr;
}

// 0x001021d0 InputSequenceTracker_SetSequenceEnabled_maybe
void CKComboManager::SetComboActive(uint32_t combo, uint8_t active) {
    m_aCombos[combo].m_bActive = active;
    m_aCombos[combo].Reset();
}

namespace {

// The break commands of `transition` (the inlined loop at 0x102328 / 0x1024fc): the combo starts over as
// soon as one action's filtered value is above its command's value.
void CheckBreakCommands(CKCombo* combo, const CKComboTransition* transition, const uint8_t* filtered) {
    const uint8_t count = transition->m_ui8NbBreakCommand;
    if (count == 0) return;
    const CKCommand* command = transition->m_aBreakCommand;
    uint32_t n = 0;
    do {
        if (filtered[command->m_ui8Command] > command->m_ui8Value) {
            combo->Reset();  // 0x00101d38
            return;
        }
        ++command;
        n = (n + 1) & 0xff;
    } while (count != n);
}

}  // namespace

// 0x00102220 InputSequenceTracker_Update_maybe (XXL2 CKComboManager::Update(UInt8*, CKAction*)). CKInput's
// PreUpdate runs it every frame after the actions: combo i's progress goes to filtered[m_ui8NbAction + i]
// (0 not started or broken, 0xff complete; the slot keeps last frame's value until the combo changes it).
// A timed command (m_fTimePressed not 0) is validated once its action has been held at least that long
// (CKAction::m_fActionTimePressed; 0 = released), an untimed one needs the action's filtered value at least
// the command's value in the frame the state advances. The first state starts the combo time
// (m_fStopComboTime = now + m_fComboTime on the scalable game clock); a later state that reaches it starts
// over.
int32_t CKComboManager::Update(uint8_t* filtered, CKAction* actions) {
    if (m_bActive == 0) return 1;
    const uint8_t nbAction = g_pEngine->m_input->m_ui8NbAction;
    const float now = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    if (m_ui8NbCombo == 0) return 1;
    CKCombo* combo = m_aCombos;
    uint32_t i = 0;
    for (;;) {
        uint8_t* slot = &filtered[nbAction + i];
        if (combo->m_bActive == 0 || combo->m_unk05 != 0) {
            *slot = 0;
        } else {
            if (*slot == 0xff) combo->Reset();  // a complete combo starts over
            const uint8_t state = combo->m_ui8CurrentState;
            CKComboTransition* transition = &combo->m_aTransitions[state];
            // The original tests the transition's address (null only for a combo without transitions in
            // state 0).
            if (reinterpret_cast<uintptr_t>(combo->m_aTransitions) + state * sizeof(CKComboTransition) == 0) {
                // nothing
            } else if (state == 0) {
                CheckBreakCommands(combo, transition, filtered);
                const uint8_t count = transition->m_ui8NbValidCommand;
                CKCommand* command = transition->m_aValidCommand;
                uint8_t ok = 1;
                if (count != 0) {
                    uint32_t n = 0;
                    do {
                        const uint8_t action = command->m_ui8Command;
                        if (action == 0xff) {
                            ok = 0;
                        } else {
                            const float timePressed = command->m_fTimePressed;
                            if (timePressed != 0.0f && command->m_bValidate == 0) {
                                const float held = actions[action].m_fActionTimePressed;
                                if (held == 0.0f || timePressed > held) {
                                    ok = 0;
                                } else {
                                    command->m_bValidate = 1;
                                }
                            } else if (timePressed == 0.0f && filtered[action] < command->m_ui8Value) {
                                ok = 0;
                            }
                        }
                        ++command;
                        n = (n + 1) & 0xff;
                    } while (count != n);
                }
                if (ok != 0) {
                    *slot = combo->NextState();  // 0x00101e00
                    combo->m_fStopComboTime = now + combo->m_fComboTime;
                } else {
                    *slot = 0;
                }
            } else if (state == combo->m_ui8NbState) {
                *slot = 0xff;
            } else if (!(combo->m_fStopComboTime > now)) {  // ble: also when unordered
                combo->Reset();
            } else {
                CheckBreakCommands(combo, transition, filtered);
                const uint8_t count = transition->m_ui8NbValidCommand;
                CKCommand* command = transition->m_aValidCommand;
                uint8_t ok = 1;
                if (count != 0) {
                    uint32_t n = 0;
                    do {
                        const float timePressed = command->m_fTimePressed;
                        if (timePressed != 0.0f && command->m_bValidate == 0) {
                            const float held = actions[command->m_ui8Command].m_fActionTimePressed;
                            if (held == 0.0f) {
                                // A released action starts the combo over (this state's commands stay
                                // as they are).
                                combo->Reset();
                                ok = 0;
                            } else if (timePressed > held) {
                                ok = 0;
                            } else {
                                command->m_bValidate = 1;
                            }
                        } else if (timePressed == 0.0f && filtered[command->m_ui8Command] < command->m_ui8Value) {
                            ok = 0;
                        }
                        ++command;
                        n = (n + 1) & 0xff;
                    } while (count != n);
                }
                if (ok != 0) *slot = combo->NextState();  // 0x00101e00; the combo time is not restarted
            }
        }
        i = (i + 1) & 0xff;
        if (!(m_ui8NbCombo > i)) return 1;
        ++combo;
    }
}
