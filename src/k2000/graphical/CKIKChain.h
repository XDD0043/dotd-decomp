// CKIKChain.h - an inverse-kinematics bone chain (key 0x14d, vtable 0xb16b68, size 0x58; XXL2:
// K/KModules/KGL/KinematicsChain/InverseCinematique/CKIKChain.h, the same members in the same order, with CIKConfig,
// CJoint and CIKChainBone). Original unit: CKIKChain.cpp (0x8be38-0x90308). No game file holds one.
//
// The solvers turn the chain's bones (from the active configuration's end effector down to its base) towards the target
// with cyclic coordinate descent, writing the hierarchy's interpolated frames (RpHAnimInterpFrame q) and rebuilding the
// bone matrices; UpdateChain (vt+0x54) picks the solver by m_eSolverMode / m_eBlendMode.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IKKinematicsChain.h"
#include "k2000/math/CMatrix34.h"

struct RwMatrix;

// XXL2 CJoint (0x1c): the Euler limits of one joint, in degrees.
struct CJoint {
    float m_fXMin;          // +0x00
    float m_fXMax;          // +0x04
    float m_fYMin;          // +0x08
    float m_fYMax;          // +0x0c
    float m_fZMin;          // +0x10
    float m_fZMax;          // +0x14
    uint8_t m_bXConstraint;  // +0x18
    uint8_t m_bYConstraint;  // +0x19
    uint8_t m_bZConstraint;  // +0x1a
    uint8_t m_pad1b;
};
DOTD_ASSERT_SIZE(CJoint, 0x1c);

// XXL2 CIKConfig (vtable 0xb16b58, 0x1c): a joint list over the bones, the base / end-effector bone indices, the end
// effector's distance and an added vector.
class CIKConfig {
public:
    // 0x0008bf10 CKIKChain_ConstructJointLimitSet_maybe (XXL2 CIKConfig::CIKConfig): no joints, indices 0, distance 0.1,
    // the added vector g_nullVector (0x00c50d64).
    CIKConfig();
    virtual ~CIKConfig() {}  // vt+0x00 / +0x04 0x99c490 / 0x99c460: the vtable only
    // 0x0008bf50 CKIKChain_LoadJointLimitSet_maybe (XXL2 CIKConfig::Load(IKFile*, UInt8)): `count` joints (each: the
    // three constraint bytes, then the six limits), then the two indices, the distance and the added vector.
    void Load(IKFile* file, uint8_t count);
    // 0x0008be78 CKIKChain_FreeJointLimitSet_maybe (XXL2 CIKConfig::Destroy(UInt8)): the `count` joints deleted, then the
    // list (not cleared).
    void Destroy(uint8_t count);

    CJoint** m_apJointList;            // +0x04 OperatorNewArray(count * 4)
    uint8_t m_ui8IndexOfBase;          // +0x08
    uint8_t m_ui8IndexOfEndEffector;   // +0x09
    uint8_t m_pad0a[2];
    float m_fDistEE;                   // +0x0c
    CVector3 m_vAddedVector;           // +0x10
};
DOTD_ASSERT_SIZE(CIKConfig, 0x1c);

// XXL2 CIKChainBone (0x28): the bone's position, its hierarchy node, its and its parent's matrix in the hierarchy's
// matrix array, and its last solved quaternion (x, y, z, w).
struct CIKChainBone {
    CVector3 m_v3dPosition;       // +0x00
    int32_t m_i32NumInHierarchy;  // +0x0c
    RwMatrix* m_pLTM;             // +0x10
    RwMatrix* m_pParentLTM;       // +0x14
    float m_QuatFinal[4];         // +0x18
};
DOTD_ASSERT_SIZE(CIKChainBone, 0x28);

class CKIKChain : public IKKinematicsChain {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x99c4d0
        return key == 0x14d || key == 0x10d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKIKChain)

    // 0x0008d088 CKIKChain_Create: operator new(0x58), the base (the next link null), the vtable. The rest is left as
    // the heap has it (Load sets it); zeroed here (the port's fresh heap).
    CKIKChain();
    ~CKIKChain() override {}  // vt+0x00 / +0x04 0x99c4f8 / 0x99c570: the vtables only

    // vt+0x10 0x0008cf50 CKIKChain_Destroy: every bone deleted and the bone list, then every configuration's joints
    // (CIKConfig::Destroy with the bone count; no null test) and the configuration itself (its deleting destructor),
    // then the configuration list. Nothing is cleared.
    void Destroy() override;
    // vt+0x24 0x0008c7b8 CKIKChain_RecursiveRegistration: itself registered with the saving manager (engine +0x50,
    // vt+0x24 with a null second argument), every type.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x0008d7d8 CKIKChain_Load (every type): the next link and the node (references), the node's hierarchy,
    // the bone count, the parent bone, the configuration count and the configurations, the bones (each its hierarchy
    // node and its and its parent's matrix), the iteration count; not started.
    int32_t Load(IKFile* file, int32_t type) override;

    // vt+0x50 0x0008c840 CKIKChain_vf50 (XXL2 GetBoneNumInHierarchy).
    uint32_t GetBoneNumInHierarchy(uint32_t bone) override {
        return static_cast<uint32_t>(m_apIKChainBoneList[bone]->m_i32NumInHierarchy);
    }
    // vt+0x54 0x0008e578 CKIKChain_Solve_maybe (XXL2 UpdateChain): while the clock runs and the chain is started, the
    // solver of m_eSolverMode (0 / 1: rate-limited CCD (blend 0) or the budgeted CCD (blend 1); 2 / 3: the limited CCD,
    // with blend 1 the bones' quaternions put in and taken back; 4: the aim joint (blend 0)), then the hierarchy's
    // matrices (RpHAnimHierarchyUpdateMatrices).
    void UpdateChain(IKTime* clock) override;
    // vt+0x58 0x0008c790 CKIKChain_vf58 (XXL2 Initialize): no bones, one configuration (none allocated), the first one
    // active, no node.
    virtual void Initialize();

    // 0x0008c810 CKIKChain_GetJointLimits_maybe (XXL2 GetJointByIndex): the active configuration's joint `index` (the
    // low byte).
    CJoint* GetJointByIndex(uint32_t index) const;
    // 0x0008db78 CKIKChain_ComputeTargetYaw_maybe (XXL2 GetYAngleFromBone) / 0x0008de08 CKIKChain_ComputeTargetPitch_maybe
    // (XXL2 GetXAngleFromBone): the signed angle (degrees) between the first bone's axis and the target, in the
    // horizontal plane / in the bone's vertical plane.
    float GetYAngleFromBone();
    float GetXAngleFromBone();
    // 0x0008e0a8 CKIKChain_SolveAimJoint_maybe (XXL2 UpdateIKDirectAimAtMode): the first bone aimed at the target (the
    // clamped pitch and yaw), moving at most m_fSpeed x 100 degrees per second.
    void SolveAimJoint(IKTime* clock);
    // 0x0008e278 CKIKChain_SolveCCDRateLimited_maybe (XXL2 UpdateIKBlendMode): the budgeted solve from the bones' last
    // quaternions; when the end effector moved more than m_fSpeed x dt, every frame slerped back towards the last
    // quaternion; the bones keep the result.
    void SolveCCDRateLimited(IKTime* clock);
    // 0x0008e840 CKIKChain_ClampToJointLimits_maybe: the Euler angles clamped to joint 0's limits.
    void ClampToJointLimits(float* angles);
    // 0x0008e948 CKIKChain_RebuildJointMatrices_maybe (XXL2 UpdateMatrices): from bone `first` to the end effector,
    // each bone's matrix = its frame's matrix x its parent's (the solvers inline it).
    void RebuildJointMatrices(int32_t first);
    // 0x0008ec20 CKIKChain_UpdateJointPositions_maybe (XXL2 UpdatePosition + UpdateEndEffector): the bones from `first`
    // on placed (their frame translation through their matrix), then the end effector from the end bone's matrix.
    void UpdateJointPositions(uint8_t first);
    // 0x0008ef98 CKIKChain_SolveCCDLimited_maybe (XXL2 IKSolverCCD) / 0x0008f4c0 CKIKChain_SolveCCDUnlimited_maybe (XXL2
    // IKSolverCCDWithoutConstraint): CCD towards `target` for m_ui8IterationNum steps or until within m_fCCDEpsilon
    // (squared), the joints clamped to their limits in the first; 1 when it stopped before the last step.
    uint8_t SolveCCDLimited(const CVector3* target);
    uint8_t SolveCCDUnlimited(const CVector3* target);
    // 0x0008f9c8 CKIKChain_SolveCCDLimitedBudget_maybe (XXL2 IKAimAtSolverCCD): CCD for (50 / bones) x bones steps,
    // stopping after the sixth step once the end effector is reached; 1 when aimed (or the end bone's direction is
    // within 0.98 of the target's, or opposite).
    int32_t SolveCCDLimitedBudget(const CVector3* target);

    int32_t m_i32BoneParent;              // +0x10 the hierarchy node above the first bone
    uint8_t m_ui8NumOfConfig;             // +0x14
    uint8_t m_ui8ActiveConfig;            // +0x15 Load sets 0
    uint8_t m_pad16[2];
    CIKConfig** m_apIkConfig;             // +0x18 OperatorNewArray(count * 4)
    uint8_t m_ui8NumOfBone;               // +0x1c
    uint8_t m_pad1d[3];
    CIKChainBone** m_apIKChainBoneList;   // +0x20 OperatorNewArray(count * 4)
    CVector3 m_vEndEffector;              // +0x24
    uint8_t m_bStarted;                   // +0x30 Load sets 0
    uint8_t m_pad31[3];
    int32_t m_eBlendMode;                 // +0x34 XXL2 E_ANIMATION_MODE
    int32_t m_eSolverMode;                // +0x38 XXL2 E_SOLVER_MODE
    CVector3 m_vTarget;                   // +0x3c
    float m_fCCDEpsilon;                  // +0x48 compared with the squared distance
    uint8_t m_ui8IterationNum;            // +0x4c read
    uint8_t m_pad4d[3];
    float m_fSpeed;                       // +0x50
    float m_bRes;                         // +0x54 XXL2 Float32 m_bRes: the last solver's answer (0 / 1)
};
DOTD_ASSERT_SIZE(CKIKChain, 0x58);
DOTD_ASSERT_OFFSET(CKIKChain, m_i32BoneParent, 0x10);
DOTD_ASSERT_OFFSET(CKIKChain, m_apIkConfig, 0x18);
DOTD_ASSERT_OFFSET(CKIKChain, m_ui8NumOfBone, 0x1c);
DOTD_ASSERT_OFFSET(CKIKChain, m_apIKChainBoneList, 0x20);
DOTD_ASSERT_OFFSET(CKIKChain, m_vEndEffector, 0x24);
DOTD_ASSERT_OFFSET(CKIKChain, m_bStarted, 0x30);
DOTD_ASSERT_OFFSET(CKIKChain, m_eBlendMode, 0x34);
DOTD_ASSERT_OFFSET(CKIKChain, m_vTarget, 0x3c);
DOTD_ASSERT_OFFSET(CKIKChain, m_ui8IterationNum, 0x4c);
DOTD_ASSERT_OFFSET(CKIKChain, m_bRes, 0x54);
