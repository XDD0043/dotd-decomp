// Immediate3DShaderPassState.h - the shader pass state of an Im3D draw (vtable 0xb18f28, on the stack of
// ShaderManagerPSGL_BindImmediate3DShaders_maybe 0xffde8). Original unit: Immediate3DShaderPassState.cpp (0xf2f18-0xf30b0).
// Its +0x14 (the base's renderable slot) is the immediate pipeline's draw descriptor (the RwIm3D pool the PSGL
// immediate pipeline submits, DrawPSGLImmediateGeometry 0x76b610's 0xcf030c: +0x0c the RwIm3DTransform flags | 0x18,
// +0x10 the LTM): one texture coordinate set with rwIM3D_VERTEXUV (bit 0), the material modulation with rwIM3D_VERTEXXYZ
// (bit 3) and the vertex colour with rwIM3D_VERTEXRGBA (bit 4), both always set by RwIm3DTransform; the LTM as the world
// matrix; a white material. Every other slot is the base's 0 (or nothing): no lights, no fog, mode 0.
#pragma once
#include <cstdint>

#include "k2000/render/MeshShaderPassState.h"

struct RwIm3DDraw;

class Immediate3DShaderPassState : public ShaderPassState {
public:
    // 0x000f3040 Immediate3DShaderPassState_Construct_maybe (and the copy 0x000f3078): the base
    // (ShaderPassStateBase_Construct_maybe 0xf5260), the vtable. ShaderManagerPSGL_BindImmediate3DShaders_maybe inlines it
    // and stores the descriptor at +0x14.
    explicit Immediate3DShaderPassState(const RwIm3DDraw* descriptor) : m_descriptor(descriptor) {}

    uint32_t TexCoordSets() override;                   // vt+0x24 0x000f2f28
    uint32_t VertexColor() override;                    // vt+0x44 0x000f2f18
    uint32_t ModulateMaterial() override;               // vt+0x48 0x000f2f88
    void FillMaterialColor(float* dst) override;        // vt+0x90 0x000f2f38
    void FillSkinBoneMatrices(float* dst) override {}   // vt+0xa0 0x000f2f70 KStub_Nop_f2f70
    void FillDirLightColors(float* dst) override;       // vt+0xb4 0x000f6a00 ShaderPassState_FillDirLightColorUniforms_maybe
    const struct RwMatrix* GetWorldMatrix() override;   // vt+0xcc 0x000f2f78
    void BindMaterialTextures() override;               // vt+0xd0 0x000f69c8 MeshShaderPassState_BindFallbackTextureUnit7_maybe

    const RwIm3DDraw* m_descriptor;  // +0x14
};
