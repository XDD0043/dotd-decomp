// CKGrpLevelManager.cpp - reconstructed original translation unit 0x5a8260-0x5a8910 (GAME_TOC2, main_toc2), 17 functions, 13 live.
// Primary owner: CKGrpLevelManager (not a registered class)
// Other owners: RegisterCKGrpLevelManagerClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5a8260  CKGrpLevelManager_Destroy  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x5a82b0  CKGrpLevelManager_Construct  [dead]
//   [ ] 0x5a8328  CKGrpLevelManager_Construct_2  [dead]
//   [x] 0x5a83a0  CKGrpLevelManager_ClearReferences  (Destroy, header)
//   [x] 0x5a8400  CKGrpLevelManager_vfB8  (header)
//   [ ] 0x5a8408  CKGrpLevelManager_FindFirstChildWithClassKey3A82_maybe  [dead]
//   [x] 0x5a8500  CKGrpLevelManager_Load
//   [ ] 0x5a8528  CKGrpLevelManager_Save
//   [x] 0x5a8550  CKGrpLevelManager_LevelReset  (RecursiveRegistration, header)
//   [ ] 0x5a85d0  RegisterCKGrpLevelManagerClass
//   [ ] 0x5a8648  _GLOBAL__I_5a8648
//   [x] 0x5a8658  CKGrpLevelManager_DestroyArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x5a86f8  CKGrpLevelManager_CreateArray
//   [x] 0x5a87d8  CKGrpLevelManager_Create
//   [x] 0x5a8868  CKGrpLevelManager_Destructor  (vtables only (implicit))
//   [x] 0x5a8890  CKGrpLevelManager_DeletingDestructor  (vtables only (implicit))
//   [ ] 0x5a88e8  CKGrpLevelManager_Destructor_2  [dead]
//
//   [x] 0x9cbc98  CKGrpLevelManager_GetClassGroup  [inline]
//   [x] 0x9cbca0  CKGrpLevelManager_GetClassId  [inline]
//   [ ] 0x9cbca8  CKGrpLevelManager_vfCC  [inline]
//   [ ] 0x9cbcb0  CKGrpLevelManager_IsKindOf  [inline]
//   [ ] 0x9cbd10  KBase1744_vf0  [inline]
//   [ ] 0x9cbd30  KBase1744_DeletingDestructor  [inline]
#include "k2000/ui/CKGrpLevelManager.h"

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x005a8500 CKGrpLevelManager_Load: GroupBasicLoad only (through its TOC bridge).
int32_t CKGrpLevelManager::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}

// 0x005a8550 CKGrpLevelManager_RecursiveRegistration (IKGroup_LevelReset through its TOC bridge).
void CKGrpLevelManager::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKGroup<IKHook>::RecursiveRegistration(type);
}
