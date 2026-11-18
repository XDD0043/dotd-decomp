// CKBlackBandBloc.cpp - reconstructed original translation unit 0x174a58-0x175918 (GAME_TOC1, main_toc1), 18 functions, 17 live.
// Primary class: CKBlackBandBloc  key 0x2c8  category CinematicNode  size 0x3c  vtable 0xb1b0a0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x174a58  CKBlackBandBloc_Delete
//   [x] 0x174aa8  CKBlackBandBloc_Abort
//   [ ] 0x174ab8  CKBlackBandBloc_DisableBands_maybe  [dead]
//   [ ] 0x174b00  RegisterCKBlackBandBlocClass
//   [ ] 0x174b78  _GLOBAL__I_174b78
//   [x] 0x174b88  CKBlackBandBloc_StartSceneExitTransitions_maybe  [dead: no pointer to its descriptor 0xb63288, no call]  (CKBlackBandBloc::StartSceneExitTransitions)
//   [x] 0x174c70  CKBlackBandBloc_StartSceneEntryTransitions_maybe  [dead: no pointer to its descriptor 0xb63290, no call]  (CKBlackBandBloc::StartSceneEntryTransitions)
//   [x] 0x174d58  CKBlackBandBloc_Stop
//   [x] 0x174f38  CKBlackBandBloc_Update
//   [x] 0x174fa0  CKBlackBandBloc_Load
//   [ ] 0x175048  CKBlackBandBloc_Save
//   [x] 0x175070  CKBlackBandBloc_RecursiveRegistration
//   [x] 0x175100  CKBlackBandBloc_DeleteArray
//   [x] 0x1751a8  CKBlackBandBloc_Create
//   [x] 0x175200  CKBlackBandBloc_Destroy  (empty: the default)
//   [x] 0x175208  CKBlackBandBloc_CreateArray
//   [x] 0x1752c0  CKBlackBandBloc_Start
//   [x] 0x175740  CKBlackBandBloc_Complete
//
//   [ ] 0x9a93b8  CKBlackBandBloc_IsKindOfClass  [inline]
//   [ ] 0x9a93f0  CKBlackBandBloc_GetClassType  [inline]
//   [ ] 0x9a93f8  CKBlackBandBloc_GetClassID  [inline]
//   [ ] 0x9a9400  CKBlackBandBloc_vf58  [inline]
//   [ ] 0x9a9408  CKBlackBandBloc_DeletingDestructor  [inline]
//   [ ] 0x9a9450  CKBlackBandBloc_Destructor  [inline]
#include "k2000/cinematics/CKBlackBandBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"

// 0x00174fa0 CKBlackBandBloc_Load
int32_t CKBlackBandBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) ReadU32LE(file, &m_unk38);
    return 1;
}

// 0x001752c0 CKBlackBandBloc_Start
void CKBlackBandBloc::Start() {
    StartCommon();
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    service->m_baData = static_cast<uint8_t>(service->m_baData & ~0x20u);
    service->m_baData = static_cast<uint8_t>(service->m_baData & ~0x10u);
    if (m_unk38 == 1) {
        // 0x00174c70 CKBlackBandBloc_StartSceneEntryTransitions_maybe (inlined)
        uint32_t count = 0;
        IKSerializable** scenes = service->GetScenes(&count);
        for (uint32_t i = count; i != 0; --i) {
            CKCinematicScene* scene = static_cast<CKCinematicScene*>(scenes[i - 1]);
            if ((scene->m_baData & 1u) != 0 && scene->m_unk40 == 0) scene->StartEntryTransition();  // 0x0016a5d0
        }
        service->m_baData = static_cast<uint8_t>((service->m_baData & ~0x10u) | 0x10u);
    } else if (m_unk38 == 2) {
        // 0x00174b88 CKBlackBandBloc_StartSceneExitTransitions_maybe (inlined)
        service->m_baData = static_cast<uint8_t>((service->m_baData & ~0x20u) | 0x20u);
        uint32_t count = 0;
        IKSerializable** scenes = service->GetScenes(&count);
        for (uint32_t i = count; i != 0; --i) {
            CKCinematicScene* scene = static_cast<CKCinematicScene*>(scenes[i - 1]);
            if ((scene->m_baData & 1u) == 0) continue;
            if ((scene->m_baBlackBandData & 0x40u) != 0 && scene->m_unk40 == 0) continue;
            scene->StartExitTransition(0);  // 0x00169980
        }
    }
}

// 0x00175740 CKBlackBandBloc_Complete
void CKBlackBandBloc::Complete() { CompleteBloc(); }

// 0x00174f38 CKBlackBandBloc_Update
void CKBlackBandBloc::Update(IKTime* /*time*/) {
    if (CheckSekensStop() != 0) Complete();  // vt+0x64
}

// 0x00174d58 CKBlackBandBloc_Stop
void CKBlackBandBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x00174aa8 CKBlackBandBloc_Abort
void CKBlackBandBloc::Abort() { m_DataFlags &= 0xfffffffeu; }

// 0x00175070 CKBlackBandBloc_RecursiveRegistration
void CKBlackBandBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
}

// 0x00174b88 CKBlackBandBloc_StartSceneExitTransitions_maybe: the out-of-line copy of Start's mode-2 code (r3 is not
// read): the service's band bit 5 set, then every playing scene (last first) starts its exit transition unless its bands
// are kept (+0x34 bit 6) with no pending entry. Dead in the original (no pointer to its descriptor 0xb63288, no call).
void CKBlackBandBloc::StartSceneExitTransitions() {
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    service->m_baData = static_cast<uint8_t>((service->m_baData & ~0x20u) | 0x20u);
    uint32_t count = 0;
    IKSerializable** scenes = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic)->GetScenes(&count);  // 0x001665e8
    while (count != 0) {
        --count;
        CKCinematicScene* scene = static_cast<CKCinematicScene*>(scenes[count]);
        if ((scene->m_baData & 1u) == 0) continue;
        if ((scene->m_baBlackBandData & 0x40u) != 0 && scene->m_unk40 == 0) continue;
        scene->StartExitTransition(0);  // 0x00169980
    }
}

// 0x00174c70 CKBlackBandBloc_StartSceneEntryTransitions_maybe: the out-of-line copy of Start's mode-1 code: every playing
// scene without a pending entry (last first) starts its entry transition, then the service's band bit 4 set. Dead in the
// original (no pointer to its descriptor 0xb63290, no call).
void CKBlackBandBloc::StartSceneEntryTransitions() {
    uint32_t count = 0;
    IKSerializable** scenes = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic)->GetScenes(&count);
    for (uint32_t i = count - 1; i != 0xffffffffu; i = count - 1) {
        count = i;
        CKCinematicScene* scene = static_cast<CKCinematicScene*>(scenes[i]);
        if ((scene->m_baData & 1u) == 0) continue;
        if (scene->m_unk40 != 0) continue;
        scene->StartEntryTransition();  // 0x0016a5d0
    }
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    service->m_baData = static_cast<uint8_t>((service->m_baData & ~0x10u) | 0x10u);
}
