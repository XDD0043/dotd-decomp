// fixed_lighting.h - the fixed-function lighting of the PS3's PSGL (OpenGL ES 1.x with the SCE extensions) as the
// RenderWare PSGL driver drives it (new platform code, not a port).
//
// The driver's immediate draws with lighting on (the PTank quads with normals, RpPTankRender.cpp) call glEnable /
// glDisable(GL_LIGHTING), glLightModelfv(GL_LIGHT_MODEL_AMBIENT), glLightfv / glLightf(GL_LIGHTi, ...),
// glMaterialfv(GL_FRONT_AND_BACK, ...) and glEnable(GL_COLOR_MATERIAL), then draw vertices with normals. dotd's
// device has no fixed-function pipeline: this module keeps that GL state and evaluates the GL lighting equation
// (OpenGL 2.1 section 2.14.1, one-sided, no specular term: the driver never sets a material specular colour, whose
// default is black) per vertex on the CPU; the draw then sends the lit colours as vertex colours with lighting off.
//
// Space: GL transforms a light's position by the modelview matrix of its glLightfv call and a vertex and its normal
// by the modelview of the draw. The driver's PTank draw positions its vertices in world space under the camera's
// view matrix, the matrix under which it set the lights, so lights and vertices are given here in world space (the
// view matrix is rigid: the same dot products and distances).
#pragma once
#include <cstdint>

namespace dotd::gfx {

// GL enums the driver passes.
enum : uint32_t {
    kGlAmbient = 0x1200,
    kGlDiffuse = 0x1201,
    kGlSpecular = 0x1202,
    kGlPosition = 0x1203,
    kGlSpotDirection = 0x1204,
    kGlSpotExponent = 0x1205,
    kGlSpotCutoff = 0x1206,
    kGlConstantAttenuation = 0x1207,
    kGlLinearAttenuation = 0x1208,
    kGlQuadraticAttenuation = 0x1209,
    kGlEmission = 0x1600,
};

// glGetIntegerv(GL_MAX_LIGHTS): PSGL's 8 (the GL minimum).
int FixedMaxLights();

// glEnable / glDisable(GL_LIGHTING), glEnable / glDisable(GL_LIGHT0 + light), glEnable / glDisable(GL_COLOR_MATERIAL)
// (GL's default colour material mode: GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE).
void FixedSetLighting(bool on);
bool FixedLightingEnabled();
void FixedSetLightEnabled(int light, bool on);
void FixedSetColorMaterial(bool on);
// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, rgba)
void FixedLightModelAmbient(const float* rgba);
// glLightfv / glLightf(GL_LIGHT0 + light, pname, ...): ambient / diffuse / specular / position (4 floats), spot
// direction (3), spot exponent / cutoff and the three attenuations (1).
void FixedLightfv(int light, uint32_t pname, const float* values);
void FixedLightf(int light, uint32_t pname, float value);
// glMaterialfv(GL_FRONT_AND_BACK, pname, rgba): ambient, diffuse, emission.
void FixedMaterialfv(uint32_t pname, const float* rgba);

// The lit colour of one vertex (world-space position and normal; `color` the vertex colour bytes, or null without a
// colour array: with colour material on it gives the ambient and diffuse material colours), clamped to [0, 1] and
// stored as bytes (rounded to nearest).
void FixedLightVertex(const float* position, const float* normal, const uint8_t* color, uint8_t out[4]);

}  // namespace dotd::gfx
