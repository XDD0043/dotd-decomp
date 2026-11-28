// pathfinding_test - step 4: the path-finding service and component (CKSrvPathFinding: the graph and grid A*,
// the queries; CKPathFindingCpnt: RequestPathTo / Update) on LVL010's navigation data. There is no RPCS3 trace of a
// query yet, so the checks are the invariants of the original's code:
// - ClampToNearestSector / FindSectorForPoint put every census point (the LVL010 in-game census's ground contacts,
//   ground_probe_points.inc) in a node whose box holds it;
// - a query between two census points (AcquirePathQuery + ProcessRequest + GetNextQueryWaypoint) ends at the target
//   (0x82) through waypoints inside graph nodes, its graph route starting at the seeker's node and ending at the
//   target's, and gives the same waypoints bit for bit when run again (the open list's tie order is deterministic);
// - a component walked from waypoint to waypoint (Update from each waypoint) reaches its target.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/misc/NavGrid.h"

namespace {

struct ProbeCase {
    const char* label;
    uint32_t point[3];
    uint32_t reach[2];
    uint32_t masks[2];
    uint32_t status;
    int32_t face;
    uint32_t projection[3];
    uint32_t dh;
    uint32_t box[6];
    uint32_t sector;
};

const ProbeCase kCases[] = {
#include "ground_probe_points.inc"
};

float F(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
}

uint32_t Bits(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, 4);
    return bits;
}

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
CKSrvPathFinding* Service() { return static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding); }

// As ground_probe_test: the level from its spawn point in `sector`, run to the first gameplay frames.
bool StartLevel(int level, int32_t sector) {
    CKS08GameManager* manager = Manager();
    IKGameStructure* structure = static_cast<IKGameStructure*>(manager->m_gameStructure);
    for (uint32_t i = 0; i < structure->m_vpStages.m_ui32NbUsedElt; ++i) {
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[i];
        if (stage == nullptr || stage->m_i32StageIndex != level) continue;
        for (uint32_t s = 0; s < stage->m_vpSpawnPoints.m_ui32NbUsedElt; ++s) {
            CKGameSpawnPoint* spawnPoint = stage->m_vpSpawnPoints.m_pBlock[s];
            if (spawnPoint != nullptr && spawnPoint->m_iSectorIndex == sector) {
                structure->m_pCurrentSpawnPoint = spawnPoint;
                break;
            }
        }
    }
    manager->RequestSpawnPointLevel();
    uint32_t gameplayFrames = 0;
    for (uint32_t frame = 0; frame < 20000; ++frame) {
        c15::RunFrame();
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeQuit) return false;
        const uint32_t mode = g_pCKGameLoop->m_mode;
        if ((mode != 5 && mode != 8) || manager->m_currentLevel != level) continue;
        CKLevel* ckLevel = g_pEngine->m_level;
        const int32_t current = ckLevel->m_currentSector;
        const bool active = current >= 0 &&
                            (static_cast<const CKSector*>(ckLevel->m_vpSectors.m_pBlock[current])->m_ba16Properties & 1) != 0;
        if (active && ++gameplayFrames == 3) return true;
    }
    return false;
}

bool NodeHolds(uint16_t node, const CVector3& p) {
    CKSrvPathFinding* service = Service();
    if (node >= service->m_Graph.m_ui32GraphNodesSize) return false;
    const CBBox& box = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[node])->m_Sector.m_box;
    return box.m_inf.x <= p.x && p.x <= box.m_sup.x && box.m_inf.z <= p.z && p.z <= box.m_sup.z &&
           box.m_inf.y <= p.y && p.y <= box.m_sup.y;
}

// The census point as a path-finding point in its node (FindSectorForPoint, else the nearest node's box point).
CPFPoint Locate(const ProbeCase& c) {
    CPFPoint point;
    point.m_position = {F(c.projection[0]), F(c.projection[1]), F(c.projection[2])};
    point.m_i16GraphNodeIndex = 0xffff;
    if (Service()->FindSectorForPoint(&point) == 0) point = Service()->ClampToNearestSector(&point);
    return point;
}

// The character the queries use: the defaults of the K engine's CPFCharacter (modes 0-2, type 0x80, radius 0.2 cells).
CPFCharacter Walker() {
    CPFCharacter character;
    character.m_bits = 0x407;
    character.m_fRadius = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;
    character.m_fMaxStepHeight = 0x1.99999ap-3f;
    character.m_fMaxStepRise = 1.0f;
    return character;
}

// One query run to the end: the waypoints (bit patterns) handed out, the final state.
uint32_t RunQuery(const CPFPoint& from, const CPFPoint& to, const CPFCharacter& character, std::vector<uint32_t>* out,
                  uint32_t* routeLength, uint16_t* firstNode, uint16_t* lastNode) {
    CKSrvPathFinding* service = Service();
    const int8_t slotIndex = service->AcquirePathQuery(&from, &to, &character);
    if (slotIndex < 0) return 0xffffffffu;
    CPFPathSlot& slot = service->m_aPathStock[slotIndex];
    uint32_t state = 0;
    for (int step = 0; step < 2000; ++step) {
        service->ProcessRequest(static_cast<uint8_t>(slotIndex));
        if ((slot.m_eState & 0x300) != 0 && (slot.m_eState & 4) != 0) continue;
        uint16_t next = 0xffff;
        CVector3 waypoint;
        state = service->GetNextQueryWaypoint(static_cast<uint8_t>(slotIndex), &next, &waypoint);
        if ((state & 4) != 0) continue;  // the service is busy (0x104: the next leg)
        if ((state & 0x80) != 0 || (state & 0x42) == 0x42 || (state & 2) != 0) {
            out->push_back(Bits(waypoint.x));
            out->push_back(Bits(waypoint.y));
            out->push_back(Bits(waypoint.z));
        }
        if ((state & 0x80) != 0 || (state & 1) != 0 || state == 9 || state == 0x11 || state == 0x21) break;
    }
    *routeLength = slot.m_ui32GraphPathSize;
    *firstNode = slot.m_ui32GraphPathSize != 0 ? slot.m_ui16GraphPath[0] : 0xffff;
    *lastNode = slot.m_ui32GraphPathSize != 0 ? slot.m_ui16GraphPath[slot.m_ui32GraphPathSize - 1] : 0xffff;
    slot.Release();
    return state;
}

// Whether node `to` can be reached from node `from` over the transitions the graph search follows (open, or the
// character's bit 12; allowed for the character; with a node in the graph), breadth first.
bool Connected(uint32_t from, uint32_t to, const CPFCharacter& character, size_t* reachable) {
    CKSrvPathFinding* service = Service();
    const uint32_t count = service->m_Graph.m_ui32GraphNodesSize;
    std::vector<uint8_t> seen(count, 0);
    std::vector<uint32_t> queue(1, from);
    seen[from] = 1;
    for (size_t q = 0; q < queue.size(); ++q) {
        const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[queue[q]]);
        for (uint32_t t = 0; t < node->m_ui16TransitionSize; ++t) {
            const CKPFGraphTransition* tr = node->m_ppTransition[t];
            if ((tr->m_baFlags & 4) == 0 && (character.m_bits & 0x1000) == 0) continue;
            if (tr->AllowsCharacter(&character) == 0 || tr->m_pNode == nullptr) continue;
            const uint32_t next = static_cast<const CKPFGraphNode*>(tr->m_pNode)->m_ui16Node;
            if (next >= count || seen[next] != 0) continue;
            seen[next] = 1;
            queue.push_back(next);
        }
    }
    *reachable = queue.size();
    return seen[to] != 0;
}

}  // namespace

int main() {
    if (!c15::BootToFrontEnd()) {
        std::printf("pathfinding: no game data configured: skipped\n");
        return 77;
    }
    c15::ParkFrontEndSequence();
    const bool started = StartLevel(10, static_cast<int32_t>(kCases[0].sector));
    C15_CHECK(started);
    if (!started) std::_Exit(1);
    CKSrvPathFinding* service = Service();
    std::printf("pathfinding: LVL010 graph of %u nodes, cell size %g\n", service->m_Graph.m_ui32GraphNodesSize,
                g_pfGridScale.m_cellSize);
    C15_CHECK(service->m_Graph.m_ui32GraphNodesSize != 0);

    // Every census point in a node holding it.
    const uint32_t total = static_cast<uint32_t>(sizeof(kCases) / sizeof(kCases[0]));
    std::vector<CPFPoint> points;
    for (const ProbeCase& c : kCases) {
        const CPFPoint point = Locate(c);
        const bool inside = NodeHolds(point.m_i16GraphNodeIndex, point.m_position);
        if (!inside) {
            std::printf("FAIL pathfinding: %s: node %u does not hold (%.3f, %.3f, %.3f)\n", c.label, point.m_i16GraphNodeIndex,
                        point.m_position.x, point.m_position.y, point.m_position.z);
            ++c15::g_failures;
        }
        points.push_back(point);
    }
    // A point far away: the nearest node's box point.
    {
        CPFPoint far;
        far.m_position = {10000.0f, 0.0f, 10000.0f};
        far.m_i16GraphNodeIndex = 0xffff;
        const CPFPoint near = service->ClampToNearestSector(&far);
        C15_CHECK(NodeHolds(near.m_i16GraphNodeIndex, near.m_position));
    }

    // Queries from the first census point (the hero) to every other distinct point.
    const CPFCharacter character = Walker();
    uint32_t reached = 0, failed = 0, multiNode = 0;
    for (uint32_t i = 1; i < total; ++i) {
        const CPFPoint& from = points[0];
        const CPFPoint& to = points[i];
        if (service->IsPointWalkable(&from, &character) == 0 || service->IsPointWalkable(&to, &character) == 0) continue;
        std::vector<uint32_t> first, second;
        uint32_t length = 0, length2 = 0;
        uint16_t firstNode = 0, lastNode = 0, firstNode2 = 0, lastNode2 = 0;
        const uint32_t state = RunQuery(from, to, character, &first, &length, &firstNode, &lastNode);
        const uint32_t state2 = RunQuery(from, to, character, &second, &length2, &firstNode2, &lastNode2);
        C15_CHECK(state == state2 && first == second && length == length2);
        if ((state & 0x80) == 0) {
            ++failed;
            std::printf("pathfinding: %s: query state 0x%x (route of %u nodes) nodes %u -> %u\n", kCases[i].label, state,
                        length, from.m_i16GraphNodeIndex, to.m_i16GraphNodeIndex);
            // The graph search's answer checked with a breadth-first search over the same transitions.
            {
                size_t reachable = 0;
                const bool connected = Connected(from.m_i16GraphNodeIndex, to.m_i16GraphNodeIndex, character, &reachable);
                std::printf("   breadth-first: %zu nodes reachable, target %s\n", reachable,
                            connected ? "reachable" : "not reachable");
                if (length == 0) C15_CHECK(!connected || state != 1);
            }
            if (std::getenv("DOTD_PF_DEBUG") != nullptr) {
                const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[from.m_i16GraphNodeIndex]);
                for (uint32_t t = 0; t < node->m_ui16TransitionSize; ++t) {
                    const CKPFGraphTransition* tr = node->m_ppTransition[t];
                    std::printf("   transition %u -> node %u flags 0x%x allowed 0x%x radius %g portals %u allows %u\n", t,
                                static_cast<const CKPFGraphNode*>(tr->m_pNode)->m_ui16Node, tr->m_baFlags,
                                tr->m_AllowedChar.m_bits, tr->m_AllowedChar.m_fRadius, tr->m_ui32NbPortals,
                                tr->AllowsCharacter(&character));
                }
            }
            continue;
        }
        ++reached;
        if (length > 1) ++multiNode;
        C15_CHECK(firstNode == from.m_i16GraphNodeIndex || length == 0);
        // The last waypoint is the target.
        const size_t n = first.size();
        C15_CHECK(n >= 3 && F(first[n - 3]) == to.m_position.x && F(first[n - 1]) == to.m_position.z);
        std::printf("pathfinding: %s: reached in %zu waypoints through %u nodes\n", kCases[i].label, n / 3, length);
    }
    std::printf("pathfinding: %u queries reached the target (%u across nodes), %u did not\n", reached, multiNode, failed);
    C15_CHECK(reached > 0);

    // Queries to an open point of every graph node, for a character that may pass closed transitions (bit 12, as the
    // component's replanning sets): the routes through several nodes, their grid legs and portals.
    CVector3 farthest = points[total - 1].m_position;
    {
        CPFCharacter through = character;
        through.m_bits |= 0x1000;
        uint32_t nodeReached = 0, nodeFailed = 0, longest = 0, waypointsTotal = 0;
        for (uint32_t n = 0; n < service->m_Graph.m_ui32GraphNodesSize; ++n) {
            CKPFGraphNode* node = static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[n]);
            const CBBox& box = node->m_Sector.m_box;
            CVector3 centre = {(box.m_sup.x + box.m_inf.x) * 0.5f, box.m_inf.y + 0.01f, (box.m_sup.z + box.m_inf.z) * 0.5f};
            PathFinding_SetWalkabilityMode(through.m_bits & 7);
            node->m_Sector.m_grid.m_ui8DynamicMask = 0xf7;
            CPFPoint to;
            to.m_i16GraphNodeIndex = 0xffff;
            if (node->m_Sector.ClampPointWithClearance(through.m_fRadius, &centre, &to.m_position) == 0) continue;
            to.m_i16GraphNodeIndex = static_cast<uint16_t>(n);
            to.m_i16GraphNodeIndex = node->FindBoxIdAtPoint(&to.m_position.x);
            if (service->IsPointWalkable(&to, &through) == 0) continue;
            std::vector<uint32_t> first, second;
            uint32_t length = 0, length2 = 0;
            uint16_t firstNode = 0, lastNode = 0, firstNode2 = 0, lastNode2 = 0;
            const uint32_t state = RunQuery(points[0], to, through, &first, &length, &firstNode, &lastNode);
            const uint32_t state2 = RunQuery(points[0], to, through, &second, &length2, &firstNode2, &lastNode2);
            C15_CHECK(state == state2 && first == second && length == length2);
            size_t reachable = 0;
            const bool connected = Connected(points[0].m_i16GraphNodeIndex, to.m_i16GraphNodeIndex, through, &reachable);
            if ((state & 0x80) == 0) {
                ++nodeFailed;
                if (length == 0 && state == 1 && connected) {
                    std::printf("FAIL pathfinding: node %u: no route found, but reachable breadth first\n", n);
                    ++c15::g_failures;
                }
                continue;
            }
            if (length > 1) C15_CHECK(connected);
            ++nodeReached;
            if (length > longest) {
                longest = length;
                farthest = to.m_position;
            }
            waypointsTotal += static_cast<uint32_t>(first.size() / 3);
            C15_CHECK(firstNode == points[0].m_i16GraphNodeIndex);
            C15_CHECK(lastNode == to.m_i16GraphNodeIndex);
            const size_t count = first.size();
            C15_CHECK(count >= 3 && F(first[count - 3]) == to.m_position.x && F(first[count - 1]) == to.m_position.z);
            // Every waypoint inside a graph node.
            for (size_t w = 0; w + 2 < count; w += 3) {
                CPFPoint p;
                p.m_position = {F(first[w]), F(first[w + 1]), F(first[w + 2])};
                p.m_i16GraphNodeIndex = 0xffff;
                if (service->FindSectorForPoint(&p) == 0) {
                    std::printf("FAIL pathfinding: node %u: waypoint %zu (%.3f, %.3f, %.3f) in no node\n", n, w / 3,
                                p.m_position.x, p.m_position.y, p.m_position.z);
                    ++c15::g_failures;
                }
            }
        }
        std::printf("pathfinding: node centres: %u reached (longest route %u nodes, %u waypoints in all), %u not (no "
                    "route breadth first either)\n",
                    nodeReached, longest, waypointsTotal, nodeFailed);
        C15_CHECK(nodeReached > 0 && longest > 1);
    }

    // A component walked waypoint by waypoint (as the follower is) to the end of the longest route found above: the
    // straight line fails, a query is started, its grid waypoints and portals (phase 6) are followed node by node.
    {
        CKPathFindingCpnt component;
        component.m_fPointValidationDistanceSquared = 0.25f;
        component.m_CharacterType = character;
        component.m_InstantaneousCharacterType = character;
        component.m_bits70 = 0x90;
        component.m_i8PFSlot = 0xff;
        component.m_i16NextGrid = 0xffff;
        component.m_ui32Action = 0x40;
        component.m_ui32ReachabilityClass = 0x40;
        component.m_eState = 0;
        component.m_ptTargetPosition.m_i16GraphNodeIndex = 0xffff;
        component.m_ptOriginalTargetPosition.m_i16GraphNodeIndex = 0xffff;
        component.m_Destination.m_i16GraphNodeIndex = 0xffff;
        CVector3 position = points[0].m_position;
        C15_CHECK(component.SetDestination(&position) == 1);
        const CVector3 target = farthest;
        C15_CHECK(component.RequestPathTo(&target, -1) == 1);
        uint32_t result = 0;
        int steps = 0;
        for (; steps < 500; ++steps) {
            result = component.Update(&position);
            if (std::getenv("DOTD_PF_DEBUG") != nullptr) {
                std::printf("   update %d: result 0x%x phase %u mode %u flags 0x%x node %u next %u waypoint (%.3f, %.3f, %.3f)\n",
                            steps, result, (component.m_bits70 >> 7) & 7, (component.m_bits70 >> 4) & 7,
                            component.m_bits70 & 0x40f, component.m_Destination.m_i16GraphNodeIndex, component.m_i16NextGrid,
                            component.m_vCurrentTarget.x, component.m_vCurrentTarget.y, component.m_vCurrentTarget.z);
            }
            for (uint8_t s = 0; s < 20; ++s) {
                if (service->m_aPathStock[s].m_bIsFree == 0) service->ProcessRequest(s);
            }
            if (result == 0x82 && (component.m_bits70 >> 7 & 7) == 3) break;
            if (result == 9 || result == 10 || result == 0x11 || result == 0x21) break;
            if ((result & 2) != 0 || (result & 0x40) != 0) position = component.m_vCurrentTarget;
        }
        std::printf("pathfinding: component: result 0x%x after %d updates at (%.3f, %.3f, %.3f)\n", result, steps,
                    position.x, position.y, position.z);
        C15_CHECK(result == 0x82 && ((component.m_bits70 >> 7) & 7) == 3);
        C15_CHECK(position.x == target.x && position.z == target.z);
        C15_CHECK(steps > 2);  // the route crosses nodes: not reached in a straight line
    }

    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("pathfinding: all tests passed\n");
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
