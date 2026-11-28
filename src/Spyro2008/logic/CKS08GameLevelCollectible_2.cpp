// CKS08GameLevelCollectible_2.cpp - reconstructed original translation unit 0x4f5d48-0x4f6648 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKS08GameLevelCollectible  key 0xa8cc  category Logic  size 0x24  vtable 0xb2aef8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4f5d48  CKS08GameLevelCollectible_Delete
//   [x] 0x4f5d98  CKS08GameLevelCollectible_SetDefaultState
//   [x] 0x4f5da8  CKS08GameLevelCollectible_vf68
//   [x] 0x4f5db0  CKS08GameLevelCollectible_ApplyCollect_maybe
//   [x] 0x4f5fa8  CKS08GameLevelCollectible_ClearGameData_maybe
//   [x] 0x4f5fd0  CKS08GameLevelCollectible_ClearLevelData
//   [x] 0x4f5ff8  CKS08GameLevelCollectible_InitLevelData
//   [x] 0x4f6020  CKS08GameLevelCollectible_PostLoad
//   [x] 0x4f6048  CKS08GameLevelCollectible_Save
//   [x] 0x4f6070  CKS08GameLevelCollectible_RecursiveRegistration
//   [x] 0x4f6098  CKS08GameLevelCollectible_Destroy
//   [x] 0x4f60c0  CKS08GameLevelCollectible_DeleteArray
//   [x] 0x4f6168  CKS08GameLevelCollectible_Create
//   [ ] 0x4f61c0  RegisterCKS08GameLevelCollectibleClass
//   [ ] 0x4f6248  _GLOBAL__D_4f6248
//   [ ] 0x4f6258  _GLOBAL__I_4f6258
//   [x] 0x4f6268  CKS08GameLevelCollectible_MessageProc
//   [x] 0x4f6398  CKS08GameLevelCollectible_InitGameData
//   [x] 0x4f63e8  CKS08GameLevelCollectible_GetInfo
//   [x] 0x4f6440  CKS08GameLevelCollectible_CreateArray
//   [x] 0x4f64f8  CKS08GameLevelCollectible_Load
//
//   [ ] 0x9c6bf0  CKS08GameLevelCollectible_IsKindOfClass  [inline]
//   [x] 0x9c6c30  CKS08GameLevelCollectible_GetClassType  [inline]
//   [x] 0x9c6c38  CKS08GameLevelCollectible_GetClassID  [inline]
//   [x] 0x9c6c40  CKS08GameLevelCollectible_GetTriggerProp14  [inline]
//   [ ] 0x9c6c48  CKS08GameLevelCollectible_Destructor  [inline]
//   [ ] 0x9c6c68  CKS08GameLevelCollectible_DeletingDestructor  [inline]
#include "Spyro2008/logic/CKS08GameLevelCollectible.h"

#include "k2000/io/IKFile.h"
#include "Spyro2008/logic/CKS08GameLevel.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/core/IKInfo.h"

// 0x004f6398 CKS08GameLevelCollectible_InitGameData
void CKS08GameLevelCollectible::InitializeGameData() {
    KBase1D0C::InitializeGameData();
    m_ui8ArmorSlot = 0;
    m_ui8Category = 1;
    m_bCollected = 0;
    m_ui8DragonIndex = 0;
    m_ui8ArmorSet = 0;
}

// 0x004f6268 CKS08GameLevelCollectible_MessageProc: the base's answer combined with its own (3, then 2, win; a base 0
// answers 0, else its own).
int32_t CKS08GameLevelCollectible::MessageProc(uint16_t message, void* data) {
    const int32_t base = KBase1D0C::MessageProc(message, data);  // 0x43478: 1
    int32_t own = 1;
    if (message == 0x20a) {
        if (*static_cast<const uint8_t*>(data) == 0) m_bCollected = 0;
        else ApplyCollect();  // 0x4f5db0
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// 0x004f63e8 CKS08GameLevelCollectible_GetInfo
int32_t CKS08GameLevelCollectible::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0x14) return 1;
    // 0x009c6c40 CKS08GameLevelCollectible_GetTriggerProp14: +0x1c.
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t { return static_cast<CKS08GameLevelCollectible*>(o)->m_bCollected; }, 0);
}

// 0x004f5db0 CKS08GameLevelCollectible_ApplyCollect_maybe
void CKS08GameLevelCollectible::ApplyCollect() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(static_cast<CKGameLevel*>(m_pLevel)->GetGameManager());  // 0x391e0
    const uint8_t category = m_ui8Category;
    m_bCollected = 1;
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
    structure->InvalidateCategoryCount(category);  // 0x50ed40
    manager->PlayCollectibleMusic();                // 0x4f8cc0
    if (m_ui8Category == 0) {
        manager->ShowCollectedItemMessage(m_ui8DragonIndex, m_ui8ArmorSlot, m_ui8ArmorSet);  // 0x501a08
        if (structure->CountItemsByCategory(0, 1) == 1) manager->QueueFirstCollectibleInfo();  // 0x50f730, 0x4ffdd0
    }
    if (m_ui8Category == 4) manager->QueueCollectibleMessage();  // 0x501938
    if (m_ui8Category == 1) {
        manager->RefreshDragonStatDisplays(0, 0, 0);  // 0x5022b0
        manager->RefreshDragonStatDisplays(1, 0, 0);
        manager->RefreshHealthShardHud(0, 0);  // 0x5032d0
        manager->RefreshHealthShardHud(1, 0);
    }
    if (m_ui8Category != 2) return;
    manager->RefreshDragonStatDisplays(0, 0, 0);
    manager->RefreshDragonStatDisplays(1, 0, 0);
    manager->RefreshManaShardHud(0, 0);  // 0x502ca0
    manager->RefreshManaShardHud(1, 0);
}

// 0x004f64f8 CKS08GameLevelCollectible_Load
int32_t CKS08GameLevelCollectible::Load(IKFile* file, int32_t type) {
    KBase1D0C::Load(file, type);
    if (type != kGameStructureBlock) return 1;
    ReadU8(file, &m_ui8Category);
    ReadU8(file, &m_ui8DragonIndex);
    ReadU8(file, &m_ui8ArmorSet);
    ReadU8(file, &m_ui8ArmorSlot);
    return 1;
}
