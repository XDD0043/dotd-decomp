// CollisionDatas.h - the data the collision meshes and CKSrvCollision exchange for lines, walls (ground edges) and
// sweeps. XXL2 names (K/KUL/CLine, K/KServices/KServiceCollision/KCollisionMesh/Datas/CLineCollisionDatas.h,
// CGroundEdgeDatas.h, ICollisionMesh.h); PS3 layouts (32-bit pointers), read from the code that fills them.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/CVector2.h"

class ICollisionMesh;

// XXL2 CLine: a start and a direction (the end is start + direction).
struct CLine {
    CVector3 m_start;    // +0x00
    CVector3 m_VectDir;  // +0x0c
};
DOTD_ASSERT_SIZE(CLine, 0x18);

// XXL2 CLine2D: the same in x / z.
struct CLine2D {
    CVector2 m_start;    // +0x00
    CVector2 m_VectDir;  // +0x08
};
DOTD_ASSERT_SIZE(CLine2D, 0x10);

// XXL2 CLineCollisionDatas (0x10 on the PS3): the first crossing found along a line. FindLineIntersection keeps the
// smaller time; the caller sets the starting time.
struct CLineCollisionDatas {
    float m_ftOnLine;                         // +0x00 the time on the line (0..1)
    const ICollisionMesh* m_pCollisionMesh;   // +0x04
    int32_t m_i32FaceIndex;                   // +0x08 (stored as the 16-bit face index)
    uint8_t m_ui8SectorNumber;                // +0x0c
    uint8_t m_pad0d[3];
};

// XXL2 SExtrapolated_Edge2D_Full_Infos (0x3c): a wall edge of a ground as the sweeps use it (CKSrvCollision
// +0x14, m_aPotentialEdge: up to 0xfe of them, filled by the grounds' FindAllPotentialEdgesForIntersection).
struct SExtrapolated_Edge2D_Full_Infos {
    CLine2D m_ExtrapolatedEdge2D;   // +0x00 the edge in x / z (start: the first vertex, moved out by the radius when
                                    // the edge was gathered for a sweep)
    CVector2 m_CircleCenterEnd;     // +0x10 the second vertex in x / z (sweeps only)
    CVector2 m_CircleCenterStart;   // +0x18 the first vertex in x / z (sweeps only)
    float m_YEnd;                   // +0x20 the second vertex's y
    float m_YStart;                 // +0x24 the first vertex's y
    float m_fHeightOfEnd;           // +0x28 the edge's height at the second vertex (an edge with height)
    float m_fHeightOfStart;         // +0x2c the edge's height at the first vertex
    CVector2 m_Normal;              // +0x30 (dz, -dx) normalised (sweeps only)
    uint8_t m_bEdgeWithHeight;      // +0x38
    uint8_t m_pad39[3];
};
DOTD_ASSERT_SIZE(SExtrapolated_Edge2D_Full_Infos, 0x3c);

// XXL2 CSlideGroundEdgeDatasOut (0x28 on the PS3): the result of a cylinder sweep against the wall edges.
struct CSlideGroundEdgeDatasOut {
    CVector3 m_v3BouncingVector;  // +0x00
    CVector3 m_v3Normal;          // +0x0c
    float m_fHeightAbove;         // +0x18
    float m_fHeightUnder;         // +0x1c
    float m_fYOfIntersection;     // +0x20
    uint8_t m_ba8Infos;           // +0x24 bit 0 edge with heights, bit 1 several edges, bit 2 data available
    uint8_t m_pad25[3];
};
DOTD_ASSERT_SIZE(CSlideGroundEdgeDatasOut, 0x28);

// XXL2 CGroundEdgeDatasOut (0x38): the best crossing of a line with the wall edges.
struct CGroundEdgeDatasOut {
    CLine m_Edge;              // +0x00
    CVector3 m_EdgeNormal;     // +0x18
    float m_ftLine;            // +0x24
    float m_ftEdge;            // +0x28
    float m_fHeightAbove;      // +0x2c
    float m_fHeightUnder;      // +0x30
    uint8_t m_ba8Infos;        // +0x34
    uint8_t m_pad35[3];
};
DOTD_ASSERT_SIZE(CGroundEdgeDatasOut, 0x38);

// XXL2 CMasksOfGrdTypeForTests: a ground is tested when its engine flags have a bit of the first mask and none of
// the second.
struct CMasksOfGrdTypeForTests {
    uint32_t m_ui32GrdToTest;   // +0x00
    uint32_t m_ui32GrdToAvoid;  // +0x04
};
DOTD_ASSERT_SIZE(CMasksOfGrdTypeForTests, 0x8);
