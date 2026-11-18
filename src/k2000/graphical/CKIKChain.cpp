// CKIKChain.cpp - reconstructed original translation unit 0x8be38-0x90308 (GAME_TOC1, main_toc1), 50 functions, 29 live.
// Primary class: CKIKChain  key 0x14d  category Graphical  size 0x58  vtable 0xb16b68
// Other owners: Quat (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x8be38  CKIKChain_ConstructJointLimitSet_2_maybe  [dead]
//   [x] 0x8be78  CKIKChain_FreeJointLimitSet_maybe  (CIKConfig::Destroy)
//   [x] 0x8bf10  CKIKChain_ConstructJointLimitSet_maybe  (CIKConfig::CIKConfig)
//   [x] 0x8bf50  CKIKChain_LoadJointLimitSet_maybe  (CIKConfig::Load)
//   [ ] 0x8c210  CKIKChain_SaveJointLimitSet_maybe  [left: save-only: XXL2 CIKConfig::Save; called only by CKIKChain_Save 0x8d4f8 (and its vtable word 0xb465e0)]
//   [x] 0x8c608  Quat_RebuildFromEuler_maybe  (AdjustToConstraint, file-local (XXL2 CJoint::AdjustToConstraint))
//   [x] 0x8c740  CKIKChain_Delete
//   [x] 0x8c790  CKIKChain_vf58  (Initialize)
//   [x] 0x8c7b8  CKIKChain_RecursiveRegistration
//   [x] 0x8c810  CKIKChain_GetJointLimits_maybe  (GetJointByIndex)
//   [x] 0x8c840  CKIKChain_vf50  (GetBoneNumInHierarchy, the header)
//   [ ] 0x8c860  CKIKChain_WriteJointRotationsToHierarchy_maybe  [dead]
//   [ ] 0x8c958  CKIKChain_ReadJointRotationsFromHierarchy_maybe  [dead]
//   [ ] 0x8ca50  RegisterCKIKChainClass
//   [ ] 0x8cac8  _GLOBAL__I_8cac8
//   [ ] 0x8cad8  CKIKChain_BlendHierarchyTowardJointsRateLimited_maybe  [dead]
//   [ ] 0x8cc40  CKIKChain_SolveCCDLimitedBudgetToStoredTarget_maybe  [dead]
//   [ ] 0x8cc98  CKIKChain_SolveCCDLimitedToStoredTarget_maybe  [dead]
//   [ ] 0x8ccf0  CKIKChain_SolveCCDLimitedViaHierarchy_maybe  [dead]
//   [x] 0x8ceb0  CKIKChain_DeleteArray
//   [x] 0x8cf50  CKIKChain_Destroy
//   [x] 0x8d088  CKIKChain_Create
//   [ ] 0x8d0d8  CKIKChain_SetJointLimitRangeZ_maybe  [dead]
//   [ ] 0x8d200  CKIKChain_SetJointLimitRangeY_maybe  [dead]
//   [ ] 0x8d328  CKIKChain_SetJointLimitRangeX_maybe  [dead]
//   [x] 0x8d450  CKIKChain_CreateArray
//   [ ] 0x8d4f8  CKIKChain_Save
//   [x] 0x8d7d8  CKIKChain_Load
//   [x] 0x8db78  CKIKChain_ComputeTargetYaw_maybe  (GetYAngleFromBone)
//   [x] 0x8de08  CKIKChain_ComputeTargetPitch_maybe  (GetXAngleFromBone)
//   [x] 0x8e0a8  CKIKChain_SolveAimJoint_maybe  (SolveAimJoint)
//   [x] 0x8e278  CKIKChain_SolveCCDRateLimited_maybe  (SolveCCDRateLimited)
//   [x] 0x8e578  CKIKChain_Solve_maybe  (UpdateChain)
//   [x] 0x8e840  CKIKChain_ClampToJointLimits_maybe  (ClampToJointLimits)
//   [x] 0x8e948  CKIKChain_RebuildJointMatrices_maybe  (RebuildJointMatrices)
//   [ ] 0x8ea70  CKIKChain_SolveAimJointNodeOnly_maybe  [dead]
//   [x] 0x8ec20  CKIKChain_UpdateJointPositions_maybe  (UpdateJointPositions)
//   [ ] 0x8ee20  CKIKChain_UpdateTipPosition_maybe  [dead]
//   [x] 0x8ef98  CKIKChain_SolveCCDLimited_maybe  (SolveCCDLimited)
//   [x] 0x8f4c0  CKIKChain_SolveCCDUnlimited_maybe  (SolveCCDUnlimited)
//   [x] 0x8f9c8  CKIKChain_SolveCCDLimitedBudget_maybe  (SolveCCDLimitedBudget)
//   [ ] 0x90130  CKIKChain_SetTargetPosition_maybe  [dead]
//   [ ] 0x90150  CKIKChain_SetEnabledAndResetJoints_maybe  [dead]
//   [ ] 0x901f8  CKIKChain_SetEnabledAndActiveSet_maybe  [dead]
//   [ ] 0x90210  CKIKChain_SetSolverCCDLimited_maybe  [dead]
//   [ ] 0x90250  CKIKChain_SetSolverCCDRateLimited_maybe  [dead]
//   [ ] 0x90268  CKIKChain_SetSolverAimJoint_maybe  [dead]
//   [ ] 0x90280  CKIKChain_SetSolverRate_maybe  [dead]
//   [ ] 0x90288  CKIKChain_GetSolverRate_maybe  [dead]
//   [ ] 0x90290  CKIKChain_GetDistanceToTarget_maybe  [dead]
//
//   [x] 0x99c4c0  CKIKChain_GetClassType  [inline]
//   [x] 0x99c4c8  CKIKChain_GetClassID  [inline]
//   [x] 0x99c4d0  CKIKChain_IsKindOfClass  [inline]
//   [x] 0x99c4f8  CKIKChain_Destructor  [inline]
//   [x] 0x99c518  IKKinematicsChain_DeletingDestructor  [inline]
//   [x] 0x99c558  IKKinematicsChain_Destructor  [inline]
//   [x] 0x99c570  CKIKChain_DeletingDestructor  [inline]
#include "k2000/graphical/CKIKChain.h"

#include <cmath>
#include <cstring>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

// C2.8 port-rest R02. No game file holds a CKIKChain; ported from the disassembly (the XXL2 build has the same code
// under the names used here).

namespace {
constexpr float kRadToDeg = 57.2957802f;  // TOC -0x65c0 / -0x6594 (0x42652ee1)

// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// The hierarchy's interpolated frame of node `node` (RtAnimInterpolator +0x50 + node x the frame size).
RpHAnimInterpFrame* InterpFrame(RpHAnimHierarchy* hierarchy, int32_t node) {
    return static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(hierarchy->currentAnim, node));
}
float* FrameQuat(RpHAnimHierarchy* hierarchy, int32_t node) { return &InterpFrame(hierarchy, node)->q.imag.x; }

CMatrix34* AsMatrix34(RwMatrix* m) { return reinterpret_cast<CMatrix34*>(m); }

// ---- local copies (C2.8 port-rest R02): the library atan2f 0x0077e9f0 (crt, not ported) and Quat_ToEulerAngles_maybe
// 0x002424a0 (k2000/math/Quat.cpp, package R01; it needs the atan2f). Replace with the shared ports once they land.

// _FDtest 0x0077ffd8: 2 NaN, 1 infinity, 0 zero, -1 any other value (denormals included).
int32_t FDtest(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    const uint32_t hi = bits >> 16;
    if ((hi & 0x7f80u) == 0x7f80u) return ((hi & 0x7fu) != 0 || (bits & 0xffffu) != 0) ? 2 : 1;
    if ((hi & 0x7fffu) != 0) return -1;
    return (bits & 0xffffu) == 0 ? 0 : -1;
}
bool SignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    return (bits & 0x80000000u) != 0;
}

// _FAtan_maybe 0x0077fe18 (the same body as crt/xatanf.cpp's, whose copy is file-local there).
float FAtan(float x, uint32_t mode) {
    constexpr float kTan15 = 0.2679491937160492f;
    constexpr float kSqrt3 = 1.7320507764816284f;
    constexpr float kA = 0.08280213922262192f;
    constexpr float kB = 0.8483080863952637f;
    constexpr float kC = 0.5149751901626587f;
    constexpr float kEpsilon = 0.000244140625f;
    constexpr float kOctant[8] = {0.0f, 0.5235987901687622f, 1.5707963705062866f, 1.0471975803375244f,
                                  1.5707963705062866f, 2.094395160675049f, 3.1415927410125732f, 2.6179938316345215f};
    if (x > kTan15) {
        mode |= 1;
        const float denominator = x + kSqrt3;
        const float numerator = ppc::fmsubs(x, kSqrt3, 1.0f);
        x = numerator / denominator;
    }
    if (-kEpsilon > x || x > kEpsilon) {
        const float square = x * x;
        const float cube = x * square;
        const float inner = ppc::fmadds(square, kA, kB);
        const float numerator = ppc::fmadds(cube, kC, x);
        const float denominator = ppc::fmadds(square, inner, 1.0f);
        x = numerator / denominator;
    }
    if ((mode & 2) != 0) x = -x;
    x = x + kOctant[mode & 7];
    if ((mode & 8) != 0) x = -x;
    return x;
}

// atan2f 0x0077e9f0 (TocBridge_atan2f 0x98f2c0; library TOC -0x2e78 0.0f, -0x2e7c 1.0f).
float Atan2f(float y, float x) {
    const int32_t xClass = FDtest(x);
    const int32_t yClass = FDtest(y);
    uint32_t mode = 0;
    float r;
    if (xClass <= 0 && yClass <= 0) {
        if (SignBit(y)) {
            y = -y;
            mode = 8;
        }
        if (SignBit(x)) {
            x = -x;
            mode ^= 6;
        }
        if (x >= y) {
            r = xClass == 0 ? 0.0f : y / x;
        } else {
            mode ^= 2;
            r = x / y;
        }
    } else {
        if (yClass == 2) return y;
        if (xClass == 2) return x;
        r = xClass == yClass ? 1.0f : 0.0f;
        mode = SignBit(y) ? 8u : 0u;
        if (SignBit(x)) mode |= 6;
        if (yClass == 1) mode ^= 2;
    }
    return FAtan(r, mode & 0xffffu);
}

// Quat_ToEulerAngles_maybe 0x002424a0: (x, y, z, w) -> three angles in degrees (TOC -0x260 -2, -0x264 1, -0x250 /
// -0x24c +-0.9999, -0x248 57.29578, -0x244 90). Near the poles the middle angle is 90 whatever the sign.
void QuatToEulerAngles(const float* q, float* out) {
    const float x = q[0];
    const float y = q[1];
    const float z = q[2];
    const float w = q[3];
    const float wm2 = w * -2.0f;
    const float y2 = y + y;
    const float x2 = x + x;
    const float xm2 = x * -2.0f;
    const float zm2 = z * -2.0f;
    const float ywm2 = y * wm2;
    const float zy2 = z * y2;
    const float xx1 = ppc::fmadds(x, xm2, 1.0f);
    const float zzm2 = z * zm2;
    const float s = ppc::fnmadds(z, x2, ywm2);
    if (!(s >= 0.999899983f) && s > -0.999899983f) {
        const float root = Sqrtf(1.0f - s * s);
        const float yym2 = y * (y * -2.0f);
        const float w2 = w + w;
        out[1] = Atan2f(s, root) * kRadToDeg;
        const float a = ppc::fmadds(x, w2, zy2);
        const float b = yym2 + xx1;
        out[0] = Atan2f(a / root, b / root) * kRadToDeg;
        const float c = ppc::fmadds(y, x2, z * w2);
        const float d = (yym2 + 1.0f) + zzm2;
        out[2] = Atan2f(c / root, d / root) * kRadToDeg;
        return;
    }
    out[0] = Atan2f(ppc::fnmadds(x, wm2, zy2), zzm2 + xx1) * kRadToDeg;
    const float b = Atan2f(0.0f, 1.0f);
    out[1] = 90.0f;
    out[2] = b * kRadToDeg;
}

// The Euler clamp of CJoint::AdjustToConstraint (0x8c608) and ClampToJointLimits (0x8e840), branch for branch: above
// the maximum takes the maximum, then the minimum unless the maximum is not below it (x, y) / when it is below (z);
// otherwise below the minimum takes it (x, y), or anything not at or above it, NaN included (z).
void ClampEuler(const CJoint* joint, float* e) {
    if (joint->m_bXConstraint != 0) {
        if (e[0] > joint->m_fXMax) {
            e[0] = joint->m_fXMax;
            if (!(e[0] >= joint->m_fXMin)) e[0] = joint->m_fXMin;
        } else if (e[0] < joint->m_fXMin) {
            e[0] = joint->m_fXMin;
        }
    }
    if (joint->m_bYConstraint != 0) {
        if (e[1] > joint->m_fYMax) {
            e[1] = joint->m_fYMax;
            if (!(e[1] >= joint->m_fYMin)) e[1] = joint->m_fYMin;
        } else if (e[1] < joint->m_fYMin) {
            e[1] = joint->m_fYMin;
        }
    }
    if (joint->m_bZConstraint != 0) {
        if (e[2] > joint->m_fZMax) {
            e[2] = joint->m_fZMax;
            if (e[2] < joint->m_fZMin) e[2] = joint->m_fZMin;
        } else if (!(e[2] >= joint->m_fZMin)) {
            e[2] = joint->m_fZMin;
        }
    }
}

// 0x0008c608 Quat_RebuildFromEuler_maybe (XXL2 CJoint::AdjustToConstraint(CQuaternion*)): q to Euler angles, clamped
// to the joint's limits, back to q (Quat_FromEulerDeg).
void AdjustToConstraint(const CJoint* joint, float* q) {
    float e[3];
    QuatToEulerAngles(q, e);
    ClampEuler(joint, e);
    Quat_FromEulerDeg(q, e);
}

// v normalised when its length is not 0 (each component times 1 / length).
void NormalizeIfNotZero(RwV3d* v) {
    const float length = Sqrtf(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    v->z = v->z * inverse;
    v->x = v->x * inverse;
    v->y = v->y * inverse;
}
// The CCD step's dot of the two unit directions (a.y b.y, then a.x b.x, then a.z b.z, fused).
float CcdDot(const RwV3d& a, const RwV3d& b) { return ppc::fmadds(a.z, b.z, ppc::fmadds(a.x, b.x, a.y * b.y)); }
// cross(b, a), each component one fused multiply-subtract.
RwV3d CcdAxis(const RwV3d& a, const RwV3d& b) {
    RwV3d axis;
    axis.z = ppc::fmsubs(b.x, a.y, b.y * a.x);
    axis.y = ppc::fmsubs(b.z, a.x, b.x * a.z);
    axis.x = ppc::fmsubs(b.y, a.z, a.y * b.z);
    return axis;
}
// The squared distance of the end effector to the target ((ey - ty)^2 first, then x, then z, fused).
float SquaredDistance(const CVector3& e, const CVector3& t) {
    const float dy = e.y - t.y;
    const float dx = e.x - t.x;
    const float dz = e.z - t.z;
    return ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
}
}  // namespace

// 0x0008bf10 CKIKChain_ConstructJointLimitSet_maybe
CIKConfig::CIKConfig() {
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64
    m_ui8IndexOfEndEffector = 0;
    m_fDistEE = 0.100000001f;  // TOC -0x6600 (0x3dcccccd)
    m_apJointList = nullptr;
    m_ui8IndexOfBase = 0;
    m_vAddedVector = kNullVector;
}

// 0x0008bf50 CKIKChain_LoadJointLimitSet_maybe
void CIKConfig::Load(IKFile* file, uint8_t count) {
    m_apJointList = new CJoint*[count];  // OperatorNewArray(count * 4)
    uint32_t i = 0;
    while (count != i) {
        CJoint* joint = new CJoint;  // OperatorNew(0x1c)
        joint->m_fXMin = 0.0f;
        joint->m_fXMax = 0.0f;
        joint->m_fYMin = 0.0f;
        joint->m_fYMax = 0.0f;
        joint->m_fZMin = 0.0f;
        joint->m_fZMax = 0.0f;
        joint->m_bXConstraint = 1;
        joint->m_bYConstraint = 1;
        joint->m_bZConstraint = 1;
        ReadRaw(file, &joint->m_bXConstraint, 3);  // the three bytes as stored
        ReadF32LE(file, &joint->m_fXMin);           // one 0x18-byte read, every word swapped
        ReadF32LE(file, &joint->m_fXMax);
        ReadF32LE(file, &joint->m_fYMin);
        ReadF32LE(file, &joint->m_fYMax);
        ReadF32LE(file, &joint->m_fZMin);
        ReadF32LE(file, &joint->m_fZMax);
        m_apJointList[i] = joint;
        i = static_cast<uint8_t>(i + 1);
    }
    ReadU8(file, &m_ui8IndexOfBase);
    ReadU8(file, &m_ui8IndexOfEndEffector);
    ReadF32LE(file, &m_fDistEE);
    ReadF32LE(file, &m_vAddedVector.x);  // one 0xc-byte read, every word swapped
    ReadF32LE(file, &m_vAddedVector.y);
    ReadF32LE(file, &m_vAddedVector.z);
}

// 0x0008be78 CKIKChain_FreeJointLimitSet_maybe
void CIKConfig::Destroy(uint8_t count) {
    for (uint32_t i = 0; i != count; ++i) delete m_apJointList[i];  // OperatorDelete (null skipped)
    delete[] m_apJointList;                                            // OperatorDeleteArray
}

// 0x0008d088 CKIKChain_Create
CKIKChain::CKIKChain()
    : m_i32BoneParent(0),
      m_ui8NumOfConfig(0),
      m_ui8ActiveConfig(0),
      m_apIkConfig(nullptr),
      m_ui8NumOfBone(0),
      m_apIKChainBoneList(nullptr),
      m_vEndEffector{0.0f, 0.0f, 0.0f},
      m_bStarted(0),
      m_eBlendMode(0),
      m_eSolverMode(0),
      m_vTarget{0.0f, 0.0f, 0.0f},
      m_fCCDEpsilon(0.0f),
      m_ui8IterationNum(0),
      m_fSpeed(0.0f),
      m_bRes(0.0f) {}

// 0x0008cf50 CKIKChain_Destroy
void CKIKChain::Destroy() {
    for (uint32_t i = 0; i < m_ui8NumOfBone; ++i) delete m_apIKChainBoneList[i];
    delete[] m_apIKChainBoneList;
    for (uint32_t i = 0; i < m_ui8NumOfConfig; ++i) {
        CIKConfig* config = m_apIkConfig[i];
        config->Destroy(m_ui8NumOfBone);  // 0x0008be78 (before the null test)
        delete config;                    // vt+0x04
    }
    delete[] m_apIkConfig;
}

// 0x0008c7b8 CKIKChain_RecursiveRegistration
void CKIKChain::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x0008d7d8 CKIKChain_Load
int32_t CKIKChain::Load(IKFile* file, int32_t /*type*/) {
    m_ui8ActiveConfig = 0;
    IKFile_ReadRef(file, &m_pNext);
    IKFile_ReadRef(file, &m_pAnimatedNode);
    m_pHierarchy = m_pAnimatedNode->m_pRpHAnimHierarchy;  // node +0x2c
    ReadU8(file, &m_ui8NumOfBone);
    ReadS32LE(file, &m_i32BoneParent);
    ReadU8(file, &m_ui8NumOfConfig);
    m_apIkConfig = new CIKConfig*[m_ui8NumOfConfig];
    m_apIKChainBoneList = new CIKChainBone*[m_ui8NumOfBone];
    for (uint32_t i = 0; i < m_ui8NumOfConfig; i = static_cast<uint8_t>(i + 1)) {
        CIKConfig* config = new CIKConfig;  // OperatorNew(0x1c) + 0x8bf10
        config->Load(file, m_ui8NumOfBone);
        m_apIkConfig[i] = config;
    }
    RwMatrix* matrices = m_pHierarchy->pMatrixArray;  // RpHAnimHierarchyGetMatrixArray
    int32_t parent = m_i32BoneParent;
    for (uint32_t i = 0; i < m_ui8NumOfBone; i = static_cast<uint8_t>(i + 1)) {
        CIKChainBone* bone = new CIKChainBone;  // OperatorNew(0x28): the position and quaternion as the heap has them
        ReadS32LE(file, &bone->m_i32NumInHierarchy);
        bone->m_pParentLTM = &matrices[parent];
        bone->m_pLTM = &matrices[bone->m_i32NumInHierarchy];
        m_apIKChainBoneList[i] = bone;
        parent = bone->m_i32NumInHierarchy;
    }
    ReadU8(file, &m_ui8IterationNum);
    m_bStarted = 0;
    return 1;
}

// 0x0008c790 CKIKChain_vf58
void CKIKChain::Initialize() {
    m_apIKChainBoneList = nullptr;
    m_ui8NumOfConfig = 1;
    m_ui8ActiveConfig = 0;
    m_ui8NumOfBone = 0;
    m_pAnimatedNode = nullptr;
    m_apIkConfig = nullptr;
}

// 0x0008c810 CKIKChain_GetJointLimits_maybe
CJoint* CKIKChain::GetJointByIndex(uint32_t index) const {
    return m_apIkConfig[m_ui8ActiveConfig]->m_apJointList[index & 0xffu];
}

// 0x0008e840 CKIKChain_ClampToJointLimits_maybe
void CKIKChain::ClampToJointLimits(float* angles) { ClampEuler(GetJointByIndex(0), angles); }

// 0x0008e948 CKIKChain_RebuildJointMatrices_maybe. The end index is read again each step.
void CKIKChain::RebuildJointMatrices(int32_t first) {
    RwMatrix* local = RwMatrixCreate();  // RwMatrixCreate_Thunk 0x23fa68
    for (int32_t k = first; static_cast<int32_t>(m_apIkConfig[m_ui8ActiveConfig]->m_ui8IndexOfEndEffector) + 1 > k; ++k) {
        CIKChainBone* bone = m_apIKChainBoneList[k];
        RpHAnimKeyFrameApply(local, InterpFrame(m_pHierarchy, bone->m_i32NumInHierarchy));  // 0x6e84d8
        Mat4_Multiply(AsMatrix34(bone->m_pLTM), AsMatrix34(local), AsMatrix34(bone->m_pParentLTM));  // 0x0023f788
    }
    RwMatrixDestroy(local);  // RwMatrixDestroy_Thunk 0x23f968
}

// 0x0008ec20 CKIKChain_UpdateJointPositions_maybe. BUG(original)? the end effector gets the offset twice: the matrix
// transform of (distance x direction), then the same offset added again.
void CKIKChain::UpdateJointPositions(uint8_t first) {
    for (int32_t k = first; static_cast<int32_t>(m_ui8NumOfBone) > k; ++k) {
        CIKChainBone* bone = m_apIKChainBoneList[k];
        RwV3dTransformPoints(reinterpret_cast<RwV3d*>(&bone->m_v3dPosition),
                             &InterpFrame(m_pHierarchy, bone->m_i32NumInHierarchy)->t, 1, bone->m_pLTM);
    }
    CIKChainBone* end = m_apIKChainBoneList[m_apIkConfig[m_ui8ActiveConfig]->m_ui8IndexOfEndEffector];
    const RwV3d& t = InterpFrame(m_pHierarchy, end->m_i32NumInHierarchy)->t;
    float y = t.y;
    float x = t.x;
    float z = t.z;
    const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z = z * inverse;
        x = x * inverse;
        y = y * inverse;
    }
    CIKConfig* config = m_apIkConfig[m_ui8ActiveConfig];
    const float distance = config->m_fDistEE;
    CVector3 offset;
    offset.z = z * distance;
    offset.x = distance * x;
    offset.y = distance * y;
    Mat4_TransformPoints(AsMatrix34(m_apIKChainBoneList[config->m_ui8IndexOfEndEffector]->m_pLTM), &m_vEndEffector, &offset,
                         1);  // 0x0023f7e8
    m_vEndEffector.x = m_vEndEffector.x + offset.x;
    m_vEndEffector.y = m_vEndEffector.y + offset.y;
    m_vEndEffector.z = m_vEndEffector.z + offset.z;
}

namespace {
// The shared body of SolveCCDLimited 0x8ef98 and SolveCCDUnlimited 0x8f4c0 (they differ by the joint clamp only).
// The first distance test stops at or within the epsilon (NaN stops); the per-step one stops when the epsilon is at or
// above the distance (NaN goes on).
uint8_t SolveCcd(CKIKChain* chain, const CVector3* target, bool limited) {
    int32_t joint = chain->m_apIkConfig[chain->m_ui8ActiveConfig]->m_ui8IndexOfEndEffector;
    CVector3 effector = chain->m_vEndEffector;
    CVector3 goal = *target;
    CVector3 bone = chain->m_apIKChainBoneList[joint]->m_v3dPosition;
    uint32_t iterations = chain->m_ui8IterationNum;
    int32_t step = 0;
    if (iterations == 0 || !(SquaredDistance(effector, goal) > chain->m_fCCDEpsilon)) {
        return iterations != 0 ? 1 : 0;
    }
    for (;;) {
        RwV3d toEffector = {effector.x - bone.x, effector.y - bone.y, effector.z - bone.z};
        RwV3d toGoal = {goal.x - bone.x, goal.y - bone.y, goal.z - bone.z};
        alignas(16) RwMatrix inverse;
        RwMatrixInvert(&inverse, chain->m_apIKChainBoneList[joint]->m_pLTM);
        RwV3d a;
        RwV3d b;
        RwV3dTransformVectors(&a, &toGoal, 1, &inverse);
        RwV3dTransformVectors(&b, &toEffector, 1, &inverse);
        NormalizeIfNotZero(&a);
        NormalizeIfNotZero(&b);
        const float dot = CcdDot(a, b);
        if (!(dot >= 0.999000013f) && dot > -0.999000013f) {  // TOC -0x659c / -0x6598
            RwV3d axis = CcdAxis(a, b);
            const float angle = crt::Acosf(dot) * kRadToDeg;  // TocBridge_Math_Acosf 0x98e1a0
            float* q = FrameQuat(chain->m_pHierarchy, chain->m_apIKChainBoneList[joint]->m_i32NumInHierarchy);
            Quat_Rotate(q, &axis, angle);  // TocBridge_RtQuatRotate_maybe 0x98e200, rwCOMBINEPRECONCAT
            if (limited) AdjustToConstraint(chain->GetJointByIndex(static_cast<uint32_t>(joint)), q);
            chain->RebuildJointMatrices(joint);  // inlined
            chain->UpdateJointPositions(static_cast<uint8_t>(joint));
        }
        joint = joint - 1;
        CIKConfig* config = chain->m_apIkConfig[chain->m_ui8ActiveConfig];
        if (static_cast<int32_t>(config->m_ui8IndexOfBase) > joint) joint = config->m_ui8IndexOfEndEffector;
        ++step;
        iterations = chain->m_ui8IterationNum;
        effector = chain->m_vEndEffector;
        goal = *target;
        bone = chain->m_apIKChainBoneList[joint]->m_v3dPosition;
        if (static_cast<int32_t>(iterations) <= step) break;
        if (chain->m_fCCDEpsilon >= SquaredDistance(effector, goal)) break;
    }
    return static_cast<int32_t>(iterations) != step ? 1 : 0;
}
}  // namespace

// 0x0008ef98 CKIKChain_SolveCCDLimited_maybe
uint8_t CKIKChain::SolveCCDLimited(const CVector3* target) { return SolveCcd(this, target, true); }

// 0x0008f4c0 CKIKChain_SolveCCDUnlimited_maybe
uint8_t CKIKChain::SolveCCDUnlimited(const CVector3* target) { return SolveCcd(this, target, false); }

// 0x0008f9c8 CKIKChain_SolveCCDLimitedBudget_maybe
int32_t CKIKChain::SolveCCDLimitedBudget(const CVector3* target) {
    CIKConfig* config = m_apIkConfig[m_ui8ActiveConfig];
    int32_t joint = config->m_ui8IndexOfEndEffector;
    const int32_t span = static_cast<int32_t>(static_cast<uint8_t>(config->m_ui8IndexOfEndEffector - config->m_ui8IndexOfBase)) + 1;
    const int32_t budget = static_cast<uint8_t>((50 / span) * span);  // divw, mullw, the low byte
    if (budget > 0) {
        CVector3 effector = m_vEndEffector;
        CVector3 bone = m_apIKChainBoneList[joint]->m_v3dPosition;
        int32_t step = 0;
        for (;;) {
            RwV3d toGoal = {target->x - bone.x, target->y - bone.y, target->z - bone.z};
            RwV3d toEffector = {effector.x - bone.x, effector.y - bone.y, effector.z - bone.z};
            alignas(16) RwMatrix inverse;
            RwMatrixInvert(&inverse, m_apIKChainBoneList[joint]->m_pLTM);
            RwV3d a;
            RwV3d b;
            RwV3dTransformVectors(&a, &toGoal, 1, &inverse);
            RwV3dTransformVectors(&b, &toEffector, 1, &inverse);
            NormalizeIfNotZero(&a);
            NormalizeIfNotZero(&b);
            const float dot = CcdDot(a, b);
            bool reached;
            if (!(dot >= 0.995000005f) && dot > -0.995000005f) {  // TOC -0x6590 / -0x658c
                RwV3d axis = CcdAxis(a, b);
                const float angle = crt::Acosf(dot) * kRadToDeg;
                float* q = FrameQuat(m_pHierarchy, m_apIKChainBoneList[joint]->m_i32NumInHierarchy);
                Quat_Rotate(q, &axis, angle);
                AdjustToConstraint(GetJointByIndex(static_cast<uint32_t>(joint)), q);
                RebuildJointMatrices(joint);  // inlined
                UpdateJointPositions(static_cast<uint8_t>(joint));
                reached = false;
            } else {
                // Aligned (or opposite): after the sixth step, reached when this is the end bone.
                reached = step > 5 && m_apIkConfig[m_ui8ActiveConfig]->m_ui8IndexOfEndEffector == joint;
            }
            joint = joint - 1;
            config = m_apIkConfig[m_ui8ActiveConfig];
            if (static_cast<int32_t>(config->m_ui8IndexOfBase) > joint) joint = config->m_ui8IndexOfEndEffector;
            ++step;
            effector = m_vEndEffector;
            bone = m_apIKChainBoneList[joint]->m_v3dPosition;
            if (step == budget) {
                if (reached) return 1;
                break;
            }
            if (reached) return 1;
        }
    }
    // The budget is spent: the end bone's direction to the end effector against its direction to the target.
    config = m_apIkConfig[m_ui8ActiveConfig];
    const CVector3 effector = m_vEndEffector;
    CIKChainBone* end = m_apIKChainBoneList[config->m_ui8IndexOfEndEffector];
    const CVector3 bone = end->m_v3dPosition;
    RwV3d toEffector = {effector.x - bone.x, effector.y - bone.y, effector.z - bone.z};
    RwV3d toGoal = {target->x - bone.x, target->y - bone.y, target->z - bone.z};
    alignas(16) RwMatrix inverse;
    RwMatrixInvert(&inverse, m_apIKChainBoneList[config->m_ui8IndexOfEndEffector]->m_pLTM);
    RwV3d a;
    RwV3d b;
    RwV3dTransformVectors(&a, &toGoal, 1, &inverse);
    RwV3dTransformVectors(&b, &toEffector, 1, &inverse);
    NormalizeIfNotZero(&a);
    NormalizeIfNotZero(&b);
    const float dot = CcdDot(a, b);
    if (dot >= 0.980000019f) return 1;  // TOC -0x6588
    return dot > -0.980000019f ? 0 : 1;  // TOC -0x6584; NaN: 1
}

// 0x0008db78 CKIKChain_ComputeTargetYaw_maybe
float CKIKChain::GetYAngleFromBone() {
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    const RwMatrix* ltm = &m_pAnimatedNode->m_pRwFrame->ltm;  // node +0x04, its frame's LTM (+0x50)
    RwMatrix* boneMatrix = m_pAnimatedNode->GetBoneMatrix(GetBoneNumInHierarchy(0));  // vt+0x50; 0x000c8bd8
    CVector3 d;
    Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(ltm), &d, reinterpret_cast<const CVector3*>(&boneMatrix->pos), 1);
    d.x = m_vTarget.x - d.x;
    d.z = m_vTarget.z - d.z;
    d.y = 0.0f;
    const float length = Sqrtf(ppc::fmadds(d.z, d.z, ppc::fmadds(d.x, d.x, 0.0f)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        d.z = d.z * inverse;
        d.x = d.x * inverse;
        d.y = d.y * inverse;
    }
    CVector3 v;
    Mat4_TransformVectors(reinterpret_cast<const CMatrix34*>(ltm), &v, reinterpret_cast<const CVector3*>(&boneMatrix->at), 1);
    v.y = 0.0f;
    const float length2 = Sqrtf(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, 0.0f)));
    if (length2 != 0.0f) {
        const float inverse = 1.0f / length2;
        v.z = v.z * inverse;
        v.x = v.x * inverse;
        v.y = v.y * inverse;
    }
    const CVector3& up = kAxisY;
    // c = up x v, e = up x c, each component one fused multiply-subtract.
    const float cx = ppc::fmsubs(up.y, v.z, up.z * v.y);
    const float cz = ppc::fmsubs(v.y, up.x, up.y * v.x);
    const float cy = ppc::fmsubs(up.z, v.x, v.z * up.x);
    const float ey = ppc::fmsubs(up.x, cz, up.z * cx);
    const float ex = ppc::fmsubs(up.z, cy, up.y * cz);
    const float ez = ppc::fmsubs(up.y, cx, up.x * cy);
    const float dot = ppc::fmadds(ez, d.z, ppc::fmadds(ex, d.x, ey * d.y));
    if (!(dot < 1.0f)) return 0.0f;  // NaN: 0
    float angle = crt::Acosf(dot) * kRadToDeg;  // TocBridge_Math_Acosf 0x98e1a0
    const float side = ppc::fmadds(cz, d.z, ppc::fmadds(cx, d.x, cy * d.y));
    if (!(side > 0.0f)) angle = -angle;
    return angle;
}

// 0x0008de08 CKIKChain_ComputeTargetPitch_maybe
float CKIKChain::GetXAngleFromBone() {
    const RwMatrix* ltm = &m_pAnimatedNode->m_pRwFrame->ltm;
    const CMatrix34* frame = reinterpret_cast<const CMatrix34*>(ltm);
    RwMatrix* boneMatrix = m_pAnimatedNode->GetBoneMatrix(GetBoneNumInHierarchy(0));
    CVector3 d;
    Mat4_TransformPoints(frame, &d, reinterpret_cast<const CVector3*>(&boneMatrix->pos), 1);
    d.x = m_vTarget.x - d.x;
    d.y = m_vTarget.y - d.y;
    d.z = m_vTarget.z - d.z;
    // The bone's right axis in world space; d loses its component along it.
    CVector3 w;
    Mat4_TransformVectors(frame, &w, reinterpret_cast<const CVector3*>(&boneMatrix->right), 1);
    const float k = ppc::fmadds(w.z, d.z, ppc::fmadds(w.x, d.x, w.y * d.y));
    d.y = d.y - w.y * k;
    d.x = d.x - w.x * k;
    d.z = d.z - w.z * k;
    const float length = Sqrtf(ppc::fmadds(d.z, d.z, ppc::fmadds(d.x, d.x, d.y * d.y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        d.z = d.z * inverse;
        d.x = d.x * inverse;
        d.y = d.y * inverse;
    }
    CVector3 u;
    Mat4_TransformVectors(frame, &u, reinterpret_cast<const CVector3*>(&boneMatrix->at), 1);
    const float dot = ppc::fmadds(d.z, u.z, ppc::fmadds(d.x, u.x, d.y * u.y));
    float angle = crt::Acosf(dot) * kRadToDeg;
    if (!(angle > 0.0f)) return 0.0f;  // NaN: 0
    Mat4_TransformVectors(frame, &w, reinterpret_cast<const CVector3*>(&boneMatrix->up), 1);
    const float side = ppc::fmadds(d.z, w.z, ppc::fmadds(d.x, w.x, d.y * w.y));
    if (side > 0.0f) angle = -angle;
    return angle;
}

// 0x0008e0a8 CKIKChain_SolveAimJoint_maybe
void CKIKChain::SolveAimJoint(IKTime* clock) {
    const int32_t node = m_apIKChainBoneList[0]->m_i32NumInHierarchy;
    float e[3] = {0.0f, 0.0f, 0.0f};
    e[0] = GetXAngleFromBone();
    e[1] = GetYAngleFromBone();
    ClampToJointLimits(e);
    float current[3];
    QuatToEulerAngles(m_apIKChainBoneList[0]->m_QuatFinal, current);
    const float dy = e[1] - current[1];
    const float dx = e[0] - current[0];
    const float dz = e[2] - current[2];
    const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    const float maxStep = (m_fSpeed * 100.0f) * clock->m_afDeltaTime[0];  // TOC -0x65bc 100, clock +0x1c
    if (distance > maxStep) {  // fcmpu, ble: NaN keeps the angles
        const float t = maxStep / distance;
        e[0] = ppc::fmadds(t, e[0] - current[0], current[0]);
        e[2] = ppc::fmadds(t, e[2] - current[2], current[2]);
        e[1] = ppc::fmadds(t, e[1] - current[1], current[1]);
    }
    float q[4];
    Quat_FromEulerDeg(q, e);
    float* frameQuat = FrameQuat(m_pHierarchy, node);
    std::memcpy(frameQuat, q, sizeof(q));
    std::memcpy(m_apIKChainBoneList[0]->m_QuatFinal, q, sizeof(q));
}

// 0x0008e278 CKIKChain_SolveCCDRateLimited_maybe. BUG(original)? the slerp goes from the new pose (t 0) to the last one
// (t 1) with t the squared ratio of the allowed move to the made one.
void CKIKChain::SolveCCDRateLimited(IKTime* clock) {
    for (uint32_t i = 0; i < m_ui8NumOfBone; i = static_cast<uint8_t>(i + 1)) {
        const uint32_t node = GetBoneNumInHierarchy(i);  // vt+0x50
        std::memcpy(FrameQuat(m_pHierarchy, static_cast<int32_t>(node)), m_apIKChainBoneList[i]->m_QuatFinal, 16);
    }
    const CVector3 before = m_vEndEffector;
    SolveCCDLimitedBudget(&m_vTarget);
    const float dy = before.y - m_vEndEffector.y;
    const float dx = before.x - m_vEndEffector.x;
    const float dz = before.z - m_vEndEffector.z;
    const float allowed = m_fSpeed * clock->m_afDeltaTime[0];  // clock +0x1c
    const float allowedSquared = allowed * allowed;
    const float movedSquared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    if (movedSquared > allowedSquared) {  // ble: NaN skips
        float t = allowedSquared / movedSquared;
        if (t > 1.0f) {
            t = 1.0f;
        } else if (!(t >= 0.0f)) {
            t = 0.0f;
        }
        for (uint32_t i = 0; i < m_ui8NumOfBone; i = static_cast<uint8_t>(i + 1)) {
            const uint32_t node = GetBoneNumInHierarchy(i);
            float* q = FrameQuat(m_pHierarchy, static_cast<int32_t>(node));
            Quat_Slerp(t, q, q, m_apIKChainBoneList[i]->m_QuatFinal);  // 0x00242728
        }
    }
    for (uint32_t i = 0; i < m_ui8NumOfBone; i = static_cast<uint8_t>(i + 1)) {
        const uint32_t node = GetBoneNumInHierarchy(i);
        std::memcpy(m_apIKChainBoneList[i]->m_QuatFinal, FrameQuat(m_pHierarchy, static_cast<int32_t>(node)), 16);
    }
}

// 0x0008e578 CKIKChain_Solve_maybe (jump table 0x8e5cc: 0 / 1 -> 0x8e640, 2 / 3 -> 0x8e5e0, 4 -> 0x8e670)
void CKIKChain::UpdateChain(IKTime* clock) {
    if (clock->m_eCurrentState != 0) return;  // clock +0x30
    if (m_bStarted == 0) return;
    switch (static_cast<uint32_t>(m_eSolverMode)) {
    case 0:
    case 1:
        if (m_eBlendMode == 0) {
            SolveCCDRateLimited(clock);
        } else if (m_eBlendMode == 1) {
            m_bRes = static_cast<float>(static_cast<uint8_t>(SolveCCDLimitedBudget(&m_vTarget)));
        }
        break;
    case 2:
    case 3:
        if (m_eBlendMode == 0) {
            m_bRes = static_cast<float>(SolveCCDLimited(&m_vTarget));
        } else if (m_eBlendMode == 1) {
            // The bones' quaternions into the frames from the base to the end effector, the solve, then back.
            for (int32_t k = m_apIkConfig[m_ui8ActiveConfig]->m_ui8IndexOfBase;
                 static_cast<int32_t>(m_apIkConfig[m_ui8ActiveConfig]->m_ui8IndexOfEndEffector) + 1 > k; ++k) {
                CIKChainBone* bone = m_apIKChainBoneList[k];
                std::memcpy(FrameQuat(m_pHierarchy, bone->m_i32NumInHierarchy), bone->m_QuatFinal, 16);
            }
            m_bRes = static_cast<float>(SolveCCDLimited(&m_vTarget));
            for (int32_t k = m_apIkConfig[m_ui8ActiveConfig]->m_ui8IndexOfBase;
                 static_cast<int32_t>(m_apIkConfig[m_ui8ActiveConfig]->m_ui8IndexOfEndEffector) + 1 > k; ++k) {
                CIKChainBone* bone = m_apIKChainBoneList[k];
                std::memcpy(bone->m_QuatFinal, FrameQuat(m_pHierarchy, bone->m_i32NumInHierarchy), 16);
            }
        }
        break;
    case 4:
        if (m_eBlendMode == 0) SolveAimJoint(clock);
        break;
    default:
        break;
    }
    RpHAnimHierarchyUpdateMatrices(m_pHierarchy);  // TocBridge 0x98e1b0
}
