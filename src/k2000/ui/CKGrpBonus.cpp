// CKGrpBonus.cpp - reconstructed original translation unit 0x5b0ce0-0x5b1348 (GAME_TOC2, main_toc2), 14 functions, 13 live.
// Primary owner: CKGrpBonus (not a registered class)
// Other owners: BonusPool (1), UpdateCKGrpBonus (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5b0ce0  CKGrpBonus_DestroyArray  (vtable-only destructors (implicit here))
//   [x] 0x5b0d80  CKGrpBonus_Create
//   [x] 0x5b0df8  BonusPool_SpawnBonusObject
//   [x] 0x5b0e90  CKGrpBonus_ReinitRuntime
//   [x] 0x5b0ef8  UpdateCKGrpBonus
//   [x] 0x5b0f70  CKGrpBonus_OnLevelExit_maybe
//   [x] 0x5b0fd8  CKGrpBonus_vf40  (GetInfo: the default, header)
//   [x] 0x5b0fe0  CKGrpBonus_CreateArray
//   [x] 0x5b10b0  CKGrpBonus_vf1C  (MessageProc)
//   [ ] 0x5b1188  CKGrpBonus_TriggerChildCollectEffects_maybe  [dead]
//   [x] 0x5b1210  CKGrpBonus_LevelReset  (RecursiveRegistration)
//   [x] 0x5b1298  CKGrpBonus_Load
//   [ ] 0x5b12c0  CKGrpBonus_Save
//   [x] 0x5b12e8  CKGrpBonus_ClearReferences  (Destroy, header)
//
//   [x] 0x9cc318  CKGrpBonus_GetClassGroup  [inline]
//   [x] 0x9cc320  CKGrpBonus_GetClassId  [inline]
//   [ ] 0x9cc328  CKGrpBonus_vfCC  [inline]
//   [ ] 0x9cc330  CKGrpBonus_vf70  [inline]
//   [ ] 0x9cc338  CKGrpBonus_vf78  [inline]
//   [ ] 0x9cc340  CKGrpBonus_IsKindOf  [inline]
//   [ ] 0x9cc398  CKGrpBonus_DeletingDestructor  [inline]
//   [x] 0x9cc3e8  CKGrpBonus_Destructor  [inline]  (vtable only (implicit))
#include "k2000/ui/CKGrpBonus.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/memory/CKGrpBonusPool.h"
#include "k2000/misc/Engine.h"

// 0x005b0e90 CKGrpBonus_ReinitRuntime (vt+0x54)
void CKGrpBonus::Restart() {
    for (IKBaseGroup* pool = m_lChilds; pool != nullptr; pool = pool->m_pNextGroup) {
        static_cast<CKGrpBonusPool*>(pool)->VfF8();  // vt+0xf8 0x5b1eb0
    }
}

// 0x005b0bc8 CKGrpBonus_ResetRuntime (vt+0x50; its checklist line is in CKGrpS08BonusPool.cpp)
void CKGrpBonus::Start() {
    for (IKBaseGroup* pool = m_lChilds; pool != nullptr; pool = pool->m_pNextGroup) {
        static_cast<CKGrpBonusPool*>(pool)->ResetPool();  // vt+0xec 0x5b1f10
    }
}

// 0x005b0f70 CKGrpBonus_OnLevelExit_maybe (vt+0x68)
void CKGrpBonus::Stop() {
    for (IKBaseGroup* pool = m_lChilds; pool != nullptr; pool = pool->m_pNextGroup) {
        static_cast<CKGrpBonusPool*>(pool)->VfF0();  // vt+0xf0 0x5b13a0
    }
}

// 0x005b0ef8 UpdateCKGrpBonus (vt+0x7c)
void CKGrpBonus::Update(IKTime* frameClock) {
    for (IKBaseGroup* pool = m_lChilds; pool != nullptr; pool = pool->m_pNextGroup) {
        static_cast<CKGrpBonusPool*>(pool)->UpdateBonuses(frameClock);  // vt+0xf4
    }
}

// 0x005b0df8 BonusPool_SpawnBonusObject
IKSerializable* CKGrpBonus::SpawnBonusObject(uint32_t kind, const CVector3* position, uint8_t playSound) {
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) {
        CKGrpBonusPool* pool = static_cast<CKGrpBonusPool*>(child);
        if ((pool->m_bitArray & 0x100u) == 0 && pool->m_ui32BonusType == kind) {
            return pool->SpawnBonus(position, playSound);  // vt+0xfc
        }
    }
    return nullptr;
}

// 0x005b1298 CKGrpBonus_Load: GroupBasicLoad only (through its TOC bridge).
int32_t CKGrpBonus::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}

// 0x005b10b0 CKGrpBonus_vf1C (MessageProc)
int32_t CKGrpBonus::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0xe00) {
        for (IKBaseGroup* pool = m_lChilds; pool != nullptr; pool = pool->m_pNextGroup) {
            pool->m_bitArray = (pool->m_bitArray & 0xffffff7fu) | 0x80u;
        }
    } else {
        if (message != 0xe01) return 1;
        for (IKBaseGroup* pool = m_lChilds; pool != nullptr; pool = pool->m_pNextGroup) {
            pool->m_bitArray &= 0xffffff7fu;
        }
    }
    return 0;
}

// 0x005b1210 CKGrpBonus_RecursiveRegistration (IKGroup_LevelReset through its TOC bridge)
void CKGrpBonus::RecursiveRegistration(int32_t type) {
    IKGroup<IKHook>::RecursiveRegistration(type);
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
