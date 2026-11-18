// CSpawnPoolRenderParam.cpp - reconstructed original translation unit 0xb9fd0-0xba598 (GAME_TOC1, main_toc1), 17 functions, 13 live.
// Primary class: CSpawnPoolRenderParam  key 0xe4d  category Graphical  size 0x14  vtable 0xb17a40
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb9fd0  CSpawnPoolRenderParam_Delete
//   [ ] 0xba020  CSpawnPoolRenderParam_Construct  [dead]
//   [ ] 0xba030  CSpawnPoolRenderParam_Construct_2  [dead]
//   [ ] 0xba040  CSpawnPoolRenderParam_UpdateInvRange_maybe  [dead]
//   [ ] 0xba060  RegisterCSpawnPoolRenderParamClass
//   [ ] 0xba0d8  _GLOBAL__I_ba0d8
//   [x] 0xba0e8  CSpawnPoolRenderParam_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0xba100  CSpawnPoolRenderParam_DeleteArray
//   [x] 0xba1a8  CSpawnPoolRenderParam_CreateArray
//   [x] 0xba240  CSpawnPoolRenderParam_Create
//   [x] 0xba278  CSpawnPoolRenderParam_RecursiveRegistration  (CSpawnPoolRenderParam::RecursiveRegistration)
//   [x] 0xba2d8  CSpawnPoolRenderParam_Destroy  (Destroy: empty, the default slot)
//   [x] 0xba2e0  CSpawnPoolRenderParam_Load
//   [ ] 0xba408  CSpawnPoolRenderParam_Save
//   [x] 0xba518  CSpawnPoolRenderParam_PostLoad
//   [ ] 0xba540  CSpawnPoolRenderParam_Destructor_2  [dead]
//   [x] 0xba558  CSpawnPoolRenderParam_DeletingDestructor  (the destructor; delete)
//
//   [ ] 0x9a10a8  CSpawnPoolRenderParam_GetClassType  [inline]
//   [ ] 0x9a10b0  CSpawnPoolRenderParam_GetClassID  [inline]
//   [ ] 0x9a10b8  CSpawnPoolRenderParam_IsKindOfClass  [inline]
#include "k2000/graphical/render/CSpawnPoolRenderParam.h"

#include "k2000/io/IKFile.h"

// 0x000ba2e0 CSpawnPoolRenderParam_Load
int32_t CSpawnPoolRenderParam::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fNear);
        ReadF32LE(file, &m_fFar);
        ReadS32LE(file, &m_unk04);
    }
    return 1;
}

// 0x000ba518 CSpawnPoolRenderParam_PostLoad: the inverse of the band's width (fsubs, fdivs; no type test).
int32_t CSpawnPoolRenderParam::PostLoad(int32_t /*type*/) {
    m_fInvRange = 1.0f / (m_fFar - m_fNear);
    return 1;
}

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x000ba278 CSpawnPoolRenderParam_RecursiveRegistration
void CSpawnPoolRenderParam::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
