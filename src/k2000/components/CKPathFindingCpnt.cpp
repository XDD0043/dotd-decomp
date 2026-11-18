// CKPathFindingCpnt.cpp - reconstructed original translation unit 0x1e1080-0x1e3c08 (GAME_TOC1, main_toc1), 22 functions, 21 live.
// Primary class: CKPathFindingCpnt  key 0x8c6  category Component  size 0x78  vtable 0xb1e4f0
// Other owners: NavPoint (1), PathQuery (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1e1080  CKPathFindingCpnt_Delete
//   [ ] 0x1e10d0  RegisterCKPathFindingCpntClass
//   [ ] 0x1e1148  _GLOBAL__I_1e1148
//   [x] 0x1e1158  NavPoint_SnapToGround_maybe
//   [ ] 0x1e1360  CKPathFindingCpnt_IsDirectPathWalkable_maybe  [dead: no pointer to its descriptor 0xb75f78]
//   [ ] 0x1e13f0  CKPathFindingCpnt_ReleasePathQuery_maybe  [dead: no pointer to its descriptor 0xb75f80]
//   [x] 0x1e1478  CKPathFindingCpnt_DeleteArray
//   [x] 0x1e1520  CKPathFindingCpnt_SetTargetPosition
//   [ ] 0x1e1960  CKPathFindingCpnt_GetCurrentSegment_maybe  [dead]
//   [x] 0x1e1be8  PathQuery_ClassifyReachability_maybe
//   [x] 0x1e1f10  CKPathFindingCpnt_RecursiveRegistration
//   [x] 0x1e1f68  CKPathFindingCpnt_Destroy  (empty: the default)
//   [x] 0x1e1f70  CKPathFindingCpnt_Create
//   [x] 0x1e2040  CKPathFindingCpnt_Load
//   [ ] 0x1e2220  CKPathFindingCpnt_Save
//   [x] 0x1e2318  CKPathFindingCpnt_CreateArray
//   [x] 0x1e2420  CKPathFindingCpnt_RestartPF
//   [x] 0x1e25d0  CKPathFindingCpnt_TryStraightElseRestartPF
//   [x] 0x1e2820  CKPathFindingCpnt_CancelPathRequest_maybe
//   [x] 0x1e28c0  CKPathFindingCpnt_TryStraightElseContinue
//   [x] 0x1e2b28  CKPathFindingCpnt_Update
//   [x] 0x1e3a40  CKPathFindingCpnt_ResetCurrentPosition
//
//   [ ] 0x9adf58  CKPathFindingCpnt_IsKindOfClass  [inline]
//   [x] 0x9adf80  CKPathFindingCpnt_GetClassType  [inline]
//   [x] 0x9adf88  CKPathFindingCpnt_GetClassID  [inline]
//   [ ] 0x9adf90  CKPathFindingCpnt_DeletingDestructor  [inline]
//   [ ] 0x9adfd8  CKPathFindingCpnt_Destructor  [inline]
#include "k2000/components/CKPathFindingCpnt.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/NavGrid.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"

namespace {
inline CKSrvPathFinding* PathFindingService() {
    return static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
}

inline CKPFGraphNode* GraphNode(CKSrvPathFinding* service, uint32_t index) {
    return static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[index]);
}

// The squared distance in x / z the component compares with m_fPointValidationDistanceSquared.
inline float FlatDistanceSquared(const CVector3& a, const CVector3& b) {
    const float dx = a.x - b.x;
    const float dz = a.z - b.z;
    return ppc::fmadds(dx, dx, dz * dz);
}

// The query slot in use released (the original's inlined CKPathFindingCpnt_ReleasePathQuery_maybe).
inline void ReleaseQuery(CKPathFindingCpnt* component) {
    if (component->m_unk76 != 0xff) {
        PathFindingService()->m_aPathStock[component->m_unk76].Release();
        component->m_unk76 = 0xff;
    }
}

// The target taken as the waypoint and remembered (the original's inlined copies: +0x60 into +0x28 and +0x50).
inline void TakeTargetAsWaypoint(CKPathFindingCpnt* component) {
    const CPFPoint& target = component->m_ptTargetPosition;
    component->m_vCurrentTarget.x = target.m_position.x;
    component->m_vCurrentTarget.z = target.m_position.z;
    component->m_vCurrentTarget.y = target.m_position.y;
    component->m_ptOriginalTargetPosition.m_position.x = target.m_position.x;
    component->m_ptOriginalTargetPosition.m_position.y = target.m_position.y;
    component->m_ptOriginalTargetPosition.m_position.z = target.m_position.z;
    component->m_ptOriginalTargetPosition.m_unk0c = target.m_unk0c;
}

// The request mode (bits 4-6) and the phase (bits 7-9) of m_bits70.
inline uint32_t WithMode(uint32_t bits, uint32_t mode) { return (bits & 0xffffff8fu) | (mode << 4); }
inline uint32_t WithPhase(uint32_t bits, uint32_t phase) { return (bits & 0xfffffc7fu) | (phase << 7); }
// 0x001e9b78 PathFindingParams_Load (XXL2 CPFCharacter's Load; its unit is CKSrvPathFinding.cpp, which
// declares no Load for CPFCharacter yet): type 0 reads four byte-swapped words.
void PathFindingParams_Load(CPFCharacter* params, IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &params->m_bits);
    ReadF32LE(file, &params->m_unk04);
    ReadF32LE(file, &params->m_unk08);
    ReadF32LE(file, &params->m_unk0c);
}

// The inlined CPFCharacter constructor (twice in CKPathFindingCpnt_Create): bits 0..2 set, 3..10 cleared,
// bit 10 set on the zeroed word (0x407); the radius_maybe from the grid scale (fmuls).
void InitParams(CPFCharacter& p) {
    p.m_bits = 0;
    p.m_bits = ((p.m_bits & ~7u) | 7u) & 0xfffff807u;
    p.m_bits |= 0x400u;
    p.m_unk04 = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;  // 0.2f
    p.m_unk08 = 0x1.99999ap-3f;                                 // 0x3e4ccccd
    p.m_unk0c = 1.0f;
}
}  // namespace

// 0x001e1158 NavPoint_SnapToGround_maybe. The probe's input is zero (no delta, no height) with the masks 1 / 8; a
// ground found is read through GroundContact_GetWorldPoint (inlined in the original). The hints are compared as the
// original does: the old one zero-extended, the new one sign-extended.
uint8_t CKPathFindingCpnt::SnapToGround(CGroundContactDatasInOut* contact, CPFPoint* point) {
    CKSrvPathFinding* const service = PathFindingService();
    const CKPFGraphNode* const node = GraphNode(service, point->m_unk0c);
    CVector3 probe;
    probe.x = point->m_position.x;
    probe.z = point->m_position.z;
    probe.y = node->m_Sector.m_box.m_sup.y;
    CGroundContactDatasIn in;  // masks {1, 8}
    in.m_fDeltaMax = 0.0f;
    in.m_fObjectHeight = 0.0f;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, contact, &probe.x, 1);
    if (static_cast<int32_t>(contact->m_eContactStatus) > 1) return 0;
    if (contact->m_pGround != nullptr) GroundContact_GetWorldPoint(contact, &probe);
    const float y = probe.y - 0.01f;  // 0x3c23d70a
    point->m_position.x = probe.x;
    point->m_position.z = probe.z;
    point->m_position.y = y;
    const uint32_t before = point->m_unk0c;
    service->FindSectorForPoint(point);
    const int32_t after = static_cast<int16_t>(point->m_unk0c);
    if (after == -1) return 0;
    return before == static_cast<uint32_t>(after) ? 1 : 0;
}

// 0x001e1520 CKPathFindingCpnt_SetTargetPosition
uint8_t CKPathFindingCpnt::RequestPathTo(const CVector3* target, int16_t hint) {
    CKSrvPathFinding* const service = PathFindingService();
    CPFPoint& point = m_ptTargetPosition;
    point.m_position.x = target->x;
    point.m_position.y = target->y;
    point.m_position.z = target->z;
    if (hint == -1) {
        point.m_unk0c = m_Destination.m_unk0c;
        if (service->FindSectorForPoint(&point) == 0) {
            const CPFPoint nearest = service->ClampToNearestSector(&point);
            point.m_position.x = nearest.m_position.x;
            point.m_position.y = nearest.m_position.y;
            point.m_position.z = nearest.m_position.z;
            point.m_unk0c = nearest.m_unk0c;
        }
    } else {
        point.m_unk0c = static_cast<uint16_t>(hint);
        service->ClampPointToSector(&point);
    }
    if (service->IsPointWalkable(&point, &m_CharacterType) == 0) {
        CKPFGraphNode* const node = GraphNode(service, point.m_unk0c);
        PathFinding_SetWalkabilityMode(m_CharacterType.m_bits & 7);
        node->m_Sector.m_grid.m_ui8DynamicMask = (m_CharacterType.m_bits & 0x800) == 0 ? 0xf7 : 0xff;
        CVector3 clamped;
        if (node->m_Sector.ClampPointWithClearance(m_CharacterType.m_unk04, &point.m_position, &clamped) == 0) {
            m_unk3c = 0x11;
            m_bits70 = WithMode(m_bits70, 0);
            return 0;
        }
        point.m_position.x = clamped.x;
        point.m_position.y = clamped.y;
        point.m_position.z = clamped.z;
    }
    auto remember = [&]() {
        m_ptOriginalTargetPosition.m_position.x = point.m_position.x;
        m_ptOriginalTargetPosition.m_position.y = point.m_position.y;
        m_ptOriginalTargetPosition.m_position.z = point.m_position.z;
        m_ptOriginalTargetPosition.m_unk0c = point.m_unk0c;
    };
    const uint32_t mode = (m_bits70 >> 4) & 7;
    if (mode == 5 || mode == 1 || mode == 0 ||
        static_cast<int16_t>(m_ptOriginalTargetPosition.m_unk0c) != static_cast<int16_t>(point.m_unk0c)) {
        m_bits70 = WithMode(m_bits70, 5);
        remember();
        return 1;
    }
    if (static_cast<int16_t>(m_ptOriginalTargetPosition.m_unk0c) == -1) {
        m_bits70 = WithMode(m_bits70, 4);
        remember();
        return 1;
    }
    const CPFSector& sector = GraphNode(service, m_ptOriginalTargetPosition.m_unk0c)->m_Sector;
    uint8_t before[2];
    uint8_t after[2];
    sector.WorldToCell(&m_ptOriginalTargetPosition.m_position, before);
    sector.WorldToCell(&point.m_position, after);
    if (before[0] != after[0] || before[1] != after[1]) {
        m_bits70 = WithMode(m_bits70, 4);
        remember();
        return 1;
    }
    if (mode == 4) return 1;
    if (!(FlatDistanceSquared(point.m_position, m_ptOriginalTargetPosition.m_position) > m_fPointValidationDistanceSquared)) {  // ble
        m_bits70 = WithMode(m_bits70, 2);
        return 1;
    }
    m_bits70 = WithMode(m_bits70, 3);
    remember();
    return 1;
}

// 0x001e1be8 PathQuery_ClassifyReachability_maybe
uint32_t CKPathFindingCpnt::ClassifyReachability(const CGroundContactDatasIn* groundIn) {
    if (m_unk38 != 0x40) return m_unk38;
    if ((m_bits70 & 0x400) != 0) {
        m_unk38 = 1;
        return 1;
    }
    CKSrvPathFinding* const service = PathFindingService();
    CPFPoint from;
    from.m_position.x = m_Destination.m_position.x;
    from.m_position.y = m_Destination.m_position.y;
    from.m_position.z = m_Destination.m_position.z;
    from.m_unk0c = m_Destination.m_unk0c;
    CPFPoint to;
    to.m_position.x = m_vCurrentTarget.x;
    to.m_position.y = m_vCurrentTarget.y;
    to.m_position.z = m_vCurrentTarget.z;
    to.m_unk0c = m_Destination.m_unk0c;
    service->FindSectorForPoint(&to);
    if (m_unk34 != 0x80) return m_unk34;
    CGroundContactDatasInOut contact;  // ground 0, face -1, status 3, sector 0
    SnapToGround(&contact, &from);
    contact.m_i32FaceIndex = -1;
    contact.m_eContactStatus = 3;
    contact.m_ui8SectorNumber = 0;
    contact.m_pGround = nullptr;
    SnapToGround(&contact, &to);
    const float fromY = from.m_position.y;
    const float toY = to.m_position.y;
    const float dy = toY - fromY;
    const float height = std::fabs(dy);
    if (!(m_CharacterType.m_unk08 >= height)) {
        if (dy >= 0.0f) {
            m_unk38 = m_CharacterType.m_unk0c < dy ? 4u : 2u;
        } else {
            m_unk38 = 0x10;
        }
        return m_unk38;
    }
    // A small step: a wall across the segment (from the waypoint back) half a unit below, then above.
    CKSrvCollision* const collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    const float half = 0.5f;
    const float dx = from.m_position.x - to.m_position.x;
    const float dz = from.m_position.z - to.m_position.z;
    CLine line;
    CSlideGroundEdgeDatasOut slide;
    {
        const float startY = toY - half;
        line.m_start.x = to.m_position.x;
        line.m_start.z = to.m_position.z;
        line.m_VectDir.x = dx;
        line.m_start.y = startY;
        line.m_VectDir.z = dz;
        line.m_VectDir.y = (fromY - half) - startY;
        const uint32_t hit = collision->ResolveWallSegmentMovement(&line, groundIn->m_fObjectHeight, &slide, nullptr,
                                                                   nullptr, 1);  // 0x001996b0
        if (hit - 1 <= 2) {
            m_unk38 = 4;
            return 4;
        }
    }
    {
        const float startY = toY + half;
        line.m_start.x = to.m_position.x;
        line.m_start.z = to.m_position.z;
        line.m_VectDir.x = dx;
        line.m_VectDir.z = dz;
        line.m_start.y = startY;
        line.m_VectDir.y = (fromY + half) - startY;
        const uint32_t hit = collision->ResolveWallSegmentMovement(&line, groundIn->m_fObjectHeight, &slide, nullptr,
                                                                   nullptr, 1);  // 0x001996b0
        if (hit - 1 <= 2) {
            m_unk38 = 4;
            return 4;
        }
    }
    m_unk38 = 0x20;
    return 0x20;
}

// 0x001e1f70 CKPathFindingCpnt_Create, the inlined constructor.
CKPathFindingCpnt::CKPathFindingCpnt() {
    InitParams(m_CharacterType);
    InitParams(m_InstantaneousCharacterType);
    m_ptTargetPosition.m_unk0c = 0xffff;
    m_Destination.m_unk0c = 0xffff;
    m_ptOriginalTargetPosition.m_unk0c = 0xffff;
}

// 0x001e2040 CKPathFindingCpnt_Load
int32_t CKPathFindingCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fPointValidationDistanceSquared);
    PathFindingParams_Load(&m_CharacterType, file, K_LEVEL_PLATEFORMS);
    m_InstantaneousCharacterType = m_CharacterType;  // the word and the three floats copied
    ReadU32LE(file, &m_bits70);
    m_unk76 = 0xff;
    m_unk34 = 0x40;
    m_unk3c = type;
    m_unk74 = 0xffff;
    // rlwinm 25,3,31 / rlwinm 7,0,31 / ori 0x10: bits 0..6 replaced by 0x10.
    m_bits70 = (m_bits70 & ~0x7fu) | 0x10u;
    // rlwinm 22,3,31 / rlwinm 10,0,31 / ori 0x80: bits 7..9 cleared; bits 0..6 survive the rotation pair.
    m_bits70 = (m_bits70 & ~0x380u) | 0x80u;
    m_Destination.m_unk0c = 0xffff;
    m_ptOriginalTargetPosition.m_unk0c = 0xffff;
    m_ptTargetPosition.m_unk0c = 0xffff;
    m_bits70 &= ~0xeu;                        // bits 1..3 cleared
    return 1;
}

// 0x001e2420 CKPathFindingCpnt_RestartPF
uint8_t CKPathFindingCpnt::StartPathQuery() {
    ReleaseQuery(this);
    m_bits70 &= ~2u;
    CKSrvPathFinding* const service = PathFindingService();
    m_ptOriginalTargetPosition.m_position.x = m_ptTargetPosition.m_position.x;
    m_ptOriginalTargetPosition.m_position.y = m_ptTargetPosition.m_position.y;
    m_ptOriginalTargetPosition.m_position.z = m_ptTargetPosition.m_position.z;
    m_ptOriginalTargetPosition.m_unk0c = m_ptTargetPosition.m_unk0c;
    const int8_t slot = service->AcquirePathQuery(&m_Destination, &m_ptTargetPosition, &m_CharacterType);
    m_unk76 = static_cast<uint8_t>(slot);
    if (slot == -1) {
        m_bits70 = WithPhase(m_bits70, 0);
        m_unk3c = 0x21;
        return 0;
    }
    const int32_t previous = m_unk3c;
    const uint32_t result = service->GetNextQueryWaypoint(static_cast<uint8_t>(slot), &m_unk74, &m_vCurrentTarget);
    m_unk3c = static_cast<int32_t>(result);
    if ((previous & 1) != 0) m_unk3c = static_cast<int32_t>(result | 1);
    uint32_t bits = WithMode(m_bits70, 2);
    bits = WithPhase(bits, 5);
    m_bits70 = bits & 0xfffffbf1u;  // bits 1-3 and 10 cleared
    return 1;
}

namespace {
// The straight-line success shared by TryDirectPathElseQuery and TryDirectPath: the target is the waypoint; across a
// door the action 1, the result 0xc2 and bit 10, else the result 0x82; mode 2, phase 4, bits 2-3 cleared; the query
// released and bit 1 cleared.
void GoStraightToTarget(CKPathFindingCpnt* component, bool acrossDoor) {
    TakeTargetAsWaypoint(component);
    uint32_t bits;
    if (acrossDoor) {
        component->m_unk3c = 0xc2;
        component->m_unk34 = 1;
        component->m_unk38 = 0x40;
        bits = WithPhase(WithMode(component->m_bits70, 2), 4);
        bits &= 0xfffffbffu;
        bits = (bits & 0xfffffff3u) | 0x400u;
    } else {
        component->m_unk3c = 0x82;
        bits = WithPhase(WithMode(component->m_bits70, 2), 4);
        bits &= 0xfffffff3u;
    }
    component->m_bits70 = bits;
    ReleaseQuery(component);
    component->m_bits70 &= ~2u;
}

// The straight-line test of TryDirectPathElseQuery / TryDirectPath: in the same node the wide segment, else across
// the door between the two nodes. 0 no, 1 in the node, 2 across a door.
int32_t StraightLineTo(CKPathFindingCpnt* component) {
    CKSrvPathFinding* const service = PathFindingService();
    if (static_cast<int16_t>(component->m_Destination.m_unk0c) ==
        static_cast<int16_t>(component->m_ptTargetPosition.m_unk0c)) {
        return service->IsDirectPathWalkable(&component->m_Destination, &component->m_ptTargetPosition,
                                             &component->m_CharacterType, 0) != 0
                   ? 1
                   : 0;
    }
    return service->IsDirectPathAcrossTransition(&component->m_Destination, &component->m_ptTargetPosition,
                                                 &component->m_CharacterType) != 0
               ? 2
               : 0;
}
}  // namespace

// 0x001e25d0 CKPathFindingCpnt_TryStraightElseRestartPF
uint8_t CKPathFindingCpnt::TryDirectPathElseQuery() {
    const int32_t straight = StraightLineTo(this);
    if (straight == 0) {
        StartPathQuery();
        return 0;
    }
    GoStraightToTarget(this, straight == 2);
    return 1;
}

// 0x001e2820 CKPathFindingCpnt_CancelPathRequest_maybe
void CKPathFindingCpnt::CancelPathRequest() {
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    if (m_unk76 != 0xff) {
        service->m_aPathStock[m_unk76].Release();
        m_unk76 = 0xff;
    }
    m_bits70 = (m_bits70 & 0xfffffc00u) | (m_bits70 & 0xdu) | 0x10u | 0x100u;
    m_unk3c = 0;
}

// 0x001e28c0 CKPathFindingCpnt_TryStraightElseContinue
uint8_t CKPathFindingCpnt::TryDirectPath() {
    const int32_t straight = StraightLineTo(this);
    if (straight == 0) {
        m_bits70 = ((m_bits70 & 0xfffffffbu) | 4u) & 0xfffffff7u;
        return 0;
    }
    GoStraightToTarget(this, straight == 2);
    return 1;
}

// 0x001e2b28 CKPathFindingCpnt_Update. `phase` and `mode` are those on entry (the original keeps them in
// registers): the request is dispatched on them, the waypoint step then reads the phase again.
uint32_t CKPathFindingCpnt::Update(const CVector3* position) {
    CKSrvPathFinding* const service = PathFindingService();
    CPFPoint& current = m_Destination;
    current.m_position.x = position->x;
    current.m_position.y = position->y;
    current.m_position.z = position->z;
    const uint16_t previousNode = current.m_unk0c;
    service->FindSectorForPoint(&current);
    const uint32_t phase = (m_bits70 >> 7) & 7;
    const uint32_t mode = (m_bits70 >> 4) & 7;
    bool test = true;
    if (phase == 5) {
        if (static_cast<int16_t>(previousNode) != static_cast<int16_t>(current.m_unk0c)) {
            m_bits70 = WithPhase(m_bits70, 0);
        }
    } else if (phase == 6) {
        test = false;
    }
    if (test && (static_cast<int16_t>(current.m_unk0c) == -1 ||
                 service->IsPointWalkable(&current, &m_CharacterType) == 0)) {
        // Not walkable: blocked (phase 7), the waypoint the nearest open point with clearance.
        m_bits70 = WithPhase(m_bits70, 7);
        ReleaseQuery(this);
        m_bits70 &= ~2u;
        if (mode > 1) m_bits70 = WithMode(m_bits70, 5);
        CPFPoint local;
        local.m_unk0c = 0xffff;
        if (static_cast<int16_t>(current.m_unk0c) == -1) {
            const CPFPoint nearest = service->ClampToNearestSector(&current);
            local.m_position.x = nearest.m_position.x;
            local.m_position.y = nearest.m_position.y;
            local.m_position.z = nearest.m_position.z;
            local.m_unk0c = nearest.m_unk0c;
        } else {
            local.m_position.x = current.m_position.x;
            local.m_position.y = current.m_position.y;
            local.m_position.z = current.m_position.z;
            local.m_unk0c = current.m_unk0c;
        }
        CKPFGraphNode* const node = GraphNode(service, local.m_unk0c);
        PathFinding_SetWalkabilityMode(m_CharacterType.m_bits & 7);
        node->m_Sector.m_grid.m_ui8DynamicMask = (m_CharacterType.m_bits & 0x800) == 0 ? 0xf7 : 0xff;
        if (node->m_Sector.ClampPointWithClearance(m_CharacterType.m_unk04, &local.m_position, &m_vCurrentTarget) != 0) {
            m_unk3c = 10;
            return 10;
        }
        m_unk3c = 9;
        return 9;
    }
    if (mode <= 1) {
        // No request.
        ReleaseQuery(this);
        m_bits70 = (m_bits70 & 0xfffffc7du) | 0x180u;
        m_unk3c = 0x11;
        return 0x11;
    }
    // The request, by the phase on entry.
    switch (phase) {
        case 3:
            if (mode == 3) {
                if ((m_bits70 & 1) != 0) {
                    TryDirectPathElseQuery();
                } else {
                    TakeTargetAsWaypoint(this);
                    m_unk3c = 0x82;
                    m_bits70 = WithPhase(WithMode(m_bits70, 2), 4) & 0xfffffffbu;
                }
            } else if (mode == 4 || mode == 5) {
                TryDirectPathElseQuery();
            }
            break;
        case 4:
            if (mode == 3) {
                if (TryDirectPath() == 0) {
                    m_unk3c = 2;
                    m_bits70 = (m_bits70 & 0xfffffff7u) | 8u;
                }
            } else if (mode == 4 || mode == 5) {
                TryDirectPathElseQuery();
            }
            break;
        case 5:
            if (mode == 4) {
                if (static_cast<int16_t>(current.m_unk0c) == static_cast<int16_t>(m_ptTargetPosition.m_unk0c)) {
                    TryDirectPathElseQuery();
                }
            } else if (mode == 5) {
                TryDirectPathElseQuery();
            } else if (mode == 3) {
                if (static_cast<int16_t>(current.m_unk0c) == static_cast<int16_t>(m_ptTargetPosition.m_unk0c) &&
                    TryDirectPath() == 0) {
                    const uint32_t bits = (m_bits70 & 0xfffffffbu) | 4u;
                    m_bits70 = bits;
                    if ((m_unk3c & 0x80) != 0) {
                        m_bits70 = (bits & 0xfffffff3u) | 8u;
                        m_unk3c = static_cast<int32_t>(static_cast<uint32_t>(m_unk3c) & 0xffffff7fu);
                    }
                }
            }
            break;
        case 6:
            break;
        default:
            TryDirectPathElseQuery();
            break;
    }
    // The waypoint, by the phase now.
    const uint32_t result = static_cast<uint32_t>(m_unk3c);
    if ((result & 0x20) != 0) return result;
    const uint32_t bits = m_bits70;
    const float reach = m_fPointValidationDistanceSquared;
    // The straight line to the waypoint checked again (bit 0) unless at a portal; else a new query.
    auto recheckStraight = [&]() -> uint32_t {
        if ((bits & 1) == 0 || (result & 0x40) != 0) return result;
        CPFPoint waypoint;
        waypoint.m_unk0c = 0xffff;
        waypoint.m_position.x = m_vCurrentTarget.x;
        waypoint.m_position.y = m_vCurrentTarget.y;
        waypoint.m_position.z = m_vCurrentTarget.z;
        waypoint.m_unk0c = current.m_unk0c;
        if (PathFindingService()->IsDirectPathWalkable(&current, &waypoint, &m_CharacterType, 1) != 0) {
            return static_cast<uint32_t>(m_unk3c);
        }
        StartPathQuery();
        return static_cast<uint32_t>(m_unk3c);
    };
    // The target reached: the waypoint and the remembered target are the target, result 0x82.
    auto arrive = [&](uint32_t newBits) -> uint32_t {
        m_bits70 = newBits;
        TakeTargetAsWaypoint(this);
        m_unk3c = 0x82;
        return 0x82;
    };
    // A query result 1 (no path): a new query with bit 12 (closed doors allowed) set during it.
    auto replanThroughDoors = [&](uint32_t code) -> uint32_t {
        if (code != 1) return code;
        m_CharacterType.m_bits = (m_CharacterType.m_bits & 0xffffefffu) | 0x1000u;
        StartPathQuery();
        m_CharacterType.m_bits &= 0xffffefffu;
        return static_cast<uint32_t>(m_unk3c);
    };
    // Waiting (bit 1): result 2.
    auto wait = [&]() -> uint32_t {
        m_bits70 = (m_bits70 & 0xfffffffdu) | 2u;
        m_unk3c = 2;
        return 2;
    };
    // The next waypoint of the query; at the target with a pending straight attempt (bit 2): result 2, bit 3 set,
    // bit 2 cleared.
    auto nextWaypoint = [&]() -> uint32_t {
        const uint32_t code = service->GetNextQueryWaypoint(m_unk76, &m_unk74, &m_vCurrentTarget);
        m_unk3c = static_cast<int32_t>(code);
        if ((code & 0x80) != 0 && (m_bits70 & 4) != 0) {
            m_unk3c = 2;
            m_bits70 = (((m_bits70 & 0xfffffff7u) | 8u) & 0xfffffffbu);
        }
        return code;
    };
    const uint32_t now = (bits >> 7) & 7;
    if (now == 3) {
        if ((bits & 1) == 0) return result;
        if (FlatDistanceSquared(current.m_position, m_vCurrentTarget) > reach) {
            StartPathQuery();
            return static_cast<uint32_t>(m_unk3c);
        }
        return result;
    }
    if (now == 4) {
        if (FlatDistanceSquared(current.m_position, m_vCurrentTarget) <= reach) {
            if ((bits & 8) == 0) return arrive(WithPhase(bits, 3));
            return arrive(((bits & 0xfffffc7fu) & 0xfffffff3u) | 0x200u);
        }
        return recheckStraight();
    }
    if (now == 5) {
        if ((result & 4) != 0) {
            // The query was busy: its waypoint now.
            const uint32_t code = nextWaypoint();
            if ((code & 4) != 0 && (result & 1) != 0) {
                m_unk3c = static_cast<int32_t>(code | 1);
                return code | 1;
            }
            const uint32_t latest = static_cast<uint32_t>(m_unk3c);
            if ((latest & 0x40) == 0) return replanThroughDoors(latest);
            if (!(FlatDistanceSquared(current.m_position, m_vCurrentTarget) <= reach)) return wait();
            if (static_cast<int16_t>(current.m_unk0c) != static_cast<int16_t>(m_unk74)) {
                const CKPFGraphTransition* const transition = service->GetTransitionBetween(current.m_unk0c, m_unk74);
                // BUG(original): a missing transition is read (address 4); treated as a closed one here.
                if (transition != nullptr && (transition->m_baFlags & 4) != 0) return wait();
            }
            StartPathQuery();
            return static_cast<uint32_t>(m_unk3c);
        }
        if (!(FlatDistanceSquared(current.m_position, m_vCurrentTarget) <= reach)) return recheckStraight();
        if ((bits & 2) != 0) {
            // Waiting at the portal to the next node.
            if (static_cast<int16_t>(current.m_unk0c) == static_cast<int16_t>(m_unk74)) {
                StartPathQuery();
                return static_cast<uint32_t>(m_unk3c);
            }
            const CKPFGraphTransition* const transition = service->GetTransitionBetween(current.m_unk0c, m_unk74);
            // BUG(original): a missing transition is read (address 4); treated as a closed one here.
            if (transition == nullptr || (transition->m_baFlags & 4) == 0) {
                StartPathQuery();
                return static_cast<uint32_t>(m_unk3c);
            }
            if (m_CharacterType.m_bits != m_InstantaneousCharacterType.m_bits ||
                m_InstantaneousCharacterType.m_unk04 != m_CharacterType.m_unk04) {
                // The portal holding the position (else the last one) must allow the instantaneous type.
                const uint32_t count = transition->m_ui32NbPortals;
                const CPFPortal* portal = nullptr;
                if (count == 1) {
                    portal = &transition->m_aPortals[0];
                } else {
                    for (uint32_t i = 0; i < count; ++i) {
                        portal = &transition->m_aPortals[i];
                        const CBBox& box = portal->m_DepartureBox;
                        if (box.m_inf.x <= current.m_position.x && box.m_sup.x >= current.m_position.x &&
                            box.m_inf.z <= current.m_position.z && box.m_sup.z >= current.m_position.z &&
                            box.m_inf.y <= current.m_position.y && box.m_sup.y >= current.m_position.y) {
                            break;
                        }
                    }
                }
                // BUG(original): with no portal the byte at address 0x37 is read; never in the data.
                const uint32_t allowed = portal != nullptr ? (portal->m_baTypesAndFlags & 0xff) : 0;
                const uint32_t types = (m_InstantaneousCharacterType.m_bits >> 3) & 0xff;
                if ((allowed & types) != allowed) return static_cast<uint32_t>(m_unk3c);
            }
            // Cross the portal: phase 6, the waypoint the arrival point, the portal's action; the query advanced.
            m_bits70 &= ~2u;
            const CPFPathSlot& slot = service->m_aPathStock[m_unk76];
            m_vCurrentTarget.z = slot.m_vPortalArrival.z;
            m_vCurrentTarget.x = slot.m_vPortalArrival.x;
            m_vCurrentTarget.y = slot.m_vPortalArrival.y;
            m_unk34 = slot.m_ui32PortalAction;
            uint32_t crossing = (m_bits70 & 0xfffffbffu) | (((transition->m_baFlags ^ 1u) & 1u) << 10);
            m_bits70 = WithPhase(crossing, 6);
            uint16_t ignoredNode;
            CVector3 ignoredPoint;
            service->GetNextQueryWaypoint(m_unk76, &ignoredNode, &ignoredPoint);
            m_unk3c = 0x42;
            m_unk38 = 0x40;
            return 0x42;
        }
        if ((bits & 8) != 0) {
            ReleaseQuery(this);
            return arrive((m_bits70 & 0xfffffc71u) | 0x200u);
        }
        if ((result & 0x80) != 0) {
            ReleaseQuery(this);
            return arrive((m_bits70 & 0xfffffc7du) | 0x180u);
        }
        nextWaypoint();
        const uint32_t latest = static_cast<uint32_t>(m_unk3c);
        if ((latest & 0x40) != 0) return wait();
        return replanThroughDoors(latest);
    }
    if (now == 6) {
        // Crossing a portal: on the next node and near its arrival point.
        if (static_cast<int16_t>(m_unk74) != static_cast<int16_t>(current.m_unk0c)) return result;
        if (!(FlatDistanceSquared(current.m_position, m_vCurrentTarget) <= reach)) return result;
        const bool sameTargetNode = static_cast<int16_t>(m_unk74) == static_cast<int16_t>(m_ptTargetPosition.m_unk0c);
        if (mode == 5 || (mode == 4 && sameTargetNode)) {
            TryDirectPathElseQuery();
            return static_cast<uint32_t>(m_unk3c);
        }
        if (mode == 3 && sameTargetNode) {
            if (TryDirectPath() != 0) return static_cast<uint32_t>(m_unk3c);
            const uint32_t failed = (m_bits70 & 0xfffffffbu) | 4u;
            m_bits70 = failed;
            if ((m_unk3c & 0x80) != 0) {
                m_bits70 = (failed & 0xfffffff3u) | 8u;
                m_unk3c = 2;
            }
        }
        m_bits70 = WithPhase(m_bits70, 5);
        nextWaypoint();
        const uint32_t latest = static_cast<uint32_t>(m_unk3c);
        if ((latest & 0x40) != 0) return wait();
        return replanThroughDoors(latest);
    }
    return result;
}

// 0x001e3a40 CKPathFindingCpnt_ResetCurrentPosition
uint32_t CKPathFindingCpnt::SetDestination(const CVector3* destination) {
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    if (m_unk76 != 0xff) {
        service->m_aPathStock[m_unk76].Release();
        m_unk76 = 0xff;
    }
    m_bits70 = (m_bits70 & 0xffffff8du) | 0x10u;
    m_InstantaneousCharacterType = m_CharacterType;
    m_Destination.m_position = *destination;
    if (service->FindSectorForPoint(&m_Destination) != 0 &&
        service->IsPointWalkable(&m_Destination, &m_CharacterType) != 0) {
        m_bits70 = (m_bits70 & 0xfffffc7fu) | 0x100u;
        m_unk3c = 0;
        return 1;
    }
    m_unk3c = 9;
    m_bits70 = (m_bits70 & 0xfffffc7fu) | 0x380u;
    return 0;
}

// C2.8 port-all P11.

// 0x001e1f10 CKPathFindingCpnt_RecursiveRegistration (no type test)
void CKPathFindingCpnt::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
