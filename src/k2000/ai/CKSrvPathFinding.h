// CKSrvPathFinding.h - the path-finding service (key 0x181, vtable 0xb1e548, size 0x76f0). Original unit:
// CKSrvPathFinding.cpp (0x1e3c08-0x1e9ee0). XXL2: K/KServices/KServicePathfinding/CKSrvPathfinding.h,
// the same members in the same order: m_Graph, m_AstarGraph, m_AstarGrid, m_aPathStock[20].
//
// C1.3 ports what the Load needs and the constructor; step 4 the path queries (the follower's) and the searches.
#pragma once
#include <cstdint>

#include "k2000/ai/TAstar.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/physics/CKQuadTreeRoot.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/IKService.h"

// 0x00c4025c: the path-finding grid scale. Its static values are (1, 0.5, 1); CKSrvPathFinding_Load
// reads the cell size and derives the other two. Name ours.
class CKPFGraphTransition;

struct PFGridScale_maybe {
    float m_cellSize;      // +0x00
    float m_halfCellSize;  // +0x04 m_cellSize * 0.5
    float m_invCellSize;   // +0x08 1 / m_cellSize
};
extern PFGridScale_maybe g_pfGridScale;

// XXL2 CPFCharacter (8 bytes there; 0x10 in DotD). The members are unnamed.
struct CPFCharacter {
    // 0x001e9b78 PathFindingParams_Load: the four words, swapped (K_LEVEL_PLATEFORMS only).
    void Load(IKFile* file, int32_t type);

    uint32_t m_bits;  // +0x00 a bitfield: 0x407 in the service, 0 in the path slots
    float m_fRadius;    // +0x04 g_pfGridScale.m_halfCellSize * 0.2 at construction
    float m_fMaxStepHeight;    // _maybe: +0x08 0.2
    float m_fMaxStepRise;    // _maybe: +0x0c 1.0
};
DOTD_ASSERT_SIZE(CPFCharacter, 0x10);

// XXL2 CPFGraph (m_apGraphNodes, m_ui32GraphNodesSize, m_Character); DotD keeps the sector quadtree in it.
struct CPFGraph {
    // 0x001f0c38 (Ghidra CKSrvPathFinding_LoadGraph_maybe; XXL2 CPFGraph::Load).
    int32_t Load(IKFile* file, int32_t type);
    // 0x001f0bd0 CKSrvPathFinding_ClearGraph_maybe (CKPFGraphTransition_2.cpp's unit; XXL2 CPFGraph::Destroy).
    void Clear();
    // 0x001f0de8 CKSrvPathFinding_SaveGraph_maybe (CKSrvPathFinding_Save's; XXL2 CPFGraph::Save): the node count
    // (little-endian), then the nodes as contiguous handles (the saving manager's vt+0x4c), or without one the
    // block's raw words; 1.
    int32_t Save(IKFile* file, int32_t type);

    IKSerializable** m_apGraphNodes;  // +0x00 CKPFGraphNode* (Mem_AllocAligned16); not set by the constructor
    uint32_t m_ui32GraphNodesSize;    // +0x04
    CPFCharacter m_Character;         // +0x08
    CKQuadTreeRoot m_quadTree;        // +0x18 (Ghidra NavSectorQuadTree)
};
DOTD_ASSERT_SIZE(CPFGraph, 0x3c);

// The open list and the searches (TAstarOpenList, TAstar) are in k2000/ai/TAstar.h.

// XXL2 CPFPoint (m_vPoint, m_i16GraphNodeIndex).
struct CPFPoint {
    CVector3 m_position;  // +0x00 XXL2 m_vPoint; not set by the constructor
    uint16_t m_i16GraphNodeIndex;     // +0x0c XXL2 m_i16GraphNodeIndex: the graph node (or included box) holding the point,
                          //       0xffff none (the constructors' value)
    uint16_t m_pad0e;
};

// The two-word result of the sector searches (FindSectorRoute, SolveSectorSegment; returned through r3): the query's
// next state and a count (the route / path length, or -1).
struct PFSearchResult {
    uint32_t m_eState;   // +0x00
    int16_t m_i16Value;  // +0x04
    uint16_t m_pad06;
};

// XXL2 CPFPathSlot (Ghidra PFPathQuery): 0x5e8 bytes; DotD's graph path holds 200 entries (XXL2 100).
struct CPFPathSlot {
    CPFPathSlot();  // 0x001e9fe0 PFPathQuery_Construct_maybe
    // 0x001e9e28 PFPathQuery_Release_maybe: the slot free again (its character flags' low 11 bits cleared,
    // the state and every path size and index 0).
    void Release();
    // 0x001e9ee0 CPFPathSlot_Initialize (XXL2 CPFPathSlot::Initialize): the slot taken for a query from `seeker` to
    // `target` (both copied, hints included) for `character` (its bits 0-12 and its radius copied): state 0x204 (find
    // the route, waiting), the paths empty, the seek point the seeker.
    void Initialize(const CPFPoint* seeker, const CPFPoint* target, const CPFCharacter* character);
    // 0x001e9e60 CPFPathSlot_SetGraphPath (XXL2 CPFPathSlot::SetGraphPath): the graph route found (`count` nodes
    // from the goal back, at most 200 kept) stored start first; the graph path index 0.
    void SetGraphPath(uint8_t count, const CPFGraphNodeIndex* route);

    CPFPoint m_SeekerPosition;        // +0x000
    CPFPoint m_TargetPosition;        // +0x010
    CPFCharacter m_Character;         // +0x020
    uint8_t m_bIsFree;                // +0x030 1
    uint8_t m_pad31[3];
    // +0x034 0 (XXL2 ESrvPFState), a bit set: 0x200 find the graph route, 0x100 solve the grid path of the current
    // graph node, 4 waiting for the service, 2 the route is followed, 0x40 the end of the current node's grid path
    // (the portal next), 0x80 the target reached; the failures 9 (no seeker node), 0x11 (no target node or blocked
    // target), 0x21 (search overflow), 1 (no path).
    uint32_t m_eState;
    uint16_t m_ui16GraphPath[200];    // +0x038 the graph nodes of the route, start first
    uint32_t m_ui32GraphPathSize;     // +0x1c8 0
    uint8_t m_aCellGridPath[500][2];  // +0x1cc XXL2 CAstarCellIndex[500] (x, z): the current node's waypoints
    uint32_t m_ui32GridPathSize;      // +0x5b4 0
    uint32_t m_ui32GraphPathIndex;    // +0x5b8 0 the current graph node in m_ui16GraphPath
    uint32_t m_ui32GridPathIndex;     // +0x5bc 0 the next waypoint in m_aCellGridPath
    CVector3 m_vEndGridPosition;      // +0x5c0 the end of the current node's leg (the next portal or the target)
    uint32_t m_ui32PortalAction;      // +0x5cc the portal's type byte (low byte of its m_baTypesAndFlags)
    CVector3 m_vPortalArrival;        // +0x5d0 where the next node's leg starts
    CVector3 m_vCurrentSeekPoint;     // +0x5dc the last waypoint handed out
};
DOTD_ASSERT_OFFSET(CPFPathSlot, m_eState, 0x34);
DOTD_ASSERT_OFFSET(CPFPathSlot, m_aCellGridPath, 0x1cc);
DOTD_ASSERT_OFFSET(CPFPathSlot, m_vPortalArrival, 0x5d0);
DOTD_ASSERT_SIZE(CPFPathSlot, 0x5e8);
DOTD_ASSERT_OFFSET(CPFPathSlot, m_ui32GraphPathSize, 0x1c8);
DOTD_ASSERT_OFFSET(CPFPathSlot, m_ui32GridPathSize, 0x5b4);

class CKSrvPathFinding : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x6)
    DOTD_DECLARE_FACTORIES(CKSrvPathFinding)

    CKSrvPathFinding();  // 0x001e4ad8 (Ghidra CKSrvPathFinding_ConstructBase_maybe)
    ~CKSrvPathFinding() override {}

    // vt+0x10 0x001e4a90 CKSrvPathFinding_Destroy (Ghidra; row name ClearReferences): IKService's part (0x1a5b8,
    // empty), then the graph cleared (CPFGraph::Clear 0x1f0bd0).
    void Destroy() override { m_Graph.Clear(); }
    int32_t MessageProc(uint16_t /*message*/, void* /*data*/) override { return 1; }  // vt+0x1c 0x1e3c58
    // vt+0x24 0x001e4da8 CKSrvPathFinding_RecursiveRegistration (row name LevelReset): type 0 only: the service
    // registered with the saving manager, the graph's (KStub_Return1_1f0bc8: nothing), then each graph node's.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001e6738 CKSrvPathFinding_Load
    void Start() override {}                            // vt+0x50 0x1e3c88 (empty in the original)
    // vt+0x38 0x001e4ea8 CKSrvPathFinding_SetDefaultState: every graph node's transitions back to their default
    // enabled bit (CKPFGraphTransition_ResetEnabledToDefault_maybe 0x1f0600).
    void SetDefaultState(int32_t flag) override;
    void Restart() override;                            // vt+0x54 0x1e4880 CKSrvPathFinding_ReinitRuntime
    void Stop() override;                               // vt+0x68 0x1e4820 CKSrvPathFinding_ReleaseAllQueries_maybe
    void Pause() override {}                            // vt+0x70 0x1e3c90 (empty in the original)
    void Resume() override {}                           // vt+0x78 0x1e3c98 (empty in the original)
    // vt+0x7c 0x001e98f8 CKSrvPathFinding_Update: with a running clock (state 0), each query slot in use is
    // processed (ProcessRequest), in slot order.
    void Update(IKTime* time) override;
    int32_t InitializeService() override;               // vt+0x94 0x1e4908 CKSrvPathFinding_Init
    void DestroyService() override;                     // vt+0x98 0x1e3ce8 CKSrvPathFinding_Shutdown

    // 0x001e5ca0 NavSectors_FindSectorForPoint_maybe: finds the graph node holding the point (first the node of
    // the point's own hint, then the targets of its transitions, then the quadtree), and stores the included box id
    // there in the hint. 1 when found, else the hint becomes 0xffff and 0 is returned.
    uint32_t FindSectorForPoint(CPFPoint* point);
    // 0x001e62e0 NavSectors_SnapPointToGround_maybe: the point's node (found first when the hint is 0xffff); the ground
    // probed (GroundProbePoints, reach 0 / height 0, masks 1 and 8, `contact` copied as the in-out contact) from the
    // point at the node box's top; with a contact (status 0) whose world point is not below the box's bottom, the
    // point's height becomes the ground's and 1 is returned; else 0 and the point is left.
    int32_t SnapPointToGround(CPFPoint* point, const struct CGroundContactDatasInOut* contact);
    // 0x001e64c8 NavSectors_SnapPointToGroundThunk_maybe: SnapPointToGround with a fresh contact (the constructor's
    // defaults). Callers: CKHkBridgeBase_9c2_maybe_AttachHero_maybe 0x3fb6f0 / _ReleaseHeroesOffBridge_maybe 0x3fd760
    // (k2000/misc/CKHkBridgeBase.cpp, not ported yet).
    uint8_t SnapPointToGround(CPFPoint* point);
    // 0x001e5f60 CKSrvPathFinding_SetBoxBlocked_maybe: the box `min`..`max` blocked (or freed) in graph node `node`'s grid
    // (when the node exists), then in the nodes holding its corners (min; max; min.x, min.y, max.z; max.x, max.y, min.z;
    // each looked up from `node`), each node once. Returns 1.
    uint32_t SetBoxBlocked(uint16_t node, const CVector3* min, const CVector3* max, uint8_t blocked);
    // 0x001e5148 NavSectors_PointToCell_maybe: the cell (x, z) of the point in its hint's node (truncated, the last
    // column / row for a point on the far side) and the point's offsets inside that cell (world units, x and z).
    void PointToCell(const CPFPoint* point, float* fracX, float* fracZ, uint8_t* cell) const;
    // 0x001e42d0 NavSectors_IsPointWalkable_maybe: whether a character of the given type fits at the point (whose
    // hint names its node): the cell must be open in the walkability palette of the character's mode, a portal
    // the character may use covering the point (widened by the cell's half size minus the character's radius)
    // makes it walkable at once, else the neighbouring cells the radius reaches into must be open too (and, for a
    // blocked diagonal, the corner's distance to the point must clear the radius).
    uint32_t IsPointWalkable(const CPFPoint* point, const CPFCharacter* character);
    // 0x001e9198 CKSrvPathFinding_HasSectorRoute_maybe: with both points in a node, the first free query slot runs a graph
    // search from `from` to `to` for `character` (Initialize, FindSectorRoute) and is released again: 1 when a route was
    // found (its length into `length` when given), 0 without a node, a free slot or a route.
    uint8_t HasSectorRoute(const CPFPoint* from, const CPFPoint* to, const CPFCharacter* character, int16_t* length);
    // 0x001e3e28 CKSrvPathFinding_GetTransitionBetween_maybe: the transition of graph node `from` that leads to node
    // `to`, or null.
    CKPFGraphTransition* GetTransitionBetween(uint16_t from, uint16_t to);
    // The unit's dead helpers (no pointer to their descriptors; C2.8 port-rest R01).
    // 0x001e5240 NavSectors_SnapPointToCellCenter_maybe: the centre of the point's cell in its node's grid.
    void SnapPointToCellCenter(const CPFPoint* point, CVector3* out) const;
    // 0x001e55f8 CKSrvPathFinding_IsTransitionEnabledBetween_maybe: the enabled bit of the transition from -> to (0: none).
    uint32_t IsTransitionEnabledBetween(uint16_t from, uint16_t to) const;
    // 0x001e59c8 NavSectors_RelocatePoint_maybe: the point's node found again (hint, its transitions, then every node).
    uint32_t RelocatePoint(CPFPoint* point);
    // 0x001e5ef8 CKSrvPathFinding_RefreshQueryEndpointSectors_maybe: the slot's seeker and target nodes found again.
    uint32_t RefreshQueryEndpointSectors(uint32_t slot);
    // 0x001e6de0 CKSrvPathFinding_GetTransitionBetweenPoints_maybe: the transition between the two points' nodes.
    CKPFGraphTransition* GetTransitionBetweenPoints(const CPFPoint* from, const CPFPoint* to) const;
    // 0x001e3ea8 CKSrvPathFinding_InitializeSearchPFGrid (XXL2 InitializeSearchPFGrid): the leg of the slot's
    // current graph node, into out[0] (start: the seeker, or the last portal's arrival point) and out[1] (end: the
    // target on the last node, else the portal to the next node: the departure box's point nearest the start for a
    // simple transition, else the centre of the nearest portal the character's type may use); also stores the end
    // (m_vEndGridPosition), the next node's start (m_vPortalArrival) and the portal's type byte.
    void ComputeSegmentEndpoints(uint8_t slot, CVector3* out);
    // 0x001e4f70 CKSrvPathFinding_IsValidOrFindNearestPointInTheBox: 1 when the point is inside the box of the node its hint names
    // (0 for no hint); else the point is moved to the box's nearest point pushed 0.001 further in (its height kept
    // when within the box's), and 0 returned.
    uint8_t ClampPointToSector(CPFPoint* point);
    // 0x001e52c8 CKSrvPathFinding_GetNextPoint (XXL2 GetNextPoint): the query's next waypoint into
    // `out` (and m_vCurrentSeekPoint) while the route is followed: the next grid waypoint, else the leg's end (state
    // 0x42, the next graph node into *nextNode), else the target (0x82). Returns the slot's state (1 for a free slot;
    // 0x104 after the portal state 0x40; failures and waiting states as they are; 0x80: `out` is the last point).
    uint32_t GetNextQueryWaypoint(uint8_t slot, uint16_t* nextNode, CVector3* out);
    // 0x001e5680 CKSrvPathFinding_FindNearestPointInBox (XXL2 FindNearestPointInBox): the point clamped into the
    // nearest graph node's box (squared distance, the first of equals), that node as the hint; with no node the point
    // itself.
    CPFPoint ClampToNearestSector(const CPFPoint* point);
    // 0x001e5920 CKSrvPathFinding_AskForPath (XXL2 AskForPath): the first free query slot initialised
    // for the query (CPFPathSlot::Initialize), its index; -1 when all 20 are in use.
    int8_t AcquirePathQuery(const CPFPoint* seeker, const CPFPoint* target, const CPFCharacter* character);
    // 0x001e67e8 CKSrvPathFinding_IsPathWalkableInSameGrid (XXL2 IsPathWalkableInSameGrid): both points inside their
    // nodes' boxes and walkable (IsPointWalkable), and one node's box holding the other point: the straight segment
    // in that node's grid is walkable (`thin` != 0: the line itself, IsSegmentWalkable; else the band of the
    // character's radius, IsWideSegmentWalkable; neither strict). The grids' masks and the walkability mode are set
    // for the character.
    uint8_t IsDirectPathWalkable(const CPFPoint* from, const CPFPoint* to, const CPFCharacter* character,
                                 uint8_t thin);
    // 0x001e6e68 CKSrvPathFinding_IsPathWalkableOnTwoGrids (XXL2 IsPathWalkableOnTwoGrids): the two points
    // are in neighbouring nodes joined by an open simple transition the character may take, the segment crosses the
    // portal's edge (Seg2D_IntersectSegment), and the two halves (each stopping the character's radius + 0.001 short
    // of the crossing) are walkable in their nodes (IsDirectPathWalkable, wide).
    uint8_t IsDirectPathAcrossTransition(const CPFPoint* from, const CPFPoint* to, const CPFCharacter* character);
    // 0x001e71e0 CKSrvPathFinding_SearchPFGraph (XXL2 SearchPFGraph): the A* over the graph nodes (each
    // transition costs 2, no heuristic) from the slot's seeker node to its target node, for the slot's character
    // (copied into m_Graph.m_Character). Found: the route stored (SetGraphPath), {2, length}; no path or a route
    // longer than the graph search's limit: {1, -1}; overflow: {0x21, -1}; no seeker / target node: {9 / 0x11, -1}.
    PFSearchResult FindSectorRoute(uint8_t slot);
    // 0x001e92f8 CKSrvPathFinding_SearchPFGrid (XXL2 SearchPFGrid): the current leg's grid path: the A*
    // over the cells of the current graph node (FindPathInGrid) from the leg's start cell to its end cell, reduced
    // to waypoints for the character's radius (FindWideSegmentWaypoint) into the slot's grid path. {2, waypoints};
    // {1, 0} no path; {0x21, overflow}; {9, 0} / {0x11, 0} the start / end cell outside the grid or closed.
    PFSearchResult SolveSectorSegment(uint8_t slot);
    // 0x001e9600 CKSrvPathFinding_UpdatePath (XXL2 UpdatePath): one step of the slot's query: state 0x200
    // the graph route (for a character with bit 0 set the seeker and target must still be inside their nodes' boxes,
    // else 9 / 0x11; without it their nodes are looked up again), a route found becomes 0x104; state 0x100 the
    // current leg's grid path.
    void ProcessRequest(uint8_t slot);
    CPFGraph m_Graph;                 // +0x0c
    TAstar m_AstarGraph;              // +0x48
    TAstar m_AstarGrid;               // +0x8c
    CPFPathSlot m_aPathStock[20];     // +0xd0
};
DOTD_ASSERT_SIZE(CKSrvPathFinding, 0x76f0);
DOTD_ASSERT_OFFSET(CKSrvPathFinding, m_Graph, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvPathFinding, m_AstarGraph, 0x48);
DOTD_ASSERT_OFFSET(CKSrvPathFinding, m_AstarGrid, 0x8c);
DOTD_ASSERT_OFFSET(CKSrvPathFinding, m_aPathStock, 0xd0);
