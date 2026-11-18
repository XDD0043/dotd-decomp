// CKLockUnlockCinematicBloc.cpp - reconstructed original translation unit 0x17e7f0-0x17f458 (GAME_TOC1, main_toc1), 20 functions, 19 live.
// Primary class: CKLockUnlockCinematicBloc  key 0x908  category CinematicNode  size 0x38  vtable 0xb1b4e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x17e7f0  CKLockUnlockCinematicBloc_Delete
//   [x] 0x17e840  CKLockUnlockCinematicBloc_Abort
//   [ ] 0x17e850  RegisterCKLockUnlockCinematicBlocClass
//   [ ] 0x17e8c8  _GLOBAL__I_17e8c8
//   [x] 0x17e8d8  CKLockUnlockCinematicBloc_Complete
//   [x] 0x17eab0  CKLockUnlockCinematicBloc_Load
//   [ ] 0x17ead8  CKLockUnlockCinematicBloc_Save
//   [x] 0x17eb00  CKLockUnlockCinematicBloc_RecursiveRegistration  (inherited: IKCinematicBloc_LevelReset, a tail call)
//   [x] 0x17eb28  CKLockUnlockCinematicBloc_Construct
//   [x] 0x17eb60  CKLockUnlockCinematicBloc_Construct_2  [dead: no pointer to its descriptor 0xb64fe0, no call]  (the constructor: the same stores as 0x17eb28 CKLockUnlockCinematicBloc_Construct)
//   [x] 0x17eb98  CKLockUnlockCinematicBloc_DeleteArray
//   [x] 0x17ec40  CKLockUnlockCinematicBloc_Update
//   [x] 0x17ee40  CKLockUnlockCinematicBloc_Destroy  (empty: the default)
//   [x] 0x17ee48  CKLockUnlockCinematicBloc_Start
//   [x] 0x17f0e0  CKLockUnlockCinematicBloc_Create
//   [x] 0x17f138  CKLockUnlockCinematicBloc_CreateArray
//   [x] 0x17f1f0  CKLockUnlockCinematicBloc_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x17f238  CKLockUnlockCinematicBloc_Stop
//   [ ] 0x17f418  CKLockUnlockCinematicBloc_Destructor_2  [dead]
//   [x] 0x17f438  CKLockUnlockCinematicBloc_Destructor  (C++ destructor chain: vtable stores only)
//
//   [ ] 0x9a9988  CKLockUnlockCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a99c0  CKLockUnlockCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a99c8  CKLockUnlockCinematicBloc_GetClassID  [inline]
#include "k2000/cinematics/CKLockUnlockCinematicBloc.h"

#include "k2000/hooks/IKHook.h"
#include "k2000/hooks/IKLife.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/misc/Engine.h"

// 0x0017eab0 CKLockUnlockCinematicBloc_Load
int32_t CKLockUnlockCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    return 1;
}

// 0x0017ee48 CKLockUnlockCinematicBloc_Start
void CKLockUnlockCinematicBloc::Start() { StartCommon(); }

// 0x0017e8d8 CKLockUnlockCinematicBloc_Complete
void CKLockUnlockCinematicBloc::Complete() { CompleteBloc(); }

// 0x0017ec40 CKLockUnlockCinematicBloc_Update
void CKLockUnlockCinematicBloc::Update(IKTime* /*time*/) {
    if (CheckSekensStop() == 0) return;  // 0x0018e9e0
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    if (data != nullptr && data->m_pHook != nullptr) {
        IKHook* hook = static_cast<IKHook*>(data->m_pHook);
        IKLife* object = hook->m_pHookLife != nullptr ? static_cast<IKLife*>(hook->m_pHookLife) : hook;
        const uint32_t locked = (object->m_bitArray >> 1) & 1u;
        SetObjectLocked(g_pEngine->m_coreManager, object, locked ^ 1u);  // 0x0001c250
        if (locked == 0) {
            data->m_pShadowData = hook->GetComponent(0x486);  // vt+0xb0
        } else {
            for (IKCinematicElement* e = m_pRelatedScene->m_pActiveNodes; e != nullptr; e = e->m_pNext) {
                if (e == this || e->IsKindOfClass(0x84c) == 0) continue;
                IKCinematicBloc* bloc = static_cast<IKCinematicBloc*>(e);
                if (bloc->IsExclusiveOnActor() == 0 || bloc->m_pElementData == nullptr) continue;  // vt+0x84
                if (static_cast<CKCinematicSceneData*>(bloc->m_pElementData)->m_pHook != data->m_pHook) continue;
                bloc->Stop();  // vt+0x6c
            }
        }
    }
    Complete();  // vt+0x64
}

// 0x0017f238 CKLockUnlockCinematicBloc_Stop
void CKLockUnlockCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x0017e840 CKLockUnlockCinematicBloc_Abort
void CKLockUnlockCinematicBloc::Abort() { m_DataFlags &= 0xfffffffeu; }
