// wall_sweep_test - step 3: the wall code on a hand-made ground (no game data, no level): the 2D segment and
// circle tests, the segment-box test, a ground's raycast (FindLineIntersection) and edge gathering (both forms), and the
// service's sweeps over an edge list given directly (gather off): the cylinder pushed out of a wall it stands in, stopped
// in front of a wall it walks into, sliding along a wall it walks into at an angle, and free when it walks away.
#include <cmath>
#include <cstdio>

#include "k2000/logic/physics/CGround.h"
#include "k2000/math/CBBox.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"

namespace {
int g_failures = 0;
void Expect(bool ok, const char* what) {
    if (!ok) {
        std::printf("wall_sweep: FAIL %s\n", what);
        ++g_failures;
    }
}
bool Near(float a, float b, float e = 1e-5f) { return std::fabs(a - b) <= e; }

CLine MakeLine(float sx, float sy, float sz, float dx, float dy, float dz) {
    CLine line;
    line.m_start = {sx, sy, sz};
    line.m_VectDir = {dx, dy, dz};
    return line;
}
}  // namespace

int main() {
    GameEngineContext engine;  // g_pEngine (the service's constructor registers itself there)

    {  // CLine2D crossings
        CLine2D a = {{0.0f, 0.0f}, {2.0f, 0.0f}};
        CLine2D b = {{1.0f, -1.0f}, {0.0f, 2.0f}};
        float ta = -1.0f, tb = -1.0f;
        Expect(Seg2D_IntersectSegment(&a, &b, &ta, &tb) == 1 && Near(ta, 0.5f) && Near(tb, 0.5f), "segments cross at 0.5 / 0.5");
        CLine2D c = {{0.0f, 1.0f}, {2.0f, 0.0f}};
        Expect(Seg2D_IntersectSegment(&a, &c, &ta, &tb) == 0, "parallel segments do not cross");
        const CVector2 center = {1.0f, 0.0f};
        float t0 = -1.0f, t1 = -1.0f;
        Expect(Seg2D_IntersectCircle(0.5f, &a, &center, &t0, &t1) == 2 && Near(t0, 0.25f) && Near(t1, 0.75f),
               "a segment through a circle: two times, smaller first");
        const CVector2 far = {1.0f, 3.0f};
        Expect(Seg2D_IntersectCircle(0.5f, &a, &far, &t0, &t1) == 0, "a circle off the segment: none");
    }
    {  // the segment-box test
        CBBox box = {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}};
        const CLine through = MakeLine(-1.0f, 0.5f, 0.5f, 3.0f, 0.0f, 0.0f);
        const CLine above = MakeLine(-1.0f, 2.0f, 0.5f, 3.0f, 0.0f, 0.0f);
        const CLine diagonal = MakeLine(-1.0f, 0.5f, 1.2f, 1.5f, 0.0f, 1.5f);  // its bounds overlap, the segment misses
        Expect(AABB_OverlapsSegmentBounds(&box, &through) == 1, "a segment through the box");
        Expect(AABB_OverlapsSegmentBounds(&box, &above) == 0, "a segment above the box");
        Expect(AABB_OverlapsSegmentBounds(&box, &diagonal) == 0, "a diagonal segment past the box's corner");
    }

    // A unit square ground at y = 0 (two faces) with one wall edge along x at z = 0 (from (0,0,0) to (1,0,0)) and one wall
    // with heights along z at x = 1.
    CVector3 vertices[4] = {{0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
    ICollisionMesh::CCollisionTriangle faces[2] = {{{0, 2, 1}}, {{0, 3, 2}}};
    CGround::SCollisionMeshEdge edge = {{0, 1}};
    CGround::SCollisionMeshEdgeWithHeight wall = {{1, 2}, {2.0f, 2.0f}};
    CGround ground;
    ground.m_aVertex = vertices;
    ground.m_aTriangle = faces;
    ground.m_ui16NbVertex = 4;
    ground.m_ui16NbTriangle = 2;
    ground.m_aEdge = &edge;
    ground.m_ui16NbEdge = 1;
    ground.m_aEdgeWithHeight = &wall;
    ground.m_ui16NbEdgeWithHeight = 1;
    ground.m_ba16EngineFlags = 1;
    const float box[6] = {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    for (int i = 0; i < 6; ++i) ground.m_AABB[i] = box[i];

    {  // FindLineIntersection: a vertical line through the square
        const CLine down = MakeLine(0.25f, 1.0f, 0.75f, 0.0f, -2.0f, 0.0f);
        CLineCollisionDatas hit;
        hit.m_ftOnLine = 3.0e38f;
        hit.m_pCollisionMesh = nullptr;
        hit.m_i32FaceIndex = -1;
        const uint8_t found = ground.FindLineIntersection(&down, &hit, 0);
        Expect(found == 1 && Near(hit.m_ftOnLine, 0.5f) && hit.m_pCollisionMesh == &ground, "the line meets the ground at t 0.5");
        const CLine outside = MakeLine(2.0f, 1.0f, 0.5f, 0.0f, -2.0f, 0.0f);
        hit.m_ftOnLine = 3.0e38f;
        Expect(ground.FindLineIntersection(&outside, &hit, 0) == 0, "a line beside the ground misses");
    }

    SExtrapolated_Edge2D_Full_Infos edges[8];
    uint8_t count = 0;
    {  // the gathering, both forms
        const CLine walk = MakeLine(0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 2.0f);
        CBBox query = {{1.5f, 1.0f, 1.5f}, {-0.5f, -0.5f, -1.5f}};
        ground.FindAllPotentialEdgesForIntersection(edges, &count, &walk, &query, 0);
        Expect(count == 2 && edges[0].m_bEdgeWithHeight == 0 && edges[1].m_bEdgeWithHeight == 1,
               "both edges gathered (the wall without heights first)");
        Expect(Near(edges[1].m_fHeightOfStart, 2.0f) && Near(edges[1].m_fHeightOfEnd, 2.0f), "the wall's heights");
        count = 0;
        ground.FindAllPotentialEdgesForIntersection(edges, &count, &walk, &query, 0.25f, 0);
        Expect(count == 2, "both edges gathered for a sweep");
        Expect(Near(edges[0].m_Normal.m_fX, 0.0f) && Near(edges[0].m_Normal.m_fY, -1.0f), "the first edge's normal (dz, -dx)");
        Expect(Near(edges[0].m_ExtrapolatedEdge2D.m_start.m_fY, -0.25f) && Near(edges[0].m_CircleCenterStart.m_fY, 0.0f),
               "the sweep form moves the edge out by the radius");
    }

    CKSrvCollision service;
    service.m_aPotentialEdge = edges;
    service.m_ui8NbPotentialBoundEdge = 1;  // only the edge along x
    const float radius = 0.25f, height = 1.0f;
    {  // standing in the wall: pushed out along its normal
        const CVector3 point = {0.5f, 0.0f, -0.1f};
        CSlideGroundEdgeDatasOut out = {};
        Expect(service.SweepCircleAgainstWallSegments(&point, radius, height, &out) == 1, "the cylinder in the wall is inside");
        Expect(Near(out.m_v3BouncingVector.z, -(0.15f + 0.002f), 1e-4f) && (out.m_ba8Infos & 4) != 0,
               "pushed back out by the overlap + 0.002");
    }
    {  // walking straight into the wall: the move stops 0.002 short of it
        const CLine walk = MakeLine(0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
        CSlideGroundEdgeDatasOut out = {};
        const uint8_t result = service.ResolveSweptCylinderWalls(&walk, radius, height, &out, nullptr, nullptr, 0);
        const float endZ = walk.m_start.z + walk.m_VectDir.z + out.m_v3BouncingVector.z;
        Expect(result == 2 && Near(endZ, -radius - 0.002f, 1e-4f), "walking into the wall stops in front of it");
    }
    {  // at an angle: it slides along x
        const CLine walk = MakeLine(0.2f, 0.0f, -1.0f, 0.4f, 0.0f, 1.0f);
        CSlideGroundEdgeDatasOut out = {};
        const uint8_t result = service.ResolveSweptCylinderWalls(&walk, radius, height, &out, nullptr, nullptr, 0);
        const float endX = walk.m_start.x + walk.m_VectDir.x + out.m_v3BouncingVector.x;
        const float endZ = walk.m_start.z + walk.m_VectDir.z + out.m_v3BouncingVector.z;
        Expect(result == 2 && Near(endZ, -radius - 0.002f, 1e-3f) && Near(endX, 0.6f, 1e-3f), "an angled walk slides along the wall");
    }
    {  // walking away: free
        const CLine walk = MakeLine(0.5f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f);
        CSlideGroundEdgeDatasOut out = {};
        Expect(service.ResolveSweptCylinderWalls(&walk, radius, height, &out, nullptr, nullptr, 0) == 0, "walking away is free");
    }
    {  // the line form against the wall without a radius
        const CLine walk = MakeLine(0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 2.0f);
        CGroundEdgeDatasOut out = {};
        count = 0;
        CBBox query = {{1.5f, 1.0f, 1.5f}, {-0.5f, -0.5f, -1.5f}};
        ground.FindAllPotentialEdgesForIntersection(edges, &count, &walk, &query, 0);
        service.m_ui8NbPotentialBoundEdge = count;
        Expect(service.RaycastWalls(&walk, height, &out, 0, nullptr, 0) == 1 && Near(out.m_ftLine, 0.5f) &&
                   Near(out.m_EdgeNormal.z, -1.0f),
               "the line meets the wall at t 0.5, normal -z");
    }
    std::printf("wall_sweep: %s\n", g_failures == 0 ? "OK" : "FAILED");
    return g_failures == 0 ? 0 : 1;
}
