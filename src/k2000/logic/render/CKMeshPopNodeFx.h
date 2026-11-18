// CKMeshPopNodeFx.h - the mesh-pop effect node (key 0xa24c, vtable 0xb1d3c8, size 0x38). Original unit:
// CKMeshPopNodeFx.cpp (0x1c9338-0x1cbc50). Its data is CKMeshPopFxData (0xa28c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKMeshPopFxData;
class CKMoveCpntUpdater;
class IKTime;

// A mesh pop: each pop shows the node at a scattered, tilted, scaled copy of its placement (+0x20 -> +0x24), plays
// the data's movement on it and fades it by the alpha curve over a drawn life; a pop can spawn sibling pops (the
// data's count) from the effect pool, and a repeating one (+0x18) pops again every drawn interval while active.
// m_baFxData: bit 0 stopped, 1 reserved, 2 popping, 3 repeating.
class CKMeshPopNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x289)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9acbd0
        return key == 0xa24c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKMeshPopNodeFx)

    CKMeshPopNodeFx() {}  // inlined in 0x001c99a8 CKMeshPopNodeFx_Create: the IKNodeFx part only
    ~CKMeshPopNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001ca048 CKMeshPopNodeFx_Load
    // vt+0x30 0x1ca850 CKMeshPopNodeFx_PostLoad: sets the node's scene flag 4, creates the two matrices
    // +0x20/+0x24 (type 0), zeroes +0x1c/+0x2c and sets the floats +0x28/+0x30/+0x34.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x001c97e8 CKMeshPopNodeFx_RecursiveRegistration: registered with the saving manager, the node base's,
    // then (type 0) the move updater (+0x18).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x001c98a8 CKMeshPopNodeFx_Destroy: both matrices destroyed and cleared (the node base's is not called).
    void Destroy() override;
    // vt+0x64 0x001ca730 CKMeshPopNodeFx_Start: not stopped, both matrices identity, the timers reset (life 3600, scale
    // 1, ring angle -1); without data it stops, otherwise it is neither popping nor repeating.
    void Vf64() override;
    // vt+0x6c 0x001c9c70 CKMeshPopNodeFx_Stop: stopped and released, a running pop's movement stopped and dropped, the
    // node moved under the dynamic root and hidden, neither popping nor repeating.
    void Stop() override;
    // vt+0x78 0x001cb6e8 CKMeshPopNodeFx_Update: the pop's clock; a popping node past its life (or its movement
    // over) stops (a repeating one only ends the pop: the movement dropped, the node hidden); otherwise the node back
    // at the scattered matrix, the movement's sample (its scales by the pop's scale) applied and the alpha updated.
    // A repeating node counts down the interval and then pops a pooled sibling (its placement copied) and draws the
    // next interval.
    void Update(IKTime* frameClock) override;
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }  // vt+0x80 0x9acc20
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x9acc28

    // 0x001cb568 CKMeshPopNodeFx_SetActive_maybe (owned by `owner` with a node): on, an idle node pops (a repeating
    // data keeps it repeating) and draws the first interval; off, a repeating node stops when it is not popping, or
    // only stops repeating.
    void SetActive(const IKSerializable* owner, int32_t active);
    // 0x001c9428 CKMeshPopNodeFx_SetMatrixForOwner_maybe: the placement (+0x20) copied from `matrix` when owned by `owner`.
    void SetMatrixForOwner(const IKSerializable* owner, const CMatrix34* matrix);
    // 0x001c9c08 CKMeshPopNodeFx_SetPositionForOwner_maybe: the placement's (+0x20) position when owned by `owner`.
    void SetPositionForOwner(const IKSerializable* owner, const CVector3* position);
    // 0x001c9d90 CKMeshPopNodeFx_PlaceWithRandomYaw_maybe (when owned by `owner`): the placement (+0x20) at `position`,
    // its up `up` and its at the z axis (Mat4_BuildFromUpAndForward), then turned about its own y by a random angle
    // (one Rand_Int draw: & 0xffff / 65535 * 360 degrees).
    void PlaceWithRandomYaw(const IKSerializable* owner, const CVector3* up, const CVector3* position);
    // 0x001caf50 CKMeshPopNodeFx_TriggerPop_maybe (owned by `owner`, a node, idle): popping; a first pop (`child` 0)
    // draws the count and pops count - 1 pooled siblings (their ring angles, this placement) before its own
    // placement, movement start, scale and life draws.
    void TriggerPop(const IKSerializable* owner, int32_t child);
    // 0x001ca978 CKMeshPopNodeFx_PlaceAtTarget_maybe: the node detached and hung by the data's placement (+0x19,
    // +0x08, +0x0c), the scattered matrix (+0x24) from the placement, then scattered (mode 2).
    void PlaceAtTarget(const IKSerializable* owner);
    // 0x001ca108 CKMeshPopNodeFx_ScatterElementRandomOffset_maybe: mode 0 offsets `m` along a direction on the ring
    // (+0x34 >= 0, spread +0x50) or a random one by the drawn distance, plus the data's offset; mode 2 also faces away
    // (+0x44) and turns it; mode 1 only turns it: a random yaw (+0x48) about its up axis, then a random tilt (+0x34)
    // about a random horizontal axis, both through its position.
    void ScatterElementRandomOffset(CMatrix34* m, int32_t mode);
    // 0x001c9580 CKMeshPopNodeFx_ApplyAlphaCurve_maybe: the alpha curve at (+0x2c / life x time) as the node's
    // geometries' alpha (a blended geometry of an additive kind kept opaque), their properties refreshed when the
    // transparency bit changes.
    void ApplyAlphaCurve();
    // 0x001c9728 CKMeshPopNodeFx_ApplyMoveUpdater_maybe: the move updater advanced by the clock's step, its scales
    // ((s + 1) x the pop's scale - 1) and applied to the node. No caller found in the EBOOT (no bl; its descriptor
    // 0xb71798 has no reference); Update inlines the same steps.
    void ApplyMoveUpdater(IKTime* frameClock);
    // 0x001c9a00 CKMeshPopNodeFx_SetUpDirForOwner_maybe (when owned by `owner`): the placement (+0x20) at the scattered
    // matrix's position (+0x24), its up `up` and its at the z axis, then turned about its own y by a random angle (one
    // Rand_Int draw). No caller found in the EBOOT (its descriptor 0xb717d0 has no reference).
    void SetUpDirForOwner(const IKSerializable* owner, const CVector3* up);

    CKMeshPopFxData* FxData() const { return reinterpret_cast<CKMeshPopFxData*>(m_pFxData); }
    CKMoveCpntUpdater* MoveUpdater() const { return reinterpret_cast<CKMoveCpntUpdater*>(m_pMoveUpdater); }
    bool OwnedBy(const IKSerializable* owner) const { return (m_baFxData & 2u) != 0 && m_pOwner == owner; }

    IKSerializable* m_pFxData;   // +0x14 the inline GetFxData/SetFxData (0x9acc20/0x9acc28) use it
    // +0x18 the CKMoveCpntUpdater the pops drive (LVL010 references class 0x1c6).
    IKSerializable* m_pMoveUpdater;
    float m_unk1c;               // +0x1c the pop's time (PostLoad / Start / TriggerPop 0, Update adds dt)
    CMatrix34* m_unk20;          // +0x20 the placement (PostLoad: RwMatrixCreate)
    CMatrix34* m_unk24;          // +0x24 the scattered matrix the pop starts from (PostLoad: RwMatrixCreate)
    float m_unk28;               // +0x28 the pop's life (PostLoad / Start 3600, TriggerPop draws it)
    float m_unk2c;               // +0x2c the repeat countdown
    float m_unk30;               // +0x30 the pop's scale (TriggerPop: 1 + its percent draw)
    float m_unk34;               // +0x34 the ring angle (radians; -1: a random direction)
};
static_assert(CKMeshPopNodeFx::kClassKey == 0xa24c, "key");
DOTD_ASSERT_SIZE(CKMeshPopNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CKMeshPopNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKMeshPopNodeFx, m_pMoveUpdater, 0x18);
DOTD_ASSERT_OFFSET(CKMeshPopNodeFx, m_unk34, 0x34);
