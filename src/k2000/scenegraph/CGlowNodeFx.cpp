// CGlowNodeFx.cpp - reconstructed original translation unit 0xe3538-0xe4ed0 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary class: CGlowNodeFx  key 0x2cb  category SceneNode  size 0x5c  vtable 0xb18a30
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xe3538  CGlowNodeFx_Delete
//   [ ] 0xe3588  RegisterCGlowNodeFxClass
//   [ ] 0xe3600  _GLOBAL__I_e3600
//   [ ] 0xe3610  CGlowNodeFx_Save
//   [x] 0xe3638  CGlowNodeFx_RecursiveRegistration  (INodeFx's (returns 1, registers nothing): CSGLeaf's)
//   [x] 0xe3660  CGlowNodeFx_SetupMaterial_maybe
//   [x] 0xe3980  CGlowNodeFx_PostLoad
//   [x] 0xe39e8  CGlowNodeFx_Destroy
//   [x] 0xe3a38  CGlowNodeFx_DeleteArray
//   [x] 0xe3ad8  CGlowNodeFx_Create
//   [ ] 0xe3b38  FUN_000e3b38  [dead]
//   [x] 0xe3b88  CGlowNodeFx_CreateArray
//   [x] 0xe3c58  CGlowNodeFx_Load
//   [x] 0xe4050  CGlowNodeFx_Enqueue
//
//   [ ] 0x9a5378  CGlowNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a53d8  CGlowNodeFx_GetClassType  [inline]
//   [ ] 0x9a53e0  CGlowNodeFx_GetClassID  [inline]
//   [ ] 0x9a53e8  CGlowNodeFx_Destructor  [inline]
//   [ ] 0x9a5428  CGlowNodeFx_DeletingDestructor  [inline]
#include "k2000/scenegraph/CGlowNodeFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

// 0x000e3c58 CGlowNodeFx_Load
int32_t CGlowNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    ReadU32LE(file, &m_ui32NbGlows);
    ReadF32LE(file, &m_fPartSize);
    ReadRaw(file, m_color, 4);  // not swapped
    const uint32_t n = m_ui32NbGlows;
    uint32_t words = 0;
    if ((m_sgProperties & 0x400) == 0) {
        uint8_t* buffer = static_cast<uint8_t*>(Mem_AllocAligned16(n * 0xc));
        m_aWorldNormal = nullptr;
        m_aPosition = reinterpret_cast<CVector3*>(buffer);
        m_aNormal = nullptr;
        words = n * 3;
    } else {
        uint8_t* buffer;
        if ((m_sgProperties & 0x4000) == 0) {
            buffer = static_cast<uint8_t*>(Mem_AllocAligned16(n * 0x18));
            m_aWorldNormal = nullptr;
            m_aPosition = reinterpret_cast<CVector3*>(buffer);
            m_aNormal = reinterpret_cast<CVector3*>(buffer + n * 0xc);
        } else {
            buffer = static_cast<uint8_t*>(Mem_AllocAligned16(n * 0x24));
            m_aPosition = reinterpret_cast<CVector3*>(buffer);
            m_aNormal = reinterpret_cast<CVector3*>(buffer + n * 0xc);
            m_aWorldNormal = reinterpret_cast<CVector3*>(buffer + n * 0x18);
        }
        words = n * 6;  // positions and normals (the world normals are not in the file)
    }
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aPosition), words);
    IKFile_ReadTextureRef(file, &m_pTexture, 0);
    ReadF32LE(file, &m_f32FlickSizeThreshold);
    ReadF32LE(file, &m_f32FlickSizeCoeff);
    ReadF32LE(file, &m_f32FlickAlphaThreshold);
    ReadRaw(file, &m_ui8FlickAlphaMean, 1);
    ReadRaw(file, &m_ui8FlickAlphaAmpl, 1);
    return 1;
}

namespace {
// Rand_Int's low 16 bits as a float (rldicl 48, fcfid, frsp). A macro, so that the rand log names CGlowNodeFx.
#define GlowRandU16() static_cast<float>(static_cast<uint16_t>(Rand_Int()))

// TOC -0x4f40 (0xb8000080, -1/32767.75...).
const float kGlowRandScale = [] {
    const uint32_t bits = 0xb8000080u;
    float f;
    std::memcpy(&f, &bits, 4);
    return f;
}();
const float kPi = 3.14159274f;  // TOC -0x4f48 (0x40490fdb)

void SetFloatBits(uint32_t* dst, float value) { std::memcpy(dst, &value, 4); }

// 0x002406d0 Mat4_TransformPointsStrided: one RwV3dTransformPoints call when both strides are 0xc, else one per point.
void TransformPointsStrided(const CMatrix34* m, uint8_t* out, int32_t outStride, const uint8_t* in, int32_t inStride,
                            int32_t count) {
    if (outStride == 0xc && inStride == 0xc) {
        Mat4_TransformPoints(m, reinterpret_cast<CVector3*>(out), reinterpret_cast<const CVector3*>(in), count);
        return;
    }
    for (int32_t i = 0; i != count; ++i) {
        Mat4_TransformPoints(m, reinterpret_cast<CVector3*>(out), reinterpret_cast<const CVector3*>(in), 1);
        in += inStride;
        out += outStride;
    }
}
}  // namespace

// The flicker's alpha: (mean + amplitude) - ((r & 0xffff) * (2 * amplitude + 1) >> 16), one rand draw (mullw, rlwinm 16).
#define GlowFlickerValue()                                                                        \
    (static_cast<uint32_t>(m_ui8FlickAlphaMean) + m_ui8FlickAlphaAmpl -                           \
     ((static_cast<uint32_t>(static_cast<uint16_t>(Rand_Int())) *                                 \
       (((static_cast<uint32_t>(m_ui8FlickAlphaAmpl) << 1) & 0x1fe) + 1)) >> 16))
// The size flicker factor: fmadds(fmadds(u, TOC -0x4f40, 1.0f), +0x50, 1.0f), one rand draw.
#define GlowSizeFactor() ppc::fmadds(ppc::fmadds(GlowRandU16(), kGlowRandScale, 1.0f), m_f32FlickSizeCoeff, 1.0f)

// The constant colour's flicker and the constant size's (flag 0x8000 without per-glow arrays): the alpha draw
// (and, past the threshold, the flicker value), then the size draw (and one or two factors).
#define GlowConstantFlicker(alphaWhenSteady)                                                  \
    do {                                                                                      \
        if (GlowRandU16() / 65535.0f >= m_f32FlickAlphaThreshold) {                           \
            color[3] = static_cast<uint8_t>(GlowFlickerValue());                              \
        } else {                                                                              \
            color[3] = (alphaWhenSteady);                                                     \
        }                                                                                     \
        std::memcpy(ptank->colorCC, color, 4);                                                \
        RpPTankAtomicCopyConstantColorToMaterial(atomic); /* the PTank material's colour */     \
        ptank->flags40 |= 0x2000;                                                             \
        float sizeX = m_fPartSize;                                                            \
        float sizeY = sizeX;                                                                  \
        if (GlowRandU16() / 65535.0f >= m_f32FlickSizeThreshold) {                            \
            if ((m_sgProperties & 0x10000) != 0) {                                            \
                sizeX = m_fPartSize * GlowSizeFactor();                                       \
                sizeY = sizeX;                                                                \
            } else {                                                                          \
                const float s1 = GlowSizeFactor();                                            \
                const float s2 = GlowSizeFactor();                                            \
                sizeX = m_fPartSize * s1;                                                     \
                sizeY = m_fPartSize * s2;                                                     \
            }                                                                                 \
        }                                                                                     \
        SetFloatBits(&ptank->renderC0[0], sizeX);                                             \
        SetFloatBits(&ptank->renderC0[1], sizeY);                                             \
        ptank->flags40 |= 0x4000;                                                             \
    } while (0)

// 0x000e3980 CGlowNodeFx_PostLoad
int32_t CGlowNodeFx::PostLoad(int32_t type) {
    INodeFx::PostLoad(type);  // 0xeca78 CNodeFx_PostLoadBase_maybe
    SetupMaterial();
    if (type == 0) m_unk2c = nullptr;
    return 1;
}

// 0x000e3660 CGlowNodeFx_SetupMaterial_maybe
void CGlowNodeFx::SetupMaterial() {
    const float size = m_fPartSize;
    RpAtomic* atomic = static_cast<CGeometry*>(m_lGeometryList)->m_pRpAtomic;
    RpPTankData* ptank = atomic->ptank;
    SetFloatBits(&ptank->renderC0[0], size);
    SetFloatBits(&ptank->renderC0[1], size);
    ptank->flags40 |= 0x4000;
    std::memcpy(ptank->colorCC, m_color, 4);
    RpPTankAtomicCopyConstantColorToMaterial(atomic);  // the PTank material's colour (RpMaterial +4)
    ptank->flags40 |= 0x2000;
    ptank->renderC8 = 0;
    ptank->flags40 |= 0x20000;
    if (m_pTexture != nullptr) {
        ptank->texCoordsE0[0] = 0;
        ptank->texCoordsE0[1] = 0;
        SetFloatBits(&ptank->texCoordsE0[2], 1.0f);  // TOC -0x4f5c
        SetFloatBits(&ptank->texCoordsE0[3], 1.0f);
        ptank->flags40 |= 0x80000;
        if (m_pTexture != nullptr) RpMaterialSetTexture(RpPTankAtomicGetMaterial(atomic), static_cast<RwTexture*>(m_pTexture));
    }
    RpPTankLockStruct lock = {nullptr, 0};
    RpPTankAtomicLock(atomic, &lock, 1, 0x40000000);  // rpPTANKDFLAGPOSITION
    for (uint32_t i = 0; i < m_ui32NbGlows; ++i) {
        std::memcpy(lock.data, &m_aPosition[i], 0xc);
        lock.data += lock.stride;
    }
    if ((m_sgProperties & 0x400) != 0 && (m_sgProperties & 0x1000) != 0) {
        RpPTankAtomicLock(atomic, &lock, 2, 0x40000000);  // rpPTANKDFLAGCOLOR
        for (uint32_t i = 0; i < m_ui32NbGlows; ++i) {
            std::memcpy(lock.data, m_color, 4);
            lock.data += lock.stride;
        }
    }
    RpPTankAtomicUnlock(atomic);
}

// 0x000e4050 CGlowNodeFx_Enqueue. The rand draws (flag 0x8000 only, and only when the node was drawn this frame):
// without 0x200, or with 0x200 and the one glow facing the camera: 2 + (1 past the alpha threshold) + (1 or 2 past the
// size threshold); with 0x200 | 0x400, the same per glow facing the camera, the alpha's second draw only when the first
// value is below the faded alpha.
void CGlowNodeFx::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                                   int32_t /*distanceCull*/) {
    if (m_unk2c != nullptr) {
        RwFrame* frame = m_pRwFrame;
        // The followed node's stored LTM (+0x80, no sync).
        const RwMatrix* source = FrameLtm(static_cast<CSGMovable*>(m_unk2c)->m_pRwFrame);
        const float x = source->pos.x;
        const float y = source->pos.y;
        frame->modelling.pos.z = source->pos.z;
        frame->modelling.pos.x = x;
        frame->modelling.pos.y = y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(m_pRwFrame);
    }
    EnqueueBase(stages, frameClock, camera);  // 0xec920
    if (m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) return;
    if (frameClock->m_eCurrentState != 0) return;
    uint32_t flags = m_sgProperties;
    RpAtomic* atomic = static_cast<CGeometry*>(m_lGeometryList)->m_pRpAtomic;
    RpPTankData* ptank = atomic->ptank;
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(FrameLtm(m_pRwFrame));  // the stored LTM (+0x50, no sync)
    bool locked = false;
    RpPTankLockStruct positions = {nullptr, 0};
    if ((flags & 0x4000) != 0) {
        RpPTankAtomicLock(atomic, &positions, 1, 0x40000000);  // rpPTANKDFLAGPOSITION
        locked = true;
        TransformPointsStrided(ltm, positions.data, positions.stride, reinterpret_cast<const uint8_t*>(m_aPosition), 0xc,
                               static_cast<int32_t>(m_ui32NbGlows));
        flags = m_sgProperties;
    }
    if ((flags & 0x200) == 0) {
        // No camera test: with the flicker (0x8000) the constant colour's alpha and the constant size.
        if ((flags & 0x8000) != 0) {
            uint8_t color[4];
            std::memcpy(color, m_color, 4);
            GlowConstantFlicker(m_color[3]);
        }
        if (locked) RpPTankAtomicUnlock(atomic);
        return;
    }
    // engine +0x08 (camera context) +0x2c (the IKCamera) +0x04 (its frame) +0x40: the modelling matrix's position.
    const RwV3d& cam = static_cast<CSGMovable*>(Engine_GetCameraContext()->m_pCamera)->m_pRwFrame->modelling.pos;
    if ((flags & 0x400) == 0) {
        // One glow at the node: faded by the angle between the node's right axis and the direction to the camera.
        float dy = ltm->m_pos.y - cam.y;
        float dx = ltm->m_pos.x - cam.x;
        float dz = ltm->m_pos.z - cam.z;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            dz = dz * inv;
            dx = dx * inv;
            dy = dy * inv;
        }
        const float dot = ppc::fmadds(dz, ltm->m_right.z, ppc::fmadds(dx, ltm->m_right.x, dy * ltm->m_right.y));
        if (dot >= 0.0f) {
            if (locked) RpPTankAtomicUnlock(atomic);
            return;
        }
        const float fade = dot * dot;
        flags = m_sgProperties;
        if ((flags & 0x2000) != 0) {
            SetFloatBits(&ptank->renderC8, fade * kPi);
            ptank->flags40 |= 0x20000;
            flags = m_sgProperties;
        }
        if ((flags & 0x800) != 0) {
            const float size = fade * m_fPartSize;
            SetFloatBits(&ptank->renderC0[0], size);
            SetFloatBits(&ptank->renderC0[1], size);
            ptank->flags40 |= 0x4000;
            flags = m_sgProperties;
        }
        if ((flags & 0x1000) != 0) {
            uint8_t color[4];
            std::memcpy(color, m_color, 4);
            color[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(m_color[3]) * fade));
            std::memcpy(ptank->colorCC, color, 4);
            RpPTankAtomicCopyConstantColorToMaterial(atomic);
            ptank->flags40 |= 0x2000;
            flags = m_sgProperties;
        }
        if ((flags & 0x8000) != 0) {
            uint8_t color[4];
            std::memcpy(color, ptank->colorCC, 4);
            GlowConstantFlicker(m_color[3]);
        }
        if (locked) RpPTankAtomicUnlock(atomic);
        return;
    }
    // Per glow, with normals: each glow faded by the angle between its normal and the direction to the camera; the
    // ones facing away hidden (size 0, alpha 0, rotation 0); the flicker per visible glow.
    const CVector3* position = m_aPosition;
    RpPTankLockStruct rotations = {nullptr, 0};
    if ((flags & 0x2000) != 0) {
        RpPTankAtomicLock(atomic, &rotations, 0x20, 0x40000000);  // rpPTANKDFLAG2DROTATE
        locked = true;
        flags = m_sgProperties;
    }
    RpPTankLockStruct sizes = {nullptr, 0};
    if ((flags & 0x8000) != 0 || (flags & 0x800) != 0) {
        RpPTankAtomicLock(atomic, &sizes, 4, 0x40000000);  // rpPTANKDFLAGSIZE
        locked = true;
        flags = m_sgProperties;
    }
    RpPTankLockStruct colors = {nullptr, 0};
    if ((flags & 0x8000) != 0 || (flags & 0x1000) != 0) {
        RpPTankAtomicLock(atomic, &colors, 2, 0x40000000);  // rpPTANKDFLAGCOLOR
        locked = true;
    }
    const CVector3* normal;
    if (m_aWorldNormal != nullptr) {
        Mat4_TransformVectors(ltm, m_aWorldNormal, m_aNormal, static_cast<int32_t>(m_ui32NbGlows));
        normal = m_aWorldNormal;
    } else {
        normal = m_aNormal;
    }
    for (uint32_t i = 0; i < m_ui32NbGlows; ++i, ++normal) {
        float dy;
        float dx;
        float dz;
        if ((m_sgProperties & 0x4000) == 0) {
            dy = position->y - cam.y;
            dx = position->x - cam.x;
            dz = position->z - cam.z;
            ++position;
        } else {
            const float* p = reinterpret_cast<const float*>(positions.data);
            dy = p[1] - cam.y;
            dx = p[0] - cam.x;
            dz = p[2] - cam.z;
        }
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            dz = dz * inv;
            dx = dx * inv;
            dy = dy * inv;
        }
        if ((m_sgProperties & 0x4000) != 0) positions.data += positions.stride;
        const float dot = ppc::fmadds(dz, normal->z, ppc::fmadds(dx, normal->x, dy * normal->y));
        if (dot >= 0.0f) {
            if (sizes.data != nullptr) {
                float* size = reinterpret_cast<float*>(sizes.data);
                size[0] = 0.0f;
                size[1] = 0.0f;
                sizes.data += sizes.stride;
            }
            if (colors.data != nullptr) {
                colors.data[3] = 0;
                colors.data += colors.stride;
            }
            if (rotations.data != nullptr) {
                std::memset(rotations.data, 0, 4);
                rotations.data += rotations.stride;
            }
            continue;
        }
        const float fade = dot * dot;
        if (sizes.data != nullptr) {
            float* size = reinterpret_cast<float*>(sizes.data);
            if ((m_sgProperties & 0x800) == 0) {
                size[0] = m_fPartSize;
                size[1] = m_fPartSize;
            } else {
                const float scaled = fade * m_fPartSize;
                size[0] = scaled;
                size[1] = scaled;
            }
        }
        if (colors.data != nullptr) {
            if ((m_sgProperties & 0x1000) == 0) {
                std::memcpy(colors.data, m_color, 4);
            } else {
                colors.data[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(m_color[3]) * fade));
            }
        }
        if (rotations.data != nullptr) {
            const float rotation = fade * kPi;
            std::memcpy(rotations.data, &rotation, 4);
            rotations.data += rotations.stride;
        }
        if ((m_sgProperties & 0x8000) != 0) {
            uint8_t* color = colors.data;
            if (GlowRandU16() / 65535.0f >= m_f32FlickAlphaThreshold) {
                // A dimmer flicker only: below the faded alpha a second draw sets it, else it stays.
                const uint32_t candidate = GlowFlickerValue();
                if (candidate < color[3]) color[3] = static_cast<uint8_t>(GlowFlickerValue());
            }
            float* size = reinterpret_cast<float*>(sizes.data);
            if (GlowRandU16() / 65535.0f >= m_f32FlickSizeThreshold) {
                if ((m_sgProperties & 0x10000) != 0) {
                    const float s = GlowSizeFactor();
                    const float y = s * size[1];
                    const float x = s * size[0];
                    size[1] = y;
                    size[0] = x;
                } else {
                    const float x = size[0];
                    const float s1 = GlowSizeFactor();
                    const float y = size[1];
                    size[0] = x * s1;
                    const float s2 = GlowSizeFactor();
                    size[1] = y * s2;
                }
            }
        }
        if (sizes.data != nullptr) sizes.data += sizes.stride;
        if (colors.data != nullptr) colors.data += colors.stride;
    }
    if (locked) RpPTankAtomicUnlock(atomic);
}

// 0x000e39e8 CGlowNodeFx_Destroy
void CGlowNodeFx::Destroy() {
    // BUG(original): the buffer pointer is not cleared (a second Destroy would free it again).
    if (m_aPosition != nullptr) Mem_FreeAligned16(m_aPosition);
    CNode::Destroy();
}
