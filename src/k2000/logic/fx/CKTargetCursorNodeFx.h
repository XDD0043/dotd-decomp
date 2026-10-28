// CKTargetCursorNodeFx.h - the target-cursor effect node (key 0x460c, vtable 0xb1da88, size 0x38). Original
// unit: CKTargetCursorNodeFx.cpp. Its data is CKTargetCursorFxData (0x464c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKTargetCursorNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x118)
    DOTD_DECLARE_FACTORIES(CKTargetCursorNodeFx)

    CKTargetCursorNodeFx() {}  // inlined in 0x001d5e70 CKTargetCursorNodeFx_Create: the IKNodeFx part only
    ~CKTargetCursorNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d5ca0 CKTargetCursorNodeFx_Load
    // vt+0x30 0x1d5c48 CKTargetCursorNodeFx_PostLoad: IKNodeFx's, then (level type) the matrix at +0x1c.
    int32_t PostLoad(int32_t type) override;

    IKSerializable* m_pFxData;   // +0x14 (Ghidra draft: CKTargetCursorFxData*)
    CNode* m_pCursorNode;        // +0x18 a second scene node (Ghidra draft: CNode*)
    CMatrix34* m_pMatrix1c;      // +0x1c PostLoad: RwMatrixCreate_Thunk
    uint32_t m_unk20[6];         // +0x20 run-time state
};
static_assert(CKTargetCursorNodeFx::kClassKey == 0x460c, "key");
DOTD_ASSERT_SIZE(CKTargetCursorNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CKTargetCursorNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKTargetCursorNodeFx, m_pCursorNode, 0x18);
