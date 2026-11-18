// RpPSGLLighting.cpp - see RpPSGLLighting.h.
#include "Renderware/rpworld/RpPSGLLighting.h"

#include <cstddef>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rpworld/RpLight.h"
#include "Renderware/rpworld/RpWorld.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "platform/gfx/fixed_lighting.h"

namespace {

// The driver's lighting globals (0xcec614): the summed colour of the world's ambient lights (+0x00..+0x08, alpha
// +0x0c 1.0f), whether one was found (+0x10), the GL lights used now (+0x18), GL_MAX_LIGHTS (+0x1c) and the lights
// used by the previous draw (+0x20).
struct LightGlobals {
    float ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    uint32_t ambientFound = 0;
    uint32_t numLights = 0;
    uint32_t maxLights = 0;
    uint32_t prevLights = 0;
    bool initialised = false;
};
// The driver's GL enable cache (0xcefd38): GL_COLOR_MATERIAL (+0x1c), GL_LIGHTi (+0x3c + 8 i), GL_LIGHTING (+0x7c).
struct EnableCache {
    uint32_t colorMaterial = 0;
    uint32_t light[8] = {};
    uint32_t lighting = 0;
};

LightGlobals g_lights;
EnableCache g_enabled;

const float kBlack[4] = {0.0f, 0.0f, 0.0f, 1.0f};  // 0xa7180c (TOC -0x43b4)
const float kWhite[4] = {1.0f, 1.0f, 1.0f, 1.0f};  // 0xa7181c

// 0x006bae28 RwPSGL_QueryMaxLights_maybe (run by the driver's open; here on first use): glGetIntegerv(GL_MAX_LIGHTS,
// +0x1c), no light used yet (+0x20).
void InitLightCount() {
    if (g_lights.initialised) return;
    g_lights.initialised = true;
    g_lights.maxLights = static_cast<uint32_t>(dotd::gfx::FixedMaxLights());
    g_lights.prevLights = 0;
}

// 0x006ba6e8 RwPSGL_SetDirectionalLight_maybe: GL_LIGHT0 + index at the light frame's -at direction (w 0), black
// ambient, the light's colour as diffuse, cutoff 180 (TOC -0x43b0); enabled through the cache.
void SetDirectionalLight(const RpLight* light, uint32_t index) {
    const RwMatrix* ltm = RwFrameGetLTM(RpLightGetFrame(light));
    const float position[4] = {-ltm->at.x, -ltm->at.y, -ltm->at.z, 0.0f};
    const int gl = static_cast<int>(index);
    dotd::gfx::FixedLightfv(gl, dotd::gfx::kGlPosition, position);
    dotd::gfx::FixedLightfv(gl, dotd::gfx::kGlAmbient, kBlack);
    dotd::gfx::FixedLightfv(gl, dotd::gfx::kGlDiffuse, light->color);
    dotd::gfx::FixedLightf(gl, dotd::gfx::kGlSpotCutoff, 180.0f);
    if (index < 8 && g_enabled.light[index] == 0) {
        dotd::gfx::FixedSetLightEnabled(gl, true);
        g_enabled.light[index] = 1;
    }
}

// 0x006ba830 RwPSGL_SetupGlobalLights_maybe(mask, useWorld): the ambient sum and the light count reset; with the
// world, every light of its directional list whose flags share a bit with the mask: an ambient one (sub type != 1)
// adds its colour (fadds), a directional one takes the next GL light while there is one (0x6ba7f0). 1 when a light
// matched the mask.
uint32_t SetupGlobalLights(uint8_t mask, bool useWorld) {
    g_lights.ambient[3] = 1.0f;
    g_lights.ambient[2] = 0.0f;
    g_lights.numLights = 0;
    g_lights.ambientFound = 0;
    g_lights.ambient[0] = 0.0f;
    g_lights.ambient[1] = 0.0f;
    if (!useWorld) return 0;
    RwCamera* camera = RwDevice_GetCamera();
    RpWorld* world = camera != nullptr ? RwCameraGetWorld(camera) : nullptr;  // RWSRCGLOBAL(curWorld)
    if (world == nullptr) return 0;
    RwLLLink* head = &world->directionalLightList.link;
    uint32_t result = 0;
    for (RwLLLink* link = head->next; link != head; link = link->next) {
        const RpLight* light = reinterpret_cast<const RpLight*>(reinterpret_cast<const uint8_t*>(link) -
                                                                offsetof(RpLight, inWorld));
        if ((mask & light->object.flags) == 0) continue;
        result = 1;
        if (light->object.subType != rpLIGHTDIRECTIONAL) {
            g_lights.ambient[0] = g_lights.ambient[0] + light->color[0];
            g_lights.ambient[1] = g_lights.ambient[1] + light->color[1];
            g_lights.ambient[2] = g_lights.ambient[2] + light->color[2];
            g_lights.ambientFound = 1;
            continue;
        }
        if (g_lights.numLights >= g_lights.maxLights) continue;
        SetDirectionalLight(light, g_lights.numLights);  // 0x006ba7f0
        ++g_lights.numLights;
    }
    return result;
}

// 0x006ba9c0 RwPSGL_SetLocalLight_maybe: a positional light while a GL light is free and its radius is not 0 (else 1):
// GL_LIGHT0 + the count with the light's colour as diffuse, its frame's LTM position (w 1), the attenuation of its PSGL
// extension (constant; linear / radius; quadratic / radius^2: inverse x (inverse x q)); a spot (0x81) or soft spot
// (0x82): the LTM's at as direction, the cone angle (RpLightGetConeAngle 0x6a2be8) x 57.29578 (TOC -0x43a8 0x42652ee1)
// as cutoff, the exponent 0 (TOC -0x43c8) or the extension's soft exponent; a point light (0x80) cutoff 180 (TOC
// -0x43b0); any other type returns 0 with nothing enabled or counted. The light enabled through the cache, the count
// advanced, 1.
uint32_t SetLocalLight(const RpLight* light) {
    if (g_lights.numLights >= g_lights.maxLights) return 1;
    if (light->radius == 0.0f) return 1;  // fcmpu with TOC -0x43c8 (NaN goes on)
    const float inverse = 1.0f / light->radius;
    const uint32_t index = g_lights.numLights;
    const int gl = static_cast<int>(index);  // GL_LIGHT0 (0x4000) + index
    dotd::gfx::FixedLightfv(gl, dotd::gfx::kGlDiffuse, light->color);
    const RwMatrix* ltm = RwFrameGetLTM(RpLightGetFrame(light));  // 0x0074a6f0
    const float position[4] = {ltm->pos.x, ltm->pos.y, ltm->pos.z, 1.0f};  // w: TOC -0x43c4
    dotd::gfx::FixedLightfv(gl, dotd::gfx::kGlPosition, position);
    const float quadraticOverRadius = inverse * light->psglAttenuation[2];
    const float linear = inverse * light->psglAttenuation[1];
    const float quadratic = inverse * quadraticOverRadius;
    dotd::gfx::FixedLightf(gl, dotd::gfx::kGlConstantAttenuation, light->psglAttenuation[0]);
    dotd::gfx::FixedLightf(gl, dotd::gfx::kGlLinearAttenuation, linear);
    dotd::gfx::FixedLightf(gl, dotd::gfx::kGlQuadraticAttenuation, quadratic);
    const float kRadToDeg = 57.2957802f;  // 0x42652ee1
    const uint8_t type = light->object.subType;
    if (type == rpLIGHTSPOT || type == rpLIGHTSPOTSOFT) {
        // The original leaves the fourth word unset (the stack): glLightfv(GL_SPOT_DIRECTION) reads three.
        const float direction[4] = {ltm->at.x, ltm->at.y, ltm->at.z, 0.0f};
        dotd::gfx::FixedLightfv(gl, dotd::gfx::kGlSpotDirection, direction);
        dotd::gfx::FixedLightf(gl, dotd::gfx::kGlSpotCutoff, RpLightGetConeAngle(light) * kRadToDeg);
        dotd::gfx::FixedLightf(gl, dotd::gfx::kGlSpotExponent, type == rpLIGHTSPOT ? 0.0f : light->psglSoftSpotExponent);
    } else if (type == rpLIGHTPOINT) {
        dotd::gfx::FixedLightf(gl, dotd::gfx::kGlSpotCutoff, 180.0f);
    } else {
        return 0;
    }
    if (index < 8 && g_enabled.light[index] == 0) {
        dotd::gfx::FixedSetLightEnabled(gl, true);
        g_enabled.light[index] = 1;
    }
    ++g_lights.numLights;
    return 1;
}

// 0x006bacc8 RwPSGL_ApplyLightState_maybe: lighting off (through the cache), or the light model's ambient (white when
// an ambient light was found: the ambient colour is then in the material's, see ApplyMaterialLighting; black
// otherwise) and lighting on; either way the GL lights the previous draw used beyond this one's are disabled.
void ApplyLightState(uint32_t enable) {
    if (enable == 0) {
        if (g_enabled.lighting != 0) {
            dotd::gfx::FixedSetLighting(false);
            g_enabled.lighting = 0;
        }
    } else {
        dotd::gfx::FixedLightModelAmbient(g_lights.ambientFound == 0 ? kBlack : kWhite);
        if (g_enabled.lighting == 0) {
            dotd::gfx::FixedSetLighting(true);
            g_enabled.lighting = 1;
        }
    }
    for (uint32_t i = g_lights.numLights; i < g_lights.prevLights; ++i) {
        if (i < 8 && g_enabled.light[i] != 0) {
            dotd::gfx::FixedSetLightEnabled(static_cast<int>(i), false);
            g_enabled.light[i] = 0;
        }
    }
    g_lights.prevLights = g_lights.numLights;
}

}  // namespace

// 0x006b9730 RwPSGL_AtomicLightingCallback_maybe
void RwPSGL_AtomicLightingCallback(RpAtomic* atomic) {
    InitLightCount();
    RwCamera* camera = RwDevice_GetCamera();
    const RpWorld* world = camera != nullptr ? RwCameraGetWorld(camera) : nullptr;
    if ((atomic->geometry->flags & rpGEOMETRYLIGHT) == 0 || world == nullptr) {
        ApplyLightState(0);
        return;
    }
    uint32_t lit = SetupGlobalLights(1, true);
    ++g_rwLightFrame;
    // The sectors the atomic is tied to (+0x64) and their local lights: a light not yet used this pass (+0x3c) that lights
    // atomics (flags & 1) is marked used; when the atomic's world sphere reaches its radius (the squared distance not
    // below (sphere radius + light radius)^2: bge skips) it is set (RwPSGL_SetLocalLight_maybe 0x6ba9c0) and its result
    // or'ed in. None here: the atomic is in no world (RpPSGLLighting.h), its tie list is empty.
    RwLLLink* tieHead = &atomic->llWorldSectorsInAtomic;
    for (RwLLLink* tieLink = tieHead->next; tieLink != tieHead; tieLink = tieLink->next) {
        const RpTie* tie = reinterpret_cast<const RpTie*>(reinterpret_cast<const uint8_t*>(tieLink) -
                                                          offsetof(RpTie, lWorldSectorInAtomic));
        RwLLLink* lightHead = &tie->worldSector->lightsInWorldSector.link;
        for (RwLLLink* link = lightHead->next; link != lightHead; link = link->next) {
            RpLight* light = reinterpret_cast<const RpLightTie*>(link)->light;  // lightInWorldSector at +0
            if (light == nullptr) continue;
            if (light->lightFrame == g_rwLightFrame) continue;
            if ((light->object.flags & 1) == 0) continue;  // rpLIGHTLIGHTATOMICS
            light->lightFrame = g_rwLightFrame;
            const RwV3d& position = RwFrameGetLTM(RpLightGetFrame(light))->pos;  // 0x0074a6f0
            const float* sphere = RpAtomicGetWorldBoundingSphere(atomic);  // 0x0069dd20
            const float dy = sphere[1] - position.y;
            const float dx = sphere[0] - position.x;
            const float dz = sphere[2] - position.z;
            const float reach = sphere[3] + light->radius;
            const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (!(distance2 < reach * reach)) continue;  // bge
            lit |= SetLocalLight(light);
        }
    }
    ApplyLightState(lit);
}

// 0x006ba440 RwPSGL_ApplyMaterialLighting_maybe. Modulated by a material colour other than opaque white (the colour
// word != -1): ambient = ambient coefficient / 255 x colour x the summed ambient light, diffuse = diffuse coefficient /
// 255 x colour, alpha = alpha / 255 (fcfid of each byte, frsp, fmuls); else diffuse = (d, d, d, 1), ambient = the
// summed ambient light (coefficient 1.0) or coefficient x it, alpha 1.
void RwPSGL_ApplyMaterialLighting(const RpMaterial* material, uint32_t geometryFlags) {
    const float kInv255 = 0.00392156886f;  // 0x3b808081 (TOC -0x43bc)
    float diffuse[4];
    float ambient[4];
    const RwRGBA& c = material->color;
    const bool white = c.red == 0xff && c.green == 0xff && c.blue == 0xff && c.alpha == 0xff;
    if ((geometryFlags & rpGEOMETRYMODULATEMATERIALCOLOR) != 0 && !white) {
        const float a = material->surfaceProps.ambient * kInv255;
        const float d = material->surfaceProps.diffuse * kInv255;
        const float alpha = static_cast<float>(c.alpha) * kInv255;
        ambient[0] = (a * static_cast<float>(c.red)) * g_lights.ambient[0];
        ambient[1] = (a * static_cast<float>(c.green)) * g_lights.ambient[1];
        ambient[2] = (a * static_cast<float>(c.blue)) * g_lights.ambient[2];
        ambient[3] = alpha;
        diffuse[0] = d * static_cast<float>(c.red);
        diffuse[1] = d * static_cast<float>(c.green);
        diffuse[2] = d * static_cast<float>(c.blue);
        diffuse[3] = alpha;
    } else {
        const float a = material->surfaceProps.ambient;
        const float d = material->surfaceProps.diffuse;
        diffuse[0] = d;
        diffuse[1] = d;
        diffuse[2] = d;
        diffuse[3] = 1.0f;
        ambient[3] = 1.0f;
        if (a == 1.0f) {  // fcmpu with TOC -0x43c4
            ambient[0] = g_lights.ambient[0];
            ambient[1] = g_lights.ambient[1];
            ambient[2] = g_lights.ambient[2];
        } else {
            ambient[0] = a * g_lights.ambient[0];
            ambient[1] = a * g_lights.ambient[1];
            ambient[2] = a * g_lights.ambient[2];
        }
    }
    dotd::gfx::FixedMaterialfv(dotd::gfx::kGlDiffuse, diffuse);
    dotd::gfx::FixedMaterialfv(dotd::gfx::kGlAmbient, ambient);
    if ((geometryFlags & rpGEOMETRYPRELIT) != 0) {
        if (g_enabled.colorMaterial == 0) {
            dotd::gfx::FixedSetColorMaterial(true);
            g_enabled.colorMaterial = 1;
        }
        return;
    }
    if (g_enabled.colorMaterial != 0) {
        dotd::gfx::FixedSetColorMaterial(false);
        g_enabled.colorMaterial = 0;
    }
    dotd::gfx::FixedMaterialfv(dotd::gfx::kGlEmission, kBlack);
}

bool RwPSGL_LightingEnabled() { return g_enabled.lighting != 0; }

void RwPSGL_DisableColorMaterial() {
    if (g_enabled.colorMaterial != 0) {
        dotd::gfx::FixedSetColorMaterial(false);
        g_enabled.colorMaterial = 0;
    }
}
