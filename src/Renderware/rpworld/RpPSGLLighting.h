// RpPSGLLighting.h - the RenderWare PSGL world driver's fixed-function lighting (library code 0x6b9730-0x6baec0): the
// lights of the current world and the material colours as glLight / glMaterial state for the driver's own immediate
// draws (the PTank quads, Renderware/rpptank/RpPTankRender.cpp). The GL state lands on platform/gfx/fixed_lighting.
//
//   [x] 0x006b9730  RwPSGL_AtomicLightingCallback_maybe
//   [x] 0x006ba440  RwPSGL_ApplyMaterialLighting_maybe
//   [x] 0x006ba6e8  RwPSGL_SetDirectionalLight_maybe
//   [x] 0x006ba7f0  RwPSGL_AddDirectionalLight_maybe (the next light index)
//   [x] 0x006ba830  RwPSGL_SetupGlobalLights_maybe
//   [x] 0x006bacc8  RwPSGL_ApplyLightState_maybe
//   [x] 0x006bae28  RwPSGL_QueryMaxLights_maybe (glGetIntegerv(GL_MAX_LIGHTS))
//   [x] 0x006ba9c0  RwPSGL_SetLocalLight_maybe: only for the lights of the world sectors an atomic is tied to (atomic
//                   +0x64); the game never adds an atomic to a world (CRenderer's world is empty: RpWorld.h), so the
//                   tie list is always empty and the call is never reached (ported for a world that holds atomics).
#pragma once
#include <cstdint>

struct RpAtomic;
struct RpMaterial;

// 0x006b9730 RwPSGL_AtomicLightingCallback_maybe: without the geometry's light flag (0x20) or a current world the
// lighting off; else the world's ambient and directional lights (mask 1, rpLIGHTLIGHTATOMICS), the engine's light frame
// counter advanced, the local lights of the atomic's sectors (none here, see above), then the light state applied.
void RwPSGL_AtomicLightingCallback(RpAtomic* atomic);
// 0x006ba440 RwPSGL_ApplyMaterialLighting_maybe: the material's GL diffuse and ambient colours (the world's summed
// ambient light times the material's ambient coefficient), then colour material on for prelit geometry (flag 8), else
// off with a black emission.
void RwPSGL_ApplyMaterialLighting(const RpMaterial* material, uint32_t geometryFlags);
// The driver's cached GL_LIGHTING state (0xcefd38 +0x7c): the draws test it after the lighting callback.
bool RwPSGL_LightingEnabled();
// The driver's cached GL_COLOR_MATERIAL state (0xcefd38 +0x18 / +0x1c): glDisable when it is on.
void RwPSGL_DisableColorMaterial();
