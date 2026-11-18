// CKGrpS08Enemy.cpp - reconstructed original translation unit 0x265b78-0x265ee0 (GAME_TOC1, main_toc1), 6 functions, 3 live.
// Primary class: CKGrpS08Enemy  key 0xa44  category Group  size 0x290  vtable 0xb215f8
// Other owners: IKGrpEnemy (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x265b78  CKGrpS08Enemy_vfA8  (OnLock)
//   [ ] 0x265c08  IKGrpEnemy_GetArray4CEntry_maybe  [dead]
//   [ ] 0x265c48  IKGrpEnemy_IsAnyMemberWithinRadius_maybe  [dead]
//   [x] 0x265cc0  CKGrpS08Enemy_vfAC  (OnUnlock)
//   [x] 0x265d50  CKGrpS08Enemy_ConstructBase_maybe
//   [ ] 0x265e18  CKGrpS08Enemy_ConstructBase_2_maybe  [dead]
// 0x00265d50 CKGrpS08Enemy_ConstructBase_maybe is the IKGrpEnemy constructor: inline in k2000/misc/IKGrpEnemy.h.

#include "Spyro2008/groups/CKGrpS08Enemy.h"

#include "k2000/logic/CKCoreManager.h"
#include "k2000/misc/Engine.h"

// 0x00265b78 CKGrpS08Enemy_vfA8 (vt+0xa8)
void CKGrpS08Enemy::OnLock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (uint32_t i = 0; i < m_vpFZSectorGrpRoot.m_ui32NbUsedElt; ++i) {
        SetObjectLocked(core, static_cast<IKLife*>(m_vpFZSectorGrpRoot.m_pBlock[i]), 1);  // 0x0001c250
    }
}

// 0x00265cc0 CKGrpS08Enemy_vfAC (vt+0xac)
void CKGrpS08Enemy::OnUnlock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (uint32_t i = 0; i < m_vpFZSectorGrpRoot.m_ui32NbUsedElt; ++i) {
        SetObjectLocked(core, static_cast<IKLife*>(m_vpFZSectorGrpRoot.m_pBlock[i]), 0);  // 0x0001c250
    }
}
