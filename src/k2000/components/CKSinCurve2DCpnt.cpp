// CKSinCurve2DCpnt.cpp - reconstructed original translation unit 0x24fba0-0x2501e0 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CKSinCurve2DCpnt  key 0x886  category Component  size 0x28  vtable 0xb20fa8
// Other owners: ShakeEffectState (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24fba0  CKSinCurve2DCpnt_Delete
//   [ ] 0x24fbf0  CKSinCurve2DCpnt_Construct  [dead]
//   [x] 0x24fc28  CKSinCurve2DCpnt_StartState_maybe
//   [x] 0x24fc48  CKSinCurve2DCpnt_ResetState_maybe
//   [ ] 0x24fc68  RegisterCKSinCurve2DCpntClass
//   [ ] 0x24fce0  _GLOBAL__I_24fce0
//   [x] 0x24fcf0  CKSinCurve2DCpnt_DeleteArray
//   [ ] 0x24fd98  CKSinCurve2DCpnt_Construct_2  [dead]
//   [ ] 0x24fdd0  CKSinCurve2DCpnt_Save
//   [ ] 0x24fdd8  CKSinCurve2DCpnt_RecursiveRegistration
//   [ ] 0x24fde0  CKSinCurve2DCpnt_Destructor
//   [ ] 0x24fe58  CKSinCurve2DCpnt_Destructor_2
//   [ ] 0x24fed0  CKSinCurve2DCpnt_Destroy
//   [x] 0x24fed8  CKSinCurve2DCpnt_CreateArray
//   [x] 0x24ffb0  CKSinCurve2DCpnt_Create
//   [x] 0x250010  CKSinCurve2DCpnt_Load
//   [ ] 0x250158  CKSinCurve2DCpnt_DeletingDestructor
//
//   [ ] 0x9ba388  CKSinCurve2DCpnt_IsKindOfClass  [inline]
//   [x] 0x9ba3b0  CKSinCurve2DCpnt_GetClassType  [inline]
//   [x] 0x9ba3b8  CKSinCurve2DCpnt_GetClassID  [inline]
#include "k2000/components/CKSinCurve2DCpnt.h"

#include "k2000/io/IKFile.h"

// 0x0024ffb0 CKSinCurve2DCpnt_Create, the inlined constructor (0x24fbf0 CKSinCurve2DCpnt_Construct is the
// same): the two point lists, in the original's store order.
CKSinCurve2DCpnt::CKSinCurve2DCpnt() {
    m_vFrequencyCurve.m_pBlock = nullptr;
    m_vFrequencyCurve.m_ui32NbElt = 20;
    m_vFrequencyCurve.m_ui32NbUsedElt = 0;
    m_vAmplitudeCurve.m_ui32NbElt = 20;
    m_vAmplitudeCurve.m_ui32NbUsedElt = 0;
    m_vAmplitudeCurve.m_pBlock = nullptr;
}

// 0x00250010 CKSinCurve2DCpnt_Load: the same for every type.
int32_t CKSinCurve2DCpnt::Load(IKFile* file, int32_t /*type*/) {
    ReadF32LE(file, &m_fDuration);
    ReadF32LE(file, &m_fFrequency);
    ReadF32LE(file, &m_fAmplitude);
    CKSinCurve2DCpnt_LoadKeys(&m_vFrequencyCurve, file);
    CKSinCurve2DCpnt_LoadKeys(&m_vAmplitudeCurve, file);
    return 1;
}

// 0x0024fc28 CKSinCurve2DCpnt_StartState_maybe (the store order of the original)
void CKSinCurve2DCpnt::StartState(State* state) const {
    state->m_fPhase = 0.0f;
    state->m_bActive = 1;
    state->m_fTime = 0.0f;
    state->m_fValue = 0.0f;
}

// 0x0024fc48 CKSinCurve2DCpnt_ResetState_maybe
void CKSinCurve2DCpnt::ResetState(State* state) const {
    state->m_fPhase = 0.0f;
    state->m_bActive = 0;
    state->m_fTime = 0.0f;
    state->m_fValue = 0.0f;
}
