// CKDefaultGameStructure.cpp - reconstructed original translation unit 0x38cf0-0x39190 (GAME_TOC1, main_toc1), 10 functions, 10 live.
// Primary class: CKDefaultGameStructure  key 0x354c  category Logic  size 0x48  vtable 0xb146e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x38cf0  CKDefaultGameStructure_Delete  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [ ] 0x38d40  RegisterCKDefaultGameStructureClass
//   [ ] 0x38db8  _GLOBAL__I_38db8
//   [ ] 0x38dc8  CKDefaultGameStructure_Save
//   [x] 0x38ea8  CKDefaultGameStructure_RecursiveRegistration  (inherited: IKGameStructure_vf24)
//   [x] 0x38ed0  CKDefaultGameStructure_Destroy  (inherited: IKGameStructure_Destroy)
//   [x] 0x38ef8  CKDefaultGameStructure_DeleteArray  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x38fa0  CKDefaultGameStructure_CreateArray  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x39058  CKDefaultGameStructure_Create  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x390b0  CKDefaultGameStructure_Load
#include "k2000/logic/CKDefaultGameStructure.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"

// 0x000390b0 CKDefaultGameStructure_Load (IKGameStructure's 0x41f90 first)
int32_t CKDefaultGameStructure::Load(IKFile* file, int32_t type) {
    IKGameStructure::Load(file, type);
    if (type != K_GAME_MEMCARD) return 1;
    IKSerializable* spawnPoint = reinterpret_cast<IKSerializable*>(m_pCurrentSpawnPoint);
    if (file->m_pSavingInterfaces != nullptr) {
        file->m_pSavingInterfaces->WriteAsHandle(file, spawnPoint);  // vt+0x48
    } else {
        const uint32_t raw = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(spawnPoint));  // the pointer's word (stw)
        const uint8_t b[4] = {static_cast<uint8_t>(raw >> 24), static_cast<uint8_t>(raw >> 16),
                              static_cast<uint8_t>(raw >> 8), static_cast<uint8_t>(raw)};
        file->Write(b, 4);  // vt+0x20
    }
    return 1;
}
