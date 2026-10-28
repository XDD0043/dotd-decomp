// CKCurve2DCpnt.h - a 2D curve given by its points (key 0x5ac6, vtable 0xb20ce8, size 0x14). Original
// unit: CKCurve2DCpnt.cpp (0x2495d0-0x24a0d0). No XXL2 class of this name; XXL2's CCurve2D keeps its
// points the same way (m_vv2TableOfPoint, a TVector of CVector2), _maybe the same container.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKCurve2DCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x16b)
    DOTD_DECLARE_FACTORIES(CKCurve2DCpnt)

    // One point (XXL2 CVector2: m_fX, m_fY; there is no shared CVector2 yet), both words byte-swapped.
    struct Point {
        float m_fX;
        float m_fY;
    };

    CKCurve2DCpnt();  // 0x002499e8 CKCurve2DCpnt_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00249a98 CKCurve2DCpnt_Load

    // 0x00249ea8 CKCurve_Evaluate_maybe (step 6: the hero's flight gravity): y at `x` by the kind +0x04: 0 the
    // polyline, 1 the Bezier curve of the points at x over the last point's x, 2 the Catmull-Rom keys (x clamped).
    float Evaluate(float x) const;
    // 0x00249d30 CKCurve_EvaluateKeys_maybe: the Catmull-Rom spline through `count` keys at `x` (the end tangents
    // mirrored; 0 outside), linear for two keys.
    static float EvaluateKeys(float x, const Point* keys, int32_t count);

    uint32_t m_unk04;              // +0x04 (0 or 2 in LVL000)
    TVector<Point, 20> m_points;   // +0x08 the constructor: null, 20, 0
};
DOTD_ASSERT_SIZE(CKCurve2DCpnt::Point, 0x8);
DOTD_ASSERT_SIZE(CKCurve2DCpnt, 0x14);
DOTD_ASSERT_OFFSET(CKCurve2DCpnt, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKCurve2DCpnt, m_points, 0x08);
