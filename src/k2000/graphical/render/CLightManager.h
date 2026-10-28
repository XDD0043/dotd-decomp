// CLightManager.h - the level's light sets and hardware lights (key 0x90d, vtable 0xb16f40, size 0x64).
// Original unit: CLightManager.cpp (0x97e50-0x9e1a0; CLightSet's code is there too). XXL2:
// K/KModules/KGL/Main/CLightManager.h (m_vLightSets, m_pPreviousLightSet, m_pAmbientLight,
// m_aHardwareDirectionalLights[4]); DotD adds three vectors after m_vLightSets. A renderer stage
// manager: created by InitializeRendererStages (renderer +0xac), handed to the loader as the global 13:36.
//
// C2.4 step 6: the light rig and the lighting the shaders read. The manager keeps one ambient and four directional
// RpLights (Renderer_CreateWorldLights_maybe 0x9a5f0); ApplyLightingZone (0x994e8) loads them from a CLightSet (the zone
// an object is lit by: its five light components) before the object draws, and the shader fillers read the rig back
// (ComputeLightCount 0x9b208, LightRig_GetNextDistinctLight 0x9ae28, the ambient colour, the point lights near the
// object). The zones' components are made each frame from the scene-graph lights (CSGLight) whose boxes overlap the
// zone (CSGLight_ComputeZoneOverlapWeights 0x9d8a8, LightZone_AccumulateLights 0x981c8, UpdateAndExtract 0x9d1a0).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CLightSet;
struct RpLight;

class CLightManager : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x24)
    DOTD_DECLARE_FACTORIES(CLightManager)

    CLightManager();                  // 0x0009c660 CLightManager_Create (inlined; = CLightManager_Construct 0x97e50)
    ~CLightManager() override {}      // STUB(C1.6): 0x9deb8 / 0x9ddb0
    // vt+0x08 0x99c9f0
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x90d || key == 0xa8d || key == 0xc; }
    void Destroy() override;  // vt+0x10 0x0009c068 CLightManager_Destroy
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x0009c988 CLightManager_Load
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x99ca28
    // vt+0x54 0x0009afe0 CLightManager_PreUpdate: the rig black (ApplyLightingZone with no zone), every light set's world
    // influence box brought up to date.
    void PreUpdate(IKTime* frameClock) override;
    // vt+0x58 0x0009d1a0 CLightManager_UpdateAndExtract: every light set's components made from this frame's lights, the point
    // lights near the focus chosen, the point light nodes' own update.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
    void Render() override {}                               // vt+0x5c 0x99ca30 (empty)
    // vt+0x70 0x0009b0d8 CLightManager_CanBeUpdated: the renderer's bit 1 (the scene roots are not extracted) is clear.
    int32_t CanBeUpdated() override;

    // ---- the light rig (C2.4 step 6) ------------------------------------------------------------------------------
    // 0x0009a5f0 Renderer_CreateWorldLights_maybe (InitializeRendererStages): the ambient light and four directional lights
    // (each with its own frame), all black and in the world.
    void CreateWorldLights();
    // 0x0009b3a8 CLightManager_DestroyRwLights_maybe (CRenderer_Shutdown): the lights out of the world and destroyed.
    void DestroyRwLights();
    // 0x000994e8 ApplyLightingZone: the rig takes the lighting of `zone` (null: all black); `flat` (the object's bit 7: lit by
    // one averaged ambient colour, no directional lights) is remembered with the zone. A zone of another sector is not applied.
    void ApplyLightingZone(const CLightSet* zone, uint8_t flat);
    // 0x0009b208 CLightManager_ComputeLightCount_maybe: the directional lights of the rig that are not black (see the .cpp).
    uint32_t ComputeLightCount() const;
    // 0x0009ae28 LightRig_GetNextDistinctLight_maybe: from `index`, the next directional light that is not black: its colour
    // (red in the top byte), its direction. Returns the index after it (4: none left); the callers store it and ask again.
    uint32_t GetNextDistinctLight(uint32_t index, CVector3* direction, uint32_t* color) const;
    // The ambient colour of the rig (+0x18 .. +0x24 of its RpLight, as the ambient uniform fill reads it).
    const float* GetAmbientColor() const;

    // ---- the point lights ----------------------------------------------------------------------------------------------
    // 0x0009c308 CLightManager_GatherPointLightsNearFocus_maybe: the enabled point lights (m_vUnk24) in the frustum and within
    // 50 units of the camera, nearest first (m_vUnk30).
    void GatherPointLightsNearFocus();
    // 0x0009c150 CLightManager_GatherLightsTouchingSphere_maybe: from those, the ones whose spheres touch `sphere` (x, y, z, r),
    // into m_vUnk3c; returns how many.
    uint32_t GatherLightsTouchingSphere(const float sphere[4]);
    // The lights gathered by the last GatherLightsTouchingSphere: 0x9b068 position, 0x9ad60 colour (red first), 0x9adf0 radius,
    // 0x9ad30 intensity-ish float (the point light node's +0x1c). Beyond the count: zeros.
    void GetLightPosition(CVector3* position, int32_t index) const;
    void GetLightColor(uint8_t color[4], int32_t index) const;
    float GetLightRadius(int32_t index) const;
    float GetLightField1C(int32_t index) const;

    TVector<CLightSet*, 2> m_vLightSets;    // +0x18 references; the constructor sets capacity 2
    TVector<IKSerializable*, 1> m_vUnk24;   // +0x24 references: the point lights (CSGPointLight, 10 in LVL010); capacity 1
    TVector<IKSerializable*, 1> m_vUnk30;   // +0x30 the point lights near the focus (nearest first); Load reserves as many as m_vUnk24
    TVector<IKSerializable*, 1> m_vUnk3c;   // +0x3c the point lights touching the last sphere
    const CLightSet* m_pPreviousLightSet;   // +0x48 the zone the rig was last loaded from (the render queues compare it with the item's)
    uint8_t m_ui8PreviousFlat;              // +0x4c a byte: the `flat` flag of that application
    uint8_t m_pad4d[3];
    RpLight* m_pAmbientLight;               // +0x50 the constructor sets 0
    RpLight* m_aHardwareDirectionalLights[4];  // +0x54 the constructor sets 0
};
DOTD_ASSERT_SIZE(CLightManager, 0x64);
DOTD_ASSERT_OFFSET(CLightManager, m_vLightSets, 0x18);
DOTD_ASSERT_OFFSET(CLightManager, m_vUnk24, 0x24);
DOTD_ASSERT_OFFSET(CLightManager, m_vUnk30, 0x30);
DOTD_ASSERT_OFFSET(CLightManager, m_vUnk3c, 0x3c);
DOTD_ASSERT_OFFSET(CLightManager, m_pPreviousLightSet, 0x48);
DOTD_ASSERT_OFFSET(CLightManager, m_ui8PreviousFlat, 0x4c);
DOTD_ASSERT_OFFSET(CLightManager, m_pAmbientLight, 0x50);

// 0x00c5c8ec: the light manager (set by its constructor; the render queues read it). Name ours.
extern CLightManager* g_pLightManager;
