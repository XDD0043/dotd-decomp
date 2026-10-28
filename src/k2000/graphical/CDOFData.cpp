// CDOFData.cpp - reconstructed original translation unit 0xb5c70-0xb6bd8 (GAME_TOC1, main_toc1), 34 functions, 28 live.
// Primary class: CDOFData  key 0x10cd  category Graphical  size 0x14  vtable 0xb17808
// Other owners: CBlurData (8), CHDRData (8), CKSpawnPool (2), RegisterCBlurHDRDOFDataClasses (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb5c70  CDOFData_Delete
//   [ ] 0xb5cc0  CBlurData_Destroy
//   [ ] 0xb5cc8  CBlurData_RecursiveRegistration
//   [ ] 0xb5d28  CBlurData_Save
//   [ ] 0xb5d30  CHDRData_InitDefaults_maybe  [dead]
//   [ ] 0xb5d58  CDOFData_Destroy
//   [ ] 0xb5d60  CDOFData_InitDefaults_maybe  [dead]
//   [ ] 0xb5d88  CDOFData_Save
//   [ ] 0xb5d90  CDOFData_SetParams_2_maybe  [dead]
//   [ ] 0xb5db8  CDOFData_IsInactive_maybe
//   [ ] 0xb5e18  RegisterCBlurHDRDOFDataClasses
//   [ ] 0xb5f00  _GLOBAL__I_b5f00
//   [x] 0xb5f10  CDOFData_DeleteArray
//   [x] 0xb5fb8  CHDRData_DeleteArray
//   [x] 0xb6060  CBlurData_DeleteArray
//   [x] 0xb6108  CDOFData_CreateArray
//   [x] 0xb61a0  CBlurData_CreateArray
//   [x] 0xb6238  CHDRData_Create
//   [ ] 0xb6270  CDOFData_RecursiveRegistration
//   [ ] 0xb62d0  CBlurData_InitDefaults_maybe  [dead]
//   [ ] 0xb6338  CDOFData_SetParams_maybe
//   [x] 0xb6360  CBlurData_Create
//   [x] 0xb6398  CDOFData_Create
//   [x] 0xb63d0  CHDRData_CreateArray
//   [ ] 0xb6468  CHDRData_Save
//   [ ] 0xb6470  CHDRData_RecursiveRegistration
//   [ ] 0xb64d0  CHDRData_Destroy
//   [x] 0xb64d8  CDOFData_Load
//   [x] 0xb6650  CHDRData_Load
//   [x] 0xb6798  CBlurData_Load
//   [x] 0xb6b60  CKSpawnPool_Delete
//   [ ] 0xb6bb0  CKSpawnPool_ResetSlotArrayFields_maybe  [dead]
//   [ ] 0xb6bc8  KStub_Nop_b6bc8  [dead]
//   [ ] 0xb6bd0  KStub_Nop_b6bd0
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

#include "k2000/graphical/CBlurData.h"
#include "k2000/graphical/CHDRData.h"

#include "k2000/io/IKFile.h"

// 0x000b64d8 CDOFData_Load
int32_t CDOFData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk04);
    ReadU32LE(file, &m_unk08);
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
