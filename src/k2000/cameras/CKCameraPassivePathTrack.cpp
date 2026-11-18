// Reconstructed original translation unit: 0x13e2b8-0x1419e0 (GAME_TOC1, main_toc1), 23 functions, 20 live.
// Primary class: CKCameraPassivePathTrack  key 0x287  category Camera  size 0x134  vtable 0xb1a380
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13e2b8  CKCameraPassivePathTrack_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x13e308  CKCameraPassivePathTrack_vf54  (Pause, empty)
//   [x] 0x13e310  CKCameraPassivePathTrack_vf5C  (Resume, empty)
//   [ ] 0x13e318  FUN_0013e318  [dead]
//   [ ] 0x13e3a8  CKCameraPassivePathTrack_GetTargetPosition_maybe  [dead]
//   [ ] 0x13e4e8  FUN_0013e4e8  [dead]
//   [ ] 0x13e560  RegisterCKCameraPassivePathTrackClass
//   [ ] 0x13e5d8  _GLOBAL__I_13e5d8
//   [x] 0x13e5e8  CKCameraPassivePathTrack_PostLoad
//   [x] 0x13e630  CKCameraPassivePathTrack_RecursiveRegistration
//   [x] 0x13e6e0  CKCameraPassivePathTrack_ComputeCameraPose_maybe
//   [x] 0x13e9e8  CKCameraPassivePathTrack_Deactivate_maybe  (Stop, CKCameraPassivePathTrack.h)
//   [x] 0x13ea10  CKCameraPassivePathTrack_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x13ea38  CKCameraPassivePathTrack_Construct  (the constructor)
//   [x] 0x13eae8  CKCameraPassivePathTrack_Construct_2  (the constructor: the same stores)
//   [x] 0x13eb98  CKCameraPassivePathTrack_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x13ec38  CKCameraPassivePathTrack_MessageProc
//   [x] 0x13edf8  CKCameraPassivePathTrack_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x13ef68  CKCameraPassivePathTrack_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x13f030  CKCameraPassivePathTrack_Activate_maybe  (Start)
//   [x] 0x13fa18  CKCameraPassivePathTrack_Update_maybe
//   [x] 0x141020  CKCameraPassivePathTrack_Load
//   [ ] 0x141548  CKCameraPassivePathTrack_Save
//
//   [x] 0x9a7738  CKCameraPassivePathTrack_IsKindOfClass  [inline]  (CKCameraPassivePathTrack.h)
//   [x] 0x9a7760  CKCameraPassivePathTrack_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a7768  CKCameraPassivePathTrack_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a7770  CKCameraPassivePathTrack_vf84  [inline]  (CKCameraPassivePathTrack.h)
//   [x] 0x9a7778  CKCameraPassivePathTrack_Destructor  [inline]  (the header's destructor)
//   [x] 0x9a77a8  CKCameraPassivePathTrack_DeletingDestructor  [inline]  (the header's destructor)
#include "k2000/cameras/CKCameraPassivePathTrack.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {

const float kZero = 0.0f;           // TOC1 -0x3dc4
const float kOne = 1.0f;            // TOC1 -0x3d94 0x3f800000
const float kPoseDt = 1000.0f;      // TOC1 -0x3d64 0x447a0000
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC1 -0x3d90)
const float kHalf = 0.5f;            // TOC1 -0x3d60 0x3f000000
const float kFollowMax = 100000.0f;  // TOC1 -0x3d58 0x47c35000
const float kFollowRest = 1e-05f;    // TOC1 -0x3d54 0x3727c5ac
const float kSlowSpeed = 0.2f;       // TOC1 -0x3d50 0x3e4ccccd

CKSrvCamera* Service() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }  // engine +0x70
IKPath* PathOf(IKSerializable* path) { return static_cast<IKPath*>(path); }

// The wrap of the bit-6 paths: below 0 the length added, at or past it the length taken off.
float WrapOnPath(IKPath* path, float distance) {
    const float length = path->GetLength();  // vt+0x5c
    while (distance < kZero) distance = distance + length;
    while (length <= distance) distance = distance - length;  // cror lt|eq
    return distance;
}

}  // namespace

CKCameraPassivePathTrack::CKCameraPassivePathTrack() {
    m_unk60 = 0.0f;
    m_unk68 = 0.0f;
    m_unk64 = 0.0f;
    m_ui16Flags = 0;
    m_afStart[1] = 1.0f;   // TOC1 -0x3d94
    m_afStart[2] = 2.0f;   // TOC1 -0x3d88 0x40000000
    m_unk94 = 50.0f;       // 0x42480000
    m_unk9C = 20.0f;       // 0x41a00000
    m_unkA4 = 0.12f;       // 0x3df5c28f
    m_unkA8 = 0.3f;        // 0x3e99999a
    m_unkAC = 0.0f;
    m_afStart[0] = 0.0f;
    m_pCameraPath = nullptr;
    m_pTargetPath = nullptr;
    m_afStart[3] = 0.0f;
    m_unk90 = 0.0f;
    m_unk98 = 20.0f;
    m_unkA0 = 0.0f;
    // The fresh heap's zeroes.
    m_fTargetPathDist = 0.0f;
    m_fCameraPathDist = 0.0f;
    m_i32Direction = 0;
    m_fLateral = 0.0f;
    m_fPathSpeed = 0.0f;
    m_padB2[0] = 0;
    m_padB2[1] = 0;
    for (uint32_t& i : m_aui32ParamIndex) i = 0;
    std::memset(m_aBlend, 0, sizeof(m_aBlend));
}

// 0x00141020 CKCameraPassivePathTrack_Load
int32_t CKCameraPassivePathTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);  // 0x00144580
    if (type != 0) return 1;
    IKFile_ReadRef(file, &m_pCameraPath);
    IKFile_ReadRef(file, &m_pTargetPath);
    for (float& value : m_afStart) ReadF32LE(file, &value);
    ReadF32LE(file, &m_unk90);
    ReadF32LE(file, &m_unk94);
    ReadF32LE(file, &m_unk98);
    ReadF32LE(file, &m_unk9C);
    ReadF32LE(file, &m_unkA0);
    ReadF32LE(file, &m_unkA4);
    ReadF32LE(file, &m_unkA8);
    ReadF32LE(file, &m_unkAC);
    ReadU16LE(file, &m_ui16Flags);
    ReadF32LE(file, &m_fPathSpeed);
    return 1;
}

// 0x0013e5e8 CKCameraPassivePathTrack_PostLoad
int32_t CKCameraPassivePathTrack::PostLoad(int32_t type) {
    IKCamera::PostLoad(type);  // KStub_Return1_144570
    m_aui32ParamIndex[3] = 0;
    m_aui32ParamIndex[0] = 0;
    m_aui32ParamIndex[1] = 0;
    m_aui32ParamIndex[2] = 0;
    return 1;
}

// 0x0013e630 CKCameraPassivePathTrack_RecursiveRegistration
void CKCameraPassivePathTrack::RecursiveRegistration(int32_t type) {
    IKCamera::RecursiveRegistration(type);  // 0x00144108
    if (m_pCameraPath != nullptr) m_pCameraPath->RecursiveRegistration(type);  // vt+0x24
    if (m_pTargetPath != nullptr) m_pTargetPath->RecursiveRegistration(type);
}

// 0x0013ec38 CKCameraPassivePathTrack_MessageProc (the jump table 0x13ec68)
int32_t CKCameraPassivePathTrack::MessageProc(uint16_t message, void* data) {
    const uint16_t k = static_cast<uint16_t>(message - 0x600);
    if (k > 7) return 1;
    const uint32_t slot = k >> 1;
    if ((k & 1u) == 0) {
        m_aui32ParamIndex[slot] = *static_cast<const uint32_t*>(data);
        return 0;
    }
    // The blend retargeted from the camera service's parameter entry (three words: x the acceleration, z the
    // deceleration and the top speed); the message's float the target, the speed 0 (stw).
    const float target = *static_cast<const float*>(data);
    const uint32_t* entry = Service()->m_unk150 + m_aui32ParamIndex[slot] * 3u;
    SParamBlend& blend = m_aBlend[slot];
    std::memcpy(&blend.m_accel, &entry[0], 4);
    std::memcpy(&blend.m_decel, &entry[2], 4);
    std::memcpy(&blend.m_maxSpeed, &entry[2], 4);
    blend.m_target = target;
    blend.m_speed = 0.0f;
    return 0;
}

// 0x0013e6e0 CKCameraPassivePathTrack_ComputeCameraPose_maybe
void CKCameraPassivePathTrack::ComputeCameraPose(float dt, const CVector3* cameraPos, CVector3* target) {
    CMatrix34 m = {};
    m.m_ui32Flags = 0x20003u;
    m.m_at.z = kOne;
    m.m_up.y = kOne;
    m.m_right.x = kOne;
    m.m_pos = *cameraPos;
    m.m_ui32Flags &= 0xfffdffffu;
    IKCamera::OrientMatrixToTarget(target, &kAxisY, &m);  // 0x00145ee0
    CKSrvCamera* service = Service();
    IKSerializable* followed = service->m_ui32NbStacked != 0 ? service->m_aStack[0].m_pTarget : nullptr;
    const float dy = target->y - cameraPos->y;
    const float dx = target->x - cameraPos->x;
    const float dz = target->z - cameraPos->z;
    const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x10690
    CDefaultGameManager* gm = g_pEngine->m_gameManager;  // engine +0x8c
    float goal = kZero;
    if (followed != nullptr && gm->GetFocusedHeroCamera() == followed) {  // vt+0x120
        const float* move = gm->GetFocusedHeroMoveVector();  // vt+0x130
        float vx = move[0];
        float vz = move[2];
        float vy = kZero;
        const float length = std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, kZero)));
        if (length != kZero) {
            const float inv = kOne / length;
            vz = vz * inv;
            vx = vx * inv;
            vy = inv * kZero;
        }
        goal = ppc::fmadds(vz, m.m_right.z, ppc::fmadds(vx, m.m_right.x, vy * m.m_right.y)) * m_unkA4;
    }
    const float current = m_fLateral;
    if (goal < current) {
        const float next = current - dt * m_unkA8;  // fmuls, fsubs
        m_fLateral = (goal <= next || goal != goal || next != next) ? next : goal;  // ble (NaN: next)
    } else if (!(goal <= current)) {  // bge, then ble: equal or NaN leaves it
        const float next = ppc::fmadds(dt, m_unkA8, current);
        m_fLateral = goal < next ? goal : next;  // blt
    }
    float halfWidth;
    float halfHeight;
    GetHalfExtentsAtDistance(distance, &halfWidth, &halfHeight);  // 0x00144278
    const float k = (m_fLateral + m_fLateral) * halfWidth;
    target->z = ppc::fmadds(k, m.m_right.z, target->z);
    target->x = ppc::fmadds(k, m.m_right.x, target->x);
    target->y = ppc::fmadds(k, m.m_right.y, target->y);
}

// 0x0013f030 CKCameraPassivePathTrack_Activate_maybe: the attached fx started; with a camera path the four blends
// restarted on their loaded values, the target placed (on the target path nearest the service's focus, or the focus;
// raised by the height blend), the camera placed on its path by the start mode, then (Activate's tail, as Update's
// follow) the height clamped against the focus, the target moved on and with bit 5 the lateral lead.
void CKCameraPassivePathTrack::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8
    if (m_pCameraPath == nullptr) return;
    for (uint32_t i = 0; i < 4; ++i) {
        SParamBlend& b = m_aBlend[i];
        b.m_accel = kZero;
        b.m_current = kZero;
        b.m_target = kZero;
        b.m_decel = kZero;
        b.m_maxSpeed = kZero;
        b.m_speed = kZero;
        b.m_speedBonus = kZero;
        b.m_current = m_afStart[i];
        b.m_target = m_afStart[i];
        m_aui32ParamIndex[i] = 0;
    }
    const float lead = m_afStart[0];        // f30 (+0x80)
    const float step = m_aBlend[3].m_current;  // f31 (+0x124)
    CKSrvCamera* service = Service();
    IKPath* camera = PathOf(m_pCameraPath);
    CVector3 point;
    if (m_pTargetPath != nullptr) {
        m_fTargetPathDist = PathOf(m_pTargetPath)->GetClosestDistanceAlong(&service->m_v3FocusPos, 1);  // vt+0x58
        PathOf(m_pTargetPath)->GetPointAtDistance(m_fTargetPathDist, &point, nullptr);                // vt+0x54
    } else {
        m_fTargetPathDist = kZero;
        point = service->m_v3FocusPos;
    }
    m_WorldTarget.x = point.x;
    m_WorldTarget.z = point.z;
    m_WorldTarget.y = point.y + m_aBlend[1].m_current;
    const uint32_t mode = m_ui16Flags & 7u;
    if (mode == 0) {
        // The nearer end of the camera path (flat distances to the target).
        CVector3 first;
        CVector3 last;
        camera->GetPointAtDistance(kZero, &first, nullptr);
        camera->GetPointAtDistance(camera->GetLength(), &last, nullptr);
        const float az = first.z - m_WorldTarget.z;
        const float bz = last.z - m_WorldTarget.z;
        const float ax = first.x - m_WorldTarget.x;
        const float bx = last.x - m_WorldTarget.x;
        const float da = ppc::fmadds(ax, ax, az * az);
        const float db = ppc::fmadds(bx, bx, bz * bz);
        if (da > db) {
            m_fCameraPathDist = camera->GetLength();
            m_WorldPosition = last;
        } else {
            m_fCameraPathDist = kZero;
            m_WorldPosition = first;
        }
    } else if (mode == 1) {
        m_fCameraPathDist = camera->GetClosestDistanceAlong(&m_WorldTarget, 1);
        camera->GetPointAtDistance(m_fCameraPathDist, &m_WorldPosition, nullptr);
    } else if (mode == 2) {
        const CVector3* from = service->m_pPreviousCamera != nullptr ? &service->m_v3RealPos : &m_WorldTarget;
        m_fCameraPathDist = camera->GetClosestDistanceAlong(from, 1);
        if (((m_ui16Flags >> 6) & 1u) != 0) m_fCameraPathDist = WrapOnPath(camera, m_fCameraPathDist);
        camera->GetPointAtDistance(m_fCameraPathDist, &m_WorldPosition, nullptr);
    } else if (mode == 3 || mode == 4) {
        const float nearest = camera->GetClosestDistanceAlong(&m_WorldTarget, 1);
        m_fCameraPathDist = nearest;
        const uint32_t choice = (m_ui16Flags >> 8) & 3u;
        int32_t way = 0;  // 1 forward, -1 backward, 0 neither
        if (choice == 1) {
            way = 1;
        } else if (choice == 2) {
            way = -1;
        } else if (choice == 0) {
            if (service->m_pPreviousCamera == nullptr) {
                way = -1;
            } else {
                const float previous = camera->GetClosestDistanceAlong(&service->m_v3RealPos, 1);
                if (previous == m_fCameraPathDist) {
                    // The same point: the way the previous camera looked along the path.
                    CVector3 at;
                    CVector3 dir;
                    camera->GetPointAtDistance(previous, &at, &dir);
                    const CVector3& axis = service->m_v3RealAxisZ;
                    const float dot = ppc::fmadds(dir.z, axis.z, ppc::fmadds(dir.x, axis.x, dir.y * axis.y));
                    way = dot <= kZero ? 1 : -1;  // cror lt|eq (NaN: backward)
                } else {
                    way = previous > m_fCameraPathDist ? 1 : -1;  // ble (NaN: backward)
                }
            }
        }
        if (way > 0) {
            m_ui16Flags = static_cast<uint16_t>((m_ui16Flags & 0xff7fu) | 0x80u);
            m_fCameraPathDist = step + m_fCameraPathDist;
        } else if (way < 0) {
            m_ui16Flags = static_cast<uint16_t>(m_ui16Flags & 0xff7fu);
            m_fCameraPathDist = m_fCameraPathDist - step;
        }
        if (((m_ui16Flags >> 6) & 1u) != 0) m_fCameraPathDist = WrapOnPath(camera, m_fCameraPathDist);
        camera->GetPointAtDistance(m_fCameraPathDist, &m_WorldPosition, nullptr);
    }
    // The tail (0x13f230).
    m_unk60 = kZero;
    m_unk68 = kZero;
    m_unk64 = kZero;
    m_i32Direction = 1;
    m_fLateral = kZero;
    const float offset = m_unkA0;
    const float floor = m_aBlend[2].m_current + service->m_v3FocusPos.y;
    float y = m_WorldPosition.y;
    if (offset < kZero) {
        const float low = offset + y;
        if (low >= floor) {
            y = low;
        } else if (!(y <= floor)) {
            y = floor;
        }
    } else if (!(y >= floor)) {
        const float low = y + offset;
        y = floor >= low ? low : floor;  // cror gt|eq (NaN: the floor)
    }
    m_WorldPosition.y = y;
    if (m_pTargetPath != nullptr) {
        m_fTargetPathDist = m_fTargetPathDist + m_aBlend[0].m_current;
        PathOf(m_pTargetPath)->GetPointAtDistance(m_fTargetPathDist, &m_WorldTarget, nullptr);
        m_WorldTarget.y = m_WorldTarget.y + m_aBlend[1].m_current;
    } else if (service->m_ui32NbStacked != 0) {
        // The target ahead of the service's first target along its at axis by the lead blend's start value.
        const RwV3d& at = static_cast<CSGMovable*>(service->m_aStack[0].m_pTarget)->m_pRwFrame->ltm.at;  // frame +0x70
        m_WorldTarget.z = ppc::fmadds(lead, at.z, m_WorldTarget.z);
        m_WorldTarget.x = ppc::fmadds(lead, at.x, m_WorldTarget.x);
        m_WorldTarget.y = ppc::fmadds(lead, at.y, m_WorldTarget.y);
    }
    // BUG(original): with no target path and no stacked target the original reads the null target path's frame (+0x04);
    // nothing here.
    if (((m_ui16Flags >> 5) & 1u) == 0) return;
    const CVector3 before = m_WorldTarget;
    ComputeCameraPose(kPoseDt, &m_WorldPosition, &m_WorldTarget);
    m_WorldPosition.x = (m_WorldPosition.x + m_WorldTarget.x) - before.x;
    m_WorldPosition.y = (m_WorldPosition.y + m_WorldTarget.y) - before.y;
    m_WorldPosition.z = (m_WorldPosition.z + m_WorldTarget.z) - before.z;
    const float along = camera->GetClosestDistanceAlong(&m_WorldPosition, 1);
    CVector3 onPath;
    camera->GetPointAtDistance(along, &onPath, nullptr);
    m_WorldPosition.x = onPath.x;
    m_WorldPosition.z = onPath.z;
}

// The follow spring inlined in Update (+0x60 target, +0x64 current, +0x68 speed; +0x94 stiffness, +0x98 damping, +0x9c
// the top speed): one step from `start` (fmsubs / fmadds), the speed clamped to the top speed, the current to
// [0, 100000]; at rest (no speed and on the target, exactly) it sits on the target. With the target already reached and
// no speed nothing is stored. Returns the new current.
float CKCameraPassivePathTrack::StepFollowSpring(float dt, float start) {
    const float diff = m_unk60 - start;
    float force;
    if (diff == kZero) {  // beq (NaN: driven)
        if (m_unk68 == kZero) return start;
        force = m_unk68 * -m_unk98;
    } else {
        force = ppc::fmsubs(m_unk94, diff, m_unk98 * m_unk68);
    }
    const float speed = ppc::fmadds(force, dt, m_unk68);
    const float max = m_unk9C;
    float clamped = speed;
    if (speed <= -max) {  // cror lt|eq
        clamped = -max;
    } else if (speed >= max) {  // cror gt|eq
        clamped = max;
    }
    float next = ppc::fmadds(clamped, dt, start);
    if (next <= kZero) {
        next = kZero;
    } else if (next >= kFollowMax) {
        next = kFollowMax;
    }
    if (std::fabs(clamped) <= kZero && std::fabs(next - m_unk60) <= kZero) {
        m_unk68 = kZero;
        m_unk64 = m_unk60;
        return m_unk60;
    }
    m_unk68 = clamped;
    m_unk64 = next;
    return next;
}

// The camera moved along its path by the follow spring from `v` (the distance to cover, its sign `sign`) (Update's
// inlined far / near cases): the new distance, wrapped with bit 6, else clamped to the path (the spring stopped there).
// Returns the distance covered.
float CKCameraPassivePathTrack::FollowAlongPath(float dt, float v, float sign) {
    IKPath* camera = PathOf(m_pCameraPath);
    m_unk64 = v;
    const float next = StepFollowSpring(dt, v);
    const float moved = v - next;
    float d = ppc::fmadds(sign, moved, m_fCameraPathDist);
    m_fCameraPathDist = d;
    if (((m_ui16Flags >> 6) & 1u) != 0) {
        m_fCameraPathDist = WrapOnPath(camera, d);
    } else if (d < kZero) {
        m_fCameraPathDist = kZero;
        m_unk68 = kZero;
    } else if (d > camera->GetLength()) {  // bgt
        m_fCameraPathDist = camera->GetLength();
        m_unk68 = kZero;
    }
    camera->GetPointAtDistance(m_fCameraPathDist, &m_WorldPosition, nullptr);  // vt+0x54
    return moved;
}

// 0x0013fa18 CKCameraPassivePathTrack_Update_maybe: the attached fx; the four blends stepped (Math_ApproachWithAccelDecel:
// +0x118 the distance, +0xfc, +0xe0, +0xc4); the target placed as Activate does; the camera moved on its path by the
// mode: 3 towards the path point nearest the target (offset by the distance blend along the direction, bit 7) at the
// speed +0x7c; 4 the same point through the follow spring (the shorter way round with bit 6); others keep the camera
// between the near (+0x90, squared) and far (the distance blend) distances from the target with the follow spring (a
// moving spring runs on in between); then the height clamp, the target's move and the lateral lead (bit 5) as Activate.
void CKCameraPassivePathTrack::Update(float dt) {
    UpdateTrackBase();  // 0x00144398
    if (m_pCameraPath == nullptr) return;
    const float far = Math_ApproachWithAccelDecel(dt, &m_aBlend[3].m_accel);  // 0x00243a10
    Math_ApproachWithAccelDecel(dt, &m_aBlend[2].m_accel);
    Math_ApproachWithAccelDecel(dt, &m_aBlend[1].m_accel);
    const float lead = Math_ApproachWithAccelDecel(dt, &m_aBlend[0].m_accel);
    CKSrvCamera* service = Service();
    IKPath* camera = PathOf(m_pCameraPath);
    CVector3 point;
    if (m_pTargetPath != nullptr) {
        m_fTargetPathDist = PathOf(m_pTargetPath)->GetClosestDistanceAlong(&service->m_v3FocusPos, 1);  // vt+0x58
        PathOf(m_pTargetPath)->GetPointAtDistance(m_fTargetPathDist, &point, nullptr);                // vt+0x54
    } else {
        m_fTargetPathDist = 0.0f;  // stw 0
        point = service->m_v3FocusPos;
    }
    const float targetY = point.y + m_aBlend[1].m_current;
    m_WorldTarget.x = point.x;
    m_WorldTarget.z = point.z;
    m_WorldTarget.y = targetY;
    const uint32_t mode = m_ui16Flags & 7u;
    if (mode == 3 || mode == 4) {
        float goal = camera->GetClosestDistanceAlong(&m_WorldTarget, 1);
        if ((m_ui16Flags & 0x40u) == 0) {
            if (goal < kZero) {
                goal = kZero;
            } else if (goal > camera->GetLength()) {
                goal = camera->GetLength();
            }
        }
        if (far != kZero) goal = ((m_ui16Flags >> 7) & 1u) != 0 ? goal + far : goal - far;
        if (mode == 3) {
            if (((m_ui16Flags >> 6) & 1u) != 0) {
                float gap = m_fCameraPathDist - goal;
                // BUG(original)?: a negative gap becomes -current - goal (not goal - current).
                if (gap < kZero) gap = -m_fCameraPathDist - goal;
                if (!(camera->GetLength() * kHalf >= gap)) {  // bge (NaN: no wrap)
                    if (goal >= m_fCameraPathDist) {
                        m_fCameraPathDist = m_fCameraPathDist + camera->GetLength();
                    } else {
                        goal = goal + camera->GetLength();
                    }
                }
            }
            float d = m_fCameraPathDist;
            if (goal >= d) {  // bge
                if (!(goal <= d)) {  // ble: equal or NaN stays
                    d = ppc::fmadds(dt, m_fPathSpeed, d);
                    m_fCameraPathDist = d;
                    if (!(goal >= d)) {
                        d = goal;
                        m_fCameraPathDist = goal;
                    }
                }
            } else {
                d = d - dt * m_fPathSpeed;  // fmuls, fsubs
                m_fCameraPathDist = d;
                if (goal > d) {
                    d = goal;
                    m_fCameraPathDist = goal;
                }
            }
            if (((m_ui16Flags >> 6) & 1u) != 0) {
                d = WrapOnPath(camera, d);
                m_fCameraPathDist = d;
            }
            camera->GetPointAtDistance(d, &m_WorldPosition, nullptr);
            m_unk68 = 0.0f;  // stw 0
        } else if ((m_ui16Flags & 0x40u) == 0) {
            const float delta = goal - m_fCameraPathDist;
            int32_t way = 1;
            float sign = kOne;
            if (delta < kZero) {
                way = -1;
                sign = -kOne;
            }
            const float v = std::fabs(delta);
            m_unk64 = v;
            const float next = StepFollowSpring(dt, v);
            const float moved = v - next;
            const float d = ppc::fmadds(sign, moved, m_fCameraPathDist);
            m_fCameraPathDist = d;
            camera->GetPointAtDistance(d, &m_WorldPosition, nullptr);
            if (way * m_i32Direction < 0 || moved <= kFollowRest) m_unk68 = 0.0f;  // blt / cror lt|eq
            m_i32Direction = way;
        } else {
            // The shorter way round the looped path.
            const float length = camera->GetLength();
            const float cur = m_fCameraPathDist;
            float forward;
            float backward;
            if (!(goal > cur)) {  // ble
                backward = cur - goal;
                forward = goal + (length - cur);
            } else {
                forward = goal - cur;
                backward = (length + cur) - goal;
            }
            float v;
            int32_t way;
            float sign;
            if (!(forward > backward)) {  // ble (NaN: forward)
                v = forward;
                way = 1;
                sign = kOne;
            } else {
                v = backward;
                way = -1;
                sign = -kOne;
            }
            m_unk64 = v;
            const float next = StepFollowSpring(dt, v);
            const float moved = v - next;
            float d = ppc::fmadds(sign, moved, m_fCameraPathDist);
            m_fCameraPathDist = d;
            while (d < kZero) d = d + length;
            while (length <= d) d = d - length;
            m_fCameraPathDist = d;
            camera->GetPointAtDistance(d, &m_WorldPosition, nullptr);
            if (way * m_i32Direction < 0 || moved <= kFollowRest) m_unk68 = 0.0f;
            m_i32Direction = way;
        }
    } else {
        // Keep the distance: d = target - camera (flat without bit 3).
        const float dx = m_WorldTarget.x - m_WorldPosition.x;
        const float dy = targetY - m_WorldPosition.y;
        const float dz = m_WorldTarget.z - m_WorldPosition.z;
        float d2;
        bool tooFar;
        if (((m_ui16Flags >> 3) & 1u) == 1) {
            d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            tooFar = !(far * far >= d2);  // bge (NaN: not far)
        } else {
            d2 = ppc::fmadds(dx, dx, dz * dz);
            tooFar = far * far < d2;  // blt
        }
        if (tooFar) {
            CVector3 at;
            CVector3 dir;
            camera->GetPointAtDistance(m_fCameraPathDist, &at, &dir);
            const float share = kOne - far / std::sqrt(d2);  // 0x10690
            const float proj = ppc::fmadds(dz * share, dir.z, ppc::fmadds(dx * share, dir.x, (dy * share) * dir.y));
            const int32_t way = proj < kZero ? -1 : 1;
            const float moved = FollowAlongPath(dt, std::fabs(proj), proj < kZero ? -kOne : kOne);
            if (way * m_i32Direction < 0 || moved <= kFollowRest) m_unk68 = 0.0f;  // blt / cror lt|eq
            m_i32Direction = way;
        } else if (m_unk90 > d2 && d2 > kZero) {  // bgt, then ble (NaN: holding)
            CVector3 at;
            CVector3 dir;
            camera->GetPointAtDistance(m_fCameraPathDist, &at, &dir);
            const float share = kOne - std::sqrt(m_unk90 / d2);
            const float proj = ppc::fmadds(dz * share, dir.z, ppc::fmadds(dx * share, dir.x, (dy * share) * dir.y));
            const int32_t way = proj < kZero ? -1 : 1;
            const float moved = FollowAlongPath(dt, std::fabs(proj), proj < kZero ? -kOne : kOne);
            if (!(way * m_i32Direction > 0) || moved <= kFollowRest) m_unk68 = 0.0f;  // bgt / cror lt|eq
            m_i32Direction = way;
        } else if (m_unk68 != kZero) {  // bne (NaN: moving)
            // A moving spring runs on from its current, the way the near test would push it.
            CVector3 at;
            CVector3 dir;
            camera->GetPointAtDistance(m_fCameraPathDist, &at, &dir);
            const float share = kOne - std::sqrt(m_unk90 / d2);
            const float start = m_unk64;
            const float next = StepFollowSpring(dt, start);
            const float moved = start - next;
            const float proj = ppc::fmadds(dz * share, dir.z, ppc::fmadds(dx * share, dir.x, (dy * share) * dir.y));
            const float sign = proj < kZero ? -kOne : kOne;
            float d = ppc::fmadds(sign, moved, m_fCameraPathDist);
            m_fCameraPathDist = d;
            bool stopped = false;
            if (((m_ui16Flags >> 6) & 1u) != 0) {
                m_fCameraPathDist = WrapOnPath(camera, d);
            } else if (d < kZero) {
                m_fCameraPathDist = kZero;
                m_unk68 = kZero;
                stopped = true;
            } else if (d > camera->GetLength()) {
                m_fCameraPathDist = camera->GetLength();
                m_unk68 = kZero;
                stopped = true;
            }
            if (!stopped && std::fabs(m_unk68) < kSlowSpeed) m_unk68 = kZero;  // bge keeps (NaN kept)
            camera->GetPointAtDistance(m_fCameraPathDist, &m_WorldPosition, nullptr);
            if (moved <= kFollowRest) m_unk68 = kZero;  // cror lt|eq
        }
    }
    // The height clamp, the target's move (leading by the lead blend's value) and the lateral lead, as Activate.
    const float offset = m_unkA0;
    const float floor = m_aBlend[2].m_current + service->m_v3FocusPos.y;
    float y = m_WorldPosition.y;
    if (offset < kZero) {
        const float low = offset + y;
        if (low >= floor) {
            y = low;
        } else if (!(y <= floor)) {
            y = floor;
        }
    } else if (!(y >= floor)) {
        const float low = y + offset;
        y = floor >= low ? low : floor;
    }
    m_WorldPosition.y = y;
    if (m_pTargetPath != nullptr) {
        m_fTargetPathDist = m_fTargetPathDist + m_aBlend[0].m_current;
        PathOf(m_pTargetPath)->GetPointAtDistance(m_fTargetPathDist, &m_WorldTarget, nullptr);
        m_WorldTarget.y = m_WorldTarget.y + m_aBlend[1].m_current;
    } else if (service->m_ui32NbStacked != 0) {
        const RwV3d& at = static_cast<CSGMovable*>(service->m_aStack[0].m_pTarget)->m_pRwFrame->ltm.at;  // frame +0x70
        m_WorldTarget.z = ppc::fmadds(lead, at.z, m_WorldTarget.z);
        m_WorldTarget.x = ppc::fmadds(lead, at.x, m_WorldTarget.x);
        m_WorldTarget.y = ppc::fmadds(lead, at.y, m_WorldTarget.y);
    }
    // BUG(original): no target path and no stacked target: the null path's frame is read; nothing here.
    if (((m_ui16Flags >> 5) & 1u) == 0) return;
    const CVector3 before = m_WorldTarget;
    ComputeCameraPose(dt, &m_WorldPosition, &m_WorldTarget);
    m_WorldPosition.x = (m_WorldPosition.x + m_WorldTarget.x) - before.x;
    m_WorldPosition.y = (m_WorldPosition.y + m_WorldTarget.y) - before.y;
    m_WorldPosition.z = (m_WorldPosition.z + m_WorldTarget.z) - before.z;
    const float along = camera->GetClosestDistanceAlong(&m_WorldPosition, 1);
    CVector3 onPath;
    camera->GetPointAtDistance(along, &onPath, nullptr);
    m_WorldPosition.x = onPath.x;
    m_WorldPosition.z = onPath.z;
}
