// CKElectricArcNodeFx.cpp - reconstructed original translation unit 0x1b1300-0x1b3510 (GAME_TOC1, main_toc1), 28 functions, 27 live.
// Primary class: CKElectricArcNodeFx  key 0x164c  category Logic  size 0x50  vtable 0xb1c8c8
// Other owners: CKElectricArcFxData (1), CKExplosionFxData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1b1300  CKElectricArcNodeFx_SampleCurveWithJitter_maybe
//   [x] 0x1b1478  CKElectricArcFxData_Load
//   [x] 0x1b1918  CKElectricArcNodeFx_Delete
//   [x] 0x1b1968  CKElectricArcNodeFx_Stop
//   [x] 0x1b19c0  CKElectricArcNodeFx_OnPause
//   [ ] 0x1b1a00  RegisterCKElectricArcNodeFxClass
//   [ ] 0x1b1a78  _GLOBAL__I_1b1a78
//   [x] 0x1b1a88  CKElectricArcNodeFx_BuildArcSegmentVerts_maybe
//   [ ] 0x1b1cd0  CKElectricArcNodeFx_Save
//   [x] 0x1b1cf8  CKElectricArcNodeFx_RecursiveRegistration
//   [x] 0x1b1d68  CKElectricArcNodeFx_Destroy  (inherited: CKNodeFx3d_Destroy)
//   [x] 0x1b1d90  CKElectricArcNodeFx_DeleteArray
//   [x] 0x1b1e38  CKElectricArcNodeFx_CreateArray
//   [x] 0x1b1ef0  CKElectricArcNodeFx_SetEndAlpha_maybe
//   [x] 0x1b1f18  CKElectricArcNodeFx_SetStartAlpha_maybe
//   [x] 0x1b1f40  CKElectricArcNodeFx_SetEndPoint
//   [x] 0x1b1f80  CKElectricArcNodeFx_SetStartPoint
//   [x] 0x1b1fc0  CKElectricArcNodeFx_SetStartAndEndPoints
//   [x] 0x1b2018  CKElectricArcNodeFx_PostLoad
//   [x] 0x1b20c0  CKElectricArcNodeFx_Create
//   [x] 0x1b2118  CKElectricArcNodeFx_Load
//   [x] 0x1b2210  CKElectricArcNodeFx_InitTexCoords_maybe
//   [x] 0x1b2468  CKElectricArcNodeFx_RebuildArcGeometry_maybe
//   [x] 0x1b2940  CKElectricArcNodeFx_Start
//   [x] 0x1b2bd0  CKElectricArcNodeFx_Update
//   [ ] 0x1b33d0  CKElectricArcNodeFx_SetAlphaForOwner_maybe  [dead]
//   [x] 0x1b3500  CKExplosionFxData_GetNodeClassKey  (CKExplosionFxData::GetAssociatedFxClassIdentifier, CKExplosionFxData.h)
//   [x] 0x1b3508  KStub_Nop_1b3508  (empty; nothing calls it)
//
//   [ ] 0x9ab958  CKElectricArcNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ab990  CKElectricArcNodeFx_GetClassType  [inline]
//   [x] 0x9ab998  CKElectricArcNodeFx_GetClassID  [inline]
//   [x] 0x9ab9a0  CKElectricArcNodeFx_GetFxData  [inline]
//   [x] 0x9ab9a8  CKElectricArcNodeFx_SetFxData  [inline]
//   [ ] 0x9ab9b0  CKElectricArcNodeFx_Destruct  [inline]
//   [ ] 0x9ab9d0  CKElectricArcNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9aba18  KStub_Nop_9aba18  [inline]
#include "k2000/logic/fx/CKElectricArcNodeFx.h"

#include <cmath>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKElectricArcFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/system/IKTime.h"
#include "platform/fps.h"

namespace {

// 0x00c50d34 / 0x00c50d64: the shared x axis and the null vector (zero in the EBOOT's BSS; static initialisers).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// TOC -0x2254 / -0x221c (0xb8000080): -1 / 32768 rounded up, the scale of the rand jitter in -1..1.
const float kRandToMinusOne = -0x1.0001p-15f;

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

// The game's rand() as the arc reads it: the low 16 bits, unsigned (clrldi 0x30).
inline float RandU16() { return static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu); }

CKElectricArcFxData* DataOf(const CKElectricArcNodeFx* fx) { return static_cast<CKElectricArcFxData*>(fx->m_pFxData); }
CGeometry* FirstGeometry(const CKElectricArcNodeFx* fx) { return static_cast<CGeometry*>(fx->m_pNode->m_lGeometryList); }

// The alpha store of one geometry (inlined in Start and Update): `alpha` with blending (render flag 11), or opaque
// without it for a material of modes 1..6 with render flag 12 (or when `alpha` is already 0xff).
void SetGeometryAlpha(CGeometry* geometry, uint8_t alpha) {
    uint32_t blended = 0;
    if (alpha != 0xff) {
        blended = 1;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (mode > 0 && mode <= 6) {
                alpha = 0xff;
                blended = 0;
            }
        }
    }
    geometry->m_cGeometryColor[3] = alpha;
    const uint32_t flags = geometry->m_BitProperties;
    if (((flags >> 11) & 1u) != blended) {
        geometry->m_BitProperties = (flags & 0xfffff7ffu) | (blended << 11);
        geometry->UpdateProperties();  // vt+0x60
    }
}

}  // namespace

// 0x001b1300 CKElectricArcNodeFx_SampleCurveWithJitter_maybe: the data's curve (flag 2: linear between the keys
// (time, value), the last key's value outside them) at `t`, plus a rand jitter of data +0x20: with flag 1 in
// -data20..+data20 around value + data20 (BUG(original)? that is 0..2 x data20 above the curve), else value + data20 x
// (1 - r / 32768) (r in 0..65535).
float CKElectricArcNodeFx::SampleCurveWithJitter(float t, const CKElectricArcFxData* data) {
    float value = 0.0f;
    if (((data->m_flags39 >> 2) & 1) != 0) {
        const uint32_t count = data->m_unk08;
        const CKElectricArcFxData::Key* keys = data->m_unk0c;
        bool found = false;
        for (uint32_t k = 0; k < count; ++k) {
            const float t0 = keys[k].m_unk00;
            if (!(t > t0 || t == t0)) continue;  // fcmpu + cror (gt, eq)
            // BUG(original): the last key compares with the word pair past the array.
            const float t1 = keys[k + 1].m_unk00;
            if (!(t < t1)) continue;
            const float v0 = keys[k].m_unk04;
            value = v0 + ((keys[k + 1].m_unk04 - v0) * (t - t0)) / (t1 - t0);
            found = true;
            break;
        }
        // BUG(original): without keys this reads the word before the array.
        if (!found) value = keys[static_cast<int32_t>(count) - 1].m_unk04;
    }
    if ((data->m_flags39 & 1) != 0) {
        const float base = value + data->m_unk20;
        const float r = RandU16();
        return ppc::fmadds((r / 65535.0f) * -2.0f, data->m_unk20, base);
    }
    const float amplitude = data->m_unk20;
    const float r = RandU16();
    return ppc::fmadds(amplitude, ppc::fmadds(r, kRandToMinusOne, 1.0f), value);
}

// 0x009ab9a0 CKElectricArcNodeFx_GetFxData / 0x009ab9a8 CKElectricArcNodeFx_SetFxData
IKFxData* CKElectricArcNodeFx::GetFxData() { return reinterpret_cast<IKFxData*>(m_pFxData); }
void CKElectricArcNodeFx::SetFxData(IKFxData* data) { m_pFxData = reinterpret_cast<IKSerializable*>(data); }

void CKElectricArcNodeFx::ApplyAlpha() {
    for (CGeometry* geometry = FirstGeometry(this); geometry != nullptr; geometry = geometry->m_pNext) {
        SetGeometryAlpha(geometry, m_ui8Alpha);
    }
}

// 0x001b1ef0 CKElectricArcNodeFx_SetEndAlpha_maybe
void CKElectricArcNodeFx::SetEndAlpha(uint8_t alpha, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    m_ui8EndAlpha = alpha;
}

// 0x001b1f18 CKElectricArcNodeFx_SetStartAlpha_maybe
void CKElectricArcNodeFx::SetStartAlpha(uint8_t alpha, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    m_ui8StartAlpha = alpha;
}

// 0x001b1f40 CKElectricArcNodeFx_SetEndPoint
void CKElectricArcNodeFx::SetEndPoint(const CVector3* point, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    m_vEnd = *point;
}

// 0x001b1f80 CKElectricArcNodeFx_SetStartPoint
void CKElectricArcNodeFx::SetStartPoint(const CVector3* point, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    m_vStart = *point;
}

// 0x001b1fc0 CKElectricArcNodeFx_SetStartAndEndPoints
void CKElectricArcNodeFx::SetStartAndEndPoints(const CVector3* start, const CVector3* end, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    m_vStart = *start;
    m_vEnd = *end;
}

// 0x001b1968 CKElectricArcNodeFx_Stop
void CKElectricArcNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    Vf60();  // vt+0x60 HideSceneNode
}

// 0x001b19c0 CKElectricArcNodeFx_OnPause: vt+0x5c (ShowSceneNode).
void CKElectricArcNodeFx::Vf70() { Vf5C(); }

// 0x001b1a88 CKElectricArcNodeFx_BuildArcSegmentVerts_maybe. One draw for the branch's length (data +0x24, its jitter
// x data +0x2c), then per step a vertex pair (half width data +0x1c x data +0x28) and a jitter draw.
void CKElectricArcNodeFx::BuildArcSegmentVerts(RwV3d** vertex, const CVector3* point, const CVector3* direction) {
    const float dx = direction->x;
    const float dz = direction->z;
    const float negX = -dx;
    const float negZ = -dz;
    const float dy = direction->y;
    const float first = RandU16();
    const CKElectricArcFxData* data = DataOf(this);
    float length = (first / 65535.0f) * data->m_unk24;
    const float jitter = length * data->m_unk2c;
    length = length / static_cast<float>(m_unk44);
    const float stepZ = dz * length;
    const float stepX = dx * length;
    const float stepY = dy * length;
    float pz = point->z;
    float px = point->x;
    float py = point->y;
    float baseZ = pz;
    float baseX = px;
    float baseY = py;
    uint32_t i = 0;
    for (;;) {
        RwV3d* v = *vertex;
        baseX = baseX + stepX;
        baseY = baseY + stepY;
        baseZ = baseZ + stepZ;
        *vertex = v + 1;
        float w = DataOf(this)->m_unk1c * DataOf(this)->m_unk28;
        v->z = ppc::fmadds(negX, w, pz);
        v->x = ppc::fmadds(negZ, w, px);
        v->y = ppc::fmadds(dy, w, py);
        v = *vertex;
        *vertex = v + 1;
        w = -DataOf(this)->m_unk1c * DataOf(this)->m_unk28;
        v->z = ppc::fmadds(negX, w, pz);
        v->x = ppc::fmadds(negZ, w, px);
        v->y = ppc::fmadds(dy, w, py);
        float offset;
        if ((DataOf(this)->m_flags39 & 1) != 0) {
            const float r = RandU16();
            ++i;
            offset = jitter * ppc::fmadds(r, kRandToMinusOne, 1.0f);
        } else {
            const float r = RandU16();
            ++i;
            offset = jitter * (r / 65535.0f);
        }
        pz = ppc::fmadds(negX, offset, baseZ);
        px = ppc::fmadds(negZ, offset, baseX);
        py = ppc::fmadds(dy, offset, baseY);
        if (m_unk44 < i) return;
    }
}

// 0x001b2210 CKElectricArcNodeFx_InitTexCoords_maybe. The strip (bolt then branch, two coordinates per step: u 0 and
// 1) starts at v = (frame - 1) / frames and goes up and down by 1 / frames per step; the second geometry's eight
// coordinates take the frame's band.
void CKElectricArcNodeFx::InitTexCoords() {
    CGeometry* geometry = FirstGeometry(this);
    if (geometry == nullptr) return;
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 0x10);
    uint32_t frames = m_unk48;
    const float step = 1.0f / static_cast<float>(frames);
    RwTexCoords* uv = geometry->m_pRpAtomic->geometry->texCoords[0];
    uint32_t segments = m_unk18;
    for (int32_t pass = 0;; ++pass) {
        const uint32_t pairs = segments + 1;
        if (pairs != 0) {
            float v = static_cast<float>(static_cast<int32_t>(m_ui8Frame) - 1) / static_cast<float>(frames);
            int32_t sign = 1;
            RwTexCoords* p = uv;
            for (uint32_t k = 0; k < pairs; ++k) {
                const float s = static_cast<float>(static_cast<int8_t>(sign));
                sign = -sign;
                p[1].v = v;
                p[0].v = v;
                p[0].u = 0.0f;  // stw 0
                p[1].u = 1.0f;
                v = ppc::fmadds(step, s, v);
                p += 2;
            }
            uv = uv + segments * 2 + 2;
        }
        if (pass == 1) break;
        segments = m_unk44;
        frames = m_unk48;
    }
    geometry->UnlockGeometry();
    geometry = geometry->m_pNext;
    if (geometry == nullptr) return;
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 0x10);
    const float count = static_cast<float>(m_unk48);
    const float low = static_cast<float>(static_cast<int32_t>(m_ui8Frame) - 1) / count;
    const float high = low + 1.0f / count;
    RwTexCoords* quad = geometry->m_pRpAtomic->geometry->texCoords[0];
    quad[0].u = 0.0f;
    quad[1].u = 0.0f;
    quad[2].u = 1.0f;
    quad[3].u = 1.0f;
    quad[4].u = 0.0f;
    quad[5].u = 0.0f;
    quad[6].u = 1.0f;
    quad[7].u = 1.0f;
    quad[0].v = low;
    quad[1].v = high;
    quad[2].v = low;
    quad[3].v = high;
    quad[4].v = low;
    quad[5].v = high;
    quad[6].v = low;
    quad[7].v = high;
    geometry->UnlockGeometry();
}

// 0x001b2468 CKElectricArcNodeFx_RebuildArcGeometry_maybe
void CKElectricArcNodeFx::RebuildArcGeometry() {
    CGeometry* geometry = FirstGeometry(this);
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 2);
    const uint32_t segments = m_unk18;
    const float step = 1.0f / static_cast<float>(static_cast<int32_t>(segments));
    RwV3d* vertex = geometry->m_pRpAtomic->geometry->morphTarget->verts;
    // BUG(original): the branch's point and direction are stack words written only at the bolt segment m_i16BranchSegment
    // (never when it is out of range); zero here.
    CVector3 branchPoint = {0.0f, 0.0f, 0.0f};
    CVector3 branchDirection = {0.0f, 0.0f, 0.0f};
    const CVector3& axis = kAxisX;
    if (segments != 0) {
        float curZ = -0.5f;
        float curY = kNullVector.y;
        float curX = kNullVector.x;
        float prevY = kNullVector.y;
        float prevX = kNullVector.x;
        float prevZ = -0.5f;
        float t = 0.0f;
        float z = -0.5f;
        uint32_t i = 1;
        for (;;) {
            t = t + step;
            z = z + step;
            float w = DataOf(this)->m_unk1c;
            vertex->x = ppc::fmadds(w, axis.x, curX);
            vertex->z = ppc::fmadds(w, axis.z, curZ);
            vertex->y = ppc::fmadds(w, axis.y, curY);
            ++vertex;
            w = -DataOf(this)->m_unk1c;
            vertex->z = ppc::fmadds(w, axis.z, curZ);
            vertex->x = ppc::fmadds(w, axis.x, curX);
            vertex->y = ppc::fmadds(w, axis.y, curY);
            ++vertex;
            const float sample = SampleCurveWithJitter(t, DataOf(this));
            const int16_t segment = static_cast<int16_t>(i);
            ++i;
            curZ = ppc::fmadds(sample, axis.z, z);
            curX = ppc::fmadds(sample, axis.x, kNullVector.x);
            curY = ppc::fmadds(sample, axis.y, kNullVector.y);
            if (m_i16BranchSegment == segment) {
                const float ddy = curY - prevY;
                const float ddx = curX - prevX;
                const float ddz = curZ - prevZ;
                branchPoint.x = curX;
                branchPoint.y = curY;
                branchPoint.z = curZ;
                branchDirection.y = ddy;
                branchDirection.x = ddx;
                branchDirection.z = ddz;
                const float length = Sqrtf(ppc::fmadds(ddz, ddz, ppc::fmadds(ddx, ddx, ddy * ddy)));
                if (length != 0.0f) {
                    const float inverse = 1.0f / length;
                    branchDirection.z = branchDirection.z * inverse;
                    branchDirection.x = branchDirection.x * inverse;
                    branchDirection.y = branchDirection.y * inverse;
                }
            }
            prevX = curX;
            prevY = curY;
            prevZ = curZ;
            if (m_unk18 < i) break;
        }
    }
    const float w = DataOf(this)->m_unk1c;
    vertex->x = ppc::fmadds(w, axis.x, kNullVector.x);
    vertex->z = ppc::fmadds(w, axis.z, 0.5f);
    vertex->y = ppc::fmadds(w, axis.y, kNullVector.y);
    ++vertex;
    const float negW = -DataOf(this)->m_unk1c;
    vertex->x = ppc::fmadds(negW, axis.x, kNullVector.x);
    vertex->y = ppc::fmadds(negW, axis.y, kNullVector.y);
    vertex->z = ppc::fmadds(negW, axis.z, 0.5f);
    ++vertex;
    if (m_unk44 != 0) BuildArcSegmentVerts(&vertex, &branchPoint, &branchDirection);
    geometry->UnlockGeometry();
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 8);
    RwRGBA* color = geometry->m_pRpAtomic->geometry->preLitLum;
    uint32_t from = m_ui8StartAlpha;
    uint32_t to = m_ui8EndAlpha;
    if (m_ui8Flipped != 0) {
        from = m_ui8EndAlpha;
        to = m_ui8StartAlpha;
    }
    uint32_t count = m_unk18;
    if (count != 0) {
        uint32_t accumulated = 0;
        for (uint32_t i = 0; i < count; count = m_unk18) {
            const uint32_t alpha = ppc::divwu(from * (count - i) + accumulated, count);
            accumulated += to;
            ++i;
            color[0].alpha = static_cast<uint8_t>(alpha);
            color[1].alpha = static_cast<uint8_t>(alpha);
            color += 2;
        }
    }
    color[1].alpha = static_cast<uint8_t>(to);
    color[0].alpha = static_cast<uint8_t>(to);
    geometry->UnlockGeometry();
    RwFrame* frame = m_pNode->m_pRwFrame;
    frame->modelling.pos.x = (m_vEnd.x + m_vStart.x) * 0.5f;
    frame->modelling.pos.y = (m_vEnd.y + m_vStart.y) * 0.5f;
    frame->modelling.pos.z = (m_vEnd.z + m_vStart.z) * 0.5f;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(m_pNode->m_pRwFrame);
    const float ey = m_vEnd.y - m_vStart.y;
    const float ex = m_vEnd.x - m_vStart.x;
    const float ez = m_vEnd.z - m_vStart.z;
    const float length = Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
    m_pNode->SetScaleXYZ(1.0f, 1.0f, length);  // 0x000d0e60
}

// 0x001b2940 CKElectricArcNodeFx_Start. Running and shown; the vertices rebuilt, the timers and the branch reset, the
// texture frame taken from the data when within the count; the lifetime (one rand draw with data flag 1); the alpha
// 0xff at once with data flag 4 (else it fades in from 0), the end alphas 0xff.
void CKElectricArcNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    Vf5C();  // vt+0x5c ShowSceneNode
    RebuildArcGeometry();
    m_fRebuildTime = 0.0f;  // stw 0
    m_i16BranchSegment = -1;
    m_fTime = 0.0f;  // stw 0
    CKElectricArcFxData* data = DataOf(this);
    if (data->m_unk38 <= m_unk48) {
        m_ui8Frame = data->m_unk38;
        InitTexCoords();
        data = DataOf(this);
    }
    m_fLifetime = data->m_unk14;
    if (((data->m_flags39 >> 1) & 1) != 0) {
        const float longest = data->m_unk14 + data->m_unk10;
        const float r = RandU16();
        data = DataOf(this);
        m_fLifetime = ppc::fmadds((r / 65535.0f) * -2.0f, data->m_unk10, longest);
    }
    if (((data->m_flags39 >> 4) & 1) != 0) {
        m_ui8Alpha = 0xff;
        ApplyAlpha();
        data = DataOf(this);
    } else {
        m_ui8Alpha = 0;
    }
    m_ui8EndAlpha = 0xff;
    m_ui8StartAlpha = 0xff;
    m_ui8Flipped = 0;
    m_fFadeOutTime = m_fLifetime + (-255.0f / data->m_unk34);
}

// 0x001b2bd0 CKElectricArcNodeFx_Update. With data flag 5 the other geometries are cleared (alpha 0). The lifetime
// runs (data flag 4: forever), the branch segment is drawn once, the vertices rebuilt every data +0x18 seconds; the node
// faces the camera across the start->end line (flipped when the line points against the camera's x axis (+0x5b0)
// vector), centred and stretched (with data flag 3 also widened by the length); then the alpha fades in (data +0x30 per
// second) up to the fade-out time and out (data +0x34 per second) after it.
void CKElectricArcNodeFx::Update(IKTime* frameClock) {
    CKElectricArcFxData* data = DataOf(this);
    if (((data->m_flags39 >> 5) & 1) != 0 && FirstGeometry(this) != nullptr) {
        for (CGeometry* geometry = FirstGeometry(this)->m_pNext; geometry != nullptr; geometry = geometry->m_pNext) {
            uint32_t blended = 1;
            uint8_t alpha = 0;
            if ((geometry->m_BitProperties & 0x1000u) != 0) {
                const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
                if (mode > 0 && mode <= 6) {
                    blended = 0;
                    alpha = 0xff;
                }
            }
            geometry->m_cGeometryColor[3] = alpha;
            const uint32_t flags = geometry->m_BitProperties;
            if (((flags >> 11) & 1u) != blended) {
                geometry->m_BitProperties = (flags & 0xfffff7ffu) | (blended << 11);
                geometry->UpdateProperties();  // vt+0x60
            }
        }
    }
    const float dt = frameClock->m_afDeltaTime[0];
    m_fTime = m_fTime + dt;
    if (!(m_fLifetime > m_fTime) && ((DataOf(this)->m_flags39 >> 4) & 1) == 0) {
        Stop();  // vt+0x6c
        return;
    }
    m_fRebuildTime = m_fRebuildTime + frameClock->m_afDeltaTime[0];
    if (m_i16BranchSegment == -1) {
        const float r = RandU16();
        const float segments = static_cast<float>(m_unk18);
        m_i16BranchSegment = static_cast<int16_t>(ppc::fctiwz(ppc::fmadds(r / 65535.0f, segments - 2.0f, 1.0f)));
    }
    if (m_fRebuildTime > DataOf(this)->m_unk18) {
        RebuildArcGeometry();
        m_fRebuildTime = 0.0f;  // stw 0
    }
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    float dx = m_vEnd.x - m_vStart.x;
    float dy = m_vEnd.y - m_vStart.y;
    float dz = m_vEnd.z - m_vStart.z;
    const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    }
    const CVector3& facing = camera->m_v3RealAxisX;
    const CVector3& axisZ = camera->m_v3RealAxisZ;
    const float dot = ppc::fmadds(dz, facing.z, ppc::fmadds(dx, facing.x, dy * facing.y));
    const float crossZ = ppc::fmsubs(axisZ.y, dx, dy * axisZ.x);
    const float crossY = ppc::fmsubs(axisZ.x, dz, axisZ.z * dx);
    const float crossX = ppc::fmsubs(dy, axisZ.z, axisZ.y * dz);
    float rightX, rightY, rightZ, atX, atY, atZ;
    if (dot < 0.0f) {
        rightX = -crossX;
        rightY = -crossY;
        rightZ = -crossZ;
        m_ui8Flipped = 1;
        atX = -dx;
        atY = -dy;
        atZ = -dz;
    } else {
        rightZ = crossZ;
        rightY = crossY;
        rightX = crossX;
        m_ui8Flipped = 0;
        atZ = dz;
        atY = dy;
        atX = dx;
    }
    RwMatrix* m = &m_pNode->m_pRwFrame->modelling;
    m->right.x = rightX;
    m->right.y = rightY;
    m->right.z = rightZ;
    m->flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(m_pNode->m_pRwFrame);
    const float upZ = ppc::fmsubs(dy, crossX, crossY * dx);
    const float upY = ppc::fmsubs(crossZ, dx, crossX * dz);
    const float upX = ppc::fmsubs(crossY, dz, dy * crossZ);
    m = &m_pNode->m_pRwFrame->modelling;
    m->flags &= 0xfffdfffcu;
    m->up.z = upZ;
    m->up.y = upY;
    m->up.x = upX;
    RwFrame_MarkDirty(m_pNode->m_pRwFrame);
    m = &m_pNode->m_pRwFrame->modelling;
    m->at.x = atX;
    m->at.y = atY;
    m->at.z = atZ;
    m->flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(m_pNode->m_pRwFrame);
    RwFrame* frame = m_pNode->m_pRwFrame;
    frame->modelling.pos.x = (m_vEnd.x + m_vStart.x) * 0.5f;
    frame->modelling.pos.y = (m_vEnd.y + m_vStart.y) * 0.5f;
    frame->modelling.pos.z = (m_vEnd.z + m_vStart.z) * 0.5f;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(m_pNode->m_pRwFrame);
    if (((DataOf(this)->m_flags39 >> 3) & 1) != 0) {
        float ey = m_vEnd.y - m_vStart.y;
        float ex = m_vEnd.x - m_vStart.x;
        float ez = m_vEnd.z - m_vStart.z;
        const float width = Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
        ey = m_vEnd.y - m_vStart.y;
        ex = m_vEnd.x - m_vStart.x;
        ez = m_vEnd.z - m_vStart.z;
        const float depth = Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
        m_pNode->ScaleXYZ(width, 1.0f, depth);  // 0x000d0d28
    } else {
        const float ey = m_vEnd.y - m_vStart.y;
        const float ex = m_vEnd.x - m_vStart.x;
        const float ez = m_vEnd.z - m_vStart.z;
        const float depth = Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
        m_pNode->ScaleXYZ(1.0f, 1.0f, depth);
    }
    data = DataOf(this);
    if ((data->m_flags39 & 0x10) != 0) return;
    uint8_t alpha = m_ui8Alpha;
    if (alpha != 0xff) {
        if (!(m_fTime >= m_fFadeOutTime)) {  // bge
            uint64_t step = static_cast<uint64_t>(ppc::fctidz(data->m_unk30 * frameClock->m_afDeltaTime[0]));
            // --fps N (not in the original): the whole steps of this frame's 60 Hz frames (the per-update trunc is
            // 0 once the frame rate passes the speed: the arc would stay invisible).
            if (dotd::fps::Unlocked()) {
                step = static_cast<uint64_t>(dotd::fps::TruncSteps(data->m_unk30, frameClock->m_afDeltaTime[0]));
            }
            if (static_cast<uint32_t>(0xff - alpha) <= static_cast<uint32_t>(step)) {
                m_ui8Alpha = 0xff;
            } else {
                m_ui8Alpha = static_cast<uint8_t>(step + alpha);
            }
            ApplyAlpha();
            alpha = m_ui8Alpha;
        }
        if (alpha == 0) return;
    }
    if (!(m_fTime > m_fFadeOutTime)) return;  // ble
    int32_t step = ppc::fctiwz(DataOf(this)->m_unk34 * frameClock->m_afDeltaTime[0]);
    if (dotd::fps::Unlocked()) {  // --fps N (not in the original), as the fade-in above
        step = static_cast<int32_t>(dotd::fps::TruncSteps(DataOf(this)->m_unk34, frameClock->m_afDeltaTime[0]));
    }
    if (static_cast<int32_t>(alpha) - step <= 0) {
        m_ui8Alpha = 0;
    } else {
        m_ui8Alpha = static_cast<uint8_t>(alpha - step);
    }
    ApplyAlpha();
}

// 0x001b2018 CKElectricArcNodeFx_PostLoad: IKNodeFx_PostLoad (returns 1), the effect data cleared, the run-time
// points (0, 0, 0) and (0, 0, 1) (TOC -0x2218; the others are TOC -0x220c = 0.0f), then vt+0x60 (the node hidden).
int32_t CKElectricArcNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    m_pFxData = nullptr;
    m_vEnd.x = 0.0f;
    m_vStart.x = 0.0f;
    m_vStart.z = 0.0f;
    m_vStart.y = 0.0f;
    m_vEnd.z = 1.0f;
    m_vEnd.y = 0.0f;
    m_fRebuildTime = 0.0f;
    m_fTime = 0.0f;
    Vf60();          // CKNodeFx3d_HideSceneNode
    return 1;
}

// 0x001b1478 CKElectricArcFxData_Load
int32_t CKElectricArcFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk14);
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk10);
    ReadU8(file, &m_unk38);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk34);
    uint8_t flags = 0;
    ReadU8(file, &flags);
    m_flags39 = flags;
    m_unk08 = 0;
    m_unk0c = nullptr;
    if (((flags >> 2) & 1) != 0) {
        ReadU32LE(file, &m_unk08);
        m_unk0c = new Key[m_unk08];
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk0c), m_unk08 * 2);
    }
    return 1;
}

// 0x001b2118 CKElectricArcNodeFx_Load
int32_t CKElectricArcNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk18);
        ReadU8(file, &m_unk44);
        ReadU8(file, &m_unk48);
    }
    return 1;
}

// 0x001b1cf8 CKElectricArcNodeFx_RecursiveRegistration
void CKElectricArcNodeFx::RecursiveRegistration(int32_t type) {
    IKNodeFx::RecursiveRegistration(type);  // 0x001d88c0 CKNodeFx3d_RecursiveRegistration: the node's, when set
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
