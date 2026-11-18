// CKCameraRigidTrack.cpp - reconstructed original translation unit 0x13a330-0x13add0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCameraRigidTrack  key 0x87  category Camera  size 0x6c  vtable 0xb19fb8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13a330  CKCameraRigidTrack_Delete
//   [x] 0x13a380  CKCameraRigidTrack_vf54  (CKCameraRigidTrack::Pause (empty), CKCameraRigidTrack.h)
//   [x] 0x13a388  CKCameraRigidTrack_vf5C  (CKCameraRigidTrack::Resume (empty), CKCameraRigidTrack.h)
//   [ ] 0x13a390  RegisterCKCameraRigidTrackClass
//   [ ] 0x13a408  _GLOBAL__I_13a408
//   [x] 0x13a418  CKCameraRigidTrack_RecursiveRegistration  (RecursiveRegistration: IKCamera's (0x144108), then 1: inherited)
//   [x] 0x13a440  CKCameraRigidTrack_Deactivate_maybe  (CKCameraRigidTrack::Stop)
//   [x] 0x13a468  CKCameraRigidTrack_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x13a490  CKCameraRigidTrack_DeleteArray
//   [x] 0x13a530  CKCameraRigidTrack_Create
//   [x] 0x13a588  CKCameraRigidTrack_Activate_maybe  (CKCameraRigidTrack::Start)
//   [x] 0x13a778  CKCameraRigidTrack_CreateArray
//   [x] 0x13a828  CKCameraRigidTrack_Load
//   [x] 0x13a990  CKCameraRigidTrack_Update_maybe  (CKCameraRigidTrack::Update)
//   [ ] 0x13ac18  CKCameraRigidTrack_Save
//
//   [ ] 0x9a71f8  CKCameraRigidTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7220  CKCameraRigidTrack_GetClassType  [inline]
//   [ ] 0x9a7228  CKCameraRigidTrack_GetClassID  [inline]
//   [ ] 0x9a7230  CKCameraRigidTrack_vfB4  [inline]
//   [ ] 0x9a7238  CKCameraRigidTrack_vf80  [inline]
//   [ ] 0x9a7240  CKCameraRigidTrack_DeletingDestructor  [inline]
//   [ ] 0x9a7288  CKCameraRigidTrack_Destructor  [inline]
#include "k2000/cameras/CKCameraRigidTrack.h"

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"

#include <cmath>

namespace {
CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }

// The pose shared by Activate and Update (P21) from `focus` (x, y, z read in the original's order z, y, x): mode
// (m_Flags bits 18-19) 0: with a target on the service's stack, the target is the focus raised by m_unk64 and the
// position the offset in the frame of the target node's heading (its stored LTM's at, flattened: (-at.x, at.z)
// normalised, TOC 0.0 / 1.0); mode 1: the target as in mode 0, the position the focus plus the offset; other modes
// nothing.
void PlaceRigid(CKCameraRigidTrack* track, float fx, float fy, float fz) {
    const uint32_t mode = (track->m_Flags >> 18) & 3u;  // rldicl r0,r0,46,62
    if (mode == 0) {
        CKSrvCamera* service = SrvCamera();
        if (service->m_ui32NbStacked == 0 || service->m_aStack[0].m_pTarget == nullptr) return;
        const float zero = 0.0f;  // TOC -0x3f68
        track->m_WorldTarget.x = fx;
        track->m_WorldTarget.z = fz;
        track->m_WorldTarget.y = fy + track->m_unk64;
        const RwMatrix* ltm = FrameLtm(static_cast<CSGLeaf*>(service->m_aStack[0].m_pTarget)->m_pRwFrame);
        const float az = ltm->at.z;
        const float nx = -ltm->at.x;
        const float length = std::sqrt(ppc::fmadds(nx, nx, ppc::fmadds(az, az, zero)));  // Math_Sqrtf
        if (length == zero) return;
        const float inverse = 1.0f / length;  // TOC -0x3f6c
        const float iy = inverse * zero;
        const float ix = nx * inverse;
        const float iz = az * inverse;
        const float ox = track->m_offsetPosition.x;
        const float y = ppc::fmadds(ox, iy, fy);
        const float z = ppc::fmadds(ox, ix, fz);
        const float x = ppc::fmadds(ox, iz, fx);
        track->m_WorldPosition.y = y;
        track->m_WorldPosition.z = z;
        track->m_WorldPosition.y = track->m_WorldPosition.y + track->m_offsetPosition.y;
        const float oz = track->m_offsetPosition.z;
        track->m_WorldPosition.z = ppc::fmadds(oz, iz, z);
        track->m_WorldPosition.x = ppc::fmadds(-ix, oz, x);
        track->m_WorldPosition.y = ppc::fmadds(oz, zero, track->m_WorldPosition.y);
    } else if (mode == 1) {
        track->m_WorldTarget.x = fx;
        track->m_WorldTarget.z = fz;
        track->m_WorldTarget.y = fy + track->m_unk64;
        track->m_WorldPosition.x = fx + track->m_offsetPosition.x;
        track->m_WorldPosition.z = fz + track->m_offsetPosition.z;
        track->m_WorldPosition.y = fy + track->m_offsetPosition.y;
    }
}
}  // namespace

// 0x0013a588 CKCameraRigidTrack_Activate_maybe: the attached fx started, then the pose from the service's focus (+0x484).
void CKCameraRigidTrack::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8
    const CVector3& focus = SrvCamera()->m_v3FocusPos;
    PlaceRigid(this, focus.x, focus.y, focus.z);
}

// 0x0013a440 CKCameraRigidTrack_Deactivate_maybe
void CKCameraRigidTrack::Stop() { StopAttachedFx(); }  // 0x00144238

// 0x0013a990 CKCameraRigidTrack_Update_maybe: IKCamera_UpdateTrackBase_maybe, the pose from the first stack entry's
// point (+0xd2c), then the view obstructions (vt+0x74, a copy of that point) and the collision (vt+0x78) on the position.
void CKCameraRigidTrack::Update(float frameTime) {
    UpdateTrackBase();  // 0x00144398
    {
        const float* point = SrvCamera()->m_aStack[0].m_unk24;
        PlaceRigid(this, point[0], point[1], point[2]);
    }
    const float* point = SrvCamera()->m_aStack[0].m_unk24;
    const CVector3 focus = {point[0], point[1], point[2]};
    ResolveViewObstructions(frameTime, &focus, &m_WorldPosition);  // vt+0x74
    ResolveCameraCollision(&m_WorldTarget, &m_WorldPosition);       // vt+0x78
}

// 0x0013a828 CKCameraRigidTrack_Load
int32_t CKCameraRigidTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_offsetPosition), 3);  // one 0xc read, swapped
        ReadF32LE(file, &m_unk64);
        ReadF32LE(file, &m_unk68);
    }
    return 1;
}
