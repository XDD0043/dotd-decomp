// CKS08MenuLanguage.cpp - reconstructed original translation unit 0x556840-0x5572b8 (GAME_TOC2, main_toc2), 18 functions, 16 live.
// Primary class: CKS08MenuLanguage  key 0x81cc  category Logic  size ?  vtable 0xb2c868
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x556840  CKS08MenuLanguage_Delete
//   [ ] 0x556890  CKS08MenuLanguage_Construct  [dead]
//   [x] 0x556938  CKS08MenuLanguage_vfE8
//   [x] 0x556970  CKS08MenuLanguage_OnMenuState_maybe
//   [x] 0x556a58  CKS08MenuLanguage_Load
//   [ ] 0x556a80  CKS08MenuLanguage_Save
//   [ ] 0x556aa8  CKS08MenuLanguage_RecursiveRegistration
//   [ ] 0x556ad0  CKS08MenuLanguage_Destroy
//   [x] 0x556af8  CKS08MenuLanguage_DeleteArray
//   [ ] 0x556b98  RegisterCKS08MenuLanguageClass
//   [ ] 0x556c20  _GLOBAL__D_556c20
//   [ ] 0x556c30  _GLOBAL__I_556c30
//   [ ] 0x556c40  CKS08MenuLanguage_Construct_2  [dead]
//   [x] 0x556ce8  CKS08MenuLanguage_CreateArray
//   [x] 0x556e28  CKS08MenuLanguage_Create
//   [ ] 0x556f10  CKS08MenuLanguage_Destructor_2
//   [ ] 0x557048  CKS08MenuLanguage_DeletingDestructor
//   [ ] 0x557180  CKS08MenuLanguage_Destructor
//
//   [x] 0x9c9b98  CKS08MenuLanguage_IsKindOfClass  [inline]
//   [x] 0x9c9bd8  CKS08MenuLanguage_GetClassType  [inline]
//   [x] 0x9c9be0  CKS08MenuLanguage_GetClassID  [inline]
//   [x] 0x9c9be8  CKS08MenuLanguage_vfB8  [inline]
//   [x] 0x9c9bf0  CKS08MenuLanguage_vfE0  [inline]
//   [x] 0x9c9bf8  CKS08MenuLanguage_vfC4  [inline]
//   [x] 0x9c9c00  CKS08MenuLanguage_vfC8  [inline]
//   [x] 0x9c9c10  CKS08MenuLanguage_vfCC  [inline]
//   [x] 0x9c9c20  CKS08MenuLanguage_vfBC  [inline]
//   [x] 0x9c9c28  CKS08MenuLanguage_vfC0  [inline]
//   [x] 0x9c9c38  CKS08MenuLanguage_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuLanguage.h"

#include "k2000/misc/Engine.h"

#include "k2000/managers/CKInput.h"

#include "Spyro2008/logic/CKS08GameManager.h"

// 0x00556a58 CKS08MenuLanguage_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuLanguage::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// 0x00556938 CKS08MenuLanguage_vfE8
void CKS08MenuLanguage::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (phase != 2 || item != 1 || state != 4) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    manager->m_unkAFC = (manager->m_unkAFC & ~1u) | 1u;
}

// 0x00556970 CKS08MenuLanguage_OnMenuState_maybe
uint8_t CKS08MenuLanguage::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 2) {
        static_cast<CDefaultGameManager*>(m_pGameManager)->RevertOptions();
    } else if (phase == 1 || (phase == 0 && (g_pEngine->m_input->m_unk148 & 1) != 0)) {
        m_unkb8 = 0;
    }
    return static_cast<uint8_t>(GetMenuId());
}
