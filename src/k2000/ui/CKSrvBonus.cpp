// CKSrvBonus.cpp - reconstructed original translation unit 0x5a9638-0x5a9bc8 (GAME_TOC2, main_toc2), 20 functions, 20 live.
// Primary owner: CKSrvBonus (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5a9638  CKSrvBonus_SpawnBonusWithVelocity_maybe
//   [x] 0x5a96c8  CKSrvBonus_Resume
//   [x] 0x5a96f0  CKSrvBonus_Pause
//   [x] 0x5a9718  CKSrvBonus_ResetOnLevelEnd_maybe
//   [x] 0x5a9740  CKSrvBonus_ResetRuntime
//   [x] 0x5a9768  CKSrvBonus_Load
//   [ ] 0x5a9790  CKSrvBonus_Save
//   [x] 0x5a97b8  CKSrvBonus_LevelReset  (RecursiveRegistration: KBase201's (0x126bd8), inherited)
//   [x] 0x5a97e0  CKSrvBonus_ClearReferences  (inherited: TocBridge_KBase201_Destroy)
//   [x] 0x5a9808  CKSrvBonus_vf98
//   [x] 0x5a9830  CKSrvBonus_Init
//   [x] 0x5a9858  CKSrvBonus_DeletingDestructor  (implicit: the vtable, KBase201's destructor)
//   [x] 0x5a98a0  CKSrvBonus_Destructor  (implicit: the vtable, KBase201's destructor)
//   [x] 0x5a98d0  CKSrvBonus_Destructor_2  (implicit: the vtable, KBase201's destructor)
//   [x] 0x5a9900  CKSrvBonus_Construct_2  (= 0x5a9938 CKSrvBonus_Construct)
//   [x] 0x5a9938  CKSrvBonus_Construct
//   [x] 0x5a9970  CKSrvBonus_DestroyArray
//   [x] 0x5a9a18  CKSrvBonus_SpawnBonus_maybe  (SpawnBonusForHero, vt+0xac)
//   [x] 0x5a9ab8  CKSrvBonus_Create
//   [x] 0x5a9b10  CKSrvBonus_CreateArray
//
//   [ ] 0x9cbdd8  CKSrvBonus_IsKindOf  [inline]
//   [ ] 0x9cbe20  CKSrvBonus_GetClassGroup  [inline]
//   [ ] 0x9cbe28  CKSrvBonus_GetClassId  [inline]
#include "k2000/ui/CKSrvBonus.h"

#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/ui/CKGrpBonus.h"
#include "k2000/ui/IKHkBonus.h"

// 0x005a9938 CKSrvBonus_Construct (the same code inlined in 0x5a9ab8 CKSrvBonus_Create): the base,
// then the vtable.
CKSrvBonus::CKSrvBonus() {}

// 0x005a9768 CKSrvBonus_Load: the base's Load (TocBridge_KBase201_Load), then 1.
int32_t CKSrvBonus::Load(IKFile* file, int32_t type) {
    KBase201::Load(file, type);
    return 1;
}

// 0x005a9638 CKSrvBonus_SpawnBonusWithVelocity_maybe (see the header).
void CKSrvBonus::SpawnBonusWithVelocity(uint32_t kind, const float* pos, const float* vel, uint8_t last) {
    CKGrpBonus* group = static_cast<CKGrpBonus*>(g_pEngine->m_gameManager->m_unk04[3]);  // the game manager's +0x10
    if (group == nullptr) return;
    IKSerializable* bonus = group->SpawnBonusObject(kind, reinterpret_cast<const CVector3*>(pos), last);  // 0x005b0df8
    if (bonus != nullptr) {
        static_cast<IKHkBonus*>(bonus)->SetLaunchVelocity(reinterpret_cast<const CVector3*>(vel), nullptr);  // vt+0xe0
    }
}

// 0x005a9a18 CKSrvBonus_SpawnBonus_maybe (see the header).
void CKSrvBonus::SpawnBonusForHero(uint32_t kind, const CVector3* pos, const CVector3* velocity, IKSerializable* hero,
                                   uint8_t last) {
    CKGrpBonus* group = static_cast<CKGrpBonus*>(g_pEngine->m_gameManager->m_unk04[3]);  // the game manager's +0x10
    if (group == nullptr) return;
    IKSerializable* bonus = group->SpawnBonusObject(kind, pos, last);  // 0x005b0df8
    if (bonus != nullptr) static_cast<IKHkBonus*>(bonus)->VfE4(velocity, hero);  // vt+0xe4
}
