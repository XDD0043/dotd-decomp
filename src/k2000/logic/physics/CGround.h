// CGround.h - a static collision mesh (key 0x48c, vtable 0xb1c1a8, size 0x50). Original unit: CGround.cpp
// (0x1a3e90-0x1a5d60). XXL2: KServiceCollision/KCollisionMesh/CGround.h, the same members in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/ICollisionMesh.h"

struct CGroundContactDatasIn;
struct CGroundContactDatasInOut;

class CGround : public ICollisionMesh {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x12)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9aad38
        return key == 0x48c || key == 0x34c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CGround)

    // An edge without height (4 bytes: two vertex indices).
    struct SCollisionMeshEdge {
        uint16_t m_aui16Index[2];
    };
    // An edge with height (12 bytes: two vertex indices and two floats).
    struct SCollisionMeshEdgeWithHeight {
        uint16_t m_aui16Index[2];
        float m_afValue[2];
    };

    CGround() {}  // 0x001a4108 CGround_Create: only the vtable
    ~CGround() override {}

    // vt+0x2c 0x001a5610 CGround_Load: the buffer size, the buffer (Mem_AllocAligned16), the mesh, then the
    // edges after the triangles in the same buffer and two floats. No type check.
    int32_t Load(IKFile* file, int32_t type) override;

    // vt+0x24 0x001a3ee0 CGround_RecursiveRegistration: registered with the saving manager unless the type is 4..7
    // (CDynamicGround's 0x1a2168 is this one).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x1c 0x001a4fb8 CGround_MessageProc: the messages 0x0b00..0x0b0f store the data byte shifted into bit n of
    // m_ba16EngineFlags, 0x0b10..0x0b1f set (byte != 0) or clear bit n - 0x10 of m_ui16PropertiesFlags (0 returned);
    // anything else returns 1. vt+0x40 GetInfo 0x1a4fb0 / vt+0x30 PostLoad 0x1a5078: return 1 (IKSerializable's).
    int32_t MessageProc(uint16_t message, void* data) override;

    // vt+0x50 0x001a3f48 CGround_vf50 / vt+0x54 0x001a3f50 CGround_vf54: a static ground has no matrix.
    const CMatrix34* GetWorldMatrix() const override { return nullptr; }
    const CMatrix34* GetInvertedWorldMatrix() const override { return nullptr; }
    // vt+0x58 0x001a4cb8 CGround_RaycastTriangles_maybe (XXL2 FindLineIntersection).
    uint8_t FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const override;
    void Update(uint8_t /*updateIndex*/) override {}  // vt+0x5c 0x001a3f58 CGround_RefreshTransform_maybe (blr)
    // vt+0x60 0x001a4000 CGround_vf60 (XXL2 MyDestroy): KStub_Nop_1a6bb8, the buffer (vertices, triangles, edges)
    // freed, the pointers and counts cleared.
    void MyDestroy() override;
    // vt+0x64 0x001a4620 CGround_FindFloorAtPoint_maybe (XXL2 GetGroundContactOnFace): the point against the face the
    // contact already holds (its normal too): inside it in x / z, the contact gets the height there (+0.001), the
    // signed distance and the status 0 (under the face), 1 (within m_fDeltaMax above) or 2 (within m_fObjectHeight).
    virtual uint8_t GetGroundContactOnFace(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                           const CVector3* point) const;
    // vt+0x68 0x001a4868 CGround_GetTriangleNormalAtPoint_maybe (XXL2 GetGroundContact): the first face that holds
    // the point in x / z decides (its normal, index and the same statuses; too far below it: no contact).
    virtual uint8_t GetGroundContact(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                     const CVector3* point) const;
    // vt+0x6c 0x001a4140 CGround_vf6C / vt+0x70 0x001a5080 CGround_vf70 (XXL2 FindAllPotentialEdgesForIntersection,
    // the line's and the line-with-height's forms): the ground's wall edges near a line, into `edges` from `*count`.
    virtual void FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                                      const CLine* line, const CBBox* box, uint8_t withHeights);
    virtual void FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                                      const CLine* line, const CBBox* box, float height,
                                                      uint8_t withHeights);

    float m_fHeightOffsetForNegativeEdges;            // +0x3c (XXL2 order)
    float m_fPropertieValue;                          // +0x40
    SCollisionMeshEdge* m_aEdge;                      // +0x44 null when there are none (Ghidra pInfiniteWalls)
    SCollisionMeshEdgeWithHeight* m_aEdgeWithHeight;  // +0x48 null when none (Ghidra pFiniteWalls)
    uint16_t m_ui16NbEdge;                            // +0x4c
    uint16_t m_ui16NbEdgeWithHeight;                  // +0x4e
};
static_assert(CGround::kClassKey == 0x48c, "key");
DOTD_ASSERT_SIZE(CGround, 0x50);
DOTD_ASSERT_OFFSET(CGround, m_fHeightOffsetForNegativeEdges, 0x3c);
DOTD_ASSERT_OFFSET(CGround, m_fPropertieValue, 0x40);
DOTD_ASSERT_OFFSET(CGround, m_aEdge, 0x44);
DOTD_ASSERT_OFFSET(CGround, m_aEdgeWithHeight, 0x48);
DOTD_ASSERT_OFFSET(CGround, m_ui16NbEdge, 0x4c);
DOTD_ASSERT_OFFSET(CGround, m_ui16NbEdgeWithHeight, 0x4e);

// The ground tests CGround and CDynamicGround share (their code is the same in both classes, operation for operation):
// the point in a face in x / z, the face's normal, the face's height under the point.
namespace ground_test {
// The point is on the inner side of the edge (a, b) in x / z: fmsubs(b.x - a.x, p.z - a.z, (b.z - a.z) * (p.x - a.x))
// <= 0 (a NaN is outside).
bool InsideEdge(const CVector3& a, const CVector3& b, float px, float pz);
// The face normal of (v0, v1, v2), normalised unless its length is 0 (the cross product of v1 - v0 and v2 - v0 with
// the original's fused terms).
CVector3 FaceNormal(const CVector3& v0, const CVector3& v1, const CVector3& v2);
// The height of the plane (v2, normal) at (p.x, p.z): v2.y - fmadds(dx, n.x, dz * n.z) / n.y, p.y when n.y is 0.
float HeightOnPlane(const CVector3& v2, const CVector3& normal, float px, float py, float pz);
// The face walk of FindLineIntersection (Moeller-Trumbore with the original's fused terms) on `line` in the mesh's
// space: faces facing the line (det >= 1e-5; with `backFaces` 0 also det <= -1e-5), u and v in -1e-5..1.00001,
// t in (-1e-5, 1.00001) and below the time `out` holds: the time and the face index go to `out`. CGround compares u
// with the double 1.0000099999997474 and keeps t when out->t > t; CDynamicGround compares u as a float and keeps t
// unless out->t <= t (`dynamicForm`). Returns whether a face was kept.
bool RaycastFaces(const ICollisionMesh& mesh, const CLine& line, CLineCollisionDatas* out, uint8_t backFaces,
                  bool dynamicForm);
// The edge gathering of FindAllPotentialEdgesForIntersection for both forms (vt+0x6c: `withRadius` false; vt+0x70:
// the box grown by 0.1 in x / z, the edge's normal and circle centres stored and its start moved out by `radius`).
// `world` takes the vertices to the world first (a moving ground's matrix), null for a static ground.
void GatherEdges(const CGround& ground, const CMatrix34* world, SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                 const CLine* line, const CBBox* box, bool withRadius, float radius, uint8_t cull);
}  // namespace ground_test
