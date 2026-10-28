// CKCurve2DCpnt.cpp - reconstructed original translation unit 0x2495d0-0x24a0d0 (GAME_TOC1, main_toc1), 19 functions, 15 live.
// Primary class: CKCurve2DCpnt  key 0x5ac6  category Component  size 0x14  vtable 0xb20ce8
// Other owners: Spline2D (2), CKCurve (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2495d0  CKCurve2DCpnt_Delete
//   [ ] 0x249620  CKCurve2DCpnt_Construct  [dead]
//   [ ] 0x249640  Spline2D_CatmullRomPoint_maybe  [dead]
//   [ ] 0x2496f8  Spline2D_CatmullRomY_maybe  [dead]
//   [ ] 0x249778  CKCurve2DCpnt_Construct_2  [dead]
//   [ ] 0x249798  RegisterCKCurve2DCpntClass
//   [ ] 0x249810  _GLOBAL__I_249810
//   [ ] 0x249820  CKCurve2DCpnt_Destructor
//   [x] 0x249878  CKCurve2DCpnt_DeleteArray
//   [x] 0x249920  CKCurve2DCpnt_CreateArray
//   [x] 0x2499e8  CKCurve2DCpnt_Create
//   [ ] 0x249a38  CKCurve2DCpnt_Save
//   [ ] 0x249a40  CKCurve2DCpnt_RecursiveRegistration
//   [ ] 0x249a48  CKCurve2DCpnt_Destroy
//   [x] 0x249a98  CKCurve2DCpnt_Load
//   [ ] 0x249c78  CKCurve2DCpnt_Destructor_2
//   [ ] 0x249cd0  CKCurve2DCpnt_DeletingDestructor
//   [x] 0x249d30  CKCurve_EvaluateKeys_maybe
//   [x] 0x249ea8  CKCurve_Evaluate_maybe
//
//   [ ] 0x9b9da0  CKCurve2DCpnt_IsKindOfClass  [inline]
//   [x] 0x9b9dc8  CKCurve2DCpnt_GetClassType  [inline]
//   [x] 0x9b9dd0  CKCurve2DCpnt_GetClassID  [inline]
#include "k2000/components/CKCurve2DCpnt.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/Vec3.h"
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

// 0x002499e8 CKCurve2DCpnt_Create, the inlined constructor (0x249620 CKCurve2DCpnt_Construct is a dead
// copy): the point list only.
CKCurve2DCpnt::CKCurve2DCpnt() {
    m_points.m_pBlock = nullptr;
    m_points.m_ui32NbElt = 20;
    m_points.m_ui32NbUsedElt = 0;
}

// 0x00249a98 CKCurve2DCpnt_Load
int32_t CKCurve2DCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk04);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    m_points.m_ui32NbElt = count;
    m_points.m_pBlock = static_cast<Point*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Point))));
    if (m_points.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = (count / 20) * 20 + 20;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Point));
        if (capacity == 0) {
            capacity = 20;
            bytes = 20 * static_cast<uint32_t>(sizeof(Point));
        }
        m_points.m_pBlock = static_cast<Point*>(Mem_ReallocAligned16(m_points.m_pBlock, bytes));
        m_points.m_ui32NbElt = capacity;
    }
    m_points.m_ui32NbUsedElt = count;
    ReadWordsLE(file, m_points.m_pBlock, count * 2);  // one read of count points (8 bytes each)
    return 1;
}

// 0x00249d30 CKCurve_EvaluateKeys_maybe (step 6)
float CKCurve2DCpnt::EvaluateKeys(float x, const Point* keys, int32_t count) {
    if (count <= 2) {
        if (count == 2) {
            const float x0 = keys[0].m_fX;
            const float t = (x - x0) / (keys[1].m_fX - x0);
            return ppc::fmadds(t, keys[1].m_fY, (1.0f - t) * keys[0].m_fY);  // TOC -0xec
        }
        if (count == 1) return keys[0].m_fY;
        return 0.0f;  // TOC -0xe8
    }
    for (int32_t i = 0; i < count - 1; ++i) {
        const Point& a = keys[i];
        const Point& b = keys[i + 1];
        if (!(a.m_fX <= x) || !(x <= b.m_fX)) continue;
        const float y1 = a.m_fY;
        const float y2 = b.m_fY;
        const float y0 = i == 0 ? y1 + (y1 - y2) : keys[i - 1].m_fY;
        const float y3 = i == count - 2 ? y2 + (y2 - y1) : keys[i + 2].m_fY;
        const float t = (x - a.m_fX) / (b.m_fX - a.m_fX);
        const float t2 = t * t;
        const float t3 = t * t2;
        const float twoT2 = t2 + t2;
        const float twoT3 = t3 + t3;
        const float fourT2 = twoT2 + twoT2;
        float w0 = twoT2 - t3;
        const float w3 = t3 - t2;
        float w1 = t3 + twoT3;
        const float fiveT2 = t2 + fourT2;
        w0 = w0 - t;
        const float u = twoT2 - w1;
        w1 = w1 - fiveT2;
        const float v = twoT2 + u;
        w1 = w1 + 2.0f;  // TOC -0x118
        const float w2 = t + v;
        float r = y1 * w1;
        r = ppc::fmadds(y0, w0, r);
        r = ppc::fmadds(y2, w2, r);
        r = ppc::fmadds(y3, w3, r);
        return r * 0.5f;  // TOC -0x114
    }
    return 0.0f;
}

// 0x00249ea8 CKCurve_Evaluate_maybe (step 6)
float CKCurve2DCpnt::Evaluate(float x) const {
    const Point* p = m_points.m_pBlock;
    const uint32_t n = m_points.m_ui32NbUsedElt;
    if (m_unk04 == 1) {
        const float last = n != 0 ? p[n - 1].m_fX : 0.0f;  // TOC -0xe8
        const float t = x / last;
        if (t < 1.0f) {  // TOC -0xec
            float out[2];
            Bezier2D_EvaluateDeCasteljau(static_cast<int32_t>(n), &p[0].m_fX, t, out);  // 0x00010eb0
            return out[1];
        }
        return p[n - 1].m_fY;  // BUG(original): an empty curve reads before its block
    }
    if (m_unk04 == 2) {
        float first = 0.0f;
        float last = 0.0f;
        if (n != 0) {
            first = p[0].m_fX;
            last = p[n - 1].m_fX;
        }
        float at = x;
        if (x <= first) {
            at = first;
        } else if (last <= x) {
            at = last;
        }
        return EvaluateKeys(at, p, static_cast<int32_t>(n));  // 0x00249d30
    }
    if (m_unk04 != 0) return 0.0f;
    if (n <= 1) return p[n - 1].m_fY;  // BUG(original): an empty curve reads before its block
    uint32_t i = 1;
    for (; i < n; ++i) {
        if (x <= p[i].m_fX) break;
    }
    if (i == n) return p[n - 1].m_fY;
    const Point& a = p[i - 1];
    const Point& b = p[i];
    const float t = (x - a.m_fX) / (b.m_fX - a.m_fX);
    return ppc::fmadds(t, b.m_fY, (1.0f - t) * a.m_fY);
}
