// CKS08MenuArmors.cpp - reconstructed original translation unit 0x541ff8-0x547150 (GAME_TOC1, main_toc1), 30 functions, 19 live.
// Primary class: CKS08MenuArmors  key 0xab8c  category Logic  size 0x1c4  vtable 0xb2c130
// Other owners: SetArmors (1), CKS08MenuChapter (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x541ff8  FUN_00541ff8  [dead]
//   [ ] 0x542220  CKS08MenuArmors_GetFullSetArmorType_maybe  [dead]
//   [ ] 0x542290  FUN_00542290  [dead]
//   [ ] 0x542340  FUN_00542340  [dead]
//   [ ] 0x542390  CKS08MenuArmors_RecursiveRegistration
//   [ ] 0x542428  CKS08MenuArmors_Destroy
//   [x] 0x542488  CKS08MenuArmors_DeleteArray
//   [ ] 0x542528  RegisterCKS08MenuArmorsClass
//   [ ] 0x5425b0  _GLOBAL__D_5425b0
//   [ ] 0x5425c0  _GLOBAL__I_5425c0
//   [ ] 0x5425d0  CKS08MenuArmors_GetFullSetArmorType_2_maybe  [dead]
//   [ ] 0x542638  CKS08MenuArmors_Construct  [dead]
//   [ ] 0x5426e0  FUN_005426e0  [dead]
//   [ ] 0x542798  CKS08MenuArmors_Construct_2  [dead]
//   [x] 0x542840  CKS08MenuArmors_CreateArray
//   [x] 0x542980  CKS08MenuArmors_Create
//   [x] 0x542a68  CKS08MenuArmors_Load
//   [ ] 0x542d10  CKS08MenuArmors_Save
//   [ ] 0x542f00  FUN_00542f00  [dead]
//   [ ] 0x5433c8  FUN_005433c8  [dead]
//   [ ] 0x543898  CKS08MenuArmors_RefreshDragonPanelItems_maybe
//   [ ] 0x544938  CKS08MenuArmors_ToggleActiveDragonPanel_maybe
//   [ ] 0x544bb0  CKS08MenuArmors_HandleSlotInput_maybe
//   [ ] 0x544fb8  CKS08MenuArmors_Destructor
//   [ ] 0x5450f0  CKS08MenuArmors_Destructor_2
//   [ ] 0x545228  CKS08MenuArmors_DeletingDestructor
//   [ ] 0x545360  CKS08MenuArmors_UpdateSlotAnimations_maybe
//   [ ] 0x5468d0  SetArmors
//   [ ] 0x547050  CKS08MenuChapter_Delete
//   [ ] 0x5470a0  FUN_005470a0  [dead]
//
//   [x] 0x9c9618  CKS08MenuArmors_IsKindOfClass  [inline]
//   [x] 0x9c9658  CKS08MenuArmors_GetClassType  [inline]
//   [x] 0x9c9660  CKS08MenuArmors_GetClassID  [inline]
//   [x] 0x9c9668  CKS08MenuArmors_vfB8  [inline]
//   [x] 0x9c9670  CKS08MenuArmors_vfE0  [inline]
//   [x] 0x9c9678  CKS08MenuArmors_GetWidgetSlotCount  [inline]
//   [x] 0x9c9680  CKS08MenuArmors_GetWidgetSlots  [inline]
//   [x] 0x9c9690  CKS08MenuArmors_vfC4  [inline]
//   [x] 0x9c9698  CKS08MenuArmors_vfC8  [inline]
//   [x] 0x9c96a8  CKS08MenuArmors_vfCC  [inline]
//   [x] 0x9c96b8  CKS08MenuArmors_vfBC  [inline]
//   [x] 0x9c96c0  CKS08MenuArmors_vfC0  [inline]
//   [ ] 0x9c96d0  CKS08MenuArmors_vfF0  [inline]
//   [ ] 0x9c96d8  CKS08MenuArmors_vfF4  [inline]
//   [x] 0x9c96e0  CKS08MenuArmors_vf84  [inline]
//   [x] 0x9c96e8  CKS08MenuArmors_vf88  [inline]
#include "Spyro2008/logic/ui/CKS08MenuArmors.h"

#include <cstring>

#include "k2000/io/IKFile.h"

// 0x00542a68 CKS08MenuArmors_Load: no type test of its own.
int32_t CKS08MenuArmors::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    m_unk160[2] = 0;
    m_unk160[0] = 0;
    m_unk160[1] = 0;
    // Clear the group's dynamic references [m_unk04, m_unk08) and its first m_unk08 states (signed test).
    RefGroup* group = Vf88();
    GroupState* states = Vf90(0);
    const int32_t dynamic = static_cast<int32_t>(group->m_unk08 - group->m_unk04);
    if (dynamic > 0) {
        std::memset(Vf8C(0) + group->m_unk04, 0, static_cast<uint32_t>(dynamic) * sizeof(IKSerializable*));
    }
    if (states != nullptr) std::memset(states, 0, group->m_unk08 * sizeof(GroupState));
    Vf88()->m_unk0c = 1;
    IKFile_ReadTextureRef(file, &m_pTexture1b8, 1);
    IKFile_ReadTextureRef(file, &m_pTexture1b4, 1);
    IKFile_ReadRef(file, &m_pText);
    ReadF32LE(file, &m_fUnk174);
    IKFile_ReadRef(file, &m_pSound);
    return 1;
}
