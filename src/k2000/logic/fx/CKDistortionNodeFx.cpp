// CKDistortionNodeFx.cpp - reconstructed original translation unit 0x1af060-0x1af710 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKDistortionNodeFx  key 0x38cc  category Logic  size 0x2c  vtable 0xb1c6a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1af060  CKDistortionNodeFx_Delete
//   [x] 0x1af0b0  CKDistortionNodeFx_Destroy  (CKDistortionNodeFx.h: empty (IKNodeFx's is not called))
//   [x] 0x1af0b8  CKDistortionNodeFx_RecursiveRegistration
//   [x] 0x1af110  CKDistortionNodeFx_PostLoad
//   [x] 0x1af118  CKDistortionNodeFx_Update
//   [ ] 0x1af1c0  RegisterCKDistortionNodeFxClass
//   [ ] 0x1af238  _GLOBAL__I_1af238
//   [x] 0x1af248  CKDistortionNodeFx_Load
//   [ ] 0x1af270  CKDistortionNodeFx_Save
//   [x] 0x1af298  CKDistortionNodeFx_DeleteArray
//   [x] 0x1af338  CKDistortionNodeFx_Create
//   [x] 0x1af390  CKDistortionNodeFx_Start
//   [x] 0x1af410  CKDistortionNodeFx_SetCenterForOwner_maybe
//   [ ] 0x1af4c0  FUN_001af4c0  [dead]
//   [x] 0x1af558  CKDistortionNodeFx_Stop
//   [x] 0x1af660  CKDistortionNodeFx_CreateArray
//
//   [ ] 0x9ab528  CKDistortionNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ab560  CKDistortionNodeFx_GetClassType  [inline]
//   [x] 0x9ab568  CKDistortionNodeFx_GetClassID  [inline]
//   [x] 0x9ab570  CKDistortionNodeFx_GetFxData  [inline]
//   [x] 0x9ab578  CKDistortionNodeFx_SetFxData  [inline]
//   [ ] 0x9ab660  CKDistortionNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9ab6a8  CKDistortionNodeFx_Destruct  [inline]
#include "k2000/logic/fx/CKDistortionNodeFx.h"

#include "k2000/graphical/CDistortionScreenFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKDistortionFxData.h"
#include "k2000/misc/Engine.h"

namespace {
CDistortionScreenFx* DistortionScreen() {
    return static_cast<CDistortionScreenFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0xc4d));  // vt+0x58
}
}  // namespace

// 0x001af248 CKDistortionNodeFx_Load
int32_t CKDistortionNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}

// 0x001af390 CKDistortionNodeFx_Start
void CKDistortionNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    DistortionScreen()->SetSource(static_cast<CKDistortionFxData*>(m_pFxData)->m_pDistortionData);  // 0x000b2038
}

// 0x001af558 CKDistortionNodeFx_Stop
void CKDistortionNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    CDistortionScreenFx* screen = DistortionScreen();
    if (screen->m_pSource == static_cast<CKDistortionFxData*>(m_pFxData)->m_pDistortionData) screen->Reset();  // 0x000b2008
    Vf60();  // vt+0x60
}

// 0x001af118 CKDistortionNodeFx_Update (vt+0x78)
void CKDistortionNodeFx::Update(IKTime* /*frameClock*/) {
    if (DistortionScreen()->m_pSource != static_cast<CKDistortionFxData*>(m_pFxData)->m_pDistortionData) Stop();  // vt+0x6c
}

// 0x001af410 CKDistortionNodeFx_SetCenterForOwner_maybe
void CKDistortionNodeFx::SetCenterForOwner(const CVector3* center, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_vCenter = {center->x, center->y, center->z};
    DistortionScreen()->m_pCenter = &m_vCenter;  // engine +0x2c (the core manager) vt+0x58, key 0xc4d; its +0x20
}

// 0x001af0b8 CKDistortionNodeFx_RecursiveRegistration
void CKDistortionNodeFx::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
