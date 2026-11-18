// CKParticlesEffectNodeFx.h - a particle effect over particle nodes (key 0x1fcc, vtable 0xb1d4d8, size
// 0x30). Original unit: CKParticlesEffectNodeFx.cpp. Not in XXL2; the field names are the Ghidra struct's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CParticlesNodeFx;
class CKParticlesEffectFxData;
class CSGBranch;
class CSGHotSpot;

class CKParticlesEffectNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x7f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9acce0
        return key == 0x1fcc || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKParticlesEffectNodeFx)

    CKParticlesEffectNodeFx();  // inlined in 0x001cd9e0 CKParticlesEffectNodeFx_Create
    ~CKParticlesEffectNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001cd758 CKParticlesEffectNodeFx_Load
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001cda50
    // vt+0x30 0x001cd718 CKParticlesEffectNodeFx_PostLoad: IKNodeFx's, then the orientation refresh off.
    int32_t PostLoad(int32_t type) override;
    void Destroy() override {}  // vt+0x10 0x001cd3a0 CKParticlesEffectNodeFx_Destroy: empty (the node is kept)
    // vt+0x64 0x001ce3a0 StartParticleEffect: running; the nodes get their render priority and are placed: under the data's
    // attach node (+0x10, which becomes +0x24) or hot spot (+0x14), or in place, with the data's matrix (+0x24); screen
    // effects (data +0x38) go under the secondary scene root, scaled by the aspect. Each node's emitter gets its
    // parameter block, the emitters start and the effect's lifetime (+0x28) is set. Without data: stopped (vt+0x6c).
    void Vf64() override;
    // vt+0x78 0x001ce0a8 UpdateParticleEffectLifetime: the lifetime counts down; the nodes follow the data's matrix while
    // +0x2c is set; a timed effect (data flags 8 or 4) stops (vt+0x6c) when its lifetime is below 0.
    void Update(IKTime* frameClock) override;
    // vt+0x7c 0x001ce1e8 CKParticlesEffectNodeFx_StopIfLinkedTo: a running effect (bit 0 of the flags clear)
    // whose data has the attach flag (0x10) and an owner in that sector (not for sector 0) stops (vt+0x6c).
    void StopIfLinkedTo(int32_t sector) override;
    IKFxData* GetFxData() override;                // vt+0x80 0x009acd28 CKParticlesEffectNodeFx_GetFxData
    void SetFxData(IKFxData* data) override;       // vt+0x84 0x009acd30 CKParticlesEffectNodeFx_SetFxData
    // vt+0x6c 0x001cf0d0 StopParticleEffect: stopped; every node back under the dynamic scene root, emitting off, at the
    // identity, and hidden once it has no particle left; the data and the orientation refresh dropped.
    void Stop() override;
    // 0x001cd640 CKParticlesEffectNodeFx_AttachNodesToHotSpot_maybe (not virtual): every node taken off its parent and
    // hung under the hot spot (CSGHotSpot_AttachVolume).
    void AttachNodesToHotSpot(CSGHotSpot* hotSpot);

    CKParticlesEffectFxData* m_pEffectData;  // +0x14 the FX data (Ghidra pEffectData); not set by the constructor or Load
    CParticlesNodeFx** m_ppParticleNodes;    // +0x18 (Mem_AllocAligned16 in Load); the constructor sets 0
    uint32_t m_ui32NodeCapacity;             // +0x1c the constructor sets 1
    uint32_t m_ui32NodeCount;                // +0x20 the constructor sets 0
    CSGBranch* m_pAttachOwner;               // +0x24 Ghidra pAttachmentOwner_maybe: the node the particle nodes hang under (Start)
    float m_fRemainingSeconds;               // +0x28 Ghidra flRemainingSeconds: the lifetime left (Start, Update)
    uint8_t m_bRefreshOrientation;           // +0x2c Ghidra name; PostLoad (0x1cd718) sets 0; Update re-applies the matrix
    uint8_t m_pad2d[3];
};
static_assert(CKParticlesEffectNodeFx::kClassKey == 0x1fcc, "key");

struct CVector3;
class IKSerializable;
// 0x001cdce0 SetOwnedParticleEffectPosition: when `owner` holds the effect's reservation, every particle node's frame
// moved to `position` (the modelling position, the identity flag cleared, the frame marked dirty).
void SetOwnedParticleEffectPosition(CKParticlesEffectNodeFx* effect, const CVector3* position, const IKSerializable* owner);
// 0x001cdc08 SetOwnedParticleEffectTransform: when `owner` holds the effect's reservation, every particle node oriented
// along `at` / `up` (CSGMovable_SetOrientationFromAtUp).
void SetOwnedParticleEffectTransform(CKParticlesEffectNodeFx* effect, const CVector3* at, const CVector3* up,
                                     const IKSerializable* owner);
DOTD_ASSERT_SIZE(CKParticlesEffectNodeFx, 0x30);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_ppParticleNodes, 0x18);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_ui32NodeCapacity, 0x1c);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_ui32NodeCount, 0x20);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_pAttachOwner, 0x24);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_fRemainingSeconds, 0x28);
DOTD_ASSERT_OFFSET(CKParticlesEffectNodeFx, m_bRefreshOrientation, 0x2c);
