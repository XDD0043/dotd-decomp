// CDOFData.cpp - reconstructed original translation unit 0xb5c70-0xb6bd8 (GAME_TOC1, main_toc1), 34 functions, 28 live.
// Primary class: CDOFData  key 0x10cd  category Graphical  size 0x14  vtable 0xb17808
// Other owners: CBlurData (8), CHDRData (8), CKSpawnPool (2), RegisterCBlurHDRDOFDataClasses (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb5c70  CDOFData_Delete
//   [x] 0xb5cc0  CBlurData_Destroy  (CBlurData.h)
//   [x] 0xb5cc8  CBlurData_RecursiveRegistration
//   [ ] 0xb5d28  CBlurData_Save
//   [ ] 0xb5d30  CHDRData_InitDefaults_maybe  [dead]
//   [x] 0xb5d58  CDOFData_Destroy  (CDOFData.h)
//   [ ] 0xb5d60  CDOFData_InitDefaults_maybe  [dead]
//   [ ] 0xb5d88  CDOFData_Save
//   [ ] 0xb5d90  CDOFData_SetParams_2_maybe  [dead]
//   [x] 0xb5db8  CDOFData_IsInactive_maybe
//   [ ] 0xb5e18  RegisterCBlurHDRDOFDataClasses
//   [ ] 0xb5f00  _GLOBAL__I_b5f00
//   [x] 0xb5f10  CDOFData_DeleteArray
//   [x] 0xb5fb8  CHDRData_DeleteArray
//   [x] 0xb6060  CBlurData_DeleteArray
//   [x] 0xb6108  CDOFData_CreateArray
//   [x] 0xb61a0  CBlurData_CreateArray
//   [x] 0xb6238  CHDRData_Create
//   [x] 0xb6270  CDOFData_RecursiveRegistration
//   [ ] 0xb62d0  CBlurData_InitDefaults_maybe  [dead]
//   [x] 0xb6338  CDOFData_SetParams_maybe
//   [x] 0xb6360  CBlurData_Create
//   [x] 0xb6398  CDOFData_Create
//   [x] 0xb63d0  CHDRData_CreateArray
//   [ ] 0xb6468  CHDRData_Save
//   [x] 0xb6470  CHDRData_RecursiveRegistration
//   [x] 0xb64d0  CHDRData_Destroy  (CHDRData.h)
//   [x] 0xb64d8  CDOFData_Load
//   [x] 0xb6650  CHDRData_Load
//   [x] 0xb6798  CBlurData_Load
//   [x] 0xb6b60  CKSpawnPool_Delete
//   [ ] 0xb6bb0  CKSpawnPool_ResetSlotArrayFields_maybe  [dead]
//   [ ] 0xb6bc8  KStub_Nop_b6bc8  [dead]
//   [x] 0xb6bd0  KStub_Nop_b6bd0  (CKSpawnPool, see below)
//
//   [ ] 0x9a0d10  CBlurData_GetClassType  [inline]
//   [ ] 0x9a0d18  CBlurData_GetClassID  [inline]
//   [x] 0x9a0d20  CHDRData_GetClassType  [inline]
//   [x] 0x9a0d28  CHDRData_GetClassID  [inline]
//   [ ] 0x9a0d30  CDOFData_IsKindOfClass  [inline]
//   [x] 0x9a0d58  CDOFData_GetClassType  [inline]
//   [x] 0x9a0d60  CDOFData_GetClassID  [inline]
//   [ ] 0x9a0d68  CDOFData_DeletingDestructor  [inline]
//   [ ] 0x9a0db0  CDOFData_Destructor  [inline]
//   [ ] 0x9a0de0  CBlurData_Destructor  [inline]
//   [ ] 0x9a0df8  CHDRData_DeletingDestructor  [inline]
//   [ ] 0x9a0e40  CHDRData_Destructor  [inline]
//   [ ] 0x9a0e70  CHDRData_IsKindOfClass  [inline]
//   [ ] 0x9a0e98  CBlurData_IsKindOfClass  [inline]
//   [ ] 0x9a0eb8  CBlurData_DeletingDestructor  [inline]
#include "k2000/graphical/CDOFData.h"

#include <cstring>

#include "k2000/graphical/CBlurData.h"
#include "k2000/graphical/CHDRData.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x000b64d8 CDOFData_Load
int32_t CDOFData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fFocusDistance);
    ReadF32LE(file, &m_fFocusClamp);
    ReadU32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk10);
    return 1;
}

// 0x000b6650 CHDRData_Load
int32_t CHDRData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fHDRIntensity);
    ReadU32LE(file, &m_eBlendMode);
    ReadRaw(file, m_cHDRColor, 4);
    ReadU8(file, &m_bExtractLuminance);
    return 1;
}

// C2.1 (family scene): CBlurData.

// 0x000b6798 CBlurData_Load
int32_t CBlurData::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadS32LE(file, &m_eBlendMode);
        ReadRaw(file, &m_bActivateMotionSettings, 1);
        ReadF32LE(file, &m_fCenterCoefficient);
        ReadF32LE(file, &m_fSpeedCoefficient);
        ReadF32LE(file, &m_fRotationSpeedCoefficient);
        ReadF32LE(file, &m_fMaxEffectSpeed);
        ReadF32LE(file, &m_fBlurGlobalIntensity);
        ReadF32LE(file, &m_fBlurStartOffset);
        ReadF32LE(file, &m_fBlurIncOffset);
        ReadF32LE(file, &m_fBlurBorderIntensity);
        ReadF32LE(file, &m_fBlurCenterIntensity);
        ReadRaw(file, &m_ui8NbRadialPasses, 1);
        ReadRaw(file, m_cBlurColor, 4);  // not swapped
    }
    return 1;
}

// C2.8 port-all P08.

// 0x000b5cc8 CBlurData_RecursiveRegistration: type 0 registers the object (the saving manager's vt+0x24).
void CBlurData::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x000b6270 CDOFData_RecursiveRegistration
void CDOFData::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x000b6470 CHDRData_RecursiveRegistration
void CHDRData::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

namespace {
// The four words +0x04..+0x10 as the floats lfs reads (m_unk0c / m_unk10 are typed words).
float DofWord(const CDOFData* d, int i) {
    const void* src = i == 0 ? static_cast<const void*>(&d->m_fFocusDistance)
                    : i == 1 ? static_cast<const void*>(&d->m_fFocusClamp)
                    : i == 2 ? static_cast<const void*>(&d->m_unk0c)
                             : static_cast<const void*>(&d->m_unk10);
    float v;
    std::memcpy(&v, src, 4);
    return v;
}
}  // namespace

// 0x000b5db8 CDOFData_IsInactive_maybe: 1 when +0x10 is 0; else 1 only when +0x04, +0x08 and +0x0c are all 0.
bool CDOFData_IsInactive(const IKSerializable* data) {
    const CDOFData* d = static_cast<const CDOFData*>(data);
    if (DofWord(d, 3) == 0.0f) return true;
    return DofWord(d, 0) == 0.0f && DofWord(d, 1) == 0.0f && DofWord(d, 2) == 0.0f;
}

// 0x000b6338 CDOFData_SetParams_maybe: +0x10, +0x04, +0x08, +0x0c copied (lfs / stfs keep the bits).
void CDOFData_SetParams(IKSerializable* data, const IKSerializable* from) {
    CDOFData* d = static_cast<CDOFData*>(data);
    const CDOFData* f = static_cast<const CDOFData*>(from);
    d->m_unk10 = f->m_unk10;
    d->m_fFocusDistance = f->m_fFocusDistance;
    d->m_fFocusClamp = f->m_fFocusClamp;
    d->m_unk0c = f->m_unk0c;
}
