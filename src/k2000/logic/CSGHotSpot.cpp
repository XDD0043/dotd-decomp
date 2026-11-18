// CSGHotSpot.cpp - reconstructed original translation unit 0xcdf20-0xceb28 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CSGHotSpot  key 0x2b4c  category Logic  size 0x28  vtable 0xb181a0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xcdf20  CSGHotSpot_Delete
//   [x] 0xcdf70  CSGHotSpot_Destroy  (empty: the default slot)
//   [x] 0xcdf78  CSGHotSpot_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0xcdf80  CSGHotSpot_Load
//   [x] 0xce130  CSGHotSpot_PostLoad  (returns 1: the default slot)
//   [ ] 0xce138  CSGHotSpot_ClearTarget_maybe  [dead]
//   [ ] 0xce150  RegisterCSGHotSpotClass
//   [ ] 0xce1c8  _GLOBAL__I_ce1c8
//   [x] 0xce1d8  CSGHotSpot_DeleteArray
//   [x] 0xce280  CSGHotSpot_Create
//   [x] 0xce2b8  CSGHotSpot_AttachVolume
//   [ ] 0xce3c0  CSGHotSpot_Save
//   [x] 0xce690  CSGHotSpot_DetachVolume
//   [ ] 0xce6f0  FUN_000ce6f0  [dead]
//   [x] 0xce790  CSGHotSpot_GetWorldPosition
//   [x] 0xce8d8  CSGHotSpot_CreateArray
//   [x] 0xce970  CSGHotSpot_GetWorldMatrix
//
//   [ ] 0x9a2718  CSGHotSpot_GetClassType  [inline]
//   [ ] 0x9a2720  CSGHotSpot_GetClassID  [inline]
//   [ ] 0x9a2728  CSGHotSpot_Destructor  [inline]
//   [ ] 0x9a2740  CSGHotSpot_IsKindOfClass  [inline]
//   [ ] 0x9a2760  CSGHotSpot_DeletingDestructor  [inline]
#include "k2000/logic/CSGHotSpot.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/Quat.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "Renderware/rwcore/RwMatrix.h"

// 0x000cdf80 CSGHotSpot_Load: the defaults, then the node, the bone and position + orientation (one 0x1c
// read, each word byte-swapped).
int32_t CSGHotSpot::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_ui8BoneNumber = 0xff;
    m_v3RelativePosition.x = 0.0f;  // TOC -0x54e0
    m_v3RelativePosition.y = 0.0f;
    m_v3RelativePosition.z = 0.0f;
    m_qUnitRelativeOrientation[0] = 0.0f;
    m_qUnitRelativeOrientation[2] = 0.0f;
    m_qUnitRelativeOrientation[1] = 0.0f;
    m_qUnitRelativeOrientation[3] = 1.0f;  // TOC -0x54e4
    IKFile_ReadRef(file, &m_pParent);
    ReadRaw(file, &m_ui8BoneNumber, 1);
    uint32_t words[7];
    ReadU32LEWords(file, words, 7);
    std::memcpy(&m_v3RelativePosition, words, 0xc);
    std::memcpy(m_qUnitRelativeOrientation, words + 3, 0x10);
    return 1;
}

// 0x000ce690 CSGHotSpot_DetachVolume
int32_t CSGHotSpot::DetachVolume(CSGLeaf* volume) {
    CSGBranch* node = m_pParent;
    if (node == nullptr) return 0;
    node->RemoveChild(volume);  // vt+0x78
    return 1;
}

// 0x000ce2b8 CSGHotSpot_AttachVolume. The bone case calls CAnimatedNode's group attach directly, so the
// node is an animated node there.
int32_t CSGHotSpot::AttachVolume(CSGLeaf* volume) {
    CSGBranch* node = m_pParent;
    if (node == nullptr) return 0;
    if (m_ui8BoneNumber == 0xff) {
        node->AddChild(volume);  // vt+0x70
    } else {
        static_cast<CAnimatedNode*>(node)->AttachChildToGroup(m_ui8BoneNumber, volume);
    }
    RwFrame* frame = volume->m_pRwFrame;
    Quat_ToMatrix(m_qUnitRelativeOrientation, reinterpret_cast<CMatrix34*>(&frame->modelling));
    frame->modelling.pos.x = m_v3RelativePosition.x;
    frame->modelling.pos.y = m_v3RelativePosition.y;
    frame->modelling.pos.z = m_v3RelativePosition.z;
    frame->modelling.flags &= 0xfffdffffu;  // rwMATRIXINTERNALIDENTITY
    RwFrame_MarkDirty(frame);
    return 1;
}

// 0x000ce790 CSGHotSpot_GetWorldPosition
int32_t CSGHotSpot::GetWorldPosition(CVector3* out) const {
    // The node is a CAnimatedNode whenever a bone is given (the hero's, the enemies').
    CSGBranch* parent = m_pParent;
    if (parent == nullptr) return 0;
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(&parent->m_pRwFrame->ltm);
    if (m_ui8BoneNumber == 0xff) {
        Mat4_TransformPoints(ltm, out, &m_v3RelativePosition, 1);
        return 1;
    }
    if (parent->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter || (parent->m_sgProperties & 0x2000u) != 0) {
        const CAnimatedNode* node = static_cast<const CAnimatedNode*>(parent);
        CMatrix34 bone;
        RwMatrixMultiply(reinterpret_cast<RwMatrix*>(&bone), node->GetBoneMatrix(m_ui8BoneNumber),
                         reinterpret_cast<const RwMatrix*>(ltm));  // Mat4_Multiply 0x23f788
        Mat4_TransformPoints(&bone, out, &m_v3RelativePosition, 1);
        return 1;
    }
    Mat4_TransformPoints(ltm, out, &m_v3RelativePosition, 1);
    return 1;
}

// 0x000ce970 CSGHotSpot_GetWorldMatrix
int32_t CSGHotSpot::GetWorldMatrix(CMatrix34* out) const {
    CSGBranch* parent = m_pParent;
    if (parent == nullptr) return 0;
    alignas(16) CMatrix34 local;
    Quat_ToMatrix(m_qUnitRelativeOrientation, &local);
    local.m_pos.z = m_v3RelativePosition.z;
    local.m_pos.x = m_v3RelativePosition.x;
    local.m_pos.y = m_v3RelativePosition.y;
    local.m_ui32Flags &= 0xfffdffffu;
    // The node's stored LTM, as the PS3 reads it (not RwFrameGetLTM): a node moved this frame still answers its last
    // synchronised matrix. G +15955: the golem QTE's sequence holds both heroes; the first hero's locomotion reads its
    // hot spot's old matrix (its position unchanged), the second's the synchronised one. (C2.7 read it through
    // RwFrameGetLTM for the electric gauge's OnActivate; the level start's UpdateSceneWorldMatrices syncs the frames
    // before the activations, and breath2 / the regression replays are unchanged with the stored one.)
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(&parent->m_pRwFrame->ltm);
    if (m_ui8BoneNumber != 0xff &&
        (parent->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter || (parent->m_sgProperties & 0x2000u) != 0)) {
        const CAnimatedNode* node = static_cast<const CAnimatedNode*>(parent);
        alignas(16) CMatrix34 bone;
        Mat4_Multiply(&bone, reinterpret_cast<const CMatrix34*>(node->GetBoneMatrix(m_ui8BoneNumber)), ltm);
        Mat4_Multiply(out, &local, &bone);
        return 1;
    }
    Mat4_Multiply(out, &local, ltm);
    return 1;
}
