// CKSpline4.cpp - reconstructed original translation unit 0xc5140-0xc6410 (GAME_TOC1, main_toc1), 18 functions, 14 live.
// Primary class: CKSpline4  key 0x2cc  category Logic  size 0x50  vtable 0xb17c30
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc5140  CKSpline4_Delete
//   [x] 0xc5190  CKSpline4_RecursiveRegistration  (IKSerializable's: returns 1)
//   [ ] 0xc5198  CKSpline4_Save
//   [ ] 0xc51a0  CKSpline4_Construct  [dead]
//   [x] 0xc5220  CKSpline4_vf50  (IKPath::GetPointAt in CKLine.cpp: the same body)
//   [x] 0xc5278  CKSpline4_EvaluateSegment_maybe
//   [ ] 0xc53d8  CKSpline4_SetSampleCount_maybe  [dead]
//   [ ] 0xc5400  RegisterCKSpline4Class
//   [ ] 0xc5478  _GLOBAL__I_c5478
//   [x] 0xc5488  CKSpline4_EvaluateSegmentTangent_maybe
//   [x] 0xc5648  CKSpline4_DeleteArray
//   [ ] 0xc56f0  CKSpline4_GetSegmentLength_maybe  [dead]
//   [x] 0xc5800  CKSpline4_GetPointAtDistance_maybe
//   [ ] 0xc5ac0  CKSpline4_Construct_2  [dead]
//   [x] 0xc5b40  CKSpline4_Destroy  (empty: IKSerializable's)
//   [x] 0xc5b48  CKSpline4_CreateArray
//   [x] 0xc5c70  CKSpline4_Create
//   [x] 0xc5d20  CKSpline4_Load
//
//   [x] 0x9a1d98  CKSpline4_vf58  [inline]  (header: 0.0)
//   [ ] 0x9a1da0  CKSpline4_GetClassType  [inline]
//   [ ] 0x9a1da8  CKSpline4_GetClassID  [inline]
//   [x] 0x9a1db0  CKSpline4_GetLength  [inline]  (header)
//   [ ] 0x9a1db8  CKSpline4_IsKindOfClass  [inline]
//   [ ] 0x9a1de0  CKSpline4_DeletingDestructor  [inline]
//   [ ] 0x9a1f08  IKPath_Destructor  [inline]
//   [ ] 0x9a1f20  CKSpline4_Destructor  [inline]
//   [ ] 0x9a2040  IKPath_DeletingDestructor  [inline]
#include "k2000/logic/math/CKSpline4.h"

#include <cmath>

#include "crt/ppc_ops.h"

// 0x000c51a0 CKSpline4_Construct (inlined in 0x000c5c70 CKSpline4_Create).
CKSpline4::CKSpline4() {
    InitPathVector(CtrlPointsList);
    InitPathVector(SegmentLenghtList);
    InitPathVector(SplineSegmentRef);
    InitPathVector(SplineUniformSamples);
    InitPathVector(SplineSegmentTransition);
}

// 0x000c5d20 CKSpline4_Load: no type test.
int32_t CKSpline4::Load(IKFile* file, int32_t /*type*/) {
    m_pPathOwner = nullptr;
    ReadU8(file, &m_ui8NumberOfSegment);
    ReadF32LE(file, &m_fTotalLenght);
    ReadF32LE(file, &m_fPrecision);
    ReadU8(file, &m_bSplineOk);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadPathVector(file, CtrlPointsList, count, true);
    ReadU32LE(file, &count);
    LoadPathVector(file, SegmentLenghtList, count, true);
    ReadU32LE(file, &count);
    LoadPathVector(file, SplineSegmentRef, count, false);
    ReadU32LE(file, &count);
    LoadPathVector(file, SplineUniformSamples, count, true);
    ReadU32LE(file, &count);
    LoadPathVector(file, SplineSegmentTransition, count, true);
    return 1;
}

// 0x000c5278 CKSpline4_EvaluateSegment_maybe. s = 1 - t, u = 1 - s (not t); the weights s^3, 3 s^2 u, 3 s u^2, u^3 as
// the original multiplies them, each coordinate a fmuls and three fmadds (P1, P0, P2, P3).
void CKSpline4::EvaluateSegment(float t, uint32_t segment, CVector3* out) const {
    const float s = 1.0f - t;
    const float s3 = s * 3.0f;
    const float u = 1.0f - s;
    const float w1 = (s * s3) * u;  // P1
    const float w2 = u * (s3 * u);  // P2
    const float w0 = s * (s * s);   // P0
    const float w3 = u * (u * u);   // P3
    const CVector3* p = CtrlPointsList.m_pBlock + segment * 4;
    out->x = ppc::fmadds(w3, p[3].x, ppc::fmadds(w2, p[2].x, ppc::fmadds(w0, p[0].x, w1 * p[1].x)));
    out->y = ppc::fmadds(w3, p[3].y, ppc::fmadds(w2, p[2].y, ppc::fmadds(w0, p[0].y, w1 * p[1].y)));
    out->z = ppc::fmadds(w3, p[3].z, ppc::fmadds(w2, p[2].z, ppc::fmadds(w0, p[0].z, w1 * p[1].z)));
}

// 0x000c5488 CKSpline4_EvaluateSegmentTangent_maybe. Per coordinate: A = P0 + t (P1 - P0), B = P1 + t (P2 - P1),
// C = P3 + s (P2 - P3), then (C + s (B - C)) - (A + t (B - A)); Math_Sqrtf (fsqrts) of y^2 + x^2 + z^2, and the
// vector scaled by 1 / length unless the length is 0.
void CKSpline4::EvaluateSegmentTangent(float t, uint32_t segment, CVector3* out) const {
    const float s = 1.0f - t;
    const CVector3* p = CtrlPointsList.m_pBlock + segment * 4;
    auto axis = [&](float p0, float p1, float p2, float p3) {
        const float a = ppc::fmadds(p1 - p0, t, p0);
        const float b = ppc::fmadds(p2 - p1, t, p1);
        const float c = ppc::fmadds(p2 - p3, s, p3);
        return ppc::fmadds(s, b - c, c) - ppc::fmadds(t, b - a, a);
    };
    const float y = axis(p[0].y, p[1].y, p[2].y, p[3].y);
    const float x = axis(p[0].x, p[1].x, p[2].x, p[3].x);
    const float z = axis(p[0].z, p[1].z, p[2].z, p[3].z);
    out->y = y;
    out->x = x;
    out->z = z;
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    const float nz = inverse * out->z;
    const float nx = inverse * out->x;
    const float ny = inverse * out->y;
    out->z = nz;
    out->x = nx;
    out->y = ny;
}

// 0x000c5800 CKSpline4_GetPointAtDistance_maybe. The sample index is fctidz(distance / step), compared as a 32-bit
// unsigned value with count - 1; the tangent (with `direction`) before the point, as the original calls them.
void CKSpline4::GetPointAtDistance(float distance, CVector3* point, CVector3* direction) {
    float t;
    uint32_t segment;
    if (m_fTotalLenght <= distance) {  // fcmpu + cror lt|eq
        t = 1.0f;
        segment = static_cast<uint32_t>(m_ui8NumberOfSegment) - 1;
    } else if (distance <= 0.0f) {  // cror lt|eq
        t = 0.0f;
        segment = 0;
    } else {
        const uint32_t last = SplineUniformSamples.m_ui32NbUsedElt - 1;
        const float* samples = SplineUniformSamples.m_pBlock;
        const uint8_t* refs = SplineSegmentRef.m_pBlock;
        const float step = m_fTotalLenght / static_cast<float>(static_cast<double>(static_cast<uint64_t>(last)));
        const uint32_t index = static_cast<uint32_t>(ppc::fctidz(distance / step));
        const float at = static_cast<float>(static_cast<double>(static_cast<uint64_t>(index)));
        const float fraction = (distance - step * at) / step;
        if (last <= index) {  // ble (unsigned)
            const float s0 = samples[index];
            segment = refs[index];
            t = ppc::fmadds(fraction, 1.0f - s0, s0);
        } else {
            const uint8_t first = refs[index];
            const uint8_t second = refs[index + 1];
            if (first == second) {
                const float s0 = samples[index];
                t = ppc::fmadds(fraction, samples[index + 1] - s0, s0);
                segment = second;
            } else {
                const float transition = SplineSegmentTransition.m_pBlock[first];
                if (!(fraction < transition)) {  // bge: not less (NaN takes it)
                    t = ((fraction - transition) / (1.0f - transition)) * samples[index + 1];
                    segment = second;
                } else {
                    const float s0 = samples[index];
                    t = ppc::fmadds(fraction / transition, 1.0f - s0, s0);
                    segment = first;
                }
            }
        }
    }
    if (direction != nullptr) EvaluateSegmentTangent(t, segment, direction);
    EvaluateSegment(t, segment, point);
}
