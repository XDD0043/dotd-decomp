// CSparkNodeFx.cpp - reconstructed original translation unit 0xe79f8-0xea630 (GAME_TOC1, main_toc1), 30 functions, 24 live.
// Primary class: CSparkNodeFx  key 0x70b  category SceneNode  size 0x5c  vtable 0xb18ba8
// Other owners: CTrailNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xe79f8  CSparkNodeFx_Delete
//   [ ] 0xe7a48  RegisterCSparkNodeFxClass
//   [ ] 0xe7ac0  _GLOBAL__I_e7ac0
//   [ ] 0xe7ad0  CSparkNodeFx_GetInfo
//   [ ] 0xe7b20  CSparkNodeFx_SetParams_maybe
//   [ ] 0xe7b60  CSparkNodeFx_AllocSparkNodes_maybe  [dead]
//   [ ] 0xe7c90  CSparkNodeFx_ReleaseAllSparks_maybe
//   [ ] 0xe7df0  CSparkNodeFx_Save
//   [ ] 0xe7e18  CSparkNodeFx_RecursiveRegistration
//   [x] 0xe7e40  CSparkNodeFx_DeleteArray
//   [ ] 0xe7ee0  CSparkNodeFx_BaseDestructor
//   [x] 0xe7f20  CSparkNodeFx_Construct  [dead]
//   [ ] 0xe7f88  CSparkNodeFx_Destroy
//   [x] 0xe8070  CSparkNodeFx_Load
//   [ ] 0xe8208  CSparkNodeFx_Construct_2  [dead]
//   [x] 0xe8270  CSparkNodeFx_CreateArray
//   [x] 0xe8388  CSparkNodeFx_Create
//   [ ] 0xe8408  CSparkNodeFx_DeletingDestructor
//   [ ] 0xe8460  CSparkNodeFx_Destructor
//   [ ] 0xe84a0  CSparkNodeFx_InitSpark_maybe
//   [ ] 0xe9128  CSparkNodeFx_SpawnInitialSparks_maybe  [dead]
//   [ ] 0xe9250  CSparkNodeFx_InitSparks_maybe
//   [ ] 0xe9410  CSparkNodeFx_PostLoad
//   [ ] 0xe96b0  CSparkNodeFx_UpdateSpark_maybe
//   [ ] 0xe9c70  CSparkNodeFx_UpdateSparks_maybe
//   [ ] 0xea040  CSparkNodeFx_MessageProc
//   [ ] 0xea200  CSparkNodeFx_Enqueue
//   [ ] 0xea460  CTrailNodeFx_Delete
//   [ ] 0xea4b0  FUN_000ea4b0  [dead]
//   [ ] 0xea590  FUN_000ea590  [dead]
//
//   [ ] 0x9a55b8  CSparkNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a5618  CSparkNodeFx_GetClassType  [inline]
//   [ ] 0x9a5620  CSparkNodeFx_GetClassID  [inline]
#include "k2000/scenegraph/CSparkNodeFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CKSparkParam.h"

// 0x000e7f20 CSparkNodeFx_Construct
CSparkNodeFx::CSparkNodeFx() {
    m_pSparks = nullptr;
    m_pFreeSparks = nullptr;
    m_unk38 = 0;
    m_pSparkParam = nullptr;
    m_pGeometry = nullptr;
    m_pMatrix = nullptr;
}

// 0x000e8070 CSparkNodeFx_Load
int32_t CSparkNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_i32NbSparks);
    ReadRaw(file, &m_unk40, 1);
    ReadRaw(file, &m_unk4c, 1);
    IKFile_ReadRef(file, &m_pSparkParam);
    return 1;
}
