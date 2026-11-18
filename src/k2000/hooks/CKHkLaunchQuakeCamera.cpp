// CKHkLaunchQuakeCamera.cpp - reconstructed original translation unit 0x152960-0x1531c8 (GAME_TOC1, main_toc1), 19 functions, 16 live.
// Primary class: CKHkLaunchQuakeCamera  key 0x2202  category Hook  size 0x2c  vtable 0xb1a928
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x152960  CKHkLaunchQuakeCamera_Delete
//   [x] 0x1529b0  CKHkLaunchQuakeCamera_Construct  [dead]
//   [ ] 0x1529f8  CKHkLaunchQuakeCamera_Construct_2  [dead]
//   [x] 0x152a40  CKHkLaunchQuakeCamera_Restart
//   [ ] 0x152a50  RegisterCKHkLaunchQuakeCameraClass
//   [ ] 0x152ac8  _GLOBAL__I_152ac8
//   [x] 0x152ad8  CKHkLaunchQuakeCamera_Update
//   [x] 0x152b50  CKHkLaunchQuakeCamera_RecursiveRegistration
//   [x] 0x152c38  CKHkLaunchQuakeCamera_DeleteArray
//   [x] 0x152cd8  CKHkLaunchQuakeCamera_Start
//   [x] 0x152ce8  CKHkLaunchQuakeCamera_GetInfo  (in the header)
//   [x] 0x152cf0  CKHkLaunchQuakeCamera_MessageProc
//   [x] 0x152d60  CKHkLaunchQuakeCamera_CreateArray
//   [x] 0x152e28  CKHkLaunchQuakeCamera_Create
//   [x] 0x152e90  CKHkLaunchQuakeCamera_Load
//   [ ] 0x152fe0  CKHkLaunchQuakeCamera_Save
//   [x] 0x153140  CKHkLaunchQuakeCamera_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x153160  CKHkLaunchQuakeCamera_DeletingDestructor  (the deleting form of the implicit destructor)
//   [ ] 0x1531a8  CKHkLaunchQuakeCamera_Destructor_2  [dead]
//
//   [ ] 0x992688  CKHkLaunchQuakeCamera_Destroy  [inline]
//   [ ] 0x9a7b60  CKHkLaunchQuakeCamera_IsKindOfClass  [inline]
//   [ ] 0x9a7ba8  CKHkLaunchQuakeCamera_GetClassType  [inline]
//   [ ] 0x9a7bb0  CKHkLaunchQuakeCamera_GetClassID  [inline]
//   [ ] 0x9a7bb8  CKHkLaunchQuakeCamera_Stop  [inline]
//   [ ] 0x9a7bc0  CKHkLaunchQuakeCamera_Pause  [inline]
//   [ ] 0x9a7bc8  CKHkLaunchQuakeCamera_Resume  [inline]
#include "k2000/hooks/CKHkLaunchQuakeCamera.h"

#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"

// 0x00152e90 CKHkLaunchQuakeCamera_Load
int32_t CKHkLaunchQuakeCamera::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk24);
        ReadU8(file, &m_bStartActive);
        IKFile_ReadRef(file, &m_unk20);
    }
    return 1;
}

// 0x00152b50 CKHkLaunchQuakeCamera_RecursiveRegistration (returns 1)
void CKHkLaunchQuakeCamera::RecursiveRegistration(int32_t type) {
    IKHook::RecursiveRegistration(type);  // 0x00019ab8
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_unk24->RecursiveRegistration(0);  // vt+0x24
    m_unk20->RecursiveRegistration(0);
}

// 0x00152cf0 CKHkLaunchQuakeCamera_MessageProc
int32_t CKHkLaunchQuakeCamera::MessageProc(uint16_t message, void* /*data*/) {
    if (message != 0x600) return 1;
    static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->StartQuake(static_cast<CKQuakeCameraLauncher*>(m_unk24));
    return 0;
}

// 0x00152ad8 CKHkLaunchQuakeCamera_Update
void CKHkLaunchQuakeCamera::Update(IKTime* /*frameClock*/) {
    if (m_bActive == 0) return;
    static_cast<CSGMovable*>(m_unk20)->ForceWorldMatrixUpdate();  // vt+0x50
    static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->StartQuake(static_cast<CKQuakeCameraLauncher*>(m_unk24));
}
