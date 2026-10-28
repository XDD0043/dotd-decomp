// CMaterial.cpp - reconstructed original translation unit 0xbb3c0-0xc0370 (GAME_TOC1, main_toc1), 111 functions, 103 live.
// Primary class: CMaterial  key 0x2bcc  category Logic  size 0xb0  vtable 0xb17af0
// Other owners: MatFXUVAnim (5), MaterialExtPlugin (3), CGeometry (1), Graphic (1), SetMaterialTexture (1), MaterialExt (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xbb3c0  CMaterial_GetSpecular_maybe
//   [ ] 0xbb3d0  CMaterial_GetAmbient_maybe
//   [ ] 0xbb3e0  CMaterial_GetDiffuse_maybe
//   [ ] 0xbb3f0  CMaterial_SetSpecularForShaderModes_maybe
//   [ ] 0xbb438  CMaterial_SetAmbient_maybe
//   [ ] 0xbb448  CMaterial_SetDiffuse_maybe
//   [ ] 0xbb458  CMaterial_GetBlendModeName_maybe
//   [ ] 0xbb4c0  CMaterial_GetBlendFactorName_maybe
//   [ ] 0xbb580  FUN_000bb580  [dead]
//   [ ] 0xbb5c0  CMaterial_IsMode10To14_maybe
//   [ ] 0xbb5e0  KStub_Return0_bb5e0  [dead]
//   [ ] 0xbb5e8  MaterialExtPlugin_Destructor
//   [ ] 0xbb610  CMaterial_Save
//   [ ] 0xbb618  CMaterial_InheritTextureAddressing_maybe
//   [ ] 0xbb690  FUN_000bb690  [dead]
//   [ ] 0xbb698  FUN_000bb698  [dead]
//   [x] 0xbb6a0  CMaterial_GetAuxLayerTexture_maybe
//   [ ] 0xbb6b0  CMaterial_SetAuxLayerParam8_maybe
//   [ ] 0xbb6c0  CMaterial_GetAuxLayerParam8_maybe
//   [ ] 0xbb6d0  CMaterial_SetAuxLayerByte6_maybe
//   [ ] 0xbb6e0  CMaterial_GetAuxLayerByte6_maybe
//   [ ] 0xbb6f0  CMaterial_SetAuxLayerParamC_maybe
//   [ ] 0xbb700  CMaterial_GetAuxLayerParamC_maybe
//   [ ] 0xbb710  CMaterial_SetAuxFloat94_maybe
//   [ ] 0xbb718  CMaterial_GetAuxFloat94_maybe
//   [ ] 0xbb720  CMaterial_SetExtColor_maybe
//   [ ] 0xbb730  CMaterial_SetAuxLayerByte5_maybe
//   [ ] 0xbb740  CMaterial_SetAuxLayerByte4_maybe
//   [ ] 0xbb750  CMaterial_GetAuxLayerByte4_maybe
//   [ ] 0xbb760  CMaterial_GetAuxLayerByte5_maybe
//   [ ] 0xbb770  CMaterial_GetAuxTexture88_maybe
//   [ ] 0xbb778  CMaterial_GetAuxTexture8C_maybe
//   [x] 0xbb780  CMaterial_SetModeTransitionHandler_maybe
//   [ ] 0xbb7b8  CMaterial_GetModeTransitionHandler_maybe
//   [x] 0xbb7f0  CMaterial_HasAuxLayerTexture_maybe
//   [ ] 0xbb828  CGeometry_SetupMaterialShader_maybe
//   [ ] 0xbb910  CMaterial_SetUVTransformMatrices
//   [ ] 0xbb938  CMaterial_GetUVTransformMatrices
//   [x] 0xbb960  CMaterial_GetDualUVTransformMatrix_maybe
//   [ ] 0xbb9a0  CMaterial_GetUVTransformMatrixByIndex_maybe
//   [x] 0xbb9f8  CMaterial_GetUVTransformMatrix_maybe
//   [ ] 0xbba68  CMaterial_GetDualBlendMode_maybe
//   [ ] 0xbbae0  CMaterial_SetDualBlendMode_maybe
//   [ ] 0xbbb28  CMaterial_GetBumpMapCoefficient
//   [ ] 0xbbb50  CMaterial_SetBumpMapCoefficient
//   [ ] 0xbbb78  CMaterial_GetBumpMapFrame
//   [ ] 0xbbba8  CMaterial_SetBumpMapFrame
//   [ ] 0xbbbd0  CMaterial_GetBumpMapTexture
//   [ ] 0xbbc30  CMaterial_SetEnvMapCoefficient
//   [ ] 0xbbc88  CMaterial_SetEnvMapFBAlpha
//   [x] 0xbbce0  CMaterial_GetEnvMapTexture
//   [ ] 0xbbd38  CMaterial_ResetEffectData_maybe
//   [ ] 0xbbda8  CMaterial_RecursiveRegistration
//   [ ] 0xbbde8  Graphic_RegisterMaterialExtPlugin_maybe
//   [x] 0xbbe40  CMaterial_Construct
//   [x] 0xbbed0  CMaterial_DeleteArray
//   [x] 0xbbf70  CMaterial_GetEnvMapCoefficient
//   [ ] 0xbbfc8  CMaterial_GetEnvMapFBAlpha
//   [ ] 0xbc030  CMaterial_GetEnvMapFrame
//   [ ] 0xbc090  CMaterial_SetEnvMapFrame
//   [ ] 0xbc0e8  MaterialExtPlugin_Constructor
//   [ ] 0xbc110  MaterialExtPlugin_Copy
//   [ ] 0xbc140  CMaterial_GetExtColor_maybe
//   [ ] 0xbc150  CMaterial_HasAuxTexture8C_maybe
//   [ ] 0xbc170  CMaterial_Construct_2
//   [ ] 0xbc200  CMaterial_HasBaseTexture_maybe
//   [x] 0xbc238  SetMaterialTexture_maybe
//   [ ] 0xbc298  CMaterial_MessageProc
//   [x] 0xbc2a0  CMaterial_HasAuxTexture88OrLayerTexture_maybe
//   [ ] 0xbc2f0  CMaterial_SetUVTransformMatrices_2  [dead]
//   [ ] 0xbc318  RegisterCMaterialClass
//   [ ] 0xbc3d0  _GLOBAL__D_bc3d0
//   [ ] 0xbc3e0  _GLOBAL__I_bc3e0
//   [ ] 0xbc3f0  CMaterial_SetAuxLayerTextureWithDefaults_maybe
//   [ ] 0xbc4b0  MatFXUVAnim_SetBaseUVTransform_2_maybe
//   [ ] 0xbc560  CMaterial_SetAuxTexture88_maybe
//   [ ] 0xbc5c8  CMaterial_SetAuxLayerTexture_maybe
//   [ ] 0xbc640  CMaterial_SetAuxTexture8C_maybe
//   [ ] 0xbc6a8  CMaterial_SetupBumpMap_maybe
//   [ ] 0xbc748  CMaterial_SetBumpMapTexture
//   [ ] 0xbc7c8  CMaterial_ApplyAuxTextureAddressing_maybe
//   [x] 0xbc920  CMaterial_HasSecondaryEffectTexture_maybe
//   [ ] 0xbc998  CMaterial_GetSecondaryEffectTexture_maybe
//   [ ] 0xbca40  CMaterial_SetEnvMapTexture
//   [ ] 0xbcb18  CMaterial_SetupEnvMap_maybe
//   [x] 0xbcc18  CMaterial_Create
//   [x] 0xbccc8  CMaterial_CreateArray
//   [ ] 0xbce38  CMaterial_ResetUVTransformMatrix_maybe
//   [ ] 0xbcf78  MatFXUVAnim_SetDualUVTransform_2_maybe
//   [ ] 0xbd038  CMaterial_SetSecondaryEffectTexture_maybe
//   [ ] 0xbd168  MatFXUVAnim_SetDualUVTransform_maybe
//   [x] 0xbd228  MatFXUVAnim_UpdateMaterial_maybe
//   [ ] 0xbdec8  MatFXUVAnim_SetBaseUVTransform_maybe
//   [ ] 0xbdf78  CMaterial_ReleaseEffectData_maybe
//   [ ] 0xbe260  CMaterial_Destroy
//   [x] 0xbe348  CMaterial_PostLoad
//   [x] 0xbe8a8  CMaterial_SetEffectType_maybe
//   [x] 0xbec50  CMaterial_Load
//   [ ] 0xbfd60  CMaterial_DeletingDestructor
//   [ ] 0xbfda0  CMaterial_Destructor
//   [ ] 0xbfdb8  CMaterial_Destructor_2  [dead]
//   [ ] 0xbfdd0  KStub_Return1_bfdd0  [dead]
//   [ ] 0xbfdd8  MaterialExt_GetShaderMode_maybe
//   [x] 0xbfde8  CMaterial_ConstructBase_maybe
//   [ ] 0xbfef0  CMaterial_ModeTransition_ToMode12_maybe
//   [ ] 0xbff20  CMaterial_RestoreEnvMapEffect_maybe
//   [ ] 0xc0038  CMaterial_ClearAuxTexturesAndRestoreEnvMap_maybe
//   [ ] 0xc0170  CMaterial_ModeTransition_ToMode0ClearEnvMap_maybe
//   [ ] 0xc0210  CMaterial_ModeTransition_ToMode0_maybe
//   [ ] 0xc0288  CMaterial_InvokeModeTransitionHandler_maybe
//   [ ] 0xc0358  FUN_000c0358  [dead]
//
//   [x] 0x9a1160  CMaterial_GetClassType  [inline]
//   [x] 0x9a1168  CMaterial_GetClassID  [inline]
//   [x] 0x9a1170  CMaterial_GetSerializationFlags  [inline]
//   [x] 0x9a11b8  CMaterial_IsKindOfClass  [inline]
//   [ ] 0x9a11d8  cosf  [inline]
//   [ ] 0x9a1390  sinf  [inline]
#include "k2000/logic/render/CMaterial.h"

#include <cstring>
#include <new>

#include "Renderware/rpmatfx/RpMatFX.h"
#include "Renderware/rwcore/RwTexture.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/CCloneManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/IKTime.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"

namespace {
const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc CColor

inline float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}

// The inlined identity of CMaterial_Load (0xbefe0) and CMaterial_SetEffectType_maybe (0xbe9dc), in
// their store order.
void SetIdentity(CMatrix34* matrix) {
    matrix->m_right.x = 1.0f;
    matrix->m_ui32Flags = 0x20003u;  // rwMATRIXTYPEORTHONORMAL | rwMATRIXINTERNALIDENTITY
    matrix->m_at.z = 1.0f;
    matrix->m_up.y = 1.0f;
    matrix->m_up.x = 0.0f;
    matrix->m_right.z = 0.0f;
    matrix->m_right.y = 0.0f;
    matrix->m_at.y = 0.0f;
    matrix->m_at.x = 0.0f;
    matrix->m_up.z = 0.0f;
    matrix->m_pos.z = 0.0f;
    matrix->m_pos.y = 0.0f;
    matrix->m_pos.x = 0.0f;
}
}  // namespace

CMaterial::KpFnModeTransition CMaterial::s_apfnModeTransitions[15][15];
CMaterialSharedState CMaterial::s_sharedState;

// 0x000bbe40 CMaterial_Construct (CMaterial_Create 0x000bcc18 inlines the same stores). +0x12, +0x14..
// +0x20, +0x2c..+0x80, +0xa4, +0xa8 and +0xac are left as they are.
CMaterial::CMaterial() {
    m_fAuxFloat94 = 50.0f;  // 0x42480000
    m_pRpMaterial = nullptr;
    m_pEffectData = nullptr;
    m_baProperties = 0;
    m_unk0c = 0;
    m_FXParameters.m_unk24 = 0;
    m_FXParameters.m_unk28 = 0;
    m_pAuxTexture88 = nullptr;
    m_pAuxTexture8C = nullptr;
    m_ui16UpdateFrameCounter = 0;
    std::memcpy(m_cExtColor, kColorWhite, 4);
    RegisterModeTransitions();
    m_pAuxLayer = nullptr;
    m_unk90 = 0;
    m_pFirstPassTransformMatrix = nullptr;
}

// 0x000bb780 CMaterial_SetModeTransitionHandler_maybe: the table at 0x00c5cb74, 15 x 15 entries of 8.
void CMaterial::SetModeTransitionHandler(KpFnModeTransition handler, int32_t from, int32_t to) {
    s_apfnModeTransitions[from][to] = handler;
}

// 0x000bfde8 CMaterial_ConstructBase_maybe (does not use the object).
void CMaterial::RegisterModeTransitions() {
    SetModeTransitionHandler(&CMaterial::ModeTransitionToMode12, 11, 12);            // opd 0xb4cb48
    SetModeTransitionHandler(&CMaterial::ModeTransitionToMode12, 13, 12);
    SetModeTransitionHandler(&CMaterial::ModeTransitionToMode0, 13, 0);              // opd 0xb4cb68
    SetModeTransitionHandler(&CMaterial::ModeTransitionToMode0, 11, 0);
    SetModeTransitionHandler(&CMaterial::RestoreEnvMapEffect, 10, 2);                // opd 0xb4cb50
    SetModeTransitionHandler(&CMaterial::ModeTransitionToMode0ClearEnvMap, 12, 0);   // opd 0xb4cb60
    SetModeTransitionHandler(&CMaterial::ModeTransitionToMode0ClearEnvMap, 14, 0);
}

// 0x000be8a8 CMaterial_SetEffectType_maybe. The slot's type is bits 16 + 7 * slot; each case of the jump
// table at 0xbe928 also clears some of the slot's flag bits (19..22 + 7 * slot) and sets its defaults.
void CMaterial::SetEffectType(int32_t slot, uint32_t effectType, int32_t reset) {
    const uint32_t shift = static_cast<uint32_t>(slot * 7 + 0x10);
    const uint32_t props = (m_baProperties & ~(7u << shift)) | (effectType << shift);
    m_baProperties = props;
    CMaterialFXEffect& fx = m_FXParameters.m_aEffects[slot];
    switch (effectType) {
    case 0:
    case 1:  // 0xbeab8
        m_baProperties = props & ~((1u << (shift + 3)) | (1u << (shift + 4)));
        fx.k01.m_aui32Words[3] = 0;
        fx.k01.m_aui32Words[0] = 0;
        fx.k01.m_aui32Words[1] = 0;
        fx.k01.m_aui32Words[2] = 0;
        m_baProperties = m_baProperties & ~(1u << (shift + 5)) & ~(1u << (shift + 6));
        fx.k01.m_ui8Byte11 = 0;
        fx.k01.m_ui32Word20 = 0;
        fx.k01.m_ui8Byte10 = 0;
        fx.k01.m_ui32Word18 = 0;
        break;
    case 2:  // 0xbe940
        m_baProperties = props & ~((1u << (shift + 3)) | (1u << (shift + 4)));
        fx.k2.m_ui16Half8 = 0;  // one word store of 0 over both halves
        fx.k2.m_ui16HalfA = 0;
        fx.k2.m_aui32Words[0] = 0;
        fx.k2.m_aui32Words[1] = 0;
        fx.k2.m_ui16HalfA = 1;
        fx.k2.m_fFloatC = 1.0f;
        fx.k2.m_fAccumV = 0.0f;
        fx.k2.m_fFloat10 = 1.0f;
        fx.k2.m_ui16Half8 = 1;
        fx.k2.m_fAccumU = 0.0f;
        break;
    case 3:  // 0xbebd8
        m_baProperties = props & ~((1u << (shift + 3)) | (1u << (shift + 4)));
        fx.k3.m_unkC = 0;
        fx.k3.m_afFloats[0] = 0x1.99999ap-4f;  // 0.1 (toc -0x59d0)
        fx.k3.m_afFloats[1] = 1.0f;
        fx.k3.m_unk8 = 0;
        break;
    case 4:  // 0xbeb58
        m_baProperties = props & ~((1u << (shift + 3)) | (1u << (shift + 4)));
        fx.k4.m_unkC = 0;
        fx.k4.m_fFloat20 = 1.0f;
        fx.k4.m_ui8Byte14 = 1;
        fx.k4.m_fFloat18 = 0x1.99999ap-4f;
        fx.k4.m_afFloats[0] = 0x1.99999ap-4f;
        fx.k4.m_afFloats[1] = 1.0f;
        fx.k4.m_unk8 = 0;
        break;
    default:
        break;
    }
    if (reset == 0) return;
    // 0xbe9b8: the slot's UV transform matrix, back to the identity.
    CMatrix34* matrix;
    if (slot != 0) {
        RwMatrix* base = nullptr;
        RwMatrix* dual = nullptr;
        RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
        matrix = reinterpret_cast<CMatrix34*>(dual);  // the same layout
    } else if (((m_baProperties >> 3) & 0xf) - 1u <= 5u) {  // modes 1..6
        RwMatrix* base = nullptr;
        RwMatrix* dual = nullptr;
        RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
        matrix = reinterpret_cast<CMatrix34*>(base);
    } else {
        matrix = m_pFirstPassTransformMatrix;
    }
    SetIdentity(matrix);  // BUG(original): no null check on the MatFX matrices
    if (((m_baProperties >> shift) & 7u) != 0) return;
    // Effect type 0: the slot's +0x08 / +0x0c become the translation.
    const float u = WordAsFloat(fx.k01.m_aui32Words[2]);
    const float v = WordAsFloat(fx.k01.m_aui32Words[3]);
    matrix->m_pos.y = v;
    matrix->m_ui32Flags = 3;
    matrix->m_pos.x = u;
}

// 0x0009e018 CMaterialMode7or8SharedState_Load_maybe (unit CLightManager.cpp by address).
int32_t CMaterialSharedState::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        IKFile_ReadRef(file, &m_pRef);
        ReadU32LE(file, &m_unk8);
    }
    return 1;
}

// 0x000c3b28 CMaterialEffectData_Load_maybe (unit CKSurfaceParticlesRendable.cpp by address). Returns
// nothing (r3 is not set).
void CMaterialEffectData_Load(CMaterialEffectData* data, IKFile* file, int32_t type, CMaterial* owner) {
    data->m_pOwner = owner;
    if (type != 0) return;
    ReadU32LE(file, &data->m_unkC);
    ReadU32LE(file, &data->m_unk10);
    ReadU32LE(file, &data->m_unk14);
    ReadU32LE(file, &data->m_unk18);
    IKFile_ReadRef(file, &data->m_pRef4);
    IKFile_ReadRef(file, &data->m_pRef8);
    data->m_pOwner = owner;
}

// 0x000bec50 CMaterial_Load. Only the level load (type 0) reads the material; every type reads the two
// flag bytes at the end.
int32_t CMaterial::Load(IKFile* file, int32_t type) {
    auto mode = [this]() { return (m_baProperties >> 3) & 0xfu; };
    if (type == K_LEVEL_PLATEFORMS) {
        // 0xbefe0
        CMatrix34* matrix = RwMatrixCreate_Thunk();
        m_pFirstPassTransformMatrix = matrix;
        matrix->m_ui32Flags = 0x20003u;
        matrix->m_pos.x = 0.0f;
        matrix->m_at.z = 1.0f;
        matrix->m_up.y = 1.0f;
        matrix->m_right.x = 1.0f;
        matrix->m_up.x = 0.0f;
        matrix->m_right.z = 0.0f;
        matrix->m_right.y = 0.0f;
        matrix->m_at.y = 0.0f;
        matrix->m_at.x = 0.0f;
        matrix->m_up.z = 0.0f;
        matrix->m_pos.z = 0.0f;
        matrix->m_pos.y = 0.0f;
        uint8_t fromClone = 0;
        ReadRaw(file, &fromClone, 1);
        m_iCloneTeamElement = -1;
        if (fromClone != 0) {
            ReadS32LE(file, &m_iCloneTeamElement);  // the material comes from the CCloneManager at PostLoad
        } else {
            // A geometry (CGeometry / CParticleGeometry): its RpGeometry's first material.
            IKSerializable* geometry = nullptr;
            IKFile_ReadRef(file, &geometry);
            RpGeometry* rpGeometry = RwShim_FindRpGeometry(geometry);  // geometry->vt+0x84
            RpMaterial* material = nullptr;
            if (rpGeometry != nullptr) material = rpGeometry->matList.materials[0];
            m_pRpMaterial = material;
            material->kMaterial = this;  // BUG(original): no null check (the PS3 stores at null + offset)
            ++m_pRpMaterial->refCount;
        }
        ReadU32LE(file, &m_baProperties);
        const uint32_t readMode = mode();  // r31: the mode as read
        if (readMode == 7) {  // 0xbf7a0
            s_sharedState.Load(file, K_LEVEL_PLATEFORMS);
            ReadU32LE(file, &m_FXParameters.m_ui32Param0);
        } else if (readMode == 8) {  // 0xbf7f8
            s_sharedState.Load(file, K_LEVEL_PLATEFORMS);
            ReadU32LE(file, &m_FXParameters.m_ui32Param0);
            ReadU32LE(file, &m_FXParameters.m_ui32Param8);
            IKFile_ReadTextureRef(file, reinterpret_cast<void**>(&m_FXParameters.m_pTexture), 0);
            ++m_FXParameters.m_pTexture->refCount;  // BUG(original): no null check
        }
        // 0xbf178: modes 2, 3 pass the first test and fail the second.
        if ((readMode - 2u <= 1u || readMode == 8 || readMode == 10 || readMode == 12 || readMode == 14) &&
            readMode - 7u <= 7u) {
            void* texture = nullptr;
            IKFile_ReadTextureRef(file, &texture, 0);
            float coefficient = 0.0f;
            ReadF32LE(file, &coefficient);
            uint8_t useFBAlpha = 0;
            ReadRaw(file, &useFBAlpha, 1);
            if (texture == nullptr) {
                m_FXParameters.m_pTexture = nullptr;
            } else {
                if (mode() - 2u <= 1u) {
                    RpMatFXMaterialSetEnvMapCoefficient(m_pRpMaterial, coefficient);
                } else {
                    std::memcpy(&m_FXParameters.m_ui32Param8, &coefficient, 4);  // stfs to +0x1c
                }
                if (mode() - 2u <= 1u) RpMatFXMaterialSetEnvMapFBAlpha(m_pRpMaterial, useFBAlpha);
                m_FXParameters.m_pTexture = static_cast<RwTexture*>(texture);
                ++m_FXParameters.m_pTexture->refCount;
            }
        }
        // 0xbf1a8: the FX effect slots (modes 5, 6, 12, 14; mode 6 has two).
        uint32_t props = m_baProperties;
        if ((props & 0x100u) != 0 && ((props >> 3) & 0xfu) <= 14u) {
            const uint32_t fxMode = (props >> 3) & 0xfu;
            int32_t count = fxMode == 6 ? 2 : 1;
            uint32_t shift = static_cast<uint32_t>(count) * 7u + 9u;  // the last slot's type bits
            if (((1u << fxMode) & 0x5060u) != 0) {
                while (count != 0) {
                    --count;  // the slot, last first
                    const uint32_t effectType = (props >> shift) & 7u;
                    const uint32_t saved = m_baProperties;
                    SetEffectType(count, effectType, 0);
                    m_baProperties = saved;  // CBitArray copy back: SetEffectType's bit changes are undone
                    CMaterialFXEffect& fx = m_FXParameters.m_aEffects[count];
                    switch (effectType) {  // jump table 0xbf4f8
                    case 0:
                    case 1:  // 0xbf8b4
                        ReadU32LEWords(file, fx.k01.m_aui32Words, 4);
                        ReadRaw(file, &fx.k01.m_ui8Byte10, 1);
                        ReadRaw(file, &fx.k01.m_ui8Byte11, 1);
                        ReadU32LE(file, &fx.k01.m_ui32Word18);
                        ReadU32LE(file, &fx.k01.m_ui32Word20);
                        break;
                    case 2: {  // 0xbf35c
                        ReadU32LEWords(file, fx.k2.m_aui32Words, 2);
                        uint8_t halves[4];  // one 4-byte read, each half swapped (lhbrx)
                        file->Read(halves, 4);
                        fx.k2.m_ui16Half8 = static_cast<uint16_t>(halves[0] | (halves[1] << 8));
                        fx.k2.m_ui16HalfA = static_cast<uint16_t>(halves[2] | (halves[3] << 8));
                        ReadF32LE(file, &fx.k2.m_fFloatC);
                        ReadF32LE(file, &fx.k2.m_fFloat10);
                        break;
                    }
                    case 3:  // 0xbfa18
                        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(fx.k3.m_afFloats), 2);
                        break;
                    case 4:  // 0xbfa78
                        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(fx.k4.m_afFloats), 2);
                        ReadF32LE(file, &fx.k4.m_fFloat18);
                        ReadF32LE(file, &fx.k4.m_fFloat20);
                        ReadRaw(file, &fx.k4.m_ui8Byte14, 1);
                        break;
                    default:
                        break;
                    }
                    shift -= 7;
                    props = m_baProperties;
                }
            }
        }
        if ((m_baProperties & 0x8000u) != 0) {  // 0xbf6e4: the first byte lands at +0x33
            ReadRaw(file, &m_FXParameters.m_aui8Raw2c[7], 1);
            ReadRaw(file, &m_FXParameters.m_aui8Raw2c[0], 7);
        }
        uint32_t m = mode();
        if ((m == 11 || m == 13 || m == 12 || m == 14) && m_pAuxLayer == nullptr) {  // 0xbf5f8
            CMaterialAuxLayer* aux = static_cast<CMaterialAuxLayer*>(::operator new(sizeof(CMaterialAuxLayer)));
            m_pAuxLayer = aux;
            aux->m_afUnk10[6] = 0.0f;
            aux->m_pTexture = nullptr;
            aux->m_ui8Byte4 = 0;
            aux->m_ui8Byte5 = 0;
            aux->m_ui8Byte6 = 0;
            aux->m_ui8Unk7 = 0;
            aux->m_ui32Param8 = 0;
            aux->m_ui32ParamC = 0;
            for (int i = 0; i < 6; ++i) aux->m_afUnk10[i] = 0.0f;
            m_pAuxLayer->m_afUnk10[6] = 1.0f;
        }
        if (mode() == 11) {  // 0xbfbe4
            ReadRaw(file, &m_pAuxLayer->m_ui8Byte6, 1);
            ReadRaw(file, &m_pAuxLayer->m_ui8Byte4, 1);
            ReadRaw(file, &m_pAuxLayer->m_ui8Byte5, 1);
            ReadU32LE(file, &m_pAuxLayer->m_ui32Param8);
            void* texture = nullptr;
            IKFile_ReadTextureRef(file, &texture, 1);
            m_pAuxLayer->m_pTexture = static_cast<RwTexture*>(texture);
            ReadU32LE(file, &m_pAuxLayer->m_ui32ParamC);
        }
        m = mode();
        if (m == 11 || m == 13 || m == 12 || m == 14) {  // 0xbf650 (mode 11 reads a second texture)
            void* texture = nullptr;
            IKFile_ReadTextureRef(file, &texture, 1);
            m_pAuxLayer->m_pTexture = static_cast<RwTexture*>(texture);
        }
        m = mode();
        if (m == 13 || m == 10) {  // 0xbf680
            void* texture = nullptr;
            IKFile_ReadTextureRef(file, &texture, 1);
            m_pAuxTexture88 = static_cast<RwTexture*>(texture);
        }
        if (mode() == 12) {  // 0xbf77c
            void* texture = nullptr;
            IKFile_ReadTextureRef(file, &texture, 1);
            m_pAuxTexture8C = static_cast<RwTexture*>(texture);
        }
        if ((m_baProperties & 0x200u) != 0) {  // 0xbf74c
            CMaterialEffectData* data = static_cast<CMaterialEffectData*>(::operator new(sizeof(CMaterialEffectData)));
            m_pEffectData = data;
            CMaterialEffectData_Load(data, file, K_LEVEL_PLATEFORMS, this);
        }
        ReadF32LE(file, &m_fAuxFloat94);
        ReadRaw(file, m_cExtColor, 4);
        if (mode() == 12) ReadU32LE(file, &m_unk90);  // 0xbfba4
        uint8_t flag14 = 0;
        ReadRaw(file, &flag14, 1);
        m_baProperties = (m_baProperties & ~0x4000u) | (static_cast<uint32_t>(flag14) << 14);
    }
    // 0xbecb0: every type.
    uint8_t flag = 1;
    ReadRaw(file, &flag, 1);
    m_baProperties = (m_baProperties & ~0x400u) | (static_cast<uint32_t>(flag) << 10);
    flag = 0;
    ReadRaw(file, &flag, 1);
    m_baProperties = (m_baProperties & ~0x800u) | (static_cast<uint32_t>(flag) << 11);
    if (mode() == 14) {  // 0xbedb8: seven floats into the aux layer, kept only when it exists
        for (int i = 0; i < 7; ++i) {
            float value = 0.0f;
            ReadF32LE(file, &value);
            if (m_pAuxLayer != nullptr) m_pAuxLayer->m_afUnk10[i] = value;
        }
    }
    return 1;
}

RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture);  // 0x006a3890 (Renderware/rpworld/RpGeometry.cpp)

// 0x000bc238 SetMaterialTexture_maybe (both of the original's branches read the same word)
void CMaterial::SetTexture(RwTexture* texture) {
    if (m_pRpMaterial->texture != texture) RpMaterialSetTexture(m_pRpMaterial, texture);
}

namespace {
// CMaterial_PostLoad's texture addressing for the aux textures (0xbe5c0 ..): the filter byte kept, addressing U / V set to
// clamp (0x100 / 0x1000) and, unless the material has property 0x1000, taken over from the diffuse texture.
void InheritAddressing(RwTexture* texture, const RpMaterial* rpMaterial, uint32_t properties) {
    uint32_t& word = texture->filterAddressing;
    const uint32_t filter = word & 0xff;
    const uint32_t high = word & 0xffff0000u;
    word = high | filter | 0x100u | 0x1000u;
    if ((properties & 0x1000u) == 0 && rpMaterial->texture != nullptr) {
        const uint32_t diffuse = rpMaterial->texture->filterAddressing;
        word = high | 0x1000u | filter | (diffuse & 0xf00u);
        word = high | static_cast<uint16_t>(filter | (diffuse & 0xf00u)) | (diffuse & 0xf000u);
    }
}

// The UV matrix of an effect slot as CMaterial_PostLoad rebuilds it: the identity, and for an effect of type 0 the
// slot's +0x08 / +0x0c as the translation.
void RebuildUvMatrix(CMatrix34* matrix, uint32_t properties, uint32_t typeShift, const CMaterialFXEffect& fx) {
    if (matrix == nullptr) return;  // BUG(original): no null check; a material without the UV effect is not in the data
    SetIdentity(matrix);
    if (((properties >> typeShift) & 7u) == 0) {
        matrix->m_pos.x = WordAsFloat(fx.k01.m_aui32Words[2]);
        matrix->m_pos.y = WordAsFloat(fx.k01.m_aui32Words[3]);
        matrix->m_ui32Flags = 3;
    }
}
}  // namespace

// 0x000be348 CMaterial_PostLoad
int32_t CMaterial::PostLoad(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        if (m_iCloneTeamElement >= 0) {
            // The material of a clone team element (CCloneManager_GetTeamElementFirstMaterial 0x86708): the first
            // RpMaterial of the element's LOD 0 geometry; it takes this CMaterial as its K plugin and a reference.
            CCloneManager* cloneManager = static_cast<CCloneManager*>(g_pEngine->m_graphic->m_renderer->m_cloneManager);
            RpMaterial* material = cloneManager->GetTeamElementFirstMaterial(static_cast<uint32_t>(m_iCloneTeamElement));
            m_pRpMaterial = material;
            material->kMaterial = this;
            ++material->refCount;
        }
        const uint32_t mode = (m_baProperties >> 3) & 0xf;
        if (mode == 5) {
            if ((m_baProperties & 4) == 0) {
                CMatrix34* base = RwMatrixCreate_Thunk();
                RpMatFXMaterialSetUVTransformMatrices(m_pRpMaterial, reinterpret_cast<RwMatrix*>(base), nullptr);
            }
        } else if (mode == 6 && (m_baProperties & 4) == 0) {
            CMatrix34* base = RwMatrixCreate_Thunk();
            CMatrix34* dual = RwMatrixCreate_Thunk();
            RpMatFXMaterialSetUVTransformMatrices(m_pRpMaterial, reinterpret_cast<RwMatrix*>(base), reinterpret_cast<RwMatrix*>(dual));
        }
    }
    // (property 0x200: KStub_Nop_c3728(effect data, type))
    if (m_pAuxTexture8C != nullptr) m_pAuxTexture8C->filterAddressing = (m_pAuxTexture8C->filterAddressing & 0xffff00ffu) | 0x1100u;
    if (m_pAuxTexture88 != nullptr) InheritAddressing(m_pAuxTexture88, m_pRpMaterial, m_baProperties);
    if (m_pAuxLayer != nullptr && m_pAuxLayer->m_pTexture != nullptr) InheritAddressing(m_pAuxLayer->m_pTexture, m_pRpMaterial, m_baProperties);
    const uint32_t properties = m_baProperties;
    if ((properties & 0x100u) != 0) {
        uint32_t mode = (properties >> 3) & 0xf;
        RwMatrix* base = nullptr;
        RwMatrix* dual = nullptr;
        if (mode == 5) {
            RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
            RebuildUvMatrix(reinterpret_cast<CMatrix34*>(base), properties, 16, m_FXParameters.m_aEffects[0]);
        }
        mode = (m_baProperties >> 3) & 0xf;
        if (mode == 0xb || mode == 0xd || mode == 0xc || mode == 0xe) {
            RebuildUvMatrix(m_pFirstPassTransformMatrix, properties, 16, m_FXParameters.m_aEffects[0]);
        }
        if (((m_baProperties >> 3) & 0xf) == 6) {
            RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
            RebuildUvMatrix(reinterpret_cast<CMatrix34*>(base), properties, 16, m_FXParameters.m_aEffects[0]);
            RebuildUvMatrix(reinterpret_cast<CMatrix34*>(dual), properties, 23, m_FXParameters.m_aEffects[1]);
        }
    }
    return 1;
}

// 0x000bbce0 CMaterial_GetEnvMapTexture
RwTexture* CMaterial::GetEnvMapTexture() {
    if (((m_baProperties >> 3) & 0xf) - 2u > 1u) return m_FXParameters.m_pTexture;
    return RpMatFXMaterialGetEnvMapTexture(m_pRpMaterial);
}

// 0x000bc920 CMaterial_HasSecondaryEffectTexture_maybe
uint32_t CMaterial::HasSecondaryEffectTexture() { return GetEnvMapTexture() != nullptr ? 1u : 0u; }

// 0x000bbf70 CMaterial_GetEnvMapCoefficient
float CMaterial::GetEnvMapCoefficient() {
    if (((m_baProperties >> 3) & 0xf) - 2u > 1u) return WordAsFloat(m_FXParameters.m_ui32Param8);
    return RpMatFXMaterialGetEnvMapCoefficient(m_pRpMaterial);
}

// 0x000bb9f8 CMaterial_GetUVTransformMatrix_maybe
CMatrix34* CMaterial::GetUVTransformMatrix() {
    if (((m_baProperties >> 3) & 0xf) - 1u > 5u) return m_pFirstPassTransformMatrix;
    RwMatrix* base = nullptr;
    RwMatrix* dual = nullptr;
    RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
    return reinterpret_cast<CMatrix34*>(base);
}

// 0x000bb960 CMaterial_GetDualUVTransformMatrix_maybe
CMatrix34* CMaterial::GetDualUVTransformMatrix() {
    RwMatrix* base = nullptr;
    RwMatrix* dual = nullptr;
    RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
    return reinterpret_cast<CMatrix34*>(dual);
}

// ---- 0x000bd228 MatFXUVAnim_UpdateMaterial_maybe ------------------------------------------------------------------
namespace {
const CVector3 kUvAxisX = {1.0f, 0.0f, 0.0f};  // 0x00c50d34 (the shared X axis; zero in the EBOOT's BSS)
const CVector3 kUvAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}

// The sine / cosine the animation inlines: a non-negative argument uses the inlined single-precision
// polynomials, a negative one (-0.0 included) the library's sinf 0x009a1390 / cosf 0x009a11d8 of its magnitude.
float UvSine(float angle) { return SignBitSet(angle) ? -crt::LibSinf(-angle) : crt::InlineSinf(angle); }
float UvCosine(float angle) { return SignBitSet(angle) ? crt::LibCosf(-angle) : crt::InlineCosf(angle); }

// A scroll position wrapped into [-1, 1] by repeated adding / subtracting of 1.0 (the original's loops).
void WrapScroll(float* x) {
    if (!(*x >= -1.0f)) {
        do {
            *x += 1.0f;
        } while (*x < -1.0f);
    }
    while (*x > 1.0f) *x -= 1.0f;
}

// "Clear rwMATRIXINTERNALIDENTITY": the original rotates left by 14, masks off the top bit and rotates by 18.
inline uint32_t ClearInternalIdentity(uint32_t flags) { return flags & ~0x20000u; }

// One axis of the type 0 scroll (the code at 0xbd944 for U, 0xbd880 for V: the same with other offsets).
// Unlimited (properties bit 21 / 22 + 7 * slot clear): pos += speed * dt, wrapped. Limited: the position moves at
// `speed` towards the stop step / maxStep, waits there `pause` seconds, then the step advances (back to 1 after
// maxStep); step 0 is also entered when the position passes 1.0 (it jumps to 0 and waits there).
void ScrollAxis(float* pos, float speed, bool limited, uint8_t* step, uint8_t maxStep, uint8_t* waiting, float pause,
                float* countdown, float dt) {
    if (!limited) {
        *pos = ppc::fmadds(speed, dt, *pos);
        WrapScroll(pos);
        return;
    }
    if (*waiting == 0) {
        *pos = ppc::fmadds(speed, dt, *pos);
        if (*step != 0 && *pos >= 1.0f) {
            *pos = 0.0f;
            *step = 0;
            *waiting = 1;
            *countdown = pause;
            return;
        }
        const float target = static_cast<float>(*step) / static_cast<float>(maxStep);
        if (*pos >= target) {
            *pos = target;
            *waiting = 1;
            *countdown = pause;
        }
    } else if (*countdown <= 0.0f) {
        *waiting = 0;
        *step = maxStep <= *step ? 1 : static_cast<uint8_t>(*step + 1);
    } else {
        *countdown = *countdown - dt;
    }
    WrapScroll(pos);
}
}  // namespace

// 0x000bd228 MatFXUVAnim_UpdateMaterial_maybe (the pointer-to-member table 0x00c4b0cc, modes 5, 6, 12, 14)
void CMaterial::UpdateUVAnimation(IKTime* frameClock) {
    if (frameClock->m_eCurrentState != IKTime::RUNNING) return;
    const float dt = frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];      // +0x1c
    const float time = frameClock->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];  // +0x04
    const uint32_t mode = (m_baProperties >> 3) & 0xf;
    // One slot in modes 5, 11, 12, 13 and 14, otherwise two.
    const uint32_t slotCount = (mode == 5 || mode == 0xb || mode == 0xd || mode == 0xc || mode == 0xe) ? 1u : 2u;
    for (uint32_t slot = 0; slot < slotCount; ++slot) {
        // Slot 0 animates the base UV matrix (modes 1..6) or the first-pass matrix; slot 1 the dual matrix.
        RwMatrix* base = nullptr;
        RwMatrix* dual = nullptr;
        CMatrix34* matrix;
        if (slot != 0) {
            RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
            matrix = reinterpret_cast<CMatrix34*>(dual);
        } else if (mode - 1u <= 5u) {
            RpMatFXMaterialGetUVTransformMatrices(m_pRpMaterial, &base, &dual);
            matrix = reinterpret_cast<CMatrix34*>(base);
        } else {
            matrix = m_pFirstPassTransformMatrix;
        }
        const uint32_t effectType = (m_baProperties >> (16 + 7 * slot)) & 7u;
        if (effectType > 4) continue;
        // BUG(original): no null check; the original writes through the null pointer of a material whose MatFX data
        // has no such matrix.
        if (matrix == nullptr) continue;
        // Properties bits of the slot: +3 U animated, +4 V animated, +5 U limited, +6 V limited (from the type's 3 bits).
        const uint32_t bitU = 19 + 7 * slot;
        const uint32_t bitV = 20 + 7 * slot;
        const uint32_t properties = m_baProperties;
        CMaterialFXEffect& fx = m_FXParameters.m_aEffects[slot];  // +0x34 + 0x28 * slot
        switch (effectType) {
        case 0: {  // scroll: the translation moves by the speeds (+0x00 U, +0x04 V) x dt
            float u = matrix->m_pos.x;
            float v = matrix->m_pos.y;
            if ((properties & (1u << bitU)) != 0) {
                ScrollAxis(&u, WordAsFloat(fx.k01.m_aui32Words[0]), (properties & (1u << (bitU + 2))) != 0,
                           &fx.k01.m_ui8StepU, fx.k01.m_ui8Byte10, &fx.k01.m_ui8WaitingU,
                           WordAsFloat(fx.k01.m_ui32Word18), &fx.k01.m_fWaitLeftU, dt);
            }
            if ((properties & (1u << bitV)) != 0) {
                ScrollAxis(&v, WordAsFloat(fx.k01.m_aui32Words[1]), (properties & (1u << (bitV + 2))) != 0,
                           &fx.k01.m_ui8StepV, fx.k01.m_ui8Byte11, &fx.k01.m_ui8WaitingV,
                           WordAsFloat(fx.k01.m_ui32Word20), &fx.m_fWaitLeftV, dt);
            }
            matrix->m_pos.x = u;
            matrix->m_pos.y = v;
            matrix->m_pos.z = 0.0f;
            matrix->m_ui32Flags = ClearInternalIdentity(matrix->m_ui32Flags);
            break;
        }
        case 1:  // rotation: about the X axis by speed U (+0x00) x dt degrees, then about Y by speed V (+0x04) x dt
            if ((properties & (1u << bitU)) != 0) {
                Mat4_RotateInPlace(matrix, &kUvAxisX, WordAsFloat(fx.k01.m_aui32Words[0]) * dt);
            }
            if ((m_baProperties & (1u << bitV)) != 0) {
                Mat4_RotateInPlace(matrix, &kUvAxisY, WordAsFloat(fx.k01.m_aui32Words[1]) * dt);
            }
            break;
        case 2: {  // flip-book: a grid of w x h frames (+0x08, +0x0a), one cycle through it every +0x0c seconds
            const uint16_t w = fx.k2.m_ui16Half8;
            const uint16_t h = fx.k2.m_ui16HalfA;
            if (w == 0 || h == 0) break;
            const float cycleTime = fx.k2.m_fFloatC;
            const float frameCount = static_cast<float>(static_cast<int32_t>(static_cast<uint32_t>(w) * h));
            const float uStep = 1.0f / static_cast<float>(w);
            const float vStep = 1.0f / static_cast<float>(h);
            // The position in the current cycle as a fraction, times w * h = the frame index.
            const float cycles = static_cast<float>(ppc::fctiwz(time / cycleTime));
            float fraction = time - cycleTime * cycles;
            fraction = fraction / cycleTime;
            fraction = fraction * frameCount;
            const uint32_t index = static_cast<uint32_t>(ppc::fctidz(fraction));
            const uint32_t row = ppc::divwu(index, w);
            const uint32_t column = index - w * row;
            float u = uStep * static_cast<float>(column);
            float v = vStep * static_cast<float>(row);
            if ((properties & (1u << bitU)) != 0) {  // plus a running U scroll (speed +0x00, accumulator +0x14)
                const float accumulated = ppc::fmadds(WordAsFloat(fx.k2.m_aui32Words[0]), dt, fx.k2.m_fAccumU);
                u = u + accumulated;
                fx.k2.m_fAccumU = accumulated;  // BUG(original): never wrapped, so it loses precision with time
                WrapScroll(&u);
            }
            if ((m_baProperties & (1u << bitV)) != 0) {  // and a V scroll (speed +0x04, accumulator +0x18)
                const float accumulated = ppc::fmadds(WordAsFloat(fx.k2.m_aui32Words[1]), dt, fx.k2.m_fAccumV);
                v = v + accumulated;
                fx.k2.m_fAccumV = accumulated;
                WrapScroll(&v);
            }
            // The matrix becomes a scale (+0x10) with the frame's translation (at.z is cleared too).
            const float scale = fx.k2.m_fFloat10;
            matrix->m_pos.x = u;
            matrix->m_pos.y = v;
            matrix->m_pos.z = 0.0f;
            matrix->m_up.y = scale;
            matrix->m_ui32Flags = 2;
            matrix->m_at.z = 0.0f;
            matrix->m_right.x = scale;
            matrix->m_right.y = 0.0f;
            matrix->m_right.z = 0.0f;
            matrix->m_up.x = 0.0f;
            matrix->m_up.z = 0.0f;
            matrix->m_at.x = 0.0f;
            matrix->m_at.y = 0.0f;
            break;
        }
        case 3: {  // shear wobble: up = (sin(time * frequency (+0x04)) * amplitude (+0x00), 1, 0)
            const float amplitude = fx.k3.m_afFloats[0];
            const float s = UvSine(time * fx.k3.m_afFloats[1]);
            matrix->m_up.y = 1.0f;
            matrix->m_up.z = 0.0f;
            matrix->m_ui32Flags = matrix->m_ui32Flags & 0xfffdfffcu;
            matrix->m_up.x = s * amplitude;
            break;
        }
        case 4: {  // circular wobble: translation = (sin(time * f (+0x04)) * a (+0x00), cos(time * g (+0x20)) * b (+0x18))
            const float sine = UvSine(time * fx.k4.m_afFloats[1]);
            const float cosine = UvCosine(time * fx.k4.m_fFloat20);
            matrix->m_pos.z = 0.0f;
            matrix->m_pos.x = sine * fx.k4.m_afFloats[0];
            matrix->m_pos.y = cosine * fx.k4.m_fFloat18;
            matrix->m_ui32Flags = ClearInternalIdentity(matrix->m_ui32Flags);
            break;
        }
        }
    }
}
