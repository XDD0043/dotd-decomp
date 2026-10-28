// CKManageCameraCinematicBloc.cpp - reconstructed original translation unit 0x17f458-0x1803c0 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CKManageCameraCinematicBloc  key 0x5c8  category CinematicNode  size 0x50  vtable 0xb1b578
// Other owners: CKParticleCinematicBloc (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x17f458  CKManageCameraCinematicBloc_Delete
//   [x] 0x17f4a8  CKManageCameraCinematicBloc_Abort
//   [ ] 0x17f508  RegisterCKManageCameraCinematicBlocClass
//   [ ] 0x17f580  _GLOBAL__I_17f580
//   [x] 0x17f590  CKManageCameraCinematicBloc_Stop
//   [x] 0x17f770  CKManageCameraCinematicBloc_Update
//   [ ] 0x17f8b8  CKManageCameraCinematicBloc_Save
//   [ ] 0x17f8e0  CKManageCameraCinematicBloc_RecursiveRegistration
//   [x] 0x17fa18  CKManageCameraCinematicBloc_DeleteArray
//   [x] 0x17fac0  CKManageCameraCinematicBloc_Create
//   [ ] 0x17fb18  CKManageCameraCinematicBloc_Destroy
//   [x] 0x17fb20  CKManageCameraCinematicBloc_CreateArray
//   [x] 0x17fbd8  CKManageCameraCinematicBloc_Start
//   [x] 0x17ffb8  CKManageCameraCinematicBloc_Load
//   [x] 0x180188  CKManageCameraCinematicBloc_Complete
//   [ ] 0x180360  CKParticleCinematicBloc_Delete
//   [ ] 0x1803b0  FUN_001803b0  [dead]
//
//   [ ] 0x9a99d0  CKManageCameraCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9a08  CKManageCameraCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9a10  CKManageCameraCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9a18  CKManageCameraCinematicBloc_PreActivate  [inline]
//   [ ] 0x9a9a20  CKManageCameraCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9a40  CKManageCameraCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKManageCameraCinematicBloc.h"

#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

// 0x0017ffb8 CKManageCameraCinematicBloc_Load
int32_t CKManageCameraCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pCamera);
        ReadF32LE(file, &m_fTransitionTime);
        ReadU8(file, &m_ui8CamTransition);
        IKFile_ReadRef(file, &m_pTarget);
        ReadF32LE(file, &m_fCameraTime);
    }
    return 1;
}

// 0x0017fbd8 CKManageCameraCinematicBloc_Start. The scene takes the camera over (bit 0 of its +0x24: ReleaseCamera gives
// it back), the bloc's own camera is reset and, when it is not the current one, becomes the next with the bloc's
// transition; then the camera follows the actor's node (or the bloc's target).
void CKManageCameraCinematicBloc::Start() {
    m_pRelatedScene->m_unk24 = static_cast<uint8_t>((m_pRelatedScene->m_unk24 & 0xfe) | 1);
    StartCommon();
    m_fCameraCurTime = m_fCameraTime;
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (m_pCamera != nullptr) {
        IKCamera* camera = static_cast<IKCamera*>(m_pCamera);
        camera->ResetTrack();  // vt+0x6c
        if (service->m_pCurrentCamera != camera) {
            service->m_pNextCamera = camera;
            if ((service->m_baTemporaryFlags & 0x10u) == 0) {
                service->m_fSwitchTimer = m_fTransitionTime;
                service->m_ui8TransitionMode = m_ui8CamTransition;
                service->m_baTemporaryFlags &= 0xffbfffffu;
            }
        }
    }
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    if (data != nullptr && data->m_pHook != nullptr) {
        service->SwitchCameraIfDifferent(0.0f, static_cast<IKHook*>(data->m_pHook)->m_pKGLObject, 0);
    } else if (m_pTarget != nullptr) {
        service->SwitchCameraIfDifferent(0.0f, m_pTarget, 0);
    }
}

// 0x0017f770 CKManageCameraCinematicBloc_Update. With bit 7 of the flags the bloc ends after its camera time (counted on
// the fixed game time); with bit 8 when its camera says it is finished.
void CKManageCameraCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    uint32_t flags = m_DataFlags;
    if ((flags & 0x80) != 0) {
        if (m_fCameraCurTime < 0.0f) {
            Complete();  // vt+0x64
            flags = m_DataFlags;
        } else {
            m_fCameraCurTime = m_fCameraCurTime - time->m_afDeltaTime[1];
        }
    }
    if ((flags & 0x100) != 0) {
        if (m_pCamera != nullptr && static_cast<IKCamera*>(m_pCamera)->IsFinished() != 0) Complete();  // vt+0x64
    }
}

// 0x0017f590 CKManageCameraCinematicBloc_Stop: the completion inlined (the outputs activated), then Complete.
void CKManageCameraCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x00180188 CKManageCameraCinematicBloc_Complete
void CKManageCameraCinematicBloc::Complete() { CompleteBloc(); }

// 0x0017f4a8 CKManageCameraCinematicBloc_Abort
void CKManageCameraCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    if (m_pCamera != nullptr) static_cast<IKCamera*>(m_pCamera)->ResetTrack();  // vt+0x6c
}
