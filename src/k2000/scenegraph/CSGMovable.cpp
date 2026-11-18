// CSGMovable.cpp - reconstructed original translation unit 0xd07b8-0xd2338 (GAME_TOC1, main_toc1), 44 functions, 41 live.
// Primary class: CSGMovable  key 0x14b  category SceneNode  size 0x8  vtable 0xb182e8
// Other owners: CSGPointLight (2), SceneNode (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd07b8  CSGMovable_Delete
//   [x] 0xd0808  CSGMovable_RecursiveRegistration
//   [ ] 0xd0868  RegisterCSGMovableClass
//   [ ] 0xd08e0  _GLOBAL__I_d08e0
//   [x] 0xd08f0  CSGMovable_SetIdentity
//   [x] 0xd0918  CSGMovable_SetOrientationFromAtUp
//   [x] 0xd0970  CSGMovable_SetUniformScale_maybe  (CSGMovable::SetUniformScale)
//   [x] 0xd09d8  CSGMovable_SetBasisFromAtRight
//   [x] 0xd0a30  CSGMovable_SetBasisFromUpAndForward
//   [x] 0xd0a88  CSGMovable_SetOrientationFromUpAt
//   [ ] 0xd0ae0  CSGMovable_OrthonormalizeMatrix_maybe  [dead: no pointer to its descriptor 0xb4fb40]
//   [x] 0xd0b38  CSGMovable_SetBasisFromRightUp  (CSGMovable::SetBasisFromRightUp)
//   [x] 0xd0b90  SceneNode_SetLocalFromWorldTimes_maybe  (inlined in its callers CAnimatedNode::AttachChildToBone and CSGBranch::AddChildKeepWorldTransform)
//   [x] 0xd0be8  CSGMovable_SetLocalMatrix_maybe
//   [ ] 0xd0c18  CSGMovable_TransformPostConcat_maybe  [dead: no pointer to its descriptor 0xb4fb60]
//   [x] 0xd0c48  CSGMovable_RotateKeepPosition_maybe
//   [ ] 0xd0cb8  CSGMovable_RotateKeepPosition_2_maybe  [dead: no pointer to its descriptor 0xb4fb70]
//   [x] 0xd0d28  CSGMovable_ScaleXYZ
//   [x] 0xd0d88  CSGMovable_Scale
//   [ ] 0xd0dd8  CSGMovable_SetScale_maybe  [dead: no pointer to its descriptor 0xb4fb88]
//   [x] 0xd0e60  CSGMovable_SetScaleXYZ_maybe
//   [ ] 0xd0ef8  CSGMovable_SetScale_2_maybe  [dead: no pointer to its descriptor 0xb4fb98]
//   [x] 0xd0f80  CSGMovable_RotateAboutPoint_maybe
//   [x] 0xd1090  CSGMovable_Construct_2
//   [x] 0xd10d0  CSGMovable_Construct
//   [x] 0xd1110  CSGMovable_DeleteArray
//   [x] 0xd11b0  CSGMovable_RotateInPlace
//   [ ] 0xd1230  CSGMovable_AlignVectorToVector_maybe  [dead: no pointer to its descriptor 0xb4fbe0]
//   [ ] 0xd1650  CSGMovable_RotateVectorToVector_maybe  [dead: no pointer to its descriptor 0xb4fbe8]
//   [ ] 0xd19d0  CSGMovable_Save
//   [x] 0xd1a08  CSGMovable_Load
//   [x] 0xd1a58  CSGMovable_BaseDestructor  (~CSGMovable)
//   [x] 0xd1ab0  CSGMovable_LookAtPoint
//   [x] 0xd1da0  CSGMovable_CreateArray
//   [x] 0xd1e50  CSGMovable_Create
//   [x] 0xd1ea8  rwSetHierarchyRoot
//   [ ] 0xd2058  CSGMovable_ClearReferences_2_maybe  [dead]
//   [x] 0xd2128  CSGMovable_Destroy
//   [x] 0xd21f8  CSGMovable_DeletingDestructor  (~CSGMovable + delete)
//   [x] 0xd2268  CSGMovable_Destructor  (~CSGMovable)
//   [x] 0xd22c0  CSGPointLight_Delete  (DOTD_DECLARE_FACTORIES in CSGPointLight.h)
//   [x] 0xd2310  CSGPointLight_RecursiveRegistration  (CSGPointLight's RecursiveRegistration: returns 1, registers nothing: CSGLeaf's)
//   [ ] 0xd2318  FUN_000d2318  [dead]
//   [ ] 0xd2330  KStub_Nop_d2330  [dead]
//
//   [x] 0x9a2908  CSGMovable_GetClassType  [inline]
//   [x] 0x9a2910  CSGMovable_GetClassID  [inline]
//   [ ] 0x9a2918  CSGMovable_GetSerializationFlags  [inline]
//   [ ] 0x9a2920  CSGMovable_ComputeLTM_maybe  [inline]
//   [ ] 0x9a2928  CSGMovable_ComputeLTMWithParent_maybe  [inline]
//   [ ] 0x9a2930  CSGMovable_IsKindOfClass  [inline]
#include "k2000/scenegraph/CSGMovable.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Mat4.h"

// 0x000d10d0 CSGMovable_Construct (0x000d1090 CSGMovable_Construct_2 is the same constructor).
CSGMovable::CSGMovable() { m_pRwFrame = RwFrameCreate(); }

// 0x000d1a08 CSGMovable_Load: the frame's modelling matrix (RwFrame +0x10), then the frame's private
// flags (RwFrame +0x03) |= 4 (rwFRAMEPRIVATESUBTREESYNCLTM). No type check.
int32_t CSGMovable::Load(IKFile* file, int32_t /*type*/) {
    CMatrix34_LoadMatrix(reinterpret_cast<CMatrix34*>(&m_pRwFrame->modelling), file);
    m_pRwFrame->object.privateFlags |= 4;
    return 1;
}

// 0x000d2128 CSGMovable_Destroy (the level / sector unload)
void CSGMovable::Destroy() {
    RwFrame* frame = m_pRwFrame;
    if (frame == nullptr) return;
    RwFrame* child = frame->child;
    while (child != nullptr) {
        RwFrame* grandChild = child->child;
        RwFrame* next = child->next;
        child->root = child;
        child->object.parent = nullptr;
        child->next = nullptr;
        for (; grandChild != nullptr; grandChild = grandChild->next) rwSetHierarchyRoot(grandChild, child);
        child = next;
    }
    m_pRwFrame->child = nullptr;
}

// 0x000d1ea8 rwSetHierarchyRoot (RW 3.7 core/src/baframe.c; the PS3 copy unrolls the recursion 9 levels).
void rwSetHierarchyRoot(RwFrame* frame, RwFrame* root) {
    frame->root = root;
    for (RwFrame* child = frame->child; child != nullptr; child = child->next) rwSetHierarchyRoot(child, root);
}

// 0x000d1ab0 CSGMovable_LookAtPoint. The PS3 code reads the frame's modelling position (+0x40), builds
// right = up x at (normalised through rwInvSqrt = Math_InvSqrtf 0x114d8) and up = at x right.
void CSGMovable::LookAtPoint(const float* target, const float* up) {
    RwFrame* frame = m_pRwFrame;
    const RwV3d& position = frame->modelling.pos;
    float dx = target[0] - position.x;
    float dy = target[1] - position.y;
    float dz = target[2] - position.z;
    const float lengthSquared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    if (!(lengthSquared >= 0x1.b7cdfep-34f)) return;  // 1e-10
    float inverse = rwInvSqrt(lengthSquared);
    dz = inverse * dz;
    dx = dx * inverse;
    dy = dy * inverse;
    const float upX = up[0], upY = up[1], upZ = up[2];
    float n0 = ppc::fmsubs(upZ, dx, upX * dz);  // up x at
    float n1 = ppc::fmsubs(upX, dy, upY * dx);
    float n2 = ppc::fmsubs(dz, upY, upZ * dy);
    const float rightLengthSquared = ppc::fmadds(n1, n1, ppc::fmadds(n2, n2, n0 * n0));
    if (rightLengthSquared < 0x1.1eb852p-6f) return;  // 0.0175
    inverse = rwInvSqrt(rightLengthSquared);
    n1 = inverse * n1;
    n2 = n2 * inverse;
    n0 = n0 * inverse;
    // right = (n2, n0, n1) in the order of the stores; up = (u2, u0, u1), the cross product of `at` and `right`
    const float u0 = ppc::fmsubs(dz, n2, dx * n1);
    const float u1 = ppc::fmsubs(dx, n0, dy * n2);
    const float u2 = ppc::fmsubs(n1, dy, dz * n0);
    RwFrame* parent = static_cast<RwFrame*>(frame->object.parent);
    if (parent == nullptr || parent->root == parent) {
        RwMatrix& matrix = frame->modelling;
        matrix.right.x = n2;
        matrix.right.y = n0;
        matrix.right.z = n1;
        matrix.up.x = u2;
        matrix.up.y = u0;
        matrix.up.z = u1;
        matrix.flags = matrix.flags & 0xfffdfffcu;
        matrix.at.x = dx;
        matrix.at.y = dy;
        matrix.at.z = dz;
    } else {
        // The axes through the transpose of the parent's rotation (RwV3dTransformVectors with a local matrix).
        RwMatrix local;
        const RwMatrix& p = parent->modelling;
        local.right = RwV3d{p.right.x, p.up.x, p.at.x};
        local.up = RwV3d{p.right.y, p.up.y, p.at.y};
        local.at = RwV3d{p.right.z, p.up.z, p.at.z};
        local.pos = RwV3d{0.0f, 0.0f, 0.0f};
        local.flags = p.flags & 0xfffdfffcu;
        const RwV3d in[3] = {RwV3d{dx, dy, dz}, RwV3d{n2, n0, n1}, RwV3d{u2, u0, u1}};
        RwV3d out[3];
        RwV3dTransformVectors(out, in, 3, &local);
        RwMatrix& matrix = frame->modelling;
        matrix.right = out[1];
        matrix.up = out[2];
        matrix.flags = matrix.flags & 0xfffdfffcu;
        matrix.at = out[0];
    }
    RwFrame_MarkDirty(m_pRwFrame);
    m_pRwFrame->modelling.flags = 3;
    RwFrame_MarkDirty(m_pRwFrame);
}

// 0x000d0be8 CSGMovable_SetLocalMatrix_maybe: RwFrameTransform(frame, matrix, rwCOMBINEREPLACE) (TocBridge inlined).
void CSGMovable::SetLocalMatrix(const RwMatrix* matrix) { RwFrameTransform(m_pRwFrame, matrix, rwCOMBINEREPLACE); }

// 0x000d0c48 CSGMovable_RotateKeepPosition_maybe (RwFrameRotate through its TocBridge: RwMatrixRotate on the modelling matrix, the
// frame marked dirty)
void CSGMovable::RotateKeepPosition(const float* axis, float degrees) {
    RwFrame* frame = m_pRwFrame;
    const float x = frame->modelling.pos.x;
    const float y = frame->modelling.pos.y;
    const float z = frame->modelling.pos.z;
    RwMatrixRotate(&frame->modelling, reinterpret_cast<const RwV3d*>(axis), degrees, rwCOMBINEREPLACE);
    RwFrame_MarkDirty(frame);
    frame->modelling.pos.x = x;
    frame->modelling.pos.z = z;
    frame->modelling.pos.y = y;
}

// 0x000d11b0 CSGMovable_RotateInPlace (RwFrameRotate through its TocBridge with rwCOMBINEPOSTCONCAT: RwMatrixRotate on the
// modelling matrix, the frame marked dirty); the position is read before and written back after (z, x, y).
void CSGMovable::RotateInPlace(const float* axis, float degrees) {
    RwFrame* frame = m_pRwFrame;
    const float z = frame->modelling.pos.z;
    const float x = frame->modelling.pos.x;
    const float y = frame->modelling.pos.y;
    RwMatrixRotate(&frame->modelling, reinterpret_cast<const RwV3d*>(axis), degrees, rwCOMBINEPOSTCONCAT);
    RwFrame_MarkDirty(frame);
    frame = m_pRwFrame;
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
}

// 0x000d0d88 CSGMovable_Scale (RwMatrixScale through its TocBridge)
void CSGMovable::Scale(const float* scale) {
    RwMatrixScale(&m_pRwFrame->modelling, reinterpret_cast<const RwV3d*>(scale), rwCOMBINEPRECONCAT);
    RwFrame_MarkDirty(m_pRwFrame);
}

// 0x000d08f0 CSGMovable_SetIdentity: RwFrameSetIdentity (0x74aaa0 through its TOC bridge 0x98ec00): the modelling matrix
// the identity (flags |= rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL), then RwFrameUpdateObjects.
void CSGMovable::SetIdentity() {
    RwMatrix* m = &m_pRwFrame->modelling;
    m->right.x = 1.0f;
    m->up.x = 0.0f;
    m->flags = m->flags | 0x20003u;
    m->at.z = 1.0f;
    m->up.y = 1.0f;
    m->up.z = 0.0f;
    m->right.z = 0.0f;
    m->right.y = 0.0f;
    m->at.y = 0.0f;
    m->at.x = 0.0f;
    m->pos.x = 0.0f;
    m->pos.z = 0.0f;
    m->pos.y = 0.0f;
    RwFrameUpdateObjects(m_pRwFrame);
}

// 0x000d0918 CSGMovable_SetOrientationFromAtUp
int32_t CSGMovable::SetOrientationFromAtUp(const CVector3* at, const CVector3* up) {
    const int32_t written = Mat4_SetBasisFromAtUp(reinterpret_cast<CMatrix34*>(&m_pRwFrame->modelling), at, up);
    RwFrame_MarkDirty(m_pRwFrame);
    return written;
}

// 0x000d09d8 CSGMovable_SetBasisFromAtRight
uint8_t CSGMovable::SetBasisFromAtRight(const CVector3* at, const CVector3* right) {
    const int32_t written = Mat4_SetBasisFromAtRight(reinterpret_cast<CMatrix34*>(&m_pRwFrame->modelling), at, right);  // 0x0023fe58
    RwFrame_MarkDirty(m_pRwFrame);
    return static_cast<uint8_t>(written);
}

// ---- C2.7 fx (the air currents' flow FX, the animated effects' rigs) ----

// 0x000d0a30 CSGMovable_SetBasisFromUpAndForward
int32_t CSGMovable::SetBasisFromUpAndForward(const CVector3* up, const CVector3* forward) {
    const int32_t written = Mat4_BuildFromUpAndForward(reinterpret_cast<CMatrix34*>(&m_pRwFrame->modelling), up, forward);
    RwFrame_MarkDirty(m_pRwFrame);
    return written;
}

// 0x000d0a88 CSGMovable_SetOrientationFromUpAt
uint8_t CSGMovable::SetOrientationFromUpAt(const CVector3* up, const CVector3* at) {
    const int32_t written = Mat4_SetBasisFromUpAt(reinterpret_cast<CMatrix34*>(&m_pRwFrame->modelling), up, at);  // 0x002400a8
    RwFrame_MarkDirty(m_pRwFrame);
    return static_cast<uint8_t>(written);
}

// 0x000d0d28 CSGMovable_ScaleXYZ (RwMatrixScale through its TocBridge)
void CSGMovable::ScaleXYZ(float x, float y, float z) {
    const RwV3d scale = {x, y, z};
    RwMatrixScale(&m_pRwFrame->modelling, &scale, rwCOMBINEPRECONCAT);
    RwFrame_MarkDirty(m_pRwFrame);
}

// 0x000d0e60 CSGMovable_SetScaleXYZ_maybe (RwMatrixScale through its TocBridge; the position saved and put back)
void CSGMovable::SetScaleXYZ(float x, float y, float z) {
    RwMatrix* modelling = &m_pRwFrame->modelling;
    const float px = modelling->pos.x;
    const float pz = modelling->pos.z;
    const float py = modelling->pos.y;
    const RwV3d scale = {x, y, z};
    RwMatrixScale(modelling, &scale, rwCOMBINEREPLACE);
    m_pRwFrame->modelling.pos.x = px;
    m_pRwFrame->modelling.pos.z = pz;
    m_pRwFrame->modelling.pos.y = py;
    RwFrame_MarkDirty(m_pRwFrame);
}

// 0x000d0f80 CSGMovable_RotateAboutPoint_maybe (RwMatrixInvert, RwFrameRotate, RwV3dTransformPoints, RwFrameTranslate
// through their TocBridges; RwFrameRotate / RwFrameTranslate are the matrix operation and the frame marked dirty)
void CSGMovable::RotateAboutPoint(float degrees, const CVector3* point, const CVector3* axis) {
    RwMatrix inverse;
    RwMatrixInvert(&inverse, &m_pRwFrame->modelling);
    RwMatrixRotate(&m_pRwFrame->modelling, reinterpret_cast<const RwV3d*>(axis), degrees, rwCOMBINEPOSTCONCAT);
    RwFrame_MarkDirty(m_pRwFrame);
    m_pRwFrame->modelling.pos.x = point->x;
    m_pRwFrame->modelling.pos.y = point->y;
    m_pRwFrame->modelling.pos.z = point->z;
    RwV3d back;
    RwV3dTransformPoints(&back, reinterpret_cast<const RwV3d*>(point), 1, &inverse);
    back.x = -back.x;
    back.y = -back.y;
    back.z = -back.z;
    RwMatrixTranslate(&m_pRwFrame->modelling, &back, rwCOMBINEPRECONCAT);
    RwFrame_MarkDirty(m_pRwFrame);
}

// C2.8 port-all P11.

// 0x000d1a58 CSGMovable_BaseDestructor (0xd2268 / 0xd21f8 the same)
CSGMovable::~CSGMovable() {
    RwFrameDestroy(m_pRwFrame);  // through TocBridge_RwFrameDestroy (not null-checked)
    m_pRwFrame = nullptr;
}

// 0x000d0808 CSGMovable_RecursiveRegistration
void CSGMovable::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x000d0970 CSGMovable_SetUniformScale_maybe
void CSGMovable::SetUniformScale(float scale) {
    RwMatrix* m = &m_pRwFrame->modelling;
    m->flags = 2;
    m->right.x = scale;
    m->right.y = 0.0f;
    m->at.z = scale;
    m->up.y = scale;
    m->at.y = 0.0f;
    m->at.x = 0.0f;
    m->up.z = 0.0f;
    m->up.x = 0.0f;
    m->right.z = 0.0f;
    RwFrame_MarkDirty(m_pRwFrame);  // 0x00010698
}

// 0x000d0b38 CSGMovable_SetBasisFromRightUp
uint8_t CSGMovable::SetBasisFromRightUp(const CVector3* right, const CVector3* up) {
    const int32_t result = Mat4_SetBasisFromRightUp(reinterpret_cast<CMatrix34*>(&m_pRwFrame->modelling), right, up);  // 0x0023fa90
    RwFrame_MarkDirty(m_pRwFrame);
    return static_cast<uint8_t>(result);
}
