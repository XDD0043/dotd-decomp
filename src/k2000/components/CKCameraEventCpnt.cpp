// CKCameraEventCpnt.cpp - reconstructed original translation unit 0x165a08-0x166328 (GAME_TOC1, main_toc1), 22 functions, 20 live.
// Primary class: CKCameraEventCpnt  key 0x1246  category Component  size 0x18  vtable 0xb1ab10
// Other owners: ScriptedCameraHandle (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x165a08  CKCameraEventCpnt_Delete
//   [ ] 0x165a58  CKCameraEventCpnt_Construct  [dead]
//   [ ] 0x165a68  CKCameraEventCpnt_Construct_2  [dead]
//   [x] 0x165a78  ScriptedCameraHandle_SetPositionAndTarget_maybe
//   [x] 0x165af8  ScriptedCameraHandle_Reset_maybe
//   [ ] 0x165b50  RegisterCKCameraEventCpntClass
//   [ ] 0x165bc8  _GLOBAL__I_165bc8
//   [x] 0x165bd8  ScriptedCameraHandle_Activate_maybe
//   [x] 0x165d68  CKCameraEventCpnt_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x165db0  CKCameraEventCpnt_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x165de0  CKCameraEventCpnt_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x165e10  CKCameraEventCpnt_DeleteArray
//   [x] 0x165eb8  ScriptedCameraHandle_TryActivate_maybe
//   [x] 0x166020  CKCameraEventCpnt_Create
//   [x] 0x166058  CKCameraEventCpnt_CreateArray
//   [ ] 0x1660f0  CKCameraEventCpnt_Save
//   [x] 0x1660f8  CKCameraEventCpnt_MessageProc  (IKBaseClass's default (1))
//   [x] 0x166100  CKCameraEventCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x166108  CKCameraEventCpnt_PostLoad
//   [x] 0x166128  CKCameraEventCpnt_Destroy  (empty: the default)
//   [x] 0x166130  ScriptedCameraHandle_Release_maybe
//   [x] 0x166240  CKCameraEventCpnt_Load
//
//   [ ] 0x9a8bf8  CKCameraEventCpnt_IsKindOfClass  [inline]
//   [x] 0x9a8c20  CKCameraEventCpnt_GetClassType  [inline]
//   [x] 0x9a8c28  CKCameraEventCpnt_GetClassID  [inline]
#include "k2000/components/CKCameraEventCpnt.h"

#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"

// 0x00166240 CKCameraEventCpnt_Load
int32_t CKCameraEventCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pCamera);
        ReadF32LE(file, &m_unk08);
    }
    return 1;
}

namespace {
IKCamera* CameraOf(const CKCameraEventCpnt* handle) { return static_cast<IKCamera*>(handle->m_pCamera); }
}  // namespace

// 0x00166108 CKCameraEventCpnt_PostLoad
int32_t CKCameraEventCpnt::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_fBaseFov = CameraOf(this)->m_unk18;
    return 1;
}

// 0x00165af8 ScriptedCameraHandle_Reset_maybe
void CKCameraEventCpnt::Reset() {
    m_fLastActivation = -1.0f;  // 0xbf800000
    m_bActive = 0;
    CameraOf(this)->ResetTrack();  // vt+0x6c
}

// 0x00165a78 ScriptedCameraHandle_SetPositionAndTarget_maybe
void CKCameraEventCpnt::SetPositionAndTarget(float fovScale, const CVector3* position, const CVector3* direction) {
    if (m_bActive == 0) return;
    IKCamera* camera = CameraOf(this);
    camera->m_WorldPosition = *position;
    camera->m_WorldTarget.x = position->x + direction->x;
    camera->m_WorldTarget.z = position->z + direction->z;
    camera->m_WorldTarget.y = position->y + direction->y;
    camera->m_unk18 = m_fBaseFov * fovScale;
}

// 0x00165bd8 ScriptedCameraHandle_Activate_maybe
void CKCameraEventCpnt::Activate(float fovScale, float blend, float time, const CVector3* position,
                                 const CVector3* direction) {
    m_bActive = 1;
    m_fLastActivation = time;
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    uint32_t i = 0;
    while (i < service->m_unke24 && service->m_apCinematicOwner[i] != this) ++i;
    if (i == service->m_unke24) {
        service->m_apCinematicOwner[service->m_unke24] = this;
        ++service->m_unke24;
    }
    service->m_pNextCamera = CameraOf(this);
    service->m_fSwitchTimer = blend;
    service->m_ui8TransitionMode = 0;
    service->m_baTemporaryFlags = (service->m_baTemporaryFlags | 0x400000u) & ~0x30u;
    service->SetActiveScriptedCamera(time, this);  // 0x0012b4f0
    SetPositionAndTarget(fovScale, position, direction);  // inlined
}

// 0x00165eb8 ScriptedCameraHandle_TryActivate_maybe
uint8_t CKCameraEventCpnt::TryActivate(const CVector3* position, const CVector3* direction, float fovScale, float blend,
                                       int32_t force) {
    const float time = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0];  // the clock +0x04
    if (force == 0) {
        // fcmpu / ble, blt: a NaN last time or delay goes on to the service.
        if (m_fLastActivation > 0.0f && (time - m_fLastActivation) < m_unk08) return 0;
        if (!static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->CanStartScriptedCamera(time)) return 0;  // 0x0012b420
    }
    Activate(fovScale, blend, time, position, direction);
    return 1;
}

// 0x00166130 ScriptedCameraHandle_Release_maybe
void CKCameraEventCpnt::Release() {
    if (m_bActive == 0) return;
    CameraOf(this)->m_unk18 = m_fBaseFov;
    m_bActive = 0;
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    service->SetActiveScriptedCamera(0.0f, nullptr);  // 0x0012b4f0
    const uint32_t count = service->m_unke24;
    if (count == 0) return;
    uint32_t i = 0;
    while (service->m_apCinematicOwner[i] != this) {
        if (++i == count) return;
    }
    service->m_unke24 = count - 1;
    if (i != count - 1) service->m_apCinematicOwner[i] = service->m_apCinematicOwner[count - 1];
}
