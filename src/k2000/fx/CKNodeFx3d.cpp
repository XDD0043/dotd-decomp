// CKNodeFx3d.cpp - reconstructed original translation unit 0x1d8898-0x1d8bf0 (GAME_TOC1, main_toc1), 13 functions, 11 live.
// Primary owner: CKNodeFx3d (not a registered class)
// Other owners: CKSrvFxParticlesAccessor (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d8898  CKNodeFx3d_ConstructBase
//   [x] 0x1d88b0  CKNodeFx3d_ClearReferences
//   [x] 0x1d88c0  CKNodeFx3d_LevelReset  (IKNodeFx::RecursiveRegistration, by P06)
//   [x] 0x1d8918  CKNodeFx3d_ShowSceneNode
//   [x] 0x1d8940  CKNodeFx3d_Load
//   [ ] 0x1d8a20  CKNodeFx3d_Save
//   [ ] 0x1d8b00  CKNodeFx3d_ConstructBase_2  [dead]
//   [x] 0x1d8b18  CKNodeFx3d_HideSceneNode
//   [x] 0x1d8b48  CKNodeFx3d_PostLoad
//   [x] 0x1d8b50  CKSrvFxParticlesAccessor_Delete  (DOTD_DECLARE_FACTORIES, CKSrvFxParticlesAccessor.h)
//   [x] 0x1d8ba0  CKSrvFxParticlesAccessor_vf50  (CKSrvFxParticlesAccessor.h)
//   [x] 0x1d8ba8  CKSrvFxParticlesAccessor_vf54  (CKSrvFxParticlesAccessor.h)
//   [ ] 0x1d8bb0  FUN_001d8bb0  [dead]
//
//   [ ] 0x9ab4a8  CKNodeFx3d_SetDataAndOwner  [inline]
//   [ ] 0x9ab500  CKNodeFx3d_Interrupt_maybe  [inline]
//   [ ] 0x9ab508  CKNodeFx3d_OnPause  [inline]
//   [ ] 0x9ab510  CKNodeFx3d_OnResume  [inline]
//   [ ] 0x9ab518  CKNodeFx3d_SetUpdateWhenPaused  [inline]
//   [ ] 0x9ab520  CKNodeFx3d_GetUpdateWhenPaused  [inline]
//   [ ] 0x9ab580  CKNodeFx3d_StopAndRelease  [inline]
//   [ ] 0x9ab620  CKNodeFx3d_ReleaseReservation  [inline]
//   [ ] 0x9ada28  CKNodeFx3d_IsKindOf  [inline]
//   [x] 0x9ada50  CKNodeFx3d_GetClassGroup  [inline]
//   [x] 0x9ada58  CKNodeFx3d_GetClassId  [inline]
//   [x] 0x9ada60  CKNodeFx3d_Start  [inline]
//   [ ] 0x9ada70  CKNodeFx3d_Update  [inline]
//   [ ] 0x9ada78  CKNodeFx3d_Stop  [inline]
//   [ ] 0x9ada90  CKNodeFx3d_DeletingDestruct  [inline]
//   [ ] 0x9adad8  CKNodeFx3d_Destruct  [inline]
#include "k2000/fx/IKNodeFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CNode.h"

// 0x001d88c0 CKNodeFx3d_RecursiveRegistration (C2.8 port-all P06: the node effects' registrations call it)
void IKNodeFx::RecursiveRegistration(int32_t type) {
    if (m_pNode != nullptr) m_pNode->RecursiveRegistration(type);  // vt+0x24
}

// 0x001d8898 CKNodeFx3d_ConstructBase
IKNodeFx::IKNodeFx() { m_pNode = nullptr; }

// 0x001d8918 CKNodeFx3d_ShowSceneNode (vt+0x5c): the node's flags bit 2 (hidden) cleared.
void IKNodeFx::Vf5C() {
    if (m_pNode == nullptr) return;
    m_pNode->m_sgProperties &= 0xfffffffbu;
}

// 0x001d8b18 CKNodeFx3d_HideSceneNode (vt+0x60): the node's flags bit 2 (hidden) set.
void IKNodeFx::Vf60() {
    if (m_pNode == nullptr) return;
    m_pNode->m_sgProperties = (m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
}

// 0x001d8940 CKNodeFx3d_Load. No type check.
int32_t IKNodeFx::Load(IKFile* file, int32_t type) {
    IKFx::Load(file, type);
    IKFile_ReadRef(file, &m_pNode);
    return 1;
}
