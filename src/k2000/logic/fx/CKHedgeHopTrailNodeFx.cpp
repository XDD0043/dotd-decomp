// CKHedgeHopTrailNodeFx.cpp - reconstructed original translation unit: 0x1c0f90-0x1c34f0 (GAME_TOC1, main_toc1), 20 functions, 17 live.
// Primary class: CKHedgeHopTrailNodeFx  key 0x2c4c  category Logic  size 0x70  vtable 0xb1cf88
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1c0f90  RegisterCKHedgeHopTrailNodeFxClass
//   [ ] 0x1c1008  _GLOBAL__I_1c1008
//   [ ] 0x1c1018  CKHedgeHopTrailNodeFx_AllocTrailPoints_maybe  [dead]
//   [x] 0x1c10e0  CKHedgeHopTrailNodeFx_CacheUVTransform_maybe  (no caller: only its descriptor)
//   [ ] 0x1c1120  CKHedgeHopTrailNodeFx_Save
//   [x] 0x1c1148  CKHedgeHopTrailNodeFx_RecursiveRegistration
//   [x] 0x1c11b8  CKHedgeHopTrailNodeFx_Destroy
//   [x] 0x1c1208  CKHedgeHopTrailNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1c12b0  CKHedgeHopTrailNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1c1368  CKHedgeHopTrailNodeFx_InitVertexAlphaGradient_maybe  (no caller: only its descriptor)
//   [x] 0x1c1450  CKHedgeHopTrailNodeFx_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x1c14a8  CKHedgeHopTrailNodeFx_Load
//   [ ] 0x1c1688  CKHedgeHopTrailNodeFx_ComputeSegmentUVAlpha_maybe  [dead]
//   [x] 0x1c1b20  CKHedgeHopTrailNodeFx_Stop
//   [x] 0x1c1bf0  CKHedgeHopTrailNodeFx_Start
//   [x] 0x1c1c88  CKHedgeHopTrailNodeFx_RespaceTrailSide_maybe
//   [x] 0x1c1f38  CKHedgeHopTrailNodeFx_ExtrudeTrailRibbon_maybe
//   [x] 0x1c23b8  CKHedgeHopTrailNodeFx_UpdateTrailGeometry_maybe
//   [x] 0x1c2a60  CKHedgeHopTrailNodeFx_Update  (CKHedgeHopTrailNodeFx.h)
//   [ ] 0x1c2a68  CKHedgeHopTrailNodeFx_SetPoseForOwner_maybe  [dead]
//
//   [x] 0x9ac648  CKHedgeHopTrailNodeFx_IsKindOfClass  [inline]  (CKHedgeHopTrailNodeFx.h)
//   [x] 0x9ac680  CKHedgeHopTrailNodeFx_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac688  CKHedgeHopTrailNodeFx_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac690  CKHedgeHopTrailNodeFx_GetFxData  [inline]
//   [x] 0x9ac698  CKHedgeHopTrailNodeFx_SetFxData  [inline]
//   [x] 0x9ac6a0  CKHedgeHopTrailNodeFx_DeletingDestruct  [inline]  (the destructor)
//   [x] 0x9ac6e8  CKHedgeHopTrailNodeFx_Destruct  [inline]  (the destructor)
#include "k2000/logic/fx/CKHedgeHopTrailNodeFx.h"

#include <cmath>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKHedgeHopTrailFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/system/IKTime.h"

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64

// The length of a - b as the unit computes it everywhere (y squared first, then x and z fused in).
float Distance(const CVector3& a, const CVector3& b) {
    const float dy = a.y - b.y;
    const float dx = a.x - b.x;
    const float dz = a.z - b.z;
    return std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
}

CGeometry* FirstGeometry(CNode* node) { return static_cast<CGeometry*>(node->m_lGeometryList); }
}  // namespace

CKHedgeHopTrailNodeFx::CKHedgeHopTrailNodeFx() {}
CKHedgeHopTrailNodeFx::~CKHedgeHopTrailNodeFx() {}

IKFxData* CKHedgeHopTrailNodeFx::GetFxData() { return m_pData; }  // 0x009ac690
void CKHedgeHopTrailNodeFx::SetFxData(IKFxData* data) { m_pData = static_cast<CKHedgeHopTrailFxData*>(data); }  // 0x009ac698

// 0x001c10e0 CKHedgeHopTrailNodeFx_CacheUVTransform_maybe
void CKHedgeHopTrailNodeFx::CacheUVTransform() {
    m_pUVTransform = static_cast<CMaterial*>(FirstGeometry(m_pNode)->m_pMaterial)->GetUVTransformMatrix();
}

// 0x001c11b8 CKHedgeHopTrailNodeFx_Destroy
void CKHedgeHopTrailNodeFx::Destroy() {
    IKNodeFx::Destroy();
    if (m_pPoints != nullptr) {
        Mem_FreeAligned16(m_pPoints);
        m_pPoints = nullptr;
    }
}

// 0x001c1148 CKHedgeHopTrailNodeFx_RecursiveRegistration
void CKHedgeHopTrailNodeFx::RecursiveRegistration(int32_t type) {
    IKNodeFx::RecursiveRegistration(type);
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // engine +0x50, vt+0x24
}

// 0x001c14a8 CKHedgeHopTrailNodeFx_Load: IKNodeFx's; level files then read the vertex and point counts (byte-swapped),
// keep the material's UV matrix and allocate the 4 x points buffer, every point the origin; side 1 starts at the
// buffer's middle.
int32_t CKHedgeHopTrailNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbVertices);
    ReadU32LE(file, &m_ui32NbPoints);
    const uint32_t count = m_ui32NbPoints;
    m_pUVTransform = static_cast<CMaterial*>(FirstGeometry(m_pNode)->m_pMaterial)->GetUVTransformMatrix();
    m_pPoints = nullptr;
    m_pPoints = static_cast<CVector3*>(Mem_AllocAligned16(count * 4u * static_cast<uint32_t>(sizeof(CVector3))));
    for (uint32_t i = 0; i < count * 4u; ++i) m_pPoints[i] = kNullVector;
    m_apSide[0] = m_pPoints;
    m_apSide[1] = m_pPoints + m_ui32NbPoints * 2u;
    return 1;
}

// 0x001c1bf0 CKHedgeHopTrailNodeFx_Start: running, the node shown (vt+0x5c), growing from no points, not fading.
void CKHedgeHopTrailNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    Vf5C();
    m_baTrail = static_cast<uint8_t>((m_baTrail & 0xfe) | 1);
    m_aui32NbUsed[1] = 0;
    m_aui32NbUsed[0] = 0;
    m_baTrail = static_cast<uint8_t>(m_baTrail & 0xfd);
}

// 0x001c1b20 CKHedgeHopTrailNodeFx_Stop: fading instead of growing, stopped, the node hidden (vt+0x60); the first
// geometry opaque (alpha 0xff, the blend bit cleared with the stage update).
void CKHedgeHopTrailNodeFx::Stop() {
    m_baTrail = static_cast<uint8_t>((m_baTrail & 0xfc) | 2);
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    Vf60();
    CGeometry* geometry = FirstGeometry(m_pNode);
    geometry->m_cGeometryColor[3] = 0xff;
    const uint32_t bits = geometry->m_BitProperties;
    if ((bits & 0x800u) != 0) {
        geometry->m_BitProperties = bits & 0xfffff7ffu;
        geometry->UpdateProperties();  // vt+0x60
    }
}

// 0x001c1368 CKHedgeHopTrailNodeFx_InitVertexAlphaGradient_maybe: the geometry locked for its prelit colours (8); per
// side the two halves (m_ui32NbVertices / 2 each) get alphas 0xff, 0xff - step, ... (step = 0xff / (half - 1), divwu;
// clamped at 0); unlocked.
void CKHedgeHopTrailNodeFx::InitVertexAlphaGradient() {
    CGeometry* geometry = FirstGeometry(m_pNode);
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 8);
    RwRGBA* prelit = geometry->m_pRpAtomic->geometry->preLitLum;
    for (uint32_t side = 0; side < 2; ++side) {
        uint32_t alpha = 0xff;
        const uint32_t half = m_ui32NbVertices >> 1;
        RwRGBA* a = prelit + m_ui32NbVertices * side;
        RwRGBA* b = prelit + (m_ui32NbVertices * side + half);
        const uint32_t step = ppc::divwu(0xffu, half - 1);
        for (uint32_t i = 0; i < half; ++i) {
            a[i].alpha = static_cast<RwUInt8>(alpha);
            b[i].alpha = static_cast<RwUInt8>(alpha);
            const bool under = alpha < step;
            alpha -= step;
            if (under) alpha = 0;
        }
    }
    geometry->UnlockGeometry();
}

// 0x001c1c88 CKHedgeHopTrailNodeFx_RespaceTrailSide_maybe: d = |A[0] - anchor A|; the strip's direction from A[0]
// to A[1] (normalised unless 0); both heads set to their anchors; then each later point i (1 .. n - 1) of both strips
// moves by d along the A strip's direction at i - 1 (A[i - 1] - A[i], re-measured after each move; the last
// measure reads A[n], the B strip's head).
float CKHedgeHopTrailNodeFx::RespaceTrailSide(uint32_t side) {
    CVector3* a = m_apSide[side];
    const Anchors& anchors = m_aAnchors[side];
    const uint32_t count = m_ui32NbPoints;
    const float d = Distance(a[0], anchors.m_vA);
    float dy = a[0].y - a[1].y;
    float dx = a[0].x - a[1].x;
    float dz = a[0].z - a[1].z;
    CVector3* b = a + count;
    float len = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (len != 0.0f) {
        const float inv = 1.0f / len;
        dz = dz * inv;
        dx = dx * inv;
        dy = dy * inv;
    }
    a[0] = anchors.m_vA;
    b[0] = anchors.m_vB;
    if (count > 1) {
        float sx = dx * d;
        float sy = dy * d;
        float sz = dz * d;
        uint32_t i = 1;
        for (;;) {
            a[i].y = sy + a[i].y;
            a[i].x = sx + a[i].x;
            a[i].z = sz + a[i].z;
            b[i].y = sy + b[i].y;
            b[i].x = sx + b[i].x;
            b[i].z = sz + b[i].z;
            dy = a[i].y - a[i + 1].y;
            dx = a[i].x - a[i + 1].x;
            dz = a[i].z - a[i + 1].z;
            ++i;
            len = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            if (len != 0.0f) {
                const float inv = 1.0f / len;
                dz = dz * inv;
                dx = dx * inv;
                dy = dy * inv;
            }
            if (count == i) break;
            sx = dx * d;
            sy = dy * d;
            sz = dz * d;
        }
    }
    return d;
}

// 0x001c1f38 CKHedgeHopTrailNodeFx_ExtrudeTrailRibbon_maybe. Per side, over its used points (at most m_ui32NbPoints),
// from the last back to the head: B = A + unit(B - A) * min(|B - A| + extend * dt (fused), cap) (fused), the cap from
// m_fMaxSegment shrinking by (1 - decay * 0.01) per point down to m_fMinSegment (ble / bge: NaN keeps); the unused
// points copy the last used one. Then, over all points: where the two sides' A points are closer than the spread
// threshold (bge: NaN not), side 0's points move by -spread * 0.5 * dt along unit(A1 - A0) and side 1's by +; the
// threshold grows from m_fMinSpread by (spread growth * 0.01 + 1) (fused) per point up to m_fMaxSpread.
void CKHedgeHopTrailNodeFx::ExtrudeTrailRibbon(IKTime* frameClock) {
    const float hundredth = 0.01f;  // TOC -0x1ea4
    const float one = 1.0f;         // TOC -0x1ebc
    const uint32_t count = m_ui32NbPoints;
    const float decay = m_pData->m_fSegmentDecay * hundredth;
    const float minSegment = m_pData->m_fMinSegment;
    const float maxSegment = m_pData->m_fMaxSegment;
    for (uint32_t side = 0; side < 2; ++side) {
        uint32_t used = count;
        if (count > m_aui32NbUsed[side]) used = m_aui32NbUsed[side];
        CVector3* points = m_apSide[side];
        if (used != 0) {
            const float keep = one - decay;
            float cap = maxSegment;
            for (uint32_t j = 0; j < used; ++j) {
                CVector3* a = &points[used - 1 - j];
                CVector3* b = a + count;
                float dy = b->y - a->y;
                float dx = b->x - a->x;
                float dz = b->z - a->z;
                float len = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
                if (len != 0.0f) {
                    const float inv = one / len;
                    dz = dz * inv;
                    dx = dx * inv;
                    dy = dy * inv;
                } else {
                    len = 0.0f;
                }
                len = ppc::fmadds(m_pData->m_fExtendSpeed, frameClock->m_afDeltaTime[0], len);
                if (!(cap >= len)) len = cap;  // bge
                cap = cap * keep;
                const float z = ppc::fmadds(dz, len, a->z);
                const float x = ppc::fmadds(len, dx, a->x);
                const float y = ppc::fmadds(dy, len, a->y);
                b->z = z;
                b->x = x;
                b->y = y;
                if (minSegment > cap) cap = minSegment;  // ble
            }
        }
        if (used < count) {
            // BUG(original): with no point used yet (every frame right after Start) the source is the point before the
            // strip: side 0 reads the 12 bytes in front of the buffer, side 1 side 0's last B point.
            const CVector3* lastA = points + (static_cast<intptr_t>(used) - 1);
            const CVector3* lastB = lastA + count;
            for (uint32_t k = count - 1, n = count - used; n != 0; --n, --k) {
                points[k] = *lastA;
                points[k + count] = *lastB;
            }
        }
    }
    const float maxSpread = m_pData->m_fMaxSpread;
    float threshold = m_pData->m_fMinSpread;
    if (count == 0) return;
    CVector3* a0 = m_apSide[0];
    CVector3* a1 = m_apSide[1];
    CVector3* b0 = a0 + count;
    CVector3* b1 = a1 + count;
    const float half = 0.5f;  // TOC -0x1ea0
    for (uint32_t i = 0; i < count; ++i) {
        float dy = a1[i].y - a0[i].y;
        float dx = a1[i].x - a0[i].x;
        float dz = a1[i].z - a0[i].z;
        float len = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (len != 0.0f) {
            const float inv = one / len;
            dz = dz * inv;
            dx = dx * inv;
            dy = dy * inv;
        } else {
            len = 0.0f;
        }
        if (!(len >= threshold)) {  // bge
            const float s = (m_pData->m_fSpreadSpeed * half) * frameClock->m_afDeltaTime[0];
            const float ns = -s;
            const float pz = dz * s;
            const float px = dx * s;
            const float py = dy * s;
            const float mz = dz * ns;
            const float mx = dx * ns;
            const float my = dy * ns;
            a0[i].z = a0[i].z + mz;
            a0[i].x = a0[i].x + mx;
            a0[i].y = a0[i].y + my;
            a1[i].x = a1[i].x + px;
            a1[i].z = a1[i].z + pz;
            b1[i].x = px + b1[i].x;
            b1[i].z = pz + b1[i].z;
            a1[i].y = a1[i].y + py;
            b0[i].x = mx + b0[i].x;
            b1[i].y = py + b1[i].y;
            b0[i].z = mz + b0[i].z;
            b0[i].y = my + b0[i].y;
        }
        threshold = threshold * ppc::fmadds(m_pData->m_fSpreadGrowth, hundredth, one);
        if (!(maxSpread >= threshold)) threshold = maxSpread;  // bge
    }
}

// 0x001c23b8 CKHedgeHopTrailNodeFx_UpdateTrailGeometry_maybe.
// Growing (bit 0), per side with fewer than points + 1 used: when |A[0] - A[1]| is below the spacing (length /
// (points - 1), bgt: NaN not) the heads just move to the anchors (a distance to the anchor is measured and not used);
// else one more point is used and, still below points + 1, every point shifts one place down the strips and the
// heads take the anchors. A side past m_ui32NbPoints used is respaced. Growing or fading: extruded, the geometry locked
// (10 while fading, else 0x1a), each side's strips sampled (Bezier, half the vertices each) into the morph target's
// vertices; while fading the prelit alphas lose fade speed * dt (fctiwz, the low byte; 0 at the floor) and once side
// 1's two halves are all 0, the fading bit is cleared and the effect stops (vt+0x6c). The atomic's bounding sphere
// (resynced first when flagged 2) is put at the node's LTM position with radius 300000, flag 2 cleared, its world bound
// marked dirty.
int32_t CKHedgeHopTrailNodeFx::UpdateTrailGeometry(IKTime* frameClock) {
    const uint32_t count = m_ui32NbPoints;
    CGeometry* geometry = FirstGeometry(m_pNode);
    int32_t result = 0;
    bool rebuild = true;
    if ((m_baTrail & 1) != 0) {
        for (uint32_t side = 0; side < 2; ++side) {
            uint32_t used = m_aui32NbUsed[side];
            if (used < count + 1) {
                CVector3* a = m_apSide[side];
                const float d = Distance(a[0], a[1]);
                const float spacing = m_pData->m_fLength / static_cast<float>(static_cast<double>(count - 1));
                if (spacing > d) {
                    (void)Distance(a[0], m_aAnchors[side].m_vA);  // measured, not used
                    a[0] = m_aAnchors[side].m_vA;
                    a[count] = m_aAnchors[side].m_vB;
                    used = m_aui32NbUsed[side];
                } else {
                    used = m_aui32NbUsed[side] + 1;
                    m_aui32NbUsed[side] = used;
                    if (count + 1 > used) {
                        CVector3* points = m_apSide[side];
                        for (uint32_t k = count - 1; k != 0; --k) {
                            points[k] = points[k - 1];
                            points[count + k] = points[count + k - 1];
                        }
                        points[0] = m_aAnchors[side].m_vA;
                        points[count] = m_aAnchors[side].m_vB;
                        used = m_aui32NbUsed[side];
                    }
                }
            }
            if (used > count) RespaceTrailSide(side);
        }
    } else if (((m_baTrail >> 1) & 1) == 0) {
        rebuild = false;
    }
    if (rebuild) {
        ExtrudeTrailRibbon(frameClock);
        RpGeometry* rp = geometry->m_pRpAtomic->geometry;
        RpGeometryLock(rp, ((m_baTrail >> 1) & 1) != 0 ? 10 : 0x1a);
        rp = geometry->m_pRpAtomic->geometry;
        RwRGBA* prelit = rp->preLitLum;
        RwV3d* verts = rp->morphTarget->verts;
        for (uint32_t side = 0; side < 2; ++side) {
            const int32_t half = static_cast<int32_t>(m_ui32NbVertices >> 1);
            CVector3* strips = m_apSide[side];
            Bezier_SampleCurvePoints(static_cast<int32_t>(count), strips, half, reinterpret_cast<CVector3*>(verts));
            Bezier_SampleCurvePoints(static_cast<int32_t>(count), strips + m_ui32NbPoints, half,
                                     reinterpret_cast<CVector3*>(verts) + half);
            const uint32_t nv = m_ui32NbVertices;
            verts += nv;
            if ((m_baTrail & 2) == 0) continue;
            const uint8_t step = static_cast<uint8_t>(ppc::fctiwz(m_pData->m_fFadeSpeed * frameClock->m_afDeltaTime[0]));
            bool allA = true;
            bool allB = true;
            const uint32_t n = nv >> 1;
            RwRGBA* pa = prelit + nv * side;
            RwRGBA* pb = prelit + (nv * side + n);
            for (uint32_t i = 0; i < n; ++i) {
                if (step < pa[i].alpha) {
                    pa[i].alpha = static_cast<RwUInt8>(pa[i].alpha - step);
                    allA = false;
                } else {
                    pa[i].alpha = 0;
                }
                if (step < pb[i].alpha) {
                    pb[i].alpha = static_cast<RwUInt8>(pb[i].alpha - step);
                    allB = false;
                } else {
                    pb[i].alpha = 0;
                }
            }
            if (side == 1) {
                if (allA && allB) {
                    m_baTrail = static_cast<uint8_t>(m_baTrail & ~2);
                    Stop();  // vt+0x6c
                }
                break;
            }
        }
        result = 1;
        geometry->UnlockGeometry();
    }
    if (geometry != nullptr) {
        RpAtomic* atomic = geometry->m_pRpAtomic;
        const RwFrame* frame = m_pNode->m_pRwFrame;
        if ((atomic->flags & 2u) != 0) {
            _rpAtomicResyncInterpolatedSphere(atomic);
            atomic = geometry->m_pRpAtomic;
        }
        atomic->boundingSphere[0] = frame->ltm.pos.x;
        atomic->boundingSphere[1] = frame->ltm.pos.y;
        atomic->boundingSphere[2] = frame->ltm.pos.z;
        atomic->boundingSphere[3] = 300000.0f;  // TOC -0x1e9c
        geometry->m_pRpAtomic->flags &= ~2u;
        geometry->m_pRpAtomic->privateFlags = static_cast<uint8_t>(geometry->m_pRpAtomic->privateFlags | 1);
    }
    return result;
}
