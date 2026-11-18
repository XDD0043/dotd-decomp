// CMenuManager.cpp - reconstructed original translation unit 0x64208-0x649d8 (GAME_TOC1, main_toc1), 20 functions, 11 live.
// Primary class: CMenuManager  key 0x44d  category Graphical  size 0x10  vtable 0xb15c20
// Other owners: DrawActiveUIMenu (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x64208  CMenuManager_Delete
//   [ ] 0x64258  CMenuManager_Construct  [dead]
//   [ ] 0x64278  CMenuManager_Construct_2  [dead]
//   [x] 0x64298  CMenuManager_Destroy
//   [ ] 0x642a8  CMenuManager_Enable  [dead]
//   [ ] 0x642b8  CMenuManager_Disable  [dead]
//   [x] 0x642c8  DrawActiveUIMenu
//   [x] 0x64328  RegisterCMenuManagerType  (RegisterAllClasses: ClassTable.inc)
//   [ ] 0x643a0  _GLOBAL__I_643a0
//   [ ] 0x643b0  CMenuManager_RemoveChildAt_maybe  [dead]
//   [ ] 0x643e0  CMenuManager_RemoveChild_maybe  [dead]
//   [ ] 0x64410  CMenuManager_AddChild_maybe  [dead]
//   [ ] 0x64440  CMenuManager_FindChildByName_maybe  [dead]
//   [ ] 0x64508  CMenuManager_GetChildAt_maybe  [dead]
//   [x] 0x64538  CMenuManager_BroadcastEvent_maybe
//   [x] 0x64578  CMenuManager_DeleteArray
//   [x] 0x64618  CMenuManager_Create
//   [x] 0x64660  CMenuManager_CreateArray
//   [ ] 0x64708  CMenuManager_Save
//   [x] 0x64880  CMenuManager_Load
//
//   [x] 0x997b50  CMenuManager_GetClassType  [inline]
//   [x] 0x997b58  CMenuManager_GetClassID  [inline]
//   [ ] 0x997b60  CMenuManager_RecursiveRegistration  [inline]
//   [x] 0x997c60  CMenuManager_IsKindOfClass  [inline]
//   [x] 0x997c80  CMenuManager_DeletingDestructor  [inline]
//   [x] 0x997cc0  CMenuManager_Destructor  [inline]
//   [ ] 0x997cd8  KStub_Return2_997cd8  [inline]
#include "k2000/graphical/ui/CMenuManager.h"

#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/io/IKFile.h"

// 0x00064618 CMenuManager_Create, in the original's store order.
CMenuManager::CMenuManager() {
    m_bEnabled = 0;
    m_pMenuSceneContainers = nullptr;
    m_pFlashMessageBox = nullptr;
}

// 0x00064880 CMenuManager_Load
int32_t CMenuManager::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadRef(file, &m_pMenuSceneContainers);
    IKFile_ReadRef(file, &m_pFlashMessageBox);
    ReadU8(file, &m_bEnabled);
    return 1;
}

// 0x000642c8 DrawActiveUIMenu
uint8_t CMenuManager::DrawActiveUIMenu(IKTime* frameClock) {
    const bool enabled = m_bEnabled != 0;
    if (enabled) static_cast<CScene2d*>(m_pMenuSceneContainers)->Render(frameClock);  // vt+0x5c
    return enabled ? 1 : 0;
}

// 0x00064538 CMenuManager_BroadcastEvent_maybe
void CMenuManager::BroadcastEvent(uint8_t event, void* data) {
    if (m_pMenuSceneContainers != nullptr) static_cast<CScene2d*>(m_pMenuSceneContainers)->BroadcastEvent(event, data);
}
