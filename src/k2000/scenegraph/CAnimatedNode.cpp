// CAnimatedNode.cpp - reconstructed original translation unit 0xc8b70-0xcb2c0 (GAME_TOC1, main_toc1), 51 functions, 46 live.
// Primary class: CAnimatedNode  key 0x54b  category SceneNode  size 0x64  vtable 0xb17e60
// Other owners: RpHAnimFrameSetHierarchy (1), RpHAnimHierarchyDetach (1), RwFrameDestroy (1), IKFile (1), UpdateAnimatedNodePoseAndCull (1), PrepareAndEnqueueAnimatedNode (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc8b70  CAnimatedNode_Delete
//   [ ] 0xc8bc0  CAnimatedNode_RecursiveRegistration
//   [ ] 0xc8bc8  CAnimatedNode_Save
//   [ ] 0xc8bd0  CAnimatedNode_vf60
//   [x] 0xc8bd8  CAnimatedNode_GetBoneMatrix
//   [x] 0xc8bf0  CAnimatedNode_GetSubtreeBoneCount
//   [ ] 0xc8c88  RegisterCAnimatedNodeClass
//   [ ] 0xc8d00  _GLOBAL__I_c8d00
//   [ ] 0xc8d10  RpHAnimFrameSetHierarchy_Thunk  [dead]
//   [ ] 0xc8d38  RpHAnimHierarchyDetach_Thunk  [dead]
//   [ ] 0xc8d60  RwFrameDestroy_Field14_Thunk_maybe
//   [ ] 0xc8d88  CAnimatedNode_FrustumTestBoundingSphere_maybe
//   [x] 0xc8e80  CAnimatedNode_SetBlendAnimPairAndWeight_maybe
//   [x] 0xc8eb0  CAnimatedNode_CrossfadeToAnim_maybe
//   [x] 0xc8ef8  IKFile_ReadBoneFrameList
//   [ ] 0xc9150  CAnimatedNode_DetachChild_maybe
//   [x] 0xc9218  CAnimatedNode_AttachChildToGroup_maybe
//   [ ] 0xc92e0  CAnimatedNode_Destroy
//   [ ] 0xc93f8  CAnimatedNode_Construct_2  [dead]
//   [x] 0xc9480  CAnimatedNode_Construct
//   [x] 0xc9508  CAnimatedNode_DeleteArray
//   [x] 0xc95a8  CAnimatedNode_GetCurrentAnimTime_maybe
//   [x] 0xc95f0  CAnimatedNode_GetAnimTimeNow_maybe
//   [x] 0xc9638  CAnimatedNode_AddAnimTime_maybe
//   [x] 0xc9690  CAnimatedNode_SetCurrentAnimTime_maybe
//   [x] 0xc96d8  CAnimatedNode_GetCurrentAnim_maybe
//   [x] 0xc9720  CAnimatedNode_GetActiveAnim_maybe
//   [x] 0xc9768  CAnimatedNode_GetCurrentAnimDuration_maybe
//   [x] 0xc97d8  CAnimatedNode_ResetCurrentAnim_maybe
//   [x] 0xc98b8  CAnimatedNode_PlayAnim_maybe
//   [x] 0xc9978  CAnimatedNode_GetBlendSlot_maybe
//   [ ] 0xc99b8  CAnimatedNode_SetRootController_maybe
//   [ ] 0xc99c0  CAnimatedNode_BaseDestructor
//   [x] 0xc9a08  CAnimatedNode_SetHAnimHierarchy_maybe
//   [ ] 0xc9ab0  CAnimatedNode_UpdateWorldMatrices
//   [x] 0xc9b88  CAnimatedNode_UpdateChildWorldMatrix_maybe
//   [x] 0xc9d48  CAnimatedNode_PostLoad
//   [ ] 0xc9e90  CAnimatedNode_CollectFlaggedChildren_maybe
//   [ ] 0xc9f60  CAnimatedNode_WriteFrameList_maybe
//   [ ] 0xca168  CAnimatedNode_GetWrappedAnimTime_maybe  [dead]
//   [ ] 0xca210  CAnimatedNode_IsAnimStartReached_maybe  [dead]
//   [x] 0xca368  CAnimatedNode_IsAnimEndReached_maybe
//   [x] 0xca4c0  CAnimatedNode_Load
//   [ ] 0xca760  CAnimatedNode_AttachChildToBone_maybe
//   [x] 0xca8a8  CAnimatedNode_RemoveChild_maybe
//   [ ] 0xca978  CAnimatedNode_DeletingDestructor
//   [ ] 0xca9d8  CAnimatedNode_Destructor
//   [x] 0xcaa20  CAnimatedNode_CreateArray
//   [x] 0xcab28  CAnimatedNode_Create
//   [x] 0xcabc8  UpdateAnimatedNodePoseAndCull
//   [x] 0xcb0f0  PrepareAndEnqueueAnimatedNode
//
//   [x] 0x99b448  CAnimatedNode_PlayAnimAtTime_maybe  [inline]
//   [ ] 0x9a2460  CAnimatedNode_IsKindOfClass  [inline]
//   [ ] 0x9a24b8  CAnimatedNode_GetClassType  [inline]
//   [ ] 0x9a24c0  CAnimatedNode_GetClassID  [inline]
#include "k2000/scenegraph/CAnimatedNode.h"

#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rpskin/RpSkin.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/geometry/CSkinGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/IKTime.h"

// 0x000c8ef8 IKFile_ReadBoneFrameList
int32_t IKFile_ReadBoneFrameList(IKFile* file, int32_t /*type*/, RwFrame** rootFrame, RpHAnimHierarchy** hierarchy,
                                 RwFrame* parent) {
    int32_t count = 0;
    ReadS32LE(file, &count);
    if (count <= 0) {
        *hierarchy = nullptr;
        return 1;
    }
    // BUG(original): when the chunk is not found, the uninitialised local list is deinitialised (freed
    // when its garbage count is non-zero). The list starts empty here.
    rwFrameList list = {nullptr, 0};
    if (RwStreamFindChunk(file->m_pRwStream, 0xe, nullptr, nullptr) != 0) {  // rwID_FRAMELIST
        if (_rwFrameListStreamRead(file->m_pRwStream, &list) == nullptr) {
            *rootFrame = nullptr;
            *hierarchy = nullptr;
        } else {
            RwFrame* root = list.frames[0];
            *rootFrame = root;
            RpHAnimHierarchy* h = RpHAnimFrameGetHierarchy(root);
            *hierarchy = h;
            for (int32_t i = 0; i < h->numNodes; ++i) {
                RwMatrix* m = &(*hierarchy)->pMatrixArray[i];
                m->right.x = 1.0f;
                m->at.z = 1.0f;
                m->up.y = 1.0f;
                m->right.y = 0.0f;
                m->up.x = 0.0f;
                m->right.z = 0.0f;
                m->up.z = 0.0f;
                m->at.y = 0.0f;
                m->at.x = 0.0f;
                m->pos.x = 0.0f;
                m->pos.z = 0.0f;
                m->pos.y = 0.0f;
                m->flags |= 0x20003u;
                h = *hierarchy;
            }
            if (parent != nullptr) {
                RwFrameAddChild(parent, *rootFrame);  // inlined in the original
            }
        }
    }
    _rwFrameListDeinitialize(&list);
    return 1;
}

// 0x000c9a08 CAnimatedNode_SetHAnimHierarchy_maybe
void CAnimatedNode::SetHAnimHierarchy(RpHAnimHierarchy* hierarchy, IKSerializable* controller, uint32_t forceUpdate,
                                      uint32_t setOnRootFrame) {
    if (m_pRpHAnimHierarchy != hierarchy || forceUpdate != 0) {
        m_pRpHAnimHierarchy = hierarchy;
        if (setOnRootFrame != 0) RpHAnimFrameSetHierarchy(m_pRootFrame, hierarchy);
        for (CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList); geometry != nullptr; geometry = geometry->m_pNext) {
            CSkinGeometry_SetHAnimHierarchy(geometry, m_pRpHAnimHierarchy);
        }
    }
    m_pController = controller;
}

// 0x000c9d48 CAnimatedNode_PostLoad
int32_t CAnimatedNode::PostLoad(int32_t type) {
    CNode::PostLoad(type);  // 0xcc340
    if (type == 0) {
        // AnimBlendSlot_PostLoadThunk_maybe 0x79d70 (bits 9-10 = 2): KStub_Return1, nothing to do.
        if ((m_sgProperties & 1) != 0) {
            // The first animation: the original replaces the word +0x5c by the animation it names (sector = word >> 24,
            // index = word & 0xffffff in the engine's animation manager; 0 for 0xffffffff) and sets it on the controller
            // (start TOC -0x562c: 0.0f, no restart). dotd keeps the word in +0x5c (an x64 pointer does not fit) and
            // resolves it for the controller (CAnimationManager_GetAnimation).
            if (m_pController != nullptr) {
                static_cast<CKAnmKeyFrameController*>(m_pController)->SetAnim(0.0f, CAnimationManager_GetAnimation(m_unk5c), false);
            }
        }
        for (CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList); geometry != nullptr; geometry = geometry->m_pNext) {
            RpSkinAtomicSetHAnimHierarchy(geometry->m_pRpAtomic, m_pRpHAnimHierarchy);  // 0x772ef8 (inlined bridge)
        }
    }
    return 1;
}

// 0x000c9218 CAnimatedNode_AttachChildToGroup_maybe
void CAnimatedNode::AttachChildToGroup(uint8_t bone, CSGLeaf* child) {
    for (CSGLeaf* entry = m_pAttachmentHead; entry != nullptr; entry = entry->m_pNext) {
        if (child->m_ui8BoneParent == entry->m_ui8BoneParent) {
            child->m_pNext = entry->m_pNext;
            entry->m_pNext = child;
            child->SetParent(this, bone);
            return;
        }
    }
    child->m_pNext = m_pAttachmentHead;
    m_pAttachmentHead = child;
    child->SetParent(this, bone);
}

// 0x000ca8a8 CAnimatedNode_RemoveChild_maybe
void CAnimatedNode::RemoveChild(CSGLeaf* child) {
    if (child->m_ui8BoneParent == 0xff) {
        CSGBranch::RemoveChild(child);
        return;
    }
    CSGLeaf* head = m_pAttachmentHead;
    if (head != nullptr) {
        if (child == head) {
            m_pAttachmentHead = child->m_pNext;
            child->m_pNext = nullptr;
        } else {
            CSGLeaf* prev = head;
            CSGLeaf* cur = prev->m_pNext;
            while (cur != nullptr && cur != child) {
                prev = cur;
                cur = cur->m_pNext;
            }
            if (cur == child) {
                prev->m_pNext = child->m_pNext;
                child->m_pNext = nullptr;
            }
        }
    }
    child->SetParent(nullptr, 0xff);
}

// 0x000c9480 CAnimatedNode_Construct
CAnimatedNode::CAnimatedNode() {
    m_pAttachmentHead = nullptr;
    m_unk5c = 0;
    m_aUnk4c[0] = 0;
    m_aUnk4c[3] = 0;
    m_aUnk4c[2] = 0;
    m_aUnk4c[1] = 0;
    m_unk60 = 1.0f;  // TOC -0x5644
    m_pController = nullptr;
}

// 0x000ca4c0 CAnimatedNode_Load
int32_t CAnimatedNode::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);  // 0xcbd28
    IKFile_ReadRef(file, &m_pAttachmentHead);
    if ((m_sgProperties & 1) == 0) {
        m_unk5c = 0xffffffffu;
    } else {
        ReadU32LE(file, &m_unk5c);
    }
    IKFile_ReadBoneFrameList(file, type, &m_pRootFrame, &m_pRpHAnimHierarchy, m_pRwFrame);
    ReadU32LEWords(file, m_aUnk4c, 4);
    IKFile_ReadRef(file, &m_pController);
    if (((m_sgProperties >> 9) & 3) == 2) AnimBlendSlot_LoadThunk(&m_blendSlot, file, type);
    ReadF32LE(file, &m_unk60);
    return 1;
}

CKAnmKeyFrameController* CAnimatedNode::ActiveController() const {
    if (((m_sgProperties >> 9) & 3) == 1) return static_cast<CKAnmKeyFrameController*>(m_pController);
    return static_cast<CKAnmKeyFrameController*>(
        static_cast<CKBlenderController*>(m_blendSlot.m_pController)->m_apControllers[m_blendSlot.m_unk10]);
}

// 0x000c9978 CAnimatedNode_GetBlendSlot_maybe
void CAnimatedNode::GetBlendSlot(AnimBlendSlot** slot, int32_t* count) {
    const uint32_t mode = (m_sgProperties >> 9) & 3;
    if (mode == 1) {
        *count = 0;
        return;
    }
    if (mode != 2) return;
    *slot = &m_blendSlot;
    *count = 1;
}

// 0x000c9638 CAnimatedNode_AddAnimTime_maybe
void CAnimatedNode::AddAnimTime(double dt) {
    CKAnmKeyFrameController* controller = ActiveController();
    controller->m_unk50 = static_cast<float>(dt) + controller->m_unk50;
}

// 0x000c95a8 CAnimatedNode_GetCurrentAnimTime_maybe: the evaluated time (+0x54).
float CAnimatedNode::GetCurrentAnimTime() const { return ActiveController()->m_unk54; }

// 0x000c95f0 CAnimatedNode_GetAnimTimeNow_maybe: the time (+0x50).
float CAnimatedNode::GetAnimTimeNow() const { return ActiveController()->m_unk50; }

// 0x000c9690 CAnimatedNode_SetCurrentAnimTime_maybe
void CAnimatedNode::SetCurrentAnimTime(float time) { ActiveController()->m_unk50 = time; }

// 0x000c9720 CAnimatedNode_GetActiveAnim_maybe: the evaluated animation (+0x5c, the animation of the last evaluation).
uint32_t CAnimatedNode::GetActiveAnim() const { return ActiveController()->GetEvaluatedAnimWord(); }

// 0x000c96d8 CAnimatedNode_GetCurrentAnim_maybe: the animation (+0x58).
RtAnimAnimation* CAnimatedNode::GetCurrentAnim() const { return ActiveController()->m_unk58; }

// 0x000c9768 CAnimatedNode_GetCurrentAnimDuration_maybe
float CAnimatedNode::GetCurrentAnimDuration() const { return ActiveController()->GetDuration(); }

// 0x000ca368 CAnimatedNode_IsAnimEndReached_maybe
bool CAnimatedNode::IsAnimEndReached(double dt) const { return ActiveController()->HasEnded(static_cast<float>(dt)); }

// 0x000c98b8 CAnimatedNode_PlayAnim_maybe
void CAnimatedNode::PlayAnim(float start, RtAnimAnimation* animation, uint32_t restart) {
    if (((m_sgProperties >> 9) & 3) != 1) {
        m_blendSlot.m_unk14 = 0;
        if (m_blendSlot.m_pController != nullptr) {
            static_cast<CKBlenderController*>(m_blendSlot.m_pController)->m_unk58 = m_blendSlot.m_unk10 != 0 ? 1.0f : 0.0f;
        }
    }
    ActiveController()->SetAnim(start, animation, (restart & 0xff) != 0);
}

void CAnimatedNode::PlayAnim(double start, uint32_t word, uint32_t restart) {
    PlayAnim(static_cast<float>(start), CAnimationManager_GetAnimation(word), restart);
}

// 0x000c8eb0 CAnimatedNode_CrossfadeToAnim_maybe: the node's own blend slot, as a blend (mode 1) or a blend that keeps the
// old controller running (mode 2).
void CAnimatedNode::CrossfadeToAnim(double blend, double start, uint32_t word, uint32_t mode) {
    m_blendSlot.CrossfadeToAnim(blend, start, word, mode == 1 ? 1u : 2u);
}

// 0x000c97d8 CAnimatedNode_ResetCurrentAnim_maybe
void CAnimatedNode::RestartCurrentAnim() {
    if (((m_sgProperties >> 9) & 3) != 1) {
        m_blendSlot.m_unk14 = 0;
        if (m_blendSlot.m_pController != nullptr) {
            static_cast<CKBlenderController*>(m_blendSlot.m_pController)->m_unk58 = m_blendSlot.m_unk10 != 0 ? 1.0f : 0.0f;
        }
    }
    ActiveController()->Reset();  // vt+0x60
}

// 0x000c8e80 CAnimatedNode_SetBlendAnimPairAndWeight_maybe
void CAnimatedNode::SetBlendAnimPairAndWeight(uint32_t word1, uint32_t word2, float start1, float start2, float weight) {
    m_blendSlot.SetAnimPairAndWeight(word1, word2, start1, start2, weight);  // 0x79e10
}

// 0x0099b448 CAnimatedNode_PlayAnimAtTime_maybe (game TOC: the constant -0x69b8 is 0.0f)
uint32_t CAnimatedNode::PlayAnimAtTime(RtAnimAnimation* animation, float time, uint32_t play, uint32_t setTime,
                                       uint32_t reset) {
    if (play != 0) {
        if (animation != nullptr) {
            PlayAnim(0.0f, animation, 1);
        } else {
            if (reset == 0) return 1;
            PlayAnim(0.0f, static_cast<RtAnimAnimation*>(nullptr), 1);
            RestartCurrentAnim();
        }
    }
    if (setTime == 0 || animation == nullptr) return 0;
    if (GetCurrentAnim() == nullptr) return 0;
    if (!(animation->duration >= time)) return 0;
    SetCurrentAnimTime(time);
    return IsAnimEndReached(0.0) ? 0u : 1u;
}

// 0x000c8bd8 CAnimatedNode_GetBoneMatrix
RwMatrix* CAnimatedNode::GetBoneMatrix(uint32_t bone) const { return &m_pRpHAnimHierarchy->pMatrixArray[bone]; }

// 0x000c8bf0 CAnimatedNode_GetSubtreeBoneCount
uint8_t CAnimatedNode::GetSubtreeBoneCount(uint8_t start) const {
    const RpHAnimHierarchy* hierarchy = m_pRpHAnimHierarchy;
    if (hierarchy == nullptr) return 0;
    if (start == 0) return static_cast<uint8_t>(hierarchy->numNodes);  // the low byte (lbz +0x07)
    const RpHAnimNodeInfo* node = &hierarchy->pNodeInfo[start];
    uint32_t count = 1;
    if ((node->flags & rpHANIMPOPPARENTMATRIX) != 0) return 1;
    int32_t depth = 1;
    do {
        ++node;
        ++count;
        depth += ((node->flags >> 1) & 1) - (node->flags & 1);
    } while (depth != 0);
    return static_cast<uint8_t>(count);
}

namespace {
// The frame's own LTM sync bit (4) cleared (lbz +0x03, rlwinm 29 / 3) after its LTM was written; DOTD: and the LTM
// marked as its owner's (RwFrame::dotdLtmOwned).
void LtmWritten(RwFrame* frame) {
    frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & 0xfbu);
    frame->dotdLtmOwned = 1;
}
}  // namespace

// 0x000c9b88 CAnimatedNode_UpdateChildWorldMatrix_maybe
void CAnimatedNode::ChildWorldMatrixUpdate(CSGMovable* child) {
    RwFrame* frame = m_pRwFrame;
    if (m_pParent != nullptr) {
        m_pParent->ChildWorldMatrixUpdate(this);  // vt+0x54
    } else {
        frame->ltm = frame->modelling;
        LtmWritten(frame);
    }
    RwFrame* childFrame = child->m_pRwFrame;
    const uint8_t bone = static_cast<CSGLeaf*>(child)->m_ui8BoneParent;
    if (bone == 0xff || m_ui16LastRenderedFrame == 0) {
        RwMatrixMultiply(&childFrame->ltm, &childFrame->modelling, &m_pRwFrame->ltm);
    } else {
        RwMatrix boneLtm;  // sp+0x70
        RwMatrixMultiply(&boneLtm, &m_pRpHAnimHierarchy->pMatrixArray[bone], &m_pRwFrame->ltm);
        RwMatrixMultiply(&childFrame->ltm, &childFrame->modelling, &boneLtm);
    }
    LtmWritten(childFrame);
}

// 0x000cabc8 UpdateAnimatedNodePoseAndCull
uint32_t CAnimatedNode::UpdatePoseAndCull(RenderQueue** stages, IKTime* frameClock, float* sphere, float* worldSphere,
                                          RwCamera* camera) {
    if ((m_sgProperties & 1u) != 0 && (m_sgProperties & 2u) == 0 && frameClock->m_eCurrentState == 0) {
        CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(m_pController);
        controller->m_unk50 = ppc::fmadds(frameClock->m_afDeltaTime[0], m_unk60, controller->m_unk50);
    }
    if (frameClock->m_eCurrentState == 0 && ((m_sgProperties >> 9) & 3) == 2) {
        m_blendSlot.AdvanceInactiveTrack(frameClock->m_afDeltaTime[0]);  // 0x79f30
    }
    KBase98D* controller = static_cast<KBase98D*>(m_pController);
    const float* local = controller->GetBoundingSphere();  // vt+0x54
    if (local != nullptr) {
        sphere[0] = static_cast<KBase98D*>(m_pController)->m_afUnk14[0];
        sphere[1] = static_cast<KBase98D*>(m_pController)->m_afUnk14[1];
        sphere[2] = static_cast<KBase98D*>(m_pController)->m_afUnk14[2];
        sphere[3] = static_cast<KBase98D*>(m_pController)->m_afUnk14[3];
    }
    TransformNodeBoundingSphereToWorld(sphere[3], this, worldSphere, &worldSphere[3], sphere);  // 0xcbfc0
    const uint32_t visible = static_cast<uint32_t>(RwCameraFrustumTestSphere(camera, worldSphere));
    controller = static_cast<KBase98D*>(m_pController);
    if (controller->m_unk26 != g_ui16RenderFrameCounter) controller->UpdateActiveState();  // vt+0x68
    uint32_t mask[4] = {0, 0, 0, 0};  // sp+0x74
    float weight;                      // sp+0x70
    bool posed;
    if ((controller->m_unk08 & 0x10u) != 0 && ((m_sgProperties & 0x2000u) != 0 || visible != 0)) {
        RpHAnimHierarchy* hierarchy = m_pRpHAnimHierarchy;
        RtAnimInterpolator* own = hierarchy->currentAnim;
        hierarchy->currentAnim = controller->Evaluate(mask, &weight, 0);  // vt+0x64
        RpHAnimHierarchyUpdateMatrices(m_pRpHAnimHierarchy);
        m_pRpHAnimHierarchy->currentAnim = own;
        posed = true;
    } else {
        controller->Evaluate(mask, &weight, 1);
        posed = false;
    }
    // The children hanging under bones: their LTM through the bone (the bone x node matrix computed once per run of
    // children on the same bone), or the node's when no pose was made; their subtree marked to sync.
    RwMatrix boneLtm;  // sp+0x90
    uint8_t lastBone = 0xff;
    for (CSGLeaf* child = m_pAttachmentHead; child != nullptr; child = child->m_pNext) {
        if ((child->m_sgProperties & 4u) != 0) continue;
        RwFrame* frame = child->m_pRwFrame;
        if (posed) {
            const uint8_t bone = child->m_ui8BoneParent;
            if (bone != lastBone) {
                RwMatrixMultiply(&boneLtm, &m_pRpHAnimHierarchy->pMatrixArray[bone], &m_pRwFrame->ltm);
            }
            RwMatrixMultiply(&frame->ltm, &frame->modelling, &boneLtm);
            lastBone = bone;
        } else {
            RwMatrixMultiply(&frame->ltm, &frame->modelling, &m_pRwFrame->ltm);
        }
        frame->object.privateFlags |= 3;
        for (RwFrame* sub = frame->child; sub != nullptr; sub = sub->next) sub->object.privateFlags |= 0xc;
        LtmWritten(frame);
    }
    // Then they are traversed (their frames' LTM made current, the previous one's bit 2 cleared), then the other children.
    RwFrame* previous = nullptr;
    RwFrame* frame = nullptr;
    for (CSGLeaf* child = m_pAttachmentHead; child != nullptr; child = child->m_pNext) {
        frame = child->m_pRwFrame;
        if (frame != previous) {
            RwFrameGetLTM(frame);
            if (previous != nullptr) previous->object.privateFlags = static_cast<RwUInt8>(previous->object.privateFlags & 0xfdu);
        }
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // vt+0x58 (TOC -0x562c: 0.0f)
        previous = frame;
    }
    if (frame != nullptr) frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & 0xfdu);
    for (CSGLeaf* child = m_lChildList; child != nullptr; child = child->m_pNext) {
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);
    }
    return visible;
}

// 0x000cb0f0 PrepareAndEnqueueAnimatedNode
void CAnimatedNode::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                     RwCamera* camera, int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4u) != 0) return;
    // BUG(original): the local sphere (sp+0x70) is not set when the controller has none (a blender without an active
    // child): the stack's bytes then go through the transform; here zeros.
    float sphere[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float worldSphere[4];  // sp+0x80
    if (UpdatePoseAndCull(stages, frameClock, sphere, worldSphere, camera) == 0) return;
    for (CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList); geometry != nullptr; geometry = geometry->m_pNext) {
        RpAtomic* atomic = geometry->m_pRpAtomic;
        const float radius = worldSphere[3];
        if ((atomic->flags & 2u) != 0) {
            // STUB(C2.7): BridgeRwUpdateAtomicMorphBoundingSphere 0x98e090 (morph targets; as CGeometry vt+0x7c).
            DOTD_STUB_ONCE("PrepareAndEnqueueAnimatedNode 0xcb0f0: morph atomic bounding sphere (C2.7)");
            atomic = geometry->m_pRpAtomic;
        }
        // The node's world sphere into the atomic's own sphere (PS3 +0x1c: RpAtomic boundingSphere; a geometry with render
        // flag 0x200000 takes it unchanged as its world sphere), the morph interpolator's bit 2 (+0x4c) cleared, the
        // atomic's private flag 1 set.
        atomic->boundingSphere[0] = worldSphere[0];
        atomic->boundingSphere[1] = worldSphere[1];
        atomic->boundingSphere[2] = worldSphere[2];
        atomic->boundingSphere[3] = radius;
        atomic->flags &= 0xfffffffdu;
        atomic->objectFlags |= 1;
    }
    if ((CullAndEnqueueGeometry(stages, frameClock, camera) & 0xff) != 0) {  // vt+0x84 (CNode's 0xcc460)
        m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
    }
}
