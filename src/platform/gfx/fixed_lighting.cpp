// fixed_lighting.cpp - see fixed_lighting.h.
#include "platform/gfx/fixed_lighting.h"

#include <cmath>

namespace dotd::gfx {
namespace {

constexpr int kMaxLights = 8;

struct Light {
    bool enabled = false;
    float ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float diffuse[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float specular[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float position[4] = {0.0f, 0.0f, 1.0f, 0.0f};
    float spotDirection[3] = {0.0f, 0.0f, -1.0f};
    float spotExponent = 0.0f;
    float spotCutoff = 180.0f;
    float attenuation[3] = {1.0f, 0.0f, 0.0f};
};

struct State {
    bool lighting = false;
    bool colorMaterial = false;
    float modelAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float matAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float matDiffuse[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    float matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    Light lights[kMaxLights];
};

State& S() {
    static State state = [] {
        State s;
        // GL_LIGHT0's diffuse and specular default to white, the others' to black.
        for (int k = 0; k < 4; ++k) {
            s.lights[0].diffuse[k] = 1.0f;
            s.lights[0].specular[k] = 1.0f;
        }
        return s;
    }();
    return state;
}

void Copy4(float* dst, const float* src) {
    for (int k = 0; k < 4; ++k) dst[k] = src[k];
}

float Clamp01(float v) { return v < 0.0f ? 0.0f : (v > 1.0f ? 1.0f : v); }

}  // namespace

int FixedMaxLights() { return kMaxLights; }

void FixedSetLighting(bool on) { S().lighting = on; }
bool FixedLightingEnabled() { return S().lighting; }
void FixedSetLightEnabled(int light, bool on) {
    if (light >= 0 && light < kMaxLights) S().lights[light].enabled = on;
}
void FixedSetColorMaterial(bool on) { S().colorMaterial = on; }
void FixedLightModelAmbient(const float* rgba) { Copy4(S().modelAmbient, rgba); }

void FixedLightfv(int light, uint32_t pname, const float* v) {
    if (light < 0 || light >= kMaxLights) return;
    Light& l = S().lights[light];
    switch (pname) {
        case kGlAmbient: Copy4(l.ambient, v); break;
        case kGlDiffuse: Copy4(l.diffuse, v); break;
        case kGlSpecular: Copy4(l.specular, v); break;
        case kGlPosition: Copy4(l.position, v); break;
        case kGlSpotDirection:
            for (int k = 0; k < 3; ++k) l.spotDirection[k] = v[k];
            break;
        default: FixedLightf(light, pname, v[0]); break;
    }
}

void FixedLightf(int light, uint32_t pname, float v) {
    if (light < 0 || light >= kMaxLights) return;
    Light& l = S().lights[light];
    switch (pname) {
        case kGlSpotExponent: l.spotExponent = v; break;
        case kGlSpotCutoff: l.spotCutoff = v; break;
        case kGlConstantAttenuation: l.attenuation[0] = v; break;
        case kGlLinearAttenuation: l.attenuation[1] = v; break;
        case kGlQuadraticAttenuation: l.attenuation[2] = v; break;
        default: break;
    }
}

void FixedMaterialfv(uint32_t pname, const float* rgba) {
    State& s = S();
    switch (pname) {
        case kGlAmbient: Copy4(s.matAmbient, rgba); break;
        case kGlDiffuse: Copy4(s.matDiffuse, rgba); break;
        case kGlEmission: Copy4(s.matEmission, rgba); break;
        default: break;
    }
}

void FixedLightVertex(const float* position, const float* normal, const uint8_t* color, uint8_t out[4]) {
    const State& s = S();
    float ambient[4], diffuse[4];
    Copy4(ambient, s.matAmbient);
    Copy4(diffuse, s.matDiffuse);
    if (s.colorMaterial && color != nullptr) {
        for (int k = 0; k < 4; ++k) {
            ambient[k] = static_cast<float>(color[k]) / 255.0f;
            diffuse[k] = ambient[k];
        }
    }
    float c[3];
    for (int k = 0; k < 3; ++k) c[k] = s.matEmission[k] + ambient[k] * s.modelAmbient[k];
    for (const Light& l : s.lights) {
        if (!l.enabled) continue;
        float vp[3];
        float attenuation = 1.0f;
        if (l.position[3] == 0.0f) {
            for (int k = 0; k < 3; ++k) vp[k] = l.position[k];
        } else {
            for (int k = 0; k < 3; ++k) vp[k] = l.position[k] / l.position[3] - position[k];
            const float d = std::sqrt(vp[0] * vp[0] + vp[1] * vp[1] + vp[2] * vp[2]);
            const float denom = l.attenuation[0] + l.attenuation[1] * d + l.attenuation[2] * d * d;
            attenuation = denom != 0.0f ? 1.0f / denom : 0.0f;
        }
        const float len = std::sqrt(vp[0] * vp[0] + vp[1] * vp[1] + vp[2] * vp[2]);
        if (len != 0.0f) {
            for (float& x : vp) x /= len;
        }
        float spot = 1.0f;
        if (l.spotCutoff != 180.0f) {
            const float* sd = l.spotDirection;
            const float sl = std::sqrt(sd[0] * sd[0] + sd[1] * sd[1] + sd[2] * sd[2]);
            const float cosAngle = sl != 0.0f ? -(vp[0] * sd[0] + vp[1] * sd[1] + vp[2] * sd[2]) / sl : 0.0f;
            const float cosCutoff = std::cos(l.spotCutoff * 3.14159265f / 180.0f);
            spot = cosAngle < cosCutoff ? 0.0f : std::pow(cosAngle < 0.0f ? 0.0f : cosAngle, l.spotExponent);
        }
        float ndotl = normal[0] * vp[0] + normal[1] * vp[1] + normal[2] * vp[2];
        if (ndotl < 0.0f) ndotl = 0.0f;
        for (int k = 0; k < 3; ++k)
            c[k] += attenuation * spot * (ambient[k] * l.ambient[k] + ndotl * diffuse[k] * l.diffuse[k]);
    }
    for (int k = 0; k < 3; ++k) out[k] = static_cast<uint8_t>(Clamp01(c[k]) * 255.0f + 0.5f);
    out[3] = static_cast<uint8_t>(Clamp01(diffuse[3]) * 255.0f + 0.5f);
}

}  // namespace dotd::gfx
