// CWall.cpp - reconstructed original translation unit 0x1a5d60-0x1a6b70 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CWall  key 0x50c  category Logic  size 0x44  vtable 0xb1c228
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a5d60  CWall_Delete
//   [x] 0x1a5db0  CWall_RecursiveRegistration
//   [x] 0x1a5e18  CWall_vf50  (GetWorldMatrix, CWall.h)
//   [x] 0x1a5e20  CWall_vf54  (GetInvertedWorldMatrix, CWall.h)
//   [x] 0x1a5e28  CWall_RefreshTransform_maybe  (Update, CWall.h: empty)
//   [ ] 0x1a5e30  RegisterCWallClass
//   [ ] 0x1a5ea8  _GLOBAL__I_1a5ea8
//   [x] 0x1a5eb8  CWall_Load
//   [ ] 0x1a5fa0  CWall_Save
//   [x] 0x1a6080  CWall_ReleaseData_maybe  (MyDestroy)
//   [x] 0x1a6120  CWall_DeleteArray
//   [x] 0x1a61c8  CWall_Create
//   [x] 0x1a6200  CWall_FindFloorAtPoint_maybe  (FindFloorAtPoint)
//   [x] 0x1a6400  CWall_vf68  (FindContact)
//   [x] 0x1a6798  CWall_CreateArray
//   [x] 0x1a6830  CWall_RaycastTriangles_maybe  (FindLineIntersection)
//
//   [ ] 0x9aadc8  CWall_GetClassType  [inline]
//   [ ] 0x9aadd0  CWall_GetClassID  [inline]
//   [ ] 0x9aadd8  CWall_IsKindOfClass  [inline]
//   [ ] 0x9aae00  CWall_DeletingDestructor  [inline]
//   [ ] 0x9aae48  CWall_Destructor  [inline]
#include "k2000/logic/CWall.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/CBBox.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CollisionDatas.h"

CWall::CWall() {}
CWall::~CWall() {}

// 0x001a5db0 CWall_RecursiveRegistration
void CWall::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x001a5eb8 CWall_Load
int32_t CWall::Load(IKFile* file, int32_t type) {
    uint32_t size = 0;
    ReadU32LE(file, &size);
    m_aVertex = static_cast<CVector3*>(Mem_AllocAligned16(size));
    ICollisionMesh::Load(file, type);  // 0x001a6c90
    m_pWorldMatrix = RwMatrixCreate_Thunk();          // 0x0023fa68
    m_pInvertedWorldMatrix = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pWorldMatrix, file);       // 0x0023f4c0
    CMatrix34_LoadMatrix(m_pInvertedWorldMatrix, file);
    return 1;
}

// 0x001a6080 CWall_ReleaseData_maybe (KStub_Nop_1a6bb8 first: nothing)
void CWall::MyDestroy() {
    if (m_aVertex != nullptr) {
        Mem_FreeAligned16(m_aVertex);
        m_aVertex = nullptr;
    }
    m_aTriangle = nullptr;
    m_ui16NbVertex = 0;
    m_ui16NbTriangle = 0;
    if (m_pWorldMatrix != nullptr) {
        RwMatrixDestroy_Thunk(m_pWorldMatrix);  // 0x0023f968
        m_pWorldMatrix = nullptr;
    }
    if (m_pInvertedWorldMatrix != nullptr) {
        RwMatrixDestroy_Thunk(m_pInvertedWorldMatrix);
        m_pInvertedWorldMatrix = nullptr;
    }
}

namespace {
// The status and distance both contact queries store (cror lt|eq: a NaN distance counts as above).
void StoreContact(CWall::ContactMaybe* contact, float dh) {
    if (dh <= 0.0f) {
        contact->m_eStatus = 0;
        contact->m_fdH = -dh;
    } else {
        contact->m_fdH = dh;
        contact->m_eStatus = 1;
    }
}
}  // namespace

// 0x001a6200 CWall_FindFloorAtPoint_maybe
uint8_t CWall::FindFloorAtPoint(ContactMaybe* contact, const CVector3* point, float maxDistance) const {
    const uint16_t* face = contact->m_pFace;
    CVector3 local;
    Mat4_TransformPoints(m_pInvertedWorldMatrix, &local, point, 1);  // 0x0023f7e8
    const CVector3& v0 = m_aVertex[face[0]];
    const CVector3& v1 = m_aVertex[face[1]];
    const CVector3& v2 = m_aVertex[face[2]];
    if (!ground_test::InsideEdge(v0, v1, local.x, local.z)) return 0;
    if (!ground_test::InsideEdge(v1, v2, local.x, local.z)) return 0;
    if (!ground_test::InsideEdge(v2, v0, local.x, local.z)) return 0;
    const float height = ground_test::HeightOnPlane(v2, contact->m_Normal, local.x, local.y, local.z);
    const float dh = height - local.y;
    if (std::fabs(dh) > maxDistance) return 0;  // the sign bit cleared; bgt: NaN goes on
    contact->m_Projection.x = local.x;
    contact->m_Projection.z = local.z;
    contact->m_Projection.y = height;
    StoreContact(contact, dh);
    return 1;
}

// 0x001a6400 CWall_vf68
uint8_t CWall::FindContact(ContactMaybe* contact, const CVector3* point, float maxDistance) const {
    CVector3 local;
    Mat4_TransformPoints(m_pInvertedWorldMatrix, &local, point, 1);
    const CCollisionTriangle* triangle = m_aTriangle;
    for (uint16_t i = 0; i < m_ui16NbTriangle; ++i, ++triangle) {
        const uint16_t* face = triangle->m_aui16Index;
        const CVector3& v0 = m_aVertex[face[0]];
        const CVector3& v1 = m_aVertex[face[1]];
        if (!ground_test::InsideEdge(v0, v1, local.x, local.z)) continue;
        const CVector3& v2 = m_aVertex[face[2]];
        if (!ground_test::InsideEdge(v1, v2, local.x, local.z)) continue;
        if (!ground_test::InsideEdge(v2, v0, local.x, local.z)) continue;
        const CVector3 normal = ground_test::FaceNormal(v0, v1, v2);
        const float height = ground_test::HeightOnPlane(v2, normal, local.x, local.y, local.z);
        const float dh = height - local.y;
        if (std::fabs(dh) > maxDistance) return 0;  // the first face decides
        contact->m_pMesh = this;
        contact->m_pFace = face;
        contact->m_Projection.z = local.z;
        contact->m_Projection.x = local.x;
        contact->m_Projection.y = height;
        contact->m_Normal.z = normal.z;
        contact->m_Normal.x = normal.x;
        contact->m_Normal.y = normal.y;
        StoreContact(contact, dh);
        return 1;
    }
    return 0;
}

// 0x001a6830 CWall_RaycastTriangles_maybe: CGround's face loop (ground_test::RaycastFaces with CGround's compares)
// except the u + v test (ble: a NaN fails).
uint8_t CWall::FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const {
    if (!AABB_OverlapsSegmentBounds(reinterpret_cast<const CBBox*>(m_AABB), line)) return 0;  // 0x0023ccb8
    CLine local;
    Mat4_TransformPoints(m_pInvertedWorldMatrix, &local.m_start, &line->m_start, 1);     // 0x0023f7e8
    Mat4_TransformVectors(m_pInvertedWorldMatrix, &local.m_VectDir, &line->m_VectDir, 1);  // 0x0023f7b0
    constexpr float kEpsilon = 9.99999975e-06f;          // TOC1 -0x2668 0x3727c5ac
    constexpr float kLow = -9.99999975e-06f;             // TOC1 -0x2664 0xb727c5ac
    constexpr float kHigh = 1.00001001f;                 // TOC1 -0x2658 0x3f800054
    constexpr double kHighDouble = 1.0000099999997474;   // TOC1 -0x2660 (lfd)
    const float dx = local.m_VectDir.x, dy = local.m_VectDir.y, dz = local.m_VectDir.z;
    bool found = false;
    for (uint32_t i = 0; i < m_ui16NbTriangle; ++i) {
        const uint16_t* face = m_aTriangle[i].m_aui16Index;
        const CVector3& v0 = m_aVertex[face[0]];
        const CVector3& v1 = m_aVertex[face[1]];
        const CVector3& v2 = m_aVertex[face[2]];
        const float e2z = v2.z - v0.z, e2x = v2.x - v0.x, e2y = v2.y - v0.y;
        const float e1y = v1.y - v0.y, e1x = v1.x - v0.x, e1z = v1.z - v0.z;
        const float py = ppc::fmsubs(e2x, dz, e2z * dx);
        const float px = ppc::fmsubs(e2z, dy, e2y * dz);
        const float pz = ppc::fmsubs(e2y, dx, e2x * dy);
        const float det = ppc::fmadds(e1z, pz, ppc::fmadds(e1x, px, e1y * py));
        if (!(det >= kEpsilon)) {
            if (backFaces != 0) continue;
            if (det > kLow) continue;
        }
        const float tz = local.m_start.z - v0.z;
        const float ty = local.m_start.y - v0.y;
        const float tx = local.m_start.x - v0.x;
        const float inverse = 1.0f / det;
        const float u = inverse * ppc::fmadds(pz, tz, ppc::fmadds(px, tx, py * ty));
        if (u < kLow) continue;
        if (static_cast<double>(u) > kHighDouble) continue;
        const float qy = ppc::fmsubs(e1x, tz, e1z * tx);
        const float qx = ppc::fmsubs(e1z, ty, e1y * tz);
        const float qz = ppc::fmsubs(e1y, tx, e1x * ty);
        const float v = inverse * ppc::fmadds(dz, qz, ppc::fmadds(dx, qx, dy * qy));
        if (v < kLow) continue;
        if (!(u + v <= kHigh)) continue;
        const float t = inverse * ppc::fmadds(e2z, qz, ppc::fmadds(e2x, qx, e2y * qy));
        if (!(t > kLow)) continue;
        if (t >= kHigh) continue;
        if (!(out->m_ftOnLine > t)) continue;
        out->m_ftOnLine = t;
        out->m_i32FaceIndex = static_cast<int32_t>(i & 0xffffu);
        found = true;
    }
    if (!found) return 0;
    out->m_pCollisionMesh = this;
    return 1;
}
