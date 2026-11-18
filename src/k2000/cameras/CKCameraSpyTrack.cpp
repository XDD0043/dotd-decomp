// CKCameraSpyTrack.cpp - reconstructed original translation unit 0x1419e0-0x143b58 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCameraSpyTrack  key 0x207  category Camera  size 0x108  vtable 0xb1a440
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1419e0  CKCameraSpyTrack_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKCameraSpyTrack))
//   [x] 0x141a30  CKCameraSpyTrack_vf54  (CKCameraSpyTrack::Pause (empty), CKCameraSpyTrack.h)
//   [x] 0x141a38  CKCameraSpyTrack_vf5C  (CKCameraSpyTrack::Resume (empty), CKCameraSpyTrack.h)
//   [ ] 0x141a40  RegisterCKCameraSpyTrackClass
//   [ ] 0x141ab8  _GLOBAL__I_141ab8
//   [x] 0x141ac8  CKCameraSpyTrack_Deactivate_maybe  (CKCameraSpyTrack::Stop)
//   [x] 0x141af0  CKCameraSpyTrack_RecursiveRegistration  (RecursiveRegistration: IKCamera's (0x144108), then 1: inherited)
//   [x] 0x141b18  CKCameraSpyTrack_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x141b40  CKCameraSpyTrack_DeleteArray  (DOTD_DECLARE_FACTORIES(CKCameraSpyTrack))
//   [x] 0x141be8  CKCameraSpyTrack_Create  (CKCameraSpyTrack())
//   [x] 0x141c70  CKCameraSpyTrack_Load
//   [x] 0x141d70  CKCameraSpyTrack_CreateArray  (DOTD_DECLARE_FACTORIES(CKCameraSpyTrack))
//   [ ] 0x141e70  CKCameraSpyTrack_Save
//   [x] 0x142080  CKCameraSpyTrack_Update_maybe  (CKCameraSpyTrack::Update)
//   [x] 0x143540  CKCameraSpyTrack_Activate_maybe  (CKCameraSpyTrack::Start)
//
//   [ ] 0x9a77f0  CKCameraSpyTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7818  CKCameraSpyTrack_GetClassType  [inline]
//   [ ] 0x9a7820  CKCameraSpyTrack_GetClassID  [inline]
//   [ ] 0x9a7828  CKCameraSpyTrack_Destructor  [inline]
//   [ ] 0x9a7858  CKCameraSpyTrack_DeletingDestructor  [inline]
#include "k2000/cameras/CKCameraSpyTrack.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CSGLeaf.h"

namespace {
CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }  // engine +0x70

bool SignBit(float angle) {
    uint32_t bits;
    std::memcpy(&bits, &angle, 4);
    return (bits >> 31) != 0;
}
// The game's inlined sine / cosine (the library's 0x9a1390 / 0x9a11d8 for a negative angle).
float SinOf(float angle) { return SignBit(angle) ? -crt::LibSinf(-angle) : crt::InlineSinf(angle); }
float CosOf(float angle) { return SignBit(angle) ? crt::LibCosf(-angle) : crt::InlineCosf(angle); }

// The first stack entry's node position (its stored LTM's, frame +0x80); the original reads through a null node when
// the stack is empty.
const RwV3d& NodePosition(CKSrvCamera* service) {
    CSGLeaf* node = service->m_ui32NbStacked != 0 ? static_cast<CSGLeaf*>(service->m_aStack[0].m_pTarget) : nullptr;
    return FrameLtm(node->m_pRwFrame)->pos;
}

float Length(float dx, float dy, float dz) {
    return std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
}
}  // namespace

// TOC -0x3cc0 (pi/180 0x3c8efa34).
void CKCameraSpyTrack::RaiseAndTurn(float /*x*/, float y, float z, float* outY, float* outZ) const {
    const float raised = y + m_sfCurrentDistance.m_fCurrentValue;
    const float angle = m_fXAngle * 0.01745329052209854f;
    const float turnedY = ppc::fmadds(CosOf(angle), raised, SinOf(angle) * z);
    *outY = turnedY;
    *outZ = ppc::fmsubs(CosOf(angle), z, SinOf(angle) * turnedY);
}

// One glide step (Update inlines it for the target, 0x00143298, and the position, 0x0014291c): nothing once the
// current vector is back on `old` (ble); inside `slowDistance` of it (blt) the acceleration becomes -distance * speed /
// slowDistance; unless already on the targeted vector the speed integrates the acceleration (fmadds), clamped to the
// targeted speed in the acceleration's direction (bgt / blt; a NaN does not clamp), then the vector moves dt * speed
// towards the target (normalised direction, fused), landing on it when closer (the bge: a NaN length moves). Returns
// whether the caller copies the current vector (all but the first exit).
static bool Glide(float dt, CKCameraSpyTrack::CSmoothedCVector3AcceleratedLinear* glide, const CVector3* old,
                  float slowDistance, float speed) {
    CVector3& current = glide->m_v3CurrentVector;
    const float distance = Length(current.x - old->x, current.y - old->y, current.z - old->z);
    if (!(distance > 0.0f)) return false;
    if (distance < slowDistance) glide->m_fAcceleration = (-distance * speed) / slowDistance;
    const CVector3& target = glide->m_v3TargetedVector;
    if (current.x == target.x && current.y == target.y && current.z == target.z) return true;
    const float accel = glide->m_fAcceleration;
    float s = ppc::fmadds(dt, accel, glide->m_fCurrentSpeed);
    glide->m_fCurrentSpeed = s;
    if (accel > 0.0f) {
        if (s > glide->m_fTargetedSpeed) {
            s = glide->m_fTargetedSpeed;
            glide->m_fCurrentSpeed = s;
        }
    } else if (accel < 0.0f) {
        if (s < glide->m_fTargetedSpeed) {
            s = glide->m_fTargetedSpeed;
            glide->m_fCurrentSpeed = s;
        }
    }
    const float step = dt * s;
    float dy = target.y - current.y;
    float dx = target.x - current.x;
    float dz = target.z - current.z;
    float length = Length(dx, dy, dz);
    if (!(length == 0.0f)) {
        const float inverse = 1.0f / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    } else {
        length = 0.0f;
    }
    if (!(length < step)) {
        const float x = ppc::fmadds(dx, step, current.x);
        const float y = ppc::fmadds(dy, step, current.y);
        const float z = ppc::fmadds(step, dz, current.z);
        current.x = x;
        current.y = y;
        current.z = z;
        return true;
    }
    const float tz = target.z;
    const float tx = target.x;
    const float ty = target.y;
    current.z = tz;
    current.x = tx;
    current.y = ty;
    return true;
}

// 0x00141c70 CKCameraSpyTrack_Load: the camera's common part, then (level files only) six floats (one 0x18 read, each
// word swapped).
int32_t CKCameraSpyTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);  // 0x00144580
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_fMaxCameraTargetDistance), 6);
    return 1;
}

// 0x00143540 CKCameraSpyTrack_Activate_maybe: the attached fx started, the distance the max (current and target, speed
// 0), the target and the position the service's real view (+0x5a4 / +0x598), the position then the target raised and
// turned, the old points the node and the position, the two glides aimed at the target / position with their speeds.
void CKCameraSpyTrack::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8
    CKSrvCamera* service = SrvCamera();
    m_sfCurrentDistance.m_fCurrentValue = m_fMaxCameraTargetDistance;
    m_sfCurrentDistance.m_fCurrentSpeed = 0.0f;  // stw 0
    m_sfCurrentDistance.m_fTargetedValue = m_fMaxCameraTargetDistance;
    m_WorldTarget = service->m_v3RealTarget;
    m_WorldPosition = service->m_v3RealPos;
    const CVector3 target = m_WorldTarget;
    m_WorldPosition.y = target.y;
    m_WorldPosition.x = target.x;
    m_WorldPosition.z = target.z;
    float y;
    float z;
    RaiseAndTurn(m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z, &y, &z);
    m_WorldPosition.y = m_WorldPosition.y + m_sfCurrentDistance.m_fCurrentValue;
    m_WorldPosition.y = y;
    m_WorldPosition.z = z;
    const RwV3d& node = NodePosition(service);
    m_v3OldTargetPosition.x = node.x;
    m_v3OldTargetPosition.z = node.z;
    m_v3OldTargetPosition.y = node.y;
    m_v3OldCameraPosition.x = m_WorldPosition.x;
    m_v3OldCameraPosition.z = m_WorldPosition.z;
    m_v3OldCameraPosition.y = m_WorldPosition.y;
    m_sv3TargetPosition.m_v3CurrentVector = m_WorldTarget;
    m_sv3TargetPosition.m_fCurrentSpeed = m_fAxisSpeed;
    m_sv3TargetPosition.m_v3TargetedVector = m_WorldTarget;
    m_sv3CameraPosition.m_v3CurrentVector = m_WorldPosition;
    m_sv3CameraPosition.m_fCurrentSpeed = m_fMoveSpeed;
    m_sv3CameraPosition.m_v3TargetedVector = m_WorldPosition;
}

// 0x00141ac8 CKCameraSpyTrack_Deactivate_maybe
void CKCameraSpyTrack::Stop() { StopAttachedFx(); }  // 0x00144238

// 0x00142080 CKCameraSpyTrack_Update_maybe. TOC -0x3cbc (255), -0x3cb4 (100), -0x3d38 (0), -0x3ce8 (1), the null vector
// 0x00c50d64.
void CKCameraSpyTrack::Update(float frameTime) {
    const float dt = frameTime;
    UpdateTrackBase();  // 0x00144398
    CKSrvCamera* service = SrvCamera();
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // engine +0x8c
    m_WorldPosition.x = service->m_v3RealPos.x;
    m_WorldPosition.y = service->m_v3RealPos.y;
    m_WorldPosition.z = service->m_v3RealPos.z;
    const bool zoomIn = manager->GetDirectionActionState(5) != 0;  // vt+0x188
    if (zoomIn || manager->GetDirectionActionState(6) != 0) {
        // The zoom: the distance approaches the min (5) / max (6) at the move speed; both glides' speeds 0.
        m_sv3CameraPosition.m_fCurrentSpeed = 0.0f;  // stw 0
        m_sv3TargetPosition.m_fCurrentSpeed = 0.0f;
        m_sfCurrentDistance.m_fCurrentSpeed = m_fMoveSpeed;
        m_sfCurrentDistance.m_fTargetedValue = zoomIn ? m_fMinCameraTargetDistance : m_fMaxCameraTargetDistance;
        FloatApproach_Step(dt, &m_sfCurrentDistance.m_fTargetedValue);  // 0x002436e8
        const CVector3 target = m_WorldTarget;
        m_WorldPosition.y = target.y;
        m_WorldPosition.z = target.z;
        m_WorldPosition.x = target.x;
        float y;
        float z;
        RaiseAndTurn(m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z, &y, &z);
        m_WorldPosition.y = m_WorldPosition.y + m_sfCurrentDistance.m_fCurrentValue;
        m_WorldPosition.y = y;
        m_WorldPosition.z = z;
        return;
    }
    if ((service->m_baTemporaryFlags & 0x200000u) != 0 &&
        (manager->GetDirectionActionState(0) != 0 || manager->GetDirectionActionState(1) != 0 ||
         manager->GetDirectionActionState(3) != 0 || manager->GetDirectionActionState(2) != 0)) {
        // The stick moves the camera and its target together (the move speed times the direction's state / 255, dt).
        SrvCamera()->m_baTemporaryFlags = (SrvCamera()->m_baTemporaryFlags & 0xffefffffu) | 0x100000u;
        m_sv3CameraPosition.m_fCurrentSpeed = 0.0f;
        m_sv3TargetPosition.m_fCurrentSpeed = 0.0f;
        const auto moveBy = [&](uint8_t direction) {
            const float speed = m_fMoveSpeed;
            const uint8_t state = manager->GetDirectionActionState(direction);
            return dt * ((speed * static_cast<float>(static_cast<double>(state))) / 255.0f);
        };
        if (manager->GetDirectionActionState(0) != 0) {
            const float d = moveBy(0);
            const float z = m_WorldPosition.z - d;
            const float tz = m_WorldTarget.z - d;
            m_WorldPosition.z = z;
            m_WorldTarget.z = tz;
        } else if (manager->GetDirectionActionState(1) != 0) {
            const float d = moveBy(1);
            const float z = d + m_WorldPosition.z;
            const float tz = m_WorldTarget.z + d;
            m_WorldPosition.z = z;
            m_WorldTarget.z = tz;
        }
        if (manager->GetDirectionActionState(3) != 0) {
            const float d = moveBy(3);
            const float x = d + m_WorldPosition.x;
            const float tx = m_WorldTarget.x + d;
            m_WorldPosition.x = x;
            m_WorldTarget.x = tx;
        } else if (manager->GetDirectionActionState(2) != 0) {
            const float d = moveBy(2);
            const float x = m_WorldPosition.x - d;
            const float tx = m_WorldTarget.x - d;
            m_WorldPosition.x = x;
            m_WorldTarget.x = tx;
        }
        return;
    }
    if (manager->GetDirectionActionState(4) != 0) {
        m_sv3TargetPosition.m_fCurrentSpeed = m_fAxisSpeed;
        m_sv3CameraPosition.m_fCurrentSpeed = m_fMoveSpeed;
        return;
    }
    {
        const RwV3d& node = NodePosition(service);
        if (!(m_v3OldTargetPosition.x == node.x && m_v3OldTargetPosition.y == node.y &&
              m_v3OldTargetPosition.z == node.z)) {
            // The node moved: re-aim both glides (the direction to the node kept flat in +0xfc, normalised).
            static const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
            m_v3CameraToTargetDir = kNull;
            const RwV3d& n = NodePosition(service);
            const float dx = n.x - m_WorldTarget.x;
            const float dy = n.y - m_WorldTarget.y;
            const float dz = n.z - m_WorldTarget.z;
            m_v3CameraToTargetDir.x = dx;
            m_v3CameraToTargetDir.y = dy;
            m_v3CameraToTargetDir.z = dz;
            m_v3CameraToTargetDir.y = 0.0f;  // stw 0
            if (!(kNull.x == dx && m_v3CameraToTargetDir.y == kNull.y && dz == kNull.z)) {
                const float length = Length(dx, m_v3CameraToTargetDir.y, m_v3CameraToTargetDir.z);
                if (!(length == 0.0f)) {
                    const float inverse = 1.0f / length;
                    const float z = inverse * m_v3CameraToTargetDir.z;
                    const float x = inverse * m_v3CameraToTargetDir.x;
                    const float y = inverse * m_v3CameraToTargetDir.y;
                    m_v3CameraToTargetDir.z = z;
                    m_v3CameraToTargetDir.x = x;
                    m_v3CameraToTargetDir.y = y;
                }
            }
            m_sv3TargetPosition.m_v3CurrentVector.x = m_WorldTarget.x;
            m_sv3TargetPosition.m_v3CurrentVector.z = m_WorldTarget.z;
            m_sv3TargetPosition.m_v3CurrentVector.y = m_WorldTarget.y;
            m_sv3TargetPosition.m_fCurrentSpeed = m_fAxisSpeed;
            const RwV3d& n2 = NodePosition(service);
            m_sv3TargetPosition.m_v3TargetedVector.x = n2.x;
            m_sv3TargetPosition.m_v3TargetedVector.y = n2.y;
            m_sv3TargetPosition.m_v3TargetedVector.z = n2.z;
            m_sv3TargetPosition.m_fTargetedSpeed = 0.0f;  // stw 0
            m_sv3TargetPosition.m_fAcceleration = 0.0f;
            m_csfAxisSpeed.m_fCurrentValue = m_fAxisSpeed;
            m_csfAxisSpeed.m_fTargetedValue = 0.0f;
            m_csfAxisSpeed.m_fCurrentSpeed = 1.0f;
            const RwV3d& n3 = NodePosition(service);
            const float nz = n3.z;
            const float nx = n3.x;
            float ny;
            float pz;
            RaiseAndTurn(nx, n3.y, nz, &ny, &pz);
            m_sv3CameraPosition.m_v3CurrentVector.x = m_WorldPosition.x;
            m_sv3CameraPosition.m_v3CurrentVector.z = m_WorldPosition.z;
            m_sv3CameraPosition.m_v3CurrentVector.y = m_WorldPosition.y;
            m_sv3CameraPosition.m_fCurrentSpeed = m_fMoveSpeed;
            m_sv3CameraPosition.m_fAcceleration = 0.0f;
            m_sv3CameraPosition.m_v3TargetedVector.x = nx;
            m_sv3CameraPosition.m_v3TargetedVector.y = ny;
            m_sv3CameraPosition.m_fTargetedSpeed = 0.0f;
            m_sv3CameraPosition.m_v3TargetedVector.z = pz;
            const float percent = m_fSlowDistance;
            const RwV3d& n4 = NodePosition(service);
            const float targetDistance = Length(m_WorldTarget.x - n4.x, m_WorldTarget.y - n4.y, m_WorldTarget.z - n4.z);
            m_fTargetToTargetDistance = (percent * targetDistance) / 100.0f;
            const float positionDistance =
                Length(m_WorldPosition.x - nx, m_WorldPosition.y - ny, m_WorldPosition.z - pz);
            m_fPositionToPositionDistance = (m_fSlowDistance * positionDistance) / 100.0f;
            const RwV3d& n5 = NodePosition(service);
            m_v3OldTargetPosition.x = n5.x;
            m_v3OldTargetPosition.y = n5.y;
            m_v3OldTargetPosition.z = n5.z;
            m_v3OldCameraPosition.x = nx;
            m_v3OldCameraPosition.z = pz;
            m_v3OldCameraPosition.y = ny;
        }
    }
    // The glides: the target (while it has a speed), then the position.
    if (m_sv3TargetPosition.m_fCurrentSpeed != 0.0f) {
        if (Glide(dt, &m_sv3TargetPosition, &m_v3OldTargetPosition, m_fTargetToTargetDistance, m_fAxisSpeed)) {
            const CVector3 current = m_sv3TargetPosition.m_v3CurrentVector;
            m_WorldTarget.x = current.x;
            m_WorldTarget.z = current.z;
            m_WorldTarget.y = current.y;
        }
    }
    if (m_sv3CameraPosition.m_fCurrentSpeed == 0.0f) return;
    if (Glide(dt, &m_sv3CameraPosition, &m_v3OldCameraPosition, m_fPositionToPositionDistance, m_fMoveSpeed)) {
        const CVector3 current = m_sv3CameraPosition.m_v3CurrentVector;
        m_WorldPosition.z = current.z;
        m_WorldPosition.x = current.x;
        m_WorldPosition.y = current.y;
    }
}
