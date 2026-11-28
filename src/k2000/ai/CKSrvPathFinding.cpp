// CKSrvPathFinding.cpp - reconstructed original translation unit 0x1e3c08-0x1e9ee0 (GAME_TOC1, main_toc1), 55 functions, 49 live.
// Primary owner: CKSrvPathFinding (not a registered class)
// Other owners: NavSectors (9), PathFindingParams (2), PathFinding (1), RegisterCKSrvPathFindingClass (1), CKSrvPathFinding_Update (1), PFPathQuery (1), PathRequest (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1e3c08  CKSrvPathFinding_Destroy  (the Delete factory: DOTD_DECLARE_FACTORIES(CKSrvPathFinding))
//   [x] 0x1e3c58  CKSrvPathFinding_vf1C  (MessageProc, vt+0x1c)
//   [ ] 0x1e3c60  PathFinding_InitCellSizeConstants_maybe  [dead]
//   [x] 0x1e3c88  CKSrvPathFinding_vf50  (Start, vt+0x50, empty)
//   [x] 0x1e3c90  CKSrvPathFinding_vf70  (Pause, vt+0x70, empty)
//   [x] 0x1e3c98  CKSrvPathFinding_vf78  (Resume, vt+0x78, empty)
//   [ ] 0x1e3ca0  CKSrvPathFinding_FindFreeQuerySlot_maybe  [dead]
//   [x] 0x1e3ce8  CKSrvPathFinding_Shutdown
//   [ ] 0x1e3da0  RegisterCKSrvPathFindingClass
//   [ ] 0x1e3e18  _GLOBAL__I_1e3e18
//   [x] 0x1e3e28  CKSrvPathFinding_GetTransitionBetween_maybe
//   [x] 0x1e3ea8  CKSrvPathFinding_InitializeSearchPFGrid
//   [x] 0x1e42d0  NavSectors_IsPointWalkable_maybe
//   [x] 0x1e4820  CKSrvPathFinding_ReleaseAllQueries_maybe
//   [x] 0x1e4880  CKSrvPathFinding_ReinitRuntime
//   [x] 0x1e48e0  CKSrvPathFinding_PostLoad  (= the inherited slot)
//   [x] 0x1e4908  CKSrvPathFinding_Init
//   [x] 0x1e4a90  CKSrvPathFinding_ClearReferences  (Destroy, vt+0x10)
//   [x] 0x1e4ad8  CKSrvPathFinding_ConstructBase_maybe
//   [x] 0x1e4c28  CKSrvPathFinding_DestroyArray  (the DeleteArray factory: DOTD_DECLARE_FACTORIES(CKSrvPathFinding))
//   [x] 0x1e4cc8  CKSrvPathFinding_CreateArray
//   [x] 0x1e4d68  CKSrvPathFinding_Create
//   [x] 0x1e4da8  CKSrvPathFinding_LevelReset  (RecursiveRegistration, vt+0x24)
//   [x] 0x1e4ea8  CKSrvPathFinding_ResetToInitialState_maybe
//   [x] 0x1e4f70  CKSrvPathFinding_IsValidOrFindNearestPointInTheBox
//   [x] 0x1e5148  NavSectors_PointToCell_maybe
//   [x] 0x1e5240  NavSectors_SnapPointToCellCenter_maybe  [dead: no pointer to its descriptor 0xb76360, no call]  (CKSrvPathFinding::SnapPointToCellCenter)
//   [x] 0x1e52c8  CKSrvPathFinding_GetNextPoint
//   [ ] 0x1e5570  FUN_001e5570  [dead]
//   [x] 0x1e55f8  CKSrvPathFinding_IsTransitionEnabledBetween_maybe  [dead: no pointer to its descriptor 0xb76390, no call]  (CKSrvPathFinding::IsTransitionEnabledBetween)
//   [x] 0x1e5680  CKSrvPathFinding_FindNearestPointInBox
//   [ ] 0x1e5880  CKSrvPathFinding_Save
//   [x] 0x1e5920  CKSrvPathFinding_AskForPath
//   [x] 0x1e59c8  NavSectors_RelocatePoint_maybe  [dead: no pointer to its descriptor 0xb763d0, no call]  (CKSrvPathFinding::RelocatePoint)
//   [x] 0x1e5ca0  NavSectors_FindSectorForPoint_maybe
//   [x] 0x1e5ef8  CKSrvPathFinding_RefreshQueryEndpointSectors_maybe  [dead: no pointer to its descriptor 0xb763e0, no call]  (CKSrvPathFinding::RefreshQueryEndpointSectors)
//   [x] 0x1e5f60  CKSrvPathFinding_SetBoxBlocked_maybe
//   [x] 0x1e62e0  NavSectors_SnapPointToGround_maybe  (CKSrvPathFinding::SnapPointToGround)
//   [x] 0x1e64c8  NavSectors_SnapPointToGroundThunk_maybe  (CKSrvPathFinding::SnapPointToGround(point))
//   [ ] 0x1e6510  CKSrvPathFinding_GetQueryCurrentSegment_maybe  [dead]
//   [x] 0x1e6738  CKSrvPathFinding_Load
//   [x] 0x1e67e8  CKSrvPathFinding_IsPathWalkableInSameGrid
//   [ ] 0x1e6c90  CKSrvPathFinding_ConstructBase_2_maybe  [dead]
//   [x] 0x1e6de0  CKSrvPathFinding_GetTransitionBetweenPoints_maybe  [dead: no pointer to its descriptor 0xb76428, no call]  (CKSrvPathFinding::GetTransitionBetweenPoints)
//   [x] 0x1e6e68  CKSrvPathFinding_IsPathWalkableOnTwoGrids
//   [x] 0x1e71e0  CKSrvPathFinding_SearchPFGraph
//   [x] 0x1e9198  CKSrvPathFinding_HasSectorRoute_maybe
//   [x] 0x1e92f8  CKSrvPathFinding_SearchPFGrid
//   [x] 0x1e9600  CKSrvPathFinding_UpdatePath
//   [x] 0x1e98f8  CKSrvPathFinding_Update
//   [ ] 0x1e9988  CKSrvPathFinding_AStarWithinSector_maybe  [dead]
//   [x] 0x1e9b78  PathFindingParams_Load
//   [ ] 0x1e9ce0  PathFindingParams_Save
//   [x] 0x1e9e28  PFPathQuery_Release_maybe
//   [x] 0x1e9e60  CPFPathSlot_SetGraphPath
//
//   [ ] 0x9ae008  CKSrvPathFinding_IsKindOf  [inline]
//   [ ] 0x9ae040  CKSrvPathFinding_GetClassGroup  [inline]
//   [ ] 0x9ae048  CKSrvPathFinding_GetClassId  [inline]
//   [ ] 0x9ae050  CKSrvPathFinding_Destructor  [inline]
//   [ ] 0x9ae1f8  CKSrvPathFinding_DeletingDestructor  [inline]
//   [x] 0x9ae3a8  TAstar_CPFGrid_FindPath  [inline]
#include "k2000/ai/CKSrvPathFinding.h"

#include <cmath>
#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "crt/ppc_ops.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/math/CBBox.h"
#include "k2000/math/CVector2.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/NavGrid.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/system/IKTime.h"

// 0x00c4025c (static values 1.0, 0.5, 1.0 in the EBOOT's data).
PFGridScale_maybe g_pfGridScale = {1.0f, 0.5f, 1.0f};

// 0x001e4ad8 (Ghidra CKSrvPathFinding_ConstructBase_maybe). The members' constructors run first here (the
// original builds the quadtree and the path slots in between); the stores are the original's.
CKSrvPathFinding::CKSrvPathFinding() {
    m_Graph.m_Character.m_bits = 0;
    m_Graph.m_Character.m_bits = (m_Graph.m_Character.m_bits & 0xfffff800u) | 0x407u;
    m_Graph.m_Character.m_fMaxStepHeight = 0x1.99999ap-3f;  // 0.2 (0x3e4ccccd)
    m_Graph.m_Character.m_fMaxStepRise = 1.0f;
    m_Graph.m_Character.m_fRadius = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;

    m_AstarGraph.SearchList = nullptr;
    m_AstarGraph.m_ui32NumberOfZone = 0;
    m_AstarGraph.m_ui16ResearchZoneSize = 0;
    m_AstarGraph.m_ui16MaxPathSize = 0;
    m_AstarGraph.m_fMultGCoef = 1.0f;
    m_AstarGraph.NodeList = nullptr;
    m_AstarGraph.m_ui16NodeListSize = 0;
    m_AstarGrid.SearchList = nullptr;
    m_AstarGrid.m_fMultGCoef = 1.0f;
    m_AstarGrid.m_ui32NumberOfZone = 0;
    m_AstarGrid.m_ui16ResearchZoneSize = 0;
    m_AstarGrid.m_ui16MaxPathSize = 0;
    m_AstarGrid.NodeList = nullptr;
    m_AstarGrid.m_ui16NodeListSize = 0;

    m_ui32Priority = 0x8c;
    Engine_SetSrvPathFinding(this);
}

// 0x001e4908 CKSrvPathFinding_Init (vt+0x94): sizes and allocates the two searches. The grid search (+0x8c) first:
// 10000 zones, 2500 / 1000 sizes, a 0.1 cost coefficient, 0x15fb4 and 20000 byte blocks; then the graph search (+0x48):
// 500 zones, 500 / 200 sizes, coefficient 1.0, 0x4e48 and 1000 byte blocks. Each open list is initialised as an
// empty ordered tree (a sentinel node and an end node inside the list itself). The node blocks are 2501 grid / 501
// graph tree-path nodes (0x15fb4 / 0x4e48 bytes on the PS3).
int32_t CKSrvPathFinding::InitializeService() {
    m_AstarGrid.m_ui32NumberOfZone = 10000;
    m_AstarGrid.m_fMultGCoef = 0x1.99999ap-4f;  // 0.1 (0x3dcccccd)
    m_AstarGrid.m_ui16ResearchZoneSize = 0x9c4;
    m_AstarGrid.m_ui16MaxPathSize = 1000;
    m_AstarGrid.NodeList = Mem_AllocAligned16(static_cast<uint32_t>(2501 * sizeof(CAstarGridPath)));
    m_AstarGrid.SearchList = static_cast<uint16_t*>(Mem_AllocAligned16(20000));
    {
        TAstarOpenList& list = m_AstarGrid.OpenList;
        TRBTree<CAstarGridPath>::InitializeList(list);  // m_pTSentinel (the sentinel node - 4 on the PS3)
        list.m_NodeSentinel.m_tParent = nullptr;
        list.m_NodeSentinel.m_tRight = nullptr;
        list.m_NodeSentinel.m_tLeft = nullptr;
        list.m_NodeSentinel.m_eColour = 1;
        // m_pTHead (the header node - 4) set by InitializeList; the header's parent the sentinel, left / right itself.
        list.m_NodeHead.m_tParent = list.m_pTSentinel;
        list.m_NodeHead.m_tRight = list.m_pTHead;
        list.m_NodeHead.m_tLeft = list.m_pTHead;
        list.m_NodeHead.m_eColour = 0;
    }

    m_AstarGraph.m_ui32NumberOfZone = 500;
    m_AstarGraph.m_ui16MaxPathSize = 200;
    m_AstarGraph.m_ui16ResearchZoneSize = 500;
    m_AstarGraph.m_fMultGCoef = 1.0f;
    m_AstarGraph.NodeList = Mem_AllocAligned16(static_cast<uint32_t>(501 * sizeof(CAstarGraphPath)));
    m_AstarGraph.SearchList = static_cast<uint16_t*>(Mem_AllocAligned16(1000));
    {
        TAstarOpenList& list = m_AstarGraph.OpenList;
        TRBTree<CAstarGraphPath>::InitializeList(list);  // the sentinel node - 8 / the header node - 8 on the PS3
        list.m_NodeSentinel.m_tParent = nullptr;
        list.m_NodeSentinel.m_tRight = nullptr;
        list.m_NodeSentinel.m_tLeft = nullptr;
        list.m_NodeSentinel.m_eColour = 1;
        list.m_NodeHead.m_tParent = list.m_pTSentinel;
        list.m_NodeHead.m_tRight = list.m_pTHead;
        list.m_NodeHead.m_tLeft = list.m_pTHead;
        list.m_NodeHead.m_eColour = 0;
    }
    return 1;
}

// 0x001e3ce8 CKSrvPathFinding_Shutdown (vt+0x98): frees the four search blocks.
void CKSrvPathFinding::DestroyService() {
    if (m_AstarGraph.NodeList != nullptr) {
        Mem_FreeAligned16(m_AstarGraph.NodeList);
        m_AstarGraph.NodeList = nullptr;
    }
    if (m_AstarGraph.SearchList != nullptr) {
        Mem_FreeAligned16(m_AstarGraph.SearchList);
        m_AstarGraph.SearchList = nullptr;
    }
    if (m_AstarGrid.NodeList != nullptr) {
        Mem_FreeAligned16(m_AstarGrid.NodeList);
        m_AstarGrid.NodeList = nullptr;
    }
    if (m_AstarGrid.SearchList != nullptr) {
        Mem_FreeAligned16(m_AstarGrid.SearchList);
        m_AstarGrid.SearchList = nullptr;
    }
}

// 0x001e4da8 CKSrvPathFinding_RecursiveRegistration
void CKSrvPathFinding::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    // KStub_Return1_1f0bc8(&m_Graph, 0): the graph's own registration does nothing.
    for (uint32_t i = 0; i < m_Graph.m_ui32GraphNodesSize; ++i) {
        m_Graph.m_apGraphNodes[i & 0xffff]->RecursiveRegistration(0);  // the index as a u16 (rlwinm)
    }
}

// 0x001e62e0 NavSectors_SnapPointToGround_maybe
int32_t CKSrvPathFinding::SnapPointToGround(CPFPoint* point, const CGroundContactDatasInOut* contact) {
    if (static_cast<int16_t>(point->m_i16GraphNodeIndex) == -1) FindSectorForPoint(point);
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[point->m_i16GraphNodeIndex]);
    const CBBox& box = node->m_Sector.m_box;
    CGroundContactDatasIn in;
    in.m_fDeltaMax = 0.0f;
    in.m_fObjectHeight = 0.0f;
    in.m_MasksOfGrdForTest[0] = 1;
    in.m_MasksOfGrdForTest[1] = 8;
    CGroundContactDatasInOut inOut;  // the caller's contact, copied member by member (status 3 first, then its own)
    CopyGroundContact(inOut, *contact);
    CVector3 probe;
    probe.x = point->m_position.x;
    probe.y = box.m_sup.y;
    probe.z = point->m_position.z;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &inOut, &probe.x, 1);  // 0x196540
    if (inOut.m_eContactStatus != 0) return 0;
    GroundContact_GetWorldPoint(&inOut, &probe);  // 0x1a70e0
    if (probe.y < box.m_inf.y) return 0;
    point->m_position.x = probe.x;
    point->m_position.z = probe.z;
    point->m_position.y = probe.y;
    return 1;
}

// 0x001e64c8 NavSectors_SnapPointToGroundThunk_maybe
uint8_t CKSrvPathFinding::SnapPointToGround(CPFPoint* point) {
    const CGroundContactDatasInOut contact;
    return static_cast<uint8_t>(SnapPointToGround(point, &contact));
}

// 0x001e6738 CKSrvPathFinding_Load
int32_t CKSrvPathFinding::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_Graph.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &g_pfGridScale.m_cellSize);
    const float cellSize = g_pfGridScale.m_cellSize;
    g_pfGridScale.m_invCellSize = 1.0f / cellSize;
    g_pfGridScale.m_halfCellSize = cellSize * 0.5f;
    return 1;
}

// 0x001e9b78 PathFindingParams_Load (CPFCharacter; used by CKPFGraphTransition_Load).
void CPFCharacter::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_bits);
    ReadF32LE(file, &m_fRadius);
    ReadF32LE(file, &m_fMaxStepHeight);
    ReadF32LE(file, &m_fMaxStepRise);
}

// 0x001e9e28 PFPathQuery_Release_maybe
void CPFPathSlot::Release() {
    m_Character.m_bits &= 0xfffff800u;
    m_ui32GridPathIndex = 0;
    m_bIsFree = 1;
    m_eState = 0;
    m_ui32GraphPathSize = 0;
    m_ui32GridPathSize = 0;
    m_ui32GraphPathIndex = 0;
}

namespace {
// Whether a transition may be taken by a character (0x001f0648 NavSectorFlags_AllowsAgent_maybe): the
// transition's allowed-mode byte (bits 3-10 of its word, 0x80 = anything) shares a bit with the character's modes
// (bits 3-10), and the low three bits share one, and the character's size fits the transition's.
bool AllowsAgent(const CKPFGraphTransition* transition, const CPFCharacter* character) {
    const uint32_t allowed = (transition->m_AllowedChar.m_bits >> 3) & 0xff;
    const uint32_t bits = character->m_bits;
    if (allowed != 0x80 && (allowed & (bits >> 3)) == 0) return false;
    if (((transition->m_AllowedChar.m_bits & bits) & 7) == 0) return false;
    return character->m_fRadius <= transition->m_AllowedChar.m_fRadius;
}

// Whether the palette entry for the flags is blocked (low seven bits all set).
bool IsBlocked(uint8_t palette) { return static_cast<uint8_t>(palette | 0x7f) == palette || palette == 0x7f; }
}  // namespace

// 0x001e9198 CKSrvPathFinding_HasSectorRoute_maybe
uint8_t CKSrvPathFinding::HasSectorRoute(const CPFPoint* from, const CPFPoint* to, const CPFCharacter* character,
                                         int16_t* length) {
    if (static_cast<int16_t>(from->m_i16GraphNodeIndex) == -1 || static_cast<int16_t>(to->m_i16GraphNodeIndex) == -1) return 0;
    for (uint8_t slot = 0; slot < 20; ++slot) {
        if (m_aPathStock[slot].m_bIsFree == 0) continue;
        m_aPathStock[slot].Initialize(from, to, character);  // 0x001e9ee0
        const PFSearchResult result = FindSectorRoute(slot);  // 0x001e71e0
        uint8_t found = 0;
        if ((result.m_eState & 2u) != 0) {
            found = 1;
            if (length != nullptr) *length = result.m_i16Value;
        }
        m_aPathStock[slot].Release();  // 0x001e9e28
        return found;
    }
    return 0;
}

// 0x001e5148 NavSectors_PointToCell_maybe
void CKSrvPathFinding::PointToCell(const CPFPoint* point, float* fracX, float* fracZ, uint8_t* cell) const {
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[point->m_i16GraphNodeIndex]);
    const CPFSector& sector = node->m_Sector;
    const float x = point->m_position.x - sector.m_box.m_inf.x;
    const float z = point->m_position.z - sector.m_box.m_inf.z;
    uint8_t cellX = static_cast<uint8_t>(ppc::fctiwz(x * g_pfGridScale.m_invCellSize));
    uint8_t cellZ = static_cast<uint8_t>(ppc::fctiwz(z * g_pfGridScale.m_invCellSize));
    if (sector.m_grid.m_width == cellX) cellX = static_cast<uint8_t>(sector.m_grid.m_width - 1);
    if (sector.m_grid.m_height == cellZ) cellZ = static_cast<uint8_t>(sector.m_grid.m_height - 1);
    *fracX = x - static_cast<float>(cellX) * g_pfGridScale.m_cellSize;
    *fracZ = z - static_cast<float>(cellZ) * g_pfGridScale.m_cellSize;
    cell[1] = cellZ;
    cell[0] = cellX;
}

// 0x001e5f60 CKSrvPathFinding_SetBoxBlocked_maybe. The corner nodes are compared as signed halfwords; a corner's node is not
// checked against the node count.
uint32_t CKSrvPathFinding::SetBoxBlocked(uint16_t node, const CVector3* min, const CVector3* max, uint8_t blocked) {
    const auto block = [&](uint16_t index) {
        static_cast<CKPFGraphNode*>(m_Graph.m_apGraphNodes[index])->m_Sector.SetBoxBlocked(min, max, blocked);  // 0x001ed3c0
    };
    if (m_Graph.m_ui32GraphNodesSize > node) block(node);
    int16_t ids[4] = {-1, -1, -1, -1};
    const int16_t own = static_cast<int16_t>(node);
    const CVector3 corners[4] = {{min->x, min->y, min->z}, {max->x, max->y, max->z}, {min->x, min->y, max->z},
                                 {max->x, max->y, min->z}};
    for (int k = 0; k < 4; ++k) {
        CPFPoint point;
        point.m_position = corners[k];
        point.m_i16GraphNodeIndex = node;
        if ((FindSectorForPoint(&point) & 0xff) == 0) continue;  // 0x001e5ca0
        const int16_t id = static_cast<int16_t>(point.m_i16GraphNodeIndex);
        ids[k] = id;
        if (id == own) continue;
        bool seen = false;
        for (int j = 0; j < k; ++j) seen = seen || ids[j] == id;
        if (!seen) block(static_cast<uint16_t>(id));
    }
    return 1;
}

// 0x001e5ca0 NavSectors_FindSectorForPoint_maybe
uint32_t CKSrvPathFinding::FindSectorForPoint(CPFPoint* point) {
    IKSerializable** nodes = m_Graph.m_apGraphNodes;
    const float x = point->m_position.x;
    const float y = point->m_position.y;
    const float z = point->m_position.z;
    uint32_t index = 0;
    bool found = false;
    if (static_cast<int16_t>(point->m_i16GraphNodeIndex) >= 0) {
        const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(nodes[point->m_i16GraphNodeIndex]);
        const CBBox& box = node->m_Sector.m_box;
        if (box.m_inf.x <= x && x <= box.m_sup.x && box.m_inf.z <= z && z <= box.m_sup.z && box.m_inf.y <= y &&
            y <= box.m_sup.y) {
            index = point->m_i16GraphNodeIndex;
            found = true;
        } else {
            for (uint32_t i = 0; i < node->m_ui16TransitionSize; ++i) {
                const CKPFGraphNode* target = static_cast<const CKPFGraphNode*>(node->m_ppTransition[i]->m_pNode);
                const CBBox& tbox = target->m_Sector.m_box;
                if (!(x < tbox.m_inf.x || tbox.m_sup.x < x || z < tbox.m_inf.z || tbox.m_sup.z < z || y < tbox.m_inf.y ||
                      tbox.m_sup.y < y)) {
                    index = target->m_ui16Node;
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found) {
        const uint16_t sector = m_Graph.m_quadTree.FindSector(&point->m_position.x, &m_Graph.m_apGraphNodes);
        if (sector == 0xffff) {
            point->m_i16GraphNodeIndex = 0xffff;
            return 0;
        }
        index = sector;
    }
    point->m_i16GraphNodeIndex = static_cast<const CKPFGraphNode*>(nodes[index])->FindBoxIdAtPoint(&point->m_position.x);
    return 1;
}

// 0x001e42d0 NavSectors_IsPointWalkable_maybe. The cell fractions are compared with the character's radius in
// cells (radius * the inverse cell size); `dx` / `dz` are -1, 0 or 1: the neighbouring cell column / row the
// radius reaches into.
uint32_t CKSrvPathFinding::IsPointWalkable(const CPFPoint* point, const CPFCharacter* character) {
    const float x = point->m_position.x;
    const float z = point->m_position.z;
    CKPFGraphNode* node = static_cast<CKPFGraphNode*>(m_Graph.m_apGraphNodes[point->m_i16GraphNodeIndex]);
    CPFGrid& grid = node->m_Sector.m_grid;
    const float radius = character->m_fRadius;
    const float margin = g_pfGridScale.m_halfCellSize - radius;
    PathFinding_SetWalkabilityMode(character->m_bits & 7);
    grid.m_ui8DynamicMask = (character->m_bits & 0x800) == 0 ? 0xf7 : 0xff;
    const float inv = g_pfGridScale.m_invCellSize;
    const float scaledX = inv * (x - node->m_Sector.m_box.m_inf.x);
    const float scaledZ = inv * (z - node->m_Sector.m_box.m_inf.z);
    int32_t cellX = ppc::fctiwz(scaledX);
    int32_t cellZ = ppc::fctiwz(scaledZ);
    if ((cellX & 0xff) == grid.m_width) cellX = cellX - 1;
    if ((cellZ & 0xff) == grid.m_height) cellZ = cellZ - 1;
    uint8_t cell[2] = {static_cast<uint8_t>(cellX), static_cast<uint8_t>(cellZ)};
    if (IsBlocked(g_pfGridPalette[grid.GetCellFlags(cell)])) return 0;
    // A portal the character may use that covers the point.
    for (uint32_t i = 0; i < node->m_ui16TransitionSize; ++i) {
        const CKPFGraphTransition* transition = node->m_ppTransition[i];
        const uint32_t flags = transition->m_baFlags;
        if ((flags & 1) != 0 || (flags & 4) == 0) continue;
        if (!AllowsAgent(transition, character)) continue;
        const CBBox& box = transition->m_aPortals[0].m_DepartureBox;
        if (box.m_inf.x - margin <= x && margin + box.m_sup.x >= x && box.m_inf.z - margin <= z &&
            margin + box.m_sup.z >= z) {
            return 1;
        }
    }
    // The fraction of the point inside its cell, and the cell clamped to the grid again (the original does it
    // in the 8-bit domain: the low byte of the cell index is what it compares).
    const float fracX = scaledX - static_cast<float>(cellX & 0xff);
    if (grid.m_width == (cellX & 0xff)) cellX = grid.m_width - 1;
    const float fracZ = scaledZ - static_cast<float>(cellZ & 0xff);
    if (grid.m_height == (cellZ & 0xff)) cellZ = grid.m_height - 1;
    const float radiusCells = radius * inv;
    int32_t dx;
    int32_t dz;
    if (radiusCells > fracX) {
        dx = -1;
        if ((cellX & 0xff) == 0) return 0;
    } else {
        dx = 0;
        if (1.0f - fracX < radiusCells) {
            if (static_cast<int32_t>(cellX & 0xff) >= static_cast<int32_t>(grid.m_width) - 1) return 0;
            dx = 1;
        }
    }
    if (radiusCells > fracZ) {
        dz = -1;
        if ((cellZ & 0xff) == 0) return 0;
    } else {
        dz = 0;
        if (1.0f - fracZ < radiusCells) {
            if (static_cast<int32_t>(cellZ & 0xff) >= static_cast<int32_t>(grid.m_height) - 1) return 0;
            dz = 1;
        }
    }
    if (dx == 0) {
        if (dz == 0) return 1;
        cell[0] = static_cast<uint8_t>(cellX);
        cell[1] = static_cast<uint8_t>(dz + cellZ);
        const uint8_t palette = g_pfGridPalette[grid.GetCellFlags(cell)];
        return static_cast<uint8_t>(palette | 0x7f) != palette ? 1u : 0u;
    }
    const uint8_t sideX = static_cast<uint8_t>(dx + cellX);
    cell[0] = sideX;
    cell[1] = static_cast<uint8_t>(cellZ);
    if (IsBlocked(g_pfGridPalette[grid.GetCellFlags(cell)])) return 0;
    if (dz == 0) return 1;
    const uint8_t sideZ = static_cast<uint8_t>(dz + cellZ);
    cell[0] = static_cast<uint8_t>(cellX);
    cell[1] = sideZ;
    if (IsBlocked(g_pfGridPalette[grid.GetCellFlags(cell)])) return 0;
    cell[0] = sideX;
    cell[1] = sideZ;
    if (!IsBlocked(g_pfGridPalette[grid.GetCellFlags(cell)])) return 1;
    // The diagonal cell is blocked: the point must be farther than the radius from that corner.
    const float cornerX = dx == -1 ? fracX : 1.0f - fracX;
    const float cornerZ = dz == -1 ? fracZ : 1.0f - fracZ;
    const float distSq = ppc::fmadds(cornerX, cornerX, cornerZ * cornerZ);
    return distSq <= radiusCells * radiusCells ? 0u : 1u;
}

// 0x001e3e28 CKSrvPathFinding_GetTransitionBetween_maybe
CKPFGraphTransition* CKSrvPathFinding::GetTransitionBetween(uint16_t from, uint16_t to) {
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[from]);
    const int32_t index = node->FindTransitionIndexTo(m_Graph.m_apGraphNodes[to]);  // 0x001efda0
    if (static_cast<int16_t>(index) < 0) return nullptr;
    return node->m_ppTransition[static_cast<uint16_t>(index)];
}

// 0x001e4ea8 CKSrvPathFinding_SetDefaultState (the node and transition indices are 16-bit in the original's loops).
void CKSrvPathFinding::SetDefaultState(int32_t /*flag*/) {
    for (uint32_t i = 0; i < m_Graph.m_ui32GraphNodesSize; ++i) {
        CKPFGraphNode* node = static_cast<CKPFGraphNode*>(m_Graph.m_apGraphNodes[i & 0xffffu]);
        for (uint32_t t = 0; t < node->m_ui16TransitionSize; ++t) {
            node->m_ppTransition[t & 0xffffu]->ResetEnabledToDefault();
        }
    }
}

// 0x001e4820 CKSrvPathFinding_ReleaseAllQueries_maybe (the service's Stop): all 20 query slots released.
void CKSrvPathFinding::Stop() {
    for (CPFPathSlot& slot : m_aPathStock) slot.Release();
}

// 0x001e4880 CKSrvPathFinding_ReinitRuntime (vt+0x54, CKSrvPathFinding_Restart): every path slot released, as Stop.
void CKSrvPathFinding::Restart() {
    for (CPFPathSlot& slot : m_aPathStock) slot.Release();  // 0x001e9e28
}

namespace {
// 0x00010690 Math_Sqrtf (fsqrts).
inline float MathSqrtf(float x) { return std::sqrt(x); }

inline CKPFGraphNode* GraphNode(const CPFGraph& graph, uint32_t index) {
    return static_cast<CKPFGraphNode*>(graph.m_apGraphNodes[index]);
}

// The original's inline box test of a point (x, then z, then y; each side inclusive).
inline bool BoxHoldsPoint(const CBBox& box, const CVector3& p) {
    return box.m_inf.x <= p.x && box.m_sup.x >= p.x && box.m_inf.z <= p.z && box.m_sup.z >= p.z &&
           box.m_inf.y <= p.y && box.m_sup.y >= p.y;
}
}  // namespace

// 0x001e3ea8 CKSrvPathFinding_InitializeSearchPFGrid
void CKSrvPathFinding::ComputeSegmentEndpoints(uint8_t slotIndex, CVector3* out) {
    CPFPathSlot& slot = m_aPathStock[slotIndex];
    const uint32_t index = slot.m_ui32GraphPathIndex;
    const CVector3& start = index == 0 ? slot.m_SeekerPosition.m_position : slot.m_vPortalArrival;
    out[0].x = start.x;
    out[0].y = start.y;
    out[0].z = start.z;
    if (slot.m_ui32GraphPathSize - 1 != index) {
        CKPFGraphNode* const from = GraphNode(m_Graph, slot.m_ui16GraphPath[index]);
        const int32_t found = from->FindTransitionIndexTo(GraphNode(m_Graph, slot.m_ui16GraphPath[index + 1]));
        CKPFGraphTransition* const transition = from->m_ppTransition[found & 0xffff];
        float ax;
        float ay;
        float az;
        uint32_t portalIndex = 0;
        if ((transition->m_baFlags & 1) == 0) {
            // A simple transition: the departure box's point nearest the start, the arrival on the box's far face.
            const CPFPortal& portal = transition->m_aPortals[0];
            AABB_ClampPoint(&portal.m_DepartureBox, &out[0], &out[1]);
            const CBBox& arrival = portal.m_ArrivalBox;
            switch ((portal.m_baTypesAndFlags >> 8) & 3) {
                case 1:
                    ax = arrival.m_inf.x;
                    ay = out[1].y;
                    az = out[1].z;
                    break;
                case 2:
                    az = arrival.m_sup.z;
                    ax = out[1].x;
                    ay = out[1].y;
                    break;
                case 3:
                    az = arrival.m_inf.z;
                    ax = out[1].x;
                    ay = out[1].y;
                    break;
                default:
                    ax = arrival.m_sup.x;
                    ay = out[1].y;
                    az = out[1].z;
                    break;
            }
        } else {
            // Portals: the nearest one (departure box centre to the start) the character's type may use.
            // BUG(original): with no portal the index is not set (no transition in the data has none).
            const uint32_t count = transition->m_ui32NbPortals;
            if (count != 0) {
                float best = -1.0f;
                const uint32_t types = (slot.m_Character.m_bits >> 3) & 0xff;
                for (uint32_t i = 0; i < count; ++i) {
                    const CPFPortal& portal = transition->m_aPortals[i];
                    const uint32_t allowed = portal.m_baTypesAndFlags & 0xff;
                    if (allowed != 0x80 && (allowed & types) != allowed) continue;
                    const CBBox& box = portal.m_DepartureBox;
                    const float dy = ppc::fmsubs(box.m_sup.y + box.m_inf.y, 0.5f, out[0].y);
                    const float dx = ppc::fmsubs(box.m_sup.x + box.m_inf.x, 0.5f, out[0].x);
                    const float dz = ppc::fmsubs(box.m_sup.z + box.m_inf.z, 0.5f, out[0].z);
                    const float distance = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
                    if (best < 0.0f || !(distance >= best)) {
                        best = distance;
                        portalIndex = i;
                    }
                }
            }
            const CPFPortal& portal = transition->m_aPortals[portalIndex];
            const CBBox& departure = portal.m_DepartureBox;
            out[1].x = (departure.m_sup.x + departure.m_inf.x) * 0.5f;
            out[1].y = (departure.m_sup.y + departure.m_inf.y) * 0.5f;
            out[1].z = (departure.m_sup.z + departure.m_inf.z) * 0.5f;
            const CBBox& arrival = portal.m_ArrivalBox;
            ax = (arrival.m_sup.x + arrival.m_inf.x) * 0.5f;
            ay = (arrival.m_sup.y + arrival.m_inf.y) * 0.5f;
            az = (arrival.m_sup.z + arrival.m_inf.z) * 0.5f;
        }
        slot.m_vPortalArrival.z = az;
        slot.m_vPortalArrival.y = ay;
        slot.m_vPortalArrival.x = ax;
        slot.m_ui32PortalAction = transition->m_aPortals[portalIndex].m_baTypesAndFlags & 0xff;
    } else {
        out[1].x = slot.m_TargetPosition.m_position.x;
        out[1].y = slot.m_TargetPosition.m_position.y;
        out[1].z = slot.m_TargetPosition.m_position.z;
    }
    slot.m_vEndGridPosition.z = out[1].z;
    slot.m_vEndGridPosition.x = out[1].x;
    slot.m_vEndGridPosition.y = out[1].y;
}

// 0x001e4f70 CKSrvPathFinding_IsValidOrFindNearestPointInTheBox
uint8_t CKSrvPathFinding::ClampPointToSector(CPFPoint* point) {
    if (static_cast<int16_t>(point->m_i16GraphNodeIndex) == -1) return 0;
    const CBBox& box = GraphNode(m_Graph, point->m_i16GraphNodeIndex)->m_Sector.m_box;
    if (BoxHoldsPoint(box, point->m_position)) return 1;
    CVector3 clamped;
    AABB_ClampPoint(&box, &point->m_position, &clamped);
    float dy = clamped.y - point->m_position.y;
    float dx = clamped.x - point->m_position.x;
    float dz = clamped.z - point->m_position.z;
    const float length = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        dz = dz * inv;
        dx = dx * inv;
        dy = dy * inv;
    }
    constexpr float kPush = 0.001f;  // 0x3a83126f
    float y = ppc::fmadds(dy, kPush, clamped.y);
    const float x = ppc::fmadds(dx, kPush, clamped.x);
    const float z = ppc::fmadds(dz, kPush, clamped.z);
    const float pointY = point->m_position.y;
    if (box.m_sup.y >= pointY && box.m_inf.y <= pointY) y = pointY;
    point->m_position.z = z;
    point->m_position.x = x;
    point->m_position.y = y;
    return 0;
}

// 0x001e52c8 CKSrvPathFinding_GetNextPoint
uint32_t CKSrvPathFinding::GetNextQueryWaypoint(uint8_t slotIndex, uint16_t* nextNode, CVector3* out) {
    CPFPathSlot& slot = m_aPathStock[slotIndex];
    if (slot.m_bIsFree != 0) return 1;
    const uint32_t state = slot.m_eState;
    if ((state & 1) != 0 || (state & 4) != 0) return state;
    if ((state & 0x80) != 0) {
        *out = slot.m_vCurrentSeekPoint;
        return state;
    }
    if ((state & 0x40) != 0) {
        slot.m_eState = 0x104;
        return 0x104;
    }
    const uint32_t gridIndex = slot.m_ui32GridPathIndex;
    const uint32_t graphIndex = slot.m_ui32GraphPathIndex;
    if ((gridIndex & 0xffff) < (slot.m_ui32GridPathSize & 0xffff)) {
        // The next waypoint of the current node's grid path.
        const uint8_t* const cell = slot.m_aCellGridPath[gridIndex & 0xffff];
        const uint8_t local[2] = {cell[0], cell[1]};
        GraphNode(m_Graph, slot.m_ui16GraphPath[graphIndex & 0xffff])->m_Sector.CellToWorldPos(local, out);
        slot.m_ui32GridPathIndex = (gridIndex + 1) & 0xffff;
    } else if (static_cast<int32_t>(graphIndex & 0xffff) <
               static_cast<int32_t>(slot.m_ui32GraphPathSize & 0xffff) - 1) {
        // The leg's end (the portal); the next graph node.
        const uint32_t next = (graphIndex + 1) & 0xffff;
        *out = slot.m_vEndGridPosition;
        slot.m_eState = 0x42;
        slot.m_ui32GridPathIndex = 1;
        slot.m_ui32GraphPathIndex = next;
        *nextNode = slot.m_ui16GraphPath[next];
    } else {
        // The target.
        *out = slot.m_TargetPosition.m_position;
        slot.m_eState = 0x82;
    }
    slot.m_vCurrentSeekPoint = *out;
    return slot.m_eState;
}

// 0x001e5680 CKSrvPathFinding_FindNearestPointInBox. The distances are squared (z, then x, then y fused).
CPFPoint CKSrvPathFinding::ClampToNearestSector(const CPFPoint* point) {
    CPFPoint result;
    const uint32_t count = m_Graph.m_ui32GraphNodesSize;
    if (count == 0) {
        result.m_position = point->m_position;
        result.m_i16GraphNodeIndex = point->m_i16GraphNodeIndex;
        return result;
    }
    CVector3 best;
    AABB_ClampPoint(&GraphNode(m_Graph, 0)->m_Sector.m_box, &point->m_position, &best);
    uint32_t bestIndex = 0;
    if (count > 1) {
        const float dy0 = point->m_position.y - best.y;
        const float dx0 = point->m_position.x - best.x;
        const float dz0 = point->m_position.z - best.z;
        float bestDistance = ppc::fmadds(dz0, dz0, ppc::fmadds(dx0, dx0, dy0 * dy0));
        uint32_t i = 1;
        do {
            CVector3 clamped;
            AABB_ClampPoint(&GraphNode(m_Graph, i & 0xffff)->m_Sector.m_box, &point->m_position, &clamped);
            const float dy = point->m_position.y - clamped.y;
            const float dx = point->m_position.x - clamped.x;
            const float dz = point->m_position.z - clamped.z;
            const float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (!(bestDistance <= distance)) {
                bestDistance = distance;
                bestIndex = i;
                best = clamped;
            }
            ++i;
        } while (count > (i & 0xffff));
    }
    result.m_position = best;
    result.m_i16GraphNodeIndex = static_cast<uint16_t>(bestIndex);
    return result;
}

// 0x001e5920 CKSrvPathFinding_AskForPath
int8_t CKSrvPathFinding::AcquirePathQuery(const CPFPoint* seeker, const CPFPoint* target,
                                          const CPFCharacter* character) {
    for (int32_t i = 0; i < 20; ++i) {
        if (m_aPathStock[i].m_bIsFree == 0) continue;
        m_aPathStock[i].Initialize(seeker, target, character);
        return static_cast<int8_t>(i);
    }
    return -1;
}

// 0x001e67e8 CKSrvPathFinding_IsPathWalkableInSameGrid. The original reads both nodes (and sets their grids' masks)
// before checking the hints; a hint outside the node array is not followed here (it fails the check below anyway).
uint8_t CKSrvPathFinding::IsDirectPathWalkable(const CPFPoint* from, const CPFPoint* to,
                                               const CPFCharacter* character, uint8_t thin) {
    const uint32_t nodeCount = m_Graph.m_ui32GraphNodesSize;
    const uint8_t mask = (character->m_bits & 0x800) == 0 ? 0xf7 : 0xff;
    CKPFGraphNode* const fromNode = from->m_i16GraphNodeIndex < nodeCount ? GraphNode(m_Graph, from->m_i16GraphNodeIndex) : nullptr;
    CKPFGraphNode* const toNode = to->m_i16GraphNodeIndex < nodeCount ? GraphNode(m_Graph, to->m_i16GraphNodeIndex) : nullptr;
    PathFinding_SetWalkabilityMode(character->m_bits & 7);
    if (fromNode != nullptr) fromNode->m_Sector.m_grid.m_ui8DynamicMask = mask;
    PathFinding_SetWalkabilityMode(character->m_bits & 7);
    if (toNode != nullptr) toNode->m_Sector.m_grid.m_ui8DynamicMask = mask;
    const int32_t fromIndex = static_cast<int16_t>(from->m_i16GraphNodeIndex);
    if (fromIndex < 0 || static_cast<uint32_t>(fromIndex) >= nodeCount) return 0;
    if (!BoxHoldsPoint(GraphNode(m_Graph, from->m_i16GraphNodeIndex)->m_Sector.m_box, from->m_position)) return 0;
    if (IsPointWalkable(from, character) == 0) return 0;
    const int32_t toIndex = static_cast<int16_t>(to->m_i16GraphNodeIndex);
    if (toIndex < 0 || static_cast<uint32_t>(toIndex) >= nodeCount) return 0;
    if (!BoxHoldsPoint(GraphNode(m_Graph, to->m_i16GraphNodeIndex)->m_Sector.m_box, to->m_position)) return 0;
    if (IsPointWalkable(to, character) == 0) return 0;
    // The grid holding both: the same node, else the target's when it holds the start, else the start's when it
    // holds the target.
    CPFSector* sector;
    if (fromIndex == toIndex) {
        sector = &fromNode->m_Sector;
    } else if (BoxHoldsPoint(toNode->m_Sector.m_box, from->m_position)) {
        sector = &toNode->m_Sector;
    } else if (BoxHoldsPoint(fromNode->m_Sector.m_box, to->m_position)) {
        sector = &fromNode->m_Sector;
    } else {
        return 0;
    }
    const float inv = g_pfGridScale.m_invCellSize;
    const CBBox& box = sector->m_box;
    CVector2 a;
    CVector2 b;
    a.m_fX = (from->m_position.x - box.m_inf.x) * inv;
    a.m_fY = inv * (from->m_position.z - box.m_inf.z);
    b.m_fY = inv * (to->m_position.z - box.m_inf.z);
    b.m_fX = inv * (to->m_position.x - box.m_inf.x);
    if (thin != 0) return sector->IsSegmentWalkable(&a, &b, 0);
    return sector->IsWideSegmentWalkable(character->m_fRadius, &a, &b, 0);
}

// 0x001e6e68 CKSrvPathFinding_IsPathWalkableOnTwoGrids. The portal's edge on the departure box (by the
// portal's side, bits 8-9 of its flags: 0 the maximum x, 1 the minimum x, 2 the maximum z, 3 the minimum z) is cut
// by the segment at `t` (on the segment); the halves stop at t -+ (radius / length + 0.001).
uint8_t CKSrvPathFinding::IsDirectPathAcrossTransition(const CPFPoint* from, const CPFPoint* to,
                                                       const CPFCharacter* character) {
    CKPFGraphNode* const fromNode = GraphNode(m_Graph, from->m_i16GraphNodeIndex);
    const int32_t found = fromNode->FindTransitionIndexTo(GraphNode(m_Graph, to->m_i16GraphNodeIndex));
    if (static_cast<int16_t>(found) < 0) return 0;
    CKPFGraphTransition* const transition = fromNode->m_ppTransition[found & 0xffff];
    if (transition == nullptr) return 0;
    if ((transition->m_baFlags & 1) != 0 || (transition->m_baFlags & 4) == 0) return 0;
    if (transition->AllowsCharacter(character) == 0) return 0;
    const CPFPortal& portal = transition->m_aPortals[0];
    const CBBox& box = portal.m_DepartureBox;
    float x0 = 0.0f;
    float z0 = 0.0f;
    float x1 = 0.0f;
    float z1 = 0.0f;
    switch ((portal.m_baTypesAndFlags >> 8) & 3) {
        case 0:
            x0 = box.m_sup.x;
            x1 = x0;
            z1 = box.m_sup.z;
            z0 = box.m_inf.z;
            break;
        case 1:
            x0 = box.m_inf.x;
            x1 = x0;
            z1 = box.m_sup.z;
            z0 = box.m_inf.z;
            break;
        case 2:
            z0 = box.m_sup.z;
            z1 = z0;
            x1 = box.m_sup.x;
            x0 = box.m_inf.x;
            break;
        default:
            z0 = box.m_inf.z;
            z1 = z0;
            x1 = box.m_sup.x;
            x0 = box.m_inf.x;
            break;
    }
    const float ax = from->m_position.x;
    const float az = from->m_position.z;
    const float bx = to->m_position.x;
    const float bz = to->m_position.z;
    CLine2D edge;
    edge.m_start.m_fX = x0;
    edge.m_start.m_fY = z0;
    edge.m_VectDir.m_fX = x1 - x0;
    edge.m_VectDir.m_fY = z1 - z0;
    CLine2D segment;
    segment.m_start.m_fX = ax;
    segment.m_start.m_fY = az;
    segment.m_VectDir.m_fX = bx - ax;
    segment.m_VectDir.m_fY = bz - az;
    float tEdge = 0.0f;
    float t = 0.0f;
    if (Seg2D_IntersectSegment(&edge, &segment, &tEdge, &t) == 0) return 0;
    const float length = MathSqrtf(
        ppc::fmadds(segment.m_VectDir.m_fX, segment.m_VectDir.m_fX, segment.m_VectDir.m_fY * segment.m_VectDir.m_fY));
    const float margin = character->m_fRadius / length + 0.001f;  // 0x3a83126f
    CPFPoint half;
    half.m_i16GraphNodeIndex = 0xffff;
    const float before = t - margin;
    if (before > 0.0f) {
        const float keep = 1.0f - before;
        half.m_position.y = from->m_position.y;
        half.m_i16GraphNodeIndex = from->m_i16GraphNodeIndex;
        half.m_position.z = ppc::fmadds(az, keep, bz * before);
        half.m_position.x = ppc::fmadds(ax, keep, bx * before);
        if (IsDirectPathWalkable(from, &half, character, 0) == 0) return 0;
    }
    const float after = margin + t;
    if (after >= 1.0f) return 1;
    const float keep = 1.0f - after;
    half.m_position.y = to->m_position.y;
    half.m_i16GraphNodeIndex = to->m_i16GraphNodeIndex;
    half.m_position.z = ppc::fmadds(az, keep, bz * after);
    half.m_position.x = ppc::fmadds(ax, keep, bx * after);
    return IsDirectPathWalkable(&half, to, character, 0) != 0 ? 1 : 0;
}

// 0x001e71e0 CKSrvPathFinding_SearchPFGraph. The graph A* is inlined (XXL2 TAstar<CKPFGraphNode, ..>::FindPath
// with the DotD costs: 2 per transition, the heuristic m_fMultGCoef * 0); a transition is followed when it is open
// (flag 4) or the character has bit 12 (set by the component while it searches past closed doors), the character may
// take it, and its node is in the graph.
PFSearchResult CKSrvPathFinding::FindSectorRoute(uint8_t slotIndex) {
    PFSearchResult result;
    CPFPathSlot& slot = m_aPathStock[slotIndex];
    const int16_t seekerHint = static_cast<int16_t>(slot.m_SeekerPosition.m_i16GraphNodeIndex);
    const int16_t targetHint = static_cast<int16_t>(slot.m_TargetPosition.m_i16GraphNodeIndex);
    if (seekerHint == -1) {
        result.m_i16Value = seekerHint;
        result.m_eState = 9;
        return result;
    }
    if (targetHint == -1) {
        result.m_i16Value = targetHint;
        result.m_eState = 0x11;
        return result;
    }
    m_Graph.m_Character.m_bits = slot.m_Character.m_bits;
    m_Graph.m_Character.m_fMaxStepRise = slot.m_Character.m_fMaxStepRise;
    m_Graph.m_Character.m_fRadius = slot.m_Character.m_fRadius;
    m_Graph.m_Character.m_fMaxStepHeight = slot.m_Character.m_fMaxStepHeight;
    const uint16_t startIndex = static_cast<uint16_t>(seekerHint);
    const uint16_t goalIndex = static_cast<uint16_t>(targetHint);
    CKPFGraphNode* const startNode = GraphNode(m_Graph, startIndex);
    CKPFGraphNode* const goalNode = GraphNode(m_Graph, goalIndex);
    CPFGraphNodeIndex route[200];
    for (CPFGraphNodeIndex& entry : route) entry.m_pNode = nullptr;

    TAstar& astar = m_AstarGraph;
    CAstarGraphPath* const nodes = static_cast<CAstarGraphPath*>(astar.NodeList);
    TRBTree<CAstarGraphPath> open(astar.OpenList);
    {
        CAstarGraphPath& zero = nodes[0];
        zero.m_pOpenList = nullptr;
        zero.m_ui16Node = 0;
        zero.m_rb.m_tParent = nullptr;
        zero.m_rb.m_tRight = nullptr;
        zero.m_rb.m_tLeft = nullptr;
        zero.m_rb.m_eColour = 0;
        zero.m_fFCost = 0.0f;
        zero.m_fGCost = 0.0f;
        zero.m_pNode = nullptr;
        zero.m_ui16parent = 0;
    }
    astar.m_ui16NodeListSize = 1;
    astar.m_ui16PathSize = 0;
    std::memset(astar.SearchList, 0, astar.m_ui32NumberOfZone << 1);
    open.Reset();

    int16_t found;  // the route length (> 0), 0 none, < 0 overflow
    if (startNode == goalNode && startIndex == goalIndex) {
        astar.m_ui16PathSize = 1;
        route[0].m_pNode = startNode;
        route[0].m_ui16Node = static_cast<uint16_t>(seekerHint);
        found = 1;
    } else {
        // The start node.
        CAstarGraphPath* const first = &nodes[1];
        first->m_ui16Node = static_cast<uint16_t>(seekerHint);
        first->m_pNode = startNode;
        first->m_fGCost = 0.0f;
        first->m_fFCost = astar.m_fMultGCoef * 0.0f;
        first->m_ui16parent = static_cast<uint16_t>((first->m_ui16parent & 0x8000) | 0x8000);
        astar.m_ui16NodeListSize = 2;
        open.Insert(first);
        first->m_pOpenList = first;
        astar.SearchList[startIndex] = 1;

        // The route from a node back to the start, into `route` (m_ui16PathSize entries): the length, 0 when it is
        // longer than the limit.
        auto construct = [&](uint32_t index, bool overflow) -> int16_t {
            if (index != 0) {
                route[astar.m_ui16PathSize].m_pNode = nodes[index].m_pNode;
                route[astar.m_ui16PathSize].m_ui16Node = nodes[index].m_ui16Node;
                for (;;) {
                    const uint16_t size = static_cast<uint16_t>(astar.m_ui16PathSize + 1);
                    astar.m_ui16PathSize = size;
                    if (!(astar.m_ui16MaxPathSize > size)) {
                        if (!overflow) return 0;
                        break;
                    }
                    index = nodes[index].m_ui16parent & 0x7fff;
                    if (index == 0) break;
                    route[size].m_pNode = nodes[index].m_pNode;
                    route[size].m_ui16Node = nodes[index].m_ui16Node;
                }
            }
            return overflow ? static_cast<int16_t>(-astar.m_ui16PathSize) : static_cast<int16_t>(astar.m_ui16PathSize);
        };

        found = 0;
        for (;;) {
            if (open.Root() == open.Sentinel()) break;
            CAstarGraphPath* const current = open.Leftmost();
            open.Remove(current);
            CKPFGraphNode* const node = current->m_pNode;
            current->m_ui16parent = static_cast<uint16_t>(current->m_ui16parent & 0x7fff);
            if (goalNode == node && goalIndex == current->m_ui16Node) {
                found = construct(astar.SearchList[goalIndex], false);
                break;
            }
            const int32_t transitionCount = node->m_ui16TransitionSize;
            if (static_cast<int32_t>(astar.m_ui16NodeListSize) + transitionCount >
                static_cast<int32_t>(astar.m_ui16ResearchZoneSize)) {
                found = construct(astar.SearchList[current->m_ui16Node], true);
                break;
            }
            for (int32_t i = 0; i < transitionCount; ++i) {
                CKPFGraphTransition* const transition = node->m_ppTransition[i & 0xffff];
                CKPFGraphNode* const target = static_cast<CKPFGraphNode*>(transition->m_pNode);
                // BUG(original): the target's index is read before the null test below (never null in the data).
                const uint16_t targetIndex = target != nullptr ? target->m_ui16Node : 0;
                if ((transition->m_baFlags & 4) == 0 && (m_Graph.m_Character.m_bits & 0x1000) == 0) continue;
                if (transition->AllowsCharacter(&m_Graph.m_Character) == 0) continue;
                if (target == nullptr) continue;
                if (m_Graph.m_ui32GraphNodesSize <= targetIndex) continue;
                const float cost = (current->m_fGCost + 1.0f) + 1.0f;
                const uint16_t existing = astar.SearchList[targetIndex];
                const uint16_t parentIndex = astar.SearchList[current->m_ui16Node];
                if (existing != 0) {
                    CAstarGraphPath* const known = &nodes[existing];
                    if (!(known->m_fGCost > cost)) continue;
                    known->m_fGCost = cost;
                    known->m_fFCost = ppc::fmadds(astar.m_fMultGCoef, 0.0f, cost);
                    known->m_ui16parent = static_cast<uint16_t>((parentIndex & 0x7fff) | (known->m_ui16parent & 0x8000));
                    if (static_cast<int16_t>(known->m_ui16parent) < 0) {
                        open.Remove(known->m_pOpenList);
                    } else {
                        known->m_ui16parent = static_cast<uint16_t>(known->m_ui16parent | 0x8000);
                    }
                    open.Insert(known);
                    known->m_pOpenList = known;
                } else {
                    const uint16_t index = astar.m_ui16NodeListSize;
                    CAstarGraphPath* const added = &nodes[index];
                    added->m_pNode = target;
                    added->m_ui16Node = targetIndex;
                    added->m_fGCost = cost;
                    added->m_fFCost = ppc::fmadds(astar.m_fMultGCoef, 0.0f, cost);
                    added->m_ui16parent = static_cast<uint16_t>((parentIndex & 0x7fff) | (added->m_ui16parent & 0x8000));
                    added->m_ui16parent = static_cast<uint16_t>(added->m_ui16parent | 0x8000);
                    astar.SearchList[targetIndex] = index;
                    open.Insert(added);
                    added->m_pOpenList = added;
                    astar.m_ui16NodeListSize = static_cast<uint16_t>(index + 1);
                }
            }
        }
    }
    if (found == 0) {
        result.m_eState = 1;
        result.m_i16Value = -1;
        return result;
    }
    if (found < 0) {
        result.m_eState = 0x21;
        result.m_i16Value = -1;
        return result;
    }
    slot.SetGraphPath(static_cast<uint8_t>(found), route);
    result.m_eState = 2;
    result.m_i16Value = found;
    return result;
}

// 0x001e92f8 CKSrvPathFinding_SearchPFGrid
PFSearchResult CKSrvPathFinding::SolveSectorSegment(uint8_t slotIndex) {
    PFSearchResult result;
    CPFPathSlot& slot = m_aPathStock[slotIndex];
    const float radius = slot.m_Character.m_fRadius;
    CKPFGraphNode* const node = GraphNode(m_Graph, slot.m_ui16GraphPath[slot.m_ui32GraphPathIndex]);
    CPFGrid& grid = node->m_Sector.m_grid;
    CVector3 ends[2];
    ComputeSegmentEndpoints(slotIndex, ends);
    grid.m_ui8DynamicMask = (slot.m_Character.m_bits & 0x800) == 0 ? 0xf7 : 0xff;
    PathFinding_SetWalkabilityMode(slot.m_Character.m_bits & 7);
    uint8_t startCell[2];
    uint8_t endCell[2];
    node->m_Sector.WorldToCell(&ends[0], startCell);
    node->m_Sector.WorldToCell(&ends[1], endCell);
    if (!(grid.m_width > startCell[0] && grid.m_height > startCell[1]) ||
        PFPaletteBlocked(g_pfGridPalette[grid.GetCellFlags(startCell)])) {
        result.m_eState = 9;
        result.m_i16Value = 0;
        return result;
    }
    if (!(grid.m_width > endCell[0] && grid.m_height > endCell[1]) ||
        PFPaletteBlocked(g_pfGridPalette[grid.GetCellFlags(endCell)])) {
        result.m_eState = 0x11;
        result.m_i16Value = 0;
        return result;
    }
    // BUG(original): the path buffer is 1012 bytes (506 cells) on the stack while the grid search may write up to
    // m_ui16MaxPathSize (1000) cells; a longer path overwrites the rest of the frame. Here the buffer holds them all.
    uint8_t path[2 * 1000];
    const int16_t count = m_AstarGrid.FindPathInGrid(&grid, startCell, endCell, path);
    if (count == 0) {
        result.m_i16Value = 0;
        result.m_eState = 1;
        return result;
    }
    if (count < 0) {
        result.m_i16Value = count;
        result.m_eState = 0x21;
        return result;
    }
    const uint16_t waypoints = node->m_Sector.FindWideSegmentWaypoint(radius, &ends[0], &ends[1], path,
                                                                      static_cast<uint16_t>(count),
                                                                      &slot.m_aCellGridPath[0][0]);
    slot.m_ui32GridPathIndex = 0;
    slot.m_ui32GridPathSize = waypoints;
    result.m_eState = 2;
    result.m_i16Value = static_cast<int16_t>(waypoints);
    return result;
}

// 0x001e9600 CKSrvPathFinding_UpdatePath
void CKSrvPathFinding::ProcessRequest(uint8_t slotIndex) {
    CPFPathSlot& slot = m_aPathStock[slotIndex];
    const uint32_t state = slot.m_eState;
    if ((state & 0x200) == 0) {
        if ((state & 0x100) == 0) return;
        slot.m_eState = SolveSectorSegment(slotIndex).m_eState;
        return;
    }
    if ((slot.m_Character.m_bits & 1) == 0) {
        FindSectorForPoint(&slot.m_SeekerPosition);
        FindSectorForPoint(&slot.m_TargetPosition);
    } else {
        bool seekerLost = true;
        if (static_cast<int16_t>(slot.m_SeekerPosition.m_i16GraphNodeIndex) != -1 &&
            BoxHoldsPoint(GraphNode(m_Graph, slot.m_SeekerPosition.m_i16GraphNodeIndex)->m_Sector.m_box,
                          slot.m_SeekerPosition.m_position)) {
            seekerLost = false;
        }
        if (seekerLost) slot.m_eState = 9;
        if (static_cast<int16_t>(slot.m_TargetPosition.m_i16GraphNodeIndex) == -1 ||
            !BoxHoldsPoint(GraphNode(m_Graph, slot.m_TargetPosition.m_i16GraphNodeIndex)->m_Sector.m_box,
                           slot.m_TargetPosition.m_position)) {
            slot.m_eState = 0x11;
            return;
        }
        if (seekerLost) return;
    }
    const PFSearchResult route = FindSectorRoute(slotIndex);
    slot.m_eState = (route.m_eState & 2) != 0 ? 0x104u : route.m_eState;
}

// 0x001e98f8 CKSrvPathFinding_Update
void CKSrvPathFinding::Update(IKTime* time) {
    if (time == nullptr || time->m_eCurrentState != 0) return;
    for (uint32_t i = 0; i < 20; ++i) {
        if (m_aPathStock[i].m_bIsFree == 0) ProcessRequest(static_cast<uint8_t>(i));
    }
}

// 0x001e9e60 CPFPathSlot_SetGraphPath
void CPFPathSlot::SetGraphPath(uint8_t count, const CPFGraphNodeIndex* route) {
    uint32_t n = count;
    if (n > 199) {
        m_ui32GraphPathSize = 200;
        n = 200;
    } else {
        m_ui32GraphPathSize = n;
    }
    for (uint32_t i = 0; (n & 0xff) > (i & 0xff); ++i) {
        m_ui16GraphPath[(n & 0xff) - (i & 0xff) - 1] = route[i & 0xff].m_ui16Node;
    }
    m_ui32GraphPathIndex = 0;
}

// 0x009ae3a8 TAstar_CPFGrid_FindPath (an [inline] of the LwMutex.cpp unit; TAstar::FindPath for CPFGrid).
// The neighbours in the order (x, z - 1), (x + 1, z), (x, z + 1), (x - 1, z); a step costs the cell's palette value
// (+ 0.0); the heuristic is m_fMultGCoef * fmadds(|dx|, |dx|, dz * dz) to the goal.
int16_t TAstar::FindPathInGrid(const CPFGrid* grid, const uint8_t* start, const uint8_t* goal, uint8_t* out) {
    CAstarGridPath* const nodes = static_cast<CAstarGridPath*>(NodeList);
    TRBTree<CAstarGridPath> open(OpenList);
    {
        // The unused node 0. The original stores a stale register (its return address) in the index, links and
        // open-list pointer; they are never read.
        CAstarGridPath& zero = nodes[0];
        zero.m_pOpenList = nullptr;
        zero.m_x = 0;
        zero.m_y = 0;
        zero.m_rb.m_tParent = nullptr;
        zero.m_rb.m_tRight = nullptr;
        zero.m_rb.m_tLeft = nullptr;
        zero.m_rb.m_eColour = 0;
        zero.m_fFCost = 0.0f;
        zero.m_ui16parent = 0;
        zero.m_fGCost = 0.0f;
    }
    m_ui16NodeListSize = 1;
    m_ui16PathSize = 0;
    std::memset(SearchList, 0, m_ui32NumberOfZone << 1);
    open.Reset();
    if (goal[0] == start[0] && start[1] == goal[1]) {
        out[1] = goal[1];
        out[0] = start[0];
        m_ui16PathSize = 1;
        return 1;
    }
    const uint32_t width = grid->m_width;
    auto heuristic = [&](uint8_t x, uint8_t y) {
        int32_t dy = static_cast<int32_t>(y) - static_cast<int32_t>(goal[1]);
        int32_t dx = static_cast<int32_t>(x) - static_cast<int32_t>(goal[0]);
        dy = dy < 0 ? -dy : dy;
        dx = dx < 0 ? -dx : dx;
        const float fdx = static_cast<float>(dx);
        const float fdy2 = static_cast<float>(dy * dy);
        return ppc::fmadds(fdx, fdx, fdy2);
    };
    {
        CAstarGridPath* const first = &nodes[1];
        first->m_x = start[0];
        first->m_y = start[1];
        first->m_fGCost = 0.0f;
        first->m_fFCost = m_fMultGCoef * heuristic(start[0], start[1]);
        first->m_ui16parent = static_cast<uint16_t>(first->m_ui16parent & 0x8000);
        first->m_ui16parent = static_cast<uint16_t>(first->m_ui16parent | 0x8000);
        m_ui16NodeListSize = 2;
        open.Insert(first);
        first->m_pOpenList = first;
        SearchList[start[0] + start[1] * width] = 1;
    }
    // The path from a node back to the start into `out` (m_ui16PathSize cells).
    auto construct = [&](uint32_t index, bool overflow) -> int16_t {
        if (index != 0) {
            out[2 * m_ui16PathSize] = nodes[index].m_x;
            out[2 * m_ui16PathSize + 1] = nodes[index].m_y;
            for (;;) {
                const uint16_t size = static_cast<uint16_t>(m_ui16PathSize + 1);
                m_ui16PathSize = size;
                if (!(m_ui16MaxPathSize > size)) {
                    if (!overflow) return 0;
                    break;
                }
                index = nodes[index].m_ui16parent & 0x7fff;
                if (index == 0) break;
                out[2 * (size & 0x7fff)] = nodes[index].m_x;
                out[2 * (size & 0x7fff) + 1] = nodes[index].m_y;
            }
        }
        return overflow ? static_cast<int16_t>(-m_ui16PathSize) : static_cast<int16_t>(m_ui16PathSize);
    };
    for (;;) {
        if (open.Root() == open.Sentinel()) return 0;
        CAstarGridPath* const current = open.Leftmost();
        open.Remove(current);
        current->m_ui16parent = static_cast<uint16_t>(current->m_ui16parent & 0x7fff);
        const uint8_t x = current->m_x;
        const uint8_t y = current->m_y;
        if (goal[0] == x && goal[1] == y) return construct(SearchList[x + goal[1] * width], false);
        if (static_cast<int32_t>(m_ui16NodeListSize) + 4 > static_cast<int32_t>(m_ui16ResearchZoneSize)) {
            return construct(SearchList[x + y * width], true);
        }
        for (uint32_t i = 0; i < 4; ++i) {
            uint8_t child[2];
            if (i == 0) {
                if (y == 0) continue;
                child[0] = x;
                child[1] = static_cast<uint8_t>(y - 1);
            } else if (i == 1) {
                if (x == 0xff) continue;
                child[1] = y;
                child[0] = static_cast<uint8_t>(x + 1);
            } else if (i == 2) {
                if (y == 0xff) continue;
                child[0] = x;
                child[1] = static_cast<uint8_t>(y + 1);
            } else {
                if (x == 0) continue;
                child[1] = y;
                child[0] = static_cast<uint8_t>(x - 1);
            }
            if (!(grid->m_width > child[0]) || !(grid->m_height > child[1])) continue;
            if (PFPaletteBlocked(g_pfGridPalette[grid->GetCellFlags(child)])) continue;
            const float step = static_cast<float>(g_pfGridPalette[grid->GetCellFlags(child)]);
            const float cost = (step + current->m_fGCost) + 0.0f;
            const uint16_t existing = SearchList[child[0] + child[1] * width];
            const uint16_t parentIndex = SearchList[x + y * width];
            if (existing != 0) {
                CAstarGridPath* const known = &nodes[existing];
                if (!(known->m_fGCost > cost)) continue;
                known->m_fGCost = cost;
                known->m_fFCost = ppc::fmadds(heuristic(child[0], child[1]), m_fMultGCoef, cost);
                known->m_ui16parent = static_cast<uint16_t>((known->m_ui16parent & 0x8000) | (parentIndex & 0x7fff));
                if (static_cast<int16_t>(known->m_ui16parent) < 0) {
                    open.Remove(known->m_pOpenList);
                } else {
                    known->m_ui16parent = static_cast<uint16_t>(known->m_ui16parent | 0x8000);
                }
                open.Insert(known);
                known->m_pOpenList = known;
            } else {
                const uint16_t index = m_ui16NodeListSize;
                CAstarGridPath* const added = &nodes[index];
                added->m_x = child[0];
                added->m_y = child[1];
                added->m_fGCost = cost;
                added->m_fFCost = ppc::fmadds(heuristic(child[0], child[1]), m_fMultGCoef, cost);
                added->m_ui16parent = static_cast<uint16_t>((added->m_ui16parent & 0x8000) | (parentIndex & 0x7fff));
                added->m_ui16parent = static_cast<uint16_t>(added->m_ui16parent | 0x8000);
                SearchList[child[0] + child[1] * width] = index;
                open.Insert(added);
                added->m_pOpenList = added;
                m_ui16NodeListSize = static_cast<uint16_t>(index + 1);
            }
        }
    }
}

// 0x001e5240 NavSectors_SnapPointToCellCenter_maybe: the centre of the cell of the point's node that holds it
// (CPFSector_FindIndexFromVector, then CPFSector_FindVectorFromIndex: at the box's bottom + 0.01) into `out`. Dead in
// the original (no pointer to its descriptor 0xb76360, no call).
void CKSrvPathFinding::SnapPointToCellCenter(const CPFPoint* point, CVector3* out) const {
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[point->m_i16GraphNodeIndex]);
    uint8_t cell[2];
    node->m_Sector.WorldToCell(&point->m_position, cell);
    node->m_Sector.CellToWorldPos(cell, out);
}

// 0x001e55f8 CKSrvPathFinding_IsTransitionEnabledBetween_maybe: the enabled bit (bit 2) of node `from`'s transition to
// node `to`; 0 without one. Dead in the original (no pointer to its descriptor 0xb76390, no call).
uint32_t CKSrvPathFinding::IsTransitionEnabledBetween(uint16_t from, uint16_t to) const {
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[from]);
    const int32_t index = node->FindTransitionIndexTo(m_Graph.m_apGraphNodes[to]);  // 0x001efda0
    if (static_cast<int16_t>(index) < 0) return 0;
    return (node->m_ppTransition[static_cast<uint16_t>(index)]->m_baFlags >> 2) & 1u;
}

// 0x001e59c8 NavSectors_RelocatePoint_maybe: the point's node looked up again: its hinted node when the box holds the
// point (x, z, then y, each inf <= p <= sup: cror, a NaN fails), else the first node a transition of it leads to whose
// box holds it, else the first node of the whole graph (a linear scan, not the quadtree of FindSectorForPoint) whose box
// holds it; the hint becomes that node's box id (NavSectors_FindBoxIdAtPoint_maybe), 1. None: the hint 0xffff, 0. Dead
// in the original (no pointer to its descriptor 0xb763d0, no call).
uint32_t CKSrvPathFinding::RelocatePoint(CPFPoint* point) {
    const auto holds = [point](const CBBox& box) {
        const float x = point->m_position.x;
        if (!(box.m_inf.x <= x) || !(box.m_sup.x >= x)) return false;
        const float z = point->m_position.z;
        if (!(box.m_inf.z <= z) || !(box.m_sup.z >= z)) return false;
        const float y = point->m_position.y;
        return box.m_inf.y <= y && box.m_sup.y >= y;
    };
    int32_t found = -1;
    if (static_cast<int16_t>(point->m_i16GraphNodeIndex) >= 0) {
        const uint16_t hint = point->m_i16GraphNodeIndex;
        const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[hint]);
        if (holds(node->m_Sector.m_box)) {
            found = hint;
        } else {
            for (uint32_t i = 0; i < node->m_ui16TransitionSize; ++i) {
                const CKPFGraphNode* target = static_cast<const CKPFGraphNode*>(node->m_ppTransition[i & 0xffffu]->m_pNode);
                if (holds(target->m_Sector.m_box)) {
                    found = target->m_ui16Node;
                    break;
                }
            }
        }
    }
    if (found < 0) {
        const int32_t count = static_cast<int32_t>(m_Graph.m_ui32GraphNodesSize);
        for (int32_t i = 0; i < count; ++i) {
            const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[i]);
            if (holds(node->m_Sector.m_box)) {
                found = i;
                break;
            }
        }
        if (found < 0) {
            point->m_i16GraphNodeIndex = 0xffff;
            return 0;
        }
    }
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[found & 0xffff]);
    point->m_i16GraphNodeIndex = node->FindBoxIdAtPoint(&point->m_position.x);  // 0x001efe18
    return 1;
}

// 0x001e5ef8 CKSrvPathFinding_RefreshQueryEndpointSectors_maybe: FindSectorForPoint of the slot's seeker, then of its
// target (that result returned: a tail call). Dead in the original (no pointer to its descriptor 0xb763e0, no call).
uint32_t CKSrvPathFinding::RefreshQueryEndpointSectors(uint32_t slot) {
    FindSectorForPoint(&m_aPathStock[slot].m_SeekerPosition);  // 0x001e5ca0
    return FindSectorForPoint(&m_aPathStock[slot].m_TargetPosition);
}

// 0x001e6de0 CKSrvPathFinding_GetTransitionBetweenPoints_maybe: GetTransitionBetween of the two points' nodes. Dead in
// the original (no pointer to its descriptor 0xb76428, no call).
CKPFGraphTransition* CKSrvPathFinding::GetTransitionBetweenPoints(const CPFPoint* from, const CPFPoint* to) const {
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(m_Graph.m_apGraphNodes[from->m_i16GraphNodeIndex]);
    const int32_t index = node->FindTransitionIndexTo(m_Graph.m_apGraphNodes[to->m_i16GraphNodeIndex]);
    if (static_cast<int16_t>(index) < 0) return nullptr;
    return node->m_ppTransition[static_cast<uint16_t>(index)];
}
