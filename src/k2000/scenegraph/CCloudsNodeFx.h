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

class CCloudsNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x21)
    DOTD_DECLARE_FACTORIES(CCloudsNodeFx)

    CCloudsNodeFx() {}  // 0x000d8968 CCloudsNodeFx_Create: CNode's constructor, then the vtables
    ~CCloudsNodeFx() override {}

    // vt+0x2c 0x000d89c8 CCloudsNodeFx_Load: the limits and the middle weather preset for every type, the
    // tank reference for type 0, then the preset copied to the first and last presets.
    int32_t Load(IKFile* file, int32_t type) override;

    IKSerializable* m_pCloudTank;            // +0x2c a CParticleGeometry; Load sets 0 first
    uint8_t m_asClusters[100][0x104];        // +0x30 XXL2 SCloudsClusterData[100] (runtime)
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
