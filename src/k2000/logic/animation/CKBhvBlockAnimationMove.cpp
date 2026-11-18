// CKBhvBlockAnimationMove.cpp - reconstructed original translation unit 0x5c2868-0x5c3088 (GAME_TOC2, main_toc2), 18 functions, 18 live.
// Primary class: CKBhvBlockAnimationMove  key 0x9d4c  category Logic  size ?  vtable 0xb2fbd0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c2868  CKBhvBlockAnimationMove_Delete
//   [x] 0x5c28b8  CKBhvBlockAnimationMove_vf68  (Leave, CKBhvBlockAnimationMove.h: empty)
//   [ ] 0x5c28c0  RegisterCKBhvBlockAnimationMoveClass
//   [ ] 0x5c2938  _GLOBAL__I_5c2938
//   [x] 0x5c2948  CKBhvBlockAnimationMove_Start_maybe  (Enter)
//   [ ] 0x5c29c0  CKBhvBlockAnimationMove_Save
//   [x] 0x5c29e8  CKBhvBlockAnimationMove_RecursiveRegistration  (KBase9C8C_vf24: returns 1; the default slot)
//   [x] 0x5c2a10  CKBhvBlockAnimationMove_Destroy  (the base's KStub_Nop_5c57c0: the default slot)
//   [x] 0x5c2a38  CKBhvBlockAnimationMove_DeletingDestructor  (the destructor; delete)
//   [x] 0x5c2a80  CKBhvBlockAnimationMove_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5c2ab0  CKBhvBlockAnimationMove_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5c2ae0  CKBhvBlockAnimationMove_Construct_2  (the constructor, CKBhvBlockAnimationMove.h)
//   [x] 0x5c2b18  CKBhvBlockAnimationMove_Construct  (the constructor, CKBhvBlockAnimationMove.h)
//   [x] 0x5c2b50  CKBhvBlockAnimationMove_DeleteArray
//   [x] 0x5c2bf8  CKBhvBlockAnimationMove_Update
//   [x] 0x5c2e28  CKBhvBlockAnimationMove_Create
//   [x] 0x5c2e80  CKBhvBlockAnimationMove_CreateArray
//   [x] 0x5c2f38  CKBhvBlockAnimationMove_Load
//
//   [ ] 0x9cd3c0  CKBhvBlockAnimationMove_IsKindOfClass  [inline]
//   [ ] 0x9cd3f8  CKBhvBlockAnimationMove_GetClassType  [inline]
//   [ ] 0x9cd400  CKBhvBlockAnimationMove_GetClassID  [inline]
#include "k2000/logic/animation/CKBhvBlockAnimationMove.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/KBase9CCC.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {
KBase9CCC* User(IKSerializable* user) { return static_cast<KBase9CCC*>(user); }
uint32_t FirstWord(IKSerializable* dictionary) {
    return static_cast<uint32_t>(static_cast<CAnimationDictionary*>(dictionary)->m_apAnimations[0]);
}
}  // namespace

// 0x005c2f38 CKBhvBlockAnimationMove_Load
int32_t CKBhvBlockAnimationMove::Load(IKFile* file, int32_t type) {
    KBase9C8C::Load(file, type);  // 0x005c57b0
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUser);
        IKFile_ReadRef(file, &m_pDictionary);
    }
    return 1;
}

// 0x005c2948 CKBhvBlockAnimationMove_Start_maybe
void CKBhvBlockAnimationMove::Enter(IKSerializable* /*user*/) {
    const uint32_t word = FirstWord(m_pDictionary);
    if (CAnimationManager_GetAnimation(word) == nullptr) return;  // cmpwi word, 0 (dotd keeps the words)
    CAnimatedNode* node = static_cast<CAnimatedNode*>(User(m_pUser)->GetAnimatedNode());  // vt+0x54
    node->PlayAnim(0.0, word, 0);  // 0x000c98b8 (TOC2 -0x60ac 0.0)
}

// 0x005c2bf8 CKBhvBlockAnimationMove_Update
void CKBhvBlockAnimationMove::Update(IKTime* clock) {
    if (CAnimationManager_GetAnimation(FirstWord(m_pDictionary)) == nullptr) return;
    const float dt = clock->m_afDeltaTime[0];
    if (static_cast<CAnimatedNode*>(User(m_pUser)->GetAnimatedNode())->IsAnimEndReached(dt)) {  // 0x000ca368
        CAnimatedNode* node = static_cast<CAnimatedNode*>(User(m_pUser)->GetAnimatedNode());
        CAnimatedNode* same = static_cast<CAnimatedNode*>(User(m_pUser)->GetAnimatedNode());
        node->SetCurrentAnimTime(same->GetCurrentAnimDuration());  // 0x000c9690 / 0x000c9768
        CVector3 position;
        static_cast<CSGHotSpot*>(User(m_pUser)->GetHotSpot())->GetWorldPosition(&position);  // vt+0x60; 0x000ce790
        CSGMovable* movable = static_cast<CSGMovable*>(User(m_pUser)->GetMovable());  // vt+0x58
        RwFrame* frame = movable->m_pRwFrame;
        frame->modelling.pos.z = position.z;
        frame->modelling.pos.x = position.x;
        frame->modelling.pos.y = position.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        User(m_pUser)->OnBlockDone(this);  // vt+0x64
        return;
    }
    static_cast<CAnimatedNode*>(User(m_pUser)->GetAnimatedNode())->AddAnimTime(dt);  // 0x000c9638
}
