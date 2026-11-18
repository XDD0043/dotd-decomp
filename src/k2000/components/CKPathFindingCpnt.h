// CKPathFindingCpnt.h - a character's path-finding parameters and query state (key 0x8c6, vtable 0xb1e4f0,
// size 0x78). Original unit: CKPathFindingCpnt.cpp. CKHkMovableCharacter embeds one (+0x1f0) and calls its
// Load. The two 0x10-byte blocks are XXL2 CPFCharacter (PathFindingParams in Ghidra; CKSrvPathFinding.h).
//
// XXL2 CKPathFindingCpnt has the same members in the same order (m_vCurrentTarget, m_ui32Action, m_eState,
// m_ptCurrentPosition, m_ptOriginalTargetPosition, m_ptTargetPosition, m_baFlags, m_i16NextGrid, m_i8PFSlot); DotD has
// one more word (+0x38) before m_eState.
//
// m_baFlags (+0x70, as Update reads it): bit 0 re-check the straight line to the waypoint while walking, bit 1
// waiting at a portal, bit 2 / bit 3 a straight-line attempt failed / the target was reached that way, bits 4-6 the
// request mode (0 / 1 none, 2 near the last target, 3 the same cell, 4 the same node, 5 a new node), bits 7-9 the
// phase (1 loaded, 2 position set, 3 at the target, 4 walking straight to the target, 5 following a query, 6 crossing
// a portal, 7 blocked), bit 10 the leg crosses a simple transition (ClassifyReachability's class 1).
#pragma once
#include <cstdint>

#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

struct CGroundContactDatasIn;
struct CGroundContactDatasInOut;

class CKPathFindingCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x23)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9adf58
        return key == 0x8c6 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPathFindingCpnt)

    CKPathFindingCpnt();  // 0x001e1f70 CKPathFindingCpnt_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001e2040 CKPathFindingCpnt_Load
    // vt+0x24 0x001e1f10 CKPathFindingCpnt_RecursiveRegistration: the component registered, whatever the type.
    // vt+0x10 0x1e1f68 Destroy: empty, the default.
    void RecursiveRegistration(int32_t type) override;
    // 0x001e1158 NavPoint_SnapToGround_maybe (XXL2 IKHkHero::FindPosOnGroundFromPFPoint-like): the ground under the
    // point (probed from its node's box top, one point, masks 1 / 8), the point moved onto it (0.01 below; the probe
    // start when no ground was found), its node looked up again. 1 when the contact found ground (status 0 or 1)
    // and the point stayed in the same node, else 0. `this` is not read.
    uint8_t SnapToGround(CGroundContactDatasInOut* contact, CPFPoint* point);
    // 0x001e1520 CKPathFindingCpnt_SetTargetPosition (XXL2 SetTargetPosition): a new target. `hint` -1: the node is
    // looked up from the current node (else the nearest node's box point); else the point is clamped into node
    // `hint`'s box. A target that is not walkable is moved into the nearest open cell with clearance (0 and result
    // code 0x11 when there is none). Then the request mode: 5 a new node (or the mode was 0, 1 or 5), 4 another cell
    // of the same node, 3 the same cell but farther than the validation distance, 2 the same cell and near (4 is kept);
    // the target is remembered (m_ptOriginalTargetPosition) except for modes 2 and a kept 4. Returns 1 (0 on failure).
    uint8_t RequestPathTo(const CVector3* target, int16_t hint);
    // 0x001e1be8 PathQuery_ClassifyReachability_maybe: m_unk38 (0x40: not classified yet) classified once for the
    // current waypoint: 1 for a closed door; else, when the waypoint is a portal jump (action 0x80), from both points
    // put on the ground: 0x10 a drop deeper than m_CharacterType.m_unk08, 4 a rise above m_CharacterType.m_unk0c, 2 a
    // smaller rise, else (a small height difference) 4 when a wall cuts the segment at either half height (0.5 below
    // or above, ResolveWallSegmentMovement with the ground's object height), 0x20 when not. Returns m_unk38 (the
    // action when it is not 0x80, without storing it).
    uint32_t ClassifyReachability(const CGroundContactDatasIn* groundIn);
    // 0x001e2420 CKPathFindingCpnt_RestartPF (XXL2 RestartPF): a query from the current position to the
    // target in a new slot: the first waypoint, phase 5 / mode 2 (0 and result 0x21 when no slot is free; result bit 0
    // kept). Returns 1 when a slot was taken.
    uint8_t StartPathQuery();
    // 0x001e25d0 CKPathFindingCpnt_TryStraightElseRestartPF (XXL2 TryStraightElseRestartPF): the target in a
    // straight line (in the same node: the wide segment; across a door: IsDirectPathAcrossTransition, which also makes
    // the action 1 and the result 0xc2), then phase 4 towards the target; else StartPathQuery. 1 when straight.
    uint8_t TryDirectPathElseQuery();
    // 0x001e2820 CKPathFindingCpnt_CancelPathRequest_maybe: the query slot in use (m_unk76, 0xff none) released,
    // the request state reset (bits 0-9 become 0x110 plus the kept bits 0, 2 and 3), the result code 0.
    void CancelPathRequest();
    // 0x001e28c0 CKPathFindingCpnt_TryStraightElseContinue (XXL2 TryStraightElseContinue): the same straight test without
    // the query; on failure bit 2 set, bit 3 cleared, 0 returned.
    uint8_t TryDirectPath();
    // 0x001e2b28 CKPathFindingCpnt_Update (XXL2 Update): one step towards the target from `position`: the
    // current node looked up; a position that is not walkable gives 9 / 10 (with the clamped waypoint); an idle
    // request (mode 0 or 1) gives 0x11; else the request is started by phase and mode and the waypoint advanced while
    // within the validation distance (queries, portals, the last leg). Returns the result code (m_unk3c): 0x82 the
    // target reached, 0x42 at a portal, 2 waiting, 4 the query is busy, bit 0 the path was replanned, 0x21 no slot.
    uint32_t Update(const CVector3* position);
    // 0x001e3a40 CKPathFindingCpnt_ResetCurrentPosition (XXL2 ResetCurrentPosition_maybe): the current position set.
    // The slot is released, the request state set, the instantaneous character type reset to the base one; 1 when the
    // path-finding service finds a node for the point and the point is walkable there (the state then says
    // "requested"), else 0 with the result code 9.
    uint32_t SetDestination(const CVector3* destination);

    float m_fPointValidationDistanceSquared;  // +0x04 (XXL2 name) read by the Load
    CPFCharacter m_CharacterType;  // +0x08 (XXL2) read by PathFindingParams_Load (0x1e9b78)
    CPFCharacter m_InstantaneousCharacterType;  // +0x18 (XXL2) a copy of m_CharacterType after the Load _maybe
    CVector3 m_vCurrentTarget;     // +0x28 (XXL2) the waypoint to walk to
    uint32_t m_unk34;              // +0x34 XXL2 m_ui32Action: the current portal's action (the Load sets 0x40)
    uint32_t m_unk38;              // +0x38 the reachability class of the waypoint (0x40 not classified)
    int32_t m_unk3c;               // +0x3c XXL2 m_eState: the result code (the Load stores its type argument, 0)
    CPFPoint m_Destination;        // +0x40 XXL2 m_ptCurrentPosition: the position (SetDestination, Update); its hint
                                   //       (+0x4c) is 0xffff (constructor, Load)
    CPFPoint m_ptOriginalTargetPosition;  // +0x50 (XXL2 name) the target last requested; hint 0xffff
    CPFPoint m_ptTargetPosition;   // +0x60 (XXL2) the target RequestPathTo sets; hint 0xffff
    uint32_t m_bits70;             // +0x70 XXL2 m_baFlags (see above); read (swapped), then bits 0..9 replaced by 0x90
    uint16_t m_unk74;              // +0x74 XXL2 m_i16NextGrid: the next graph node of the query; the Load sets 0xffff
    uint8_t m_unk76;               // +0x76 XXL2 m_i8PFSlot: the query slot, 0xff none (the Load)
    uint8_t m_pad77;
};
DOTD_ASSERT_SIZE(CKPathFindingCpnt, 0x78);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_fPointValidationDistanceSquared, 0x04);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_CharacterType, 0x08);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_InstantaneousCharacterType, 0x18);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_vCurrentTarget, 0x28);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_Destination, 0x40);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_ptOriginalTargetPosition, 0x50);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_ptTargetPosition, 0x60);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_bits70, 0x70);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKPathFindingCpnt, m_unk76, 0x76);
