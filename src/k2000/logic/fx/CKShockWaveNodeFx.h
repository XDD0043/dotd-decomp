// CKShockWaveNodeFx.h - the shockwave effect node (key 0x30cc, vtable 0xb1d808, size 0x58). Original unit:
// CKShockWaveNodeFx.cpp (0x1d22e8-0x1d3400). Its data is CKShockWaveFxData (0x310c). Not in XXL2; names ours.
// Load reads only the IKNodeFx part; everything else is set at run time.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKShockWaveNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc3)
    DOTD_DECLARE_FACTORIES(CKShockWaveNodeFx)

    CKShockWaveNodeFx() {}  // inlined in 0x001d2648 CKShockWaveNodeFx_Create: the IKNodeFx part only
    ~CKShockWaveNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d24b0 CKShockWaveNodeFx_Load
    // vt+0x30 PostLoad 0x1d2338 (stays the default in C2.1).

    uint32_t m_unk14;            // +0x14
    IKSerializable* m_pFxData;   // +0x18 the inline GetFxData (0x9ad268) returns it
    uint32_t m_unk1c[14];        // +0x1c (word, heap pointer) pairs live; not set by Load
    int32_t m_unk54;             // +0x54
};
static_assert(CKShockWaveNodeFx::kClassKey == 0x30cc, "key");
DOTD_ASSERT_SIZE(CKShockWaveNodeFx, 0x58);
DOTD_ASSERT_OFFSET(CKShockWaveNodeFx, m_pFxData, 0x18);
DOTD_ASSERT_OFFSET(CKShockWaveNodeFx, m_unk54, 0x54);
