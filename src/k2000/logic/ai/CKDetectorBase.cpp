// CKDetectorBase.cpp - reconstructed original translation unit 0x1a8608-0x1a9890 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKDetectorBase  key 0x270c  category Logic  size 0x14  vtable 0xb1c3a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a8608  CKDetectorBase_Delete
//   [ ] 0x1a8658  CKDetectorBase_SetGameState
//   [ ] 0x1a86f8  RegisterCKDetectorBaseClass
//   [ ] 0x1a8770  _GLOBAL__I_1a8770
//   [x] 0x1a8780  CKDetectorBase_DeleteArray
//   [x] 0x1a8828  CKDetectorBase_CreateArray
//   [x] 0x1a88c0  CKDetectorBase_Create
//   [ ] 0x1a88f8  CKDetectorBase_SetDefaultState
//   [x] 0x1a8948  CKDetectorBase_SetEnabled_maybe
//   [ ] 0x1a8978  CKDetectorBase_GetInfo
//   [ ] 0x1a89d0  CKDetectorBase_Save
//   [ ] 0x1a89d8  CKDetectorBase_MessageProc
//   [ ] 0x1a8a68  CKDetectorBase_RecursiveRegistration
//   [ ] 0x1a8a70  CKDetectorBase_PostLoad
//   [ ] 0x1a8a78  CKDetectorBase_Destroy
//   [x] 0x1a8a88  CKDetectorBase_Load
//   [ ] 0x1a8c70  CKDetectorBase_CheckDetection_maybe
//
//   [ ] 0x9aaf38  CKDetectorBase_GetClassType  [inline]
//   [ ] 0x9aaf40  CKDetectorBase_GetClassID  [inline]
//   [ ] 0x9aaf48  CKDetectorBase_GetTriggerProp2  [inline]
//   [ ] 0x9aaf58  CKDetectorBase_vf5C  [inline]
//   [ ] 0x9aaf60  CKDetectorBase_Destructor  [inline]
//   [ ] 0x9aaf78  CKDetectorBase_vf54  [inline]
//   [ ] 0x9aafa8  CKDetectorBase_IsKindOfClass  [inline]
//   [ ] 0x9aafc8  CKDetectorBase_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKDetectorBase.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKDetectedMovable.h"

// 0x001a8948 CKDetectorBase_SetEnabled_maybe: bit 4 = enabled (the argument shifted in, as the original's
// rlwinm/or); disabling also clears bits 1-3.
void CKDetectorBase::SetEnabled(uint32_t enabled) {
    m_baData = (m_baData & ~0x10u) | ((enabled << 4) & 0xfffffff0u);
    if (enabled != 0) return;
    m_baData &= ~0xeu;
}

// 0x001a8a88 CKDetectorBase_Load
int32_t CKDetectorBase::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_baData);
    IKFile_ReadRef(file, &m_pGeometry);
    IKFile_ReadRef(file, &m_pDetectedMovable);
    ReadU32LE(file, &m_ui32NumSector);
    SetEnabled((m_baData >> 5) & 1);  // a virtual call (vt+0x58)
    return 1;
}
