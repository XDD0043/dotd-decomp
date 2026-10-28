// CKCrumblyZoneElement.cpp - reconstructed original translation unit 0x402430-0x403720 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKCrumblyZoneElement  key 0xa30c  category Logic  size 0x30  vtable 0xb25700
// Other owners: CrumblyZonePiece (11), CKHkCrumblyZoneMultiState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x402430  CKCrumblyZoneElement_Delete
//   [x] 0x402480  CKCrumblyZoneElement_Construct  [dead]
//   [ ] 0x402490  CKCrumblyZoneElement_Construct_2  [dead]
//   [ ] 0x4024a0  CrumblyZonePiece_ReparentNodes_maybe
//   [ ] 0x402608  RegisterCKCrumblyZoneElementClass
//   [ ] 0x402680  _GLOBAL__I_402680
//   [ ] 0x402690  CrumblyZonePiece_SetFxPosition
//   [ ] 0x4026d0  CrumblyZonePiece_ResetMeshMatrixB_maybe
//   [ ] 0x402710  CrumblyZonePiece_ResetMeshMatrixA_maybe
//   [ ] 0x402750  CrumblyZonePiece_TransformMeshMatrixB_maybe
//   [ ] 0x402870  CrumblyZonePiece_TransformMeshMatrixA_maybe
//   [ ] 0x402990  CKHkCrumblyZoneMultiState_AdvancePieceAnim_maybe
//   [x] 0x4029d8  CKCrumblyZoneElement_DeleteArray
//   [ ] 0x402a80  CrumblyZonePiece_Activate_maybe
//   [ ] 0x402d68  CrumblyZonePiece_Deactivate_maybe
//   [ ] 0x402e48  CrumblyZonePiece_CaptureMeshMatrixA_maybe  [dead]
//   [x] 0x402f20  CKCrumblyZoneElement_CreateArray
//   [x] 0x402fb8  CKCrumblyZoneElement_Create
//   [ ] 0x402ff0  CrumblyZonePiece_CaptureMeshMatrixB_maybe  [dead]
//   [ ] 0x4030c8  CKCrumblyZoneElement_Save
//   [ ] 0x4030d0  CKCrumblyZoneElement_RecursiveRegistration
//   [ ] 0x4030d8  CKCrumblyZoneElement_PostLoad
//   [ ] 0x4030f8  CKCrumblyZoneElement_Destroy
//   [ ] 0x403138  CrumblyZonePiece_ApplyWorldMatrix_maybe
//   [x] 0x403358  CKCrumblyZoneElement_Load
//   [ ] 0x4036b0  CKCrumblyZoneElement_Destructor
//   [ ] 0x4036c8  CKCrumblyZoneElement_Destructor_2  [dead]
//   [ ] 0x4036e0  CKCrumblyZoneElement_DeletingDestructor
//
//   [ ] 0x9c1108  CKCrumblyZoneElement_GetClassType  [inline]
//   [ ] 0x9c1110  CKCrumblyZoneElement_GetClassID  [inline]
//   [ ] 0x9c1118  CKCrumblyZoneElement_IsKindOfClass  [inline]
#include "k2000/logic/CKCrumblyZoneElement.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// 0x00403358 CKCrumblyZoneElement_Load
int32_t CKCrumblyZoneElement::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pZone);
    IKFile_ReadRef(file, &m_pNode);
    IKFile_ReadRef(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    ReadU32LE(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadRef(file, &m_unk20);
    m_pMatrix28 = RwMatrixCreate_Thunk();
    m_pMatrix2c = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pMatrix28, file);
    CMatrix34_LoadMatrix(m_pMatrix2c, file);
    return 1;
}
