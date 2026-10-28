// CKDOFNodeFx.cpp - reconstructed original translation unit 0x1b06d8-0x1b1300 (GAME_TOC1, main_toc1), 26 functions, 23 live.
// Primary class: CKDOFNodeFx  key 0x7fcc  category Logic  size 0x20  vtable 0xb1c7b8
// Other owners: CKElectricArcFxData (5), CKDOFFxData (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1b06d8  CKDOFNodeFx_Delete
//   [ ] 0x1b0728  CKDOFNodeFx_Destroy
//   [ ] 0x1b0730  CKDOFNodeFx_RecursiveRegistration
//   [ ] 0x1b07d8  CKDOFNodeFx_PostLoad
//   [ ] 0x1b0818  CKDOFNodeFx_Start
//   [ ] 0x1b0828  CKDOFNodeFx_Interrupt_maybe
//   [ ] 0x1b0868  CKDOFNodeFx_InterpolateParams_maybe
//   [ ] 0x1b0a40  CKDOFFxData_BeginFadeOut_maybe
//   [ ] 0x1b0a58  CKDOFFxData_SetBlendTime_maybe
//   [ ] 0x1b0a60  KStub_Nop_1b0a60  [dead]
//   [ ] 0x1b0a68  FUN_001b0a68  [dead]
//   [ ] 0x1b0ad0  RegisterCKDOFNodeFxClass
//   [ ] 0x1b0b48  _GLOBAL__I_1b0b48
//   [ ] 0x1b0b58  CKDOFNodeFx_Save
//   [x] 0x1b0b80  CKDOFNodeFx_DeleteArray
//   [x] 0x1b0c20  CKDOFNodeFx_CreateArray
//   [ ] 0x1b0cd0  CKDOFNodeFx_Stop
//   [ ] 0x1b0de8  CKDOFNodeFx_SetDataAndOwner
//   [x] 0x1b0eb8  CKDOFNodeFx_Create
//   [ ] 0x1b0f10  CKDOFNodeFx_Update
//   [x] 0x1b10f8  CKDOFNodeFx_Load
//   [ ] 0x1b11b8  CKElectricArcFxData_GetNodeClassKey
//   [ ] 0x1b11c0  CKElectricArcFxData_EvaluateCurve_maybe  [dead]
//   [ ] 0x1b1260  CKElectricArcFxData_Destroy
//   [ ] 0x1b12b0  CKElectricArcFxData_Save
//   [ ] 0x1b12d8  CKElectricArcFxData_RecursiveRegistration
//
//   [ ] 0x9ab7b0  CKDOFNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ab7e8  CKDOFNodeFx_GetClassType  [inline]
//   [x] 0x9ab7f0  CKDOFNodeFx_GetClassID  [inline]
//   [ ] 0x9ab7f8  CKDOFNodeFx_IsGlobalEffect_maybe  [inline]
//   [ ] 0x9ab800  CKDOFNodeFx_GetFxData  [inline]
//   [ ] 0x9ab808  CKDOFNodeFx_SetFxData  [inline]
//   [ ] 0x9ab810  CKDOFNodeFx_Destruct  [inline]
//   [ ] 0x9ab830  CKDOFNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9ab878  CKElectricArcFxData_IsKindOfClass  [inline]
//   [ ] 0x9ab8b0  CKElectricArcFxData_GetClassType  [inline]
//   [ ] 0x9ab8b8  CKElectricArcFxData_GetClassID  [inline]
//   [ ] 0x9ab8c0  CKElectricArcFxData_DeletingDestructor  [inline]
//   [ ] 0x9ab918  CKElectricArcFxData_Destructor  [inline]
#include "k2000/logic/fx/CKDOFNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x001b10f8 CKDOFNodeFx_Load: the data reference only in level files.
int32_t CKDOFNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pDOFData);
    return 1;
}
