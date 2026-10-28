// CKParticlesEffectNodeFx.h - a particle effect over particle nodes (key 0x1fcc, vtable 0xb1d4d8, size
// 0x30). Original unit: CKParticlesEffectNodeFx.cpp. Not in XXL2; the field names are the Ghidra struct's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CParticlesNodeFx;
class CKParticlesEffectFxData;

class CKParticlesEffectNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x7f)
    DOTD_DECLARE_FACTORIES(CKParticlesEffectNodeFx)

    CKParticlesEffectNodeFx();  // inlined in 0x001cd9e0 CKParticlesEffectNodeFx_Create
    ~CKParticlesEffectNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001cd758 CKParticlesEffectNodeFx_Load
    // vt+0x7c 0x001ce1e8 CKParticlesEffectNodeFx_StopIfLinkedTo: a running effect (bit 0 of the flags clear)
    // whose data has the attach flag (0x10) and an owner in that sector (not for sector 0) stops (vt+0x6c).
    void StopIfLinkedTo(int32_t sector) override;
    IKFxData* GetFxData() override;                // vt+0x80 0x009acd28 CKParticlesEffectNodeFx_GetFxData
    void SetFxData(IKFxData* data) override;       // vt+0x84 0x009acd30 CKParticlesEffectNodeFx_SetFxData
    // vt+0x6c 0x001cf0d0 StopParticleEffect. STUB(C2.2): hooks family (the effect runtime).
    void Stop() override;

    CKParticlesEffectFxData* m_pEffectData;  // +0x14 the FX data (Ghidra pEffectData); not set by the constructor or Load
    CParticlesNodeFx** m_ppParticleNodes;    // +0x18 (Mem_AllocAligned16 in Load); the constructor sets 0
    uint32_t m_ui32NodeCapacity;             // +0x1c the constructor sets 1
    uint32_t m_ui32NodeCount;                // +0x20 the constructor sets 0
    uint32_t m_unk24;                        // +0x24
    uint32_t m_unk28;                        // +0x28
    uint8_t m_bRefreshOrientation;           // +0x2c Ghidra name; PostLoad (0x1cd718) sets 0
    uint8_t m_pad2d[3];
};
static_assert(CKParticlesEffectNodeFx::kClassKey == 0x1fcc, "key");
DOTD_ASSERT_SIZE(CKParticlesEffectNodeFx, 0x30);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_ppParticleNodes, 0x18);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_ui32NodeCapacity, 0x1c);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_ui32NodeCount, 0x20);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_bRefreshOrientation, 0x2c);
