// CKHkS08Weapon.cpp - reconstructed original translation unit 0x2b0ea0-0x2b2d08 (GAME_TOC1, main_toc1), 31 functions, 27 live.
// Primary class: CKHkS08Weapon  key 0x2902  category Hook  size 0xd0  vtable 0xb223f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b0ea0  CKHkS08Weapon_Delete
//   [ ] 0x2b0ef0  CKHkS08Weapon_Pause
//   [ ] 0x2b0ef8  CKHkS08Weapon_Resume
//   [ ] 0x2b0f00  CKHkS08Weapon_vfC0
//   [ ] 0x2b0f08  CKHkS08Weapon_vfCC
//   [ ] 0x2b0f10  CKHkS08Weapon_ResetRuntime_2  [dead]
//   [ ] 0x2b0f98  CKHkS08Weapon_InitStateMachine_maybe  [dead]
//   [ ] 0x2b0fd8  CKHkS08Weapon_InitDefaults_maybe  [dead]
//   [ ] 0x2b1020  CKHkS08Weapon_SyncFramePosition_maybe  [dead]
//   [ ] 0x2b1088  CKHkS08Weapon_RecursiveRegistration
//   [ ] 0x2b10b0  CKHkS08Weapon_Destroy
//   [x] 0x2b10f8  CKHkS08Weapon_DeleteArray
//   [x] 0x2b1198  CKHkS08Weapon_Create
//   [ ] 0x2b1250  RegisterCKHkS08WeaponClass
//   [ ] 0x2b12d8  _GLOBAL__D_2b12d8
//   [ ] 0x2b12e8  _GLOBAL__I_2b12e8
//   [ ] 0x2b12f8  CKHkS08Weapon_TakeFromPool_maybe
//   [ ] 0x2b1500  CKHkS08Weapon_PostLoad
//   [ ] 0x2b1558  CKHkS08Weapon_ReturnToPool_maybe
//   [ ] 0x2b1688  CKHkS08Weapon_Stop
//   [ ] 0x2b1748  CKHkS08Weapon_MessageProc
//   [x] 0x2b1750  CKHkS08Weapon_CreateArray
//   [x] 0x2b1870  CKHkS08Weapon_Load
//   [ ] 0x2b1a38  CKHkS08Weapon_Save
//   [x] 0x2b1be8  CKHkS08Weapon_Start
//   [ ] 0x2b1c70  CKHkS08Weapon_State0
//   [ ] 0x2b2218  CKHkS08Weapon_SetEjectVelocity_maybe
//   [ ] 0x2b24e0  CKHkS08Weapon_State1
//   [ ] 0x2b2870  CKHkS08Weapon_Update
//   [ ] 0x2b2a70  CKHkS08Weapon_SetLanded_maybe
//   [ ] 0x2b2bc0  CKHkS08Weapon_SetEjected_maybe
//
//   [ ] 0x9bcaa0  CKHkS08Weapon_IsKindOfClass  [inline]
//   [ ] 0x9bcae8  CKHkS08Weapon_GetClassType  [inline]
//   [ ] 0x9bcaf0  CKHkS08Weapon_GetClassID  [inline]
//   [ ] 0x9bcaf8  CKHkS08Weapon_Destructor  [inline]
//   [ ] 0x9bcb18  CKHkS08Weapon_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "k2000/core/Ps3MemberFn.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// 0x00c4092c (TOC +0x16d0): the reference count per weapon kind (read-only; only Load, Save and
// CKHkS08Weapon_State0 read it). Nine words before the next table (0x01010101 at index 9)_maybe.
const uint32_t kWeaponRefCount[9] = {0, 0, 0, 0, 2, 0, 0, 2, 0};
}  // namespace

// 0x002b1870 CKHkS08Weapon_Load
int32_t CKHkS08Weapon::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    ReadU32LE(file, &m_unk20);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): the block is sized by the kind's table entry, the read by the file's count.
    m_apUnkAC = static_cast<IKSerializable**>(
        Mem_CallocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*)), kWeaponRefCount[m_unk20]));
    IKFile_ReadObjectRefArray(file, m_apUnkAC, count);
    return 1;
}

namespace {
// DOTD: the weapon's state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table Start builds at +0xc0).
Ps3MemberFnEntry<CKHkS08Weapon::StateFn> g_weaponStates[] = {
    {0x00b93f20u, nullptr, "CKHkS08Weapon_State0 0x2b1c70 (C2.7: weapons)", false},
    {0x00b93f30u, nullptr, "CKHkS08Weapon_State1 0x2b24e0 (C2.7: weapons)", false},
};
}  // namespace

uint8_t CKHkS08Weapon::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_weaponStates, pair, "CKHkS08Weapon state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x002b1be8 CKHkS08Weapon_Start
void CKHkS08Weapon::Start() {
    // The state engine: a table of two handlers at +0xc0 (the PS3 descriptors of CKHkS08Weapon_State0 / State1,
    // TOC +0x1684 / +0x1688) that +0xb8 points to; the current state byte pair 0xff / 2.
    // CallState maps them to the native handlers (g_weaponStates; the update that runs them is C2.7).
    m_unkC0[0] = 0x00b93f20u;
    m_unkC0[2] = 0x00b93f30u;
    m_unkC0[1] = 0;
    m_unkC0[3] = 0;
    m_unkB8 = &m_unkC0[0];
    m_unkBC = 0xff;
    m_unkBD = 2;
    m_GContactIn.m_fDeltaMax = 0.2f;     // TOC +0x168c (0x3e4ccccd)
    m_GContactIn.m_fObjectHeight = 1.0f;  // TOC +0x1690
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 2;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_unkB0[1] = 0;
}
