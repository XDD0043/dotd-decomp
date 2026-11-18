// ShaderUniform.cpp - reconstructed original translation unit 0xf5260-0xf7f30 (GAME_TOC1, main_toc1).
// Reconstructed original translation unit: 0xf5260-0xf7f30 (GAME_TOC1, main_toc1), 41 functions, 27 live.
// Primary owner: ShaderUniform (not a registered class)
// Other owners: ShaderPassState (8), ShaderPassStateBase (6), Mat4 (1), GetCurrentTransposedWorldViewProjectionMatrix (1), MeshShaderPassState (1), FillWorldViewProjectionUniformOrIdentity (1), FillShaderUniformFromPassState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xf5260  ShaderPassStateBase_Construct_maybe
//   [ ] 0xf52a8  ShaderPassStateBase_Construct_2_maybe  [dead]
//   [x] 0xf52f0  ShaderPassState_FillAmbientColorUniform_maybe
//   [ ] 0xf5378  FUN_000f5378  [dead]
//   [ ] 0xf5400  FUN_000f5400  [dead]
//   [ ] 0xf5518  ShaderPassState_FillInvRasterSizeUniform_maybe  [dead]
//   [x] 0xf55a8  ShaderPassState_AdvanceToNextPass_maybe
//   [ ] 0xf5698  FUN_000f5698  [dead]
//   [x] 0xf5748  ShaderUniform_ComputeGaussianBlurTaps_maybe
//   [ ] 0xf5e08  ShaderPassState_FillGaussianBlurTapsUniform_maybe  [dead]
//   [x] 0xf5e30  ShaderPassStateBase_maybe_DeletingDestructor  (implicit: ~ShaderPassState (the vtable only), then delete)
//   [x] 0xf5e60  ShaderPassStateBase_maybe_Destructor  (implicit: ~ShaderPassState, the vtable only)
//   [x] 0xf5e70  ShaderPassStateBase_Destruct_maybe  (implicit: ~ShaderPassState, the vtable only)
//   [ ] 0xf5e80  ShaderPassState_FillSkinWeightMaskUniform_maybe  [dead]
//   [x] 0xf5f50  Mat4_SetIdentity44_maybe  (the identity: inline in its only caller MeshShaderPassState::FillWorld)
//   [ ] 0xf5fa0  GetCurrentTransposedWorldViewProjectionMatrix  [dead: no pointer to its descriptor 0xb554a0, no call]
//   [x] 0xf5fd0  ShaderPassState_ApplyUniformEnableFlags0And1_maybe
//   [ ] 0xf6060  ShaderUniform_FillViewportScaleOffset_maybe  [dead: no pointer to its descriptor 0xb554b0, no call (inlined in FillShaderUniformFromPassState's case 0x1f)]
//   [x] 0xf6208  ShaderUniform_FillShadowEntryParams_maybe
//   [x] 0xf62e8  ShaderUniform_FillShadowEntryProjection_maybe
//   [x] 0xf63b8  ShaderPassState_FillPointLightUniforms_maybe  (FillPointLightColors, the dispatcher's cases 7 / 0x16)
//   [ ] 0xf6528  ShaderUniform_FillPointLightPositionsObjectSpace_maybe  [dead: no pointer to its descriptor 0xb554d0, no call (the dispatcher's cases 6 / 0x15: FillPointLightPositions)]
//   [ ] 0xf6670  ShaderUniform_FillLightDirectionsObjectSpace_maybe  [dead: no pointer to its descriptor 0xb554d8, no call (the dispatcher's cases 4 / 0x12: FillDirLightDirections)]
//   [ ] 0xf6788  ShaderUniform_FillFogParams_maybe  [dead: no pointer to its descriptor 0xb554e0, no call (the dispatcher's case 0: FillFogParams)]
//   [x] 0xf68d8  ShaderPassStateBase_maybe_vf90_FillVec4Ones_maybe  (Immediate2DShaderPassState::FillMaterialColor)
//   [ ] 0xf6908  ShaderUniform_FillManagerColorScaledUniform_maybe  [dead]
//   [x] 0xf69c8  MeshShaderPassState_BindFallbackTextureUnit7_maybe  (BindFallbackTextureUnit7, MeshShaderPassState.cpp)
//   [x] 0xf6a00  ShaderPassState_FillDirLightColorUniforms_maybe
//   [ ] 0xf6b48  FUN_000f6b48  [dead]
//   [x] 0xf6c50  ShaderUniform_FillAxisPlaneUniform_maybe  (FillAxisPlane, the dispatcher's cases 0xc / 0x1d)
//   [ ] 0xf6e60  FillWorldViewProjectionUniformOrIdentity  [dead: no pointer to its descriptor 0xb55578, no call (the dispatcher's cases 1 / 0x25)]
//   [ ] 0xf6f30  FUN_000f6f30  [dead]
//   [x] 0xf7008  FillShaderUniformFromPassState
//   [x] 0xf7e58  KStub_Nop_f7e58  (empty: CKGraphic_Update's call does nothing)
//   [x] 0xf7e60  KStub_Nop_f7e60  (empty: the shader manager slot CShaderManagerPSGL_ResetRuntime_maybe calls)
//   [x] 0xf7e68  CShaderManager_InvalidateProfileCapabilities_maybe  (m_bShadersEnabled = 0: inline in ConstructShaderManagerPSGL)
//   [ ] 0xf7e78  FUN_000f7e78  [dead]
//   [ ] 0xf7ea0  KStub_Nop_f7ea0  [dead]
//   [ ] 0xf7ea8  KStub_Return1024_f7ea8  [dead]
//   [ ] 0xf7eb0  KStub_Nop_f7eb0  [dead]
//   [x] 0xf7eb8  MaterialMode_GetMaxShaderSlotCount_maybe
//
//   [ ] 0x9a5a48  ShaderPassStateBase_maybe_vfC  [inline]
//   [ ] 0x9a5a50  ShaderPassStateBase_maybe_vf14  [inline]
//   [ ] 0x9a5a58  ShaderPassStateBase_maybe_vf18  [inline]
//   [ ] 0x9a5a60  ShaderPassStateBase_maybe_vf1C  [inline]
//   [ ] 0x9a5a68  ShaderPassStateBase_maybe_vf24  [inline]
//   [ ] 0x9a5a70  ShaderPassStateBase_maybe_vf28  [inline]
//   [ ] 0x9a5a78  ShaderPassStateBase_maybe_vf2C  [inline]
//   [ ] 0x9a5a80  ShaderPassStateBase_maybe_vf38  [inline]
//   [ ] 0x9a5a88  ShaderPassStateBase_maybe_vf3C  [inline]
//   [ ] 0x9a5a90  ShaderPassStateBase_maybe_vf40  [inline]
//   [ ] 0x9a5a98  ShaderPassStateBase_maybe_vf44  [inline]
//   [ ] 0x9a5aa0  ShaderPassStateBase_maybe_vf48  [inline]
//   [ ] 0x9a5aa8  ShaderPassStateBase_maybe_vf54  [inline]
//   [ ] 0x9a5ab0  ShaderPassStateBase_maybe_vf80  [inline]
//   [ ] 0x9a5ab8  ShaderPassStateBase_maybe_vf84  [inline]
//   [ ] 0x9a5ac0  ShaderPassStateBase_maybe_vf88  [inline]
//   [ ] 0x9a5ac8  ShaderPassStateBase_maybe_vf8C  [inline]
#include "k2000/render/MeshShaderPassState.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/CDOFData.h"
#include "k2000/graphical/memory/CKPBuffer.h"
#include "k2000/graphical/render/CBackgroundCopyRender.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/graphical/render/CLightManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/render/ShaderMatrixCache.h"
#include "k2000/render/ShaderVariantKey.h"
#include "k2000/services/CKSrvShadow.h"

// C2.4 step 3 ports the pass counters (AdvanceToNextPass) and the uniform dispatcher; the fillers it calls are the
// pass state's virtual slots (MeshShaderPassState.cpp). Step 6 adds the light, fog and special light fillers (below the
// pass counters); the shadow and post-effect constants are still the zero state (steps 7-8).

// 0x000f55a8 ShaderPassState_AdvanceToNextPass_maybe: the next pass's light counters. The passes take the lights in
// the order special, scene (directional) and point lights, each pass taking as many as it has slots; +0x07 / +0x08 /
// +0x09 are what the new pass skips. Ported with the original's arithmetic (byte truncations included).
void ShaderPassState::AdvanceToNextPass() {
    const uint32_t passIndex = static_cast<uint32_t>(m_passIndex) + 1;
    m_passIndex = static_cast<uint8_t>(passIndex);
    if (m_passCount <= (passIndex & 0xff)) return;
    uint32_t special = m_specialActive;          // uVar7
    uint32_t consumed = passIndex * m_slotLimit;  // uVar9
    uint32_t uVar6 = special;
    const uint32_t consumedByte = consumed & 0xff;  // uVar3
    uint8_t bVar8 = m_specialActive;
    uint8_t lightCount = m_lightCount;  // bVar1 before reassignment
    uint32_t uVar5, uVar4;
    if (consumedByte < special) {
        special = special - consumed;
        uVar6 = special & 0xff;
        uVar5 = lightCount;
        bVar8 = static_cast<uint8_t>(special);
        m_specialDone = bVar8;
        uVar4 = lightCount + uVar6;
    } else {
        m_specialDone = bVar8;
        uVar5 = lightCount;
        uVar4 = uVar5 + bVar8;
    }
    uint8_t bVar1;
    uint8_t bVar2 = m_pointTouching;
    if (uVar4 < consumedByte) {
        m_dirDone = lightCount;
        bVar1 = lightCount;
        uVar5 = uVar5 + bVar2 + uVar6;
    } else {
        bVar8 = static_cast<uint8_t>(special);
        bVar1 = static_cast<uint8_t>(consumed - special);
        uVar5 = ((consumed - special) & 0xff) + bVar2 + uVar6;
        m_dirDone = bVar1;
    }
    if (uVar5 < consumedByte) {
        m_pointDone = bVar2;
        m_slotsUsed = 0;
        return;
    }
    m_pointDone = static_cast<uint8_t>((static_cast<uint8_t>(consumed) - bVar1) - bVar8);
    m_slotsUsed = 0;
}

// ==== the light, fog and special light fillers (C2.4 step 6) ===========================================================
namespace {
CLightManager* Lights() { return g_pLightManager; }

// 0x000f6788 ShaderUniform_FillFogParams_maybe (the VSC_FOG case): (fog start, fog end, the fog flag, 0) of the current camera
// while the pass has fog on, else zeros.
void FillFogParams(ShaderPassState* pass, float* dst) {
    dst[0] = dst[1] = dst[2] = dst[3] = 0.0f;
    if ((pass->IsFogEnabled() & 0xff) == 0) return;
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    dst[0] = camera->GetFogStart();
    dst[1] = camera->GetFogEnd();
    dst[3] = 0.0f;
    dst[2] = static_cast<float>(pass->FogFlag() & 0xff);
}

// Cases 4 and 0x12: the directions of the rig's distinct lights in object space, one float4 each, as many as the pass has not
// taken (4 - lights taken so far). The walk over the rig starts at light 0 in every call (the original's index variable is
// cleared each time), so a later pass lists the first lights again.
void FillDirLightDirections(const ShaderPassState* pass, float* dst) {
    uint32_t taken = pass->m_dirDone;
    if (taken >= 4) return;
    uint32_t index = 0;
    do {
        ++taken;
        CVector3 direction = {0.0f, 0.0f, 0.0f};
        uint32_t color = 0;
        index = Lights()->GetNextDistinctLight(index, &direction, &color);
        const float world[3] = {direction.x, direction.y, direction.z};
        float object[3];
        ShaderMatrixCache_WorldDirToObject(world, object);
        dst[0] = object[0];
        dst[1] = object[1];
        dst[2] = object[2];
        if (taken > 3) return;
        dst += 4;
    } while (index < 4);
}

// Cases 6 and 0x15: the positions (object space) and radii of the pass's point lights (those the earlier passes did not take).
void FillPointLightPositions(const ShaderPassState* pass, float* dst) {
    const uint32_t first = pass->m_pointDone;
    for (uint32_t i = first; i < first + pass->m_pointAllocated; ++i) {
        CVector3 position;
        Lights()->GetLightPosition(&position, static_cast<int32_t>(i));
        const float world[3] = {position.x, position.y, position.z};
        float object[3];
        ShaderMatrixCache_WorldPointToObject(world, object);
        dst[0] = object[0];
        dst[1] = object[1];
        dst[2] = object[2];
        dst[3] = Lights()->GetLightRadius(static_cast<int32_t>(i));
        dst += 4;
    }
}

// Cases 7 and 0x16 (0x000f63b8 ShaderPassState_FillPointLightUniforms_maybe): the colours of the pass's point lights, red,
// green and blue over 255, and the intensity-ish float plus one.
void FillPointLightColors(const ShaderPassState* pass, float* dst) {
    const uint32_t first = pass->m_pointDone;
    for (uint32_t i = first; i < first + pass->m_pointAllocated; ++i) {
        uint8_t color[4];
        Lights()->GetLightColor(color, static_cast<int32_t>(i));
        dst[0] = static_cast<float>(color[0]) / 255.0f;
        dst[1] = static_cast<float>(color[1]) / 255.0f;
        dst[2] = static_cast<float>(color[2]) / 255.0f;
        dst[3] = Lights()->GetLightField1C(static_cast<int32_t>(i)) + 1.0f;
        dst += 4;
    }
}

float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}

// Cases 0xc and 0x1d (0x000f6c50 ShaderUniform_FillAxisPlaneUniform_maybe): the special light is a plane along an axis:
// (1, 0, 0, the shader manager's +0x80 float) once the pass has taken the special light, else (0, -1, 0, its +0x7c float)
// (both from the level's shader manager block: 1.0 and 0.2 in LVL000). The original also computes the lengths of the manager's
// two vectors at +0x64 / +0x70 and their object-space transforms, and uses none of them.
void FillAxisPlane(const ShaderPassState* pass, float* dst) {
    if (pass->m_specialDone != 0) {
        dst[0] = 1.0f;
        dst[1] = 0.0f;
        dst[2] = 0.0f;
        dst[3] = WordAsFloat(g_pShaderManager->m_unk7c[1]);
        return;
    }
    dst[0] = 0.0f;
    dst[1] = -1.0f;
    dst[2] = 0.0f;
    dst[3] = WordAsFloat(g_pShaderManager->m_unk7c[0]);
}
}  // namespace

// 0x000f62e8 ShaderUniform_FillShadowEntryProjection_maybe (VSC_INFOQUAD_SHADOW): the current sector's shadow scale (1 when it is
// 0), the other scale and the origin's x and z.
void FillShadowEntryProjection(float* dst) {
    const CKSrvShadow* shadow = static_cast<const CKSrvShadow*>(g_pEngine->m_srvShadow);
    const uint32_t sector = shadow->m_unk0c;
    float scale = shadow->GetEntryFloat18(sector);
    if (scale == 0.0f) scale = 1.0f;
    dst[0] = scale;
    dst[1] = shadow->GetEntryFloat1C(sector);
    const float* origin = shadow->GetEntryOrigin(sector);
    dst[2] = origin[0];
    dst[3] = origin[2];
}

// 0x000f6208 ShaderUniform_FillShadowEntryParams_maybe (PSC_MINMAX_SHADOW): the entry's two heights and, with a texture, its +0x20.
void FillShadowMinMax(float* dst) {
    const CKSrvShadow* shadow = static_cast<const CKSrvShadow*>(g_pEngine->m_srvShadow);
    const uint32_t sector = shadow->m_unk0c;
    dst[0] = shadow->GetEntryFloat10(sector);
    dst[1] = shadow->GetEntryFloat14(sector);
    dst[2] = shadow->EntryHasTexture(sector) != 0 ? WordAsFloat(shadow->m_unk30.m_pBlock[sector].m_unk20) : 0.0f;
}

// 0x000f6a00 ShaderPassState_FillDirLightColorUniforms_maybe: the colours of the rig's distinct lights as float4 (each byte
// over 255), as many as the pass has not taken; the walk starts at light 0 (see FillDirLightDirections).
void FillDirLightColorUniforms(const ShaderPassState* pass, float* dst) {
    uint32_t taken = pass->m_dirDone;
    if (taken >= 4) return;
    uint32_t index = 0;
    do {
        ++taken;
        CVector3 direction = {0.0f, 0.0f, 0.0f};
        uint32_t color = 0;
        index = Lights()->GetNextDistinctLight(index, &direction, &color);
        dst[0] = static_cast<float>(color >> 24) / 255.0f;
        dst[1] = static_cast<float>((color >> 16) & 0xff) / 255.0f;
        dst[2] = static_cast<float>((color >> 8) & 0xff) / 255.0f;
        dst[3] = static_cast<float>(color & 0xff) / 255.0f;
        if (taken > 3) return;
        dst += 4;
    } while (index < 4);
}

namespace {
CameraContext* CameraContextOf() { return static_cast<CameraContext*>(g_pEngine->m_cameraContext); }
const CPostRenderingFx* PostRenderingFx() {
    return static_cast<const CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d));
}
bool DepthOfFieldPath(const CPostRenderingFx* postFx) {
    return (g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 && g_pShaderManager->m_bShadersEnabled != 0 &&
           g_pShaderManager->m_i32ProfileMode == 6 && (postFx->m_BitProperties & 0x400) != 0;
}

// One tap of ShaderUniform_ComputeGaussianBlurTaps_maybe: exp(-(x^2 + y^2) / 2) / sqrt(2 pi) with the routine's inline
// exponential (2^ceil(t) times a polynomial for e^-f, f = (ceil(t) - t) ln 2, t = v log2 e), as the assembly computes it.
float GaussianTapWeight(float x, float ySquared) {
    const float log2e = 0x1.715476p+0f;   // TOC -0x4b20 0x3fb8aa3b
    const float ln2 = 0x1.62e430p-1f;     // TOC -0x4b1c 0x3f317218
    const float c1 = -0x1.55549ep-3f;     // TOC -0x4b18 0xbe2aaa4f
    const float c2 = 0x1.fffffap-2f;      // TOC -0x4b14 0x3efffffd
    const float c3 = -0x1.285c80p-13f;    // TOC -0x4b10 0xb9142e40
    const float c4 = 0x1.5c9edep-10f;     // TOC -0x4b0c 0x3aae4f6f
    const float c5 = 0x1.1004dap-7f;      // TOC -0x4b08 0x3c08026d
    const float c6 = 0x1.5541cap-5f;      // TOC -0x4b04 0x3d2aa0e5
    const float one = 1.0f, minusTwo = -2.0f, twoPi = 0x1.921fb6p+2f;  // TOC -0x4b00 0x40c90fdb
    const float t = (ppc::fmadds(x, x, ySquared) / minusTwo) * log2e;
    // The integer part rounded up: t plus 0.99999994 when t's sign bit is clear (srawi 31 / andc on the bits).
    uint32_t bits;
    std::memcpy(&bits, &t, 4);
    const uint32_t biasBits = 0x3f7fffffu & ~static_cast<uint32_t>(static_cast<int32_t>(bits) >> 31);
    float bias;
    std::memcpy(&bias, &biasBits, 4);
    const int32_t n = ppc::fctiwz(t + bias);
    const float f = (static_cast<float>(n) - t) * ln2;
    const float a = ppc::fmadds(f, c1, c2);
    const float b = ppc::fmadds(f, c3, c4);
    const float f2 = f * f;
    const float p = ppc::fmsubs(f, a, one);
    const float q = ppc::fmsubs(f, b, c5);
    const float f4 = f2 * f2;
    const float r = ppc::fmadds(f, p, one);
    const float s = ppc::fmadds(f, q, c6);
    const float poly = ppc::fmadds(f4, s, r);
    const uint32_t scaleBits = static_cast<uint32_t>(n + 0x7f) << 23;  // 2^n as float bits
    float scale;
    std::memcpy(&scale, &scaleBits, 4);
    float value = poly * scale;
    uint32_t polyBits;
    std::memcpy(&polyBits, &poly, 4);
    const uint32_t exponent = (polyBits >> 23) + static_cast<uint32_t>(n);
    if (exponent > 0xff) {
        const uint32_t overflow = static_cast<uint32_t>(static_cast<int32_t>(~exponent) >> 31) & 0x7f800000u;
        std::memcpy(&value, &overflow, 4);
    }
    return value / std::sqrt(twoPi);  // fsqrts
}
}  // namespace

// 0x000f5748 ShaderUniform_ComputeGaussianBlurTaps_maybe(multiplier, width, height, offsets, weights): the taps of a
// 5 x 5 Gaussian (deviation 1) inside the diamond |x| + |y| <= 2 (13 taps; x from -2 to 2, y from -2 to 2 within it):
// offsets (x / w, y / h, 0, 0), weights (w, w, w, w), the weights' 4 * 13 floats then divided by their sum and multiplied.
// The Cg's GaussBlur5x5PS reads only the first 12 taps (BUG(original): the last one, (2, 0), is left out of the sum).
void ComputeGaussianBlurTaps(float multiplier, int32_t width, int32_t height, float* offsets, float* weights) {
    const float one = 1.0f;
    const float invWidth = one / static_cast<float>(width);
    const float invHeight = one / static_cast<float>(height);
    float sum = 0.0f;
    uint32_t count = 0;  // floats written
    const float two = 2.0f;
    for (int32_t i = -2; i <= 2; ++i) {
        const float x = static_cast<float>(i);
        const float ax = std::fabs(x);
        const struct {
            float dy;       // the y offset in texels
            float ySquared;
            float margin;   // |x| + margin <= 2
        } rows[5] = {{-2.0f, 4.0f, 2.0f}, {-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {2.0f, 4.0f, 2.0f}};
        for (const auto& row : rows) {
            if (!(ax + row.margin <= two)) continue;
            float* o = offsets + count;
            o[3] = 0.0f;
            o[2] = 0.0f;
            o[0] = invWidth * x;
            // y offsets: -2 h (fmuls by -2), -h (fneg), h * 0, h, h + h (fadds)
            if (row.dy == -2.0f) o[1] = invHeight * -2.0f;
            else if (row.dy == -1.0f) o[1] = -invHeight;
            else if (row.dy == 0.0f) o[1] = invHeight * 0.0f;
            else if (row.dy == 1.0f) o[1] = invHeight;
            else o[1] = invHeight + invHeight;
            const float w = GaussianTapWeight(x, row.ySquared);
            float* out = weights + count;
            count += 4;
            sum = sum + w;
            out[3] = w;
            out[0] = w;
            out[1] = w;
            out[2] = w;
        }
    }
    for (uint32_t k = 0; k < count; ++k) weights[k] = (weights[k] / sum) * multiplier;
}

// 0x000f7008 FillShaderUniformFromPassState: the 40-case dispatcher over the uniform records' ids (ShaderUniformId).
// `dst` is the record's destination (+0x0c) of the uniform. The cases the original sends to the pass state's
// virtual slots do the same here.
void FillShaderUniformFromPassState(ShaderPassState* pass, int32_t id, float* dst) {
    switch (id) {
        case kVscFog:  // 0: the fog start / end and the fog flag (CKSrvCamera_GetFogStart / End, vt+0x28)
            FillFogParams(pass, dst);
            break;
        case kVscWorldViewProj:  // 1
        case kPscWorldViewProj:  // 0x25
            if (pass->ModulateMaterial() != 0) {
                GetTransposedWorldViewProjectionMatrix(dst);
            } else {
                for (int i = 0; i < 16; ++i) dst[i] = (i % 5 == 0) ? 1.0f : 0.0f;
            }
            break;
        case kVscAmbientColor:  // 2
        case kPscAmbientColor:  // 0x14
            pass->FillAmbientColor(dst);
            break;
        case kVscMaterialColor:  // 3
        case kPscMaterialColor:  // 0x1b
            pass->FillMaterialColor(dst);
            break;
        case kVscDirLightDir:  // 4: the directional lights' directions in object space (LightRig_GetNextDistinctLight)
        case kPscDirLightDir:  // 0x12
            FillDirLightDirections(pass, dst);
            break;
        case kVscDirLightColor:  // 5
        case kPscDirLightColor:  // 0x13
            pass->FillDirLightColors(dst);
            break;
        case kVscPointLightPos:  // 6
        case kPscPointLightPos:  // 0x15
            FillPointLightPositions(pass, dst);
            break;
        case kVscPointLightColor:  // 7
        case kPscPointLightColor:  // 0x16
            FillPointLightColors(pass, dst);
            break;
        case kVscUvTransform:  // 8
            pass->FillUvTransform(dst);
            break;
        case kVscViewPomHeight:  // 9
            pass->FillViewPomHeight(dst);
            break;
        case kVscSpecular:  // 10
        case kPscSpecular:  // 0x19
            pass->FillSpecular(dst);
            break;
        case kVscDualUvTransform:  // 0xb
            pass->FillDualUvTransform(dst);
            break;
        case kVscSpecialLight:  // 0xc: ShaderUniform_FillAxisPlaneUniform_maybe 0xf6c50 (the special light)
        case kPscSpecialLight:  // 0x1d
            FillAxisPlane(pass, dst);
            break;
        case kVscWorldView:  // 0xd
            pass->FillWorldView(dst);
            break;
        case kVscWorld:  // 0xe
            pass->FillWorld(dst);
            break;
        case kVscInfoQuadShadow:  // 0xf: the shadow service's entry (CKSrvShadow_GetEntryFloat18 ...), 0x000f62e8
            FillShadowEntryProjection(dst);
            break;
        case kVscBoneWeight: {  // 0x10: 1 for each skin weight the vertex has (vt+0x20)
            dst[0] = dst[1] = dst[2] = dst[3] = 0.0f;
            const uint32_t weights = pass->MaxSkinWeights() & 0xff;
            for (uint32_t i = 0; i < weights && i < 4; ++i) dst[i] = 1.0f;
            break;
        }
        case kVscBoneMatrices:  // 0x11
            pass->FillSkinBoneMatrices(dst);  // FillSkinBoneMatrixPaletteUniform 0xeea50
            break;
        case kPscNormalParam:  // 0x17
            pass->FillNormalParam(dst);
            break;
        case kPscPomTextureShadow:  // 0x18
            pass->FillPomTextureShadow(dst);
            break;
        case kPscSpecularColor:  // 0x1a
            pass->FillExtColor(dst);
            break;
        case kPscMaterialFx:  // 0x1c
            pass->FillEnvMapCoefficients(dst);
            break;
        case kPscDofParam: {  // 0x1e: the DOF data's four words (+0x50 -> +4..+0x10) on the depth of field path
            const CPostRenderingFx* postFx = PostRenderingFx();
            if (postFx != nullptr && DepthOfFieldPath(postFx)) std::memcpy(dst, &static_cast<const CDOFData*>(postFx->m_pDOFData)->m_fFocusDistance, 16);
            break;
        }
        case kPscDofAdjustTex: {  // 0x1f: the alternative scene raster's rectangle in its parent (scale, offset)
            const RwRaster* raster = CameraContextOf()->m_unk10;
            const RwRaster* parent = raster->parent;
            if (raster == parent) {
                dst[0] = 1.0f;
                dst[1] = 1.0f;
                dst[3] = 0.0f;
                dst[2] = 0.0f;
            } else {
                const double parentWidth = static_cast<double>(parent->width), parentHeight = static_cast<double>(parent->height);
                // RwRasterGetOffset
                dst[0] = static_cast<float>(static_cast<double>(raster->width) / parentWidth);
                dst[1] = static_cast<float>(static_cast<double>(raster->height) / parentHeight);
                dst[2] = static_cast<float>(static_cast<double>(raster->nOffsetX) / parentWidth);
                dst[3] = static_cast<float>(static_cast<double>(raster->nOffsetY) / parentHeight);
            }
            break;
        }
        case kPscDofPixelSize: {  // 0x20: a quarter and a whole texel of the alternative scene raster
            const RwRaster* raster = CameraContextOf()->m_unk10;
            if (raster != nullptr) {
                const int32_t width = raster->width, height = raster->height;
                dst[0] = 0.25f / static_cast<float>(width);
                dst[1] = 0.25f / static_cast<float>(height);
                dst[2] = 1.0f / static_cast<float>(width);
                dst[3] = 1.0f / static_cast<float>(height);
            }
            break;
        }
        case kPscDofRadius: {  // 0x21: the post object's +0x58 / +0x5c / +0x60 on the depth of field path
            const CPostRenderingFx* postFx = PostRenderingFx();
            if (postFx != nullptr && DepthOfFieldPath(postFx)) {
                dst[0] = postFx->m_unk58;
                dst[1] = postFx->m_unk5c;
                dst[2] = postFx->m_unk60;
                dst[3] = 0.0f;
            }
            break;
        }
        case kPscFarCamera: {  // 0x22: (the main camera's far plane, the far-texture object's +0x1c); the original reads the
            // object without a test (DEV guard: none, 0)
            const CBackgroundCopyRender* farTexture =
                static_cast<const CBackgroundCopyRender*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x4d0d));
            const float tolerance = farTexture != nullptr ? farTexture->m_unk1c : 0.0f;
            dst[0] = CameraContextOf()->m_pMainCamera->farPlane;
            dst[1] = tolerance;
            break;
        }
        case kPscDownSample: {  // 0x26: 16 taps over the full-size shared raster: x (-2.5, -1.5, -0.5, 0.5), y (row - 2.5) in
            // units of 4 texels
            const RwRaster* shared = CKPBuffer::m_spaSharedRasters[0];
            const float one = 1.0f;
            const float invHeight = one / static_cast<float>(ppc::divw(shared->height, 4));  // srawi 2, addze
            const float invWidth = one / static_cast<float>(ppc::divw(shared->width, 4));
            float* out = dst;
            for (int32_t row = 0; row < 4; ++row) {
                out[0] = invWidth * -2.5f;
                out[2] = invWidth * -1.5f;
                out[4] = invWidth * -0.5f;
                out[6] = invWidth * 0.5f;
                const float y = (static_cast<float>(row) - 2.5f) * invHeight;
                out[7] = y;
                out[1] = y;
                out[3] = y;
                out[5] = y;
                out += 8;
            }
            break;
        }
        case kPscGauss5x5:  // 0x27: the 5x5 Gaussian taps of the full-size shared raster (offsets, then the weights at +0x100)
            ComputeGaussianBlurTaps(1.0f, CKPBuffer::m_spaSharedRasters[0]->width, CKPBuffer::m_spaSharedRasters[0]->height, dst, dst + 64);
            break;
        case kPscMinMaxShadow:  // 0x24
            FillShadowMinMax(dst);
            break;
        case kPscAnim:  // 0x23
            pass->FillAnim(dst);
            break;
        default:
            break;
    }
}

// 0x000f5fd0 ShaderPassState_ApplyUniformEnableFlags0And1_maybe: the two boolean constants (vt+0x4c = 0, vt+0x3c).
uint32_t ShaderPassState_EnableFlag(ShaderPassState* pass, int slot) {
    return slot == 0 ? 0u : (pass->ModulateVertexColorFirst() & 0xff);
}
