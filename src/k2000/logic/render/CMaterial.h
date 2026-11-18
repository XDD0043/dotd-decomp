// CMaterial.h - the engine's material over an RpMaterial (key 0x2bcc, vtable 0xb17af0, size 0xb0).
// Original unit: CMaterial.cpp (0xbb3c0-0xc0370). XXL2: K/KModules/KGL/Material/CMaterial.h
// (IKSerializable: m_pRpMaterial, m_baProperties, m_ui16UpdateFrameCounter, m_FXParameters; statics
// m_sui32RpToKMaterialPlugingOffset, m_sapFnMaterialUpdateFuncs). DotD has more members after them.
//
// m_baProperties bits (from CMaterial_Load / CMaterial_SetEffectType_maybe):
//   0x00000078 the material mode, (props >> 3) & 0xf (0..14)
//   0x00000100 the FX effect slots are in the file (modes 5, 6, 12, 14)
//   0x00000200 a CMaterialEffectData follows (+0x9c)
//   0x00000400, 0x00000800, 0x00004000: one file byte each, inserted at bits 10, 11, 14
//   0x00008000 8 raw bytes at +0x2c follow
//   bits 16 + 7 * slot: the slot's 3-bit effect type; bits 19..22 + 7 * slot: its flags
#pragma once
#include <cstdint>

#include <cstring>

#include "Renderware/rpworld/RpGeometry.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CMaterial;
class IKFile;
class IKTime;
struct CMatrix34;
struct RwMatrix;
struct RwTexture;

// The 0x2c-byte block CMaterial_Load allocates for modes 11..14 (+0x84; Ghidra "AuxLayer": the
// CMaterial_Get/SetAuxLayer* accessors 0xbb6a0..0xbb760). Not constructed: Load zeroes it.
struct CMaterialAuxLayer {
    RwTexture* m_pTexture;   // +0x00 CMaterial_GetAuxLayerTexture_maybe
    uint8_t m_ui8Byte4;      // +0x04 read raw (mode 11)
    uint8_t m_ui8Byte5;      // +0x05 read raw (mode 11)
    uint8_t m_ui8Byte6;      // +0x06 read raw (mode 11)
    uint8_t m_ui8Unk7;       // +0x07 zeroed with the word
    uint32_t m_ui32Param8;   // +0x08 mode 11
    uint32_t m_ui32ParamC;   // +0x0c mode 11
    float m_afUnk10[7];      // +0x10 mode 14 (seven floats); +0x28 defaults to 1.0
};

// The block CMaterial_Load allocates for property bit 0x200 (+0x9c; OperatorNew(0x1c), not constructed).
// Read by 0x000c3b28 CMaterialEffectData_Load_maybe (unit CKSurfaceParticlesRendable.cpp).
struct CMaterialEffectData {
    CMaterial* m_pOwner;       // +0x00 the material (stored before and after the type-0 reads)
    IKSerializable* m_pRef4;   // +0x04 a handle
    IKSerializable* m_pRef8;   // +0x08 a handle
    uint32_t m_unkC;           // +0x0c
    uint32_t m_unk10;          // +0x10
    uint32_t m_unk14;          // +0x14
    uint32_t m_unk18;          // +0x18
};
void CMaterialEffectData_Load(CMaterialEffectData* data, IKFile* file, int32_t type, CMaterial* owner);  // 0x000c3b28
// 0x000c3680 CMaterialEffectData_LevelReset_maybe (unit CKSurfaceParticlesRendable.cpp by address; CMaterial's
// RecursiveRegistration): the two handles' RecursiveRegistration (vt+0x24) when set.
void CMaterialEffectData_RecursiveRegistration(CMaterialEffectData* data, int32_t type);

// The static object at 0x00c5d280 (vtable 0xb17b48: destructors only), set up by 0x000bc318
// RegisterCMaterialClass to {vtable, 0, 0}; modes 7 and 8 load it. Its Load is 0x0009e018
// CMaterialMode7or8SharedState_Load_maybe (unit CLightManager.cpp).
struct CMaterialSharedState {
    virtual ~CMaterialSharedState() {}   // 0x009a11a8 / 0x009a1178
    IKSerializable* m_pRef;              // +0x04 a handle
    uint32_t m_unk8;                     // +0x08
    int32_t Load(IKFile* file, int32_t type);  // 0x0009e018
    // 0x0009e100 CMaterialMode7or8SharedState_Release_maybe (CMaterial_Destroy, modes 7 and 8): the count
    // decremented; at 0 the reference is cleared.
    void Release();
};
DOTD_ASSERT_SIZE(CMaterialSharedState, 0xc);

// One FX effect slot (CMaterial_SetEffectType_maybe sets the defaults per effect type; the Load's jump
// table at 0xbf4f8 reads it). Stride 0x28; the slots start at +0x34 and +0x5c. Offsets below are into
// the slot; the four bytes after each slot (+0x58, +0x80) are not touched.
struct CMaterialFXEffect {
    union {
        struct {                        // effect types 0 and 1 (type 0: scroll, MatFXUVAnim_UpdateMaterial_maybe 0xbd228)
            // +0x00 / +0x04 the U / V scroll speed (floats, per second), +0x08 / +0x0c the UV offset (type 0's
            // initial translation, PostLoad)
            uint32_t m_aui32Words[4];
            uint8_t m_ui8Byte10;        // +0x10 raw; U: the number of steps of the limited scroll (properties bit 21 + 7 * slot)
            uint8_t m_ui8Byte11;        // +0x11 raw; V: the same (properties bit 22 + 7 * slot)
            uint8_t m_ui8StepU;         // +0x12 runtime: U's current step (0 .. m_ui8Byte10)
            uint8_t m_ui8StepV;         // +0x13 runtime: V's current step
            uint8_t m_ui8WaitingU;      // +0x14 runtime: U is waiting at its step (1) or moving (0)
            uint8_t m_ui8WaitingV;      // +0x15 runtime: V, the same
            uint8_t m_aui8Unk16[2];
            uint32_t m_ui32Word18;      // +0x18 raw; U: the wait at each step, seconds (a float)
            float m_fWaitLeftU;         // +0x1c runtime: U's remaining wait, seconds
            uint32_t m_ui32Word20;      // +0x20 raw; V: the wait at each step (a float)
        } k01;
        struct {                        // effect type 2
            uint32_t m_aui32Words[2];   // +0x00 default 0
            uint16_t m_ui16Half8;       // +0x08 default 1 (lhbrx)
            uint16_t m_ui16HalfA;       // +0x0a default 1 (lhbrx)
            float m_fFloatC;            // +0x0c default 1.0
            float m_fFloat10;           // +0x10 default 1.0
            float m_fAccumU;            // +0x14 default 0; runtime: the accumulated U scroll (flip-book, bit 19 + 7 * slot)
            float m_fAccumV;            // +0x18 default 0; runtime: the accumulated V scroll (bit 20 + 7 * slot)
            uint32_t m_unk1c;
            uint32_t m_unk20;
        } k2;
        struct {                        // effect type 3
            float m_afFloats[2];        // +0x00 defaults 0.1, 1.0
            uint32_t m_unk8;            // default 0
            uint32_t m_unkC;            // default 0
            uint32_t m_unk10[5];
        } k3;
        struct {                        // effect type 4
            float m_afFloats[2];        // +0x00 defaults 0.1, 1.0
            uint32_t m_unk8;            // default 0
            uint32_t m_unkC;            // default 0
            uint32_t m_unk10;
            uint8_t m_ui8Byte14;        // +0x14 default 1, read raw
            uint8_t m_aui8Unk15[3];
            float m_fFloat18;           // +0x18 default 0.1
            uint32_t m_unk1c;
            float m_fFloat20;           // +0x20 default 1.0
        } k4;
    };
    float m_fWaitLeftV;                  // +0x24 the 4 bytes up to the next slot; effect type 0 keeps V's remaining wait
                                        //       here (a float)
};
DOTD_ASSERT_SIZE(CMaterialFXEffect, 0x28);

// XXL2 CMaterial::SMaterialFXParameters (an anonymous union there); DotD's spans +0x14..+0x84.
struct CMaterialFXParameters {
    uint32_t m_ui32Param0;          // +0x14 modes 7 and 8 (XXL2: m_FXParameters+0, read for modes 7, 8)
    uint32_t m_unk18;               // +0x18 not set by the constructor or Load
    uint32_t m_ui32Param8;          // +0x1c mode 8 reads it; modes 8/10/12/14 then store the texture's
                                    //       coefficient (a float) here
    RwTexture* m_pTexture;          // +0x20 mode 8, then modes 8/10/12/14 (XXL2: m_FXParameters+8)
    uint32_t m_unk24;               // +0x24 constructor 0
    uint32_t m_unk28;               // +0x28 constructor 0
    uint8_t m_aui8Raw2c[8];         // +0x2c property 0x8000: the file's first byte goes to +0x33, the
                                    //       next seven to +0x2c..+0x32 (raw)
    CMaterialFXEffect m_aEffects[2];  // +0x34, +0x5c
};
DOTD_ASSERT_SIZE(CMaterialFXParameters, 0x70);

class CMaterial : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xaf)
    DOTD_DECLARE_FACTORIES(CMaterial)

    // A mode-transition handler (XXL2 CMaterial::KpFnMaterialUpdate is the update table's type).
    using KpFnModeTransition = void (CMaterial::*)();

    CMaterial();                                         // 0x000bbe40 CMaterial_Construct
    ~CMaterial() override {}                             // 0x000bfda0 / 0x000bfd60 CMaterial_Destructor / _DeletingDestructor: the vtables only
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2bcc || key == 0xc; }  // 0x9a11b8
    // vt+0x10 0x000be260 CMaterial_Destroy (the level unload): the effect data released, the shared state of
    // modes 7 and 8 released, the RenderWare material and the first-pass matrix destroyed, the effect block deleted.
    void Destroy() override;
    // 0x000bdf78 CMaterial_ReleaseEffectData_maybe: per mode, the UV transform matrices (5, 6) and the textures
    // (8, 10..14) released; the aux layer (+0x84) deleted.
    void ReleaseEffectData();
    int32_t Load(IKFile* file, int32_t type) override;   // vt+0x2c 0x000bec50 CMaterial_Load
    // 0x000bc238 SetMaterialTexture_maybe: the texture of the referenced RenderWare material becomes `texture`
    // when it is not already (RpMaterialSetTexture).
    void SetTexture(RwTexture* texture);

    // The accessors the shader pass reads (C2.4 step 3; the material mode is bits 3-6 of m_baProperties).
    // 0x000bbce0 CMaterial_GetEnvMapTexture: modes 2 and 3 ask the MatFX env map effect, the others the FX texture.
    RwTexture* GetEnvMapTexture();
    // 0x000bc920 CMaterial_HasSecondaryEffectTexture_maybe (same rule, as a flag)
    uint32_t HasSecondaryEffectTexture();
    // 0x000bbf70 CMaterial_GetEnvMapCoefficient: modes 2 and 3 the MatFX env coefficient, the others the FX word as a float.
    float GetEnvMapCoefficient();
    // 0x000bb9f8 CMaterial_GetUVTransformMatrix_maybe: the MatFX base UV matrix for modes 1..6, else the first pass matrix.
    CMatrix34* GetUVTransformMatrix();
    // 0x000bb960 CMaterial_GetDualUVTransformMatrix_maybe: the MatFX dual UV matrix.
    CMatrix34* GetDualUVTransformMatrix();
    // 0x000bb6a0 CMaterial_GetAuxLayerTexture_maybe / 0x000bb7f0 CMaterial_HasAuxLayerTexture_maybe
    RwTexture* GetAuxLayerTexture() { return m_pAuxLayer->m_pTexture; }
    bool HasAuxLayerTexture() { return m_pAuxLayer != nullptr && m_pAuxLayer->m_pTexture != nullptr; }
    // 0x000bc2a0 CMaterial_HasAuxTexture88OrLayerTexture_maybe
    bool HasAuxTexture88OrLayerTexture() { return m_pAuxTexture88 != nullptr || HasAuxLayerTexture(); }
    int32_t GetSerializationFlags() override { return 2; }  // vt+0x34 0x9a1170
    // vt+0x30 0x000be348 CMaterial_PostLoad (C2.4 step 4): the clone material, the UV transform matrices of modes 5 / 6,
    // the aux textures' addressing and the first-pass UV matrices.
    int32_t PostLoad(int32_t type) override;

    // 0x000be8a8 CMaterial_SetEffectType_maybe: puts the effect type into slot's bits of m_baProperties,
    // resets the slot's parameters, and with reset != 0 also resets its UV transform matrix.
    void SetEffectType(int32_t slot, uint32_t effectType, int32_t reset);

    // 0x000bd228 MatFXUVAnim_UpdateMaterial_maybe: the per-frame UV animation of the materials with property bit 8
    // (shader modes 5, 6, 12, 14; the table 0x00c4b0cc, called by CGeometry::EnqueueVisible once per frame). Only
    // while the clock is running. Each effect slot (one in modes 5, 11, 12, 13, 14, else two; layer 0 writes the
    // base UV matrix in modes 1..6 or the first-pass matrix, layer 1 the dual matrix) animates by its effect type:
    // 0 scroll, 1 rotate, 2 flip-book, 3 shear wobble, 4 circular wobble (see the .cpp).
    void UpdateUVAnimation(IKTime* frameClock);

    // 0x000bfde8 CMaterial_ConstructBase_maybe: (re)fills the static mode-transition table; every
    // constructor calls it. 0x000bb780 CMaterial_SetModeTransitionHandler_maybe stores one entry.
    static void RegisterModeTransitions();
    static void SetModeTransitionHandler(KpFnModeTransition handler, int32_t from, int32_t to);
    // 0x000bb7b8 CMaterial_GetModeTransitionHandler_maybe: the table's [from][to] entry.
    static KpFnModeTransition GetModeTransitionHandler(int32_t from, int32_t to) { return s_apfnModeTransitions[from][to]; }
    // 0x000c0288 CMaterial_InvokeModeTransitionHandler_maybe: the handler from the current mode to `to`, when there is one;
    // returns `to`. No code calls it (no bl, no reference to its descriptor), so the handlers never run.
    int32_t InvokeModeTransitionHandler(int32_t to);
    // The handlers (the table's entries; they run only through InvokeModeTransitionHandler). Each acts with property bit
    // 0x2000 set only.
    // 0x000bfef0 CMaterial_ModeTransition_ToMode12_maybe: the mode becomes 12.
    void ModeTransitionToMode12();
    // 0x000bff20 CMaterial_RestoreEnvMapEffect_maybe: the env map's coefficient, texture, FB alpha and frame read, the
    // mode set to 2 and the MatFX effects to 2 (env map), the four written back.
    void RestoreEnvMapEffect();
    // 0x000c0038 CMaterial_ClearAuxTexturesAndRestoreEnvMap_maybe: the aux layer and +0x8c textures cleared, then as
    // RestoreEnvMapEffect. Its descriptor 0xb4cb58 sits in the handler run, but CMaterial_ConstructBase_maybe never
    // registers it (no reference to the descriptor).
    void ClearAuxTexturesAndRestoreEnvMap();
    // 0x000c0170 CMaterial_ModeTransition_ToMode0ClearEnvMap_maybe: the aux layer, env map and +0x8c textures cleared,
    // the specular reset (0.0), the mode bits and properties 0x100 / 0x8000 cleared.
    void ModeTransitionToMode0ClearEnvMap();
    // 0x000c0210 CMaterial_ModeTransition_ToMode0_maybe: the aux layer's texture cleared, the specular reset (0.0), the
    // mode bits cleared (mode 0).
    void ModeTransitionToMode0();

    // The RenderWare material's surface properties (+0x04 -> +0x0c ambient, +0x10 specular, +0x14 diffuse).
    float GetSpecular() const { return m_pRpMaterial->surfaceProps.specular; }  // 0x000bb3c0 CMaterial_GetSpecular_maybe
    float GetAmbient() const { return m_pRpMaterial->surfaceProps.ambient; }    // 0x000bb3d0 CMaterial_GetAmbient_maybe
    float GetDiffuse() const { return m_pRpMaterial->surfaceProps.diffuse; }    // 0x000bb3e0 CMaterial_GetDiffuse_maybe
    void SetAmbient(float value) { m_pRpMaterial->surfaceProps.ambient = value; }  // 0x000bb438 CMaterial_SetAmbient_maybe
    void SetDiffuse(float value) { m_pRpMaterial->surfaceProps.diffuse = value; }  // 0x000bb448 CMaterial_SetDiffuse_maybe
    // 0x000bb3f0 CMaterial_SetSpecularForShaderModes_maybe: `value` in modes 11..14, else 0.
    void SetSpecularForShaderModes(float value);
    // 0x000bb458 CMaterial_GetBlendModeName_maybe / 0x000bb4c0 CMaterial_GetBlendFactorName_maybe (the editor's labels).
    static const char* GetBlendModeName(int32_t mode);
    static const char* GetBlendFactorName(int32_t factor);
    static bool IsMode10To14(uint32_t mode) { return mode - 10u < 5u; }  // 0x000bb5c0 CMaterial_IsMode10To14_maybe
    // 0x000bfdd8 MaterialExt_GetShaderMode_maybe: the material mode (bits 3-6 of the properties).
    uint32_t GetShaderMode() const { return (m_baProperties >> 3) & 0xf; }
    // The aux layer (+0x84, no null test) and the other aux fields.
    void SetAuxLayerParam8(float value) { std::memcpy(&m_pAuxLayer->m_ui32Param8, &value, 4); }  // 0x000bb6b0
    float GetAuxLayerParam8() const {  // 0x000bb6c0
        float v;
        std::memcpy(&v, &m_pAuxLayer->m_ui32Param8, 4);
        return v;
    }
    void SetAuxLayerByte6(uint8_t value) { m_pAuxLayer->m_ui8Byte6 = value; }  // 0x000bb6d0
    uint8_t GetAuxLayerByte6() const { return m_pAuxLayer->m_ui8Byte6; }      // 0x000bb6e0
    void SetAuxLayerParamC(float value) { std::memcpy(&m_pAuxLayer->m_ui32ParamC, &value, 4); }  // 0x000bb6f0
    float GetAuxLayerParamC() const {  // 0x000bb700
        float v;
        std::memcpy(&v, &m_pAuxLayer->m_ui32ParamC, 4);
        return v;
    }
    void SetAuxFloat94(float value) { m_fAuxFloat94 = value; }  // 0x000bb710 CMaterial_SetAuxFloat94_maybe
    float GetAuxFloat94() const { return m_fAuxFloat94; }       // 0x000bb718 CMaterial_GetAuxFloat94_maybe
    void SetExtColor(const uint8_t* color) { std::memcpy(m_cExtColor, color, 4); }  // 0x000bb720 CMaterial_SetExtColor_maybe
    void GetExtColor(uint8_t* color) const { std::memcpy(color, m_cExtColor, 4); }  // 0x000bc140 CMaterial_GetExtColor_maybe
    void SetAuxLayerByte5(uint8_t value) { m_pAuxLayer->m_ui8Byte5 = value; }  // 0x000bb730
    void SetAuxLayerByte4(uint8_t value) { m_pAuxLayer->m_ui8Byte4 = value; }  // 0x000bb740
    uint8_t GetAuxLayerByte4() const { return m_pAuxLayer->m_ui8Byte4; }      // 0x000bb750
    uint8_t GetAuxLayerByte5() const { return m_pAuxLayer->m_ui8Byte5; }      // 0x000bb760
    RwTexture* GetAuxTexture88() const { return m_pAuxTexture88; }  // 0x000bb770 CMaterial_GetAuxTexture88_maybe
    RwTexture* GetAuxTexture8C() const { return m_pAuxTexture8C; }  // 0x000bb778 CMaterial_GetAuxTexture8C_maybe
    bool HasAuxTexture8C() const { return m_pAuxTexture8C != nullptr; }  // 0x000bc150 CMaterial_HasAuxTexture8C_maybe
    // 0x000bc200 CMaterial_HasBaseTexture_maybe: the RenderWare material's texture, unless property 0x1000.
    bool HasBaseTexture() const { return (m_baProperties & 0x1000u) == 0 && m_pRpMaterial->texture != nullptr; }
    // 0x000bb910 CMaterial_SetUVTransformMatrices / 0x000bb938 CMaterial_GetUVTransformMatrices (the MatFX ones).
    void SetUVTransformMatrices(RwMatrix* base, RwMatrix* dual);
    void GetUVTransformMatrices(RwMatrix** base, RwMatrix** dual) const;
    // 0x000bb9a0 CMaterial_GetUVTransformMatrixByIndex_maybe: the MatFX base (0) or dual (1) matrix.
    RwMatrix* GetUVTransformMatrixByIndex(int32_t index) const;
    // 0x000bba68 CMaterial_GetDualBlendMode_maybe: 1 for (5, 6), 2 for (5, 2), else 0.
    uint32_t GetDualBlendMode() const;
    // 0x000bbc30 CMaterial_SetEnvMapCoefficient: modes 2 and 3 the MatFX env coefficient, the others the FX word (+0x1c).
    void SetEnvMapCoefficient(float coefficient);
    // 0x000bbc88 CMaterial_SetEnvMapFBAlpha: modes 2 and 3 only.
    void SetEnvMapFBAlpha(int32_t useFBAlpha);
    // C2.8 port-rest R07: the MatFX accessors with no caller in the EBOOT (no bl, no descriptor reference) and the ones
    // only the mode transitions call (the RpMatFX side: Renderware/rpmatfx/RpMatFX.cpp).
    // 0x000bbae0 CMaterial_SetDualBlendMode_maybe: the dual blend modes (5, 2) for mode 2, else (5, 6).
    void SetDualBlendMode(int32_t mode);
    float GetBumpMapCoefficient();                  // 0x000bbb28 CMaterial_GetBumpMapCoefficient
    void SetBumpMapCoefficient(float coefficient);  // 0x000bbb50 CMaterial_SetBumpMapCoefficient
    void* GetBumpMapFrame();                        // 0x000bbb78 CMaterial_GetBumpMapFrame
    void SetBumpMapFrame(void* frame);              // 0x000bbba8 CMaterial_SetBumpMapFrame
    RwTexture* GetBumpMapTexture();                 // 0x000bbbd0 CMaterial_GetBumpMapTexture: modes 1 and 3, else null
    // 0x000bbfc8 CMaterial_GetEnvMapFBAlpha: modes 2 and 3 the MatFX flag as 0 / 1, else 0.
    int32_t GetEnvMapFBAlpha();
    void* GetEnvMapFrame();                         // 0x000bc030 CMaterial_GetEnvMapFrame: modes 2 and 3, else null
    void SetEnvMapFrame(void* frame);               // 0x000bc090 CMaterial_SetEnvMapFrame: modes 2 and 3 only
    // 0x000bc6a8 CMaterial_SetupBumpMap_maybe: unless `texture` is the current bump map (modes 1 and 3), the MatFX setup.
    void SetupBumpMap(RwTexture* texture, void* frame, float coefficient);
    // 0x000bc748 CMaterial_SetBumpMapTexture: unless it is the current bump map (modes 1 and 3), the MatFX setter.
    void SetBumpMapTexture(RwTexture* texture);
    // 0x000bca40 CMaterial_SetEnvMapTexture: unless it is the current env map texture, mode 2 the MatFX setter, the
    // others the FX texture (+0x20: the old one released, the new one's count raised).
    void SetEnvMapTexture(RwTexture* texture);
    // 0x000bcb18 CMaterial_SetupEnvMap_maybe: unless it is the current env map texture, mode 2 the MatFX setup, the
    // others the FX coefficient (+0x1c) and texture (+0x20, the old one not released, the new one's count raised).
    void SetupEnvMap(RwTexture* texture, void* frame, uint8_t useFBAlpha, float coefficient);
    // 0x000bd038 CMaterial_SetSecondaryEffectTexture_maybe: modes 4 / 6 the MatFX dual texture, 2 / 3 / 8 / 10 / 12 / 14
    // as SetEnvMapTexture.
    void SetSecondaryEffectTexture(RwTexture* texture);
    // 0x000bbd38 CMaterial_ResetEffectData_maybe: the FX parameters +0x14..+0x33 cleared, the aux layer (when there is one)
    // zeroed, the aux textures +0x88 / +0x8c cleared (no release).
    void ResetEffectData();
    // The aux textures' setters: a different texture replaces the old one, which is released (RwTextureDestroy) only
    // when the new one is null.
    void SetAuxTexture88(RwTexture* texture);         // 0x000bc560 CMaterial_SetAuxTexture88_maybe
    void SetAuxTexture8C(RwTexture* texture);         // 0x000bc640 CMaterial_SetAuxTexture8C_maybe
    void SetAuxLayerTexture(RwTexture* texture);      // 0x000bc5c8 CMaterial_SetAuxLayerTexture_maybe (no layer null test)
    // 0x000bc3f0 CMaterial_SetAuxLayerTextureWithDefaults_maybe: as SetAuxLayerTexture, then the layer's and the
    // material's defaults (byte 6 = 8, +0x08 0.1, +0x0c 0.3, +0x94 20.0, the white colour, byte 5 = 100, byte 4 = 8).
    void SetAuxLayerTextureWithDefaults(RwTexture* texture);
    // 0x000bc7c8 CMaterial_ApplyAuxTextureAddressing_maybe: +0x8c clamped (0x1100), +0x88 and the aux layer's texture
    // as CMaterial_PostLoad's addressing (InheritAddressing).
    void ApplyAuxTextureAddressing();
    // 0x000bc998 CMaterial_GetSecondaryEffectTexture_maybe: modes 4 / 6 the MatFX dual texture, 2 / 3 the env map
    // texture, 8 / 10 / 12 / 14 the FX texture (+0x20), else null.
    RwTexture* GetSecondaryEffectTexture();
    // 0x000bce38 CMaterial_ResetUVTransformMatrix_maybe: the slot's UV matrix back to the identity; effect type 0 takes
    // the slot's +0x08 / +0x0c as the translation (no null test).
    void ResetUVTransformMatrix(int32_t slot);
    // vt+0x24 0x000bbda8 CMaterial_RecursiveRegistration: the effect block's (+0x9c) when there is one.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x1c 0x000bc298 CMaterial_MessageProc: 1 (the default).
    // 0x000bdec8 MatFXUVAnim_SetBaseUVTransform_maybe (0xbc4b0 the same code): the MatFX base matrix becomes `matrix`,
    // the dual kept in mode 6 (else null).
    void SetBaseUVTransform(RwMatrix* matrix);
    // 0x000bd168 MatFXUVAnim_SetDualUVTransform_maybe (0xbcf78 the same code): the MatFX dual matrix becomes `matrix`,
    // the base kept in modes 1..6 (else the first-pass matrix).
    void SetDualUVTransform(RwMatrix* matrix);

    RpMaterial* m_pRpMaterial;          // +0x04 the referenced geometry's first material, or (with the
                                        //       clone flag) taken from the CCloneManager at PostLoad
    uint32_t m_baProperties;            // +0x08 CBitArray (bits above)
    uint32_t m_unk0c;                   // +0x0c constructor 0
    uint16_t m_ui16UpdateFrameCounter;  // +0x10 constructor 0 (XXL2 constructor sets it the same way)
    uint16_t m_ui16Unk12;               // +0x12 not set by the constructor or Load
    CMaterialFXParameters m_FXParameters;  // +0x14
    CMaterialAuxLayer* m_pAuxLayer;     // +0x84 modes 11..14
    RwTexture* m_pAuxTexture88;         // +0x88 modes 10, 13 (CMaterial_GetAuxTexture88_maybe)
    RwTexture* m_pAuxTexture8C;         // +0x8c mode 12 (CMaterial_GetAuxTexture8C_maybe)
    uint32_t m_unk90;                   // +0x90 mode 12
    float m_fAuxFloat94;                // +0x94 constructor 50.0 (CMaterial_Set/GetAuxFloat94_maybe)
    uint8_t m_cExtColor[4];             // +0x98 CColor, read raw; constructor copies 0x00c50dfc (white)
                                        //       (CMaterial_Set/GetExtColor_maybe)
    CMaterialEffectData* m_pEffectData; // +0x9c property 0x200
    CMatrix34* m_pFirstPassTransformMatrix;  // +0xa0 RwMatrixCreate in the type-0 Load; the slot-0 UV
                                        //       transform of modes 0 and 7..14 (XXL2
                                        //       SetInternalFirstPassTransformMatrix, _maybe)
    uint32_t m_unka4;                   // +0xa4 not set by the constructor or Load
    uint32_t m_unka8;                   // +0xa8 not set by the constructor or Load
    int32_t m_iCloneTeamElement;        // +0xac -1, or the CCloneManager team element whose first
                                        //       material PostLoad takes (CCloneManager_GetTeamElementFirstMaterial)

    static KpFnModeTransition s_apfnModeTransitions[15][15];  // 0x00c5cb74 [from][to]
    static CMaterialSharedState s_sharedState;                // 0x00c5d280
};
DOTD_ASSERT_SIZE(CMaterial, 0xb0);
DOTD_ASSERT_OFFSET(CMaterial, m_pRpMaterial, 0x04);
DOTD_ASSERT_OFFSET(CMaterial, m_baProperties, 0x08);
DOTD_ASSERT_OFFSET(CMaterial, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CMaterial, m_ui16UpdateFrameCounter, 0x10);
DOTD_ASSERT_OFFSET(CMaterial, m_FXParameters, 0x14);
DOTD_ASSERT_OFFSET(CMaterial, m_FXParameters.m_ui32Param8, 0x1c);
DOTD_ASSERT_OFFSET(CMaterial, m_FXParameters.m_pTexture, 0x20);
DOTD_ASSERT_OFFSET(CMaterial, m_FXParameters.m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CMaterial, m_FXParameters.m_aui8Raw2c, 0x2c);
DOTD_ASSERT_OFFSET(CMaterial, m_FXParameters.m_aEffects, 0x34);
DOTD_ASSERT_OFFSET(CMaterial, m_pAuxLayer, 0x84);
DOTD_ASSERT_OFFSET(CMaterial, m_pAuxTexture88, 0x88);
DOTD_ASSERT_OFFSET(CMaterial, m_pAuxTexture8C, 0x8c);
DOTD_ASSERT_OFFSET(CMaterial, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CMaterial, m_fAuxFloat94, 0x94);
DOTD_ASSERT_OFFSET(CMaterial, m_cExtColor, 0x98);
DOTD_ASSERT_OFFSET(CMaterial, m_pEffectData, 0x9c);
DOTD_ASSERT_OFFSET(CMaterial, m_pFirstPassTransformMatrix, 0xa0);
DOTD_ASSERT_OFFSET(CMaterial, m_iCloneTeamElement, 0xac);
