// CKSas.cpp - reconstructed original translation unit: 0x326b8-0x32cb0 (GAME_TOC1, main_toc1), 18 functions, 15 live.
// Primary class: CKSas  key 0x44c  category Logic  size 0x3c  vtable 0xb141a0
// Other owners: CKSector (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x326b8  CKSas_Delete
//   [x] 0x32708  CKSas_RecursiveRegistration
//   [ ] 0x32768  RegisterCKSasClass
//   [ ] 0x327e0  _GLOBAL__I_327e0
//   [x] 0x327f0  CKSas_DeleteArray
//   [x] 0x32898  CKSas_Create
//   [x] 0x328d0  CKSas_CreateArray
//   [ ] 0x32968  CKSas_Save
//   [x] 0x32970  CKSas_Load
//   [x] 0x32b00  CKSas_PostLoad
//   [ ] 0x32b08  CKSas_IsPointInBoxForSector_maybe  [dead]
//   [x] 0x32bb0  CKSas_Destroy  (empty: the default)
//   [x] 0x32bb8  CKSector_Delete  (CKSector DOTD_DECLARE_FACTORIES Delete: vt+0x04 when not null)
//   [x] 0x32c08  CKSector_SetActive_maybe  (inline in CKSector.h)
//   [x] 0x32c20  CKSector_vf54  (CKSector.h SectorLoaded: empty)
//   [x] 0x32c28  CKSector_vf58  (CKSector.h SectorUnload: empty)
//   [ ] 0x32c30  FUN_00032c30  [dead]
//   [ ] 0x32c40  FUN_00032c40  [dead]
//
//   [ ] 0x994090  CKSas_GetClassType  [inline]
//   [ ] 0x994098  CKSas_GetClassID  [inline]
//   [x] 0x9940a0  CKSas_GetSerializationFlags  [inline]
//   [ ] 0x9940a8  CKSas_IsKindOfClass  [inline]
//   [ ] 0x9940c8  CKSas_DeletingDestructor  [inline]
//   [ ] 0x994108  CKSas_Destructor  [inline]
#include "k2000/logic/CKSas.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x00032970 CKSas_Load: the two sector numbers, then the two boxes (twelve floats). The original reads the bytes
// raw and swaps each word.
int32_t CKSas::Load(IKFile* file, int32_t /*type*/) {
    ReadU32LEWords(file, &m_ui32SectorA, 2);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_boxA), 12);
    return 1;
}

// 0x00032708 CKSas_RecursiveRegistration
void CKSas::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
