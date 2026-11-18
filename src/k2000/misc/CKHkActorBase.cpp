// CKHkActorBase.cpp - reconstructed original translation unit: 0x3f6dc0-0x3f7430 (GAME_TOC1, main_toc1), 22 functions, 21 live.
// Primary owner: CKHkActorBase (not a registered class)
// Other owners: KBaseD82 (2), WorldObjectBase (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f6dc0  CKHkActorBase_d82_maybe_Construct
//   [x] 0x3f6e08  CKHkActorBase_d82_maybe_ClearReferences
//   [x] 0x3f6e48  CKHkActorBase_d82_maybe_ResetRuntime
//   [x] 0x3f6e50  CKHkActorBase_d82_maybe_Stop
//   [x] 0x3f6e58  KStub_Nop_3f6e58  (Pause: empty; the hooks' Pause call it, IKHook's empty slot)
//   [x] 0x3f6e60  KStub_Nop_3f6e60  (Resume: empty; the hooks' Resume call it, IKHook's empty slot)
//   [x] 0x3f6e68  WorldObjectBase_Update_Nop  (empty: the hooks Update bodies start with it)
//   [x] 0x3f6e70  CKHkActorBase_d82_maybe_PostLoad
//   [x] 0x3f6e98  CKHkActorBase_d82_maybe_Load
//   [ ] 0x3f6ec0  CKHkActorBase_d82_maybe_Save
//   [x] 0x3f6ee8  CKHkActorBase_d82_maybe_LevelReset  (RecursiveRegistration: IKHook's (inherited), then 1)
//   [x] 0x3f6f10  KBaseD82_vfC4  (CKHkActorBase::HighlightNode)
//   [ ] 0x3f70f8  CKHkActorBase_d82_maybe_Construct_2  [dead]
//   [x] 0x3f7140  KStub_Return1_3f7140  (GetInfo: returns 1, the default slot)
//   [x] 0x3f7148  CKHkActorBase_d82_maybe_MessageProc
//   [x] 0x3f72a0  KStub_Nop_3f72a0
//   [x] 0x3f72a8  KBaseD82_SetGameState
//   [x] 0x3f7338  CKHkActorBase_d82_maybe_OnActivate
//   [x] 0x3f7370  CKHkActorBase_d82_maybe_OnDeactivate
//   [x] 0x3f73a8  CKHkActorBase_d82_maybe_DeletingDestructor  (~CKHkActorBase; delete)
//   [x] 0x3f73f0  CKHkActorBase_d82_maybe_BaseDestructor  (the C++ destructor ~CKHkActorBase)
//   [x] 0x3f7410  CKHkActorBase_d82_maybe_Destructor  (~CKHkActorBase)
//
//   [ ] 0x9c0b70  CKHkActorBase_d82_maybe_IsKindOf  [inline]
//   [ ] 0x9c0bb8  CKHkActorBase_d82_maybe_GetClassGroup  [inline]
//   [ ] 0x9c0bc0  CKHkActorBase_d82_maybe_GetClassId  [inline]
//   [ ] 0x9c0bc8  KStub_Nop_9c0bc8  [inline]
//   [ ] 0x9c0bd0  KStub_Nop_9c0bd0  [inline]
//   [ ] 0x9c0bd8  KStub_Nop_9c0bd8  [inline]
//   [x] 0x9c0be0  KStub_Nop_9c0be0  [inline]  (CKHkActorBase::VfD4)
//   [ ] 0x9c0be8  KStub_Return0_9c0be8  [inline]
//   [ ] 0x9c0bf0  KStub_Return0_9c0bf0  [inline]
//   [ ] 0x9c0bf8  KStub_Return0_9c0bf8  [inline]
//   [ ] 0x9c0c00  KStub_Return0_9c0c00  [inline]
//   [ ] 0x9c0c08  KStub_Return0_9c0c08  [inline]
//   [ ] 0x9c0c10  KStub_Return0_9c0c10  [inline]
//   [x] 0x9c0c18  CKHkActorBase_d82_maybe_SetVisible  [inline]
#include "k2000/misc/CKHkActorBase.h"

#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x003f6e98 CKHkActorBase_d82_maybe_Load: IKHook's part only.
int32_t CKHkActorBase::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    return 1;
}

// 0x003f7148 CKHkActorBase_d82_maybe_MessageProc
int32_t CKHkActorBase::MessageProc(uint16_t message, void* /*data*/) {
    switch (message) {
    case 0x908: SetEnabled(1); return 0;  // vt+0xcc
    case 0x909: SetEnabled(0); return 0;
    case 0x90a: SetVisible(1); return 0;  // vt+0xd0
    case 0x90b: SetVisible(0); return 0;
    case 0x90c: VfD4(1, 0); return 0;     // vt+0xd4
    case 0x90d: VfD4(0, 0); return 0;
    case 0x90e: VfD4(1, 1); return 0;
    case 0x90f: VfD4(0, 1); return 0;
    default: return 1;
    }
}

// 0x003f72a8 KBaseD82_SetGameState. The preset is ((id ^ 1) as |x| - 1) < 0 in the low word: 1 for game state 1 only.
// CKS08GameModule's ApplyLeft / ApplyDone send it at the level start (after the hooks' SetDefaultState), so the hooks
// with a preset (pression stones, doors, spawners, ...) take their saved / designed state from it.
int32_t CKHkActorBase::SetGameState(const SApplyGameState* state) {
    if (state->m_ui32InfoId != 1) return 0;
    ApplyStatePreset(state->m_ui32GameStateId == 1 ? 1 : 0);  // vt+0xc8
    return 1;
}

// 0x009c0c18 CKHkActorBase_d82_maybe_SetVisible
void CKHkActorBase::SetVisible(int32_t visible) {
    if (m_pKGLObject == nullptr) return;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pKGLObject);
    leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | (((static_cast<uint32_t>(visible) ^ 1u) << 2) & 0x3fcu);
}

// 0x003f7338 CKHkActorBase_d82_maybe_OnActivate: the game manager's +0xc (TOC +0x45b4 -> +0x8c) meca group lists the actor.
void CKHkActorBase::VfA0() {
    static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2])->AddActiveActor(this);  // 0x003f80d0
}

// 0x003f7370 CKHkActorBase_d82_maybe_OnDeactivate: the same group drops it.
void CKHkActorBase::VfA4() {
    static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2])->RemoveActiveActor(this);  // 0x003f8508
}

#include "k2000/geometry/CGeometry.h"
#include "k2000/scenegraph/CNode.h"

// 0x003f6f10 KBaseD82_vfC4. The colour's alpha byte (+0x23) is read back after the store, so the bit 11 of +0x14 ("alpha
// byte != 0xff") ends 0 for both colours; a changed bit is stored and the geometry's vt+0x60 called.
void CKHkActorBase::HighlightNode(float value, IKSerializable* node) {
    if (node == nullptr) return;
    if (node->IsKindOfClass(0xcb) != 0) {  // CNode
        const uint8_t green = value == 0.0f ? 0xff : 0x00;
        for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList); geometry != nullptr;
             geometry = geometry->m_pNext) {
            geometry->m_cGeometryColor[0] = 0xff;
            geometry->m_cGeometryColor[1] = green;
            geometry->m_cGeometryColor[2] = green;
            geometry->m_cGeometryColor[3] = 0xff;
            const uint32_t translucent = geometry->m_cGeometryColor[3] != 0xff ? 1u : 0u;
            const uint32_t bits = geometry->m_BitProperties;
            if (((bits >> 11) & 1u) != translucent) {
                geometry->m_BitProperties = (bits & 0xfffff7ffu) | (translucent << 11);
                geometry->UpdateProperties();  // vt+0x60
            }
        }
    }
    if (node->IsKindOfClass(0x24b) != 0) {  // CSGBranch
        for (CSGLeaf* child = static_cast<CSGLeaf*>(static_cast<CSGBranch*>(node)->m_lChildList); child != nullptr;
             child = child->m_pNext) {
            HighlightNode(value, child);  // vt+0xc4
        }
    }
}
