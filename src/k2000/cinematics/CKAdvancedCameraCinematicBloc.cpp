// CKAdvancedCameraCinematicBloc.cpp - reconstructed original translation unit 0x1702f8-0x172ba8 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKAdvancedCameraCinematicBloc  key 0x208  category CinematicNode  size 0xb0  vtable 0xb1af70
// Other owners: Math (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1702f8  CKAdvancedCameraCinematicBloc_Delete
//   [ ] 0x170348  CKAdvancedCameraCinematicBloc_EvaluateEase_maybe  [dead]
//   [x] 0x1703a0  CKAdvancedCameraCinematicBloc_Abort
//   [ ] 0x170440  RegisterCKAdvancedCameraCinematicBlocClass
//   [ ] 0x1704b8  _GLOBAL__I_1704b8
//   [x] 0x1704c8  CKAdvancedCameraCinematicBloc_Stop
//   [x] 0x1706a8  Math_GetYawPitchToPoint_maybe  [dead: no pointer to its descriptor 0xb629a8, no call]  (Math_GetYawPitchToPoint: ViewAngles out of line)
//   [ ] 0x1707b8  CKAdvancedCameraCinematicBloc_Save
//   [x] 0x1707e0  CKAdvancedCameraCinematicBloc_RecursiveRegistration
//   [x] 0x170ab8  CKAdvancedCameraCinematicBloc_DeleteArray
//   [x] 0x170b58  CKAdvancedCameraCinematicBloc_Create
//   [x] 0x170bb0  CKAdvancedCameraCinematicBloc_Destroy  (empty: the default)
//   [x] 0x170bb8  CKAdvancedCameraCinematicBloc_CreateArray
//   [ ] 0x170c68  CKAdvancedCameraCinematicBloc_FindEaseTimeForValue_maybe  [dead]
//   [x] 0x170da8  CKAdvancedCameraCinematicBloc_ComputeOrbitPoint_maybe
//   [x] 0x171350  CKAdvancedCameraCinematicBloc_Complete
//   [x] 0x171570  CKAdvancedCameraCinematicBloc_Update
//   [x] 0x171d40  CKAdvancedCameraCinematicBloc_Start
//   [x] 0x172560  CKAdvancedCameraCinematicBloc_Load
//
//   [ ] 0x9a9250  CKAdvancedCameraCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9288  CKAdvancedCameraCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9290  CKAdvancedCameraCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9298  CKAdvancedCameraCinematicBloc_PreActivate  [inline]
//   [ ] 0x9a92a0  CKAdvancedCameraCinematicBloc_Destructor  [inline]
//   [ ] 0x9a92c0  CKAdvancedCameraCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKAdvancedCameraCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include <cmath>
#include <cstdint>
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

// 0x00172560 CKAdvancedCameraCinematicBloc_Load
int32_t CKAdvancedCameraCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        for (IKSerializable*& ref : m_apUnk38) IKFile_ReadRef(file, &ref);
        ReadU8(file, &m_unk60);
        ReadF32LE(file, &m_unk64);
        ReadF32LE(file, &m_unk68);
        ReadF32LE(file, &m_unk6c);
    }
    return 1;
}

namespace {
constexpr float kPi = 3.14159274f;        // TOC -0x33d4
constexpr float kTwoPi = 6.28318548f;     // TOC -0x33d0
constexpr float kDegToRad = 0.0174532905f;  // TOC -0x33d8
constexpr float kJustStarted = -2.0f;     // TOC -0x344c: the state after Start
constexpr float kSwitchPending = -1.0f;   // TOC -0x33dc: the state of the switch to the moving camera

float Sqrtf(float value) { return static_cast<float>(std::sqrt(static_cast<double>(value))); }  // Math_Sqrtf 0x10690

// The sign bit, as the original tests it (the float's word below 0).
bool SignBit(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, 4);
    return (bits >> 31) != 0;
}
// The inlined sine / cosine: the octant polynomials for a non-negative angle, the library's otherwise.
float SinOf(float angle) { return SignBit(angle) ? -crt::LibSinf(-angle) : crt::InlineSinf(angle); }
float CosOf(float angle) { return SignBit(angle) ? crt::LibCosf(-angle) : crt::InlineCosf(angle); }

CKSrvCamera* CameraService() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }  // engine +0x70
IKCamera* CameraAt(IKSerializable* const* slots, int32_t index) { return static_cast<IKCamera*>(slots[index]); }
float CurveAt(IKSerializable* curve, float x) { return static_cast<CKCurve2DCpnt*>(curve)->Evaluate(x); }  // 0x00249ea8

// The camera becomes the next one unless it is the current one; outside a locked switch (flags bit 4) with `time` and
// `mode` and bit 22 cleared.
void RequestCamera(CKSrvCamera* service, IKCamera* camera, float time, uint8_t mode) {
    if (service->m_pCurrentCamera == camera) return;
    service->m_pNextCamera = camera;
    if ((service->m_baTemporaryFlags & 0x10u) != 0) return;
    service->m_fSwitchTimer = time;
    service->m_ui8TransitionMode = mode;
    service->m_baTemporaryFlags &= 0xffbfffffu;
}

// The view from `position` to `target`: the pitch (Math_Asinf of the normalised y) and the yaw (Vec3_GetYawAngleFromZ
// 0x244528 of the normalised vector); a zero length keeps the vector as it is.
void ViewAngles(const CVector3& position, const CVector3& target, float* yaw, float* pitch) {
    CVector3 d = {target.x - position.x, target.y - position.y, target.z - position.z};
    const float length = Sqrtf(ppc::fmadds(d.z, d.z, ppc::fmadds(d.x, d.x, d.y * d.y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        d.y = d.y * inverse;
        d.z = d.z * inverse;
        d.x = d.x * inverse;
    }
    *pitch = crt::Asinf(d.y);  // 0x0098f1d0 TocBridge_Math_Asinf
    *yaw = Vec3_GetYawAngleFromZ(&d);
}
}  // namespace

// 0x00170da8 CKAdvancedCameraCinematicBloc_ComputeOrbitPoint_maybe
CVector3 CKAdvancedCameraCinematicBloc::ComputeOrbitPoint(float yaw, float pitch, const CVector3& base) {
    CVector3 out = base;
    const float sinYaw = SinOf(yaw);
    const float cosPitch = CosOf(pitch);
    out.x = ppc::fmadds(cosPitch, sinYaw, base.x);
    out.y = base.y + SinOf(pitch);
    out.z = ppc::fmadds(CosOf(yaw), cosPitch, base.z);
    return out;
}

// 0x00171d40 CKAdvancedCameraCinematicBloc_Start
void CKAdvancedCameraCinematicBloc::Start() {
    m_pRelatedScene->m_unk24 = static_cast<uint8_t>((m_pRelatedScene->m_unk24 & 0xfe) | 1);
    StartCommon();
    CKSrvCamera* service = CameraService();
    CVector3 startTarget;
    if (IKCamera* start = CameraAt(m_apUnk38, 0)) {
        start->ResetTrack();  // vt+0x6c
        if (m_unk60 != 0) {
            RequestCamera(service, start, m_unk68, static_cast<uint8_t>(m_unk60 - 1));
        } else {
            RequestCamera(service, start, 0.0f, 0);
        }
        start = CameraAt(m_apUnk38, 0);
        m_v3StartPos = start->m_WorldPosition;
        m_fStartFov = start->m_unk18;
        m_fStartValue84 = start->Vf84();  // vt+0x84
        startTarget = start->m_WorldTarget;
    } else {
        // The service's real pose (+0x598) and its view axis (+0x5c8).
        m_v3StartPos = service->m_v3RealPos;
        startTarget = {m_v3StartPos.x + service->m_v3RealAxisZ.x, m_v3StartPos.y + service->m_v3RealAxisZ.y,
                       m_v3StartPos.z + service->m_v3RealAxisZ.z};
    }
    ViewAngles(m_v3StartPos, startTarget, &m_fStartYaw, &m_fStartPitch);
    if (IKCamera* end = CameraAt(m_apUnk38, 1)) {
        end->ResetTrack();
        end = CameraAt(m_apUnk38, 1);
        m_v3EndPos = end->m_WorldPosition;
        m_fEndFov = end->m_unk18;
        m_fEndValue84 = end->Vf84();
        ViewAngles(m_v3EndPos, end->m_WorldTarget, &m_fEndYaw, &m_fEndPitch);
    } else {
        m_v3EndPos = m_v3StartPos;
        m_fEndYaw = m_fStartYaw;
        m_fEndPitch = m_fStartPitch;
    }
    // The end's yaw within half a turn of the start's (flag 0x100: the long way round), the same for the pitch.
    const float startYaw = m_fStartYaw;
    const float startPitch = m_fStartPitch;
    const float endYaw = m_fEndYaw;
    if ((m_DataFlags & 0x100) == 0) {
        if (startYaw + kPi < endYaw) {
            m_fEndYaw = endYaw - kTwoPi;
        } else if (startYaw - kPi > endYaw) {
            m_fEndYaw = endYaw + kTwoPi;
        }
    } else {
        if (startYaw + kPi > endYaw && endYaw > startYaw) {
            m_fEndYaw = endYaw + kTwoPi;
        } else if (startYaw - kPi < endYaw && endYaw < startYaw) {
            m_fEndYaw = endYaw - kTwoPi;
        }
    }
    const float endPitch = m_fEndPitch;
    if (startPitch + kPi < endPitch) {
        m_fEndPitch = endPitch - kTwoPi;
    } else if (startPitch - kPi > endPitch) {
        m_fEndPitch = endPitch + kTwoPi;
    }
    m_fTimeLeft = kJustStarted;
}

// 0x00171350 CKAdvancedCameraCinematicBloc_Complete
void CKAdvancedCameraCinematicBloc::Complete() {
    CompleteBloc();
    if (IKCamera* camera = CameraAt(m_apUnk38, 0)) camera->ResetTrack();  // vt+0x6c
    if (IKCamera* camera = CameraAt(m_apUnk38, 1)) camera->ResetTrack();
}

// 0x001704c8 CKAdvancedCameraCinematicBloc_Stop
void CKAdvancedCameraCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x001703a0 CKAdvancedCameraCinematicBloc_Abort
void CKAdvancedCameraCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    if (IKCamera* camera = CameraAt(m_apUnk38, 0)) camera->ResetTrack();
    if (IKCamera* camera = CameraAt(m_apUnk38, 1)) camera->ResetTrack();
}

// 0x00171570 CKAdvancedCameraCinematicBloc_Update
void CKAdvancedCameraCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    CKSrvCamera* service = CameraService();
    const float left = m_fTimeLeft;
    if (left == kJustStarted) {
        m_fTimeLeft = kSwitchPending;
        return;
    }
    if (left == kSwitchPending) {
        // The moving camera takes the start pose and becomes the next camera (no transition).
        if ((service->m_baTemporaryFlags & 8u) != 0) return;
        m_fTimeLeft = m_unk64;
        IKCamera* moved = CameraAt(m_apUnk38, 2);
        const bool own = moved != nullptr;
        if (!own) moved = CameraAt(m_apUnk38, 1);
        if (moved == nullptr) return;
        moved->m_WorldPosition = m_v3StartPos;
        moved->m_WorldTarget = ComputeOrbitPoint(m_fStartYaw, m_fStartPitch, m_v3StartPos);
        moved->Vf88(m_fStartValue84);  // vt+0x88
        moved->m_unk18 = m_fStartFov;
        RequestCamera(service, moved, 0.0f, 0);
        if (own) CameraAt(m_apUnk38, 1)->Start(nullptr);  // vt+0x50
        return;
    }
    IKCamera* end = CameraAt(m_apUnk38, 1);
    if (end == nullptr || !(left > 0.0f)) {
        // The move is over: with flag 0x80 the bloc completes once it held +0x6c seconds.
        if ((m_DataFlags & 0x80) != 0 && time->m_afCurrentTime[0] - m_fEndTime >= m_unk6c) Complete();  // vt+0x64
        return;
    }
    m_fTimeLeft = left - time->m_afDeltaTime[0];
    if (CameraAt(m_apUnk38, 2) != nullptr) {
        // A separate moving camera: the end camera runs (vt+0x60) and its pose is taken again.
        end->Update(time->m_afDeltaTime[0]);
        end = CameraAt(m_apUnk38, 1);
        m_v3EndPos = end->m_WorldPosition;
        m_fEndFov = end->m_unk18;
        m_fEndValue84 = end->Vf84();
        ViewAngles(m_v3EndPos, end->m_WorldTarget, &m_fEndYaw, &m_fEndPitch);
    }
    CVector3 position;
    CVector3 target;
    float fov;
    float value84;
    if (m_fTimeLeft <= 0.0f) {
        m_fTimeLeft = 0.0f;
        position = m_v3EndPos;
        target = ComputeOrbitPoint(m_fEndYaw, m_fEndPitch, m_v3EndPos);
        fov = m_fEndFov;
        value84 = m_fEndValue84;
        m_fEndTime = time->m_afCurrentTime[0];
    } else {
        // The blend factor: linear with flag 0x200, else smoothed (3u^2 - 2u^3).
        const float linear = 1.0f - m_fTimeLeft / m_unk64;
        float s = linear;
        if ((m_DataFlags & 0x200) == 0) {
            const float squared = linear * linear;
            s = ppc::fmadds(linear, squared * -2.0f, squared * 3.0f);  // TOC -0x344c / -0x3448
        }
        const float r = 1.0f - s;
        const float offsetX = CurveAt(m_apUnk38[3], s);
        const float offsetY = CurveAt(m_apUnk38[4], s);
        const float offsetZ = CurveAt(m_apUnk38[5], s);
        const float endYawPart = s * m_fEndYaw;
        const float endPitchPart = s * m_fEndPitch;
        const float startX = ppc::fmadds(r, m_v3StartPos.x, offsetX);
        const float startY = ppc::fmadds(r, m_v3StartPos.y, offsetY);
        const float startZ = ppc::fmadds(r, m_v3StartPos.z, offsetZ);
        position.x = ppc::fmadds(s, m_v3EndPos.x, startX);
        const float yaw = ppc::fmadds(r, m_fStartYaw, endYawPart);
        position.y = ppc::fmadds(s, m_v3EndPos.y, startY);
        const float pitch = ppc::fmadds(r, m_fStartPitch, endPitchPart);
        position.z = ppc::fmadds(s, m_v3EndPos.z, startZ);
        const float yawOffset = CurveAt(m_apUnk38[6], s);
        const float pitchOffset = CurveAt(m_apUnk38[7], s);
        target = ComputeOrbitPoint(ppc::fmadds(yawOffset, kDegToRad, yaw), ppc::fmadds(pitchOffset, kDegToRad, pitch),
                                   position);
        fov = ppc::fmadds(r, m_fStartFov, s * m_fEndFov);
        fov = fov + CurveAt(m_apUnk38[8], s);
        value84 = ppc::fmadds(r, m_fStartValue84, s * m_fEndValue84);
        value84 = value84 + CurveAt(m_apUnk38[9], s);
    }
    IKCamera* moved = CameraAt(m_apUnk38, 2);
    if (moved == nullptr) moved = CameraAt(m_apUnk38, 1);
    moved->m_WorldPosition = position;
    moved->m_WorldTarget = target;
    moved->Vf88(value84);  // vt+0x88
    moved->m_unk18 = fov;
}

// 0x001707e0 CKAdvancedCameraCinematicBloc_RecursiveRegistration
void CKAdvancedCameraCinematicBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    for (IKSerializable* object : m_apUnk38) {
        if (object != nullptr) object->RecursiveRegistration(type);  // vt+0x24
    }
}

// 0x001706a8 Math_GetYawPitchToPoint_maybe: the out-of-line copy of the view angles the bloc inlines (ViewAngles above:
// the pitch Math_Asinf of the normalised y, the yaw Vec3_GetYawAngleFromZ; r3 is not read). Dead in the original (no
// pointer to its descriptor 0xb629a8, no call).
void Math_GetYawPitchToPoint(const CVector3* from, const CVector3* to, float* yaw, float* pitch) {
    ViewAngles(*from, *to, yaw, pitch);
}
