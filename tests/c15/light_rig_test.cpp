// light_rig_test - C2.4 step 6: the light rig and the zones' light accumulation on synthetic lights (no game data).
// Two scene-graph lights (CSGLight) each lend components to a zone of kind 0 (whole level); the zone's components are made by
// LightZone_AccumulateLights (0x981c8), the rig takes them in ApplyLightingZone (0x994e8) and the shaders' view of it is
// checked: the ambient colour, the directions, ComputeLightCount (0x9b208: the odd-lane quirk), GetNextDistinctLight (0x9ae28).
#include <cstdio>
#include <initializer_list>
#include <cstring>

#include "Renderware/rpworld/RpLight.h"
#include "k2000/graphical/render/CLightManager.h"
#include "k2000/graphical/render/CLightSet.h"
#include "k2000/logic/render/CLightComponent.h"
#include "k2000/math/CurveKeys.h"
#include "k2000/scenegraph/CSGLight.h"

namespace {
int g_failures = 0;
void Expect(bool ok, const char* what) {
    if (!ok) {
        std::printf("light_rig: FAIL %s\n", what);
        ++g_failures;
    }
}

CLightComponent* Component(uint8_t r, uint8_t g, uint8_t b, uint8_t a, float dx, float dy, float dz) {
    CLightComponent* component = new CLightComponent();
    component->m_baProperties = 0x10;  // weighted by its alpha
    component->m_cLightColor[0] = r;
    component->m_cLightColor[1] = g;
    component->m_cLightColor[2] = b;
    component->m_cLightColor[3] = a;
    component->m_v3Dir = {dx, dy, dz};
    return component;
}
}  // namespace

int main() {
    CLightManager manager;
    manager.CreateWorldLights();
    Expect(manager.ComputeLightCount() == 0, "a fresh rig has no light");
    uint32_t color = 0;
    CVector3 direction;
    Expect(manager.GetNextDistinctLight(0, &direction, &color) == 4, "a fresh rig has no distinct light");

    CLightSet zone;
    zone.InitializeData();
    zone.m_baProperties = 0;  // kind 0: the whole level, every light covers it entirely
    zone.m_unk78 = 0;
    const uint8_t black[4] = {0, 0, 0, 0xff};
    for (CLightComponent*& component : zone.m_apLightComponent) {
        component = new CLightComponent();
        std::memcpy(component->m_cLightColor, black, 4);
        component->m_v3Dir = {0.0f, 0.0f, 0.0f};
    }

    // Light A (box type 0): ambient (200, 100, 50) and a directional component (0, 255, 0) pointing along +Y.
    CLightComponent* a0 = Component(200, 100, 50, 255, 0, 0, 0);
    CLightComponent* a1 = Component(0, 255, 0, 255, 0, 2, 0);
    IKSerializable* aParams[2] = {a0, a1};
    // Light B (box type 0): a third component (255, 255, 0): two lanes reach 1/255 (an even number).
    CLightComponent* b0 = Component(0, 0, 0, 255, 0, 0, 0);
    CLightComponent* b1 = Component(0, 0, 0, 255, 0, 0, 0);
    CLightComponent* b2 = Component(255, 255, 0, 255, 1, 0, 0);
    IKSerializable* bParams[3] = {b0, b1, b2};

    IKSerializable* sets[1] = {&zone};
    CSGLight lightA, lightB;
    for (CSGLight* light : {&lightA, &lightB}) {
        light->m_eLightBoxType = 0;
        light->m_ui32OcclusionLevel = 0;
        light->m_apLightSets = sets;
        light->m_ui32LightSetCapacity = 1;
        light->m_ui32NbLightSets = 1;
    }
    lightA.m_aplightParameters = aParams;
    lightA.m_ui32NbActiveLights = 2;
    lightB.m_aplightParameters = bParams;
    lightB.m_ui32NbActiveLights = 3;
    lightA.ComputeZoneOverlapWeights();
    Expect(zone.m_i32MaxOcclusionLevel[0] == 0 && zone.m_i32MaxOcclusionLevel[1] == -1, "the zone remembers the light's occlusion level");
    Expect(zone.m_avpAccumulatedLight.m_pBlock[0].m_ui32NbUsedElt == 1 && zone.m_afAccumulatedLightRatio.m_pBlock[0].m_pBlock[0] == 1.0f, "kind 0 zone: ratio 1");

    // Only light A: weight 1, so the zone's components are A's.
    zone.AccumulateLights(0, 0);
    Expect(zone.m_apLightComponent[0]->m_cLightColor[0] == 200 && zone.m_apLightComponent[0]->m_cLightColor[1] == 100 &&
               zone.m_apLightComponent[0]->m_cLightColor[2] == 50 && zone.m_apLightComponent[0]->m_cLightColor[3] == 255,
           "component 0 is light A's first component");
    Expect(zone.m_apLightComponent[1]->m_cLightColor[1] == 255 && zone.m_apLightComponent[1]->m_v3Dir.y == 2.0f, "component 1 is light A's second");

    manager.ApplyLightingZone(&zone, 0);
    Expect(manager.m_pPreviousLightSet == &zone && manager.m_ui8PreviousFlat == 0, "the zone is remembered");
    const float* ambient = manager.GetAmbientColor();
    Expect(ambient[0] > 0.78f && ambient[0] < 0.79f && ambient[1] > 0.39f && ambient[1] < 0.40f && ambient[3] == 1.0f, "ambient colour = component 0");
    Expect(manager.ComputeLightCount() == 1, "one light with one reaching lane counts");
    uint32_t index = manager.GetNextDistinctLight(0, &direction, &color);
    Expect(index == 1 && color == 0x00ff00ffu && direction.y == 2.0f, "the first distinct light is directional light 0 (green)");
    Expect(manager.GetNextDistinctLight(index, &direction, &color) == 4, "and there is no other");

    // A third light component whose colour has two reaching lanes: it is in the rig but is not counted.
    zone.m_apLightComponent[2]->m_baProperties = 0;
    std::memcpy(zone.m_apLightComponent[2]->m_cLightColor, b2->m_cLightColor, 4);
    zone.m_apLightComponent[2]->m_v3Dir = b2->m_v3Dir;
    manager.ApplyLightingZone(&zone, 0);
    Expect(manager.ComputeLightCount() == 1, "an even number of reaching lanes does not count (the odd-lane quirk)");
    index = manager.GetNextDistinctLight(0, &direction, &color);
    index = manager.GetNextDistinctLight(index, &direction, &color);
    Expect(index == 2 && color == 0xffff00ffu, "the two-lane light is still a distinct light");

    // The flat form: one ambient colour (the mean of the non-black components), no directional lights in the world.
    manager.ApplyLightingZone(&zone, 1);
    Expect(manager.m_ui8PreviousFlat == 1, "the flat flag is remembered");
    Expect(manager.GetAmbientColor()[0] > 0.0f, "flat: the ambient colour is the mean");
    // No zone: all black again.
    manager.ApplyLightingZone(nullptr, 0);
    Expect(manager.ComputeLightCount() == 0 && manager.GetAmbientColor()[0] == 0.0f, "no zone: black");

    // ColorCurve_Evaluate: two keys, the middle is the mean; outside the keys the end colours.
    TVector<CurveKey, 20> keys;
    CurveKey storage[2];
    const float times[2] = {0.0f, 2.0f};
    for (int i = 0; i < 2; ++i) std::memcpy(&storage[i].m_key, &times[i], 4);
    const uint8_t first[4] = {0, 0, 0, 0xff}, second[4] = {200, 100, 50, 0xff};
    std::memcpy(storage[0].m_valueRaw, first, 4);
    std::memcpy(storage[1].m_valueRaw, second, 4);
    keys.m_pBlock = storage;
    keys.m_ui32NbElt = 2;
    keys.m_ui32NbUsedElt = 2;
    uint8_t out[4];
    ColorCurve_Evaluate(1.0f, out, &keys);
    Expect(out[0] == 100 && out[1] == 50 && out[2] == 25 && out[3] == 0xff, "the colour curve's middle");
    ColorCurve_Evaluate(-1.0f, out, &keys);
    Expect(out[0] == 0 && out[3] == 0xff, "before the first key");
    ColorCurve_Evaluate(5.0f, out, &keys);
    Expect(out[0] == 200, "after the last key");

    std::printf("light_rig: %d failure(s)\n", g_failures);
    return g_failures == 0 ? 0 : 1;
}
