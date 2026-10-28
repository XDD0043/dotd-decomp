// MeshShaderPassState.cpp - reconstructed original translation unit 0xedb08-0xf1508 (GAME_TOC1, main_toc1), 61 functions, 58 live.
// Primary owner: MeshShaderPassState (not a registered class)
// Other owners: ShaderVariantKey (5), ConstructMeshShaderPassState (2), GetMeshPassWorldMatrix (1), MeshShaderPass (1), FillSkinBoneMatrixPaletteUniform (1), MeshShaderConstants (1), ShaderVariantList (1)
//
// C2.4 step 2 ports the pass state's getters (the shader variant is built from them) and the pass count; the uniform
// fillers (FillMaterialColorUniform ... FillWorldViewUniform, vt+0x90..0xd0) are step 3, the variant key builders
// are in ShaderVariantKey.cpp.
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xedb08  MeshShaderPassState_vf48
//   [x] 0xedb10  MeshShaderPassState_AllocateSlots_vfC_To0A_maybe
//   [x] 0xedb90  MeshShaderPassState_AllocatePointLightSlots_maybe
//   [x] 0xedc10  MeshShaderPassState_vf18
//   [x] 0xedc18  MeshShaderPassState_GetSkinWeightsUsed_maybe
//   [x] 0xedc70  MeshShaderPassState_GetTexCoordSetCount_maybe
//   [x] 0xedcd8  MeshShaderPassState_GetFogFlag_maybe
//   [x] 0xedd30  MeshShaderPassState_HasPrelitColors_maybe
//   [ ] 0xedd48  MeshShaderPassState_GetVertexModulateFlag_maybe
//   [x] 0xedd50  MeshShaderPassState_FillMaterialColorUniform_maybe
//   [x] 0xedde8  MeshShaderPassState_GetRemainingSpecialLights_maybe
//   [x] 0xede50  MeshShaderPassState_AllocateSlots_vf10_To0C_maybe
//   [x] 0xeded0  MeshShaderPassState_GetMaterialShaderMode_maybe
//   [ ] 0xedf28  MeshShaderPassState_ComputeLightCountSum_maybe  [dead]
//   [x] 0xedfe8  MeshShaderPassState_GetRemainingDirLights_maybe
//   [ ] 0xee068  MeshShaderPassState_vf38
//   [x] 0xee138  MeshShaderPassState_GetMaxSkinWeightsPerVertex_maybe
//   [x] 0xee188  GetMeshPassWorldMatrix
//   [ ] 0xee208  MeshShaderPassState_DeletingDestructor
//   [ ] 0xee250  MeshShaderPassState_Destruct
//   [ ] 0xee280  MeshShaderPassState_Destruct_2
//   [ ] 0xee2b0  MeshShaderPassState_ConstructEmpty_maybe
//   [ ] 0xee2e8  MeshShaderPassState_ConstructEmpty_2_maybe
//   [x] 0xee320  MeshShaderPassState_UsesUvTransform_maybe
//   [x] 0xee3c0  MeshShaderPassState_vf8C
//   [x] 0xee418  MeshShaderPassState_vf88
//   [x] 0xee470  MeshShaderPassState_vf84
//   [x] 0xee4c8  MeshShaderPassState_HasAuxLayerTexture_maybe
//   [x] 0xee520  MeshShaderPass_GetDualBlendMode_maybe
//   [x] 0xee5c0  MeshShaderPassState_IsVertexColorFirst_maybe
//   [x] 0xee5f8  MeshShaderPassState_FillAnimUniform_maybe
//   [x] 0xee730  MeshShaderPassState_FillSpecularUniform_maybe
//   [x] 0xee7d8  MeshShaderPassState_FillScaledDirLightColorUniforms_maybe
//   [x] 0xee880  MeshShaderPassState_FillPomTextureShadowUniform_maybe
//   [x] 0xee968  MeshShaderPassState_FillTransposedWorldMatrixUniform_maybe
//   [x] 0xeea50  FillSkinBoneMatrixPaletteUniform
//   [x] 0xeeac0  MeshShaderConstants_SetEnvMapCoefficients_maybe
//   [x] 0xeeba0  MeshShaderPassState_IsFogEnabled_maybe
//   [x] 0xeec20  MeshShaderPassState_FillDualUVTransformUniform_maybe
//   [x] 0xeecb0  MeshShaderPassState_FillUVTransformUniform_maybe
//   [x] 0xeed48  MeshShaderPassState_FillViewPomHeightUniform_maybe
//   [x] 0xeee80  MeshShaderPassState_IsFarTextureActive_maybe
//   [x] 0xeef48  MeshShaderPassState_IsShadowEnabled_maybe
//   [x] 0xeefe8  MeshShaderPassState_BindMaterialTextures_maybe
//   [x] 0xef448  MeshShaderPassState_IsSpecialLightActive_maybe
//   [x] 0xef528  MeshShaderPassState_HasSpecular_maybe
//   [x] 0xef5e0  MeshShaderPassState_FillWorldViewUniform_maybe
//   [x] 0xef698  MeshShaderPassState_GetPointLightCount_maybe
//   [x] 0xef790  MeshShaderPassState_ComputePointLightCount_maybe
//   [x] 0xef860  MeshShaderPassState_UsesNormalInfluence_maybe
//   [x] 0xef898  MeshShaderPassState_FillNormalParamUniform_maybe
//   [x] 0xefa78  MeshShaderPassState_FillMaterialExtColorUniform_maybe
//   [x] 0xefc08  MeshShaderPassState_ComputePassCount_maybe
//   [x] 0xefe08  ConstructMeshShaderPassState
//   [ ] 0xeff58  ConstructMeshShaderPassState_2  [dead]
//   [ ] (ShaderVariantKey.cpp) 0xf00a8 .. 0xf0f00
//   [x] 0xf5260  ShaderPassStateBase_Construct_maybe (unit ShaderPassStateBase)
//   [x] 0xf7eb8  MaterialMode_GetMaxShaderSlotCount_maybe (unit CShaderManagerPSGL)
#include "k2000/render/MeshShaderPassState.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Renderware/rpmatfx/RpMatFX.h"
#include "Renderware/rpskin/RpSkin.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/system/CTimeManager.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "k2000/graphical/render/CLightManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/render/ShaderMatrixCache.h"
#include "k2000/graphical/render/CBackgroundCopyRender.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/system/IKTime.h"
#include "platform/gfx/mesh.h"

namespace {
ShaderSceneInputs g_sceneInputs;

bool IsAuxMode(uint32_t mode) { return mode == 0xb || mode == 0xd || mode == 0xc || mode == 0xe; }
}  // namespace

ShaderSceneInputs& SceneInputs() { return g_sceneInputs; }

// CLightManager_ComputeLightCount_maybe 0x9b208 on the renderer's light manager (graphic +4 -> +0xac).
uint8_t SceneLightCount() { return g_pLightManager != nullptr ? static_cast<uint8_t>(g_pLightManager->ComputeLightCount()) : 0; }
// CLightManager_GatherLightsTouchingSphere_maybe 0x9c150: the point lights touching the sphere (kept in the manager).
uint32_t GatherPointLights(const float sphere[4]) { return g_pLightManager != nullptr ? g_pLightManager->GatherLightsTouchingSphere(sphere) : 0; }

// 0x000f5260 ShaderPassStateBase_Construct_maybe: every byte zero except the pass count 1 (the members' initializers).
ShaderPassState::ShaderPassState() {}

// 0x000edb10 MeshShaderPassState_AllocateSlots_vfC_To0A_maybe: vt+0x0c, limited to the slots left in the pass.
uint32_t ShaderPassState::AllocateDirLightSlots() {
    uint8_t wanted = static_cast<uint8_t>(DirLightsRemaining());
    const uint8_t used = m_slotsUsed;
    uint32_t result = wanted;
    if (static_cast<int32_t>(m_slotLimit) - static_cast<int32_t>(used) < static_cast<int32_t>(result)) {
        wanted = static_cast<uint8_t>(m_slotLimit - used);
        result = wanted;
    }
    m_dirAllocated = wanted;
    m_slotsUsed = static_cast<uint8_t>(wanted + used);
    return result;
}

// 0x000ede50 MeshShaderPassState_AllocateSlots_vf10_To0C_maybe: vt+0x10 into +0x0c.
uint32_t ShaderPassState::AllocateSpecialLightSlots() {
    uint8_t wanted = static_cast<uint8_t>(SpecialLightsRemaining());
    const uint8_t used = m_slotsUsed;
    uint32_t result = wanted;
    if (static_cast<int32_t>(m_slotLimit) - static_cast<int32_t>(used) < static_cast<int32_t>(result)) {
        wanted = static_cast<uint8_t>(m_slotLimit - used);
        result = wanted;
    }
    m_specialAllocated = wanted;
    m_slotsUsed = static_cast<uint8_t>(wanted + used);
    return result;
}

// 0x000edb90 MeshShaderPassState_AllocatePointLightSlots_maybe: vt+0x14 into +0x0b.
uint32_t ShaderPassState::AllocatePointLightSlots() {
    uint8_t wanted = static_cast<uint8_t>(PointLightsRemaining());
    const uint8_t used = m_slotsUsed;
    uint32_t result = wanted;
    if (static_cast<int32_t>(m_slotLimit) - static_cast<int32_t>(used) < static_cast<int32_t>(result)) {
        wanted = static_cast<uint8_t>(m_slotLimit - used);
        result = wanted;
    }
    m_pointAllocated = wanted;
    m_slotsUsed = static_cast<uint8_t>(wanted + used);
    return result;
}

// 0x000f7eb8 MaterialMode_GetMaxShaderSlotCount_maybe: shader slots per pass (lights, effects, textures share them).
uint32_t MaterialMode_GetMaxShaderSlotCount(int32_t mode, int32_t postOrFar, int32_t specular, int32_t textured) {
    const uint32_t untextured = textured != 0 ? 0u : 1u;
    const uint32_t base = untextured + (postOrFar != 0 ? 6u : 7u);
    if (mode == 0xc || mode == 0xe) return (base - 2) & 0xff;
    if (mode == 0xb || mode == 0xd) return specular != 0 ? (base - 4) & 0xff : (base - 3) & 0xff;
    return base & 0xff;
}

// 0x000efe08 ConstructMeshShaderPassState: the base constructed, the atomic and the material stored, the depth of
// field flag (bit 10 of the post-rendering object's flags, class key 0x38d) when the graphic caps have 0x200 and the
// shader manager runs the RSX profiles (+0x44, +0x40 = 6), the pass count computed and the per-pass counters cleared.
MeshShaderPassState::MeshShaderPassState(RpAtomic* renderable, RpMaterial* material) {
    m_renderable = renderable;
    m_material = material;
    // DEV guard: the tests build pass states without a core manager or shader manager.
    const CPostRenderingFx* postFx = g_pEngine->m_coreManager != nullptr
                                         ? static_cast<const CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d))
                                         : nullptr;
    m_depthOfFieldFlag = 0;
    if (postFx != nullptr && g_pShaderManager != nullptr && (g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 &&
        g_pShaderManager->m_bShadersEnabled != 0 &&
        g_pShaderManager->m_i32ProfileMode == 6) {
        m_depthOfFieldFlag = static_cast<uint8_t>((postFx->m_BitProperties >> 10) & 1);
    }
    ComputePassCount();
    m_specialDone = 0;
    m_passIndex = 0;
    m_dirDone = 0;
}

CMaterial* MeshShaderPassState::KMaterial() const { return m_material->kMaterial; }

// 0x000eded0 MeshShaderPassState_GetMaterialShaderMode_maybe (vt+0x08): CMaterial_GetShaderMode, bits 3-6 of its properties.
uint32_t MeshShaderPassState::GetMaterialShaderMode() {
    CMaterial* material = KMaterial();
    return material != nullptr ? (material->m_baProperties >> 3) & 0xf : 0;
}

// 0x000edfe8 MeshShaderPassState_GetRemainingDirLights_maybe (vt+0x0c): the scene's directional lights minus the ones earlier passes took,
// for geometries with light (rpGEOMETRYLIGHT 0x20).
uint32_t MeshShaderPassState::DirLightsRemaining() {
    const uint32_t geometryFlags = m_renderable->geometry->flags;
    const uint32_t lights = SceneLightCount();
    uint32_t result = 0;
    if ((geometryFlags & 0x20) != 0 && lights != 0) result = (lights - m_dirDone) & 0xff;
    return result;
}

// 0x000edde8 MeshShaderPassState_GetRemainingSpecialLights_maybe (vt+0x10): the special light (vt+0x30) minus what earlier passes took.
uint32_t MeshShaderPassState::SpecialLightsRemaining() {
    const uint8_t active = static_cast<uint8_t>(SpecialLightActive());
    uint8_t result = 0;
    if (active != 0) result = static_cast<uint8_t>(active - m_specialDone);
    return result;
}

// 0x000ef698 MeshShaderPassState_GetPointLightCount_maybe (vt+0x14): the point lights touching the atomic's world
// bounding sphere (at most 2) minus the ones earlier passes took; none unless the shader manager allows them.
uint32_t MeshShaderPassState::PointLightsRemaining() {
    if ((g_sceneInputs.managerFlags & 2) == 0) return 0;
    const float sphere[4] = {m_renderable->worldSphere[0], m_renderable->worldSphere[1], m_renderable->worldSphere[2],
                             m_renderable->worldSphere[3]};
    uint32_t count = GatherPointLights(sphere);
    if (count < 3) {
        if (count == 0) return 0;
    } else {
        count = 2;
    }
    return (count - m_pointDone) & 0xff;
}

// 0x000edc18 MeshShaderPassState_GetSkinWeightsUsed_maybe (vt+0x1c): the skin weights per vertex the shader handles (at most 2).
uint32_t MeshShaderPassState::SkinWeightsUsed() {
    uint8_t weights = static_cast<uint8_t>(MaxSkinWeights());
    if (weights > 2) weights = 2;
    return weights;
}

// 0x000ee138 MeshShaderPassState_GetMaxSkinWeightsPerVertex_maybe (vt+0x20): RpSkinGeometryGetSkin then
// RpSkin_GetMaxWeightsPerVertex_maybe (0 without a skin), as a byte.
uint32_t MeshShaderPassState::MaxSkinWeights() {
    const RpSkin* skin = RpSkinGeometryGetSkin(m_renderable->geometry);
    uint8_t weights = 0;
    if (skin != nullptr) weights = static_cast<uint8_t>(RpSkinGetMaxWeightsPerVertex(skin));
    return weights;
}

// 0x000eea50 FillSkinBoneMatrixPaletteUniform (vt+0xa0, uniform 0x11 VSC_BONE_MATRICES): the bone palette of the
// renderable through BridgeBuildPSGLSkinBoneMatrixPalette into the uniform record's data (+0x0c of the record
// 0x00c68448, 210 float4 registers c40..c249: 70 bones x 3). RpSkinAtomicGetHAnimHierarchy is called and its result
// dropped (the palette builder reads the hierarchy itself). The record's data persists between draws: the builder
// writes nothing for an atomic without a hierarchy and nothing on a cache hit, and the record keeps the last palette.
void MeshShaderPassState::FillSkinBoneMatrices(float* dst) {
    static float s_record[kSkinBoneMatrixFloats];  // the record's data
    const RpSkin* skin = RpSkinGeometryGetSkin(m_renderable->geometry);
    RpSkinAtomicGetHAnimHierarchy(m_renderable);
    BuildPSGLSkinBoneMatrixPalette(s_record, m_renderable, skin);
    std::memcpy(dst, s_record, sizeof s_record);
}

// 0x000edc70 MeshShaderPassState_GetTexCoordSetCount_maybe (vt+0x24): texture coordinate sets the shader reads: 1 with a textured
// geometry whose material has a texture, 2 for a geometry with two sets (rpGEOMETRYTEXTURED2), else 0.
uint32_t MeshShaderPassState::TexCoordSets() {
    if (m_material == nullptr) return 0;
    uint32_t result = 2;
    const uint32_t geometryFlags = m_renderable->geometry->flags;
    if ((geometryFlags & 4) == 0) {
        if ((geometryFlags & 0x80) == 0) return 0;
    } else {
        result = m_material->texture != nullptr ? 1u : 0u;
    }
    return result;
}

// 0x000edcd8 MeshShaderPassState_GetFogFlag_maybe (vt+0x28): the fog type: 1 when fog is on (vt+0x34), else 0.
uint32_t MeshShaderPassState::FogFlag() { return (IsFogEnabled() & 0xff) != 0 ? 1u : 0u; }

// 0x000eeba0 MeshShaderPassState_IsFogEnabled_maybe (vt+0x34): RwRenderStateGet(0xe) != 0 and the graphic module's
// fog texture (+0x1c) present.
uint32_t MeshShaderPassState::IsFogEnabled() {
    int32_t fog = 0;
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &fog);
    if (g_pEngine->m_graphic->m_pFogTexture == nullptr) return 0;
    return fog != 0 ? 1u : 0u;
}

// 0x000ef790 MeshShaderPassState_ComputePointLightCount_maybe (vt+0x2c): the point lights touching the atomic's
// local bounding sphere (at most 2), remembered in +0x0f.
uint32_t MeshShaderPassState::ComputePointLights() {
    // (the original also refreshes the atomic's morph bounding sphere when its flag 2 is set: one morph target here)
    const float sphere[4] = {m_renderable->boundingSphere[0], m_renderable->boundingSphere[1], m_renderable->boundingSphere[2],
                             m_renderable->boundingSphere[3]};
    uint32_t count = GatherPointLights(sphere);
    if (count > 2) count = 2;
    m_pointTouching = static_cast<uint8_t>(count);
    return count & 0xff;
}

// 0x000ef448 MeshShaderPassState_IsSpecialLightActive_maybe (vt+0x30): the special light: on for the aux layer modes with specular (vfD4).
uint32_t MeshShaderPassState::SpecialLightActive() {
    if (IsAuxMode(GetMaterialShaderMode()) && SpecularEnabled() != 0) {
        m_specialActive = 1;
        return 1;
    }
    m_specialActive = 0;
    return 0;
}

// 0x000ee5c0 MeshShaderPassState_IsVertexColorFirst_maybe (vt+0x3c): CMaterial property bit 10.
uint32_t MeshShaderPassState::ModulateVertexColorFirst() {
    CMaterial* material = KMaterial();
    return material != nullptr ? (material->m_baProperties >> 10) & 1 : 0;
}

// 0x000ef860 MeshShaderPassState_UsesNormalInfluence_maybe (vt+0x40): CMaterial property bit 11.
uint32_t MeshShaderPassState::UseNormalInfluence() {
    CMaterial* material = KMaterial();
    return material != nullptr ? (material->m_baProperties >> 11) & 1 : 0;
}

// 0x000edd30 MeshShaderPassState_HasPrelitColors_maybe (vt+0x44): the geometry has prelit colours (rpGEOMETRYPRELIT 8).
uint32_t MeshShaderPassState::VertexColor() { return (m_renderable->geometry->flags >> 3) & 1; }

// 0x000eef48 MeshShaderPassState_IsShadowEnabled_maybe (vt+0x54): the main camera is drawing, the shadow service is active (+0x14, +0x15), the
// shader manager's flag 1 is set (the geometry's shader flag byte) and the level's current sector has a shadow texture.
uint32_t MeshShaderPassState::ShadowEnabled() {
    const CKSrvShadow* shadow = static_cast<const CKSrvShadow*>(g_pEngine->m_srvShadow);
    if (RwDevice_GetCurrentCamera() != g_pEngine->m_graphic->m_renderer->m_cameraContext->m_pMainCamera) return 0;
    if (shadow->m_unk14 == 0 || shadow->m_unk15 == 0) return 0;
    if ((g_sceneInputs.managerFlags & 1) == 0) return 0;
    return shadow->EntryHasTexture(static_cast<uint32_t>(g_pEngine->m_level->m_currentSector)) & 0xff;
}

// 0x009a5850 MeshShaderPassState_IsDepthOfFieldPass_maybe (vt+0x58): the depth of field flag, in the first pass only.
uint32_t MeshShaderPassState::RenderDepthOfField() { return m_passIndex == 0 ? m_depthOfFieldFlag : 0; }

// 0x000ee520 MeshShaderPass_GetDualBlendMode_maybe (vt+0x78): for mode 6 (dual UV transform) the dual effect's blend:
// 2 for source alpha / one, else 1; 0 for other modes.
uint32_t MeshShaderPassState::DualBlendMode() {
    CMaterial* material = KMaterial();
    if (material == nullptr || ((material->m_baProperties >> 3) & 0xf) != 6) return 0;
    int32_t src = 0, dst = 0;
    RpMatFXMaterialGetDualBlendModes(material->m_pRpMaterial, &src, &dst);  // CMaterial_GetDualBlendMode_maybe 0xbba68
    uint32_t dual = 0;
    if (src == 5) {
        if (dst == 6) dual = 1;
        else if (dst == 2) dual = 2;
    }
    return dual == 2 ? 2u : 1u;
}

// 0x000ee320 MeshShaderPassState_UsesUvTransform_maybe (vt+0x7c): for the aux layer modes, CMaterial property bit 8 (the UV transform).
uint32_t MeshShaderPassState::UvTransform() {
    CMaterial* material = KMaterial();
    if (IsAuxMode(GetMaterialShaderMode()) && material != nullptr) return (material->m_baProperties >> 8) & 1;
    return 0;
}

// 0x000ee4c8 MeshShaderPassState_HasAuxLayerTexture_maybe (vt+0x80): CMaterial_HasAuxLayerTexture_maybe.
uint32_t MeshShaderPassState::HasAuxLayerTexture() {
    CMaterial* material = KMaterial();
    return material != nullptr && material->m_pAuxLayer != nullptr && material->m_pAuxLayer->m_pTexture != nullptr ? 1u : 0u;
}

// 0x000ee470 MeshShaderPassState_vf84 (vt+0x84): CMaterial_HasSecondaryEffectTexture_maybe: modes 2 and 3 ask the
// MatFX env map texture, the others the material's FX texture.
uint32_t MeshShaderPassState::HasSecondaryEffectTexture() {
    CMaterial* material = KMaterial();
    if (material == nullptr) return 0;
    if (((material->m_baProperties >> 3) & 0xf) - 2u > 1u) return material->m_FXParameters.m_pTexture != nullptr ? 1u : 0u;
    return RpMatFXMaterialGetEnvMapTexture(material->m_pRpMaterial) != nullptr ? 1u : 0u;
}

// 0x000ee418 MeshShaderPassState_vf88 (vt+0x88): CMaterial_HasAuxTexture8C_maybe.
uint32_t MeshShaderPassState::HasAuxTexture8C() {
    CMaterial* material = KMaterial();
    return material != nullptr && material->m_pAuxTexture8C != nullptr ? 1u : 0u;
}

// 0x000ee3c0 MeshShaderPassState_vf8C (vt+0x8c): CMaterial_HasAuxLayerTexture_maybe again.
uint32_t MeshShaderPassState::HasAuxLayerTextureB() { return HasAuxLayerTexture(); }

// 0x000ef528 MeshShaderPassState_HasSpecular_maybe (vt+0xd4): an aux layer mode material with a specular surface property.
uint32_t MeshShaderPassState::SpecularEnabled() {
    if (m_material != nullptr && IsAuxMode(GetMaterialShaderMode())) return 0.0f < m_material->surfaceProps.specular ? 1u : 0u;
    return 0;
}

// 0x000eee80 MeshShaderPassState_IsFarTextureActive_maybe (vt+0xd8): the far texture object (class key 0x4d0d) is active (+0x20 and +0x21)
// and the RW camera is the main one: the manager's flag 4. DEV guard: a level without the object gives 0 (the
// original reads through the null object).
uint32_t MeshShaderPassState::RenderFarTexture() {
    const CBackgroundCopyRender* farTexture =
        g_pEngine->m_coreManager != nullptr
            ? static_cast<const CBackgroundCopyRender*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x4d0d))
            : nullptr;
    if (farTexture != nullptr && g_pEngine->m_cameraContext != nullptr && farTexture->m_unk20 != 0 && farTexture->m_unk21 != 0 &&
        RwDevice_GetCurrentCamera() == static_cast<CameraContext*>(g_pEngine->m_cameraContext)->m_pMainCamera) {
        return (g_sceneInputs.managerFlags >> 2) & 1;
    }
    return 0;
}

// 0x000efc08 MeshShaderPassState_ComputePassCount_maybe: the lights (scene, point, special) share the shader
// slots of a pass (MaterialMode_GetMaxShaderSlotCount_maybe); more lights than slots mean more passes.
uint32_t MeshShaderPassState::ComputePassCount() {
    const uint8_t lights = SceneLightCount();
    m_lightCount = lights;
    const uint8_t pointLights = static_cast<uint8_t>(ComputePointLights());
    const uint8_t specialLights = static_cast<uint8_t>(SpecialLightActive());
    const uint8_t total = static_cast<uint8_t>(lights + specialLights + pointLights);
    const bool textured = m_material->texture != nullptr;
    CMaterial* material = KMaterial();
    const uint32_t mode = material != nullptr ? (material->m_baProperties >> 3) & 0xf : 0;
    const bool postOrFar = RenderDepthOfField() != 0 || RenderFarTexture() != 0;
    const uint32_t specular = SpecularEnabled() & 0xff;
    const uint8_t slots = static_cast<uint8_t>(
        MaterialMode_GetMaxShaderSlotCount(static_cast<int32_t>(mode), postOrFar ? 1 : 0, static_cast<int32_t>(specular), textured ? 1 : 0));
    m_passCount = 1;
    if (slots < total) {
        m_passCount = static_cast<uint8_t>(total / slots);
        if (total != static_cast<uint32_t>(m_passCount) * slots) m_passCount = static_cast<uint8_t>(m_passCount + 1);
    }
    m_slotLimit = slots;
    return slots;
}

// ==== the uniform fillers (C2.4 step 3) ================================================================
// Each fills the destination of one constant (float4 per register) from the pass state's material and atomic. The
// dispatcher is FillShaderUniformFromPassState 0xf7008 (ShaderUniform.cpp).

namespace {
float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}

// BindTextureOnUnit_maybe 0x598c0: the texture on a texture unit with the sampler state its filter / addressing word
// gives; null clears the unit.
void BindUnit(RwTexture* texture, int unit) {
    if (texture == nullptr || texture->raster == nullptr) {
        dotd::gfx::BindTextureUnit(unit, 0, dotd::gfx::DrawState());
        return;
    }
    dotd::gfx::BindTextureUnit(unit, RwDevice_GetRasterTexture(texture->raster), RwDevice_TextureState(texture));
}

// 0x000f69c8 MeshShaderPassState_BindFallbackTextureUnit7_maybe: CKGraphic +0x20 (the 16x16 blank texture) on unit 7.
void BindFallbackUnit7() {
    CKGraphic* graphic = g_pEngine->m_graphic;
    if (graphic->m_unk20 != nullptr) {
        BindUnit(static_cast<RwTexture*>(graphic->m_unk20), 7);
        return;
    }
    static uint32_t s_noFogTexture = 0;
    if (s_noFogTexture == 0) {
        const uint8_t clear[4] = {0, 0, 0, 0};
        s_noFogTexture = dotd::gfx::CreateTextureRGBA8(1, 1, clear, false);
    }
    dotd::gfx::BindTextureUnit(7, s_noFogTexture, dotd::gfx::DrawState());
}

// The fog texture (or the dummy texture) of texture unit 7: with fog on (vt+0x34) the level's fog texture (CKGraphic +0x1c)
// whose filter / addressing word is set to clamp / clamp and filter 5 first (the word's other bits stay), else the 16x16
// blank texture of CKGraphic +0x20. The shader reads (fog colour rgb, fog amount a) from it at the fog coefficient; the
// blank one has no fog amount. The blank texture is created by CKGraphic_InitializeModule, which is a stand-in here (+0x20
// stays null): a clear 1x1 texture gives the same (zero) fog amount.
void BindFogTextureUnit(ShaderPassState* pass) {
    CKGraphic* graphic = g_pEngine->m_graphic;
    if ((pass->IsFogEnabled() & 0xff) != 0) {
        RwTexture* fog = static_cast<RwTexture*>(graphic->m_pFogTexture);
        fog->filterAddressing = (fog->filterAddressing & 0xffff0000u) | 0x3305u;
        BindUnit(fog, 7);
        return;
    }
    BindFallbackUnit7();
}

// Two rows of a UV transform matrix as constant registers: the matrix is a 4x3 RW matrix (rows right, up, at, pos),
// the registers hold (right.x, up.x, at.x, pos.x) and (right.y, up.y, at.y, pos.y).
void FillUvRows(const CMatrix34* m, float* dst) {
    dst[0] = m->m_right.x;
    dst[1] = m->m_up.x;
    dst[2] = m->m_at.x;
    dst[3] = m->m_pos.x;
    dst[4] = m->m_right.y;
    dst[5] = m->m_up.y;
    dst[6] = m->m_at.y;
    dst[7] = m->m_pos.y;
}

const RwMatrix* g_worldMatrixOverride = nullptr;  // 0x00c68314
}  // namespace

void BindFallbackTextureUnit7() { BindFallbackUnit7(); }

// 0x000598c0 BindTextureOnUnit_maybe
void BindTextureOnUnit(RwTexture* texture, int unit) { BindUnit(texture, unit); }

void MeshShaderPass_SetWorldMatrixOverride(const RwMatrix* matrix) { g_worldMatrixOverride = matrix; }

// 0x000f52f0 ShaderPassState_FillAmbientColorUniform_maybe (vt+0xb0): the rig's ambient colour in the first pass, zero in
// the later ones (they only add lights).
void ShaderPassState::FillAmbientColor(float* dst) {
    if (m_passIndex == 0) {
        const float* ambient = g_pLightManager != nullptr && g_pLightManager->m_pAmbientLight != nullptr ? g_pLightManager->GetAmbientColor() : nullptr;
        for (int i = 0; i < 4; ++i) dst[i] = ambient != nullptr ? ambient[i] : 0.0f;
    } else {
        dst[0] = dst[1] = dst[2] = dst[3] = 0.0f;
    }
}

// 0x000edd50 MeshShaderPassState_FillMaterialColorUniform_maybe (vt+0x90)
void MeshShaderPassState::FillMaterialColor(float* dst) {
    dst[0] = static_cast<float>(m_material->color.red) / 255.0f;
    dst[1] = static_cast<float>(m_material->color.green) / 255.0f;
    dst[2] = static_cast<float>(m_material->color.blue) / 255.0f;
    dst[3] = static_cast<float>(m_material->color.alpha) / 255.0f;
}

// 0x000eeac0 MeshShaderConstants_SetEnvMapCoefficients_maybe (vt+0x94): for the env map modes (2, 10, 12, 14) the
// coefficient and the material's float at +0x90.
void MeshShaderPassState::FillEnvMapCoefficients(float* dst) {
    CMaterial* material = KMaterial();
    if (material == nullptr) return;
    const uint32_t mode = (material->m_baProperties >> 3) & 0xf;
    if (mode == 2 || mode == 10 || mode == 12 || mode == 14) {
        dst[0] = material->GetEnvMapCoefficient();
        dst[1] = WordAsFloat(material->m_unk90);
        dst[2] = 0.0f;
        dst[3] = 0.0f;
    }
}

// 0x000eecb0 MeshShaderPassState_FillUVTransformUniform_maybe (vt+0x98)
void MeshShaderPassState::FillUvTransform(float* dst) {
    const CMatrix34* m = KMaterial()->GetUVTransformMatrix();
    if (m != nullptr) FillUvRows(m, dst);
}

// 0x000eec20 MeshShaderPassState_FillDualUVTransformUniform_maybe (vt+0x9c): no null check in the original.
void MeshShaderPassState::FillDualUvTransform(float* dst) { FillUvRows(KMaterial()->GetDualUVTransformMatrix(), dst); }

// 0x000eed48 MeshShaderPassState_FillViewPomHeightUniform_maybe (vt+0xa4): xyz zero, w the aux layer's parameter 8 for the modes 11 and 13.
void MeshShaderPassState::FillViewPomHeight(float* dst) {
    dst[0] = dst[1] = dst[2] = 0.0f;
    CMaterial* material = KMaterial();
    if (material == nullptr) return;
    const uint32_t mode = (material->m_baProperties >> 3) & 0xf;
    if (mode == 0xb || mode == 0xd) dst[3] = WordAsFloat(material->m_pAuxLayer->m_ui32Param8);
}

// 0x000ef898 MeshShaderPassState_FillNormalParamUniform_maybe (vt+0xa8): the normal map parameters: from the material's property bits, or for
// the modes 11 and 13 from the aux layer.
void MeshShaderPassState::FillNormalParam(float* dst) {
    CMaterial* material = KMaterial();
    const uint32_t mode = (material->m_baProperties >> 3) & 0xf;
    if (mode != 0xd && mode != 0xb) {
        const uint32_t props = material->m_baProperties;
        dst[0] = (props & 0x800) == 0 ? 1.0f : 0.0f;
        dst[1] = (props & 0x400) == 0 ? 0.0f : 1.0f;
        dst[2] = (props & 0x400) == 0 ? 1.0f : 0.0f;
        dst[3] = (props & 0x4000) == 0 ? 0.0f : 1.0f;
        return;
    }
    const CMaterialAuxLayer* aux = material->m_pAuxLayer;
    dst[0] = WordAsFloat(aux->m_ui32Param8);
    dst[1] = static_cast<float>(aux->m_ui8Byte6);
    dst[2] = static_cast<float>(aux->m_ui8Byte4);
    dst[3] = static_cast<float>(aux->m_ui8Byte5);
}

// 0x000ee880 MeshShaderPassState_FillPomTextureShadowUniform_maybe (vt+0xac): the aux layer texture's size and the layer's parameter C.
void MeshShaderPassState::FillPomTextureShadow(float* dst) {
    CMaterial* material = KMaterial();
    RwTexture* texture = material->m_pAuxLayer != nullptr ? material->GetAuxLayerTexture() : nullptr;
    float* out = dst;
    if (texture != nullptr) {
        out = dst + 2;
        dst[0] = texture->raster != nullptr ? static_cast<float>(texture->raster->width) : 0.0f;
        dst[1] = texture->raster != nullptr ? static_cast<float>(texture->raster->height) : 0.0f;
    }
    *out = WordAsFloat(material->m_pAuxLayer->m_ui32ParamC);
}

// 0x000ee7d8 MeshShaderPassState_FillScaledDirLightColorUniforms_maybe (vt+0xb4): ShaderPassState_FillDirLightColor-
// Uniforms_maybe 0xf6a00 (the colours of the rig's distinct lights, as many as the pass has not taken: see the dispatcher's
// note on the light order) times the material's diffuse.
void MeshShaderPassState::FillDirLightColors(float* dst) {
    FillDirLightColorUniforms(this, dst);
    for (int i = 0; i < 4; ++i) {
        dst[i * 4 + 0] *= m_material->surfaceProps.diffuse;
        dst[i * 4 + 1] *= m_material->surfaceProps.diffuse;
        dst[i * 4 + 2] *= m_material->surfaceProps.diffuse;
    }
}

// 0x000ee730 MeshShaderPassState_FillSpecularUniform_maybe (vt+0xb8): (specular, aux float 0x94) of the K material, else the RW material's
// specular and 20.0.
void MeshShaderPassState::FillSpecular(float* dst) {
    CMaterial* material = KMaterial();
    dst[0] = m_material->surfaceProps.specular;  // CMaterial_GetSpecular_maybe 0xbb3c0 reads the RW material's
    dst[1] = material != nullptr ? material->m_fAuxFloat94 : 20.0f;
}

// 0x000efa78 MeshShaderPassState_FillMaterialExtColorUniform_maybe (vt+0xbc)
void MeshShaderPassState::FillExtColor(float* dst) {
    CMaterial* material = KMaterial();
    const uint8_t white[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc
    for (int i = 0; i < 4; ++i) dst[i] = static_cast<float>(material != nullptr ? material->m_cExtColor[i] : white[i]) / 255.0f;
}

// 0x000ee188 GetMeshPassWorldMatrix (vt+0xcc): the override matrix (0x00c68314) when set, else the atomic's frame LTM
// (none for a PTank atomic).
const RwMatrix* MeshShaderPassState::GetWorldMatrix() {
    if (g_worldMatrixOverride != nullptr) return g_worldMatrixOverride;
    if (RpAtomicIsPTank(m_renderable) == 0 && m_renderable->frame != nullptr) return RwFrameGetLTM(m_renderable->frame);
    return nullptr;
}

// 0x000ef5e0 MeshShaderPassState_FillWorldViewUniform_maybe (vt+0xc0): the transposed world * view matrix with its
// last register row replaced by the eye position in object space and 1.
void MeshShaderPassState::FillWorldView(float* dst) {
    GetTransposedWorldViewMatrix(dst);
    float eye[3], object[3];
    ShaderMatrixCache_GetEyeWorld(eye);
    ShaderMatrixCache_WorldPointToObject(eye, object);
    dst[12] = object[0];
    dst[13] = object[1];
    dst[14] = object[2];
    dst[15] = 1.0f;
}

// 0x000ee968 MeshShaderPassState_FillTransposedWorldMatrixUniform_maybe (vt+0xc4): the world matrix's three register
// rows and (0, 0, 0, 1); the identity without a world matrix.
void MeshShaderPassState::FillWorld(float* dst) {
    const RwMatrix* world = GetWorldMatrix();
    for (int i = 0; i < 16; ++i) dst[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    if (world == nullptr) return;
    dst[0] = world->right.x; dst[1] = world->up.x; dst[2] = world->at.x; dst[3] = world->pos.x;
    dst[4] = world->right.y; dst[5] = world->up.y; dst[6] = world->at.y; dst[7] = world->pos.y;
    dst[8] = world->right.z; dst[9] = world->up.z; dst[10] = world->at.z; dst[11] = world->pos.z;
    dst[12] = 0.0f; dst[13] = 0.0f; dst[14] = 0.0f; dst[15] = 1.0f;
}

// 0x000ee5f8 MeshShaderPassState_FillAnimUniform_maybe (vt+0xc8): the game time and the aux layer's animation parameters.
void MeshShaderPassState::FillAnim(float* dst) {
    CMaterial* material = KMaterial();
    const CMaterialAuxLayer* aux = material->m_pAuxLayer;
    dst[0] = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    dst[1] = aux != nullptr ? aux->m_afUnk10[6] : 0.0f;  // +0x28
    for (int i = 0; i < 6; ++i) dst[2 + i] = aux != nullptr ? aux->m_afUnk10[i] : 0.0f;  // +0x10 .. +0x24
}

// 0x000eefe8 MeshShaderPassState_BindMaterialTextures_maybe (vt+0xd0): the material's extra textures on their units
// by shader mode (the diffuse texture is unit 0, bound by the pass loop), then the fog texture on unit 7. The jump
// table at 0x000ef11c: modes 2, 4 / 6, 10, 11, 12, 13, 14 have extra textures.
void MeshShaderPassState::BindMaterialTextures() {
    CMaterial* material = KMaterial();
    if (material != nullptr) {
        switch ((material->m_baProperties >> 3) & 0xf) {
            case 2:
                if (RwTexture* t = material->GetEnvMapTexture()) BindUnit(t, 1);
                break;
            case 4:
            case 6:
                if (RwTexture* t = RpMatFXMaterialGetDualTexture(m_material)) BindUnit(t, 1);
                break;
            case 10:
                if (RwTexture* t = material->GetEnvMapTexture()) BindUnit(t, 1);
                if (material->m_pAuxTexture88 != nullptr) BindUnit(material->m_pAuxTexture88, 2);
                break;
            case 11:
                if (material->GetAuxLayerTexture() != nullptr) BindUnit(material->GetAuxLayerTexture(), 1);
                break;
            case 12:
                if (material->HasAuxLayerTexture()) {
                    BindUnit(material->GetAuxLayerTexture(), 1);
                    if (material->HasSecondaryEffectTexture() != 0) BindUnit(material->GetEnvMapTexture(), 2);
                    BindUnit(material->m_pAuxTexture8C, 4);  // (a dummy texture when there is none)
                } else {
                    if (material->HasAuxTexture88OrLayerTexture()) BindUnit(material->m_pAuxTexture88, 3);
                    if (material->HasSecondaryEffectTexture() != 0) {
                        BindUnit(material->GetEnvMapTexture(), 1);
                    } else if (material->m_pAuxTexture8C != nullptr) {
                        BindUnit(material->m_pAuxTexture8C, 1);
                    }
                }
                break;
            case 13:
                if (material->GetAuxLayerTexture() != nullptr) BindUnit(material->GetAuxLayerTexture(), 1);
                if (material->m_pAuxTexture88 != nullptr) BindUnit(material->m_pAuxTexture88, 2);
                break;
            case 14:
                if (material->GetAuxLayerTexture() != nullptr) BindUnit(material->GetAuxLayerTexture(), 1);
                if (RwTexture* t = material->GetEnvMapTexture()) BindUnit(t, 2);
                break;
            default:
                break;
        }
    }
    BindFogTextureUnit(this);
}
