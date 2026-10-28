// CKElectricalGrapple.cpp - reconstructed original translation unit 0x395018-0x396748 (GAME_TOC1, main_toc1), 27 functions, 27 live.
// Primary class: CKElectricalGrapple  key 0xa00c  category Logic  size 0x158  vtable 0xb237e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x395018  CKElectricalGrapple_Delete
//   [ ] 0x395068  CKElectricalGrapple_GetAbilityId
//   [ ] 0x395070  CKElectricalGrapple_ResetRuntime
//   [ ] 0x3950b8  CKElectricalGrapple_GetSoundForEvent_maybe
//   [ ] 0x395230  CKElectricalGrapple_End
//   [ ] 0x3952a8  CKElectricalGrapple_Start
//   [ ] 0x3952d8  CKElectricalGrapple_PostLoad
//   [ ] 0x395300  CKElectricalGrapple_RecursiveRegistration
//   [ ] 0x395328  CKElectricalGrapple_Destroy
//   [ ] 0x395350  CKElectricalGrapple_DeletingDestructor
//   [ ] 0x395398  CKElectricalGrapple_Destructor
//   [ ] 0x3953c8  CKElectricalGrapple_DestructBody
//   [x] 0x3953f8  CKElectricalGrapple_Construct
//   [ ] 0x395430  CKElectricalGrapple_Construct_2
//   [x] 0x395468  CKElectricalGrapple_DeleteArray
//   [ ] 0x395508  RegisterCKElectricalGrappleClass
//   [ ] 0x395590  _GLOBAL__D_395590
//   [ ] 0x3955a0  _GLOBAL__I_3955a0
//   [ ] 0x3955b0  CKElectricalGrapple_Slot80_maybe
//   [ ] 0x395630  CKElectricalGrapple_GrabTarget_maybe
//   [ ] 0x395678  CKElectricalGrapple_Slot84_maybe
//   [ ] 0x395790  CKElectricalGrapple_UpdateGrab_maybe
//   [x] 0x395b88  CKElectricalGrapple_Create
//   [x] 0x395be0  CKElectricalGrapple_CreateArray
//   [x] 0x395c90  CKElectricalGrapple_Load
//   [ ] 0x395ed0  CKElectricalGrapple_Save
//   [ ] 0x396120  CKElectricalGrapple_SetFxActive
//
//   [ ] 0x9bfc08  CKElectricalGrapple_IsKindOfClass  [inline]
//   [ ] 0x9bfc58  CKElectricalGrapple_GetClassType  [inline]
//   [ ] 0x9bfc60  CKElectricalGrapple_GetClassID  [inline]
//   [ ] 0x9bfc68  CKElectricalGrapple_vf94  [inline]
//   [ ] 0x9bfc70  CKElectricalGrapple_StartEmitterFx  [inline]
#include "k2000/logic/CKElectricalGrapple.h"

#include "k2000/io/IKFile.h"

// 0x00395c90 CKElectricalGrapple_Load: CKGrabElement's data, then (level data only) four references.
int32_t CKElectricalGrapple::Load(IKFile* file, int32_t type) {
    CKGrabElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk140[0]);
        IKFile_ReadRef(file, &m_unk140[1]);
        IKFile_ReadRef(file, &m_unk140[2]);
        IKFile_ReadRef(file, &m_unk150);
    }
    return 1;
}
