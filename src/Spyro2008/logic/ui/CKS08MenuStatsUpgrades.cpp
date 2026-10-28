// CKS08MenuStatsUpgrades.cpp - reconstructed original translation unit 0x56aee8-0x56cd80 (GAME_TOC2, main_toc2), 23 functions, 21 live.
// Primary class: CKS08MenuStatsUpgrades  key 0xad0c  category Logic  size ?  vtable 0xb2d7e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x56aee8  CKS08MenuStatsUpgrades_Delete
//   [x] 0x56af38  CKS08MenuStatsUpgrades_vf8C
//   [x] 0x56af50  CKS08MenuStatsUpgrades_vf90
//   [ ] 0x56af68  CKS08MenuStatsUpgrades_RefreshUpgradeRowGroup_maybe
//   [ ] 0x56b328  CKS08MenuStatsUpgrades_HandlePageInput_maybe
//   [ ] 0x56b570  CKS08MenuStatsUpgrades_OnItemEvent
//   [ ] 0x56b5b8  CKS08MenuStatsUpgrades_RecursiveRegistration
//   [ ] 0x56b628  CKS08MenuStatsUpgrades_Destroy
//   [x] 0x56b650  CKS08MenuStatsUpgrades_DeleteArray
//   [ ] 0x56b6f0  RegisterCKS08MenuStatsUpgradesClass
//   [ ] 0x56b778  _GLOBAL__D_56b778
//   [ ] 0x56b788  _GLOBAL__I_56b788
//   [ ] 0x56b798  CKS08MenuStatsUpgrades_Construct  [dead]
//   [ ] 0x56b840  CKS08MenuStatsUpgrades_Save
//   [ ] 0x56b988  CKS08MenuStatsUpgrades_Construct_2  [dead]
//   [x] 0x56ba30  CKS08MenuStatsUpgrades_Load
//   [x] 0x56bc60  CKS08MenuStatsUpgrades_Create
//   [x] 0x56bd48  CKS08MenuStatsUpgrades_CreateArray
//   [ ] 0x56be88  CKS08MenuStatsUpgrades_Destructor_2
//   [ ] 0x56bfc0  CKS08MenuStatsUpgrades_DeletingDestructor
//   [ ] 0x56c0f8  CKS08MenuStatsUpgrades_Destructor
//   [ ] 0x56c230  CKS08MenuStatsUpgrades_RefreshUpgradeTexts_maybe
//   [ ] 0x56cb20  CKS08MenuStatsUpgrades_OnMenuState_maybe
//
//   [x] 0x9ca6a8  CKS08MenuStatsUpgrades_IsKindOfClass  [inline]
//   [x] 0x9ca6e8  CKS08MenuStatsUpgrades_GetClassType  [inline]
//   [x] 0x9ca6f0  CKS08MenuStatsUpgrades_GetClassID  [inline]
//   [x] 0x9ca6f8  CKS08MenuStatsUpgrades_vfB8  [inline]
//   [x] 0x9ca700  CKS08MenuStatsUpgrades_vfE0  [inline]
//   [x] 0x9ca708  CKS08MenuStatsUpgrades_vfC4  [inline]
//   [x] 0x9ca710  CKS08MenuStatsUpgrades_vfC8  [inline]
//   [x] 0x9ca720  CKS08MenuStatsUpgrades_vfCC  [inline]
//   [x] 0x9ca730  CKS08MenuStatsUpgrades_vfBC  [inline]
//   [x] 0x9ca738  CKS08MenuStatsUpgrades_vfC0  [inline]
//   [x] 0x9ca748  CKS08MenuStatsUpgrades_GetWidgetSlotCount  [inline]
//   [x] 0x9ca750  CKS08MenuStatsUpgrades_GetWidgetSlots  [inline]
//   [ ] 0x9ca760  CKS08MenuStatsUpgrades_vfF0  [inline]
//   [ ] 0x9ca768  CKS08MenuStatsUpgrades_vfF4  [inline]
//   [ ] 0x9ca770  CKS08MenuStatsUpgrades_vfE4  [inline]
//   [x] 0x9ca778  CKS08MenuStatsUpgrades_vf84  [inline]
//   [x] 0x9ca780  CKS08MenuStatsUpgrades_vf88  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsUpgrades.h"

#include <cstring>

#include "k2000/io/IKFile.h"

// 0x0056ba30 CKS08MenuStatsUpgrades_Load: no type test of its own.
int32_t CKS08MenuStatsUpgrades::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    // Clear the group's dynamic references [m_unk04, m_unk08) and its first m_unk08 states (signed test).
    RefGroup* group = Vf88();
    GroupState* states = Vf90(0);
    const int32_t dynamic = static_cast<int32_t>(group->m_unk08 - group->m_unk04);
    if (dynamic > 0) {
        std::memset(Vf8C(0) + group->m_unk04, 0, static_cast<uint32_t>(dynamic) * sizeof(IKSerializable*));
    }
    if (states != nullptr) std::memset(states, 0, group->m_unk08 * sizeof(GroupState));
    Vf88()->m_unk0c = 0;
    ReadRaw(file, &m_unk178, 4);
    ReadRaw(file, &m_unk17c, 4);
    IKFile_ReadRef(file, &m_pUnk268);
    return 1;
}
