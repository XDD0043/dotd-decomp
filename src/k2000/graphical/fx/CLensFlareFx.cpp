// CLensFlareFx.cpp - reconstructed original translation unit 0xb3170-0xb4808 (GAME_TOC1, main_toc1), 24 functions, 21 live.
// Primary class: CLensFlareFx  key 0x1b4d  category Graphical  size 0x30  vtable 0xb176f8
// Other owners: CLensFlareData (7), DrawLensFlareElements (2), RegisterCLensFlareFxAndDataClasses (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xb3170  FUN_000b3170  [dead]
//   [x] 0xb32e0  CLensFlareFx_vf78  (Clear, CLensFlareFx.h)
//   [x] 0xb32e8  CLensFlareFx_SetEnabled
//   [ ] 0xb3308  CLensFlareFx_IsEnabled  [dead]
//   [ ] 0xb3318  FUN_000b3318  [dead]
//   [ ] 0xb3320  RegisterCLensFlareFxAndDataClasses
//   [ ] 0xb33d8  _GLOBAL__I_b33d8
//   [x] 0xb33e8  CLensFlareData_DeleteArray
//   [x] 0xb3490  CLensFlareFx_DeleteArray
//   [x] 0xb3538  CLensFlareData_Create
//   [x] 0xb3570  CLensFlareFx_Create
//   [x] 0xb35c8  CLensFlareData_CreateArray
//   [x] 0xb3660  CLensFlareFx_CreateArray
//   [ ] 0xb3718  CLensFlareData_Save
//   [x] 0xb3720  CLensFlareFx_RecursiveRegistration
//   [x] 0xb3780  CLensFlareData_RecursiveRegistration
//   [x] 0xb37e0  CLensFlareData_Destroy
//   [x] 0xb3838  CLensFlareFx_Enqueue
//   [x] 0xb3970  CLensFlareFx_PostLoad
//   [x] 0xb39a0  CLensFlareFx_Destroy
//   [x] 0xb39c8  DrawLensFlareElements
//   [x] 0xb43b0  DrawLensFlareElements
//   [x] 0xb43b8  CLensFlareFx_Draw
//   [x] 0xb43d0  CLensFlareData_Load
//
//   [x] 0x9a0aa8  CLensFlareData_GetClassType  [inline]
//   [x] 0x9a0ab0  CLensFlareData_GetClassID  [inline]
//   [x] 0x9a0ab8  CLensFlareFx_GetClassType  [inline]
//   [x] 0x9a0ac0  CLensFlareFx_GetClassID  [inline]
//   [x] 0x9a0ac8  CLensFlareFx_GetSerializationFlags  [inline]
//   [ ] 0x9a0ad0  CLensFlareData_DeletingDestructor  [inline]
//   [ ] 0x9a0b18  CLensFlareData_Destructor  [inline]
//   [x] 0x9a0b48  CLensFlareData_IsKindOfClass  [inline]
//   [x] 0x9a0b68  CLensFlareFx_IsKindOfClass  [inline]
//   [ ] 0x9a0ba0  CLensFlareFx_Save  [inline]
//   [x] 0x9a0bc8  CLensFlareFx_Load  [inline]
//   [x] 0x9a0bf0  CLensFlareFx_Destructor  [inline]
//   [x] 0x9a0c10  CLensFlareFx_DeletingDestructor  [inline]
#include "k2000/graphical/fx/CLensFlareFx.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm2D.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/render/CRenderer.h"

namespace {
// 0x00010690 Math_Sqrtf: the double square root rounded to float, as a double.
inline double MathSqrtf(double x) { return static_cast<double>(static_cast<float>(std::sqrt(x))); }

// 0x00c5cad8: the flare's four Im2D vertices (BSS; the screen z and reciprocal z are only rewritten when the near
// screen z changed), and 0x00c297d8: their strip order.
RwIm2DVertex s_vertices[4];
RwImVertexIndex s_indices[4] = {1, 0, 2, 3};

// fctidz, then the low byte (stb of the 64-bit word).
uint8_t LowByte(float value) { return static_cast<uint8_t>(ppc::fctidz(static_cast<double>(value))); }
}  // namespace

// 0x000b3570 CLensFlareFx_Create: the inlined IRendableObject part, in the original's store order.
CLensFlareFx::CLensFlareFx() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x009a0bc8 CLensFlareFx_Load
int32_t CLensFlareFx::Load(IKFile* file, int32_t type) {
    IScreenFx::Load(file, type);  // the original calls IRendableObject_Load
    return 1;
}

// 0x000b39a0 CLensFlareFx_Destroy
void CLensFlareFx::Destroy() { IRendableObject::Destroy(); }

// 0x000b3970 CLensFlareFx_PostLoad: for the level (type 0) disabled, without data.
int32_t CLensFlareFx::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_BitProperties &= ~0x100u;
    m_pData = nullptr;
    return 1;
}

// 0x000b32e8 CLensFlareFx_SetEnabled
void CLensFlareFx::SetEnabled(int32_t on) {
    m_BitProperties = (m_BitProperties & ~0x100u) | (static_cast<uint32_t>(on) << 8);
}

// 0x000b3838 CLensFlareFx_UpdateAndExtract: while enabled, the data's source position taken, projected to the screen
// (raster pixels), and the object queued in stage 16 (+0x40 of the stage array) when a 0.1 sphere there is not outside
// the main camera's frustum (0x00c5c9cc, the camera context's main camera).
void CLensFlareFx::UpdateAndExtract(float, RenderQueue** stages, IKTime*, RwCamera*, int32_t) {
    if ((m_BitProperties & 0x100) == 0) return;
    if (m_pData != nullptr) {
        m_vPosition.x = m_pData->m_vPosition.x;
        m_vPosition.y = m_pData->m_vPosition.y;
        m_vPosition.z = m_pData->m_vPosition.z;
    }
    CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
    ProjectWorldPointToScreen(context, &m_vPosition, m_afScreen, 1);
    const RwReal sphere[4] = {m_vPosition.x, m_vPosition.y, m_vPosition.z, 0.1f};  // TOC -0x5d0c
    if (RwCameraFrustumTestSphere(context->m_pMainCamera, sphere) == rwSPHEREOUTSIDE) return;
    stages[16]->Add(this);
}

// 0x000b43b8 CLensFlareFx_Render
void CLensFlareFx::Render(IKTime* /*frameClock*/) {
    if (m_pData == nullptr) return;
    DrawLensFlareElements(this, m_pData);
}

// 0x000b39c8 DrawLensFlareElements: one textured Im2D quad (a 4-vertex strip) per element along the line from the
// source's screen point through the screen centre. The colour channels an element flags tend, with the source's
// distance from the centre (twice the normalised distance, at most 1), to 255 times the source's normalised x (red)
// and y (green, blue) distance; the alpha is 255 minus 1% of the element's alpha times the pixel distance, at least
// 200. Z test and write off, no culling and fog, clamped and filtered texture, alpha test always, vertex alpha, blend
// SRCALPHA / ONE, flat shading; the render states pushed and popped around it.
void DrawLensFlareElements(CLensFlareFx* fx, CLensFlareData* data) {
    if (data->m_pTexture == nullptr) return;
    const RwRaster* target = RwDevice_GetCurrentCamera()->frameBuffer;  // RWEngine +0 (the current camera) +0x60
    CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
    RwRaster* raster = data->m_pTexture->raster;
    const float targetWidth = static_cast<float>(target->width);
    float textureWidth = targetWidth;
    if (raster != nullptr) textureWidth = static_cast<float>(static_cast<int32_t>(raster->width));
    const float halfWidth = targetWidth * 0.5f;                                    // TOC -0x5d00
    const float halfHeight = static_cast<float>(target->height) * 0.5f;
    const float nearZ = RwIm2DGetNearScreenZ();                                     // RWEngine +0x18
    const float cameraNear = context->m_pMainCamera->nearPlane;
    float dx = fx->m_afScreen[0] - halfWidth;
    float dy = fx->m_afScreen[1] - halfHeight;
    float nx = dx / halfWidth;
    float ny = dy / halfHeight;
    const float distance = static_cast<float>(MathSqrtf(ppc::fmadds(nx, nx, ny * ny)));  // normalised, sp+0x84
    float length = static_cast<float>(MathSqrtf(ppc::fmadds(dx, dx, dy * dy)));
    if (length == 0.0f) {
        length = 0.0f;
    } else {
        const float inv = 1.0f / length;
        dy = dy * inv;
        dx = dx * inv;
    }
    ny = std::fabs(ny);
    if (nx < 0.0f) nx = -nx;
    // The source-position colour: 255 - (uint8)(255 - 255 * |n|) per channel (0 when 255 * |n| is above 255), red from
    // x, green and blue from y, alpha 0.
    uint8_t byteY = 0;
    float scaled = ny * 255.0f;  // TOC -0x5d58
    if (!(scaled > 255.0f)) byteY = static_cast<uint8_t>(ppc::fctiwz(255.0f - scaled));
    uint8_t byteX = 0;
    scaled = nx * 255.0f;
    if (!(scaled > 255.0f)) byteX = static_cast<uint8_t>(ppc::fctiwz(255.0f - scaled));
    const uint8_t positionRed = 0xff > byteX ? static_cast<uint8_t>(0xff - byteX) : 0;
    const uint8_t positionGreen = byteY < 0xff ? static_cast<uint8_t>(0xff - byteY) : 0;
    const uint8_t positionBlue = positionGreen;
    const uint8_t positionAlpha = 0;  // 0xff - 0xff
    PushRenderStates(g_pRenderStateRenderer);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(3));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, reinterpret_cast<void*>(8));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(2));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, raster);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(5));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(2));
    RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void*>(1));
    if (data->m_ui8Count != 0) {
        const float alphaAdd = static_cast<float>(positionAlpha) * 0.0f;
        const float colorRed = static_cast<float>(positionRed);
        const float colorGreen = static_cast<float>(positionGreen);
        const float colorBlue = static_cast<float>(positionBlue);
        const float twiceDistance = distance + distance;
        uint32_t counter = 0;
        uint32_t index = 0;
        do {
            if (s_vertices[0].z != nearZ) {
                for (RwIm2DVertex& vertex : s_vertices) vertex.z = nearZ;
                const float recipZ = 1.0f / cameraNear;
                for (RwIm2DVertex& vertex : s_vertices) vertex.recipZ = recipZ;
            }
            const CLensFlareData::Element& element = data->m_pElements[index];
            const float along = length * element.m_fDistance;
            const uint32_t mode = (element.m_ui8Flags >> 3) & 3;
            float half = element.m_fSize * 64.0f;  // TOC -0x5cf4
            const float offsetY = dy * along;
            const float offsetX = along * dx;
            if (mode == 1) {
                half = half * distance;
            } else if (mode == 2) {
                half = half * (1.0f - distance);
            }
            const float bottom = halfHeight + (half + offsetY);
            const float rightX = halfWidth + (half + offsetX);
            const float leftX = halfWidth + (offsetX - half);
            const float top = halfHeight + (offsetY - half);
            s_vertices[3].y = bottom;
            s_vertices[2].x = rightX;
            s_vertices[3].x = leftX;
            s_vertices[1].y = top;
            s_vertices[0].x = leftX;
            s_vertices[0].y = top;
            s_vertices[1].x = rightX;
            s_vertices[2].y = bottom;
            float u0 = element.m_fU;
            float v0 = element.m_fV;
            float u1, v1, q0, qv0, q1, qv1;
            if (textureWidth > targetWidth) {
                u1 = u0 + data->m_fUSpan;
                v1 = v0 + data->m_fVSpan;
                q0 = 3.40282347e+38f;  // 0x00c4acb8 +0x28: FLT_MAX
                qv0 = q0;
                q1 = 1.0f / u1;
                qv1 = 1.0f / v1;
            } else {
                const float halfTexel = 0.5f / textureWidth;
                v0 = v0 + halfTexel;
                u0 = u0 + halfTexel;
                v1 = v0 + data->m_fVSpan;
                u1 = u0 + data->m_fUSpan;
                q0 = 1.0f / u0;
                q1 = 1.0f / u1;
                qv1 = 1.0f / v1;
                qv0 = 1.0f / v0;
            }
            // BUG(original)? The projective coordinates: s = u * q with q = 1 / u (FLT_MAX for a texture wider than
            // the target), as the PS3 Im2D path reads them.
            const float t1 = v1 * qv1;
            const float s0 = u0 * q0;
            const float t0 = v0 * qv0;
            const float s1 = u1 * q1;
            s_vertices[2].q = q1;
            s_vertices[3].q = q0;
            s_vertices[0].q = q0;
            s_vertices[0].r = 0.0f;
            s_vertices[1].q = q1;
            s_vertices[1].r = 0.0f;
            s_vertices[2].r = 0.0f;
            s_vertices[3].r = 0.0f;
            s_vertices[3].t = t1;
            s_vertices[3].s = s0;
            s_vertices[0].s = s0;
            s_vertices[1].t = t0;
            s_vertices[2].s = s1;
            s_vertices[0].t = t0;
            s_vertices[1].s = s1;
            s_vertices[2].t = t1;
            uint8_t alpha = 200;
            const float fadeAlpha = length * static_cast<float>(static_cast<int32_t>(element.m_Color[3])) * 0.01f;  // TOC -0x5cec
            if (!(fadeAlpha > 255.0f)) {
                alpha = static_cast<uint8_t>(ppc::fctiwz(255.0f - fadeAlpha));
                if (alpha <= 199) alpha = 200;
            }
            float k = 1.0f;
            if (!(twiceDistance > 1.0f)) k = twiceDistance < 0.0f ? 0.0f : twiceDistance;
            float keepRed = 1.0f, addRed = 0.0f;
            if ((element.m_ui8Flags & 1) != 0) {
                keepRed = 1.0f - k;
                addRed = k;
            }
            float keepGreen = 1.0f, addGreen = 0.0f;
            if ((element.m_ui8Flags & 2) != 0) {
                keepGreen = 1.0f - k;
                addGreen = k;
            }
            float keepBlue = 1.0f, addBlue = 0.0f;
            if ((element.m_ui8Flags & 4) != 0) {
                keepBlue = 1.0f - k;
                addBlue = k;
            }
            const uint8_t red = LowByte(ppc::fmadds(keepRed, static_cast<float>(element.m_Color[0]), addRed * colorRed));
            const uint8_t green = LowByte(ppc::fmadds(keepGreen, static_cast<float>(element.m_Color[1]), addGreen * colorGreen));
            const uint8_t blue = LowByte(ppc::fmadds(keepBlue, static_cast<float>(element.m_Color[2]), addBlue * colorBlue));
            // (The element's own alpha plus alphaAdd is converted into a stack byte that is never read.)
            (void)alphaAdd;
            for (RwIm2DVertex& vertex : s_vertices) {
                vertex.emissiveColor.red = red;
                vertex.emissiveColor.green = green;
                vertex.emissiveColor.blue = blue;
                vertex.emissiveColor.alpha = alpha;
            }
            ++counter;
            RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRISTRIP, s_vertices, 4, s_indices, 4);
            index = counter & 0xff;
        } while (index < data->m_ui8Count);
    }
    PopRenderStates(g_pRenderStateRenderer);
}

// 0x000b43d0 CLensFlareData_Load: for the level (type 0) the texture (a reference taken), two bytes, the spans, the
// element count and the elements (Mem_AllocAligned16, read from the last to the first), then the source position.
int32_t CLensFlareData::Load(IKFile* file, int32_t type) {
    if (type != 0) return 1;
    IKFile_ReadTextureRef(file, reinterpret_cast<void**>(&m_pTexture), 1);
    ReadU8(file, &m_unk0c);
    ReadU8(file, &m_unk0d);
    ReadF32LE(file, &m_fUSpan);
    ReadF32LE(file, &m_fVSpan);
    ReadU8(file, &m_ui8Count);
    m_pElements = static_cast<Element*>(Mem_AllocAligned16(static_cast<uint32_t>(m_ui8Count) * 0x1cu));
    for (uint32_t i = m_ui8Count; i != 0;) {
        --i;
        Element& element = m_pElements[i];
        ReadU8(file, &element.m_unk00);
        ReadF32LE(file, &element.m_fDistance);
        ReadF32LE(file, &element.m_fSize);
        ReadF32LE(file, &element.m_fU);
        ReadF32LE(file, &element.m_fV);
        file->Read(element.m_Color, 4);
        ReadU8(file, &element.m_ui8Flags);
    }
    ReadF32LE(file, &m_vPosition.x);  // one 12-byte read, then the three words byte-swapped
    ReadF32LE(file, &m_vPosition.y);
    ReadF32LE(file, &m_vPosition.z);
    return 1;
}

// 0x000b37e0 CLensFlareData_Destroy: the elements freed, the texture released.
void CLensFlareData::Destroy() {
    Mem_FreeAligned16(m_pElements);
    if (m_pTexture != nullptr) {
        TextureRef_Release(m_pTexture);  // RwTextureDestroy
        m_pTexture = nullptr;
    }
}

// C2.8 port-all P08.

// 0x000b3720 CLensFlareFx_RecursiveRegistration
void CLensFlareFx::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x000b3780 CLensFlareData_RecursiveRegistration
void CLensFlareData::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
