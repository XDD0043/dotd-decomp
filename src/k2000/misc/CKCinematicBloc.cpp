// CKCinematicBloc.cpp - reconstructed original translation unit 0x18edd8-0x18fc20 (GAME_TOC1, main_toc1), 14 functions, 12 live.
// Primary owner: CKCinematicBloc (not a registered class)
// Other owners: CKCinematicNodeBase (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18edd8  CKCinematicBloc_Load
//   [ ] 0x18f100  CKCinematicBloc_Save
//   [x] 0x18f438  IKCinematicElement_Construct
//   [x] 0x18f450  CKCinematicBloc_AdvanceActorAnim
//   [x] 0x18f540  CKCinematicBloc_GetActorAnimTime_maybe
//   [x] 0x18f5f0  CKCinematicBloc_GetActorCurrentAnim_maybe
//   [x] 0x18f6a0  CKCinematicBloc_IsActorAnimEndReached
//   [x] 0x18f7d0  CKCinematicBloc_PlayActorAnim
//   [x] 0x18f900  CKCinematicBloc_CrossfadeActorAnim
//   [ ] 0x18fa08  FUN_0018fa08  [dead]
//   [ ] 0x18fad8  IKCinematicElement_Construct_2  [dead]
//   [x] 0x18faf0  KStub_Return1_18faf0  (IKCinematicElement GetInfo vt+0x40: returns 1, the default slot)
//   [x] 0x18faf8  IKCinematicElement_MessageProc
//   [x] 0x18fc18  KStub_Return1_18fc18  (IKCinematicElement PostLoad vt+0x30: returns 1, the default slot)
//
//   [ ] 0x9aa5f8  IKCinematicElement_DeletingDestructor  [inline]
//   [ ] 0x9aa638  IKCinematicElement_vf0  [inline]
//   [ ] 0x9aa650  KStub_Return0_9aa650  [inline]
#include "k2000/misc/IKCinematicBloc.h"

#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"

// 0x0018edd8 CKCinematicBloc_Load (XXL2 IKCinematicBloc::BasicLoadCinematicElement)
int32_t IKCinematicBloc::BasicLoadCinematicElement(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU16LE(file, &m_ui16StartElementsFirstIndex);
        ReadU16LE(file, &m_ui16InterruptElementsFirstIndex);
        ReadU16LE(file, &m_ui16ElementsNumber);
        IKFile_ReadRef(file, &m_pElementData);
        IKFile_ReadRef(file, &m_pParentGroup);
        ReadU32LE(file, &m_DataFlags);
        IKFile_ReadRef(file, &m_pSekensElement);
        ReadF32LE(file, &m_fBlendingValue);
        IKFile_ReadRef(file, &m_pRelatedScene);
    }
    m_DataFlags &= 0xfffffffau;
    return 1;
}

// 0x0018f438 IKCinematicElement_Construct
IKCinematicElement::IKCinematicElement() {
    m_pRelatedScene = nullptr;
    m_pNext = nullptr;
}

namespace {

// The actor's hook, its animation node and its blend slot (null when the node animates through a single controller).
struct ActorAnim {
    CAnimatedNode* m_pNode;
    AnimBlendSlot* m_pSlot;
    uint32_t m_ui32Handle;
};

ActorAnim ActorOf(const CKCinematicSceneData* data, int32_t index) {
    IKHook* hook = static_cast<IKHook*>(data->m_pHook);
    ActorAnim actor;
    actor.m_pNode = static_cast<CAnimatedNode*>(hook->m_pKGLObject);
    // The original's buffer has room for 25 slots; the hero (CKHkS08Hero_GetCinematicAnimSlots) writes two, the first is
    // the one played. The original leaves the count unset for a node whose blend mode is 0 or 3; 0 here (the node's path).
    AnimBlendSlot* slots[2] = {nullptr, nullptr};
    int32_t count = 0;
    hook->GetBlendSlot(slots, &count);  // vt+0xbc
    actor.m_pSlot = count == 0 ? nullptr : slots[0];
    actor.m_ui32Handle = index >= 0 ? static_cast<uint32_t>(static_cast<const CAnimationDictionary*>(data->m_pAnimDico)->m_apAnimations[index]) : 0u;
    return actor;
}

CKAnmKeyFrameController* SlotController(AnimBlendSlot* slot) {
    return static_cast<CKAnmKeyFrameController*>(static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10]);
}

}  // namespace

// 0x0018faf8 IKCinematicElement_MessageProc
int32_t IKCinematicElement::ElementMessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x500) {
        if ((m_DataFlags & 1) != 0) return 0;
        if ((m_pRelatedScene->m_baData & 1) == 0) return 0;
        PreActivate();  // vt+0x58
        static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic)->ActivateNode(nullptr, this);  // 0x00167940
        return 0;
    }
    if (message == 0x501) {
        if ((m_DataFlags & 1) != 0) Stop();  // vt+0x6c
        return 0;
    }
    return 1;
}

// 0x0018f450 CKCinematicBloc_AdvanceActorAnim
void IKCinematicBloc::AdvanceActorAnim(double dt) {
    const ActorAnim actor = ActorOf(static_cast<CKCinematicSceneData*>(m_pElementData), -1);
    if (actor.m_pSlot == nullptr) {
        actor.m_pNode->AddAnimTime(dt);
        return;
    }
    CKAnmKeyFrameController* controller = SlotController(actor.m_pSlot);
    controller->m_unk50 = static_cast<float>(dt) + controller->m_unk50;
    actor.m_pSlot->AdvanceInactiveTrack(dt);  // vt+0x10
}

// 0x0018f540 CKCinematicBloc_GetActorAnimTime_maybe
double IKCinematicBloc::GetActorAnimTime() {
    const ActorAnim actor = ActorOf(static_cast<CKCinematicSceneData*>(m_pElementData), -1);
    if (actor.m_pSlot != nullptr) return static_cast<double>(SlotController(actor.m_pSlot)->GetEvaluatedTime());
    return static_cast<double>(actor.m_pNode->GetCurrentAnimTime());
}

// 0x0018f5f0 CKCinematicBloc_GetActorCurrentAnim_maybe
uint32_t IKCinematicBloc::GetActorCurrentAnim() {
    const ActorAnim actor = ActorOf(static_cast<CKCinematicSceneData*>(m_pElementData), -1);
    if (actor.m_pSlot != nullptr) return SlotController(actor.m_pSlot)->GetEvaluatedAnimWord();  // +0x5c
    return actor.m_pNode->GetActiveAnim();
}

// 0x0018f6a0 CKCinematicBloc_IsActorAnimEndReached
bool IKCinematicBloc::IsActorAnimEndReached(double dt) {
    const ActorAnim actor = ActorOf(static_cast<CKCinematicSceneData*>(m_pElementData), -1);
    if (actor.m_pSlot != nullptr) return SlotController(actor.m_pSlot)->HasEnded(static_cast<float>(dt));
    return actor.m_pNode->IsAnimEndReached(dt);
}

// 0x0018f7d0 CKCinematicBloc_PlayActorAnim
void IKCinematicBloc::PlayActorAnim(double start, int32_t index) {
    const ActorAnim actor = ActorOf(static_cast<CKCinematicSceneData*>(m_pElementData), index);
    if (actor.m_pSlot != nullptr) {
        AnimBlendSlot* slot = actor.m_pSlot;
        slot->m_unk14 = 0;
        if (slot->m_pController != nullptr) {
            static_cast<CKBlenderController*>(slot->m_pController)->m_unk58 = slot->m_unk10 != 0 ? 1.0f : 0.0f;
        }
        SlotController(slot)->SetAnim(static_cast<float>(start), actor.m_ui32Handle, false);
        return;
    }
    actor.m_pNode->PlayAnim(start, actor.m_ui32Handle, 0);
}

// 0x0018f900 CKCinematicBloc_CrossfadeActorAnim
void IKCinematicBloc::CrossfadeActorAnim(double blend, double start, int32_t index, uint32_t mode) {
    const ActorAnim actor = ActorOf(static_cast<CKCinematicSceneData*>(m_pElementData), index);
    if (actor.m_pSlot == nullptr) {
        actor.m_pNode->CrossfadeToAnim(blend, start, actor.m_ui32Handle, mode);
        return;
    }
    actor.m_pSlot->CrossfadeToAnim(blend, start, actor.m_ui32Handle, mode);
}
