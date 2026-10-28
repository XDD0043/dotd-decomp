// CDynamicGround.cpp - reconstructed original translation unit 0x1a1c58-0x1a3920 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: CDynamicGround  key 0x4cc  category Logic  size 0x74  vtable 0xb1c0b0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a1c58  CDynamicGround_Delete
//   [x] 0x1a1ca8  CDynamicGround_vf50
//   [x] 0x1a1cc0  CDynamicGround_vf54
//   [ ] 0x1a1cc8  RegisterCDynamicGroundClass
//   [ ] 0x1a1d40  _GLOBAL__I_1a1d40
//   [ ] 0x1a1d50  CDynamicGround_PostLoad
//   [x] 0x1a1d78  CDynamicGround_Load
//   [ ] 0x1a1ef0  CDynamicGround_Save
//   [ ] 0x1a2168  CDynamicGround_RecursiveRegistration
//   [ ] 0x1a2190  CDynamicGround_vf60
//   [x] 0x1a21e0  CDynamicGround_DeleteArray
//   [x] 0x1a2280  CDynamicGround_Create
//   [x] 0x1a22c8  CDynamicGround_vf6C
//   [x] 0x1a2798  CDynamicGround_RefreshTransform_maybe
//   [x] 0x1a2860  CDynamicGround_FindFloorAtPoint_maybe
//   [x] 0x1a2ad8  CDynamicGround_ProbeGround_maybe
//   [x] 0x1a2ea8  CDynamicGround_CreateArray
//   [x] 0x1a2f48  CDynamicGround_RaycastTriangles_maybe
//   [x] 0x1a32b8  CDynamicGround_vf70
//
//   [ ] 0x9aabb8  CDynamicGround_IsKindOfClass  [inline]
//   [ ] 0x9aabf0  CDynamicGround_GetClassType  [inline]
//   [ ] 0x9aabf8  CDynamicGround_GetClassID  [inline]
//   [ ] 0x9aac00  CDynamicGround_GetSerializationFlags  [inline]
//   [ ] 0x9aac08  CDynamicGround_DeletingDestructor  [inline]
//   [ ] 0x9aac50  CDynamicGround_Destructor  [inline]
#include "k2000/logic/physics/CDynamicGround.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/CBBox.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CollisionDatas.h"

// 0x001a1d78 CDynamicGround_Load
int32_t CDynamicGround::Load(IKFile* file, int32_t type) {
    CGround::Load(file, type);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_OBB), 6);
    IKFile_ReadRef(file, &m_pParent);
    m_pInvertedWorldMatrix = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pInvertedWorldMatrix, file);
    m_ui8UpdateIndex = 100;
    return 1;
}

// 0x001a1ca8 CDynamicGround_vf50: the parent's frame +0x50 (its LTM as stored, not recomputed).
const CMatrix34* CDynamicGround::GetWorldMatrix() const {
    return reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(m_pParent)->m_pRwFrame->ltm);
}

// 0x001a2798 CDynamicGround_RefreshTransform_maybe
void CDynamicGround::Update(uint8_t updateIndex) {
    if (m_ui8UpdateIndex == updateIndex) return;
    m_ui8UpdateIndex = updateIndex;
    m_ba16EngineFlags = static_cast<uint16_t>(m_ba16EngineFlags & ~0x20u);
    if ((m_ba16EngineFlags & 1) == 0) return;
    const CMatrix34* world = GetWorldMatrix();
    Mat4_Invert(m_pInvertedWorldMatrix, world);
    BBox_TransformByMatrix(reinterpret_cast<CBBox*>(m_AABB), reinterpret_cast<const CBBox*>(m_OBB), world);
}

// 0x001a2860 CDynamicGround_FindFloorAtPoint_maybe
uint8_t CDynamicGround::GetGroundContactOnFace(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                               const CVector3* point) const {
    const uint16_t* face = GroundContact_GetTriangle(inOut);
    CVector3 local;
    Mat4_TransformPoints(m_pInvertedWorldMatrix, &local, point, 1);
    const CVector3& v0 = m_aVertex[face[0]];
    const CVector3& v1 = m_aVertex[face[1]];
    if (!ground_test::InsideEdge(v0, v1, local.x, local.z)) return 0;
    const CVector3& v2 = m_aVertex[face[2]];
    if (!ground_test::InsideEdge(v1, v2, local.x, local.z)) return 0;
    if (!ground_test::InsideEdge(v2, v0, local.x, local.z)) return 0;
    const float height = ground_test::HeightOnPlane(v2, inOut->m_Normal, local.x, local.y, local.z);
    const float dh = height - local.y;
    uint32_t status;
    if (dh <= 0.0f) {
        inOut->m_fdH = -dh;
        status = 0;
    } else if (in->m_fDeltaMax >= dh && inOut->m_eContactStatus != 2) {
        inOut->m_fdH = dh;
        status = 1;
    } else if (in->m_fObjectHeight >= dh) {
        inOut->m_fdH = dh;
        status = 2;
    } else {
        return 0;
    }
    inOut->m_ProjectionOnGround.x = local.x;
    inOut->m_ProjectionOnGround.z = local.z;
    inOut->m_ProjectionOnGround.y = height + 0.001f;
    inOut->m_eContactStatus = status;
    return 1;
}

// 0x001a2ad8 CDynamicGround_ProbeGround_maybe: the local point inside the local box (x, z; y above its bottom less
// m_fObjectHeight), then CGround's face walk on the local point.
uint8_t CDynamicGround::GetGroundContact(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                         const CVector3* point) const {
    CVector3 local;
    Mat4_TransformPoints(m_pInvertedWorldMatrix, &local, point, 1);
    const CBBox& box = *reinterpret_cast<const CBBox*>(m_OBB);
    if (!(box.m_inf.x <= local.x) || !(box.m_sup.x >= local.x)) return 0;
    if (!(box.m_inf.z <= local.z) || !(box.m_sup.z >= local.z)) return 0;
    if (!(local.y >= box.m_inf.y - in->m_fObjectHeight)) return 0;
    for (uint32_t i = 0; i < m_ui16NbTriangle; ++i) {
        const uint16_t* face = m_aTriangle[i].m_aui16Index;
        const CVector3& v0 = m_aVertex[face[0]];
        const CVector3& v1 = m_aVertex[face[1]];
        if (!ground_test::InsideEdge(v0, v1, local.x, local.z)) continue;
        const CVector3& v2 = m_aVertex[face[2]];
        if (!ground_test::InsideEdge(v1, v2, local.x, local.z)) continue;
        if (!ground_test::InsideEdge(v2, v0, local.x, local.z)) continue;
        const CVector3 normal = ground_test::FaceNormal(v0, v1, v2);
        const float height = ground_test::HeightOnPlane(v2, normal, local.x, local.y, local.z);
        const float dh = height - local.y;
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
        inOut->m_fdH = stored;
        inOut->m_eContactStatus = status;
        inOut->m_i32FaceIndex = static_cast<int32_t>(i & 0xffffu);
        inOut->m_pGround = const_cast<CDynamicGround*>(this);
        inOut->m_ProjectionOnGround.x = local.x;
        inOut->m_Normal = normal;
        inOut->m_ProjectionOnGround.z = local.z;
        inOut->m_ProjectionOnGround.y = height + 0.001f;
        return 1;
    }
    return 0;
}

// 0x001a2f48 CDynamicGround_RaycastTriangles_maybe: the world line against the world box, then the line taken into the
// ground's space (its start through the inverse matrix as a point, its direction as a vector) against the local box,
// then the faces (CDynamicGround's form of the compares).
uint8_t CDynamicGround::FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const {
    if (!AABB_OverlapsSegmentBounds(reinterpret_cast<const CBBox*>(m_AABB), line)) return 0;
    CLine local;
    Mat4_TransformPoints(m_pInvertedWorldMatrix, &local.m_start, &line->m_start, 1);
    Mat4_TransformVectors(m_pInvertedWorldMatrix, &local.m_VectDir, &line->m_VectDir, 1);
    if (!AABB_OverlapsSegmentBounds(reinterpret_cast<const CBBox*>(m_OBB), &local)) return 0;
    if (!ground_test::RaycastFaces(*this, local, out, backFaces, true)) return 0;
    out->m_pCollisionMesh = this;
    return 1;
}

// 0x001a22c8 CDynamicGround_vf6C: CGround's gathering on the edges' vertices taken to the world (the parent's frame
// matrix, read as stored).
void CDynamicGround::FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                                          const CLine* line, const CBBox* box, uint8_t cull) {
    ground_test::GatherEdges(*this, GetWorldMatrix(), edges, count, line, box, false, 0.0f, cull);
}

// 0x001a32b8 CDynamicGround_vf70: the sweep form, the same way.
void CDynamicGround::FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                                          const CLine* line, const CBBox* box, float radius,
                                                          uint8_t cull) {
    ground_test::GatherEdges(*this, GetWorldMatrix(), edges, count, line, box, true, radius, cull);
}
