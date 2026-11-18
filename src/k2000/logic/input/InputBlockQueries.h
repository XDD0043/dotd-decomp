// InputBlockQueries.h - the input blocks' game-manager queries (KBase628C's non-virtual helpers in CKInputBlock.cpp,
// k2000/input, P21's unit: its checklist is left as it was). C2.8 port-all P06 wrote them here, inline, for the action
// and position blocks (KBase608C.h, KBase620C.h). Each asks the game manager (engine +0x8c) for the block's player (+0x0f).
#pragma once
#include <cstdint>

#include "k2000/input/KBase628C.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"

// 0x00209a90 CKInputBlock_628c_maybe_IsActionPressed_maybe: the filtered state of `action` (vt+0x160).
inline uint8_t InputBlock_IsActionPressed(const KBase628C* block, uint8_t action) {
    return g_pEngine->m_gameManager->IsActionPressed(action, block->m_unk0f);
}

// 0x0020a108 CKInputBlock_628c_maybe_GetActionValue_maybe: the analog value of `action` (vt+0x164).
inline float InputBlock_GetActionValue(const KBase628C* block, uint8_t action) {
    return g_pEngine->m_gameManager->GetActionValue(action, block->m_unk0f);
}

// 0x0020a158 CKInput_IsStickDirectionPressed_maybe: the action of stick direction `direction` (vt+0x15c; -1 none, as a
// signed byte), then its filtered state (vt+0x160); 0 without an action.
inline uint8_t InputBlock_IsStickDirectionPressed(const KBase628C* block, uint32_t direction) {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    const int8_t action = static_cast<int8_t>(manager->GetStickDirectionAction(direction));
    if (action == -1) return 0;
    return g_pEngine->m_gameManager->IsActionPressed(static_cast<uint8_t>(action), block->m_unk0f);
}
