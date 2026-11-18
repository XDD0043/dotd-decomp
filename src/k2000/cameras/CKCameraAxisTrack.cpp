// CKCameraAxisTrack.cpp - reconstructed original translation unit 0x13c700-0x13d8c8 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCameraAxisTrack  key 0x1c7  category Camera  size 0x98  vtable 0xb1a1f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13c700  CKCameraAxisTrack_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKCameraAxisTrack))
//   [x] 0x13c750  CKCameraAxisTrack_vf54  (CKCameraAxisTrack::Pause (empty), CKCameraAxisTrack.h)
//   [x] 0x13c758  CKCameraAxisTrack_vf5C  (CKCameraAxisTrack::Resume (empty), CKCameraAxisTrack.h)
//   [ ] 0x13c760  RegisterCKCameraAxisTrackClass
//   [ ] 0x13c7d8  _GLOBAL__I_13c7d8
//   [x] 0x13c7e8  CKCameraAxisTrack_Deactivate_maybe  (CKCameraAxisTrack::Stop)
//   [x] 0x13c810  CKCameraAxisTrack_RecursiveRegistration
//   [x] 0x13c8c0  CKCameraAxisTrack_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x13c8e8  CKCameraAxisTrack_DeleteArray  (DOTD_DECLARE_FACTORIES(CKCameraAxisTrack))
//   [x] 0x13c988  CKCameraAxisTrack_Create  (CKCameraAxisTrack())
//   [x] 0x13c9e0  CKCameraAxisTrack_CreateArray  (DOTD_DECLARE_FACTORIES(CKCameraAxisTrack))
//   [x] 0x13ca90  CKCameraAxisTrack_Load
//   [ ] 0x13cda0  CKCameraAxisTrack_Save
//   [x] 0x13d058  CKCameraAxisTrack_Update_maybe  (CKCameraAxisTrack::Update)
//   [x] 0x13d4b8  CKCameraAxisTrack_Activate_maybe  (CKCameraAxisTrack::Start)
//
//   [ ] 0x9a7528  CKCameraAxisTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7550  CKCameraAxisTrack_GetClassType  [inline]
//   [ ] 0x9a7558  CKCameraAxisTrack_GetClassID  [inline]
//   [ ] 0x9a7560  CKCameraAxisTrack_vfB4  [inline]
//   [ ] 0x9a7568  CKCameraAxisTrack_vf80  [inline]
//   [ ] 0x9a7570  CKCameraAxisTrack_Destructor  [inline]
//   [ ] 0x9a75a0  CKCameraAxisTrack_DeletingDestructor  [inline]
#include "k2000/cameras/CKCameraAxisTrack.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CSGMovable.h"

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

// The pose both slots end with: the position on the yaw at the distance from the target (fused), the target raised by
// m_fTargetHighOffset and the position by m_fCameraHighOffset (stores: x, z, target y, y).
void PlaceOnYaw(CKCameraAxisTrack* track, float yaw) {
    const float tx = track->m_WorldTarget.x;
    const float distance = track->m_fCameraTargetDistance;
    track->m_WorldPosition.x = ppc::fmadds(SinOf(yaw), distance, tx);
    const float tz = track->m_WorldTarget.z;
    const float c = CosOf(track->m_yaw.m_current);
    const float ty = track->m_WorldTarget.y;
    const float z = ppc::fmadds(c, distance, tz);
    const float targetY = ty + track->m_fTargetHighOffset;
    const float positionY = ty + track->m_fCameraHighOffset;
    track->m_WorldPosition.z = z;
    track->m_WorldTarget.y = targetY;
    track->m_WorldPosition.y = positionY;
}
}  // namespace

void CKCameraAxisTrack::ComputeAxisPoint(CVector3* point) {
    const CVector3& focus = SrvCamera()->m_v3FocusPos;  // +0x484
    m_WorldTarget.x = focus.x;
    m_WorldTarget.y = focus.y;
    m_WorldTarget.z = focus.z;
    switch (m_eAxisType) {
    case 0: {  // the node's LTM position (its frame +0x80)
        const RwV3d& pos = FrameLtm(static_cast<CSGMovable*>(m_pAxis)->m_pRwFrame)->pos;
        point->x = pos.x;
        point->y = pos.y;
        point->z = pos.z;
        break;
    }
    case 1:
        // The original reads the vector at +0x84 of the axis object itself (axis + 4 + 0x80, where type 0 loads the frame
        // pointer at +4): an object class no level file shows; not mapped.
        DOTD_STUB_ONCE("CKCameraAxisTrack axis type 1: the vector at +0x84 of an object of unknown class (no level holds the camera)");
        break;
    case 2: {  // the path point nearest the target: IKPath vt+0x58 (squared 1), then vt+0x54 (no direction)
        IKPath* path = static_cast<IKPath*>(m_pAxis);
        const float distance = path->GetClosestDistanceAlong(&m_WorldTarget, 1);
        path->GetPointAtDistance(distance, point, nullptr);
        break;
    }
    default:
        break;  // BUG(original): the point stays the uninitialised stack (here the caller's zero vector)
    }
}

// 0x0013c810 CKCameraAxisTrack_RecursiveRegistration
void CKCameraAxisTrack::RecursiveRegistration(int32_t type) {
    IKCamera::RecursiveRegistration(type);  // 0x00144108
    if (m_eAxisType != 1 && m_eAxisType != 2) return;
    if (m_pAxis != nullptr) m_pAxis->RecursiveRegistration(type);  // vt+0x24
}

// 0x0013ca90 CKCameraAxisTrack_Load: the camera's common part, then (level files only) the four offsets, the axis
// reference, its type and the yaw approach's top speed, acceleration and deceleration.
int32_t CKCameraAxisTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);  // 0x00144580
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fTargetHighOffset);
    ReadF32LE(file, &m_fCameraHighOffset);
    ReadF32LE(file, &m_fCameraTargetDistance);
    ReadF32LE(file, &m_fHeightAboveGround);
    IKFile_ReadRef(file, &m_pAxis);
    ReadU32LE(file, &m_eAxisType);
    ReadF32LE(file, &m_fYawMaxSpeed);
    ReadF32LE(file, &m_fYawAccel);
    ReadF32LE(file, &m_fYawDecel);
    return 1;
}

// 0x0013d4b8 CKCameraAxisTrack_Activate_maybe: the attached fx started; with an axis, the target and the axis point, the
// yaw approach cleared (7 floats, TOC -0x3e40) and its current / target yaw that of target - axis point (Vec3_GetYawAngleFromZ;
// BUG(original): 0 when that vector's x is 0 and its z is not), the pose, then the approach's speed 0 and its parameters.
void CKCameraAxisTrack::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8
    if (m_pAxis == nullptr) return;
    CVector3 point = {0.0f, 0.0f, 0.0f};
    ComputeAxisPoint(&point);
    CVector3 v;
    v.x = m_WorldTarget.x - point.x;
    v.y = m_WorldTarget.y - point.y;
    v.z = m_WorldTarget.z - point.z;
    const float zero = 0.0f;
    m_yaw.m_accel = zero;
    m_yaw.m_decel = zero;
    m_yaw.m_maxSpeed = zero;
    m_yaw.m_current = zero;
    m_yaw.m_speed = zero;
    m_yaw.m_target = zero;
    m_yaw.m_speedBonus = zero;
    float yaw = zero;
    if (v.x != zero || v.z == zero) {
        yaw = Vec3_GetYawAngleFromZ(&v);  // 0x00244528
        m_yaw.m_current = yaw;
    } else {
        m_yaw.m_current = zero;
    }
    m_yaw.m_target = yaw;
    PlaceOnYaw(this, yaw);
    const float current = m_yaw.m_current;
    m_yaw.m_speed = 0.0f;  // stw 0
    m_yaw.m_target = current;
    m_yaw.m_maxSpeed = m_fYawMaxSpeed;
    m_yaw.m_accel = m_fYawAccel;
    m_yaw.m_decel = m_fYawDecel;
}

// 0x0013c7e8 CKCameraAxisTrack_Deactivate_maybe
void CKCameraAxisTrack::Stop() { StopAttachedFx(); }  // 0x00144238

// 0x0013d058 CKCameraAxisTrack_Update_maybe: IKCamera_UpdateTrackBase_maybe; with an axis, the target and the axis
// point, the yaw target that of target - axis point unless its x and z are both 0, one step of the yaw approach
// (Math_ApproachAngleWithAccelDecel 0x243c88), the pose, then the view obstructions (vt+0x74, the focus) and the
// collision (vt+0x78) on the position.
void CKCameraAxisTrack::Update(float frameTime) {
    UpdateTrackBase();  // 0x00144398
    if (m_pAxis == nullptr) return;
    CVector3 point = {0.0f, 0.0f, 0.0f};
    ComputeAxisPoint(&point);
    CVector3 v;
    v.x = m_WorldTarget.x - point.x;
    v.y = m_WorldTarget.y - point.y;
    v.z = m_WorldTarget.z - point.z;
    if (v.x != 0.0f || v.z != 0.0f) m_yaw.m_target = Vec3_GetYawAngleFromZ(&v);
    Math_ApproachAngleWithAccelDecel(frameTime, m_yaw.Data());
    PlaceOnYaw(this, m_yaw.m_current);
    ResolveViewObstructions(frameTime, &SrvCamera()->m_v3FocusPos, &m_WorldPosition);  // vt+0x74
    ResolveCameraCollision(&m_WorldTarget, &m_WorldPosition);                          // vt+0x78
}
