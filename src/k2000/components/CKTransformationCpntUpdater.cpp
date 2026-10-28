// CKTransformationCpntUpdater.cpp - reconstructed original translation unit 0x2520c0-0x252a40 (GAME_TOC1, main_toc1), 20 functions, 13 live.
// Primary class: CKTransformationCpntUpdater  key 0x1446  category Component  size 0x10  vtable 0xb21108
// Other owners: Mat4 (1), Node (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2520c0  CKTransformationCpntUpdater_GetCpnt_maybe  [dead]
//   [ ] 0x2520c8  RegisterCKTransformationCpntUpdaterClass
//   [ ] 0x252140  _GLOBAL__I_252140
//   [ ] 0x252150  Mat4_ApplyLocalTRSDelta_maybe
//   [ ] 0x2524a8  Node_ApplyTRSDeltaToLocalMatrix_maybe
//   [ ] 0x2525b8  CKTransformationCpntUpdater_EvaluateRunning_maybe  [dead]
//   [ ] 0x252670  CKTransformationCpntUpdater_Resume_maybe  [dead]
//   [ ] 0x2526a8  CKTransformationCpntUpdater_Pause_maybe  [dead]
//   [ ] 0x2526e0  CKTransformationCpntUpdater_Stop_maybe  [dead]
//   [ ] 0x252718  CKTransformationCpntUpdater_Restart_maybe
//   [x] 0x252750  CKTransformationCpntUpdater_DeleteArray
//   [x] 0x2527f0  CKTransformationCpntUpdater_Create
//   [ ] 0x252828  CKTransformationCpntUpdater_SetTransformationCpnt_maybe  [dead]
//   [x] 0x252830  CKTransformationCpntUpdater_CreateArray
//   [ ] 0x2528c0  CKTransformationCpntUpdater_Save
//   [x] 0x2528c8  CKTransformationCpntUpdater_Load
//   [x] 0x252958  CKTransformationCpntUpdater_PostLoad
//   [ ] 0x252978  CKTransformationCpntUpdater_RecursiveRegistration
//   [ ] 0x252980  CKTransformationCpntUpdater_Destroy
//   [ ] 0x252988  CKTransformationCpntUpdater_Evaluate_maybe  [dead]
//
//   [ ] 0x9ba620  CKTransformationCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9ba648  CKTransformationCpntUpdater_GetClassType  [inline]
//   [x] 0x9ba650  CKTransformationCpntUpdater_GetClassID  [inline]
//   [ ] 0x9ba658  CKTransformationCpntUpdater_DeletingDestructor  [inline]
//   [ ] 0x9ba6a0  CKTransformationCpntUpdater_Destructor  [inline]
#include "k2000/components/CKTransformationCpntUpdater.h"

#include "k2000/io/IKFile.h"

// 0x002528c8 CKTransformationCpntUpdater_Load
int32_t CKTransformationCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pTransformation);
    return 1;
}

// 0x00252958 CKTransformationCpntUpdater_PostLoad: level type only.
int32_t CKTransformationCpntUpdater::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_unk08 = 0;
    m_unk0c = 0.0f;
    return 1;
}
