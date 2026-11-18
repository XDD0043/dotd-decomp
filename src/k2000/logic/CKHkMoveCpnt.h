// CKHkMoveCpnt.h - the movement parameters of an enemy (key 0x300c, vtable 0xb22630, size 0xac). Original
// unit: CKHkMoveCpnt.cpp. XXL2: Commun/K/KSquad/CKHkMoveCpnt.h (m_fRadius ... m_fJumpFallStartRatio: 27
// floats, then m_eMvtAnim, m_fAnimScaleRatio, m_sfSpeed, m_sv3Speed). DotD reads 30 floats, so the floats do
// not map one to one onto XXL2's names; the two words its Load sets after them keep XXL2's names (_maybe).
// Embedded in CKEnemyCpnt (+0x08) and CKS08EnemyCpnt (+0x37c); no KP3 file holds one on its own.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKPathFindingCpnt;
struct CGroundContactDatasIn;
struct CKAvoidanceAgent;

// XXL2 SJumpMoveCpnt (Commun/K/KSquad/CKHkMoveCpnt.h, 0x24 bytes): the state of a jump between path nodes; Move reads
// the state byte, JumpMove (0x2bdcf8) all of it. No DotD enemy passes one yet.
struct SJumpMoveCpnt {
    uint8_t m_ui8JumpState;     // +0x00 (XXL2) 0 start, 1 take-off, 2 / 3 flight, 4 landing
    uint8_t m_pad01[3];
    float m_fJumpRatio;         // +0x04 (XXL2) the take-off / landing time, the flight's ratio
    float m_fBirdDist;          // +0x08 (XXL2) the arc length
    CVector3 m_v3JumpStartPos;  // +0x0c (XXL2)
    CVector3 m_v3JumpEndPos;    // +0x18 (XXL2)
};

class CKHkMoveCpnt : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc0)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x300c || key == 0xc; }  // vt+0x08 0x9bcfd8
    DOTD_DECLARE_FACTORIES(CKHkMoveCpnt)

    // 0x002bc9c0 CKHkMoveCpnt_Create: the vtable and three 0.0f (TOC 0x18e4) at +0x84..+0x8c.
    CKHkMoveCpnt() {
        m_afUnk84[0] = 0.0f;
        m_afUnk84[2] = 0.0f;
        m_afUnk84[1] = 0.0f;
    }
    ~CKHkMoveCpnt() override {}

    // vt+0x2c 0x002bcc98 CKHkMoveCpnt_Load: 30 floats for K_LEVEL_PLATEFORMS, then +0x7c = 0, +0x80 = 1.0.
    int32_t Load(IKFile* file, int32_t type) override;

    // 0x002c4d38 Steering_ComputeDesiredVelocity_maybe (XXL2 CKHkMoveCpnt::Move; DotD passes the ground data, the
    // path-finding flag `keepPath` and `staticForce` as well): one ground step toward `target` (or the path finding's
    // waypoint while it is followed): the target, avoidance (+0x0c of the agent) and wall forces (static, when
    // `staticForce`) weighted by +0x64 / +0x60 / +0x5c, the path request kept up to date, `yaw` turned toward the
    // force's heading (or `direction`'s), the speed approaching the mode's target (FloatApproach at +0x84), the
    // position moved along the heading; the movement animation (+0x7c) and its speed ratio (+0x80) chosen.
    void Move(CVector3* position, float* yaw, CVector3* speed, const CVector3* target, const CVector3* direction,
              const float* dt, const CGroundContactDatasIn* groundIn, const CKAvoidanceAgent* avoidance,
              CKPathFindingCpnt* pathFinding, uint8_t mode, SJumpMoveCpnt* jump, uint8_t keepPath, uint8_t staticForce);
    // 0x002c4430 Steering_ComputeDesiredVelocityNoTurnSmoothing_maybe: Move's forces, path request and turn without the
    // speed control (the burning run): the position moves along the force by the current speed's length; `mode` unread.
    void MoveNoTurnSmoothing(CVector3* position, float* yaw, CVector3* speed, const CVector3* target,
                             const CVector3* direction, const float* dt, const CGroundContactDatasIn* groundIn,
                             const CKAvoidanceAgent* avoidance, CKPathFindingCpnt* pathFinding, uint8_t mode,
                             SJumpMoveCpnt* jump, uint8_t keepPath);
    // 0x002c1180 Steering_ComputeDesiredVelocity3D_maybe: Move in three dimensions (the flying enemies): the 3D wall
    // force, the avoidance's y, a unit target force at the target's height, the position moved along the force's 3D
    // direction (see the definition).
    void Move3D(CVector3* position, float* yaw, CVector3* speed, const CVector3* target, const CVector3* direction,
                const float* dt, const CGroundContactDatasIn* groundIn, const CKAvoidanceAgent* avoidance,
                CKPathFindingCpnt* pathFinding, uint8_t mode, SJumpMoveCpnt* jump, uint8_t keepPath, uint8_t staticForce);
    // 0x002bf0d0 NavSteering_ComputeWallAvoidance3D_maybe: ComputeStaticAvoidForce with a 3D last resort.
    void ComputeStaticAvoidForce3D(const CVector3* position, CVector3* force, CKPathFindingCpnt* pathFinding);
    // DOTD: the shared body of the two.
    void StaticAvoidForce(const CVector3* position, CVector3* force, CKPathFindingCpnt* pathFinding, bool threeD);
    // 0x002c2390 NavSteering_ComputeWallAvoidance_maybe (XXL2 CKHkMoveCpnt::ComputeStaticAvoidForce): the push away
    // from the unwalkable cells around `position`.
    void ComputeStaticAvoidForce(const CVector3* position, CVector3* force, CKPathFindingCpnt* pathFinding);
    // 0x002bdcf8 Steering_StepSpecialTraversal_maybe (XXL2 CKHkMoveCpnt::JumpMove _maybe): the jump between nodes.
    void JumpMove(CVector3* position, float* yaw, const CVector3* target, const float* dt, CKPathFindingCpnt* pathFinding,
                  SJumpMoveCpnt* jump);
    // A movement parameter by its offset in the object (+0x04..+0x78), as the original reads them.
    float Param(uint32_t offset) const { return m_afParams[(offset - 4) / 4]; }

    float m_afParams[30];      // +0x04..+0x78 XXL2 m_fRadius, m_fAnimRunSpeed, ... (DotD has three more)
    uint32_t m_eMvtAnim;       // +0x7c _maybe XXL2 EEnemyMvtAnim m_eMvtAnim (the Load sets 0)
    float m_fAnimScaleRatio;   // +0x80 _maybe XXL2 m_fAnimScaleRatio (the Load sets 1.0, as XXL2's)
    float m_afUnk84[3];        // +0x84 the constructor sets 0.0 (XXL2 m_sfSpeed _maybe)
    uint32_t m_unk90[7];       // +0x90..+0xa8 run-time state
};

// 0x002bc7c0 NavSector_ContainsWalkablePoint_maybe (CKHkMoveCpnt.cpp's unit; no bl caller, its descriptor only): the graph
// node holding `point` (NavSectors_FindSectorForPoint from the path-finding component's destination hint +0x4c); 1 when
// that node's box holds the point (each bound with cror: a NaN fails) and the point is walkable for the component's
// character (+0x08; NavSectors_IsPointWalkable), else 0.
uint8_t NavSector_ContainsWalkablePoint(const CVector3* point, CKPathFindingCpnt* pathFinding);

static_assert(CKHkMoveCpnt::kClassKey == 0x300c, "key");
DOTD_ASSERT_SIZE(CKHkMoveCpnt, 0xac);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_afParams, 0x04);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_eMvtAnim, 0x7c);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_fAnimScaleRatio, 0x80);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_afUnk84, 0x84);
