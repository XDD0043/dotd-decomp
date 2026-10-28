// CKSpline4.cpp - reconstructed original translation unit 0xc5140-0xc6410 (GAME_TOC1, main_toc1), 18 functions, 14 live.
// Primary class: CKSpline4  key 0x2cc  category Logic  size 0x50  vtable 0xb17c30
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc5140  CKSpline4_Delete
//   [ ] 0xc5190  CKSpline4_RecursiveRegistration
//   [ ] 0xc5198  CKSpline4_Save
//   [ ] 0xc51a0  CKSpline4_Construct  [dead]
//   [ ] 0xc5220  CKSpline4_vf50
//   [ ] 0xc5278  CKSpline4_EvaluateSegment_maybe
//   [ ] 0xc53d8  CKSpline4_SetSampleCount_maybe  [dead]
//   [ ] 0xc5400  RegisterCKSpline4Class
//   [ ] 0xc5478  _GLOBAL__I_c5478
//   [ ] 0xc5488  CKSpline4_EvaluateSegmentTangent_maybe
//   [x] 0xc5648  CKSpline4_DeleteArray
//   [ ] 0xc56f0  CKSpline4_GetSegmentLength_maybe  [dead]
//   [ ] 0xc5800  CKSpline4_GetPointAtDistance_maybe
//   [ ] 0xc5ac0  CKSpline4_Construct_2  [dead]
//   [ ] 0xc5b40  CKSpline4_Destroy
//   [x] 0xc5b48  CKSpline4_CreateArray
//   [x] 0xc5c70  CKSpline4_Create
//   [x] 0xc5d20  CKSpline4_Load
//
//   [ ] 0x9a1d98  CKSpline4_vf58  [inline]
//   [ ] 0x9a1da0  CKSpline4_GetClassType  [inline]
//   [ ] 0x9a1da8  CKSpline4_GetClassID  [inline]
//   [ ] 0x9a1db0  CKSpline4_GetLength  [inline]
//   [ ] 0x9a1db8  CKSpline4_IsKindOfClass  [inline]
//   [ ] 0x9a1de0  CKSpline4_DeletingDestructor  [inline]
//   [ ] 0x9a1f08  IKPath_Destructor  [inline]
//   [ ] 0x9a1f20  CKSpline4_Destructor  [inline]
//   [ ] 0x9a2040  IKPath_DeletingDestructor  [inline]
#include "k2000/logic/math/CKSpline4.h"

// 0x000c51a0 CKSpline4_Construct (inlined in 0x000c5c70 CKSpline4_Create).
CKSpline4::CKSpline4() {
    InitPathVector(CtrlPointsList);
    InitPathVector(SegmentLenghtList);
    InitPathVector(SplineSegmentRef);
    InitPathVector(SplineUniformSamples);
    InitPathVector(SplineSegmentTransition);
}

// 0x000c5d20 CKSpline4_Load: no type test.
int32_t CKSpline4::Load(IKFile* file, int32_t /*type*/) {
    m_pPathOwner = nullptr;
    ReadU8(file, &m_ui8NumberOfSegment);
    ReadF32LE(file, &m_fTotalLenght);
    ReadF32LE(file, &m_fPrecision);
    ReadU8(file, &m_bSplineOk);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadPathVector(file, CtrlPointsList, count, true);
    ReadU32LE(file, &count);
    LoadPathVector(file, SegmentLenghtList, count, true);
    ReadU32LE(file, &count);
    LoadPathVector(file, SplineSegmentRef, count, false);
    ReadU32LE(file, &count);
    LoadPathVector(file, SplineUniformSamples, count, true);
    ReadU32LE(file, &count);
    LoadPathVector(file, SplineSegmentTransition, count, true);
    return 1;
}
