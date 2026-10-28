// CKControlableHero.cpp - reconstructed original translation unit 0x344758-0x344ef0 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKControlableHero  key 0xa88c  category Logic  size 0xc  vtable 0xb22e40
// Other owners: CKHkS08Hero (6), IKHkHero (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x344758  CKControlableHero_Delete
//   [x] 0x3447a8  CKControlableHero_Construct  [dead]
//   [ ] 0x3447c0  CKControlableHero_Construct_2  [dead]
//   [ ] 0x3447d8  CKControlableHero_Save
//   [ ] 0x3447e0  CKControlableHero_UpdateMoveTo
//   [ ] 0x344848  RegisterCKControlableHeroClass
//   [ ] 0x3448c0  _GLOBAL__I_3448c0
//   [ ] 0x3448d0  CKControlableHero_DetachHero
//   [ ] 0x344948  CKControlableHero_BindAndAttachHero_maybe
//   [x] 0x344a80  CKControlableHero_DeleteArray
//   [x] 0x344b28  CKControlableHero_CreateArray
//   [x] 0x344bd0  CKControlableHero_Create
//   [x] 0x344c10  CKControlableHero_Load
//   [ ] 0x344c88  CKControlableHero_RecursiveRegistration
//   [ ] 0x344c90  CKControlableHero_PostLoad
//   [ ] 0x344c98  CKControlableHero_Destroy
//   [ ] 0x344ca8  CKControlableHero_Destructor
//   [ ] 0x344cc8  CKControlableHero_DeletingDestructor
//   [ ] 0x344d10  CKControlableHero_Destructor_2  [dead]
//   [ ] 0x344d30  CKHkS08Hero_GetComponentByKey_maybe
//   [ ] 0x344d48  IKHkHero_GetCinematicAnimSlots
//   [ ] 0x344e10  CKHkS08Hero_BasePause_maybe
//   [ ] 0x344e18  CKHkS08Hero_BaseResume_maybe
//   [ ] 0x344e20  KStub_Nop_344e20
//   [ ] 0x344e28  CKHkS08Hero_InitAnimBlendSlot_Thunk_maybe  [dead]
//   [x] 0x344e68  CKHkS08Hero_GetControllingHero
//   [x] 0x344e88  CKHkS08Hero_LeaveAttachedObject_maybe
//   [ ] 0x344ee8  KStub_Nop_344ee8  [dead]
//
//   [ ] 0x9be790  CKControlableHero_GetClassType  [inline]
//   [ ] 0x9be798  CKControlableHero_GetClassID  [inline]
//   [ ] 0x9be7a0  KBaseA88C_IsKindOf  [inline]
//   [ ] 0x9be7c8  CKControlableHero_IsKindOfClass  [inline]
//   [ ] 0x9be7f0  KBaseA88C_DeletingDestructor  [inline]
//   [ ] 0x9be830  KBaseA88C_Destructor  [inline]
#include "k2000/logic/CKControlableHero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"

#include "k2000/io/IKFile.h"

// 0x00344c10 CKControlableHero_Load
int32_t CKControlableHero::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk04);
        m_unk08 = 0;  // the original stores `type`, which is 0 here
    }
    return 1;
}

// 0x00344e68 CKHkS08Hero_GetControllingHero: the group's hero of index m_ui8TrackedLeader (the one this hero follows;
// itself for the player's hero).
CKHkS08Hero* CKHkS08Hero::GetControllingHero() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    return static_cast<CKHkS08Hero*>(group->m_apHeros[m_ui8TrackedLeader]);
}

// 0x00344e88 CKHkS08Hero_LeaveAttachedObject_maybe (step 4 AI: TeleportTo's): a hero attached to an object
// (+0x358 bit 0) tells it (+0x90, MessageProc vt+0x1c) message 0x940 with itself.
void CKHkS08Hero::LeaveAttachedObject() {
    if ((m_unk358 & 1u) == 0) return;
    m_unk90->MessageProc(0x940, this);
}
