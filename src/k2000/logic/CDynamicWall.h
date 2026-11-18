// CDynamicWall.h - a collision wall that follows a scene-graph node (key 0x54c, vtable 0xb1c130, size 0x68). Original
// unit: CDynamicWall.cpp (0x1a3920-0x1a3e90). XXL2: KServiceCollision/KCollisionMesh/CDynamicWall.h (m_pParent,
// m_pLocalMatrix, m_OBB, m_ui8UpdateIndex in this order, the same Load). In no level file of the game
// (work/level-class-keys.json); C2.8 port-rest R05 ported it from the disassembly.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CWall.h"

class CDynamicWall : public CWall {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x15)
    // vt+0x08 0x009aac70 CDynamicWall_IsKindOfClass
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x54c || key == 0x50c || key == 0x34c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CDynamicWall)

    // 0x001a3da8 CDynamicWall_Create: CWall's vtable, then this one (no member stores).
    CDynamicWall();
    // 0x009aad08 / 0x009aacc0 CDynamicWall_Destructor / _DeletingDestructor (inline): vtable stores only.
    ~CDynamicWall() override;

    // vt+0x24 0x001a3970 CDynamicWall_RecursiveRegistration: CWall's (outside the memory-card types 4..7 registered with
    // the saving manager), its own copy.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x001a3b38 CDynamicWall_Load: CWall's, the local box (one 0x18 read, each word swapped), the parent
    // reference, a new local matrix loaded; the update index 100.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x5c 0x001a3a68 CDynamicWall_RefreshTransform_maybe: once per update index the world matrix = the local matrix
    // times the parent frame's LTM, its inverse, the world box; a wall in a quadtree (+0x04) passes the box on.
    void Update(uint8_t updateIndex) override;
    // 0x001a6bc0 CDynamicWall_UpdateQuadtreeBounds_maybe (not virtual; CKSrvDetect.cpp's unit): the quadtree agent
    // (+0x04) gets the world box's x / z extent (min x / z from the box's +0x0c / +0x14, max from +0x00 / +0x08), then
    // it and its parents are invalidated.
    void UpdateQuadtreeBounds();
    // vt+0x60 0x001a3cb0 CDynamicWall_FreeGeometry: CWall's MyDestroy, the local matrix destroyed, no parent.
    void MyDestroy() override;

    IKSerializable* m_pParent;    // +0x44 reference: the CSGLeaf / node whose frame the wall follows
    CMatrix34* m_pLocalMatrix;    // +0x48 RwMatrixCreate + CMatrix34_LoadMatrix
    float m_OBB[6];               // +0x4c CBBox: the local box (min, max)
    uint8_t m_ui8UpdateIndex;     // +0x64 Load sets 100
    uint8_t m_pad65[3];
};
static_assert(CDynamicWall::kClassKey == 0x54c, "key");
DOTD_ASSERT_SIZE(CDynamicWall, 0x68);
DOTD_ASSERT_OFFSET(CDynamicWall, m_pParent, 0x44);
DOTD_ASSERT_OFFSET(CDynamicWall, m_pLocalMatrix, 0x48);
DOTD_ASSERT_OFFSET(CDynamicWall, m_OBB, 0x4c);
DOTD_ASSERT_OFFSET(CDynamicWall, m_ui8UpdateIndex, 0x64);
