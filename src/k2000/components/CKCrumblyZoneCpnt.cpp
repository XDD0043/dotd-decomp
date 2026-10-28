// CKCrumblyZoneCpnt.cpp - reconstructed original translation unit 0x401850-0x402430 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKCrumblyZoneCpnt  key 0xc6  category Component  size 0x10  vtable 0xb25690
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x401850  RegisterCKCrumblyZoneCpntClass
//   [ ] 0x4018c8  _GLOBAL__I_4018c8
//   [ ] 0x4018d8  CKCrumblyZoneCpnt_PostLoad
//   [ ] 0x401900  CKCrumblyZoneCpnt_Save
//   [ ] 0x401928  CKCrumblyZoneCpnt_RecursiveRegistration
//   [ ] 0x401950  CKCrumblyZoneCpnt_Destroy
//   [x] 0x401a18  CKCrumblyZoneCpnt_DeleteArray
//   [ ] 0x401ab8  CKCrumblyZoneCpnt_DeletingDestructor
//   [ ] 0x401b00  CKCrumblyZoneCpnt_Destructor
//   [ ] 0x401b30  CKCrumblyZoneCpnt_DestructBody
//   [ ] 0x401b60  CKCrumblyZoneCpnt_Construct  [dead]
//   [ ] 0x401b98  CKCrumblyZoneCpnt_Construct_2  [dead]
//   [ ] 0x401bd0  CKCrumblyZoneCpnt_QueueInstanceTransform_maybe
//   [ ] 0x401d18  CKCrumblyZoneCpnt_GetInfo
//   [ ] 0x401d20  CKCrumblyZoneCpnt_MessageProc
//   [ ] 0x401e58  CKCrumblyZoneCpnt_vf60
//   [x] 0x4021a0  CKCrumblyZoneCpnt_CreateArray
//   [x] 0x402250  CKCrumblyZoneCpnt_Create
//   [x] 0x4022a8  CKCrumblyZoneCpnt_Load
//
//   [ ] 0x9c1098  CKCrumblyZoneCpnt_IsKindOfClass  [inline]
//   [x] 0x9c10d0  CKCrumblyZoneCpnt_GetClassType  [inline]
//   [x] 0x9c10d8  CKCrumblyZoneCpnt_GetClassID  [inline]
//   [ ] 0x9c10e0  CKCrumblyZoneCpnt_vf50  [inline]
//   [ ] 0x9c10e8  CKCrumblyZoneCpnt_vf54  [inline]
//   [ ] 0x9c10f0  CKCrumblyZoneCpnt_vf58  [inline]
//   [ ] 0x9c1100  CKCrumblyZoneCpnt_vf5C  [inline]
#include "k2000/components/CKCrumblyZoneCpnt.h"

#include "k2000/io/IKFile.h"

// 0x004022a8 CKCrumblyZoneCpnt_Load
int32_t CKCrumblyZoneCpnt::Load(IKFile* file, int32_t type) {
    IKMecaCpnt::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_ui32NbImpEmitters);
        m_apImpulseEmitters = new SImpulsePart[m_ui32NbImpEmitters];  // OperatorNewArray(n * 8 + 4)
        for (uint32_t i = 0; i < m_ui32NbImpEmitters; ++i) IKFile_ReadRef(file, &m_apImpulseEmitters[i].m_pImpulsePart);
    }
    return 1;
}
