// CKPurpleRay.cpp - reconstructed original translation unit 0x3c5af0-0x3c9a68 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKPurpleRay  key 0x930c  category Logic  size 0x228  vtable 0xb23f08
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3c5af0  CKPurpleRay_Delete
//   [x] 0x3c5b40  CKPurpleRay_GetAbilityId
//   [x] 0x3c5b48  CKPurpleRay_ResetRuntime
//   [x] 0x3c5bd8  CKPurpleRay_GetFxSound_maybe
//   [x] 0x3c5df8  CKPurpleRay_End
//   [x] 0x3c5e90  CKPurpleRay_Update
//   [x] 0x3c5eb8  CKPurpleRay_Start
//   [x] 0x3c5f08  CKPurpleRay_PostLoad
//   [x] 0x3c5f88  CKPurpleRay_RecursiveRegistration  (inherited: CKBreathElement_RecursiveRegistration)
//   [x] 0x3c5fb0  CKPurpleRay_Destroy
//   [x] 0x3c5ff0  CKPurpleRay_DeletingDestructor  (the destructor; delete)
//   [x] 0x3c6038  CKPurpleRay_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3c6068  CKPurpleRay_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3c6098  CKPurpleRay_Construct
//   [x] 0x3c60d0  CKPurpleRay_Construct_2  (the same as 0x3c6098 CKPurpleRay_Construct)
//   [x] 0x3c6108  CKPurpleRay_DeleteArray
//   [ ] 0x3c61a8  RegisterCKPurpleRayClass
//   [ ] 0x3c6230  _GLOBAL__D_3c6230
//   [ ] 0x3c6240  _GLOBAL__I_3c6240
//   [x] 0x3c6250  CKPurpleRay_GetEmitterPosition
//   [x] 0x3c6358  CKPurpleRay_StopBreathing
//   [x] 0x3c6430  CKPurpleRay_CreateArray
//   [x] 0x3c64e0  CKPurpleRay_Create
//   [x] 0x3c6538  CKPurpleRay_Load
//   [ ] 0x3c71f0  CKPurpleRay_Save
//   [x] 0x3c7d90  CKPurpleRay_UpdateBeamAndImpact_maybe
//   [x] 0x3c8ab0  CKPurpleRay_UpdateFx
//   [x] 0x3c9080  CKPurpleRay_SetFxActive
//
//   [x] 0x9c0238  CKPurpleRay_IsKindOfClass  [inline]
//   [ ] 0x9c0288  CKPurpleRay_GetClassType  [inline]
//   [ ] 0x9c0290  CKPurpleRay_GetClassID  [inline]
//   [x] 0x9c0298  CKPurpleRay_StartEmitterFx  [inline]
//
// The bodies are CKBeamBreath's (k2000/logic/CKBeamBreath.cpp, DOTD): this unit and its twin are the same code.
#include "k2000/logic/physics/CKPurpleRay.h"

#include "Renderware/rwcore/RwMatrix.h"

// 0x003c5fb0 CKPurpleRay_Destroy (RwMatrixDestroy_Thunk). DOTD: only a matrix that was created, as CKFearEyes_Destroy
// (its twin) does.
void CKPurpleRay::Destroy() {
    CKBreathElement::Destroy();
    if (m_pLocalMatrix != nullptr) RwMatrixDestroy(m_pLocalMatrix);
}
