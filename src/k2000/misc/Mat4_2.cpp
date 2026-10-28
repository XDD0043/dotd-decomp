// Mat4_2.cpp - reconstructed original translation unit 0x246bb8-0x2472f0 (GAME_TOC1, main_toc1), 13 functions, 7 live.
// Primary owner: Mat4 (not a registered class)
// Other owners: CurveKeys (2), CKSinCurve2DCpnt (2), Curve (1), Matrix (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x246bb8  Curve_EvaluatePiecewiseLinear
//   [ ] 0x246ce8  CurveKeys_Equals_2_maybe  [dead]
//   [ ] 0x246db8  CurveKeys_NotEquals_2_maybe  [dead]
//   [x] 0x246e88  CKSinCurve2DCpnt_LoadKeys_maybe
//   [ ] 0x247068  CKSinCurve2DCpnt_SaveKeys_maybe  [dead]
//   [ ] 0x2471c0  KStub_Nop_2471c0  [dead]
//   [ ] 0x2471c8  KStub_Nop_2471c8  [dead]
//   [ ] 0x2471d0  KStub_Nop_2471d0
//   [ ] 0x2471d8  Mat4_OrthoNormalize
//   [ ] 0x247200  Matrix_OrthoNormalizeInPlace
//   [ ] 0x247228  Mat4_TransformVector
//   [ ] 0x247260  Mat4_TransformPoint
//   [ ] 0x247298  Mat4_Transpose_maybe  [dead]
#include <cstring>

#include "k2000/components/CKSinCurve2DCpnt.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// One Read of count words, then every word byte-swapped in place (an lwbrx/stw loop on the PS3). The
// file is little-endian: on a little-endian host the bytes stay as they are.
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    ReadRaw(file, dst, count * 4);
    uint8_t* p = static_cast<uint8_t*>(dst);
    for (uint32_t i = 0; i < count; ++i, p += 4) {
        const uint32_t v = static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
                           (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
        std::memcpy(p, &v, 4);
    }
}
}  // namespace

// 0x00246e88 CKSinCurve2DCpnt_LoadKeys_maybe
void CKSinCurve2DCpnt_LoadKeys(TVector<CKCurve2DCpnt::Point, 20>* points, IKFile* file) {
    uint32_t dropped = 0;  // swapped into a stack word and never used
    ReadU32LE(file, &dropped);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return;
    using Point = CKCurve2DCpnt::Point;
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    points->m_ui32NbElt = count;
    points->m_pBlock = static_cast<Point*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Point))));
    if (points->m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = (count / 20) * 20 + 20;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Point));
        if (capacity == 0) {
            capacity = 20;
            bytes = 20 * static_cast<uint32_t>(sizeof(Point));
        }
        points->m_pBlock = static_cast<Point*>(Mem_ReallocAligned16(points->m_pBlock, bytes));
        points->m_ui32NbElt = capacity;
    }
    points->m_ui32NbUsedElt = count;
    ReadWordsLE(file, points->m_pBlock, count * 2);  // one read of count points (8 bytes each)
}

// 0x00246bb8 Curve_EvaluatePiecewiseLinear. The tests in the original's order: before the first point and after the last
// the end values; then t equal to the first point's x, then, per segment (lo, hi): t equal to hi's x (its y), inside
// (lo.x, hi.x) the interpolation (1 - u) * lo.y + u * hi.y (fmadds), else on to the next segment; 0 after the last.
float Curve_EvaluatePiecewiseLinear(float t, const TVector<CKCurve2DCpnt::Point, 20>* points) {
    using Point = CKCurve2DCpnt::Point;
    const uint32_t count = points->m_ui32NbUsedElt;
    if (count == 0) return 0.0f;
    const Point* p = points->m_pBlock;
    if (count == 1) return p[0].m_fY;
    if (p[0].m_fX > t) return p[0].m_fY;
    if (p[count - 1].m_fX < t) return p[count - 1].m_fY;
    if (p[0].m_fX == t) return p[0].m_fY;
    if (t == p[1].m_fX) return p[1].m_fY;
    for (uint32_t i = 0;; ++i) {
        const Point& lo = p[i];
        const Point& hi = p[i + 1];
        if (t > lo.m_fX && t < hi.m_fX) {
            const float u = (t - lo.m_fX) / (hi.m_fX - lo.m_fX);
            return ppc::fmadds(1.0f - u, lo.m_fY, u * hi.m_fY);
        }
        if (i + 2 >= count) return 0.0f;  // the last segment tested (bdnz)
        if (t == p[i + 1].m_fX) return p[i + 1].m_fY;
        if (t == p[i + 2].m_fX) return p[i + 2].m_fY;
    }
}
