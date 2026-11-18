// CKLensFlareNodeFx.cpp - reconstructed original translation unit: 0x1c6758-0x1c7128 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKLensFlareNodeFx  key 0x370c  category Logic  size 0x18  vtable 0xb1d1a8
// Other owners: CKLightningObjectFxData (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c6758  CKLensFlareNodeFx_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1c67a8  CKLensFlareNodeFx_Destroy  (empty: CKLensFlareNodeFx.h)
//   [x] 0x1c67b0  CKLensFlareNodeFx_RecursiveRegistration
//   [x] 0x1c6808  CKLensFlareNodeFx_PostLoad  (CKLensFlareNodeFx.h)
//   [x] 0x1c6810  CKLensFlareNodeFx_Update
//   [ ] 0x1c68b8  RegisterCKLensFlareNodeFxClass
//   [ ] 0x1c6930  _GLOBAL__I_1c6930
//   [x] 0x1c6940  CKLensFlareNodeFx_Load
//   [ ] 0x1c6968  CKLensFlareNodeFx_Save
//   [x] 0x1c6990  CKLensFlareNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1c6a38  CKLensFlareNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1c6af0  CKLensFlareNodeFx_Start
//   [x] 0x1c6b88  CKLensFlareNodeFx_Stop
//   [x] 0x1c6c90  CKLensFlareNodeFx_Create  (DOTD_DECLARE_FACTORIES; the constructor in CKLensFlareNodeFx.h)
//   [x] 0x1c6ce8  CKLightningObjectFxData_GetNodeClassKey  (CKLightningObjectFxData.h)
//   [x] 0x1c6cf0  CKLightningObjectFxData_PostLoad  (IKFxData's: the default)
//   [x] 0x1c6d18  CKLightningObjectFxData_RecursiveRegistration  (IKFxData's: the default)
//   [x] 0x1c6d40  CKLightningObjectFxData_Destroy  (empty: CKLightningObjectFxData.h)
//   [x] 0x1c6d48  CKLightningObjectFxData_Load
//   [ ] 0x1c6f50  CKLightningObjectFxData_Save
//
//   [x] 0x9ac888  CKLensFlareNodeFx_IsKindOfClass  [inline]  (CKLensFlareNodeFx.h)
//   [x] 0x9ac8c0  CKLensFlareNodeFx_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac8c8  CKLensFlareNodeFx_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac8d0  CKLensFlareNodeFx_GetFxData  [inline]
//   [x] 0x9ac8d8  CKLensFlareNodeFx_SetFxData  [inline]
//   [x] 0x9ac8e0  CKLensFlareNodeFx_Destruct  [inline]  (CKLensFlareNodeFx.h)
//   [x] 0x9ac900  CKLensFlareNodeFx_DeletingDestruct  [inline]  (CKLensFlareNodeFx.h)
//   [x] 0x9ac948  CKLightningObjectFxData_IsKindOfClass  [inline]  (CKLightningObjectFxData.h)
//   [x] 0x9ac980  CKLightningObjectFxData_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac988  CKLightningObjectFxData_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac990  CKLightningObjectFxData_Destructor  [inline]  (CKLightningObjectFxData.h)
//   [x] 0x9ac9d0  CKLightningObjectFxData_DeletingDestructor  [inline]  (CKLightningObjectFxData.h)
#include "k2000/logic/fx/CKLensFlareNodeFx.h"

#include "k2000/logic/CKCoreManager.h"
#include "k2000/graphical/fx/CLensFlareFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKLensFlareFxData.h"
#include "k2000/logic/fx/CKLightningObjectFxData.h"
#include "k2000/misc/Engine.h"

namespace {
// The level's lens flare screen effect (core manager vt+0x58 with key 0x1b4d).
CLensFlareFx* LevelLensFlare() {
    return static_cast<CLensFlareFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x1b4d));
}
}  // namespace

// 0x001c6940 CKLensFlareNodeFx_Load
int32_t CKLensFlareNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}

// 0x001c67b0 CKLensFlareNodeFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner) only.
void CKLensFlareNodeFx::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

IKFxData* CKLensFlareNodeFx::GetFxData() { return m_pData; }  // 0x009ac8d0
void CKLensFlareNodeFx::SetFxData(IKFxData* data) { m_pData = static_cast<CKLensFlareFxData*>(data); }  // 0x009ac8d8

// 0x001c6af0 CKLensFlareNodeFx_Start: running; the level's flare enabled and showing this data's flare data.
void CKLensFlareNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    CLensFlareFx* flare = LevelLensFlare();
    flare->SetEnabled(1);
    flare->m_pData = m_pData->m_pFlareData;
}

// 0x001c6b88 CKLensFlareNodeFx_Stop: stopped; the level's flare disabled when it still shows this data's flare data;
// the node hidden (vt+0x60) either way.
void CKLensFlareNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    CLensFlareFx* flare = LevelLensFlare();
    if (flare->m_pData != m_pData->m_pFlareData) {
        Vf60();
        return;
    }
    flare->SetEnabled(0);
    Vf60();
}

// 0x001c6810 CKLensFlareNodeFx_Update: stops (vt+0x6c) once the level's flare shows other flare data.
void CKLensFlareNodeFx::Update(IKTime* /*frameClock*/) {
    if (LevelLensFlare()->m_pData != m_pData->m_pFlareData) Stop();
}

// 0x001c6d48 CKLightningObjectFxData_Load: level files only: IKFxData's, three byte-swapped words (+0x0c, +0x10, +0x14),
// a byte ORed into the flags (bit 0 cleared first), a word (+0x08) and four raw bytes (+0x3c).
int32_t CKLightningObjectFxData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFxData::Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    uint8_t flag = 0;
    ReadU8(file, &flag);
    m_baFlags44 = static_cast<uint8_t>((m_baFlags44 & 0xfe) | flag);
    ReadU32LE(file, &m_unk08);
    ReadRaw(file, m_Color, 4);
    return 1;
}
