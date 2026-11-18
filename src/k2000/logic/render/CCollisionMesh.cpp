// CCollisionMesh.cpp - reconstructed original translation unit 0x1a14e8-0x1a1c58 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CCollisionMesh  key 0x38c  category Logic  size 0x3c  vtable 0xb1c040
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a14e8  CCollisionMesh_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1a1538  CCollisionMesh_RecursiveRegistration
//   [x] 0x1a15a0  CCollisionMesh_vf50  (header)
//   [x] 0x1a15a8  CCollisionMesh_vf54  (header)
//   [x] 0x1a15b0  CCollisionMesh_RefreshTransform_maybe  (header)
//   [ ] 0x1a15b8  CCollisionMesh_Save
//   [ ] 0x1a1678  RegisterCCollisionMeshClass
//   [ ] 0x1a16f0  _GLOBAL__I_1a16f0
//   [x] 0x1a1700  CCollisionMesh_Load
//   [x] 0x1a17b0  CCollisionMesh_FreeGeometry
//   [x] 0x1a1810  CCollisionMesh_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1a18b8  CCollisionMesh_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1a18f0  CCollisionMesh_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1a1988  CCollisionMesh_RaycastTriangles_maybe
//
//   [ ] 0x9aab18  CCollisionMesh_GetClassType  [inline]
//   [ ] 0x9aab20  CCollisionMesh_GetClassID  [inline]
//   [ ] 0x9aab28  CCollisionMesh_IsKindOfClass  [inline]
//   [ ] 0x9aab50  CCollisionMesh_DeletingDestructor  [inline]
//   [ ] 0x9aab98  CCollisionMesh_Destructor  [inline]
#include "k2000/logic/render/CCollisionMesh.h"

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/math/CBBox.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CollisionDatas.h"

// 0x001a1700 CCollisionMesh_Load: no type check.
int32_t CCollisionMesh::Load(IKFile* file, int32_t type) {
    uint32_t size = 0;
    ReadU32LE(file, &size);
    m_aVertex = static_cast<CVector3*>(Mem_AllocAligned16(size));
    ICollisionMesh::Load(file, type);
    return 1;
}

// 0x001a1538 CCollisionMesh_RecursiveRegistration
void CCollisionMesh::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) - 4u > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x001a17b0 CCollisionMesh_FreeGeometry
void CCollisionMesh::MyDestroy() {
    if (m_aVertex != nullptr) {
        Mem_FreeAligned16(m_aVertex);
        m_aVertex = nullptr;
    }
    m_ui16NbTriangle = 0;
    m_aTriangle = nullptr;
    m_ui16NbVertex = 0;
}

// 0x001a1988 CCollisionMesh_RaycastTriangles_maybe (Moeller-Trumbore with the original's fused terms, as CGround's)
uint8_t CCollisionMesh::FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const {
    if (!AABB_OverlapsSegmentBounds(reinterpret_cast<const CBBox*>(m_AABB), line)) return 0;  // 0x0023ccb8
    if (m_ui16NbTriangle == 0) return 0;
    constexpr float kEpsilon = 9.99999975e-06f;  // TOC -0x2790 (0x3727c5ac)
    constexpr float kLow = -9.99999975e-06f;     // TOC -0x278c
    constexpr float kHigh = 0.99998999f;         // TOC -0x2784 (0x3f7fff58)
    const float dx = line->m_VectDir.x, dy = line->m_VectDir.y, dz = line->m_VectDir.z;
    bool found = false;
    for (uint32_t i = 0; i < m_ui16NbTriangle; ++i) {
        const uint16_t* face = m_aTriangle[i].m_aui16Index;
        const CVector3& v0 = m_aVertex[face[0]];
        const CVector3& v1 = m_aVertex[face[1]];
        const CVector3& v2 = m_aVertex[face[2]];
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
        const float inverse = 1.0f / det;
        const float ty = line->m_start.y - v0.y;
        const float tx = line->m_start.x - v0.x;
        const float tz = line->m_start.z - v0.z;
        const float u = inverse * ppc::fmadds(pz, tz, ppc::fmadds(px, tx, py * ty));
        if (u < kEpsilon) continue;
        if (u > kHigh) continue;
        const float qy = ppc::fmsubs(e1x, tz, e1z * tx);
        const float qx = ppc::fmsubs(e1z, ty, e1y * tz);
        const float qz = ppc::fmsubs(e1y, tx, e1x * ty);
        const float v = inverse * ppc::fmadds(dz, qz, ppc::fmadds(dx, qx, dy * qy));
        if (!(v >= kEpsilon)) continue;
        if (u + v > kHigh) continue;
        const float t = inverse * ppc::fmadds(e2z, qz, ppc::fmadds(e2x, qx, e2y * qy));
        if (t <= kEpsilon) continue;
        if (t >= kHigh) continue;
        if (out->m_ftOnLine <= t) continue;
        out->m_ftOnLine = t;
        out->m_i32FaceIndex = static_cast<int32_t>(i & 0xffffu);
        found = true;
    }
    if (!found) return 0;
    out->m_pCollisionMesh = this;
    return 1;
}
