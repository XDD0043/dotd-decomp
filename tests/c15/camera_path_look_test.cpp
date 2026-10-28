// camera_path_look_test - step 6 AI: the paths' closest-distance / point-at-distance slots (CKLine 0xc7a30 /
// 0xc8050, CKSpline4L 0xc66a8) and the path modes of CKCameraConstraint_ComputeLookDirection_maybe 0x9a7d38 (zone
// mode 2 with a path, mode 3 with two CKFlaggedPaths incl. the +0x74 move of flag 0x40000) on small paths whose
// results follow by hand from the original's operations (the values are exact in float or checked to 1e-6).
// No game data is needed.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "k2000/cameras/CKCameraClassicTrack3.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/logic/CKLine.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/logic/math/CKSpline4L.h"

namespace {
int g_failures = 0;
#define CHECK(cond)                                                      \
    do {                                                                 \
        if (!(cond)) {                                                   \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            ++g_failures;                                                \
        }                                                                \
    } while (0)

bool Near(float a, double b) { return std::fabs(static_cast<double>(a) - b) <= 1e-6; }
bool NearV(const CVector3& v, double x, double y, double z) { return Near(v.x, x) && Near(v.y, y) && Near(v.z, z); }

// Paths built in memory (never freed: the test ends).
CKLine* MakeLine(const CVector3* points, const float* lengths, uint8_t segments, float total) {
    CKLine* line = new CKLine();
    line->m_ui8NumberOfSegment = segments;
    line->m_fTotalLenght = total;
    line->PointsList.m_pBlock = const_cast<CVector3*>(points);
    line->PointsList.m_ui32NbElt = line->PointsList.m_ui32NbUsedElt = segments + 1u;
    line->SegmentLenghtList.m_pBlock = const_cast<float*>(lengths);
    line->SegmentLenghtList.m_ui32NbElt = line->SegmentLenghtList.m_ui32NbUsedElt = segments;
    return line;
}

const CVector3 kLinePoints[3] = {{0.0f, 0.0f, 0.0f}, {10.0f, 0.0f, 0.0f}, {10.0f, 0.0f, 10.0f}};
const float kLineLengths[2] = {10.0f, 10.0f};
const CVector3 kLine2Points[2] = {{0.0f, 5.0f, 0.0f}, {0.0f, 5.0f, 10.0f}};
const float kLine2Lengths[1] = {10.0f};
const CVector3 kSamples[3] = {{0.0f, 0.0f, 0.0f}, {5.0f, 0.0f, 0.0f}, {10.0f, 0.0f, 0.0f}};

void TestLine() {
    CKLine* line = MakeLine(kLinePoints, kLineLengths, 2, 20.0f);
    const CVector3 p1 = {4.0f, 3.0f, 0.0f};
    // Segment 0: t = (10 * 4) / 100 = 0.4, the point (4, 0, 0) at squared distance 9 (segment 1: t 0, 45): 0.4 * 10.
    CHECK(line->GetClosestDistanceAlong(&p1, 1) == 4.0f);
    CHECK(line->GetClosestDistanceAlong(&p1, 0) == 4.0f);  // |d| sums 3 against 9
    const CVector3 p2 = {12.0f, 0.0f, 6.0f};
    // Segment 0: t 1.2 cut to 1, (10, 0, 0) at 40; segment 1: t = (10 * 6) / 100 = 0.6, (10, 0, 6) at 4: 0.6 * 10 + 10.
    CHECK(line->GetClosestDistanceAlong(&p2, 1) == 16.0f);
    CVector3 point;
    CVector3 direction;
    line->GetPointAtDistance(16.0f, &point, &direction);  // cumulated 10 then 20: segment 1, t = (16 - 10) / 10
    CHECK(NearV(point, 10.0, 0.0, 6.0));
    CHECK(direction.x == 0.0f && direction.y == 0.0f && direction.z == 1.0f);
    line->GetPointAtDistance(25.0f, &point, nullptr);  // cut to the length 20: the last point
    CHECK(point.x == 10.0f && point.y == 0.0f && point.z == 10.0f);
    line->GetPointAtDistance(4.0f, &point, &direction);  // segment 0
    CHECK(NearV(point, 4.0, 0.0, 0.0));
    CHECK(direction.x == 1.0f && direction.y == 0.0f && direction.z == 0.0f);
    CHECK(line->GetLength() == 20.0f);
}

void TestSpline() {
    CKSpline4L* spline = new CKSpline4L();
    spline->m_fTotalLenght = 10.0f;
    spline->SamplePointsList.m_pBlock = const_cast<CVector3*>(kSamples);
    spline->SamplePointsList.m_ui32NbElt = spline->SamplePointsList.m_ui32NbUsedElt = 3;
    const CVector3 a = {6.0f, 1.0f, 0.0f};  // nearest sample 1; towards sample 2: 5 * (1 + 5 / 25)
    CHECK(Near(spline->GetClosestDistanceAlong(&a, 1), 6.0));
    CHECK(Near(spline->GetClosestDistanceAlong(&a, 0), 6.0));
    const CVector3 b = {-2.0f, 0.0f, 0.0f};  // nearest sample 0, behind it, the last sample not as near: 0
    CHECK(spline->GetClosestDistanceAlong(&b, 1) == 0.0f);
    const CVector3 c = {11.0f, 0.0f, 0.0f};  // nearest the last sample, past it: the length
    CHECK(spline->GetClosestDistanceAlong(&c, 1) == 10.0f);
    const CVector3 d = {9.0f, 0.0f, 0.0f};  // the last sample, before it: 5 * (2 - 5 / 25)
    CHECK(Near(spline->GetClosestDistanceAlong(&d, 1), 9.0));
    const CVector3 e = {4.0f, 0.0f, 0.0f};  // sample 1, towards sample 0: 5 * (1 - 5 / 25)
    CHECK(Near(spline->GetClosestDistanceAlong(&e, 1), 4.0));
}

void TestLookDirection() {
    CKLine* line = MakeLine(kLinePoints, kLineLengths, 2, 20.0f);
    CKLine* line2 = MakeLine(kLine2Points, kLine2Lengths, 1, 10.0f);
    static float s_beacons1[2] = {0.0f, 20.0f};
    static float s_beacons2[2] = {0.0f, 10.0f};
    CKFlaggedPath* first = new CKFlaggedPath();
    first->m_pPath = line;
    first->m_ui32NbOfBeacon = 2;
    first->m_aBeaconList = s_beacons1;
    CKFlaggedPath* second = new CKFlaggedPath();
    second->m_pPath = line2;
    second->m_ui32NbOfBeacon = 2;
    second->m_aBeaconList = s_beacons2;
    CKCameraConstraint* zone = new CKCameraConstraint();
    zone->m_unk1c = 0;
    zone->m_unk20 = IKCamera::AsFloat(0);
    zone->m_unk38 = 3;
    zone->m_unk3c = first;
    zone->m_unk40 = second;
    zone->m_afUnk44[0] = 0.0f;
    zone->m_unk74 = IKCamera::AsWord(2.0f);
    const CVector3 point = {12.0f, 1.0f, 6.0f};
    // Mode 3: the distance on the first path 16 (segment 1, (10, 0, 6) at squared distance 5), the interval [0, 20]
    // mapped on [0, 10]: 8, the second path's point (0, 5, 8). Look mode 0: (0, 5, 8) - point = (-12, 4, 2), normalised.
    CVector3 v = CKCameraClassicTrack3::ComputeLookDirection(zone, &point);
    const double n0 = std::sqrt(164.0);
    CHECK(NearV(v, -12.0 / n0, 4.0 / n0, 2.0 / n0));
    zone->m_unk20 = IKCamera::AsFloat(0x400u);  // negated before the normalisation
    v = CKCameraClassicTrack3::ComputeLookDirection(zone, &point);
    CHECK(NearV(v, 12.0 / n0, -4.0 / n0, -2.0 / n0));
    // Look mode 1 (+0x1c bits 5-6): from the second path's point to the first's: (10, 0, 6) - (0, 5, 8); flag 0x400
    // does not apply there. Flag 0x40000: +0x74 += the first path's y 0 - the point's y 1.
    zone->m_unk1c = 0x20;
    zone->m_unk20 = IKCamera::AsFloat(0x40400u);
    v = CKCameraClassicTrack3::ComputeLookDirection(zone, &point);
    const double n1 = std::sqrt(129.0);
    CHECK(NearV(v, 10.0 / n1, -5.0 / n1, -2.0 / n1));
    CHECK(IKCamera::AsFloat(zone->m_unk74) == 1.0f);
    // Mode 2 with the path itself at +0x3c. Look mode 0: (10, 0, 6) - point = (-2, -1, 0), normalised.
    zone->m_unk38 = 2;
    zone->m_unk3c = line;
    zone->m_unk40 = nullptr;
    zone->m_unk1c = 0;
    zone->m_unk20 = IKCamera::AsFloat(0);
    v = CKCameraClassicTrack3::ComputeLookDirection(zone, &point);
    const double n2 = std::sqrt(5.0);
    CHECK(NearV(v, -2.0 / n2, -1.0 / n2, 0.0));
    // Look mode 1, angle 0: the path's direction there (0, 0, 1) turned by 0: (c x - s z, -y, s x + c z); the game's
    // inline cosine of 0 is its polynomial's constant 0.99999994.
    zone->m_unk1c = 0x20;
    v = CKCameraClassicTrack3::ComputeLookDirection(zone, &point);
    CHECK(v.x == 0.0f && v.y == 0.0f && v.z == 0.99999994f);
    // Mode 3 without its second path: the z axis.
    zone->m_unk38 = 3;
    zone->m_unk3c = first;
    v = CKCameraClassicTrack3::ComputeLookDirection(zone, &point);
    CHECK(v.x == 0.0f && v.y == 0.0f && v.z == 1.0f);
}

}  // namespace

int main() {
    TestLine();
    TestSpline();
    TestLookDirection();
    if (g_failures != 0) {
        std::printf("camera_path_look_test: %d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("camera_path_look_test: OK\n");
    return 0;
}
