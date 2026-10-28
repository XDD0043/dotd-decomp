// Reconstructed original translation unit: 0xf2bf8-0xf2f18 (GAME_TOC1, main_toc1), 15 functions, 14 live.
// Primary owner: Immediate2DShaderPassState (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xf2bf8  Immediate2DShaderPassState_GetTexCoordSetCount_maybe
//   [x] 0xf2c90  KStub_Return1_f2c90  (Immediate2DShaderPassState.h)
//   [ ] 0xf2c98  KStub_Nop_f2c98  [dead]
//   [ ] 0xf2ca0  Immediate2DShaderPassState_DeletingDestructor_maybe
//   [ ] 0xf2ce8  Immediate2DShaderPassState_Destruct_maybe
//   [ ] 0xf2d18  Immediate2DShaderPassState_Destruct_2_maybe
//   [x] 0xf2d48  Immediate2DShaderPassState_Construct_maybe  (Immediate2DShaderPassState.h)
//   [ ] 0xf2d88  Immediate2DShaderPassState_Construct_2_maybe
//   [x] 0xf2dc8  Immediate2DShaderPassState_IsGaussianBlur_maybe
//   [x] 0xf2df8  Immediate2DShaderPassState_IsPostDof_maybe
//   [x] 0xf2e28  Immediate2DShaderPassState_IsBloom_maybe
//   [x] 0xf2e58  Immediate2DShaderPassState_IsDownSample16x16_maybe
//   [x] 0xf2e88  Immediate2DShaderPassState_IsDontModulateAlpha_maybe
//   [x] 0xf2eb8  Immediate2DShaderPassState_IsDownSample4x4_maybe
//   [x] 0xf2ee8  Immediate2DShaderPassState_IsCopyAlpha_maybe
#include "k2000/render/Immediate2DShaderPassState.h"

#include "Renderware/rwcore/RwIm3D.h"
#include "k2000/render/CShaderManagerPSGL.h"

namespace {
// The seven post slots: (|mode ^ n| - 1) >> 31, i.e. the shader manager's Im2D mode (+0x48) is n.
uint32_t ModeIs(uint32_t n) { return g_pShaderManager->m_ui32Immediate2DMode == n ? 1u : 0u; }
}  // namespace

// 0x000f2bf8 Immediate2DShaderPassState_GetTexCoordSetCount_maybe: one texture coordinate set when +0x11 is set, else when
// a raster is bound (RwRenderStateGet(rwRENDERSTATETEXTURERASTER)) whose type byte (+0x20) has a bit of 0x27. Every
// raster that is set as a texture is a texture (4) or a camera texture (5), so a bound raster counts here.
uint32_t Immediate2DShaderPassState::TexCoordSets() {
    void* raster = nullptr;
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &raster);
    const uint32_t bound = raster != nullptr ? 1u : 0u;
    if (m_forceTexCoords != 0) return 1;
    return bound & 0xff;
}

uint32_t Immediate2DShaderPassState::PostDepthOfField() { return ModeIs(1); }          // 0x000f2df8
uint32_t Immediate2DShaderPassState::GaussianBlur() { return ModeIs(2); }              // 0x000f2dc8
uint32_t Immediate2DShaderPassState::CopyAlpha() { return ModeIs(3); }                 // 0x000f2ee8
uint32_t Immediate2DShaderPassState::DownSample4x4() { return ModeIs(4); }             // 0x000f2eb8
uint32_t Immediate2DShaderPassState::DontModulateAlphaTexture() { return ModeIs(5); }  // 0x000f2e88
uint32_t Immediate2DShaderPassState::DownSample16x16() { return ModeIs(6); }           // 0x000f2e58
uint32_t Immediate2DShaderPassState::Bloom() { return ModeIs(7); }                     // 0x000f2e28

// 0x000f68d8 ShaderPassStateBase_maybe_vf90_FillVec4Ones_maybe: (1, 1, 1, 1).
void Immediate2DShaderPassState::FillMaterialColor(float* dst) {
    dst[0] = 1.0f;
    dst[1] = 1.0f;
    dst[3] = 1.0f;
    dst[2] = 1.0f;
}

// 0x000f6a00 (the mesh pass state's filler of the directional light colours).
void Immediate2DShaderPassState::FillDirLightColors(float* dst) { FillDirLightColorUniforms(this, dst); }

// 0x000f69c8 MeshShaderPassState_BindFallbackTextureUnit7_maybe: CKGraphic +0x20 (the blank texture) on unit 7.
void Immediate2DShaderPassState::BindMaterialTextures() { BindFallbackTextureUnit7(); }
