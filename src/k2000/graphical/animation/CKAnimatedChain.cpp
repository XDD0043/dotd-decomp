// CKAnimatedChain.cpp - reconstructed original translation unit 0x90308-0x92830 (GAME_TOC1, main_toc1), 36 functions, 18 live.
// Primary class: CKAnimatedChain  key 0x18d  category Graphical  size 0x6c  vtable 0xb16c30
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x90308  CKAnimatedChain_Delete
//   [x] 0x90358  CKAnimatedChain_RecursiveRegistration
//   [ ] 0x903b0  CKAnimatedChain_CapturePoseFromHierarchy_maybe  [dead]
//   [ ] 0x90440  CKAnimatedChain_FindAxisInterval_maybe  [dead]
//   [ ] 0x90610  CKAnimatedChain_SetTargetCoords_maybe  [dead]
//   [ ] 0x90630  CKAnimatedChain_SetInitialApproachSpeed_maybe  [dead]
//   [ ] 0x90638  CKAnimatedChain_GetInitialApproachSpeed_maybe  [dead]
//   [ ] 0x90640  CKAnimatedChain_SetApproachAcceleration_maybe  [dead]
//   [ ] 0x90648  CKAnimatedChain_GetApproachAcceleration_maybe  [dead]
//   [x] 0x90650  CKAnimatedChain_vf50  (GetBoneNumInHierarchy, the header)
//   [ ] 0x90668  FUN_00090668  [dead]
//   [ ] 0x90678  FUN_00090678  [dead]
//   [ ] 0x90680  FUN_00090680  [dead]
//   [ ] 0x90690  RegisterCKAnimatedChainClass
//   [ ] 0x90708  _GLOBAL__I_90708
//   [x] 0x90718  CKAnimatedChain_DeleteArray
//   [ ] 0x907b8  FUN_000907b8  [dead]
//   [x] 0x907e0  CKAnimatedChain_SampleBlendGridLayered_maybe  (SampleBlendGridLayered)
//   [x] 0x909c8  CKAnimatedChain_SampleBlendGrid_maybe  (SampleBlendGrid)
//   [ ] 0x90b00  CKAnimatedChain_BlendPoseIntoHierarchy_maybe  [dead]
//   [x] 0x90be8  CKAnimatedChain_Create
//   [x] 0x90c38  CKAnimatedChain_Destroy
//   [ ] 0x90ce0  FUN_00090ce0  [dead]
//   [ ] 0x90d30  FUN_00090d30  [dead]
//   [ ] 0x90d68  CKAnimatedChain_ResizeAxisKeysAndPoseBuffers_maybe  [dead]
//   [x] 0x90f50  CKAnimatedChain_CreateArray
//   [ ] 0x91000  FUN_00091000  [dead]
//   [ ] 0x91048  CKAnimatedChain_SetActive_maybe  [dead]
//   [x] 0x910a8  CKAnimatedChain_ApproachTargetBlend_maybe  (BlendBeforeStop)
//   [x] 0x91298  CKAnimatedChain_Load
//   [ ] 0x91678  CKAnimatedChain_Save
//   [x] 0x91950  CKAnimatedChain_ComputeTargetCoordsFromBones_maybe  (InterpolationAimAtSolver)
//   [x] 0x91d08  CKAnimatedChain_SampleAtCoords_maybe  (SampleAtCoords)
//   [ ] 0x921c0  CKAnimatedChain_SetCoordsAndSample_maybe  [dead]
//   [x] 0x92270  CKAnimatedChain_StepToTargetCoords_maybe  (UpDateInterpolationAimAtMode)
//   [x] 0x92610  CKAnimatedChain_Update_maybe  (UpdateChain)
//
//   [x] 0x99c5b8  CKAnimatedChain_GetClassType  [inline]
//   [x] 0x99c5c0  CKAnimatedChain_GetClassID  [inline]
//   [x] 0x99c5c8  CKAnimatedChain_IsKindOfClass  [inline]
//   [x] 0x99c5f0  CKAnimatedChain_DeletingDestructor  [inline]
//   [x] 0x99c638  CKAnimatedChain_Destructor  [inline]
//   [ ] 0x99c658  IScreenFx_vf8  [inline]
//   [ ] 0x99c680  IScreenFx_vf14  [inline]
//   [ ] 0x99c688  IScreenFx_vf18  [inline]
//   [ ] 0x99c690  IScreenFx_vf24  [inline]
//   [ ] 0x99c698  IScreenFx_vf30  [inline]
//   [ ] 0x99c6a0  IScreenFx_vf34  [inline]
#include "k2000/graphical/animation/CKAnimatedChain.h"

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

// C2.8 port-rest R02. No game file holds a CKAnimatedChain; ported from the disassembly.

namespace {
constexpr float kDegToRad = 0.0174532905f;  // TOC -0x653c (0x3c8efa34)
constexpr float kRadToDeg = 57.2957802f;    // TOC -0x652c (0x42652ee1)

// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// Node `node`'s interpolated frame quaternion (RtAnimInterpolator +0x50 + node x the frame size, + 8).
float* FrameQuat(RpHAnimHierarchy* hierarchy, uint32_t node) {
    return &static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(hierarchy->currentAnim, static_cast<RwInt32>(node)))
                ->q.imag.x;
}

// The angle step of BlendBeforeStop / UpDateInterpolationAimAtMode: the distance (in radians) from the angles to the
// target angles, each difference one fused multiply-subtract (target x k - angle x k).
float AngleDistance(const CKAnimatedChain* chain) {
    const float y = chain->m_fYAngle * kDegToRad;
    const float x = chain->m_fXAngle * kDegToRad;
    const float dy = ppc::fmsubs(chain->m_fYTargetAngle, kDegToRad, y);
    const float dx = ppc::fmsubs(chain->m_fXTargetAngle, kDegToRad, x);
    return Sqrtf(ppc::fmadds(dx, dx, dy * dy));
}

// The accelerated speed: speed + speed^2 x acceleration x dt (fused).
float Accelerate(const CKAnimatedChain* chain, float dt) {
    const float speed = chain->m_fCurrentSpeed;
    return ppc::fmadds(speed * (speed * chain->m_fSpeedUp), dt, speed);
}

// One axis of SampleAtCoords: `value` clamped into keys[0 .. count - 1] (overran is set then), the cell and the fraction
// in it (clamped to 0 .. 1; a NaN fraction becomes 0). Below the first key: cell 0, fraction 0; above the last: cell
// count - 2, fraction 1. The search falls back to cell 0 when no key is at or above the value.
void AxisCell(const float* keys, uint32_t count, float* value, bool* overran, int32_t* cell, float* fraction) {
    if (keys[0] > *value) {
        *overran = true;
        *fraction = 0.0f;
        *cell = 0;
        *value = keys[0];
        return;
    }
    if (keys[count - 1] < *value) {
        *overran = true;
        *fraction = 1.0f;
        *value = keys[count - 1];
        *cell = static_cast<int32_t>(count) - 2;
        return;
    }
    *overran = false;
    const float v = *value;
    int32_t index = 0;
    if (count > 1 && !(keys[1] >= v)) {
        for (uint32_t k = 2; k < count; ++k) {
            if (keys[k] >= v) {
                index = static_cast<int32_t>(k) - 1;
                break;
            }
        }
    }
    float t = (v - keys[index]) / (keys[index + 1] - keys[index]);
    if (t > 1.0f) {
        t = 1.0f;
    } else if (!(t >= 0.0f)) {
        t = 0.0f;
    }
    *cell = index;
    *fraction = t;
}
}  // namespace

// 0x00090be8 CKAnimatedChain_Create
CKAnimatedChain::CKAnimatedChain()
    : m_ui8NumOfBone(0),
      m_ui8NumOfKeyByAxe(0),
      m_ui8BoneRef(0),
      m_i8NumBoneForPosRef(0),
      m_pTabOfBoneNum(nullptr),
      m_pfAngleValues{nullptr, nullptr},
      m_fYTargetAngle(0.0f),
      m_fXTargetAngle(0.0f),
      m_vTarget{0.0f, 0.0f, 0.0f},
      m_fYAngle(0.0f),
      m_fXAngle(0.0f),
      m_pQuatMatrix(nullptr),
      m_pQuatInterMatrix(nullptr),
      m_pQuatAnim(nullptr),
      m_pQuatFinal(nullptr),
      m_fSpeedUp(0.0f),
      m_fCurrentSpeed(0.0f),
      m_fSpeed(50.0f),  // TOC -0x6540 (0x42480000)
      m_fSpeedMin(0.0f),
      m_fSpeedMax(0.0f),
      m_fInterBlendCoef(0.0f),
      m_fInterAnimCoef(0.0f),
      m_ChainState(0) {}

// 0x00090c38 CKAnimatedChain_Destroy
void CKAnimatedChain::Destroy() {
    delete[] m_pTabOfBoneNum;
    delete[] m_pQuatFinal;
    delete[] m_pQuatAnim;
    delete[] m_pfAngleValues[0];
    delete[] m_pfAngleValues[1];
}

// 0x00090358 CKAnimatedChain_RecursiveRegistration
void CKAnimatedChain::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x00091298 CKAnimatedChain_Load
int32_t CKAnimatedChain::Load(IKFile* file, int32_t /*type*/) {
    m_ui8NumOfBone = 0;
    m_pfAngleValues[1] = nullptr;
    m_i8NumBoneForPosRef = -1;
    m_fSpeedMax = 2.0f;
    m_fSpeedUp = 0.0f;
    m_ui8NumOfKeyByAxe = 0;
    m_pfAngleValues[0] = nullptr;
    m_fInterBlendCoef = 0.0f;
    m_fInterAnimCoef = 0.0f;
    m_fSpeed = 2.0f;
    m_fSpeedMin = 0.0f;
    IKFile_ReadRef(file, &m_pNext);
    ReadU8(file, &m_ui8NumOfBone);
    IKFile_ReadRef(file, &m_pAnimatedNode);
    m_pHierarchy = m_pAnimatedNode->m_pRpHAnimHierarchy;  // node +0x2c
    m_pTabOfBoneNum = new uint32_t[m_ui8NumOfBone];
    ReadU32LEWords(file, m_pTabOfBoneNum, m_ui8NumOfBone);  // one read, every word swapped
    ReadU8(file, &m_ui8NumOfKeyByAxe);
    if (m_ui8NumOfKeyByAxe != 0) {
        m_pfAngleValues[0] = new float[m_ui8NumOfKeyByAxe];
        m_pfAngleValues[1] = new float[m_ui8NumOfKeyByAxe];
        for (uint32_t i = 0; i < m_ui8NumOfKeyByAxe; i = static_cast<uint8_t>(i + 1)) {
            m_pfAngleValues[0][i] = 0.0f;  // stw 0
            m_pfAngleValues[1][i] = 0.0f;
        }
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_pfAngleValues[0]), m_ui8NumOfKeyByAxe);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_pfAngleValues[1]), m_ui8NumOfKeyByAxe);
    }
    // (Without keys the original reads 0 bytes into each null array.)
    m_fCurrentSpeed = m_fSpeed;
    m_ChainState = 0;
    m_fSpeedUp = 0.0f;
    m_pQuatFinal = nullptr;
    m_pQuatAnim = nullptr;
    m_fYAngle = 0.0f;
    m_fXAngle = 0.0f;
    return 1;
}

// 0x000909c8 CKAnimatedChain_SampleBlendGrid_maybe
void CKAnimatedChain::SampleBlendGrid(int32_t x, int32_t y, uint8_t bone, float tx, float ty) {
    float a[4];
    float b[4];
    Quat** grid = m_pQuatMatrix[bone];
    Quat_Slerp(tx, a, grid[x][y].m_a, grid[x + 1][y].m_a);  // 0x00242728
    Quat_Slerp(tx, b, grid[x][y + 1].m_a, grid[x + 1][y + 1].m_a);
    Quat_Slerp(ty, m_pQuatAnim[bone].m_a, a, b);
}

// 0x000907e0 CKAnimatedChain_SampleBlendGridLayered_maybe. The inter grid is crossed along y first.
void CKAnimatedChain::SampleBlendGridLayered(int32_t x, int32_t y, uint8_t bone, float tx, float ty) {
    float a[4];
    float b[4];
    Quat** grid = m_pQuatMatrix[bone];
    Quat_Slerp(tx, a, grid[x][y].m_a, grid[x + 1][y].m_a);
    Quat_Slerp(tx, b, grid[x][y + 1].m_a, grid[x + 1][y + 1].m_a);
    Quat_Slerp(ty, m_pQuatAnim[bone].m_a, a, b);
    Quat** inter = m_pQuatInterMatrix[bone];
    Quat_Slerp(ty, a, inter[x][y].m_a, inter[x][y + 1].m_a);
    Quat_Slerp(ty, b, inter[x + 1][y].m_a, inter[x + 1][y + 1].m_a);
    Quat_Slerp(tx, a, a, b);
    Quat_Slerp(m_fInterBlendCoef, m_pQuatAnim[bone].m_a, m_pQuatAnim[bone].m_a, a);
}

// 0x000910a8 CKAnimatedChain_ApproachTargetBlend_maybe. The speed is clamped to the minimum when not at or above it
// (NaN included), then to the maximum when above it.
void CKAnimatedChain::BlendBeforeStop(IKTime* clock) {
    m_ChainState = static_cast<uint16_t>(m_ChainState & ~0x20u);
    const float distance = AngleDistance(this);
    float speed = Accelerate(this, clock->m_afDeltaTime[0]);  // clock +0x1c
    m_fCurrentSpeed = speed;
    if (!(speed >= m_fSpeedMin)) {
        speed = m_fSpeedMin;
        m_fCurrentSpeed = speed;
    }
    if (speed > m_fSpeedMax) {
        speed = m_fSpeedMax;
        m_fCurrentSpeed = speed;
    }
    const float step = speed * clock->m_afDeltaTime[0];
    float t;
    if (distance > step) {  // ble: NaN arrives
        t = step / distance;
        m_fYAngle = ppc::fmadds(t, m_fYTargetAngle - m_fYAngle, m_fYAngle);
        m_fXAngle = ppc::fmadds(t, m_fXTargetAngle - m_fXAngle, m_fXAngle);
    } else {
        m_ChainState = static_cast<uint16_t>(m_ChainState & ~0x4u);
        t = 1.0f;  // TOC -0x6570
        m_fYAngle = m_fYTargetAngle;
        m_fXAngle = m_fXTargetAngle;
    }
    for (int32_t i = 0; static_cast<int32_t>(m_ui8NumOfBone) > i; ++i) {
        float* q = FrameQuat(m_pHierarchy, m_pTabOfBoneNum[i]);
        Quat_Slerp(t, q, m_pQuatFinal[i].m_a, q);
        std::memcpy(m_pQuatFinal[i].m_a, q, 16);
    }
}

// 0x00091950 CKAnimatedChain_ComputeTargetCoordsFromBones_maybe
void CKAnimatedChain::InterpolationAimAtSolver() {
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(&m_pAnimatedNode->m_pRwFrame->ltm);  // node +0x04, +0x50
    const int32_t reference = m_i8NumBoneForPosRef;
    RwMatrix* boneMatrix = static_cast<float>(static_cast<double>(reference)) == -1.0f
                               ? m_pAnimatedNode->GetBoneMatrix(GetBoneNumInHierarchy(0))  // vt+0x50
                               : m_pAnimatedNode->GetBoneMatrix(static_cast<uint32_t>(reference));
    CVector3 position;
    Mat4_TransformPoints(ltm, &position, reinterpret_cast<const CVector3*>(&boneMatrix->pos), 1);
    const CVector3 referencePosition = position;
    CVector3 direction;
    if (((m_ChainState >> 4) & 1u) != 0) {
        direction = m_vTarget;
        const float length = Sqrtf(ppc::fmadds(direction.z, direction.z,
                                               ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            direction.z = direction.z * inverse;
            direction.x = direction.x * inverse;
            direction.y = direction.y * inverse;
        }
    } else {
        direction.x = m_vTarget.x - position.x;
        direction.z = m_vTarget.z - position.z;
        direction.y = m_vTarget.y - position.y;
    }
    alignas(16) CMatrix34 world;
    alignas(16) CMatrix34 inverse;
    Mat4_Multiply(&world, reinterpret_cast<const CMatrix34*>(m_pAnimatedNode->GetBoneMatrix(m_ui8BoneRef)), ltm);
    Mat4_Invert(&inverse, &world);  // 0x0023f878
    CVector3 d;
    Mat4_TransformVectors(&inverse, &d, &direction, 1);
    CVector3 unused;
    Mat4_TransformPoints(&inverse, &unused, &referencePosition, 1);  // the result is not read
    // The horizontal direction (y dropped).
    float ux = d.x;
    float uz = d.z;
    float uy = 0.0f;
    const float length = Sqrtf(ppc::fmadds(uz, uz, ppc::fmadds(ux, ux, 0.0f)));
    if (length != 0.0f) {
        const float inverseLength = 1.0f / length;
        uz = uz * inverseLength;
        ux = ux * inverseLength;
        uy = inverseLength * 0.0f;
    }
    float yaw = 0.0f;
    if (uz < 0.999899983f) {  // TOC -0x6530; NaN: 0
        yaw = crt::Acosf(uz) * kRadToDeg;  // TocBridge_Math_Acosf 0x98e1a0
        if (ux > 0.0f) yaw = -yaw;
    }
    m_fYTargetAngle = yaw;
    // c = u x Y, e = c x d, g = c x e, each component one fused multiply-subtract.
    const CVector3& up = kAxisY;
    const float cx = ppc::fmsubs(up.z, uy, up.y * uz);
    const float cz = ppc::fmsubs(up.y, ux, up.x * uy);
    const float cy = ppc::fmsubs(up.x, uz, up.z * ux);
    const float ez = ppc::fmsubs(cy, d.x, cx * d.y);
    const float ey = ppc::fmsubs(cx, d.z, cz * d.x);
    const float ex = ppc::fmsubs(cz, d.y, cy * d.z);
    float gy = ppc::fmsubs(cz, ex, cx * ez);
    float gx = ppc::fmsubs(cy, ez, cz * ey);
    float gz = ppc::fmsubs(cx, ey, cy * ex);
    const float gLength = Sqrtf(ppc::fmadds(gz, gz, ppc::fmadds(gx, gx, gy * gy)));
    if (gLength != 0.0f) {
        const float inverseLength = 1.0f / gLength;
        gz = gz * inverseLength;
        gx = gx * inverseLength;
        gy = gy * inverseLength;
    }
    const float dot = ppc::fmadds(uz, gz, ppc::fmadds(ux, gx, uy * gy));
    float pitch = 0.0f;
    if (dot < 0.999899983f) {
        pitch = crt::Acosf(dot) * kRadToDeg;
        if (!(gy >= 0.0f)) pitch = -pitch;
    }
    m_fXTargetAngle = pitch;
}

// 0x00091d08 CKAnimatedChain_SampleAtCoords_maybe. Bit 9 ends as the x axis' overrun (the y axis' is written first and
// overwritten).
int32_t CKAnimatedChain::SampleAtCoords(float* y, float* x) {
    m_ChainState = static_cast<uint16_t>(m_ChainState & ~0x200u);
    bool overran;
    int32_t cellY;
    float ty;
    AxisCell(m_pfAngleValues[0], m_ui8NumOfKeyByAxe, y, &overran, &cellY, &ty);
    if (overran) m_ChainState = static_cast<uint16_t>(m_ChainState | 0x200u);
    int32_t cellX;
    float tx;
    AxisCell(m_pfAngleValues[1], m_ui8NumOfKeyByAxe, x, &overran, &cellX, &tx);
    m_ChainState = static_cast<uint16_t>((m_ChainState & ~0x200u) | (overran ? 0x200u : 0u));
    const bool layered = (m_ChainState & 0x40u) != 0 && !(m_fInterBlendCoef <= 0.0f);  // fcmpu + cror lt|eq
    for (uint32_t bone = 0; bone < m_ui8NumOfBone; bone = static_cast<uint8_t>(bone + 1)) {
        if (layered) {
            SampleBlendGridLayered(cellX, cellY, static_cast<uint8_t>(bone), tx, ty);  // 0x000907e0
        } else {
            SampleBlendGrid(cellX, cellY, static_cast<uint8_t>(bone), tx, ty);  // 0x000909c8
        }
    }
    return 1;
}

// 0x00092270 CKAnimatedChain_StepToTargetCoords_maybe. Here the speed takes the minimum only when below it (NaN
// does not), then the maximum when above it.
void CKAnimatedChain::UpDateInterpolationAimAtMode(IKTime* clock) {
    if ((m_ChainState & 0x8u) == 0) InterpolationAimAtSolver();  // 0x00091950
    SampleAtCoords(&m_fYTargetAngle, &m_fXTargetAngle);
    if (((m_ChainState >> 1) & 1u) == 0) {
        // No approach: the sampled pose at once.
        if ((m_ChainState & 0x200u) == 0) m_ChainState = static_cast<uint16_t>((m_ChainState & ~0x20u) | 0x20u);
        m_fCurrentSpeed = m_fSpeed;
        m_fYAngle = m_fYTargetAngle;
        m_fXAngle = m_fXTargetAngle;
        for (int32_t i = 0; static_cast<int32_t>(m_ui8NumOfBone) > i; ++i) {
            float* q = FrameQuat(m_pHierarchy, m_pTabOfBoneNum[i]);
            std::memcpy(q, m_pQuatAnim[i].m_a, 16);
            std::memcpy(m_pQuatFinal[i].m_a, q, 16);
        }
        return;
    }
    const float distance = AngleDistance(this);
    float speed = Accelerate(this, clock->m_afDeltaTime[0]);
    m_fCurrentSpeed = speed;
    if (speed < m_fSpeedMin) {
        speed = m_fSpeedMin;
        m_fCurrentSpeed = speed;
    }
    if (speed > m_fSpeedMax) {
        speed = m_fSpeedMax;
        m_fCurrentSpeed = speed;
    }
    const float step = speed * clock->m_afDeltaTime[0];
    float t;
    if (distance > step) {  // ble: NaN arrives
        t = step / distance;
        m_fYAngle = ppc::fmadds(t, m_fYTargetAngle - m_fYAngle, m_fYAngle);
        m_fXAngle = ppc::fmadds(t, m_fXTargetAngle - m_fXAngle, m_fXAngle);
        m_ChainState = static_cast<uint16_t>(m_ChainState & ~0x20u);
    } else {
        m_fCurrentSpeed = m_fSpeed;
        if ((m_ChainState & 0x200u) == 0) m_ChainState = static_cast<uint16_t>((m_ChainState & ~0x20u) | 0x20u);
        m_fYAngle = m_fYTargetAngle;
        m_fXAngle = m_fXTargetAngle;
        t = 1.0f;
    }
    for (int32_t i = 0; static_cast<int32_t>(m_ui8NumOfBone) > i; ++i) {
        float* q = FrameQuat(m_pHierarchy, m_pTabOfBoneNum[i]);
        Quat_Slerp(t, q, m_pQuatFinal[i].m_a, m_pQuatAnim[i].m_a);
        std::memcpy(m_pQuatFinal[i].m_a, q, 16);
    }
}

// 0x00092610 CKAnimatedChain_Update_maybe
void CKAnimatedChain::UpdateChain(IKTime* clock) {
    if (clock->m_eCurrentState != 0) return;  // clock +0x30
    const uint32_t state = m_ChainState;
    if ((state & 1u) != 0) {
        if ((state & 0x40u) != 0) {
            for (int32_t i = 0; static_cast<int32_t>(m_ui8NumOfBone) > i; ++i) {
                float* q = FrameQuat(m_pHierarchy, m_pTabOfBoneNum[i]);
                Quat_Slerp(m_fInterAnimCoef, m_pQuatFinal[i].m_a, m_pQuatFinal[i].m_a, q);
                std::memcpy(q, m_pQuatFinal[i].m_a, 16);
            }
        } else {
            if ((state & 0x80u) != 0) {
                for (int32_t i = 0; static_cast<int32_t>(m_ui8NumOfBone) > i; ++i) {
                    std::memcpy(m_pQuatFinal[i].m_a, FrameQuat(m_pHierarchy, m_pTabOfBoneNum[i]), 16);
                }
                m_ChainState = static_cast<uint16_t>(m_ChainState & ~0x100u);
                m_fCurrentSpeed = m_fSpeed;
            }
            UpDateInterpolationAimAtMode(clock);  // 0x00092270
        }
    } else if ((state & 2u) != 0) {
        BlendBeforeStop(clock);  // 0x000910a8
    } else {
        return;
    }
    RpHAnimHierarchyUpdateMatrices(m_pHierarchy);  // TocBridge 0x98e1b0
}
