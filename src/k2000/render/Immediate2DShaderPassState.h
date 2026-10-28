// Immediate2DShaderPassState.h - the shader pass state of an Im2D draw (vtable 0xb18e40, on the stack of
// ShaderManagerPSGL_BindImmediate2DShaders_maybe 0xffd58). Original unit: Immediate2DShaderPassState.cpp (0xf2bf8-0xf2f18).
// Every slot it does not override is the base's (0x9a5810..0x9a59a8: 0, or nothing); the overrides give one texture
// coordinate set for a bound raster, the vertex colour, no material modulation (the identity world-view-projection: the
// PSGL Im2D path sends clip-space vertices) and the post pass the shader manager's mode (+0x48) names.
#pragma once
#include <cstdint>

#include "k2000/render/MeshShaderPassState.h"

class Immediate2DShaderPassState : public ShaderPassState {
public:
    // 0x000f2d48 Immediate2DShaderPassState_Construct_maybe: the base (ShaderPassStateBase_Construct_maybe 0xf5260),
    // the vtable, +0x11 = 0.
    Immediate2DShaderPassState() { m_forceTexCoords = 0; }

    uint32_t TexCoordSets() override;                 // vt+0x24 0x000f2bf8
    uint32_t VertexColor() override { return 1; }     // vt+0x44 0x000f2c90 KStub_Return1
    uint32_t ModulateMaterial() override { return 0; }  // vt+0x48 0x009a5960 (the base's 0)
    uint32_t PostDepthOfField() override;             // vt+0x5c 0x000f2df8 (mode 1)
    uint32_t GaussianBlur() override;                 // vt+0x60 0x000f2dc8 (mode 2)
    uint32_t CopyAlpha() override;                    // vt+0x64 0x000f2ee8 (mode 3)
    uint32_t DownSample4x4() override;                // vt+0x68 0x000f2eb8 (mode 4)
    uint32_t DontModulateAlphaTexture() override;     // vt+0x6c 0x000f2e88 (mode 5)
    uint32_t DownSample16x16() override;              // vt+0x70 0x000f2e58 (mode 6)
    uint32_t Bloom() override;                        // vt+0x74 0x000f2e28 (mode 7)
    void FillMaterialColor(float* dst) override;      // vt+0x90 0x000f68d8 ShaderPassStateBase_maybe_vf90_FillVec4Ones_maybe
    void FillDirLightColors(float* dst) override;     // vt+0xb4 0x000f6a00 ShaderPassState_FillDirLightColorUniforms_maybe
    void BindMaterialTextures() override;             // vt+0xd0 0x000f69c8 MeshShaderPassState_BindFallbackTextureUnit7_maybe

    uint8_t m_forceTexCoords;  // +0x11 (the constructor clears it; nothing sets it in DotD) _maybe
};
