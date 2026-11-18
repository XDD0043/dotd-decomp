// Reconstructed original translation unit: 0x5c79e0-0x5c7bf8 (GAME_TOC2, main_toc2), 8 functions, 6 live.
// Primary owner: CKHkScriptedNPC (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c79e0  CKHkScriptedNPC_Destroy  (DOTD_DECLARE_FACTORIES)
//   [x] 0x5c7a30  CKHkScriptedNPC_GetTriggerProp99
//   [x] 0x5c7a40  CKHkScriptedNPC_GetTriggerProp9B
//   [x] 0x5c7a50  CKHkScriptedNPC_vfC8
//   [x] 0x5c7a88  CKHkScriptedNPC_vfF0
//   [ ] 0x5c7a90  CKHkScriptedNPC_DispatchToNextStateBlock_maybe  [dead]
//   [x] 0x5c7b68  CKHkScriptedNPC_vf100
//   [ ] 0x5c7bc0  FUN_005c7bc0  [dead]
//
// GetTriggerProp99 / 9B are GetInfo's accessors (CKHkScriptedNPC_2.cpp); vfF0 is SetStream in the header.
#include "k2000/ui/CKHkScriptedNPC.h"

// 0x005c7a50 CKHkScriptedNPC_vfC8 (vt+0xc8): the state preset's active (+0x4c) and shown (+0x50) bytes: +0x4e / +0x52
// for a non-zero state, else +0x4f / +0x53.
void CKHkScriptedNPC::ApplyStatePreset(int32_t state) {
    if (state != 0) {
        m_unk4C = m_unk4E;
        m_unk50 = m_unk52;
        return;
    }
    m_unk4C = m_unk4F;
    m_unk50 = m_unk53;
}

// 0x005c7b68 CKHkScriptedNPC_vf100 (vt+0x100): the prepared block (+0x5c) undone (vt+0xfc) unless it is the current one.
void CKHkScriptedNPC::UnprepareNext() {
    if (m_unk60 != m_unk5C) UnprepareBlock(m_unk5C);
}
