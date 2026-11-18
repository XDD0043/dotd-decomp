// CKFearEyes.cpp - reconstructed original translation unit 0x39cf88-0x3a0f00 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKFearEyes  key 0x92cc  category Logic  size 0x228  vtable 0xb23920
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x39cf88  CKFearEyes_Delete
//   [x] 0x39cfd8  CKFearEyes_GetAbilityId
//   [x] 0x39cfe0  CKFearEyes_ResetRuntime
//   [x] 0x39d070  CKFearEyes_GetFxSound_maybe
//   [x] 0x39d290  CKFearEyes_End
//   [x] 0x39d328  CKFearEyes_Update
//   [x] 0x39d350  CKFearEyes_Start
//   [x] 0x39d3a0  CKFearEyes_PostLoad
//   [x] 0x39d420  CKFearEyes_RecursiveRegistration  (inherited: CKBreathElement_RecursiveRegistration)
//   [x] 0x39d448  CKFearEyes_Destroy
//   [x] 0x39d488  CKFearEyes_DeletingDestructor  (C++ destructor chain: vtable stores, CKBreathElement_DestructBody)
//   [x] 0x39d4d0  CKFearEyes_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x39d500  CKFearEyes_DestructBody  (C++ destructor chain: vtable stores, CKBreathElement_DestructBody)
//   [x] 0x39d530  CKFearEyes_Construct
//   [x] 0x39d568  CKFearEyes_Construct_2  (the same as 0x39d530 CKFearEyes_Construct)
//   [x] 0x39d5a0  CKFearEyes_DeleteArray
//   [ ] 0x39d640  RegisterCKFearEyesClass
//   [ ] 0x39d6c8  _GLOBAL__D_39d6c8
//   [ ] 0x39d6d8  _GLOBAL__I_39d6d8
//   [x] 0x39d6e8  CKFearEyes_GetEmitterPosition
//   [x] 0x39d7f0  CKFearEyes_StopBreathing
//   [x] 0x39d8c8  CKFearEyes_CreateArray
//   [x] 0x39d978  CKFearEyes_Create
//   [x] 0x39d9d0  CKFearEyes_Load
//   [ ] 0x39e688  CKFearEyes_Save
//   [x] 0x39f228  CKFearEyes_UpdateBeamAndImpact_maybe
//   [x] 0x39ff48  CKFearEyes_UpdateFx
//   [x] 0x3a0518  CKFearEyes_SetFxActive
//
//   [x] 0x9bfd28  CKFearEyes_IsKindOfClass  [inline]
//   [ ] 0x9bfd78  CKFearEyes_GetClassType  [inline]
//   [ ] 0x9bfd80  CKFearEyes_GetClassID  [inline]
//   [x] 0x9bfd88  CKFearEyes_StartEmitterFx  [inline]
//
// The bodies are CKBeamBreath's (k2000/logic/CKBeamBreath.cpp, DOTD): this unit and its twin are the same code.
#include "k2000/logic/CKFearEyes.h"

#include "Renderware/rwcore/RwMatrix.h"

// 0x0039d448 CKFearEyes_Destroy (RwMatrixDestroy_Thunk). DOTD: only a matrix that was created (the original destroys
// whatever the word holds; ResetRuntime of the level data creates it).
void CKFearEyes::Destroy() {
    CKBreathElement::Destroy();
    if (m_unk21c != nullptr) RwMatrixDestroy(m_unk21c);
}
