// ICollisionMesh.h - the base of the collision meshes (key 0x34c, abstract; CGround, CDynamicGround). Its
// Load sits in CKSrvDetect.cpp's unit (0x1a6c90). XXL2: K/KServices/KServiceCollision/KCollisionMesh/
// ICollisionMesh.h, the same members in the same order (m_aVertex, m_aTriangle, m_pSector, m_AABB, the
// counts and flags); DotD has two words before them.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

struct CLine;
struct CLineCollisionDatas;
struct SExtrapolated_Edge2D_Full_Infos;
struct CBBox;

class ICollisionMesh : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xd)

    ICollisionMesh() {}  // inlined in the derived Creates: no stores
    ~ICollisionMesh() override {}
    // vt+0x10 0x001a6c50 ICollisionMesh_Destroy: MyDestroy (vt+0x60).
    void Destroy() override { MyDestroy(); }

    // vt+0x2c 0x001a6c90 ICollisionMesh_Load. Not a type check: CGround calls it for every type. The vertex
    // buffer (m_aVertex) is allocated by the caller first; the triangles follow the vertices in it.
    int32_t Load(IKFile* file, int32_t type) override;

    // The mesh slots (XXL2 ICollisionMesh / CGround / CWall names; every DotD mesh class fills them).
    // vt+0x50 GetWorldMatrix: the matrix that takes the mesh's vertices to the world; null for a static mesh.
    virtual const CMatrix34* GetWorldMatrix() const = 0;
    // vt+0x54 GetInvertedWorldMatrix: its inverse; null for a static mesh.
    virtual const CMatrix34* GetInvertedWorldMatrix() const = 0;
    // vt+0x58 FindLineIntersection (Ghidra *_RaycastTriangles_maybe): the first triangle the line crosses.
    virtual uint8_t FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const = 0;
    // vt+0x5c Update (Ghidra *_RefreshTransform_maybe): a moving mesh takes its parent's matrix once per update
    // index (the kluster toggles the index every frame).
    virtual void Update(uint8_t updateIndex) = 0;
    // vt+0x60 MyDestroy (XXL2): the mesh's buffers freed (CGround's, CDynamicGround's).
    virtual void MyDestroy() = 0;

    // 0x001a6b70 ICollisionMesh_SetActive: bit 0 of the engine flags (the mesh is tested) and the level's
    // ground-list-dirty bit (CKLevel +0x2f bit 0: the klusters rebuild their active ground lists).
    void SetActive(uint16_t active);
    // 0x001a6ba8 ICollisionMesh_GetMeshSlotIndex_maybe: the number of the mesh's sector.
    uint16_t GetSectorNumber() const;

    // A triangle: three vertex indices (6 bytes).
    struct CCollisionTriangle {
        uint16_t m_aui16Index[3];
    };

    IKSerializable* m_unk04;          // +0x04 a reference (0 in the LVL010 samples)
    uint32_t m_unk08;                 // +0x08 not read (non-zero live: set at runtime)
    CVector3* m_aVertex;              // +0x0c the mesh's buffer (vertices, then triangles, then the edges)
    CCollisionTriangle* m_aTriangle;  // +0x10 m_aVertex + m_ui16NbVertex * 0xc
    IKSerializable* m_pSector;        // +0x14 CKSector
    float m_AABB[6];                  // +0x18 CBBox (min, max)
    uint16_t m_ui16NbVertex;          // +0x30
    uint16_t m_ui16NbTriangle;        // +0x32
    uint16_t m_ui16LastRayID;         // +0x34 Load sets 0
    uint16_t m_ba16EngineFlags;       // +0x36 CBitArray16
    uint16_t m_ui16PropertiesFlags;   // +0x38
    uint8_t m_ui8Type;                // +0x3a
};
static_assert(ICollisionMesh::kClassKey == 0x34c, "key");
DOTD_ASSERT_SIZE(ICollisionMesh, 0x3c);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_aVertex, 0x0c);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_aTriangle, 0x10);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_pSector, 0x14);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_AABB, 0x18);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_ui16NbVertex, 0x30);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_ui16NbTriangle, 0x32);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_ui16LastRayID, 0x34);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_ba16EngineFlags, 0x36);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_ui16PropertiesFlags, 0x38);
DOTD_ASSERT_OFFSET(ICollisionMesh, m_ui8Type, 0x3a);
