// CWall.h - a collision wall: a mesh with its own world matrix and inverse (key 0x50c, vtable 0xb1c228, size 0x44).
// Original unit: CWall.cpp (0x1a5d60-0x1a6b70). XXL2: KServiceCollision/KCollisionMesh/CWall.h (the ICollisionMesh slot
// names). In no level file of the game (work/level-class-keys.json); CDynamicWall (0x54c, also in none) derives from it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/ICollisionMesh.h"

class CWall : public ICollisionMesh {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x14)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x50c || key == 0x34c || key == 0xc; }  // 0x9aadd8
    DOTD_DECLARE_FACTORIES(CWall)

    // The contact a wall answers (vt+0x64 / +0x68; names ours, 0x2c bytes _maybe): not CGround's CGroundContactDatasInOut
    // (the projection sits at +0x1c here).
    struct ContactMaybe {
        const ICollisionMesh* m_pMesh;  // +0x00 vt+0x68 sets it
        const uint16_t* m_pFace;        // +0x04 the face (three vertex indices); vt+0x64 reads it
        CVector3 m_Normal;              // +0x08 vt+0x68 sets it; vt+0x64 reads it
        uint32_t m_eStatus;             // +0x14 0 under the face, 1 above it
        uint32_t m_unk18;               // +0x18
        CVector3 m_Projection;          // +0x1c the point on the face (no 0.001 lift, unlike the grounds)
        float m_fdH;                    // +0x28 the distance to the face
    };

    // 0x001a61c8 CWall_Create: only the vtable. Out of line (CWall.cpp): with inline ones the MSVC x64 Debug link of the
    // tests failed with LNK1163 on the vtable COMDAT that ClassTable.cpp also emitted.
    CWall();
    ~CWall() override;

    // vt+0x24 0x001a5db0 CWall_RecursiveRegistration: outside the memory-card types 4..7 registered with the saving manager.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x001a5eb8 CWall_Load: the buffer size, the buffer (Mem_AllocAligned16), the mesh, then two new matrices
    // loaded (the world matrix, then its inverse). No type check.
    int32_t Load(IKFile* file, int32_t type) override;

    const CMatrix34* GetWorldMatrix() const override { return m_pWorldMatrix; }  // vt+0x50 0x001a5e18 CWall_vf50
    const CMatrix34* GetInvertedWorldMatrix() const override { return m_pInvertedWorldMatrix; }  // vt+0x54 0x001a5e20
    // vt+0x58 0x001a6830 CWall_RaycastTriangles_maybe (XXL2 FindLineIntersection): the world line against the world box,
    // then taken into the wall's space against every face (CGround's compares, but u + v must be at most 1.00001: a NaN
    // fails here).
    uint8_t FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const override;
    void Update(uint8_t /*updateIndex*/) override {}  // vt+0x5c 0x001a5e28 CWall_RefreshTransform_maybe (blr)
    // vt+0x60 0x001a6080 CWall_ReleaseData_maybe (XXL2 MyDestroy): KStub_Nop_1a6bb8, the buffer freed, no triangles,
    // the counts 0, both matrices destroyed.
    void MyDestroy() override;
    // vt+0x64 0x001a6200 CWall_FindFloorAtPoint_maybe: the point (in the wall's space) against the contact's face: inside
    // it in x / z and within `maxDistance` of it, the contact gets the point on it, the distance and the status.
    virtual uint8_t FindFloorAtPoint(ContactMaybe* contact, const CVector3* point, float maxDistance) const;
    // vt+0x68 0x001a6400 CWall_vf68: the same against the first face that holds the point in x / z (its normal and the
    // mesh too); that face too far: no contact.
    virtual uint8_t FindContact(ContactMaybe* contact, const CVector3* point, float maxDistance) const;

    CMatrix34* m_pWorldMatrix;          // +0x3c RwMatrixCreate, loaded
    CMatrix34* m_pInvertedWorldMatrix;  // +0x40 RwMatrixCreate, loaded
};
static_assert(CWall::kClassKey == 0x50c, "key");
DOTD_ASSERT_SIZE(CWall, 0x44);
DOTD_ASSERT_OFFSET(CWall, m_pWorldMatrix, 0x3c);
DOTD_ASSERT_OFFSET(CWall, m_pInvertedWorldMatrix, 0x40);
DOTD_ASSERT_SIZE(CWall::ContactMaybe, 0x2c);
