// CKCameraFixTrack.cpp - reconstructed original translation unit 0x13c110-0x13c700 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCameraFixTrack  key 0x187  category Camera  size 0x60  vtable 0xb1a138
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13c110  CKCameraFixTrack_Delete
//   [x] 0x13c160  CKCameraFixTrack_vf54  (CKCameraFixTrack::Pause (empty), CKCameraFixTrack.h)
//   [x] 0x13c168  CKCameraFixTrack_vf5C  (CKCameraFixTrack::Resume (empty), CKCameraFixTrack.h)
//   [ ] 0x13c170  RegisterCKCameraFixTrackClass
//   [ ] 0x13c1e8  _GLOBAL__I_13c1e8
//   [x] 0x13c1f8  CKCameraFixTrack_Deactivate_maybe  (CKCameraFixTrack::Stop)
//   [x] 0x13c220  CKCameraFixTrack_RecursiveRegistration  (RecursiveRegistration: IKCamera's (0x144108), then 1: inherited)
//   [x] 0x13c248  CKCameraFixTrack_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x13c270  CKCameraFixTrack_DeleteArray
//   [x] 0x13c318  CKCameraFixTrack_Create
//   [x] 0x13c370  CKCameraFixTrack_Activate_maybe  (CKCameraFixTrack::Start)
//   [x] 0x13c3f0  CKCameraFixTrack_Update  (CKCameraFixTrack::Update)
//   [x] 0x13c470  CKCameraFixTrack_CreateArray
//   [x] 0x13c528  CKCameraFixTrack_Load
//   [ ] 0x13c618  CKCameraFixTrack_Save
//
//   [ ] 0x9a7470  CKCameraFixTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7498  CKCameraFixTrack_GetClassType  [inline]
//   [ ] 0x9a74a0  CKCameraFixTrack_GetClassID  [inline]
//   [ ] 0x9a74a8  CKCameraFixTrack_vf84  [inline]
//   [ ] 0x9a74b0  CKCameraFixTrack_DeletingDestructor  [inline]
//   [ ] 0x9a74f8  CKCameraFixTrack_Destructor  [inline]
#include "k2000/cameras/CKCameraFixTrack.h"

#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"

namespace {
// The target: the camera service's focus (engine +0x70 -> +0x484), its y raised by the offset (fadds).
void TargetFocus(CKCameraFixTrack* track) {
    const CVector3& focus = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3FocusPos;
    track->m_WorldTarget.x = focus.x;
    track->m_WorldTarget.y = focus.y;
    track->m_WorldTarget.z = focus.z;
    track->m_WorldTarget.y = track->m_WorldTarget.y + track->m_fTargetHighOffset;
}
}  // namespace

// 0x0013c370 CKCameraFixTrack_Activate_maybe
void CKCameraFixTrack::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8
    TargetFocus(this);
}

// 0x0013c1f8 CKCameraFixTrack_Deactivate_maybe
void CKCameraFixTrack::Stop() { StopAttachedFx(); }  // 0x00144238

// 0x0013c3f0 CKCameraFixTrack_Update
void CKCameraFixTrack::Update(float /*frameTime*/) {
    UpdateTrackBase();  // 0x00144398
    TargetFocus(this);
}

// 0x0013c528 CKCameraFixTrack_Load
int32_t CKCameraFixTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fTargetHighOffset);
        ReadF32LE(file, &m_fRollAngle);
    }
    return 1;
}
