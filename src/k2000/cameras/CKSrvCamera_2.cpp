// CKSrvCamera_2.cpp - the second half of the reconstructed CKSrvCamera.cpp unit (0x12a888-0x13a330): the service's frame
// (step 5, the FRAME family). The checklist is in CKSrvCamera.cpp; the functions here are ticked there:
//   0x12e508 CKSrvCamera_UpdateHeroGroundReference_maybe, 0x12f268 CKSrvCamera_ResolveGroundClearance_maybe,
//   0x132fd8 CKSrvCamera_AdjustViewToKeepTargetInFrameMargins_maybe, 0x1339e8 CKSrvCamera_TurnViewTowardDesiredDirection_maybe,
//   0x1354b0 CKSrvCamera_SmoothCalculationPosition_maybe, 0x1357d0 CKSrvCamera_ApplyFrameMarginAdjustment_maybe,
//   0x135c80 CKSrvCamera_SmoothCalculationTarget_maybe, 0x135fd0 CKSrvCamera_FetchTrackPose_maybe,
//   0x136348 CKSrvCamera_OrientMatrixToTarget_maybe, 0x1366a0 CKSrvCamera_UpdateCameraBeacon_maybe,
//   0x137ae0 CKSrvCamera_UpdateFrame.
//
// The TOC constants: 0.0 (-0x40e0), 1.0 (-0x40e4), -1.0 (-0x40a4), 0.5 (-0x409c), 0.01 (-0x408c), -0.01 (-0x4054), 0.02
// (-0x40d8), 0.001 (-0x407c), -0.001 (-0x3fbc), 150 (-0x40d4), pi/180 (-0x4050, 0x3c8efa34), 0.75 (-0x404c), 4/3 (-0x4044,
// 0x3faaaaab), 0.707 (-0x3ff0), 0.866 (-0x3fdc), 0.9998477 (-0x3fe0), 180/pi (-0x3fe8), -180/pi (-0x3fd8), pi (-0x3fec),
// pi/2 (-0x3fb0), pi/6 (-0x3fac), 45 (-0x3fb4), 15 (-0x3fb8), 0.1 (-0x4048), 180 (-0x3fe4), 100000 (-0x4058), -0.0
// (-0x3ff4). Every float operation is the original's (single precision, the fused ones through ppc_ops).
#include "k2000/cameras/CKSrvCamera.h"

#include <cfloat>
#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "crt/xtanf.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/CKCameraBeacon.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/cameras/CKCameraSector.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/graphical/IRendableObject.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00c50d40 / 0x00c50d64: the shared Y axis and the null vector (zero in the EBOOT's BSS; static initialisers).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// The word at 0x00c4acb8 + 0x28 (FLT_MAX statically): the start time of a line test and the start distance of a beacon search.
const float kFarAway = FLT_MAX;

// 0x00010690 Math_Sqrtf (fsqrts; also inlined as fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

inline float AsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}

// The sign bit of a float (the original stores it and tests the word: the inlined cosf's guard).
inline bool SignBit(float x) {
    uint32_t word;
    std::memcpy(&word, &x, 4);
    return (word & 0x80000000u) != 0;
}

// The inlined cosine (FetchTrackPose, TurnViewTowardDesiredDirection): the octant polynomial for a non-negative argument,
// the library's cosf 0x009a11d8 of -x otherwise.
inline float GameCosf(float x) { return SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }

// The "|x| < limit" tests the original makes by clearing the sign bit of a stored copy (fcmpu: a NaN is not below).
inline bool AbsBelow(float x, float limit) { return std::fabs(x) < limit; }

// The +0x7b0 block (m_unk7b0, 0x1d words): the blend start of a camera switch. The words this unit writes, by offset.
float& Blend(CKSrvCamera* camera, uint32_t offset) {
    return reinterpret_cast<float*>(camera->m_unk7b0)[(offset - 0x7b0u) / 4u];
}

// An RwMatrix of the stack (16 floats) from three axes and a position; the flags word keeps its (unset) value with the
// bits 0xfffdfffc, as the original's `and` on the uninitialised stack word (zero here).
void BuildMatrix(CMatrix34* m, const CVector3& right, const CVector3& up, const CVector3& at, const CVector3& pos) {
    m->m_right = right;
    m->m_up = up;
    m->m_at = at;
    m->m_pos = pos;
    m->m_ui32Flags &= 0xfffdfffcu;
}

// 0x0023f788 Mat4_Multiply etc. take CMatrix34; Quat_FromMatrix the 16 floats.
inline const float* Floats(const CMatrix34* m) { return reinterpret_cast<const float*>(m); }

}  // namespace

// ---- the smoothing and the springs --------------------------------------------------------------------------------

// 0x0012e508 CKSrvCamera_UpdateHeroGroundReference_maybe. +0x8ac the reference point (A), +0x8b8 the second point (B),
// +0x8c4 the plane normal, +0x8d0 the spring (target, value, speed); the camera's frame margins (vt+0x7c) are the
// spring's stiffness and damping.
void CKSrvCamera::UpdateHeroGroundReference(float dt, CVector3* focus) {
    uint32_t flags = m_baTemporaryFlags;
    if ((flags & 1u) == 0 && (flags & 0x10000u) == 0) return;
    if (m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr) return;
    CVector3& a = m_v3GroundRefA;
    CVector3& b = m_v3GroundRefB;
    const CVector3& n = m_v3GroundNormal;
    float* spring = m_unk8d0;  // [0] target, [1] value, [2] speed
    // The focus moved within the plane: A and B follow it.
    const float dx = focus->x - a.x;
    const float dy = focus->y - a.y;
    const float dz = focus->z - a.z;
    const float d = ppc::fmadds(dz, n.z, ppc::fmadds(dx, n.x, dy * n.y));
    const float nd = -d;
    const float px = ppc::fmadds(n.x, nd, dx);
    const float pz = ppc::fmadds(n.z, nd, dz);
    const float py = ppc::fmadds(n.y, nd, dy);
    a.x = a.x + px;
    a.z = pz + a.z;
    a.y = py + a.y;
    b.x = px + b.x;
    b.y = py + b.y;
    b.z = pz + b.z;
    if (!(d >= -0.01f) || (m_baTemporaryFlags & 1u) == 0) {
        b.x = focus->x;
        b.y = focus->y;
        b.z = focus->z;
    }
    // The focused hero's position lifts B (CKS08GameManager vt+0x120 / vt+0x128).
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    IKSerializable* first = m_ui32NbStacked != 0 ? m_aStack[0].m_pTarget : nullptr;
    if (first == manager->GetFocusedHeroCamera()) {
        const float* hero = manager->GetFocusedHeroPosition();
        if (!(b.y >= hero[1])) {
            b.x = hero[0];
            b.y = hero[1];
            b.z = hero[2];
        }
    }
    const float h = ppc::fmadds(b.z - a.z, n.z, ppc::fmadds(b.x - a.x, n.x, (b.y - a.y) * n.y));
    const float zero = 0.0f;
    float offset;
    if (h >= zero) {
        float stiffness, damping;
        m_pCurrentCamera->GetFrameMargins(&stiffness, &damping);
        const float error = spring[0] - h;
        spring[1] = h;
        bool move = true;
        float force = 0.0f;
        if (error != zero) {
            force = ppc::fmsubs(stiffness, error, damping * spring[2]);
        } else if (spring[2] != zero) {
            force = spring[2] * -damping;
        } else {
            move = false;
        }
        float value = h;
        if (move) {
            const float speed = ppc::fmadds(force, dt, spring[2]);
            value = ppc::fmadds(dt, speed, h);
            if (value <= 0.0f) value = 0.0f;
            else if (value >= 100000.0f) value = 100000.0f;
            if (std::fabs(speed) <= 0.0f && std::fabs(value - spring[0]) <= 0.0f) {
                value = spring[0];
                spring[2] = 0.0f;
                spring[1] = value;
            } else {
                spring[2] = speed;
                spring[1] = value;
            }
        }
        offset = h - value;
    } else {
        float stiffness, damping;
        m_pCurrentCamera->GetFrameMargins(&stiffness, &damping);
        const float depth = -h;
        const float error = spring[0] - depth;
        spring[1] = depth;
        if (error == zero && spring[2] == zero) {
            offset = depth + h;
        } else {
            const float force = error != zero ? ppc::fmsubs(stiffness, error, damping * spring[2]) : spring[2] * -damping;
            const float speed = ppc::fmadds(force, dt, spring[2]);
            float value = ppc::fmadds(dt, speed, depth);
            if (value <= 0.0f) value = 0.0f;
            else if (value >= 100000.0f) value = 100000.0f;
            if (std::fabs(speed) <= 0.0f && std::fabs(value - spring[0]) <= 0.0f) {
                value = spring[0];
                spring[2] = 0.0f;
                spring[1] = value;
                offset = value + h;
            } else {
                spring[1] = value;
                offset = value + h;
                spring[2] = speed;
            }
        }
    }
    a.x = ppc::fmadds(offset, n.x, a.x);
    focus->x = a.x;
    a.z = ppc::fmadds(offset, n.z, a.z);
    a.y = ppc::fmadds(offset, n.y, a.y);
    focus->z = a.z;
    focus->y = a.y;
    if ((m_baTemporaryFlags & 1u) == 0 && spring[1] <= 0.01f) {
        m_baTemporaryFlags &= 0xfffeffffu;
        spring[2] = 0.0f;
        spring[0] = 0.0f;
        spring[1] = 0.0f;
        focus->z = b.z;
        focus->x = b.x;
        focus->y = b.y;
    }
}

// 0x001354b0 CKSrvCamera_SmoothCalculationPosition_maybe. The offset starts at the null vector each frame; the speed
// (+0x788) carries over. A component closer than 0.001 to its target does not pull.
void CKSrvCamera::StepViewOffsetSpring(float dt, uint8_t mode) {
    const CVector3& p = m_InternalCamera.m_WorldPosition;
    const CVector3& ax = m_v3InternalAxisX;
    const CVector3& ay = m_v3InternalAxisY;
    const CVector3& az = m_v3InternalAxisZ;
    const float dx = m_v3CalcPos.x - p.x;
    const float dy = m_v3CalcPos.y - p.y;
    const float dz = m_v3CalcPos.z - p.z;
    const float tz0 = dy * az.y;
    const float ty0 = dy * ay.y;
    const float tx0 = dy * ax.y;
    const CVector3& visc = m_SmoothVisc[mode];
    const CVector3& spring = m_SmoothKSpring[mode];
    float ox = kNullVector.x;
    float oy = kNullVector.y;
    float oz = kNullVector.z;
    const float lz = ppc::fmadds(dz, az.z, ppc::fmadds(dx, az.x, tz0));
    const float ly = ppc::fmadds(dz, ay.z, ppc::fmadds(dx, ay.x, ty0));
    const float lx = ppc::fmadds(dz, ax.z, ppc::fmadds(dx, ax.x, tx0));
    CVector3& speed = m_v3Unk788;
    const float zero = 0.0f;
    while (dt > zero) {
        float step;
        if (dt > 0.02f) {
            dt = dt - 0.02f;
            step = 0.02f;
        } else {
            step = dt;
            dt = 0.0f;
        }
        float ex = lx - ox;
        float ey = ly - oy;
        float ez = lz - oz;
        const bool zx = ex < zero ? ex > -0.001f : !(ex >= 0.001f);
        if (zx) ex = 0.0f;
        const bool zy = ey < zero ? ey > -0.001f : !(ey >= 0.001f);
        if (zy) ey = 0.0f;
        const bool zz = ez < zero ? ez > -0.001f : !(ez >= 0.001f);
        if (zz) ez = 0.0f;
        const float fx = ppc::fmsubs(spring.x, ex, speed.x * visc.x);
        const float fy = ppc::fmsubs(spring.y, ey, speed.y * visc.y);
        const float fz = ppc::fmsubs(spring.z, ez, speed.z * visc.z);
        speed.x = ppc::fmadds(step, fx, speed.x);
        speed.y = ppc::fmadds(step, fy, speed.y);
        speed.z = ppc::fmadds(step, fz, speed.z);
        ox = ppc::fmadds(step, speed.x, ox);
        oy = ppc::fmadds(step, speed.y, oy);
        oz = ppc::fmadds(step, speed.z, oz);
    }
    float x = ppc::fmadds(ox, ax.x, p.x);
    float z = ppc::fmadds(ox, ax.z, p.z);
    float y = ppc::fmadds(ox, ax.y, p.y);
    m_v3CalcPos.x = x;
    m_v3CalcPos.z = z;
    m_v3CalcPos.y = y;
    z = ppc::fmadds(oy, ay.z, z);
    x = ppc::fmadds(oy, ay.x, x);
    y = ppc::fmadds(oy, ay.y, y);
    m_v3CalcPos.z = z;
    m_v3CalcPos.x = x;
    m_v3CalcPos.y = y;
    m_v3CalcPos.z = ppc::fmadds(oz, az.z, z);
    m_v3CalcPos.x = ppc::fmadds(oz, az.x, x);
    m_v3CalcPos.y = ppc::fmadds(oz, az.y, y);
    ComputeViewBasis();
}

// 0x00135c80 CKSrvCamera_SmoothCalculationTarget_maybe. The target in the internal camera's axes, from (0, 0, the
// internal target's distance); the speed (+0x77c) carries over.
void CKSrvCamera::StepSmoothedTowardTrackPose(float dt, uint8_t mode) {
    const CVector3& p = m_InternalCamera.m_WorldPosition;
    const CVector3& t = m_InternalCamera.m_WorldTarget;
    const CVector3& ax = m_v3InternalAxisX;
    const CVector3& ay = m_v3InternalAxisY;
    const CVector3& az = m_v3InternalAxisZ;
    const float ix = t.x - p.x;
    const float iy = t.y - p.y;
    const float iz = t.z - p.z;
    const float dx = m_v3CalcTarget.x - p.x;
    const float dy = m_v3CalcTarget.y - p.y;
    const float dz = m_v3CalcTarget.z - p.z;
    const float tz0 = dy * az.y;
    const float tx0 = dy * ax.y;
    const float ty0 = dy * ay.y;
    const CVector3& visc = m_SmoothVisc[mode];
    const CVector3& spring = m_SmoothKSpring[mode];
    const float lz = ppc::fmadds(dz, az.z, ppc::fmadds(dx, az.x, tz0));
    const float lx = ppc::fmadds(dz, ax.z, ppc::fmadds(dx, ax.x, tx0));
    const float ly = ppc::fmadds(dz, ay.z, ppc::fmadds(dx, ay.x, ty0));
    float oz = Sqrtf(ppc::fmadds(iz, iz, ppc::fmadds(ix, ix, iy * iy)));
    const float zero = 0.0f;
    float ox = zero;
    float oy = zero;
    CVector3& speed = m_v3Unk77c;
    if (dt > zero) {
        for (;;) {
            float step;
            if (dt > 0.02f) {
                dt = dt - 0.02f;
                step = 0.02f;
            } else {
                step = dt;
                dt = 0.0f;
            }
            float ex = lx - ox;
            float ey = ly - oy;
            float ez = lz - oz;
            if (!(std::fabs(ex) >= 0.001f)) ex = 0.0f;
            if (!(std::fabs(ey) >= 0.001f)) ey = 0.0f;
            if (!(std::fabs(ez) >= 0.001f)) ez = 0.0f;
            const float fx = ppc::fmsubs(spring.x, ex, speed.x * visc.x);
            const float fy = ppc::fmsubs(spring.y, ey, speed.y * visc.y);
            const float fz = ppc::fmsubs(spring.z, ez, speed.z * visc.z);
            speed.x = ppc::fmadds(step, fx, speed.x);
            speed.y = ppc::fmadds(step, fy, speed.y);
            speed.z = ppc::fmadds(step, fz, speed.z);
            ox = ppc::fmadds(step, speed.x, ox);
            oy = ppc::fmadds(step, speed.y, oy);
            oz = ppc::fmadds(step, speed.z, oz);
            if (!(dt > zero)) break;
        }
    }
    m_v3CalcTarget.x = p.x;
    m_v3CalcTarget.y = p.y;
    m_v3CalcTarget.z = p.z;
    float z = ppc::fmadds(ox, ax.z, p.z);
    float x = ppc::fmadds(ox, ax.x, p.x);
    float y = ppc::fmadds(ox, ax.y, p.y);
    m_v3CalcTarget.z = z;
    m_v3CalcTarget.x = x;
    m_v3CalcTarget.y = y;
    z = ppc::fmadds(oy, ay.z, z);
    x = ppc::fmadds(oy, ay.x, x);
    y = ppc::fmadds(oy, ay.y, y);
    m_v3CalcTarget.z = z;
    m_v3CalcTarget.x = x;
    m_v3CalcTarget.y = y;
    m_v3CalcTarget.z = ppc::fmadds(oz, az.z, z);
    m_v3CalcTarget.x = ppc::fmadds(oz, az.x, x);
    m_v3CalcTarget.y = ppc::fmadds(oz, az.y, y);
    ComputeViewBasis();
}

// 0x00135fd0 CKSrvCamera_FetchTrackPose_maybe. The oscillation: roll target = vt+0x84 + vt+0x8c * cos(vt+0x90 * the
// scalable game clock), the rate vt+0x8c * vt+0x90 / (pi/2) per second; without it 45 degrees per second.
void CKSrvCamera::FetchTrackPose(float dt, CKCameraSector* sector, IKCamera* /*camera*/) {
    IKCamera* camera = m_pCurrentCamera;
    m_v3CalcPos.x = camera->m_WorldPosition.x;
    m_v3CalcPos.z = camera->m_WorldPosition.z;
    m_v3CalcPos.y = camera->m_WorldPosition.y;
    camera = m_pCurrentCamera;
    m_v3CalcTarget.x = camera->m_WorldTarget.x;
    m_v3CalcTarget.z = camera->m_WorldTarget.z;
    m_v3CalcTarget.y = camera->m_WorldTarget.y;
    IKSerializable* farObject = sector != nullptr ? sector->m_unk28 : nullptr;
    camera = m_pCurrentCamera;
    if (farObject != nullptr && farObject->GetClassID() == 0x6d) {
        // An object of class id 0x6d (the one registered class with that id is CLensFlareFx, key 0x1b4d) gives the far
        // plane from its +0x04.
        float far;
        // PS3 +0x04 is IRendableObject::m_pNextAccumulatedObject (a pointer the original reads as a float). PORT: read
        // through the member (its first four bytes), not the PS3 offset, so x64 does not read the vtable pointer.
        std::memcpy(&far, &static_cast<const IRendableObject*>(farObject)->m_pNextAccumulatedObject, 4);
        m_fCalcFar = far;
        m_fCalcFov = camera->m_unk18;
    } else {
        m_fCalcFar = camera->m_fFar;
        m_fCalcFov = camera->m_unk18;
    }
    float target = camera->Vf84();
    const float amplitude = m_pCurrentCamera->Vf8C();
    float rate;
    if (amplitude == 0.0f) {
        rate = 45.0f;
    } else {
        const float frequency = m_pCurrentCamera->Vf90();
        const float x = frequency * g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
        const float c = GameCosf(x);
        target = ppc::fmadds(c, amplitude, target);
        rate = (amplitude * m_pCurrentCamera->Vf90()) / 1.5707963705062866f;
    }
    if (m_pCurrentCamera->Vf94() != 0) {
        const float roll = m_fCalcRoll;
        if (target > roll) {
            const float r = ppc::fmadds(rate, dt, roll);
            m_fCalcRoll = r;
            if (target < r) m_fCalcRoll = target;
        } else {
            const float r = roll - rate * dt;
            m_fCalcRoll = r;
            if (!(target <= r)) m_fCalcRoll = target;
        }
    } else {
        m_fCalcRoll = target;
    }
    ComputeViewBasis();
}

// 0x00136348 CKSrvCamera_OrientMatrixToTarget_maybe. `matrix` is an RwMatrix as 16 floats (right 0..2, flags 3, up 4..6,
// at 8..10, position 12..14). Nothing when the target is the matrix's position.
void CKSrvCamera::OrientMatrixToTarget(const float* target, const float* up, float* matrix, uint8_t keepPitch) {
    float dx = target[0] - matrix[12];
    float dz = target[2] - matrix[14];
    float dy = target[1] - matrix[13];
    if (kNullVector.x == dx && kNullVector.y == dy && kNullVector.z == dz) return;
    const float zero = 0.0f;
    const float one = 1.0f;
    if (keepPitch != 0) {
        // The at axis keeps its y; x / z point at the target in the horizontal plane (fsqrts inline).
        const float sum = ppc::fmadds(dx, dx, dz * dz);
        const float y = matrix[9];
        if (Sqrtf(sum) == zero) {
            dx = matrix[8];
            dz = matrix[10];
            dy = matrix[9];
        } else {
            const float inverse = one / Sqrtf(sum);
            const float horizontal = Sqrtf(one - y * y);
            dz = (dz * inverse) * horizontal;
            dx = (dx * inverse) * horizontal;
            dy = y;
        }
    } else {
        const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (length != zero) {
            const float inverse = one / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
    }
    uint32_t flags;
    std::memcpy(&flags, &matrix[3], 4);
    flags &= 0xfffdfffcu;
    matrix[9] = dy;
    matrix[8] = dx;
    matrix[10] = dz;
    std::memcpy(&matrix[3], &flags, 4);
    // The up vector's length: only its y counts (x and z are taken as 0 by the original's arithmetic).
    const float upY = up[1];
    const float upLength = Sqrtf(ppc::fmadds(upY, upY, zero) + zero);
    if (upLength != zero) {
        const float inverse = one / upLength;
        const float ux = inverse * zero;
        const float uy = upY * inverse;
        const float t12 = ux * dx;
        const float t1 = ux * dz;
        const float dot = ppc::fmadds(uy, dy, t12) + t1;
        if (AbsBelow(dot, 0.9998477101325989f)) {
            // right = up x at, normalised; up = at x right
            const float t0 = ux * dy;
            float ry = t12 - t1;
            const float t13 = uy * dx;
            float rx = ppc::fmsubs(uy, dz, t0);
            float rz = t0 - t13;
            const float length = Sqrtf(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry)));
            if (length != zero) {
                const float inv = one / length;
                rz = rz * inv;
                rx = rx * inv;
                ry = ry * inv;
            }
            const float a0 = dy * rx;
            const float a13 = dx * rz;
            const float a12 = dz * ry;
            matrix[0] = rx;
            matrix[1] = ry;
            matrix[2] = rz;
            std::memcpy(&flags, &matrix[3], 4);
            flags &= 0xfffdfffcu;
            std::memcpy(&matrix[3], &flags, 4);
            matrix[6] = ppc::fmsubs(dx, ry, a0);
            matrix[5] = ppc::fmsubs(dz, rx, a13);
            matrix[4] = ppc::fmsubs(dy, rz, a12);
            return;
        }
    }
    // up = right x at (the old right axis), normalised; right = up x at
    const float r0 = matrix[0];
    const float r1 = matrix[1];
    const float r2 = matrix[2];
    const float t10 = r2 * dx;
    const float t12 = r1 * dz;
    const float t13 = r0 * dy;
    float uy = ppc::fmsubs(r0, dz, t10);
    float ux = ppc::fmsubs(r2, dy, t12);
    float uz = ppc::fmsubs(r1, dx, t13);
    const float length = Sqrtf(ppc::fmadds(uz, uz, ppc::fmadds(ux, ux, uy * uy)));
    if (length != zero) {
        const float inverse = one / length;
        uz = uz * inverse;
        ux = ux * inverse;
        uy = uy * inverse;
    }
    const float b0 = dx * uy;
    const float b13 = dz * ux;
    const float b12 = dy * uz;
    matrix[4] = ux;
    matrix[5] = uy;
    matrix[6] = uz;
    std::memcpy(&flags, &matrix[3], 4);
    flags &= 0xfffdfffcu;
    std::memcpy(&matrix[3], &flags, 4);
    matrix[2] = ppc::fmsubs(dy, ux, b0);
    matrix[1] = ppc::fmsubs(dx, uz, b13);
    matrix[0] = ppc::fmsubs(dz, uy, b12);
}

// 0x0012f268 CKSrvCamera_ResolveGroundClearance_maybe. The clearance is the near plane's half height (tan(fov / 2) *
// 0.75) or the camera's vt+0x80 + 0.01 when larger. The final ground probe (+0x704 in, +0x714 in/out) looks below the
// position (above it when the position is under the internal camera's); on a ground the position is lifted to the
// ground plus the clearance, on a dynamic ground (class id 0x13) along its up axis; a ground with engine flag bit 3
// (a ceiling) pushes it down; status 2 (a wall) probes again from below the ground and keeps the position under it
// unless a line from the focus is blocked. `dt` is not used.
void CKSrvCamera::ResolveGroundClearance(float /*dt*/, CVector3* position, const CVector3* internalPosition,
                                         const CVector3* savedPosition, const CVector3* focus) {
    if ((m_pCurrentCamera->m_Flags & 0x1000u) == 0) return;
    const float halfAngle = (m_fCalcFov * 0.01745329052209854f) * 0.5f;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    float point[3] = {position->x, position->y, position->z};
    float pz = position->z;
    float px = position->x;
    float py = position->y;
    const float halfHeight = crt::Tanf(halfAngle) * 0.75f;
    const float zero = 0.0f;
    float clearance = m_pCurrentCamera->Vf80() + 0.01f;
    if (halfHeight > clearance) clearance = halfHeight;
    const float below = py - internalPosition->y;
    if (below >= -0.01f) {
        float height = savedPosition->y - internalPosition->y;
        point[1] = internalPosition->y;
        if (height < zero) height = zero;
        m_FinalGrdDataIn.m_fDeltaMax = zero;
        m_FinalGrdDataIn.m_fObjectHeight = height + halfHeight;
    } else {
        float delta = halfHeight + below;
        m_FinalGrdDataIn.m_fObjectHeight = halfHeight - below;
        if (delta < zero) delta = zero;
        m_FinalGrdDataIn.m_fDeltaMax = delta;
    }
    collision->GroundProbePoints(&m_FinalGrdDataIn, &m_FinalGrdDataInOut, point, 1);
    const uint32_t status = m_FinalGrdDataInOut.m_eContactStatus;
    if (status == 3) {
        if ((m_pCurrentCamera->m_Flags & 0x2000u) != 0) m_baTemporaryFlags = (m_baTemporaryFlags & ~0x4000u) | 0x4000u | 4u;
        pz = savedPosition->z;
        px = savedPosition->x;
        py = savedPosition->y;
    } else {
        m_baTemporaryFlags &= ~0x4000u;
        const CGround* ground = static_cast<const CGround*>(m_FinalGrdDataInOut.m_pGround);
        CVector3 world;
        if (((ground->m_ba16EngineFlags >> 3) & 1u) != 0) {
            // A ceiling: the position below it (unless at a face, status 0, within its height of the camera's).
            if (status != 0 ||
                !(m_FinalGrdDataInOut.m_fdH >= std::fabs(m_pCurrentCamera->m_WorldPosition.y - focus->y))) {
                GroundContact_GetWorldPoint(reinterpret_cast<const ::CGroundContactDatasInOut*>(&m_FinalGrdDataInOut), &world);
                py = (world.y - halfHeight) - 0.01f;
            }
        } else if (status == 1 || status == 0) {
            if (status == 0 && m_GContactInOut.m_eContactStatus != 3 &&
                (static_cast<const CGround*>(m_GContactInOut.m_pGround)->m_ba16EngineFlags & 8u) != 0) {
                // the position is kept
            } else {
                GroundContact_GetWorldPoint(reinterpret_cast<const ::CGroundContactDatasInOut*>(&m_FinalGrdDataInOut), &world);
                if ((m_ui8ProbeFlags & 1u) != 0 ||
                    (m_GContactInOut.m_eContactStatus != 3 &&
                     ((static_cast<const CGround*>(m_GContactInOut.m_pGround)->m_ba16EngineFlags >> 3) & 1u) != 0)) {
                    clearance = 0.01f;
                }
                float lifted = clearance + world.y;
                if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) {
                    const float floor = clearance + ground->m_fPropertieValue;
                    if (!(lifted > floor)) lifted = floor;
                }
                if ((m_baTemporaryFlags & 0x800u) == 0 && lifted >= py) py = lifted;
            }
        } else if (status == 2) {
            const bool dynamic = const_cast<CGround*>(ground)->GetClassID() == 0x13;
            GroundContact_GetWorldPoint(reinterpret_cast<const ::CGroundContactDatasInOut*>(&m_FinalGrdDataInOut), &world);
            bool probeAgain = (m_baTemporaryFlags & 1u) != 0 || !(focus->y >= world.y);
            bool onGround = !probeAgain;  // the position on the ground (+ the clearance)
            bool lineTest = false;
            CVector3 under;
            CKSrvCamera::CGroundContactDatasInOut contact;
            if (probeAgain) {
                contact.m_i32FaceIndex = -1;
                contact.m_eContactStatus = 3;
                contact.m_ui8SectorNumber = 0;
                contact.m_pGround = nullptr;
                if (dynamic) {
                    const CMatrix34* m = ground->GetWorldMatrix();
                    const float back = -(halfHeight + 0.01f);
                    point[2] = ppc::fmadds(back, m->m_up.z, world.z);
                    point[0] = ppc::fmadds(back, m->m_up.x, world.x);
                    point[1] = ppc::fmadds(back, m->m_up.y, world.y);
                } else {
                    point[1] = world.y - (halfHeight + 0.01f);
                }
                m_FinalGrdDataIn.m_fObjectHeight = halfHeight;
                m_FinalGrdDataIn.m_fDeltaMax = halfHeight * 0.1f;
                collision->GroundProbePoints(&m_FinalGrdDataIn, &contact, point, 1);
                if (contact.m_eContactStatus != 3 &&
                    (static_cast<const CGround*>(contact.m_pGround)->m_ba16EngineFlags & 8u) != 0) {
                    // A ceiling under the wall's ground: the position under it, unless a line from the focus is blocked.
                    GroundContact_GetWorldPoint(reinterpret_cast<const ::CGroundContactDatasInOut*>(&contact), &under);
                    under.y = under.y - (halfHeight + 0.01f);
                    if (contact.m_eContactStatus == 0 && focus->y > under.y) {
                        onGround = true;
                    } else {
                        lineTest = true;
                    }
                } else {
                    onGround = true;
                }
            }
            if (lineTest) {
                CLine line;
                line.m_start.x = focus->x;
                line.m_start.y = focus->y;
                line.m_start.z = focus->z;
                line.m_VectDir.x = under.x - focus->x;
                line.m_VectDir.y = under.y - focus->y;
                line.m_VectDir.z = under.z - focus->z;
                CLineCollisionDatas hit;
                hit.m_ftOnLine = kFarAway;
                hit.m_pCollisionMesh = nullptr;
                hit.m_i32FaceIndex = -1;
                hit.m_ui8SectorNumber = 0;
                const CMasksOfGrdTypeForTests masks = {1, 0x80};
                if (collision->RaycastMeshes(&line, &hit, 1, 1, &masks) == 0) {
                    // The ceiling's contact becomes the final one.
                    px = under.x;
                    py = under.y;
                    pz = under.z;
                    m_FinalGrdDataInOut.m_Normal.x = contact.m_Normal.x;
                    m_FinalGrdDataInOut.m_i32FaceIndex = contact.m_i32FaceIndex;
                    m_FinalGrdDataInOut.m_pGround = contact.m_pGround;
                    m_FinalGrdDataInOut.m_Normal.z = contact.m_Normal.z;
                    m_FinalGrdDataInOut.m_Normal.y = contact.m_Normal.y;
                    m_FinalGrdDataInOut.m_ProjectionOnGround.x = contact.m_ProjectionOnGround.x;
                    m_FinalGrdDataInOut.m_fdH = contact.m_fdH;
                    m_FinalGrdDataInOut.m_eContactStatus = contact.m_eContactStatus;
                    m_FinalGrdDataInOut.m_ProjectionOnGround.z = contact.m_ProjectionOnGround.z;
                    m_FinalGrdDataInOut.m_ProjectionOnGround.y = contact.m_ProjectionOnGround.y;
                    m_FinalGrdDataInOut.m_ui8SectorNumber = contact.m_ui8SectorNumber;
                } else {
                    if (dynamic) {
                        const CMatrix34* m = ground->GetWorldMatrix();
                        px = ppc::fmadds(clearance, m->m_up.x, world.x);
                        py = ppc::fmadds(clearance, m->m_up.y, world.y);
                        pz = ppc::fmadds(clearance, m->m_up.z, world.z);
                    } else {
                        py = clearance + world.y;
                    }
                    if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) {
                        const float floor = clearance + ground->m_fPropertieValue;
                        if (!(floor < py)) py = floor;
                    }
                }
            } else if (onGround) {
                if (dynamic) {
                    const CMatrix34* m = ground->GetWorldMatrix();
                    px = ppc::fmadds(clearance, m->m_up.x, world.x);
                    py = ppc::fmadds(clearance, m->m_up.y, world.y);
                    pz = ppc::fmadds(clearance, m->m_up.z, world.z);
                } else {
                    py = clearance + world.y;
                }
                if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) {
                    const float floor = clearance + ground->m_fPropertieValue;
                    if (!(py > floor)) py = floor;
                }
            }
        }
    }
    position->z = pz;
    position->x = px;
    position->y = py;
}

// 0x001339e8 CKSrvCamera_TurnViewTowardDesiredDirection_maybe. The limit starts (+0x46c bit 15) when the view looks
// steeply up or down (|calculation z.y| > 0.866) and the turn is larger than the step; while it holds, the calculation
// axes are the real ones turned by the step toward them (Mat4_RotateInPlace about real x x calculation x), the target
// put back at its distance.
void CKSrvCamera::TurnViewTowardDesiredDirection(float dt) {
    if ((m_baTemporaryFlags & 8u) != 0 || m_pCurrentCamera->Vf98() == 0) {
        m_baTemporaryFlags &= ~0x8000u;
        return;
    }
    const CVector3& cx = m_v3CalcAxisX;
    const CVector3& rx = m_v3RealAxisX;
    float cosine = ppc::fmadds(cx.z, rx.z, ppc::fmadds(cx.x, rx.x, cx.y * rx.y));
    if (cosine <= -1.0f) cosine = -1.0f;
    else if (cosine >= 1.0f) cosine = 1.0f;
    const float step = dt * AsFloat(m_unk7ac);
    if ((m_baTemporaryFlags & 0x8000u) == 0) {
        if (!(std::fabs(m_v3CalcAxisZ.y) <= 0.8659999966621399f)) {
            const float limit = GameCosf(step);
            if (!(cosine >= limit)) m_baTemporaryFlags = (m_baTemporaryFlags & ~0x8000u) | 0x8000u;
        }
        if ((m_baTemporaryFlags & 0x8000u) == 0) return;
    }
    if (cosine >= 1.0f) {
        m_baTemporaryFlags &= ~0x8000u;
        return;
    }
    const float ex = m_v3CalcPos.x - m_v3CalcTarget.x;
    const float ey = m_v3CalcPos.y - m_v3CalcTarget.y;
    const float ez = m_v3CalcPos.z - m_v3CalcTarget.z;
    const float distance = Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
    CMatrix34 matrix;
    std::memset(&matrix, 0, sizeof(matrix));
    BuildMatrix(&matrix, m_v3CalcAxisX, m_v3CalcAxisY, m_v3CalcAxisZ, m_v3CalcPos);
    // axis = real x x calculation x
    const float t0 = rx.z * cx.y;
    CVector3 axis;
    axis.x = ppc::fmsubs(rx.y, cx.z, t0);
    const float t11 = rx.x * cx.z;
    axis.y = ppc::fmsubs(rx.z, cx.x, t11);
    const float t0b = rx.y * cx.x;
    const float sum = ppc::fmadds(axis.x, axis.x, axis.y * axis.y);
    axis.z = ppc::fmsubs(rx.x, cx.y, t0b);
    float length = Sqrtf(ppc::fmadds(axis.z, axis.z, sum));
    if (length == 0.0f) {
        m_v3CalcTarget.z = m_v3RealTarget.z;
        m_v3CalcTarget.x = m_v3RealTarget.x;
        m_v3CalcTarget.y = m_v3RealTarget.y;
        ComputeViewBasis();
        return;
    }
    const float inverse = 1.0f / length;
    axis.z = axis.z * inverse;
    axis.x = axis.x * inverse;
    axis.y = axis.y * inverse;
    if (length <= -1.0f) length = -1.0f;
    else if (length >= 1.0f) length = 1.0f;
    const float angle = !(cosine <= 0.7070000171661377f) ? crt::Asinf(length) : crt::Acosf(cosine);
    const float rest = angle - step;
    if (rest <= 0.0f) {
        m_baTemporaryFlags &= ~0x8000u;
        return;
    }
    Mat4_RotateInPlace(&matrix, &axis, rest * -57.295780181884766f);
    m_v3CalcAxisX.x = matrix.m_right.x;
    m_v3CalcAxisX.y = matrix.m_right.y;
    m_v3CalcAxisX.z = matrix.m_right.z;
    m_v3CalcAxisY.z = matrix.m_up.z;
    m_v3CalcAxisY.x = matrix.m_up.x;
    m_v3CalcAxisY.y = matrix.m_up.y;
    m_v3CalcAxisZ.z = matrix.m_at.z;
    m_v3CalcAxisZ.x = matrix.m_at.x;
    m_v3CalcAxisZ.y = matrix.m_at.y;
    m_v3CalcTarget.z = ppc::fmadds(distance, matrix.m_at.z, m_v3CalcPos.z);
    m_v3CalcTarget.x = ppc::fmadds(distance, matrix.m_at.x, m_v3CalcPos.x);
    m_v3CalcTarget.y = ppc::fmadds(distance, matrix.m_at.y, m_v3CalcPos.y);
}

namespace {

// The turn angle of AdjustViewToKeepTargetInFrameMargins (both halves): from the cosine of the two normalised directions
// when it is small, else from the length of their cross product (asin; pi - asin when they point apart).
float TurnAngle(float cosine, float crossLength) {
    if (!(std::fabs(cosine) >= 0.7070000171661377f)) {
        if (cosine <= -1.0f) cosine = -1.0f;
        else if (cosine >= 1.0f) cosine = 1.0f;
        return crt::Acosf(cosine);
    }
    float s = crossLength;
    if (!(s <= 1.0f)) s = 1.0f;
    if (cosine >= 0.0f) return crt::Asinf(s);
    return 3.1415927410125732f - crt::Asinf(s);
}

}  // namespace

// 0x00132fd8 CKSrvCamera_AdjustViewToKeepTargetInFrameMargins_maybe. Only with at most one stacked target. The frame at
// the point's depth is tan(fov / 2) * |depth| high (* 0.75) and that / (h/w * 4/3) wide; the safe margins of the
// profile (+0x37c up, +0x3a4 down, +0x354 right, +0x32c left) narrow it. The axes turn up / down (bit 0 of the result)
// then left / right (bit 1) until the point is inside; an up axis pointing down is turned half a turn about the view
// (bit 0).
uint8_t CKSrvCamera::AdjustViewToKeepTargetInFrameMargins(float fov, float* axes, const float* point, uint8_t profile) {
    CMatrix34* m = reinterpret_cast<CMatrix34*>(axes);
    uint8_t result = 0;
    const float left = m_afSafeLeft[profile];
    const float right = m_afSafeRight[profile];
    const float up = m_afSafeUp[profile];
    const float down = m_afSafeDown[profile];
    if (static_cast<uint8_t>(m_ui32NbStacked) > 1) return 0;
    const float dy = point[1] - m->m_pos.y;
    const float dx = point[0] - m->m_pos.x;
    const float dz = point[2] - m->m_pos.z;
    const float scaledFov = fov * 0.01745329052209854f;
    const float a10 = dy * m->m_at.y;
    const float r12 = dy * m->m_right.y;
    const float u11 = dy * m->m_up.y;
    const float halfFov = scaledFov * 0.5f;
    float depth = ppc::fmadds(dz, m->m_at.z, ppc::fmadds(dx, m->m_at.x, a10));
    float side = ppc::fmadds(dz, m->m_right.z, ppc::fmadds(dx, m->m_right.x, r12));
    const float height = ppc::fmadds(dz, m->m_up.z, ppc::fmadds(dx, m->m_up.x, u11));
    float span = std::fabs(depth) * crt::Tanf(halfFov);
    const float aspect = 0x1.555556p+0f;  // 4/3 (TOC 0x3faaaaab)
    float halfWidth = span / (m_pCameraContext->m_fHeightOverWidth * aspect);
    const float halfHeight = span * 0.75f;
    // Vertical: top (f11) and -bottom (f12).
    float top = halfHeight - up;
    if (top <= 0.0f) top = 0.0f;
    const float bottomLimit = halfHeight - down;
    float negBottom = -bottomLimit;
    if (bottomLimit <= 0.0f) negBottom = -0.0f;
    bool turnVertical;
    float wanted;
    float wantedDepth = depth;
    if (!(height - top <= 0.0f) || negBottom - height > 0.0f) {
        if (depth < 0.0f) {
            wanted = height < 0.0f ? negBottom : top;
            wantedDepth = -depth;
        } else {
            float clamped = negBottom;
            if (!(height < clamped)) clamped = height;
            wanted = top;
            if (!(top < clamped)) wanted = clamped;
        }
        turnVertical = true;
    } else if (!(depth >= 0.0f)) {
        wanted = height < 0.0f ? negBottom : top;
        wantedDepth = -depth;
        turnVertical = true;
    } else {
        turnVertical = false;
    }
    const CVector3& at = m->m_at;
    if (turnVertical) {
        // v1: the wanted direction (depth, wanted height); v2: the point's (depth, height); both normalised.
        float v1y = ppc::fmadds(wantedDepth, at.y, wanted * m->m_up.y);
        float v1x = ppc::fmadds(wantedDepth, at.x, wanted * m->m_up.x);
        float v1z = ppc::fmadds(wantedDepth, at.z, wanted * m->m_up.z);
        float length = Sqrtf(ppc::fmadds(v1z, v1z, ppc::fmadds(v1x, v1x, v1y * v1y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            v1z = v1z * inverse;
            v1x = v1x * inverse;
            v1y = v1y * inverse;
        }
        float v2y = ppc::fmadds(depth, at.y, height * m->m_up.y);
        float v2x = ppc::fmadds(depth, at.x, height * m->m_up.x);
        float v2z = ppc::fmadds(depth, at.z, height * m->m_up.z);
        length = Sqrtf(ppc::fmadds(v2z, v2z, ppc::fmadds(v2x, v2x, v2y * v2y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            v2z = v2z * inverse;
            v2x = v2x * inverse;
            v2y = v2y * inverse;
        }
        result = 1;
        CVector3 axis;
        axis.y = ppc::fmsubs(v2x, v1z, v2z * v1x);
        axis.x = ppc::fmsubs(v2z, v1y, v2y * v1z);
        axis.z = ppc::fmsubs(v2y, v1x, v2x * v1y);
        const float crossLength = Sqrtf(ppc::fmadds(axis.z, axis.z, ppc::fmadds(axis.x, axis.x, axis.y * axis.y)));
        if (crossLength != 0.0f) {
            const float inverse = 1.0f / crossLength;
            axis.z = axis.z * inverse;
            axis.x = axis.x * inverse;
            axis.y = axis.y * inverse;
            if (!(crossLength <= 0.0f)) {
                const float cosine = ppc::fmadds(v2z, v1z, ppc::fmadds(v2x, v1x, v2y * v1y));
                const float angle = TurnAngle(cosine, crossLength);
                Mat4_RotateInPlace(m, &axis, angle * 57.295780181884766f);
                result = 1;
                // The point in the turned axes again.
                const float a12 = dy * at.y;
                const float r13 = dy * m->m_right.y;
                depth = ppc::fmadds(dz, at.z, ppc::fmadds(dx, at.x, a12));
                side = ppc::fmadds(dz, m->m_right.z, ppc::fmadds(dx, m->m_right.x, r13));
                span = std::fabs(depth) * crt::Tanf(halfFov);
                halfWidth = span / (m_pCameraContext->m_fHeightOverWidth * aspect);
            }
        }
    }
    // Horizontal: -right limit (f13) and left limit (f31).
    const float rightLimit = halfWidth - right;
    float negRight = -rightLimit;
    if (rightLimit <= 0.0f) negRight = -0.0f;
    float leftLimit = halfWidth - left;
    if (leftLimit <= 0.0f) leftLimit = 0.0f;
    if (!(side - leftLimit <= 0.0f) || negRight - side > 0.0f) {
        result |= 2;
        float clamped = negRight;
        if (!(side < clamped)) clamped = side;
        float wantedSide = leftLimit;
        if (!(leftLimit < clamped)) wantedSide = clamped;
        float v1y = ppc::fmadds(depth, at.y, wantedSide * m->m_right.y);
        float v1x = ppc::fmadds(depth, at.x, wantedSide * m->m_right.x);
        float v1z = ppc::fmadds(depth, at.z, wantedSide * m->m_right.z);
        float length = Sqrtf(ppc::fmadds(v1z, v1z, ppc::fmadds(v1x, v1x, v1y * v1y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            v1z = v1z * inverse;
            v1x = v1x * inverse;
            v1y = v1y * inverse;
        }
        // BUG(original): the point's direction uses |depth| (the wanted one the signed depth).
        const float absDepth = std::fabs(depth);
        float v2y = ppc::fmadds(absDepth, at.y, side * m->m_right.y);
        float v2x = ppc::fmadds(absDepth, at.x, side * m->m_right.x);
        float v2z = ppc::fmadds(absDepth, at.z, side * m->m_right.z);
        length = Sqrtf(ppc::fmadds(v2z, v2z, ppc::fmadds(v2x, v2x, v2y * v2y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            v2z = v2z * inverse;
            v2x = v2x * inverse;
            v2y = v2y * inverse;
        }
        CVector3 axis;
        axis.y = ppc::fmsubs(v1z, v2x, v2z * v1x);
        axis.x = ppc::fmsubs(v2z, v1y, v2y * v1z);
        axis.z = ppc::fmsubs(v2y, v1x, v1y * v2x);
        const float crossLength = Sqrtf(ppc::fmadds(axis.z, axis.z, ppc::fmadds(axis.x, axis.x, axis.y * axis.y)));
        if (crossLength != 0.0f) {
            const float inverse = 1.0f / crossLength;
            axis.z = axis.z * inverse;
            axis.x = axis.x * inverse;
            axis.y = axis.y * inverse;
            if (!(crossLength <= 0.0f)) {
                const float cosine = ppc::fmadds(v2z, v1z, ppc::fmadds(v1x, v2x, v2y * v1y));
                const float angle = TurnAngle(cosine, crossLength);
                Mat4_RotateInPlace(m, &axis, angle * 57.295780181884766f);
            }
        }
    }
    if (!(m->m_up.y >= 0.0f)) {
        Mat4_RotateInPlace(m, &m->m_at, 180.0f);
        result |= 1;
    }
    return result;
}

// 0x001357d0 CKSrvCamera_ApplyFrameMarginAdjustment_maybe. +0x794 the last target, +0x7a0 the spring (rest, value, speed):
// the target is put at the adjusted view's distance (at least 1) and pulled back toward the last target by the spring
// value (stiffness 15, no damping).
uint8_t CKSrvCamera::ApplyFrameMarginAdjustment(float dt, uint8_t profile, const float* point) {
    CMatrix34 axes;
    std::memset(&axes, 0, sizeof(axes));
    BuildMatrix(&axes, m_v3CalcAxisX, m_v3CalcAxisY, m_v3CalcAxisZ, m_v3CalcPos);
    const uint8_t changed = AdjustViewToKeepTargetInFrameMargins(m_fCalcFov, reinterpret_cast<float*>(&axes), point, profile);
    CVector3& last = m_v3Unk794;
    CVector3& spring = m_v3Unk7a0;  // x rest, y value, z speed
    if (changed != 0 || spring.y != 0.0f) {
        float distance = std::fabs(ppc::fmadds(point[2] - m_v3CalcPos.z, axes.m_at.z,
                                               ppc::fmadds(point[0] - m_v3CalcPos.x, axes.m_at.x,
                                                           (point[1] - m_v3CalcPos.y) * axes.m_at.y)));
        if (distance < 1.0f) distance = 1.0f;
        const float tx = ppc::fmadds(distance, axes.m_at.x, m_v3CalcPos.x);
        const float ty = ppc::fmadds(distance, axes.m_at.y, m_v3CalcPos.y);
        const float tz = ppc::fmadds(distance, axes.m_at.z, m_v3CalcPos.z);
        m_v3CalcTarget.x = tx;
        float mx = tx - last.x;
        m_v3CalcTarget.y = ty;
        float my = ty - last.y;
        m_v3CalcTarget.z = tz;
        float mz = tz - last.z;
        float length = Sqrtf(ppc::fmadds(mz, mz, ppc::fmadds(mx, mx, my * my)));
        float value = length;
        if (length == 0.0f) {
            value = 0.0f;
            spring.y = value;
        } else {
            const float inverse = 1.0f / length;
            spring.y = value;
            mz = mz * inverse;
            mx = mx * inverse;
            my = my * inverse;
        }
        const float error = spring.x - value;
        bool apply = true;
        float speed = spring.z;
        if (error == 0.0f && spring.z == 0.0f) {
            apply = false;  // the target is pulled back by the whole value
        }
        if (apply) {
            const float force = error != 0.0f ? ppc::fmsubs(error, 15.0f, spring.z * 0.0f) : spring.z * -0.0f;
            speed = ppc::fmadds(force, dt, spring.z);
            const float next = ppc::fmadds(dt, speed, value);
            if (next <= 0.0f) {
                value = 0.0f;
            } else if (!(value <= next)) {
                value = next;
            }
            if (std::fabs(speed) <= 0.0f && std::fabs(value - spring.x) <= 0.0f) {
                spring.y = spring.x;
                spring.z = 0.0f;
            } else {
                spring.y = value;
                spring.z = speed;
            }
        }
        const float back = -spring.y;
        m_v3CalcTarget.z = ppc::fmadds(back, mz, m_v3CalcTarget.z);
        m_v3CalcTarget.x = ppc::fmadds(back, mx, m_v3CalcTarget.x);
        m_v3CalcTarget.y = ppc::fmadds(back, my, m_v3CalcTarget.y);
        ComputeViewBasis();
    }
    if (spring.z != 0.0f && changed == 0 && spring.y < 0.001f) {
        spring.z = 0.0f;
        spring.y = spring.x;
    }
    last.z = m_v3CalcTarget.z;
    last.x = m_v3CalcTarget.x;
    last.y = m_v3CalcTarget.y;
    return changed != 0 ? 1 : 0;
}

// ---- the camera beacons ---------------------------------------------------------------------------------------------

namespace {

// The view the beacons are tested against (+0x934): `position`, the axes / position of `axes` copied into the matrix
// (+0x940: the words as they are, the position's in z, x, y order), 0.001 of the far plane, the far plane, the half
// width and height at distance 1 for the field of view `fov` (degrees).
void FillBeaconFrustum(CKSrvCamera* service, const CVector3& position, const CMatrix34& axes, float fov, float far) {
    const float tangent = crt::Tanf((fov * 0.01745329052209854f) * 0.5f);
    CKSrvCamera::SBeaconFrustum& frustum = service->m_BeaconFrustum;
    const float aspect = service->m_pCameraContext->m_fHeightOverWidth * 0x1.555556p+0f;
    frustum.m_v3Position.x = position.x;
    frustum.m_v3Position.y = position.y;
    frustum.m_v3Position.z = position.z;
    std::memcpy(frustum.m_pMatrix, &axes, sizeof(CMatrix34));
    frustum.m_fNear = far * 0.0010000000474974513f;
    frustum.m_fFar = far;
    frustum.m_fHalfHeight = tangent * 0.75f;
    frustum.m_pCamera = service->m_pCurrentCamera;
    frustum.m_pBeacon = service->m_pUnk920;
    frustum.m_fHalfWidth = tangent / aspect;
}

// The squared distance from the calculation position to a beacon's node (the LTM read on demand).
float BeaconDistance2(const CKSrvCamera* service, const CKCameraBeacon* beacon, CVector3* position) {
    const RwV3d& p = RwFrameGetLTM(static_cast<CSGMovable*>(beacon->m_pKGLObject)->m_pRwFrame)->pos;
    position->x = p.x;
    position->y = p.y;
    position->z = p.z;
    const float dy = p.y - service->m_v3CalcPos.y;
    const float dx = p.x - service->m_v3CalcPos.x;
    const float dz = p.z - service->m_v3CalcPos.z;
    return ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
}

}  // namespace

// 0x001366a0 CKSrvCamera_UpdateCameraBeacon_maybe. A beacon in view (CKCameraBeacon vt+0xc4; the list +0x930 holds the
// candidates, by priority +0x22 first) turns the calculation target toward the beacon's node (+0x924): fully for a
// camera with m_Flags 0x100, half way (a slerp at 0.5) otherwise; the follow track (key 0x387) only takes or drops its
// target entry (the beacon's node on the target stack). Taking or losing a beacon, with `blend`, starts a blend
// (+0x916) from the old view over acos(old z . new z) / (pi / 6) seconds; it runs while +0x918 > 0.
void CKSrvCamera::UpdateCameraBeacon(float dt, uint8_t blend) {
    const bool isTrack3 = m_pCurrentCamera->IsKindOfClass(0x387) != 0;
    bool changed = false;
    bool held = false;  // the original's path into the turn (+0x915 tested there)
    CMatrix34 calc;
    std::memset(&calc, 0, sizeof(calc));
    if (m_unke24 == 0 && m_pCurrentCamera->VfB0() != 0 && m_bUnk914 != 0) {
        BuildMatrix(&calc, m_v3CalcAxisX, m_v3CalcAxisY, m_v3CalcAxisZ, m_v3CalcPos);
        if (m_bUnk917 != 0) {
            changed = false;
            m_bUnk917 = static_cast<uint8_t>(m_unke24);  // 0
        } else {
            CMatrix34 real;
            std::memset(&real, 0, sizeof(real));
            BuildMatrix(&real, m_v3RealAxisX, m_v3RealAxisY, m_v3RealAxisZ, m_v3RealPos);
            IKSerializable* const previous = m_pUnk920;
            float best = kFarAway;
            const uint8_t previousHeld = m_bUnk915;
            m_pUnk920 = nullptr;
            m_bUnk915 = static_cast<uint8_t>(m_unke24);  // 0
            uint32_t priority = 0;
            if (previous != nullptr && (m_baTemporaryFlags & 8u) == 0) {
                // The beacon held is tested again first, from the real view toward the camera's target.
                FillBeaconFrustum(this, m_pCurrentCamera->m_WorldTarget, real, m_fRealFov, m_fRealFar);
                CKCameraBeacon* beacon = static_cast<CKCameraBeacon*>(previous);
                if (beacon->IsInView(&m_BeaconFrustum) != 0) {
                    m_pUnk920 = previous;
                    m_bUnk915 = 1;
                    best = BeaconDistance2(this, beacon, &m_v3BeaconPos);
                    priority = beacon->m_unk22;
                }
            }
            if ((m_pCurrentCamera->m_Flags & 0x10000u) == 0) {
                // The candidates from the focus with the calculation view.
                FillBeaconFrustum(this, m_v3FocusPosCopy, calc, m_fCalcFov, m_fCalcFar);
                for (CameraNode* node = m_pUnk930; node != nullptr; node = node->m_pNext) {
                    CKCameraBeacon* beacon = static_cast<CKCameraBeacon*>(node->m_pObject);
                    if (beacon->m_unk22 < priority) break;
                    if (beacon->IsInView(&m_BeaconFrustum) == 0) continue;
                    CVector3 position;
                    const float distance = BeaconDistance2(this, beacon, &position);
                    if (beacon->m_unk22 > priority || !(best <= distance)) {
                        best = distance;
                        m_bUnk915 = 1;
                        m_pUnk920 = beacon;
                        m_v3BeaconPos = position;
                        priority = beacon->m_unk22;
                    }
                }
            }
            if (previousHeld == m_bUnk915 && m_pUnk920 == previous) {
                changed = false;
            } else if (!isTrack3) {
                if (previous != nullptr) CKCameraBeacon_FireEnterLeaveSignals(static_cast<CKCameraBeacon*>(previous), 0);
                if (m_pUnk920 != nullptr) CKCameraBeacon_FireEnterLeaveSignals(static_cast<CKCameraBeacon*>(m_pUnk920), 1);
                changed = true;
            } else {
                // The follow track: the old beacon's node leaves the target stack, the new one's joins it.
                if (previous != nullptr) {
                    CKCameraBeacon* old = static_cast<CKCameraBeacon*>(previous);
                    CKCameraBeacon_FireEnterLeaveSignals(old, 0);
                    if (m_ui32NbStacked != 0) {
                        const uint32_t index = FindStackTarget(old->m_pKGLObject);
                        if (index < m_ui32NbStacked) RemoveStackEntry(index);
                    }
                }
                changed = false;
                if (m_pUnk920 != nullptr) {
                    CKCameraBeacon* beacon = static_cast<CKCameraBeacon*>(m_pUnk920);
                    CKCameraBeacon_FireEnterLeaveSignals(beacon, 1);
                    beacon = static_cast<CKCameraBeacon*>(m_pUnk920);
                    IKSerializable* node = beacon->m_pKGLObject;
                    uint32_t index = 0;
                    if (node != nullptr) {
                        const uint8_t keep = beacon->m_unk38 >= 0.0f ? 1 : 0;
                        index = FindStackTarget(node);
                        if (index < m_ui32NbStacked) {
                            if (m_aStack[index].m_unk04 != 0) {
                                m_baTemporaryFlags = (m_baTemporaryFlags & ~0x800000u) | 0x800000u;
                                m_aStack[index].m_unk04 = 0;
                            }
                            m_aStack[index].m_unk05 = keep;
                        } else {
                            m_baTemporaryFlags = (m_baTemporaryFlags & ~0x1000000u) | 0x1000000u;
                            StackEntry& entry = m_aStack[m_ui32NbStacked];
                            entry.m_unk20 = -1.0f;
                            entry.m_pTarget = node;
                            entry.m_unk05 = keep;
                            entry.m_unk0c = 0;
                            entry.m_unk10[3] = 1.0f;
                            entry.m_unk04 = 0;
                            entry.m_unk08 = -1.0f;
                            entry.m_unk10[0] = 1.0f;
                            entry.m_unk10[1] = 1.0f;
                            entry.m_unk10[2] = 1.0f;
                            entry.m_unk24[2] = kFarAway;
                            entry.m_unk24[0] = kFarAway;
                            entry.m_unk24[1] = kFarAway;
                            index = m_ui32NbStacked;
                            ++m_ui32NbStacked;
                        }
                    }
                    // BUG(original): without a node the beacon's values go to entry 0.
                    beacon = static_cast<CKCameraBeacon*>(m_pUnk920);
                    m_aStack[index].m_unk08 = beacon->m_unk38;
                    m_aStack[index].m_unk0c = static_cast<uint8_t>((static_cast<CKCameraBeacon*>(m_pUnk920)->m_unk21 >> 2) & 1u);
                }
            }
        }
        held = true;
    }
    if (held) {
        if (m_bUnk915 != 0 && !isTrack3) {
            // The calculation target turned toward the beacon.
            const CKCameraBeacon* beacon = static_cast<const CKCameraBeacon*>(m_pUnk920);
            const uint8_t keepPitch = static_cast<uint8_t>((beacon->m_unk21 >> 2) & 1u);
            CMatrix34 view = calc;
            OrientMatrixToTarget(&m_v3BeaconPos.x, &kAxisY.x, reinterpret_cast<float*>(&view), keepPitch);
            if ((m_pCurrentCamera->m_Flags & 0x100u) == 0) {
                float qView[4], qCalc[4], q[4];
                Quat_FromMatrix(qView, Floats(&view));
                Quat_FromMatrix(qCalc, Floats(&calc));
                Quat_Slerp(0.5f, q, qCalc, qView);
                Quat_ToMatrix(q, &view);
            }
            const float dx = m_v3CalcTarget.x - m_v3CalcPos.x;
            const float dy = m_v3CalcTarget.y - m_v3CalcPos.y;
            const float dz = m_v3CalcTarget.z - m_v3CalcPos.z;
            const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            m_v3CalcTarget.z = ppc::fmadds(distance, view.m_at.z, m_v3CalcPos.z);
            m_v3CalcTarget.x = ppc::fmadds(distance, view.m_at.x, m_v3CalcPos.x);
            m_v3CalcTarget.y = ppc::fmadds(distance, view.m_at.y, m_v3CalcPos.y);
            ComputeViewBasis();
        }
    } else {
        // No beacon test: one held is dropped.
        if (m_bUnk915 != 0) {
            if (m_pUnk920 != nullptr) {
                CKCameraBeacon_FireEnterLeaveSignals(static_cast<CKCameraBeacon*>(m_pUnk920), 0);
                m_pUnk920 = nullptr;
            }
            m_bUnk915 = 0;
            changed = true;
        }
    }
    if (blend == 0 || isTrack3) {
        m_bUnk916 = 0;
        return;
    }
    if (changed) {
        // The blend start: the real view turned to the real target, relative to the calculation axes.
        m_bUnk916 = 1;
        CMatrix34 start;
        std::memset(&start, 0, sizeof(start));
        BuildMatrix(&start, m_v3RealAxisX, m_v3RealAxisY, m_v3RealAxisZ, m_v3CalcPos);
        const float czx = m_v3CalcAxisZ.x;
        const float czy = m_v3CalcAxisZ.y;
        const float czz = m_v3CalcAxisZ.z;
        OrientMatrixToTarget(&m_v3RealTarget.x, &m_v3RealAxisY.x, reinterpret_cast<float*>(&start), 0);
        CMatrix34 axes;
        std::memset(&axes, 0, sizeof(axes));
        BuildMatrix(&axes, m_v3CalcAxisX, m_v3CalcAxisY, m_v3CalcAxisZ, m_v3CalcPos);
        CMatrix34 inverse;
        Mat4_Invert(&inverse, &axes);
        CMatrix34 relative;
        Mat4_Multiply(&relative, &start, &inverse);
        Quat_FromMatrix(m_afBeaconBlendQuat, Floats(&relative));
        const CVector3& rz = m_v3RealAxisZ;
        float cosine = ppc::fmadds(czz, rz.z, ppc::fmadds(czx, rz.x, czy * rz.y));
        if (cosine <= -1.0f) cosine = -1.0f;
        else if (cosine >= 1.0f) cosine = 1.0f;
        const float time = crt::Acosf(cosine) / 0.5235987305641174f;
        m_fBeaconBlendTime = time;
        m_fBeaconBlendDuration = time;
    }
    if (m_bUnk916 == 0) return;
    float left = m_fBeaconBlendTime - dt;
    if (left < 0.0f) left = 0.0f;
    m_fBeaconBlendTime = left;
    float t = 1.0f;
    if (m_fBeaconBlendDuration != 0.0f) t = (m_fBeaconBlendDuration - left) / m_fBeaconBlendDuration;
    // The view direction from the start rotation to none (relative to the calculation axes), the target put on it.
    const float identity[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float q[4];
    Quat_Slerp(t, q, m_afBeaconBlendQuat, identity);
    CMatrix34 turn;
    Quat_ToMatrix(q, &turn);
    CVector3 direction = turn.m_at;
    CMatrix34 axes;
    std::memset(&axes, 0, sizeof(axes));
    BuildMatrix(&axes, m_v3CalcAxisX, m_v3CalcAxisY, m_v3CalcAxisZ, m_v3CalcPos);
    Mat4_TransformVectors(&axes, &direction, &direction, 1);
    const float dx = m_v3CalcTarget.x - m_v3CalcPos.x;
    const float dy = m_v3CalcTarget.y - m_v3CalcPos.y;
    const float dz = m_v3CalcTarget.z - m_v3CalcPos.z;
    const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    m_v3CalcTarget.z = ppc::fmadds(distance, direction.z, m_v3CalcPos.z);
    m_v3CalcTarget.x = ppc::fmadds(distance, direction.x, m_v3CalcPos.x);
    m_v3CalcTarget.y = ppc::fmadds(distance, direction.y, m_v3CalcPos.y);
    ComputeViewBasis();
    if (m_fBeaconBlendTime != 0.0f) return;
    if (m_bUnk915 == 0) {
        m_bUnk917 = 0;
        m_pUnk920 = nullptr;
    }
    m_bUnk916 = 0;
}

// ---- the frame ------------------------------------------------------------------------------------------------------

namespace {

// The position of a target-stack node: its modelling position under a parent of class id 2, else (refreshed unless
// m_baTemporaryFlags bit 0x80000) its LTM's. The PS3 reads the stored LTM; it is computed on demand here.
const RwV3d* FocusPositionOf(CSGLeaf* leaf, uint32_t flags) {
    CSGBranch* parent = static_cast<CSGBranch*>(leaf->m_pParent);
    if (parent != nullptr && parent->GetClassID() == 2) return &leaf->m_pRwFrame->modelling.pos;
    if ((flags & 0x80000u) == 0) leaf->ForceWorldMatrixUpdate();
    return &RwFrameGetLTM(leaf->m_pRwFrame)->pos;
}

}  // namespace

// 0x00137ae0 CKSrvCamera_UpdateFrame. The camera steps run with the mean of the last 150 frame times; the pose fetch,
// the sector timer and the effects' transition with the frame's own time where the original passes it.
void CKSrvCamera::UpdateFrame(float frameTime) {
    // The temporary flags: bit 2 cleared unless bit 14; bit 13 = bit 12; bits 11, 12 and 20 cleared.
    uint32_t flags = m_baTemporaryFlags;
    if ((flags & 0x4000u) == 0) {
        m_baTemporaryFlags &= ~4u;
        flags = m_baTemporaryFlags;
    }
    m_baTemporaryFlags = ((m_baTemporaryFlags & ~0x2000u) | (((flags >> 12) & 1u) << 13)) & 0xffefe7ffu;
    // The frame-time ring and its mean.
    const uint32_t ring = m_ui32FrameTimeIndex;
    const float oldest = m_afFrameTimes[ring];
    m_afFrameTimes[ring] = frameTime;
    const float sum = frameTime + (m_fFrameTimeSum - oldest);
    m_fFrameTimeSum = sum;
    m_ui32FrameTimeIndex = ring == 0x95 ? 0 : ring + 1;
    const float mean = sum / 150.0f;
    const float inverseMean = 1.0f / mean;
    m_fFrameTimeMean = mean;
    // KStub_Nop_106d8: the debug print "Temps Camera Moyenne = %f, soit %d fps".

    // The focus: the first target's position; every target's position kept in its entry.
    if (m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr) {
        m_v3FocusPos.x = kNullVector.x;
        m_v3FocusPos.y = kNullVector.y;
        m_v3FocusPosCopy.x = m_v3FocusPos.x;
        m_v3FocusPos.z = kNullVector.z;
        m_v3FocusPosCopy.z = kNullVector.z;
        m_v3FocusPosCopy.y = kNullVector.y;
    } else {
        const RwV3d* position = FocusPositionOf(static_cast<CSGLeaf*>(m_aStack[0].m_pTarget), m_baTemporaryFlags);
        const float y = position->y;
        const float z = position->z;
        m_v3FocusPos.x = position->x;
        m_v3FocusPos.y = y;
        m_v3FocusPosCopy.x = m_v3FocusPos.x;
        m_v3FocusPos.z = z;
        m_v3FocusPosCopy.z = z;
        m_v3FocusPosCopy.y = y;
    }
    for (uint32_t i = 0; i < m_ui32NbStacked; ++i) {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_aStack[i & 0xff].m_pTarget);
        if (leaf == nullptr) continue;
        CSGBranch* parent = static_cast<CSGBranch*>(leaf->m_pParent);
        if ((parent == nullptr || parent->GetClassID() != 2) && (m_baTemporaryFlags & 0x80000u) == 0) {
            leaf->ForceWorldMatrixUpdate();
        }
        const RwV3d& position = RwFrameGetLTM(leaf->m_pRwFrame)->pos;
        m_aStack[i].m_unk24[2] = position.z;
        m_aStack[i].m_unk24[0] = position.x;
        m_aStack[i].m_unk24[1] = position.y;
    }
    UpdateCameraZones();

    // The camera sector at the focus (none while a cinematic owns the camera).
    CKCameraSector* found;
    if (m_unke24 == 0) {
        CKCameraSector* current = m_pCurrentSector;
        if (current != nullptr && m_fSectorTimer > 0.0f) {
            m_fSectorTimer = m_fSectorTimer - frameTime;
            if (m_fSectorTimer < 0.0f) {
                m_fSectorTimer = -1.0f;
                current->FlushTriggerSignals();
            }
        }
        found = FindCameraSectorAtFocus(false, nullptr);
        // KStub_Nop_106d8: a debug print of the sector mode (+0x24).
    } else {
        // KStub_Nop_106d8: a debug print.
        m_pCurrentSector = nullptr;
        found = nullptr;
    }
    if (m_pCurrentSector != found && found != nullptr) {
        m_fSectorTimer = found->m_unk54;
        if (m_pCurrentSector != nullptr) m_pCurrentSector->FlushTriggerSignals();
        // BUG(original): with an empty target stack the original passes the words at address 4 as the focus.
        IKCamera* camera = found->FindValidCamera();
        if (camera == nullptr && m_pCurrentSector == nullptr) {
            // Another sector at the focus that has cameras (the search stops back at the first one).
            const CKCameraSector* first = found;
            CKCameraSector* other = found;
            for (;;) {
                other = FindCameraSectorAtFocus(true, other);
                if (other == nullptr || other == first) break;
                camera = other->FindValidCamera();
                if (camera != nullptr) {
                    found = other;
                    break;
                }
            }
        }
        if (m_pCurrentCamera == camera) {
            m_pCurrentSector = found;
        } else {
            if (camera != nullptr) {
                const CKCameraSector* current = m_pCurrentSector;
                const uint8_t mode = (current != nullptr && (current->m_unk38 & 1u) != 0)
                                         ? static_cast<uint8_t>(current->m_unk3c)
                                         : static_cast<uint8_t>(found->m_unk34);
                m_pNextCamera = camera;
                if ((m_baTemporaryFlags & 0x10u) == 0) {
                    m_ui8TransitionMode = mode;
                    m_fSwitchTimer = 1.0f;
                    m_baTemporaryFlags = (m_baTemporaryFlags & ~0x400000u) | 0x400000u;
                }
                m_pCurrentSector = found;
            }
            if ((found->m_unk2d & 8u) != 0) m_pCurrentSector = found;
        }
        if (m_pCurrentSector != nullptr) m_pCurrentSector->QueueActivateSignals();
    }

    // The switch to the next camera.
    uint8_t switched = 0;
    if (m_pNextCamera != nullptr) {
        IKCamera* const next = m_pNextCamera;
        const uint32_t flagsAtSwitch = m_baTemporaryFlags;
        const uint32_t wasBlending = (flagsAtSwitch >> 3) & 1u;
        bool noPreviousSwitch = false;
        if ((flagsAtSwitch & 8u) != 0) noPreviousSwitch = m_bUnk885 == 0;
        m_bUnk885 = 0;
        IKCamera* current = m_pCurrentCamera;
        if (current != nullptr && current->m_unk3e != 0) m_ui8TransitionMode = static_cast<uint8_t>(current->m_unk40);
        const bool testAngle = m_pCurrentSector != nullptr ? ((m_pCurrentSector->m_unk38 >> 1) & 1u) != 0
                                                            : (flagsAtSwitch & 0x400000u) != 0;
        if (testAngle) {
            // A switch through more than +0x1c8 radians (over x/z) is a cut (mode 12).
            const float zero = 0.0f;
            float nx = next->m_WorldTarget.x - next->m_WorldPosition.x;
            float nz = next->m_WorldTarget.z - next->m_WorldPosition.z;
            float ny = zero;
            float length = Sqrtf(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, zero)));
            if (length != zero) {
                const float inverse = 1.0f / length;
                nz = nz * inverse;
                nx = nx * inverse;
                ny = inverse * zero;
            }
            float rx = m_v3RealAxisZ.x;
            float rz = m_v3RealAxisZ.z;
            float ry = zero;
            length = Sqrtf(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, zero)));
            if (length != zero) {
                const float inverse = 1.0f / length;
                rz = rz * inverse;
                rx = rx * inverse;
                ry = inverse * zero;
            }
            float cosine = ppc::fmadds(nz, rz, ppc::fmadds(nx, rx, ry * ny));
            if (cosine <= -1.0f) cosine = -1.0f;
            else if (cosine >= 1.0f) cosine = 1.0f;
            const float angle = crt::Acosf(cosine);
            if (!(AsFloat(m_unk1c8) >= angle)) m_ui8TransitionMode = 0xc;
        }
        m_baTemporaryFlags &= ~0x400000u;
        m_fBlendElapsed = 0.0f;
        const uint8_t mode = m_ui8TransitionMode;
        const float duration = mode != 0xc ? m_fSwitchTimer : 0.0f;
        m_ui8PreviousTransitionMode = mode;
        m_fBlendDuration = duration;
        m_fSwitchTimer = 0.0f;
        m_ui8TransitionMode = 0;
        // The blend start: the real pose, its quaternion, field of view, far plane and the roll.
        Blend(this, 0x7b0) = m_v3RealPos.x;
        Blend(this, 0x7b8) = m_v3RealPos.z;
        Blend(this, 0x7b4) = m_v3RealPos.y;
        Blend(this, 0x7bc) = m_v3RealTarget.x;
        Blend(this, 0x7c0) = m_v3RealTarget.y;
        Blend(this, 0x7c4) = m_v3RealTarget.z;
        Blend(this, 0x7c8) = m_fRealFov;
        Blend(this, 0x7cc) = m_fRealFar;
        Blend(this, 0x7d0) = m_fCalcRoll;
        CMatrix34 real;
        std::memset(&real, 0, sizeof(real));
        BuildMatrix(&real, m_v3RealAxisX, m_v3RealAxisY, m_v3RealAxisZ, m_v3RealPos);
        Quat_FromMatrix(&Blend(this, 0x7d4), Floats(&real));
        if (m_pCurrentCamera != nullptr) {
            m_pCurrentCamera->Stop();
            if (m_bUnk884 == 0 && (m_pCurrentCamera->m_Flags & 0x100u) != 0 && (m_pNextCamera->m_Flags & 0x100u) != 0 &&
                !noPreviousSwitch) {
                m_bUnk885 = 1;
            }
        }
        m_baTemporaryFlags |= 8u;
        if ((m_baTemporaryFlags & 0x10u) != 0) {
            m_baTemporaryFlags &= ~1u;
            m_unk8d0[0] = 0.0f;
            m_unk8d0[2] = 0.0f;
            m_unk8d0[1] = 0.0f;
        }
        m_baTemporaryFlags = (m_baTemporaryFlags | 4u) & ~0x30u;
        m_pPreviousCamera = m_pCurrentCamera;
        m_pCurrentCamera = m_pNextCamera;
        m_pNextCamera = nullptr;
        UpdateHeroGroundReference(mean, &m_v3FocusPos);
        IKCamera* camera = m_pCurrentCamera;
        camera->Start((m_baTemporaryFlags & 0x40u) != 0 ? &m_v3ScriptedStart : nullptr);
        if (m_fBlendDuration != 0.0f && m_unke24 == 0 &&
            (m_pCurrentSector == nullptr || (m_pCurrentSector->m_unk38 & 4u) == 0)) {
            // No blend through a wall: a line from the real position to the new camera.
            CLineCollisionDatas hit;
            hit.m_ftOnLine = kFarAway;
            hit.m_pCollisionMesh = nullptr;
            hit.m_i32FaceIndex = -1;
            hit.m_ui8SectorNumber = 0;
            const CMasksOfGrdTypeForTests masks = {1, 0x88};
            CLine line;
            line.m_start.x = m_v3RealPos.x;
            line.m_start.y = m_v3RealPos.y;
            line.m_start.z = m_v3RealPos.z;
            const CVector3& to = m_pCurrentCamera->m_WorldPosition;
            line.m_VectDir.x = to.x - m_v3RealPos.x;
            line.m_VectDir.y = to.y - m_v3RealPos.y;
            line.m_VectDir.z = to.z - m_v3RealPos.z;
            CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
            if (collision->RaycastMeshes(&line, &hit, 1, 0, &masks) != 0) m_fBlendDuration = 0.0f;
        }
        m_baTemporaryFlags &= ~0x40u;
        FetchTrackPose(frameTime, m_pCurrentSector, m_pCurrentCamera);
        UpdateCameraBeacon(mean, 0);
        // The internal camera on the new pose.
        m_InternalCamera.m_WorldPosition.x = m_v3CalcPos.x;
        m_InternalCamera.m_WorldPosition.z = m_v3CalcPos.z;
        m_InternalCamera.m_WorldPosition.y = m_v3CalcPos.y;
        m_InternalCamera.m_WorldTarget.x = m_v3CalcTarget.x;
        m_InternalCamera.m_WorldTarget.y = m_v3CalcTarget.y;
        m_InternalCamera.m_WorldTarget.z = m_v3CalcTarget.z;
        m_InternalCamera.m_unk18 = m_fCalcFov;
        m_InternalCamera.m_fFar = m_fCalcFar;
        ComputeDesiredBasis();
        m_v3SavedPos.x = m_v3CalcPos.x;
        m_v3SavedPos.y = m_v3CalcPos.y;
        m_v3SavedTarget.x = m_v3CalcTarget.x;
        m_v3SavedTarget.y = m_v3CalcTarget.y;
        // The distance and the turn from the real pose to the new one (the blend's), with the velocities projected on them.
        float dy = m_v3CalcPos.y - m_v3RealPos.y;
        float dx = m_v3CalcPos.x - m_v3RealPos.x;
        m_v3SavedPos.z = m_v3CalcPos.z;
        m_v3SavedTarget.z = m_v3CalcTarget.z;
        float dz = m_v3CalcPos.z - m_v3RealPos.z;
        float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (distance != 0.0f) {
            const float inverse = 1.0f / distance;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        } else {
            distance = 0.0f;
        }
        Blend(this, 0x7f4) = distance;
        const CVector3& rz = m_v3RealAxisZ;
        const CVector3& cz = m_v3CalcAxisZ;
        const float t10 = cz.z * rz.x;
        const float t11 = rz.z * cz.y;
        const float t12 = rz.y * cz.x;
        float ay = ppc::fmsubs(rz.z, cz.x, t10);
        float ax = ppc::fmsubs(rz.y, cz.z, t11);
        float az = ppc::fmsubs(cz.y, rz.x, t12);
        const float length = Sqrtf(ppc::fmadds(az, az, ppc::fmadds(ax, ax, ay * ay)));
        float sine = 0.0f;
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            az = az * inverse;
            ax = ax * inverse;
            ay = ay * inverse;
            sine = length;
            if (sine <= -1.0f) sine = -1.0f;
            else if (sine >= 1.0f) sine = 1.0f;
        }
        Blend(this, 0x808) = crt::Asinf(sine);
        if (wasBlending == 0) {
            Blend(this, 0x80c) = m_v3VelocityPos.x;
            Blend(this, 0x810) = m_v3VelocityPos.y;
            Blend(this, 0x814) = m_v3VelocityPos.z;
            Blend(this, 0x7e4) = 0.0f;
            float projected = ppc::fmadds(dz, Blend(this, 0x814), ppc::fmadds(dx, Blend(this, 0x80c), dy * Blend(this, 0x810)));
            if (projected < 0.0f) projected = 0.0f;
            Blend(this, 0x7ec) = projected;
            Blend(this, 0x818) = m_v3VelocityAxis.x;
            Blend(this, 0x81c) = m_v3VelocityAxis.y;
            Blend(this, 0x820) = m_v3VelocityAxis.z;
            Blend(this, 0x7f8) = 0.0f;
            projected = ppc::fmadds(az, Blend(this, 0x820), ppc::fmadds(ax, Blend(this, 0x818), ay * Blend(this, 0x81c)));
            if (projected < 0.0f) projected = 0.0f;
            Blend(this, 0x800) = projected;
        }
        m_unk840[1] = 0;
        m_unk849 = 1;
        m_unk840[0] = 0;
        m_unk848 = 1;
        StartCameraParamBlend(static_cast<uint8_t>(wasBlending & 1u));
        ResetCollisionProbes();
        if ((m_baTemporaryFlags & 8u) == 0 || (m_baTemporaryFlags & 0x10u) != 0) {
            m_baTemporaryFlags &= 0xfffefffeu;
            m_unk8d0[0] = 0.0f;
            m_unk8d0[2] = 0.0f;
            m_unk8d0[1] = 0.0f;
        }
        m_baTemporaryFlags &= ~0x20000u;
        m_csfCollisionSmoothSpring.m_fTargetedValue = 0.0f;
        m_csfCollisionSmoothSpring.m_fCurrentSpeed = 0.0f;
        m_csfCollisionSmoothSpring.m_fCurrentValue = 0.0f;
        m_v3Unk77c.x = kNullVector.x;
        m_v3Unk77c.z = kNullVector.z;
        m_v3Unk77c.y = kNullVector.y;
        m_v3Unk788.x = kNullVector.x;
        m_v3Unk788.z = kNullVector.z;
        m_v3Unk788.y = kNullVector.y;
        m_v3Unk794.x = m_v3CalcTarget.x;
        m_v3Unk794.z = m_v3CalcTarget.z;
        m_v3Unk794.y = m_v3CalcTarget.y;
        m_v3Unk7a0.x = 0.0f;
        m_v3Unk7a0.z = 0.0f;
        m_v3Unk7a0.y = 0.0f;
        switched = 1;
        CaptureHeroHeadingLock();
    }

    if (m_pCurrentCamera != nullptr) {
        UpdateHeroGroundReference(mean, &m_v3FocusPos);
        if ((m_baTemporaryFlags & 8u) != 0) m_baTemporaryFlags |= 4u;
        m_pCurrentCamera->Update(mean);
        m_baTemporaryFlags &= 0xfe7fffffu;
        FetchTrackPose(frameTime, m_pCurrentSector, m_pCurrentCamera);
        m_v3SavedPos.x = m_v3CalcPos.x;
        m_v3SavedPos.y = m_v3CalcPos.y;
        m_v3SavedPos.z = m_v3CalcPos.z;
        m_v3SavedTarget.x = m_v3CalcTarget.x;
        m_v3SavedTarget.y = m_v3CalcTarget.y;
        m_v3SavedTarget.z = m_v3CalcTarget.z;
        UpdateCameraBeacon(mean, 1);
        // The smoothing of the camera's pose (m_Flags: 0x40 the target by its own mode, else 0x100 by mode 2; 0x20 the
        // position, then the ground clearance), the frame margins (0x100).
        IKCamera* camera = m_pCurrentCamera;
        if ((camera->m_Flags & 0x40u) != 0) {
            StepSmoothedTowardTrackPose(mean, camera->m_TargetSmoothMode);
        } else if ((camera->m_Flags & 0x100u) != 0) {
            StepSmoothedTowardTrackPose(mean, 2);
        }
        camera = m_pCurrentCamera;
        if ((camera->m_Flags & 0x20u) != 0) {
            StepViewOffsetSpring(mean, camera->m_CameraSmoothMode);
            ResolveGroundClearance(mean, &m_v3CalcPos, &m_InternalCamera.m_WorldPosition, &m_v3SavedPos, &m_v3FocusPosCopy);
            ComputeViewBasis();
            camera = m_pCurrentCamera;
        }
        if ((camera->m_Flags & 0x100u) != 0) {
            float point[3] = {m_v3FocusPosCopy.x, m_v3FocusPosCopy.y, m_v3FocusPosCopy.z};
            if (static_cast<uint8_t>(m_ui32NbStacked) > 1) {
                // Two targets: the middle of the first two.
                point[0] = (point[0] + m_aStack[1].m_unk24[0]) * 0.5f;
                point[1] = (point[1] + m_aStack[1].m_unk24[1]) * 0.5f;
                point[2] = (point[2] + m_aStack[1].m_unk24[2]) * 0.5f;
            }
            if (camera != nullptr) {
                const float y = point[1];
                const uint8_t profile = camera->GetEffectiveProfileIndex();
                camera = m_pCurrentCamera;
                point[1] = y + m_afSafeOffsetYFromBasicTarget[profile];
            }
            ApplyFrameMarginAdjustment(mean, camera->GetEffectiveProfileIndex(), point);
        }
        if (switched == 0) {
            // The velocities (per second of the mean frame time) of the position, the target and the view axis.
            const CVector3& ip = m_InternalCamera.m_WorldPosition;
            const CVector3& it = m_InternalCamera.m_WorldTarget;
            m_v3VelocityPos.x = inverseMean * (m_v3CalcPos.x - ip.x);
            m_v3VelocityPos.y = inverseMean * (m_v3CalcPos.y - ip.y);
            m_v3VelocityPos.z = inverseMean * (m_v3CalcPos.z - ip.z);
            m_v3VelocityTarget.x = inverseMean * (m_v3CalcTarget.x - it.x);
            m_v3VelocityTarget.y = inverseMean * (m_v3CalcTarget.y - it.y);
            m_v3VelocityTarget.z = inverseMean * (m_v3CalcTarget.z - it.z);
            float ox = it.x - ip.x;
            float oy = it.y - ip.y;
            float oz = it.z - ip.z;
            const float length = Sqrtf(ppc::fmadds(oz, oz, ppc::fmadds(ox, ox, oy * oy)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                oz = oz * inverse;
                ox = ox * inverse;
                oy = oy * inverse;
            }
            const CVector3& cz = m_v3CalcAxisZ;
            CVector3& w = m_v3VelocityAxis;
            w.x = ppc::fmsubs(oy, cz.z, oz * cz.y);
            w.y = ppc::fmsubs(oz, cz.x, ox * cz.z);
            const float sumXY = ppc::fmadds(w.x, w.x, w.y * w.y);
            w.z = ppc::fmsubs(ox, cz.y, oy * cz.x);
            const float turn = Sqrtf(ppc::fmadds(w.z, w.z, sumXY));
            float sine = 0.0f;
            if (turn != 0.0f) {
                const float inverse = 1.0f / turn;
                w.z = inverse * w.z;
                w.x = inverse * w.x;
                w.y = inverse * w.y;
                sine = turn;
                if (sine <= -1.0f) sine = -1.0f;
                else if (sine >= 1.0f) sine = 1.0f;
            }
            const float rate = crt::Asinf(sine) / mean;
            w.z = rate * w.z;
            w.x = rate * w.x;
            w.y = rate * w.y;
        }
        // The internal camera on the calculation pose; the turn limit, the transition, the effects, the fov blend.
        m_InternalCamera.m_WorldPosition.x = m_v3CalcPos.x;
        m_InternalCamera.m_WorldPosition.z = m_v3CalcPos.z;
        m_InternalCamera.m_WorldPosition.y = m_v3CalcPos.y;
        m_InternalCamera.m_WorldTarget.y = m_v3CalcTarget.y;
        m_InternalCamera.m_WorldTarget.z = m_v3CalcTarget.z;
        m_InternalCamera.m_WorldTarget.x = m_v3CalcTarget.x;
        m_InternalCamera.m_unk18 = m_fCalcFov;
        m_InternalCamera.m_fFar = m_fCalcFar;
        ComputeDesiredBasis();
        TurnViewTowardDesiredDirection(mean);
        UpdateCameraTransition(mean);
        ApplyCameraEffects(mean);
        if ((m_baTemporaryFlags & 0x100u) != 0) {
            // The state +0x8f8 (7 floats) of Math_ApproachWithAccelDecel (StartCameraParamBlend sets it).
            const float fov = Math_ApproachWithAccelDecel(mean, reinterpret_cast<float*>(m_unk8f8));
            m_fCalcFov = fov;
            if (m_pCurrentCamera->m_unk18 == fov) m_baTemporaryFlags &= ~0x100u;
        }
        ReleaseHeroHeadingLock();
        if (m_bHeadingLocked == 0) {
            if ((m_baTemporaryFlags & 0x8000u) == 0 && m_pCurrentCamera->VfB4() != 0 && (m_bUnk915 != 0 || m_bUnk916 != 0)) {
                // A beacon turns the view: the heading is the direction of the pose before the smoothing.
                CVector3& heading = m_v3HeadingDir;
                const float hy = m_v3SavedTarget.y - m_v3SavedPos.y;
                const float hx = m_v3SavedTarget.x - m_v3SavedPos.x;
                const float hz = m_v3SavedTarget.z - m_v3SavedPos.z;
                heading.x = hx;
                heading.y = hy;
                heading.z = hz;
                const float length = Sqrtf(ppc::fmadds(hz, hz, ppc::fmadds(hx, hx, hy * hy)));
                if (length != 0.0f) {
                    const float inverse = 1.0f / length;
                    heading.z = inverse * heading.z;
                    heading.x = inverse * heading.x;
                    heading.y = inverse * heading.y;
                }
            } else {
                m_v3HeadingDir.x = m_v3CalcAxisZ.x;
                m_v3HeadingDir.z = m_v3CalcAxisZ.z;
                m_v3HeadingDir.y = m_v3CalcAxisZ.y;
            }
        }
        // The real pose is the calculation pose.
        m_v3RealPos = m_v3CalcPos;
        m_v3RealTarget = m_v3CalcTarget;
        m_fRealFov = m_fCalcFov;
        m_fRealFar = m_fCalcFar;
        m_v3RealAxisX = m_v3CalcAxisX;
        m_v3RealAxisY = m_v3CalcAxisY;
        m_v3RealAxisZ = m_v3CalcAxisZ;
        // The camera node: the axes and the position written (m_baTemporaryFlags bit 7), or the position and a look at the
        // real target.
        if ((m_baTemporaryFlags & 0x80u) != 0) {
            RwFrame* frame = m_pCameraNode->m_pRwFrame;
            frame->modelling.right.x = m_v3CalcAxisX.x;
            frame->modelling.right.y = m_v3CalcAxisX.y;
            frame->modelling.right.z = m_v3CalcAxisX.z;
            frame->modelling.flags &= 0xfffdfffcu;
            RwFrame_MarkDirty(frame);
            frame = m_pCameraNode->m_pRwFrame;
            frame->modelling.up.x = m_v3CalcAxisY.x;
            frame->modelling.up.y = m_v3CalcAxisY.y;
            frame->modelling.up.z = m_v3CalcAxisY.z;
            frame->modelling.flags &= 0xfffdfffcu;
            RwFrame_MarkDirty(frame);
            frame = m_pCameraNode->m_pRwFrame;
            frame->modelling.at.x = m_v3CalcAxisZ.x;
            frame->modelling.at.y = m_v3CalcAxisZ.y;
            frame->modelling.at.z = m_v3CalcAxisZ.z;
            frame->modelling.flags &= 0xfffdfffcu;
            RwFrame_MarkDirty(frame);
            frame = m_pCameraNode->m_pRwFrame;
            frame->modelling.pos.z = m_v3RealPos.z;
            frame->modelling.pos.x = m_v3RealPos.x;
            frame->modelling.pos.y = m_v3RealPos.y;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);
        } else {
            RwFrame* frame = m_pCameraNode->m_pRwFrame;
            frame->modelling.pos.z = m_v3RealPos.z;
            frame->modelling.pos.x = m_v3RealPos.x;
            frame->modelling.pos.y = m_v3RealPos.y;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);
            m_pCameraNode->LookAtPoint(&m_v3RealTarget.x, &m_v3RealAxisY.x);
        }
        // The camera context: the field of view (forced by vt+0xa8, the 4:3 reference window by vt+0xa0) and the clip
        // planes (near 0.001 of the far plane); then the roll.
        CameraContext* context = m_pCameraContext;
        const float fov = m_fRealFov;
        const uint8_t force = m_pCurrentCamera->VfA8();
        const uint8_t reference = m_pCurrentCamera->VfA0();
        context->SetFieldOfView(fov, 0, force, reference);
        m_pCameraContext->SetClipPlanes(m_fRealFar, 0.01f, 1, 0);
        if (m_fCalcRoll != 0.0f) m_pCameraNode->RotateInPlace(&m_v3RealAxisZ.x, m_fCalcRoll);
        const RwMatrix& modelling = m_pCameraNode->m_pRwFrame->modelling;
        m_v3FrameRight.x = modelling.right.x;
        m_v3FrameRight.z = modelling.right.z;
        m_v3FrameRight.y = modelling.right.y;
        m_v3FrameUp.x = modelling.up.x;
        m_v3FrameUp.z = modelling.up.z;
        m_v3FrameUp.y = modelling.up.y;
        m_v3FrameAt.x = modelling.at.x;
        m_v3FrameAt.z = modelling.at.z;
        m_v3FrameAt.y = modelling.at.y;
        UpdateFrustumPlanes();
        // The dodge spheres: the first half its radius ahead of the camera, the second at the pose before the smoothing.
        IKBoundingVolume* dodge = static_cast<IKBoundingVolume*>(m_pDodgeBS);
        const float ahead = dodge->m_fRadius * 0.5f;
        RwFrame* dodgeFrame = dodge->m_pRwFrame;
        dodgeFrame->modelling.pos.x = ppc::fmadds(ahead, m_v3RealAxisZ.x, m_v3RealPos.x);
        dodgeFrame->modelling.pos.y = ppc::fmadds(ahead, m_v3RealAxisZ.y, m_v3RealPos.y);
        dodgeFrame->modelling.pos.z = ppc::fmadds(ahead, m_v3RealAxisZ.z, m_v3RealPos.z);
        dodgeFrame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(dodgeFrame);
        IKBoundingVolume* push = static_cast<IKBoundingVolume*>(m_pDodgeBSPushCam);
        RwFrame* pushFrame = push->m_pRwFrame;
        pushFrame->modelling.pos.z = m_v3SavedPos.z;
        pushFrame->modelling.pos.x = m_v3SavedPos.x;
        pushFrame->modelling.pos.y = m_v3SavedPos.y;
        pushFrame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(pushFrame);
        // Bit 10 = bit 9, bit 9 cleared.
        m_baTemporaryFlags = (m_baTemporaryFlags & ~0x600u) | (((m_baTemporaryFlags >> 9) & 1u) << 10);
        // The beacons of this frame back to their pool (FreeListPool 0xceaa20 in the original).
        for (CameraNode* node = m_pUnk930; node != nullptr;) {
            CameraNode* nextNode = node->m_pNext;
            delete node;
            node = nextNode;
        }
        m_pUnk930 = nullptr;
        // The hero position kept for the heading lock while the camera follows the focused hero.
        CDefaultGameManager* manager = g_pEngine->m_gameManager;
        IKSerializable* heroCamera = manager->GetFocusedHeroCamera();
        if (heroCamera != nullptr && m_ui32NbStacked != 0 && m_aStack[0].m_pTarget == heroCamera) {
            const float* hero = manager->GetFocusedHeroPosition();
            m_v3LockHeroPos.x = hero[0];
            m_v3LockHeroPos.z = hero[2];
            m_v3LockHeroPos.y = hero[1];
        }
        m_unk24[1] = m_unk24[0];
    }
    m_baTemporaryFlags &= ~0x2000000u;
}
