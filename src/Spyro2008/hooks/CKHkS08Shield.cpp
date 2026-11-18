// CKHkS08Shield.cpp - reconstructed original translation unit 0x2ac320-0x2acb08 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKHkS08Shield  key 0x2f82  category Hook  size 0x24  vtable 0xb222c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2ac320  CKHkS08Shield_Delete
//   [x] 0x2ac370  CKHkS08Shield_Destroy  (empty: the default)
//   [x] 0x2ac378  CKHkS08Shield_Start  (empty: IKHook's)
//   [x] 0x2ac380  CKHkS08Shield_Pause  (empty: IKHook's)
//   [x] 0x2ac388  CKHkS08Shield_Resume  (empty: IKHook's)
//   [x] 0x2ac390  CKHkS08Shield_Update  (empty: IKHook's)
//   [x] 0x2ac398  CKHkS08Shield_vfC0
//   [x] 0x2ac3a0  CKHkS08Shield_vfCC
//   [x] 0x2ac3a8  CKHkS08Shield_PostLoad
//   [x] 0x2ac400  CKHkS08Shield_Load
//   [ ] 0x2ac488  CKHkS08Shield_Save
//   [x] 0x2ac508  CKHkS08Shield_RecursiveRegistration  (IKHook's: inherited)
//   [x] 0x2ac530  CKHkS08Shield_DeleteArray
//   [x] 0x2ac5d8  CKHkS08Shield_Create
//   [ ] 0x2ac640  RegisterCKHkS08ShieldClass
//   [ ] 0x2ac6c8  _GLOBAL__D_2ac6c8
//   [ ] 0x2ac6d8  _GLOBAL__I_2ac6d8
//   [x] 0x2ac6e8  CKHkS08Shield_TakeFromPool_maybe
//   [x] 0x2ac840  CKHkS08Shield_Stop
//   [x] 0x2ac900  CKHkS08Shield_ReturnToPool_maybe
//   [x] 0x2aca30  CKHkS08Shield_CreateArray
//   [x] 0x2acb00  CKHkS08Shield_MessageProc  (returns 1: the default)
//
//   [ ] 0x9bc9a8  CKHkS08Shield_IsKindOfClass  [inline]
//   [ ] 0x9bc9f0  CKHkS08Shield_GetClassType  [inline]
//   [ ] 0x9bc9f8  CKHkS08Shield_GetClassID  [inline]
//   [ ] 0x9bca00  CKHkS08Shield_Destructor  [inline]
//   [ ] 0x9bca20  CKHkS08Shield_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08Shield.h"

#include "k2000/io/IKFile.h"

#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x0001d5c0 Group_TransferHook_maybe (CKCoreManager.cpp; CKHkS08Enemy_xforkB.cpp).
void GroupTransferHook(CKCoreManager* core, IKHook* hook, IKBaseGroup* to, IKBaseGroup* from, uint32_t flags);

// 0x002ac400 CKHkS08Shield_Load: IKHook's part, then one word whatever the type.
int32_t CKHkS08Shield::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    ReadU32LE(file, &m_unk20);
    return 1;
}

// 0x002ac3a8 CKHkS08Shield_PostLoad
int32_t CKHkS08Shield::PostLoad(int32_t type) {
    PostLoadLife(type);  // 0x00019f68 IKLife_PostLoad
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    return 1;
}

// 0x002ac840 CKHkS08Shield_Stop
void CKHkS08Shield::Stop() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    CSGBranch* root = static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
    if (static_cast<IKSerializable*>(node->m_pParent) == static_cast<IKSerializable*>(root)) return;
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    root->AddChild(static_cast<CSGLeaf*>(m_pKGLObject));                 // vt+0x70
}

// 0x002ac6e8 CKHkS08Shield_TakeFromPool_maybe
void CKHkS08Shield::TakeFromPool() {
    CKCoreManager* core = g_pEngine->m_coreManager;  // +0x2c
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    IKBaseGroup* pool = static_cast<IKBaseGroup*>(enemies->m_vUnk19c.m_pBlock[m_unk20]);
    IKBaseGroup* shields = static_cast<IKBaseGroup*>(enemies->m_pUnk1ac);
    for (IKHook* hook = *reinterpret_cast<IKHook**>(pool->GetMemberListHead()); hook != nullptr; hook = hook->m_pNextHook) {
        if (hook == this) {
            GroupTransferHook(core, this, shields, static_cast<IKBaseGroup*>(enemies->m_vUnk19c.m_pBlock[m_unk20]), 0);
            break;
        }
    }
    SetObjectActiveInContext(core, this, 1, shields);  // 0x0001cb10
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties &= 0xfffffffbu;
}

// 0x002ac900 CKHkS08Shield_ReturnToPool_maybe
void CKHkS08Shield::ReturnToPool() {
    CKCoreManager* core = g_pEngine->m_coreManager;  // +0x2c
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    IKBaseGroup* shields = static_cast<IKBaseGroup*>(enemies->m_pUnk1ac);
    SetObjectActiveInContext(core, this, 0, shields);  // 0x0001cb10
    for (IKHook* hook = *reinterpret_cast<IKHook**>(shields->GetMemberListHead()); hook != nullptr; hook = hook->m_pNextHook) {
        if (hook == this) {
            GroupTransferHook(core, this, static_cast<IKBaseGroup*>(enemies->m_vUnk19c.m_pBlock[m_unk20]), shields, 0);
            break;
        }
    }
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
}
