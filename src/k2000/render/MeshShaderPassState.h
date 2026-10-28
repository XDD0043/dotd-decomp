// MeshShaderPassState.h - the shader pass state of one mesh (C2.4 step 2): what the renderer asks about a
// mesh (its atomic, its RpMaterial and the K material behind it) and about the scene to pick the shader variant.
// Original unit: MeshShaderPassState.cpp (0xedb08-0xf1508); the object is built per mesh by
// ConstructMeshShaderPassState 0xefe08 (vtable 0xb18d58) over ShaderPassStateBase_Construct_maybe 0xf5260.
//
// The getters are the virtual slots ShaderVariantKey_BuildForMesh_maybe 0xf1508 and the pass count calls (the
// slot offset is in each comment). The uniform fillers (vt+0x90..0xd0) and the texture binding (vt+0xd0) are
// step 3 (ported: FillShaderUniformFromPassState in ShaderUniform.cpp calls them); the slots that BuildForMesh does not
// call stay unported (vt+0x38, +0x50; vt+0x4c is the constant 0 of ShaderPassState_EnableFlag).
//
// Scene dependence: the original reads the light manager, the render states, the shadow service and the shader
// manager's flag word. Those are ported in steps 5-7; until then they are the fields of ShaderSceneInputs,
// which a caller fills by hand (the lights and the fog come from the light manager and the render states since step 6).
// STUB(C2.4 step 7): shadows.
#pragma once
#include <cstdint>

struct RpAtomic;
struct RpMaterial;

// The bone palette uniform (VSC_BONE_MATRICES, u_f34BoneMatrix[70], float3x4): 210 float4 registers.
constexpr uint32_t kSkinBoneMatrixFloats = 210 * 4;
class CMaterial;

// The scene state the pass state reads (PS3 sources in the comments).
struct ShaderSceneInputs {
    // (C2.4 step 6: the light count, the point lights touching a sphere, the ambient colour and the fog state are read from the
    // light manager and the render states now: CLightManager::ComputeLightCount / GatherLightsTouchingSphere / GetAmbientColor,
    // RwRenderStateGet(0xe) and the graphic module's fog texture.)
    // g_ShaderManagerPSGL +0x8c (set by the renderer): bit 0 shadow textures, bit 1 point lights, bit 2 far texture.
    uint32_t managerFlags = 0;
    // g_ShaderManagerPSGL +0x38 (ConstructMembers 0xf9138: 0): the lights are computed in the pixel shader.
    uint8_t pixelLightning = 0;
    // g_ShaderManagerPSGL +0x3c (ConstructMembers: 6): the shader mode of the Cg profile table.
    uint32_t defaultShaderMode = 6;
    // (C2.4 step 8: the far-texture object and the depth of field flag are read from the level's objects:
    // MeshShaderPassState::RenderFarTexture 0xeee80, ConstructMeshShaderPassState 0xefe08.)
};
ShaderSceneInputs& SceneInputs();

// 0x000f5260 ShaderPassStateBase_Construct_maybe and the base's slots.
class ShaderPassState {
public:
    ShaderPassState();
    virtual ~ShaderPassState() {}

    virtual uint32_t GetMaterialShaderMode() { return 0; }  // vt+0x08
    virtual uint32_t DirLightsRemaining() { return 0; }     // vt+0x0c
    virtual uint32_t SpecialLightsRemaining() { return 0; } // vt+0x10
    virtual uint32_t PointLightsRemaining() { return 0; }   // vt+0x14
    virtual uint32_t SpotLights() { return 0; }             // vt+0x18
    virtual uint32_t SkinWeightsUsed() { return 0; }        // vt+0x1c
    virtual uint32_t MaxSkinWeights() { return 0; }         // vt+0x20
    virtual uint32_t TexCoordSets() { return 0; }           // vt+0x24
    virtual uint32_t FogFlag() { return 0; }                // vt+0x28
    virtual uint32_t ComputePointLights() { return 0; }     // vt+0x2c
    virtual uint32_t SpecialLightActive() { return 0; }     // vt+0x30
    virtual uint32_t IsFogEnabled() { return 0; }           // vt+0x34
    virtual uint32_t ModulateVertexColorFirst() { return 0; }  // vt+0x3c
    virtual uint32_t UseNormalInfluence() { return 0; }     // vt+0x40
    virtual uint32_t VertexColor() { return 0; }            // vt+0x44
    virtual uint32_t ModulateMaterial() { return 1; }       // vt+0x48
    virtual uint32_t ShadowEnabled() { return 0; }          // vt+0x54
    virtual uint32_t RenderDepthOfField() { return 0; }     // vt+0x58
    virtual uint32_t PostDepthOfField() { return 0; }       // vt+0x5c  KStub_Return0 9a5818
    virtual uint32_t GaussianBlur() { return 0; }           // vt+0x60
    virtual uint32_t CopyAlpha() { return 0; }              // vt+0x64
    virtual uint32_t DownSample4x4() { return 0; }          // vt+0x68
    virtual uint32_t DontModulateAlphaTexture() { return 0; }  // vt+0x6c
    virtual uint32_t DownSample16x16() { return 0; }        // vt+0x70
    virtual uint32_t Bloom() { return 0; }                  // vt+0x74
    virtual uint32_t DualBlendMode() { return 0; }          // vt+0x78
    virtual uint32_t UvTransform() { return 0; }            // vt+0x7c
    virtual uint32_t HasAuxLayerTexture() { return 0; }     // vt+0x80
    virtual uint32_t HasSecondaryEffectTexture() { return 0; }  // vt+0x84
    virtual uint32_t HasAuxTexture8C() { return 0; }        // vt+0x88 (CMaterial_HasAuxTexture8C_maybe)
    virtual uint32_t HasAuxLayerTextureB() { return 0; }    // vt+0x8c
    virtual uint32_t SpecularEnabled() { return 0; }        // vt+0xd4
    virtual uint32_t RenderFarTexture() { return 0; }       // vt+0xd8

    // ---- the uniform fillers and the texture binding (C2.4 step 3). `dst` is the uniform's destination (the record's
    // +0x0c): one float4 per constant register, laid out as the PS3 constant registers (matrices as rows).
    virtual void FillMaterialColor(float* dst) {}           // vt+0x90 (ids 3, 0x1b)
    virtual void FillEnvMapCoefficients(float* dst) {}      // vt+0x94 (id 0x1c)
    virtual void FillUvTransform(float* dst) {}             // vt+0x98 (id 8)
    virtual void FillDualUvTransform(float* dst) {}         // vt+0x9c (id 0xb)
    virtual void FillSkinBoneMatrices(float* dst) {}        // vt+0xa0 (id 0x11)
    virtual void FillViewPomHeight(float* dst) {}           // vt+0xa4 (id 9)
    virtual void FillNormalParam(float* dst) {}             // vt+0xa8 (id 0x17)
    virtual void FillPomTextureShadow(float* dst) {}        // vt+0xac (id 0x18)
    virtual void FillAmbientColor(float* dst);              // vt+0xb0 (ids 2, 0x14) 0x000f52f0
    virtual void FillDirLightColors(float* dst) {}          // vt+0xb4 (ids 5, 0x13)
    virtual void FillSpecular(float* dst) {}                // vt+0xb8 (ids 10, 0x19)
    virtual void FillExtColor(float* dst) {}                // vt+0xbc (id 0x1a)
    virtual void FillWorldView(float* dst) {}               // vt+0xc0 (id 0xd)
    virtual void FillWorld(float* dst) {}                   // vt+0xc4 (id 0xe)
    virtual void FillAnim(float* dst) {}                    // vt+0xc8 (id 0x23)
    virtual const struct RwMatrix* GetWorldMatrix() { return nullptr; }  // vt+0xcc GetMeshPassWorldMatrix
    virtual void BindMaterialTextures() {}                  // vt+0xd0

    // 0x000f55a8 ShaderPassState_AdvanceToNextPass_maybe: the next pass's light counters (and the lights it takes).
    void AdvanceToNextPass();

    // 0x000edb10 / 0x000ede50 / 0x000edb90: take the slots a getter offers out of this pass's budget (+4 slot limit,
    // +0xd used) and remember the amount (+0xa dir, +0xc special, +0xb point lights).
    uint32_t AllocateDirLightSlots();      // MeshShaderPassState_AllocateSlots_vfC_To0A_maybe
    uint32_t AllocateSpecialLightSlots();  // MeshShaderPassState_AllocateSlots_vf10_To0C_maybe
    uint32_t AllocatePointLightSlots();    // MeshShaderPassState_AllocatePointLightSlots_maybe

    uint8_t m_slotLimit = 0;       // +0x04 shader slots per pass (MaterialMode_GetMaxShaderSlotCount_maybe)
    uint8_t m_passIndex = 0;       // +0x05
    uint8_t m_passCount = 1;       // +0x06
    uint8_t m_dirDone = 0;         // +0x07 directional lights taken by earlier passes
    uint8_t m_specialDone = 0;     // +0x08
    uint8_t m_pointDone = 0;       // +0x09
    uint8_t m_dirAllocated = 0;    // +0x0a
    uint8_t m_pointAllocated = 0;  // +0x0b
    uint8_t m_specialAllocated = 0;  // +0x0c
    uint8_t m_slotsUsed = 0;       // +0x0d
    uint8_t m_lightCount = 0;      // +0x0e
    uint8_t m_pointTouching = 0;   // +0x0f
    uint8_t m_specialActive = 0;   // +0x10
    RpAtomic* m_renderable = nullptr;  // +0x14
    RpMaterial* m_material = nullptr;  // +0x18
    uint8_t m_depthOfFieldFlag = 0;    // +0x1c
};

// 0x000efe08 ConstructMeshShaderPassState (vtable 0xb18d58): the pass state of `renderable` drawn with `material`.
class MeshShaderPassState : public ShaderPassState {
public:
    MeshShaderPassState(RpAtomic* renderable, RpMaterial* material);

    uint32_t GetMaterialShaderMode() override;      // 0x000eded0
    uint32_t DirLightsRemaining() override;         // 0x000edfe8 vfC
    uint32_t SpecialLightsRemaining() override;     // 0x000edde8 vf10
    uint32_t PointLightsRemaining() override;       // 0x000ef698 GetPointLightCount_maybe
    uint32_t SpotLights() override { return 0; }    // 0x000edc10 vf18
    uint32_t SkinWeightsUsed() override;            // 0x000edc18 vf1C
    uint32_t MaxSkinWeights() override;             // 0x000ee138
    uint32_t TexCoordSets() override;               // 0x000edc70 vf24
    uint32_t FogFlag() override;                    // 0x000edcd8 vf28
    uint32_t ComputePointLights() override;         // 0x000ef790
    uint32_t SpecialLightActive() override;         // 0x000ef448 vf30
    uint32_t IsFogEnabled() override;               // 0x000eeba0
    uint32_t ModulateVertexColorFirst() override;   // 0x000ee5c0 vf3C
    uint32_t UseNormalInfluence() override;         // 0x000ef860 vf40
    uint32_t VertexColor() override;                // 0x000edd30 vf44
    uint32_t ModulateMaterial() override { return 1; }  // 0x000edb08 vf48
    uint32_t ShadowEnabled() override;              // 0x000eef48 vf54
    uint32_t RenderDepthOfField() override;         // 0x009a5850 vf58
    uint32_t DualBlendMode() override;              // 0x000ee520
    uint32_t UvTransform() override;                // 0x000ee320 vf7C
    uint32_t HasAuxLayerTexture() override;         // 0x000ee4c8 vf80
    uint32_t HasSecondaryEffectTexture() override;  // 0x000ee470 vf84
    uint32_t HasAuxTexture8C() override;            // 0x000ee418 vf88
    uint32_t HasAuxLayerTextureB() override;        // 0x000ee3c0 vf8C
    uint32_t SpecularEnabled() override;            // 0x000ef528 vfD4
    uint32_t RenderFarTexture() override;           // 0x000eee80 vfD8

    void FillMaterialColor(float* dst) override;        // 0x000edd50
    void FillEnvMapCoefficients(float* dst) override;   // 0x000eeac0
    void FillUvTransform(float* dst) override;          // 0x000eecb0
    void FillDualUvTransform(float* dst) override;      // 0x000eec20
    void FillViewPomHeight(float* dst) override;        // 0x000eed48
    void FillNormalParam(float* dst) override;          // 0x000ef898
    void FillPomTextureShadow(float* dst) override;     // 0x000ee880
    void FillDirLightColors(float* dst) override;       // 0x000ee7d8
    void FillSpecular(float* dst) override;             // 0x000ee730
    void FillExtColor(float* dst) override;             // 0x000efa78
    void FillWorldView(float* dst) override;            // 0x000ef5e0
    void FillWorld(float* dst) override;                // 0x000ee968
    void FillAnim(float* dst) override;                 // 0x000ee5f8
    void FillSkinBoneMatrices(float* dst) override;     // 0x000eea50 FillSkinBoneMatrixPaletteUniform
    const struct RwMatrix* GetWorldMatrix() override;   // 0x000ee188
    void BindMaterialTextures() override;               // 0x000eefe8

    // 0x000efc08 MeshShaderPassState_ComputePassCount_maybe
    uint32_t ComputePassCount();

private:
    CMaterial* KMaterial() const;  // the K material plugin of the RpMaterial (null without one)
};

// 0x000f7eb8 MaterialMode_GetMaxShaderSlotCount_maybe(mode, postOrFar, specular, textured)
uint32_t MaterialMode_GetMaxShaderSlotCount(int32_t mode, int32_t postOrFar, int32_t specular, int32_t textured);

// 0x00c68314: the world matrix the passes use instead of the atomic's frame (the clones' and the hero's matrices);
// null: the frame's.
void MeshShaderPass_SetWorldMatrixOverride(const struct RwMatrix* matrix);

// 0x000f7008 FillShaderUniformFromPassState (ShaderUniform.cpp): the value of the uniform with this ShaderUniformId
// (ShaderVariantKey.h) into `dst` (one float4 per constant register).
void FillShaderUniformFromPassState(ShaderPassState* pass, int32_t id, float* dst);
// 0x000598c0 BindTextureOnUnit_maybe: the texture (with the sampler state its filter / addressing word gives) on a texture unit;
// null clears the unit.
void BindTextureOnUnit(struct RwTexture* texture, int unit);
// 0x000f69c8 MeshShaderPassState_BindFallbackTextureUnit7_maybe: the graphic module's blank texture (+0x20) on unit 7 (no fog).
void BindFallbackTextureUnit7();
// 0x000f6a00 ShaderPassState_FillDirLightColorUniforms_maybe (ShaderUniform.cpp): the colours of the light rig's distinct lights.
void FillDirLightColorUniforms(const ShaderPassState* pass, float* dst);
// 0x000f5fd0 ShaderPassState_ApplyUniformEnableFlags0And1_maybe: the value of boolean constant `slot` (0: vertex
// modulation, always off; 1: vertex colour first).
uint32_t ShaderPassState_EnableFlag(ShaderPassState* pass, int slot);
