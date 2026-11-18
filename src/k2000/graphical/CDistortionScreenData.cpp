// CDistortionScreenData.cpp - reconstructed original translation unit 0xb1580-0xb3170 (GAME_TOC1, main_toc1), 32 functions, 29 live.
// Primary class: CDistortionScreenData  key 0xc8d  category Graphical  size 0x30  vtable 0xb175b0
// Other owners: CDistortionScreenFx (10), RegisterCDistortionScreenFxAndDataClasses (1), EvaluateDistortionVertex (1), RenderDistortionGridWarp (1), CLensFlareFx (1), CLensFlareData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xb1580  CDistortionScreenData_GetMaxAbsCurveValue_maybe  [dead]
//   [ ] 0xb1628  CDistortionScreenData_EvaluateCurve_maybe  [dead]
//   [ ] 0xb16c0  CDistortionScreenData_Save
//   [x] 0xb16c8  CDistortionScreenData_PostLoad  (CDistortionScreenData.h)
//   [x] 0xb16d0  CDistortionScreenData_vf58  (KUPostLoadVersionUpdate, CDistortionScreenData.h)
//   [x] 0xb16d8  CDistortionScreenData_RecursiveRegistration
//   [ ] 0xb1738  RegisterCDistortionScreenFxAndDataClasses
//   [ ] 0xb17f0  _GLOBAL__I_b17f0
//   [x] 0xb1800  CDistortionScreenData_Destroy
//   [x] 0xb1850  CDistortionScreenData_DeleteArray
//   [x] 0xb18f8  CDistortionScreenFx_DeleteArray
//   [ ] 0xb19a0  CDistortionScreenData_InitDefaults_maybe  [dead]
//   [x] 0xb1a68  EvaluateDistortionVertex_maybe
//   [x] 0xb1d20  CDistortionScreenFx_BuildGrid_maybe
//   [x] 0xb1f78  CDistortionScreenData_Create
//   [x] 0xb1fb0  CDistortionScreenFx_Create
//   [x] 0xb2008  CDistortionScreenData_Reset_maybe
//   [x] 0xb2038  CDistortionScreenData_SetSource_maybe
//   [x] 0xb2080  CDistortionScreenData_vf54  (KUDestroy)
//   [x] 0xb20d0  CDistortionScreenData_CreateArray
//   [x] 0xb2168  CDistortionScreenFx_CreateArray
//   [x] 0xb2220  CDistortionScreenFx_RecursiveRegistration
//   [x] 0xb2280  CDistortionScreenFx_PostLoad
//   [x] 0xb22e0  CDistortionScreenFx_Destroy
//   [ ] 0xb2350  CDistortionScreenFx_Save
//   [x] 0xb2378  CDistortionScreenFx_Load
//   [x] 0xb2428  RenderDistortionGridWarp
//   [x] 0xb2c88  CDistortionScreenFx_Draw
//   [x] 0xb2d28  CDistortionScreenData_Load
//   [x] 0xb3008  CDistortionScreenData_vf50  (KUInitialize)
//   [x] 0xb30d0  CLensFlareFx_Delete  (DOTD_DECLARE_FACTORIES(CLensFlareFx))
//   [x] 0xb3120  CLensFlareData_Delete  (DOTD_DECLARE_FACTORIES(CLensFlareData))
//
//   [x] 0x9a0968  CDistortionScreenData_GetClassType  [inline]
//   [x] 0x9a0970  CDistortionScreenData_GetClassID  [inline]
//   [x] 0x9a0978  CDistortionScreenFx_GetClassType  [inline]
//   [x] 0x9a0980  CDistortionScreenFx_GetClassID  [inline]
//   [x] 0x9a0988  CDistortionScreenFx_GetSerializationFlags  [inline]
//   [x] 0x9a0990  CDistortionScreenData_IsKindOfClass  [inline]
//   [x] 0x9a09b0  CDistortionScreenFx_IsKindOfClass  [inline]
//   [x] 0x9a09e8  CDistortionScreenFx_DeletingDestructor  [inline]
//   [x] 0x9a0a30  CDistortionScreenData_DeletingDestructor  [inline]
//   [x] 0x9a0a70  CDistortionScreenData_Destructor  [inline]
//   [x] 0x9a0a88  CDistortionScreenFx_Destructor  [inline]
#include "k2000/graphical/CDistortionScreenData.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm2D.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
#include "crt/ppc_ops.h"
#include "crt/xpowfast.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/CDistortionScreenFx.h"
#include "k2000/graphical/memory/CKPBuffer.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {
// count little-endian words read in one block, then each byte-swapped (lwbrx on the PS3).
void SwapWordsLE(const uint8_t* bytes, void* dst, uint32_t count) {
    uint8_t* out = static_cast<uint8_t*>(dst);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t bits = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(out + 4 * i, &bits, 4);
    }
}
}  // namespace

// 0x000b1fb0 CDistortionScreenFx_Create: the inlined IRendableObject part, in the original's store order.
CDistortionScreenFx::CDistortionScreenFx() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x000b2378 CDistortionScreenFx_Load
int32_t CDistortionScreenFx::Load(IKFile* file, int32_t type) {
    IScreenFx::Load(file, type);  // the original calls IRendableObject_Load (IScreenFx_Load inlined)
    if (type == K_LEVEL_PLATEFORMS) {
        m_unk28 = 0;
        m_unk30 = nullptr;
        m_unk34 = nullptr;
        ReadU8(file, &m_ui8Resol);
    }
    return 1;
}

// 0x000b2d28 CDistortionScreenData_Load
int32_t CDistortionScreenData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pv2Amplitude = nullptr;
    ReadF32LE(file, &m_fDuration);
    ReadF32LE(file, &m_fDampCoeff);
    ReadF32LE(file, &m_fAmpThreshold);
    ReadRaw(file, m_cColor, 4);  // not swapped by the original
    ReadU32LE(file, &m_ui32NbAmplitudePoints);
    m_pv2Amplitude = new CVector2[m_ui32NbAmplitudePoints];  // OperatorNewArray(count * 8 + 4), count cookie
    const uint32_t bytes = m_ui32NbAmplitudePoints * 8;
    uint8_t* raw = new uint8_t[bytes != 0 ? bytes : 1];
    file->Read(raw, bytes);  // one read, then 2 * count words swapped
    SwapWordsLE(raw, m_pv2Amplitude, m_ui32NbAmplitudePoints * 2);
    delete[] raw;
    uint8_t offset[0xc];
    file->Read(offset, 0xc);
    SwapWordsLE(offset, &m_v3OffsetPos, 3);
    return 1;
}

// 0x000b2280 CDistortionScreenFx_PostLoad
int32_t CDistortionScreenFx::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_BitProperties &= 0xfffffcffu;
    m_pSource = nullptr;
    m_fTime = 0.0f;
    m_unk1c = nullptr;
    m_pCenter = nullptr;
    BuildGrid();  // 0x000b1d20
    return 1;
}

// 0x000b22e0 CDistortionScreenFx_Destroy
void CDistortionScreenFx::Destroy() {
    IRendableObject::Destroy();  // 0x000a7248
    if (m_unk30 != nullptr) {
        Mem_FreeAligned16(m_unk30);
        m_unk30 = nullptr;
    }
    if (m_unk34 != nullptr) {
        Mem_FreeAligned16(m_unk34);
        m_unk34 = nullptr;
    }
}

// 0x000b1d20 CDistortionScreenFx_BuildGrid_maybe
void CDistortionScreenFx::BuildGrid() {
    const uint32_t n = m_ui8Resol;
    m_unk28 = n * 4 + n + (n * 2 - 2) * (n - 1) - 6;
    if (m_unk30 != nullptr) Mem_FreeAligned16(m_unk30);  // 0x00052fb8
    if (m_unk34 != nullptr) Mem_FreeAligned16(m_unk34);
    m_unk30 = Mem_AllocAligned16((n * n * 4 + n * n * 32) & 0x003ffffcu);  // 0x00053198; 0x24 per vertex
    RwImVertexIndex* indices = static_cast<RwImVertexIndex*>(Mem_AllocAligned16(m_unk28 * 4));
    m_unk34 = indices;
    // The first column pair, then per row the pairs of its other columns and, but after the last two rows, the join
    // to the next row (the last index again, then the next row's first index twice, its second and the row after's
    // first). The resolution is read again from the object at each step, as the original.
    indices[0] = 0;
    indices[1] = m_ui8Resol;
    indices[2] = 1;
    indices[3] = static_cast<RwImVertexIndex>(m_ui8Resol + 1);
    if (m_ui8Resol == 1) return;
    uint32_t at = 4;
    for (uint32_t row = 0;;) {
        const uint32_t size = m_ui8Resol;
        const uint32_t base = row * size;
        uint32_t last = base;
        for (uint32_t column = 1; column < m_ui8Resol; ++column) {
            last = column + base;
            indices[at] = last;
            indices[at + 1] = last + m_ui8Resol;
            at += 2;
        }
        if (row < static_cast<uint8_t>(m_ui8Resol - 2)) {
            const uint32_t next = row + 1;
            indices[at] = last + m_ui8Resol;
            indices[at + 1] = next * m_ui8Resol;
            indices[at + 2] = next * m_ui8Resol;
            indices[at + 3] = next * m_ui8Resol + 1;
            indices[at + 4] = (row + 2) * m_ui8Resol;
            at += 5;
        }
        ++row;
        if (!(static_cast<uint8_t>(row) < static_cast<uint8_t>(m_ui8Resol - 1))) return;
    }
}

namespace {
// 0x000b1a68 EvaluateDistortionVertex_maybe: the texture coordinate `uv` of the grid point at `point` (both in 0..1 of
// the screen), pushed away from the warp's centre `center` by the amplitude (+0x2c) times e^(-distance x damping
// (+0x20)), at most the distance itself, clamped to 1e-5..1; `alpha` the push over the threshold (+0x1c) in 255ths
// (255 above it). The e^ is the library's fast 2^ (Math_Exp2Fast_maybe 0x781558) inlined, of the value times log2 e.
void EvaluateDistortionVertex(const CDistortionScreenData* data, uint8_t* alpha, float* uv, const float* point,
                              const float* center) {
    float dy = center[1] - point[1];
    float dx = center[0] - point[0];
    const float length = std::sqrt(ppc::fmadds(dx, dx, dy * dy));  // Math_Sqrtf 0x10690
    float distance = length;
    float negative;
    if (length != 0.0f) {
        negative = -length;
        const float inverse = 1.0f / length;
        dy = dy * inverse;
        dx = dx * inverse;
    } else {
        distance = 0.0f;
        negative = -0.0f;  // TOC -0x5db8
    }
    const float falloff = crt::Exp2Fast(negative * data->m_fDampCoeff * 1.44269502e+00f);  // TOC -0x5db4 (log2 e)
    float push = data->m_fAmp * falloff;
    if (!(distance > push)) push = distance;  // bgt
    const float ratio = std::fabs(push) / data->m_fAmpThreshold;
    *alpha = ratio <= 1.0f ? static_cast<uint8_t>(ppc::fctiwz(ratio * 255.0f)) : 0xff;  // ble; TOC -0x5d94
    float u = ppc::fmadds(dx, push, point[0]);
    const float v = ppc::fmadds(dy, push, point[1]);
    uv[0] = u;
    uv[1] = v;
    const float kMin = 9.99999975e-06f;  // TOC -0x5d90
    if (u <= kMin) {
        u = kMin;
    } else if (u >= 1.0f) {
        u = 1.0f;
    }
    uv[0] = u;
    float w = uv[1];
    if (w <= kMin) {
        w = kMin;
    } else if (w >= 1.0f) {
        w = 1.0f;
    }
    uv[1] = w;
}
}  // namespace

// 0x000b2428 RenderDistortionGridWarp: the effect runs while the source's duration is above `time`. With the post
// effects (graphic caps 0x400): the warp's centre on the screen (0.5, 0.5 without one; the node's LTM position, else the
// centre point, plus the source's offset, projected and divided by the final colour raster's size), the amplitude curve
// read at `time` (+0x2c, piecewise linear, 0 outside it) and its largest |value| (+0x18); while it runs, every grid
// point (n x n over the current camera's raster, at the middle screen z) takes the warped coordinate into the scene
// colour copy (CKPBuffer's full-size shared raster) with the source's colour and the push's alpha, and the grid is drawn
// as one Im2D triangle strip (no Z, no culling, no fog, clamped, filtered, alpha test always, vertex alpha, the alpha
// blend, Gouraud) between PushRenderStates / PopRenderStates.
uint8_t RenderDistortionGridWarp(CDistortionScreenFx* fx, float time, IKSerializable* centerNode, const CVector3* center,
                                 CDistortionScreenData* data) {
    const uint8_t running = data->m_fDuration > time ? 1 : 0;  // bgt
    if ((g_pEngine->m_graphic->m_baHardwareCaps & 0x400) == 0) return running;
    RwRaster* scene = CKPBuffer::m_spaSharedRasters[0];  // 0x00c5c8d0
    CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
    const float last = static_cast<float>(static_cast<double>(static_cast<int32_t>(fx->m_ui8Resol) - 1));
    const float nearZ = RwIm2DGetNearScreenZ();  // RWEngine +0x18
    const float farZ = RwIm2DGetFarScreenZ();    // RWEngine +0x1c
    const RwRaster* target = RwDevice_GetCurrentCamera()->frameBuffer;  // RWEngine +0 (the current camera) +0x60
    const float recipZ = 1.0f / context->m_pMainCamera->nearPlane;
    const float step = 1.0f / last;
    const float rowStep = static_cast<float>(static_cast<double>(target->height)) / last;
    const float columnStep = static_cast<float>(static_cast<double>(target->width)) / last;
    float screen[2] = {0.5f, 0.5f};  // TOC -0x5d78
    const CVector3& offset = data->m_v3OffsetPos;
    bool project = false;
    RwV3d position;
    if (centerNode != nullptr) {
        const RwMatrix& ltm = static_cast<CSGMovable*>(centerNode)->m_pRwFrame->ltm;
        position = {ltm.pos.x + offset.x, ltm.pos.y + offset.y, ltm.pos.z + offset.z};
        project = true;
    } else if (center != nullptr) {
        position = {center->x + offset.x, center->y + offset.y, center->z + offset.z};
        project = true;
    }
    if (project) {
        ProjectWorldPointToScreen(context, &position, screen, 1);  // 0x000a30c0
        float width = 0.0f;
        if (context->m_pFinalColorRaster != nullptr) width = static_cast<float>(static_cast<uint32_t>(context->m_pFinalColorRaster->width));
        screen[0] = screen[0] / width;
        float height = 0.0f;
        if (context->m_pFinalColorRaster != nullptr) height = static_cast<float>(static_cast<uint32_t>(context->m_pFinalColorRaster->height));
        screen[1] = screen[1] / height;
    }
    const float z = (nearZ + farZ) * 0.5f;
    // The amplitude at `time`: the curve's segment holding it (above its start, at most its end), linear.
    const uint32_t count = data->m_ui32NbAmplitudePoints;
    float amplitude = 0.0f;
    if (count > 1) {
        const CVector2* points = data->m_pv2Amplitude;
        for (uint32_t i = 0; i + 1 < count; ++i) {
            if (time > points[i].m_fX && time <= points[i + 1].m_fX) {
                const float t = (time - points[i].m_fX) / (points[i + 1].m_fX - points[i].m_fX);
                amplitude = ppc::fmadds(t, points[i + 1].m_fY - points[i].m_fY, points[i].m_fY);
                break;
            }
        }
    }
    data->m_fAmp = amplitude;
    float largest = 0.0f;
    if (count != 0) {
        largest = std::fabs(data->m_pv2Amplitude[0].m_fY);
        for (uint32_t i = 1; i < count; ++i) {
            const float value = std::fabs(data->m_pv2Amplitude[i].m_fY);
            if (!(value < largest)) largest = value;  // blt
        }
    }
    data->m_fMaxAmp = largest;
    if (running == 0) return 0;
    const uint32_t size = fx->m_ui8Resol;
    if (size != 0) {
        RwIm2DVertex* grid = static_cast<RwIm2DVertex*>(fx->m_unk30);
        float point[2] = {0.0f, 0.0f};  // sp+0x88: the grid point in 0..1
        uint32_t k = 0;
        for (uint32_t row = 0; row < fx->m_ui8Resol; ++row) {
            const float y = rowStep * static_cast<float>(static_cast<double>(row));
            for (uint32_t column = 0; column < fx->m_ui8Resol; ++column) {
                RwIm2DVertex& vertex = grid[k++];
                vertex.z = z;
                vertex.recipZ = recipZ;
                vertex.x = columnStep * static_cast<float>(static_cast<double>(column));
                vertex.y = y;
                uint8_t alpha;
                float uv[2];
                EvaluateDistortionVertex(data, &alpha, uv, point, screen);  // 0x000b1a68
                vertex.emissiveColor.red = data->m_cColor[0];
                vertex.emissiveColor.green = data->m_cColor[1];
                vertex.emissiveColor.blue = data->m_cColor[2];
                vertex.emissiveColor.alpha = alpha;
                vertex.q = 1.0f;
                vertex.r = 0.0f;
                vertex.s = uv[0];
                vertex.t = 1.0f - uv[1];
                point[0] = point[0] + step;
            }
            point[0] = 0.0f;
            point[1] = point[1] + step;
        }
    }
    PushRenderStates(g_pRenderStateRenderer);  // 0x0009e590
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(3));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, reinterpret_cast<void*>(8));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(2));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, scene);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendTableSrc[1])));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendTableDest[1])));
    RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void*>(2));
    RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRISTRIP, static_cast<RwIm2DVertex*>(fx->m_unk30),
                                 static_cast<RwInt32>(size * size), static_cast<RwImVertexIndex*>(fx->m_unk34),
                                 static_cast<RwInt32>(fx->m_unk28));  // RWEngine +0x34
    PopRenderStates(g_pRenderStateRenderer);  // 0x0009e858
    return running;
}

// 0x000b2c88 CDistortionScreenFx_Draw
void CDistortionScreenFx::Render(IKTime* frameClock) {
    if (frameClock->m_eCurrentState != 0) return;
    m_fTime = m_fTime + frameClock->m_afDeltaTime[1];  // +0x20
    if (m_pSource == nullptr) return;
    if (RenderDistortionGridWarp(this, m_fTime, m_unk1c, m_pCenter, static_cast<CDistortionScreenData*>(m_pSource)) != 0) return;
    m_BitProperties &= 0xfffffeffu;
    m_pCenter = nullptr;
    m_pSource = nullptr;
    m_unk1c = nullptr;
}

// 0x000b2008 CDistortionScreenData_Reset_maybe
void CDistortionScreenFx::Reset() {
    m_fTime = 0.0f;
    m_BitProperties &= 0xfffffeffu;
    m_pCenter = nullptr;
    m_pSource = nullptr;
    m_unk1c = 0;
}

// 0x000b2038 CDistortionScreenData_SetSource_maybe
void CDistortionScreenFx::SetSource(IKSerializable* source) {
    m_fTime = 0.0f;
    if (source == nullptr) {
        m_BitProperties &= 0xfffffeffu;
        return;
    }
    m_pSource = source;
    m_BitProperties = (m_BitProperties & 0xfffffeffu) | 0x100u;
}

// C2.8 port-all P08.

// 0x000b16d8 CDistortionScreenData_RecursiveRegistration
void CDistortionScreenData::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x000b1800 CDistortionScreenData_Destroy
void CDistortionScreenData::Destroy() {
    if (m_pv2Amplitude != nullptr) {
        delete[] m_pv2Amplitude;  // OperatorDeleteArray(pointer - 4)
        m_pv2Amplitude = nullptr;
    }
}

// 0x000b2080 CDistortionScreenData_vf54 (KUDestroy): the same body as Destroy.
void CDistortionScreenData::KUDestroy() {
    if (m_pv2Amplitude != nullptr) {
        delete[] m_pv2Amplitude;
        m_pv2Amplitude = nullptr;
    }
}

// 0x000b3008 CDistortionScreenData_vf50 (KUInitialize). The old curve is not freed (the original overwrites the pointer).
int32_t CDistortionScreenData::KUInitialize() {
    static const uint8_t kWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc (copied as a word)
    m_ui32NbAmplitudePoints = 0;
    m_fDuration = 2.0f;
    m_fDampCoeff = 0.002f;
    m_fAmpThreshold = 0.02f;
    m_pv2Amplitude = nullptr;
    m_ui32NbAmplitudePoints = 2;
    std::memcpy(m_cColor, kWhite, 4);
    m_pv2Amplitude = new CVector2[2];  // OperatorNewArray(0x14), count cookie 2
    m_pv2Amplitude[0].m_fY = 0.0f;
    m_pv2Amplitude[0].m_fX = 0.0f;
    m_pv2Amplitude[1].m_fY = 0.0f;
    m_pv2Amplitude[1].m_fX = 1.0f;
    m_v3OffsetPos.x = 0.0f;  // the null vector 0x00c50d64
    m_v3OffsetPos.z = 0.0f;
    m_v3OffsetPos.y = 0.0f;
    return 1;
}

// 0x000b2220 CDistortionScreenFx_RecursiveRegistration
void CDistortionScreenFx::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
