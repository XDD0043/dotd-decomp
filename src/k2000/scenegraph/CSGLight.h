// CSGLight.h - a scene-graph light (key 0x80b, vtable 0xb18270, size 0x64). Original unit: CSGLight.cpp
// (0xcf6e0-0xd07b8). XXL2: K/KModules/KGL/SceneGraph/CSGLight.h, the same members in the same order,
// except that DotD keeps the light sets in a growable array (XXL2: CLightSet*[16]).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CBBox.h"
#include "k2000/scenegraph/CSGLeaf.h"

class CSGLight : public CSGLeaf {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x20)
    DOTD_DECLARE_FACTORIES(CSGLight)

    CSGLight();  // inlined in 0x000cfb50 CSGLight_Create
    ~CSGLight() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000d0008 CSGLight_Load
    // vt+0x58 0x000cfbc0 CSGLight_Enqueue: the colour animations advance; unless hidden (flag 4) the world influence box is
    // made (once, or every frame for a dynamic light, flag 0x10), the frame stamped and the zones told (ComputeZoneOverlapWeights).
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
    // 0x0009d8a8 CSGLight_ComputeZoneOverlapWeights_maybe (CLightManager.cpp)
    void ComputeZoneOverlapWeights();

    IKSerializable** m_aplightParameters;  // +0x18 CLightComponent* array (Mem_AllocAligned16 in Load)
    uint32_t m_ui32NbActiveLights;         // +0x1c
    uint32_t m_eLightBoxType;              // +0x20 XXL2 CSGLight::ELightBoxType
    // +0x24 CLightSet* array, its capacity and its count (names ours). The constructor sets 0, 2, 0; Load
    // replaces them only when the file has light sets.
    IKSerializable** m_apLightSets;
    uint32_t m_ui32LightSetCapacity;       // +0x28
    uint32_t m_ui32NbLightSets;            // +0x2c
    CBBox m_xLocalInfluenceBBox;           // +0x30
    CBBox m_xWorldInfluenceBBox;           // +0x48 not set by the constructor or Load
    uint32_t m_ui32OcclusionLevel;         // +0x60
};
static_assert(CSGLight::kClassKey == 0x80b, "key");
DOTD_ASSERT_SIZE(CSGLight, 0x64);
DOTD_ASSERT_OFFSET(CSGLight, m_aplightParameters, 0x18);
DOTD_ASSERT_OFFSET(CSGLight, m_ui32NbActiveLights, 0x1c);
DOTD_ASSERT_OFFSET(CSGLight, m_eLightBoxType, 0x20);
DOTD_ASSERT_OFFSET(CSGLight, m_apLightSets, 0x24);
DOTD_ASSERT_OFFSET(CSGLight, m_ui32LightSetCapacity, 0x28);
DOTD_ASSERT_OFFSET(CSGLight, m_ui32NbLightSets, 0x2c);
DOTD_ASSERT_OFFSET(CSGLight, m_xLocalInfluenceBBox, 0x30);
DOTD_ASSERT_OFFSET(CSGLight, m_xWorldInfluenceBBox, 0x48);
DOTD_ASSERT_OFFSET(CSGLight, m_ui32OcclusionLevel, 0x60);
