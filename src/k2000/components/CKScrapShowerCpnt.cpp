// CKScrapShowerCpnt.cpp - reconstructed original translation unit 0x4a66d0-0x4a7460 (GAME_TOC1, main_toc1), 22 functions, 19 live.
// Primary class: CKScrapShowerCpnt  key 0x5c6  category Component  size 0x20  vtable 0xb286c0
// Other owners: CKHkScrapShower (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4a66d0  CKScrapShowerCpnt_Delete
//   [ ] 0x4a6720  RegisterCKScrapShowerCpntClass
//   [ ] 0x4a6798  _GLOBAL__I_4a6798
//   [ ] 0x4a67a8  CKHkScrapShower_SetPieceShadowScale_maybe
//   [ ] 0x4a6820  CKHkScrapShower_RegisterPieceShadow_maybe
//   [ ] 0x4a6928  CKHkScrapShower_TryCameraShake_maybe
//   [ ] 0x4a69f0  CKScrapShowerCpnt_PostLoad
//   [ ] 0x4a6a18  CKScrapShowerCpnt_RecursiveRegistration
//   [ ] 0x4a6a40  CKScrapShowerCpnt_Destroy
//   [ ] 0x4a6a80  CKScrapShowerCpnt_DeletingDestructor
//   [ ] 0x4a6ac8  CKScrapShowerCpnt_Destructor
//   [ ] 0x4a6af8  CKScrapShowerCpnt_DestructBody
//   [ ] 0x4a6b28  CKScrapShowerCpnt_Construct  [dead]
//   [ ] 0x4a6b60  CKScrapShowerCpnt_Construct_2  [dead]
//   [x] 0x4a6b98  CKScrapShowerCpnt_DeleteArray
//   [ ] 0x4a6c38  CKHkScrapShower_LaunchScrapAtPoint_maybe
//   [ ] 0x4a6c88  FUN_004a6c88  [dead]
//   [ ] 0x4a6cb0  CKHkScrapShower_UnregisterPieceShadow_maybe
//   [x] 0x4a6d30  CKScrapShowerCpnt_CreateArray
//   [x] 0x4a6de0  CKScrapShowerCpnt_Create
//   [ ] 0x4a6e38  CKScrapShowerCpnt_Save
//   [x] 0x4a7138  CKScrapShowerCpnt_Load
//
//   [ ] 0x9c4ec8  CKScrapShowerCpnt_IsKindOfClass  [inline]
//   [x] 0x9c4f00  CKScrapShowerCpnt_GetClassType  [inline]
//   [x] 0x9c4f08  CKScrapShowerCpnt_GetClassID  [inline]
#include "k2000/components/CKScrapShowerCpnt.h"

#include "k2000/io/IKFile.h"

// 0x004a7138 CKScrapShowerCpnt_Load
int32_t CKScrapShowerCpnt::Load(IKFile* file, int32_t type) {
    IKMecaCpnt::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk0c);
        ReadU8(file, &m_ui8NbEntries);
        m_aEntries = new Entry[m_ui8NbEntries];  // OperatorNewArray(n * 8)
        for (uint32_t i = 0; i < m_ui8NbEntries; ++i) {
            IKFile_ReadRef(file, &m_aEntries[i].m_pRef);
            m_aEntries[i].m_bEnabled = 1;
        }
        IKFile_ReadRef(file, &m_pUnk10);
        ReadF32LE(file, &m_unk18);
        ReadF32LE(file, &m_unk1c);
        IKFile_ReadRef(file, &m_pUnk14);
    }
    return 1;
}
