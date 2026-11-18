// CKS08MenuOptionPS3.cpp - reconstructed original translation unit 0x55b9e8-0x55c5b0 (GAME_TOC2, main_toc2), 18 functions, 16 live.
// Primary class: CKS08MenuOptionPS3  key 0xae0c  category Logic  size ?  vtable 0xb2cc88
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x55b9e8  CKS08MenuOptionPS3_Delete
//   [ ] 0x55ba38  CKS08MenuOptionPS3_Construct  [dead]
//   [x] 0x55bae0  CKS08MenuOptionPS3_OnItemEvent
//   [x] 0x55bb90  CKS08MenuOptionPS3_OnMenuState_maybe
//   [x] 0x55bd50  CKS08MenuOptionPS3_Load
//   [ ] 0x55bd78  CKS08MenuOptionPS3_Save
//   [x] 0x55bda0  CKS08MenuOptionPS3_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x55bdc8  CKS08MenuOptionPS3_Destroy  (inherited: CKMenuBase114c::Destroy)
//   [x] 0x55bdf0  CKS08MenuOptionPS3_DeleteArray
//   [ ] 0x55be90  RegisterCKS08MenuOptionPS3Class
//   [ ] 0x55bf18  _GLOBAL__D_55bf18
//   [ ] 0x55bf28  _GLOBAL__I_55bf28
//   [ ] 0x55bf38  CKS08MenuOptionPS3_Construct_2  [dead]
//   [x] 0x55bfe0  CKS08MenuOptionPS3_CreateArray
//   [x] 0x55c120  CKS08MenuOptionPS3_Create
//   [x] 0x55c208  CKS08MenuOptionPS3_Destructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x55c340  CKS08MenuOptionPS3_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x55c478  CKS08MenuOptionPS3_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9c9e88  CKS08MenuOptionPS3_IsKindOfClass  [inline]
//   [x] 0x9c9ec8  CKS08MenuOptionPS3_GetClassType  [inline]
//   [x] 0x9c9ed0  CKS08MenuOptionPS3_GetClassID  [inline]
//   [x] 0x9c9ed8  CKS08MenuOptionPS3_vfB8  [inline]
//   [x] 0x9c9ee0  CKS08MenuOptionPS3_vfE0  [inline]
//   [x] 0x9c9ee8  CKS08MenuOptionPS3_vfC4  [inline]
//   [x] 0x9c9ef0  CKS08MenuOptionPS3_vfC8  [inline]
//   [x] 0x9c9f00  CKS08MenuOptionPS3_vfCC  [inline]
//   [x] 0x9c9f10  CKS08MenuOptionPS3_vfBC  [inline]
//   [x] 0x9c9f18  CKS08MenuOptionPS3_vfC0  [inline]
//   [x] 0x9c9f28  CKS08MenuOptionPS3_vfE4  [inline]
//   [x] 0x9c9f30  CKS08MenuOptionPS3_vfF0  [inline]
//   [x] 0x9c9f38  CKS08MenuOptionPS3_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuOptionPS3.h"

#include "k2000/misc/CKInterfaceButtonBase.h"

#include "Spyro2008/logic/ui/CKS08MenuMain.h"

#include "Spyro2008/logic/CKS08GameManager.h"

// 0x0055bd50 CKS08MenuOptionPS3_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuOptionPS3::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// 0x0055bae0 CKS08MenuOptionPS3_OnItemEvent
void CKS08MenuOptionPS3::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (phase != 1 || state != 4) return;
    if (item == 10) {
        static_cast<CDefaultGameManager*>(m_pGameManager)->ResetEditedOptions();  // vt+0x1d4
        RefreshOptionWidgets();
    } else if (item == 15) {
        static_cast<CDefaultGameManager*>(m_pGameManager)->RefreshOptionsChangedFlag();
        StartTransitionToMenu(6);
    }
}

// 0x0055bb90 CKS08MenuOptionPS3_OnMenuState_maybe
uint8_t CKS08MenuOptionPS3::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        // BUG(original): with no buttons the call goes through null.
        static_cast<CKInterfaceButtonBase*>(m_apButtons.m_ui32NbUsedElt != 0 ? m_apButtons.m_pBlock[0] : nullptr)->Show();
    } else if (phase == 1) {
        PlayScreenVideo(3, 1);
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
        static_cast<CKS08MenuMain*>(manager->Vf344()[9])->PlayEnterSounds();
        RefreshOptionWidgets();
    }
    return static_cast<uint8_t>(GetMenuId());
}
