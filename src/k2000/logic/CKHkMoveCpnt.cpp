// CKHkMoveCpnt.cpp - reconstructed original translation unit 0x2bc640-0x2c5e00 (GAME_TOC1, main_toc1), 20 functions, 17 live.
// Primary class: CKHkMoveCpnt  key 0x300c  category Logic  size 0xac  vtable 0xb22630
// Other owners: Steering (4), NavSteering (3), NavSector (1), NavSectors (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2bc640  CKHkMoveCpnt_Delete
//   [x] 0x2bc690  CKHkMoveCpnt_Destroy  (empty: the inherited default)
//   [ ] 0x2bc698  FUN_002bc698  [dead]
//   [ ] 0x2bc738  RegisterCKHkMoveCpntClass
//   [ ] 0x2bc7b0  _GLOBAL__I_2bc7b0
//   [x] 0x2bc7c0  NavSector_ContainsWalkablePoint_maybe
//   [x] 0x2bc920  CKHkMoveCpnt_DeleteArray
//   [x] 0x2bc9c0  CKHkMoveCpnt_Create
//   [x] 0x2bca10  CKHkMoveCpnt_CreateArray
//   [ ] 0x2bcac0  NavSectors_IsPointInAllowedSector_2_maybe  [dead]
//   [x] 0x2bcc98  CKHkMoveCpnt_Load
//   [ ] 0x2bd590  CKHkMoveCpnt_Save
//   [x] 0x2bdcf8  Steering_StepSpecialTraversal_maybe  (CKHkMoveCpnt::JumpMove)
//   [ ] 0x2be438  FUN_002be438  [dead]
//   [x] 0x2bea90  NavSteering_TestCellEdgeByNeighborFlags_maybe
//   [x] 0x2bf0d0  NavSteering_ComputeWallAvoidance3D_maybe
//   [x] 0x2c1180  Steering_ComputeDesiredVelocity3D_maybe
//   [x] 0x2c2390  NavSteering_ComputeWallAvoidance_maybe
//   [x] 0x2c4430  Steering_ComputeDesiredVelocityNoTurnSmoothing_maybe
//   [x] 0x2c4d38  Steering_ComputeDesiredVelocity_maybe
//
//   [ ] 0x990b48  CKHkMoveCpnt_RecursiveRegistration  [inline]
//   [ ] 0x990b50  KStub_Return1_990b50  [inline]
//   [ ] 0x990b58  KStub_Return1_990b58  [inline]
//   [ ] 0x990b60  KStub_Return1_990b60  [inline]
//   [ ] 0x990b68  KStub_Return1_990b68  [inline]
//   [ ] 0x990b70  KStub_Nop_990b70  [inline]
//   [ ] 0x990b78  KStub_Return1_990b78  [inline]
//   [ ] 0x990b80  KStub_Return1_990b80  [inline]
//   [ ] 0x990b88  KStub_Return0_990b88  [inline]
//   [ ] 0x990b90  IKUpdatable_IsKindOf  [inline]
//   [ ] 0x990bb0  KStub_Nop_990bb0  [inline]
//   [ ] 0x990bb8  KStub_Return1_990bb8  [inline]
//   [ ] 0x990bc0  KStub_Nop_990bc0  [inline]
//   [ ] 0x990bc8  KStub_Nop_990bc8  [inline]
//   [ ] 0x990bd0  KStub_Nop_990bd0  [inline]
//   [ ] 0x990bd8  KStub_Return1_990bd8  [inline]
//   [ ] 0x990be0  KStub_Return1_990be0  [inline]
//   [ ] 0x990be8  KStub_Nop_990be8  [inline]
//   [ ] 0x990bf0  KStub_Nop_990bf0  [inline]
//   [ ] 0x990bf8  KStub_Nop_990bf8  [inline]
//   [ ] 0x990c00  KStub_Nop_990c00  [inline]
//   [ ] 0x990c08  KStub_Nop_990c08  [inline]
//   [ ] 0x990c10  KStub_Return1_990c10  [inline]
//   [ ] 0x990c18  KStub_Nop_990c18  [inline]
//   [ ] 0x9bcfc8  CKHkMoveCpnt_GetClassType  [inline]
//   [ ] 0x9bcfd0  CKHkMoveCpnt_GetClassID  [inline]
//   [ ] 0x9bcfd8  CKHkMoveCpnt_IsKindOfClass  [inline]
//   [ ] 0x9bcff8  CKHkMoveCpnt_DeletingDestructor  [inline]
//   [ ] 0x9bd038  CKHkMoveCpnt_Destructor  [inline]
#include "k2000/logic/CKHkMoveCpnt.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/NavGrid.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/ai/CKSrvPathFinding.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/services/CKSrvAvoidance.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/math/Vec3.h"
#include "k2000/hooks/GroundContact.h"

// 0x002bcc98 CKHkMoveCpnt_Load
int32_t CKHkMoveCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        for (float& value : m_afParams) ReadF32LE(file, &value);
        m_fAnimScaleRatio = 0x1p+0f;  // TOC 0x18f8
        m_eMvtAnim = 0;
    }
    return 1;
}

namespace {

constexpr float kPi = 3.1415927f;     // TOC 0x192c
constexpr float kTwoPi = 6.2831855f;  // TOC 0x1930

bool SignBitSet(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof bits);
    return (bits >> 31) != 0;
}
// The inlined sinf / cosf of game code; a negative argument goes to the library functions (0x9a1390 / 0x9a11d8).
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }

// The path finding's result says its waypoint is followed: bit 2, not bit 0x80 without bit 4, not bit 1.
bool FollowsWaypoint(int32_t bits) {
    return (bits & 2) != 0 && !((bits & 0x80) != 0 && (bits & 4) == 0) && (bits & 1) == 0;
}

// The heading of a unit direction: acos of z, the other half turn for a negative x; outside acos's range 0 or pi.
float HeadingOf(float x, float z) {
    const bool outside = z < 0.0f ? z < -1.0f : z > 1.0f;  // TOC 0x1928 / 0x18f8
    if (outside) return z < 0.0f ? kPi : 0.0f;
    const float angle = crt::Acosf(z);  // TocBridge_Math_Acosf 0x98e1a0
    return x < 0.0f ? kTwoPi - angle : angle;
}

// The movement animation for a turn of `delta` (> 0: to the left of the heading, else to the right).
uint32_t TurnAnim(float delta, bool positive) {
    if (positive) {
        if (delta >= 5.4977875f) return 1;  // TOC 0x18a4
        if (delta >= 3.926991f) return 7;   // TOC 0x18a8
        if (delta >= 2.3561945f) return 2;  // TOC 0x18ac
        if (delta >= 0.7853982f) return 6;  // TOC 0x18b0
        return 1;
    }
    if (delta >= 5.4977875f) return 1;
    if (delta >= 3.926991f) return 6;
    if (delta >= 2.3561945f) return 2;
    if (delta < 0.7853982f) return 1;
    return 7;
}

}  // namespace

// 0x002c1180 Steering_ComputeDesiredVelocity3D_maybe (no XXL2 counterpart; the flying kinds 1 / 8): Move in three
// dimensions. The wall force is the 3D one (0x2bf0d0), the avoidance agent's y counts, the way to the target keeps the
// target's height (the waypoint's x / z with the target's y) and the target force is always of unit length (inside the
// arrival distance too); a followed waypoint drops the avoidance. The modes pick the target speed, acceleration and
// turn speed as Move's do, the yaw turns toward the force's heading (or `direction`'s), the position moves along the
// force's 3D direction (along the yaw, with a 0.1 climb while the force rises, when faster than the mode allows) by the
// FloatApproach speed (+0x84); the movement animation and its speed ratio as Move's. The original's NaN branches (bge /
// ble without cror) are kept as written. The labels are the original's addresses.
void CKHkMoveCpnt::Move3D(CVector3* position, float* yaw, CVector3* speed, const CVector3* target,
                          const CVector3* direction, const float* dt, const CGroundContactDatasIn* groundIn,
                          const CKAvoidanceAgent* avoidance, CKPathFindingCpnt* pathFinding, uint8_t mode,
                          SJumpMoveCpnt* jump, uint8_t keepPath, uint8_t staticForce) {
    const CVector3 kNull{0.0f, 0.0f, 0.0f};  // TOC 0x1938: g_nullVector 0x00c50d64
    const float kMargin = 0.05f;             // TOC 0x1950
    const float speedLength =
        std::sqrt(ppc::fmadds(speed->z, speed->z, ppc::fmadds(speed->x, speed->x, speed->y * speed->y)));
    CVector3 wall;
    if ((pathFinding->m_unk3c & 0x40) == 0 || (pathFinding->m_bits70 & 0x400u) != 0) {
        ComputeStaticAvoidForce3D(position, &wall, pathFinding);  // 0x002bf0d0
    } else {
        wall = kNull;  // 0x2c1498
    }
    float avoidX = avoidance->m_v0c.x;
    float avoidY = avoidance->m_v0c.y;
    float avoidZ = avoidance->m_v0c.z;
    if (jump != nullptr) {
        bool special = false;
        if ((pathFinding->m_unk3c & 0x40) != 0) {
            const uint32_t reach = pathFinding->ClassifyReachability(groundIn);  // 0x001e1be8
            special = reach != 1 && reach != 0x40;
        }
        if (special || jump->m_ui8JumpState != 0) {
            JumpMove(position, yaw, target, dt, pathFinding, jump);  // 0x002bdcf8
            *speed = kNull;
            return;
        }
    }

    // 0x2c13e0: the way to the target (the waypoint's x / z with the target's height while it is followed).
    float dx;
    float dy;
    float dz;
    if (FollowsWaypoint(pathFinding->m_unk3c)) {
        dx = pathFinding->m_vCurrentTarget.x - position->x;
        dy = target->y - position->y;
        dz = pathFinding->m_vCurrentTarget.z - position->z;
    } else {
        dx = target->x - position->x;
        dy = target->y - position->y;
        dz = target->z - position->z;
    }
    float arrival = Param(0x4c);
    if (Param(0x20) + kMargin < speedLength) arrival = Param(0x50);
    const float distance = std::sqrt(ppc::fmadds(dx, dx, dz * dz));  // flat
    float tx;
    float ty;
    float tz;
    if (distance == 0.0f) {  // 0x2c14e0
        tx = kNull.x;
        ty = kNull.y;
        tz = kNull.z;
    } else if (arrival < distance || FollowsWaypoint(pathFinding->m_unk3c)) {  // 0x2c1af8
        const float k = 1.0f / distance;
        tz = dz * k;
        tx = dx * k;
        ty = dy;
    } else {  // 0x2c1480
        const float k = 1.0f / arrival;
        tz = dz * k;
        tx = dx * k;
        ty = dy;
    }
    {
        const float length = std::sqrt(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, ty * ty)));  // 0x2c14f0
        if (length != 0.0f) {
            const float k = 1.0f / length;
            tz = tz * k;
            tx = tx * k;
            ty = ty * k;
        }
    }
    if (FollowsWaypoint(pathFinding->m_unk3c)) {  // 0x2c1b58: no avoidance along the path
        avoidX = kNull.x;
        avoidY = kNull.y;
        avoidZ = kNull.z;
    }
    float ax = kNull.x;
    float ay = kNull.y;
    float az = kNull.z;
    if (staticForce != 0) {
        const float ratio = Param(0x5c);
        ax = ppc::fmadds(ratio, wall.x, ax);
        az = ppc::fmadds(ratio, wall.z, az);
        ay = ppc::fmadds(ratio, wall.y, ay);
    }
    const float dynamicRatio = Param(0x60);
    const float targetRatio = Param(0x64);
    float ry = ppc::fmadds(targetRatio, ty, ppc::fmadds(dynamicRatio, avoidY, ay));
    float rx = ppc::fmadds(targetRatio, tx, ppc::fmadds(dynamicRatio, avoidX, ax));
    float rz = ppc::fmadds(targetRatio, tz, ppc::fmadds(dynamicRatio, avoidZ, az));
    float squared = ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry));
    float length = std::sqrt(squared);
    bool moving;
    if (!(length > 1.0f)) {  // ble 0x2c19e0
        moving = length > 0.0f;
    } else {
        moving = true;
        length = 1.0f;
        const float again = std::sqrt(squared);
        if (again != 0.0f) {  // 0x2c1ad8
            const float k = 1.0f / again;
            ry = ry * k;
            rx = rx * k;
            rz = rz * k;
            squared = ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry));
        }
    }

    // 0x2c15d8: the path request (as Move's).
    const int32_t requestBits = pathFinding->m_unk3c;
    bool request = true;
    if ((requestBits & 0x80) != 0 && (requestBits & 0x40) == 0) {
        const bool noWall = wall.x == kNull.x && wall.y == kNull.y && wall.z == kNull.z;
        const bool blocked = length < 0.5f && !noWall && Param(0x58) < distance;  // TOC 0x1948
        if (!blocked && keepPath == 0) {
            request = false;
            if (noWall) {
                pathFinding->RequestPathTo(position, -1);                            // 0x001e1520
                if (pathFinding->m_unk76 != 0xff) pathFinding->CancelPathRequest();  // 0x001e2820
            }
        }
    }
    if (request) {
        pathFinding->RequestPathTo(target, -1);  // 0x001e1520
        pathFinding->Update(position);           // 0x001e2b28
    }

    // 0x2c1618: the force's direction and heading, the turn still to make.
    float nx = rx;
    float ny = ry;
    float nz = rz;
    float heading = 0.0f;
    const float forceLength = std::sqrt(squared);
    if (forceLength != 0.0f) {  // 0x2c1970
        const float k = 1.0f / forceLength;
        nz = k * rz;
        nx = k * rx;
        ny = k * ry;
        heading = HeadingOf(nx, nz);
    }
    float turn = std::fabs(heading - *yaw);
    if (turn > kPi) turn = kTwoPi - turn;  // ble 0x2c1660

    // The mode's target speed (`aim`), acceleration, turn speed and how the position moves (`how`: 0 along the yaw,
    // 1 turning toward the force, 2 standing).
    float aim = 0.0f;
    float acceleration = 0.0f;
    float rotation = 0.0f;
    uint32_t how = 0;
    auto fast = [&]() {  // 0x2c1ec8
        if (Param(0x44) < std::fabs(turn)) aim = Param(0x20);
        acceleration = Param(0x28);
        rotation = Param(0x34);
        how = 0;
    };
    if (mode == 0) {  // 0x2c19f8
        aim = Param(0x3c) < length ? Param(0x20) : 0.0f;
        acceleration = Param(0x2c);
        rotation = Param(0x38);
        how = speedLength > 0.0f ? 1 : 2;
    } else if (mode == 1) {  // 0x2c1d00 (bge: an unordered length takes the slow branch)
        if (Param(0x40) < length) {
            aim = Param(0x1c);
        } else {
            aim = Param(0x3c) < length ? Param(0x20) : 0.0f;
        }
        if (Param(0x20) + kMargin < speedLength) {
            fast();
        } else {
            acceleration = Param(0x2c);
            rotation = Param(0x38);
            if (!(speedLength > 0.0f)) {
                how = 2;
            } else {
                if (Param(0x48) < std::fabs(turn) && Param(0x1c) == aim) aim = Param(0x20);
                how = 1;
            }
        }
    } else if (mode == 2) {  // 0x2c2088
        if (Param(0x40) < length) {
            aim = Param(0x54) < distance ? Param(0x18) : Param(0x1c);
        } else {
            aim = Param(0x3c) < length ? Param(0x20) : 0.0f;
        }
        if (Param(0x1c) + kMargin < speedLength) {
            if (Param(0x44) < std::fabs(turn)) aim = Param(0x20);
            acceleration = Param(0x24);
            rotation = Param(0x30);
            how = 0;
        } else if (Param(0x20) + kMargin < speedLength) {
            fast();
        } else {
            acceleration = Param(0x24);
            rotation = Param(0x30);
            if (!(speedLength > 0.0f)) {
                how = 2;
            } else {
                if (Param(0x48) < std::fabs(turn) && Param(0x18) == aim) aim = Param(0x20);
                how = 1;
            }
        }
    } else {
        // STUB(C2.8): modes above 2 (+0x397) branch on the low byte of the target pointer and an uninitialised float
        // register in the original (as Move's); no DotD enemy is known to use one. Treated as mode 0.
        DOTD_STUB_ONCE("CKHkMoveCpnt_Move3D: mode above 2 (C2.8)");
        aim = Param(0x3c) < length ? Param(0x20) : 0.0f;
        acceleration = Param(0x2c);
        rotation = Param(0x38);
        how = speedLength > 0.0f ? 1 : 2;
    }
    // 0x2c1680: once arrived (and not following the waypoint) the goal is `direction`'s heading.
    if (!(FollowsWaypoint(pathFinding->m_unk3c) && (pathFinding->m_unk3c & 4) == 0) && !(arrival < distance)) {
        heading = HeadingOf(direction->x, direction->z);
    }

    float outX = nx;
    float outY = ny;
    float outZ = nz;
    if (how == 0) {  // 0x2c1714: along the yaw, climbing 0.1 while the force rises
        const float y0 = *yaw;
        outX = GameSinf(y0);
        outZ = GameCosf(y0);
        outY = 0.0f;
        if (ny > 0.0f) {
            const float l = std::sqrt(ppc::fmadds(outZ, outZ, ppc::fmadds(outX, outX, 0.01f)));  // TOC 0x1954
            if (l == 0.0f) {
                outY = 0.1f;  // TOC 0x1958
            } else {
                const float k = 1.0f / l;
                outZ = outZ * k;
                outX = outX * k;
                outY = k * 0.1f;
            }
        }
        m_eMvtAnim = !(Param(0x1c) < speedLength) ? 3 : 4;  // bge
    } else if (how == 1) {  // 0x2c1f28: toward the force
        float goal = heading;
        if (!(FollowsWaypoint(pathFinding->m_unk3c) && (pathFinding->m_unk3c & 4) == 0) && !(Param(0x4c) < distance)) {
            goal = HeadingOf(direction->x, direction->z);
        }
        const float y0 = *yaw;
        float delta = heading - y0;
        uint32_t anim;
        if (heading > y0) {
            if (!(delta < 5.4977875f)) {  // TOC 0x18a4
                anim = 1;
            } else if (delta >= 3.926991f) {  // TOC 0x18a8
                anim = 7;
            } else if (delta >= 2.3561945f) {  // TOC 0x18ac
                anim = 2;
            } else if (delta >= 0.7853982f) {  // TOC 0x18b0
                anim = 6;
            } else {
                anim = 1;
            }
        } else {
            delta = -delta;
            if (!(delta < 5.4977875f)) {
                anim = 1;
            } else if (!(delta < 3.926991f)) {
                anim = 6;
            } else if (!(delta < 2.3561945f)) {
                anim = 2;
            } else if (delta < 0.7853982f) {
                anim = 1;
            } else {
                anim = 7;
            }
        }
        heading = goal;
        m_eMvtAnim = anim;
    } else {  // 0x2c1c68: standing: `direction`'s heading (the force's while the waypoint is followed)
        if (!(FollowsWaypoint(pathFinding->m_unk3c) && (pathFinding->m_unk3c & 4) == 0)) {
            heading = HeadingOf(direction->x, direction->z);
        }
        outX = rx;
        outY = ry;
        outZ = rz;
        if (length > 0.0f) {
            const float again = std::sqrt(squared);
            if (again != 0.0f) {
                const float k = 1.0f / again;
                outZ = k * rz;
                outX = k * rx;
                outY = k * ry;
            }
        }
        m_eMvtAnim = 5;
    }

    // 0x2c18a0: the yaw turned toward `heading` by the turn speed, the shorter way.
    {
        const float y0 = *yaw;
        float delta = heading - y0;
        if (delta == 0.0f) {
            if (Param(0x3c) > length) m_eMvtAnim = 0;  // 0x2c1ce8
        } else {
            float speedOfTurn = rotation;
            if (heading > y0) {
                if (!(delta < kPi)) {
                    speedOfTurn = -rotation;
                    delta = kTwoPi - delta;
                }
            } else {
                delta = -delta;  // 0x2c1d88
                if (!(delta < kPi)) {
                    delta = kTwoPi - delta;
                } else {
                    speedOfTurn = -rotation;
                }
            }
            delta = std::fabs(delta);
            const float step = speedOfTurn * *dt;
            const float size = step < 0.0f ? -step : step;
            if (!(delta < size)) {  // bge 0x2c1d68
                *yaw = y0 + step;
            } else {
                *yaw = heading;
                if (Param(0x3c) > length) m_eMvtAnim = 0;
            }
            float y = *yaw;
            if (y > kTwoPi) {
                y = y - kTwoPi;
                *yaw = y;
            }
            if (y < 0.0f) *yaw = y + kTwoPi;
        }
    }

    // 0x2c1930: the speed along the direction.
    float current;
    {
        const float sx = speed->x, sy = speed->y, sz = speed->z;
        if (!moving || (aim == 0.0f && sx == kNull.x && sy == kNull.y && sz == kNull.z)) {
            *speed = kNull;  // 0x2c1bc8
            current = 0.0f;
        } else {
            float ux = sx, uy = sy, uz = sz;
            const float l = std::sqrt(ppc::fmadds(sz, sz, ppc::fmadds(sx, sx, sy * sy)));
            if (l != 0.0f) {
                const float k = 1.0f / l;
                uz = sz * k;
                ux = sx * k;
                uy = sy * k;
            }
            const float along = ppc::fmadds(outZ, uz, ppc::fmadds(ux, outX, outY * uy));
            m_afUnk84[2] = !(along > 0.0f) ? 0.0f : speedLength;  // ble
            m_afUnk84[1] = acceleration;
            m_afUnk84[0] = aim;
            FloatApproach_Step(*dt, m_afUnk84);  // 0x002436e8
            current = m_afUnk84[2];
            const float stepLength = current * *dt;
            position->z = ppc::fmadds(stepLength, outZ, position->z);
            position->x = ppc::fmadds(stepLength, outX, position->x);
            position->y = ppc::fmadds(stepLength, outY, position->y);
            speed->z = current * outZ;
            speed->x = current * outX;
            speed->y = current * outY;
        }
    }
    // 0x2c1be4: the animation's speed ratio (the TOC +0x195c jump table).
    switch (m_eMvtAnim) {
        case 0:
        case 5:
        case 10:
            m_fAnimScaleRatio = 1.0f;
            break;
        case 3:
            m_fAnimScaleRatio = current / Param(0x0c);
            break;
        case 4:
            m_fAnimScaleRatio = current / Param(0x10);
            break;
        case 8:
            m_fAnimScaleRatio = 1.0f / Param(0x68);
            break;
        case 9:
            m_fAnimScaleRatio = 1.0f / (Param(0x70) * jump->m_fBirdDist * Param(0x78));
            break;
        case 11:
            m_fAnimScaleRatio = 1.0f / Param(0x6c);
            break;
        default:  // 1, 2, 6, 7 and above 11
            m_fAnimScaleRatio = current / Param(0x14);
            break;
    }
}

// 0x002c4430 Steering_ComputeDesiredVelocityNoTurnSmoothing_maybe (no XXL2 counterpart; the burning run's step, State26
// 0x29fba0): Move's forces, path request and headings without its speed control. The arrival distance is always +0x50,
// the static force always weighted, `mode` is not read; the yaw turns toward the goal by +0x38 per second, the movement
// animation is the turn's (or 0 once turned with a force below +0x3c), and the position moves along the force's
// direction by the current speed's length times dt; `speed` itself and the animation's speed ratio are left as they are.
// The original's NaN branches (bge / ble without cror) are kept as written.
void CKHkMoveCpnt::MoveNoTurnSmoothing(CVector3* position, float* yaw, CVector3* speed, const CVector3* target,
                                       const CVector3* direction, const float* dt, const CGroundContactDatasIn* groundIn,
                                       const CKAvoidanceAgent* avoidance, CKPathFindingCpnt* pathFinding, uint8_t /*mode*/,
                                       SJumpMoveCpnt* jump, uint8_t keepPath) {
    const CVector3 kNull{0.0f, 0.0f, 0.0f};  // TOC 0x1938: g_nullVector 0x00c50d64
    CVector3 wall;
    if ((pathFinding->m_unk3c & 0x40) == 0 || (pathFinding->m_bits70 & 0x400u) != 0) {
        ComputeStaticAvoidForce(position, &wall, pathFinding);  // 0x002c2390
    } else {
        wall = kNull;  // 0x2c4888
    }
    float avoidX = avoidance->m_v0c.x;
    float avoidZ = avoidance->m_v0c.z;
    if (jump != nullptr) {
        bool special = false;
        if ((pathFinding->m_unk3c & 0x40) != 0) {
            const uint32_t reach = pathFinding->ClassifyReachability(groundIn);  // 0x001e1be8
            special = reach != 1 && reach != 0x40;
        }
        if (special || jump->m_ui8JumpState != 0) {
            JumpMove(position, yaw, target, dt, pathFinding, jump);  // 0x002bdcf8
            *speed = kNull;
            return;
        }
    }

    // 0x2c4628: the way to the target (or the path finding's waypoint).
    float dx;
    float dz;
    if (FollowsWaypoint(pathFinding->m_unk3c)) {
        dz = pathFinding->m_vCurrentTarget.z - position->z;
        dx = pathFinding->m_vCurrentTarget.x - position->x;
    } else {
        dz = target->z - position->z;
        dx = target->x - position->x;
    }
    const float distance = std::sqrt(ppc::fmadds(dx, dx, dz * dz));  // 0x00010690
    const float arrival = Param(0x50);
    float tx;
    float tz;
    const float ty = 0.0f;
    bool dropAvoidance = false;
    if (distance == 0.0f) {  // 0x2c48f0
        tx = kNull.x;
        tz = kNull.z;
        dropAvoidance = arrival > distance && FollowsWaypoint(pathFinding->m_unk3c);
    } else if (distance > arrival || FollowsWaypoint(pathFinding->m_unk3c)) {  // 0x2c4bb8
        const float k = 1.0f / distance;
        tz = k * dz;
        tx = k * dx;
        dropAvoidance = arrival > distance && FollowsWaypoint(pathFinding->m_unk3c);
    } else {  // 0x2c46a8: inside the arrival distance the target force shrinks with it
        const float k = 1.0f / arrival;
        tz = k * dz;
        tx = k * dx;
    }
    float avoidY = 0.0f;
    if (dropAvoidance) {  // 0x2c4940
        avoidX = kNull.x;
        avoidY = kNull.y;
        avoidZ = kNull.z;
    }
    const float staticRatio = Param(0x5c);
    const float dynamicRatio = Param(0x60);
    const float targetRatio = Param(0x64);
    float ry = ppc::fmadds(targetRatio, ty, ppc::fmadds(dynamicRatio, avoidY, ppc::fmadds(staticRatio, wall.y, kNull.y)));
    float rx = ppc::fmadds(targetRatio, tx, ppc::fmadds(dynamicRatio, avoidX, ppc::fmadds(staticRatio, wall.x, kNull.x)));
    float rz = ppc::fmadds(targetRatio, tz, ppc::fmadds(dynamicRatio, avoidZ, ppc::fmadds(staticRatio, wall.z, kNull.z)));
    float squared = ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry));
    float length = std::sqrt(squared);
    if (length > 1.0f) {  // ble 0x2c4748
        length = 1.0f;
        const float again = std::sqrt(squared);
        if (again != 0.0f) {  // 0x2c4b98
            const float k = 1.0f / again;
            rx = rx * k;
            ry = ry * k;
            rz = rz * k;
            squared = ppc::fmadds(rz, rz, ppc::fmadds(ry, ry, rx * rx));
        }
    }

    // 0x2c4748: the path request (as Move's).
    const int32_t requestBits = pathFinding->m_unk3c;
    bool request = true;
    if ((requestBits & 0x80) != 0 && (requestBits & 0x40) == 0) {
        const bool noWall = wall.x == kNull.x && wall.y == kNull.y && wall.z == kNull.z;
        const bool blocked = length < 0.5f && !noWall && Param(0x58) < distance;  // TOC 0x1948
        if (!blocked && keepPath == 0) {
            request = false;
            if (noWall) {
                pathFinding->RequestPathTo(position, -1);                            // 0x001e1520
                if (pathFinding->m_unk76 != 0xff) pathFinding->CancelPathRequest();  // 0x001e2820
            }
        }
    }
    if (request) {
        pathFinding->RequestPathTo(target, -1);  // 0x001e1520
        pathFinding->Update(position);           // 0x001e2b28
    }

    // 0x2c4788: the original takes the speed's length here and drops it (Math_Sqrtf has no side effect); the force's
    // direction and heading.
    float nx = rx;
    float ny = ry;
    float nz = rz;
    float heading = 0.0f;
    const float forceLength = std::sqrt(squared);
    if (forceLength != 0.0f) {
        const float k = 1.0f / forceLength;
        nz = k * rz;
        nx = k * rx;
        ny = k * ry;
        heading = HeadingOf(nx, nz);
    }
    // 0x2c4810: the goal: the force's heading while the waypoint is followed (not bit 4) or outside +0x50, else
    // `direction`'s.
    float goal = heading;
    const float rotation = Param(0x38);
    if (!(FollowsWaypoint(pathFinding->m_unk3c) && (pathFinding->m_unk3c & 4) == 0) && !(arrival < distance)) {
        goal = HeadingOf(direction->x, direction->z);
    }
    // 0x2c4964: the turn animation from the force's heading.
    {
        const float y0 = *yaw;
        float delta = heading - y0;
        uint32_t anim;
        if (heading > y0) {
            if (!(delta < 5.4977875f)) {         // TOC 0x18a4
                anim = 1;
            } else if (delta >= 3.926991f) {     // TOC 0x18a8
                anim = 7;
            } else if (delta >= 2.3561945f) {    // TOC 0x18ac
                anim = 2;
            } else if (delta < 0.7853982f) {     // TOC 0x18b0
                anim = 1;
            } else {
                anim = 6;
            }
        } else {
            delta = -delta;
            if (!(delta < 5.4977875f)) {
                anim = 1;
            } else if (!(delta < 3.926991f)) {
                anim = 6;
            } else if (!(delta < 2.3561945f)) {
                anim = 2;
            } else if (delta < 0.7853982f) {
                anim = 1;
            } else {
                anim = 7;
            }
        }
        m_eMvtAnim = anim;
    }
    // 0x2c4988: the yaw turned toward the goal by the turn speed, the shorter way.
    {
        const float y0 = *yaw;
        float delta = goal - y0;
        if (delta == 0.0f) {
            if (Param(0x3c) > length) m_eMvtAnim = 0;  // 0x2c4aa8
        } else {
            float speedOfTurn = rotation;
            if (goal > y0) {
                if (!(delta < kPi)) {
                    speedOfTurn = -rotation;
                    delta = kTwoPi - delta;
                }
            } else {
                delta = -delta;  // 0x2c4be0
                if (!(delta < kPi)) {
                    delta = kTwoPi - delta;
                } else {
                    speedOfTurn = -rotation;
                }
            }
            delta = std::fabs(delta);
            const float step = speedOfTurn * *dt;
            const float size = step < 0.0f ? -step : step;
            if (!(delta < size)) {  // bge 0x2c4cb8
                *yaw = y0 + step;
            } else {
                *yaw = goal;
                if (Param(0x3c) > length) m_eMvtAnim = 0;
            }
            float y = *yaw;
            if (y > kTwoPi) {
                y = y - kTwoPi;
                *yaw = y;
            }
            if (y < 0.0f) *yaw = y + kTwoPi;
        }
    }
    // 0x2c4a28: the position along the force's direction by the current speed.
    const float speedLength =
        std::sqrt(ppc::fmadds(speed->z, speed->z, ppc::fmadds(speed->x, speed->x, speed->y * speed->y)));
    const float stepLength = speedLength * *dt;
    position->z = ppc::fmadds(stepLength, nz, position->z);
    position->x = ppc::fmadds(stepLength, nx, position->x);
    position->y = ppc::fmadds(stepLength, ny, position->y);
}

// 0x002c4d38 Steering_ComputeDesiredVelocity_maybe (XXL2 CKHkMoveCpnt::Move). The labels are the original's addresses.
void CKHkMoveCpnt::Move(CVector3* position, float* yaw, CVector3* speed, const CVector3* target, const CVector3* direction,
                        const float* dt, const CGroundContactDatasIn* groundIn, const CKAvoidanceAgent* avoidance,
                        CKPathFindingCpnt* pathFinding, uint8_t mode, SJumpMoveCpnt* jump, uint8_t keepPath,
                        uint8_t staticForce) {
    const CVector3 kNull{0.0f, 0.0f, 0.0f};  // TOC 0x1938: g_nullVector 0x00c50d64
    const float speedLength =
        std::sqrt(ppc::fmadds(speed->z, speed->z, ppc::fmadds(speed->x, speed->x, speed->y * speed->y)));
    float ax = kNull.x, ay = kNull.y, az = kNull.z;  // the forces' sum
    CVector3 wall;
    if ((pathFinding->m_unk3c & 0x40) == 0 || (pathFinding->m_bits70 & 0x400u) != 0) {
        ComputeStaticAvoidForce(position, &wall, pathFinding);  // 0x002c2390
    } else {
        wall = kNull;
    }
    float avoidX = avoidance->m_v0c.x;
    float avoidY = 0.0f;
    float avoidZ = avoidance->m_v0c.z;
    if (jump != nullptr) {
        bool special = false;
        if ((pathFinding->m_unk3c & 0x40) != 0) {
            const uint32_t reach = pathFinding->ClassifyReachability(groundIn);  // 0x001e1be8
            special = reach != 1 && reach != 0x40;
        }
        if (special || jump->m_ui8JumpState != 0) {
            JumpMove(position, yaw, target, dt, pathFinding, jump);  // 0x002bdcf8
            *speed = kNull;
            return;
        }
    }

    // 0x2c4f88: the way to the target (or the path finding's waypoint), the arrival distance +0x4c (+0x50 above the
    // speed +0x20 + 0.05).
    const int32_t bits = pathFinding->m_unk3c;
    float dx;
    float dz;
    if (FollowsWaypoint(bits)) {
        dx = pathFinding->m_vCurrentTarget.x - position->x;
        dz = pathFinding->m_vCurrentTarget.z - position->z;
    } else {
        dx = target->x - position->x;
        dz = target->z - position->z;
    }
    const float distance = std::sqrt(ppc::fmadds(dx, dx, dz * dz));
    const float kMargin = 0.05f;  // TOC 0x1950
    float arrival = Param(0x4c);
    if (Param(0x20) + kMargin < speedLength) arrival = Param(0x50);
    float tx;
    const float ty = 0.0f;
    float tz;
    bool dropAvoidance = false;
    if (distance == 0.0f) {
        tx = kNull.x;
        tz = kNull.z;
        dropAvoidance = !(arrival <= distance) && FollowsWaypoint(bits);
    } else if (arrival < distance) {
        const float k = 1.0f / distance;
        tz = dz * k;
        tx = dx * k;
    } else if (FollowsWaypoint(bits)) {
        const float k = 1.0f / distance;
        tz = dz * k;
        tx = dx * k;
        dropAvoidance = !(arrival <= distance);
    } else {
        // Inside the arrival distance: the target force shrinks with the distance.
        const float k = 1.0f / arrival;
        tz = dz * k;
        tx = dx * k;
    }
    if (dropAvoidance) {  // 0x2c53a4: the waypoint is close: no avoidance
        avoidX = kNull.x;
        avoidY = kNull.y;
        avoidZ = kNull.z;
    }
    if (staticForce != 0) {
        const float ratio = Param(0x5c);  // XXL2 m_fStaticForceRatio
        ax = ppc::fmadds(ratio, wall.x, ax);
        az = ppc::fmadds(ratio, wall.z, az);
        ay = ppc::fmadds(ratio, wall.y, ay);
    }
    const float dynamicRatio = Param(0x60);  // XXL2 m_fDynamicForceRatio
    const float targetRatio = Param(0x64);   // XXL2 m_fTargetForceRatio
    float ry = ppc::fmadds(targetRatio, ty, ppc::fmadds(dynamicRatio, avoidY, ay));
    float rx = ppc::fmadds(targetRatio, tx, ppc::fmadds(dynamicRatio, avoidX, ax));
    float rz = ppc::fmadds(targetRatio, tz, ppc::fmadds(dynamicRatio, avoidZ, az));
    float squared = ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry));
    float length = std::sqrt(squared);
    bool moving;
    if (length <= 1.0f) {
        moving = length > 0.0f;
    } else {
        // At most 1.
        moving = true;
        length = 1.0f;
        const float again = std::sqrt(squared);
        if (again != 0.0f) {
            const float k = 1.0f / again;
            ry = ry * k;
            rx = rx * k;
            rz = rz * k;
            squared = ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry));
        }
    }

    // 0x2c50d0: the path request.
    const int32_t requestBits = pathFinding->m_unk3c;
    bool request = true;
    if ((requestBits & 0x80) != 0 && (requestBits & 0x40) == 0) {
        const bool noWall = wall.x == kNull.x && wall.y == kNull.y && wall.z == kNull.z;
        const bool blocked = length < 0.5f && !noWall && Param(0x58) < distance;  // TOC 0x1948; XXL2 m_fPFDistActivation
        if (!blocked && keepPath == 0) {
            request = false;
            if (noWall) {
                pathFinding->RequestPathTo(position, -1);                       // 0x001e1520
                if (pathFinding->m_unk76 != 0xff) pathFinding->CancelPathRequest();  // 0x001e2820
            }
        }
    }
    if (request) {
        pathFinding->RequestPathTo(target, -1);  // 0x001e1520
        pathFinding->Update(position);           // 0x001e2b28
    }

    // 0x2c5110: the force's heading.
    float nx, ny, nz;
    float heading;
    const float forceLength = std::sqrt(squared);
    if (forceLength == 0.0f) {
        heading = 0.0f;
        nz = rz;
        ny = ry;
        nx = rx;
    } else {
        const float k = 1.0f / forceLength;
        nz = rz * k;
        nx = rx * k;
        ny = ry * k;
        heading = HeadingOf(nx, nz);
    }
    float turn = std::fabs(heading - *yaw);
    if (!(turn <= kPi)) turn = kTwoPi - turn;

    // The mode's target speed (`aim`), acceleration and turn speed.
    float aim = 0.0f;
    float acceleration = 0.0f;
    float rotation = 0.0f;
    float outX = nx, outY = ny, outZ = nz;  // the direction the position moves along
    float limit;
    if (mode == 0) {
        aim = Param(0x3c) < length ? Param(0x20) : 0.0f;
        if (speedLength <= 0.0f) goto L5b10;
        goto L518c;
    }
    if (mode == 1) {
        if (!(Param(0x40) < length)) {
            aim = Param(0x3c) < length ? Param(0x20) : 0.0f;
            limit = Param(0x20);
        } else {
            aim = Param(0x1c);
            limit = Param(0x20);
        }
        if (limit + kMargin < speedLength) goto L5a40;
        if (speedLength <= 0.0f) goto L5b10;
        if (!(Param(0x48) >= turn) && Param(0x1c) == aim) aim = Param(0x20);
        goto L518c;
    }
    if (mode == 2) {
        if (!(Param(0x40) < length)) {
            aim = Param(0x3c) < length ? Param(0x20) : 0.0f;
        } else if (!(Param(0x54) < distance)) {  // XXL2 m_fDistOfBraking
            aim = Param(0x1c);
        } else {
            aim = Param(0x18);
        }
        if (Param(0x1c) + kMargin < speedLength) {
            // 0x2c5664
            if (!(Param(0x44) >= turn)) aim = Param(0x20);
            acceleration = Param(0x24);
            rotation = Param(0x30);
            goto L56a0;
        }
        if (Param(0x20) + kMargin < speedLength) goto L5a40;
        acceleration = Param(0x24);
        rotation = Param(0x30);
        if (speedLength <= 0.0f) goto L5b18;
        if (!(Param(0x48) >= turn) && Param(0x18) == aim) aim = Param(0x20);
        goto L5194;
    }
    // STUB(C2.8): modes above 2 (+0x397) branch on the low byte of an uninitialised register in the original; no DotD
    // enemy is known to use one. Treated as mode 0's turn toward the force.
    DOTD_STUB_ONCE("CKHkMoveCpnt_Move: mode above 2 (C2.8)");
    goto L518c;

L5a40:
    // Faster than the run: slow down along the current heading.
    if (Param(0x44) < turn) aim = Param(0x20);
    acceleration = Param(0x28);
    rotation = Param(0x34);
    goto L56a0;

L518c:
    acceleration = Param(0x2c);
    rotation = Param(0x38);
L5194: {
    // Turn toward the force's heading (or `direction`'s once arrived and not following the waypoint).
    float goal = heading;
    if (!(FollowsWaypoint(pathFinding->m_unk3c) && (pathFinding->m_unk3c & 4) == 0) && !(arrival < distance)) {
        goal = HeadingOf(direction->x, direction->z);
    }
    const float y0 = *yaw;
    const bool left = heading > y0;
    const float delta = left ? heading - y0 : -(heading - y0);
    m_eMvtAnim = TurnAnim(delta, left);
    heading = goal;
    outZ = nz;
    outX = nx;
    goto L57f8;
}

L56a0: {
    // Along the current heading.
    const float y0 = *yaw;
    outX = GameSinf(y0);
    outZ = GameCosf(y0);
    outY = 0.0f;
    m_eMvtAnim = Param(0x1c) >= speedLength ? 3 : 4;
    goto L57f8;
}

L5b10:
    acceleration = Param(0x2c);
    rotation = Param(0x38);
L5b18:
    // Standing: face `direction` (or the force's heading while the waypoint is followed).
    if (!(FollowsWaypoint(pathFinding->m_unk3c) && (pathFinding->m_unk3c & 4) == 0)) {
        heading = HeadingOf(direction->x, direction->z);
    }
    if (!(length <= 0.0f)) {
        const float again = std::sqrt(squared);
        if (again != 0.0f) {
            const float k = 1.0f / again;
            outZ = k * rz;
            outX = rx * k;
            outY = ry * k;
        } else {
            outZ = rz;
            outY = ry;
            outX = rx;
        }
    } else {
        outZ = rz;
        outY = ry;
        outX = rx;
    }
    m_eMvtAnim = 5;

L57f8: {
    // 0x2c57f8: the yaw turned toward `heading` by the turn speed, the shorter way.
    const float y0 = *yaw;
    float delta = heading - y0;
    if (delta != 0.0f) {
        float speedOfTurn = rotation;
        if (heading > y0) {
            if (!(delta < kPi)) {
                speedOfTurn = -rotation;
                delta = kTwoPi - delta;
            }
        } else {
            delta = -delta;
            if (delta >= kPi) {
                delta = kTwoPi - delta;
            } else {
                speedOfTurn = -rotation;
            }
        }
        delta = std::fabs(delta);
        const float step = speedOfTurn * *dt;
        const float size = step < 0.0f ? -step : step;
        if (size <= delta) {
            *yaw = y0 + step;
        } else {
            *yaw = heading;
            if (!(Param(0x3c) <= length)) m_eMvtAnim = 0;
        }
        float y = *yaw;
        if (y > kTwoPi) {
            y = y - kTwoPi;
            *yaw = y;
        }
        if (y < 0.0f) *yaw = y + kTwoPi;
    } else if (!(Param(0x3c) <= length)) {
        m_eMvtAnim = 0;
    }
}
    // 0x2c5888: the speed along the direction.
    float current;
    {
        float sx = speed->x, sy = speed->y, sz = speed->z;
        if (!moving || (aim == 0.0f && sx == kNull.x && sy == kNull.y && sz == kNull.z)) {
            *speed = kNull;  // 0x2c5290
            current = 0.0f;
        } else {
            float ux = sx, uy = sy, uz = sz;
            const float l = std::sqrt(ppc::fmadds(sz, sz, ppc::fmadds(sx, sx, sy * sy)));
            if (l != 0.0f) {
                const float k = 1.0f / l;
                uz = sz * k;
                ux = sx * k;
                uy = sy * k;
            }
            const float along = ppc::fmadds(outZ, uz, ppc::fmadds(ux, outX, outY * uy));
            m_afUnk84[2] = along <= 0.0f ? 0.0f : speedLength;  // the speed kept only going the same way
            m_afUnk84[1] = acceleration;
            m_afUnk84[0] = aim;
            FloatApproach_Step(*dt, m_afUnk84);  // 0x002436e8
            current = m_afUnk84[2];
            const float stepLength = current * *dt;
            position->z = ppc::fmadds(stepLength, outZ, position->z);
            position->x = ppc::fmadds(stepLength, outX, position->x);
            position->y = ppc::fmadds(stepLength, outY, position->y);
            speed->z = current * outZ;
            speed->x = current * outX;
            speed->y = current * outY;
        }
    }
    // 0x2c52ac: the animation's speed ratio.
    switch (m_eMvtAnim) {
        case 0:
        case 5:
        case 10:
            m_fAnimScaleRatio = 1.0f;
            break;
        case 3:
            m_fAnimScaleRatio = current / Param(0x0c);
            break;
        case 4:
            m_fAnimScaleRatio = current / Param(0x10);
            break;
        case 8:
            m_fAnimScaleRatio = 1.0f / Param(0x68);
            break;
        case 9:
            m_fAnimScaleRatio = 1.0f / (Param(0x70) * jump->m_fBirdDist * Param(0x78));
            break;
        case 11:
            m_fAnimScaleRatio = 1.0f / Param(0x6c);
            break;
        default:  // 1, 2, 6, 7: the run
            m_fAnimScaleRatio = current / Param(0x14);
            break;
    }
}

namespace {
// 0x002bea90 NavSteering_TestCellEdgeByNeighborFlags_maybe (the original passes the move component first, unread): the
// 2x2 cells around the point's nearest cell corner, open (1) or not: hiHi (high x, high z), loHi, hiLo, loLo; `corner`
// says which of them holds the point (0 hiHi, 1 loHi, 2 hiLo, 3 loLo), fracZ / fracX its offsets in that cell, half the
// half cell size. In the block's half-cell units (u along z, v along x: 0 the low cells' centre, 2 the high ones') the
// closed cells push: none: no force, 1 returned; all four: no force, 0; one: away from its centre; two on a side: straight
// out of that side; two on a diagonal, or three: toward the open cell (or the open side's) centre. The strength is the
// distance term times half / (half - radius), at most 1; 1 returned.
uint8_t TestCellEdgeByNeighborFlags(uint8_t hiHi, uint8_t loHi, uint8_t hiLo, uint8_t loLo, uint32_t corner, float radius,
                                    float fracZ, float halfZ, float fracX, float halfX, CVector3* force) {
    const float clearance = halfZ - radius;
    const float sizeZ = halfZ + halfZ;
    const float sizeX = halfX + halfX;
    const float scale = halfZ / clearance;
    float z = fracZ;
    float x = fracX;
    if (corner == 1) {
        z = halfZ + fracZ;
        x = fracX - halfX;
    } else if (corner == 0) {
        z = halfZ + fracZ;
        x = halfX + fracX;
    } else if (corner == 2) {
        z = fracZ - halfZ;
        x = halfX + fracX;
    } else if (corner == 3) {
        z = fracZ - halfZ;
        x = fracX - halfX;
    }
    const float u = z / halfZ;
    const float v = x / halfX;
    // Away from the anchor (0x2bebd0) / toward it (0x2bed30, 0x2bef6c).
    auto away = [&](float amount, float ax, float az) -> uint8_t {
        float strength = amount * scale;
        if (strength > 1.0f) strength = 1.0f;
        float dx = x - ax;
        float dy = 0.0f - 0.0f;
        float dz = z - az;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
        force->z = strength * dz;
        force->x = strength * dx;
        force->y = strength * dy;
        return 1;
    };
    auto toward = [&](float amount, float ax, float az) -> uint8_t {
        float strength = amount * scale;
        if (strength > 1.0f) strength = 1.0f;
        float dx = ax - x;
        float dz = az - z;
        float dy = 0.0f;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, 0.0f * 0.0f)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = inverse * 0.0f;
        }
        force->z = strength * dz;
        force->x = strength * dx;
        force->y = strength * dy;
        return 1;
    };
    const uint32_t closed = (hiHi == 0 ? 1u : 0u) + (loHi == 0 ? 1u : 0u) + (hiLo == 0 ? 1u : 0u) + (loLo == 0 ? 1u : 0u);
    switch (closed) {  // the TOC +0x1940 jump table
        case 0:
            *force = CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x1938)
            return 1;
        case 1:
            if (hiHi == 0) return away(v >= u ? u : v, sizeX, sizeZ);
            if (loHi == 0) return away(2.0f - u <= v ? 2.0f - v : u, 0.0f, sizeZ);  // TOC +0x193c: 2.0f
            if (hiLo == 0) return away(v >= 2.0f - u ? 2.0f - u : v, sizeX, 0.0f);
            return away(v >= u ? 2.0f - v : 2.0f - u, 0.0f, 0.0f);
        case 2: {
            // A closed side: straight out of it (TOC +0x1928: -1.0f).
            if (hiHi == 0 && loHi == 0) {
                const float push = scale * u;
                *force = CVector3{0.0f, 0.0f, push > 1.0f ? -1.0f : -push};
                return 1;
            }
            if (hiLo == 0 && loLo == 0) {
                float push = scale * (2.0f - u);
                if (push > 1.0f) push = 1.0f;
                *force = CVector3{0.0f, 0.0f, push};
                return 1;
            }
            if (hiHi == 0 && hiLo == 0) {
                const float push = scale * v;
                *force = CVector3{push > 1.0f ? -1.0f : -push, 0.0f, 0.0f};
                return 1;
            }
            if (loLo == 0 && loHi == 0) {
                float push = scale * (2.0f - v);
                if (push > 1.0f) push = 1.0f;
                *force = CVector3{push, 0.0f, 0.0f};
                return 1;
            }
            // A closed diagonal: toward the centre of the open cell nearer the point.
            if (hiHi == 0 && loLo == 0) {
                if (v >= u) {
                    const float far = 2.0f - v;
                    return toward(u <= far ? far : u, sizeX, 0.0f);
                }
                const float far = 2.0f - u;
                return toward(v >= far ? v : far, 0.0f, sizeZ);
            }
            if (loHi == 0 && hiLo == 0) {
                const float farU = 2.0f - u;
                if (v >= farU) {
                    const float farV = 2.0f - v;
                    return toward(farU <= farV ? farU : farV, sizeX, sizeZ);
                }
                return toward(v >= u ? u : v, 0.0f, 0.0f);
            }
            return 1;  // unreachable: two closed cells always make a side or a diagonal
        }
        case 3:
            if (hiHi != 0) return toward(v >= u ? 2.0f - u : 2.0f - v, sizeX, sizeZ);
            if (loHi != 0) {
                const float far = 2.0f - u;
                return toward(v >= far ? v : far, 0.0f, sizeZ);
            }
            if (hiLo != 0) {
                const float far = 2.0f - v;
                return toward(u <= far ? far : u, sizeX, 0.0f);
            }
            return toward(v >= u ? v : u, 0.0f, 0.0f);
        case 4:
            *force = CVector3{0.0f, 0.0f, 0.0f};
            return 0;
        default:
            return 0;
    }
}
}  // namespace

// 0x002c2390 NavSteering_ComputeWallAvoidance_maybe. The point's node (its hint, FindSectorForPoint; none: no force) and
// cell; the 2x2 cells around the cell corner nearest the point (the point's cell, its two side neighbours and the
// diagonal one) open or not: a cell inside the grid by the walkability palette of the character's mode, one outside it
// when a transition the character may take (bit 0 clear, bit 2 set) leads to a node whose box holds the point moved one
// cell that way and whose arrival box, widened by half a cell, holds it in x / z. TestCellEdgeByNeighborFlags gives the
// force; when it fails (all four closed) the force points (flat, unit length) to the nearest open cell's centre.
void CKHkMoveCpnt::ComputeStaticAvoidForce(const CVector3* position, CVector3* force, CKPathFindingCpnt* pathFinding) {
    StaticAvoidForce(position, force, pathFinding, false);
}

// 0x002bf0d0 NavSteering_ComputeWallAvoidance3D_maybe (Steering_ComputeDesiredVelocity3D's wall force): the same code
// as 0x2c2390 instruction for instruction (compared after relocating the branches), but for the last resort: the force
// toward the nearest open cell keeps its height difference (a 3D unit vector).
void CKHkMoveCpnt::ComputeStaticAvoidForce3D(const CVector3* position, CVector3* force, CKPathFindingCpnt* pathFinding) {
    StaticAvoidForce(position, force, pathFinding, true);
}

// DOTD: the body of 0x2c2390 / 0x2bf0d0 (`threeD`: the latter's fallback).
void CKHkMoveCpnt::StaticAvoidForce(const CVector3* position, CVector3* force, CKPathFindingCpnt* pathFinding,
                                    bool threeD) {
    *force = CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x1938)
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // TOC +0x18dc, +0x6c
    CPFPoint point;
    point.m_unk0c = pathFinding->m_Destination.m_unk0c;  // +0x4c
    point.m_position = *position;
    service->FindSectorForPoint(&point);  // 0x001e5ca0
    const uint16_t hint = point.m_unk0c;
    if (static_cast<int16_t>(hint) == -1) return;
    float fracX = 0.0f;
    float fracZ = 0.0f;
    uint8_t cell[2];
    service->PointToCell(&point, &fracX, &fracZ, cell);  // 0x001e5148
    const uint8_t cellX = cell[0];
    const uint8_t cellZ = cell[1];
    const float size = g_pfGridScale.m_cellSize;  // TOC +0x1944
    const float half = size * 0.5f;               // TOC +0x1948
    const CPFCharacter* character = &pathFinding->m_CharacterType;  // +0x08
    CKPFGraphNode* node = static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[hint]);
    // A cell open or not; `p` is the point moved into it (for a cell outside the grid).
    auto open = [&](uint8_t x, uint8_t z, float px, float py, float pz, bool inside) -> uint8_t {
        CPFGrid& grid = node->m_Sector.m_grid;
        if (inside || (x < grid.m_width && z < grid.m_height)) {
            PathFinding_SetWalkabilityMode(character->m_bits & 7);  // 0x001f1158
            grid.m_ui8DynamicMask = (character->m_bits & 0x800) == 0 ? 0xf7 : 0xff;
            const uint8_t at[2] = {x, z};
            return PFPaletteBlocked(g_pfGridPalette[grid.GetCellFlags(at)]) ? 0 : 1;  // 0x001f0fe0, TOC +0x194c
        }
        for (uint32_t i = 0; i < node->m_ui16TransitionSize; ++i) {
            const CKPFGraphTransition* transition = node->m_ppTransition[i];
            const uint32_t flags = transition->m_baFlags;
            if ((flags & 1) != 0 || (flags & 4) == 0) continue;
            if (transition->AllowsCharacter(character) == 0) continue;  // 0x001f0648
            const CBBox& box = static_cast<const CKPFGraphNode*>(transition->m_pNode)->m_Sector.m_box;
            if (!(box.m_inf.x <= px && box.m_sup.x >= px && box.m_inf.z <= pz && box.m_sup.z >= pz &&
                  box.m_inf.y <= py && box.m_sup.y >= py)) {
                continue;
            }
            const CBBox& arrival = transition->m_aPortals[0].m_ArrivalBox;
            const float margin = g_pfGridScale.m_halfCellSize;  // 0x00c40260 (TOC +0x18e8)
            if (arrival.m_inf.x - margin <= px && margin + arrival.m_sup.x >= px && arrival.m_inf.z - margin <= pz &&
                margin + arrival.m_sup.z >= pz) {
                return 1;
            }
        }
        return 0;
    };
    const float px = position->x;
    const float py = position->y;
    const float pz = position->z;
    // The cells by x (lo / hi) and z (lo / hi) and which of them holds the point.
    uint8_t loX = cellX, hiX = cellX, loZ = cellZ, hiZ = cellZ;
    float loPx = px, hiPx = px, loPz = pz, hiPz = pz;
    uint32_t corner = 0;
    bool known = true;
    if (fracZ >= half && fracX >= half) {
        corner = 3;
        hiX = static_cast<uint8_t>(cellX + 1);
        hiZ = static_cast<uint8_t>(cellZ + 1);
        hiPx = size + px;
        hiPz = size + pz;
    } else if (fracZ <= half && fracX >= half) {
        corner = 1;
        hiX = static_cast<uint8_t>(cellX + 1);
        loZ = static_cast<uint8_t>(cellZ - 1);
        hiPx = size + px;
        loPz = pz - size;
    } else if (fracZ >= half && fracX <= half) {
        corner = 2;
        loX = static_cast<uint8_t>(cellX - 1);
        hiZ = static_cast<uint8_t>(cellZ + 1);
        loPx = px - size;
        hiPz = size + pz;
    } else if (fracZ <= half && fracX <= half) {
        corner = 0;
        loX = static_cast<uint8_t>(cellX - 1);
        loZ = static_cast<uint8_t>(cellZ - 1);
        loPx = px - size;
        loPz = pz - size;
    } else {
        known = false;  // an unordered fraction: all four closed
    }
    uint8_t hiHi = 0, loHi = 0, hiLo = 0, loLo = 0;
    if (known) {
        // The point's cell first, then the z side, the x side and the diagonal (the original's order).
        const bool curHiX = hiX == cellX, curHiZ = hiZ == cellZ;
        const uint8_t sideX = curHiX ? loX : hiX;
        const uint8_t sideZ = curHiZ ? loZ : hiZ;
        const float sidePx = curHiX ? loPx : hiPx;
        const float sidePz = curHiZ ? loPz : hiPz;
        const uint8_t current = open(cellX, cellZ, px, py, pz, true);
        const uint8_t zSide = open(cellX, sideZ, px, py, sidePz, false);
        const uint8_t xSide = open(sideX, cellZ, sidePx, py, pz, false);
        const uint8_t diagonal = open(sideX, sideZ, sidePx, py, sidePz, false);
        auto put = [&](bool atHiX, bool atHiZ, uint8_t value) {
            if (atHiX && atHiZ) hiHi = value;
            else if (!atHiX && atHiZ) loHi = value;
            else if (atHiX) hiLo = value;
            else loLo = value;
        };
        put(curHiX, curHiZ, current);
        put(curHiX, !curHiZ, zSide);
        put(!curHiX, curHiZ, xSide);
        put(!curHiX, !curHiZ, diagonal);
    }
    if (TestCellEdgeByNeighborFlags(hiHi, loHi, hiLo, loLo, corner, character->m_unk04, fracZ, half, fracX, half, force) != 0) {
        return;  // 0x002bea90
    }
    // Every cell around closed: toward the nearest open cell.
    CKPFGraphNode* own = static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[hint]);
    PathFinding_SetWalkabilityMode(character->m_bits & 7);
    own->m_Sector.m_grid.m_ui8DynamicMask = (character->m_bits & 0x800) == 0 ? 0xf7 : 0xff;
    CVector3 nearest;
    own->m_Sector.FindNearestWalkableCell(&point.m_position, &nearest);  // 0x001ed6e0
    const float zero = 0.0f;  // TOC +0x18e4
    if (threeD) {
        const float dy = nearest.y - position->y;
        const float dx = nearest.x - position->x;
        const float dz = nearest.z - position->z;
        force->y = dy;
        force->x = dx;
        force->z = dz;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
        if (length == zero) return;
        const float inverse = 1.0f / length;  // TOC +0x18f8
        force->z = inverse * force->z;
        force->x = inverse * force->x;
        force->y = inverse * force->y;
        return;
    }
    const float dx = nearest.x - position->x;
    const float dz = nearest.z - position->z;
    force->y = zero;
    force->x = dx;
    force->z = dz;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zero)));  // Math_Sqrtf
    if (length == zero) return;
    const float inverse = 1.0f / length;  // TOC +0x18f8
    force->z = inverse * force->z;
    force->x = inverse * force->x;
    force->y = inverse * force->y;
}

// 0x002bdcf8 Steering_StepSpecialTraversal_maybe (XXL2 CKHkMoveCpnt::JumpMove _maybe): the jump between path nodes, a
// state machine on the jump's state byte. 0: the start is the position, the end the ground under the current waypoint
// (probed from the top of its node's box, reach 0 / height 0, masks 1 and 8; kept when nothing is found), the arc length
// the horizontal distance (z squared first, fused) plus the height difference plus twice +0x74; then the take-off (1,
// anim 8, +0x68 seconds) or, without one (ble: NaN too), the flight. 1: the take-off's time runs (cror: done once
// +0x68 <= time). 2 / 3: the flight along the cubic Bezier start, start / end raised to the higher end's height (ble:
// NaN takes the end's) plus +0x74, end, at ratio += dt / (+0x70 x arc) capped at 1 (ble); anim 10 and state 3 from
// ratio +0x78 on (cror), else 9; the position follows; at ratio 1 the landing (4, anim 11, +0x6c seconds) or, without
// one, done (0, anim 0). 4: the landing's time runs (cror). The animation speed (+0x80) is the state's rate (other
// states: by the animation, the jump table at TOC +0x1924). Then the yaw turns toward the jump's heading (end - start,
// normalised unless 0; HeadingOf) by the turn speed (+0x38), the shorter way, wrapped into [0, 2 pi); the path
// finding's target is requested and it is updated from the position.
void CKHkMoveCpnt::JumpMove(CVector3* position, float* yaw, const CVector3* target, const float* dt,
                            CKPathFindingCpnt* pathFinding, SJumpMoveCpnt* jump) {
    float rate = 0.0f;
    bool byAnim = false;
    switch (jump->m_ui8JumpState) {
    case 0: {
        jump->m_v3JumpStartPos = *position;
        CGroundContactDatasIn in;
        in.m_fDeltaMax = 0.0f;
        in.m_fObjectHeight = 0.0f;
        in.m_MasksOfGrdForTest[0] = 1;
        in.m_MasksOfGrdForTest[1] = 8;
        CGroundContactDatasInOut inOut;
        CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
        CVector3 probe;
        probe.x = pathFinding->m_vCurrentTarget.x;
        probe.y = pathFinding->m_vCurrentTarget.y;
        probe.z = pathFinding->m_vCurrentTarget.z;
        probe.y = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[pathFinding->m_unk74])->m_Sector.m_box.m_sup.y;
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &inOut, &probe.x, 1);  // 0x196540
        if (inOut.m_eContactStatus != 3) GroundContact_GetWorldPoint(&inOut, &jump->m_v3JumpEndPos);  // 0x1a70e0
        const CVector3& s = jump->m_v3JumpStartPos;
        const CVector3& e = jump->m_v3JumpEndPos;
        const float dz = s.z - e.z;
        const float dx = s.x - e.x;
        float arc = std::sqrt(ppc::fmadds(dx, dx, dz * dz));
        jump->m_fBirdDist = arc;
        arc = arc + std::fabs(s.y - e.y);
        jump->m_fBirdDist = arc;
        jump->m_fJumpRatio = 0.0f;  // (a word store of 0)
        arc = arc + (Param(0x74) + Param(0x74));
        jump->m_fBirdDist = arc;
        if (!(Param(0x68) > 0.0f)) {  // ble 0x2be348
            jump->m_ui8JumpState = 2;
            m_eMvtAnim = 9;
            rate = 1.0f / ((Param(0x70) * jump->m_fBirdDist) * Param(0x78));
            break;
        }
        jump->m_ui8JumpState = 1;
        m_eMvtAnim = 8;
        rate = 1.0f / Param(0x68);
        break;
    }
    case 1: {
        const float t = jump->m_fJumpRatio + *dt;
        jump->m_fJumpRatio = t;
        if (!(Param(0x68) < t || Param(0x68) == t)) {  // cror lt|eq
            m_eMvtAnim = 8;
            rate = 1.0f / Param(0x68);
            break;
        }
        jump->m_fJumpRatio = 0.0f;
        jump->m_ui8JumpState = 2;
        m_eMvtAnim = 9;
        rate = 1.0f / ((Param(0x70) * jump->m_fBirdDist) * Param(0x78));
        break;
    }
    case 2:
    case 3: {
        const CVector3& s = jump->m_v3JumpStartPos;
        const CVector3& e = jump->m_v3JumpEndPos;
        CVector3 p1 = s;
        CVector3 p2 = e;
        if (!(s.y <= e.y)) {  // ble 0x2be388
            const float y = s.y + Param(0x74);
            p2.y = y;
            p1.y = y;
        } else {
            const float y = e.y + Param(0x74);
            p1.y = y;
            p2.y = y;
        }
        float t = *dt / (Param(0x70) * jump->m_fBirdDist) + jump->m_fJumpRatio;
        jump->m_fJumpRatio = t;
        if (t > 1.0f) {
            t = 1.0f;
            jump->m_fJumpRatio = 1.0f;
        }
        CVector3 out;
        Vec3_CubicBezier(t, &out, &jump->m_v3JumpStartPos, &p1, &p2, &jump->m_v3JumpEndPos);  // 0x10fc0
        if (!(jump->m_fJumpRatio > Param(0x78) || jump->m_fJumpRatio == Param(0x78))) {  // cror gt|eq
            m_eMvtAnim = 9;
        } else {
            jump->m_ui8JumpState = 3;
            m_eMvtAnim = 10;
        }
        position->x = out.x;
        position->z = out.z;
        position->y = out.y;
        if (jump->m_fJumpRatio != 1.0f) {
            byAnim = true;
            break;
        }
        jump->m_fJumpRatio = 0.0f;
        if (!(Param(0x6c) > 0.0f)) {  // ble 0x2be41c
            rate = 1.0f;
            jump->m_ui8JumpState = 0;
            m_eMvtAnim = 0;
            break;
        }
        jump->m_ui8JumpState = 4;
        rate = 1.0f / Param(0x6c);
        m_eMvtAnim = 11;
        break;
    }
    case 4: {
        const float t = jump->m_fJumpRatio + *dt;
        jump->m_fJumpRatio = t;
        if (!(Param(0x6c) < t || Param(0x6c) == t)) {  // cror lt|eq
            rate = 1.0f / Param(0x6c);
            m_eMvtAnim = 11;
            break;
        }
        rate = 1.0f;
        jump->m_ui8JumpState = 0;
        jump->m_fJumpRatio = 0.0f;  // (a word store of 0)
        m_eMvtAnim = 0;
        break;
    }
    default:
        byAnim = true;
        break;
    }
    if (byAnim) {
        // The rate of the current animation (the jump table at TOC +0x1924; above 11: 0 / +0x14).
        switch (m_eMvtAnim) {
        case 0:
        case 5:
        case 10: rate = 1.0f; break;
        case 3: rate = 0.0f / Param(0x0c); break;
        case 4: rate = 0.0f / Param(0x10); break;
        case 8: rate = 1.0f / Param(0x68); break;
        case 9: rate = 1.0f / ((Param(0x70) * jump->m_fBirdDist) * Param(0x78)); break;
        case 11: rate = 1.0f / Param(0x6c); break;
        default: rate = 0.0f / Param(0x14); break;  // 1, 2, 6, 7 and above 11
        }
    }
    m_fAnimScaleRatio = rate;

    // 0x2bddcc: the heading of the jump and the yaw turned toward it.
    float hx = jump->m_v3JumpEndPos.x - jump->m_v3JumpStartPos.x;
    float hz = jump->m_v3JumpEndPos.z - jump->m_v3JumpStartPos.z;
    const float len = std::sqrt(ppc::fmadds(hz, hz, ppc::fmadds(hx, hx, 0.0f)));
    if (len != 0.0f) {
        const float inv = 1.0f / len;
        hz = hz * inv;
        hx = hx * inv;
    }
    const float heading = HeadingOf(hx, hz);
    const float y0 = *yaw;
    float delta = heading - y0;
    float speedOfTurn = Param(0x38);
    if (heading > y0) {  // else ble 0x2bdfe0 (NaN too)
        if (!(delta < kPi)) {
            speedOfTurn = -speedOfTurn;
            delta = kTwoPi - delta;
        }
    } else {
        delta = -delta;
        if (!(delta < kPi)) {
            delta = kTwoPi - delta;
        } else {
            speedOfTurn = -speedOfTurn;
        }
    }
    delta = std::fabs(delta);
    const float step = speedOfTurn * *dt;
    const float size = step < 0.0f ? -step : step;
    float y;
    if (!(delta < size)) {  // bge 0x2bdfd0
        y = y0 + step;
        *yaw = y;
    } else {
        y = heading;
        *yaw = heading;
    }
    if (y > kTwoPi) {
        y = y - kTwoPi;
        *yaw = y;
    }
    if (y < 0.0f) *yaw = y + kTwoPi;
    pathFinding->RequestPathTo(target, -1);  // 0x001e1520
    pathFinding->Update(position);           // 0x001e2b28
}

// 0x002bc7c0 NavSector_ContainsWalkablePoint_maybe
uint8_t NavSector_ContainsWalkablePoint(const CVector3* point, CKPathFindingCpnt* pathFinding) {
    CPFPoint query;
    query.m_position = *point;
    query.m_unk0c = pathFinding->m_Destination.m_unk0c;
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    service->FindSectorForPoint(&query);  // 0x001e5ca0
    const int16_t index = static_cast<int16_t>(query.m_unk0c);
    if (index < 0 || static_cast<uint32_t>(index) >= service->m_Graph.m_ui32GraphNodesSize) return 0;
    const CBBox& box = static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[query.m_unk0c])->m_Sector.m_box;
    const CVector3& p = query.m_position;
    if (!(box.m_inf.x <= p.x) || !(box.m_sup.x >= p.x)) return 0;
    if (!(box.m_inf.z <= p.z) || !(box.m_sup.z >= p.z)) return 0;
    if (!(box.m_inf.y <= p.y) || !(box.m_sup.y >= p.y)) return 0;
    return static_cast<uint8_t>(service->IsPointWalkable(&query, &pathFinding->m_CharacterType));  // 0x001e42d0
}
