// ShaderVariantKey.cpp - reconstructed original translation unit 0xf1508-0xf26a0 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary owner: ShaderVariantKey (not a registered class)
// Other owners: ShaderCacheEntry (2)
//
// C2.4 step 2: the key builder for meshes, the key comparisons, and (from MeshShaderPassState.cpp and
// ShaderProgramBase.cpp) the key's init / equality, the define list and the uniform lists. The shader cache
// file (ShaderCacheEntry_Read/Write) is not needed: the programs are translated at run time.
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xf1508  ShaderVariantKey_BuildForMesh_maybe
//   [x] 0xf1c90  ShaderVariantKey_BuildForMesh_maybe  (thunk)
//   [x] 0xf1c98  ShaderVariantKey_BuildForMesh_maybe  (thunk)
//   [x] 0xf1ca0  ShaderVariantKey_BuildForImmediate3D_maybe  (thunk; the body 0xf07a8 is MeshShaderPassState.cpp's range)
//   [x] 0xf1ca8  ShaderVariantKey_BuildForImmediate3D_maybe  (thunk)
//   [x] 0xf1cb0  ShaderVariantKey_BuildFromPassState_maybe  (thunk)
//   [x] 0xf1cb8  ShaderVariantKey_BuildFromPassState_maybe  (thunk)
//   (from MeshShaderPassState.cpp) [x] 0xf0108 ShaderVariantKey_BuildFromPassState_maybe
//   (from MeshShaderPassState.cpp) [x] 0xf07a8 ShaderVariantKey_BuildForImmediate3D_maybe (bit 6 is cleared once more after
//   bit 9: the word started at 0)
//   [x] 0xf1cc0  KStub_Nop_f1cc0
//   [ ] 0xf1cc8  KStub_Nop_f1cc8  [dead]
//   [ ] 0xf1cd0  ShaderVariantKey_Copy_2_maybe  [dead]
//   [x] 0xf1d48  ShaderVariantKey_Assign_maybe  (struct assignment)
//   [x] 0xf1dc0  ShaderVariantKey_Copy_maybe  (struct copy)
//   [x] 0xf1e38  ShaderVariantKey_MatchesVertexShader_maybe
//   [x] 0xf2000  ShaderVariantKey_MatchesPixelShader_maybe
//   [ ] 0xf21e8  ShaderCacheEntry_Read_maybe  (shfct.bin cache: not used)  [platform]  (the shfct.bin shader cache / its offline variant lists: the programs are translated at run time (ShaderVariantKey.cpp header))
//   [ ] 0xf2448  ShaderCacheEntry_Write_maybe  [platform]  (the shfct.bin shader cache / its offline variant lists: the programs are translated at run time (ShaderVariantKey.cpp header))
//   (from other units) [x] 0xf00d8 Init, [x] 0xf0e48 Equals, [x] 0xf41b0 / 0xf44c0 / 0xf48c0 Collect*, [x] 0xf8840 GetShaderModeForKey
//   Not ported: ShaderVariantList_AppendVariantsForMaterialMode_maybe 0xf0f00, ShaderVariantList_AppendFixedVariants_maybe 0xf26a0 and
//   ShaderVariantList_BuildDefaults_maybe 0xf2900 list every key a material mode can need, to pre-generate shfct.bin offline; the
//   translator makes variants on demand (STUB(offline): shader_variants_test sweeps the keys instead).
#include "k2000/render/ShaderVariantKey.h"

#include <cstring>
#include <string>
#include <unordered_map>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/render/MeshShaderPassState.h"
#include "platform/config.h"
#include "platform/gfx/cg_program.h"
#include "platform/log.h"

using dotd::gfx::cg::Define;

namespace {
bool IsAuxMode(uint32_t mode) { return mode == 0xb || mode == 0xd || mode == 0xc || mode == 0xe; }
uint32_t Bit(uint32_t flags, int n) { return (flags >> n) & 1; }
void SetBit(uint32_t* flags, int n, uint32_t value) { *flags = (*flags & ~(1u << n)) | ((value & 0xff) << n); }
}  // namespace

// 0x000f00d8 ShaderVariantKey_Init_maybe
void ShaderVariantKey_Init(ShaderVariantKey* key) { std::memset(key, 0, sizeof(ShaderVariantKey)); }

// 0x000f1508 ShaderVariantKey_BuildForMesh_maybe. The calls are the pass state's virtual slots, in the original's
// order (the allocations take shader slots out of the pass's budget, so the order matters).
void ShaderVariantKey_BuildForMesh(ShaderVariantKey* key, ShaderPassState* pass) {
    uint32_t& flags = key->flags;
    key->texCoords = static_cast<uint8_t>(pass->TexCoordSets());          // vt+0x24
    key->mode = pass->GetMaterialShaderMode();                            // vt+0x08
    if (key->texCoords == 0) key->mode = 0;
    SetBit(&flags, 12, pass->HasAuxTexture8C());                          // vt+0x88
    if (IsAuxMode(key->mode) && pass->HasAuxLayerTexture() == 0) {        // vt+0x80: an aux layer mode without its texture
        flags &= ~(1u << 12);
        if (pass->HasSecondaryEffectTexture() == 0) {                     // vt+0x84
            key->mode = pass->UvTransform() == 0 ? 0u : 5u;               // vt+0x7c
        } else {
            key->mode = 2;
        }
    }
    SetBit(&flags, 11, pass->HasSecondaryEffectTexture());                // vt+0x84
    SetBit(&flags, 13, pass->HasAuxLayerTextureB());                      // vt+0x8c
    SetBit(&flags, 10, pass->HasAuxLayerTexture());                       // vt+0x80
    key->specialLights = static_cast<uint8_t>(pass->AllocateSpecialLightSlots());  // 0xede50
    key->dirLights = static_cast<uint8_t>(pass->AllocateDirLightSlots());          // 0xedb10
    key->pointLights = static_cast<uint8_t>(pass->AllocatePointLightSlots());      // 0xedb90
    key->spotLights = static_cast<uint8_t>(pass->SpotLights());           // vt+0x18
    key->weights = static_cast<uint8_t>(pass->SkinWeightsUsed());         // vt+0x1c
    key->fogType = static_cast<uint8_t>(pass->FogFlag());                 // vt+0x28
    key->dualBlend = pass->DualBlendMode();                               // vt+0x78
    SetBit(&flags, 1, pass->VertexColor());                               // vt+0x44
    SetBit(&flags, 2, pass->ModulateMaterial());                          // vt+0x48
    SetBit(&flags, 3, pass->SpecularEnabled());                           // vt+0xd4
    SetBit(&flags, 4, pass->m_passIndex == 0 ? 1u : 0u);                  // the first pass
    SetBit(&flags, 14, pass->RenderDepthOfField());                       // vt+0x58
    SetBit(&flags, 15, pass->PostDepthOfField());                         // vt+0x5c
    SetBit(&flags, 17, pass->GaussianBlur());                             // vt+0x60
    SetBit(&flags, 16, pass->CopyAlpha());                                // vt+0x64
    SetBit(&flags, 18, pass->DownSample4x4());                            // vt+0x68
    SetBit(&flags, 19, pass->DontModulateAlphaTexture());                 // vt+0x6c
    SetBit(&flags, 20, pass->DownSample16x16());                          // vt+0x70
    SetBit(&flags, 21, pass->Bloom());                                    // vt+0x74
    SetBit(&flags, 0, pass->UvTransform());                               // vt+0x7c
    const CMaterial* material = pass->m_material->kMaterial;
    SetBit(&flags, 6, material != nullptr ? (material->m_baProperties >> 14) & 1 : 0);  // the env alpha subtract bit
    SetBit(&flags, 5, pass->RenderFarTexture());                          // vt+0xd8
    SetBit(&flags, 7, pass->ShadowEnabled());                             // vt+0x54
    SetBit(&flags, 8, pass->ModulateVertexColorFirst());                  // vt+0x3c
    SetBit(&flags, 9, pass->UseNormalInfluence());                        // vt+0x40
}

// 0x000f0108 ShaderVariantKey_BuildFromPassState_maybe (also the thunks 0xf1cb0 / 0xf1cb8): the key of a pass state
// that is not a mesh's (the Im2D draws: ShaderManagerPSGL_BindImmediate2DShaders_maybe). The same slots as
// BuildForMesh in another order, without the aux-layer fallbacks and the light slot allocation: the mode is vt+0xd4 (0
// without texture coordinates), the light counts are the getters' (vt+0x10 / +0x0c / +0x14), bit 3 is vt+0x50 (no pass
// state of the immediate paths overrides the base's 0; the dotd base does not declare the slot).
void ShaderVariantKey_BuildFromPassState(ShaderVariantKey* key, ShaderPassState* pass) {
    key->texCoords = static_cast<uint8_t>(pass->TexCoordSets());          // vt+0x24
    key->mode = pass->SpecularEnabled();                                  // vt+0xd4
    if (key->texCoords == 0) key->mode = 0;
    key->specialLights = static_cast<uint8_t>(pass->SpecialLightsRemaining());  // vt+0x10
    key->dirLights = static_cast<uint8_t>(pass->DirLightsRemaining());    // vt+0x0c
    key->pointLights = static_cast<uint8_t>(pass->PointLightsRemaining());  // vt+0x14
    key->spotLights = static_cast<uint8_t>(pass->SpotLights());           // vt+0x18
    key->weights = static_cast<uint8_t>(pass->SkinWeightsUsed());         // vt+0x1c
    key->fogType = static_cast<uint8_t>(pass->FogFlag());                 // vt+0x28
    key->dualBlend = pass->DualBlendMode();                               // vt+0x78
    uint32_t& flags = key->flags;
    flags = 0;
    SetBit(&flags, 1, pass->VertexColor());                               // vt+0x44
    SetBit(&flags, 2, pass->ModulateMaterial());                          // vt+0x48
    SetBit(&flags, 3, 0);                                                 // vt+0x50
    SetBit(&flags, 4, pass->m_passIndex == 0 ? 1u : 0u);                  // (+5 - 1) >> 63: the first pass
    SetBit(&flags, 14, pass->RenderDepthOfField());                       // vt+0x58
    SetBit(&flags, 15, pass->PostDepthOfField());                         // vt+0x5c
    SetBit(&flags, 17, pass->GaussianBlur());                             // vt+0x60
    SetBit(&flags, 16, pass->CopyAlpha());                                // vt+0x64
    SetBit(&flags, 18, pass->DownSample4x4());                            // vt+0x68
    SetBit(&flags, 19, pass->DontModulateAlphaTexture());                 // vt+0x6c
    SetBit(&flags, 20, pass->DownSample16x16());                          // vt+0x70
    SetBit(&flags, 21, pass->Bloom());                                    // vt+0x74
    SetBit(&flags, 0, pass->UvTransform());                               // vt+0x7c
    SetBit(&flags, 5, pass->RenderFarTexture());                          // vt+0xd8
    SetBit(&flags, 7, pass->ShadowEnabled());                             // vt+0x54
    SetBit(&flags, 8, pass->ModulateVertexColorFirst());                  // vt+0x3c
    SetBit(&flags, 9, pass->UseNormalInfluence());                        // vt+0x40
    SetBit(&flags, 10, pass->HasAuxLayerTexture());                       // vt+0x80
    SetBit(&flags, 11, pass->HasSecondaryEffectTexture());                // vt+0x84
    SetBit(&flags, 12, pass->HasAuxTexture8C());                          // vt+0x88
    SetBit(&flags, 13, pass->HasAuxLayerTextureB());                      // vt+0x8c
}

// 0x000f07a8 ShaderVariantKey_BuildForImmediate3D_maybe (and the thunks 0xf1ca0 / 0xf1ca8)
void ShaderVariantKey_BuildForImmediate3D(ShaderVariantKey* key, ShaderPassState* pass) {
    key->texCoords = static_cast<uint8_t>(pass->TexCoordSets());          // vt+0x24
    key->mode = pass->SpecularEnabled();                                  // vt+0xd4
    if (key->texCoords == 0) key->mode = 0;
    key->specialLights = static_cast<uint8_t>(pass->SpecialLightsRemaining());  // vt+0x10
    key->dirLights = static_cast<uint8_t>(pass->DirLightsRemaining());    // vt+0x0c
    key->pointLights = static_cast<uint8_t>(pass->PointLightsRemaining());  // vt+0x14
    key->spotLights = static_cast<uint8_t>(pass->SpotLights());           // vt+0x18
    key->weights = static_cast<uint8_t>(pass->SkinWeightsUsed());         // vt+0x1c
    key->fogType = static_cast<uint8_t>(pass->FogFlag());                 // vt+0x28
    key->dualBlend = pass->DualBlendMode();                               // vt+0x78
    uint32_t& flags = key->flags;
    flags = 0;
    SetBit(&flags, 1, pass->VertexColor());                               // vt+0x44
    SetBit(&flags, 2, pass->ModulateMaterial());                          // vt+0x48
    SetBit(&flags, 3, 0);                                                 // vt+0x50 (KStub_Return0_9a5810 in every pass state)
    SetBit(&flags, 4, pass->m_passIndex == 0 ? 1u : 0u);                  // (+5 - 1) >> 63: the first pass
    SetBit(&flags, 14, pass->RenderDepthOfField());                       // vt+0x58
    SetBit(&flags, 15, pass->PostDepthOfField());                         // vt+0x5c
    SetBit(&flags, 17, pass->GaussianBlur());                             // vt+0x60
    SetBit(&flags, 16, pass->CopyAlpha());                                // vt+0x64
    SetBit(&flags, 18, pass->DownSample4x4());                            // vt+0x68
    SetBit(&flags, 19, pass->DontModulateAlphaTexture());                 // vt+0x6c
    SetBit(&flags, 20, pass->DownSample16x16());                          // vt+0x70
    SetBit(&flags, 21, pass->Bloom());                                    // vt+0x74
    SetBit(&flags, 0, pass->UvTransform());                               // vt+0x7c
    SetBit(&flags, 5, pass->ImmediateKeyBit5());                          // vt+0xdc
    SetBit(&flags, 7, pass->ShadowEnabled());                             // vt+0x54
    SetBit(&flags, 8, pass->ModulateVertexColorFirst());                  // vt+0x3c
    SetBit(&flags, 9, pass->UseNormalInfluence());                        // vt+0x40
    SetBit(&flags, 10, pass->HasAuxLayerTexture());                       // vt+0x80
    SetBit(&flags, 11, pass->HasSecondaryEffectTexture());                // vt+0x84
    SetBit(&flags, 12, pass->HasAuxTexture8C());                          // vt+0x88
    SetBit(&flags, 13, pass->HasAuxLayerTextureB());                      // vt+0x8c
}

// 0x000f0e48 ShaderVariantKey_Equals
bool ShaderVariantKey_Equals(const ShaderVariantKey& a, const ShaderVariantKey& b) {
    return a.mode == b.mode && a.specialLights == b.specialLights && a.dirLights == b.dirLights &&
           a.pointLights == b.pointLights && a.spotLights == b.spotLights && a.texCoords == b.texCoords &&
           a.fogType == b.fogType && a.dualBlend == b.dualBlend && a.flags == b.flags && a.weights == b.weights;
}

// 0x000f1e38 ShaderVariantKey_MatchesVertexShader_maybe
bool ShaderVariantKey_MatchesVertexShader(const ShaderVariantKey& a, const ShaderVariantKey& b) {
    if (a.texCoords != b.texCoords) return false;
    uint32_t mode;
    bool checkAux = true;  // the aux modes compare the UV-transform bit first
    if (a.texCoords == 0) {
        mode = a.mode;
    } else {
        mode = a.mode;
        const uint32_t other = b.mode;
        if (!(mode == other || ((mode == 10 || mode == 2) && (other == 10 || other == 2)))) {
            if (mode == 0) {
                if (other != 9 && other != 1 && other != 3 && other != 7 && other != 8) return false;
            } else {
                if (mode != 9 && mode != 1 && mode != 3 && mode != 7 && mode != 8) return false;
                if (other != 0) return false;
            }
            checkAux = false;
        }
    }
    const uint32_t f2 = a.flags, f3 = b.flags;
    if (checkAux && IsAuxMode(mode)) {
        if ((f2 & 1) != (f3 & 1)) return false;
    }
    const uint32_t vertexColor = Bit(f2, 1);
    if (vertexColor != Bit(f3, 1)) return false;
    if ((vertexColor == 0 || Bit(f2, 4) == Bit(f3, 4)) && a.dirLights == b.dirLights && a.pointLights == b.pointLights &&
        a.specialLights == b.specialLights && a.weights == b.weights && Bit(f2, 14) == Bit(f3, 14) &&
        Bit(f2, 5) == Bit(f3, 5)) {
        return Bit(f2, 7) == Bit(f3, 7);
    }
    return false;
}

// 0x000f2000 ShaderVariantKey_MatchesPixelShader_maybe
bool ShaderVariantKey_MatchesPixelShader(const ShaderVariantKey& a, const ShaderVariantKey& b) {
    if (a.texCoords != b.texCoords) return false;
    const uint32_t mode = a.mode;
    bool checkDual = true;
    if (a.texCoords != 0) {
        const uint32_t other = b.mode;
        if (mode != other) {
            if (mode == 0) {
                if (other != 9 && other != 5 && other != 4 && other != 1 && other != 3) return false;
            } else {
                if (mode != 9 && mode != 5 && mode != 4 && mode != 1 && mode != 3) return false;
                if (other != 0) return false;
            }
            checkDual = false;
        }
    }
    if (checkDual && mode == 6 && a.dualBlend != b.dualBlend) return false;
    if (a.specialLights == b.specialLights && a.pointLights == b.pointLights && a.dirLights == b.dirLights) {
        const uint32_t f2 = a.flags, f3 = b.flags;
        if ((Bit(f2, 3) == Bit(f3, 3) || !IsAuxMode(mode)) && Bit(f2, 1) == Bit(f3, 1) && Bit(f2, 14) == Bit(f3, 14) &&
            Bit(f2, 15) == Bit(f3, 15) && Bit(f2, 17) == Bit(f3, 17) && Bit(f2, 16) == Bit(f3, 16) &&
            Bit(f2, 18) == Bit(f3, 18) && Bit(f2, 19) == Bit(f3, 19) && Bit(f2, 20) == Bit(f3, 20) &&
            Bit(f2, 21) == Bit(f3, 21) && Bit(f2, 5) == Bit(f3, 5)) {
            return Bit(f2, 7) == Bit(f3, 7);
        }
    }
    return false;
}

// 0x000f48c0 ShaderGen_CollectExternFragments_maybe: (name, value) pairs in the original's order. The strings are
// the ones of TOC 0x00c159d8 (resolved offline: "1" 0xac56d0, "0" 0xac57c0, "%d" 0xac5810).
std::vector<Define> ShaderGen_CollectExternFragments(const ShaderVariantKey& key) {
    std::vector<Define> out;
    auto add = [&out](const char* name, const std::string& value) { out.push_back({name, value}); };
    const uint32_t flags = key.flags;
    if ((flags & kShaderKeyPostDof) != 0) {
        add("externPostRenderDepthOfField", "1");
        add("externDontModulateAlphaTexture", "1");
    }
    if ((flags & kShaderKeyDontModulateAlpha) != 0) add("externDontModulateAlphaTexture", "1");
    if ((flags & kShaderKeyGaussianBlur) != 0) {
        add("externGaussianBlur5x5", "1");
        add("externDontModulateAlphaTexture", "1");
    }
    if ((flags & kShaderKeyCopyAlpha) != 0) add("externDOFCopyAlpha", "1");
    if ((flags & kShaderKeyDownSample4x4) != 0) add("externDownSample4x4", "1");
    if ((flags & kShaderKeyBloom) != 0) add("externBloom", "1");
    if ((flags & kShaderKeyDownSample16x16) != 0) add("externDownSample16x16", "1");
    if ((flags & kShaderKeyShadow) != 0) add("externShadowEnable", "1");
    add("externTransform", "0");
    if ((flags & kShaderKeyRenderDof) != 0) add("externRenderDepthOfField", "0");
    if ((flags & kShaderKeyRenderFarTex) != 0) add("externRenderFarTex", "0");
    add("externFogType", std::to_string(key.fogType));
    add("externDirLight", std::to_string(key.dirLights));
    add("externPointLight", std::to_string(key.pointLights));
    add("externSpotLight", std::to_string(key.spotLights));
    add("externVertexColor", (flags & kShaderKeyVertexColor) != 0 ? "1" : "0");
    add("externWeightNb", std::to_string(key.weights));
    if ((flags & kShaderKeyModulateVertexColorFirst) != 0) add("externModulateVertexColorFirst", "0");
    if ((flags & kShaderKeyUseNormalInfluence) != 0) add("externUseNormalInfluence", "0");
    add("externTexCoordNb", std::to_string(key.texCoords));
    add("externFirstPass", (flags & kShaderKeyFirstPass) != 0 ? "1" : "0");
    if ((flags & kShaderKeySpecular) != 0) add("externSpecular", "0");
    // The material effect, by mode (the jump table at 0xf4c84).
    const uint32_t mode = key.mode;
    switch (mode) {
    case 2: add("externMATERIALFX_ENV", "0"); break;
    case 4: add("externMATERIALFX_DUALPASS", "0"); break;
    case 5: add("externMATERIALFX_UVTRANSFORM", "0"); break;
    case 6:
        add("externMATERIALFX_DUALUVTRANSFORM", "0");
        if (key.dualBlend == 2) add("externDualAlphaBlend", "0");
        break;
    case 7: add("externMATERIALFX_REFRACT", "0"); break;
    case 8: add("externMATERIALFX_REFRACT_ENV", "0"); break;
    case 9: add("externMATERIALFX_ALPHA_SORT", "0"); break;
    case 10:
        add("externMATERIALFX_ENV", "0");
        add("externUseCtrlMap", "0");
        break;
    case 11: add("externMATERIALFX_POM", "0"); break;
    case 12:
        if ((flags & kShaderKeyAuxLayerTexture) != 0) {
            add("externMATERIALFX_NORMAL", "0");
            add("externUseNormalMap", "0");
            add("externUseEnvMap", "0");
            add("externUseDualEnvMap", "0");
        }
        break;
    case 13:
        add("externMATERIALFX_POM", "0");
        add("externUseCtrlMap", "0");
        break;
    case 14: add("externMATERIALFXNORMANIM", "0"); break;
    default: add("externMATERIALFX_NONE", "0"); break;  // modes 0, 1, 3 and anything above 14
    }
    if (IsAuxMode(mode) && (flags & kShaderKeyUvTransform) != 0) add("externMATERIALFX_UVTRANSFORM", "0");
    const bool envSubtract = mode == 2 || mode == 3 || mode == 8 || mode == 10 || mode == 12 || mode == 14;
    if (envSubtract && (flags & kShaderKeyEnvSubtractAlpha) != 0) add("externEnvSubstractAlpha", "0");
    add("externSpecialLight", std::to_string(key.specialLights));
    add("externPS3", "0");
    if (SceneInputs().pixelLightning != 0) add("externPixelLightning", "1");
    return out;
}

// The Cg DeclareUniform names in the order of ShaderUniformId (the shader's own tables: vertex 0xc26750+, pixel 0xc19848+).
const char* ShaderUniformCgName(int32_t id) {
    static const char* const kNames[] = {
        "u_f4Fog", "u_f44WorldViewProj", "u_f4AmbientColor", "u_f4MaterialColor", "u_f4DirLight", "u_f4DirLightColor",
        "u_f4PointLight", "u_f4PointLightColor", "u_f4UvAnimMatrix", "u_fViewPomH", "u_f4Specular", "u_f4SecondUvAnimMatrix",
        "u_f4SpecialLightDir", "u_f44WorldView", "u_f44World", "u_f4InfoQuadShadow", "u_f4BoneWeight", "u_f34BoneMatrix",
        // pixel program, from 0x12
        "u_f4PixelDirLight", "u_f4PixelDirLightColor", "u_f4PixelAmbientColor", "u_f4PixelPointLight", "u_f4PixelPointLightColor",
        "u_f4NormalParam", "u_f3PomTextureShadow", "u_f4Specular", "u_f4SpecularColor", "u_f4PixelMaterialColor", "u_f4PixelMatFx",
        "u_f4SpecialLight", "u_f4DofParam", "u_f4DofAjustTex", "u_f4DofPixelSize", "u_f4DofRadius", "u_f2FarCameraAndTolerance",
        "u_f4AnimFx", "u_f3MinMaxShadow", "u_f44WorldViewProj", "u_af2SampleOffsets", "u_af4Gauss5x5"};
    if (id < 0 || id >= static_cast<int32_t>(sizeof kNames / sizeof kNames[0])) return nullptr;
    return kNames[id];
}

// 0x000f44c0 ShaderGen_CollectVertexUniforms_maybe
std::vector<int32_t> ShaderGen_CollectVertexUniforms(const ShaderVariantKey& key) {
    std::vector<int32_t> ids;
    const uint32_t flags = key.flags;
    const uint32_t mode = key.mode;
    const bool pixelLightning = SceneInputs().pixelLightning != 0;
    ids.push_back(kVscFog);
    ids.push_back(kVscWorldViewProj);
    if ((flags & kShaderKeyShadow) != 0) {
        ids.push_back(kVscWorld);
        ids.push_back(kVscInfoQuadShadow);
    }
    ids.push_back(kVscMaterialColor);
    if (key.weights != 0) {
        ids.push_back(kVscBoneMatrices);
        ids.push_back(kVscBoneWeight);
    }
    if ((flags & kShaderKeySpecular) != 0) ids.push_back(kVscViewPomHeight);
    bool addPom = false;  // uniform 9 after the mode switch (0xf45c8)
    switch (mode) {
    case 2:
        addPom = true;
        break;
    case 4:
    case 6:
        ids.push_back(kVscUvTransform);
        ids.push_back(kVscDualUvTransform);
        break;
    case 5:
        ids.push_back(kVscUvTransform);
        break;
    case 10:
        addPom = (flags & kShaderKeyAuxLayerTexture) != 0;
        break;
    case 11:
    case 13:
        addPom = (flags & kShaderKeySpecular) == 0;
        break;
    case 12:
        if ((flags & kShaderKeyUvTransform) != 0) ids.push_back(kVscUvTransform);
        addPom = (flags & kShaderKeyAuxLayerTexture) != 0;
        break;
    case 14:
        if ((flags & kShaderKeyUvTransform) != 0) ids.push_back(kVscUvTransform);
        addPom = true;
        break;
    default:
        break;
    }
    if (addPom) ids.push_back(kVscViewPomHeight);
    if (IsAuxMode(mode) && (flags & kShaderKeyUvTransform) != 0) ids.push_back(kVscUvTransform);
    if (key.specialLights != 0) ids.push_back(kVscSpecialLight);
    ids.push_back(kVscWorldView);
    ids.push_back(kVscAmbientColor);
    if (key.dirLights != 0) {
        if (mode - 0xb < 4) {
            ids.push_back(kVscDirLightDir);
        } else if (!pixelLightning) {
            ids.push_back(kVscDirLightDir);
            ids.push_back(kVscDirLightColor);
            ids.push_back(kVscSpecular);
        }
    }
    if (key.pointLights != 0) {
        if (mode - 0xb < 4) {
            ids.push_back(kVscPointLightPos);
        } else if (!pixelLightning) {
            ids.push_back(kVscPointLightPos);
            ids.push_back(kVscPointLightColor);
            ids.push_back(kVscSpecular);
        }
    }
    return ids;
}

// 0x000f41b0 ShaderGen_CollectPixelUniforms_maybe
std::vector<int32_t> ShaderGen_CollectPixelUniforms(const ShaderVariantKey& key) {
    std::vector<int32_t> ids;
    const uint32_t flags = key.flags;
    const uint32_t mode = key.mode;
    const bool pixelLightning = SceneInputs().pixelLightning != 0;
    if (mode == 0xe) ids.push_back(kPscAnim);
    ids.push_back(kPscMaterialColor);
    if ((flags & kShaderKeySpecular) != 0) {
        ids.push_back(kPscSpecular);
        ids.push_back(kPscSpecularColor);
    }
    ids.push_back(kPscAmbientColor);
    if (key.dirLights != 0) {
        bool skip = false;
        if (mode - 0xb > 3) {
            if (!pixelLightning) skip = true;
            else ids.push_back(kPscDirLightDir);
        }
        if (!skip) ids.push_back(kPscDirLightColor);
    }
    if (key.pointLights != 0 && (mode - 0xb < 4 || pixelLightning)) {
        ids.push_back(kPscPointLightPos);
        ids.push_back(kPscPointLightColor);
    }
    if (mode < 0xf) {
        const uint32_t bit = 1u << mode;
        if ((bit & 0x5404) != 0) {
            ids.push_back(kPscMaterialFx);
            ids.push_back(kPscNormalParam);
        } else if ((bit & 0x2800) != 0) {
            ids.push_back(kPscPomTextureShadow);
        }
    }
    if (key.specialLights != 0) ids.push_back(kPscSpecialLight);
    if ((flags & kShaderKeyRenderDof) != 0) {
        ids.push_back(kPscDofParam);
        ids.push_back(kPscDofAdjustTex);
        ids.push_back(kPscDofPixelSize);
        ids.push_back(kPscDofRadius);
    }
    if ((flags & kShaderKeyGaussianBlur) != 0) ids.push_back(kPscGauss5x5);
    if ((flags & kShaderKeyDownSample4x4) != 0 || (flags & kShaderKeyDownSample16x16) != 0) ids.push_back(kPscDownSample);
    if ((flags & kShaderKeyRenderFarTex) != 0) ids.push_back(kPscFarCamera);
    if ((flags & kShaderKeyShadow) != 0) ids.push_back(kPscMinMaxShadow);
    return ids;
}

// 0x000f8840 CShaderManagerPSGL_GetShaderModeForKey_maybe
uint32_t CShaderManagerPSGL_GetShaderModeForKey(const ShaderVariantKey& key) {
    uint32_t mode = SceneInputs().defaultShaderMode;
    if ((key.flags & kShaderKeyPostDof) != 0 || (key.flags & kShaderKeyGaussianBlur) != 0 || key.mode == 0xb || key.mode == 0xd) mode = 6;
    return mode;
}

// (no original address: the run-time replacement of CShaderManagerPSGL_FindOrCreatePrograms_maybe 0xfd3f8 / the shader
// cache: the program of a key, translated and compiled on first use)
// The programs by key (perf): the define list of a key costs a vector of strings and the program lookup by that list a
// string map search, on every mesh draw. Everything ShaderGen_CollectExternFragments reads is in the cache key: the key's
// fields (all but the padding byte +0x0b) and ShaderSceneInputs::pixelLightning (externPixelLightning). The entries
// hold what cg::GetProgram answered (programs are compiled once and never change); they are dropped when the program
// cache is destroyed (cg::ProgramsGeneration, CShaderManagerPSGL::ReleaseShaderResources).
namespace {
struct ProgramCacheKey {
    uint32_t words[6];
    bool operator==(const ProgramCacheKey& o) const { return std::memcmp(words, o.words, sizeof words) == 0; }
};
struct ProgramCacheHash {
    size_t operator()(const ProgramCacheKey& k) const {
        uint64_t h = 0xcbf29ce484222325ull;
        for (uint32_t w : k.words) h = (h ^ w) * 0x100000001b3ull;
        return static_cast<size_t>(h ^ (h >> 32));
    }
};
std::unordered_map<ProgramCacheKey, const dotd::gfx::cg::Program*, ProgramCacheHash> g_programsByKey;
uint32_t g_programsByKeyGeneration = 0;
// perf: the last key asked for and its answer (consecutive draws mostly share their variant): no hashing for a repeat.
ProgramCacheKey g_lastProgramKey;
const dotd::gfx::cg::Program* g_lastProgram = nullptr;
bool g_lastProgramValid = false;
}  // namespace

const dotd::gfx::cg::Program* ShaderVariant_GetProgram(const ShaderVariantKey& key) {
    if (!dotd::gfx::cg::SourcesLoaded()) {
        const std::string path = dotd::platform::GetConfig().usrdir + "/EBOOT.elf";
        std::string error;
        if (!dotd::gfx::cg::InitSources(path.c_str(), &error)) {
            DOTD_LOG("shader: cannot read the Cg sources: %s", error.c_str());
            return nullptr;
        }
    }
    if (g_programsByKeyGeneration != dotd::gfx::cg::ProgramsGeneration()) {
        g_programsByKey.clear();
        g_lastProgramValid = false;
        g_programsByKeyGeneration = dotd::gfx::cg::ProgramsGeneration();
    }
    ProgramCacheKey cacheKey;
    cacheKey.words[0] = key.mode;
    cacheKey.words[1] = static_cast<uint32_t>(key.specialLights) | static_cast<uint32_t>(key.dirLights) << 8 |
                        static_cast<uint32_t>(key.pointLights) << 16 | static_cast<uint32_t>(key.spotLights) << 24;
    cacheKey.words[2] = static_cast<uint32_t>(key.weights) | static_cast<uint32_t>(key.texCoords) << 8 |
                        static_cast<uint32_t>(key.fogType) << 16;
    cacheKey.words[3] = key.dualBlend;
    cacheKey.words[4] = key.flags;
    cacheKey.words[5] = SceneInputs().pixelLightning != 0 ? 1u : 0u;
    if (g_lastProgramValid && cacheKey == g_lastProgramKey) return g_lastProgram;
    const dotd::gfx::cg::Program* program = nullptr;
    auto found = g_programsByKey.find(cacheKey);
    if (found != g_programsByKey.end()) {
        program = found->second;
    } else {
        program = dotd::gfx::cg::GetProgram(ShaderGen_CollectExternFragments(key));
        program = program != nullptr && program->error.empty() ? program : nullptr;
        g_programsByKey.emplace(cacheKey, program);
    }
    g_lastProgramKey = cacheKey;
    g_lastProgram = program;
    g_lastProgramValid = true;
    return program;
}
