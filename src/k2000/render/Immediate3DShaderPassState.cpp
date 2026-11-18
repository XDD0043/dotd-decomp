// Reconstructed original translation unit: 0xf2f18-0xf30b0 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary owner: Immediate3DShaderPassState (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xf2f18  Immediate3DShaderPassState_vf44_KeyBit1_DescBit4_maybe
//   [x] 0xf2f28  Immediate3DShaderPassState_vf24_GetKeyByte9_DescBit0_maybe
//   [x] 0xf2f38  Immediate3DShaderPassState_vf90_FillVec4Ones_maybe
//   [x] 0xf2f68  KStub_Nop_f2f68  (vt+0xe0: only this vtable has the slot, the mesh and Im2D ones end before it; no caller, not declared)
//   [x] 0xf2f70  KStub_Nop_f2f70  (vt+0xa0, Immediate3DShaderPassState.h)
//   [x] 0xf2f78  Immediate3DShaderPassState_vfCC_GetDescField10_maybe
//   [x] 0xf2f88  Immediate3DShaderPassState_vf48_KeyBit2_DescBit3_maybe
//   [x] 0xf2f98  Immediate3DShaderPassState_DeletingDestructor_maybe  (the C++ destructor)
//   [x] 0xf2fe0  Immediate3DShaderPassState_Destruct_maybe  (the C++ destructor: the base's, ShaderPassStateBase_Destruct_maybe)
//   [ ] 0xf3010  Immediate3DShaderPassState_Destruct_2_maybe  [dead] (its OPD 0xb54600 is unreferenced)
//   [x] 0xf3040  Immediate3DShaderPassState_Construct_maybe  (Immediate3DShaderPassState.h)
//   [ ] 0xf3078  Immediate3DShaderPassState_Construct_2_maybe  [dead] (its OPD 0xb54610 is unreferenced)
#include "k2000/render/Immediate3DShaderPassState.h"

#include "Renderware/rwcore/RwIm3D.h"

// 0x000f2f28 Immediate3DShaderPassState_vf24_GetKeyByte9_DescBit0_maybe: descriptor +0x0c bit 0 (rwIM3D_VERTEXUV).
uint32_t Immediate3DShaderPassState::TexCoordSets() { return m_descriptor->transformFlags & 1u; }

// 0x000f2f18 Immediate3DShaderPassState_vf44_KeyBit1_DescBit4_maybe: descriptor +0x0c bit 4 (rwIM3D_VERTEXRGBA).
uint32_t Immediate3DShaderPassState::VertexColor() { return (m_descriptor->transformFlags >> 4) & 1u; }

// 0x000f2f88 Immediate3DShaderPassState_vf48_KeyBit2_DescBit3_maybe: descriptor +0x0c bit 3 (rwIM3D_VERTEXXYZ).
uint32_t Immediate3DShaderPassState::ModulateMaterial() { return (m_descriptor->transformFlags >> 3) & 1u; }

// 0x000f2f38 Immediate3DShaderPassState_vf90_FillVec4Ones_maybe: (1, 1, 1, 1) into the uniform's data.
void Immediate3DShaderPassState::FillMaterialColor(float* dst) {
    dst[0] = 1.0f;
    dst[1] = 1.0f;
    dst[3] = 1.0f;
    dst[2] = 1.0f;
}

// 0x000f6a00 (the mesh pass state's filler of the directional light colours).
void Immediate3DShaderPassState::FillDirLightColors(float* dst) { FillDirLightColorUniforms(this, dst); }

// 0x000f2f78 Immediate3DShaderPassState_vfCC_GetDescField10_maybe: descriptor +0x10, the LTM RwIm3DTransform was given
// (null: none, the vertices are in world space).
const RwMatrix* Immediate3DShaderPassState::GetWorldMatrix() {
    return m_descriptor->hasLtm ? &m_descriptor->ltm : nullptr;
}

// 0x000f69c8 MeshShaderPassState_BindFallbackTextureUnit7_maybe: CKGraphic +0x20 (the blank texture) on unit 7.
void Immediate3DShaderPassState::BindMaterialTextures() { BindFallbackTextureUnit7(); }
