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
//   [x] 0x3447e0  CKControlableHero_UpdateMoveTo
//   [ ] 0x344848  RegisterCKControlableHeroClass
//   [ ] 0x3448c0  _GLOBAL__I_3448c0
//   [x] 0x3448d0  CKControlableHero_DetachHero
//   [x] 0x344948  CKControlableHero_BindAndAttachHero_maybe
//   [x] 0x344a80  CKControlableHero_DeleteArray
//   [x] 0x344b28  CKControlableHero_CreateArray
//   [x] 0x344bd0  CKControlableHero_Create
//   [x] 0x344c10  CKControlableHero_Load
//   [x] 0x344c88  CKControlableHero_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x344c90  CKControlableHero_PostLoad  (returns 1: the root's default)
//   [x] 0x344c98  CKControlableHero_Destroy
//   [x] 0x344ca8  CKControlableHero_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x344cc8  CKControlableHero_DeletingDestructor  (C++ deleting destructor)
//   [ ] 0x344d10  CKControlableHero_Destructor_2  [dead]
//   [x] 0x344d30  CKHkS08Hero_GetComponentByKey_maybe
//   [x] 0x344d48  IKHkHero_GetCinematicAnimSlots
//   [x] 0x344e10  CKHkS08Hero_BasePause_maybe  (empty: CKHkS08Hero::Pause's base call, IKHook's empty Pause)
//   [x] 0x344e18  CKHkS08Hero_BaseResume_maybe  (empty: CKHkS08Hero::Resume's base call, IKHook's empty Resume)
//   [x] 0x344e20  KStub_Nop_344e20  (empty)
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
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"

// 0x00344c10 CKControlableHero_Load
int32_t CKControlableHero::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk04);
        m_pHero = nullptr;  // the original stores `type`, which is 0 here
    }
    return 1;
}

// 0x00344948 CKControlableHero_BindAndAttachHero_maybe (C2.8 sequence)
void CKControlableHero::BindAndAttachHero(const CVector3* position, const CVector3* direction) {
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x08
    if (group == nullptr) {
        m_pHero = nullptr;  // the stw of the null group
        return;
    }
    m_pHero = static_cast<CKHkS08Hero*>(group->m_apHeros[m_unk04]);  // 0x002ca080 GetHeroByDragonIndex
    if (m_pHero == nullptr) return;
    if (m_pHero->AttachToObject(this, 3) == 0) return;  // 0x00362360
    m_pHero->SetAttachedMovementEnabled(1);              // 0x00362050
    // vt+0xcc CKHkS08Hero_SetMoveDestination: r6 is left from the calls above (not read).
    m_pHero->SetMoveDestination(10.0f, position, direction, 0, 1, 0);  // TOC +0x2aa4 10.0
}

// 0x003447e0 CKControlableHero_UpdateMoveTo
uint8_t CKControlableHero::UpdateMoveTo(IKTime* clock) {
    if (m_pHero == nullptr) return 1;
    return m_pHero->UpdateMoveTo(clock, nullptr);  // vt+0xd0
}

// 0x003448d0 CKControlableHero_DetachHero
void CKControlableHero::DetachHero() {
    if (m_pHero == nullptr) return;
    if (m_pHero->GetAttachedObject() != this) return;  // 0x00361d50
    m_pHero->DetachFromObject();                        // 0x00364608
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
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_unk90->MessageProc(0x940, this);
}

// 0x00344d30 CKHkS08Hero_GetComponentByKey_maybe (vt+0xb0)
IKSerializable* CKHkS08Hero::GetComponent(uint32_t key) {
    if (key != 0x486) return nullptr;
    return reinterpret_cast<IKSerializable*>(&m_unk64);  // the shadow data: m_unk64..m_unk80 (pointer + 0x64)
}

// 0x00344d48 IKHkHero_GetCinematicAnimSlots (vt+0xbc; only the abstract hero's vtable 0xb22f10 holds it)
void IKHkHero::GetBlendSlot(AnimBlendSlot** slots, int32_t* count) {
    const uint32_t n = static_cast<IKGrpHero*>(m_pGrpHero)->GetNbAnimBlendSlots(m_ui8Hero);  // vt+0x134 (a byte)
    *count = static_cast<int32_t>(n);
    for (uint32_t i = n; i != 0; --i) slots[i - 1] = m_pAnimBlendSlots + (i - 1);
}
