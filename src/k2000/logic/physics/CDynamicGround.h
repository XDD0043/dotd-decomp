// CDynamicGround.h - a moving collision mesh (key 0x4cc, vtable 0xb1c0b0, size 0x74). Original unit:
// CDynamicGround.cpp. XXL2: KServiceCollision/KCollisionMesh/CDynamicGround.h, the same members in the
// same order (m_pParent, m_pInvertedWorldMatrix, m_OBB, m_ui8UpdateIndex).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/CMatrix34.h"

class CDynamicGround : public CGround {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x13)
    DOTD_DECLARE_FACTORIES(CDynamicGround)

    CDynamicGround() {}  // CDynamicGround_Create: only the vtables (CGround's, then its own)
    ~CDynamicGround() override {}

    // vt+0x2c 0x001a1d78 CDynamicGround_Load: CGround's, the box, the parent, a new matrix (loaded), the
    // update index 100.
    int32_t Load(IKFile* file, int32_t type) override;

    // vt+0x50 0x001a1ca8 CDynamicGround_vf50: the parent leaf's frame matrix (RwFrame +0x50, read as stored).
    const CMatrix34* GetWorldMatrix() const override;
    // vt+0x54 0x001a1cc0 CDynamicGround_vf54
    const CMatrix34* GetInvertedWorldMatrix() const override { return m_pInvertedWorldMatrix; }
    // vt+0x58 0x001a2f48 CDynamicGround_RaycastTriangles_maybe
    uint8_t FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const override;
    // vt+0x5c 0x001a2798 CDynamicGround_RefreshTransform_maybe: once per update index, flag 0x20 cleared and, while the
    // ground is active, the inverse of the parent's matrix and the world box (the local box m_OBB through the matrix).
    void Update(uint8_t updateIndex) override;
    // vt+0x64 0x001a2860 CDynamicGround_FindFloorAtPoint_maybe: CGround's in the ground's space (the point through
    // the inverse matrix; the contact stays local), and a status 2 contact does not become 1.
    uint8_t GetGroundContactOnFace(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                   const CVector3* point) const override;
    // vt+0x68 0x001a2ad8 CDynamicGround_ProbeGround_maybe: CGround's in the ground's space, after the local box test.
    uint8_t GetGroundContact(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                             const CVector3* point) const override;
    // vt+0x6c 0x001a22c8 CDynamicGround_vf6C / vt+0x70 0x001a32b8 CDynamicGround_vf70
    void FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                              const CLine* line, const CBBox* box, uint8_t withHeights) override;
    void FindAllPotentialEdgesForIntersection(SExtrapolated_Edge2D_Full_Infos* edges, uint8_t* count,
                                              const CLine* line, const CBBox* box, float height,
                                              uint8_t withHeights) override;

    IKSerializable* m_pParent;          // +0x50 CSGLeaf
    CMatrix34* m_pInvertedWorldMatrix;  // +0x54 RwMatrixCreate + CMatrix34_LoadMatrix
    float m_OBB[6];                     // +0x58 CBBox, one 0x18 read, each word swapped
    uint8_t m_ui8UpdateIndex;           // +0x70 Load sets 100
};
static_assert(CDynamicGround::kClassKey == 0x4cc, "key");
DOTD_ASSERT_SIZE(CDynamicGround, 0x74);
DOTD_ASSERT_OFFSET(CDynamicGround, m_pParent, 0x50);
DOTD_ASSERT_OFFSET(CDynamicGround, m_pInvertedWorldMatrix, 0x54);
DOTD_ASSERT_OFFSET(CDynamicGround, m_OBB, 0x58);
DOTD_ASSERT_OFFSET(CDynamicGround, m_ui8UpdateIndex, 0x70);
