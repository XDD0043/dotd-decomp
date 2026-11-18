// CKFightZoneSectorGrpRoot.cpp - reconstructed original translation unit 0x26d6b8-0x26df60 (GAME_TOC1, main_toc1), 27 functions, 24 live.
// Primary class: CKFightZoneSectorGrpRoot  key 0x1904  category Group  size 0x2c  vtable 0xb21c38
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26d6b8  CKFightZoneSectorGrpRoot_Delete
//   [ ] 0x26d708  CKFightZoneSectorGrpRoot_Construct  [dead]
//   [x] 0x26d778  CKFightZoneSectorGrpRoot_Start  (empty: the IKBaseGroup default)
//   [x] 0x26d780  CKFightZoneSectorGrpRoot_Stop  (empty: the IKBaseGroup default)
//   [x] 0x26d788  CKFightZoneSectorGrpRoot_Pause  (empty: the IKBaseGroup default)
//   [x] 0x26d790  CKFightZoneSectorGrpRoot_Resume  (empty: the IKBaseGroup default)
//   [x] 0x26d798  CKFightZoneSectorGrpRoot_Update  (empty: the IKBaseGroup default)
//   [ ] 0x26d7a0  CKFightZoneSectorGrpRoot_vfB8  [dead: vt+0xb8 (returns 1), called only by the dead CKCoreManager 0x1c330 / 0x1d460 (raw ELF scan of the vt+0xb8 calls)]
//   [ ] 0x26d7a8  CKFightZoneSectorGrpRoot_Construct_2  [dead]
//   [x] 0x26d818  CKFightZoneSectorGrpRoot_PostLoad  (header)
//   [ ] 0x26d840  RegisterCKFightZoneSectorGrpRootClass
//   [ ] 0x26d8b8  _GLOBAL__I_26d8b8
//   [x] 0x26d8c8  CKFightZoneSectorGrpRoot_DeleteArray
//   [x] 0x26d968  CKFightZoneSectorGrpRoot_Restart
//   [x] 0x26da60  CKFightZoneSectorGrpRoot_EnableMembers
//   [x] 0x26dad0  CKFightZoneSectorGrpRoot_OnActivate
//   [x] 0x26db40  CKFightZoneSectorGrpRoot_DisableMembers
//   [x] 0x26dbb0  CKFightZoneSectorGrpRoot_OnDeactivate
//   [x] 0x26dc90  CKFightZoneSectorGrpRoot_CreateArray
//   [x] 0x26dd70  CKFightZoneSectorGrpRoot_Create
//   [x] 0x26ddf8  CKFightZoneSectorGrpRoot_RecursiveRegistration  (inherited: IKGroup_LevelReset 0x12a68, IKBaseGroup.h)
//   [ ] 0x26de20  CKFightZoneSectorGrpRoot_Save
//   [x] 0x26de48  CKFightZoneSectorGrpRoot_Load
//   [x] 0x26de70  CKFightZoneSectorGrpRoot_Destroy  (header)
//   [x] 0x26ded0  CKFightZoneSectorGrpRoot_DeletingDestructor  (the deleting form of the implicit destructor)
//   [ ] 0x26df20  CKFightZoneSectorGrpRoot_Destructor_2  [dead]
//   [x] 0x26df40  CKFightZoneSectorGrpRoot_Destructor  (C++ destructor chain: vtable stores only)
//
//   [x] 0x9bbf50  CKFightZoneSectorGrpRoot_GetClassType  [inline]
//   [x] 0x9bbf58  CKFightZoneSectorGrpRoot_GetClassID  [inline]
//   [ ] 0x9bbf60  CKFightZoneSectorGrpRoot_vfCC  [inline]
//   [ ] 0x9bbf68  CKFightZoneSectorGrpRoot_IsKindOfClass  [inline]
#include "k2000/groups/CKFightZoneSectorGrpRoot.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/IKGrpEnemy.h"

// 0x0026de48 CKFightZoneSectorGrpRoot_Load: GroupBasicLoad only.
int32_t CKFightZoneSectorGrpRoot::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}

// 0x0026d968 CKFightZoneSectorGrpRoot_Restart (vt+0x54): every fight zone (the child groups) whose fight runs (its flags
// bit 5) loses the bit and ends its fight at once (ForceEndFight); unless the root is asleep (its flags bit 2), each zone
// is woken in its own bundle (SetObjectActive_maybe 0x1d1c0).
void CKFightZoneSectorGrpRoot::Restart() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) {
        CKGrpFightZone* zone = static_cast<CKGrpFightZone*>(child);
        if ((zone->m_bitArray & 0x20u) != 0) {
            zone->m_bitArray &= 0xffffffdfu;  // rlwinm 26,1,31 / 6,0,31
            zone->ForceEndFight();  // 0x0026e398
        }
        if ((m_bitArray & 4u) == 0) SetObjectActive(core, child, 1);
    }
}

// 0x0026dad0 CKFightZoneSectorGrpRoot_OnActivate
void CKFightZoneSectorGrpRoot::VfA0() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) SetObjectActive(core, child, 1);
}

// 0x0026dbb0 CKFightZoneSectorGrpRoot_OnDeactivate: every child group (the fight zones) put to sleep in its own bundle
// (SetObjectActive_maybe 0x1d1c0: a zone's vt+0x98 ends a running fight, CKGrpFightZone_StopFight), the enemy group
// (the game manager's +0x04) first unlocked (SetObjectLocked 0x1c250) while it is locked (its bit 1), tested per child.
// G +67774: the sector change of the streaming load ends the fight of the zone the heroes leave, so that zone is no
// longer the enemy group's current one and the next sector's zones run their triggers.
void CKFightZoneSectorGrpRoot::VfA4() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) {
        IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);
        if ((enemies->m_bitArray & 2u) != 0) SetObjectLocked(core, enemies, 0);  // 0x0001c250
        SetObjectActive(core, child, 0);  // 0x0001d1c0
    }
}

// 0x0026da60 CKFightZoneSectorGrpRoot_EnableMembers (vt+0xa8)
void CKFightZoneSectorGrpRoot::OnLock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) SetObjectLocked(core, child, 1);
}

// 0x0026db40 CKFightZoneSectorGrpRoot_DisableMembers (vt+0xac)
void CKFightZoneSectorGrpRoot::OnUnlock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) SetObjectLocked(core, child, 0);
}
