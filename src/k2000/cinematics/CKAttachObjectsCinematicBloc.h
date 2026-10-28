// CKAttachObjectsCinematicBloc.h - attaches an object to another (key 0x248, vtable 0xb1b008, size 0x84). Original unit: CKAttachObjectsCinematicBloc.cpp.
// XXL2: the same members (m_v3OldPos and m_pOldMatrix are runtime); DotD adds +0x78.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/math/CMatrix34.h"

class IKFile;

class CKAttachObjectsCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x9)
    DOTD_DECLARE_FACTORIES(CKAttachObjectsCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00172ee8 CKAttachObjectsCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKAttachObjectsCinematicBloc() {}
    ~CKAttachObjectsCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00173f38 CKAttachObjectsCinematicBloc_Load

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
    uint32_t m_unk7c[2];            // +0x7c DotD; not set by the constructor nor the Load
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
DOTD_ASSERT_OFFSET(CKAttachObjectsCinematicBloc, m_unk7c, +0x7c);
