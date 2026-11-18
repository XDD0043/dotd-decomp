// ShaderVariantKey.h - which shader program a mesh needs (C2.4 step 2). Original unit: ShaderVariantKey.cpp
// (0xf1508-0xf26a0) with the key builders of MeshShaderPassState.cpp (0xf00d8-0xf0f00) and the define / uniform
// collection of ShaderProgramBase.cpp (0xf41b0-0xf4fb8).
//
// The original turns a key into the `-Dextern...=value` arguments of its embedded Cg compiler
// (ShaderGen_CollectExternFragments_maybe 0xf48c0) and into the list of uniforms the draw must fill
// (ShaderGen_CollectVertexUniforms_maybe 0xf44c0 / ShaderGen_CollectPixelUniforms_maybe 0xf41b0); the compiled
// NV40 programs are cached in shfct.bin. Here the same define list goes through the Cg preprocessor and the Cg ->
// GLSL translator (platform/gfx/cg_program.h) and ShaderVariant_GetProgram returns the linked GL program.
#pragma once
#include <cstdint>
#include <vector>

#include "k2000/core/Layout.h"
#include "platform/gfx/cg_program.h"

class ShaderPassState;

// The key (0x14 bytes). The mode is the material shader mode (CMaterial properties bits 3-6, 0..14) after
// BuildForMesh's fallbacks (an aux layer mode without its texture becomes 0, 2 or 5).
struct ShaderVariantKey {
    uint32_t mode;           // +0x00
    uint8_t specialLights;   // +0x04 externSpecialLight
    uint8_t dirLights;       // +0x05 externDirLight
    uint8_t pointLights;     // +0x06 externPointLight
    uint8_t spotLights;      // +0x07 externSpotLight (always 0 for meshes)
    uint8_t weights;         // +0x08 externWeightNb (skin weights per vertex, at most 2)
    uint8_t texCoords;       // +0x09 externTexCoordNb
    uint8_t fogType;         // +0x0a externFogType (0 / 1)
    uint8_t pad0b;           // +0x0b
    uint32_t dualBlend;      // +0x0c 0, 1, or 2 (mode 6: externDualAlphaBlend)
    uint32_t flags;          // +0x10 kShaderKey* bits
};
DOTD_ASSERT_SIZE(ShaderVariantKey, 0x14);
DOTD_ASSERT_OFFSET(ShaderVariantKey, specialLights, 0x04);
DOTD_ASSERT_OFFSET(ShaderVariantKey, dualBlend, 0x0c);
DOTD_ASSERT_OFFSET(ShaderVariantKey, flags, 0x10);

// ShaderVariantKey::flags (named after the extern define each one turns on).
enum : uint32_t {
    kShaderKeyUvTransform = 0x1,         // modes 11..14: externMATERIALFX_UVTRANSFORM, uniform VSC_UVTRANSF
    kShaderKeyVertexColor = 0x2,         // externVertexColor
    kShaderKeyModulateMaterial = 0x4,    // (always set by meshes; no define)
    kShaderKeySpecular = 0x8,            // externSpecular
    kShaderKeyFirstPass = 0x10,          // externFirstPass
    kShaderKeyRenderFarTex = 0x20,       // externRenderFarTex
    kShaderKeyEnvSubtractAlpha = 0x40,   // externEnvSubstractAlpha (CMaterial property bit 14)
    kShaderKeyShadow = 0x80,             // externShadowEnable
    kShaderKeyModulateVertexColorFirst = 0x100,
    kShaderKeyUseNormalInfluence = 0x200,
    kShaderKeyAuxLayerTexture = 0x400,   // aux layer texture present (mode 12: externMATERIALFX_NORMAL)
    kShaderKeySecondaryTexture = 0x800,
    kShaderKeyAuxTexture8C = 0x1000,
    kShaderKeyAuxLayerTextureB = 0x2000,
    kShaderKeyRenderDof = 0x4000,        // externRenderDepthOfField
    kShaderKeyPostDof = 0x8000,          // externPostRenderDepthOfField
    kShaderKeyCopyAlpha = 0x10000,       // externDOFCopyAlpha
    kShaderKeyGaussianBlur = 0x20000,    // externGaussianBlur5x5
    kShaderKeyDownSample4x4 = 0x40000,
    kShaderKeyDontModulateAlpha = 0x80000,
    kShaderKeyDownSample16x16 = 0x100000,
    kShaderKeyBloom = 0x200000,
};

// The uniform ids the collection returns (the order of the Cg DeclareUniform lines: the vertex program's float
// uniforms 0..0x11, then the pixel program's 0x12..0x27; the original's table is at 0x00c1d36c).
enum ShaderUniformId : int32_t {
    kVscFog = 0, kVscWorldViewProj, kVscAmbientColor, kVscMaterialColor, kVscDirLightDir, kVscDirLightColor,
    kVscPointLightPos, kVscPointLightColor, kVscUvTransform, kVscViewPomHeight, kVscSpecular, kVscDualUvTransform,
    kVscSpecialLight, kVscWorldView, kVscWorld, kVscInfoQuadShadow, kVscBoneWeight, kVscBoneMatrices,
    kPscDirLightDir = 0x12, kPscDirLightColor, kPscAmbientColor, kPscPointLightPos, kPscPointLightColor,
    kPscNormalParam, kPscPomTextureShadow, kPscSpecular, kPscSpecularColor, kPscMaterialColor, kPscMaterialFx,
    kPscSpecialLight, kPscDofParam, kPscDofAdjustTex, kPscDofPixelSize, kPscDofRadius, kPscFarCamera, kPscAnim,
    kPscMinMaxShadow, kPscWorldViewProj, kPscDownSample, kPscGauss5x5,
};

// The Cg name of a ShaderUniformId (the uniform of the vertex program for ids below 0x12, of the pixel program above),
// e.g. kVscWorldViewProj -> "u_f44WorldViewProj"; null for an unknown id. The GL location is
// glGetUniformLocation(program->glProgram, name); cg::Program::vertex/pixel.uniforms give the type and register.
const char* ShaderUniformCgName(int32_t id);

// 0x000f00d8 ShaderVariantKey_Init_maybe
void ShaderVariantKey_Init(ShaderVariantKey* key);
// 0x000f1508 ShaderVariantKey_BuildForMesh_maybe (also reached through the thunks 0xf1c90 / 0xf1c98): the key of the
// mesh a pass state describes (the atomics' meshes and, through the PTank's shader hook, the PTank particles).
void ShaderVariantKey_BuildForMesh(ShaderVariantKey* key, ShaderPassState* pass);
// 0x000f0108 ShaderVariantKey_BuildFromPassState_maybe: the key of an Im2D pass state (the post-effect passes).
void ShaderVariantKey_BuildFromPassState(ShaderVariantKey* key, ShaderPassState* pass);
// 0x000f07a8 ShaderVariantKey_BuildForImmediate3D_maybe (also its thunks 0xf1ca0 / 0xf1ca8, the OPD table 0xb53a98): the
// key of an Im3D pass state (ShaderManagerPSGL_BindImmediate3DShaders_maybe 0xffde8: the Rt2d shapes, brushes and fonts
// and the other RwIm3D draws): BuildFromPassState's slots in the same order, with key bit 5 from vt+0xdc instead of vt+0xd8.
void ShaderVariantKey_BuildForImmediate3D(ShaderVariantKey* key, ShaderPassState* pass);
// 0x000f0e48 ShaderVariantKey_Equals
bool ShaderVariantKey_Equals(const ShaderVariantKey& a, const ShaderVariantKey& b);
// 0x000f1e38 / 0x000f2000: do the two keys need the same vertex / pixel program?
bool ShaderVariantKey_MatchesVertexShader(const ShaderVariantKey& a, const ShaderVariantKey& b);
bool ShaderVariantKey_MatchesPixelShader(const ShaderVariantKey& a, const ShaderVariantKey& b);

// 0x000f48c0 ShaderGen_CollectExternFragments_maybe: the define list of a key, in the original's order. Reads
// ShaderSceneInputs::pixelLightning (g_ShaderManagerPSGL +0x38) for externPixelLightning.
std::vector<dotd::gfx::cg::Define> ShaderGen_CollectExternFragments(const ShaderVariantKey& key);
// 0x000f44c0 / 0x000f41b0: the uniforms the vertex / pixel program of the key reads (ShaderUniformId, with the
// original's repeats).
std::vector<int32_t> ShaderGen_CollectVertexUniforms(const ShaderVariantKey& key);
std::vector<int32_t> ShaderGen_CollectPixelUniforms(const ShaderVariantKey& key);

// 0x000f8840 CShaderManagerPSGL_GetShaderModeForKey_maybe: the Cg profile table index of a key: 6 for the post-DoF and
// Gaussian blur passes and the aux layer modes 11 / 13, else the shader manager's default (+0x3c, 6). The original picks
// the NV40 profile with it; the GL port has one profile, so nothing reads the result yet.
uint32_t CShaderManagerPSGL_GetShaderModeForKey(const ShaderVariantKey& key);

// The linked GL program of a key (translated, compiled and cached on first use; platform/gfx/cg_program.h). Reads
// EBOOT.elf from the configured USRDIR on the first call; null when that fails or the variant does not compile.
const dotd::gfx::cg::Program* ShaderVariant_GetProgram(const ShaderVariantKey& key);
