// CKMeshPopNodeFx.h - the mesh-pop effect node (key 0xa24c, vtable 0xb1d3c8, size 0x38). Original unit:
// CKMeshPopNodeFx.cpp (0x1c9338-0x1cbc50). Its data is CKMeshPopFxData (0xa28c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKMeshPopNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x289)
    DOTD_DECLARE_FACTORIES(CKMeshPopNodeFx)

    CKMeshPopNodeFx() {}  // inlined in 0x001c99a8 CKMeshPopNodeFx_Create: the IKNodeFx part only
    ~CKMeshPopNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001ca048 CKMeshPopNodeFx_Load
    // vt+0x30 0x1ca850 CKMeshPopNodeFx_PostLoad: sets the node's scene flag 4, creates the two matrices
    // +0x20/+0x24 (type 0), zeroes +0x1c/+0x2c and sets the floats +0x28/+0x30/+0x34.
    int32_t PostLoad(int32_t type) override;

    IKSerializable* m_pFxData;   // +0x14 the inline GetFxData/SetFxData (0x9acc20/0x9acc28) use it
    // +0x18 an object reference (Ghidra draft: CKMoveCpntUpdater*; LVL010 references class 0x1c6).
    IKSerializable* m_pMoveUpdater;
    uint32_t m_unk1c;            // +0x1c PostLoad sets 0
    CMatrix34* m_unk20;              // +0x20 PostLoad: RwMatrixCreate
    CMatrix34* m_unk24;              // +0x24 PostLoad: RwMatrixCreate
    float m_unk28;               // +0x28 PostLoad
    uint32_t m_unk2c;            // +0x2c PostLoad sets 0
    float m_unk30;               // +0x30 PostLoad
    float m_unk34;               // +0x34 PostLoad
};
static_assert(CKMeshPopNodeFx::kClassKey == 0xa24c, "key");
DOTD_ASSERT_SIZE(CKMeshPopNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CKMeshPopNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKMeshPopNodeFx, m_pMoveUpdater, 0x18);
DOTD_ASSERT_OFFSET(CKMeshPopNodeFx, m_unk34, 0x34);
