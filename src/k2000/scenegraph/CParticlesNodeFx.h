// CParticlesNodeFx.h - a particle-emitter scene node (key 0x4cb, vtable 0xb18b18, size 0x68). Original
// units: CParticlesNodeFx.cpp (0xe5ba8-0xe5c80, the registration) and CParticlesNodeFx_2.cpp
// (0xe5fb8-0xe79f8). XXL2: K/KModules/KGL/SceneGraph/NodeFx/CParticlesNodeFx.h; the members DotD keeps
// are in XXL2's order (XXL2 reads m_ui8NbActivePoints, m_ui8NbEmitParticlesPerPoint, m_fCompensationCoeff,
// m_ai8BoneExclusion, then sets m_oldPosition and m_oldSpeed: the PS3 Load does the same at these offsets).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"
#include "k2000/math/CMatrix34.h"

struct RpPrtAdvEmtPointList;
struct RpPrtStdEmitter;

class CParticlesNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x13)
    DOTD_DECLARE_FACTORIES(CParticlesNodeFx)

    CParticlesNodeFx();  // inlined in 0x000e6200 CreateCParticlesNodeFx
    ~CParticlesNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000e6a00 CParticlesNodeFx_Load
    int32_t PostLoad(int32_t type) override;             // vt+0x30 0x000e65f0 CParticlesNodeFx_PostLoad
    // vt+0x58 0x000e5fe0 EnqueueParticleNodeRenderWork: the node queued in the engine's particle scheduler
    // (prepared before the stages run), its children traversed, flag 0x80000 cleared.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    // 0x000e6938 ParticleFxNode_StopEmitting_maybe (not virtual): an emitter with live particles stops emitting
    // (flags 0x80400 cleared), is updated once with twice its particle life as the time, and the atomic's
    // radius grows by the node's.
    void StopEmitting();
    float m_fBoundingRadius;               // +0x2c DotD; name from the Ghidra struct (flBoundingRadius)
    float m_fCompensationCoeff;            // +0x30
    CVector3 m_oldPosition;                // +0x34 Load: g_nullVector
    CVector3 m_oldSpeed;                   // +0x40 Load: g_nullVector
    float m_fEmissionSpeedAdjustment;      // +0x4c DotD; Ghidra name; PostLoad (0xe65f0) sets 0
    uint8_t m_ui8NbActivePoints;           // +0x50
    uint8_t m_ui8NbEmitParticlesPerPoint;  // +0x51
    uint16_t m_ui16Pad;                    // +0x52 never written
    // +0x54 XXL2 RpPrtAdvEmtPointList*; the constructor sets 0, PostLoad points it into the emitter (property
    // 0x1000006), as XXL2's.
    RpPrtAdvEmtPointList* m_pAdvEmtPointList;
    RpPrtStdEmitter* m_pRpPrtStdEmitter;   // +0x58 XXL2 RpPrtStdEmitter*; set by PostLoad (the atomic's emitter)
    int8_t m_ai8BoneExclusion[4];          // +0x5c read raw (the file bytes)
    uint32_t m_ui32LastUpdateGeneration;   // +0x60 DotD; Ghidra dwLastUpdateGeneration; the constructor sets 0xffffffff
    uint8_t m_bReadyForWorkerUpdate;       // +0x64 DotD; Ghidra name; the constructor sets 0
    uint8_t m_pad65[3];
};
static_assert(CParticlesNodeFx::kClassKey == 0x4cb, "key");
DOTD_ASSERT_SIZE(CParticlesNodeFx, 0x68);

// 0x000e6ba8 UpdateParticleNodeSimulation (the scheduler's update of a ready node)
void UpdateParticleNodeSimulation(CParticlesNodeFx* node, IKTime* frameClock);
// 0x000e6c60 PrepareParticleNodeForRendering (PrepareQueuedParticleNodes)
void PrepareParticleNodeForRendering(CParticlesNodeFx* node, RenderQueue** stages, IKTime* frameClock, RwCamera* camera);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_fBoundingRadius, 0x2c);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_fCompensationCoeff, 0x30);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_oldPosition, 0x34);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_oldSpeed, 0x40);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_ui8NbActivePoints, 0x50);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_ui8NbEmitParticlesPerPoint, 0x51);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_pAdvEmtPointList, 0x54);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_ai8BoneExclusion, 0x5c);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_ui32LastUpdateGeneration, 0x60);
DOTD_ASSERT_OFFSET(CParticlesNodeFx, m_bReadyForWorkerUpdate, 0x64);
