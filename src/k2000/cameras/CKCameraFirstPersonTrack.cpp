// CKCameraFirstPersonTrack.cpp - reconstructed original translation unit 0x1504c8-0x1512e0 (GAME_TOC1, main_toc1), 18 functions, 17 live.
// Primary class: CKCameraFirstPersonTrack  key 0x3c7  category Camera  size 0x70  vtable 0xb1a798
// Other owners: CKCameraBeacon (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1504c8  CKCameraFirstPersonTrack_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKCameraFirstPersonTrack))
//   [x] 0x150518  CKCameraFirstPersonTrack_vf54  (CKCameraFirstPersonTrack::Pause (empty), CKCameraFirstPersonTrack.h)
//   [x] 0x150520  CKCameraFirstPersonTrack_vf5C  (CKCameraFirstPersonTrack::Resume (empty), CKCameraFirstPersonTrack.h)
//   [ ] 0x150528  RegisterCKCameraFirstPersonTrackClass
//   [ ] 0x1505a0  _GLOBAL__I_1505a0
//   [x] 0x1505b0  CKCameraFirstPersonTrack_RecursiveRegistration  (RecursiveRegistration: IKCamera's (0x144108), then 1: inherited)
//   [x] 0x1505d8  CKCameraFirstPersonTrack_ApplyStickLook_maybe  (CKCameraFirstPersonTrack::ApplyStickLook)
//   [x] 0x150b08  CKCameraFirstPersonTrack_Deactivate_maybe  (CKCameraFirstPersonTrack::Stop)
//   [x] 0x150b30  CKCameraFirstPersonTrack_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x150b58  CKCameraFirstPersonTrack_DeleteArray  (DOTD_DECLARE_FACTORIES(CKCameraFirstPersonTrack))
//   [x] 0x150c00  CKCameraFirstPersonTrack_Create  (CKCameraFirstPersonTrack())
//   [x] 0x150c58  CKCameraFirstPersonTrack_Update  (CKCameraFirstPersonTrack::Update)
//   [x] 0x150d30  CKCameraFirstPersonTrack_CreateArray  (DOTD_DECLARE_FACTORIES(CKCameraFirstPersonTrack))
//   [x] 0x150de8  CKCameraFirstPersonTrack_Load
//   [x] 0x150f28  CKCameraFirstPersonTrack_Activate_maybe  (CKCameraFirstPersonTrack::Start)
//   [ ] 0x151140  CKCameraFirstPersonTrack_Save
//   [x] 0x151268  CKCameraBeacon_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKCameraBeacon))
//   [ ] 0x1512b8  FUN_001512b8  [dead]
//
//   [ ] 0x9a7a08  CKCameraFirstPersonTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7a30  CKCameraFirstPersonTrack_GetClassType  [inline]
//   [ ] 0x9a7a38  CKCameraFirstPersonTrack_GetClassID  [inline]
//   [ ] 0x9a7a40  CKCameraFirstPersonTrack_vf70  [inline]
//   [ ] 0x9a7a48  CKCameraFirstPersonTrack_vf98  [inline]
//   [ ] 0x9a7a50  CKCameraFirstPersonTrack_vfB0  [inline]
//   [ ] 0x9a7a58  CKCameraFirstPersonTrack_Destructor  [inline]
//   [ ] 0x9a7a88  CKCameraFirstPersonTrack_DeletingDestructor  [inline]
#include "k2000/cameras/CKCameraFirstPersonTrack.h"

#include <cmath>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"

namespace {
CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }  // engine +0x70
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (the shared Y axis)

// The right stick's axis: (state(positive) - state(negative)) / 255 (TOC -0x3a68), the bytes unsigned.
float StickAxis(CKS08GameManager* manager, uint8_t positive, uint8_t negative) {
    const uint8_t a = manager->GetDirectionActionState(positive);  // vt+0x188
    const uint8_t b = manager->GetDirectionActionState(negative);
    return static_cast<float>(static_cast<double>(static_cast<int32_t>(a) - static_cast<int32_t>(b))) / 255.0f;
}

// The matrix the turns are built in: the identity (flags 0x20003), as the original's stores.
void InitTurnMatrix(CMatrix34* m) {
    m->m_right = {1.0f, 0.0f, 0.0f};
    m->m_ui32Flags = 0x20003u;
    m->m_up = {0.0f, 1.0f, 0.0f};
    m->m_ui32pad1 = 0;
    m->m_at = {0.0f, 0.0f, 1.0f};
    m->m_ui32pad2 = 0;
    m->m_pos = {0.0f, 0.0f, 0.0f};
    m->m_ui32pad3 = 0;
}
}  // namespace

// 0x001505d8 CKCameraFirstPersonTrack_ApplyStickLook_maybe. TOC -0x3a9c (0), -0x3a60 (1), -0x3a58 (-1), -0x3a54
// (180/pi), -0x3a50 (85), -0x3a64 (360).
void CKCameraFirstPersonTrack::ApplyStickLook(float dt) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // engine +0x8c
    if (m_fPlayerCtrl_LR_Speed != 0.0f) {
        // The yaw: the stick's x axis, the angle (degrees) brought into [0, 360), the direction turned about y.
        const uint8_t a = manager->GetDirectionActionState(2);
        const uint8_t b = manager->GetDirectionActionState(3);
        CKSrvCamera* service = SrvCamera();
        if ((service->m_baTemporaryFlags & 0x200000u) != 0) {
            const float axis = static_cast<float>(static_cast<double>(static_cast<int32_t>(a) - static_cast<int32_t>(b))) / 255.0f;
            if (axis != 0.0f) {
                service->m_baTemporaryFlags = (service->m_baTemporaryFlags & 0xffefffffu) | 0x100000u;
                float angle = dt * (axis * m_fPlayerCtrl_LR_Speed);
                if (!(angle >= 0.0f)) {  // bge: a NaN goes round once
                    do {
                        angle = angle + 360.0f;
                    } while (angle < 0.0f);
                }
                while (angle >= 360.0f) angle = angle - 360.0f;  // cror gt|eq
                CMatrix34 turn;
                InitTurnMatrix(&turn);
                RwMatrixRotate_Thunk(&turn, &kAxisY, angle);                                  // 0x0023f708
                Mat4_TransformVectors(&turn, &m_v3CameraDirection, &m_v3CameraDirection, 1);  // 0x0023f7b0
            }
        }
    }
    if (m_fPlayerCtrl_UD_Speed == 0.0f) return;
    if ((SrvCamera()->m_baTemporaryFlags & 0x200000u) == 0) return;
    float axis = StickAxis(manager, 0, 1);
    if (axis == 0.0f) return;
    CKSrvCamera* service = SrvCamera();
    service->m_baTemporaryFlags = (service->m_baTemporaryFlags & 0xffefffffu) | 0x100000u;
    if (static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->Vf1B0() != 0) axis = -axis;  // vt+0x1b0
    // The pitch: the angle between the direction and its flat part (degrees), the turn limited so that the pitch stays
    // within 85 degrees, about the right axis of the frame whose up is y and forward the flat direction.
    const float zero = 0.0f;
    CVector3 flat = {m_v3CameraDirection.x, zero, m_v3CameraDirection.z};
    float squared = ppc::fmadds(m_v3CameraDirection.x, m_v3CameraDirection.x, zero);
    float turn = axis * m_fPlayerCtrl_UD_Speed;
    squared = ppc::fmadds(m_v3CameraDirection.z, m_v3CameraDirection.z, squared);
    turn = turn * dt;
    const float length = std::sqrt(squared);  // Math_Sqrtf 0x10690
    if (!(length == zero)) {
        const float inverse = 1.0f / length;
        const float z = flat.z * inverse;
        const float x = flat.x * inverse;
        const float y = flat.y * inverse;
        flat.z = z;
        flat.x = x;
        flat.y = y;
    }
    float dot = ppc::fmadds(m_v3CameraDirection.z, flat.z,
                            ppc::fmadds(m_v3CameraDirection.x, flat.x, m_v3CameraDirection.y * flat.y));
    if (dot <= -1.0f) {
        dot = -1.0f;
    } else if (dot >= 1.0f) {
        dot = 1.0f;
    }
    const float pitch = crt::Acosf(dot) * 57.295780181884766f;  // TocBridge_Math_Acosf 0x98e1a0
    if (!(turn > zero)) {
        float limit = !(m_v3CameraDirection.y > zero) ? pitch + 85.0f : 85.0f - pitch;
        limit = -limit;
        if (!(turn > limit)) turn = limit;
    } else {
        const float limit = !(m_v3CameraDirection.y > zero) ? 85.0f - pitch : pitch + 85.0f;
        if (!(limit > turn)) turn = limit;
    }
    CMatrix34 basis;
    InitTurnMatrix(&basis);
    Mat4_BuildFromUpAndForward(&basis, &kAxisY, &flat);  // 0x0023ff80
    const CVector3 right = basis.m_right;
    RwMatrixRotate_Thunk(&basis, &right, turn);
    Mat4_TransformVectors(&basis, &m_v3CameraDirection, &m_v3CameraDirection, 1);
}

// 0x00150f28 CKCameraFirstPersonTrack_Activate_maybe: the attached fx started, the position the service's focus copy
// (+0x490) raised by the y offset, the direction (flattened, normalised unless of length 0) from `startPosition` to the
// position, or without one the service's real view (target - position, +0x5a4 - +0x598); the target position + direction.
void CKCameraFirstPersonTrack::Start(const CVector3* startPosition) {
    StartAttachedFx();  // 0x001441e8
    CKSrvCamera* service = SrvCamera();
    const CVector3& focus = service->m_v3FocusPosCopy;
    const float fx = focus.x;
    m_WorldPosition.x = fx;
    m_WorldPosition.y = focus.y;
    const float fz = focus.z;
    m_WorldPosition.z = fz;
    m_WorldPosition.y = m_WorldPosition.y + m_fCameraYOffsetFromTargetedLeaf;
    float dx;
    float dy;
    float dz;
    if (startPosition != nullptr) {
        dx = fx - startPosition->x;
        dy = m_WorldPosition.y - startPosition->y;
        dz = fz - startPosition->z;
    } else {
        dx = service->m_v3RealTarget.x - service->m_v3RealPos.x;
        dy = service->m_v3RealTarget.y - service->m_v3RealPos.y;
        dz = service->m_v3RealTarget.z - service->m_v3RealPos.z;
    }
    m_v3CameraDirection.x = dx;
    m_v3CameraDirection.y = dy;
    m_v3CameraDirection.y = 0.0f;  // TOC -0x3a9c
    const float y = m_v3CameraDirection.y;
    m_v3CameraDirection.z = dz;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, y * y)));  // Math_Sqrtf 0x10690
    if (!(length == 0.0f)) {
        const float inverse = 1.0f / length;
        const float z = inverse * m_v3CameraDirection.z;
        const float x = inverse * m_v3CameraDirection.x;
        const float yy = inverse * m_v3CameraDirection.y;
        m_v3CameraDirection.z = z;
        m_v3CameraDirection.x = x;
        m_v3CameraDirection.y = yy;
    }
    const float tx = m_WorldPosition.x + m_v3CameraDirection.x;
    const float tz = m_WorldPosition.z + m_v3CameraDirection.z;
    const float ty = m_WorldPosition.y + m_v3CameraDirection.y;
    m_WorldTarget.x = tx;
    m_WorldTarget.z = tz;
    m_WorldTarget.y = ty;
}

// 0x00150b08 CKCameraFirstPersonTrack_Deactivate_maybe
void CKCameraFirstPersonTrack::Stop() { StopAttachedFx(); }  // 0x00144238

// 0x00150c58 CKCameraFirstPersonTrack_Update: IKCamera_UpdateTrackBase_maybe, the position the focus copy raised by the y
// offset, the stick look, then the target position + direction.
void CKCameraFirstPersonTrack::Update(float frameTime) {
    UpdateTrackBase();  // 0x00144398
    const CVector3& focus = SrvCamera()->m_v3FocusPosCopy;
    m_WorldPosition.x = focus.x;
    m_WorldPosition.y = focus.y;
    m_WorldPosition.z = focus.z;
    m_WorldPosition.y = m_WorldPosition.y + m_fCameraYOffsetFromTargetedLeaf;
    ApplyStickLook(frameTime);
    const float tx = m_WorldPosition.x + m_v3CameraDirection.x;
    const float tz = m_WorldPosition.z + m_v3CameraDirection.z;
    const float ty = m_WorldPosition.y + m_v3CameraDirection.y;
    m_WorldTarget.x = tx;
    m_WorldTarget.z = tz;
    m_WorldTarget.y = ty;
}

// 0x00150de8 CKCameraFirstPersonTrack_Load: the camera's common part, then (level files only) the y offset and the two
// stick speeds (the direction is not loaded).
int32_t CKCameraFirstPersonTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);  // 0x00144580
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fCameraYOffsetFromTargetedLeaf);
    ReadF32LE(file, &m_fPlayerCtrl_LR_Speed);
    ReadF32LE(file, &m_fPlayerCtrl_UD_Speed);
    return 1;
}
