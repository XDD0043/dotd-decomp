// CKAttachObjectsCinematicBloc.h - attaches an object to another (key 0x248, vtable 0xb1b008, size 0x84). Original unit: CKAttachObjectsCinematicBloc.cpp.
// XXL2: the same members (m_v3OldPos and m_pOldMatrix are runtime); DotD adds +0x78.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/math/CMatrix34.h"

class IKFile;
class IKTime;

class CKAttachObjectsCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x9)
    DOTD_DECLARE_FACTORIES(CKAttachObjectsCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00172ee8 CKAttachObjectsCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKAttachObjectsCinematicBloc() {}
    ~CKAttachObjectsCinematicBloc() override {}
    // vt+0x10 0x00172f40 CKAttachObjectsCinematicBloc_Destroy: both matrices destroyed (the pointers kept).
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00173f38 CKAttachObjectsCinematicBloc_Load
    // vt+0x24 0x00172d20 CKAttachObjectsCinematicBloc_RecursiveRegistration: registered (unless 4..7), the base's, then the leaf's
    // when it has no parent (CSGLeaf +0x0c) and the hot spot's.
    void RecursiveRegistration(int32_t type) override;

    // vt+0x5c 0x00173a80 CKAttachObjectsCinematicBloc_Start: the blocs' start (StartCommon), the leaf's sector (-2 without a
    // leaf, +0x7c), its modelling matrix (+0x4c) and parent bone (+0x80) kept, then the leaf attached (to the hot spot, the
    // actor's bone or the actor / attach leaf); completed at once when there is nothing to attach to.
    void Start() override;
    void Complete() override;            // vt+0x64 0x00174880 CKAttachObjectsCinematicBloc_Complete (CompleteBloc)
    void Update(IKTime* time) override;  // vt+0x68 0x00172c80 CKAttachObjectsCinematicBloc_Update (CheckSekensStop only)
    // vt+0x6c 0x001737e8 CKAttachObjectsCinematicBloc_Stop: the attachment undone as Abort does, the bloc completed.
    void Stop() override;
    // vt+0x70 0x00173720 CKAttachObjectsCinematicBloc_Abort: not running, the attachment undone.
    void Abort() override;
    // 0x001731f8 CKAttachObjectsCinematicBloc_ApplyAttachment_maybe: `attach` 1 hangs the leaf under the hot spot or the
    // actor / attach leaf at m_v3Pos (its old parent and position kept), 0 takes it off again (AttachToParent).
    void ApplyAttachment(int32_t attach);
    // 0x00173038 CKAttachObjectsCinematicBloc_AttachToParent_maybe: a leaf without a parent goes back under its old parent
    // (on its old bone when that is an animated node, 0x54b), or its sector's root (the dynamic scene root for -2), keeping
    // its world placement; with m_bRestorePos its old matrix and position come back.
    void AttachToParent();
    // 0x00173488 CKAttachObjectsCinematicBloc_RestoreObject_maybe: `attach` 1 hangs the leaf on bone m_ui32BoneIndex of the
    // actor / attach leaf at m_v3Pos with m_pMatrixToApply, 0 takes it off again (AttachToParent).
    void RestoreObject(int32_t attach);
    // The actor's node (the scene data's hook's) or, without scene data, the attach leaf.
    bool HasTarget() const;
    class CSGBranch* Target() const;

    IKSerializable* m_pLeaf;        // +0x38 CSGLeaf
    IKSerializable* m_pLeafParent;  // +0x3c CSGBranch
    CVector3 m_v3OldPos;            // +0x40 read by the Load (after m_v3Pos)
    CMatrix34* m_pOldMatrix;        // +0x4c RwMatrixCreate, identity, whatever the type
    CMatrix34* m_pMatrixToApply;    // +0x50 RwMatrixCreate + CMatrix34_LoadMatrix
    CVector3 m_v3Pos;               // +0x54
    uint8_t m_bAttachToBone;        // +0x60
    uint8_t m_pad61[3];
    uint32_t m_ui32BoneIndex;       // +0x64
    uint8_t m_bRestorePos;          // +0x68
    uint8_t m_pad69[3];
    IKSerializable* m_pAttachLeaf;  // +0x6c CSGLeaf
    uint8_t m_bAttachToHotSpot;     // +0x70
    uint8_t m_pad71[3];
    IKSerializable* m_pHotSpot;     // +0x74 CSGHotSpot
    uint8_t m_unk78;                // +0x78 DotD
    uint8_t m_pad79[3];
    int32_t m_i32SectorIndex;       // +0x7c DotD runtime (Start): the leaf's sector (vt+0x6c), -2 without a leaf
    uint32_t m_ui32OldBone;         // +0x80 DotD runtime (Start): the leaf's parent bone (+0x14), 0xff none
};
DOTD_ASSERT_SIZE(CKAttachObjectsCinematicBloc, 0x84);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_pLeaf, +0x38);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_pLeafParent, +0x3c);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_v3OldPos, +0x40);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_pOldMatrix, +0x4c);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_pMatrixToApply, +0x50);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_v3Pos, +0x54);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_bAttachToBone, +0x60);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_ui32BoneIndex, +0x64);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_bRestorePos, +0x68);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_pAttachLeaf, +0x6c);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_bAttachToHotSpot, +0x70);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_pHotSpot, +0x74);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_unk78, +0x78);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_i32SectorIndex, +0x7c);
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_ui32OldBone, +0x80);
