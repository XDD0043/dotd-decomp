// CCloudsNodeFx.h - a cloud layer effect (key 0x84b, vtable 0xb18910, size 0x6678; LVL040). Original unit:
// CCloudsNodeFx.cpp. XXL2: K/KModules/kgl/SceneGraph/NodeFx/CCloudsNodeFx.h, the same members at the
// same (32-bit) offsets: m_pCloudTank, m_asClusters[100], m_asWeather[3], then the scalars.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"

// XXL2 SCloudsWeatherPreset (0x34 bytes).
struct SCloudsWeatherPreset {
    float m_fMedHeight;                       // +0x00
    float m_fDeltaHeight;                     // +0x04
    float m_fMedSize;                         // +0x08
    float m_fDeltaSize;                       // +0x0c
    float m_fClusterLateralSpread;            // +0x10
    float m_fClusterVerticalSpread;           // +0x14
    float m_fWindSpeed;                       // +0x18
    float m_fWindDir;                         // +0x1c
    uint32_t m_ui32ExternNbClusters;          // +0x20
    uint32_t m_ui32MedNbCloudsPerCluster;     // +0x24
    uint32_t m_ui32DeltaNbCloudsPerCluster;   // +0x28
    uint8_t m_acColor[2][4];                  // +0x2c CColor[2], read raw (file bytes)
};
DOTD_ASSERT_SIZE(SCloudsWeatherPreset, 0x34);

// One cloud of a cluster (0x18 bytes; XXL2 SCloudsClusterData's cloud entries, names ours): InitCloud draws them.
struct SCloudData_maybe {
    float m_afUnk00[3];  // +0x00 three draws in [-1, 1]: the offset in the cluster (times the lateral / vertical spreads)
    float m_fUnk0c;      // +0x0c a draw in [-1, 1] (drawn first): the size (times the delta size, plus the medium size)
    float m_fUnk10;      // +0x10 0 or 0.5 (bit 15 of a draw): the tex coord quarter's u
    float m_fUnk14;      // +0x14 0 or 0.5: its v
};
// XXL2 SCloudsClusterData (0x104 bytes; the member names ours).
struct SCloudsClusterData {
    float m_afPos[3];             // +0x00 x at the far limit (or a draw), y on the delta height, z a draw
    float m_fUnk0c;               // +0x0c the fade (alpha factor): 1 when made visible, else 0; UpdateClouds moves it
    uint32_t m_ui32NbClouds;      // +0x10 1..10
    SCloudData_maybe m_asClouds[10];  // +0x14
};
DOTD_ASSERT_SIZE(SCloudsClusterData, 0x104);

class CCloudsNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x21)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a4ca0
        return key == 0x84b || key == 0x50b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CCloudsNodeFx)

    CCloudsNodeFx() {}  // 0x000d8968 CCloudsNodeFx_Create: CNode's constructor, then the vtables
    ~CCloudsNodeFx() override {}

    // vt+0x2c 0x000d89c8 CCloudsNodeFx_Load: the limits and the middle weather preset for every type, the
    // tank reference for type 0, then the preset copied to the first and last presets.
    int32_t Load(IKFile* file, int32_t type) override;

    // 0x000d8178 CCloudsNodeFx_InitCloud_maybe: cluster `index` (< 100) redrawn from the current preset (m_asWeather[0]):
    // its cloud count (med +- delta, 1..10), its position (x at -far with `atFarEdge`, else a draw), its clouds; +0x0c 1
    // with `visible`. 2 + n * 6 draws (3 + n * 6 without `atFarEdge`).
    void InitCloud(uint32_t index, int32_t atFarEdge, int32_t visible);
    // 0x000d8728 CCloudsNodeFx_SetTargetParams_maybe: `preset` becomes the pending and the current preset, the state
    // interpolation 1.
    void SetTargetParams(const SCloudsWeatherPreset* preset);
    // 0x000d8818 CCloudsNodeFx_ApplyPendingParams_maybe: the pending preset made current, every cluster of its count
    // redrawn (InitCloud(i, 0, 1)), the interpolations reset; shown (m_ba8Infos bit 0, the node's hidden bit 2 clear)
    // with `shown` 1, hidden with 0.
    void ApplyPendingParams(uint8_t shown);
    // 0x000d8688 CCloudsNodeFx_BeginParamTransition_maybe (port-final F05): a transition toward `preset` over `duration`
    // seconds (the target preset m_asWeather[2] without the two sizes). Its only callers are dead (CKHkWeatherCenter).
    void BeginParamTransition(const SCloudsWeatherPreset* preset, float duration);

    // vt+0x58 0x000da088 CCloudsNodeFx_vf58 (port-last Z8): unless hidden (flag 4), the clock stopped (+0x30) or the
    // layer not shown (m_ba8Infos bit 0): UpdateClouds, the tank atomic's sphere made the null vector with radius 1e10
    // (resynced first when dirty; dirty bit cleared, world bound marked), the node's geometry culled and queued (vt+0x84).
    // No frame stamp, no children (unlike CNode's).
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
    // 0x000d94e0 CCloudsNodeFx_UpdateClouds_maybe (port-last Z8): the preset transition (cosine ease), the cluster
    // count, the clusters' wind drift and fades (InitCloud at the far edge: rand draws), the PTank's particle count,
    // then WritePTankVertices.
    void UpdateClouds(IKTime* frameClock);
    // 0x000d8d90 CCloudsNodeFx_WritePTankVertices_maybe (port-last Z8): every cloud's position (the cluster turned by
    // the wind direction around the camera), size, tex coords and colour (by the cluster's x, faded) into the tank.
    void WritePTankVertices();

    IKSerializable* m_pCloudTank;            // +0x2c a CParticleGeometry; Load sets 0 first
    SCloudsClusterData m_asClusters[100];    // +0x30 XXL2 SCloudsClusterData[100] (runtime)
    SCloudsWeatherPreset m_asWeather[3];     // +0x65c0
    float m_fFarLimit;                       // +0x665c
    float m_fShowSpeed;                      // +0x6660
    uint32_t m_ui32NbActiveClusters;         // +0x6664
    uint32_t m_ui32NbClusters;               // +0x6668
    float m_fStateInterpolation;             // +0x666c Load sets 1.0f (TOC -0x50e4)
    float m_fSpeedInterpolation;             // +0x6670 Load sets 0
    uint8_t m_ui8InitialPreset;              // +0x6674
    uint8_t m_ui8FinalPreset;                // +0x6675
    uint8_t m_ba8Infos;                      // +0x6676 Load sets 0
    uint8_t m_pad6677;
};
static_assert(CCloudsNodeFx::kClassKey == 0x84b, "key");
DOTD_ASSERT_SIZE(CCloudsNodeFx, 0x6678);
DOTD_ASSERT_OFFSET(CCloudsNodeFx, m_pCloudTank, 0x2c);
DOTD_ASSERT_OFFSET(CCloudsNodeFx, m_asWeather, 0x65c0);
DOTD_ASSERT_OFFSET(CCloudsNodeFx, m_fFarLimit, 0x665c);
DOTD_ASSERT_OFFSET(CCloudsNodeFx, m_fStateInterpolation, 0x666c);
DOTD_ASSERT_OFFSET(CCloudsNodeFx, m_ba8Infos, 0x6676);
