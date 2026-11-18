// CGround.cpp - reconstructed original translation unit 0x1a3e90-0x1a5d60 (GAME_TOC1, main_toc1), 22 functions, 21 live.
// Primary class: CGround  key 0x48c  category Logic  size 0x50  vtable 0xb1c1a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a3e90  CGround_Delete
//   [x] 0x1a3ee0  CGround_RecursiveRegistration
//   [x] 0x1a3f48  CGround_vf50
//   [x] 0x1a3f50  CGround_vf54
//   [x] 0x1a3f58  CGround_RefreshTransform_maybe
//   [ ] 0x1a3f60  FUN_001a3f60  [dead]
//   [ ] 0x1a3f78  RegisterCGroundClass
//   [ ] 0x1a3ff0  _GLOBAL__I_1a3ff0
//   [x] 0x1a4000  CGround_vf60
//   [x] 0x1a4060  CGround_DeleteArray
//   [x] 0x1a4108  CGround_Create
//   [x] 0x1a4140  CGround_vf6C
//   [x] 0x1a4620  CGround_FindFloorAtPoint_maybe
//   [x] 0x1a4868  CGround_GetTriangleNormalAtPoint_maybe
//   [x] 0x1a4c20  CGround_CreateArray
//   [x] 0x1a4cb8  CGround_RaycastTriangles_maybe
//   [x] 0x1a4fb0  CGround_GetInfo  (IKSerializable's: returns 1)
//   [x] 0x1a4fb8  CGround_MessageProc
//   [x] 0x1a5078  CGround_PostLoad  (IKSerializable's: returns 1)
//   [x] 0x1a5080  CGround_vf70
//   [x] 0x1a5610  CGround_Load
//   [ ] 0x1a5998  CGround_Save
//
//   [ ] 0x9aad28  CGround_GetClassType  [inline]
//   [ ] 0x9aad30  CGround_GetClassID  [inline]
//   [ ] 0x9aad38  CGround_IsKindOfClass  [inline]
//   [ ] 0x9aad60  CGround_DeletingDestructor  [inline]
//   [ ] 0x9aada8  CGround_Destructor  [inline]
#include "k2000/logic/physics/CGround.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/math/CBBox.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CollisionDatas.h"

// 0x001a5610 CGround_Load
int32_t CGround::Load(IKFile* file, int32_t type) {
    uint32_t size = 0;
    ReadU32LE(file, &size);
    m_aVertex = static_cast<CVector3*>(Mem_AllocAligned16(size));
    ICollisionMesh::Load(file, type);
    uint8_t* const afterTriangles =
        reinterpret_cast<uint8_t*>(m_aTriangle) + ((m_ui16NbTriangle * 6u + 3u) & 0xfffffffcu);
    ReadU16LE(file, &m_ui16NbEdge);
    if (m_ui16NbEdge == 0) {
        m_aEdge = nullptr;
    } else {
        m_aEdge = reinterpret_cast<SCollisionMeshEdge*>(afterTriangles);
        uint16_t* half = m_aEdge->m_aui16Index;
        file->Read(half, m_ui16NbEdge * 4u);  // one read, then each u16 swapped
        for (uint32_t i = 0; i < m_ui16NbEdge * 2u; ++i) {
            const uint8_t* b = reinterpret_cast<const uint8_t*>(half + i);
            half[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));
        }
    }
    ReadU16LE(file, &m_ui16NbEdgeWithHeight);
    if (m_ui16NbEdgeWithHeight == 0) {
        m_aEdgeWithHeight = nullptr;
    } else {
        if (m_aEdge != nullptr) {
            m_aEdgeWithHeight = reinterpret_cast<SCollisionMeshEdgeWithHeight*>(m_aEdge + m_ui16NbEdge);
        } else {
            m_aEdgeWithHeight = reinterpret_cast<SCollisionMeshEdgeWithHeight*>(afterTriangles);
        }
        uint32_t i = 0;
        do {
            SCollisionMeshEdgeWithHeight* edge = &m_aEdgeWithHeight[i];
            ++i;
            uint16_t halves[2];
            file->Read(halves, 4);  // one 4-byte read, each u16 swapped
            for (uint16_t& h : halves) {
                const uint8_t* b = reinterpret_cast<const uint8_t*>(&h);
                h = static_cast<uint16_t>(b[0] | (b[1] << 8));
            }
            edge->m_aui16Index[0] = halves[0];
            edge->m_aui16Index[1] = halves[1];
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(edge->m_afValue), 2);
        } while (i < m_ui16NbEdgeWithHeight);
    }
    ReadF32LE(file, &m_fHeightOffsetForNegativeEdges);
    ReadF32LE(file, &m_fPropertieValue);
    return 1;
}

namespace ground_test {

bool InsideEdge(const CVector3& a, const CVector3& b, float px, float pz) {
    const float r = (b.z - a.z) * (px - a.x);
    return ppc::fmsubs(b.x - a.x, pz - a.z, r) <= 0.0f;
}

CVector3 FaceNormal(const CVector3& v0, const CVector3& v1, const CVector3& v2) {
    const float ax = v1.x - v0.x, ay = v1.y - v0.y, az = v1.z - v0.z;
    const float bx = v2.x - v0.x, by = v2.y - v0.y, bz = v2.z - v0.z;
    CVector3 n;
    n.y = ppc::fmsubs(az, bx, ax * bz);
    n.x = ppc::fmsubs(ay, bz, az * by);
    n.z = ppc::fmsubs(ax, by, ay * bx);
    float sum = n.y * n.y;
    sum = ppc::fmadds(n.x, n.x, sum);
    sum = ppc::fmadds(n.z, n.z, sum);
    const float length = std::sqrt(sum);  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        n.z = n.z * inverse;
        n.x = n.x * inverse;
        n.y = n.y * inverse;
    }
    return n;
}

float HeightOnPlane(const CVector3& v2, const CVector3& normal, float px, float py, float pz) {
    if (normal.y == 0.0f) return py;
    float t = (pz - v2.z) * normal.z;
    t = ppc::fmadds(px - v2.x, normal.x, t);
    t = t / normal.y;
    return v2.y - t;
}

}  // namespace ground_test

// 0x001a4620 CGround_FindFloorAtPoint_maybe (XXL2 GetGroundContactOnFace). The face must exist (the caller only asks
// for the contact's own ground).
uint8_t CGround::GetGroundContactOnFace(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                        const CVector3* point) const {
    const uint16_t* face = GroundContact_GetTriangle(inOut);
    const CVector3& v0 = m_aVertex[face[0]];
    const CVector3& v1 = m_aVertex[face[1]];
    const float px = point->x, pz = point->z;
    if (!ground_test::InsideEdge(v0, v1, px, pz)) return 0;
    const CVector3& v2 = m_aVertex[face[2]];
    if (!ground_test::InsideEdge(v1, v2, px, pz)) return 0;
    if (!ground_test::InsideEdge(v2, v0, px, pz)) return 0;
    const float height = ground_test::HeightOnPlane(v2, inOut->m_Normal, px, point->y, pz);
    const float dh = height - point->y;
    uint32_t status;
    if (dh <= 0.0f) {
        inOut->m_fdH = -dh;
        status = 0;
    } else if (in->m_fDeltaMax >= dh) {
        inOut->m_fdH = dh;
        status = 1;
    } else if (in->m_fObjectHeight >= dh) {
        inOut->m_fdH = dh;
        status = 2;
    } else {
        return 0;
    }
    inOut->m_ProjectionOnGround.x = px;
    inOut->m_ProjectionOnGround.z = pz;
    inOut->m_ProjectionOnGround.y = height + 0.001f;
    inOut->m_eContactStatus = status;
    return 1;
}

// 0x001a4868 CGround_GetTriangleNormalAtPoint_maybe (XXL2 GetGroundContact). The faces in order; the first that holds
// the point in x / z answers: within m_fDeltaMax above the point (or under it) the statuses 1 / 0, within
// m_fObjectHeight the status 2; higher than that, no contact (the later faces are not tried).
uint8_t CGround::GetGroundContact(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                  const CVector3* point) const {
    const float px = point->x, pz = point->z;
    for (uint32_t i = 0; i < m_ui16NbTriangle; ++i) {
        const uint16_t* face = m_aTriangle[i].m_aui16Index;
        const CVector3& v0 = m_aVertex[face[0]];
        const CVector3& v1 = m_aVertex[face[1]];
        if (!ground_test::InsideEdge(v0, v1, px, pz)) continue;
        const CVector3& v2 = m_aVertex[face[2]];
        if (!ground_test::InsideEdge(v1, v2, px, pz)) continue;
        if (!ground_test::InsideEdge(v2, v0, px, pz)) continue;
        const CVector3 normal = ground_test::FaceNormal(v0, v1, v2);
        const float height = ground_test::HeightOnPlane(v2, normal, px, point->y, pz);
        const float dh = height - point->y;
        uint32_t status;
        float stored;
        if (!(in->m_fDeltaMax < dh)) {
            stored = dh <= 0.0f ? -dh : dh;
            status = dh <= 0.0f ? 0u : 1u;
        } else if (in->m_fObjectHeight >= dh) {
            stored = dh;
            status = 2;
        } else {
            return 0;
        }
        inOut->m_pGround = const_cast<CGround*>(this);
        inOut->m_i32FaceIndex = static_cast<int32_t>(i & 0xffffu);
        inOut->m_ProjectionOnGround.x = px;
        inOut->m_Normal = normal;
        inOut->m_ProjectionOnGround.z = pz;
        inOut->m_ProjectionOnGround.y = height + 0.001f;
        inOut->m_eContactStatus = status;
        inOut->m_fdH = stored;
        return 1;
    }
    return 0;
}

namespace ground_test {

bool RaycastFaces(const ICollisionMesh& mesh, const CLine& line, CLineCollisionDatas* out, uint8_t backFaces,
                  bool dynamicForm) {
    constexpr float kEpsilon = 9.99999975e-06f;          // 0x3727c5ac
    constexpr float kLow = -9.99999975e-06f;             // 0xb727c5ac
    constexpr float kHigh = 1.00001001f;                 // 0x3f800054
    constexpr double kHighDouble = 1.0000099999997474;   // CGround's lfd (TOC -0x26b8)
    const float dx = line.m_VectDir.x, dy = line.m_VectDir.y, dz = line.m_VectDir.z;
    bool found = false;
    for (uint32_t i = 0; i < mesh.m_ui16NbTriangle; ++i) {
        const uint16_t* face = mesh.m_aTriangle[i].m_aui16Index;
        const CVector3& v0 = mesh.m_aVertex[face[0]];
        const CVector3& v1 = mesh.m_aVertex[face[1]];
        const CVector3& v2 = mesh.m_aVertex[face[2]];
        const float e2z = v2.z - v0.z, e2x = v2.x - v0.x, e2y = v2.y - v0.y;
        const float e1y = v1.y - v0.y, e1z = v1.z - v0.z, e1x = v1.x - v0.x;
        const float py = ppc::fmsubs(e2x, dz, e2z * dx);
        const float px = ppc::fmsubs(e2z, dy, e2y * dz);
        const float pz = ppc::fmsubs(e2y, dx, e2x * dy);
        const float det = ppc::fmadds(e1z, pz, ppc::fmadds(e1x, px, e1y * py));
        if (!(det >= kEpsilon)) {
            if (backFaces != 0) continue;
            if (det > kLow) continue;
        }
        const float ty = line.m_start.y - v0.y;
        const float tz = line.m_start.z - v0.z;
        const float tx = line.m_start.x - v0.x;
        const float inverse = 1.0f / det;
        const float u = inverse * ppc::fmadds(pz, tz, ppc::fmadds(px, tx, py * ty));
        if (u < kLow) continue;
        if (dynamicForm ? u > kHigh : static_cast<double>(u) > kHighDouble) continue;
        const float qy = ppc::fmsubs(e1x, tz, e1z * tx);
        const float qx = ppc::fmsubs(e1z, ty, e1y * tz);
        const float qz = ppc::fmsubs(e1y, tx, e1x * ty);
        const float v = inverse * ppc::fmadds(dz, qz, ppc::fmadds(dx, qx, dy * qy));
        if (v < kLow) continue;
        if (u + v > kHigh) continue;
        const float t = inverse * ppc::fmadds(e2z, qz, ppc::fmadds(e2x, qx, e2y * qy));
        if (!(t > kLow)) continue;
        if (t >= kHigh) continue;
        if (dynamicForm ? out->m_ftOnLine <= t : !(out->m_ftOnLine > t)) continue;
        out->m_ftOnLine = t;
        out->m_i32FaceIndex = static_cast<int32_t>(i & 0xffffu);
        found = true;
    }
    return found;
}

void GatherEdges(const CGround& ground, const CMatrix34* world, SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                 const CLine* line, const CBBox* box, bool withRadius, float radius, uint8_t cull) {
    // The box: x / z grown by 0.1 for the sweep form (TOC -0x26ac in CGround, -0x2734 in CDynamicGround).
    constexpr float kMargin = 0.100000001f;
    const float infX = withRadius ? box->m_inf.x - kMargin : box->m_inf.x;
    const float supX = withRadius ? box->m_sup.x + kMargin : box->m_sup.x;
    const float infZ = withRadius ? box->m_inf.z - kMargin : box->m_inf.z;
    const float supZ = withRadius ? box->m_sup.z + kMargin : box->m_sup.z;
    const float supY = box->m_sup.y;
    const float infY = box->m_inf.y;
    uint32_t n = *count;
    SExtrapolated_Edge2D_Full_Infos* edge = edges + n;
    auto points = [&](uint16_t i0, uint16_t i1, CVector3* p) {
        p[0] = ground.m_aVertex[i0];
        p[1] = ground.m_aVertex[i1];
        if (world != nullptr) Mat4_TransformPoints(world, p, p, 2);
    };
    // x and z: the edge's extent against the box (max < inf or min > sup: out; the second vertex is the minimum only
    // when it is strictly smaller).
    auto overlapsXZ = [&](const CVector3& p0, const CVector3& p1) {
        const bool xSwap = p1.x < p0.x;
        const float maxX = xSwap ? p0.x : p1.x, minX = xSwap ? p1.x : p0.x;
        if (maxX < infX || minX > supX) return false;
        const bool zSwap = p1.z < p0.z;
        const float maxZ = zSwap ? p0.z : p1.z, minZ = zSwap ? p1.z : p0.z;
        if (maxZ < infZ || minZ > supZ) return false;
        return true;
    };
    // The facing test: the edge's normal (dz, -dx) against the line's direction, fmsubs(dz, dir.x, dx * dir.z) <= 0
    // keeps it (a NaN too). CDynamicGround's sweep form computes it as fmadds(dz, dir.x, -dx * dir.z): the same value.
    auto facing = [&](float dx, float dz) {
        return !(ppc::fmsubs(dz, line->m_VectDir.x, dx * line->m_VectDir.z) > 0.0f);
    };
    auto store = [&](const CVector3& p0, const CVector3& p1, float dx, float dz, uint8_t withHeight) {
        if (withRadius) {
            edge->m_CircleCenterEnd.m_fX = p1.x;
            edge->m_CircleCenterEnd.m_fY = p1.z;
            edge->m_CircleCenterStart.m_fX = p0.x;
            edge->m_CircleCenterStart.m_fY = p0.z;
            float nx = dz, ny = -dx;
            const float length = std::sqrt(ppc::fmadds(nx, nx, ny * ny));  // Math_Sqrtf
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                ny = inverse * ny;
                nx = inverse * nx;
            }
            edge->m_Normal.m_fX = nx;
            edge->m_Normal.m_fY = ny;
        }
        edge->m_ExtrapolatedEdge2D.m_VectDir.m_fY = dz;
        edge->m_ExtrapolatedEdge2D.m_VectDir.m_fX = dx;
        edge->m_YEnd = p1.y;
        edge->m_ExtrapolatedEdge2D.m_start.m_fX = p0.x;
        edge->m_ExtrapolatedEdge2D.m_start.m_fY = p0.z;
        edge->m_YStart = p0.y;
        edge->m_bEdgeWithHeight = withHeight;
        if (withRadius) {
            edge->m_ExtrapolatedEdge2D.m_start.m_fY = ppc::fmadds(radius, edge->m_Normal.m_fY, p0.z);
            edge->m_ExtrapolatedEdge2D.m_start.m_fX = ppc::fmadds(radius, edge->m_Normal.m_fX, p0.x);
        }
        ++edge;
        ++n;
    };
    // The edges without height: the lower vertex not above the box.
    for (uint32_t i = 0; i < ground.m_ui16NbEdge; ++i) {
        CVector3 p[2];
        points(ground.m_aEdge[i].m_aui16Index[0], ground.m_aEdge[i].m_aui16Index[1], p);
        if (!overlapsXZ(p[0], p[1])) continue;
        const float minY = p[1].y > p[0].y ? p[0].y : p[1].y;
        if (minY > supY) continue;
        if ((n & 0xff) > 0xfd) {
            *count = static_cast<uint8_t>(n);
            return;
        }
        const float dx = p[1].x - p[0].x;
        const float dz = p[1].z - p[0].z;
        if (cull != 0 && !facing(dx, dz)) continue;
        store(p[0], p[1], dx, dz, 0);
    }
    // The edges with height: the vertical span of the wall (each vertex's y and y + its height) against the box.
    for (uint32_t i = 0; i < ground.m_ui16NbEdgeWithHeight; ++i) {
        const CGround::SCollisionMeshEdgeWithHeight& wall = ground.m_aEdgeWithHeight[i];
        CVector3 p[2];
        points(wall.m_aui16Index[0], wall.m_aui16Index[1], p);
        if (!overlapsXZ(p[0], p[1])) continue;
        float top1, bottom1, top0, bottom0;
        if (wall.m_afValue[1] <= 0.0f) {
            top1 = p[1].y;
            bottom1 = wall.m_afValue[1] + p[1].y;
        } else {
            bottom1 = p[1].y;
            top1 = wall.m_afValue[1] + p[1].y;
        }
        if (wall.m_afValue[0] <= 0.0f) {
            top0 = p[0].y;
            bottom0 = wall.m_afValue[0] + p[0].y;
        } else {
            bottom0 = p[0].y;
            top0 = wall.m_afValue[0] + p[0].y;
        }
        const float top = top1 > top0 ? top1 : top0;
        if (top < infY) continue;
        const float bottom = bottom1 > bottom0 ? bottom0 : bottom1;
        if (bottom > supY) continue;
        if ((n & 0xff) > 0xfd) {
            *count = static_cast<uint8_t>(n);
            return;
        }
        const float dx = p[1].x - p[0].x;
        const float dz = p[1].z - p[0].z;
        if (cull != 0 && !facing(dx, dz)) continue;
        edge->m_fHeightOfEnd = wall.m_afValue[1];
        edge->m_fHeightOfStart = wall.m_afValue[0];
        store(p[0], p[1], dx, dz, 1);
    }
    *count = static_cast<uint8_t>(n);
}

}  // namespace ground_test

// 0x001a4cb8 CGround_RaycastTriangles_maybe (XXL2 FindLineIntersection): the line's segment against the box, then the
// faces; a kept face makes this the mesh of `out`.
uint8_t CGround::FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const {
    if (!AABB_OverlapsSegmentBounds(reinterpret_cast<const CBBox*>(m_AABB), line)) return 0;
    if (!ground_test::RaycastFaces(*this, *line, out, backFaces, false)) return 0;
    out->m_pCollisionMesh = this;
    return 1;
}

// 0x001a4140 CGround_vf6C (XXL2 FindAllPotentialEdgesForIntersection(edges, count, line, box, cull))
void CGround::FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                                   const CLine* line, const CBBox* box, uint8_t cull) {
    ground_test::GatherEdges(*this, nullptr, edges, count, line, box, false, 0.0f, cull);
}

// 0x001a5080 CGround_vf70 (XXL2 FindAllPotentialEdgesForIntersection(edges, count, line, box, radius, cull))
void CGround::FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                                   const CLine* line, const CBBox* box, float radius, uint8_t cull) {
    ground_test::GatherEdges(*this, nullptr, edges, count, line, box, true, radius, cull);
}

// 0x001a4000 CGround_vf60 (MyDestroy)
void CGround::MyDestroy() {
    Mem_FreeAligned16(m_aVertex);
    m_ui16NbEdgeWithHeight = 0;
    m_aVertex = nullptr;
    m_aTriangle = nullptr;
    m_aEdge = nullptr;
    m_aEdgeWithHeight = nullptr;
    m_ui16NbVertex = 0;
    m_ui16NbTriangle = 0;
    m_ui16NbEdge = 0;
}

// 0x001a3ee0 CGround_RecursiveRegistration
void CGround::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) - 4u > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x001a4fb8 CGround_MessageProc. The first range ANDs with ~(1 << n) and ORs the data byte << n (not normalised).
int32_t CGround::MessageProc(uint16_t message, void* data) {
    if (((message >> 8) & 0xff) != 0x0b) return 1;
    const uint32_t low = message & 0xffu;
    const uint8_t value = *static_cast<const uint8_t*>(data);
    if (low <= 0x0f) {
        m_ba16EngineFlags = static_cast<uint16_t>((m_ba16EngineFlags & ~(1u << low)) | (static_cast<uint32_t>(value) << low));
        return 0;
    }
    if (low > 0x1f) return 1;
    const uint32_t bit = (low - 0x10) & 0xffffu;
    if (value != 0) {
        m_ui16PropertiesFlags = static_cast<uint16_t>(m_ui16PropertiesFlags | (1u << bit));
    } else {
        m_ui16PropertiesFlags = static_cast<uint16_t>(m_ui16PropertiesFlags & ~(1u << bit));
    }
    return 0;
}
