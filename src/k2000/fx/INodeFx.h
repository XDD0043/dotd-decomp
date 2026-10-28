// INodeFx.h - a scene node that is an effect (key 0x50b, not registered; vtable 0xb18cc8; Ghidra calls
// its unit CNodeFx). Original unit: CNodeFx.cpp (0xec920-0xed0d0). XXL2: K/KModules/KGL/SceneGraph/
// NodeFx/INodeFx.h (XXL2 member: m_fDeltaTime); DotD adds three bytes that its Load reads.
// Size 0x2c: CTrailNodeFx and CParticlesNodeFx keep their own fields from +0x2c.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

class INodeFx : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x14)

    INodeFx() {}  // inlined in 0x000e6200 CreateCParticlesNodeFx: the vtable only
    ~INodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000eccd8 CNodeFx_Load

    // +0x24 XXL2 m_fDeltaTime: the particle node's frame time (PrepareParticleNodeForRendering /
    // UpdateParticleNodeSimulation); not set by the constructor or Load.
    float m_fDeltaTime;
    // +0x28..+0x2a: CNodeFx_PostLoadBase_maybe (0xeca78) copies them into bits 22, 23 and 25 of every
    // geometry's render flags.
    uint8_t m_unk28;
    uint8_t m_unk29;
    uint8_t m_unk2a;
    uint8_t m_pad2b;  // never written
};
static_assert(INodeFx::kClassKey == 0x50b, "key");
DOTD_ASSERT_SIZE(INodeFx, 0x2c);
DOTD_ASSERT_OFFSET(INodeFx, m_fDeltaTime, 0x24);
DOTD_ASSERT_OFFSET(INodeFx, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(INodeFx, m_unk29, 0x29);
DOTD_ASSERT_OFFSET(INodeFx, m_unk2a, 0x2a);
