// CKCameraBalistTrack.cpp - reconstructed original translation unit 0x14f888-0x1504c8 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKCameraBalistTrack  key 0x2c7  category Camera  size 0x70  vtable 0xb1a6d8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x14f888  CKCameraBalistTrack_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKCameraBalistTrack))
//   [x] 0x14f8d8  CKCameraBalistTrack_vf54  (CKCameraBalistTrack::Pause (empty), CKCameraBalistTrack.h)
//   [x] 0x14f8e0  CKCameraBalistTrack_vf5C  (CKCameraBalistTrack::Resume (empty), CKCameraBalistTrack.h)
//   [ ] 0x14f8e8  RegisterCKCameraBalistTrackClass
//   [ ] 0x14f960  _GLOBAL__I_14f960
//   [x] 0x14f970  CKCameraBalistTrack_PostLoad  (PostLoad: KStub_Return1_144570, then 1: inherited)
//   [x] 0x14f998  CKCameraBalistTrack_RecursiveRegistration  (RecursiveRegistration: IKCamera's (0x144108), then 1: inherited)
//   [x] 0x14f9c0  CKCameraBalistTrack_Deactivate_maybe  (CKCameraBalistTrack::Stop)
//   [x] 0x14f9e8  CKCameraBalistTrack_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x14fa10  CKCameraBalistTrack_DeleteArray  (DOTD_DECLARE_FACTORIES(CKCameraBalistTrack))
//   [x] 0x14fab8  CKCameraBalistTrack_Create  (CKCameraBalistTrack())
//   [x] 0x14fb10  CKCameraBalistTrack_Activate_maybe  (CKCameraBalistTrack::Start)
//   [x] 0x14fd78  CKCameraBalistTrack_Update  (CKCameraBalistTrack::Update)
//   [x] 0x150018  CKCameraBalistTrack_CreateArray  (DOTD_DECLARE_FACTORIES(CKCameraBalistTrack))
//   [x] 0x1500d0  CKCameraBalistTrack_Load
//   [ ] 0x1502f0  CKCameraBalistTrack_Save
//
//   [ ] 0x9a7950  CKCameraBalistTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7978  CKCameraBalistTrack_GetClassType  [inline]
//   [ ] 0x9a7980  CKCameraBalistTrack_GetClassID  [inline]
//   [ ] 0x9a7988  CKCameraBalistTrack_vf80  [inline]
//   [ ] 0x9a7990  CKCameraBalistTrack_DeletingDestructor  [inline]
//   [ ] 0x9a79d8  CKCameraBalistTrack_Destructor  [inline]
#include "k2000/cameras/CKCameraBalistTrack.h"

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"

namespace {
CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }  // engine +0x70
}  // namespace

// The first stack entry's node (none when the stack is empty: the original then reads through a null node). Its
// modelling matrix (frame +0x10..+0x4c) under a parent whose class id (vt+0x18) is 2, else the stored LTM (+0x50..+0x8c).
void CKCameraBalistTrack::PlaceInNodeFrame() {
    CKSrvCamera* service = SrvCamera();
    CSGLeaf* node = service->m_ui32NbStacked != 0 ? static_cast<CSGLeaf*>(service->m_aStack[0].m_pTarget) : nullptr;
    CSGBranch* parent = static_cast<CSGBranch*>(node->m_pParent);
    RwFrame* frame = node->m_pRwFrame;
    const RwMatrix* m = (parent != nullptr && parent->GetClassID() == 2) ? &frame->modelling : &frame->ltm;
    // The target: position + right * k0, then + up * k1 (stores x, z, y each time).
    float k = m_fTargetRight;
    float tx = ppc::fmadds(k, m->right.x, m->pos.x);
    float tz = ppc::fmadds(k, m->right.z, m->pos.z);
    float ty = ppc::fmadds(k, m->right.y, m->pos.y);
    m_WorldTarget.x = tx;
    m_WorldTarget.z = tz;
    m_WorldTarget.y = ty;
    k = m_fTargetUp;
    tz = ppc::fmadds(k, m->up.z, tz);
    tx = ppc::fmadds(k, m->up.x, tx);
    ty = ppc::fmadds(k, m->up.y, ty);
    m_WorldTarget.z = tz;
    m_WorldTarget.x = tx;
    m_WorldTarget.y = ty;
    // The position: target + at * k2, then the modelling right * k3 and the modelling up * k4.
    k = m_fCameraAt;
    float px = ppc::fmadds(k, m->at.x, tx);
    float pz = ppc::fmadds(k, m->at.z, tz);
    float py = ppc::fmadds(k, m->at.y, ty);
    m_WorldPosition.x = px;
    px = m_WorldPosition.x;
    m_WorldPosition.z = pz;
    m_WorldPosition.y = py;
    const RwMatrix* modelling = &node->m_pRwFrame->modelling;
    k = m_fCameraRight;
    pz = ppc::fmadds(k, modelling->right.z, pz);
    px = ppc::fmadds(k, modelling->right.x, px);
    py = ppc::fmadds(k, modelling->right.y, py);
    m_WorldPosition.z = pz;
    m_WorldPosition.x = px;
    m_WorldPosition.y = py;
    k = m_fCameraUp;
    pz = ppc::fmadds(k, modelling->up.z, pz);
    px = ppc::fmadds(k, modelling->up.x, px);
    py = ppc::fmadds(k, modelling->up.y, py);
    m_WorldPosition.z = pz;
    m_WorldPosition.x = px;
    m_WorldPosition.y = py;
}

// 0x0014fb10 CKCameraBalistTrack_Activate_maybe: the attached fx started, then the pose.
void CKCameraBalistTrack::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8
    PlaceInNodeFrame();
}

// 0x0014f9c0 CKCameraBalistTrack_Deactivate_maybe
void CKCameraBalistTrack::Stop() { StopAttachedFx(); }  // 0x00144238

// 0x0014fd78 CKCameraBalistTrack_Update: IKCamera_UpdateTrackBase_maybe, the pose, then the collision (vt+0x78).
void CKCameraBalistTrack::Update(float /*frameTime*/) {
    UpdateTrackBase();  // 0x00144398
    PlaceInNodeFrame();
    ResolveCameraCollision(&m_WorldTarget, &m_WorldPosition);  // vt+0x78
}

// 0x001500d0 CKCameraBalistTrack_Load: the camera's common part, then (level files only) six floats.
int32_t CKCameraBalistTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);  // 0x00144580
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fTargetRight);
    ReadF32LE(file, &m_fTargetUp);
    ReadF32LE(file, &m_fCameraAt);
    ReadF32LE(file, &m_fCameraRight);
    ReadF32LE(file, &m_fCameraUp);
    ReadF32LE(file, &m_fHeightAboveGround);
    return 1;
}
