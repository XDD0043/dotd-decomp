// CSGMovable.h - a scene-graph object with a RenderWare frame (key 0x14b, vtable 0xb182e8, size 0x8).
// Original unit: CSGMovable.cpp (0xd07b8-0xd2338). XXL2: K/KModules/KGL/SceneGraph/CSGMovable.h, member
// m_pRwFrame (XXL2's m_sModelName is not in the PS3 build).
//
// The root of the scene-node chain CSGMovable -> CSGLeaf -> CSGBranch -> CNode. Its Load reads the
// frame's modelling matrix.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

// RenderWare 3.7 RwFrame (Renderware/rwcore/RwCamera.h): RwObject (+0x00, private flags at +0x03),
// inDirtyListLink (+0x08), modelling matrix (+0x10), LTM (+0x50, position at +0x80), child/next/root links.
struct RwFrame;
struct RwMatrix;

class CSGMovable : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x5)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x14b || key == 0xc; }  // vt+0x08 0x9a2930
    DOTD_DECLARE_FACTORIES(CSGMovable)

    CSGMovable();  // 0x000d10d0 CSGMovable_Construct
    // 0x000d1a58 CSGMovable_BaseDestructor (0x0d2268 Destructor the same, 0xd21f8 DeletingDestructor + delete): the
    // frame destroyed (RwFrameDestroy) and cleared.
    ~CSGMovable() override;
    // vt+0x24 0x000d0808 CSGMovable_RecursiveRegistration: type 0: the node registered. CSGLeaf overrides it with
    // nothing (0xceb78).
    void RecursiveRegistration(int32_t type) override;

    // vt+0x10 0x000d2128 CSGMovable_Destroy: every child frame cut loose (its own root, no parent, no
    // sibling; its subtree re-rooted), then the frame has no children. The frame itself stays.
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000d1a08 CSGMovable_Load

    // vt+0x50 0x000cf300 CSGLeaf_ComputeLTM_maybe (XXL2 CSGLeaf::ForceWorldMatrixUpdate); CSGLeaf overrides it.
    // The empty default is the abstract-base slot (no instance of CSGMovable itself is updated).
    virtual void ForceWorldMatrixUpdate() {}
    // vt+0x54 0x000cf1e0 CSGLeaf_ComputeLTMWithParent_maybe (XXL2 ChildWorldMatrixUpdate): CSGLeaf overrides it.
    virtual void ChildWorldMatrixUpdate(CSGMovable* /*child*/) {}

    // 0x000d08f0 CSGMovable_SetIdentity (not virtual): the frame's modelling matrix the identity, the frame updated.
    void SetIdentity();
    // 0x000d0970 CSGMovable_SetUniformScale_maybe (not virtual): the frame's modelling matrix a uniform scale `scale`
    // (the axes' diagonal, the other axis words 0, the position kept, flags 2), the frame marked dirty. Caller: CKHkS08TuningFork
    // (SetMeshAlpha / UpdateFadeAlpha, R10).
    void SetUniformScale(float scale);
    // 0x000d0b38 CSGMovable_SetBasisFromRightUp (not virtual): Mat4_SetBasisFromRightUp on the frame's modelling
    // matrix, then the frame marked dirty; Mat4_SetBasisFromRightUp's result (a byte).
    uint8_t SetBasisFromRightUp(const CVector3* right, const CVector3* up);
    // 0x000d0918 CSGMovable_SetOrientationFromAtUp (not virtual): Mat4_SetBasisFromAtUp on the frame's
    // modelling matrix (`at` and `up` become its axes; unchanged when `up` x `at` is too short), then the
    // frame is marked dirty. Returns Mat4_SetBasisFromAtUp's result (1 when written).
    int32_t SetOrientationFromAtUp(const CVector3* at, const CVector3* up);
    // 0x000d09d8 CSGMovable_SetBasisFromAtRight (not virtual): Mat4_SetBasisFromAtRight on the frame's modelling matrix,
    // the frame marked dirty; its result's low byte returned.
    uint8_t SetBasisFromAtRight(const CVector3* at, const CVector3* right);

    // 0x000d1ab0 CSGMovable_LookAtPoint (not virtual): the frame turned to look at `target` (world position) with
    // `up` as the approximate up vector; nothing when the target is (almost) at the frame or `up` is parallel to
    // the view direction. A frame under a non-root parent has the axes taken into the parent's space.
    void LookAtPoint(const float* target, const float* up);
    // 0x000d0be8 CSGMovable_SetLocalMatrix_maybe (not virtual): RwFrameTransform(frame, matrix, replace).
    void SetLocalMatrix(const RwMatrix* matrix);
    // 0x000d0d88 CSGMovable_Scale (not virtual): RwMatrixScale(modelling, scale, rwCOMBINEPRECONCAT), the frame marked dirty.
    void Scale(const float* scale);
    // 0x000d0c48 CSGMovable_RotateKeepPosition_maybe (not virtual): the modelling matrix replaced by the rotation of `degrees`
    // about `axis` (RwFrameRotate, replace), the position put back.
    void RotateKeepPosition(const float* axis, float degrees);
    // 0x000d11b0 CSGMovable_RotateInPlace (not virtual): the modelling matrix rotated by `degrees` about `axis`
    // (RwFrameRotate, post-concatenated), the position put back. step 5 (the camera's roll).
    void RotateInPlace(const float* axis, float degrees);
    // 0x000d0a30 CSGMovable_SetBasisFromUpAndForward (not virtual): Mat4_BuildFromUpAndForward on the modelling matrix,
    // the frame marked dirty; its result returned. C2.7 fx.
    int32_t SetBasisFromUpAndForward(const CVector3* up, const CVector3* forward);
    // 0x000d0a88 CSGMovable_SetOrientationFromUpAt (not virtual): Mat4_SetBasisFromUpAt on the modelling matrix, the frame
    // marked dirty; its result's low byte returned.
    uint8_t SetOrientationFromUpAt(const CVector3* up, const CVector3* at);
    // 0x000d0d28 CSGMovable_ScaleXYZ (not virtual): RwMatrixScale(modelling, (x, y, z), rwCOMBINEPRECONCAT), the frame
    // marked dirty. C2.7 fx.
    void ScaleXYZ(float x, float y, float z);
    // 0x000d0e60 CSGMovable_SetScaleXYZ_maybe (not virtual): RwMatrixScale(modelling, (x, y, z), rwCOMBINEREPLACE) with the
    // position kept, the frame marked dirty.
    void SetScaleXYZ(float x, float y, float z);
    // 0x000d0f80 CSGMovable_RotateAboutPoint_maybe (not virtual): the modelling matrix turned by `degrees` about `axis`
    // through `point` (in the parent's space): RwFrameRotate post-concatenated, the position set to `point`, then
    // translated back by the point taken through the inverse of the matrix before the turn (pre-concatenated). C2.7 fx.
    void RotateAboutPoint(float degrees, const CVector3* point, const CVector3* axis);

    // +0x04 the constructor creates it (RwFrameCreate); Load sets its modelling matrix. The frame
    // hierarchy (RwFrameAddChild, the dirty list) is not ported: every frame is a root, its LTM its
    // modelling matrix (Renderware/rwcore/RwCamera.h).
    RwFrame* m_pRwFrame;
};
static_assert(CSGMovable::kClassKey == 0x14b, "key");
DOTD_ASSERT_SIZE(CSGMovable, 0x8);

// 0x000d1ea8 rwSetHierarchyRoot (RW's static, compiled into this unit): `root` for the frame and its subtree.
void rwSetHierarchyRoot(RwFrame* frame, RwFrame* root);
DOTD_ASSERT_OFFSET(CSGMovable, m_pRwFrame, 0x04);
