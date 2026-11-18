// CKSpline4L.cpp - reconstructed original translation unit 0xc6410-0xc7648 (GAME_TOC1, main_toc1), 17 functions, 14 live.
// Primary class: CKSpline4L  key 0x7cc  category Logic  size 0x2c  vtable 0xb17d00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc6410  CKSpline4L_Delete
//   [x] 0xc6460  CKSpline4L_RecursiveRegistration  (IKSerializable's: returns 1)
//   [ ] 0xc6468  CKSpline4L_Save
//   [ ] 0xc6470  CKSpline4L_Construct  [dead]
//   [ ] 0xc64b8  CKSpline4L_SetSampleCount_maybe  [dead]
//   [ ] 0xc64e0  CKSpline4L_Construct_2  [dead]
//   [ ] 0xc6528  RegisterCKSpline4LClass
//   [ ] 0xc65a0  _GLOBAL__I_c65a0
//   [x] 0xc65b0  CKSpline4L_DeleteArray
//   [x] 0xc6650  CKSpline4L_vf50  (IKPath::GetPointAt in CKLine.cpp: the same body)
//   [x] 0xc66a8  CKSpline4L_GetClosestDistanceAlong
//   [x] 0xc6df0  CKSpline4L_Destroy  (empty: IKSerializable's)
//   [x] 0xc6df8  CKSpline4L_CreateArray
//   [x] 0xc6ed0  CKSpline4L_Create
//   [x] 0xc6f40  CKSpline4L_Load
//   [x] 0xc7318  CKSpline4L_GetSegmentDirection
//   [x] 0xc7420  CKSpline4L_GetPointAtDistance_maybe
//
//   [ ] 0x9a2080  CKSpline4L_GetClassType  [inline]
//   [ ] 0x9a2088  CKSpline4L_GetClassID  [inline]
//   [x] 0x9a2090  CKSpline4L_GetLength  [inline]
//   [ ] 0x9a2098  CKSpline4L_IsKindOfClass  [inline]
//   [ ] 0x9a20c0  CKSpline4L_Destructor  [inline]
//   [ ] 0x9a2168  CKSpline4L_DeletingDestructor  [inline]
#include "k2000/logic/math/CKSpline4L.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"

// Inlined in 0x000c6ed0 CKSpline4L_Create (CKSpline4L_Construct 0xc6470).
CKSpline4L::CKSpline4L() {
    InitPathVector(CtrlPointsList);
    InitPathVector(SamplePointsList);
}

// 0x000c6f40 CKSpline4L_Load: no type test.
int32_t CKSpline4L::Load(IKFile* file, int32_t /*type*/) {
    m_pPathOwner = nullptr;
    ReadU8(file, &m_ui8NumberOfSegment);
    ReadF32LE(file, &m_fTotalLenght);
    ReadF32LE(file, &m_fPrecision);
    ReadU8(file, &m_bSplineOk);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadPathVector(file, CtrlPointsList, count, true);
    ReadU32LE(file, &count);
    LoadPathVector(file, SamplePointsList, count, true);
    return 1;
}

// IKPath's slots vt+0x54 / +0x58 / +0x5c are pure in the original; CKLine, CKSpline4L and CKSpline4 have their own.
void IKPath::GetPointAtDistance(float /*distance*/, CVector3* /*point*/, CVector3* /*direction*/) {
    DOTD_STUB_ONCE("IKPath vt+0x54: GetPointAtDistance of a path other than CKSpline4L (step 5)");
}
float IKPath::GetClosestDistanceAlong(const CVector3* /*point*/, uint8_t /*squared*/) {
    DOTD_STUB_ONCE("IKPath vt+0x58: GetClosestDistanceAlong of a path other than CKSpline4L / CKLine (CKSpline4_vf58 0x9a1d98: no LVL010 path)");
    return 0.0f;
}
float IKPath::GetLength() {
    DOTD_STUB_ONCE("IKPath vt+0x5c: GetLength of a path other than CKSpline4L (step 5)");
    return 0.0f;
}

// 0x000c7318 CKSpline4L_GetSegmentDirection (Math_Sqrtf is fsqrts)
void CKSpline4L::GetSegmentDirection(uint32_t index, CVector3* direction) const {
    const CVector3* points = SamplePointsList.m_pBlock;
    const CVector3* a;
    const CVector3* b;
    if (index < SamplePointsList.m_ui32NbUsedElt - 1) {
        a = &points[index];
        b = &points[index + 1];
    } else {
        a = &points[index - 1];
        b = &points[index];
    }
    const float dy = b->y - a->y;
    const float dx = b->x - a->x;
    const float dz = b->z - a->z;
    direction->y = dy;
    direction->x = dx;
    direction->z = dz;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    const float z = inverse * direction->z;
    const float x = inverse * direction->x;
    const float y = inverse * direction->y;
    direction->z = z;
    direction->x = x;
    direction->y = y;
}

// 0x000c7420 CKSpline4L_GetPointAtDistance_maybe. The segment index is fctidz(distance / step) compared as a 32-bit
// unsigned value with count - 1; the step and the fraction in single precision.
void CKSpline4L::GetPointAtDistance(float distance, CVector3* point, CVector3* direction) {
    const uint32_t count = SamplePointsList.m_ui32NbUsedElt;
    if (m_fTotalLenght <= distance) {  // fcmpu + cror lt|eq: the length reached
        if (direction != nullptr) GetSegmentDirection(count - 1, direction);
        *point = SamplePointsList.m_pBlock[SamplePointsList.m_ui32NbUsedElt - 1];
        return;
    }
    if (distance < 0.0f) distance = 0.0f;
    const uint32_t last = count - 1;
    const float step = m_fTotalLenght / static_cast<float>(static_cast<double>(static_cast<uint64_t>(last)));
    const uint32_t index = static_cast<uint32_t>(ppc::fctidz(distance / step));
    if (last <= index) {
        if (direction != nullptr) GetSegmentDirection(last, direction);
        *point = SamplePointsList.m_pBlock[SamplePointsList.m_ui32NbUsedElt - 1];
        return;
    }
    const CVector3& a = SamplePointsList.m_pBlock[index];
    const CVector3& b = SamplePointsList.m_pBlock[index + 1];
    const float at = static_cast<float>(static_cast<double>(static_cast<uint64_t>(index)));
    const float u = (distance - step * at) / step;
    point->x = ppc::fmadds(u, b.x - a.x, a.x);
    point->y = ppc::fmadds(u, b.y - a.y, a.y);
    point->z = ppc::fmadds(u, b.z - a.z, a.z);
    if (direction != nullptr) GetSegmentDirection(index, direction);
}

namespace {

// fcfid of the zero-extended 32-bit count, then frsp.
inline float U32ToFloat(uint32_t value) { return static_cast<float>(static_cast<double>(static_cast<uint64_t>(value))); }

// The two measures of 0xc66a8: the squared length (fmuls dy, fmadds dx, fmadds dz) and the sum of the absolute
// differences (each difference stored as a float with its sign bit cleared, then fadds).
inline float SquaredLength(float dx, float dy, float dz) { return ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)); }
inline float AbsSum(float dx, float dy, float dz) { return (std::fabs(dx) + std::fabs(dy)) + std::fabs(dz); }

}  // namespace

// 0x000c66a8 CKSpline4L_GetClosestDistanceAlong. The first sample keeps a tie (the compare is "best <= d"). With
// the nearest sample the first one and the point behind it, the original returns 0 unless the last sample is as near
// (a closed path), then measures against the segment before the last sample from the FIRST sample's offset.
float CKSpline4L::GetClosestDistanceAlong(const CVector3* point, uint8_t squared) {
    const CVector3* samples = SamplePointsList.m_pBlock;
    const uint32_t count = SamplePointsList.m_ui32NbUsedElt;
    float best = squared != 0
                     ? SquaredLength(point->x - samples[0].x, point->y - samples[0].y, point->z - samples[0].z)
                     : AbsSum(point->x - samples[0].x, point->y - samples[0].y, point->z - samples[0].z);
    uint32_t index = 0;
    if (count > 1) {  // cmplwi 1; ble
        for (uint32_t i = 1; i < count; ++i) {  // CTR count - 1
            const CVector3& s = samples[i];
            const float d = squared != 0 ? SquaredLength(point->x - s.x, point->y - s.y, point->z - s.z)
                                         : AbsSum(point->x - s.x, point->y - s.y, point->z - s.z);
            if (!(best <= d)) {  // ble skips
                best = d;
                index = i;
            }
        }
    }
    const uint32_t last = count - 1;
    const CVector3& p = samples[index];
    const float qz = point->z - p.z;  // f22
    const float qx = point->x - p.x;  // f24
    const float qy = point->y - p.y;  // f23
    // The dot product with q: fmuls qy, fmadds qx, fmadds qz.
    auto dot = [&](float ex, float ey, float ez) { return ppc::fmadds(qz, ez, ppc::fmadds(qx, ex, qy * ey)); };
    if (index == 0) {
        const float ey = samples[1].y - samples[0].y;
        const float ex = samples[1].x - samples[0].x;
        const float ez = samples[1].z - samples[0].z;
        const float d = dot(ex, ey, ez);
        if (!(d < 0.0f)) {  // TOC -0x5708: 0.0
            const float length = GetLength();  // vt+0x5c
            return (d * (length / U32ToFloat(last))) / SquaredLength(ex, ey, ez);
        }
        const CVector3& end = samples[last];
        const float atEnd = squared != 0 ? SquaredLength(point->x - end.x, point->y - end.y, point->z - end.z)
                                         : AbsSum(point->x - end.x, point->y - end.y, point->z - end.z);
        if (!(atEnd == best)) return 0.0f;  // bne (unordered too)
        const CVector3& before = samples[count - 2];
        const float by = before.y - end.y;  // f31
        const float bx = before.x - end.x;  // f29
        const float bz = before.z - end.z;  // f30
        // BUG(original): q is still relative to the first sample here.
        const float db = dot(bx, by, bz);
        if (db < 0.0f) return 0.0f;
        const float length = GetLength();
        const float l = U32ToFloat(last);
        return (length / l) * (l - db / SquaredLength(bx, by, bz));
    }
    if (index != last) {
        const CVector3& next = samples[index + 1];
        const CVector3& prev = samples[index - 1];
        const float ny = next.y - p.y;  // f28
        const float nx = next.x - p.x;  // f26
        const float nz = next.z - p.z;  // f27
        const float dn = dot(nx, ny, nz);  // f25
        const float length = GetLength();
        const float step = length / U32ToFloat(last);
        if (dn > 0.0f) return step * (U32ToFloat(index) + dn / SquaredLength(nx, ny, nz));  // ble skips
        const float py = prev.y - p.y;  // f13
        const float px = prev.x - p.x;  // f12
        const float pz = prev.z - p.z;  // f11
        const float dp = dot(px, py, pz);
        if (dp > 0.0f) return step * (U32ToFloat(index) - dp / SquaredLength(px, py, pz));
        return step * U32ToFloat(index);
    }
    const CVector3& before = samples[count - 2];
    const float by = before.y - p.y;  // f31
    const float bx = before.x - p.x;  // f29
    const float bz = before.z - p.z;  // f30
    const float db = dot(bx, by, bz);
    if (db < 0.0f) return GetLength();
    const float length = GetLength();
    const float l = U32ToFloat(index);
    return (length / l) * (l - db / SquaredLength(bx, by, bz));
}
