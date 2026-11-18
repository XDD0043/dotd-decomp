// CKPFGraphNode.h - a node of the path-finding graph: a sector box with its cell grid, its transitions and
// the nodes it includes (key 0x40c, vtable 0xb1e618, size 0x38). Original unit: CKPFGraphNode.cpp.
// XXL2: K/KServices/KServicePathfinding/CKPFGraphNode.h (m_Sector, m_ppTransition, m_ui16TransitionSize,
// m_ui16Node, m_lpIncludedNode).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CBBox.h"
#include "k2000/misc/NavGrid.h"

class CKPFGraphTransition;
struct CVector2;

// XXL2 CPFSector (vtable 0xb1e608, 0x28 bytes on the PS3): m_box, m_grid.
class CPFSector {
public:
    CPFSector() {}  // 0x001ebd60 CKPFGraphNode_ConstructBase_maybe: the vtable and m_grid's constructor
    virtual ~CPFSector() {}

    // 0x001ebdd0 CKPFGraphNode_LoadBoundsAndCells: m_box.m_inf, m_box.m_sup (12-byte reads), the grid.
    int32_t Load(IKFile* file, int32_t type);
    // 0x001ebf00 CKPFGraphNode_SaveBoundsAndCells_maybe (CKPFGraphNode_Save's sector part): m_box.m_inf then m_box.m_sup
    // as little-endian words, then the grid's (KStub_Return1_1f0fd8: nothing); 1.
    int32_t Save(IKFile* file, int32_t type);
    // 0x001ebd30 CKPFGraphNode_FreeCells_maybe: the grid's cells freed (NavGrid_FreeCells_maybe).
    void FreeCells() { m_grid.FreeCells(); }

    // The grid is in cells of g_pfGridScale.m_cellSize from the box's minimum corner (x, z); cell coordinates as
    // floats (CVector2: x, z) are those positions times the inverse cell size.
    // 0x001ea3e0 CPFSector_FindIndexFromVector (XXL2 CPFSector::FindIndexFromVector): the cell (x, z) of a point:
    // truncated, and the last column / row when the point is on the box's far side (low byte equal to the size).
    void WorldToCell(const CVector3* point, uint8_t* cell) const;
    // 0x001ea470 CPFSector_FindVectorFromIndex (XXL2 CPFSector::FindVectorFromIndex): the centre of a cell, at the
    // box's bottom plus 0.01.
    void CellToWorldPos(const uint8_t* cell, CVector3* out) const;
    // 0x001eabc8 CPFSector_IsPathWalkableWithWidth (XXL2 CPFSector::IsPathWalkableWithWidth): whether a band of
    // half width `width` (world units) around the segment a-b (cell coordinates) only crosses open cells: the four
    // corners, then the two side edges walked cell by cell along the major axis (with the cell an edge enters
    // sideways). `strict`: a cell must have palette value 1 exactly (else: not blocked). The original passes the flag
    // in r7 (r6 is not read).
    uint8_t IsWideSegmentWalkable(float width, const CVector2* a, const CVector2* b, uint8_t strict);
    // 0x001ec108 CPFSector_IsPathWalkable (XXL2 CPFSector::IsPathWalkable): the same for the segment
    // itself (its two end cells, then the cells it crosses along the major axis).
    uint8_t IsSegmentWalkable(const CVector2* a, const CVector2* b, uint8_t strict);
    // 0x001ec820 CPFSector_OptimizeGridPath (XXL2 CPFSector::OptimizeGridPath): the A* cell path
    // (`count` cells from the goal back to the start) reduced to the cells where the band of half width `width` must
    // turn: the turning cells first, then from `start` the farthest one reachable straight (IsWideSegmentWalkable,
    // strict for the first and the last leg), into `out`; returns the number of cells written.
    uint16_t FindWideSegmentWaypoint(float width, const CVector3* start, const CVector3* end, const uint8_t* path,
                                     uint16_t count, uint8_t* out);
    // 0x001ed6e0 CKPFGraphNode_FindNearestWalkableCell_maybe (XXL2 CPFSector::FindNearestPointFromObstacle): the
    // centre of the point's cell when it is open, else of the nearest open cell (centre distance) on the first ring
    // of cells around it (up to 100 rings) that has one, at the point's height; 0 when none.
    uint8_t FindNearestWalkableCell(const CVector3* point, CVector3* out) const;
    // 0x001ee190 NavSector_ClampPointWithClearance_maybe: the point moved into its nearest open cell
    // (FindNearestWalkableCell), then kept `radius` away from the closed cells around that cell (the sides, and the
    // corner of a closed diagonal cell). 0 when no open cell was found.
    uint8_t ClampPointWithClearance(float radius, const CVector3* point, CVector3* out) const;
    // 0x001ed3c0 NavGrid_SetBoxBlocked (this = the node's sector, node +0x04): the cells under the box `min`..`max`
    // (x, z) get the dynamic obstacle bit (`blocked`) or lose it (CPFGrid::SetCellBlocked). A corner outside the
    // sector's box is clamped into it; a `max` inside it is moved 0.001 down on every axis. Returns 1.
    uint32_t SetBoxBlocked(const CVector3* min, const CVector3* max, uint8_t blocked);

    CBBox m_box;      // +0x04 XXL2 m_box
    CPFGrid m_grid;   // +0x1c XXL2 m_grid
};
DOTD_ASSERT_SIZE(CPFSector, 0x28);
DOTD_ASSERT_OFFSET(CPFSector, m_box, 0x04);
DOTD_ASSERT_OFFSET(CPFSector, m_grid, 0x1c);

class CKPFGraphNode : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x10)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x40c || key == 0xc; }  // vt+0x08 0x9b04c0
    DOTD_DECLARE_FACTORIES(CKPFGraphNode)

    // XXL2 CKPFGraphNode::GraphNodeList node (8 bytes; FreeListPool 0x00cea8.. in the original).
    struct IncludedNode {
        IKSerializable* m_pNode;  // +0x00 a CKPFGraphNode reference
        IncludedNode* m_pNext;    // +0x04
    };

    CKPFGraphNode();  // 0x001efc58 CKPFGraphNode_Construct (0x001efca8 Construct_2: the same code)
    // vt+0x10 0x001eff00 CKPFGraphNode_Destroy: the included nodes back to their pool (deleted here), the transition
    // block freed, the sector's cells freed.
    void Destroy() override;
    // vt+0x24 0x001efb60 CKPFGraphNode_RecursiveRegistration: outside the memory-card types (4..7) the node registers
    // with the saving manager (vt+0x24). (vt+0x30 0x001efbc8 PostLoad: 1, the inherited default.)
    void RecursiveRegistration(int32_t type) override;
    ~CKPFGraphNode() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001effa8 CKPFGraphNode_Load
    // 0x001efe18 NavSectors_FindBoxIdAtPoint_maybe: the node's own index, or the index of the last included
    // node (the list is sorted by the nodes' minimum y) whose box contains `point` (x, y, z).
    uint16_t FindBoxIdAtPoint(const float* point) const;
    // 0x001efda0 CKPFGraphNode_FindTransitionIndexTo_maybe: the index of the first transition whose node is `node`,
    // -1 when none.
    int32_t FindTransitionIndexTo(const IKSerializable* node) const;

    CPFSector m_Sector;                       // +0x04 XXL2 m_Sector
    CKPFGraphTransition** m_ppTransition;     // +0x2c XXL2 m_ppTransition (Mem_AllocAligned16)
    uint16_t m_ui16TransitionSize;            // +0x30 XXL2 m_ui16TransitionSize
    uint16_t m_ui16Node;                      // +0x32 XXL2 m_ui16Node; not loaded
    IncludedNode* m_lpIncludedNode;           // +0x34 XXL2 m_lpIncludedNode (the last one read first)
};
DOTD_ASSERT_SIZE(CKPFGraphNode, 0x38);
DOTD_ASSERT_OFFSET(CKPFGraphNode, m_Sector, 0x04);
DOTD_ASSERT_OFFSET(CKPFGraphNode, m_ppTransition, 0x2c);
DOTD_ASSERT_OFFSET(CKPFGraphNode, m_ui16TransitionSize, 0x30);
DOTD_ASSERT_OFFSET(CKPFGraphNode, m_lpIncludedNode, 0x34);
