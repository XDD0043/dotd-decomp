// CKNode2dFx.cpp - reconstructed original translation unit 0x1d84f0-0x1d8898 (GAME_TOC1, main_toc1), 10 functions, 9 live.
// Primary owner: CKNode2dFx (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1d84f0  CKNode2dFx_ConstructBase_2  [dead]
//   [x] 0x1d8508  CKNode2dFx_ClearReferences  (IKNode2dFx::Destroy, IKNode2dFx.h)
//   [x] 0x1d8518  CKNode2dFx_LevelReset  (IKNode2dFx::RecursiveRegistration, IKNode2dFx.h)
//   [x] 0x1d8570  CKNode2dFx_ShowSceneNode
//   [x] 0x1d85a8  CKNode2dFx_Load
//   [ ] 0x1d8688  CKNode2dFx_Save
//   [x] 0x1d8768  CKNode2dFx_StopAndRelease
//   [x] 0x1d8808  CKNode2dFx_HideSceneNode
//   [x] 0x1d8840  CKNode2dFx_ConstructBase
//   [x] 0x1d8858  CKNode2dFx_ReleaseReservation
//
//   [ ] 0x9abe48  CKNode2dFx_SetDataAndOwner  [inline]
//   [ ] 0x9abea0  CKNode2dFx_Interrupt_maybe  [inline]
//   [ ] 0x9abea8  CKNode2dFx_OnPause  [inline]
//   [ ] 0x9abee8  CKNode2dFx_OnResume  [inline]
//   [ ] 0x9abf28  CKNode2dFx_SetUpdateWhenPaused  [inline]
//   [ ] 0x9abf30  CKNode2dFx_GetUpdateWhenPaused  [inline]
//   [ ] 0x9ad948  CKNode2dFx_IsKindOf  [inline]
//   [x] 0x9ad970  CKNode2dFx_GetClassGroup  [inline]
//   [x] 0x9ad978  CKNode2dFx_GetClassId  [inline]
//   [x] 0x9ad980  CKNode2dFx_Stop  [inline]
//   [ ] 0x9ad998  CKNode2dFx_Update  [inline]
//   [x] 0x9ad9a0  CKNode2dFx_Start  [inline]
//   [ ] 0x9ad9c0  CKNode2dFx_Destruct  [inline]
//   [ ] 0x9ad9e0  CKNode2dFx_DeletingDestruct  [inline]
#include "k2000/fx/IKNode2dFx.h"

#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/ui/IKNode2d.h"

// 0x001d8840 CKNode2dFx_ConstructBase
IKNode2dFx::IKNode2dFx() { m_pNode = nullptr; }

// 0x001d85a8 CKNode2dFx_Load. No type check.
int32_t IKNode2dFx::Load(IKFile* file, int32_t type) {
    IKFx::Load(file, type);
    IKFile_ReadRef(file, &m_pNode);
    return 1;
}

// 0x001d8570 CKNode2dFx_ShowSceneNode
void IKNode2dFx::Vf5C() {
    static_cast<CScene2d*>(g_pEngine->m_manager2d->m_unkA68)->AddChild(static_cast<IKNode2d*>(m_pNode));  // 0x65468
}

// 0x001d8808 CKNode2dFx_HideSceneNode
void IKNode2dFx::Vf60() {
    static_cast<CScene2d*>(g_pEngine->m_manager2d->m_unkA68)->RemoveChild(static_cast<IKNode2d*>(m_pNode));  // 0x650d8
}
